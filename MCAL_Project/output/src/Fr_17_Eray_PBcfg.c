
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
**  FILENAME  : Fr_17_Eray_PBcfg.c                                            **
**                                                                            **
**  VERSION   : 19.0.0                                                        **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:31             !!!IGNORE-LINE!!!        **
**                                                                            **
**  GENERATOR : Build b191017-0938               !!!IGNORE-LINE!!!          **
**                                                                            **
**  BSW MODULE DECRIPTION : Fr_17_Eray.bmd                                    **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Fr configuration generated out of ECUC file                **
**                                                                            **
**  SPECIFICATION(S) : Specification of FlexRay Driver, AUTOSAR Release 4.2.2 **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/



/*******************************************************************************
**  Include Section   **
*******************************************************************************/
/* Include module header File */
#include "Fr_17_Eray.h"
  
/*******************************************************************************
**  Inclusion File Check  **
*******************************************************************************/


/*******************************************************************************
**  Private Macro Definitions **
*******************************************************************************/

/*******************************************************************************
**  Private Type Definitions  **
*******************************************************************************/


/*******************************************************************************
**  Private Function Declarations **
*******************************************************************************/


/*******************************************************************************
**  Global Function Declarations   **
*******************************************************************************/

/*******************************************************************************
  Global Constant Definitions
*******************************************************************************/

/*
@@@@@@START_OF_BUFFER_RECONFIG_DUMP@@@@@@
MSG_RAM_SIZE_TOTAL 8192
MSG_BUFFER_COUNT_MAX 128
HW_BUFFER_RECONFIGURATION_USED NO, Controller Index:0 30 32-bit words
KEY_SLOT_LPDU,1,0,4
DYNAMIC_LPDU,2
4,4
5,4
Static LPDUs for which FrIf reconfig available, length
RECONFIG_LPDU,Total:0
Number of LPDU which may share HW buffer
STATIC_LPDU,3
COM_OP,macrotick,LpduIdx,Length
PREPARE_LPDU,10110,1,4
PREPARE_LPDU,20120,3,4


PB_CFG_END

@@@@@@END_OF_BUFFER_RECONFIG_DUMP@@@@@@
*/

#define FR_17_ERAY_START_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
#include "Fr_17_Eray_MemMap.h"
/*
LPduIdx to message buffer mapping for Controller 0
*/
/* MISRA2012_RULE_5_1_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
static const uint8 Fr_17_Eray_FrMultipleConfiguration_LPduIdx2MsgBuff_0[6] =
{
  0U, 1U, 2U, 3U, 4U, 5U
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
static const uint16 Fr_17_Eray_FrMultipleConfiguration_DataPointerOffset_0[6] =
{
  24U, 25U, 26U, 27U, 28U, 29U
};

/*************** LPDU configuration Controller 0 ***************/
/* MISRA2012_RULE_5_1_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
static const Fr_17_Eray_LPduConfigType Fr_17_Eray_FrMultipleConfiguration_kLPduConfig_0 [6] =
{
  /* -------------------------  LPDU 0 ------------------------------- */
  {
    /*
    3U - Slot ID
    1U - Cycle code
    3U,- FrPChannels , add 0x1 as the hw regs take ChannelA = 1, ChannelB = 2
    and ChannelAB = 3
    1U - Message Buffer Direction: 0 - Receive, 1 - Transmit
    1U, - PPIT: 0 - Disable, 1 - Enable
    1U, - Transmission Mode : 1 - Single shot - always single shot
    0U  - Message Buffer Service Request - always set to 0
    */
    0x1f010003U,
    /*
    0x7c7U - Header CRC
    2U - Payload Length Configured
    0U - FrIfAllowDynamicLSduLength
    */
    0x000207c7U,
    FR_17_ERAY_LPDU_NOT_RECONFIGURABLE,
    /*DEM Id for FlexRay Slot Status Error. */
    FR_17_ERAY_DEM_REPORT_DISABLED
  },
  /* -------------------------  LPDU 1 ------------------------------- */
  {
    /*
    4U - Slot ID
    1U - Cycle code
    3U,- FrPChannels , add 0x1 as the hw regs take ChannelA = 1, ChannelB = 2
    and ChannelAB = 3
    0U - Message Buffer Direction: 0 - Receive, 1 - Transmit
    0U, - PPIT: 0 - Disable, 1 - Enable
    1U, - Transmission Mode : 1 - Single shot - always single shot
    0U  - Message Buffer Service Request - always set to 0
    */
    0x13010004U,
    /*
    0x0U - Header CRC
    2U - Payload Length Configured
    0U - FrIfAllowDynamicLSduLength
    */
    0x00020000U,
    FR_17_ERAY_LPDU_NOT_RECONFIGURABLE,
    /*DEM Id for FlexRay Slot Status Error. */
    FR_17_ERAY_DEM_REPORT_DISABLED
  },
  /* -------------------------  LPDU 2 ------------------------------- */
  {
    /*
    5U - Slot ID
    2U - Cycle code
    1U,- FrPChannels , add 0x1 as the hw regs take ChannelA = 1, ChannelB = 2
    and ChannelAB = 3
    1U - Message Buffer Direction: 0 - Receive, 1 - Transmit
    1U, - PPIT: 0 - Disable, 1 - Enable
    1U, - Transmission Mode : 1 - Single shot - always single shot
    0U  - Message Buffer Service Request - always set to 0
    */
    0x1d020005U,
    /*
    0x4daU - Header CRC
    2U - Payload Length Configured
    0U - FrIfAllowDynamicLSduLength
    */
    0x000204daU,
    FR_17_ERAY_LPDU_NOT_RECONFIGURABLE,
    /*DEM Id for FlexRay Slot Status Error. */
    FR_17_ERAY_DEM_REPORT_DISABLED
  },
  /* -------------------------  LPDU 3 ------------------------------- */
  {
    /*
    6U - Slot ID
    3U - Cycle code
    1U,- FrPChannels , add 0x1 as the hw regs take ChannelA = 1, ChannelB = 2
    and ChannelAB = 3
    0U - Message Buffer Direction: 0 - Receive, 1 - Transmit
    0U, - PPIT: 0 - Disable, 1 - Enable
    1U, - Transmission Mode : 1 - Single shot - always single shot
    0U  - Message Buffer Service Request - always set to 0
    */
    0x11030006U,
    /*
    0x0U - Header CRC
    2U - Payload Length Configured
    0U - FrIfAllowDynamicLSduLength
    */
    0x00020000U,
    FR_17_ERAY_LPDU_NOT_RECONFIGURABLE,
    /*DEM Id for FlexRay Slot Status Error. */
    FR_17_ERAY_DEM_REPORT_DISABLED
  },
  /* -------------------------  LPDU 4 ------------------------------- */
  {
    /*
    13U - Slot ID
    2U - Cycle code
    2U,- FrPChannels , add 0x1 as the hw regs take ChannelA = 1, ChannelB = 2
    and ChannelAB = 3
    1U - Message Buffer Direction: 0 - Receive, 1 - Transmit
    1U, - PPIT: 0 - Disable, 1 - Enable
    1U, - Transmission Mode : 1 - Single shot - always single shot
    0U  - Message Buffer Service Request - always set to 0
    */
    0x1e02000dU,
    /*
    0x26cU - Header CRC
    2U - Payload Length Configured
    0U - FrIfAllowDynamicLSduLength
    */
    0x0002026cU,
    FR_17_ERAY_LPDU_RECONFIGURABLE,
    /*DEM Id for FlexRay Slot Status Error. */
    FR_17_ERAY_DEM_REPORT_DISABLED
  },
  /* -------------------------  LPDU 5 ------------------------------- */
  {
    /*
    13U - Slot ID
    3U - Cycle code
    1U,- FrPChannels , add 0x1 as the hw regs take ChannelA = 1, ChannelB = 2
    and ChannelAB = 3
    0U - Message Buffer Direction: 0 - Receive, 1 - Transmit
    0U, - PPIT: 0 - Disable, 1 - Enable
    1U, - Transmission Mode : 1 - Single shot - always single shot
    0U  - Message Buffer Service Request - always set to 0
    */
    0x1103000dU,
    /*
    0x0U - Header CRC
    2U - Payload Length Configured
    0U - FrIfAllowDynamicLSduLength
    */
    0x00020000U,
    FR_17_ERAY_LPDU_RECONFIGURABLE,
    /*DEM Id for FlexRay Slot Status Error. */
    FR_17_ERAY_DEM_REPORT_DISABLED
  }
};

/***** Communication controller configuration Controller 0  *****/
/* MISRA2012_RULE_5_1_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
static const Fr_17_Eray_CCConfigType Fr_17_Eray_FrMultipleConfiguration_kCCCfg_0 =
{
  /* SUCC1 register configuration */
  /*
  0U - CmdPOCBusy (Unused member)
    1U - pKeySlotUsedForStartup
    1U - pKeySlotUsedForSync
  0U - Reserved bit
  0x1fU - FrIfGColdStartAttempts
  7U - FrPAllowPassiveToActive
  0U - FrPWakeupChannel
    0U - FrPKeySlotOnlyEnabled in FlexRay Protocol 2.1 Rev. A
    1U - FrPAllowHaltDueToClock
  0U - pChannelsMTS (Unused), 0 means no channels selected
  3U- FrPChannels, add 0x1 as the hw regs take ChannelA = 1, ChannelB = 2 and ChannelAB = 3
  */
  0x0c87fb00U,
  /* SUCC2 register settings */
  /*
  0x13972U - FrPdListenTimeout
  0xfU - (FrIfGListenNoise - 1)
  */
  0x0f013972U,
  /* SUCC3 register settings */
  /*
  0x1U - FrIfGMaxWithoutClockCorrectPassive
  0x1U - FrIfGMaxWithoutClockCorrectFatal
  */
  0x00000011U,
  /* NEMC register settings */
  /*
  0x2U - FrIfGNetworkManagementVectorLength
  */
  0x00000002U,
  /* PRTC1 register settings */
  /*
  0xaU - FrIfGdTSSTransmitter
  0x61U - FrIfGdCasRxLowMax
  0U - Strobe Point Position. Always zero (default)
  0U - BRP. Always zero as driver supports only 10Mbps rate
  0x8cU - FrIfgdWakeupRxWindow
  0x2U - FrPWakeupPattern
  */
  0x088c061aU,
  /* PRTC2 register settings */
  /*
  0x2dU - FrIfgdWakeupRxIdle
  0x12U - FrIfgdWakeupRxLow
  0x2dU - FrIfGdWakeupTxIdle
  0x12U - FrIfGdWakeupTxActive
  */
  0x122d122dU,
  /* MHDC register settings */
  /*
  0x4U - FrIfGPayloadLengthStatic
  0x3fU - FrPLatestTx
  */
  0x003f0004U,
  /* GTUC01 register settings */
  /*
  0x9c40U - UT: FrPMicroPerCycle
  */
  0x00009c40U,
  /* GTUC02 register settings */
  /*
  0x3e8U - FrIfGMacroPerCycle
  0x4U - FrIfGSyncFrameIDCountMax maps to FrIfGSyncNodeMax FR Pr 2.1
  */
  0x000403e8U,
  /* GTUC03 register settings */
  /*
  0x19U - FrPMicroInitialOffsetA [A]
  0x19U - FrPMicroInitialOffsetB [B]
  0xaU - FrPMacroInitialOffsetA [A]
  0x2U - FrPMacroInitialOffsetB [B]
  */
  0x020a1919U,
  /* GTUC04 register settings */
  /*
  0x38eU- NetworkIdleTimeStart = (FrIfGMacroPerCycle - FrIfGdNit - 1)
  0x393U- Range: 8 -15998, maps to (FrPOffsetCorrectionStart - 1)
  */
  0x0393038eU,
  /* GTUC05 register settings */
  /*
  0x4U - FrPDelayCompensationA
  0x4U - FrPDelayCompensationB
  0x1U - FrPClusterDriftDamping
  0x34U - FrPDecodingCorrection
  */
  0x34010404U,
  /* GTUC06 register settings */
  /*
  0x81U - FrPdAcceptedStartupRange
  0xd2U - is same as FrPdMaxDrift
  */
  0x00d20081U,
  /* GTUC07 register settings */
  /*
  0x32U - FrIfGdStaticSlot
  0xc - FrIfGNumberOfStaticSlots
  */
  0x000c0032U,
  /* GTUC08 register settings */
  /*
  0x4U - FrIfGdMinislot
  0x4bU - FrIfGNumberOfMinislots
  */
  0x004b0004U,
  /* GTUC09 register settings */
  /*
  0x8U - FrIfgdActionPointOffset
  0x3U - FrIfgdMinislotActionPointOffset
  0x1U - FrIfgdDynamicSlotIdlePhase
  */
  0x00010308U,
  /* GTUC10 register settings */
  /*
  0x32U - FrPOffsetCorrectionOut
  0xd2U - FrPRateCorrectionOut
  */
  0x00d20032U,
  /* GTUC11 register settings */
  /*
  0x0000U - Unused (FrPExternOffsetControl, FrPExternRateControl
  0U - FrPExternOffsetCorrection is not present in AS40
  0U - FrPExternRateCorrection is not present in AS40
  */
  0x00000000U,
  /* CUST1 register settings */
  /*
  0x00U - Unused
  0x00U - Reserved
  FR_RXSEL0_PORT14_8 - FrRxInputSelection Channel A
  FR_RXSEL0_PORT14_7 - FrRxInputSelection Channel B
  0x00U - Unused
  */
  0x00000000U
};


/* MISRA2012_RULE_5_1_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
static const uint32 Fr_17_Eray_FrMultipleConfiguration_CCConfigArray_0[63] =
{
  0x000f4240U,  /* FrIfGdCycle */
  0x00009c40U, /* UT: FrPMicroPerCycle */
  0x00013972U, /* FrPdListenTimeout */
  0x000003e8U, /* FrIfGMacroPerCycle */
  0x000003e8U,  /* FrIfGdMacrotick */
  0x0000004bU, /* FrIfGNumberOfMinislots */
  0x0000000cU, /* FrIfGNumberOfStaticSlots */
  0x00000059U,  /* FrIfGdNit */
  0x00000032U, /* FrIfGdStaticSlot */
  0x0000008cU, /* FrIfgdWakeupRxWindow */
  0x00000003U, /* FrPKeySlotId */
  0x0000003fU, /* FrPLatestTx */
  0x00000032U, /* FrPOffsetCorrectionOut */
  0x00000394U, /* FrPOffsetCorrectionStart */
  0x000000d2U, /* FrPRateCorrectionOut */
  0x00000000U,  /* Second Keyslot ID */
  0x00000081U, /* FrPdAcceptedStartupRange */
  0x0000001fU, /* FrIfGColdStartAttempts */
  0x0000003fU,  /* FrIfGCycleCountMax */
  0x00000010U, /*FrIfGListenNoise */
  0x00000001U, /* FrIfGMaxWithoutClockCorrectFatal */
  0x00000001U, /* FrIfGMaxWithoutClockCorrectPassive */
  0x00000002U, /* FrIfGNetworkManagementVectorLength */
  0x00000004U, /* FrIfGPayloadLengthStatic */
  0x00000004U, /* FrIfGSyncFrameIDCountMax maps to FrIfGSyncNodeMax FR Pr 2.1 */
  0x00000008U, /* FrIfgdActionPointOffset */
  0x00000000U, /* FrIfGdBit */
  0x00000061U, /* FrIfGdCasRxLowMax */
  0x00000001U, /* FrIfgdDynamicSlotIdlePhase */
  0x00000003U, /* FrIfgdMinislotActionPointOffset */
  0x00000004U, /* FrIfGdMinislot */
  0x00000000U, /*  0 - T12_5NS -> 10 Mbps */
  0x00000000U,  /* FrIfGdSymbolWindow */
  0x00000008U, /* FrIfgdActionPointOffset */
  0x0000000aU, /* FrIfGdTSSTransmitter */
  0x0000002dU, /* FrIfgdWakeupRxIdle */
  0x00000012U, /* FrIfgdWakeupRxLow */
  0x00000012U, /* FrIfGdWakeupTxActive */
  0x0000002dU, /* FrIfGdWakeupTxIdle */
  0x00000007U, /* FrPAllowPassiveToActive */
  0x00000002U,/* FrPChannels */
  0x00000001U, /* FrPClusterDriftDamping */
  0x00000034U, /* FrPDecodingCorrection */
  0x00000004U, /* FrPDelayCompensationA */
  0x00000004U, /* FrPDelayCompensationB */
  0x0000000aU, /* FrPMacroInitialOffsetA */
  0x00000002U, /* FrPMacroInitialOffsetB */
  0x00000019U, /* FrPMicroInitialOffsetA */
  0x00000019U, /* FrPMicroInitialOffsetB */
  0x0000007fU, /* FrPPayloadLengthDynMax */
  0x00000001U, /* 1 - N2SAMPLES - Fixed at N2 samples as the baudrate supported is 10Mbit/s */
  0x00000000U, /* FrPWakeupChannel ->  0 - FR_CHANNEL_A */
  0x00000002U, /* FrPWakeupPattern */
  0x00000001U, /* FrPdMicrotick -> 1 - T25NS */
  0x00000000U, /* FrIfGdIgnoreAfterTx - Set to 0 for FR Pr 2.1 */
  0x00000001U, /* FrPAllowHaltDueToClock */
  0x00000000U, /* FrPExternalSync - Set to 0 for FR Pr 2.1 */
  0x00000000U, /* FrPFallBackInternal - Set to 0 for FR Pr 2.1 */
  0x00000000U, /* FrPKeySlotOnlyEnabled */
  0x00000001U, /* FrPKeySlotUsedForStartup */
  0x00000001U, /* FrPKeySlotUsedForSync */
  0x00000000U, /* FrPNmVectorEarlyUpdate - Set to 0 for FR Pr 2.1 */
  0x00000000U  /* FrPTwoKeySlotMode - Set to 0 for FR Pr 2.1 */
};




/* MISRA2012_RULE_5_1_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
static const Fr_17_Eray_CCType Fr_17_Eray_FrMultipleConfiguration_CC[] =
{
  {
    /* Pointer to configuration of Communication Controller */
    &Fr_17_Eray_FrMultipleConfiguration_kCCCfg_0,
    
    /* Pointer to array of LPDU configurations */
    Fr_17_Eray_FrMultipleConfiguration_kLPduConfig_0,
    
    #if (FR_17_ERAY_FIFO_CONFIGURED == STD_ON)
    NULL_PTR,
    #endif
    
    /* Pointer to array of FR parameters accessed by Fr_ReadCCConfig */
    Fr_17_Eray_FrMultipleConfiguration_CCConfigArray_0,
    
    /* Pointer to LPDU to message buffer mapping array */
    Fr_17_Eray_FrMultipleConfiguration_LPduIdx2MsgBuff_0,
    
    /* Pointer to Data pointer offsets */
    Fr_17_Eray_FrMultipleConfiguration_DataPointerOffset_0,
    
    /* Number of LPDUs configured */
    6U,
    
    /* ERAY Module clock configuration : Runtime Mode Control setting */
    1U,
    
    /* Buffer Reconfiguration Status */
    0U,
    
    /*DEM Id for FlexRay controller hardware test failure.*/
    DemConf_DemEventParameter_FR_CTRL_TESTRESULT_ERROR,
    
    /* Number of HW message buffers required */
    6U
  }
};

/* MISRA2012_RULE_5_1_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
static const uint8 Fr_17_Eray_FrMultipleConfiguration_CCMap[FR_17_ERAY_NUM_CONTROLLERS_IN_DEVICE] =
{
  0U,
  255U
};


/* Implementation-specific post build configuration for FlexRay driver */
const Fr_17_Eray_ConfigType Fr_17_Eray_Config =
{
  &Fr_17_Eray_FrMultipleConfiguration_CC[0],
  &Fr_17_Eray_FrMultipleConfiguration_CCMap[0]

};

#define FR_17_ERAY_STOP_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code.
Variable declared before MemMap header file */
#include "Fr_17_Eray_MemMap.h"
