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
**  FILENAME     : Mcu_17_TimerIp.h                                           **
**                                                                            **
**  VERSION      : 24.0.0                                                     **
**                                                                            **
**  DATE         : 2021-02-04                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Timer IP functions header definition file                  **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/*[cover parentID={CA14F0F2-695F-47fd-928A-C41F5D0ED7CF}][/cover]*/
/* [cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}][/cover] */
#ifndef MCU_17_TIMERIP_H
#define MCU_17_TIMERIP_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Mcal_Compiler.h"
#include "Mcu_17_TimerIp_Cfg.h"

#if (MCU_GTM_USED == STD_ON)
/* ACCESS is undefined here to resolve the conflict between macro 'ACCESS'
 * (ObjectAccessType) used in OS module and the structure member 'ACCESS'
 * (Ifx_GTM_ARU) used in GTM SFR definitions.
 * This is to be done before including "IfxGtm_reg.h"
 */
#ifdef ACCESS
#undef ACCESS
#endif
#include "IfxGtm_reg.h"
#endif
/* End of #if (MCU_GTM_USED == STD_ON) */

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/*Service ID definitions for ISRs - used during error reporting */
#define MCU_TOM_CH_ISR                        ((uint8)146U)
#define MCU_ATOM_CH_ISR                       ((uint8)147U)
#define MCU_TIM_CH_ISR                        ((uint8)148U)
#define MCU_CCU6_CH_ISR                       ((uint8)149U)
#define MCU_GPT12_CH_ISR                      ((uint8)150U)
#define MCU_STM_COMP_ISR                      ((uint8)151U)
#define MCU_ERU_OGU_ISR                       ((uint8)152U)

#if (MCU_SAFETY_ENABLE == STD_ON)
/* Error ID for spurious interrupt Safety Error*/
#define MCU_E_INVALID_ISR                     ((uint8)202U)
#endif

/* Macros related to timer user data table */
#define TIMER_CH_UNUSED                       (0x0U)
#define TIMER_IP_NO_USER                      (0x0U)
#define TIMER_NO_OF_CALLBACK                  (0x8U)
#define TIMER_CH_USED_BY_ADC_DRIVER           (0x1U)
#define TIMER_CH_USED_BY_WDG_DRIVER           (0x2U)
#define TIMER_CH_USED_BY_PWM_DRIVER           (0x3U)
#define TIMER_CH_USED_BY_GPT_DRIVER           (0x4U)
#define TIMER_CH_USED_BY_ICU_DRIVER           (0x5U)
#define TIMER_CH_USED_BY_OCU_DRIVER           (0x6U)
#define TIMER_CH_USED_BY_DSADC_DRIVER         (0x7U)

/* Macros related to TIM module */
#if (MCU_GTM_USED == STD_ON)
#define GTM_MAX_TIM_CHANNELS                  (MCU_17_GTM_NO_OF_TIM_MODULES * \
                                                MCU_17_GTM_NO_OF_TIM_CHANNELS)
#define GTM_TIM_IRQ_EN_REG_MSK                (0x3FU)
#define GTM_TIM_CLR_PENDING_IRQ               (0x3FU)
#define GTM_TIM_IRQ_MODE_POS                  (0x6U)
#define GTM_TIM_REG_RESET                     (0x0U)
#define GTM_TIM_CH_RESET                      (0x1U)
#define GTM_TIM_CH_ENABLE                     (0x1U)
#define GTM_TIM_CH_DISABLE                    (0x0U)

/* Macros related to TOM module */
#define GTM_MAX_TOM_CHANNELS                  (MCU_17_GTM_NO_OF_TOM_MODULES * \
                                                 MCU_17_GTM_NO_OF_TOM_CHANNELS)
#define GTM_TOM_CLR_PENDING_IRQ               (0x3U)
#define GTM_TOM_IRQ_EN_REG_MSK                (0x3U)
#define GTM_TOM_IRQ_MODE_POS                  (0x6U)
#define GTM_TOM_REG_RESET                     (0x0U)
#define GTM_TOM_CH_PER_TGC                    (0x8U)
#define GTM_TOM_CH_ENABLE                     (0x2UL)
#define GTM_TOM_CH_OUT_ENABLE                 (0x2UL)
#define GTM_TOM_CH_DISABLE                    (0x1UL)
#define GTM_TOM_CH_OUT_DISABLE                (0x1UL)
#define GTM_TOM_BITS_PER_CHAN                 (0x2U)
#define GTM_TOM_CH_SW_RESET                   (0x1U)
#define GTM_TOM_TGC0                          (0x0U)
#define GTM_TOM_TGC1                          (0x1U)
#define GTM_TOM_FORCE_UPDATE_ENABLE           (0x2U)
#define GTM_TOM_FORCE_UPDATE_DISABLE          (0x1U)
#define GTM_TOM_HOST_TRIGGER_ENABLE           (0x1U)
#define GTM_TOM_HOST_TRIGGER_DISABLE          (0x0U)
#define GTM_TOM_CH_ENABLED                    (0x3U)
#define GTM_TOM_CH_DISABLED                   (0x0U)
#define GTM_TOM_DISABLE_STAT_UPDATE           (0x0U)
#define GTM_DISABLE_RSTCN0_FUPD               (0x55555555U)
#define GTM_RESTORE_RSTCN0_FUPD               (0x55555555U)
#define GTM_TOM_CHAN_PER_SRN                  (0x2U)
#define GTM_TOM_CH_STAT_NO_UPDATE             (0x0UL)

/* Macros related to ATOM module */
#define GTM_MAX_ATOM_CHANNELS                 (MCU_17_GTM_NO_OF_ATOM_MODULES * \
                                                MCU_17_GTM_NO_OF_ATOM_CHANNELS)
#define GTM_ATOM_CH_ENABLE                    (0x2UL)
#define GTM_ATOM_CH_DISABLE                   (0x1UL)
#define GTM_ATOM_CH_OUT_ENABLE                (0x2UL)
#define GTM_ATOM_CH_OUT_DISABLE               (0x1UL)
#define GTM_ATOM_CLR_PENDING_IRQ              (0x3U)
#define GTM_ATOM_IRQ_EN_REG_MSK               (0x3U)
#define GTM_ATOM_IRQ_MODE_POS                 (0x6U)
#define GTM_ATOM_REG_RESET                    (0x0U)
#define GTM_ATOM_BITS_PER_CHAN                (0x2U)
#define GTM_ATOM_FORCE_UPDATE_ENABLE          (0x2U)
#define GTM_ATOM_FORCE_UPDATE_DISABLE         (0x1U)
#define GTM_ATOM_HOST_TRIGGER_ENABLE          (0x1U)
#define GTM_ATOM_HOST_TRIGGER_DISABLE         (0x0U)
#define GTM_ATOM_DISABLE_STAT_UPDATE          (0x0U)
#define GTM_ATOM_CH_SW_RESET                  (0x1UL)
#define GTM_ATOM_CHAN_PER_SRN                 (0x2U)
#define GTM_ATOM_CH_STAT_NO_UPDATE            (0x0UL)
#define GTM_CHANNEL_NO_OFF                    (0x0U)
#define GTM_MODULE_NO_OFF                     (0x8U)
#define GTM_MODULE_NO_MASK                    (0x0000FF00U)
#define GTM_CHANNEL_NO_MASK                   (0x000000FFU)

#endif /* End of #if (MCU_GTM_USED == STD_ON) */

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
#if (MCU_GTM_USED == STD_ON)

/* Type definitions relating to GTM timer APIs */
/*[cover parentID= {1AD85D3E-1AEA-4b06-87AE-6F486891194E}]*/
typedef uint32 Mcu_17_Gtm_TimerOutType;
#define MCU_GTM_TIMER_TOM                ((Mcu_17_Gtm_TimerOutType)0U)
#define MCU_GTM_TIMER_ATOM               ((Mcu_17_Gtm_TimerOutType)1U)
/*[/cover]*/

/*[cover parentID={F66E552F-F8B0-4834-884C-BB9025CFCFE9}]*/
typedef uint8 Mcu_17_Gtm_TimerOutputEnableType;
#define MCU_GTM_TIMER_OUT_DISABLE        ((Mcu_17_Gtm_TimerOutputEnableType)0U)
#define MCU_GTM_TIMER_OUT_ENABLE         ((Mcu_17_Gtm_TimerOutputEnableType)1U)
/*[/cover]*/

/*[cover parentID={399B7EAF-A13A-4492-8943-A2DD800E9800}][/cover]*/
typedef uint8 Mcu_17_Gtm_TimerEnableType;
#define MCU_GTM_TIMER_DISABLE        ((Mcu_17_Gtm_TimerEnableType)0U)
#define MCU_GTM_TIMER_ENABLE         ((Mcu_17_Gtm_TimerEnableType)1U)

/*[cover parentID={2DE45A5E-4662-4e8a-8CAE-B30353524465}]*/
typedef enum
{
  MCU_NOCHANGE_OUT_ON_TRIGGER = 0X0U,
  MCU_DISABLE_OUT_ON_TRIGGER  = 0x1U,
  MCU_ENABLE_OUT_ON_TRIGGER   = 0x2U
} Mcu_17_Gtm_TimerOutputEnTriggerType;
/*[/cover]*/

/*[cover parentID={832E588D-F022-413e-A427-1842C96174F7}]*/
typedef enum
{
  MCU_NOCHANGE_ON_TRIGGER = 0X0U,
  MCU_DISABLE_ON_TRIGGER  = 0x1U,
  MCU_ENABLE_ON_TRIGGER   = 0x2U
} Mcu_17_Gtm_TimerEnTriggerType;
/*[/cover]*/

/*[cover parentID={83A70188-CA89-41e5-A6A7-5F2FCBA1B77A}][/cover]*/
typedef uint8 Mcu_17_Gtm_TimerUpdateEnableType;
#define MCU_GTM_TIMER_UPDATE_DISABLE        ((Mcu_17_Gtm_TimerUpdateEnableType)0U)
#define MCU_GTM_TIMER_UPDATE_ENABLE         ((Mcu_17_Gtm_TimerUpdateEnableType)1U)

/*[cover parentID={FDB5C869-32DE-4334-B1BC-2C87BF0C112E}]*/
typedef uint8 Mcu_17_Gtm_TimerStatusType;
#define MCU_GTM_TIMER_STOPPED            ((Mcu_17_Gtm_TimerStatusType)0U)
#define MCU_GTM_TIMER_RUNNING            ((Mcu_17_Gtm_TimerStatusType)1U)
/*[/cover]*/

/*[cover parentID={2B34A25B-EDB8-487f-A47E-C53B59BFE077}]*/
typedef uint8 Mcu_17_Gtm_MappedPortTimerOutType;
#define MCU_OUT_TIMER_MAPPED_COL_A      ((Mcu_17_Gtm_MappedPortTimerOutType)0U)
#define MCU_OUT_TIMER_MAPPED_COL_B      ((Mcu_17_Gtm_MappedPortTimerOutType)1U)
#define MCU_OUT_TIMER_MAPPED_COL_C      ((Mcu_17_Gtm_MappedPortTimerOutType)2U)
#define MCU_OUT_TIMER_MAPPED_COL_D      ((Mcu_17_Gtm_MappedPortTimerOutType)3U)
#define MCU_OUT_TIMER_MAPPED_COL_E      ((Mcu_17_Gtm_MappedPortTimerOutType)4U)
#define MCU_OUT_TIMER_MAPPED_COL_F      ((Mcu_17_Gtm_MappedPortTimerOutType)5U)
#define MCU_OUT_TIMER_MAPPED_COL_G      ((Mcu_17_Gtm_MappedPortTimerOutType)6U)
#define MCU_OUT_TIMER_MAPPED_COL_H      ((Mcu_17_Gtm_MappedPortTimerOutType)7U)
#define MCU_OUT_TIMER_MAPPED_COL_I      ((Mcu_17_Gtm_MappedPortTimerOutType)8U)
#define MCU_OUT_TIMER_MAPPED_COL_J      ((Mcu_17_Gtm_MappedPortTimerOutType)9U)
#define MCU_OUT_TIMER_MAPPED_COL_K      ((Mcu_17_Gtm_MappedPortTimerOutType)10U)
#define MCU_OUT_TIMER_MAPPED_COL_L      ((Mcu_17_Gtm_MappedPortTimerOutType)11U)
/*[/cover]*/

/*[cover parentID={B699BF99-DB77-40c0-85E4-BC7A536F35EC}]*/
typedef uint32 Mcu_17_Gtm_TimerChIdentifierType;
/*[/cover]*/

/*[cover parentID={342EF0E5-263D-4b92-8944-196AE881B23E}]*/
typedef struct
{
  Mcu_17_Gtm_TimerChIdentifierType TimerId;
  uint32 TimChCtrlReg;
  uint32 TimChExtendedCtrlReg;
  uint32 TimChFltRisingEdge;
  uint32 TimChFltFallingEdge;
  uint32 TimChTduvReg;
  uint32 TimChIntEnMode;
} Mcu_17_Gtm_TimChConfigType;
/*[/cover]*/

/*[cover parentID={F224E9D3-72EF-4285-8C7B-3A5B77769F16}]*/
typedef struct
{
  Mcu_17_Gtm_TimerOutType TimerType;
  Mcu_17_Gtm_TimerChIdentifierType TimerId;
  uint32 TimerChCtrlReg;
  uint32 TimerChCN0Reg;
  uint32 TimerChCM0Reg;
  uint32 TimerChCM1Reg;
  uint32 TimerChSR0Reg;
  uint32 TimerChSR1Reg;
  uint32 TimerChIntEnMode;
} Mcu_17_Gtm_TomAtomChConfigType;
/*[/cover]*/

/*TIM structures*/
/*[cover parentID={44435777-AE57-46d4-860A-FE3932442652}]*/
typedef volatile struct
{
  Ifx_GTM_TIM_CH CH;
  uint8 Reserved1[64];
} Mcu_17_Gtm_TimCh;
/*[/cover]*/

/*[cover parentID={CF5D0190-1866-4bec-83A0-91AB9BFFAEB3}]*/
typedef volatile struct
{
  Mcu_17_Gtm_TimCh TIM_CHANNEL[8];
} Mcu_17_Gtm_TimChArray;
/*[/cover]*/

/*TOM structures*/
/*[cover parentID={11F98C57-1374-4c93-B98A-7E9DF87E046D}]*/
typedef volatile struct
{
  /**< \brief 30, TOM TGC0 Global Control Register */
  Ifx_GTM_TOM_TGC_GLB_CTRL   TGC_GLB_CTRL;
  /**< \brief 34, TOM TGC0 Action Time Base Register */
  Ifx_GTM_TOM_TGC_ACT_TB     TGC_ACT_TB;
  /**< \brief 34, TOM TGC0 Action Time Base Register */
  Ifx_GTM_TOM_TGC_FUPD_CTRL  TGC_FUPD_CTRL;
  /**< \brief 38, TOM TGC0 Force Update Control Register */
  Ifx_GTM_TOM_TGC_INT_TRIG   TGC_INT_TRIG;
  /**< \brief 3C, TOM reserved memory */
  uint8 Reserved2[48];
  /**< \brief 70, TOM TGC0 Enable/Disable Control Register */
  Ifx_GTM_TOM_TGC_ENDIS_CTRL TGC_ENDIS_CTRL;
  /**< \brief 74, TOM TGC0 Enable/Disable Status Register */
  Ifx_GTM_TOM_TGC_ENDIS_STAT TGC_ENDIS_STAT;
  /**< \brief 78, TOM TGC0 Output Enable Control Register */
  Ifx_GTM_TOM_TGC_OUTEN_CTRL TGC_OUTEN_CTRL;
  /**< \brief 7C, TOM TGC0 Output Enable Status Register */
  Ifx_GTM_TOM_TGC_OUTEN_STAT TGC_OUTEN_STAT;
  uint8 Reserved3[432];
} Mcu_17_Gtm_TomTgc;
/*[/cover]*/

/*[cover parentID={84C7A620-7D29-4cf8-9FE6-A7060D9C6608}]*/
typedef volatile struct
{
  uint8 Reserved1[48];
  Mcu_17_Gtm_TomTgc TOM_TGC[2];
} Mcu_17_Gtm_TomTgcArray;
/*[/cover]*/

/*[cover parentID={F5F072E1-0F0E-40b2-A87C-DE3911AC4CC1}]*/
typedef volatile struct
{
  Ifx_GTM_TOM_CH CH;
  uint8 Reserved1[20];
} Mcu_17_Gtm_TomCh;
/*[/cover]*/

/*[cover parentID={8F349D3D-31F9-425c-B195-1FCFF01280B0}]*/
typedef volatile struct
{
  Mcu_17_Gtm_TomCh TOM_CHANNEL[16];
} Mcu_17_Gtm_TomChArray;
/*[/cover]*/

/*ATOM structures*/
/*[cover parentID={57D3D05C-5F98-4ac1-B3FF-1CF7E81FE2D8}]*/
typedef volatile struct
{
  Ifx_GTM_ATOM_CH CH;
  uint8 Reserved1[80];
} Mcu_17_Gtm_AtomCh;
/*[/cover]*/

/*[cover parentID={7B524F0E-D267-4d94-8C6F-EDE38ADBC28F}]*/
typedef volatile struct
{
  Mcu_17_Gtm_AtomCh ATOM_CHANNEL[8];
} Mcu_17_Gtm_AtomChArray;
/*[/cover]*/

#endif /* End of #if (MCU_GTM_USED == STD_ON) */

/* Type definitions relating to CCU6 timer APIs */
/*[cover parentID={986639DB-D0AD-4a24-8C26-8AFFC79AA9D6}][/cover]*/
typedef uint8 Mcu_17_Ccu6_KernelIdentifierType;
#define MCU_CCU6_KERNEL_0       ((Mcu_17_Ccu6_KernelIdentifierType)0x0U)
#define MCU_CCU6_KERNEL_1       ((Mcu_17_Ccu6_KernelIdentifierType)0x1U)

/*[cover parentID={DCF0036A-B14D-4c1e-A256-D09796FF43DF}][/cover]*/
typedef uint8 Mcu_17_Ccu6_TimerType;
#define MCU_CCU6_TIMER_T12      ((Mcu_17_Ccu6_TimerType)0x0U)
#define MCU_CCU6_TIMER_T13      ((Mcu_17_Ccu6_TimerType)0x1U)

/*[cover parentID={C8D1FF98-C6D2-4912-BA97-9EC4F3162E9F}][/cover]*/
typedef uint8 Mcu_17_Ccu6_ComparatorType;
#define MCU_CCU6_COMPARATOR_CCU60      ((Mcu_17_Ccu6_ComparatorType)0x0U)
#define MCU_CCU6_COMPARATOR_CCU61      ((Mcu_17_Ccu6_ComparatorType)0x1U)
#define MCU_CCU6_COMPARATOR_CCU62      ((Mcu_17_Ccu6_ComparatorType)0x2U)
#define MCU_CCU6_COMPARATOR_CCU63      ((Mcu_17_Ccu6_ComparatorType)0x3U)

/*[cover parentID={0BF0E4FB-E671-45a5-B5E4-B1E82952058E}][/cover]*/
typedef uint32 Mcu_17_Ccu6_TimerChIdentifierType;

/*[cover parentID={A8D3337B-90DD-4e08-AF85-D8CDE4733846}]*/
typedef struct
{
  Mcu_17_Ccu6_TimerChIdentifierType TimerId;
  uint32 TimerCtrlReg0; /* For T12 - [2-0] - Timer T12 Input Clock Select
                                     [3]   - Timer T12 Prescaler Bit
                                     [7]   - T12 Operating Mode
                           For T13 - [10-8] - Timer T13 Input Clock Select
                                     [11]   - Timer T13 Prescaler Bit*/
  uint32 ModCtrlReg;   /*  For T12 - [1-0] - Timer T12 modulation enable for
                                             comparator
                           For T13 - [2]   - Enable Compare Timer T13 Output
                       */
  uint32 PasStateLvlReg; /*For T12 - [1-0] - Compare Outputs
                                             Passive State Level of comparator
                           For T13 - [2]   - Passive State Level of Output COUT63
                          */
  uint32 TimerCntReg;
  uint32 TimerPeriodReg;
  uint32 Ccu6ShadowReg;
  uint8 TimerModeSelectReg;
  uint8 PortInSelReg0;
  uint8 IntEnReg;           /* 2 - Falling 1- Raising 0- PM */
  uint8 IntNodePointerReg;  /* [3:2]T12/T13, [1:0] CC6x     */
} Mcu_17_Ccu6_TimerConfigType;
/*[/cover]*/

/*[cover parentID={295B766D-522F-43e5-A337-D6F265E253DF}]*/
typedef struct
{
  Mcu_17_Ccu6_TimerChIdentifierType TimerId;
  uint32 IEnBitPos;
  uint32 IEnLen;
  uint32 RegVal;
} Mcu_17_Ccu6_TimerChIntType;
/*[/cover]*/

/* Type definitions relating to GPT12 timer APIs */
/*[cover parentID={111C8577-3073-45a5-9D95-FC68E03E9D28}][/cover]*/
typedef uint8 Mcu_17_Gpt12_TimerBlockType;
#define MCU_GPT12_GPT1_BLOCK             ((Mcu_17_Gpt12_TimerBlockType)1U)
#define MCU_GPT12_GPT2_BLOCK             ((Mcu_17_Gpt12_TimerBlockType)2U)

/*[cover parentID={C25405DB-6F2E-4d52-9143-FFFA96C1F04B}][/cover]*/
typedef uint32 Mcu_17_Gpt12_TimerChIdentifierType;
#define MCU_GPT12_TIMER2             ((Mcu_17_Gpt12_TimerChIdentifierType)0U)
#define MCU_GPT12_TIMER3             ((Mcu_17_Gpt12_TimerChIdentifierType)1U)
#define MCU_GPT12_TIMER4             ((Mcu_17_Gpt12_TimerChIdentifierType)2U)
#define MCU_GPT12_TIMER5             ((Mcu_17_Gpt12_TimerChIdentifierType)3U)
#define MCU_GPT12_TIMER6             ((Mcu_17_Gpt12_TimerChIdentifierType)4U)

/*[cover parentID={36F2C4BE-EDC5-4abf-8673-67A137E7043E}][/cover]*/
typedef uint8 Mcu_17_Gpt12_ClkPrescalarType;
#define MCU_GPT12_GPT1_CLOCK_DIV8        ((Mcu_17_Gpt12_ClkPrescalarType)0U)
#define MCU_GPT12_GPT1_CLOCK_DIV4        ((Mcu_17_Gpt12_ClkPrescalarType)1U)
#define MCU_GPT12_GPT1_CLOCK_DIV32       ((Mcu_17_Gpt12_ClkPrescalarType)2U)
#define MCU_GPT12_GPT1_CLOCK_DIV16       ((Mcu_17_Gpt12_ClkPrescalarType)3U)

#define MCU_GPT12_GPT2_CLOCK_DIV4        ((Mcu_17_Gpt12_ClkPrescalarType)0U)
#define MCU_GPT12_GPT2_CLOCK_DIV2        ((Mcu_17_Gpt12_ClkPrescalarType)1U)
#define MCU_GPT12_GPT2_CLOCK_DIV16       ((Mcu_17_Gpt12_ClkPrescalarType)2U)
#define MCU_GPT12_GPT2_CLOCK_DIV8        ((Mcu_17_Gpt12_ClkPrescalarType)3U)

/*[cover parentID={82556D8C-5349-4d24-840A-A22A2F444664}]*/
typedef struct
{
  Mcu_17_Gpt12_TimerChIdentifierType TimerId;
  uint32 TimerCtrlReg;
  uint32 TimerCntReg;
  uint32 PortInSelReg;/* [3-2] - ISTxEUD , [1-0] - ISTxIN , [4-31] - Reserved*/
} Mcu_17_Gpt12_TimerConfigType;
/*[/cover]*/


/* Function pointer type that defines an MCAL driver callback function */
/*[cover parentID={CFCE01EB-5298-4ab1-A129-239258F61A6C}]*/
typedef void (* const Mcu_17_Timer_CallbackFuncPtrType)
(
  uint32 LogicalChannelId,
  uint32 StatusFlags
);
/*[/cover]*/

/* STM timer configuration information */
/*[cover parentID={13F6CEBB-7E5D-4a38-91F6-A5424676054C}]*/
typedef struct
{
  uint32 CompareRegVal;          /* STM compare Reg Value */
  unsigned_int StmTimerId  : 8;  /* Timer no              */
  unsigned_int CMPRegId    : 8;  /* CMP Register          */
  unsigned_int CmconRegVal : 8;  /* CMCON Reg Value       */
  unsigned_int reserved    : 8;  /* reserved              */
} Mcu_17_Stm_TimerConfigType;
/*[/cover]*/

/* Type definitions relating to STM timer APIs */
/*[cover parentID={ECB708E5-F0DC-43df-83E8-A008A7F046FA}][/cover]*/
typedef uint32 Mcu_17_Stm_StmIdentifierType;

/*[cover parentID={02C8E207-B5A9-4794-B66B-43C02B11B8D0}][/cover]*/
typedef uint8 Mcu_17_Stm_StmCmpIdentifierType;

/*[cover parentID={DD0A4985-5B95-490e-BFDA-9E64797FAE58}][/cover]*/
typedef uint8 Mcu_17_Stm_ComIntEnableType;

/* Type definitions relating to ERU APIs */
/*[cover parentID={DE2169E1-B376-4632-BE3D-5431ECD974EF}][/cover]*/
typedef uint8 Mcu_17_Eru_SrcIdentifierType;
/*******************************************************************************
**                            Global Macros                                   **
*******************************************************************************/
#if (MCU_GTM_USED == STD_ON)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'GTM_TOM_CH_POINTER' defined for easy readability in code.
 * No side effects foreseen by violating this MISRA rule. */
/* Macro to get the TOM channel base address*/
#define GTM_TOM_CH_POINTER(Module,Channel) \
               (&(((Mcu_17_Gtm_TomChArray*)(volatile void*)\
                   (&(MODULE_GTM.TOM[Module])))->TOM_CHANNEL[Channel].CH))

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'GTM_TOM_TGC_POINTER' defined for easy readability in code.
 * No side effects foreseen by violating this MISRA rule. */
/* Macro to get the TOM TGCx base address*/
#define GTM_TOM_TGC_POINTER(Module,TomTgcIndex) \
               (&(((Mcu_17_Gtm_TomTgcArray*)(volatile void*)\
                   (&(MODULE_GTM.TOM[Module])))->TOM_TGC[TomTgcIndex]))

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'GTM_ATOM_CH_POINTER' defined for easy readability in code.
 * No side effects foreseen by violating this MISRA rule. */
/* Macro to get the ATOM channel base address*/
#define GTM_ATOM_CH_POINTER(Module,Channel) \
               (&(((Mcu_17_Gtm_AtomChArray*)(volatile void*)\
                   (&(MODULE_GTM.ATOM[Module])))->ATOM_CHANNEL[Channel].CH))

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'GTM_ATOM_AGC_POINTER' defined for easy readability in code.
 * No side effects foreseen by violating this MISRA rule. */
/* Macro to get the ATOM AGC base address*/
#define GTM_ATOM_AGC_POINTER(Module) \
               (&(&(MODULE_GTM.ATOM[Module]))->AGC)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'GTM_TIM_CH_POINTER' defined for easy readability in code.
 * No side effects foreseen by violating this MISRA rule. */
/* Macro to get the TIM channel base address*/
#define GTM_TIM_CH_POINTER(Module,Channel) \
               (&(((Mcu_17_Gtm_TimChArray*)(volatile void*)\
                   (&(MODULE_GTM.TIM[Module])))->TIM_CHANNEL[Channel].CH))

#endif
/* End of #if (MCU_GTM_USED == STD_ON) */

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
#define MCU_17_TIMERIP_START_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Mcu_MemMap.h"

#if (MCU_GTM_USED == STD_ON)

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Gtm_TomChannelInit\
              (const Mcu_17_Gtm_TomAtomChConfigType * const ConfigPtr);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Gtm_TomChannelShadowTransfer
(
  const uint8 Module,
  const uint8 Channel
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Gtm_TomChannelDeInit
(
  const uint8 Module,
  const uint8 Channel
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
**                    "TimerOutputEn", the application can decide to          **
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
extern void Mcu_17_Gtm_TomChannelEnable
(
  const uint8 Module,
  const uint8 Channel,
  const Mcu_17_Gtm_TimerOutputEnableType TimerOutputEn
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Gtm_TomChannelDisable
(
  const uint8 Module,
  const uint8 Channel
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern Mcu_17_Gtm_TimerStatusType Mcu_17_Gtm_IsTomChannelEnabled
(
  const uint8 Module,
  const uint8 Channel
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Gtm_TomTriggerRequest
(
  const uint8 Module,
  const uint8 TomTgcIndex,
  const uint16 TriggerChannels
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
** Reentrancy       : Reentrant for other channels                            **
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
extern Std_ReturnType Mcu_17_Gtm_TomChInitCheck
(
  const Mcu_17_Gtm_TomAtomChConfigType *const ConfigPtr
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Gtm_TomChUpdateEnDis
(
  const uint8 Module,
  const uint8 Channel,
  const Mcu_17_Gtm_TimerUpdateEnableType UpEnVal
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Gtm_TomChOutEnCtrlUpdate
(
  const uint8 Module,
  const uint8 Channel,
  const Mcu_17_Gtm_TimerOutputEnTriggerType TimerOutputEnDis
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Gtm_TomChOutEnStatUpdate
(
  const uint8 Module,
  const uint8 Channel,
  const Mcu_17_Gtm_TimerOutputEnableType TimerOutputEnDis
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Gtm_TomChEndisCtrlUpdate
(
  const uint8 Module,
  const uint8 Channel,
  const Mcu_17_Gtm_TimerEnTriggerType TimerEnDis
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Gtm_TomChEndisStatUpdate
(
  const uint8 Module,
  const uint8 Channel,
  const Mcu_17_Gtm_TimerEnableType TimerEnDis
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Gtm_AtomChannelInit
(
  const Mcu_17_Gtm_TomAtomChConfigType *const ConfigPtr
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Gtm_AtomChannelShadowTransfer
(
  const uint8 Module,
  const uint8 Channel
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Gtm_AtomChannelDeInit
(
  const uint8 Module,
  const uint8 Channel
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
**                    "TimerOutputEn", the application can decide to          **
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
extern void Mcu_17_Gtm_AtomChannelEnable
(
  const uint8 Module,
  const uint8 Channel,
  const Mcu_17_Gtm_TimerOutputEnableType TimerOutputEn
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Gtm_AtomChannelDisable
(
  const uint8 Module,
  const uint8 Channel
);

/*******************************************************************************
** Traceability    : [cover parentID=]                                        **
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
extern Mcu_17_Gtm_TimerStatusType Mcu_17_Gtm_IsAtomChannelEnabled
(
  const uint8 Module,
  const uint8 Channel
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Gtm_AtomTriggerRequest
(
  const uint8 Module,
  const uint16 TriggerChannels
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : ConfigPtr - Pointer to configuration data of a ATOM     **
**                    channel                                                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
extern Std_ReturnType Mcu_17_Gtm_AtomChInitCheck
(
  const Mcu_17_Gtm_TomAtomChConfigType *const ConfigPtr
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Gtm_AtomChUpdateEnDis
(
  const uint8 Module,
  const uint8 Channel,
  const Mcu_17_Gtm_TimerUpdateEnableType UpEnVal
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Gtm_AtomChOutEnCtrlUpdate
(
  const uint8 Module,
  const uint8 Channel,
  const Mcu_17_Gtm_TimerOutputEnTriggerType TimerOutputEnDis
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Gtm_AtomChOutEnStatUpdate
(
  const uint8 Module,
  const uint8 Channel,
  const Mcu_17_Gtm_TimerOutputEnableType TimerOutputEnDis
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Gtm_AtomChEndisCtrlUpdate
(
  const uint8 Module,
  const uint8 Channel,
  const Mcu_17_Gtm_TimerEnTriggerType TimerEnDis
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Gtm_AtomChEndisStatUpdate
(
  const uint8 Module,
  const uint8 Channel,
  const Mcu_17_Gtm_TimerEnableType TimerEnDis
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Gtm_TimChannelInit
(
  const Mcu_17_Gtm_TimChConfigType * const ConfigPtr
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Gtm_TimChannelDeInit
(
  const uint8 Module,
  const uint8 Channel
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Gtm_TimChannelEnable
(
  const uint8 Module,
  const uint8 Channel
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Gtm_TimChannelDisable
(
  const uint8 Module,
  const uint8 Channel
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern Mcu_17_Gtm_TimerStatusType Mcu_17_Gtm_IsTimChannelEnabled
(
  const uint8 Module,
  const uint8 Channel
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Gtm_ConnectPortPinToTim
(
  const uint8 Module,
  const uint8 Channel,
  const uint8 TimerChselValue
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
** Service ID       : 0x71                                                    **
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
extern void Mcu_17_Gtm_ConnectTimerOutToPortPin
(
  const uint16 Tout_IndexNumber,
  const Mcu_17_Gtm_MappedPortTimerOutType TimerOutColumnSelect
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
** Reentrancy       : Reentrant for other channels                            **
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
extern Std_ReturnType Mcu_17_Gtm_TimChInitCheck
(
  const Mcu_17_Gtm_TimChConfigType *const ConfigPtr
);

#endif
/* End of #if (MCU_GTM_USED == STD_ON) */

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Ccu6_TimerInit
(
  const Mcu_17_Ccu6_TimerConfigType * const ConfigPtr
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Ccu6_TimerDeInit
(
  const Mcu_17_Ccu6_TimerChIdentifierType TimerId
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Ccu6_TimerStart
(
  const Mcu_17_Ccu6_TimerChIdentifierType TimerId
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Ccu6_TimerStop
(
  const Mcu_17_Ccu6_TimerChIdentifierType TimerId
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Ccu6_TimerShadowTransfer
(
  const Mcu_17_Ccu6_TimerChIdentifierType TimerId
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
** Parameters(in)   : Ccu6IntConfig - CCU6 timer channel interrupt is         **
**                                    configuration                           **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
extern void Mcu_17_Ccu6_TimerIntEnDis
(
  const Mcu_17_Ccu6_TimerChIntType * const Ccu6IntConfig
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern Std_ReturnType Mcu_17_Ccu6_TimerInitCheck
(
  const Mcu_17_Ccu6_TimerConfigType * const ConfigPtr
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Gpt12_TimerInit
(
  const Mcu_17_Gpt12_TimerConfigType * const ConfigPtr
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern Std_ReturnType Mcu_17_Gpt12_TimerInitCheck
(
  const Mcu_17_Gpt12_TimerConfigType *const ConfigPtr
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Gpt12_TimerDeInit
(
  const Mcu_17_Gpt12_TimerChIdentifierType TimerId
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Gpt12_TimerStart
(
  const Mcu_17_Gpt12_TimerChIdentifierType TimerId
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Gpt12_TimerStop
(
  const Mcu_17_Gpt12_TimerChIdentifierType TimerId
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Stm_SetupComparator
(
  const Mcu_17_Stm_TimerConfigType * const ConfigPtr
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
** Reentrancy       : Reentrant for other STM Timers                          **
**                                                                            **
** Parameters(in)   : ConfigPtr - STM Timer channel initialization contents   **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value   :   E_OK      - No error has been detected                  **
**                    E_NOT_OK  - Error has been detected                     **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Mcu_17_Stm_CheckComparator
(
  const Mcu_17_Stm_TimerConfigType * const ConfigPtr
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Stm_ComparatorIntDisable
(
  const uint8 StmTimerId,
  const uint8 StmComparatorId
);

#define MCU_17_TIMERIP_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
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
** Traceability     : [cover parentID=]                                       **
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
** Parameters(in)   : Module -        TOM Module ID                           **
**                    Channel -       TOM Channel ID                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Mcu_17_Gtm_TomChannelIsr
(
  const uint8 Module,
  const uint8 Channel
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
** Parameters(in)   : Module -        ATOM Module ID                          **
**                    Channel -       ATOM Channel ID                         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Mcu_17_Gtm_AtomChannelIsr
(
  const uint8 Module,
  const uint8 Channel
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
** Parameters(in)   : Module -        TIM Module ID                           **
**                    Channel -       TIM Channel ID                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Mcu_17_Gtm_TimChannelIsr
(
  const uint8 Module,
  const uint8 Channel
);

#endif
/* End of #if (MCU_GTM_USED == STD_ON) */

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Ccu6_ChannelIsr
(
  const Mcu_17_Ccu6_KernelIdentifierType Kernel,
  const Mcu_17_Ccu6_ComparatorType Comparator
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Gpt12_ChannelIsr
(
  const Mcu_17_Gpt12_TimerChIdentifierType Timer
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Stm_CompareMatchIsr
(
  const Mcu_17_Stm_StmIdentifierType StmTimerId,
  const Mcu_17_Stm_StmCmpIdentifierType StmCmpId
);

/*******************************************************************************
** Traceability     : [cover parentID=]                                       **
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
extern void Mcu_17_Eru_GatingIsr
(
  const Mcu_17_Eru_SrcIdentifierType EruSrcId
);

#define MCU_17_TIMERIP_STOP_SEC_CODE_FAST_ASIL_B_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Mcu_MemMap.h"

#endif
/* End of #ifndef MCU_17_TIMERIP_H */
