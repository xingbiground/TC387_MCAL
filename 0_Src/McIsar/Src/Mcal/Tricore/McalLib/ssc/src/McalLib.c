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
**  FILENAME     : McalLib.c                                                  **
**                                                                            **
**  VERSION      : 41.0.0                                                     **
**                                                                            **
**  DATE         : 2023-05-16                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : MCAL Library source file                                   **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={4C08C419-6659-4ae1-A70F-A5C8FC62A22B}][/cover] */
/* [cover parentID={EBC12FA6-C2FB-416e-8518-7337947C6D63}][/cover] */
/* [cover parentID={ACBBD55B-CDB7-4936-BF3A-D2A247B8A6DF}][/cover] */
/* [cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}][/cover] */
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "IfxScu_reg.h"
#include "IfxScu_bf.h"
#include "IfxStm_reg.h"
#include "IfxCpu_reg.h"
#include "McalLib.h"
#include "SchM_McalLib.h"
/* Include Safety Error header definition */
#if(MCALLIB_SAFETY_ENABLE == STD_ON)
#include "Mcal_SafetyError.h"
#endif
/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/


/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
#define MCAL_PASSEQSHIFT                           (0xBU)  /* 11U */
#define MCAL_PASSWORD_SHIFT                        (0xCU)  /* 12U */
#define MCAL_LFSR_SHIFT                            (0xDU)  /* 13U */
#define MCAL_INVALID_ARGUMENT                      (0x0U)

/* Macros for Mcal_GetGlobalDsprAddress/Mcal_GetLocalDsprAddress */
#define MCAL_VALID_DSPR_MSB                        (0xDU)
/* Macros for Mcal_GetGlobalPsprAddress/Mcal_GetLocalPsprAddress */
#define MCAL_VALID_PSPR_MSB                        (0xCU)
#define MCAL_PSPR_ADDRESS_MASK                     (0xF0100000U)
#define MCAL_PSPR_ADDRESS_MASK_N                   (~MCAL_PSPR_ADDRESS_MASK)
#define MCAL_INVALID_CPU_ID_5                      (0x5U)
#define MCAL_SHIFT_UPPER_NIBBLE                    (0x1CU)/* Bit position 28 */

#if (MCAL_NO_OF_CORES > 5U )
#define MCAL_INVALID_PSPR_ADDR                     (0x0U)
#endif

#if (MCAL_NO_OF_CORES > 5U )
#define MCAL_INVALID_DSPR_ADDR                     (0x0U)
#endif

/* Macros for ENDINIT protection */
#define MCAL_ENDINIT_WDT_PWD_INV                   (0x3FU)
#define MCAL_ENDINIT_WDT_PWD_MASK                  (0x0000FFFCU)

/* Macros for Peripheral ENDINIT protection */
#define MCAL_PER_ENDINIT_PROTECTED                 (0x1U)
#define MCAL_PER_ENDINIT_WDT_TIMER_REL             (0xFFFC0000U)

/* Macros for Safety ENDINIT protection */
#define MCAL_SAFETY_ENDINIT_PROTECTED              (0x1U)
#define MCAL_SAFETY_ENDINIT_WDT_TIMER_REL          (0xFFFC0000U)
#define MCAL_DEFAULT_MASK_VALUE                    (uint32)(0xFFFFFFFFU)
#define MCAL_SPINLOCK_DEFAULT_TIMEOUT              (uint32)(0x2710U)

/* Macros for CPUWDT ENDINIT protection */
#define MCAL_ENDINIT_RELOAD_MASK                   (0xFFFF0000U)
#define MCAL_CPUWDTSR_TIMER_MASK                   (0xFFFF0000U)
#define MCAL_ENDINIT_TIMEOUT_VALUE                 (0x0000FFFCU)
#define MCAL_CPUWDT_TIMER_VALUE_MAX                (0xFFFFU)

#define MCAL_CPUWDTCON0_UNLOCK                     (0x1U)
#define MCAL_CPUWDTCON0_LOCK                       (0x3U)
#define MCAL_CPUWDTCON0_DISABLE_ENDINIT            (0x2U)
#define MCAL_CPUWDTCON0_ENABLE_ENDINIT             (0x3U)

#define MCAL_AUTO_PWD_SEQ_ENABLED                  (0x1U)
#define MCAL_TIMER_CHECK_ENABLED                   (0x1U)

/* Macros for STM frequency calculation */
#define MCAL_STM_TIMER_RESOL_ZERO                  (0x0U)
#define MCAL_STMCLK_DISABLED                       (0x0U)
#define MCAL_PLL0_CLK_SRC0_FREQ                    (0x1U)
#define MCAL_OSC0_CLK_PLL0_FREQ                    (0x1U)
#define MCAL_SYS_CLK_PLL0_FREQ                     (0x2U)
#define MCAL_RESOLUTION_U                          (0x3E8U) /* 1000U  */
#define MCAL_OSCVAL_MHz                            (0x10U)  /* 16 Mhz */
#define MCAL_OSCFREQ_MHz                           (0x1U)   /* 1 Mhz  */

/* Macros for Spinlock address*/
#define SPINLOCKFREE                               (0x0U)
/*SpinLock is Available*/
#define SPINLOCKBUSY                               (0x1U)
/*SpinLock is Not Available*/
#define MCAL_TIMEOUT                               (0x3E8U) /* 1000U */

#define MCAL_UPDATE_NEWPASSWORD                    (0x1U)
#define MCAL_NOUPDATE_PASSWORD                     (0x0U)
#define MCAL_DUMMY_PASSWORD                        (0x0U)
#define MCAL_SETENDINITPROTECTION                  (0x1U)
#define MCAL_RESETENDINITPROTECTION                (0x0U)
#define MCAL_32BIT_ACCESS                          (0x0U)
#define MCAL_16BIT_ACCESS                          (0x1U)
#define MCAL_16BIT_MAX_ADDR                        (0xFFFFU)

/* Get the current STM Tick */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro defined for easy
 * readability in code. No side effects foreseen by violating this MISRA rule.
 */
#define MCAL_GET_STM_TICK()                        (MODULE_STM0.TIM0.U)
/*******************************************************************************
**                      Imported Compiler Switch Checks                       **
*******************************************************************************/
/* [cover parentID={491F788E-197E-4a54-B1C8-2902F835C275}]McalLib version
   check[/cover] */
#ifndef MCALLIB_SW_MAJOR_VERSION
 #error "MCALLIB_SW_MAJOR_VERSION is not defined. "
#endif

#ifndef MCALLIB_SW_MINOR_VERSION
 #error "MCALLIB_SW_MINOR_VERSION is not defined. "
#endif

#ifndef MCALLIB_SW_PATCH_VERSION
 #error "MCALLIB_SW_PATCH_VERSION is not defined. "
#endif

/* Check for Correct inclusion of headers */
#if ( MCALLIB_SW_MAJOR_VERSION != 20U )
 #error "MCALLIB_SW_MAJOR_VERSION does not match. "
#endif

#if ( MCALLIB_SW_MINOR_VERSION != 25U )
 #error "MCALLIB_SW_MINOR_VERSION does not match. "
#endif

#if (MCALLIB_SW_PATCH_VERSION != 0U)
 #error "MCALLIB_SW_PATCH_VERSION does not match."
#endif
/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]Memory Mapping
   [/cover] */
/* [cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]Memory mapping for
   callout code is not applicable for McalLib[/cover] */
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]Memory mapping for
    configuration data is not applicable for McalLib[/cover] */
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]Memory mapping for
    variables[/cover] */
/* [cover parentID={D11431C7-DF20-470b-8994-6A31F882BA7C}][/cover] */
#define MCALLIB_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "McalLib_MemMap.h"

static uint32 Mcal_StmTimerResolution;

static volatile uint32 Mcal_LockAddressSiecon0;

static volatile uint32 Mcal_LockAddressEicon0;

/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]Memory mapping for
    variables[/cover] */
#define MCALLIB_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "McalLib_MemMap.h"
/* [cover parentID={1A65EADD-AFD0-4845-B2D2-8257E086DD67}]No user mode macro
used [/cover] */

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]No user mode macro
used [/cover] */
#define MCALLIB_START_SEC_CONST_ASIL_B_GLOBAL_8
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "McalLib_MemMap.h"

static const uint8 Mcal_kCoreXMemSegment[MCAL_COREID_MAX_VALUE + 0x1U] =
{
  MCAL_CORE0_MEM_SEGMENT, /* Index 0 */
  #if ( MCAL_NO_OF_CORES > 1U )
  MCAL_CORE1_MEM_SEGMENT, /* Index 1 */
  #if ( MCAL_NO_OF_CORES > 2U )
  MCAL_CORE2_MEM_SEGMENT, /* Index 2 */
  #if ( MCAL_NO_OF_CORES > 3U )
  MCAL_CORE3_MEM_SEGMENT, /* Index 3 */
  #if ( MCAL_NO_OF_CORES > 4U )
  MCAL_CORE4_MEM_SEGMENT, /* Index 4 */
  #if ( MCAL_NO_OF_CORES > 5U )
  MCAL_MEM_SEGMENT2_MSB,  /* Index 5 */
  MCAL_CORE5_MEM_SEGMENT  /* Index 6 */
  #endif
  #endif
  #endif
  #endif
  #endif
};

#define MCALLIB_STOP_SEC_CONST_ASIL_B_GLOBAL_8
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "McalLib_MemMap.h"
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond
  32 characters in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond
  32 characters in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond
  32 characters in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond
  32 characters in generated code due to Autosar Naming constraints.*/
#define MCALLIB_START_SEC_CONST_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "McalLib_MemMap.h"

static const uint32 Mcal_kDsprEndAddress[MCAL_COREID_MAX_VALUE + 0x1U] =
{
  MCAL_DSPR0_END_ADDR,
  #if ( MCAL_NO_OF_CORES > 1U )
  MCAL_DSPR1_END_ADDR,
  #if ( MCAL_NO_OF_CORES > 2U )
  MCAL_DSPR2_END_ADDR,
  #if ( MCAL_NO_OF_CORES > 3U )
  MCAL_DSPR3_END_ADDR,
  #if ( MCAL_NO_OF_CORES > 4U )
  MCAL_DSPR4_END_ADDR,
  #if ( MCAL_NO_OF_CORES > 5U )
  MCAL_INVALID_DSPR_ADDR,
  MCAL_DSPR5_END_ADDR
  #endif
  #endif
  #endif
  #endif
  #endif
};

static const uint32 Mcal_kPsprLocalEndAddress[MCAL_COREID_MAX_VALUE + 0x1U] =
{
  MCAL_LOCAL_PSPR0_END_ADDR,
  #if ( MCAL_NO_OF_CORES > 1U )
  MCAL_LOCAL_PSPR1_END_ADDR,
  #if ( MCAL_NO_OF_CORES > 2U )
  MCAL_LOCAL_PSPR2_END_ADDR,
  #if ( MCAL_NO_OF_CORES > 3U )
  MCAL_LOCAL_PSPR3_END_ADDR,
  #if ( MCAL_NO_OF_CORES > 4U )
  MCAL_LOCAL_PSPR4_END_ADDR,
  #if ( MCAL_NO_OF_CORES > 5U )
  MCAL_INVALID_PSPR_ADDR,
  MCAL_LOCAL_PSPR5_END_ADDR
  #endif
  #endif
  #endif
  #endif
  #endif
};

static const uint32 Mcal_kPsprGlobalEndAddress[MCAL_COREID_MAX_VALUE + 0x1U] =
{
  MCAL_PSPR0_END_ADDR,
  #if ( MCAL_NO_OF_CORES > 1U )
  MCAL_PSPR1_END_ADDR,
  #if ( MCAL_NO_OF_CORES > 2U )
  MCAL_PSPR2_END_ADDR,
  #if ( MCAL_NO_OF_CORES > 3U )
  MCAL_PSPR3_END_ADDR,
  #if ( MCAL_NO_OF_CORES > 4U )
  MCAL_PSPR4_END_ADDR,
  #if ( MCAL_NO_OF_CORES > 5U )
  MCAL_INVALID_PSPR_ADDR,
  MCAL_PSPR5_END_ADDR
  #endif
  #endif
  #endif
  #endif
  #endif
};

static const uint32 Mcal_kPsprGlobalBaseAddress[MCAL_COREID_MAX_VALUE + 0x1U] =
{
  MCAL_PSPR0_BASE_ADDR,
  #if ( MCAL_NO_OF_CORES > 1U )
  MCAL_PSPR1_BASE_ADDR,
  #if ( MCAL_NO_OF_CORES > 2U )
  MCAL_PSPR2_BASE_ADDR,
  #if ( MCAL_NO_OF_CORES > 3U )
  MCAL_PSPR3_BASE_ADDR,
  #if ( MCAL_NO_OF_CORES > 4U )
  MCAL_PSPR4_BASE_ADDR,
  #if ( MCAL_NO_OF_CORES > 5U )
  MCAL_INVALID_PSPR_ADDR,
  MCAL_PSPR5_BASE_ADDR
  #endif
  #endif
  #endif
  #endif
  #endif
};

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond
  32 characters in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond
  32 characters in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond
  32 characters in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond
  32 characters in generated code due to Autosar Naming constraints.*/
#define MCALLIB_STOP_SEC_CONST_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "McalLib_MemMap.h"
/* [cover parentID={1A65EADD-AFD0-4845-B2D2-8257E086DD67}]No user mode macro
  used [/cover] */

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/
/* Internal Structure definition for McalLib driver
 * McalLib_CpuEndInitRetType is used to store the timer reload value at the
 * time of EndInit reset and the current password in CON0 SFR.
 */
/*[cover parentID={D3F3A208-D26C-47a1-BDF9-5BFAF6406291}][/cover]*/
typedef struct
{
  uint32 TimerRelValAtReset; /* Holds timer reload value at reset */
  uint32 Password;           /* Decrypted Password read from SFR */
} McalLib_CpuEndInitRetType;
/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]Memory mapping for
   code[/cover]*/
#define MCALLIB_START_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "McalLib_MemMap.h"

LOCAL_INLINE uint32 Mcal_lGetCpuIndex(void);
LOCAL_INLINE uint16 Mcal_lDecryptPw(const uint32 Value);
LOCAL_INLINE uint32 Mcal_lDelayResetTickCalibration(const uint8 ApiId);
LOCAL_INLINE uint32 Mcal_lCpuRelValue(const uint32 CpuIndex,
                                      const uint32 WdtCpuCon0Value);
LOCAL_INLINE uint32 Mcal_lCpuPwSequence(const uint32 CpuIndex,
                                        const uint32 WdtCpuCon0Value);
LOCAL_INLINE void Mcal_lWriteSafetyEndInitProtection
                                    (volatile void* const RegAddress,
                                     const uint32 DataValue,
                                     const uint32 Mask,
                                     const uint8  Accesstype,
                                     const uint8  ApiId);
static McalLib_CpuEndInitRetType Mcal_lUpdateCpuEndInit(const uint32  NewPassword,
                                     const uint32  CoreIdIndex,
                                     const uint32  TimerRelValAtReset,
                                     const boolean UpdatePassword,
                                     const boolean SetResetProtection);
static uint32 Mcal_lUpdatePeripheralEndInit(const uint32 NewPassword,
                                            const boolean UpdatePassword,
                                            const boolean SetResetProtection);
static uint32 Mcal_lUpdateSafetyEndInit(const uint32 NewPassword,
                                        const boolean UpdatePassword,
                                        const boolean SetResetProtection);
LOCAL_INLINE uint32 Mcal_lCalculateTimerReloadVal(const uint32 CoreId,
                                     const uint32 TimerRelValAtReset,
                                     const boolean SetResetProtection);
static void Mcal_lGetSpinlock(volatile uint32 *const LockAddress,
                              const uint32 Timeout, const uint8 ApiId);
LOCAL_INLINE void Mcal_lReleaseSpinlock(volatile uint32 * const LockAddress);
#if (MCALLIB_SAFETY_ENABLE == STD_ON)
static void Mcal_lReportError(const uint8 ApiId, const uint8 ErrorId);
#endif
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]Memory mapping for
   code[/cover]*/
#define MCALLIB_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "McalLib_MemMap.h"

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/


/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]Memory mapping for
   code[/cover]*/
#define MCALLIB_START_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "McalLib_MemMap.h"
/*******************************************************************************
** Traceability     : [cover parentID={8366FBD5-CC94-4b46-84C1-1587582733A4}] **
**                                                                            **
** Syntax           : uint32 Mcal_GetCpuWdgPassword (void)                    **
**                                                                            **
** Description      : This interface is used by applications to retrieve the  **
**                    endinit password currently installed in the watchdog of **
**                    the CPU they are currently executing on.                **
**                                                                            **
** Service ID       : 0x88                                                   **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Currently installed password                            **
**                                                                            **
*******************************************************************************/
uint32 Mcal_GetCpuWdgPassword(void)
{
  uint32 Password;
  /*[cover parentID={7ABA6FAF-7F08-48b8-B059-2F99F2798124}]Retrieve cpuindex
     of current core[/cover] */
  uint32 CoreIdIndex = Mcal_lGetCpuIndex();

  /* Retrieve the encrypted(partially inverted) password from the register */
  /* [cover parentID={714F01A3-0913-4052-9F62-D4E907791D82}]Extract the
      password content from WDTCPUxCON0 reg PW bit[/cover] */
  Password = Mcal_GetBitAtomic(MODULE_SCU.WDTCPU[CoreIdIndex].CON0.U,
                               IFX_SCU_WDTCPU_CON0_PW_OFF,
                               IFX_SCU_WDTCPU_CON0_PW_LEN);
  /* Decrypt the password (invert bits 0:5) */
  /* password by inverting bits 0:5[/cover] */
  /* [cover parentID={A820A825-B92B-4ff8-87F0-D28F16C2F619}]Decrypt the
      password by inverting bits 0:5[/cover] */
  Password = Password ^ (uint32)MCAL_ENDINIT_WDT_PWD_INV;
  /* [cover parentID={E9117C0D-92CC-41a9-90CB-BE6DBC90F5C3}]Return  password
     [/cover] */
  return (Password);
}

/*******************************************************************************
** Traceability     : [cover parentID={C5FA4346-076A-4fce-AC48-91FD7E7C4CBF}] **
**                                                                            **
** Syntax           : uint32 Mcal_SetCpuWdgPassword (const uint32 Password)   **
**                                                                            **
** Description      : This interface is used by applications to install a     **
**                    specified endinit password in the endinit registers of  **
**                    the watchdog of the CPU they are executing on.          **
**                    Previously stored data in the PW bitfield of            **
**                    WDTCPUxCON0 register is returned back to the caller     **
**                                                                            **
** Service ID       : 0x85                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant on same CPU, Reentrant on other CPUs      **
**                                                                            **
** Parameters(in)   : Password - New password to be installed into            **
**                    WDTCPUxCON0 register                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : return the previous installed password                  **
**                                                                            **
*******************************************************************************/
uint32 Mcal_SetCpuWdgPassword(const uint32 Password)
{
  McalLib_CpuEndInitRetType CpuEndInitRet;
  uint32 UpdatedPassword = (Password & (uint32)IFX_SCU_WDTCPU_CON0_PW_MSK);
  /* [cover parentID={C3A1147A-CF1C-480d-8134-75BEDE663A14}]
   * Reterive CoreIdIndex
   * [/cover] */
  uint32 CoreId = Mcal_lGetCpuIndex();

  /* Enter critical section */
  /* [cover parentID={4D3611DD-6749-4cc3-81CB-EADA6F27831F}]Enter crtical
        section for updating CpuWdg password[/cover] */
  SchM_Enter_McalLib_CpuEndInit();

  /* Update the new password */
  /* [cover parentID={D48BC0AA-A835-4f73-9183-5A9BB88B8066}]
   * Update the new password
   * [/cover] */
  CpuEndInitRet = Mcal_lUpdateCpuEndInit(UpdatedPassword, CoreId, 0x0U,
                                         MCAL_UPDATE_NEWPASSWORD,
                                         MCAL_RESETENDINITPROTECTION);

  /* Exit critical section */
  /* [cover parentID={3A2FCF58-EB50-44b4-AF19-75E0C63B690D}]Exit critical
     section[/cover] */
  SchM_Exit_McalLib_CpuEndInit();

  /* [cover parentID={B493E147-E76E-4186-9FDC-70714AA64E31}]
   * Return Previously installed password
   * [/cover] */
  return (CpuEndInitRet.Password);
}

/*******************************************************************************
** Traceability     : [cover parentID={1619BFC3-44C7-4fe5-84B7-EA6DC8570B6A}] **
**                                                                            **
** Syntax           : void Mcal_WriteCpuEndInitProtReg                        **
**                   (volatile void* const RegAddress, const uint32 DataValue)**
**                                                                            **
** Description      : This interface is used by applications to resume        **
**                    protection of CPU endinit protected registers of the    **
**                    CPU they are executing on. This interface also supports **
**                    write access to CPU endinit protected CSFRs.            **
**                                                                            **
** Service ID       : 0x7E                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : RegAddress - CPU Endinit protected register address     **
**                    DataValue - Value to be written to the register located **
**                    at RegAddress.                                          **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void Mcal_WriteCpuEndInitProtReg(volatile void* const RegAddress,
                                  const uint32 DataValue)
{
  McalLib_CpuEndInitRetType CpuEndInitRet;
  uint32 CoreId;
  /* MISRA2012_RULE_11_6_JUSTIFICATION: The address of the register is
   * compared against CSFR register offset.
   * There are no other operation performed, hence this convesion
   * does not cause any issue */
  uint32 TempAddr = (uint32)RegAddress;

  /* [cover parentID={E178D5D6-9647-4bde-9B6D-A42416AC714B}]
     If SAFETY Error Check is Enabled[/cover] */
  #if (MCALLIB_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={AC213D25-D820-4cef-A724-CA3EB87EB2C6}]
      Check if input address is null pointer[/cover] */
  if ((RegAddress) == NULL_PTR)
  {
    /* [cover parentID={8AA5A630-14E4-444b-AF64-6702217F5C39}]
        Report error MCALLIB_E_PARAM_POINTER[/cover] */
    Mcal_lReportError(MCALLIB_SID_CPUENDINIT, MCALLIB_E_PARAM_POINTER);
  }
  /* [cover parentID={FE4D45F8-C269-41d8-A66C-28BF60649F7D}]
     If address is not null pointer [/cover] */
  else
  #endif
  {
    /* [cover parentID={5FC8A013-625D-433a-9381-7C74D60AA759}]
     * Retrieve cpuindex of current core
     * [/cover] */
    CoreId = Mcal_lGetCpuIndex();

    /* Enter critical section */
    /* [cover parentID={461765B3-4C5C-4a93-9F2B-8E85946F13B0}]
     * Enter critical section
     * [/cover] */
    SchM_Enter_McalLib_CpuEndInit();

    /* Reset CpuEndInit Protection */
    /* [cover parentID={2449C750-888D-4215-92C7-89A336D2BCF6}]
     * Reset CpuEndInit Protection
     * [/cover] */
    CpuEndInitRet = Mcal_lUpdateCpuEndInit(MCAL_DUMMY_PASSWORD, CoreId, 0x0U,
                                           MCAL_NOUPDATE_PASSWORD,
                                           MCAL_RESETENDINITPROTECTION);

    /* Update CPU Endinit protected register
     * Note: CPU specific registers are updated using MTCR
     */
    /* [cover parentID={FC76C818-3B35-46e8-8F71-06CAAA9B972B}]
     * Update CPU Endinit protected register
     * [/cover] */
    /* [cover parentID={9AB7EC4B-1C37-4b90-9D90-F7B9FE87F06E}][/cover] */
    if (TempAddr > MCAL_16BIT_MAX_ADDR)
    {
      /* MISRA2012_RULE_11_5_JUSTIFICATION: Conversion between
       * pointer to void and pointer to object due to SFR access. */
      /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between
       * pointers of different object types due to SFR access. */
      *((volatile uint32*)RegAddress) = (uint32)DataValue;
    }
    else
    {
      /* [cover parentID={33F5D436-8491-4d1b-B32F-EEDD8A451900}][/cover] */
      /* CPU specific registers are updated using MTCR */
      switch(TempAddr)
      {
        case CPU_PMA0:
            MTCR(CPU_PMA0, DataValue);
            break;
        case CPU_PMA1:
            MTCR(CPU_PMA1, DataValue);
            break;
        case CPU_ISP:
            MTCR(CPU_ISP, DataValue);
            break;
        case CPU_BIV:
            MTCR(CPU_BIV, DataValue);
            break;
        case CPU_BTV:
            MTCR(CPU_BTV, DataValue);
            break;
        case CPU_SEGEN:
            MTCR(CPU_SEGEN, DataValue);
            break;
        case CPU_DCON0:
            MTCR(CPU_DCON0, DataValue);
            break;
        case CPU_PCON0:
            MTCR(CPU_PCON0, DataValue);
            break;
        default:
            /* This case is not possible, kept only for MISRA compliance */
            break;
      }
    }

    /* Set CpuEndInit Protection */
    /* [cover parentID={34F6FD8A-A61F-4636-B594-A600DB5FAC5F}]
     * Set CpuEndInit Protection
     * [/cover] */
    (void)Mcal_lUpdateCpuEndInit(MCAL_DUMMY_PASSWORD, CoreId,
                                 CpuEndInitRet.TimerRelValAtReset,
                                 MCAL_NOUPDATE_PASSWORD,
                                 MCAL_SETENDINITPROTECTION);

    /* Exit critical section */
    /* [cover parentID={60F5FA05-4D84-400c-9E59-108DA8315CE8}]
     * Exit critical section
     * [/cover] */
    SchM_Exit_McalLib_CpuEndInit();
  }
}

/*******************************************************************************
** Traceability     : [cover parentID={5BE87D93-DC0C-4989-A16E-CE49AEE7BF0D}] **
**                                                                            **
** Syntax           : uint32 Mcal_GetSafetyEndInitPassword (void)             **
**                                                                            **
** Description      : This interface is used by applications to retrieve the  **
**                    Safety endinit password currently installed in the      **
**                    Global ENDINIT control register (SEICON0 register).     **
**                    The password corresponds to EPW bitfield in register    **
**                    SEICON0.                                                **
**                                                                            **
** Service ID       : 0x87                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Currently installed password                            **
**                                                                            **
*******************************************************************************/
uint32 Mcal_GetSafetyEndInitPassword(void)
{
  uint32 Password;

  /* Retrieve the encrypted(partially inverted) password from the register */
  /* [cover parentID={7C4FBB47-84FA-4491-BE2D-D07F7C6AA2D1}]Retrieve the
      encrypted  password from the register[/cover] */
  Password = Mcal_GetBitAtomic(MODULE_SCU.SEICON0.U,
                               IFX_SCU_SEICON0_EPW_OFF,
                               IFX_SCU_SEICON0_EPW_LEN);

  /* Decrypt the password (invert bits 0:5) */
  /* [cover parentID={6180D731-B725-466c-8DC7-5CC0D41BB597}]Decrypt the
      password[/cover] */
  Password = Password ^ (uint32)MCAL_ENDINIT_WDT_PWD_INV;
  /* [cover parentID={50367A61-FB21-4c2e-9258-9AA88D7CA8AC}]
      Return password[/cover] */
  return (Password);
}

/*******************************************************************************
** Traceability     : [cover parentID={1D74AAF8-8492-4b33-B8D8-B865ECB04396}] **
**                                                                            **
** Syntax           : uint32 Mcal_SetSafetyEndInitPassword                    **
**                                               (const uint32 Password)      **
**                                                                            **
** Description      : This interface is used by applications to install a     **
**                    password for Safety endinit protection. The interface   **
**                    internally prepares the password (shifting, inversion   **
**                    etc.), installs the password and returns the previously **
**                    installed password (from the EPW bitfield).             **
**                                                                            **
** Service ID       : 0x80                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : Password - New password to be installed into            **
**                    SEICON0 register                                        **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Returns the last installed password                     **
**                                                                            **
*******************************************************************************/
uint32 Mcal_SetSafetyEndInitPassword(const uint32 Password)
{
  uint32 OldPassword;
  uint32 NewPassword = (Password & (uint32)IFX_SCU_SEICON0_EPW_MSK);

  /* Critical section to protect SCU_SEICON0 register*/
  /* [cover parentID={E6F5A6B8-5E08-496d-B4C3-EB42D886A1F7}]Enter Critical
     Section for updating safety endinit password[/cover] */
  SchM_Enter_McalLib_SafetyEndInit();

  /* Acquire the lock for SCU_SEICON0 register */
  /* [cover parentID={C098B134-9F92-4803-ABCD-54C25B8A9A8F}]
   * Acquire the lock for SCU_SEICON0 register
   * [/cover] */
  Mcal_lGetSpinlock(&Mcal_LockAddressSiecon0, \
                   (uint32)MCAL_SPINLOCK_DEFAULT_TIMEOUT,
                   MCALLIB_SID_SETSAFETYENDINIT);
  /* [cover parentID={6CFA30E3-B332-47a0-9779-39A715C02A47}][/cover] */
  /* Reset ENDINIT protection and update the new password */
  OldPassword = Mcal_lUpdateSafetyEndInit(NewPassword,
                                          MCAL_UPDATE_NEWPASSWORD,
                                          MCAL_RESETENDINITPROTECTION);

  /* Release the lock for SCU_SEICCON0 register */
  /* [cover parentID={E81DDB92-1211-407b-A0C4-7CC4EA7E03B9}]
   * Release the lock for SCU_SEICCON0 register
   * [/cover] */
  Mcal_lReleaseSpinlock(&Mcal_LockAddressSiecon0);

  /* [cover parentID={EA17FFF8-6438-4167-80A3-470F8B14D1C4}]
   * Exit critical section
   * [/cover] */
  SchM_Exit_McalLib_SafetyEndInit();

  /* Return old password */
  /* [cover parentID={567C341C-482C-4c37-9651-52F4095AA60E}]Return old
     password [/cover] */
  return (OldPassword);
}

/*******************************************************************************
** Traceability     :[cover parentID={49C5FBA9-0673-47dd-8182-DE8AED479123}]  **
** [/cover]                                                                   **
** Syntax           : void Mcal_WriteSafetyEndInitProtReg                     **
                     (volatile void* const RegAddress, const uint32 DataValue)**
**                                                                            **
** Description      : This API is needed to write required values to safety   **
**                    end-init protected registers by unprotecting to write   **
**                    and protecting back to keep protection intact. This     **
**                    interface also supports write access to safety endinit  **
**                    protected CSFRs.                                        **
**                                                                            **
**                                                                            **
** Service ID       : 0x7F                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : RegAddress - Safety Endinit protected register address  **
**                    DataValue - Value to be written to the register located **
**                    at RegAddress                                           **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void Mcal_WriteSafetyEndInitProtReg(volatile void* const RegAddress,
                                    const uint32 DataValue)
{
  /* [cover parentID={4035DB5A-D359-4547-B3D4-AD4A8475F6EE}]
   * If SAFETY Error Check is Enabled
   * [/cover] */
  #if (MCALLIB_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={2C16B817-914C-46a6-8232-4EE20FC3FDAA}]
      Check if input address is null pointer[/cover] */
  if ((RegAddress) == NULL_PTR)
  {
    /* [cover parentID={27FF0329-1BC1-4339-91A7-E02687B80671}]
     * Report error MCALLIB_E_PARAM_POINTER[/cover]
     */
    Mcal_lReportError(MCALLIB_SID_SAFETYENDINIT,
                      MCALLIB_E_PARAM_POINTER);
  }
  /* [cover parentID={AB76685F-687F-4e66-9DAC-E28B0DBCAFCE}]
   * If address is not null pointer[/cover]
   */
  else
  #endif
  {
    /* Write the data into safetyendinit register with default mask */
    /* [cover parentID={0AB9676C-BE6A-4851-AC15-612F9E23A897}][/cover] */
    Mcal_lWriteSafetyEndInitProtection(
                                        RegAddress,
                                        DataValue,
                                        MCAL_DEFAULT_MASK_VALUE,
                                        MCAL_32BIT_ACCESS,
                                        MCALLIB_SID_SAFETYENDINIT
                                      );
  }
}

/*******************************************************************************
** Traceability     :[cover parentID={D41CCA16-D6E9-473e-A7FD-96E5F50DA961}]  **
** [/cover]                                                                   **
** Syntax           : void Mcal_WriteSafetyEndInitProtReg16                   **
                     (volatile void* const RegAddress, const uint16 DataValue)**
**                                                                            **
** Description      : This API is needed to write required values to safety   **
**                    end-init protected registers by unprotecting to write   **
**                    and protecting back to keep protection intact           **
**                                                                            **
**                                                                            **
** Service ID       : 0x81                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : RegAddress - Safety Endinit protected register address  **
**                    DataValue - Value to be written to the register located **
**                    at RegAddress                                           **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void Mcal_WriteSafetyEndInitProtReg16(volatile void* const RegAddress,
                                      const uint16 DataValue)
{
  /* [cover parentID={93B23F99-B0D3-4e77-B2DE-B7CA148C79AB}]
      If SAFETY Error Check is Enabled[/cover] */
  #if (MCALLIB_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={5C03C912-F7C2-4380-9502-839E329DD953}]
      Check if input address is null pointer[/cover] */
  if ((RegAddress) == NULL_PTR)
  {
    /* [cover parentID={8125DCB6-5FA7-4be5-B5AD-C214218F543A}]
     * Report error MCALLIB_E_PARAM_POINTER[/cover]
     */
    Mcal_lReportError(MCALLIB_SID_SAFETYENDINIT_16, \
                      MCALLIB_E_PARAM_POINTER);
  }
  /* [cover parentID={252C1D0A-F50F-4f7b-A454-567D7E438D0C}]
   * If address is not null pointer[/cover]
   */
  else
  #endif
  {
    /* [cover parentID={7FEB1C5E-2EFD-4f08-BE4C-84C4E63B6C7A}]
       Write the data into safetyendinit register with default mask
       [/cover] */
    Mcal_lWriteSafetyEndInitProtection(
                                        RegAddress,
                                        DataValue,
                                        MCAL_DEFAULT_MASK_VALUE,
                                        MCAL_16BIT_ACCESS,
                                        MCALLIB_SID_SAFETYENDINIT_16
                                      );
  }
}

/*******************************************************************************
** Traceability     : [cover parentID={C056F09A-B74A-4ac8-A7E8-9B8D40D8C8E2}] **
** [/cover]                                                                   **
** Syntax           : void Mcal_WriteSafetyEndInitProtRegMask                 **
**                      (volatile void* const RegAddress,                     **
**                      const uint32 DataValue,                               **
**                      uint32 Mask)                                          **
**                                                                            **
** Description      : This API is needed to write required values to safety   **
**                    end-init protected register bits by unprotecting to     **
**                    write and protecting back to keep protection intact.    **
**                    This interface also supports write access to safety     **
**                    endinit protected CSFRs.                                **
**                                                                            **
**                                                                            **
**                                                                            **
** Service ID       : 0x8F                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : RegAddress - Safety Endinit protected register address  **
**                    DataValue - Value to be written to the register located **
**                    at RegAddress                                           **
**                    Mask - Value to be written to mask the register value   **
**                    need to be changed.                                     **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void Mcal_WriteSafetyEndInitProtRegMask(volatile void* const RegAddress,
                                         const uint32 DataValue, uint32 Mask)
{
  /* [cover parentID={5974CFB6-87C9-4794-B9F9-0EC6DD775F98}]
      If SAFETY Error Check is Enabled[/cover] */
  #if (MCALLIB_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={CBE8BCA9-7698-4c9d-8E65-EE8C1F75B35D}]
      Check if input address is null pointer[/cover] */
  if ((RegAddress) == NULL_PTR)
  {
    /* [cover parentID={E2348FD8-212E-4299-88D4-3849DBE60CCF}]
       Report error MCALLIB_E_PARAM_POINTER[/cover] */
    Mcal_lReportError(MCALLIB_SID_SAFETYENDINITMASK,
                      MCALLIB_E_PARAM_POINTER);
  }
  /* [cover parentID={1348778A-0EA6-4fb3-B370-4751F20C57D0}]
     If address is not null pointer[/cover] */
  else
  #endif
  {
    /* [cover parentID={D8F923BB-96E0-441d-A9F8-BA1A6D865DE4}]
       Mcal_WriteSafetyEndInitProtRegMask[/cover] */
    /* [cover parentID={F67D85E8-2ED7-481e-AA31-B1BC3FC37866}]
       Write the data into safetyendinit register with mask[/cover] */
    Mcal_lWriteSafetyEndInitProtection(
                                        RegAddress,
                                        DataValue,
                                        Mask,
                                        MCAL_32BIT_ACCESS,
                                        MCALLIB_SID_SAFETYENDINITMASK
                                      );
  }
}

/*******************************************************************************
** Traceability     : [cover parentID={E0C11962-A636-4404-B096-E13741CF52ED}] **
** [/cover]                                                                   **
** Syntax           : uint32 Mcal_GetPeripheralEndInitPassword (void)         **
**                                                                            **
** Description      : This interface is used by applications to retrieve the  **
**                    peripheral endinit password currently installed in the  **
**                    Global ENDINIT control register (EICON0 register).      **
**                    The password corresponds to bits 15:2 in register EICON0**
**                                                                            **
** Service ID       : 0x82                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Currently installed password                            **
**                                                                            **
*******************************************************************************/
uint32 Mcal_GetPeripheralEndInitPassword(void)
{
  uint32 Password;

  /* Retrieve the encrypted(partially inverted) password from the register */
  /* [cover parentID={C2FA35C2-FD4F-42ab-81A5-3CB77AB6293F}]Retrieve the
     encrypted  password from the register[/cover] */
  Password = Mcal_GetBitAtomic(MODULE_SCU.EICON0.U,
                               IFX_SCU_EICON0_EPW_OFF,
                               IFX_SCU_EICON0_EPW_LEN);

  /* Decrypt the password (invert bits 0:5) */
  /* [cover parentID={B8B47083-237D-44e7-8286-FAD882674D90}]Decrypt the
     password[/cover] */
  Password = Password ^ (uint32)MCAL_ENDINIT_WDT_PWD_INV;

  /* [cover parentID={8E0B1A74-D0AD-4d98-A6D4-7AB519A9F963}]
     Return password[/cover] */
  return (Password);
}

/*******************************************************************************
** Traceability     :[cover parentID={1C3749D6-0FFF-4339-B267-3167F5938B13}]  **
**                                                                            **
** Syntax           : uint32 Mcal_SetPeripheralEndInitPassword                **
**                   (const uint32 Password)                                  **
**                                                                            **
** Description      : This interface is used by applications to install a     **
**                    password for peripheral endinit protection. The         **
**                    interface internally prepares the password (shifting,   **
**                    inversion etc.), installs the password and returns the  **
**                    previously installed password.                          **
**                                                                            **
** Service ID       : 0x7C                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : Password - New password to be installed into            **
**                    EICON0 register                                         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Returns the last installed password                     **
**                                                                            **
*******************************************************************************/
uint32 Mcal_SetPeripheralEndInitPassword(const uint32 Password)
{
  uint32 OldPassword;
  uint32 NewPassword = (Password & (uint32)IFX_SCU_EICON0_EPW_MSK);

  /* Enter Critical section, to protect write to SCU_EICON0 register */
  /* [cover parentID={B0865877-FB51-4389-B51E-F3BECC0CD3F0}]
   * Enter crtical section for updating peripheral endinit password
   * [/cover] */
  SchM_Enter_McalLib_PeripheralEndInit();

  /* Acquire the Spinlock for writing tp SCU_EICCON0 register */
  /* [cover parentID={BA6A8376-519A-4681-9898-32B3C9AA155A}]
   * Acquire the Spinlock for writing tp SCU_EICCON0 register
   * [/cover] */
  Mcal_lGetSpinlock(&Mcal_LockAddressEicon0,
                   (uint32)MCAL_SPINLOCK_DEFAULT_TIMEOUT,
                   MCALLIB_SID_SETPERIPHERALENDINIT);

   /* [cover parentID={B2497D28-4A5A-4a41-89E8-B6549080E1E4}][/cover] */
  /* Reset ENDINIT protection and update the new password */
  OldPassword = Mcal_lUpdatePeripheralEndInit(NewPassword,
                                              MCAL_UPDATE_NEWPASSWORD,
                                              MCAL_RESETENDINITPROTECTION);

  /* Release the Spinlock */
  /* [cover parentID={7831D1EA-89DF-4b15-BBAB-425FACCE408B}]
     Release the Spinlock
     [/cover] */
  Mcal_lReleaseSpinlock(&Mcal_LockAddressEicon0);

  /* Exit Critical section */
  /* [cover parentID={FA823BDD-51FD-4043-8D96-8D43F4109756}]
   * Exit critical section
   * [/cover] */
  SchM_Exit_McalLib_PeripheralEndInit();

  /*Return old password*/
  /* [cover parentID={61C56107-C8EB-4fbf-9A29-8BEA6DEDBADF}]Return old
     password [/cover] */
  return (OldPassword);
}

/*******************************************************************************
** Traceability     : [cover parentID={382E875A-A388-4f3f-842B-BBD7143DEE70}] **
**                                                                            **
** Syntax           : Mcal_WritePeripEndInitProtReg                           **
**                   (volatile void* const RegAddress, const uint32 DataValue)**
**                                                                            **
** Description      :This API is needed to write required values to peripheral**
**                   protected registers by unprotecting to write end-init    **
**                   and protecting back to keep protection intact.           **
**                                                                            **
** Service ID       : 0x7A                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : RegAddress - Peripheral Endinit protected register      **
**                    address.                                                **
**                    DataValue - Value to be written to the register         **
**                    located at RegAddress.                                  **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void Mcal_WritePeripEndInitProtReg(volatile void* const RegAddress,
                                   const uint32 DataValue)
{
  /* [cover parentID={AFFF6EC8-965F-4f68-A3DA-BBCC7AE589B1}]
     If SAFETY Error Check is Enabled[/cover] */
  #if (MCALLIB_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={E437DC4F-781A-4f79-B1CC-4C6D0557C31D}]
      Check if input address is null pointer[/cover] */
  if ((RegAddress) == NULL_PTR)
  {
    /* [cover parentID={55F2F56D-E927-47b0-9B15-38874239EA8D}]
       Report error MCALLIB_E_PARAM_POINTER[/cover] */
    Mcal_lReportError(MCALLIB_SID_PERIPHERALENDINIT,
                      MCALLIB_E_PARAM_POINTER);
  }
  /* [cover parentID={68C78085-FCDC-4bf6-8D36-F75B06543DB5}]
     If address is not null pointer [/cover] */
  else
  #endif
  {
    /*Critical section to protect SCU_EICON0 ans SCU_EICON1 registers */
    /* [cover parentID={3B162CFE-48A4-41d9-A974-4EB51BFD64AD}]
     * Enter critical section for write peripheral endinit protection reg
     * [/cover] */
    SchM_Enter_McalLib_PeripheralEndInit();

    /* Acquire the Spinlock for writing tp SCU_EICCON0 register */
    /* [cover parentID={4AA7F08A-A41E-4f23-85D5-507F6D2CA4DE}]
     * Acquire the Spinlock for writing tp SCU_EICCON0 register
     * [/cover] */
    Mcal_lGetSpinlock(&Mcal_LockAddressEicon0,
                     (uint32)MCAL_SPINLOCK_DEFAULT_TIMEOUT,
                     MCALLIB_SID_PERIPHERALENDINIT);

    /* Reset Peripheral EndInit protection */
    /* [cover parentID={511EE30E-EAD8-4cff-BBF9-E6D3FC004DEB}]
     * Reset Peripheral EndInit protection
     * [/cover] */
    (void)Mcal_lUpdatePeripheralEndInit(MCAL_DUMMY_PASSWORD,
                                        MCAL_NOUPDATE_PASSWORD,
                                        MCAL_RESETENDINITPROTECTION);

    /* Update the register */
    /* [cover parentID={444D88B6-6F28-42d8-A9B3-DC73B0B2CD23}]
     * Update the register
     * [/cover] */
    /* MISRA2012_RULE_11_5_JUSTIFICATION: Conversion between
     * pointer to void and pointer to object due to SFR access. */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between
     * pointers of different object types due to SFR access. */
    *((volatile uint32*)RegAddress) = DataValue;

    /* Set Peripheral EndInit protection */
    /* [cover parentID={DD8D453E-0FD7-4e1a-B2C2-C207595CC876}]
     * Set Peripheral EndInit protection
     * [/cover] */
    (void)Mcal_lUpdatePeripheralEndInit(MCAL_DUMMY_PASSWORD,
                                        MCAL_NOUPDATE_PASSWORD,
                                        MCAL_SETENDINITPROTECTION);
    /* Release the Spinlock */
    /* [cover parentID={0B9059B2-B68B-4462-92AF-41E0C00856B3}]
     * Release the Spinlock
     * [/cover] */
    Mcal_lReleaseSpinlock(&Mcal_LockAddressEicon0);

    /* [cover parentID={1363313D-5FAA-4a8f-853E-AF5A75668F77}]
     * Exit critical section
     * [/cover] */
    SchM_Exit_McalLib_PeripheralEndInit();
  }
}

/*******************************************************************************
** Traceability     : [cover parentID={32C6BD4E-84D4-4d99-9939-40ACDFBADF92}] **
**                                                                            **
** Syntax           : uint32 Mcal_GetCpuPhysicalId(void)                      **
**                                                                            **
** Description      : This interface is used by applications in a multicore   **
**                    environment to determine the CPU they are executing on. **
**                    The API returns the contents of CORE_ID register, for   **
**                    the core on which it is invoked.                        **
**                                                                            **
** Service ID       : 0x8B                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Physical Core ID for the CPU on which this API is called**
**                                                                            **
*******************************************************************************/
uint32 Mcal_GetCpuPhysicalId(void)
{
  /* [cover parentID={67B47B7B-BCC4-4e5f-9A7E-1E171742E615}]
     Read the CPU_CORE_ID register to retrieve the CoreId [/cover] */
  uint32 CoreId = (uint32)MFCR(CPU_CORE_ID);
  /* [cover parentID={2E22F876-FA68-47b1-BFFC-3EBDC68F5C10}]
     Return CoreId[/cover] */
  return(CoreId);
}

/*******************************************************************************
** Traceability     : [cover parentID={19A3024B-65AF-4139-95D6-AF25CB4A476E}] **
**                                                                            **
** Syntax           : uint32 Mcal_GetGlobalDsprAddress                        **
**                    (                                                       **
**                     const uint32 CpuId,                                    **
**                     const uint32 LocalDsprAddress                          **
**                    )                                                       **
**                                                                            **
** Description      : This interface is used by applications in a multicore   **
**                    environment to determine the global address of a local  **
**                    DSPR address of a specified CPU. A value 0 is returned  **
**                    in case an invalid input argument is passed             **
**                    (incorrect CpuId, local DSPR address)                   **
**                                                                            **
**                                                                            **
** Service ID       : 0x7B                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : CpuId - Physical Core ID                                **
**                    LocalDsprAddress - Local DSPR address for which global  **
**                    DSPR address is returned                                **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : 0: Invalid input parameter passed                       **
**                    Else, value returned the Global DSPR address            **
**                    If passed parameter is valid global DSPR address        **
**                    corresponding to passed CPU id then return              **
**                    passed address as is.                                   **
*******************************************************************************/
uint32 Mcal_GetGlobalDsprAddress
(const uint32 CpuId, const uint32 LocalDsprAddress)
{
  /* Obtain the memory segment information to which
   * LocalDsprAddress belongs to */
  /* [cover parentID={5AB06FBB-9343-4fe2-AEC4-6F40F2290CA4}]
   * Extract the memory segment to which DSPR address belongs
   * [/cover] */
  uint8 DsprMsb = (uint8)((LocalDsprAddress & (uint32)MCAL_DSPR_GLOBAL_MASK) >>
                          MCAL_SHIFT_UPPER_NIBBLE);

  uint32  RetGlobalAddress = MCAL_INVALID_ARGUMENT;

  /* Is the input physical CpuId a valid value */
  /* [cover parentID={4601D034-5B02-4e38-8306-3B0B47BFD6E2}]
   * Check the CpuID is not invalid (Core 5 or greater than or equal
   * to maximum number of cores)
   * [/cover] */
  if((CpuId != (uint32)MCAL_INVALID_CPU_ID_5) &&
      (CpuId <= (uint32)MCAL_COREID_MAX_VALUE))
  {
    /* Is LocalDsprAddress within the DSPR address range */
    /* The check against the starting address of DSPR memory range isnlt
     * done as its base address starts from 0xM0000000 - 0xM0018000,
     * where 'M' corresponds to memory segment
     */
    /* [cover parentID={7584D010-0D1C-4cec-8371-A89B322A1E92}]Local
       DsprAddress within the DSPR address range[/cover] */
    if((LocalDsprAddress & (uint32)MCAL_DSPR_GLOBAL_MASK_N) <=
        Mcal_kDsprEndAddress[CpuId])
    {
      /* Does LocalDsprAddress belong to memory segment 0xD */
      /* [cover parentID={C021555F-7DEF-4011-8235-C90C2DE91FF3}]LocalDspr
         Address belong to memory segment 0xD[/cover] */
      if (DsprMsb == (uint8)MCAL_VALID_DSPR_MSB)
      {
        /* Compute the Global DSPR address */
        /* [cover parentID={68068C41-3E2A-4f2c-ADF7-D527D8A53EF7}]
            Compute globalDspraddress[/cover] */
        RetGlobalAddress =
                        ((LocalDsprAddress & (uint32)MCAL_DSPR_GLOBAL_MASK_N) |
                        ((uint32)Mcal_kCoreXMemSegment[CpuId] <<
                          MCAL_SHIFT_UPPER_NIBBLE));
      }
      else
      {
        /* Validate if DSPR address's memory segment belongs to a
         * valid CPUx memory segment */
        /*if ((DsprMsb != (uint8)MCAL_MEM_SEGMENT2_MSB) &&
            (DsprMsb <= (uint8)MCAL_CORE0_MEM_SEGMENT) &&
            (DsprMsb >= Mcal_kCoreXMemSegment[MCAL_COREID_MAX_VALUE]))*/
        /* [cover parentID={B6E52E52-6E44-4bdf-95CD-25E11748601C}]GlobalDspr
        address memory segment belong to valid CPU memory segment[/cover] */
        if(DsprMsb == Mcal_kCoreXMemSegment[CpuId])
        {
          /*[cover parentID={EA7BB3D2-D189-4931-80BF-6C6E091157F4}]Return
                 GlobalDsprAddress[/cover] */
          RetGlobalAddress = LocalDsprAddress;
        }
      }
    }
  }
  /* [cover parentID={EA7BB3D2-D189-4931-80BF-6C6E091157F4}]Return
     GlobalDsprAddress[/cover] */
  /* [cover parentID={9E058E8D-CE5F-4aeb-A4ED-BA0B0CCFE5B6}]Return
     GlobalDspraddress 0[/cover] */
  return (RetGlobalAddress);
}

/*******************************************************************************
** Traceability     : [cover parentID={6A4C10C1-2C3C-468f-8F33-C02634550889}] **
**                                                                            **
** Syntax           : uint32 Mcal_GetLocalDsprAddress                         **
**                    (                                                       **
**                     const uint32 GlobalDsprAddress                         **
**                    )                                                       **
**                                                                            **
** Description      : This API is used by applications in a multicore         **
**                    environment to determine the local CPU address of a     **
**                    global DSPR address of the CPU, this interface is       **
**                    invoked on. A value 0 is returned in case an invalid    **
**                    input argument is passed(incorrect global DSPR address) **
**                                                                            **
** Service ID       : 0x83                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : GlobalDsprAddress - Global DSPR address                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : 0: Invalid input parameter passed                       **
**                    Else, value returned the local DSPR address             **
**                    If passed parameter is valid local DSPR address         **
**                    corresponding to currently executing CPU then routine   **
**                    shall return passed address as is                       **
*******************************************************************************/
uint32 Mcal_GetLocalDsprAddress(const uint32 GlobalDsprAddress)
{
  uint32 DsprEndAddress;
  /* Obtain the memory segment information to which
   * GlobalDsprAddress belongs to */
  /* [cover parentID={F43CEA65-A9BE-4051-99B2-D7AA361231AB}]
   * Extract the memory segment to which DSPR address belongs
   * [/cover] */
  uint8 DsprMsb = (uint8)((GlobalDsprAddress & (uint32)MCAL_DSPR_GLOBAL_MASK) >>
                          MCAL_SHIFT_UPPER_NIBBLE);

  uint32 RetLocalAddress = MCAL_INVALID_ARGUMENT;
  /* [cover parentID={F1D77D46-E71E-461c-BB86-B438B9716DAC}]Check for CPUIndex
     [/cover] */
  uint32 CoreIndex = Mcal_lGetCpuIndex();

  /* Validate if Global DSPR address's memory segment is a
   *  valid CPUx memory segment */
  /* [cover parentID={E163BFCC-7444-4c74-9762-D50D80ACA3B9}]Is
     GlobalDsprAddress's memory segment a valid CPU memory segment[/cover] */
  if ((DsprMsb != (uint8)MCAL_MEM_SEGMENT2_MSB) &&
      (DsprMsb <= (uint8)MCAL_CORE0_MEM_SEGMENT) &&
      (DsprMsb >= Mcal_kCoreXMemSegment[MCAL_COREID_MAX_VALUE]))
  {
    /* Is GlobalDsprAddress within the DSPR address range */
    /* The check against the starting address of DSPR memory range isn't
     * done as its base address starts from 0xM0000000 - 0xM0018000, where
     * 'M' corresponds to memory segment
     */
    /* [cover parentID={F490A20E-4BB0-46d3-9E7E-78D3E82E289D}]Is
       GlobalDsprAddress address within the DSPR address range[/cover] */
    if((GlobalDsprAddress & (uint32)MCAL_DSPR_GLOBAL_MASK_N) <=
        Mcal_kDsprEndAddress[MCAL_CORE0_MEM_SEGMENT - DsprMsb])
    {
      /* Compute Local DSPR address */
      /* [cover parentID={CE9639D9-9374-49f3-950A-A8E65048B103}]Compute
          Local DSPR address[/cover] */
      RetLocalAddress =
                        ((GlobalDsprAddress & (uint32)MCAL_DSPR_GLOBAL_MASK_N) |
                         (uint32)MCAL_LOCAL_DSPR_BASE_ADDR);
    }

  }
  else
  {
    /* [cover parentID={26D4B584-E7D8-493b-B524-16A6C479D2BF}]GlobalDspr
        Address belong to memory segment 0xD[/cover] */
    if(DsprMsb == (uint8)MCAL_VALID_DSPR_MSB)
    {
      /* Calculate the DSPR end address */
      #if ( MCAL_NO_OF_CORES > 5U )
      if (CoreIndex == MCAL_INVALID_CPU_ID_5)
      {
        DsprEndAddress = Mcal_kDsprEndAddress[MCAL_MAX_CORES];
      }
      else
      #endif
      {
        DsprEndAddress = Mcal_kDsprEndAddress[CoreIndex];
      }

      /* [cover parentID={7056C288-3337-4661-9838-32727B69CAED}]Input
          parameter is valid localDspraddress with executing CPU
          [/cover] */
      if((GlobalDsprAddress & (uint32)MCAL_DSPR_GLOBAL_MASK_N) <=
         DsprEndAddress)
      {
        /* [cover parentID={A13DD372-FA55-4fa2-9DE6-A9BE2182505B}]
           Return LocalDsprAddress[/cover] */
        RetLocalAddress = GlobalDsprAddress;
      }

    }
  }
  /* [cover parentID={A13DD372-FA55-4fa2-9DE6-A9BE2182505B}]
     Return LocalDsprAddress[/cover] */
  /* [cover parentID={C8838677-BE78-49d8-8448-7EEE5C587AC8}]Return
     LocalDsprAddress 0[/cover] */
  return (RetLocalAddress);
}

/*******************************************************************************
** Traceability     : [cover parentID={3FCAA99A-4260-4c7e-9224-EAE68F1461C6}] **
**                                                                            **
** Syntax           : uint32 Mcal_GetGlobalPsprAddress                        **
**                    (                                                       **
**                     const uint32 CpuId,                                    **
**                     const uint32 LocalPsprAddress                          **
**                    )                                                       **
**                                                                            **
** Description      : This interface is used by applications in a multicore   **
**                    environment to determine the global address of a local  **
**                    PSPR address of a specified CPU. A value 0 is returned  **
**                    in case an invalid input argument is passed             **
**                    (incorrect CpuId, local PSPR address)                   **
**                                                                            **
** Service ID       : 0x7D                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : CpuId - Physical Core ID                                **
**                    LocalPsprAddress - Local PSPR address for which global  **
**                    PSPR address is returned                                **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : 0: Invalid input parameter passed                       **
**                    Else, value returned the Global PSPR address            **
**                    If passed parameter is valid Global PSPR address        **
**                    corresponding to currently executing CPU then routine   **
**                    shall return passed address as is                       **
*******************************************************************************/
uint32 Mcal_GetGlobalPsprAddress(const uint32 CpuId,
                                 const uint32 LocalPsprAddress)
{
  /* Obtain the memory segment information to which
   * LocalPsprAddress belongs to */
  /* [cover parentID={403F7F86-1A80-48c4-A0EA-8E26D88266DB}]
   * Extract the memory segment to which PSPR address belongs
   * [/cover] */
  uint8 PsprMsb = (uint8)((LocalPsprAddress & (uint32)MCAL_PSPR_GLOBAL_MASK) >>
                          MCAL_SHIFT_UPPER_NIBBLE);
  uint32 RetGlobalAddress = MCAL_INVALID_ARGUMENT;
  uint32 LocalRetAddress = LocalPsprAddress;

  /* Is the input physical CpuId a valid value */
  /* [cover parentID={7107E3A8-43A4-4d74-9810-7883B9E33371}]
   * Check the CpuID is not invalid (Core 5 or greater than or equal to maximum
   * number of cores)
   * [/cover] */
  if((CpuId != (uint32)MCAL_INVALID_CPU_ID_5) &&
      (CpuId <= (uint32)MCAL_COREID_MAX_VALUE))
  {
    /* Does LocalPsprAddress belong to memory segment 0xC */
    /* [cover parentID={3B145523-EEA5-4b96-9540-53E3228BB612}]Local
        PsprAddress belong to memory segment 0xC[/cover] */
    if (PsprMsb == (uint8)MCAL_VALID_PSPR_MSB)
    {
      /* Is LocalPsprAddress within the PSPR address range */
      /* [cover parentID={E2C43B5E-E279-404a-8AD6-1919A5A32CE7}]Local
         PsprAddress within the PSPR address range[/cover] */
      if (LocalRetAddress <= Mcal_kPsprLocalEndAddress[CpuId])
      {
        /* Compute the Global PSPR address */
        /* [cover parentID={9718F7E1-972D-4d85-B1D3-19833108A29D}]
            Compute GlobalPSPR address[/cover] */
        RetGlobalAddress =
          (uint32)((LocalRetAddress & (uint32)MCAL_PSPR_GLOBAL_MASK_N) |
          (((uint32)Mcal_kCoreXMemSegment[CpuId] << MCAL_SHIFT_UPPER_NIBBLE)
          | Mcal_kPsprGlobalBaseAddress[CpuId]));
      }
    }
    else
    {
      /* Validate if PSPR address's memory segment is a
       * valid Global CPUx memory segment */
      /*[cover parentID={D48BCD3E-A39E-41fd-ADE8-80102F454106}]PSPR address
          memory segment is a valid Global CPUx memory segment[/cover] */
      if (PsprMsb == Mcal_kCoreXMemSegment[CpuId])
      {
        LocalRetAddress = (LocalRetAddress &
                           (uint32)MCAL_PSPR_GLOBAL_MASK_N);
        /* [cover parentID={373CFC21-BBFA-422f-B29A-345340C106B9}]
           Check if local PSPR address is more than or equal to global
           PSPR base address and less than or equal to global PSPR end
           address [/cover] */
        if((LocalRetAddress >= Mcal_kPsprGlobalBaseAddress[CpuId])  &&
            (LocalRetAddress <= Mcal_kPsprGlobalEndAddress[CpuId]))
        {
          /* [cover parentID={14A6F0A2-A944-4aaa-854F-0E8C66FEA20A}]
              Return GlobalPSPR address[/cover] */
          RetGlobalAddress = LocalPsprAddress;
        }
      }
    }
  }
  /* [cover parentID={14A6F0A2-A944-4aaa-854F-0E8C66FEA20A}]Return GlobalPSPR
     address[/cover] */
  /* [cover parentID={B3D4FDB4-1431-4344-8002-3B3FD3DBE383}]Return GlobalPSPR
     address 0[/cover] */
  return (RetGlobalAddress);
}

/*******************************************************************************
** Traceability     : [cover parentID={CD35B780-C410-4f80-98F4-722831388424}] **
**                                                                            **
** Syntax           : uint32 Mcal_GetLocalPsprAddress                         **
**                    (                                                       **
**                     const  uint32 GlobalPsprAddress                        **
**                    )                                                       **
**                                                                            **
** Description      : This API is used by applications in a multicore         **
**                    environment to determine the local CPU address of a     **
**                    global PSPR address of the CPU, this interface is       **
**                    invoked on. A value 0 is returned in case an invalid    **
**                    input argument is passed(incorrect global PSPR address) **
**                                                                            **
** Service ID       : 0x84                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : GlobalPsprAddress - Global PSPR address                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : 0: Invalid input parameter passed                       **
**                    Else, value returned the local PSPR address             **
**                    If passed parameter is valid local PSPR address         **
**                    corresponding to currently executing CPU then routine   **
**                    shall return passed address as is                       **
**                                                                            **
*******************************************************************************/
uint32 Mcal_GetLocalPsprAddress(const uint32 GlobalPsprAddress)
{
  /* Obtain the memory segment information to which
   * GlobalPsprAddress belongs to */
  /* [cover parentID={C88A6DFC-0AA1-4b7f-92E2-D40B9CEBF72B}]
   * Compute an PSPR global end address based on available core
   * [/cover] */
  /* [cover parentID={8D55C24F-2536-4651-B221-B3C2E1DAF6BF}]
   *  Compute an PSPR global start address based on available core
   * [/cover] */
  /* [cover parentID={3A0405BB-A65F-46b5-A4DC-64363E713D9F}]
   * Compute an PSPR local end address based on available core
   * [/cover] */
  /* [cover parentID={2C9717B8-872D-46ac-88C1-195339372B6E}]
   * Compute Local PSPR address
   * [/cover] */
  uint8 PsprMsb = (uint8)((GlobalPsprAddress & (uint32)MCAL_PSPR_GLOBAL_MASK) >>
                          MCAL_SHIFT_UPPER_NIBBLE);
  uint32 RetLocalAddress = MCAL_INVALID_ARGUMENT;
  uint32 LocalRetAddress = GlobalPsprAddress;
  /* [cover parentID={88AD1AD5-66D4-4114-BC45-CB7F0111D626}]
     Retrieve CPU index[/cover] */
  uint32 CpuIndex = Mcal_lGetCpuIndex();

  /* Validate if Global PSPR address's memory segment is a
   * valid CPUx memory segment */
  /* [cover parentID={E45A508B-6870-4523-8C60-3D302AA693A4}]Global PSPR
      address's memory segment is a valid CPUx memory segment[/cover] */
  if ((PsprMsb != (uint8)MCAL_MEM_SEGMENT2_MSB) &&
      (PsprMsb <= (uint8)MCAL_CORE0_MEM_SEGMENT) &&
      (PsprMsb >= Mcal_kCoreXMemSegment[(MCAL_COREID_MAX_VALUE)]))
  {

    LocalRetAddress = (LocalRetAddress & (uint32)MCAL_PSPR_GLOBAL_MASK_N);
    /* Is GlobalPsprAddress within the PSPR address range */
    /* [cover parentID={0A6EDA28-0C9F-4f61-BE7A-CF5254FC561E}]GlobalPspr
        Address within the PSPR address range[/cover] */
    if((LocalRetAddress >= Mcal_kPsprGlobalBaseAddress
        [MCAL_CORE0_MEM_SEGMENT - PsprMsb]) && (LocalRetAddress <=
            Mcal_kPsprGlobalEndAddress[MCAL_CORE0_MEM_SEGMENT - PsprMsb]))
    {
      /* Compute Local PSPR address */
      /* [cover parentID={2C9717B8-872D-46ac-88C1-195339372B6E}]Compute
         Local PSPR address[/cover] */
      RetLocalAddress =
                        (uint32)((LocalRetAddress & (uint32)MCAL_PSPR_ADDRESS_MASK_N)
                                 | (uint32)MCAL_LOCAL_PSPR_BASE_ADDR);
    }
  }
  else
  {
    /* Does GlobalPsprAddress belong to memory segment 0xC */
    /* [cover parentID={49C478D4-2415-4338-B240-445B9CA08490}]GlobalPspr
        Address belong to memory segment 0xC[/cover] */
    if (PsprMsb == (uint8)MCAL_VALID_PSPR_MSB)
    {
      /* Is GlobalPsprAddress a valid local PSPR address belonging
                        to the executing core */
      /* [cover parentID={3A55B630-2EEB-4968-A499-49366CCC5792}]
         GlobalPsprAddress a valid local PSPR address belonging to the
         executing core[/cover] */
      if(LocalRetAddress <= Mcal_kPsprLocalEndAddress[CpuIndex])
      {
        /*[cover parentID={6552A987-2D25-4170-9013-3028CB051E91}]Return
            Local PSPR address[/cover] */
        RetLocalAddress = GlobalPsprAddress;
      }
    }

  }
  /* [cover parentID={6552A987-2D25-4170-9013-3028CB051E91}]Return Local PSPR
    address[/cover] */
  /* [cover parentID={9D170B96-D5E4-46c2-B034-1A6C9734C791}]Return Local PSPR
    address 0[/cover] */
  return (RetLocalAddress);
}

/*******************************************************************************
** Traceability     : [cover parentID={106361C3-AE5B-4684-9B55-96C57BF8AC41}] **
**                                                                            **
** Syntax           : uint32 Mcal_DelayTickResolution (void)                  **
**                                                                            **
** Description      : The interface is used by applications to retrieve in    **
**                    nanoseconds the resolution of the delay tick (STM timer)**
**                                                                            **
** Service ID       : 0x8C                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Resolution of STM timer delay tick in nanoseconds       **
**                                                                            **
*******************************************************************************/
uint32 Mcal_DelayTickResolution(void)
{
  /* Return the STM timer resolution is 1ns resolution */
  return (Mcal_StmTimerResolution);
}

/*******************************************************************************
** Traceability     : [cover parentID={06D30CED-D581-4f9d-88B2-BF39C78EA317}] **
**                                                                            **
** Syntax           : uint32 Mcal_DelayResetTickCalibration(void)             **
**                                                                            **
** Description      : The interface is used by applications to indicate to    **
**                    MCALLib that the clock tree has changed. The expectation**
**                    is that as a result of invocation of this service, any  **
**                    internally cached tick resolution data is discarded.    **
**                    This service is expected to query the clock tree and    **
**                    determine the resolution. The interface returns in      **
**                    nanoseconds the resolution of the delay tick (STM timer)**
**                                                                            **
** Service ID       : 0x86                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Resolution of delay tick in nanoseconds                 **
**                                                                            **
*******************************************************************************/
uint32 Mcal_DelayResetTickCalibration(void)
{
  /* Added local variable TimerResolution to hold value of STM timer resolution */
  uint32 TimerResolution;

  /* [cover parentID={2203708E-A73E-4414-AC15-6ECB9D9A5858}]
     Calculate STM timer resolution in 1ns resolution[/cover] */
  /* [cover parentID={C59047B9-C9CC-4b5a-B2CD-EBE16E90A41B}][/cover] */
  /* Local variable assigned value of Mcal_lDelayResetTickCalibration
  to avoid violation of CertC rule : EXP30-C Do not depend on the order 
  of evaluation for side effects*/
  TimerResolution = Mcal_lDelayResetTickCalibration(MCALLIB_SID_DELAYTICKRESOLUTION);
  Mcal_StmTimerResolution = TimerResolution;

  /* [cover parentID={F8D3FCA6-8D9A-406c-8E9F-28E04CFBFB5B}]
   Return STM timer resolution[/cover] */
  return (Mcal_StmTimerResolution);
}

/*******************************************************************************
** Traceability     : [cover parentID={B90FF39B-C537-412f-8234-E9B0307B4D62}] **
** [/cover]                                                                   **
** Syntax           : uint32 Mcal_DelayGetTick (void)                         **
**                                                                            **
** Description      : This interface is used by applications to retrieve the  **
**                    latest tick count of the underlying STM timer. The      **
**                    latest tick count in STM0_TIM0 is returned by this      **
**                    interface. There are two uses of this interface.        **
**                    Applications can retrieve a base tick count, add the    **
**                    desired delay to the base tick count and arrive at a    **
**                    terminal tick count. Applications can also then         **
**                    periodically invoke this interface to determine if the  **
**                    underlying timer has counted up to the terminal tick    **
**                    count.                                                  **
**                                                                            **
** Service ID       : 0x8A                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Latest lower 32 bit counter value of STM0 timer         **
**                                                                            **
**                                                                            **
*******************************************************************************/
uint32 Mcal_DelayGetTick(void)
{
  uint32 DelayTick = MCAL_GET_STM_TICK();
  return DelayTick;
}

/*******************************************************************************
** Traceability     :[cover parentID={1800AF01-292F-4937-B75B-A5A1CD450B30}]  **
**  [/cover]                                                                  **
** Syntax           : uint32 Mcal_GetCpuIndex (uint32 CpuId)                  **
**                                                                            **
** Description      : This interface is used by applications in a multicore   **
**                    environment to determine the CPU they are executing on. **
**                    The API returns the contents of CORE_ID register,       **
**                   variable, structure for the core on which it is invoked. **
**                                                                            **
** Service ID       : 0x89                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Returns the Core Index corresponding to the input       **
**                    physical Core Id. In case the input Core Id is an       **
**                    invalid value, then the API returns 0xFFFFFFFF          **
**                                                                            **
*******************************************************************************/
uint32 Mcal_GetCpuIndex(void)
{
  uint32 CpuIndex = Mcal_lGetCpuIndex();

  /* [cover parentID={1CEDCBE5-ECC4-42da-B01B-10D366516465}]
   * Return the core Id
   * [/cover] */
  return CpuIndex;
}

/* [cover parentID={1B3AF15C-FD6B-43a1-8ACB-D951C425066B}]
   McalLib_GetVersionInfo
   [/cover] */
/*******************************************************************************
** Traceability     : [cover parentID={79233180-2CAD-4a65-A94F-FEB42233EEC0}] **
** [/cover]                                                                   **
** Syntax           : void McalLib_GetVersionInfo                             **
**                                (Std_VersionInfoType* const versioninfo)    **
** Description      : Function "McalLib_GetVersionInfo" shall have means to   **
**                    provide the version information of the MCALLIB module.  **
**                                                                            **
** Service ID       : 0x79                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : versioninfo - Pointer to where to store the version     **
                      information of MCALLIB module.                          **
**                                                                            **
** Parameters (out) : MCALLIB version information                             **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void  McalLib_GetVersionInfo(Std_VersionInfoType* const versioninfo)
{
  /* [cover parentID={469F845E-C354-42a3-B671-C8CB1FF18715}]
     If SAFETY Error Check is Enabled[/cover] */
  /* [cover parentID={8DE01E71-D128-4972-B0AF-D082246619F6}]
     Error check[/cover] */
  #if (MCALLIB_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={3E0E8009-CCD1-4404-A60B-EDED50CA216F}]
   Check if input parameter is null pointer[/cover] */
  if ((versioninfo) == NULL_PTR)
  {
    /* [cover parentID={64253942-C0B1-4ade-BC23-FAA4429C18A8}]
       Report error MCALLIB_E_PARAM_POINTER[/cover] */
    Mcal_lReportError(MCALLIB_SID_GETVERSIONINFO, MCALLIB_E_PARAM_POINTER);
  }
  /* [cover parentID={75420898-D793-4c5f-94E0-2E9C44DA3DEB}]
     Have all check passed?[/cover] */
  else
  #endif
  {
    /* [cover parentID={100FDF35-3B62-4c30-9799-B7F79121EF87}]
    Retrieve the version information of the module[/cover] */
    ((Std_VersionInfoType*)(versioninfo))->vendorID = (uint16)MCALLIB_VENDOR_ID;

    /* Get McalLib Module ID */
    ((Std_VersionInfoType*)(versioninfo))->moduleID = (uint16)MCALLIB_MODULE_ID;

    /* Get McalLib module Software major version */
    ((Std_VersionInfoType*)(versioninfo))->sw_major_version =
                                                (uint8)MCALLIB_SW_MAJOR_VERSION;

    /* Get McalLib module Software minor version */
    ((Std_VersionInfoType*)(versioninfo))->sw_minor_version =
                                                (uint8)MCALLIB_SW_MINOR_VERSION;

    /* Get McalLib module Software patch version */
    ((Std_VersionInfoType*)(versioninfo))->sw_patch_version =
                                                (uint8)MCALLIB_SW_PATCH_VERSION;
  }
}

/*******************************************************************************
** Traceability     : [cover parentID={FDC04393-3918-4d1a-BD98-97EB51ACDAB3}] **
** [/cover]                                                                   **
** Syntax           : void Mcal_GetSpinlock                                   **
**                    ( volatile uint32 * const LockAddress,                  **
**                             const uint32 Timeout)                          **
**                                                                            **
** Description     : This API will check if spinlock is available in an non   **
**                   atomic fashion and if spinlock is free then it is        **
**                   acquired in an atomic fashion acquired else it will      **
**                   try again until the timer tick provided by user is not   **
**                   less than difference between current and base stm ticks  **
**                                                                            **
** Service ID       : 0x8D                                                    **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : LockAddress - It is used to lock the shared variables.  **
**                    Timeout - It is total time provided in micro second by  **
**                              user using which spinlock should be acquired. **
**                              Timeout value should be in range of 1 us to   **
**                              1048575 us (timeout when passed as 1 indicate **
**                              as 1 us to this API).                         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None.                                                   **
*******************************************************************************/
void Mcal_GetSpinlock(volatile uint32 *const LockAddress, const uint32 Timeout)
{
  /* [cover parentID={A6FC0022-BE1B-4764-9527-D4B928AADD62}]
     If SAFETY Error Check is Enabled[/cover] */
  #if (MCALLIB_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={F361A66A-5290-4fed-ABF2-9547AFB2BBAE}]
     Check if input address is null pointer[/cover] */
  if ((LockAddress) == NULL_PTR)
  {
    /* [cover parentID={49CFCB8A-36C7-4dc0-BD9F-C28247C3EDEC}]
       Report error MCALLIB_E_PARAM_POINTER[/cover] */
    Mcal_lReportError(MCALLIB_SID_GETSPINLOCK, MCALLIB_E_PARAM_POINTER);
  }
  else
  #endif
  {
    /* [cover parentID={78961246-9CDD-4da7-AD8A-4F80AF6C948A}]
     * Acquire the Lock
     * [/cover] */
    Mcal_lGetSpinlock(LockAddress, Timeout, MCALLIB_SID_GETSPINLOCK);
  }
  return;
}

/*******************************************************************************
** Traceability     : [cover parentID={87DDCCC6-8C0A-4942-B49F-A3BABA4BFCA2}] **
** [/cover]                                                                   **
** Syntax           : void Mcal_ReleaseSpinlock                               **
**                               (volatile uint32 * const LockAddress)        **
**                                                                            **
** Description     : This API will release the Spinlock and value of lock     **
                     address will be 0x0U.                                    **
**                                                                            **
**                                                                            **
** Service ID      : 0x8E                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters(in)  : LockAddress - Lock that needs to be cleared(release)     **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
void Mcal_ReleaseSpinlock(volatile uint32 * const LockAddress)
{
  /* [cover parentID={1CE56696-4A08-4fca-ADF7-6443897F9F9A}]
     If SAFETY Error Check is Enabled[/cover] */
  #if (MCALLIB_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={E8246BFE-9198-46ec-989E-075408125C86}]
     Check if input address is null pointer[/cover] */
  if ((LockAddress) == NULL_PTR)
  {
    /* [cover parentID={A3DF5750-8B9E-43dc-8859-853BADDD7CEA}]
        Report error MCALLIB_E_PARAM_POINTER[/cover] */
    Mcal_lReportError(MCALLIB_SID_RELSPINLOCK, MCALLIB_E_PARAM_POINTER);
  }
  /* [cover parentID={3B173FA2-D1EF-49f7-B05E-6E14223B735D}]
     If address is not null pointer [/cover] */
  else
  #endif
  {
    Mcal_lReleaseSpinlock(LockAddress);
  }
}

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/

/*******************************************************************************
** Traceability     : [cover parentID={B0B9072D-629B-49f7-9E87-BC4CF2A925D4}] **
** [/cover]                                                                   **
**                                                                            **
** Syntax           : LOCAL_INLINE uint32  Mcal_lCpuPwSequence                **
**                    (                                                       **
**                      const uint32 CpuIndex,                                **
**                      const uint32 WdtCpuCon0Value                          **
**                    )                                                       **
**                                                                            **
** Description      : This function returns the password to be used during    **
**                    'password access' of WDTCPUxCON0 to unlock the register **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : CpuIndex -  CpuIndex corresponding to CPU Core Id       **
**                    WdtCpuCon0Value -  Contents of register WDTCPUxCON0     **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : password to be written to WDTCPUxCON0 to unlock it      **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32  Mcal_lCpuPwSequence(const uint32 CpuIndex,
                                         const uint32 WdtCpuCon0Value)
{
  uint32 PwdBit0Value;

  /* [cover parentID={B44279C3-41FF-4e95-8F82-33919982A41E}]
  Decrypt the password extracted from WdtCpuCon0 reg[/cover] */
  uint32 Password = Mcal_lDecryptPw(WdtCpuCon0Value);

  /* Check if Auto sequence password is enabled */
  /* [cover parentID={8764C622-562B-499e-BF57-7F467B553FCF}]
     Check if Automatic password sequencing is enable[/cover] */
  if (Mcal_GetBitAtomic(MODULE_SCU.WDTCPU[CpuIndex].SR.U,
                        IFX_SCU_WDTCPU_SR_PAS_OFF, IFX_SCU_WDTCPU_SR_PAS_LEN) ==
                        MCAL_AUTO_PWD_SEQ_ENABLED)
  {
    /*  Modify the password with expected password by calculating new
     *  14-bit LFSR with characteristic polynomial x14+x13+x12+x2+1.*/
    /* [cover parentID={C5E54F01-B967-4f08-BB1D-6147BE98DEAE}]
    Calculate the next password based upon a 14 bit 'Linear Feedback Shift
    Register' .[/cover] */
    PwdBit0Value = (((Password >> 1U) ^ (Password >> MCAL_PASSEQSHIFT) ^
                     (Password >> MCAL_PASSWORD_SHIFT) ^
                     (Password >> MCAL_LFSR_SHIFT)) & (uint32)1U);

    Password = (((Password << 1U) | PwdBit0Value ) &
                 (uint32)IFX_SCU_WDTCPU_CON0_PW_MSK);
  }
  /* [cover parentID={A3754FD3-C09F-48d8-BF9C-D11CD9E3BC51}]
     Return the password without modification[/cover] */
  /* [cover parentID={56281BA0-25B6-45a7-AB4E-FFE889986FC4}]
    Return password[/cover] */
  return (Password);
}

/*******************************************************************************
** Traceability     : [cover parentID={5523EAB3-5C07-4194-B205-26B2921B84CB}] **
** [/cover]                                                                   **
**                                                                            **
** Syntax           : LOCAL_INLINE uint32 Mcal_lCpuRelValue                   **
**                    (                                                       **
**                      const uint32 CpuIndex,                                **
**                      const uint32 WdtCpuCon0Value                          **
**                    )                                                       **
**                                                                            **
** Description      : This function returns the timer reload value to be used **
**                    during 'password access' of WDTCPUxCON0 to unlock the   **
**                    register                                                **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : CpuIndex -  CpuIndex corresponding to CPU Core Id       **
**                    WdtCpuCon0Value -  Contents of register WDTCPUxCON0     **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : timer reload value  to be written to WDTCPUxCON0 to     **
**                    unlock it                                               **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Mcal_lCpuRelValue(const uint32 CpuIndex,
                                      const uint32 WdtCpuCon0Value)
{
  uint32 TimerReload;

  /* Is Timer check enabled */
  /* [cover parentID={D511EF7F-5C92-4103-98CF-A5F8EC01DA99}]
   Check If  WDTCPUxSR register TCS bit is enable[/cover] */
  if (Mcal_GetBitAtomic(MODULE_SCU.WDTCPU[CpuIndex].SR.U,
                        IFX_SCU_WDTCPU_SR_TCS_OFF,
                        IFX_SCU_WDTCPU_SR_TCS_LEN) == MCAL_TIMER_CHECK_ENABLED)
  {
    /* Compute Timer reload value based on the inverted value of
     * running WDT timer value */
    /* [cover parentID={D1B6CC5D-442B-4413-9887-CFCBFCBBA7AF}]
     * Timer reload value give inverted value of current timer value obtain
     * from WDTCPUxSR.TIM [/cover] */
    TimerReload = (((MODULE_SCU.WDTCPU[CpuIndex].SR.U) &
                     MCAL_CPUWDTSR_TIMER_MASK) >> IFX_SCU_WDTCPU_SR_TIM_OFF);

    TimerReload = ((~TimerReload) & (uint32)IFX_SCU_WDTCPU_SR_TIM_MSK);
  }
  /* [cover parentID={81383C2C-9BA0-4b49-B811-EB98942760DC}]
    From input WDTCPUxCON0 extract timer reload value [/cover] */
  else
  {
    /* [cover parentID={81383C2C-9BA0-4b49-B811-EB98942760DC}]
     * From input WDTCPUxCON0 extract timer reload value [/cover] */
    /* Compute Timer reload value based on the current timer reload value */
    TimerReload = ((WdtCpuCon0Value & (uint32)MCAL_ENDINIT_RELOAD_MASK) >>
                   IFX_SCU_WDTCPU_CON0_REL_OFF);
  }
  /* [cover parentID={978E3EE6-83B3-4387-BB63-1AD7D2E83877}]
   * Return timer reload value[/cover] */
  return (TimerReload);
}

/*******************************************************************************
** Traceability     : [cover parentID={0919090F-C59B-47be-8A63-0E22F481D743}] **
** [/cover]                                                                   **
**                                                                            **
** Syntax           : LOCAL_INLINE uint16 Mcal_lDecryptPw                     **
**                    (                                                       **
**                      const uint32 Value                                    **
**                    )                                                       **
**                                                                            **
** Description      : This function returns the decrypted password, which is  **
**                    used to in unlocking the ENDINIT registers              **
**                    (EICON0/SEICON0/WDTCPUxCON0)                            **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : Value -  Data from which password is extracted          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : the decrypted password                                  **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint16 Mcal_lDecryptPw(const uint32 Value)
{
  /* Decrypt the password, by extract password from positions [15:2], and
   * inverting the last 6 bits on the extracted password
   */
  return((uint16)(((Value & (uint32)MCAL_ENDINIT_WDT_PWD_MASK) >>
                    IFX_SCU_WDTCPU_CON0_PW_OFF) ^
                    (uint32)MCAL_ENDINIT_WDT_PWD_INV));
}

/*******************************************************************************
** Traceability     : [cover parentID={4C12BC33-B548-4ac7-86E4-F0EAB7DAF746}] **
** [/cover]                                                                   **
**                                                                            **
** Syntax           : void Mcal_lWriteSafetyEndInitProtection                 **
                      ( volatile void* const RegAddress,                      **
                        const uint32 DataValue,                               **
                        const uint32 Mask,                                    **
                        const uint8  Accesstype,                              **
                        const uint8  ApiId)                                   **
**                                                                            **
** Description      : This API is needed to write required values to safety   **
**                    end-init protected registers by unprotecting to write   **
**                    and protecting back to keep protection intact. This     **
**                    interface also supports write access to safety endinit  **
**                    protected CSFRs.                                        **
**                                                                            **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : RegAddress - Safety Endinit protected register address  **
**                    DataValue - Value to be written to the register located **
**                    at RegAddress.                                          **
**                    Mask - Value to indicate which register bits need       **
**                    to be updated.                                          **
**                    Accesstype - Register access type - 16/32 bit           **
**                    ApiId - Service ID of the API reporting an error        **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Mcal_lWriteSafetyEndInitProtection
                                               (volatile void* const RegAddress,
                                                const uint32 DataValue,
                                                const uint32 Mask,
                                                const uint8  Accesstype,
                                                const uint8  ApiId)
{
  /* MISRA2012_RULE_11_5_JUSTIFICATION: Conversion between
   * pointer to void and pointer to object due to SFR access. */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between
   * pointers of different object types due to SFR access. */
  volatile uint32* const RegAddress32 = RegAddress;
  /* MISRA2012_RULE_11_5_JUSTIFICATION: Conversion between
   * pointer to void and pointer to object due to SFR access. */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between
   * pointers of different object types due to SFR access. */
  volatile uint16* const RegAddress16 = RegAddress;
  uint32 TempData;
  /* MISRA2012_RULE_11_6_JUSTIFICATION: The address of the register is
   * comapred against CSFR register offsets.
   * There are no other operation performed, hence this convesion
   * does not cause any issue */
  uint32 TempAddr = (uint32)RegAddress;

  /* Mask the DataValue as per the passed Mask */
  uint32 MaskedData = DataValue & Mask;

  /* Critical section to protect SCU_SEICON0 and SCU_SEICON1 register*/
  /* [cover parentID={65DFF53B-24CB-4967-90D4-398D7423E928}]
      Enter critical section for write safety endinit protection reg
      [/cover] */
  SchM_Enter_McalLib_SafetyEndInit();

  /* Acquire the lock for SCU_SEICON0 register */
  /* [cover parentID={8F370CDA-A0DE-4695-800F-C7CC570256BA}]
      Acquire the lock for SCU_SEICON0 register
     [/cover] */
  Mcal_lGetSpinlock(&Mcal_LockAddressSiecon0, \
                   (uint32)MCAL_SPINLOCK_DEFAULT_TIMEOUT, ApiId);

  /* Reset Safety EndInit Protection*/
  /* [cover parentID={41EA97F8-07A4-4da6-B2EE-768CB3D7B6CC}]
      Reset Safety EndInit Protection
     [/cover] */
  (void)Mcal_lUpdateSafetyEndInit(MCAL_DUMMY_PASSWORD,
                            MCAL_NOUPDATE_PASSWORD,
                            MCAL_RESETENDINITPROTECTION);

  /* Update the register */
  /* Note: CPU specific registers are updated using MTCR */
  /* [cover parentID={F391CD55-6DFA-4ad8-A795-5D43D6AB5D84}][/cover] */
  if (TempAddr > MCAL_16BIT_MAX_ADDR)
  {
    /* [cover parentID={DCB30C5F-21C5-498f-A219-EE8F508CD5F4}]
        Check the AccessType is  32bit access
       [/cover] */
    if (Accesstype == MCAL_32BIT_ACCESS)
    {
      /* Check if the masking is required */
      /* [cover parentID={9FB76018-74B9-498a-B8E8-953D7C6DAFCA}][/cover] */
      if(Mask == MCAL_DEFAULT_MASK_VALUE)
      {
        *RegAddress32 = MaskedData;
      }
      else
      {
        /* Read the SFR and write only the bits based on the mask */
        TempData = (uint32)(((uint32) *RegAddress32 & (uint32)~Mask) |
                   MaskedData);

        *RegAddress32 = TempData;
      }
    }
    else
    {
      /* [cover parentID={5CE8820B-A554-4941-96F3-349D18198A5C}]
       * Update the register
       * [/cover]
       */
      *RegAddress16 = (uint16)MaskedData;
    }
  }
  else
  {
    /* CPU specific registers are updated using MTCR */
    /* MISRA2012_RULE_11_6_JUSTIFICATION: The address of the register is
     * comapred against CSFR register offsets.
     * There are no other operation performed, hence this convesion
     * does not cause any issue */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: The address of the register is
     * comapred against CSFR register offsets.
     * There are no other operation performed, hence this convesion
     * does not cause any issue */
    /* [cover parentID={7952E564-BA1D-4caf-9925-D47BEC3B5F1D}][/cover] */
    switch((uint32)RegAddress32)
    {
      case CPU_COMPAT:
          MTCR(CPU_COMPAT, MaskedData);
          break;
      case CPU_SYSCON:
          MTCR(CPU_SYSCON, MaskedData);
          break;
      case CPU_TPS_EXTIM_ENTRY_LVAL:
          MTCR(CPU_TPS_EXTIM_ENTRY_LVAL, MaskedData);
          break;
      case CPU_TPS_EXTIM_EXIT_LVAL:
          MTCR(CPU_TPS_EXTIM_EXIT_LVAL, MaskedData);
          break;
      case CPU_TPS_EXTIM_CLASS_EN:
          MTCR(CPU_TPS_EXTIM_CLASS_EN, MaskedData);
          break;
      default:
          /* This case is not possible, kept only for MISRA compliance */
          break;
    }
  }

  /* Set Safety EndInit Protection */
  /* [cover parentID={3F7731FF-CE60-4306-925E-5E21E8BCAFBE}]
     Set Safety EndInit Protection
     [/cover] */
  (void)Mcal_lUpdateSafetyEndInit(MCAL_DUMMY_PASSWORD,
                            MCAL_NOUPDATE_PASSWORD,
                            MCAL_SETENDINITPROTECTION);

  /* Release the lock for SCU_SEICCON0 register */
  /* [cover parentID={C129F8E9-E64D-4ae7-906D-902988D55FA1}]
     Release the lock for SCU_SEICCON0 register
     [/cover] */
  Mcal_lReleaseSpinlock(&Mcal_LockAddressSiecon0);

  /* [cover parentID={D7BCD4A4-FA36-476d-A582-088869946097}]
      Exit critical section for write safety endinit protection reg
     [/cover] */
  SchM_Exit_McalLib_SafetyEndInit();
}

/*******************************************************************************
** Traceability     :[cover parentID={1CCEB859-15A4-4d14-98E6-0191C58E03B5}]  **
**                   [/cover]                                                 **
**                                                                            **
** Syntax           :LOCAL_INLINE uint32 Mcal_lDelayResetTickCalibration      **
**                                                        (const uint8 ApiId) **
**                                                                            **
** Description      : The interface is used by applications to indicate to    **
**                    MCALLib that the clock tree has changed. The expectation**
**                    is that as a result of invocation of this service, any  **
**                    internally cached tick resolution data is discarded.    **
**                    This service is expected to query the clock tree and    **
**                    determine the resolution. The interface returns in      **
**                    nanoseconds the resolution of the delay tick (STM timer)**
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : ApiId - Service ID of the API reporting an error        **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Resolution of delay tick in nanoseconds                 **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Mcal_lDelayResetTickCalibration(const uint8 ApiId)
{
  float32 StmFreq, PLL0Freq;
  float32 LocalStmTimerResol = (float32)0;
  uint32 OscFreq;
  uint8 StmDiv, Src0ClkSel, PLL0Ndiv, PLL0Pdiv, PLL0K2div, Oscval, PLL0ClkSel;


  /* [cover parentID={0245DED7-5AFC-4f35-876D-AEC5118EE056}]
      Enter critical section[/cover] */
  SchM_Enter_McalLib_StmTimerResolution();

  StmDiv     = (uint8)(((uint32)MODULE_SCU.CCUCON0.U)  &
                             (uint32)IFX_SCU_CCUCON0_STMDIV_MSK);
  Src0ClkSel = (uint8)((((uint32)MODULE_SCU.CCUCON0.U) >>
                              IFX_SCU_CCUCON0_CLKSEL_OFF) &
                             (uint32)IFX_SCU_CCUCON0_CLKSEL_MSK);
  PLL0Ndiv   = (uint8)((((uint32)MODULE_SCU.SYSPLLCON0.U) >>
                              IFX_SCU_SYSPLLCON0_NDIV_OFF) &
                             (uint32)IFX_SCU_SYSPLLCON0_NDIV_MSK) + (uint8)1U;
  PLL0Pdiv   = (uint8)((((uint32)MODULE_SCU.SYSPLLCON0.U) >>
                              IFX_SCU_SYSPLLCON0_PDIV_OFF) &
                             (uint32)IFX_SCU_SYSPLLCON0_PDIV_MSK) + (uint8)1U;
  PLL0K2div  = (uint8)(((uint32)MODULE_SCU.SYSPLLCON1.U) &
                             (uint32)IFX_SCU_SYSPLLCON1_K2DIV_MSK) + (uint8)1U;
  Oscval     = (uint8)((((uint32)MODULE_SCU.OSCCON.U) >>
                              IFX_SCU_OSCCON_OSCVAL_OFF) &
                             (uint32)IFX_SCU_OSCCON_OSCVAL_MSK);
  PLL0ClkSel = (uint8)((((uint32)MODULE_SCU.SYSPLLCON0.U) >>
                              IFX_SCU_SYSPLLCON0_INSEL_OFF) &
                             (uint32)IFX_SCU_SYSPLLCON0_INSEL_MSK);

  /* [cover parentID={AABD4D00-A372-4e29-B360-0543BA412484}]
     Exit critical Section[/cover] */
  SchM_Exit_McalLib_StmTimerResolution();

  /* If fSTM is disabled, then return timer resolution as 0 */
  /* [cover parentID={9AEC7374-8E25-4936-AA51-224738F39F36}]
   * Check if STM clock disabled[/cover] */
  if(StmDiv == (uint8)MCAL_STMCLK_DISABLED)
  {
    /* [cover parentID={7DB1FA52-2712-4daa-8EB3-5D3BF1CBF02D}]If SAFETY
     * Error Check is Enabled[/cover] */
    /* [cover parentID={96699695-17F2-4fa8-AC73-49A2C470DC33}]If SAFETY
     * Error Check is Enabled[/cover] */
    /* [cover parentID={21BC6F5D-85A7-4d5a-BFBB-C782B3FEC56B}]If SAFETY
     * Error Check is Enabled[/cover] */
    #if (MCALLIB_SAFETY_ENABLE == STD_ON)
    /* [cover parentID={8A536F85-CDD2-4a3d-AF62-D1744ABCD2CF}]
     * Report error MCALLIB_E_CLKDISABLE[/cover] */
    Mcal_lReportError(ApiId, MCALLIB_E_CLKDISABLE);
    #endif

    Mcal_StmTimerResolution = MCAL_STM_TIMER_RESOL_ZERO;
  }
  else
  {
    /* Check the source of fSource0 - PLL0 or backup clock */
    /* [cover parentID={344D24C2-972E-432e-8A0A-9ED87525D74A}]
       Check the Source of freq PLL0 clock sel[/cover] */
    if(Src0ClkSel == (uint8)MCAL_PLL0_CLK_SRC0_FREQ)
    {
      /* Check the source of fPLL0 - backup clock or OSC0*/
      /* [cover parentID={344D24C2-972E-432e-8A0A-9ED87525D74A}]
         Check the Source of freq PLL0 clock sel[/cover] */
      switch(PLL0ClkSel)
      {
        /*Fall through is used as the logic for oscillator frequency
         * calculation and SYSCLK frequency calculation is exactly same*/
        /* [cover parentID={5EB344C3-9A2B-4bca-92AA-9B89A1FE3DDA}]
            Is PLL0 clock source Osc 0 clock [/cover] */
        case MCAL_OSC0_CLK_PLL0_FREQ:
        case MCAL_SYS_CLK_PLL0_FREQ:
          /* Calculate OSC0 frequency(its in MHz)*/
          /* [cover parentID={2073EAEB-1D43-47da-A1B4-608B3846D17A}]Calculate
             OSC_ClockFreq [/cover] */
          OscFreq = ((uint32)Oscval +
                     (uint32)MCAL_OSCVAL_MHz - (uint32)MCAL_OSCFREQ_MHz);
          break;
        default:
          /* [cover parentID={B8FBCFA9-AACF-4dbe-8D8F-AD75CFEE3751}]
                     OSC_ClockFreq is Backup Clock frequency[/cover] */
          OscFreq = MCAL_BACKUP_FREQUENCY;
          break;
      }
      /* Calculate PLL0 freq by formula = (fOSC * Ndiv)/(K2div * Pdiv)*/
      /* [cover parentID={DEC7141C-7011-422c-8C9E-4B270FE50403}]Calculate
         PLL0_Clockfreq using Oscfreq,Ndiv, Pdiv, K2div[/cover] */
      PLL0Freq = (((float32)OscFreq * (float32)PLL0Ndiv) /
                  ((float32)PLL0Pdiv * (float32)PLL0K2div));
      /* Calculate fSTM */
      /* [cover parentID={CE793E76-8F55-4fc5-9B98-CA024C14371D}]Calculate
      Stm_Freq using PLL0_Clockfreq ,StmDiv[/cover] */
      StmFreq = PLL0Freq / (float32)StmDiv;
    }
    else
    {
      /* Calculate fSTM */
      /* [cover parentID={3E42C595-B418-4c0f-9181-5D89C75125C1}]
      Calculate STM freq depends on Backup Clock freq and STM divider
      [/cover] */
      StmFreq = (float32)MCAL_BACKUP_FREQUENCY / (float32)StmDiv;
    }

    /* Mcal_StmTimerResolution in 1ns resolution is obtained by
     * (10^9)/(StmFreq * 10^6), since value of StmFreq is MHz,
     *  Mcal_StmTimerResolution = 10^9/(StmFreq * 10^6)
     *  Mcal_StmTimerResolution = 10^3/(StmFreq)
     */
    /* [cover parentID={205F9729-B78C-4ff6-B5A4-4CF0A0512ABD}]Calculate STM
    timer resolution in 1ns resolution[/cover] */
    LocalStmTimerResol = ((float32)MCAL_RESOLUTION_U / StmFreq);
  }

  /* This is used to avoid MISRA when Safety is switched OFF */
  UNUSED_PARAMETER(ApiId);

  /* [cover parentID={E1412D6E-B1C5-4683-AEFA-730560F0772F}]
   * Return STM timer resolution[/cover]
   */
  /* [cover parentID={19F230D8-6462-4c4d-9833-2618D4960F84}]
   * return STM timer resolution zero[/cover]
   */
  return ((uint32)LocalStmTimerResol);
}

#if (MCALLIB_SAFETY_ENABLE == STD_ON)
/*******************************************************************************
** Traceability     :[cover parentID={D5D6528A-4A62-42dc-9C9D-5F09340FBFB0}]  **
**                   [/cover]                                                 **
** Syntax :          LOCAL_INLINE void Mcal_lReportError(const uint8 ApiId,   **
**                                                const uint8 ErrorId)        **
**                                                                            **
** Service ID:       NA                                                       **
** [/cover]                                                                   **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  ApiId - Service ID of the API reporting an error         **
**                   ErrorId - ID of the error reported                       **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
** Description :    Function to report Safety Error                           **
*                                                                             **
*******************************************************************************/
LOCAL_INLINE void Mcal_lReportError(const uint8 ApiId, const uint8 ErrorId)
{
  Mcal_ReportSafetyError(MCALLIB_MODULE_ID, MCALLIB_INSTANCE_ID,
                         ApiId, ErrorId);
}
#endif

/*******************************************************************************
** Traceability     : [cover parentID={1912F5BE-EDDE-484a-A31F-F3475F2A59FD}] **
** [/cover]                                                                   **
** Syntax           : uint32 Mcal_lGetCpuIndex(void)                          **
**                                                                            **
** Description      : This interface is used by applications in a multicore   **
**                    environment to determine the CPU they are executing on. **
**                    The API returns the contents of CORE_ID register,       **
**                   variable, structure for the core on which it is invoked. **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Returns the Core Index corresponding to the input       **
**                    physical Core Id. In case the input Core Id is an       **
**                    invalid value, then the API returns 0xFFFFFFFF          **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Mcal_lGetCpuIndex(void)
{
  /* [cover parentID={B7499D38-0AD1-42ce-BD5F-BA67D72B3DED}]
   * Read the CPU_CORE_ID register to retrieve the CoreIdIndex [/cover]
   */
  uint32 CoreIdIndex = (uint32)MFCR(CPU_CORE_ID);
  #if ( MCAL_NO_OF_CORES > 5U )
  /* If the CpuId is greater than, equal to that of CPU5 Core Id(0x6U),
   * then return CoreIndex as (CpuId - 1),
   * else return the same value as input CpuId */
  /* [cover parentID={DF2416E6-335D-4e1f-A0FA-BAF1C1BC133C}]
  Check if CoreIdIndex is greater than, equal to number of core [/cover] */
  if (CoreIdIndex >= (uint32)MCAL_NO_OF_CORES)
  {
    CoreIdIndex = CoreIdIndex - (uint32)0x1U;
  }
  #endif

  /* [cover parentID={E8AFC2A6-8251-4e22-A852-1723FFB711C1}]
   * Return the current CoreIdIndex [/cover]
   */
  return(CoreIdIndex);
}

/*******************************************************************************
** Traceability     :[cover parentID={9979C54A-B8B4-4815-9DC3-CFD6BF59AA95}]  **
**                   [/cover]                                                 **
** Syntax           : static uint32 Mcal_lUpdateSafetyEndInit(                **
**                                          const uint32 NewPassword,         **
**                                          const boolean UpdatePassword,     **
**                                          const boolean SetResetProtection) **
**                                                                            **
** Description      : This interface updates password/enables/disable         **
**                    Safety EndInit protection                               **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : NewPassword        -  Password to be updated            **
**                    UpdatePassword     -  True  - Update Password           **
**                                          False - No password update        **
**                    SetResetProtection -  True  - Enable ENDINIT protection **
**                                          False - Disable ENDINIT protection**
**                                                                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Password - Password retrieved from SCU_SEICON0 register **
**                                                                            **
*******************************************************************************/
static uint32 Mcal_lUpdateSafetyEndInit(const uint32 NewPassword,
                                        const boolean UpdatePassword,
                                        const boolean SetResetProtection)
{
  uint32 Password;
  uint32 Seicon0Value;
  uint32 NewSeicon0Value;
  /* The variable 'dummy' is made volatile to prevent any optimization of the
   * variable during compilation, since the variable is used only for read back
   * of ENDINIT control registers, after the same register is written in the
   * previous statement
   */
  volatile uint32 dummy;

  /* Calculate the password from the retrieved SCU_SEICON0 register */
  /* [cover parentID={B2B14FB1-F8EF-4cde-B5DA-4129BA331374}]
   * Calculate the password from the retrieved SCU_SEICON0 register[/cover]
   */
  Password = Mcal_lDecryptPw((uint32)(MODULE_SCU.SEICON0.U));

  /* [cover parentID={A8E28D51-8868-4041-ADE1-5D2A9BA8A54C}]
      Check if ENDINIT Protection needs to be Set
     [/cover] */
  if (SetResetProtection == MCAL_SETENDINITPROTECTION)
  {
    /* [cover parentID={9C14810F-46F4-4a5e-B586-CE5D22DF82D4}]
       Calculate the value to be written in SCU_SEICON0 to re-enable protection
       [/cover] */
    Seicon0Value =
                  ((uint32)MCAL_SAFETY_ENDINIT_WDT_TIMER_REL |
                    ((uint32)Password << (uint32)IFX_SCU_SEICON0_EPW_OFF) |
                    ((uint32)MCAL_SAFETY_ENDINIT_PROTECTED <<
                    IFX_SCU_SEICON0_ENDINIT_OFF));
  }
  else
  {
    /* [cover parentID={A2915C78-C633-468e-A3AE-96E629A22143}]
     * Calculate the value to be written in SCU_SEICON0 to unlock it [/cover]
     */
    Seicon0Value = ((uint32)MCAL_SAFETY_ENDINIT_WDT_TIMER_REL |
                  ((uint32)Password << (uint32)IFX_SCU_SEICON0_EPW_OFF));
  }

  /* [cover parentID={4142F921-D301-41d9-9108-17026665FD43}]
   * Check if passwprd needs to be updated[/cover]
   */
  if (UpdatePassword == MCAL_UPDATE_NEWPASSWORD)
  {
    /* Calculate the value to be written in SCU_SEICON0,
     * to update it with new password */
    /* [cover parentID={DEC55626-564E-4d36-AACE-8AA4F69DDCC8}]
     * Calculate the value to be written in SCU_SEICON0, to update it with new
     * password [/cover]
     */
    NewSeicon0Value = (uint32)((uint32)MCAL_SAFETY_ENDINIT_WDT_TIMER_REL |
                      ((uint32)NewPassword << (uint32)IFX_SCU_SEICON0_EPW_OFF) |
                      ((uint32)MCAL_SAFETY_ENDINIT_PROTECTED <<
                      (uint32)IFX_SCU_SEICON0_ENDINIT_OFF));

    /* Update the SCU_SEICON0 to enable ENDINIT protection */
    /* [cover parentID={B21BEF3D-EDEE-46b8-BC20-FCD25348DFBB}]
     * Update the SCU_SEICON0 to enable ENDINIT protection[/cover]
     */
    MODULE_SCU.SEICON0.U = Seicon0Value;

     /* [cover parentID={D4DFA4A6-F96A-4aca-9326-4A129E55ABEC}]
      * Read back the SCU_SEICON0  reg to ensure Write is is done correctly
      * [/cover]
      */
    dummy = MODULE_SCU.SEICON0.U;

    /* Update the SCU_SEICON0 with the new password */
    /* [cover parentID={010249F4-AFF9-44ca-8AA6-D9FA225088F0}]
     * Update the SCU_SEICON0 with the new password
     * [/cover]
     */
    MODULE_SCU.SEICON0.U = NewSeicon0Value;

    /* Read back the SEICON0 reg to ensure Write is is done correctly */
    /* [cover parentID={AEF500FF-30FE-4fb1-B43C-4C65434B4877}]
     * Read back the SCU_SEICON0  reg to ensure Write is is done correctly
     * [/cover]
     */
    dummy = MODULE_SCU.SEICON0.U;
  }
  else
  {
    /* [cover parentID={E6BA5EB6-33FF-4772-8389-8085A11206C5}]
     * Update the SCU_SEICON0 to enable ENDINIT protection
     * [/cover]
     */
    MODULE_SCU.SEICON0.U = Seicon0Value;
    /* [cover parentID={D41B3AF3-7A8D-45a3-990C-632AF21876D7}]
     * Read back the SCU_SEICON0  reg to ensure Write is is done correctly
     * [/cover]
     */
    dummy = MODULE_SCU.SEICON0.U;
  }

  UNUSED_PARAMETER(dummy);

  /* [cover parentID={FD7EA7AA-6F81-406b-8C2A-0F16677957F4}]
   * Return the old password [/cover]
   */
  return Password;
}

/*******************************************************************************
** Traceability     :[cover parentID={61F6C298-1B19-4592-9F11-A09849183489}]  **
**                   [/cover]                                                 **
** Syntax           : static uint32 Mcal_lUpdatePeripheralEndInit(            **
**                                          const uint32 NewPassword,         **
**                                          const boolean UpdatePassword,     **
**                                          const boolean SetResetProtection) **
**                                                                            **
** Description      : This interface updates password/enables/disable         **
**                    Peripheral EndInit protection                           **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : NewPassword        -  Password to be updated            **
**                    UpdatePassword     -  True  - Update Password           **
**                                          False - No password update        **
**                    SetResetProtection -  True  - Enable ENDINIT protection **
**                                          False - Disable ENDINIT protection**
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Password - Password retrieved from SCU_EICON0 register  **                                                    **
**                                                                            **
*******************************************************************************/
static uint32 Mcal_lUpdatePeripheralEndInit(const uint32 NewPassword,
                                            const boolean UpdatePassword,
                                            const boolean SetResetProtection)
{
  uint32 Password;
  uint32 Eicon0Value;
  uint32 NewEicon0Value;
  /* The variable 'dummy' is made volatile to prevent any optimization of the
   * variable during compilation, since the variable is used only for read back
   * of ENDINIT control registers, after the same register is written in the
   * previous statement
   */
  volatile uint32 dummy;

  /* Calculate the password from the retrieved EICON0 register */
  /* [cover parentID={72C08E75-2CBC-4e8b-9D57-DC2AFD225F73}]
   * Calculate the password from the retrieved SCU_SEICON0 register
   * [/cover]
   */
  Password = Mcal_lDecryptPw((uint32)(MODULE_SCU.EICON0.U));

  /* [cover parentID={92440BB6-B642-4820-B994-B0B7C901DA49}][/cover] */
  if (SetResetProtection == MCAL_SETENDINITPROTECTION)
  {
    /* [cover parentID={8DC0A3C6-9CFE-4d8a-A9B3-E7D2B7A3F712}]
     * Calculate the value to be written in SCU_EICON0 to re-enable protection
     * [/cover]
     */
    Eicon0Value =
                  ((uint32)MCAL_PER_ENDINIT_WDT_TIMER_REL |
                    ((uint32)Password << (uint32)IFX_SCU_EICON0_EPW_OFF) |
                    ((uint32)MCAL_PER_ENDINIT_PROTECTED <<
                    IFX_SCU_EICON0_ENDINIT_OFF));
  }
  else
  {
    /* [cover parentID={B1DD1917-EB64-4255-A13C-37283405691C}]
     * Calculate the value to be written in SCU_EICON0 to unlock it
     * [/cover]
     */
    Eicon0Value = ((uint32)MCAL_PER_ENDINIT_WDT_TIMER_REL |
                  ((uint32)Password << (uint32)IFX_SCU_EICON0_EPW_OFF));
  }

  /* [cover parentID={AC012730-EF78-4b9b-99B1-9C1909D90060}]
   * Check if passwprd needs to be updated
   * [/cover]
   */
  if (UpdatePassword == MCAL_UPDATE_NEWPASSWORD)
  {
    /* Calculate the value to be written in SCU_EICON0,
     * to update it with new password */
	 /* [cover parentID={8A80061E-1AE0-4d21-AE7E-2A80AB93C630}]
     * Calculate the value to be written in SCU_EICON0,
     * to update it with new password
     * [/cover] */
    NewEicon0Value = ((uint32)MCAL_PER_ENDINIT_WDT_TIMER_REL |
                     ((uint32)NewPassword << (uint32)IFX_SCU_EICON0_EPW_OFF) |
                     ((uint32)MCAL_PER_ENDINIT_PROTECTED <<
                     IFX_SCU_EICON0_ENDINIT_OFF));

    /* Update the SCU_EICON0 to enable ENDINIT protection */
    MODULE_SCU.EICON0.U = Eicon0Value;

    /* Read back the SCU_EICON0  reg to ensure Write is is done correctly */
    dummy = MODULE_SCU.EICON0.U;

    /* Update the SCU_SEICON0 with the new password */
    /* [cover parentID={E0716D6C-3D3D-4d96-8625-F6E0DAB3B87A}]
     * Update the SCU_SEICON0 with the new password
     * [/cover] */
    MODULE_SCU.EICON0.U = NewEicon0Value;

    /* Read back the EICON0 reg to ensure Write is is done correctly */
    dummy = MODULE_SCU.EICON0.U;
  }
  else
  {
    /* Update the SCU_SEICON0 to enable ENDINIT protection */
    /* [cover parentID={1588C1CA-ABCF-4b7b-BCE6-C665A41F2EAD}]
     * Update the SCU_SEICON0 to enable ENDINIT protection
     * [/cover] */

    MODULE_SCU.EICON0.U = Eicon0Value;

     /* [cover parentID={ADA1213B-A447-4277-BAF4-AF8299BA5A86}]
      * Read back the SCU_EICON0  reg to ensure Write is is done correctly
      * [/cover] */
    dummy = MODULE_SCU.EICON0.U;
  }

  UNUSED_PARAMETER(dummy);

  /* Return the old password */
  /* [cover parentID={C52BFE95-3C6F-4d08-BF04-AEC275D5A191}]
     * Return the old password
     * [/cover] */
  return Password;
}

/*******************************************************************************
** Traceability     :[cover parentID={DED86600-0ABE-4e8f-B5AD-199D2317A8EB}]  **
**                   [/cover]                                                 **
**                                                                            **
** Syntax           : static uint32 Mcal_lUpdateCpuEndInit(                   **
**                                          const uint32 NewPassword,         **
**                                          const uint32 CoreIdIndex.         **
**                                          const uint32 TimerRelValAtReset   **
**                                          const boolean UpdatePassword,     **
**                                          const boolean SetResetProtection) **
**                                                                            **
** Description      : This interface updates password/enables/disable         **
**                    CPU EndInit protection                                  **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Not Reentrant on same CPU, Reentrant on other CPUs      **
**                                                                            **
** Parameters(in)   : NewPassword        -  Password to be updated            **
**                    CoreIdIndex        -  Core ID                           **
**                    TimerRelValAtReset -  Timer value at ENDINIT disabled   **
**                    UpdatePassword     -  True  - Update Password           **
**                                          False - No password update        **
**                    SetResetProtection -  True  - Enable ENDINIT protection **
**                                          False - Disable ENDINIT protection**
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : CpuEndInitRet - Current password and TimerReload value  **
**                                                                            **
*******************************************************************************/
static McalLib_CpuEndInitRetType Mcal_lUpdateCpuEndInit(
                                     const uint32  NewPassword,
                                     const uint32  CoreIdIndex,
                                     const uint32  TimerRelValAtReset,
                                     const boolean UpdatePassword,
                                     const boolean SetResetProtection)
{
  McalLib_CpuEndInitRetType CpuEndInitRet;
  uint32 UnlockCpuWdtCon0Value;
  uint32 NewCpuWdtCon0Value;
  uint32 UnlockTimerReload;
  uint32 CpuWdtCon0Value;
  uint32 UnlockPassword;
  uint32 TimerReload;

  /* The variable 'dummy' is made volatile to prevent any optimization of the
   * variable during compilation, since the variable is used only for read back
   * of ENDINIT control registers, after the same register is written in the
   * previous statement
   */
  volatile uint32 dummy;

  /* Initalize to zero */
  CpuEndInitRet.TimerRelValAtReset = 0x0U;

  /* Read the WDTCPUxCON0 register */
   CpuWdtCon0Value = MODULE_SCU.WDTCPU[CoreIdIndex].CON0.U;

  /* Compute the password required to unlock the WDTCPUxCON0 register */
  UnlockPassword = Mcal_lCpuPwSequence(CoreIdIndex, (uint32)CpuWdtCon0Value);

  /* Compute the timer reload value required to unlock
   * the WDTCPUxCON0 register */
  UnlockTimerReload = Mcal_lCpuRelValue(CoreIdIndex, (uint32)CpuWdtCon0Value);

  /* Extract the current timer reload value */
  TimerReload = Mcal_lCalculateTimerReloadVal(CoreIdIndex, TimerRelValAtReset,
                                              SetResetProtection);

  /* Compute the current password, to be returned, based on the retrieved
   * WDTCPUxCON0 value */
  CpuEndInitRet.Password = Mcal_lDecryptPw((uint32)CpuWdtCon0Value);

  /* Calculate the value to be written in WDTCPUxCON0, to unlock it */
  UnlockCpuWdtCon0Value =
          (UnlockTimerReload << IFX_SCU_WDTCPU_CON0_REL_OFF) |
          (UnlockPassword << IFX_SCU_WDTCPU_CON0_PW_OFF)|
          ((uint32)MCAL_CPUWDTCON0_UNLOCK);

   /* Check if password update is requested */
   /* [cover parentID={5D303B68-3C5F-4f92-9593-9E42DC9BD5C1}]
      Check if password update is requested
      [/cover] */
  if (UpdatePassword == MCAL_UPDATE_NEWPASSWORD)
  {
    /* Calculate the value to be written in WDTCPUxCON0, to update it with
     * new password
     */
    /* [cover parentID={11FAAF91-980D-4f27-B797-29B7C0666674}]
     * Calculate the value to be written in WDTCPUxCON0 to update the new
     * password [/cover]
     */
    NewCpuWdtCon0Value = (TimerReload << IFX_SCU_WDTCPU_CON0_REL_OFF) |
                         (NewPassword << IFX_SCU_WDTCPU_CON0_PW_OFF)  |
                         ((uint32)MCAL_CPUWDTCON0_LOCK);
  }
  else
  {
    /* Check Set/Reset ENDINIT protection requested */
    /* [cover parentID={0FE372A6-78E4-4839-8263-6740A02C2AC7}]
       Check Set/Reset ENDINIT protection requested
       [/cover] */
    if (SetResetProtection == MCAL_SETENDINITPROTECTION)
    {
      /* Calculate the value to be written in WDTCPUxCON0,
       * to re-enable ENDINIT protection
       */
      /* [cover parentID={315C2D0B-B963-449f-B59D-CB9B8373F038}]
       *  Calculate the value to be written in WDTCPUxCON0, to re-enable
       *  ENDINIT protection[/cover]
       */
      NewCpuWdtCon0Value = (TimerReload << IFX_SCU_WDTCPU_CON0_REL_OFF) |
                           (CpuEndInitRet.Password <<
                           IFX_SCU_WDTCPU_CON0_PW_OFF)  |
                           ((uint32)MCAL_CPUWDTCON0_ENABLE_ENDINIT);
    }
    else
    {
      /* Calculate the value to be written in WDTCPUxCON0,
       * to temporarily disable ENDINIT protection
       */
      /* [cover parentID={FA68029C-B3AB-4683-8164-47E83FD2A16F}]
       * Calculate the value to be written in WDTCPUxCON0, to temporarily
       * disable ENDINIT protection and store the timer reload value
       * (required while re-enabling ENDINIT protection)[/cover]
       */
      NewCpuWdtCon0Value = (TimerReload << IFX_SCU_WDTCPU_CON0_REL_OFF) |
                           (CpuEndInitRet.Password <<
                           IFX_SCU_WDTCPU_CON0_PW_OFF)  |
                           ((uint32)MCAL_CPUWDTCON0_DISABLE_ENDINIT);

      CpuEndInitRet.TimerRelValAtReset = TimerReload;
    }
  }

  /* Unlock the WDTCPUxCON0 register */
  MODULE_SCU.WDTCPU[CoreIdIndex].CON0.U = UnlockCpuWdtCon0Value;

  dummy = MODULE_SCU.WDTCPU[CoreIdIndex].CON0.U;

  /* Update the WDTCPUxCON0 to re-enable/temporary disable ENDINIT protection */
  MODULE_SCU.WDTCPU[CoreIdIndex].CON0.U = NewCpuWdtCon0Value;

  dummy = MODULE_SCU.WDTCPU[CoreIdIndex].CON0.U;

  UNUSED_PARAMETER(dummy);

  /* [cover parentID={F2DEA58E-0358-4096-A1EA-D805864C0D80}]
     Return the old password
     [/cover] */
  return (CpuEndInitRet);
}

/*******************************************************************************
** Traceability     :[cover parentID={C9B454CE-0DAA-4ad1-958E-B32F00DE06C7}]  **
**                   [/cover]                                                 **
**                                                                            **
** Syntax           : LOCAL_INLINE uint32 Mcal_lCalculateTimerReloadVal(      **
**                                  const uint32 CoreId,                      **
**                                  const uint32 TimerRelValAtReset,          **
**                                  const boolean SetResetProtection)         **
**                                                                            **
** Description      : This interface calculates the timer reload value        **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Not Reentrant on same CPU, Reentrant on other CPUs      **
**                                                                            **
** Parameters(in)   : CoreId             -  Core ID                           **
**                    TimerRelValAtReset -  Timer value at ENDINIT disabled   **
**                    SetResetProtection -  True  - Enable ENDINIT protection **
**                                          False - Disable ENDINIT protection**
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : TimerReload - Timer reload value                        **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Mcal_lCalculateTimerReloadVal(const uint32 CoreId,
                                     const uint32 TimerRelValAtReset,
                                     const boolean SetResetProtection)
{
  uint32 TimerReload = Mcal_GetBitAtomic(MODULE_SCU.WDTCPU[CoreId].SR.U,
                                         IFX_SCU_WDTCPU_SR_TIM_OFF,
                                         IFX_SCU_WDTCPU_SR_TIM_LEN);
  /* [cover parentID={9F31EF03-A22B-400c-9BA0-DA3240B9F447}][/cover] */
  if (SetResetProtection == MCAL_SETENDINITPROTECTION)
  {
    TimerReload = TimerReload - (uint32)MCAL_ENDINIT_TIMEOUT_VALUE;

    /* Calculate the timer reload value */
    /* Timer Reload value = Current timer reload value + the WDT timer value
     * when ENDINIT protection was disabled
     */
    /* [cover parentID={AF55A6A4-A70F-4a37-A78D-3F7EEAC1943C}][/cover] */
    TimerReload = TimerReload + TimerRelValAtReset;

    if(TimerReload > (uint32)MCAL_CPUWDT_TIMER_VALUE_MAX)
    {
      TimerReload = MCAL_CPUWDT_TIMER_VALUE_MAX;
    }
  }

  return TimerReload;
}

/*******************************************************************************
** Traceability     : [cover parentID={EEAA8C0B-6BD5-462e-A3D8-3116EF8B6747}] **
** [/cover]                                                                   **
** Syntax          : void Mcal_lGetSpinlock                                   **
**                    ( volatile uint32 * const LockAddress,                  **
**                             const uint32 Timeout, const uint8 ApiId)       **
**                                                                            **
** Description     : This function will check if spinlock is available in an  **
**                   non atomic fashion and if spinlock is free then it is    **
**                   acquired in an atomic fashion acquired else it will      **
**                   try again until the timer tick provided by user is not   **
**                   less than difference between current and base stm ticks  **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters(in)  : LockAddress - It is used to lock the shared variables.   **
**                   Timeout - It is total time provided in micro second by   **
**                              user using which spinlock should be acquired. **
**                              Timeout value should be in range of 1 us to   **
**                              1048575 us (timeout when passed as 1 indicate **
**                              as 1 us to this API).                         **
**                   ApiId - Service ID of the API reporting an error         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None.                                                   **
*******************************************************************************/
static void Mcal_lGetSpinlock(volatile uint32 *const LockAddress,
                              const uint32 Timeout, const uint8 ApiId)
{
  uint32 LockAddVal;
  uint32 DelayTickResolution;
  uint32 LockAddRet;
  uint32 DelayTicks, BaseSTMTick, CurrSTMTick;
  uint32 LockVal = SPINLOCKBUSY;

  /* [cover parentID={887AEE46-FC58-4ba8-BCB2-4E331C00736E}][/cover] */
  if(Mcal_StmTimerResolution == 0U)
  {
    DelayTickResolution = Mcal_lDelayResetTickCalibration
                                            (MCALLIB_SID_GETSPINLOCK);
  }
  else
  {
    DelayTickResolution = Mcal_StmTimerResolution;
  }

  /* [cover parentID={397C69E3-87F0-4802-AC83-A23CFFC54804}]
   * Check is DelayTickResolution resolution is zero even after calibaration
   * [/cover]
   */
  if(DelayTickResolution != 0U)
  {
    /* [cover parentID={250EA709-EF99-4943-BEC6-BE8A3C26EE0B}]
       Calculate delay ticks using delay tick resolution
       [/cover] */
    DelayTicks = ((Timeout / DelayTickResolution) * MCAL_TIMEOUT);
    CurrSTMTick         = MCAL_GET_STM_TICK();
    BaseSTMTick         = CurrSTMTick;
    /* [cover parentID={B277155C-3137-4a57-8443-B908AB561FBD}]
     * If spinlock is not acquired and if difference between current and base
     * STM ticks is less than delay ticks
     * [/cover] */
    do
    {
      LockAddVal = *LockAddress;
      /* Loop untill the lock address is free  for a specified timeout in a
       * non-atomic fashion
       */
      /* [cover parentID={68D38DF0-C61C-450e-8AFD-005EA69D1E84}]
       * Loop if spinlock is busy and if difference between current and base STM
       * ticks is less than delay ticks
       * [/cover]
       */
      /* [cover parentID={80B6F3DB-C04E-476e-8E55-39456B699A76}]
       * Loop untill the lock address is free  for a specified timeout in a
       * non-atomic fashion
       * [/cover]
       */
      while(((uint32)(CurrSTMTick - BaseSTMTick) < DelayTicks) &&
            (LockAddVal != (uint32)SPINLOCKFREE))
      {
        /* Read the current STM tick from STM.TIM0 register */
        CurrSTMTick       = MCAL_GET_STM_TICK();
        LockAddVal = *LockAddress;
      }
      /* MISRA2012_RULE_11_3_JUSTIFICATION: Intrinsic function used for
       *  compare swap which require pointer conversion, no side effect seen
       *  as pointer passed is always 32-bit aligned
       */
      /* MISRA2012_RULE_11_5_JUSTIFICATION: Intrinsic function used for
       * compare swap which require pointer conversion, no side effect seen
       * as pointer passed is always 32-bit aligned
       */
      /* MISRA2012_RULE_11_8_JUSTIFICATION: Intrinsic function used for
       *  compare swap which require removing of volatile from pointer, no
       *  side effect seen as pointer passed is always 32-bit aligned
       */
      /* MISRA2012_RULE_4_6_JUSTIFICATION: Basic numerical type - int/
       *  unsigned int is used while invoking compiler intrinsic functions.
       *  These compiler intrinsic functions are implemented specific to
       *  tricore
       */
      LockAddRet = Mcal_CmpAndSwap(LockAddress, LockVal, SPINLOCKFREE);
      /* [cover parentID={40E05C7E-C511-4834-9617-6F98212953BD}]Compare
      if Lock address is free and than acquire the lock in an atomic
      fashion if difference between current and base STM ticks is less
      than delay ticks[/cover] */
    } while(
      (LockAddRet != (uint32)SPINLOCKFREE) &&
      (((CurrSTMTick - BaseSTMTick) < DelayTicks)));

    /* [cover parentID={555094D0-9B6D-48e7-9F75-ED4EB196B554}]
     *  If SAFETY Error Check is Enabled
     *  [/cover]
     */
    #if (MCALLIB_SAFETY_ENABLE == STD_ON)
    /* [cover parentID={7F7F914E-7EFA-440c-819B-EE9F050C34B0}]
     * If spinlock is not free and timeout has expired
     * [/cover]
     */
    if((((CurrSTMTick - BaseSTMTick) >= DelayTicks)) &&
        (LockAddRet != (uint32)SPINLOCKFREE))
    {
      /* [cover parentID={1F7567B8-AA4E-4a73-83EF-ACD52C7C4843}]
       * Report error MCALLIB_E_TIMEOUT_FAILED
       * [/cover]
       */
      Mcal_lReportError(ApiId, MCALLIB_E_TIMEOUT_FAILED);
    }
    #endif
  }

  /* This is used to avoid MISRA when Safety is switched OFF */
  UNUSED_PARAMETER(ApiId);
  return;
}

/*******************************************************************************
** Traceability     : [cover parentID={9D17E679-C32F-4f07-87E8-780743171A72}] **
** [/cover]                                                                   **
** Syntax          : void Mcal_lReleaseSpinlock                               **
**                               (volatile uint32 * const LockAddress)        **
**                                                                            **
** Description     : This function will release the Spinlock and value of     **
                     lock address will be 0x0U.                               **
**                                                                            **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters(in)  : LockAddress - Lock that needs to be cleared(release)     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Mcal_lReleaseSpinlock(volatile uint32 * const LockAddress)
{
  /* Ensure sequence and synchronization of read(s), write(s) of guarded
   * resources before releasing the lock
   */
  DSYNC();

  /* Clear the lock variable */
  Mcal_SetBitAtomic(LockAddress, 0x0U, 0x1, SPINLOCKFREE);

  /* MISRA2012_RULE_2_7_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the variable LockAddress is
   * accessed using only assembly instruction.
   */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer LockAddress is
   * accessed using assembly instruction. */
}

/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]Memory mapping for
   code[/cover]*/
#define MCALLIB_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "McalLib_MemMap.h"
