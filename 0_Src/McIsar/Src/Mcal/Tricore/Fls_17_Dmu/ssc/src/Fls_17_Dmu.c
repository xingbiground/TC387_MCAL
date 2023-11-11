/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2023)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : Fls_17_Dmu.c                                                **
**                                                                           **
**  VERSION    :  44.0.0                                                     **
**                                                                           **
**  DATE       :  2023-05-22                                               **
**                                                                           **
**  VARIANT    : Variant PB                                                  **
**                                                                           **
**  PLATFORM   : Infineon AURIX2G                                            **
**                                                                           **
**  AUTHOR     : DL-AUTOSAR-Engineering                                      **
**                                                                           **
**  VENDOR     : Infineon Technologies                                       **
**                                                                           **
**  DESCRIPTION: This file contains                                          **
**                 - functionality of Flash driver                           **
**                                                                           **
**  SPECIFICATION(S) : Specification of FLS Driver,                          **
**                           AUTOSAR Release 4.2.2 and 4.4.0                 **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: No                                      **
**                                                                           **
******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* [cover parentID={CE0E1013-F855-45f6-A341-3134FAB115C5}][/cover] */
/* [cover parentID={325361F6-5AA1-4027-A491-D8A970E7FE8C}][/cover] */
/* [cover parentID={93231028-6942-4390-A06D-5ACF5EB86F2F}][/cover] */
/* [cover parentID={34C9BD42-7196-4ba0-B305-4C5EE582F134}][/cover] */

#include "IfxDmu_reg.h"
#include "IfxDmu_bf.h"
#include "IfxFsi_reg.h"

/* Inclusion of Flash header file */
/* [cover parentID={93E8BC5E-CDEC-4da2-9273-77E9147D1B32}][/cover] */
#include "Fls_17_Dmu.h"

/* Inclusion of Flash command cycles file */
#include "Fls_17_Dmu_ac.h"

/* Scheduled function header file */
/* [cover parentID={7C4DD5F8-940F-4e60-A4E3-6E198B3431C3}][/cover] */
#include "SchM_Fls_17_Dmu.h"

#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
#include "Mcal_SafetyError.h"
#endif

/* [cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}]
Autosar variant management[/cover] */

/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/

#ifndef FLS_17_DMU_AR_RELEASE_MAJOR_VERSION
#error "FLS_17_DMU_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#ifndef FLS_17_DMU_AR_RELEASE_MINOR_VERSION
  #error "FLS_17_DMU_AR_RELEASE_MINOR_VERSION is not defined."
#endif

#ifndef FLS_17_DMU_AR_RELEASE_REVISION_VERSION
  #error "FLS_17_DMU_AR_RELEASE_REVISION_VERSION is not defined."
#endif

#if ( FLS_17_DMU_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION)
  #error "FLS_17_DMU_AR_RELEASE_MAJOR_VERSION does not match."
#endif

#if ( FLS_17_DMU_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION)
  #error "FLS_17_DMU_AR_RELEASE_MINOR_VERSION does not match."
#endif

#if ( FLS_17_DMU_AR_RELEASE_REVISION_VERSION != \
                                          MCAL_AR_RELEASE_REVISION_VERSION)
  #error "FLS_17_DMU_AR_RELEASE_REVISION_VERSION does not match."
#endif

/* [cover parentID={D5FA2170-40E5-46c9-A804-BFA8D0202805}][/cover] */
/*
    DRIVER VERSION CHECK FOR FLS MODULE INCLUSION
*/

#ifndef FLS_17_DMU_SW_MAJOR_VERSION
#error "FLS_17_DMU_SW_MAJOR_VERSION is not defined. "
#endif

#ifndef FLS_17_DMU_SW_MINOR_VERSION
#error "FLS_17_DMU_SW_MINOR_VERSION is not defined. "
#endif

#ifndef FLS_17_DMU_SW_PATCH_VERSION
#error "FLS_17_DMU_SW_PATCH_VERSION is not defined. "
#endif

#if (FLS_17_DMU_SW_MAJOR_VERSION != 20U)
#error "FLS_17_DMU_SW_MAJOR_VERSION does not match."
#endif

#if (FLS_17_DMU_SW_MINOR_VERSION != 25U)
#error "FLS_17_DMU_SW_MINOR_VERSION does not match."
#endif

#if (FLS_17_DMU_SW_PATCH_VERSION != 0U)
#error "FLS_17_DMU_SW_PATCH_VERSION does not match."
#endif

/* [cover parentID={703AAC5B-F330-40d2-98BC-02D1C0CE7C27}]
[/cover]
*/
/*
    VERSION CHECK FOR DET MODULE INCLUSION
*/
#if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) || \
(FLS_17_DMU_SAFETY_ENABLE == STD_ON)

#ifndef DET_AR_RELEASE_MAJOR_VERSION
#error "DET_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#if ( DET_AR_RELEASE_MAJOR_VERSION != 4U )
#error "DET_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

#endif /* (FLS_DEV_ERROR_DETECT == STD_ON) */


/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

#define FLS_ONE_VALUE                (1U)

/* Mask to get the page start address */
#define FLS_PAGE_START_ADDR_MASK     (0xFFFFFFF8U)

/* Page size mask used for checking if address is page aligned*/
#define FLS_PAGE_SIZE_MASK        (FLS_17_DMU_PAGE_SIZE-1U)

#if(FLS_17_DMU_IFX_FEE_USED == STD_ON)
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled. Hence this macro will be unused
in other pre-compile conditions. There is no side effect violating this rule. */
#define FLS_WL_SIZE_MASK          (512U-1U)
#endif

/* Protection and sequence errors */
#define FLS_PROER_SQER_ERROR        (0x00000006U)

/* Operational error */
#define FLS_OPER_ERROR              (0x00000001U)
/* Uncorrectable bit error */
#if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_ON)
#define FLS_ERRM_BIT_MASK               (0x00000008U)
#define FLS_ECCERRPAGEADDR_INIT_VAL     (0xFFFFFFFFU)
#else
#define FLS_AERM_BIT_MASK               (0x00080000U)
#endif
/* Dflash busy status */
#define FLS_D0BUSY                  (0x00000001U)
/* Dflash Waitstate mask */
#define FLS_DMU_WAITSTATES_MASK     (0xFFF8FF00U)
/*SELD0 for Margin Select*/
#define FLS_DMU_SELD0_MASK          (0xFFFFFFFCU)
/*Normal mode Mask*/
#define FLS_DMU_PCONTROL_ESLDIS_MASK    (0x00030000U)

/*Timeout value for margin switch*/
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled. Hence this macro will be unused
in other pre-compile conditions. There is no side effect violating this rule. */
#define FLS_DMU_MARGIN_TIMEOUT      (2000U)
/*End of Busy Interrupt Bit*/

#if( FLS_17_DMU_USE_INTERRUPTS == STD_ON)
#define FLS_DMU_EER_EOBM_MASK       (0x80000000U)
#endif

#if( FLS_17_DMU_USE_INTERRUPTS == STD_ON)
#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
#if (FLS_17_DMU_USE_ERASESUSPEND == STD_ON)
#define FLS_DMU_SUSPEND_STATE  (0xAECDBEEFU)
#define FLS_DMU_SUSPEND_RESET  (0U)
#endif

#if  (FLS_17_DMU_CANCEL_API  ==  STD_ON)
#define FLS_DMU_CANCEL_STATE (0xBAECDEADU)
#define FLS_DMU_CANCEL_RESET (0U)
#endif
#endif
#endif

#if (FLS_17_DMU_USE_ERASESUSPEND == STD_ON)
#define FLS_RESUMEERASE_TIMEOUT     (500U)
#endif

/*Trap Disable*/
#define FLS_DMU_ECCC_TRAPDIS_MASK   (0xC0000000U)

/*Enable CLR the AERM bit*/
#define FLS_DMU_ECCC_CLR        (0x00000003U)

#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
#define FLS_DMU_MODE_CHK            (0x00000003U)
#endif

#if (FLS_17_DMU_INITCHECK_API == STD_ON)
/*Init Check registers*/
#define FLS_REG_CLR_CHK               (0xFFFFFFFFU)
#define FLS_REG_COMM_CLRCHK           (uint8)(0xFF)
#define FLS_ERRSRREG_CLRCHK           (0x0000001FU)
#define FLS_DMU_SENSING_MODE_CLR_CHK    (0x00000003U)
#define FLS_DMU_CRANKING_MODE_CLR_CHK   (0x00000003U)
#define FLS_DMU_NORMAL_MODE_CHK         (0xFFFFFFFFU)
#define FLS_DMU_PROTECTION_CLR_CHK      (0xFFFFFFFFU)
#endif

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled. Hence this macro will be unused
in other pre-compile conditions. There is no side effect violating this rule. */
#define FLS_DMU_ECCW_CLR_CHK          (0xFFFFFFFFU)
#define FLS_DMU_ECCC_CLR_CHK          (0xC0000000U)
#define FLS_DMU_ERR_CLR               (0x0000003EU)

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is not referenced. */
#define FLS_DMU_WAITSTATES_MASK_CHK   (0x000000FFU)

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled. Hence this macro will be unused
in other pre-compile conditions. There is no side effect violating this rule. */
#define FLS_DMU_SELD0_MASK_CHK        (0x00000003U)

/*
#define IFX_DMU_HF_ERRSR_OPER_MSK (0x1u)
#define IFX_DMU_HF_ERRSR_PVER_OFF (3u)
#define IFX_DMU_HF_ERRSR_PVER_MSK (0x1u)
#define IFX_DMU_HF_ECCC_TRAPDIS_MSK (0x3u)
*/

/*Init status for the API*/
#define FLS_INITIALIZED            ((uint32)1)
#define FLS_UNINITIALIZED          ((uint32)0)

/* Word size - 4 bytes */
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled. Hence this macro will be unused
in other pre-compile conditions. There is no side effect violating this rule. */
#define FLS_WORD_SIZE              (4U)

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled. Hence this macro will be unused
in other pre-compile conditions. There is no side effect violating this rule. */
#define FLS_WORD_SIZE_MASK        (FLS_WORD_SIZE - 1U)

#if (FLS_17_DMU_USE_ERASESUSPEND == STD_ON)
#define SUSPEND_CLR_OFF            (0x2U)
#endif

/* Mask to check the Mod4K result */
#define FLS_MOD4K_MASK          (0x0FFFU)
/* Number of shifts to do division or multiplication by 4K -> 2^12 */
#define FLS_4KSHIFT_VAL          (12U)
/* Mask to check the Mod64 result */
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is not referenced */
#define FLS_MOD64_MASK          (0x3FU)
/* Number of shifts to do division or multiplication by 64 -> 2^6 */
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is not referenced */
#define FLS_64SHIFT_VAL          (6U)

/* Recommended maximum number of sectors to be erased in 1 erase command cycle
*/
#define FLS_MAXERASE_SEC          (64U)

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled. Hence this macro will be unused
in other pre-compile conditions. There is no side effect violating this rule. */
#define FLS_VERIFYSECTOR_CHK_VAL   (0xDEADBEEFU)

/*Read with hard margin selection value */
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled. Hence this macro will be unused
in other pre-compile conditions. There is no side effect violating this rule. */
#define FLS_READHARDMARGIN_VAL      (3U)

/*Tight0- Tight margin for 0 (low) level */
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled. Hence this macro will be unused
in other pre-compile conditions. There is no side effect violating this rule. */
#define FLS_TIGHT0MARGIN_VAL       (0xfffffeffU)

/*Hardening*/
#if(FLS_17_DMU_IFX_FEE_USED == STD_ON)
/*Mask to extract the TBE (3 bit error) status in FSI_COMM_2 */
#define FLS_COMM2TBE_MASK (0xE0U)

/* Register setting value for control gate voltage of 4.1V */
#define FLS_CTRLGATEVOLTAGE_VAL (0x20)

/* Mask to extract the result stored (5bits) in FSI_COMM_2.COMM2[4:0] */
#define FLS_FSICOMM2RES_MASK          ((uint8)(0x1FU))

#define FLS_DMU_HARDEN_PAGE_ALIGN      (0x8U)
#define FLS_DMU_HARDEN_WORD_ALIGN      (0xFFFFFFF7U)

/*Timeout for User Content Count*/
#define FLS_USRCONTENT_PAGE_TIMEOUT         (21000U)
#define FLS_USRCONTENT_WL_TIMEOUT         (100000U)
/* 8 bits shift value */
#define FLS_SHIFT8BITS_VAL          ((uint8)(8U))

#endif /*Hardening*/

#define FLS_COMM_RESET_VAL         ((uint8)0x00)

#define FLS_SUSPEND_ERR_CLR        (0x2U)

/* Wordline fail count to be suported */
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled. Hence this macro will be unused
in other pre-compile conditions. There is no side effect violating this rule. */
#define FLS_WL_FAIL_COUNT (2U)

#if (FLS_17_DMU_IFX_FEE_USED == STD_ON)
#define FLS_EVER_CHK ((uint8)(0x1))
#endif

#if (FLS_17_DMU_INIT_API_MODE == FLS_17_DMU_MCAL_SUPERVISOR)

/* Library APIs  */

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for User
mode support in code. This is done to enhance readability and simplicity of
code. No side effects foreseen by violating this MISRA rule. */
#define FLS_17_DMU_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(RegAdd,Data) \
                                     Mcal_WritePeripEndInitProtReg(RegAdd,Data)


/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for User
mode support in code. This is done to enhance readability and simplicity of
code. No side effects foreseen by violating this MISRA rule. */
#define FLS_17_DMU_SFR_INIT_DEINIT_WRITE32(reg, value)  \
                                              ((*(reg)) = (uint32)(value))

#else
#include "McalLib_OsStub.h"
/* [cover parentID={1A65EADD-AFD0-4845-B2D2-8257E086DD67} ][/cover] */

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for User
mode support in code. This is done to enhance readability and simplicity of
code. No side effects foreseen by violating this MISRA rule. */
#define FLS_17_DMU_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(RegAdd,Data) \
                                 MCAL_LIB_WRITEPERIPENDINITPROTREG(RegAdd,Data)


/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for User
mode support in code. This is done to enhance readability and simplicity of
code. No side effects foreseen by violating this MISRA rule. */
#define FLS_17_DMU_SFR_INIT_DEINIT_WRITE32(RegAdd, Data)\
                        MCAL_SFR_OS_WRITE32(FLS_17_DMU_MODULE_ID,RegAdd,Data)

#endif /*(FLS_17_DMU_INIT_API_MODE == MCAL_SUPERVISOR)*/

#if (FLS_17_DMU_RUNTIME_API_MODE == FLS_17_DMU_MCAL_SUPERVISOR)
/* Library APIs  */
#if((FLS_17_DMU_IFX_FEE_USED == STD_ON) || \
(FLS_17_DMU_ECC_ERROR_INFO_API  ==  STD_OFF) || \
(FLS_17_DMU_ERASE_VERIFICATION == STD_ON))
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for User
mode support in code. This is done to enhance readability and simplicity of
code. No side effects foreseen by violating this MISRA rule. */
#define FLS_17_DMU_LIB_RUNTIME_WRITEPERIPENDINITPROTREG(RegAdd,Data) \
                                     Mcal_WritePeripEndInitProtReg(RegAdd,Data)

#endif
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for User
mode support in code. This is done to enhance readability and simplicity of
code. No side effects foreseen by violating this MISRA rule. */
#define FLS_17_DMU_SFR_RUNTIME_WRITE32(reg, value)\
                                   ((*(reg)) = (uint32)(value))
#else
#include "McalLib_OsStub.h"
#if((FLS_17_DMU_IFX_FEE_USED == STD_ON) || \
(FLS_17_DMU_ECC_ERROR_INFO_API  ==  STD_OFF) || \
(FLS_17_DMU_ERASE_VERIFICATION == STD_ON))
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for User
mode support in code. This is done to enhance readability and simplicity of
code. No side effects foreseen by violating this MISRA rule. */
#define FLS_17_DMU_LIB_RUNTIME_WRITEPERIPENDINITPROTREG(RegAdd,Data) \
                                 MCAL_LIB_WRITEPERIPENDINITPROTREG(RegAdd,Data)
#endif
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for User
mode support in code. This is done to enhance readability and simplicity of
code. No side effects foreseen by violating this MISRA rule. */
#define FLS_17_DMU_SFR_RUNTIME_WRITE32(RegAdd, Data)\
                       MCAL_SFR_OS_WRITE32(FLS_17_DMU_MODULE_ID,RegAdd,Data)
#endif /*(FLS_17_DMU_RUNTIME_API_MODE == MCAL_SUPERVISOR)*/

/*****************************************************************************
**                      Private Function Declarations                       **
*****************************************************************************/

#define FLS_17_DMU_START_SEC_CODE_ASIL_B_LOCAL

/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}][/cover] */
/* [cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}][/cover] */
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}][/cover] */
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}][/cover] */
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}][/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}][/cover] */

/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. Even though the memmap
   header is included multiple times, the contents of the file are protected
   from multiple definition / inclusion. */
#include "Fls_17_Dmu_MemMap.h"

static void Fls_lMainErase(void);

static void Fls_lMainWrite(void);

static void Fls_lMainRead(void);

static void Fls_lMainCompare(void);

static void Fls_lMainBlankCheck(void);

static void Fls_lErrorHandler(const uint8 JobType);

LOCAL_INLINE uint32 Fls_lGetPageAddress(const uint32 address);

#if (FLS_17_DMU_TIMEOUT_SUPERVISION == STD_ON)
static void Fls_lTimeOutMonitoring(const uint8 ServiceID);
#endif

#if (FLS_17_DMU_ERASE_VERIFICATION == STD_ON)
LOCAL_INLINE Std_ReturnType Fls_lPageEraseCheck(
  uint32 *const AddrCheckPtr,
  const uint32 Length,
  const uint8 ServiceID);
#endif

#if (FLS_17_DMU_IFX_FEE_USED == STD_ON)
static Std_ReturnType Fls_lLocalVerifyErase(
  const Fls_17_Dmu_AddressType TargetAddress,
  uint32 *const UnerasedWordlineAddressPtr,
  uint8 *const UnerasedWordlineCountPtr,
  const uint8 Sector, const uint32 value);
#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
LOCAL_INLINE uint8 Fls_lHardenSafetyChk(
  const Fls_17_Dmu_AddressType TargetAddress,
  const uint8 AlignChk);
#endif
#endif

#if (FLS_17_DMU_IFX_FEE_USED == STD_ON)
static void Fls_lEverFlagChkFail(void);
#endif

#if (FLS_17_DMU_USE_ERASESUSPEND == STD_ON)
LOCAL_INLINE boolean Fls_lSpndTimeout(const uint32 TimeOutCount);
#endif

static void Fls_lMainWriteJobStart(const uint32 PhysicalAddress);

static void Fls_lMainEraseJobStart(const uint32 PhysicalAddress);

LOCAL_INLINE boolean Fls_lPverChk(void);

#if (FLS_17_DMU_INITCHECK_API == STD_ON)
static Std_ReturnType Fls_lInitCheck(void);
#endif

#if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON)|| \
(FLS_17_DMU_SAFETY_ENABLE == STD_ON)
LOCAL_INLINE uint8 Fls_lBusyDET_Read(
  const Fls_17_Dmu_StateType *const StatePtr);

LOCAL_INLINE uint8 Fls_lBusyDET_Write(const Fls_17_Dmu_StateType *const
                                      StatePtr);

LOCAL_INLINE uint8 Fls_lBusyDET_Erase(const Fls_17_Dmu_StateType *const
                                      StatePtr);

#if (FLS_17_DMU_COMPARE_API == STD_ON)
LOCAL_INLINE uint8 Fls_lBusyDET_Compare(
  const Fls_17_Dmu_StateType*const
  StatePtr);
#endif

static uint8 Fls_lUninitDET(const uint8 ServiceID);

LOCAL_INLINE Std_ReturnType Fls_lCheckEraseDet(
  const Fls_17_Dmu_AddressType TargetAddress,
  const Fls_17_Dmu_LengthType Length);

LOCAL_INLINE Std_ReturnType Fls_lCheckWriteDet(
  const Fls_17_Dmu_AddressType TargetAddress,
  const uint8 *const SourceAddressPtr,
  const Fls_17_Dmu_LengthType Length);

/* API to check DET errors in Fls_Init API. */
static void Fls_lReportError(const uint8 Fls_Sid, const uint8 ErrorId);

#endif /* End of FLS_DEV_ERROR_DETECT, FLS_17_DMU_SAFETY_ENABLE */

/*Check for command sequence error and protection error*/
LOCAL_INLINE uint32 Fls_lChkSeqProtErrors(void);

/*Check for operational error */
LOCAL_INLINE uint32 Fls_lChkOperError(void);

/*Check for double bit errors (DBER) */
LOCAL_INLINE uint32 Fls_lChkBitErrors(void);

/* Return the Busy status of the Data Flash Bank */
/* FLASH0_FSR.U & (1U<< (1U + (Bank) ) */
LOCAL_INLINE uint32 Fls_lHWBusyCheck(void);

/* get the write mode , page mode or burst mode */
LOCAL_INLINE uint8 Fls_lGetWriteMode(void);

/* Get max read length according to the FLS mode */
LOCAL_INLINE Fls_17_Dmu_LengthType Fls_lGetReadModeLength(void);

LOCAL_INLINE MemIf_ModeType Fls_lSetDefaultMode(void);


#define FLS_17_DMU_STOP_SEC_CODE_ASIL_B_LOCAL
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}][/cover] */

/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. Even though the memmap
   header is included multiple times, the contents of the file are protected
   from multiple definition / inclusion. */
#include "Fls_17_Dmu_MemMap.h"

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}][/cover] */

/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. Even though the memmap
   header is included multiple times, the contents of the file are protected
   from multiple definition / inclusion. */
#include "Fls_17_Dmu_MemMap.h"

/* MISRA2012_RULE_8_4_JUSTIFICATION: The variable declaration and
definition is correct and compatible.*/
const Fls_17_Dmu_ConfigType *Fls_ConfigPtr;

/* Initialize status. */
static uint32 Fls_17_Dmu_InitStatus;

#if(FLS_17_DMU_IFX_FEE_USED == STD_OFF)
#if(FLS_17_DMU_SAFETY_ENABLE == STD_ON)
#if(FLS_17_DMU_USE_INTERRUPTS == STD_ON)
#if  (FLS_17_DMU_CANCEL_API  ==  STD_ON)
static uint32 Fls_17_Dmu_JobCancelFlag;
#endif
#if (FLS_17_DMU_USE_ERASESUSPEND == STD_ON)
static volatile uint32 Fls_17_Dmu_EraseSuspendFlag;
#endif
#endif
#endif
#endif

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
/* [cover parentID={8A00BEA5-55E8-4faa-8270-04E4059138F6}]
[/cover]
*/
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover]
*/

/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. Even though the memmap
   header is included multiple times, the contents of the file are protected
   from multiple definition / inclusion. */
#include "Fls_17_Dmu_MemMap.h"



/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define FLS_17_DMU_START_SEC_CODE_ASIL_B_LOCAL

/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. Even though the memmap
   header is included multiple times, the contents of the file are protected
   from multiple definition / inclusion. */
#include "Fls_17_Dmu_MemMap.h"
/*******************************************************************************
** Traceability     : [cover parentID={E35FF093-4D81-429d-87D5-8A59FAFBBEFE}] **
**                                                                            **
** Syntax : void Fls_17_Dmu_Init(const Fls_17_Dmu_ConfigType* const ConfigPtr)**
**                                                                            **
** Service ID: 0x00                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  ConfigPtr - Pointer to configuration set                **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : Driver Module Initialization function                        **
** Service for FLASH initialization. The Initialization function shall        **
** initialize all Flash relevant registers with the values of the structure   **
** referenced by the parameter ConfigPtr.                                     **
**                                                                            **
*******************************************************************************/
void Fls_17_Dmu_Init(const Fls_17_Dmu_ConfigType *const ConfigPtr)
/* [cover parentID={E35FF093-4D81-429d-87D5-8A59FAFBBEFE}][/cover] */
{
  Fls_17_Dmu_StateType  *StatePtr;
  uint32 DFlash0WaitState;
  uint32 BitChange;
  uint32 OperErrChk;

  /* [cover parentID={847791BC-14C3-4fea-86A4-6F564E93786E}]
  Is the Configuration point NULL ?
  [/cover] */
  if (ConfigPtr == NULL_PTR)
  {
    /* [cover parentID={052A4F15-6F3C-4888-A3F0-5E10718631CC}]
    Report DET error
    [/cover] */
    /* Report to DET */
    #if( FLS_17_DMU_DEV_ERROR_DETECT == STD_ON ) || \
    (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
    Fls_lReportError(FLS_17_DMU_SID_INIT, FLS_17_DMU_E_PARAM_CONFIG);
    #endif
  }

  /* [cover parentID={C740BB47-7648-4040-BD5F-CC72896D6A3D}]
  DET Enabled
  [/cover] */

  #if( FLS_17_DMU_DEV_ERROR_DETECT == STD_ON ) || \
  (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  /* Check if the driver is BUSY */
  /* [cover parentID={D8E7C847-0D6E-436d-9540-BED71955B138}]
    If the FLS driver Busy ?
    [/cover] */
  else if(ConfigPtr->FlsStateVarPtr->FlsJobType != FLS_17_DMU_NONE )
  {
    /* [cover parentID={052A4F15-6F3C-4888-A3F0-5E10718631CC}]
    Report DET error
    [/cover] */
    Fls_lReportError(FLS_17_DMU_SID_INIT,
                     FLS_17_DMU_E_BUSY);/* Report to DET */
  }
  #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  /*Safety Error if HWbusy */
  /* [cover parentID={C9D014C9-199B-453e-9D92-76E32BFAA4CE}]
  HW Busy ?
  [/cover] */
  else if(Fls_lHWBusyCheck() != 0U)
  {
    /* [cover parentID={CF916B13-9CD9-4fb4-9A1B-6E2EEBB8BBB7}]
    [/cover] */
     Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                                 FLS_17_DMU_SID_INIT, FLS_17_DMU_SE_HW_BUSY);
  }
  /* [cover parentID={B2067ECE-C152-439b-93CD-73560BB1D9E4}]
  Is erase already suspended?
  [/cover] */
  else if(DMU_HF_SUSPEND.B.SPND == 1U)
  {
    /* [cover parentID={CF916B13-9CD9-4fb4-9A1B-6E2EEBB8BBB7}]
    [/cover] */
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_INIT, FLS_17_DMU_SE_INIT_FAILED);
  }
  /*If the mode is not set to Single Mode*/
  /* [cover parentID={7FE8445C-12B7-4fda-A5D5-1EF72B5E6AFE}]
  Is the mode set to Single ended sensing mode ?
  [/cover] */
  else if((DMU_HF_PROCONUSR.U & FLS_DMU_MODE_CHK) != 0U)
  {
    /* [cover parentID={CF916B13-9CD9-4fb4-9A1B-6E2EEBB8BBB7}]
    [/cover] */
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_INIT, FLS_17_DMU_SE_INIT_FAILED);
  }
  #endif
  #endif
  else
  {
    /*  ------------------------------------------------------------------ **
    **                 Flash Module Initialization                         **
    **  ------------------------------------------------------------------ */
    /*
    Initialization of flash driver and its relevant registers
    */

    /* [cover parentID={0A96AA98-47DC-407b-AC21-B5DD959EC624}]
    Store the configuration pointer
    Clears error flags of FSR register
    Set DFlash (DF0) Wait states according to configuration
    [/cover] */
    /* Store the configuration pointer */
    Fls_ConfigPtr = ConfigPtr;

    /* Reset the command sequencer */
    Fls_lResetReadCmdCycle();

    /*clear the previous errors*/
    Fls_lClearStatusCmdCycle();

    /* Set DFlash (DF0) Wait states according to configuration */
    /*MISRA2012_RULE_11_4_JUSTIFICATION: Conversion between pointer to
      object and integer type is permitted for special function registers*/
    DFlash0WaitState = DMU_HF_DWAIT.U;
    DFlash0WaitState &= FLS_DMU_WAITSTATES_MASK;
    DFlash0WaitState |= ConfigPtr->FlsWaitStates;


    /* Clear the following Error Interrupt masks */
    /* OPERM, SQERM, PROERM, PVERM, EVERM, EOBM */
    /*MISRA2012_RULE_11_4_JUSTIFICATION: Conversion between pointer to
      object and integer type is permitted for special function registers*/
    /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
    the object types as the address of the SFR is being passed.
    MISRA2012_RULE_11_1_JUSTIFICATION: Pointer cast is required to match
    the object types for SFR.*/
    FLS_17_DMU_SFR_INIT_DEINIT_WRITE32(\
                                       (volatile uint32 *)&DMU_HF_EER.U, 0U);

    /* Margin Read Selection is set as standard margin */
    /*As per hardware manual - "If a change between the standard and
     hard read margin setting is done, the system must wait a delay time
     hard tFL_MarginDel until the next read is requested."
     Therefore, the delay is not needed because there is no immediate read
     happening after the register is set-up.Read will happen as part of
     user request.*/
    /*MISRA2012_RULE_11_4_JUSTIFICATION: Conversion between pointer to
      object and integer type is permitted for special function registers*/
    BitChange = DMU_HF_MARGIN.U & FLS_DMU_SELD0_MASK;

    /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
    the object types as the address of the register is being passed.
    MISRA2012_RULE_11_1_JUSTIFICATION: Pointer cast is required to match
    the object types.*/
    FLS_17_DMU_SFR_INIT_DEINIT_WRITE32(\
                                       (volatile uint32 *)&DMU_HF_MARGIN.U, \
                                       BitChange);

    /*MISRA2012_RULE_11_4_JUSTIFICATION: Conversion between pointer to
      object and integer type is permitted for special function registers*/
    /* [cover parentID={6D6E729F-9EC7-4b69-B622-7F4ED402D8AA}]
    Initialise the DWAIT register
    [/cover] */
    /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
    the object types as the address of the register is being passed.*/
    /*MISRA2012_RULE_11_1_JUSTIFICATION: Pointer cast is required to match
    the object types.*/
    FLS_17_DMU_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(\
        (volatile uint32 *)&DMU_HF_DWAIT.U, \
        DFlash0WaitState);

    /* [cover parentID={D118D1FC-6455-4613-947D-0EFA7BF24499}]
    INTERRUPT ENABLED
    [/cover] */
    #if( FLS_17_DMU_USE_INTERRUPTS == STD_ON)
    /* Enable End of Busy Interrupt Mask */
    /*MISRA2012_RULE_11_4_JUSTIFICATION: Conversion between pointer to
      object and integer type is permitted for special function registers*/
    BitChange = (DMU_HF_EER.U | FLS_DMU_EER_EOBM_MASK);

    FLS_17_DMU_SFR_INIT_DEINIT_WRITE32(&DMU_HF_EER.U, \
                                       BitChange);

    #endif

    /* The uncorrectable ECC error trap is disabled and ECC status register
     is cleared to clear the errors. */
    /*MISRA2012_RULE_11_4_JUSTIFICATION: Conversion between pointer to
      object and integer type is permitted for special function registers*/
    BitChange = (DMU_HF_ECCC.U & FLS_DMU_ECCC_CLR_CHK);
    BitChange |= (FLS_DMU_ECCC_TRAPDIS_MASK | FLS_DMU_ECCC_CLR);

    /* [cover parentID={03DCC2CD-1DD2-4f54-A0DC-AAFA42F0740D}]

       [/cover] */
    /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
    the object types as the address of the register is being passed.*/
    /*MISRA2012_RULE_11_1_JUSTIFICATION: Pointer cast is required to match
    the object types.*/
    FLS_17_DMU_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(\
        (volatile uint32 *)&DMU_HF_ECCC.U, \
        BitChange);

    /*Enable the ECC correction*/
    /*MISRA2012_RULE_11_4_JUSTIFICATION: Conversion between pointer to
      object and integer type is permitted for special function registers*/
    /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
    the object types as the address of the SFR is being passed.*/
    /*MISRA2012_RULE_11_1_JUSTIFICATION: Pointer cast is required to match
    the object types for SFR.*/
    FLS_17_DMU_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(\
        (volatile uint32 *)&DMU_HF_ECCW.U, 0U);

    /*Clear the suspend registers*/
    /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
    the object types as the address of the register is being passed.*/
    FLS_17_DMU_SFR_INIT_DEINIT_WRITE32(\
                    (volatile uint32 *)&DMU_HF_SUSPEND, FLS_SUSPEND_ERR_CLR);


   /*Disable Cranking mode*/
   /*MISRA2012_RULE_11_4_JUSTIFICATION: Conversion between pointer to
    object and integer type is permitted for special function registers*/
   /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
    the object types as the address of the SFR is being passed.*/
   /*MISRA2012_RULE_11_1_JUSTIFICATION: Pointer cast is required to match
    the object types.*/
    FLS_17_DMU_SFR_INIT_DEINIT_WRITE32(\
                    (volatile uint32 *)&DMU_HF_CCONTROL.U, 0U);


    /* Enable normal mode */
    /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
    the object types as the address of the SFR is being passed.*/
    FLS_17_DMU_SFR_INIT_DEINIT_WRITE32((volatile uint32 *)\
                    &DMU_HF_PCONTROL.U, FLS_DMU_PCONTROL_ESLDIS_MASK);


    /*Reset the COMM1 and COMM2 values to system reset values*/
    /* [cover parentID={E1BD7A7A-7C40-4b22-8C1D-2A02D4D2B180}]
    Reset the value of FSI_COMM1 and FSI_COMM2 registers
    [/cover] */
    FSI_COMM_1.U = FLS_COMM_RESET_VAL;
    FSI_COMM_2.U = FLS_COMM_RESET_VAL;

    /*  ------------------------------------------------------------------ **
    **                 Global Variable Initialization                      **
    **  ------------------------------------------------------------------ */
    /*
    After having finished the module initialization,
    the Flash Driver state shall be set to FLS_17_DMU_IDLE and and the jobs
    result shall be set to FLS_17_DMU_JOB_OK.
    */

    /* [cover parentID={D3BE77D2-199E-463b-BDC0-2E35609756A1}]
       Initialise the Global variables
       Set the Job result to OK, Job type to NONE
       Assign the default operating mode of FLS as per configuration,
       Initialize the OPER status, Check for OPER error
       [/cover] */
    StatePtr = ConfigPtr->FlsStateVarPtr;

    #if(FLS_17_DMU_IFX_FEE_USED == STD_OFF)
    #if( FLS_17_DMU_USE_INTERRUPTS == STD_ON)
    #if(FLS_17_DMU_SAFETY_ENABLE == STD_ON)
    #if  (FLS_17_DMU_CANCEL_API  ==  STD_ON)
    Fls_17_Dmu_JobCancelFlag = FLS_DMU_CANCEL_RESET;
    #endif
    #if (FLS_17_DMU_USE_ERASESUSPEND == STD_ON)
    Fls_17_Dmu_EraseSuspendFlag = FLS_DMU_SUSPEND_RESET;
    #endif
    #endif
    #endif
    #endif
    /*Set JobResult to ok */
    StatePtr->FlsJobResult = MEMIF_JOB_OK;

    /* Setting the Jobtype to none */
    StatePtr->FlsJobType = FLS_17_DMU_NONE;

    StatePtr->NotifCaller = FLS_17_DMU_NO_JOB;

    /* Initialize Job Status */
    StatePtr->JobStarted.Write = 0U;
    StatePtr->JobStarted.Erase = 0U;

    #if (FLS_17_DMU_TIMEOUT_SUPERVISION == STD_ON)
    StatePtr->FlsCmdStartTicks = 0U;
    StatePtr->FlsEraseCmdTimeoutTicks = 0U;
    StatePtr->FlsWriteCmdTimeoutTicks = 0U;
    #endif

    /* Assign default mode */
    StatePtr->FlsMode = Fls_lSetDefaultMode();

    #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_ON)
    StatePtr->FlsEccErrorPageAddress = FLS_ECCERRPAGEADDR_INIT_VAL;
    #endif

    /* Check for OPER */
    OperErrChk = Fls_lChkOperError();

    /* [cover parentID={279000FC-5834-4380-95C2-CF55B77B1218}]
          [/cover] */
    if(OperErrChk != 0U)
    {
      #if(FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
      /*Report runtime error for OPER*/
      /* [cover parentID={8FB4FE0E-760A-4fcc-8309-7660E0D2BCA5}]
      [/cover] */
      (void)Mcal_Wrapper_Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                                          FLS_17_DMU_INSTANCE_ID,
                                          FLS_17_DMU_SID_INIT,
                                          FLS_17_DMU_E_INIT_FAILED);
      #endif
    }
    else
    {
      /*Check if read or write protection is enabled*/
      /* [cover parentID={BDDB77BE-114B-4bd9-8CD0-C2999F93EDF0}]
            [/cover] */
      if(DMU_HF_PROCONDF.U == 0U)
      {
      /* [cover parentID={EF535A4A-1D07-46d6-9728-2EA0599D6F59}]
       [/cover] */
        Fls_17_Dmu_InitStatus = FLS_INITIALIZED;
      }
      else
      {
         Fls_17_Dmu_InitStatus = FLS_UNINITIALIZED;
      }
    }
    /* [cover parentID={53A71103-0C6E-48c6-B3C8-6A48D0158B7A}]
    Return
    [/cover] */
  }
}/* End of Function: Fls_Init */


#if (FLS_17_DMU_INITCHECK_API == STD_ON)
/******************************************************************************
** Traceability   : [cover parentID={FABE1515-678B-4067-9C75-7DBE5B2AB39C}]  **
**                                                                           **
** Syntax         : Std_ReturnType Fls_17_Dmu_InitCheck                      **
**                              (                                            **
**                              const Fls_17_Dmu_ConfigType *const ConfigPtr **
**                              )                                            **
**                                                                           **
** Description    : This function verifies the initialization the FLS driver **
**                  in context to the core from where the API is invoked.    **
**                                                                           **
** [/cover]                                                                  **
**                                                                           **
** Service ID     : 0x2B                                                     **
**                                                                           **
** Sync/Async     : Synchronous                                              **
**                                                                           **
** Reentrancy     : Non Reentrant                                            **
**                                                                           **
** Parameters(in) : None                                                     **
**                                                                           **
** Parameters(out): None                                                     **
**                                                                           **
** Return value   : E_OK - Initialization comparison is success              **
**                  E_NOT_OK - Initialization comparison failed              **
**                                                                           **
******************************************************************************/
Std_ReturnType Fls_17_Dmu_InitCheck(const Fls_17_Dmu_ConfigType
                                    *const ConfigPtr)
/* [cover parentID={EFF2DF9F-5598-4cc5-9E51-91522FA3FE54}]
Fls_17_Dmu_InitCheck
[/cover] */
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint32 MarginCheck, EccEnableCheck, ErrStatusCheck,
         EccStatusCheck, DwaitRegCheck, DwaitCheck, EerStatusCheck,
         PverEverErrChk, ErrorChkStatus, CrankingModeCheck, SensingModeCheck,
         NormalModeCheck,ProtectionCheck;
  uint8 HardenChkComm;

  /* [cover parentID={F3951DFF-FAC3-45fe-A50B-6FE2D6C7C8A3}]
  Is the configuration Pointer valid ?
  [/cover] */
  if(ConfigPtr != NULL_PTR)
  {
    MarginCheck = ((uint32)DMU_HF_MARGIN.U & FLS_DMU_SELD0_MASK_CHK);
    EccEnableCheck = ((uint32)DMU_HF_ECCW.U & FLS_DMU_ECCW_CLR_CHK);
    CrankingModeCheck = ((uint32)DMU_HF_CCONTROL.U & \
                                         FLS_DMU_CRANKING_MODE_CLR_CHK);
    SensingModeCheck = ((uint32)DMU_HF_PROCONUSR.U & \
                                         FLS_DMU_SENSING_MODE_CLR_CHK);
    NormalModeCheck = ((uint32)DMU_HF_PCONTROL.U & \
                                         FLS_DMU_NORMAL_MODE_CHK);
    ProtectionCheck = ((uint32)DMU_HF_PROCONDF.U & FLS_DMU_PROTECTION_CLR_CHK);
    /*MISRA2012_RULE_13_5_JUSTIFICATION: No side effects due to order of
    evaluation of SFR declared volatile */
    /*MISRA2012_RULE_1_3_JUSTIFICATION: No side effects due to order of
     evaluation of SFR declared volatile */
    /*MISRA2012_RULE_13_2_JUSTIFICATION: No side effects due to order of
    evaluation of SFR declared volatile */
    ErrStatusCheck = (((uint32)DMU_HF_ECCS.U & FLS_REG_CLR_CHK) | \
                      ((uint32)DMU_HF_SUSPEND.U & FLS_REG_CLR_CHK));
    DwaitRegCheck = ((uint32)DMU_HF_DWAIT.U & FLS_REG_CLR_CHK);
    DwaitCheck = (((uint32)DMU_HF_DWAIT.U & FLS_DMU_WAITSTATES_MASK) |
                  ConfigPtr->FlsWaitStates);
    EerStatusCheck = ((uint32)DMU_HF_EER.U & FLS_REG_CLR_CHK);
    EccStatusCheck = ((uint32)DMU_HF_ECCC.U & FLS_REG_CLR_CHK);
    /*MISRA2012_RULE_13_5_JUSTIFICATION: No side effects due to order of
    evaluation of SFR declared volatile */
    /*MISRA2012_RULE_1_3_JUSTIFICATION: No side effects due to order of
     evaluation of SFR declared volatile */
    /*MISRA2012_RULE_13_2_JUSTIFICATION: No side effects due to order of
    evaluation of SFR declared volatile */
    HardenChkComm = (((uint8)FSI_COMM_1.U & FLS_REG_COMM_CLRCHK) |  \
                     ((uint8)FSI_COMM_2.U & FLS_REG_COMM_CLRCHK));

    PverEverErrChk = ((uint32)DMU_HF_ERRSR.U & FLS_ERRSRREG_CLRCHK);
    ErrorChkStatus = (ErrStatusCheck | PverEverErrChk | EccEnableCheck |
                      MarginCheck | HardenChkComm | CrankingModeCheck |
                      SensingModeCheck | ProtectionCheck);

    /* [cover parentID={66C77917-9CFA-471b-8B9C-3A18BC7820C9}]
    Is the FLS Config pointer valid AND equal to Root config pointer ?
    [/cover] */
    if((Fls_ConfigPtr != NULL_PTR) && (Fls_ConfigPtr == ConfigPtr))
    {
      RetVal = Fls_lInitCheck();

      /* [cover parentID={DF34E196-F684-4a24-9965-F78A71A73615}]
        Is the configuration  pointer stored in the local config pointer
        and return value of local Init check is  OK?
       [/cover] */
      if(RetVal == E_OK)
      {
        #if( FLS_17_DMU_USE_INTERRUPTS == STD_ON)
        /* [cover parentID={20D36E91-D163-49e3-9FAB-DB2CB89CD207}]
        Is only the EOBM bit in EER register enabled ?
        [/cover] */
        if (FLS_DMU_EER_EOBM_MASK != EerStatusCheck)
        #else
        /* [cover parentID={FDFFE611-0D14-478d-AE88-4290AFE1F897}]
        Is the EER register clear ?
        [/cover] */
        if (0U != EerStatusCheck)
        #endif
        {
          RetVal = E_NOT_OK;
        }
        /* [cover parentID={DCEF55B4-9BA7-430b-9DC5-4F608841A70F}]
        Is the value read from all the registers and variables correctly
        inittialized and the driver status set to initialized?
        [/cover] */
        else if (ErrorChkStatus != 0U)
        {
          /* [cover parentID={01B89F15-BE09-498b-B234-19E591DE9AFA}]
          [/cover] */
          RetVal = E_NOT_OK;
        }
        /* [cover parentID={DCEF55B4-9BA7-430b-9DC5-4F608841A70F}]
         Is the value read from all the registers and variables correctly
         inittialized and the driver status set to initialized?
        [/cover] */
        else if ((DwaitCheck != DwaitRegCheck) ||
                 (FLS_DMU_ECCC_TRAPDIS_MASK != EccStatusCheck))
        {
          /* [cover parentID={01B89F15-BE09-498b-B234-19E591DE9AFA}]
          [/cover] */
          RetVal = E_NOT_OK;
        }
        /* [cover parentID={DCEF55B4-9BA7-430b-9DC5-4F608841A70F}]
        Is the value read from all the registers and variables correctly
        inittialized and the driver status set to initialized?
        [/cover] */
        else if (NormalModeCheck != FLS_DMU_PCONTROL_ESLDIS_MASK)
        {
          /* [cover parentID={01B89F15-BE09-498b-B234-19E591DE9AFA}]
          [/cover] */
          RetVal = E_NOT_OK;
        }
        else
        {
          /* Dummy else */
        }
      }
    }
    else
    {
      /* [cover parentID={01B89F15-BE09-498b-B234-19E591DE9AFA}]
      [/cover] */
      RetVal = E_NOT_OK;
    }
  }
  return(RetVal);
}



/*******************************************************************************
** Traceability   : [cover parentID={3A4253EB-DAF9-423b-A0FD-B1CB1AD5631E}]   **
**                                                                            **
** Syntax         : Std_ReturnType Fls_lInitCheck                             **
**                              (                                             **
**                                void                                        **
**                              )                                             **
**                                                                            **
** Description    : This function verifies the initialization the FLS driver  **
**                  in context to the core from where the API is invoked.     **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : None                                                      **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : E_OK - Initialization comparison is success               **
**                  E_NOT_OK - Initialization comparison failed               **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Fls_lInitCheck(void)
{
  Std_ReturnType ReturnVal;
  const Fls_17_Dmu_StateType  *StatePtr;

  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;

  /* [cover parentID={A20560D7-857F-4791-827A-586F8ECA9E9B}]
  Any Pending Job?
  [/cover] */
  /* [cover parentID={440F8FCE-E61B-4845-99A8-192CAC847171}]
  Is FLS job result set to JOB_OK
  [/cover] */
  if((StatePtr->FlsJobResult != MEMIF_JOB_OK)
      || (StatePtr->FlsJobType != FLS_17_DMU_NONE))
  {
    /* [cover parentID={D1064166-8D05-41f2-92DE-00C42FBBCB7D}]
    [/cover] */
    ReturnVal = E_NOT_OK;
  }
  /* [cover parentID={FA63A99F-EFAE-49f1-93A0-ED2256E75A26}]
  Is Erase Job started status same as the one set in the Fls init ?
  [/cover] */
  /* [cover parentID={37778CE9-5FAC-42e3-B725-024830C0331B}]
  Is the default Mode equal to the FLS Mode?
  [/cover] */
  /* [cover parentID={6EA59D69-C64B-429a-84E7-7B988B538F3B}]
  Is write Job started
  [/cover] */
  else if((StatePtr->JobStarted.Write != 0U)
          || (StatePtr->JobStarted.Erase != 0U)
        || (StatePtr->NotifCaller != FLS_17_DMU_NO_JOB)
          || (Fls_ConfigPtr->FlsDefaultMode != StatePtr->FlsMode) ||
          (Fls_17_Dmu_InitStatus != FLS_INITIALIZED)
       )
  {
    /* [cover parentID={D1064166-8D05-41f2-92DE-00C42FBBCB7D}]
    [/cover] */
    ReturnVal = E_NOT_OK;
  }
  /* [cover parentID={63FF59F0-971D-4bdf-9633-791FA86D7D11}]
   [/cover] */
  /* [cover parentID={C2288BA1-335E-4fad-8239-778A24A58283}]
     [/cover] */
  #if(FLS_17_DMU_IFX_FEE_USED == STD_OFF)
  #if( FLS_17_DMU_USE_INTERRUPTS == STD_ON)
  #if(FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  #if  (FLS_17_DMU_CANCEL_API  ==  STD_ON)
  else if(Fls_17_Dmu_JobCancelFlag != FLS_DMU_CANCEL_RESET)
  {
    ReturnVal = E_NOT_OK;
  }
  #endif
  #if (FLS_17_DMU_USE_ERASESUSPEND == STD_ON)
  else if(Fls_17_Dmu_EraseSuspendFlag != FLS_DMU_SUSPEND_RESET)
  {
    ReturnVal = E_NOT_OK;
  }
  #endif
  #endif
  #endif
  #endif
  /* [cover parentID={79C75DCF-4C7A-45ee-A1F4-EEFF4C9FBCB5}]
  [/cover] */
  #if (FLS_17_DMU_TIMEOUT_SUPERVISION == STD_ON)
  else if((StatePtr->FlsCmdStartTicks != 0U) ||
  (StatePtr->FlsEraseCmdTimeoutTicks != 0U) ||
  (StatePtr->FlsWriteCmdTimeoutTicks != 0U))
  {
    ReturnVal = E_NOT_OK;
  }
  #endif
  /* [cover parentID={E83BA411-CB3E-4a95-B246-B5DEFBA18AF4}]
  [/cover] */
  #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_ON)
  else if(StatePtr->FlsEccErrorPageAddress != FLS_ECCERRPAGEADDR_INIT_VAL)
  {
    ReturnVal = E_NOT_OK;
  }
  #endif
  else
  {
    /* [cover parentID={24A1B99D-801E-431b-9290-CFFCEACE6E59}]
      [/cover] */
    ReturnVal = E_OK;
  }

  return(ReturnVal);

}
/* End of Fls_InitCheck */
/******************************************************************************/
#endif
/* End of #if (FLS_INITCHECK_API == STD_ON) */

/*******************************************************************************
** Traceability :[cover parentID={6959CDE2-07AD-4e69-807A-7C5952D7A7BD}]      **
**                                                                            **
** Syntax : void Fls_17_Dmu_GetVersionInfo(
                                 Std_VersionInfoType * const VersioninfoPtr ) **
**                                                                            **
** Service ID:     0x10                                                       **
**                                                                            **
** Sync/Async:      Synchronous                                               **
**                                                                            **
** Reentrancy:      reentrant                                                 **
**                                                                            **
** Parameters (in): VersioninfoPtr : Pointer to where to store the version    **
**                                   information of this module.              **
**                                                                            **
** Parameters (out):VersioninfoPtr : Pointer to where to store the version    **
**                               information of this module.                  **
** Return value:    none                                                      **
**                                                                            **
** Description :    This service returns the version information of           **
**                  this module.                                              **
**                  The version information includes:                         **
**                  Module Id,Vendor Id , Vendor specific version numbers     **
**                                                                            **
*******************************************************************************/
#if (FLS_17_DMU_VERSION_INFO_API == STD_ON)
/* [cover parentID={D746F9C2-0E84-4b70-B3C7-602D35911049}][/cover] */

/* [cover parentID={BE398CB8-00EC-49f1-B412-B4DA0A38FA75}][/cover] */
void Fls_17_Dmu_GetVersionInfo(Std_VersionInfoType* const VersionInfoPtr)
{ /* [cover parentID={0D6C04B3-0806-4803-B44F-FC92D762B0D9}][/cover] */
  #if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) || \
  (FLS_17_DMU_SAFETY_ENABLE == STD_ON)

  /* [cover parentID={B02230C6-1C60-41e8-944D-21D6C1BF3BBE}]
  Is version information pointer Null? [/cover] */
  if ((VersionInfoPtr) == NULL_PTR)
  {
    /* [cover parentID={E6FFC26B-96BE-4fce-88E1-5FD86A03B53B}]
    Report DET error
    [/cover] */

    Fls_lReportError(
      FLS_17_DMU_SID_GETVERSIONINFO,
      FLS_17_DMU_E_PARAM_POINTER
    );/* Report to  DET */

  }
  else
  #endif
  {
    /* Note that version info pointer is not checked for NULL as the user
     is supposed to send the memory allocated pointer */
    /* FLS Module ID */
    /* [cover parentID={C6691AD5-6557-4533-BF53-2F0D04D79DF2}][/cover] */
    ((Std_VersionInfoType*)(VersionInfoPtr))->moduleID = FLS_17_DMU_MODULE_ID;
    /* FLS vendor ID */
    ((Std_VersionInfoType*)(VersionInfoPtr))->vendorID = FLS_17_DMU_VENDOR_ID;
    /* major version of FLS */
    ((Std_VersionInfoType*)(VersionInfoPtr))->sw_major_version =
      (uint8)FLS_17_DMU_SW_MAJOR_VERSION;
    /* minor version of FLS */
    ((Std_VersionInfoType*)(VersionInfoPtr))->sw_minor_version =
      (uint8)FLS_17_DMU_SW_MINOR_VERSION;
    /* patch version of FLS */
    ((Std_VersionInfoType*)(VersionInfoPtr))->sw_patch_version =
      (uint8)FLS_17_DMU_SW_PATCH_VERSION;
  }
  /* [cover parentID={856AA060-4F1B-4abe-9C42-B33FE3DE01E1}][/cover] */
}
#endif

/*******************************************************************************
** Traceability :[cover parentID={65778937-91C1-4192-98F4-8E9595BAC650}]      **
**                                                                            **
** Syntax : Std_ReturnType Fls_17_Dmu_Erase(                                  **
**                             const Fls_17_Dmu_AddressType TargetAddress,    **
**                             const Fls_17_Dmu_LengthType Length             **
**                                  )                                         **
**                                                                            **
** Service ID: 0x01                                                           **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  TargetAddress - Target address in Flash memory.         **
** This address offset will be added to the flash memory base address         **
**                    Length - Number of bytes to erase                       **
**                                                                            **
** Parameters (out): E_OK: command has been accepted                          **
**                   E_NOT_OK: command has not been accepted                  **
**                                                                            **
** Return value    : Std_ReturnType                                           **
**                                                                            **
** Description : This API Erases Flash. It copies the given parameters to     **
** driver internal variables, initiates the erase job, sets the driver status **
** to MEMIF_BUSY and job result to MEMIF_JOB_PENDING.                         **
*******************************************************************************/
Std_ReturnType Fls_17_Dmu_Erase( const Fls_17_Dmu_AddressType TargetAddress,
                                 const Fls_17_Dmu_LengthType Length)
/*[cover parentID={6C63C328-5CB0-4efe-A474-EB350526D552}][/cover]*/
{
  Fls_17_Dmu_StateType*   StatePtr;
  uint32  PhysicalAddress;
  #if (FLS_17_DMU_TIMEOUT_SUPERVISION == STD_ON)
  uint32 TimeOutResolution;
  #endif
  uint8            JobType;
  Std_ReturnType   ReturnValue;


  /* check for development errors */
  /* [cover parentID={3D29230A-4B5D-4c61-9502-D0C497A89D6E}]
  DET Enabled or SAFETY enabled
  [/cover] */
  #if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) || \
  (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={BBB01167-074A-4d27-99DF-0BC50E528A75}]
  Check for development error
  [/cover] */
  /* [cover parentID={C3FABF96-64B7-4b52-8ECE-333E338D0535}]
   [/cover] */
  if(Fls_lCheckEraseDet(TargetAddress, Length) != E_OK)
  {
    /* [cover parentID={00049BFD-5949-475a-8781-B4DF8F70D60E}]
    Set the Return Value as NOT OK
    [/cover] */
    ReturnValue = E_NOT_OK;
  }

  #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={AB5C643C-1FF9-42c9-9A9C-067A7C8F93B5}]
   Is erase already suspended?
   [/cover] */
  else if(DMU_HF_SUSPEND.B.SPND == 1U)
  {
    /* [cover parentID={39F53B3D-9335-4be1-BBF3-4B5B5F83DF9A}]
         Report Error
    [/cover] */
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_ERASE, FLS_17_DMU_SE_ILLGL_OPERTN);

    /* [cover parentID={00049BFD-5949-475a-8781-B4DF8F70D60E}]
    Set the Return Value as NOT OK
    [/cover] */
    ReturnValue = E_NOT_OK;
  }
  #endif
  else
    /* FLS_DEV_ERROR_DETECT */
  #endif
  {
    /* Check for OPER error */
    /* [cover parentID={7865460E-8936-43de-A6BA-B0B650B791DC}]
    Is operational error detected?
    [/cover] */
    if(Fls_lChkOperError() == 0U)
    {
      /* [cover parentID={3E636493-8F52-42f3-AC35-DCCF57556815}]
      Set the Return Value as OK
      [/cover] */
      ReturnValue = E_OK;

      /* Initialise Local variables */
      StatePtr = Fls_ConfigPtr->FlsStateVarPtr;

      /* [cover parentID={785A057F-E5AC-44e8-9F02-86BA61F4851F}]
      Make a copy of parameters
      Calculate the physical address from TargetAddress
      Set the physical address to be erase
      Calculate the length in terms of number of 4K sectors
      [/cover] */
      /* Calculate the physical address from TargetAddress */
      PhysicalAddress = (uint32) (FLS_17_DMU_BASE_ADDRESS + TargetAddress);
      /* Set the physical address to be erased */
      StatePtr->FlsEraseAddress = PhysicalAddress;

      /* [cover parentID={46B795EB-A7F3-44eb-98B8-19EFE2B4FB91}]
      Is the calculated address 4K aligned  ?
      [/cover] */
      if((Length & FLS_MOD4K_MASK) == 0U)
      {
        /* Calculate the length in terms of number of 4K sectors*/
        /* [cover parentID={B86B3591-795B-4503-925F-19C1080BDD26}]
        [/cover] */
        StatePtr->FlsEraseNumSectors = (uint16) (Length >> FLS_4KSHIFT_VAL);
      }
      else
      {
        /* [cover parentID={8139D453-3976-4135-A87E-54BF9DFF4572}]
        Update the number of 4K sectors to be erased
        [/cover] */
        /* Calculate the length in terms of number of 4K sectors*/
        StatePtr->FlsEraseNumSectors =
          (uint16)((Length >> FLS_4KSHIFT_VAL) + FLS_ONE_VALUE);
      }
      /* Check if number of sectors to be erased can be accommodated in 1 erase
        command cycle; If not seal the number of sectors to be erased to
        recommended value 64 */
      /* [cover parentID={3B345FB4-2CB2-4272-8B67-4D54F6259F88}]
      Check if number of sectors to be erased can be accommodated
      in 1 erase command cycle;
       [/cover] */
      if (StatePtr->FlsEraseNumSectors > FLS_MAXERASE_SEC)
      {
        /* [cover parentID={2B3AA270-750F-4cd0-9AF2-530C9ACAC808}]
        [/cover] */
        StatePtr->FlsEraseNumSecPerCmd = (uint8)FLS_MAXERASE_SEC;
      }
      else
      {
        /* [cover parentID={52985A0C-56CA-4066-90B7-E1E6AD4ADD3C}]
        [/cover] */
        StatePtr->FlsEraseNumSecPerCmd = (uint8)StatePtr->FlsEraseNumSectors;
      }
      /* Check for hardware status */
      /* [cover parentID={C9F5A0A4-A3BB-4b03-A33D-890B0A1D5EB5}]
      Is Data Flash HW Busy?
      [/cover] */
      if(Fls_lHWBusyCheck() == 0U)
      {
        #if(FLS_17_DMU_IFX_FEE_USED == STD_OFF)
        #if(FLS_17_DMU_USE_INTERRUPTS == STD_ON)
        #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
        #if  (FLS_17_DMU_CANCEL_API  ==  STD_ON)
        Fls_17_Dmu_JobCancelFlag = FLS_DMU_CANCEL_RESET;
        #endif
        #endif
        #endif
        #endif
        StatePtr->FlsEver = ((uint8)0x00);
        Fls_lClearStatusCmdCycle();
        #if (FLS_17_DMU_TIMEOUT_SUPERVISION == STD_ON)
        /* Calculate time required for one erase command*/
        TimeOutResolution = Mcal_DelayTickResolution();
        StatePtr->FlsEraseCmdTimeoutTicks = FLS_17_DMU_ERASE_TIME/ \
                                                TimeOutResolution;
        #endif
        /* Execute the ERASE COMMAND CYCLES */
        /* [cover parentID={B4D4B886-2A89-4e47-9FDC-5B2627F92309}]
        Execute Erase Command Cycles
        [/cover] */
        Fls_lCallEraseCommand(StatePtr->FlsEraseAddress);
        /* Check for Sequence error,Protection error  */
        /* [cover parentID={A5E5A351-0321-4aa0-B226-F88C67A3A3D7}]
        Is sequence/protection error detected?
        [/cover] */
        if(Fls_lChkSeqProtErrors() != 0U)
        {
          /* [cover parentID={00049BFD-5949-475a-8781-B4DF8F70D60E}]
          Set the Return Value as NOT OK
          [/cover] */
          ReturnValue = E_NOT_OK;
          /* [cover parentID={5E8AE484-07AC-4af4-AC97-DC24CDC06E7E}]
          Report FLS_17_DMU_E_ERASE_FAILED transient fault
          [/cover] */
          #if(MCAL_AR_VERSION == MCAL_AR_440)
          (void)Det_ReportTransientFault( (uint16)FLS_17_DMU_MODULE_ID,
                                  FLS_17_DMU_INSTANCE_ID,
                                  FLS_17_DMU_SID_ERASE,
                                  FLS_17_DMU_E_ERASE_FAILED);
          #else
            #if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
            /* [cover parentID={9CB1C431-D13A-4394-B485-B935377A22CA}]
            Report runtime Error
            [/cover] */
            (void)Mcal_Wrapper_Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                                  FLS_17_DMU_INSTANCE_ID,
                                  FLS_17_DMU_SID_ERASE,
                                  FLS_17_DMU_E_ERASE_FAILED);
            #endif
          #endif
        }
        /* Check for command sequence Timeout */
        /* [cover parentID={71CA1BA3-109A-46c9-B0B6-AA6D22B3773F}]
        Is there command sequence timeout?
        [/cover] */
        else if (StatePtr->FlsTimeoutErr == FLS_17_DMU_ERASE)
        {
          /* [cover parentID={9CB1C431-D13A-4394-B485-B935377A22CA}]
          Report erase failed error
          [/cover] */
          /* [cover parentID={5E8AE484-07AC-4af4-AC97-DC24CDC06E7E}]
          Report FLS_17_DMU_E_ERASE_FAILED transient fault
          [/cover] */
          #if(MCAL_AR_VERSION == MCAL_AR_440)
          (void)Det_ReportTransientFault( (uint16)FLS_17_DMU_MODULE_ID,
                                  FLS_17_DMU_INSTANCE_ID,
                                  FLS_17_DMU_SID_ERASE,
                                  FLS_17_DMU_E_ERASE_FAILED);
          #else
            #if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
            /* [cover parentID={9CB1C431-D13A-4394-B485-B935377A22CA}]
            Report runtime Error
            [/cover] */
            (void)Mcal_Wrapper_Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                                  FLS_17_DMU_INSTANCE_ID,
                                  FLS_17_DMU_SID_ERASE,
                                  FLS_17_DMU_E_ERASE_FAILED);
            #endif
          #endif
          /* [cover parentID={00049BFD-5949-475a-8781-B4DF8F70D60E}]
          Set the Return Value as NOT OK
          [/cover] */
          ReturnValue = E_NOT_OK;
        }
        else
        {
          /*Set the Job Type*/
          /* [cover parentID={E640D575-9E03-47cc-AF2B-FFAFD266B784}]
          Update the Job Type as FLS_ERASE(erase job)
          [/cover] */
          JobType = FLS_17_DMU_ERASE;
          /* [cover parentID={7A7C7BAD-908D-48c8-9A86-4F9016C6986F}]
          Update driver status to pending by setting the FLS job result to Job
          pending
          [/cover] */
          /* Set the flash job result to job pending */
          StatePtr->FlsJobResult = MEMIF_JOB_PENDING;

          /* Update the new job */
          StatePtr->FlsJobType = JobType;
          /*Job type settings done*/

          /* Indicate that the ERASE Job has been started */
          StatePtr->JobStarted.Erase = 1U;
        }
      }
      else
      {
        #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
        Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_ERASE, FLS_17_DMU_SE_HW_BUSY);
        #endif
        /* [cover parentID={00049BFD-5949-475a-8781-B4DF8F70D60E}]
        Set the Return Value as NOT OK
        [/cover] */
        ReturnValue = E_NOT_OK;
      }
    }
    /* [cover parentID={D44ECCF8-609D-4a21-B167-D9303536A875}]
    [/cover] */
    else
    {
      /* [cover parentID={F3BD876A-909E-41c4-BDEE-D2EBF0735388}]
      Report FLS_17_DMU_E_ERASE_FAILED transient fault
      [/cover] */
      #if(MCAL_AR_VERSION == MCAL_AR_440)
      (void)Det_ReportTransientFault( (uint16)FLS_17_DMU_MODULE_ID,
                              FLS_17_DMU_INSTANCE_ID,
                              FLS_17_DMU_SID_ERASE,
                              FLS_17_DMU_E_ERASE_FAILED);
      #else
        #if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
        /* [cover parentID={9CB1C431-D13A-4394-B485-B935377A22CA}]
        Report runtime Error
        [/cover] */
        (void)Mcal_Wrapper_Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                              FLS_17_DMU_INSTANCE_ID,
                              FLS_17_DMU_SID_ERASE,
                              FLS_17_DMU_E_ERASE_FAILED);
        #endif
      #endif
      /* Job cannot be started because of OPER error */
      ReturnValue = E_NOT_OK;
    }
  }
  /* [cover parentID={CE2708C6-69C0-4bdd-8A7B-B23AB208CEBD}]
  Return
  [/cover] */
  return(ReturnValue);
}

/*******************************************************************************
** Traceability :[cover parentID={32E75AE9-D154-41ac-AC8E-FDA0064F594A}]      **
**                                                                            **
** Syntax : Std_ReturnType Fls_17_Dmu_Write(                                  **
**                           const Fls_AddressType TargetAddress,             **
**                                    const uint8 *const SourceAddressPtr,    **
**                              const Fls_LengthType Length                   **
**                                  )                                         **
**                                                                            **
** Service ID: 0x02                                                           **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :TargetAddress,SourceAddressPtr and Length                 **
**                                                                            **
** Parameters (out): E_OK: command has been accepted                          **
**                   E_NOT_OK: command has not been accepted                  **
**                                                                            **
** Return value    : Std_ReturnType                                           **
**                                                                            **
** Description : Writing to given flash address.                              **
** Service for writing one or more flash pages. This service copies the given **
** parameters to driver internal variables, initiate a Write job, set driver  **
** status to MEMIF_BUSY and job result to MEMIF_JOB_PENDING.                  **
*******************************************************************************/
Std_ReturnType Fls_17_Dmu_Write( const Fls_17_Dmu_AddressType TargetAddress,
                                 const uint8 *const SourceAddressPtr,
                                 const Fls_17_Dmu_LengthType Length
                               )
/* [cover parentID={56425B2B-6F8E-4a81-AAEF-6B0A60CA6988}][/cover] */
{
  Fls_17_Dmu_StateType   *StatePtr;
  uint32 PhysicalAddress;
  #if (FLS_17_DMU_TIMEOUT_SUPERVISION == STD_ON)
  uint32 TimeOutResolution;
  #endif
  uint32          *PageStartAddressPtr;
  Std_ReturnType  RetVal;
  uint8           WriteMode;
  uint8           JobType;

  /* Initialise Local variables */
  RetVal = E_OK;
  /* [cover parentID={92FC4D7A-3D54-43df-91CB-547CF3BD8FD2}]
  Return value is OK
  [/cover] */

  /* [cover parentID={F6619BCF-D161-445b-9702-29D168BFDFA3}]
  DET Enabled
  [/cover] */
  #if  ( FLS_17_DMU_DEV_ERROR_DETECT == STD_ON ) || \
  (FLS_17_DMU_SAFETY_ENABLE == STD_ON)

  /*[cover parentID={F46FD0D2-B0BE-4061-94D2-3E28023E7359}]
  Is development error detected ?
  [/cover] */
  if(Fls_lCheckWriteDet(TargetAddress, SourceAddressPtr,
                        Length) != E_OK)
  {
    /* [cover parentID={81B43DCD-E3FA-4dd1-B543-B9FED6088033}]
    Return value is NOT OK
    [/cover] */
    RetVal = E_NOT_OK;
  }
  /* [cover parentID={ABF80738-88B1-4700-919A-E145959FB823}]
  Check if  the driver is busy
  [/cover] */
  /* [cover parentID={61BF2015-B801-439d-BCF2-DA8A1A87FB49}]
  Is the driver busy?
  [/cover] */
  else if(Fls_lBusyDET_Write(Fls_ConfigPtr->FlsStateVarPtr) == 1U)
  {
    /* [cover parentID={81B43DCD-E3FA-4dd1-B543-B9FED6088033}]
    Return value is NOT OK
    [/cover] */
    RetVal = E_NOT_OK;
  }
  else
  #endif
  {
    StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
    /* PVER check for IFX FEE, clear FlsPver */
    #if(FLS_17_DMU_IFX_FEE_USED == STD_ON)
    StatePtr->FlsPver = 0U;
    #endif
    /* Check OPER error status */
    /* [cover parentID={172C5220-DDAC-4b4e-BB33-76069AFD501A}]
    Is operational error detected?
    [/cover] */
    if(Fls_lChkOperError() == 0U)
    {
      /*Check HW Busy*/
      /* [cover parentID={6EDD3361-0A18-471a-ADA0-1CA87FEA3FB2}]
      Is hardware busy?
      [/cover] */
      if(Fls_lHWBusyCheck() == 0U)
      {
        #if(FLS_17_DMU_IFX_FEE_USED == STD_OFF)
        #if(FLS_17_DMU_USE_INTERRUPTS == STD_ON)
        #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
        #if  (FLS_17_DMU_CANCEL_API  ==  STD_ON)
        Fls_17_Dmu_JobCancelFlag = FLS_DMU_CANCEL_RESET;
        #endif
        #endif
        #endif
        #endif
        /* Determine the page start address */
        /* [cover parentID={A9B96D9C-0240-40c2-9114-77CA94921D22}]
        Update the Fls Write Physical Address to the address where the write has
          to begin
        [/cover] */
        /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from integer to
        pointer type is required to access the FLASH address/target address. No
        memory alignment issues.*/
        /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from uint32 to uint32* type
        is required to access the FLASH address/target address. No memory
        alignment issues. */
        /* MISRA2012_RULE_10_8_JUSTIFICATION: Cast from uint32 to uint32* type
        is required to store the FLASH address/target address. No truncation
        or loss of information is resulted from this cast.*/
        PageStartAddressPtr = (uint32*)(FLS_17_DMU_BASE_ADDRESS  \
                                        + TargetAddress);
        /* Setting the PhysicalAddress to DF0 start address for Command cycle
                 execution */
        PhysicalAddress = FLS_17_DMU_BASE_ADDRESS;
        /*By Default Setting the PageStartAddress to DataBank0 PageAddress */
        /* [cover parentID={71640E10-5599-462f-8BE2-1382951C25BD}]
        Update the write buffer address(source)
        [/cover] */
        /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from pointer to
        uint32 type is required to access the FLASH address/target address
        which is defined as uint32. No memory alignment issues. */
        /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from pointer to uint32
        is required to access the FLASH address/target address which is
        defined as uint32 by AUTOSAR. No memory alignment issues. */
        StatePtr->FlsWriteAddress = (uint32)PageStartAddressPtr;

        /* Assigning Length to global variable FlsWriteLength*/
        StatePtr->FlsWriteLength = Length;

        /* Assigning SourceAddressPtr to Global variable FlsWriteBufferPtr */
        StatePtr->FlsWriteBufferPtr = SourceAddressPtr;
        /*End of StateVar variable setting*/

        /* [cover parentID={165C446B-0AFB-4c49-BF1D-5C91564E5673}]
        FLS_DEV_ERROR_DETECT is enabled
        FLS_17_DMU_IFX_FEE_USED is disabled
        [/cover] */
        #if ( FLS_17_DMU_ERASE_VERIFICATION == STD_ON)
        /* [cover parentID={EC5445C8-F6A1-4fe9-AFEA-9831C0882664}]
        Comparing the contents of the addressed memory area against the value
        of an erased flash cell to check that the block has not been
        completely erased
        [/cover] */
        /* [cover parentID={876A2A15-FF33-46b4-B6AB-F027069B8079}]
        [/cover] */
        if(Fls_lPageEraseCheck
            (PageStartAddressPtr, Length, FLS_17_DMU_SID_WRITE) != E_OK)
        {
          RetVal = E_NOT_OK;
        }
        else
        #endif /* ERASE VERIFICATION */
        {
          /*Obtain the Mode (Page or Burst) */
          WriteMode = Fls_lGetWriteMode();
          /* [cover parentID={898C45F2-EF1A-465f-86A9-B446C0525083}]
          Clear the HW error status registers
          [/cover] */
          Fls_lClearStatusCmdCycle();
          #if (FLS_17_DMU_TIMEOUT_SUPERVISION == STD_ON)
          /* Calculate time required for one burst write */
          TimeOutResolution = Mcal_DelayTickResolution();
          StatePtr->FlsWriteCmdTimeoutTicks = FLS_17_DMU_WRITE_TIME/ \
                                                  TimeOutResolution;
          #endif
          /* [cover parentID={601ECCF4-1583-4fd3-8FF0-627484D546B0}]
          Call write command sequence
          [/cover] */
          /* Execute the Write command sequence */
          Fls_lCallWriteCommand(PhysicalAddress, StatePtr, WriteMode);
          /* [cover parentID={AF5A0B0E-17B4-476d-9038-2E4DCC90BA91}]
          Is production/sequence error detected?
          [/cover] */
          /* Check for Sequence error,Protection error */
          if(Fls_lChkSeqProtErrors() != 0U)
          {
            /* [cover parentID={FD79D307-7859-4d09-A1A3-440A4FA09B81}]
            Report FLS_17_DMU_E_WRITE_FAILED transient fault
            [/cover] */
            #if(MCAL_AR_VERSION == MCAL_AR_440)
            (void)Det_ReportTransientFault( (uint16)FLS_17_DMU_MODULE_ID,
                                    FLS_17_DMU_INSTANCE_ID,
                                    FLS_17_DMU_SID_WRITE,
                                    FLS_17_DMU_E_WRITE_FAILED);
            #else
              /* [cover parentID={9764FBD6-16E6-49b1-924B-AFC37936ECA2}]
              Runtime error detection enabled
              [/cover] */
              #if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
                  /* [cover parentID={E589FD7F-86DA-4aa9-8F8F-FA675DFD6438}]
                  Report runtime error
                  [/cover] */
              (void)Mcal_Wrapper_Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                                    FLS_17_DMU_INSTANCE_ID,
                                    FLS_17_DMU_SID_WRITE,
                                    FLS_17_DMU_E_WRITE_FAILED);
              #endif
            #endif
            /* [cover parentID={81B43DCD-E3FA-4dd1-B543-B9FED6088033}]
            Return value is NOT OK
            [/cover] */
            RetVal = E_NOT_OK;
          }
          /* Check for command cycle Timeout */
          /* [cover parentID={1A5C2B23-1B6A-446e-B706-B39EA4EFA77A}]
          Is timeout error detected?
          [/cover] */
          else if (StatePtr->FlsTimeoutErr == FLS_17_DMU_WRITE)
          {
            /* [cover parentID={FD79D307-7859-4d09-A1A3-440A4FA09B81}]
            Report FLS_17_DMU_E_WRITE_FAILED transient fault
            [/cover] */
            #if(MCAL_AR_VERSION == MCAL_AR_440)
            (void)Det_ReportTransientFault( (uint16)FLS_17_DMU_MODULE_ID,
                                    FLS_17_DMU_INSTANCE_ID,
                                    FLS_17_DMU_SID_WRITE,
                                    FLS_17_DMU_E_WRITE_FAILED);
            #else
              #if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
              /* [cover parentID={E589FD7F-86DA-4aa9-8F8F-FA675DFD6438}]
              Report write failed runtime error
              [/cover] */
              (void)Mcal_Wrapper_Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                                    FLS_17_DMU_INSTANCE_ID,
                                    FLS_17_DMU_SID_WRITE,
                                    FLS_17_DMU_E_WRITE_FAILED);
              #endif
            #endif
            RetVal = E_NOT_OK;
            /* [cover parentID={81B43DCD-E3FA-4dd1-B543-B9FED6088033}]
            Return value is NOT OK
            [/cover] */
          }
          else
          {
            /*Assign jobtype of Data Bank0 to write */
            /* [cover parentID={47820183-3840-4278-99EC-CAD7E0D144E4}]
            Update the state variable with FLS Jobtype with the new job(Write)
            [/cover] */
            /* [cover parentID={0DC68D4D-11BF-4832-8CD4-95849C0FAC74}]
            Update the state variable with FLS Jobtype with the new job(Write)
            [/cover] */
            JobType = FLS_17_DMU_WRITE;
            /* [cover parentID={0DC68D4D-11BF-4832-8CD4-95849C0FAC74}]
            Update job result as job pending
            [/cover] */
            StatePtr->FlsJobResult = MEMIF_JOB_PENDING;
            /* Update the new job  */
            StatePtr->FlsJobType = JobType;
            /* Indicate that the WRITE Job has started */
            StatePtr->JobStarted.Write = 1U;
          }
        }
      }
      else
      {
        #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
        Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                             FLS_17_DMU_SID_WRITE, FLS_17_DMU_SE_HW_BUSY);
        #endif
        /* [cover parentID={81B43DCD-E3FA-4dd1-B543-B9FED6088033}]
         Return value is NOT OK
        [/cover] */
        RetVal = E_NOT_OK;
      }
    }
    else
    {
      #if(MCAL_AR_VERSION == MCAL_AR_440)
      (void)Det_ReportTransientFault( (uint16)FLS_17_DMU_MODULE_ID,
                              FLS_17_DMU_INSTANCE_ID,
                              FLS_17_DMU_SID_WRITE,
                              FLS_17_DMU_E_WRITE_FAILED);
      #else
        #if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
        /* [cover parentID={9CB1C431-D13A-4394-B485-B935377A22CA}]
        Report runtime Error
        [/cover] */
        (void)Mcal_Wrapper_Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                              FLS_17_DMU_INSTANCE_ID,
                              FLS_17_DMU_SID_WRITE,
                              FLS_17_DMU_E_WRITE_FAILED);
        #endif
      #endif
      /* [cover parentID={81B43DCD-E3FA-4dd1-B543-B9FED6088033}]
      Return value is NOT OK
      [/cover] */
      RetVal = E_NOT_OK;
    }
  }
  /* [cover parentID={109B909A-7693-4d33-8FCC-6914CD8A9E33}]
  Return
  [/cover] */
  return(RetVal);
}

#if (FLS_17_DMU_COMPARE_API == STD_ON)
/*******************************************************************************
** Traceability :[cover parentID={09A2E0A1-079D-41b3-B3A2-DBEDA142ABC2}]      **
**                                                                            **
** Syntax : Std_ReturnType Fls_17_Dmu_Compare(                                **
**                                 const Fls_17_Dmu_AddressType SourceAddress,**
**                                      const uint8 *const TargetAddressPtr,  **
**                                     const Fls_17_Dmu_LengthType Length     **
**                                    );                                      **
**                                                                            **
** Service ID:  0x08                                                          **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :SourceAddress -  Source address in Flash memory.          **
** This address offset will be added to the flash memory base address.        **
**                  TargetAddressPtr - Pointer to target data buffer          **
**                  Length - Number of bytes to compare                       **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: command has been accepted                         **
**                    E_NOT_OK: command has not been accepted                 **
**                                                                            **
** Description : Service for comparing the contents of an area of flash memory**
** with that of an application data buffer. This service shall copy the given **
** parameters to driver internal variables, initiate a compare job, set the   **
** driver status to MEMIF_BUSY, set the job result to MEMIF_JOB_PENDING       **
** and return with E_OK.                                                      **
*******************************************************************************/
Std_ReturnType Fls_17_Dmu_Compare( const Fls_17_Dmu_AddressType SourceAddress,
                                   const uint8 *const TargetAddressPtr,
                                   const Fls_17_Dmu_LengthType Length
                                 )
/*[cover parentID={48F60B5E-23BE-42c9-856D-E572D4367401}][/cover]*/
{
  Fls_17_Dmu_StateType   *StatePtr;
  uint32 PhysicalAddress;
  uint8           JobType;
  Std_ReturnType  ReturnValue;
  /* Initialise Local variables */
  /* [cover parentID={32B578EC-FAAA-4a7e-86B6-A16FF31220D9}]
  Set the Return Value as OK
  [/cover] */
  ReturnValue = E_OK;

  /****************************** DET *****************************************/
  /* [cover parentID={141BC9A4-04FB-4dd9-A4EF-D29B75655BAE}]
  DET Enabled
  [/cover] */
  #if( FLS_17_DMU_DEV_ERROR_DETECT == STD_ON ) || \
  (FLS_17_DMU_SAFETY_ENABLE == STD_ON)

  /* [cover parentID={874569B4-586A-4fb7-A0D3-4C7E705ECB34}]
  Is UNINIT Det error detected?
  [/cover] */
  if(Fls_lUninitDET(FLS_17_DMU_SID_COMPARE) == 1U)
  {
    /* [cover parentID={B281440C-ED41-47d8-B4CB-3590176399EC}]
    Set the Return Value as NOT OK
    [/cover] */
    ReturnValue = E_NOT_OK;
  }

  /*
   Checking whether given SourceAddress is valid or not
  */
  /* [cover parentID={F036BFD7-87BC-429e-93BC-5A0CCA67ABFF}]
  Is the given SourceAddress valid ?
  [/cover] */
  else if( SourceAddress >= FLS_17_DMU_TOTAL_SIZE )
  {
    /* [cover parentID={F9010C56-EC3D-4407-87A1-DEC3A216E9DA}]
     Report DET error
     [/cover] */
    Fls_lReportError(
      FLS_17_DMU_SID_COMPARE,
      FLS_17_DMU_E_PARAM_ADDRESS
    );/* Report to DET */

    /* [cover parentID={B281440C-ED41-47d8-B4CB-3590176399EC}]
    Set the Return Value as NOT OK
    [/cover] */
    ReturnValue = E_NOT_OK;
  }

  /*
  Check for Pointer to an application buffer
  */
  /* [cover parentID={5523FD97-7681-47a9-8C5F-7A673E442E2B}]
  Is there any Pointer to an application buffer?
  [/cover] */
  else if(TargetAddressPtr == NULL_PTR)
  {
    /* [cover parentID={F9010C56-EC3D-4407-87A1-DEC3A216E9DA}]
    Report DET error
    [/cover] */
    Fls_lReportError(
      FLS_17_DMU_SID_COMPARE,
      FLS_17_DMU_E_PARAM_DATA
    );/* Report to DET */
    /* [cover parentID={B281440C-ED41-47d8-B4CB-3590176399EC}]
    Set the Return Value as NOT OK
    [/cover] */
    ReturnValue = E_NOT_OK;
  }
  /*
   Checking whether given Length is valid or not
  */
  /* [cover parentID={A57944B9-9512-4a2d-9154-03C2711F57B2}]
  Is the given Length valid ?
  [/cover] */
  else if((Length == 0U) || (Length > (FLS_17_DMU_TOTAL_SIZE - SourceAddress)))
  {
    /* [cover parentID={F9010C56-EC3D-4407-87A1-DEC3A216E9DA}]
    Report DET error
    [/cover] */
    Fls_lReportError(
      FLS_17_DMU_SID_COMPARE,
      FLS_17_DMU_E_PARAM_LENGTH
    );/* Report to DET */
    /* [cover parentID={B281440C-ED41-47d8-B4CB-3590176399EC}]
    Set the Return Value as NOT OK
    [/cover] */
    ReturnValue = E_NOT_OK;
  }
  /* [cover parentID={B58F9527-A75E-427e-9375-0F5EB221B662}]
  Is the Flash driver busy?
  [/cover] */
  else if(Fls_lBusyDET_Compare(Fls_ConfigPtr->FlsStateVarPtr) == 1U)
  {
    /* [cover parentID={B281440C-ED41-47d8-B4CB-3590176399EC}]
    Set the Return Value as NOT OK
    [/cover] */
    ReturnValue = E_NOT_OK;
  }

  /* [cover parentID={8AB01410-36EA-4aa1-BED4-03BFD185EC90}]
  Is the FLS HW IDLE ?
  [/cover] */
  /*Check HW Busy*/
  #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  else if(Fls_lHWBusyCheck() != 0U)
  {
    /* [cover parentID={6DFCC433-E3EE-407c-97A6-18BCB10D4A78}]
    [/cover]*/
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_COMPARE, FLS_17_DMU_SE_HW_BUSY);
    /* [cover parentID={B281440C-ED41-47d8-B4CB-3590176399EC}]
    Set the Return Value as NOT OK
    [/cover] */
    ReturnValue = E_NOT_OK;
  }
  #endif
  else
  #endif /* FLS_DEV_ERROR_DETECT == STD_ON */
    /**************************************************************************/
  {
    /* [cover parentID={73EF1706-206B-48f7-AA72-278D4E1850BB}]
    Update Job type to compare and Job result to job pending
    [/cover] */
    JobType = FLS_17_DMU_COMPARE;

    PhysicalAddress = (uint32)(FLS_17_DMU_BASE_ADDRESS + SourceAddress);
    StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
    /* 1. Set the flash job result to job pending */
    StatePtr->FlsJobResult = MEMIF_JOB_PENDING;

    /* [cover parentID={C70C4FD1-6C10-485d-97FD-B99498390558}]
    Store job parameters : Length/ target address pointer/ source address
    [/cover] */
    /*MISRA2012_RULE_11_8_JUSTIFICATION: Common global buffer is used for
     compare and read operation. Hence casting is done in such a way to match
     the fls read buffer pointer type.
    */
    StatePtr->FlsReadBufferPtr = (uint8 *)TargetAddressPtr;
    /* Assigning Length to Global variable FlsReadLength*/
    StatePtr->FlsReadLength = Length;
    StatePtr->FlsReadAddress = PhysicalAddress;

    /*3. Update the new job on affected banks */
    StatePtr->FlsJobType = JobType;
  }
  /* [cover parentID={8452DB20-BF96-4947-8028-65EF39FD122D}]
  Return
  [/cover] */
  return(ReturnValue);
}
/* FLS_COMPARE_API == STD_ON */
#endif

#if (FLS_17_DMU_BLANK_CHECK_API == STD_ON)
/*******************************************************************************
** Traceability :  [cover parentID={A3F66C87-9D89-4f07-902F-2009EA91E6AB}]    **
**                                                                            **
** Syntax : Std_ReturnType Fls_17_Dmu_BlankCheck(                             **
**                           const Fls_17_Dmu_AddressType TargetAddress       **
**                                const Fls_17_Dmu_LengthType Length          **
**                                    );                                      **
**                                                                            **
** Service ID:  0x0A                                                          **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :TargetAddress - Address in Flash memory from which the    **
**                   blank check should be started.                           **
**                  Length - Number of bytes to be checked for erase pattern  **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: command has been accepted                         **
**                    E_NOT_OK: command has not been accepted                 **
**                                                                            **
** Description : This API is a Service is to verify, whether a given memory   **
** area has been erased but not (yet) programmed.                             **
*******************************************************************************/
Std_ReturnType Fls_17_Dmu_BlankCheck(
  const Fls_17_Dmu_AddressType TargetAddress,
  const Fls_17_Dmu_LengthType Length
)
/* [cover parentID={DF1893ED-5581-422c-A14F-1F4A3E1213C1}][/cover] */
{
  Fls_17_Dmu_StateType   *StatePtr;
  uint32 PhysicalAddress;
  uint8           JobType;
  Std_ReturnType  ReturnValue;

  /* Initialise Local variables */
  /* [cover parentID={7BAA6745-2325-4954-9414-4EE94D08E6DE}]
                Return value is OK
                [/cover] */
  ReturnValue = E_OK;

  /****************************** DET ***************************************/
  /* [cover parentID={890EBA3B-503E-4b1f-B193-8459AA2A92DF}]
  DET Enabled
  [/cover] */
  #if( FLS_17_DMU_DEV_ERROR_DETECT == STD_ON ) || \
  (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={9523B544-B5EA-4de1-B748-D0B82B11B04C}]
  Is Uninit DET error detected?
  [/cover] */
  /* [cover parentID={52A84A6A-F5E2-43ea-A49F-9B1F4BC39F7B}]
  Checking for Uninit DET
  [/cover] */
  if(Fls_lUninitDET(FLS_17_DMU_SID_BLANKCHECK) == 1U)
  {
    /* [cover parentID={C1A4EA1F-207C-452b-8573-FE785F6034F2}]
     Return value is NOT OK
     [/cover] */
    ReturnValue = E_NOT_OK;
  }
  /*[cover parentID={37693A7B-92C4-45bc-8D98-1155CBDAB4A8}]
  Does the start address lie beyond the specified lower and upper flash address
  boundaries?
  [/cover] */
  else if(TargetAddress >= FLS_17_DMU_TOTAL_SIZE)
  {
    /* [cover parentID={7FE697D6-9B33-440a-B417-D94DA4F8D19E}]
    Report DET error
    [/cover] */
    Fls_lReportError(
      FLS_17_DMU_SID_BLANKCHECK,
      FLS_17_DMU_E_PARAM_ADDRESS
    );/* Report to DET */
    /* [cover parentID={C1A4EA1F-207C-452b-8573-FE785F6034F2}]
    Return value is NOT OK
    [/cover] */
    ReturnValue = E_NOT_OK;
  }
  /* [cover parentID={FAF31B75-4A1F-4524-8B30-DFD9DEB5B66D}]
  Is the given length valid?
  [/cover] */
  /*   Checking whether given Length is valid or not  */
  else if(!(( Length >= FLS_ONE_VALUE) &&
            ( Length <= (FLS_17_DMU_TOTAL_SIZE - TargetAddress ))))
  {
    /* [cover parentID={7FE697D6-9B33-440a-B417-D94DA4F8D19E}]
    Report DET error
    [/cover] */
    Fls_lReportError(
      FLS_17_DMU_SID_BLANKCHECK,
      FLS_17_DMU_E_PARAM_LENGTH
    );/* Report to DET */

    /* [cover parentID={C1A4EA1F-207C-452b-8573-FE785F6034F2}]
    Return value is NOT OK
    [/cover] */
    ReturnValue = E_NOT_OK;
  }
  /* [cover parentID={365469BA-536A-4c30-A73F-27F264936494}]
  Is the job type none?
  [/cover] */
  else if (Fls_ConfigPtr->FlsStateVarPtr->FlsJobType != FLS_17_DMU_NONE)
  {
    /* [cover parentID={7FE697D6-9B33-440a-B417-D94DA4F8D19E}]
    Report DET error
    [/cover] */
    Fls_lReportError(
      FLS_17_DMU_SID_BLANKCHECK,
      FLS_17_DMU_E_BUSY);/* Report to DET */
    /* [cover parentID={C1A4EA1F-207C-452b-8573-FE785F6034F2}]
    Return value is NOT OK
    [/cover] */
    ReturnValue = E_NOT_OK;
  }
  #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={52BC18CE-8E84-4d6d-99BE-8A7FB405EB37}]
  Is the HW IDLE ?
  [/cover] */
  else if(Fls_lHWBusyCheck() != 0U)
  {
    /* [cover parentID={B603BBDD-C639-44c4-B13A-E9FB95BDFB31}]
    [/cover] */
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_BLANKCHECK, FLS_17_DMU_SE_HW_BUSY);
    /* [cover parentID={C1A4EA1F-207C-452b-8573-FE785F6034F2}]
    Return value is NOT OK
    [/cover] */
    ReturnValue = E_NOT_OK;
  }
  #endif
  else
  #endif /* FLS_17_DMU_DEV_ERROR_DETECT == STD_ON */
    /*************************************************************************/
  {
    /* [cover parentID={01410584-CA77-4095-A9DC-D0FF7819B8A1}]
                Update job type to blankcheck and job result to pending
                [/cover] */
    JobType = FLS_17_DMU_BLANKCHECK;
    PhysicalAddress = (uint32)(FLS_17_DMU_BASE_ADDRESS + TargetAddress);
    StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
    /* 1. Set the flash job result to job pending */
    StatePtr->FlsJobResult = MEMIF_JOB_PENDING;

    /* Assigning Length to Global variable FlsReadLength*/
    /* [cover parentID={EB07BD14-21A1-4ef9-9615-DD3C11B544D5}]
    Store job parameters : Length/target address pointer/ source address
    [/cover] */
    StatePtr->FlsReadLength = Length;

    StatePtr->FlsReadAddress = PhysicalAddress;

    /*3. Update the new job  */
    StatePtr->FlsJobType = JobType;

  }
  return(ReturnValue);
}
/* FLS_BLANK_CHECK_API == STD_ON */
#endif


#if  (FLS_17_DMU_CANCEL_API  ==  STD_ON)
/*******************************************************************************
** Traceability :  [cover parentID={818E8AB7-EAE0-4743-8C20-7BB75D96CBA5}]    **
**                                                                            **
** Syntax : void Fls_17_Dmu_Cancel(Void)                                      **
**                                                                            **
** Service ID:  0x03                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description :                                                              **
** Service for Canceling an ongoing flash job.                                **
** Read and Compare jobs will be cancelled immediately. Write and Erase jobs  **
** will be cancelled in driver immediately but hardware might still be busy   **
** until the ongoing operation is completed for the already issued commands   **
*******************************************************************************/
void Fls_17_Dmu_Cancel(void)
/*[cover parentID={3F2C37E5-7D99-4666-9665-28F9BF259443}][/cover]*/
{
  Fls_17_Dmu_StateType  *StatePtr;
  uint8 JobType;
  boolean JobCanceled;

  /* [cover parentID={94491FDE-D479-45ae-98A2-07217CF697DE}]
  DET enabled
  [/cover] */
  #if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON ) || \
  (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  /* API called before initialization */
  /* [cover parentID={29F6DEEF-E175-4eca-821A-CAD42FD988CA}]
  Check for Uninit DET error
  [/cover] */
  /* [cover parentID={0A7233D3-B287-4cb8-8657-9D281BAC4F44}]
  Is Uninit error detected?
  [/cover] */
  if (Fls_lUninitDET(FLS_17_DMU_SID_CANCEL) == 0U)
  #endif
  {
    StatePtr = Fls_ConfigPtr->FlsStateVarPtr;

    JobType = StatePtr->FlsJobType;
    JobCanceled = (boolean)FALSE;

    /* [cover parentID={DF5DC956-193E-4090-8660-312B4ED60BDA}]
    Is the  WRITE job scheduled ?
    [/cover] */
    /* Cancel WRITE Job */
    if(FLS_17_DMU_WRITE == JobType)
    {
      #if(FLS_17_DMU_IFX_FEE_USED == STD_OFF)
      #if(FLS_17_DMU_SAFETY_ENABLE == STD_ON)
      #if(FLS_17_DMU_USE_INTERRUPTS == STD_ON)
      Fls_17_Dmu_JobCancelFlag = FLS_DMU_CANCEL_STATE;
      #endif
      #endif
      #endif
      /* Set the JobType to NONE;
         This shall be done before calling Fls_lUnLoadAccessCode() */
      /* [cover parentID={D48C4AF7-3590-42d0-AA06-5D356DEA381F}]
      1) Reset the job status to driver IDLE status.
      2) Reset the job result to canceled.
      3) Reset the write address to TOTAL FLS SIZE.
      4)  Reset the write length to 0.
      5)  Reset the write buffer pointer to NULL.
      [/cover] */
      StatePtr->FlsJobType = FLS_17_DMU_NONE;

      StatePtr->FlsJobResult = MEMIF_JOB_CANCELED;
      JobCanceled = (boolean)TRUE;

      /* Resetting the internal variables */
      StatePtr->FlsWriteAddress = (uint32)FLS_17_DMU_TOTAL_SIZE;
      StatePtr->FlsWriteLength = 0U;
      StatePtr->FlsWriteBufferPtr = NULL_PTR;
    }

    /* [cover parentID={E0F0EC51-199F-4d4a-9E86-460C63DBE8F4}]
    Is the ERASE job scheduled ?
    [/cover] */
    /* Cancel ERASE Job */
    else if(FLS_17_DMU_ERASE == JobType)
    {
      #if(FLS_17_DMU_IFX_FEE_USED == STD_OFF)
      #if(FLS_17_DMU_SAFETY_ENABLE == STD_ON)
      #if(FLS_17_DMU_USE_INTERRUPTS == STD_ON)
      Fls_17_Dmu_JobCancelFlag = FLS_DMU_CANCEL_STATE;
      #endif
      #endif
      #endif

      /* Set the JobType to NONE*/
      /*[cover parentID={8DD2D23A-49E2-4f6c-A46A-CB99D0DE1F33}]
      Reset the Job Type to None.
      Set the Job result to CANCELED.
      Set Job Cancelled to TRUE
      [/cover] */
      StatePtr->FlsJobType = FLS_17_DMU_NONE;

      StatePtr->FlsJobResult = MEMIF_JOB_CANCELED;
      JobCanceled = (boolean)TRUE;

      /* Resetting the internal variables */
      StatePtr->FlsEraseAddress = (uint32)FLS_17_DMU_TOTAL_SIZE;
      StatePtr->FlsEraseNumSectors = 0U;
      StatePtr->FlsEraseNumSecPerCmd = 0U;
    }
    /* [cover parentID={2CE6DBB5-D10D-4ebb-8565-1AA0CFCBB093}]
    Is the READ or COMPARE job scheduled ?
    [/cover] */
    else if((FLS_17_DMU_READ == JobType) || (FLS_17_DMU_COMPARE == JobType))
    {
      /* Cancel READ / COMPARE Job */
      /* Set the JobType to NONE */
      /* [cover parentID={EFEF65CE-1521-4025-AD99-335699C63C27}]
      1) Reset the job to NONE
      2) Reset the job result to CANCELED.
      3) Reset the read buffer to NULL.
      4) Reset the read length to ZERO.
      5) Reset  read address to invalid.
      [/cover] */
      StatePtr->FlsJobType = FLS_17_DMU_NONE;

      StatePtr->FlsJobResult = MEMIF_JOB_CANCELED;
      JobCanceled = (boolean)TRUE;

      /*Reset internal variables after cancellation*/
      StatePtr->FlsReadBufferPtr = NULL_PTR;
      StatePtr->FlsReadLength = 0U;
      StatePtr->FlsReadAddress = (uint32)FLS_17_DMU_TOTAL_SIZE;
    }

    /* [cover parentID={CE931036-99B6-42c2-8E73-2627A09786AB}]
    Is BLANCHECK job scheduled ?
    [/cover] */
    else if(FLS_17_DMU_BLANKCHECK == JobType)
    {
      /* Set the JobType to NONE; */
      /* [cover parentID={4B2CDCA7-3527-4d13-98ED-8275076F9644}]
      Reset the Job Type to None.
      Set the Job result to CANCELED.
      Set Job Canceled to TRUE
       [/cover] */
      StatePtr->FlsJobType = FLS_17_DMU_NONE;

      StatePtr->FlsJobResult = MEMIF_JOB_CANCELED;
      JobCanceled = (boolean)TRUE;

      /*Reset internal variables after cancellation*/
      StatePtr->FlsReadBufferPtr = NULL_PTR;
      StatePtr->FlsReadLength = 0U;
      StatePtr->FlsReadAddress = (uint32)FLS_17_DMU_TOTAL_SIZE;
    }
    else
    {
      /* Set the JobType to NONE */
      /* [cover parentID={E82ABB8D-5F51-475c-8E55-3E42FCEC986D}]
       Make Jobtype as NONE
      [/cover] */
      StatePtr->FlsJobType = FLS_17_DMU_NONE;
    }

    /* [cover parentID={86E9AD85-FE3A-4534-B8DD-423DB0620E33}]
    1. Rest the write and erase started status to not started.
    [/cover] */
    /* Reset JobStartStatus */
    StatePtr->JobStarted.Write = 0U;
    StatePtr->JobStarted.Erase = 0U;

    /* [cover parentID={FE31305C-9609-4d78-97FA-3F86AF49B6D6}]
    Is job canceled and Fee job error notification configured ?
    [/cover] */
    if((JobCanceled == (boolean)TRUE) &&
        (Fls_ConfigPtr->FlsJobErrorNotificationPtr != NULL_PTR)
      )
    {
      /* [cover parentID={9DDC4A9D-123A-4ac7-8539-ECE5F8B1F2AB}]
       Notification flag for FEE is set to Cancel Job
      [/cover] */
      StatePtr->NotifCaller = FLS_17_DMU_CANCEL_JOB;
      /* [cover parentID={F3DF12FB-EC06-455a-B0A2-2DAAAE766369}]
      Call Fee Error Notification
      [/cover] */
      /* FlsJobErrorNotificationPtr should be called */
      (Fls_ConfigPtr->FlsJobErrorNotificationPtr)();
      /* [cover parentID={0265A23C-D907-426e-A17E-358B707B470E}]
      Set the FEE notification flag to No Job
      [/cover] */
      StatePtr->NotifCaller = FLS_17_DMU_NO_JOB;
    }

  }

}

#endif /* #if (FLS_CANCEL_API == STD_ON) */

#if(FLS_17_DMU_IFX_FEE_USED == STD_ON)
/*******************************************************************************
** Traceability : [cover parentID={2286DD54-0A69-45e6-ADFD-CC09F66B2688}]     **
**                                                                            **
** Syntax : void Fls_17_Dmu_CancelNonEraseJobs(void)                          **
**                                                                            **
** Service ID: 0x28                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description :                                                              **
** Service for Canceling an ongoing flash jobs except the erase job.          **
** Read and Compare jobs will be cancelled immediately. Write job             **
** will be cancelled in driver immediately but hardware might still be busy   **
** until the ongoing operation is completed for the already issued commands   **
*******************************************************************************/
void Fls_17_Dmu_CancelNonEraseJobs(void)
/*[cover parentID={2EFCDB48-187B-4d13-A230-B0C7BE5BFAEA}][/cover]*/
{
  Fls_17_Dmu_StateType  *StatePtr;
  uint8 JobType;
  boolean JobCanceled;

  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
  JobType = StatePtr->FlsJobType;
  JobCanceled = (boolean)FALSE;


  /* Cancel WRITE Job */
  /* [cover parentID={FCC0F9DA-5263-46df-9488-5892DE57EB42}]
  Is the WRITE job ongoing ?
  [/cover] */
  if(FLS_17_DMU_WRITE == JobType)
  {
    /* [cover parentID={302F4467-5E2A-42db-8C9E-981AEB4BD72C}]
    Set the Job Type to FLS_NONE.
    [/cover] */
    StatePtr->FlsJobType = FLS_17_DMU_NONE;

    /*
    Set the result of job as cancelled if it was marked as pending
    */
    StatePtr->FlsJobResult = MEMIF_JOB_CANCELED;

    JobCanceled = (boolean)TRUE;

    /* Reset JobStart Status */
    StatePtr->JobStarted.Write = 0U;

  }
  /* Cancel READ / COMPARE / BlankCheck Job */
  /* [cover parentID={D851CF64-788A-4ef2-9682-0A4B3D549105}]
  Is READ/COMPARE/BLANKCHECK ongoing ?
  [/cover] */
  else if((FLS_17_DMU_READ == JobType) || (FLS_17_DMU_COMPARE == JobType) || \
          (FLS_17_DMU_BLANKCHECK == JobType))
  {
    /* [cover parentID={1A9B312D-8DEB-4a5d-A2E5-8D10CF13FF6D}]
    1. Set the result of job as cancelled if it was marked as pending.
    2. Cancel the ongoing job by making jobtype as none.
    3. Set Job Cancel flag to True.
    [/cover] */
    StatePtr->FlsJobType = FLS_17_DMU_NONE;

    StatePtr->FlsJobResult = MEMIF_JOB_CANCELED;

    JobCanceled = (boolean)TRUE;
  }

  /* [cover parentID={F3112721-8540-47e1-A8D0-478427EE4389}]
  Is ERASE Job ongoing ?
  [/cover] */
  else
  {
    /* Reset JobType of Non-Erase Job */
    /* [cover parentID={7A29178D-275C-4db0-B4FA-0E06AD582A3D}]
    [/cover] */
    StatePtr->FlsJobType = ((JobType == FLS_17_DMU_ERASE) ?
                            FLS_17_DMU_ERASE : FLS_17_DMU_NONE);

  }

  /* Set the NotifCaller to Cancel Job */
  /* [cover parentID={E392F39B-4481-48a7-BB3F-0EBBC78AA941}]
  Is the notification configured and Job Cancelled Flag is set to True?
  [/cover] */
  if((JobCanceled == (boolean)TRUE) &&
      (Fls_ConfigPtr->FlsJobErrorNotificationPtr != NULL_PTR)
    )
  {
    /* [cover parentID={44BCC7FD-9B85-4b8b-A8C1-6586C4BF8476}]
    Set the Notification flag to CANCEL_JOB
    [/cover] */
    Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_CANCEL_JOB;
    /* FlsJobErrorNotificationPtr should be called */
    /* [cover parentID={D448B972-5866-4b69-B9B7-57AAD957B0F4}]
    Call FlsJobErrorNotificationPtr
    [/cover] */
    (Fls_ConfigPtr->FlsJobErrorNotificationPtr)();
    /* [cover parentID={92FB03DC-A95C-4cec-BBD8-3009629BF38D}]
    Set the notification pointer to FLS_NO_JOB
    [/cover] */
    Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_NO_JOB;
  }

}
#endif

/*******************************************************************************
** Traceability : [cover parentID={CB676030-CE4D-4b2d-B0FB-14DB3947C53D}]     **
**                                                                            **
** Syntax : void Fls_17_Dmu_SetMode(const MemIf_ModeType Mode)                **
**                                                                            **
** Service ID:  0x09                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : Mode MEMIF_MODE_SLOW:                                    **
**                        Slow read access                                    **
**                                                                            **
**                        MEMIF_MODE_FAST:                                    **
**                        Fast read access                                    **
**                                                                            **
** Parameters (out): : None                                                   **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This API sets the Flash driver's operation mode.             **
**               FAST or SLOW mode impacts only Read/Compare operations.      **
**               Based on the currently active mode, the number of bytes to be**
**               read from Flash in each call of Fls_17_Dmu_MainFunction is   **
**               taken from the configuration                                 **
*******************************************************************************/
#if  (FLS_17_DMU_SET_MODE_API  ==  STD_ON)
/* [cover parentID={887E1F26-1DC2-4b3d-967A-49E35D53B742}][/cover] */
void Fls_17_Dmu_SetMode(const MemIf_ModeType Mode)
{
  /* [cover parentID={750FE6BF-FE76-4ad6-AE35-13ABFF0A450E}]
  DET Enabled
  [/cover] */
  #if  ( FLS_17_DMU_DEV_ERROR_DETECT == STD_ON ) || \
  (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  uint8 JobType;
  /* [cover parentID={DA2E0867-34EC-4300-9774-BC6DFF1C45D9}]
   Is the driver initialised?
   [/cover] */
  if (Fls_lUninitDET(FLS_17_DMU_SID_SETMODE) == 0U)
  {
    JobType = Fls_ConfigPtr->FlsStateVarPtr->FlsJobType;
    /* Check if the driver is BUSY */
    /* [cover parentID={6CAF01FF-2D18-4e15-8852-65E33436C658}]
    Is the driver busy?
    [/cover] */
    if( JobType != FLS_17_DMU_NONE )
    {
      /* [cover parentID={01F518B7-444B-4946-8602-F01AA7A4489C}]
      Report DET error
      [/cover] */

      Fls_lReportError(FLS_17_DMU_SID_SETMODE,
                       FLS_17_DMU_E_BUSY);/* Report to DET */
    }
    #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
    /* [cover parentID={1A8AFA18-F677-49b2-9C24-5A8196A0EF42}]
    Value of Mode is valid ?
    [/cover] */
    else if ((MEMIF_MODE_SLOW != Mode) && (MEMIF_MODE_FAST != Mode))
    {
      /* [cover parentID={97BDC29C-6774-4d78-8827-93504FA03E41}]
      Value of Mode is valid ?
      [/cover] */
      Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                             FLS_17_DMU_SID_SETMODE,
                             FLS_17_DMU_SE_PARAM_INVLD);
    }
    #endif
    else
  #endif
    { /* [cover parentID={C93A086D-8E9B-43d1-B373-57F389935F09}]
      Set flash driver's operation mode
      [/cover] */
      Fls_ConfigPtr->FlsStateVarPtr->FlsMode = Mode;
    }
    /* [cover parentID={A019C01B-F6EC-4a90-A07E-5970D6A6BA4C}][/cover] */
    #if  ( FLS_17_DMU_DEV_ERROR_DETECT == STD_ON ) || \
    (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  }
    #endif
}
#endif


/*******************************************************************************
** Traceability : [cover parentID={18730333-536B-494d-8FB0-10F16F44A4A0}]     **
**                                                                            **
** Syntax : void Fls_17_Dmu_MainFunction(void)                                **
**                                                                            **
** Service ID:  0x06                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out): : None                                                   **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description :                                                              **
** This service shall perform the processing of the flash read,write          **
**         and erase jobs                                                     **
*******************************************************************************/
/* CYCLOMATIC_Fls_17_Dmu_MainFunction_JUSTIFICATION: This Function has
 cyclomatic complexity greater than 15, as the OPER error check mandated by
 the hardware manual. This cannot be further broken down into local function.*/
void Fls_17_Dmu_MainFunction(void)
/* [cover parentID={D100ACCD-70B7-4226-B004-79439A1FC37F}]
Fls_17_Dmu_MainFunction [/cover] */
/* [cover parentID={BF6D9ACD-AC47-4231-A2B6-917D4FF7432D}][/cover] */
{
  const Fls_17_Dmu_StateType  *StatePtr;
  uint8 JobType;
  uint8 ErrorUninitFlag = 0U;
  uint32 OperStatusChk;
  /* [cover parentID={68813369-F249-48f9-B216-C4313DCB2E4F}]
  DET Enabled
  [/cover] */
  #if  ( FLS_17_DMU_DEV_ERROR_DETECT == STD_ON ) || \
  (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  /* API  called before initialization */
  /* [cover parentID={D6F6BADF-FCFB-4bb4-9E0F-8ACDB6E61E41}]
  Is Uninit DET error detected or Config pointer Null?
  [/cover] */
  /* [cover parentID={7B21429D-9466-458d-9427-024A5BAAA05E}]
  Check for Uninit DET error and set error flag if found
  [/cover] */
  ErrorUninitFlag = Fls_lUninitDET(FLS_17_DMU_SID_MAIN);
  #else
  /* [cover parentID={7D145E42-85F2-453c-B735-FE52377F8FA3}]
  Is Config pointer valid and Fls Init done ?
  [/cover] */
  if((Fls_ConfigPtr == NULL_PTR) ||
      (FLS_INITIALIZED != Fls_17_Dmu_InitStatus))
  {
    /* [cover parentID={DDDE3EA7-DC9F-4eb8-BED7-96844ABF14E8}]
    [/cover] */
    ErrorUninitFlag = 1;
  }
  #endif
  /* [cover parentID={0A086CC7-5F84-4e6d-93EF-CAC0942190D8}]
  Is the error flag set ?
  [/cover] */
  /* [cover parentID={B6F16F30-2B1D-4b3f-B72C-EDA57875D761}]
  Is error flag set?
  [/cover] */
  if (ErrorUninitFlag == 0U)
  {
    StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
    JobType = StatePtr->FlsJobType;
    /* [cover parentID={12FC3586-8656-4ca3-A2B3-449B7762EF77}]
    Is there an ongoing job?
    [/cover] */
    if( JobType != FLS_17_DMU_NONE)
    {
      OperStatusChk = ((uint32)DMU_HF_ERRSR.U & FLS_OPER_ERROR);
      /* Check for any Flash operation is ongoing? */
      /* [cover parentID={9487CF90-FF87-4172-8101-EAC857722077}]
      Is harwdare idle?
      [/cover] */
      if(( Fls_lHWBusyCheck() == 0U) || (OperStatusChk != 0U))
      {
        /* [cover parentID={0FA15697-671E-43a0-AAA1-1899866E810E}]
        Get the type of the pending job
        [/cover] */
        switch(JobType)
        {
          /**************************** ERASE *******************************/
          case FLS_17_DMU_ERASE:
          {
            /* Fls_Main_Erase operation should be called  */
            /*OPER is checked to prevent driver being stuck in busy state
            because of OPER error in interrupt mode*/
            /* [cover parentID={0DDBB492-71EF-4c16-8E59-AE12CCF803C2}]
            Is OPER set?
            [/cover] */
            #if(FLS_17_DMU_USE_INTERRUPTS == STD_ON)
            if(OperStatusChk != 0U)
            #endif
            {
              /* [cover parentID={0366A308-A442-4d97-95CA-70DE34BBC2D2}]
              Call Local Main Erase Function
              [/cover] */
              Fls_lMainErase();
            }
          }
          break;
          /***************************** WRITE ******************************/
          case FLS_17_DMU_WRITE:
          {
            /* Fls_Main_Write operation should be called  */
            /*OPER is checked to prevent driver being stuck in busy state
            because of OPER error in interrupt mode*/
            /* [cover parentID={EC5806CB-46DD-43d9-A0FE-B6F5C20050DB}]
            Call Local Main Write Function
            [/cover] */
            #if(FLS_17_DMU_USE_INTERRUPTS == STD_ON)
            if(OperStatusChk != 0U)
            #endif
            {
              /* [cover parentID={8B248420-DCFE-47fa-B4AB-919D14056F7B}]
              Call Local Main Write Function
              [/cover] */
              Fls_lMainWrite();
            }
          }
          break;
          /*************************** READ *********************************/
          case FLS_17_DMU_READ:
          {
            /* Fls_Main_Read operation should be called  */
            /* [cover parentID={2C284258-AFB5-422a-9652-A64A65D4217D}]
            Call Local Main Read Function
            [/cover] */
            Fls_lMainRead();
          }
          break;
          /*************************** COMPARE ******************************/
          case FLS_17_DMU_COMPARE:
          {
            /* Fls_Main_Compare operation should be called  */
            /* [cover parentID={533B372F-9552-4912-B8EB-6B4F880AD80D}]
            Call Local Main Comapre Function
            [/cover] */
            Fls_lMainCompare();
          }
          break;
          /***************************** BLANK CHECK ************************/
          case FLS_17_DMU_BLANKCHECK:
          {
            /* Fls_Main_BlankCheck operation should be called  */
            /* [cover parentID={218A069E-51B9-441e-A2EE-6A32EDDBE2E2}]
            Call Local Main Blank Check Function
              [/cover] */
            Fls_lMainBlankCheck();
          }
          break;
          default:
          {
            /* Do nothing - To avoid MISRA warning */
          }
          break;
        }
      }
      #if (FLS_17_DMU_TIMEOUT_SUPERVISION == STD_ON)
      else
      {
        /* [cover parentID={2AB8D16D-C1D1-4da7-8F50-942FC3C04B64}]
        Check for job timeout
        [/cover] */
        Fls_lTimeOutMonitoring(FLS_17_DMU_SID_MAIN);
      }
      #endif
    }
  }
  /* [cover parentID={DE6A282F-9FFE-43a0-A515-0A3EF92B213E}][/cover] */
}



/*******************************************************************************
** Traceability : [cover parentID={2A9A31FE-C2D1-47ca-9A22-3F281024F0A2}]     **
**                                                                            **
** Syntax : Std_ReturnType Fls_17_Dmu_Read(
**                              const Fls_17_Dmu_AddressType SourceAddress,   **
**                                   uint8 *const TargetAddressPtr,           **
**                              const Fls_17_Dmu_LengthType Length            **
**                                 );                                         **
**                                                                            **
** Service ID:  0x07                                                          **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : SourceAddress,TargetAddressPtr and Length                **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: command has been accepted                         **
**                    E_NOT_OK: command has not been accepted                 **
**                                                                            **
** Description : Service for reading from flash memory. This service copies   **
** the given parameters to driver internal variables, set driver status to    **
** MEMIF_BUSY and job result to MEMIF_JOB_PENDING.                            **
*******************************************************************************/
Std_ReturnType Fls_17_Dmu_Read(const Fls_17_Dmu_AddressType SourceAddress,
                               uint8 *const TargetAddressPtr,
                               const Fls_17_Dmu_LengthType Length)
/* [cover parentID={F945E4D5-BEB5-4055-B6F7-33D2A6F0B2A4}][/cover] */
{
  Fls_17_Dmu_StateType  *StatePtr;
  uint32 PhysicalAddress;
  Std_ReturnType ReturnValue;
  uint8 JobType;

  /* Initialise Local variables */
  /* [cover parentID={6E4AF82B-7708-4645-8CA5-FE72D28D3474}]
  Set the Return Value as OK
  [/cover] */
  ReturnValue = (Std_ReturnType)E_OK;

  /**************************** DET ******************************************/

  /* [cover parentID={9FDC9E89-EF19-47c1-B186-5BC98FC13F5B}]
  DET Enabled
  [/cover] */
  #if  ( FLS_17_DMU_DEV_ERROR_DETECT == STD_ON ) || \
  (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  /*  API  called before initialization */
  /* [cover parentID={EF160363-0D89-4fb2-8950-26584F81C13A}]
  Is Uninit Det error detected?
  [/cover] */
  if(Fls_lUninitDET(FLS_17_DMU_SID_READ) == 1U)
  {
    /* [cover parentID={1281120B-29EA-4864-8DC0-A4CDAF6C217E}]
    Set the Return Value as NOT OK
    [/cover] */

    ReturnValue = E_NOT_OK;
  }
  /*  Checking whether given SourceAddress is valid or not */
  /* [cover parentID={D0FB4705-8153-40cd-A224-9DEDFAF46501}]
  Is the given Source Address valid?
  [/cover] */
  else if(SourceAddress >= (FLS_17_DMU_TOTAL_SIZE))
  {
    /* [cover parentID={DEF6F07D-0960-4930-9AD3-EA6589D169BA}]
    Report DET error
    [/cover] */

    Fls_lReportError(FLS_17_DMU_SID_READ,
                     FLS_17_DMU_E_PARAM_ADDRESS);/* Report to DET*/

    ReturnValue = E_NOT_OK;
    /* [cover parentID={1281120B-29EA-4864-8DC0-A4CDAF6C217E}]
    Set the Return Value as NOT OK
    [/cover] */

  }
  /*Check for Pointer to an application buffer*/
  /* [cover parentID={671138DB-C22D-4e38-8F87-676B02CA6475}]
  Is there a Pointer to an application buffer?
  [/cover] */
  else if(TargetAddressPtr == NULL_PTR)
  {
    /* [cover parentID={DEF6F07D-0960-4930-9AD3-EA6589D169BA}]
    Report DET error
    [/cover] */
    Fls_lReportError(FLS_17_DMU_SID_READ,
                     FLS_17_DMU_E_PARAM_DATA);/* Report to DET */
    /* [cover parentID={1281120B-29EA-4864-8DC0-A4CDAF6C217E}]
     Set the Return Value as NOT OK
    [/cover] */
    ReturnValue = E_NOT_OK;
  }
  /* Checking whether given Length is valid or not */
  /* [cover parentID={4CCB86DF-F9A8-4690-9AC6-EA988D47BC05}]
  Is the given Length valid?
  [/cover] */
  else if((Length < FLS_ONE_VALUE) ||
          (Length > (FLS_17_DMU_TOTAL_SIZE - SourceAddress)))
  {
    /* [cover parentID={DEF6F07D-0960-4930-9AD3-EA6589D169BA}]
     Report DET error
     [/cover] */
    Fls_lReportError(FLS_17_DMU_SID_READ,
                     FLS_17_DMU_E_PARAM_LENGTH);/* Report to DET */
    /* [cover parentID={1281120B-29EA-4864-8DC0-A4CDAF6C217E}]
    Set the Return Value as NOT OK
    [/cover] */
    ReturnValue = E_NOT_OK;

  }

  /* [cover parentID={8DE1B39A-A277-4108-98C2-BCF4BC933AFB}]
  If the new Read job can be accepted? ( busy check)
  [/cover] */
  else if(Fls_lBusyDET_Read(Fls_ConfigPtr->FlsStateVarPtr) == 1U)
  {
    /* [cover parentID={1281120B-29EA-4864-8DC0-A4CDAF6C217E}]
    Set the Return Value as NOT OK
    [/cover] */
    ReturnValue = E_NOT_OK;
  }
  else
  #endif
    /*************************************************************************/
  {
    /* [cover parentID={D92E9E44-C57F-411b-946F-5FEDD9352AB4}]
    Is HW busy ?
    [/cover] */
    if(Fls_lHWBusyCheck() == 0U)
    {
      /*Assign jobtype to read */
      /* [cover parentID={735FD7FA-90EA-45ab-B927-643A6BC0CC6D}]
      Update the physical address to the base address plus the given source
      address. Update job result to pending/ Store job parameters/ Update the
      job type to Read
      [/cover] */
      JobType = FLS_17_DMU_READ;
      PhysicalAddress = (uint32)(FLS_17_DMU_BASE_ADDRESS + SourceAddress);
      StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
      /* 2. Set the flash job result to job pending */
      StatePtr->FlsJobResult = MEMIF_JOB_PENDING;

      /* Assigning TargetAddressPtr to Global variable FlsReadBufferPtr */
      StatePtr->FlsReadBufferPtr = TargetAddressPtr;
      /* [cover parentID={E0319812-0D46-4ee8-A535-A8E760315388}]
      Assigning TargetAddressPtr to Global variable Read Buffer Pointer
      Assigning Length to Global variable FlsReadLength
      [/cover] */

      /* Assigning Length to Global variable FlsReadLength*/
      StatePtr->FlsReadLength = Length;

      StatePtr->FlsReadAddress = PhysicalAddress;

      /*3. Update the new job on affected banks */
      StatePtr->FlsJobType = JobType;
    }
    else
    {
      /* [cover parentID={D70FB0F7-8375-480b-9755-113CE3E22BA6}]
      [/cover] */
      #if(FLS_17_DMU_SAFETY_ENABLE == STD_ON)
      Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                             FLS_17_DMU_SID_READ, FLS_17_DMU_SE_HW_BUSY);
      #endif
      /* [cover parentID={1281120B-29EA-4864-8DC0-A4CDAF6C217E}]
      Set the Return Value as NOT OK
      [/cover] */
      ReturnValue = E_NOT_OK; /*HW is busy*/
    }
  }
  /* [cover parentID={F93086E6-451A-482b-BEDE-9F1E1DDA6E73}]
  Return
  [/cover] */
  return(ReturnValue);
}

#if (FLS_17_DMU_GET_STATUS_API == STD_ON)
/*******************************************************************************
** Traceability : [cover parentID={5C6365D7-79D7-459f-BEB7-A89C359F9399}]     **
**                                                                            **
** Syntax : MemIf_StatusType Fls_17_Dmu_GetStatus(void)                       **
**                                                                            **
** Service ID:  0x04                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Re-entrant                                                    **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out): : None                                                   **
**                                                                            **
** Return value    :  MemIf_StatusType - The state of the driver              **
**                                                                            **
** Description :                                                              **
** This service shall return the driver state synchronously                   **
*******************************************************************************/
MemIf_StatusType Fls_17_Dmu_GetStatus(void)
/*[cover parentID={59FF2D8F-716D-43e2-B59E-7D3D1A27A5DA}][/cover]*/
{
  MemIf_StatusType ReturnValue;
  uint8 JobType;

  /* [cover parentID={B08669D6-885F-42d8-806C-2ECED4ED1F9A}]
     Is the driver initialised?
     [/cover] */
  /* [cover parentID={D7C68622-1B4E-499f-8CEF-919839012A86}]
  Is the Config Pointer NULL PTR?
  [/cover] */
  if((Fls_ConfigPtr == NULL_PTR) || (FLS_INITIALIZED != Fls_17_Dmu_InitStatus))
  {
    /* [cover parentID={FEF1E417-BE22-440b-87E3-C2FD830ABA70}]
    Return - Driver is not initialized
    MEMIF_UNINIT
    [/cover] */
    ReturnValue = MEMIF_UNINIT;
  }
  else
  {
    JobType = Fls_ConfigPtr->FlsStateVarPtr->FlsJobType;
    /* [cover parentID={99B95143-5330-4aa8-9128-E72015131532}]
    Is there any ongoing job?
    [/cover] */
    if((JobType != FLS_17_DMU_NONE))
    {
      /* [cover parentID={8C1B9220-1A20-49c0-A932-74F4A21C8D59}]
      Return flash status as busy
      MEMIF_BUSY
      [/cover] */
      ReturnValue = MEMIF_BUSY;
    }
    else
    {
      /* [cover parentID={CB7B8DE8-3A82-4564-A0F4-C0BC212E4F6A}]
      Return flash status as idle
      MEMIF_IDLE
      [/cover] */
      ReturnValue = MEMIF_IDLE;
    }
  }
  /*  Service shall return driver state synchronously. */
  return(ReturnValue);
} /* End of Function: Fls_GetStatus */


#endif

#if  (FLS_17_DMU_GET_JOB_RESULT_API  ==  STD_ON)
/*******************************************************************************
** Traceability : [cover parentID={FBF001A4-D07E-4b03-8FA8-5C020552B5D6}]     **
**                                                                            **
** Syntax : MemIf_JobResultType Fls_17_Dmu_GetJobResult(void)                 **
**                                                                            **
** Service ID:  0x05                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Re-entrant                                                    **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out): : None                                                   **
**                                                                            **
** Return value    :  MemIf_JobResultType  - The result of the last job       **
**                                                                            **
** Description :                                                              **
**         This service shall return the result of the last job synchronously **
*******************************************************************************/
MemIf_JobResultType Fls_17_Dmu_GetJobResult(void)
/* [cover parentID={BDC1DA1D-8384-4ca0-9EA1-AD0E33D37102}][/cover] */
{

  MemIf_JobResultType RetVal;
  /* [cover parentID={F08DCF6B-684A-474e-89FE-F32D9B941CF5}]
  DET Enabled
  [/cover] */
  #if  ( FLS_17_DMU_DEV_ERROR_DETECT == STD_ON ) || \
  (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  /*  API  called before initialization */
  /* [cover parentID={624E029E-8CC6-418f-B8C6-17BB642D8A61}]
  Check for Uninit DET error
  [/cover] */

  /* [cover parentID={E9039619-FDF4-438b-A228-DB8EF06B29D7}]
  Check for Uninit DET error
  [/cover] */
  if (Fls_lUninitDET(FLS_17_DMU_SID_GETJOBRESULT) != 0U)
  {
    /* [cover parentID={B8DBD4BB-DA12-46f6-896B-51F7D7DCF1DC}]
    Return : Job failed
    [/cover] */
    RetVal = MEMIF_JOB_FAILED;
  }
  else
  #endif
  {
    /* [cover parentID={A5F084DF-5708-4ac2-933E-B241D4E0A3E2}]
    Update the local state pointer by the global configuration values
    Return the FLS Job Result (for the last job) stored by the Flash Driver
    [/cover] */
    RetVal = Fls_ConfigPtr->FlsStateVarPtr->FlsJobResult;
  }

  return(RetVal);
}
#endif
/*FLS_GET_JOB_RESULT_API == STD_ON */

#if  (FLS_17_DMU_ECC_ERROR_INFO_API  ==  STD_ON)
/******************************************************************************
** Traceability : [cover parentID={5D978438-49B5-4fed-9D92-E977E22885F0}]    **
**                                                                           **
** Syntax : Std_ReturnType  Fls_17_Dmu_GetEccErrorPageAddress(               **
**                                            uint32 * const PageAddressPtr) **
**                                                                           **
** Service ID:  0x2E                                                         **
**                                                                           **
** Sync/Async:  Synchronous                                                  **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) :  None                                                   **
**                                                                           **
** Parameters (out):  PageAddress - Pointer to store the last ECC error      **
**                                  occurred page address                    **
**                                                                           **
** Return value    :  None                                                   **
**                                                                           **
** Description :                                                             **
** Service to get the address of the flash page where last ECC error is      **
** detected.If there is no ECC error detected in the current power cycle,then**
** the value of PageAddress parameter will be 0xFFFFFFFF.                    **
******************************************************************************/
Std_ReturnType  Fls_17_Dmu_GetEccErrorPageAddress
(
    uint32 * const PageAddressPtr
)
{
  Std_ReturnType RetVal;
  /* [cover parentID={F996E829-28BE-45af-8B1D-D6B467DA7591}]
  Is null pointer passed as parameter?
  [/cover] */
  if(PageAddressPtr == NULL_PTR)
  {
    #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
    /* [cover parentID={F996E829-28BE-45af-8B1D-D6B467DA7591}]
    Report Safety Error
    [/cover] */
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                  FLS_17_DMU_SID_GETECCERRORPGADDR, FLS_17_DMU_SE_PARAM_DATA);
    #endif
    RetVal = E_NOT_OK;
  }
  /* [cover parentID={97BBDD9B-4C57-4513-BA34-0B0025F07466}]
  Is driver busy?
  [/cover] */
  else if(Fls_ConfigPtr->FlsStateVarPtr->FlsJobType != FLS_17_DMU_NONE)
  {
    #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
    /* [cover parentID={97BBDD9B-4C57-4513-BA34-0B0025F07466}]
    Report Safety Error
    [/cover] */
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                        FLS_17_DMU_SID_GETECCERRORPGADDR, FLS_17_DMU_SE_BUSY);
    #endif
    RetVal = E_NOT_OK;
  }
  else
  {
    /* [cover parentID={AE7FF18D-164C-46fe-921D-F3E8121BCF03}]
    Update the passed parameter with the latest address of the page where ECC
    was detected
    [/cover] */
    *PageAddressPtr = Fls_ConfigPtr->FlsStateVarPtr->FlsEccErrorPageAddress;
    RetVal = E_OK;
  }

  return(RetVal);
}
#endif

#if (FLS_17_DMU_IFX_FEE_USED == STD_ON)
/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax : Std_ReturnType Fls_17_Dmu_ReadWordsSync(                          **
**                                const Fls_17_Dmu_AddressType SourceAddress, **
**                                            uint32 *const TargetAddressPtr, **
**                                    const uint32 Length                     **
**                                         )                                  **
**                                                                            **
** Service ID:  0x21                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : SourceAddress, TargetAddressPtr and Length               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: Read successful                                    **
**                   E_NOT_OK: HW busy or read failed with ECC error          **
**                                                                            **
** Description : Service for reading word data from flash bank synchronously  **
*******************************************************************************/
Std_ReturnType Fls_17_Dmu_ReadWordsSync(
  const Fls_17_Dmu_AddressType SourceAddress,
  uint32 *const TargetAddressPtr,
  const uint32 Length)
/*[cover parentID={0E143A6B-82CC-4526-89DC-A33334872FB0}][/cover]*/
{
  Fls_17_Dmu_StateType  *StatePtr;
  uint8 JobType;
  uint32 PhysicalAddress;
  Std_ReturnType RetVal;
  const uint64 *SrcPtr;
  uint8 *DestPtr;
  uint32 ReadCount;
  #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_OFF)
  uint32 BitChange;
  #endif
  #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_ON)
  uint32 EccErrorFlag = 0U;
  #endif
  uint32 ErrorFlag = 0U;
  uint64 PageData;
  uint8 *PagePtr;
  uint32 PageOffset;
  uint32 PageBytes;
  /* [cover parentID={AC6F2839-EEDA-4960-9BE9-D7B6B8B47544}]
  Set the return value as E_OK
  [/cover] */
  RetVal = E_OK;

  #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)

  /*  Checking whether given SourceAddress is valid or not */
  /* [cover parentID={106DFBEB-28F5-4a04-ADBF-E68C075AAECD}]
  Check if the Source Address, Target Address AND Length are valid ?
  [/cover] */
  if((SourceAddress >= (FLS_17_DMU_TOTAL_SIZE)) ||
      (((Fls_17_Dmu_AddressType)SourceAddress & FLS_WORD_SIZE_MASK) != 0U))
  {
    /* [cover parentID={AC2C3207-C597-421b-AED1-4241772F58F4}]
    Report Safety Error
    [/cover] */
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                          FLS_17_DMU_SID_READSYNC, FLS_17_DMU_SE_PARAM_ADDRESS);

    RetVal = E_NOT_OK;
  }
  /*Check for Pointer to an application buffer*/
  /* [cover parentID={EDFECFC9-D884-4d10-AFEE-4F007B91DA32}]
  [/cover] */
  else if(TargetAddressPtr == NULL_PTR)
  {
    /* [cover parentID={AC2C3207-C597-421b-AED1-4241772F58F4}]
    Report Safety Error
    [/cover] */
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_READSYNC, FLS_17_DMU_SE_PARAM_DATA);

    RetVal = E_NOT_OK;
  }
  /* Checking whether given Length is valid or not */
  /* [cover parentID={47CFE999-29F4-46fd-910F-A04DB33EE144}]
  [/cover] */
  else if((Length < FLS_ONE_VALUE) ||
          (Length > ((FLS_17_DMU_TOTAL_SIZE - SourceAddress) / FLS_WORD_SIZE)))
  {
    /* [cover parentID={AC2C3207-C597-421b-AED1-4241772F58F4}]
    Report Safety Error
    [/cover] */
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_READSYNC, FLS_17_DMU_SE_PARAM_LENGTH);

    RetVal = E_NOT_OK;
  }
  /* [cover parentID={65D72724-2220-4887-A71C-D858DFD9F778}]
  Is the flash HW busy?
  [/cover] */
  else if(Fls_lHWBusyCheck() != 0U)
  {
    /* [cover parentID={AC2C3207-C597-421b-AED1-4241772F58F4}]
    Report Safety Error
    [/cover] */
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                       FLS_17_DMU_SID_READSYNC, FLS_17_DMU_SE_HW_BUSY);
    RetVal = E_NOT_OK;
  }
  else
  #endif
  {
    StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
    JobType = StatePtr->FlsJobType;

    /* [cover parentID={37D0FA7F-BE27-46ff-9A46-9BB3CDD69FDF}]
    Is there any ongoing job?
    [/cover] */
    /* Check if no operation ongoing */
    if(JobType == FLS_17_DMU_NONE)
    {
      /* Modify the GlobalVar JobType so that no new requests can be accepted on
      *the Bank till ReadSync is finished */
      StatePtr->FlsJobType = FLS_17_DMU_READSYNC;
      #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_OFF)
      /*Clear the ECC status bits by writing DMU_HF_ECCC.CLR with 11b */
      BitChange = DMU_HF_ECCC.U | FLS_DMU_ECCC_CLR;

      /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
       the object types as the address of the register is being passed.*/
      FLS_17_DMU_LIB_RUNTIME_WRITEPERIPENDINITPROTREG(\
          (volatile uint32 *)&DMU_HF_ECCC.U, \
          BitChange);
      /*There is a delay of 2-3 cycles in the clearing of AERM bit*/
      NOP();
      NOP();
      NOP();
      #endif
      /* Read the data */
      /* [cover parentID={4BFEA3B8-DE2F-4a0a-9187-F79A8384557D}]
      Is the length zero?
      [/cover] */
      ReadCount = (Length * FLS_WORD_SIZE);
      PhysicalAddress = (uint32)( FLS_17_DMU_BASE_ADDRESS + SourceAddress );
      PageOffset = (PhysicalAddress & FLS_PAGE_SIZE_MASK);
      /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from uint32 to uint64* is
      required to access the FLASH address for data buffer alignment and store
      it in pointerfor easy arithmetic operations. No memory alignment issues.*/
      /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from uint32 to uint64*
      type is required to access the FLASH address/target address and store it
      in pointer for easy arithmetic operations. No memory alignment issues.*/
      SrcPtr = (uint64*)Fls_lGetPageAddress(PhysicalAddress);
      PageBytes = (FLS_17_DMU_PAGE_SIZE - PageOffset);
      PageData = (*SrcPtr);
      /* DSYNC() is added to avoid compiler optimization (re-ordering of DFlash
      read and ECC error check in Fls_lChkBitErrors())*/
      DSYNC();
      /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
      PageData is used inside Fls_17_Dmu_ReadWordsSync() to
      read the values. The address is not used beyond the context of the
      API, hence it is not an issue*/
      PagePtr = (uint8*)(&PageData);
      PagePtr = &PagePtr[PageOffset];
      #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_ON)
      EccErrorFlag = Fls_lChkBitErrors();
      /* [cover parentID={83658E77-F821-491a-B410-21936EF18C5B}]
      [/cover] */
      if(EccErrorFlag != 0U)
      {
        ErrorFlag = 1U;
        /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from pointer to uint32
        is required to store the FLASH address/target address in state var
        structure. No memory alignment issues.*/
        /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from pointer to uint32
        type is required to access the FLASH address and store it in state var
        structure. No memory alignment issues.*/
        StatePtr-> FlsEccErrorPageAddress = (uint32)SrcPtr;
      }
      #endif
      SrcPtr++;
      /*MISRA2012_RULE_11_8_JUSTIFICATION: Casting is done to copy the flash
      data bytewise to the user buffer pointed by TargetAddressPtr. */
      DestPtr = (uint8*)TargetAddressPtr;
      while(ReadCount > 0U)
      {
        /* [cover parentID={50FD7B65-0EE5-40a9-A463-47E034E841C8}]
        [/cover] */
        if(PageBytes == 0U)
        {
          /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
          PageData is used inside Fls_17_Dmu_ReadWordsSync() to
          read the values. The address is not used beyond the context of the
          API, hence it is not an issue*/
          PagePtr = (uint8*)(&PageData);
          PageData = (*SrcPtr);
          /* DSYNC() is added to avoid compiler optimization (re-ordering of
          DFlash read and ECC error check in Fls_lChkBitErrors())*/
          DSYNC();
          #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_ON)
          EccErrorFlag = Fls_lChkBitErrors();
          /* [cover parentID={DB205178-F145-427c-A048-659AA2C02DA5}]
          [/cover] */
          if(EccErrorFlag != 0U)
          {
            ErrorFlag = 1U;
            /* update page addr*/
            /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from pointer to uint32
            is required to store the FLASH address/target address in state var
            structure. No memory alignment issues.*/
            /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from pointer to
            uint32 type is required to access the FLASH address and store it in
            state var structure. No memory alignment issues.*/
            StatePtr-> FlsEccErrorPageAddress = ((uint32)SrcPtr);
          }
          #endif
          PageBytes = FLS_17_DMU_PAGE_SIZE;
          SrcPtr++;
        }
        *DestPtr = *PagePtr;
        DestPtr++;
        PagePtr++;
        ReadCount--;
        PageBytes--;
      }
      #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_OFF)
      ErrorFlag = Fls_lChkBitErrors();
      #endif

      /* Restore the JobType with previous tasks */
      StatePtr->FlsJobType = FLS_17_DMU_NONE;
      /* Check for uncorrectable bit error */
      /* [cover parentID={3E0984C3-E497-489e-9384-BCB4A6069132}]
      Check for uncorrectable ECC errors
      [/cover] */
      /* [cover parentID={C15185C5-63ED-4af3-9B33-BD3F59CD0B67}]
      Is uncorrectable ECC error detected?
      [/cover] */
      if(ErrorFlag != 0U)
      {
        #if(MCAL_AR_VERSION == MCAL_AR_440)
        (void)Det_ReportTransientFault( (uint16)FLS_17_DMU_MODULE_ID,
                                FLS_17_DMU_INSTANCE_ID,
                                FLS_17_DMU_SID_READSYNC,
                                FLS_17_DMU_E_READ_FAILED);
        #else
          #if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
          (void)Mcal_Wrapper_Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                                FLS_17_DMU_INSTANCE_ID,
                                FLS_17_DMU_SID_READSYNC,
                                FLS_17_DMU_E_READ_FAILED);
          #endif
        #endif
        /* Return E_NOT_OK */
        RetVal = E_NOT_OK;
      }
    }
    else
    {
      /* [cover parentID={AC2C3207-C597-421b-AED1-4241772F58F4}]
      Report Safety Error
      [/cover] */
      #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
      Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                             FLS_17_DMU_SID_READSYNC, FLS_17_DMU_SE_BUSY);
      #endif
      RetVal = E_NOT_OK;
    }
  }
  return(RetVal);
}


/*******************************************************************************
** Traceability : [cover parentID={071F2EBB-AF4C-4744-89F8-D802E4DDB976}]     **
**                                                                            **
** Syntax : Std_ReturnType Fls_17_Dmu_CompareWordsSync(                       **
**                              const Fls_17_Dmu_AddressType SourceAddress,   **
**                                     const uint32 *const TargetAddressPtr,  **
**                                     const uint32 Length);                  **
**                                                                            **
** Service ID: 0x22                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : SourceAddress - Source address in Flash memory.          **
**          This address offset is added to the flash memory base address     **
**                   TargetAddressPtr - Pointer to target data buffer         **
**                   Length - Number of words to be compared. It takes the    **
**                   value from 1 to Flash Size                               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: Compare successful                                 **
**                   E_NOT_OK: HW busy or compare failed or ECC error         **
**                                                                            **
** Description : Service for comparing data from flash bank synchronously     **
*******************************************************************************/
/* CYCLOMATIC_Fls_17_Dmu_CompareWordsSync_JUSTIFICATION: This Function has
 cyclomatic complexity of 15, as the read optimization is implemented along with
 the ECC error info enhancement. This cannot be further broken down into local
 function.*/
Std_ReturnType Fls_17_Dmu_CompareWordsSync(
  const Fls_17_Dmu_AddressType SourceAddress,
  const uint32 *const TargetAddressPtr,
  const uint32 Length)
/* [cover parentID={EA54EE68-6A30-4a38-A981-DD82346FC1A1}][/cover] */
{
  Fls_17_Dmu_StateType  *StatePtr;
  uint8 JobType;
  uint32 PhysicalAddress;
  Std_ReturnType RetVal;
  const uint64 *SrcPtr;
  const uint8 *DestPtr;
  uint32 CompLen;
  #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_OFF)
  uint32 BitChange;
  #endif
  #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_ON)
  uint32 EccErrorFlag = 0U;
  #endif
  uint32 ErrorFlag = 0U;
  uint64 PageData;
  uint8 *PagePtr;
  uint32 PageOffset;
  uint32 PageBytes = 0U;
  RetVal = E_OK;

  #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  /*  Checking whether given SourceAddress is valid or not */
  /* [cover parentID={4FD34CA4-DBD9-41e2-A799-495CB014483A}]
  Check if Valid SourceAddress, Target Address pointer AND Length are
  passed ?
  [/cover] */
  if((SourceAddress >= (FLS_17_DMU_TOTAL_SIZE)) ||
      (((uint32)SourceAddress & FLS_WORD_SIZE_MASK) != 0U))
  {
    /* [cover parentID={51D3C659-C8AF-4f0c-9197-D279B447C36D}]
    Report Safety Error
    [/cover] */
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_COMPARESYNC,
                           FLS_17_DMU_SE_PARAM_ADDRESS);

    RetVal = E_NOT_OK;
  }
  /*Check for Pointer to an application buffer*/
  /* [cover parentID={E678B87C-2CD1-4ada-97BB-71CEA86D44C3}]
  Check if Valid SourceAddress, Target Address pointer AND Length are
  passed ?
  [/cover] */
  else if(TargetAddressPtr == NULL_PTR)
  {
    /* [cover parentID={51D3C659-C8AF-4f0c-9197-D279B447C36D}]
    Report Safety Error
    [/cover] */
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                          FLS_17_DMU_SID_COMPARESYNC, FLS_17_DMU_SE_PARAM_DATA);

    RetVal = E_NOT_OK;
  }
  /* Checking whether given Length is valid or not */
  /* [cover parentID={6F2DF1C2-4685-4ec2-BE35-2F6B9F336323}]
  Check if Valid SourceAddress, Target Address pointer AND Length are
  passed ?
  [/cover] */
  else if((Length < FLS_ONE_VALUE) ||
          (Length > ((FLS_17_DMU_TOTAL_SIZE - SourceAddress) / FLS_WORD_SIZE)))
  {
    /* [cover parentID={51D3C659-C8AF-4f0c-9197-D279B447C36D}]
    Report Safety Error
    [/cover] */
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                        FLS_17_DMU_SID_COMPARESYNC, FLS_17_DMU_SE_PARAM_LENGTH);

    RetVal = E_NOT_OK;
  }/*Range Check Over*/

  /* [cover parentID={77BFA20F-CA11-46b5-9298-458699DBD7FF}]
  Is flash HW busy?
  [/cover] */
  else if(Fls_lHWBusyCheck() != 0U)/*HW Busy check*/
  {
    /* [cover parentID={51D3C659-C8AF-4f0c-9197-D279B447C36D}]
    Report Safety Error
    [/cover] */
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_COMPARESYNC, FLS_17_DMU_SE_HW_BUSY);
    RetVal = E_NOT_OK;
  }
  else
  #endif
  {
    StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
    JobType = StatePtr->FlsJobType;
    CompLen = (Length * FLS_WORD_SIZE);
    PhysicalAddress = (uint32)( FLS_17_DMU_BASE_ADDRESS + SourceAddress);
    /* Check if no operation ongoing */
    /* [cover parentID={9238260E-3B01-492e-B273-C446ABE18069}]
    Is there any ongoing job ?
    [/cover] */
    if(JobType == FLS_17_DMU_NONE)
    {
      /* Modify the GlobalVar JobType so that no new requests can be accepted on
      the Bank till CompareSync is finished */
      /* [cover parentID={59CE9E38-7367-44ac-8B70-73D939397B9B}]
      Update the job type to comparesync
      [/cover] */
      StatePtr->FlsJobType = FLS_17_DMU_COMPARESYNC;
      #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_OFF)
      /*Clear the ECC status bits by writing DMU_HF_ECCC.CLR with 11b to clear
              AERM bit*/
      /* [cover parentID={128AD975-478F-4c58-A290-C3609D63DCF1}]
      Clear the ECC error bit(AERM)
      [/cover] */
      BitChange = DMU_HF_ECCC.U | FLS_DMU_ECCC_CLR;
      /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
       the object types as the address of the register is being passed.*/
      FLS_17_DMU_LIB_RUNTIME_WRITEPERIPENDINITPROTREG(\
          (volatile uint32 *)&DMU_HF_ECCC.U, \
          BitChange);
      /*There is a delay of 2-3 cycles in the clearing of AERM bit*/
      NOP();
      NOP();
      NOP();
      #endif
      PageOffset = (PhysicalAddress & FLS_PAGE_SIZE_MASK);
      /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from uint32 to uint64* is
      required to access the FLASH address for data buffer alignment and store
      it in pointer for easy arithmetic operations. No memory alignment
      issues.*/
      /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from uint32 to uint64*
      type is required to access the FLASH address/target address and store it
      in pointer for easy arithmetic operations. No memory alignment issues.*/
      SrcPtr = (uint64*)Fls_lGetPageAddress(PhysicalAddress);
      PageBytes = (FLS_17_DMU_PAGE_SIZE - PageOffset);
      PageData = (*SrcPtr);
      /* DSYNC() is added to avoid compiler optimization (re-ordering of DFlash
      read and ECC error check in Fls_lChkBitErrors())*/
      DSYNC();
      /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
      PageData is used inside Fls_17_Dmu_CompareWordsSync() to
      read the values. The address is not used beyond the context of the
      API, hence it is not an issue*/
      PagePtr = (uint8*)(&PageData);
      PagePtr = &PagePtr[PageOffset];
      #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_ON)
      EccErrorFlag = Fls_lChkBitErrors();
      /* [cover parentID={4594FA54-3F26-47fb-9181-1FC700CA61B3}]
      Is error flag set?
      [/cover] */
      if(EccErrorFlag != 0U)
      {
        /* [cover parentID={97593709-8549-4aad-B2CC-43BBA356C817}]
        [/cover] */
        ErrorFlag = 1U;
        /* update page addr*/
        /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from pointer to uint32
        is required to store the FLASH address/target address in state var
        structure. No memory alignment issues.*/
        /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from pointer to uint32
        type is required to access the FLASH address and store it in state var
        structure. No memory alignment issues.*/
        StatePtr-> FlsEccErrorPageAddress = (uint32)SrcPtr;
      }
      #endif
      SrcPtr ++;
      /*MISRA2012_RULE_11_8_JUSTIFICATION: Casting is done to copy the flash
      data bytewise to the user buffer pointed by TargetAddressPtr. */
      DestPtr = (uint8*)TargetAddressPtr;
      /* [cover parentID={89BED17C-08A5-4bd5-AA34-61F134E9182B}]
      Is the compare length zero ?
      [/cover] */
      while(CompLen > 0U)
      {
        if(PageBytes == 0U)
        {
          /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
          PageData is used inside Fls_17_Dmu_CompareWordsSync() to
          read the values. The address is not used beyond the context of the
          API, hence it is not an issue*/
          PagePtr = (uint8*)(&PageData);
          PageData = *SrcPtr;
          /* DSYNC() is added to avoid compiler optimization (re-ordering of
          DFlash read and ECC error check in Fls_lChkBitErrors())*/
          DSYNC();
          #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_ON)
          EccErrorFlag = Fls_lChkBitErrors();
          /* [cover parentID={6D1F1685-EBC6-4b71-96E3-C60FEB81FDF0}]
          Is error flag set?
          [/cover] */
          if(EccErrorFlag != 0U)
          {
            ErrorFlag = 1U;
            /* update page addr*/
            /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from pointer to uint32
            is required to store the FLASH address/target address in state var
            structure. No memory alignment issues.*/
            /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from pointer to
            uint32 type is required to access the FLASH address and store it in
            state var structure. No memory alignment issues.*/
            StatePtr-> FlsEccErrorPageAddress = (uint32)SrcPtr;
          }
          #endif
          PageBytes = FLS_17_DMU_PAGE_SIZE;
          SrcPtr++;
        }
        CompLen--;
        /* Compare the flash data with the buffer data */
        /* [cover parentID={F431BD56-7EDE-4f60-A896-EAD3EBBEA036}]
        [/cover] */
        if (*DestPtr != *PagePtr)
        {
          CompLen = 0U;
          RetVal = E_NOT_OK;
        }
        DestPtr++;
        PagePtr++;
        PageBytes--;
      }

      /* Restore the JobType with previous tasks */
      StatePtr->FlsJobType = FLS_17_DMU_NONE;

      #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_OFF)
      ErrorFlag = Fls_lChkBitErrors();
      #endif
      /* Check for uncorrectable bit error */
      /* [cover parentID={249BBF67-8E21-4fdf-B509-FF012107651F}]
      Is uncorrectable ECC error detected?
      [/cover] */
      if(ErrorFlag != 0U)
      {
        #if(MCAL_AR_VERSION == MCAL_AR_440)
        (void)Det_ReportTransientFault( (uint16)FLS_17_DMU_MODULE_ID,
                                  FLS_17_DMU_INSTANCE_ID,
                                  FLS_17_DMU_SID_COMPARESYNC,
                                  FLS_17_DMU_E_COMPARE_FAILED);
        #else
          #if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
          /* [cover parentID={08F6505A-55B1-4c60-868B-9AE1A58BD337}]
          Report runtime error
          [/cover] */
          (void)Mcal_Wrapper_Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                                  FLS_17_DMU_INSTANCE_ID,
                                  FLS_17_DMU_SID_COMPARESYNC,
                                  FLS_17_DMU_E_COMPARE_FAILED);
          #endif
        #endif
        /* [cover parentID={D271F1A4-BCAA-4111-B71B-C65816C69E14}]
        Set the Return value as NOT OK
        [/cover] */
        /* Return E_NOT_OK */
        RetVal = E_NOT_OK;
      }
    }
    else
    {
      /* [cover parentID={51D3C659-C8AF-4f0c-9197-D279B447C36D}]
      Report Safety Error
      [/cover] */
      #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
      Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                             FLS_17_DMU_SID_COMPARESYNC, FLS_17_DMU_SE_BUSY);
      #endif

      RetVal = E_NOT_OK;

    }
  }
  return(RetVal);
}


#if (FLS_17_DMU_IFX_NVM_PRESENT == STD_ON)
/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax : Std_ReturnType Fls_17_Dmu_VerifyErase(                            **
**                         const Fls_17_Dmu_AddressType TargetAddress         **
**                               ,uint32 *const UnerasedWordlineAddressPtr    **
**                               uint8 * const UnerasedWordlineCountPtr       **
**                               )                                            **
**                                                                            **
** Service ID: 0x23                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : TargetAddress                                            **
**                                                                            **
** Parameters (out): UnerasedWordlineAddressPtr,UnerasedWordlineCountPtr      **
**                                                                            **
** Return value    :  E_OK: Erase verification successful                     **
**                    E_NOT_OK: HW busy or erase verification failed          **
**                                                                            **
** Description : Service for verifying erase of a sector                      **
*******************************************************************************/
Std_ReturnType Fls_17_Dmu_VerifyErase(
  const Fls_17_Dmu_AddressType TargetAddress,
  uint32 *const UnerasedWordlineAddressPtr,
  uint8 * const UnerasedWordlineCountPtr )
/* [cover parentID={5E18E6DD-2144-49f5-8745-3EED2D934CE0}]
Fls_17_Dmu_VerifyErase
[/cover] */
/*[cover parentID={3C77357E-5460-46ff-A479-A216C527E574}][/cover]*/
{

  Std_ReturnType RetVal;


  #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  const Fls_17_Dmu_StateType  *StatePtr;
  uint8 JobType;
  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
  JobType = StatePtr->FlsJobType;

  /* Checking whether given TargetAddress is valid or not */
  /* [cover parentID={C91AC245-9A1A-4969-90A0-E3B85AFCBAFF}]
  Check if the Target Address is valid ?
  [/cover] */
  if(((uint32)TargetAddress >= FLS_17_DMU_TOTAL_SIZE) ||
      ((TargetAddress & FLS_MOD4K_MASK ) != 0U))
  {
    /* [cover parentID={2561E479-101F-4dcb-A481-F44D709DFC01}]
    Report Safety Error
    [/cover] */
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_VERIFYERASE,
                           FLS_17_DMU_SE_PARAM_ADDRESS);

    RetVal = E_NOT_OK;
  }

  /* [cover parentID={A0982E2C-E7C1-48c3-97CA-C8575A744659}]
  Is the Unerasable Word Line Counter Address is Valid ?
  [/cover] */
  /* [cover parentID={E46A3AD4-479E-4b64-A4BA-8F55B7F031E3}]
  Is the UnerasableWord Line buffer Address valid ?
  [/cover] */
  else if((UnerasedWordlineAddressPtr == NULL_PTR) ||
          (UnerasedWordlineCountPtr == NULL_PTR))
  {

    /* [cover parentID={2561E479-101F-4dcb-A481-F44D709DFC01}]
    Report Safety Error
    [/cover] */
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                          FLS_17_DMU_SID_VERIFYERASE, FLS_17_DMU_SE_PARAM_DATA);

    RetVal = E_NOT_OK;
  }
  /* [cover parentID={EFC67AE6-E063-42b3-9474-32E7F663F3FC}]
  Is driver IDLE?
  [/cover] */
  else  if(JobType != FLS_17_DMU_NONE)/*Driver Busy*/
  {
    /* [cover parentID={2561E479-101F-4dcb-A481-F44D709DFC01}]
    Report Safety Error
    [/cover] */
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_VERIFYERASE, FLS_17_DMU_SE_BUSY);
    RetVal = E_NOT_OK;
  }
  /* [cover parentID={F939BB22-8474-4f86-8782-5A7BCCE24B2D}]
  Is the FLS HW IDLE ?
  [/cover] */
  else if(Fls_lHWBusyCheck() != 0U)/*HW Busy check*/
  {
    /* [cover parentID={2561E479-101F-4dcb-A481-F44D709DFC01}]
    Report Safety Error
    [/cover] */
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_VERIFYERASE, FLS_17_DMU_SE_HW_BUSY);
    RetVal = E_NOT_OK;
  }
  else
  {
  #endif

    /* [cover parentID={9C701D72-F144-44a7-B620-3D229B8F49ED}]
       [/cover] */
    RetVal = Fls_lLocalVerifyErase(TargetAddress, UnerasedWordlineAddressPtr,
                                   UnerasedWordlineCountPtr, 0U, 0U);
    #if(FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  }
    #endif
  return(RetVal);

}
#endif


/*******************************************************************************
** Traceability :  [cover parentID={73A7CFF7-D3A9-49ba-A186-E9AA3F27FC09}]    **
**                                                                            **
** Syntax : Std_ReturnType Fls_17_Dmu_VerifySectorErase                       **
**                                (const Fls_17_Dmu_AddressType TargetAddress,**
**                                 uint32 * const UnerasedWordlineAddressPtr  **
**                                 uint8 * const UnerasedWordlineCountPtr     **
**                               const uint8 Sector);                         **
**                                                                            **
** Service ID: 0x24                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : TargetAddress,Sector                                     **
**                                                                            **
** Parameters (out): UnerasedWordlineAddressPtr,UnerasedWordlineCountPtr      **
**                                                                            **
** Return value    :  E_OK: Erase verification successful                     **
**                    E_NOT_OK: HW busy or erase verification failed          **
**                                                                            **
** Description : Service for verifying erase of a sector                      **
*******************************************************************************/
Std_ReturnType Fls_17_Dmu_VerifySectorErase(
  const Fls_17_Dmu_AddressType TargetAddress,
  uint32 *const UnerasedWordlineAddressPtr,
  uint8 *const UnerasedWordlineCountPtr,
  const uint8 Sector)
/* [cover parentID={2643CE1D-3341-479a-A7C9-4AB37E7FAD8D}]
Fls_17_Dmu_VerifySectorErase[/cover] */
/* [cover parentID={E4899288-DB87-4ef0-94EB-11BD01754497}][/cover] */
{
  Std_ReturnType RetVal;

  #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  const Fls_17_Dmu_StateType  *StatePtr;
  uint8 JobType;
  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
  JobType = StatePtr->FlsJobType;

  /* Checking whether given TargetAddress is valid or not */
  /* [cover parentID={97B0627D-ACE6-43f7-9B7C-6A2DA77E3D94}]
  Is the Target Address valid ?
  [/cover] */
  if(((uint32)TargetAddress >= FLS_17_DMU_TOTAL_SIZE) ||
      ((TargetAddress & FLS_MOD4K_MASK ) != 0U))
  {
    /* Report Safety Error*/


    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_VERIFYSECTORERASE,
                           FLS_17_DMU_SE_PARAM_ADDRESS);

    RetVal = E_NOT_OK;
  }

  /* [cover parentID={6EC80274-A0EC-4e5e-A6FD-BA66135BBA79}]
  Is the UnerasableWordlineAddressBuffer valid?
  [/cover] */
  else if((UnerasedWordlineAddressPtr == NULL_PTR) ||
          (UnerasedWordlineCountPtr == NULL_PTR))
  {
    /* Report Safety Error */
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_VERIFYSECTORERASE,
                           FLS_17_DMU_SE_PARAM_DATA);

    RetVal = E_NOT_OK;
  }
  /*FLS_17_DMU_NVMSECTOR_SIZE will always be a multiple of 4K*/
  /* [cover parentID={9B9D5B4D-A521-4778-9E4E-DF7F0606D8F7}]
  Is the sector given is valid ?
  [/cover] */
  else if(Sector >= (FLS_17_DMU_NVMSECTOR_SIZE / FLS_17_DMU_SUBSECTOR_SIZE))
  {
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_VERIFYSECTORERASE,
                           FLS_17_DMU_SE_PARAM_INVLD);
    RetVal = E_NOT_OK;
  }
  /* [cover parentID={66433ED3-1964-4c98-9E98-D445C29EC469}]
  Is driver IDLE?
  [/cover] */
  else  if(JobType != FLS_17_DMU_NONE)/*Driver Busy*/
  {
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_VERIFYSECTORERASE,
                           FLS_17_DMU_SE_BUSY);
    RetVal = E_NOT_OK;
  }
  /* [cover parentID={8ABBE01A-C680-4b23-B7DE-6AE6D9A2CE11}]
  [/cover] */
  else if(Fls_lHWBusyCheck() != 0U)/*HW Busy check*/
  {
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_VERIFYSECTORERASE,
                           FLS_17_DMU_SE_HW_BUSY);
    RetVal = E_NOT_OK;
  }
  else
  {
  #endif

    /* [cover parentID={59936861-E6B4-4d62-B7AA-273A6D67920F}]
           [/cover] */
    RetVal = Fls_lLocalVerifyErase(TargetAddress, UnerasedWordlineAddressPtr,
                                   UnerasedWordlineCountPtr, Sector,
                                   FLS_VERIFYSECTOR_CHK_VAL);
    #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  }
    #endif
  return(RetVal);
}


/*******************************************************************************
** Traceability :  [cover parentID={EDD8E749-FB74-4f70-AA54-681738556B8D}]    **
**                                                                            **
** Syntax : Std_ReturnType Fls_lLocalVerifyErase                              **
**                            (const Fls_17_Dmu_AddressType TargetAddress,    **
**                                 uint32 * const UnerasedWordlineAddressPtr  **
**                                 uint8 * const UnerasedWordlineCountPtr     **
**                            const uint8 *Sector, const uint32 value)        **
**                                                                            **
** Service ID: 0x24                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : TargetAddress,Sector                                     **
**                                                                            **
** Parameters (out): UnerasedWordlineAddressPtr,UnerasedWordlineCountPtr,     **
**                                                                            **
**                                                                            **
** Return value    :  E_OK: Erase verification successful                     **
**                    E_NOT_OK: HW busy or erase verification failed          **
**                                                                            **
** Description : Service for verifying erase of a sector                      **
*******************************************************************************/
static Std_ReturnType Fls_lLocalVerifyErase(
  const Fls_17_Dmu_AddressType TargetAddress,
  uint32 *const UnerasedWordlineAddressPtr,
  uint8 *const UnerasedWordlineCountPtr,
  const uint8 Sector, const uint32 value)
{
  Fls_17_Dmu_StateType  *StatePtr;
  uint32 PhysicalAddress;
  uint64 *SrcPtr;
  uint64 PageData;
  uint32 Length;
  uint32 UnerasableWLAddr;
  uint32 HFMarginBackUpVal;
  uint32 BitChange;
  uint32 TimeOutCountInitial;
  uint32 TimeOutResolution;
  uint32 TimeOutCount;
  uint32 MeasuredTicks;
  uint32 ErrorFlag = 0U;
  uint8 FailCount;
  uint8 CompareFail;
  uint8 JobType;
  Std_ReturnType RetVal;
#if (FLS_17_DMU_IFX_NVM_PRESENT == STD_OFF)
  Length = FLS_17_DMU_SUBSECTOR_SIZE;
  FailCount = *UnerasedWordlineCountPtr;
  SrcPtr =
   /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from uint32 to uint64*
   type is required to access the FLASH address/target address and store it in
   pointer for easy arithmetic operations. No memory alignment issues.*/
   /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from uint32 to uint64*
   is required to access the FLASH address and thereby perform page reads.
   No memory alignment issues.*/
   /* MISRA2012_RULE_10_8_JUSTIFICATION: Cast from uint32 to uint64* type
   is required to store the FLASH address/target address and thereby perform
   page reads. No truncation or loss of information is resulted from this
   cast.*/
   (uint64 *)((FLS_17_DMU_BASE_ADDRESS + TargetAddress) + \
         (uint32)(FLS_17_DMU_SUBSECTOR_SIZE * Sector));
#endif

  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
  JobType = StatePtr->FlsJobType;

  RetVal = E_OK;

  /* Store the DMU_HF_MARGIN value so that it can be restored later */

  HFMarginBackUpVal = DMU_HF_MARGIN.U;

  /* [cover parentID={D040DA42-C45F-446e-BA44-1490FED7C3C6}]
  [/cover] */
  if(value == FLS_VERIFYSECTOR_CHK_VAL)
  {

    /* [cover parentID={D08CFEBB-BB0B-4396-8C2A-4B6FA50FA484}]
      [/cover] */
    FailCount = *UnerasedWordlineCountPtr;
  }
  #if (FLS_17_DMU_IFX_NVM_PRESENT == STD_ON)
  else
  {

    /* [cover parentID={72D41EF1-D0FC-4042-9DD7-EB3BB163712D}]
    [/cover] */
    FailCount = 0U;
  }
  #endif
  #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_OFF)
  /*Clear the ECC status bits by writing DMU_HF_ECCC.CLR with 11b to clear
                   AERM bit*/
  BitChange = DMU_HF_ECCC.U | FLS_DMU_ECCC_CLR;

  /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
   the object types as the address of the register is being passed.*/
  FLS_17_DMU_LIB_RUNTIME_WRITEPERIPENDINITPROTREG(\
      (volatile uint32 *)&DMU_HF_ECCC.U, \
      BitChange);
  #endif
  /* If EVER bit is 1, then read has to be performed with tight margin for
  0-level. Switch to hard margin is done here instead of doing it just before
     read, because it takes 2us (tFL_MarginDel) for the switch over to happen.
     */
  BitChange = (DMU_HF_MARGIN.U | FLS_READHARDMARGIN_VAL)& \
              FLS_TIGHT0MARGIN_VAL;
  DMU_HF_MARGIN.U = BitChange;
  NOP();
  NOP();

  /* [cover parentID={371B2DD6-ADBF-4530-A11F-E92A512AD2C5}]
  Wait for 2us for margin set up
  [/cover] */
  /*2us delay for margin switchover*/
  TimeOutResolution = Mcal_DelayTickResolution();
  TimeOutCount = (uint32)FLS_DMU_MARGIN_TIMEOUT / TimeOutResolution;
  TimeOutCountInitial = Mcal_DelayGetTick();

  do
  {
    MeasuredTicks = Mcal_DelayGetTick() -  TimeOutCountInitial;

  } while (TimeOutCount > MeasuredTicks);

  PhysicalAddress = FLS_17_DMU_BASE_ADDRESS + TargetAddress;

  /* [cover parentID={E613808C-16A9-4daf-84CE-B18CC5B5C6EB}]
  [/cover] */
  if(value == FLS_VERIFYSECTOR_CHK_VAL)
  {

    SrcPtr =
      /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from uint32 to
      uint64* type is required to access the FLASH address and thereby
      perform page reads. No memory alignment issues. */
      /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from uint32 to uint64* type
      is required to check the value of the address for data buffer alignment.
      No memory alignment issues.*/
      /* MISRA2012_RULE_10_8_JUSTIFICATION: Cast from uint32 to uint64* type
      is required to store the FLASH address/target address and thereby perform
      page reads. No truncation or loss of information is resulted from this
      cast.*/
      /* [cover parentID={063F8BCF-D0BD-4dc8-9FEB-67E28F4D3728}]
      [/cover] */
      (uint64 *)(PhysicalAddress + (uint32)(FLS_17_DMU_SUBSECTOR_SIZE * \
                                            Sector));

  }
  #if (FLS_17_DMU_IFX_NVM_PRESENT == STD_ON)
  else
  {
    /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from uint32 to uint64*
    type is required to access the FLASH address for data buffer alignment
    and store it in SrcPtr for easy arithmetic operations. No memory
    alignment issues.*/
    /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from uint32 to uint64* is
    required to access the FLASH address for data buffer alignment and store
    it in pointer for easy arithmetic operations. No memory alignment issues.*/

    /* [cover parentID={28A9A6B6-08E7-4030-ABCD-D47DE0DFB515}]
    [/cover] */
    SrcPtr = (uint64*)PhysicalAddress;
  }
  #endif

  /* Check if no operation ongoing */
  /* [cover parentID={59493295-2203-4e9a-8E20-B6B420DDD482}]
  Is there a Job pending ?
  [/cover] */
  if(JobType == FLS_17_DMU_NONE)
  {
    /* Modify the GlobalVar JobType so that no new requests can be accepted on
                   the Bank till VerifyErase is finished */
    StatePtr->FlsJobType = FLS_17_DMU_VERIFYERASE;

    /* [cover parentID={8D0BF8F5-BDAD-4ad0-91DC-1E69943BFDCF}]
    Is the erase verification of the sector to be done ?
    [/cover] */
    if(value == FLS_VERIFYSECTOR_CHK_VAL )
    {
      /* Data Flash Bank0 : Logical sector size-> 4K bytes*/

      /* [cover parentID={5DEA9552-A223-43dd-8D7E-1E29888AFED3}]
          [/cover] */
      Length = FLS_17_DMU_SUBSECTOR_SIZE;
    }
    #if (FLS_17_DMU_IFX_NVM_PRESENT == STD_ON)
    else
    {
      /* [cover parentID={4C69C001-A357-46e6-BD1D-74F68486B195}]
      [/cover] */
      Length = FLS_17_DMU_NVMSECTOR_SIZE;
    }
    #endif

    /* Check if there is verify error during Erase operation */
    while((Length != 0U) && (FailCount <= FLS_WL_FAIL_COUNT))
    {
      CompareFail = 0U;
      PageData = *SrcPtr;
      /* DSYNC() is added to avoid compiler optimization (re-ordering of DFlash
      read and ECC error check in Fls_lChkBitErrors())*/
      DSYNC();
      #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_ON)
      /* [cover parentID={779C0349-1545-4e48-82CD-A04703EC7B7E}]
      Is the ECC error present ?
      [/cover] */
      if(Fls_lChkBitErrors()!= 0U)
      {
        ErrorFlag = 1U;
        /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from pointer to uint32
        is required to store the FLASH address/target address in state var
        structure. No memory alignment issues.*/
        /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from pointer to uint32
        type is required to access the FLASH address and store it in state var
        structure. No memory alignment issues.*/
        StatePtr->FlsEccErrorPageAddress = (uint32)SrcPtr;
      }
      #endif
      PageData |= SrcPtr[1];
      /* DSYNC() is added to avoid compiler optimization (re-ordering of DFlash
      read and ECC error check in Fls_lChkBitErrors())*/
      DSYNC();
      /* [cover parentID={AAF177CA-38BE-4ae6-B034-9F5ADD199216}]
      Is the ECC error present ?
      [/cover] */
      if(Fls_lChkBitErrors()!= 0U)
      {
        ErrorFlag = 1U;
        #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_ON)
        StatePtr->FlsEccErrorPageAddress = (uint32)SrcPtr[1];
        #endif
      }

      /* COMPARE THE FLASH DATA WITH zero (first 16 Bytes of the Wordline)*/
      /* [cover parentID={B13AFAA0-6A7A-421c-89E0-61E2A4ACCDAA}]
           [/cover] */
      if((PageData != 0U) || (ErrorFlag != 0U))
      {
        /* [cover parentID={3CECDCD9-5370-41db-B503-BE7381F6CE13}]
        Set the Compare Flag and clear the errors
        [/cover] */
        CompareFail = 1U;
      }

      /* [cover parentID={A22C0065-DEFA-4b9f-B8B6-136F8CBD10AF}]
      Is the compare flag set ?
      [/cover] */
      if(CompareFail == 1U)
      {

        FailCount++;

        /* [cover parentID={F310322C-941E-49c1-BECA-80CE10999925}]
        Is the Fail Count more than the max Fail count?
        [/cover] */
        if(FailCount > FLS_WL_FAIL_COUNT)
        {
          /* [cover parentID={C10C46F2-9D2A-4543-A6F4-B9A0C6454F0D}]
          Set the return value to E_NOT_OK
          [/cover] */
          RetVal = E_NOT_OK;

        }
        else
        {
          /* Update the Unerasable WL address */
          /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from pointer to
          uint32 type is required to access the FLASH address. No memory
          alignment issues. */
          /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from pointer to uint32 is
          required to access the flash address and store it in UnerasableWLAddr.
          No memory alignment issues. */
          UnerasableWLAddr = (uint32)SrcPtr - FLS_17_DMU_BASE_ADDRESS;

          /* [cover parentID={330D00BF-4F65-48bf-A117-4AF2E2B46BB8}]
          Update the un-erasable wordline address
          Increment the address of the buffer to the next address
          Decrement the length
          Increment the FLS address to the next address for verification
          [/cover] */
          /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
          array indexing used for FLASH address calculation and for subsequent
          traversal.The access range is within the flash address range.*/
          /* MISRA2012_RULE_10_4_JUSTIFICATION: Cast from uint8 to uint32
            is required to interface for storage of failed wordline address
            in the FEE buffer. The operation is working as expected.*/
          *(UnerasedWordlineAddressPtr + ((uint32)FailCount - 1U))
            = UnerasableWLAddr;

          /* increment SrcPtr to next wordline, divide by 4 for SrcPtr is
             uint32 ptr*/

          /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
          array indexing used for FLASH address calculation and for subsequent
          traversal.The access range is within the flash address range.*/
          SrcPtr += (FLS_17_DMU_WORDLINE_SIZE / FLS_17_DMU_PAGE_SIZE);
          Length -= FLS_17_DMU_WORDLINE_SIZE;
          ErrorFlag = 0U;
        }
      }
      else
      {
        /* increment SrcPtr to next wordline, divide by 4 for SrcPtr is
           uint32 ptr*/

        /* [cover parentID={12BD4FE5-B880-4b64-A718-9BED64AF1509}]
            [/cover] */
        /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
        array indexing used for FLASH address calculation and for subsequent
        traversal.The access range is within the flash address range.*/
        SrcPtr += (FLS_17_DMU_WORDLINE_SIZE / FLS_17_DMU_PAGE_SIZE);
        Length -= FLS_17_DMU_WORDLINE_SIZE;
        ErrorFlag = 0U;
      }

    }

    /* [cover parentID={EDF703EC-DC51-43c1-9BFF-7E3A3D11D9F7}]
    Update the failed word line count in the wordline count buffer
    [/cover] */
    *UnerasedWordlineCountPtr = FailCount;

    /* Restore the JobType with previous tasks */
    StatePtr->FlsJobType = FLS_17_DMU_NONE;
  }
  else
  {
    /* [cover parentID={C10C46F2-9D2A-4543-A6F4-B9A0C6454F0D}]
    Set the return value to E_NOT_OK
    [/cover] */
    RetVal = E_NOT_OK;

  }

  /*Restore the DMU_HF_MARGIN value that was backed-up earlier */
  DMU_HF_MARGIN.U = HFMarginBackUpVal;

  return(RetVal);
}



/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax : Fls_17_Dmu_Job_Type Fls_17_Dmu_GetNotifCaller(void)               **
**                                                                            **
** Service ID: 0x29                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  FLS Job that raised the notification                    **
**                                                                            **
** Description :                                                              **
** Ths function returns the FLS Job that raised the notification              **
*******************************************************************************/
Fls_17_Dmu_Job_Type Fls_17_Dmu_GetNotifCaller(void)
/* [cover parentID={519B41BB-BF62-462e-ABC6-1F035388EE0F}][/cover] */
{
  /* [cover parentID={1A32FA81-F43C-4ea1-8475-A19BB0177DD1}]
  Notify the caller with the present running job
  [/cover] */
  return(Fls_ConfigPtr->FlsStateVarPtr->NotifCaller);
  /* [cover parentID={0C41A653-5FBA-4588-B5C5-E6E215A3616F}]
  Return
  [/cover] */

}

#endif /* FLS_17_DMU_IFX_FEE_USED == STD_ON */


/*[cover parentID={2CDC5CFF-A02A-4fb1-8FED-A46CBA2351DA}][/cover]*/
#if (FLS_17_DMU_USE_ERASESUSPEND == STD_ON)
/*******************************************************************************
** Traceability :  [cover parentID={169CB9F4-AF3D-48a8-89DA-B7E27440AA98}]    **
**                                                                            **
** Syntax : Std_ReturnType Fls_17_Dmu_SuspendErase(void)                      **
**                                                                            **
** Service ID: 0x25                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  E_OK - Erase suspend successful                         **
**                    E_NOT_OK - Erase suspend failed                         **
**                                                                            **
** Description :                                                              **
** Ths function suspends an ongoing erase of a sector.                        **
*******************************************************************************/
Std_ReturnType Fls_17_Dmu_SuspendErase(void)
/* [cover parentID={E62F23D2-A43A-4d8f-B76C-6DDA9D9A79F2}][/cover] */
{
  Std_ReturnType RetVal;
  Fls_17_Dmu_StateType  *StatePtr;
  uint32 TimeOutCount;

  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
  uint32 BitChange;


  /* [cover parentID={298F7C2D-0034-46da-884F-6DCAA541C2E6}]
  Is the FLS HW busy ?
  [/cover] */
  if(DMU_HF_STATUS.B.D0BUSY != 1U)
  {
    /* [cover parentID={C6D2B841-80B2-483c-ADD8-EBBE6C3E40F7}]
    Set the Return Value as NOT OK
      [/cover] */
    RetVal = E_NOT_OK;
  }
  /* [cover parentID={1DEF006C-547C-41d2-8D5D-00FAAD8AA2A4}]
  Is system already in suspend mode?
  [/cover] */
  else if(DMU_HF_SUSPEND.B.SPND == 1U)
  {
    /* [cover parentID={F7F96367-68C7-4856-8AC5-3CC6E99A975C}]
      [/cover] */
    RetVal = E_OK;
  }
  else
  {
    #if(FLS_17_DMU_IFX_FEE_USED == STD_OFF)
    #if(FLS_17_DMU_SAFETY_ENABLE == STD_ON)
    #if(FLS_17_DMU_USE_INTERRUPTS == STD_ON)
    /* [cover parentID={1841D68D-D0E3-4553-9CAE-533F69DDD295}]
    [/cover] */
    Fls_17_Dmu_EraseSuspendFlag = FLS_DMU_SUSPEND_STATE;
    #endif
    #endif
    #endif
    BitChange = DMU_HF_SUSPEND.U | IFX_DMU_HF_SUSPEND_REQ_MSK;
    DMU_HF_SUSPEND.U = BitChange;
    TimeOutCount = FLS_17_DMU_ERASESUSPEND_TIMEOUT;
    do
    {
      TimeOutCount-- ;

    /*MISRA2012_RULE_13_5_JUSTIFICATION: No side effects due to order of
    evaluation of SFR declared volatile */
    } while((TimeOutCount > 0U) && (DMU_HF_SUSPEND.B.REQ == 1U));

    /* [cover parentID={1DD2F5F8-0B13-4559-B297-9B42DDE73CFF}]
    Check whether operation timeout occured?
    [/cover] */
    if (TRUE == Fls_lSpndTimeout(TimeOutCount))
    {
      /* [cover parentID={C6D2B841-80B2-483c-ADD8-EBBE6C3E40F7}]
      Set the Return Value as NOT OK
      [/cover] */
      RetVal = E_NOT_OK;
      #if(FLS_17_DMU_IFX_FEE_USED == STD_OFF)
      #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
      #if(FLS_17_DMU_USE_INTERRUPTS == STD_ON)
      Fls_17_Dmu_EraseSuspendFlag = FLS_DMU_SUSPEND_RESET;
      #endif
      #endif
      #endif
    }
    /* [cover parentID={9F5DEB0F-FCCB-4565-A1B4-CB62E07C434A}]
    Is the suspend successful ?
    [/cover] */
    else if(DMU_HF_SUSPEND.B.SPND != 1U)
    {
      /* Clear Suspend Error status */
      BitChange = DMU_HF_SUSPEND.U | SUSPEND_CLR_OFF;
      DMU_HF_SUSPEND.U = BitChange;
      /* [cover parentID={C6D2B841-80B2-483c-ADD8-EBBE6C3E40F7}]
      Set the Return Value as NOT OK
      [/cover] */
      RetVal = E_NOT_OK;
      #if(FLS_17_DMU_IFX_FEE_USED == STD_OFF)
      #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
      #if(FLS_17_DMU_USE_INTERRUPTS == STD_ON)
      Fls_17_Dmu_EraseSuspendFlag = FLS_DMU_SUSPEND_RESET;
      #endif
      #endif
      #endif
    }
    else
    {
      #if (FLS_17_DMU_TIMEOUT_SUPERVISION == STD_ON)
      /*Capture updated erase time after suspending*/
      StatePtr->FlsEraseCmdTimeoutTicks = StatePtr->FlsEraseCmdTimeoutTicks -
      (Mcal_DelayGetTick() - StatePtr->FlsCmdStartTicks);
      #endif
      RetVal = E_OK;
      /* Set job status for the bank to None */
      /* [cover parentID={E0E13B9C-3796-434b-B450-E3B500D4E279}]
                [/cover] */
      StatePtr->FlsJobType = FLS_17_DMU_NONE;
      /* Reset JobStartStatus */
      StatePtr->JobStarted.Erase = 0U;
      /* Set the flash job result to job ok */
      StatePtr->FlsJobResult = MEMIF_JOB_OK;
    }
  }

  return RetVal;
}

/*******************************************************************************
** Traceability :  [cover parentID={0F3EBC6B-A3E5-452f-87AD-3D740F53F2C2}]    **
**                                                                            **
** Syntax : Std_ReturnType Fls_17_Dmu_ResumeErase ()                          **
**                                                                            **
** Service ID: 0x26                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  E_OK - Resume Erase successful                          **
**                    E_NOT_OK - Resume Erase failed                          **
**                                                                            **
** Description :                                                              **
** This function resumes an already suspended erase of a sector.              **
*******************************************************************************/
Std_ReturnType Fls_17_Dmu_ResumeErase (void)
/*[cover parentID={478A22CE-6897-4722-81AB-41264DBC1353}][/cover]*/
{
  Std_ReturnType RetVal;
  Fls_17_Dmu_StateType  *StatePtr;
  uint32 PhysicalAddress;
  uint32 TimeOutCount;
  uint32 BitChange;
  uint32 TimeOutCountInitial;
  uint32 TimeOutResolution;
  uint32 MeasuredTicks;

  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
  RetVal = E_OK;

  /*[cover parentID={76635B72-DC96-4520-80D3-876789189994}][/cover]*/
  if (Fls_lHWBusyCheck() != 0U)
  {
      #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
      /*[cover parentID={7049EBEB-1545-46d3-8306-12138A97FC29}][/cover]*/
      Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_RESUMEERASE, FLS_17_DMU_SE_HW_BUSY);
      #endif
      RetVal = E_NOT_OK;
  }
  /*[cover parentID={CCF7EFC8-2663-4837-B0F2-ED22A94A56BF}][/cover]*/
   else  if(StatePtr->FlsJobType != FLS_17_DMU_NONE)/*Driver Busy*/
  {
      #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
       /*[cover parentID={297B1EFF-5A8C-4d79-A23C-BBCB56B91B6F}][/cover]*/
      Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                             FLS_17_DMU_SID_RESUMEERASE, FLS_17_DMU_SE_BUSY);
      #endif
      RetVal = E_NOT_OK;
  }
  /* [cover parentID={1A1D6B47-4982-474b-A13D-44321A53C4FD}]
     Is suspend bit set?
     [/cover] */
  else if(DMU_HF_SUSPEND.B.SPND == 1U)
  {
      PhysicalAddress = Fls_ConfigPtr->FlsStateVarPtr->FlsEraseAddress;

      Fls_lClearStatusCmdCycle();

      /* Execute the Resume ERASE COMMAND CYCLES */
      /*capture start tick*/
      Fls_lResumeEraseCmdCycle(PhysicalAddress);

      /*Timeout for the resume command to complete*/

      TimeOutResolution = Mcal_DelayTickResolution();
      TimeOutCount = (uint32)FLS_RESUMEERASE_TIMEOUT / TimeOutResolution;
      TimeOutCountInitial = Mcal_DelayGetTick();
      /* [cover parentID={6D6977AB-BA44-4a58-A227-0E9D7FE46D26}]
      If the timeout has not happened and the suspend request bit is
      still set ?
      [/cover] */
      do
      {
        MeasuredTicks = Mcal_DelayGetTick() -  TimeOutCountInitial;

      } while ((DMU_HF_SUSPEND.B.SPND == 1U) && (TimeOutCount > MeasuredTicks));
      /*OPER check*/
      /* [cover parentID={BF4432ED-123D-44e8-8456-C43EDFE797A0}]
       Is the OPER error detected ?
       [/cover] */
      if (0U != Fls_lChkOperError())
      {
        /* [cover parentID={DC4FE44E-4F36-450d-8DCC-300BAB0F1D8E}]
         Raise Resume fail runtime error
         [/cover] */
  #if(FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
        (void)Mcal_Wrapper_Det_ReportRuntimeError((uint16) FLS_17_DMU_MODULE_ID,
            FLS_17_DMU_INSTANCE_ID, FLS_17_DMU_SID_RESUMEERASE,
            FLS_17_DMU_E_RESUME_FAIL);
  #endif
        /* OPER error occured */
        /* [cover parentID={1901C645-1546-472b-9EB4-E9FB9C442D7C}]
         Return Value is NOT OK
         [/cover] */
        RetVal = E_NOT_OK;
      }
      else
      {
        /* [cover parentID={2FD8C463-7825-48fd-B0D8-804643B707DD}]
         Is Sequential / protection error detected?
         [/cover] */
        if(Fls_lChkSeqProtErrors() != 0U)/*SQER check*/
        {
          /* [cover parentID={61A69F77-F379-4ffe-981C-DE61535E9E0C}]
           Send command cycles for resuming the erase for the particular sector
           [/cover] */
          /* Clear the error status flags */
          BitChange = FLS_DMU_ERR_CLR;
          /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
           the object types as the address of the register is being passed.*/
          FLS_17_DMU_SFR_RUNTIME_WRITE32( \
              (volatile uint32 *)&DMU_HF_CLRE.U, BitChange);
    #if(FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
          /* [cover parentID={8A007A35-6F17-4912-92C0-A028FD5823E4}]
           Raise resume fail runtime error.
           [/cover] */
          (void)Mcal_Wrapper_Det_ReportRuntimeError((uint16)FLS_17_DMU_MODULE_ID,
              FLS_17_DMU_INSTANCE_ID,
              FLS_17_DMU_SID_RESUMEERASE,
              FLS_17_DMU_E_RESUME_FAIL);
    #endif
          /* [cover parentID={1901C645-1546-472b-9EB4-E9FB9C442D7C}]
           Return Value is NOT OK
           [/cover] */
          RetVal = E_NOT_OK;
        }
        /*
          Timeout happened then give HW timeout error
        */
        /* [cover parentID={7DAA9B2F-BC8E-4636-BB64-A3CBDF0A51E3}]
        Is the suspend error bit still ON and the timeout has expired?
        [/cover] */
        else if((DMU_HF_SUSPEND.B.SPND == 1U) && (TimeOutCount < MeasuredTicks))
        {
          #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
          /* [cover parentID={D9F1C2B9-8405-4f9f-B05A-6BFC2AAC5B0F}]
          [/cover] */
          Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                          FLS_17_DMU_SID_RESUMEERASE, FLS_17_DMU_SE_HW_TIMEOUT);
          #endif
          /* If timeout happens and Suspend bit is not cleared return E_NOT_OK*/
          /* [cover parentID={1901C645-1546-472b-9EB4-E9FB9C442D7C}]
          Return Value is NOT OK
          [/cover] */
          RetVal = E_NOT_OK;
        }
        else
        {
          /*wait for 100ns for the HW busy bit*/
          TimeOutResolution = Mcal_DelayTickResolution();
          TimeOutCount = (uint32)FLS_17_DMU_HWBUSY_DELAY / TimeOutResolution;
          TimeOutCountInitial = Mcal_DelayGetTick();

          do
          {
            MeasuredTicks = Mcal_DelayGetTick() -  TimeOutCountInitial;

          } while (TimeOutCount > MeasuredTicks);
          #if (FLS_17_DMU_TIMEOUT_SUPERVISION == STD_ON)
          /*Capture initial time-stamp*/
          StatePtr->FlsCmdStartTicks = Mcal_DelayGetTick();
          #endif
          /* [cover parentID={9C73EF56-973D-4403-907E-831D5C8E35BF}]
          [/cover] */
          /* Restore the JobType with previous erase */
          StatePtr->FlsJobType = FLS_17_DMU_ERASE;
          /* 1. Set the flash job result to job pending */
          StatePtr->FlsJobResult = MEMIF_JOB_PENDING;
          /*Indicate that the ERASE Job has been started */
          StatePtr->JobStarted.Erase = 1U;
        }
      }
    }
  else
  {
      /*MISRA*/
  }
  /* [cover parentID={9F1E20BB-946A-4dc8-BB0F-6FEFE559B0D4}]
         [/cover] */
  return RetVal;
}

#endif /* FLS_USE_ERASESUSPEND == STD_ON */

/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax : Std_ReturnType Fls_17_Dmu_GetOperStatus(void)                     **
**                                                                            **
** Service ID: 0x2A                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  E_OK - No OPER error                                    **
**                    E_NOT_OK - OPER error has occurred                      **
**                                                                            **
** Description : This function provides the OPER error status                 **
*******************************************************************************/
Std_ReturnType Fls_17_Dmu_GetOperStatus(void)
/* [cover parentID={284116EC-B6F7-4276-96FE-3AA60587BC9C}][/cover] */
{
  uint32 OPER_Status;
  Std_ReturnType RetVal;

  RetVal = E_OK;

  OPER_Status = ((uint32)DMU_HF_ERRSR.U & IFX_DMU_HF_ERRSR_OPER_MSK);
  /* [cover parentID={08A2FB3E-A953-4d56-9FF2-3290BBF7C42B}]
  Is the oper bit set or operational error detected?
  [/cover] */
  if(0U != OPER_Status)
  {
    /* [cover parentID={EBDAB6DD-A77E-4c14-97FA-5E29E91C977B}]
      [/cover] */
    RetVal = E_NOT_OK;
  }

  return (RetVal);
}

#if(FLS_17_DMU_IFX_FEE_USED == STD_ON)
/*******************************************************************************
** Traceability :  [cover parentID={685AB4B7-A883-439e-9AAD-040235A9CF46}]    **
**                                                                            **
** Syntax : Fls_17_Dmu_HardenType Fls_17_Dmu_IsHardeningRequired(             **
**                    const Fls_17_Dmu_AddressType TargetAddress,             **
**                    const uint8 AlignChk )                                  **
**                                                                            **
** Service ID: 0x2C                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  TargetAddress, AlignChk                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Fls_17_Dmu_HardenType                                   **
**                                                                            **
** Description : The function checks whether the contents of memory at        **
                 requested wordline address needs hardening or not            **
*******************************************************************************/
Fls_17_Dmu_HardenType Fls_17_Dmu_IsHardeningRequired(
  const Fls_17_Dmu_AddressType TargetAddress,
  const uint8 AlignChk)
/* [cover parentID={03D233C8-248E-4bef-9AFC-1AED269BAB08}]
 Service to harden - Fls_17_Dmu_IsHardeningRequired
  [/cover] */
/* [cover parentID={ABEE16D0-CB28-422d-B3CE-FFA63C0990BB}]
Service to harden - Fls_17_Dmu_IsHardeningRequired
[/cover] */
{
  uint8 RetVal;
  uint8 ECCErrorStat;
  uint32 PhysicalAddress;
  uint32 CountDiff, BitChange = 0U, BitRestore;
  uint32 TimeOutType;
  uint32 TimeOutCount;
  uint32 TimeOutCountInitial;
  uint32 TimeOutResolution;
  uint32 MeasuredTicks;
  uint32 OperStatusChk;

  #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={2F60A417-B321-452d-9828-F080219483C6}]
  Is range check of parameters OK ?
  [/cover] */
  if((Fls_lHardenSafetyChk(TargetAddress, AlignChk))
      == FLS_17_DMU_HARDENCHK_ERROR)
  {
    /* [cover parentID={A8C5F3FD-4A78-4e1f-A862-8A4B584C1B23}]
     [/cover] */
    RetVal = FLS_17_DMU_HARDENCHK_ERROR;
  }
  else
  #endif
  {
    PhysicalAddress = FLS_17_DMU_BASE_ADDRESS + TargetAddress;

    /* Set the control gate voltage to 4.1V before executing the command */

    FSI_COMM_1.B.COMM1 = FLS_CTRLGATEVOLTAGE_VAL;

    BitRestore = DMU_HF_CONTROL.U;

    /* [cover parentID={5FB58FDC-269F-4aa8-BC84-A530319AF796}]
    Check is the hardening needed pagewise ?
    [/cover] */
    if(FLS_17_DMU_PAGE_HARDEN == AlignChk)
    {
      /* [cover parentID={4D174B2B-4FA5-45da-8586-E587142F0972}]
      Set the FLS alignment set the timeout to pagewise.
      [/cover] */
      BitChange = ((uint32)DMU_HF_CONTROL.U | FLS_DMU_HARDEN_PAGE_ALIGN);
      TimeOutType = (uint32)FLS_USRCONTENT_PAGE_TIMEOUT;
    }
    else
    {
      /* [cover parentID={B61B5C3F-5B51-4fcb-A58E-7F545DC2E4D1}]
            [/cover] */
      BitChange = ((uint32)DMU_HF_CONTROL.U & FLS_DMU_HARDEN_WORD_ALIGN);
      TimeOutType = (uint32)FLS_USRCONTENT_WL_TIMEOUT;
    }

    FLS_17_DMU_LIB_RUNTIME_WRITEPERIPENDINITPROTREG(&DMU_HF_CONTROL.U,
        BitChange);

    Fls_lClearStatusCmdCycle();

    /* Execute the user content count command sequence */
    Fls_lUserContentCountCmdCycle(PhysicalAddress);

    /*Wait for 20us*/
    TimeOutResolution = Mcal_DelayTickResolution();
    TimeOutCount =  TimeOutType / TimeOutResolution;
    TimeOutCountInitial = Mcal_DelayGetTick();
    /* [cover parentID={E3928CF4-13A0-4f20-BC80-4F8319B12355}]
    Is the HW busy or OPER bit is set or timeout occurred?
    [/cover] */
    do
    {
      MeasuredTicks = Mcal_DelayGetTick() -  TimeOutCountInitial;
      OperStatusChk = ((uint32)DMU_HF_ERRSR.U & FLS_OPER_ERROR);

    } while ((Fls_lHWBusyCheck() != 0U) && (OperStatusChk != 1U)
          && (TimeOutCount > MeasuredTicks));


    /* [cover parentID={8F6A889D-037E-482d-835F-7CEDCC8D75DA}]
    OPER error present ?
    [/cover] */
    if(Fls_lChkOperError() != 0U) /*Check for OPER*/
    {
      /*Harden fail due to OPER error*/
      RetVal = FLS_17_DMU_HARDENCHK_ERROR;

      #if(FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
      /* [cover parentID={4FF2F271-1FF0-4d39-BEAD-C78031C572BE}]
            [/cover] */
      (void)Mcal_Wrapper_Det_ReportRuntimeError((uint16)FLS_17_DMU_MODULE_ID,
                             FLS_17_DMU_INSTANCE_ID,
                             FLS_17_DMU_SID_ISHARDENINGREQ,
                             FLS_17_DMU_E_HARDENCHK_FAIL);
      #endif
    }

    /* [cover parentID={EEAA2EA6-E945-4c61-AB6F-70D4175BC75C}]
    Sequence or Protection Error present ?
    [/cover] */
    else if (Fls_lChkSeqProtErrors() != 0U)
    {
      RetVal = FLS_17_DMU_HARDENCHK_ERROR;
      /*Clear the SQER/PVER/EVER error*/
      BitChange = FLS_DMU_ERR_CLR;
      /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
       the object types as the address of the register is being passed.*/
      FLS_17_DMU_SFR_RUNTIME_WRITE32( \
                                      (volatile uint32 *)&DMU_HF_CLRE.U, \
                                      BitChange);

      #if(FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)

      /* [cover parentID={4FF2F271-1FF0-4d39-BEAD-C78031C572BE}]
      [/cover] */
      (void)Mcal_Wrapper_Det_ReportRuntimeError((uint16)FLS_17_DMU_MODULE_ID,
                             FLS_17_DMU_INSTANCE_ID,
                             FLS_17_DMU_SID_ISHARDENINGREQ,
                             FLS_17_DMU_E_HARDENCHK_FAIL);
      #endif
    }
    /* [cover parentID={973362DB-D403-4269-9835-968C04555ED8}]
                [/cover] */
    else if((Fls_lHWBusyCheck() != 0U) && (TimeOutCount <= MeasuredTicks))
    {
      #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)

      /* [cover parentID={E2F7CB76-D4E4-48df-95C4-753AEB8DFA68}]
                [/cover] */
      Mcal_ReportSafetyError((uint16)FLS_17_DMU_MODULE_ID,
                             FLS_17_DMU_INSTANCE_ID,
                             FLS_17_DMU_SID_ISHARDENINGREQ,
                             FLS_17_DMU_SE_HW_TIMEOUT);
      #endif

      /* [cover parentID={9A20550F-33FA-42fa-A9E3-88B3F976B128}]
          [/cover] */
      RetVal = FLS_17_DMU_HARDENCHK_ERROR;
    }
    else
    {
      /* [cover parentID={425BF8CF-FBBA-46cc-A02D-773F6908768C}]
      [/cover] */
      /* Result (Difference in count of '1' bits) is returned as 13-bit unsigned
          integer with bits [7:0] in FSI_COMM_1.COMM1[7:0] and bits [12:8] in
          FSI_COMM_2.COMM2[4:0]. Ordering of the information is done and
          stored in CountDiff*/
      /* [cover parentID={6C804F97-3744-42d8-89E8-0845DA77B8D3}]
      [/cover] */
      CountDiff = FSI_COMM_2.B.COMM2;

      CountDiff = (CountDiff & FLS_FSICOMM2RES_MASK) << FLS_SHIFT8BITS_VAL;


      CountDiff |= FSI_COMM_1.B.COMM1;

      /* Obtain the TBE (3 bit error) status after the command execution */

      ECCErrorStat = FSI_COMM_2.B.COMM2 & FLS_COMM2TBE_MASK;

      /* Hardening is required either if there is a difference in number of
         '1'-bits with tight margin for 0-level and the number of '1'-bits with
         tight margin for 1-level or with 3-bit ECC errors */
      /* [cover parentID={A68072CC-35A4-450c-A40E-B139549FDBD5}]
      Is target adress page aligned AND obtained count difference of
      hardening greater than one ?
      [/cover] */
      if ((CountDiff > 1U) && (FLS_17_DMU_PAGE_HARDEN == AlignChk))
      {
        /* [cover parentID={F0F63CEF-8914-4cda-BDDD-A94E32E6CBF9}]
        [/cover] */
        RetVal = FLS_17_DMU_HARDENCHK_REQRD;
      }
      /* [cover parentID={4DD7EE14-BCCC-4d92-ABE4-8E363F8DF223}]
      is the target address given for hardening word aligned AND the obtained
      count difference greater than 2 ?
      [/cover] */
      else if((CountDiff > 2U) && (FLS_17_DMU_WORDLINE_HARDEN == AlignChk))
      {
        /* [cover parentID={F0F63CEF-8914-4cda-BDDD-A94E32E6CBF9}]
               [/cover] */
        RetVal = FLS_17_DMU_HARDENCHK_REQRD;
      }
      /* [cover parentID={610BB82D-23D8-44c9-B9E6-9D20FD04486B}]
      Is there a triple bit error?
      [/cover] */
      else if(ECCErrorStat != 0U)
      {
        /* [cover parentID={F0F63CEF-8914-4cda-BDDD-A94E32E6CBF9}]
               [/cover] */
        RetVal = FLS_17_DMU_HARDENCHK_REQRD;
      }
      else
      {
        /* [cover parentID={CC5CE357-72E4-432c-9502-3BE98313054C}]
              [/cover] */
        RetVal = FLS_17_DMU_HARDENCHK_NOTREQD;
      }

      /*Clear the page alignment to restore the previous status so that other
       operations are not affected*/
      FLS_17_DMU_LIB_RUNTIME_WRITEPERIPENDINITPROTREG(&DMU_HF_CONTROL.U,
          BitRestore);

      /*Reset the COMM1 and COMM2 values to system reset values*/
      FSI_COMM_1.U = FLS_COMM_RESET_VAL;
      FSI_COMM_2.U = FLS_COMM_RESET_VAL;

    } /*timeout, SQER, PROER*/

  } /*Range Check is OK*/

  return (RetVal);
}


#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
/*******************************************************************************
** Traceability :  [cover parentID={DECD5BE2-41EA-45d4-8242-0388F4E97A67}]    **
**                                                                            **
** Syntax : LOCAL_INLINE uint8 Fls_lHardenSafetyChk(const                     **
**              Fls_17_Dmu_AddressType TargetAddress, const uint8 AlignChk)   **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  TargetAddress, AlignChk                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Fls_17_Dmu_HardenType                                   **
**                                                                            **
** Description : This function which will do the safety  and                  **
                 range check for the Fls_17_Dmu_IsHardeningRequired()         **
*******************************************************************************/
LOCAL_INLINE uint8 Fls_lHardenSafetyChk(
  const Fls_17_Dmu_AddressType TargetAddress, const uint8 AlignChk)
{
  uint8 RetVal;
  const Fls_17_Dmu_StateType  *StatePtr;
  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
  RetVal = FLS_17_DMU_HARDENCHK_NOTREQD;
  /*Check the Target Address*/
  /* [cover parentID={82D4778A-D3D0-4bd8-B508-7A3CF26327A4}]
  Is the target address within valid FLS range ?
  [/cover] */
  if(((uint32)TargetAddress) >= FLS_17_DMU_TOTAL_SIZE)
  {

    /* [cover parentID={670E38DF-44BF-4d75-BC89-E7533AFD4B9E}]
      [/cover] */
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                  FLS_17_DMU_SID_ISHARDENINGREQ, FLS_17_DMU_SE_PARAM_ADDRESS);

    RetVal = FLS_17_DMU_HARDENCHK_ERROR;
  }
  /* [cover parentID={5DCA9A77-B8BB-4d8b-BB40-7B32A1C9B225}]
  Is the alignment of the address correct as per the AlignChk parameter(another
  parameter in the function) ?
  [/cover] */
  else if(((FLS_17_DMU_WORDLINE_HARDEN == AlignChk) &&
           ((TargetAddress & FLS_WL_SIZE_MASK) != 0U)) ||
          ((FLS_17_DMU_PAGE_HARDEN == AlignChk) &&
           ((TargetAddress & FLS_PAGE_SIZE_MASK) != 0U)))
  {
    /* [cover parentID={670E38DF-44BF-4d75-BC89-E7533AFD4B9E}]
            [/cover] */
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                  FLS_17_DMU_SID_ISHARDENINGREQ, FLS_17_DMU_SE_PARAM_ADDRESS);
    RetVal = FLS_17_DMU_HARDENCHK_ERROR;
  }
  /* [cover parentID={3338857C-4FC3-4708-91FA-F0533151005E}]
  Is the value of the AlignChk parameter valid ?
  [/cover] */
  else if((FLS_17_DMU_WORDLINE_HARDEN != AlignChk) &&
          (FLS_17_DMU_PAGE_HARDEN != AlignChk))
  {
    /* [cover parentID={670E38DF-44BF-4d75-BC89-E7533AFD4B9E}]
            [/cover] */
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                  FLS_17_DMU_SID_ISHARDENINGREQ, FLS_17_DMU_SE_PARAM_INVLD);
    RetVal = FLS_17_DMU_HARDENCHK_ERROR;
  }
  /* [cover parentID={87BA5140-9EC1-443d-B45E-5BC7E32DCD18}]
  Is the FLS HW busy ?
  [/cover] */
  else if(Fls_lHWBusyCheck() != 0U)/*HW Busy check*/
  {
    /* [cover parentID={670E38DF-44BF-4d75-BC89-E7533AFD4B9E}]
            [/cover] */
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                      FLS_17_DMU_SID_ISHARDENINGREQ, FLS_17_DMU_SE_HW_BUSY);
    RetVal = FLS_17_DMU_HARDENCHK_ERROR;
  }
  /* [cover parentID={F0068116-161F-426c-8622-A8AAE08A64D6}]
  Is the FLS driver busy ?
  [/cover] */
  else  if(StatePtr->FlsJobType != FLS_17_DMU_NONE)/*Driver Busy*/
  {
    /* [cover parentID={670E38DF-44BF-4d75-BC89-E7533AFD4B9E}]
            [/cover] */
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                       FLS_17_DMU_SID_ISHARDENINGREQ, FLS_17_DMU_SE_BUSY);
    RetVal = FLS_17_DMU_HARDENCHK_ERROR;
  }
  else
  {
    /*MISRA*/
  }

  return(RetVal);
}
#endif
#endif


/*******************************************************************************
** Traceability   : [cover parentID={37415CD4-E15C-4510-A1CC-22A5D72046F3}]   **
**                                                                            **
** Syntax : static void Fls_lMainErase(void)                                  **
**                                                                            **
** Service ID:  None                                                          **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non-reentrant                                                 **
**                                                                            **
** Parameters (in) : void                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : Performs the erase operation during Interrupt/Cyclic         **
**               Job handling                                                 **
*******************************************************************************/
static void Fls_lMainErase(void)
/* [cover parentID={181AB1EF-DB67-46a2-BAE9-430B0D0E4DFB}]
Fls_lMainErase
[/cover] */
{
  Fls_17_Dmu_StateType       *StatePtr;
  MemIf_JobResultType LastJobResult;
  uint32     PhysicalAddress;
  uint32     EraseSizeBytesPerCmd;
  Std_ReturnType      RetVal;
  uint32 BitChange;


  /******************* Initialise the local variables ***************/
  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;


  /* Sector erase size in bytes per Erase command ; 1 logical sector = 4K*/
  /* MISRA2012_RULE_10_8_JUSTIFICATION: It is ensured that no truncation or
  loss of information is resulted from this cast.*/
  EraseSizeBytesPerCmd = (uint32)((uint16)(StatePtr->FlsEraseNumSecPerCmd) << \
                                  (uint8)FLS_4KSHIFT_VAL);

  /* Erase job has already been started */
  /* [cover parentID={7FD2CA56-A3EA-448a-8D38-03EE5884BF39}]
  Is operational error present?
  [/cover] */
  if(Fls_lChkOperError() != 0U) /* Check for operational error */
  {
    /* [cover parentID={92139929-5540-4453-A4A1-99337173A05E}]
    Report erase error (RTE/Transient) according to Autosar version
    [/cover] */
    #if(MCAL_AR_VERSION == MCAL_AR_440)
    (void)Det_ReportTransientFault( (uint16)FLS_17_DMU_MODULE_ID,
                            FLS_17_DMU_INSTANCE_ID,
                            FLS_17_DMU_SID_MAIN,
                            FLS_17_DMU_E_ERASE_FAILED);
    #else
      #if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
      /* Report Runtime error code to Mcal_Wrapper */
      (void)Mcal_Wrapper_Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                            FLS_17_DMU_INSTANCE_ID,
                            FLS_17_DMU_SID_MAIN,
                            FLS_17_DMU_E_ERASE_FAILED);
      #endif
    #endif
    /* Call Fls_lErrorHandler local function */
    /* [cover parentID={0FF9C214-3F2F-4405-8B4F-E0468E8691B8}]
    Call error handler function
    [/cover] */
    Fls_lErrorHandler(FLS_17_DMU_ERASE);

    /* [cover parentID={234A9B4E-AAB9-4095-A13A-01049F15F821}]
    Set return value as NOT OK
    [/cover] */
    RetVal = E_NOT_OK;
  }
  /* [cover parentID={5B6995C2-C363-4360-8427-E769BECEC555}]
  Is the EVER error present ?
  [/cover] */
  else if(DMU_HF_ERRSR.B.EVER != 0U)
  {
    #if ( FLS_17_DMU_IFX_FEE_USED ==  STD_OFF )
      #if(MCAL_AR_VERSION == MCAL_AR_440)
      (void)Det_ReportTransientFault( (uint16)FLS_17_DMU_MODULE_ID,
                              FLS_17_DMU_INSTANCE_ID,
                              FLS_17_DMU_SID_MAIN,
                              FLS_17_DMU_E_ERASE_FAILED);
        #if (FLS_17_DMU_ERASE_VERIFY_REPORT == STD_ON)
        /* Report Runtime error code to Mcal_Wrapper */
        (void)Mcal_Wrapper_Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                              FLS_17_DMU_INSTANCE_ID,
                              FLS_17_DMU_SID_MAIN,
                              FLS_17_DMU_E_VERIFY_ERASE_FAILED);
        #endif
      #else
      #if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) || \
      (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
      /* [cover parentID={C5713918-B847-4c0b-B964-DB1EE2F55D3A}][/cover] */
      Fls_lReportError(FLS_17_DMU_SID_MAIN,FLS_17_DMU_E_VERIFY_ERASE_FAILED);
      #endif
      #if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
      (void)Mcal_Wrapper_Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID, \
         FLS_17_DMU_INSTANCE_ID,FLS_17_DMU_SID_MAIN, FLS_17_DMU_E_ERASE_FAILED);
      #endif
      #endif
      /* [cover parentID={B2C72E86-FA45-4cfb-AFC7-F7EF1B442209}]
      Call error handler and set error flag as E_NOT_OK
      [/cover] */
      Fls_lErrorHandler(FLS_17_DMU_ERASE);
      RetVal = E_NOT_OK;
    #else
    /* [cover parentID={DC6E6DBA-DB98-43b3-840F-3A20DB0FE5D8}]
    Is the EVER Flag set ?
    [/cover] */
    if (StatePtr->FlsEver == 0U)
    {
      StatePtr->FlsEver = FLS_EVER_CHK;
      RetVal = E_OK;
    }
    else
    {
      /* [cover parentID={41FA5459-0C7A-46df-AE66-294AD36850EE}]
      Report erase error (DET/Safety/RTE/Transient) according to Autosar
      version [/cover] */
      #if(MCAL_AR_VERSION == MCAL_AR_440)
      (void)Det_ReportTransientFault( (uint16)FLS_17_DMU_MODULE_ID,
                              FLS_17_DMU_INSTANCE_ID,
                              FLS_17_DMU_SID_MAIN,
                              FLS_17_DMU_E_ERASE_FAILED);
        #if (FLS_17_DMU_ERASE_VERIFY_REPORT == STD_ON)
        /* Report Runtime error code to Mcal_Wrapper */
        (void)Mcal_Wrapper_Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                              FLS_17_DMU_INSTANCE_ID,
                              FLS_17_DMU_SID_MAIN,
                              FLS_17_DMU_E_VERIFY_ERASE_FAILED);
        #endif
      #else
      #if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) || \
      (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
      /* [cover parentID={C5713918-B847-4c0b-B964-DB1EE2F55D3A}][/cover] */
      Fls_lReportError(FLS_17_DMU_SID_MAIN,FLS_17_DMU_E_VERIFY_ERASE_FAILED);
      #endif
      #if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
      (void)Mcal_Wrapper_Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
         FLS_17_DMU_INSTANCE_ID,FLS_17_DMU_SID_MAIN, FLS_17_DMU_E_ERASE_FAILED);
      #endif
      #endif
      /* [cover parentID={13875837-D4F9-43c7-B6CA-04698E303A42}]
      Call Fls_lEverFlagChkFail
      [/cover] */
      Fls_lEverFlagChkFail();
      /* [cover parentID={A9ABB334-54A0-49a6-B6EC-FC17604A7A08}][/cover] */
      RetVal = E_NOT_OK;
    }
    #endif
  }
  else
  {
    RetVal = E_OK;
  }
/* [cover parentID={9C869C68-F488-4cb9-BF8D-B95FE9479333}][/cover] */
  if(RetVal == E_OK)
  {
    /* [cover parentID={3C653B10-4DC8-4ee3-9472-6660DD525CB1}]
    1) Goto the next erase address
    2) Decrement the number of sectors to be erased
    [/cover] */
    /* Calculate the latest address to be erased */
    StatePtr->FlsEraseAddress += EraseSizeBytesPerCmd;
    /* Calcualte the remaining sectors to be erased*/
    StatePtr->FlsEraseNumSectors -= StatePtr->FlsEraseNumSecPerCmd ;
    /* Check if number of sectors to be erased can be accomodated in 1 erase
      command cycle; If not seal the number of sectors to be erased to
      recommended value 64 */
    /* [cover parentID={C40B99A0-C4C1-4885-9831-A704AE271C15}]
    Is the number of sectors to be erased greater than the configured max
    sector value ?
    [/cover] */
    if (StatePtr->FlsEraseNumSectors > FLS_MAXERASE_SEC)
    {
      /* [cover parentID={C55FE0CA-2B6A-45ff-BB0D-2B30EED09B95}]
          [/cover] */
      StatePtr->FlsEraseNumSecPerCmd = (uint8)FLS_MAXERASE_SEC;
    }
    else
    {
      /* [cover parentID={0B8CC455-EFC9-4182-AC24-CDF5FB71C4C6}]
                  [/cover] */
      StatePtr->FlsEraseNumSecPerCmd = (uint8)StatePtr->FlsEraseNumSectors;
    }
    /* [cover parentID={03EBBA09-1B63-4561-AF01-A74538226915}]
    Are there any remaining sectors to be erase ?
    [/cover] */
    if(StatePtr->FlsEraseNumSectors != 0U)
    {
      /* [cover parentID={422871A3-7C24-4cd0-982D-8CCFACE10C29}]
      Read the erase address
      [/cover] */
      /* Obtain the physical address for the erase operation */
      PhysicalAddress = StatePtr->FlsEraseAddress;
      /* Start Erase operation */
      Fls_lMainEraseJobStart(PhysicalAddress);
    }
    else /* Job completed successfully */
    {
      #if ( FLS_17_DMU_IFX_FEE_USED ==  STD_ON )
      /* [cover parentID={F068704D-64CE-47a8-BA5C-A2F2C62DC0C4}]
      Is the FLS EVER Flag already set ?
      [/cover] */
      if(StatePtr->FlsEver != FLS_EVER_CHK)
      #endif
      {
        /* Set to JOB_OK if no warnings  */
        LastJobResult = MEMIF_JOB_OK;
      /* [cover parentID={2CF252A9-99C5-4e92-8042-09C1F99C0BBE}][/cover] */
        /* clear the HW error status flags */
        BitChange = FLS_DMU_ERR_CLR;
        /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
         the object types as the address of the register is being passed.*/
        FLS_17_DMU_SFR_RUNTIME_WRITE32( \
                                        (volatile uint32 *)&DMU_HF_CLRE.U, \
                                        BitChange);

        /* [cover parentID={DBBA1F9E-4542-4095-9B8F-77592D851CBA}]
        Is the Job End notification call back configured ?
        [/cover] */
        if(Fls_ConfigPtr->FlsJobEndNotificationPtr != NULL_PTR)
        {
          /* [cover parentID={3342180D-4E97-40f2-868F-A5B6D5309FF8}]
          Set the notification flag to FLS_ERASE job
          [/cover] */
          Fls_ConfigPtr->FlsStateVarPtr->NotifCaller =
            FLS_17_DMU_ERASE_JOB;
          /* FlsJobEndNotificationPtr should be called */
          /* [cover parentID={EAFDF5B9-B692-4d24-A25F-7B3CCFB27C30}]
          Call Job End Notification
          [/cover] */
          (Fls_ConfigPtr->FlsJobEndNotificationPtr)();
          Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_NO_JOB;
        }

        /* Update the global status variables */
        /* [cover parentID={6276B6E9-7B22-4a9c-B020-B8541EC537F1}]
                  [/cover] */
        StatePtr->FlsJobResult = LastJobResult;
        /* Clear the Erase Job */
        StatePtr->FlsJobType = FLS_17_DMU_NONE;
        /* Clear JobStarted bit for operation JobType */
        StatePtr->JobStarted.Erase = 0U;
      }/*If the EVER flag is not set*/
      #if ( FLS_17_DMU_IFX_FEE_USED ==  STD_ON )
      else
      {
        /* [cover parentID={49F204F9-C922-4f8e-9ED3-FBD44CEAA0A1}]
        Report erase error (DET/Safety/RTE/Transient) according to Autosar
        version [/cover] */
        #if(MCAL_AR_VERSION == MCAL_AR_440)
        (void)Det_ReportTransientFault( (uint16)FLS_17_DMU_MODULE_ID,
                                FLS_17_DMU_INSTANCE_ID,
                                FLS_17_DMU_SID_MAIN,
                                FLS_17_DMU_E_ERASE_FAILED);
          #if (FLS_17_DMU_ERASE_VERIFY_REPORT == STD_ON)
          /* Report Runtime error code to Mcal_Wrapper */
          (void)Mcal_Wrapper_Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                                FLS_17_DMU_INSTANCE_ID,
                                FLS_17_DMU_SID_MAIN,
                                FLS_17_DMU_E_VERIFY_ERASE_FAILED);
          #endif
        #else
        #if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) || \
        (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
        /* [cover parentID={C5713918-B847-4c0b-B964-DB1EE2F55D3A}][/cover] */
        Fls_lReportError(FLS_17_DMU_SID_MAIN,FLS_17_DMU_E_VERIFY_ERASE_FAILED);
        #endif
        #if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
        (void)Mcal_Wrapper_Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
        FLS_17_DMU_INSTANCE_ID, FLS_17_DMU_SID_MAIN, FLS_17_DMU_E_ERASE_FAILED);

        #endif
        #endif
        /* [cover parentID={8EFFF9CE-A174-4395-AFF9-B23CAE396F92}]
        Raise erase verify error notification and clear all errors
        [/cover] */
        Fls_lEverFlagChkFail();
      }
      #endif
    }/* End of Job evaluation */
  }
}

/*******************************************************************************
** Traceability :[cover parentID={2C50AC81-E6FE-45bc-BF8D-827C0A73DFF5}]      **
**                                                                            **
** Syntax : static void Fls_lEverFlagChkFail(void)                            **
**                                                                            **
** Service ID:  None                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non-reentrant                                                 **
**                                                                            **
** Parameters (in) : void                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : Performs the erase operation during Interrupt/Cyclic         **
**               Job handling                                                 **
*******************************************************************************/
#if (FLS_17_DMU_IFX_FEE_USED == STD_ON)
static void Fls_lEverFlagChkFail(void)
{
  /* MISRA2012_RULE_8_13_JUSTIFICATION: pointer is updated
     so it is not declared const. */
  Fls_17_Dmu_StateType       *StatePtr;
  uint32 BitChange;

  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;

  StatePtr->JobStarted.Erase = 0U;

  /* Clear the failed Job  */
  StatePtr->FlsJobType = FLS_17_DMU_NONE;

  /* Update the global status variables */
  StatePtr->FlsJobResult = MEMIF_JOB_FAILED;

  /* [cover parentID={92E5E059-9F0A-428b-84EA-BA64D4CDAA49}]
  Is the Fls EraseVerify notification callback configured ?
  [/cover] */
  if(Fls_ConfigPtr->FlsEraseVerifyErrNotifPtr != NULL_PTR)
  {
    Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_ERASE_JOB;

    /* Fls EVER Notification should be called */
    /* [cover parentID={2112CED0-011E-409d-861B-50ED1933B545}]
    Call the Fls Erase Verify Error notification
    [/cover] */
    (Fls_ConfigPtr->FlsEraseVerifyErrNotifPtr)();
    Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_NO_JOB;
  }

  /* [cover parentID={B2B4C82D-148A-47b3-9F6D-D2A7E4003D7D}]
      [/cover] */
  StatePtr->FlsEver = (uint8)0x00;

  /*Clear EVER error*/
  BitChange = FLS_DMU_ERR_CLR;
  /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
   the object types as the address of the register is being passed.*/
  FLS_17_DMU_SFR_RUNTIME_WRITE32( \
                                  (volatile uint32 *)&DMU_HF_CLRE.U, \
                                  BitChange);
}
#endif
/*******************************************************************************
** Traceability   : [cover parentID={90851DBD-548F-4112-A993-66C3FE35A4F0}]   **
**                                                                            **
** Syntax : static void Fls_lMainEraseJobStart(const uint32 PhysicalAddress)  **
**                                                                            **
** Service ID:  None                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non-reentrant                                                 **
**                                                                            **
** Parameters (in) : Physical Address - Physical address for Erase            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : Performs the erase operation during Interrupt/Cyclic         **
**               Job handling                                                 **
*******************************************************************************/
static void Fls_lMainEraseJobStart(const uint32 PhysicalAddress)
{
  Fls_17_Dmu_StateType   *StatePtr;
  uint32                  SeqProtErr;

  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;

  /* Indicate that the ERASE Job has been started */
  StatePtr->JobStarted.Erase = 1U;

  /* [cover parentID={89F777C5-EE77-4f9b-A44E-D82F5A75D7B6}]
  Clear all error status flags
  [/cover] */
  Fls_lClearStatusCmdCycle();
  /* Initiate erase command */
  Fls_lCallEraseCommand(PhysicalAddress);
  /* Check for Sequence error,Protection error bit */
  SeqProtErr = Fls_lChkSeqProtErrors();
  /* [cover parentID={0110F23D-ED1B-43e2-BD5D-5B94EBD9917E}]
  Is sequence / protection error detected?
  [/cover] */
  if(SeqProtErr != 0U)
  {
    /* [cover parentID={AA669A0E-FB3D-4d85-BE77-ED7B51FA54F5}]
    Report erase error (Runtime/transient fault) according to the Autosar
    version [/cover] */
    /* [cover parentID={AA669A0E-FB3D-4d85-BE77-ED7B51FA54F5}]
    [/cover] */
    /* Report Transient fault */
    #if(MCAL_AR_VERSION == MCAL_AR_440)
    (void)Det_ReportTransientFault( (uint16)FLS_17_DMU_MODULE_ID,
                            FLS_17_DMU_INSTANCE_ID,
                            FLS_17_DMU_SID_MAIN,
                            FLS_17_DMU_E_ERASE_FAILED);
    #else
      #if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
      /* [cover parentID={9CB1C431-D13A-4394-B485-B935377A22CA}]
      Report runtime Error
      [/cover] */
      (void)Mcal_Wrapper_Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                            FLS_17_DMU_INSTANCE_ID,
                            FLS_17_DMU_SID_MAIN,
                            FLS_17_DMU_E_ERASE_FAILED);
      #endif
    #endif
    /* [cover parentID={87AD13DF-DDF8-4cbf-B05E-EB8DF78D95F6}]
    Call error handler
    [/cover] */
    /* Call to Fls_lErrorHandler local function */
    Fls_lErrorHandler(FLS_17_DMU_ERASE);
  }
  /* Check for command cycle Timeout */
  /* [cover parentID={EA55CAD0-EEAF-4cc2-BE0A-8C322D2F7DF3}]
  Is there a command cycle timeout?
  [/cover] */
  else if (StatePtr->FlsTimeoutErr == FLS_17_DMU_ERASE)
  {
    /* [cover parentID={318E04D6-BFF5-4ffd-9039-22B583F11AF3}]
    Report erase error (Runtime/transient fault) according to the Autosar
    version [/cover] */
    #if(MCAL_AR_VERSION == MCAL_AR_440)
    (void)Det_ReportTransientFault( (uint16)FLS_17_DMU_MODULE_ID,
                            FLS_17_DMU_INSTANCE_ID,
                            FLS_17_DMU_SID_MAIN,
                            FLS_17_DMU_E_ERASE_FAILED);
    #else
      #if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
      /* [cover parentID={9CB1C431-D13A-4394-B485-B935377A22CA}]
      Report runtime Error
      [/cover] */
      (void)Mcal_Wrapper_Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                            FLS_17_DMU_INSTANCE_ID,
                            FLS_17_DMU_SID_MAIN,
                            FLS_17_DMU_E_ERASE_FAILED);
      #endif
    #endif
    /* Call Fls_lErrorHandler local function */
    /* [cover parentID={50FFF2FA-5BE1-47ee-9D53-8F56B149CCC4}]
    Call  error handler
    [/cover] */
    Fls_lErrorHandler(FLS_17_DMU_ERASE);
  }
  else
  {
    /* dummy else */
  }
}

/*******************************************************************************
** Traceability :[cover parentID={F4367CF1-D6D3-45b3-BA3C-377009141D20}]      **
**                                                                            **
** Syntax : static void Fls_lMainRead(void)                                   **
**                                                                            **
** Service ID:  None                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non-reentrant                                                 **
**                                                                            **
** Parameters (in) : void                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : Performs the Read operation during Interrupt/Cyclic          **
**               Job handling                                                 **
*******************************************************************************/
static void Fls_lMainRead(void)
{
  Fls_17_Dmu_StateType *StatePtr;
  Fls_17_Dmu_LengthType ReadCount;
  MemIf_JobResultType LastJobResult;
  const uint64 *SourcePtr;
  uint64 PageData;
  uint8 *PagePtr;
  uint32 PageOffset;
  Fls_17_Dmu_LengthType MaxRead;
  #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_OFF)
  uint32 BitChange;
  #endif
  #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_ON)
  uint32 EccErrorFlag = 0U;
  #endif
  /************* Initialise Local Variables *****************************/
  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
  uint32 ErrorFlag = 0U;
  uint32 PageBytes = 0U;
  /* Get max read length according to the FLS mode */
  MaxRead = Fls_lGetReadModeLength();

  /* Check whether the given length is greater than MAX_READ */
  /* [cover parentID={271C1C18-3467-4145-B264-4EFACFF82720}]
  Is the given length greater than flash read mode length?
  [/cover] */
  if(StatePtr->FlsReadLength > MaxRead)
  {
    /* [cover parentID={5FB65A2C-AD56-45b9-8C4E-8FEB776CF8C5}]
    1 Load upto maximum byte to read in one cycle
    2 Decreament in the readcount from the read length
    [/cover] */
    /* Load Max Byte to read in one cycle */
    ReadCount = MaxRead;
    /* Decrement the count from the total count to read */
    StatePtr->FlsReadLength = StatePtr->FlsReadLength - ReadCount;
  }
  else
  {

    /* [cover parentID={176EE95B-66BD-4ef7-8912-D2DC766AC7DC}]
        [/cover] */
    ReadCount = StatePtr->FlsReadLength;
    StatePtr->FlsReadLength = 0U;
  }
  #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_OFF)
  /*Clear the ECC status bits by writing DMU_HF_ECCC.CLR with 11b to clear
       AERM bit*/
  BitChange = DMU_HF_ECCC.U | FLS_DMU_ECCC_CLR;

  /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
   the object types as the address of the register is being passed.*/
  FLS_17_DMU_LIB_RUNTIME_WRITEPERIPENDINITPROTREG(\
      (volatile uint32 *)&DMU_HF_ECCC.U, \
      BitChange);
  /*There is a delay of 2-3 cycles in the setting of AERM bit*/
  NOP();
  NOP();
  NOP();
  #endif
  /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from uint32 to uint64* is required
  to access the FLASH address for data buffer alignment and store it in pointer
  for easy arithmetic operations. No memory alignment issues.*/
  /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from uint32 to uint64*
  type is required to access the FLASH address/target address and store it in
  pointer for easy arithmetic operations. No memory alignment issues.*/
  SourcePtr = (uint64*)Fls_lGetPageAddress(StatePtr->FlsReadAddress);
  PageOffset = (StatePtr->FlsReadAddress & FLS_PAGE_SIZE_MASK);
  PageBytes = (FLS_17_DMU_PAGE_SIZE - PageOffset);
  PageData = (*SourcePtr);
  /* DSYNC() is added to avoid compiler optimization (re-ordering of DFlash
  read and ECC error check in Fls_lChkBitErrors())*/
  DSYNC();
  /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
  PageData is used inside Fls_lMainRead() local function to
  read the values. The address is not used beyond the context of the
  function, hence it is not an issue*/
  PagePtr = (uint8*)(&PageData);
  PagePtr = &PagePtr[PageOffset];
  #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_ON)
  EccErrorFlag = Fls_lChkBitErrors();
  /* [cover parentID={1708DD65-4B6A-4d58-B36C-DDA701EB5177}]
  ECC error occurred?
  [/cover] */
  if(EccErrorFlag != 0U)
  {
    ErrorFlag = 1U;
    /* update page addr*/
    /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from pointer to uint32
    is required to store the FLASH address/target address in state var
    structure. No memory alignment issues.*/
    /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from pointer to uint32
    type is required to access the FLASH address and store it in state var
    structure. No memory alignment issues.*/
    StatePtr-> FlsEccErrorPageAddress = ((uint32)SourcePtr);
  }
  #endif
  StatePtr->FlsReadAddress = (StatePtr->FlsReadAddress + ReadCount);
  SourcePtr++;
  /* [cover parentID={21FD7082-A812-42a4-B45D-5E5063D52045}]
  Is the requested read completed?[/
  [/cover] */
  while(ReadCount > 0U)
  {
    /* [cover parentID={EA26BAE2-1B25-4427-B7DA-0CF3D403394A}]
    Is page data copied to user buffer?[/
    [/cover] */
    if(PageBytes == 0U)
    {
      /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
      PageData is used inside Fls_lMainRead() local function to
      read the values. The address is not used beyond the context of the
      function, hence it is not an issue*/
      PagePtr = (uint8*)(&PageData);
      /* [cover parentID={D58F7AE4-F81C-4eb6-9504-DF6E07C75F73}]
      [/cover] */
      PageData = (*SourcePtr);
      /* DSYNC() is added to avoid compiler optimization (re-ordering of DFlash
      read and ECC error check in Fls_lChkBitErrors())*/
      DSYNC();
      #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_ON)
      EccErrorFlag = Fls_lChkBitErrors();
      /* [cover parentID={21857778-484B-450d-9281-DE81287F49BE}]
      ECC error occurred?
      [/cover] */
      if(EccErrorFlag != 0U)
      {
        ErrorFlag = 1U;
        /* update page addr*/
        /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from pointer to uint32
        is required to store the FLASH address/target address in state var
        structure. No memory alignment issues.*/
        /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from pointer to uint32
        type is required to access the FLASH address and store it in state var
        structure. No memory alignment issues.*/
        StatePtr-> FlsEccErrorPageAddress = ((uint32)SourcePtr);
      }
      #endif
      PageBytes = FLS_17_DMU_PAGE_SIZE;
      SourcePtr++;
    }
    /* [cover parentID={E60D3A99-ADF7-4458-9199-1C39AB79CD58}]
    [/cover] */
    *(StatePtr->FlsReadBufferPtr) = *PagePtr;
    (StatePtr->FlsReadBufferPtr)++;
    PagePtr++;
    ReadCount--;
    PageBytes--;
  }

  /* Check for single bit or double bit error */
  #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_OFF)
  ErrorFlag = Fls_lChkBitErrors();
  #endif
  /* [cover parentID={302E132C-2856-4b4a-B8AA-91F03C20F774}][/cover] */
  if(ErrorFlag != 0U)
  {
    /* [cover parentID={CC8AF404-74F3-4dec-8361-E916D059A5C5}][/cover] */
    #if(MCAL_AR_VERSION == MCAL_AR_440)
    (void)Det_ReportTransientFault( (uint16)FLS_17_DMU_MODULE_ID,
                              FLS_17_DMU_INSTANCE_ID,
                              FLS_17_DMU_SID_MAIN,
                              FLS_17_DMU_E_READ_FAILED);
    #else
      #if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
      (void)Mcal_Wrapper_Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                              FLS_17_DMU_INSTANCE_ID,
                              FLS_17_DMU_SID_MAIN,
                              FLS_17_DMU_E_READ_FAILED);
      #endif
    #endif
    /* Call to Fls_lErrorHandler local function */
    /* [cover parentID={D4143E91-3525-40a6-AA60-1288984E9CDD}][/cover] */
    Fls_lErrorHandler(FLS_17_DMU_READ);
  }
  else
  {
    /* [cover parentID={336448D9-7D79-46fe-8F5B-D711C74AF892}]
      Is read length zero ?
    [/cover] */
    if(StatePtr->FlsReadLength == 0U)
    {
      /* [cover parentID={77587821-AD60-4f95-98BF-8E5C42054191}]
      1 Set the job result as OK
      2 Set that there is no ongoing job
      [/cover] */
      /* Set Job Result to JOB OK if no warnings */
      LastJobResult = MEMIF_JOB_OK;
      /* 1. Clear the Job request */
      StatePtr->FlsJobType = FLS_17_DMU_NONE;

      /* 2. Update the global status variables */
      StatePtr->FlsJobResult = LastJobResult;

      /* [cover parentID={E916EC0D-DBCA-416a-876E-2EF997F493C1}]
        [/cover] */
      if(Fls_ConfigPtr->FlsJobEndNotificationPtr != NULL_PTR)

      {
        /* [cover parentID={C8511FFB-5D80-49f4-96AA-3D2BB3E3EAA3}]
             1 Set the notification caller as read
             2 Fls_JobEndNotification
             3 Set notification caller as none
             [/cover] */
        Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_READ_JOB;
        /* FlsJobEndNotificationPtr should be called */
        (Fls_ConfigPtr->FlsJobEndNotificationPtr)();
        Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_NO_JOB;
      }
    }
  }
}

/*******************************************************************************
** Traceability :[cover parentID={3C12F0A1-9B05-4de3-895F-F4268E9B4A9D}]      **
**                                                                            **
** Syntax : static void Fls_lMainCompare(void)                                **
**                                                                            **
** Service ID:  None                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non-reentrant                                                 **
**                                                                            **
** Parameters (in) : void                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : Performs the Compare operation during Interrupt/Cyclic       **
**               Job handling                                                 **
*******************************************************************************/
static void Fls_lMainCompare(void)
{
  Fls_17_Dmu_StateType *StatePtr;
  Fls_17_Dmu_LengthType CompLen;
  MemIf_JobResultType LastJobResult;
  const uint64 *SourcePtr;
  uint64 PageData;
  uint8 *PagePtr;
  uint32 PageOffset;
  uint32 PageBytes = 0U;
  Fls_17_Dmu_LengthType MaxRead;
  uint32 BitChange;
  uint32 ErrorFlag = 0U;
  #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_ON)
  uint32 EccErrorFlag = 0U;
  #endif
  /************ Initialise Local variables ****************************/
  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;

  LastJobResult = StatePtr->FlsJobResult;
  /* Get max read length according to the FLS mode */
  MaxRead = Fls_lGetReadModeLength();

  /* Check whether the given length is greater than MAX_READ */
  /* [cover parentID={E296BBF4-62F8-47d4-A520-EEFAE9136E97}]
   [/cover] */
  if(StatePtr->FlsReadLength > MaxRead)
  {

    /* [cover parentID={96D8CE13-8E81-4398-9B05-7AC78260CA95}]
       [/cover] */
    /* Load Max Byte to read in one cycle */
    CompLen = MaxRead;
    /* Decrement the count from the totalcount to read */
    StatePtr->FlsReadLength = StatePtr->FlsReadLength - CompLen;
  }
  else
  {
    /* [cover parentID={01D3385C-E281-46f1-BFD9-881D417A7664}]
            [/cover] */
    CompLen = StatePtr->FlsReadLength;
    StatePtr->FlsReadLength = 0U;
  }

  #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_OFF)
  /*Clear the ECC status bits by writing DMU_HF_ECCC.CLR with 11b to clear
             AERM bit*/
  BitChange = DMU_HF_ECCC.U | FLS_DMU_ECCC_CLR;
  /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
   the object types as the address of the register is being passed.*/
  FLS_17_DMU_LIB_RUNTIME_WRITEPERIPENDINITPROTREG(\
      (volatile uint32 *)&DMU_HF_ECCC.U, \
      BitChange);
  /*Clearing of AERM takes 2-3 cycles so NOP added*/
  NOP();
  NOP();
  NOP();
  #endif
  /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from uint32 to uint64* is required
  to access the FLASH address for data buffer alignment and store it in pointer
  for easy arithmetic operations. No memory alignment issues.*/
  /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from uint32 to uint64*
  type is required to access the FLASH address/target address and store it in
  pointer for easy arithmetic operations. No memory alignment issues.*/
  SourcePtr = (uint64*)Fls_lGetPageAddress(StatePtr->FlsReadAddress);
  PageOffset = (StatePtr->FlsReadAddress & FLS_PAGE_SIZE_MASK);
  PageBytes = (FLS_17_DMU_PAGE_SIZE - PageOffset);
  PageData = (*SourcePtr);
  /* DSYNC() is added to avoid compiler optimization (re-ordering of DFlash
  read and ECC error check in Fls_lChkBitErrors())*/
  DSYNC();
  /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
  PageData is used inside Fls_lMainCompare() local function to
  read the values. The address is not used beyond the context of the
  function, hence it is not an issue*/
  PagePtr = (uint8*)(&PageData);
  PagePtr = &PagePtr[PageOffset];
  #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_ON)
  EccErrorFlag = Fls_lChkBitErrors();
  /* [cover parentID={180FBF1A-D06C-4752-8D97-E089B6DA91CE}]
  [/cover] */
  if(EccErrorFlag != 0U)
  {
    ErrorFlag = 1U;
    /* update page addr*/
    /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from pointer to uint32
    is required to store the FLASH address/target address in state var
    structure. No memory alignment issues.*/
    /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from pointer to uint32
    type is required to access the FLASH address and store it in state var
    structure. No memory alignment issues.*/
    StatePtr-> FlsEccErrorPageAddress = ((uint32)SourcePtr);
  }
  #endif
  StatePtr->FlsReadAddress = (StatePtr->FlsReadAddress + CompLen);
  SourcePtr++;
  /* [cover parentID={DC9520C4-C1C8-4c4a-AED7-767BED2D3C71}]
  [/cover] */
  while(CompLen > 0U)
  {
    if(PageBytes == 0U)
    {
      /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
      PageData is used inside Fls_lMainCompare() local function to
      read the values. The address is not used beyond the context of the
      function, hence it is not an issue*/
      PagePtr = (uint8*)(&PageData);
      PageData = (*SourcePtr);
      /* DSYNC() is added to avoid compiler optimization (re-ordering of DFlash
      read and ECC error check in Fls_lChkBitErrors())*/
      DSYNC();
      #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_ON)
      /* [cover parentID={C43CD7EA-CA5E-41e5-A3BA-56CE17355C4B}]
      [/cover] */
      EccErrorFlag = Fls_lChkBitErrors();
      if(EccErrorFlag != 0U)
      {
        ErrorFlag = 1U;
        /* update page addr*/
        /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from pointer to uint32
        is required to store the FLASH address/target address in state var
        structure. No memory alignment issues.*/
        /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from pointer to uint32
        type is required to access the FLASH address and store it in state var
        structure. No memory alignment issues.*/
        StatePtr-> FlsEccErrorPageAddress = ((uint32)SourcePtr);
      }
      #endif
      PageBytes = FLS_17_DMU_PAGE_SIZE;
      SourcePtr++;
    }

    CompLen--;
    /* [cover parentID={5BC31CAB-979A-4f27-B6FD-37DD8A8BFD41}]
    [/cover] */
    if(*(StatePtr->FlsReadBufferPtr) != *PagePtr)
    {
      /* [cover parentID={F18814F1-301D-4039-8375-569167AEF1BF}]
      Set Job result as MEMIF_BLOCK_INCONSISTENT and break the loop
      [/cover] */
      LastJobResult = MEMIF_BLOCK_INCONSISTENT;
      CompLen = 0U;
    }
    (StatePtr->FlsReadBufferPtr)++;
    PagePtr++;
    PageBytes--;
  }
  /* Check if Non-correctable ECC error was present thus leading to failure */
  #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_OFF)
  ErrorFlag = Fls_lChkBitErrors();
  #endif
  /* [cover parentID={8CDE2B13-C40E-4ac6-A690-04565BDF9B5A}]
  Is there any accumulated bit error ?
  [/cover] */
  if(ErrorFlag!= 0U)
  {
    /* [cover parentID={0C949275-8441-4561-AC01-4C38A0FC4DA6}]
    Report FLS_17_DMU_E_COMPARE_FAILED (Runtime/Transient fault) error according
    to the Autosar version [/cover] */
    #if(MCAL_AR_VERSION == MCAL_AR_440)
    (void)Det_ReportTransientFault( (uint16)FLS_17_DMU_MODULE_ID,
                              FLS_17_DMU_INSTANCE_ID,
                              FLS_17_DMU_SID_MAIN,
                              FLS_17_DMU_E_COMPARE_FAILED);
    #else
      #if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
      /* [cover parentID={08F6505A-55B1-4c60-868B-9AE1A58BD337}]
      Report runtime error
      [/cover] */
      (void)Mcal_Wrapper_Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                              FLS_17_DMU_INSTANCE_ID,
                              FLS_17_DMU_SID_MAIN,
                              FLS_17_DMU_E_COMPARE_FAILED);
      #endif
    #endif
    /* Call to Fls_lErrorHandler local function */
    Fls_lErrorHandler(FLS_17_DMU_COMPARE);
  }
  /* Check if block was inconsistent */

  /* [cover parentID={555958BA-3AF2-4972-8288-CEF766CA29D1}]
  Was the job result set as FAIL ?
  [/cover] */
  else if(LastJobResult == MEMIF_BLOCK_INCONSISTENT)
  {
    /* Update the global status variables */
    StatePtr->FlsJobResult = LastJobResult;

    /* Clear the failed Job  */
    /* [cover parentID={7FF6AE9C-7D1C-47b3-ACC0-AA8974797C11}]
    1) Set job result to INCONSISTENT.
    2) Set the Fls Job to NONE.
    3) Clear command status
    [/cover] */
    StatePtr->FlsJobType = FLS_17_DMU_NONE;

    /* Clear the errors status flags */
    BitChange = FLS_DMU_ERR_CLR;
    /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
     the object types as the address of the register is being passed.*/
    FLS_17_DMU_SFR_RUNTIME_WRITE32( \
                                    (volatile uint32 *)&DMU_HF_CLRE.U, \
                                    BitChange);

    /* [cover parentID={804C2028-4885-4373-9C2C-79A21887D9CB}]
    Is the job error notification configured?
    [/cover] */
    if(Fls_ConfigPtr->FlsJobErrorNotificationPtr != NULL_PTR)
    {
      Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_COMPARE_JOB;
      /* FlsJobErrorNotificationPtr should be called */
      /* [cover parentID={8F96A53C-476D-479f-BE2D-9C6DE07E6B82}]
      Call FlsJobErrorNotificationPtr
      [/cover] */
      (Fls_ConfigPtr->FlsJobErrorNotificationPtr)();
      Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_NO_JOB;
    }
  }
  /* No failures detected */
  else
  {
    /* Job completed */
    /* [cover parentID={F45F2F43-2BC5-4ed0-BBE0-201FD974856A}]
    If the read bytes are remaining ?
    [/cover] */
    if ( StatePtr->FlsReadLength == 0U)
    {
      /* [cover parentID={8FF67721-99AB-45e9-91AA-6D6D80FFC27C}]
      Set job status of compare to zero
      job result as OK
      Set there is no ongoing job type
      Call FlsJobEndNotificationPtr
      [/cover] */
      /* Update the result to JOB_OK if no warnings */
      LastJobResult = MEMIF_JOB_OK;

      /* 1. Update the Global Status variables */
      StatePtr->FlsJobResult = LastJobResult;
      /* 2. Clear the Job request */
      StatePtr->FlsJobType = FLS_17_DMU_NONE;

      /* [cover parentID={9F61B7BD-362E-4d68-832A-78D0AFFDE614}]
          Is the job end notification configured?
          [/cover] */
      if(Fls_ConfigPtr->FlsJobEndNotificationPtr != NULL_PTR)
      {
        Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_COMPARE_JOB;
        /* FlsJobEndNotificationPtr should be called */
        /* [cover parentID={5539CBB5-D1EF-4ebc-A6CD-F007C59E8808}]
        Call FlsJobEndNotificationPtr
        [/cover] */
        (Fls_ConfigPtr->FlsJobEndNotificationPtr)();
        Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_NO_JOB;
      }

    }
    /* Job not yet completed */
    else
    {
      /* Avoid MISRA error */
    }
  }
}

/*******************************************************************************
** Traceability : [cover parentID={CD60BE4B-C8CF-47d3-96F3-176EB447E34B}]     **
**                                                                            **
** Syntax : static void Fls_lMainBlankCheck(void)                             **
**                                                                            **
** Service ID:  None                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non-reentrant                                                 **
**                                                                            **
** Parameters (in) : void                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : Performs the Blank Check operation during Interrupt/Cyclic   **
**               Job handling                                                 **
*******************************************************************************/
static void Fls_lMainBlankCheck(void)
/* [cover parentID={CC1709BE-2FF2-44ce-A8F2-55FC9C1829FE}]
Fls_lMainBlankCheck
[/cover] */
{
  Fls_17_Dmu_StateType *StatePtr;
  Fls_17_Dmu_LengthType CompLen;
  MemIf_JobResultType LastJobResult;
  const uint64 *SourcePtr;
  uint64 PageData;
  uint8 *PagePtr;
  uint32 PageOffset;
  uint32 PageBytes = 0U;
  Fls_17_Dmu_LengthType MaxRead;
  uint32 BitChange;
  uint32 ErrorFlag = 0U;
  #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_ON)
  uint32 EccErrorFlag = 0U;
  #endif
  /************ Initialise Local variables ****************************/
  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
  LastJobResult = StatePtr->FlsJobResult;

  /* Get max read length according to the FLS mode */
  MaxRead = Fls_lGetReadModeLength();

  /* Check whether the given length is greater than MAX_READ */
  /* [cover parentID={A6265ABB-BB93-416d-AAB7-57CC2DAE013C}]
  Is the given length is greater than Read mode length?
  [/cover] */
  if(StatePtr->FlsReadLength > MaxRead)
  {
    /* Load Max Byte to read in one cycle */

    /* [cover parentID={E7330B53-EDD0-4308-B861-971923B9CADF}]
     [/cover] */
    CompLen = MaxRead;
    /* Decrement the count from the totalcount to read */
    StatePtr->FlsReadLength = StatePtr->FlsReadLength - CompLen;
  }
  else
  {
    /* [cover parentID={2C82B987-3449-4082-ADD3-7F13AE2D632F}]
           [/cover] */
    CompLen = StatePtr->FlsReadLength;
    StatePtr->FlsReadLength = 0U;
  }
  #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_OFF)
  /*Clear the ECC status bits by writing DMU_HF_ECCC.CLR with 11b to clear
             AERM bit*/
  BitChange = DMU_HF_ECCC.U | FLS_DMU_ECCC_CLR;

  /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
  the object types as the address of the register is being passed. */
  FLS_17_DMU_LIB_RUNTIME_WRITEPERIPENDINITPROTREG( \
      (volatile uint32 *)&DMU_HF_ECCC.U, \
      BitChange);
  /*Clearing of AERM bits takes 2-3 cyles so added NOP*/
  NOP();
  NOP();
  NOP();
  #endif
  /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from uint32 to uint64* is required
  to access the FLASH address for data buffer alignment and store it in pointer
  for easy arithmetic operations. No memory alignment issues.*/
  /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from uint32 to pointer
  type is required to access the FLASH address/target address and store it in
  pointer for easy arithmetic operations. No memory alignment issues.*/
  SourcePtr = (uint64*)Fls_lGetPageAddress(StatePtr->FlsReadAddress);
  PageOffset = (StatePtr->FlsReadAddress & FLS_PAGE_SIZE_MASK);
  PageBytes = (FLS_17_DMU_PAGE_SIZE - PageOffset);
  PageData = (*SourcePtr);
  /* DSYNC() is added to avoid compiler optimization (re-ordering of DFlash
  read and ECC error check in Fls_lChkBitErrors())*/
  DSYNC();
  /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
  PageData is used inside Fls_lMainBlankCheck() local function to
  read the values. The address is not used beyond the context of the
  function, hence it is not an issue*/
  PagePtr = (uint8*)(&PageData);
  PagePtr = &PagePtr[PageOffset];
  #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_ON)
  EccErrorFlag = Fls_lChkBitErrors();
  /* [cover parentID={2BDAE170-EBC3-4285-9A0C-4E7E5827C75A}]
  [/cover] */
  if(EccErrorFlag != 0U)
  {
    ErrorFlag = 1U;
    /* update page addr*/
    /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from pointer to uint32
    is required to store the FLASH address/target address in state var
    structure. No memory alignment issues.*/
    /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from pointer to uint32
    type is required to access the FLASH address and store it in state var
    structure. No memory alignment issues.*/
    StatePtr-> FlsEccErrorPageAddress = (uint32)SourcePtr;
  }
  #endif
  StatePtr->FlsReadAddress = (StatePtr->FlsReadAddress + CompLen);
  SourcePtr++;
  /* [cover parentID={5E8EFC72-E212-46aa-9EA3-62321EECDE58}]
  Is the read count greater than 0?
  [/cover] */
  while(CompLen > 0U)
  {
    if(PageBytes == 0U)
    {
      /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
      PageData is used inside Fls_lMainBlankCheck() local function to
      read the values. The address is not used beyond the context of the
      function, hence it is not an issue*/
      PagePtr = (uint8*)(&PageData);
      PageData = (*SourcePtr);
      /* DSYNC() is added to avoid compiler optimization (re-ordering of DFlash
      read and ECC error check in Fls_lChkBitErrors())*/
      DSYNC();
      #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_ON)
      EccErrorFlag = Fls_lChkBitErrors();
      /* [cover parentID={065F27A6-4780-460a-9C95-AA8D0DCD7ADD}]
      [/cover] */
      if(EccErrorFlag != 0U)
      {
        ErrorFlag = 1U;
        /* update page addr*/
        /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from pointer to uint32
        is required to store the FLASH address/target address in state var
        structure. No memory alignment issues.*/
        /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from pointer to uint32
        type is required to access the FLASH address and store it in state var
        structure. No memory alignment issues.*/
        StatePtr-> FlsEccErrorPageAddress = (uint32)SourcePtr;
      }
      #endif
      PageBytes = FLS_17_DMU_PAGE_SIZE;
      SourcePtr++;
    }
    CompLen--;
    /* [cover parentID={CA1271AA-20AC-42d7-A92E-0936208FD210}]
    [/cover] */
    if(FLS_17_DMU_DEFAULT_ERASEVALUE != *PagePtr)
    {
      /* [cover parentID={E1ED6439-0220-49b1-A81A-683BEBE716D2}]
      [/cover] */
      LastJobResult = MEMIF_BLOCK_INCONSISTENT;
      CompLen = 0U;
    }
    PagePtr++;
    PageBytes--;
  }
  /* Check if Non-correctable ECC error was present thus leading to failure */
  #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_OFF)
  ErrorFlag = Fls_lChkBitErrors();
  #endif

  /* [cover parentID={6330B07D-5056-45d5-A964-E6F1D989D1BE}]
  [/cover] */
  /* Check if Non-correctable ECC error was present thus leading to failure */
  if(ErrorFlag != 0U)
  {
    /* [cover parentID={BA25C1D8-64EE-4482-A64D-DE922F7A2A38}]
    Report FLS_17_DMU_E_BLANKCHECK_FAILED error
    [/cover] */
    #if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
    /* Blank Check Job fails due to hardware error */
    /* Report Runtime error code to Mcal_Wrapper */
    (void)Mcal_Wrapper_Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                              FLS_17_DMU_INSTANCE_ID,
                              FLS_17_DMU_SID_MAIN,
                              FLS_17_DMU_E_BLANKCHECK_FAILED);
    #endif
    /* Call to Fls_lErrorHandler local function */
    Fls_lErrorHandler(FLS_17_DMU_BLANKCHECK);
  }

  /* [cover parentID={39DC4E7C-0DEF-4575-B2BA-8E2F5C1F7A8C}]
  Is the job result inconsistent ?
  [/cover] */
  /* Check if block was inconsistent */
  else if(LastJobResult == MEMIF_BLOCK_INCONSISTENT)
  {

    /* [cover parentID={66EC1E14-CC95-4ffd-A207-004A4D20237B}]
    1 Job result is inconsistent
    2 Set Job status of Blankcheck to 0
    3 Set flash job type to none
    [/cover] */
    /* Update the global status variables */
    StatePtr->FlsJobResult = LastJobResult;

    /* Clear the failed Job */
    StatePtr->FlsJobType = FLS_17_DMU_NONE;

    /* Clear the errors status flags */
    BitChange = FLS_DMU_ERR_CLR;
    /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
     the object types as the address of the register is being passed.*/
    FLS_17_DMU_SFR_RUNTIME_WRITE32( \
                                    (volatile uint32 *)&DMU_HF_CLRE.U, \
                                    BitChange);

    /* [cover parentID={08E0DC31-33DF-4858-9C5D-88209C2AB7B2}]
    Is the job error notification configured?
    [/cover] */
    if(Fls_ConfigPtr->FlsJobErrorNotificationPtr != NULL_PTR)
    {
      Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_BLANKCHECK_JOB;
      /* FlsJobErrorNotificationPtr should be called */
      /* [cover parentID={7343C2F5-4978-41ad-A5DD-F465827A5F2E}]
      Call FlsJobErrorNotificationPtr
      [/cover] */
      (Fls_ConfigPtr->FlsJobErrorNotificationPtr)();
      Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_NO_JOB;
    }

  }
  /* No failures detected */
  else
  {
    /* Job completed */
    /* [cover parentID={82FD4CD2-1600-4745-ACB7-16E920DF482E}]
    Is read length equal to zero?
    [/cover] */
    if ( StatePtr->FlsReadLength == 0U)
    {
      /* [cover parentID={A6B380AF-9ADE-4208-AC1C-E7CA3AA634C5}]
      1 Set job status to blank check to zero
      2 Set job result to ok
      3 Set job type to none
      [/cover] */
      /* Update the result to JOB_OK if no warnings */
      LastJobResult = MEMIF_JOB_OK;

      /* 1. Update the Global Status variables */
      StatePtr->FlsJobResult = LastJobResult;

      /* 2. Clear the Job request */
      StatePtr->FlsJobType = FLS_17_DMU_NONE;


      /* [cover parentID={5BD7D116-4D4E-456b-B193-C56E772700F2}]
      Is the job end notification configured?
      [/cover] */
      if(Fls_ConfigPtr->FlsJobEndNotificationPtr != NULL_PTR)

      {
        Fls_ConfigPtr->FlsStateVarPtr->NotifCaller =
          FLS_17_DMU_BLANKCHECK_JOB;
        /* [cover parentID={4E929EC6-67C2-4e32-9767-1C8D28C040E3}]
        Call FlsJobEndNotificationPtr
        [/cover] */
        (Fls_ConfigPtr->FlsJobEndNotificationPtr)();
        Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_NO_JOB;
      }

    }
    /* Job not yet completed */
    else
    {
      /* Avoid MISRA error */
    }
  }
}
/*******************************************************************************
** Traceability : [cover parentID={EF96175F-F994-4d9c-BD93-5CF8463F5CE5}]     **
**                                                                            **
** Syntax : static void Fls_lMainWrite(void)                                  **
**                                                                            **
** Service ID:  None                                                          **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non-reentrant                                                 **
**                                                                            **
** Parameters (in) : void                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : Performs the Write operation during Interrupt/Cyclic         **
**               Job handling                                                 **
*******************************************************************************/
static void Fls_lMainWrite(void)
/* [cover parentID={6D182FBC-83B3-4374-B6D9-DE1FE855AB91}]
Fls_lMainWrite
[/cover] */
{
  Fls_17_Dmu_StateType       *StatePtr;
  MemIf_JobResultType LastJobResult;
  uint32     PhysicalAddress;
  boolean             Error = FALSE ;
  uint8               PageLength;
  uint32     BitChange;

  /******************* Initialise local variables ********************/
  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;

  /* Setting the PhysicalAddress to DF0 start address for Command cycle
    execution */
  /* [cover parentID={0FCF07E2-45ED-4c11-9ED4-304D1A5D5D57}]
  Setting the physical address
  [/cover] */
  PhysicalAddress = FLS_17_DMU_BASE_ADDRESS;

  /* Check for operational error */
  /* [cover parentID={E251B206-AC59-454e-9753-A7F656DA9A39}]
  Is Operation error detected?
  [/cover] */
  if(Fls_lChkOperError() != 0U)
  {
    /* [cover parentID={DA364642-D70D-4832-BDEE-C91AF19BFC02}]
    Report write error (DET/Safety/RTE/Transient) according to Autosar
    version [/cover] */
    #if(MCAL_AR_VERSION == MCAL_AR_440)
    (void)Det_ReportTransientFault( (uint16)FLS_17_DMU_MODULE_ID,
                            FLS_17_DMU_INSTANCE_ID,
                            FLS_17_DMU_SID_MAIN,
                            FLS_17_DMU_E_WRITE_FAILED);
    #else
      /* [cover parentID={9764FBD6-16E6-49b1-924B-AFC37936ECA2}]
      Runtime error detection enabled
      [/cover] */
      #if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
      /* Report Runtime error code to Mcal_Wrapper */
      /* [cover parentID={8F543077-AC3A-4c9c-BB33-3D93A7254B8A}]
      Report runtime error
      [/cover] */
      (void)Mcal_Wrapper_Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                            FLS_17_DMU_INSTANCE_ID,
                            FLS_17_DMU_SID_MAIN,
                            FLS_17_DMU_E_WRITE_FAILED);
      #endif
    #endif
    Error = (boolean)TRUE;
  }

  /* Check for Program verification error */
  #if(FLS_17_DMU_IFX_FEE_USED == STD_OFF)
  /* [cover parentID={44BD2BAB-C1B6-4419-A1D1-39B07A345F18}]
  Is PVER detected ?
  [/cover] */
  /* [cover parentID={43B6C1D6-08F6-4a8a-B8B4-3173D9A5F054}]
  Check for Program verification error
  [/cover] */
  else if((boolean)TRUE == Fls_lPverChk())
  {
    Error = (boolean)TRUE;
    /* [cover parentID={4297C209-7AE5-424c-8DE7-68AB53442E1A}]
    Report write error (DET/Safety/RTE/Transient) according to Autosar
    version [/cover] */
    #if(MCAL_AR_VERSION == MCAL_AR_440)
      (void)Det_ReportTransientFault( (uint16)FLS_17_DMU_MODULE_ID,
                            FLS_17_DMU_INSTANCE_ID,
                            FLS_17_DMU_SID_MAIN,
                            FLS_17_DMU_E_WRITE_FAILED);
      #if (FLS_17_DMU_WRITE_VERIFICATION == STD_ON)
      /* [cover parentID={8F543077-AC3A-4c9c-BB33-3D93A7254B8A}]
      Report runtime error
      [/cover] */
      (void)Mcal_Wrapper_Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                            FLS_17_DMU_INSTANCE_ID,
                            FLS_17_DMU_SID_MAIN,
                            FLS_17_DMU_E_VERIFY_WRITE_FAILED);
      #endif
    #else
      #if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) || \
      (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
      Fls_lReportError(FLS_17_DMU_SID_MAIN,
                       FLS_17_DMU_E_VERIFY_WRITE_FAILED);
      #endif
      /* [cover parentID={9764FBD6-16E6-49b1-924B-AFC37936ECA2}]
      Runtime error detection enabled
      [/cover] */
      #if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
      /* [cover parentID={8F543077-AC3A-4c9c-BB33-3D93A7254B8A}]
      Report runtime error
      [/cover] */
      (void)Mcal_Wrapper_Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                            FLS_17_DMU_INSTANCE_ID,
                            FLS_17_DMU_SID_MAIN,
                            FLS_17_DMU_E_WRITE_FAILED);
      #endif
    #endif
  }
  #endif  /* FLS_17_DMU_IFX_FEE_USED == STD_OFF */
  else
  {
    /* [cover parentID={07EE857A-6236-4f58-B157-C96EB8326069}]
    Is the mode normal (page)  ?
    [/cover] */
    if( Fls_lGetWriteMode() == FLS_17_DMU_PAGE_WRITE)
    {
      PageLength = FLS_17_DMU_PAGE_SIZE;
    }
    else
    {
      PageLength = FLS_17_DMU_BURST_PAGE_SIZE;
    }

    /* PageStartAddress is incremented by PageLength bytes */
    StatePtr->FlsWriteAddress += PageLength;
    /* length is decremented by PageLength */
    StatePtr->FlsWriteLength -= PageLength;

    /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
     array indexing used for FLASH address calculation and for subsequent
       traversal.The access range is within the flash address range.*/
    StatePtr->FlsWriteBufferPtr = (StatePtr->FlsWriteBufferPtr + \
                                   PageLength);

  }
  /* [cover parentID={14666654-242F-44fe-8343-CA415484EB44}]
  [/cover] */
  if(Error == (boolean)FALSE)
  {
    /* Check for Program verification error */
    #if(FLS_17_DMU_IFX_FEE_USED == STD_ON)
    /* [cover parentID={01624FAF-D8E2-4230-82D2-D2D000C9BFB8}]
    [/cover] */
    /* [cover parentID={9FAF48D8-39F9-45f2-A433-C12B493052AE}]
    Program verification error check
    [/cover] */
    if ((boolean)TRUE == Fls_lPverChk())
    {
      StatePtr->FlsPver = 1U;
    }
    #endif  /* FLS_17_DMU_IFX_FEE_USED == STD_ON */

    /* Check for Flash write Job is finished completely  */
    /* [cover parentID={B5460158-12CD-4f3c-945B-F0E21EB79402}]
    Check if the flash write length is finished completely?
    [/cover] */
    if(StatePtr->FlsWriteLength == 0U)
    {
      #if(FLS_17_DMU_IFX_FEE_USED == STD_ON)
      /* [cover parentID={2885FE31-54BB-4d44-AC7D-61D46743EA2E}]
      Is the PVER flag set ?
      [/cover] */
      if( StatePtr->FlsPver == 0U)
      #endif
      {
        /* [cover parentID={66D9DABC-41EA-49b1-9AE6-E7A0C8A49071}]
        Update job result to OK
        Update job type as NONE
        Clear the Write Job Started Status bit
        [/cover] */

        /* Indicate Job successfully completed if no warnings seen till now */
        LastJobResult = MEMIF_JOB_OK;
        /* 1. Update the global status variables */
        StatePtr->FlsJobResult = LastJobResult;
        /* 2. Clear the Write Job */
        StatePtr->FlsJobType = FLS_17_DMU_NONE;
        /* 3. Clear the Write Job Started Status bit */
        StatePtr->JobStarted.Write = 0U;
        /* [cover parentID={C938F682-00F1-4522-850E-78314BCAB1F6}]
          Execute Clear Status command
         [/cover] */
        /* Clear the errors status flags */
        BitChange = FLS_DMU_ERR_CLR;
        /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
         the object types as the address of the register is being passed.*/
        FLS_17_DMU_SFR_RUNTIME_WRITE32( \
                                        (volatile uint32 *)&DMU_HF_CLRE.U, \
                                        BitChange);
        /* [cover parentID={107F6003-DA61-43ad-998B-FF8844150448}]
        Is the notification configured ?
        [/cover] */
        if(Fls_ConfigPtr->FlsJobEndNotificationPtr != NULL_PTR)
        {
          /* [cover parentID={C4514C38-EFB6-4030-B3F8-5C8E5A3F556E}]
          Set NotifCaller to WRITE
          [/cover] */
          Fls_ConfigPtr->FlsStateVarPtr->NotifCaller =
            FLS_17_DMU_WRITE_JOB;
          /* FlsJobEndNotificationPtr should be called */
          /* [cover parentID={4B4F32E7-87B9-49ce-B939-0A151BE7A414}]
          Call FlsJobEndNotification
          [/cover] */
          (Fls_ConfigPtr->FlsJobEndNotificationPtr)();
          Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_NO_JOB;
        }
      }
      #if(FLS_17_DMU_IFX_FEE_USED == STD_ON)
      else
      {
        #if(MCAL_AR_VERSION == MCAL_AR_440)
        (void)Det_ReportTransientFault( (uint16)FLS_17_DMU_MODULE_ID,
                                FLS_17_DMU_INSTANCE_ID,
                                FLS_17_DMU_SID_MAIN,
                                FLS_17_DMU_E_WRITE_FAILED);
          #if (FLS_17_DMU_WRITE_VERIFICATION == STD_ON)
          /* [cover parentID={8F543077-AC3A-4c9c-BB33-3D93A7254B8A}]
          Report runtime error
          [/cover] */
          (void)Mcal_Wrapper_Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                                FLS_17_DMU_INSTANCE_ID,
                                FLS_17_DMU_SID_MAIN,
                                FLS_17_DMU_E_VERIFY_WRITE_FAILED);
          #endif
        #else
          #if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) || \
          (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
          Fls_lReportError(FLS_17_DMU_SID_MAIN,
                           FLS_17_DMU_E_VERIFY_WRITE_FAILED);
          #endif
          /* [cover parentID={9764FBD6-16E6-49b1-924B-AFC37936ECA2}]
          Runtime error detection enabled
          [/cover] */
          #if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
          /* Report Runtime error code to Mcal_Wrapper */
          /* [cover parentID={8F543077-AC3A-4c9c-BB33-3D93A7254B8A}]
          Report runtime error
          [/cover] */
          (void)Mcal_Wrapper_Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                                FLS_17_DMU_INSTANCE_ID,
                                FLS_17_DMU_SID_MAIN,
                                FLS_17_DMU_E_WRITE_FAILED);
          #endif
        #endif
        /* [cover parentID={E0828E8C-9475-4a81-B853-0290FC8C9087}]
        1.  Set the write job result to JOB FAILED
        2.  Set the driver status to idle by setting the job status to NONE
        3.  Reset the status of write started
        4.  Clear the HW error status
        [/cover] */
        /* Update the global status variables */
        StatePtr->FlsJobResult = MEMIF_JOB_FAILED;
        /* 2. Clear the Write Job */
        StatePtr->FlsJobType = FLS_17_DMU_NONE;
        /* 3. Clear the Write Job Started Status bit */
        StatePtr->JobStarted.Write = 0U;

        /* Clear the errors status flags */
        BitChange = FLS_DMU_ERR_CLR;
        /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
         the object types as the address of the register is being passed.*/
        FLS_17_DMU_SFR_RUNTIME_WRITE32( \
                                        (volatile uint32 *)&DMU_HF_CLRE.U, \
                                        BitChange);
        StatePtr->FlsPver = (uint8)0x00;

        /* [cover parentID={7D7674D2-6A24-49a0-869F-1D779611670C}]
        Is PVER error notification function configured ?
        [/cover] */
        if(Fls_ConfigPtr->FlsProgVerifyErrNotifPtr != NULL_PTR)
        {
          Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_WRITE_JOB;
          /* Fls PVER Notification should be called */
          /* [cover parentID={D8375BAC-CB2C-43a4-8C12-35FFDC64D3E3}]
          Call PVER error notification callback function
          [/cover] */
          (Fls_ConfigPtr->FlsProgVerifyErrNotifPtr)();
          Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_NO_JOB;
        }
      }
      #endif
    }
    else /*Write Operation not finished, writeLength not zero*/
    {
      #if (FLS_17_DMU_ERASE_VERIFICATION == STD_ON)
      /* [cover parentID={CBC62C0E-16DE-4a3a-9A9A-3331DC697059}]
      CHECK FOR DFLASHx PAGE NOT ERASED
      [/cover] */
      /* [cover parentID={4FEA93A2-7C3E-4cf1-ABEB-A3C7CE5AC41D}]
      Call function to verify if the page is erased corretly
      [/cover]*/
      /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from uint32 to pointer
      type is required to pass the FLASH address/target address to
      Fls_lPageEraseCheck() function. No memory alignment issues. */
      /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from uint32 to pointer is
      required to pass the FLASH address/target address in state var structure
      to Fls_lPageEraseCheck() function. No memory alignment issues. */
      if(Fls_lPageEraseCheck((uint32 *)(StatePtr->FlsWriteAddress),
                         StatePtr->FlsWriteLength, FLS_17_DMU_SID_MAIN) != E_OK)
      {
        Error = (boolean)TRUE;
        /* [cover parentID={70C26BA9-D5DA-4915-AA93-958065DF6E35}]
        Call error handler
        [/cover] */
        Fls_lErrorHandler(FLS_17_DMU_WRITE);
      }
      /* Check needed only when DET is STD_ON */

      /* [cover parentID={2369B0F7-D19B-4c7c-BEFE-F6B7D389E0A6}]
      If there is no error flag set
      [/cover] */
      if(Error == (boolean)FALSE)
      #endif /* FLS_17_DMU_ERASE_VERIFICATION == STD_ON */
      {
        /* Start Write operation */
        /* [cover parentID={6F377A17-8EC5-4ab6-96C9-853EB66BDAC4}]
        [/cover]*/
        Fls_lMainWriteJobStart(PhysicalAddress);
      }
    }
  }
  else
  {
    /*[cover parentID={66F08F3E-6331-476a-9509-C52646D79C4F}][/cover]*/
    /* Call to Fls_lErrorHandler local function */
    Fls_lErrorHandler(FLS_17_DMU_WRITE);
  }
  /*[cover parentID={8B75A26F-E481-48c0-95A2-7BDA263BC235}][/cover]*/
}/* end of Fls_lMainWrite */

/*******************************************************************************
** Traceability : [cover parentID={DA20ED82-A382-4935-9DCA-2CB7DB807EFF}]     **
**                                                                            **
** Syntax : static void Fls_lMainWriteJobStart(const uint32 PhysicalAddress)  **
**                                                                            **
** Service ID:  None                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non-reentrant                                                 **
**                                                                            **
** Parameters (in) : Physical Address - Physical address for Write            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : Performs the Write operation during Interrupt/Cyclic         **
**               Job handling                                                 **
*******************************************************************************/
static void Fls_lMainWriteJobStart(const uint32 PhysicalAddress)
{
  Fls_17_Dmu_StateType   *StatePtr;
  uint32                  SeqProtErr;
  uint8                   WriteMode;

  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;

  /* Mark that the Job has been started */
  StatePtr->JobStarted.Write = 1U;
  /* Obtain the write mode (Page or Burst) */
  WriteMode = Fls_lGetWriteMode();

  /* [cover parentID={D5529673-60AA-40d6-8AB4-8B6CA095B1B2}]
  Clear all error status flags
  [/cover] */
  Fls_lClearStatusCmdCycle();
  /************* Call Write command sequence *************/
  Fls_lCallWriteCommand(PhysicalAddress, StatePtr, WriteMode);

  SeqProtErr = Fls_lChkSeqProtErrors();

  /* Check for Sequence error,Protection error bit */
  /* [cover parentID={9B8D418C-8979-4f82-A189-E037B5105CEE}]
  Is Sequence error,Protection error bit not reset?
  [/cover] */
  if(SeqProtErr != 0U)
  {
    /* [cover parentID={6848FCA7-2DD9-481f-8AEB-BFB1C183E35A}]
    Report write error (Runtime/transient fault) according to the Autosar
    version [/cover] */
    #if(MCAL_AR_VERSION == MCAL_AR_440)
    (void)Det_ReportTransientFault( (uint16)FLS_17_DMU_MODULE_ID,
                            FLS_17_DMU_INSTANCE_ID,
                            FLS_17_DMU_SID_MAIN,
                            FLS_17_DMU_E_WRITE_FAILED);
    #else
      /* [cover parentID={9764FBD6-16E6-49b1-924B-AFC37936ECA2}]
      Runtime error detection enabled
      [/cover] */
      #if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
      /* [cover parentID={E589FD7F-86DA-4aa9-8F8F-FA675DFD6438}]
      Report runtime error
      [/cover] */
      (void)Mcal_Wrapper_Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                            FLS_17_DMU_INSTANCE_ID,
                            FLS_17_DMU_SID_MAIN,
                            FLS_17_DMU_E_WRITE_FAILED);
      #endif
    #endif
    /* Call to Fls_lErrorHandler local function */
    /* [cover parentID={F50049B6-39C7-4e2e-8AB1-FF0BC5284ADF}]
    Call to ErrorHandler local function
    [/cover] */
    Fls_lErrorHandler(FLS_17_DMU_WRITE);
  }
  /* Check for Command Cycle Timeout Error */
  /* [cover parentID={C8111C73-2D8E-49ee-BC1F-3BA9B532ECD0}]
  If command cycle timeout error detected?
  [/cover] */
  else if (StatePtr->FlsTimeoutErr == FLS_17_DMU_WRITE)
  {
    /* [cover parentID={01947A3E-444B-475e-89A3-5D2CD483FFCD}]
    Report write error (Runtime/transient fault) according to the Autosar
    version [/cover] */
    #if(MCAL_AR_VERSION == MCAL_AR_440)
    (void)Det_ReportTransientFault( (uint16)FLS_17_DMU_MODULE_ID,
                            FLS_17_DMU_INSTANCE_ID,
                            FLS_17_DMU_SID_MAIN,
                            FLS_17_DMU_E_WRITE_FAILED);
    #else
      /* [cover parentID={9764FBD6-16E6-49b1-924B-AFC37936ECA2}]
      Runtime error detection enabled
      [/cover] */
      #if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
      /* [cover parentID={E589FD7F-86DA-4aa9-8F8F-FA675DFD6438}]
      Report runtime error
      [/cover] */
      (void)Mcal_Wrapper_Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                            FLS_17_DMU_INSTANCE_ID,
                            FLS_17_DMU_SID_MAIN,
                            FLS_17_DMU_E_WRITE_FAILED);
      #endif
    #endif
    /* [cover parentID={F50049B6-39C7-4e2e-8AB1-FF0BC5284ADF}]
         [/cover] */
    /* Call to Fls_lErrorHandler local function */
    Fls_lErrorHandler(FLS_17_DMU_WRITE);
  }
  else
  {
    /* dummy else */
  }
}


/*******************************************************************************
** Traceability :   [cover parentID={F146E9B8-8D93-44e6-B685-4512CD9D7996}]   **
**                                                                            **
** Syntax : void Fls_17_Dmu_Isr(void)                                         **
**                                                                            **
** Service ID: 0x2D                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : void                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : This routine is used instead of Main function if configured  **
** for Erase and Write Jobs.                                                  **
*******************************************************************************/
#if( FLS_17_DMU_USE_INTERRUPTS == STD_ON)
/* [cover parentID={ACBA93D7-451E-46e4-8042-0709418579B2}]
Flash use interrupts is enable
[/cover] */
/* [cover parentID={C4627507-8FE4-4c06-9B52-A03B36EC1995}][/cover] */
void Fls_17_Dmu_Isr(void)
{
  const Fls_17_Dmu_StateType  *StatePtr;
  uint8 JobType;
  uint32 FlashFsrStatus;

  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
  JobType = StatePtr->FlsJobType;


  /* [cover parentID={7846D57A-04E4-4ad7-B320-FDFB964B2EC7}]
   Is there any pending job?
  [/cover] */
  if( JobType != FLS_17_DMU_NONE)
    /* [cover parentID={7846D57A-04E4-4ad7-B320-FDFB964B2EC7}]
    Is there any pending job?
    [/cover] */
  {
    #if(FLS_17_DMU_SAFETY_ENABLE == STD_ON)
    #if(FLS_17_DMU_CANCEL_API  ==  STD_ON)
    /* [cover parentID={AB579A17-99BE-4335-B18D-003C5C160B37}]
       [/cover] */
    if(Fls_17_Dmu_JobCancelFlag == FLS_DMU_CANCEL_STATE)
    {
      /* [cover parentID={1F3D4A14-33A2-4b14-BA1C-BE402EE2610A}]
      [/cover] */
      Fls_17_Dmu_JobCancelFlag = FLS_DMU_CANCEL_RESET;
    }
    else
    #endif
    #endif
    {
      FlashFsrStatus = (uint32)DMU_HF_SUSPEND.B.SPND;
      /************************** ERASE *********************************/
      /* [cover parentID={9965D260-A6A3-4996-BB9D-616A743E13D8}]
      Is erase job pending?
      [/cover] */
      if(JobType == FLS_17_DMU_ERASE)
      {
        /* [cover parentID={66F7F03B-813F-4219-A41B-B3C26A363353}]
         Is HW Busy  or Suspend bit set ?
        [/cover] */
        if((Fls_lHWBusyCheck() == 0U) && (FlashFsrStatus == 0U))
        {
          /* Fls_Main_Erase operation should be called  */

          /* [cover parentID={B76AB378-82EA-4423-B8D7-1D5278617320}]
          [/cover] */
          Fls_lMainErase();
        }
        #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
        else
        {
          #if (FLS_17_DMU_USE_ERASESUSPEND == STD_ON)
          /* [cover parentID={7662DCA0-6C70-4ec6-A948-9B0D80CBEBD4}]
           [/cover] */
          if(Fls_17_Dmu_EraseSuspendFlag == FLS_DMU_SUSPEND_STATE)
          {
            /* [cover parentID={4FAB8791-7093-440c-B4B8-3FE761FECDA3}]
                          [/cover] */
            Fls_17_Dmu_EraseSuspendFlag = FLS_DMU_SUSPEND_RESET;
          }
          else
          #endif
          {
            /* [cover parentID={16A47F4C-1538-4f78-8376-396D1E0AE07B}]
              Raise Safety Error Invalid ISR
            [/cover] */
            Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                               FLS_17_DMU_SID_ISR, FLS_17_DMU_SE_INVALID_ISR);
          }
        }
        #endif

      }
      /* [cover parentID={B54EA47D-6C51-47a0-856A-126E54F4DB1A}]
      Is write job pending?
      [/cover] */
      /************************** WRITE *********************************/
      else if(JobType == FLS_17_DMU_WRITE)
      {
        /* [cover parentID={B7670FE3-88FD-4d64-B7F3-F16B62DD9146}]
           Is HW Busy ?
        [/cover] */
        if(Fls_lHWBusyCheck() == 0U)
        {
          /* Fls_Main_Wrire operation should be called  */
          /* [cover parentID={DD0D49E8-725F-40f8-9711-7D36E299ADD6}]
                      [/cover] */
          Fls_lMainWrite();
        }
        #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
        else
        {
          /*Invalid Interrupt Safety error */
          /* [cover parentID={16A47F4C-1538-4f78-8376-396D1E0AE07B}]
                  Raise Safety Error Invalid ISR
                  [/cover] */
          Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                             FLS_17_DMU_SID_ISR, FLS_17_DMU_SE_INVALID_ISR);
        }
        #endif
      }
      else
      {
        /*Avoid MISRA*/
      }
    }
  }
  #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  else /*If the Driver is IDLE or main write/erase is not called*/
  {
    #if  (FLS_17_DMU_CANCEL_API  ==  STD_ON)
    /* [cover parentID={9C16D23D-EED3-4feb-9D63-1E138E1BDD6F}]
     [/cover] */
    if(Fls_17_Dmu_JobCancelFlag == FLS_DMU_CANCEL_STATE)
    {

      /* [cover parentID={63ABB013-3158-4fca-8D25-127410F2D969}]
      [/cover] */
      Fls_17_Dmu_JobCancelFlag = FLS_DMU_CANCEL_RESET;
    }
    else
    #endif
    {
      /*Invalid Interrupt Safety error */
      /* [cover parentID={16A47F4C-1538-4f78-8376-396D1E0AE07B}]
      Raise Safety Error Invalid ISR
      [/cover] */
      Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                          FLS_17_DMU_SID_ISR, FLS_17_DMU_SE_INVALID_ISR);
    }
  }
  #endif
}
/* FLS_USE_INTERRUPTS == STD_ON */
#endif

/*******************************************************************************
** Traceability   : [cover parentID={08821C81-62AE-44a8-A9FC-E8F21739A886}]   **
**                                                                            **
** Syntax : static void Fls_lErrorHandler(const uint8 JobType)                **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : JobType                                                  **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : This routine is called when error occurred during            **
**               flash operations                                             **
*******************************************************************************/
static void Fls_lErrorHandler(const uint8 JobType)
{
  Fls_17_Dmu_StateType  *StatePtr;
  uint32 BitChange;

  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;

  /* [cover parentID={B6DFB935-DCBC-4085-8714-C4B127C0034A}]
  Is the ongoing job type equal to erase?
  [/cover] */
  if(JobType == FLS_17_DMU_ERASE)
  {
    /* [cover parentID={DDB34D8E-C828-4ae0-9154-EEC5ED9F8A8A}]
    Reset the Erase Job started status
    [/cover] */
    StatePtr->JobStarted.Erase = 0U;
  }
  /* [cover parentID={ECB56FB8-A9AA-4d1e-B987-4CF1DA3C4969}]
  Is ongoing job equal to write?
  [/cover] */
  else if(JobType == FLS_17_DMU_WRITE)
  {
    /* [cover parentID={C1E62E3A-E79C-4623-A8EF-47AA5D18F442}]
    Reset the Write Job started status
    [/cover] */
    StatePtr->JobStarted.Write = 0U;
  }
  else
  {
    /* Avoid MISRA 60 */
  }

  /* Clear the failed Job  */
  /* [cover parentID={FEB56CFC-8EF2-43b0-A7A4-341FA6BAE559}]
   Reset the Job status
  [/cover] */
  if(StatePtr->FlsJobType == JobType)
  {
    /* [cover parentID={00E2177E-AB85-4db3-959F-CAE84223C6BE}]
       Reset the Job status
      [/cover] */
    StatePtr->FlsJobType = FLS_17_DMU_NONE;
  }
  /* [cover parentID={2FEEDAEA-263F-4340-B44A-6067DDC65352}]
  Clear the failed job
  Set the job result to failed
  Reset job started status for the job failed
  Set that there is no job ongoing
  [/cover] */
  /* Update the global status variables */
  StatePtr->FlsJobResult = MEMIF_JOB_FAILED;

  /* Clear the errors status flags */
  BitChange = FLS_DMU_ERR_CLR;
  /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
   the object types as the address of the register is being passed.*/
  FLS_17_DMU_SFR_RUNTIME_WRITE32( \
                                  (volatile uint32 *)&DMU_HF_CLRE.U, \
                                  BitChange);

  /* [cover parentID={B0F6E07C-3940-490c-8D32-CF4B2D4A575E}]
  Is the Job Error Notification configured ?
  [/cover] */
  if(Fls_ConfigPtr->FlsJobErrorNotificationPtr != NULL_PTR)
  {
    /* [cover parentID={2FF6AA12-20B3-438d-A3D0-65E8DC8D3141}]
      [/cover] */
    Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = JobType;
    /* FlsJobErrorNotificationPtr should be called */
    (Fls_ConfigPtr->FlsJobErrorNotificationPtr)();
    Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_NO_JOB;
  }
}
/*******************************************************************************
** Traceability   : [cover parentID={CE9DC2FF-3376-4eb1-AC9C-9A983955F355}]   **
**                                                                            **
** Syntax: LOCAL_INLINE uint32 Fls_lGetPageAddress(const uint32 address)      **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : (uint32)address - address to be processed                **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : uint32 - Page start address                              **
**                                                                            **
** Description : This routine returns the start address of the page           **
*******************************************************************************/

LOCAL_INLINE uint32 Fls_lGetPageAddress(const uint32 address)
{
  return(address & FLS_PAGE_START_ADDR_MASK);
}

#if (FLS_17_DMU_USE_ERASESUSPEND == STD_ON)
/*******************************************************************************
** Traceability :[cover parentID={4A7C5E8C-7A6F-4153-8B12-08A01C465B1D}]      **
**                                                                            **
** Syntax: LOCAL_INLINE boolean Fls_lSpndTimeout(const uint32 TimeOutCount)   **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : TimeOutCount - Value of the Timeout count                **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : boolean                                                  **
**                                                                            **
** Description : This routine checks if erase suspend error or timeout error  **
**               occured                                                      **
*******************************************************************************/
LOCAL_INLINE boolean Fls_lSpndTimeout(const uint32 TimeOutCount)
{
  boolean RetVal;
  uint32 BitChange;

  /* [cover parentID={7C075E30-847C-4001-AB4A-93C86FCC3A04}]
  Is the suspend error present ?
  [/cover] */
  if (DMU_HF_SUSPEND.B.ERR == 1U) /*Suspend Error*/
  {
    /* [cover parentID={3C9E5EF2-E33D-43a2-9B3E-3B318D4BD80E}]
    Raise Safety Error
    [/cover] */
    #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_SUSPENDERASE,
                           FLS_17_DMU_SE_SUSPNDERASE_FAIL);
    #endif
    /* Clear Suspend Error status */

    BitChange = DMU_HF_SUSPEND.U | SUSPEND_CLR_OFF;
    DMU_HF_SUSPEND.U = BitChange;
    /* [cover parentID={5692C14A-E8CC-4aa0-873B-F5ADCE5F77BB}]
    Set the Return Value as TRUE
    [/cover] */
    RetVal = (boolean)TRUE;
  }
  /* [cover parentID={F74A8727-A427-4e64-B1FE-A2806E6E2B1F}]
  Timeout occured ?
  [/cover] */
  else if (TimeOutCount == 0U) /*Timeout */
  {
    #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
    /* [cover parentID={3C9E5EF2-E33D-43a2-9B3E-3B318D4BD80E}]
    Raise Safety Error
    [/cover] */
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_SUSPENDERASE,
                           FLS_17_DMU_SE_HW_TIMEOUT);
    #endif
    RetVal = (boolean)TRUE;
  }
  else
  {
    RetVal = (boolean)FALSE;
  }
  return (RetVal);
}
#endif

/*******************************************************************************
** Traceability : [cover parentID={D33AFD18-0DFE-461f-9059-2CA38024EFA0}]     **
**                                                                            **
** Syntax: LOCAL_INLINE boolean Fls_lPverChk(void)                            **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : boolean                                                  **
**                                                                            **
** Description : This routine checks if PVER error occured                    **
*******************************************************************************/
LOCAL_INLINE boolean Fls_lPverChk(void)
{
  uint32 TempFSR;
  boolean RetVal;

  TempFSR = (uint32)DMU_HF_ERRSR.U;

  /* [cover parentID={15EBAEE1-A6B6-44c8-BCBF-ABEC7042EA5A}]
  Is there any program verification error?
  [/cover] */
  if ((((TempFSR >> IFX_DMU_HF_ERRSR_PVER_OFF)) &
       IFX_DMU_HF_ERRSR_PVER_MSK) == 1U)
  {
    /* [cover parentID={1B47D2DE-E598-4508-AFC4-1C05062421B8}]
      [/cover] */
    RetVal = (boolean)TRUE;
  }
  else
  {
    /* [cover parentID={E86A24CA-2D27-4e29-BACC-0FB899726219}]
            [/cover] */
    RetVal = (boolean)FALSE;
  }
  return (RetVal);
}

#if(FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) || \
(FLS_17_DMU_SAFETY_ENABLE == STD_ON)
/*******************************************************************************
** Traceability : [cover parentID={92A72106-A5C8-4c69-A1F0-7D88AB31130E}]     **
**                                                                            **
** Syntax: LOCAL_INLINE uint8 Fls_lBusyDET_Read                               **
**                                ( const Fls_17_Dmu_StateType*const StatePtr)**
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : StatePtr : FLS Global variable structure                 **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : ErrorFlag - DET has occured (1) or not (0)               **
**                                                                            **
** Description : This routine detects if the new Read job can be accepted     **
*******************************************************************************/
LOCAL_INLINE uint8 Fls_lBusyDET_Read(const
                                     Fls_17_Dmu_StateType *const StatePtr )
{
  uint8 ErrorFlag;

  uint8 JobType;
  JobType = StatePtr->FlsJobType;
  ErrorFlag = 0U;

  /* No other job has been accepted */
  /* [cover parentID={05B7A427-ED62-44e5-9E3C-266C4674ED66}]
  Has any job been accepted?
  [/cover] */
  if(JobType != FLS_17_DMU_NONE)
  {
    /* [cover parentID={E58AB3EE-6386-4ca3-AEBB-19AB84D7A0F0}]
    Report DET error
    [/cover] */
    Fls_lReportError(
      FLS_17_DMU_SID_READ,
      FLS_17_DMU_E_BUSY);/* Report to DET */
    ErrorFlag = 1U;
  }

  return(ErrorFlag);
}

#if (FLS_17_DMU_COMPARE_API == STD_ON)
/*******************************************************************************
** Traceability : [cover parentID={250C5940-F4C3-47d7-985C-9D0B6AC86400}]     **
**                                                                            **
** Syntax: LOCAL_INLINE uint8 Fls_lBusyDET_Compare                            **
**                              ( const Fls_17_Dmu_StateType*const StatePtr)  **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : StatePtr : FLS Global variable structure                 **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : ErrorFlag - DET has occured (1) or not (0)               **
**                                                                            **
** Description : This routine detects if the new Compare job can be accepted  **
*******************************************************************************/
LOCAL_INLINE uint8 Fls_lBusyDET_Compare(
  const Fls_17_Dmu_StateType *const StatePtr )
{
  uint8 ErrorFlag;
  uint8 JobType;
  JobType = StatePtr->FlsJobType;
  ErrorFlag = 0U;

  /* No other job has been accepted */
  /* [cover parentID={6750A1BE-EC48-47a4-9BEA-2F53C694CA17}]
  Is the driver already busy
  [/cover] */
  if(JobType != FLS_17_DMU_NONE)
  {
    /* [cover parentID={22C549DB-C1CA-4ede-A38B-16DAD3DB289E}]
      Is the driver already busy
      [/cover] */
    Fls_lReportError(
      FLS_17_DMU_SID_COMPARE,
      FLS_17_DMU_E_BUSY);/* Report to DET */
    ErrorFlag = 1U;
  }

  return(ErrorFlag);
}
#endif

/*******************************************************************************
** Traceability     : [cover parentID={7C7AAF5E-BC04-4553-A68E-49C17D982385}] **
**                                                                            **
** Syntax: LOCAL_INLINE uint8 Fls_lBusyDET_Write                              **
**                            ( const Fls_17_Dmu_StateType*const StatePtr )   **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : StatePtr : FLS Global variable structure                 **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : ErrorFlag - DET has occured (1) or not (0)               **
**                                                                            **
** Description : This routine detects if the new Write job can be accepted    **
*******************************************************************************/
LOCAL_INLINE uint8 Fls_lBusyDET_Write(const Fls_17_Dmu_StateType *const
                                      StatePtr)
{
  uint8 ErrorFlag;
  uint8 JobType;
  JobType = StatePtr->FlsJobType;
  ErrorFlag = 0U;

  /* No other job has been accepted */
  /* [cover parentID={6D71398A-4FA4-4d16-9FA6-0A9A50AA7F83}]
  Has any job been accepted?
  [/cover] */
  if(JobType != FLS_17_DMU_NONE)
  {
    /* [cover parentID={40E62EA1-BCDF-4f8b-88AB-375EB517E9E8}]
    Report DET error
    [/cover] */
    Fls_lReportError(
      FLS_17_DMU_SID_WRITE,
      FLS_17_DMU_E_BUSY);/* Report to DET */
    ErrorFlag = 1U;
  }

  return(ErrorFlag);
}

/*******************************************************************************
** Traceability :[cover parentID={9B354613-0325-464d-B420-5B6E956717DF}]      **
**                                                                            **
** Syntax: LOCAL_INLINE uint8 Fls_lBusyDET_Erase                              **
**                                ( const Fls_17_Dmu_StateType*const StatePtr)**
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : StatePtr : FLS Global variable structure                 **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : ErrorFlag - DET has occured (1) or not (0)               **
**                                                                            **
** Description : This routine detects if the new Erase job can be accepted    **
*******************************************************************************/
LOCAL_INLINE uint8 Fls_lBusyDET_Erase(const Fls_17_Dmu_StateType *const
                                      StatePtr)
{
  uint8 ErrorFlag;

  uint8 JobType;
  JobType = StatePtr->FlsJobType;
  ErrorFlag = 0U;

  /* No other job has been accepted */
  /* [cover parentID={D879E651-37B8-438d-B783-04B815A40AEC}]
  Has any job been accepted?
  [/cover] */
  if(JobType != FLS_17_DMU_NONE)
  {
    /* [cover parentID={9767C368-A7A9-4736-ADBE-B75D51778C6E}]
    Report DET error
    [/cover] */
    Fls_lReportError(
      FLS_17_DMU_SID_ERASE,
      FLS_17_DMU_E_BUSY);/* Report to DET */
    ErrorFlag = 1U;
  }

  return(ErrorFlag);
}

/*******************************************************************************
** Traceability :     [cover parentID={744CAAD3-0ED4-46d3-AABB-8426E922A937}] **
**                                                                            **
** Syntax: static uint8 Fls_lUninitDET( const uint8 ServiceID )               **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : ServiceID - Service ID of the calling function           **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : ErrorFlag - DET has occured (1) or not (0)               **
**                                                                            **
** Description : This routine performs the UNINIT DET check                   **
*******************************************************************************/
static uint8 Fls_lUninitDET( const uint8 ServiceID )
{
  uint8 ErrorFlag;

  ErrorFlag = 0U;
  /* [cover parentID={E3127F70-89FD-4d77-A030-53527057D2CF}]
  Is the driver initialised?
  [/cover] */
  if((Fls_ConfigPtr == NULL_PTR) || (FLS_INITIALIZED != Fls_17_Dmu_InitStatus))
  {
    /* [cover parentID={23B1C635-DFEE-40d5-81E9-11F51B490B75}]
    Report to DET
    [/cover] */
    Fls_lReportError(ServiceID,
                     FLS_17_DMU_E_UNINIT);/* Report to DET */

    ErrorFlag = 1U;
  }

  return (ErrorFlag);
}

/*******************************************************************************
** Traceability :[cover parentID={F674110C-7572-4925-A85C-D7FBAA456FB0}]      **
**                                                                            **
** Syntax : LOCAL_INLINE Std_ReturnType Fls_lCheckEraseDet(                   **
**                             const Fls_17_Dmu_AddressType TargetAddress,    **
**                                  const  Fls_LengthType Length)             **
**                                                                            **
** Service ID:  None                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  TargetAddress and Length                                **
**                                                                            **
** Parameters (out): E_OK: No development Error detected                      **
**                   E_NOT_OK: development Error is detected                  **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                                                                            **
** Description : This routine checks for development error for                **
**               Fls_17_Dmu_Erase API                                         **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fls_lCheckEraseDet(
  const Fls_17_Dmu_AddressType TargetAddress,
  const Fls_17_Dmu_LengthType Length)
{
  const Fls_17_Dmu_StateType*   StatePtr;
  Std_ReturnType   ReturnValue;

  /* API called before initialization? */
  /* [cover parentID={703059FE-8BEE-4dfc-BA84-ED7289C1E42B}]
  Is Uninit DET error detected?
  [/cover] */
  if(Fls_lUninitDET(FLS_17_DMU_SID_ERASE) == 1U)
  {
    /* [cover parentID={A2F1E30A-8BF6-45ee-BE40-E3121C8BCFDE}]
       Set the Return Value as NOT OK
       [/cover] */

    ReturnValue = E_NOT_OK;
  }

  /* Checking whether given TargetAddress is valid or not */
  /* [cover parentID={2139AFD5-1DC3-4858-96ED-AAFC1324617E}]
  Is the given TargetAddress valid?
  [/cover] */
  else if(((uint32)TargetAddress >= FLS_17_DMU_TOTAL_SIZE) ||
          ((TargetAddress & FLS_MOD4K_MASK ) != 0U))
  {
    /* Report to DET */
    /* [cover parentID={685D8E78-D6D4-4c14-915B-9DA926422AF0}]
    Report DET error
    [/cover] */
    /* [cover parentID={A5CB3F8B-F837-492f-90DD-B32C11CD1477}][/cover] */


    Fls_lReportError(FLS_17_DMU_SID_ERASE, FLS_17_DMU_E_PARAM_ADDRESS);
    /* [cover parentID={A2F1E30A-8BF6-45ee-BE40-E3121C8BCFDE}]
    Set the Return Value as NOT OK
    [/cover] */

    ReturnValue = E_NOT_OK;
  }

  /* Checking whether given Length is valid or not */
  /* [cover parentID={F2A57A9F-57D6-434e-A014-BFBD76775BEA}]
  Is the given Length valid?
  [/cover] */

  else if((!(( Length >= FLS_ONE_VALUE) &&
             ( Length <= (FLS_17_DMU_TOTAL_SIZE - TargetAddress )))) ||
          ((Length & FLS_MOD4K_MASK) != 0U))
  {
    /* Report to DET */
    /* [cover parentID={685D8E78-D6D4-4c14-915B-9DA926422AF0}]
    Report DET error
    [/cover] */

    Fls_lReportError(FLS_17_DMU_SID_ERASE, FLS_17_DMU_E_PARAM_LENGTH);
    /* [cover parentID={A2F1E30A-8BF6-45ee-BE40-E3121C8BCFDE}]
    Set the Return Value as NOT OK
    [/cover] */
    ReturnValue = E_NOT_OK;
  }
  else
  {
    StatePtr = Fls_ConfigPtr->FlsStateVarPtr;

    /* [cover parentID={9FB3CD89-DC40-4700-BD76-18F6BDA3B3A4}]
    [/cover] */
    if(Fls_lBusyDET_Erase((const Fls_17_Dmu_StateType *)StatePtr) == 1U)
    {
      /* [cover parentID={A2F1E30A-8BF6-45ee-BE40-E3121C8BCFDE}]
      Set the Return Value as NOT OK
      [/cover] */
      ReturnValue = E_NOT_OK;
    }
    else
    {
      /* [cover parentID={4EA51479-668F-4d7f-A75C-754A712DE036}]
        [/cover] */
      ReturnValue = E_OK;
    }
  }
  /* [cover parentID={A93B90B0-2AEA-497e-A630-5DBACCB89CEF}]
  Return
  [/cover] */
  return ReturnValue;
}

/*******************************************************************************
** Traceability   : [cover parentID={009ADDB2-72CC-462a-953E-CB33EFC755D0}]   **
**                                                                            **
** Syntax : LOCAL_INLINE Std_ReturnType Fls_lCheckWriteDet(                   **
**                                      const Fls_AddressType TargetAddress,  **
**                                       const uint8 *const SourceAddressPtr, **
**                                     const Fls_LengthType Length)           **
**                                                                            **
** Service ID:  None                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  TargetAddress, SourceAddressPtr and Length              **
**                                                                            **
** Parameters (out): E_OK: No development Error detected                      **
**                   E_NOT_OK: development Error is detected                  **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                                                                            **
** Description : This routine checks for development error for                **
**               Fls_17_Dmu_Write API                                         **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fls_lCheckWriteDet(
  const Fls_17_Dmu_AddressType TargetAddress,
  const uint8 *const SourceAddressPtr,
  const Fls_17_Dmu_LengthType Length)

{
  Std_ReturnType  RetVal;

  RetVal = E_OK;

  /* API called before initialization */

  /* [cover parentID={BBF8A325-DA84-4202-929C-F48493B64529}]
  Is Uninit DET error detected?
  [/cover] */
  if(Fls_lUninitDET(FLS_17_DMU_SID_WRITE) == 1U)
  {
    RetVal = E_NOT_OK;
  }
  /* Checking whether given TargetAddress is valid or not */
  /* [cover parentID={10B65A6A-5954-48de-AE99-5341E74DCAD3}]
  Is the given TargetAddress valid?
  [/cover] */

  /* [cover parentID={10B65A6A-5954-48de-AE99-5341E74DCAD3}]
  Is the given TargetAddress valid?
  [/cover] */
  else if((((uint32)TargetAddress >= FLS_17_DMU_TOTAL_SIZE)) ||
          ((TargetAddress & FLS_PAGE_SIZE_MASK) != 0U) )
  {
    /* [cover parentID={6D67E4AE-5472-4009-AD54-6F7274A50002}]
    Report DET error
    [/cover] */

    /* Report to DET */
    Fls_lReportError(FLS_17_DMU_SID_WRITE, FLS_17_DMU_E_PARAM_ADDRESS);

    RetVal = E_NOT_OK;
  }
  /* Checking whether given Length is valid or not */
  /* [cover parentID={66607E1C-BF66-4580-8164-0B6F3E37B92F}]
  Is the given Length valid?
  [/cover] */

  else if((!(((uint32)Length >= FLS_ONE_VALUE) &&
             ((uint32)Length <= (FLS_17_DMU_TOTAL_SIZE - TargetAddress)))) ||
          ((Length & FLS_PAGE_SIZE_MASK) != 0U))
  {
    /* [cover parentID={6D67E4AE-5472-4009-AD54-6F7274A50002}]
    Report DET error
    [/cover] */

    /* Report to DET */
    Fls_lReportError(FLS_17_DMU_SID_WRITE, FLS_17_DMU_E_PARAM_LENGTH);

    RetVal = E_NOT_OK;
  }
  /* Check for Pointer to an application buffer */
  /* [cover parentID={EBB93C07-D227-4d1e-A803-487926749C49}]
  Is there a pointer to the application buffer?
  [/cover] */
  else if(SourceAddressPtr == NULL_PTR)
  {
    /* [cover parentID={6D67E4AE-5472-4009-AD54-6F7274A50002}]
    Report DET error
    [/cover] */

    /* Report to DET */
    Fls_lReportError(FLS_17_DMU_SID_WRITE, FLS_17_DMU_E_PARAM_DATA);

    RetVal = E_NOT_OK;
  }
  else
  {
    /* dummy else */
  }

  /* [cover parentID={9B7A1A6F-658D-445b-B2E0-0E20E88BFFF9}]
  Return
  [/cover] */
  return RetVal;

}

#endif
/* FLS_17_DMU_DEV_ERROR_DETECT == STD_ON */

#if (FLS_17_DMU_TIMEOUT_SUPERVISION == STD_ON)
/*******************************************************************************
** Traceability :[cover parentID={98064BA1-6260-461c-8DA6-5730095C485C}]      **
**                                                                            **
** Syntax: static void Fls_lTimeOutMonitoring( const uint8 ServiceID )        **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : ServiceID - Service ID of the calling function           **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description : This routine performs the TIMEOUT DET check                  **
*******************************************************************************/
static void Fls_lTimeOutMonitoring(const uint8 ServiceID)
{
  const Fls_17_Dmu_StateType  *StatePtr;
  uint32 MeasuredTicks;
  uint8 ErrorFlag;
  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
  ErrorFlag = 0U;

  /* [cover parentID={62F8D639-4265-495c-85E5-53BBE225EE61}]
  Is Erase operation ongoing?
  [/cover] */
  if(StatePtr->FlsJobType == FLS_17_DMU_ERASE)
  {
    MeasuredTicks = Mcal_DelayGetTick() - StatePtr->FlsCmdStartTicks;
    /* [cover parentID={B2E54AE9-1CA6-46d6-BCC0-AF1CC0E21C56}]
    Is the elapsed ticks greater than the time recorded for one erase command?
    [/cover] */
    if (MeasuredTicks > StatePtr->FlsEraseCmdTimeoutTicks)
    {
      ErrorFlag = 1U;
    }
  }
  /* [cover parentID={061214B4-B74F-4d5a-9F8B-311888B43A24}]
  Is Write operation ongoing?
  [/cover] */
  if(StatePtr->FlsJobType == FLS_17_DMU_WRITE)
  {
    MeasuredTicks = Mcal_DelayGetTick() - StatePtr->FlsCmdStartTicks;
    /* [cover parentID={77FC62E9-7412-4f4f-87C6-5B9C2E2D7990}]
    Is the elapsed ticks greater than the time recorded for one write command?
    [/cover] */
    if (MeasuredTicks > StatePtr->FlsWriteCmdTimeoutTicks)
    {
      /* [cover parentID={C0ADBB9E-4831-4293-A5C9-A0BB73FBBE31}]
      Set the error flag
      [/cover] */
      ErrorFlag = 1U;
    }
  }
  /* [cover parentID={48B85ABB-926D-41a7-89BE-F85F0DB7B001}]
  Is the error flag set ?
  [/cover] */
  if(ErrorFlag == 1U)
  {
    #if(MCAL_AR_VERSION == MCAL_AR_440)
      #if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
      /* Report Runtime error code to Mcal_Wrapper */
      /* [cover parentID={4BC03A63-AD1D-4cef-9621-03DC55BF0B59}]
      Report runtime error FLS_17_DMU_E_TIMEOUT
      [/cover] */
      (void)Mcal_Wrapper_Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                            FLS_17_DMU_INSTANCE_ID,
                            ServiceID,
                            FLS_17_DMU_E_TIMEOUT);
      #endif
    #else
      /* Report timeout DET*/
      /* [cover parentID={75771AE4-657F-43bf-BBA3-A601D7D6E46E}]
      Report FLS_17_DMU_E_TIMEOUT error
      [/cover] */
      Fls_lReportError(ServiceID,FLS_17_DMU_E_TIMEOUT);
    #endif
    /* [cover parentID={DF4D9AE9-D2B4-4600-9AAE-E10B007D2F50}]
    Call error handler to raise error notification and reset the
    job status variables [/cover] */
    Fls_lErrorHandler(StatePtr->FlsJobType);
  }
  #if ((MCAL_AR_VERSION == MCAL_AR_440) && \
  (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_OFF))
  UNUSED_PARAMETER(ServiceID);
  #endif

}
#endif

#if ( FLS_17_DMU_ERASE_VERIFICATION == STD_ON)
/*******************************************************************************
** Traceability :  [cover parentID={02694C60-A685-40e9-A517-AEACCDE8F330}]    **
**                                                                            **
** Syntax: LOCAL_INLINE Std_ReturnType Fls_lPageEraseCheck(                   **
**                                            uint32* const AddrCheckPtr,     **
**                                             const uint32  Length,          **
**                                            const uint8   ServiceID)        **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : AddrCheckPtr - address of the page, Length - page length **
**                   ServiceID - Service ID of the API for the DET            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK - page was erased correctly                         **
**                   E_NOT_OK - Page was not erased correctly                 **
**                                                                            **
** Description : Checks if the page was erased correctly                      **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fls_lPageEraseCheck(uint32 *const AddrCheckPtr,
    const uint32 Length,
    const uint8 ServiceID)
{
  Std_ReturnType  RetVal;
  uint8 Loop;
  uint8 PageLength;
  uint32 BitChange;
  uint32 ErrorFlag = 0U;
  const uint64 *SourcePtr;
  uint64 PageData;
  RetVal = E_OK;
  Loop = 0U;
  /* [cover parentID={700EEDE6-8445-4d2e-A797-6A387D7FF21D}]
         [/cover] */
  /*Clear the ECC status bits by writing DMU_HF_ECCC.CLR with 11b to clear
  AERM bit*/
  BitChange = DMU_HF_ECCC.U | FLS_DMU_ECCC_CLR;

  /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
     the object types as the address of the register is being passed.*/
  FLS_17_DMU_LIB_RUNTIME_WRITEPERIPENDINITPROTREG((volatile uint32 *)\
                                                     &DMU_HF_ECCC.U,BitChange);
  /* [cover parentID={991AA291-EAFF-4a9e-AF2F-57A8D0D6B5C7}]
      [/cover] */
  if( (Length <= (FLS_17_DMU_BURST_PAGE_SIZE - FLS_17_DMU_PAGE_SIZE)) ||
      /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from pointer to uint32 is
      required to access the FLASH address/target address. No memory alignment
      issues. */
      /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from pointer to uint32
      type is required to access the FLASH address/target address which
      is defined as uint32. No memory alignment issues.*/
      ((((uint32)AddrCheckPtr) & (FLS_17_DMU_BURST_PAGE_SIZE - 1U)) != 0U) )
  {
    /* [cover parentID={49D2A803-672D-4af8-B15F-8C7F333D8CE4}]
          [/cover] */
    PageLength = FLS_17_DMU_PAGE_SIZE;
  }
  else
  {
    /* [cover parentID={C2A415CA-2664-4bf1-854C-C58482C32FD2}]
       [/cover] */
    PageLength = FLS_17_DMU_BURST_PAGE_SIZE;
  }
  /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to access
  flash address being passed and to read one page at a time */
  /*MISRA2012_RULE_1_3_JUSTIFICATION: Pointer cast is for optimized read
  operation (8 bytes per read). The data is read from the flash address passed.
  The access is checked to be within the valid memory access hence no
  occurrence of undefined behaviour*/
  SourcePtr = (uint64*)AddrCheckPtr;
  while(Loop < (PageLength / FLS_17_DMU_PAGE_SIZE))
  {
    PageData = (*SourcePtr);
    /* DSYNC() is added to avoid compiler optimization (re-ordering of DFlash
    read and ECC error check in Fls_lChkBitErrors())*/
    DSYNC();
    SourcePtr++;
    Loop++;
    /* [cover parentID={FAFBD17A-E662-470c-AD11-0F53B47E676F}]
    [/cover] */
    if(FLS_17_DMU_DEFAULT_ERASEVALUE != PageData)
    {
       /* [cover parentID={8AB2103F-4C42-472b-A512-8874F36F6AD8}]
      [/cover] */
      ErrorFlag = 1U;
      Loop = PageLength / FLS_17_DMU_PAGE_SIZE;
    }
  }
  /* Check for Non-correctable ECC errors during the above check */
  /* [cover parentID={002085F0-05CA-4f83-A266-731FE44D7C46}]
  [/cover] */
  ErrorFlag |= Fls_lChkBitErrors();
  if(ErrorFlag != 0U)
  {
    #if(MCAL_AR_VERSION == MCAL_AR_440)
      #if (FLS_17_DMU_ERASE_VERIFY_REPORT == STD_ON)
      (void)Mcal_Wrapper_Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                            FLS_17_DMU_INSTANCE_ID,
                            ServiceID,
                            FLS_17_DMU_E_VERIFY_ERASE_FAILED);
      #endif
    #else
      /* Report to DET */
      /* [cover parentID={237C2A16-31DB-43d6-83A4-7C0AC257FC39}]
      [/cover] */
      Fls_lReportError(ServiceID,
                         FLS_17_DMU_E_VERIFY_ERASE_FAILED);
    #endif
    RetVal = E_NOT_OK;
  }
  #if ((MCAL_AR_VERSION == MCAL_AR_440) && \
  (FLS_17_DMU_ERASE_VERIFY_REPORT == STD_OFF))
  UNUSED_PARAMETER(ServiceID);
  #endif
  return RetVal;
}
#endif

/*******************************************************************************
** Traceability :[cover parentID={A6F30336-23EC-46c9-A9FF-E59694FAAA03}]      **
**                                                                            **
** Syntax:LOCAL_INLINE uint8 Fls_lGetWriteMode(void);                         **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : FLS_17_DMU_PAGE_WRITE - Page write to be done            **
**                   FLS_17_DMU_BURST_WRITE - Burst write to be done          **
**                                                                            **
** Description : This function checks whether Burst Write can be performed or **
**               Page Write has to be performed                               **
*******************************************************************************/
LOCAL_INLINE uint8 Fls_lGetWriteMode(void)
{
  const Fls_17_Dmu_StateType   *StatePtr;
  uint8           RetVal;

  RetVal = FLS_17_DMU_BURST_WRITE;
  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
  /* [cover parentID={33755848-C021-4ef6-A7C2-709E557E2C91}]
  Is the write length less than the defined page burst size?
  [/cover] */
  if((StatePtr->FlsWriteLength <=
      (FLS_17_DMU_BURST_PAGE_SIZE - FLS_17_DMU_PAGE_SIZE))
      || ((StatePtr->FlsWriteAddress
           & (FLS_17_DMU_BURST_PAGE_SIZE - 1U)) != 0U))
  {
    /* [cover parentID={5CCD8DC2-8504-4578-92FB-CC0D480AAC62}]
      [/cover] */
    RetVal = FLS_17_DMU_PAGE_WRITE;
  }

  return RetVal;
}

/*******************************************************************************
** Traceability :[cover parentID={F5E03FEE-EA96-4893-BF64-DD240CF917AE}]      **
**                                                                            **
** Syntax:LOCAL_INLINE Fls_LengthType Fls_lGetReadModeLength(void);           **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : max read length as per read mode                         **
**                                                                            **
** Description : Get max read length according to the FLS mode                **
*******************************************************************************/
LOCAL_INLINE Fls_17_Dmu_LengthType Fls_lGetReadModeLength(void)
{
  const Fls_17_Dmu_StateType   *StatePtr;
  Fls_17_Dmu_LengthType  MaxRead;

  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
  MaxRead = Fls_ConfigPtr->FlsFastRead;

  /* [cover parentID={7F559EDA-D1C4-4181-BD16-4F8BD0DC689E}]
  Is the mode configred equals slow mode?
  [/cover] */
  if(StatePtr->FlsMode == MEMIF_MODE_SLOW)
  {
    /* [cover parentID={2938FE28-D5EE-4428-9CD5-93E82D3F5E9E}]
    Update the Maximum read to the slow read mode
    [/cover] */
    MaxRead = Fls_ConfigPtr->FlsSlowRead;
  }

  return MaxRead;
}

/*******************************************************************************
** Traceability : [cover parentID={ACA27314-E9B3-43c4-9C97-026F0C0AE667}]     **
**                                                                            **
** Syntax: LOCAL_INLINE uint32 Fls_lChkSeqProtErrors(void)                    **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Seq and protection bits of FSR                           **
**                                                                            **
** Description : Checks for seq and protection errors                         **
*******************************************************************************/
LOCAL_INLINE uint32 Fls_lChkSeqProtErrors(void)
{
  uint32 RetVal;

  RetVal = ((uint32)DMU_HF_ERRSR.U & FLS_PROER_SQER_ERROR);

  return RetVal;
}

/*******************************************************************************
** Traceability :[cover parentID={3F153B3F-0CBA-46e9-B9F0-3D543008C486}]      **
**                                                                            **
** Syntax: LOCAL_INLINE uint32 Fls_lChkOperError(void)                        **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : operational error bit of FSR                             **
**                                                                            **
** Description : Checks for operational error                                 **
*******************************************************************************/
LOCAL_INLINE uint32 Fls_lChkOperError(void)
{
  uint32 RetVal;


  RetVal = ((uint32)DMU_HF_ERRSR.U & FLS_OPER_ERROR);
  /* [cover parentID={76160973-4671-4f08-983C-A0DA155B3A88}]
    Check for operational error ?
    [/cover] */
  if(RetVal != 0U)
  {
    RetVal = FLS_OPER_ERROR;
    /* [cover parentID={4A4D8D8F-2D11-42ac-8371-6819C588FFD5}]
    Raise the illegal state notification
    [/cover] */

    if(Fls_ConfigPtr->FlsIllegalStateNotificationPtr != NULL_PTR)
    {
      /* FlsIllegalStateNotificationPtr should be called */
      /* [cover parentID={14189214-017C-4a1a-9E15-E475089C8157}]
          Raise the illegal state notification
          [/cover] */
      (Fls_ConfigPtr->FlsIllegalStateNotificationPtr)();
    }
  }

  return (RetVal);
}

/*******************************************************************************
** Traceability : [cover parentID={653BD8F9-D7EA-4a74-A8DB-5BDB014F51A3}]     **
**                                                                            **
** Syntax: LOCAL_INLINE uint32 Fls_lChkBitErrors(void)                        **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Non correctable bit of FSR                               **
**                                                                            **
** Description : Checks for double ECC errors                                 **
*******************************************************************************/
LOCAL_INLINE uint32 Fls_lChkBitErrors(void)
{
  uint32 RetVal;
  #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_OFF)
  uint32 BitChange;
  #endif
  /* [cover parentID={B6C1503A-B86D-450f-908C-EADA555D721D}]
  Return the ECC bit error status.
  [/cover] */
  /*API switch*/
  #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_ON)
  RetVal = ((uint32)DMU_HF_ECCS.U & FLS_ERRM_BIT_MASK);
  #else
  RetVal = ((uint32)DMU_HF_ECCS.U & FLS_AERM_BIT_MASK);
  #endif
  #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_OFF)
  /* [cover parentID={23B71B2C-3CC4-484c-A8A5-171F66FCBC61}]
    [/cover] */
  if(RetVal != 0U)
  {
    /* [cover parentID={618DA161-3B07-4899-A565-55CC84058ED4}]
      [/cover] */
    /*Clear the ECC status by writing HF_ECCC.CLR with 11b*/
    BitChange = DMU_HF_ECCC.U | FLS_DMU_ECCC_CLR;
    /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
    the object types as the address of the register is being passed.*/
    FLS_17_DMU_LIB_RUNTIME_WRITEPERIPENDINITPROTREG(\
        (volatile uint32 *)&DMU_HF_ECCC.U, \
        BitChange);
  }
  #endif
  return RetVal;
}

/*******************************************************************************
** Traceability : [cover parentID={70FF10EA-9B50-4b20-AB23-C14CF3AB0F80}]     **
**                                                                            **
** Syntax: LOCAL_INLINE uint32 Fls_lHWBusyCheck(void)                         **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Busy bit of FSR                                          **
**                                                                            **
** Description : Checks for Busy status of the Data Flash Bank                **
*******************************************************************************/
LOCAL_INLINE uint32 Fls_lHWBusyCheck(void)
{
  uint32 RetVal;

  RetVal = ((uint32)DMU_HF_STATUS.U & FLS_D0BUSY);

  return RetVal;
}

/*******************************************************************************
** Traceability : [cover parentID={679709F3-4A7F-48d6-A544-BE382E28FF2F}]     **
**                                                                            **
** Syntax: LOCAL_INLINE MemIf_ModeType Fls_lSetDefaultMode(void)              **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : MemIf_ModeType                                           **
**                                                                            **
** Description : Returns the default mode of FLS driver                       **
*******************************************************************************/
LOCAL_INLINE MemIf_ModeType Fls_lSetDefaultMode(void)
{
  return (Fls_ConfigPtr->FlsDefaultMode);
}

#if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON)|| \
(FLS_17_DMU_SAFETY_ENABLE == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={6D03B66B-576D-4850-ABCD-769EAFF88353}]   **
**                                                                            **
** Syntax          : LOCAL_INLINE void Fls_lReportError                       **
**                                (const uint8 Fls_Sid, const uint8 ErrorId)  **
**                                                                            **
** Description     : Function to report Safety Error and DET                  **
** [/cover]                                                                   **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : Fls_Sid - Service id of the caller API                   **
**                   ErrorId - ID of the error to be reported                 **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
*                                                                             **
*******************************************************************************/
static void Fls_lReportError(const uint8 Fls_Sid, const uint8 ErrorId)
{
  #if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON)
  (void)Det_ReportError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID, Fls_Sid,
                  ErrorId);
  #endif

  #if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID, Fls_Sid,
                         ErrorId);
  #endif
}
#endif/*End of Fls_lReportError*/


#define FLS_17_DMU_STOP_SEC_CODE_ASIL_B_LOCAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. Even though the memmap
   header is included multiple times, the contents of the file are protected
   from multiple definition / inclusion. */
#include "Fls_17_Dmu_MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
