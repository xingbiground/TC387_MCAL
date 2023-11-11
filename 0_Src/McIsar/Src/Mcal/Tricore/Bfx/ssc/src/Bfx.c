/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2021)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : Bfx.c                                                      **
**                                                                            **
**  VERSION      : 12.0.0                                                     **
**                                                                            **
**  DATE         : 2021-02-23                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID={DDA63FB1-2F74-4880-973A-BF580860E9BA}]    **
**                                                                            **
**  DESCRIPTION  : BFX library source file                                    **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of BFX library,                          **
**                     AUTOSAR Release 4.2.2 and 4.4.0                        **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*[cover parentID={DC0B4213-1D31-4256-BAD3-DC0CD7F025C4}] File Structure*/
/* Own header file */
#include "Bfx.h"
/*[/cover]*/

/*[cover parentID={0AF316CA-64BD-421b-8F2F-F3966F42F073}]
Imported SW Interfaces
No BSW module function is called. Hence no BSW module header file is included.
[/cover] */

/*******************************************************************************
**                      Imported Compiler Switch Checks                       **
*******************************************************************************/

/*[cover parentID={52DEE5CF-FAD4-4034-B8EA-0129E6E23863}] Version checks*/

/* BFX Header File Version Check */
#ifndef BFX_SW_MAJOR_VERSION
#error "BFX_SW_MAJOR_VERSION is not defined. "
#endif

#ifndef BFX_SW_MINOR_VERSION
#error "BFX_SW_MINOR_VERSION is not defined. "
#endif

#ifndef BFX_SW_PATCH_VERSION
#error "BFX_SW_PATCH_VERSION is not defined."
#endif

#if (BFX_SW_MAJOR_VERSION != 20U)
#error "BFX_SW_MAJOR_VERSION does not match. "
#endif

#if (BFX_SW_MINOR_VERSION != 0U)
#error "BFX_SW_MINOR_VERSION does not match. "
#endif

#if (BFX_SW_PATCH_VERSION != 1U)
#error "BFX_SW_PATCH_VERSION does not match."
#endif


/*******************************************************************************
**                         User Mode Macros                                   **
*******************************************************************************/

/*[cover parentID={C9E9BEC9-F29C-4330-920D-618869AE79FD}]
User Mode macros not required
[/cover]*/

/******************************************************************************/

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/******************************************************************************/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/
/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
/******************************************************************************/

/*[cover parentID={826C08F0-0107-42bf-9DCC-FABBFE7F9A19}]
Code Memory section executable by all cores
[/cover]*/
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
Memory mapping support
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
Code Memory section naming as per AS
[/cover]*/
#define BFX_START_SEC_CODE_ASIL_B_GLOBAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*[cover parentID={6D3BA711-CAAB-4a34-82CC-822B613FCB90}]
MemMap_h file to be developed by user
[/cover]*/
#include "Bfx_MemMap.h"
/*******************************************************************************
**                       Global Function Definitions                          **
*******************************************************************************/
/*[cover parentID={DC57EAE9-9BF3-42f2-B172-BF68A3BF5B66}]
The BFX library does not require initialization or shut down phase
[/cover]*/


/*******************************************************************************
** Traceability      : [cover parentID={07EEBE08-34BB-4df3-A5F3-B41147724599},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_GetVersionInfo                                **
**                     (                                                      **
**                       Std_VersionInfoType* const Versioninfo               **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_GetVersionInfo returns the version information **
**                     of BFX library.                                        **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0xff                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : None                                                   **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : Versioninfo - Pointer to where to store the version    **
**                     information of this module                             **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
/*[cover parentID={0AF316CA-64BD-421b-8F2F-F3966F42F073}]
Imported SW Interfaces
Std_VersionInfoType is imported
[/cover] */
void Bfx_GetVersionInfo(Std_VersionInfoType * const Versioninfo)
{
  ((Std_VersionInfoType*)(Versioninfo))->vendorID = BFX_VENDOR_ID;
  ((Std_VersionInfoType*)(Versioninfo))->moduleID = BFX_MODULE_ID;
  ((Std_VersionInfoType*)(Versioninfo))->sw_major_version =\
                                         (uint8)BFX_SW_MAJOR_VERSION;
  ((Std_VersionInfoType*)(Versioninfo))->sw_minor_version =\
                                         (uint8)BFX_SW_MINOR_VERSION;
  ((Std_VersionInfoType*)(Versioninfo))->sw_patch_version =\
                                         (uint8)BFX_SW_PATCH_VERSION;
}/* end of Bfx_GetVersionInfo() */

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                            General Notes                                   **
*******************************************************************************/

/*******************************************************************************
**                            LOW Level Driver Functions                      **
*******************************************************************************/

/*******************************************************************************
**                            LOW Level Driver Functions                      **
*******************************************************************************/

/*[cover parentID={35C78994-9DC3-4b1c-96AF-706E29827EC8}]
Interrupt Control Registers not written
[/cover] */

/*[cover parentID={826C08F0-0107-42bf-9DCC-FABBFE7F9A19}]
Code Memory section executable by all cores
[/cover]*/
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
Memory mapping support
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
Code Memory section naming as per AS
[/cover]*/
#define BFX_STOP_SEC_CODE_ASIL_B_GLOBAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*[cover parentID={6D3BA711-CAAB-4a34-82CC-822B613FCB90}]
MemMap_h file to be developed by user
[/cover]*/
#include "Bfx_MemMap.h"

/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
Callout Memory section not used in BFX library
[/cover]*/
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
Configuration data Memory section not used in BFX library
[/cover]*/
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
Constant data Memory section not used in BFX library
[/cover]*/
/*[cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
Variable data Memory section not used in BFX library
[/cover]*/

