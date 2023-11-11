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
**  FILENAME     : Std_Types.h                                                **
**                                                                            **
**  VERSION      : 2.0.0                                                      **
**                                                                            **
**  DATE         : 2018-03-26                                                 **
**                                                                            **
**  VARIANT      : NA                                                         **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : AUTOSAR Standard Tyes                                      **
**                                                                            **
**  SPECIFICATION(S) : AUTOSAR_SWS_StandardTypes.pdf, AUTOSAR Release 4.2.2   **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef STD_TYPES_H
#define STD_TYPES_H

/* Traceability:
 [cover parentID={9B86C499-F591-4d3c-8A6C-5ED8FCAD72A1}] 
Include protection
 [/cover]*/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Traceability:
 [cover parentID={B6DD2FBA-E4D7-4e6f-9065-124B8D8B5F50}]
 Files inclusion
 [/cover]*/
#include "Compiler.h"
#include "Platform_Types.h"
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/* Published information */
#define STD_TYPES_VENDOR_ID    (17u)
#define STD_TYPES_AR_RELEASE_MAJOR_VERSION (4u)
#define STD_TYPES_AR_RELEASE_MINOR_VERSION (2u)
#define STD_TYPES_AR_RELEASE_REVISION_VERSION (2u)
#define STD_TYPES_SW_MAJOR_VERSION (1u)
#define STD_TYPES_SW_MINOR_VERSION (0u)
#define STD_TYPES_SW_PATCH_VERSION (0u)


/* [cover parentID={D3B7A33C-16F3-4536-948B-9A6B08314102}]Std_StatusType */

#ifndef STATUSTYPEDEFINED
  #define STATUSTYPEDEFINED
  #define E_OK     0x00u

  typedef unsigned char StatusType; /* OSEK compliance */
#endif
/* [/cover] */
#define E_NOT_OK   0x01u

/* [cover parentID={48655FD7-0240-489e-9A11-02B5238A1A86}] STD_HIGH, STD_LOW*/
#define STD_HIGH   0x01u       /* Standard HIGH */
#define STD_LOW    0x00u       /* Standard LOW */
/* [/cover] */
/* [cover parentID={80CAA429-4E81-4c18-9C31-F38F97D4B9A2}]STD_ACTIVE, STD_IDLE*/
#define STD_ACTIVE 0x01u       /* Logical state active */
#define STD_IDLE   0x00u       /* Logical state idle */
/* [/cover] */
/* [cover parentID={4861BF77-68F1-4433-BF83-505E4DB52C88}]STD_ON, STD_OFF */
#define STD_ON     0x01u      /* Standard ON */
#define STD_OFF    0x00u      /* Standard OFF */
/* [/cover] */
/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/*
 Describes the standard Type Definitions used in the project
*/

/* Standard return type */
/* [cover parentID={B22BF253-F56E-4f6e-9EF6-E6F924E968C9}]Std_ReturnType */

typedef uint8  Std_ReturnType;
/*[/cover]*/
/*
  Structure for the Version of the module.This is requested by calling 
  <Module name>_GetVersionInfo()
*/
/* [cover parentID={267E034F-2D9A-4ef5-9453-2D429CAEE5BC}]Std_VersionInfoType*/
typedef struct
{
  uint16  vendorID;
  uint16  moduleID;
  uint8   sw_major_version;
  uint8   sw_minor_version;
  uint8   sw_patch_version;
}Std_VersionInfoType;
/*[/cover]*/
/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/

#endif /* STD_TYPES_H*/


