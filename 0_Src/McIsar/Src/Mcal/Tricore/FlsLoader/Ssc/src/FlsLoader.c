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
**  FILENAME     : FlsLoader.c                                                **
**                                                                            **
**  VERSION      : 25.0.0                                                     **
**                                                                            **
**  DATE         : 2022-07-05                                                **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Flsloader Driver source file                               **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* [cover parentID={39989DCD-71A6-43d4-93AD-8BA52C4F3202}][/cover] */
/* [cover parentID={CE8CD855-9086-432d-AC76-FFCC5AFFABF9}][/cover] */
/* [cover parentID={2B88F8F8-2A90-4ca6-8FA5-A773B7C60765}]
FlsLoader file structure
[/cover] */

/* Inclusion of Flash header file */
#include "FlsLoader.h"

/* Inclusion of Flash header file */
#include "FlsLoader_Local.h"

/* Inclusion of header file for exclusive area. */
#include "FlsLdr_ExclArea.h"

/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/

/* [cover parentID={78569C2B-7DA9-42f1-AA7F-2E1E3570EFF1}][/cover] */
/* [cover parentID={BFF5DB8A-5CDC-4636-BBCB-70CB93080065}][/cover] */
/* Check for Driver Software Version */
#ifndef FLSLOADER_SW_MAJOR_VERSION
  #error "FLSLOADER_SW_MAJOR_VERSION is not defined. "
#endif

#ifndef FLSLOADER_SW_MINOR_VERSION
  #error "FLSLOADER_SW_MINOR_VERSION is not defined. "
#endif

#ifndef FLSLOADER_SW_PATCH_VERSION
  #error "FLSLOADER_SW_PATCH_VERSION is not defined. "
#endif

#if ( FLSLOADER_SW_MAJOR_VERSION != 20U )
  #error "FLSLOADER_SW_MAJOR_VERSION does not match. "
#endif

#if ( FLSLOADER_SW_MINOR_VERSION != 20U )
  #error "FLSLOADER_SW_MINOR_VERSION does not match. "
#endif

#if ( FLSLOADER_SW_PATCH_VERSION != 0U )
  #error "FLSLOADER_SW_PATCH_VERSION does not match. "
#endif

/* [cover parentID={F2DA6E09-440F-4213-92C6-ABCA48C046BC}][/cover] */
/* Check for DET Version Inclusion */
#if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)

#ifndef DET_AR_RELEASE_MAJOR_VERSION
  #error "DET_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#if ( DET_AR_RELEASE_MAJOR_VERSION != 4U )
  #error "DET_AR_RELEASE_MAJOR_VERSION does not match."
#endif

#endif /*#if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)*/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

#if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
/* Flash NULL */
#define FLSLOADER_NULL                  ((void *) 0)
#endif

#define FLSLOADER_NUM_5                 (5U)
#define FLSLOADER_NUM_32                (32U)
#define FLSLOADER_NUM_256               (256U)
#define FLSLOADER_NUM_8                 (8U)
#define FLSLOADER_NUM_3                 (3U)
#define FLSLOADER_ZERO_DATA             (0x00000000U)

#if (FLSLOADER_LOCK_UNLOCK_API == STD_ON)
#define FLSLOADER_UCB0                  (0x10U)
#define FLSLOADER_UCB1                  (0x11U)
#define FLSLOADER_PWD                   (8U)
#endif

/* (17*8)bytes UCB <P/D>FLASH content */
#define FLSLOADER_FLASH_TRAP_DIS        (0xC0000000U)
#define FLSLOADER_INTERRUPT_REG_CLR            (0U)
#define FLSLOADER_CRANKINGMODE_CTRL_REG_CLR    (0U)

#if ((FLSLOADER_DEINIT_API == STD_ON)\
     && (FLSLOADER_DEV_ERROR_DETECT == STD_ON))
#define FLSLOADER_UNINTIALIZED          (0U)
#endif

#if (FLSLOADER_DEINIT_API == STD_ON)
#define FLSLOADER_FLASH_TRAP_EN         (0x3FFFFFFFU)
#endif

#define FLSLOADER_WDT_PASSWORD_LOWER_MASK  ( 0x000000FCU )

/* mask for password Bits 8-15 */
#define FLSLOADER_WDT_PASSWORD_UPPER_MASK  ( 0x0000FF00U )

/* mask for password bits */
#define FLSLOADER_WDT_PASSWORD_MASK   \
                                    (FLSLOADER_WDT_PASSWORD_LOWER_MASK | \
                                     FLSLOADER_WDT_PASSWORD_UPPER_MASK)

#define FLSLOADER_WDT_RELOAD_MASK          ( 0xFFFF0000U )


/* mask for LCK and ENDINIT status bits */
#define FLSLOADER_WDT_STATUS_MASK          ( 0x00000003U )

/*Mask to check 4-byte alignment*/
#define FLSLOADER_ALIGN_4BYTE              ( 0x00000003U )

/*8-byte data size for load page command*/
#define FLSLOADER_LOAD_PAGE_8BYTE          ( 0x00000008U)

/*2-word size*/
#define FLDR_LOADPAGE_DATA_SIZE            ( 0x00000002U)

#define FLDR_LOADPAGE_CNT_PER_PF_BURST     (32U)
#define FLDR_LOADPAGE_CNT_PER_DF_BURST     (4U)
#define FLDR_LOADPAGE_CNT_PER_PF_PAGE      (4U)
#define FLDR_LOADPAGE_CNT_PER_DF_PAGE      (1U)

/*Indexes in byte array*/
#define FLDR_BYTE_1    (1u)
#define FLDR_BYTE_2    (2u)
#define FLDR_BYTE_3    (3u)
#define FLDR_BYTE_4    (4u)
#define FLDR_BYTE_5    (5u)
#define FLDR_BYTE_6    (6u)
#define FLDR_BYTE_7    (7u)

#define FLDR_WORD_0    (0U)
#define FLDR_WORD_1    (1U)

#define FLDR_SHIFT_8   (8u)
#define FLDR_SHIFT_16  (16u)
#define FLDR_SHIFT_24  (24u)

/*******************************************************************************
**                      Private function like Macros                          **
*******************************************************************************/

/*
  Function Like Macro:FlsLoader_lGetMode
  macro to get the kind of flash
  Input Parameters: FlashType
*/
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used for code
 * simplification and readability*/
#define FlsLoader_lGetMode(FlashType) (((FlashType)!=(FLSLOADER_DFLASH_BANK0)) \
                             ? (FLSLOADER_PFLASH_VAL) : (FLSLOADER_DFLASH_VAL))

/******************************************************************************
**                      Global Type Definitions                              **
******************************************************************************/
/******************************************************************************
**                      Private Type Definitions                             **
******************************************************************************/

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/******************************************************************************
**                      Private Variable Definitions                         **
******************************************************************************/
/* [cover parentID={C829DF02-56F2-4e35-8652-24A8516EF825}]
[/cover] */
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
[/cover] */
/* [cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
#define FLSLOADER_START_SEC_VAR_CLEARED_QM_LOCAL_8
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "FlsLoader_MemMap.h"
#if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
  uint8  FlsLoader_InitStatus;
#endif
#define FLSLOADER_STOP_SEC_VAR_CLEARED_QM_LOCAL_8
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "FlsLoader_MemMap.h"

/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond
   32 chars and this macro is used only inside the FLSLOADER module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond
   32 chars and this macro is used only inside the FLSLOADER module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond
   32 chars and this macro is used only inside the FLSLOADER module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond
   32 chars and this macro is used only inside the FLSLOADER module*/

/* [cover parentID={C829DF02-56F2-4e35-8652-24A8516EF825}]
[/cover] */
#define FLSLOADER_START_SEC_VAR_CLEARED_QM_LOCAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "FlsLoader_MemMap.h"
#if (FLSLOADER_CALLOUT_FUNC == STD_ON)
static uint32  FlsLoader_CalloutTick;
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond
   32 chars and this macro is used only inside the FLSLOADER module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond
   32 chars and this macro is used only inside the FLSLOADER module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond
   32 chars and this macro is used only inside the FLSLOADER module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond
   32 chars and this macro is used only inside the FLSLOADER module*/
#define FLSLOADER_STOP_SEC_VAR_CLEARED_QM_LOCAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "FlsLoader_MemMap.h"

/* [cover parentID={C829DF02-56F2-4e35-8652-24A8516EF825}]
[/cover] */
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
[/cover] */
/* [cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
#define FLSLOADER_START_SEC_WRITEERASE_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "FlsLoader_MemMap.h"
/*******************************************************************************
**                    Prototypes Of Local Functions                           **
*******************************************************************************/
LOCAL_INLINE void FlsLoader_lResetSafetyENDINIT(void);

LOCAL_INLINE void FlsLoader_lSetSafetyENDINIT(void);

LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lBurstWrite(
                            const FlsLoader_AddressType BurstOffSet,
                            const uint32 FlashType,
                            const uint8* const SourceAddressPtr,
                            const FlsLoader_AddressType TargetAddress,
                            const uint32 NumberOfBursts);

LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lPageWrite(
                           const FlsLoader_AddressType OffSet,
                           const uint32 FlashType,
                           const uint8* const SourceAddressPtr,
                           const FlsLoader_AddressType TargetAddress,
                           const uint32 NoOfPages);

LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lPageWriteCmdCycle(
                                   const FlsLoader_AddressType TargetAddress,
                                   const uint32 FlashType,
                                   const uint8* const SourceAddressPtr,
                                   const uint32 SrcAddrWordAlignFlag,
                                   const uint32 PageTimeoutTicks);

LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lBurstWriteCmdCycle(
                                   const FlsLoader_AddressType TargetAddress,
                                   const uint32 FlashType,
                                   const uint8* const SourceAddressPtr,
                                   const uint32 SrcAddrWordAlignFlag,
                                   const uint32 BurstTimeoutTicks);

LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lEraseCalcPhySector(
                                     const FlsLoader_AddressType TargetAddress,
                                     const uint32 FlashType,
                                     const FlsLoader_LengthType Length,
                                     const uint32 EraseTimeoutTicks);

LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lEraseCmdCycle(
                                     const FlsLoader_AddressType TargetAddress,
                                     const uint32 FlashType,
                                     const FlsLoader_LengthType Length,
                                     const uint32 EraseTimeoutTicks);

#define FLSLOADER_STOP_SEC_WRITEERASE_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "FlsLoader_MemMap.h"
/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/* [cover parentID={C829DF02-56F2-4e35-8652-24A8516EF825}]
[/cover] */
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
[/cover] */
/* [cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
/* Mapping the code */
#define FLSLOADER_START_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "FlsLoader_MemMap.h"

/*******************************************************************************
** Traceability     : [cover parentID={8B55ADF6-0F68-48bd-AC43-A83DD8F1E51C}] **
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
/*
  CD_FlsLoader028: This is the initialization function for FlsLoader.
*/
/* [cover parentID={181A7BBB-2982-4084-98B6-8B1D0702F1EB}][/cover] */
FlsLoader_ReturnType FlsLoader_Init(const FlsLoader_ConfigType* const Address)
{
  FlsLoader_ReturnType  RetError;
  uint32 EccControlValue;
  #if (FLSLOADER_DEV_ERROR_DETECT == STD_OFF)
  UNUSED_PARAMETER(Address);
  #endif

  #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)

  /* Init RetError to OK */
  RetError = FLSLOADER_E_OK;

  /* [cover parentID={AE6B22FB-B9AA-467b-8AFF-4D11E24B09A1}]
  DET Enabled
  [/cover] */
  /* [cover parentID={9D339296-731B-4789-9064-DA06CB20F527}]
  Is Config Pointer Null
  [/cover] */
  if ( Address != FLSLOADER_NULL )
  {
    /* [cover parentID={B5259F9E-76A6-4c21-A5E9-B33C2A42C4D5}]
    Report DET error FLSLOADER_E_PARAM_IGNORED
    [/cover] */
    /* Report FLSLOADER_E_PARAM_IGNORED DET */
    (void)Det_ReportError(FLSLOADER_MODULE_ID,
                        FLSLOADER_INSTANCE_ID,
                        FLSLOADER_SID_INIT,
                        FLSLOADER_E_PARAM_IGNORED);

    RetError = FLSLOADER_E_NOT_OK;
  }

  /*[cover parentID={97C3C3BB-F1B3-4688-91F9-0F30BE8083A2}]
    Is Return error E_OK and No DET detected
   [/cover] */
  if (RetError != FLSLOADER_E_NOT_OK)
  #endif /*FLSLOADER_DEV_ERROR_DETECT */
  {
    /* [cover parentID={98AA748F-7091-486b-B558-46A01709645B}]
    Check all PF banks are protected as OTP/WOP and set Return error to
    E_OK or E_ROM_VERSION [/cover] */
    RetError = FlsLoader_lCheckOTPWOP();

    /* Disable traps on Uncorrectable errors */
    EccControlValue = DMU_HF_ECCC.U | FLSLOADER_FLASH_TRAP_DIS;

    /* [cover parentID={C6A720B4-104A-4a12-828C-E6600FE866FA}]
    Disable traps on uncorrectable ECC errors
    [/cover] */
    /* Reset EndInit protection, Update HF_ECCC, Set EndInit protection */
    Mcal_WritePeripEndInitProtReg(&DMU_HF_ECCC.U, EccControlValue);

    /* Clear the following Error Interrupt masks */
    /* OPERM, SQERM, PROERM, PVERM, EVERM, EOBM */
    Mcal_WritePeripEndInitProtReg(&DMU_HF_EER.U, \
                                             FLSLOADER_INTERRUPT_REG_CLR);

    /*Disable Cranking mode*/
    Mcal_WritePeripEndInitProtReg(&DMU_HF_CCONTROL.U, \
                                     FLSLOADER_CRANKINGMODE_CTRL_REG_CLR);

    #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
    /* [cover parentID={69EBCA8F-5F07-43b9-AF66-5FD7CEB970A4}]
    DET enabled
    [/cover] */
    /* [cover parentID={C504C3CA-5DF6-4453-8F12-A4CD8A6CCF8A}]
    Set driver Init Status to Initialized
    [/cover] */
    FlsLoader_InitStatus = (uint8)FLSLOADER_INITIALIZED;
    #endif /*FLSLOADER_DEV_ERROR_DETECT*/

  }

  return RetError;
}  /* End of Fls_Loader_Init */

/*Preprocessor switch to enable/disable the API to deinitialze
FlsLoader. */
#if (FLSLOADER_DEINIT_API == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={3D2C9644-7F66-4b67-8170-689CD91CEDAE}] **
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
/*
CD_FlsLoader030: Service for FlsLaderDeInitialization
*/
FlsLoader_ReturnType FlsLoader_DeInit(void)
{
  FlsLoader_ReturnType  RetError;
  uint32 Fls0FsrCheck;
  uint32 EccControlValue;
  /* Init RetError to OK */
  RetError = FLSLOADER_E_OK;

  #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={644E8FE4-0E14-476b-8162-C7A7777C3832}]
    Is driver Initialized
    [/cover] */
  if (FlsLoader_InitStatus != FLSLOADER_INITIALIZED)
  {
    /* [cover parentID={D374E964-D3C0-4cfd-9E0B-45A44F040C2F}]
    DET Enabled
    [/cover] */
    /* [cover parentID={7D54A690-27BA-4b2b-8130-09A92D757A3B}]
    DET Enabled
    [/cover] */
    /* [cover parentID={2FAB51A9-3BBF-4c16-81DD-D7E6C1D376BF}]
    Report DET error
    [/cover] */
    /* FlsLoader not initialized,Report to DET*/
    (void)Det_ReportError ( FLSLOADER_MODULE_ID,
                          FLSLOADER_INSTANCE_ID,
                          FLSLOADER_SID_DEINIT,
                          FLSLOADER_E_UNINIT);
    RetError = FLSLOADER_E_NOT_OK;
  }

  /* [cover parentID={D527BB7D-8057-43c7-AAD5-0E3DA907D0BA}]
    No DET error found
    [/cover] */
  if (RetError != FLSLOADER_E_NOT_OK )
  #endif /* FLSLOADER_DEV_ERROR_DETECT */
  {
    /* Check for Flash Busy*/
    Fls0FsrCheck = (DMU_HF_STATUS.U & (uint32)(FLSLOADER_FLASH_BUSY_MASK));

    /* [cover parentID={D1F74F37-5764-423f-A263-A07AF6D379FF}]
    Flash is busy
    [/cover] */
    if (Fls0FsrCheck != FLSLOADER_NO_BUSY)
    {
      /* Report FLSLOADER_E_BUSY DET */
      RetError = FLSLOADER_E_BUSY;
      #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
      /* [cover parentID={D374E964-D3C0-4cfd-9E0B-45A44F040C2F}]
      DET Enabled
      [/cover] */
      /* [cover parentID={7D54A690-27BA-4b2b-8130-09A92D757A3B}]
      DET Enabled
      [/cover] */
      /* [cover parentID={4431BF96-8BCD-422a-81AA-856BCD45F8CE}]
      Report DET error FLSLOADER_E_BUSY
      [/cover] */
      (void)Det_ReportError( FLSLOADER_MODULE_ID,
                       FLSLOADER_INSTANCE_ID,
                       FLSLOADER_SID_DEINIT,
                       (uint8)FLSLOADER_E_BUSY);
      #endif /* FLSLOADER_DEV_ERROR_DETECT */
    }
    else
    {
      /* [cover parentID={5F68B74A-4CF4-4618-A92B-77445A5EF6E5}]
      Set driver Init Status to Uninitialized
      [/cover] */
      #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
      FlsLoader_InitStatus = (uint8)FLSLOADER_UNINTIALIZED;
      #endif /* FLSLOADER_DEV_ERROR_DETECT */

      /* [cover parentID={5C023713-7D02-470f-A744-E2D2381006FD}]
      Reset command sequence interpreter
      [/cover] */
      /* Reset to Read PFLASH, DFLASH (both banks) */
      FlsLoader_lCommandCycle(FLSLOADER_CYCLE_5554, FLSLOADER_VALUE_F0);

      /* Enable traps on Uncorrectable errors */
      EccControlValue = DMU_HF_ECCC.U & FLSLOADER_FLASH_TRAP_EN;

      /* [cover parentID={CF2F080E-984E-4021-98AD-7C578FE6839C}]
      Enable traps on uncorrectable ECC errors
      [/cover] */
      /* Reset EndInit protection, Update HF_ECCC, Set EndInit protection */
      Mcal_WritePeripEndInitProtReg(&DMU_HF_ECCC.U, EccControlValue);

    }

  }
  return RetError;
}  /*End of function FlsLoader_DeInit */
#endif  /*(FLSLOADER_DEINIT_API == STD_ON) */

#define FLSLOADER_STOP_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "FlsLoader_MemMap.h"

/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
[/cover] */
/* [cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
#define FLSLOADER_START_SEC_WRITEERASE_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "FlsLoader_MemMap.h"
/*******************************************************************************
** Traceability     : [cover parentID={51E5841D-93A2-4932-8422-482AC96EA332}] **
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
/* [cover parentID={1C9E98BF-0D08-482b-BE29-ACCC9BC81F63}][/cover] */
FlsLoader_ReturnType FlsLoader_Write(const FlsLoader_AddressType TargetAddress,
                                     const FlsLoader_LengthType Length,
                                     const uint8* const SourceAddressPtr)
{
  FlsLoader_ReturnType  RetError;
  FlsLoader_AddressType OffSet;
  FlsLoader_AddressType BurstOffSet;
  FlsLoader_AddressType TargetPageAddress;
  const uint8*          SourcePageAddress;
  uint32                FlashType;
  uint32                NumberOfBursts;
  uint32                FlsFsrCheck;
  uint32                BytesToWrite;
  uint32                NoOfPages;
  uint32                BurstLoadPageCount;

  /* Set start point for callout check */
  #if (FLSLOADER_CALLOUT_FUNC == STD_ON)
  /* [cover parentID={8138DEFF-76DD-4d55-85DB-DCC35906CD81}]
  Call out enabled
  [/cover] */
  /* [cover parentID={FDE6B2D1-7F35-40c1-9434-033A50B2231A}]
  Read and store STM ticks as base for next timeout checks for call out
  [/cover] */
  FlsLoader_CalloutTick = Mcal_DelayGetTick();
  #endif

  /*Block 1: DET Check */
  #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={85402662-1E01-4620-BFD6-8651934CD046}]
  DET Enabled
  [/cover] */
  RetError = FlsLoader_lWriteDetCheck(Length, TargetAddress);

  /* [cover parentID={1F65CC13-49DA-41dd-BD41-3FE4D3C89D22}]
    Is DET check successful
  [/cover] */
  if (RetError != FLSLOADER_E_NOT_OK)
  #endif /*FLSLOADER_E_NOT_OK*/
  {
    /*Check for Busy state of FLASH
    Registers differ between Checking of Busy state of PFlash and DFlash */
    FlsFsrCheck = (DMU_HF_STATUS.U & ((uint32)FLSLOADER_FLASH_BUSY_MASK));

    /* [cover parentID={543ED0F1-E764-4b9b-AE21-FF0A07B2847F}]
    Is flash busy
    [/cover] */
    if ( FlsFsrCheck != FLSLOADER_NO_BUSY)
    {
      /* Report FLSLOADER_E_BUSY DET */
      #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
      /* [cover parentID={22B1D13E-99F4-4413-A266-8D7E9CBCD6C4}]
      DET Enabled
      [/cover] */
      /* [cover parentID={7E159FD2-0929-41e8-BFBD-1C83AF86B022}]
      Report DET error FLSLOADER_E_BUSY
      [/cover] */
      (void)Det_ReportError(FLSLOADER_MODULE_ID,
                            FLSLOADER_INSTANCE_ID,
                            FLSLOADER_SID_WRITE,
                            (uint8)FLSLOADER_E_BUSY);
      #endif /*FLSLOADER_DEV_ERROR_DETECT*/
      RetError = FLSLOADER_E_BUSY;
    }
    /* [cover parentID={780987F4-C0E6-4e63-98CA-4CFA3B24EAF0}]
    Is Source address Null
    [/cover] */
    #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
    else if ( SourceAddressPtr == FLSLOADER_NULL)
    {
      /* [cover parentID={9C72BEF4-FDF7-47db-8068-00E98D7E2BBD}]
      DET Enabled
      [/cover] */
      /* [cover parentID={22B1D13E-99F4-4413-A266-8D7E9CBCD6C4}]
      DET Enabled
      [/cover] */
      /* [cover parentID={6B9AAAB4-BC11-4bb3-83A6-2A54360DB3BF}]
      Report DET error FLSLOADER_E_PARAM_ADDRESS
      [/cover] */
      (void)Det_ReportError(FLSLOADER_MODULE_ID,
                          FLSLOADER_INSTANCE_ID,
                          FLSLOADER_SID_WRITE,
                          FLSLOADER_E_PARAM_ADDRESS);

      RetError = FLSLOADER_E_NOT_OK;
    }
    #endif /*FLSLOADER_DEV_ERROR_DETECT*/
    else
    {
      /*PFLASH0*/
      /* Block 2: check the Flash Type DFLASH/PFLASH.
      If the Flash type is PFLASH check PMU0. */
      FlashType = FlsLoader_lGetFlashType(TargetAddress);
      /* Protection Installation check  */
      /* Preprocessor switch to enable/disable the lockcheck functionality */
      #if (FLSLOADER_ENABLE_LOCKCHECK == STD_ON)
      /* [cover parentID={F0F76068-2EE4-46f9-84A6-9BE8E6DA4BE8}]
      Lock check Enabled
      [/cover] */
      /* [cover parentID={ACF98D76-A9E3-4faf-8C55-97D7DEE80239}]
      Check if target sectors are locked
      [/cover] */
      RetError = FlsLoader_lFlashLockCheck(TargetAddress, FlashType, Length);

      /* [cover parentID={FB9F8D27-06ED-4181-9A35-E01F493FF4C6}]
      Are sectors locked
      [/cover] */
      if (FLSLOADER_E_OK == RetError) /*FLSLOADER_ENABLE_LOCKCHECK*/
      #endif
      {

        /* [cover parentID={8E72A66E-7D3D-4bf8-A43D-3B07776C8D23}]
        Is flash type PFlash
        [/cover] */
        /* Count the number of loops */
        if (FlashType != FLSLOADER_DFLASH_BANK0)
        {
          /* [cover parentID={C47359CC-136C-462a-8365-9549210D4524}]
          Is Target address 256 byte aligned
          [/cover] */
          /* PFlash */
          if((TargetAddress & FLSLOADER_MOD_256) == 0x00U)
          {
            NumberOfBursts  = Length >> FLSLOADER_SHIFT_BY_8; /*Divide by 256*/
          }
          else
          {
            NumberOfBursts = 0U;
          }
          BurstLoadPageCount = FLSLOADER_NUM_32;
          OffSet       = (FlsLoader_AddressType)FLSLOADER_NUM_32;
          BurstOffSet  = (FlsLoader_AddressType)FLSLOADER_NUM_256;
          BytesToWrite = (Length - (NumberOfBursts * FLSLOADER_NUM_256));
          NoOfPages    = (BytesToWrite >> FLSLOADER_SHIFT_BY_5);
        }
        else
        {
          /* [cover parentID={1CE32AEB-41D1-41aa-9590-7B73F7EFA70C}]
          Is Target address 32 byte aligned
          [/cover] */
          /* DFlash and UCB */
          if((TargetAddress & FLSLOADER_MOD_32) == 0x00U)
          {
            NumberOfBursts  = Length >> FLSLOADER_NUM_5; /*Divide by 32*/
          }
          else
          {
            NumberOfBursts = 0U;
          }
          BurstLoadPageCount = FLSLOADER_NUM_4;
          OffSet       = (FlsLoader_AddressType)FLSLOADER_NUM_8;
          BurstOffSet  = (FlsLoader_AddressType)FLSLOADER_NUM_32;
          BytesToWrite = (Length - (NumberOfBursts * FLSLOADER_NUM_32));
          NoOfPages    = (BytesToWrite >> FLSLOADER_SHIFT_BY_3);
        }

        /* Block 5: Execute the command sequence . */
        /* Disable and restore interrupts for critical
        command cycles. As there are 2 critical command cycles,
        the entire write operation is protected. */

        /* [cover parentID={D72D883C-4E11-4bb4-B9DE-31ED40CFB8DD}]
        Write in Burst Mode and return E_OK/E_NOT_OK
        [/cover] */
        RetError = FlsLoader_lBurstWrite(BurstOffSet,
                                         FlashType, SourceAddressPtr,
                                         TargetAddress, NumberOfBursts);
        /* [cover parentID={5539B416-48B1-4f87-AE34-43ED15911FC6}]
        Is Burst write successful and remaining number pages is not zero
        [/cover] */
        if ((RetError == FLSLOADER_E_OK) && (NoOfPages != 0U))
        {
          /* Write Remaining Pages */
          TargetPageAddress = TargetAddress;
          TargetPageAddress += (NumberOfBursts *
                                (BurstLoadPageCount << FLSLOADER_NUM_3));

          SourcePageAddress = (const uint8*)SourceAddressPtr;
          /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic is used to
          access user buffer efficiently*/
          SourcePageAddress += (NumberOfBursts *\
                                (BurstLoadPageCount << FLSLOADER_NUM_3));

          /* [cover parentID={5B04C7C2-A4E7-4b8b-9D7B-675A5BC74CBC}]
          Write Remaining Pages and return E_OK/E_NOT_OK
          [/cover] */
          RetError = FlsLoader_lPageWrite(OffSet, FlashType, SourcePageAddress,
                                          TargetPageAddress, NoOfPages);
        }
      }
    }
  }

  #if (FLSLOADER_CALLOUT_FUNC == STD_ON)
  /* [cover parentID={63DE31A9-8303-449b-8F4E-D65F59888EE2}]
  Call out enabled
  [/cover] */
  FlsLoader_CalloutTick = 0U;
  #endif

  return RetError;
}  /*End of function OCFLS_Write */
#define FLSLOADER_STOP_SEC_WRITEERASE_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "FlsLoader_MemMap.h"

/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
[/cover] */
/* [cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
#define FLSLOADER_START_SEC_WRITEERASE_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "FlsLoader_MemMap.h"
/*******************************************************************************
** Traceability     : [cover parentID={5AAA2584-E304-4bac-908A-44753FB02082}] **
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
/* Service to Erase a sector of Flash */
/* [cover parentID={A303F4CA-C13E-484a-A1F9-4D54BCB9557C}][/cover] */
FlsLoader_ReturnType FlsLoader_Erase(const FlsLoader_AddressType TargetAddress,
                                     const FlsLoader_LengthType Length )
{
  FlsLoader_ReturnType  RetError;
  FlsLoader_AddressType TargetEraseAddr;
  uint32                FlsFsrCheck;
  uint32                FlashType;
  uint32                EraseLenght;
  uint32                NoOfEraseCycle;
  uint32                LoopCount;
  uint32                EraseTimeoutTicks;
  uint32                TickResolution;

  #if ((FLSLOADER_DEV_ERROR_DETECT == STD_OFF) &&\
       (FLSLOADER_ENABLE_LOCKCHECK == STD_OFF))
  /*Init RetError to OK */
  RetError = FLSLOADER_E_OK;
  #endif

  /* [cover parentID={5314BC2D-895B-47bb-8919-14F6DAE482A6}]
  Call out enabled
  [/cover] */
  /*Set start point for callout check*/
  #if (FLSLOADER_CALLOUT_FUNC == STD_ON)
  /* [cover parentID={BF127E8D-CAD6-454c-81EE-9CBF244A6E76}]
  Read and store STM ticks as base for next timeout checks for call out
  [/cover] */
  FlsLoader_CalloutTick = Mcal_DelayGetTick();
  #endif

  /*Block 1: check DET */
  #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={154B3FC2-8CBC-4370-BB71-D768FFB4D219}]
  DET is enabled
  [/cover] */
  /* [cover parentID={DE2BABDB-0F37-4491-A0B0-D52B8667D55A}]
  Do DET check for Erase API
  [/cover] */
  RetError = FlsLoader_lEraseDetCheck(Length, TargetAddress);

  /* [cover parentID={9A1D28D2-8E38-4dbe-8FF8-A3F7BA0C85DA}]
  No DET errors found
  [/cover] */
  if (RetError == FLSLOADER_E_OK)
  #endif
  {
    /* Check for Busy state of FLASH
    Registers differ between Checking of Busy state of PFlash and DFlash */
    FlsFsrCheck = (DMU_HF_STATUS.U & ((uint32)FLSLOADER_FLASH_BUSY_MASK));

    /* [cover parentID={4F1DBAF0-D71A-4dd2-8E91-79E74B11DEC2}]
    Flash is busy
    [/cover] */
    if ( FlsFsrCheck != FLSLOADER_NO_BUSY)
    {
      /* Report FLSLOADER_E_BUSY DET */
      #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
      /* [cover parentID={ECFF0D77-0EF7-4822-A610-AD387430CC5D}]
      DET is enabled
      [/cover] */
      /* [cover parentID={0DB38384-61A2-495b-9CF8-A211489F3BE8}]
      Report DET error FLSLOADER_E_BUSY
      [/cover] */
      (void)Det_ReportError( FLSLOADER_MODULE_ID,
                           FLSLOADER_INSTANCE_ID,
                           FLSLOADER_SID_ERASE,
                           (uint8)FLSLOADER_E_BUSY);
      #endif
      RetError = FLSLOADER_E_BUSY;
    }
    else
    {
      /* [cover parentID={101F1D3E-25C6-4c10-8201-319ACFC29752}]
      FLash type is PFlash
      [/cover] */
      /* Extract the flash type */
      FlashType = FlsLoader_lGetFlashType (TargetAddress);

      /* Given Address belongs to Data FLASH */
      /*Check if the Target Address passed is UCB protected */
      /* Check if global write protection is installed in DFLASH*/
      /*Check if the Target Address passed is UCB protected */
      #if (FLSLOADER_ENABLE_LOCKCHECK == STD_ON)
      /* [cover parentID={8946BC7B-3AB7-423d-A494-9BDB1356C01B}]
      Lock check Enabled
      [/cover] */

      /* [cover parentID={FD2643AE-83DE-405e-B777-F7750AF48F9B}]
      Check if target sectors are locked
      [/cover] */
      /* Protection Check Algorithm */
      /* Preprocessor switch to enable/disable the lockcheck functionality */
      /* Check if global write protection is installed */
      RetError = FlsLoader_lEraseLockCheck (TargetAddress, FlashType, Length);

      /* [cover parentID={D9039774-7BDA-4442-A6B7-96FA7FFBEE6D}]
      Are sectors locked
      [/cover] */
      if (RetError == FLSLOADER_E_OK)
      #endif
      {

        /* [cover parentID={1F89A37C-3B0F-4753-94DC-CDCE85541266}]
        Calculate number of STM counts required for maximum time per page
        write for given Flash type (PFlash or DFlash)
        [/cover] */
        /*STM count resolution in ns*/
        TickResolution = Mcal_DelayTickResolution();

        /* [cover parentID={1F89A37C-3B0F-4753-94DC-CDCE85541266}]
        Calculate number of STM counts required for maximum time per page
        write for given Flash type (PFlash or DFlash)
        [/cover] */
        if(FlashType != FLSLOADER_DFLASH_BANK0)
        {
          /*STM counts for given max PF erase time per command*/
          EraseTimeoutTicks = (uint32)\
                             (FLSLOADER_MAX_TIME_PER_PF_ERASE / TickResolution);

          /*Add 10% additional buffer from software*/
          EraseTimeoutTicks += (uint32)(EraseTimeoutTicks / FLSLOADER_DIV_10);
        }
        else
        {
          /*STM counts for given max DF erase time per command*/
          EraseTimeoutTicks = (uint32)\
                             (FLSLOADER_MAX_TIME_PER_DF_ERASE / TickResolution);

          /*Add 50% DF hardware worst case scenario*/
          EraseTimeoutTicks += (EraseTimeoutTicks >> FLSLOADER_NUM_1);

          /*Add 10% additional buffer from software*/
          EraseTimeoutTicks += (uint32)(EraseTimeoutTicks / FLSLOADER_DIV_10);
        }

        /* [cover parentID={101F1D3E-25C6-4c10-8201-319ACFC29752}]
        FLash type is PFlash
        [/cover] */
        /*Calculate no. of erase loops need to be performed*/
        if(FlashType != FLSLOADER_DFLASH_BANK0)
        {
          /*No. of 256kb loops for PFlash*/
          NoOfEraseCycle = ((uint32)((Length - 1U) / \
                                     FLSLOADER_MAX_PF_ERASE_SECTORS_16)) + 1U;

          /*Set erase length to 16 sectors or 256kb*/
          EraseLenght = FLSLOADER_MAX_PF_ERASE_SECTORS_16;
        }
        else
        {
          /*No. of 256kb loops for DFlash*/
          NoOfEraseCycle = ((uint32)((Length - 1U) / \
                                     FLSLOADER_MAX_DF_ERASE_SECTORS_64)) + 1U;

          /*Set erase lenght to 64 sectors or 256kb*/
          EraseLenght = FLSLOADER_MAX_DF_ERASE_SECTORS_64;
        }

        /*Copy the given erase address*/
        TargetEraseAddr = TargetAddress;

        /* [cover parentID={EDE895E0-02D2-4b44-99AF-E09E296A4C16}]
        Execut erase for calculated number of erase cycles
        [/cover] */
        for(LoopCount = 0U; LoopCount < NoOfEraseCycle; LoopCount++)
        {
          /*Calculate remaining secotrs lenght for last loop*/
          if(LoopCount == (NoOfEraseCycle - 1U))
          {
            /*Last loop Lenght is less than 32 or 64*/
            if((Length % EraseLenght) != 0U)
            {
              /*Extract remaining Lenght*/
              EraseLenght = Length % EraseLenght;
            }
          }

          /* [cover parentID={0435E69B-FFF5-4e03-AA58-4855EB678102}]
          Execute the erase operation for given erase length and store status
          [/cover] */
          /*Erase the sectors for the physical bank*/
          RetError |= FlsLoader_lEraseCalcPhySector(TargetEraseAddr, \
                      FlashType, EraseLenght, EraseTimeoutTicks);

          /* [cover parentID={0435E69B-FFF5-4e03-AA58-4855EB678102}]
          Execute the erase operation for given erase length and store status
          [/cover] */
          if(FlashType != FLSLOADER_DFLASH_BANK0)
          {
            /*Increment erase address by 256kb for PFlash*/
            TargetEraseAddr = TargetEraseAddr + \
                         (FLSLOADER_MAX_PF_ERASE_SECTORS_16*FLSLOADER_SIZE_16K);
          }
          else
          {
            /*Increment erase address by 256kb for DFlash*/
            TargetEraseAddr = TargetEraseAddr + \
                         (FLSLOADER_MAX_DF_ERASE_SECTORS_64*FLSLOADER_SIZE_4K);
          }
        }
      }
    }
  }

  /* [cover parentID={EBE0C92B-870B-43a5-A26A-A88CFADEA443}]
  Call out enabled
  [/cover] */
  #if (FLSLOADER_CALLOUT_FUNC == STD_ON)
  FlsLoader_CalloutTick = 0U;
  #endif

  return RetError;
}  /* End of Function */
#define FLSLOADER_STOP_SEC_WRITEERASE_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "FlsLoader_MemMap.h"

/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
[/cover] */
/* [cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
#define FLSLOADER_START_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "FlsLoader_MemMap.h"

/* Preprocessor switch to enable/disable the FlsLoader_Lock API */
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
/* [cover parentID={FF762F42-A404-4fc9-830E-EFB62C07B7B5}][/cover] */
FlsLoader_ReturnType FlsLoader_Lock(void)
{
  uint32                FlashBusy;
  FlsLoader_ReturnType  RetError ;
  uint32                PfProtDis;
  uint32                DfProtDis;
  uint32                PUcbOState;
  uint32                PUcbCState;
  uint32                DUcbOState;
  uint32                DUcbCState;
  FlsLoader_ReturnType  RetPf;      /*Access state of PF UCB*/
  FlsLoader_ReturnType  RetDf;      /*Access state of DF UCB*/
  FlsLoader_ReturnType  RetOtp;     /*Status of OTP UCB after programmed*/
  FlsLoader_ReturnType  RetStatDf;  /*Status of DF UCB after programmed*/
  FlsLoader_ReturnType  RetStatPf;  /*Status of PF UCB after programmed*/

  RetError = FLSLOADER_E_OK;

  /*Set start point for callout check*/
  #if (FLSLOADER_CALLOUT_FUNC == STD_ON)
  /* [cover parentID={DB7767A2-C098-4c6f-9B17-30632AB0399A}]
  Call out enabled
  [/cover] */
  /* [cover parentID={5C0F9614-07AE-442b-8B88-0B20A186A671}]
  Read and store STM ticks as base for next timeout checks for call out
  [/cover] */
  FlsLoader_CalloutTick = Mcal_DelayGetTick();
  #endif

  #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={F0830A48-0774-4e21-A667-F7A18F576826}]
  DET is enabled
  [/cover] */
  /* [cover parentID={926AAB26-BF6A-4baa-AD78-07DD7178C11F}]
  Is driver Initialized
  [/cover] */
  if (FlsLoader_InitStatus != FLSLOADER_INITIALIZED)
  {
    /* [cover parentID={ED31DC86-545F-4c82-9264-76F820F128A9}]
    Reprot DET error FLSLOADER_E_UNINIT
    [/cover] */
    /* Report missing initialization to DET */
    (void)Det_ReportError(FLSLOADER_MODULE_ID,
                        FLSLOADER_INSTANCE_ID,
                        FLSLOADER_SID_LOCK,
                        FLSLOADER_E_UNINIT);
    RetError = FLSLOADER_E_NOT_OK;
  }

  if (RetError == FLSLOADER_E_OK)
  #endif
  {
    /* (FLSLOADER_DEV_ERROR_DETECT == STD_ON) */

    /* Check if PFLASH or DFLASH is busy */
    FlashBusy = (uint32)(DMU_HF_STATUS.U & FLSLOADER_FLASH_BUSY_MASK);

    /* [cover parentID={299866E2-15C7-4075-8B5F-7EDB56D59826}]
    Is flash Busy
    [/cover] */
    if (FlashBusy != FLSLOADER_ZERO_DATA)
    {
      /* Report Flash Busy to DET */
      RetError = FLSLOADER_E_BUSY;
      #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
      /* [cover parentID={BD33167D-332C-4764-89F8-6BDE7BB70992}]
      DET is enabled
      [/cover] */
      /* [cover parentID={A76BECCB-AEF5-4f7c-A279-ACA22EF76DA9}]
      Report DET error FLSLOADER_E_BUSY
      [/cover] */
      (void)Det_ReportError(FLSLOADER_MODULE_ID,
                          FLSLOADER_INSTANCE_ID,
                          FLSLOADER_SID_LOCK,
                          (uint8)FLSLOADER_E_BUSY);
      #endif    /*(FLSLOADER_DEV_ERROR_DETECT == STD_ON)*/
    }
    /* Protection should not be installed for the corresponding user level.*/
    if (RetError == FLSLOADER_E_OK)
    {
      /* Global flash protection disable status for PF and DF0*/
      PfProtDis = DMU_HF_PROTECT.B.PRODISP;
      DfProtDis = DMU_HF_PROTECT.B.PRODISD;

      /* Confirm states of PFLASH ORIG and COPY UCBs*/
      PUcbOState = DMU_HF_CONFIRM1.B.PROINPO;
      PUcbCState = DMU_HF_CONFIRM1.B.PROINPC;

      /* Confirm states of DFLASH ORIG and COPY UCBs*/
      DUcbOState = DMU_HF_CONFIRM1.B.PROINDO;
      DUcbCState = DMU_HF_CONFIRM1.B.PROINDC;

      /*Initialize UCB program status to E_OK*/
      RetStatPf = FLSLOADER_E_OK;
      RetStatDf = FLSLOADER_E_OK;

      /* [cover parentID={DA8015B3-CDDC-4612-93CF-6770FA0B797B}][/cover] */
      /*Evaluate if PF UCB can be locked or not*/
      RetPf = FlsLoader_lEvalUcbState(PUcbOState, PUcbCState, PfProtDis);

      /* [cover parentID={C9A7F361-EE6A-4702-B9AD-1C63614FC700}][/cover] */
      /*Evaluate if DF UCB can be locked or not*/
      RetDf = FlsLoader_lEvalUcbState(DUcbOState, DUcbCState, DfProtDis);

      /* [cover parentID={67B2D717-2C65-4e0c-8B49-C79A03F01F5B}][/cover] */
      /* Check if PF UCB can be locked */
      if(RetPf == FLSLOADER_E_OK)
      {
        /* [cover parentID={80A3F917-EBB9-451e-9560-55B12B941F97}][/cover] */
        /*Lock PF UCB*/
        RetStatPf |= FlsLoader_lLock(FLSLOADER_UCB_PFLASH);
      }

      /* [cover parentID={C3AF68EA-AF46-4895-A74C-84F9A504ECD1}][/cover] */
      /* Check if DF UCB can be locked */
      if(RetDf == FLSLOADER_E_OK)
      {
        /* [cover parentID={B7190931-1D15-413a-85A5-EAEEE2FD7095}][/cover] */
        /*Lock DF UCB*/
        RetStatDf |= FlsLoader_lLock(FLSLOADER_UCB_DFLASH);
      }

        /* [cover parentID={BD74FB67-AF73-425b-A14F-6A80362DEEEA}]
        [/cover] */
        RetOtp = FlsLoader_lLock(FLSLOADER_UCB_OTP);

      /* [cover parentID={C883B003-AFB4-47b8-A444-49258FBF6EA3}][/cover] */
      /* Check if all the UCBs are already locked */
      if((RetPf == FLSLOADER_E_LOCKED) && \
          (RetDf == FLSLOADER_E_LOCKED) && \
          (RetOtp == FLSLOADER_E_LOCKED))
      {
        RetError = FLSLOADER_E_LOCKED;
      }
      else
      {
        /* [cover parentID={A3E45065-D921-4dc4-B238-94442BAAF97C}][/cover] */
        /*Check if anyone of the UCB lock procedure reported failure */
        if((RetStatPf == 1U) || (RetStatDf == 1U) || (RetOtp == 1U))
        {
          RetError = FLSLOADER_E_NOT_OK;
        }
        else
        {
          /*Atleast one ucb is programmed successfully*/
          RetError = FLSLOADER_E_OK;
        }
      }
    }
  }
  /*Reset the call-out timer*/
  #if (FLSLOADER_CALLOUT_FUNC == STD_ON)
  /* [cover parentID={1B233333-A14D-4904-9E6E-24475A190F4D}]
  Call out enabled
  [/cover] */
  FlsLoader_CalloutTick = 0;
  #endif

  return RetError;
}  /* End of function FlsLoader_Lock */
#endif  /*(FLSLOADER_LOCK_UNLOCK_API == STD_ON) */


#if (FLSLOADER_LOCK_UNLOCK_API == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={24FB8005-B151-4f2f-A6D6-C0F186FF2DC6}] **
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
/* [cover parentID={E02D320C-3065-40a8-8F8F-4DD6D0A06C5D}][/cover] */
FlsLoader_ReturnType FlsLoader_UnLock(
                                const FlsLoader_AddressType TargetAddress,
                                const FlsLoader_ValueType* const Password
                                    )
{
  FlsLoader_ReturnType   RetError ;
  uint32                 FlsErrCheck;
  uint32                 FlsBusyStat;
  uint32                 FlsFpro;
  uint32                 FlsFprodisd;
  uint8                  UserConfig;
  uint8                  Index;

  /* Init RetError to OK */
  RetError = FLSLOADER_E_OK ;

  #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={E5097B9A-3036-408a-B630-6FCAE7CA3245}]
    Is driver Initialized
    [/cover] */
  if (FlsLoader_InitStatus != FLSLOADER_INITIALIZED)
  {
    /* [cover parentID={3D4187BF-C14B-4e7e-8725-FA0EBEACB8D5}]
    DET Enabled
    [/cover] */
    /* [cover parentID={DA626ADA-ED69-4c35-B084-E7237B27B304}]
    Report DET error FLSLOADER_E_UNINIT
    [/cover] */
    /*  Report missing initialization to DET */
    (void)Det_ReportError(FLSLOADER_MODULE_ID,
                        FLSLOADER_INSTANCE_ID,
                        FLSLOADER_SID_UNLOCK,
                        FLSLOADER_E_UNINIT);
    RetError = FLSLOADER_E_NOT_OK;
  }
  /* [cover parentID={48A95ABB-6470-47f3-B4DD-5E1EFB9D3D7D}]
  Password pointer is Null
  [/cover] */
  else if (Password == FLSLOADER_NULL)
  {
    /* [cover parentID={3E1CF154-4A4F-4f68-AF62-C463F0C80792}]
    DET Enabled
    [/cover] */
    /* [cover parentID={BAB56FB9-040D-459d-AAC5-4E451683E416}]
    Report DET error FLSLOADER_E_PARAM_ADDRESS
    [/cover] */
    /*Null pointer passed for password input*/
    (void)Det_ReportError(FLSLOADER_MODULE_ID,
                        FLSLOADER_INSTANCE_ID,
                        FLSLOADER_SID_UNLOCK,
                        FLSLOADER_E_PARAM_ADDRESS);

    RetError = FLSLOADER_E_NOT_OK;
  }
  else
  {
    /* [cover parentID={E2384B55-300D-43b3-A210-8A7B700E727B}]
    Is Target address belongs to either of UCB_PFLASH_ORIG and  UCB_DFLASH_ORIG
    [/cover] */
    if (TargetAddress != FLSLOADER_UCB_PFLASH_ORGINAL_START)
    {
      /* [cover parentID={E2384B55-300D-43b3-A210-8A7B700E727B}]
      Is Target address belongs to either of UCB_PFLASH_ORIG and UCB_DFLASH_ORIG
      [/cover] */
      if (TargetAddress != FLSLOADER_UCB_DFLASH_ORIGINAL_START)
      {
        /* [cover parentID={3E1CF154-4A4F-4f68-AF62-C463F0C80792}]
        DET Enabled
        [/cover] */
        /* [cover parentID={BAB56FB9-040D-459d-AAC5-4E451683E416}]
        Report DET error FLSLOADER_E_PARAM_ADDRESS
        [/cover] */
        (void)Det_ReportError(FLSLOADER_MODULE_ID,
                            FLSLOADER_INSTANCE_ID,
                            FLSLOADER_SID_UNLOCK,
                            FLSLOADER_E_PARAM_ADDRESS);
        RetError = FLSLOADER_E_NOT_OK;
      }
    }
  }

  if (RetError != FLSLOADER_E_NOT_OK)
  #endif
  {
    /* #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON) */

    /* PROTECTION in PFLASH  */
    if ( TargetAddress == FLSLOADER_UCB_PFLASH_ORGINAL_START )
    {
      /* PROTECTION in PFLASH  */
      UserConfig = FLSLOADER_UCB0;
    }
    else
    {
      /* PROTECTION in DFLASH  */
      UserConfig = FLSLOADER_UCB1;
    }

    FlsBusyStat = (uint32)(DMU_HF_STATUS.U & (uint32)FLSLOADER_FLASH_BUSY_MASK);

    /* [cover parentID={DA28B7D2-4299-484a-BE85-E364B6AE0810}]
    Is flash Busy
    [/cover] */
    if (FlsBusyStat != 0U)
    {
      /* Report Pflash busy to DET */
      #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
      /* [cover parentID={3E1CF154-4A4F-4f68-AF62-C463F0C80792}]
      DET Enabled
      [/cover] */
      /* [cover parentID={4DD01DA2-DCA5-472b-A2DB-FC2032E06D83}]
      Report DET error FLSLOADER_E_BUSY
      [/cover] */
      (void)Det_ReportError(FLSLOADER_MODULE_ID,
                          FLSLOADER_INSTANCE_ID,
                          FLSLOADER_SID_UNLOCK,
                          (uint8)FLSLOADER_E_BUSY);
      #endif
      RetError = FLSLOADER_E_BUSY;
    }
    if (RetError == FLSLOADER_E_OK)
    {
      /* Clear error and status flags*/
      FlsLoader_lCommandCycle(FLSLOADER_CYCLE_5554, FLSLOADER_VALUE_FA);

      /* cycle 1 */
      FlsLoader_lCommandCycle(FLSLOADER_CYCLE_553C, UserConfig);

      /* [cover parentID={82A1E143-9A39-4a72-A9F0-3731EC250C8D}]
      Disable the password protection for the selected UCB
      [/cover] */
      /* Cycle 2 to Cycle 9 : Passwords for disabling protection */
      for(Index = (uint8)0U; Index < (uint8)FLSLOADER_PWD; Index++)
      {
        /* provide 8 passwords */
        FlsLoader_lCommandCycle(FLSLOADER_CYCLE_553C, Password[Index]);

      }

      /* [cover parentID={3AA0B378-3526-4d8f-AFC6-BF72BF34FBFF}]
      Check for any errors while disabling the protection
      [/cover] */
      if (UserConfig == FLSLOADER_UCB0)
      {
        /* [cover parentID={3AA0B378-3526-4d8f-AFC6-BF72BF34FBFF}]
        Check for any errors while disabling the protection
        [/cover] */
        /*Check if there are no protection and sequence errors*/
        FlsErrCheck = FlsLoader_lProtSeqOperErrorCheck();
        /* Check if PFlash Protection is Disabled*/
        FlsFpro     = DMU_HF_PROTECT.B.PRODISP;

        /* [cover parentID={A2B09D23-0845-4a70-8EC0-0BEDC4166547}]
        No execution errors and global flash protection disabled for
        the selected UCB
        [/cover] */
        /* return if protection is not disabled or if there are errors */
        if ((FlsFpro == 0U) || (FlsErrCheck == FLSLOADER_E_NOT_OK))
        {
          /* return if protection is not disabled or if there are errors */
          RetError = FLSLOADER_E_NOT_OK;
        }
      }
      else
      {
        /* [cover parentID={3AA0B378-3526-4d8f-AFC6-BF72BF34FBFF}]
        Check for any errors while disabling the protection
        [/cover] */
        /*Check if there are no protection and sequence errors*/
        FlsErrCheck = FlsLoader_lProtSeqOperErrorCheck();
        /* Check if DFlash Protection is Disabled*/
        FlsFprodisd = DMU_HF_PROTECT.B.PRODISD;

        /* [cover parentID={A2B09D23-0845-4a70-8EC0-0BEDC4166547}]
        No execution errors and global flash protection disabled for
        the selected UCB
        [/cover] */
        /* return if protection is not disabled or if there are errors */
        if ((FlsFprodisd == 0U) || (FlsErrCheck == FLSLOADER_E_NOT_OK))
        {
          /* return if protection is not disabled or if there are errors */
          RetError = FLSLOADER_E_NOT_OK;
        }
      }

      /* Clear error and status flags.*/
      FlsLoader_lCommandCycle(FLSLOADER_CYCLE_5554, FLSLOADER_VALUE_FA);
    }
  }
  return RetError;
}
#endif  /* if (FLSLOADER_LOCK_UNLOCK_API == STD_ON)    */

#define FLSLOADER_STOP_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "FlsLoader_MemMap.h"
/* Inline Functions */

#define FLSLOADER_START_SEC_WRITEERASE_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "FlsLoader_MemMap.h"

/*******************************************************************************
** Syntax           : LOCAL_INLINE void FlsLoader_lResetSafetyENDINIT         **
**                    (                                                       **
**                      void                                                  **
**                    )                                                       **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : This function resets the safety end init flag.          **
** When FLsLoader driver is executing write or erase, it is assumed that      **
** there are no other tasks running in parallel or from another core that     **
** requires the service of safety WDG endinit function.                       **
** Password sequencing will not be enabled and not checked within this        **
** function, also Time based check is not enabled                             **
**                                                                            **
*******************************************************************************/
/* [cover parentID={FB68BDED-7A5B-4750-B1AB-BAE70A108E94}][/cover] */
/* [cover parentID={40129362-40C8-4d07-A9AD-7C3B633E96FF}][/cover] */
LOCAL_INLINE void FlsLoader_lResetSafetyENDINIT(void)
{
  uint32 NewValCon0;
  uint32 NewPw;                   /* next password to be used */
  uint32 NewRel;                  /* next reload value to be used */

  uint32 Result;

  /* Safety Wdg register is acquired */
  /*MISRA2012_RULE_19_2_JUSTIFICATION: Union used for register type
       definition */
  /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
  volatile Ifx_SCU_WDTS_CON0* ScuWdtcon0Ptr = &SCU_WDTS_CON0;

  /* save old value */
  NewValCon0  = SCU_WDTS_CON0.U;

  /* get valid next password */
  Result = NewValCon0 & FLSLOADER_WDT_PASSWORD_MASK;
  Result = ( Result & FLSLOADER_WDT_PASSWORD_UPPER_MASK) |
           ((~(Result & FLSLOADER_WDT_PASSWORD_LOWER_MASK))
            & FLSLOADER_WDT_PASSWORD_LOWER_MASK );

  /* password sequencing will not be enabled at this time,
  no need for the run time calculation of password */
  NewPw = Result;
  /* get valid next timer reload */
  Result = NewValCon0 & FLSLOADER_WDT_RELOAD_MASK;
  /* Time control enable shall not be enabled by the system */
  NewRel = Result;
  /* build required password WDTCON0 value */
  NewValCon0 =  ( (NewRel) |              /* new reload value  */
                  (NewPw)  |              /* new Password */
                  (1u) );                 /* Clear LCK, keep ENDINIT set */

  ScuWdtcon0Ptr->U  = NewValCon0;        /* password access to unlock */

  NewValCon0 &= ~ FLSLOADER_WDT_STATUS_MASK;/*clear ENDINIT and LCK Bit */
  NewValCon0 |= FLSLOADER_NUM_2;                    /* set LCK Bit */

  ScuWdtcon0Ptr->U = NewValCon0;  /* write access and lock for Timeout mode */
}

/*******************************************************************************
** Traceability     :                                                         **
** Syntax           : void FlsLoader_lSetSafetyENDINIT                        **
**                    (                                                       **
**                      void                                                  **
**                    )                                                       **
**                                                                            **
** Service ID       :   NA                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : none                                                    **
**                                                                            **
** Parameters (out) :                                                         **
** Return value     : void                                                    **
**                                                                            **
** Description      : This function sets  the safety end init flag.           **
** When FLsLoader driver is executing write or erase, it is assumed that      **
** there are no other tasks running in parallel or from another core that     **
** requires the service of safety WDG endinit function.                       **
**                                                                            **
*******************************************************************************/
/* [cover parentID={5B748F96-935C-4dde-8B74-3E685B846DB1}][/cover] */
/* [cover parentID={F8A9A22F-D946-4583-AFFC-23CFD749278B}][/cover] */
LOCAL_INLINE void FlsLoader_lSetSafetyENDINIT(void)
{
  uint32 NewValCon0;
  uint32 NewPw;                   /* next password to be used */
  uint32 NewRel;                  /* next timer reload to be used */
  uint32 Result;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: Union used for register type
       definition */
  /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
  volatile Ifx_SCU_WDTS_CON0* ScuWdtcon0Ptr = &SCU_WDTS_CON0;

  /* save old value */
  NewValCon0  = SCU_WDTS_CON0.U;

  Result = NewValCon0 & FLSLOADER_WDT_PASSWORD_MASK;
  Result = ( Result & FLSLOADER_WDT_PASSWORD_UPPER_MASK) |
           ((~(Result & FLSLOADER_WDT_PASSWORD_LOWER_MASK))
            & FLSLOADER_WDT_PASSWORD_LOWER_MASK );
  NewPw = Result;

  Result = NewValCon0 & FLSLOADER_WDT_RELOAD_MASK;
  NewRel = Result;
  /* build required password WDTCON0 value */
  NewValCon0  =  ( (NewRel) |             /* new reload value  */
                   (NewPw)  |             /* new Password */
                   (1u) );                /* Clear LCK, keep ENDINIT set */

  /*  unlock with password access */
  SCU_WDTS_CON0.U   = NewValCon0;
  /* clear timer reload and restore saved and corrected reload value */

  /* clear ENDINIT and LCK Bit*/
  NewValCon0 &= ~FLSLOADER_WDT_STATUS_MASK;

  /* set LCK and ENDINIT Bit */
  NewValCon0 |= FLSLOADER_NUM_3;

  /* write modify access and lock */
  ScuWdtcon0Ptr->U = NewValCon0;

}

/*******************************************************************************
** Syntax           : LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lBurstWrite(**
**                            const FlsLoader_AddressType BurstOffSet,        **
**                            const uint32 FlashType,                         **
**                            const uint8* const SourceAddressPtr,            **
**                            const FlsLoader_AddressType TargetAddress,      **
**                            const uint32 NumberOfBursts)                    **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : BurstOffSet: Offset to increment Target address to next **
**                      burst write                                           **
**                    FlashType: Flash bank number (DFlash0, PFlash0 to       **
**                      PFlash5)                                              **
**                    NumberofBursts: Number of bursts to be executed         **
**                    SourceAddressPtr: Pointer to source data buffer         **
**                    TargetAddress: Target address in Flash                  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FLSLOADER_E_OK: Burst writes executed successfully.     **
**                    FLSLOADER_E_NOT_OK: Burst writes failed. Protection,    **
**                    sequence, operation or program verification error has   **
**                    occurred.                                               **
**                                                                            **
** Description      : This function writes the data to PFlash or DFlash in    **
**                    burst mode.                                             **
*******************************************************************************/
/* [cover parentID={898DA933-BF9F-419b-A9A9-7E8D36C675F8}][/cover] */
LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lBurstWrite(
                            const FlsLoader_AddressType BurstOffSet,
                            const uint32 FlashType,
                            const uint8* const SourceAddressPtr,
                            const FlsLoader_AddressType TargetAddress,
                            const uint32 NumberOfBursts)
{
  FlsLoader_ReturnType           RetError;
  uint32                         Count;
  uint32                         TickResolution;
  uint32                         BurstTimeoutTicks;
  const uint8*                   SourceAddress;
  uint32                         SrcAddrWordAlignFlag;

  FlsLoader_AddressType TargetFlashAddress = TargetAddress;

  /* [cover parentID={5B791FEA-2086-4af5-A65B-579756B07BDC}]
     Calculate number of STM counts required for maximum time per burst
   write for given Flash type (PFlash or DFlash)
   [/cover] */
  /*STM count resolution in ns*/
  TickResolution = Mcal_DelayTickResolution();

  /* [cover parentID={5B791FEA-2086-4af5-A65B-579756B07BDC}]
   Calculate number of STM counts required for maximum time per burst
   write for given Flash type (PFlash or DFlash)
  [/cover] */
  if(FlashType != FLSLOADER_DFLASH_BANK0)
  {
    /*STM counts for given max PF burst time*/
    BurstTimeoutTicks = (uint32)\
                        (FLSLOADER_MAX_TIME_PER_PF_BURST / TickResolution);
  }
  else
  {
    /*STM counts for given max DF burst time*/
    BurstTimeoutTicks = (uint32)\
                        (FLSLOADER_MAX_TIME_PER_DF_BURST / TickResolution);
  }

  /*Add 10% additional buffer from software*/
  BurstTimeoutTicks += (uint32)(BurstTimeoutTicks / FLSLOADER_DIV_10);

  RetError = FLSLOADER_E_OK;

  /* [cover parentID={A74A1291-2EFA-4ba8-99F9-15B3F01C1C00}]
     Check if the source address is aligned with the 4 byte
     boundary and if not set a flag
     [/cover] */
  /*Check word alignment of Source address*/
  /* MISRA2012_RULE_11_4_JUSTIFICATION: Pointer conversion is required for
     the comparision of pointer value with an integer */
  /* MISRA2012_RULE_11_6_JUSTIFICATION: Pointer conversion is required for
     the comparision of pointer value with an integer */
  if (((uint32)SourceAddressPtr & FLSLOADER_ALIGN_4BYTE) == FALSE)
  {
    /*SA is aligned to word boundary, set flag to true*/
    SrcAddrWordAlignFlag = TRUE;
  }
  else
  {
    /*SA is not aligned to word boundary, set flag to true*/
    SrcAddrWordAlignFlag = FALSE;
  }

  SourceAddress = SourceAddressPtr;

  /* [cover parentID={DD03D090-924F-437b-BB52-EC0909D7D739}]
    Loop to perform requested number of burst writes
   [/cover] */
  /* [cover parentID={F3420D36-A2CA-492d-8525-B515644AA3FE}]
   Loop to perform requested number of burst writes
  [/cover] */
  for (Count = 0U;
       (Count < NumberOfBursts) && (RetError == FLSLOADER_E_OK);
       Count++)
  {

    /* Clear error and status flags*/
    FlsLoader_lCommandCycle(FLSLOADER_CYCLE_5554, FLSLOADER_VALUE_FA);

    /* Enter the Page Mode */
    FlsLoader_lCommandCycle(FLSLOADER_CYCLE_5554, \
                            FlsLoader_lGetMode(FlashType));

    /* [cover parentID={A9233307-DCC7-4b12-B513-8FD75EA95C5F}]
        Flash type is PFlash
        [/cover] */
    /* Check if Program Flash is in page mode */
    if (FlashType != FLSLOADER_DFLASH_BANK0)
    {

      /* [cover parentID={1F0874AD-5729-4a4c-BECE-3CA419AAAB12}]
          PFlash page mode not yet set and counter is within timeout
      [/cover] */
      RetError = FlsLoader_lCheckBitSet(&DMU_HF_STATUS.U, \
                                        FLSLOADER_PFPAGE_BIT_MASK);
    }
    else
    {

      /* [cover parentID={FD913A43-A8CE-4c61-83B4-87E3CC851007}]
         DFlash page mode not yet set and counter is within timeout
      [/cover] */
      RetError = FlsLoader_lCheckBitSet(&DMU_HF_STATUS.U, \
                                        FLSLOADER_DFPAGE_BIT_MASK);
    }

    /* [cover parentID={2773548D-49A2-4d5a-A4C8-F8B43BC13A98}]
    Page mode set within timeout
    [/cover] */
    if (RetError == FLSLOADER_E_OK)
    {
      /* [cover parentID={8747644E-EB95-4873-BAA3-89ACD5BDAD96}]
      Execute write burst command and store return error status
      [/cover] */
      /*execute burst write commands*/
      RetError |= FlsLoader_lBurstWriteCmdCycle(TargetFlashAddress, FlashType, \
                  SourceAddress, SrcAddrWordAlignFlag, BurstTimeoutTicks);

      /* [cover parentID={68E41A09-DD77-43bc-BF70-322269C545F2}]
       RetVal is not FLSLOADER_E_OPERR
      [/cover] */
      if(RetError != FLSLOADER_E_OPERR)
      {
        /* Clear the status if the operation is successful.*/
        FlsLoader_lCommandCycle(FLSLOADER_CYCLE_5554, FLSLOADER_VALUE_FA);
      }
      else
      {
        RetError = FLSLOADER_E_NOT_OK;
      }

      /* Iterate the TargetAddress to the next page Address */
      TargetFlashAddress = TargetFlashAddress + BurstOffSet;

      /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic used to
      * pass next source burst data*/
      SourceAddress = SourceAddress + BurstOffSet;
    }
  }
  return RetError;
}

/*******************************************************************************
** Traceability     : FlsLoader_ReturnType LOCAL_INLINE FlsLoader_ReturnType  **
**                    FlsLoader_lPageWrite(                                   **
**                         const FlsLoader_AddressType OffSet,                **
**                         const uint32 FlashType,                            **
**                         const uint8* const SourceAddressPtr,               **
**                         const FlsLoader_AddressType TargetAddress,         **
**                         const uint32 NoOfPages)                            **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : FlashType: Flash bank number (DFlash0, PFlash0 to       **
**                    PFlash5)                                                **
**                    NumberOfPages: Number of pages to be written            **
**                    OffSet: Offset to increment Target address to           **
**                    next page write                                         **
**                    SourceAddressPtr: Pointer to source data buffer         **
**                    TargetAddress: Target address in Flash                  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FLSLOADER_E_OK: Page writes executed successfully.      **
**                    FLSLOADER_E_NOT_OK: Page writes failed. Protection,     **
**                    sequence, operation or program verification error has   **
**                    occurred.                                               **
**                                                                            **
** Description      : This function writes the data to PFlash or DFlash in    **
**                    page mode.                                              **
*******************************************************************************/
/* [cover parentID={84E94D79-FD8A-40e6-A173-E08F87123348}][/cover] */
LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lPageWrite(
                           const FlsLoader_AddressType OffSet,
                           const uint32 FlashType,
                           const uint8* const SourceAddressPtr,
                           const FlsLoader_AddressType TargetAddress,
                           const uint32 NoOfPages)
{
  uint32                         Count;
  uint32                         TickResolution;
  uint32                         PageTimeoutTicks;
  const uint8*                   SourceAddress;
  FlsLoader_ReturnType           RetError;
  FlsLoader_AddressType          TargetFlashAddr = TargetAddress;
  uint32                         SrcAddrWordAlignFlag;

  RetError = FLSLOADER_E_OK;

  /*STM count resolution in ns*/
  /* [cover parentID={584957CC-524A-45e5-A441-CAB1EE30207F}]
    Calculate number of STM counts required for maximum time per page
    write for given Flash type (PFlash or DFlash)
  [/cover] */
  /*STM count resolution in ns*/
  TickResolution = Mcal_DelayTickResolution();

  /* [cover parentID={584957CC-524A-45e5-A441-CAB1EE30207F}]
    Calculate number of STM counts required for maximum time per page
    write for given Flash type (PFlash or DFlash)
  [/cover] */
  if(FlashType != FLSLOADER_DFLASH_BANK0)
  {
    /*STM counts for given max PF page write time*/
    PageTimeoutTicks = (uint32)\
                       (FLSLOADER_MAX_TIME_PER_PF_PAGE / TickResolution);
  }
  else
  {
    /*STM counts for given max DF page write time*/
    PageTimeoutTicks = (uint32)\
                       (FLSLOADER_MAX_TIME_PER_DF_PAGE / TickResolution);
  }

  /*Add 10% additional buffer from software*/
  PageTimeoutTicks += (uint32)(PageTimeoutTicks / FLSLOADER_DIV_10);

  /* [cover parentID={D2054E7F-8DB4-42cd-959A-9F451653285A}]
      Check if the source address is aligned with the 4 byte
      boundary and if not set a flag
  [/cover] */
  /*Check word alignment of Source address*/
  /* MISRA2012_RULE_11_4_JUSTIFICATION: Pointer conversion is required for
     the comparision of pointer value with an integer */
  /* MISRA2012_RULE_11_6_JUSTIFICATION: Pointer conversion is required for
     the comparision of pointer value with an integer */
  if (((uint32)SourceAddressPtr & FLSLOADER_ALIGN_4BYTE) == FALSE)
  {
    /*SA is aligned to word boundary, set flag to true*/
    SrcAddrWordAlignFlag = TRUE;
  }
  else
  {
    /*SA is not aligned to word boundary, set flag to false*/
    SrcAddrWordAlignFlag = FALSE;
  }

  SourceAddress = SourceAddressPtr;

  /* [cover parentID={D5FA6219-C50E-4284-81D3-3701E0B765E0}]
     Loop to perform requested number of page writes
  [/cover] */
  /* [cover parentID={07D15EAC-BFBE-4a69-A70D-A22DD0833D25}]
     Loop to perform requested number of page writes
  [/cover] */
  for (Count = 0U; (Count < NoOfPages) && (RetError == FLSLOADER_E_OK); Count++)
  {
    /* Clear error and status flags*/
    FlsLoader_lCommandCycle(FLSLOADER_CYCLE_5554, FLSLOADER_VALUE_FA);

    /* Enter the Page Mode */
    FlsLoader_lCommandCycle(FLSLOADER_CYCLE_5554, \
                            FlsLoader_lGetMode(FlashType));

    /* [cover parentID={A6ED4E9D-4065-4e3d-8F34-B316647BED24}]
       Flash type is PFlash
    [/cover] */
    /*Check if Program Flash is in page mode */
    if (FlashType != FLSLOADER_DFLASH_BANK0)
    {
      /* [cover parentID={0EAA27F2-F5D2-497a-A0BE-575A96E24F6E}]
      PFlash page mode not yet set and counter is within timeout
      [/cover] */
      RetError = FlsLoader_lCheckBitSet(&DMU_HF_STATUS.U, \
                                        FLSLOADER_PFPAGE_BIT_MASK);
    }
    else
    {
      /* [cover parentID={B61BD0FC-791C-4a49-B189-B76D3965CC01}]
       DFlash page mode not yet set and counter is within timeout
      [/cover] */
      RetError = FlsLoader_lCheckBitSet(&DMU_HF_STATUS.U, \
                                        FLSLOADER_DFPAGE_BIT_MASK);
    }

    /* [cover parentID={62F4E761-72F5-4a17-8865-BB1B652144B0}]
       Page mode set successfully
      [/cover] */
    /*Either seq error, protection error or timeout has happened*/
    if (RetError == FLSLOADER_E_OK)
    {
      /* [cover parentID={C3975310-AE8F-4d3a-B423-88E88FDB566F}]
       Execute write page command and store return error status
      [/cover] */
      /*execute page write commands*/
      RetError |= FlsLoader_lPageWriteCmdCycle(TargetFlashAddr, \
                  FlashType, SourceAddress, SrcAddrWordAlignFlag, \
                  PageTimeoutTicks);

      /* [cover parentID={33FB8D25-FE41-4610-89B4-1ADA64DD607F}][/cover] */
      if(RetError != FLSLOADER_E_OPERR)
      {
        /* Clear the status if the operation is successful.*/
        FlsLoader_lCommandCycle(FLSLOADER_CYCLE_5554, FLSLOADER_VALUE_FA);
      }
      else
      {
        RetError = FLSLOADER_E_NOT_OK;
      }

      /*Iterate the TargetAddress to the next page Address */
      TargetFlashAddr = TargetFlashAddr + OffSet;

      /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic used to
      * pass next source burst data*/
      SourceAddress = SourceAddress + OffSet;
    }
  }
  return RetError;
}

/*******************************************************************************
** Syntax           : LOCAL_INLINE FlsLoader_ReturnType                       **
**                                FlsLoader_lEraseCalcPhySector(              **
**                                const FlsLoader_AddressType TargetAddress,  **
**                                const uint32 FlashType,                     **
**                                const FlsLoader_LengthType Length,          **
**                                const uint32 EraseTimeoutTicks)             **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : EraseTimeoutTicks: Timeout counts for one erase command **
**                    FlashType: Flash bank number (DFlash0, PFlash0          **
**                    to PFlash5)                                             **
**                    Length: Number of sectors for erase                     **
**                    TargetAddress: Target address to be erased in           **
**                    Flash                                                   **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FLSLOADER_E_OK: Erase successful.                       **
**                    FLSLOADER_E_NOT_OK: Protection, Sequence, Operation or  **
**                    Program Verification Error has occurred.                **
**                                                                            **
** Description      : This function identifies if number of sectors to be     **
**                    erased is in same physical sector or different          **
**                    physical sectors and executes the erase                 **
**                    commands accordingly.                                   **
*******************************************************************************/
/* [cover parentID={A050088B-DDF6-41a6-B360-0356F39EA591}][/cover] */
LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lEraseCalcPhySector(
                                     const FlsLoader_AddressType TargetAddress,
                                     const uint32 FlashType,
                                     const FlsLoader_LengthType Length,
                                     const uint32 EraseTimeoutTicks)
{
  uint32 FlsPbankStart;
  uint32 FlsPbankEnd;
  uint32 FlsBankStartAddr;
  uint32 FlsEndAddress;
  FlsLoader_LengthType FlsNoOfSectors;
  uint32 EraseTargetAddr;
  FlsLoader_ReturnType RetError;
  uint32 FlashType0;

  /*Copy Target address*/
  EraseTargetAddr = TargetAddress;

  /* [cover parentID={2430C8EF-90E9-44c3-A649-57393164A30B}]
  Flash type is PFlash
  [/cover] */
  /*calculate start and end physical bank numbers for PF/DF bank*/
  if (FlashType != FLSLOADER_DFLASH_BANK0)
  {
    /*Calculate PF End address of given erase operation*/
    FlsEndAddress = (EraseTargetAddr + \
                     (Length * FLSLOADER_SIZE_16K)) - 1U;

    /*Get Start adress of given PF bank*/
    FlsBankStartAddr = FlsLoader_PFlashOffset[FlashType];

    /*Physical sector number of given Start address*/
    FlsPbankStart = (EraseTargetAddr - FlsBankStartAddr) / \
                    FLSLOADER_PHYSICAL_SECTOR_1MB;

    /*Physical sector number of End address*/
    FlsPbankEnd = (FlsEndAddress - FlsBankStartAddr) / \
                  FLSLOADER_PHYSICAL_SECTOR_1MB;
  }
  else
  {
    /*For DF, it is single physical sector*/
    FlsPbankStart = 0U;
    FlsPbankEnd = 0U;
  }

  /* [cover parentID={E74A6E2B-A003-456a-94D0-FD00E8F5EAA0}]
    Start and end physical sector numbers are different
  [/cover] */
  /*Both start/end address lies in same physical sector*/
  if(FlsPbankEnd == FlsPbankStart)
  {

    /* [cover parentID={EFCD1D23-A1AB-4c35-B4E7-025720B430E5}]
    Execute erase command for the physical sector with given erase values
    and report error status
    [/cover] */
    /*Execute erase operation for the given Length*/
    RetError = FlsLoader_lEraseCmdCycle(EraseTargetAddr,\
                                   FlashType, Length, EraseTimeoutTicks);
  }
  else
  {

    /*Flash type should be less than no. of PF banks*/
    FlashType0 = FlashType & FLSLOADER_MASK_3_BITS;

    /*Get Start adress of given PF bank*/
    FlsBankStartAddr = FlsLoader_PFlashOffset[FlashType0];

    /*Calculate PF phy bank end address*/
    FlsEndAddress = FlsBankStartAddr + \
                    ((FlsPbankEnd * FLSLOADER_PHYSICAL_SECTOR_1MB) - 1U);

    /*Calculate no. of sectors in current PF phy bank*/
    FlsNoOfSectors = ((FlsEndAddress - EraseTargetAddr) + 1U) / \
                     FLSLOADER_SIZE_16K;

    /* [cover parentID={5C98E501-F5BC-4a67-9D61-81B95D5F33BB}]
        Execute erase command for current physical sector
    [/cover] */
    /*Erase current physical sector*/
    RetError = FlsLoader_lEraseCmdCycle(EraseTargetAddr,\
                          FlashType, FlsNoOfSectors, EraseTimeoutTicks);

    /*Get next physical sector start address*/
    EraseTargetAddr = FlsEndAddress + 1U;

    /*Calculate remaining no. of sectors*/
    FlsNoOfSectors = Length - FlsNoOfSectors;

    /* [cover parentID={3A9CD3AF-B470-470e-B9FA-94C4E63DC620}]
       Execute erase command for next physical sector and add logical OR the
       error status previous operation
    [/cover] */
    /*Erase in next physical sector*/
    RetError |= FlsLoader_lEraseCmdCycle(EraseTargetAddr,\
                           FlashType, FlsNoOfSectors, EraseTimeoutTicks);
  }

  return RetError;
}

/*******************************************************************************
** Syntax           : LOCAL_INLINE FlsLoader_ReturnType                       **
**                             FlsLoader_lEraseCmdCycle(                      **
**                       const FlsLoader_AddressType TargetAddress,           **
**                       const uint32 FlashType,                              **
**                       const FlsLoader_LengthType Length,                   **
**                       const uint32 EraseTimeoutTicks)                      **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : EraseTimeoutTicks: Timeout counts for one erase command **
**                    FlashType: Flash bank number (DFlash0, PFlash0 to       **
**                    PFlash5)                                                **
**                    Length: Number of sectors for erase                     **
**                    TargetAddress: Target address to be erased in Flash     **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FLSLOADER_E_OK: Erase successful                        **
**                    FLSLOADER_E_NOT_OK: Protection, Sequence, Operation or  **
**                    Program Verification Error has occurred.                **
**                                                                            **
** Description      : This function executes erase command for given target   **
**                    address and length of sectors.                          **
*******************************************************************************/
/* [cover parentID={01359B74-2A91-4aac-AE96-660263C6E672}][/cover] */
/* [cover parentID={5A0BFE9C-D406-42ee-855D-92C59305FF1F}][/cover] */
LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lEraseCmdCycle(
                                     const FlsLoader_AddressType TargetAddress,
                                     const uint32 FlashType,
                                     const FlsLoader_LengthType Length,
                                     const uint32 EraseTimeoutTicks)
{
  FlsLoader_ReturnType  RetError;
  uint32                EraseErrStat;
  uint32                         BaseTicks;
  uint32                         CurrTicks;
  uint32                         ElapsedTicks;
  uint32                         BusySetTicks;
  uint32                         TickResolution;

  TickResolution = Mcal_DelayTickResolution();

  /* Clear error and status flags*/
  FlsLoader_lCommandCycle(FLSLOADER_CYCLE_5554, FLSLOADER_VALUE_FA);

  /* [cover parentID={22798873-5A79-47e6-8FBD-3431687C95DE}]
    Disable safety end init protection
  [/cover] */
  /* [cover parentID={30E4C8B9-E1EA-40a6-9ECF-744606ED7207}]
    Flash type is PFlash
  [/cover] */
  /* [cover parentID={0CFA9DCB-B1BB-4478-924F-48DA43FAAD58}]
    Flash type is PFlash
  [/cover] */
  /* Reset Safety Endinit is required for PFlash */
  if (FlashType != FLSLOADER_DFLASH_BANK0)
  {
    /* [cover parentID={57106E92-A247-4dee-9C12-4C7A08078B91}][/cover] */
    BusySetTicks   = (uint32) (FLSLOADER_BUSY_SET_DELAY_PF / TickResolution);
    /* [cover parentID={36F37C9B-9F81-4323-AA6A-4BA932516468}][/cover] */
    FlsLdr_ExclArea_PfErase_Enter();
    FlsLoader_lResetSafetyENDINIT();
  }
  else
  {
    /* [cover parentID={7A419AA4-5D1B-405c-BAFB-5FC133126771}][/cover] */
    BusySetTicks   = (uint32) (FLSLOADER_BUSY_SET_DELAY_DF / TickResolution);
  }

  /*Invoke Erase Logical Sector Range command sequence*/

  /* Erase Logical Sector Range command cycle-1 */
  FlsLoader_lCommandCycle(FLSLOADER_CYCLE_AA50, TargetAddress);

  /* Erase Logical Sector Range command cycle-2 */
  FlsLoader_lCommandCycle(FLSLOADER_CYCLE_AA58, Length);

  /* Erase Logical Sector Range command cycle-3 */
  FlsLoader_lCommandCycle(FLSLOADER_CYCLE_AAA8, FLSLOADER_VALUE_80);

  /* Erase Logical Sector Range command cycle-4 */
  FlsLoader_lCommandCycle(FLSLOADER_CYCLE_AAA8, FLSLOADER_VALUE_50);

  /* Wait till the ERASE bit is set */
  /* [cover parentID={732C9626-3FF2-4b3f-A650-97AD8803FA57}]
     Erase bit set
  [/cover] */
  RetError = FlsLoader_lCheckBitSet(&DMU_HF_OPERATION.U, \
                                    FLSLOADER_ERASE_BIT_MASK);

  /* [cover parentID={4BD67D11-F10D-4cc4-87F0-DFD60B69353A}]
    Enable safety end init protection
  [/cover] */
  /* [cover parentID={F46ADACC-FCC2-4de2-A5CB-CFDD0F8F1C3A}]
    Flash type is PFlash
  [/cover] */
  /*Enable Safety Endinit*/
  if (FlashType != FLSLOADER_DFLASH_BANK0)
  {
    FlsLoader_lSetSafetyENDINIT();
    /* [cover parentID={9105D320-687F-49bf-925E-F94B076C8733}][/cover] */
    FlsLdr_ExclArea_PfErase_Exit();
  }

  /* [cover parentID={8B115660-EE09-4866-9B8B-60E35E596971}]
     Flash busy Reset within maximum timeout
  [/cover] */
  if (RetError == FLSLOADER_E_OK)
  {
    BaseTicks = Mcal_DelayGetTick();
    do
    {
      CurrTicks = Mcal_DelayGetTick();
      ElapsedTicks = (uint32)((CurrTicks - BaseTicks) &\
                            FLSLOADER_OVERFLOW_MASK);
    }while(ElapsedTicks < BusySetTicks);

    /* [cover parentID={CEF38B2B-7C57-43c2-96D5-5BA37DFAAEF4}]
      Check if erase is completed within maximum timeout and return status
    [/cover] */
    /*Check for erase timeout*/
    RetError = FlsLoader_lBusyCheck(EraseTimeoutTicks);

    if (RetError == FLSLOADER_E_OK)
    {
      EraseErrStat = FLSLOADER_BIT_RESET;

      /* [cover parentID={041C5D9F-5B17-4977-970D-D8F2A533E6B8}] [/cover] */
      /*Check PVER for PF erase as the erase counters
        are programmed during PF erase*/
      if (FlashType != FLSLOADER_DFLASH_BANK0)
      {
        /*Read PVER error status*/
        EraseErrStat |= DMU_HF_ERRSR.B.PVER;
      }

      /*Read EVER error status*/
      EraseErrStat |= DMU_HF_ERRSR.B.EVER;

      /*Read OPER error status*/
      EraseErrStat |= DMU_HF_ERRSR.B.OPER;

      /* [cover parentID={ED37EF00-DED5-4744-883F-C8DF413FBC47}] [/cover] */
      /* If PVER (PFlash), EVER or OPER set, return E_NOT_OK*/
      if (EraseErrStat == FLSLOADER_BIT_SET)
      {
        RetError = FLSLOADER_E_NOT_OK;
      }
      /* Clear error and status flags.*/
      FlsLoader_lCommandCycle(FLSLOADER_CYCLE_5554, FLSLOADER_VALUE_FA);
    }
  }


  return RetError;
}

/*******************************************************************************
** Syntax           : LOCAL_INLINE FlsLoader_ReturnType                       **
**                                 FlsLoader_lPageWriteCmdCycle(              **
**                                 const FlsLoader_AddressType TargetAddress, **
**                                 const uint32 LoadPageCount,                **
**                                 const uint8* const SourceAddressPtr,       **
**                                 const uint32 SrcAddrWordAlignFlag,         **
**                                 const uint32 PageTimeoutTicks)             **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : FlashType Flash bank number (DFlash0, PFlash0 to        **
**                    PFlash5)                                                **
**                    PageTimeoutTicks: Timeout count value for one page      **
**                    write.                                                  **
**                    SourceAddressPtr: Pointer to source data buffer         **
**                    SrcAddrWordAlignFlag: Flag indicating word alignment of **
**                    SourceAddressPtr.                                       **
**                    TargetAddress: Target address for write operation       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FLSLOADER_E_OK: Page write executed successfully.       **
**                    FLSLOADER_E_NOT_OK: Page write failed. Protection,      **
**                    sequence, operation or program verification error       **
**                    has occurred.                                           **
**                    FLSLOADER_E_OPERR: Timeout or Operational error         **
**                    has occurred.                                           **
**                                                                            **
** Description      : This function executes write page command for given     **
**                    target address.                                         **
*******************************************************************************/
/* [cover parentID={08D3DA05-7F97-491b-BD80-1B620AE57E42}][/cover] */
LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lPageWriteCmdCycle(
                                   const FlsLoader_AddressType TargetAddress,
                                   const uint32 FlashType,
                                   const uint8* const SourceAddressPtr,
                                   const uint32 SrcAddrWordAlignFlag,
                                   const uint32 PageTimeoutTicks)
{
  uint32                         InCount;
  uint32                         LoadPageCount;
  FlsLoader_ReturnType           RetError;
  const FlsLoader_AddressType   *PdataPtr;
  uint32                         WordAlignedBuffer[FLDR_LOADPAGE_DATA_SIZE];
  uint32                         Count;
  uint32                         WriteErrStat;
  uint32                         BaseTicks;
  uint32                         CurrTicks;
  uint32                         ElapsedTicks;
  uint32                         BusySetTicks;
  uint32                         TickResolution;

  TickResolution = Mcal_DelayTickResolution();
  /*MISRA2012_RULE_11_3_JUSTIFICATION: "PdataPtr" cast to 4-byte ptr
  necessary 32-bit width WD transfers, PdataPtr is used only in case of aligned
  access caller function check the algnment of the SourceAddressPtr*/
  PdataPtr = (const FlsLoader_AddressType *)SourceAddressPtr;
  /* [cover parentID={C2123567-1C93-4330-987E-A5D606F57E6F}][/cover] */
  /*Number of 8-byte data to be written in page assembly buffer*/
  if(FlashType != FLSLOADER_DFLASH_BANK0)
  {
    LoadPageCount = FLDR_LOADPAGE_CNT_PER_PF_PAGE;
    /* [cover parentID={2DB4C124-2F7E-470f-9D2C-5D5B0ED0A1B8}][/cover] */
    BusySetTicks   = (uint32) (FLSLOADER_BUSY_SET_DELAY_PF / TickResolution);
  }
  else
  {
    LoadPageCount = FLDR_LOADPAGE_CNT_PER_DF_PAGE;
    /* [cover parentID={8296FBDD-5FB1-41cc-A275-80360AF50382}][/cover] */
    BusySetTicks   = (uint32) (FLSLOADER_BUSY_SET_DELAY_DF / TickResolution);
  }

  /*Complete all pending memory read/writes*/
  DSYNC();

  /*Initialize local source data count*/
  Count = 0U;

  /* [cover parentID={88FAD358-621D-4c76-993E-E38727FAECE4}]
     Check if page write is completed within maximum timeout
  [/cover] */
  for (InCount = 0U; InCount < LoadPageCount; InCount++)
  {
    /* [cover parentID={1D727914-4E7D-4dd7-A380-6D0080BA3DE0}]
       Check if source address is aligned to word boundary
    [/cover] */
    /*Check if SA is aligned to word boundary*/
    if (SrcAddrWordAlignFlag == FALSE)
    {
      /*Copy source data into word aligned local buffer*/
      WordAlignedBuffer[FLDR_WORD_0] = \
          (((uint32)SourceAddressPtr[Count + FLDR_BYTE_3] << FLDR_SHIFT_24) | \
           ((uint32)SourceAddressPtr[Count + FLDR_BYTE_2] << FLDR_SHIFT_16) | \
           ((uint32)SourceAddressPtr[Count + FLDR_BYTE_1] << FLDR_SHIFT_8)  | \
            (uint32)SourceAddressPtr[Count]);

      /*Copy source data into word aligned local buffer*/
      WordAlignedBuffer[FLDR_WORD_1] = \
          (((uint32)SourceAddressPtr[Count + FLDR_BYTE_7] << FLDR_SHIFT_24) | \
           ((uint32)SourceAddressPtr[Count + FLDR_BYTE_6] << FLDR_SHIFT_16) | \
           ((uint32)SourceAddressPtr[Count + FLDR_BYTE_5] << FLDR_SHIFT_8)  | \
            (uint32)SourceAddressPtr[Count + FLDR_BYTE_4]);

      /* [cover parentID={FBB0F1DA-F45A-46ea-B66C-CA259FE557E3}]
         Load source data into hardware page assembly buffer
      [/cover] */
      /*load page assembly buffer first 32-bits*/
      FlsLoader_lCommandCycle(FLSLOADER_CYCLE_55F0, \
                              WordAlignedBuffer[FLDR_WORD_0]);

      /*load page assembly buffer next 32-bits*/
      FlsLoader_lCommandCycle(FLSLOADER_CYCLE_55F4, \
                              WordAlignedBuffer[FLDR_WORD_1]);

      /*Increment source data offset by 8-bytes*/
      Count += FLSLOADER_LOAD_PAGE_8BYTE;
      /* Load Page register gets incremented automatically. */
    }
    else
    {

      /* [cover parentID={FBB0F1DA-F45A-46ea-B66C-CA259FE557E3}]
         Load source data into hardware page assembly buffer
      [/cover] */
      /*load page assembly buffer first 32-bits*/
      FlsLoader_lCommandCycle(FLSLOADER_CYCLE_55F0, PdataPtr[Count]);

      /*load page assembly buffer next 32-bits*/
      FlsLoader_lCommandCycle(FLSLOADER_CYCLE_55F4, PdataPtr[Count + 1u]);

      /*Increment source data offset by 8-bytes*/
      Count += FLDR_LOADPAGE_DATA_SIZE;
      /* Load Page register gets incremented automatically. */
    }
  }

  /* [cover parentID={415856AE-E127-4c79-8DBF-646571810510}]
    Disable the end init protection
  [/cover] */
  if (FlashType != FLSLOADER_DFLASH_BANK0)
  {
    /* [cover parentID={7B77804D-38DA-470f-9015-9D40E80FD5CA}][/cover] */
    /* [cover parentID={3F53913C-E5C6-46e8-A56C-E8D7CF3F1F97}][/cover] */
    FlsLdr_ExclArea_PfProg_Enter();
    /* [cover parentID={0BFFD54C-C760-4eb0-8F5D-0C3D5F357240}][/cover] */
    FlsLoader_lResetSafetyENDINIT();
  }

  /* [cover parentID={85B8F559-3ED5-43f8-95A8-121FEBD4ECC5}]
     Execute write page command sequence to start programming
  [/cover] */

  /*Invoke "Write Page" command cycles*/

  /* Write Page command cycle-1 */
  FlsLoader_lCommandCycle(FLSLOADER_CYCLE_AA50, TargetAddress);

  /* Write Page command cycle-2 */
  FlsLoader_lCommandCycle(FLSLOADER_CYCLE_AA58, FLSLOADER_VALUE_00);

  /* Write Page command cycle-3 */
  FlsLoader_lCommandCycle(FLSLOADER_CYCLE_AAA8, FLSLOADER_VALUE_A0);

  /* Write Page command cycle-4 */
  FlsLoader_lCommandCycle(FLSLOADER_CYCLE_AAA8, FLSLOADER_VALUE_AA);

  /* [cover parentID={4DBA2EDB-3637-4670-86CE-B75670822975}]
    Program State not yet Set in register and Counter is within Timeout
  [/cover] */
  /* Wait till the PROG bit is set */
  RetError = FlsLoader_lCheckBitSet(&DMU_HF_OPERATION.U, \
                                    FLSLOADER_PROG_BIT_MASK);

  /* [cover parentID={3086495C-BC85-4cc6-AE35-BAB154231A16}]
    Flash type is PFlash
  [/cover] */
  if ((FlashType != FLSLOADER_DFLASH_BANK0))
  {
    /* [cover parentID={1D455BBE-EAFA-4a5c-BF3E-1127BB519222}]
      Enable back the end init protection
    [/cover] */
    FlsLoader_lSetSafetyENDINIT();
    /* [cover parentID={50441ABD-0369-4c14-93B4-DE6F62DD0ECD}][/cover] */
    FlsLdr_ExclArea_PfProg_Exit();
  }

  /* [cover parentID={E33E4F65-36CC-48a5-9D45-1F4FB7E31ECD}]
     Program State Set in Register within Timeout
  [/cover] */
  if (RetError == FLSLOADER_E_OK)
  {
    BaseTicks = Mcal_DelayGetTick();
    do
    {
      CurrTicks = Mcal_DelayGetTick();
      ElapsedTicks = (uint32)((CurrTicks - BaseTicks) &\
                            FLSLOADER_OVERFLOW_MASK);
    }while(ElapsedTicks < BusySetTicks);

    /* [cover parentID={88FAD358-621D-4c76-993E-E38727FAECE4}]
      Check if page write is completed within maximum timeout
    [/cover] */
    /*Poll for busy status and return*/
    RetError = FlsLoader_lBusyCheck(PageTimeoutTicks);

    /* [cover parentID={DE6C038E-251C-4a31-98D8-0164B954258F}]
     Flash busy Reset within Timeout
    [/cover] */
    if (RetError == FLSLOADER_E_OK)
    {
      /*Read PVER error status*/
      WriteErrStat = DMU_HF_ERRSR.B.PVER;

      /*Read OPER error status*/
      WriteErrStat |= DMU_HF_ERRSR.B.OPER;

      /* [cover parentID={B4828835-9969-4bc7-AFE6-A73854697426}] [/cover] */
      /* If PVER or OPER set, return E_NOT_OK */
      if (WriteErrStat == FLSLOADER_BIT_SET)
      {
        RetError = FLSLOADER_E_NOT_OK;
      }
    }
    else
    {
       RetError = FLSLOADER_E_OPERR;
    }
  }

  return RetError;
}

/*******************************************************************************
** Syntax           : LOCAL_INLINE FlsLoader_ReturnType                       **
**                                   FlsLoader_lBurstWriteCmdCycle(           **
**                                 const FlsLoader_AddressType TargetAddress, **
**                                 const uint32 FlashType,                    **
**                                 const uint8* const SourceAddressPtr,       **
**                                 const uint32 SrcAddrWordAlignFlag,         **
**                                 const uint32 BurstTimeoutTicks)            **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : BurstTimeoutTicks: Timeout count for one burst write    **
**                    FlashType: Flash bank number (DFlash0, PFlash0 to       **
**                      PFlash5)                                              **
**                    SourceAddressPtr: Pointer to source data buffer         **
**                    SrcAddrWordAlignFlag: Flag indicating word alignment of **
**                    SourceAddressPtr.                                       **
**                    TargetAddress: Target address for write operation       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FLSLOADER_E_OK: Burst write executed successfully.      **
**                    FLSLOADER_E_NOT_OK: Burst write failed. Protection,     **
**                    sequence, operation or program verification error       **
**                    has occurred.                                           **
**                    FLSLOADER_E_OPERR: Timeout or Operational error         **
**                    has occurred.                                           **
**                                                                            **
** Description      : This function executes write burst command for given    **
**                    target address                                          **
*******************************************************************************/
/* [cover parentID={16EF8765-20CA-43a1-9FFD-A60A35B06E56}][/cover] */
LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lBurstWriteCmdCycle(
                                   const FlsLoader_AddressType TargetAddress,
                                   const uint32 FlashType,
                                   const uint8* const SourceAddressPtr,
                                   const uint32 SrcAddrWordAlignFlag,
                                   const uint32 BurstTimeoutTicks)
{
  uint32                         InCount;
  uint32                         BurstLoadPageCount;
  FlsLoader_ReturnType           RetError;
  const FlsLoader_AddressType   *PdataPtr;
  uint32                         WordAlignedBuffer[FLDR_LOADPAGE_DATA_SIZE];
  uint32                         Count;
  uint32                         WriteErrStat;
  uint32                         BaseTicks;
  uint32                         CurrTicks;
  uint32                         ElapsedTicks;
  uint32                         BusySetTicks;
  uint32                         TickResolution;

  /*MISRA2012_RULE_11_3_JUSTIFICATION: "PdataPtr" cast to 4-byte ptr
  necessary 32-bit width WD transfers, PdataPtr is used only in case of aligned
  access caller function check the algnment of the SourceAddressPtr*/
  PdataPtr = (const FlsLoader_AddressType *)SourceAddressPtr;

  TickResolution = Mcal_DelayTickResolution();


  /* [cover parentID={8CC11643-2668-4a68-A647-70BFDE63791D}][/cover] */
  /*Number of 8-byte data to be written in page assembly buffer*/
  if(FlashType != FLSLOADER_DFLASH_BANK0)
  {
    /* [cover parentID={98EED929-8F8C-41cb-967A-BF5CDDD05E2B}][/cover] */
    BurstLoadPageCount = FLDR_LOADPAGE_CNT_PER_PF_BURST;
    BusySetTicks   = (uint32) (FLSLOADER_BUSY_SET_DELAY_PF / TickResolution);
  }
  else
  {
    /* [cover parentID={9C855CDE-6D7B-44f7-823A-C70EEC0C55C3}][/cover] */
    BurstLoadPageCount = FLDR_LOADPAGE_CNT_PER_DF_BURST;
    BusySetTicks   = (uint32) (FLSLOADER_BUSY_SET_DELAY_DF / TickResolution);
  }

  /*Complete all pending memory read/writes*/
  DSYNC();

  /*Initialize local source data count*/
  Count = 0U;

  for (InCount = 0U; InCount < BurstLoadPageCount; InCount++)
  {
    /* [cover parentID={E78D2F9C-CE8E-4416-8821-75A8CEF309B3}]
    Check if source address is aligned to word boundary
    [/cover] */
    /*Check if SA is aligned to word boundary*/
    if (SrcAddrWordAlignFlag == FALSE)
    {
      /*Copy source data into word aligned local buffer*/
      WordAlignedBuffer[FLDR_WORD_0] = \
          (((uint32)SourceAddressPtr[Count + FLDR_BYTE_3] << FLDR_SHIFT_24) | \
           ((uint32)SourceAddressPtr[Count + FLDR_BYTE_2] << FLDR_SHIFT_16) | \
           ((uint32)SourceAddressPtr[Count + FLDR_BYTE_1] << FLDR_SHIFT_8)  | \
            (uint32)SourceAddressPtr[Count]);

      /*Copy source data into word aligned local buffer*/
      WordAlignedBuffer[FLDR_WORD_1] = \
          (((uint32)SourceAddressPtr[Count + FLDR_BYTE_7] << FLDR_SHIFT_24) | \
           ((uint32)SourceAddressPtr[Count + FLDR_BYTE_6] << FLDR_SHIFT_16) | \
           ((uint32)SourceAddressPtr[Count + FLDR_BYTE_5] << FLDR_SHIFT_8)  | \
            (uint32)SourceAddressPtr[Count + FLDR_BYTE_4]);

      /* [cover parentID={052869B0-226B-4fad-AD5A-DA512F674B9E}]
      Load source data into hardware page assembly buffer
      [/cover] */
      /*load page assembly buffer first 32-bits*/
      FlsLoader_lCommandCycle(FLSLOADER_CYCLE_55F0, \
                              WordAlignedBuffer[FLDR_WORD_0]);

      /*load page assembly buffer next 32-bits*/
      FlsLoader_lCommandCycle(FLSLOADER_CYCLE_55F4, \
                              WordAlignedBuffer[FLDR_WORD_1]);

      /*Increment source data to next 8 bytes*/
      Count += FLSLOADER_LOAD_PAGE_8BYTE;

    }
    else
    {

      /* [cover parentID={052869B0-226B-4fad-AD5A-DA512F674B9E}]
      Load source data into hardware page assembly buffer
      [/cover] */
      /*load page assembly buffer first 32-bits*/
      FlsLoader_lCommandCycle(FLSLOADER_CYCLE_55F0, PdataPtr[Count]);

      FlsLoader_lCommandCycle(FLSLOADER_CYCLE_55F4, PdataPtr[Count + 1u]);

      Count += FLDR_LOADPAGE_DATA_SIZE;
      /* Load Page register gets incremented automatically. */
    }
  }

  /* [cover parentID={5CF77FEA-C2C1-4a47-B240-D962B6BAAFD3}]
     Flash type is PFlash
  [/cover] */
  if (FlashType != FLSLOADER_DFLASH_BANK0)
  {
    /* [cover parentID={110A32D2-3177-4f37-AACF-E443E4BC8D88}][/cover] */
    /* [cover parentID={3F53913C-E5C6-46e8-A56C-E8D7CF3F1F97}][/cover] */
    FlsLdr_ExclArea_PfProg_Enter();
    /* [cover parentID={C55F552E-4EBF-4385-B786-8BF3B89B3735}][/cover] */
    FlsLoader_lResetSafetyENDINIT();
  }

  /* [cover parentID={301453BD-ACA3-455d-AD9A-CDE69D247922}]
  Execute write page command sequence to start programming
  [/cover] */

  /*Invoke "Write Burst" command cycles*/

  /* Write Burst command cycle-1 */
  FlsLoader_lCommandCycle(FLSLOADER_CYCLE_AA50, TargetAddress);

  /* Write Burst command cycle-2 */
  FlsLoader_lCommandCycle(FLSLOADER_CYCLE_AA58, FLSLOADER_VALUE_00);

  /* Write Burst command cycle-3 */
  FlsLoader_lCommandCycle(FLSLOADER_CYCLE_AAA8, FLSLOADER_VALUE_A0);

  /* Write Burst command cycle-4 */
  FlsLoader_lCommandCycle(FLSLOADER_CYCLE_AAA8, FLSLOADER_VALUE_A6);

  /* [cover parentID={B38A6441-1AE9-4ebd-81F3-D55097FE2FE1}]
    Program State not yet Set in register and Counter is within Timeout
  [/cover] */
  RetError = FlsLoader_lCheckBitSet(&DMU_HF_OPERATION.U, \
                                    FLSLOADER_PROG_BIT_MASK);

  /* [cover parentID={640E867F-39A6-4de0-A8CA-D3F1D13DBBC0}]
    Flash type is PFlash
  [/cover] */
  if ((FlashType != FLSLOADER_DFLASH_BANK0))
  {
    /* [cover parentID={877B696C-6C37-4473-95E3-66E5E1AC97D1}]
      Enable back the end init protection
    [/cover] */
    FlsLoader_lSetSafetyENDINIT();
    /* [cover parentID={B4E7FB35-6AAA-4008-8DB6-8843FA216C4F}][/cover] */
    FlsLdr_ExclArea_PfProg_Exit();
  }

  /* [cover parentID={4FAE36AD-27EC-42da-BB65-4405BC8C9C74}]
  Program State Set in Register within Timeout
  [/cover] */
  if (RetError == FLSLOADER_E_OK)
  {
    BaseTicks = Mcal_DelayGetTick();
    do
    {
      CurrTicks = Mcal_DelayGetTick();
      ElapsedTicks = (uint32)((CurrTicks - BaseTicks) &\
                            FLSLOADER_OVERFLOW_MASK);
    }while(ElapsedTicks < BusySetTicks);

    /* [cover parentID={6E127B21-A9EB-40a7-AE64-053BB18F71C5}]
     Check if burst write is completed within maximum time calculated
    [/cover] */
    /*Poll for burst timeout*/
    RetError = FlsLoader_lBusyCheck(BurstTimeoutTicks);

    /* [cover parentID={C778EC9F-DDAE-4664-AEEA-A3917563EC4B}]
       Flash busy Reset within Timeout
    [/cover] */
    if (RetError == FLSLOADER_E_OK)
    {
      /*Read PVER error status*/
      WriteErrStat = DMU_HF_ERRSR.B.PVER;

      /*Read OPER error status*/
      WriteErrStat |= DMU_HF_ERRSR.B.OPER;

      /* [cover parentID={9E8C606E-CFB0-4ea4-B3E3-E0DAB398ABAF}] [/cover] */
      /* If PVER or OPER set, return E_NOT_OK */
      if (WriteErrStat == FLSLOADER_BIT_SET)
      {
        RetError = FLSLOADER_E_NOT_OK;
      }
    }
    else
    {
       RetError = FLSLOADER_E_OPERR;
    }
  }

  return RetError;

}

/*******************************************************************************
** Syntax           : FlsLoader_ReturnType FlsLoader_lBusyCheck(\             **
**                                                 const uint32 TimeoutTicks) **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : TimeoutTicks: Counts for busy timeout check             **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FLSLOADER_E_OK: Flash busy status is reset within given **
**                    timeout counts.                                         **
**                    FLSLOADER_E_NOT_OK: Flash busy status did not reset     **
**                    within given timeout counts.                            **
**                                                                            **
** Description      : This function polls the hardware busy status for given  **
**                    timeout counts and returns E_OK if the busy status      **
**                    is reset within timeout else it returns E_NOT_OK.       **
**                    If call out feature is enabled, this function provides  **
**                    call out function to application at every call out time **
**                    configured by user.                                     **
*******************************************************************************/
/* [cover parentID={CB90D3E5-B1D0-4a94-AA7A-4E4725FF3064}][/cover] */
/* MISRA2012_RULE_8_7_JUSTIFICATION: Function is referenced in FlsLoader.c and
   FlsLoader_Platform.c */
FlsLoader_ReturnType FlsLoader_lBusyCheck(\
                                    const uint32 TimeoutTicks)
{
  volatile uint32      FlashBusyStat;
  uint32               FlashOperStat;
  uint32               BaseTicks;
  uint32               CurrTicks;
  uint32               ElapsedTicks;
  FlsLoader_ReturnType RetError;
  #if (FLSLOADER_CALLOUT_FUNC == STD_ON)
  uint32               CalloutTicks;
  uint32               TickResolution;
  #endif

  RetError = FLSLOADER_E_NOT_OK;

  /*Base STM count for loop check*/
  BaseTicks = Mcal_DelayGetTick();

  #if (FLSLOADER_CALLOUT_FUNC == STD_ON)
  /* [cover parentID={A99EDACF-171F-4263-8C35-A7B5DF465A48}]
   Call out is enabled
  [/cover] */
  /*Resolution of each STM count in nanoseconds*/
  TickResolution = Mcal_DelayTickResolution();

  /*Counts required for configured callout*/
  CalloutTicks   = (uint32) (FLSLOADER_CALLOUT_TIME / TickResolution);
  #endif

  do
  {
    /*read flash busy status*/
    FlashBusyStat = (DMU_HF_STATUS.U & (uint32)FLSLOADER_FLASH_BUSY_MASK);

    /*Current STM count in loop*/
    CurrTicks = Mcal_DelayGetTick();

    #if (FLSLOADER_CALLOUT_FUNC == STD_ON)
    /* [cover parentID={7AA5A4BF-EC25-4ef2-A6E1-28C1A1FAD550}]
       Call out is enabled
    [/cover] */
    /* [cover parentID={32323651-B202-4f96-821C-0694551B9DCB}]
       Calculate counts required for configured call out time
    [/cover] */
    /*counts elapsed since last callout*/
    ElapsedTicks = (uint32)((CurrTicks - FlsLoader_CalloutTick) &\
                            FLSLOADER_OVERFLOW_MASK);

    /* [cover parentID={6B1DE8EE-7838-4e63-AFE4-6DAA37E385F3}]
     Elapsed counts exceeds counts for configured call out time
    [/cover] */
    /*elapsed counts exceed or equals required callout counts*/
    if(ElapsedTicks >= CalloutTicks)
    {
      /*Set next sampling point for callout*/
      FlsLoader_CalloutTick += CalloutTicks;

      /*give application callout*/
      /* [cover parentID={741A4A74-141F-4606-A26C-C63217C73F9D}]
       Invoke application call out function
      [/cover] */
      (FlsLoader_CallOutPtr)();
    }
    #endif

    /*counts elapsed in the loop*/
    ElapsedTicks = (uint32)((CurrTicks - BaseTicks) &\
                            FLSLOADER_OVERFLOW_MASK);

    /* [cover parentID={56DF2F8F-D0B7-40f4-AAA5-82BA00348733}]
     Flash busy status is reset
    [/cover] */
    /*flash busy reset, Return E_OK*/
    if(FlashBusyStat == FLSLOADER_BIT_RESET)
    {
      RetError = FLSLOADER_E_OK;
    }

    /*Read OPER error status*/
    FlashOperStat = DMU_HF_ERRSR.B.OPER;

  } while(((FlashBusyStat != 0U) && (ElapsedTicks < TimeoutTicks)) &&\
             (FlashOperStat != FLSLOADER_BIT_SET));
  /* [cover parentID={6132FD5D-2353-427f-BA02-69AC6ACBA736}]
   Elapsed counts exceeds input timeout counts and flash busy status is
   not yet reset
  [/cover] */

  return RetError;
}

/*******************************************************************************
** Syntax           : FlsLoader_ReturnType FlsLoader_lCheckBitSet(\           **
**                                                 const uint32 TimeoutTicks) **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : RegAddress: Address of the DMU register whose bit need  **
**                    to be checked for setting                               **
**                    BitPosMask: Bit position mask value of the bit to be    **
                      checked for checking                                    **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FLSLOADER_E_OK: Bit is set within timeout and no errors **
**                    are reported                                            **
**                    FLSLOADER_E_NOT_OK: Bit is not set within timeout or    **
**                    either sequence error or protection error occured.      **
**                                                                            **
** Description      : This function polls the status of bit identified by     **
**                    parameter BitPosMask and checks if it is set within     **
**                    defined timeout and no errors are reported.             **
*******************************************************************************/
/* [cover parentID={661C6F7F-D7CC-402a-AD85-CD68ABD4C4B6}][/cover] */
/* MISRA2012_RULE_8_7_JUSTIFICATION: Function is referenced in FlsLoader.c and
   FlsLoader_Platform.c */
FlsLoader_ReturnType FlsLoader_lCheckBitSet(\
                                   const volatile void* const RegAddress, \
                                   const uint32 BitPosMask)
{
  uint32 RegData;
  uint32 InCount;
  uint32 SeqErrStat;
  uint32 ProtErrStat;
  FlsLoader_ReturnType RetError;
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
     by violating this MISRA rule.*/
  const volatile uint32* const RegisterAddr = RegAddress;

  RetError = FLSLOADER_E_NOT_OK;

  RegData = (*RegisterAddr) & BitPosMask;

  SeqErrStat = DMU_HF_ERRSR.B.SQER;

  ProtErrStat = DMU_HF_ERRSR.B.PROER;

  InCount = 0u;

  /* [cover parentID={4E7C0F75-BB5E-44f5-B720-1E33A13803B2}]
  [/cover] */
  /*Loop until the bit is set or any error is reported*/
  while((RegData == FLSLOADER_ZERO_DATA) && \
        (SeqErrStat != FLSLOADER_BIT_SET) && \
        (ProtErrStat != FLSLOADER_BIT_SET) && \
        (InCount < FLSLOADER_CMDCYCLE_TIMEOUT))
  {
    InCount++;

    RegData = (*RegisterAddr) & BitPosMask;

    SeqErrStat = DMU_HF_ERRSR.B.SQER;

    ProtErrStat = DMU_HF_ERRSR.B.PROER;
  }

  /* [cover parentID={EDC81287-B213-41c9-913D-2A9C6E89E48F}]
  [/cover] */
  /*Check if bit was set or any error */
  if ((SeqErrStat != FLSLOADER_BIT_SET) && \
      (ProtErrStat != FLSLOADER_BIT_SET) && \
      (InCount < FLSLOADER_CMDCYCLE_TIMEOUT))
  {
    RetError = FLSLOADER_E_OK;
  }

  return RetError;
}

#define FLSLOADER_STOP_SEC_WRITEERASE_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "FlsLoader_MemMap.h"
#define FLSLOADER_START_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "FlsLoader_MemMap.h"

/* Enable/Disable the API FlsLoader_GetVersionInfo*/
#if (FLSLOADER_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={91723AB7-7D52-430d-A346-DCB00D3A5EFA}] **
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
/* [cover parentID={BFD4C28D-4860-4819-9581-A39B47300438}]
FlsLoader_GetVersionInfo
[/cover] */
void FlsLoader_GetVersionInfo( Std_VersionInfoType * const VersionInfoPtr)
{

  /* [cover parentID={76F37427-12D5-405e-B76B-C927392AD14B}]
  DET Enabled
  [/cover] */
  #if ( FLSLOADER_DEV_ERROR_DETECT == STD_ON )

  /* [cover parentID={38B93154-7DB4-42d1-82A7-612B9CA6ADCE}]
  Is Version info pointer Null
  [/cover] */
  if(VersionInfoPtr == NULL_PTR)
  {
    /* [cover parentID={76F37427-12D5-405e-B76B-C927392AD14B}]
    DET Enabled
    [/cover] */
    /* [cover parentID={BC016B6D-7645-4b32-A8DA-EF7A0C7808EB}]
    Report DET error FLSLOADER_E_PARAM_POINTER
    [/cover] */
    /*Report DET on DriverState error*/
    (void)Det_ReportError(FLSLOADER_MODULE_ID,
                        FLSLOADER_INSTANCE_ID,
                        FLSLOADER_SID_GETVERSIONINFO,
                        FLSLOADER_E_PARAM_POINTER);
  }
  else
  #endif
  {
    /* [cover parentID={6E25EA55-004E-4b03-8351-06B68541CA7B}]
    Return Fls Loader module ID and SW version info
    [/cover] */
    VersionInfoPtr->moduleID         = FLSLOADER_MODULE_ID;
    VersionInfoPtr->sw_major_version = FLSLOADER_SW_MAJOR_VERSION;
    VersionInfoPtr->sw_minor_version = FLSLOADER_SW_MINOR_VERSION;
    VersionInfoPtr->sw_patch_version = FLSLOADER_SW_PATCH_VERSION;
    VersionInfoPtr->vendorID         = FLSLOADER_VENDOR_ID;
  }
}
#endif /* (FLSLOADER_VERSION_INFO_API == STD_ON) */

#define FLSLOADER_STOP_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "FlsLoader_MemMap.h"
