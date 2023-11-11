/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2020)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Crc_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 10.0.0                                                        **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:30      !!!IGNORE-LINE!!!                   **
**                                                                            **
**  GENERATOR : Build b191017-0938          !!!IGNORE-LINE!!!                 **
**                                                                            **
**  BSW MODULE DECRIPTION : Crc.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : CRC configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of CRC Driver, AUTOSAR Release 4.2.2     **
**                   : Specification of Crc Driver, AUTOSAR Release 4.4.0     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef CRC_CFG_H
#define CRC_CFG_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
#define CRC_HARDWARE_MODE       (0x01u)
#define CRC_RUNTIME_MODE        (0x02u)
#define CRC_TABLE_MODE          (0x03u)


/************************Macro for Initial Values of CRC***********************/
#define CRC_INITIAL_VALUE8      ((uint8)0xFFU)
#define CRC_INITIAL_VALUE8H2F   ((uint8)0xFFU)
#define CRC_INITIAL_VALUE16     ((uint16)0xFFFFU)
#define CRC_INITIAL_VALUE16ARC  ((uint16)0x0000U)
#define CRC_INITIAL_VALUE32     ((uint32)0xFFFFFFFFU)
#define CRC_INITIAL_VALUE32P4   ((uint32)0xFFFFFFFFU)
#define CRC_INITIAL_VALUE64     ((uint64)0xFFFFFFFFFFFFFFFFU)
/* ************************************************************************** */

/*************************Autosar specific information*************************/
#define CRC_AR_RELEASE_MAJOR_VERSION  (4U)
#define CRC_AR_RELEASE_MINOR_VERSION  (2U)
#define CRC_AR_RELEASE_REVISION_VERSION  (2U)
/* ************************************************************************** */

/*************************Release specific information*************************/
#define CRC_SW_MAJOR_VERSION  (20U)
#define CRC_SW_MINOR_VERSION  (20U)
#define CRC_SW_PATCH_VERSION  (0U)
/* ************************************************************************** */

/*************************Macro for versioninfoapi*****************************/
#define CRC_VERSION_INFO_API  (STD_ON)
/* ************************************************************************** */

/*************************Macro for Mode of CRC polynomials********************/
/*Macro for selection of 16 bit CRC method */
#define CRC_16_MODE (CRC_TABLE_MODE) 
/*Macro for selection of 16 bit CRC16ARC method*/
#define CRC_16ARC_MODE (STD_OFF) 
/*Macro for selection of 32 bit CRC32 method */
#define CRC_32_MODE (CRC_TABLE_MODE) 
/*Macro for selection of 32 bit CRCP4 method */
#define CRC_32P4_MODE (CRC_TABLE_MODE) 
/*Macro for selection of 8 bit CRC method*/
#define CRC_8_MODE (CRC_TABLE_MODE)
/*Macro for selection of 8 bit CRC8H2F method*/
#define CRC_8H2F_MODE (CRC_TABLE_MODE)
/*Macro for selection of 64 bit CRC64 method*/
#define CRC_64_MODE (STD_OFF) 
/* ************************************************************************** */

/*************************Macro for DMA mode***********************************/
/*Macro for selection of CRC_8_DMA mode*/
#define CRC_8_DMAMODE (STD_OFF)
/*Macro for selection of CRC_16_DMA mode*/
#define CRC_16_DMAMODE (STD_OFF)
/*Macro for selection of CRC_32_DMA mode*/
#define CRC_32_DMAMODE (STD_OFF)
/*Macro for selection of CRC_32P4_DMA mode*/
#define CRC_32P4_DMAMODE (STD_OFF)

/* ************************************************************************** */
#define CRC_SAFETYENABLE              (STD_ON)
/*************************Macro for Error value********************************/
#define CRC_8_CONFIGERROR_VAL          (0)
#define CRC_8H2F_CONFIGERROR_VAL    (0)
#define CRC_16_CONFIGERROR_VAL      (0)
#define CRC_32_CONFIGERROR_VAL      (0)
#define CRC_32P4_CONFIGERROR_VAL      (0)

/****************************FCE-DMA allocation to Cores***********************/
#define CRC_DMA_MAX_CHANNELS (0U)
#define CRC_CONFIGURED_CORE0 (STD_OFF)
#define CRC_CONFIGURED_CORE1 (STD_OFF)
#define CRC_CONFIGURED_CORE2 (STD_OFF)
#define CRC_CONFIGURED_CORE3 (STD_OFF)
#define CRC_CONFIGURED_CORE4 (STD_OFF)
#define CRC_CONFIGURED_CORE5 (STD_OFF)
/* ************************************************************************** */
#endif  /* CRC_CFG_H */
