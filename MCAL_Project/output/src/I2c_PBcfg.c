
/*****************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2019)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : I2c_PBcfg.c                                                   **
**                                                                            **
**  VERSION   : 1.40.0_8.0.0                                                  **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:30    !!!IGNORE-LINE!!!                     **
**                                                                            **
**  GENERATOR : Build b191017-0938    !!!IGNORE-LINE!!!                       **
**                                                                            **
**  BSW MODULE DECRIPTION : i2c.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION : This file contains                                          **
**                Code template for I2c_PBcfg.c file                          **
**                                                                            **
**  MAY BE CHANGED BY USER [yes/no]: No                                       **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                                                                            **
**  TRACEBILITY :                                                             **
**                                                                            **
*******************************************************************************/




/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Include I2C Module File */
#include "I2c.h"

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/
/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/

#define I2C_START_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.
*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "I2c_MemMap.h"
static const I2c_ChannelConfigType I2c_ChannelConfig[I2C_MAX_CHANNELS] =
{
  {
    /* Hw Unit */
    0x0U,
    
    /* AdddressCfgValue */
    0x380000U,
    
    /* FracDividerCfgValue */
    0x203e5U,
    
    /* FracDividerHighCfgValue */
    0x0U,
    
    /* TimingCfgvalue */
    0x0U,
    
    /* FIFOCfgValue */
    0x30022U,
    
    /* PortPinCfgvalue */
    0x0U,
    
    /* HwClkSettings */
    0x100U,
    
    /* AddressingMode */
    I2C_7_BIT_ADDRESSING,
    
    /* Notification function */
    {
      NULL_PTR
    },
    
    /* Tx Timeout value */
    65535U,
    
    /* Rx Timeout value */
    65535U
  },
};
/* I2c configuration set */
/* MISRA2012_RULE_8_7_JUSTIFICATION: Module configuration data structure
declaration is as per Autosar guidelines. This data structure is needed
by SW units using I2c Driver APIs hence it should be declared as extern in
the SW unit from where it is used */
/* MISRA2012_RULE_8_4_JUSTIFICATION: Module configuration data structure
declaration is as per Autosar guidelines. This data structure is needed
by SW units using I2c Driver APIs hence it should be declared as extern in
the SW unit from where it is used */
const I2c_ConfigType I2c_Config  =
{
      &I2c_ChannelConfig[0],
      I2C_MAX_CHANNELS
};

#define I2C_STOP_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "I2c_MemMap.h"
