#ifndef ICU_17_TIMERIP_H
#define ICU_17_TIMERIP_H

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
**  FILENAME     : Icu_17_TimerIp.h                                           **
**                                                                            **
**  VERSION      : 25.0.0                                                     **
**                                                                            **
**  DATE         : 2020-10-05                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID={8D374FAB-7082-46e8-8E66-94AE4D49F842}]    **
**                                                                            **
**  DESCRIPTION  : Icu Driver header definition file                          **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Icu Driver Header file                                 **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* [cover parentID={309926DF-2467-4678-91A2-6C4280D1DB26}] */
/* Imported Types */
/*  [/cover] */
/* Inclusion of Platform_Types.h and Compiler.h */
#include "Std_Types.h"

 #include "McalLib.h"
/*Icu Configuration File*/
#include "Icu_17_TimerIp_Cfg.h"

#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
#include "IfxGtm_bf.h"
#endif
#if (ICU_17_TIMERIP_GPT12_USED == STD_ON)
#include "IfxGpt12_bf.h"
#endif
/* Check for Report wakeup Source  */
#if (ICU_17_TIMERIP_REPORT_WAKEUP_SOURCE == STD_ON)
/* Include Ecu State Manager header file */
#include "EcuM.h"
#if (MCAL_AR_VERSION == MCAL_AR_422)
#include "EcuM_Cbk.h"
#else
#include "EcuM_Externals.h"
#endif
#endif

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/* [cover parentID={4669E3B6-CF32-45e9-84E9-0E51CB80F811}] */
/*
  Published parameters
*/
/* ICU Vendor ID - Vendor ID of the dedicated implementation of this
module according to the AUTOSAR vendor list */
#define ICU_17_TIMERIP_VENDOR_ID     ((uint16)17)
/*ICU Module ID - Module ID of this module from Module List */
#define ICU_17_TIMERIP_MODULE_ID     ((uint16)122)
/*  [/cover] */

#define ICU_17_TIMERIP_MCAL_SUPERVISOR                 (0U)

#define ICU_17_TIMERIP_MCAL_USER1                      (1U)

#if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
(ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
/*
    Development error values
    Development error values are of type uint8
    Development error list
*/
/* API service called with invalid pointer */
/* [cover parentID={D00EFDD8-9824-43b9-A68D-590B8144D6D6}] */
#define ICU_17_TIMERIP_E_PARAM_POINTER        ((uint8)0x0A)
/*  [/cover] */
/* API service used with an invalid channel Identifier  */
/* [cover parentID={B699913A-4725-4926-BB85-F12F7E9F8F8C}] */
#define ICU_17_TIMERIP_E_PARAM_CHANNEL        ((uint8)0x0B)
/*  [/cover] */
/* API service used with an invalid or not feasible Activation */
/* [cover parentID={07F18F3F-35EC-4a8b-BB2B-BB7ABC84E732}] */
#define ICU_17_TIMERIP_E_PARAM_ACTIVATION     ((uint8)0x0C)
/*  [/cover] */
/* API Service used with NULL  pointer */
/* [cover parentID={CF91E6D5-10F8-40ec-B874-051A3841C324}] */
#define ICU_17_TIMERIP_E_INIT_FAILED          ((uint8)0x0D)
/*  [/cover] */
/* API Service used with an invalid size (size =0) */
/* [cover parentID={8D8FBFEC-C665-4b47-9B3A-1CE81922EA3E}] */
#define ICU_17_TIMERIP_E_PARAM_BUFFER_SIZE    ((uint8)0x0E)
/*  [/cover] */
/* API Service Icu_17_TimerIp_SetMode used with an invalid mode value */
/* [cover parentID={7B7FFF4D-F3E7-4b2a-A9CD-4A8633F2D1F4}] */
#define ICU_17_TIMERIP_E_PARAM_MODE           ((uint8)0x0F)
/*  [/cover] */
/* API service used without module initialization */
/* [cover parentID={8F8E0703-C0F8-42c7-B279-8F3241C596EA}] */
#define ICU_17_TIMERIP_E_UNINIT               ((uint8)0x14)
/*  [/cover] */
/* API Service Icu_17_TimerIp_SetMode is called when an running operation is
 ongoing */
/* [cover parentID={1805AE2B-643E-462f-8F6E-CB3F42AA01D7}] */
#define ICU_17_TIMERIP_E_BUSY_OPERATION       ((uint8)0x16)
/*  [/cover] */
/* Init function: Icu_17_TimerIp_Init called while driver already initialized */
/* [cover parentID={A7CA9B8F-6C28-45e3-A437-30920F538D96}] */
#define ICU_17_TIMERIP_E_ALREADY_INITIALIZED  ((uint8)0x17)
/*  [/cover] */
/* Init function: Icu_17_TimerIp_StartTimeStamp called with parameter
NotifyInterval is invalid (e.g. NotifyInterval < 1) */
/* [cover parentID={24D992E9-C045-456f-A039-2D60E25C27D2}] */
#define ICU_17_TIMERIP_E_PARAM_NOTIFY_INTERVAL ((uint8)0x18)
/*  [/cover] */
/* Init function: Icu_17_TimerIp_GetVersionInfo called with a parameter
NULL_PTR */
/* [cover parentID={C143E5D7-D720-48dd-9C6D-1DE8F87DBCD0}] */
#define ICU_17_TIMERIP_E_PARAM_VINFO          ((uint8)0x19)
/*  [/cover] */


#if (ICU_17_TIMERIP_SAFETY_ENABLE  == STD_ON)
/* Function 'Icu_17_TimerIp_SetMode' called to SLEEP without IRQ enabled
for any wakeup channel. This is added as Safety measure before putting
ICU to SLEEP */
#define ICU_17_TIMERIP_E_NO_WAKEUP           ((uint8)0x20)

/* In Icu_17_TimerIp_Init function CCU6 clock
   initiization is failed */
#define ICU_17_TIMERIP_E_PARAM_CLC_ERROR     ((uint8)0x35)

/* Error reporting in case of unexpected triggering of
   service requests or call of a wrong ISR  */
#define ICU_17_TIMERIP_E_INTR_SRC_ERROR     ((uint8)0x36)

#endif
/* Icu_17_TimerIp_EnableMultiEdgeDetection called with a
  EdgeCount parameter as zero */
/* [cover parentID={D73A414A-D9D2-4300-9218-33E19EC7819E}] */
#define ICU_17_TIMERIP_E_PARAM_EDGE_NUMBER   ((uint8)0x21)

/* Slave Core Init called before Master Core's Init */
/* [cover parentID={A20E41F2-6B84-42a6-A9DA-4D93097374DB}] */
#define ICU_17_TIMERIP_E_MASTER_CORE_UNINIT       ((uint8)0x66)
/*  [/cover] */
/* Master Core De-Init called before all slave core De-Init */
/* [cover parentID={27E985F9-E9C3-453e-9BF0-0F3F5EB1FB07}] */
#define ICU_17_TIMERIP_E_SLAVE_CORE_INIT          ((uint8)0x67)
/*  [/cover] */
/* Init called for non configured core */
#define ICU_17_TIMERIP_E_CORE_NOT_CONFIGURED      ((uint8)0x64)
/* Channel not allocated for current core. */
/* [cover parentID={93789F01-0931-420c-B25B-028115803A71}] */
#define ICU_17_TIMERIP_E_CORE_CHANNEL_MISMATCH      ((uint8)0x65)
/*  [/cover] */
#if (ICU_17_TIMERIP_SAFETY_ENABLE  == STD_ON)
/*  function: ISR invoked on a spurious interrupt.*/
/* [cover parentID=] */
#define ICU_17_TIMERIP_E_INVALID_ISR            ((uint8)0xC9)
/*  [/cover] */
/*  function: Counter of edge count channel overflowed.*/
/* [cover parentID=] */
#define ICU_17_TIMERIP_E_EDGE_COUNTER_OVERFLOW  ((uint8)0xC8)
/*  [/cover] */
/*  function: ICU Api, to start a activity, invoked in sleep mode..*/
/* [cover parentID=] */
#define ICU_17_TIMERIP_E_INVALID_MODE            ((uint8)0xCA)
/*  [/cover] */
/*  function: Notification invoked on a non- notification
 *            function configured channel.*/
/* [cover parentID=] */
#define ICU_17_TIMERIP_E_INVALID_NOTIF           ((uint8)0xCB)
/*  [/cover] */
/*  function: SetactivationCondition called on an active time stamping channel*/
/* [cover parentID={8771FCBE-5FDA-4542-B218-9CBB3BC36C7A}] */
#define ICU_17_TIMERIP_E_BUSY_CHANNEL           ((uint8)0xCC)
/*  [/cover] */

/*  function: Notify interval is greater than buffer size in case of a Linear 
              buffer */
/* [cover parentID={8FD16294-B7EE-4e00-842F-81525E436955}] */
#define ICU_17_TIMERIP_E_PARAM_IMPLAUSIBLE_NOTIFY_INTERVAL     ((uint8)0xCD)
/*  [/cover] */

/* [cover parentID={4B80CF73-E445-4e45-A4F6-0CCCD54655E8}] */
#define ICU_17_TIMERIP_E_PARAM_TIMEOUT    ((uint8)0xCE)
/*  [/cover] */

#endif

/* API Service ID's */
/* API Service ID for Icu_17_TimerIp_Init() */
#define ICU_17_TIMERIP_SID_INIT                              ((uint8)0x00)
/* API Service ID for Icu_17_TimerIp_DeInit() */
#define ICU_17_TIMERIP_SID_DEINIT                            ((uint8)0x01)
/* API Service ID for Icu_17_TimerIp_SetMode() */
#define ICU_17_TIMERIP_SID_SETMODE                           ((uint8)0x02)
/* API Service ID for Icu_17_TimerIp_DisableWakeup() */
#define ICU_17_TIMERIP_SID_DISABLEWAKEUP                     ((uint8)0x03)
/* API Service ID for Icu_17_TimerIp_EnableWakeup() */
#define ICU_17_TIMERIP_SID_ENABLEWAKEUP                      ((uint8)0x04)
/* API Service ID for Icu_17_TimerIp_SetActivationCondition() */
#define ICU_17_TIMERIP_SID_SETACTIVATIONCONDITION            ((uint8)0x05)
/* API Service ID for Icu_17_TimerIp_DisableNotification() */
#define ICU_17_TIMERIP_SID_DISABLENOTIFICATION               ((uint8)0x06)
/* API Service ID for Icu_17_TimerIp_EnableNotification() */
#define ICU_17_TIMERIP_SID_ENABLENOTIFICATION                ((uint8)0x07)
/* API Service ID for Icu_17_TimerIp_GetInputState() */
#define ICU_17_TIMERIP_SID_GETINPUTSTATE                     ((uint8)0x08)
/* API Service ID for Icu_17_TimerIp_StartTimestamp() */
#define ICU_17_TIMERIP_SID_STARTTIMESTAMP                    ((uint8)0x09)

/* API Service ID for Icu_17_TimerIp_GetTimestampIndex() */
#define ICU_17_TIMERIP_SID_GETTIMESTAMPINDEX                 ((uint8)0x0B)
/* API Service ID for Icu_17_TimerIp_ResetEdgeCount() */
#define ICU_17_TIMERIP_SID_RESETEDGECOUNT                    ((uint8)0x0C)
/* API Service ID for Icu_17_TimerIp_EnableEdgeCount() */
#define ICU_17_TIMERIP_SID_ENABLEEDGECOUNT                   ((uint8)0x0D)
/* API Service ID for Icu_17_TimerIp_DisableEdgeCount() */
#define ICU_17_TIMERIP_SID_DISABLEEDGECOUNT                  ((uint8)0x0E)
/* API Service ID for Icu_17_TimerIp_GetEdgeNumbers() */
#define ICU_17_TIMERIP_SID_GETEDGENUMBERS                    ((uint8)0x0F)
/* API Service ID for Icu_17_TimerIp_GetTimeElapsed() */
#define ICU_17_TIMERIP_SID_GETTIMEELAPSED                    ((uint8)0x10)
/* API Service ID for Icu_17_TimerIp_GetDutyCycleValues() */
#define ICU_17_TIMERIP_SID_GETDUTYCYCLEVALUES                ((uint8)0x11)
/* API Service ID for Icu_17_TimerIp_GetVersionInfo */
#define ICU_17_TIMERIP_SID_GETVERSIONINFO                    ((uint8)0x12)
/* API Service ID for Icu_17_TimerIp_StartSignalMeasurement */
#define ICU_17_TIMERIP_SID_STARTSIGNALMEASUREMENT            ((uint8)0x13)
/* API Service ID for Icu_17_TimerIp_StopSignalMeasurement */
#define ICU_17_TIMERIP_SID_STOPSIGNALMEASUREMENT             ((uint8)0x14)
/* API Service ID for Icu_17_TimerIp_CheckWakeup */
#define ICU_17_TIMERIP_SID_CHECKWAKEUP                       ((uint8)0x15)
/* API Service ID for Icu_17_TimerIp_EnableEdgeDetection */
#define ICU_17_TIMERIP_SID_ENABLEEDGEDETECTION               ((uint8)0x16)
/* API Service ID for Icu_17_TimerIp_DisableEdgeDetection */
#define ICU_17_TIMERIP_SID_DISABLEEDGEDETECTION              ((uint8)0x17)
/* API Service ID for Icu_17_TimerIp_EnableMultiEdgeDetection */
#define ICU_17_TIMERIP_SID_ENABLEMULTIEDGEDETECTION          ((uint8)0x19)
/* API Service ID for TimerIp Isr*/
#define ICU_17_TIMERIP_SID_ISR                               ((uint8)0x20)
/* API Service ID for Icu_17_TimerIp_StartIncInterface */
#define ICU_17_TIMERIP_SID_START_INC_INTERFACE               ((uint8)0x21)
/* API Service ID for Icu_17_TimerIp_StopIncInterface */
#define ICU_17_TIMERIP_SID_STOP_INC_INTERFACE                ((uint8)0x22)
/* API Service ID for Icu_17_TimerIp_CalibratePos */
#define ICU_17_TIMERIP_SID_CALIBRATE_POS                     ((uint8)0x23)
/* API Service ID for Icu_17_TimerIp_ReadEncCount */
#define ICU_17_TIMERIP_SID_READ_ENC_COUNT                    ((uint8)0x24)
/* API Service ID for Icu_17_TimerIp_ReadEncCountDir */
#define ICU_17_TIMERIP_SID_READ_ENC_DIR                      ((uint8)0x25)

#define ICU_17_TIMERIP_SID_SETTIMEOUTVALUE                   ((uint8)0x26)
#endif

#if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON) || \
    (ICU_17_TIMERIP_RUNTIME_ERROR_DETECT == STD_ON) || \
    ((ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON))
/* API Service Called to measure when the required service was not started */
/* [cover parentID={BC7F5587-FAB7-4174-888E-F6A3AC1C6F28}] */
#define ICU_17_TIMERIP_E_NOT_STARTED          ((uint8)0x15)
/*  [/cover] */
/* API Service ID for Icu_17_TimerIp_StopTimestamp() */
#define ICU_17_TIMERIP_SID_STOPTIMESTAMP                     ((uint8)0x0A)
#endif

/* ICU options chosen */
#define ICU_17_TIMERIP_GTM_OPTION           (0UL)
#define ICU_17_TIMERIP_ERU_OPTION           (1UL)
#define ICU_17_TIMERIP_CCU_OPTION           (2UL)
#define ICU_17_TIMERIP_GPT12_OPTION         (3UL)

/* TIM Enable */
#define ICU_GTM_TIM_ENABLE_CHANNEL ((uint32)1UL)
#define ICU_GTM_TIM_MODE_TIPM  (3UL)
#define ICU_GTM_TIM_MODE_TIEM  (2UL)
#define ICU_GTM_TIM_MODE_TPWM  (0UL)
#define ICU_ERU_EXIS_CHNL_BIT_POS (0x3U)
#define ICU_ERU_OGU_CHNL_BIT_POS (0x6U)

/* maximum number of cores supported by ICU */
#define ICU_17_TIMERIP_MAX_CORES 6
/* Maximum number of ERU supported by ICU */
#define ICU_17_TIMERIP_TOTAL_ERU_CHANNELS 8
/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/* [cover parentID={6065CFC0-E659-4e8e-A8CD-FAC9DB1C3873}] */
typedef enum
{
  /* Normal operation, all used interrupts are enabled according to the
  notification requests */
  ICU_17_TIMERIP_MODE_NORMAL = 0U,
  /* Operation for reduced power operation mode. In Wake-up mode only those
  notifications are available which are configured as wake-up capable */
  ICU_17_TIMERIP_MODE_SLEEP = 1U
} Icu_17_TimerIp_ModeType;
/*  [/cover] */
/* [cover parentID={A69F117B-245D-4a94-9824-F54993922A9B}] */
/* Numeric identifier of a ICU channel */
typedef uint8 Icu_17_TimerIp_ChannelType;
/*  [/cover] */
/* [cover parentID={458E7B6C-4314-4620-B14E-2797DEB662C0}] */
typedef enum
{
  /* No activation edge has been detected since the last call of
  Icu_17_TimerIp_GetInputState() or Icu_17_TimerIp_Init().*/
  ICU_17_TIMERIP_IDLE = 0U,
  /* An activation edge has been detected by an ICU*/
  ICU_17_TIMERIP_ACTIVE = 1U
} Icu_17_TimerIp_InputStateType;
/*  [/cover] */
/* [cover parentID={249882F7-69B3-4220-B888-F204514BE640}] */
/* Activations to be used for all kinds of measurement */
/* ICU_17_TIMERIP_FALLING_EDGE, ICU_17_TIMERIP_RISING_EDGE,
   ICU_17_TIMERIP_BOTH_EDGES are the possible values*/
typedef enum
{
  /*Activation of configuration will be started when a rising edge occurs on the
  ICU input signal.*/
  ICU_17_TIMERIP_RISING_EDGE = 0U,
  /* Activation of edges  will be started when a falling edge occurs on the
   ICU input signal */
  ICU_17_TIMERIP_FALLING_EDGE = 1U,
  /* Activation of configuration on both  rising edge or falling edge occur on
   the ICU input signal (any kind of edges) */
  ICU_17_TIMERIP_BOTH_EDGES = 2U,
  ICU_17_TIMERIP_NO_EDGE = 3U
} Icu_17_TimerIp_ActivationType;
/*  [/cover] */
/* [cover parentID={04BF5403-A6BB-4900-A643-0AF74C652886}] */
/*Icu_17_TimerIp_ValueType is used for the widest timer */
typedef uint32 Icu_17_TimerIp_ValueType;
/*  [/cover] */
/* [cover parentID={6CEFC407-FDD5-4b88-9729-609F9116328F}] */
/*
  The following structure is used in Icu_17_TimerIp_GetDutyCycle_Values API.
*/
typedef struct
{
  /* To store ActiveTime for GetDutyCycles API.*/
  Icu_17_TimerIp_ValueType  ActiveTime;
  /* To store PeriodTime for GetDutyCycles API.*/
  Icu_17_TimerIp_ValueType  PeriodTime;
} Icu_17_TimerIp_DutyCycleType;
/*  [/cover] */
/* [cover parentID={239541D6-33BE-4b95-A033-0BA6B5810A7A}] */
/*
 Icu_Index type is used in Timestamp Measurement . A maximum of 16 bits
 could be used here, as the Buffer size cannot go beyond 65535
*/
typedef uint16 Icu_17_TimerIp_IndexType;
/*  [/cover] */
/* [cover parentID={4A488C5C-958B-4895-AED7-C04EC30559EA}] */
/* Icu_EdgeNumbertype is used in Edge Count API's.
   Value of this type shall be returned to the caller on
   Icu_17_TimerIp_GetEdgeNumbers
*/
typedef uint32 Icu_17_TimerIp_EdgeNumberType;
/*  [/cover] */

/* [cover parentID={B8ACC6FF-1192-41c1-A41B-9F60A2824C4B}] */
/* The following type informs the type of measurement mode to be used */
/*
   The following values are possible
   ICU_MODE_SIGNAL_EDGE_DETECT,
   ICU_17_TIMERIP_MODE_SIGNAL_MEASUREMENT,
   ICU_MODE_TIMESTAMP
   ICU_MODE_EDGE_COUNTER */
typedef enum
{
  ICU_17_TIMERIP_MODE_SIGNAL_EDGE_DETECT = 0U,
  ICU_17_TIMERIP_MODE_SIGNAL_MEASUREMENT = 1U,
  ICU_17_TIMERIP_MODE_TIMESTAMP = 2U,
  ICU_17_TIMERIP_MODE_EDGE_COUNTER = 3U,
  ICU_17_TIMERIP_MODE_INCREMENTAL_INTERFACE = 4U
} Icu_17_TimerIp_MeasurementModeType;
/*  [/cover] */
/* [cover parentID={9B93291E-9F14-4a97-B3B6-442629CD595E}] */
/* The following modes are possible
   if MeasurementModeType is ICU_17_TIMERIP_MODE_SIGNAL_MEASUREMENT
   ICU_LOW_TIME
   ICU_HIGH_TIMER
   ICU_PERIODTIME
   ICU_17_TIMERIP_ACTIVE_TIME/ICU_DUTY_CYCLE*/
typedef enum
{
  ICU_17_TIMERIP_LOW_TIME = 0U,
  ICU_17_TIMERIP_HIGH_TIME = 1U,
  ICU_17_TIMERIP_PERIOD_TIME = 2U,
  ICU_17_TIMERIP_DUTY_CYCLE = 3U
} Icu_17_TimerIp_SignalMeasurementPropertyType;
/*  [/cover] */
/* [cover parentID={7CDF5EBA-065C-4fb3-B246-D05662F3CDB8}] */
/*TimeStamp Types */
/*
 The following modes are possible
 if MeasurementModeType is ICU_17_TIMERIP_MODE_TIMESTAMP 
 ICU_17_TIMERIP_LINEAR_BUFFER,
 ICU_17_TIMERIP_CIRCULAR_BUFFER */
typedef enum
{
  ICU_17_TIMERIP_LINEAR_BUFFER = 0U,
  ICU_17_TIMERIP_CIRCULAR_BUFFER = 1U
} Icu_17_TimerIp_TimestampBufferType;
/*  [/cover] */
/* [cover parentID={E97AF4C5-748F-487c-A6CC-63481EC0A690}] */
/* To provide Notification the following type will be used */
typedef void (*Icu_17_TimerIp_NotifiPtrType)(void);
/*  [/cover] */
/* [cover parentID={65C4ECFD-22C2-44d4-B2A2-D2B0F26FF2D7}] */
/* Incremental Interface mode Types */
/* 
 The following modes are possible 
 if MeasurementModeType is ICU_17_TIMERIP_MODE_INCREMENTAL_INTERFACE 
 ICU_17_TIMERIP_1_COUNT_INPUT, 
 ICU_17_TIMERIP_2_COUNT_INPUT */
typedef enum
{
  ICU_17_TIMERIP_1_COUNT_INPUT = 1U,
  ICU_17_TIMERIP_2_COUNT_INPUT = 3U
} Icu_17_TimerIp_IncrementType;
/*  [/cover] */
/* [cover parentID={40536106-D831-44a4-9F1C-CAE1F508C303}] */
/* Incremental Interface mode Count direction Type */
/* 
 The following Count direction are possible 
 ICU_17_TIMERIP_ENC_COUNT_UP, 
 ICU_17_TIMERIP_ENC_COUNT_DOWN */
typedef enum
{
  ICU_17_TIMERIP_ENC_COUNT_UP = 0U,
  ICU_17_TIMERIP_ENC_COUNT_DOWN = 1U
} Icu_17_TimerIp_EncCountDirType;
/*  [/cover] */
/* INTERNAL DATA TYPES */
/*******************************************************************************
**                      Internal Type Definitions                             **
*******************************************************************************/
/* [cover parentID={CFF1C6E9-2417-4aa5-A7B4-75F7CD450038}] */
#if (ICU_17_TIMERIP_REPORT_WAKEUP_SOURCE == STD_ON)
/*
  Wakeup Capable Channels
*/
/* Container for wakeup channels */
typedef struct
{
  /* The following parameter will be used to provide the wakeup reason value.
    The type EcuM_WakeupSourceType should have been declared in Ecum.h      */
  EcuM_WakeupSourceType EcuMWakeupInfo;
} Icu_17_TimerIp_ChannelWakeupType;
#endif
/*  [/cover] */
/* [cover parentID={83841952-7095-454b-A320-1ED9B2F6065F}] */
/* The definition for each Channel  */
/* container for channel configuration */
/* The following struct type is channel dependent configuration */
typedef struct
{
  /* The callback notifications shall be configurable as function
     pointers within the initialization data structure */
  /* The following parameter is a function pointer to provide notification */
  /* This should have a valid function and they make sense for the following
     modes ICU_MODE_SIGNAL_EDGE_DETECT and ICU_MODE_TIMESTAMP
      The functions will be called from ISR after the following events
      ICU_MODE_SIGNAL_EDGE_DETECT -> after Icu_EnableNotification
      ICU_MODE_TIMESTAMP         -> enabled by Icu_EnableNotification and
      Icu_StartTimeStamp with NotifyInterval more than 0.
  */
  Icu_17_TimerIp_NotifiPtrType NotificationPointer;
  Icu_17_TimerIp_NotifiPtrType TimeOutNotificationPointer;
  Icu_17_TimerIp_NotifiPtrType CntOvflNotificationPointer;
  /* measurement property struct  */
  struct
  {
    /* Measurement Mode of the channel */
    unsigned_int     MeasurementMode : 3;
    /* Default start edge, ICU_17_TIMERIP_RISING_EDGE,ICU_17_TIMERIP_FALLING_EDGE and
     ICU_17_TIMERIP_BOTH_EDGES*/
    unsigned_int      DefaultStartEdge: 2;
    /* Measurement Property for incremental interface mode, time stamp capture 
       and signal measurement */
    unsigned_int      MeasurementProperty: 2;
    /* The following parameter informs whether the channel is
      wakeup capable or not */
    unsigned_int      WakeupCapability: 1;
    /* resource number */
    unsigned_int      AssignedHwUnitNumber: 16;
    /*
    * MCU dependent properties for used HW units
      Icu Assigned Hw Unit for the measurement
      0 -> ICU_17_TIMERIP_GTM_OPTION
      1 -> ICU_17_TIMERIP_ERU_OPTION
      2 -> ICU_17_TIMERIP_CCU_OPTION
      3 -> ICU_17_TIMERIP_GPT12_OPTION
    */
    unsigned_int      AssignedHwUnit: 2;
    /* CCU6 Port connections */
    unsigned_int      PinSelection: 4;
    /* parameter to store if the timeout is enabled */
    unsigned_int      TimeOutEnabled: 1;
    /* parameter to store if the timeout is exclusive or mixed */
    unsigned_int      IsTimeOutExclusive: 1;
    /* Filtering time for rising edge */
    uint32 TimChFilterTimeForRisingEdge;
    /* Filtering time for falling edge */
    uint32 TimChFilterTimeForFallingEdge;
    /* Threshold to identify the overflow ISR of previous signal phase.*/
    uint32 OverflowISRThreshold;
    /* Filtering time for TIM interrupt mode */
    uint16 InterruptMode;
    /*Channel Clock Select */
    uint8 TimChannelClockSelect;
    /* HW CONTROL register data*/
    uint32 CTRLData;
    /* TIM channel ECTRL register data*/
    uint32 TimECTRLData;
    /* TIM channel TDUV register data*/
    uint32 TimTDUVData;
  } IcuProperties;
  #if (ICU_17_TIMERIP_REPORT_WAKEUP_SOURCE == STD_ON)
  /* Pointer to channel wakeup information */
  Icu_17_TimerIp_ChannelWakeupType ChannelWakeupInfo;
  #endif
  uint8 ModeMappingIndex;
} Icu_17_TimerIp_ChannelConfigType;
/*  [/cover] */
/* [cover parentID={881B1E21-8085-404b-9170-3601E5FD94DB}] */
/*Icu_17_TimerIp_ConfigTypeCore struct*/
typedef struct
{
  /* Pointer to Channel Configuration structure */
  const Icu_17_TimerIp_ChannelConfigType* ChannelConfigPtr;
  /* Max channels defined per core.*/
  Icu_17_TimerIp_ChannelType MaxChannelCore;
  /* Max Data channel channels defined per core.*/
  Icu_17_TimerIp_ChannelType MaxDataChannelCore;
} Icu_17_TimerIp_CoreConfigType;
/*  [/cover] */
/* [cover parentID={BFE9D051-E2BC-41f2-BEA4-543738AC2D48}] */
/*Icu_17_TimerIp_ConfigType struct*/
typedef struct
{
  /* Pointer to Core Configuration structure */
  const Icu_17_TimerIp_CoreConfigType * CoreConfig[ICU_17_TIMERIP_MAX_CORES];
  #if (ICU_17_TIMERIP_SINGLE_CORE == STD_OFF)
  /* Mapping between global logical identifier to core specific logical
     identifier. 16 bit value - lower 8bit(assuming there will be less than 256
     channels) for identifier.upper 8bit to identify which core is using that
     identifier.*/
  const uint16 ChannelMapping[ICU_17_TIMERIP_MAX_CHANNELS];
  #endif
} Icu_17_TimerIp_ConfigType;
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

#define ICU_17_TIMERIP_START_SEC_CODE_ASIL_B_GLOBAL

#include "Icu_17_TimerIp_MemMap.h"

/*******************************************************************************
**                                                                            **
** Syntax : void Icu_17_TimerIp_Init(const Icu_17_TimerIp_ConfigType          **
**                                                     *const ConfigPtr )     **
** Description : Driver Module Initialization                                 **
**               1.This function will initialize all relevant registers of    **
**               configured hardware (AssignedHWUnit) with the values of      **
**               structure referenced by the parameter ConfigPtr.             **
**               2. This service will disable all notifications.              **
**               3. Resources that are not configured in the configuration    **
**                  file will not be changed.                                 **
**               4. All ICU channel status is set to ICU_17_TIMERIP_IDLE      **
**               5. All used registers used by configuration will be          **
**                  initialized if Reset and Deinit API will not reset the    **
**                  registers                                                 **
**               6. Clearing of pending interrupt flags not done in this      **
**                  function.                                                 **
**               7. After initialization the mode is set to                   **
**                  ICU_17_TIMERIP_MODE_NORMAL                                **
**                                                                            **
** Service ID:      0x00                                                      **
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
extern void Icu_17_TimerIp_Init
(
  const Icu_17_TimerIp_ConfigType *const ConfigPtr
);

#if(ICU_17_TIMERIP_INITCHECK_API == STD_ON)
/*******************************************************************************
** Traceability : [cover parentID=]                                           **
**                                                                            **
** Syntax : Std_ReturnType Icu_17_TimerIp_InitCheck(                          **
**                const Icu_17_TimerIp_ConfigType *ConfigPtr )                **
**                                                                            **
** Service ID      :    None                                                  **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Non-Reentrant                                         **
**                                                                            **
** Parameters (in) :    ConfigPtr - Pointer to ICU Driver configuration set   **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    E_OK - if initialization comparison is success        **
**                      E_NOT_OK - if initialization comparison fails         **
**                                                                            **
** Description     : This routine verifies the initialization of ICU driver.  **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Icu_17_TimerIp_InitCheck
(const Icu_17_TimerIp_ConfigType* const ConfigPtr);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Icu_17_TimerIp_InitCheck(ConfigPtr) \
        ERROR_Icu_17_TimerIp_InitCheck_API_IS_NOT_SELECTED
#endif

/*******************************************************************************
**                                                                            **
** Syntax : void Icu_17_TimerIp_DeInit(void)                                  **
**                                                                            **
** Description : Service for ICU De-Initialization                            **
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
#if (ICU_17_TIMERIP_DE_INIT_API == STD_ON)
extern void Icu_17_TimerIp_DeInit
(
  void
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Icu_17_TimerIp_DeInit() ERROR_Icu_17_TimerIp_DeInit_API_IS_NOT_SELECTED
#endif

/*******************************************************************************
**                                                                            **
** Syntax : void Icu_17_TimerIp_SetMode(Icu_17_TimerIp_ModeType const Mode)   **
**                                                                            **
** Description : Service for ICU mode selection                               **
**               1.This service will set the operation mode to the given mode **
**                 parameter.                                                 **
**               2.In ICU_17_TIMERIP_MODE_NORMAL mode all notifications are   **
**                 available as configured and selected by the                **
**                 Icu_17_TimerIp_DisableNotification                         **
**                 and Icu_17_TimerIp_EnableNotification services before or   **
**                 after the call of Icu_17_TimerIp_SetMode.                  **
**               3.In ICU_17_TIMERIP_MODE_SLEEP mode only those notifications **
**                 available which are configured as wake-up capable and that **
**                 are not disabled via service Icu_17_TimerIp_DisableWakeup. **
**                 All other interrupts are disabled                          **
**                                                                            **
** Service ID:       0x02                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       non reentrant                                            **
**                                                                            **
** Parameters (in):  Mode : ICU_17_TIMERIP_MODE_NORMAL,                       **
**                          ICU_17_TIMERIP_MODE_SLEEP                         **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
*******************************************************************************/
#if ( ICU_17_TIMERIP_SET_MODE_API == STD_ON)
extern void Icu_17_TimerIp_SetMode
(
  const Icu_17_TimerIp_ModeType Mode
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Icu_17_TimerIp_SetMode(Mode) \
                              ERROR_Icu_17_TimerIp_SetMode_API_IS_NOT_SELECTED
#endif

/*******************************************************************************
**                                                                            **
** Syntax : void Icu_17_TimerIp_DisableWakeup(                                **
**                         const   Icu_17_TimerIp_ChannelType Channel)        **
**                                                                            **
** Description : 1 This service will disable the wake-up capability of single **
**                 ICU channel for the following ICU mode selection(s).       **
**               2.This service is only feasible for ICU channels configured  **
**                 as wake-up capable true.                                   **
**               3.From the call of Icu_17_TimerIp_Init()channel which was    **
**                 configured as wakeup capable by using this service user can**
**                 disable the wakeup capability                              **
**                                                                            **
** Service ID:       0x03                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  Channel : Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
*******************************************************************************/
#if (ICU_17_TIMERIP_DISABLE_WAKEUP_API == STD_ON)
extern void Icu_17_TimerIp_DisableWakeup
(
  const Icu_17_TimerIp_ChannelType Channel
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Icu_17_TimerIp_DisableWakeup(Channel) \
                    ERROR_Icu_17_TimerIp_DisableWakeup_API_IS_NOT_SELECTED
#endif

/*******************************************************************************
**                                                                            **
** Syntax :          void Icu_17_TimerIp_EnableWakeup(                        **
**                         const   Icu_17_TimerIp_ChannelType Channel)        **
**                                                                            **
** Description : 1 This service will re-enable /enable the wake-up capability **
**                 of ICU channel.                                            **
**               2.This service is only feasible for ICU channels configured  **
**                 as wake-up capable true. The signal measurement mode       **
**                 should be ICU_MODE_SIGNAL_EDGE_DETECT.                     **
**               3.From the call of Icu_17_TimerIp_Init() the channel which   **
**                 was configured as wakeup capable and the same capability   **
**                 was disabled by using service                              **
**                 Icu_17_TimerIp_DisableWakeup().                            **
**                                                                            **
** Service ID:       0x04                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant for different channel number                   **
**                                                                            **
** Parameters (in):  Channel : Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
*******************************************************************************/
#if ( ICU_17_TIMERIP_ENABLE_WAKEUP_API == STD_ON)
extern void Icu_17_TimerIp_EnableWakeup(
  const Icu_17_TimerIp_ChannelType Channel);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Icu_17_TimerIp_EnableWakeup(Channel) \
                           ERROR_Icu_17_TimerIp_EnableWakeup_API_IS_NOT_SELECTED
#endif

/*******************************************************************************
**                                                                            **
** Syntax : void Icu_17_TimerIp_SetActivationCondition(                       **
**                        const  Icu_17_TimerIp_ChannelType Channel           **
**                        const  Icu_17_TimerIp_ActivationType Activation)    **
**                                                                            **
** Description : 1 This service will set the required configured edge.        **
**               2.This service is only feasible for ICU channels configured  **
**                 as EdgeDetection,TimeStamp and EdgeCounter.                **
**               3.For Signal Measurement Only DefaultStartEdge to be Used    **
**                                                                            **
** Service ID:       0x05                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                   Activation - ICU_17_TIMERIP_RISING_EDGE                  **
**                                ICU_17_TIMERIP_BOTH_EDGES                   **
**                                ICU_17_TIMERIP_FALLING_EDGE                 **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
*******************************************************************************/

extern void Icu_17_TimerIp_SetActivationCondition
(
  const Icu_17_TimerIp_ChannelType  Channel,
  const Icu_17_TimerIp_ActivationType  Activation
);

/*******************************************************************************
**                                                                            **
** Syntax : void Icu_17_TimerIp_DisableEdgeDetection(                         **
**                              const   Icu_17_TimerIp_ChannelType Channel    **
**                                     )                                      **
** Description : This service will disable the ICU signal edge detection      **
**                channel.                                                    **
**                                                                            **
** Service ID:       0x17                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
**                                                                            **
*******************************************************************************/
#if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
extern void Icu_17_TimerIp_DisableEdgeDetection
(
  const Icu_17_TimerIp_ChannelType Channel
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Icu_17_TimerIp_DisableEdgeDetection(Channel)                           \
                   ERROR_Icu_17_TimerIp_DisableEdgeDetection_API_IS_NOT_SELECTED
#endif
/*******************************************************************************
**                                                                            **
** Syntax : void Icu_17_TimerIp_EnableEdgeDetection(                          **
**                               const  Icu_17_TimerIp_ChannelType Channel)   **
**                                                                            **
** Description : This service will Re enables the ICU signal edge detection   **
**               channel, activation edge depends on either DefaultStartEdge  **
**               Or activation by Icu_17_TimerIp_SetActivationCondition API.  **
**                                                                            **
** Service ID:       0x16                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
*******************************************************************************/
#if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
extern void Icu_17_TimerIp_EnableEdgeDetection
(
  const Icu_17_TimerIp_ChannelType Channel
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Icu_17_TimerIp_EnableEdgeDetection(Channel)                           \
                    ERROR_Icu_17_TimerIp_EnableEdgeDetection_API_IS_NOT_SELECTED
#endif
/*******************************************************************************
** Syntax : void Icu_17_TimerIp_EnableMultiEdgeDetection(                     **
**                               const  Icu_17_TimerIp_ChannelType Channel    **
**                               const  uint32 EdgeCount)                     **
**                                                                            **
** Service ID:  0x19                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  reentrant                                                     **
**                                                                            **
** Parameters (in):  Channel : Numeric identifier of the ICU channel          **
**                   EdgeCount : Number of edges before interrupt occurs      **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:    none                                                      **
**                                                                            **
** Description : This service will Re enables the ICU signal edge detection   **
**               channel, activation edge depends on either DefaultStartEdge  **
**               Or activation by Icu_17_TimerIp_SetActivationCondition API.  **
*******************************************************************************/
#if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
extern void Icu_17_TimerIp_EnableMultiEdgeDetection
(const Icu_17_TimerIp_ChannelType Channel,
 const uint32 EdgeCount);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Icu_17_TimerIp_EnableMultiEdgeDetection(Channel,EdgeCount)             \
               ERROR_Icu_17_TimerIp_EnableMultiEdgeDetection_API_IS_NOT_SELECTED
#endif

/*******************************************************************************
**                                                                            **
** Syntax : void Icu_17_TimerIp_DisableNotification(                          **
**                       const  Icu_17_TimerIp_ChannelType Channel)           **
**                                                                            **
** Description : This service will disable  ICU signal notifications of       **
**               this channel.                                                **
**               This API affects both ICU_MODE_SIGNAL_EDGE_DETECT and        **
**               ICU_MODE_TIMESTAMP Channels.                                 **
**                                                                            **
** Service ID:       0x06                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
*******************************************************************************/
extern void Icu_17_TimerIp_DisableNotification
(
  const Icu_17_TimerIp_ChannelType Channel
);

/*******************************************************************************
**                                                                            **
** Syntax : void Icu_17_TimerIp_EnableNotification(                           **
**                               const  Icu_17_TimerIp_ChannelType Channel)   **
**                                                                            **
** Description : This service will enable the ICU signal notification,        **
**               activation edge depends on either DefaultStartEdge           **
*                Or activation by Icu_17_TimerIp_SetActivationCondition API.  **
**               This API affects both ICU_MODE_SIGNAL_EDGE_DETECT and        **
**               ICU_MODE_TIMESTAMP Channels.                                 **
**                                                                            **
** Service ID:       0x07                                                     **
*                                                                             **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
*******************************************************************************/
extern void Icu_17_TimerIp_EnableNotification
(
  const Icu_17_TimerIp_ChannelType Channel
);

/*******************************************************************************
**                                                                            **
** Syntax :Icu_17_TimerIp_InputStateType Icu_17_TimerIp_GetInputState         **
**                               (const Icu_17_TimerIp_ChannelType Channel)   **
**                                                                            **
** Description : 1. This service returns the status of the ICU input.         **
**               2. If an activation edge has been detected this service will **
**                  return ICU_17_TIMERIP_ACTIVE.                             **
**               3. Once the service has returned the status                  **
**                  ICU_17_TIMERIP_ACTIVE the stored status will be set to    **
**                  ICU_17_TIMERIP_IDLE until the next edge is detected.      **
**               4. If no  edge has been detected this service will           **
**                  return ICU_17_TIMERIP_IDLE.                               **
**               5. If development error detection is enabled and an error is **
**                  detected the service returns ICU_17_TIMERIP_IDLE.         **
**               6. Signal edge detection channels                            **
**                  channels status is changed here.                          **
**               7. For a signal measurement channel only the status          **
**                  is returned and its not put to IDLE. A successful read    **
**                  of Icu_17_TimerIp_GetTimeElapsed or                       **
**                  Icu_17_TimerIp_GetDutyCycleValues                         **
**                  will set the state to ICU_17_TIMERIP_IDLE                 **
**                                                                            **
** Service ID:       0x08                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     Status (Icu_17_TimerIp_InputStateType) -                 **
**                   Returns the state of Channel                             **
**                                                                            **
*******************************************************************************/
#if (ICU_17_TIMERIP_GET_INPUT_STATE_API == STD_ON)
extern Icu_17_TimerIp_InputStateType Icu_17_TimerIp_GetInputState
(
  const Icu_17_TimerIp_ChannelType Channel
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Icu_17_TimerIp_GetInputState(Channel) \
               ERROR_Icu_17_TimerIp_GetInputState_API_IS_NOT_SELECTED
#endif

#if (ICU_17_TIMERIP_TIMESTAMP_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Syntax :void Icu_17_TimerIp_StartTimestamp(                                **
**                           const  Icu_17_TimerIp_ChannelType Channel ,      **
**                            Icu_17_TimerIp_ValueType *const BufferPtr,      **
**                           const  uint16         BufferSize,                **
**                           const             uint16 NotifyInterval )        **
**                                                                            **
** Description : 1. This service will start the TimeStamp Capture.            **
**               2. This service will also set the Notification Flag, if      **
**                  NotifyInterval is greater than zero.                      **
**               3. The Notifications is  done in ISR Only.                   **
**                                                                            **
** Service ID:       0x09                                                     **
**                                                                            **
** Sync/Async:       Asynchronous                                             **
**                                                                            **
** Reentrancy:       reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                   BufferSize - Size of the Buffer                          **
**                   NotifyInterval - Interval for Timestamp Notifications    **
**                                                                            **
** Parameters (out):                                                          **
**                   BufferPtr - Starting address of Buffer, that will        **
**                               hold the timer capture values                **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
*******************************************************************************/
extern void Icu_17_TimerIp_StartTimestamp
(
  const Icu_17_TimerIp_ChannelType Channel,
  Icu_17_TimerIp_ValueType *const BufferPtr,
  const uint16 BufferSize,
  const uint16 NotifyInterval
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Icu_17_TimerIp_StartTimestamp(                                      \
                           Channel,BufferPtr,BufferSize,NotifyInterval)     \
                         ERROR_Icu_17_TimerIp_StartTimestamp_API_IS_NOT_SELECTED
#endif

#if (ICU_17_TIMERIP_TIMESTAMP_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Syntax :           void Icu_17_TimerIp_StopTimestamp(                      **
**                              const  Icu_17_TimerIp_ChannelType Channel )   **
**                                                                            **
** Description : 1. This service will stop the TimeStamp Capture.             **
**               2. This service will also deactivate the interrupt flags.    **
**                                                                            **
** Service ID:       0x0A                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out):                                                          **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
*******************************************************************************/
extern void Icu_17_TimerIp_StopTimestamp
(
  const Icu_17_TimerIp_ChannelType Channel
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Icu_17_TimerIp_StopTimestamp(Channel) \
                 ERROR_Icu_17_TimerIp_StopTimestamp_API_IS_NOT_SELECTED
#endif

#if (ICU_17_TIMERIP_TIMESTAMP_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Syntax :Icu_17_TimerIp_IndexType Icu_17_TimerIp_GetTimestampIndex(         **
**                                 const  Icu_17_TimerIp_ChannelType Channel  **
**                                                      )                     **
**                                                                            **
** Description : 1. This service will return the next index of the            **
**                  Buffer that will be written by the ISR.                   **
**               2. In case of a liner buffer and the buffer is filled the    **
**                  service will returns buffer size.                         **
**                                                                            **
** Service ID:       0x0B                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out):                                                          **
**                                                                            **
** Return value:     Icu_17_TimerIp_IndexType                                 **
**                                                                            **
*******************************************************************************/
extern Icu_17_TimerIp_IndexType Icu_17_TimerIp_GetTimestampIndex
(
  const Icu_17_TimerIp_ChannelType Channel
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Icu_17_TimerIp_GetTimestampIndex(Channel) \
                      ERROR_Icu_17_TimerIp_GetTimestampIndex_API_IS_NOT_SELECTED
#endif

#if (ICU_17_TIMERIP_EDGE_COUNT_API ==STD_ON)
/*******************************************************************************
**                                                                            **
** Syntax :          void Icu_17_TimerIp_ResetEdgeCount(                      **
**                              const Icu_17_TimerIp_ChannelType Channel )    **
**                                                                            **
** Description : This service will set the edge counter variable to zero.     **
**                                                                            **
** Service ID:       0x0C                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out):                                                          **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
*******************************************************************************/
extern void Icu_17_TimerIp_ResetEdgeCount
(
  const Icu_17_TimerIp_ChannelType Channel
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Icu_17_TimerIp_ResetEdgeCount(Channel) \
                       ERROR_Icu_17_TimerIp_ResetEdgeCount_API_IS_NOT_SELECTED
#endif

#if (ICU_17_TIMERIP_EDGE_COUNT_API ==STD_ON)
/*******************************************************************************
**                                                                            **
** Syntax :          void Icu_17_TimerIp_EnableEdgeCount(                     **
**                              const  Icu_17_TimerIp_ChannelType Channel )   **
**                                                                            **
** Description : 1. This service shall start the edge count mode.             **
**               2. The index of the channel is initialized in                **
**                  Icu_17_TimerIp_Init.                                      **
**               3. Icu_ActivityStarted Flag is set to true.                  **
**                                                                            **
** Service ID:       0x0D                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out):                                                          **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
*******************************************************************************/
extern void Icu_17_TimerIp_EnableEdgeCount
(
  const Icu_17_TimerIp_ChannelType Channel
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Icu_17_TimerIp_EnableEdgeCount(Channel) \
                       ERROR_Icu_17_TimerIp_EnableEdgeCount_API_IS_NOT_SELECTED
#endif

#if (ICU_17_TIMERIP_EDGE_COUNT_API ==STD_ON)
/*******************************************************************************
**                                                                            **
** Syntax :          void Icu_17_TimerIp_DisableEdgeCount(                    **
**                               const  Icu_17_TimerIp_ChannelType Channel )  **
**                                                                            **
** Description : 1. This service will stop the edge counting capability       **
**                  of a channel.                                             **
**                                                                            **
** Service ID:       0x0E                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out):                                                          **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
*******************************************************************************/

extern void Icu_17_TimerIp_DisableEdgeCount
(
  const Icu_17_TimerIp_ChannelType Channel
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Icu_17_TimerIp_DisableEdgeCount(Channel) \
                       ERROR_Icu_17_TimerIp_DisableEdgeCount_API_IS_NOT_SELECTED
#endif

#if (ICU_17_TIMERIP_EDGE_COUNT_API ==STD_ON)
/*******************************************************************************
**                                                                            **
** Syntax :Icu_17_TimerIp_EdgeNumberType Icu_17_TimerIp_GetEdgeNumbers(       **
**                                const  Icu_17_TimerIp_ChannelType Channel ) **
**                                                                            **
** Description : 1. This service will return the number of edges counted      **
**                  for the channel specified.                                **
**                                                                            **
** Service ID:       0x0F                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out):                                                          **
**                                                                            **
** Return value:     Icu_17_TimerIp_EdgeNumberType                            **
**                                                                            **
*******************************************************************************/
extern Icu_17_TimerIp_EdgeNumberType Icu_17_TimerIp_GetEdgeNumbers
(
  const Icu_17_TimerIp_ChannelType Channel
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Icu_17_TimerIp_GetEdgeNumbers(Channel) \
                        ERROR_Icu_17_TimerIp_GetEdgeNumbers_API_IS_NOT_SELECTED
#endif

#if (ICU_17_TIMERIP_SIGNAL_MEASUREMENT_API == STD_ON)
/* Configuration of API Service */
/*******************************************************************************
**                                                                            **
** Syntax :          void Icu_17_TimerIp_StartSignalMeasurement (             **
**                                const  Icu_17_TimerIp_ChannelType Channel)  **
**                                                                            **
** Description : 1. This service starts the measurement of signals beginning  **
**                  with the configured default start edge which occurs first **
**                  after the call of this service.                           **
**                                                                            **
** Service ID:       0x13                                                     **
**                                                                            **
** Sync/Async:       Asynchronous                                             **
**                                                                            **
** Reentrancy:       reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  None                                                     **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
*******************************************************************************/
extern void Icu_17_TimerIp_StartSignalMeasurement
(
  const Icu_17_TimerIp_ChannelType Channel
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Icu_17_TimerIp_StartSignalMeasurement(Channel)                        \
                 ERROR_Icu_17_TimerIp_StartSignalMeasurement_API_IS_NOT_SELECTED
#endif


#if (ICU_17_TIMERIP_SIGNAL_MEASUREMENT_API == STD_ON)
/* Configuration of API Service */
/*******************************************************************************
**                                                                            **
** Syntax :          void Icu_17_TimerIp_StopSignalMeasurement (              **
**                                const  Icu_17_TimerIp_ChannelType Channel)  **
**                                                                            **
** Description : 1. This service stops the measurement of signals of the      **
**                  given channel                                             **
**                                                                            **
** Service ID:       0x14                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  None                                                     **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
*******************************************************************************/
extern void Icu_17_TimerIp_StopSignalMeasurement
(
  const Icu_17_TimerIp_ChannelType Channel
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Icu_17_TimerIp_StopSignalMeasurement(Channel)                      \
                  ERROR_Icu_17_TimerIp_StopSignalMeasurement_API_IS_NOT_SELECTED
#endif


#if (ICU_17_TIMERIP_GET_TIME_ELAPSED_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Syntax :         Icu_17_TimerIp_ValueType Icu_17_TimerIp_GetTimeElapsed (  **
**                               const  Icu_17_TimerIp_ChannelType Channel )  **
**                                                                            **
** Description : 1. This service will return the latest time difference value **
**                  measured as per the configured type of measurement.       **
**                  The service shall measure the following measurement types **
**                  High Time, Low Time Or Period Time.                       **
**               2. The service shall return zero if there were no edges      **
**                  captured or the service has already read the same value.  **
**               3. For a successful read the service sets the Channel Status **
**                  to ICU_17_TIMERIP_IDLE.                                   **
**                                                                            **
** Service ID:       0x10                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out):                                                          **
**                                                                            **
** Return value:     Icu_17_TimerIp_ValueType                                 **
**                                                                            **
*******************************************************************************/
extern Icu_17_TimerIp_ValueType Icu_17_TimerIp_GetTimeElapsed
(
  const Icu_17_TimerIp_ChannelType Channel
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Icu_17_TimerIp_GetTimeElapsed(Channel) \
                    ERROR_Icu_17_TimerIp_GetTimeElapsed_API_IS_NOT_SELECTED
#endif

#if (ICU_17_TIMERIP_GET_DUTY_CYCLE_VALUES_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Syntax :          void Icu_17_TimerIp_GetDutyCycleValues (                 **
**                                const  Icu_17_TimerIp_ChannelType Channel,  **
**                      Icu_17_TimerIp_DutyCycleType *const DutyCycleValues ) **
**                                                                            **
** Description : 1. This service will return the latest high time             **
**                  and period time captured.                                 **
**               2. The service shall write zero in the given address         **
**                  if there were no edges captured or the                    **
**                  has already read the same value.                          **
**               3. A successful read puts the status to ICU_17_TIMERIP_IDLE  **
**                                                                            **
** Service ID:       0x11                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out):  DutyCycleValues - Pointer to structure that could       **
**                                     hold high time and period time.        **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
*******************************************************************************/
extern void Icu_17_TimerIp_GetDutyCycleValues
(
  const Icu_17_TimerIp_ChannelType Channel,
  Icu_17_TimerIp_DutyCycleType *const DutyCycleValues
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Icu_17_TimerIp_GetDutyCycleValues(Channel,DutyCycleValues)      \
                    ERROR_Icu_17_TimerIp_GetDutyCycleValues_API_IS_NOT_SELECTED
#endif


#if (ICU_17_TIMERIP_GET_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Syntax :          void Icu_17_TimerIp_GetVersionInfo (                     **
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
** Description : 1. This service will return the version infos of ICU driver  **
*******************************************************************************/
extern void Icu_17_TimerIp_GetVersionInfo(
  Std_VersionInfoType* const versioninfo);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Icu_17_TimerIp_GetVersionInfo(versioninfo)      \
                         ERROR_Icu_17_TimerIp_GetVersionInfo_API_IS_NOT_SELECTED
#endif
/*Applicable to Autosar V 3.2.1 based on Bugzilla 25392*/
/*******************************************************************************
** Traceability: [cover parentID= {0897A5BE-58B5-4947-AD97-CD98CCEFC2F5}]     **
**                                                                            **
** Syntax : void Icu_17_TimerIp_CheckWakeup(                                  **
**                           const EcuM_WakeupSourceType WakeupSource)        **
**                                                                            **
** Description : Checks if a wakeup capable ICU channel is the source for a   **
**               wakeup event and calls the ECU state manager service         **
**               EcuM_SetWakeupEvent in case of a valid ICU channel           **
**               wakeup event.                                                **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x15                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  WakeupSource-Information on wake-up source to be checked.**
**    The associated ICU channel can be determined from configuration data.   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
#if ((ICU_17_TIMERIP_WAKEUP_FUNCTIONALITY_API == STD_ON) \
&& (ICU_17_TIMERIP_REPORT_WAKEUP_SOURCE == STD_ON))
extern void Icu_17_TimerIp_CheckWakeup
(
  const EcuM_WakeupSourceType WakeupSource
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Icu_17_TimerIp_CheckWakeup(wakeupSource) \
                         ERROR_Icu_17_TimerIp_CheckWakeup_API_IS_NOT_SELECTED
#endif

/*******************************************************************************
** Traceability: [cover parentID={01129404-A6F1-4050-AEA2-C129B6FBBC14}]      **
**                                                                            **
** Syntax : void Icu_17_TimerIp_StartIncInterface(                            **
**                                const  Icu_17_TimerIp_ChannelType Channel)  **
**                                                                            **
** Description : Starts the incremental interface mode activities.            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x21                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
#if (ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON) 
extern void Icu_17_TimerIp_StartIncInterface
(
    const Icu_17_TimerIp_ChannelType Channel
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Icu_17_TimerIp_StartIncInterface(Channel) \
                 ERROR_Icu_17_TimerIp_StartIncInterface_API_IS_NOT_SELECTED
#endif

/*******************************************************************************
** Traceability: [cover parentID={602273A3-C207-4e50-B1F2-E0CF2E8BBAF5}]      **
**                                                                            **
** Syntax : void Icu_17_TimerIp_StopIncInterface(                             **
**                                const  Icu_17_TimerIp_ChannelType Channel)  **
**                                                                            **
** Description : Stop the incremental interface mode activities.              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x22                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
#if (ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON) 
extern void Icu_17_TimerIp_StopIncInterface
(
    const Icu_17_TimerIp_ChannelType Channel
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Icu_17_TimerIp_StopIncInterface(Channel) \
                      ERROR_Icu_17_TimerIp_StopIncInterface_API_IS_NOT_SELECTED
#endif

/*******************************************************************************
** Traceability: [cover parentID={CA784191-BE6D-4705-9477-9E31862E5377}]      **
**                                                                            **
** Syntax : void Icu_17_TimerIp_CalibratePos(                                 **
**                                const  Icu_17_TimerIp_ChannelType Channel,  **
**                                const uint16 Position )                     **
**                                                                            **
** Description : Calibrate the start point for increment interface mode       **
**               functionality.                                               **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x23                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                   Position - Start point to be set                         **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
#if (ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON) 
extern void Icu_17_TimerIp_CalibratePos
(
    const Icu_17_TimerIp_ChannelType Channel,
    const uint16 Position
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Icu_17_TimerIp_CalibratePos(Channel,Position) \
                        ERROR_Icu_17_TimerIp_CalibratePos_API_IS_NOT_SELECTED
#endif

/*******************************************************************************
** Traceability: [cover parentID={345F0D7A-64CB-4e61-83AD-C5C0F8E96095}]      **
**                                                                            **
** Syntax : uint16 Icu_17_TimerIp_ReadEncCount(                               **
**                                const  Icu_17_TimerIp_ChannelType Channel)  **
**                                                                            **
** Description : read the current encoder count value                         **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x24                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     uint16: Encoder counter value                            **
**                                                                            **
*******************************************************************************/
#if (ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON) 
extern uint16 Icu_17_TimerIp_ReadEncCount
(
    const Icu_17_TimerIp_ChannelType Channel
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Icu_17_TimerIp_ReadEncCount(Channel) \
                    ERROR_Icu_17_TimerIp_ReadEncCount_API_IS_NOT_SELECTED
#endif

/*******************************************************************************
** Traceability: [cover parentID={AAC7A62B-17C7-47ff-A8C0-FD8E3ADE4AD6}]      **
**                                                                            **
** Syntax : Icu_17_TimerIp_EncCountDirType Icu_17_TimerIp_ReadEncCountDir(    **
**                                const  Icu_17_TimerIp_ChannelType Channel)  **
**                                                                            **
** Description : read the current encoder counting direcion                   **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x25                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     Icu_17_TimerIp_EncCountDirType: Counting direction       **
**                                                                            **
*******************************************************************************/
#if (ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON) 
extern Icu_17_TimerIp_EncCountDirType Icu_17_TimerIp_ReadEncCountDir
(
    const Icu_17_TimerIp_ChannelType Channel
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Icu_17_TimerIp_ReadEncCountDir(Channel) \
                    ERROR_Icu_17_TimerIp_ReadEncCountDir_API_IS_NOT_SELECTED
#endif

/*******************************************************************************
** Syntax : void Icu_17_TimerIp_SetTimeoutValue(                              **
**                               const  Icu_17_TimerIp_ChannelType Channel    **
**                               const  uint32 TimeoutValue)                  **
**                                                                            **
** Service ID:  0x26                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  reentrant                                                     **
**                                                                            **
** Parameters (in):  Channel : Numeric identifier of the ICU channel          **
**                   TimeoutValue : Timeout value to be set                   **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:    none                                                      **
**                                                                            **
** Description : This service will set the timeout value passed by the user.  **
*******************************************************************************/
#if (ICU_17_TIMERIP_TIMEOUT_DETECTION_API == STD_ON)
extern void Icu_17_TimerIp_SetTimeoutValue
(const Icu_17_TimerIp_ChannelType Channel,
 const uint32 TimeoutValue);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Icu_17_TimerIp_SetTimeoutValue(Channel,TimeoutValue)             \
                    ERROR_Icu_17_TimerIp_SetTimeoutValue_API_IS_NOT_SELECTED
#endif

#define ICU_17_TIMERIP_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Icu_17_TimerIp_MemMap.h"

/*    PBCFG.H inclusion */
#include "Icu_17_TimerIp_PBcfg.h"


#endif /* ICU_17_TIMERIP_H */
