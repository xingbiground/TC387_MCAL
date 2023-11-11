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
**  FILENAME     : Dem_cfg.h                                                  **
**                                                                            **
**  VERSION      : 4.0.0                                                     **
**                                                                            **
**  DATE         : 2023-05-31                                                **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Stub file for Dem Module - To be Replaced by user          **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
#ifndef _DEM_CFG_H
#define _DEM_CFG_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
#if ((defined(APP_SW)) && ((APP_SW == TEST_APP) || (APP_SW == DEMO_APP)))
/* Assignment of Event Id values for the Symbols */

#define DemConf_DemEventParameter_FEE_E_GC_INIT                     (1U)
#define DemConf_DemEventParameter_FEE_E_WRITE                       (2U)
#define DemConf_DemEventParameter_FEE_E_READ                        (3U)
#define DemConf_DemEventParameter_FEE_E_GC_WRITE                    (4U)
#define DemConf_DemEventParameter_FEE_E_GC_READ                     (5U)
#define DemConf_DemEventParameter_FEE_E_GC_ERASE                    (6U)
#define DemConf_DemEventParameter_FEE_E_INVALIDATE                  (7U)
#define DemConf_DemEventParameter_FEE_E_WRITE_CYCLES_EXHAUSTED      (8U)
#define DemConf_DemEventParameter_FEE_E_GC_TRIG                     (9U)
#define DemConf_DemEventParameter_FEE_E_UNCONFIG_BLK_EXCEEDED       (10U)

#define DemConf_DemEventParameter_FR_CTRL_TESTRESULT_ERROR          (15U)
#define DemConf_DemEventParameter_FR_CTRL_TIMEOUT_ERROR             (16U)

#define DemConf_DemEventParameter_CAN_TIMEOUT_ERROR                 (17U)

#define DemConf_DemEventParameter_MCU_E_OSC_FAILURE                 (25U)
#define DemConf_DemEventParameter_MCU_E_SYSTEM_PLL_TIMEOUT_ERR      (26U)
#define DemConf_DemEventParameter_MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR  (27U)
#define DemConf_DemEventParameter_MCU_E_SYSTEM_PLL_LOCK_LOSS        (28U)
#define DemConf_DemEventParameter_MCU_E_PERIPHERAL_PLL_LOCK_LOSS    (29U)
#define DemConf_DemEventParameter_MCU_E_GTM_CLC_ENABLE_ERR          (30U)
#define DemConf_DemEventParameter_MCU_E_GTM_CLC_DISABLE_ERR         (31U)
#define DemConf_DemEventParameter_MCU_E_CONVCTRL_CLC_ENABLE_ERR     (32U)
#define DemConf_DemEventParameter_MCU_E_CONVCTRL_CLC_DISABLE_ERR    (33U)
#define DemConf_DemEventParameter_MCU_E_CCUCON_UPDATE_ERR           (34U)
#define DemConf_DemEventParameter_MCU_E_CCU6_CLC_ENABLE_ERR         (35U)
#define DemConf_DemEventParameter_MCU_E_CCU6_CLC_DISABLE_ERR        (36U)
#define DemConf_DemEventParameter_MCU_E_GPT12_CLC_ENABLE_ERR        (37U)
#define DemConf_DemEventParameter_MCU_E_GPT12_CLC_DISABLE_ERR       (38U)
#define DemConf_DemEventParameter_MCU_E_PMSWCR_UPDATE_ERR           (39U)

#define DemConf_DemEventParameter_SMU_E_ACTIVATE_FSP_FAILURE        (44U)
#define DemConf_DemEventParameter_SMU_E_ACTIVATE_PES_FAILURE        (45U)
#define DemConf_DemEventParameter_SMU_E_ACTIVATE_RUN_STATE_FAILURE  (46U)
#define DemConf_DemEventParameter_SMU_E_CLEAR_ALARM_STATUS_FAILURE  (47U)
#define DemConf_DemEventParameter_SMU_E_RELEASE_FSP_FAILURE         (48U)
#define DemConf_DemEventParameter_SMU_E_RT_STOP_FAILURE             (49U)
#define DemConf_DemEventParameter_SMU_E_SET_ALARM_STATUS_FAILURE    (51U)
#define DemConf_DemEventParameter_SMU_E_SFF_FAILURE                 (52U)
#define DemConf_DemEventParameter_SMU_E_CORE_ALIVE_FAILURE          (53U)

#define DemConf_DemEventParameter_Fr_17_EraySlotStatusErr_Lpdu0     (55U)
#define DemConf_DemEventParameter_Fr_17_EraySlotStatusErr_Lpdu1     (56U)
#define DemConf_DemEventParameter_Fr_17_EraySlotStatusErr_Lpdu2     (57U)
#define DemConf_DemEventParameter_Fr_17_ErayCtrlTestResult_Ctrl0    (58U)
#define DemConf_DemEventParameter_Fr_17_ErayCtrlTimout_Ctrl0        (59U)

#define DemConf_DemEventParameter_ADC_E_CLC_ERR                     (60U)
#define DemConf_DemEventParameter_ADC_E_STOP_CONV_FAIL              (61U)

#define DemConf_DemEventParameter_ETH_E_ACCESS                      (62U)
#define DemConf_DemEventParameter_ETH_E_TIMEOUT                     (63U)
#define DemConf_DemEventParameter_ETH_E_FRAMESEQ                    (64U)
#define DemConf_DemEventParameter_ETH_E_RX_FRAMESLOST               (65U)
#define DemConf_DemEventParameter_ETH_E_ALIGNMENT                   (66U)
#define DemConf_DemEventParameter_ETH_E_CRC                         (67U)
#define DemConf_DemEventParameter_ETH_E_SINGLECOLLISION             (68U)
#define DemConf_DemEventParameter_ETH_E_MULTIPLECOLLISION           (69U)
#define DemConf_DemEventParameter_ETH_E_LATECOLLISION               (70U)
#define DemConf_DemEventParameter_ETH_E_UNDERSIZEFRAME              (71U)
#define DemConf_DemEventParameter_ETH_E_OVERSIZEFRAME               (72U)

#define DemConf_DemEventParameter_WDG_E_MODE_FAILED                 (73U)
#define DemConf_DemEventParameter_WDG_E_DISABLE_REJECTED            (74U)
#define DemConf_DemEventParameter_WDG_E_ACCESS_FAILED               (75U)
#define DemConf_DemEventParameter_WDG_E_OVERFLOW_FAILED             (76U)
#define DemConf_DemEventParameter_SPI_E_HARDWARE_ERROR              (77U)

#define DemConf_DemEventParameter_DSADC_E_CLC_FAILURE               (78U)
#define DemConf_DemEventParameter_DSADC_E_FIFO_FAILURE              (79U)
#define DemConf_DemEventParameter_IOM_E_CLC_ENABLE_ERR              (80U)

#define DemConf_DemEventParameter_LIN_E_TIMEOUT                     (86U)

#define DemConf_DemEventParameter_STM_E_CLC_ENABLE_ERR              (87U)

/* Add DEM IDs for all modules sequentially */
#else /* (defined(APP_SW)) && ((APP_SW == TEST_APP) || (APP_SW == DEMO_APP)) */
/* Assignment of Event Id values for the Symbols */
#define DemConf_DemEventParameter_ADC_E_CLC_ERR                     (60U)
#define DemConf_DemEventParameter_AdcClc                            (0U)
#define DemConf_DemEventParameter_AdcStopConvFail                   (1U)
#define DemConf_DemEventParameter_ADC_CLC                           (5U)
#define DemConf_DemEventParameter_SOME_OTHER                        (6U)

#define DemConf_DemEventParameter_DemEventParameter_0               (7U)
#define DemConf_DemEventParameter_DemEventParameter_1               (8U)
#define DemConf_DemEventParameter_DemEventParameter_2               (9U)
#define DemConf_DemEventParameter_DemEventParameter_3               (10U)
#define DemConf_DemEventParameter_DemEventParameter_4               (11U)
#define DemConf_DemEventParameter_DemEventParameter_5               (12U)
#define DemConf_DemEventParameter_DemEventParameter_6               (13U)
#define DemConf_DemEventParameter_DemEventParameter_7               (14U)
#define DemConf_DemEventParameter_DemEventParameter_8               (15U)
#define DemConf_DemEventParameter_FR_CTRL_TESTRESULT_ERROR          (15U)
#define DemConf_DemEventParameter_Fr_17_EraySlotStatusErr_Lpdu0     (7U)
#define DemConf_DemEventParameter_Fr_17_EraySlotStatusErr_Lpdu1     (8U)
#define DemConf_DemEventParameter_Fr_17_ErayCtrlTestResult_Ctrl0    (9U)
#define DemConf_DemEventParameter_Fr_17_ErayCtrlTimout_Ctrl0        (10U)
#define DemConf_DemEventParameter_MSC_E_CLC_FAILURE                 (18U)
#define DemConf_DemEventParameter_MSC_E_KRST_FAILURE                (19U)
/* Add DEM IDs for all modules sequentially */

/*Fee DEMs*/
#define DemConf_DemEventParameter_FEE_E_GC_INIT                     (16U)
#define DemConf_DemEventParameter_FEE_E_WRITE                       (17U)
#define DemConf_DemEventParameter_FEE_E_READ                        (18U)
#define DemConf_DemEventParameter_FEE_E_GC_WRITE                    (19U)
#define DemConf_DemEventParameter_FEE_E_GC_READ                     (20U)
#define DemConf_DemEventParameter_FEE_E_GC_ERASE                    (21U)
#define DemConf_DemEventParameter_FEE_E_INVALIDATE                  (22U)
#define DemConf_DemEventParameter_FEE_E_WRITE_CYCLES_EXHAUSTED      (23U)
#define DemConf_DemEventParameter_FEE_E_GC_TRIG                     (24U)
#define DemConf_DemEventParameter_FEE_E_UNCONFIG_BLK_EXCEEDED       (25U)

#define DemConf_DemEventParameter_MCU_E_SYSTEM_PLL_TIMEOUT_ERR      (26U)
#define DemConf_DemEventParameter_MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR  (27U)
#define DemConf_DemEventParameter_MCU_E_SYSTEM_PLL_LOCK_LOSS        (28U)
#define DemConf_DemEventParameter_MCU_E_PERIPHERAL_PLL_LOCK_LOSS    (29U)
#define DemConf_DemEventParameter_MCU_E_GTM_CLC_ENABLE_ERR          (30U)
#define DemConf_DemEventParameter_MCU_E_GTM_CLC_DISABLE_ERR         (31U)
#define DemConf_DemEventParameter_MCU_E_CONVCTRL_CLC_ENABLE_ERR     (32U)
#define DemConf_DemEventParameter_MCU_E_CONVCTRL_CLC_DISABLE_ERR    (33U)
#define DemConf_DemEventParameter_MCU_E_CCUCON_UPDATE_ERR           (34U)
#define DemConf_DemEventParameter_MCU_E_CCU6_CLC_ENABLE_ERR         (35U)
#define DemConf_DemEventParameter_MCU_E_CCU6_CLC_DISABLE_ERR        (36U)
#define DemConf_DemEventParameter_MCU_E_GPT12_CLC_ENABLE_ERR        (37U)
#define DemConf_DemEventParameter_MCU_E_GPT12_CLC_DISABLE_ERR       (38U)
#define DemConf_DemEventParameter_MCU_E_PMSWCR_UPDATE_ERR           (39U)
#define DemConf_DemEventParameter_MCU_E_OSC_FAILURE                 (40U)

#define DemConf_DemEventParameter_ETH_E_ACCESS                      (53U)
#define DemConf_DemEventParameter_ETH_E_TIMEOUT                     (54U)
#define DemConf_DemEventParameter_ETH_E_FRAMESEQ                    (55U)
#define DemConf_DemEventParameter_ETH_E_RX_FRAMESLOST               (56U)
#define DemConf_DemEventParameter_ETH_E_ALIGNMENT                   (57U)
#define DemConf_DemEventParameter_ETH_E_CRC                         (58U)
#define DemConf_DemEventParameter_ETH_E_SINGLECOLLISION             (59U)
#define DemConf_DemEventParameter_ETH_E_MULTIPLECOLLISION           (60U)
#define DemConf_DemEventParameter_ETH_E_LATECOLLISION               (61U)
#define DemConf_DemEventParameter_ETH_E_UNDERSIZEFRAME              (62U)
#define DemConf_DemEventParameter_ETH_E_OVERSIZEFRAME               (63U)

#define DemConf_DemEventParameter_WDG_E_MODE_FAILED                 (64U)
#define DemConf_DemEventParameter_WDG_E_DISABLE_REJECTED            (65U)
#define DemConf_DemEventParameter_WDG_E_ACCESS_FAILED               (66U)
#define DemConf_DemEventParameter_WDG_E_OVERFLOW_FAILED             (67U)

#define DemConf_DemEventParameter_SMU_E_ACTIVATE_FSP_FAILURE        (44U)
#define DemConf_DemEventParameter_SMU_E_ACTIVATE_PES_FAILURE        (45U)
#define DemConf_DemEventParameter_SMU_E_ACTIVATE_RUN_STATE_FAILURE  (46U)
#define DemConf_DemEventParameter_SMU_E_CLEAR_ALARM_STATUS_FAILURE  (47U)
#define DemConf_DemEventParameter_SMU_E_RELEASE_FSP_FAILURE         (48U)
#define DemConf_DemEventParameter_SMU_E_RT_STOP_FAILURE             (49U)
#define DemConf_DemEventParameter_SMU_E_SET_ALARM_STATUS_FAILURE    (51U)
#define DemConf_DemEventParameter_SMU_E_SFF_FAILURE                 (52U)

#define DemConf_DemEventParameter_SPI_E_HARDWARE_ERROR              (77U)

#define DemConf_DemEventParameter_DSADC_E_CLC_FAILURE               (78U)
#define DemConf_DemEventParameter_DSADC_E_FIFO_FAILURE              (79U)

#define DemConf_DemEventParameter_LIN_E_TIMEOUT                     (86U)

#endif /* ((APP_SW == TEST_APP) || (APP_SW == DEMO_APP)) */

#endif /* end of _DEM_CFG_H */

