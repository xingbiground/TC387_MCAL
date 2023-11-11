/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2019)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : Sent.h                                                     **
**                                                                            **
**  VERSION      : 1.30.0_8.0.0                                               **
**                                                                            **
**  DATE         : 2019-08-23                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : SENT Driver header definition file                         **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#ifndef SENT_H
#define SENT_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/* Inclusion of Platform_Types.h and Compiler.h */
#include "Std_Types.h"

#include "Sent_Types.h"

/* Pre-compile/static configuration parameters for SENT  */
#include "Sent_Cfg.h"

/* Inclusion of Mcal Specific Global Header File */
#include "McalLib.h"
/*******************************************************************************
**                      Global Macro Definitions                              **
*****************************************1*************************************/

/* SENT Vendor ID */
#define SENT_VENDOR_ID                     (17U)
/* SENT Module ID */
#define SENT_MODULE_ID                     (255U)

/* To access the respective Sent Channel through array indexing */
#define SENT_CHANNEL                       (&(MODULE_SENT.CH[0]))
/* To access the Sent Channel's RDR register through array indexing */
#define SENT_RDR                           (&(MODULE_SENT.RDR[0]))
/* To access the Sent Channel's RDR register through array indexing */
#define SENT_TIMESTAMP                     (&(MODULE_SENT.RTS[0]))
/* To access the Sent Interrupt Nodes through array indexing */
#define SENT_SRC                           (&(SRC_SENT0))



/* Sent module Status Uninitialized */
#define SENT_UNINITIALIZED              ((uint8)0U)
/* Status to indicate that SENT module is initialized */
#define SENT_MOD_INITIALIZED                ((uint8)1U)
/*
  Development error codes
*/
#if (SENT_DEV_ERROR_DETECT == STD_ON)

/* Service is called before Init */
#define SENT_E_UNINIT                  ((uint8)0x05)
/*Synchronous transmission service called at invalid channel.*/
#define SENT_E_INVALID_CHANNEL        ((uint8)0x02)
/* Service is called with invalid parameter */
#define SENT_E_PARAM_POINTER           ((uint8)0x03)
/* Service is called when initialization is failed */
#define SENT_E_INIT_FAILED              ((uint8)0x10)
/* Service is called when already initialized */
#define SENT_E_ALREADY_INITIALIZED      ((uint8)0x14)

/* Multi-core DETs*/
/* Report DET SENT channel not configured for this Core*/
#define SENT_E_CORE_NOT_CONFIGURED     ((uint8)0x64)
/* [cover parentID={E3883A82-81DD-4402-96D5-42BA11077AFD}]
   SENT channel is not allocated to this core
[/cover] */
#define SENT_E_CORE_CHANNEL_MISMATCH   ((uint8)0x65)
/* Core Initialization called when master initialization is not done */
#define SENT_MASTER_CORE_UNINIT        ((uint8)0x66)
/* Master De-initialization called before de-initialization of the slave cores*/
#define SENT_E_SLAVE_CORE_INIT         ((uint8)0x67)
/* Report DET when channel is not configured */
# define SENT_E_CHANNEL_NOT_CONFIGURED  ((uint8)0x68)
/* Report DET when channel is not enabled */
#define SENT_E_CHANNEL_NOT_ENABLED ((uint8)0x69)

/*
  Service ID number for all SENT driver services
*/
/* Service ID for Sent_Init */
#define SENT_SID_INIT                   ((uint8)152)
/* Service ID for Sent_SetChannel */
#define SENT_SID_SETCHANNEL             ((uint8)153)
/* Service ID for Sent_ReadData */
#define SENT_SID_READDATA               ((uint8)154)
/* Service ID for Sent_ReadSerialData */
#define SENT_SID_READSERIALDATA         ((uint8)155)
/* Service ID for Sent_ReadChannelStatus */
#define SENT_SID_READCHANSTATUS         ((uint8)156)
/* Service ID for Sent_SpcGenPulse */
#define SENT_SID_SPCGENPULSE            ((uint8)157)
/* Service ID for Sent_SetWdgTimer */
#define SENT_SID_CONFIGWDG              ((uint8)158)
/* Service ID for Sent_GetVersionInfo */
#define SENT_SID_GETVERINFO             ((uint8)159)
/* Service ID for Sent_DeInit */
#define SENT_SID_DEINIT                 ((uint8)160)
/*Service ID for Sent_ReadGlitchStatus */
#define SENT_SID_READGLITCHSTATUS       ((uint8)161)
/*Service ID for Sent_ResetGlitchStatus */
#define SENT_SID_RESETGLITCHSTATUS       ((uint8)162)
/*Service ID for Sent_FDFLParameters */
#define SENT_SID_FDFLPARAMETERS         ((uint8)163)


#endif /* SENT_DEV_ERROR_DETECT */

/*
  Macros required for configuring the SENT driver
*/

/* Default Interrupt Enable bits
 * SCRI, SDI, WSI, CRCI, NVI, NNI, FDI, FRI, TDI, RBI and RSI
 */
#define SENT_CHANNEL_CFG_INTEN          (0x3FFFU)
#define SENT_TIMEOUT_VALUE              ((uint16)0xFFU)

/* SENT Channel Event status bits */
#define SENT_INT_RSI_EVENT              (0x1U)
#define SENT_INT_RDI_EVENT              (0x2U)
#define SENT_INT_RBI_EVENT              (0x4U)
#define SENT_INT_TDI_EVENT              (0x8U)
#define SENT_INT_TBI_EVENT              (0x10U)
#define SENT_INT_FRI_EVENT              (0x20U)
#define SENT_INT_FDI_EVENT              (0x40U)
#define SENT_INT_NNI_EVENT              (0x80U)
#define SENT_INT_NVI_EVENT              (0x100U)
#define SENT_INT_CRCI_EVENT             (0x200U)
#define SENT_INT_WSI_EVENT              (0x400U)
#define SENT_INT_SDI_EVENT              (0x800U)
#define SENT_INT_SCRI_EVENT             (0x1000U)
#define SENT_INT_WDI_EVENT              (0x2000U)
#define SENT_TRANS_INPROGRESS_EVENT     (0x4000U)
typedef uint8 Sent_ChannelType;
/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/* SPC Related Typedefs */
#if (SENT_SPC_USED == STD_ON)
/* Type : Sent_SpcTimeBaseType
   This type defines a pulse time base of the SPC channel transmission. */
typedef enum
{
  PULSE_NOMINAL_FREQ,  /* Pulse is based on measured frequency of last
                         Synchronization/Calibration Pulse */
  PULSE_LAST_SYNC_FREQ /* Pulse is based on nominal frequency */
} Sent_SpcTimeBaseType;

typedef enum
{
  PULSE_STOP,             /* No pulse is generated, on-going transfer is
                                            stopped immediately */
  PULSE_START_IMMED,      /* Pulse starts immediately */
  PULSE_START_SYNC,       /* Pulse starts each time first falling edge of any
                            Synchronization/ Calibration Pulse is received */
  PULSE_START_EXT_TRIGGER /* Pulse starts after each external trigger event */
} Sent_SpcTrigSrcType;


/* Type : Sent_SpcMode
   This type defines modes for the SPC channel transmission. */
typedef enum
{
  SYNC_MODE,              /* Synchonization mode */
  BIDIRECTIONAL_MODE,     /* Bidirectional mode */
  RANGE_SELECTION,        /* Range selection mode */
  ID_SELECTION            /* ID selection mode */
} Sent_SpcMode;

/* Type : Sent_SpcType
   This type defines different operations for the SPC channel transmission. */
typedef struct
{
  Sent_SpcMode          Mode;           /* Different mode selection for SPC */
  Sent_SpcTrigSrcType   TriggerSource;  /* Trigger source for SPC operation */
  Sent_SpcTimeBaseType  TimeBase;       /* Pulse time base for SPC */
  uint8                 PulseLength;    /* Length of pulse in tick times */
  uint8                 Delay;          /* SPC pulse delay time */
} Sent_SpcType;


#endif /* (SENT_SPC_USED == STD_ON) */
/*
  Structure definition for SENT configuration
*/
typedef struct
{
  /* Pointer to Core configuration */
  const Sent_CoreConfigType *SentCorePtr[MCAL_NO_OF_CORES];
  /* Module clock divider */
  uint32                    ModuleClkDiv;
  /* Module Fractional step divider */
  uint16                    ModuleFracDivStep;
  /* Number of SENT channels configured */
  uint8                     NumChannelsConfigured;
  /* The Lookup table pointer
     The pointer to the structure gives the arrangement
     of channels as per the core */
  const Sent_ChannelMapType   *Sent_ChannelLookUpTable;
  /* Physical to Logical Id mapping */
  const Sent_ChannelIdxType   *Sent_LogicalChanId;
  /* Logical to Physical Id mapping */
  const Sent_ChannelIdxType   *Sent_PhysicalChanId;
} Sent_ConfigType;

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
#define SENT_START_SEC_CODE_QM_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
    without safegaurd. It complies to Autosar guidelines. */
#include "Sent_MemMap.h"
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void Sent_Init                                          **
**                    (                                                       **
**                      const Sent_ConfigType *ConfigPtr                      **
**                    )                                                       **
**                                                                            **
** Description      : This function:                                          **
**                      - Initializes the SENT Module, Baud Rate registers    **
**                      - Also configures the respective Channels registers   **
**                                                                            **
** Service ID       : 0x98                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non reentrant                                           **
**                                                                            **
** Parameters (in)  : ConfigPtr - Pointer to SENT configuration               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Sent_Init
(
  const Sent_ConfigType * const ConfigPtr
);

/*******************************************************************************
** Traceability      :                                                        **
**                                                                            **
** Syntax            : void Sent_SetChannel                                   **
**                     (                                                      **
**                      Sent_ChannelIdxType ChannelId,                        **
**                      Sent_ChanOpType Operation                             **
**                     )                                                      **
**                                                                            **
** Description       : This function:                                         **
**                       - Enables/Disables the SENT Channel                  **
**                                                                            **
** Service ID        : 0x99                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Non-Reentrant                                          **
**                                                                            **
** Parameters(in)    : Channel_Id - SENT Channel number                       **
**                     Operation - SENT_ENABLE/SENT_DISABLE                   **
**                                                                            **
** Parameters (out)  : none                                                    **
**                                                                            **
** Return value      : none                                                   **
**                                                                            **
*******************************************************************************/
extern void Sent_SetChannel
(
  const Sent_ChannelIdxType ChanId,
  Sent_ChanOpType Operation
);

/*******************************************************************************
** Traceability      :                                                        **
**                                                                            **
** Syntax           : uint32 Sent_ReadData                                    **
**                    (                                                       **
**                      const Sent_ChannelIdxType ChannelId                   **
**                    )                                                       **
**                                                                            **
** Description      : This function:                                          **
**                      - reads the nibbles recieved in the Data register     **
**                                                                            **
** Service ID       : 0x9A                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters(in)   : ChannelId - SENT Channel whose data has to be read      **
**                                                                            **
** Parameters (out) : Data read from the SENT Channel                         **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
*******************************************************************************/
extern uint32 Sent_ReadData
(
  const Sent_ChannelIdxType ChannelId
);

/*******************************************************************************
** Traceability      :                                                        **
**                                                                            **
** Syntax           : void Sent_ReadSerialData                                **
**                    (                                                       **
**                      Sent_ChannelIdxType ChannelId,                        **
**                      Sent_RxSerialDataType *DataPtr                        **
**                    )                                                       **
**                                                                            **
** Description      : This function:                                          **
**                      - reads the Serial data recieved and collected over   **
**                        several SENT frames                                 **
**                                                                            **
** Service ID       : 0x9B                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters(in)   : ChannelId - SENT Channel's serial data has to be read   **
**                                                                            **
** Parameters (out) : DataPtr - Data pointer pointing to the serial data read **
**                              from the SENT Channel                         **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
*******************************************************************************/
extern void Sent_ReadSerialData
(
  const Sent_ChannelIdxType ChannelId,
  Sent_RxSerialDataType * const DataPtr
);

/*******************************************************************************
** Traceability      :                                                        **
**                                                                            **
** Syntax           : void Sent_ReadChannelStatus                             **
**                    (                                                       **
**                      Sent_ChannelIdxType ChannelId,                        **
**                      Sent_ChanStatusType *StatPtr                          **
**                    )                                                       **
**                                                                            **
** Description      : This function:                                          **
**                      - reads the Channel status                            **
**                      - Also collects the Timestamp                         **
**                                                                            **
** Service ID       : 0x9C                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters(in)   : ChannelId - SENT Channel's status has to be read        **
**                                                                            **
** Parameters (out) : StatPtr - Pointer pointing to the status of the SENT    **
**                              Channel                                       **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
*******************************************************************************/
extern void Sent_ReadChannelStatus
(
  const Sent_ChannelIdxType ChannelId,
  Sent_ChanStatusType * const StatPtr
);

#if (SENT_SPC_USED == STD_ON)
/*******************************************************************************
** Traceability      :                                                        **
**                                                                            **
** Syntax           : void Sent_SpcGenPulse                                   **
**                    (                                                       **
**                      Sent_ChannelIdxType ChannelId,                        **
**                      const Sent_SpcType *SpcCfgPtr                         **
**                    )                                                       **
**                                                                            **
** Description      : This function:                                          **
**                      - generates a Master pulse for SPC Sync transmission  **
**                      - can be used for Bi-Directional mode also            **
**                                                                            **
** Service ID       : 0x9D                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters(in)   : ChannelId - SENT Channel's status has to be read        **
**                    Sent_SpcType - Pointer to configure the SPC mode and    **
**                                   generate a master pulse                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
*******************************************************************************/
extern void Sent_SpcGenPulse
(
  const Sent_ChannelIdxType ChanId,
  const Sent_SpcType * const SpcCfgPtr
);
#endif

/*******************************************************************************
** Traceability      :                                                        **
**                                                                            **
** Syntax           : void Sent_SetWdgTimer                                   **
**                    (                                                       **
**                      Sent_ChannelIdxType ChannelId,                        **
**                      uint16 WdgTimerReloadVal                              **
**                    )                                                       **
**                                                                            **
** Description      : This function:                                          **
**                      - configures the Channel's watchdog timer             **
**                                                                            **
** Service ID       : 0x9E                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters(in)   : ChannelId - SENT Channel's status has to be read        **
**                    WdgTimerReloadVal - Watchdog Reload Timer value         **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
*******************************************************************************/
extern void Sent_SetWdgTimer
(
  const Sent_ChannelIdxType ChanId,
  uint16 WdgTimerReloadVal
);
#if (SENT_VERSION_INFO_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Syntax           : void Sent_GetVersionInfo                                **
**                    (                                                       **
**                      Std_VersionInfoType* const versioninfo                **
**                    )                                                       **
**                                                                            **
** Description      : - This function returns the version information of this **
**                      module.The version information include : Module ID,   **
**                      Vendor ID,Vendor specific version numbers             **
**                                                                            **
** Service ID       : 0x9F                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (out) : versioninfo - Pointer to store the                      **
**                    version information of this module.                     **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
extern void Sent_GetVersionInfo
(
  Std_VersionInfoType* const versioninfo
);
#else
/* MISRA2012_RULE_04_9_JUSTIFICATION: Function like macro used to generate
  compile time error in case of incorrect configuration*/
#define Sent_GetVersionInfo(versioninfo)                              \
                               (ERROR_Sent_GetVersionInfo_NOT_SELECTED)

#endif /* #if( (SENT_VERSION_INFO_API == STD_ON) */

#if (SENT_DEINIT_API == STD_ON)
/*******************************************************************************
** Traceability      :                                                        **
**                                                                            **
** Syntax           : void Sent_DeInit                                        **
**                    (                                                       **
**                      void                                                  **
**                    )                                                       **
**                                                                            **
** Description      : This function:                                          **
**                      - De-Initializes the SENT Module and it's registers,  **
**                      - also with respective Channels registers             **
**                                                                            **
** Service ID       : 0xA0                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
extern void Sent_DeInit
(
  void
);
#endif

/*******************************************************************************
**                      Global Function Declarations:                         **
**             Functions to be Called From Interrupt/Scheduler Context        **
*******************************************************************************/
/*******************************************************************************
** Traceability      :                                                        **
**                                                                            **
** Syntax           : void Sent_Isr (uint8 IntrNode)                          **
**                                                                            **
** Description      : This function:                                          **
**                      - is the interrupt handler and collects the status    **
**                        of the relevant channels and inform the user        **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters(in)   : IntrNode - interrupt node Number number                 **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
*******************************************************************************/
extern void Sent_Isr(uint8 IntrNode);

/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : Sent_GlitchStatusType Sent_ReadGlitchFilterStatus       **
**                    (                                                       **
**                      const Sent_ChannelIdxType ChannelId                   **
**                    )                                                       **
**                                                                            **
** Description      : This function:                                          **
**                      - reads the status of the glitch filter               **
**                                                                            **
** Service ID       : 0xA1                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters(in)   : ChannelId - SENT Channel's status has to be read        **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : Polarity of the falling and raising edge signal         **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Sent_ReadGlitchFilterStatus
(
        const Sent_ChannelIdxType ChannelId
);

/*******************************************************************************
** Traceability      :                                                        **
**                                                                            **
** Syntax            : void Sent_ResetGlitchFilterStatus                      **
**                     (                                                      **
**                       const Sent_ChannelIdxType ChannelId                  **
**                     )                                                      **
**                                                                            **
** Description       : This function:                                         **
**                       - resets the status flag after glitch filtering and  **
**                         signal inversion                                   **
**                                                                            **
** Service ID        : 0xA2                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Non-Reentrant                                          **
**                                                                            **
** Parameters(in)    : ChannelId - SENT Channel's status has to be read       **
**                                                                            **
** Parameters (out)  : none                                                   **
**                                                                            **
** Return value      : none                                                   **
**                                                                            **
*******************************************************************************/
extern void Sent_ResetGlitchFilterStatus
(
        const Sent_ChannelIdxType ChannelId
);

/*******************************************************************************
** Traceability      :                                                        **
**                                                                            **
** Syntax            : Std_ReturnType Sent_FDFLParameters                     **
**                    (                                                       **
**                      Sent_ChannelIdxType ChannelId                         **
**                    )                                                       **
**                                                                            **
** Description       : This function:                                         **
**                      - reads the status of FDFL parameters                 **
**                                                                            **
** Service ID        : 0xA3                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Non-Reentrant                                          **
**                                                                            **
** Parameters(in)    : ChannelId - SENT Channel's status has to be read       **
**                                                                            **
** Parameters (out)  : none                                                   **
**                                                                            **
** Return value      : none                                                   **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Sent_FDFLParameters
(
        const Sent_ChannelIdxType ChannelId
);
/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/
/******************************************************************************
**                      Private Variable Definitions                         **
******************************************************************************/
/* To store the SENT driver configuration pointer */
//static const SentModule_ConfigType *Sent_kConfigPtr;
#define SENT_STOP_SEC_CODE_QM_GLOBAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Sent_MemMap.h"
/* The file is included to get extern declaration of all the configuration root
structure. The extern declaration of configuration root structure is needed by
application software */
#include "Sent_PBcfg.h"
#endif /* SENT_H */
