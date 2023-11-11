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
**  FILENAME  : McalLib_Cfg.h                                                 **
**                                                                            **
**  VERSION   : 11.0.0                                                        **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:31             !!!IGNORE-LINE!!!            **
**                                                                            **
**  GENERATOR : Build b191017-0938               !!!IGNORE-LINE!!!            **
**                                                                            **
**  BSW MODULE DECRIPTION : McalLib.bmd                                       **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : McalLib configuration generated out of ECUC file           **
**                                                                            **
**  SPECIFICATION(S) : Specification of McalLib Driver                        **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef MCALLIB_CFG_H
#define MCALLIB_CFG_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
#define MCALLIB_AR_RELEASE_MAJOR_VERSION      (4U)
#define MCALLIB_AR_RELEASE_MINOR_VERSION      (2U)
#define MCALLIB_AR_RELEASE_REVISION_VERSION   (2U)
#define MCALLIB_SW_MAJOR_VERSION              (20U)
#define MCALLIB_SW_MINOR_VERSION              (25U)
#define MCALLIB_SW_PATCH_VERSION              (0U)

/*Number of cores available*/
#define MCAL_NO_OF_CORES              (0x4U)
/* Number of active cores available */
#define MCAL_NO_OF_ACTIVE_CORES       (0x4U)

/* Backup clock frequency in MHz */
#define MCAL_BACKUP_FREQUENCY         (0x64U)

/* Global PSPR base address */
#define MCAL_PSPR0_GLOBAL_BASE_ADDR   (0x70100000U)
#define MCAL_PSPR1_GLOBAL_BASE_ADDR   (0x60100000U)
#define MCAL_PSPR2_GLOBAL_BASE_ADDR   (0x50100000U)
#define MCAL_PSPR3_GLOBAL_BASE_ADDR   (0x40100000U)

/* Global PSPR End address */
#define MCAL_PSPR0_GLOBAL_END_ADDR    (0x7010ffffU)
#define MCAL_PSPR1_GLOBAL_END_ADDR    (0x6010ffffU)
#define MCAL_PSPR2_GLOBAL_END_ADDR    (0x5010ffffU)
#define MCAL_PSPR3_GLOBAL_END_ADDR    (0x4010ffffU)

/* Global DSPR base address */
#define MCAL_DSPR0_GLOBAL_BASE_ADDR   (0x70000000U)
#define MCAL_DSPR1_GLOBAL_BASE_ADDR   (0x60000000U)
#define MCAL_DSPR2_GLOBAL_BASE_ADDR   (0x50000000U)
#define MCAL_DSPR3_GLOBAL_BASE_ADDR   (0x40000000U)

/* Global DSPR End address */
#define MCAL_DSPR0_GLOBAL_END_ADDR    (0x7003bfffU)
#define MCAL_DSPR1_GLOBAL_END_ADDR    (0x6003bfffU)
#define MCAL_DSPR2_GLOBAL_END_ADDR    (0x50017fffU)
#define MCAL_DSPR3_GLOBAL_END_ADDR    (0x40017fffU)

/*
Configuration: MCALLIB_SAFETY_ENABLE:
Compile switch to enable/disable the Safety Enable API
- ON if McalLibSafetyEnable   is true
- OFF if McalLibSafetyEnable   is false
*/
#define MCALLIB_SAFETY_ENABLE         (STD_ON)

/*For retriving the Master Core ID */
#define MCAL_MASTER_COREID            (0U)

#endif  /* MCALLIB_CFG_H */

