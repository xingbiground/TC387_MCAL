/*****************************************************************************
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
**  FILENAME  : Dsadc_PBcfg.c                                                 **
**                                                                            **
**  VERSION   : 8.0.0                                                         **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:35            !!!IGNORE-LINE!!!             **
**                                                                            **
**  GENERATOR : Build b191017-0938              !!!IGNORE-LINE!!!             **
**                                                                            **
**  BSW MODULE DECRIPTION : Dsadc.bmd                                         **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION :  Dsadc configuration generated out of ECUC file             **
**                                                                            **
**  SPECIFICATION(S) : Specification of DSADC Driver                          **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                            Includes                                        **
*******************************************************************************/
/* Include module header file */
/* [cover parentID={C7D5952A-E79A-496d-A6D8-22C1661986B6}] */
#include "Dsadc.h"



#define DSADC_START_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Dsadc_MemMap.h"
/*Function declaration for Buffer full Notification for DSADC Channel Id 0*/
extern void TestDsAdc_BufferFullNotification(void);
/*Function declaration for New Result Notification for DSADC Channel Id 0*/
extern void TestDsAdc_NewResultNotification(void);




/*DSADC channels configurations*/
static const Dsadc_ChannelConfigType Dsadc_kChannelConfiguration  [DSADC_MAX_CHANNELS_CONFIGURED] =
{
  /*Configuration of DSADC Channel Id 0*/
  {
    /*Address for the OGU trigger configuration structure*/
    NULL_PTR,
    /* Modulator Configuration Register */
    0x80008000U,
    /* Common Mode Voltage Configuration Register */
    0x00000000U,
    /* Demodulator Configuration Register */
    0x84008000U,
    /* Filter Configuration Register */
    0x80008008U,
    /* CIC Filter Configuration Register */
    0x01ff01ffU,
    /* AUX CIC Filter Configuration Register */
    0x00000000U,
    /* Timestamp counter Register */
    0x00000000U,
    /* Integrator Window Control Register */
    0x00000000U,
    /* Result FIFO Control Register */
    0x00000000U,
    /* Offset Compensation Register */
    0x00000000U,
    /* Gain Calibration Register */
    0x61a81170U,
    /* Gain Control Register */
    0x061b1170U,
    /* Gain Correction Register */
    0x001b1170U,
    /* Limit Checking boundary configuration Register */
    0x00000000U,
    /* Overshoot compensation configuration Register */
    0x00000000U,
    /* Carrier Generator Synchronization Register */
    0x00000000U,
    /* Rectification Configuration Register */
    0x00000000U,
    /* DSADC Channel number */
    0x00U,
    /* DSADC Channel Access Mode */
    DSADC_STREAM_LINEAR_BUFFER,
    /* DSADC Timestamp*/
    DSADC_TIMESTAMP_DISABLED,
    /* DSADC TimestampTriggerMode*/
    DSADC_NO_TIMESTAMP_TRIGGER,
    /* DSADC Channel Trigger Mode */
    DSADC_TRIGGER_MODE_NORMAL,
    /* DSADC Channel Trigger Source */
    DSADC_TRIGGER_NONE,
    /* DSADC Channel DsadcGateActiveLevel */
    DSADC_GATE_HIGH_LEVEL,
    /* DSADC Channel Interrupt Mode*/
    0x03U,
    /* DSADC Buffer Full Notification */
    TestDsAdc_BufferFullNotification,
    /* DSADC New Result Notification */
    TestDsAdc_NewResultNotification,
    /* DSADC Window Close Notification  */
    NULL_PTR
  }
};

/* Configuration Root for DsadcConfigSet*/


const Dsadc_ConfigType Dsadc_Config =
{
  /* pointer to DSDAC channel configuration */
  &Dsadc_kChannelConfiguration[0],
  /* pointer to ERU input channel configuration */
      NULL_PTR,
  /* Contents of DSADC Clock control register, CLC */
  0x00000000U,
  /* Contents DSADC Global configuration register GLOBCFG */
  0x00009000U,
  /* Contents DSADC Carrier generator configuration register CGCFG */
  0x00000000U,
  /*Carrier Generator Waveform*/
  DSADC_CARR_SIG_STOPPED
};

#define DSADC_STOP_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration of notification function
  before MemMap inclusion It complies to Autosar guidelines. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Dsadc_MemMap.h"

