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
**  FILENAME     : Fr_17_Eray.h                                               **
**                                                                            **
**  VERSION      : 14.0.0                                                     **
**                                                                            **
**  DATE         : 2023-05-17                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Fr Driver header definition file                           **
**                                                                            **
**  SPECIFICATION(S) : Specification of FlexRay Driver, AUTOSAR Release 4.2.2 **
**                     and 4.4.0                                              **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/* [cover parentID={7A09C695-9B2F-4b5d-9CBB-B88864F61A9A}] */
/*  [/cover] */

#ifndef FR_17_ERAY_H
#define FR_17_ERAY_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/* Types and constants shared among Fr, FrIf and FrTrcv. */
/* [cover parentID={574A6292-FB57-4a0e-8B72-AF30A68E0B8D}] */
#include "Fr_GeneralTypes.h"
/*  [/cover] */

/* Pre-compile configuration parameters for FR */
#include "Fr_17_Eray_Cfg.h"

/* [cover parentID={2DE502EC-DFC7-4aad-8935-DD49512AF394},
    {256B13B3-12D0-4b68-955D-EC3B6457FF27}] */
/* Mcal_Wrapper header file */
#include "Mcal_Wrapper.h"
/*  [/cover] */

#include "McalLib.h"

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/*
  Published parameters
*/
/* [cover parentID={3EC10B38-9D7C-40ee-9825-E088466FF77D}] */
/* Fr Vendor ID */
#define FR_17_ERAY_VENDOR_ID                  (17U)
/* Fr Module ID */
#define FR_17_ERAY_MODULE_ID                  ((uint16)0x51)
/*  [/cover] */

/* [cover parentID={C3A0CE28-A4F8-4334-89FF-F9C31A594A1F}] */
/* API parameter timer index exceeds number of available timers */
#define FR_17_ERAY_E_INV_TIMER_IDX    ((uint8)0x01)
/* [/cover] */

/* [cover parentID={C89812DD-1C18-4265-B559-5481582AF758}] */
/* Invalid pointer in parameter list */
#define FR_17_ERAY_E_PARAM_POINTER    ((uint8)0x02)
/* [/cover] */

/* [cover parentID={B8D1B011-3124-4681-8E38-5EEF36D13AAB}] */
/* Parameter offset exceeds bounds */
#define FR_17_ERAY_E_INV_OFFSET       ((uint8)0x03)
/* [/cover] */

/* [cover parentID={856B013D-9488-4c7e-8599-2C6EBC97E343}] */
/* Invalid controller index */
#define FR_17_ERAY_E_INV_CTRL_IDX     ((uint8)0x04)
/* [/cover] */

/* [cover parentID={09AAF9BD-9F82-48b2-AFF0-250CF23ABCF7}] */
/* Invalid channel index */
#define FR_17_ERAY_E_INV_CHNL_IDX     ((uint8)0x05)
/* [/cover] */

/* [cover parentID={793AD559-36B2-4771-BD87-E5315C63C4F1}] */
/* Parameter cycle exceeds 63 */
#define FR_17_ERAY_E_INV_CYCLE        ((uint8)0x06)
/* [/cover] */

/* [cover parentID={67AF544D-0026-4b56-9572-8A70C8510A65}] */
/* Fr module was not initialized */
#define FR_17_ERAY_E_INIT_FAILED      ((uint8)0x08)
/* [/cover] */

/* [cover parentID={F277147C-EBA0-468d-BB72-1C800A89068A}] */
/* Fr CC is not in the expected POC state. */
#define FR_17_ERAY_E_INV_POCSTATE     ((uint8)0x09)
/* [/cover] */

/* [cover parentID={5A47C140-CF56-40aa-A8A2-5FB48C89CCC9}] */
/* Payload length parameter has an invalid value. */
#define FR_17_ERAY_E_INV_LENGTH       ((uint8)0x0A)
/* [/cover] */

/* [cover parentID={8AC4E387-AE3D-4314-8015-9B4985854B41}] */
/* Invalid LPdu index */
#define FR_17_ERAY_E_INV_LPDU_IDX     ((uint8)0x0B)
/* [/cover] */

/* [cover parentID={1A767B5F-D47D-410d-8A17-1629E013FCEF}] */
/* Invalid FlexRay header CRC */
#define FR_17_ERAY_E_INV_HEADERCRC    ((uint8)0x0C)
/* [/cover] */

/* [cover parentID={ABB414D9-0ED7-4895-8D40-852823AAF606}] */
/* Invalid value passed as parameter Fr_ConfigParamIdx */
#define FR_17_ERAY_E_INV_CONFIG_IDX   ((uint8)0x0D)
/* [/cover] */

/* [cover parentID={7C7C0437-1609-4425-AF78-45676390AFF8}] */
/* Invalid value passed as parameter Fr_ListSize */
#define FR_17_ERAY_E_INV_FRAMELIST_SIZE ((uint8)0x0E)
/* [/cover] */

/* Macro for no error detection, This is for module internal use only */
#define FR_17_ERAY_E_DET_NO_ERR       ((uint32)0)

/*
  Service IDs. Used while reporting development errors.
*/
#define FR_17_ERAY_SID_INIT                         ((uint8)0x1c)
#define FR_17_ERAY_SID_CONTROLLERINIT               ((uint8)0x00)
#define FR_17_ERAY_SID_STARTCOMMUNICATION           ((uint8)0x03)
#define FR_17_ERAY_SID_ALLOWCOLDSTART               ((uint8)0x23)
#define FR_17_ERAY_SID_ALLSLOTS                     ((uint8)0x24)
#define FR_17_ERAY_SID_HALTCOMMUNICATION            ((uint8)0x04)
#define FR_17_ERAY_SID_ABORTCOMMUNICATION           ((uint8)0x05)
#define FR_17_ERAY_SID_SENDWUP                      ((uint8)0x06)
#define FR_17_ERAY_SID_SETWAKEUPCHANNEL             ((uint8)0x07)
#define FR_17_ERAY_SID_GETPOCSTATUS                 ((uint8)0x0a)
#define FR_17_ERAY_SID_TRANSMITTXLPDU               ((uint8)0x0b)
#define FR_17_ERAY_SID_CANCELTXLPDU                 ((uint8)0x2d)
#define FR_17_ERAY_SID_RECEIVERXLPDU                ((uint8)0x0c)
#define FR_17_ERAY_SID_CHECKTXLPDUSTATUS            ((uint8)0x0d)
#define FR_17_ERAY_SID_PREPARELPDU                  ((uint8)0x1f)
#define FR_17_ERAY_SID_RECONFIGLPDU                 ((uint8)0x25)
#define FR_17_ERAY_SID_DISABLELPDU                  ((uint8)0x26)
#define FR_17_ERAY_SID_GETGLOBALTIME                ((uint8)0x10)
#define FR_17_ERAY_SID_GETNMVECTOR                  ((uint8)0x22)
#define FR_17_ERAY_SID_GETNUMOFSTARTUPFRAMES        ((uint8)0x27)
#define FR_17_ERAY_SID_GETCHANNELSTATUS             ((uint8)0x28)
#define FR_17_ERAY_SID_GETCLOCKCORRECTION           ((uint8)0x29)
#define FR_17_ERAY_SID_GETSYNCFRAMELIST             ((uint8)0x2a)
#define FR_17_ERAY_SID_GETWAKEUPRXSTATUS            ((uint8)0x2b)
#define FR_17_ERAY_SID_SETABSOLUTETIMER             ((uint8)0x11)
#define FR_17_ERAY_SID_CANCELABSOLUTETIMER          ((uint8)0x13)
#define FR_17_ERAY_SID_ENABLEABSOLUTETIMERIRQ       ((uint8)0x15)
#define FR_17_ERAY_SID_ACKABSOLUTETIMERIRQ          ((uint8)0x17)
#define FR_17_ERAY_SID_DISABLEABSOLUTETIMERIRQ      ((uint8)0x19)
#define FR_17_ERAY_SID_GETABSTIMERIRQSTATUS         ((uint8)0x20)
#define FR_17_ERAY_SID_GETVERSIONINFO               ((uint8)0x1b)
#define FR_17_ERAY_SID_READCCCONFIG                 ((uint8)0x2e)


/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/

/* ---------------------------------------------------------------------------*/

/*
  Type definition for data structure containing configuration parameters for
  a FlexRay communication controller.
*/
/* [cover parentID={ABF6940D-8B29-4865-8974-E25C96FB0F5F}] */
typedef struct
{
  uint32 Succ1CfgVal;    /* Configuration value for register SUCC1 */
  uint32 Succ2CfgVal;    /* Configuration value for register SUCC2 */
  uint32 Succ3CfgVal;    /* Configuration value for register SUCC3 */
  uint32 NemcCfgVal;     /* Configuration value for register NEMC */
  uint32 Prtc1CfgVal;    /* Configuration value for register PRTC1 */
  uint32 Prtc2CfgVal;    /* Configuration value for register PRTC2 */
  uint32 MhdcCfgVal;     /* Configuration value for register MHDC */
  uint32 Gtuc01CfgVal;   /* Configuration value for register GTUC01 */
  uint32 Gtuc02CfgVal;   /* Configuration value for register GTUC02 */
  uint32 Gtuc03CfgVal;   /* Configuration value for register GTUC03 */
  uint32 Gtuc04CfgVal;   /* Configuration value for register GTUC04 */
  uint32 Gtuc05CfgVal;   /* Configuration value for register GTUC05 */
  uint32 Gtuc06CfgVal;   /* Configuration value for register GTUC06 */
  uint32 Gtuc07CfgVal;   /* Configuration value for register GTUC07 */
  uint32 Gtuc08CfgVal;   /* Configuration value for register GTUC08 */
  uint32 Gtuc09CfgVal;   /* Configuration value for register GTUC09 */
  uint32 Gtuc10CfgVal;   /* Configuration value for register GTUC10 */
  uint32 Gtuc11CfgVal;   /* Configuration value for register GTUC11 */
  uint32 Cust1CfgVal;    /* Configuration value for register CUST1 */
} Fr_17_Eray_CCConfigType;
/*  [/cover] */
/* ---------------------------------------------------------------------------*/

/*
  Type definition for data structure containing configuration parameters for
  a message buffer.
*/
/* [cover parentID={249B8A64-D0F9-4dec-8CAE-51A68DD9F6B0}] */
typedef struct
{
  uint32 Wrhs1CfgVal;   /* Configuration value for register WRHS1 */
  uint32 Wrhs2CfgVal;   /* Configuration value for register WRHS2 */
  uint8  LpduReconfigurable; /* FrIfReconfigurable - is an Lpdu is dynamically
                                reconfigurable */
  Dem_EventIdType FrDemFTSlotStatusErrId; /* DEM Id for FlexRay Slot Status
                                             Error. */
} Fr_17_Eray_LPduConfigType;
/*  [/cover] */
/* ---------------------------------------------------------------------------*/

#if (FR_17_ERAY_FIFO_CONFIGURED == STD_ON)
/*
  Data type for FR Receive receive FIFO configuration.
*/
/* [cover parentID={801BE27B-D6A9-4aed-81A7-DAE3FFC0032A}] */
typedef struct
{
  /*
  Fifo Rejection Filter criteria
  FrChannels|(FrFid<<2)|((FrCycleRepetition|FrBaseCycle)<<16U)|(RSS<23)|(RNF<24)
  */
  uint32 FrFifoFrfCfg;

  /* FIFO Rejection Filter Mask */
  uint16 FrFifoFrfm;

  /* Fifo Depth.*/
  uint8 FrFifoDepth;

} Fr_17_Eray_RxFifoConfigType;
/*  [/cover] */
#endif  /* (FR_17_ERAY_FIFO_CONFIGURED == STD_ON) */

/*
  This is the type of FlexRay external data structure containing the
  initialization data for the individual FlexRay controller.
*/
/* [cover parentID={0F241661-B09B-478f-8F03-7B9A1F7C1B3C}] */
typedef struct
{
  /* Pointer to configuration of Communication Controller */
  const Fr_17_Eray_CCConfigType *CCCfgPtr;

  /* Pointer to array of LPDU configurations */
  const Fr_17_Eray_LPduConfigType *LPduConfigPtr;

  #if (FR_17_ERAY_FIFO_CONFIGURED == STD_ON)
  /* Pointer to the configuration of Receive FIFO */
  const Fr_17_Eray_RxFifoConfigType *RxFifoConfigPtr;
  #endif

  /* Pointer to array of FR parameters accessed by Fr_ReadCCConfig */
  const uint32 *ConfigParamPtr;

  /* Pointer to LPDU to message buffer mapping array */
  const uint8 *LPduIdx2MsgBuffIdxPtr;

  /* Pointer to data pointer offsets of message buffers */
  const uint16 *DataPointerOffsetPtr;

  /* Number of LPDUs configured */
  uint16 LPduCount;

  /* Eray System Clock Divider */
  uint8 FrClockDivider;

  /* Flag to indicate whether the Buffer reconfiguration is ON */
  uint8 FrIsBuffReconfigOn;

  /* Dem Event Id References */
  /* DEM Id for FlexRay controller hardware test failure. */
  Dem_EventIdType FrDemCtrlTestResultId;

  /* Number of Message buffers configured */
  uint8 MsgBuffCountMax;

} Fr_17_Eray_CCType;
/*  [/cover] */

/*
  This is the type of FlexRay external data structure containing the overall
  initialization data for the FlexRay Driver.
*/
/* [cover parentID={E80C00A7-BFC9-4eb8-B826-0ECD6BCC9671}] */
typedef struct
{
  /* Pointer to the data structure containing the
  initialization data for the individual FlexRay controller */
  const Fr_17_Eray_CCType *CfgPtr ;

  /* Pointer to Physical to Logical Indexing map array */
  const uint8 *Phy2LogIdxPtr ;

} Fr_17_Eray_ConfigType ;
/*  [/cover] */

/* ---------------------------------------------------------------------------*/


/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/


/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Functions                                      **
*******************************************************************************/
/* Memory Map of the FR Code */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
Memory mapping for code
[/cover] */
/* [cover parentID={DF28B3B6-C88D-459e-8E7C-E5538C958549}]
Fr_17_Eray_MemMap.h
[/cover] */
#define FR_17_ERAY_START_SEC_CODE_QM_LOCAL
#include "Fr_17_Eray_MemMap.h"

/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : void Fr_17_Eray_Init( const Fr_17_Eray_ConfigType        **
**                                                     * const Fr_ConfigPtr)  **
**                                                                            **
** Description     : Initializes the Fr                                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  0x1c                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant                                           **
**                                                                            **
** Parameters (in) : Fr_ConfigPtr - Address to an Fr dependent configuration  **
**                                  structure that contains all information   **
**                                  for operating the Fr subsequently.        **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
extern void Fr_17_Eray_Init(const Fr_17_Eray_ConfigType* const Fr_ConfigPtr);

/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_ControllerInit                 **
**                                                  (const uint8 Fr_CtrlIdx)  **
**                                                                            **
** Description     : Initializes a FlexRay CC.                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  0x00                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_ControllerInit (const uint8 Fr_CtrlIdx);

/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_StartCommunication             **
**                                                  (const uint8 Fr_CtrlIdx)  **
**                                                                            **
** Description     : Starts FlexRay communication.                            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  0x03                                                    **
**                                                                            **
** Sync/Async      :  Asynchronous                                            **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_StartCommunication(const uint8 Fr_CtrlIdx );

/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_AllowColdstart                 **
**                                                  (const uint8 Fr_CtrlIdx)  **
**                                                                            **
** Description     : Invokes the CC CHI command 'ALLOW_COLDSTART'.            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  0x23                                                    **
**                                                                            **
** Sync/Async      :  Asynchronous                                            **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_AllowColdstart(const uint8 Fr_CtrlIdx );

/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_AllSlots                       **
**                                                  (const uint8 Fr_CtrlIdx)  **
**                                                                            **
** Description     : Invokes the CC CHI command 'ALL_SLOTS'.                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  0x24                                                    **
**                                                                            **
** Sync/Async      :  Asynchronous                                            **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_AllSlots(const uint8 Fr_CtrlIdx );


/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_HaltCommunication              **
**                                                  (const uint8 Fr_CtrlIdx)  **
**                                                                            **
** Description     : Invokes the CC CHI command 'HALT'.                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  0x04                                                    **
**                                                                            **
** Sync/Async      :  Asynchronous                                            **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_HaltCommunication(const uint8 Fr_CtrlIdx );

/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_AbortCommunication             **
**                                                  (const uint8 Fr_CtrlIdx)  **
**                                                                            **
** Description     : Invokes the CC CHI command 'FREEZE'.                     **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  0x05                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_AbortCommunication(const uint8 Fr_CtrlIdx );

/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_SendWUP                        **
**                                                  (const uint8 Fr_CtrlIdx)  **
**                                                                            **
** Description     : Invokes the CC CHI command 'WAKEUP'.                     **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  0x06                                                    **
**                                                                            **
** Sync/Async      :  Asynchronous                                            **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_SendWUP(const uint8 Fr_CtrlIdx );

/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_SetWakeupChannel               **
**                                         (const uint8 Fr_CtrlIdx,           **
**                                          const Fr_ChannelType Fr_ChnlIdx)  **
**                                                                            **
** Description     : Sets a wakeup channel.                                   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  0x07                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                   Fr_ChnlIdx - Index of FlexRay channel within the context **
**                                of the FlexRay CC Fr_CtrlIdx. Valid values  **
**                                are FR_CHANNEL_A and FR_CHANNEL_B.          **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_SetWakeupChannel
(
  const uint8 Fr_CtrlIdx,
  const Fr_ChannelType Fr_ChnlIdx
);

/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_GetPOCStatus(                  **
**                               const uint8 Fr_CtrlIdx,                      **
**                               Fr_POCStatusType* const Fr_POCStatusPtr      **
**                                                         )                  **
**                                                                            **
** Description     : Gets the POC status.                                     **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  0x0a                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                                                                            **
** Parameters (out): Fr_POCStatusPtr - Address the output value is stored to. **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_GetPOCStatus
(
  const uint8 Fr_CtrlIdx,
  Fr_POCStatusType* const Fr_POCStatusPtr
);

#if (MCAL_AR_VERSION == MCAL_AR_440)
/*******************************************************************************
** Traceability    : [cover parentID={F349C525-8D6C-47ea-82B2-9FEF41F74655}]  **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_TransmitTxLPdu(                **
**                         const uint8 Fr_CtrlIdx,                            **
**                         const uint16 Fr_LPduIdx,                           **
**                         const uint8 * const Fr_LSduPtr,                    **
**                         const uint8 Fr_LSduLength                          **
**                         Fr_SlotAssignmentType * const Fr_SlotAssignmentPtr **
**                         )                                                  **
**                                                                            **
** Description     : Transmits data on the FlexRay network                    **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  0x0b                                                    **
**                                                                            **
** Sync/Async      :  Asynchronous                                            **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                   Fr_LPduIdx - This index is used to uniquely identify a   **
**                                  FlexRay frame.                            **
**                   Fr_LSduPtr - This reference points to a buffer where the **
**                                  assembled LSdu to be transmitted within   **
**                                  this LPdu is stored at.                   **
**                   Fr_LSduLength - Determines the length of the data (in    **
**                                   Bytes) to be transmitted.                **
**                  Fr_SlotAssignmentPtr - This reference points to the memory**
**                           location where current slotid, cycle count and   **
**                           channelID shall be stored.                       **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_TransmitTxLPdu
(
    const uint8 Fr_CtrlIdx,
    const uint16 Fr_LPduIdx,
    const uint8 * const Fr_LSduPtr,
    const uint8 Fr_LSduLength,
    Fr_SlotAssignmentType * const Fr_SlotAssignmentPtr
);
#elif (MCAL_AR_VERSION == MCAL_AR_422)
/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_TransmitTxLPdu(                **
**                                    const uint8 Fr_CtrlIdx,                 **
**                                    const uint16 Fr_LPduIdx,                **
**                                    const uint8 * const Fr_LSduPtr,         **
**                                    const uint8 Fr_LSduLength               **
**                         )                                                  **
**                                                                            **
** Description     : Transmits data on the FlexRay network                    **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  0x0b                                                    **
**                                                                            **
** Sync/Async      :  Asynchronous                                            **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                   Fr_LPduIdx - This index is used to uniquely identify a   **
**                                  FlexRay frame.                            **
**                   Fr_LSduPtr - This reference points to a buffer where the **
**                                  assembled LSdu to be transmitted within   **
**                                  this LPdu is stored at.                   **
**                   Fr_LSduLength - Determines the length of the data (in    **
**                                   Bytes) to be transmitted.                **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_TransmitTxLPdu
(
  const uint8 Fr_CtrlIdx,
  const uint16 Fr_LPduIdx,
  const uint8* const Fr_LSduPtr,
  const uint8 Fr_LSduLength
);
#endif

/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_CancelTxLPdu(                  **
**                                    const uint8 Fr_CtrlIdx,                 **
**                                    const uint16 Fr_LPduIdx                 **
**                                   )                                        **
**                                                                            **
** Description     : Cancels the already pending transmission of a LPdu       **
                     contained in a controllers physical transmit resource    **
                     (e.g. message buffer).                                   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  0x2d                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                   Fr_LPduIdx - This index is used to uniquely identify a   **
**                                  FlexRay frame.                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_CancelTxLPdu
(
  const uint8 Fr_CtrlIdx,
  const uint16 Fr_LPduIdx
);

#if (MCAL_AR_VERSION == MCAL_AR_440)
/*******************************************************************************
** Traceability    : [cover parentID={957D8DC7-8DBC-42b2-A2FE-2CE881036830}]  **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_ReceiveRxLPdu(                 **
**                         const uint8 Fr_CtrlIdx,                            **
**                         const uint16 Fr_LPduIdx,                           **
**                         uint8 * const Fr_LSduPtr,                          **
**                         Fr_RxLPduStatusType * const Fr_RxLPduStatusPtr,    **
**                         uint8 * const Fr_LSduLengthPtr                     **
**                         Fr_SlotAssignmentType * const Fr_SlotAssignmentPtr **
**                         )                                                  **
**                                                                            **
** Description     : Receives data from the FlexRay network.                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  0x0c                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                   Fr_LPduIdx - This index is used to uniquely identify a   **
**                                  FlexRay frame.                            **
**                                                                            **
** Parameters (out):                                                          **
**                  Fr_LSduPtr - This reference points to a buffer where the  **
**                                  LSdu to be received shall be stored       **
**                  Fr_RxLPduStatusPtr - This reference points to the memory  **
**                                      location where the status of the LPdu **
**                                      shall be stored                       **
**                  Fr_LSduLengthPtr - This reference points to the memory    **
**                           location where the length of the LSdu (in bytes) **
**                           shall be stored. This length represents the      **
**                           number of bytes copied to LSduPtr.               **
**                  Fr_SlotAssignmentPtr - This reference points to the memory**
**                           location where current slotid, cycle count and   **
**                           channelID shall be stored.                       **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType  Fr_17_Eray_ReceiveRxLPdu
(
    const uint8 Fr_CtrlIdx,
    const uint16 Fr_LPduIdx,
    uint8 * const Fr_LSduPtr,
    Fr_RxLPduStatusType * const Fr_RxLPduStatusPtr,
    uint8 * const Fr_LSduLengthPtr,
    Fr_SlotAssignmentType * const Fr_SlotAssignmentPtr
);
#elif (MCAL_AR_VERSION == MCAL_AR_422)
/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_ReceiveRxLPdu(                 **
**                           const uint8 Fr_CtrlIdx,                          **
**                           const uint16 Fr_LPduIdx,                         **
**                           uint8 * const Fr_LSduPtr,                        **
**                           Fr_RxLPduStatusType * const Fr_RxLPduStatusPtr,  **
**                           uint8 * const Fr_LSduLengthPtr                   **
**                         )                                                  **
**                                                                            **
** Description     : Receives data from the FlexRay network.                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  0x0c                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                  Fr_LPduIdx - This index is used to uniquely identify a    **
**                                  FlexRay frame.                            **
**                                                                            **
** Parameters (out):                                                          **
**                  Fr_LSduPtr - This reference points to a buffer where the  **
**                                  LSdu to be received shall be stored       **
**                  Fr_RxLPduStatusPtr - This reference points to the memory  **
**                                      location where the status of the LPdu **
**                                      shall be stored                       **
**                  Fr_LSduLengthPtr - This reference points to the memory    **
**                           location where the length of the LSdu (in bytes) **
**                           shall be stored. This length represents the      **
**                           number of bytes copied to LSduPtr.               **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_ReceiveRxLPdu
(
  const uint8 Fr_CtrlIdx,
  const uint16 Fr_LPduIdx,
  uint8* const Fr_LSduPtr,
  Fr_RxLPduStatusType* const Fr_RxLPduStatusPtr,
  uint8* const Fr_LSduLengthPtr
);
#endif
#if(MCAL_AR_VERSION == MCAL_AR_440)
/*******************************************************************************
** Traceability    : [cover parentID={60D10B28-3FCB-4323-B3DF-BDE1DB63FDD8}]  **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_CheckTxLPduStatus(             **
**                          const uint8 Fr_CtrlIdx,                           **
**                          const uint16 Fr_LPduIdx,                          **
**                          Fr_TxLPduStatusType * const Fr_TxLPduStatusPtr    **
**                          Fr_SlotAssignmentType * const Fr_SlotAssignmentPtr**
**                         )                                                  **
**                                                                            **
** Description     : Checks the transmit status of the LSdu.                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  0x0d                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                                                                            **
**                   Fr_LPduIdx - This index is used to uniquely identify a   **
**                                  FlexRay frame.                            **
**                                                                            **
** Parameters (out): Fr_TxLPduStatusPtr - This reference is used to store the **
**                                        transmit status of the LPdu         **
**                   Fr_SlotAssignmentPtr - This reference points to the      **
**                           memory location where current slotid,            **
**                           cycle count and channelID shall be stored.       **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType  Fr_17_Eray_CheckTxLPduStatus
(
    const uint8 Fr_CtrlIdx,
    const uint16 Fr_LPduIdx,
    Fr_TxLPduStatusType * const Fr_TxLPduStatusPtr,
    Fr_SlotAssignmentType * const Fr_SlotAssignmentPtr
);
#elif (MCAL_AR_VERSION == MCAL_AR_422)
/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_CheckTxLPduStatus(             **
**                             const uint8 Fr_CtrlIdx,                        **
**                             const uint16 Fr_LPduIdx,                       **
**                             Fr_TxLPduStatusType * const Fr_TxLPduStatusPtr **
**                         )                                                  **
**                                                                            **
** Description     : Checks the transmit status of the LSdu.                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  0x0d                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                                                                            **
**                   Fr_LPduIdx - This index is used to uniquely identify a   **
**                                  FlexRay frame.                            **
**                                                                            **
** Parameters (out):                                                          **
**                  Fr_TxLPduStatusPtr - This reference is used to store the  **
**                                        transmit status of the LSdu         **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_CheckTxLPduStatus
(
  const uint8 Fr_CtrlIdx,
  const uint16 Fr_LPduIdx,
  Fr_TxLPduStatusType * const Fr_TxLPduStatusPtr
);
#endif
#if (FR_17_ERAY_PREPARE_LPDU == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_PrepareLPdu(                   **
**                                    const uint8 Fr_CtrlIdx,                 **
**                                    const uint16 Fr_LPduIdx,                **
**                         )                                                  **
**                                                                            **
** Description     : Prepares a LPdu.                                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  0x1f                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                   Fr_LPduIdx - This index is used to uniquely identify a   **
**                                  FlexRay frame.                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_PrepareLPdu
(
  const uint8 Fr_CtrlIdx,
  const uint16 Fr_LPduIdx
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application and
  not enabled in the configuration*/
#define Fr_17_Eray_PrepareLPdu( Fr_CtrlIdx, Fr_LPduIdx) \
ERROR_Fr_17_Eray_PrepareLPdu_API_IS_NOT_SELECTED
#endif /* (FR_17_ERAY_PREPARE_LPDU == STD_ON) */

#if (FR_17_ERAY_RECONFIG_LPDU == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_ReconfigLPdu(                  **
**                                     const uint8 Fr_CtrlIdx,                **
**                                     const uint16 Fr_LPduIdx,               **
**                                     const uint16 Fr_FrameId,               **
**                                     const Fr_ChannelType Fr_ChnlIdx,       **
**                                     const uint8 Fr_CycleRepetition,        **
**                                     const uint8 Fr_CycleOffset,            **
**                                     const uint8 Fr_PayloadLength,          **
**                                     const uint16 Fr_HeaderCRC              **
**                                           )                                **
**                                                                            **
** Description     : Reconfigures a given LPdu according to the parameters    **
**       (FrameId, Channel, CycleRepetition, CycleOffset, PayloadLength,      **
**       HeaderCRC) at runtime.                                               **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  0x25                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                   Fr_LPduIdx - This index is used to uniquely identify a   **
**                                FlexRay frame.                              **
**                   Fr_FrameId - FlexRay Frame ID the FrIf_LPdu shall be     **
**                                configured to.                              **
**                   Fr_ChnlIdx - FlexRay Channel the FrIf_LPdu shall be      **
**                                configured to.                              **
**                   Fr_CycleRepetition -Cycle Repetition part of the cycle   **
**                          filter mechanism FrIf_LPdu shall be configured to **
**                   Fr_CycleOffset - Cycle Offset part of the cycle filter   **
**                                mechanism FrIf_LPdu shall be configured to. **
**                   Fr_PayloadLength  - Payloadlength in units of bytes the  **
**                                FrIf_LPduIdx shall be configured to.        **
**                   Fr_HeaderCRC - Header CRC the FrIf_LPdu shall be         **
**                                  configured to.                            **
**                                                                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_ReconfigLPdu(
    const uint8 Fr_CtrlIdx,
    const uint16 Fr_LPduIdx,
    const uint16 Fr_FrameId,
    const Fr_ChannelType Fr_ChnlIdx,
    const uint8 Fr_CycleRepetition,
    const uint8 Fr_CycleOffset,
    const uint8 Fr_PayloadLength,
    const uint16 Fr_HeaderCRC
);

#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application and
  not enabled in the configuration*/
#define Fr_17_Eray_ReconfigLPdu(CtrlIdx, Fr_LPduIdx,Fr_FrameId,Fr_ChnlIdx, \
Fr_CycleRepetition, Fr_CycleOffset, Fr_PayloadLength, Fr_HeaderCRC)\
ERROR_Fr_17_Eray_ReconfigLPdu_API_IS_NOT_SELECTED
#endif /* (FR_17_ERAY_RECONFIG_LPDU == STD_ON) */

#if (FR_17_ERAY_DISABLE_LPDU == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_DisableLPdu(                   **
**                                           const uint8 Fr_CtrlIdx,          **
**                                           const uint16 Fr_LPduIdx,         **
**                                           )                                **
**                                                                            **
** Description     : Disables the hardware resource of a LPdu for             **
                     transmission/reception.                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  0x26                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                                                                            **
**                   Fr_LPduIdx - This index is used to uniquely identify a   **
**                                  FlexRay frame.                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_DisableLPdu(
    const uint8 Fr_CtrlIdx,
    const uint16 Fr_LPduIdx
);

#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application and
  not enabled in the configuration*/
#define Fr_17_Eray_DisableLPdu(CtrlIdx, Fr_LPduIdx )\
ERROR_Fr_17_Eray_DisableLPdu_API_IS_NOT_SELECTED
#endif /* (FR_17_ERAY_DISABLE_LPDU == STD_ON) */

/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_GetGlobalTime(                 **
**                                    const uint8 Fr_CtrlIdx,                 **
**                                    uint8* const Fr_CyclePtr,               **
**                                    uint16* const Fr_MacroTickPtr           **
**                         )                                                  **
**                                                                            **
** Description     : Gets the current global FlexRay time.                    **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  0x10                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                                                                            **
** Parameters (out):                                                          **
**                  Fr_CyclePtr - Address where the current FlexRay           **
**                                communication cycle value shall be stored.  **
**                  Fr_MacroTickPtr - Address where the current macrotick     **
**                                    value shall be stored.                  **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_GetGlobalTime
(
  const uint8 Fr_CtrlIdx,
  uint8* const Fr_CyclePtr,
  uint16* const Fr_MacroTickPtr
);

#if (FR_17_ERAY_NMVECTOR_ENABLE == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_GetNmVector(                   **
**                                    const uint8 Fr_CtrlIdx,                 **
**                                    uint8* const Fr_NmVectorPtr             **
**                         )                                                  **
**                                                                            **
** Description     : Gets the network management vector of the last           **
**                   communication cycle.                                     **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  0x22                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                                                                            **
** Parameters (out):                                                          **
**                  Fr_NmVectorPtr - Address where the NmVector of the last   **
**                                communication cycle shall be stored.        **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_GetNmVector
(
  const uint8 Fr_CtrlIdx,
  uint8* const Fr_NmVectorPtr
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application and
  not enabled in the configuration*/
#define Fr_17_Eray_GetNmVector(CtrlIdx, NmVectorPtr) \
ERROR_Fr_17_Eray_GetNmVector_API_IS_NOT_SELECTED
#endif /* (FR_17_ERAY_NMVECTOR_ENABLE == STD_ON) */

/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_GetNumOfStartupFrames(         **
**                                    const uint8 Fr_CtrlIdx,                 **
**                                    uint8* const Fr_NumOfStartupFramesPtr   **
**                                    )                                       **
**                                                                            **
** Description     : Gets the current number of startup frames seen on the    **
**                   cluster.                                                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  0x27                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                                                                            **
** Parameters (out):                                                          **
**          Fr_NumOfStartupFramesPtr - Address where the number of startup    **
**          frames seen within the last even/odd cycle pair shall be stored.  **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_GetNumOfStartupFrames
(
    const uint8 Fr_CtrlIdx,
    uint8* const Fr_NumOfStartupFramesPtr
);

/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_GetChannelStatus               **
                     (                                                        **
**                         const uint8 Fr_CtrlIdx,                            **
**                         uint16* const Fr_ChannelAStatusPtr,                **
**                         uint16* const Fr_ChannelBStatusPtr                 **
**                      )                                                     **
**                                                                            **
** Description     : Gets the channel status information.                     **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service  ID     :  0x28                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                                                                            **
** Parameters (out):                                                          **
**          Fr_ChannelAStatusPtr - Address where the bitcoded channel A       **
            status information shall be stored.                               **
            Fr_ChannelBStatusPtr - Address where the bitcoded channel B       **
            status information shall be stored.                               **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_GetChannelStatus
(
    const uint8 Fr_CtrlIdx,
    uint16* const Fr_ChannelAStatusPtr,
    uint16* const Fr_ChannelBStatusPtr
);

/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_GetClockCorrection             **
                          (                                                   **
                           const uint8 Fr_CtrlIdx,                            **
                           sint16* const Fr_RateCorrectionPtr,                **
                           sint32* const Fr_OffsetCorrectionPtr               **
                          )                                                   **
**                                                                            **
**                                                                            **
** Description     : Gets the current clock correction values.                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service  ID     :  0x29                                                    **
**                                                                            **
**  Sync/Async     :  Synchronous                                             **
**                                                                            **
**  Reentrancy     :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                                                                            **
** Parameters (out):                                                          **
**                   Fr_RateCorrectionPtr - Address where the current rate    **
**                             correction value shall be stored.              **
**                   Fr_ChannelBStatusPtr - Address where the current offset  **
**                             correction value shall be stored.              **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_GetClockCorrection
(
    const uint8 Fr_CtrlIdx,
    sint16* const Fr_RateCorrectionPtr,
    sint32* const Fr_OffsetCorrectionPtr
);

/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_GetSyncFrameList               **
                     (                                                        **
                          const uint8 Fr_CtrlIdx,                             **
                          const uint8 Fr_ListSize,                            **
                          uint16* const Fr_ChannelAEvenListPtr,               **
                          uint16* const Fr_ChannelBEvenListPtr,               **
                          uint16* const Fr_ChannelAOddListPtr,                **
                          uint16* const Fr_ChannelBOddListPtr                 **
                     )                                                        **
**                                                                            **
** Description     : Gets a list of syncframes received or transmitted on     **
                     channel A and channel B via the even and odd             **
                     communication cycle                                      **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service  ID     :  0x2a                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
                     the FlexRay Driver.                                      **
                     Fr_ListSize - Size of the arrays passed via parameters:  **
                     Fr_ChannelAEvenListPtr                                   **
                     Fr_ChannelBEvenListPtr                                   **
                     Fr_ChannelAOddListPtr                                    **
                     Fr_ChannelBOddListPtr.                                   **
                     The service must ensure to not write more entries into   **
                     those arrays than granted by this parameter.             **
**                                                                            **
** Parameters (out):                                                          **
**  Fr_ChannelAEvenListPtr - Address the list of syncframes on channel        **
        A within the even communication cycle is written to. The exact number **
        of elements written to the list is limited by parameter Fr_ListSize.  **
        Unused list elements are filled with the value '0' to indicate that   **
        no more syncframe has been seen.                                      **
    Fr_ChannelBEvenListPtr - Address the list of syncframes on channel B      **
        within the even communication cycle is written to. The exact number   **
        of elements written to the list is limited by parameter Fr_ListSize.  **
        Unused list elements are filled with the value '0' to indicate that   **
        no more syncframe has been seen.                                      **
    Fr_ChannelAOddListPtr - Address the list of syncframes on channel A       **
      within the odd communication cycle is written to. The exact number of   **
      elements written to the list is limited by parameter Fr_ListSize.       **
      Unused list elements are filled with the value '0' to indicate that     **
      no more syncframe has been seen.                                        **
    Fr_ChannelBOddListPtr - Address the list of syncframes on channel B       **
      within the odd communication cycle is written to. The exact number      **
      of elements written to the list is limited by parameter Fr_ListSize.    **
      Unused list elements are filled with the value '0' to indicate that     **
      no more syncframe has been seen.                                        **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_GetSyncFrameList
(
    const uint8 Fr_CtrlIdx,
    const uint8 Fr_ListSize,
    uint16* const Fr_ChannelAEvenListPtr,
    uint16* const Fr_ChannelBEvenListPtr,
    uint16* const Fr_ChannelAOddListPtr,
    uint16* const Fr_ChannelBOddListPtr
);

/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_GetWakeupRxStatus              **
                     (                                                        **
                         const uint8 Fr_CtrlIdx,                              **
                         uint8* const Fr_WakeupRxStatusPtr                    **
                     )                                                        **
                                                                              **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Description    : Gets the wakeup received information from the FlexRay     **
**                  controller.                                               **
**                                                                            **
** Service  ID     :  0x2b                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
                     the FlexRay Driver.                                      **
**                                                                            **
** Parameters (out):                                                          **
**                   Fr_WakeupRxStatusPtr - Address where bitcoded wakeup     **
**                   reception status shall be stored.                        **
**                    Bit 0: Wakeup received on channel A indicator           **
**                    Bit 1: Wakeup received on channel B indicator           **
**                    Bit 2-7: Unused                                         **
**                                                                            **
** Return value   :  E_OK: API call finished successfully.                    **
**                   E_NOT_OK: API call aborted due to errors.                **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_GetWakeupRxStatus
(
    const uint8 Fr_CtrlIdx,
    uint8* const Fr_WakeupRxStatusPtr
);

/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_SetAbsoluteTimer(              **
**                                    const uint8 Fr_CtrlIdx,                 **
**                                    const uint8 Fr_AbsTimerIdx,             **
**                                    const uint8 Fr_Cycle,                   **
**                                    const uint16 Fr_Offset                  **
**                         )                                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  0x11                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                  Fr_AbsTimerIdx - Index of absolute timer within the       **
**                                    context of the FlexRay CC.              **
**                  Fr_Cycle - Absolute cycle the timer shall elapse in.      **
**                  Fr_Offset - Offset within cycle Cycle in units of         **
**                              macrotick the timer shall elapse at.          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
** Description     :  Sets the absolute FlexRay timer.                        **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_SetAbsoluteTimer
(
  const uint8 Fr_CtrlIdx,
  const uint8 Fr_AbsTimerIdx,
  const uint8 Fr_Cycle,
  const uint16 Fr_Offset
);

/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_CancelAbsoluteTimer(           **
**                                    const uint8 Fr_CtrlIdx,                 **
**                                    const uint8 Fr_AbsTimerIdx              **
**                         )                                                  **
**                                                                            **
** Description     :  Stops an absolute timer.                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  0x13                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                  Fr_AbsTimerIdx - Index of absolute timer within the       **
**                                    context of the FlexRay CC.              **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_CancelAbsoluteTimer
(
  const uint8 Fr_CtrlIdx,
  const uint8 Fr_AbsTimerIdx
);

/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_EnableAbsoluteTimerIRQ(        **
**                                    const uint8 Fr_CtrlIdx,                 **
**                                    const uint8 Fr_AbsTimerIdx              **
**                         )                                                  **
**                                                                            **
** Description     :  Enables the interrupt line of an absolute timer.        **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  0x15                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                   Fr_AbsTimerIdx - Index of absolute timer within the      **
**                                    context of the FlexRay CC.              **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_EnableAbsoluteTimerIRQ
(
  const uint8 Fr_CtrlIdx,
  const uint8 Fr_AbsTimerIdx
);


/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_AckAbsoluteTimerIRQ(           **
**                                    const uint8 Fr_CtrlIdx,                 **
**                                    const uint8 Fr_AbsTimerIdx              **
**                         )                                                  **
**                                                                            **
** Description     :  Resets the interrupt condition of an absolute timer.    **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  0x17                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                  Fr_AbsTimerIdx - Index of absolute timer within the       **
**                                    context of the FlexRay CC.              **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_AckAbsoluteTimerIRQ
(
  const uint8 Fr_CtrlIdx,
  const uint8 Fr_AbsTimerIdx
);

/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_DisableAbsoluteTimerIRQ(       **
**                                    const uint8 Fr_CtrlIdx,                 **
**                                    const uint8 Fr_AbsTimerIdx              **
**                         )                                                  **
**                                                                            **
** Description     :  Disables the interrupt line of an absolute timer.       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  0x19                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                   Fr_AbsTimerIdx - Index of absolute timer within the      **
**                                    context of the FlexRay CC.              **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_DisableAbsoluteTimerIRQ
(
  const uint8 Fr_CtrlIdx,
  const uint8 Fr_AbsTimerIdx
);


/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_GetAbsoluteTimerIRQStatus(     **
**                                    const uint8 Fr_CtrlIdx,                 **
**                                    const uint8 Fr_AbsTimerIdx,             **
**                                    boolean* const Fr_IRQStatusPtr          **
**                         )                                                  **
**                                                                            **
** Description     :  Gets IRQ status of an absolute timer.                   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  0x20                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                   Fr_AbsTimerIdx - Index of absolute timer within the      **
**                                    context of the FlexRay CC.              **
**                                                                            **
** Parameters (out): Fr_IRQStatusPtr - Address the output value is stored to. **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_GetAbsoluteTimerIRQStatus
(
  const uint8 Fr_CtrlIdx,
  const uint8 Fr_AbsTimerIdx,
  boolean* const Fr_IRQStatusPtr
);

#if (FR_17_ERAY_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : void  Fr_17_Eray_GetVersionInfo                          **
**                    (                                                       **
**                      Std_VersionInfoType * const VersioninfoPtr            **
**                    )                                                       **
**                                                                            **
** Description     : This function returns the version information of this    **
**                   module. The version information include : Module ID,     **
**                   Vendor ID,Vendor specific version numbers                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      : 0x1b                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : none                                                     **
**                                                                            **
** Parameters (out): VersioninfoPtr - Pointer to where to store the           **
**                    version information of this module.                     **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
*******************************************************************************/
extern void Fr_17_Eray_GetVersionInfo
                             (Std_VersionInfoType * const VersioninfoPtr);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application and
  not enabled in the configuration*/
#define Fr_17_Eray_GetVersionInfo(VersioninfoPtr)                         \
                         ERROR_Fr_17_Eray_GetVersionInfo_API_IS_NOT_SELECTED
#endif /* (FR_17_ERAY_VERSION_INFO_API == STD_ON) */

/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_ReadCCConfig                   **
                     (                                                        **
                       const uint8 Fr_CtrlIdx,                                **
                       const uint8 Fr_ConfigParamIdx,                         **
                       uint32* const Fr_ConfigParamValuePtr                   **
                     )                                                        **
**                                                                            **
** Description     : Reads a FlexRay protocol configuration parameter for a   **
**                   particular FlexRay controller out of the module's        **
**                   configuration.                                           **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  0x2e                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                   Fr_ConfigParamIdx - Index that identifies the            **
                               configuration parameter to read.               **
**                                                                            **
** Parameters (out): Fr_ConfigParamValuePtr - Address the output value is     **
                     stored to.                                               **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fr_17_Eray_ReadCCConfig
(
    const uint8 Fr_CtrlIdx,
    const uint8 Fr_ConfigParamIdx,
    uint32* const Fr_ConfigParamValuePtr
);

/* Memory Map of the FR Code */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
Memory mapping for code
[/cover] */
#define FR_17_ERAY_STOP_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
#include "Fr_17_Eray_MemMap.h"

#include "Fr_17_Eray_PBcfg.h"

#endif /* FR_17_ERAY_H */
