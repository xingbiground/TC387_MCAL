
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
**  FILENAME     : Dio.h                                                      **
**                                                                            **
**  VERSION      : 9.0.0                                                     **
**                                                                            **
**  DATE         : 2023-07-05                                                 **
**                                                                            **
**  VARIANT      : Variant LT                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Dio Driver header definition file                          **
**                                                                            **
**  SPECIFICATION(S) : Specification of Dio Driver, AUTOSAR Release 4.2.2 and **
**                     AUTOSAR Release 4.4.0                                  **
**                                                                            **
**MAY BE CHANGED BY USER : no                                                 **
**                                                                            **
*******************************************************************************/
/* [cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}][/cover] */
/* [cover parentID={932945B3-2C26-47f5-B876-357C8EF56E38},
                  {AC8683E3-C8D8-4704-B9CC-4620683FE9C3}] [/cover]*/
#ifndef DIO_H
#define DIO_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/*  [cover parentID={9C4DD64A-BCE6-418b-984F-4A15129F83AD}] [/cover]*/
/* Inclusion of Platform_Types.h and Compiler.h */
#include "Std_Types.h"

/* Pre-compile/static configuration parameters for Dio  */
#include "Dio_Cfg.h"


/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/*  [cover parentID={24B75FCE-905E-48af-8523-0346834B3383}] [/cover] */

/* DIO Vendor ID */
#define DIO_VENDOR_ID                     (17U)
/* DIO Module ID */
#define DIO_MODULE_ID                     (120U)


#if ((DIO_SAFETY_ENABLE == STD_ON) || (DIO_DEV_ERROR_DETECT == STD_ON))
/* Development Errors */

/* Service is called with invalid parameter channel  */
/*  [cover parentID={6C6F5208-4953-409f-A67F-8DFB8DF98698}] [/cover] */
#define DIO_E_PARAM_INVALID_CHANNEL_ID   ((uint8)0x0A)
/* Service is called with invalid parameter port     */
/*  [cover parentID={3E8D6DFB-856B-4b7c-9BB4-C8191361E972}] [/cover] */
#define DIO_E_PARAM_INVALID_PORT_ID      ((uint8)0x14)
/* Service is called with invalid parameter group    */
/*  [cover parentID={2AA9113D-9689-4fe2-A718-CCB58AEC0393}] [/cover] */
#define DIO_E_PARAM_INVALID_GROUP        ((uint8)0x1F)
/* Service is called with Null pointer               */
/*  [cover parentID={AC0E41EB-301C-48ce-B46F-AA2EAE2C51AE}] [/cover] */
#define DIO_E_PARAM_POINTER              ((uint8)0x20)

/* Dio Service ID Numbers */

/* Dio_ReadChannel Service Id */
#define DIO_SID_READCHANNEL                   ((uint8)0U)
/* Dio_WriteChannel Service Id */
#define DIO_SID_WRITECHANNEL                  ((uint8)1U)
/* Dio_ReadPort Service Id */
#define DIO_SID_READPORT                      ((uint8)2U)
/* Dio_WritePort Service Id */
#define DIO_SID_WRITEPORT                     ((uint8)3U)
/* Dio_ReadChannelGroup Service Id */
#define DIO_SID_READCHANNELGROUP              ((uint8)4U)
/* Dio_WriteChannelGroup Service Id */
#define DIO_SID_WRITECHANNELGROUP             ((uint8)5U)

#if(DIO_FLIP_CHANNEL_API == STD_ON)
/* Dio_FlipChannel Service Id */
#define DIO_SID_FLIPCHANNEL                   ((uint8)17U)
#endif

#if(DIO_VERSION_INFO_API == STD_ON)
/* Dio_GetVersionInfo Service Id */
#define DIO_SID_GETVERSIONINFO                ((uint8)18U)
#endif

#if(DIO_MASKED_WRITE_PORT_API == STD_ON)
  /*Dio_MaskedWritePort Service Id */
#define DIO_SID_MASKEDWRITEPORT                ((uint8)19U)
#endif

#endif /*(DIO_DEV_ERROR_DETECT == STD_ON)*/

#if(DIO_SAFETY_ENABLE == STD_ON)
/*Report if Invalid level is passed */
#define DIO_E_PARAM_INVALID_LEVEL               ((uint8)50U)
#endif

/* DIO MODULE INSTANCE ID */
#define DIO_INSTANCE_ID              ((uint8)0U)

/*Macros to inform the Dio port is configured or not*/
#define DIO_PORT_NOT_CONFIGURED      ((uint8)0U)
#define DIO_PORT_CONFIGURED          ((uint8)1U)
/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/*  [cover parentID={B5F0C022-AA09-40d4-80A6-0DA99E77640E}] */
/*Type definition for numeric id of Dio Channels*/
typedef uint16 Dio_ChannelType;
/*  [/cover] */


/*  [cover parentID={C85FE8A9-804B-4974-8AA0-26619B64D350}] */
/*Type definition for possible levels that a Dio Channel can have*/
typedef uint8 Dio_LevelType;
/*  [/cover] */

/*  [cover parentID={39EBA438-2BB2-482a-B107-ED779F07E15A}] */
/*Type definition for numeric id of Dio Port*/
typedef uint8 Dio_PortType;
/*  [/cover] */

/*  [cover parentID={4B71595A-94D5-4413-BBE7-B4DF5B5DFED8}] */
/*Type definition for level of a Dio Port */
typedef uint16 Dio_PortLevelType;
/*  [/cover] */

/*  [cover parentID={94516F93-1557-469c-9B92-72EDE6446C04}] */
/*Type definition of a Dio Channel Group*/
typedef struct
{
  /*Defines the Position of Channel Group*/
  Dio_PortLevelType       mask;

  /*Defines the position of group from LSB*/
  uint8        offset;

  /*Port Number on which Channel Group is defined*/
  Dio_PortType port;
} Dio_ChannelGroupType;
/*  [/cover] */

/* [cover parentID= {29DF056F-4887-4821-B6D8-BA1FF4BF5542}] */
/*Type definition of Dio port and Channel configuration*/
typedef struct
{
  /*Configuration status of Port*/
  uint8 Dio_PortIdConfig;

  /*Defines the configured channels of port*/
  uint16 Dio_ChannelConfig;

} Dio_PortChannelIdType;
/*  [/cover] */

/*  [cover parentID={F31D3073-3F7A-4720-AC89-3D96E98B04D0}] */
/*Type definition for all configurable parameters of the DIO driver*/
typedef struct Dio_ConfigType
{
  /*Port and Channel configuration of Dio Driver*/
  const Dio_PortChannelIdType* Dio_PortChannelIdConfigPtr;

  /*Channel Group configuration*/
  const Dio_ChannelGroupType* Dio_ChannelGroupConfigPtr;

  /*Number of Channel Groups configured*/
  uint32 Dio_ChannelGroupConfigSize;
} Dio_ConfigType;
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
#define DIO_START_SEC_CODE_ASIL_B_GLOBAL
/*mapping of code and data to specific memory sections via memory mapping file*/
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Dio_Memmap.h header is included without safegaurd.*/
#include "Dio_MemMap.h"

/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax           : Dio_LevelType Dio_ReadChannel                           **
**                    (                                                       **
**                     const  Dio_ChannelType ChannelId                       **
**                    )                                                       **
**                                                                            **
** Description :  This Api:                                                   **
**      - returns the level of specified channel                              **
**      - The specified channel can be input or output                        **
**      - returns the physical level of the channel                           **
**  [/cover]                                                                  **
**                                                                            **
** Service ID:  0x00                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant                                                     **
**                                                                            **
** Parameters (in)  : ChannelId - ChannelId whose level to be read            **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : RetVal - The Api returns level                          **
**                    of the specified channel                                **
**                                                                            **
*******************************************************************************/
extern Dio_LevelType Dio_ReadChannel
(
  const Dio_ChannelType ChannelId
);

/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax           : void Dio_WriteChannel                                   **
**                    (                                                       **
**                     const Dio_ChannelType ChannelId,                       **
**                     const  Dio_LevelType Level                             **
**                    )                                                       **
**                                                                            **
**                                                                            **
** Description :  This Api:                                                   **
**      - sets the specified level for specified channel                      **
**      - Possible levels for channel are STD_HIGH and STD_LOW                **
**      - The real physical level of pin is not                               **
**        modified if the specified channel is configured as input            **
**      - For input channel this Api writes into the output                   **
**        register, so that pin level can be set immediately when direction   **
**        changed by PORT driver                                              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x01                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant                                                     **
**                                                                            **
** Parameters(in)   : ChannelId - ID of DIO channel                           **
**                    Level - Level to be written                             **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
extern void Dio_WriteChannel
(
  const Dio_ChannelType ChannelId,
  const Dio_LevelType Level
);

/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax           : Dio_PortLevelType Dio_ReadPort                          **
**                    (                                                       **
**                     const Dio_PortType PortId                              **
**                    )                                                       **
**                                                                            **
** Description :  This Api:                                                   **
**      - returns the level of specified port                                 **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x02                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant                                                     **
**                                                                            **
** Parameters (in):  PortId - Port id whose level to be read                  **
**                                                                            **
** Parameters (out):  none                                                    **
**                                                                            **
** Return value     : RetVal - The Api returns level                          **
**                    of the specified port                                   **
**                                                                            **
*******************************************************************************/
extern Dio_PortLevelType Dio_ReadPort
(
  const Dio_PortType PortId
);

/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax           : void Dio_WritePort                                      **
**                    (                                                       **
**                     const Dio_PortType PortId,                             **
**                     const Dio_PortLevelType Level                          **
**                    )                                                       **
**                                                                            **
**                                                                            **
** Description :  This Api:                                                   **
**      - sets the specified level for specified port                         **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x03                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant                                                     **
**                                                                            **
** Parameters(in)   : PortId - ID of DIO port                                 **
**                    Level - Level to be written                             **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
extern void Dio_WritePort
(
  const Dio_PortType PortId,
  const Dio_PortLevelType Level
);

/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax           : Dio_PortLevelType Dio_ReadChannelGroup                  **
**                    (                                                       **
**                      const Dio_ChannelGroupType * const ChannelGroupIdPtr  **
**                    )                                                       **
**                                                                            **
** Description :  This Api:                                                   **
**  - returns the level of specified channel group                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x04                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant                                                     **
**                                                                            **
** Parameters (in)  : ChannelGroupIdPtr -                                     **
**                    pointer to channel group configuration                  **
**                                                                            **
** Parameters (out):  none                                                    **
**                                                                            **
** Return value     : RetVal - The Api returns level                          **
**                    of the specified channel group                          **
**                                                                            **
*******************************************************************************/
extern Dio_PortLevelType Dio_ReadChannelGroup
(
  const Dio_ChannelGroupType * const ChannelGroupIdPtr
);

/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax           : void Dio_WriteChannelGroup                              **
**                    (                                                       **
**                      const Dio_ChannelGroupType * const ChannelGroupIdPtr  **
**                     const Dio_PortLevelType Level                          **
**                    )                                                       **
**                                                                            **
** Description :  This Api:                                                   **
**  - sets the level of specified channel group                               **
**  - The value for all the pins the channel group are set at one shot        **
**  - Other pins of the port and pins that are configured as                  **
**    input remains unchanged                                                 **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x05                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant                                                     **
**                                                                            **
** Parameters (in)  : ChannelGroupIdPtr -                                     **
**                    pointer to channel group configuration                  **
**                    Level - Sets level of specified channel group           **
**                                                                            **
** Parameters (out):  none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
extern void Dio_WriteChannelGroup
(
  const Dio_ChannelGroupType * const ChannelGroupIdPtr,
  const Dio_PortLevelType Level
);

#if (DIO_FLIP_CHANNEL_API == STD_ON)
/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax           : Dio_LevelType Dio_FlipChannel                           **
**                    (                                                       **
**                     const Dio_ChannelType ChannelId                        **
**                    )                                                       **
**                                                                            **
** Description :  This Api: Flip the channel level                            **
**      - returns the inverted level of specified output channel              **
**      - The specified channel is input, API shall have no influence         **
**        on the physical output of the channel                               **
**      - The specified channel is input, API shall have no influence         **
**        on the result of next Read service                                  **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x11                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant                                                     **
**                                                                            **
** Parameters (in)  : ChannelId - ChannelId whose level to be inverted        **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : RetVal - The Api returns the level                      **
**                  of the specified channel after inversion                  **
**                                                                            **
*******************************************************************************/
extern Dio_LevelType Dio_FlipChannel
(
  const Dio_ChannelType ChannelId
);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: With Dio_FlipChannel disabled
Dio_FlipChannel is implemented as Function like macro. Function like macro is
used to generate compilation error, when an optional function is called by the
application and not enabled in the configuration.*/
#define Dio_FlipChannel(ChannelId)(ERROR_Dio_FlipChannel_API_IS_NOT_SELECTED)
#endif /* End for DIO_FLIP_CHANNEL_API */

#if ( DIO_VERSION_INFO_API == STD_ON )
/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax :void Dio_GetVersionInfo                                            **
**                    (                                                       **
**                      Std_VersionInfoType * const VersionInfo               **
**                    )                                                       **
**                                                                            **
** Description :  This Api:                                                   **
**   - This Api returns the version information of this module                **
**     The version information include : Module ID, Vendor ID,                **
**     Vendor specific version numbers                                        **
**   - This Api is available if the DIO_VERSION_INFO_API is                   **
**     set ON                                                                 **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x12                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant                                                     **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  VersionInfo - Pointer to where to store the             **
**                    version information of this module.                     **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
extern void Dio_GetVersionInfo
(
  Std_VersionInfoType * const VersionInfo
);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: With Dio_GetVersionInfo disabled
Dio_GetVersionInfo is implemented as Function like macro. Function like macro
is used to generate compilation error, when an optional function is called by
the application and not enabled in the configuration.*/
#define Dio_GetVersionInfo(VersionInfo)(ERROR_Dio_GetVersionInfo_API_IS_NOT_SELECTED)
#endif /* #if (DIO_VERSION_INFO_API == STD_ON) */

#if (DIO_MASKED_WRITE_PORT_API == STD_ON )
/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax :void Dio_MaskedWritePort                                           **
**                    (                                                       **
**                     Dio_PortType PortId,                                   **
**                     Dio_PortLevelType Level,                               **
**                     Dio_PortLevelType Mask                                 **
**                    )                                                       **
**                                                                            **
** Description :  This Api:                                                   **
**   - Service to set the value of a given port with required mask.           **
**                                                                            **
**   - This Api is available if the Dio_MaskedWritePort is                    **
**     set ON                                                                 **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x13                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant                                                     **
**                                                                            **
** Parameters (in) :   PortId- ID of DIO Port                                 **
**                     Level - Value to be written                            **
**                     Mask - Channels to be masked in the port               **
** Parameters (out):                                                          **
**                                                                            **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
extern void Dio_MaskedWritePort
(
  const Dio_PortType PortId,
  const Dio_PortLevelType Level,
  const Dio_PortLevelType Mask
);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: With Dio_MaskedWritePort disabled
Dio_MaskedWritePort is implemented as Function like macro. Function like macro
is used to generate compilation error, when an optional function is called by
the application and not enabled in the configuration.*/
#define Dio_MaskedWritePort(PortId, Level, Mask)(ERROR_Dio_MaskedWritePort_API_IS_NOT_SELECTED)
#endif /* End for DIO_MASKED_WRITE_PORT */

/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/

#define DIO_STOP_SEC_CODE_ASIL_B_GLOBAL
/*mapping of code and data to specific memory sections via memory mapping file*/
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Dio_Memmap.h header is included without safegaurd.*/
#include "Dio_MemMap.h"

#endif   /*  DIO_H  */
