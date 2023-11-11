
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
**  FILENAME  : Dio_Lcfg.c                                                    **
**                                                                            **
**  VERSION   : 7.0.0                                                         **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:31       !!!IGNORE-LINE!!!                  **
**                                                                            **
**  GENERATOR : Build b191017-0938           !!!IGNORE-LINE!!!                **
**                                                                            **
**  BSW MODULE DECRIPTION : Dio.bmd                                           **
**                                                                            **
**  VARIANT   : Variant LT                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Dio configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Dio Driver, AUTOSAR Release 4.2.2     **
**                    and AUTOSAR Release 4.4.0                               **
**                                                                            **
** MAY BE CHANGED BY USER : no                                                **
**                                                                            **
*******************************************************************************/


    
  /*******************************************************************************
  **                             Includes                                       **
  *******************************************************************************/

  /* Include Port Module File */
  #include "Dio.h"

  /*******************************************************************************
  **                      Private Macro Definitions                             **
  *******************************************************************************/

  /*******************************************************************************
  **                      Global Constant Definitions                           **
  *******************************************************************************/
  
  /* Memory mapping of the DIO configuration */
  #define DIO_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  /* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines 
  Dio_Memmap.h header is included without safegaurd.*/
  #include "Dio_MemMap.h"
  /*
      Configuration of DIO Channel groups 
  */
              
static const Dio_ChannelGroupType Dio_kChannelGroupConfig[DIO_CHANNELGROUPCOUNT]=
  {
  
    {/* DioPort_0, DioChGrpId_P33_0 */
    (Dio_PortLevelType)0xe0, /* Mask    */
    (uint8)5,              /* Offset  */
    (Dio_PortType)33          /* Port Id */
    }
};

  static const Dio_PortChannelIdType Dio_kPortChannelConfig[] =
  { 
    {
    /* Port0*/
      DIO_PORT_NOT_CONFIGURED,
      (0x0000U)
    },
    {
    /* Port1*/
      DIO_PORT_NOT_CONFIGURED,
      (0x0000U)
    },
    {
    /* Port2*/
      DIO_PORT_CONFIGURED,
      (0x0020U)
    },
    {
    /* Port10*/
      DIO_PORT_CONFIGURED,
      (0x0040U)
    },
    {
    /* Port11*/
      DIO_PORT_NOT_CONFIGURED,
      (0x0000U)
    },
    {
    /* Port12*/
      DIO_PORT_NOT_CONFIGURED,
      (0x0000U)
    },
    {
    /* Port13*/
      DIO_PORT_NOT_CONFIGURED,
      (0x0000U)
    },
    {
    /* Port14*/
      DIO_PORT_NOT_CONFIGURED,
      (0x0000U)
    },
    {
    /* Port15*/
      DIO_PORT_NOT_CONFIGURED,
      (0x0000U)
    },
    {
    /* Port20*/
      DIO_PORT_CONFIGURED,
      (0x0800U)
    },
    {
    /* Port21*/
      DIO_PORT_NOT_CONFIGURED,
      (0x0000U)
    },
    {
    /* Port22*/
      DIO_PORT_NOT_CONFIGURED,
      (0x0000U)
    },
    {
    /* Port23*/
      DIO_PORT_NOT_CONFIGURED,
      (0x0000U)
    },
    {
    /* Port24*/
      DIO_PORT_NOT_CONFIGURED,
      (0x0000U)
    },
    {
    /* Port25*/
      DIO_PORT_NOT_CONFIGURED,
      (0x0000U)
    },
    {
    /* Port26*/
      DIO_PORT_NOT_CONFIGURED,
      (0x0000U)
    },
    {
    /* Port30*/
      DIO_PORT_NOT_CONFIGURED,
      (0x0000U)
    },
    {
    /* Port31*/
      DIO_PORT_NOT_CONFIGURED,
      (0x0000U)
    },
    {
    /* Port32*/
      DIO_PORT_NOT_CONFIGURED,
      (0x0000U)
    },
    {
    /* Port33*/
      DIO_PORT_CONFIGURED,
      (0x04e0U)
    },
    {
    /* Port34*/
      DIO_PORT_NOT_CONFIGURED,
      (0x0000U)
    },
    {
    /* Port40*/
      DIO_PORT_NOT_CONFIGURED,
      (0x0000U)
    },
    {
    /* Port41*/
      DIO_PORT_NOT_CONFIGURED,
      (0x0000U)
    }
  };
    const Dio_ConfigType Dio_Config =
    {
                
      /* Dio Port and Channelconfiguration */
            &Dio_kPortChannelConfig[0],
      /* Dio Channelgroup configuration */
      
        &Dio_kChannelGroupConfig[0],
      /* Configured number of Dio Channelgroups for configuration */
      DIO_CHANNELGROUPCOUNT
    };
  #define DIO_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
    /* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines 
    Dio_Memmap.h header is included without safegaurd.*/
    /* MISRA2012_RULE_20_1_JUSTIFICATION: Dio_Memmap.h header included as per Autosar 
    guidelines. */
  #include "Dio_MemMap.h"

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/
