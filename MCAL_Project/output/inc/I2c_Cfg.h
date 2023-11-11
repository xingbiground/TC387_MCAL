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
**  FILENAME  : I2c_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 4.0.0                                                         **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:30    !!!IGNORE-LINE!!!                     **
**                                                                            **
**  GENERATOR : Build b191017-0938    !!!IGNORE-LINE!!!                       **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : I2C configuration generated out of ECU configuration       **
**                 file (I2c.bmd/.xdm)                                        **
**                                                                            **
**  MAY BE CHANGED BY USER [yes/no]: No                                       **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                                                                            **
**  TRACEBILITY :                                                             **
**                                                                            **
*******************************************************************************/
#ifndef I2C_CFG_H
#define I2C_CFG_H

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
#define I2C_AR_RELEASE_MAJOR_VERSION  (4U)
#define I2C_AR_RELEASE_MINOR_VERSION  (2U)
#define I2C_AR_RELEASE_REVISION_VERSION  (2U)

#define I2C_SW_MAJOR_VERSION   (10U)
#define I2C_SW_MINOR_VERSION   (40U)
#define I2C_SW_PATCH_VERSION   (1U)

#define I2C_DEV_ERROR_DETECT  (STD_ON)

#define I2C_VERSION_INFO_API  (STD_OFF)

#define I2C_INIT_DEINIT_API_MODE  (I2C_MCAL_SUPERVISOR)



#define I2C_MAX_CHANNELS (1U)

#define I2C_REG_ADDR\
                        &MODULE_I2C0,\
                        &MODULE_I2C1
#define I2C_MAX_HW_UNIT (2)

#endif  /* I2C_CFG_H */

