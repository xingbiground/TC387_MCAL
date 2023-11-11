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
**  FILENAME     : Adc.h                                                      **
**                                                                            **
**  VERSION      : 16.0.0                                                     **
**                                                                            **
**  DATE         : 2020-07-20                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID={CE9C864B-D74D-45af-8B1B-2BB0535DA5B6},    **
**                                 {F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}]    **
**                                                                            **
**  DESCRIPTION  : Adc Driver header definition file                          **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of ADC Driver,                           **
**                     AUTOSAR Release 4.2.2 and 4.4.0                        **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef ADC_H
#define ADC_H
/* [cover parentID={B2A31D0F-3CF7-47d9-BD9E-36AE5295CFEF}] */
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Std_Types.h"
#include "McalLib.h"
#include "Adc_Cfg.h"
#if (ADC_GTM_AVAILABLE == STD_ON)
#include "Mcu_17_TimerIp.h"
#endif
/* [/cover] */
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/* [cover parentID={055BDD8A-C95E-4814-ACCB-19E83F1633ED}] */
#define ADC_VENDOR_ID                       ((uint16)17U)
#define ADC_MODULE_ID                       ((uint16)123U)
#define ADC_MODULE_INSTANCE                 ((uint8)0U)
/* [/cover] */

/* [cover parentID={A5B1DAC2-4EA6-4fe3-A61E-A351E74D6639}]
    Safety Mechanism for ASIL B [/cover] */
/* DET - Default Error Tracer ID's */
#define ADC_E_NO_ERR                        ((uint8)0x00U)
/*[cover parentID={3B5188F7-D046-4db7-8701-FE9E3523DA92}]  [/cover]*/
#define ADC_E_UNINIT                        ((uint8)0x0AU)
/*[cover parentID={5A623159-C025-463f-9D28-D82BA12CD245}]  [/cover]*/
#define ADC_E_BUSY                          ((uint8)0x0BU)
/*[cover parentID={DBE28F13-23B1-4430-9434-CF1DC41F785E}]  [/cover]*/
#define ADC_E_IDLE                          ((uint8)0x0CU)
/*[cover parentID={7C8A8459-505A-440f-BF2D-4892D3F5CD79}]  [/cover]*/
#define ADC_E_ALREADY_INITIALIZED           ((uint8)0x0DU)
/*[cover parentID={23AF3D3D-4BC1-498f-910F-988C76C1C6A5}]  [/cover]*/
#define ADC_E_PARAM_CONFIG                  ((uint8)0x0EU)
/*[cover parentID={A6BA838B-7A1D-469a-835F-3E38DCFA1206}]  [/cover]*/
#define ADC_E_PARAM_POINTER                 ((uint8)0x14U)
/*[cover parentID={29B48601-972A-4b3e-8B4D-5D8D25281C46}]  [/cover]*/
#define ADC_E_PARAM_GROUP                   ((uint8)0x15U)
/*[cover parentID={11826CE6-B727-4026-A939-0C948C43AD2A}]  [/cover]*/
#define ADC_E_WRONG_CONV_MODE               ((uint8)0x16U)
/*[cover parentID={A65ED8B5-2372-4b9b-83AA-9C3FD6B1E685}]  [/cover]*/
#define ADC_E_WRONG_TRIGG_SRC               ((uint8)0x17U)
/*[cover parentID={6D028623-4F54-4e1e-AF65-4D5693DE88D9}]  [/cover]*/
#define ADC_E_NOTIF_CAPABILITY              ((uint8)0x18U)
/*[cover parentID={DFBE5718-3E9B-4ba0-8616-F2F1861A641A}]  [/cover]*/
#define ADC_E_BUFFER_UNINIT                 ((uint8)0x19U)
/*[cover parentID={9EE94B26-B526-491d-8FCC-BFE3466424C1}]  [/cover]*/
#define ADC_E_NOT_DISENGAGED                ((uint8)0x1AU)
/*[cover parentID={39765BA4-5EA3-4eac-9703-3F05AE9BCAEB}]  [/cover]*/
#define ADC_E_POWER_STATE_NOT_SUPPORTED     ((uint8)0x1BU)
#define ADC_E_TRANSITION_NOT_POSSIBLE       ((uint8)0x1CU)
/*[cover parentID={23C037CF-632E-46fc-BD0B-595C843E33F0}]  [/cover]*/
#define ADC_E_PERIPHERAL_NOT_PREPARED       ((uint8)0x1DU)
/*[cover parentID={90995A28-B06B-48dd-AF96-01D960648CCF}]  [/cover]*/
#define ADC_E_CONVERTER_OFF                 ((uint8)0x30U)


/* Multi-Core DET - Tracer ID's */
/*[cover parentID={0D8F9175-6531-410b-91D4-03F58CA7C705}]  [/cover]*/
#define ADC_E_CORE_NOT_CONFIGURED           ((uint8)0x64U)
/*[cover parentID={3AD25BE6-C94B-4354-85F4-842EFDE941B5}]  [/cover]*/
#define ADC_E_CORE_GROUP_MISMATCH           ((uint8)0x65U)
/*[cover parentID={0F5E1CFD-E6D0-400b-A69A-6AF1AF85DA4C}]  [/cover]*/
#define ADC_E_MASTER_CORE_UNINIT            ((uint8)0x66U)
/*[cover parentID={CFF7A76D-BF03-4f11-857F-A57A4810978F}]  [/cover]*/
#define ADC_E_SLAVE_CORE_INIT               ((uint8)0x67U)

/*Safety Error - Tracer ID's */
/* [cover parentID={A5B1DAC2-4EA6-4fe3-A61E-A351E74D6639}]
    Safety Mechanism for ASIL B [/cover] */
/*[cover parentID={029AE45D-8A32-48e8-86E2-0B01CEA5FC97}]  [/cover]*/
#define ADC_SE_CALIB_ONGOING                ((uint8)0xC8U)
/*[cover parentID={A169E730-037A-4342-B603-F4838D551DC8}]  [/cover]*/
#define ADC_SE_INT_PLAUSIBILITY             ((uint8)0xC9U)
/*[cover parentID={56593F89-99C5-4339-9AAB-158348720581}]  [/cover]*/
#define ADC_SE_POWER_STATE_INVALID          ((uint8)0xCAU)
/*[cover parentID={A2B967D5-B0F5-41cb-83DC-0358C1D59E4D}]  [/cover]*/
#define ADC_SE_PARAM_KERNEL                 ((uint8)0xCBU)

#define ADC_SID_INIT                        ((uint8)0x00U)
#define ADC_SID_DEINIT                      ((uint8)0x01U)
#define ADC_SID_START_GROUP_CONVERSION      ((uint8)0x02U)
#define ADC_SID_STOP_GROUP_CONVERSION       ((uint8)0x03U)
#define ADC_SID_READ_GROUP                  ((uint8)0x04U)
#define ADC_SID_ENABLE_HARDWARE_TRIGGER     ((uint8)0x05U)
#define ADC_SID_DISABLE_HARDWARE_TRIGGER    ((uint8)0x06U)
#define ADC_SID_ENABLE_GROUP_NOTIFICATION   ((uint8)0x07U)
#define ADC_SID_DISABLE_GROUP_NOTIFICATION  ((uint8)0x08U)
#define ADC_SID_GET_GROUP_STATUS            ((uint8)0x09U)
#define ADC_SID_GET_VERSION_INFO            ((uint8)0x0AU)
#define ADC_SID_GET_STREAM_LAST_POINTER     ((uint8)0x0BU)
#define ADC_SID_SETUP_RESULT_BUFFER         ((uint8)0x0CU)
#define ADC_SID_SET_POWER_STATE             ((uint8)0x10U)

#define ADC_SID_GET_STARTUP_CAL_STATUS      ((uint8)0x30U)
#define ADC_SID_TRIGGER_STARTUP_CAL         ((uint8)0x31U)
#define ADC_SID_INIT_CHECK                  ((uint8)0x32U)
#define ADC_SID_RS0_INTRPT_HANDLER          ((uint8)0x33U)
#define ADC_SID_RS1_INTRPT_HANDLER          ((uint8)0x34U)
#define ADC_SID_RS2_INTRPT_HANDLER          ((uint8)0x35U)
#define ADC_SID_CH_INTRPT_HANDLER           ((uint8)0x36U)

#define ADC_SID_GET_CURRENT_POWER_STATE     ((uint8)0x11U)
#define ADC_SID_GET_TARGET_POWER_STATE      ((uint8)0x12U)
#define ADC_SID_PREPARE_POWER_STATE         ((uint8)0x13U)

/* No. of kernels per synchronization group */
#define ADC_KERNELS_PER_SYNGRP             (4U)

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/* [cover parentID={1AE97C78-251D-4385-8500-96C5CF438CE4}]  [/cover]*/
/*Type Definition for  Adc_ChannelType */
typedef uint8 Adc_ChannelType;

/* [cover parentID={42BD172B-CBEB-4d47-B460-A727E170E9BC}]  [/cover]*/
/*Type Definition for  Adc_GroupType */
typedef uint16 Adc_GroupType;

/* [cover parentID={3DA422AF-5587-4e37-9D57-F52093E53FA9}]  [/cover]*/
/*Type Definition for  Adc_ValueGroupType */
typedef uint16 Adc_ValueGroupType;

/* [cover parentID={1741C687-2EF7-4b6a-8B56-238CDBB442DA}]  [/cover]*/
/*Type Definition for  Adc_ConversionTimeType */
typedef uint8 Adc_ConversionTimeType;

/* [cover parentID={4F7EFD1E-DC3F-4d2c-9D29-8F0D95C929D0}]  [/cover]*/
/*Type Definition for  Adc_SamplingTimeType */
typedef uint8 Adc_SamplingTimeType;

/* [cover parentID={A0322806-F8CF-4655-93E7-52D8E74BB69F}]  [/cover]*/
/*Type Definition for  Adc_ResolutionType */
typedef uint8 Adc_ResolutionType;

/* [cover parentID={782B6C9A-6B35-4205-AAC0-59A629484099}]  [/cover]*/
/*Type Definition for  Adc_GroupPriorityType */
typedef uint8 Adc_GroupPriorityType;

/* [cover parentID={C5644C0D-8A53-413c-9019-011F83CE0BEC}]  [/cover]*/
/*Type Definition for Adc_StreamNumSampleType */
typedef uint8 Adc_StreamNumSampleType;

/* [cover parentID={6E603295-1F49-4bff-BD7E-FC0A349D7157}]  [/cover]*/
/*Type Definition for Adc_HwTriggerTimerType */
typedef uint16 Adc_HwTriggerTimerType;

/* [cover parentID={AEBD942A-F05F-4679-8818-ABEB6AE58686}]  [/cover]*/
/*Type Definition for  Adc_ResultRegType*/
typedef uint8 Adc_ResultRegType;

/* [cover parentID={092EE1A4-B8C4-43d8-9575-75CE5A08DC2E}]  [/cover]*/
/*Type Definition for  Adc_PrescaleType*/
typedef uint8 Adc_PrescaleType;

/* [cover parentID={1FC0B5FB-0E67-4acd-8E3D-13816F8E7136}]  [/cover]*/
/*Type Definition for  Adc_NotifyFnPtrType - Notification Function*/
typedef void (*Adc_NotifyFnPtrType)(void);

/* [cover parentID={FBDB1992-69BA-4bb1-8FDF-547851FE37BB}]  [/cover]*/
/*Type Definition for  Adc_StatusType */
typedef uint8 Adc_StatusType;
#define ADC_IDLE                        ((Adc_StatusType)0U)
#define ADC_BUSY                        ((Adc_StatusType)1U)
#define ADC_COMPLETED                   ((Adc_StatusType)2U)
#define ADC_STREAM_COMPLETED            ((Adc_StatusType)3U)

/* [cover parentID={78721DB3-91A1-4ee1-81E8-2D5095C091AD}]  [/cover]*/
/*Type Definition for  Adc_StartupCalibStatusType */
typedef uint8 Adc_StartupCalibStatusType;
#define ADC_STARTUP_CALIB_NOT_TRIGGERED ((Adc_StartupCalibStatusType)0U)
#define ADC_STARTUP_CALIB_ONGOING       ((Adc_StartupCalibStatusType)1U)
#define ADC_STARTUP_CALIB_OVER          ((Adc_StartupCalibStatusType)2U)

/* [cover parentID={3D92ABB0-1B96-40b6-A970-B3DC09E74E16}]  [/cover]*/
/*Type Definition for  Adc_TriggerSourceType */
typedef uint8 Adc_TriggerSourceType;
#define ADC_TRIGG_SRC_SW                ((Adc_TriggerSourceType)0U)
#define ADC_TRIGG_SRC_HW                ((Adc_TriggerSourceType)1U)

/* [cover parentID={B6EC1809-0850-4ef3-B423-97BA05E70A3B}]  [/cover]*/
/*Type Definition for  Adc_GroupConvModeType */
typedef uint8 Adc_GroupConvModeType;
#define ADC_CONV_MODE_ONESHOT           ((Adc_GroupConvModeType)0U)
#define ADC_CONV_MODE_CONTINUOUS        ((Adc_GroupConvModeType)1U)

/*[cover parentID={44CC688C-0B16-4012-AAA1-5F053FF73513}]  [/cover]*/
/*Type Definition for Adc_SyncConvModeType */
typedef uint8 Adc_SyncConvModeType;
#define ADC_SYNC_CONV_MODE_NONE         ((Adc_SyncConvModeType)0U)
#define ADC_SYNC_CONV_MODE_MASTER       ((Adc_SyncConvModeType)1U)
#define ADC_SYNC_CONV_MODE_SLAVE        ((Adc_SyncConvModeType)2U)

/* [cover parentID={DA1A7831-5D80-4236-A4DF-C256E545B826}]  [/cover]*/
/*Type Definition for  Adc_StreamBufferModeType*/
typedef uint8 Adc_StreamBufferModeType;
#define ADC_STREAM_BUFFER_LINEAR        ((Adc_StreamBufferModeType)0U)
#define ADC_STREAM_BUFFER_CIRCULAR      ((Adc_StreamBufferModeType)1U)

/* [cover parentID={CE194AA1-D1B2-4a2b-BFAA-9E571CC103EA}]  [/cover]*/
/*Type Definition for  Adc_GroupAccessModeType*/
typedef uint8 Adc_GroupAccessModeType;
#define ADC_ACCESS_MODE_SINGLE          ((Adc_GroupAccessModeType)0U)
#define ADC_ACCESS_MODE_STREAMING       ((Adc_GroupAccessModeType)1U)

/* [cover parentID={EFEFDF07-17B4-48b6-B50E-965E27BAEE34}]  [/cover]*/
/*Type Definition for  Adc_HwTriggerSignalType*/
typedef uint8 Adc_HwTriggerSignalType;
#define ADC_HW_TRIG_RISING_EDGE         ((Adc_HwTriggerSignalType)0U)
#define ADC_HW_TRIG_FALLING_EDGE        ((Adc_HwTriggerSignalType)1U)
#define ADC_HW_TRIG_BOTH_EDGES          ((Adc_HwTriggerSignalType)2U)

/* [cover parentID={086DAE53-8F13-490f-8178-3796EDF409F6}]  [/cover]*/
/*Type Definition for  Adc_GroupReplacementType*/
typedef uint8 Adc_GroupReplacementType;
#define ADC_GROUP_REPL_ABORT_RESTART    ((Adc_GroupReplacementType)0U)
#define ADC_GROUP_REPL_SUSPEND_RESUME   ((Adc_GroupReplacementType)1U)

/* [cover parentID={D2E66836-A178-440f-B365-0611EF34BA21}]  [/cover]*/
/*Type Definition for  Adc_HwTrigGateType*/
typedef uint8 Adc_HwTrigGateType;
#define ADC_GTM_HW_USED                 ((Adc_HwTrigGateType)0U)
#define ADC_ERU_HW_USED                 ((Adc_HwTrigGateType)1U)
#define ADC_OTHER_HW_USED               ((Adc_HwTrigGateType)2U)

/*[cover parentID={93692CA5-5EB4-4735-998E-371DCD1468AF}]  [/cover]*/
/*Type Definition for Adc_PowerStateType*/
typedef uint8 Adc_PowerStateType;
#define ADC_FULL_POWER  ((Adc_PowerStateType)0U)
#define ADC_FAST_STANDBY_MODE  ((Adc_PowerStateType)1U)
#define ADC_SLOW_STANDBY_MODE  ((Adc_PowerStateType)2U)
#define ADC_OFF  ((Adc_PowerStateType)3U)

/* [cover parentID={4CE8B1D8-3649-48f8-8F0A-16ECF5474293}]  [/cover]*/
/*Type Definition for  Adc_PriorityImplementationType*/
typedef uint8 Adc_PriorityImplementationType;
/*ADC_PRIORITY_NONE - 0U
  ADC_PRIORITY_HW - 1U
  ADC_PRIORITY_HW_SW - 2U*/

/* [cover parentID={CE1D2941-093C-49c0-A3EA-7A257F251630}]  [/cover]*/
/*Type Definition for  Adc_ResultAlignmentType*/
typedef uint8 Adc_ResultAlignmentType;
/* ADC_ALIGN_RIGHT - 0U
   ADC_ALIGN_LEFT - 1U */

/* [cover parentID={508C4125-00A6-426e-896F-AD2EAD1A8904}]  [/cover]*/
/*Type Definition for  Adc_ChannelRangeSelectType*/
typedef enum
{
  ADC_RANGE_UNDER_LOW = 0U,
  ADC_RANGE_BETWEEN = 1U,
  ADC_RANGE_OVER_HIGH = 2U,
  ADC_RANGE_ALWAYS = 3U,
  ADC_RANGE_NOT_UNDER_LOW = 4U,
  ADC_RANGE_NOT_BETWEEN = 5U,
  ADC_RANGE_NOT_OVER_HIGH = 6U
} Adc_ChannelRangeSelectType;

/*[cover parentID={8C63AE46-B3BC-4cd3-8D98-DF8E104B9156}]  [/cover]*/
/*Type Definition for  Adc_PowerStateRequestResultType*/
typedef enum
{
  ADC_SERVICE_ACCEPTED = 0U,
  ADC_NOT_INIT = 1U,
  ADC_SEQUENCE_ERROR = 2U,
  ADC_HW_FAILURE = 3U,
  ADC_POWER_STATE_NOT_SUPP = 4U,
  ADC_TRANS_NOT_POSSIBLE = 5U
} Adc_PowerStateRequestResultType;

/*[cover parentID={A99FE780-5646-418f-A512-3BBAB8882F1B}]  [/cover]*/
/*Type Definition for  Adc_EruChannelCfgType*/
typedef struct
{
  uint16 EruEicrCfg;
  uint16 EruIgcrCfg;
  uint8 ErsChannel;
  uint8 OguChannel;
} Adc_EruChannelCfgType;

/* [cover parentID= {382F9FF1-66C3-4898-8D8E-113D9DBD4DCE}]  [/cover]*/
/*Type Definition for  Adc_GroupDefType*/
typedef struct
{
  Adc_ChannelType ASChannelId;
  Adc_ChannelType AnalogChannelNo;
  Adc_ResultRegType ResultReg;
  uint32 AnChDiagnosticsCfg;
} Adc_GroupDefType;

/* [cover parentID= {4B7CF68E-B020-49f6-8288-5EA97B0D8085}]  [/cover]*/
/*Type Definition for  Adc_GroupCfgType*/
typedef struct
{
  Adc_NotifyFnPtrType NotifyPtr;
  const Adc_GroupDefType *GroupDefinition;
  #if (ADC_GTM_AVAILABLE == STD_ON)
  const Mcu_17_Gtm_TomAtomChConfigType *GtmTrigCfg;
  const Mcu_17_Gtm_TomAtomChConfigType *GtmGateCfg;
  #endif
  const Adc_EruChannelCfgType *EruTrigCfg;
  const Adc_EruChannelCfgType *EruGateCfg;
  uint32 GroupQCtrlCfg;
  uint32 GroupQModeCfg;
  uint32 AliasChCfg;
  uint32 GrpReqTmCfg;
  uint16 ChannelMask;
  uint16 ResultRegMask;
  uint16 SyncChannelMask;
  uint16 SyncResRegMask;
  Adc_TriggerSourceType TriggerSource;
  Adc_GroupConvModeType ConvMode;
  Adc_GroupAccessModeType AccessMode;
  Adc_StreamBufferModeType StreamMode;
  Adc_StreamNumSampleType NumOfSamples;
  Adc_HwTrigGateType HwTrigType;
  Adc_HwTrigGateType HwGateType;
  uint8 GrpPriority;
  uint8 NoOfChannels;
  uint8 LimitCheckGroup;
  uint8 GrpEmuxCfg;
  uint8 DiagnosticChGrp;
} Adc_GroupCfgType;

/* [cover parentID={7AA424F7-C379-4ccd-B8BD-E77C070232BA}]  [/cover]*/
/*Type Definition for  Adc_ChannelCfgType*/
typedef struct
{
  uint32 ChannelChctrCfg;
  uint32 BoundaryValues;
  Adc_ChannelType AnChannelNo;
  uint8 LimitCheckEnabled;
} Adc_ChannelCfgType;

/* [cover parentID={966E4F2D-428D-4abb-8A65-F11BA7E5F2CD}]  [/cover]*/
/*Type Definition for  Adc_HwCfgType*/
typedef struct
{
  uint32 GrpAnalogFuncCfg;
  uint32 GrpArbitCfg;
  uint32 GrpArbitPrioCfg;
  uint32 KernelInputClass0Cfg;
  uint32 KernelInputClass1Cfg;
  uint32 GrpSyncCtrlCfg;
} Adc_HwCfgType;

/* [cover parentID={0C31DECB-2DD9-4faa-AC70-CFCE7713F46C}]  [/cover]*/
/*Type Definition for  Adc_HwUnitCfgType*/
typedef struct
{
  const Adc_HwCfgType *HwCfgPtr;
  const Adc_ChannelCfgType *ChCfgPtr;
  const Adc_GroupCfgType *GrpCfgPtr;
  uint32 SwTrigGrpMask;
  uint32 HwTrigGrpMask;
  Adc_SyncConvModeType SyncConvMode;
  uint8 SlaveKernels[ADC_KERNELS_PER_SYNGRP - 1U];
  uint8 NoOfGroups;
  uint8 SRNUsed;
} Adc_HwUnitCfgType;

/* [cover parentID={37ADEA95-8386-4391-A186-367CDEF8C4A5}]  [/cover]*/
/*Type Definition for  Adc_GlobalCfgType*/
typedef struct
{
  uint32 GlobalCfg;
  uint32 GlobInputClass0Cfg;
  uint32 GlobInputClass1Cfg;
  uint32 GlobEmuxGrpInterfaceCfg;
} Adc_GlobalCfgType;

/* [cover parentID={11C54D40-5E7A-43de-BBC3-323D820B5862}]  [/cover]*/
/*Type Definition for Adc_CoreConfigType*/
typedef struct
{
  const Adc_HwUnitCfgType *HwUnitCfgPtr[ADC_MAX_KERNEL_ID];
} Adc_CoreConfigType;

/* [cover parentID={374D8ED6-AA62-4e2f-9A65-AF83705CD7F7}]  [/cover]*/
/*Type Definition for Adc_ConfigType*/
typedef struct
{
  const Adc_GlobalCfgType     *GlobalCfgPtr;
  const Adc_CoreConfigType    *CoreCfgPtr[MCAL_NO_OF_CORES];
} Adc_ConfigType;

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
#define ADC_START_SEC_CODE_ASIL_B_GLOBAL
#include "Adc_MemMap.h"
/*******************************************************************************
** Traceability: [cover parentID]                                             **
**                                                                            **
** Syntax           : void Adc_Init                                           **
**                    (                                                       **
**                      const Adc_ConfigType * const ConfigPtr                **
**                    )                                                       **
**                                                                            **
** Description      : This API initializes the ADC hardware units and clear   **
**                    global variables to their reset state. The SFRs of the  **
**                    configured kernels are first reset to default values and**
**                    then initialized as per the configuration.              **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x00                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Re-entrant for different CPU core                       **
**                                                                            **
** Parameters(in)   : ConfigPtr - Pointer to ADC configuration Set            **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
extern void Adc_Init(const Adc_ConfigType * const ConfigPtr);

#if(ADC_INIT_CHECK_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID]                                             **
**                                                                            **
** Syntax           : Std_ReturnType Adc_InitCheck                            **
**                    (                                                       **
**                      const Adc_ConfigType * const ConfigPtr                **
**                    )                                                       **
**                                                                            **
** Description      : This API returns the status of the modules              **
**                    initialization in context to the core from where the    **
**                    API is invoked. The API is available when safety is     **
**                    enabled or initialization check is explicitly enabled   **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x32                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Re-entrant for different CPU core                       **
**                                                                            **
** Parameters(in)   : ConfigPtr - Pointer to ADC configuration Set            **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK: Initialization verification passed                **
**                    E_NOT_OK: Initialization verification failed            **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Adc_InitCheck(const Adc_ConfigType * const ConfigPtr);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Adc_InitCheck(ConfigPtr)     \
                              (ERROR_Adc_InitCheck_API_IS_NOT_SELECTED)
#endif

#if(ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING)
/*******************************************************************************
** Traceability: [cover parentID]                                             **
**                                                                            **
** Syntax           : Std_ReturnType Adc_SetupResultBuffer                    **
**                    (                                                       **
**                      const Adc_GroupType Group,                            **
**                      const Adc_ValueGroupType *const DataBufferPtr         **
**                    )                                                       **
**                                                                            **
** Description      : This API will set-up the group's result buffer,         **
**                    where the conversion results will be stored.            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x0C                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Re-Entrant                                              **
**                                                                            **
** Parameters(in)   : Group ID and Data buffer pointer                        **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK/E_NOT_OK                                           **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Adc_SetupResultBuffer(const Adc_GroupType Group,\
                                const Adc_ValueGroupType * const DataBufferPtr);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Adc_SetupResultBuffer(Group, DataBufferPtr)  \
                      (ERROR_Adc_SetupResultBuffer_API_IS_NOT_SELECTED)
#endif

#if (ADC_DEINIT_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID]                                             **
**                                                                            **
** Syntax           : void Adc_DeInit                                         **
**                    (                                                       **
**                      void                                                  **
**                    )                                                       **
**                                                                            **
** Description      : This API resets all SFRs (including SRC) of the kernels **
**                    configured by Adc_Init to their reset states. It also   **
**                    resets the global SFR's (common to all Kernels) of the  **
**                    EVADC IP.                                               **
**                    Note: SFRs of kernels not configured by Adc_Init are    **
**                    not de-initialized by this API                          **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x01                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Re-entrant for different CPU core                       **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
extern void Adc_DeInit(void);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Adc_DeInit() (ERROR_Adc_DeInit_API_IS_NOT_SELECTED)
#endif

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID]                                             **
**                                                                            **
** Syntax           : void Adc_StartGroupConversion                           **
**                    (                                                       **
**                      const Adc_GroupType Group                             **
**                    )                                                       **
**                                                                            **
** Description      : This API setups the group for conversion and starts the **
**                    conversion of the requested ADC Channel group           **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x02                                                    **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Re-entrant for channel groups executing on different    **
**                    ADC hardware groups                                     **
**                                                                            **
** Parameters(in)   : Group - Numeric ID of requested ADC Channel group.      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
extern void Adc_StartGroupConversion(const Adc_GroupType Group);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Adc_StartGroupConversion(Group) \
(ERROR_Adc_StartGroupConversion_API_IS_NOT_SELECTED)
#endif

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID]                                             **
**                                                                            **
** Syntax           : void Adc_StopGroupConversion                            **
**                    (                                                       **
**                      const Adc_GroupType Group                             **
**                    )                                                       **
**                                                                            **
** Description      : This API stops the conversion of the requested ADC      **
**                    Channel group                                           **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x03                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Re-entrant for channel groups executing on different    **
**                    ADC hardware groups                                     **
**                                                                            **
** Parameters(in)   : Group - Numeric ID of requested ADC Channel group.      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
extern void Adc_StopGroupConversion(const Adc_GroupType Group);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Adc_StopGroupConversion(Group) \
(ERROR_Adc_StopGroupConversion_API_IS_NOT_SELECTED)
#endif

#if (ADC_READ_GROUP_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID]                                             **
**                                                                            **
** Syntax           : Std_ReturnType Adc_ReadGroup                            **
**                    (                                                       **
**                      const Adc_GroupType Group                             **
**                      Adc_ValueGroupType * const DataBufferPtr              **
**                    )                                                       **
**                                                                            **
** Description      : This API reads the group conversion result of the last  **
**                    completed conversion round of the requested group and   **
**                    stores the channel's conversion value starting from     **
**                    DataBufferPtr address. The channel's conversion values  **
**                    are stored in ascending channel number order            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x04                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Re-entrant for different AdcChannel Groups              **
**                                                                            **
** Parameters(in)   : Group - Numeric ID of requested ADC Channel group.      **
**                                                                            **
** Parameters (out) : DataBufferPtr - Location to store the requested Group's **
**                    channels conversion result                              **
**                                                                            **
** Return value     : E_OK - Results are available and written to the data    **
**                           buffer                                           **
**                    E_NOT_OK - No results are available or development      **
**                               error occurred                               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Adc_ReadGroup(const Adc_GroupType Group,
                                    Adc_ValueGroupType * const DataBufferPtr);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Adc_ReadGroup(Group,DataBufferPtr) \
(ERROR_Adc_ReadGroup_API_IS_NOT_SELECTED)
#endif

#if (ADC_HW_TRIGGER_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID]                                             **
**                                                                            **
** Syntax           : void Adc_EnableHardwareTrigger                          **
**                    (                                                       **
**                      const Adc_GroupType Group                             **
**                    )                                                       **
**                                                                            **
** Description      : This API setups the group for conversion and enables    **
**                    the hardware trigger for the requested ADC Group.       **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x05                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Re-entrant for channel groups executing on different    **
**                    ADC hardware groups                                     **
**                                                                            **
** Parameters(in)   : Group - Numeric ID of requested ADC Channel group.      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
extern void Adc_EnableHardwareTrigger(const Adc_GroupType Group);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Adc_EnableHardwareTrigger(Group) \
(ERROR_Adc_EnableHardwareTrigger_API_IS_NOT_SELECTED)
#endif

#if (ADC_HW_TRIGGER_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID]                                             **
**                                                                            **
** Syntax           : void Adc_DisableHardwareTrigger                         **
**                    (                                                       **
**                      const Adc_GroupType Group                             **
**                    )                                                       **
**                                                                            **
** Description      : This function  stops the ongoing conversion and disables**
**                    hardware trigger for the requested ADC Channel group.   **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x06                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Re-entrant for channel groups executing on different    **
**                    ADC hardware groups                                     **
**                                                                            **
** Parameters(in)   : Group - Numeric ID of requested ADC Channel group.      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
extern void Adc_DisableHardwareTrigger(const Adc_GroupType Group);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Adc_DisableHardwareTrigger(Group) \
(ERROR_Adc_DisableHardwareTrigger_API_IS_NOT_SELECTED)
#endif

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID]                                             **
**                                                                            **
** Syntax           : void Adc_EnableGroupNotification                        **
**                    (                                                       **
**                      const Adc_GroupType Group                             **
**                    )                                                       **
**                                                                            **
** Description      : This API enables the notification mechanism for the     **
**                    requested ADC Channel group.                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x07                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Re-entrant                                              **
**                                                                            **
** Parameters(in)   : Group - Numeric ID of requested ADC Channel group.      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
extern void Adc_EnableGroupNotification(const Adc_GroupType Group);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Adc_EnableGroupNotification(Group) \
(ERROR_Adc_EnableGroupNotification_API_IS_NOT_SELECTED)
#endif

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID]                                             **
**                                                                            **
** Syntax           : void Adc_DisableGroupNotification                       **
**                    (                                                       **
**                      const Adc_GroupType Group                             **
**                    )                                                       **
**                                                                            **
** Description      : This API disables the notification mechanism for the    **
**                    requested ADC Channel group.                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x08                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Re-Entrant                                              **
**                                                                            **
** Parameters(in)   : Group - Numeric ID of requested ADC Channel group.      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
extern void Adc_DisableGroupNotification(const Adc_GroupType Group);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Adc_DisableGroupNotification(Group) \
(ERROR_Adc_DisableGroupNotification_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
** Traceability: [cover parentID]                                             **
**                                                                            **
** Syntax           : Adc_StatusType Adc_GetGroupStatus                       **
**                    (                                                       **
**                      const Adc_GroupType Group                             **
**                    )                                                       **
**                                                                            **
** Description      : This API returns the conversion status of the requested **
**                    ADC Channel group.                                      **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x09                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Re-Entrant                                              **
**                                                                            **
** Parameters(in)   : Group - Numeric ID of requested ADC Channel group.      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : Adc_StatusType                                          **
**                    Conversion status for the requested group               **
**                                                                            **
*******************************************************************************/
extern Adc_StatusType Adc_GetGroupStatus(const Adc_GroupType Group);

#if(ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING)
/*******************************************************************************
** Traceability: [cover parentID]                                             **
**                                                                            **
** Syntax           : Adc_StreamNumSampleType Adc_GetStreamLastPointer        **
**                    (                                                       **
**                      const Adc_GroupType Group                             **
**                      Adc_ValueGroupType ** const PtrToSamplePtr            **
**                    )                                                       **
**                                                                            **
** Description      : This API returns the number of valid samples per channel**
**                    stored in the result buffer. It also returns a pointer  **
**                    to the result buffer containing the latest available    **
**                    conversion results.                                     **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x0b                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Re-entrant for different AdcChannel Groups              **
**                                                                            **
** Parameters(in)   : Group - Numeric ID of requested ADC Channel group.      **
**                                                                            **
** Parameters (out) : SamplePtr - Pointer to the last acquired value.         **
**                                                                            **
** Return value     : Adc_StreamNumSampleType                                 **
**                    Number of valid samples per channel.                    **
**                                                                            **
*******************************************************************************/
extern Adc_StreamNumSampleType Adc_GetStreamLastPointer(
       const Adc_GroupType Group,  Adc_ValueGroupType ** const PtrToSamplePtr);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application and
  not enabled in the configuration*/
#define Adc_GetStreamLastPointer(Group,PtrToSamplePtr) \
(ERROR_Adc_GetStreamLastPointer_API_IS_NOT_SELECTED)
#endif

#if (ADC_STARTUP_CALIB_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID]                                             **
**                                                                            **
** Syntax           : Std_ReturnType Adc_TriggerStartupCal                    **
**                    (                                                       **
**                       void                                                 **
**                    )                                                       **
**                                                                            **
** Description      : This API starts the start up calibration of all ADC     **
**                    kernels.                                                **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x31                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK: Startup calibration has been started              **
**                    E_NOT_OK: Development error occured                     **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Adc_TriggerStartupCal(void);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Adc_TriggerStartupCal() \
(ERROR_Adc_TriggerStartupCal_API_IS_NOT_SELECTED)
#endif

#if (ADC_STARTUP_CALIB_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID]                                             **
**                                                                            **
** Syntax           : Adc_StartupCalibStatusType Adc_GetStartupCalStatus      **
**                    (                                                       **
**                       void                                                 **
**                    )                                                       **
**                                                                            **
** Description      : This API returns the status of the start up calibration.**
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x30                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Re-Entrant                                              **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : ADC_STARTUP_CALIB_NOT_TRIGGERED: Startup calibration has**
**                                                     not been triggered     **
**                    ADC_STARTUP_CALIB_ONGOING: Startup calibration is       **
**                                               ongoing                      **
**                    ADC_STARTUP_CALIB_OVER: Startup calibration has         **
**                                            completed                       **
**                                                                            **
*******************************************************************************/
extern Adc_StartupCalibStatusType Adc_GetStartupCalStatus(void);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Adc_GetStartupCalStatus(Group) \
(ERROR_Adc_GetStartupCalStatus_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
** Traceability: [cover parentID]                                             **
**                                                                            **
** Syntax           : void Adc_RS0EventInterruptHandler                       **
**                    (                                                       **
**                       const uint32 KernelId                                **
**                    )                                                       **
**                                                                            **
** Description      : This API Handles the interrupts from Request source 0   **
**                    for passed ADC KernelId.                                **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Re-entrant for different ADC hardware groups            **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID for which the Interrupt handler    **
**                    is invoked                                              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Adc_RS0EventInterruptHandler(const uint32 KernelId);

#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
/*******************************************************************************
** Traceability: [cover parentID]                                             **
**                                                                            **
** Syntax           : void Adc_RS1EventInterruptHandler                       **
**                    (                                                       **
**                       const uint32 KernelId                                **
**                    )                                                       **
**                                                                            **
** Description      : This API Handles the interrupts from Request source 1   **
**                    for passed ADC KernelId.                                **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Re-entrant for different ADC hardware groups            **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID for which the Interrupt handler    **
**                    is invoked                                              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Adc_RS1EventInterruptHandler(const uint32 KernelId);
#endif

#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
/*******************************************************************************
** Traceability: [cover parentID]                                             **
**                                                                            **
** Syntax           : void Adc_RS2EventInterruptHandler                       **
**                    (                                                       **
**                       const uint32 KernelId                                **
**                    )                                                       **
**                                                                            **
** Description      : This API Handles the interrupts from Request source 2   **
**                    for passed ADC KernelId.                                **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Re-entrant for different ADC hardware groups            **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID for which the Interrupt handler    **
**                    is invoked                                              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Adc_RS2EventInterruptHandler(const uint32 KernelId);
#endif

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID]                                             **
**                                                                            **
** Syntax           : void Adc_ChEventInterruptHandler                        **
**                    (                                                       **
**                       const uint32 KernelId                                **
**                    )                                                       **
**                                                                            **
** Description      : This API Handles the interrupts from ADC Channel Event  **
**                    for passed ADC KernelId.                                **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Re-entrant for different ADC hardware groups            **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID for which the Interrupt handler    **
**                    is invoked                                              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Adc_ChEventInterruptHandler(const uint32 KernelId);
#endif

#if(ADC_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID]                                             **
**                                                                            **
** Syntax           : void Adc_GetVersionInfo                                 **
**                    (                                                       **
**                      Std_VersionInfoType * const versioninfo               **
**                    )                                                       **
**                                                                            **
** Description      : This API returns the version information of this module.**
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x0a                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Re-entrant                                              **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : versioninfo -  Pointer to where to store the version    **
**                    information of this module                              **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
extern void Adc_GetVersionInfo(Std_VersionInfoType * const versioninfo);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Adc_GetVersionInfo(versioninfo) \
 (ERROR_Adc_GetVersionInfo_API_IS_NOT_SELECTED)
#endif

#if(ADC_LOW_POWER_STATE_SUPPORT == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID]                                             **
**                                                                            **
** Syntax           : Std_ReturnType Adc_PreparePowerState                    **
**                    (                                                       **
**                      const Adc_PowerStateType PowerState                   **
**                      Adc_PowerStateRequestResultType * const Result        **
**                    )                                                       **
**                                                                            **
** Description      : API starts the needed process to allow the ADC hardware **
**                    module to enter the requested power state. The API must **
**                    be invoked from all the cores using the ADC driver, as  **
**                    each call prepares the power state only for the ADC     **
**                    hardware groups used by the calling core.               **
**                    Note: This API is available only when                   **
**                    AdcLowPowerStatesSupport is configured as true.         **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x13                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different CPU cores                       **
**                                                                            **
** Parameters(in)   : PowerState                                              **
**                                                                            **
** Parameters (out) : Result                                                  **
**                                                                            **
** Return value     : E_OK: Preparation process started                       **
**                    E_NOT_OK: Service is rejected                           **
*******************************************************************************/
extern Std_ReturnType Adc_PreparePowerState(\
               const Adc_PowerStateType PowerState,\
               Adc_PowerStateRequestResultType * const Result);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application and
  not enabled in the configuration*/
#define Adc_PreparePowerState(PowerState,Result)     \
 (ERROR_Adc_PreparePowerState_API_IS_NOT_SELECTED)
#endif

#if(ADC_LOW_POWER_STATE_SUPPORT == STD_ON)
/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax           : Std_ReturnType Adc_SetPowerState                        **
**                    (                                                       **
**                      Adc_PowerStateRequestResultType * const Result        **
**                    )                                                       **
**                                                                            **
** Description      : API configures the ADC module so that it enters the     **
**                    already prepared power state, chosen between a          **
**                    predefined set of configured ones. The API must be      **
**                    invoked from all the cores using the ADC driver, as each**
**                    call sets the power state only for the ADC hardware     **
**                    groups used by the calling core.                        **
**             Note: 1.The converter automatically switches back to           **
**                    'Normal operation' from  'Fast standby mode' or         **
**                    'Slow standby mode' whenever a conversion is requested. **
**                   2.This API is available only when                        **
**                     AdcLowPowerStatesSupport is configured as true.        **
**                                                                            **
** Service ID       : 0x10                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different CPU cores                       **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : Result - Result of Power state change                   **
**                                                                            **
** Return value     : E_OK: Power Mode changed                                **
**                    E_NOT_OK: Request rejected                              **
*******************************************************************************/
extern Std_ReturnType Adc_SetPowerState(\
                                Adc_PowerStateRequestResultType * const Result);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application and
  not enabled in the configuration*/
#define Adc_SetPowerState(Result)     \
 (ERROR_Adc_SetPowerState_API_IS_NOT_SELECTED)
#endif

#if(ADC_LOW_POWER_STATE_SUPPORT == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID]                                             **
**                                                                            **
** Syntax           : Std_ReturnType Adc_GetTargetPowerState                  **
**                    (                                                       **
**                      Adc_PowerStateType * const TargetPowerState           **
**                      Adc_PowerStateRequestResultType * const Result        **
**                    )                                                       **
**                                                                            **
** Description      : API returns the current power state of the ADC hardware **
                      groups used by the calling core. (Because, power        **
                      transitions are always synchronous, the target power    **
                      state is immediately achieved.).                        **
                      Note: This API is available only when                   **
                            AdcLowPowerStatesSupport is configured as true.   **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x12                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different CPU cores                       **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters(out)   :Result - Result of Target Power mode                    **
**                    TargetPowerState - Target Power mode of ADC HW Units    **
**                                                                            **
** Return value     : E_OK: Mode could be read                                **
**                    E_NOT_OK: Service is rejected                           **
*******************************************************************************/
extern Std_ReturnType Adc_GetTargetPowerState(\
               Adc_PowerStateType * const TargetPowerState,\
               Adc_PowerStateRequestResultType * const Result);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application and
  not enabled in the configuration*/
#define Adc_GetTargetPowerState(TargetPowerState,Result)     \
 (ERROR_Adc_GetTargetPowerState_API_IS_NOT_SELECTED)
#endif

#if(ADC_LOW_POWER_STATE_SUPPORT == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID]                                             **
**                                                                            **
** Syntax           : Std_ReturnType Adc_GetCurrentPowerState                 **
**                    (                                                       **
**                      Adc_PowerStateType * const CurrentPowerState          **
**                      Adc_PowerStateRequestResultType * const Result        **
**                    )                                                       **
**                                                                            **
** Description      : API returns the current power state of the ADC hardware **
**                    groups used by the calling core.                        **
**                    Note: This API is available only when                   **
**                          AdcLowPowerStatesSupport is configured as true.   **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x11                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different CPU cores                       **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters(out)   :Result - Result of Current Power mode                   **
**                    CurrentPowerState - Current Power mode of ADC HW Units  **
**                                                                            **
** Return value     : E_OK: Mode could be read                                **
**                    E_NOT_OK: Service is rejected                           **
*******************************************************************************/
extern Std_ReturnType Adc_GetCurrentPowerState(\
               Adc_PowerStateType * const CurrentPowerState,\
               Adc_PowerStateRequestResultType * const Result);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application and
  not enabled in the configuration*/
#define Adc_GetCurrentPowerState(CurrentPowerState,Result)     \
 (ERROR_Adc_GetCurrentPowerState_API_IS_NOT_SELECTED)
#endif

#define ADC_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Adc_MemMap.h"
/* The file is included to get extern declaration of all the configuration root
structure. The extern declaration of configuration root structure is needed by
application software */
#include "Adc_PBcfg.h"
#endif

