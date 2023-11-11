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
**  FILENAME  : Mcu_PBcfg.c                                                   **
**                                                                            **
**  VERSION   : 33.0.0                                                        **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:31       !!!IGNORE-LINE!!!                  **
**                                                                            **
**  GENERATOR : Build b191017-0938           !!!IGNORE-LINE!!!                **
**                                                                            **
**  BSW MODULE DECRIPTION : Mcu.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Mcu configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Mcu Driver, AUTOSAR Release 4.2.2     **
**                     and 4.4.0                                              **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                       Includes                                             **
*******************************************************************************/
/* Include module header file */
#include "Mcu.h"
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
#define MCU_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Mcu_MemMap.h"

/*
  PLL Distribution configuration structure(s)
  for each clock setting configurations
*/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
static const Mcu_PllDistributionConfigType Mcu_kPllDistributionConfiguration_Config_0 =
{
  /* CCUCON0 value */
  0x17230133U,
  /* CCUCON1 value */
  0x22000294U,
  /* CCUCON2 value */
  0x07001802U,
  /* CCUCON5 value */
  0x00000032U,
  /* CCUCON6...CCUCON9 value */
  {
    0x00000000U,
    0x00000000U,
    0x00000000U,
    0x00000000U
  }
};
/*
   Configuration : Mcu_ConfigType
   For Mcu_ConfigType: MCU specific configuration ID
   This id corresponds to the container name of the McuConfiguration.
   Use this as the parameter for API: Mcu_Init
   Container: McuClockSettingConfig
   Multilplicity : 1 - *
*/
static const Mcu_ClockConfigType Mcu_kClockConfiguration_Config[1] =
{
  /*McuClockSettingConfig_0*/
  {
    /* System PLL configuration value */
    {
      1U,
      0U,
      29U,
      1U,
      0U,
      0U
    },
    /* Peripheral PLL configuration value */
    {
      31U,
      0U,
      3U,
      1U,
      0U,
      0U
    },
    /* System PLL K2 divider increment step change delay */
    10U,
    /* System PLL K2 divider decrement step change delay */
    10U,
    /* Peripheral PLL K2 divider step change increment */
    10U,
    /* Peripheral PLL K2 divider step change decrement */
    10U,
    /* Peripheral PLL K3 divider step change increment */
    10U,
    /* Peripheral PLL K3 divider step change decrement */
    10U,
    /* PLL clock divider configuration pointer */
    &Mcu_kPllDistributionConfiguration_Config_0,
    /* External Clock configuration */
    0x00000000U,
    /* Backup frequency K Divider value for both PLLs */
    0x0355U,
    /* Converter Control Phase Synchronization configuration */
    0x00U,
  },/*McuClockReferencePointConfig*/
};
/*
  Ptr to RAM Section in config structure
  Container: McuRamSectorSettingConf
  Multiplicity: 1 - *
  Configuration: RAM Section Id
  This id corresponds to the container name of the McuRAMSettingConfiguration.
  Use this as the parameter for API: Mcu_InitRamSection
*/

/*
  Standby Mode config structure for Low Power (Standby) Mode Configuration:
  
*/
static const Mcu_LowPowerModeType  Mcu_kLowPowerModeConfiguration_Config =
{
  /*MaxModeEvrcCtrl value*/
  {
    0x1U,
    0x0U,
    0U
  },
  /* PMSWCR0 Register value */
  0x00000000U,
  /* PMSWCR3Value  */
  0x00000000U,
  /* PMSWCR4Value  */
  0x00000000U,
  /* PMSWCR5Value  */
  0x00000000U,
  /* EVRUVMONValue  */
  0x00000000U,
  /* EVRMONCTRLValue  */
  0x00000000U
};
/*Generate configuration structure for GTM Clock config*/
                                    static const Mcu_GtmClockSettingType Mcu_kGtmClockConfigPtr_Config =
{
  /*CMU config clock, external and fixed clock enable - GtmCmuClockEnable*/
  0x0080aaaaU,
  /*CMU global clock numerator - GtmCmuGlobalNumerator*/
  0x00000001U,
  /*CMU global clock denominator - GtmCmuGlobalDenominator*/
  0x00000001U,

  /*CMU config clock_0...7 Numerator and Denominator - GtmCmuConfClkCtrl*/
  {
    0x00000000U,
    0x00000000U,
    0x00000000U,
    0x00000000U,
    0x00000000U,
    0x00000000U,
    0x00000000U,
    0x00000000U
  },

  /*CMU fixed clock Divider selection - GtmCmuFixedClkCtrl*/
    0x00000000U,

  /*GTM cluster input clock divider configuration - GtmCmuClusterInputClockDividerEnable */
  0x0002aaaaU,

  /* External clock settings - GtmEclkCtrl*/
  {
    /*External Clock_0 disabled - reset value of numerator and denominator*/
    {1U, 1U},
    /*External Clock_1 disabled - reset value of numerator and denominator*/
    {1U, 1U},
    /*External Clock_2 disabled - reset value of numerator and denominator*/
    {1U, 1U}
  }
};
/*Generate configuration structure for GTM cluster config*/
static const Mcu_GtmClusterConfigType Mcu_kGtmClusterConfigPtr_Config[9] =
{
            
  /*GTM Cluster_0 configuration*/
  {
    /*GTM cluster TIM/TOM/ATOM enable settings*/
    0x00000006U,
    /*GTM cluster config clock settings*/
    0x00000000U,
    /*GTM cluster fixed clock settings*/
    0x00000000U
  },            
  /*GTM Cluster_1 configuration*/
  {
    /*GTM cluster TIM/TOM/ATOM enable settings*/
    0x00000000U,
    /*GTM cluster config clock settings*/
    0x00000000U,
    /*GTM cluster fixed clock settings*/
    0x00000000U
  },            
  /*GTM Cluster_2 configuration*/
  {
    /*GTM cluster TIM/TOM/ATOM enable settings*/
    0x00000000U,
    /*GTM cluster config clock settings*/
    0x00000000U,
    /*GTM cluster fixed clock settings*/
    0x00000000U
  },            
  /*GTM Cluster_3 configuration*/
  {
    /*GTM cluster TIM/TOM/ATOM enable settings*/
    0x00000000U,
    /*GTM cluster config clock settings*/
    0x00000000U,
    /*GTM cluster fixed clock settings*/
    0x00000000U
  },            
  /*GTM Cluster_4 configuration*/
  {
    /*GTM cluster TIM/TOM/ATOM enable settings*/
    0x00000000U,
    /*GTM cluster config clock settings*/
    0x00000000U,
    /*GTM cluster fixed clock settings*/
    0x00000000U
  },            
  /*GTM Cluster_5 configuration*/
  {
    /*GTM cluster TIM/TOM/ATOM enable settings*/
    0x00000000U,
    /*GTM cluster config clock settings*/
    0x00000000U,
    /*GTM cluster fixed clock settings*/
    0x00000000U
  },            
  /*GTM Cluster_6 configuration*/
  {
    /*GTM cluster TIM/TOM/ATOM enable settings*/
    0x00000000U,
    /*GTM cluster config clock settings*/
    0x00000000U,
    /*GTM cluster fixed clock settings*/
    0x00000000U
  },            
  /*GTM Cluster_7 configuration*/
  {
    /*GTM cluster TIM/TOM/ATOM enable settings*/
    0x00000000U,
    /*GTM cluster config clock settings*/
    0x00000000U,
    /*GTM cluster fixed clock settings*/
    0x00000000U
  },            
  /*GTM Cluster_8 configuration*/
  {
    /*GTM cluster TIM/TOM/ATOM enable settings*/
    0x00000000U,
    /*GTM cluster config clock settings*/
    0x00000000U,
    /*GTM cluster fixed clock settings*/
    0x00000000U
  }
};

/*
 Gtm Configuration structure for module
  Container: Mcu_kGtmConfiguration
  Multiplicity: 1 - *
*/
static const Mcu_GtmConfigType Mcu_kGtmConfiguration_Config =
{
  /* Ptr to GTM clock configuration -  GtmClockCfgPtr */
  &Mcu_kGtmClockConfigPtr_Config,
  /* Ptr to GTM cluster configuration -  GtmClusterCfgPtr */
  Mcu_kGtmClusterConfigPtr_Config,
  /*Configuration for TOM global settings*/
  {
    /*Configuration for Tom global settings -  GtmTomCfg*/
        /*GtmTomGlobalConf_0*/
        {
          /*TomTgcIntTrigRstCn0 value for group0*/
          0x55555555U,
          /*TomTgcActTb value for group0*/
          0x00000001U
        },
        {
          /*TomTgcIntTrigRstCn1 value for group1*/
          0x55555555U,
          /*TomTgcActTb value for group1*/
          0x00000001U
        },        /*GtmTomGlobalConf_1*/
        {
          /*TomTgcIntTrigRstCn0 value for group0*/
          0x55555555U,
          /*TomTgcActTb value for group0*/
          0x00000001U
        },
        {
          /*TomTgcIntTrigRstCn1 value for group1*/
          0x55555555U,
          /*TomTgcActTb value for group1*/
          0x00000001U
        },        /*GtmTomGlobalConf_2*/
        {
          /*TomTgcIntTrigRstCn0 value for group0*/
          0x55555555U,
          /*TomTgcActTb value for group0*/
          0x00000001U
        },
        {
          /*TomTgcIntTrigRstCn1 value for group1*/
          0x55555555U,
          /*TomTgcActTb value for group1*/
          0x00000001U
        },        /*GtmTomGlobalConf_3*/
        {
          /*TomTgcIntTrigRstCn0 value for group0*/
          0x55555555U,
          /*TomTgcActTb value for group0*/
          0x00000001U
        },
        {
          /*TomTgcIntTrigRstCn1 value for group1*/
          0x55555555U,
          /*TomTgcActTb value for group1*/
          0x00000001U
        },        /*GtmTomGlobalConf_4*/
        {
          /*TomTgcIntTrigRstCn0 value for group0*/
          0x55555555U,
          /*TomTgcActTb value for group0*/
          0x00000001U
        },
        {
          /*TomTgcIntTrigRstCn1 value for group1*/
          0x55555555U,
          /*TomTgcActTb value for group1*/
          0x00000001U
        }
  },
  /*Configuration for ATOM global settings*/
  {
    /*Configuration for Atom global settings -  GtmAtomCfg*/

        /*GtmAtomGlobalConf_0*/
        {
          /*AtomTgcIntTrigRstCn0 value*/
          0x55555555U,
          /*AtomTgcActTb value */
          0x00000001U
        },
        /*GtmAtomGlobalConf_1*/
        {
          /*AtomTgcIntTrigRstCn0 value*/
          0x55555555U,
          /*AtomTgcActTb value */
          0x00000001U
        },
        /*GtmAtomGlobalConf_2*/
        {
          /*AtomTgcIntTrigRstCn0 value*/
          0x55555555U,
          /*AtomTgcActTb value */
          0x00000001U
        },
        /*GtmAtomGlobalConf_3*/
        {
          /*AtomTgcIntTrigRstCn0 value*/
          0x55555555U,
          /*AtomTgcActTb value */
          0x00000001U
        },
        /*GtmAtomGlobalConf_4*/
        {
          /*AtomTgcIntTrigRstCn0 value*/
          0x55555555U,
          /*AtomTgcActTb value */
          0x00000001U
        },
        /*GtmAtomGlobalConf_5*/
        {
          /*AtomTgcIntTrigRstCn0 value*/
          0x55555555U,
          /*AtomTgcActTb value */
          0x00000001U
        },
        /*GtmAtomGlobalConf_6*/
        {
          /*AtomTgcIntTrigRstCn0 value*/
          0x55555555U,
          /*AtomTgcActTb value */
          0x00000001U
        },
        /*GtmAtomGlobalConf_7*/
        {
          /*AtomTgcIntTrigRstCn0 value*/
          0x55555555U,
          /*AtomTgcActTb value */
          0x00000001U
        },
        /*GtmAtomGlobalConf_8*/
        {
          /*AtomTgcIntTrigRstCn0 value*/
          0x55555555U,
          /*AtomTgcActTb value */
          0x00000001U
        }
  },

  /*Configuration for Gtm to Adc trigger settings*/
  {
    /*Configuration of Gtm Adc trigger 0*/
    {
      /*GtmAdcOut0 value*/
      0x00000001U,
      /*GtmAdcOut1 value */
      0x00000000U
    },    /*Configuration of Gtm Adc trigger 1*/
    {
      /*GtmAdcOut0 value*/
      0x00000000U,
      /*GtmAdcOut1 value */
      0x00000000U
    },    /*Configuration of Gtm Adc trigger 2*/
    {
      /*GtmAdcOut0 value*/
      0x00000000U,
      /*GtmAdcOut1 value */
      0x00000000U
    },    /*Configuration of Gtm Adc trigger 3*/
    {
      /*GtmAdcOut0 value*/
      0x00000000U,
      /*GtmAdcOut1 value */
      0x00000000U
    },    /*Configuration of Gtm Adc trigger 4*/
    {
      /*GtmAdcOut0 value*/
      0x00000000U,
      /*GtmAdcOut1 value */
      0x00000000U
    }  },
  /*Configuration for Gtm to Dsadc trigger settings*/
  {
    /*Configuration of Gtm Dsadc trigger 0*/
    {
      /*GtmDsadcOut0 value*/
      0x00000000U,
      /*GtmDsadcOut1 value */
      0x00000000U
    },    /*Configuration of Gtm Dsadc trigger 1*/
    {
      /*GtmDsadcOut0 value*/
      0x00000000U,
      /*GtmDsadcOut1 value */
      0x00000000U
    },    /*Configuration of Gtm Dsadc trigger 2*/
    {
      /*GtmDsadcOut0 value*/
      0x00000000U,
      /*GtmDsadcOut1 value */
      0x00000000U
    },    /*Configuration of Gtm Dsadc trigger 3*/
    {
      /*GtmDsadcOut0 value*/
      0x00000000U,
      /*GtmDsadcOut1 value */
      0x00000000U
    }
  },
  /*Configuration for Timer to Port connections*/
  {
    /*Configuration of ToutSel*/
    /*Toutsel 0 value*/
    0x00200000U,
    /*Toutsel 1 value*/
    0x00000000U,
    /*Toutsel 2 value*/
    0x00000000U,
    /*Toutsel 3 value*/
    0x00400000U,
    /*Toutsel 4 value*/
    0x00000000U,
    /*Toutsel 5 value*/
    0x00000000U,
    /*Toutsel 6 value*/
    0x00000000U,
    /*Toutsel 7 value*/
    0x00000000U,
    /*Toutsel 8 value*/
    0x00000000U,
    /*Toutsel 9 value*/
    0x00000000U,
    /*Toutsel 10 value*/
    0x00000000U,
    /*Toutsel 11 value*/
    0x00000000U,
    /*Toutsel 12 value*/
    0x00000000U,
    /*Toutsel 13 value*/
    0x00000000U,
    /*Toutsel 14 value*/
    0x00000000U,
    /*Toutsel 15 value*/
    0x00000000U,
    /*Toutsel 16 value*/
    0x00000000U,
    /*Toutsel 17 value*/
    0x00000000U,
    /*Toutsel 18 value*/
    0x00000000U,
    /*Toutsel 19 value*/
    0x00000000U,
    /*Toutsel 20 value*/
    0x00000000U,
    /*Toutsel 21 value*/
    0x00000000U,
    /*Toutsel 22 value*/
    0x00000000U,
    /*Toutsel 23 value*/
    0x00000000U,
    /*Toutsel 24 value*/
    0x00000000U,
    /*Toutsel 25 value*/
    0x00000000U,
    /*Toutsel 26 value*/
    0x00000000U,
    /*Toutsel 27 value*/
    0x00000000U,
    /*Toutsel 28 value*/
    0x00000000U,
    /*Toutsel 29 value*/
    0x00000000U,
    /*Toutsel 30 value*/
    0x00000000U,
    /*Toutsel 31 value*/
    0x00000000U,
    /*Toutsel 32 value*/
    0x00000000U,
    /*Toutsel 33 value*/
    0x00000000U
  },
  /*Mask for TOUTSEL configuration. SELx used will be generated as 0xF*/
  {
    /*Toutsel 0 mask value*/
    0x00f00000U,
    /*Toutsel 1 mask value*/
    0x00000000U,
    /*Toutsel 2 mask value*/
    0x00000000U,
    /*Toutsel 3 mask value*/
    0x00f00000U,
    /*Toutsel 4 mask value*/
    0x00000000U,
    /*Toutsel 5 mask value*/
    0x00000000U,
    /*Toutsel 6 mask value*/
    0x00000000U,
    /*Toutsel 7 mask value*/
    0x00000000U,
    /*Toutsel 8 mask value*/
    0x00000000U,
    /*Toutsel 9 mask value*/
    0x00000000U,
    /*Toutsel 10 mask value*/
    0x00000000U,
    /*Toutsel 11 mask value*/
    0x00000000U,
    /*Toutsel 12 mask value*/
    0x00000000U,
    /*Toutsel 13 mask value*/
    0x00000000U,
    /*Toutsel 14 mask value*/
    0x00000000U,
    /*Toutsel 15 mask value*/
    0x00000000U,
    /*Toutsel 16 mask value*/
    0x00000000U,
    /*Toutsel 17 mask value*/
    0x00000000U,
    /*Toutsel 18 mask value*/
    0x00000000U,
    /*Toutsel 19 mask value*/
    0x00000000U,
    /*Toutsel 20 mask value*/
    0x00000000U,
    /*Toutsel 21 mask value*/
    0x00000000U,
    /*Toutsel 22 mask value*/
    0x00000000U,
    /*Toutsel 23 mask value*/
    0x00000000U,
    /*Toutsel 24 mask value*/
    0x00000000U,
    /*Toutsel 25 mask value*/
    0x00000000U,
    /*Toutsel 26 mask value*/
    0x00000000U,
    /*Toutsel 27 mask value*/
    0x00000000U,
    /*Toutsel 28 mask value*/
    0x00000000U,
    /*Toutsel 29 mask value*/
    0x00000000U,
    /*Toutsel 30 mask value*/
    0x00000000U,
    /*Toutsel 31 mask value*/
    0x00000000U,
    /*Toutsel 32 mask value*/
    0x00000000U,
    /*Toutsel 33 mask value*/
    0x00000000U    
  },
  /*Configuration for Port to Timer Connections*/
  {
    /*Configuration of TimInSel*/   
    /*TimInsel 0 value*/
    0x00000000U,
    /*TimInsel 1 value*/
    0x00000000U,
    /*TimInsel 2 value*/
    0x00000000U,
    /*TimInsel 3 value*/
    0x00000000U,
    /*TimInsel 4 value*/
    0x00000000U,
    /*TimInsel 5 value*/
    0x00000000U,
    /*TimInsel 6 value*/
    0x00000000U    
  },
  /*Configuration for TBU channel - GtmTbuCfg (GtmTbuChannelConf)*/
  0x00000002U,
  /* TOM modules used configuration */
  0x0001U,
  /* ATOM modules used configuration */
  0x0001U,
  /* Gtm sleep mode configuration */
  (boolean)FALSE
};

#if (MCU_GPT1_USED == STD_ON) || (MCU_GPT2_USED == STD_ON)
/* GPT12 Prescalar configuration structure */
static const Mcu_Gpt12ConfigType Mcu_kGpt12PrescalerConfiguration_Config =
{
  /*GPT Block 1 Prescalar */
  0x00U,
  /*GPT Block 2 Prescalar */
  0x00U,
  /*Reserved field initialized to 0*/
  0x0U
};
#endif
/* Main MCU Configuration Structure */
const Mcu_ConfigType Mcu_Config =
{
  /*McuModuleConfiguration*/
  /* MCU clock Configuration Pointer*/
  Mcu_kClockConfiguration_Config,
  /* Ram Section configuration Pointer*/
  NULL_PTR,
  #if (MCU_GTM_USED == STD_ON)
  /* GTM Global Configuration Pointer*/
  &Mcu_kGtmConfiguration_Config,
  #endif
  /*Ptr to GPT12 Prescaler config structure */
  #if ((MCU_GPT1_USED == STD_ON) || (MCU_GPT2_USED == STD_ON))
  &Mcu_kGpt12PrescalerConfiguration_Config,
  #endif
  /* Ptr to Standby Mode in config structure */
  &Mcu_kLowPowerModeConfiguration_Config,
  /* Reset configuration */
  0x00000200U,
  /* Application Reset Disable configuration */
  0x00000000U,
  /* Trap configuration */
  0xffffffffU,
  /*Eru global input filter configuration */
  0x00000000U,
  /* Total number of Clock settings */
  ((Mcu_ClockType)1U),
  /* Total number of RAM Sectors */
  ((Mcu_RamSectionType)0U),
  /*GPT12 sleep mode setting */
  #if ((MCU_GPT1_USED == STD_ON) || (MCU_GPT2_USED == STD_ON))
  (boolean)FALSE,
  #endif
  #if (MCU_CCU60_USED == STD_ON)
  (boolean)FALSE,
  #endif
  #if (MCU_CCU61_USED == STD_ON)
  (boolean)FALSE
  #endif
};
/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/

#define MCU_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header included as per Autosar
   guidelines. */
#include "Mcu_MemMap.h"
