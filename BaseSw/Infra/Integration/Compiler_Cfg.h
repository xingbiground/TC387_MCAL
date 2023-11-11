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
**  FILENAME     : Compiler_Cfg.h                                             **
**                                                                            **
**  VERSION      : 0.0.2                                                      **
**                                                                            **
**  DATE         : 2016-03-26                                                 **
**                                                                            **
**  VARIANT      : NA                                                         **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID={035D74CB-B32E-40b3-BDF7-72AE57794957}]    **
**                                                                            **
**  DESCRIPTION  : Compiler Configuration File                                **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Compiler Abstraction,                 **
**                     AUTOSAR Release 4.2.2                                  **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/

#ifndef COMPILER_CFG_H
#define COMPILER_CFG_H

/*

 * The following memory and pointer classes can be configured per module.

 * Those defines are passed to the compiler abstraction macros in Compiler.h

 */

/*******************************************************************************

**                                 MCU                                        **

*******************************************************************************/

/*To be used for code*/

#define MCU_CODE

/*To be used for all global or static variables that are never initialized*/

#define MCU_VAR_NOINIT

/*To be used for all global or static variables that are initialized only after power on reset*/

#define MCU_VAR_POWER_ON_INIT

/* To be used for all global or static variables that have at least one of the

following properties:

-accessed bitwise

-frequently used

-high number of accesses in source code*/

#define MCU_VAR_FAST

/*To be used for global or static variables that are initialized after every

reset.*/

#define MCU_VAR

/*To be used for global or static constants*/

#define MCU_CONST

/*To be used for references on application data (expected to be in RAM or ROM) passed via API*/

#define MCU_APPL_DATA

/*To be used for references on application constants (expected to be certainly in ROM, for instance pointer of Init-function) passed via API*/

#define MCU_APPL_CONST

/*To be used for references on application functions. (e.g. call back function pointers)*/

#define MCU_APPL_CODE

/*******************************************************************************

**                                 PORT                                        *

*******************************************************************************/

/*To be used for code*/

#define PORT_CODE

/*To be used for all global or static variables that are never initialized*/

#define PORT_VAR_NOINIT

/*To be used for all global or static variables that are initialized only after power on reset*/

#define PORT_VAR_POWER_ON_INIT

/* To be used for all global or static variables that have at least one of the

following properties:

-accessed bitwise

-frequently used

-high number of accesses in source code*/

#define PORT_VAR_FAST

/*To be used for global or static variables that are initialized after every

reset.*/

#define PORT_VAR

/*To be used for global or static constants*/

#define PORT_CONST

/*To be used for references on application data (expected to be in RAM or ROM) passed via API*/

#define PORT_APPL_DATA

/*To be used for references on application constants (expected to be certainly in ROM, for instance pointer of Init-function) passed via API*/

#define PORT_APPL_CONST

/*To be used for references on application functions. (e.g. call back function pointers)*/

#define PORT_APPL_CODE

/*******************************************************************************

**                                 DIO                                        **

*******************************************************************************/

/*To be used for code*/

#define DIO_CODE

/*To be used for all global or static variables that are never initialized*/

#define DIO_VAR_NOINIT

/*To be used for all global or static variables that are initialized only after power on reset*/

#define DIO_VAR_POWER_ON_INIT

/* To be used for all global or static variables that have at least one of the

following properties:

-accessed bitwise

-frequently used

-high number of accesses in source code*/

#define DIO_VAR_FAST

/*To be used for global or static variables that are initialized after every

reset.*/

#define DIO_VAR

/*To be used for global or static constants*/

#define DIO_CONST

/*To be used for references on application data (expected to be in RAM or ROM) passed via API*/

#define DIO_APPL_DATA

/*To be used for references on application constants (expected to be certainly in ROM, for instance pointer of Init-function) passed via API*/

#define DIO_APPL_CONST

/*To be used for references on application functions. (e.g. call back function pointers)*/

#define DIO_APPL_CODE

/*******************************************************************************

**                                 ADC                                        **

*******************************************************************************/

/*To be used for code*/

#define ADC_CODE

/*To be used for all global or static variables that are never initialized*/

#define ADC_VAR_NOINIT

/*To be used for all global or static variables that are initialized only after power on reset*/

#define ADC_VAR_POWER_ON_INIT

/* To be used for all global or static variables that have at least one of the

following properties:

-accessed bitwise

-frequently used

-high number of accesses in source code*/

#define ADC_VAR_FAST

/*To be used for global or static variables that are initialized after every

reset.*/

#define ADC_VAR

/*To be used for global or static constants*/

#define ADC_CONST

/*To be used for references on application data (expected to be in RAM or ROM) passed via API*/

#define ADC_APPL_DATA

/*To be used for references on application constants (expected to be certainly in ROM, for instance pointer of Init-function) passed via API*/

#define ADC_APPL_CONST

/*To be used for references on application functions. (e.g. call back function pointers)*/

#define ADC_APPL_CODE

/*******************************************************************************

**                                 GPTA                                        *

*******************************************************************************/

/*To be used for code*/

#define GPTA_CODE

/*To be used for all global or static variables that are never initialized*/

#define GPTA_VAR_NOINIT

/*To be used for all global or static variables that are initialized only after power on reset*/

#define GPTA_VAR_POWER_ON_INIT

/* To be used for all global or static variables that have at least one of the

following properties:

-accessed bitwise

-frequently used

-high number of accesses in source code*/

#define GPTA_VAR_FAST

/*To be used for global or static variables that are initialized after every

reset.*/

#define GPTA_VAR

/*To be used for global or static constants*/

#define GPTA_CONST

/*To be used for references on application data (expected to be in RAM or ROM) passed via API*/

#define GPTA_APPL_DATA

/*To be used for references on application constants (expected to be certainly in ROM, for instance pointer of Init-function) passed via API*/

#define GPTA_APPL_CONST

/*To be used for references on application functions. (e.g. call back function pointers)*/

#define GPTA_APPL_CODE

/*******************************************************************************

**                                 GPT                                        **

*******************************************************************************/

/*To be used for code*/

#define GPT_CODE

/*To be used for all global or static variables that are never initialized*/

#define GPT_VAR_NOINIT

/*To be used for all global or static variables that are initialized only after power on reset*/

#define GPT_VAR_POWER_ON_INIT

/* To be used for all global or static variables that have at least one of the

following properties:

-accessed bitwise

-frequently used

-high number of accesses in source code*/

#define GPT_VAR_FAST

/*To be used for global or static variables that are initialized after every

reset.*/

#define GPT_VAR

/*To be used for global or static constants*/

#define GPT_CONST

/*To be used for references on application data (expected to be in RAM or ROM) passed via API*/

#define GPT_APPL_DATA

/*To be used for references on application constants (expected to be certainly in ROM, for instance pointer of Init-function) passed via API*/

#define GPT_APPL_CONST

/*To be used for references on application functions. (e.g. call back function pointers)*/

#define GPT_APPL_CODE

/*******************************************************************************

**                                 ICU                                        **

*******************************************************************************/

/*To be used for code*/

#define ICU_CODE

/*To be used for all global or static variables that are never initialized*/

#define ICU_VAR_NOINIT

/*To be used for all global or static variables that are initialized only after power on reset*/

#define ICU_VAR_POWER_ON_INIT

/* To be used for all global or static variables that have at least one of the

following properties:

-accessed bitwise

-frequently used

-high number of accesses in source code*/

#define ICU_VAR_FAST

/*To be used for global or static variables that are initialized after every

reset.*/

#define ICU_VAR

/*To be used for global or static constants*/

#define ICU_CONST

/*To be used for references on application data (expected to be in RAM or ROM) passed via API*/

#define ICU_APPL_DATA

/*To be used for references on application constants (expected to be certainly in ROM, for instance pointer of Init-function) passed via API*/

#define ICU_APPL_CONST

/*To be used for references on application functions. (e.g. call back function pointers)*/

#define ICU_APPL_CODE

/*******************************************************************************

**                                 PWM                                        **

*******************************************************************************/

/*To be used for code*/

#define PWM_CODE

/*To be used for all global or static variables that are never initialized*/

#define PWM_VAR_NOINIT

/*To be used for all global or static variables that are initialized only after power on reset*/

#define PWM_VAR_POWER_ON_INIT

/* To be used for all global or static variables that have at least one of the

following properties:

-accessed bitwise

-frequently used

-high number of accesses in source code*/

#define PWM_VAR_FAST

/*To be used for global or static variables that are initialized after every

reset.*/

#define PWM_VAR

/*To be used for global or static constants*/

#define PWM_CONST

/*To be used for references on application data (expected to be in RAM or ROM) passed via API*/

#define PWM_APPL_DATA

/*To be used for references on application constants (expected to be certainly in ROM, for instance pointer of Init-function) passed via API*/

#define PWM_APPL_CONST

/*To be used for references on application functions. (e.g. call back function pointers)*/

#define PWM_APPL_CODE

/*******************************************************************************

**                                 SPI                                        **

*******************************************************************************/

/*To be used for code*/

#define SPI_CODE

/*To be used for all global or static variables that are never initialized*/

#define SPI_VAR_NOINIT

/*To be used for all global or static variables that are initialized only after power on reset*/

#define SPI_VAR_POWER_ON_INIT

/* To be used for all global or static variables that have at least one of the

following properties:

-accessed bitwise

-frequently used

-high number of accesses in source code*/

#define SPI_VAR_FAST

/*To be used for global or static variables that are initialized after every

reset.*/

#define SPI_VAR

/*To be used for global or static constants*/

#define SPI_CONST

/*To be used for references on application data (expected to be in RAM or ROM) passed via API*/

#define SPI_APPL_DATA

/*To be used for references on application constants (expected to be certainly in ROM, for instance pointer of Init-function) passed via API*/

#define SPI_APPL_CONST

/*To be used for references on application functions. (e.g. call back function pointers)*/

#define SPI_APPL_CODE

/*******************************************************************************

**                                 CAN                                        **

*******************************************************************************/

/*To be used for code*/

#define CAN_CODE

/*To be used for all global or static variables that are never initialized*/

#define CAN_VAR_NOINIT

/*To be used for all global or static variables that are initialized only after power on reset*/

#define CAN_VAR_POWER_ON_INIT

/* To be used for all global or static variables that have at least one of the

following properties:

-accessed bitwise

-frequently used

-high number of accesses in source code*/

#define CAN_VAR_FAST

/*To be used for global or static variables that are initialized after every

reset.*/

#define CAN_VAR

/*To be used for global or static constants*/

#define CAN_CONST

/*To be used for references on application data (expected to be in RAM or ROM) passed via API*/

#define CAN_APPL_DATA

/*To be used for references on application constants (expected to be certainly in ROM, for instance pointer of Init-function) passed via API*/

#define CAN_APPL_CONST

/*To be used for references on application functions. (e.g. call back function pointers)*/

#define CAN_APPL_CODE

/*******************************************************************************

**                                 WDG                                        **

*******************************************************************************/

/*To be used for code*/

#define WDG_CODE

/*To be used for all global or static variables that are never initialized*/

#define WDG_VAR_NOINIT

/*To be used for all global or static variables that are initialized only after power on reset*/

#define WDG_VAR_POWER_ON_INIT

/* To be used for all global or static variables that have at least one of the

following properties:

-accessed bitwise

-frequently used

-high number of accesses in source code*/

#define WDG_VAR_FAST

/*To be used for global or static variables that are initialized after every

reset.*/

#define WDG_VAR

/*To be used for global or static constants*/

#define WDG_CONST

/*To be used for references on application data (expected to be in RAM or ROM) passed via API*/

#define WDG_APPL_DATA

/*To be used for references on application constants (expected to be certainly in ROM, for instance pointer of Init-function) passed via API*/

#define WDG_APPL_CONST

/*To be used for references on application functions. (e.g. call back function pointers)*/

#define WDG_APPL_CODE

/*******************************************************************************

**                                 CANTRCV                                     *

*******************************************************************************/

/*To be used for code*/

#define CANTRCV_CODE

/*To be used for all global or static variables that are never initialized*/

#define CANTRCV_VAR_NOINIT

/*To be used for all global or static variables that are initialized only after power on reset*/

#define CANTRCV_VAR_POWER_ON_INIT

/* To be used for all global or static variables that have at least one of the

following properties:

-accessed bitwise

-frequently used

-high number of accesses in source code*/

#define CANTRCV_VAR_FAST

/*To be used for global or static variables that are initialized after every

reset.*/

#define CANTRCV_VAR

/*To be used for global or static constants*/

#define CANTRCV_CONST

/*To be used for references on application data (expected to be in RAM or ROM) passed via API*/

#define CANTRCV_APPL_DATA

/*To be used for references on application constants (expected to be certainly in ROM, for instance pointer of Init-function) passed via API*/

#define CANTRCV_APPL_CONST

/*To be used for references on application functions. (e.g. call back function pointers)*/

#define CANTRCV_APPL_CODE

#endif /* COMPILER_CFG_H */

