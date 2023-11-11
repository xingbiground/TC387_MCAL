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
**  FILENAME     : CanTrcv_17_V9251.c                                         **
**                                                                            **
**  VERSION      : 14.0.0                                                     **
**                                                                            **
**  DATE         : 2022-06-28                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID={80494498-4278-4044-8E6A-7489AC699809}]    **
**                                                                            **
**  DESCRIPTION  : CanTrcv Driver source file                                 **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of CanTrcv Driver,AUTOSAR Release 4.2.2  **
**                                                  and AUTOSAR Release 4.4.0 **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* CanTrcv_17_V9251.h contains prototype of CanTrcv_17_V9251 module */
#include "CanTrcv_17_V9251.h"
/* CanIf.h contains prototype of CAN Interface function */
/* [cover parentID={F4373030-2F40-4d6e-A181-07DBFAF5C998}]
   [/cover] */
#include "CanIf.h"
#if (MCAL_AR_VERSION == MCAL_AR_440)
    /* CanIf_CanTrcv.h contains prototype of CAN Interface callback function */
    #include "CanIf_CanTrcv.h"
#endif
/* MCAL header file containing global macros, type definitions and functions
  needed by all MCAL drivers. */
#include "McalLib.h"
/* Enable / Disable DET checking */
#if (CANTRCV_17_V9251_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif
/*(CANTRCV_17_V9251_DEV_ERROR_DETECT == STD_ON) */
/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/
/* Check if the correct version of CanTrcv_17_V9251.h is included */
/* [cover parentID={8C7B7037-E443-4b9d-99F4-06DD4A384745}]
     [/cover] */
#ifndef CANTRCV_17_V9251_AR_RELEASE_MAJOR_VERSION
#error "CANTRCV_17_V9251_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

/* Check for consistent AUTOSAR version between generated code and static code
using macro published by MCALLIB */
/* [cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}]
     [/cover] */
#if (CANTRCV_17_V9251_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION)
#error "CANTRCV_17_V9251_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

/* Check for definition of SW version Information */
/* [cover parentID={8C7B7037-E443-4b9d-99F4-06DD4A384745}]
     [/cover] */
#ifndef CANTRCV_17_V9251_SW_MAJOR_VERSION
#error "CANTRCV_17_V9251_SW_MAJOR_VERSION is not defined. "
#endif

#ifndef CANTRCV_17_V9251_SW_MINOR_VERSION
#error "CANTRCV_17_V9251_SW_MINOR_VERSION is not defined. "
#endif

#ifndef CANTRCV_17_V9251_SW_PATCH_VERSION
#error "CANTRCV_17_V9251_SW_PATCH_VERSION is not defined. "
#endif

/* Check for Correct inclusion of headers */
/* [cover parentID={D16E1089-3609-460f-8F87-FDA0410D040D}]
     [/cover] */
#if ( CANTRCV_17_V9251_SW_MAJOR_VERSION != 20U )
#error "CANTRCV_17_V9251_SW_MAJOR_VERSION does not match. "
#endif

#if ( CANTRCV_17_V9251_SW_MINOR_VERSION != 20U )
#error "CANTRCV_17_V9251_SW_MINOR_VERSION does not match. "
#endif

#if ( CANTRCV_17_V9251_SW_PATCH_VERSION != 0U )
#error "CANTRCV_17_V9251_SW_PATCH_VERSION does not match. "
#endif

/* Inter Module Checks to avoid integration of incompatible files
  VERSION CHECK FOR DET MODULE INCLUSION */
/* [cover parentID={8C7B7037-E443-4b9d-99F4-06DD4A384745}]
   [/cover] */
#if (CANTRCV_17_V9251_DEV_ERROR_DETECT == STD_ON)

#ifndef DET_AR_RELEASE_MAJOR_VERSION
#error "DET_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

/* Check for consistent AUTOSAR version between generated code and static
  code using macro published by MCALLIB */
/* [cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}]
     [/cover] */
#if ( DET_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION )
#error "DET_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

#endif
/* End Of CANTRCV_17_V9251_DEV_ERROR_DETECT */

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
/* CAN Transceiver Driver states. */

/* CAN Transceiver Driver is NOT initialized. */
/* MISRA2012_RULE_2_5_JUSTIFICATION: This Macro is used when configuartion has
DET enabled*/
#define  CANTRCV_17_V9251_UNINIT                          ((uint8)0)

/* CAN Transceiver Driver is initialized. */
/* MISRA2012_RULE_2_5_JUSTIFICATION: This Macro is used when configuartion has
DET enabled*/
#define  CANTRCV_17_V9251_INIT                            ((uint8)1)

/* CAN Transceiver macro to clear */
#define CANTRCV_17_V9251_CHANNEL_ZERO                     ((uint8)(0U))

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/
/*
Type: CanTrcv_17_V9251_ChannelStatusType
[cover parentID={7DB68B0F-61DB-451a-9591-0D0A20EAAC1C}][/cover]
*/
typedef struct
{

  /* Global Variable to update Current Mode of CanTrcv */
  CanTrcv_TrcvModeType
  Cantrcv_17_V9251_CurrentMode[CANTRCV_17_V9251_CHANNELS_CFG];

  /* Global Variable holds the wake up mode */
  CanTrcv_TrcvWakeupModeType
  CanTrcv_17_V9251_WakeupMode[CANTRCV_17_V9251_CHANNELS_CFG];

  /* Global Variable to Update WakeUp Reason */
  CanTrcv_TrcvWakeupReasonType
  Cantrcv_17_V9251_WuReason[CANTRCV_17_V9251_CHANNELS_CFG];

} CanTrcv_17_V9251_ChannelStatusType;


/*******************************************************************************
**                      Imported Global Constant Declaration                  **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
#define CANTRCV_17_V9251_START_SEC_CODE_QM_LOCAL
/* [cover parentID={DC0F3BD1-1815-492a-8B3D-D19A2DBC37C6}]
    MemMap file  [/cover] */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
    MemMap file  [/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
    MemMap file  [/cover] */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_V9251_MemMap.h"

#if (CANTRCV_17_V9251_DEV_ERROR_DETECT == STD_ON)
static Std_ReturnType CanTrcv_17_V9251_lCheckUninitDet(const uint8 ServiceId);
static Std_ReturnType
CanTrcv_17_V9251_lChannelIdDet(const uint8 Channel, const uint8 ServiceId);
#endif
static void CanTrcv_17_V9251_lSetInitMode(const uint8 Channel);
static void CanTrcv_17_V9251_ldelay(void);
LOCAL_INLINE uint16 CanTrcv_17_V9251_lGetPendWu(const uint8 Channel);
LOCAL_INLINE void CanTrcv_17_V9251_lSetPendWu(const uint8 Channel);
LOCAL_INLINE void CanTrcv_17_V9251_lClearPendWu(const uint8 Channel);

#define CANTRCV_17_V9251_STOP_SEC_CODE_QM_LOCAL
/* [cover parentID={DC0F3BD1-1815-492a-8B3D-D19A2DBC37C6}]
    MemMap file  [/cover] */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
    MemMap file  [/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
    MemMap file  [/cover] */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_V9251_MemMap.h"
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_V9251_START_SEC_VAR_CLEARED_QM_LOCAL_UNSPECIFIED
/* [cover parentID={DC0F3BD1-1815-492a-8B3D-D19A2DBC37C6}]
    MemMap file  [/cover] */
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
    MemMap for variables  [/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
    MemMap file  [/cover] */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_V9251_MemMap.h"

/* Global structure to hold CanTrcv channel status */
/* [cover parentID={977D09E3-A27E-4ed4-8D47-3FE07AACFB8C}]
      CAN transceiver States [/cover] */
static CanTrcv_17_V9251_ChannelStatusType CanTrcv_17_V9251_Channelstatus;

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_V9251_STOP_SEC_VAR_CLEARED_QM_LOCAL_UNSPECIFIED
/* [cover parentID={DC0F3BD1-1815-492a-8B3D-D19A2DBC37C6}]
    MemMap file  [/cover] */
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
    MemMap for variables  [/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
    MemMap file  [/cover] */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_V9251_MemMap.h"
#if (CANTRCV_17_V9251_DEV_ERROR_DETECT == STD_ON)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_V9251_START_SEC_VAR_CLEARED_QM_LOCAL_8
/* [cover parentID={DC0F3BD1-1815-492a-8B3D-D19A2DBC37C6}]
    MemMap file  [/cover] */
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
    MemMap for variables  [/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
    MemMap file  [/cover] */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_V9251_MemMap.h"

/* CanTrcv hardware initialization state */
static uint8 CanTrcv_17_V9251_DriverState;

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_V9251_STOP_SEC_VAR_CLEARED_QM_LOCAL_8
/* [cover parentID={DC0F3BD1-1815-492a-8B3D-D19A2DBC37C6}]
    MemMap file  [/cover] */
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
    MemMap for variables  [/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
    MemMap file  [/cover] */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_V9251_MemMap.h"
#endif
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_V9251_START_SEC_VAR_CLEARED_QM_LOCAL_16
/* [cover parentID={DC0F3BD1-1815-492a-8B3D-D19A2DBC37C6}]
    MemMap file  [/cover] */
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
    MemMap for variables  [/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
    MemMap file  [/cover] */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_V9251_MemMap.h"
/* Set or Clear the pending notification */

static uint16 CanTrcv_17_V9251_PendWakeup;

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_V9251_STOP_SEC_VAR_CLEARED_QM_LOCAL_16
/* [cover parentID={DC0F3BD1-1815-492a-8B3D-D19A2DBC37C6}]
    MemMap file  [/cover] */
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
    MemMap for variables  [/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
    MemMap file  [/cover] */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_V9251_MemMap.h"
/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define CANTRCV_17_V9251_START_SEC_CODE_QM_LOCAL
/* [cover parentID={DC0F3BD1-1815-492a-8B3D-D19A2DBC37C6}]
    MemMap file  [/cover] */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
    MemMap file  [/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
    MemMap file  [/cover] */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_V9251_MemMap.h"
/*******************************************************************************
** Traceability      :[cover parentID={7382D53F-BD6B-49b3-BAA3-ED7F07565D49}] **
**                                                                            **
**                                                                            **
** Syntax            : void CanTrcv_17_V9251_Init                             **
**                                  (const CanTrcv_ConfigType* ConfigPtr)     **
**                                                                            **
**                                                                            **
** Description       : This API initializes the CanTrcv_17_V9251 module by    **
**                     setting CAN transceiver hardware to the mode           **
**                     configured by the configuration parameter              **
**                     CanTrcvInitState.                                      **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        :  0x00                                                  **
**                                                                            **
** Sync/Async        :  Synchronous                                           **
**                                                                            **
** Reentrancy        :  non reentrant                                         **
**                                                                            **
** Parameters (in)   :  ConfigPtr - Pointer to driver configuration.          **
**                                                                            **
**                      Note: Since CanTrcv_17_V9251 module is pre-compile    **
**                      module, NULL_PTR must be passed as the parameter for  **
**                      CanTrcv_17_V9251_Init API.                            **
**                                                                            **
** Parameters (out)  :  none                                                  **
**                                                                            **
** Return value      :  none                                                  **
**                                                                            **
*******************************************************************************/
void CanTrcv_17_V9251_Init(const CanTrcv_17_V9251_ConfigType* const ConfigPtr)
{
  /* channel index counter */
  uint8 TrcvIdx = CANTRCV_17_V9251_CHANNEL_ZERO;

  #if (CANTRCV_17_V9251_DEV_ERROR_DETECT == STD_ON)
  /* CanTrcv hardware is not Initialized */
  /* Status as not initialized */
  /* [cover parentID={4C709C94-9548-405d-A50F-4D4690FD501F}]
     [/cover] */
  CanTrcv_17_V9251_DriverState = CANTRCV_17_V9251_UNINIT;
  /* check if ConfigPtr passed is NULL_PTR */
  /* [cover parentID={5CA1C137-4701-42a4-BA7A-0D6BE46F7FD9}]
     [/cover] */
  if (NULL_PTR == ConfigPtr)
  {
  #endif /* End of (CANTRCV_17_V9251_DEV_ERROR_DETECT == STD_ON) */
     /*Loop for all configured channels */
    /* [cover parentID={AD5CB9A5-1440-4f6c-9C9F-09A9A68DE71E}]
    Loop for all configured channels  [/cover] */
    while(TrcvIdx < CANTRCV_17_V9251_CHANNELS_USED)
    {
    /* Update the CanTrcv hardware to Configured mode for all channel */
    CanTrcv_17_V9251_lSetInitMode(TrcvIdx);
    /* increment the channel Id */
    TrcvIdx++;
    }
    #if (CANTRCV_17_V9251_DEV_ERROR_DETECT == STD_ON)
    /* CanTrcv hardware is Initialized */
    /* [cover parentID={B2F93415-C556-4f45-81C6-CEB7DEEE59F4}]
       CanTrcv hardware is Initialized  [/cover] */
    CanTrcv_17_V9251_DriverState = CANTRCV_17_V9251_INIT;
    #endif

    #if (CANTRCV_17_V9251_DEV_ERROR_DETECT == STD_OFF)
    /* ConfigPtr is not using as CanTrcv is Pre-Compile Module */
    UNUSED_PARAMETER(ConfigPtr);
    #endif
  #if (CANTRCV_17_V9251_DEV_ERROR_DETECT == STD_ON)
  }
  else
  {
    /* [cover parentID={C2401F8E-4A7E-4a74-BA71-3F1FB1AF3049}]
     Report to DET [/cover] */
    (void)Det_ReportError(
      CANTRCV_17_V9251_MODULE_ID,
      CANTRCV_17_V9251_INSTANCE_ID,
      CANTRCV_17_V9251_SID_INIT,
      CANTRCV_17_V9251_E_INIT_FAILED
    );
  }
  #endif /* End of (CANTRCV_17_V9251_DEV_ERROR_DETECT == STD_ON) */
}
/*******************************************************************************
** Traceability     :[cover parentID={13661675-1775-40a2-9115-279CC8AEF4AF}]  **
**                                                                            **
**                                                                            **
** Syntax           : Std_ReturnType CanTrcv_17_V9251_SetOpMode               **
**                     (const uint8 Transceiver, const CanTrcv_TrcvModeType   **
**                                                                   OpMode)  **
**                                                                            **
**                                                                            **
** Description      : This API sets the mode of the CAN transceiver given     **
**                                                      the value OpMode.     **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x01                                                    **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant for different transceiver.                    **
**                                                                            **
** Parameters (in)  : Transceiver -CAN Transceiver to which API call has      **
**                                 to be applied.                             **
**                    OpMode - This parameter contains the desired operating  **
**                                                                    mode.   **
**                                                                            **
** Parameters (out) :  none                                                   **
**                                                                            **
** Return value     :  E_OK: CAN Transceiver state have been changed to       **
**                           requested mode.                                  **
**                     E_NOT_OK: CAN Transceiver state change failed or the   **
**                               parameter is out of the allowed range.       **
**                                                                            **
*******************************************************************************/
Std_ReturnType CanTrcv_17_V9251_SetOpMode(const uint8 Transceiver,
    const CanTrcv_TrcvModeType OpMode)
{

  /* STB Dio channel variable */
  Dio_ChannelType TrcvDioChannel;
  /* Channel Index variable */
  uint8 ChannelIndex = 0;
  /* return Status variable */
  Std_ReturnType ReturnValue = E_NOT_OK;
  /* CanTrcv Current mode variable */
  CanTrcv_TrcvModeType CurrentMode;

  /* DET is OFF */
  /* [cover parentID= {EC95AE47-0BCA-4afa-8CFC-4F545ED93884}]
  [/cover] */
  #if (CANTRCV_17_V9251_DEV_ERROR_DETECT == STD_OFF)
  ReturnValue = E_OK;
  #endif

  /*  If DET is enable */
  /* [cover parentID={953919D1-5922-4465-8AC2-F138BF97128E}]
  [/cover] */
  #if (CANTRCV_17_V9251_DEV_ERROR_DETECT == STD_ON)
  /*  Is CanTrcv module has been initialized */
  /* [cover parentID={A00DDCB4-E4B8-4058-84F9-E4A7C2BED777}]
      [/cover] */
  /* [cover parentID={195DF18D-497A-4a3d-96DD-822275CA7867}]
     [/cover] */
  ReturnValue =
        CanTrcv_17_V9251_lCheckUninitDet(CANTRCV_17_V9251_SID_SETOPMODE);

  /*  If no DET Error */
  /* [cover parentID={16E1227F-8972-44c8-9069-6A57ADE577B8}]
     [/cover] */
  if (ReturnValue == E_OK)
  {
    /* Is Channel Index valid */
    /* [cover parentID={5C11DD6F-82CA-4a29-8731-4F1B6F710357}]
      [/cover] */
    /* [cover parentID={195DF18D-497A-4a3d-96DD-822275CA7867}]
      [/cover] */
    ReturnValue = CanTrcv_17_V9251_lChannelIdDet(Transceiver,
                  CANTRCV_17_V9251_SID_SETOPMODE);
  }

  /*  If no DET Error */
  /* [cover parentID={7902BD8B-A7F9-4e33-8021-D3248C5F660D}]
       [/cover] */
  if (ReturnValue == E_OK)
  #endif
  {
    /* If OpMode valid */
    /* [cover parentID={D25B4391-E617-4889-8F2E-BFA62EA5DCE6}]
         [/cover] */
    if ((OpMode == CANTRCV_TRCVMODE_NORMAL) ||
        (OpMode == CANTRCV_TRCVMODE_STANDBY))
    {
        /* Valid Mode */
    }
    else
    {
      #if (CANTRCV_17_V9251_DEV_ERROR_DETECT == STD_ON)
      /* Report if invalid OpMode */
      /* [cover parentID={2D7F4232-9BB4-4237-97FD-3BEDC81749D5}]
         [/cover] */
      (void)Det_ReportError(
        CANTRCV_17_V9251_MODULE_ID,
        CANTRCV_17_V9251_INSTANCE_ID,
        CANTRCV_17_V9251_SID_SETOPMODE,
        CANTRCV_17_V9251_E_PARAM_TRCV_OPMODE
      );
      #endif
      /* [cover parentID={195DF18D-497A-4a3d-96DD-822275CA7867}]
      [/cover] */
      ReturnValue = E_NOT_OK;
    }

  }
  /*  If DET Error and OpMode is Invalid */
  /* [cover parentID={D25B4391-E617-4889-8F2E-BFA62EA5DCE6}]
     [/cover] */
  if (ReturnValue == E_OK)
  {
    /* Get the Channel Id */
    ChannelIndex = CanTrcv_17_V9251_ChannelUsed[Transceiver];
    /* Get the STB Pin Dio channel  */
    TrcvDioChannel =
    CanTrcv_17_V9251_ChannelConfig[ChannelIndex].CanTrcv_17_V9251_DioChannel;
    /* Get the channel mode */
    CurrentMode =
    CanTrcv_17_V9251_Channelstatus.Cantrcv_17_V9251_CurrentMode[Transceiver];

    /* If current mode is same as OpMode  */
    /* [cover parentID={110DA67D-1DDA-4421-A53A-EBDC336420DF}]
    [/cover] */
    if (CurrentMode != OpMode)
    {
      /* If Normal Mode  */
      /* [cover parentID={A49E0BDF-48C1-484c-9080-2D6D7B0C695E}]
          If Normal Mode  [/cover] */
      if (OpMode == CANTRCV_TRCVMODE_NORMAL)
      {
        /* Set the CanTrcv hardware to Normal mode */
        /* [cover parentID={920BB52B-97E2-4ab9-B3EB-26D863F32DA1}]
             Set the CanTrcv hardware to Normal mode [/cover] */
        Dio_WriteChannel(TrcvDioChannel, (CANTRCV_17_V9251_NORMAL_MODE));

        /* Delay for Mode Transition to normal mode */
        CanTrcv_17_V9251_ldelay();

        /* Update Wake up reason as Wake up due to Internal */
        CanTrcv_17_V9251_Channelstatus.
        Cantrcv_17_V9251_WuReason[Transceiver] = CANTRCV_WU_INTERNALLY;

        /* Update the Current mode as Normal */
        /* [cover parentID={A34F5382-426F-4664-ADA8-30EBCACA46D1}]
             update current mode to Normal mode [/cover] */
      CanTrcv_17_V9251_Channelstatus.
      Cantrcv_17_V9251_CurrentMode[Transceiver] = CANTRCV_TRCVMODE_NORMAL;

      }  /*  end of( OpMode == CANTRCV_TRCVMODE_NORMAL) */

      else/* If StandBy Mode  */
      {
        /* Set the CanTrcv hardware to Standby mode  */
        /* [cover parentID={17626427-23B7-4f12-9FE1-77F0168B5B4B}]
          Put CanTrcv hardware to Stand by mode [/cover] */
        Dio_WriteChannel(TrcvDioChannel, (CANTRCV_17_V9251_STANDBY_MODE));

        /* Update the Current mode as Stand by */
        /* [cover parentID={E9F2B7F8-1447-4540-9CA5-EFA3D30F3D09}]
          Update the Current mode as Stand by [/cover] */
      CanTrcv_17_V9251_Channelstatus.
      Cantrcv_17_V9251_CurrentMode[Transceiver] = CANTRCV_TRCVMODE_STANDBY;
      }
    }
    /* [cover parentID={B33EC695-6974-40c3-843C-452C47D79F7E}]
        Indicate CANIF after each mode switch [/cover] */
      CanIf_TrcvModeIndication(Transceiver, OpMode);
  }

  return (ReturnValue);

} /* End of CanTrcv_SetOpMode function */

/*******************************************************************************
** Traceability     :[cover parentID={B2427119-128F-4e41-875C-8292B07147EC}]  **
**                                                                            **
**                                                                            **
** Syntax           : Std_ReturnType CanTrcv_17_V9251_GetOpMode               **
**                     (const uint8 Transceiver, CanTrcv_TrcvModeType* const  **
**                                                                   OpMode)  **
**                                                                            **
**                                                                            **
** Description      : This API reads the mode of the CAN transceiver and      **
**                                    returns it in the parameter OpMode.     **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x02                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different transceiver.                    **
**                                                                            **
** Parameters (in)  : Transceiver -CAN Transceiver to which API call has      **
**                                 to be applied.                             **
**                                                                            **
** Parameters (out) :  OpMode - Pointer to operation mode of the applied      **
**                              CAN transceiver.                              **
**                                                                            **
** Return value     :  E_OK : Operation mode read successfully.               **
**                     E_NOT_OK : Operation mode was not detected.            **
**                                                                            **
*******************************************************************************/
Std_ReturnType CanTrcv_17_V9251_GetOpMode(
  const uint8 Transceiver, CanTrcv_TrcvModeType* const OpMode)
{
  /* DET return variable */
  Std_ReturnType ReturnValue = E_NOT_OK;

  /* [cover parentID={6854525F-7CC8-477e-9830-D2C192A35BA6}]
     [/cover] */
  /* If DET is enable */
  #if (CANTRCV_17_V9251_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={0B51B7B9-ED5F-4cee-B92B-541BEAAFFBD6}]
     [/cover] */
  /* [cover parentID={6891F36B-3A21-473b-969F-5222B2402C9E}]
     [/cover] */
  /*  Is CanTrcv module has been initialized */
  ReturnValue =
  CanTrcv_17_V9251_lCheckUninitDet(CANTRCV_17_V9251_SID_GETOPMODE);

  /*  If no DET Error */
  /* [cover parentID={A383EE6C-4C4B-4ec6-B01F-B6565225B439}]
     If no DET Error [/cover] */
  if (ReturnValue == E_OK)
  {
    /* Is Channel Index valid */
    /* [cover parentID={8EDE3F4F-4B96-48a4-AD1B-D6BD504076DC}]
         [/cover] */
    /* [cover parentID={6891F36B-3A21-473b-969F-5222B2402C9E}]
      [/cover] */
    ReturnValue =
    CanTrcv_17_V9251_lChannelIdDet(Transceiver, CANTRCV_17_V9251_SID_GETOPMODE);
  }

  /*  If no DET Error */
  /* [cover parentID={B897276E-4BA0-416e-8BD7-0ACEFF0CF8F9}]
       If no DET Error [/cover] */
  if (ReturnValue == E_OK)
  {
    /* If called with OpMode as NULL_PTR */
    /* [cover parentID={A3990178-5F97-4acb-9BFE-E7B17612DFD8}]
        If called with OpMode as NULL_PTR [/cover] */
    if (OpMode == NULL_PTR)
    {
      /* If OpMode is not valid raise the DET */
      /* [cover parentID={B17BF7C6-CD20-4e73-9A58-2CBB5636FB99}]
         If called with OpMode as NULL_PTR report to DET [/cover] */
      (void)Det_ReportError(
        CANTRCV_17_V9251_MODULE_ID,
        CANTRCV_17_V9251_INSTANCE_ID,
        CANTRCV_17_V9251_SID_GETOPMODE,
        CANTRCV_17_V9251_E_PARAM_POINTER
      );
      /* [cover parentID={6891F36B-3A21-473b-969F-5222B2402C9E}]
        [/cover] */
      ReturnValue = E_NOT_OK ;
    }
  }
  /*  If no DET Error */
  /* [cover parentID={B17BF7C6-CD20-4e73-9A58-2CBB5636FB99}]
     [/cover] */
  if (ReturnValue == E_OK)
  #endif
    /* End of DET error switch */
  {
    /* Get the Current mode of CanTrcv channel */
    /* [cover parentID={1A0CA9F8-54FE-4177-A8C3-3AAC88D8C0BC}]
      [/cover] */
    *OpMode =
     CanTrcv_17_V9251_Channelstatus.Cantrcv_17_V9251_CurrentMode[Transceiver];
     ReturnValue = E_OK;
  }
  return (ReturnValue);

} /* End of CanTrcv_17_V9251_GetOpModeMode function */
/*******************************************************************************
** Traceability     : [cover parentID={8EF396C0-73AC-4baf-8B2F-EE6C65542899}] **
**                    [cover parentID={8070365C-26AF-40e7-9276-65FC95A6AE20}] **
**                                                                            **
**                                                                            **
** Syntax           : Std_ReturnType CanTrcv_17_V9251_GetBusWuReason          **
**                    (const uint8 Transceiver,CanTrcv_TrcvWakeupReasonType*  **
**                                                            const reason)   **
**                                                                            **
** Description      : This API reads the wakeup reason for the CAN            **
**                    transceiver and returns it in the parameter reason.     **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       :  0x03                                                   **
**                                                                            **
** Sync/Async       :  Synchronous                                            **
**                                                                            **
** Reentrancy       :  Reentrant for different transceivers.                  **
**                                                                            **
** Parameters (in)  :  Transceiver -CAN transceiver to which API call has     **
**                                  to be applied.                            **
**                                                                            **
** Parameters (out) :  reason - Pointer to wake up reason of the applied      **
**                              CAN transceiver.                              **
**                                                                            **
** Return value     :  E_OK: Transceiver wakeup reason was provided           **
**                           successfully.                                    **
**                     E_NOT_OK : If no wake up reason is available or if     **
**                                the service request failed due to           **
**                                development errors.                         **
**                                                                            **
*******************************************************************************/
Std_ReturnType CanTrcv_17_V9251_GetBusWuReason(
  const uint8 Transceiver, CanTrcv_TrcvWakeupReasonType* const reason)
{
  /* DET return variable */
  Std_ReturnType ReturnValue = E_NOT_OK;

  /* IF DET is enable */
  /* [cover parentID={8A065C66-27D2-45db-A8C3-9CDE523B0AED}]
    [/cover] */
  #if (CANTRCV_17_V9251_DEV_ERROR_DETECT == STD_ON)

  /*  Is CanTrcv module has been initialized */
  /* [cover parentID={3DFBD9CB-594B-49d4-9D30-8D4436086120}]
    [/cover] */
  /* [cover parentID={258D6AB9-6DA4-403d-90E5-D261CA64BB01}]
    [/cover] */
  ReturnValue =
  CanTrcv_17_V9251_lCheckUninitDet(CANTRCV_17_V9251_SID_GETBUSWUREASON);

  /* [cover parentID={7F736BBA-97C1-4967-8B6B-05C3AB5BD45D}]
     [/cover] */
  /*  If no DET Error */
  if (ReturnValue == E_OK)
  {
    /* Is Channel Index valid */
    /* [cover parentID={9DD99BED-DD87-49e9-B636-14FE24FC97FC}]
       [/cover] */
    /* [cover parentID={ECE42278-A1EF-443f-9D76-2996AEF9C74C}]
        For invalid Channel Index [/cover] */
    ReturnValue = CanTrcv_17_V9251_lChannelIdDet(Transceiver,
                  CANTRCV_17_V9251_SID_GETBUSWUREASON);
  }
  /*  If no DET Error */
  /* [cover parentID={497DEFE9-2292-4bc8-AD12-42D5B9273039}]
       [/cover] */
  if (ReturnValue == E_OK)
  {
    /* If OpMode is NULL_PTR raise the DET */
    /* [cover parentID={438DAEC2-CBF2-4c10-931F-9B19DEBD3137}]
       [/cover] */
    if (reason == NULL_PTR)
    {
      /* If OpMode is null report to DET */
      /* [cover parentID={07249ECE-1BAE-4cdc-A184-5A1E5E525893}]
         [/cover] */
      (void)Det_ReportError(
        CANTRCV_17_V9251_MODULE_ID,
        CANTRCV_17_V9251_INSTANCE_ID,
        CANTRCV_17_V9251_SID_GETBUSWUREASON,
        CANTRCV_17_V9251_E_PARAM_POINTER
      );
      /* [cover parentID={89A76AC8-CDCB-4b5b-8987-7464AA340CF1}]
      [/cover] */
      /*  return E_NOT_OK */
      ReturnValue = E_NOT_OK;
    }
  }

  /*  If no DET Error */
  /* [cover parentID={07249ECE-1BAE-4cdc-A184-5A1E5E525893}]
     [/cover] */
  if (ReturnValue == E_OK)
  #endif/*(CANTRCV_17_V9251_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the WakeUp reason of CanTrcv channel */
    /* [cover parentID={262E698D-2621-477a-A887-093E6AB96EBD}]
         [/cover] */
    *reason =
     CanTrcv_17_V9251_Channelstatus.Cantrcv_17_V9251_WuReason[Transceiver];
    ReturnValue = E_OK;
  }
  return (ReturnValue);
} /* End of CanTrcv_17_V9251_GetBusWuReason function */

#if (CANTRCV_17_V9251_GET_VERSION_INFO == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={5C5D0536-DD93-4534-86AC-9F80243E6C77}] **
**                    [cover parentID={B0A54B20-FEB8-4ba6-8BE6-DD7F4C56C115}] **
**                                                                            **
**                                                                            **
** Syntax           : void CanTrcv_17_V9251_GetVersionInfo                    **
**                             (Std_VersionInfoType* const VersionInfoPtr)    **
**                                                                            **
**                                                                            **
** Description      : This API returns the version information of this module.**
**                    Note: This API is available only when                   **
**                    CanTrVersionInfoApi is configured as true.              **
** [/cover]                                                                   **
**                                                                            **
** Service ID       :  0x04                                                   **
**                                                                            **
** Sync/Async       :  Synchronous                                            **
**                                                                            **
** Reentrancy       :  reentrant                                              **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : versioninfo - Pointer to where to store the version     **
**                                  information of this module                **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void CanTrcv_17_V9251_GetVersionInfo(Std_VersionInfoType* const versioninfo)
{

  /* If DET is Enable */
  /* [cover parentID={569C7ACE-A052-4f62-A380-9331C9E18BEC}]
  [/cover] */
  #if (CANTRCV_17_V9251_DEV_ERROR_DETECT == STD_ON )


  /* [cover parentID={D7199CEC-3A74-4975-A035-DE705DEA70F2}]
  if versioninfo is null [/cover] */
  if ((versioninfo) == NULL_PTR)
  {

    /* Report to DET */
    /* [cover parentID={8E65E13B-5325-4496-8E48-7DBC214AEA04}]
    [/cover] */
    (void)Det_ReportError((uint16)CANTRCV_17_V9251_MODULE_ID,
                    CANTRCV_17_V9251_INSTANCE_ID,
                    CANTRCV_17_V9251_SID_GETVERSIONINFO,
                    CANTRCV_17_V9251_E_PARAM_POINTER);

  }
  else
  #endif /* #if (CANTRCV_17_V9251_DEV_ERROR_DETECT == STD_ON )  */
  {

    /* [cover parentID={9851B053-CC12-4f94-A86B-E94E5DBE9192}]
       [/cover] */
    /* provide the version of the module */
    versioninfo->moduleID = CANTRCV_17_V9251_MODULE_ID;
    versioninfo->vendorID = CANTRCV_17_V9251_VENDOR_ID;
    versioninfo->sw_major_version = (uint8)CANTRCV_17_V9251_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = (uint8)CANTRCV_17_V9251_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = (uint8)CANTRCV_17_V9251_SW_PATCH_VERSION;

  }

}
#endif /* #if( (CANTRCV_17_V9251_GET_VERSION_INFO == STD_ON) */

/*******************************************************************************
** Traceability     : [cover parentID={08B3B669-4619-4983-BC4B-52857ABDA7D9}] **
**                    [cover parentID={E7E5FD27-9D06-48a5-A4CE-D1DE3C212AA0}] **
**                                                                            **
**                                                                            **
** Syntax           : Std_ReturnType CanTrcv_17_V9251_SetWakeupMode           **
**                    (const uint8 Transceiver, const                         **
**                               CanTrcv_TrcvWakeupModeType TrcvWakeupMode)   **
**                                                                            **
** Description      : This API enables/disables/clears the wake-up events     **
**                    of the CAN transceiver according to parameter           **
**                    TrcvWakeupMode.                                         **
** [/cover]                                                                   **
**                                                                            **
** Service ID       :  0x05                                                   **
**                                                                            **
** Sync/Async       :  Synchronous                                            **
**                                                                            **
** Reentrancy       :  Reentrant for different transceivers                   **
**                                                                            **
** Parameters (in)  : Transceiver - CAN transceiver to which API call has     **
**                                   to be applied.                           **
**                    TrcvWakeupMode - Requested CAN transceiver wakeup mode. **
**                                                                            **
** Parameters (out) :  none                                                   **
**                                                                            **
** Return value     :  E_OK: Wakeup state changed to the requested mode.      **
**                     E_NOT_OK : Wakeup state change has failed or the       **
**                                parameter is out of the allowed range.      **
**                                                                            **
*******************************************************************************/
Std_ReturnType CanTrcv_17_V9251_SetWakeupMode(
  const uint8 Transceiver, const CanTrcv_TrcvWakeupModeType TrcvWakeupMode
)
{
  /* DET return variable */
  Std_ReturnType ReturnValue = E_NOT_OK;
  /* Channel index variable */
  uint8 ChannelIndex = 0;
  /* wake up source variable */
  EcuM_WakeupSourceType TrcvWakeupSource;
  /* wake up by bus variable */
  boolean TrcvWubyBus ;

  /* [cover parentID={C0FBECCA-AA61-4660-9BF5-EB5DD0D8E7BE}]
     If DET is enabled [/cover] */
  #if (CANTRCV_17_V9251_DEV_ERROR_DETECT == STD_ON)

  /*  Is CanTrcv module has been initialized */
  /* [cover parentID={B68F8A79-E345-4d9f-B104-1C734CAD4405}]
     return E_NOT_OK if module is not initialized [/cover] */
  /* [cover parentID={F6836EB7-A90D-444b-961B-CCE4A6C92B15}]
     return E_NOT_OK if module is not initialized [/cover] */
  ReturnValue =
       CanTrcv_17_V9251_lCheckUninitDet(CANTRCV_17_V9251_SID_SETWAKEUPMODE);
  /*  If no DET Error */
  /* [cover parentID={BE071038-154D-4bce-95E5-A2AC12553E43}]
     If no DET Error [/cover] */
  if (ReturnValue == E_OK)
  {
    /* Is Channel Index valid */
    /* [cover parentID={62C69B4E-6D36-4f4d-B861-A1D6874281BF}]
         [/cover] */
    /* [cover parentID={B68F8A79-E345-4d9f-B104-1C734CAD4405}]
           return E_NOT_OK if Channel Index is not valid [/cover] */
    ReturnValue = CanTrcv_17_V9251_lChannelIdDet(Transceiver,
                  CANTRCV_17_V9251_SID_SETWAKEUPMODE);
  }
  /*  If no DET Error */
  /* [cover parentID={1A26A42F-D3E5-450e-81F2-ECC392EC1CDA}]
     If no DET Error [/cover] */
  if (ReturnValue == E_OK)
  {
    /* Is a valid wake up mode */
    /* [cover parentID={7B03835B-8092-42f3-B52A-781EE2B35E37}]
     Is a valid wake up mode [/cover] */
    if  ((TrcvWakeupMode == CANTRCV_WUMODE_ENABLE) ||
        (TrcvWakeupMode == CANTRCV_WUMODE_DISABLE) ||
        (TrcvWakeupMode == CANTRCV_WUMODE_CLEAR))
    {
        /* Valid Wake-Up Mode. */
    }
    else
    {
      /* If invalid wake up mode raise the DET */
      /* [cover parentID={4CB3640E-A756-4057-8595-8C80F12577A6}]
             [/cover] */
      (void)Det_ReportError(
        CANTRCV_17_V9251_MODULE_ID,
        CANTRCV_17_V9251_INSTANCE_ID,
        CANTRCV_17_V9251_SID_SETWAKEUPMODE,
        CANTRCV_17_V9251_E_PARAM_TRCV_WAKEUP_MODE
      );
      /* [cover parentID={B68F8A79-E345-4d9f-B104-1C734CAD4405}]
             return E_NOT_OK if TrcvWakeupMode is invalid [/cover] */
      ReturnValue = E_NOT_OK;
    }
  }

  /*  If no DET Error */
  /* [cover parentID={7B03835B-8092-42f3-B52A-781EE2B35E37}]
     If no DET Error [/cover] */
  if (ReturnValue == E_OK)
  #endif
    /*(CANTRCV_17_V9251_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the channel Index */
    ChannelIndex = CanTrcv_17_V9251_ChannelUsed[Transceiver];

    /* Get the configured wake up by bus status */
    TrcvWubyBus =
    CanTrcv_17_V9251_ChannelConfig[ChannelIndex].CanTrcv_17_V9251_WakeupbyBus;

    /*[cover parentID={EF7E5F40-86A2-4533-89C4-BB6005579436}]
      If wake up by bus is enabled [/cover]*/
    if (TRUE == TrcvWubyBus)
    {
      /* Get the channel Index */
      TrcvWakeupSource =
      CanTrcv_17_V9251_ChannelConfig[ChannelIndex].
                         CanTrcv_17_V9251_WakeupSourceRef;

      /* If wake up mode is enable */
      /* [cover parentID={C096EDD6-5F80-4dcd-AABC-C2EEE1B5DB8A}]
          If wake up mode is enable [/cover] */
      if (TrcvWakeupMode == CANTRCV_WUMODE_ENABLE)
      {
        /* update the wake up mode for CanTrcv channel */
        /* [cover parentID={1E096D68-EB72-4d4b-BAD4-D717FB2DC1A3}]
            [/cover] */
        CanTrcv_17_V9251_Channelstatus.
        CanTrcv_17_V9251_WakeupMode[Transceiver] = CANTRCV_WUMODE_ENABLE;

        /* Check for pending wake up events */
        /* [cover parentID={218E6A77-D73A-4ec1-86DE-5C336619CA7A}]
           [/cover] */
        if(CANTRCV_17_V9251_PENWU_SET ==
                   CanTrcv_17_V9251_lGetPendWu(Transceiver))
        {
          /* Report to EcuM for previous wake up event */
          EcuM_SetWakeupEvent(((uint32)1U) << TrcvWakeupSource);
          CanTrcv_17_V9251_lClearPendWu(Transceiver);

        }
      }
      /* If wake up mode is disable */
      /* [cover parentID={DC77B2ED-B75F-4c33-85C9-2FA3AA2497BA}]
          If wake up mode is disable [/cover] */
      else if (TrcvWakeupMode == CANTRCV_WUMODE_DISABLE)
      {
        /* update the wake up mode as disable for CanTrcv channel */
        /* [cover parentID={BF0F2008-9FAA-47ea-ACAE-2C47EF132714}]
           update the wake up mode as disable for CanTrcv channel [/cover] */
           CanTrcv_17_V9251_Channelstatus.
        CanTrcv_17_V9251_WakeupMode[Transceiver] = CANTRCV_WUMODE_DISABLE;
      }
      /* [cover parentID={413CF59A-19CB-46bc-AE7F-DEA970D8A6EF}]
          [/cover] */
      /* If wake up mode is clear */
      else
      {
        /* Clear the pending wake up events. */
        /* [cover parentID={AD770B4E-F9E2-4cd3-9844-4124709907D8}]
          Clear the pending wake up events [/cover] */
        CanTrcv_17_V9251_lClearPendWu(Transceiver);

      }
      /* Set Return Value to E_OK */
      /*[cover parentID={B187D832-A67E-4d14-920A-4C96AD084E47}]
      Set Return Value to E_OK  [/cover] */
      ReturnValue = E_OK;
    }
    else
    {
    /* wake up by bus is disabled */
    ReturnValue = E_NOT_OK;
    }
  }
  return (ReturnValue);
} /* End of CanTrcv_17_V9251_SetWakeupMode function */

/*******************************************************************************
** Traceability    : [cover parentID={2EF448E0-F24D-4bcf-9658-8B688F311B1A}]  **
**                   [cover parentID={38E782AB-23E3-4463-B742-902202207FE6}]  **
**                                                                            **
**                                                                            **
** Syntax          : Std_ReturnType CanTrcv_17_V9251_CheckWakeup              **
**                                                (const uint8 Transceiver)   **
** [/cover]                                                                   **
** Description     : This API service is called by underlying CANIF module    **
**                   in case a wake up interrupt is detected.                 **
**                   This API validates the wake up by checking the           **
**                   current mode of CAN Transceiver and                      **
**                   CanTrcvWakeupByBusUsed configuration parameter.          **
**                                                                            **
**                                                                            **
** Service ID      : 0x07                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : non reentrant                                            **
**                                                                            **
** Parameters (in) : Transceiver - Transceiver to which the API               **
**                               call has to be applied.                      **
** Parameters (out):                                                          **
**                                                                            **
** Return value    : E_OK :when a valid interrupt is detected                 **
**                   E_NOT_OK : when a no interrupt is detected or            **
**                                             due to DET error               **
**                                                                            **
*******************************************************************************/
Std_ReturnType CanTrcv_17_V9251_CheckWakeup(const uint8 Transceiver)
{
  /* DET return variable */
  Std_ReturnType ReturnValue = E_NOT_OK;
  /* wake up source variable */
  EcuM_WakeupSourceType TrcvWakeupSource;
  /* Channel index variable */
  uint8 ChannelIndex = 0;
  /* CanTrcv Current mode variable */
  CanTrcv_TrcvModeType CurrentMode;
  /* wake up by bus variable */
  boolean TrcvWubyBus ;
  /* STB Diochannel variable */
  Dio_ChannelType TrcvChannel;

  /* [cover parentID={BB947AB9-369E-4810-A1D5-8287A36901D8}]
     If DET enabled [/cover] */
  #if (CANTRCV_17_V9251_DEV_ERROR_DETECT == STD_ON)

  /* Is CanTrcv module has been initialized */
  /* [cover parentID={A844E599-54A6-46d4-9D65-F7C209BAA684}]
      Is CanTrcv module has been initialized [/cover] */
  /* [cover parentID={E091DE02-AB7A-4403-9325-9AEB6C0CEB6F}]
      Is CanTrcv module has been initialized [/cover] */
  ReturnValue =
      CanTrcv_17_V9251_lCheckUninitDet(CANTRCV_17_V9251_SID_CHECKWAKEUP);

  /* If no DET error
  [cover parentID={03F2699D-A066-4172-B492-8553CDB4CF0A}]
  If no DET error[/cover] */
  if (ReturnValue == E_OK)
  {
    /* Is Channel Index valid */
    /* [cover parentID={8F4AFD96-AFE9-4c84-A8B9-10952FC0ED46}]
         [/cover] */
    /* [cover parentID={A844E599-54A6-46d4-9D65-F7C209BAA684}]
      [/cover] */
    ReturnValue = CanTrcv_17_V9251_lChannelIdDet(Transceiver,
                  CANTRCV_17_V9251_SID_CHECKWAKEUP);
  }
  /* [cover parentID={A635AFB2-6B8C-42a9-A92B-0FB11D593459}]
      If no DET errors [/cover] */
  if (ReturnValue == E_OK)
  #endif
    /* End of (CANTRCV_17_V9251_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the channel Index */
    ChannelIndex = CanTrcv_17_V9251_ChannelUsed[Transceiver];
    /* Get the wakeup source Id */
    TrcvWakeupSource =
    CanTrcv_17_V9251_ChannelConfig[ChannelIndex].
                            CanTrcv_17_V9251_WakeupSourceRef;

    /* Get the configured wake up by bus status */
    TrcvWubyBus =
    CanTrcv_17_V9251_ChannelConfig[ChannelIndex].
                               CanTrcv_17_V9251_WakeupbyBus;

    /* Get the channel mode */
    CurrentMode =
    CanTrcv_17_V9251_Channelstatus.Cantrcv_17_V9251_CurrentMode[Transceiver];

    /*  Get the configured Diochannel for STB Pin */
    TrcvChannel =
    CanTrcv_17_V9251_ChannelConfig[ChannelIndex].CanTrcv_17_V9251_DioChannel;

    /* Is current mode is Stand By and Wake up by bus is enabled */
    /* [cover parentID={EFA3A3A8-68E7-4d6d-9AB6-A4D9E0BF7F48}]
       Is current mode is Stand By and Wake up by bus is enable [/cover] */
    if ((CANTRCV_TRCVMODE_STANDBY == CurrentMode) &&
        (TRUE == TrcvWubyBus))
    {
      /* Put the CanTrcv into Normal Mode after valid wake up is detected
       [cover parentID={36CF6044-DEAA-4b1a-9B73-D13C144CADA1}][/cover] */
      Dio_WriteChannel(TrcvChannel, (CANTRCV_17_V9251_NORMAL_MODE));

      /* Delay for Mode Transition to normal mode */
      CanTrcv_17_V9251_ldelay();

      /* Update the Current mode as Normal */
      CanTrcv_17_V9251_Channelstatus.
      Cantrcv_17_V9251_CurrentMode[Transceiver] = CANTRCV_TRCVMODE_NORMAL;

      /* update Wake up reason as Wake up by bus */
      CanTrcv_17_V9251_Channelstatus.
      Cantrcv_17_V9251_WuReason[Transceiver] = CANTRCV_WU_BY_BUS;

      /* If wake up mode is enable */
      /* [cover parentID={33CDC7E0-5DA6-43ea-962D-1374B40CAB5A}]
      [/cover] */
      if (CANTRCV_WUMODE_ENABLE ==
          CanTrcv_17_V9251_Channelstatus.
          CanTrcv_17_V9251_WakeupMode[Transceiver])
      {
        /* [cover parentID={1E702B71-9B38-4d87-B573-86B2755917BE}]
        Report the wake up event to ECuM [/cover] */
        EcuM_SetWakeupEvent(((uint32)1U) << TrcvWakeupSource);
      }
      else /* If wake up mode is disable */
      {
        /* store the wake up event as pending */
        CanTrcv_17_V9251_lSetPendWu(Transceiver);
      }
      ReturnValue = E_OK;
    }
    else/* if wrong wake up return E_NOT_OK */
    {
      ReturnValue = E_NOT_OK;
    }

  }
  return (ReturnValue);
}  /* End of CanTrcv_17_V9251_CheckWakeUp function */

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
/*******************************************************************************
** Traceability      :[cover parentID={777CDA2F-4AC3-43d0-A9FD-8F9830189678}] **
**                                                                            **
** Syntax            : static void CanTrcv_17_V9251_lSetInitMode              **
**                                                     (const uint8 Channel)  **
**                                                                            **
** Description       : This API sets the CAN transceiver hardware to the      **
**                      mode configured by the configuration parameter        **
**                      CanTrcvInitState.                                     **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
**                                                                            **
** Service ID        :  N/A                                                   **
**                                                                            **
** Sync/Async        :  Asynchronous                                          **
**                                                                            **
** Reentrancy        :  Non reentrant                                         **
**                                                                            **
** Parameters (in)   :  Channel - CAN transceiver to which API call has to    **
**                                be applied.                                 **
**                                                                            **
** Parameters (out)  :  None                                                  **
**                                                                            **
** Return value      :  None                                                  **
**                                                                            **
*******************************************************************************/
static void CanTrcv_17_V9251_lSetInitMode(const uint8 Channel)
{
  /* STB Diochannel variable */
  Dio_ChannelType TrcvChannel;
  /* internal value variable */
  Dio_LevelType TrcvPinLevel;
  /* CanTrcv mode variable */
  CanTrcv_TrcvModeType TrcvNwMode;
  /* channel index variable */
  uint8 TrcvChannelId;

  /*  Get the configured Diochannel for STB Pin */
  TrcvChannel =
  CanTrcv_17_V9251_ChannelConfig[Channel].CanTrcv_17_V9251_DioChannel;
  /*  Get the configured mode for initialization  */
  TrcvNwMode =
  CanTrcv_17_V9251_ChannelConfig[Channel].CanTrcv_17_V9251_NetworkMode;
  /*  Get the internal value for  */
  TrcvPinLevel =
  CanTrcv_17_V9251_ChannelConfig[Channel].CanTrcv_17_V9251_DioPinLevel;
  /*  Put the CanTrcv into configured Mode  */
  /* [cover parentID={A32F70E4-C90D-4156-BBB9-B9BF82C1BCC8}]
     Put the CanTrcv into configured Mode [/cover] */
  Dio_WriteChannel(TrcvChannel, (Dio_LevelType) (TrcvPinLevel));

  /*  Is normal mode configured  */
  /* [cover parentID={BD05E0B0-0843-4e62-9248-A4AE5A7FF097}]
      Is normal mode configured [/cover] */
  if (TrcvNwMode == CANTRCV_TRCVMODE_NORMAL)
  {
    /* Delay for Mode Transition to Normal mode */
    CanTrcv_17_V9251_ldelay();
  }
  /*  Get the CanTrcv Channel */
  TrcvChannelId =
  CanTrcv_17_V9251_ChannelConfig[Channel].CanTrcv_17_V9251_ChannelId;
  /* update the mode after initialization  */
  /* [cover parentID={D4AE1E11-F60A-4095-BC1C-3A518D899821}]
     Put the CanTrcv into configured Mode [/cover] */
   CanTrcv_17_V9251_Channelstatus.
   Cantrcv_17_V9251_CurrentMode[TrcvChannelId] = TrcvNwMode;

   /* update Wake up reason as Wake up by Power On */
   CanTrcv_17_V9251_Channelstatus.
   Cantrcv_17_V9251_WuReason[TrcvChannelId] = CANTRCV_WU_POWER_ON;
   /*MISRA2012_RULE_2_2_JUSTIFICATION:Parameter TrcvChannelId is used as index
   to access the respective wake-up reason of the channel using setbit atomic.*/

  return;
}
#if (CANTRCV_17_V9251_DEV_ERROR_DETECT == STD_ON)
/*******************************************************************************
** Traceability   :[cover parentID={96633709-DFCB-4040-B3AB-2BCB527C9EB1}]    **
**                                                                            **
** Syntax         : static Std_ReturnType CanTrcv_17_V9251_lCheckUninitDet    **
**                                                   (const uint8 ServiceId)  **
** Description    : This function will check whether the module               **
**                  Initialization has been done or not.                      **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
**                                                                            **
** Service ID     : N/A                                                       **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : ServiceId:  API service id for DET                        **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : E_OK : Module is initialized.                             **
**                  E_NOT_OK : Module is not initialized and DET reported.    **
**                                                                            **
*******************************************************************************/
static Std_ReturnType CanTrcv_17_V9251_lCheckUninitDet(const uint8 ServiceId)
{
  /* DET return variable */
  Std_ReturnType RetVal = E_NOT_OK;

  /* Is CanTrcv driver is not initialized */
  /* [cover parentID={CF8B10F0-8A9C-43d4-A0BA-53D5C3F8FE3E}]
     If driver is initialized [/cover] */
  if (CanTrcv_17_V9251_DriverState == CANTRCV_17_V9251_UNINIT)
  {
    /* If CanTrcv Driver is not initialized raise DET */
    /* [cover parentID={85475AF2-750A-4fb0-ADF8-61CDF2BC7850}]
         [/cover] */
    (void)Det_ReportError(CANTRCV_17_V9251_MODULE_ID,
                          CANTRCV_17_V9251_INSTANCE_ID,
                          ServiceId,
                          CANTRCV_17_V9251_E_UNINIT);
    /* return E_NOT_OK */
    RetVal = E_NOT_OK;

  }
  else /* Is CanTrcv driver is initialized */
  {
    /* return E_OK */
    RetVal = E_OK;

  }

  return RetVal;
}

/*******************************************************************************
** Traceability   :[cover parentID={9F5105A3-91E9-43a6-BEB7-BF7C19A1F125}]    **
**                                                                            **
** Syntax         : static Std_ReturnType CanTrcv_17_V9251_lChannelIdDet(     **
**                             const uint8 Channel, const uint8 ServiceId)    **
**                                                                            **
** Description    : This function will check for valid channel Id.            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : N/A                                                       **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : ServiceId:  API service id for DET                        **
**                  Channel  : CAN Transceiver channel Id.                    **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : E_OK : Channel Id is valid.                               **
**                  E_NOT_OK : Channel Id is invalid and DET reported.        **
**                                                                            **
*******************************************************************************/
static Std_ReturnType \
CanTrcv_17_V9251_lChannelIdDet(const uint8 Channel, const uint8 ServiceId)
{
  /* DET return variable */
  Std_ReturnType RetVal = E_NOT_OK;

  /* Is channel Id Invalid */
  /* [cover parentID={D72D590A-F9F9-4f0c-ADD4-B544B3F5E28E}]
      Is channel Id Invalid [/cover] */
  if (Channel >= CANTRCV_17_V9251_CHANNELS_CFG)
  {
    /* Report to DET for Invalid Channel*/
    /* [cover parentID={6CE71A64-CFF0-4584-8109-B75A084ECB63}]
      [/cover] */
    (void)Det_ReportError(CANTRCV_17_V9251_MODULE_ID,
                          CANTRCV_17_V9251_INSTANCE_ID,
                          ServiceId,
                          CANTRCV_17_V9251_E_INVALID_TRANSCEIVER);
  }
  else
  {
    /* Check if channel is configured as used or not */
    /* [cover parentID={24563972-800B-4628-85AD-3E3C2245F717}]
       [/cover] */
    if (CanTrcv_17_V9251_ChannelUsed[Channel] == 0xFFU)
    {
      /* Report to DET for accesing Channel configured as not used*/
      /* [cover parentID={6CE71A64-CFF0-4584-8109-B75A084ECB63}]
        [/cover] */
      (void)Det_ReportError(CANTRCV_17_V9251_MODULE_ID,
                            CANTRCV_17_V9251_INSTANCE_ID,
                            ServiceId,
                            CANTRCV_17_V9251_E_INVALID_TRANSCEIVER);
    }
    else
    {

      RetVal = E_OK;
    }

  }

  return RetVal;
}
#endif /* #if (CANTRCV_17_V9251_DEV_ERROR_DETECT == STD_ON) */
/*******************************************************************************
** Traceability   :[cover parentID={4FD17C05-833D-4014-98E9-0422D3AB093E}]    **
**                                                                            **
** Syntax         : void CanTrcv_17_V9251_ldelay(void)                        **
**                                                                            **
** Description    : This function will provide CanTrcv Mode Switch Delay      **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : None                                                      **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
static void CanTrcv_17_V9251_ldelay(void)
{
  uint32 TickResolution;
  uint32 DelayCount;
  uint32 InitialCount;
  uint32 ElapsedTicks;

  /* Get the Tick resolution */
  TickResolution = Mcal_DelayTickResolution();
  /* Calculate the Delay count */
  DelayCount = (uint32)CANTRCV_17_V9251_WAIT_COUNT / TickResolution ;
  /* Get the Initial count */
  InitialCount = Mcal_DelayGetTick();

  /* [cover parentID={90904409-B934-447e-B9B3-1917308C2DB7}]
  State Transition Delay
  [/cover] */
  do
  {
    /* Calculate the elapsed Tick  */
    ElapsedTicks = (uint32)(Mcal_DelayGetTick() - InitialCount);

  } while(DelayCount >= ElapsedTicks);
}
/*******************************************************************************
** Traceability   :[cover parentID={F21DEA3D-4097-4713-A059-5727A234C47E}]    **
**                                                                            **
** Syntax         : LOCAL_INLINE uint8 CanTrcv_17_V9251_lGetPendWu            **
**                                                 (const uint8 Channel)      **
**                                                                            **
** Description    : Function to get the pending wakeup's of the Channel.      **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : Channel: CAN Transceiver Channel ID.                      **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint16 CanTrcv_17_V9251_lGetPendWu(const uint8 Channel)
{
  /* Get the Pending Wake up of the CAN Transceiver channel */
  return ((CanTrcv_17_V9251_PendWakeup >> Channel) & (uint16)1U);
}

/*******************************************************************************
** Traceability   :[cover parentID={DF3ED19A-696A-437c-9C03-66368F688FFC}]    **
**                                                                            **
** Syntax         : LOCAL_INLINE void CanTrcv_17_V9251_lSetPendWu             **
**                                                (const uint8 Channel)       **
**                                                                            **
** Description    : Function to Set the pending wakeup's of the Channel       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : Channel: CAN Transceiver Channel ID.                      **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void CanTrcv_17_V9251_lSetPendWu(const uint8 Channel)
{
  /* set the pending wake up of the Transceiver */
  CanTrcv_17_V9251_PendWakeup |= (uint16)((uint16)1U << Channel) ;
}

/*******************************************************************************
** Traceability   :[cover parentID={4578BCD3-1334-4123-8AC8-285ABDC98AA0}]    **
**                                                                            **
** Syntax         : LOCAL_INLINE void CanTrcv_17_V9251_lClearPendWu           **
**                                                  (const uint8 Channel)     **
**                                                                            **
** Description    : Function to clear the pending wakeup's of the Channel     **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : Channel: CAN Transceiver Channel ID.                      **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void CanTrcv_17_V9251_lClearPendWu(const uint8 Channel)
{
  /* clear the pending wake up of the Transceiver */
  /* [cover parentID={338039DA-83BF-4b4d-A087-BC7B1377C7AF}]
     [/cover] */
  CanTrcv_17_V9251_PendWakeup &= (uint16)(~((uint16)1U << Channel ));
}

#define CANTRCV_17_V9251_STOP_SEC_CODE_QM_LOCAL
/* [cover parentID={DC0F3BD1-1815-492a-8B3D-D19A2DBC37C6}]
    MemMap file  [/cover] */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
    MemMap file  [/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
    MemMap file  [/cover] */
/* [cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
    Callout Memory section not used in CanTrcv_17_V9251 driver
  [/cover]*/
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_V9251_MemMap.h"

/*******************************************************************************
**                               End of File                                  **
*******************************************************************************/
