#ifndef OCU_H
#define OCU_H

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
**  FILENAME     : Ocu.h                                                      **
**                                                                            **
**  VERSION      : 15.0.0                                                     **
**                                                                            **
**  DATE         : 2021-03-02                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID={BE31E28F-DD8A-4185-BB3A-92BC76B2C2DE}]    **
**                                                                            **
**  DESCRIPTION  : Ocu Driver header definition file                          **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) :Specification of OCU Driver,AUTOSAR Release 4.2.2&4.4.0 **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* [cover parentID={2B46C055-0FB0-4fb3-9711-505BA534CE9A}] */
/* Imported Types */
/*  [/cover] */
/* [cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}][/cover] */
/* Inclusion of Platform_Types.h and Compiler.h */
#include "Std_Types.h"

#include "Mcal_Compiler.h"

/*Ocu Configuration File*/
#include "Ocu_Cfg.h"

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/* [cover parentID={A9645E92-91D5-4a4e-9A60-76DDF65EA3D6}] */
/*
  Published parameters
*/
/* OCU Vendor ID - Vendor ID of the dedicated implementation of this
module according to the AUTOSAR vendor list */
#define OCU_VENDOR_ID     ((uint16)17)
/*OCU Module ID - Module ID of this module from Module List */
#define OCU_MODULE_ID     ((uint16)125)
/*OCU Instance ID - Set as 0  */
#define OCU_INSTANCE_ID   ((uint8)0)
/*  [/cover] */

#if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
/*
    Development error values
*/

/* Init function: Ocu_Init called while driver already initialized */
/* [cover parentID={D23F5D79-1646-4dad-9BFD-63A76659DF97}] */
#define OCU_E_ALREADY_INITIALIZED  ((uint8)0x07)
/*  [/cover] */
/* API Service Ocu_StartChannel called on a RUNNING channel  */
/* [cover parentID={BBA25AD4-466E-4946-A3C4-091E74C02A95}] */
#define OCU_E_BUSY       ((uint8)0x09)
/*  [/cover] */
/* Channel not allocated for current core. */
/* [cover parentID={B8A951B3-C01C-4094-82FF-A1E9475F411E}] */
#define OCU_E_CORE_CHANNEL_MISMATCH      ((uint8)0x65)
/*  [/cover] */
/* Init called for non configured core */
/* [cover parentID={38E13C1C-620C-456a-AE0A-6362DBE99B0C}] */
#define OCU_E_CORE_NOT_CONFIGURED      ((uint8)0x64)
/*  [/cover] */
/* API Service used with NULL  pointer */
/* [cover parentID={91529BAC-1B0A-467c-A9F5-5DB6C90592BC}] */
#define OCU_E_INIT_FAILED          ((uint8)0x0B)
/*  [/cover] */
/* API service used when no notification function is configured */
/* [cover parentID={359FF161-C638-47a8-A08E-15C79A1E2378}] */
#define OCU_E_NO_VALID_NOTIF       ((uint8)0x06)
/*  [/cover] */
/* API service used with invalid pin action */
/* [cover parentID={5D2292C4-42F1-43da-B7C8-CD6C2A248C05}] */
#define OCU_E_PARAM_INVALID_ACTION       ((uint8)0x05)
/*  [/cover] */
/* API service used with an invalid channel Identifier  */
/* [cover parentID={89958249-1C76-47b7-9742-02BD0559AFEE}] */
#define OCU_E_PARAM_INVALID_CHANNEL        ((uint8)0x03)
/*  [/cover] */
/* API service used with an invalid pin state */
/* [cover parentID={7CEEB9A3-C08C-47a9-9F11-C0846F8C4D4A}] */
#define OCU_E_PARAM_INVALID_STATE        ((uint8)0x04)
/*  [/cover] */
/* API Service used on a channel with no pin */
/* [cover parentID={DD4D141F-F030-49cc-87FB-F06BA07FEE5A}] */
#define OCU_E_PARAM_NO_PIN                        ((uint8)0x0A)
/*  [/cover] */
/* API service called with invalid pointer */
/* [cover parentID={06AD8BDF-83FA-4b14-96CF-87674058ADB9}] */
#define OCU_E_PARAM_POINTER                       ((uint8)0x08)
/*  [/cover] */
/* API service used without module initialization */
/* [cover parentID={F9EAA811-F16C-4d0b-9A7A-8AC18296BE72}] */
#define OCU_E_UNINIT                              ((uint8)0x02)
/* API Service ID's */
/* API Service ID for Ocu_Init() */
#define OCU_SID_INIT                              ((uint8)0x00)
/* API Service ID for Ocu_DeInit() */
#define OCU_SID_DEINIT                            ((uint8)0x01)
/* API Service ID for Ocu_StartChannel() */
#define OCU_SID_STARTCHANNEL                      ((uint8)0x02)
/* API Service ID for Ocu_StopChannel() */
#define OCU_SID_STOPCHANNEL                       ((uint8)0x03)
/* API Service ID for Ocu_SetPinState() */
#define OCU_SID_SETPINSTATE                       ((uint8)0x04)
/* API Service ID for Ocu_SetPinAction() */
#define OCU_SID_SETPINACTION                      ((uint8)0x05)
/* API Service ID for Ocu_GetCounter() */
#define OCU_SID_GETCOUNTER                        ((uint8)0x06)
/* API Service ID for Ocu_SetAbsoluteThreshold() */
#define OCU_SID_SETABSOLUTETHRESHOLD              ((uint8)0x07)
/* API Service ID for Ocu_SetRelativeThreshold() */
#define OCU_SID_SETRELATIVETHRESHOLD              ((uint8)0x08)
/* API Service ID for Ocu_GetVersionInfo */
#define OCU_SID_GETVERSIONINFO                    ((uint8)0x09)
/* API Service ID for Ocu_DisableNotification() */
#define OCU_SID_DISABLENOTIFICATION               ((uint8)0x0A)
/* API Service ID for Ocu_EnableNotification() */
#define OCU_SID_ENABLENOTIFICATION                ((uint8)0x0B)

#if (OCU_SAFETY_ENABLE == STD_ON)
/* API Service ID for Isr*/
#define OCU_SID_ISR                               ((uint8)0x20)
#endif
#endif


/* OCU options chosen */
#define OCU_GTM_TOM           (0U)
#define OCU_GTM_ATOM          (1U)
#define OCU_GTM_ATOM_SHARED   (2U)

/* Configurable Clocks used in pbcfg.c*/

#define OCU_GTM_CONFIGURABLE_CLOCK_0   ((uint8)0U)

#define OCU_GTM_CONFIGURABLE_CLOCK_1   ((uint8)1U)

#define OCU_GTM_CONFIGURABLE_CLOCK_2   ((uint8)2U)

#define OCU_GTM_CONFIGURABLE_CLOCK_3   ((uint8)3U)

#define OCU_GTM_CONFIGURABLE_CLOCK_4   ((uint8)4U)

#define OCU_GTM_CONFIGURABLE_CLOCK_5   ((uint8)5U)

#define OCU_GTM_CONFIGURABLE_CLOCK_6   ((uint8)6U)

#define OCU_GTM_CONFIGURABLE_CLOCK_7   ((uint8)7U)

#define OCU_GTM_TBU_TS0   ((uint8)8U)

#define OCU_GTM_TBU_TS1   ((uint8)9U)

#define OCU_GTM_TBU_TS2   ((uint8)10U)

#define OCU_GTM_FIXED_CLOCK_0   ((uint8)0U)

#define OCU_GTM_FIXED_CLOCK_1   ((uint8)1U)

#define OCU_GTM_FIXED_CLOCK_2   ((uint8)2U)

#define OCU_GTM_FIXED_CLOCK_3   ((uint8)3U)

#define OCU_GTM_FIXED_CLOCK_4   ((uint8)4U)

/* maximum number of cores supported by OCU */
#define OCU_MAX_CORES 6

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/* [cover parentID={D466AD6D-E1C0-472c-B7E8-A8176A2EA8D7}] */
/* Numeric identifier of a OCU channel */
typedef uint8 Ocu_ChannelType;
/*  [/cover] */
/* [cover parentID={3EBE5004-31C9-4d38-A85C-96AFBCE402BB}] */
/* To provide Notification the following type will be used */
typedef void (*Ocu_NotifiPtrType)(void);
/*  [/cover] */
/* [cover parentID={38990AA0-4662-4674-AC52-1F24207F9A2D}] */
typedef enum
{
  /* compare match will occur Outside the current Reference Interval */
  OCU_CM_OUT_REF_INTERVAL = 0U,
  /* compare match will  occur Inside the current Reference Interval */
  OCU_CM_IN_REF_INTERVAL = 1U
} Ocu_ReturnType;

#if(OCU_SAFETY_ENABLE == STD_ON)

/* API service used with wrong compare values */
/* [cover parentID={D94F58EA-1266-4286-BF9C-73A2F9985B2C}] */
#define OCU_E_PARAM_COMPARE_VALUE 200U
/*  [/cover] */
/* API service used with wrong Reference values */
/* [cover parentID={A854CFC2-EA28-47d2-AED9-3A58BD12C16A}] */
#define OCU_E_PARAM_REF_VALUE 201U
/*  [/cover] */
/*  function: ISR invoked on a spurious interrupt
*   For Un-Initialized Channal*/
/* [cover parentID={D7DE1EB4-B79E-44c9-BBC8-2846E3869853}] */
#define OCU_E_INVALID_ISR_UNINIT 202U
/*  [/cover] */
/* function: ISR invoked on a spurious interrupt
* ISR is invoked when the channel is not active */
/* [cover parentID={E332B88C-35D4-4bd5-8ECE-8BDA5C848E02}] */
#define OCU_E_INVALID_ISR_INACTIVE_CHANNEL 203U
/*  [/cover] */
/* function: ISR invoked on a spurious interrupt
*ISR is invoked with wrong flags (Compare match notification flag) */
/* [cover parentID={0075E04F-293C-42d0-B9B1-C38C9CAA29F9}] */
#define OCU_E_INVALID_ISR_COMP_INVALID 204U
/*  [/cover] */
/* function: ISR invoked on a spurious interrupt
* the ISR is invoked when the passed channel ID is not configured*/
/* [cover parentID={E69C5E36-4033-433e-84DB-E299C5AAD442}] */
#define OCU_E_INVALID_ISR_CHANNEL_INVALID 205U
/*  [/cover] */
/* function: ISR invoked on a spurious interrupt
* the ISR is invoked when the passed channel and core id mismatch. */
/* [cover parentID={A8CF557E-7610-45e4-9E38-E4BCB22CF2EA}] */
#define OCU_E_INVALID_ISR_CHANNEL_CORE_MISMATCH 206U
/*  [/cover] */

#endif






/*  [/cover] */
/* [cover parentID={72417ABE-D885-4230-A83F-386F60EFBB86}] */
/* Type for reading the counter and writing the threshold values  */
typedef uint32 Ocu_ValueType;
/*  [/cover] */
/* [cover parentID={9AE436C1-3D3C-4de7-AEB4-A913AE50D91D}] */
/* Pin action to be performed on compare match */
typedef enum
{
  /* pin will remain at its current level */
  OCU_DISABLE = 0U,
  /* pin will be set HIGH */
  OCU_SET_HIGH = 1U,
  /* pin will be set LOW */
  OCU_SET_LOW = 2U,
  /* pin will be set to the opposite of its current level */
  OCU_TOGGLE = 3U


} Ocu_PinActionType;
/*  [/cover] */
/* [cover parentID={FBF0099B-7421-4227-BB8A-85AB6F36EF2E}] */
typedef enum
{
  /* Pin state is LOW */
  OCU_LOW = 0U,
  /* Pin state is HIGH */
  OCU_HIGH = 1U

} Ocu_PinStateType;
/*  [/cover] */

/* INTERNAL DATA TYPES */
/*******************************************************************************
**                      Internal Type Definitions                             **
*******************************************************************************/
/* [cover parentID={D135CB50-26FC-4997-B41F-316D5EC10ABE}] */
/* The following struct type is channel dependent configuration */
typedef struct
{
  /* The following parameter is a function pointer to provide notification */
  Ocu_NotifiPtrType NotificationPointer;
  /* Default Threshold for the channel */
  Ocu_ValueType DefaultThreshold;
  /* Max counter for the channel */
  Ocu_ValueType MaxCounterValue;
  /* channel properties */
  struct
  {
    /* HW unit selected */
    unsigned_int      AssignedHwUnit: 2;
    /* resource number */
    unsigned_int      AssignedHwUnitNumber: 16;
    /* pin default state */
    unsigned_int      PinDefaultState: 1;
    /* Pin used */
    unsigned_int      PinUsed: 1;
    /* Dma used */
    unsigned_int      DmaUsed: 1;
    /* Adc used */
    unsigned_int      AdcUsed: 1;
    /* Clock selection */
    unsigned_int      ClockSelect: 4;
    /* reserved and padded to 32 bits */
    unsigned_int      Reserved: 6;
  } OcuProperties;
} Ocu_ChannelConfigType;
/*  [/cover] */
/* [cover parentID={DD9C834E-CC09-45d9-8BBA-2F9E02111A33}] */
/*Ocu_ConfigTypeCore struct*/
typedef struct
{
  /* Pointer to Channel Configuration structure */
  const Ocu_ChannelConfigType* ChannelConfigPtr;
  /* Max channels defined per core.*/
  Ocu_ChannelType MaxChannelCore;
} Ocu_CoreConfigType;
/*  [/cover] */
/* [cover parentID={571F3101-3413-4996-88EA-09A9E3F62527}] */
/*Ocu_ConfigType struct*/
typedef struct
{
  /* Pointer to Core Configuration structure */
  const Ocu_CoreConfigType * CoreConfig[OCU_MAX_CORES];
  #if (OCU_SINGLE_CORE == STD_OFF)
  /* Mapping between global logical identifier to core specific logical
     identifier. 16 bit value - lower 8bit(assuming there will be less than 256
     channels) for identifier.upper 8bit to identify which core is using that
     identifier.*/
  const uint16 ChannelMapping[OCU_MAX_CHANNELS];
  #endif
} Ocu_ConfigType;
/*  [/cover] */

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/

#define OCU_START_SEC_CODE_ASIL_B_GLOBAL
#include "Ocu_MemMap.h"

/*******************************************************************************
**                                                                            **
** Syntax : void Ocu_Init(const Ocu_ConfigType       *const ConfigPtr )       **
** Description : Driver Module Initialization                                 **
**               1.This function will initialize all relevant registers of    **
**               configured hardware (AssignedHWUnit) with the values of      **
**               structure referenced by the parameter ConfigPtr.             **
**               2. This service will disable all notifications.              **
**               3. Resources that are not configured in the configuration    **
**                  file will not be changed.                                 **
**               4. All OCU channel status is set to OCU_STOPPED              **
**               5. All used registers used by configuration will be          **
**                  initialized if Reset and Deinit API will not reset the    **
**                  registers                                                 **
**               6. Clearing of pending interrupt flags not done in this      **
**                  function.                                                 **
**                                                                            **
** Service ID:      0                                                         **
**                                                                            **
** Sync/Async:      Synchronous                                               **
**                                                                            **
** Reentrancy:      non reentrant                                             **
**                                                                            **
** Parameters (in): Config - Pointer to configuration set                     **
**                                                                            **
** Parameters (out):none                                                      **
**                                                                            **
** Return value:    none                                                      **
**                                                                            **
*******************************************************************************/
extern void Ocu_Init
(
  const Ocu_ConfigType *const ConfigPtr
);

/*******************************************************************************
**                                                                            **
** Syntax : void Ocu_DeInit(void)                                             **
**                                                                            **
** Description : Service for OCU De-Initialization                            **
**               1.After the call of this service, the state of the used      **
**                 peripherals/registers will set to power on reset state.    **
**               2. This service will disable all used interrupts and         **
**                  notifications.                                            **
**               3. This service clear all pending interrupt flags            **
**               4. All global variables will set to reset value              **
**                                                                            **
** Service ID:       0x01                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       non reentrant                                            **
**                                                                            **
** Parameters (in):  none                                                     **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
*******************************************************************************/
#if (OCU_DE_INIT_API == STD_ON)
extern void Ocu_DeInit
(
  void
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Ocu_DeInit() (ERROR_Ocu_DeInit_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
**                                                                            **
** Syntax : void Ocu_EnableNotification(                                      **
**                       const  Ocu_ChannelType ChannelNumber)                **
**                                                                            **
** Description : This service will enable notifications of channel.           **
**                                                                            **
** Service ID:       0x0B                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  ChannelNumber - Numeric identifier of the OCU channel    **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
*******************************************************************************/
#if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
extern void Ocu_EnableNotification
(
  const Ocu_ChannelType ChannelNumber
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Ocu_EnableNotification(channel) \
                                     (ERROR_Ocu_EnableNotification_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
**                                                                            **
** Syntax : void Ocu_DisableNotification(                                     **
**                       const  Ocu_ChannelType ChannelNumber)                **
**                                                                            **
** Description : This service will disable notifications of channel.          **
**                                                                            **
** Service ID:       0x0A                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  ChannelNumber - Numeric identifier of the OCU channel    **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
*******************************************************************************/
#if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
extern void Ocu_DisableNotification
(
  const Ocu_ChannelType ChannelNumber
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Ocu_DisableNotification(channel) \
                                    (ERROR_Ocu_DisableNotification_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
**                                                                            **
** Syntax : void Ocu_SetPinAction( const Ocu_ChannelType ChannelNumber,       **
**                                 const Ocu_PinActionType PinAction)         **
**                                                                            **
** Description : This service will set the pin action to be performed on next **
**               compare match                                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x05                                                     **
*                                                                             **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  ChannelNumber - Numeric identifier of the OCU channel    **
**                   PinAction - Pin action to be performed on next compare   **
**                               match                                        **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
#if (OCU_SET_PIN_ACTION_API == STD_ON)
extern void Ocu_SetPinAction( const Ocu_ChannelType ChannelNumber,
                       const Ocu_PinActionType PinAction);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Ocu_SetPinAction(Channel,PinAction) \
                                           (ERROR_Ocu_SetPinAction_API_IS_NOT_SELECTED)
#endif


/*******************************************************************************
**                                                                            **
** Syntax : void Ocu_SetPinState( const Ocu_ChannelType ChannelNumber,        **
**                                 const Ocu_PinStateType PinAction)          **
**                                                                            **
** Description : This service will set the pin state immediately              **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x04                                                     **
*                                                                             **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  ChannelNumber - Numeric identifier of the OCU channel    **
**                   PinState - Pin state to be set                           **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
#if (OCU_SET_PIN_STATE_API == STD_ON)
extern void Ocu_SetPinState( const Ocu_ChannelType ChannelNumber,
                      const Ocu_PinStateType PinState);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Ocu_SetPinState(Channel,PinState) \
                                            (ERROR_Ocu_SetPinState_API_IS_NOT_SELECTED)
#endif
/*******************************************************************************
**                                                                            **
** Syntax : void Ocu_StartChannel( const Ocu_ChannelType ChannelNumber)       **
**                                                                            **
** Description : This service will start the OCU channel                      **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x02                                                     **
*                                                                             **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  ChannelNumber - Numeric identifier of the OCU channel    **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
extern void Ocu_StartChannel( const Ocu_ChannelType ChannelNumber);

/*******************************************************************************
**                                                                            **
** Syntax : void Ocu_StopChannel( const Ocu_ChannelType ChannelNumber)        **
**                                                                            **
** Description : This service will stop the OCU channel                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x03                                                     **
*                                                                             **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  ChannelNumber - Numeric identifier of the OCU channel    **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
extern void Ocu_StopChannel( const Ocu_ChannelType ChannelNumber);


/*******************************************************************************
**                                                                            **
** Syntax : Ocu_ValueType Ocu_GetCounter( const Ocu_ChannelType ChannelNumber)**
**                                                                            **
** Description : This service will return current counter value               **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x06                                                     **
*                                                                             **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  ChannelNumber - Numeric identifier of the OCU channel    **
**                                                                            **
** Parameters (out): Ocu_ValueType - Counter value                            **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
#if (OCU_GET_COUNTER_API == STD_ON)
extern Ocu_ValueType Ocu_GetCounter( const Ocu_ChannelType ChannelNumber);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Ocu_GetCounter(Channel)              (ERROR_Ocu_GetCounter_API_IS_NOT_SELECTED)
#endif


/*******************************************************************************
**                                                                            **
** Syntax : Ocu_ValueType Ocu_SetAbsoluteThreshold(                           **
**                                   const Ocu_ChannelType ChannelNumber,     **
**                                   const Ocu_ValueType ReferenceValue,      **
**                                   const Ocu_ValueType AbsoluteValue )      **
**                                                                            **
** Description : This service will set the threshold using the absolute values**
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x07                                                     **
*                                                                             **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the OCU channel          **
**                   ReferenceValue - Reference to identify if the compare    **
**                                    match occurs in the given interval      **
**                   AbsoluteValue - new compare value                        **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     Ocu_ReturnType - to indicate if the compare match occurs **
**                                    in this cycle.                          **
**                                                                            **
*******************************************************************************/
#if (OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON)
extern Ocu_ReturnType Ocu_SetAbsoluteThreshold( const Ocu_ChannelType ChannelNumber,
    const Ocu_ValueType ReferenceValue, const Ocu_ValueType AbsoluteValue );
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Ocu_SetAbsoluteThreshold(ChannelNumber,ReferenceValue,AbsoluteValue)\
                                   (ERROR_Ocu_SetAbsoluteThreshold_API_IS_NOT_SELECTED)
#endif


/*******************************************************************************
**                                                                            **
** Syntax : Ocu_ValueType Ocu_SetRelativeThreshold(                           **
**                                   const Ocu_ChannelType ChannelNumber,     **
**                                   const Ocu_ValueType RelativeValue )      **
**                                                                            **
** Description : This service will set the threshold using the absolute values**
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x08                                                     **
*                                                                             **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the OCU channel          **
**                   RelativeValue - Relative threshold w.r.t. current counter**
**                   value.                                                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     Ocu_ReturnType - to indicate if the compare match occurs **
**                                    in this cycle.                          **
**                                                                            **
*******************************************************************************/
#if (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)
extern Ocu_ReturnType Ocu_SetRelativeThreshold( const Ocu_ChannelType ChannelNumber,
    const Ocu_ValueType RelativeValue );
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Ocu_SetRelativeThreshold(ChannelNumber,RelativeValue)\
                                   (ERROR_Ocu_SetRelativeThreshold_API_IS_NOT_SELECTED)
#endif


#if (OCU_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Syntax :          void Ocu_GetVersionInfo (                                **
**                                Std_VersionInfoType* const versioninfo)     **
**                                                                            **
** Service ID:       0x12                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  None                                                     **
**                                                                            **
** Parameters (out): versioninfo : Pointer to hold the version values         **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description : 1. This service will return the version infos of OCU driver  **
*******************************************************************************/
extern void Ocu_GetVersionInfo(
  Std_VersionInfoType* const versioninfo);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Ocu_GetVersionInfo(versioninfo)      \
                                       (ERROR_Ocu_GetVersionInfo_API_IS_NOT_SELECTED)
#endif

#if(OCU_INITCHECK_API == STD_ON)
/*******************************************************************************
** Traceability : [cover parentID=]                                           **
**                                                                            **
** Syntax : Std_ReturnType Ocu_InitCheck(                                     **
**                const Ocu_ConfigType *ConfigPtr )                           **
**                                                                            **
** Service ID      :    None                                                  **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Non Reentrant                                         **
**                                                                            **
** Parameters (in) :    ConfigPtr - Pointer to OCU Driver configuration set   **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    E_OK - if initialization comparison is success        **
**                      E_NOT_OK - if initialization comparison fails         **
**                                                                            **
** Description     : This routine verifies the initialization of OCU driver.  **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Ocu_InitCheck
(const Ocu_ConfigType* const ConfigPtr);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Ocu_InitCheck(ConfigPtr) \
        (ERROR_Ocu_InitCheck_API_IS_NOT_SELECTED)
#endif

#define OCU_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Ocu_MemMap.h"

#include "Ocu_PBcfg.h"


#endif /* OCU_H */
