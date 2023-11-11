
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
**  FILENAME  : FlsLoader_Cfg.h                                               **
**                                                                            **
**  VERSION   : 10.0.0                                                         **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:31              !!!IGNORE-LINE!!!           **
**                                                                            **
**  GENERATOR : Build b191017-0938                !!!IGNORE-LINE!!!           **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : FlashLoader configuration generated out of ECUC file       **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/



#ifndef FLSLOADER_CFG_H
#define FLSLOADER_CFG_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/* Pflash sector size */
#define FLSLOADER_PF_SECTOR_SIZE          (0X004000U)  /* 16KB */
#define FLSLOADER_PF_SECTOR_NUMBER_OFFSET (14U)        /* 16KB = 2^14 */
#define FLSLOADER_PF_SECTOR_MASK          (0xFF)
#define FLSLOADER_TC39x   (1U)

#define NO_PROTECTION     (0U)
#define READ_PROTECTION   (1U)
#define WRITE_PROTECTION  (2U)
#define WOP_PROTECTION    (3U)
#define OTP_PROTECTION    (4U)


#define FLSLOADER_DERIVATIVE             (FLSLOADER_TC389x)
/* FLASH LOADER module instance ID */
#define FLSLOADER_INSTANCE_ID            ((uint8)1U)

#define FLSLOADER_AR_RELEASE_MAJOR_VERSION      (4U)
#define FLSLOADER_AR_RELEASE_MINOR_VERSION      (2U)
#define FLSLOADER_AR_RELEASE_REVISION_VERSION   (2U)

#define FLSLOADER_SW_MAJOR_VERSION       (20U)
#define FLSLOADER_SW_MINOR_VERSION       (20U)
#define FLSLOADER_SW_PATCH_VERSION       (0U)

#define FLSLOADER_NUM_OF_PFLASH_BANK     (4U)
#define FLSLOADER_NUM_OF_DFLASH_BANK     ((uint8)2U)

#define FLSLOADER_PFLASH0_START_ADDRESS  ((uint32)(0xa0000000U))
#define FLSLOADER_PFLASH0_END            ((FlsLoader_AddressType)(0xa02fffffU))
#define FLSLOADER_PFLASH0_SIZE           (0x300000U)
#define FLSLOADER_NUM_OF_PF0_SECTORS     (192U)

#define FLSLOADER_PFLASH1_START_ADDRESS  ((uint32)(0xa0300000U))
#define FLSLOADER_PFLASH1_END            ((FlsLoader_AddressType)(0xa05fffffU))
#define FLSLOADER_PFLASH1_SIZE           (0x300000U)
#define FLSLOADER_NUM_OF_PF1_SECTORS     (192U)

#define FLSLOADER_PFLASH2_START_ADDRESS  ((uint32)(0xa0600000U))
#define FLSLOADER_PFLASH2_END            ((FlsLoader_AddressType)(0xa08fffffU))
#define FLSLOADER_PFLASH2_SIZE           (0x300000U)
#define FLSLOADER_NUM_OF_PF2_SECTORS     (192U)

#define FLSLOADER_PFLASH3_START_ADDRESS  ((uint32)(0xa0900000U))
#define FLSLOADER_PFLASH3_END            ((FlsLoader_AddressType)(0xa09fffffU))
#define FLSLOADER_PFLASH3_SIZE           (0x100000U)
#define FLSLOADER_NUM_OF_PF3_SECTORS     (64U)

#define FLSLOADER_DFLASH0_START_ADDRESS  ((FlsLoader_AddressType)(0xaf000000U))
#define FLSLOADER_DFLASH0_END            ((FlsLoader_AddressType)(0xaf07ffffU))
#define FLSLOADER_DFLASH0_BANK_SIZE      (0x80000U)
#define FLSLOADER_NUM_OF_DF0_SECTORS     (128U)

#define FLSLOADER_DFLASH1_START_ADDRESS  ((FlsLoader_AddressType)(0xafc00000U))
#define FLSLOADER_DFLASH1_END            ((FlsLoader_AddressType)(0xafc1ffffU))
#define FLSLOADER_DFLASH1_BANK_SIZE      (0x20000U)
#define FLSLOADER_NUM_OF_DF1_SECTORS     (32U) 

/* UCB PFLASH Original address */
#define FLSLOADER_UCB_PFLASH_ORGINAL_START  ((FlsLoader_AddressType)(0xaf402000U))
#define FLSLOADER_UCB_PFLASH_ORGINAL_END    ((FlsLoader_AddressType)(0xaf4021ffU))
#define FLSLOADER_UCB_PFLASH_ORGINAL_SIZE   (0x80U)

/* UCB PFLASH Copy address */
#define FLSLOADER_UCB_PFLASH_COPY_START   ((FlsLoader_AddressType)(0xaf403000U))
#define FLSLOADER_UCB_PFLASH_COPY_END     ((FlsLoader_AddressType)(0xaf4031ffU))
#define FLSLOADER_UCB_PFLASH_COPY_SIZE    (0x200U)

/* UCB DFLASH Original address */
#define FLSLOADER_UCB_DFLASH_ORIGINAL_START ((FlsLoader_AddressType)(0xaf402200U))
#define FLSLOADER_UCB_DFLASH_ORGINAL_END    ((FlsLoader_AddressType)(0xaf4023ffU))
#define FLSLOADER_UCB_DFLASH_ORGINAL_SIZE   (0x80U)

/* UCB DFLASH Copy address */
#define FLSLOADER_UCB_DFLASH_COPY_START   ((FlsLoader_AddressType)(0xaf403200U))
#define FLSLOADER_UCB_DFLASH_COPY_END     ((FlsLoader_AddressType)(0xaf4033ffU))
#define FLSLOADER_UCB_DFLASH_COPY_SIZE    (0x200U)

/* UCB OTP0 address */
#define FLSLOADER_UCB_OTP0_START  ((FlsLoader_AddressType)(0xaf404000U))
#define FLSLOADER_UCB_OTP0_END    ((FlsLoader_AddressType)(0xaf4041ffU))
#define FLSLOADER_UCB_OTP0_SIZE   (0x80U)

/* UCB OTP7 Copy address */
#define FLSLOADER_UCB_START   ((FlsLoader_AddressType)(0xaf400000U))
#define FLSLOADER_UCB_END     ((FlsLoader_AddressType)(0xaf405fffU))
#define FLSLOADER_UCB_SIZE    (0x6000U)

#define FLSLOADER_PF_BANKS                (4U)
#define FLSLOADER_FLASH_BUSY_MASK         (0x0000003DU)
#define FLSLOADER_PFLASH_END              (FLSLOADER_PFLASH3_END)

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

#define FLSLOADER_START_SEC_CONST_QM_LOCAL_8
#include "FlsLoader_MemMap.h"

/* MISRA2012_RULE_8_9_JUSTIFICATION:FlsLoader_PFlashSectorCount is exported 
from FlsLoader_Cfg.c*/
extern const uint8 FlsLoader_PFlashSectorCount[FLSLOADER_NUM_OF_PFLASH_BANK];

#define FLSLOADER_STOP_SEC_CONST_QM_LOCAL_8
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "FlsLoader_MemMap.h"

/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond
   32 chars and this macro is used only inside the FLSLOADER module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the FLSLOADER module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the FLSLOADER module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the FLSLOADER module*/
#define FLSLOADER_START_SEC_CONST_QM_LOCAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "FlsLoader_MemMap.h"

extern const uint32 FlsLoader_PFlashOffset[FLSLOADER_NUM_OF_PFLASH_BANK];

/* MISRA2012_RULE_8_9_JUSTIFICATION: FlsLoader_PFlashEndAddress is generated in
   FlsLoader_Cfg.c and exported. Hence it can not be defined at block scope */
extern const uint32 FlsLoader_PFlashEndAddress[FLSLOADER_NUM_OF_PFLASH_BANK];

/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the FLSLOADER module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the FLSLOADER module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the FLSLOADER module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the FLSLOADER module*/
#define FLSLOADER_STOP_SEC_CONST_QM_LOCAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "FlsLoader_MemMap.h"

/*******************************************************************************
**                      Derived Macros                                        **
*******************************************************************************/

/*
Configuration: FLSLOADER_DEV_ERROR_DETECT
Preprocessor switch to enable/disable the development error detection and
reporting.
-If ON, Enable development error detecion
-If OFF,Disable development error detecion
*/
#define FLSLOADER_DEV_ERROR_DETECT       (STD_ON)

/*
Configuration: FLSLOADER_ENABLE_LOCKCHECK
Preprocessor switch to enable/disable the Lockcheck
The erase and write API's has Lock Check functionality, substantially
this is a big section, user could remove the same, if locking is not
used.
-If ON, Enable the FlsLoader Lockcheck in Write / Erase API's
-If OFF,Disable the FlsLoader Lockcheck in Write / Erase API's
*/
#define FLSLOADER_ENABLE_LOCKCHECK       (STD_OFF)

/*
Configuration: FLSLOADER_DEINIT_API
Preprocessor switch to enable/disable the deinitilize FlsLoader API
-If ON, Enable FlsLoader Deinitilization API
-If OFF,Disable FlsLoader Deinitilization API
*/
#define FLSLOADER_DEINIT_API             (STD_ON)


/*
Configuration: FLSLOADER_LOCK_UNLOCK_API
Preprocessor switch to enable/disable the Lock/UnLock API
-If ON, Enable the FlsLoader Lock/UnLock API
-If OFF,Disable FlsLoader Lock/UnLock API
*/
#define FLSLOADER_LOCK_UNLOCK_API        (STD_OFF)


/*
Configuration: FLSLOADER_CALLOUT_FUNC
Preprocessor switch to enable/disable the Loop CallOut function 
-If ON, Enable the FFlsLoader_lCallout Function 
-If OFF,Disable the FFlsLoader_lCallout Function 
*/
#define FLSLOADER_CALLOUT_FUNC           (STD_OFF)


/*
Configuration: FLSLOADER_CALLOUT_TIME
The maximum time in nanoseconds to wait before invoking call-out function to application
*/
#define FLSLOADER_CALLOUT_TIME           (5000000U)


/*
Configuration: FLSLOADER_VERSION_INFO_API
Preprocessor switch to enable/disable the versioninfo API
-If ON, Include the FlsLoader GetVersionInfo API
-If OFF,Disable FlsLoader GetVersionInfo API
*/
#define FLSLOADER_VERSION_INFO_API       (STD_OFF)


/* Configuration: FlsLoader PFlash0 Protection configuration */
#define FLSLOADER_PF0_PROT         (NO_PROTECTION)


/* Configuration: FlsLoader PFlash1 Protection configuration */
#define FLSLOADER_PF1_PROT        (NO_PROTECTION)


/* Configuration: FlsLoader PFlash2 Protection configuration */
#define FLSLOADER_PF2_PROT         (NO_PROTECTION)


/* Configuration: FlsLoader PFlash3 Protection configuration */
#define FLSLOADER_PF3_PROT        (NO_PROTECTION)


/* Configuration:this device variant does not have Pf4Sectors so FLSLOADER_PF4_PROT 
generated with default value NO_PROTECTION   */
#define FLSLOADER_PF4_PROT         (NO_PROTECTION)


/* Configuration:this device variant does not have Pf5Sectors so FLSLOADER_PF5_PROT 
generated with default value NO_PROTECTION   */
#define FLSLOADER_PF5_PROT         (NO_PROTECTION)


/*
Configuration: FlsLoader DFLASH0 Read/Write Protection configuration */
#define FLSLOADER_DF0_PROT        (NO_PROTECTION)

/*******************************************************************************
**                      Extern function declarations                          **
*******************************************************************************/

#if ((FLSLOADER_PF0_PROT == READ_PROTECTION )|| \
  (FLSLOADER_PF0_PROT == WRITE_PROTECTION)|| \
  (FLSLOADER_PF0_PROT == OTP_PROTECTION )|| \
  (FLSLOADER_PF0_PROT == WOP_PROTECTION)\
||(FLSLOADER_PF1_PROT == READ_PROTECTION )||\
  (FLSLOADER_PF1_PROT == WRITE_PROTECTION)\
||(FLSLOADER_PF1_PROT == OTP_PROTECTION )|| \
  (FLSLOADER_PF1_PROT == WOP_PROTECTION)\
||(FLSLOADER_PF2_PROT == READ_PROTECTION )|| \
  (FLSLOADER_PF2_PROT == WRITE_PROTECTION)\
||(FLSLOADER_PF2_PROT == OTP_PROTECTION )|| \
  (FLSLOADER_PF2_PROT == WOP_PROTECTION)\
||(FLSLOADER_PF3_PROT == READ_PROTECTION )|| \
  (FLSLOADER_PF3_PROT == WRITE_PROTECTION)\
||(FLSLOADER_PF3_PROT == OTP_PROTECTION )|| \
  (FLSLOADER_PF3_PROT == WOP_PROTECTION)\
)
/* PFLASH0 UCB 4 double word password*/

#define FLSLOADER_PF0_PW00   ((uint32)0x00000000U)

#define FLSLOADER_PF0_PW01   ((uint32)0x00000000U)

#define FLSLOADER_PF0_PW10   ((uint32)0x00000000U)

#define FLSLOADER_PF0_PW11   ((uint32)0x00000000U)

#define FLSLOADER_PF0_PW20   ((uint32)0x00000000U)

#define FLSLOADER_PF0_PW21   ((uint32)0x00000000U)

#define FLSLOADER_PF0_PW30   ((uint32)0x00000000U)

#define FLSLOADER_PF0_PW31   ((uint32)0x00000000U)

/* PFLASH0 protection configuration for Sector x*/

#define FLSLOADER_PROCONP00       ((uint32)0x00000000U)

#define FLSLOADER_PROCONP01       ((uint32)0x00000000U)

#define FLSLOADER_PROCONP02       ((uint32)0x00000000U)

#define FLSLOADER_PROCONP03       ((uint32)0x00000000U)

#define FLSLOADER_PROCONP04       ((uint32)0x00000000U)

#define FLSLOADER_PROCONP05       ((uint32)0x00000000U)


#define FLSLOADER_PROCONOTP00     ((uint32)0x00000000U)

#define FLSLOADER_PROCONOTP01     ((uint32)0x00000000U)

#define FLSLOADER_PROCONOTP02     ((uint32)0x00000000U)

#define FLSLOADER_PROCONOTP03     ((uint32)0x00000000U)

#define FLSLOADER_PROCONOTP04     ((uint32)0x00000000U)

#define FLSLOADER_PROCONOTP05     ((uint32)0x00000000U)


#define FLSLOADER_PROCONWOP00     ((uint32)0x00000000U)

#define FLSLOADER_PROCONWOP01     ((uint32)0x00000000U)

#define FLSLOADER_PROCONWOP02     ((uint32)0x00000000U)

#define FLSLOADER_PROCONWOP03     ((uint32)0x00000000U)

#define FLSLOADER_PROCONWOP04     ((uint32)0x00000000U)

#define FLSLOADER_PROCONWOP05     ((uint32)0x00000000U)

/* PFLASH1 protection configuration for Sector x*/

#define FLSLOADER_PROCONP10       ((uint32)0x00000000U)

#define FLSLOADER_PROCONP11       ((uint32)0x00000000U)

#define FLSLOADER_PROCONP12       ((uint32)0x00000000U)

#define FLSLOADER_PROCONP13       ((uint32)0x00000000U)

#define FLSLOADER_PROCONP14       ((uint32)0x00000000U)

#define FLSLOADER_PROCONP15       ((uint32)0x00000000U)


#define FLSLOADER_PROCONOTP10     ((uint32)0x00000000U)

#define FLSLOADER_PROCONOTP11     ((uint32)0x00000000U)

#define FLSLOADER_PROCONOTP12     ((uint32)0x00000000U)

#define FLSLOADER_PROCONOTP13     ((uint32)0x00000000U)

#define FLSLOADER_PROCONOTP14     ((uint32)0x00000000U)

#define FLSLOADER_PROCONOTP15     ((uint32)0x00000000U)


#define FLSLOADER_PROCONWOP10     ((uint32)0x00000000U)

#define FLSLOADER_PROCONWOP11     ((uint32)0x00000000U)

#define FLSLOADER_PROCONWOP12     ((uint32)0x00000000U)

#define FLSLOADER_PROCONWOP13     ((uint32)0x00000000U)

#define FLSLOADER_PROCONWOP14     ((uint32)0x00000000U)

#define FLSLOADER_PROCONWOP15     ((uint32)0x00000000U)

/* PFLASH2 protection configuration for Sector x*/

#define FLSLOADER_PROCONP20       ((uint32)0x00000000U)

#define FLSLOADER_PROCONP21       ((uint32)0x00000000U)

#define FLSLOADER_PROCONP22       ((uint32)0x00000000U)

#define FLSLOADER_PROCONP23       ((uint32)0x00000000U)

#define FLSLOADER_PROCONP24       ((uint32)0x00000000U)

#define FLSLOADER_PROCONP25       ((uint32)0x00000000U)


#define FLSLOADER_PROCONOTP20     ((uint32)0x00000000U)

#define FLSLOADER_PROCONOTP21     ((uint32)0x00000000U)

#define FLSLOADER_PROCONOTP22     ((uint32)0x00000000U)

#define FLSLOADER_PROCONOTP23     ((uint32)0x00000000U)

#define FLSLOADER_PROCONOTP24     ((uint32)0x00000000U)

#define FLSLOADER_PROCONOTP25     ((uint32)0x00000000U)


#define FLSLOADER_PROCONWOP20     ((uint32)0x00000000U)

#define FLSLOADER_PROCONWOP21     ((uint32)0x00000000U)

#define FLSLOADER_PROCONWOP22     ((uint32)0x00000000U)

#define FLSLOADER_PROCONWOP23     ((uint32)0x00000000U)

#define FLSLOADER_PROCONWOP24     ((uint32)0x00000000U)

#define FLSLOADER_PROCONWOP25     ((uint32)0x00000000U)

/* PFLASH3 protection configuration for Sector x*/

#define FLSLOADER_PROCONP30       ((uint32)0x00000000U)

#define FLSLOADER_PROCONP31       ((uint32)0x00000000U)

#define FLSLOADER_PROCONP32         ((uint32)0x00000000U)

#define FLSLOADER_PROCONP33         ((uint32)0x00000000U)

#define FLSLOADER_PROCONP34         ((uint32)0x00000000U)

#define FLSLOADER_PROCONP35         ((uint32)0x00000000U)


#define FLSLOADER_PROCONOTP30       ((uint32)0x00000000U)

#define FLSLOADER_PROCONOTP31       ((uint32)0x00000000U)

#define FLSLOADER_PROCONOTP32       ((uint32)0x00000000U)

#define FLSLOADER_PROCONOTP33       ((uint32)0x00000000U)

#define FLSLOADER_PROCONOTP34       ((uint32)0x00000000U)

#define FLSLOADER_PROCONOTP35       ((uint32)0x00000000U)


#define FLSLOADER_PROCONWOP30       ((uint32)0x00000000U)

#define FLSLOADER_PROCONWOP31       ((uint32)0x00000000U)

#define FLSLOADER_PROCONWOP32       ((uint32)0x00000000U)

#define FLSLOADER_PROCONWOP33       ((uint32)0x00000000U)

#define FLSLOADER_PROCONWOP34       ((uint32)0x00000000U)

#define FLSLOADER_PROCONWOP35       ((uint32)0x00000000U)

/* PFLASH4 protection configuration for Sector x*/

#define FLSLOADER_PROCONP40       ((uint32)0x00000000U)

#define FLSLOADER_PROCONP41       ((uint32)0x00000000U)

#define FLSLOADER_PROCONP42       ((uint32)0x00000000U)

#define FLSLOADER_PROCONP43       ((uint32)0x00000000U)

#define FLSLOADER_PROCONP44       ((uint32)0x00000000U)

#define FLSLOADER_PROCONP45       ((uint32)0x00000000U)


#define FLSLOADER_PROCONOTP40       ((uint32)0x00000000U)

#define FLSLOADER_PROCONOTP41       ((uint32)0x00000000U)

#define FLSLOADER_PROCONOTP42       ((uint32)0x00000000U)

#define FLSLOADER_PROCONOTP43       ((uint32)0x00000000U)

#define FLSLOADER_PROCONOTP44       ((uint32)0x00000000U)

#define FLSLOADER_PROCONOTP45       ((uint32)0x00000000U)


#define FLSLOADER_PROCONWOP40       ((uint32)0x00000000U)

#define FLSLOADER_PROCONWOP41       ((uint32)0x00000000U)

#define FLSLOADER_PROCONWOP42       ((uint32)0x00000000U)

#define FLSLOADER_PROCONWOP43       ((uint32)0x00000000U)

#define FLSLOADER_PROCONWOP44       ((uint32)0x00000000U)

#define FLSLOADER_PROCONWOP45       ((uint32)0x00000000U)

/* PFLASH5 protection configuration for Sector x*/

#define FLSLOADER_PROCONP50       ((uint32)0x00000000U)

#define FLSLOADER_PROCONP51       ((uint32)0x00000000U)

#define FLSLOADER_PROCONOTP50       ((uint32)0x00000000U)

#define FLSLOADER_PROCONOTP51       ((uint32)0x00000000U)

#define FLSLOADER_PROCONWOP50       ((uint32)0x00000000U)

#define FLSLOADER_PROCONWOP51       ((uint32)0x00000000U)

#endif

#if (FLSLOADER_DF0_PROT == READ_PROTECTION)
#define FLSLOADER_PROCOND0 ((uint32)(0x80000001U))
#elif (FLSLOADER_DF0_PROT == WRITE_PROTECTION)
#define FLSLOADER_PROCOND0 ((uint32)(0x00000001U))
#else
#define FLSLOADER_PROCOND0 ((uint32)(0x00000000U))
#endif

#if (FLSLOADER_DF0_PROT != NO_PROTECTION)
/* DFLASH UCB 4 double word password*/

#define FLSLOADER_DF0_PW00    ((uint32)0x00000000U)


#define FLSLOADER_DF0_PW01    ((uint32)0x00000000U)


#define FLSLOADER_DF0_PW10    ((uint32)0x00000000U)


#define FLSLOADER_DF0_PW11    ((uint32)0x00000000U)


#define FLSLOADER_DF0_PW20    ((uint32)0x00000000U)


#define FLSLOADER_DF0_PW21    ((uint32)0x00000000U)


#define FLSLOADER_DF0_PW30    ((uint32)0x00000000U)


#define FLSLOADER_DF0_PW31    ((uint32)0x00000000U)
#else
/* Passords in the form of Bytes used in array to fill in UCB_PFLASH  */
#define FLSLOADER_DF0_PW00    ((uint32)(0U))
#define FLSLOADER_DF0_PW01    ((uint32)(0U))
#define FLSLOADER_DF0_PW10    ((uint32)(0U))
#define FLSLOADER_DF0_PW11    ((uint32)(0U))
#define FLSLOADER_DF0_PW20    ((uint32)(0U))
#define FLSLOADER_DF0_PW21    ((uint32)(0U))
#define FLSLOADER_DF0_PW30    ((uint32)(0U))
#define FLSLOADER_DF0_PW31    ((uint32)(0U))
#endif

#define FLSLOADER_DF0_USERMODE    ((uint32)(0U))


#endif /*FLSLOADER_CFG_H*/
