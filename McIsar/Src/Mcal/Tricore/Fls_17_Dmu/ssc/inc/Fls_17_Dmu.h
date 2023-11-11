/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2023)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : Fls_17_Dmu.h                                                **
**                                                                           **
**  VERSION    :  21.0.0                                                     **
**                                                                           **
**  DATE       :  2023-05-22                                                 **
**                                                                           **
**  VARIANT    : Variant PB                                                  **
**                                                                           **
**  PLATFORM   : Infineon AURIX2G                                            **
**                                                                           **
**  AUTHOR     : DL-AUTOSAR-Engineering                                      **
**                                                                           **
**  VENDOR     : Infineon Technologies                                       **
**                                                                           **
**  DESCRIPTION: This file exports functionality of Flash driver             **
**                                                                           **
**  SPECIFICATION(S) : Specification of FLS Driver,                          **
**                           AUTOSAR Release 4.2.2 and 4.4.0                 **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: No                                      **
**                                                                           **
******************************************************************************/
/* [cover parentID={D4AC2E4F-6D86-4b0b-A3E8-031DBD101412}][/cover] */
/* [cover parentID={D0DC9620-096E-49ad-B133-83B17D89DABC}][/cover] */
#ifndef  FLS_17_DMU_H
#define  FLS_17_DMU_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Inclusion of Platform_Types.h and Compiler.h  */
#include "Std_Types.h"

/* Global functions like Set/Reset END INIT protection bit,
  Enable/Disable interrupts, Atomic write function */
#include "McalLib.h"

/* Fls Module Configuration header file */
#include "Fls_17_Dmu_Cfg.h"

/* Conditional Inclusion of Developement Error Tracer File */
#if ((FLS_17_DMU_DEV_ERROR_DETECT == STD_ON ) || \
     (FLS_17_DMU_SAFETY_ENABLE == STD_ON) || (MCAL_AR_VERSION == MCAL_AR_440))
#include "Det.h"
#endif
/* Conditional inclusion of Mcal_Wrapper file for Runtime Error Reporting */
#if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
#include "Mcal_Wrapper.h"
#endif

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/*
    Published paramters
*/

/* FLS Vendor ID */
#define FLS_17_DMU_VENDOR_ID                  ((uint16)17)
/* FLS Module ID */
#define FLS_17_DMU_MODULE_ID                  ((uint16)92)

#if((FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) || \
    (FLS_17_DMU_SAFETY_ENABLE == STD_ON) || \
    (MCAL_AR_VERSION == MCAL_AR_440))
/* Development error values - DET's */
/* API service called with wrong parameter */
#define FLS_17_DMU_E_PARAM_CONFIG           ((uint8)1)
/* API service called with wrong/inconsistent Address(s)*/
#define FLS_17_DMU_E_PARAM_ADDRESS          ((uint8)2)
/* API service called with wrong/inconsistent length(s)*/
#define FLS_17_DMU_E_PARAM_LENGTH           ((uint8)3)
/* API service called with wrong/inconsistent Data(s)*/
#define FLS_17_DMU_E_PARAM_DATA             ((uint8)4)
/* API service called without module initalization */
#define FLS_17_DMU_E_UNINIT                 ((uint8)5)
/* API service called while    Driver is still busy  */
#define FLS_17_DMU_E_BUSY                   ((uint8)6)
/* Erase Verification (blank check) failed */
#define FLS_17_DMU_E_VERIFY_ERASE_FAILED    ((uint8)7)
/* Write Verification (compare) failed */
#define FLS_17_DMU_E_VERIFY_WRITE_FAILED    ((uint8)8)
/* Timeout for Erase/write jobs */
#define FLS_17_DMU_E_TIMEOUT                ((uint8)9)
/* API service called with NULL parameter */
#define FLS_17_DMU_E_PARAM_POINTER          ((uint8)10)
#endif /* FLS_DEV_ERROR_DETECT */

#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
/*Safety Errors*/
/* API service called with wrong/inconsistent Address(s)*/
#define FLS_17_DMU_SE_PARAM_ADDRESS          ((uint8)2)
/* API service called with wrong/inconsistent length(s)*/
#define FLS_17_DMU_SE_PARAM_LENGTH           ((uint8)3)
/* API service called with wrong/inconsistent Data(s)*/
#define FLS_17_DMU_SE_PARAM_DATA             ((uint8)4)
/* API service called while    Driver is still busy  */
#define FLS_17_DMU_SE_BUSY                   ((uint8)6)
/*Invalid parameter*/
#define FLS_17_DMU_SE_PARAM_INVLD            ((uint8)90)
/*Initialization failed in Init*/
#define FLS_17_DMU_SE_INIT_FAILED            ((uint8)95)
/*Suspend Operation not allowed*/
#define FLS_17_DMU_SE_ILLGL_OPERTN           ((uint8)100)
/*HW Busy*/
#define FLS_17_DMU_SE_HW_BUSY           ((uint8)110)
/*Timeout after the command is executed*/
#define FLS_17_DMU_SE_HW_TIMEOUT         ((uint8)115)
/*Suspend Erase Error*/
#define FLS_17_DMU_SE_SUSPNDERASE_FAIL      ((uint8)80)
/*Invalid Interrupt*/
#define FLS_17_DMU_SE_INVALID_ISR            ((uint8)120)
#endif/*Safety Errors*/

#if(FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) || \
   (FLS_17_DMU_SAFETY_ENABLE == STD_ON) || \
   (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON) || \
   (MCAL_AR_VERSION == MCAL_AR_440)
/* API Service ID's */
#define FLS_17_DMU_SID_INIT           ((uint8)0)
#define FLS_17_DMU_SID_ERASE          ((uint8)1)
#define FLS_17_DMU_SID_WRITE          ((uint8)2)
#define FLS_17_DMU_SID_CANCEL         ((uint8)3)
#define FLS_17_DMU_SID_GETSTATUS      ((uint8)4)
#define FLS_17_DMU_SID_GETJOBRESULT   ((uint8)5)
#define FLS_17_DMU_SID_MAIN           ((uint8)6)
#define FLS_17_DMU_SID_READ           ((uint8)7)
#define FLS_17_DMU_SID_COMPARE        ((uint8)8)
#define FLS_17_DMU_SID_SETMODE        ((uint8)9)
#define FLS_17_DMU_SID_BLANKCHECK     ((uint8)10)
#define FLS_17_DMU_SID_GETVERSIONINFO ((uint8)16)
#define FLS_17_DMU_SID_READSYNC       ((uint8)33)
#define FLS_17_DMU_SID_COMPARESYNC    ((uint8)34)
#define FLS_17_DMU_SID_CANCELNONERASE ((uint8)35)
#define FLS_17_DMU_SID_VERIFYERASE    ((uint8)36)
#define FLS_17_DMU_SID_VERIFYSECTORERASE ((uint8)44)
#define FLS_17_DMU_SID_SUSPENDERASE   ((uint8)37)
#define FLS_17_DMU_SID_GETOPERSTATUS  ((uint8)38)
#define FLS_17_DMU_SID_ISHARDENINGREQ ((uint8)40)
#define FLS_17_DMU_SID_ISR            ((uint8)45)
#define FLS_17_DMU_SID_RESUMEERASE    ((uint8)42)
#define FLS_17_DMU_SID_INITCHECK      ((uint8)43)
#define FLS_17_DMU_SID_GETECCERRORPGADDR ((uint8)46)
#endif /*API Sevice IDs*/


#if((MCAL_AR_VERSION == MCAL_AR_440) || ((MCAL_AR_VERSION == MCAL_AR_422) && (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)))
/* Run Time Errors */
#define FLS_17_DMU_E_ERASE_FAILED          ((uint8)0x01)
#define FLS_17_DMU_E_WRITE_FAILED          ((uint8)0x02)
#define FLS_17_DMU_E_READ_FAILED           ((uint8)0x03)
#define FLS_17_DMU_E_COMPARE_FAILED        ((uint8)0x04)
#define FLS_17_DMU_E_BLANKCHECK_FAILED     ((uint8)0x1E)
#define FLS_17_DMU_E_HARDENCHK_FAIL        ((uint8)0x37)
#define FLS_17_DMU_E_RESUME_FAIL           ((uint8)0x38)
#define FLS_17_DMU_E_INIT_FAILED           ((uint8)0x39)
#endif /* FLS_RUNTIME_ERROR_DETECT */

/* Options of FlsJobType */
#define FLS_17_DMU_NONE      ((uint8)0)
#define FLS_17_DMU_WRITE     ((uint8)1)
#define FLS_17_DMU_ERASE     ((uint8)2)
#define FLS_17_DMU_READ      ((uint8)3)
#define FLS_17_DMU_COMPARE   ((uint8)4)
#define FLS_17_DMU_READSYNC  ((uint8)5)
#define FLS_17_DMU_CANCEL    ((uint8)6)
#define FLS_17_DMU_COMPARESYNC    ((uint8)7)
#define FLS_17_DMU_VERIFYERASE    ((uint8)8)
#define FLS_17_DMU_BLANKCHECK     ((uint8)9)

#if(FLS_17_DMU_IFX_FEE_USED == STD_ON)
/*Hardening Return Values*/
#define FLS_17_DMU_HARDENCHK_NOTREQD  ((Fls_17_Dmu_HardenType)0)
#define FLS_17_DMU_HARDENCHK_REQRD    ((Fls_17_Dmu_HardenType)1)
#define FLS_17_DMU_HARDENCHK_ERROR    ((Fls_17_Dmu_HardenType)2)
/*Hardening Align Check*/
#define FLS_17_DMU_PAGE_HARDEN           ((uint8)(0x55))
#define FLS_17_DMU_WORDLINE_HARDEN       ((uint8)(0xAA))
#endif

#define FLS_17_DMU_BURST_PAGE_SIZE (32U)
#define FLS_17_DMU_WORDLINE_SIZE   (512U)

/* DF0's individual Logical sector size: 4K bytes */
#define FLS_17_DMU_LOGICALSECTOR_SIZE (4096U)

/*Worst case 100ns delay for the HW busy bit to get set for FSI@20Mhz.*/
#define FLS_17_DMU_HWBUSY_DELAY          (100U)

#define FLS_17_DMU_SUBSECTOR_SIZE (FLS_17_DMU_LOGICALSECTOR_SIZE)

#define FLS_17_DMU_MCAL_SUPERVISOR (0U)
#define FLS_17_DMU_MCAL_USER1      (1U)

#define FLS_17_DMU_PAGE_WRITE   (0U)
#define FLS_17_DMU_BURST_WRITE  (1U)

/* Options for DFLS Read Access Wait States.Note SysClk(Mhz)/ WaitStates <=63*/
#define FLS_17_DMU_WAITSTATE_READ_0  (0U)

#define FLS_17_DMU_WAITSTATE_READ_1  (1U)

#define FLS_17_DMU_WAITSTATE_READ_2  (2U)

#define FLS_17_DMU_WAITSTATE_READ_3  (3U)

#define FLS_17_DMU_WAITSTATE_READ_4  (4U)

#define FLS_17_DMU_WAITSTATE_READ_5  (5U)

#define FLS_17_DMU_WAITSTATE_READ_6  (6U)

#define FLS_17_DMU_WAITSTATE_READ_7  (7U)

#define FLS_17_DMU_WAITSTATE_READ_8  (8U)

#define FLS_17_DMU_WAITSTATE_READ_9  (9U)

#define FLS_17_DMU_WAITSTATE_READ_10 (10U)

#define FLS_17_DMU_WAITSTATE_READ_11 (11U)

#define FLS_17_DMU_WAITSTATE_READ_12 (12U)

#define FLS_17_DMU_WAITSTATE_READ_13 (13U)

#define FLS_17_DMU_WAITSTATE_READ_14 (14U)

#define FLS_17_DMU_WAITSTATE_READ_15 (15U)

#define FLS_17_DMU_WAITSTATE_READ_16 (16U)

#define FLS_17_DMU_WAITSTATE_READ_17 (17U)

#define FLS_17_DMU_WAITSTATE_READ_18 (18U)

#define FLS_17_DMU_WAITSTATE_READ_19 (19U)

#define FLS_17_DMU_WAITSTATE_READ_20 (20U)

#define FLS_17_DMU_WAITSTATE_READ_21 (21U)

#define FLS_17_DMU_WAITSTATE_READ_22 (22U)

#define FLS_17_DMU_WAITSTATE_READ_23 (23U)

#define FLS_17_DMU_WAITSTATE_READ_24 (24U)

#define FLS_17_DMU_WAITSTATE_READ_25 (25U)

#define FLS_17_DMU_WAITSTATE_READ_26 (26U)

#define FLS_17_DMU_WAITSTATE_READ_27 (27U)

#define FLS_17_DMU_WAITSTATE_READ_28 (28U)

#define FLS_17_DMU_WAITSTATE_READ_29 (29U)

#define FLS_17_DMU_WAITSTATE_READ_30 (30U)

#define FLS_17_DMU_WAITSTATE_READ_31 (31U)

#define FLS_17_DMU_WAITSTATE_READ_32 (32U)

#define FLS_17_DMU_WAITSTATE_READ_33 (33U)

#define FLS_17_DMU_WAITSTATE_READ_34 (34U)

#define FLS_17_DMU_WAITSTATE_READ_35 (35U)

#define FLS_17_DMU_WAITSTATE_READ_36 (36U)

#define FLS_17_DMU_WAITSTATE_READ_37 (37U)

#define FLS_17_DMU_WAITSTATE_READ_38 (38U)

#define FLS_17_DMU_WAITSTATE_READ_39 (39U)

#define FLS_17_DMU_WAITSTATE_READ_40 (40U)

#define FLS_17_DMU_WAITSTATE_READ_41 (41U)

#define FLS_17_DMU_WAITSTATE_READ_42 (42U)

#define FLS_17_DMU_WAITSTATE_READ_43 (43U)

#define FLS_17_DMU_WAITSTATE_READ_44 (44U)

#define FLS_17_DMU_WAITSTATE_READ_45 (45U)

#define FLS_17_DMU_WAITSTATE_READ_46 (46U)

#define FLS_17_DMU_WAITSTATE_READ_47 (47U)

#define FLS_17_DMU_WAITSTATE_READ_48 (48U)

#define FLS_17_DMU_WAITSTATE_READ_49 (49U)

#define FLS_17_DMU_WAITSTATE_READ_50 (50U)

#define FLS_17_DMU_WAITSTATE_READ_51 (51U)

#define FLS_17_DMU_WAITSTATE_READ_52 (52U)

#define FLS_17_DMU_WAITSTATE_READ_53 (53U)

#define FLS_17_DMU_WAITSTATE_READ_54 (54U)

#define FLS_17_DMU_WAITSTATE_READ_55 (55U)

#define FLS_17_DMU_WAITSTATE_READ_56 (56U)

#define FLS_17_DMU_WAITSTATE_READ_57 (57U)

#define FLS_17_DMU_WAITSTATE_READ_58 (58U)

#define FLS_17_DMU_WAITSTATE_READ_59 (59U)

#define FLS_17_DMU_WAITSTATE_READ_60 (60U)

#define FLS_17_DMU_WAITSTATE_READ_61 (61U)

#define FLS_17_DMU_WAITSTATE_READ_62 (62U)

#define FLS_17_DMU_WAITSTATE_READ_63 (63U)

#define FLS_17_DMU_WAITSTATE_READ_64 (64U)

#define FLS_17_DMU_WAITSTATE_READ_65 (65U)

#define FLS_17_DMU_WAITSTATE_READ_66 (66U)

#define FLS_17_DMU_WAITSTATE_READ_67 (67U)

#define FLS_17_DMU_WAITSTATE_READ_68 (68U)

#define FLS_17_DMU_WAITSTATE_READ_69 (69U)

#define FLS_17_DMU_WAITSTATE_READ_70 (70U)

#define FLS_17_DMU_WAITSTATE_READ_71 (71U)

#define FLS_17_DMU_WAITSTATE_READ_72 (72U)

#define FLS_17_DMU_WAITSTATE_READ_73 (73U)

#define FLS_17_DMU_WAITSTATE_READ_74 (74U)

#define FLS_17_DMU_WAITSTATE_READ_75 (75U)

#define FLS_17_DMU_WAITSTATE_READ_76 (76U)

#define FLS_17_DMU_WAITSTATE_READ_77 (77U)

#define FLS_17_DMU_WAITSTATE_READ_78 (78U)

#define FLS_17_DMU_WAITSTATE_READ_79 (79U)

#define FLS_17_DMU_WAITSTATE_READ_80 (80U)

#define FLS_17_DMU_WAITSTATE_READ_81 (81U)

#define FLS_17_DMU_WAITSTATE_READ_82 (82U)

#define FLS_17_DMU_WAITSTATE_READ_83 (83U)

#define FLS_17_DMU_WAITSTATE_READ_84 (84U)

#define FLS_17_DMU_WAITSTATE_READ_85 (85U)

#define FLS_17_DMU_WAITSTATE_READ_86 (86U)

#define FLS_17_DMU_WAITSTATE_READ_87 (87U)

#define FLS_17_DMU_WAITSTATE_READ_88 (88U)

#define FLS_17_DMU_WAITSTATE_READ_89 (89U)

#define FLS_17_DMU_WAITSTATE_READ_90 (90U)

#define FLS_17_DMU_WAITSTATE_READ_91 (91U)

#define FLS_17_DMU_WAITSTATE_READ_92 (92U)

#define FLS_17_DMU_WAITSTATE_READ_93 (93U)

#define FLS_17_DMU_WAITSTATE_READ_94 (94U)

#define FLS_17_DMU_WAITSTATE_READ_95 (95U)

#define FLS_17_DMU_WAITSTATE_READ_96 (96U)

#define FLS_17_DMU_WAITSTATE_READ_97 (97U)

#define FLS_17_DMU_WAITSTATE_READ_98 (98U)

#define FLS_17_DMU_WAITSTATE_READ_99 (99U)

#define FLS_17_DMU_WAITSTATE_READ_100 (100U)

#define FLS_17_DMU_WAITSTATE_READ_101 (101U)

#define FLS_17_DMU_WAITSTATE_READ_102 (102U)

#define FLS_17_DMU_WAITSTATE_READ_103 (103U)

#define FLS_17_DMU_WAITSTATE_READ_104 (104U)

#define FLS_17_DMU_WAITSTATE_READ_105 (105U)

#define FLS_17_DMU_WAITSTATE_READ_106 (106U)

#define FLS_17_DMU_WAITSTATE_READ_107 (107U)

#define FLS_17_DMU_WAITSTATE_READ_108 (108U)

#define FLS_17_DMU_WAITSTATE_READ_109 (109U)

#define FLS_17_DMU_WAITSTATE_READ_110 (110U)

#define FLS_17_DMU_WAITSTATE_READ_111 (111U)

#define FLS_17_DMU_WAITSTATE_READ_112 (112U)

#define FLS_17_DMU_WAITSTATE_READ_113 (113U)

#define FLS_17_DMU_WAITSTATE_READ_114 (114U)

#define FLS_17_DMU_WAITSTATE_READ_115 (115U)

#define FLS_17_DMU_WAITSTATE_READ_116 (116U)

#define FLS_17_DMU_WAITSTATE_READ_117 (117U)

#define FLS_17_DMU_WAITSTATE_READ_118 (118U)

#define FLS_17_DMU_WAITSTATE_READ_119 (119U)

#define FLS_17_DMU_WAITSTATE_READ_120 (120U)

#define FLS_17_DMU_WAITSTATE_READ_121 (121U)

#define FLS_17_DMU_WAITSTATE_READ_122 (122U)

#define FLS_17_DMU_WAITSTATE_READ_123 (123U)

#define FLS_17_DMU_WAITSTATE_READ_124 (124U)

#define FLS_17_DMU_WAITSTATE_READ_125 (125U)

#define FLS_17_DMU_WAITSTATE_READ_126 (126U)

#define FLS_17_DMU_WAITSTATE_READ_127 (127U)

#define FLS_17_DMU_WAITSTATE_READ_128 (128U)

#define FLS_17_DMU_WAITSTATE_READ_129 (129U)

#define FLS_17_DMU_WAITSTATE_READ_130 (130U)

#define FLS_17_DMU_WAITSTATE_READ_131 (131U)

#define FLS_17_DMU_WAITSTATE_READ_132 (132U)

#define FLS_17_DMU_WAITSTATE_READ_133 (133U)

#define FLS_17_DMU_WAITSTATE_READ_134 (134U)

#define FLS_17_DMU_WAITSTATE_READ_135 (135U)

#define FLS_17_DMU_WAITSTATE_READ_136 (136U)

#define FLS_17_DMU_WAITSTATE_READ_137 (137U)

#define FLS_17_DMU_WAITSTATE_READ_138 (138U)

#define FLS_17_DMU_WAITSTATE_READ_139 (139U)

#define FLS_17_DMU_WAITSTATE_READ_140 (140U)

#define FLS_17_DMU_WAITSTATE_READ_141 (141U)

#define FLS_17_DMU_WAITSTATE_READ_142 (142U)

#define FLS_17_DMU_WAITSTATE_READ_143 (143U)

#define FLS_17_DMU_WAITSTATE_READ_144 (144U)

#define FLS_17_DMU_WAITSTATE_READ_145 (145U)

#define FLS_17_DMU_WAITSTATE_READ_146 (146U)

#define FLS_17_DMU_WAITSTATE_READ_147 (147U)

#define FLS_17_DMU_WAITSTATE_READ_148 (148U)

#define FLS_17_DMU_WAITSTATE_READ_149 (149U)

#define FLS_17_DMU_WAITSTATE_READ_150 (150U)

#define FLS_17_DMU_WAITSTATE_READ_151 (151U)

#define FLS_17_DMU_WAITSTATE_READ_152 (152U)

#define FLS_17_DMU_WAITSTATE_READ_153 (153U)

#define FLS_17_DMU_WAITSTATE_READ_154 (154U)

#define FLS_17_DMU_WAITSTATE_READ_155 (155U)

#define FLS_17_DMU_WAITSTATE_READ_156 (156U)

#define FLS_17_DMU_WAITSTATE_READ_157 (157U)

#define FLS_17_DMU_WAITSTATE_READ_158 (158U)

#define FLS_17_DMU_WAITSTATE_READ_159 (159U)

#define FLS_17_DMU_WAITSTATE_READ_160 (160U)

#define FLS_17_DMU_WAITSTATE_READ_161 (161U)

#define FLS_17_DMU_WAITSTATE_READ_162 (162U)

#define FLS_17_DMU_WAITSTATE_READ_163 (163U)

#define FLS_17_DMU_WAITSTATE_READ_164 (164U)

#define FLS_17_DMU_WAITSTATE_READ_165 (165U)

#define FLS_17_DMU_WAITSTATE_READ_166 (166U)

#define FLS_17_DMU_WAITSTATE_READ_167 (167U)

#define FLS_17_DMU_WAITSTATE_READ_168 (168U)

#define FLS_17_DMU_WAITSTATE_READ_169 (169U)

#define FLS_17_DMU_WAITSTATE_READ_170 (170U)

#define FLS_17_DMU_WAITSTATE_READ_171 (171U)

#define FLS_17_DMU_WAITSTATE_READ_172 (172U)

#define FLS_17_DMU_WAITSTATE_READ_173 (173U)

#define FLS_17_DMU_WAITSTATE_READ_174 (174U)

#define FLS_17_DMU_WAITSTATE_READ_175 (175U)

#define FLS_17_DMU_WAITSTATE_READ_176 (176U)

#define FLS_17_DMU_WAITSTATE_READ_177 (177U)

#define FLS_17_DMU_WAITSTATE_READ_178 (178U)

#define FLS_17_DMU_WAITSTATE_READ_179 (179U)

#define FLS_17_DMU_WAITSTATE_READ_180 (180U)

#define FLS_17_DMU_WAITSTATE_READ_181 (181U)

#define FLS_17_DMU_WAITSTATE_READ_182 (182U)

#define FLS_17_DMU_WAITSTATE_READ_183 (183U)

#define FLS_17_DMU_WAITSTATE_READ_184 (184U)

#define FLS_17_DMU_WAITSTATE_READ_185 (185U)

#define FLS_17_DMU_WAITSTATE_READ_186 (186U)

#define FLS_17_DMU_WAITSTATE_READ_187 (187U)

#define FLS_17_DMU_WAITSTATE_READ_188 (188U)

#define FLS_17_DMU_WAITSTATE_READ_189 (189U)

#define FLS_17_DMU_WAITSTATE_READ_190 (190U)

#define FLS_17_DMU_WAITSTATE_READ_191 (191U)

#define FLS_17_DMU_WAITSTATE_READ_192 (192U)

#define FLS_17_DMU_WAITSTATE_READ_193 (193U)

#define FLS_17_DMU_WAITSTATE_READ_194 (194U)

#define FLS_17_DMU_WAITSTATE_READ_195 (195U)

#define FLS_17_DMU_WAITSTATE_READ_196 (196U)

#define FLS_17_DMU_WAITSTATE_READ_197 (197U)

#define FLS_17_DMU_WAITSTATE_READ_198 (198U)

#define FLS_17_DMU_WAITSTATE_READ_199 (199U)

#define FLS_17_DMU_WAITSTATE_READ_200 (200U)

#define FLS_17_DMU_WAITSTATE_READ_201 (201U)

#define FLS_17_DMU_WAITSTATE_READ_202 (202U)

#define FLS_17_DMU_WAITSTATE_READ_203 (203U)

#define FLS_17_DMU_WAITSTATE_READ_204 (204U)

#define FLS_17_DMU_WAITSTATE_READ_205 (205U)

#define FLS_17_DMU_WAITSTATE_READ_206 (206U)

#define FLS_17_DMU_WAITSTATE_READ_207 (207U)

#define FLS_17_DMU_WAITSTATE_READ_208 (208U)

#define FLS_17_DMU_WAITSTATE_READ_209 (209U)

#define FLS_17_DMU_WAITSTATE_READ_210 (210U)

#define FLS_17_DMU_WAITSTATE_READ_211 (211U)

#define FLS_17_DMU_WAITSTATE_READ_212 (212U)

#define FLS_17_DMU_WAITSTATE_READ_213 (213U)

#define FLS_17_DMU_WAITSTATE_READ_214 (214U)

#define FLS_17_DMU_WAITSTATE_READ_215 (215U)

#define FLS_17_DMU_WAITSTATE_READ_216 (216U)

#define FLS_17_DMU_WAITSTATE_READ_217 (217U)

#define FLS_17_DMU_WAITSTATE_READ_218 (218U)

#define FLS_17_DMU_WAITSTATE_READ_219 (219U)

#define FLS_17_DMU_WAITSTATE_READ_220 (220U)

#define FLS_17_DMU_WAITSTATE_READ_221 (221U)

#define FLS_17_DMU_WAITSTATE_READ_222 (222U)

#define FLS_17_DMU_WAITSTATE_READ_223 (223U)

#define FLS_17_DMU_WAITSTATE_READ_224 (224U)

#define FLS_17_DMU_WAITSTATE_READ_225 (225U)

#define FLS_17_DMU_WAITSTATE_READ_226 (226U)

#define FLS_17_DMU_WAITSTATE_READ_227 (227U)

#define FLS_17_DMU_WAITSTATE_READ_228 (228U)

#define FLS_17_DMU_WAITSTATE_READ_229 (229U)

#define FLS_17_DMU_WAITSTATE_READ_230 (230U)

#define FLS_17_DMU_WAITSTATE_READ_231 (231U)

#define FLS_17_DMU_WAITSTATE_READ_232 (232U)

#define FLS_17_DMU_WAITSTATE_READ_233 (233U)

#define FLS_17_DMU_WAITSTATE_READ_234 (234U)

#define FLS_17_DMU_WAITSTATE_READ_235 (235U)

#define FLS_17_DMU_WAITSTATE_READ_236 (236U)

#define FLS_17_DMU_WAITSTATE_READ_237 (237U)

#define FLS_17_DMU_WAITSTATE_READ_238 (238U)

#define FLS_17_DMU_WAITSTATE_READ_239 (239U)

#define FLS_17_DMU_WAITSTATE_READ_240 (240U)

#define FLS_17_DMU_WAITSTATE_READ_241 (241U)

#define FLS_17_DMU_WAITSTATE_READ_242 (242U)

#define FLS_17_DMU_WAITSTATE_READ_243 (243U)

#define FLS_17_DMU_WAITSTATE_READ_244 (244U)

#define FLS_17_DMU_WAITSTATE_READ_245 (245U)

#define FLS_17_DMU_WAITSTATE_READ_246 (246U)

#define FLS_17_DMU_WAITSTATE_READ_247 (247U)

#define FLS_17_DMU_WAITSTATE_READ_248 (248U)

#define FLS_17_DMU_WAITSTATE_READ_249 (249U)

#define FLS_17_DMU_WAITSTATE_READ_250 (250U)

#define FLS_17_DMU_WAITSTATE_READ_251 (251U)

#define FLS_17_DMU_WAITSTATE_READ_252 (252U)

#define FLS_17_DMU_WAITSTATE_READ_253 (253U)

#define FLS_17_DMU_WAITSTATE_READ_254 (254U)

#define FLS_17_DMU_WAITSTATE_READ_255 (255U)

/* Options for DFLS Error Correction Wait States */

#define FLS_17_DMU_WAITSTATE_ERRCOREC_0 (0U)

#define FLS_17_DMU_WAITSTATE_ERRCOREC_1 (1U)

#define FLS_17_DMU_WAITSTATE_ERRCOREC_2 (2U)

#define FLS_17_DMU_WAITSTATE_ERRCOREC_3 (3U)

#define FLS_17_DMU_WAITSTATE_ERRCOREC_4 (4U)

#define FLS_17_DMU_WAITSTATE_ERRCOREC_5 (5U)

#define FLS_17_DMU_WAITSTATE_ERRCOREC_6 (6U)

#define FLS_17_DMU_WAITSTATE_ERRCOREC_7 (7U)


/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/* [cover parentID={AEBC6EE4-722B-471c-BCA8-756866BF1671}] */
typedef uint32 Fls_17_Dmu_AddressType;
/*  [/cover] */

/* [cover parentID={C99A4CBA-743A-4fc6-A260-F8699A0BF36A}] */
typedef uint32 Fls_17_Dmu_LengthType;
/*  [/cover] */
/* [cover parentID={7CC7EAC9-39DA-4e13-AFF9-BF2FE8484521}][/cover]*/
typedef struct
{
  unsigned_int Reserved1 : 1;

  unsigned_int Write     : 1;

  unsigned_int Erase     : 1;

  unsigned_int Read      : 1;

  unsigned_int Compare   : 1;

  unsigned_int Reserved2 : 3;
} Fls_17_Dmu_JobStartType;

/* Return values of the function Fls_17_Dmu_GetNotifCaller */
/* [cover parentID={6797898F-5651-46a0-944A-B2F3BE377F23}][/cover] */
/* [cover parentID={1AE3AA55-AC0E-4f57-9FDF-60AB99C40E54}][/cover] */
/* [cover parentID={1AE3AA55-AC0E-4f57-9FDF-60AB99C40E54}][/cover] */
typedef uint8 Fls_17_Dmu_Job_Type;
/* [cover parentID={60B2F68B-08A5-4029-916D-03293423BF65}][/cover] */
typedef uint8 Fls_17_Dmu_HardenType;

#define FLS_17_DMU_NO_JOB        ((Fls_17_Dmu_Job_Type)FLS_17_DMU_NONE)
#define FLS_17_DMU_WRITE_JOB     ((Fls_17_Dmu_Job_Type)FLS_17_DMU_WRITE)
#define FLS_17_DMU_ERASE_JOB     ((Fls_17_Dmu_Job_Type)FLS_17_DMU_ERASE)
#define FLS_17_DMU_READ_JOB      ((Fls_17_Dmu_Job_Type)FLS_17_DMU_READ)
#define FLS_17_DMU_COMPARE_JOB   ((Fls_17_Dmu_Job_Type)FLS_17_DMU_COMPARE)
#define FLS_17_DMU_READSYNC_JOB  ((Fls_17_Dmu_Job_Type)FLS_17_DMU_READSYNC)
#define FLS_17_DMU_CANCEL_JOB    ((Fls_17_Dmu_Job_Type)FLS_17_DMU_CANCEL)
#define FLS_17_DMU_BLANKCHECK_JOB   ((Fls_17_Dmu_Job_Type)FLS_17_DMU_BLANKCHECK)

/* [cover parentID={521A2761-98D4-4d2f-BEA2-CD9EFC8D051C}][/cover] */
typedef struct
{
  /* Source address for read job,
    destination aage address for write job,
    DFLASH physical address for erase job */
  uint32 FlsReadAddress;
  uint32 FlsWriteAddress;
  uint32 FlsEraseAddress;

  /* Erase and Write Timeout Cycle Count */
  #if (FLS_17_DMU_TIMEOUT_SUPERVISION == STD_ON)
  uint32 FlsCmdStartTicks;
  uint32 FlsEraseCmdTimeoutTicks;
  uint32 FlsWriteCmdTimeoutTicks;
  #endif

  /* Number of bytes to read or write */
  Fls_17_Dmu_LengthType FlsReadLength;
  Fls_17_Dmu_LengthType FlsWriteLength;

  /* Destination pointer for read job and
     source pointer for write job */
  uint8* FlsReadBufferPtr;
  const uint8* FlsWriteBufferPtr;

  /* Variable used to store Job Result of the Flash */
  MemIf_JobResultType FlsJobResult;

  /* FLS Mode - Fast or Slow */
  MemIf_ModeType FlsMode;

  /* Job type for which notification was raised */
  Fls_17_Dmu_Job_Type NotifCaller;

  /* Status to indicate if the job has been started */
  Fls_17_Dmu_JobStartType JobStarted;

  /* Number of sectors to be erased */
  uint16 FlsEraseNumSectors;
  /* Number of sectors to be erased in 1 command cycle */
  uint8 FlsEraseNumSecPerCmd;
  /* Status of current jobtype */
  Fls_17_Dmu_Job_Type FlsJobType;

  /* PVER error status */
  #if(FLS_17_DMU_IFX_FEE_USED == STD_ON)
  uint8 FlsPver;
  #endif

  /*EVER error status*/
  uint8 FlsEver;

  /* Command Sequence Timeout Error Status */
  uint8 FlsTimeoutErr;

  #if (FLS_17_DMU_ECC_ERROR_INFO_API == STD_ON)
  uint32 FlsEccErrorPageAddress;
  #endif
} Fls_17_Dmu_StateType;

/*
Type:Fls_17_Dmu_NotifFunctionPtrType
Function pointer for JobEnd and JobError Notification
*/
typedef void (*Fls_17_Dmu_NotifFunctionPtrType)(void);

/*
  This is the type of Flash external data structure containing
  the overall initialization data for the Flash Driver
*/
/* [cover parentID={5A6BA16E-9635-4713-B7C6-06F2DE9AB50E}]
  [/cover] */
typedef struct
{
  Fls_17_Dmu_StateType   *FlsStateVarPtr;

  /* FLS_MAX_READ, Maximum number of bytes to Read in one cycle of FLS driver
    job processing */
  Fls_17_Dmu_LengthType FlsFastRead;
  Fls_17_Dmu_LengthType FlsSlowRead;
  /* Funtion pointer for JobEndNotification.*/
  Fls_17_Dmu_NotifFunctionPtrType FlsJobEndNotificationPtr;

  /* Funtion pointer for JobErrorNotification. */
  Fls_17_Dmu_NotifFunctionPtrType FlsJobErrorNotificationPtr;

  /* Funtion pointer for EVER ErrorNotification. */
  Fls_17_Dmu_NotifFunctionPtrType FlsEraseVerifyErrNotifPtr;

  /* Funtion pointer for PVER ErrorNotification. */
  Fls_17_Dmu_NotifFunctionPtrType FlsProgVerifyErrNotifPtr;

  /* Funtion pointer for Illegal State Notification */
  Fls_17_Dmu_NotifFunctionPtrType FlsIllegalStateNotificationPtr;

  /* Wait state configuration for Read access and error correction */
  uint32 FlsWaitStates;

  /* FLS call cycle */
  #if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) ||                 \
      (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  uint32 FlsCallCycle;
  #endif

  /* Default mode of FLS Driver */
  MemIf_ModeType FlsDefaultMode;

} Fls_17_Dmu_ConfigType;
/* [cover parentID={8D832E9B-AF58-4d48-8C2F-241BE30E65E2}][/cover] */
/*   Typedefs for FLS INIT API to be used by MEMIF module */
typedef void (*Fls_Init_Type)(const Fls_17_Dmu_ConfigType* ConfigPtr);


/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/




/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_START_SEC_CODE_ASIL_B_LOCAL
#include "Fls_17_Dmu_MemMap.h"

/*******************************************************************************
**                                                                            **
** Syntax : void Fls_17_Dmu_Init(const Fls_17_Dmu_ConfigType*const ConfigPtr) **
**                                                                            **
** Service ID:  0x00                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  ConfigPtr - Pointer to configuration set                **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : Driver Module Initialization function                        **
** Service for FLASH initialization. The Initialization function shall        **
** initialize all Flash relevant registers with the values of the structure   **
** referenced by the parameter ConfigPtr.                                     **
**                                                                            **
*******************************************************************************/
extern void Fls_17_Dmu_Init(const Fls_17_Dmu_ConfigType*const ConfigPtr);

#if (FLS_17_DMU_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Syntax : void Fls_17_Dmu_GetVersionInfo(                                   **
**                                  Std_VersionInfoType *const VersioninfoPtr)**
**                                                                            **
** Service ID:     0x10                                                       **
**                                                                            **
** Sync/Async:      Synchronous                                               **
**                                                                            **
** Reentrancy:      reentrant                                                 **
**                                                                            **
** Parameters (in): VersioninfoPtr : Pointer to where to store the version    **
**                                   information of this module.              **
**                                                                            **
** Parameters (out):none                                                      **
**                                                                            **
** Return value:    none                                                      **
**                                                                            **
** Description :    This service returns the version information of           **
**                  this module.                                              **
**                  The version information includes:                         **
**                  Module Id,Vendor Id , Vendor specific version numbers     **
**                                                                            **
*******************************************************************************/
extern void Fls_17_Dmu_GetVersionInfo
                               (Std_VersionInfoType* const VersionInfoPtr);

#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_GetVersionInfo(VersioninfoPtr) \
                      ((ERROR_Fls_17_Dmu_GetVersionInfo_API_IS_NOT_SELECTED))

#endif/*(FLS_VERSION_INFO_API == STD_ON)*/

/*******************************************************************************
** Syntax : Std_ReturnType Fls_17_Dmu_Erase(                                  **
**                              const Fls_17_Dmu_AddressType TargetAddress,   **
**                              const Fls_17_Dmu_LengthType Length            **
**                                  )                                         **
**                                                                            **
** Service ID:  0x01                                                          **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  TargetAddress and Length                                **
**                                                                            **
** Parameters (out): E_OK: command has been accepted                          **
**                   E_NOT_OK: command has not been accepted                  **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This API Erases Flash. It copies the given parameters to     **
** driver internal variables, initiates the erase job, sets the driver status **
** to MEMIF_BUSY and job result to MEMIF_JOB_PENDING.                         **
*******************************************************************************/
extern Std_ReturnType Fls_17_Dmu_Erase(
                              const Fls_17_Dmu_AddressType TargetAddress,
                              const Fls_17_Dmu_LengthType Length
                               );


/*******************************************************************************
** Syntax : Std_ReturnType Fls_17_Dmu_Write(                                  **
**                                const Fls_17_Dmu_AddressType TargetAddress, **
**                                const uint8 *const SourceAddressPtr,        **
**                                const Fls_17_Dmu_LengthType Length          **
**                                  )                                         **
**                                                                            **
** Service ID:  0x02                                                          **
**                                                                            **
** Sync/Async:  ASynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :SourceAddressPtr,TargetAddress and Length                 **
**                                                                            **
** Parameters (out): E_OK: command has been accepted                          **
**                   E_NOT_OK: command has not been accepted                  **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : Writing to given flash address.                              **
** Service for writing one or more flash pages. This service copies the given **
** parameters to driver internal variables, initiate a Write job, set driver  **
** status to MEMIF_BUSY and job result to MEMIF_JOB_PENDING.                  **
*******************************************************************************/
extern Std_ReturnType Fls_17_Dmu_Write(
                                 const Fls_17_Dmu_AddressType TargetAddress,
                                 const uint8 *const SourceAddressPtr,
                                 const Fls_17_Dmu_LengthType Length
                                  );


#if (FLS_17_DMU_COMPARE_API == STD_ON)
/*******************************************************************************
** Syntax : Std_ReturnType Fls_17_Dmu_Compare(                                **
**                                      const Fls_AddressType SourceAddress,  **
**                                      const uint8 *const TargetAddressPtr,  **
**                                   const Fls_LengthType Length              **
**                                    )                                       **
**                                                                            **
** Service ID:  0x08                                                          **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :SourceAddress, TargetAddressPtr and Length                **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: command has been accepted                         **
**                    E_NOT_OK: command has not been accepted                 **
**                                                                            **
** Description : Service for comparing the contents of an area of flash memory**
** with that of an application data buffer. This service shall copy the given **
** parameters to driver internal variables, initiate a compare job, set the   **
** driver status to MEMIF_BUSY, set the job result to MEMIF_JOB_PENDING       **
** and return with E_OK.                                                      **
*******************************************************************************/
extern Std_ReturnType Fls_17_Dmu_Compare(
                            const Fls_17_Dmu_AddressType SourceAddress,
                            const uint8 *const TargetAddressPtr,
                            const Fls_17_Dmu_LengthType Length
                            );
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_Compare( SourceAddress, \
                     TargetAddressPtr, \
                     Length          \
                   )                 \
((ERROR_Fls_17_Dmu_Compare_API_IS_NOT_SELECTED))

#endif

#if (FLS_17_DMU_BLANK_CHECK_API == STD_ON)
/*******************************************************************************
** Syntax : Std_ReturnType Fls_17_Dmu_BlankCheck(                             **
**                                const Fls_17_Dmu_AddressType TargetAddress  **
**                                const  Fls_17_Dmu_LengthType Length         **
**                                    )                                       **
**                                                                            **
** Service ID:  0x0A                                                          **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :TargetAddress and Length                                  **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: command has been accepted                         **
**                    E_NOT_OK: command has not been accepted                 **
**                                                                            **
** Description : This API is a Service is to verify, whether a given memory   **
** area has been erased but not (yet) programmed.                             **
*******************************************************************************/
extern Std_ReturnType Fls_17_Dmu_BlankCheck(
                                    const Fls_17_Dmu_AddressType TargetAddress,
                                    const Fls_17_Dmu_LengthType Length
                                     );

#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_BlankCheck(TargetAddress,\
                             Length \
                           )\
(ERROR_Fls_17_Dmu_BlankCheck_API_IS_NOT_SELECTED)
#endif

#if  (FLS_17_DMU_CANCEL_API  ==  STD_ON)
/*******************************************************************************
** Syntax : void Fls_17_Dmu_Cancel(Void)                                      **
**                                                                            **
** Service ID:  0x03                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description :                                                              **
** Service for Canceling an ongoing flash job.                                **
** Read and Compare jobs will be cancelled immediately. Write and Erase jobs  **
** will be cancelled in driver immediately but hardware might still be busy   **
** until the ongoing operation is completed for the already issued commands   **
*******************************************************************************/
extern void Fls_17_Dmu_Cancel(void);

#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_Cancel(void) \
(ERROR_Fls_17_Dmu_Cancel_API_IS_NOT_SELECTED)

#endif

#if  (FLS_17_DMU_ECC_ERROR_INFO_API  ==  STD_ON)
/******************************************************************************
** Syntax : Std_ReturnType  Fls_17_Dmu_GetEccErrorPageAddress(               **
**                                            uint32 * const PageAddressPtr) **
**                                                                           **
** Service ID:  0x2E                                                         **
**                                                                           **
** Sync/Async:  Synchronous                                                  **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) :  None                                                   **
**                                                                           **
** Parameters (out):  PageAddress - Pointer to store the last ECC error      **
**                                  occurred page address                    **
**                                                                           **
** Return value    :  None                                                   **
**                                                                           **
** Description :                                                             **
** Service to get the address of the flash page where last ECC error is      **
** detected.If there is no ECC error detected in the current power cycle,then**
** the value of PageAddress parameter will be 0xFFFFFFFF.                    **
******************************************************************************/
extern Std_ReturnType Fls_17_Dmu_GetEccErrorPageAddress(
                                                 uint32 * const PageAddressPtr
                                                       );

#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_GetEccErrorPageAddress(PageAddress) \
(ERROR_Fls_17_Dmu_GetEccErrorPageAddress_API_IS_NOT_SELECTED)

#endif

#if(FLS_17_DMU_IFX_FEE_USED == STD_ON)
/*******************************************************************************
** Syntax : void Fls_17_Dmu_CancelNonEraseJobs(void)                          **
**                                                                            **
** Service ID: 0x28                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description :                                                              **
** Service for Canceling an ongoing flash jobs except the erase job.          **
** Read and Compare jobs will be cancelled immediately. Write job             **
** will be cancelled in driver immediately but hardware might still be busy   **
** until the ongoing operation is completed for the already issued commands   **
*******************************************************************************/
extern void Fls_17_Dmu_CancelNonEraseJobs(void);

#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_CancelNonEraseJobs() \
     (ERROR_Fls_17_Dmu_CancelNonEraseJobs_API_IS_NOT_SELECTED)
#endif

#if  (FLS_17_DMU_GET_STATUS_API  ==  STD_ON)
/*******************************************************************************
** Syntax : MemIf_StatusType Fls_17_Dmu_GetStatus(void)                       **
**                                                                            **
** Service ID:  0x04                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Re-entrant                                                    **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out): : None                                                   **
**                                                                            **
** Return value    :  MemIf_StatusType                                        **
**                                                                            **
** Description :                                                              **
**         This service shall return the driver state synchronously           **
*******************************************************************************/
extern MemIf_StatusType Fls_17_Dmu_GetStatus(void);

#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_GetStatus() \
(ERROR_Fls_17_Dmu_GetStatus_API_IS_NOT_SELECTED)

#endif

#if (FLS_17_DMU_GET_JOB_RESULT_API  ==  STD_ON)
/*******************************************************************************
** Syntax : MemIf_JobResultType Fls_17_Dmu_GetJobResult(void)                 **
**                                                                            **
** Service ID:  0x05                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Re-entrant                                                    **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out): : None                                                   **
**                                                                            **
** Return value    :  MemIf_JobResultType                                     **
**                                                                            **
** Description :                                                              **
**         This service shall return the result of the last job synchronously **
*******************************************************************************/
extern MemIf_JobResultType Fls_17_Dmu_GetJobResult(void);

#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_GetJobResult() \
(ERROR_Fls_17_Dmu_GetJobResult_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
** Syntax : void Fls_17_Dmu_SetMode(MemIf_ModeType Mode)                      **
**                                                                            **
** Service ID:  0x09                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : Mode MEMIF_MODE_SLOW:                                    **
**                        Slow read access                                    **
**                                                                            **
**                        MEMIF_MODE_FAST:                                    **
**                        Fast read access                                    **
**                                                                            **
** Parameters (out): : None                                                   **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This API sets the Flash driver's operation mode.             **
**               FAST or SLOW mode impacts only Read/Compare operations.      **
**               Based on the currently active mode, the number of bytes to be**
**               read from Flash in each call of Fls_17_Dmu_MainFunction is   **
**               taken from the configuration                                 **
*******************************************************************************/
#if  (FLS_17_DMU_SET_MODE_API  ==  STD_ON)
extern void Fls_17_Dmu_SetMode(const MemIf_ModeType Mode);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_SetMode(Mode) \
(ERROR_Fls_17_Dmu_SetMode_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
** Syntax : Std_ReturnType Fls_17_Dmu_Read(                                   **
**                               const Fls_17_Dmu_AddressType SourceAddress,  **
**                                 uint8 *const TargetAddressPtr,             **
**                               const Fls_17_Dmu_LengthType Length           **
**                                 );                                         **
** Service ID:  0x07                                                          **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : SourceAddress,TargetAddressPtr and Length                **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: command has been accepted                         **
**                    E_NOT_OK: command has not been accepted                 **
**                                                                            **
** Description : Service for reading from flash memory. This service copies   **
** the given parameters to driver internal variables, set driver status to    **
** MEMIF_BUSY and job result to MEMIF_JOB_PENDING.                            **
*******************************************************************************/
extern Std_ReturnType Fls_17_Dmu_Read(
                                const Fls_17_Dmu_AddressType SourceAddress,
                                uint8 *const TargetAddressPtr,
                                const Fls_17_Dmu_LengthType Length
                               );


#if (FLS_17_DMU_IFX_FEE_USED == STD_ON)
/*******************************************************************************
** Syntax : Std_ReturnType Fls_17_Dmu_ReadWordsSync(                          **
                                   const Fls_17_Dmu_AddressType SourceAddress,**
**                                           uint32 *const TargetAddressPtr,  **
**                                       const uint32 Length                  **
**                                         );                                 **
**                                                                            **
** Service ID:  0x21                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : SourceAddress, TargetAddressPtr and Length               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: Read successful                                    **
**                   E_NOT_OK: HW busy or read failed with ECC error          **
**                                                                            **
** Description : Service for reading word data from flash bank synchronously  **
*******************************************************************************/
extern Std_ReturnType Fls_17_Dmu_ReadWordsSync
                              (const Fls_17_Dmu_AddressType SourceAddress,
                               uint32 *const TargetAddressPtr,
                               const uint32 Length
                               );

/*******************************************************************************
** Syntax : Fls_17_Dmu_Job_Type Fls_17_Dmu_GetNotifCaller(void)               **
**                                                                            **
** Service ID: 0x29                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description :                                                              **
** Ths function returns the FLS Job that raised the notification              **
*******************************************************************************/
extern Fls_17_Dmu_Job_Type Fls_17_Dmu_GetNotifCaller(void);

/*******************************************************************************
** Syntax:Std_ReturnType Fls_17_Dmu_CompareWordsSync(                         **
**                                 const Fls_17_Dmu_AddressType SourceAddress,**
**                                   const uint32 *const TargetAddressPtr,    **
**                                       const  uint32 Length);               **
**                                                                            **
** Service ID: 0x22                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : SourceAddress, TargetAddressPtr, Length                  **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: Compare successful                                 **
**                   E_NOT_OK: HW busy or compare failed or ECC error         **
**                                                                            **
** Description : Service for comparing data from flash bank synchronously     **
*******************************************************************************/
extern Std_ReturnType Fls_17_Dmu_CompareWordsSync(
                              const Fls_17_Dmu_AddressType SourceAddress,
                              const uint32 *const TargetAddressPtr,
                              const uint32 Length);

#if (FLS_17_DMU_IFX_NVM_PRESENT == STD_ON)
/*******************************************************************************
** Syntax : Std_ReturnType Fls_17_Dmu_VerifyErase(                            **
**                              const Fls_17_Dmu_AddressType TargetAddress,   **
**                                 uint32 * const UnerasedWordlineAddressPtr, **
**                                 uint8 * const UnerasedWordlineCountPtr );  **
**                                                                            **
**                                                                            **
** Service ID: 0x23                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : TargetAddress                                            **
**                                                                            **
** Parameters (out): UnerasedWordlineAddressPtr,UnerasedWordlineCountPtr      **
**                                                                            **
** Return value    :  E_OK: Erase verification successful                     **
**                    E_NOT_OK: HW busy or erase verification failed          **
**                                                                            **
** Description : Service for verifying erase of a sector                      **
*******************************************************************************/
extern Std_ReturnType Fls_17_Dmu_VerifyErase(
                                   const Fls_17_Dmu_AddressType TargetAddress,
                                   uint32 *const UnerasedWordlineAddressPtr,
                                   uint8 *const UnerasedWordlineCountPtr );

#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_VerifyErase(TargetAddress, UnerasedWordlineAddressPtr,  \
                                              UnerasedWordlineCountPtr) \
(ERROR_Fls_17_Dmu_VerifyErase_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
** Syntax : Std_ReturnType Fls_17_Dmu_VerifySectorErase(                      **
**                                 const Fls_17_Dmu_AddressType TargetAddress,**
**                                 uint32 * const UnerasedWordlineAddressPtr, **
**                                 uint8 * const UnerasedWordlineCountPtr,    **
**                                 const uint8 Sector);                       **
**                                                                            **
**                                                                            **
** Service ID: 0x24                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : TargetAddress, Sector                                    **
**                                                                            **
** Parameters (out): UnerasedWordlineAddressPtr,UnerasedWordlineCountPtr      **
**                                                                            **
** Return value    :  E_OK: Erase verification successful                     **
**                    E_NOT_OK: HW busy or erase verification failed          **
**                                                                            **
** Description : Service for verifying erase of a logical sector              **
*******************************************************************************/
extern Std_ReturnType Fls_17_Dmu_VerifySectorErase(
                                  const Fls_17_Dmu_AddressType TargetAddress,
                                  uint32 *const UnerasedWordlineAddressPtr,
                                  uint8 * const UnerasedWordlineCountPtr,
                                  const uint8 Sector);

#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_ReadWordsSync(SourceAddress,TargetAddressPtr,Length) \
(ERROR_Fls_17_Dmu_ReadWordsSync_API_IS_NOT_SELECTED)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_GetNotifCaller() \
(ERROR_Fls_17_Dmu_GetNotifCaller_API_IS_NOT_SELECTED)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_CompareWordsSync(SourceAddress,TargetAddressPtr,\
                                                        Length) \
(ERROR_Fls_17_Dmu_CompareWordsSync_API_IS_NOT_SELECTED)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_VerifySectorErase(TargetAddress, UnerasedWordlineAddressPtr, \
                                     UnerasedWordlineCountPtr,Sector) \
(ERROR_Fls_17_Dmu_VerifySectorErase_API_IS_NOT_SELECTED)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_VerifyErase(TargetAddress, UnerasedWordlineAddressPtr,  \
                                              UnerasedWordlineCountPtr) \
(ERROR_Fls_17_Dmu_VerifyErase_API_IS_NOT_SELECTED)

#endif /* #if (FLS_IFX_FEE_USED == STD_ON) */

#if (FLS_17_DMU_USE_ERASESUSPEND == STD_ON)
/*******************************************************************************
** Syntax : Std_ReturnType  Fls_17_Dmu_SuspendErase (void)                    **
**                                                                            **
** Service ID: 0x25                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  E_OK - Erase suspend successful                         **
**                    E_NOT_OK - Erase suspend failed                         **
**                                                                            **
** Description :                                                              **
** Ths function suspends an ongoing erase of a sector.                        **
*******************************************************************************/
extern Std_ReturnType Fls_17_Dmu_SuspendErase(void);

/*******************************************************************************
** Syntax : Std_ReturnType Fls_17_Dmu_ResumeErase (void)                      **
**                                                                            **
**                                                                            **
** Service ID: 0x26                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  E_OK - Erase suspend successful                         **
**                    E_NOT_OK - Erase suspend failed                         **
**                                                                            **
** Description :                                                              **
** Ths function suspends an ongoing erase of a sector.                        **
*******************************************************************************/
extern Std_ReturnType Fls_17_Dmu_ResumeErase (void);

#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_SuspendErase() \
(ERROR_Fls_17_Dmu_SuspendErase_API_IS_NOT_SELECTED)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_ResumeErase() \
(ERROR_Fls_17_Dmu_ResumeErase_API_IS_NOT_SELECTED)

#endif /* FLS_USE_ERASESUSPEND == STD_ON */

/*******************************************************************************
** Syntax : void Fls_17_Dmu_Isr(void)                                         **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : void                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : This routine is used instead of Main function if configured  **
** for Erase and Write Jobs.                                                  **
*******************************************************************************/
#if( FLS_17_DMU_USE_INTERRUPTS == STD_ON)

extern void Fls_17_Dmu_Isr(void);

#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_Isr() \
(ERROR_Fls_17_Dmu_Isr_API_IS_NOT_SELECTED)

#endif

/*******************************************************************************
** Syntax : Std_ReturnType Fls_17_Dmu_GetOperStatus(void)                     **
**                                                                            **
** Service ID: 0x2A                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  E_OK - No OPER error                                    **
**                    E_NOT_OK - OPER error has occured                       **
**                                                                            **
** Description : This function provides the OPER error status                 **
*******************************************************************************/
extern Std_ReturnType Fls_17_Dmu_GetOperStatus(void);

#if (FLS_17_DMU_IFX_FEE_USED == STD_ON)
/*******************************************************************************
** Syntax : Fls_17_Dmu_HardenType Fls_17_Dmu_IsHardeningRequired(             **
**                               const Fls_17_Dmu_AddressType TargetAddress   **
**                                                 const uint8 AlignChk)      **
**                                                                            **
** Service ID: 0x2C                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  TargetAddress                                           **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                                                                            **
** Description : The function checks whether the contents of memory at        **
                 requested wordline address needs hardening or not            **
*******************************************************************************/
extern Fls_17_Dmu_HardenType Fls_17_Dmu_IsHardeningRequired(
                                 const Fls_17_Dmu_AddressType TargetAddress,
                                 const uint8 AlignChk);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Fls_17_Dmu_IsHardeningRequired(TargetAddress, AlignChk) \
                     (ERROR_Fls_17_Dmu_IsHardeningRequired_API_IS_NOT_SELECTED)
#endif/*FLS_17_DMU_IFX_FEE_USED == STD_ON*/

#if (FLS_17_DMU_INITCHECK_API == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={FABE1515-678B-4067-9C75-7DBE5B2AB39C}]   **
**                                                                            **
** Syntax         : Std_ReturnType Fls_17_Dmu_InitCheck                       **
**                            (                                               **
**                             const Fls_17_Dmu_ConfigType *const ConfigPtr   **
**                            )                                               **
**                                                                            **
** Description    : This function verifies the initialization the GPT driver  **
**                  in context to the core from where the API is invoked.     **
**                                                                            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : 0x0E                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : None                                                      **
**                                                                            **
** Parameters(out): Fls                                                       **
**                                                                            **
** Return value   : E_OK     - Initialization comparison is success           **
**                  E_NOT_OK - Initialization comparison failed               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fls_17_Dmu_InitCheck(
                             const Fls_17_Dmu_ConfigType *const ConfigPtr);
/******************************************************************************/
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Fls_17_Dmu_InitCheck(ConfigPtr) (ERROR_Fls_17_Dmu_InitCheck_API_IS_NOT_SELECTED)
#endif
/* End of #if (FLS_INITCHECK_API == STD_ON) */


/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_STOP_SEC_CODE_ASIL_B_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. Even though the memmap
   header is included multiple times, the contents of the file are protected
   from multiple definition / inclusion. */
#include "Fls_17_Dmu_MemMap.h"

#include "Fls_17_Dmu_PBcfg.h"

#endif

