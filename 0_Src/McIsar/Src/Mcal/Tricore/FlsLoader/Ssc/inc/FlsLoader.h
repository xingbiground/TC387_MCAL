/*******************************************************************************
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
**  FILENAME     : FlsLoader.h                                                **
**                                                                            **
**  VERSION      : 12.0.0                                                     **
**                                                                            **
**  DATE         : 2022-07-05                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Flsloader Driver header definition file                    **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={4B085EF4-0701-45a0-B98C-E960E9C288E8}]
FlsLoader file structure
[/cover] */

#ifndef FLSLOADER_H
#define FLSLOADER_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* [cover parentID={8802F572-9CD3-4540-A2E9-45AAB2AF6352}] [/cover]*/
/* Inclusion of Platform_Types.h and Compiler.h */
#include "Std_Types.h"
#include "Mcal_Compiler.h"
#include "McalLib.h"

/* Pre-compile/static configuration parameters for FLASHLOADER */
#include "FlsLoader_Cfg.h"

/* Conditional Inclusion of Developement Error Tracer File */
/* [cover parentID={8802F572-9CD3-4540-A2E9-45AAB2AF6352}] [/cover]*/
#if  ( FLSLOADER_DEV_ERROR_DETECT == STD_ON )
#include "Det.h"
#endif
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/*
   Published parameters
*/

/* [cover parentID={0EEFA107-912D-4311-9B5E-8577838C6389}][/cover] */
/* FLSLOADER Vendor ID */
#define FLSLOADER_VENDOR_ID              ((uint16)17U)

/* [cover parentID={0EEFA107-912D-4311-9B5E-8577838C6389}][/cover] */
/* FLSLOADER module id 255 -> 0xFF */
#define FLSLOADER_MODULE_ID              ((uint16)255U)

/*If there is no error  */
#define FLSLOADER_E_OK              ((FlsLoader_ReturnType)0x0)
/*If there is error */
#define FLSLOADER_E_NOT_OK          ((FlsLoader_ReturnType)0x1)
/* If locked segment */
#define FLSLOADER_E_LOCKED          ((FlsLoader_ReturnType)0x2)

/*If the memory is installed with OTP */
#define FLSLOADER_E_ROMVERSION      ((FlsLoader_ReturnType)0x3)

/* [cover parentID={6CED327A-842D-42c4-A55D-CD627376AE24}][/cover] */
/*If the device is busy */
#define FLSLOADER_E_BUSY            ((FlsLoader_ReturnType)0x5)

/* If the OPER bit or timeout occured (internal to the driver) */
#define FLSLOADER_E_OPERR           ((FlsLoader_ReturnType)0x6)

/*
   FLASH LOADER Development error codes
*/
#if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)

/* [cover parentID={73FFF22E-0995-4073-AD62-57A39424140B}][/cover] */
/*If Invalid Parameter   */
#define FLSLOADER_E_PARAM_IGNORED   ((uint8)0x0)
/*If the Value is incorrect */
#define FLSLOADER_E_UNLOCKED        ((uint8)0x1)

/* [cover parentID={FFD46B8D-9376-494b-BE26-852E0C2E6A7B}][/cover] */
/*If the Size is incorrect */
#define FLSLOADER_E_PARAM_LENGTH    ((uint8)0x2)

/* [cover parentID={E662C0C6-1065-478f-AEBF-E160E5F0C036}][/cover] */
/*If the Position is incorrect */
#define FLSLOADER_E_PARAM_ADDRESS   ((uint8)0x3)

/* [cover parentID={6AF03CF6-BE54-4b91-861B-1C6D742EF002}][/cover] */
/*If the Channel is not initialised */
#define FLSLOADER_E_UNINIT          ((uint8)0x4)

/* [cover parentID={FC404F9A-6377-4d85-A7DF-0C5E0DA90E15}][/cover] */
/*If the Channel is not initialised */
#define FLSLOADER_E_PARAM_POINTER   ((uint8)0x6)

/*
   API Service ID's
*/
/* API Service ID for FlsLoader_Init() */
#define FLSLOADER_SID_INIT           ((uint8)0x2F)
/* API Service ID for FlsLoader_DeInit() */
#define FLSLOADER_SID_DEINIT         ((uint8)0x30)
/* API Service ID for FlsLoader_WriteSync() */
#define FLSLOADER_SID_WRITE         ((uint8)0x31)
/* API Service ID for FlsLoader_EraseSync() */
#define FLSLOADER_SID_ERASE         ((uint8)0x32)
/* API Service ID for FlsLoader_Lock() */
#define FLSLOADER_SID_LOCK          ((uint8)0x33)
/* API Service ID for FlsLoader_Unlock() */
#define FLSLOADER_SID_UNLOCK        ((uint8)0x34)
/* API Service ID for FlsLoader_GetVersionInfo() */
#define FLSLOADER_SID_GETVERSIONINFO ((uint8)0x35)

#endif  /*(FLSLOADER_DEV_ERROR_DETECT == STD_ON) */

/* The flash sizes */
#define FLSLOADER_SIZE_4K           ((0x00001000U))
#define FLSLOADER_SIZE_16K          ((0x00004000U))
#define FLSLOADER_SIZE_64K          ((0x00010000U))
#define FLSLOADER_SIZE_128K         ((0x00020000U))

/* Physical sector size*/
#define FLSLOADER_PHYSICAL_SECTOR_1MB     ((0x00100000U))

/* Max erase sectors for PFlash and DFlash */
#define FLSLOADER_MAX_PF_ERASE_SECTORS_16 ((uint32)16U)
#define FLSLOADER_MAX_DF_ERASE_SECTORS_64 ((uint32)64U)

/* To differentiate between PFLASH and DFLASH the following value is written
in the command cycle. */
#define FLSLOADER_PFLASH_VAL            ((uint32)(0x00000050U))
#define FLSLOADER_DFLASH_VAL            ((uint32)(0x0000005DU))

/*******************************************************************************
**                      Private Macro like functions                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/* [cover parentID={4AB28438-C206-45e5-A03A-E03C48F5987C}] [/cover]*/
/*
Type: FlsLoader_ValueType
Specifies the values for Mode and Password
*/
typedef uint32 FlsLoader_ValueType;

/* [cover parentID={4FD3CA46-9EED-4cfc-9CC2-7BB624B55AFB}] [/cover]*/
/*
Type: FlsLoader_AddressType
This specifies the starting address of a sector of Flash
or starting address of a page
*/
typedef uint32 FlsLoader_AddressType;

/* [cover parentID={27ACDD70-D791-4e20-8B65-462E913EA0A3}] [/cover]*/
/*
Type: FlsLoader_LengthType
This specifies the Length/size to programme /erase
*/
typedef uint32 FlsLoader_LengthType;

/* [cover parentID={BC95914F-E8CF-4b16-A6B2-F08DA27B11B6}] [/cover]*/
/*
Type: FlsLoader_ReturnType
This specifies the various Return types that can be specified by the APIs
*/
typedef uint32 FlsLoader_ReturnType;

/* [cover parentID={4BF40FD4-193A-46ee-B5C1-74B7B9709E66}] [/cover]*/
/*
Type: FlsLoader_Configtype
*/
typedef void FlsLoader_ConfigType;

#if (FLSLOADER_CALLOUT_FUNC == STD_ON)
/* [cover parentID={295E15CB-B8B8-4c8d-ABB9-8136F4142026}] [/cover]*/
/*
Type: FlsLoader_CallOutFunc
*/
typedef void (*FlsLoader_CallOutFunc) (void);

#endif

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/
#define FLSLOADER_START_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "FlsLoader_MemMap.h"

/* Enable/Disable the API FlsLoader_GetVersionInfo*/
#if (FLSLOADER_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Syntax           : void FlsLoader_GetVersionInfo(                          **
**                                      Std_VersionInfoType*                  **
**                                      const VersioninfoPtr )                **
**                                                                            **
** Service ID       :0x35                                                     **
**                                                                            **
** Sync/Async       :Synchronous                                              **
**                                                                            **
** Reentrancy       :Reentrant                                                **
**                                                                            **
** Parameters (in)  :None                                                     **
**                                                                            **
** Parameters (out) :VersioninfoPtr : Pointer to where to store the version   **
**                                   information of this module.              **
**                                                                            **
** Return value     :None                                                     **
**                                                                            **
** Description      :This service returns the version information of          **
**                   this module.                                             **
**                   The version information includes:                        **
**                   Module Id,Vendor Id , Vendor specific version numbers    **
**                                                                            **
*******************************************************************************/
extern void  FlsLoader_GetVersionInfo(Std_VersionInfoType * \
                                      const VersionInfoPtr);

#else

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used for Error
 * Indication when FlsLoader_GetVersionInfo() API is not selected.
   No functional impact*/
#define FlsLoader_GetVersionInfo(VersionInfoPtr) \
                             ERROR_FlsLoader_GetVersionInfo_API_IS_NOT_SELECTED

#endif /* (FLSLOADER_VERSION_INFO_API == STD_ON) */

/*******************************************************************************
** Syntax           :  FlsLoader_ReturnType FlsLoader_Init(                   **
**                      const FlsLoader_ConfigType* const Address)            **
**                                                                            **
** Service ID       : 0x2F                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : Address: NULL pointer because the driver supports       **
**                    single configuration variant                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FLSLOADER_E_OK: Successful execution                    **
**                    FLSLOADER_E_ROMVERSION: All sectors are protected under **
**                    OTP.                                                    **
**                    FLSLOADER_E_NOT_OK: Development error occurred          **
**                                                                            **
** Description      : This function initilizes the flash module and checks    **
**                    if all the flash sectors is configured as ROM           **
*******************************************************************************/
extern FlsLoader_ReturnType FlsLoader_Init(const FlsLoader_ConfigType* \
                                           const Address);


/* Enable / Disable the use of the function */
#if (FLSLOADER_DEINIT_API == STD_ON)
/*******************************************************************************
** Syntax           :  FlsLoader_ReturnType FlsLoader_DeInit(void)            **
**                                                                            **
** Service ID       : 0x30                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : void                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FLSLOADER_E_OK:  Successful execution.                  **
**                    FLSLOADER_E_BUSY:  Flash is busy with erase/write       **
**                    operation.                                              **
**                    FLSLOADER_E_NOT_OK: Development error occurred.         **
**                                                                            **
** Description      : This function deinitilizes the flash module.            **
**                    This Function sets the registers to their default       **
**                    state and executes the reset to read command.           **
*******************************************************************************/
extern  FlsLoader_ReturnType FlsLoader_DeInit(void);

#else

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used for Error
 * Indication when FlsLoader_DeInit() API is not selected.
   No functional impact*/
#define FlsLoader_DeInit() \
ERROR_FlsLoader_DeInit_API_IS_NOT_SELECTED

#endif /* (FLSLOADER_DEINIT_API == STD_ON) */

#define FLSLOADER_STOP_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "FlsLoader_MemMap.h"

#define FLSLOADER_START_SEC_WRITEERASE_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "FlsLoader_MemMap.h"

/*******************************************************************************
** Syntax           :  FlsLoader_ReturnType FlsLoader_Write(                  **
**                      const FlsLoader_AddressType TargetAddress,            **
**                      const FlsLoader_LengthType Length,                    **
**                      const uint8* const SourceAddressPtr)                  **
**                                                                            **
** Service ID       : 0x31                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : Length: Number of bytes to be written. It should be     **
**                      multiple of the following page sizes of the           **
**                      selected Flash for write.                             **
**                      PFlash: 32 Bytes                                      **
**                      DFlash: 8 Bytes                                       **
**                    SourceAddressPtr: Pointer to source data buffer         **
**                    TargetAddress: Target address in Flash memory.          **
**                      It should be aligned to the following page sizes      **
**                      of the selected Flash for write.                      **
**                      PFlash: 32 Bytes                                      **
**                      DFlash: 8 Bytes                                       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FLSLOADER_E_OK: Successful execution.                   **
**                    FLSLOADER_E_BUSY: Flash is busy with erase/write        **
**                      operation.                                            **
**                    FLSLOADER_E_NOT_OK: Returned when DET, Sequence error,  **
**                      Program/Erase verify errors occur, SourceAddressPtr is**
**                      null pointer.                                         **
**                    FLSLOADER_E_LOCKED: Programming a locked sector.        **
**                                                                            **
** Description      : This function is used to program a page of internal     **
**                    Flash. Sectors of PFlash and DFlash can be programmed.  **
*******************************************************************************/
extern FlsLoader_ReturnType FlsLoader_Write(
                                     const FlsLoader_AddressType TargetAddress,
                                     const FlsLoader_LengthType Length,
                                     const uint8 *const SourceAddressPtr);

/*******************************************************************************
** Syntax           :  FlsLoader_ReturnType FlsLoader_Erase(                  **
**                      const FlsLoader_AddressType TargetAddress,            **
**                      const FlsLoader_LengthType Length                     **
**                    )                                                       **
**                                                                            **
** Service ID       : 0x32                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : Length: Number of Flash (PFlash or DFlash) sectors to   **
**                    be erased. Note: Number of sectors should lie within    **
**                    single Flash bank. Erase operation across the Flash     **
**                    banks is not supported.                                 **
**                    TargetAddress: Target address in Flash memory. It       **
**                    should be aligned to the following sector sizes of the  **
**                    selected Flash for erase.                               **
**                    PFlash: 16 Kbyte                                        **
**                    DFlash: 4 Kbyte                                         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FLSLOADER_E_OK: Successful completion.                  **
**                    FLSLOADER_E_BUSY: Flash is busy with erase/write        **
**                    operation.                                              **
**                    FLSLOADER_E_NOT_OK: Returned when DET, Sequence error,  **
**                    Erase verify errors occur.                              **
**                    FLSLOADER_E_LOCKED: Sector is protected.                **
**                                                                            **
** Description      : This function erases the logical sectors of the         **
                      internal Flash. The completion of this operation is     **
                      denoted by clearing of busy status flag or error.       **
*******************************************************************************/
extern  FlsLoader_ReturnType FlsLoader_Erase(
                                     const FlsLoader_AddressType TargetAddress,
                                     const FlsLoader_LengthType Length
                                             );

#define FLSLOADER_STOP_SEC_WRITEERASE_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "FlsLoader_MemMap.h"

#define FLSLOADER_START_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "FlsLoader_MemMap.h"
/* Enable / Disable the use of the function */
#if (FLSLOADER_LOCK_UNLOCK_API == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={F2D81695-7D14-4c10-BB8F-FE46A6E4AD8A}] **
** Syntax           :  FlsLoader_ReturnType FlsLoader_Lock(void)              **
**                                                                            **
** Service ID       : 0x33                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FLSLOADER_E_OK: Successful completion.                  **
**                    FLSLOADER_E_BUSY:  Flash is busy with erase/write       **
**                    operation.                                              **
**                    FLSLOADER_E_NOT_OK: Returned when DET, Sequence error,  **
**                    Program/Erase verify errors occur.                      **
**                    FLSLOADER_E_LOCKED: Flash is already locked.            **
**                                                                            **
** Description      : This function locks (protect) the internal PFlash and   **
**                    DFlash 0 of micro-controller with pre-configured        **
**                    protections.                                            **
**                                                                            **
**                    Following protection configurations are                 **
**                    supported by the driver:                                **
**                    -DFlash: Read protection, write protection.             **
**                    -DFlash protections are configurable at bank level.     **
**                    -PFlash: Write protection, write once protection (WOP), **
**                    one time programmable (OTP) protection.                 **
**                    -PFlash protections are configurable at sector level.   **
**                    However a bank and its corresponding sectors to be      **
**                    protected shall have same protection configured.        **
*******************************************************************************/
extern FlsLoader_ReturnType FlsLoader_Lock(void);

#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used for Error
 * Indication when FlsLoader_Lock() API is not selected. No functional impact*/
#define FlsLoader_Lock() ERROR_FlsLoader_Lock_API_IS_NOT_SELECTED

#endif

/* Enable / Disable the use of the function */
#if (FLSLOADER_LOCK_UNLOCK_API == STD_ON)
/*******************************************************************************
** Syntax           :  FlsLoader_ReturnType FlsLoader_UnLock(                 **
**                       const FlsLoader_AddressType TargetAddress,           **
**                       const FlsLoader_ValueType* const Password            **
**                    )                                                       **
**                                                                            **
** Service ID       : 0x34                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : Password  Pointer to the 4 double word (256 bit) UCB    **
**                    password of corresponding Flash to be unlocked.         **
**                    TargetAddress UCB address of corresponding Flash to     **
**                    be unlocked.                                            **
**                    0xAF402000 - PFlash UCB                                 **
**                    0xAF402200 - DFlash UCB                                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FLSLOADER_E_OK: Successful completion.                  **
**                    FLSLOADER_E_BUSY: Flash is busy with erase/write        **
**                    operation.                                              **
**                    FLSLOADER_E_NOT_OK: Returned when DET, Sequence error,  **
**                    Protection error.                                       **
**                                                                            **
** Description      : This function is used to unlock the internal PFlash and **
**                    DFlash 0 of the micro-controller from active protection.**
**                    It temporarily (until next controller reset) disables   **
**                    the current active read or write protection. A wrong    **
**                    password will result in protection error.               **
**                                                                            **
**                    - DFlash 0 can be unlocked from read and write          **
**                      protections.                                          **
**                    - PFlash can be unlocked from write protection. WOP and **
**                      OTP cannot be unlocked.                               **
*******************************************************************************/
extern FlsLoader_ReturnType FlsLoader_UnLock(
                                const FlsLoader_AddressType TargetAddress,
                                const FlsLoader_ValueType* const Password
                                    );

#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used for Error
 * Indication when FlsLoader_UnLock() API is not selected.
   No functional impact*/
#define FlsLoader_UnLock(TargetAddress,Password) \
                             ERROR_FlsLoader_UnLock_API_IS_NOT_SELECTED

#endif

#define FLSLOADER_STOP_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "FlsLoader_MemMap.h"

#endif
/* #ifndef FLSLOADER_H */
