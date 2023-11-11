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
**  FILENAME     : Mcu.c                                                      **
**                                                                            **
**  VERSION      : 52.0.0                                                     **
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
**  DESCRIPTION  : Mcu Driver source file                                     **
**                                                                            **
**  SPECIFICATION(S) : Specification of Mcu Driver, AUTOSAR Release 4.2.2 and **
**                     4.4.0                                                  **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* [cover parentID={06798858-8368-416d-B33B-DF81AD5ADCA1}][/cover] */
/* [cover parentID={7BECF43B-4104-476f-91BC-65753183E675}][/cover] */
/* [cover parentID={EEE64FD5-CC6C-490f-9686-1A9647CE55F1}][/cover] */
/* [cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}][/cover] */
#include "Mcu.h"
#include "Mcu_17_TimerIp.h"
#include "IfxScu_reg.h"
#include "IfxPms_reg.h"
#include "IfxPms_bf.h"
/* Mcu Operation in User 1 Mode  */
#if (MCU_INIT_DEINIT_API_MODE == MCU_MCAL_USER1) || \
    (MCU_RUNTIME_API_MODE == MCU_MCAL_USER1)
#include "McalLib_OsStub.h"
#endif
#include "IfxConverter_reg.h"
#include "IfxConverter_bf.h"
#if ((MCU_GPT1_USED == STD_ON) || (MCU_GPT2_USED == STD_ON))
#include "IfxGpt12_reg.h"
#include "IfxGpt12_bf.h"
#endif
/* End of #if ((MCU_GPT1_USED == STD_ON) || (MCU_GPT2_USED == STD_ON)) */
#if (MCU_CCU60_USED == STD_ON) || (MCU_CCU61_USED == STD_ON)
#include "IfxCcu6_reg.h"
#include "IfxCcu6_bf.h"
#endif
/* End of #if (MCU_CCU60_USED == STD_ON) || (MCU_CCU61_USED == STD_ON) */
#include "IfxScu_bf.h"
#if (MCU_GTM_USED == STD_ON)
#include "IfxGtm_bf.h"
#endif
/* End of #if (MCU_GTM_USED == STD_ON) */

#if (MCU_E_ERR_DEM_REPORTING == STD_ON)
#include "Mcal_Wrapper.h"
#endif

#if (MCU_DEV_ERROR_DETECT == STD_ON)
/* Import of DET functionality */
#include "Det.h"
#endif /* End Of MCU_DEV_ERROR_DETECT */

#if (MCU_SAFETY_ENABLE == STD_ON)
#include "Mcal_SafetyError.h"
#endif

/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/
#ifndef MCU_AR_RELEASE_MAJOR_VERSION
#error "MCU_AR_RELEASE_MAJOR_VERSION is not defined."
#endif

#if (MCU_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION)
#error "MCU_AR_RELEASE_MAJOR_VERSION does not match."
#endif

#ifndef MCU_AR_RELEASE_MINOR_VERSION
#error "MCU_AR_RELEASE_MINOR_VERSION is not defined."
#endif

#if (MCU_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION)
#error "MCU_AR_RELEASE_MINOR_VERSION does not match."
#endif

#ifndef MCU_AR_RELEASE_REVISION_VERSION
#error "MCU_AR_RELEASE_REVISION_VERSION is not defined."
#endif

#if (MCU_AR_RELEASE_REVISION_VERSION != MCAL_AR_RELEASE_REVISION_VERSION)
#error "MCU_AR_RELEASE_REVISION_VERSION does not match."
#endif

#ifndef MCU_SW_MAJOR_VERSION
#error "MCU_SW_MAJOR_VERSION is not defined."
#endif

#ifndef MCU_SW_MINOR_VERSION
#error "MCU_SW_MINOR_VERSION is not defined."
#endif

#ifndef MCU_SW_PATCH_VERSION
#error "MCU_SW_PATCH_VERSION is not defined."
#endif

/*[cover parentID={BBD0BE43-D6EB-45c7-B4E8-FA2B9BEB7D7A}]*/
#if (MCU_SW_MAJOR_VERSION != 20U)
#error "MCU_SW_MAJOR_VERSION does not match."
#endif

#if (MCU_SW_MINOR_VERSION != 25U)
#error "MCU_SW_MINOR_VERSION does not match."
#endif

#if (MCU_SW_PATCH_VERSION != 0U)
#error "MCU_SW_PATCH_VERSION does not match."
#endif

#if (MCU_DEV_ERROR_DETECT == STD_ON)
#ifndef DET_AR_RELEASE_MAJOR_VERSION
#error "DET_AR_RELEASE_MAJOR_VERSION is not defined."
#endif

/*[cover parentID={25C03FE0-5223-4e77-A5DE-E7A30348AB5D}][/cover]*/
#if (DET_AR_RELEASE_MAJOR_VERSION != 4U)
#error "DET_AR_RELEASE_MAJOR_VERSION does not match."
#endif
#endif /* End for MCU_DEV_ERROR_DETECT */
/*[/cover]*/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
/* Oscillator related Macros */
/* Macro to check Oscillator is disabled */
#if (MCU_INIT_CLOCK_API == STD_ON)
#define MCU_OSC_DIS_POWERSAVING_MODE (3U)
#endif

/* Mcu driver macros for commonly used numerical values */
#define MCU_PMSWCR_BUSY    (1U)

/*Mcu RAM section Macros*/
#if (MCAL_AR_VERSION == MCAL_AR_440)

#define MCU_RAM_WRITE_SIZE_HALF_WORD           (2U)
#define MCU_RAM_WRITE_SIZE_WORD                (4U)
#define MCU_RAM_WRITE_SIZE_DOUBLE_WORD         (8U)
#endif

#if ((MCU_NO_OF_STDBY_RAM_BLK != 0U) || (MCU_GTM_USED == STD_ON))
#define MCU_STARTING_INDEX (0U)
#endif

#define MCU_RAM_SIZE_ZERO  (0U)

#define MCU_PMS_EVRUVMON_MASK (((uint32)IFX_PMS_UVMON_SWDUVVAL_MSK << \
IFX_PMS_UVMON_SWDUVVAL_OFF) | ((uint32)IFX_PMS_UVMON_EVRCUVVAL_MSK << \
IFX_PMS_UVMON_EVRCUVVAL_OFF))

#define MCU_PMS_EVRMONCTRL_MASK (((uint32)IFX_PMS_MONCTRL_SWDUVMOD_MSK << \
IFX_PMS_MONCTRL_SWDUVMOD_OFF) | ((uint32)IFX_PMS_MONCTRL_EVRCUVMOD_MSK << \
IFX_PMS_MONCTRL_EVRCUVMOD_OFF))

#define MCU_PMSWCR5_MASK    (((uint32)IFX_PMS_PMSWCR5_BPTRISTREQ_MSK << \
IFX_PMS_PMSWCR5_BPTRISTREQ_OFF) | ((uint32)IFX_PMS_PMSWCR5_TRISTREQ_MSK << \
IFX_PMS_PMSWCR5_TRISTREQ_OFF)   | ((uint32)IFX_PMS_PMSWCR5_ESR0TRIST_MSK << \
IFX_PMS_PMSWCR5_ESR0TRIST_OFF)  | ((uint32)IFX_PMS_PMSWCR5_PORSTDF_MSK << \
IFX_PMS_PMSWCR5_PORSTDF_OFF))

#if (MCU_INITCHECK_API == STD_ON)
#define MCU_PMSWCR5_INITCHECK_MASK (MCU_PMSWCR5_MASK ^ \
((uint32)IFX_PMS_PMSWCR5_BPTRISTREQ_MSK << IFX_PMS_PMSWCR5_BPTRISTREQ_OFF))
#endif

/* Mcu driver state definition */
#define MCU_DRIVER_INITIALIZED ((uint32)1U)

#if (MCU_INITCHECK_API == STD_ON)
#define MCU_PMSWCR1_VAL_MSK       ((uint32)0x7F001700U)

#if (MCU_INIT_CLOCK_API == STD_ON)
#define MCU_PERPLLCON_DEFAULT_VAL ((uint32)0x00003E00U)
#endif

#if ((MCU_CCU60_USED == STD_ON) || (MCU_CCU61_USED ==STD_ON))
#define CCU_CLC_MSK               (((uint32)IFX_CCU6_CLC_DISS_MSK << \
(uint32)IFX_CCU6_CLC_DISS_OFF) | ((uint32)IFX_CCU6_CLC_EDIS_MSK << \
(uint32)IFX_CCU6_CLC_EDIS_OFF))
#endif

#if ((MCU_GPT1_USED == STD_ON) || (MCU_GPT2_USED == STD_ON))
#define GPT12_CLC_MSK             (((uint32)IFX_GPT12_CLC_DISS_MSK << \
(uint32)IFX_GPT12_CLC_DISS_OFF) | ((uint32)IFX_GPT12_CLC_EDIS_MSK << \
(uint32)IFX_GPT12_CLC_EDIS_OFF))
#endif
#endif
/*End of #if (MCU_INITCHECK_API == STD_ON)*/

#define MCU_API_SETMODE ((uint8)8U)
#define MCU_API_INITCLOCK ((uint8)2U)

#if (MCU_INIT_CLOCK_API == STD_ON)
/* Bit mask for Divider relevant bit-fields in CCUCON0 register */
#define MCU_CCUCON0_DIV_BIT_MASK    ((uint32)0x0FFFFFFFU)
/* Bit mask for CCUCON1 register (CLKSELxxx) bit-fields reset */
#define MCU_CCUCON1_CLKSEL_RST_MASK ((uint32)0x0F0F0F8F)
/* Bit mask for CCUCON2 register (CLKSELxxx) bit-fields reset */
#define MCU_CCUCON2_CLKSEL_RST_MASK ((uint32)0x07000F0F)

#define MCU_SYSPLLCON_DEFAULT_VAL ((uint32)0x40003A00U)

#endif

/* CCUCON0 lock status timeout value */
#define MCU_CCUCON0_LCK_TIMEOUT ((uint32)1500U)
#if (MCU_INIT_CLOCK_API == STD_ON)
/*CPU will be running at backup clock frequency. Highest possible frequency is
  100 MHz HW recommends a maximum delay of 5 uS. The while loop takes min
  4 instructions. Hence timeout = 4*(1500/100000000) = 60us.
  Higher value is given for safety margin*/
#define MCU_CCUCON12_LCK_TIMEOUT ((uint32)1500U)
#define MCU_PLLPWD_DELAY        ((uint32)1200000U)
#endif
#define MCU_STM_TICK_OVERFLOW   (0xFFFFFFFFU)


/* PLL INSEL clock selection value */
#define MCU_PLL_INSEL_OSCCLK           ((uint32)1U)
#define MCU_PLL_INSEL_BACKUP           ((uint32)0U)
/*
    SW workaround for too low negative resistance in oscillator,
    which leads to higher oscillator frequency stabilization time.
    Measurements suggests 3.5ms, 1.5ms of safety factor is added and
    in total wait for 5ms is implemented.
  */
#if (MCU_INIT_CLOCK_API == STD_ON)
/* Timeout to wait for Oscillator frequency stabilization */
#define MCU_VALIDATE_OSC_FREQ_TIMEOUT  ((uint32)10000U)
#endif


#define PERPLL_DIVBY_ZERO_NUM        ((uint32)10U)
#define PERPLL_DIVBY_ZERO_DEN        ((uint32)16U)
#define PERPLL_DIVBY_ONE_DEN         ((uint32)2U)

#if (MCU_INIT_CLOCK_API == STD_ON)
/* Macro to select Backup clock or Oscillator as PLL input source */
#define MCU_PLL_FBACK_KDIV_MASK      ((uint32)0x0000000FU)
#define MCU_PERPLL_K2DIV_BITPOS_MASK (4U)
#define MCU_PERPLL_K3DIV_BITPOS_MASK (8U)
#endif

/* Macro to select Backup clock or PLL as clock distribution source */
#define MCU_FSOURCE_CLKSEL_BACKUPCLK (0U)

#if (MCU_DISTRIBUTE_PLL_CLOCK_API == STD_ON)
#define MCU_FSOURCE_CLKSEL_PLLCLK (1U)
#endif
/* Timeout for validating the frequency of PLL. Values are given as safety
   margin of x3 from worst possible tick-counts.
   CPU will be running at backup clock frequency. Highest possible frequency
   is 100 MHz i.e. 10 nS per instruction HW recommends a maximum delay of 5 uS.
   The while loop takes min 4 instructions.
   Hence a sufficient timeout with safety margin is provided.
*/
#define MCU_PLL_PWDSTAT_TIMEOUT ((uint32)1000U)
#define MCU_PLL_KDIVRDY_TIMEOUT ((uint32)1000U)
#define MCU_PLL_PMSWCR3_DELAY   ((uint32)250000U)

/* Conversion from microseconds to nanoseconds */
#define MCU_STM_TIMER_COMPU_VAL ((uint32)1000U)

/* Bit masks for reserved bits in SYSPLLCON0 and PERPLLCON0 registers */
#define MCU_SYSPLLCON0_RSRVD_RW_MASK ((uint32)0x000001FBU)
#define MCU_PERPLLCON0_RSRVD_RW_MASK ((uint32)0x000001FEU)

#if (MCU_GTM_USED == STD_ON)
/* GTM module enable and GTM-CMU clock disable */
#define MCU_GTM_MODULE_ENABLE            ((uint32)0U)
#if (MCU_DEINIT_API == STD_ON)
#define MCU_GTM_MODULE_DISABLE           ((uint32)1U)
#endif
#define MCU_GTM_CMU_CLK_DISABLE          ((uint32)0x00555555U)
#if (MCU_DEINIT_API == STD_ON)
#define MCU_GTM_ADC_TRIGOUT_RESET_VAL    (0x0U)

#if (MCU_GTM_TO_DSADC_TRIG_AVAILABLE == STD_ON)
#define MCU_GTM_DSADC_TRIGOUT_RESET_VAL  (0x0U)
#endif

#define MCU_GTM_CMU_GCLK_NUM_RESET_VAL   (0x1U)
#define MCU_GTM_CMU_GCLK_DEN_RESET_VAL   (0x1U)
#define MCU_GTM_CMU_ECLK_NUM_RESET_VAL   (0x1U)
#define MCU_GTM_CMU_ECLK_DEN_RESET_VAL   (0x1U)
#define MCU_GTM_CMU_CLK_CTRL_RESET_VAL   (0x0U)
#define MCU_GTM_CMU_FXCLK_CTRL_RESET_VAL (0x0U)
#endif
/*GTM TBU channel related masks*/
#define MCU_TBU_CH_DISABLE_MASK ((uint32)0x00000055U)
#define MCU_TBU_CH_MASK         ((uint32)0x0000FFFFU)
#define MCU_TBU_CH_0_2_MASK     ((uint32)\
((IFX_GTM_TBU_CH0_CTRL_LOW_RES_MSK << IFX_GTM_TBU_CH0_CTRL_LOW_RES_OFF) | \
(IFX_GTM_TBU_CH0_CTRL_CH_CLK_SRC_MSK << IFX_GTM_TBU_CH0_CTRL_CH_CLK_SRC_OFF)))

#define MCU_TBU_CH_ENABLED      (2U)

#if (MCU_GTM_NO_OF_TBU_CH_AVAILABLE > 0U)
#define MCU_TBU_CH0_OFF (8U)
#define MCU_TBU_CH0_INDEX (0U)
#endif

#if (MCU_GTM_NO_OF_TBU_CH_AVAILABLE > 1U)
#define MCU_TBU_CH1_OFF (12U)
#define MCU_TBU_CH1_INDEX (2U)
#endif

#if (MCU_GTM_NO_OF_TBU_CH_AVAILABLE > 2U)
#define MCU_TBU_CH2_OFF (16U)
#define MCU_TBU_CH2_INDEX (4U)
#endif

#if (MCU_GTM_NO_OF_TBU_CH_AVAILABLE > 3U)
#define MCU_TBU_CH3_OFF (20U)
#define MCU_TBU_CH3_INDEX (6U)
#define MCU_TBU_CH3_MODE_MASK      (((uint32)IFX_GTM_TBU_CH3_CTRL_USE_CH2_MSK)\
 << ((uint32)IFX_GTM_TBU_CH3_CTRL_USE_CH2_OFF))
#endif

#if (MCU_INITCHECK_API == STD_ON)
#define MCU_TBU_CHEN_MSK          ((uint32)0x000000AAU)

#define MCU_GTM_ATOM_TRIG_INITCHK_READ_MSK    (0x0000FFFFU)
#define MCU_GTM_ATOM_RSTCN0_INITCHK_READ_MSK  (0xFFFF0000U)

#define MCU_GTM_TOM_TRIG_INITCHK_READ_MSK  (0x0000FFFFU)
#define MCU_GTM_TOM_RSTCN0_INITCHK_READ_MSK   (0xFFFF0000U)

#define MCU_GTM_ATOM_TRIG_INITCHK_MSK    (0x00005555U)
#define MCU_GTM_ATOM_RSTCN0_INITCHK_MSK  (0x55550000U)

#define MCU_GTM_TOM_TRIG_INITCHK_MSK  (0x00005555U)
#define MCU_GTM_TOM_RSTCN0_INITCHK_MSK   (0x55550000U)

#endif

#if (MCU_DEINIT_API == STD_ON)

#if ((MCU_GTM_NO_OF_TBU_CH_AVAILABLE > 0U)||\
    (MCU_GTM_NO_OF_TBU_CH_AVAILABLE > 1U)||\
    (MCU_GTM_NO_OF_TBU_CH_AVAILABLE > 2U))
#define MCU_TBU_CH0_2_CTRL_RST_VAL (0x0U)
#endif

#if (MCU_GTM_NO_OF_TBU_CH_AVAILABLE > 3U)
#define MCU_TBU_CH3_CTRL_RST_VAL   (0x1U)
#endif

#endif

#define MCU_TBU_CH_MSK              (0x3U)
#define MCU_GTM_CLS_CLK_LEN        (0x2U)
#define MCU_GTM_CLS_CLK_DIV_MSK    (0x3U)

#if (MCU_DEINIT_API == STD_ON)
#define MCU_CCM_CMU_CLK_CFG_RST_VAL   (0x00000000U)
#define MCU_CCM_CMU_FXCLK_CFG_RST_VAL (0x00000000U)
#endif


#if (MCU_DEINIT_API == STD_ON)
#define MCU_ATOM_INT_TRIG_RST_VAL  (0x00005555U)
#define MCU_ATOM_FUPD_CTRL_RST_VAL (0x55550000U)
#define MCU_ATOM_ACT_TB_RST_VAL    (0x00000000U)
#endif


/*GTM - ATOM channel group mask */
#define MCU_GTM_ATOM_AGC_INT_TRIG_MASK ((uint32)\
(((uint32)IFX_GTM_ATOM_AGC_INT_TRIG_INT_TRIG0_MSK << \
(uint32)IFX_GTM_ATOM_AGC_INT_TRIG_INT_TRIG0_OFF) | \
((uint32)IFX_GTM_ATOM_AGC_INT_TRIG_INT_TRIG1_MSK << \
(uint32)IFX_GTM_ATOM_AGC_INT_TRIG_INT_TRIG1_OFF) | \
((uint32)IFX_GTM_ATOM_AGC_INT_TRIG_INT_TRIG2_MSK << \
(uint32)IFX_GTM_ATOM_AGC_INT_TRIG_INT_TRIG2_OFF) | \
((uint32)IFX_GTM_ATOM_AGC_INT_TRIG_INT_TRIG3_MSK << \
(uint32)IFX_GTM_ATOM_AGC_INT_TRIG_INT_TRIG3_OFF) | \
((uint32)IFX_GTM_ATOM_AGC_INT_TRIG_INT_TRIG4_MSK << \
(uint32)IFX_GTM_ATOM_AGC_INT_TRIG_INT_TRIG4_OFF) | \
((uint32)IFX_GTM_ATOM_AGC_INT_TRIG_INT_TRIG5_MSK << \
(uint32)IFX_GTM_ATOM_AGC_INT_TRIG_INT_TRIG5_OFF) | \
((uint32)IFX_GTM_ATOM_AGC_INT_TRIG_INT_TRIG6_MSK << \
(uint32)IFX_GTM_ATOM_AGC_INT_TRIG_INT_TRIG6_OFF) | \
((uint32)IFX_GTM_ATOM_AGC_INT_TRIG_INT_TRIG7_MSK << \
(uint32)IFX_GTM_ATOM_AGC_INT_TRIG_INT_TRIG7_OFF)))

#define MCU_GTM_ATOM_AGC_RST_CN0_MASK  ((uint32)\
(((uint32)IFX_GTM_ATOM_AGC_FUPD_CTRL_RSTCN0_CH0_MSK << \
(uint32)IFX_GTM_ATOM_AGC_FUPD_CTRL_RSTCN0_CH0_OFF) | \
((uint32)IFX_GTM_ATOM_AGC_FUPD_CTRL_RSTCN0_CH1_MSK << \
(uint32)IFX_GTM_ATOM_AGC_FUPD_CTRL_RSTCN0_CH1_OFF) | \
((uint32)IFX_GTM_ATOM_AGC_FUPD_CTRL_RSTCN0_CH2_MSK << \
(uint32)IFX_GTM_ATOM_AGC_FUPD_CTRL_RSTCN0_CH2_OFF) | \
((uint32)IFX_GTM_ATOM_AGC_FUPD_CTRL_RSTCN0_CH3_MSK << \
(uint32)IFX_GTM_ATOM_AGC_FUPD_CTRL_RSTCN0_CH3_OFF) | \
((uint32)IFX_GTM_ATOM_AGC_FUPD_CTRL_RSTCN0_CH4_MSK << \
(uint32)IFX_GTM_ATOM_AGC_FUPD_CTRL_RSTCN0_CH4_OFF) | \
((uint32)IFX_GTM_ATOM_AGC_FUPD_CTRL_RSTCN0_CH5_MSK << \
(uint32)IFX_GTM_ATOM_AGC_FUPD_CTRL_RSTCN0_CH5_OFF) | \
((uint32)IFX_GTM_ATOM_AGC_FUPD_CTRL_RSTCN0_CH6_MSK << \
(uint32)IFX_GTM_ATOM_AGC_FUPD_CTRL_RSTCN0_CH6_OFF) | \
((uint32)IFX_GTM_ATOM_AGC_FUPD_CTRL_RSTCN0_CH7_MSK << \
(uint32)IFX_GTM_ATOM_AGC_FUPD_CTRL_RSTCN0_CH7_OFF)))

#if (MCU_DEINIT_API == STD_ON)
#define MCU_TOM_INT_TRIG_RST_VAL  (0x00005555U)
#define MCU_TOM_FUPD_CTRL_RST_VAL (0x55550000U)
#define MCU_TOM_ACT_TB_RST_VAL    (0x00000000U)
#endif

/*GTM - TOM channel group mask */
#define MCU_GTM_TOM_TGC_INT_TRIG_MASK ((uint32)\
(((uint32)IFX_GTM_TOM_TGC_INT_TRIG_INT_TRIG0_MSK << \
(uint32)IFX_GTM_TOM_TGC_INT_TRIG_INT_TRIG0_OFF) | \
((uint32)IFX_GTM_TOM_TGC_INT_TRIG_INT_TRIG1_MSK << \
(uint32)IFX_GTM_TOM_TGC_INT_TRIG_INT_TRIG1_OFF) | \
((uint32)IFX_GTM_TOM_TGC_INT_TRIG_INT_TRIG2_MSK << \
(uint32)IFX_GTM_TOM_TGC_INT_TRIG_INT_TRIG2_OFF) | \
((uint32)IFX_GTM_TOM_TGC_INT_TRIG_INT_TRIG3_MSK << \
(uint32)IFX_GTM_TOM_TGC_INT_TRIG_INT_TRIG3_OFF) | \
((uint32)IFX_GTM_TOM_TGC_INT_TRIG_INT_TRIG4_MSK << \
(uint32)IFX_GTM_TOM_TGC_INT_TRIG_INT_TRIG4_OFF) | \
((uint32)IFX_GTM_TOM_TGC_INT_TRIG_INT_TRIG5_MSK << \
(uint32)IFX_GTM_TOM_TGC_INT_TRIG_INT_TRIG5_OFF) | \
((uint32)IFX_GTM_TOM_TGC_INT_TRIG_INT_TRIG6_MSK << \
(uint32)IFX_GTM_TOM_TGC_INT_TRIG_INT_TRIG6_OFF) | \
((uint32)IFX_GTM_TOM_TGC_INT_TRIG_INT_TRIG7_MSK << \
(uint32)IFX_GTM_TOM_TGC_INT_TRIG_INT_TRIG7_OFF)))

#define MCU_GTM_TOM_TGC_RST_CN0_MASK  ((uint32) \
(((uint32)IFX_GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH0_MSK << \
(uint32)IFX_GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH0_OFF) | \
((uint32)IFX_GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH1_MSK << \
(uint32)IFX_GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH1_OFF) | \
((uint32)IFX_GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH2_MSK << \
(uint32)IFX_GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH2_OFF) | \
((uint32)IFX_GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH3_MSK << \
(uint32)IFX_GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH3_OFF) | \
((uint32)IFX_GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH4_MSK << \
(uint32)IFX_GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH4_OFF) | \
((uint32)IFX_GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH5_MSK << \
(uint32)IFX_GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH5_OFF) | \
((uint32)IFX_GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH6_MSK << \
(uint32)IFX_GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH6_OFF) | \
((uint32)IFX_GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH7_MSK << \
(uint32)IFX_GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH7_OFF)))

#define MCU_TOM_ACT_TB_TRIG_MSK       \
(((uint32)IFX_GTM_TOM_TGC_ACT_TB_TB_TRIG_MSK \
<< (uint32)IFX_GTM_TOM_TGC_ACT_TB_TB_TRIG_OFF))

#define MCU_ATOM_ACT_TB_TRIG_MSK      \
(((uint32)IFX_GTM_ATOM_AGC_ACT_TB_TB_TRIG_MSK \
<< (uint32)IFX_GTM_ATOM_AGC_ACT_TB_TB_TRIG_OFF))

#if (MCU_INITCHECK_API == STD_ON)
#define GTM_CMU_CLK_EN_CHK_MSK ((uint32)0x00AAAAAAU)
#endif

#endif
/* End of #if (MCU_GTM_USED == STD_ON) */

#if (MCU_GET_RAM_STATE_API == STD_ON)
#define MCU_CSSX_LEN (0x1)
#endif

#if (MCU_INIT_CLOCK_API == STD_ON)
/* Convertor control block module enable */
#define MCU_CONVCTRL_CCCTRL_ENABLE     ((uint32)0xB0000000U)
/* Macro related to read back when safety is enabled */
#if (MCU_SAFETY_ENABLE == STD_ON)
  #define MCU_CONVCTRL_CCCTRL_PDWC_MASK  ((uint32)0xFU)
#endif
#endif

/* Bit mask for reserved bits in CCUCON0 register*/
#define MCU_CCUCON0_RSVD_BIT_MASK ((uint32)0xFFFF7FFFU)

/* Reset related Macros */
/* Mask for possible reset reason values except reserved bits */
#define MCU_RESET_REASON_MASK ((uint32)0x5FFD07FBU)
/* Reset Status types of MCU needed for internal use in a raw form */
/* Reset reason is undefined. */
#define MCU_RAW_RESET_UNDEFINED ((Mcu_RawResetType)(0xFFFFFFFFU))
/* ESR0 reset */
#define MCU_RAW_ESR0_RESET      ((Mcu_RawResetType)(0x00000001U))
/* ESR1 reset */
#define MCU_RAW_ESR1_RESET      ((Mcu_RawResetType)(0x00000002U))
/* SMU reset */
#define MCU_RAW_SMU_RESET       ((Mcu_RawResetType)(0x00000008U))
/* Software reset */
#define MCU_RAW_SW_RESET        ((Mcu_RawResetType)(0x00000010U))
/* STM0 Reset*/
#define MCU_RAW_STM0_RESET      ((Mcu_RawResetType)(0x00000020U))

#if (MCAL_NO_OF_CORES > 1U)
/* STM1 Reset*/
#define MCU_RAW_STM1_RESET ((Mcu_RawResetType)(0x00000040U))
#endif

#if (MCAL_NO_OF_CORES > 2U)
/* STM2 Reset*/
#define MCU_RAW_STM2_RESET ((Mcu_RawResetType)(0x00000080U))
#endif

#if (MCAL_NO_OF_CORES > 3U)
/* STM3 Reset*/
#define MCU_RAW_STM3_RESET ((Mcu_RawResetType)(0x00000100U))
#endif

#if (MCAL_NO_OF_CORES > 4U)
/* STM4 Reset*/
#define MCU_RAW_STM4_RESET ((Mcu_RawResetType)(0x00000200U))
#endif

#if (MCAL_NO_OF_CORES > 5U)
/* STM5 Reset*/
#define MCU_RAW_STM5_RESET ((Mcu_RawResetType)(0x00000400U))
#endif

/* Power On reset on battery connect*/
#define MCU_RAW_POWER_ON_RESET_1  ((Mcu_RawResetType)(0x13810000U))
/* Power On reset, Pulling down PORST Line */
#define MCU_RAW_POWER_ON_RESET_2  ((Mcu_RawResetType)(0x00010000U))
/*Cerberus System Reset*/
#define MCU_RAW_CB0_RESET         ((Mcu_RawResetType)(0x00040000U))
/*Cerberus Debug Reset*/
#define MCU_RAW_CB1_RESET         ((Mcu_RawResetType)(0x00080000U))
/*Cerberus Application Reset*/
#define MCU_RAW_CB3_RESET         ((Mcu_RawResetType)(0x00100000U))
/* EVRC Reset*/
#define MCU_RAW_EVRC_RESET        ((Mcu_RawResetType)(0x00810000U))
/* EVR33 Reset*/
#define MCU_RAW_EVR33_RESET       ((Mcu_RawResetType)(0x01010000U))
/* Supply Watchdog Reset*/
#define MCU_RAW_SUPPLY_WDOG_RESET ((Mcu_RawResetType)(0x02010000U))
/* Standby Regulator Watchdog Reset*/
#define MCU_RAW_STBYR_RESET       ((Mcu_RawResetType)(0x10010000U))
/* LBIST Reset*/
#define MCU_RAW_LBIST_RESET       ((Mcu_RawResetType)(0x40000000U))

#if (MCU_PERFORM_RESET_API == STD_ON)
/* Used for the delay after performing reset */
#define MCU_PERFORM_RESET_DELAY ((uint32)150000000U)
#endif

/* Mode identification and Mode request values */
#define MCU_INDIVIDUAL_CORE_IDLE_MODE ((uint8)0x00U)
#define MCU_UNANIMOUS_SEL_SYSTEM_MODE ((uint8)0x07U)
#define MCU_IDLE_MODE_REQ_VAL         ((uint32)1U)
#define MCU_SLEEP_MODE_REQ_VAL        ((uint32)2U)
#define MCU_STANDBY_MODE_REQ_VAL      ((uint32)3U)

#if (MCU_DEINIT_API == STD_ON)
#define MCU_DRIVER_UNINITIALIZED ((uint32)0U)
/* Reset value of Power Management and reset registers - used in DeInit API */
#define MCU_PMSWCR0_DEINIT_VALUE ((uint32)0x001002D0U)
/* STBYEVEN bit is made 1 for update of STBYEV bits*/
#define MCU_PMSWCR1_DEINIT_VALUE ((uint32)0x09000000U)
#define MCU_PMSWCR3_DEINIT_VALUE ((uint32)0x00000000U)
#define MCU_PMSWCR5_DEINIT_VALUE ((uint32)0x00000001U)
#define MCU_RSTCON_DEINIT_VALUE  ((uint32)0x00000282U)
#define MCU_ARSTDIS_DEINIT_VALUE ((uint32)0U)
#define MCU_EVRUVMON_DEINIT_VALUE ((uint32)0x007500B8U)
#define MCU_EVRMONCTRL_DEINIT_VALUE ((uint32)0x00200020U)
#endif

#if (MCU_LOW_POWER_MODE_API == STD_ON)
#if (MCU_IDLE_MODE_CORE != MCU_IDLE_CORE_NOT_DEFINED)
/* Each CPU can choose to trigger idle mode */
#define MCU_CPU_INIDIVIDUAL_UNANIMOUS ((uint32)0xFFFFFFFFU)
#endif

/* Bit mask for reserved bits in PMS_PMSWSTATCLR register */
#define MCU_PMS_WAKEUP_CAUSE_CLR_MASK ((uint32)0xF001EFFFU)
/* CPU - reserved state values */
#define MCU_CPU_MODE_RESERVED1 ((uint32)0x00000005U)
#define MCU_CPU_MODE_RESERVED2 ((uint32)0x00000007U)
#define MCU_CPU_MODE_RESERVED3 ((uint32)0x00000000U)
#define WAKEUP_CAUSE_INVALID   ((uint32)0xFFFFFFFFU)

#endif

#if (MCU_TRAP_API == STD_ON)
#define TRAP_CAUSE_INVALID    ((uint32)0xFFFFFFFFU)
#define MCU_TRAP_CLR          (0x1)
#define SCU_TRAPCLR_ESR0T_LEN (0x1)
#endif

#if (MCU_CPU_CCUCON_UPDATE_API == STD_ON)
#define MCU_CPU_CCUCON_BASE_ADDR ((volatile uint32 *)&SCU_CCUCON6)
#define MCU_CPU_CCUCON_MAXVAL    ((uint32)0x3FU)
#endif

/* Macros related to GPT12 timer */
#if ((MCU_GPT1_USED == STD_ON) || (MCU_GPT2_USED == STD_ON))
#define GPT12_TIMER_ENABLE       (0x0)
#define GPT12_TIMER_CLK_ENABLED  (0x0U)

#if (MCU_DEINIT_API == STD_ON)
#define GPT12_TIMER_DISABLE      (0x1)
#define GPT12_TIMER_CLK_DISABLED (0x1U)
#endif

#define GPT12_TXCON_RESET_VAL     (0x0U)

#if (MCU_INITCHECK_API == STD_ON)
#define GPT12_TXCON_INITCHECK_MSK (0xFFFFE7FFU)
#endif
#endif

/* Macros related to CCU6 kernel */
#if (MCU_CCU60_USED == STD_ON) || (MCU_CCU61_USED == STD_ON)
#define CCU6_KERNEL_ENABLE       (0U)
#define CCU6_KERNEL_CLK_ENABLED  (0x0U)
#define CCU6_INTERRUPT_FLAG_CLR  (0x0000F7FFU)

#if (MCU_DEINIT_API == STD_ON)
#define CCU6_KERNEL_DISABLE      (1U)
#define CCU6_KERNEL_CLK_DISABLED (0x1U)
#endif

#if (MCU_INITCHECK_API == STD_ON)
#define CCU6_IS_MSK              (0x0000F7FFU)
#endif
#endif


#define CONVERTER_KERNEL_ENABLE       (0x0)
#define CONVERTER_KERNEL_CLK_ENABLED  (0x0U)
#if (MCU_DEINIT_API == STD_ON)
#define CONVERTER_KERNEL_DISABLE      (0x1)
#define CONVERTER_KERNEL_CLK_DISABLED (0x1U)
#endif


/* User Mode related macros */
/*[cover parentID={1A65EADD-AFD0-4845-B2D2-8257E086DD67}]*/
#if (MCU_INIT_DEINIT_API_MODE == MCU_MCAL_SUPERVISOR)
/* Library APIs  */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'MCU_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define MCU_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(RegAdd, Data) \
    Mcal_WritePeripEndInitProtReg(RegAdd, Data)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(RegAdd, Data) \
    Mcal_WriteSafetyEndInitProtReg(RegAdd, Data)

#if ((MCU_INIT_CLOCK_API == STD_ON) || (MCU_GPT1_USED == STD_ON) || \
    (MCU_GPT2_USED == STD_ON))
/* Supervisory mode registers */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'MCU_SFR_INIT_DEINIT_WRITE32'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define MCU_SFR_INIT_DEINIT_WRITE32(reg, value) \
    ((*(reg)) = (uint32)(value));
#endif
#else

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
* 'MCU_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG'
* defined for User mode support in code.
* No side effects foreseen by violating this MISRA rule. */
#define MCU_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(RegAdd, Data) \
    MCAL_LIB_WRITEPERIPENDINITPROTREG(RegAdd, Data)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
* 'MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG'
* defined for User mode support in code.
* No side effects foreseen by violating this MISRA rule. */
#define MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(RegAdd, Data) \
    MCAL_LIB_WRITESAFETYENDINITPROTREG(RegAdd, Data)

#if ((MCU_INIT_CLOCK_API == STD_ON) || (MCU_GPT1_USED == STD_ON) || \
    (MCU_GPT2_USED == STD_ON))
/* Supervisory mode registers */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
* 'MCU_SFR_INIT_DEINIT_WRITE32'
* defined for User mode support in code.
* No side effects foreseen by violating this MISRA rule. */
#define MCU_SFR_INIT_DEINIT_WRITE32(reg, value) \
    MCAL_SFR_OS_WRITE32(MCU_MODULE_ID, reg, value)
#endif
#endif

#if (MCU_RUNTIME_API_MODE == MCU_MCAL_SUPERVISOR)
/* Library APIs  */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'MCU_LIB_RUNTIME_WRITECPUENDINITPROTREG'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define MCU_LIB_RUNTIME_WRITECPUENDINITPROTREG(RegAdd, Data) \
  Mcal_WriteCpuEndInitProtReg(RegAdd, Data)

#if ((MCU_PERFORM_RESET_API == STD_ON) || \
    (MCU_CLR_COLD_RESET_STAT_API == STD_ON) || (MCU_TRAP_API == STD_ON))
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'MCU_LIB_RUNTIME_WRITEPERIPENDINITPROTREG'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define MCU_LIB_RUNTIME_WRITEPERIPENDINITPROTREG(RegAdd, Data) \
  Mcal_WritePeripEndInitProtReg(RegAdd, Data)
#endif
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'MCU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define MCU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG(RegAdd, Data) \
  Mcal_WriteSafetyEndInitProtReg(RegAdd, Data)

#else
/* Library APIs  */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'MCU_LIB_RUNTIME_WRITECPUENDINITPROTREG'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define MCU_LIB_RUNTIME_WRITECPUENDINITPROTREG(RegAdd, Data) \
  MCAL_LIB_WRITECPUENDINITPROTREG(RegAdd, Data)

#if ((MCU_PERFORM_RESET_API == STD_ON) || \
    (MCU_CLR_COLD_RESET_STAT_API == STD_ON) || (MCU_TRAP_API == STD_ON))
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'MCU_LIB_RUNTIME_WRITEPERIPENDINITPROTREG'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define MCU_LIB_RUNTIME_WRITEPERIPENDINITPROTREG(RegAdd, Data) \
  MCAL_LIB_WRITEPERIPENDINITPROTREG(RegAdd, Data)
#endif

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'MCU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define MCU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG(RegAdd, Data) \
  MCAL_LIB_WRITESAFETYENDINITPROTREG(RegAdd, Data)
#endif
/* End of #if (MCU_RUNTIME_API_MODE == MCU_MCAL_SUPERVISOR) */
/*[/cover]*/
/*[/cover]*/
/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}][/cover]*/
/*[cover parentID={64F85676-14B5-4fd8-BC46-F4B276E05AC6}][/cover]*/
/*[cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}][/cover]*/
#define MCU_START_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}][/cover]*/
/*[cover parentID={4E3D9856-2420-4bc0-8E39-B0F93F3DC39E}][/cover]*/
#include "Mcu_MemMap.h"

LOCAL_INLINE void Mcu_lSetIdleMode(const uint8 CoreId);
LOCAL_INLINE void Mcu_lSetSleepMode(const uint8 CoreId);
LOCAL_INLINE void Mcu_lSetStandbyMode(const uint8 CoreId);
#if ((MCU_DEV_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
static void Mcu_lReportError(const uint8 ApiId,
                             const uint8 ErrorId);
#endif

#if ((MCU_MULTICORE_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
static void Mcu_lReportMultiCoreError(const uint8 ApiId,
                                      const uint8 ErrorId);
#endif

#if (MCU_LOW_POWER_MODE_API == STD_ON)
LOCAL_INLINE uint32 Mcu_lGetCpuMode(const uint32 CoreId);
#endif

LOCAL_INLINE void Mcu_lPerPllToBackUpClockFreq(const uint8 ApiId);
LOCAL_INLINE Std_ReturnType Mcu_lSwitchToBackUpClockFreq(
  const uint8 ApiId,
  const Mcu_ClockType ClockSettingIndex);
LOCAL_INLINE Std_ReturnType Mcu_lCcuconLckChk(const uint8 ApiId);
LOCAL_INLINE Mcu_ResetType Mcu_lGetRstReason(const Mcu_RawResetType
    RstReasonRaw);
LOCAL_INLINE Mcu_ResetType Mcu_lGetRstReason2(const Mcu_RawResetType
    RstReasonRaw);
LOCAL_INLINE Std_ReturnType Mcu_lEnableClockControl(void);
#if (MCU_INIT_CLOCK_API == STD_ON)
LOCAL_INLINE Std_ReturnType Mcu_lInitOscClock(void);
LOCAL_INLINE Std_ReturnType Mcu_lInitPllClock(void);
LOCAL_INLINE Std_ReturnType Mcu_lInitPllKDivCheck(void);
LOCAL_INLINE Std_ReturnType Mcu_lInitClockTree(void);
LOCAL_INLINE Std_ReturnType Mcu_lInitCcuCon12(void);
LOCAL_INLINE void Mcu_lInitCcuConCpuReg(void);
#endif

#if (MCU_DISTRIBUTE_PLL_CLOCK_API == STD_ON)
LOCAL_INLINE Std_ReturnType Mcu_lSwitchToDesiredFreq(void);
LOCAL_INLINE void Mcu_lPerPllToDesiredFreq(void);
#endif

#if (MCU_GTM_USED == STD_ON)
LOCAL_INLINE void Mcu_lGtmCmuGlobalInit(void);
LOCAL_INLINE void Mcu_lGtmTriggerInit(void);
LOCAL_INLINE void Mcu_lGtmToutSelInit(void);
LOCAL_INLINE void Mcu_lGtmTimInselInit(void);
LOCAL_INLINE void Mcu_lGtmTbuGlobalInit(void);
LOCAL_INLINE void Mcu_lGtmCcmGlobalInit(void);
LOCAL_INLINE void Mcu_lGtmAtomGlobalInit(void);
LOCAL_INLINE void Mcu_lGtmTomGlobalInit(void);
LOCAL_INLINE Std_ReturnType Mcu_lGtmGlobalInit(void);

#if (MCU_INITCHECK_API == STD_ON)
LOCAL_INLINE Std_ReturnType Mcu_lGtmGlobalInitCheck(void);
LOCAL_INLINE Std_ReturnType Mcu_lGtmCmuGlobalInitCheck(void);
LOCAL_INLINE Std_ReturnType Mcu_lGtmTriggerInitCheck(void);
LOCAL_INLINE Std_ReturnType Mcu_lGtmToutSelInitCheck(void);
LOCAL_INLINE Std_ReturnType Mcu_lGtmTimInselInitCheck(void);
LOCAL_INLINE Std_ReturnType Mcu_lGtmCcmGlobalInitCheck(void);
LOCAL_INLINE Std_ReturnType Mcu_lGtmAtomGlobalInitCheck(void);
LOCAL_INLINE Std_ReturnType Mcu_lGtmTomGlobalInitCheck(void);
#endif
/* End of #if (MCU_INITCHECK_API == STD_ON) */

#if (MCU_DEINIT_API == STD_ON)
LOCAL_INLINE void Mcu_lGtmCmuGlobalDeInit(void);
LOCAL_INLINE void Mcu_lGtmTriggerDeInit(void);
LOCAL_INLINE void Mcu_lGtmTbuGlobalDeInit(void);
LOCAL_INLINE void Mcu_lGtmToutSelDeInit(void);
LOCAL_INLINE void Mcu_lGtmTimInselDeInit(void);
LOCAL_INLINE void Mcu_lGtmCcmGlobalDeInit(void);
LOCAL_INLINE void Mcu_lGtmAtomGlobalDeInit(void);
LOCAL_INLINE void Mcu_lGtmTomGlobalDeInit(void);
LOCAL_INLINE Std_ReturnType Mcu_lGtmGlobalDeInit(void);
#endif
/* End of #if (MCU_DEINIT_API == STD_ON) */

#endif
/* End of #if (MCU_GTM_USED == STD_ON) */
#if (MCU_INITCHECK_API == STD_ON)
LOCAL_INLINE Std_ReturnType Mcu_lLpmInitCheck(void);
#endif

#if ((MCU_GPT1_USED == STD_ON) || (MCU_GPT2_USED == STD_ON))
LOCAL_INLINE Std_ReturnType Mcu_lGpt12Init(void);
#endif
#if (MCU_CCU60_USED == STD_ON) || (MCU_CCU61_USED == STD_ON)
LOCAL_INLINE Std_ReturnType Mcu_lCcu6Init(void);
#endif
LOCAL_INLINE Std_ReturnType Mcu_lConvCtrlInit(void);
LOCAL_INLINE void Mcu_lWriteTrapDisReg(void);
LOCAL_INLINE void Mcu_lSetCpuMode(const uint32 CoreId, const uint32 ModeReq);
#if (MCU_DEINIT_API == STD_ON)
#if ((MCU_GPT1_USED == STD_ON) || (MCU_GPT2_USED == STD_ON))
LOCAL_INLINE Std_ReturnType Mcu_lGpt12DeInit(void);
#endif
#if (MCU_CCU60_USED == STD_ON) || (MCU_CCU61_USED == STD_ON)
LOCAL_INLINE Std_ReturnType Mcu_lCcu6DeInit(void);
#endif
LOCAL_INLINE Std_ReturnType Mcu_lConvCtrlDeInit(void);
LOCAL_INLINE void Mcu_lResetTrapDisReg(void);
#endif
/* End of #if (MCU_DEINIT_API == STD_ON) */

#if (MCU_INIT_CLOCK_API == STD_ON)
#if ((MCU_DEV_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
LOCAL_INLINE Std_ReturnType Mcu_lInitClockDetCheck
(const Mcu_ClockType ClockSetting);
#endif
#endif
/* End of #if (MCU_INIT_CLOCK_API == STD_ON) */


#if (MCU_E_ERR_DEM_REPORTING == STD_ON)
static void Mcu_lReportDemError
(
const Dem_EventIdType EventId,
const Dem_EventStatusType EventStatus
);
#endif


#define MCU_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Mcu_MemMap.h"

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
#define MCU_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Mcu_MemMap.h"

/* Variable to store the Mcu driver configuration pointer */
static const Mcu_ConfigType *Mcu_ConfigPtr;
/* Variable to store the Mcu clock setting id used in Mcu_InitClock() */
static Mcu_ClockType Mcu_ClockSetting;
/* Variable to store the reset status */
static Mcu_RawResetType Mcu_ResetStatusVal;
/* Variable to store the Mcu driver status */
static uint32 Mcu_DriverState;

#define MCU_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Mcu_MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}][/cover]*/
#define MCU_START_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Mcu_MemMap.h"
/*******************************************************************************
** Traceability    :  [cover parentID={20742399-F8FA-4d00-AC98-FF35779EC992}] **
**                                                                            **
** Syntax          :  void Mcu_Init(const Mcu_ConfigType* const ConfigPtr)    **
**                                                                            **
** Description     : This API initializes the MCU driver, and other APIs can  **
**                   be used only after driver initialization is completed.   **
**                   It also performs the configuration for power management, **
**                   reset settings, clock settings, trap settings and        **
**                   GTM global settings                                      **
**                                                                            **
** Service ID      : 0x00                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : ConfigPtr - Pointer to configuration set                 **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={E9E7877F-B957-480b-9D6D-10CC6AE0AA86}][/cover]*/
/*[cover parentID={03618BDC-C1C3-43eb-A2DA-6022929F2B11}][/cover]*/
void Mcu_Init(const Mcu_ConfigType *const ConfigPtr)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_PMSWCR1 Pmswcr1Val;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_PMTRCSR0 Pmtrcsr0Val;
  #if (MCU_CLR_COLD_RESET_STAT_API == STD_OFF)
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_RSTCON2 Rstcon2Val;
  #endif
  volatile uint32 TempVal;
  uint32 Pmswcr5Val;
  uint32 EvruvmonVal;
  uint32 EvrmonCtrlVal;

  Std_ReturnType ClcError = (Std_ReturnType)E_OK;

  /*
    Development Error Check: (only if Development Error Detection is ON)
    1. Check input pointer parameter for invalid (NULL) value and report DET
       Error
    2. Check Mcu Driver is already initialized and report DET Error
  */
  /* [cover parentID={0D5EBB68-9D26-4838-ACA0-802A940F6E30}]
   If Development Error Trace OR Safety is ON
   [/cover] */
  /*[cover parentID={1E40EFA7-C89D-4154-9017-EF776DA0BB87}]*/
  /* [cover parentID={1E40EFA7-C89D-4154-9017-EF776DA0BB87}]
    * Check for DETs */
  #if ((MCU_DEV_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
  uint32 ErrorFlag = MCU_ERR_NOT_FOUND;
  /* [cover parentID={4C12E6E3-4FBE-4af5-89DE-9D78CB03428B}]
   If Multicore is ON
   [/cover] */
  #if ((MCU_MULTICORE_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
  uint32 CoreId = Mcal_GetCpuIndex();
  if (MCAL_MASTER_COREID != CoreId)
  {
    /* [cover parentID={E10C71C1-CB79-44f6-99F5-1E294C064F4A}]
    Report Error
    [/cover] */
    Mcu_lReportMultiCoreError(MCU_SID_INIT, MCU_E_CORE_MISMATCH);
    ErrorFlag = MCU_ERR_FOUND;
  }
  else
  #endif
  {
    /* [cover parentID={3295E621-4F7B-4ffa-A54C-F9D47C7BBB8F}]
     Is Configuration Pointer NULL
     [/cover] */
    if (NULL_PTR == ConfigPtr)
    {
      /* [cover parentID={B83A982F-D6D7-4528-B953-5D7515B4127F}]
      Report Error
      [/cover] */
      Mcu_lReportError(MCU_SID_INIT, MCU_E_PARAM_CONFIG);
      ErrorFlag = MCU_ERR_FOUND;
    }
    else
    {
      /* [cover parentID={FAFE400F-9873-4822-A3A0-AA90FB6AA20E}]
       *  Is Mcu Driver already initialized
       * [/cover] */
      if (MCU_DRIVER_INITIALIZED == Mcu_DriverState)
      {
        /* [cover parentID={D3770F14-F689-4025-8D17-935B8F2000E2}]
        Report Error
        [/cover] */
        Mcu_lReportError(MCU_SID_INIT, MCU_E_INIT_FAILED);
        ErrorFlag = MCU_ERR_FOUND;
      }
    }
  }
  /*[/cover]*/
  /* [cover parentID={7E57EE28-51B2-4135-86FF-51A33B91F6BC}]
   *  Did any DET occur*/
  if (MCU_ERR_FOUND != ErrorFlag)
    /*[/cover] */
  #endif
    /*[/cover] */
  {
    /*
      Power Management and Reset Initialization
      1. Create local copy of configuration pointer (local copy is used in
         all relevant APIs).
      2. Save reset status register content. Used in Mcu_GetResetReason() and
         Mcu_GetResetRawValue() APIs
      3. Configure reset settings.
      4. Setup up Idle and System mode invocation core ID settings.
      5. Setup Idle request acknowledgment and standby setting.
    */

    Mcu_ConfigPtr = ConfigPtr;

    #if (MCU_CLR_COLD_RESET_STAT_API == STD_OFF)
    /* Read the reset status only if has not been cleared */
    /* [cover parentID={17F6A73E-4B74-4e70-9A33-F406D91617D5}]
     *  Is Reset status not zero [/cover]*/
    if (SCU_RSTSTAT.U != 0x0U)
    #endif
    {
      Mcu_ResetStatusVal = SCU_RSTSTAT.U;
    }
    /* [cover parentID={7CC2592A-133B-4889-896F-48FF8497EF97}]
         *  If Clear cold reset status API is OFF*/
    #if (MCU_CLR_COLD_RESET_STAT_API == STD_OFF)
    /* If Mcu_ClearColdReset API is disabled then clear reset status in Init*/
    /* [cover parentID={35E1DDDF-0CD9-46cc-B67F-7F5885D92388}]
     * Clear Reset status
     * [/cover] */
    Rstcon2Val.U = SCU_RSTCON2.U;
    Rstcon2Val.B.CLRC = 0x1U;

    MCU_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(&SCU_RSTCON2.U,
        (uint32)(Rstcon2Val.U));
    #endif

    Pmswcr1Val.U = SCU_PMSWCR1.U;
    /* [cover parentID={CAD00C3D-D089-4200-BCE5-785FD2BC0B4E}]
     * If Idle mode Core is defined*/
    #if (MCU_IDLE_MODE_CORE != MCU_IDLE_CORE_NOT_DEFINED)
    Pmswcr1Val.B.CPUIDLSEL = MCU_IDLE_MODE_CORE;
    #endif
    /*[/cover] */
    /* [cover parentID={0567AB83-A316-45fc-A354-C08FC0D03C88}]
     * If System mode Core is defined*/
    #if (MCU_SYSTEM_MODE_CORE != MCU_SYSTEM_CORE_NOT_DEFINED)
    Pmswcr1Val.B.CPUSEL = MCU_SYSTEM_MODE_CORE;
    Pmswcr1Val.B.STBYEV = MCU_STANDBY_MODE_ENTRY;
    Pmswcr1Val.B.STBYEVEN = 0x1U;
    #endif
    /* [/cover] */
    /*[/cover] */
    MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_RSTCON.U,
        Mcu_ConfigPtr->McuResetCfg);

    MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_PMSWCR1.U,
        (uint32)Pmswcr1Val.U);

    /*
      If low-power standby configuration is available, configure
      power management for low power mode standby settings.
    */
    /* [cover parentID={6EC884CA-E99F-4dba-A9D7-3C1C50B106D8}]
     * Is LPM Configuration available
     * [/cover] */
    if ((((uint32)Mcu_ConfigPtr->McuLowPowerModeCfgPtr->MaxModeEvrcCtrl
          .McuMode) &
         (0x1U << MCU_STANDBY)) > 0x0U)
    {
      MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&PMS_PMSWCR0.U,
          Mcu_ConfigPtr->McuLowPowerModeCfgPtr->Pmswcr0);

      Pmswcr5Val = PMS_PMSWCR5.U & (~MCU_PMSWCR5_MASK);
      Pmswcr5Val |= (Mcu_ConfigPtr->McuLowPowerModeCfgPtr->Pmswcr5 & MCU_PMSWCR5_MASK);
      MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&PMS_PMSWCR5.U, Pmswcr5Val);

      /*[cover parentID={374F2C73-7F5B-40c8-8AA8-C728B8EE6236}]*/
      EvruvmonVal = PMS_EVRUVMON.U & (~MCU_PMS_EVRUVMON_MASK);
      EvruvmonVal |= (Mcu_ConfigPtr->McuLowPowerModeCfgPtr->Evruvmon & MCU_PMS_EVRUVMON_MASK);
      MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&PMS_EVRUVMON.U, EvruvmonVal);

      EvrmonCtrlVal = PMS_EVRMONCTRL.U & (~MCU_PMS_EVRMONCTRL_MASK);
      EvrmonCtrlVal |= (Mcu_ConfigPtr->McuLowPowerModeCfgPtr->EvrmonCtrl & MCU_PMS_EVRMONCTRL_MASK);
      MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&PMS_EVRMONCTRL.U, EvrmonCtrlVal);
      /*[/cover]*/
    }
    /* [cover parentID={8034AAF1-C460-49a5-853C-FCCDCA80BEFE}]
     *  Check for EVRC configuration
     * [/cover] */
    if ((((uint32)Mcu_ConfigPtr->McuLowPowerModeCfgPtr->MaxModeEvrcCtrl
          .McuMode) &
         ((uint32)0x1U << MCU_SLEEP)) > 0x0U)
    {
      /* configure EVRC low power mode setting on sleep request */
      Pmtrcsr0Val.U = SCU_PMTRCSR0.U;
      Pmtrcsr0Val.B.LPSLPEN = Mcu_ConfigPtr->
                              McuLowPowerModeCfgPtr->
                              MaxModeEvrcCtrl.EvrcLowPowerMode;

      MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_PMTRCSR0.U,
          (uint32)Pmtrcsr0Val.U);
    }
    /*
     * TRAP and RESET related configurations.
     */
    /* Configure Application reset disable and Trap settings */

    MCU_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(&SCU_ARSTDIS.U,
        Mcu_ConfigPtr->McuArstDisCfg);
    /* [cover parentID={298B2E2E-33EF-4698-8858-8304635C55ED}]
     * Configure Traps
     * [/cover] */
    Mcu_lWriteTrapDisReg();
    /* Configure global ERU filter settings */
    /* [cover parentID={7AB9F715-5C50-46fb-93A9-3870F803A47C}]
     * [/cover] */
    MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_EIFILT.U,
        Mcu_ConfigPtr->
        McuEruEiFiltCfg);
    /* Initialize McalLib tick resolution */
    TempVal = Mcal_DelayResetTickCalibration();
    UNUSED_PARAMETER(TempVal);

    /* GTM, CCU6, GPT12 and ConverControl Clock enabling */
    ClcError = Mcu_lEnableClockControl();
    /* [cover parentID={36B31CFB-E63D-42f7-A290-F18ABEEE5067},
     * {083E2934-657E-40d3-8A19-E6EDE53387C2}]
     *  Is Converter Control initialization successful
     * [/cover] */
    if (ClcError == (Std_ReturnType)E_OK)
    {
      /*[cover parentID={A84FAB89-437B-42da-837C-53DC941DDBB1}][/cover]*/
      Mcu_DriverState = MCU_DRIVER_INITIALIZED;
    }
  }
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
} /* End of Mcu_Init () */

#if (MCU_DEINIT_API == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID={FB26E537-E48D-410e-B4C6-1FBBA1B83CE0}]  **
**                                                                            **
** Syntax          : void Mcu_DeInit(void)                                    **
**                                                                            **
** Description     : This API de-initializes the MCU driver. It puts all the  **
**                   resources used by MCU and power management configurations**
                     to reset state. PLL will not be de-initialized by this   **
                     function.                                                **
**                                                                            **
** Service ID      : 0x51                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={E9E7877F-B957-480b-9D6D-10CC6AE0AA86}][/cover]*/
/*[cover parentID={03618BDC-C1C3-43eb-A2DA-6022929F2B11}][/cover]*/
void Mcu_DeInit(void)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_PMTRCSR0 Pmtrcsr0Val;
  uint32 Pmswcr5Val;
  uint32 EvruvmonVal;
  uint32 EvrmonCtrlVal;
  Std_ReturnType ClcError = E_OK;
  /*
    Development Error Check: (only if Development Error Detection is ON)
    1. Check Mcu Driver is not yet initialized and report DET Error
  */
  /* [cover parentID={4E50D277-A1FD-477f-97AB-2D837350F8B4}]
     If Development error Trace OR Safety is ON
     [/cover] */
  /*[cover parentID={FC6EFC3E-74AC-4b74-901D-6678BBC2D7D0}]*/
  #if ((MCU_DEV_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
  uint32 ErrorFlag = MCU_ERR_NOT_FOUND;
  /* [cover parentID={AA601DAB-5F53-4efd-AC5B-1A4642DB8CBF}]
   * If Multicore is ON
   * [/cover] */
  #if ((MCU_MULTICORE_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
  uint32 CoreId = Mcal_GetCpuIndex();
  if (MCAL_MASTER_COREID != CoreId)
  {
    /* [cover parentID={87688516-C1F4-43a6-889F-88DAF28261F8}]
    Report DET
    [/cover] */
    /* [cover parentID={9D9B357A-4CB0-4000-A165-C251CB9F1290}]
    Report Error
    [/cover] */
    Mcu_lReportMultiCoreError(MCU_SID_DEINIT, MCU_E_CORE_MISMATCH);
    ErrorFlag = MCU_ERR_FOUND;
  }
  else
  #endif
  {
    /* [cover parentID={8AB807DE-3335-4838-8B7F-034168988B8E}]
    Is MCU Driver not initialized
    [/cover] */
    if (Mcu_DriverState != MCU_DRIVER_INITIALIZED)
    {
      /* [cover parentID={87688516-C1F4-43a6-889F-88DAF28261F8}]
      Report DET
      [/cover] */
      Mcu_lReportError(MCU_SID_DEINIT, MCU_E_UNINIT);
      ErrorFlag = MCU_ERR_FOUND;
    }
  }
  /*[/cover]*/
  /* [cover parentID={2A8DE3EB-06BE-4bc1-915E-35DCEDFDF0DD}]
    * Did any DET occur
    * [/cover] */
  if (MCU_ERR_FOUND != ErrorFlag)
  #endif
  {
    /*
      Power Management, Reset, GTM and Trap setting reset
      1. De-initialize Mcu driver state.
      2. Restore reset value for power management registers.
      3. Restore reset value for reset control registers.
      4. Restore reset value to Trap control register.
      5. Invalidate local configuration pointer and reset register values.
      6. Disable GTM, CCU6, GPT12 and Convertor Control module
      7. Assign other Mcu driver variables to uninitialized state.
    */
    /* [cover parentID={38DAA759-6146-496d-8399-6D27A8A7CB60}]
    Set Mcu Driver State to De-initialized
    [/cover] */
    Mcu_DriverState = MCU_DRIVER_UNINITIALIZED;

    Mcu_lResetTrapDisReg();

    MCU_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(&SCU_ARSTDIS.U,
        MCU_ARSTDIS_DEINIT_VALUE);

    MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_RSTCON.U,
        MCU_RSTCON_DEINIT_VALUE);

    MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_PMSWCR1.U,
        MCU_PMSWCR1_DEINIT_VALUE);
    /*Reset low power mode settings if low power mode is configured.*/
    /* [cover parentID={292EDB74-E52D-4f8e-800D-F7BB4FDDC68E}]
     * Is Low Power mode configured
     * [/cover] */
    if ((((uint32)Mcu_ConfigPtr->McuLowPowerModeCfgPtr->MaxModeEvrcCtrl
          .McuMode) &
         ((uint32)0x1U << MCU_STANDBY)) > 0x0U)
    {

      MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&PMS_PMSWCR0.U,
          MCU_PMSWCR0_DEINIT_VALUE);

      MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&PMS_PMSWCR3.U,
          MCU_PMSWCR3_DEINIT_VALUE);

      Pmswcr5Val = PMS_PMSWCR5.U & (~MCU_PMSWCR5_MASK);
      Pmswcr5Val |= MCU_PMSWCR5_DEINIT_VALUE;
      MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&PMS_PMSWCR5.U,
          Pmswcr5Val);

      EvruvmonVal = PMS_EVRUVMON.U & (~MCU_PMS_EVRUVMON_MASK);
      EvruvmonVal |= MCU_EVRUVMON_DEINIT_VALUE;
      MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&PMS_EVRUVMON.U,
          EvruvmonVal);

      EvrmonCtrlVal = PMS_EVRMONCTRL.U & (~MCU_PMS_EVRMONCTRL_MASK);
      EvrmonCtrlVal |= MCU_EVRMONCTRL_DEINIT_VALUE;
      MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&PMS_EVRMONCTRL.U,
          EvrmonCtrlVal);
    }

    /* [cover parentID={8CF05707-C21B-473d-9E33-64DAF167CC90}]
     * Is Sleep mode configured
     * [/cover] */
    if ((((uint32)Mcu_ConfigPtr->McuLowPowerModeCfgPtr->
          MaxModeEvrcCtrl.McuMode) & ((uint32)0x1U << MCU_SLEEP)) > 0x0U)
    {

      Pmtrcsr0Val.U = SCU_PMTRCSR0.U;
      Pmtrcsr0Val.B.LPSLPEN = 0x0U;

      MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_PMTRCSR0.U,
          (uint32)Pmtrcsr0Val.U);
    }

    MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_EIFILT.U, 0x0U);
    /* If GTM module is available, perform global GTM de-initialization */
    #if (MCU_GTM_USED == STD_ON)
    /* [cover parentID={E6B236B8-0E81-4c4a-8A89-2E8CA7A47F45}]
    De-Initialize GTM
    [/cover] */
    /* [cover parentID={BE349F69-F208-49d8-8D02-08ECAF7445E0}]
     * Is GTM frequency not zero [/cover] */
    if (SCU_CCUCON0.B.GTMDIV != 0U)
    {
      ClcError = Mcu_lGtmGlobalDeInit();
    }
    /* [cover parentID={28BCDD0C-3179-4edb-ABE6-A07615E49321}]
     * Is GTM de-initialization successful
     * [/cover] */
    if (ClcError == (Std_ReturnType)E_OK)
    #endif
    {
      #if (MCU_CCU60_USED == STD_ON) || (MCU_CCU61_USED == STD_ON)
      /* [cover parentID={F8A00A4E-8446-481a-BEF0-D32901CB1F94}]
      De-initialize CCU6
      [/cover] */
      ClcError = Mcu_lCcu6DeInit();

      /* [cover parentID={428C25B6-118B-4a81-A86A-B6489BC534AA}]
       * Is Ccu6 de-initialization successful
       * [/cover] */
      if (ClcError == (Std_ReturnType)E_OK)
      #endif
      {
        /* [cover parentID={8B68CA64-C318-4dbd-957D-4E113BA5A469}]
        De-Initialize GPT12
        [/cover] */
        #if ((MCU_GPT1_USED == STD_ON) || (MCU_GPT2_USED == STD_ON))
        ClcError = Mcu_lGpt12DeInit();
        /* [cover parentID={C001E3E6-358B-42cb-89AC-79B2B2CC6249}]
         * Is GPT12 de-initialization successful
         * [/cover] */
        if (ClcError == (Std_ReturnType)E_OK)
        #endif
        {
          /* [cover parentID={64A678D3-6A4C-47a9-9A95-F1C5343C214C}]
           De-Initialize Converter Control
           [/cover] */
          ClcError = Mcu_lConvCtrlDeInit();
          /* [cover parentID={869A9B39-AA69-4ffe-9D95-4A5D9DF669B9}]
           * Is Converter Control de-initialization successful
           * [/cover] */
          if (ClcError == (Std_ReturnType)E_OK)
          {
            /* Reset Mcu module global data */
            Mcu_ConfigPtr = NULL_PTR;
          }
        }
      }
    }
  }
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}
#endif

/*******************************************************************************
** Traceability    : [cover parentID={4D72BAD4-4E08-49fb-8A9A-85D291AF2C4A}]  **
**                                                                            **
** Syntax          : Std_ReturnType Mcu_InitRamSection                        **
**                   (                                                        **
**                     const Mcu_RamSectionType  RamSection                   **
**                   )                                                        **
**                                                                            **
** Description     : This function initializes the given RAM section with     **
**                   configured data as per configuration data set.           **
**                                                                            **
** Service ID      : 0x01                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for other RAM sections                         **
**                                                                            **
** Parameters (in) : RamSection - Selects RAM memory section number out of    **
**                   configuration set.                                       **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: RAM successfully initialized                       **
**                   E_NOT_OK: RAM initialization failed                      **
**                   e.g. due to parameter error                              **
**                                                                            **
*******************************************************************************/
/*[cover parentID={E9E7877F-B957-480b-9D6D-10CC6AE0AA86}][/cover]*/
Std_ReturnType Mcu_InitRamSection(const Mcu_RamSectionType RamSection)
{
  Mcu_RamSizeType RamLength;
  Std_ReturnType RetValue = (Std_ReturnType)E_NOT_OK;

  /*
    Development Error Check: (only if Development Error Detection is ON)
    1. Check Mcu Driver is not yet initialized and report DET Error
    2. Check input parameter RamSection is within configured range and report
    DET error.
  */
  /* [cover parentID={F6B6C9DF-8844-4752-B4BC-EC7EC0BE27BC}]
   If Development Error Trace OR Safety is ON
   [/cover] */
  /*[cover parentID=]*/
  #if ((MCU_DEV_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
  uint32 ErrorFlag = MCU_ERR_NOT_FOUND;
  /* [cover parentID={E26C65DD-820C-40b7-8444-699C2A5E92AA}]
    * Is Mcu Driver not initialized
    * [/cover] */
  if (Mcu_DriverState != MCU_DRIVER_INITIALIZED)
  {
    /* [cover parentID={EA0FCDEE-3A31-420e-B229-E1A952506429}]
    Report Error
    [/cover] */
    Mcu_lReportError(MCU_SID_INITRAMSECTION, MCU_E_UNINIT);
    ErrorFlag = MCU_ERR_FOUND;
  }
  else
  {
    /* [cover parentID=]
     * Is value of parameter greater than configured Ram Sections
     * [/cover] */
    if (RamSection >= (Mcu_ConfigPtr->McuNoOfRamCfg))
    {
      /* [cover parentID={9CC3B806-3145-4a15-BFA8-F99613C99812}]
      Report Error
      [/cover] */
      Mcu_lReportError(MCU_SID_INITRAMSECTION, MCU_E_PARAM_RAMSECTION);
      ErrorFlag = MCU_ERR_FOUND;
    }
  }
  /*[/cover]*/
  /*[/cover]*/
  /* [cover parentID={79AE43FD-6215-45a6-B8AB-D01DEEC4C29E}]
   * Did any DET occur
   * [/cover] */
  if (MCU_ERR_FOUND != ErrorFlag)
  #endif
  {
    /* Out of multiple config sets, some config sets may have no ram
       sections defined. Such cases shall be protected against invalid
       pointer access, to avoid memory exception. A NULL_PTR check is
       performed
    */
    /* [cover parentID={847FA821-056D-4a32-AA2A-96BBAC88EFA5}]
     * Is Ram Pointer not Null
     * [/cover] */
    if (NULL_PTR != Mcu_ConfigPtr->McuRamCfgPtr)
    {
      /*
        RAM initialization
        1. Make local copy of Ram location base address pointer, Length of
           ram section and data it shall be initialized with.
        2. Loop through the complete memory section and initialize it with
           configured data.
      */

      #if (MCAL_AR_VERSION == MCAL_AR_440)
      uint32 RamWriteSize;

      RamWriteSize = Mcu_ConfigPtr->McuRamCfgPtr[RamSection].RamWriteSize;

      /*[cover parentID={10C7EA8B-2117-4d22-9DF7-39B87D740ADD}][/cover]*/
      if (MCU_RAM_WRITE_SIZE_HALF_WORD == RamWriteSize)
      {
        uint16 *RamBasePtr;
        uint16 RamData;
        RamBasePtr = (uint16 *)Mcu_ConfigPtr->McuRamCfgPtr[RamSection].
        /* MISRA2012_RULE_11_5_JUSTIFICATION: cast from void pointer to uint16
        pointer is made as ram initialization is performed 2 bytes at once. */
        /* MISRA2012_RULE_11_3_JUSTIFICATION: cast from void pointer to uint16
        pointer is made as ram initialization is performed 2 bytes at once. */
                     RamBaseAdrPtr;
        RamData = (uint16)Mcu_ConfigPtr->McuRamCfgPtr[RamSection].RamData;
        RamLength = Mcu_ConfigPtr->McuRamCfgPtr[RamSection].RamSize
                                               / MCU_RAM_WRITE_SIZE_HALF_WORD;

        /* [cover parentID={D8FD5C74-0894-4b8b-A495-656AC9234249}]
         * Loop through complete memory section
         * [/cover] */
        while (RamLength > (Mcu_RamSizeType)MCU_RAM_SIZE_ZERO)
        {
          *RamBasePtr = RamData;
          RamBasePtr++;
          RamLength--;
        }
      }
      /*[cover parentID={066DE2E2-BD03-458a-B7C4-6BCB8C7EDAA5}][/cover]*/
      else if (MCU_RAM_WRITE_SIZE_WORD == RamWriteSize)
      {
        uint32 *RamBasePtr;
        uint32 RamData;
        RamBasePtr = (uint32 *)Mcu_ConfigPtr->McuRamCfgPtr[RamSection].
        /* MISRA2012_RULE_11_5_JUSTIFICATION: cast from void pointer to uint32
        pointer is made as ram initialization is performed 4 bytes at once. */
        /* MISRA2012_RULE_11_3_JUSTIFICATION: cast from void pointer to uint32
        pointer is made as ram initialization is performed 4 bytes at once. */
                     RamBaseAdrPtr;
        RamData = (uint32)Mcu_ConfigPtr->McuRamCfgPtr[RamSection].RamData;
        RamLength = Mcu_ConfigPtr->McuRamCfgPtr[RamSection].RamSize
                                                    / MCU_RAM_WRITE_SIZE_WORD;

        /* [cover parentID={D8FD5C74-0894-4b8b-A495-656AC9234249}]
         * Loop through complete memory section
         * [/cover] */
        while (RamLength > (Mcu_RamSizeType)MCU_RAM_SIZE_ZERO)
        {
          *RamBasePtr = RamData;
          RamBasePtr++;
          RamLength--;
        }
      }

      else if (MCU_RAM_WRITE_SIZE_DOUBLE_WORD == RamWriteSize)
      {
        uint64 *RamBasePtr;
        uint64 RamData;
        RamBasePtr = (uint64 *)Mcu_ConfigPtr->McuRamCfgPtr[RamSection].
        /* MISRA2012_RULE_11_5_JUSTIFICATION: cast from void pointer to uint64
        pointer is made as ram initialization is performed 8 bytes at once. */
        /* MISRA2012_RULE_11_3_JUSTIFICATION: cast from void pointer to uint64
        pointer is made as ram initialization is performed 8 bytes at once. */
                     RamBaseAdrPtr;
        RamData = Mcu_ConfigPtr->McuRamCfgPtr[RamSection].RamData;
        RamLength = Mcu_ConfigPtr->McuRamCfgPtr[RamSection].RamSize
                                             / MCU_RAM_WRITE_SIZE_DOUBLE_WORD;

        /* [cover parentID={D8FD5C74-0894-4b8b-A495-656AC9234249}]
         * Loop through complete memory section
         * [/cover] */
        while (RamLength > (Mcu_RamSizeType)MCU_RAM_SIZE_ZERO)
        {
          *RamBasePtr = RamData;
          RamBasePtr++;
          RamLength--;
        }
      }

      /*[cover parentID={6EB4CCE6-023A-4e86-8257-F2845602B40B}][/cover]*/
      else
      #endif
      {
        uint8 *RamBasePtr;
        uint8 RamData;
        RamBasePtr = (uint8 *)Mcu_ConfigPtr->McuRamCfgPtr[RamSection].
        /* MISRA2012_RULE_11_5_JUSTIFICATION: cast from void pointer to uint8
           pointer is made as ram initialization is performed byte by byte. */
                     RamBaseAdrPtr;
        RamData = (uint8)Mcu_ConfigPtr->McuRamCfgPtr[RamSection].RamPrstData;
        RamLength = Mcu_ConfigPtr->McuRamCfgPtr[RamSection].RamSize;

        /* [cover parentID={D8FD5C74-0894-4b8b-A495-656AC9234249}]
         * Loop through complete memory section
         * [/cover] */
        while (RamLength > (Mcu_RamSizeType)MCU_RAM_SIZE_ZERO)
        {
          *RamBasePtr = RamData;
          RamBasePtr++;
          RamLength--;
        }
      }
      RetValue = (Std_ReturnType)E_OK;
    }
  }
  /* [cover parentID={416EA724-E7EF-4223-87EA-77C8A508A055}]
   * Return E_NOT_OK
   * [/cover] */
  return RetValue;
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

#if (MCU_INIT_CLOCK_API == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID={D55E83D2-5300-4d48-9BF0-F425F619E87A}]  **
**                                                                            **
** Syntax          : Std_ReturnType Mcu_InitClock                             **
**                   (                                                        **
**                     const Mcu_ClockType  ClockSetting                      **
**                   )                                                        **
**                                                                            **
** Description     : This API initializes the PLLs and other MCU specific     **
**                   clock options. The PLL lock procedure is started (if PLL **
**                   shall be initialized) for system and peripheral PLLs,    **
**                   but the function does not wait until the peripheral PLL  **
**                   is locked                                                **
**                   Note: Mcu_InitClock only initializes the PLL parameters. **
**                         PLL clock will be activated to the MCU distribution**
**                         only after the system PLL is also locked and then  **
**                         Mcu_DistributePllClock shall be called. i.e The    **
**                         sequence to activate PLL clock to the MCU clock    **
**                         distribution is:                                   **
**                         1)Call Mcu_InitClock                               **
**                         2)Call Mcu_GetPllStatus                            **
**                         3)Call Mcu_DistributePllClock                      **
**                                                                            **
** Service ID      : 0x02                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : ClockSetting: Clock setting index                        **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: Clock initialization successful                    **
**                   E_NOT_OK: Clock initialization failed                    **
**                   e.g. due to parameter error                              **
**                                                                            **
*******************************************************************************/
/*[cover parentID={E9E7877F-B957-480b-9D6D-10CC6AE0AA86}][/cover]*/
Std_ReturnType Mcu_InitClock(const Mcu_ClockType ClockSetting)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
    defined to modify certain bits and avoid 32-bit mask value.
    No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_SYSPLLCON0 Syspllcon0Val;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_PERPLLCON0 Perpllcon0Val;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_CONVERTER_PHSCFG ConvCtrlPhscfg;
  #if (MCU_SAFETY_ENABLE == STD_ON)
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_CONVERTER_PHSCFG ReadBack;
  #endif
  uint32 SysPllPwdStat, PerPllPwdStat;
  volatile uint32 ClkselVal, TempVal;
  volatile uint32 TimeoutCtr;
  Std_ReturnType RetValue = E_OK;

  /*
    Development Error Check: (only if Development Error Detection is ON)
    1. Check Mcu Driver is not yet initialized and report DET Error
    2. Check input parameter ClockSetting is within configured range and report
       DET error.
  */
  /* [cover parentID={52A6C0D0-23F2-4071-9681-FFCD9B9B50A9}]
   If Development Error Trace OR Safety is ON
   [/cover] */
  /*[cover parentID={EDB26605-C0A6-431d-9057-B1074E368237}]*/
  #if ((MCU_DEV_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
  RetValue = Mcu_lInitClockDetCheck(ClockSetting);

  /*[/cover] */
  /*[/cover]*/
  /* [cover parentID={21BAC3D6-3EB9-4818-A80B-CF70AA19A782}]
   * Did any DET occur
   * [/cover] */
  if (E_OK == RetValue)
  #endif
  {
    /*
      1. Create module local copy of clock setting index.
      2. If backup clock is selected for distribution source - switch to
         backup clock, otherwise proceed with further steps.
    */
    Mcu_ClockSetting = (uint8)ClockSetting;
    /* [cover parentID={7B053884-4440-4ee8-8D20-59DBCFA881F9}]
     * Is PLL clock selected as distribution source
     * [/cover] */
    if (MCU_FSOURCE_CLKSEL_BACKUPCLK != SCU_CCUCON0.B.CLKSEL)
    {
      /* [cover parentID={D51B3126-F352-4f6c-AC8D-2A68CB2D32E1}]
      * Switch clock tree to Backup clock
      * [/cover] */
      RetValue = Mcu_lSwitchToBackUpClockFreq(MCU_API_INITCLOCK, ClockSetting);
    }

    /* [cover parentID={BDC75F76-4522-4a0b-99F1-54B1A07C3710}]
     * Is Clock switched to Back-up clock successfully
     * [/cover] */
    if ((Std_ReturnType)E_NOT_OK != RetValue)
    {
      ClkselVal = (((Mcu_ConfigPtr->McuClockSettingPtr
                     [Mcu_ClockSetting].PllDistributionCfgPtr->Ccucon0) >>
                    (uint32)IFX_SCU_CCUCON0_CLKSEL_OFF) &
                   (uint32)IFX_SCU_CCUCON0_CLKSEL_MSK);

      /* [cover parentID={EB6ED034-D129-4fce-B0DD-F0E8351A9AB0}]
      * Is PLL used as Clock source in configuration
      * [/cover] */
      if ((uint32)MCU_FSOURCE_CLKSEL_BACKUPCLK != ClkselVal)
      {
        /*
          Preparation for Oscillator initialization
          2. Move the PLLs in power-saving mode to avoid unintended current
             jumps.
          3. Wait (with timeout) until PLLs power-saving mode in not active.
          4. Report Production error in case of timeout error.
        */

        /* Moving PLLs into power-saving mode */
        Syspllcon0Val.U = (uint32)SCU_SYSPLLCON0.U &
                          (~MCU_SYSPLLCON0_RSRVD_RW_MASK);
        Syspllcon0Val.B.PLLPWD = 0x0U;

        Perpllcon0Val.U = (uint32)SCU_PERPLLCON0.U &
                          (~MCU_PERPLLCON0_RSRVD_RW_MASK);
        Perpllcon0Val.B.PLLPWD = 0x0U;


        MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_SYSPLLCON0.U,
            (uint32)Syspllcon0Val.U);

        MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_PERPLLCON0.U,
            (uint32)Perpllcon0Val.U);
        TimeoutCtr = MCU_PLL_PWDSTAT_TIMEOUT;

        SysPllPwdStat = (uint32)SCU_SYSPLLSTAT.B.PWDSTAT;

        PerPllPwdStat = (uint32)SCU_PERPLLSTAT.B.PWDSTAT;

        /* [cover parentID={52485AB2-B942-4b41-8E99-174EB9D0D7E6}]
         * Provide delay to allow PLLs to move to Power saving mode
         * [/cover] */
        while ((TimeoutCtr > 0x0U) && ((0x0U == SysPllPwdStat) ||
                                       (0x0U == PerPllPwdStat)))
        {

          SysPllPwdStat = (uint32)SCU_SYSPLLSTAT.B.PWDSTAT;

          PerPllPwdStat = (uint32)SCU_PERPLLSTAT.B.PWDSTAT;

          TimeoutCtr--;
        }
        /* [cover parentID={89A63ABA-37DB-4c53-B8FA-DC59C7ECF266}]
         * Is System PLL still not in Power saving mode
         * [/cover] */
        if (0x0U == SCU_SYSPLLSTAT.B.PWDSTAT)
        {
          /* [cover parentID={EA8C88BD-C991-480a-8C9C-0757C17EF5DA}]
           * If Production error Reporting is ON
           * [/cover] */
          #if (MCU_E_SYSTEM_PLL_TIMEOUT_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
          /* Report Production error for system PLL error */
          /* [cover parentID={DF1E8931-1FEF-497f-A436-8EB6E3AA1777}]
           * Report System PLL Time-Out Production error
           * [/cover] */
          Mcu_lReportDemError(MCU_E_SYSTEM_PLL_TIMEOUT_ERR,
                                DEM_EVENT_STATUS_FAILED);
          #endif
          RetValue = (Std_ReturnType)E_NOT_OK;
        }
        #if (MCU_E_SYSTEM_PLL_TIMEOUT_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
        else
        {
          /* Report Production error for system PLL passed */
          /* [cover parentID={C0DEBA0E-EDA9-479c-BFDF-7027A13FF9E0}]
           Report Production error Event Passed for System PLL Timeout
          [/cover] */
          Mcu_lReportDemError(MCU_E_SYSTEM_PLL_TIMEOUT_ERR,
                                DEM_EVENT_STATUS_PASSED);
        }
        #endif

        /* [cover parentID={3AE6DAE7-42FD-4046-8232-766AF63266B0}]
         * Is Peripheral PLL still not in Power Saving mode
         * [/cover] */
        if (0x0U == SCU_PERPLLSTAT.B.PWDSTAT)
        {
          /*[cover parentID={61C5F8AA-689A-4f26-9C0E-FA196C1287C2}][/cover]*/
          #if (MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR_DEM_REPORT == \
          MCU_ENABLE_DEM_REPORT)
          /* Report Production error for peripheral PLL error */
          /* [cover parentID={05E8FF43-A772-4ddb-B63F-1798A4240528}]
           Report Peripheral PLL Time-Out DEM
           [/cover] */
          /* [cover parentID={35CA0459-D655-442d-8304-3455D92BFE74}]
           Report Peripheral PLL Time-Out DEM
           [/cover] */
          Mcu_lReportDemError(MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR,
                                DEM_EVENT_STATUS_FAILED);
          #endif
          RetValue = (Std_ReturnType)E_NOT_OK;
        }
        #if (MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR_DEM_REPORT == \
        MCU_ENABLE_DEM_REPORT)
        else
        {
          /* Report Production error for peripheral PLL passed */
          /* [cover parentID={46E5587C-7FA0-4b5e-9058-4040C4B6E533}]
          Report Production error Event Passed for Peripheral PLL Timeout
          [/cover] */
          Mcu_lReportDemError(MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR,
                                DEM_EVENT_STATUS_PASSED);
        }
        #endif

        /* [cover parentID={17878121-134D-48ea-A631-343FB382665F}]
         * Is Power saving mode properly entered
         * [/cover] */
        if ((Std_ReturnType)E_NOT_OK != RetValue)
        {
          /* Setup Oscillator as per configuration */
          /* [cover parentID={C6AD707F-D1D1-4525-9C7D-E8D1D35BD79E}]
           * Setup Oscillator as per configuration
           * [/cover] */
          RetValue = Mcu_lInitOscClock();
        }
        /* Check if Oscillator setup has been successful */
        /* [cover parentID={CBB5EDD3-8D51-4d83-98C5-ED8810A6ED69}]
         * Is Oscillator initialization successful
         * [/cover] */
        if ((Std_ReturnType)E_NOT_OK != RetValue)
        {
          /* Initialize PLLs as per configuration */
          /* [cover parentID={2CFAFDB6-5925-4067-8DEB-0C6460937B58}]
           * Initialize PLLs as per configuration
           * [/cover] */
          RetValue = Mcu_lInitPllClock();
        }
      }

      /* Check PLL initialization and locking successful*/
      /*[cover parentID={9A6F6A43-4BB9-4faa-9913-49E6B9CB5C99}][/cover]*/
      if ((Std_ReturnType)E_NOT_OK != RetValue)
      {
        /*
          Setup converter control block phase configuration.
          1. unlock the PHSCFG register write.
          2. write value and lock the register.
        */

        /* Enable CONVCTRL register update */
        TempVal = CONVCTRL_CCCTRL.U;

        MCU_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(
          &CONVCTRL_CCCTRL.U,
          MCU_CONVCTRL_CCCTRL_ENABLE);

        ConvCtrlPhscfg.U = CONVCTRL_PHSCFG.U;
        ConvCtrlPhscfg.B.PDWC = 0x1U;
        ConvCtrlPhscfg.B.PHSDIV = Mcu_ConfigPtr->McuClockSettingPtr
                                  [Mcu_ClockSetting].ConvCtrlBlockConf;

        /* [cover parentID={9DC52994-9CCB-47a5-B316-B08714190522},
         * {A69EE533-3E00-459c-82CC-2DEC69A19DB0}]
         * Setup converter control block phase configuration
         * [/cover] */
        MCU_SFR_INIT_DEINIT_WRITE32(&CONVCTRL_PHSCFG.U, ConvCtrlPhscfg.U);
        /* Restore CCCTRL register value */
        MCU_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(
          &CONVCTRL_CCCTRL.U,
          TempVal);

        /*[cover parentID={A8C4DA8C-96F8-48e5-95D6-AE5975CAF97E}][/cover]*/
        #if (MCU_SAFETY_ENABLE == STD_ON)
        /* Readback PHSCFG to ensure value has been updated*/
        ReadBack.U = CONVCTRL_PHSCFG.U;
        /* Check if the value has been updated in PHSCFG*/
        /*[cover parentID={1507AC8D-FA89-467a-AFF6-9A369D2EB702}][/cover]*/
        if (ReadBack.U != (ConvCtrlPhscfg.U & MCU_CONVCTRL_CCCTRL_PDWC_MASK))
        {
          /* Report Safety error if PHSCFG is not updated*/
          /*[cover parentID={4CF5C532-2924-4aca-876E-A055C14DE42A}][/cover]*/
          Mcu_lReportError(MCU_SID_INITCLOCK, MCU_E_PHSCFG_UPDATE_ERR);
          RetValue = E_NOT_OK;
        }
        else
        #endif
        {
          /*
            Clock tree divider setup
            1. Setup all the clock divider values.
          */
          /* [cover parentID={C2759930-42C4-4e19-BCE1-E0DE1CA5A2DA}]
           * Configure CPU and other frequencies under clock tree
           * [/cover] */
          RetValue = Mcu_lInitClockTree();
        }
      }
    }
  }
  /*[cover parentID={3EEF5A37-5147-4bea-9A24-A20B918B78C5}][/cover]
    [cover parentID={BFE4DF12-5A92-4ce0-B101-D37FC5A5547B}][/cover]*/
  /* [cover parentID={BFE4DF12-5A92-4ce0-B101-D37FC5A5547B}]
   * [cover parentID={3EEF5A37-5147-4bea-9A24-A20B918B78C5}]
   * Return E_NOT_OK
   * [/cover] */
  return RetValue;
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}
#endif

#if (MCU_DISTRIBUTE_PLL_CLOCK_API == STD_ON)
/*******************************************************************************
** Traceability :  [cover parentID={70A99F93-87ED-476a-9C60-D640686262BC}]    **
**                                                                            **
** Syntax          :  Std_ReturnType Mcu_DistributePllClock( void )           **
**                                                                            **
** Description     : This API selects the PLL clock as source for MCU clock   **
**                   tree distribution. Afterwards, it ramps up/down the clock**
**                   to desired clock frequency as per configuration data set.**
**                                                                            **
** Service ID      : 0x03                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: Clock distribution successful                      **
**                   E_NOT_OK: Clock distribution failed                      **
**                                                                            **
*******************************************************************************/
/*[cover parentID={E9E7877F-B957-480b-9D6D-10CC6AE0AA86}][/cover]*/
Std_ReturnType Mcu_DistributePllClock(void)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_CCUCON0 Ccucon0Val;
  uint32 ClkselVal, TimeoutCtr, Ccucon0Lck;
  Std_ReturnType RetValue = (Std_ReturnType)E_OK;
  uint32 SysPllStat, PerPllStat;
  uint32 ErrorFlag = MCU_ERR_NOT_FOUND;

  /*
    Development Error Check: (only if Development Error Detection is ON)
    1. Check Mcu Driver is not yet initialized and report DET Error.
    2. Check for system PLL lock not yet set, report DET Error.
  */
  /* [cover parentID={70E80C6F-966D-4488-8D37-1152979A2477}]
     If Development Error Trace OR Safety is ON
     [/cover] */
  /*[cover parentID={A77A0962-E868-40df-9F09-74A96D264B72}]*/
  #if ((MCU_DEV_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
  /* [cover parentID={E58353B6-B5EA-485f-B3BC-723938F95810}]
     If Multicore is ON
     [/cover] */
  #if ((MCU_MULTICORE_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
  uint32 CoreId = Mcal_GetCpuIndex();
  if (MCAL_MASTER_COREID != CoreId)
  {
    /* [cover parentID={A23D6D63-00E7-46c8-8183-785397AABCDF}]
     Report Error
     [/cover] */
    Mcu_lReportMultiCoreError(MCU_SID_DISTRIBUTEPLLCLOCK, MCU_E_CORE_MISMATCH);
    ErrorFlag = MCU_ERR_FOUND;
  }
  else
  #endif
  {
    /* [cover parentID={CF572CD4-13DC-4c74-956C-E29DBEA01FDD}]
     * Is Mcu Driver not Initialized
     * [/cover] */
    if (Mcu_DriverState != MCU_DRIVER_INITIALIZED)
    {
      /* [cover parentID={8F6D5D4C-0192-470d-B41A-F31DAF598941}]
       Report Error
         [/cover] */
      /* [cover parentID={8F6D5D4C-0192-470d-B41A-F31DAF598941}]
      Report Error
      [/cover] */
      Mcu_lReportError(MCU_SID_DISTRIBUTEPLLCLOCK, MCU_E_UNINIT);
      ErrorFlag = MCU_ERR_FOUND;
    }
    else
    {
      SysPllStat = (uint32)SCU_SYSPLLSTAT.B.LOCK;
      PerPllStat = (uint32)SCU_PERPLLSTAT.B.LOCK;

      /* [cover parentID={671E7EB1-A618-4f06-B206-DD8BC68D6A61}]
       * Are PLLs not Locked
       * [/cover] */
      if ((SysPllStat != 0x1U) || (PerPllStat != 0x1U))
      {
        /* [cover parentID={0C9E5C92-9CBF-4ab8-B24B-2DCC5067FE43}]
        Report Error
           [/cover] */
        Mcu_lReportError(MCU_SID_DISTRIBUTEPLLCLOCK, MCU_E_PLL_NOT_LOCKED);
        ErrorFlag = MCU_ERR_FOUND;
      }
    }
  }
  /*[/cover]*/
  #else
  SysPllStat = (uint32)SCU_SYSPLLSTAT.B.LOCK;
  PerPllStat = (uint32)SCU_PERPLLSTAT.B.LOCK;

  /* [cover parentID={709B9486-0358-4018-9662-0CE7257628DF}]
   * Are PLLs  locked
   * [/cover] */
  if ((SysPllStat != 0x1U) || (PerPllStat != 0x1U))
  {
    ErrorFlag = MCU_ERR_FOUND;
  }
  #endif
  /* [cover parentID={286734A2-FDE1-4fa3-BE30-E8F689CC197C}]
   * Did any DET occur
   * [/cover] */
  if (MCU_ERR_FOUND == ErrorFlag)
  {
    RetValue = (Std_ReturnType)E_NOT_OK;
  }
  else
  {
    /*
      PLL clock activation:
      1. Check if PLL as clock-tree source is requested and switch the
         clock source accordingly.
      2. Ramp the source frequencies (PLLs) to desired output frequency.
    */

    ClkselVal = (((Mcu_ConfigPtr->McuClockSettingPtr
                   [Mcu_ClockSetting].PllDistributionCfgPtr->Ccucon0) >>
                  (uint32)IFX_SCU_CCUCON0_CLKSEL_OFF) &
                 (uint32)IFX_SCU_CCUCON0_CLKSEL_MSK);
    /* [cover parentID={DDC9BF39-82E7-402e-A8F9-C0092D39525D}]
     * Is PLL selected as Clock Tree Source
     * [/cover] */
    if ((uint32)MCU_FSOURCE_CLKSEL_PLLCLK == ClkselVal)
    {
      Ccucon0Val.U = SCU_CCUCON0.U;
      Ccucon0Val.B.CLKSEL = MCU_FSOURCE_CLKSEL_PLLCLK;
      Ccucon0Val.B.UP = 0x1U;
      Ccucon0Val.U = (uint32)Ccucon0Val.U &
                     MCU_CCUCON0_RSVD_BIT_MASK;

      /* Wait within timeout until CCUCON0 write lock is not reset */
      TimeoutCtr = MCU_CCUCON0_LCK_TIMEOUT;
      Ccucon0Lck = (uint32)SCU_CCUCON0.B.LCK;

      /* [cover parentID={E6DFDFE1-5A08-41b7-93DC-9B2CABA95517}]
       * Provide a delay and check if the Ccucon0 register can be updated
       * [/cover] */
      while ((TimeoutCtr > 0x0U) && (0x1U == Ccucon0Lck))
      {
        Ccucon0Lck = (uint32)SCU_CCUCON0.B.LCK;

        TimeoutCtr--;
      }
      /* [cover parentID={BC98A101-C2AC-4dae-BC75-8A412BEDD723}]
       * Did timeout occur and Ccucon0 can still not be updated
       * [/cover] */
      if (0x0U == TimeoutCtr)
      {

        #if (MCU_E_CCUCON_UPDATE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
        /* Report Production error for system PLL error */
        /* [cover parentID=]
         * Report Error: Event failed
         * [/cover] */
        Mcu_lReportDemError(MCU_E_CCUCON_UPDATE_ERR,
                              DEM_EVENT_STATUS_FAILED);
        #endif

        RetValue = (Std_ReturnType)E_NOT_OK;
      }
      else
      {
        /*
         * CCUCON0 register is available to write, update and ramp to desired
         * frequency.
         */
        #if (MCU_E_CCUCON_UPDATE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
        /* Report Production error for system PLL error */
        Mcu_lReportDemError(MCU_E_CCUCON_UPDATE_ERR,
                              DEM_EVENT_STATUS_PASSED);
        #endif
        /*[/cover]*/
        /* [cover parentID={2B15999F-8C5D-4102-8AB0-7F0DCE40BAF4}]
         * Switch clock tree source to PLL
         * [/cover] */
        MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_CCUCON0.U,
            (uint32)Ccucon0Val.U);

        /* [cover parentID={64D51ED5-C539-4cb5-82EE-0445953D05DC}]
         * Ramp up the PLLs to Desired frequencies
         * [/cover] */
        RetValue = Mcu_lSwitchToDesiredFreq();
      }
    }
  }
  /*[cover parentID={730EFD93-8E8A-4f24-9897-14E05AD9A310}][/cover]
    [cover parentID={282C0FE3-7036-498a-8576-34CBEC0A93BE}][/cover]*/
  return RetValue;
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}
#endif

/*******************************************************************************
** Traceability    : [cover parentID={6DABBF23-F48B-42e7-9E89-C66C7922EAB0}]  **
**                                                                            **
** Syntax          : Mcu_PllStatusType Mcu_GetPllStatus( void )               **
**                                                                            **
** Description     : This function provides the lock status of the system     **
**                   and peripheral PLL                                       **
**                                                                            **
** Service ID      : 0x04                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Mcu_PllStatusType                                        **
**                   Returns whether PLL is Locked,Unlocked, Undefined status **
**                                                                            **
*******************************************************************************/
/*[cover parentID={E9E7877F-B957-480b-9D6D-10CC6AE0AA86}][/cover]*/
Mcu_PllStatusType Mcu_GetPllStatus(void)
{
  Mcu_PllStatusType RetValue = MCU_PLL_STATUS_UNDEFINED;
  #if (MCU_DISTRIBUTE_PLL_CLOCK_API == STD_ON)
  uint32 SysPllStatus, PerPllStatus;
  #endif

  /*
    Development Error Check: (only if Development Error Detection is ON)
    1. Check Mcu Driver is not yet initialized and report DET Error.
  */
  /*[cover parentID={4876E6B2-8281-468d-9340-51537077D027}]*/
  if (MCU_DRIVER_INITIALIZED != Mcu_DriverState)
  {
    /* [cover parentID={DB1F4DE2-7728-4004-817B-D587A6A10E84}]
     If Development Error Trace OR Safety is ON
     [/cover] */
    #if ((MCU_DEV_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
    /* [cover parentID={00EEE31E-F162-4791-A97B-14ECF186253D}]
    Report Error
    [/cover] */
    Mcu_lReportError(MCU_SID_GETPLLSTATUS, MCU_E_UNINIT);
    #endif
  }
  /*[/cover]*/
  /* [cover parentID={5AA5CBAE-DC82-4777-8A9C-F2118178F926}]
     * If Distribute Pll Clock API is ON
     * [/cover] */
  #if (MCU_DISTRIBUTE_PLL_CLOCK_API == STD_ON)
  else
  {
    /* Return the system Pll lock status */
    SysPllStatus = (uint32)SCU_SYSPLLSTAT.B.LOCK;
    PerPllStatus = (uint32)SCU_PERPLLSTAT.B.LOCK;
    /* [cover parentID={5622A390-BA2C-45b6-81FE-5B0E89D32D75}]
     * Is System Pll status and Peripheral Pll status Set
     * [/cover] */
    if ((SysPllStatus == 0x1U) && (PerPllStatus == 0x1U))
    {
      RetValue = MCU_PLL_LOCKED;
    }
    else
    {
      RetValue = MCU_PLL_UNLOCKED;
    }
  }
  #endif

  /* [cover parentID={B66E9AAD-16FB-4d99-9037-386F28EB0E13}]
   * Return PLL Status Undefined
   * [/cover] */
  return RetValue;
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability    : [cover parentID={E32524B2-67CE-4272-9653-5109A76F6770}]  **
**                                                                            **
** Syntax          :  Mcu_ResetType Mcu_GetResetReason( void )                **
**                                                                            **
** Description     : The API reads the reset type from the hardware and       **
**                   returns the type of reset occurred as per MCU supported  **
**                   resets.                                                  **
**                                                                            **
** Service ID      : 0x05                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Mcu_ResetType - Returns the reset reason                 **
**                                                                            **
*******************************************************************************/
/*[cover parentID={E9E7877F-B957-480b-9D6D-10CC6AE0AA86}][/cover]*/
Mcu_ResetType Mcu_GetResetReason(void)
{
  Mcu_RawResetType ResetReasonRaw;
  Mcu_ResetType ResetReason = MCU_RESET_UNDEFINED;

  /*
    Check Mcu Driver is not yet initialized and report DET Error.
    If DET reporting is disabled, then error checking is still done.
  */
  /*[cover parentID={2E1626EF-EEE9-4215-A359-30825A85EE5C}]*/
  if (MCU_DRIVER_INITIALIZED != Mcu_DriverState)
  {
    /* [cover parentID={2B3DD2D8-DC29-47ff-BF2D-F3E2ABE9F50E}]
        If Development Error Trace OR Safety is ON
        [/cover] */
    #if ((MCU_DEV_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
    /* [cover parentID={78996CAD-CEB7-41cf-BEC6-ED4E2A0DFEC0}]
     Report Error
     [/cover] */
    Mcu_lReportError(MCU_SID_GETRESETREASON, MCU_E_UNINIT);
    #endif
    /*[/cover]*/
  }
  else
  {
    /*
      1. Extract the reset reason from the raw reset status register value
      2. Retrieve type of reset out of raw reset value and return.
    */

    /* [cover parentID={1662331B-0279-4c60-A35B-036EC8C5DA0F}]
     * Extract reset reason from raw reset status register value
    * and reset reason [/cover] */
    ResetReasonRaw = (Mcu_RawResetType)(Mcu_ResetStatusVal &
                                        MCU_RESET_REASON_MASK);
    ResetReason = Mcu_lGetRstReason(ResetReasonRaw);
  }
  /* [cover parentID={364D5344-6521-48a6-AC91-9ED360D9E7EB}]
   * Return Reset Undefined
   * [/cover] */
  return ResetReason;
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability    : [cover parentID={F4921D33-023D-497a-9851-FFF425C12CD9}]  **
**                                                                            **
** Syntax          : Mcu_ResetType Mcu_GetResetRawValue( void )               **
**                                                                            **
** Description     : The API reads the returns the raw value of reset         **
**                   register.                                                **
**                                                                            **
** Service ID      : 0x06                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Mcu_RawResetType - Returns the raw value of reset        **
**                   register                                                 **
**                                                                            **
*******************************************************************************/
/*[cover parentID={E9E7877F-B957-480b-9D6D-10CC6AE0AA86}][/cover]*/
Mcu_RawResetType Mcu_GetResetRawValue(void)
{
  Mcu_RawResetType RetValue = MCU_RAW_RESET_UNDEFINED;

  /*
    Development Error Check: (only if Development Error Detection is ON)
    1. Check Mcu Driver is not yet initialized and report DET Error.
  */
  /*[cover parentID={8012BEA0-3D4C-4290-8F88-AC15EB8B7832}]*/
  if (MCU_DRIVER_INITIALIZED != Mcu_DriverState)
  {
    /* [cover parentID={B6FB4168-3289-4da8-A784-1D2BB62C273E}]
     If Development Error Trace OR Safety is ON
     [/cover] */

    #if ((MCU_DEV_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
    /* [cover parentID={AA4A144C-5E2D-4822-B5CC-5392FB2AFC59}]
     Report Error
     [/cover] */
    Mcu_lReportError(MCU_SID_GETRESETRAWVALUE, MCU_E_UNINIT);
    #endif
    /*[/cover]*/
  }
  else
  {
    /* Return raw reset status value */
    RetValue = Mcu_ResetStatusVal;
  }

  /* [cover parentID={F81325AB-2580-4766-A5A8-5992695F0EBA}]
   * Return Raw reset Undefined
   * [/cover] */
  return RetValue;
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
} /*End of Mcu_GetResetRawValue*/

#if (MCU_PERFORM_RESET_API == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID={9B15F2AE-C56F-4f25-9170-54EEE7C6B552}]  **
**                                                                            **
** Syntax          :  void Mcu_PerformReset( void )                           **
**                                                                            **
** Description     : The API performs a micro-controller reset.               **
**                   The MCU specific reset type to be performed by this      **
**                   service shall be configured in the configuration set.    **
**                                                                            **
** Service ID      : 0x07                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={E9E7877F-B957-480b-9D6D-10CC6AE0AA86}][/cover]*/
void Mcu_PerformReset(void)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_SWRSTCON SwResetReq;
  uint32 ResetDelayTicks, BaseSTMTick, CurrSTMTick, DelayTickResolution;

  /*
    Development Error Check: (only if Development Error Detection is ON)
    1. Check Mcu Driver is not yet initialized and report DET Error.
  */
  /* [cover parentID={4870BC3E-EBBD-4b2d-BBBB-17CE41AC3EBA}]
   If Development Error Trace OR Safety is ON
   [/cover] */
  #if ((MCU_DEV_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
  uint32 ErrorFlag = MCU_ERR_NOT_FOUND;
  /*[cover parentID={C3B1B8D9-8026-46c3-ABA0-5369F4056255}]Initialization
  check [/cover]*/
  /* [cover parentID={220C94D6-8EDB-4210-BECA-17315FED59A3}]
   * Is Mcu Driver not Initialized
   * [/cover] */
  /* [cover parentID={C3B1B8D9-8026-46c3-ABA0-5369F4056255}]
   * Initialization Check*/
  if (MCU_DRIVER_INITIALIZED != Mcu_DriverState)
  {
    /* [cover parentID={7F08556D-B13A-4a2f-B63C-230C0BE98BEE}]
    Report Error
    [/cover] */
    /* [cover parentID={6FBDC917-8809-4e58-ABE2-9287D12E5781}]
    Report Error
    [/cover] */
    Mcu_lReportError(MCU_SID_PERFORMRESET, MCU_E_UNINIT);
    ErrorFlag = MCU_ERR_FOUND;
  }
  /*[/cover]*/
  /*[/cover]*/
  /* [cover parentID={260B44C0-FF3F-4014-846B-F9C03CA464D6}]
   * Did any error occur
   * [/cover] */
  if (MCU_ERR_FOUND != ErrorFlag)
  #endif
  {
    /*
      Software Reset request:
      1. Set software reset request bit.
      2. Wait for sufficient delay to ensure reset is performed
    */
    /* [cover parentID={3D271358-73AE-4f29-9725-5D945C0AF6C4}]
     * Set Software Reset request bits*/
    SwResetReq.U = SCU_SWRSTCON.U;
    SwResetReq.B.SWRSTREQ = 0x1U;

    MCU_LIB_RUNTIME_WRITEPERIPENDINITPROTREG(&SCU_SWRSTCON.U,
        (uint32)SwResetReq.U);
    /*[/cover]*/

    CurrSTMTick = Mcal_DelayGetTick();
    BaseSTMTick = CurrSTMTick;
    DelayTickResolution = Mcal_DelayTickResolution();
    ResetDelayTicks = (MCU_PERFORM_RESET_DELAY / DelayTickResolution);

    /* [cover parentID={23360C75-1014-4fde-8542-8028E77E8868}]
     * Provide delay for Software reset request bits to be written
     * [/cover] */
    while ((uint32)((CurrSTMTick - BaseSTMTick) & MCU_STM_TICK_OVERFLOW) <
           ResetDelayTicks)
    {
      CurrSTMTick = Mcal_DelayGetTick();
    }
  }
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
    Registers[/cover]*/
  /*In case of SW Reset the following instruction should not be executed,
     * while in case of SW Reset failing the following Safety error will be
     * reported */
  /* [cover parentID={9D656632-E9EC-44bc-A4DE-04D97EEE033C}]
     * If Safety check is Enabled
     * [/cover] */
  #if (MCU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={F95CDC9F-505B-4b0e-B5A9-2F3777141041}]
   * Report Safety error for SW reset Failure
   * [/cover] */
  Mcal_ReportSafetyError((uint16)MCU_MODULE_ID, MCU_MODULE_INSTANCE,
                         MCU_SID_PERFORMRESET, MCU_E_SW_RESET_FAILED);
  #endif
}
#endif

/*******************************************************************************
** Traceability    : [cover parentID={6FCF65DC-EA71-431c-8A66-D95E61FDD98B}]  **
**                                                                            **
** Syntax          :  void Mcu_SetMode( const Mcu_ModeType McuMode )          **
**                                                                            **
** Description     : This API sets the device to idle, sleep or standby mode. **
**                   In Idle mode, the CPU is idle and peripherals are active.**
**                   In sleep mode, the CPUs are idle and selected peripherals**
**                   are put to sleep and other peripherals work at gated     **
**                   clocks. In standby mode, the CPU and all peripherals are **
**                   put to sleep. On a wakeup event after idle/sleep, the    **
**                   program execution continues from last instruction before **
**                   it went to sleep. On a wakeup event after standby, the   **
**                   program execution starts from the reset vector.  Please  **
**                   refer the HW UM for the pre-conditions to be taken care  **
**                   before invoking Mcu_SetMode for the desired mode.        **
**                                                                            **
** Service ID      : 0x08                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Concurrency Safe for IDLE mode transition requests       **
**                   and non re-entrant for other transitions.                **
**                                                                            **
** Parameters (in) : McuMode : Mcu Mode number as configured in the           **
**                   configuration set                                        **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={E9E7877F-B957-480b-9D6D-10CC6AE0AA86}][/cover]*/
void Mcu_SetMode(const Mcu_ModeType McuMode)
{
  uint32 CoreId;

  /*
    Development Error Check: (only if Development Error Detection is ON)
    1. Check Mcu Driver is not yet initialized and report DET Error.
    2. Check if requested mode is within maximum possible modes.
  */
  /* [cover parentID={9A23376B-40F3-4dd6-83D3-7E98FE4EC1B7}]
   If Development Error Trace OR Safety is ON
   [/cover] */
  #if ((MCU_DEV_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
  uint32 ErrorFlag = MCU_ERR_NOT_FOUND;

  /* [cover parentID={BCBBF2D2-813E-415c-9BE8-A95BACCB8BE7}]
   * Is Mcu Driver not Initialized
   * [/cover] */
  /* [cover parentID={C3B1B8D9-8026-46c3-ABA0-5369F4056255}]
   * Initialization Check*/
  if (Mcu_DriverState != MCU_DRIVER_INITIALIZED)
  {
    /* [cover parentID={7F08556D-B13A-4a2f-B63C-230C0BE98BEE}]
     * Report Error
     * [/cover] */
    Mcu_lReportError(MCU_SID_SETMODE, MCU_E_UNINIT);
    ErrorFlag = MCU_ERR_FOUND;
  }
  else
  {
    /* [cover parentID={AA84C5DE-3CAE-4e56-8A52-8E571BBEE295}]
    * Is Mcu mode Invalid
    * [/cover] */
    if ((McuMode >= (Mcu_ModeType)MCU_MAX_NO_MODES) || (0x0U ==
        (((uint32)0x1U << (uint32)McuMode) & (uint32)Mcu_ConfigPtr->
         McuLowPowerModeCfgPtr->MaxModeEvrcCtrl.McuMode)))
    {
      /* [cover parentID={DFE63F87-0390-408a-B9C5-5D4998AFEB86}]
      * Report Error
      * [/cover] */
      Mcu_lReportError(MCU_SID_SETMODE, MCU_E_PARAM_MODE);
      ErrorFlag = MCU_ERR_FOUND;
    }
  }
  /*[/cover] */
  /* [cover parentID={FD82A9FB-28E1-49e1-AA09-5A7306960D05}]
   * Did any DET occur
   * [/cover] */
  if (MCU_ERR_FOUND != ErrorFlag)
  #endif
  {
    /*
      Mode request:
      1. Read current core ID in indexed format.
      2. Process selected mode request.
    */

    CoreId = Mcal_GetCpuIndex();

    /* [cover parentID={6347561A-60CB-4cbe-BC12-2D68C0EAEA7A}]
     * If Mcu Idle Available is ON
     * [/cover] */
    if ((Mcu_ModeType)MCU_IDLE == McuMode)
    {
      /* [cover parentID={A73786E4-84A3-4b31-A601-BF635234A700}]
      * Set CPU mode to Idle mode
      * [/cover] */
      Mcu_lSetIdleMode((uint8)CoreId);
    }
    /* [cover parentID={09C23B4D-A156-43c9-B443-63C465A07FF5}]
     * If Mcu Sleep Available is ON
     * [/cover] */
    else if ((Mcu_ModeType)MCU_SLEEP == McuMode)
    {
      /* [cover parentID={33B7C621-CE8D-4011-9EB7-B1DA5518174C}]
      * Set CPU mode to Sleep mode
      * [/cover] */
      Mcu_lSetSleepMode((uint8)CoreId);
    }
    /* [cover parentID={4DBE3B4B-0740-4957-906E-7D8934102771}]
     * Is selected mode standby mode
     * [/cover] */
    else
    {
      #if ((MCU_DEV_ERROR_DETECT == STD_OFF) && (MCU_SAFETY_ENABLE == STD_OFF))
      if ((Mcu_ModeType)MCU_STANDBY == McuMode)
      #endif
      {
        /* [cover parentID={652BDAE3-5E19-4e81-9365-3E1DE536F635}]
           * Set CPU mode to StandBy mode
           * [/cover] */
        Mcu_lSetStandbyMode((uint8)CoreId);
      }
    }
  }
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

#if (MCU_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Traceability    :  [cover parentID={974BD883-B297-44c7-B471-B56B9309FF49}] **
**                                                                            **
** Syntax          :  void  Mcu_GetVersionInfo                                **
**                   (                                                        **
**                     Std_VersionInfoType * const versioninfo                **
**                   )                                                        **
**                                                                            **
** Description     : This service returns the version information of module.  **
**                   The version information includes:                        **
**                   - Vendor Id                                              **
**                   - Module Id                                              **
**                   - SW Major Version                                       **
**                   - SW Minor Version                                       **
**                   - SW Patch Version                                       **
**                                                                            **
** Service ID      : 0x09                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : versioninfo : (Pointer to store the version              **
**                   information of this module)                              **
**                                                                            **
** Parameters (out): VersionInfoPtr values are updated with version           **
**                   information                                              **
**                                                                            **
** Return value:   : None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={E9E7877F-B957-480b-9D6D-10CC6AE0AA86}][/cover]*/
void Mcu_GetVersionInfo(Std_VersionInfoType *const versioninfo)
{
  /*
    Development Error Check: (only if Development Error Detection is ON)
    1. Check input VersionInfoPtr for invalid pointer (NULL_PTR) and
       report DET Error.
  */
  /* [cover parentID={A90EBC30-914B-4f26-848D-C92A86C84D3B}]
   Mcu_GetVersionInfo
   [/cover] */
  /* [cover parentID={A8D8F794-E655-4a0b-A36B-20FD56112BEC}]
   If DET check OR Safety is ON
   [/cover] */
  /*[cover parentID={EE1DAA3C-8D8B-43df-B6D1-D946D5059230}]*/
  #if ((MCU_DEV_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
  uint32 ErrorFlag = MCU_ERR_NOT_FOUND;

  /* [cover parentID={1334BAC3-3A1E-4e80-965F-C15C1FE28E6B}]
   * Is NULL Parameter passed
   * [/cover] */
  if (NULL_PTR == versioninfo)
  {
    /* [cover parentID={E4BC06B8-242D-4b09-8B61-6B1D50D80ED1}]
     Report Error
     [/cover] */
    Mcu_lReportError(MCU_SID_GETVERSIONINFO, MCU_E_PARAM_POINTER);
    ErrorFlag = MCU_ERR_FOUND;
  }
  /*[/cover]*/
  /*[cover parentID={476C403A-31E2-427f-A97A-DED77F0FCBBE}][/cover]*/
  if (MCU_ERR_FOUND != ErrorFlag)
  #endif
  {
    /*
      Copy module version information:
      1. Module ID.
      2. Vendor ID.
      3. SW Major version.
      4. SW Minor version.
      5. SW Patch version.
    */
    /* [cover parentID={06909272-07F2-4c3f-AA6A-AA9FEDDA4811}]
     Copy module version information
     [/cover] */
    versioninfo->moduleID = (uint16)MCU_MODULE_ID;
    versioninfo->vendorID = (uint16)MCU_VENDOR_ID;
    versioninfo->sw_major_version = (uint8)MCU_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = (uint8)MCU_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = (uint8)MCU_SW_PATCH_VERSION;
  }
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}
#endif

#if (MCU_GET_RAM_STATE_API == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID = {C15F6F39-253E-4197-90BA-972226223996}]**
**                                                                            **
** Syntax          : Mcu_RamStateType  Mcu_GetRamState (void)                 **
**                                                                            **
** Description     : This service returns the RAM state of given CPU.         **
**                                                                            **
** Service ID      : 0x0A                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : MCU_RAMSTATE_INVALID: RAM contents got corrupted         **
**                   MCU_RAMSTATE_VALID  : RAM contents are valid             **
**                                                                            **
*******************************************************************************/
Mcu_RamStateType Mcu_GetRamState(void)
{
  Mcu_RamStateType RetVal;
  uint32           CpuId;
  uint8            CssVal;
  uint8            BitPos;

  RetVal = MCU_RAMSTATE_INVALID;

  /* [cover parentID={B4F071B5-9403-4853-B67C-ECB74C2CC55A}]
   *  If DET or Safety is Enabled
   * [/cover] */
  #if ((MCU_DEV_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
  /* [cover parentID={C3751BAD-3CD5-428c-A7E9-EEEAA8A3A31C}]
   *  Is Mcu driver not initialized
   * [/cover] */
  if (Mcu_DriverState != MCU_DRIVER_INITIALIZED)
  {
    /* [cover parentID={4A9B6487-BCD1-4619-A26C-090D32644779}]
     *  Report DET
     * [/cover] */
    Mcu_lReportError(MCU_SID_GETRAMSTATE, MCU_E_UNINIT);
  }
  /* [cover parentID={B5BDD035-93FF-42fb-81A9-9ACE2B52FE32}]
   *  if no DET occurred [/cover] */
  else
  #endif
  {
    /* [cover parentID={E17BF395-72EA-40d8-8D8C-AC39B09CACC8}]
     * Get Core Id [/cover] */
    CpuId = Mcal_GetCpuIndex();

    /* Calculate the bit position for the core */
    BitPos = (uint8)(CpuId + IFX_SCU_RSTCON2_CSSX_OFF);

    /* [cover parentID={054B7B3A-7AFE-4127-B56E-A5F2EB9EDC3C}]
     *  Read the Ram state
     * [/cover] */
    /* Read the CSSx status */
    CssVal = (uint8)Mcal_GetBitAtomic(SCU_RSTCON2.U, BitPos, MCU_CSSX_LEN);

    /* [cover parentID={BE598566-4DE2-47fc-846B-B13DC654B54D}][/cover] */
    /* Check if the RAM contents are valid */
    if (CssVal == 0x1U)
    {
      RetVal = MCU_RAMSTATE_VALID;
    }
  }
  /* [cover parentID={DE19194B-5919-43db-81F4-C7E7C5D84C3B}]
   *  Return MCU_RAMSTATE_INVALID [/cover] */
  /* [cover parentID={9E4830ED-FDA3-4280-9A3C-591756B3D40A}]
   *  Return MCU_RAMSTATE_VALID [/cover] */
  return RetVal;
}
#endif

#if (MCU_CLK_SRC_FAILURE_NOTIF_API == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID={09D2A990-2509-4e23-95F7-2ABB2B773FAE}]  **
**                                                                            **
** Syntax          : void Mcu_ClockFailureNotification ( void )               **
**                                                                            **
** Description     : This service reports Production error when called        **
**                   in case of PLL lock loss                                 **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:   : None                                                     **
**                                                                            **
*******************************************************************************/
void Mcu_ClockFailureNotification(void)
{
  /*[cover parentID={C1A044A3-4640-45a1-B470-B7ABA26B1424}][/cover]*/
  #if (MCU_E_OSC_FAILURE_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
  uint32 OscconPllHv, OscconPllLv;
  #endif

  /* Report Production error for clock loss failure */
  /*[cover parentID={B021273D-D599-4997-A1DB-1054D1D46341}][/cover]*/
  #if (MCU_E_SYSTEM_PLL_LOCK_LOSS_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
  if (0x1U != SCU_SYSPLLSTAT.B.LOCK)
  {
    /* [cover parentID=]
     * Report Production error
     * [/cover] */
    Mcu_lReportDemError(MCU_E_SYSTEM_PLL_LOCK_LOSS, DEM_EVENT_STATUS_FAILED);
  }
  #endif

  /*[cover parentID={91661C22-8E06-4acc-9BD8-7BAF4938BB91}][/cover]*/
  #if (MCU_E_PERIPHERAL_PLL_LOCK_LOSS_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
  /*[cover parentID={74567C60-1B18-4c2c-AD83-1FCF815758E7}][/cover]*/
  if (0x1U != SCU_PERPLLSTAT.B.LOCK)
  {
    /* [cover parentID=]
     * Report Production error
     * [/cover] */
    Mcu_lReportDemError(MCU_E_PERIPHERAL_PLL_LOCK_LOSS,
                          DEM_EVENT_STATUS_FAILED);
  }
  #endif

  #if (MCU_E_OSC_FAILURE_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
  OscconPllHv = SCU_OSCCON.B.PLLHV;
  OscconPllLv = SCU_OSCCON.B.PLLLV;
  /*[cover parentID={265F6BA1-0834-40c7-8CB8-A81576C2B4DC}][/cover]*/
  if ((0x0U == OscconPllHv) || (0x0U == OscconPllLv))
  {
    /* [cover parentID=]
     * Report Production error
     * [/cover] */
    Mcu_lReportDemError(MCU_E_OSC_FAILURE, DEM_EVENT_STATUS_FAILED);
  }
  #endif
}
#endif

#if (MCU_CLR_COLD_RESET_STAT_API == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID={C2A8BF2B-6C17-4afd-AE82-343432DCB2C3}]  **
**                                                                            **
** Syntax          : void  Mcu_ClearColdResetStatus ( void )                  **
**                                                                            **
** Description     : This API clears the reset reason register content.       **
**                                                                            **
** Service ID      : 0x50                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={E9E7877F-B957-480b-9D6D-10CC6AE0AA86}][/cover]*/
void Mcu_ClearColdResetStatus(void)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_RSTCON2 Rstcon2Val;
  /*
    Development Error Check: (only if Development Error Detection is ON)
    1. Check Mcu Driver is not yet initialized and report DET Error.
  */
  /* [cover parentID={DB4040CA-3686-49a0-B1C2-7DAB43429114}]
   * If DET OR Safety is ON
   * [/cover] */
  /* [cover parentID={F4E03A60-822D-44fc-8FFE-AB7E064EB969}]
   * Check for DET
   * [/cover] */
  #if ((MCU_DEV_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
  uint32 ErrorFlag = MCU_ERR_NOT_FOUND;

  /* [cover parentID={480B14F1-CD6D-42d3-BB0D-ED5E07FD6C7F}]
   * Is Mcu Driver not Initialized
   * [/cover] */
  if (Mcu_DriverState != MCU_DRIVER_INITIALIZED)
  {
    /* [cover parentID={45A6F3FF-65B3-48ac-AF2D-026C626017DD}]
     * Report DET
     * [/cover] */
    Mcu_lReportError(MCU_SID_CLRCOLDRESETSTAT, MCU_E_UNINIT);
    ErrorFlag = MCU_ERR_FOUND;
  }

  /* [cover parentID={EB62AD2C-41FC-47dc-BBD1-F8351536F3F2}]
   * Did any DET occur
   * [/cover] */
  if (MCU_ERR_FOUND != ErrorFlag)
  #endif
  {
    /* Clear cold reset */
    Rstcon2Val.U = SCU_RSTCON2.U;
    Rstcon2Val.B.CLRC = 0x1U;
    MCU_LIB_RUNTIME_WRITEPERIPENDINITPROTREG(&SCU_RSTCON2.U,
        (uint32)(Rstcon2Val.U));
  }
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}
#endif /* End of #if (MCU_CLR_COLD_RESET_STAT_API == STD_ON) */

/* [cover parentID={E45EF867-B755-429e-BBB2-E17E55283BB7}]
 * If Low power mode API is ON
 * [/cover] */
#if (MCU_LOW_POWER_MODE_API == STD_ON)
/*******************************************************************************
** Traceability    :  [cover parentID={BB171340-32CF-4d99-B7C1-00845A7F0A90}] **
**                                                                            **
** Syntax          : uint32 Mcu_GetCpuIdleModeInitiator                       **
**                   (                                                        **
**                     void                                                   **
**                   )                                                        **
**                                                                            **
** Description     : This API returns the CPU ID which is configured to       **
**                   initiate IDLE mode.                                      **
**                                                                            **
** Service ID      : 0x52                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : uint32 - CPU Id value.                                   **
**                                                                            **
*******************************************************************************/
/*[cover parentID={E9E7877F-B957-480b-9D6D-10CC6AE0AA86}][/cover]*/
uint32 Mcu_GetCpuIdleModeInitiator(void)
{
  uint32 CpuId = MCU_IDLE_CORE_NOT_DEFINED;

  /*
    Development Error Check: (only if Development Error Detection is ON)
    1. Check Mcu Driver is not yet initialized and report DET Error.
  */
  /* [cover parentID={72D4A280-8F7F-4acb-AC2A-B5329422082B}]
   If Development Error Trace OR Safety is ON
   [/cover] */
  /*[cover parentID={CF3B84B2-45B3-422c-ACB6-3C0F1354F99B}]*/
  /* [cover parentID={0727903C-06B1-4a77-9642-30FE1341469A}]
    * Check for DET*/
  #if ((MCU_DEV_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
  uint32 ErrorFlag = MCU_ERR_NOT_FOUND;

  /* [cover parentID={4C5AD939-8C33-4726-8D91-FE11F6DC2FEC}]
   * Is Mcu Driver not Initialized
   * [/cover] */
  /* [cover parentID={E13680AE-EEAB-49ef-BC18-13FF3D90D18E}]
   * Is Mcu Driver not Initialized
   * [/cover] */
  if (MCU_DRIVER_INITIALIZED != Mcu_DriverState)
  {
    /* [cover parentID={5A3F7EF2-25C4-43ce-8F68-DF5612528568}]
     Report DET
     [/cover] */
    Mcu_lReportError(MCU_SID_GETCPUIDLEMODEINIT, MCU_E_UNINIT);
    ErrorFlag = MCU_ERR_FOUND;
  }
  /*[/cover]*/
  /* [cover parentID={A963F0B8-B8BF-4814-97BB-D93F28F6E313}]
   * No DET occurred
   * [/cover] */
  /* [cover parentID={F6FC65AC-4945-484c-B70F-F8E1D7FA0550}]
    * Did any DET occur
    * [/cover] */
  if (MCU_ERR_FOUND != ErrorFlag)
  #endif
    /*[/cover] */
  {
    /* [cover parentID={3995408C-7EB2-4454-A6A3-385F4973D18E}]
     * If Idle mode core is not defined
     * [/cover] */
    #if (MCU_IDLE_MODE_CORE != MCU_IDLE_CORE_NOT_DEFINED)
    /* Read current CPU IDLE mode initiator core ID setting*/
    CpuId = (uint32)SCU_PMSWCR1.B.CPUIDLSEL;

    /* [cover parentID={53028A88-A9ED-4975-9319-01A308EEBFA3}]
     * Based on Idle mode settings return whether a Single core can
     * trigger Idle mode or all Cores can trigger Idle mode Unanimously
     * [/cover] */
    if (CpuId > (uint32)0x0U)
    {
      CpuId = (CpuId - (uint32)0x1U);
    }
    else
    {

      CpuId = MCU_CPU_INIDIVIDUAL_UNANIMOUS;
    }
    #endif
  }
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
  /*[cover parentID={E63DE180-2796-4e67-A472-9026E906991A}]Interrupt Control
  Registers[/cover]*/
  return CpuId;
}

/*******************************************************************************
** Traceability    : [cover parentID={E44FFFB6-4A71-47f0-AF58-E5C903C31AA9}]  **
**                                                                            **
** Syntax          : Mcu_CpuModeType  Mcu_GetCpuState                         **
**                   (                                                        **
**                     const Mcu_CpuIdType CpuId                              **
**                   )                                                        **
**                                                                            **
** Description     : This API returns the current CPU state of requested CPU  **
**                                                                            **
** Service ID      : 0x53                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : CpuId : The Core id for which the mode needs to be       **
**                   determined                                               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Mcu_CpuModeType  - CPU mode status of requested core     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={E9E7877F-B957-480b-9D6D-10CC6AE0AA86}][/cover]*/
Mcu_CpuModeType Mcu_GetCpuState(const Mcu_CpuIdType CpuId)
{
  Mcu_CpuModeType CpuMode = MCU_CPU_UNDEFINED_MODE;
  uint32 PmstRegVal; /*SCU_PMCSR_PMST bit-field value */

  /*
    Development Error Check: (only if Development Error Detection is ON)
    1. Check Mcu Driver is not yet initialized and report DET Error.
    2. Check input core ID out of supported number of cores in device and
       report DET Error.
  */
  /* [cover parentID={63B9689B-8B06-4d91-B49E-1A8548E65CFE}]
   If Development Error Trace OR Safety is ON
   [/cover] */
  /*[cover parentID={BB91408E-DFAA-4525-9D21-FDBB50419D0D}]*/
  #if ((MCU_DEV_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
  uint32 ErrorFlag = MCU_ERR_NOT_FOUND;

  /* [cover parentID={1203FDF3-5A8D-4e7a-BE45-241BAD63B3DC}]
   * Is Mcu Driver not Initialized
   * [/cover] */
  if (MCU_DRIVER_INITIALIZED != Mcu_DriverState)
  {
    /* [cover parentID={02E9982C-9453-4cba-AC3C-C9D9746CF6B8}]
     Report DET
       [/cover] */
    Mcu_lReportError(MCU_SID_GETCPUSTATE, MCU_E_UNINIT);
    ErrorFlag = MCU_ERR_FOUND;
  }
  else
  {
    /* [cover parentID={1C86CFA0-6CF0-46db-89AD-7EC4D7F7DCF1}]
     * Is CPU Id Invalid
     * [/cover] */
    if ((uint32)CpuId >= MCAL_NO_OF_ACTIVE_CORES)
    {
      /* [cover parentID={D1A1488F-1FC0-46f9-97D4-9365E0FD9CB5}]
      Report DET
      [/cover] */
      Mcu_lReportError(MCU_SID_GETCPUSTATE, MCU_E_PARAM_CPUID);
      ErrorFlag = MCU_ERR_FOUND;
    }
  }
  /*[/cover]*/
  /* [cover parentID={D6676911-24B0-43ab-B6A7-ECBA32A4E439}]
   * Did any DET occur
   * [/cover] */
  if (MCU_ERR_FOUND != ErrorFlag)
  #endif
  {
    /* Read CPU mode of requested core and return */
    PmstRegVal = Mcu_lGetCpuMode((uint32)CpuId);

    /* [cover parentID={B3F25330-911A-4b2d-B06C-DB70C0C46DCE}]
     * Is CPU mode not reserved mode
     * [/cover] */
    if ((PmstRegVal != MCU_CPU_MODE_RESERVED1) &&
        (PmstRegVal != MCU_CPU_MODE_RESERVED2) &&
        (PmstRegVal != MCU_CPU_MODE_RESERVED3))
    {
      /* MISRA2012_RULE_10_5_JUSTIFICATION: Unsigned to enum typecast is
         performed as API return type is an enum, whereas return value is from
         SFR defined as unsigned int. */
      /* MISRA2012_RULE_10_3_JUSTIFICATION: Assignment to narrower type enum
         is performed however CpuId possible values (from SFR) are within
         allowed enum values. */
      /* [cover parentID={C3139614-8605-4d34-BB00-9093DEA23F3A}]
       * Get CPU mode
       * [/cover] */
      CpuMode = (Mcu_CpuModeType)PmstRegVal;
    }
  }
  return CpuMode;
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
  /*[cover parentID={6B0BFEC8-4110-465d-B63D-31230771BB6F}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability    : [cover parentID={4B0CC8EC-9E20-48cb-BC36-5CD0AC6C297C}]  **
**                                                                            **
** Syntax          : void Mcu_ClearWakeupCause                                **
**                   (                                                        **
**                     const uint32 WakeupCause                               **
**                   )                                                        **
**                                                                            **
** Description     : This API clears the selected wakeup reasons.             **
**                                                                            **
** Service ID      : 0x55                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : WakeupCause - mask for wakeup causes to be cleared.      **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={E9E7877F-B957-480b-9D6D-10CC6AE0AA86}][/cover]*/
void Mcu_ClearWakeupCause(const uint32 WakeupCause)
{
  /*
    Development Error Check: (only if Development Error Detection is ON)
    1. Check Mcu Driver is not yet initialized and report DET Error.
  */
  /* [cover parentID={E6AD7DFC-09B6-461d-8B41-11C980FB025F}]
   * If Development Error Trace OR Safety is ON
   * [/cover] */
  /*[cover parentID={BFB510F0-D9E5-4747-AF4E-B833B8F60EB1}]*/
  #if ((MCU_DEV_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
  uint32 ErrorFlag = MCU_ERR_NOT_FOUND;

  /* [cover parentID={D66EE4AF-646A-4a0b-9F11-A83F296FB80D}]
   * Is Mcu Driver not Initialized
   * [/cover] */
  if (MCU_DRIVER_INITIALIZED != Mcu_DriverState)
  {
    /* [cover parentID={CE123ECF-860B-4614-BF4D-AF0D50B7C3FB}]
     * Report DET
     * [/cover] */
    Mcu_lReportError(MCU_SID_CLRWAKEUPCAUSE, MCU_E_UNINIT);
    ErrorFlag = MCU_ERR_FOUND;
  }
  /*[/cover]*/
  /* [cover parentID={74F3B788-A5BE-41ee-A4EF-073BF148BBE7}]
   * Did any DET occur
   * [/cover] */
  if (MCU_ERR_FOUND != ErrorFlag)
  #endif
  {
    /* Clear wake-up cause status register */
    MCU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG(&PMS_PMSWSTATCLR.U,
        (uint32)(WakeupCause & MCU_PMS_WAKEUP_CAUSE_CLR_MASK));
  }
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability    : [cover parentID={DB328D8B-C8DE-4175-9D61-4A10B8D5874A}]  **
**                                                                            **
** Syntax          : uint32 Mcu_GetWakeupCause ( void )                       **
**                                                                            **
** Description     : This API returns the wakeup cause register value.        **
**                                                                            **
** Service ID      : 0x54                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : uint32  - Reason for wakeup                              **
**                                                                            **
*******************************************************************************/
/*[cover parentID={E9E7877F-B957-480b-9D6D-10CC6AE0AA86}][/cover]*/
uint32 Mcu_GetWakeupCause(void)
{
  uint32 WakeupCause = WAKEUP_CAUSE_INVALID;
  /*
     Development Error Check: (only if Development Error Detection is ON)
     1. Check Mcu Driver is not yet initialized and report DET Error.
   */
  /* [cover parentID={A15E599D-5694-4d56-9A36-B7324E1D92F1}]
   If Development Error Trace OR Safety is ON
   [/cover] */
  /*[cover parentID={0727903C-06B1-4a77-9642-30FE1341469A}]*/
  #if ((MCU_DEV_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
  uint32 ErrorFlag = MCU_ERR_NOT_FOUND;

  if (MCU_DRIVER_INITIALIZED != Mcu_DriverState)
  {
    /* [cover parentID={425E1792-0427-4de8-BA10-91A238F85AF0}]
     Report DET
     [/cover] */
    Mcu_lReportError(MCU_SID_GETWAKEUPCAUSE, MCU_E_UNINIT);
    ErrorFlag = MCU_ERR_FOUND;
  }
  /*[/cover]*/
  if (MCU_ERR_FOUND != ErrorFlag)
  #endif
  {
    WakeupCause = (uint32)PMS_PMSWSTAT2.U;
  }
  return (WakeupCause);
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

#endif /* End of #if (MCU_LOW_POWER_MODE_API == STD_ON)*/

/* [cover parentID={560D9955-1897-46d8-BEAB-A5B1448E0D9C}]
 * If Trap API is ON*/
#if (MCU_TRAP_API == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID={3417D555-72B1-4b61-8590-50081D146931}]  **
**                                                                            **
** Syntax          : void Mcu_SetTrapRequest                                  **
**                   (                                                        **
**                     const Mcu_TrapRequestType TrapRequestId                **
**                   )                                                        **
**                                                                            **
** Description     : This API sets the selected trap request.                 **
**                                                                            **
** Service ID      : 0x57                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for other Trap IDs                             **
**                                                                            **
** Parameters (in) : TrapRequestId - Type of trap request to be set           **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={E9E7877F-B957-480b-9D6D-10CC6AE0AA86}][/cover]*/
void Mcu_SetTrapRequest(const Mcu_TrapRequestType TrapRequestId)
{
  /*
    Development Error Check: (only if Development Error Detection is ON)
    1. Check Mcu Driver is not yet initialized and report DET Error.
    2. Check if input TrapRequestId parameter is within valid range.
  */
  /* [cover parentID={091EA580-4169-4c7d-99E1-7CC5BD960C91}]
   * If Development Error Trace OR Safety is ON
   * [/cover] */
  /* [cover parentID={409ABF28-0E43-4c62-B56E-7C35A2ED8CA6}]
   * Check for DETs */
  #if ((MCU_DEV_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
  uint32 ErrorFlag = MCU_ERR_NOT_FOUND;

  /* [cover parentID={3ECBAC37-2622-49d8-B69A-02C9DECE8F25}]
   * Is Mcu Driver not Initialized
   * [/cover] */
  if (MCU_DRIVER_INITIALIZED != Mcu_DriverState)
  {
    /* [cover parentID={A1271D5E-2C19-4636-8BCA-CC5A6D47427E}]
     * Report DET
     * [/cover] */
    Mcu_lReportError(MCU_SID_SETTRAPREQ, MCU_E_UNINIT);
    ErrorFlag = MCU_ERR_FOUND;
  }
  else
  {
    /* [cover parentID={D7611B8F-4D7E-473e-8B49-37DCA5D171BC}]
     * Is Trap Id Invalid
     * [/cover] */
    if ((uint32)TrapRequestId >= (uint32)MCU_TRAP_INVALID)
    {
      /* [cover parentID={541B5FF9-42E0-438f-B984-C696831A43D0}]
       * Report DET
       * [/cover] */
      Mcu_lReportError(MCU_SID_SETTRAPREQ, MCU_E_PARAM_TRAPID);
      ErrorFlag = MCU_ERR_FOUND;
    }
  }
  /*[/cover]*/
  /*[/cover] */
  /* [cover parentID={8889BDCF-9728-4970-8684-108464B9CA3C}]
   * Did any DET occur
   * [/cover] */
  if (MCU_ERR_FOUND != ErrorFlag)
  #endif
  {
    /* Set trap request of requested type */
    /* [cover parentID={E78E6DFD-AFB0-41bb-B402-3A997463AF2D}]
     * Set Trap according to the Trap Id
     * [/cover] */
    MCU_LIB_RUNTIME_WRITEPERIPENDINITPROTREG(&SCU_TRAPSET.U,
        ((uint32)0x1U << (uint32)TrapRequestId));
  }
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability    : [cover parentID={F3FEEAD8-DF2D-40dd-BE97-AD8A933504CE}]  **
**                                                                            **
** Syntax          : void Mcu_ClearTrapRequest                                **
**                   (                                                        **
**                     const Mcu_TrapRequestType TrapRequestId                **
**                   )                                                        **
**                                                                            **
** Description     : This API clears the selected trap cause.                 **
**                                                                            **
** Service ID      : 0x58                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for other Trap IDs                             **
**                                                                            **
** Parameters (in) : TrapRequestId - Type of trap reason to be cleared        **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={E9E7877F-B957-480b-9D6D-10CC6AE0AA86}][/cover]*/
void Mcu_ClearTrapRequest(const Mcu_TrapRequestType TrapRequestId)
{
  /*
    Development Error Check: (only if Development Error Detection is ON)
    1. Check Mcu Driver is not yet initialized and report DET Error.
    2. Check if input TrapRequestId parameter is within valid range.
  */
  /* [cover parentID={67052861-5236-4fea-9BF5-83F22F6EB4A8}]
   * If Development error Trace OR Safety is ON
   * [/cover] */
  /*[cover parentID={6FFC3B3D-C03A-46e7-A73F-D38315781A95}]*/
  #if ((MCU_DEV_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
  uint32 ErrorFlag = MCU_ERR_NOT_FOUND;

  /* [cover parentID={E9A887CC-534D-4591-BDE2-635EB5965C3D}]
   * Is Mcu Driver not Initialized
   * [/cover] */
  if (MCU_DRIVER_INITIALIZED != Mcu_DriverState)
  {
    /* [cover parentID={CA7FA090-99E0-4c4e-95FF-F3A8CE74AF7F}]
    * Report DET
    * [/cover] */
    Mcu_lReportError(MCU_SID_CLRTRAPREQ, MCU_E_UNINIT);
    ErrorFlag = MCU_ERR_FOUND;
  }
  else
  {
    /* [cover parentID={3B066364-0623-4109-9268-F25B863C0D6C}]
     * Is Trap request Id Invalid
     * [/cover] */
    if ((uint32)TrapRequestId >= (uint32)MCU_TRAP_INVALID)
    {
      /* [cover parentID={CA7FA090-99E0-4c4e-95FF-F3A8CE74AF7F}]
       * Report DET
       * [/cover] */
      /* [cover parentID={F8A2AA21-A216-484e-B6F1-50C9AEDCB8A9}]
      * Report DET [/cover] */
      Mcu_lReportError(MCU_SID_CLRTRAPREQ, MCU_E_PARAM_TRAPID);
      ErrorFlag = MCU_ERR_FOUND;
    }
  }
  /*[/cover]*/
  /* [cover parentID={5E99AED6-29A0-4aab-B2F7-C2F86A22C694}]
   * Did any DET Occur
   * [/cover] */
  if (MCU_ERR_FOUND != ErrorFlag)
  #endif
  {
    /* Clear trap request of requested type */
    Mcal_SetBitAtomic(&(SCU_TRAPCLR.U), TrapRequestId, SCU_TRAPCLR_ESR0T_LEN,
                      MCU_TRAP_CLR);
  }
  /* MISRA2012_RULE_2_7_JUSTIFICATION: TrapRequestId is used in
   * Mcal_SetBitAtomic No side effects foreseen by violating this MISRA rule.*/
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability    : [cover parentID={CA656C80-8781-4c49-8E2C-5E9D11667F81}]  **
**                                                                            **
** Syntax          : uint32 Mcu_GetTrapCause ( void )                         **
**                                                                            **
** Description     : This API returns the trap cause register value.          **
**                                                                            **
** Service ID      : 0x56                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : uint32  - Reason for Trap                                **
**                                                                            **
*******************************************************************************/
/*[cover parentID={E9E7877F-B957-480b-9D6D-10CC6AE0AA86}][/cover]*/
uint32 Mcu_GetTrapCause(void)
{
  uint32 TrapCause = TRAP_CAUSE_INVALID;
  /*
    Development Error Check: (only if Development Error Detection is ON)
    1. Check Mcu Driver is not yet initialized and report DET Error.
  */
  /* [cover parentID={74D01893-1738-4df6-B788-88A05150D86C}]
   * If Development Error Trace OR Safety is ON
   * [/cover] */
  /*[cover parentID={7B706CF3-4305-4237-B2CE-42D56F27FA3A}]*/
  #if ((MCU_DEV_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
  uint32 ErrorFlag = MCU_ERR_NOT_FOUND;

  /* [cover parentID={652BE9C0-C470-4ead-82F0-857DCA9CDD59}]
   * Is Mcu Driver not initialized
   * [/cover] */
  if (MCU_DRIVER_INITIALIZED != Mcu_DriverState)
  {
    /* [cover parentID={EBCD294C-FB62-4310-98BA-8ED105293A68}]
     * Report DET
     * [/cover] */
    Mcu_lReportError(MCU_SID_GETTRAPCAUSE, MCU_E_UNINIT);
    ErrorFlag = MCU_ERR_FOUND;
  }
  /*[/cover]*/
  /* [cover parentID={0F7968D3-5048-4d0f-BBC4-FA925EFC8A48}]
   * Did any DET occur
   * [/cover] */
  if (MCU_ERR_FOUND != ErrorFlag)
  #endif
  {
    TrapCause = (uint32)SCU_TRAPSTAT.U;
  }
  /* Read and return trap status register content */
  return (TrapCause);
  /* [cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
   * Registers
   * [/cover] */
}
#endif /* End of #if (MCU_TRAP_API == STD_ON)*/
/*[/cover] */

#if (MCU_CPU_CCUCON_UPDATE_API == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID={96F0B853-7221-431c-B01F-88F331042463}]  **
**                                                                            **
** Syntax          : void Mcu_UpdateCpuCcuconReg                              **
**                   (                                                        **
**                     const Mcu_CpuIdType CpuId,                             **
**                     const uint8 DivVal,                                    **
**                     const uint8 Delay                                      **
**                   )                                                        **
** Description     : This API updates CCUCONx divider value of CPUx to the    **
**                   user provided value.                                     **
**                                                                            **
** Service ID      : 0x59                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for other cores                                **
**                                                                            **
** Parameters (in) : CpuId  - CpuId of core                                   **
**                   DivVal - New divider value for update in CCUCONx.        **
**                   Delay  - Delay in microseconds after register update.    **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={E9E7877F-B957-480b-9D6D-10CC6AE0AA86}][/cover]*/
void Mcu_UpdateCpuCcuconReg(
  const Mcu_CpuIdType CpuId,
  const uint8 DivVal,
  const uint8 Delay)
{
  uint32 DeltaTicks, BaseSTMTick, CurrSTMTick;
  /*
    Development Error Check: (only if Development Error Detection is ON)
    1. Check Mcu Driver is not yet initialized and report DET Error.
    2. Check if input CpuId parameter is within valid range.
  */
  /* [cover parentID={02A64288-B8B9-4062-9843-6A428144ABC4}]
   If Development Error Trace OR Safety is ON
   [/cover] */
  /*[cover parentID={16EEBB6B-E740-467f-A2DF-061472B092FC}]*/
  #if ((MCU_DEV_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
  uint32 ErrorFlag = MCU_ERR_NOT_FOUND;

  /* [cover parentID={BC548543-B28E-4a5f-AFE9-42B21F4DA337}]
   * Is Mcu Driver not Initialized
   * [/cover] */
  if (MCU_DRIVER_INITIALIZED != Mcu_DriverState)
  {
    /* [cover parentID={35405A9F-F741-4e81-91B4-3254CAD1ED2B}]
    Report DET
    [/cover] */
    Mcu_lReportError(MCU_SID_UPDCPUCCUCONREG, MCU_E_UNINIT);
    ErrorFlag = MCU_ERR_FOUND;
  }
  /* [cover parentID={B99490E5-C76F-4043-ADD1-861052140504}]
   * Is CPU Id Invalid
   * [/cover] */
  else if ((uint32)CpuId >= MCAL_NO_OF_ACTIVE_CORES)
  {
    {
      /* [cover parentID={497A500F-A3AC-4e52-BDF2-74D933FA4269}]
       * Report DET
       * [/cover] */
      Mcu_lReportError(MCU_SID_UPDCPUCCUCONREG, MCU_E_PARAM_CPUID);
      ErrorFlag = MCU_ERR_FOUND;
    }
  }
  else
  {
    /* [cover parentID={C968BCDD-D78B-46fc-925D-DB6E79E34F43}]
     * Is Divider value greater than maximum Ccucon value
     * [/cover] */
    if ((uint32)DivVal > MCU_CPU_CCUCON_MAXVAL)
    {
      /* [cover parentID={800AC4DA-BD00-4883-94E8-EA7517DD53C5}]
       * Report DET
       * [/cover] */
      Mcu_lReportError(MCU_SID_UPDCPUCCUCONREG, MCU_E_PARAM_DIV_VAL);
      ErrorFlag = MCU_ERR_FOUND;
    }
  }
  /*[/cover]*/
  /*[cover parentID={2007473A-1AC4-42f6-BCA8-7F01BB77D903}][/cover]*/
  if (MCU_ERR_FOUND != ErrorFlag)
  #endif
  {
    /*
     * Update CCUCONx register divider value corresponding to CpuId.
     */
    /* [cover parentID={CBD07C1A-13C9-4737-847A-F0603F32E7F7}]
     * Update Ccucon x register value according to CPU Id. (x:6-11)
     * [/cover] */
    MCU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG(
      & (MCU_CPU_CCUCON_BASE_ADDR[CpuId]),
      /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
       * by violating this MISRA rule, as the pointer to the object type
       * it is getting cast into is a known type . */
      (uint32)(((uint32)DivVal & MCU_CPU_CCUCON_MAXVAL)));
    /*
     * Add the intended delay after CCUCONx update.
     */
    DeltaTicks  = Mcal_DelayTickResolution();
    CurrSTMTick = Mcal_DelayGetTick();
    BaseSTMTick = CurrSTMTick;
    DeltaTicks  = ((((uint32)Delay) * MCU_STM_TIMER_COMPU_VAL) / DeltaTicks);
    /* [cover parentID={C7063824-59CA-40f6-96F8-45861855CFFD}]
     * Provide intended Delay after Ccucon update
     * [/cover] */
    while ((uint32)((CurrSTMTick - BaseSTMTick) & MCU_STM_TICK_OVERFLOW) <
           DeltaTicks)
    {
      CurrSTMTick = Mcal_DelayGetTick();
    }
  }
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}
#endif /* End of #if (MCU_CPU_CCUCON_UPDATE_API == STD_ON)*/

#if (MCU_INITCHECK_API == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID={5B1D92F0-57CB-4962-AEF9-E996035AD411}]  **
**                                                                            **
** Syntax          : Std_ReturnType Mcu_InitCheck                             **
**                   (                                                        **
**                     const Mcu_ConfigType * const ConfigPtr                 **
**                   )                                                        **
**                                                                            **
** Description     : This function checks whether Mcu_Init is successful      **
**                   or not.                                                  **
**                                                                            **
** Service ID      : 0x5A                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : ConfigPtr - Pointer to configuration set                 **
**                                                                            **
** Parameters (out):                                                          **
**                                                                            **
** Return value    : E_OK     : Mcu Initcheck successful                      **
**                   E_NOT_OK : Mcu Initcheck failed                          **
**                                                                            **
*******************************************************************************/
/*[cover parentID={E9E7877F-B957-480b-9D6D-10CC6AE0AA86}][/cover]*/
/*[cover parentID={F6A07732-3E6D-44a3-9A72-2ECDA65E1335}]SW Safety Measure
[/cover]*/
Std_ReturnType Mcu_InitCheck(const Mcu_ConfigType *const ConfigPtr)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
   defined to modify certain bits and avoid 32-bit mask value.
   No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_PMSWCR1 Pmswcr1Val;

  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_CCUCON0 Ccucon0Val;

  #if (MCU_INIT_CLOCK_API == STD_ON)
  Mcu_SystemPllConfigType PllSource;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_SYSPLLCON0 Syspllcon0Val;

  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
    defined to modify certain bits and avoid 32-bit mask value.
    No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_PERPLLCON0 Perpllcon0Val;
  #endif
  /* End of #if(MCU_INIT_CLOCK_API == STD_ON) */

  uint32 SfrVal;
  uint32 ConfigVal;
  Std_ReturnType CompResult;
  Std_ReturnType RetVal = E_NOT_OK;
  uint32 CmpVal = 0xFFFFFFFFU;
  Ccucon0Val.U = SCU_CCUCON0.U;

  /* [cover parentID={15C9329D-2BD5-4d2a-AE23-AA6B9DA016C1}]
   * Is configuration pointer not NULL, MCU driver initialized
   * and Clocksetting is in range
   * [/cover] */
  if ((Mcu_DriverState == MCU_DRIVER_INITIALIZED) &&
      (ConfigPtr == Mcu_ConfigPtr) &&
      (Mcu_ClockSetting <= Mcu_ConfigPtr->McuNoOfClockCfg))
  {
    Pmswcr1Val.U = (SCU_PMSWCR1.U & MCU_PMSWCR1_VAL_MSK);
    /* [cover parentID={EC1BA793-58F4-48b2-B81B-E4B9CC801F5F}]
     * If Idle mode Core is defined*/
    #if (MCU_IDLE_MODE_CORE != MCU_IDLE_CORE_NOT_DEFINED)
    Pmswcr1Val.B.CPUIDLSEL = MCU_IDLE_MODE_CORE;
    #endif
    /*[/cover] */
    /* [cover parentID={768B50FA-B6E5-42a8-BCA2-CC8755AADE54}]
     * If System mode Core is defined*/
    #if (MCU_SYSTEM_MODE_CORE != MCU_SYSTEM_CORE_NOT_DEFINED)
    Pmswcr1Val.B.CPUSEL = MCU_SYSTEM_MODE_CORE;
    Pmswcr1Val.B.STBYEV = MCU_STANDBY_MODE_ENTRY;
    #endif
    /*[/cover] */
    SfrVal    = SCU_PMSWCR1.U;
    ConfigVal = Pmswcr1Val.U;
    CmpVal   &= ~(SfrVal ^ ConfigVal);

    SfrVal    = SCU_RSTCON.U;
    ConfigVal = (ConfigPtr->McuResetCfg);
    CmpVal   &= ~(SfrVal ^ ConfigVal);

    CompResult = Mcu_lLpmInitCheck();
    CmpVal    &= ~(E_OK ^ (uint32)CompResult);

    SfrVal    = SCU_ARSTDIS.U;
    ConfigVal = (ConfigPtr->McuArstDisCfg);
    CmpVal   &= ~(SfrVal ^ ConfigVal);

    SfrVal    = SCU_TRAPDIS0.U;
    ConfigVal = (ConfigPtr->McuTrapSettingConf0);
    CmpVal   &= ~(SfrVal ^ ConfigVal);
    /* [cover parentID={C4ADDE94-3F0C-4e19-B546-0553B0CFCA4E}]
     * If more than 4 cores are available
     * [/cover] */
    #if (MCAL_NO_OF_ACTIVE_CORES > 4U)
    SfrVal    = SCU_TRAPDIS1.U;
    ConfigVal = (ConfigPtr->McuTrapSettingConf1);
    CmpVal   &= ~(SfrVal ^ ConfigVal);
    #endif

    SfrVal    = SCU_EIFILT.U;
    ConfigVal = (ConfigPtr->McuEruEiFiltCfg);
    CmpVal   &= ~(SfrVal ^ ConfigVal);

    #if (MCU_CCU60_USED == STD_ON)
    SfrVal    = (CCU60_CLC.U & CCU_CLC_MSK);
    if ((boolean)TRUE == Mcu_ConfigPtr->IsCcu60SleepModeEnabled)
    {
      ConfigVal = 0x0U;
    }
    else
    {
      ConfigVal = 0x8U;
    }
    CmpVal   &= ~(SfrVal ^ ConfigVal);

    SfrVal = (CCU60_IS.U & CCU6_IS_MSK);
    ConfigVal = 0x0U;
    CmpVal   &= ~(SfrVal ^ ConfigVal);
    #endif

    #if (MCU_CCU61_USED == STD_ON)
    SfrVal    = (CCU61_CLC.U & CCU_CLC_MSK);
    if ((boolean)TRUE == Mcu_ConfigPtr->IsCcu61SleepModeEnabled)
    {
      ConfigVal = 0x0U;
    }
    else
    {
      ConfigVal = 0x8U;
    }
    CmpVal   &= ~(SfrVal ^ ConfigVal);

    SfrVal = (CCU61_IS.U & CCU6_IS_MSK);
    ConfigVal = 0x0U;
    CmpVal   &= ~(SfrVal ^ ConfigVal);
    #endif

    #if ((MCU_GPT1_USED == STD_ON) || (MCU_GPT2_USED == STD_ON))
    SfrVal    = (GPT120_CLC.U & GPT12_CLC_MSK);
    if ((boolean)TRUE == Mcu_ConfigPtr->IsGpt12SleepModeEnabled)
    {
      ConfigVal = 0x0U;
    }
    else
    {
      ConfigVal = 0x8U;
    }
    CmpVal   &= ~(SfrVal ^ ConfigVal);

    #if (MCU_GPT1_USED == STD_ON)
    SfrVal = (GPT120_T3CON.U & GPT12_TXCON_INITCHECK_MSK);
    CmpVal   &= ~(SfrVal);

    SfrVal = (uint32)GPT120_T3CON.B.BPS1;
    ConfigVal = (uint32)Mcu_ConfigPtr->McuGpt12PreScalarConfigPtr->Gpt1PrescalarDiv;
    CmpVal   &= ~(SfrVal ^ ConfigVal);
    #endif

    #if (MCU_GPT2_USED == STD_ON)
    SfrVal = (GPT120_T6CON.U & GPT12_TXCON_INITCHECK_MSK);
    CmpVal   &= ~(SfrVal);

    SfrVal = (uint32)GPT120_T6CON.B.BPS2;
    ConfigVal = (uint32)Mcu_ConfigPtr->McuGpt12PreScalarConfigPtr->Gpt2PrescalarDiv;
    CmpVal   &= ~(SfrVal ^ ConfigVal);
    #endif
    #endif

    SfrVal    = (uint32)CONVCTRL_CLC.B.DISS;
    ConfigVal = (0U);
    CmpVal   &= ~(SfrVal ^ ConfigVal);

    /* [cover parentID={8D4FC400-AC1D-4057-BE90-39E3D44948DE}]
     * If GTM is available
     * [/cover] */
    #if (MCU_GTM_USED == STD_ON)
    /* [cover parentID={C7448237-7697-4135-8DB4-5C9950508495}]
     * Verify GTM settings against configured value
     * [/cover] */
    /* [cover parentID={BFB3E4F8-665D-4dca-934E-504DEFEE4780}]
     * Is GTM frequency not zero [/cover] */
    if (Ccucon0Val.B.GTMDIV != 0x0U)
    {
      CompResult = Mcu_lGtmGlobalInitCheck();
      CmpVal    &= ~(E_OK ^ (uint32)CompResult);
    }
    #endif

    /* [cover parentID={A9A7E19B-09B0-47fb-947C-F4C2256810A0}]
     * If Mcu Init clock is ON
     * [/cover] */
    #if (MCU_INIT_CLOCK_API == STD_ON)
    PllSource = Mcu_ConfigPtr->
      McuClockSettingPtr[Mcu_ClockSetting].SystemPllCfg;

    /* [cover parentID={7EBA1E57-8B2E-4e50-BA95-8A7F58B89A37}]
     * Is oscillator or SYSCLK selected as clock input
     * [/cover] */
    if (MCU_PLL_INSEL_OSCCLK == (uint32)PllSource.Insel)
    {
      SfrVal    = (SCU_OSCCON.B.MODE);
      ConfigVal = MCU_OSC_MODE;
      CmpVal   &= ~(SfrVal ^ ConfigVal);

      SfrVal    = (SCU_OSCCON.B.OSCVAL);
      ConfigVal = MCU_OSCVAL_REG_VALUE;
      CmpVal   &= ~(SfrVal ^ ConfigVal);
    }
    else if (MCU_PLL_INSEL_BACKUP == (uint32)PllSource.Insel)
    {
      SfrVal    = (SCU_OSCCON.B.MODE);
      ConfigVal = MCU_OSC_DIS_POWERSAVING_MODE;
      CmpVal   &= ~(SfrVal ^ ConfigVal);
    }
    else
    {
      SfrVal    = (SCU_OSCCON.B.MODE);
      ConfigVal = MCU_OSC_DIS_POWERSAVING_MODE;
      CmpVal   &= ~(SfrVal ^ ConfigVal);

      SfrVal    = (SCU_OSCCON.B.OSCVAL);
      ConfigVal = MCU_SYSCLK_OSCVAL;
      CmpVal   &= ~(SfrVal ^ ConfigVal);
    }

    /* [cover parentID={D6ADA084-78F7-46a6-8D72-88E46553B291}]
     * Is PLL selected for clock distribution [/cover] */
    if (Ccucon0Val.B.CLKSEL == 0x1U)
    {
      Syspllcon0Val.U = MCU_SYSPLLCON_DEFAULT_VAL;
      Syspllcon0Val.B.NDIV = ConfigPtr->McuClockSettingPtr
                             [Mcu_ClockSetting].SystemPllCfg.SysPllNDiv;
      Syspllcon0Val.B.PDIV = ConfigPtr->McuClockSettingPtr
                             [Mcu_ClockSetting].SystemPllCfg.SysPllPDiv;
      Syspllcon0Val.B.INSEL = ConfigPtr->McuClockSettingPtr
                              [Mcu_ClockSetting].SystemPllCfg.Insel;
      Syspllcon0Val.B.PLLPWD = 0x1U;
      Syspllcon0Val.B.MODEN  = Mcu_ConfigPtr->McuClockSettingPtr
                               [Mcu_ClockSetting].SystemPllCfg.FmPllEn;

      SfrVal    = (SCU_SYSPLLCON0.U);
      ConfigVal = Syspllcon0Val.U;
      CmpVal   &= ~(SfrVal ^ ConfigVal);

      SfrVal    = (SCU_SYSPLLCON1.U);
      ConfigVal = ConfigPtr->McuClockSettingPtr
                  [Mcu_ClockSetting].SystemPllCfg.SysPllK2Div;
      CmpVal   &= ~(SfrVal ^ ConfigVal);

      /* [cover parentID={2C60DFC6-C382-4ac0-887D-FCE0B91A96A2}]
       * Is modulation enabled
       * [/cover] */
      if (0x1U == ConfigPtr->McuClockSettingPtr
          [Mcu_ClockSetting].SystemPllCfg.FmPllEn)
      {
        SfrVal    = (SCU_SYSPLLCON2.U);
        ConfigVal = ConfigPtr->McuClockSettingPtr
                    [Mcu_ClockSetting].SystemPllCfg.ModulationAmplitude;
        CmpVal   &= ~(SfrVal ^ ConfigVal);
      }

      Perpllcon0Val.U       = MCU_PERPLLCON_DEFAULT_VAL;
      Perpllcon0Val.B.DIVBY = ConfigPtr->McuClockSettingPtr
                              [Mcu_ClockSetting].PeripheralPllCfg.K3DivByPass;
      Perpllcon0Val.B.NDIV  = ConfigPtr->McuClockSettingPtr
                              [Mcu_ClockSetting].PeripheralPllCfg.PerPllNDiv;
      Perpllcon0Val.B.PDIV  = ConfigPtr->McuClockSettingPtr
                              [Mcu_ClockSetting].PeripheralPllCfg.PerPllPDiv;
      Perpllcon0Val.B.PLLPWD = 0x1U;

      SfrVal    = (SCU_PERPLLCON0.U);
      ConfigVal = Perpllcon0Val.U;
      CmpVal   &= ~(SfrVal ^ ConfigVal);

      SfrVal    = (SCU_PERPLLCON1.B.K2DIV);
      ConfigVal = ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
                  .PeripheralPllCfg.PerPllK2Div;
      CmpVal   &= ~(SfrVal ^ ConfigVal);

      SfrVal    = (SCU_PERPLLCON1.B.K3DIV);
      ConfigVal = ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
                  .PeripheralPllCfg.PerPllK3Div;
      CmpVal   &= ~(SfrVal ^ ConfigVal);
    }

    SfrVal    = (CONVCTRL_PHSCFG.B.PHSDIV);
    ConfigVal = ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
                .ConvCtrlBlockConf;
    CmpVal   &= ~(SfrVal ^ ConfigVal);

    SfrVal    = (SCU_CCUCON6.U);
    ConfigVal = ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
                .PllDistributionCfgPtr->CcuconCpu[0];
    CmpVal   &= ~(SfrVal ^ ConfigVal);
    /* [cover parentID={1E0B8164-6DFC-4ac7-97D5-F4457D496F67}]
     * If more than 1 core is available
     * [/cover] */
    #if (MCAL_NO_OF_ACTIVE_CORES > 1U)
    SfrVal    = (SCU_CCUCON7.U);
    ConfigVal = ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
                .PllDistributionCfgPtr->CcuconCpu[1];
    CmpVal   &= ~(SfrVal ^ ConfigVal);
    #endif
    /* [cover parentID={F43BE123-1A98-4833-8FCB-F861BC2F2B7A}]
     * If more than 2 core is available
     * [/cover] */
    #if (MCAL_NO_OF_ACTIVE_CORES > 2U)
    SfrVal    = (SCU_CCUCON8.U);
    ConfigVal = ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
                .PllDistributionCfgPtr->CcuconCpu[2];
    CmpVal   &= ~(SfrVal ^ ConfigVal);
    #endif
    /* [cover parentID={091EB9C5-9181-4d1f-BA29-1DD6D0789029}]
     * If more than 3 cores are available
     * [/cover] */
    #if (MCAL_NO_OF_ACTIVE_CORES > 3U)
    SfrVal    = (SCU_CCUCON9.U);
    ConfigVal = ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
                .PllDistributionCfgPtr->CcuconCpu[3];
    CmpVal   &= ~(SfrVal ^ ConfigVal);
    #endif
    /* [cover parentID={EE242DD5-047A-4fbf-9BD6-E88BD77BAAC3}]
     * If more than 4 cores are available
     * [/cover] */
    #if (MCAL_NO_OF_ACTIVE_CORES > 4U)
    SfrVal    = (SCU_CCUCON10.U);
    ConfigVal = ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
                .PllDistributionCfgPtr->CcuconCpu[4];
    CmpVal   &= ~(SfrVal ^ ConfigVal);
    #endif
    /* [cover parentID={5168E2FD-F273-4f27-8A55-485CF186DF60}]
     * If more than 5 cores are available
     * [/cover] */
    #if (MCAL_NO_OF_ACTIVE_CORES > 5U)
    SfrVal    = (SCU_CCUCON11.U);
    ConfigVal = ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
                .PllDistributionCfgPtr->CcuconCpu[5];
    CmpVal   &= ~(SfrVal ^ ConfigVal);
    #endif

    SfrVal    = (SCU_CCUCON1.U) & 0x7FFFFFFFU;
    ConfigVal = ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
                .PllDistributionCfgPtr->Ccucon1;
    CmpVal   &= ~(SfrVal ^ ConfigVal);

    SfrVal    = (SCU_CCUCON2.U) & 0x7FFFFFFFU;
    ConfigVal = ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
                .PllDistributionCfgPtr->Ccucon2;
    CmpVal   &= ~(SfrVal ^ ConfigVal);

    SfrVal    = (SCU_CCUCON0.U) & 0x3FFFFFFFU;
    ConfigVal = ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
                .PllDistributionCfgPtr->Ccucon0;
    CmpVal   &= ~(SfrVal ^ ConfigVal);

    SfrVal    = (SCU_CCUCON5.U) & 0x3FFFFFFFU;
    ConfigVal = ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
                .PllDistributionCfgPtr->Ccucon5;
    CmpVal   &= ~(SfrVal ^ ConfigVal);

    SfrVal    = SCU_EXTCON.U;
    ConfigVal = ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
                .ExternalClockCfg;
    CmpVal   &= ~(SfrVal ^ ConfigVal);
    /* [cover parentID={7E45CD24-DD9E-478d-824F-13FE2B25043B}]
     *  If Safety is Enabled
     * [/cover] */
    #if (MCU_SAFETY_ENABLE == STD_ON)
    SfrVal    = (SCU_CCUCON3.U) & 0x3FFFFFFFU;
    ConfigVal = ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
                .PllDistributionCfgPtr->Ccucon3;
    CmpVal   &= ~(SfrVal ^ ConfigVal);

    SfrVal    = (SCU_CCUCON4.U) & 0x3FFFFFFFU;
    ConfigVal = (ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
                 .PllDistributionCfgPtr->Ccucon4) &
                0x3FFFFFFFU;
    CmpVal   &= ~(SfrVal ^ ConfigVal);
    #endif
    /* End of #if (MCU_SAFETY_ENABLE == STD_ON) */
    #endif
    /* End of #if(MCU_INIT_CLOCK_API == STD_ON) */
    /* [cover parentID={09A2F02C-C203-40be-AF49-FF4D6348E986}]
     * Are all verifications successful
     * [/cover] */
    if (CmpVal == 0xFFFFFFFFU)
    {
      RetVal = E_OK;
    }
  }

  return RetVal;
}
#endif
/* End of #if (MCU_INITCHECK_API == STD_ON) */

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
#if (MCU_GTM_USED == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={CA735F33-C59C-436e-9225-F8EA47ACF0D3}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType Mcu_lGtmGlobalInit (void)    **
**                                                                            **
** Description     : This function performs GTM global initialization.        **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK : GTM global initialization successful.             **
**                   E_NOT_OK : GTM global initialization failed.             **
**                                                                            **
*******************************************************************************/
/*[cover parentID={D50B4A4A-DE2D-4ca6-8C73-6981ACDF402B}][/cover]*/
LOCAL_INLINE Std_ReturnType Mcu_lGtmGlobalInit(void)
{

  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_GTM_CLC GtmClcVal;
  Std_ReturnType GtmInitStatus = E_NOT_OK;

  /*
    GTM Global initialization
    1. Enable GTM module clock.
    2. Once GTM module is disabled, setup GTM internal (global) register
       configurations.
  */

  GtmClcVal.U = GTM_CLC.U;
  GtmClcVal.B.DISR = 0x0U;

  /* [cover parentID={3424907A-D37A-44e2-B303-00C9606D1C38}]
   * Sleep mode is Enabled
   * [/cover] */
  if ((boolean)TRUE == Mcu_ConfigPtr->McuGtmConfigPtr->IsGtmSleepModeEnabled)
  {
    GtmClcVal.B.EDIS = 0x0U;
  }
  else
  {
    /*GTM_CLC.B.EDIS = 0x1U;*/
    GtmClcVal.B.EDIS = 0x1U;
  }
  MCU_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(&GTM_CLC.U, GtmClcVal.U);

  /* [cover parentID={22D6A0F8-53AB-41a0-AEF1-A74B976DD3AA}]
   * GTM module is Enabled
   * [/cover] */
  if (MCU_GTM_MODULE_ENABLE == (uint32)GTM_CLC.B.DISS)
  {
    /* [cover parentID={75B4CDF9-2C7D-49e5-9B8D-A4BEA5A17588}]
     * If Production error Reporting is ON*/
    #if (MCU_E_GTM_CLC_ENABLE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
    /*Report Production error for GTM enable passed*/
    /* [cover parentID={F332F740-976D-4fa8-AEE0-CC43E0015CA0}]
     * Report Production error: Event Passed
     * [/cover] */
    Mcu_lReportDemError(MCU_E_GTM_CLC_ENABLE_ERR, DEM_EVENT_STATUS_PASSED);
    #endif
    /* Initialize various GTM sub-modules */
    /* [cover parentID={8F591719-3B5C-4164-9DA4-4D3DF9F02DD9}]
     * Initialize Clock management Unit
     * [/cover] */
    Mcu_lGtmCmuGlobalInit();
    /* [cover parentID={2DCB59DB-C0FB-4d4b-9D83-8D9016DCE6AD}]
     * Initialize Time Base Unit
     * [/cover] */
    Mcu_lGtmTbuGlobalInit();
    /* [cover parentID={0B1CBD90-B4D7-4512-9738-F7174B02BE23}]
     * Initialize Cluster configuration module
     * [/cover] */
    Mcu_lGtmCcmGlobalInit();
    /* [cover parentID={FC5300FD-3F19-4761-856C-9305FD5BFC90}]
     * Initialize TOM module
     * [/cover] */
    Mcu_lGtmTomGlobalInit();
    /* [cover parentID={02B62AF5-761D-405c-B8B5-E6E77C627713}]
     * Initialize ATOM module
     * [/cover] */
    Mcu_lGtmAtomGlobalInit();
    /* [cover parentID={C3896F6A-D150-4277-B429-836C2DF2AE0F}]
     * Initialize GTM to ADC trigger
     * [/cover] */
    Mcu_lGtmTriggerInit();
    /* [cover parentID={65F0419A-11CF-485b-9662-D6E227EB5329}]
     * Initialize Toutselx registers
     * [/cover] */
    Mcu_lGtmToutSelInit();

    Mcu_lGtmTimInselInit();
    GtmInitStatus = E_OK;
  }
  else
  {
    #if (MCU_E_GTM_CLC_ENABLE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
    /*Report Production error for GTM enable error*/
    /*[cover parentID={DB971738-669E-4adf-9860-55AB1412C102} ]
    [/cover]*/
    /* [cover parentID={8D8985C7-A014-44a0-8144-A168E375FB53}]
     * Report Production error: Event failed
     * [/cover] */
    Mcu_lReportDemError(MCU_E_GTM_CLC_ENABLE_ERR, DEM_EVENT_STATUS_FAILED);
    #endif
    /*[/cover] */
  }
  /*[cover parentID={EF8DD776-51FA-4870-8319-5436E54D1D6E}][/cover]
    [cover parentID={7FB62725-7D91-43bd-B0B8-517D707E2DC4} ][/cover]*/
  return GtmInitStatus;
}

#if (MCU_DEINIT_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={458CD4BA-ED0F-43e0-AE7F-6CF220E16A01}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType Mcu_lGtmGlobalDeInit (void)  **
**                                                                            **
** Description     : This function performs GTM global de-initialization.     **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK : GTM global de-initialization successful.          **
**                   E_NOT_OK : GTM global de-initialization failed.          **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Mcu_lGtmGlobalDeInit(void)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_GTM_CLC GtmClcVal;
  Std_ReturnType GtmDeInitStatus = E_NOT_OK;

  /* [cover parentID={A2737666-F0E0-4945-B69E-AA5D504B4D74}]
   * De-Initialize TOUTSELx
   * [/cover] */
  Mcu_lGtmToutSelDeInit();
  /* [cover parentID={9B56D035-5638-45e7-B9CF-2846544FE625}]
   * De-Initialize TIMINSELx
   * [/cover] */
  Mcu_lGtmTimInselDeInit();
  /*Disable GTM module*/
  /* [cover parentID={BE19B839-010E-43e8-8582-5C5DFB9A95BD}]
   * De-Initialize TOM module
   * [/cover] */
  Mcu_lGtmTomGlobalDeInit();
  /* [cover parentID={BE021722-5E3E-454e-8931-8425BD72685F}]
   * De-initialize ATOM module
   * [/cover] */
  Mcu_lGtmAtomGlobalDeInit();
  /* [cover parentID={65763936-9BE8-40fa-ABFC-DB4E22DB597D}]
   * De-initialize GTM to ADC Trigger
   * [/cover] */
  Mcu_lGtmTriggerDeInit();
  /* [cover parentID={87B696C9-67E6-445b-95FF-B8071343F857}]
   * De-initialize CCM module
   * [/cover] */
  Mcu_lGtmCcmGlobalDeInit();
  /* [cover parentID={C64A5400-1C44-464a-891B-D28F87216156}]
   * De-initialize TBU channels
   * [/cover] */
  Mcu_lGtmTbuGlobalDeInit();
  /* [cover parentID={C6CBD159-2A1E-4fb2-8C3C-908432ED2868}]
   * De-initialize GTM Clock Management Unit
   * [/cover] */
  Mcu_lGtmCmuGlobalDeInit();
  GtmClcVal.U      = GTM_CLC.U;
  GtmClcVal.B.DISR = 0x1U;
  GtmClcVal.B.EDIS = 0x0U;
  MCU_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(&GTM_CLC.U, (uint32)GtmClcVal.U);

  /* [cover parentID={6D1BC91F-826C-4ea3-A6E0-4156F7BA6EDC}]
   * Is GTM Module clock is not disabled
   * [/cover] */
  if (MCU_GTM_MODULE_DISABLE == (uint32)GTM_CLC.B.DISS)
  {
    /* [cover parentID={AD9EFCF0-BFF2-4fe8-887E-4BC226C6A3BE}]
     * If Production error Reporting is ON*/
    #if (MCU_E_GTM_CLC_DISABLE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
    /*Report Production error for GTM module disable passed*/
    /*[cover parentID={306D1B8B-A598-4a6f-BA97-3D14E1C483C7} ][/cover]*/
    /* [cover parentID={531E0FF0-6879-4ed5-9568-33B5533754F7}]
     * Report Production error: Event Passed
     * [/cover] */
    Mcu_lReportDemError(MCU_E_GTM_CLC_DISABLE_ERR,
                          DEM_EVENT_STATUS_PASSED);
    #endif
    GtmDeInitStatus = E_OK;
  }
  #if (MCU_E_GTM_CLC_DISABLE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
  else
  {
    /*Report Production error for GTM module disable error*/
    /* [cover parentID={01F83276-AB42-412f-9F74-EE9D588B30D0}]
     * Report Production error: Event Failed
     * [/cover] */
    Mcu_lReportDemError(MCU_E_GTM_CLC_DISABLE_ERR, DEM_EVENT_STATUS_FAILED);
  }
  #endif
  /*[/cover] */
  /*[cover parentID={0C2FF629-EEDC-4483-AA6F-A38367BC61B7}][/cover]
    [cover parentID={B5D7C746-B073-4c94-870B-692B9C5871F9}][/cover]*/
  return GtmDeInitStatus;
}
#endif

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={F0ECB1D5-EAC3-4a99-B1AF-92475E49DBAA}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE void Mcu_lGtmCmuGlobalInit(void)            **
**                                                                            **
** Description     : This function performs GTM clock initialization          **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/

LOCAL_INLINE void Mcu_lGtmCmuGlobalInit(void)
{
  volatile uint32 ReadBack;
  uint32 TempVal;

  /*Disable all clock sources before changing control
    registers, numerator and denominators registers */
  GTM_CMU_CLK_EN.U = MCU_GTM_CMU_CLK_DISABLE;
  /*
    Update Global Numerator and Denominator for CMU Global Clock
    Numerator is written twice before writing into Denominator
    This is secure way of updating these registers as per TS.
  */
  GTM_CMU_GCLK_NUM.U = Mcu_ConfigPtr->McuGtmConfigPtr->
                       GtmClockCfgPtr->GtmCmuGlobalNumerator;
  GTM_CMU_GCLK_NUM.U = Mcu_ConfigPtr->McuGtmConfigPtr->
                       GtmClockCfgPtr->GtmCmuGlobalNumerator;
  GTM_CMU_GCLK_DEN.U = Mcu_ConfigPtr->McuGtmConfigPtr->
                       GtmClockCfgPtr->GtmCmuGlobalDenominator;

  /* Write CMU clock control registers for all possible clocks*/
  GTM_CMU_CLK_0_CTRL.U = Mcu_ConfigPtr->McuGtmConfigPtr->
                         GtmClockCfgPtr->GtmCmuConfClkCtrl[0];
  GTM_CMU_CLK_1_CTRL.U = Mcu_ConfigPtr->McuGtmConfigPtr->
                         GtmClockCfgPtr->GtmCmuConfClkCtrl[1];
  GTM_CMU_CLK_2_CTRL.U = Mcu_ConfigPtr->McuGtmConfigPtr->
                         GtmClockCfgPtr->GtmCmuConfClkCtrl[2];
  GTM_CMU_CLK_3_CTRL.U = Mcu_ConfigPtr->McuGtmConfigPtr->
                         GtmClockCfgPtr->GtmCmuConfClkCtrl[3];
  GTM_CMU_CLK_4_CTRL.U = Mcu_ConfigPtr->McuGtmConfigPtr->
                         GtmClockCfgPtr->GtmCmuConfClkCtrl[4];
  GTM_CMU_CLK_5_CTRL.U = Mcu_ConfigPtr->McuGtmConfigPtr->
                         GtmClockCfgPtr->GtmCmuConfClkCtrl[5];
  GTM_CMU_CLK_6_CTRL.U = Mcu_ConfigPtr->McuGtmConfigPtr->
                         GtmClockCfgPtr->GtmCmuConfClkCtrl[6];
  GTM_CMU_CLK_7_CTRL.U = Mcu_ConfigPtr->McuGtmConfigPtr->
                         GtmClockCfgPtr->GtmCmuConfClkCtrl[7];
  /*
    Numerator is written twice before writing into Denominator
    This is secure way of updating these registers as per TS.
   */
  GTM_CMU_ECLK_0_NUM.U = Mcu_ConfigPtr->McuGtmConfigPtr->
                         GtmClockCfgPtr->GtmEclkCtrl[0].GtmCmuExtClockNum;
  GTM_CMU_ECLK_0_NUM.U = Mcu_ConfigPtr->McuGtmConfigPtr->
                         GtmClockCfgPtr->GtmEclkCtrl[0].GtmCmuExtClockNum;
  GTM_CMU_ECLK_0_DEN.U = Mcu_ConfigPtr->McuGtmConfigPtr->
                         GtmClockCfgPtr->GtmEclkCtrl[0].GtmCmuExtClockDen;

  GTM_CMU_ECLK_1_NUM.U = Mcu_ConfigPtr->McuGtmConfigPtr->
                         GtmClockCfgPtr->GtmEclkCtrl[1].GtmCmuExtClockNum;
  GTM_CMU_ECLK_1_NUM.U = Mcu_ConfigPtr->McuGtmConfigPtr->
                         GtmClockCfgPtr->GtmEclkCtrl[1].GtmCmuExtClockNum;
  GTM_CMU_ECLK_1_DEN.U = Mcu_ConfigPtr->McuGtmConfigPtr->
                         GtmClockCfgPtr->GtmEclkCtrl[1].GtmCmuExtClockDen;

  GTM_CMU_ECLK_2_NUM.U = Mcu_ConfigPtr->McuGtmConfigPtr->
                         GtmClockCfgPtr->GtmEclkCtrl[2].GtmCmuExtClockNum;
  GTM_CMU_ECLK_2_NUM.U = Mcu_ConfigPtr->McuGtmConfigPtr->
                         GtmClockCfgPtr->GtmEclkCtrl[2].GtmCmuExtClockNum;
  GTM_CMU_ECLK_2_DEN.U = Mcu_ConfigPtr->McuGtmConfigPtr->
                         GtmClockCfgPtr->GtmEclkCtrl[2].GtmCmuExtClockDen;
  /* Configure CMU fixed clock settings */
  GTM_CMU_FXCLK_CTRL.U = Mcu_ConfigPtr->McuGtmConfigPtr->
                         GtmClockCfgPtr->GtmCmuFixedClkCtrl;
  /* Cluster0 input clock divider configuration */
  TempVal = (uint32)GTM_CTRL.B.RF_PROT;
  GTM_CTRL.B.RF_PROT = 0x0U;
  ReadBack = GTM_CTRL.U;
  GTM_CLS_CLK_CFG.U = Mcu_ConfigPtr->McuGtmConfigPtr->
                      GtmClockCfgPtr->GtmCmuClsInDiv;
  /* MISRA2012_RULE_10_3_JUSTIFICATION: Assignment to narrower type as
     a register bit-field value (RF_PROT: 1bit wide) is written and possible
     write values are either 0U or 1U. */
  GTM_CTRL.B.RF_PROT = TempVal;

  /* Enable all clocks as per the configuration */
  GTM_CMU_CLK_EN.U = Mcu_ConfigPtr->McuGtmConfigPtr->
                     GtmClockCfgPtr->GtmCmuClockEnable;
  UNUSED_PARAMETER(ReadBack);
}

#if (MCU_DEINIT_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={1C86BBD2-45A6-4a37-94AF-263A1685EC7D}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE void Mcu_lGtmCmuGlobalDeInit(void)          **
**                                                                            **
** Description     : This function performs GTM clock de-initialization       **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Mcu_lGtmCmuGlobalDeInit(void)
{
  volatile uint32 ReadBack;
  uint32          TempVal;

  /* Disable all clock sources before changing control
   * registers, numerator and denominators registers */
  GTM_CMU_CLK_EN.U = MCU_GTM_CMU_CLK_DISABLE;
  /*
   * Update Global Numerator and Denominator for CMU Global Clock
   * Numerator is written twice before writing into Denominator
   * This is secure way of updating these registers as per TS.
   */
  GTM_CMU_GCLK_NUM.U = MCU_GTM_CMU_GCLK_NUM_RESET_VAL;
  GTM_CMU_GCLK_NUM.U = MCU_GTM_CMU_GCLK_NUM_RESET_VAL;
  GTM_CMU_GCLK_DEN.U = MCU_GTM_CMU_GCLK_DEN_RESET_VAL;

  /* Write CMU clock control registers for all possible clocks*/
  GTM_CMU_CLK_0_CTRL.U = MCU_GTM_CMU_CLK_CTRL_RESET_VAL;
  GTM_CMU_CLK_1_CTRL.U = MCU_GTM_CMU_CLK_CTRL_RESET_VAL;
  GTM_CMU_CLK_2_CTRL.U = MCU_GTM_CMU_CLK_CTRL_RESET_VAL;
  GTM_CMU_CLK_3_CTRL.U = MCU_GTM_CMU_CLK_CTRL_RESET_VAL;
  GTM_CMU_CLK_4_CTRL.U = MCU_GTM_CMU_CLK_CTRL_RESET_VAL;
  GTM_CMU_CLK_5_CTRL.U = MCU_GTM_CMU_CLK_CTRL_RESET_VAL;
  GTM_CMU_CLK_6_CTRL.U = MCU_GTM_CMU_CLK_CTRL_RESET_VAL;
  GTM_CMU_CLK_7_CTRL.U = MCU_GTM_CMU_CLK_CTRL_RESET_VAL;
  /*
   * Numerator is written twice before writing into Denominator
   * This is secure way of updating these registers as per TS.
   */
  GTM_CMU_ECLK_0_NUM.U = MCU_GTM_CMU_ECLK_NUM_RESET_VAL;
  GTM_CMU_ECLK_0_NUM.U = MCU_GTM_CMU_ECLK_NUM_RESET_VAL;
  GTM_CMU_ECLK_0_DEN.U = MCU_GTM_CMU_ECLK_DEN_RESET_VAL;

  GTM_CMU_ECLK_1_NUM.U = MCU_GTM_CMU_ECLK_NUM_RESET_VAL;
  GTM_CMU_ECLK_1_NUM.U = MCU_GTM_CMU_ECLK_NUM_RESET_VAL;
  GTM_CMU_ECLK_1_DEN.U = MCU_GTM_CMU_ECLK_DEN_RESET_VAL;

  GTM_CMU_ECLK_2_NUM.U = MCU_GTM_CMU_ECLK_NUM_RESET_VAL;
  GTM_CMU_ECLK_2_NUM.U = MCU_GTM_CMU_ECLK_NUM_RESET_VAL;
  GTM_CMU_ECLK_2_DEN.U = MCU_GTM_CMU_ECLK_DEN_RESET_VAL;
  /* Configure CMU fixed clock settings */
  GTM_CMU_FXCLK_CTRL.U = MCU_GTM_CMU_FXCLK_CTRL_RESET_VAL;
  /* Cluster0 input clock divider configuration */
  TempVal = (uint32)GTM_CTRL.B.RF_PROT;
  GTM_CTRL.B.RF_PROT = 0x0U;
  ReadBack = GTM_CTRL.U;
  GTM_CLS_CLK_CFG.U = MCU_GTM_CLS_CLK_CFG_RESET_VAL;
  /* MISRA2012_RULE_10_3_JUSTIFICATION: Assignment to narrower type as
   a register bit-field value (RF_PROT: 1bit wide) is written and possible
   write values are either 0U or 1U. */
  GTM_CTRL.B.RF_PROT = TempVal;

  /* Enable all clocks as per the configuration */
  UNUSED_PARAMETER(ReadBack);
}
#endif

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={87A83D0E-9C25-4aeb-9615-40A2ED01F948}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE void Mcu_lGtmTriggerInit(void)              **
**                                                                            **
** Description     : Function that initializes the GTM triggering             **
**                   configuration settings.                                  **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={C0F73721-E73F-4445-B04C-813F73AB0716}][/cover]*/
LOCAL_INLINE void Mcu_lGtmTriggerInit(void)
{
  /*
     Configure GTM ADC trigger configuration registers. Default value (0U) is
     written (generated via code template configuration file) for trigger
     registers corresponding to non-existent ADC kernel in a given device.
  */

  GTM_ADCTRIG0OUT0.U = Mcu_ConfigPtr->McuGtmConfigPtr->GtmAdcTrigCfg[0]
                       .GtmAdcTrigOut0;
  GTM_ADCTRIG0OUT1.U = Mcu_ConfigPtr->McuGtmConfigPtr->GtmAdcTrigCfg[0]
                       .GtmAdcTrigOut1;
  GTM_ADCTRIG1OUT0.U = Mcu_ConfigPtr->McuGtmConfigPtr->GtmAdcTrigCfg[1]
                       .GtmAdcTrigOut0;
  GTM_ADCTRIG1OUT1.U = Mcu_ConfigPtr->McuGtmConfigPtr->GtmAdcTrigCfg[1]
                       .GtmAdcTrigOut1;
  GTM_ADCTRIG2OUT0.U = Mcu_ConfigPtr->McuGtmConfigPtr->GtmAdcTrigCfg[2]
                       .GtmAdcTrigOut0;
  GTM_ADCTRIG2OUT1.U = Mcu_ConfigPtr->McuGtmConfigPtr->GtmAdcTrigCfg[2]
                       .GtmAdcTrigOut1;
  GTM_ADCTRIG3OUT0.U = Mcu_ConfigPtr->McuGtmConfigPtr->GtmAdcTrigCfg[3]
                       .GtmAdcTrigOut0;
  GTM_ADCTRIG3OUT1.U = Mcu_ConfigPtr->McuGtmConfigPtr->GtmAdcTrigCfg[3]
                       .GtmAdcTrigOut1;
  GTM_ADCTRIG4OUT0.U = Mcu_ConfigPtr->McuGtmConfigPtr->GtmAdcTrigCfg[4]
                       .GtmAdcTrigOut0;
  GTM_ADCTRIG4OUT1.U = Mcu_ConfigPtr->McuGtmConfigPtr->GtmAdcTrigCfg[4]
                       .GtmAdcTrigOut1;

  /*
     Configure GTM DSADC trigger configuration registers. Default value (0U) is
     written (generated via code template configuration file) for trigger
     registers corresponding to non-existent DSADC kernel in a given device.
  */
  #if (MCU_GTM_TO_DSADC_TRIG_AVAILABLE == STD_ON)
  GTM_DSADCOUTSEL00.U = Mcu_ConfigPtr->McuGtmConfigPtr->GtmDsadcTrigCfg[0]
                       .GtmDsadcTrigOut0;
  GTM_DSADCOUTSEL10.U = Mcu_ConfigPtr->McuGtmConfigPtr->GtmDsadcTrigCfg[1]
                       .GtmDsadcTrigOut0;
  GTM_DSADCOUTSEL20.U = Mcu_ConfigPtr->McuGtmConfigPtr->GtmDsadcTrigCfg[2]
                       .GtmDsadcTrigOut0;
  GTM_DSADCOUTSEL30.U = Mcu_ConfigPtr->McuGtmConfigPtr->GtmDsadcTrigCfg[3]
                       .GtmDsadcTrigOut0;
  #if (MCU_GTM_TO_DSADC_TRIG1 == STD_ON)
  GTM_DSADCOUTSEL01.U = Mcu_ConfigPtr->McuGtmConfigPtr->GtmDsadcTrigCfg[0]
                       .GtmDsadcTrigOut1;
  GTM_DSADCOUTSEL11.U = Mcu_ConfigPtr->McuGtmConfigPtr->GtmDsadcTrigCfg[1]
                       .GtmDsadcTrigOut1;
  GTM_DSADCOUTSEL21.U = Mcu_ConfigPtr->McuGtmConfigPtr->GtmDsadcTrigCfg[2]
                       .GtmDsadcTrigOut1;
  GTM_DSADCOUTSEL31.U = Mcu_ConfigPtr->McuGtmConfigPtr->GtmDsadcTrigCfg[3]
                       .GtmDsadcTrigOut1;
  #endif
  #endif /*End of (MCU_GTM_TO_DSADC_TRIG_AVAILABLE == STD_ON)*/
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={889CBC14-0B14-4a03-959B-0D9AACECAC6A}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE void Mcu_lGtmToutSelInit(void)              **
**                                                                            **
** Description     : Function that initializes the GTM to port                **
**                   configuration settings.                                  **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={C0F73721-E73F-4445-B04C-813F73AB0716}][/cover]*/
LOCAL_INLINE void Mcu_lGtmToutSelInit(void)
{
  /*
     Configure GTM TOUTSEL configuration registers.
  */
  uint8 ToutSelRegIndex;

  /*[cover parentID={90AB3615-CEB9-4208-9B9B-51C7766243C1}][/cover]*/
  /*[cover parentID={4C4A4DA3-F8CC-49ea-A0F9-713AA6673C0B}][/cover]*/
  for (ToutSelRegIndex = MCU_STARTING_INDEX;
       ToutSelRegIndex < MCU_GTM_NO_OF_TOUTSEL_AVAILABLE; ToutSelRegIndex++)
  {
    MODULE_GTM.TOUTSEL[ToutSelRegIndex].U &= (~(Mcu_ConfigPtr->McuGtmConfigPtr
                                          ->GtmToutSelCfgMsk[ToutSelRegIndex]));
    MODULE_GTM.TOUTSEL[ToutSelRegIndex].U |= Mcu_ConfigPtr->McuGtmConfigPtr
                                             ->GtmToutSelCfg[ToutSelRegIndex];
  }
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={3455F71F-CEE3-4465-A43F-BF5BC0072EC0}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE void Mcu_lGtmTimInselInit(void)             **
**                                                                            **
** Description     : Function that initializes the Port to GTM TIM            **
**                   configuration settings.                                  **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={C0F73721-E73F-4445-B04C-813F73AB0716}][/cover]*/
LOCAL_INLINE void Mcu_lGtmTimInselInit(void)
{
  /*
     Configure GTM TIMINSEL configuration registers.
  */
  uint8 TimInSelRegIndex;

  /*[cover parentID={D9667840-AC80-445c-98F1-5ED59E39EF12}][/cover]*/
  for (TimInSelRegIndex = MCU_STARTING_INDEX;
       TimInSelRegIndex < MCU_GTM_NO_OF_TIM_AVAILABLE; TimInSelRegIndex++)
  {
    MODULE_GTM.TIMINSEL[TimInSelRegIndex].U |= Mcu_ConfigPtr->McuGtmConfigPtr
                                             ->GtmTimInSelCfg[TimInSelRegIndex];
  }
}

#if (MCU_DEINIT_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={44A09A2F-B54F-4fb7-AF14-F777400DBD05}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE void Mcu_lGtmToutSelDeInit(void)            **
**                                                                            **
** Description     : Function that resets the GTM to port configuration       **
**                   settings.                                                **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={C0F73721-E73F-4445-B04C-813F73AB0716}][/cover]*/
LOCAL_INLINE void Mcu_lGtmToutSelDeInit(void)
{
  /*
     Configure GTM TOUTSEL configuration registers.
  */
  uint8 ToutSelRegIndex;

  /*[cover parentID={A3C93AE3-0B27-412b-B563-83DD8363ECFD}][/cover]*/
  for (ToutSelRegIndex = MCU_STARTING_INDEX;
       ToutSelRegIndex < MCU_GTM_NO_OF_TOUTSEL_AVAILABLE; ToutSelRegIndex++)
  {
    MODULE_GTM.TOUTSEL[ToutSelRegIndex].U &=
    (~(Mcu_ConfigPtr->McuGtmConfigPtr->GtmToutSelCfg[ToutSelRegIndex]));

  }
}
#endif
/* End of #if (MCU_DEINIT_API == STD_ON) */

#if (MCU_DEINIT_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={6941873D-2B9B-4dc7-A9BE-60F9E3CD0935}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE void Mcu_lGtmTimInselDeInit(void)           **
**                                                                            **
** Description     : Function that resets the Port to GTM TIM configuration   **
**                   settings.                                                **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={C0F73721-E73F-4445-B04C-813F73AB0716}][/cover]*/
LOCAL_INLINE void Mcu_lGtmTimInselDeInit(void)
{
  /*
     Configure GTM TIMINSEL configuration registers.
  */
  uint8 TimInSelRegIndex;

  for (TimInSelRegIndex = MCU_STARTING_INDEX;
       TimInSelRegIndex < MCU_GTM_NO_OF_TIM_AVAILABLE; TimInSelRegIndex++)
  {
    MODULE_GTM.TIMINSEL[TimInSelRegIndex].U &=
    (~(Mcu_ConfigPtr->McuGtmConfigPtr->GtmTimInSelCfg[TimInSelRegIndex]));
  }
}
#endif
/* End of #if (MCU_DEINIT_API == STD_ON) */

#if (MCU_DEINIT_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={8704A0B8-E6C9-4752-A535-CEF12C345768}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE void Mcu_lGtmTriggerDeInit(void)            **
**                                                                            **
** Description     : Function that de-initializes the GTM triggering          **
**                   configuration settings.                                  **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Mcu_lGtmTriggerDeInit(void)
{
  /*
     De-Initialize the ADC trigger registers.
  */

  GTM_ADCTRIG0OUT0.U = MCU_GTM_ADC_TRIGOUT_RESET_VAL;
  GTM_ADCTRIG0OUT1.U = MCU_GTM_ADC_TRIGOUT_RESET_VAL;
  GTM_ADCTRIG1OUT0.U = MCU_GTM_ADC_TRIGOUT_RESET_VAL;
  GTM_ADCTRIG1OUT1.U = MCU_GTM_ADC_TRIGOUT_RESET_VAL;
  GTM_ADCTRIG2OUT0.U = MCU_GTM_ADC_TRIGOUT_RESET_VAL;
  GTM_ADCTRIG2OUT1.U = MCU_GTM_ADC_TRIGOUT_RESET_VAL;
  GTM_ADCTRIG3OUT0.U = MCU_GTM_ADC_TRIGOUT_RESET_VAL;
  GTM_ADCTRIG3OUT1.U = MCU_GTM_ADC_TRIGOUT_RESET_VAL;
  GTM_ADCTRIG4OUT0.U = MCU_GTM_ADC_TRIGOUT_RESET_VAL;
  GTM_ADCTRIG4OUT1.U = MCU_GTM_ADC_TRIGOUT_RESET_VAL;

  /*
     De-Initialize the DSADC trigger registers.
  */
  #if (MCU_GTM_TO_DSADC_TRIG_AVAILABLE == STD_ON)
  GTM_DSADCOUTSEL00.U = MCU_GTM_DSADC_TRIGOUT_RESET_VAL;
  GTM_DSADCOUTSEL10.U = MCU_GTM_DSADC_TRIGOUT_RESET_VAL;
  GTM_DSADCOUTSEL20.U = MCU_GTM_DSADC_TRIGOUT_RESET_VAL;
  GTM_DSADCOUTSEL30.U = MCU_GTM_DSADC_TRIGOUT_RESET_VAL;
  #if (MCU_GTM_TO_DSADC_TRIG1 == STD_ON)
  GTM_DSADCOUTSEL01.U = MCU_GTM_DSADC_TRIGOUT_RESET_VAL;
  GTM_DSADCOUTSEL11.U = MCU_GTM_DSADC_TRIGOUT_RESET_VAL;
  GTM_DSADCOUTSEL21.U = MCU_GTM_DSADC_TRIGOUT_RESET_VAL;
  GTM_DSADCOUTSEL31.U = MCU_GTM_DSADC_TRIGOUT_RESET_VAL;
  #endif
  #endif /*End of (MCU_GTM_TO_DSADC_TRIG_AVAILABLE == STD_ON)*/
}
#endif
/* End of #if (MCU_DEINIT_API == STD_ON) */

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={E6BEE77E-6E1F-4aaf-9842-317D02990D2F}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE void Mcu_lGtmTbuGlobalInit  (void)          **
**                                                                            **
** Description     :    This function performs global initialization of GTM - **
**                      TBU channels as per configuration.                    **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Non-Reentrant                                         **
**                                                                            **
** Parameters (in) :    None                                                  **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    None                                                  **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Mcu_lGtmTbuGlobalInit(void)
{
  /* Disable all TBU channels before changing its configuration */
  GTM_TBU_CHEN.U = MCU_TBU_CH_DISABLE_MASK & (~(MCU_TBU_CH_MASK <<
                      (2U * MCU_GTM_NO_OF_TBU_CH_AVAILABLE)));

  uint8 TbuChInfo = (uint8)(Mcu_ConfigPtr->McuGtmConfigPtr->GtmTbuCfg &
                              MCU_TBU_CH_EN_MSK);

  #if (MCU_GTM_NO_OF_TBU_CH_AVAILABLE > 0U)
  if (((TbuChInfo >> MCU_TBU_CH0_INDEX)& MCU_TBU_CH_MSK) == MCU_TBU_CH_ENABLED)
  {
    GTM_TBU_CH0_CTRL.U = ((Mcu_ConfigPtr->McuGtmConfigPtr->GtmTbuCfg >>
                           MCU_TBU_CH0_OFF) & MCU_TBU_CH_0_2_MASK);
  }
  #endif

  #if (MCU_GTM_NO_OF_TBU_CH_AVAILABLE > 1U)
  if (((TbuChInfo >> MCU_TBU_CH1_INDEX) & MCU_TBU_CH_MSK) == MCU_TBU_CH_ENABLED)
  {
    GTM_TBU_CH1_CTRL.U = ((Mcu_ConfigPtr->McuGtmConfigPtr->GtmTbuCfg >>
                           MCU_TBU_CH1_OFF) & MCU_TBU_CH_0_2_MASK);
  }
  #endif

  #if (MCU_GTM_NO_OF_TBU_CH_AVAILABLE > 2U)
  if (((TbuChInfo >> MCU_TBU_CH2_INDEX) & MCU_TBU_CH_MSK) == MCU_TBU_CH_ENABLED)
  {
    GTM_TBU_CH2_CTRL.U = ((Mcu_ConfigPtr->McuGtmConfigPtr->GtmTbuCfg >>
                           MCU_TBU_CH2_OFF) & MCU_TBU_CH_0_2_MASK);
  }
  #endif

  #if (MCU_GTM_NO_OF_TBU_CH_AVAILABLE > 3U)
  if (((TbuChInfo >> MCU_TBU_CH3_INDEX) & MCU_TBU_CH_MSK) == MCU_TBU_CH_ENABLED)
  {
    GTM_TBU_CH3_CTRL.U = (((Mcu_ConfigPtr->McuGtmConfigPtr->GtmTbuCfg >>
                            MCU_TBU_CH3_OFF) & MCU_TBU_CH3_MODE_MASK));
  }
  #endif
  /* Enable TBU channels as per the configuration */
  GTM_TBU_CHEN.U = (Mcu_ConfigPtr->McuGtmConfigPtr->GtmTbuCfg &
                    MCU_TBU_CH_EN_MSK);
}

#if (MCU_DEINIT_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={73727385-92EB-42de-85D4-A5694D4D05D7}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE void Mcu_lGtmTbuGlobalDeInit  (void)        **
**                                                                            **
** Description     :    This function performs  de-initialization of          **
**                      TBU channels.                                         **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Non-Reentrant                                         **
**                                                                            **
** Parameters (in) :    None                                                  **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    None                                                  **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Mcu_lGtmTbuGlobalDeInit(void)
{
  /* Disable all TBU channels before changing its configuration */
  GTM_TBU_CHEN.U = MCU_TBU_CH_DISABLE_MASK & (~(MCU_TBU_CH_MASK <<
                      (2U * MCU_GTM_NO_OF_TBU_CH_AVAILABLE)));

  uint8 TbuChInfo = (uint8)(Mcu_ConfigPtr->McuGtmConfigPtr->GtmTbuCfg &
                              MCU_TBU_CH_EN_MSK);

  #if (MCU_GTM_NO_OF_TBU_CH_AVAILABLE > 0U)
  if (((TbuChInfo >> MCU_TBU_CH0_INDEX) & MCU_TBU_CH_MSK) == MCU_TBU_CH_ENABLED)
  {
    GTM_TBU_CH0_CTRL.U = MCU_TBU_CH0_2_CTRL_RST_VAL;
  }
  #endif

  #if (MCU_GTM_NO_OF_TBU_CH_AVAILABLE > 1U)
  if (((TbuChInfo >> MCU_TBU_CH1_INDEX) & MCU_TBU_CH_MSK) == MCU_TBU_CH_ENABLED)
  {
    GTM_TBU_CH1_CTRL.U = MCU_TBU_CH0_2_CTRL_RST_VAL;
  }
  #endif

  #if (MCU_GTM_NO_OF_TBU_CH_AVAILABLE > 2U)
  if (((TbuChInfo >> MCU_TBU_CH2_INDEX) & MCU_TBU_CH_MSK) == MCU_TBU_CH_ENABLED)
  {
    GTM_TBU_CH2_CTRL.U = MCU_TBU_CH0_2_CTRL_RST_VAL;
  }
  #endif

  #if (MCU_GTM_NO_OF_TBU_CH_AVAILABLE > 3U)
  if (((TbuChInfo >> MCU_TBU_CH3_INDEX) & MCU_TBU_CH_MSK) == MCU_TBU_CH_ENABLED)
  {
    GTM_TBU_CH3_CTRL.U = MCU_TBU_CH3_CTRL_RST_VAL;
  }
  #endif
}
#endif
/* End of #if (MCU_DEINIT_API == STD_ON) */

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={3B679638-812A-49e1-8C57-AEEFCB393ED8}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE void Mcu_lGtmCcmGlobalInit  (void)          **
**                                                                            **
** Description     :    This function performs initialization of Cluster      **
**                      Module as per configuration.                          **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Non-Reentrant                                         **
**                                                                            **
** Parameters (in) :    None                                                  **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    None                                                  **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Mcu_lGtmCcmGlobalInit(void)
{
  uint32 GtmCcmCfgVal;
  uint8 ClsClkVal;
  uint8 ClusterIndex;

  /* [cover parentID={4DAFBD8C-2FD8-4ad0-BA73-FD4DF5A1D8BA}]
   * Loop through all available Clusters
   * [/cover] */
  for (ClusterIndex = MCU_STARTING_INDEX;
       ClusterIndex < MCU_GTM_NO_OF_CCM_AVAILABLE; ClusterIndex++)
  {
    /* Check the cluster clock is Enabled/Disabled */
    /* [cover parentID={D28B3C12-AE11-41fb-A0BD-DFDFC47EDE0F}]
     * Is Cluster clock enabled [/cover] */
    ClsClkVal = (uint8)(((GTM_CLS_CLK_CFG.U) >> \
                         (MCU_GTM_CLS_CLK_LEN * ClusterIndex)) & \
                          MCU_GTM_CLS_CLK_DIV_MSK);

    if (ClsClkVal != 0x0U)
    {
      MODULE_GTM.CCM[ClusterIndex].PROT.B.CLS_PROT = 0x0U;
      if ( Mcu_ConfigPtr->McuGtmConfigPtr->
                        GtmClusterCfgPtr[ClusterIndex].GtmCcmCfg != 0x0U)
      {
        GtmCcmCfgVal = ((uint32)MODULE_GTM.CCM[ClusterIndex].CFG.U);
        /*[cover parentID={548EFFB4-AE1A-4bdd-ACB6-E20D9A37AB43}][/cover]*/
        GtmCcmCfgVal = (GtmCcmCfgVal | Mcu_ConfigPtr->McuGtmConfigPtr->
                        GtmClusterCfgPtr[ClusterIndex].GtmCcmCfg);
        MODULE_GTM.CCM[ClusterIndex].CFG.U = GtmCcmCfgVal;
      }
      MODULE_GTM.CCM[ClusterIndex].CMU_CLK_CFG.U = Mcu_ConfigPtr->
          McuGtmConfigPtr->GtmClusterCfgPtr[ClusterIndex].GtmCcmConfClockCfg;
      MODULE_GTM.CCM[ClusterIndex].CMU_FXCLK_CFG.U = Mcu_ConfigPtr->
          McuGtmConfigPtr->GtmClusterCfgPtr[ClusterIndex].GtmCcmFixedClockCfg;
      MODULE_GTM.CCM[ClusterIndex].PROT.B.CLS_PROT = 0x1U;
    }
  }
}

#if (MCU_DEINIT_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={9BD508AE-D8DE-489a-9467-AFFD22E08D92}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE void Mcu_lGtmCcmGlobalDeInit  (void)        **
**                                                                            **
** Description     :    This function performs de-initialization of Cluster   **
**                      Module                     .                          **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Non-Reentrant                                         **
**                                                                            **
** Parameters (in) :    None                                                  **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    None                                                  **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Mcu_lGtmCcmGlobalDeInit(void)
{
  uint8 ClusterIndex;
  uint8 ClsClkVal;

  /* [cover parentID={B080BE31-8483-4479-A147-42EF237A13B9}]
   * Loop through all available Clusters
   * [/cover] */
  for (ClusterIndex = MCU_STARTING_INDEX;
       ClusterIndex < MCU_GTM_NO_OF_CCM_AVAILABLE; ClusterIndex++)
  {
    /* Check the cluster clock is Enabled/Disabled */
    ClsClkVal = (uint8)(((GTM_CLS_CLK_CFG.U) >> \
                         (MCU_GTM_CLS_CLK_LEN * ClusterIndex)) & \
                          MCU_GTM_CLS_CLK_DIV_MSK);
    /* [cover parentID={AD45CED8-07E8-4d3f-95CA-7798D0874AA7}]
       * Is Cluster clock enabled
       * [/cover] */
    if (ClsClkVal != 0x0U)
    {
      MODULE_GTM.CCM[ClusterIndex].PROT.B.CLS_PROT = 0x0U;
      if ( Mcu_ConfigPtr->McuGtmConfigPtr->
                        GtmClusterCfgPtr[ClusterIndex].GtmCcmCfg != 0x0U)
      {
        MODULE_GTM.CCM[ClusterIndex].CFG.U |= Mcu_ConfigPtr->McuGtmConfigPtr->
                        GtmClusterCfgPtr[ClusterIndex].GtmCcmCfg;
      }
      MODULE_GTM.CCM[ClusterIndex].CMU_CLK_CFG.U = MCU_CCM_CMU_CLK_CFG_RST_VAL;
      MODULE_GTM.CCM[ClusterIndex].CMU_FXCLK_CFG.U =
        MCU_CCM_CMU_FXCLK_CFG_RST_VAL;
      MODULE_GTM.CCM[ClusterIndex].PROT.B.CLS_PROT = 0x1U;
    }
  }
}
#endif
/* End of #if (MCU_DEINIT_API == STD_ON) */

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={AF165ACF-89FE-475f-9FBA-43C2E06E3F10}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE void Mcu_lGtmTomGlobalInit  (void)          **
**                                                                            **
** Description     :    This function configures the global configurations of **
**                      the TOM modules relating to trigger configuration     **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Non-Reentrant                                         **
**                                                                            **
** Parameters (in) :    None                                                  **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    None                                                  **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Mcu_lGtmTomGlobalInit(void)
{
  Mcu_17_Gtm_TomTgc *TomTgcRegPtr;
  uint8 TomModuleIndex;
  uint8 GtmTomCfgIndex;
  uint32 GtmTomTgcActTb;

  /* [cover parentID={3896B03A-1984-4877-899F-D8B8C2790BB7}]
   * Loop through all available TOM modules
   * [/cover] */
  for (TomModuleIndex = MCU_STARTING_INDEX;
       TomModuleIndex < MCU_GTM_NO_OF_TOM_AVAILABLE; TomModuleIndex++)
  {
    /* Is the TOM module used by other MCAL drivers */
    /* [cover parentID={73BBE4FB-5372-4e42-8179-DC6DEE28A100}]
     * Check if TOM module is Used
     * [/cover] */
    if (((Mcu_ConfigPtr->McuGtmConfigPtr->GtmTomModuleUsage >>
          TomModuleIndex) & 0x1U) == 0x1U)
    {
      /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
       * by violating this MISRA rule, as the pointer to the object type
       * it is getting cast into is a known type . */
      /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
       * by violating this MISRA rule. */
      TomTgcRegPtr   = GTM_TOM_TGC_POINTER(TomModuleIndex, 0x0U);
      GtmTomCfgIndex = (0x2U * TomModuleIndex);
      TomTgcRegPtr->TGC_INT_TRIG.U =
        (Mcu_ConfigPtr->McuGtmConfigPtr->GtmTomCfg[GtmTomCfgIndex]
         .TomTgcIntTrigRstCn0 & MCU_GTM_TOM_TGC_INT_TRIG_MASK);
      TomTgcRegPtr->TGC_FUPD_CTRL.U =
        (Mcu_ConfigPtr->McuGtmConfigPtr->GtmTomCfg[GtmTomCfgIndex]
         .TomTgcIntTrigRstCn0 & MCU_GTM_TOM_TGC_RST_CN0_MASK);
      GtmTomTgcActTb = (TomTgcRegPtr->TGC_ACT_TB.U & MCU_TOM_ACT_TB_TRIG_MSK);
      TomTgcRegPtr->TGC_ACT_TB.U = GtmTomTgcActTb | \
        (Mcu_ConfigPtr->McuGtmConfigPtr->GtmTomCfg[GtmTomCfgIndex].TomTgcActTb);
      /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
       * by violating this MISRA rule, as the pointer to the object type
       * it is getting cast into is a known type . */
      /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
       * by violating this MISRA rule. */
      TomTgcRegPtr   = GTM_TOM_TGC_POINTER(TomModuleIndex, 0x1U);
      GtmTomCfgIndex = ((2U * TomModuleIndex) + 0x1U);
      /*Global Configuration of TOM0 Group0*/
      TomTgcRegPtr->TGC_INT_TRIG.U =
        (Mcu_ConfigPtr->McuGtmConfigPtr->GtmTomCfg[GtmTomCfgIndex]
         .TomTgcIntTrigRstCn0 & MCU_GTM_TOM_TGC_INT_TRIG_MASK);
      TomTgcRegPtr->TGC_FUPD_CTRL.U =
        (Mcu_ConfigPtr->McuGtmConfigPtr->GtmTomCfg[GtmTomCfgIndex]
         .TomTgcIntTrigRstCn0 & MCU_GTM_TOM_TGC_RST_CN0_MASK);
      GtmTomTgcActTb = (TomTgcRegPtr->TGC_ACT_TB.U & MCU_TOM_ACT_TB_TRIG_MSK);
      TomTgcRegPtr->TGC_ACT_TB.U = GtmTomTgcActTb | \
        (Mcu_ConfigPtr->McuGtmConfigPtr->GtmTomCfg[GtmTomCfgIndex].TomTgcActTb);
    }
  }
}

#if (MCU_DEINIT_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    :  [cover parentID={76E26F40-7A10-494f-B031-E8D73702699A}] **
**                                                                            **
** Syntax          : LOCAL_INLINE void Mcu_lGtmTomGlobalDeInit  (void)        **
**                                                                            **
** Description     :    This function de-initialized the global configurations**
**                      of the TOM modules relating to trigger configuration  **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Non-Reentrant                                         **
**                                                                            **
** Parameters (in) :    None                                                  **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    None                                                  **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Mcu_lGtmTomGlobalDeInit(void)
{
  Mcu_17_Gtm_TomTgc *TomTgcRegPtr;
  uint8 TomModuleIndex;
  uint32 GtmTomTgcActTb;

  /* [cover parentID={A06B16AF-C15C-41a9-9FCF-22BFF8A63044}]
   * Loop through all available TOM modules
   * [/cover] */
  for (TomModuleIndex = MCU_STARTING_INDEX;
       TomModuleIndex < MCU_GTM_NO_OF_TOM_AVAILABLE; TomModuleIndex++)
  {
    /* Is the TOM module used by other MCAL drivers */
    /* [cover parentID={C0549D39-DD7B-42a6-85F3-11510BE0A3BC}]
     * Check if TOM module is Used
     * [/cover] */
    if (((Mcu_ConfigPtr->McuGtmConfigPtr->GtmTomModuleUsage >>
          TomModuleIndex) & 0x1U) == 0x1U)
    {
      /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
       * by violating this MISRA rule, as the pointer to the object type
       * it is getting cast into is a known type . */
      /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
       * by violating this MISRA rule. */
      TomTgcRegPtr = GTM_TOM_TGC_POINTER(TomModuleIndex, 0x0U);
      /*Global Configuration of TOM0 Group0*/

      TomTgcRegPtr->TGC_INT_TRIG.U = MCU_TOM_INT_TRIG_RST_VAL;
      TomTgcRegPtr->TGC_FUPD_CTRL.U = MCU_TOM_FUPD_CTRL_RST_VAL;
      GtmTomTgcActTb = (TomTgcRegPtr->TGC_ACT_TB.U & MCU_TOM_ACT_TB_TRIG_MSK);
      TomTgcRegPtr->TGC_ACT_TB.U = (GtmTomTgcActTb | MCU_TOM_ACT_TB_RST_VAL);

      /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
       * by violating this MISRA rule, as the pointer to the object type
       * it is getting cast into is a known type . */
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access. No side effects foreseen
       * by violating this MISRA rule. */
      /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
       * by violating this MISRA rule. */
      TomTgcRegPtr = GTM_TOM_TGC_POINTER(TomModuleIndex, 0x1U);
      /*Global Configuration of TOM0 Group0*/
      TomTgcRegPtr->TGC_INT_TRIG.U = MCU_TOM_INT_TRIG_RST_VAL;
      TomTgcRegPtr->TGC_FUPD_CTRL.U = MCU_TOM_FUPD_CTRL_RST_VAL;
      GtmTomTgcActTb = (TomTgcRegPtr->TGC_ACT_TB.U & MCU_TOM_ACT_TB_TRIG_MSK);
      TomTgcRegPtr->TGC_ACT_TB.U = (GtmTomTgcActTb | MCU_TOM_ACT_TB_RST_VAL);
    }
  }
}
#endif
/* End of #if (MCU_DEINIT_API == STD_ON) */

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={84694EEF-63BF-49f3-8D07-31BEAB44C34B}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE void Mcu_lGtmAtomGlobalInit  (void)         **
**                                                                            **
** Description     :    This function configures the global configurations of **
**                      the ATOM modules relating to trigger configuration    **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Non-Reentrant                                         **
**                                                                            **
** Parameters (in) :    None                                                  **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    None                                                  **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Mcu_lGtmAtomGlobalInit(void)
{

  Ifx_GTM_ATOM_AGC *AtomAgcRegPtr;
  uint8 AtomModuleIndex;
  uint32 GtmAtomTgcActTb;

  /* [cover parentID={F3B6EE9A-AD76-43f1-872C-6848B33E7277}]
   * Loop through all available ATOM modules
   * [/cover] */
  for (AtomModuleIndex = MCU_STARTING_INDEX;
       AtomModuleIndex < MCU_GTM_NO_OF_ATOM_AVAILABLE; AtomModuleIndex++)
  {
    /* Is the ATOM module used by other MCAL drivers */
    /* [cover parentID={F80C9151-D637-4b4a-A951-391C2104784B}]
     * Check if ATOM module is Used
     * [/cover] */
    if (((Mcu_ConfigPtr->McuGtmConfigPtr->GtmAtomModuleUsage >>
          AtomModuleIndex) & 0x1U) == 0x1U)
    {
      AtomAgcRegPtr = GTM_ATOM_AGC_POINTER(AtomModuleIndex);
      /*Global Configuration of ATOM GroupX*/
      AtomAgcRegPtr->INT_TRIG.U =
        (Mcu_ConfigPtr->McuGtmConfigPtr->GtmAtomCfg[AtomModuleIndex]
         .AtomAgcIntTrigRstCn0 & MCU_GTM_ATOM_AGC_INT_TRIG_MASK);
      AtomAgcRegPtr->FUPD_CTRL.U =
        (Mcu_ConfigPtr->McuGtmConfigPtr->GtmAtomCfg[AtomModuleIndex]
         .AtomAgcIntTrigRstCn0 & MCU_GTM_ATOM_AGC_RST_CN0_MASK);
      GtmAtomTgcActTb = (AtomAgcRegPtr->ACT_TB.U & MCU_ATOM_ACT_TB_TRIG_MSK);
      AtomAgcRegPtr->ACT_TB.U = GtmAtomTgcActTb | \
        (Mcu_ConfigPtr->McuGtmConfigPtr->GtmAtomCfg[AtomModuleIndex]
         .AtomAgcActTb);
    }
  }
}

#if (MCU_DEINIT_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={5DE4DEF0-BDA7-42ab-A986-3A1BC5A0B9F3}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE void Mcu_lGtmAtomGlobalDeInit  (void)       **
**                                                                            **
** Description     :    This function de-initialized the global configurations**
**                      of the ATOM modules relating to trigger configuration **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Non-Reentrant                                         **
**                                                                            **
** Parameters (in) :    None                                                  **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    None                                                  **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Mcu_lGtmAtomGlobalDeInit(void)
{

  Ifx_GTM_ATOM_AGC *AtomAgcRegPtr;
  uint8 AtomModuleIndex;
  uint32 GtmAtomTgcActTb;

  /* [cover parentID={EF86C432-5DDC-47ed-890C-7E1B3409C65C}]
   * Loop through all available ATOM modules
   * [/cover] */
  for (AtomModuleIndex = MCU_STARTING_INDEX;
       AtomModuleIndex < MCU_GTM_NO_OF_ATOM_AVAILABLE; AtomModuleIndex++)
  {
    /* Is the ATOM module used by other MCAL drivers */
    /* [cover parentID={6299E88D-920A-4b1f-A117-0AF9BCC9ED28}]
     * Check if ATOM module is Used
     * [/cover] */
    if (((Mcu_ConfigPtr->McuGtmConfigPtr->GtmAtomModuleUsage >>
          AtomModuleIndex) &
         0x1U) == 0x1U)
    {
      AtomAgcRegPtr = GTM_ATOM_AGC_POINTER(AtomModuleIndex);
      /*Global Configuration of ATOM GroupX*/
      AtomAgcRegPtr->INT_TRIG.U = MCU_ATOM_INT_TRIG_RST_VAL;
      AtomAgcRegPtr->FUPD_CTRL.U = MCU_ATOM_FUPD_CTRL_RST_VAL;
      GtmAtomTgcActTb = (AtomAgcRegPtr->ACT_TB.U & MCU_ATOM_ACT_TB_TRIG_MSK);
      AtomAgcRegPtr->ACT_TB.U = (GtmAtomTgcActTb | MCU_ATOM_ACT_TB_RST_VAL);
    }
  }
}
#endif
/*#if (MCU_DEINIT_API == STD_ON)*/

#endif
/*#if (MCU_GTM_USED == STD_ON)*/


#if ((MCU_GPT1_USED == STD_ON) || (MCU_GPT2_USED == STD_ON))
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={4D00B3F1-50D2-4cfc-9797-3F47419ACBDA}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType Mcu_lGpt12Init  (void)       **
**                                                                            **
** Description     :    This function initializes the GPT12 Kernel            **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Non-Reentrant                                         **
**                                                                            **
** Parameters (in) :    None                                                  **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    : E_OK: GPT12 module clock enabling successful             **
**                   E_NOT_OK: GPT12 module clock enabling unsuccessful       **
**                                                                            **
*******************************************************************************/
/*[cover parentID={F762790E-FD9A-47c4-91FD-31BFB7E3952A}][/cover]*/
LOCAL_INLINE Std_ReturnType Mcu_lGpt12Init(void)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_GPT12_CLC Gpt12ClcVal;

  #if (MCU_GPT1_USED == STD_ON)
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_GPT12_T3CON GptT3Con;
  #endif

  #if (MCU_GPT2_USED == STD_ON)
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_GPT12_T6CON GptT6Con;
  #endif

  Std_ReturnType Gpt12InitStatus = E_OK;
  /*
    GPT12 initialization
    1. Enable GPT12 module clock.
  */

  Gpt12ClcVal.U = GPT120_CLC.U;
  Gpt12ClcVal.B.DISR = GPT12_TIMER_ENABLE;

  /*[cover parentID={F284161A-DB23-4991-B5F6-938E10425100}]*/
  #if ((MCU_GPT1_USED == STD_ON) || (MCU_GPT2_USED == STD_ON))
  /*[cover parentID={2141FD0C-EDC1-425f-A5C5-F86F5913A958}][/cover]*/
  if ((boolean)TRUE == Mcu_ConfigPtr->IsGpt12SleepModeEnabled)
  {
    Gpt12ClcVal.B.EDIS = 0x0U;
  }
  else
  {
    Gpt12ClcVal.B.EDIS = 0x1U;
  }
  #endif
  /*[/cover]*/

  /*[cover parentID={1EC6070C-74DD-4525-81DD-FF833EF4E721}][/cover]*/
  MCU_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(&GPT120_CLC.U,
      Gpt12ClcVal.U);

  /* [cover parentID={DB5EDFD1-F331-438e-A14C-DC4EAE4A5B95}]
   * Gpt12 Clock is Enabled
   * [/cover] */
  if (GPT120_CLC.B.DISS != GPT12_TIMER_CLK_ENABLED)
  {
    Gpt12InitStatus = E_NOT_OK;
    /* [cover parentID={7F3F78CC-FF98-4204-BE88-07E7D8DCB2B9}]
     * If Production error Reporting is ON */
    #if (MCU_E_GPT12_CLC_ENABLE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
    /* [/cover] */
    /*Report Production error for CLC enable failed*/
    /* [cover parentID={C6CDAE4C-88F4-4308-831B-5BCAC0CA4B30}]
     * Report Production error: Event Failed
     * [/cover] */
    Mcu_lReportDemError(MCU_E_GPT12_CLC_ENABLE_ERR, DEM_EVENT_STATUS_FAILED);
    #endif
  }
  #if (MCU_E_GPT12_CLC_ENABLE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
  else
  {
    /*Report Production error for CLC enable passed*/
    /*[cover parentID={F85FBFEA-DAED-482d-A18E-52A2B07079AB} ][/cover]*/
    /* [cover parentID={A67BEF70-75C4-428a-84BD-61E4AD766B6D}]
    * Report Production error: Event Passed
    * [/cover] */
    Mcu_lReportDemError(MCU_E_GPT12_CLC_ENABLE_ERR, DEM_EVENT_STATUS_PASSED);
  }
  #endif
  /* [/cover] */
  if (Gpt12InitStatus == E_OK)
  {
    /*[cover parentID={B6B1C64C-AA23-4215-A1B0-02B3ACFB04C0}]*/
    #if (MCU_GPT1_USED == STD_ON)
    GptT3Con.U = GPT12_TXCON_RESET_VAL;
    GptT3Con.B.BPS1 = Mcu_ConfigPtr->McuGpt12PreScalarConfigPtr->Gpt1PrescalarDiv;
    MCU_SFR_INIT_DEINIT_WRITE32(&GPT120_T3CON.U, GptT3Con.U);
    #endif
    /*[/cover]*/

    /*[cover parentID={2DC34AA5-D28D-4494-BA6C-E57A8590BD8F}]*/
    #if (MCU_GPT2_USED == STD_ON)
    GptT6Con.U = GPT12_TXCON_RESET_VAL;
    GptT6Con.B.BPS2 = Mcu_ConfigPtr->McuGpt12PreScalarConfigPtr->Gpt2PrescalarDiv;
    MCU_SFR_INIT_DEINIT_WRITE32(&GPT120_T6CON.U, GptT6Con.U);
    #endif
    /*[/cover]*/
  }
  /*[cover parentID={32AC2478-EAE7-4474-9852-CAB45944F3EB}][/cover]
  [cover parentID={F7AE6935-7A9C-4728-AC44-B07D4AA175F7}][/cover]*/
  return Gpt12InitStatus;
}
#endif
/*#if ((MCU_GPT1_USED == STD_ON) || (MCU_GPT2_USED == STD_ON))*/

#if (MCU_DEINIT_API == STD_ON)
#if ((MCU_GPT1_USED == STD_ON) || (MCU_GPT2_USED == STD_ON))
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={289C5EE1-6F6A-429b-8B17-2C06A2D1959E}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType Mcu_lGpt12DeInit  (void)     **
**                                                                            **
** Description     :    This function de-initializes the GPT12 Kernel         **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Non-Reentrant                                         **
**                                                                            **
** Parameters (in) :    None                                                  **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    : E_OK: GPT12 module clock disabling successful            **
**                   E_NOT_OK: GPT12 module clock disabling unsuccessful      **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Mcu_lGpt12DeInit(void)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_GPT12_CLC Gpt12ClcVal;
  Std_ReturnType Gpt12InitStatus = E_OK;

  #if (MCU_GPT1_USED == STD_ON)
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_GPT12_T3CON GptT3Con;
  #endif

  #if (MCU_GPT2_USED == STD_ON)
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_GPT12_T6CON GptT6Con;
  #endif

  /*[cover parentID={87C07D30-7F2F-4413-BB55-B9CD2D9DF7BD}]
   * Gpt block 1 used */
  #if (MCU_GPT1_USED == STD_ON)
  /* De-Initialize Gpt block 1 */
  GptT3Con.U = GPT12_TXCON_RESET_VAL;
  MCU_SFR_INIT_DEINIT_WRITE32(&GPT120_T3CON.U, GptT3Con.U);
  #endif
  /*[/cover]*/

  /*[cover parentID={BD7BB187-BC81-4258-A956-EB9DE9B77C01}]
   * GPt block 2 is used */
  #if (MCU_GPT2_USED == STD_ON)
  /* De-Initialize Gpt block 2 */
  GptT6Con.U = GPT12_TXCON_RESET_VAL;
  MCU_SFR_INIT_DEINIT_WRITE32(&GPT120_T6CON.U, GptT6Con.U);
  #endif
  /*[/cover]*/

  /*
    GPT12 initialization
    1. Disable GPT12 module clock.
  */

  Gpt12ClcVal.U = GPT120_CLC.U;
  Gpt12ClcVal.B.DISR = GPT12_TIMER_DISABLE;
  Gpt12ClcVal.B.EDIS = 0x0U;

  MCU_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(&GPT120_CLC.U,
      Gpt12ClcVal.U);

  /*[cover parentID={6F8B6DD8-07F0-461e-933F-09B39D0B77AF}]*/
  /* [cover parentID={3B8B8643-CB88-4fea-8856-3D126386369B}]
   * Gpt12 Clock disabled
   * [/cover] */
  if (GPT120_CLC.B.DISS != GPT12_TIMER_CLK_DISABLED)
  {
    Gpt12InitStatus = E_NOT_OK;
    /* [cover parentID={223601F0-0BD6-47f5-B2D3-08D683009DB9}]
     * If Production error Reporting is ON*/

    #if (MCU_E_GPT12_CLC_DISABLE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
    /*Report Production error for CLC disable failed*/
    /* [cover parentID={96C1E83C-73A0-430d-AF78-E9193A400E75}]
     * Report Production error: Event Failed
     * [/cover] */
    Mcu_lReportDemError(MCU_E_GPT12_CLC_DISABLE_ERR, DEM_EVENT_STATUS_FAILED);
    #endif
  }
  #if (MCU_E_GPT12_CLC_DISABLE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
  else
  {
    /*Report Production error for CLC disable passed*/
    /* [cover parentID={4A2D70C9-4FB8-47f2-B338-028DC030C012}]
     * Report Production error: Event Passed
     * [/cover] */
    Mcu_lReportDemError(MCU_E_GPT12_CLC_DISABLE_ERR, DEM_EVENT_STATUS_PASSED);
  }
  /*[/cover]*/
  #endif
  /*[/cover] */
  /*[cover parentID={755DF27B-A9B1-4952-B165-19418A2440B6}][/cover]
  [cover parentID={8E03B4CB-2EBC-472f-9909-40F105D9DD68}][/cover]*/
  return Gpt12InitStatus;
}
#endif
/* End of #if ((MCU_GPT1_USED == STD_ON) || (MCU_GPT2_USED == STD_ON)) */
#endif
/* End of #if (MCU_DEINIT_API == STD_ON) */

#if (MCU_CCU60_USED == STD_ON) || (MCU_CCU61_USED == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={72841ED6-994D-4dc4-88C2-7DD6A03BBA07}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType Mcu_lCcu6Init  (void)        **
**                                                                            **
** Description     :    This function initializes the CCU6 Kernels            **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Non-Reentrant                                         **
**                                                                            **
** Parameters (in) :    None                                                  **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    : E_OK: CCU6 kernels clock enabling successful             **
**                   E_NOT_OK: CCU6 kernels clock enabling unsuccessful       **
**                                                                            **
*******************************************************************************/
/*[cover parentID={F762790E-FD9A-47c4-91FD-31BFB7E3952A}][/cover]*/
LOCAL_INLINE Std_ReturnType Mcu_lCcu6Init(void)
{
  Std_ReturnType Ccu6ClcStatus = E_NOT_OK;

  /*[cover parentID={C568FC9C-3169-4ac8-8F04-3BD09EEBCB3A}]*/
  #if (MCU_CCU60_USED == STD_ON)
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
   defined to modify certain bits and avoid 32-bit mask value.
   No side effects foreseen by violating this MISRA rule.*/
  Ifx_CCU6_CLC Ccu60ClcVal;
  Ccu60ClcVal.U = CCU60_CLC.U;
  Ccu60ClcVal.B.DISR = CCU6_KERNEL_ENABLE;

  /*[cover parentID={90666ECC-A68A-409b-B0CE-9E0C054F6AA5}][/cover]*/
  if ((boolean)TRUE == Mcu_ConfigPtr->IsCcu60SleepModeEnabled)
  {
    Ccu60ClcVal.B.EDIS = 0x0U;
  }
  else
  {
    Ccu60ClcVal.B.EDIS = 0x1U;
  }

  /*[cover parentID={AEBC4A33-C370-460d-81D7-C343B04E1FD6}][/cover]*/
  MCU_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(&CCU60_CLC.U,
      Ccu60ClcVal.U);

  Ccu60ClcVal.U = CCU60_CLC.U;
  #endif
  /*[/cover]*/

  /*[cover parentID={220B27BD-8BA5-4414-8875-CB3D0DF89091}][/cover]*/
  #if (MCU_CCU61_USED == STD_ON)
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_CCU6_CLC Ccu61ClcVal;
  Ccu61ClcVal.U = CCU61_CLC.U;
  Ccu61ClcVal.B.DISR = CCU6_KERNEL_ENABLE;

  /*[cover parentID={B0F6B594-98FF-462b-9CEC-FA949E4B860B}][/cover]*/
  if ((boolean)TRUE == Mcu_ConfigPtr->IsCcu61SleepModeEnabled)
  {
    Ccu61ClcVal.B.EDIS = 0x0U;
  }
  else
  {
    Ccu61ClcVal.B.EDIS = 0x1U;
  }

  /*[cover parentID={EF69D2FA-9FFA-4eb4-ADF4-91F0DC3F2E8B}][/cover]*/
  MCU_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(&CCU61_CLC.U,
      Ccu61ClcVal.U);

  Ccu61ClcVal.U = CCU61_CLC.U;
  #endif
  /* [cover parentID={29689503-3389-4633-9B18-58E62002CE47}]
   * Ccu6 Kernel0 and Kernel1 Clock Enabled
   * [/cover] */
  if
  (
    #if (MCU_CCU60_USED == STD_ON)
    (Ccu60ClcVal.B.DISS == CCU6_KERNEL_CLK_ENABLED)
    #endif
    #if ((MCU_CCU60_USED == STD_ON) && (MCU_CCU61_USED == STD_ON))
    &&
    #endif
    #if (MCU_CCU61_USED == STD_ON)
    (Ccu61ClcVal.B.DISS == CCU6_KERNEL_CLK_ENABLED)
    #endif
  )
  {
    /* [cover parentID={89FCB181-B846-4b15-A177-5AB75E93ABAD}]
     * If Production error Reporting is ON*/
    #if (MCU_E_CCU6_CLC_ENABLE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
    /*Report Production error for CLC enable passed*/
    /* [cover parentID={D9190440-57A7-4431-9FC7-446CB7B8D39B}]
     * Report Production error: Event Passed
     * [/cover] */
    Mcu_lReportDemError(MCU_E_CCU6_CLC_ENABLE_ERR, DEM_EVENT_STATUS_PASSED);
    #endif
    #if (MCU_CCU60_USED == STD_ON)
    CCU60_ISR.U = CCU6_INTERRUPT_FLAG_CLR;
    #endif
    #if (MCU_CCU61_USED == STD_ON)
    CCU61_ISR.U = CCU6_INTERRUPT_FLAG_CLR;
    #endif
    Ccu6ClcStatus = E_OK;
  }
  #if (MCU_E_CCU6_CLC_ENABLE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
  /*[/cover] */
  else
  {
    /*Report Production error for CLC enable failed*/
    /*[cover parentID={F68D83A6-8FDD-4a3f-98CF-F4AAAA3D3CE0} ][/cover]*/
    /* [cover parentID={F6CF1602-3005-4c6f-83D6-3C6086411388}]
    * Report Production error: Event Failed
    * [/cover] */
    Mcu_lReportDemError(MCU_E_CCU6_CLC_ENABLE_ERR, DEM_EVENT_STATUS_FAILED);
  }
  #endif
  /*[cover parentID={364B7666-F2FF-43ab-B2E9-27071C261205}][/cover]
  [cover parentID={838FF274-812C-4fac-BB31-60F1CCCECAC1}][/cover]*/
  return (Ccu6ClcStatus);
}
#endif
/*End of #if (MCU_CCU60_USED == STD_ON) || (MCU_CCU61_USED == STD_ON)*/

#if (MCU_DEINIT_API == STD_ON)
#if (MCU_CCU60_USED == STD_ON) || (MCU_CCU61_USED == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    :  [cover parentID={8320A097-5BA9-489e-9D83-E6E155BC04B6}] **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType Mcu_lCcu6DeInit  (void)      **
**                                                                            **
** Description     :    This function de-initializes the CCU6 Kernels         **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Non-Reentrant                                         **
**                                                                            **
** Parameters (in) :    None                                                  **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    : E_OK: CCU6 kernels clock disabling successful            **
**                   E_NOT_OK: CCU6 kernels clock disabling unsuccessful      **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Mcu_lCcu6DeInit(void)
{
  Std_ReturnType Ccu6ClcStatus = E_NOT_OK;

  #if (MCU_CCU60_USED == STD_ON)
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
  defined to modify certain bits and avoid 32-bit mask value.
  No side effects foreseen by violating this MISRA rule.*/
  Ifx_CCU6_CLC Ccu60ClcVal;
  CCU60_ISR.U = CCU6_INTERRUPT_FLAG_CLR;
  Ccu60ClcVal.U = CCU60_CLC.U;
  Ccu60ClcVal.B.DISR = CCU6_KERNEL_DISABLE;

  MCU_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(&CCU60_CLC.U,
      Ccu60ClcVal.U);

  Ccu60ClcVal.U = CCU60_CLC.U;
  #endif

  #if (MCU_CCU61_USED == STD_ON)
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_CCU6_CLC Ccu61ClcVal;
  CCU61_ISR.U = CCU6_INTERRUPT_FLAG_CLR;
  Ccu61ClcVal.U = CCU61_CLC.U;
  Ccu61ClcVal.B.DISR = CCU6_KERNEL_DISABLE;

  MCU_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(&CCU61_CLC.U,
      Ccu61ClcVal.U);

  Ccu61ClcVal.U = CCU61_CLC.U;
  #endif

  /* [cover parentID={1E16AAA3-A1B5-47cc-9F15-4CFFBC5E7819}]
   * Ccu6 Kernel0 and Kernel1 Clock Disabled
   * [/cover] */
  if
  (
    #if (MCU_CCU60_USED == STD_ON)
    (Ccu60ClcVal.B.DISS == CCU6_KERNEL_CLK_DISABLED)
    #endif
    #if ((MCU_CCU60_USED == STD_ON) && (MCU_CCU61_USED == STD_ON))
    &&
    #endif
    #if (MCU_CCU61_USED == STD_ON)
    (Ccu61ClcVal.B.DISS == CCU6_KERNEL_CLK_DISABLED)
    #endif
  )
  {
    /* [cover parentID={E6F37713-1E34-4d46-A0A1-0323EB830F25}]
     * If Production error Reporting is ON*/
    #if (MCU_E_CCU6_CLC_DISABLE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
    /* [cover parentID={8E4A706A-82C5-4c27-89D2-EC1289FB9F2D}]
     * Report Production error: Event Passed
     * [/cover] */
    Mcu_lReportDemError(MCU_E_CCU6_CLC_DISABLE_ERR, DEM_EVENT_STATUS_PASSED);
    #endif
    Ccu6ClcStatus = E_OK;
  }
  #if (MCU_E_CCU6_CLC_DISABLE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
  /*[/cover] */
  else
  {
    /*Report Production error for CLC disable failed*/
    /*[cover parentID={DD6955D7-BDA0-488f-B2B8-5782FEED35BC} ][/cover]*/
    /* [cover parentID={C3005699-E034-47f5-B10A-D0A95E9A8AA3}]
    * Report Production error: Event Failed
    * [/cover] */
    Mcu_lReportDemError(MCU_E_CCU6_CLC_DISABLE_ERR, DEM_EVENT_STATUS_FAILED);
  }
  #endif
  /*[cover parentID={CA3D6D48-0DD3-4f6f-B28C-21967D18A5E7}][/cover]
  [cover parentID={E769A9ED-4D2B-4dfc-8DB0-28B69E2CB5BA}][/cover]*/
  return (Ccu6ClcStatus);
}
#endif
/*End of #if (MCU_CCU60_USED == STD_ON) || (MCU_CCU61_USED == STD_ON)*/
#endif
/* End of #if (MCU_DEINIT_API == STD_ON) */

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={81BCA440-CE0F-4353-B20A-0E35BB386544}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType Mcu_lConvCtrlInit (void)     **
**                                                                            **
** Description     :    This function initializes the Converter Control block **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Non-Reentrant                                         **
**                                                                            **
** Parameters (in) :    None                                                  **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    : E_OK: Convertor control clock enabling successful        **
**                   E_NOT_OK: Convertor control clock enabling unsuccessful  **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Mcu_lConvCtrlInit(void)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_CONVERTER_CLC ConvCtrlClcVal;
  Std_ReturnType ConvCtrlInitStatus = E_OK;

  ConvCtrlClcVal.U = CONVCTRL_CLC.U;
  ConvCtrlClcVal.B.DISR = CONVERTER_KERNEL_ENABLE;

  MCU_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(&CONVCTRL_CLC.U,
      ConvCtrlClcVal.U);

  /* [cover parentID={F0001CF5-CBFA-449b-81F6-E7F5BDC3FC91}]
   * Is Converter control module clock Enabled
   * [/cover] */
  if (CONVCTRL_CLC.B.DISS != CONVERTER_KERNEL_CLK_ENABLED)
  {
    ConvCtrlInitStatus = E_NOT_OK;
    /* [cover parentID={C3A5973F-B709-48bd-8501-E07899FD643A}]
     * If Production error Reporting is ON*/
    #if (MCU_E_CONVCTRL_CLC_ENABLE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
    /*Report Production error for CLC enable failed*/
    /*[cover parentID={A3F405D3-6A98-4d85-B8A5-A6B377095307} ]
    [/cover] */
    /* [cover parentID={FEFEA6B3-2DEE-428f-BAA8-1E48416EBBEB}]
     * Report Production error: Event failed
     * [/cover] */
    Mcu_lReportDemError(MCU_E_CONVCTRL_CLC_ENABLE_ERR,
                          DEM_EVENT_STATUS_FAILED);
    #endif
  }
  #if (MCU_E_CONVCTRL_CLC_ENABLE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
  else
  {
    /*Report Production error for CLC enable passed*/
    /* [cover parentID={CD76B24E-1A89-4b8c-AC42-A340D03540CF}]
     * Report Production error: Event Passed
     * [/cover] */
    Mcu_lReportDemError(MCU_E_CONVCTRL_CLC_ENABLE_ERR,
                          DEM_EVENT_STATUS_PASSED);
  }
  #endif
  /*[/cover] */
  /*[cover parentID={D88DF839-8258-4771-913E-2CD24C6C5FDD}][/cover]
    [cover parentID={595E7B8B-8EA0-4435-87E2-7920E21FD0E4}][/cover]*/
  return ConvCtrlInitStatus;
}

#if (MCU_DEINIT_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={D82A1751-7FAC-4ba7-BD86-6D09F71CD5FE}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType Mcu_lConvCtrlDeInit (void)   **
**                                                                            **
** Description     :    This function de-initializes  Converter Control block **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Non-Reentrant                                         **
**                                                                            **
** Parameters (in) :    None                                                  **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    : E_OK: Convertor control clock disabling successful       **
**                   E_NOT_OK: Convertor control clock disabling unsuccessful **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Mcu_lConvCtrlDeInit(void)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_CONVERTER_CLC ConvCtrlClcVal;
  Std_ReturnType ConvCtrlInitStatus = E_OK;

  ConvCtrlClcVal.U = CONVCTRL_CLC.U;
  ConvCtrlClcVal.B.DISR = CONVERTER_KERNEL_DISABLE;
  MCU_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(&CONVCTRL_CLC.U,
      ConvCtrlClcVal.U);

  /* [cover parentID={46FF1644-CB25-4986-96D2-8135FB009A46}]
   * Is Converter control module clock Disabled
   * [/cover] */
  if (CONVCTRL_CLC.B.DISS != CONVERTER_KERNEL_CLK_DISABLED)
  {
    ConvCtrlInitStatus = E_NOT_OK;
    /* [cover parentID={4B430AF8-BB30-49d5-88D0-A58F46F63EF2}]
     * If Production error Reporting is ON*/
    #if (MCU_E_CONVCTRL_CLC_DISABLE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
    /*Report Production error for CLC disable failed*/
    /*[cover parentID={84234C2B-11B9-4fd7-8B14-90D601156E0F}]
    [/cover]*/
    /* [cover parentID={2A07E7AE-36D8-48a6-BF74-D004D646F587}]
     * Report Production error: Event failed
     * [/cover] */
    Mcu_lReportDemError(MCU_E_CONVCTRL_CLC_DISABLE_ERR,
                          DEM_EVENT_STATUS_FAILED);
    #endif
  }
  #if (MCU_E_CONVCTRL_CLC_DISABLE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
  else
  {
    /* Report Production error for CLC disable passed*/
    /* [cover parentID={8456F272-DE17-4cfe-AA12-F9936338EDF7}]
     * Report Production error: Event Passed
     * [/cover] */
    Mcu_lReportDemError(MCU_E_CONVCTRL_CLC_DISABLE_ERR,
                          DEM_EVENT_STATUS_PASSED);
  }
  #endif
  /*[/cover] */
  /*[cover parentID={FEA9865F-C6C1-48ff-9E97-BBAEC9DB35C8}][/cover]
    [cover parentID={618DE6D3-9206-47a8-933D-AC6800E55FA1}][/cover]*/
  return ConvCtrlInitStatus;
}
#endif
/* End of #if (MCU_DEINIT_API == STD_ON) */

#if (MCU_INIT_CLOCK_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={4703EDBE-9E52-46dd-A527-B83BDD55D4C2}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType Mcu_lInitOscClock(void)      **
**                                                                            **
** Description     : This function sets up the oscillator clock based on      **
**                   configuration                                            **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK : Oscillator initialization successful.             **
**                   E_NOT_OK : Oscillator initialization failed.             **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Mcu_lInitOscClock(void)
{
  Std_ReturnType RetValue = (Std_ReturnType)E_OK;
  Mcu_SystemPllConfigType PllSource;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_OSCCON OscconVal;

  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_SYSPLLCON0 Syspllcon0Val;

  uint32 OscconPllHv, OscconPllLv;
  volatile uint32 TimeoutCtr;

  PllSource = Mcu_ConfigPtr->
      McuClockSettingPtr[Mcu_ClockSetting].SystemPllCfg;

  /*Setup PLL input source for OSC watchdog monitoring*/
  Syspllcon0Val.U = MCU_SYSPLLCON_DEFAULT_VAL;
  Syspllcon0Val.B.INSEL = PllSource.Insel;

  MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_SYSPLLCON0.U,
      (uint32)Syspllcon0Val.U);


  /* [cover parentID={FE48A89D-E543-4258-BD8A-9A05C2CA52DF}]
   * Is Oscillator used as PLL Source
   * [/cover] */
  if (MCU_PLL_INSEL_OSCCLK == (uint32)PllSource.Insel)
  {
    /*
      Oscillator is used as PLL source:
      1. Configure Oscillator mode to be enabled.
      2. Set OSCVAL value and perform oscillator watchdog reset
      3. Wait (with timeout) until Oscillator frequency becomes
         usable. (check against Lower and Upper ranges both)
      4. In case Oscillator setup timeout expires, Report Production error and
         return Mcu_InitClock() with an error.
    */
    OscconVal.U = SCU_OSCCON.U;
    OscconVal.U |= MCU_OSC_CAPACITANCE_EN;
    OscconVal.B.MODE = MCU_OSC_MODE;
    OscconVal.B.OSCVAL = MCU_OSCVAL_REG_VALUE;
    OscconVal.B.OSCRES = 0x1U;
  }
  /* [cover parentID={EE6330D3-8F5F-44da-A00C-6AD0DEE928ED}]
   * Is Backup clock used as PLL Source
   * [/cover] */
  else if (MCU_PLL_INSEL_BACKUP == (uint32)PllSource.Insel)
  {
    OscconVal.U = SCU_OSCCON.U;
    OscconVal.B.MODE = MCU_OSC_DIS_POWERSAVING_MODE;
  }
  else
  {
    OscconVal.U = SCU_OSCCON.U;
    OscconVal.B.MODE = MCU_OSC_DIS_POWERSAVING_MODE;
    OscconVal.B.OSCVAL = MCU_SYSCLK_OSCVAL;
    OscconVal.B.OSCRES = 0x1U;
  }

    MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_OSCCON.U,
        (uint32)(OscconVal.U));

  /*Skip oscillator watchdog monitoring for Backup clock*/
  /* [cover parentID={E76971BB-329F-4e6c-86D9-A8C20B468731}]
   * Is Oscillator/SYSCLK used as PLL Source
   * [/cover] */
  if (MCU_PLL_INSEL_BACKUP != (uint32)PllSource.Insel)
  {
    /* Check for oscillator frequency available to use */
    TimeoutCtr = MCU_VALIDATE_OSC_FREQ_TIMEOUT;
    OscconPllHv = (uint32)SCU_OSCCON.B.PLLHV;
    OscconPllLv = (uint32)SCU_OSCCON.B.PLLLV;

    /* [cover parentID={8E8D5F32-E248-4686-8E4B-DA6B51C84FDD}]
     * Wait till Oscillator frequency is Usable
     * [/cover] */
    while ((TimeoutCtr > 0x0U) &&
           ((0x0U == OscconPllHv) ||
            (0x0U == OscconPllLv)))
    {
      OscconPllHv = (uint32)SCU_OSCCON.B.PLLHV;
      OscconPllLv = (uint32)SCU_OSCCON.B.PLLLV;

      TimeoutCtr--;
    }

    /* [cover parentID={96765643-8130-45dc-BE46-D0ED45DFF70F}]
     * Did Timeout occur and is Oscillator frequency unstable
     * [/cover] */
    if (0x0U == TimeoutCtr)
    {
      /* [cover parentID={D435DD7F-C13D-479c-A39B-1B58E6E68ED8}]
       * If Production error Reporting is ON*/
      #if (MCU_E_OSC_FAILURE_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
      /* Report Production error for oscillator error */
      /* [cover parentID={AF6AE147-0A47-495f-985D-4CF4C74F555B}]
       * Report Production error: Event Failed
       * [/cover] */
      /* [cover parentID={EFE3583A-E5A7-42a0-9268-DBB266EFEF3F}]
       * Report Production error: Event Failed
       * [/cover] */
      Mcu_lReportDemError(MCU_E_OSC_FAILURE,
                            DEM_EVENT_STATUS_FAILED);
      #endif
      /*[/cover] */
      RetValue = (Std_ReturnType)E_NOT_OK;
    }
    /* [cover parentID={D592B856-1E85-4899-8A3D-D7878A9A5FAB}]
     * Is Oscillator frequency stable
     * [/cover] */
    else
    {
      /* [cover parentID={58DB094C-DCE1-4aa6-A4CF-67996FDE4A14}]
       * If Production error Reporting is ON*/
      #if (MCU_E_OSC_FAILURE_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
      /* Report Production error for oscillator passed */
      /* [cover parentID={98F8323C-7BDB-4174-9DC6-A3DDB5B17E4F}]
       * Report Production error: Event Passed
       * [/cover] */
      Mcu_lReportDemError(MCU_E_OSC_FAILURE,
                            DEM_EVENT_STATUS_PASSED);
      #endif
      /* [/cover] */
    }
  }
  /*[cover parentID={9505B7AA-A7C9-47fa-952E-E87F4AFF0388}][/cover]
  [cover parentID={88DE7537-9A2A-4fa6-9238-17283A4379BA}][/cover]*/
  return RetValue;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={FF9298A9-12CB-4e56-B982-F4C439743E99}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType Mcu_lInitPllClock(void)      **
**                                                                            **
** Description     : This function enables and initializes all PLLs as        **
**                   per configuration.                                       **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK : PLLs initialization successful.                   **
**                   E_NOT_OK : PLLs initialization failed.                   **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Mcu_lInitPllClock(void)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_SYSPLLCON0 Syspllcon0Val;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_SYSPLLCON1 Syspllcon1Val;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_PERPLLCON0 Perpllcon0Val;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_PERPLLCON1 Perpllcon1Val;
  volatile uint32 TimeoutCtr;
  uint32 SysPllStat, PerPllStat;
  uint32 ResetDelayTicks, BaseSTMTick, CurrSTMTick, DelayTickResolution;
  Std_ReturnType RetValue = (Std_ReturnType)E_OK;

  /*
    System PLL configuration:
    1. Setup system Input source selection, PLL mode, PDIV, NDIV values
       of system PLL.
    2. Setup K2DIV divider value (corresponding fSOURCE0 = fBACKUP).
    3. move the system PLL to normal mode.
  */

  Syspllcon0Val.U = SCU_SYSPLLCON0.U;
  Syspllcon0Val.B.NDIV = Mcu_ConfigPtr->McuClockSettingPtr
                         [Mcu_ClockSetting].SystemPllCfg.SysPllNDiv;
  Syspllcon0Val.B.PDIV = Mcu_ConfigPtr->McuClockSettingPtr
                         [Mcu_ClockSetting].SystemPllCfg.SysPllPDiv;
  Syspllcon0Val.B.PLLPWD = 0x1U;
  Syspllcon0Val.U = (uint32)Syspllcon0Val.U & (~MCU_SYSPLLCON0_RSRVD_RW_MASK);
  /* [cover parentID={C65D3D60-D9B9-4061-9202-604BBDD64B13}]
   * Check if Frequency Modulation is Enabled
   * [/cover] */
  if (0x1U == Mcu_ConfigPtr->
      McuClockSettingPtr[Mcu_ClockSetting].SystemPllCfg.FmPllEn)
  {
    /* Configure frequency modulation settings */
    Syspllcon0Val.B.MODEN = Mcu_ConfigPtr->McuClockSettingPtr
                            [Mcu_ClockSetting]
                            .SystemPllCfg.FmPllEn;
    MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_SYSPLLCON2.U,
        (uint32)Mcu_ConfigPtr->McuClockSettingPtr
        [Mcu_ClockSetting].SystemPllCfg.ModulationAmplitude);
  }
  Syspllcon1Val.U = SCU_SYSPLLCON1.U;
  Syspllcon1Val.B.K2DIV = ((uint32)Mcu_ConfigPtr->
                           McuClockSettingPtr[Mcu_ClockSetting]
  /*  MISRA2012_RULE_10_3_JUSTIFICATION: Assignment to narrower type as
      a register bit-field value (K2DIV : 3bit wide) is written and
      configuration generation limits possible values between 0 - 7.*/
                            .BackupFreqKDiv & MCU_PLL_FBACK_KDIV_MASK);

  MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_SYSPLLCON1.U,
      (uint32)Syspllcon1Val.U);

  /* [cover parentID={B66DCB81-DB2F-48c0-BBD1-1DD2124BCC32}]
   * Setup system PLL mode, PDIV, NDIV values of system PLL and move System PLL
   * into Normal mode [/cover] */
  MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_SYSPLLCON0.U,
      (uint32)Syspllcon0Val.U);

  /*
    Peripheral PLL configuration:
    1. Setup  PDIV, NDIV, K3DIVBY values of peripheral PLL.
    2. Setup K2DIV and K3DIV divider value
       (corresponding fSOURCE1 = fBACKUP and fSOURCE0 = fBACKUP).
    3. move the peripheral PLL to normal mode.
  */
  Perpllcon0Val.U = SCU_PERPLLCON0.U;
  Perpllcon1Val.U = SCU_PERPLLCON1.U;
  Perpllcon0Val.B.DIVBY = Mcu_ConfigPtr->McuClockSettingPtr
                          [Mcu_ClockSetting]
                          .PeripheralPllCfg.K3DivByPass;
  Perpllcon0Val.B.NDIV = Mcu_ConfigPtr->McuClockSettingPtr
                         [Mcu_ClockSetting]
                         .PeripheralPllCfg.PerPllNDiv;
  Perpllcon0Val.B.PDIV = Mcu_ConfigPtr->McuClockSettingPtr
                         [Mcu_ClockSetting]
                         .PeripheralPllCfg.PerPllPDiv;
  Perpllcon0Val.B.PLLPWD = 0x1U;
  Perpllcon0Val.U = (uint32)Perpllcon0Val.U &
                    (~MCU_PERPLLCON0_RSRVD_RW_MASK);

  Perpllcon1Val.B.K2DIV = (((uint32)Mcu_ConfigPtr->McuClockSettingPtr
                            [Mcu_ClockSetting]
                            .BackupFreqKDiv >>
                            MCU_PERPLL_K2DIV_BITPOS_MASK) &
  /* MISRA2012_RULE_10_3_JUSTIFICATION: Assignment to narrower type as
   a register bit-field value (K2DIV : 3bit wide) is written and
   configuration generation limits possible values between 0 - 7. */
  MCU_PLL_FBACK_KDIV_MASK);
  Perpllcon1Val.B.K3DIV = (((uint32)Mcu_ConfigPtr->McuClockSettingPtr
                            [Mcu_ClockSetting]
                            .BackupFreqKDiv >>
                            MCU_PERPLL_K3DIV_BITPOS_MASK) &
  /* MISRA2012_RULE_10_3_JUSTIFICATION: Assignment to narrower type as
  a register bit-field value (K3DIV : 3bit wide) is written and
  configuration generation limits possible values between 0 - 7. */
                            MCU_PLL_FBACK_KDIV_MASK);

  MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_PERPLLCON1.U,
      (uint32)(Perpllcon1Val.U));
  MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_PERPLLCON0.U,
      (uint32)(Perpllcon0Val.U));

  CurrSTMTick = Mcal_DelayGetTick();
  BaseSTMTick = CurrSTMTick;
  DelayTickResolution = Mcal_DelayResetTickCalibration();
  ResetDelayTicks = (MCU_PLLPWD_DELAY / DelayTickResolution);

  /* [cover parentID={4F263A95-088F-44fa-91BD-6B8C8A263859}]
   * Provide a delay for status update of PLLs to Normal mode
   * [/cover] */
  while ((uint32)((CurrSTMTick - BaseSTMTick) & MCU_STM_TICK_OVERFLOW) <
         ResetDelayTicks)
  {
    CurrSTMTick = Mcal_DelayGetTick();
  }

  /*
    PLL mode check:
    1. Wait (with timeout) until PLLs have moved to normal mode.
    2. In case of timeout, raise a Production error and return Mcu_InitClock()
       with an Error.
  */

  TimeoutCtr = MCU_PLL_PWDSTAT_TIMEOUT;
  SysPllStat = (uint32)SCU_SYSPLLSTAT.B.PWDSTAT;
  PerPllStat = (uint32)SCU_PERPLLSTAT.B.PWDSTAT;

  /* [cover parentID={58BD1595-02D2-4f84-8D1A-069CF2DBAC2E}]
   * Wait till PLL has entered Normal mode of Operation
   * [/cover] */
  while ((TimeoutCtr > 0x0U) && ((0x1U == SysPllStat) ||
                                 (0x1U == PerPllStat)))
  {
    SysPllStat = (uint32)SCU_SYSPLLSTAT.B.PWDSTAT;
    PerPllStat = (uint32)SCU_PERPLLSTAT.B.PWDSTAT;
    TimeoutCtr--;
  }
  /* [cover parentID={61CD80D1-C07D-44f4-A1AE-B24BC1CFEE0A}]
   * Is System PLL not in Normal mode
   * [/cover] */
  if (0x1U == SCU_SYSPLLSTAT.B.PWDSTAT)
  {
    /* [cover parentID={D0981CC1-A188-4d16-80E7-DBB84F068208}]
         * If Production error Reporting is ON*/
    #if (MCU_E_SYSTEM_PLL_TIMEOUT_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
    /*      [/cover] */
    /*Report Production error for system PLL normal mode timeout error*/
    /* [cover parentID={90FFE3CE-27EC-4afa-8CCF-1621ECE7D6B7}]
    Report Production error: Event Failed for System PLL
    [/cover] */
    Mcu_lReportDemError(MCU_E_SYSTEM_PLL_TIMEOUT_ERR,
                          DEM_EVENT_STATUS_FAILED);
    #endif

    RetValue = (Std_ReturnType)E_NOT_OK;
  }
  #if (MCU_E_SYSTEM_PLL_TIMEOUT_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
  else
  {
    /*Report Production error for system PLL normal mode timeout passed*/
    /* [cover parentID={DD81C8CB-F2A4-49a3-9394-1BCDEA26AB24}]
    Report Production error: Event Passed for System PLL
    [/cover] */
    Mcu_lReportDemError(MCU_E_SYSTEM_PLL_TIMEOUT_ERR,
                          DEM_EVENT_STATUS_PASSED);
  }
  #endif
  /* [/cover] */
  /* [cover parentID={57181DC5-9A40-4f3c-A51A-BBDF80BC9337}]
   * Is Peripheral PLL not in Normal mode
   * [/cover] */
  if (0x1U == SCU_PERPLLSTAT.B.PWDSTAT)
  {
    /* [cover parentID={9F93092D-762B-4142-9583-4E38B2199F3C}]
     * If Production error Reporting is ON*/

    #if (MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
    /*Report Production error for peripheral PLL normal mode timeout error*/
    /* [cover parentID={3F2E931E-63B0-44d9-AB0C-24BD894781B2}]
    Report Production error: Event Failed for Peripheral PLL
    [/cover] */
    Mcu_lReportDemError(MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR,
                          DEM_EVENT_STATUS_FAILED);
    #endif

    RetValue = (Std_ReturnType)E_NOT_OK;
  }
  #if (MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
  else
  {
    /*Report Production error for peripheral PLL normal mode timeout passed*/
    /* [cover parentID={46C928CC-9161-485b-BBC1-64C3CE982AD1}]
    Report Production error: Event Passed for Peripheral PLL
    [/cover] */
    Mcu_lReportDemError(MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR,
                          DEM_EVENT_STATUS_PASSED);
  }
  #endif
  /*[/cover] */
  /* [cover parentID={D1FCDBAC-5B14-4c5b-9D28-E9BF6FEEBBC4}]
   * Are PLLs properly moved to Normal mode
   * [/cover] */
  if ((Std_ReturnType)E_NOT_OK != RetValue)
  {
    /* Check if KDIV values are applied and ready to use */
    /* [cover parentID={84D31529-8A38-49fc-8F44-5291CF69FF1E}]
     * Check if K divider values of System and Peripheral PLLs are available
     * and ready to use
     * [/cover] */
    RetValue = Mcu_lInitPllKDivCheck();
  }
  /* [cover parentID={77BC8852-2CBD-46b4-AB77-1E0366D687A6}]
   * Are new K divider values ready to use
   * [/cover] */
  if ((Std_ReturnType)E_NOT_OK != RetValue)
  {
    /*
      PLL Lock detection:
      1. Initiate lock detection of both PLLs.
    */

    Syspllcon0Val.U = SCU_SYSPLLCON0.U;
    Syspllcon0Val.B.RESLD = 0x1U;

    MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_SYSPLLCON0.U,
        (uint32)(Syspllcon0Val.U));
    Perpllcon0Val.U = SCU_PERPLLCON0.U;
    Perpllcon0Val.B.RESLD = 0x1U;

    MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_PERPLLCON0.U,
        (uint32)(Perpllcon0Val.U));
  }
  /*[cover parentID={1AD994DF-2717-46c8-B9DB-E71B2AA48541}][/cover]
    [cover parentID={7BCB45ED-C96E-4dec-AC12-A61C433346B0}][/cover]*/
  return RetValue;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={81B068A9-93F7-485b-A73D-1B77CEF54A57}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType Mcu_lInitPllKDivCheck        **
**                                                                  (void)    **
**                                                                            **
** Description     : This function Checks if KDIV values are correctly applied**
**                   during Mcu_lInitPllClock() function                      **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK : PLLs KDIV value successfully applied.             **
**                   E_NOT_OK : PLLs KDIV value application failed.           **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Mcu_lInitPllKDivCheck(void)
{
  volatile uint32 TimeoutCtr;
  uint32 SysPllStat, PerPllStat, PerPllStat1;
  Std_ReturnType RetValue = (Std_ReturnType)E_OK;
  /*
    PLL K2DIV check:
    1. Wait (with timeout) until K2DIV values are effectively applied
       for system and peripheral PLLs.
    2. In case of timeout, raise a Production error and return Mcu_InitClock()
       with an Error.
  */
  TimeoutCtr = MCU_PLL_KDIVRDY_TIMEOUT;
  SysPllStat = (uint32)SCU_SYSPLLSTAT.B.K2RDY;
  PerPllStat = (uint32)SCU_PERPLLSTAT.B.K2RDY;
  PerPllStat1 = (uint32)SCU_PERPLLSTAT.B.K3RDY;

  /* [cover parentID={94D12598-0F7C-4dde-A79A-707678140F29}]
   * Provide delay for K2 divider values to get effectively
   * applied for System and Peripheral PLLs
   * [/cover] */
  while ((TimeoutCtr > 0x0U) && ((0x0U == SysPllStat) ||
                                 (0x0U == PerPllStat) ||
                                 (0x0U == PerPllStat1)))
  {
    SysPllStat = (uint32)SCU_SYSPLLSTAT.B.K2RDY;
    PerPllStat = (uint32)SCU_PERPLLSTAT.B.K2RDY;
    PerPllStat1 = (uint32)SCU_PERPLLSTAT.B.K3RDY;
    TimeoutCtr--;
  }

  /* [cover parentID={1240474A-34D7-4f85-BF74-C499D9FFFEC4}]
   * Is System PLL K2 Divider value not Ready
   * [/cover] */
  if (0x0U == SCU_SYSPLLSTAT.B.K2RDY)
  {
    /* [cover parentID={6CAF4879-1020-450b-B9C1-E2F0B7C1DEF0}]
     * If Production error Reporting is ON*/
    #if (MCU_E_SYSTEM_PLL_TIMEOUT_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
    /*Report Production error for system PLL error*/
    /* [cover parentID={F6943986-7B4D-4c35-9612-EF5675B9DD8C}]
     * Report Production error: Event Failed for System PLL
    [/cover] */
    Mcu_lReportDemError(MCU_E_SYSTEM_PLL_TIMEOUT_ERR,
                          DEM_EVENT_STATUS_FAILED);
    #endif

    RetValue = (Std_ReturnType)E_NOT_OK;
  }
  #if (MCU_E_SYSTEM_PLL_TIMEOUT_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
  else
  {
    /*Report Production error for system PLL passed*/
    /* [cover parentID={3ADC86EC-CBEF-49cb-A039-D7F8AEDDAA4D}]
     * Report Production error: Event Passed for System PLL
    [/cover] */
    Mcu_lReportDemError(MCU_E_SYSTEM_PLL_TIMEOUT_ERR,
                          DEM_EVENT_STATUS_PASSED);
  }
  #endif
  /*[/cover] */
  PerPllStat = (uint32)SCU_PERPLLSTAT.B.K2RDY;
  PerPllStat1 = (uint32)SCU_PERPLLSTAT.B.K3RDY;
  /* [cover parentID={2FF8AB76-CC8C-4500-B231-45C7501BC941}]
   * Are Peripheral PLL K2 and K3 Divider values Ready
   * [/cover] */
  if ((0x0U == PerPllStat) || (0x0U == PerPllStat1))
  {
    /* [cover parentID={A0B010C4-5ACF-423d-81C9-86A1F8D9AD56}]
     * If Production error Reporting is ON*/
    #if (MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
    /*Report Production error for peripheral PLL error*/
    /* [cover parentID={81373284-4D27-4f23-9A27-59B17DA7F2F4}]
     * Report Production error: Event Failed for Peripheral PLL
    [/cover] */
    Mcu_lReportDemError(MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR,
                          DEM_EVENT_STATUS_FAILED);
    #endif

    RetValue = (Std_ReturnType)E_NOT_OK;
  }
  #if (MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
  else
  {
    /*Report Production error for peripheral PLL passed*/
    /* [cover parentID={68CDA2FC-A0E8-4f0c-91D5-E0B3B50F1940}]
     * Report Production error: Event Passed for Peripheral PLL
     [/cover] */
    Mcu_lReportDemError(MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR,
                          DEM_EVENT_STATUS_PASSED);
  }
  #endif
  /*[/cover] */
  /*[cover parentID={5DB95EFD-FBE8-4b0f-840E-DC2979F3EB64}][/cover]
  [cover parentID={6E672C64-E4F6-4b64-A0A1-9BE5F2117063}][/cover]*/
  return RetValue;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={41ACB226-21EB-4197-9C76-B7D2C8E71288}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType Mcu_lInitClockTree(void)     **
**                                                                            **
** Description     : This local function initializes clock tree dividers for  **
**                   to configure various clocks of CCU                       **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK : CCUCONx divider configuration successful          **
**                   E_NOT_OK : CCUCONx divider configuration failed          **
                                                                              **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Mcu_lInitClockTree(void)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_CCUCON0 Ccucon0Val;
  uint32 TimeoutCtr, Ccucon0Lck, Ccucon5Lck;
  #if (MCU_SAFETY_ENABLE == STD_ON)
  uint32 Ccucon3Lck, Ccucon4Lck;
  #endif
  Std_ReturnType RetValue = (Std_ReturnType)E_OK;

  /* Setup CPU clock dividers */
  /* [cover parentID={81FEBF1D-470E-4f5c-A469-10CC011B4151}]
   * Set up CPU Clock Dividers
   * [/cover] */
  Mcu_lInitCcuConCpuReg();

  /*
    1. Setup clock divider bit-fields of CCUCON0, CCUCON1, CCUCON2
       and CCUCON5 registers
    2. Update only the Divider bit-fields of CCUCON0.
    Bit-15 (Reserved bit position) is made zero during configuration generation
  */

  /* Write CLKSEL bits of CCUCON1 and CCUCON2 as zero before update. */

  RetValue = Mcu_lInitCcuCon12();

  /*
    Update for CCUCON0 register divider values
    1. Check if CCUCON0 register lock is free and report the Production error
       accordingly.
    2. Update the register
  */
  /* [cover parentID={2068F600-417B-4813-87EB-017233692E38}]
   * Is CCUCON1 and CCUCON2 initialization successful
   * [/cover] */
  if (E_OK == RetValue)
  {
    Ccucon0Val.U = SCU_CCUCON0.U;
    Ccucon0Val.U = (((uint32)Ccucon0Val.U & (~MCU_CCUCON0_DIV_BIT_MASK)) |
                    ((Mcu_ConfigPtr->McuClockSettingPtr
                      [Mcu_ClockSetting].PllDistributionCfgPtr->Ccucon0) &
                     MCU_CCUCON0_DIV_BIT_MASK));
    Ccucon0Val.B.UP = 0x1U;

    TimeoutCtr = MCU_CCUCON0_LCK_TIMEOUT;

    Ccucon0Lck = (uint32)SCU_CCUCON0.B.LCK;
    Ccucon5Lck = (uint32)SCU_CCUCON5.B.LCK;

    /* [cover parentID={03A77F59-E6A5-416b-9ADC-E2403215A474}]
     * Provide Delay for Ccucon5 register to get locked
     * [/cover] */
    while ((TimeoutCtr > 0x0U) &&
           ((0x1U == Ccucon0Lck) || (0x1U == Ccucon5Lck)))
    {
      Ccucon0Lck = (uint32)SCU_CCUCON0.B.LCK;
      Ccucon5Lck = (uint32)SCU_CCUCON5.B.LCK;

      TimeoutCtr--;
    }
    /* [cover parentID={CEC16590-6658-413c-80D9-EEF4079E6760}]
       * Are Ccucon0 and Ccucon5 not locked
       * [/cover] */
    if ((0x1U == Ccucon0Lck) || (0x1U == Ccucon5Lck))
    {
      /* [cover parentID={A07D9DCC-8EF2-48fc-A97F-4F688B8EBE72}]
       * If Production error Reporting is ON*/
      #if (MCU_E_CCUCON_UPDATE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
      /* Report Production error for system PLL error */
      /* [cover parentID={CA6A9A2F-7F4B-4fdc-8C0F-35090FEEA944}]
       Report Production error: Event Failed
       [/cover] */
      /*[cover parentID={86FD62A6-E150-44c5-B439-37325BCA944E} ]
        [/cover]*/
      /* [cover parentID={E4ED1A33-4973-4142-80DC-6736A98D2B64}]
       * Report Production error: Event Failed
       * [/cover] */
      Mcu_lReportDemError(MCU_E_CCUCON_UPDATE_ERR,
                            DEM_EVENT_STATUS_FAILED);
      #endif

      RetValue = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
      #if (MCU_E_CCUCON_UPDATE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
      /* Report Production error for system PLL error */
      /* [cover parentID={95F25D8B-584B-487e-B5E5-2AFDB07C179D}]
      Report Production error: Event Passed
      [/cover] */
      /* [cover parentID={BE1F873C-CCE1-4a48-B108-F80A9998CED4}]
       * Report Production error: Event Passed
       * [/cover] */
      Mcu_lReportDemError(MCU_E_CCUCON_UPDATE_ERR,
                            DEM_EVENT_STATUS_PASSED);
      #endif
      /*[/cover] */


      MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_CCUCON5.U,
          Mcu_ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
          .PllDistributionCfgPtr->Ccucon5);


      MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_CCUCON0.U,
          (uint32)(Ccucon0Val.U));

      /* [cover parentID={F4F43087-7B13-40d9-8E65-3A3702D047FC}]
       * If Safety is ON
       * [/cover] */
      #if (MCU_SAFETY_ENABLE == STD_ON)
      TimeoutCtr = MCU_CCUCON0_LCK_TIMEOUT;

      Ccucon3Lck = (uint32)SCU_CCUCON3.B.LCK;
      Ccucon4Lck = (uint32)SCU_CCUCON4.B.LCK;

      /* [cover parentID={A4442ECF-7A69-4504-B256-D6F2B3E0784B}]
       * Provide delay for Ccucon3 and Ccucon4 to get locked
       * [/cover] */
      while ((TimeoutCtr > 0x0U) &&
             ((0x1U == Ccucon3Lck) || (0x1U == Ccucon4Lck)))
      {
        Ccucon3Lck = (uint32)SCU_CCUCON3.B.LCK;
        Ccucon4Lck = (uint32)SCU_CCUCON4.B.LCK;

        TimeoutCtr--;
      }

      /* [cover parentID={D9CE7326-51F2-4093-B391-82824EC64402}]
        * Is Ccucon3 OR Ccucon4 locked
        * [/cover] */
      if ((0x1U == Ccucon3Lck) || (0x1U == Ccucon4Lck))
      {
        #if (MCU_E_CCUCON_UPDATE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
        /* Report Production error for system PLL error */
        /* [cover parentID={CA6A9A2F-7F4B-4fdc-8C0F-35090FEEA944}]
         Report Production error: Event Failed
         [/cover] */
        /*[cover parentID={86FD62A6-E150-44c5-B439-37325BCA944E} ]
          [/cover]*/
        Mcu_lReportDemError(MCU_E_CCUCON_UPDATE_ERR,
                              DEM_EVENT_STATUS_FAILED);
        #endif

        RetValue = (Std_ReturnType)E_NOT_OK;
      }
      else
      {
        #if (MCU_E_CCUCON_UPDATE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
        /* Report Production error for system PLL error */
        /* [cover parentID={95F25D8B-584B-487e-B5E5-2AFDB07C179D}]
        Report Production error: Event Passed
        [/cover] */
        Mcu_lReportDemError(MCU_E_CCUCON_UPDATE_ERR,
                              DEM_EVENT_STATUS_PASSED);
        #endif


        /*[cover parentID={8B7E1864-49D2-455a-8408-F360851B5222}][/cover]*/
        MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_CCUCON3.U,
            Mcu_ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
            .PllDistributionCfgPtr->Ccucon3);


        /*[cover parentID={2E101CAA-7042-49e7-948D-D56BAA7A280B}][/cover]*/
        MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_CCUCON4.U,
            Mcu_ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
            .PllDistributionCfgPtr->Ccucon4);
      }
      #endif
    }

    /* [cover parentID={846C6270-6588-418e-832B-F9B6D8360AB7}]
     * Is CPU and other frequencies under clock tree configuration successful
     * [/cover] */
    if ((Std_ReturnType)E_NOT_OK != RetValue)
    {

      MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_EXTCON.U,
          (uint32)Mcu_ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
          .ExternalClockCfg);
    }
  }
  /*[cover parentID={FCF67DF4-616B-482b-A6D7-5C77FF58A650}][/cover]
    [cover parentID={4DBE2A0E-FBAB-4ea9-A671-206F5E2BC711} ][/cover]*/
  return RetValue;
}

#endif /* End of (MCU_INIT_CLOCK_API == STD_ON) */

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={7E8F9BD6-C6B1-4c6e-8A41-9C1E790AE91E}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType Mcu_lSwitchToBackUpClockFreq **
**                                    (                                       **
**                                      const uint8 ApiId,                    **
**                                      const Mcu_ClockType ClockSettingIndex **
**                                    )                                       **
**                                                                            **
** Description     : This function safely moves the clock tree to backup clock**
**                   frequency and change clock tree distribution source as   **
**                   backup clock                                             **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : ApiId              - Service Id of the API in which      **
**                                        the local function is called        **
**                   ClockSettingIndex  - Index of the clock configuration    **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK : Pll ramp to backup clock successful               **
**                   E_NOT_OK : Pll ramp to backup clock failed               **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Mcu_lSwitchToBackUpClockFreq(
  const uint8 ApiId,
  const Mcu_ClockType ClockSettingIndex)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_SYSPLLCON1 Syspllcon1Val;

  uint32 SyspllK2Div, SyspllPDiv, SyspllNDiv, KDivRampDelayTicks;
  uint32 PllBackupFreqKDiv, SysPllStat;
  uint32 DelayTickResolution, BaseSTMTick, CurrSTMTick;
  volatile uint32 TimeoutCtr;
  Std_ReturnType RetValue = (Std_ReturnType)E_OK;

  /*
    Ramp system PLL (PLL0) to backup frequency:
    1. Calculate the K2DIV value corresponding to backup frequency (target) and
       current K2DIV value.
    2. Change (increase/decrease) K2DIV value until targeted K2DIV value is
       not achieved.
    3. Wait (with timeout) until new K2DIV value is effective.
    4. Provide configured delay in between each K2DIV change
  */

  SyspllPDiv = (uint32)SCU_SYSPLLCON0.B.PDIV;
  SyspllNDiv = (uint32)SCU_SYSPLLCON0.B.NDIV;

  /* [cover parentID={C23D9684-D89E-4ae6-84A1-B1F46EA2AC29}]
   * Calculate Backup freq K div value based on Oscillator or Backup
   * [/cover] */
  if (SCU_SYSPLLCON0.B.INSEL == MCU_PLL_INSEL_OSCCLK)
  {
    PllBackupFreqKDiv = (uint32)((SyspllNDiv + 0x1U) * MCU_MAIN_OSC_FREQ) /
                        (MCU_BACKUP_FREQ * (SyspllPDiv + 0x1U ));

  }
  else if (SCU_SYSPLLCON0.B.INSEL == MCU_PLL_INSEL_BACKUP)
  {
    PllBackupFreqKDiv = (uint32)(SyspllNDiv + 0x1U) / (SyspllPDiv + 0x1U);
  }
  else
  {
    PllBackupFreqKDiv = (uint32)((SyspllNDiv + 0x1U) * MCU_SYSCLK_FREQ) /
                        (MCU_BACKUP_FREQ * (SyspllPDiv + 0x1U ));
  }

  PllBackupFreqKDiv = PllBackupFreqKDiv - 0x1U;
  SyspllK2Div = (uint32)SCU_SYSPLLCON1.B.K2DIV;

  /* [cover parentID={1D645637-0A4A-451e-AC9A-73992C70AB01}]
   * Ramp System PLL to Backup frequency
   * [/cover] */
  while ((PllBackupFreqKDiv != SyspllK2Div) &&
         ((Std_ReturnType)E_OK == RetValue))
  {
    if (PllBackupFreqKDiv > SyspllK2Div)
    {
      SyspllK2Div++;
      KDivRampDelayTicks = Mcu_ConfigPtr->
                           McuClockSettingPtr[ClockSettingIndex]
                           .SysPllK2DivStepUpChangeDelay;
    }
    else
    {
      SyspllK2Div--;
      KDivRampDelayTicks = Mcu_ConfigPtr->
                           McuClockSettingPtr[ClockSettingIndex]
                           .SysPllK2DivStepDownChangeDelay;
    }

    /* Write new KDIV value */

    Syspllcon1Val.U = SCU_SYSPLLCON1.U;
    /* MISRA2012_RULE_10_3_JUSTIFICATION: Assignment to narrower type as
       a register bit-field value (K2DIV : 3bit wide) is written and possible
       target KDIV values are between 0 - 7 therefore writes are limited within
       expected range. */
    Syspllcon1Val.B.K2DIV = SyspllK2Div;

    /* [cover parentID={E76B9381-DF99-4f6e-B2DD-F23C8858C140}]
     * Is this local function called for local initialization
     * [/cover] */
    if (ApiId == MCU_API_INITCLOCK)
    {
      MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_SYSPLLCON1.U,
          (uint32)(Syspllcon1Val.U));
    }
    else
    {
      MCU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG(&SCU_SYSPLLCON1.U,
          (uint32)(Syspllcon1Val.U));
    }

    /* Wait until updated KDIV value is effective */
    TimeoutCtr = MCU_PLL_KDIVRDY_TIMEOUT;
    SysPllStat = (uint32)SCU_SYSPLLSTAT.B.K2RDY;

    /* [cover parentID={C6CB2374-F89C-4bb0-A375-EB2EF0495F47}]
     * Provide delay for new value of K2 divider to get reflected
     * [/cover] */
    while ((TimeoutCtr > 0x0U) && (0x0U == SysPllStat))
    {
      SysPllStat = (uint32)SCU_SYSPLLSTAT.B.K2RDY;
      TimeoutCtr--;
    }

    /* [cover parentID={90CF8EBE-2C60-4c43-A1FE-9B43082267A8}]
     * Did timeout occur and is new K2 divider value still not available
     * [/cover] */
    if (0x0U == TimeoutCtr)
    {
      /* [cover parentID={DA8EFA29-B606-49ea-A3ED-95ACCDCC0C26}]
       * If Production error Reporting is ON*/
      #if (MCU_E_SYSTEM_PLL_TIMEOUT_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
      /*Report Production error for system PLL error*/
      /* [cover parentID=]
       * Report Production error: Event Failed
       * [/cover] */
      Mcu_lReportDemError(MCU_E_SYSTEM_PLL_TIMEOUT_ERR,
                            DEM_EVENT_STATUS_FAILED);
      #endif
      RetValue = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
      #if (MCU_E_SYSTEM_PLL_TIMEOUT_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
      /*Report Production error for system PLL error*/
      /* [cover parentID=]
       * Report Production error: Event Passed
       * [/cover] */
      Mcu_lReportDemError(MCU_E_SYSTEM_PLL_TIMEOUT_ERR,
                            DEM_EVENT_STATUS_PASSED);
      #endif
      /*[/cover] */
      /* Configured delay at each KDIV step change */
      DelayTickResolution = Mcal_DelayResetTickCalibration();
      CurrSTMTick = Mcal_DelayGetTick();
      BaseSTMTick = CurrSTMTick;
      KDivRampDelayTicks = ((KDivRampDelayTicks * MCU_STM_TIMER_COMPU_VAL) /
                            DelayTickResolution);

      /* [cover parentID={62B4E79A-A41F-4a67-A28A-314112325C43}]
       * Configure delay at each KDIV change
       * [/cover] */
      while ((uint32)((CurrSTMTick - BaseSTMTick) & MCU_STM_TICK_OVERFLOW) <
             KDivRampDelayTicks)
      {
        CurrSTMTick = Mcal_DelayGetTick();
      }
    }
  }

  /* [cover parentID={3F79B604-3FBF-4d82-AB55-A95FAD5E54C5}]
   * Is System PLL K2 divider value updated properly
   * [/cover] */
  if ((Std_ReturnType)E_OK == RetValue)
  {
    /* Switch peripheral PLLs to backup clock frequency */
    /* [cover parentID={0A263E10-E478-46f8-9639-51E08FC5E61B}]
     * Ram Peripheral PLL frequencies to Backup Clock frequency
     * [/cover] */
    Mcu_lPerPllToBackUpClockFreq(ApiId);
    /*[cover parentID={2176E0C4-FCB6-4b22-9126-B25C9C3EEA2D}][/cover]*/
    RetValue = Mcu_lCcuconLckChk(ApiId);
  }
  /*[cover parentID={8B9FAFDD-F1ED-41cd-8E37-0FBDD786455E}][/cover]
    [cover parentID={8C3CD177-F59F-4adc-AF1F-3C2A61777BB4}][/cover]*/
  return RetValue;
}


/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={F8F9759F-5956-406c-9EC7-F7971D97FC74}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType Mcu_lCcuconLckChk            **
**                   (void)                                                   **
**                                                                            **
** Description     : This function checks whether CCUCON0 is ready to         **
**                   be updated or not.                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : ApiId: The service ID of API from which the function     **
**                          is called.                                        **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK     : CCUCON0 is unlocked and can be updated        **
**                   E_NOT_OK : CCUCON0 is locked and can't be updated        **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Mcu_lCcuconLckChk(const uint8 ApiId)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_CCUCON0 Ccucon0Val;

  uint32 Ccucon0Lck;
  uint32 TimeoutCtr;
  Std_ReturnType RetValue = (Std_ReturnType)E_OK;

  /* Move clock tree distribution source as backup clock. */
  Ccucon0Val.U = SCU_CCUCON0.U;
  Ccucon0Val.B.CLKSEL = MCU_FSOURCE_CLKSEL_BACKUPCLK;
  Ccucon0Val.B.UP = 0x1U;
  Ccucon0Val.U = (uint32)Ccucon0Val.U & MCU_CCUCON0_RSVD_BIT_MASK;

  TimeoutCtr = MCU_CCUCON0_LCK_TIMEOUT;

  Ccucon0Lck = (uint32)SCU_CCUCON0.B.LCK;

  while ((TimeoutCtr > 0x0U) && (0x1U == Ccucon0Lck))
  {
    Ccucon0Lck = (uint32)SCU_CCUCON0.B.LCK;

    TimeoutCtr--;
  }

  /*[cover parentID={F6C60C6F-70E1-4615-A22B-14809D00ADB8}]*/
  if (0x1U == Ccucon0Lck)
  {
    #if (MCU_E_CCUCON_UPDATE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)

    Mcu_lReportDemError(MCU_E_CCUCON_UPDATE_ERR,
                          DEM_EVENT_STATUS_FAILED);
    #endif

    RetValue = (Std_ReturnType)E_NOT_OK;
  }
  else
  {
    #if (MCU_E_CCUCON_UPDATE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)

    Mcu_lReportDemError(MCU_E_CCUCON_UPDATE_ERR,
                          DEM_EVENT_STATUS_PASSED);
    #endif

    /*[cover parentID={FE3084DC-7C1D-4f2e-BF40-C78BB83EEAAA}]*/
    if (ApiId == MCU_API_INITCLOCK)
    {

      MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_CCUCON0.U,
          (uint32)(Ccucon0Val.U));
    }
    else
    {

      MCU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG(&SCU_CCUCON0.U,
          (uint32)(Ccucon0Val.U));
    }
  }
  return (RetValue);
}


/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={168E4F66-6353-420c-A4C8-B866C367BD00}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE void Mcu_lPerPllToBackUpClockFreq           **
**                                                             (uint8 ApiId)  **
** Description     : This function switches Peripheral PLL to backup clock    **
**                   frequency.                                               **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : ApiId - Service Id of the API in which the local function**
**                           is called                                        **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Mcu_lPerPllToBackUpClockFreq(const uint8 ApiId)
{
  uint32 PerpllKDiv, KDivRampDelayTicks;
  uint32 PllBackupFreqKDiv, PerpllPDiv, PerpllNDiv;
  uint32 DelayTickResolution, BaseSTMTick, CurrSTMTick;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_PERPLLCON1 Perpllcon1Val;

  /* Read delay tick resolution */
  DelayTickResolution = Mcal_DelayTickResolution();

  /*
    Ramp Peripheral PLL (PLL1) to backup frequency:
    1. Read the K2DIV value corresponding to backup frequency (target) and
       current K2DIV.
    2. Change (increase/decrease) K2DIV value until targeted K2DIV value is
       not achieved.
    3. Provide configured delay in between each K2DIV change
  */

  PerpllPDiv = (uint32)SCU_PERPLLCON0.B.PDIV;
  PerpllNDiv = (uint32)SCU_PERPLLCON0.B.NDIV;

  /* [cover parentID={59699B37-0CA8-4909-923F-765DA8C674E6}]
   * Calculate backup frequency K div value based on Oscillator or Backup clock
   * [/cover] */
  if (SCU_SYSPLLCON0.B.INSEL == MCU_PLL_INSEL_OSCCLK)
  {
    PllBackupFreqKDiv = (uint32)((PerpllNDiv + 0x1U) * MCU_MAIN_OSC_FREQ) /
                        (MCU_BACKUP_FREQ * (PerpllPDiv + 0x1U ));

  }
  else if (SCU_SYSPLLCON0.B.INSEL == MCU_PLL_INSEL_BACKUP)
  {
    PllBackupFreqKDiv = (uint32)(PerpllNDiv + 0x1U) / (PerpllPDiv + 0x1U );
  }
  else
  {
    PllBackupFreqKDiv = (uint32)((PerpllNDiv + 0x1U) * MCU_SYSCLK_FREQ) /
                        (MCU_BACKUP_FREQ * (PerpllPDiv + 0x1U ));
  }

  PllBackupFreqKDiv = PllBackupFreqKDiv - 0x01U;
  PerpllKDiv = (uint32)SCU_PERPLLCON1.B.K2DIV;

  /* [cover parentID={2D755FA8-70E9-4d8b-B1B9-B676616F2892}]
   * Ramp Peripheral PLL K2 divider to Backup Clock divider
   * [/cover] */
  while (PllBackupFreqKDiv != PerpllKDiv)
  {
    if (PllBackupFreqKDiv > PerpllKDiv)
    {
      KDivRampDelayTicks = Mcu_ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
                           .PeripheralPllK2StepUpChangeDelay;
      PerpllKDiv++;
    }
    else
    {
      KDivRampDelayTicks = Mcu_ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
                           .PeripheralPllK2StepDownChangeDelay;
      PerpllKDiv--;
    }

    /* Write new KDIV value */

    Perpllcon1Val.U = SCU_PERPLLCON1.U;
    /* MISRA2012_RULE_10_3_JUSTIFICATION: Assignment to narrower type as
       a register bit-field value (K2DIV : 3bit wide) is written and possible
       target KDIV values are between 0 - 7 therefore writes are limited within
       expected range. */
    Perpllcon1Val.B.K2DIV = PerpllKDiv;
    /* [cover parentID={593E7A7C-9255-4350-B08E-F73BEBF9F924}]
     * Is this local function called for local initialization
     * [/cover] */
    if (ApiId == MCU_API_INITCLOCK)
    {
      MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_PERPLLCON1.U,
          (uint32)(Perpllcon1Val.U));
    }
    else
    {
      MCU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG(&SCU_PERPLLCON1.U,
          (uint32)(Perpllcon1Val.U));
    }

    /* Configured delay at each KDIV step change */
    CurrSTMTick = Mcal_DelayGetTick();
    BaseSTMTick = CurrSTMTick;
    KDivRampDelayTicks = ((KDivRampDelayTicks * MCU_STM_TIMER_COMPU_VAL) /
                          DelayTickResolution);
    /* [cover parentID={AA238512-7BBC-4ca1-9E89-1561C62CF019}]
     * Provide user configured Peripheral PLL K2 divider delay
     * [/cover] */
    while ((uint32)((CurrSTMTick - BaseSTMTick) & MCU_STM_TICK_OVERFLOW) <
           KDivRampDelayTicks)
    {
      CurrSTMTick = Mcal_DelayGetTick();
    }
  }

  /*
    Ramp Peripheral PLL (PLL2) to backup frequency:
    1. Read the K3DIV value corresponding to backup frequency (target) and
       current K3DIV value.
    2. Change (increase/decrease) K3DIV value until targeted K3DIV value is
       not achieved.
    3. Provide configured delay in between each K3DIV change
  */

  /* [cover parentID={879B2A88-F187-4d30-9559-DF850F748C26}]
   * Calculate backup K3 divider value based on PLL input and
   * Divider Bypass status [/cover] */
  if (SCU_SYSPLLCON0.B.INSEL == MCU_PLL_INSEL_OSCCLK)
  {
    PllBackupFreqKDiv = (uint32)((PerpllNDiv + 0x1U) * MCU_MAIN_OSC_FREQ) /
                        (MCU_BACKUP_FREQ * (PerpllPDiv + 0x1U ));

  }
  else if (SCU_SYSPLLCON0.B.INSEL == MCU_PLL_INSEL_BACKUP)
  {
    PllBackupFreqKDiv = (uint32)(PerpllNDiv + 0x1U) / (PerpllPDiv + 0x1U );
  }
  else
  {
    PllBackupFreqKDiv = (uint32)((PerpllNDiv + 0x1U) * MCU_SYSCLK_FREQ) /
                        (MCU_BACKUP_FREQ * (PerpllPDiv + 0x1U ));
  }

  /* [cover parentID={879B2A88-F187-4d30-9559-DF850F748C26}]
   * Calculate backup K3 divider value based on PLL input and
   * Divider Bypass status [/cover] */
  if (SCU_PERPLLCON0.B.DIVBY == 0x0U)
  {
    PllBackupFreqKDiv = (uint32)((PllBackupFreqKDiv * PERPLL_DIVBY_ZERO_NUM) /
                                 PERPLL_DIVBY_ZERO_DEN);
  }
  else
  {
    PllBackupFreqKDiv = (uint32)(PllBackupFreqKDiv / PERPLL_DIVBY_ONE_DEN);
  }
  PllBackupFreqKDiv = PllBackupFreqKDiv - 0x1U;
  PerpllKDiv = (uint32)SCU_PERPLLCON1.B.K3DIV;

  /* [cover parentID={EC661D55-0BBF-4617-BDCE-53612E807A87}]
   * Ramp Peripheral PLL K3 Divider to Backup clock divider value
   * [/cover] */
  while (PllBackupFreqKDiv != PerpllKDiv)
  {
    if (PllBackupFreqKDiv > PerpllKDiv)
    {
      KDivRampDelayTicks = Mcu_ConfigPtr->McuClockSettingPtr
                           [Mcu_ClockSetting]
                           .PeripheralPllK3StepUpChangeDelay;
      PerpllKDiv++;
    }
    else
    {
      KDivRampDelayTicks = Mcu_ConfigPtr->McuClockSettingPtr
                           [Mcu_ClockSetting]
                           .PeripheralPllK3StepDownChangeDelay;
      PerpllKDiv--;
    }

    /* Write new KDIV value */

    Perpllcon1Val.U = SCU_PERPLLCON1.U;
    /* MISRA2012_RULE_10_3_JUSTIFICATION: Assignment to narrower type as
       a register bit-field value (K3DIV : 3bit wide) is written and possible
       target KDIV values are between 0 - 7 therefore writes are limited within
       expected range. */
    Perpllcon1Val.B.K3DIV = PerpllKDiv;

    /* [cover parentID={2DC836CF-0A32-4d3b-BC34-2ABAFDB98E94}]
     * Is this local function called for local initialization
     * [/cover] */
    if (ApiId == MCU_API_INITCLOCK)
    {
      MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_PERPLLCON1.U,
          (uint32)(Perpllcon1Val.U));
    }
    else
    {
      MCU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG(&SCU_PERPLLCON1.U,
          (uint32)(Perpllcon1Val.U));
    }

    /* Configured delay at each KDIV step change */
    CurrSTMTick = Mcal_DelayGetTick();
    BaseSTMTick = CurrSTMTick;
    KDivRampDelayTicks = ((KDivRampDelayTicks * MCU_STM_TIMER_COMPU_VAL) /
                          DelayTickResolution);
    /* [cover parentID={221958D8-3717-4800-B9FB-4A659BA700AD}]
     * Provide user configured Peripheral PLL K3 divider delay
     * [/cover] */
    while ((uint32)((CurrSTMTick - BaseSTMTick) & MCU_STM_TICK_OVERFLOW) <
           KDivRampDelayTicks)
    {
      CurrSTMTick = Mcal_DelayGetTick();
    }
  }
}

#if (MCU_DISTRIBUTE_PLL_CLOCK_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={E90D1053-78D1-4f70-851D-83B1BA5533DD}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType Mcu_lSwitchToDesiredFreq     **
**                                                                    ( void )**
**                                                                            **
** Description     : This function safely moves the clock tree to desired     **
**                   clock frequency.                                         **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK : Pll ramp to desired frequency successful          **
**                   E_NOT_OK : Pll ramp to desired frequency failed          **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Mcu_lSwitchToDesiredFreq(void)
{
  uint32 CurrentKDivVal, TargetKDivVal, KDivRampDelayTicks;
  uint32 DelayTickResolution, BaseSTMTick, CurrSTMTick, SysPllStat;
  volatile uint32 TimeoutCtr;
  Std_ReturnType RetValue = (Std_ReturnType)E_OK;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_SYSPLLCON1 Syspllcon1Val;

  /*
    Ramp system PLL (PLL0) to desired frequency:
    1. Read the current K2DIV value.
    2. Change (increase/decrease) K2DIV value until targeted K2DIV value is
       not achieved.
    3. Wait (with timeout) until new K2DIV value is effective.
    4. Provide configured delay in between each K2DIV change
  */

  CurrentKDivVal = (uint32)SCU_SYSPLLCON1.B.K2DIV;
  TargetKDivVal = Mcu_ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
                  .SystemPllCfg.SysPllK2Div;
  /* [cover parentID={042E6DAA-75B4-48e5-B9F2-871AB3A33D8F}]
   * Ramp System PLL to Desired frequency
   * [/cover] */
  while ((TargetKDivVal != CurrentKDivVal) &&
         ((Std_ReturnType)E_OK == RetValue))
  {
    /* [cover parentID={1DD24CD7-A3B2-451a-BAC4-DB4E3ACBCA8F}]
     * Compare Current and Target K2 divider value and update Current
     * divider value in steps of 1 [/cover] */
    if (TargetKDivVal > CurrentKDivVal)
    {
      CurrentKDivVal++;
      KDivRampDelayTicks = Mcu_ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
                           .SysPllK2DivStepUpChangeDelay;
    }
    else
    {
      CurrentKDivVal--;
      KDivRampDelayTicks = Mcu_ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
                           .SysPllK2DivStepDownChangeDelay;
    }

    /* Write new KDIV value */
    /*Mcal_ResetSafetyEndInitProtection();*/
    Syspllcon1Val.U = SCU_SYSPLLCON1.U;
    /* MISRA2012_RULE_10_3_JUSTIFICATION: Assignment to narrower type as
       a register bit-field value (K2DIV : 3bit wide) is written and possible
       target KDIV values are between 0 - 7 therefore writes are limited within
       expected range. */
    Syspllcon1Val.B.K2DIV = CurrentKDivVal;

    MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_SYSPLLCON1.U,
        (uint32)(Syspllcon1Val.U));

    /* Wait until updated KDIV value is effective */
    TimeoutCtr = MCU_PLL_KDIVRDY_TIMEOUT;
    SysPllStat = (uint32)SCU_SYSPLLSTAT.B.K2RDY;

    /* [cover parentID={05261A3A-D735-494c-9450-1A14307CDD2A}]
     * Provide delay for new K2 divider value to get reflected
     * [/cover] */
    while ((TimeoutCtr > 0x0U) && (0x0U == SysPllStat))
    {

      SysPllStat = (uint32)SCU_SYSPLLSTAT.B.K2RDY;
      TimeoutCtr--;
    }
    /* [cover parentID={9A6520CF-CC8C-4bfc-8B5D-953A80C602F9}]
     * Did Timeout occur and is new K2 divider value still not reflected
     * [/cover] */
    if (0x0U == TimeoutCtr)
    {
      /* [cover parentID={C98AD486-A4BA-40eb-AF64-1938F96DC459}]
       * If Production error Reporting is ON */
      #if (MCU_E_SYSTEM_PLL_TIMEOUT_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
      /*Report Production error for system PLL error*/
      /* [cover parentID=]
       * Report Production error: Event Failed
       * [/cover] */
      Mcu_lReportDemError(MCU_E_SYSTEM_PLL_TIMEOUT_ERR,
                            DEM_EVENT_STATUS_FAILED);
      #endif

      RetValue = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
      #if (MCU_E_SYSTEM_PLL_TIMEOUT_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
      /*Report Production error for system PLL passed*/
      /* [cover parentID=]
       * Report Production error: Event Passed
       * [/cover] */
      Mcu_lReportDemError(MCU_E_SYSTEM_PLL_TIMEOUT_ERR,
                            DEM_EVENT_STATUS_PASSED);
      #endif
      /*[/cover] */

      /* Configured delay at each KDIV step change */
      DelayTickResolution = Mcal_DelayResetTickCalibration();
      CurrSTMTick = Mcal_DelayGetTick();
      BaseSTMTick = CurrSTMTick;
      KDivRampDelayTicks = ((KDivRampDelayTicks * MCU_STM_TIMER_COMPU_VAL) /
                            DelayTickResolution);

      /* [cover parentID={872938B1-E4A8-4856-80ED-B919856C168A}]
       * Provide user configured System PLL K2 divider delay
       * [/cover] */
      while ((uint32)((CurrSTMTick - BaseSTMTick) & MCU_STM_TICK_OVERFLOW) <
             KDivRampDelayTicks)
      {
        CurrSTMTick = Mcal_DelayGetTick();
      }
    }
  }

  /* [cover parentID={58AA2804-B20E-477d-A48F-6E3A4C7A2BF9}]
   * Is System PLL K2 divider value updated properly
   * [/cover] */
  if ((Std_ReturnType)E_OK == RetValue)
  {
    /* Switch Peripheral PLL to desired frequency as per configuration */
    /* [cover parentID={7B802F1C-10C4-4646-BD29-2C2EAD7F98F5}]
     * Switch Peripheral PLL to desired frequency
     * [/cover] */
    Mcu_lPerPllToDesiredFreq();
  }
  /*[cover parentID={5C8EA8BE-3B9E-4791-826E-5EB7EADCD745}][/cover]
    [cover parentID={07B241A5-2298-4e79-BFB8-D876F1977012} ][/cover]*/
  return RetValue;
}
/* End of #if (MCU_DISTRIBUTE_PLL_CLOCK_API == STD_ON) */

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={786E19EB-B84B-4e7c-BBDB-624A89C7CDAE}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE void Mcu_lPerPllToDesiredFreq(void)         **
**                                                                            **
** Description     : This function switches Peripheral PLL to desired         **
**                   frequency as per configuration.                          **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Mcu_lPerPllToDesiredFreq(void)
{
  uint32 CurrentKDivVal, TargetKDivVal, KDivRampDelayTicks;
  uint32 DelayTickResolution, BaseSTMTick, CurrSTMTick;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_PERPLLCON1 Perpllcon1Val;

  /* Read and store delay tick resolution */

  DelayTickResolution = Mcal_DelayTickResolution();
  /*
    Ramp peripheral PLL (PLL1) to desired frequency:
    1. Read the current K2DIV value.
    2. Change (increase/decrease) K2DIV value until targeted K2DIV value is
       not achieved.
    3. Provide configured delay in between each K2DIV change
  */

  TargetKDivVal = Mcu_ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
                  .PeripheralPllCfg.PerPllK2Div;

  CurrentKDivVal = (uint32)SCU_PERPLLCON1.B.K2DIV;

  /* [cover parentID={9E1A2AD9-53BD-4182-A9CC-24BADA906149}]
   * Ramp PLL K2 Divider to Desired K2 divider value
   * [/cover] */
  while (TargetKDivVal != CurrentKDivVal)
  {
    /* [cover parentID={305C58F6-4946-46c9-8384-FE4F39A491C5}]
     * Compare Current and Target K2 divider value and update
     * Current divider value in steps of 1
     * [/cover] */
    if (TargetKDivVal > CurrentKDivVal)
    {
      KDivRampDelayTicks = Mcu_ConfigPtr->McuClockSettingPtr
                           [Mcu_ClockSetting]
                           .PeripheralPllK2StepUpChangeDelay;
      CurrentKDivVal++;
    }
    else
    {
      KDivRampDelayTicks = Mcu_ConfigPtr->McuClockSettingPtr
                           [Mcu_ClockSetting]
                           .PeripheralPllK2StepDownChangeDelay;
      CurrentKDivVal--;
    }

    /* Write new KDIV value */
    /*Mcal_ResetSafetyEndInitProtection();*/

    Perpllcon1Val.U = SCU_PERPLLCON1.U;
    /* MISRA2012_RULE_10_3_JUSTIFICATION: Assignment to narrower type as
       a register bit-field value (K2DIV : 3bit wide) is written and possible
       target KDIV values are between 0 - 7 therefore writes are limited within
       expected range. */
    Perpllcon1Val.B.K2DIV = CurrentKDivVal;

    MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_PERPLLCON1.U,
        (uint32)(Perpllcon1Val.U));

    /* Configured delay at each KDIV step change */
    CurrSTMTick = Mcal_DelayGetTick();
    BaseSTMTick = CurrSTMTick;
    KDivRampDelayTicks = ((KDivRampDelayTicks * MCU_STM_TIMER_COMPU_VAL) /
                          DelayTickResolution);
    /* [cover parentID={14AFD46E-7B40-4f31-981C-B3AC47E6BBD2}]
     * Provide user configured Peripheral PLL K2 divider delay
     * [/cover] */
    while ((uint32)((CurrSTMTick - BaseSTMTick) &
                    MCU_STM_TICK_OVERFLOW) < KDivRampDelayTicks)
    {
      CurrSTMTick = Mcal_DelayGetTick();
    }
  }

  /*
    Ramp peripheral PLL (PLL2) to desired frequency:
    1. Read the current K3DIV value.
    2. Change (increase/decrease) K3DIV value until targeted K3DIV value is
       not achieved.
    3. Provide configured delay in between each K3DIV change
  */

  TargetKDivVal = Mcu_ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
                  .PeripheralPllCfg.PerPllK3Div;
  CurrentKDivVal = (uint32)SCU_PERPLLCON1.B.K3DIV;

  /* [cover parentID={F59AE38C-5370-4be3-B46D-4FA6CE71DDCF}]
   * Ramp PLL K3 Divider to desired Divider value
   * [/cover] */
  while (TargetKDivVal != CurrentKDivVal)
  {
    /* [cover parentID={3A8D9BD2-63FD-47f3-8662-BA142A29CC66}]
     * Compare Current and Target K3 divider value and update Current divider
     * value in steps of 1 [/cover] */
    if (TargetKDivVal > CurrentKDivVal)
    {
      KDivRampDelayTicks = Mcu_ConfigPtr->McuClockSettingPtr
                           [Mcu_ClockSetting].PeripheralPllK3StepUpChangeDelay;
      CurrentKDivVal++;
    }
    else
    {
      KDivRampDelayTicks = Mcu_ConfigPtr->McuClockSettingPtr
                           [Mcu_ClockSetting].PeripheralPllK3StepDownChangeDelay;
      CurrentKDivVal--;
    }

    /* Write new KDIV value */

    Perpllcon1Val.U = SCU_PERPLLCON1.U;
    /* MISRA2012_RULE_10_3_JUSTIFICATION: Assignment to narrower type as
       a register bit-field value (K3DIV : 3bit wide) is written and possible
       target KDIV values are between 0 - 7 therefore writes are limited within
       expected range. */
    Perpllcon1Val.B.K3DIV = CurrentKDivVal;

    MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_PERPLLCON1.U,
        (uint32)(Perpllcon1Val.U));

    /* Configured delay at each KDIV step change */
    CurrSTMTick = Mcal_DelayGetTick();
    BaseSTMTick = CurrSTMTick;
    KDivRampDelayTicks = ((KDivRampDelayTicks * MCU_STM_TIMER_COMPU_VAL) /
                          DelayTickResolution);
    /* [cover parentID={A7CEC24E-28B3-4a93-80F2-8B5F6B43E10C}]
     * Provide user configured Peripheral PLL K3 divider delay
     * [/cover] */
    while ((uint32)((CurrSTMTick - BaseSTMTick) & MCU_STM_TICK_OVERFLOW) <
           KDivRampDelayTicks)
    {
      CurrSTMTick = Mcal_DelayGetTick();
    }
  }
}

#endif

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={41D65477-3558-4ead-996A-42A550D3222A}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Mcu_ResetType Mcu_lGetRstReason             **
**                                (const Mcu_RawResetType RstReasonRaw)       **
**                                                                            **
** Description     : This function determines type of reset out of raw reset  **
**                   register content.                                        **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Reset reason of type Mcu_ResetType                       **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Mcu_ResetType Mcu_lGetRstReason
(const Mcu_RawResetType RstReasonRaw)
{
  Mcu_ResetType ResetReason = MCU_RESET_UNDEFINED;

  /*
    1. Match the raw reset reason against value w.r.t. types of reset.
       Accordingly, return the reset reason.
  */
  switch (RstReasonRaw)
  {
    /* [cover parentID={BB7C9C1B-306D-4820-B916-0E14017E5004}]
     * Is Reset Reason ESR0
     * [/cover] */
    case MCU_RAW_ESR0_RESET:
    {
      ResetReason = MCU_ESR0_RESET;
      break;
    }
    /* [cover parentID={097DA4CC-0B63-4d65-9AA5-E53D47BF8A31}]
     * Is Reset Reason ESR1
     * [/cover] */
    case MCU_RAW_ESR1_RESET:
    {
      ResetReason = MCU_ESR1_RESET;
      break;
    }
    /* [cover parentID={0DE2197A-E921-4689-A083-0BE3A5536830}]
     * Is Reset Reason SMU Reset
     * [/cover] */
    case MCU_RAW_SMU_RESET:
    {
      ResetReason = MCU_SMU_RESET;
      break;
    }
    /* [cover parentID={6D508E06-7C84-41c1-B213-EF8540604BFF}]
     * Is Reset reason Software reset
     * [/cover] */
    case MCU_RAW_SW_RESET:
    {
      ResetReason = MCU_SW_RESET;
      break;
    }
    /* [cover parentID={5868CC92-F3F2-413d-B21F-CB99872DDD3B}]
     * Is Reset reason STMx (x:0-5) reset
     */
    case MCU_RAW_STM0_RESET:
    {
      ResetReason = MCU_STM0_RESET;
      break;
    }
    #if (MCAL_NO_OF_CORES > 1U)
    case MCU_RAW_STM1_RESET:
    {
      ResetReason = MCU_STM1_RESET;
      break;
    }
    #endif

    #if (MCAL_NO_OF_CORES > 2U)
    case MCU_RAW_STM2_RESET:
    {
      ResetReason = MCU_STM2_RESET;
      break;
    }
    #endif

    #if (MCAL_NO_OF_CORES > 3U)
    case MCU_RAW_STM3_RESET:
    {
      ResetReason = MCU_STM3_RESET;
      break;
    }
    #endif

    #if (MCAL_NO_OF_CORES > 4U)
    case MCU_RAW_STM4_RESET:
    {
      ResetReason = MCU_STM4_RESET;
      break;
    }
    #endif

    #if (MCAL_NO_OF_CORES > 5U)
    case MCU_RAW_STM5_RESET:
    {
      ResetReason = MCU_STM5_RESET;
      break;
    }
    #endif
    /* [/cover] */
    /* [cover parentID={545E6B66-F02D-48a2-9CA7-703F013CCAEA}]
     * Is Reset reason Power On reset
     * [/cover] */
    case MCU_RAW_POWER_ON_RESET_1:
    case MCU_RAW_POWER_ON_RESET_2:
    {
      ResetReason = MCU_POWER_ON_RESET;
      break;
    }
    default:
    {
      /* [cover parentID={47CAA7E0-F234-4d64-AC8F-46FD6C50649A}]
       * Get further Reset reason
       * [/cover] */
      ResetReason = Mcu_lGetRstReason2(RstReasonRaw);
      break;
    }
  }

  return ResetReason;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={C56F9D4E-31F1-4db7-B4E7-980476A2BE62}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Mcu_ResetType Mcu_lGetRstReason2            **
**                                (const Mcu_RawResetType RstReasonRaw)       **
**                                                                            **
** Description     : This function determines type of reset out of raw reset  **
**                   register content.                                        **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Reset reason of type Mcu_ResetType                       **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Mcu_ResetType Mcu_lGetRstReason2(const Mcu_RawResetType
    RstReasonRaw)
{
  Mcu_ResetType ResetReason = MCU_RESET_UNDEFINED;

  /*
    1. Match the raw reset reason against value w.r.t. types of reset.
       Accordingly, return the reset reason.
  */
  switch (RstReasonRaw)
  {
    /* [cover parentID={5503F550-94B6-4fd1-B8D5-A035B585AB41}]
     * Is Reset reason LBIST reset
     * [/cover] */
    case MCU_RAW_LBIST_RESET:
    {
      ResetReason = MCU_LBIST_RESET;
      break;
    }
    /* [cover parentID={8076AD0C-E64D-4008-B223-65D9AFC7A38A}]
     * Is Reset reason CB0 Reset
     * [/cover] */
    case MCU_RAW_CB0_RESET:
    {
      ResetReason = MCU_CB0_RESET;
      break;
    }
    /* [cover parentID={DCD3F6A7-7736-4ef4-8B9A-C887D78B129F}]
    * Is Reset reason CB1 reset
    * [/cover] */
    case MCU_RAW_CB1_RESET:
    {
      ResetReason = MCU_CB1_RESET;
      break;
    }
    /* [cover parentID={C268402A-7EA2-4d93-836F-6254FE39196C}]
     * Is Reset reason CB3 reset
     * [/cover] */
    case MCU_RAW_CB3_RESET:
    {
      ResetReason = MCU_CB3_RESET;
      break;
    }
    /* [cover parentID={8850ED7A-0808-46fc-8E52-89A8560C4F2C}]
     * Is Reset reason EVRC reset
     * [/cover] */
    case MCU_RAW_EVRC_RESET:
    {
      ResetReason = MCU_EVRC_RESET;
      break;
    }
    /* [cover parentID={0D654F2A-F90C-4c32-927C-CB0C04BAB28C}]
     * Is Reset reason EVR33 reset
     * [/cover] */
    case MCU_RAW_EVR33_RESET:
    {
      ResetReason = MCU_EVR33_RESET;
      break;
    }
    /* [cover parentID={126312B1-0C61-4396-B286-2F6D381E1056}]
     * Is Reset reason supply watchdog reset
     * [/cover] */
    case MCU_RAW_SUPPLY_WDOG_RESET:
    {
      ResetReason = MCU_SUPPLY_WDOG_RESET;
      break;
    }
    /* [cover parentID={65276D76-8049-4c21-B172-7CA2235DF880}]
     * Is Reset reason STBYR reset
     * [/cover] */
    case MCU_RAW_STBYR_RESET:
    {
      ResetReason = MCU_STBYR_RESET;
      break;
    }
    default:
    {
      /* if none of the above match, check whether the reset reason is
       *  MCU_RESET_UNDEFINED or  MCU_RESET_MULTIPLE */
      /* [cover parentID={A46933A2-6C9C-4d93-9478-C9768A15BCE3}]
       * Is Reset Reason Power On reset 1 OR Power On reset 2
       * [/cover] */
      if (((RstReasonRaw & MCU_RAW_POWER_ON_RESET_1) ==
           (MCU_RAW_POWER_ON_RESET_1)) || ((RstReasonRaw &
            MCU_RAW_POWER_ON_RESET_2) == (MCU_RAW_POWER_ON_RESET_2)))
      {
        ResetReason = MCU_RESET_MULTIPLE;
      }
      else
      {
        ResetReason = MCU_RESET_UNDEFINED;
      }
      break;
    }
  }

  return ResetReason;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={13E996E6-2681-4db1-9570-A2B835232E7B}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE void Mcu_lSetIdleMode(const uint8 CoreId)   **
**                                                                            **
** Description     : This function sets CPU mode to IDLE.                     **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : CoreId: Core number to initiate idle mode.               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Mcu_lSetIdleMode(const uint8 CoreId)
{
  uint8 CoreSelect, IdleModeSel;

  /*
    1. Calculate current coreID value and evaluate if current core id is
       authorized to trigger IDLE mode.
    2. Set CPU to IDLE mode accordingly.
  */

  CoreSelect = CoreId + (uint8)0x1U;
  IdleModeSel = (uint8)SCU_PMSWCR1.B.CPUIDLSEL;

  /* [cover parentID={C2227782-DEDB-43fb-B9BE-B2FE91CC9182}]
   * Is Current Core authorized to trigger Idle mode
   * [/cover] */
  if ((CoreSelect == IdleModeSel) ||
      (MCU_INDIVIDUAL_CORE_IDLE_MODE == IdleModeSel))
  {
    /* [cover parentID={6CBD9AE7-2F5D-40ec-AD1B-2226BEC4D4DD}]
     * Set CPU to Idle mode
     * [/cover] */
    Mcu_lSetCpuMode((uint32)CoreId, MCU_IDLE_MODE_REQ_VAL);
  }
  #if ((MCU_DEV_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
  else
  {
    Mcu_lReportError(MCU_SID_SETMODE, MCU_E_UNAUTHORIZED_REQUESTER);
  }
  #endif
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={36ABEDDC-8FFB-4088-B526-6D92CAB0DC32}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE void Mcu_lSetSleepMode(const uint8 CoreId)  **
**                                                                            **
** Description     : This function sets CPU mode to SLEEP.                    **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : CoreId: Core number to initiate sleep mode.              **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Mcu_lSetSleepMode(const uint8 CoreId)
{
  uint8 CoreSelect, SleepModeSel;

  /*
    1. Calculate current coreID value and evaluate if current core id is
       authorized to trigger SLEEP mode.
    2. Set CPU to SLEEP mode accordingly.
  */

  CoreSelect = CoreId + (uint8)0x1U;
  SleepModeSel = (uint8)SCU_PMSWCR1.B.CPUSEL;

  /* [cover parentID={F52BD8F9-8AE6-4aca-8898-EA06BDF8B154}]
   * Is Current Core Set to trigger Sleep mode
   * [/cover] */
  if ((CoreSelect == SleepModeSel) ||
      (MCU_UNANIMOUS_SEL_SYSTEM_MODE == SleepModeSel))
  {
    /* [cover parentID={38D0DB49-8287-4a1e-9CB9-6BFC5E640936}]
     * Set CPU into Sleep mode
     * [/cover] */
    Mcu_lSetCpuMode((uint32)CoreId, MCU_SLEEP_MODE_REQ_VAL);
  }
  #if ((MCU_DEV_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
  else
  {
    Mcu_lReportError(MCU_SID_SETMODE, MCU_E_UNAUTHORIZED_REQUESTER);
  }
  #endif
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={F6CE7044-1784-42d1-8565-D8D2E41F36EF}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE void Mcu_lSetStandbyMode(const uint8 CoreId)**
**                                                                            **
** Description     : This function sets system to STANDBY mode.               **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : CoreId: Core number to initiate Standby mode.            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
/* CYCLOMATIC_Mcu_lSetStandbyMode_JUSTIFICATION: This Function has cyclomatic
   Complexity >15. This is due to higher number of Production error and DET
   checks inside the function. This local function is the functional block for
   switching system to StandyBy mode.*/
LOCAL_INLINE void Mcu_lSetStandbyMode(const uint8 CoreId)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_SYSPLLCON0 Syspllcon0Val;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_PERPLLCON0 Perpllcon0Val;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_PMSWCR1 Pmswcr1Val;
  volatile uint32 TimeoutCtr;
  uint32 SysPllStat, PerPllStat, Pmswcr3Stat;
  uint32 ResetDelayTicks, BaseSTMTick, CurrSTMTick, DelayTickResolution;
  #if (MCU_NO_OF_STDBY_RAM_BLK != 0U)
  uint32 DummyStdByRamRead[MCU_NO_OF_STDBY_RAM_BLK];
  uint8  LoopCtr;
  #endif
  uint8  CoreSelect, StandbyModeSel;
  volatile Std_ReturnType RetValue = E_OK;

  /*
    1. Check if low power mode is configured and current core is configured
       to trigger standby mode.
    2. Perform RAM redundancy area preparation and store the data.
    3. Switch clock tree source to backup clock, if not set already.
    4. Move both PLLs to power saving mode.
    5. Trigger request to move system into standby mode.
  */

  CoreSelect = CoreId + (uint8)0x1U;
  StandbyModeSel = (uint8)SCU_PMSWCR1.B.CPUSEL;

  /* [cover parentID={F6C5B26A-9C26-4abf-9370-0863F1A596FA}]
   * Is the current core authorized to Trigger Standby mode
   * or all cores are allowed to trigger
   * [/cover] */
  if (((CoreSelect == StandbyModeSel) ||
       (MCU_UNANIMOUS_SEL_SYSTEM_MODE == StandbyModeSel)))
  {
    /* [cover parentID={03997D73-246D-42db-894F-747755CB1EDF}]
     * Is Single core authorized to trigger Standby Or in case
     * all cores are authorized is the selected core, Master core
     * [/cover] */
    if (!((MCU_UNANIMOUS_SEL_SYSTEM_MODE == StandbyModeSel) &&
          (MCAL_MASTER_COREID != CoreId)))
    {
      /*switch to backup clock if not set already*/
      /* [cover parentID={017E26D9-4EEF-4991-AA98-B27810851C17}]
      * Is Backup clock selected as Clock tree source
      * [/cover] */
      if (MCU_FSOURCE_CLKSEL_BACKUPCLK != SCU_CCUCON0.B.CLKSEL)
      {
        RetValue =
          Mcu_lSwitchToBackUpClockFreq(MCU_API_SETMODE, Mcu_ClockSetting);
      }

      /* [cover parentID={AA566181-D2A0-495a-BEBC-FC6E4785AE94}]
       * Is Switching to Backup clock successful
       * [/cover] */
      if (E_OK == RetValue)
      {
        /*
          1. Move Both PLLs to power-saving mode.
          2. Set IRADIS bit to avoid any possible unblock of standby request due
             to pending idle request sequence.
          3. Set wakeup timer settings as per configuration.
        */
        Syspllcon0Val.U = (uint32)SCU_SYSPLLCON0.U &
                          (~MCU_SYSPLLCON0_RSRVD_RW_MASK);
        Syspllcon0Val.B.PLLPWD = 0x0U;
        Perpllcon0Val.U = (uint32)SCU_PERPLLCON0.U &
                          (~MCU_PERPLLCON0_RSRVD_RW_MASK);
        Perpllcon0Val.B.PLLPWD = 0x0U;


        MCU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG(&SCU_SYSPLLCON0.U,
            (uint32)(Syspllcon0Val.U));

        MCU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG(&SCU_PERPLLCON0.U,
            (uint32)(Perpllcon0Val.U));

        TimeoutCtr = MCU_PLL_PWDSTAT_TIMEOUT;
        SysPllStat = (uint32)SCU_SYSPLLSTAT.B.PWDSTAT;
        PerPllStat = (uint32)SCU_PERPLLSTAT.B.PWDSTAT;

        /* [cover parentID={C247DB3D-AFB6-4d20-BAAD-30227F24062A}]
         * Provide delay for wakeup timer register to be available for updating
         * [/cover] */
        while ((TimeoutCtr > 0x0U) && ((0x0U == SysPllStat) ||
                                       (0x0U == PerPllStat)))
        {
          SysPllStat = (uint32)SCU_SYSPLLSTAT.B.PWDSTAT;
          PerPllStat = (uint32)SCU_PERPLLSTAT.B.PWDSTAT;
          TimeoutCtr--;
        }

        /* [cover parentID={5C0B3366-ADB6-42ee-ABF9-499609E3E6B7}]
         * Is System PLL not locked
         * [/cover] */
        if (0x0U == SCU_SYSPLLSTAT.B.PWDSTAT)
        {
          #if (MCU_E_SYSTEM_PLL_TIMEOUT_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
          /* Report Production error for system PLL error */
          /* [cover parentID=]
             Report Production error: Event Failed
          [/cover] */
          /* [cover parentID={A94E9C59-3D01-45d6-8722-A6F06AF3AD12}]
             Report Production error: Event Failed
          [/cover] */
          Mcu_lReportDemError(MCU_E_SYSTEM_PLL_TIMEOUT_ERR,
                                DEM_EVENT_STATUS_FAILED);
          #endif

          RetValue = E_NOT_OK;
        }
        #if (MCU_E_SYSTEM_PLL_TIMEOUT_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
        else
        {
          /* Report Production error for system PLL passed */
          /* [cover parentID=]
           * Report Production error: Event Passed
           * [/cover] */
          Mcu_lReportDemError(MCU_E_SYSTEM_PLL_TIMEOUT_ERR,
                                DEM_EVENT_STATUS_PASSED);
        }
        #endif

        /* [cover parentID={AA7CE0F9-2FCD-4a66-9E5E-7339733E21C7}]
         * Is Peripheral PLL not locked
         * [/cover] */
        if (0x0U == SCU_PERPLLSTAT.B.PWDSTAT)
        {
          /* [cover parentID={666C7474-1D48-46a1-8FF5-67EDB2E577F2}]
           * If Production error Reporting is ON*/
          #if (MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR_DEM_REPORT == \
          MCU_ENABLE_DEM_REPORT)
          /* Report Production error for peripheral PLL error */
          /* [cover parentID=]
           * Report Production error: Event Failed
          [/cover] */
          /* [cover parentID={35CA0459-D655-442d-8304-3455D92BFE74}]
           *  Report Production error: Event Failed
           [/cover] */
          Mcu_lReportDemError(MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR,
                                DEM_EVENT_STATUS_FAILED);
          #endif
          RetValue = E_NOT_OK;
        }
        #if (MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR_DEM_REPORT == \
        MCU_ENABLE_DEM_REPORT)
        else
        {
          /* Report Production error for peripheral PLL passed */
          Mcu_lReportDemError(MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR,
                                DEM_EVENT_STATUS_PASSED);
        }
        #endif
        /* [/cover] */
        /* [cover parentID={ABDEEA24-483A-492f-8870-6E5B7138F1BC}]
         * Are PLLs properly moved to Power saving mode
         * [/cover] */
        if (E_OK == RetValue)
        {
          Pmswcr1Val.U = SCU_PMSWCR1.U;
          Pmswcr1Val.B.IRADIS = 0x1U;

          MCU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG(&SCU_PMSWCR1.U,
              (uint32)Pmswcr1Val.U);

          CurrSTMTick = Mcal_DelayGetTick();
          BaseSTMTick = CurrSTMTick;
          /*[cover parentID={B284BD60-6D62-4e4b-B802-77C97E07BDC0}][/cover]*/
          DelayTickResolution = Mcal_DelayResetTickCalibration();
          ResetDelayTicks = (MCU_PLL_PMSWCR3_DELAY / DelayTickResolution);
          Pmswcr3Stat = PMS_PMSWCR3.B.BUSY;

          /* [cover parentID={21784FC3-C77F-4533-AF99-22FD57FBED79}]
          * Provide Delay for Standby register to get updated
          * [/cover] */
          while (
            ((uint32)((CurrSTMTick - BaseSTMTick) & MCU_STM_TICK_OVERFLOW) <
             ResetDelayTicks) &&
            (0x1U == Pmswcr3Stat))
          {
            CurrSTMTick = Mcal_DelayGetTick();
            Pmswcr3Stat = PMS_PMSWCR3.B.BUSY;
          }

          /* [cover parentID={07B5BFCB-3616-4fc1-A321-A9F0B4703CDE}]
          * Is wakeup timer configuration register Busy
          * [/cover] */
          if (MCU_PMSWCR_BUSY == PMS_PMSWCR3.B.BUSY)
          {
            /* [cover parentID={50F03EBD-09E1-400f-B94E-11F6040D52C4}]
            * If Production error Reporting is ON*/
            #if (MCU_E_PMSWCR_UPDATE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
            /* Report Production error for  PMSWCR3 update error */
            /* [cover parentID={687D25F7-BACB-4024-9F76-52B9FF44C141} ]
            [/cover]*/
            /* [cover parentID={7C9750F3-AD52-4a98-A801-9A4A1D27C645}]
            * Report Production error: Event Failed
            * [/cover] */
            Mcu_lReportDemError(MCU_E_PMSWCR_UPDATE_ERR,
                                  DEM_EVENT_STATUS_FAILED);
            #endif
            RetValue = E_NOT_OK;
          }
          else
          {
            /*
            * PMSWCR3 register is available to write, update and ramp to
            * desired frequency.
            */
            #if (MCU_E_PMSWCR_UPDATE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
            /* Report Production error for system PLL error */
            /* [cover parentID={38D8FA1F-823F-46e7-AB5E-56ADD5A90FEC}]
            * Report Production error: Event Passed
            * [/cover] */
            Mcu_lReportDemError(MCU_E_PMSWCR_UPDATE_ERR,
                                  DEM_EVENT_STATUS_PASSED);
            #endif
            /* [/cover] */

            MCU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG(&PMS_PMSWCR3.U,
                Mcu_ConfigPtr->McuLowPowerModeCfgPtr->Pmswcr3);
          }
        }
      }
    }

    /* [cover parentID={BAFDFCBD-C216-4496-AC50-21934C35BDEF}]
     * Is Standby wakeup timer properly configured
     * [/cover] */
    if (E_OK == RetValue)
    {
      /* [cover parentID={2857DC94-F700-4136-A308-F7C1D1029B4A}]
       * If number of Standby Ram configured is non zero */
      #if (MCU_NO_OF_STDBY_RAM_BLK != 0U)
      /* [cover parentID={83FD0CF3-B336-4b69-8A8C-79508D9EDACD}]
       * Loop through configured Standby RAM
       * [/cover] */
      for (LoopCtr = MCU_STARTING_INDEX; LoopCtr < MCU_NO_OF_STDBY_RAM_BLK;
           LoopCtr++)
      {
        /* Dummy read performed as per Errata MTU_TC.018 */
        DummyStdByRamRead[LoopCtr] = *Mcu_ConfigPtr->McuLowPowerModeCfgPtr->
                                     StdbyRamAdr[LoopCtr];

        UNUSED_PARAMETER(DummyStdByRamRead[LoopCtr]);
      }
      #endif
      /*[/cover] */

      /* [cover parentID={70E6E3B7-E52E-4e21-9B8D-2D071497A842}]
       * Set CPU mode
       * [/cover] */
      Mcu_lSetCpuMode((uint32)CoreId, MCU_STANDBY_MODE_REQ_VAL);
    }
  }
  /* [cover parentID={CAF79D02-4E3D-4eff-B1EF-4B9CDE074555}]
   * If Development Error Trace OR Safety is ON
   * [/cover] */
  #if ((MCU_DEV_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
  else
  {
    /* [cover parentID={483A0236-B345-412c-AD20-81DEE1D573E9}]
     * Report DET: Unauthorized request from the CPU
     * [/cover] */
    Mcu_lReportError(MCU_SID_SETMODE, MCU_E_UNAUTHORIZED_REQUESTER);
  }
  #endif
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={E0DDBB6C-7109-48f2-921B-E3F691E4CDB2}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE void Mcu_lWriteTrapDisReg(void)             **
**                                                                            **
** Description     : This function writes the  TRAPDIS registers to configured**
**                   value.                                                   **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Mcu_lWriteTrapDisReg(void)
{

  MCU_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(&SCU_TRAPDIS0.U,
      Mcu_ConfigPtr->McuTrapSettingConf0);
  /* [cover parentID={B4EFFB58-5B64-4a79-A606-97EBBAAD3326}]
   * If number of Cores available is more than 4
   * [/cover] */
  #if (MCAL_NO_OF_ACTIVE_CORES > 4U)

  MCU_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(&SCU_TRAPDIS1.U,
      Mcu_ConfigPtr->McuTrapSettingConf1);
  #endif
}

#if (MCU_DEINIT_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={CBCCA239-7552-4fe2-A3BE-7B2EA7FE09B6}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE void Mcu_lResetTrapDisReg(void)             **
**                                                                            **
** Description     : This function resets TRAPDIS registers .                 **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Mcu_lResetTrapDisReg(void)
{

  MCU_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(&SCU_TRAPDIS0.U,
      MCU_TRAPDIS0_RESET_VAL);
  /* [cover parentID={37B5AD55-931D-478b-8A39-EC9156EC7928}]
   * If number of Cores available is more than 4
   * [/cover] */
  #if (MCAL_NO_OF_ACTIVE_CORES > 4U)

  MCU_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(&SCU_TRAPDIS1.U,
      MCU_TRAPDIS1_RESET_VAL);
  #endif
}
#endif
/* End of #if (MCU_DEINIT_API == STD_ON) */

#if (MCU_INIT_CLOCK_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={D531A7FC-9536-41a6-A25B-7E1493155469}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE void Mcu_lInitCcuConCpuReg(void)            **
**                                                                            **
** Description     : This function initializes CPU clock configuration        **
**                   registers to configured value.                           **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Mcu_lInitCcuConCpuReg(void)
{
  /*Clock Divider Configuration for Core0 */

  MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_CCUCON6.U,
      (Mcu_ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
       .PllDistributionCfgPtr->CcuconCpu[0]));
  /* [cover parentID={D625B019-3200-4251-A1B1-EE3800F190F4}]
   * If more than 1 core is available
   * [/cover] */
  #if (MCAL_NO_OF_ACTIVE_CORES > 1U)
  /*Clock Divider Configuration for Core1 */

  MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_CCUCON7.U,
      (Mcu_ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
       .PllDistributionCfgPtr->CcuconCpu[1]));
  #endif
  /* [cover parentID={92767265-CDDE-41c0-B63B-05E21980EF8C}]
   * If more than 2 cores are available
   * [/cover] */
  #if (MCAL_NO_OF_ACTIVE_CORES > 2U)
  /*Clock Divider Configuration for Core2 */

  MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_CCUCON8.U,
      (Mcu_ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
       .PllDistributionCfgPtr->CcuconCpu[2]));
  #endif
  /* [cover parentID={ED475AD4-C56D-4527-86D1-7822D88D5427}]
   * If more than 3 cores are available
   * [/cover] */
  #if (MCAL_NO_OF_ACTIVE_CORES > 3U)
  /*Clock Divider Configuration for Core3 */

  MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_CCUCON9.U,
      (Mcu_ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
       .PllDistributionCfgPtr->CcuconCpu[3]));
  #endif
  /* [cover parentID={77537818-3180-4422-B059-E45AC6CD0F09}]
   * If more than 4 cores are available
   * [/cover] */
  #if (MCAL_NO_OF_ACTIVE_CORES > 4U)
  /*Clock Divider Configuration for Core4 */

  MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_CCUCON10.U,
      (Mcu_ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
       .PllDistributionCfgPtr->CcuconCpu[4]));
  #endif
  /* [cover parentID={7F7478AE-F77F-47fe-9255-DCABB05BEB39}]
   * If more than 5 cores are available
   * [/cover] */
  #if (MCAL_NO_OF_ACTIVE_CORES > 5U)
  /*Clock Divider Configuration for Core5 */

  MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_CCUCON11.U,
      (Mcu_ConfigPtr->McuClockSettingPtr[Mcu_ClockSetting]
       .PllDistributionCfgPtr->CcuconCpu[5]));
  #endif
}
#endif /*End of MCU_INIT_CLOCK_API */
#if (MCU_LOW_POWER_MODE_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={3964B726-1BB1-4728-865A-A0E0187F32EA}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE uint32 Mcu_lGetCpuMode(uint32 CoreId)       **
**                                                                            **
** Description     :    This function returns mode of requested CPU id.       **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Reentrant                                             **
**                                                                            **
** Parameters (in) :    CoreId - CPU logical core id                          **
**                                                                            **
** Parameters (out):    uint32 - CPU mode                                     **
**                                                                            **
** Return value    :    None                                                  **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Mcu_lGetCpuMode(const uint32 CoreId)
{
  uint32 CpuMode = (uint32)MCU_CPU_UNDEFINED_MODE;
  switch (CoreId)
  {
    /* [cover parentID={D773FD89-F036-4513-8508-402C830AD9E2}]
     * Is selected CPU Core0
     * [/cover] */
    case 0U:
      CpuMode = (uint32)SCU_PMCSR0.B.PMST;
      break;

      /* [cover parentID={52DE09A6-E126-4e0c-B9D0-49F54B272495}]
       * If more than 1 core is available
       * [/cover] */
      #if (MCAL_NO_OF_ACTIVE_CORES > 1U)
    /* [cover parentID={5DDCB03F-810D-4e0f-8843-F78ECAC8045F}]
     * Is selected CPU Core1
     * [/cover] */
    case 1U:
      CpuMode = (uint32)SCU_PMCSR1.B.PMST;
      break;
      #endif

      /* [cover parentID={BCFF1A5B-FCD9-4ae6-A0AE-34F3D7E67B0B}]
       * If more than 2 cores are available
       * [/cover] */
      #if (MCAL_NO_OF_ACTIVE_CORES > 2U)
    /* [cover parentID={040569F5-975E-4a59-A41F-0714B2CF2446}]
     * Is selected CPU Core2
     * [/cover] */
    case 2U:
      CpuMode = (uint32)SCU_PMCSR2.B.PMST;
      break;
      #endif

      /* [cover parentID={C3E0BEE2-04F2-46b4-A945-1732D440B5C4}]
       * If more than 3 cores are available
       * [/cover] */
      #if (MCAL_NO_OF_ACTIVE_CORES > 3U)
    /* [cover parentID={A6F09EDF-1430-4f9e-A477-88FCCCA1D394}]
     * Is selected CPU Core3
     * [/cover] */
    case 3U:
      CpuMode = (uint32)SCU_PMCSR3.B.PMST;
      break;
      #endif

      /* [cover parentID={BBDFA620-5FD8-42fe-A622-EC6B052EFFB2}]
       * If more than 4 cores are available
       * [/cover] */
      #if (MCAL_NO_OF_ACTIVE_CORES > 4U)
    /* [cover parentID={4BC0F895-5D14-4fba-97DB-279318CDCAC5}]
     * Is selected CPU Core4
     * [/cover] */
    case 4U:
      CpuMode = (uint32)SCU_PMCSR4.B.PMST;
      break;
      #endif

      /* [cover parentID={7D597FA9-38F0-4538-8BC7-194ECB195BD7}]
       * If more than 5 cores are available
       * [/cover] */
      #if (MCAL_NO_OF_ACTIVE_CORES > 5U)
    /* [cover parentID={E8AA565B-A627-401c-B957-7B5AFB5A8DDB}]
     * Is selected CPU Core5
     * [/cover] */
    case 5U:
      CpuMode = (uint32)SCU_PMCSR5.B.PMST;
      break;
      #endif

    default:
      /* Invalid logical core id is passed to the function*/
      break;
  }
  return (CpuMode);
}
#endif
/* End of #if (MCU_LOW_POWER_MODE_API == STD_ON) */

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={834F5C76-E1AE-4e51-8683-E51F77FB740A}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE void Mcu_lSetCpuMode                        **
**                              (uint8 CoreId, uint8 ModeReq)                 **
**                                                                            **
** Description     :    This function sets CPU mode of requested core id.     **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Reentrant for other cores                             **
**                                                                            **
** Parameters (in) :    CoreId  - CPU logical core id.                        **
**                      ModeReq - Requested mode id.                          **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    None                                                  **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Mcu_lSetCpuMode(const uint32 CoreId, const uint32 ModeReq)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_PMCSR0 PMCSR0Val;
  /* [cover parentID={D470E823-8860-4329-9C7D-C3287BE4751A}]
   * If number of Cores is more than 1
   * [/cover] */
  #if (MCAL_NO_OF_ACTIVE_CORES > 1U)
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_PMCSR1 PMCSR1Val;
  #endif
  /* [cover parentID={957C02BB-F288-4034-BEA3-819D4A5941CF}]
   * If number of Cores is more than 2
   * [/cover] */
  #if (MCAL_NO_OF_ACTIVE_CORES > 2U)
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_PMCSR2 PMCSR2Val;
  #endif
  /* [cover parentID={630BC937-DAD7-4071-A6D8-20EC3C287B1A}]
   * If number of Cores is more than 3
   * [/cover] */
  #if (MCAL_NO_OF_ACTIVE_CORES > 3U)
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_PMCSR3 PMCSR3Val;
  #endif
  /* [cover parentID={E5EB92DD-1486-4342-AF4F-6D898A7B5589}]
   * If number of cores is more than 4
   * [/cover] */
  #if (MCAL_NO_OF_ACTIVE_CORES > 4U)
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_PMCSR4 PMCSR4Val;
  #endif
  /* [cover parentID={B6A4298F-EFDB-48dc-A701-438F33887320}]
   * If number of cores is more than 5
   * [/cover] */
  #if (MCAL_NO_OF_ACTIVE_CORES > 5U)
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_PMCSR5 PMCSR5Val;
  #endif

  switch (CoreId)
  {
    /* [cover parentID={2D57DEFD-A0FF-4b31-B850-60E01EA5A4B5}]
     * Is Core0 selected
     * [/cover] */
    case 0U:
      PMCSR0Val.U = SCU_PMCSR0.U;
      /* MISRA2012_RULE_10_3_JUSTIFICATION: Assignment to narrower
         type as a register bit-field value (REQSLP : 2bit wide) is
         written and ModeReq value is limited between 1 - 3 by
         caller function. */
      PMCSR0Val.B.REQSLP = ModeReq;

      MCU_LIB_RUNTIME_WRITECPUENDINITPROTREG(&SCU_PMCSR0.U, PMCSR0Val.U);
      break;

      /* [cover parentID={D470E823-8860-4329-9C7D-C3287BE4751A}]
       * If number of Cores is more than 1
       * [/cover] */
      #if (MCAL_NO_OF_ACTIVE_CORES > 1U)
    /* [cover parentID={D274CFE0-FC37-40cb-8D60-21C90EA634E4}]
     * Is Core1  selected
     * [/cover] */
    case 1U:
      PMCSR1Val.U = SCU_PMCSR1.U;
      /* MISRA2012_RULE_10_3_JUSTIFICATION: Assignment to narrower
         type as a register bit-field value (REQSLP : 2bit wide) is
         written and ModeReq value is limited between 1 - 3 by
         caller function. */
      PMCSR1Val.B.REQSLP = ModeReq;

      MCU_LIB_RUNTIME_WRITECPUENDINITPROTREG(&SCU_PMCSR1.U, PMCSR1Val.U);
      break;
      #endif

      /* [cover parentID={957C02BB-F288-4034-BEA3-819D4A5941CF}]
       * If number of Cores is more than 2
       * [/cover] */
      #if (MCAL_NO_OF_ACTIVE_CORES > 2U)
    /* [cover parentID={48B59F24-D01E-4daf-B863-CA97EE49DBC7}]
     * Is Core2 selected
     * [/cover] */
    case 2U:
      PMCSR2Val.U = SCU_PMCSR2.U;
      /* MISRA2012_RULE_10_3_JUSTIFICATION: Assignment to narrower
         type as a register bit-field value (REQSLP : 2bit wide) is
         written and ModeReq value is limited between 1 - 3 by
         caller function. */
      PMCSR2Val.B.REQSLP = ModeReq;

      MCU_LIB_RUNTIME_WRITECPUENDINITPROTREG(&SCU_PMCSR2.U, PMCSR2Val.U);
      break;
      #endif

      /* [cover parentID={630BC937-DAD7-4071-A6D8-20EC3C287B1A}]
       * If number of Cores is more than 3
       * [/cover] */
      #if (MCAL_NO_OF_ACTIVE_CORES > 3U)
    /* [cover parentID={73C6AF87-98DC-4607-B96A-A58C777DEF5C}]
     * Is Core3 selected
     * [/cover] */
    case 3U:
      PMCSR3Val.U = SCU_PMCSR3.U;
      /* MISRA2012_RULE_10_3_JUSTIFICATION: Assignment to narrower
         type as a register bit-field value (REQSLP : 2bit wide) is
         written and ModeReq value is limited between 1 - 3 by
         caller function. */
      PMCSR3Val.B.REQSLP = ModeReq;

      MCU_LIB_RUNTIME_WRITECPUENDINITPROTREG(&SCU_PMCSR3.U, PMCSR3Val.U);
      break;
      #endif

      /* [cover parentID={E5EB92DD-1486-4342-AF4F-6D898A7B5589}]
       * If number of cores is more than 4
       * [/cover] */
      #if (MCAL_NO_OF_ACTIVE_CORES > 4U)
    /* [cover parentID={F7ED9270-7F77-4396-988A-42FFDD9DFF74}]
     * Is Core4 Selected
     * [/cover] */
    case 4U:
      PMCSR4Val.U = SCU_PMCSR4.U;
      /* MISRA2012_RULE_10_3_JUSTIFICATION: Assignment to narrower
        type as a register bit-field value (REQSLP : 2bit wide) is
        written and ModeReq value is limited between 1 - 3 by
        caller function. */
      PMCSR4Val.B.REQSLP = ModeReq;

      MCU_LIB_RUNTIME_WRITECPUENDINITPROTREG(&SCU_PMCSR4.U, PMCSR4Val.U);
      break;
      #endif

      /* [cover parentID={B6A4298F-EFDB-48dc-A701-438F33887320}]
       * If number of cores is more than 5
       * [/cover] */
      #if (MCAL_NO_OF_ACTIVE_CORES > 5U)
    /* [cover parentID={0C8C3934-B5F0-43aa-8B1A-1309A98AF2B3}]
     * Is Core5 selected
     * [/cover] */
    case 5U:
      PMCSR5Val.U = SCU_PMCSR5.U;
      /* MISRA2012_RULE_10_3_JUSTIFICATION: Assignment to narrower
         type as a register bit-field value (REQSLP : 2bit wide) is
         written and ModeReq value is limited between 1 - 3 by
         caller function. */
      PMCSR5Val.B.REQSLP = ModeReq;

      MCU_LIB_RUNTIME_WRITECPUENDINITPROTREG(&SCU_PMCSR5.U, PMCSR5Val.U);
      break;
      #endif

    default:
      /* Invalid logical core id is passed to the function*/
      break;
  }
}
/* [cover parentID={090D6842-D490-4b84-BE3A-A59A774FCCB0}]
 * If DET or Safety is ON*/
#if ((MCU_DEV_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
**                                                                            **
** Traceability    :  [cover parentID={F901FE78-2F76-4fcc-A977-DBCC12458A50}] **
**                                                                            **
** Syntax          : static void Mcu_lReportError                             **
**                       (const uint8 ApiId, const uint8 ErrorId)             **
**                                                                            **
** Description     :  This function calls the appropriate error handlers.     **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Reentrant                                               **
**                                                                            **
** Parameters (in) :  ApiId   - API service ID.                               **
**                    ErrorId - Error Identifier.                             **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
static void Mcu_lReportError(const uint8 ApiId, const uint8 ErrorId)
{
  /* [cover parentID={C9E8729F-2EC8-45e0-B9F9-4954213DB516}]
   * If Safety is Enabled
   * [/cover] */
  #if (MCU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={6EB5712C-826E-4116-AF19-AB7FDE526A3A}]
   * Report Safety Error
   * [/cover] */
  Mcal_ReportSafetyError((uint16)MCU_MODULE_ID, MCU_MODULE_INSTANCE,
                         ApiId, ErrorId);
  #endif

  /* [cover parentID={B7BD255B-1E86-49a9-AC7B-E46A24BB1321}]
   * If Development Error Trace is ON
   * [/cover] */
  #if (MCU_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={8C7FD36E-1813-4a5d-80AE-608719DBBDEC}]
   * Report DET
   * [/cover] */
  (void)Det_ReportError((uint16)MCU_MODULE_ID, MCU_MODULE_INSTANCE,
                                                         ApiId, ErrorId);
  #endif
}
#endif
/*[/cover] */
/* End of #if (( MCU_DEV_ERROR_DETECT == STD_ON) || \
                                               (MCU_SAFETY_ENABLE == STD_ON)) */

/* [cover parentID={270E47B5-6007-480c-A84C-BBF398BD94F5}]
 * If Multicore error detect OR Safety is ON
 * [/cover] */
#if ((MCU_MULTICORE_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
**                                                                            **
** Traceability    :  [cover parentID={1C35E6BC-3A4E-4fb2-8F14-882E0D3C8C53}] **
**                                                                            **
** Syntax          : static void Mcu_lReportMultiCoreError                    **
**                       (const uint8 ApiId, const uint8 ErrorId)             **
**                                                                            **
** Description     :  This function calls the appropriate error handlers.     **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Reentrant                                               **
**                                                                            **
** Parameters (in) :  ApiId   - API service ID.                               **
**                    ErrorId - Error Identifier.                             **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
static void Mcu_lReportMultiCoreError(
  const uint8 ApiId,
  const uint8 ErrorId)
{
  /* [cover parentID={741E7B41-90B5-4f1f-B269-DC248E8928F6}]
   * If Multicore Error detection is ON
   * [/cover] */
  #if (MCU_MULTICORE_ERROR_DETECT == STD_ON)
  /* [cover parentID={83B5FC08-42FD-4af8-B8A7-8DD46C90B3B1}]
   * Report MultiCore error
   * [/cover] */
  (void)Det_ReportError((uint16)MCU_MODULE_ID, MCU_MODULE_INSTANCE,
                                                            ApiId, ErrorId);
  #endif

  /* [cover parentID={64F4C44F-D603-4a25-BEC0-DCBBD0938588}]
   * If Safety check and reporting is Enabled
   * [/cover] */
  #if (MCU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={67BE8883-372B-4bf1-87A6-330D463F2020}]
   * Report Safety Error
   * [/cover] */
  Mcal_ReportSafetyError((uint16)MCU_MODULE_ID, MCU_MODULE_INSTANCE,
                         ApiId, ErrorId);
  #endif
}
#endif
/* End of #if (( MCU_MULTICORE_ERROR_DETECT == STD_ON) || \
                                               (MCU_SAFETY_ENABLE == STD_ON)) */

#if ((MCU_GTM_USED == STD_ON) && (MCU_INITCHECK_API == STD_ON))
/*******************************************************************************
**                                                                            **
** Traceability    :  [cover parentID={E0BAEEE4-F915-4b93-9C34-062BA3156998}] **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType Mcu_lGtmGlobalInitCheck      **
**                   (void)                                                   **
**                                                                            **
** Description     : This function checks whether GTM initialization is       **
**                   successful or not.                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for other channels                             **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK     : GTM initialization check successful           **
**                   E_NOT_OK : GTM initialization check failed               **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Mcu_lGtmGlobalInitCheck(void)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
     defined to modify certain bits and avoid 32-bit mask value.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_GTM_CLC GtmClcVal;
  uint32 SfrVal;
  uint32 ConfigVal;
  uint32 CmpVal = 0xFFFFFFFFU;
  Std_ReturnType CompResult;
  Std_ReturnType RetVal = E_NOT_OK;
  uint8 TbuChInfo = (uint8)(Mcu_ConfigPtr->McuGtmConfigPtr->GtmTbuCfg &
                              MCU_TBU_CH_EN_MSK);

  GtmClcVal.B.DISS = 0;
  GtmClcVal.B.DISR = 0;
  GtmClcVal.B.reserved_2 = 0;
  GtmClcVal.B.EDIS = 0;
  GtmClcVal.B.reserved_4 = 0;

  /* [cover parentID={5B707FEA-3267-4fb4-9780-54693BC9180F}]
   * Is GTM sleep mode enabled
   * [/cover] */
  if ((boolean)TRUE == Mcu_ConfigPtr->McuGtmConfigPtr->IsGtmSleepModeEnabled)
  {
    GtmClcVal.B.EDIS = 0x0U;
  }
  else
  {
    GtmClcVal.B.EDIS = 0x1U;
  }

  SfrVal    = GTM_CLC.U;
  ConfigVal = GtmClcVal.U;
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  /* Check if GTM kernel is enabled */
  /* [cover parentID={63CEE360-4F46-48df-B096-6B28DC9AB590}]
   * Is GTM Clock enabled
   * [/cover] */
  if (CmpVal == 0xFFFFFFFFU)
  {
    /* [cover parentID={CFE53AE9-2B7D-4026-9E7C-26AEF35E96E4}]
     * Verify contents of Clock management unit
     * [/cover] */
    CompResult = Mcu_lGtmCmuGlobalInitCheck();
    CmpVal    &= ~(E_OK ^ (uint32)CompResult);

    #if (MCU_GTM_NO_OF_TBU_CH_AVAILABLE > 0U)
    if (((TbuChInfo >> IFX_GTM_TBU_CHEN_ENDIS_CH0_OFF) &
            IFX_GTM_TBU_CHEN_ENDIS_CH0_MSK) == MCU_TBU_CH_ENABLED)
    {
      SfrVal    = GTM_TBU_CH0_CTRL.U;
      ConfigVal = ((Mcu_ConfigPtr->McuGtmConfigPtr->GtmTbuCfg >>
                    MCU_TBU_CH0_OFF) &
                   MCU_TBU_CH_0_2_MASK);
      CmpVal   &= ~(SfrVal ^ ConfigVal);
    }
    #endif

    #if (MCU_GTM_NO_OF_TBU_CH_AVAILABLE > 1U)
    if (((TbuChInfo >> IFX_GTM_TBU_CHEN_ENDIS_CH1_OFF) &
            IFX_GTM_TBU_CHEN_ENDIS_CH1_MSK) == MCU_TBU_CH_ENABLED)
    {
      SfrVal    = GTM_TBU_CH1_CTRL.U;
      ConfigVal = ((Mcu_ConfigPtr->McuGtmConfigPtr->GtmTbuCfg >>
                    MCU_TBU_CH1_OFF) &
                   MCU_TBU_CH_0_2_MASK);
      CmpVal   &= ~(SfrVal ^ ConfigVal);
    }
    #endif

    #if (MCU_GTM_NO_OF_TBU_CH_AVAILABLE > 2U)
    if (((TbuChInfo >> IFX_GTM_TBU_CHEN_ENDIS_CH2_OFF) &
            IFX_GTM_TBU_CHEN_ENDIS_CH2_MSK) == MCU_TBU_CH_ENABLED)
    {
      SfrVal    = GTM_TBU_CH2_CTRL.U;
      ConfigVal = ((Mcu_ConfigPtr->McuGtmConfigPtr->GtmTbuCfg >>
                    MCU_TBU_CH2_OFF) &
                   MCU_TBU_CH_0_2_MASK);
      CmpVal   &= ~(SfrVal ^ ConfigVal);
    }
    #endif

    #if (MCU_GTM_NO_OF_TBU_CH_AVAILABLE > 3U)
    if (((TbuChInfo >> IFX_GTM_TBU_CHEN_ENDIS_CH3_OFF) &
            IFX_GTM_TBU_CHEN_ENDIS_CH3_MSK) == MCU_TBU_CH_ENABLED)
    {
      SfrVal    = ((uint32)GTM_TBU_CH3_CTRL.U & MCU_TBU_CH3_MODE_MASK);
      ConfigVal = ((Mcu_ConfigPtr->McuGtmConfigPtr->GtmTbuCfg >>
                    MCU_TBU_CH3_OFF) &
                   MCU_TBU_CH3_MODE_MASK);
      CmpVal   &= ~(SfrVal ^ ConfigVal);
    }
    #endif

    SfrVal    = ((GTM_TBU_CHEN.U) & MCU_TBU_CHEN_MSK);
    ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->GtmTbuCfg & MCU_TBU_CH_EN_MSK;
    CmpVal   &= ~(SfrVal ^ ConfigVal);

    /* [cover parentID={05F6666D-0B9E-49fc-B30E-31C1634BB9DC}]
     * Verify contents of cluster
     * [/cover] */
    CompResult = Mcu_lGtmCcmGlobalInitCheck();
    CmpVal    &= ~(E_OK ^ (uint32)CompResult);

    /* [cover parentID={49CBA948-BAF6-4db2-A5FD-B3220CDA3DD4}]
     * Verify contents of ATOM
     * [/cover] */
    CompResult = Mcu_lGtmAtomGlobalInitCheck();
    CmpVal    &= ~(E_OK ^ (uint32)CompResult);

    /* [cover parentID={C6192888-B7FA-4ec6-9C55-5005E400C876}]
     * Verify Contents of TOM
     * [/cover] */
    CompResult = Mcu_lGtmTomGlobalInitCheck();
    CmpVal    &= ~(E_OK ^ (uint32)CompResult);

    /* [cover parentID={0FEB6C77-58DD-4533-9B95-F00D953E1B6E}]
     * Verify GTM to ADC trigger settings
     * [/cover] */
    CompResult = Mcu_lGtmTriggerInitCheck();
    CmpVal    &= ~(E_OK ^ (uint32)CompResult);

    /* [cover parentID={55AFEF64-157B-4ce6-9E45-7A978CDA3070}]
     * Verify Toutselx settings
     * [/cover] */
    CompResult = Mcu_lGtmToutSelInitCheck();
    CmpVal    &= ~(E_OK ^ (uint32)CompResult);

    CompResult = Mcu_lGtmTimInselInitCheck();
    CmpVal    &= ~(E_OK ^ (uint32)CompResult);
  }

  /* [cover parentID={76B7AF47-6CE4-4b48-B94E-515FECA7CEFB}]
   * Are all verifications successful
   * [/cover] */
  if (CmpVal == 0xFFFFFFFFU)
  {
    RetVal = E_OK;
  }

  return RetVal;
}

/*******************************************************************************
**                                                                            **
** Traceability    :  [cover parentID={2B3D013D-C290-483a-A715-0C3F4BB31FA1}] **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType Mcu_lGtmCmuGlobalInitCheck   **
**                   (void)                                                   **
**                                                                            **
** Description     : This function checks whether CMU initialization is       **
**                   successful or not.                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for other channels                             **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK     : CMU Initcheck successful                      **
**                   E_NOT_OK : CMU Initcheck failed                          **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Mcu_lGtmCmuGlobalInitCheck(void)
{
  uint32 SfrVal;
  uint32 ConfigVal;
  uint32 CmpVal = 0xFFFFFFFFU;
  Std_ReturnType RetVal = E_NOT_OK;

  SfrVal    = GTM_CMU_GCLK_NUM.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->
              GtmClockCfgPtr->GtmCmuGlobalNumerator;
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = GTM_CMU_GCLK_DEN.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->
              GtmClockCfgPtr->GtmCmuGlobalDenominator;
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = GTM_CMU_CLK_0_CTRL.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->
              GtmClockCfgPtr->GtmCmuConfClkCtrl[0];
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = GTM_CMU_CLK_1_CTRL.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->
              GtmClockCfgPtr->GtmCmuConfClkCtrl[1];
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = GTM_CMU_CLK_2_CTRL.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->
              GtmClockCfgPtr->GtmCmuConfClkCtrl[2];
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = GTM_CMU_CLK_3_CTRL.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->
              GtmClockCfgPtr->GtmCmuConfClkCtrl[3];
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = GTM_CMU_CLK_4_CTRL.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->
              GtmClockCfgPtr->GtmCmuConfClkCtrl[4];
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = GTM_CMU_CLK_5_CTRL.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->
              GtmClockCfgPtr->GtmCmuConfClkCtrl[5];
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = GTM_CMU_CLK_6_CTRL.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->
              GtmClockCfgPtr->GtmCmuConfClkCtrl[6];
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = GTM_CMU_CLK_7_CTRL.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->
              GtmClockCfgPtr->GtmCmuConfClkCtrl[7];
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = GTM_CMU_ECLK_0_NUM.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->
              GtmClockCfgPtr->GtmEclkCtrl[0].GtmCmuExtClockNum;
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = GTM_CMU_ECLK_0_DEN.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->
              GtmClockCfgPtr->GtmEclkCtrl[0].GtmCmuExtClockDen;
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = GTM_CMU_ECLK_1_NUM.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->
              GtmClockCfgPtr->GtmEclkCtrl[1].GtmCmuExtClockNum;
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = GTM_CMU_ECLK_1_DEN.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->
              GtmClockCfgPtr->GtmEclkCtrl[1].GtmCmuExtClockDen;
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = GTM_CMU_ECLK_2_NUM.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->
              GtmClockCfgPtr->GtmEclkCtrl[2].GtmCmuExtClockNum;
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = GTM_CMU_ECLK_2_DEN.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->
              GtmClockCfgPtr->GtmEclkCtrl[2].GtmCmuExtClockDen;
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = GTM_CMU_FXCLK_CTRL.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->
              GtmClockCfgPtr->GtmCmuFixedClkCtrl;
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = GTM_CLS_CLK_CFG.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->
              GtmClockCfgPtr->GtmCmuClsInDiv;
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = ((uint32)GTM_CMU_CLK_EN.U & GTM_CMU_CLK_EN_CHK_MSK);
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->
              GtmClockCfgPtr->GtmCmuClockEnable;
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  if (CmpVal == 0xFFFFFFFFU)
  {
    RetVal = E_OK;
  }

  return RetVal;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={EAB5E5F5-93A7-47a9-980D-077BDB8F2738}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType Mcu_lGtmCcmGlobalInitCheck   **
**                   (void)                                                   **
**                                                                            **
** Description     : This function checks whether Cluster initialization      **
**                   is successful or not.                                    **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for other channels                             **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK     : CCM Initcheck successful                      **
**                   E_NOT_OK : CCM Initcheck failed                          **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Mcu_lGtmCcmGlobalInitCheck(void)
{
  uint32 SfrVal;
  uint32 ConfigVal;
  uint32 CmpVal = 0xFFFFFFFFU;
  Std_ReturnType RetVal = E_NOT_OK;
  uint8 ClusterIndex;
  uint8 ClsClkVal;

  /* [cover parentID={D50E351E-23EB-4b95-93C9-A1108E2B78F9}]
   * Loop through available clusters
   * [/cover] */
  for (ClusterIndex = MCU_STARTING_INDEX;
       ClusterIndex < MCU_GTM_NO_OF_CCM_AVAILABLE; ClusterIndex++)
  {
    /* Check the cluster clock is Enabled/Disabled */
    ClsClkVal = (uint8)(((GTM_CLS_CLK_CFG.U) >> \
                         (MCU_GTM_CLS_CLK_LEN * ClusterIndex)) & \
                          MCU_GTM_CLS_CLK_DIV_MSK);

    /* [cover parentID={EC6AB24A-0E67-4d5f-ACE9-565420916DDE}]
     * Is cluster clock enabled
     * [/cover] */
    if (ClsClkVal != 0x0U)
    {
      if ( Mcu_ConfigPtr->McuGtmConfigPtr->
                        GtmClusterCfgPtr[ClusterIndex].GtmCcmCfg != 0x0U)
      {
        SfrVal    = (((uint32)MODULE_GTM.CCM[ClusterIndex].CFG.U) & \
                    Mcu_ConfigPtr->McuGtmConfigPtr->GtmClusterCfgPtr[ClusterIndex]
                   .GtmCcmCfg) ;
        ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->GtmClusterCfgPtr[ClusterIndex]
                    .GtmCcmCfg;
        CmpVal   &= ~(SfrVal ^ ConfigVal);
      }

      SfrVal    = MODULE_GTM.CCM[ClusterIndex].CMU_CLK_CFG.U;
      ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->GtmClusterCfgPtr[ClusterIndex]
                  .GtmCcmConfClockCfg;
      CmpVal   &= ~(SfrVal ^ ConfigVal);

      SfrVal    = MODULE_GTM.CCM[ClusterIndex].CMU_FXCLK_CFG.U;
      ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->GtmClusterCfgPtr[ClusterIndex]
                  .GtmCcmFixedClockCfg;
      CmpVal   &= ~(SfrVal ^ ConfigVal);
    }
  }

  /* [cover parentID={BEBF16A7-DAA2-4e94-B4BE-7BF734602885}]
   * Verify Cluster settings against configured value
   * [/cover] */
  if (CmpVal == 0xFFFFFFFFU)
  {
    RetVal = E_OK;
  }

  return RetVal;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={B464F893-423D-48a5-B9A8-B34BF284C686}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType Mcu_lGtmAtomGlobalInitCheck  **
**                   (void)                                                   **
**                                                                            **
** Description     : This function checks whether ATOM initialization         **
**                   is successful or not.                                    **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for other channels                             **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK     : ATOM Initcheck successful                     **
**                   E_NOT_OK : ATOM Initcheck failed                         **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Mcu_lGtmAtomGlobalInitCheck(void)
{
  const Ifx_GTM_ATOM_AGC *AtomAgcRegPtr;
  uint32 CmpVal = 0xFFFFFFFFU;
  uint32 SfrVal;
  uint32 ConfigVal;
  Std_ReturnType RetVal = E_NOT_OK;
  uint8 AtomModuleIndex;

  /* [cover parentID={F680819D-92F7-4d84-B5C9-373BC52B671F}]
   * Loop through available ATOM modules
   * [/cover] */
  for (AtomModuleIndex = MCU_STARTING_INDEX;
       AtomModuleIndex < MCU_GTM_NO_OF_ATOM_AVAILABLE; AtomModuleIndex++)
  {
    /* Is the ATOM module used by other MCAL drivers */
    /* [cover parentID={77078740-0B28-48c4-A8FD-C111456A6CE4}]
     * Verify ATOM settings against configured value
     * [/cover] */
    if (((Mcu_ConfigPtr->McuGtmConfigPtr->GtmAtomModuleUsage >>
          AtomModuleIndex) & 0x1U) == 0x1U)
    {

      AtomAgcRegPtr = GTM_ATOM_AGC_POINTER(AtomModuleIndex);

      SfrVal    = AtomAgcRegPtr->INT_TRIG.U & MCU_GTM_ATOM_TRIG_INITCHK_READ_MSK;
      ConfigVal = ((Mcu_ConfigPtr->McuGtmConfigPtr->GtmAtomCfg[AtomModuleIndex]
                   .AtomAgcIntTrigRstCn0 ^ MCU_GTM_ATOM_TRIG_INITCHK_MSK) 
                  & MCU_GTM_ATOM_TRIG_INITCHK_READ_MSK);
      CmpVal   &= ~(SfrVal ^ ConfigVal);

      SfrVal    = AtomAgcRegPtr->FUPD_CTRL.U & MCU_GTM_ATOM_RSTCN0_INITCHK_READ_MSK;
      ConfigVal = ((Mcu_ConfigPtr->McuGtmConfigPtr->GtmAtomCfg[AtomModuleIndex]
                   .AtomAgcIntTrigRstCn0 ^ MCU_GTM_ATOM_RSTCN0_INITCHK_MSK) 
                  & MCU_GTM_ATOM_RSTCN0_INITCHK_READ_MSK);
      CmpVal   &= ~(SfrVal ^ ConfigVal);

      SfrVal    = (AtomAgcRegPtr->ACT_TB.U & (~MCU_ATOM_ACT_TB_TRIG_MSK));
      ConfigVal = (Mcu_ConfigPtr->McuGtmConfigPtr->GtmAtomCfg[AtomModuleIndex]
                   .AtomAgcActTb);
      CmpVal   &= ~(SfrVal ^ ConfigVal);
    }
  }

  /*[cover parentID={D93F6D87-BA42-4950-AFC5-2760CF94FEA4}][/cover]*/
  if (CmpVal == 0xFFFFFFFFU)
  {
    RetVal = E_OK;
  }

  return RetVal;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={22A5F790-2618-4d85-8995-34C895C0721A}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType Mcu_lGtmTomGlobalInitCheck   **
**                   (void)                                                   **
**                                                                            **
** Description     : This function checks whether TOM initialization          **
**                   is successful or not.                                    **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for other channels                             **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK     : TOM Initcheck successful                      **
**                   E_NOT_OK : TOM Initcheck failed                          **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Mcu_lGtmTomGlobalInitCheck(void)
{
  const Mcu_17_Gtm_TomTgc *TomTgcRegPtr;
  uint32 CmpVal = 0xFFFFFFFFU;
  uint32 SfrVal;
  uint32 ConfigVal;
  Std_ReturnType RetVal = E_NOT_OK;
  uint8 TomModuleIndex;
  uint8 GtmTomCfgIndex;

  /* [cover parentID={40E7754C-77BE-4ef8-BB07-FF0E6599FECE}]
   * Loop through available TOM modules
   * [/cover] */
  for (TomModuleIndex = MCU_STARTING_INDEX;
       TomModuleIndex < MCU_GTM_NO_OF_TOM_AVAILABLE; TomModuleIndex++)
  {
    /* Is the TOM module used by other MCAL drivers */
    /* [cover parentID={397D7604-75D0-420f-B956-12697B173626}]
     * Verify TOM settings against configured value*/
    if (((Mcu_ConfigPtr->McuGtmConfigPtr->GtmTomModuleUsage >>
          TomModuleIndex) & 0x1U) == 0x1U)
    {
      /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
       * by violating this MISRA rule, as the pointer to the object type
       * it is getting cast into is a known type . */
      /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
       * by violating this MISRA rule. */
      TomTgcRegPtr   = GTM_TOM_TGC_POINTER(TomModuleIndex, 0x0U);
      GtmTomCfgIndex = (2U * TomModuleIndex);

      SfrVal    = TomTgcRegPtr->TGC_INT_TRIG.U & MCU_GTM_TOM_TRIG_INITCHK_READ_MSK;
      ConfigVal = ((Mcu_ConfigPtr->McuGtmConfigPtr->GtmTomCfg[GtmTomCfgIndex]
                   .TomTgcIntTrigRstCn0 ^ MCU_GTM_TOM_TRIG_INITCHK_MSK) 
           & MCU_GTM_TOM_TRIG_INITCHK_READ_MSK);
      CmpVal   &= ~(SfrVal ^ ConfigVal);

      SfrVal    = TomTgcRegPtr->TGC_FUPD_CTRL.U & MCU_GTM_TOM_RSTCN0_INITCHK_READ_MSK;
      ConfigVal = ((Mcu_ConfigPtr->McuGtmConfigPtr->GtmTomCfg[GtmTomCfgIndex]
                   .TomTgcIntTrigRstCn0 ^ MCU_GTM_TOM_RSTCN0_INITCHK_MSK) 
           & MCU_GTM_TOM_RSTCN0_INITCHK_READ_MSK);
      CmpVal   &= ~(SfrVal ^ ConfigVal);

      SfrVal    = (TomTgcRegPtr->TGC_ACT_TB.U & (~MCU_TOM_ACT_TB_TRIG_MSK));
      ConfigVal = (Mcu_ConfigPtr->McuGtmConfigPtr->GtmTomCfg[GtmTomCfgIndex]
                   .TomTgcActTb);
      CmpVal   &= ~(SfrVal ^ ConfigVal);

      /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
       * by violating this MISRA rule, as the pointer to the object type
       * it is getting cast into is a known type . */
      /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
       * by violating this MISRA rule. */
      TomTgcRegPtr   = GTM_TOM_TGC_POINTER(TomModuleIndex, 0x1U);
      GtmTomCfgIndex = ((2U * TomModuleIndex) + 0x1U);

      SfrVal    = TomTgcRegPtr->TGC_INT_TRIG.U & MCU_GTM_TOM_TRIG_INITCHK_READ_MSK;
      ConfigVal = ((Mcu_ConfigPtr->McuGtmConfigPtr->GtmTomCfg[GtmTomCfgIndex]
                   .TomTgcIntTrigRstCn0 ^ MCU_GTM_TOM_TRIG_INITCHK_MSK) 
           & MCU_GTM_TOM_TRIG_INITCHK_READ_MSK);
      CmpVal   &= ~(SfrVal ^ ConfigVal);

      SfrVal    = TomTgcRegPtr->TGC_FUPD_CTRL.U & MCU_GTM_TOM_RSTCN0_INITCHK_READ_MSK;
      ConfigVal = ((Mcu_ConfigPtr->McuGtmConfigPtr->GtmTomCfg[GtmTomCfgIndex]
                   .TomTgcIntTrigRstCn0 ^ MCU_GTM_TOM_RSTCN0_INITCHK_MSK) 
           & MCU_GTM_TOM_RSTCN0_INITCHK_READ_MSK);
      CmpVal   &= ~(SfrVal ^ ConfigVal);

      SfrVal    = (TomTgcRegPtr->TGC_ACT_TB.U & (~MCU_TOM_ACT_TB_TRIG_MSK));
      ConfigVal = (Mcu_ConfigPtr->McuGtmConfigPtr->GtmTomCfg[GtmTomCfgIndex]
                   .TomTgcActTb);
      CmpVal   &= ~(SfrVal ^ ConfigVal);
    }
  }

  if (CmpVal == 0xFFFFFFFFU)
  {
    RetVal = E_OK;
  }
  /*[/cover] */
  return RetVal;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={32E238CA-EF07-4979-834C-ADFC47352812}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType Mcu_lGtmTriggerInitCheck     **
**                   (void)                                                   **
**                                                                            **
** Description     : This This function checks whether GTM to Trigger         **
**                   initialization is successful or not.                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for other channels                             **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK     : GTM trigger Initcheck successful              **
**                   E_NOT_OK : GTM trigger Initcheck failed                  **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Mcu_lGtmTriggerInitCheck(void)
{
  uint32 SfrVal;
  uint32 ConfigVal;
  uint32 CmpVal = 0xFFFFFFFFU;
  Std_ReturnType RetVal = E_NOT_OK;

  SfrVal    = (uint32)GTM_ADCTRIG0OUT0.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->GtmAdcTrigCfg[0].GtmAdcTrigOut0;
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = (uint32)GTM_ADCTRIG0OUT1.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->GtmAdcTrigCfg[0].GtmAdcTrigOut1;
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = (uint32)GTM_ADCTRIG1OUT0.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->GtmAdcTrigCfg[1].GtmAdcTrigOut0;
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = (uint32)GTM_ADCTRIG1OUT1.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->GtmAdcTrigCfg[1].GtmAdcTrigOut1;
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = (uint32)GTM_ADCTRIG2OUT0.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->GtmAdcTrigCfg[2].GtmAdcTrigOut0;
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = (uint32)GTM_ADCTRIG2OUT1.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->GtmAdcTrigCfg[2].GtmAdcTrigOut1;
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = (uint32)GTM_ADCTRIG3OUT0.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->GtmAdcTrigCfg[3].GtmAdcTrigOut0;
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = (uint32)GTM_ADCTRIG3OUT1.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->GtmAdcTrigCfg[3].GtmAdcTrigOut1;
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = (uint32)GTM_ADCTRIG4OUT0.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->GtmAdcTrigCfg[4].GtmAdcTrigOut0;
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = (uint32)GTM_ADCTRIG4OUT1.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->GtmAdcTrigCfg[4].GtmAdcTrigOut1;
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  #if (MCU_GTM_TO_DSADC_TRIG_AVAILABLE == STD_ON)
  SfrVal    = (uint32)GTM_DSADCOUTSEL00.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->GtmDsadcTrigCfg[0].GtmDsadcTrigOut0;
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = (uint32)GTM_DSADCOUTSEL10.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->GtmDsadcTrigCfg[1].GtmDsadcTrigOut0;
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = (uint32)GTM_DSADCOUTSEL20.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->GtmDsadcTrigCfg[2].GtmDsadcTrigOut0;
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = (uint32)GTM_DSADCOUTSEL30.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->GtmDsadcTrigCfg[3].GtmDsadcTrigOut0;
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  #if (MCU_GTM_TO_DSADC_TRIG1 == STD_ON)
  SfrVal    = (uint32)GTM_DSADCOUTSEL01.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->GtmDsadcTrigCfg[0].GtmDsadcTrigOut1;
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = (uint32)GTM_DSADCOUTSEL11.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->GtmDsadcTrigCfg[1].GtmDsadcTrigOut1;
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = (uint32)GTM_DSADCOUTSEL21.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->GtmDsadcTrigCfg[2].GtmDsadcTrigOut1;
  CmpVal   &= ~(SfrVal ^ ConfigVal);

  SfrVal    = (uint32)GTM_DSADCOUTSEL31.U;
  ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->GtmDsadcTrigCfg[3].GtmDsadcTrigOut1;
  CmpVal   &= ~(SfrVal ^ ConfigVal);
  #endif
  #endif /*End of (MCU_GTM_TO_DSADC_TRIG_AVAILABLE == STD_ON)*/

  if (CmpVal == 0xFFFFFFFFU)
  {
    RetVal = E_OK;
  }

  return RetVal;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={DEFD04E6-5C91-46ca-AEBA-FC422E8AE179}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType Mcu_lGtmToutSelInitCheck     **
**                   (void)                                                   **
**                                                                            **
** Description     : This function checks whether GTM to Port                 **
**                   initialization is successful or not.                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for other channels                             **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK     : GTM to Port Initialization successful         **
**                   E_NOT_OK : GTM to Port Initialization failed             **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Mcu_lGtmToutSelInitCheck(void)
{
  uint8 ToutSelRegIndex;
  uint32 SfrVal;
  uint32 ConfigVal;
  uint32 CmpVal = 0xFFFFFFFFU;
  Std_ReturnType RetVal = E_NOT_OK;

  /* [cover parentID=][/cover]*/
  for (ToutSelRegIndex = MCU_STARTING_INDEX;
       ToutSelRegIndex < MCU_GTM_NO_OF_TOUTSEL_AVAILABLE; ToutSelRegIndex++)
  {
    SfrVal = MODULE_GTM.TOUTSEL[ToutSelRegIndex].U &
              Mcu_ConfigPtr->McuGtmConfigPtr->GtmToutSelCfgMsk[ToutSelRegIndex];
    ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->GtmToutSelCfg[ToutSelRegIndex];
    CmpVal   &= ~(SfrVal ^ ConfigVal);
  }

  /* [cover parentID={6B86B871-09D3-478c-86DF-8D7EED7A0859}][/cover]*/
  if (CmpVal == 0xFFFFFFFFU)
  {
    RetVal = E_OK;
  }

  return RetVal;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={B70AFE1A-59DD-4ce7-8DA0-C306B3C1A654}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType Mcu_lGtmTimInselInitCheck    **
**                   (void)                                                   **
**                                                                            **
** Description     : This function checks whether Port to GTM TIM             **
**                   initialization is successful or not.                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for other channels                             **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK     : Port to GTM TIM Initialization successful     **
**                   E_NOT_OK : Port to GTM TIM Initialization failed         **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Mcu_lGtmTimInselInitCheck(void)
{
  uint8 TimInSelRegIndex;
  uint32 SfrVal;
  uint32 ConfigVal;
  uint32 CmpVal = 0xFFFFFFFFU;
  Std_ReturnType RetVal = E_NOT_OK;

  for (TimInSelRegIndex = MCU_STARTING_INDEX;
       TimInSelRegIndex < MCU_GTM_NO_OF_TIM_AVAILABLE; TimInSelRegIndex++)
  {
    SfrVal = MODULE_GTM.TIMINSEL[TimInSelRegIndex].U;
    ConfigVal = Mcu_ConfigPtr->McuGtmConfigPtr->GtmTimInSelCfg[TimInSelRegIndex];
    CmpVal   &= ~(SfrVal ^ ConfigVal);
  }

  /* [cover parentID={D1EB08B5-881E-49e2-9396-13B4E66804BC}][/cover]*/
  if (CmpVal == 0xFFFFFFFFU)
  {
    RetVal = E_OK;
  }

  return RetVal;
}
#endif

#if (MCU_INITCHECK_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={C4878123-A713-4867-A83A-A3BEB7CB5C73}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType Mcu_lLpmInitCheck            **
**                   (void)                                                   **
**                                                                            **
** Description     : This function checks whether LPM initialization          **
**                   is successful or not.                                    **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK     : LPM Initialization successful                 **
**                   E_NOT_OK : LPM Initialization failed                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Mcu_lLpmInitCheck(void)
{
  uint32 SfrVal;
  uint32 ConfigVal;
  uint32 CmpVal = 0xFFFFFFFFU;
  Std_ReturnType RetVal = E_NOT_OK;

  /* If low-power standby configuration is available, validate
   * power management for low power mode standby settings.
   */
  /* [cover parentID={6B1DBAD5-FDF5-4974-AC9B-6CC423337912}]
   * Is low power standby configuration available
   * [/cover] */
  if ((Mcu_ConfigPtr->McuLowPowerModeCfgPtr->MaxModeEvrcCtrl.McuMode &
       (uint8)(0x1U << MCU_STANDBY)) > (uint8)0x0U)
  {
    SfrVal    = PMS_PMSWCR0.U;
    ConfigVal = (Mcu_ConfigPtr->McuLowPowerModeCfgPtr->Pmswcr0);
    CmpVal   &= ~(SfrVal ^ ConfigVal);

    SfrVal    = PMS_PMSWCR5.U & MCU_PMSWCR5_INITCHECK_MASK;
    ConfigVal = ((Mcu_ConfigPtr->McuLowPowerModeCfgPtr->Pmswcr5) &
                  MCU_PMSWCR5_INITCHECK_MASK);
    CmpVal   &= ~(SfrVal ^ ConfigVal);

    SfrVal    = PMS_EVRUVMON.U & MCU_PMS_EVRUVMON_MASK;
    ConfigVal = ((Mcu_ConfigPtr->McuLowPowerModeCfgPtr->Evruvmon) &
                  MCU_PMS_EVRUVMON_MASK);
    CmpVal   &= ~(SfrVal ^ ConfigVal);

    SfrVal    = PMS_EVRMONCTRL.U & MCU_PMS_EVRMONCTRL_MASK;
    ConfigVal = ((Mcu_ConfigPtr->McuLowPowerModeCfgPtr->EvrmonCtrl) &
                  MCU_PMS_EVRMONCTRL_MASK);
    CmpVal   &= ~(SfrVal ^ ConfigVal);
  }
  /* [cover parentID={876C5BFA-4EB2-4702-BCC2-9FBFF85A43C0}]
   * Is EVRC sleep mode configuration available
   * [/cover] */
  if ((((uint32)Mcu_ConfigPtr->McuLowPowerModeCfgPtr->MaxModeEvrcCtrl.McuMode) &
       ((uint32)0x1U << MCU_SLEEP)) > 0x0U)
  {
    SfrVal    = (uint32)SCU_PMTRCSR0.B.LPSLPEN;
    ConfigVal = Mcu_ConfigPtr->McuLowPowerModeCfgPtr->
                MaxModeEvrcCtrl.EvrcLowPowerMode;
    CmpVal    &= ~(SfrVal ^ ConfigVal);
  }

  /*[cover parentID={CB921A68-DD52-4e6b-BC74-0C6EE39AC9D3}][/cover]*/
  if (CmpVal == 0xFFFFFFFFU)
  {
    RetVal = E_OK;
  }

  return RetVal;
}
#endif
/* End of #if (MCU_INITCHECK_API == STD_ON)) */

#if (MCU_INIT_CLOCK_API == STD_ON)
#if ((MCU_DEV_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability    : [cover parentID={A586CFB8-18A5-4011-A109-8BDFA1243621}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType Mcu_lInitClockDetCheck       **
**                   (                                                        **
**                     const Mcu_ClockType  ClockSetting                      **
**                   )                                                        **
**                                                                            **
** Description     : This function performs the DET checks related to Init    **
**                   Clock                                                    **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : ClockSetting: Clock setting index                        **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: Clock initialization DET check successful          **
**                   E_NOT_OK: Clock initialization DET check failed          **
**                   e.g. due to parameter error                              **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Mcu_lInitClockDetCheck
(const Mcu_ClockType ClockSetting)
{
  Std_ReturnType RetValue = E_OK;

  /* [cover parentID={A89AA330-B75A-498e-9C9A-99509C6111C7}]
   * If Multicore is ON
   * [/cover] */
  #if ((MCU_MULTICORE_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
  uint32 CoreId = Mcal_GetCpuIndex();

  /* [cover parentID={EDB26605-C0A6-431d-9057-B1074E368237}]
   * Check for DETs */
  if (MCAL_MASTER_COREID != CoreId)
  {
    /* [cover parentID={EC1F64C3-AD07-4d13-8201-CB686AF5FDD1}]
     * Report Error
     * [/cover] */
    Mcu_lReportMultiCoreError(MCU_SID_INITCLOCK, MCU_E_CORE_MISMATCH);
    RetValue = E_NOT_OK;
  }
  else
  #endif
  {
    /* [cover parentID={ACEE8B94-0FC2-4450-904B-F489C7D83224}]
     * Is Mcu Driver not Initialized
     * [/cover] */
    if (Mcu_DriverState != MCU_DRIVER_INITIALIZED)
    {
      /* [cover parentID={51DF0F3D-BDBF-403b-B9AB-B11595396C26}]
      Report Error
      [/cover] */
      /* [cover parentID={5AC910A9-A393-4ed6-96A4-079D785BEBFE}]
       * Report Error
       * [/cover] */
      Mcu_lReportError(MCU_SID_INITCLOCK, MCU_E_UNINIT);
      RetValue = E_NOT_OK;
    }
    else
    {
      /* [cover parentID={DEE18A97-E0F8-404a-8631-60D1C4154F31}]
       * Is Clock setting more than number of clocks configured
       * [/cover] */
      /* [cover parentID={58397EE7-2CEF-4732-9E7E-3A984592010F}]
       * Report Error
       * [/cover] */
      if (ClockSetting >= (Mcu_ConfigPtr->McuNoOfClockCfg))
      {
        Mcu_lReportError(MCU_SID_INITCLOCK, MCU_E_PARAM_CLOCK);
        RetValue = E_NOT_OK;
      }
    }
  }

  return RetValue;
}
#endif
/* End of #if (( MCU_DEV_ERROR_DETECT == STD_ON) || \
                                          (MCU_SAFETY_ENABLE == STD_ON))*/
#endif
/*End of #if(MCU_INIT_CLOCK_API == STD_ON) */
#if (MCU_INIT_CLOCK_API == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID={58FED2AB-82BA-456c-9078-2057F15F889C}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType Mcu_lInitCcuCon12            **
**                   (                                                        **
**                     void                                                   **
**                   )                                                        **
**                                                                            **
** Description     : This function initializes CCUCON1 and CCUCON2            **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: Initialization Successful                          **
**                   E_NOT_OK: Initialization Failed                          **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Mcu_lInitCcuCon12(void)
{
  Std_ReturnType RetValue = E_OK;
  uint32 TimeoutCtr;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
   defined to modify certain bits and avoid 32-bit mask value.
   No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_CCUCON1 Ccucon1Val;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: RAM variable of SFR union type
   defined to modify certain bits and avoid 32-bit mask value.
   No side effects foreseen by violating this MISRA rule.*/
  Ifx_SCU_CCUCON2 Ccucon2Val;

  /* [cover parentID={D224E947-3FFE-43e1-8202-9EE6E7DA60A1}]
   * Provide a delay for Ccucon1 to be unlocked
   * [/cover] */
  TimeoutCtr = MCU_CCUCON12_LCK_TIMEOUT;
  do
  {
    TimeoutCtr--;
    Ccucon1Val.U = SCU_CCUCON1.U;
  } while ((TimeoutCtr > 0x0U) && (0x1U == Ccucon1Val.B.LCK));

  /* [cover parentID={A0A4B920-3720-47fc-BC57-230207EB630E}]
   * Is CCUCON1 still locked after timeout
   * [/cover] */
  if (0x1U == SCU_CCUCON1.B.LCK)
  {
    /* [cover parentID={0463F5D1-08AA-427c-A680-CB9B8876721A}]
     * If Production error Reporting is Enabled [/cover] */
    #if (MCU_E_CCUCON_UPDATE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
    /* [cover parentID={36B40D2E-E451-425e-8BAA-30D557ED4D47}]
     * Report Production error: Event Failed [/cover] */
    Mcu_lReportDemError(MCU_E_CCUCON_UPDATE_ERR,
                          DEM_EVENT_STATUS_FAILED);
    #endif

    RetValue = (Std_ReturnType)E_NOT_OK;
  }
  else
  {
    #if (MCU_E_CCUCON_UPDATE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
    /* [cover parentID={D6A46CB8-1955-4cd1-B6E7-50418C581C42}]
     * Report Production error: Event Passed [/cover] */
    Mcu_lReportDemError(MCU_E_CCUCON_UPDATE_ERR,
                          DEM_EVENT_STATUS_PASSED);
    #endif

    MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_CCUCON1.U,
        (SCU_CCUCON1.U & MCU_CCUCON1_CLKSEL_RST_MASK));
  }

  /* [cover parentID={2AAC8D29-8155-4037-9DE5-BED94ECCBD2E}]
   * Provide a delay for Ccucon2 to be unlocked
   * [/cover] */
  TimeoutCtr = MCU_CCUCON12_LCK_TIMEOUT;
  do
  {
    TimeoutCtr--;
    Ccucon2Val.U = SCU_CCUCON2.U;
  } while ((TimeoutCtr > 0x0U) && (0x1U == Ccucon2Val.B.LCK));

  /* [cover parentID={0DA62FA6-D639-4ff8-82B6-27750409C29C}]
   * Is Ccucon2 still locked after timeout [/cover] */
  if (0x1U == SCU_CCUCON2.B.LCK)
  {
    /* [cover parentID={16741F0F-91BF-4f10-A25F-755C0653468E}]
     * If Production error Reporting is Enabled [/cover] */
    #if (MCU_E_CCUCON_UPDATE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
    /* [cover parentID={673EA2CC-4776-44bb-9854-811CE578383A}]
     * Report Production error: Event Failed [/cover] */
    Mcu_lReportDemError(MCU_E_CCUCON_UPDATE_ERR,
                          DEM_EVENT_STATUS_FAILED);
    #endif

    RetValue = (Std_ReturnType)E_NOT_OK;
  }
  else
  {
    #if (MCU_E_CCUCON_UPDATE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
    /* [cover parentID={2ED3C3F6-A33A-4a2f-A4D7-1B7F68B0881E}]
     * Report Production error: Event Passed [/cover] */
    Mcu_lReportDemError(MCU_E_CCUCON_UPDATE_ERR,
                          DEM_EVENT_STATUS_PASSED);
    #endif

    MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_CCUCON2.U,
        (SCU_CCUCON2.U & MCU_CCUCON2_CLKSEL_RST_MASK));
  }

  /* [cover parentID={71022001-0837-4298-A631-008017761D06}]
   * Provide a delay for Ccucon1 to be unlocked
   * [/cover] */
  TimeoutCtr = MCU_CCUCON12_LCK_TIMEOUT;
  do
  {
    TimeoutCtr--;
    Ccucon1Val.U = SCU_CCUCON1.U;
  } while ((TimeoutCtr > 0x0U) && (0x1U == Ccucon1Val.B.LCK));

  /* [cover parentID={5FC66507-AD79-446d-927B-0B9D997EDFD0}]
   * Is Ccucon1 still locked after timeout [/cover] */
  if (0x1U == SCU_CCUCON1.B.LCK)
  {
    /* [cover parentID={B08F2EA3-4E43-4bdb-99FA-02206284067D}]
     * If Production error Reporting is Enabled [/cover] */
    #if (MCU_E_CCUCON_UPDATE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
    /* [cover parentID={24B8BA0C-D7BB-4dc1-B331-E8630880A3F7}]
     * Report Production error: Event Failed [/cover] */
    Mcu_lReportDemError(MCU_E_CCUCON_UPDATE_ERR,
                          DEM_EVENT_STATUS_FAILED);
    #endif

    RetValue = (Std_ReturnType)E_NOT_OK;
  }
  else
  {
    #if (MCU_E_CCUCON_UPDATE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
    /* [cover parentID={33F32075-7901-433d-A89C-BA45BC502545}]
     * Report Production error: Event Passed [/cover] */
    Mcu_lReportDemError(MCU_E_CCUCON_UPDATE_ERR,
                          DEM_EVENT_STATUS_PASSED);
    #endif

    MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_CCUCON1.U,
        Mcu_ConfigPtr->McuClockSettingPtr
        [Mcu_ClockSetting].PllDistributionCfgPtr->Ccucon1);
  }

  /* [cover parentID={D0E230A6-2539-47ca-987E-71B034CCE958}]
   * Provide a delay for Ccucon2 to be unlocked
   * [/cover] */
  TimeoutCtr = MCU_CCUCON12_LCK_TIMEOUT;
  do
  {
    TimeoutCtr--;
    Ccucon2Val.U = SCU_CCUCON2.U;
  } while ((TimeoutCtr > 0x0U) && (0x1U == Ccucon2Val.B.LCK));

  /* [cover parentID={6604EC7B-1643-4c0c-B2C4-83544D5B6AC3}]
   * Is Ccucon2 still locked after timeout [/cover] */
  if (0x1U == SCU_CCUCON2.B.LCK)
  {
    /* [cover parentID={85C83FC6-1B31-4922-92C2-8C99CB03474A}]
     * If Production error Reporting is Enabled [/cover] */
    #if (MCU_E_CCUCON_UPDATE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
    /* [cover parentID={FF53C723-7862-48b9-9F4E-8F313E89FC16}]
     * Report Production error: Event Failed [/cover] */
    Mcu_lReportDemError(MCU_E_CCUCON_UPDATE_ERR,
                          DEM_EVENT_STATUS_FAILED);
    #endif

    RetValue = (Std_ReturnType)E_NOT_OK;
  }
  else
  {
    #if (MCU_E_CCUCON_UPDATE_ERR_DEM_REPORT == MCU_ENABLE_DEM_REPORT)
    /* [cover parentID={B1306855-C355-49d3-9CD5-15406101B513}]
     * Report Production error: Event Failed [/cover] */
    Mcu_lReportDemError(MCU_E_CCUCON_UPDATE_ERR,
                          DEM_EVENT_STATUS_PASSED);
    #endif

    MCU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&SCU_CCUCON2.U,
        Mcu_ConfigPtr->McuClockSettingPtr
        [Mcu_ClockSetting].PllDistributionCfgPtr->Ccucon2);
  }
  return RetValue;
}
#endif
/*End of #if(MCU_INIT_CLOCK_API == STD_ON) */

/*******************************************************************************
** Traceability    : [cover parentID={164AB092-99D7-4a43-B51F-541EFF2293A2}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType Mcu_lEnableClockControl      **
**                   (                                                        **
**                     void                                                   **
**                   )                                                        **
**                                                                            **
** Description     : This function enables the clock controller for GTM,      **
**                   CCU6, GPT12 and Converter Control                        **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Mcu_lEnableClockControl(void)
{
  Std_ReturnType ClcError = (Std_ReturnType)E_OK;

  /*If GTM module is used, perform global GTM initialization */
  /* [cover parentID={9F4D7805-B21C-469c-BF16-F3B8CAB7D946}]
   * If GTM is Used
   * [/cover] */
  #if (MCU_GTM_USED == STD_ON)
  /* [cover parentID={00C9726D-7D41-41ce-8D8B-045EBE21D878}]
   * Initialize GTM
   * [/cover] */
  /* [cover parentID={63F951D8-4532-46d3-8313-1ED19C0966C2}]
   * Is GTM frequency not zero [/cover] */
  if (SCU_CCUCON0.B.GTMDIV != 0U)
  {
    ClcError = Mcu_lGtmGlobalInit();
  }
  /* [cover parentID={4DA2D268-D41B-48c4-BBF5-673496600744}]
   * Is GTM Initialization Successful
   * [/cover] */
  if (ClcError == (Std_ReturnType)E_OK)
  #endif
  {
    /*[cover parentID={1F88D435-5D0F-445e-9DFB-3328FBB2B75D}][/cover]*/
    #if (MCU_CCU60_USED == STD_ON) || (MCU_CCU61_USED == STD_ON)
    /* [cover parentID={6ADEB234-67B4-47d7-A07A-0C666B6E6783}]
    * Initialize Ccu6
    * [/cover] */
    ClcError = Mcu_lCcu6Init();

    /* [cover parentID={7CA15751-F554-4d8d-8C15-BABE4FA1FBD4}]
     *  Is Ccu6 Initialized successfully
     * [/cover] */
    if (ClcError == (Std_ReturnType)E_OK)
    #endif
    {
      /* [cover parentID={69965050-0C20-49c8-A3BE-E70C2248FE1B}]
       * If GPT12 is Used
       * [/cover] */
      #if ((MCU_GPT1_USED == STD_ON) || (MCU_GPT2_USED == STD_ON))
      /* [cover parentID={F5CB87B6-8481-40bd-8594-78AC858FB446}]
       * Initialize Gpt12
       * [/cover] */
      ClcError = Mcu_lGpt12Init();

      /* [cover parentID={7403A310-52DB-4c6f-849E-B71A0A97A67F}]
       *  Is GPT12 Initialization successful
       * [/cover] */
      if (ClcError == (Std_ReturnType)E_OK)
      #endif
      {
        /*[cover parentID={049503EF-089E-4cdc-93AA-BE7CF76792C0}]
        [/cover]*/
        ClcError = Mcu_lConvCtrlInit();
      }
    }
  }

  return ClcError;
}
#if (MCU_E_ERR_DEM_REPORTING == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    :  [cover parentID={F5BD6EA8-8DEF-4683-BDE3-E798D87FD814}] **
**                                                                            **
** Syntax          : static void Mcu_lReportDemError                          **
**                       (const Dem_EventIdType EventId,                      **
**                        const Dem_EventStatusType ErrorId)                  **
**                                                                            **
** Description     :  This function calls the appropriate Production error    **
**                    handlers.                                               **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Reentrant                                               **
**                                                                            **
** Parameters (in) :  Dem_EventIdType   - DEM Event ID.                       **
**                    Dem_EventStatusType - DEM status ID.                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
static void Mcu_lReportDemError
(
const Dem_EventIdType EventId,
const Dem_EventStatusType EventStatus
)
{
  #if (MCAL_AR_VERSION == MCAL_AR_440)
    (void)Mcal_Wrapper_Dem_SetEventStatus(EventId, EventStatus);
  #else
    Mcal_Wrapper_Dem_ReportErrorStatus(EventId, EventStatus);
  #endif
}
#endif /*End of MCU_ENABLE_DEM_REPORT */
#define MCU_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Mcu_MemMap.h"
