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
**  FILENAME     : Mcu.h                                                      **
**                                                                            **
**  VERSION      : 26.0.0                                                     **
**                                                                            **
**  DATE         : 2023-05-22                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Mcu Driver header definition file                          **
**                                                                            **
**  SPECIFICATION(S) : Specification of Mcu Driver, AUTOSAR Release 4.2.2     **
**                     and 4.4.0                                              **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#ifndef MCU_H
#define MCU_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Inclusion of common project headers */
/*[cover parentID={025CCD64-3039-4b4c-A6B9-B92839818D73}][/cover]*/
/*[cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}][/cover]*/
#include "Std_Types.h"
#include "McalLib.h"
/*Inclusion of Mcu configuration header*/
#include "Mcu_Cfg.h"


/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/* Module Identification, Vendor Identification */
/* Module ID */
/*[cover parentID={E6A6C60C-4ECA-4ba7-8D20-7C73BBC3E785}]*/
#define MCU_MODULE_ID                   ((uint16)101U)

/* MCU module instance ID*/
#define MCU_MODULE_INSTANCE             (0U)

/* MCU Vendor ID */
#define MCU_VENDOR_ID                   ((uint16)17U)
/*[/cover]*/

#if (( MCU_DEV_ERROR_DETECT == STD_ON) || (MCU_SAFETY_ENABLE == STD_ON))
/* Error Value Definitions */
/* MCU_E_PARAM_CONFIG */
/* [cover parentID={31B4DF4E-9A06-419d-9372-BB4AAF242FB7}][/cover]*/
/* API Service called with invalid config pointer */
#define MCU_E_PARAM_CONFIG              ((uint8)10U)

/* MCU_E_PARAM_CLOCK */
/*[cover parentID={89986B6D-51F1-492b-8C2B-CF17C4FDA55F}][/cover]*/
/* API Service called with invalid clock-setting */
#define MCU_E_PARAM_CLOCK               ((uint8)11U)

/* MCU_E_PARAM_MODE */
/*[cover parentID={A1907C68-9825-4d7e-853B-104FC4F71CC9}][/cover]*/
/* API Service called with invalid mode */
#define MCU_E_PARAM_MODE                ((uint8)12U)

/* MCU_E_PARAM_RAMSECTION */
/* [cover parentID={2939D1D0-602C-447a-A978-6E2319D08088}][/cover] */
/*API Service called with invalid ram-section */
#define MCU_E_PARAM_RAMSECTION          ((uint8)13U)

/* MCU_E_PLL_NOT_LOCKED */
/* [cover parentID={67F24596-7760-4405-9EA1-4CF6E6DB61E5}][/cover] */
/* If the lock status of the PLL is not detected */
#define MCU_E_PLL_NOT_LOCKED            ((uint8)14U)

/* MCU_E_UNINIT */
/*[cover parentID={6BC02723-0282-4247-A5CA-77FC6F3CE082}][/cover]*/
/* The service Mcu_Init() shall be called first before calling
  any other MCU services */
#define MCU_E_UNINIT                    ((uint8)15U)

/* MCU_E_PARAM_POINTER */
/* [cover parentID={15BF7BBB-F3C9-4bf9-B562-5789A88221F9}][/cover]*/
/* When the passed pointer is NULL_PTR */
#define MCU_E_PARAM_POINTER             ((uint8)16U)

/* MCU_E_INIT_FAILED */
/*[cover parentID = {4E9EE407-CB45-45bf-81E4-94075A409936}][/cover]*/
/* When Mcu_Init() initialization fails */
#define MCU_E_INIT_FAILED               ((uint8)17U)

/* MCU_E_UNAUTHORIZED_REQUESTER */
/*[cover parentID={29E2E838-3C7C-433e-95A5-25E5AA4DFF10}][/cover]*/
/* If an unauthorized CPU has initiated mode switch */
#define MCU_E_UNAUTHORIZED_REQUESTER    ((uint8)18U)

/* MCU_E_PARAM_CPUID */
/* [cover parentID={BEF06C09-0C92-4e72-BFD8-1A43EFD72C99}][/cover] */
/* If CPU id given is an invalid core index */
#define MCU_E_PARAM_CPUID               ((uint8)19U)

/* MCU_E_PARAM_TRAPID */
/* [cover parentID={104FBB27-ABD5-413b-A7EF-0BE1F73D8A3B}][/cover] */
/* If Trap related actions are requested with an invalid trap source id */
#define MCU_E_PARAM_TRAPID              ((uint8)20U)

/* MCU_E_PARAM_DIV_VAL */
/* [cover parentID={06785076-E606-48fd-B7DE-9DB7BC7A7764}][/cover] */
/* If divider value input is bigger than max possible divider value */
#define MCU_E_PARAM_DIV_VAL             ((uint8)21U)

/* MCU_E_CORE_NOT_MASTER  */
/* [cover parentID={EC1F64C3-AD07-4d13-8201-CB686AF5FDD1}][/cover] */
/* If Init/DeInit/Clock APIs are called from a non-master core */
#define MCU_E_CORE_MISMATCH             ((uint8)104U)

/*Service ID definitions for APIs - used during error reporting */
/* Service ID for Mcu_Init */
#define MCU_SID_INIT                    ((uint8)0U)
/* Service ID for Mcu_InitRamSection */
#define MCU_SID_INITRAMSECTION          ((uint8)1U)
/* Service ID for Mcu_InitClock */
#define MCU_SID_INITCLOCK               ((uint8)2U)
/* Service ID for Mcu_DistributePllClock */
#define MCU_SID_DISTRIBUTEPLLCLOCK      ((uint8)3U)
/* Service ID for Mcu_GetPllStatus */
#define MCU_SID_GETPLLSTATUS            ((uint8)4U)
/* Service ID for Mcu_GetResetReason */
#define MCU_SID_GETRESETREASON          ((uint8)5U)
/* Service ID for Mcu_GetResetRawValue */
#define MCU_SID_GETRESETRAWVALUE        ((uint8)6U)
/* Service ID for Mcu_PerformReset*/
#define MCU_SID_PERFORMRESET            ((uint8)7U)
/* Service ID for Mcu_SetMode */
#define MCU_SID_SETMODE                 ((uint8)8U)
/* Service ID for  Mcu_GetVersionInfo  */
#define MCU_SID_GETVERSIONINFO          ((uint8)9U)
/* Service ID for  Mcu_GetRamState  */
#define MCU_SID_GETRAMSTATE             ((uint8)10U)
/* Service ID for Mcu_ClearColdResetStatus */
#define MCU_SID_CLRCOLDRESETSTAT        ((uint8)80U)
/* Service ID for Mcu_DeInit */
#define MCU_SID_DEINIT                  ((uint8)81U)
/* Service ID for Mcu_GetCpuIdleModeInitiator */
#define MCU_SID_GETCPUIDLEMODEINIT      ((uint8)82U)
/* Service ID for Mcu_GetCpuState */
#define MCU_SID_GETCPUSTATE             ((uint8)83U)
/* Service ID for Mcu_GetWakeupCause */
#define MCU_SID_GETWAKEUPCAUSE          ((uint8)84U)
/* Service ID for Mcu_ClearWakeupCause */
#define MCU_SID_CLRWAKEUPCAUSE          ((uint8)85U)
/* Service ID for Mcu_GetTrapCause */
#define MCU_SID_GETTRAPCAUSE            ((uint8)86U)
/* Service ID for Mcu_SetTrapRequest */
#define MCU_SID_SETTRAPREQ              ((uint8)87U)
/* Service ID for Mcu_ClearTrapRequest */
#define MCU_SID_CLRTRAPREQ              ((uint8)88U)
/* Service ID for Mcu_UpdateCpuCcuconReg */
#define MCU_SID_UPDCPUCCUCONREG         ((uint8)89U)

/*DET error identification macros - for API return values */
#endif /* End of (MCU_DEV_ERROR_DETECT == STD_ON) */

#if (MCU_SAFETY_ENABLE == STD_ON)
/* Error ID for SW Reset failure Safety Error*/
/*[cover parentID={2003F68D-D5B2-4e69-A353-D653847F91CB}]*/
#define MCU_E_SW_RESET_FAILED             ((uint8)201U)
/*[/cover]*/

#define MCU_E_PHSCFG_UPDATE_ERR           ((uint8)203U)
#endif

/* Return value when DET error found */
#define MCU_ERR_FOUND                    ((uint32)1U)
/* return value when DET error is not found */
#define MCU_ERR_NOT_FOUND                ((uint32)0U)

#if (MCU_GTM_USED == STD_ON)
/* GTM global configuration macros */
/* GTM - No of CMU config clocks*/
#define MCU_GTM_NO_OF_CFGCLK              (8U)
/* GTM - No of CMU external clocks*/
#define MCU_GTM_NO_OF_EXTCLK              (3U)
/* GTM - No of GTM to ADC triggers*/
#define MCU_NO_OF_GTM_ADC_TRIGGER         (5U)
/* GTM - No of GTM to ADC triggers*/
#define MCU_NO_OF_GTM_DSADC_TRIGGER       (4U)
#endif
/*End of #if (MCU_GTM_USED == STD_ON) */
/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/* [cover parentID={D294AA9D-557F-4964-8B7F-40EFCFFF3596}] */
/* Identification for external clock configuration */
typedef uint32   Mcu_ExternalClockConfigType;
/* [/cover]  */

/* [cover parentID={44D78C5E-C961-4265-BEAB-C9209C24164B}]] */
/* Identification for clock setting */
typedef uint32   Mcu_ClockType;
/* [/cover]  */

/*[cover parentID={0658ACCB-16BB-49ef-AB1E-4C8A31C6DD19}]*/
/* Identification for a RAM section in the configuration structure */
typedef uint32   Mcu_RamSectionType;
/* [/cover]  */

/* [cover parentID={A417C0A0-F7C5-45fa-A601-9F9DF799A2E2}]  */
/* Identification for reset reason as read from a reset status register */
/* [cover parentID={BE68E3D8-057B-4c00-92D2-B64B609B5883}][/cover]  */
typedef uint32   Mcu_RawResetType;
/* [/cover]  */

/* RAM Section base address */
/* [cover parentID={6ED6A23E-6950-4fcb-9EAF-4E08FF8B81BD}][/cover]  */
typedef void*    Mcu_RamBaseAdrType;

/* RAM Section Size */
/* [cover parentID={B04F7350-1346-42df-B263-7B5C592423FB}][/cover]  */
typedef uint32   Mcu_RamSizeType;

/* RAM Section Write Size */
/* [cover parentID={45245E11-428A-49ae-B8B0-C970D9CAE512}][/cover]  */
typedef uint32   Mcu_RamWriteSizeType;

/* Data Pre-setting to be initialized */
/* [cover parentID={8127826C-90A3-4cb2-B670-3765062E724F}][/cover]  */
typedef uint64    Mcu_RamPrstDatType;
/* [/cover]  */

/* [cover parentID={FB075DB4-7FC7-4944-A192-EDD33CB9EE2F}] */
/* Identification for MCU mode in the configuration structure */
typedef uint8   Mcu_ModeType;
/* [/cover]  */

/* [cover parentID={675FA76C-F018-49fb-91D1-08531F907B2A} ] */
/* Enumeration definition of Pll status */
typedef enum
{
  MCU_PLL_LOCKED       = 0x0U,             /* PLL is locked         */
  MCU_PLL_UNLOCKED,                        /* PLL is unlocked       */
  MCU_PLL_STATUS_UNDEFINED                 /* PLL Status is unknown */
} Mcu_PllStatusType;
/* [/cover]  */

/* [cover parentID= {A417C0A0-F7C5-45fa-A601-9F9DF799A2E2}] */
/* Enumeration definition for types resets supported by MCU */
typedef enum
{
  MCU_ESR0_RESET        = 0x00U,      /* ESR0 reset     */
  MCU_ESR1_RESET        = 0x01U,      /* ESR1 reset     */
  MCU_SMU_RESET         = 0x02U,      /* SMU reset      */
  MCU_SW_RESET          = 0x03U,      /* Software reset */
  MCU_STM0_RESET        = 0x04U,      /* STM0 reset     */
  MCU_STM1_RESET        = 0x05U,      /* STM1 reset     */
  MCU_STM2_RESET        = 0x06U,      /* STM2 reset     */
  MCU_STM3_RESET        = 0x07U,      /* STM3 reset     */
  MCU_STM4_RESET        = 0x08U,      /* STM4 reset     */
  MCU_STM5_RESET        = 0x09U,      /* STM5 reset     */
  MCU_POWER_ON_RESET    = 0x0AU,      /* Power On reset */
  MCU_CB0_RESET         = 0x0BU,      /* CB0 reset      */
  MCU_CB1_RESET         = 0x0CU,      /* CB1 reset      */
  MCU_CB3_RESET         = 0x0DU,      /* CB3 reset      */
  MCU_EVRC_RESET        = 0x0EU,      /* EVRC Regulator Watchdog reset    */
  MCU_EVR33_RESET       = 0x0FU,      /* EVR33 Regulator Watchdog reset   */
  MCU_SUPPLY_WDOG_RESET = 0x10U,      /* Supply Watchdog reset            */
  MCU_STBYR_RESET       = 0x11U,      /* Standby Regulator Watchdog reset */
  MCU_LBIST_RESET       = 0x12U,      /* Reset from LBIST completion      */
  MCU_RESET_MULTIPLE    = 0xFEU,      /* Multiple Reset Reasons found     */
  MCU_RESET_UNDEFINED   = 0xFFU       /* Reset is undefined               */
} Mcu_ResetType;
/* [/cover]  */

/* Enumeration definition for CPU ID identifiers during low power modes*/
/*[cover parentID={8A6D8397-672F-4c30-B80B-D8061DF91E16}]*/
typedef enum
{
  MCU_CPU0        = 0x0U,    /* CPU0 identifier */
  #if ( MCAL_NO_OF_ACTIVE_CORES > 1U )
  MCU_CPU1        = 0x1U,    /* CPU1 identifier */
  #endif
  #if ( MCAL_NO_OF_ACTIVE_CORES > 2U )
  MCU_CPU2        = 0x2U,    /* CPU2 identifier */
  #endif
  #if ( MCAL_NO_OF_ACTIVE_CORES > 3U )
  MCU_CPU3        = 0x3U,    /* CPU3 identifier */
  #endif
  #if ( MCAL_NO_OF_ACTIVE_CORES > 4U )
  MCU_CPU4        = 0x4U,    /* CPU4 identifier */
  #endif
  #if ( MCAL_NO_OF_ACTIVE_CORES > 5U )
  MCU_CPU5        = 0x5U,    /* CPU5 identifier */
  #endif
} Mcu_CpuIdType;
/*[/cover]*/
/*
  Enumeration definition for Ram Status
*/
/* [cover parentID={D40AA42D-0CB7-4727-9463-E065515C9E69}] */
typedef enum
{
  MCU_RAMSTATE_INVALID   = 0x0U,    /* RAM contents got corrupted */
  MCU_RAMSTATE_VALID     = 0x1U     /* RAM contents are valid */
} Mcu_RamStateType;
/*[/cover]*/
/*
  Enumeration definition for CPU power mode status
  Mapped directly to PMST bits of SCU_PMCSRx register where x identifies core ID
*/
/*[cover parentID={BB4684FB-7251-46d6-87B6-D937B02462DF}]*/
typedef enum
{
  MCU_CPU_NORMAL_MODE      = 0x1U,    /* CPU Running in normal mode */
  MCU_CPU_IDLE_MODE_REQ    = 0x2U,    /* CPU Idle mode requested    */
  MCU_CPU_IDLE_MODE_ACK    = 0x3U,    /* CPU Idle mode acknowledged */
  MCU_CPU_SLEEP_MODE_REQ   = 0x4U,    /* CPU Sleep mode requested   */
  MCU_CPU_STANDBY_MODE_REQ = 0x6U,    /* CPU Standby mode requested */
  MCU_CPU_UNDEFINED_MODE   = 0xFFU    /* CPU mode is undefined      */
} Mcu_CpuModeType;
/*[/cover]*/
/* Enumeration definition for Trap request types . */
/*[cover parentID={495E20BC-1A8E-4922-8B20-BFBE0BF2D74A}]*/
typedef enum
{
  MCU_TRAP_ESR0    = 0x0U,    /* ESR0 trap request    */
  MCU_TRAP_ESR1    = 0x1U,    /* ESR1 trap request    */
  MCU_TRAP_TRAP2   = 0x2U,    /* TRAP2 trap request   */
  MCU_TRAP_SMU     = 0x3U,    /* SMU trap request     */
  MCU_TRAP_INVALID = 0x4U     /* Invalid trap request */
} Mcu_TrapRequestType;
/*[/cover]*/
/*
  Structure definition for MCU driver System PLL Configuration
  Mcu_SystemPllConfigType is used to store the system PLL configuration.
*/
/* [cover parentID={B64CB41B-EDC8-4b1c-BCAC-606424132723}] */
typedef struct
{
  unsigned_int Insel               : 2; /* Input source for both PLLs  */
  unsigned_int SysPllPDiv          : 3; /* P-Div value for system PLL  */
  unsigned_int SysPllNDiv          : 7; /* N-Div value for system PLL  */
  unsigned_int SysPllK2Div         : 3; /* K2-Div value for system PLL */
  unsigned_int FmPllEn             : 1; /* FM system PLL selection     */
  /* Modulation amplitude for FM system PLL */
  unsigned_int ModulationAmplitude : 16;
} Mcu_SystemPllConfigType;
/* [/cover]  */

/* Structure definition for MCU driver Peripheral PLL Configuration
   Mcu_PeripheralPllConfigType is used to store the peripheral PLL
   configuration.
*/
/* [cover parentID={51ADF0C8-6688-4a1e-870B-693AF22FC339}] */
typedef struct
{
  unsigned_int PerPllNDiv          : 7; /* N-Div value for peripheral PLL  */
  unsigned_int PerPllPDiv          : 3; /* P-Div value for peripheral PLL  */
  unsigned_int PerPllK2Div         : 3; /* K2-Div value for peripheral PLL */
  unsigned_int PerPllK3Div         : 3; /* K3-Div value for peripheral PLL */
  unsigned_int K3DivByPass         : 1; /* K3-Div bypass selection         */
  unsigned_int Reserved            : 15; /* Reserved                        */
} Mcu_PeripheralPllConfigType;
/* [/cover]  */

/* Structure definition for MCU driver clock distribution configuration
   Mcu_PllDistributionConfigType is used to store the PLL distribution
   configuration.
*/
/* [cover parentID={961B4DA2-598A-41cb-AC57-037D95EFC75B}] */
typedef struct
{
  uint32 Ccucon0;    /* Variable to configure Ccucon0 register */
  uint32 Ccucon1;    /* Variable to configure Ccucon1 register */
  uint32 Ccucon2;    /* Variable to configure Ccucon2 register */
  #if (MCU_SAFETY_ENABLE == STD_ON)
  uint32 Ccucon3;    /* Variable to configure Ccucon1 register */
  uint32 Ccucon4;    /* Variable to configure Ccucon2 register */
  #endif
  uint32 Ccucon5;    /* Variable to configure Ccucon5 register */
  /* Variable to configure Ccucon[i] register [i = 6...12 : for Cpu0...Cpu5]*/
  uint32 CcuconCpu[MCAL_NO_OF_ACTIVE_CORES];
} Mcu_PllDistributionConfigType;
/* [/cover]  */

/* Structure definition for MCU driver Clock Configuration
   Mcu_ClockConfigType is used to store the clock configuration data
   of the MCU Driver
*/
/* [cover parentID={BE9A1D16-CB43-4f8d-B4DB-F98283E9AD37}] */
typedef struct
{
  /* Variable to store System PLL Configuration */
  Mcu_SystemPllConfigType              SystemPllCfg;
  /* Variable to store Peripheral PLL Configuration */
  Mcu_PeripheralPllConfigType          PeripheralPllCfg;
  /* configured delay value for system PLL K2 divider increment */
  uint32                               SysPllK2DivStepUpChangeDelay;
  /* configured delay value for system PLL K2 divider decrement */
  uint32                               SysPllK2DivStepDownChangeDelay;
  /* configured delay value for peripheral PLL K2 divider increment */
  uint32                               PeripheralPllK2StepUpChangeDelay;
  /* configured delay value for peripheral PLL K2 divider decrement */
  uint32                               PeripheralPllK2StepDownChangeDelay;
  /* configured delay value for peripheral PLL K3 divider increment */
  uint32                               PeripheralPllK3StepUpChangeDelay;
  /* configured delay value for peripheral PLL K3 divider decrement */
  uint32                               PeripheralPllK3StepDownChangeDelay;
  /* Pointer to PLL Distribution configuration */
  const Mcu_PllDistributionConfigType *PllDistributionCfgPtr;
  /* Variable to store External Clock Configuration */
  Mcu_ExternalClockConfigType          ExternalClockCfg;
  /*KDIV values to output fBACKUP from both PLLs*/
  uint16                               BackupFreqKDiv;
  /* Variable to store converter control block configuration*/
  uint8                                ConvCtrlBlockConf;
} Mcu_ClockConfigType;
/* [/cover]  */

/* Structure definition for MCU driver Ram section initialization
   Mcu_RamConfigType is used to store the Ram section configuration.
*/
/* [cover parentID={9313E654-7696-4d46-8E19-41900A43E69C}] */
typedef struct
{
  Mcu_RamBaseAdrType    RamBaseAdrPtr;  /* Pointer to Ram section base address             */
  Mcu_RamSizeType       RamSize;        /* size of ram section                             */
  Mcu_RamPrstDatType    RamPrstData;    /* initialization data value                       */
  #if (MCAL_AR_VERSION == MCAL_AR_440)
  uint64                RamData;        /* initialization data value to be written at once */
  Mcu_RamWriteSizeType  RamWriteSize;   /* Number of bytes to be written at once in RAM    */
  #endif
} Mcu_RamConfigType;
/* [/cover]  */

/* Structure definition for MCU mode and low power mode EvrcCtrl Configuration
   Mcu_ModeEvrcCtrlType is used to store the MCU mode and EvrcCtrl
   configuration.
*/
/* [cover parentID={DB66DD3E-12C7-4d4a-AA8D-0A1CC504AC63}] */
typedef struct
{
  unsigned_int McuMode          : 3; /* McuMode configuration                 */
  unsigned_int EvrcLowPowerMode : 1; /* Low power mode configuration for EVRC */
  unsigned_int Reserved         : 28; /* Reserved                              */
} Mcu_ModeEvrcCtrlType;
/* [/cover]  */

#if (MCU_GPT1_USED == STD_ON) || (MCU_GPT2_USED == STD_ON)
/* [cover parentID={50E23BE3-28D3-4841-B450-3DFED253A14A}] */
typedef struct
{
  unsigned_int Gpt1PrescalarDiv : 2;  /*Gpt block 1 prescalar divider value */
  unsigned_int Gpt2PrescalarDiv : 2;  /*Gpt block 2 prescalar divider value */
  unsigned_int Reserved         : 28; /* Reserved                           */
} Mcu_Gpt12ConfigType;
/* [/cover]  */
#endif
/* Structure definition for MCU driver Low Power mode (Standby) Configuration
   Mcu_LowPowerModeType is used to store the Standby configuration.
*/
/* [cover parentID={96CD296A-EA9E-40aa-84E7-5E7651F5C69F}] */
typedef struct
{
  /* Variable to store the configured modes and EVRC configuration settings */
  Mcu_ModeEvrcCtrlType MaxModeEvrcCtrl;
  /* Variable to store the configuration parameters of PMSWCR0 */
  uint32               Pmswcr0;
  /* Variable to store the configuration parameters of PMSWCR3 */
  uint32               Pmswcr3;
  /* Variable to store the configuration parameters of PMSWCR4 */
  uint32               Pmswcr4;
  /* Variable to store the configuration parameters of PMSWCR5 */
  uint32               Pmswcr5;
  /* Variable to store the configuration parameters of EVRUVMON */
  uint32               Evruvmon;
  /* Variable to store the configuration parameters of EVRMONCTRL */
  uint32               EvrmonCtrl;
  #if (MCU_NO_OF_STDBY_RAM_BLK != 0U)
  uint32              *StdbyRamAdr[MCU_NO_OF_STDBY_RAM_BLK];
  #endif
} Mcu_LowPowerModeType;
/* [/cover]  */

/* Structure definition for MCU driver GTM External Clock Configuration
   Mcu_GtmExtClkType is used to store the GTM External Clock configuration.
*/
/* [cover parentID={8CD82F0C-20CD-4a77-BAA0-E6C98BD9A370}] */
#if (MCU_GTM_USED == STD_ON)
typedef struct
{
  /* Variable to store GTM Cmu external clock numerator configuration */
  uint32 GtmCmuExtClockNum;
  /* Variable to store GTM Cmu external clock denominator configuration */
  uint32 GtmCmuExtClockDen;
} Mcu_GtmExtClkType;
/* [/cover]  */

/* Structure definition for MCU driver GTM Clock Configuration
   Mcu_GtmClockSettingType is used to store the GTM Clock configuration.
*/
/* [cover parentID={3E2BC6D4-47C8-47f3-BA76-7DF39B799053}] */
typedef struct
{
  /* Variable to store GTM Cmu clock enable configuration*/
  uint32            GtmCmuClockEnable;
  /* Variable to store GTM Cmu global numerator configuration */
  uint32            GtmCmuGlobalNumerator;
  /* Variable to store GTM Cmu global denominator configuration */
  uint32            GtmCmuGlobalDenominator;
  /* Variable to store GTM Cmu global clock configuration [0...7] */
  uint32            GtmCmuConfClkCtrl[MCU_GTM_NO_OF_CFGCLK];
  /* Variable to store GTM Cmu global fixed clock configuration */
  uint32            GtmCmuFixedClkCtrl;
  /* Variable to store GTM cluster input clock divider configuration */
  uint32            GtmCmuClsInDiv;
  /* Variable to store GTM External Clock configuration [0...2]*/
  Mcu_GtmExtClkType GtmEclkCtrl[MCU_GTM_NO_OF_EXTCLK];
} Mcu_GtmClockSettingType;
/* [/cover]  */

/* Structure definition for MCU driver GTM Tom Configuration
   Mcu_GtmClusterConfigType is used to store the GTM Tom configuration.
*/
/* [cover parentID={A35D4C95-FE32-4564-8149-0457D3DE9680}] */
typedef struct
{
  /* Variable to store GTM cluster configuration */
  uint32 GtmCcmCfg;
  /* Variable to store GTM Cluster configurable clock configuration */
  uint32 GtmCcmConfClockCfg;
  /* Variable to store GTM cluster fixed clock configuration */
  uint32 GtmCcmFixedClockCfg;
} Mcu_GtmClusterConfigType;
/* [/cover]  */

/* Structure definition for MCU driver GTM Tom Configuration
   Mcu_GtmTomConfigType is used to store the GTM Tom configuration.
*/
/* [cover parentID={1A6D4355-DB62-4945-8C15-C3CECFE1A4B9}] */
typedef struct
{
  /*
    Variable to store GTM Tom Group Configuration
    Bits 0-15 : will store the internal trigger configuration of corresponding
                TGC (TOM[i]_TGC[y]_INT_TRIG)
    Bits 16-31: will store the RSTCN0 configuration of corresponding TGC
                (TOM[i]_TGC[y]_GLB_CTRL)
  */
  uint32 TomTgcIntTrigRstCn0;
  /*
    Variable for store the time base configuration of corresponding TGC
    TOM[i]_TGC[y]_ACT_TB configuration
  */
  uint32 TomTgcActTb;
} Mcu_GtmTomConfigType;
/* [/cover]  */

/* Structure definition for MCU driver GTM Atom Configuration
   Mcu_GtmAtomConfigType is used to store the GTM Atom configuration.
*/
/* [cover parentID={A6D55EA3-FB05-4392-8766-D3341A62C183}] */
typedef struct
{
  /*
    Variable to store GTM Atom Group Configuration
    Bits 0-15 : will store the internal trigger configuration of corresponding
                AGC (ATOM[i]_AGC[y]_INT_TRIG)
    Bits 16-31: will store the RSTCN0 configuration of corresponding AGC
                (ATOM[i]_AGC[y]_GLB_CTRL)
  */
  uint32 AtomAgcIntTrigRstCn0;
  /*
    Variable for store the time base configuration of corresponding AGC
    ATOM[i]_AGC[y]_ACT_TB configuration
  */
  uint32 AtomAgcActTb;
} Mcu_GtmAtomConfigType;
/* [/cover]  */

/* Structure definition for MCU driver GTM Tom Configuration
   Mcu_GtmTomConfigType is used to store the GTM Tom configuration.
*/
/* [cover parentID={3456A467-A10B-4313-BD32-B841BE5556F1}] */
typedef struct
{
  uint32 GtmAdcTrigOut0; /* SEL0 - SEL7 values  */
  uint32 GtmAdcTrigOut1; /* SEL8 - SEL11 values */
} Mcu_GtmAdcTrigType;
/* [/cover]  */

/* [cover parentID={48B6219B-0A52-44a3-8B32-491E91461588}] */
typedef struct
{
  uint32 GtmDsadcTrigOut0; /* SEL0 - SEL7 values  */
  uint32 GtmDsadcTrigOut1; /* SEL8 - SEL13 values */
} Mcu_GtmDsadcTrigType;
/* [/cover]  */

/* Structure definition for MCU driver Ram section initialization Configuration
   Mcu_GtmConfigType is used to store the Ram section configuration.
*/
/* [cover parentID={615FCEA6-1325-4466-841C-BAE882721A0C}] */

typedef struct
{
  /* Pointer to GTM Clock Configurations */
  const Mcu_GtmClockSettingType  *GtmClockCfgPtr;
  /* Pointer to GTM Cluster Configurations */
  const Mcu_GtmClusterConfigType *GtmClusterCfgPtr;
  /* Array to store GTM Tom global Configurations [2 groups per TOM unit]*/
  Mcu_GtmTomConfigType            GtmTomCfg[MCU_GTM_NO_OF_TOM_AVAILABLE * 2U];
  /* Array to store GTM Atom global Configurations*/
  Mcu_GtmAtomConfigType           GtmAtomCfg[MCU_GTM_NO_OF_ATOM_AVAILABLE];
  /* Array to store GTM to ADC trigger configurations*/
  Mcu_GtmAdcTrigType              GtmAdcTrigCfg[MCU_NO_OF_GTM_ADC_TRIGGER];
  /* Array to store GTM to DSADC trigger configurations*/
  Mcu_GtmDsadcTrigType            GtmDsadcTrigCfg[MCU_NO_OF_GTM_DSADC_TRIGGER];
  /* Array to store TOUTSEL configurations*/
  uint32                          GtmToutSelCfg[MCU_GTM_NO_OF_TOUTSEL_AVAILABLE];
  /* Array to store TOUTSEL used mask*/
  uint32                          GtmToutSelCfgMsk[MCU_GTM_NO_OF_TOUTSEL_AVAILABLE];
  /* Array to store TIMINSEL configurations*/
  uint32                          GtmTimInSelCfg[MCU_GTM_NO_OF_TIM_AVAILABLE];
  /* Variable to store GTM TBU Configuration */
  uint32                          GtmTbuCfg;
  /* Variable to store the usage of TOM module */
  uint16                          GtmTomModuleUsage;
  /* Variable to store the usage of ATOM module */
  uint16                          GtmAtomModuleUsage;
  /* Variable to store GTM Sleep mode configuration */
  boolean                         IsGtmSleepModeEnabled;
} Mcu_GtmConfigType;
#endif
/* End of #if (MCU_GTM_USED == STD_ON) */
/* [/cover]  */

/* Structure definition for MCU driver Configuration
   Mcu_ConfigType is used to store the configuration data of the MCU Driver
*/

/* [cover parentID={FE26C17E-A083-43a2-9316-9E6740CCB1FD}] */
typedef struct
{
  /* Pointer to clock setting configuration */
  const Mcu_ClockConfigType  *McuClockSettingPtr;
  /* Pointer to RAM Section configuration */
  const Mcu_RamConfigType    *McuRamCfgPtr;
  /* Pointer to GTM global configuration */
  #if (MCU_GTM_USED == STD_ON)
  const Mcu_GtmConfigType    *McuGtmConfigPtr;
  #endif
  /* Pointer to GPT12 Prescalar configuartion */
  #if ((MCU_GPT1_USED == STD_ON) || (MCU_GPT2_USED == STD_ON))
  const Mcu_Gpt12ConfigType  *McuGpt12PreScalarConfigPtr;
  #endif
  /* Pointer to Low power mode configuration */
  const Mcu_LowPowerModeType *McuLowPowerModeCfgPtr;
  /* Variable to store reset request configuration */
  uint32                      McuResetCfg;
  /* Variable to store application reset disable configuration */
  uint32                      McuArstDisCfg;
  /* Variable to store trap setting configuration */
  uint32                      McuTrapSettingConf0;
  #if (MCAL_NO_OF_ACTIVE_CORES > 4U)
  uint32                      McuTrapSettingConf1;
  #endif
  /* Variable to store global Eru filter configuration for channels */
  uint32                      McuEruEiFiltCfg;
  /* Variable to store total number of configured clock settings */
  Mcu_ClockType               McuNoOfClockCfg;
  /* Variable to store total number of configured RAM sectors */
  Mcu_RamSectionType          McuNoOfRamCfg;
  #if ((MCU_GPT1_USED == STD_ON) || (MCU_GPT2_USED == STD_ON))
  /* Variable to store GPT12 Sleep mode configuration */
  boolean                     IsGpt12SleepModeEnabled;
  #endif
  #if (MCU_CCU60_USED == STD_ON)
  /* Variable to store CCU60 Sleep mode configuration */
  boolean                     IsCcu60SleepModeEnabled;
  #endif
  #if (MCU_CCU61_USED == STD_ON)
  /* Variable to store CCU61 Sleep mode configuration */
  boolean                     IsCcu61SleepModeEnabled;
  #endif
} Mcu_ConfigType;
/* [/cover]  */

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
#define MCU_START_SEC_CODE_ASIL_B_GLOBAL
#include "Mcu_MemMap.h"

/*******************************************************************************
** Traceability    :                                                          **
**                                                                            **
** Syntax          : void Mcu_Init(const Mcu_ConfigType* const ConfigPtr)     **
**                                                                            **
** Description     : This API initializes the MCU driver, and other APIs can  **
**                   be used only after driver initialization is completed.   **
**                   It also performs the configuration for power management, **
**                   reset settings, clock settings, trap settings and        **
**                   GTM global settings                                      **
**                                                                            **
** Service ID      : 0x00                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : ConfigPtr - Pointer to configuration set                 **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
extern void Mcu_Init(const Mcu_ConfigType * const ConfigPtr);

/*******************************************************************************
** Traceability    :                                                          **
**                                                                            **
** Syntax          : Std_ReturnType Mcu_InitRamSection                        **
**                   (                                                        **
**                     const Mcu_RamSectionType  RamSection                   **
**                   )                                                        **
**                                                                            **
** Description     : This function initializes the given RAM section with     **
**                   configured data as per configuration data set.           **
**                                                                            **
** Service ID      : 0x01                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for other RAM sections                         **
**                                                                            **
** Parameters (in) : RamSection - Selects RAM memory section number out of    **
**                   configuration set.                                       **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: RAM successfully initialized                       **
**                   E_NOT_OK: RAM initialization failed                      **
**                   e.g. due to parameter error                              **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Mcu_InitRamSection(const Mcu_RamSectionType RamSection );

#if (MCU_INIT_CLOCK_API == STD_ON)
/*******************************************************************************
** Traceability    :                                                          **
**                                                                            **
** Syntax          : Std_ReturnType Mcu_InitClock                             **
**                   (                                                        **
**                     const Mcu_ClockType  ClockSetting                      **
**                   )                                                        **
**                                                                            **
** Description     : This API initializes the PLLs and other MCU specific     **
**                   clock options. The PLL lock procedure is started (if PLL **
**                   shall be initialized) for system and peripheral PLLs,    **
**                   but the function does not wait until the peripheral PLL  **
**                   is locked                                                **
**                   Note: Mcu_InitClock only initializes the PLL parameters. **
**                         PLL clock will be activated to the MCU distribution**
**                         only after the system PLL is also locked and then  **
**                         Mcu_DistributePllClock shall be called. i.e The    **
**                         sequence to activate PLL clock to the MCU clock    **
**                         distribution is:                                   **
**                         1)Call Mcu_InitClock                               **
**                         2)Call Mcu_GetPllStatus                            **
**                         3)Call Mcu_DistributePllClock                      **
**                                                                            **
** Service ID      : 0x02                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : ClockSetting: Clock setting index                        **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: Clock initialization successful                    **
**                   E_NOT_OK: Clock initialization failed                    **
**                   e.g. due to parameter error                              **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Mcu_InitClock(const Mcu_ClockType ClockSetting);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Mcu_InitClock(ClockSetting)      ERROR_Mcu_InitClock_API_IS_NOT_SELECTED
#endif/* End of (MCU_INIT_CLOCK_API == STD_ON)*/

#if (MCU_DISTRIBUTE_PLL_CLOCK_API == STD_ON)
/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax          : Std_ReturnType Mcu_DistributePllClock( void )            **
**                                                                            **
** Description     : This API selects the PLL clock as source for MCU clock   **
**                   tree distribution. Afterwards, it ramps up/down the clock**
**                   to desired clock frequency as per configuration data set.**
**                                                                            **
** Service ID      : 0x03                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: Clock distribution successful                      **
**                   E_NOT_OK: Clock distribution failed                      **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Mcu_DistributePllClock( void );
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Mcu_DistributePllClock()\
                    ERROR_Mcu_DistributePllClock_API_IS_NOT_SELECTED
#endif/* End of (MCU_INIT_CLOCK_API == STD_ON)*/

/*******************************************************************************
** Traceability    :                                                          **
**                                                                            **
** Syntax          : Mcu_PllStatusType Mcu_GetPllStatus( void )               **
**                                                                            **
** Description     : This function provides the lock status of the system     **
**                   and peripheral PLL                                       **
**                                                                            **
** Service ID      : 0x04                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Mcu_PllStatusType                                        **
**                   Returns whether PLL is Locked,Unlocked, Undefined status **
**                                                                            **
*******************************************************************************/
extern Mcu_PllStatusType Mcu_GetPllStatus( void );

/*******************************************************************************
** Traceability    :                                                          **
**                                                                            **
** Syntax          : Mcu_ResetType Mcu_GetResetReason( void )                 **
**                                                                            **
** Description     : The API reads the reset type from the hardware and       **
**                   returns the type of reset occurred as per MCU supported  **
**                   resets.                                                  **
**                                                                            **
** Service ID      : 0x05                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Mcu_ResetType - Returns the reset reason                 **
**                                                                            **
*******************************************************************************/
extern Mcu_ResetType Mcu_GetResetReason( void );

/*******************************************************************************
** Traceability    :                                                          **
**                                                                            **
** Syntax          : Mcu_ResetType Mcu_GetResetRawValue( void )               **
**                                                                            **
** Description     : The API reads the returns the raw value of reset         **
**                   register.                                                **
**                                                                            **
** Service ID      : 0x06                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Mcu_RawResetType - Returns the raw value of reset        **
**                   register                                                 **
**                                                                            **
*******************************************************************************/
extern Mcu_RawResetType Mcu_GetResetRawValue( void );

#if (MCU_PERFORM_RESET_API == STD_ON)
/*******************************************************************************
** Traceability    :                                                          **
**                                                                            **
** Syntax          : void Mcu_PerformReset( void )                            **
**                                                                            **
** Description     : The API performs a micro-controller reset.               **
**                   The MCU specific reset type to be performed by this      **
**                   service shall be configured in the configuration set.    **
**                                                                            **
** Service ID      : 0x07                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
extern void Mcu_PerformReset( void );
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Mcu_PerformReset()  ERROR_Mcu_PerformReset_API_IS_NOT_SELECTED
#endif /* End of MCU_PERFORM_RESET_API */

/*******************************************************************************
** Traceability    :                                                          **
**                                                                            **
** Syntax          : void Mcu_SetMode( const Mcu_ModeType McuMode )           **
**                                                                            **
** Description     : This API sets the selected power mode for MCU. In case   **
**                   the CPU is switched off, the function is returned after  **
**                   wake-up is performed.                                    **
**                                                                            **
** Service ID      : 0x08                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : McuMode : Mcu Mode number as configured in the           **
**                   configuration set                                        **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
extern void Mcu_SetMode(const Mcu_ModeType McuMode);

#if(MCU_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Traceability    :                                                          **
**                                                                            **
** Syntax          : void  Mcu_GetVersionInfo                                 **
**                   (                                                        **
**                     Std_VersionInfoType * const versioninfo                **
**                   )                                                        **
**                                                                            **
** Description     : This service returns the version information of module.  **
**                   The version information includes:                        **
**                   - Vendor Id                                              **
**                   - Module Id                                              **
**                   - SW Major Version                                       **
**                   - SW Minor Version                                       **
**                   - SW Patch Version                                       **
**                                                                            **
** Service ID      : 0x09                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : versioninfo : (Pointer to store the version              **
**                   information of this module)                              **
**                                                                            **
** Parameters (out): VersionInfoPtr values are updated with version           **
**                   information                                              **
**                                                                            **
** Return value:   : None                                                     **
**                                                                            **
*******************************************************************************/
extern void Mcu_GetVersionInfo(Std_VersionInfoType * const versioninfo);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Mcu_GetVersionInfo(versioninfo)\
                        ERROR_Mcu_GetVersionInfo_API_IS_NOT_SELECTED
#endif  /* #if (MCU_VERSION_INFO_API == STD_ON) */

#if(MCU_GET_RAM_STATE_API == STD_ON)
/*******************************************************************************
** Traceability    :                                                          **
**                                                                            **
** Syntax          : Mcu_RamStateType  Mcu_GetRamState (void)                 **
**                                                                            **
** Description     : This service returns the RAM state of given CPU.         **
**                                                                            **
** Service ID      : 0x0A                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : MCU_RAMSTATE_INVALID: RAM contents got corrupted         **
**                   MCU_RAMSTATE_VALID  : RAM contents are valid             **
**                                                                            **
*******************************************************************************/
extern Mcu_RamStateType Mcu_GetRamState(void);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Mcu_GetRamState()\
                        ERROR_Mcu_GetRamState_API_IS_NOT_SELECTED
#endif  /* #if (MCU_GET_RAM_STATE_API == STD_ON) */

#if (MCU_CLK_SRC_FAILURE_NOTIF_API == STD_ON)
/*******************************************************************************
** Traceability    :                                                          **
**                                                                            **
** Syntax          : void Mcu_ClockFailureNotification ( void )               **
**                                                                            **
** Description     : This service reports DEM error when called in case of    **
**                   PLL lock loss                                            **
**                                                                            **
** Service ID      : 0xFF                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:   : None                                                     **
**                                                                            **
*******************************************************************************/
extern void Mcu_ClockFailureNotification(void);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Mcu_ClockFailureNotification()\
                        ERROR_Mcu_ClockFailureNotification_API_IS_NOT_SELECTED
#endif  /* #if (MCU_CLK_SRC_FAILURE_NOTIF_API == STD_ON) */

#if (MCU_CLR_COLD_RESET_STAT_API == STD_ON)
/*******************************************************************************
** Traceability    :                                                          **
**                                                                            **
** Syntax          : void  Mcu_ClearColdResetStatus ( void )                  **
**                                                                            **
** Description     : This API clears the reset reason register content.       **
**                                                                            **
** Service ID      : 0x50                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
extern void Mcu_ClearColdResetStatus( void );
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Mcu_ClearColdResetStatus()\
                    ERROR_Mcu_ClearColdResetStatus_API_IS_NOT_SELECTED
#endif /* (MCU_CLR_COLD_RESET_STAT_API == STD_ON) */

#if (MCU_DEINIT_API == STD_ON)
/*******************************************************************************
** Traceability    :                                                          **
**                                                                            **
** Syntax          : void Mcu_DeInit(void)                                    **
**                                                                            **
** Description     : This API de-initializes the MCU driver. It puts all the  **
**                   resources used by MCU and power management configurations**
                     to reset state. PLL will not be de-initialized by this   **
                     function.                                                **
**                                                                            **
** Service ID      : 0x51                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
extern void Mcu_DeInit(void);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Mcu_DeInit()  ERROR_Mcu_DeInit_API_IS_NOT_SELECTED
#endif

#if (MCU_LOW_POWER_MODE_API == STD_ON)
/*******************************************************************************
** Traceability    :                                                          **
**                                                                            **
** Syntax          : uint32 Mcu_GetCpuIdleModeInitiator                       **
**                   (                                                        **
**                     void                                                   **
**                   )                                                        **
**                                                                            **
** Description     : This API returns the CPU ID which is configured to       **
**                   initiate IDLE mode.                                      **
**                                                                            **
** Service ID      : 0x52                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : uint32 - CPU Id value.                                   **
**                                                                            **
*******************************************************************************/
extern uint32 Mcu_GetCpuIdleModeInitiator(void);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Mcu_GetCpuIdleModeInitiator()\
                        ERROR_Mcu_GetCpuIdleModeInitiator_API_IS_NOT_SELECTED
#endif

#if (MCU_LOW_POWER_MODE_API == STD_ON)
/*******************************************************************************
** Traceability    :                                                          **
**                                                                            **
** Syntax          : Mcu_CpuModeType  Mcu_GetCpuState                         **
**                   (                                                        **
**                     const Mcu_CpuIdType CpuId                              **
**                   )                                                        **
**                                                                            **
** Description     : This API returns the current CPU state of requested CPU  **
**                                                                            **
** Service ID      : 0x53                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : CpuId : The Core id for which the mode needs to be       **
**                   determined                                               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Mcu_CpuModeType  - CPU mode status of requested core     **
**                                                                            **
*******************************************************************************/
extern Mcu_CpuModeType Mcu_GetCpuState(const Mcu_CpuIdType CpuId);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Mcu_GetCpuState(CpuId)  ERROR_Mcu_GetCpuState_API_IS_NOT_SELECTED
#endif

#if (MCU_LOW_POWER_MODE_API == STD_ON)
/*******************************************************************************
** Traceability    :                                                          **
**                                                                            **
** Syntax          : uint32 Mcu_GetWakeupCause ( void )                       **
**                                                                            **
** Description     : This API returns the wakeup cause register value.        **
**                                                                            **
** Service ID      : 0x54                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : uint32  - Reason for wakeup                              **
**                                                                            **
*******************************************************************************/
extern uint32 Mcu_GetWakeupCause(void);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Mcu_GetWakeupCause()  ERROR_Mcu_GetWakeupCause_API_IS_NOT_SELECTED
#endif

#if (MCU_LOW_POWER_MODE_API == STD_ON)
/*******************************************************************************
** Traceability    :                                                          **
**                                                                            **
** Syntax          : void Mcu_ClearWakeupCause                                **
**                   (                                                        **
**                     const uint32 WakeupCause                               **
**                   )                                                        **
**                                                                            **
** Description     : This API clears the selected wakeup reasons.             **
**                                                                            **
** Service ID      : 0x55                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : WakeupCause - mask for wakeup causes to be cleared.      **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
extern void Mcu_ClearWakeupCause(const uint32 WakeupCause);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Mcu_ClearWakeupCause(WakeupCause)\
                           ERROR_Mcu_ClearWakeupCause_API_IS_NOT_SELECTED
#endif

#if (MCU_TRAP_API == STD_ON)
/*******************************************************************************
** Traceability    :                                                          **
**                                                                            **
** Syntax          : uint32 Mcu_GetTrapCause ( void )                         **
**                                                                            **
** Description     : This API returns the trap cause register value.          **
**                                                                            **
** Service ID      : 0x56                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : uint32  - Reason for Trap                                **
**                                                                            **
*******************************************************************************/
extern uint32 Mcu_GetTrapCause(void);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Mcu_GetTrapCause()  ERROR_Mcu_GetTrapCause_API_IS_NOT_SELECTED
#endif

#if (MCU_TRAP_API == STD_ON)
/*******************************************************************************
** Traceability    :                                                          **
**                                                                            **
** Syntax          : void Mcu_SetTrapRequest                                  **
**                   (                                                        **
**                     const Mcu_TrapRequestType TrapRequestId                **
**                   )                                                        **
**                                                                            **
** Description     : This API sets the selected trap request.                 **
**                                                                            **
** Service ID      : 0x57                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for other Trap Ids                             **
**                                                                            **
** Parameters (in) : TrapRequestId - Type of trap request to be set           **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
extern void Mcu_SetTrapRequest(const Mcu_TrapRequestType TrapRequestId);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Mcu_SetTrapRequest(TrapRequestId)\
                          ERROR_Mcu_SetTrapRequest_API_IS_NOT_SELECTED
#endif

#if (MCU_TRAP_API == STD_ON)
/*******************************************************************************
** Traceability    :                                                          **
**                                                                            **
** Syntax          : void Mcu_ClearTrapRequest                                **
**                   (                                                        **
**                     const Mcu_TrapRequestType TrapRequestId                **
**                   )                                                        **
**                                                                            **
** Description     : This API clears the selected trap cause.                 **
**                                                                            **
** Service ID      : 0x58                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for other Trap Ids                             **
**                                                                            **
** Parameters (in) : TrapRequestId - Type of trap reason to be cleared        **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
extern void Mcu_ClearTrapRequest(const Mcu_TrapRequestType TrapRequestId);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Mcu_ClearTrapRequest(TrapRequestId)\
                        ERROR_Mcu_ClearTrapRequest_API_IS_NOT_SELECTED
#endif

#if (MCU_CPU_CCUCON_UPDATE_API == STD_ON)
/*******************************************************************************
** Traceability    :                                                          **
**                                                                            **
** Syntax          : void Mcu_UpdateCpuCcuconReg                              **
**                   (                                                        **
**                     const Mcu_CpuIdType CpuId,                             **
**                     const uint8 DivVal,                                    **
**                     const uint8 Delay                                      **
**                   )                                                        **
** Description     : This API updates CCUCONx divider value of CPUx to the    **
**                   user provided value.                                     **
**                                                                            **
** Service ID      : 0x59                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for other cores                                **
**                                                                            **
** Parameters (in) : CpuId  - CpuId of core                                   **
**                   DivVal - New divider value for update in CCUCONx.        **
**                   Delay  - Delay in microseconds after register update.    **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
extern void Mcu_UpdateCpuCcuconReg
(
  const Mcu_CpuIdType CpuId,
  const uint8 DivVal,
  const uint8 Delay
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Mcu_UpdateCpuCcuconReg(CpuId,DivVal,Delay)\
                               ERROR_Mcu_UpdateCpuCcuconReg_API_IS_NOT_SELECTED
#endif


#if (MCU_INITCHECK_API == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID={4D72BAD4-4E08-49fb-8A9A-85D291AF2C4A}]  **
**                                                                            **
** Syntax          : Std_ReturnType Mcu_InitCheck                             **
**                   (                                                        **
**                     const Mcu_ConfigType * const ConfigPtr                 **
**                   )                                                        **
**                                                                            **
** Description     : This function checks whether Mcu_Init is successful      **
**                   or not.                                                  **
**                                                                            **
** Service ID      : 0x5A                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : ConfigPtr - Pointer to configuration set                 **
**                                                                            **
** Parameters (out):                                                          **
**                                                                            **
** Return value    : E_OK     : Mcu Initcheck successful                      **
**                   E_NOT_OK : Mcu Initcheck failed                          **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Mcu_InitCheck
(
  const Mcu_ConfigType * const ConfigPtr
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Mcu_InitCheck(ConfigPtr)  ERROR_Mcu_InitCheck_API_IS_NOT_SELECTED
#endif

#define MCU_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Mcu_MemMap.h"
/*The file is included to get extern declaration of all the configuration root
structure. The extern declaration of configuration root structure is needed by
application software*/
#include "Mcu_PBcfg.h"

#endif  /* End of  MCU_H */
