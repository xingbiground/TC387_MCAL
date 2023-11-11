/*****************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2022)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Adc_PBcfg.c                                                   **
**                                                                            **
**  VERSION   : 14.0.0                                                         **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:35            !!!IGNORE-LINE!!!             **
**                                                                            **
**  GENERATOR : Build b191017-0938              !!!IGNORE-LINE!!!             **
**                                                                            **
**  BSW MODULE DECRIPTION : Adc.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION :  Adc configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of ADC Driver,                           **
**                     AUTOSAR Release 4.2.2 and 4.4.0                        **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Inclusion of module header file */
#include "Adc.h"

/***********Global configuration of EMUX feature***********/

/***********Configuration for External HW trigger and gating signals***********/
/*Gtm Trigger Configuration for AdcHWGroup of HW Unit 0 */
/* MISRA2012_RULE_5_1_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/

#define ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"
static const Mcu_17_Gtm_TomAtomChConfigType Adc_kHwUnit0GrpAdcHWGroupGtmTrig_Config=
{
  MCU_GTM_TIMER_TOM, /*GTM_TOM Timer Type Used*/
  0x00000006U, /* Timer ID */
  0x00001800U, /*Control Register Value for GTM_TOM_0 */
  0x00000000U, /*CN0 Register value*/
  0x0000f424U, /*CM0 register value*/
  0x00007a12U, /*CM1 register value*/
  0x0000f424U, /*SR0 register value*/
  0x00007a12U, /*SR1 register value*/
  0x00U /*Interrupt Enable and Interrupt Mode values*/
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/

#define ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"

/*******************Group Definition - Channel Sequence*******************/
/* MISRA2012_RULE_5_1_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/

#define ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"
/**Group Definition of AdcSWGroup- ID0 of HW Unit 0 */
static const Adc_GroupDefType Adc_kHwUnit0GrpAdcSWGroup_Config[2]=
{
  /*AS Logical Channel*/ /*Analog Channel*/ /*Result Register*/ /*Channel Diagnostic Data*/
        {  0U,                   5U,                0U,                0x00000000U},
        {  1U,                   4U,                1U,                0x00000000U}
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/

#define ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"
/* MISRA2012_RULE_5_1_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/

#define ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"
/**Group Definition of AdcHWGroup- ID1 of HW Unit 0 */
static const Adc_GroupDefType Adc_kHwUnit0GrpAdcHWGroup_Config[2]=
{
  /*AS Logical Channel*/ /*Analog Channel*/ /*Result Register*/ /*Channel Diagnostic Data*/
        {  0U,                   5U,                0U,                0x00000000U},
        {  1U,                   4U,                1U,                0x00000000U}
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/

#define ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"

/***********************Group Configuration Definition***********************/
/* MISRA2012_RULE_5_1_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/ 

#define ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"

/*****Group Configuration Definition of HW Unit 0 ******/
static const Adc_GroupCfgType Adc_kHwUnit0Grp_Config[2]=
{

  {/*Group Configuration structure for AdcSWGroup - ID0*/
    /*
      Group Properties:
      Trigger Source: ADC_TRIGG_SRC_SW
      Trigger Edge: 
      HW Trigger Source: ADC_TRIG_NONE
      HW Gate Source: ADC_GATE_NONE
      Gate Level: ADC_GATE_LVL_HIGH
    */
    /* Notification Function Address */
    (Adc_NotifyFnPtrType)0U,
    /*Address for Group Definition Structure*/
    &Adc_kHwUnit0GrpAdcSWGroup_Config[0U],
    /*Address for the GTM trigger configuration structure*/
    (const Mcu_17_Gtm_TomAtomChConfigType *)0U,
    /*Address for the GTM gate configuration structure*/
    (const Mcu_17_Gtm_TomAtomChConfigType *)0U,
    /*Address for the ERU trigger configuration structure*/
    (const Adc_EruChannelCfgType *)0U,
    /*Address for the ERU gate configuration structure*/
    (const Adc_EruChannelCfgType *)0U,
    /*Configuration value for the G0QCTRL register*/
    0x00000000U,
    /*Configuration value for the G0QMR register*/
    0x00000001U,
    /*Configuration value for the G0ALIAS register*/
    0x00000100U,
    /* Configuration value for G0REQTM register*/
    0x00000000U,
    /*Bit Mask for all the analog channels configured for the group*/
    0x0030U,
    /*Bit Mask for all the result registers configured for the group*/
    0x0003U,
    /*Bit Mask for all the analog channels configured for synchronous conversion*/
    0x0000U,
    /*Bit Mask for all the result registers configured for synchronous conversion*/
    0x0000U,
    ADC_TRIGG_SRC_SW,
    ADC_CONV_MODE_CONTINUOUS,
    ADC_ACCESS_MODE_STREAMING,
    ADC_STREAM_BUFFER_LINEAR,
    5U, /*Number of streaming samples for the group*/
    ADC_OTHER_HW_USED, /*HW peripheral used for Trigger*/
    ADC_OTHER_HW_USED, /*HW peripheral used for Gate*/
    0U, /*Priority Level for the group*/
    2U, /*Channel Count for the group*/
    0U, /*Limit Check enabled for the group*/
    0x00U, /* EMUX configuration of the Group */
    0U /* Diagnostic channels configured for the Group */
  },

  {/*Group Configuration structure for AdcHWGroup - ID1*/
    /*
      Group Properties:
      Trigger Source: ADC_TRIGG_SRC_HW
      Trigger Edge: ADC_HW_TRIG_RISING_EDGE
      HW Trigger Source: ADC_TRIG_8_GxREQTRI_GTM_ADCx_TRIG0
      HW Gate Source: ADC_GATE_NONE
      Gate Level: ADC_GATE_LVL_HIGH
    */
    /* Notification Function Address */
    (Adc_NotifyFnPtrType)0U,
    /*Address for Group Definition Structure*/
    &Adc_kHwUnit0GrpAdcHWGroup_Config[0U],
    /*Address for the GTM trigger configuration structure*/
    (const Mcu_17_Gtm_TomAtomChConfigType *)&Adc_kHwUnit0GrpAdcHWGroupGtmTrig_Config,
    /*Address for the GTM gate configuration structure*/
    (const Mcu_17_Gtm_TomAtomChConfigType *)0U,
    /*Address for the ERU trigger configuration structure*/
    (const Adc_EruChannelCfgType *)0U,
    /*Address for the ERU gate configuration structure*/
    (const Adc_EruChannelCfgType *)0U,
    /*Configuration value for the G0QCTRL register*/
    0x00004800U,
    /*Configuration value for the G0QMR register*/
    0x00000005U,
    /*Configuration value for the G0ALIAS register*/
    0x00000100U,
    /* Configuration value for G0REQTM register*/
    0x00000000U,
    /*Bit Mask for all the analog channels configured for the group*/
    0x0030U,
    /*Bit Mask for all the result registers configured for the group*/
    0x0003U,
    /*Bit Mask for all the analog channels configured for synchronous conversion*/
    0x0000U,
    /*Bit Mask for all the result registers configured for synchronous conversion*/
    0x0000U,
    ADC_TRIGG_SRC_HW,
    ADC_CONV_MODE_ONESHOT,
    ADC_ACCESS_MODE_STREAMING,
    ADC_STREAM_BUFFER_LINEAR,
    5U, /*Number of streaming samples for the group*/
    ADC_GTM_HW_USED, /*HW peripheral used for Trigger*/
    ADC_OTHER_HW_USED, /*HW peripheral used for Gate*/
    0U, /*Priority Level for the group*/
    2U, /*Channel Count for the group*/
    0U, /*Limit Check enabled for the group*/
    0x00U, /* EMUX configuration of the Group */
    0U /* Diagnostic channels configured for the Group */
  }
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/

#define ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"


/***********************Channel Configuration Definition***********************/
/*****Channel Configuration Definition of HW Unit 0 *****/
/* MISRA2012_RULE_5_1_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/

#define ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"
static const Adc_ChannelCfgType Adc_kHwUnit0Ch_Config[2]=
{

  {
    0x00000000U, /*Configuration value for the G0CHCTR5 register*/
    0x00000000U, /*Configuration value for the G0BOUND register*/
    5U, /*Analog Channel number for the corresponding Logical Channel*/
    0U /*Limit Check channel or not */
  },

  {
    0x00000000U, /*Configuration value for the G0CHCTR4 register*/
    0x00000000U, /*Configuration value for the G0BOUND register*/
    4U, /*Analog Channel number for the corresponding Logical Channel*/
    0U /*Limit Check channel or not */
  }
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
#define ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"

/********************HW Unit Converter Configurations********************/

/**HW Unit 0 Converter Configurations **/
/* MISRA2012_RULE_5_1_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
#define ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"
static const Adc_HwCfgType Adc_kHwUnit0Hw_Config=
{
  0x00300004U, /*Configuration value for G0ANCFG register*/
  0x00000003U, /*Configuration value for G0ARBCFG register*/
  0x01000000U, /*Configuration value for G0ARBPR register*/
  0x00000000U, /*Configuration value for G0ICLASS0 register*/
  0x00000000U, /*Configuration value for G0ICLASS1 register*/
  0x00000000U /*Configuration value for G0SYNCTR register*/
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
#define ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"


/***************************HW Unit Configuration ***************************/

/*************HW Unit 0 Configuration **************/
/* MISRA2012_RULE_5_1_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
   #define ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"
static const Adc_HwUnitCfgType Adc_kHwUnit0_Config=
{
  &Adc_kHwUnit0Hw_Config, /*Analog Converter Configuration*/
  &Adc_kHwUnit0Ch_Config[0U], /*Channel Configuration structure*/
  &Adc_kHwUnit0Grp_Config[0U], /*Group Configuration structure*/
  0x00000001U, /* Mask for SW triggered groups*/
  0x00000002U,/* Mask for HW triggered groups*/
  ADC_SYNC_CONV_MODE_NONE, /* Synchronous conversion mode */
  { 0xffU, 0xffU, 0xffU }, /* Slave Kernels */
  2U, /* Group Count for HW Unit 0*/
  1U /* Bit Mask for SRNs used for HW Unit 0*/
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
#define ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"


/* MISRA2012_RULE_5_1_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/

#define ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"
/******************Global Configuration*******************/

static const Adc_GlobalCfgType Adc_kGlob_Config=
{
  0x00000000U, /*Configuration value for GLOBCFG register */
  0x00000000U, /*Configuration value for GLOBICLASS0 register */
  0x00000000U, /*Configuration value for GLOBICLASS1 register */
  0x00000000U /*Configuration value for EMUXSEL register */
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/

#define ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"


/***************************Core Configuration ***************************/
/*******Core0 Configuration*******/
/* MISRA2012_RULE_5_1_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/

#define ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"
static const Adc_CoreConfigType Adc_kCore0_Config=
{
  {
    &Adc_kHwUnit0_Config, /* HW Unit 1 Configuration */
    (Adc_HwUnitCfgType*)0U, /* HW Unit 2 Configuration */
    (Adc_HwUnitCfgType*)0U, /* HW Unit 3 Configuration */
    (Adc_HwUnitCfgType*)0U, /* HW Unit 4 Configuration */
    (Adc_HwUnitCfgType*)0U, /* HW Unit 5 Configuration */
    (Adc_HwUnitCfgType*)0U, /* HW Unit 6 Configuration */
    (Adc_HwUnitCfgType*)0U, /* HW Unit 7 Configuration */
    (Adc_HwUnitCfgType*)0U, /* HW Unit 8 Configuration */
    (Adc_HwUnitCfgType*)0U, /* HW Unit 9 Configuration */
    (Adc_HwUnitCfgType*)0U, /* HW Unit 10 Configuration */
    (Adc_HwUnitCfgType*)0U, /* HW Unit 11 Configuration */
    (Adc_HwUnitCfgType*)0U /* HW Unit 12 Configuration */
  }
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Memmap macros are defined as per Autosar
   naming convention, hence it goes beyond 32 characters.*/

#define ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"
  

/*******Configuration Root*******/ 
#define ADC_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"

const Adc_ConfigType Adc_Config=
{
  &Adc_kGlob_Config, /* Global Configuration */
  {
    &Adc_kCore0_Config, /* Core0 Configuration */
    (const Adc_CoreConfigType*)0U, /* Core1 Configuration */
    (const Adc_CoreConfigType*)0U, /* Core2 Configuration */
    (const Adc_CoreConfigType*)0U /* Core3 Configuration */
  }
};


#define ADC_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"


