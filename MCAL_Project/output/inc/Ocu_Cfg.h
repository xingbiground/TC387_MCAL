
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
**  FILENAME  : Ocu_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 8.0.0                                                         **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:30              !!!IGNORE-LINE!!!       **
**                                                                            **
**  GENERATOR : Build b191017-0938                !!!IGNORE-LINE!!!         **
**                                                                            **
**                                                                            **
**  BSW MODULE DECRIPTION : NA                                                **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Ocu configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) :Specification of Ocu Driver,AUTOSAR Release 4.2.2&4.4.0 **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef OCU_CFG_H
#define OCU_CFG_H




/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/*Section to Generate Autosar Specific Version Information*/

#define OCU_AR_RELEASE_MAJOR_VERSION  (4U)
#define OCU_AR_RELEASE_MINOR_VERSION  (2U)
#define OCU_AR_RELEASE_REVISION_VERSION  (2U)

/*Section to Generate Vendor Specific Version Information*/
/* Vendor specific implementation version information */
#define OCU_SW_MAJOR_VERSION   (20U)
#define OCU_SW_MINOR_VERSION   (10U)
#define OCU_SW_PATCH_VERSION   (0U)

/* General Configuration */
/*
Configuration: OCU_DEV_ERROR_DETECT
Adds/removes the Development Error Detection 
from the code 
- if STD_ON, Development error detection is enabled
- if STD_OFF, Development error detection is disabled
*/
#define OCU_DEV_ERROR_DETECT                         (STD_ON)      
/*
Configuration: OCU_MULTICORE_ERROR_DETECT
Adds/removes the Multicore Error Detection 
from the code 
- if STD_ON, Multicore error detection is enabled
- if STD_OFF, Multicore error detection is disabled
*/
#define OCU_MULTICORE_ERROR_DETECT                         (STD_OFF)      

/*
Configuration : OCU_SAFETY_ENABLE
Pre-processor switch to enable/disable the OCU driver safety features.
*/
#define OCU_SAFETY_ENABLE               (STD_ON)      
/*  [/cover] */

/*
Configuration : OCU_INITCHECK_API
Pre-processor switch to enable/disable the OCU init check API.
*/
#define OCU_INITCHECK_API               (STD_ON)      
/*  [/cover] */
/*
Configuration: OCU_DE_INIT_API
Adds/removes Ocu_DeInit API 
from the code 
- if STD_ON, Ocu_DeInit is enabled
- if STD_OFF, Ocu_DeInit is disabled
*/
#define OCU_DE_INIT_API                              (STD_ON)      
/*
Configuration: OCU_SET_PIN_ACTION_API
Adds/removes Set Pin Action API from the code 
- if STD_ON, Ocu_SetPinAction is enabled
- if STD_OFF, Ocu_SetPinAction is disabled
*/
#define OCU_SET_PIN_ACTION_API                           (STD_ON)      
/*
Configuration: OCU_SET_PIN_STATE_API
Adds/removes Set Pin State API from the code 
- if STD_ON, Ocu_SetPinState is enabled
- if STD_OFF, Ocu_SetPinState is disabled
*/
#define OCU_SET_PIN_STATE_API                (STD_ON)      
/*
Configuration: OCU_GET_COUNTER_API
Adds/removes Get Counter API from the code 
- if STD_ON, Ocu_GetCounter is enabled
- if STD_OFF, Ocu_GetCounter is disabled
*/
#define OCU_GET_COUNTER_API                      (STD_ON)      
/*
Configuration: OCU_SET_ABSOLUTE_THRESHOLD_API
Adds/removes Set Absolute Threshold API from the code 
- if STD_ON, Ocu_SetAbsoluteThreshold is enabled
- if STD_OFF, Ocu_SetAbsoluteThreshold is disabled
*/
#define OCU_SET_ABSOLUTE_THRESHOLD_API                     (STD_ON)      
/*
Configuration: OCU_SET_RELATIVE_THRESHOLD_API
Adds/removes Set Relative Threshold API from the code 
- if STD_ON, Ocu_SetRelativeThreshold is enabled
- if STD_OFF, Ocu_SetRelativeThreshold is disabled
*/
#define OCU_SET_RELATIVE_THRESHOLD_API                     (STD_ON)      
/*
Configuration: OCU_VERSION_INFO_API
Adds/removes Get Version Info API from the code 
- if STD_ON, Ocu_GetVersionInfo is enabled
- if STD_OFF, Ocu_GetVersionInfo is disabled
*/
#define OCU_VERSION_INFO_API                     (STD_OFF)      
/*
Configuration: OCU_NOTIFICATION_SUPPORTED
Adds/removes Enable Notification and Disable Notification APIs from the code 
- if STD_ON, Ocu_EnableNotification and Ocu_DisableNotification are enabled
- if STD_OFF, Ocu_EnableNotification and Ocu_DisableNotification are disabled
*/
#define OCU_NOTIFICATION_SUPPORTED                             (STD_ON)      

/*
Core 0 Configurations    
*/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: decomposition of name is not possible,
Further distinct name can not be given*/
#ifndef OcuConf_OcuChannel_OCU_DEMO_CHANNEL
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: decomposition of name is not possible,
Further distinct name can not be given*/
#define OcuConf_OcuChannel_OCU_DEMO_CHANNEL       ((Ocu_ChannelType)0U)
#endif

/* Core 0 Configurations summary */
/* [cover parentID={C178A546-E7FB-4f7c-B406-585E5E43ECCC}] 
[/cover] */
#define OCU_MAX_CHANNELS_CORE0                   (1U)
/*  [/cover] */


/*
Core 1 Configurations    
*/

/* Core 1 Configurations summary */
/* [cover parentID={C178A546-E7FB-4f7c-B406-585E5E43ECCC}] 
[/cover] */
#define OCU_MAX_CHANNELS_CORE1                   (0U)
/*  [/cover] */

/*
Core 2 Configurations    
*/

/* Core 2 Configurations summary */
/* [cover parentID={C178A546-E7FB-4f7c-B406-585E5E43ECCC}] 
[/cover] */
#define OCU_MAX_CHANNELS_CORE2                   (0U)
/*  [/cover] */

/*
Core 3 Configurations    
*/

/* Core 3 Configurations summary */
/* [cover parentID={C178A546-E7FB-4f7c-B406-585E5E43ECCC}] 
[/cover] */
#define OCU_MAX_CHANNELS_CORE3                   (0U)
/*  [/cover] */

/*
Core 4 Configurations    
*/

/* Core 4 Configurations summary */
/* [cover parentID={C178A546-E7FB-4f7c-B406-585E5E43ECCC}] 
[/cover] */
#define OCU_MAX_CHANNELS_CORE4                   (0U)
/*  [/cover] */

/*
Core 5 Configurations    
*/

/* Core 5 Configurations summary */
/* [cover parentID={C178A546-E7FB-4f7c-B406-585E5E43ECCC}] 
[/cover] */
#define OCU_MAX_CHANNELS_CORE5                   (0U)
/*  [/cover] */



/***************************************************************************
TOTAL NUMBER OF CONFIGURED CHANNELS 
****************************************************************************/
#define OCU_MAX_CHANNELS         (1U)

/* Macro to idntify single core execution */
#define  OCU_SINGLE_CORE                  (STD_ON)      
#define  OCU_SINGLE_CORE_ID 0


#endif  /* OCU_CFG_H */


