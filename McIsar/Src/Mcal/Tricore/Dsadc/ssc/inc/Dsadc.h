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
**  FILENAME     : Dsadc.h                                                    **
**                                                                            **
**  VERSION      : 16.0.0                                                     **
**                                                                            **
**  DATE         : 2021-09-08                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID={78B6576F-74E3-43c7-AAAF-030A3446EF3D}]    **
**                                                                            **
**  DESCRIPTION  : DSADC driver header definition file                        **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef DSADC_H
#define DSADC_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Std_Types.h"
#include "Mcu_17_TimerIp.h"
#include "Dsadc_Cfg.h"


/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/* [cover parentID={92E6CE02-D040-45d7-BEED-249AF169F6A2}] */
#define DSADC_VENDOR_ID                             ((uint16)17U)
#define DSADC_MODULE_ID                             ((uint16)0xFFU) /* 255U */
#define DSADC_MODULE_INSTANCE                       ((uint8)0x0U)
/* [/cover] */

#if ((DSADC_DEV_ERROR_DETECT == STD_ON)|| (DSADC_SAFETY_ENABLE == STD_ON))

/* DET - Default Error Tracer ID's */
#define DSADC_E_NO_ERR                              ((uint8)0x00U)
/*[cover parentID={ADFD2E71-B36E-40d3-A779-6CFF7C47EDF0}]  [/cover]*/
#define DSADC_E_PARAM_CONFIG                        ((uint8)0x01U)
/*[cover parentID={FFB76835-E860-45fe-99EF-E79ABB4E0BFA}]  [/cover]*/
#define DSADC_E_ALREADY_INITIALIZED                 ((uint8)0x02U)
/*[cover parentID={FC1DF616-18E3-4f5a-9310-23B3C9030F2F}]  [/cover]*/
#define DSADC_E_UNINIT                              ((uint8)0x03U)
/*[cover parentID={542F9F4F-02CD-461a-8107-31EEE77873B6}]  [/cover]*/
#define DSADC_E_BUSY                                ((uint8)0x04U)
/*[cover parentID={1A97225F-386C-4c99-B907-D557643F7A57}]  [/cover]*/
#define DSADC_E_PARAM_CHANNEL                       ((uint8)0x05U)
/*[cover parentID={2251C719-6D15-47b3-9476-4E909EA0F191}]  [/cover]*/
#define DSADC_E_PARAM_POINTER                       ((uint8)0x06U)
/*[cover parentID={D96937CE-F2CC-474e-8CFB-8BB13A3FF03D}]  [/cover]*/
#define DSADC_E_INV_LINEAR_BUFFER_CONFIG            ((uint8)0x07U)
/*[cover parentID={CDAD8668-E407-4e39-B414-3BE41912B8CC}]  [/cover]*/
#define DSADC_E_INV_CIRCULAR_BUFFER_CONFIG          ((uint8)0x08U)
/*[cover parentID={6944868F-BA45-436b-BCFE-BC7078B4DC9C}]  [/cover]*/
#define DSADC_E_INVALID_BUFFER_CONFIG               ((uint8)0x09U)
/*[cover parentID={808DFC51-CCE1-4f49-9557-625DCA65F629}]  [/cover]*/
#define DSADC_E_UNIDLE                              ((uint8)0x0AU)
/*[cover parentID={A35FA3E8-ECB0-472a-A4A3-3B36AB1864D8}]  [/cover]*/
#define DSADC_E_CARRIER_ALREADY_RUNNING             ((uint8)0x0BU)
/*[cover parentID={89CD8BEE-2985-46b5-9BF7-DB3B037368B3}]  [/cover]*/
#define DSADC_E_NOTIF_CAPABILITY                    ((uint8)0x0CU)
/*[cover parentID={6FC14045-E9B4-4ea8-9038-65C6115F8410}]  [/cover]*/
#define DSADC_E_SINGLE_ACCESSMODE_TIMESTAMP         ((uint8)0x0DU)
/*[cover parentID={B72487B8-39AB-4118-A82A-7F0D11AFDC16}]  [/cover]*/
#define DSADC_E_CALIB_RUNNING                       ((uint8)0x0EU)
/*[cover parentID={3E5E7EFE-8337-4603-8836-541C5FB366D6}]  [/cover]*/
#define DSADC_E_INV_BUFFER_SIZE                     ((uint8)0x0FU)
/*[cover parentID={D19EA972-AED0-4f76-976D-8CA993E10037}]  [/cover]*/
#define DSADC_E_INVALID_BUFFER_POINTER              ((uint8)0x10U)
/*[cover parentID={194E76F7-F8B3-45a8-95FD-CFE1911B87DE}]  [/cover]*/
#define DSADC_E_INVALID_PARAM_VALUE                 ((uint8)0x11U)
/*[cover parentID={B3F3463B-DF52-4d87-ADFD-FEC26ED5EE20}]  [/cover]*/
#define DSADC_E_INVALID_PARAM_DELAY                 ((uint8)0x12U)


/*Safety Error - Tracer ID's */
/*[cover parentID={5CABF9E0-BA44-4a52-B84F-8AF5CEC4B04E}]  [/cover]*/
#define DSADC_SE_INVALID_ISR                        ((uint8)0x11U)
/*[cover parentID={B5B3D2C8-B877-4dca-9F01-751D9F262A5B}]  [/cover]*/
#define DSADC_SE_PARAM_HW_CHANNEL                   ((uint8)0x12U)
/*[cover parentID={B19C21E7-4BB6-4adf-82FE-EEF63B4AEE05}]  [/cover]*/
#define DSADC_SE_EARLY_WINDOW_ISR                   ((uint8)0x13U)

/*SID's for all APIs*/
#define DSADC_SID_INIT                              ((uint8)0x1AU)
#define DSADC_SID_DEINIT                            ((uint8)0x1BU)
#define DSADC_SID_START_MODULATION                  ((uint8)0x1CU)
#define DSADC_SID_STOP_MODULATION                   ((uint8)0x1DU)
#define DSADC_SID_READ_STREAM_RESULTS               ((uint8)0x1EU)
#define DSADC_SID_READ_RESULT                       ((uint8)0x1FU)
#define DSADC_SID_GET_STATUS                        ((uint8)0x20U)
#define DSADC_SID_SETUP_RESULT_BUFFER               ((uint8)0x21U)
#define DSADC_SID_START_CARRIER_SIGNAL              ((uint8)0x22U)
#define DSADC_SID_STOP_CARRIER_SIGNAL               ((uint8)0x23U)
#define DSADC_SID_ENABLE_NOTIFICATIONS              ((uint8)0x24U)
#define DSADC_SID_DISABLE_NOTIFICATIONS             ((uint8)0x25U)
#define DSADC_SID_GET_TIMESTAMP                     ((uint8)0x26U)
#define DSADC_SID_START_CALIBRATION                 ((uint8)0x27U)
#define DSADC_SID_GET_CALIBRATION_STATUS            ((uint8)0x28U)
#define DSADC_SID_INITCHECK                         ((uint8)0x29U)
#define DSADC_SID_ISR                               ((uint8)0x2AU)
#define DSADC_SID_TIMERISR                          ((uint8)0x2BU)
#define DSADC_SID_GET_VERSION_INFO                  ((uint8)0x2CU)
#define DSADC_SID_RESTART_DEMODULATOR               ((uint8)0x2DU)
#define DSADC_SID_GET_IRMS_VALUE                    ((uint8)0x2EU)
#define DSADC_SID_SET_GAINCORR_REG_VALUE            ((uint8)0xF0U)
#define DSADC_SID_RESTART_INTEGRATOR                ((uint8)0xF1U)
#define DSADC_SID_GET_SDCAP_VALUE                   ((uint8)0xF2U)

#endif /*End for DSADC_DEV_ERROR_DETECT */

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/* [cover parentID={ABDEC054-C8E7-4219-B76C-5DF2EF00BA57}]
   Type Definition for Dsadc_ChannelMaskType [/cover] */
typedef uint32 Dsadc_ChannelMaskType;

/* [cover parentID={9FFD2FD9-5BF6-448b-B865-C1379C6BE6FB}]
   Type Definition for Dsadc_SizeType [/cover] */
typedef uint16 Dsadc_SizeType;

/* [cover parentID={A6F1C45E-09FF-414e-ACA0-52E8E00CC37B}]
   Type Definition for Dsadc_TimeStampType [/cover] */
typedef uint16 Dsadc_TimeStampType;

/* [cover parentID={C60CAF65-AB04-4f5a-9F8A-660281D3656A}]
   Type Definition for Dsadc_IrmsValueType [/cover] */
typedef uint16 Dsadc_IrmsValueType;

/* [cover parentID={6B840E9B-DF37-4752-9B29-8C3B27E28410}]
   Type Definition for Dsadc_ResultType [/cover] */
typedef sint16 Dsadc_ResultType;

/* [cover parentID={E6F22369-7370-4945-9F63-8A608D9AA62B}]
   Type Definition for Dsadc_ChannelType [/cover] */
typedef uint8 Dsadc_SdcapValueType;

/* [cover parentID={BB076371-4546-461f-9E4C-95ABF47B5F13}]
   Type Definition for Dsadc_ChannelType [/cover] */
typedef uint8 Dsadc_ChannelType;

/* [cover parentID={AB648EC1-BEA1-425a-A47D-6E5D21736795}]
   Type Definition for Dsadc_GainCorrType [/cover] */
typedef uint32 Dsadc_GainCorrType;

#if(DSADC_RESTART_INTEGRATOR_API == STD_ON)
/* [cover parentID={69856B92-D927-4c19-8A3C-BEF3E4AD9100}]
   Type Definition for Dsadc_DelayType [/cover] */
typedef uint32 Dsadc_DelayType;
#endif

/* [cover parentID={EB55BEED-48A9-4f7a-A4A2-1AD60145D1F7}]
   Type Definition for Dsadc_NotifyFnPtrType - Notification Function [/cover] */
typedef void (*Dsadc_NotifyFnPtrType)(void);

/* [cover parentID={7B08773D-6046-475f-B2D1-73A6ECB2DBDC}]
   Type Definition for  Dsadc_CalibrationStatusType[/cover] */
typedef uint8 Dsadc_CalibrationStatusType;
#define DSADC_CALIBRATION_NOT_STARTED          ((Dsadc_CalibrationStatusType)0U)
#define DSADC_CALIBRATION_RUNNING              ((Dsadc_CalibrationStatusType)1U)
#define DSADC_CALIBRATION_DONE                 ((Dsadc_CalibrationStatusType)2U)
#define DSADC_CALIBRATION_ERROR                ((Dsadc_CalibrationStatusType)3U)

/* [cover parentID={E4CBA7B4-FF20-41b8-8AB7-2CECC704A2EB}]
   Type Definition for Dsadc_ChannelstatusType [/cover] */
typedef uint8 Dsadc_ChannelstatusType;
#define DSADC_IDLE                             ((Dsadc_ChannelstatusType)0x0U)
#define DSADC_BUSY                             ((Dsadc_ChannelstatusType)0x1U)
#define DSADC_RESULT_READY                     ((Dsadc_ChannelstatusType)0x2U)

/* [cover parentID={5E39628E-764F-4bca-BCDF-6D02944FDAB4}]
   Type Definition for  Dsadc_EruOguConfigType [/cover] */
typedef struct
{
  uint16 EruOguIgcr;
  uint8  OguChannelNo;
}Dsadc_EruOguConfigType;

/* [cover parentID={F431CB3D-A29F-43fd-85F8-15816D26F5C7}]
   Type Definition for Dsadc_EruErsConfigType [/cover] */
typedef struct
{
  uint16 EruErsEicr;
  uint8  ErsChannelNo;
}Dsadc_EruErsConfigType;

/* [cover parentID={1FF12CC6-7B25-4ed1-811A-279387FFA67D}]
   Type Definition for  Dsadc_ChannelConfigType [/cover] */
typedef struct
{
  const Dsadc_EruOguConfigType *Dsadc_EruOguConf;
  uint32 ModulatorConfigReg;
  uint32 CommonModeVoltConfigReg;
  uint32 DemodulatorConfigReg;
  uint32 FilterConfigReg;
  uint32 CICFilterConfigReg;
  uint32 AuxCICFilterConfigReg;
  uint32 TimeStampConfigReg;
  uint32 IntegratorConfigReg;
  uint32 ResultFifoConfigReg;
  uint32 OffsetCompConfigReg;
  uint32 GainCalibConfigReg;
  uint32 GainControlConfigReg;
  uint32 GainCorrConfigReg;
  uint32 LimitCheckingConfigReg;
  uint32 OvershootCompenconfigReg;
  uint32 CarrierGenSyncConfigReg;
  uint32 RectificationConfigReg;
  uint8 HwAssignedChannelNum;
  uint8 AccessMode;
  uint8 TimestampMode;
  uint8 TimestampTriggermode;
  uint8 TriggerMode;
  uint8 TriggerSource;
  uint8 GateActiveLevel;
  uint8 ChannelIntMode;
  Dsadc_NotifyFnPtrType BufferFullNotifyPtr;
  Dsadc_NotifyFnPtrType NewResultNotifyPtr;
  Dsadc_NotifyFnPtrType WindowCloseNotifyPtr;
}Dsadc_ChannelConfigType;

/* [cover parentID={A1AE9B1E-348F-40e6-9CE3-07FBDDDF43EA}] */
/*Type Definition for  Dsadc_ConfigType */
typedef struct
{
  const Dsadc_ChannelConfigType *DsadcChannelConfiguration;
  const Dsadc_EruErsConfigType *DsadcEruErsConfig;
  uint32 DsadcClcCtrlReg;
  uint32 GlobalConfigReg;
  uint32 CarrierGenConfigReg;
  uint8 CGWaveform;
}Dsadc_ConfigType;
/*  [/cover] */

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/

#define DSADC_START_SEC_CODE_ASIL_B_LOCAL

#include "Dsadc_MemMap.h"

/*******************************************************************************
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : void Dsadc_Init                                         **
**                    (                                                       **
**                      const Dsadc_ConfigType  * const ConfigPtr             **
**                    )                                                       **
**                                                                            **
** Description      : This API initializes the DSADC Hardware as per the      **
**                    configuration pointer passed and sets all the Global    **
**                    variables to their required initial values.The          **
**                    SFR's of DSADC Hardware resets to its default values    **
**                    and then it is configured with the given configuration  **
**                    data.The API  will set the DSADC module state to        **
**                    DSADC_INITIALIZED if the initialization was successful. **
**                                                                            **
**                    It also enables the DSADC module by writing into the    **
**                    CLC register and Enable the Modulator and Demodulator   **
**                    for the configured channels                             **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x1A                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : ConfigPtr - Pointer to the DSADC Driver configuration   **
**                                structure                                   **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Dsadc_Init(const Dsadc_ConfigType * const ConfigPtr);

#if(DSADC_INITCHECK_API == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : Std_ReturnType Dsadc_InitCheck                          **
**                    (                                                       **
**                      const Dsadc_ConfigType  * const ConfigPtr             **
**                    )                                                       **
**                                                                            **
** Description      : This Function verifies the Initialization of DSADC      **
**                    driver.                                                 **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x29                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : ConfigPtr - Pointer to DSADC configuration Set          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK - Initialization verification passed               **
**                    E_NOT_OK - Initialization verification failed           **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Dsadc_InitCheck(const Dsadc_ConfigType * const ConfigPtr);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Dsadc_InitCheck(ConfigPtr)  (ERROR_Dsadc_InitCheck_API_IS_NOT_SELECTED)
#endif

#if(DSADC_DEINIT_API == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : void Dsadc_DeInit(void)                                 **
**                                                                            **
** Description      : This API resets all SFRs of the DSADC Channels          **
**                    configured by Dsadc_Init to their reset states. It also **
**                    resets the global SFR's of the EDSADC IP.               **
**                    Note: SFRs of DSADC Hardware not configured by          **
**                    Dsadc_Init are not de-initialized by this API           **
**                                                                            **
** Service ID       : 0x1B                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
extern void Dsadc_DeInit(void);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Dsadc_DeInit()             (ERROR_Dsadc_DeInit_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : Std_ReturnType Dsadc_StartModulation                    **
**                    (const Dsadc_ChannelType ChannelId)                     **
**                                                                            **
** Description      : This API Enables the Result data acquisition for the    **
**                    referred channel and enable the Trigger source if it is **
**                    configured. It sets the Channel status to DSADC_BUSY.   **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x1C                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for same channel, Reentrant  for other    **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric Id of  the requested DSADC Channel  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK : DSADC channel Result data acquisition is         **
**                           enabled                                          **
**                    E_NOT_OK: DSADC channel Result data acquisition is      **
**                              not enabled                                   **
*******************************************************************************/
extern Std_ReturnType Dsadc_StartModulation (const Dsadc_ChannelType ChannelId);

/*******************************************************************************
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : Std_ReturnType Dsadc_StopModulation                     **
**                        (const Dsadc_ChannelType ChannelId)                 **
**                                                                            **
** Description      : This API Disables the Result data acquisition           **
**                    for the referred channel and disable the Trigger source **
**                    if it is configured. It sets the Dsadc Channel status   **
**                    to DSADC_IDLE.                                          **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x1D                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for same channel, Reentrant  for other    **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric Id of  the requested DSADC Channel  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK : DSADC channel Result data acquisition is         **
**                           stopped                                          **
**                    E_NOT_OK: DSADC channel Result data acquisition is      **
**                              not disabled                                  **
*******************************************************************************/
extern Std_ReturnType Dsadc_StopModulation (const Dsadc_ChannelType ChannelId);

#if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : Dsadc_SizeType Dsadc_ReadStreamResults                  **
**                    (                                                       **
**                      const Dsadc_ChannelType ChannelId,                    **
**                      Dsadc_ResultType * const ResultLinearBufferPtr        **
**                    )                                                       **
**                                                                            **
** Description      : This API reads the conversion results stored in         **
**                    the linear buffer. If the ResultLinearBufferPtr is not  **
**                    the channel Buffer what was configured in the           **
**                    Dsadc_SetupResultBuffer API call, then this API copies  **
**                    the conversion results from channel buffer to the       **
**                    ResultLinearBufferPtr.This API returns the number of    **
**                    valid conversion results. The starting location of the  **
**                    conversion results are always 0 in the buffer.          **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x1E                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for same channel, Reentrant  for other    **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric Id of  the requested DSADC Channel  **
**                                                                            **
** Parameters (out) : ResultLinearBufferPtr -> Location to store the requested**
**                                             channel Result buffer          **
** Return value     : Dsadc_SizeType -> Number of valid conversion result in  **
**                                      the channel buffer                    **
**                    65535 -> HW FIFO Error occurred. Data loss is possible  **
**                    0 -> Read Stream result failed                          **
*******************************************************************************/
extern Dsadc_SizeType Dsadc_ReadStreamResults
(
  const Dsadc_ChannelType ChannelId,
  Dsadc_ResultType  * const ResultLinearBufferPtr
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Dsadc_ReadStreamResults(ChannelId, ResultLinearBufferPtr) \
                            (ERROR_Dsadc_ReadStreamResults_API_IS_NOT_SELECTED)
#endif

#if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : Std_ReturnType Dsadc_ReadResult                         **
**                    (                                                       **
**                      const Dsadc_ChannelType ChannelId,                    **
**                      Dsadc_ResultType * const ResultPtr                    **
**                    )                                                       **
**                                                                            **
** Description      : This API read the Result data for given DSADC channel.  **
**                    If the Access mode is single then this API read the     **
**                    DSADC Hardware result Register to update ResultPtr.     **
**                    If the Access mode is configured as Circular buffer     **
**                    then this API update the ResultPtr with the circular    **
**                    Buffer data.                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x1F                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for same channel, Reentrant  for other    **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric Id of  the requested DSADC Channel  **
**                                                                            **
** Parameters (out) : Access mode single: ResultPtr-> Result from the DSADC   **
**                                                  Hardware result register  **
**                    Access mode circular Buffer : ResultPtr -> Result from  **
**                      the Circular buffer current read Pointer location.    **
**                                                                            **
** Return value     : E_OK : Requested DSADC channel result is read           **
**                    E_NOT_OK: Failed to read the requested DSADC channel    **
**                              result                                        **
*******************************************************************************/
extern Std_ReturnType Dsadc_ReadResult
(
  const Dsadc_ChannelType ChannelId,
  Dsadc_ResultType  * const ResultPtr
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Dsadc_ReadResult(ChannelId, ResultPtr) \
                            (ERROR_Dsadc_ReadResult_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : Dsadc_ChannelstatusType Dsadc_GetStatus                 **
**                    (                                                       **
**                      const Dsadc_ChannelType ChannelId                     **
**                    )                                                       **
**                                                                            **
** Description      : This interface is used to return the current status     **
**                    of the passed DSADC channel.                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x20                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for same channel, Reentrant  for other    **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric Id of  the requested DSADC Channel  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : current status of the DSADC Channel                     **
**                    DSADC_IDLE -> DSADC Channel is in Idle State            **
**                    DSADC_BUSY -> DSADC Channel is doing conversion         **
**                    DSADC_RESULT_READY -> result is available to read       **
*******************************************************************************/
extern Dsadc_ChannelstatusType Dsadc_GetStatus
(
  const Dsadc_ChannelType ChannelId
);

#if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : Std_ReturnType Dsadc_SetupResultBuffer                  **
**                    (                                                       **
**                      const Dsadc_ChannelType ChannelId,                    **
**                      const Dsadc_ResultType  * const DataBufferPtr,        **
**                      const Dsadc_SizeType Size                             **
**                    )                                                       **
**                                                                            **
** Description      : This API sets up the start address of Channel specific  **
**                    result buffers, where the conversion results will be    **
**                    stored.This API setup the buffer only if the Access mode**
**                    is configured as Linear Buffer or Circular Buffer.      **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x21                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for same channel, Reentrant  for other    **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric ID of requested DSADC channel       **
**                    DataBufferPtr - Pointer to the start of result          **
**                                    data buffer which is channel buffer     **
**                    Size - Result Buffer size which defines the number of   **
**                           result can store in the result buffer. Maximum   **
**                           size of the buffer should be 65534.              **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK : Result buffer(Channel Buffer)initialization      **
**                           is successful                                    **
**                    E_NOT_OK: Result buffer Initialization failed           **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Dsadc_SetupResultBuffer
(
  const Dsadc_ChannelType ChannelId, \
  const Dsadc_ResultType  * const DataBufferPtr,\
  const Dsadc_SizeType Size\
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Dsadc_SetupResultBuffer(ChannelId, DataBufferPtr, Size) \
                          (ERROR_Dsadc_SetupResultBuffer_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : Std_ReturnType Dsadc_StartCarrierSignal(void)           **
**                                                                            **
** Description      : This API is used to start the generation of the carrier **
**                    signal from the carrier generator based on the          **
**                    configured waveform properties for exciting the Resolver**
**                    coils. This interface checks the current status of the  **
**                    Carrier generator. If it is stopped, then the carrier   **
**                    generator is started with the configured input waveform **
**                    and frequency.                                          **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x22                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK : The Carrier Generator is Started                 **
**                    E_NOT_OK: The Carrier Generator is not Started          **
*******************************************************************************/
extern Std_ReturnType Dsadc_StartCarrierSignal (void);

/*******************************************************************************
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : Std_ReturnType Dsadc_StopCarrierSignal (void)           **
**                                                                            **
** Description      : The interface is used to stop the generation of carrier **
**                    signal from the carrier generator                       **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x23                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK : The Carrier Generator is stopped                 **
**                    E_NOT_OK: The Carrier Generator is not stopped          **
*******************************************************************************/
extern Std_ReturnType Dsadc_StopCarrierSignal (void);

/*******************************************************************************
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : void Dsadc_EnableNotification                           **
**                    (                                                       **
**                      const Dsadc_ChannelType ChannelId                     **
**                    )                                                       **
**                                                                            **
** Description      : This API enables the notification mechanism for the     **
**                    requested DSADC Channel.                                **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x24                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for same channel, Reentrant for other     **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric ID of requested DSADC Channel       **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
extern void Dsadc_EnableNotifications(const Dsadc_ChannelType ChannelId);

/*******************************************************************************
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : void Dsadc_DisableNotifications                         **
**                    (                                                       **
**                      const Dsadc_ChannelType ChannelId                     **
**                    )                                                       **
**                                                                            **
** Description      : This API disables the notification mechanism for the    **
**                    requested DSADC Channel.                                **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x25                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for same channel, Reentrant for other     **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric ID of requested DSADC Channel       **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
extern void Dsadc_DisableNotifications(const Dsadc_ChannelType ChannelId);

/*******************************************************************************
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : Dsadc_TimeStampType Dsadc_GetTimestamp                  **
**                    (                                                       **
**                      const Dsadc_ChannelType ChannelId                     **
**                    )                                                       **
**                                                                            **
** Description      : This API returns the timestamp count value for the Read **
**                    Result Event. This timestamp count is the time from the **
**                    HW result event untill the ReadResult API reads the     **
**                    result value from the HW Result register.               **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x26                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for same channel, Reentrant for other     **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : ChannelId - Numeric ID of requested DSADC Channel       **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : Timestamp count value                                   **
**                                                                            **
*******************************************************************************/
extern Dsadc_TimeStampType Dsadc_GetTimestamp
(
  const Dsadc_ChannelType ChannelId
);

/*******************************************************************************
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : Std_ReturnType  Dsadc_StartCalibration                  **
**                    (                                                       **
**                      const Dsadc_ChannelType ChannelId                     **
**                    )                                                       **
**                                                                            **
** Description      : This interface allows the user to trigger the           **
**                    calibration algorithm.User has to make sure that        **
**                    configuration parameter related to Calibration is       **
**                    correctly configured for successful calibration         **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x27                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant for same channel, Reentrant  for other    **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : ChannelId - DSADC channel ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK: Calibration Algorithm has now started             **
**                    E_NOT_OK: Calibration Algorithm has not been triggered  **
******************************************************************************/
extern Std_ReturnType Dsadc_StartCalibration(const Dsadc_ChannelType ChannelId);

/*******************************************************************************
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : Dsadc_CalibrationStatusType Dsadc_GetCalibrationStatus  **
**                    (                                                       **
**                      const Dsadc_ChannelType ChannelId                     **
**                    )                                                       **
**                                                                            **
** Description      : This interface is used to get the current status of the **
**                    calibration algorithm for the given input channel.when  **
**                    the Calibration status is DSADC_CALIBRATION_DONE then   **
**                    the status will change to DSADC_CALIBRATION_NOT_STARTED.**
**                    So that when this function is called next time          **
**                    DSADC_CALIBRATION_NOT_STARTED is returned               **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x28                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant for same channel, Reentrant  for other    **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : ChannelId - DSADC channel ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Calibration status for the requested channel            **
**                    DSADC_CALIBRATION_NOT_STARTED ->Calibration algorithm   **
**                                                    not started             **
**                    DSADC_CALIBRATION_RUNNING -> calibration algorithm is   **
**                                                 currently running          **
**                    DSADC_CALIBRATION_DONE -> Calibration algorithm   is    **
**                                              finished and it is success    **
**                    DSADC_CALIBRATION_ERROR -> calibration algorithm is     **
**                                               finished and it is Failed    **
*******************************************************************************/
extern Dsadc_CalibrationStatusType Dsadc_GetCalibrationStatus
(
  const Dsadc_ChannelType ChannelId
);

#if(DSADC_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : void Dsadc_GetVersionInfo                               **
**                    (                                                       **
**                      Std_VersionInfoType * const versioninfo               **
**                    )                                                       **
**                                                                            **
** Description      : This API returns the version information of this module.**
**                    Note: This API is available only when                   **
**                          DsadcVersionInfoApi is configured as true.        **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x2C                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : versioninfo -  Pointer to where to store the version    **
**                    information of this module                              **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
extern void Dsadc_GetVersionInfo(Std_VersionInfoType * const versioninfo);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Dsadc_GetVersionInfo(versioninfo) \
                            (ERROR_Dsadc_GetVersionInfo_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
** Traceability     : [cover parentID ]                                       **
**                                                                            **
** Syntax           : Std_ReturnType Dsadc_RestartDemodulator                 **
**                    (const Dsadc_ChannelMaskType ChannelIds)                **
**                                                                            **
** Description      : This API restart the demodulators for all the DSADC     **
**                    channels requested. The DSADC channels are requested    **
**                    as a bit coded information in the input parameter       **
**                    (i.e. Channel 0 is requested by setting the bit         **
**                    position 0 of the input parameter)                      **
**                                                                            **
** Service ID       : 0x2D                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for same channel, Reentrant  for other    **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : ChannelIds - Bit coded information for the DSADC logical**
**                    channel numbers. DSADC logical channel enable or disable**
**                    is indicated by the corresponding bit position.         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK : Demodulator is restarted for all the DSADC       **
**                           channels requested                               **
**                    E_NOT_OK: Demodulator is not Restarted  failed          **
*******************************************************************************/
extern Std_ReturnType Dsadc_RestartDemodulator \
                                       (const Dsadc_ChannelMaskType ChannelId);

/*******************************************************************************
** Traceability     : [cover parentID ]                                       **
**                                                                            **
** Syntax           : Dsadc_IrmsValueType Dsadc_GetIrmsValue                  **
**                    (const Dsadc_ChannelType ChannelId)                     **
**                                                                            **
** Description      : This API reads the IRMS value from DSADC channel.       **
**                                                                            **
**                                                                            **
** Service ID       : 0x2EU                                                   **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant for same channel, Reentrant  for other    **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : ChannelId - DSADC channel ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Dsadc_GetIrmsValue -> the Irms value read from register **
*******************************************************************************/
extern Dsadc_IrmsValueType Dsadc_GetIrmsValue
                                       (const Dsadc_ChannelType ChannelId);

/*******************************************************************************
** Traceability     : [cover parentID ]                                       **
**                                                                            **
** Syntax           : Std_ReturnType Dsadc_SetGainCorrRegValue                **
**                    (const Dsadc_ChannelType ChannelId,                     **
**                     const Dsadc_GainCorrType  RegValue)                    **
**                                                                            **
** Description      : This API writes the gain correction to the GAINCORR     **
**                    register                                                **
**                                                                            **
**                                                                            **
** Service ID       : 0xF0U                                                   **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant for same channel, Reentrant  for other    **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : ChannelId - DSADC channel ID                            **
**                    RegValue - Value to be written into Gain correction     **
**                               register (GAINCORR)                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK : DSADC channel Gain correction is updated         **
**                           based on user request                            **
**                    E_NOT_OK: DSADC channel Gain correction is not updated  **
*******************************************************************************/
extern Std_ReturnType Dsadc_SetGainCorrRegValue
                    (const Dsadc_ChannelType ChannelId,
                     const Dsadc_GainCorrType  RegValue);


/*******************************************************************************
** Traceability     : [cover parentID ]                                       **
**                                                                            **
** Syntax           : Dsadc_SdcapValueType Dsadc_GetSdcapValue                **
**                    (const Dsadc_ChannelType ChannelId)                     **
**                                                                            **
** Description      : This API reads the SDCAP value for requested            **
**                    DSADC channel.                                          **
**                                                                            **
**                                                                            **
** Service ID       : 0xF2U                                                   **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant for same channel, Reentrant  for other    **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : ChannelId - DSADC channel ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Dsadc_GetSdcapValue -> the SDCAP value read from        **
**                    register                                                **
*******************************************************************************/
extern Dsadc_SdcapValueType Dsadc_GetSdcapValue
                                       (const Dsadc_ChannelType ChannelId);

#if(DSADC_RESTART_INTEGRATOR_API == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID ]                                       **
**                                                                            **
** Syntax           : Std_ReturnType Dsadc_RestartIntegrator(                 **
**                                const Dsadc_ChannelMaskType ChannelId,      **
**                                  const Dsadc_DelayType Delay)              **
**                                                                            **
** Description      : This API restart the integrator for all the DSADC       **
**                    channels requested. The DSADC channels are requested    **
**                    as a bit coded information in the input parameter       **
**                    (i.e. Channel 0 is requested by setting the bit         **
**                    position 0 of the input parameter)                      **
**                    The delay shall be passed as ticks count for STM        **
**                                                                            **
**                    Example for delay calculation:                          **
                        Delay = 12.800 Microseconds                           **
**                      STM frequency = 100 MHz                               **
**                      Tstmperiod = 1/100MHz = 10ns = 0.01Microseconds       **
**                      Ticks = Delay/TstmPeriod = 1280 ticks                 **
**                                                                            **
**                   Note: Carrier signal is also restarted along wih the     **
**                        integartor                                          **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0xF1U                                                   **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : ChannelId - Bit coded information for the DSADC logical **
**                    channel numbers. DSADC logical channel enable or disable**
**                    is indicated by the corresponding bit position.         **
**                                                                            **
**                    Delay - The delay to be inserted between the restart    **
**                    of integrator for selected channels. The delay          ** 
**                    parameter is in ticks.                                  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK : Integrator is restarted for all the DSADC        **
**                           channels requested                               **
**                    E_NOT_OK: Integrator is not Restarted                   **
*******************************************************************************/
Std_ReturnType Dsadc_RestartIntegrator(const Dsadc_ChannelMaskType ChannelId,
                                       const Dsadc_DelayType Delay);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an function is called but the related functionality 
  is disabled */
#define Dsadc_RestartIntegrator(ChannelId,Delay) \
                            (ERROR_Dsadc_RestartIntegrator_API_IS_NOT_SELECTED)
#endif

#if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : void Dsadc_Isr                                          **
**                    (                                                       **
**                      const Dsadc_ChannelType HwChannelId                   **
**                    )                                                       **
**                                                                            **
** Description      : Handles the interrupts from Main Service Request for    **
**                    the passed DSADC channel.                               **
**                                                                            **
** Service ID       : 0x2A                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant for same channel, reentrant  for other    **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : HwChannelId - DSADC Hardware channel ID                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : void                                                    **
*******************************************************************************/
extern void Dsadc_Isr(const Dsadc_ChannelType HwChannelId);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an function is called but the related functionality 
  is disabled */
#define Dsadc_Isr(HwChannelId) (ERROR_Dsadc_Isr_API_IS_NOT_SELECTED)
#endif


#define DSADC_STOP_SEC_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline.*/
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
  without safegaurd. It complies to Autosar guidelines. */
#include "Dsadc_MemMap.h"

/* The file is included to get extern declaration of all the configuration root
structure. The extern declaration of configuration root structure is needed by
application software */
#include "Dsadc_PBcfg.h"

#endif /* End for DSADC_H */
