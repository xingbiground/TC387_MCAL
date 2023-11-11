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
**  FILENAME     : FlsLoader_Platform.c                                       **
**                                                                            **
**  VERSION      : 23.0.0                                                     **
**                                                                            **
**  DATE         : 2021-02-26                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Flsloader driver platform specific source file             **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* [cover parentID={28D418EE-E771-43ce-8898-3C66276F7DDA}] [/cover]*/
#include "FlsLoader_Local.h"
#include "FlsLoader.h"
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
#define FLSLOADER_PROCON_CHECK          ((uint32)(0xFFFFFFFFU))
#define FLSLOADER_ONE_U8                (1U)
#if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
#define FLSLOADER_EEPROM_OFFSETEND      (FLSLOADER_DFLASH0_BANK_SIZE - 1U)
#define FLSLOADER_DF_EEPROM_SEGMENT     (0xAF0U)
#define FLSLOADER_DF_UCB_SEGMENT        (0xAF4U)
#define FLSLOADER_EEPROM_SECTOR_SIZE    (0xFFFU)    /* 4K Sector size */
#define FLSLOADER_UCB_SECTOR_SIZE_1     (0x1FFU)    /* 512 Bytes */
#define FLSLOADER_UCB_SECTOR_SIZE       (FLSLOADER_UCB_SECTOR_SIZE_1+1U)
#define FLSLOADER_DFLASH_SECTOR_SIZE    (FLSLOADER_EEPROM_SECTOR_SIZE+1U)
#define FLSLOADER_DFLASH0_ADDRESS_MASK  ((FlsLoader_AddressType)(0x000FFFFFU))
#define FLSLOADER_UCB_ADDRESS_MASK      ((FlsLoader_AddressType)(0x00005FFFU))
#define FLSLOADER_MOD_8                 (0x7U)
#define FLSLOADER_UNALIGNED_SECTOR_ADDR ((uint8)1U)
#define FLSLOADER_LENGTH_OUTSIDE_RANGE  ((uint8)2U)
#endif

#if (FLSLOADER_LOCK_UNLOCK_API == STD_ON)

/*PFLASH or DFLSAH0 protection is Enabled*/
#define FLASH_PROTECTION_TRUE       (((FLSLOADER_DF0_PROT != NO_PROTECTION)||\
                                      (FLSLOADER_PF0_PROT != NO_PROTECTION)||\
                                      (FLSLOADER_PF1_PROT != NO_PROTECTION)||\
                                      (FLSLOADER_PF2_PROT != NO_PROTECTION)||\
                                      (FLSLOADER_PF3_PROT != NO_PROTECTION)||\
                                      (FLSLOADER_PF4_PROT != NO_PROTECTION)||\
                                      (FLSLOADER_PF5_PROT != NO_PROTECTION))?\
                                       TRUE : FALSE)

/*Read or Write protection is Enabled for atleast one PFLASH bank*/
#define FLASH_READ_WRITE_PTOTECTION_TRUE \
                                  (((FLSLOADER_PF0_PROT == WRITE_PROTECTION)||\
                                    (FLSLOADER_PF1_PROT == WRITE_PROTECTION)||\
                                    (FLSLOADER_PF2_PROT == WRITE_PROTECTION)||\
                                    (FLSLOADER_PF3_PROT == WRITE_PROTECTION)||\
                                    (FLSLOADER_PF4_PROT == WRITE_PROTECTION)||\
                                    (FLSLOADER_PF5_PROT == WRITE_PROTECTION)||\
                                    (FLSLOADER_PF0_PROT == READ_PROTECTION)||\
                                    (FLSLOADER_PF1_PROT == READ_PROTECTION)||\
                                    (FLSLOADER_PF2_PROT == READ_PROTECTION)||\
                                    (FLSLOADER_PF3_PROT == READ_PROTECTION)||\
                                    (FLSLOADER_PF4_PROT == READ_PROTECTION)||\
                                    (FLSLOADER_PF5_PROT == READ_PROTECTION))?\
                                     TRUE : FALSE)

/*OTP or WOP protection is Enabled for atleast one PFLASH bank*/
#define FLASH_OTP_OWP_PROTECTION_TRUE \
                                  (((FLSLOADER_PF0_PROT == OTP_PROTECTION)||\
                                    (FLSLOADER_PF0_PROT == WOP_PROTECTION)||\
                                    (FLSLOADER_PF1_PROT == OTP_PROTECTION)||\
                                    (FLSLOADER_PF1_PROT == WOP_PROTECTION)||\
                                    (FLSLOADER_PF2_PROT == OTP_PROTECTION)||\
                                    (FLSLOADER_PF2_PROT == WOP_PROTECTION)||\
                                    (FLSLOADER_PF3_PROT == OTP_PROTECTION)||\
                                    (FLSLOADER_PF3_PROT == WOP_PROTECTION)||\
                                    (FLSLOADER_PF4_PROT == OTP_PROTECTION)||\
                                    (FLSLOADER_PF4_PROT == WOP_PROTECTION)||\
                                    (FLSLOADER_PF5_PROT == OTP_PROTECTION)||\
                                    (FLSLOADER_PF5_PROT == WOP_PROTECTION))?\
                                     TRUE : FALSE)

/*Flash protection is configured*/
#if (FLASH_PROTECTION_TRUE == TRUE)

#define FLSLOADER_NUM_UCB_SECTORS       (1U)
/* UCB size is 512 bytes, one page is 8Bytes, Total page = 64. (512/8)*/
#define FLSLOADER_NUM_UCB_PAGES         (64U)
#define FLSLOADER_PAGE_SIZE             (8U)
#endif

#if (FLASH_OTP_OWP_PROTECTION_TRUE == TRUE)
/*Macro used only if OTP/WOP protection enabled*/
#define FLSLOADER_NUM_8                 (0x8U)
#endif
#endif /*End for FLSLOADER_LOCK_UNLOCK_API check*/

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/
/* [cover parentID={C829DF02-56F2-4e35-8652-24A8516EF825}]
[/cover] */
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
[/cover] */
/* [cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond
   32 chars and this macro is used only inside the FLSLOADER module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond
   32 chars and this macro is used only inside the FLSLOADER module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond
   32 chars and this macro is used only inside the FLSLOADER module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond
   32 chars and this macro is used only inside the FLSLOADER module*/
#define FLSLOADER_START_SEC_CONST_QM_LOCAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "FlsLoader_MemMap.h"


#if (FLSLOADER_LOCK_UNLOCK_API == STD_ON)
/* UCB_PFLASH Content */
#if ((FLSLOADER_PF0_PROT == WRITE_PROTECTION)||\
     (FLSLOADER_PF1_PROT == WRITE_PROTECTION)||\
     (FLSLOADER_PF2_PROT == WRITE_PROTECTION)||\
     (FLSLOADER_PF3_PROT == WRITE_PROTECTION)||\
     (FLSLOADER_PF4_PROT == WRITE_PROTECTION)||\
     (FLSLOADER_PF5_PROT == WRITE_PROTECTION)||\
     (FLSLOADER_PF0_PROT == READ_PROTECTION) ||\
     (FLSLOADER_PF1_PROT == READ_PROTECTION) ||\
     (FLSLOADER_PF2_PROT == READ_PROTECTION) ||\
     (FLSLOADER_PF3_PROT == READ_PROTECTION) ||\
     (FLSLOADER_PF4_PROT == READ_PROTECTION) ||\
     (FLSLOADER_PF5_PROT == READ_PROTECTION))
/* MISRA2012_RULE_8_9_JUSTIFICATION: FlsLoader_UcbPFlashPage0 is declared
 * static to the file */
static const uint32 FlsLoader_UcbPFlashPage0[FLSLOADER_UCB_PFLASH_ORGINAL_SIZE]=
{
  FLSLOADER_PROCONP00, FLSLOADER_PROCONP01,   /*0x000, 0x004 */
  FLSLOADER_PROCONP02, FLSLOADER_PROCONP03,   /*0x008, 0x00C */
  FLSLOADER_PROCONP04, FLSLOADER_PROCONP05,   /*0x010, 0x014 */
  0x00000000, 0x00000000,                     /*0x018, 0x01C */
  FLSLOADER_PROCONP10, FLSLOADER_PROCONP11,   /*0x020, 0x024 */
  FLSLOADER_PROCONP12, FLSLOADER_PROCONP13,   /*0x028, 0x02C */
  FLSLOADER_PROCONP14, FLSLOADER_PROCONP15,   /*0x030, 0x034 */
  0x00000000, 0x00000000,                     /*0x038, 0x03C */
  FLSLOADER_PROCONP20, FLSLOADER_PROCONP21,   /*0x040, 0x044 */
  FLSLOADER_PROCONP22, FLSLOADER_PROCONP23,   /*0x048, 0x04C */
  FLSLOADER_PROCONP24, FLSLOADER_PROCONP25,   /*0x050, 0x054 */
  0x00000000, 0x00000000,                     /*0x058, 0x05C */
  FLSLOADER_PROCONP30, FLSLOADER_PROCONP31,   /*0x060, 0x064 */
  FLSLOADER_PROCONP32, FLSLOADER_PROCONP33,   /*0x068, 0x06C */
  FLSLOADER_PROCONP34, FLSLOADER_PROCONP35,   /*0x070, 0x074 */
  0x00000000, 0x00000000,                     /*0x078, 0x07C */
  FLSLOADER_PROCONP40, FLSLOADER_PROCONP41,   /*0x080, 0x084 */
  FLSLOADER_PROCONP42, FLSLOADER_PROCONP43,   /*0x088, 0x08C */
  FLSLOADER_PROCONP44, FLSLOADER_PROCONP45,   /*0x090, 0x094 */
  0x00000000, 0x00000000,                     /*0x098, 0x09C */
  FLSLOADER_PROCONP50, FLSLOADER_PROCONP51,   /*0x0A0, 0x0A4 */
  0x00000000, 0x00000000,                     /*0x0A8, 0x0AC */
  0x00000000, 0x00000000,                     /*0x0B0, 0x0B4 */
  0x00000000, 0x00000000,                     /*0x0B8, 0x0BC */
  0x00000000, 0x00000000,                     /*0x0C0, 0x0C4 */
  0x00000000, 0x00000000,                     /*0x0C8, 0x0CC */
  0x00000000, 0x00000000,                     /*0x0D0, 0x0D4 */
  0x00000000, 0x00000000,                     /*0x0D8, 0x0DC */
  0x00000000, 0x00000000,                     /*0x0E0, 0x0E4 */
  0x00000000, 0x00000000,                     /*0x0E8, 0x0EC */
  0x00000000, 0x00000000,                     /*0x0F0, 0x0F4 */
  0x00000000, 0x00000000,                     /*0x0F8, 0x0FC */
  FLSLOADER_PF0_PW00, FLSLOADER_PF0_PW01,     /*0x100, 0x104 */
  FLSLOADER_PF0_PW10, FLSLOADER_PF0_PW11,     /*0x108, 0x10C */
  FLSLOADER_PF0_PW20, FLSLOADER_PF0_PW21,     /*0x110, 0x114 */
  FLSLOADER_PF0_PW30, FLSLOADER_PF0_PW31,     /*0x118, 0x11C */
  0x00000000, 0x00000000,                     /*0x120, 0x124 */
  0x00000000, 0x00000000,                     /*0x128, 0x12C */
  0x00000000, 0x00000000,                     /*0x130, 0x134 */
  0x00000000, 0x00000000,                     /*0x138, 0x13C */
  0x00000000, 0x00000000,                     /*0x140, 0x144 */
  0x00000000, 0x00000000,                     /*0x148, 0x14C */
  0x00000000, 0x00000000,                     /*0x150, 0x154 */
  0x00000000, 0x00000000,                     /*0x158, 0x15C */
  0x00000000, 0x00000000,                     /*0x160, 0x164 */
  0x00000000, 0x00000000,                     /*0x168, 0x16C */
  0x00000000, 0x00000000,                     /*0x170, 0x174 */
  0x00000000, 0x00000000,                     /*0x178, 0x17C */
  0x00000000, 0x00000000,                     /*0x180, 0x184 */
  0x00000000, 0x00000000,                     /*0x188, 0x18C */
  0x00000000, 0x00000000,                     /*0x190, 0x194 */
  0x00000000, 0x00000000,                     /*0x198, 0x19C */
  0x00000000, 0x00000000,                     /*0x1A0, 0x1A4 */
  0x00000000, 0x00000000,                     /*0x1A8, 0x1AC */
  0x00000000, 0x00000000,                     /*0x1B0, 0x1B4 */
  0x00000000, 0x00000000,                     /*0x1B8, 0x1BC */
  0x00000000, 0x00000000,                     /*0x1C0, 0x1C4 */
  0x00000000, 0x00000000,                     /*0x1C8, 0x1CC */
  0x00000000, 0x00000000,                     /*0x1D0, 0x1D4 */
  0x00000000, 0x00000000,                     /*0x1D8, 0x1DC */
  0x00000000, 0x00000000,                     /*0x1E0, 0x1E4 */
  0x00000000, 0x00000000,                     /*0x1E8, 0x1EC */
  FLSLOADER_CONFIRMATION_CODE, 0x00000000,     /*0x1F0, 0x1F4 */
  0x00000000, 0x00000000                     /*0x1F8, 0x1FC */
};
#endif
/*#if ((FLSLOADER_PF0_PROT == WRITE_PROTECTION)||...*/


/* UCB_DPFLASH Content */
#if (FLSLOADER_DF0_PROT != NO_PROTECTION)
/* MISRA2012_RULE_8_9_JUSTIFICATION: FlsLoader_UcbDFlashPage0 is declared
 * static to the file */
static const uint32 FlsLoader_UcbDFlashPage0[FLSLOADER_UCB_DFLASH_ORGINAL_SIZE]=
{
  FLSLOADER_DF0_USERMODE, FLSLOADER_PROCOND0, /* 0x000, 0x004 */
  0x00000000, 0x00000000,                     /* 0x008, 0x00C */
  0x00000000, 0x00000000,                     /* 0x010, 0x014 */
  0x00000000, 0x00000000,                     /* 0x018, 0x01C */
  0x00000000, 0x00000000,                     /* 0x020, 0x024 */
  0x00000000, 0x00000000,                     /* 0x028, 0x02C */
  0x00000000, 0x00000000,                     /* 0x030, 0x034 */
  0x00000000, 0x00000000,                     /* 0x038, 0x03C */
  0x00000000, 0x00000000,                     /* 0x040, 0x044 */
  0x00000000, 0x00000000,                     /* 0x048, 0x04C */
  0x00000000, 0x00000000,                     /* 0x050, 0x054 */
  0x00000000, 0x00000000,                     /* 0x058, 0x05C */
  0x00000000, 0x00000000,                     /* 0x060, 0x064 */
  0x00000000, 0x00000000,                     /* 0x068, 0x06C */
  0x00000000, 0x00000000,                     /* 0x070, 0x074 */
  0x00000000, 0x00000000,                     /* 0x078, 0x07C */
  0x00000000, 0x00000000,                     /* 0x080, 0x084 */
  0x00000000, 0x00000000,                     /* 0x088, 0x08C */
  0x00000000, 0x00000000,                     /* 0x090, 0x094 */
  0x00000000, 0x00000000,                     /* 0x098, 0x09C */
  0x00000000, 0x00000000,                     /* 0x0A0, 0x0A4 */
  0x00000000, 0x00000000,                     /* 0x0A8, 0x0AC */
  0x00000000, 0x00000000,                     /* 0x0B0, 0x0B4 */
  0x00000000, 0x00000000,                     /* 0x0B8, 0x0BC */
  0x00000000, 0x00000000,                     /* 0x0C0, 0x0C4 */
  0x00000000, 0x00000000,                     /* 0x0C8, 0x0CC */
  0x00000000, 0x00000000,                     /* 0x0D0, 0x0D4 */
  0x00000000, 0x00000000,                     /* 0x0D8, 0x0DC */
  0x00000000, 0x00000000,                     /* 0x0E0, 0x0E4 */
  0x00000000, 0x00000000,                     /* 0x0E8, 0x0EC */
  0x00000000, 0x00000000,                     /* 0x0F0, 0x0F4 */
  0x00000000, 0x00000000,                     /* 0x0F8, 0x0FC */
  FLSLOADER_DF0_PW00, FLSLOADER_DF0_PW01,     /* 0x100, 0x104 */
  FLSLOADER_DF0_PW10, FLSLOADER_DF0_PW11,     /* 0x108, 0x10C */
  FLSLOADER_DF0_PW20, FLSLOADER_DF0_PW21,     /* 0x110, 0x114 */
  FLSLOADER_DF0_PW30, FLSLOADER_DF0_PW31,     /* 0x118, 0x11C */
  0x00000000, 0x00000000,                     /* 0x120, 0x124 */
  0x00000000, 0x00000000,                     /* 0x128, 0x12C */
  0x00000000, 0x00000000,                     /* 0x130, 0x134 */
  0x00000000, 0x00000000,                     /* 0x138, 0x13C */
  0x00000000, 0x00000000,                     /* 0x140, 0x144 */
  0x00000000, 0x00000000,                     /* 0x148, 0x14C */
  0x00000000, 0x00000000,                     /* 0x150, 0x154 */
  0x00000000, 0x00000000,                     /* 0x158, 0x15C */
  0x00000000, 0x00000000,                     /* 0x160, 0x164 */
  0x00000000, 0x00000000,                     /* 0x168, 0x16C */
  0x00000000, 0x00000000,                     /* 0x170, 0x174 */
  0x00000000, 0x00000000,                     /* 0x178, 0x17C */
  0x00000000, 0x00000000,                     /* 0x180, 0x184 */
  0x00000000, 0x00000000,                     /* 0x188, 0x18C */
  0x00000000, 0x00000000,                     /* 0x190, 0x194 */
  0x00000000, 0x00000000,                     /* 0x198, 0x19C */
  0x00000000, 0x00000000,                     /* 0x1A0, 0x1A4 */
  0x00000000, 0x00000000,                     /* 0x1A8, 0x1AC */
  0x00000000, 0x00000000,                     /* 0x1B0, 0x1B4 */
  0x00000000, 0x00000000,                     /* 0x1B8, 0x1BC */
  0x00000000, 0x00000000,                     /* 0x1C0, 0x1C4 */
  0x00000000, 0x00000000,                     /* 0x1C8, 0x1CC */
  0x00000000, 0x00000000,                     /* 0x1D0, 0x1D4 */
  0x00000000, 0x00000000,                     /* 0x1D8, 0x1DC */
  0x00000000, 0x00000000,                     /* 0x1E0, 0x1E4 */
  0x00000000, 0x00000000,                     /* 0x1E8, 0x1EC */
  FLSLOADER_CONFIRMATION_CODE, 0x00000000,/* 0x1F0, 0x1F4 */
  0x00000000, 0x00000000,                     /* 0x1F8, 0x1FC */
};
#endif
/*#if (FLSLOADER_PF0_PROT != NO_PROTECTION)*/

/* UCB OTP FLASH content */
#if  ((FLSLOADER_PF0_PROT == OTP_PROTECTION)||\
      (FLSLOADER_PF0_PROT == WOP_PROTECTION)||\
      (FLSLOADER_PF1_PROT == OTP_PROTECTION)||\
      (FLSLOADER_PF1_PROT == WOP_PROTECTION)||\
      (FLSLOADER_PF2_PROT == OTP_PROTECTION)||\
      (FLSLOADER_PF2_PROT == WOP_PROTECTION)||\
      (FLSLOADER_PF3_PROT == OTP_PROTECTION)||\
      (FLSLOADER_PF3_PROT == WOP_PROTECTION)||\
      (FLSLOADER_PF4_PROT == OTP_PROTECTION)||\
      (FLSLOADER_PF4_PROT == WOP_PROTECTION)||\
      (FLSLOADER_PF5_PROT == OTP_PROTECTION)||\
      (FLSLOADER_PF5_PROT == WOP_PROTECTION))
/* MISRA2012_RULE_8_9_JUSTIFICATION: FlsLoader_UcbDFlashPage0 is declared
 * static to the file */
static const uint32 FlsLoader_UcbOTPFlashPage0[FLSLOADER_UCB_OTP0_SIZE] = {
  FLSLOADER_PROCONOTP00, FLSLOADER_PROCONOTP01,   /* 0x000, 0x004 */
  FLSLOADER_PROCONOTP02, FLSLOADER_PROCONOTP03,   /* 0x008, 0x00C */
  FLSLOADER_PROCONOTP04, FLSLOADER_PROCONOTP05,   /* 0x010, 0x014 */
  0x00000000, 0x00000000,                         /* 0x018, 0x01C */
  FLSLOADER_PROCONOTP10, FLSLOADER_PROCONOTP11,   /* 0x020, 0x024 */
  FLSLOADER_PROCONOTP12, FLSLOADER_PROCONOTP13,   /* 0x028, 0x02C */
  FLSLOADER_PROCONOTP14, FLSLOADER_PROCONOTP15,   /* 0x030, 0x034 */
  0x00000000, 0x00000000,                         /* 0x038, 0x03C */
  FLSLOADER_PROCONOTP20, FLSLOADER_PROCONOTP21,   /* 0x040, 0x044 */
  FLSLOADER_PROCONOTP22, FLSLOADER_PROCONOTP23,   /* 0x048, 0x04C */
  FLSLOADER_PROCONOTP24, FLSLOADER_PROCONOTP25,   /* 0x050, 0x054 */
  0x00000000, 0x00000000,                         /* 0x058, 0x05C */
  FLSLOADER_PROCONOTP30, FLSLOADER_PROCONOTP31,   /* 0x060, 0x064 */
  FLSLOADER_PROCONOTP32, FLSLOADER_PROCONOTP33,   /* 0x068, 0x06C */
  FLSLOADER_PROCONOTP34, FLSLOADER_PROCONOTP35,   /* 0x070, 0x074 */
  0x00000000, 0x00000000,                         /* 0x078, 0x07C */
  FLSLOADER_PROCONOTP40, FLSLOADER_PROCONOTP41,   /* 0x080, 0x084 */
  FLSLOADER_PROCONOTP42, FLSLOADER_PROCONOTP43,   /* 0x088, 0x08C */
  FLSLOADER_PROCONOTP44, FLSLOADER_PROCONOTP45,   /* 0x090, 0x094 */
  0x00000000, 0x00000000,                         /* 0x098, 0x09C */
  FLSLOADER_PROCONOTP50, FLSLOADER_PROCONOTP51,   /* 0x0A0, 0x0A4 */
  0x00000000, 0x00000000,                         /* 0x0A8, 0x0AC */
  0x00000000, 0x00000000,                         /* 0x0B0, 0x0B4 */
  0x00000000, 0x00000000,                         /* 0x0B8, 0x0BC */
  0x00000000, 0x00000000,                         /* 0x0C0, 0x0C4 */
  0x00000000, 0x00000000,                         /* 0x0C8, 0x0CC */
  0x00000000, 0x00000000,                         /* 0x0D0, 0x0D4 */
  0x00000000, 0x00000000,                         /* 0x0D8, 0x0DC */
  0x00000000, 0x00000000,                         /* 0x0E0, 0x0E4 */
  0x00000000, 0x00000000,                         /* 0x0E8, 0x0EC */
  0x00000000, 0x00000000,                         /* 0x0F0, 0x0F4 */
  0x00000000, 0x00000000,                         /* 0x0F8, 0x0FC */
  FLSLOADER_PROCONWOP00, FLSLOADER_PROCONWOP01,   /* 0x100, 0x104 */
  FLSLOADER_PROCONWOP02, FLSLOADER_PROCONWOP03,   /* 0x108, 0x10C */
  FLSLOADER_PROCONWOP04, FLSLOADER_PROCONWOP05,   /* 0x110, 0x114 */
  0x00000000, 0x00000000,                         /* 0x118, 0x11C */
  FLSLOADER_PROCONWOP10, FLSLOADER_PROCONWOP11,   /* 0x120, 0x124 */
  FLSLOADER_PROCONWOP12, FLSLOADER_PROCONWOP13,   /* 0x128, 0x12C */
  FLSLOADER_PROCONWOP14, FLSLOADER_PROCONWOP15,   /* 0x130, 0x134 */
  0x00000000, 0x00000000,                         /* 0x138, 0x13C */
  FLSLOADER_PROCONWOP20, FLSLOADER_PROCONWOP21,   /* 0x140, 0x144 */
  FLSLOADER_PROCONWOP22, FLSLOADER_PROCONWOP23,   /* 0x148, 0x14C */
  FLSLOADER_PROCONWOP24, FLSLOADER_PROCONWOP25,   /* 0x150, 0x154 */
  0x00000000, 0x00000000,                         /* 0x158, 0x15C */
  FLSLOADER_PROCONWOP30, FLSLOADER_PROCONWOP31,   /* 0x160, 0x164 */
  FLSLOADER_PROCONWOP32, FLSLOADER_PROCONWOP33,   /* 0x168, 0x16C */
  FLSLOADER_PROCONWOP34, FLSLOADER_PROCONWOP35,   /* 0x170, 0x174 */
  0x00000000, 0x00000000,                         /* 0x178, 0x17C */
  FLSLOADER_PROCONWOP40, FLSLOADER_PROCONWOP41,   /* 0x180, 0x184 */
  FLSLOADER_PROCONWOP42, FLSLOADER_PROCONWOP43,   /* 0x188, 0x18C */
  FLSLOADER_PROCONWOP44, FLSLOADER_PROCONWOP45,   /* 0x190, 0x194 */
  0x00000000, 0x00000000,                         /* 0x198, 0x19C */
  FLSLOADER_PROCONWOP50, FLSLOADER_PROCONWOP51,   /* 0x1A0, 0x1A4 */
  0x00000000, 0x00000000,                         /* 0x1A8, 0x1AC */
  0x00000000, 0x00000000,                         /* 0x1B0, 0x1B4 */
  0x00000000, 0x00000000,                         /* 0x1B8, 0x1BC */
  0x00000000, 0x00000000,                         /* 0x1C0, 0x1C4 */
  0x00000000, 0x00000000,                         /* 0x1C8, 0x1CC */
  0x00000000, 0x00000000,                         /* 0x1D0, 0x1D4 */
  0x00000000, 0x00000000,                         /* 0x1D8, 0x1DC */
  0x00000000, 0x00000000,                         /* 0x1E0, 0x1E4 */
  0x00000000, 0x00000000,                         /* 0x1E8, 0x1EC */
  FLSLOADER_CONFIRMATION_CODE, 0x00000000,        /* 0x1F0, 0x1F4 */
  0x00000000, 0x00000000,                         /* 0x1F8, 0x1FC */
};
#endif  /*  #if ((FLSLOADER_PF0_PROT == OTP_PROTECTION)...*/
#endif /* #if (FLSLOADER_LOCK_UNLOCK_API == STD_ON) */

/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond
   32 chars and this macro is used only inside the FLSLOADER module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond
   32 chars and this macro is used only inside the FLSLOADER module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond
   32 chars and this macro is used only inside the FLSLOADER module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond
   32 chars and this macro is used only inside the FLSLOADER module*/
#define FLSLOADER_STOP_SEC_CONST_QM_LOCAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_PFlashOffset'
 * before #include memap.h - Accepted deviation in AUTOSAR */
#include "FlsLoader_MemMap.h"

/*******************************************************************************
**                    Prototypes Of Local Functions                           **
*******************************************************************************/
/* [cover parentID={C829DF02-56F2-4e35-8652-24A8516EF825}]
[/cover] */
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
[/cover] */
/* [cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
#define FLSLOADER_START_SEC_WRITEERASE_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_PFlashOffset'
 * before #include memap.h - Accepted deviation in AUTOSAR */
#include "FlsLoader_MemMap.h"

#if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)

/*
  Function FlsLoader_lAddressPageCheck
  Input Parameters: TargetAddress
*/
LOCAL_INLINE boolean FlsLoader_lAddressPageCheck(
                                  const FlsLoader_AddressType TargetAddress);
/*
  Function FlsLoader_lDFlashCheck
  Input Parameters: TargetAddress
*/
LOCAL_INLINE boolean FlsLoader_lDFlashCheck(
                                  const FlsLoader_AddressType TargetAddress);
/*
  Function FlsLoader_lDFlashAddressCheck
  Input Parameters: TargetAddress
*/
LOCAL_INLINE boolean FlsLoader_lDFlashAddressCheck(
                                     const FlsLoader_AddressType TargetAddress);
/*
  Function FlsLoader_lDFlashLengthCheck
  Input Parameters: TargetAddress, NumberOfSectors
*/
LOCAL_INLINE boolean FlsLoader_lDFlashLengthCheck(
                                    const FlsLoader_LengthType NumberOfSectors,
                                    const FlsLoader_AddressType TargetAddress);
/*
  Function FlsLoader_lPFlashCheck
  Input Parameters: TargetAddress
*/
LOCAL_INLINE boolean FlsLoader_lPFlashCheck(
                         const FlsLoader_AddressType TargetAddress);
/*
  Function FlsLoader_lPFlashAddressCheck
  Input Parameters: Len, TargetAddress
*/
LOCAL_INLINE uint8 FlsLoader_lPFlashAddressCheck(
                                     const FlsLoader_LengthType Len,
                                     const FlsLoader_AddressType TargetAddress);
/*
  Function FlsLoader_lDFlashPageCheck
  Input Parameters: TargetAddress, Length
*/
LOCAL_INLINE boolean FlsLoader_lDFlashPageCheck(
                                    const FlsLoader_AddressType TargetAddress,
                                    const FlsLoader_LengthType Length);

#endif /*#if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)*/

#if ((FLSLOADER_ENABLE_LOCKCHECK == STD_ON) ||\
     (FLSLOADER_DEV_ERROR_DETECT == STD_ON))
/*
  Function FlsLoader_lSectorNumber
  Input Parameters: Offset, FlashBank
*/
LOCAL_INLINE uint32 FlsLoader_lSectorNumber(const uint32 Offset,
                                                      const uint32 FlashBank);
#endif /*#if ((FLSLOADER_ENABLE_LOCKCHECK == STD_ON) ||\
             (FLSLOADER_DEV_ERROR_DETECT == STD_ON))*/

#if (FLSLOADER_ENABLE_LOCKCHECK == STD_ON)
/*
  Function FlsLoader_lCheckBitStatus
  Input Parameters: StartAddress, First, Last
*/
LOCAL_INLINE uint32 FlsLoader_lCheckBitStatus(\
                                 const uint32* const StartAddress,
                                 const uint32 First, const uint32 Last);

/*
  Function FlsLoader_lPFlashSectorCheck
  Input Parameters: TargetAddress, Length, FlashType
*/
LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lPFlashSectorCheck(
                          const FlsLoader_AddressType TargetAddress,
                          const FlsLoader_LengthType Length,
                          const uint32 FlashType);

/*
  Function FlsLoader_lCheckProtStatus
  Input Parameters: StartAddress, Length, First
*/
LOCAL_INLINE boolean FlsLoader_lCheckProtStatus(
                                    const uint32* const StartAddress,
                                    const uint32 Length, const uint32 First);

/*
  Function FlsLoader_lSectorProtCheck
  Input Parameters: FlashType, SectorNumber, Length
*/
LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lSectorProtCheck(
                                           const uint32 FlashType,
                                           const uint32 SectorNumber,
                                           const FlsLoader_LengthType Length);

#endif /*#if ((FLSLOADER_ENABLE_LOCKCHECK == STD_ON)) */

#define FLSLOADER_STOP_SEC_WRITEERASE_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_PFlashOffset'
 * before #include memap.h - Accepted deviation in AUTOSAR */
#include "FlsLoader_MemMap.h"

#define FLSLOADER_START_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_PFlashOffset'
 * before #include memap.h - Accepted deviation in AUTOSAR */
#include "FlsLoader_MemMap.h"

#if (FLSLOADER_LOCK_UNLOCK_API == STD_ON)

/*Flash protection is configured*/
#if (FLASH_PROTECTION_TRUE == TRUE)
LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lLockCmdCycles(
                        const FlsLoader_AddressType UcbSectorAddress,
                        const FlsLoader_AddressType* const PdataPtr);

LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lLockCmdCyclesWrite(
                         const FlsLoader_AddressType UcbSectorAddress,
                         const FlsLoader_AddressType* const PdataPtr,
                         const uint32 TimeoutTicks);
#endif
#endif

#define FLSLOADER_STOP_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_PFlashOffset'
 * before #include memap.h - Accepted deviation in AUTOSAR */
#include "FlsLoader_MemMap.h"

/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
[/cover] */
/* [cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
#define FLSLOADER_START_SEC_WRITEERASE_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_PFlashOffset'
 * before #include memap.h - Accepted deviation in AUTOSAR */
#include "FlsLoader_MemMap.h"

/*******************************************************************************
** Syntax           : FlsLoader_ReturnType FlsLoader_lProtSeqOperErrorCheck(  **
**                                                                       void)**
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FLSLOADER_E_OK: No error occurred.                      **
**                    FLSLOADER_E_NOT_OK: Operational or sequence error       **
**                    occurred.                                               **
**                    FLSLOADER_E_LOCKED: Protection error occurred.          **
**                                                                            **
** Description      : This function detects if any operational, sequence or   **
**                    protection error occurred after previous                **
**                    execution of write or erase.                            **
*******************************************************************************/
/* [cover parentID={0273E1C0-D8DF-4b79-B8F8-A40AA8D60499}][/cover] */
FlsLoader_ReturnType FlsLoader_lProtSeqOperErrorCheck(void)
{
  FlsLoader_ReturnType  RetError;
  uint32 FsrErrcheck;

  RetError = FLSLOADER_E_OK;
  /* [cover parentID={10BF7FA4-1240-482d-A428-DAF1DB61A484}]
  Operational or sequence error flags set
  [/cover] */
  FsrErrcheck = ((uint32)DMU_HF_ERRSR.U & \
                 ((uint32)FLSLOADER_PROER_SQER_OPER_ERROR));
  if ((FsrErrcheck & FLSLOADER_OPER_ERROR) == FLSLOADER_OPER_ERROR)
  {
    RetError = FLSLOADER_E_NOT_OK;
  }
  /* [cover parentID={10BF7FA4-1240-482d-A428-DAF1DB61A484}]
  Operational or sequence error flags set
  [/cover] */
  else if ((FsrErrcheck & FLSLOADER_SQER_ERROR) == FLSLOADER_SQER_ERROR)
  {
    RetError = FLSLOADER_E_NOT_OK;
  }
  /* [cover parentID={97DF496E-2AF4-4f3b-9A99-A8B19BC7DBA5}]
  Protection error flag set
  [/cover] */
  else if ((FsrErrcheck & FLSLOADER_PROER_ERROR) == FLSLOADER_PROER_ERROR)
  {
    RetError = FLSLOADER_E_LOCKED;
  }
  else
  {
    /* do nothing */
  }
  return RetError;
}

#define FLSLOADER_STOP_SEC_WRITEERASE_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_PFlashOffset'
 * before #include memap.h - Accepted deviation in AUTOSAR */
#include "FlsLoader_MemMap.h"

/* [cover parentID={C829DF02-56F2-4e35-8652-24A8516EF825}]
[/cover] */
/*Memory Map of the FlsLoader Code*/
#define FLSLOADER_START_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_PFlashOffset'
 * before #include memap.h - Accepted deviation in AUTOSAR */
#include "FlsLoader_MemMap.h"

#if (FLSLOADER_LOCK_UNLOCK_API == STD_ON)
/*******************************************************************************
** Syntax           : FlsLoader_ReturnType FlsLoader_lEvalUcbState(\          **
**                                            const uint32 UcbOrigState,\     **
**                                            const uint32 UcbCopyState,\     **
**                                            const uint32 ProtDisStatus)     **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : UcbOrigState: DF/PF ORIG UCB state                      **
**                    UcbCopyState: DF/PF COPY UCB state                      **
**                    ProtDisStatus: DF/PF Flash protection status            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FLSLOADER_E_OK: UCB can be accessed.                    **
**                    FLSLOADER_E_LOCKED: UCB can't be accessed.              **
**                                                                            **
** Description      : This function evaluates access to an UCB is allowed or  **
**                    not based on confirmation states of its original and    **
**                    copy UCBs. If access is allowed it returns E_OK,        **
**                    else E_LOCKED.                                          **
*******************************************************************************/
/* [cover parentID={FEDBEF7F-CF16-4c10-89B5-D82AD47CBAFD}][/cover] */
FlsLoader_ReturnType FlsLoader_lEvalUcbState(const uint32 UcbOrigState,\
                                              const uint32 UcbCopyState,\
                                              const uint32 ProtDisStatus)
{
FlsLoader_ReturnType RetState;

  RetState = FLSLOADER_E_OK;

  /* [cover parentID={B86AB23E-06C2-4ab5-A00A-F5B53D966ADA}][/cover] */
  /*Check if any of the original or copy ucb confirmation states is set
    to CONFIRMED and Flash protection enabled*/
  if((ProtDisStatus == FLSLOADER_FLASH_PROT_ENABLED) \
    && ((UcbOrigState == FLSLOADER_UCB_FLASH_CONFIRMED) \
     || (UcbCopyState == FLSLOADER_UCB_FLASH_CONFIRMED)))
  {
    RetState = FLSLOADER_E_LOCKED;
  }
  /* [cover parentID={CB02CE43-6469-4ce3-9610-2E59181D7F6C}][/cover] */
  /*Check if orig and copy confirmation states are set to ERRORED*/
  else if((UcbOrigState == FLSLOADER_UCB_FLASH_ERRORED) \
    && (UcbCopyState == FLSLOADER_UCB_FLASH_ERRORED))
  {
    RetState = FLSLOADER_E_LOCKED;
  }
  else
  {
    /*Do nothing*/
  }

  return RetState;
}

/*******************************************************************************
** Syntax           : FlsLoader_ReturnType FlsLoader_lLock(\                  **
**                                        FlsLoader_UcbType Ucb)              **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FLSLOADER_E_OK: Protection installed successfully.      **
**                    FLSLOADER_E_NOT_OK: Protection installation failed.     **
**                    Protection, sequence, operation, erase or program       **
**                    verification error has occurred.                        **
**                                                                            **
** Description      : This function locks DFlash/PFlash sectors with          **
**                    configured protection profile and is called             **
**                    from lock API.                                          **
*******************************************************************************/
/* [cover parentID={88EA5D66-90BB-4b50-BC42-6C84BEAA22AF}][/cover] */
FlsLoader_ReturnType FlsLoader_lLock(FlsLoader_UcbType Ucb)
{
  FlsLoader_ReturnType RetError;

  #if (FLASH_OTP_OWP_PROTECTION_TRUE == TRUE)
  uint32 OtpUcbOStates;      /*Confirm states of all OTPx_ORIG UCBs */
  uint32 SingleOtpUcbOState; /*Confirm state of single OTP_ORIG UCB */
  uint8  StartPos;
  uint8  LoopCount;
  FlsLoader_ReturnType RetOtp;
  #endif

  #if (FLASH_PROTECTION_TRUE == TRUE)
  FlsLoader_AddressType UcbSectorAddress;
  const FlsLoader_AddressType *PdataPtr ;
  #endif  /*FLASH_PROTECTION_TRUE*/

  /*Initial return value is E_OK*/
  RetError = FLSLOADER_E_OK;

  /* [cover parentID={286E17A6-4AE9-4a05-A475-73856CC35863}][/cover] */
  if (Ucb == FLSLOADER_UCB_PFLASH)
  {
    /* [cover parentID={E0C333E7-2865-4d8b-8B3F-1E51F4C684D6}][/cover] */
    /* Check if write or read protection is enabled for PF sectors*/
    #if (FLASH_READ_WRITE_PTOTECTION_TRUE == TRUE)

    /*Read PF COPY UCB sector address */
    UcbSectorAddress = FLSLOADER_UCB_PFLASH_COPY_START;

    /*Read address of source data to be used for PF lock */
    PdataPtr = (const FlsLoader_AddressType *)(&FlsLoader_UcbPFlashPage0[0]);

    /* [cover parentID={49D4A6C1-C193-46ac-B5AD-72F56248F040}][/cover] */
    RetError |= FlsLoader_lLockCmdCycles(UcbSectorAddress, PdataPtr);

    /*Read PF ORIG UCB sector address */
    UcbSectorAddress = FLSLOADER_UCB_PFLASH_ORGINAL_START;

    /* [cover parentID={F3FF3EA2-17D6-4722-832C-74A269D5904C}][/cover] */
    RetError |= FlsLoader_lLockCmdCycles(UcbSectorAddress, PdataPtr);

    #endif
  }
  /* [cover parentID={36F1B839-A416-42e4-99F6-C79980A3D83A}][/cover] */
  else if(Ucb == FLSLOADER_UCB_DFLASH)
  {

    /* [cover parentID={8AB1AD72-2847-4f9b-9FEF-B9222ECB171C}][/cover] */
    #if (FLSLOADER_DF0_PROT != NO_PROTECTION)

    /*Read DF COPY UCB sector address */
    UcbSectorAddress = FLSLOADER_UCB_DFLASH_COPY_START;

    /*Read address of source data to be used for DF lock */
    PdataPtr = (const FlsLoader_AddressType *)(&FlsLoader_UcbDFlashPage0[0]);

    /* [cover parentID={98309C49-7967-4252-AE73-D6DF96C85404}][/cover] */
    RetError |= FlsLoader_lLockCmdCycles(UcbSectorAddress, PdataPtr);

    /*Read DF ORIG UCB sector address */
    UcbSectorAddress = FLSLOADER_UCB_DFLASH_ORIGINAL_START;

    /* [cover parentID={31B64055-25BD-4b8d-8FD5-605E1B6C3E4C}][/cover] */
    RetError |= FlsLoader_lLockCmdCycles(UcbSectorAddress, PdataPtr);

    #endif
  }
  else
  {
    /* [cover parentID={0CB0BDA6-1DAB-42dc-AF50-3C136BA9E052}][/cover] */
    #if (FLASH_OTP_OWP_PROTECTION_TRUE == TRUE)

    RetOtp = FLSLOADER_E_LOCKED;

    /*Extract confirm states of all OTPx_ORIG UCBs*/
    OtpUcbOStates = (DMU_HF_CONFIRM2.U) & FLSLOADER_MASK_ORIG_STATES;

    /*Read address of source data to be used for PF OTP/WOP lock */
    PdataPtr = (const FlsLoader_AddressType *)(&FlsLoader_UcbOTPFlashPage0[0]);

    /* [cover parentID={79A07640-F1B7-4389-97EB-FDB347E1E7FC}][/cover] */
    for(LoopCount = 0U; (LoopCount < FLSLOADER_NUM_8); LoopCount++)
    {
      /*Calculate start position of current ucb state*/
      StartPos = (LoopCount << FLSLOADER_SHF_1);

      /*Extract state of current UCB to be programmed*/
      SingleOtpUcbOState = EXTRACT(OtpUcbOStates,StartPos,\
                                        FLSLOADER_SIZE_2_BITS);

      /* [cover parentID={E82D2687-DCC2-4cc8-8F93-E2FE615DDB86}][/cover] */
      /* Allow programming only if UCB is in UNLOCKED state*/
      if(SingleOtpUcbOState == FLSLOADER_UCB_FLASH_UNLOCKED)
      {
        RetOtp = FLSLOADER_E_OK;

        /*Calculate sector address of current OTPx_COPY UCB under loop*/
        UcbSectorAddress = FLSLOADER_UCB_OTP0_COPY_START + \
                           (FLSLOADER_UCB_OTP_SECTOR_SIZE * LoopCount);

        /* [cover parentID={3FB0BB30-B8D3-493e-A4C4-1E98B99C9D3F}][/cover] */
        /*Lock current OTPx ORIG UCB*/
        RetError |= FlsLoader_lLockCmdCycles(UcbSectorAddress, PdataPtr);

        /*Calculate sector address of current OTPx_ORIG UCB under loop*/
        UcbSectorAddress = FLSLOADER_UCB_OTP0_ORIG_START + \
                           (FLSLOADER_UCB_OTP_SECTOR_SIZE * LoopCount);

        /* [cover parentID={92479370-FE51-4fd7-830D-D250A6B6AE1B}][/cover] */
        /*Lock current OTPx ORIG UCB*/
        RetError |= FlsLoader_lLockCmdCycles(UcbSectorAddress, PdataPtr);
      }
    }

    /* [cover parentID={98ABCDAF-FD91-4a36-8C95-23EA00764A02}][/cover] */
    /*None of the UCBs are in UNLOCKED state, return E_LOCKED*/
    if(RetOtp == FLSLOADER_E_LOCKED)
    {
      RetError = FLSLOADER_E_LOCKED;
    }

    #endif
  }
  return RetError;
}

#if (FLASH_PROTECTION_TRUE == TRUE)
/*******************************************************************************
** Syntax           : LOCAL_INLINE FlsLoader_ReturnType                       **
**                      FlsLoader_lLockCmdCycles(                             **
**                      const FlsLoader_AddressType UcbSectorAddress,         **
**                      const FlashLoader_DataType* const PdataPtr)           **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : PdataPtr: Pointer to UCB data to be programmed          **
**                    StartAddress: DMU command interpreter address           **
**                    UcbSectorAddress: Address of UCB to be programmed       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FLSLOADER_E_OK: UCB programmed successfully.            **
**                    FLSLOADER_E_NOT_OK: UCB programming failed.             **
**                    Protection, sequence, operation, erase or               **
**                    program verification error has occurred.                **
**                                                                            **
** Description      : This function erases and writes the UCB passed by       **
**                    address.                                                **
*******************************************************************************/
/* [cover parentID={B720856C-E3CD-41aa-B3D7-BAD4525F032D}][/cover] */
LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lLockCmdCycles(
                        const FlsLoader_AddressType UcbSectorAddress,
                        const FlsLoader_AddressType* const PdataPtr)
{
  FlsLoader_ReturnType  RetError;
  uint32                TimeoutTicks;
  uint32                TickResolution;
  uint32                EraseErrStat;

  /* Erase the corresponding User Configuraiton Block */

  /* Clear error and status flags*/
  FlsLoader_lCommandCycle(FLSLOADER_CYCLE_5554, FLSLOADER_VALUE_FA);

  /*Invoke Erase Logical Sector Range command sequence*/

  /* Erase Logical Sector Range command cycle-1 */
  FlsLoader_lCommandCycle(FLSLOADER_CYCLE_AA50, UcbSectorAddress);

  /* Erase Logical Sector Range command cycle-2 */
  FlsLoader_lCommandCycle(FLSLOADER_CYCLE_AA58, FLSLOADER_NUM_UCB_SECTORS);

  /* Erase Logical Sector Range command cycle-3 */
  FlsLoader_lCommandCycle(FLSLOADER_CYCLE_AAA8, FLSLOADER_VALUE_80);

  /* Erase Logical Sector Range command cycle-4 */
  FlsLoader_lCommandCycle(FLSLOADER_CYCLE_AAA8, FLSLOADER_VALUE_50);

  /* [cover parentID={B73A533C-A35E-4e9f-96AA-231B79C6EAA6}]
  Get the STM timer resolution in nano seconds
  [/cover] */
  TickResolution = Mcal_DelayTickResolution();

  /* [cover parentID={B787E00D-7FBA-4bfd-928A-3B1E5A4A203C}]
  Erase state not set and counter is within timeout counts
  [/cover] */
  RetError = FlsLoader_lCheckBitSet(&DMU_HF_OPERATION.U, \
                                    FLSLOADER_ERASE_BIT_MASK);

  /* [cover parentID={40131FAE-42B0-4de8-9086-921DA79C9B11}]
  Erase state set within timeout
  [/cover] */
  if (RetError == FLSLOADER_E_OK)
  {
    TimeoutTicks = (uint32)\
                   (FLSLOADER_MAX_TIME_PER_DF_ERASE / TickResolution);

    /*Add 50% additional for DF hardware worst case scenario*/
    TimeoutTicks += (TimeoutTicks >> FLSLOADER_NUM_1);

    /*Add 10% additional buffer from software*/
    TimeoutTicks += (uint32)(TimeoutTicks / FLSLOADER_DIV_10);

    /* [cover parentID={87089CC0-11A4-4045-AD8D-AB88021ED882}]
    Check if erase is completed within calculated timeout
    [/cover] */
    RetError = FlsLoader_lBusyCheck(TimeoutTicks);

    /* [cover parentID={35B36BAA-596D-4565-9674-90DEE4B63160}] [/cover] */
    /*check if Flash busy is reset within TimeoutTicks*/
    if (RetError == FLSLOADER_E_OK)
    {
      /*Read EVER error status*/
      EraseErrStat = DMU_HF_ERRSR.B.EVER;

      /*Read OPER error status*/
      EraseErrStat |= DMU_HF_ERRSR.B.OPER;

      /* [cover parentID={1F4135BD-94EA-4041-801F-7DAB0E8D0EB5}] [/cover] */
      /* If EVER or OPER set, return E_NOT_OK*/
      if (EraseErrStat == FLSLOADER_BIT_SET)
      {
        RetError = FLSLOADER_E_NOT_OK;
      }
    }
  }

  /* Clear error and status flags */
  FlsLoader_lCommandCycle(FLSLOADER_CYCLE_5554, FLSLOADER_VALUE_FA);

  if (RetError == FLSLOADER_E_OK)
  {
    TimeoutTicks = (uint32)\
                   (FLSLOADER_MAX_TIME_PER_DF_PAGE / TickResolution);

    /*Add 10% additional buffer from software*/
    TimeoutTicks += (uint32)(TimeoutTicks / FLSLOADER_DIV_10);

    /* [cover parentID={C43475D8-E57A-41a7-BDA3-958F74D7F016}]
    Write the UCB
    [/cover] */
    RetError = FlsLoader_lLockCmdCyclesWrite(\
               UcbSectorAddress, PdataPtr, TimeoutTicks);
  }

  return RetError;
}
/*******************************************************************************
** Syntax           : LOCAL_INLINE FlsLoader_ReturnType                       **
**                         FlsLoader_lLockCmdCyclesWrite(                     **
**                         const FlsLoader_AddressType UcbSectorAddress,      **
**                         const FlsLoader_AddressType* const PdataPtr,       **
**                         const uint32 TimeoutTicks)                         **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : PdataPtr: UCB data to be programmed                     **
**                    TimeoutTicks: Timeout counts for one DF page write      **
**                    UcbSectorAddress  Address of the UCB to be programmed   **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FlsLoader_ReturnType                                    **
**                                                                            **
** Description      : This function Locks the required profile and called     **
**                    from Lock  API.                                         **
*******************************************************************************/
/* [cover parentID={70C5C9CC-71DD-47d6-AF1E-42C20958ED95}][/cover] */
LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lLockCmdCyclesWrite(
                         const FlsLoader_AddressType UcbSectorAddress,
                         const FlsLoader_AddressType* const PdataPtr,
                         const uint32 TimeoutTicks)
{
  FlsLoader_ReturnType           RetError;
  uint32                         Count;
  FlsLoader_AddressType          UcbAddress   = UcbSectorAddress;
  const FlsLoader_AddressType   *UcbDataPtr   = PdataPtr;
  uint32                         DataCount;
  uint32                         WriteErrStat;

  RetError = FLSLOADER_E_OK;

  /*Initialize local source data count*/
  DataCount = 0U;

  /* [cover parentID={FFA617B3-99E5-4440-A548-97D73D83B572}]
  Loop to write all UCB pages
  [/cover] */
  /* [cover parentID={1E69A87B-7527-4255-BBFA-83427BC51862}]
  Loop to write all UCB pages
  [/cover] */
  for (Count = 0U;
       (Count < FLSLOADER_NUM_UCB_PAGES) && (RetError == FLSLOADER_E_OK);
       Count++)
  {
    /* Clear error and status flags*/
    FlsLoader_lCommandCycle(FLSLOADER_CYCLE_5554, FLSLOADER_VALUE_FA);

    /* Enter the Page Mode */
    FlsLoader_lCommandCycle(FLSLOADER_CYCLE_5554, FLSLOADER_DFLASH_VAL);

    /* [cover parentID={4258E615-4689-4ae7-9D96-610A095605BF}]
    DFLASH not yet in Page Mode and Counter is within Timeout
    [/cover] */
    /* Check if Program Flash is in page mode */
    RetError = FlsLoader_lCheckBitSet(&DMU_HF_STATUS.U, \
                                      FLSLOADER_DFPAGE_BIT_MASK);

    /* [cover parentID={3A0A6904-BFD4-4be5-ACF8-E101E6810FF2}]
    DFLASH set to Pade mode within Timeout
    [/cover] */
    /* Check PFPAGE/DFPAGE bit was SET */
    if (RetError == FLSLOADER_E_OK)
    {
      /* [cover parentID={FBB0F1DA-F45A-46ea-B66C-CA259FE557E3}]
         Load source data into hardware page assembly buffer
      [/cover] */
      /*load page assembly buffer first 32-bits*/
      FlsLoader_lCommandCycle(FLSLOADER_CYCLE_55F0, UcbDataPtr[DataCount]);

      /*load page assembly buffer next 32-bits*/
      FlsLoader_lCommandCycle(FLSLOADER_CYCLE_55F4, UcbDataPtr[DataCount + 1u]);

      /*Increment source data offset by 8-bytes*/
      DataCount += FLSLOADER_NUM_2;
      /* Load Page register gets incremented automatically. */

      /* Write Page command cycle-1 */
      FlsLoader_lCommandCycle(FLSLOADER_CYCLE_AA50, UcbAddress);

      /* Write Page command cycle-2 */
      FlsLoader_lCommandCycle(FLSLOADER_CYCLE_AA58, FLSLOADER_VALUE_00);

      /* Write Page command cycle-3 */
      FlsLoader_lCommandCycle(FLSLOADER_CYCLE_AAA8, FLSLOADER_VALUE_A0);

      /* Write Page command cycle-4 */
      FlsLoader_lCommandCycle(FLSLOADER_CYCLE_AAA8, FLSLOADER_VALUE_AA);

      /* [cover parentID={542F8B25-C69E-4d6b-9722-6EF2A45D94A2}]
      Flash program not Set and Counter within Timeout
      [/cover] */
      RetError = FlsLoader_lCheckBitSet(&DMU_HF_OPERATION.U, \
                                        FLSLOADER_PROG_BIT_MASK);

      /* [cover parentID={D61A7216-8FA7-4359-ACA8-BFDB05D530EC}]
      Flash program state Set within Timeout
      [/cover] */
      if (RetError == FLSLOADER_E_OK)
      {
        /* [cover parentID={F40BF83A-CB32-45b9-A704-BE0004723D9B}] [/cover] */
        RetError = FlsLoader_lBusyCheck(TimeoutTicks);

        /* [cover parentID={B013D452-1E42-4fbf-8FB4-0C942DD6BD51}]
        Check if UCB page is written within timeout and return status
        accordingly
        [/cover] */
        if (RetError == FLSLOADER_E_OK)
        {
          /*Read PVER error status*/
          WriteErrStat = DMU_HF_ERRSR.B.PVER;

          /*Read OPER error status*/
          WriteErrStat |= DMU_HF_ERRSR.B.OPER;

          /* [cover parentID={446A108C-89EF-4b50-B0B9-FDAA6233BBCE}] [/cover] */
          /* If PVER or OPER set, return E_NOT_OK */
          if (WriteErrStat == FLSLOADER_BIT_SET)
          {
            RetError = FLSLOADER_E_NOT_OK;
          }
        }
      }

      /* Clear the status if the operation is successful.*/
      FlsLoader_lCommandCycle(FLSLOADER_CYCLE_5554, FLSLOADER_VALUE_FA);

      /* Iterate the TargetAddress to the next page Address */
      UcbAddress = UcbAddress + FLSLOADER_PAGE_SIZE;

    }
  } /* End of For Loop */
  return RetError;
}

#endif /*#if (FLASH_PROTECTION_TRUE)*/
#endif  /* #if (FLSLOADER_LOCK_UNLOCK_API == STD_ON)*/

/*******************************************************************************
** Syntax :           FlsLoader_ReturnType FlsLoader_lCheckOTPWOP(void)       **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FLSLOADER_E_OK: At least one sector is not protected    **
**                    under OTP or WOP.                                       **
**                    FLSLOADER_E_ROMVERSION: All sectors are protected       **
**                    under OTP or WOP.                                       **
**                                                                            **
** Description      : This function checks if all PFlash banks are protected  **
**                    under OTP/WOP or not.                                   **
*******************************************************************************/
/* [cover parentID={5114BE32-B195-4dde-96F9-0564D486B272}][/cover] */
FlsLoader_ReturnType FlsLoader_lCheckOTPWOP(void)
{
  FlsLoader_ReturnType  RetError;
  uint32 FlsOTPCheck;
  uint32 FlsWOPCheck;
  uint32 * OtpAddress[FLSLOADER_OTP_REGS_6];
  uint32 * WopAddress[FLSLOADER_WOP_REGS_6];
  uint32 Count;


  uint8 FlsIndex = 0U;
  RetError = FLSLOADER_E_OK;

  /* [cover parentID={90822045-6F4A-4f6f-B1A7-554C3AAD84B9}]
  Loop to check if all PFlash banks are protected under OTP or WOP
  [/cover] */
  for(FlsIndex = 0U; FlsIndex < (uint8)FLSLOADER_NUM_OF_PFLASH_BANK; FlsIndex++)
  {
    /* Check OTP register of all the sectors */
    uint32 FlsSector = (uint8)FlsLoader_PFlashSectorCount[FlsIndex];

    FlsOTPCheck = FLSLOADER_PROCON_CHECK;
    FlsWOPCheck = FLSLOADER_PROCON_CHECK;

    /*MISRA2012_RULE_11_3_JUSTIFICATION: OtpAddress typecasted for SFR access, 
    4 byte aligned access*/
    /*MISRA2012_RULE_11_8_JUSTIFICATION: OtpAddress typecasted for SFR access*/
    OtpAddress[FLSLOADER_INDEX_0] = (uint32 *) \
                     &(MODULE_DMU.HP[FlsIndex].PROCON_OTP0.U);

    /*MISRA2012_RULE_11_3_JUSTIFICATION: OtpAddress typecasted for SFR access,
    4 byte aligned access*/
    /*MISRA2012_RULE_11_8_JUSTIFICATION: OtpAddress typecasted for SFR access*/
    OtpAddress[FLSLOADER_INDEX_1] = (uint32 *) \
                     &(MODULE_DMU.HP[FlsIndex].PROCON_OTP1.U);

    /*MISRA2012_RULE_11_3_JUSTIFICATION: OtpAddress typecasted for SFR access
    4 byte aligned access*/
    /*MISRA2012_RULE_11_8_JUSTIFICATION: OtpAddress typecasted for SFR access*/
    OtpAddress[FLSLOADER_INDEX_2] = (uint32 *) \
                     &(MODULE_DMU.HP[FlsIndex].PROCON_OTP2.U);

    /*MISRA2012_RULE_11_3_JUSTIFICATION: OtpAddress typecasted for SFR access
    4 byte aligned access*/
    /*MISRA2012_RULE_11_8_JUSTIFICATION: OtpAddress typecasted for SFR access*/
    OtpAddress[FLSLOADER_INDEX_3] = (uint32 *) \
                     &(MODULE_DMU.HP[FlsIndex].PROCON_OTP3.U);

    /*MISRA2012_RULE_11_3_JUSTIFICATION: OtpAddress typecasted for SFR access
    4 byte aligned access*/
    /*MISRA2012_RULE_11_8_JUSTIFICATION: OtpAddress typecasted for SFR access*/
    OtpAddress[FLSLOADER_INDEX_4] = (uint32 *) \
                     &(MODULE_DMU.HP[FlsIndex].PROCON_OTP4.U);

    /*MISRA2012_RULE_11_3_JUSTIFICATION: OtpAddress typecasted for SFR access
    4 byte aligned access*/
    /*MISRA2012_RULE_11_8_JUSTIFICATION: OtpAddress typecasted for SFR access*/
    OtpAddress[FLSLOADER_INDEX_5] = (uint32 *) \
                     &(MODULE_DMU.HP[FlsIndex].PROCON_OTP5.U);

    /*MISRA2012_RULE_11_3_JUSTIFICATION: WopAddress typecasted for SFR access
    4 byte aligned access*/
    /*MISRA2012_RULE_11_8_JUSTIFICATION: OtpAddress typecasted for SFR access*/
    WopAddress[FLSLOADER_INDEX_0] = (uint32 *) \
                     &(MODULE_DMU.HP[FlsIndex].PROCON_WOP0.U);

    /*MISRA2012_RULE_11_3_JUSTIFICATION: WopAddress typecasted for SFR access
    4 byte aligned access*/
    /*MISRA2012_RULE_11_8_JUSTIFICATION: OtpAddress typecasted for SFR access*/
    WopAddress[FLSLOADER_INDEX_1] = (uint32 *) \
                     &(MODULE_DMU.HP[FlsIndex].PROCON_WOP1.U);

    /*MISRA2012_RULE_11_3_JUSTIFICATION: WopAddress typecasted for SFR access
    4 byte aligned access*/
    /*MISRA2012_RULE_11_8_JUSTIFICATION: OtpAddress typecasted for SFR access*/
    WopAddress[FLSLOADER_INDEX_2] = (uint32 *) \
                     &(MODULE_DMU.HP[FlsIndex].PROCON_WOP2.U);

    /*MISRA2012_RULE_11_3_JUSTIFICATION: WopAddress typecasted for SFR access
    4 byte aligned access*/
    /*MISRA2012_RULE_11_8_JUSTIFICATION: OtpAddress typecasted for SFR access*/
    WopAddress[FLSLOADER_INDEX_3] = (uint32 *) \
                     &(MODULE_DMU.HP[FlsIndex].PROCON_WOP3.U);

    /*MISRA2012_RULE_11_3_JUSTIFICATION: WopAddress typecasted for SFR access
    4 byte aligned access*/
    /*MISRA2012_RULE_11_8_JUSTIFICATION: OtpAddress typecasted for SFR access*/
    WopAddress[FLSLOADER_INDEX_4] = (uint32 *) \
                     &(MODULE_DMU.HP[FlsIndex].PROCON_WOP4.U);

    /*MISRA2012_RULE_11_3_JUSTIFICATION: WopAddress typecasted for SFR access
    4 byte aligned access*/
    /*MISRA2012_RULE_11_8_JUSTIFICATION: OtpAddress typecasted for SFR access*/
    WopAddress[FLSLOADER_INDEX_5] = (uint32 *) \
                     &(MODULE_DMU.HP[FlsIndex].PROCON_WOP5.U);

    Count = 0U;

    /* [cover parentID={22DB197C-0B7F-463c-B597-0F3EE018E290}]
    Check for unprotected sector
    [/cover] */
    while(FlsSector != 0U)
    {
      /* Check OTP status of the all the register */
      FlsOTPCheck &= *OtpAddress[Count];
      /* Check WOP status of the all the register */
      FlsWOPCheck &= *WopAddress[Count];
      FlsSector -= FLSLOADER_DECREMENT_BY_32;
      Count++;
    }

    /* [cover parentID={90AB8115-DD08-479e-8118-EFD74574167B}]
     All PFlash banks are protected with OTP or WOP
    [/cover] */
    if((FlsOTPCheck != FLSLOADER_PROCON_CHECK) &&
        (FlsWOPCheck != FLSLOADER_PROCON_CHECK))
    {
        break;
    }
  }

  if (FlsIndex == (uint8)FLSLOADER_NUM_OF_PFLASH_BANK)
  {
    /* All sectors of all the banks are either WOP or OTP protected */
    RetError = FLSLOADER_E_ROMVERSION;
  }

  return RetError;
}

#define FLSLOADER_STOP_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_PFlashOffset'
 * before #include memap.h - Accepted deviation in AUTOSAR */
#include "FlsLoader_MemMap.h"

/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
[/cover] */
/* [cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
#define FLSLOADER_START_SEC_WRITEERASE_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_PFlashOffset'
 * before #include memap.h - Accepted deviation in AUTOSAR */
#include "FlsLoader_MemMap.h"

#if ((FLSLOADER_ENABLE_LOCKCHECK == STD_ON) ||\
     (FLSLOADER_DEV_ERROR_DETECT == STD_ON))
/*******************************************************************************
** Syntax :           LOCAL_INLINE uint32 FlsLoader_lSectorNumber(            **
**                               const uint32 Offset, const uint32 FlashBank) **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : FlashBank: Flash bank number (DFlash0, PFlash0 to       **
**                    PFlash5)                                                **
**                    offset: Offset from start address of flash              **
**                    bank to given target address                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Sector number that starts after given offset.           **
**                                                                            **
** Description      : This function identifies and returns the sector number  **
**                    which starts immediately after given                    **
**                    offset memory.                                          **
*******************************************************************************/
/* [cover parentID={729FFEE7-E968-475f-ACA1-7703BAFB2FC7}][/cover] */
LOCAL_INLINE uint32 FlsLoader_lSectorNumber(const uint32 Offset,
                                            const uint32 FlashBank)
{
  uint32 SectorNumber;
  uint32 TotalSectros = (uint32)FlsLoader_PFlashSectorCount[FlashBank];

  /* [cover parentID={74AE1847-E952-4d67-95A4-B937C5F99C07}]
  Loop to identify the sector number for given offset
  [/cover] */
  for(SectorNumber = 0U;
      SectorNumber < TotalSectros;
      SectorNumber++)
  {

    /* [cover parentID={B9E07213-695C-4bdd-9DAC-36A0CB1E3098}]
    Condition to identify sector number for given offset
    [/cover] */
    if((SectorNumber * FLSLOADER_PF_SECTOR_SIZE) == Offset)
    {
      break;
    }
  }
  /* [cover parentID={DC417A2D-6B15-4bf5-B5EA-54FF4E73F358}]
   Loop count reached one more than total available sectors
  [/cover] */
  if(SectorNumber == TotalSectros)
  {
    SectorNumber = FLSLOADER_INV;
  }

  return SectorNumber;
}

#endif /*#if ((FLSLOADER_ENABLE_LOCKCHECK == STD_ON) ||\
             (FLSLOADER_DEV_ERROR_DETECT == STD_ON))*/

#if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
/*******************************************************************************
** Syntax           :  FlsLoader_ReturnType FlsLoader_lWriteDetCheck(         **
**                      const FlsLoader_LengthType Length,                    **
**                      const FlsLoader_AddressType TargetAddress             **
**                    )                                                       **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : Length: Number of bytes to be written.                  **
**                    TargetAddress: Start address for the write              **
**                    operation.                                              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FLSLOADER_E_OK: No DET.                                 **
**                    FLSLOADER_E_NOT_OK: Driver not initialized or invalid   **
**                    length or invalid target address.                       **
**                                                                            **
** Description      : This function performs DET check for FlsLoader_Write API**
*******************************************************************************/
/* [cover parentID={E441D833-617B-488c-9F6F-567F052F48E1}][/cover] */
FlsLoader_ReturnType FlsLoader_lWriteDetCheck(
                                     const FlsLoader_LengthType Length,
                                     const FlsLoader_AddressType TargetAddress)
{
  uint8                     ErrorHook;
  FlsLoader_ReturnType      RetError;
  FlsLoader_AddressType     WriteEndAddr;
  uint32                    TargetPfBank;

  /* Init RetError to OK */
  RetError = FLSLOADER_E_OK;

  /* [cover parentID={68DBAD36-3389-4a0a-84A8-5250BA6FA191}]
  Driver is initialized
  [/cover] */
  /* check for Init DET */
  if (FlsLoader_InitStatus != FLSLOADER_INITIALIZED)
  {

    /* [cover parentID={A861C04C-E9F5-42ed-85E9-DB757B958D39}]
    Report DET FLSLOADER_E_UNINIT
    [/cover] */
    /* Report missing initialization DET */
    (void)Det_ReportError(FLSLOADER_MODULE_ID,
                        FLSLOADER_INSTANCE_ID,
                        FLSLOADER_SID_WRITE,
                        FLSLOADER_E_UNINIT);
    RetError = FLSLOADER_E_NOT_OK;
  }

  /* [cover parentID={51A6FCC7-F09A-4a77-8F6A-3AC794C4A31A}]
   Target address is page aligned and within DFlash/PFlash boundary
   [/cover] */
  /* Check of TargetAddress
    TargetAddress can be multiple of 256 bytes in case of PFLASH or 32 bytes.
    in case of DFLASH. */
  /* Report Invalid TargetAddress to DET */
  if (RetError != FLSLOADER_E_NOT_OK)
  {
    /* [cover parentID={736A8FD8-7BB7-40c7-9B39-17EDAAC84088}]
    Check if Target address is within PFLASH/DFLASH and
    aligned to page boudaries [/cover] */
    ErrorHook = FlsLoader_lAddressPageCheck(TargetAddress);
    if (FALSE == ErrorHook)
    {

      /* [cover parentID={ECE5875A-6263-4aef-83AB-28AB90773487}]
      Report DET FLSLOADER_E_PARAM_ADDRESS
      [/cover] */
      (void)Det_ReportError(FLSLOADER_MODULE_ID,
                          FLSLOADER_INSTANCE_ID,
                          FLSLOADER_SID_WRITE,
                          FLSLOADER_E_PARAM_ADDRESS);

      RetError = FLSLOADER_E_NOT_OK;
    }
  }

  if (RetError != FLSLOADER_E_NOT_OK)
  {
    /* [cover parentID={4752D431-0955-4b4a-831F-97F4AA5A4C68}]
    Target address belongs to DFlash
    [/cover] */
    /* Returns true if, position is DFLASH address */
    if (FlsLoader_lCheckFlashType(TargetAddress) == TRUE)
    {


      /* [cover parentID={A390B892-367B-4a51-948E-2EFA263DDB28}]
      Check that length (number of bytes to be written) does not exceed DFlash
      range
      [/cover] */
      /* [cover parentID={289E1414-E41B-4122-BA29-0D8247235669}]
      Length is within DFlash
      [/cover] */
      /* Given TargetAddress and Length should not exceed the flash
       * boundary.*/
      /* Its Data Flash assign,Report invalid Length to DET */
      if (FlsLoader_lDFlashPageCheck(TargetAddress, Length) == FALSE)
      {

        /* [cover parentID={DACFC141-5495-49cb-99EB-8C9EA49EA302}]
        Report DET FLSLOADER_E_PARAM_LENGTH
        [/cover] */
        (void)Det_ReportError(FLSLOADER_MODULE_ID,
                            FLSLOADER_INSTANCE_ID,
                            FLSLOADER_SID_WRITE,
                            FLSLOADER_E_PARAM_LENGTH);

        RetError = FLSLOADER_E_NOT_OK;
      }
    }
    else  /*PFlash*/
    {
      /* [cover parentID={7F313A20-2ACE-46e3-B3B4-A4E0B3C2F98C}]
      Length is zero or more than 16MB
      [/cover] */
      /*Length is zero or more than 16MB*/
      if ((Length == (FlsLoader_LengthType)0U) || \
          (Length > (FlsLoader_LengthType)FLSLOADER_MAX_PF_WRITE_DATA_LENGTH))
      {
        (void)Det_ReportError(FLSLOADER_MODULE_ID,
                            FLSLOADER_INSTANCE_ID,
                            FLSLOADER_SID_WRITE,
                            FLSLOADER_E_PARAM_LENGTH);

        RetError = FLSLOADER_E_NOT_OK;
      }
      else
      {
        /* [cover parentID={BBC5CD9E-D23A-44f4-AE24-1CD0A56AD140}]
        Length is aligned to PFlash page size
        [/cover] */
        if ((Length & (FlsLoader_LengthType)FLSLOADER_MOD_32) != 0U)
        {
          (void)Det_ReportError(FLSLOADER_MODULE_ID,
                              FLSLOADER_INSTANCE_ID,
                              FLSLOADER_SID_WRITE,
                              FLSLOADER_E_PARAM_LENGTH);

          RetError = FLSLOADER_E_NOT_OK;
        }
        /* [cover parentID={5C27CBB0-1FFA-42f9-9D20-063B1F025366}]
        End address to be written is within addressable PFlash range
        [/cover] */
        else
        {
          /*Get PFlash bank number in which the write operation is intended*/
          TargetPfBank = FlsLoader_lGetFlashType(TargetAddress);

          /*Calculate the end address of write operation*/
          WriteEndAddr = (TargetAddress + Length) - 1U;

          /*Check if the end address of write operation lies within the end
           address of PFlash bank in which the write operation is intended*/
          if (WriteEndAddr > FlsLoader_PFlashEndAddress[TargetPfBank])
          {
            (void)Det_ReportError(FLSLOADER_MODULE_ID,
                                FLSLOADER_INSTANCE_ID,
                                FLSLOADER_SID_WRITE,
                                FLSLOADER_E_PARAM_LENGTH);

            RetError = FLSLOADER_E_NOT_OK;
          }
        }
      }
    }
  }
  return RetError;
}
/*******************************************************************************
** Syntax           :  FlsLoader_ReturnType FlsLoader_lEraseDetCheck(         **
**                      FlsLoader_LengthType Length,                          **
**                      FlsLoader_AddressType TargetAddress)                  **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : Length: Number of sectors to be erased                  **
**                    TargetAddress: Target address for erase operation       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FLSLOADER_E_OK: No DET.                                 **
**                    FLSLOADER_E_NOT_OK: Driver not initialized or           **
**                    invalid length or invalid target address.               **
**                                                                            **
** Description      : This function performs DET check for FlsLoader_Erase    **
**                    API.                                                    **
*******************************************************************************/
/* [cover parentID={566C33D9-6CCC-4c06-ABEE-49440B7C795B}][/cover] */
FlsLoader_ReturnType FlsLoader_lEraseDetCheck(
                                const FlsLoader_LengthType Length,
                                const FlsLoader_AddressType TargetAddress)
{
  FlsLoader_ReturnType  RetError;
  uint8                 ErrorHook;

  RetError = FLSLOADER_E_OK;

  /* [cover parentID={0CF3D2CF-7A58-41c4-BF65-48E96ECC5758}]
    Driver initialized
  [/cover] */
  if (FlsLoader_InitStatus != FLSLOADER_INITIALIZED)
  {
    /* [cover parentID={66B07C7A-31BF-44d2-92D2-533A24DF62B2}]
       Report DET FLSLOADER_E_UNINIT
    [/cover] */
    /* CD_FlsLoader039: Report missing initilization to DET */
    (void)Det_ReportError(FLSLOADER_MODULE_ID,
                        FLSLOADER_INSTANCE_ID,
                        FLSLOADER_SID_ERASE,
                        FLSLOADER_E_UNINIT);
    RetError = FLSLOADER_E_NOT_OK;
  }
  else
  {
    /* [cover parentID={D8DA631A-3B7D-4cfc-A6D5-20912770A67C}]
       Target address is within the addressable PFlash range
    [/cover] */
    /* CD_FlsLoader041: Report invalid TargetAddress to DET */
    if (FlsLoader_lCheckFlashType(TargetAddress) == TRUE)
    {
      /* [cover parentID={D9E7564A-B368-4850-8127-928E52D8AD18}]
       Target erase is for DFlash
      [/cover] */
      /* Check for DFLASH Address*/
      if (FlsLoader_lDFlashCheck(TargetAddress) == TRUE)
      {
        /* [cover parentID={223BC3CE-8A72-4459-9C6E-801E58F44C03}]
        Check if Target address belongs to DF0_EEPROM or DF_UCB start sector
        [/cover] */
        ErrorHook = FlsLoader_lDFlashAddressCheck(TargetAddress);

        /* [cover parentID={DEE6DC69-5F94-49cd-B7E8-259FDDC2B748}]
          Target address is out of addressable DFlash 0 range or not
          aligned to sector size
        [/cover] */
        if  (FALSE == ErrorHook)
        {
          /* [cover parentID={676EC340-5325-4acc-A039-61E9C0F0F69E}]
           Report DET FLSLOADER_E_PARAM_ADDRESS
          [/cover] */
          /* TargetAddress not aligned to sector of DF0_EEPROM or DF_UCB*/
          (void)Det_ReportError(FLSLOADER_MODULE_ID,
                              FLSLOADER_INSTANCE_ID,
                              FLSLOADER_SID_ERASE,
                              FLSLOADER_E_PARAM_ADDRESS);
          RetError = FLSLOADER_E_NOT_OK;
        }
      }
      else
      {

        /* [cover parentID={676EC340-5325-4acc-A039-61E9C0F0F69E}]
          Report DET FLSLOADER_E_PARAM_ADDRESS
        [/cover] */
        /* TargetAddress does not belong to DF0_EEPROM or DF_UCB*/
        (void)Det_ReportError(FLSLOADER_MODULE_ID,
                            FLSLOADER_INSTANCE_ID,
                            FLSLOADER_SID_ERASE,
                            FLSLOADER_E_PARAM_ADDRESS);
        RetError = FLSLOADER_E_NOT_OK;
      }
      if (RetError != FLSLOADER_E_NOT_OK)
      {
        /* [cover parentID={3752567F-D5FE-46fd-A436-8D1D37AAC76D}]
        Check if given Lenght is within DF0_EEPROM or DF_UCB addressable range
        [/cover] */
        ErrorHook = FlsLoader_lDFlashLengthCheck(Length, TargetAddress);

        /* [cover parentID={2828207A-97F8-4272-9DA0-83387208FE38}][/cover] */
        if(FALSE == ErrorHook)
        {

          /* [cover parentID={98DAADC9-B035-40a7-A94E-C90E52C17FE8}]
             Report DET FLSLOADER_E_PARAM_LENGHT
          [/cover] */
          (void)Det_ReportError(FLSLOADER_MODULE_ID,
                              FLSLOADER_INSTANCE_ID,
                              FLSLOADER_SID_ERASE,
                              FLSLOADER_E_PARAM_LENGTH);
          RetError = FLSLOADER_E_NOT_OK;
        }
      }
    }
    else
    {

      /* [cover parentID={FF4ED600-43A7-43e6-B529-D208F91C63FB}][/cover] */
      /*Check if passed target address lies within valid PFlash range*/
      if (FlsLoader_lPFlashCheck(TargetAddress) == FALSE)
      {
        /* [cover parentID={676EC340-5325-4acc-A039-61E9C0F0F69E}]
           Report DET FLSLOADER_E_PARAM_ADDRESS
        [/cover] */
        (void)Det_ReportError(FLSLOADER_MODULE_ID,
                            FLSLOADER_INSTANCE_ID,
                            FLSLOADER_SID_ERASE,
                            FLSLOADER_E_PARAM_ADDRESS);

        RetError = FLSLOADER_E_NOT_OK;
      }
      else
      {
        /* [cover parentID={D17B4D4A-5D75-4b96-8814-EA3B9BADAE63}]
         Check if target address aligned to the PFlash sector size and
         length of sectors to be erased is within the respective bank
        [/cover] */
        /* [cover parentID={5AB5014A-7B9D-44f2-BF90-096F16102A00}]
          Target address aligned to PFlash sector size
        [/cover] */
        ErrorHook = FlsLoader_lPFlashAddressCheck(Length,\
                                                  TargetAddress);
        /* [cover parentID={D8DA631A-3B7D-4cfc-A6D5-20912770A67C}]
        Is Target Address within PFLASH addressable range
        [/cover] */
        if  (ErrorHook == FLSLOADER_UNALIGNED_SECTOR_ADDR)
        {

          /* [cover parentID={676EC340-5325-4acc-A039-61E9C0F0F69E}]
             Report DET FLSLOADER_E_PARAM_ADDRESS
          [/cover] */
          (void)Det_ReportError(FLSLOADER_MODULE_ID,
                              FLSLOADER_INSTANCE_ID,
                              FLSLOADER_SID_ERASE,
                              FLSLOADER_E_PARAM_ADDRESS);

          RetError = FLSLOADER_E_NOT_OK;
        }

        if  (ErrorHook == FLSLOADER_LENGTH_OUTSIDE_RANGE)
        {

          /* [cover parentID={D0681A59-B688-4bb4-A35E-0523C681740E}]
             Length is within PFlash range
          [/cover] */
          (void)Det_ReportError(FLSLOADER_MODULE_ID,
                              FLSLOADER_INSTANCE_ID,
                              FLSLOADER_SID_ERASE,
                              FLSLOADER_E_PARAM_LENGTH);

          RetError = FLSLOADER_E_NOT_OK;
        }
      }
    } /* end of if check FlashType */
  }
  return RetError;
}
/*******************************************************************************
** Syntax           :   LOCAL_INLINE boolean FlsLoader_lAddressPageCheck(     **
**                                 const FlsLoader_AddressType TargetAddress) **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : TargetAddress: Target address in Flash for write        **
**                    operation.                                              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : TRUE: Valid Target address.                             **
**                    FALSE: Invalid Target address. It is either non-aligned **
**                    or out of addressable Flash range.                      **
**                                                                            **
** Description      : The function checks if Target address is within         **
**                    addressable Flash (PFlash or DFlash) range and          **
**                    is aligned to page size of respective Flash or not.     **
*******************************************************************************/
/* [cover parentID={865A6049-708F-4f31-AD84-61F8FB4CB56B}][/cover] */
LOCAL_INLINE boolean FlsLoader_lAddressPageCheck(
                                  const FlsLoader_AddressType TargetAddress)
{
  boolean RetVal;
  /* Init ErrorHook to false */
  RetVal = FALSE;

  /* [cover parentID={5872A1D1-9998-48b7-A03C-0C77BD33E0C6}]
  Target address is aligned to 32 byte boundary
  [/cover] */
  /* Check of TargetAddress can be multiple of 256 bytes or 32 bytes. */
  /* CD_FlsLoader036 :Report Invalid TargetAddress to DET */
  if (FlsLoader_lPFlashCheck(TargetAddress) == TRUE)
  {
    /* First byte is already checked, last two nibbles must be zero for 256
       byte address*/
    /* [cover parentID={63BDC5B9-1BD8-4571-8022-382B10683B9A}]
    Target address is aligned to 8 byte boundary
    [/cover] */
    if((TargetAddress & (FlsLoader_AddressType)FLSLOADER_MOD_32) == \
                                                          FLSLOADER_POSITION_0)
    {
      /* valid sector Address */
      RetVal = TRUE;
    }
  }
  else
  {
    /* [cover parentID={DA6C7B3C-BA02-4ecd-AF4D-012091D4B6FE}]
    Target address is within addressable DFlash range
    [/cover] */
    if(FlsLoader_lDFlashCheck(TargetAddress) == TRUE)
    {

      /* [cover parentID={CF60733F-562D-437f-A3ED-3B1DD5C50FAE}]
      Target address is within addressable PFlash range
      [/cover] */
      if((TargetAddress & (FlsLoader_AddressType)FLSLOADER_MOD_8) == \
                                                          FLSLOADER_POSITION_0)
      {
        RetVal = TRUE;
      }
    }
  } /* end of if TargetAddress check */
  return RetVal;
}
/*******************************************************************************
** Syntax           :  LOCAL_INLINE boolean FlsLoader_lDFlashCheck(           **
**                                       FlsLoader_AddressType TargetAddress) **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : TargetAddress: Target address for erase or write        **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : 0: Target address is outside the addressable DFlash 0   **
**                    range                                                   **
**                    1: Target address is within the addressable DFlash 0    **
**                    range                                                   **
**                                                                            **
** Description      : This function checks if Target address of an erase or   **
**                    write operation lies within the addressable             **
**                    DFlash 0 range or not.                                  **
*******************************************************************************/
/* [cover parentID={B2AD1BB7-9DBA-4e5a-A855-0C4E9FFD5C1E}][/cover] */
LOCAL_INLINE boolean FlsLoader_lDFlashCheck(
                                  const FlsLoader_AddressType TargetAddress)
{
  boolean RetVal;
  RetVal  = FALSE;

  /* [cover parentID={520835FB-3627-4722-A87F-F19F90458C17}]
     Target address is within DFlash 0 EEPROM range
  [/cover] */
  if(TargetAddress >= FLSLOADER_DFLASH0_START_ADDRESS)
  {
    /* [cover parentID={520835FB-3627-4722-A87F-F19F90458C17}]
    Target address is within DFlash 0 EEPROM range
    [/cover] */
    if(TargetAddress <= FLSLOADER_DFLASH0_END)
    {
      RetVal = TRUE;
    }
  }

  /* [cover parentID={7086AED6-BD60-4f61-9911-ED87CC2B3D9E}]
  Is Target address within the DF_UCB addressable range
  [/cover] */
  if(TargetAddress >= FLSLOADER_UCB_START)
  {
    /* [cover parentID={7086AED6-BD60-4f61-9911-ED87CC2B3D9E}]
       Target address is within DFlash 0 UCB range
    [/cover] */
    if(TargetAddress <= FLSLOADER_UCB_END)
    {
      RetVal = TRUE;
    }
  }
  return RetVal;
}

/*******************************************************************************
** Traceability     :                                                         **
** Syntax   :   LOCAL_INLINE boolean FlsLoader_lDFlashAddressCheck(           **
**                      const FlsLoader_AddressType TargetAddress             **
**                    )                                                       **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : TargetAddress : Target address for erase                **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : TRUE: Valid target address                              **
**                    FALSE: Invalid target address                           **
**                                                                            **
** Description      : This function checks if Target address of erase         **
**                    operation is aligned to the size of DFlash 0            **
**                    (EEPROM or UCB) sector or not.                          **
*******************************************************************************/
/* [cover parentID={859407CE-C543-4e89-A9BC-4FBE2E3B3406}][/cover] */
LOCAL_INLINE boolean FlsLoader_lDFlashAddressCheck(
                                     const FlsLoader_AddressType TargetAddress)
{
  uint16               DfSegment;
  boolean              RetVal;
  RetVal = FALSE;
  DfSegment = (uint16)(TargetAddress >> FLSLOADER_SHIFT_BY_20);

  /* [cover parentID={D0A6D047-957C-41f9-BB6E-F52257B77AF8}]
    Target address is within addressable DFlash 0 range
  [/cover] */

  if (DfSegment == FLSLOADER_DF_EEPROM_SEGMENT)
  {

    /* [cover parentID={F052754C-7331-41de-B611-0C79E2B71ED3}]
       Target address is aligned to the size of DFlash sector
    [/cover] */
    if ((TargetAddress & (FlsLoader_AddressType)FLSLOADER_EEPROM_SECTOR_SIZE) \
        == FLSLOADER_POSITION_0)
    {
      /*Valid DF_EEPROM Start Sector Address */
      RetVal = TRUE;
    }
  }
  else
  {

    /* [cover parentID={58612F10-41AB-404b-9176-29065F799A0A}]
     Target address is aligned to the size of UCB
    [/cover] */
    if ((TargetAddress & (FlsLoader_AddressType)FLSLOADER_UCB_SECTOR_SIZE_1) \
        == FLSLOADER_POSITION_0)
    {
      /*Valid DF_UCB Start Sector Address */
      RetVal = TRUE;
    }
  }

  return RetVal;
}
/*******************************************************************************
** Syntax           : LOCAL_INLINE boolean FlsLoader_lDFlashLengthCheck(      **
**                      const FlsLoader_LengthType NumberOfSectors,           **
**                      const FlsLoader_AddressType TargetAddress             **
**                    )                                                       **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : NumberOfSectors: Number of sectors to be checked        **
**                    TargetAddress: Start address in DFlash                  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : 0: Number of sectors exceeds the addressable DFlash 0   **
**                    range                                                   **
**                    1: Number of sectors lie within the addressable DFlash 0**
**                    range                                                   **
**                                                                            **
** Description      : This function checks if number of sectors to be erased  **
**                    from start address of a DFlash erase operation          **
**                    lie within the addressable DFlash 0 range or not.       **
*******************************************************************************/
/* [cover parentID={CA4B8B9E-CEEA-4c3a-9273-8BF95F54C557}][/cover] */
LOCAL_INLINE boolean FlsLoader_lDFlashLengthCheck(
                                    const FlsLoader_LengthType NumberOfSectors,
                                    const FlsLoader_AddressType TargetAddress)
{
  uint32               DFLengthCheck;
  uint16               DfSegment;
  boolean              RetVal;

  RetVal = TRUE;
  DfSegment = (uint16)(TargetAddress >> FLSLOADER_SHIFT_BY_20);

  /* [cover parentID={A1CB4A5C-A80B-4a08-AA21-04C3B573958F}]
  Number of sectors are zero
  [/cover] */
  if ((NumberOfSectors == 0U) || \
      (NumberOfSectors > FLSLOADER_MAX_ERASE_SECTOR_DF))
  {
    RetVal = FALSE;
  }
  else
  {
    /* [cover parentID={0CE1F51A-9088-41d6-B808-91F07EA8BAAF}]
    Target address is within DFlash 0 UCB range
    [/cover] */
    if (DfSegment == FLSLOADER_DF_EEPROM_SEGMENT)
    {
      DFLengthCheck = ((uint32)(TargetAddress + (FlsLoader_AddressType)\
                       (NumberOfSectors * FLSLOADER_DFLASH_SECTOR_SIZE)))\
                       -1U;
      /* [cover parentID={B353E419-91FF-46f4-BC26-EC736CA8EB20}]
      End address exceeds the range of DFlash 0 EEPROM
      [/cover] */
      if ( DFLengthCheck > FLSLOADER_DFLASH0_END )
      {
        /*InValid DF_EEPROM Sector Length */
        RetVal = FALSE;
      }
    }

    /* [cover parentID={6B378743-8D8D-4599-B061-D56F09C5A946}]
    Start address is within DFlash 0 EEPROM range
    [/cover] */
    if (DfSegment == FLSLOADER_DF_UCB_SEGMENT)
    {
      DFLengthCheck = ((uint32)(TargetAddress + (FlsLoader_AddressType) \
                       (NumberOfSectors * FLSLOADER_UCB_SECTOR_SIZE))) - 1U;

      /* [cover parentID={C6F6A193-EC7E-4d19-A9AC-D1F60A1A90A3}]
      End address exceeds the range of DFlash 0 UCB
      [/cover] */
      if ( DFLengthCheck > FLSLOADER_UCB_END )
      {
        RetVal = FALSE; /*InValid DF_EEPROM Sector Length*/
      }
    }
  }

  return RetVal;
}

/*******************************************************************************
** Syntax           : LOCAL_INLINE boolean FlsLoader_lPFlashCheck(            **
**                                 const FlsLoader_AddressType TargetAddress) **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : TargetAddress: Target address for erase or write        **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : TRUE: Target address is within the addressable range of **
**                          a PFlash bank.                                    **
**                    FALSE: Target address is outside the addressable range  **
**                           of all available PFlash banks.                   **
**                                                                            **
** Description      : The function checks if target address lies within the   **
**                    addressable range of available PFlash banks.            **
*******************************************************************************/
/* [cover parentID={A560C272-A051-41c8-BB23-8A531983AB38}][/cover] */
LOCAL_INLINE boolean FlsLoader_lPFlashCheck(
                         const FlsLoader_AddressType TargetAddress)
{
  boolean  RetVal;
  uint8    LoopCount;

  RetVal = FALSE;

  /* [cover parentID={74489053-FF78-405e-9869-8E02A5EFCE7C}][/cover] */
  /*Loop through each PFlash bank to validate passed target address*/
  for (LoopCount = 0U; LoopCount < (uint8)FLSLOADER_NUM_OF_PFLASH_BANK; LoopCount++)
  {
    /* [cover parentID={11419F58-6B84-40f4-A7E7-FBA5FB28EA37}][/cover] */
    /* [cover parentID={8B888B71-6297-4240-ADC3-5062E268AB9A}][/cover] */
    /*Check if passed target address lies within current PF bank*/
    if ((TargetAddress >= FlsLoader_PFlashOffset[LoopCount]) &&\
        (TargetAddress <= FlsLoader_PFlashEndAddress[LoopCount]))
    {
      /* Target address is within current PF bank, return TRUE, stop the loop*/
      RetVal = TRUE;
      break;
    }
  }

  return RetVal;
}

/*******************************************************************************
** Syntax           : LOCAL_INLINE uint8 FlsLoader_lPFlashAddressCheck(       **
**                                  const FlsLoader_LengthType Len,           **
**                                  const FlsLoader_AddressType TargetAddress)**
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : Len: Number of sectors to be erased                     **
**                    TargetAddress: Target address for erase                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : 0: Valid target address and length                      **
**                    1: Invalid target address and/or length                 **
**                                                                            **
** Description      : This function checks,                                   **
**                    1. Target address of erase operation is aligned         **
**                    to the size of PFlash sector or not.                    **
**                    2. Number of sectors to be erased from target address   **
**                    lie within the addressable PFlash range or not.         **
*******************************************************************************/
/* [cover parentID={C736DCB2-9BA1-4cfd-9021-F7A275D8B341}][/cover] */
LOCAL_INLINE uint8 FlsLoader_lPFlashAddressCheck(
                                     const FlsLoader_LengthType Len,
                                     const FlsLoader_AddressType TargetAddress)
{
  uint8     RetVal = 0U;
  uint32    Offset;
  uint32    SectorNumber;
  uint8     NoOfSectors;
  uint32    FlashBank;

  /* [cover parentID={AB9B6067-1A5B-4b25-8970-AC3A9F5EAEE6}]
  Length of sectors to be erased is zero or more than 192
  [/cover] */
  if ((Len == (FlsLoader_LengthType)0U) ||
      (Len > (FlsLoader_LengthType)FLSLOADER_MAX_ERASE_SECTOR_PF))
  {
    /*Invalid Erase Length*/
    RetVal = FLSLOADER_LENGTH_OUTSIDE_RANGE;
  }
  else
  {
    /* [cover parentID={6D94D8B4-AB6E-4bf6-A93B-78AFAEBEB291}]
    Read the PFlash bank number to which the target address belongs
    [/cover] */
    FlashBank = FlsLoader_lGetFlashType(TargetAddress);
    NoOfSectors = FlsLoader_PFlashSectorCount[FlashBank];

    Offset = TargetAddress - FlsLoader_PFlashOffset[FlashBank];

    /* [cover parentID={6ED47787-01B9-4b0c-93A4-F85964822584}]
    Check if target address points to valid sector address in PFlash bank
    and get the sector number
    [/cover] */
    SectorNumber = FlsLoader_lSectorNumber(Offset, FlashBank);

    /* [cover parentID={82355749-8D77-4678-8DA9-A0A895D177DE}]
    Valid sector number received
    [/cover] */
    if(SectorNumber == FLSLOADER_INV)
    {
      /* Target address is not the start address of a sector */
      RetVal = FLSLOADER_UNALIGNED_SECTOR_ADDR;
    }
    else
    {

      /* [cover parentID={C72F3AF2-FD65-4fd1-8CFE-9EFBD0A2665B}]
      End sector number exceeds the maximum sectors available for the PFlash
      bank
      [/cover] */
      /* Check if affected number of sectors are more than the available one */
      if ((SectorNumber + Len) > NoOfSectors)
      {
        RetVal = FLSLOADER_LENGTH_OUTSIDE_RANGE;
      }
    }
  }

  return RetVal;
}

/*******************************************************************************
** Syntax           : LOCAL_INLINE boolean FlsLoader_lDFlashPageCheck(        **
**                                 const FlsLoader_AddressType TargetAddress, **
                                   const FlsLoader_LengthType Length )        **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : Length: Number of bytes for write                       **
**                    TargetAddress: Target address for write                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : TRUE: Valid length for write operation                  **
**                    FALSE: Invalid length for write operation               **
**                                                                            **
** Description      : This function checks if length of data to be written    **
**                    using write API is within the addressable               **
**                    DFlash 0 range and is 8 byte aligned or not.            **
*******************************************************************************/
/* [cover parentID={6F39F5B2-0944-4a6a-85B0-25778DD20981}][/cover] */
LOCAL_INLINE boolean FlsLoader_lDFlashPageCheck(
                                    const FlsLoader_AddressType TargetAddress,
                                    const FlsLoader_LengthType Length)
{
  boolean                   RetVal;
  uint16                    DfSegment;
  FlsLoader_LengthType      TargetEnd;
  RetVal   = TRUE;

  /* [cover parentID={EF574830-021D-4f56-9E8D-CE3C518C50F4}]
   Length is zero bytes or more than 1MB
  [/cover] */
  if (((Length) == (FlsLoader_LengthType) 0U) || \
      (Length > \
      (FlsLoader_LengthType) FLSLOADER_MAX_DF_WRITE_DATA_LENGTH))
  {
    RetVal = FALSE;
  }
  /* [cover parentID={7221A8CE-B010-4bd7-8EE5-BEF9DCA205D4}]
     Length is 8 byte aligned
  [/cover] */
  else if (((Length) & ((FlsLoader_LengthType)FLSLOADER_MOD_8)) != 0U)
  {
    RetVal = FALSE;
  }
  else
  {
    /* Check address is in EEPROM Segment or in UCB segment */
    DfSegment = (uint16)(TargetAddress >> FLSLOADER_SHIFT_BY_20);

    /* [cover parentID={5219156A-8818-4d60-8A73-DF2B2224A0FE}]
     Target address is within the addressable DFlash 0 EEPROM range
    [/cover] */
    if (DfSegment == FLSLOADER_DF_EEPROM_SEGMENT)
    {
      TargetEnd = (Length+(TargetAddress & FLSLOADER_DFLASH0_ADDRESS_MASK))-1U;

      /* [cover parentID={42A42DA2-79A0-4378-A2B8-52FACCC3C7CE}]
          End address exceeds the addressable DFlash 0 EEPROM range
      [/cover] */
      if (TargetEnd > (FlsLoader_LengthType)FLSLOADER_EEPROM_OFFSETEND)
      {
        RetVal = FALSE;
      }
    }
    else
    {
      TargetEnd = (Length+(TargetAddress & FLSLOADER_UCB_ADDRESS_MASK))-1U;

      /* [cover parentID={F32EF248-98BB-441c-A486-822DC04F5EC4}]
         End address exceeds the addressable DFlash 0 UCB range
      [/cover] */
      if (TargetEnd > (FlsLoader_LengthType)FLSLOADER_UCB_ADDRESS_MASK)
      {
        RetVal = FALSE;
      }
    }
  }
  return RetVal;
}
#endif /* #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON) */

/*******************************************************************************
** Syntax           : uint32 FlsLoader_lGetFlashType(                         **
**                                 const FlsLoader_AddressType TargetAddress) **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : TargetAddress: Target address in Flash                  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Flash bank number:                                      **
**                    PFlash 0 = 0                                            **
**                    PFlash 1 = 1                                            **
**                    PFlash 2 = 2                                            **
**                    PFlash 3 = 3                                            **
**                    PFlash 4 = 4                                            **
**                    PFlash 5 = 5                                            **
**                    DFlash 0 = 16                                           **
**                                                                            **
** Description      : This function checks for which bank the target address  **
**                    belongs to and returns the bank number.                 **
*******************************************************************************/
/* [cover parentID={C12BD30D-1ED9-4531-BD2F-95B6A93FD292}][/cover] */
uint32 FlsLoader_lGetFlashType(
                        const FlsLoader_AddressType TargetAddress)
{
  uint32      Flash_Type;
#if (FLSLOADER_NUM_OF_PFLASH_BANK > FLSLOADER_ONE_U8)
  uint8       PfSegment;
  uint8       Count;
  uint8       FlashBank;
  uint8       FlashBankMask;
#endif

  /* [cover parentID={EBA0869C-7B17-4bba-BF7C-000D2BE83E4D}]
    7th nibble of target address is zero
  [/cover] */
  if (FlsLoader_lCheckFlashType(TargetAddress) == TRUE)
  {
    Flash_Type = FLSLOADER_DFLASH_BANK0;
  }
  else
  {
    /* Given Address belongs to PFLASH  */
    /* Address 7th Nibble | PFlash Bank */
    /* ---------------------------------*/
    /*  (0-2)             | PF0         */
    /*  (3-5)             | PF1         */
    /*  (6-8)             | PF2         */
    /*  (9-B)             | PF3         */
    /*  (C-E)             | PF4         */
    /*  (F)               | PF5         */

    Flash_Type = FLSLOADER_PFLASH_BANK0;
#if (FLSLOADER_NUM_OF_PFLASH_BANK > FLSLOADER_ONE_U8)
    /*get 7th nibble of input TargetAddress*/
    PfSegment = (uint8)((TargetAddress >> FLSLOADER_SHIFT_BY_20)
                        & FLSLOADER_PFLASH_MASK);

    /* [cover parentID={26174A12-4FC6-4ed4-955E-B8A558E0FC9A}]
       Loop to identify PFlash bank for target address
    [/cover] */
    for(Count = FLSLOADER_ONE_U8; Count < \
        (uint8)FLSLOADER_NUM_OF_PFLASH_BANK; Count++)
    {
      /*Check from Last Bank*/
      FlashBank = (uint8)FLSLOADER_NUM_OF_PFLASH_BANK - Count;

      /*Get the 7th nibble for the flash bank*/
      FlashBankMask = (uint8) ((FlsLoader_PFlashOffset[FlashBank]
                                >> FLSLOADER_SHIFT_BY_20)
                               & FLSLOADER_PFLASH_MASK);

      /* [cover parentID={91734FB2-EDD5-44c4-A9C4-5E7E3BA6D791}]
      Check to identify the PFlash bank
      [/cover] */
      /* nibble matches for the flash bank*/
      if(PfSegment >= FlashBankMask)
      {
        /*return matched bank number*/
        Flash_Type = (uint32)FlashBank;
        break;
      }
    }
#endif
  }
  return Flash_Type;
}

#if (FLSLOADER_ENABLE_LOCKCHECK == STD_ON)
/*******************************************************************************
** Syntax           :  FlsLoader_ReturnType                                   **
**                     FlsLoader_lFlashLockCheck(                             **
**                               const FlsLoader_AddressType TargetAddress,   **
**                               const uint32 FlashType,                      **
**                               const FlsLoader_LengthType Length)           **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : FlashType: Flash bank number (DFlash0, PFlash0 to       **
**                    PFlash5)                                                **
**                    Length: Length in bytes for write operation             **
**                    TargetAddress: Target address for write operation       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FLSLOADER_E_OK: No sector is protected in given write   **
**                    length.                                                 **
**                    FLSLOADER_E_LOCKED: At least one sector is              **
**                    protected in given write length.                        **
**                                                                            **
** Description      : This function checks if any sector in given write       **
**                    length is protected by write/OTP/WOP protection.        **
*******************************************************************************/
/* [cover parentID={9E14CA2B-90D4-436f-83FF-BB0AC2644E3C}][/cover] */
FlsLoader_ReturnType FlsLoader_lFlashLockCheck(
                        const FlsLoader_AddressType TargetAddress,
                        const uint32 FlashType,
                        const FlsLoader_LengthType Length)
{
  uint32                FlsFpro;
  uint32                FlsFprod;
  uint32                FlsProcondrpro1;
  FlsLoader_ReturnType  RetError;

  RetError = FLSLOADER_E_OK;

  /* [cover parentID={BCAF0E8D-F1E9-472e-A2E4-8FC42BEBD81C}]
     Flash type is PFlash
  [/cover] */
  if (FlashType != FLSLOADER_DFLASH_BANK0)
  {
    /* Read PF protection disable status */
    FlsFpro = DMU_HF_PROTECT.B.PRODISP;

    /* [cover parentID={E5C6FC36-E478-4d23-84DF-6C18C35A4680}]
       PFlash protection disable set
    [/cover] */
    if (FlsFpro != 1U)
    {

      /* [cover parentID={CFC5BCEB-24F3-4015-A2C3-D6C95C6EDD48}]
        Check if any sector in the given write length is protected by
        write/WOP/OTP protection
      [/cover] */
      /* [cover parentID={0F56D49F-8D3F-4a8a-8AAD-C6C72F2409D4}]
       Check if any sector in the given write length is protected by
       write/WOP/OTP protection
      [/cover] */
      RetError = FlsLoader_lPFlashSectorCheck(TargetAddress, Length, FlashType);
    }
  }
  else
  {
    /*Check if global write protection is installed in DFLASH*/
    /*Read DF protection disable status*/
    FlsFprod = DMU_HF_PROTECT.B.PRODISD;

    /*Read DF write protection status*/
    FlsProcondrpro1 = DMU_HF_PROCONDF.B.L;

    /* [cover parentID={C898C1B1-DC86-4abf-B8EF-06C934107488}]
    DFlash protection disable not set and write protection is enabled
    [/cover] */
    if(FlsFprod != 1U)
    {

      /* [cover parentID={C898C1B1-DC86-4abf-B8EF-06C934107488}]
        DFlash protection disable not set and write protection is enabled
      [/cover] */
      /* [cover parentID={AEF2A4DE-51E5-41fe-8D95-10B132485285}]
      [/cover] */
      if(FlsProcondrpro1 == 1U)
      {
        RetError = FLSLOADER_E_LOCKED;
      }
    }
  }
  return RetError;
}

/*******************************************************************************
** Syntax           : LOCAL_INLINE FlsLoader_ReturnType                       **
**                    FlsLoader_lPFlashSectorCheck (                          **
**                                 const FlsLoader_AddressType TargetAddress, **
**                                 const FlsLoader_LengthType Length,         **
**                                 const uint32 FlashType)                    **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : FlashType: Flash bank number (DFlash0, PFlash0 to       **
**                    PFlash5)                                                **
**                    Length: Number of bytes to be written                   **
**                    TargetAddress: Target address for write operation       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FLSLOADER_E_OK: All sectors falling under target        **
**                    address and length are not protected.                   **
**                    FLSLOADER_E_LOCKED: At least one sector falling under   **
**                    target address and length is write protected.           **
**                                                                            **
** Description      : This function identifies all PFlash sectors falling     **
**                    under target address and length and checks if           **
**                    any sector is write protected or not.                   **
*******************************************************************************/
/* [cover parentID={877F3909-67B7-4438-9B92-F296717721B9}][/cover] */
LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lPFlashSectorCheck(
                          const FlsLoader_AddressType TargetAddress,
                          const FlsLoader_LengthType Length,
                          const uint32 FlashType)
{
  uint32                SectorNumber;
  uint32                SectorNumber1;
  uint32                SectorLength;
  uint8                 SectorMask;
  uint32                Offset;
  uint32                Offset1;
  FlsLoader_ReturnType  RetError;
  FlsLoader_AddressType EndAddress;
  const uint32          *FlsRegProconp0;

  RetError = FLSLOADER_E_OK;

  /*MISRA2012_RULE_11_3_JUSTIFICATION: typecasted for SFR access*/
  /*MISRA2012_RULE_11_8_JUSTIFICATION: cast away volatile for SFR access,
  4 byte aligned access*/
  FlsRegProconp0 = (uint32*) & (MODULE_DMU.HP[FlashType].PROCON_P0.U);

  uint8 NumberOfSector = FlsLoader_PFlashSectorCount[FlashType];
  /* Address offset within the sector */
  Offset = TargetAddress - FlsLoader_PFlashOffset[(uint8)FlashType];

  /* Let's find the start sector */
  for(SectorNumber = 0U; SectorNumber < NumberOfSector; SectorNumber++)
  {
    if(Offset < (FLSLOADER_PF_SECTOR_SIZE * SectorNumber))
    {
      break;
    }
  }

  SectorNumber--;

  /* Let's find the end sector+1 */
  EndAddress = TargetAddress + Length;
  Offset1 = EndAddress - FlsLoader_PFlashOffset[(uint8)FlashType];

  for(SectorNumber1 = 0U; SectorNumber1 < NumberOfSector; SectorNumber1++)
  {
    if(Offset1 < (FLSLOADER_PF_SECTOR_SIZE * SectorNumber1))
    {
      break;
    }
  }

  SectorLength = SectorNumber1 - SectorNumber;

  /* [cover parentID={FA5C092A-B81F-4d5c-8BB6-F1F233FB78DD}]
  Check if any sector is write protected and report status
  [/cover] */
  SectorMask = FlsLoader_lCheckProtStatus(FlsRegProconp0, \
                                          SectorLength, \
                                          SectorNumber);

  /* [cover parentID={0CE6D2C2-D037-4fac-97B2-D83D18ECC577}]
  At least one sector is write protected
  [/cover] */
  if(SectorMask != FALSE)
  {
    RetError = FLSLOADER_E_LOCKED;
  }

  return RetError;
}
/*******************************************************************************
** Syntax           :  FlsLoader_ReturnType                                   **
**                     FlsLoader_lEraseLockCheck (                            **
**                              const FlsLoader_AddressType TargetAddress,    **
**                              const uint32 FlashType,                       **
**                              const FlsLoader_LengthType Length)            **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : FlashType: Flash bank number (DFlash0, PFlash0 to       **
**                    PFlash5)                                                **
**                    Length: Number of sectors to be erased                  **
**                    TargetAddress: Target address for erase operation       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FLSLOADER_E_OK: No sector is protected in given erase   **
**                    length.                                                 **
**                    FLSLOADER_E_LOCKED: At least one sector is              **
**                    protected in given erase length.                        **
**                                                                            **
** Description      : This function checks if any sector in given erase       **
**                    length is protected by write/OTP/WOP protection.        **
*******************************************************************************/
/* [cover parentID={6E43B182-5E52-41f0-AA22-07715E3DB729}][/cover] */
FlsLoader_ReturnType FlsLoader_lEraseLockCheck(
                    const FlsLoader_AddressType TargetAddress,
                    const uint32 FlashType,
                    const FlsLoader_LengthType Length)
{
  uint32                FlsFproD;
  uint32                FlsProcond2;
  uint32                FlsFpro;
  FlsLoader_ReturnType  RetError;
  uint32                SectorNumber;
  uint32                Offset;

  RetError = FLSLOADER_E_OK;

  /* [cover parentID={B33F37FC-E10A-41fd-97D1-759BFB3A1F4B}]
    Flash type is DFlash
  [/cover] */
  /* Given Address belongs to Data FLASH */
  /*Check if the Target Address passed is UCB protected */
  /* Check if global write protection is installed in DFLASH*/
  if (FlashType == FLSLOADER_DFLASH_BANK0)
  {
    /*Read DF protection disable status*/
    FlsFproD = DMU_HF_PROTECT.B.PRODISD;

    /*Read DF write protection status*/
    FlsProcond2 = DMU_HF_PROCONDF.B.L;

    /* [cover parentID={A39C14CF-ED85-43b7-94E7-B8A04649B51D}]
      DFlash protection disable Set
    [/cover] */
    if (FlsFproD != 1U)
    {
      /* [cover parentID={ADF8EAF2-0F08-41bc-944A-F71F9AAA28BD}]
        DFlash write protection enabled
      [/cover] */
      if(FlsProcond2 == 1U)
      {
        RetError = FLSLOADER_E_LOCKED;
      }
    }
  }
  else
  {
    /*Check if the Target Address passed is UCB protected */
    /* Protection Check Algorithm */
    /* Preprocessor switch to enable/disable the lockcheck functionality */
    /* Check if global write protection is installed */
    FlsFpro = DMU_HF_PROTECT.B.PRODISP;

    /* [cover parentID={0B9C55E7-6F7D-42d2-A540-58957CDD2E33}]
      PFlash protection disable Set
    [/cover] */
    if(FlsFpro != 1U)
    {
      Offset = TargetAddress - FlsLoader_PFlashOffset[FlashType];

      /* [cover parentID={D156EB68-2E8C-428f-8F3B-351245501BCD}]
          Sector is proected
      [/cover] */
      SectorNumber = FlsLoader_lSectorNumber(Offset, FlashType);

      /* [cover parentID={D156EB68-2E8C-428f-8F3B-351245501BCD}]
         Sector is proected
      [/cover] */
      RetError = FlsLoader_lSectorProtCheck(FlashType, SectorNumber, Length);
    }

  }
  return RetError;
}

/*******************************************************************************
** Syntax           : FlsLoader_ReturnType  FlsLoader_lSectorProtCheck(       **
**                      uint32 FlashType,uint32 SectorNumber,                 **
**                      FlsLoader_LengthType Length )                         **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : FlashType: Flash bank number (PFlash0 to PFlash5)       **
**                    Length: Number of sectors to be checked                 **
**                    SectorNumber: Start sector number                       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FLSLOADER_E_OK: Sectors are not locked.                 **
**                    FLSLOADER_E_LOCKED: At least one sector is locked.      **
**                                                                            **
** Description      : This function checks the protection status of all the   **
**                    PFlash sectors ranging from given sector                **
**                    number and length and returns status accordingly.       **
*******************************************************************************/
/* [cover parentID={B90407F8-393C-4e8f-A8B8-6E7218807366}][/cover] */
LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lSectorProtCheck(
                                           const uint32 FlashType,
                                           const uint32 SectorNumber,
                                           const FlsLoader_LengthType Length)
{
  uint8        RetProtError = 0U;
  uint8        RetOtpError  = 0U;
  uint8        RetWopError  = 0U;
  const uint32 *FlsRegProconp;
  const uint32 *FlsRegProconWop;
  const uint32 *FlsRegProconOtp;

  FlsLoader_ReturnType RetError = FLSLOADER_E_OK;

  /*MISRA2012_RULE_11_3_JUSTIFICATION: typecasted for SFR access,
  4 byte aligned access*/
  /*MISRA2012_RULE_11_8_JUSTIFICATION: cast away volatile for SFR access*/
  FlsRegProconp = (uint32 *) & (MODULE_DMU.HP[FlashType].PROCON_P0.U);

  /*MISRA2012_RULE_11_3_JUSTIFICATION: typecasted for SFR access,
  4 byte aligned access*/
  /*MISRA2012_RULE_11_8_JUSTIFICATION: cast away volatile for SFR access*/
  FlsRegProconWop = (uint32 *) & (MODULE_DMU.HP[FlashType].PROCON_WOP0.U);

  /*MISRA2012_RULE_11_3_JUSTIFICATION: typecasted for SFR access,
  4 byte aligned access*/
  /*MISRA2012_RULE_11_8_JUSTIFICATION: cast away volatile for SFR access*/
  FlsRegProconOtp = (uint32 *) & (MODULE_DMU.HP[FlashType].PROCON_OTP0.U);

  /* [cover parentID={A0C8F8F5-A12D-4242-9EEC-FEC7E97D7F54}]
    Check and report write protection status of all given sectors
  [/cover] */
  RetProtError =  FlsLoader_lCheckProtStatus(\
                  FlsRegProconp, Length, SectorNumber);

  /* [cover parentID={D4A4B6C8-87D0-4b03-83AF-757F2325D9FE}]
    Check and report OTP protection status of all given sectors
  [/cover] */
  RetOtpError =  FlsLoader_lCheckProtStatus(\
                 FlsRegProconOtp, Length, SectorNumber );

  /* [cover parentID={A1615BA5-431C-4a2e-A740-2830A929B2F8}]
    Check and report WOP protection status of all given sectors
  [/cover] */
  RetWopError =  FlsLoader_lCheckProtStatus(\
                 FlsRegProconWop, Length, SectorNumber );
  /* [cover parentID={35E7DEDC-11E2-4493-BDF6-E99439067DA0}]
  [/cover] */
  if((RetProtError == TRUE) ||
      (RetOtpError == TRUE) ||
      (RetWopError == TRUE))
  {
    /* Sectors are locked */
    RetError = FLSLOADER_E_LOCKED;
  }
  else
  {
    /* Sectors are not locked */
    RetError = FLSLOADER_E_OK;
  }

  return RetError;
}

/*******************************************************************************
** Syntax:           LOCAL_INLINE uint32 FlsLoader_lCheckBitStatus(\          **
**                               const uint32* const StartAddress,            **
**                               const uint32 First, const uint32 Last)       **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : First: Start bit to be checked                          **
**                    Last: End bit to be checked                             **
**                    StartAddress: Address of register for bit status check  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Register bit mask value from first to last bit.         **
**                                                                            **
** Description      : This function returns the bit mask value of the register**
**                    from first to last bit.                                 **
*******************************************************************************/
/* [cover parentID={BFADDF49-AAAE-4894-83EE-5F88DF5B8A95}][/cover] */
LOCAL_INLINE uint32 FlsLoader_lCheckBitStatus(\
                                 const uint32* const StartAddress,
                                 const uint32 First, const uint32 Last)
{
  uint32 MsbFlushCount;
  uint32 MaskStatus  = *StartAddress;
  uint32 LastBitPos = Last;

  LastBitPos--;
  /* Number of MSB bits to be flushed */
  MsbFlushCount = FLSLOADER_BIT_POSITION_31 - LastBitPos;

  /* Flush MSB bits, back to original */
  MaskStatus = ( MaskStatus << MsbFlushCount) >> MsbFlushCount;
  /* Flush LSB and back to original */
  MaskStatus = ( MaskStatus >> First) << First;   /* Flush LSB bits */

  return MaskStatus;
  /*MISRA2012_RULE_8_13_JUSTIFICATION: StartAddress points to SFR access*/
}

/*******************************************************************************
** Syntax           :  LOCAL_INLINE boolean FlsLoader_lCheckProtStatus(       **
**                               const uint32 *const StartAddress,            **
**                                                const uint32 Length,        **
**                                                const uint32 Start)         **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : First: Start bit position to be checked.                **
**                    Length: Number of bits to be checked. Each bit          **
**                    represents one sector.                                  **
**                    StartAddress: Base address of requested protection      **
**                    registers                                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FALSE : Sectors are not protected                       **
**                    TRUE : Sectors are protected                            **
**                                                                            **
** Description      : This function identifies the protection register(s) for **
**                    all corresponding sectors represented by start          **
**                    and length inputs and it checks and reports their       **
**                    protection status from the register(s).                 **
*******************************************************************************/
/* [cover parentID={BA2ADF3F-EFE4-4017-A57B-066A0BF95DB6}][/cover] */
LOCAL_INLINE boolean FlsLoader_lCheckProtStatus(
                                    const uint32* const StartAddress,
                                    const uint32 Length, const uint32 First)
{
  boolean RetError = FALSE;
  uint32 MaskStatus   = 0U;
  uint32 LastRegVal   = 0U;
  uint32 FirstRegVal  = 0U;
  uint32 FirstBitPos  = First;
  uint32 Last         = (FirstBitPos + Length);
  const uint32* Baseproconreg =  StartAddress;

  /* [cover parentID={4F41D0D5-A28D-4d31-B370-C3E71732F5D7}]
  Last bit to be checked is zero indicating all sectors have been checked
  for their protection status
  [/cover] */
  while(Last != 0U)
  {
    /* Check if last bit is in current register or not */
    LastRegVal = Last >> FLSLOADER_SHIFT_BY_5;

    /* [cover parentID={D25A9992-7389-4d96-A6F0-C1968053D32B}]
     Last bit is less than 32
    [/cover] */
    if(LastRegVal == 0U)
    {

      /* [cover parentID={002E47F4-DF68-4de1-B9BB-9416DCC4C0BF}]
         Current register need to be used for checking protection status.
         Read bit masked status from given first to last bits of current
         register.
      [/cover] */
      /* Last is in the current register */
      MaskStatus = FlsLoader_lCheckBitStatus(Baseproconreg,
                                             FirstBitPos, Last);
      Baseproconreg++;
      Last  = FLSLOADER_REG_FIRST_BIT;
      FirstBitPos = FLSLOADER_REG_FIRST_BIT;
    }
    else
    {
      /* Last bit lies in the next register */
      /* check if the first bit lies in the current register */
      FirstRegVal = FirstBitPos >> FLSLOADER_SHIFT_BY_5;

      /* [cover parentID={A2FD9311-9653-44ee-9A4B-A75BD9E58813}]
        First bit is less than 32
      [/cover] */
      if(FirstRegVal == 0U)
      {
        /* [cover parentID={D58F3228-2E36-4e98-8AE4-A3FF41FD94BB}]
         Current register need to be used for checking protection status.
         Read bit masked status from given first to last bits of current
         register.
        [/cover] */
        /* First bit lies in the current register */
        /* Mask will be from the First bit to the 31st bit for this register*/
        MaskStatus = FlsLoader_lCheckBitStatus(Baseproconreg,
                                            FirstBitPos, FLSLOADER_REG_32_BIT);
        Baseproconreg++;

        /* For next register read bits from starting i.e. First = 0 */
        FirstBitPos = 0U;
        Last = Last - FLSLOADER_DECREMENT_BY_32;
      }
      else
      {
        /*First bit lies is next register */
        /* Nothing to be read from this register as First bit is in next reg*/
        Baseproconreg++;
        Last  -= FLSLOADER_DECREMENT_BY_32;
        FirstBitPos -= FLSLOADER_DECREMENT_BY_32;
      }
    }
    /* [cover parentID={A462AFFC-1D7A-44f0-B4CB-BFBD419E566E}]
       Bit masked status of all bits from given first to last bit postion is
       zero
    [/cover] */
    if(MaskStatus != 0x00U)
    {
      /* Sectors are protected */
      RetError = TRUE;
      break;
    }
  }
  return RetError;
}

#endif /*#if (FLSLOADER_ENABLE_LOCKCHECK == STD_ON)*/

#define FLSLOADER_STOP_SEC_WRITEERASE_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: FlsLoader_MemMap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_PFlashOffset'
 * before #include memap.h - Accepted deviation in AUTOSAR */
#include "FlsLoader_MemMap.h"
