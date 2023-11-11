/*******************************************************************************
**                                                                            **
**  Copyright (C) Infineon Technologies (2023)                                **
**                                                                            **
**  All rights reserved.                                                      **
**                                                                            **
**  This document contains proprietary information belonging to Infineon      **
**  Technologies. Passing on and copying of this document, and communication  **
**  of its contents is not permitted without prior written authorization.     **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : Can_17_McmCan.c                                            **
**                                                                            **
**  VERSION      : 66.0.0                                                     **
**                                                                            **
**  DATE         : 2023-05-16                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID={75972939-822C-41cc-8B6A-327F181E274A}]    **
**                 [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]    **
**                 [cover parentID={C0E673D5-B80C-40f5-9944-70221E106146}]    **
**                 [cover parentID={6CE56ADD-37B9-4c96-BC08-609A206511DC}]    **
**                                                                            **
**  DESCRIPTION  : CAN Driver source file                                     **
**                                                                            **
**  SPECIFICATION(S) : Specification of Can Driver, AUTOSAR Release 4.2.2 and **
**                     4.4.0                                                  **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Include the declarations of Can functions and types */
#include "Can_17_McmCan.h"

/* Register definition file for Aurix2G target */
#include "IfxSrc_reg.h"

/* MCAL header file containing global macros, type definitions and functions
needed by all MCAL drivers */

#if (CAN_17_MCMCAN_INIT_DEINIT_API_MODE != CAN_17_MCMCAN_MCAL_SUPERVISOR)
#include "McalLib_OsStub.h"
#endif

/* Include the declarations of Can functions and types */
#include "SchM_Can_17_McmCan.h"

/* Include the declarations of CanIf callback functions and types */
#if (MCAL_AR_VERSION == MCAL_AR_422)
#include "CanIf_Cbk.h"
#else
#include "CanIf_Can.h"
#include "CanIf.h"
#endif /*#if (MCAL_AR_VERSION == MCAL_AR_422)*/

#if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON)
/* Include default error detection header file if DET is Enabled */
#include "Det.h"
#endif /*#if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON)*/

#if (CAN_17_MCMCAN_RUNTIME_ERROR_DETECT == STD_ON)
/* Include Mcal_Wrapper header file if runtime error is enabled*/
#include "Mcal_Wrapper.h"
#endif /*#if (CAN_17_MCMCAN_RUNTIME_ERROR_DETECT == STD_ON)*/

/*******************************************************************************
**                       Version check                                        **
*******************************************************************************/
/* [cover parentID={527E2B9D-7EFB-422d-A9BF-282FD3E78B84}]
[/cover] */
/* [cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}]
[/cover] */
/* Check if the correct version of Can_17_McmCan.h is included */
#ifndef CAN_17_MCMCAN_AR_RELEASE_MAJOR_VERSION
#error "CAN_17_MCMCAN_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#if (CAN_17_MCMCAN_AR_RELEASE_MAJOR_VERSION != 4U)
#error "CAN_17_MCMCAN_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

/* Check for definition of SW version Information */
#ifndef CAN_17_MCMCAN_SW_MAJOR_VERSION
#error "CAN_17_MCMCAN_SW_MAJOR_VERSION is not defined. "
#endif

#ifndef CAN_17_MCMCAN_SW_MINOR_VERSION
#error "CAN_17_MCMCAN_SW_MINOR_VERSION is not defined. "
#endif

#ifndef CAN_17_MCMCAN_SW_PATCH_VERSION
  #error "CAN_17_MCMCAN_SW_PATCH_VERSION is not defined. "
#endif

/* Check for Correct inclusion of headers */
#if (CAN_17_MCMCAN_SW_MAJOR_VERSION != 20U)
#error "CAN_17_MCMCAN_SW_MAJOR_VERSION does not match. "
#endif

#if (CAN_17_MCMCAN_SW_MINOR_VERSION != 25U)
#error "CAN_17_MCMCAN_SW_MINOR_VERSION does not match. "
#endif

#if (CAN_17_MCMCAN_SW_PATCH_VERSION != 0U)
  #error "CAN_17_MCMCAN_SW_PATCH_VERSION does not match. "
#endif

/*Check against AUTOSAR versions*/
#ifndef CAN_17_MCMCAN_AR_RELEASE_MAJOR_VERSION
#error "CAN_17_MCMCAN_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#if (CAN_17_MCMCAN_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION)
#error "CAN_17_MCMCAN_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

#ifndef CAN_17_MCMCAN_AR_RELEASE_MINOR_VERSION
#error "CAN_17_MCMCAN_AR_RELEASE_MINOR_VERSION is not defined. "
#endif

#if (CAN_17_MCMCAN_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION)
#error "CAN_17_MCMCAN_AR_RELEASE_MINOR_VERSION does not match. "
#endif

#ifndef CAN_17_MCMCAN_AR_RELEASE_REVISION_VERSION
#error "CAN_17_MCMCAN_AR_RELEASE_REVISION_VERSION is not defined. "
#endif

#if (CAN_17_MCMCAN_AR_RELEASE_REVISION_VERSION != \
     MCAL_AR_RELEASE_REVISION_VERSION)
#error "CAN_17_MCMCAN_AR_RELEASE_REVISION_VERSION does not match. "
#endif

/* Inter Module Check */

/* [cover parentID={A3DC8FC4-FD65-43c0-A540-925A1AC9702B}]
  Version check for DET
[/cover] */
/*
  VERSION CHECK FOR DET MODULE INCLUSION
*/


#if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON)

#ifndef DET_AR_RELEASE_MAJOR_VERSION
#error "DET_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#if (DET_AR_RELEASE_MAJOR_VERSION != CAN_17_MCMCAN_AR_RELEASE_MAJOR_VERSION)
#error "DET_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

#endif



/*******************************************************************************
**                       Private Macro Definitions                            **
*******************************************************************************/

/*Masks used in functions*/
/*Message RAM postion calculation mask*/
#define CAN_17_MCMCAN_MSGRAM_SHIFT_MASK                                (uint8)2U

/* Value for MASK the Message RAM Offset address */
#define CAN_17_MCMCAN_RAM_ADDRESS_OFFSET_MASK              (uint32) (0x0000FFFC)

/* value for Tx buffer Index */
#define CAN_17_MCMCAN_TX_BUFF_MASK                         (uint32)(0x00000001U)

/* value for New Data */
#define CAN_17_MCMCAN_NDATA_RESET_MASK                     (uint32)(0xFFFFFFFFU)

/* Set for identify the MsgID is extended */
#define CAN_17_MCMCAN_SET_XTD_BIT_MASK                     (uint32)(0x80000000U)

/* used for Mask value for identify the INIT */
#define CAN_17_MCMCAN_CCCR_CCE_SET_MASK                    (uint32)(0x00000003U)

/* Value used for enable the CLK configuration change */
#define CAN_17_MCMCAN_CLKSEL_WRITE_ENABLE_MASK             (uint32)(0xC0000000U)

/* Shift operation values used by the CAN driver */
#define CAN_17_MCMCAN_SHIFT_MSGRAM_RT_MASK                            (uint8)18U

/*To calculate the MCR clock values*/
#define CAN_17_MCMCAN_CLK_SHIFT_MASK                                (uint32)0x2U

/*Mask to check the timeout of INIT bit*/
#define CAN_17_MCMCAN_CCCR_INIT_SET_MASK                   (uint32)(0x00000001U)

/*Mask to check the timeout of remaining bits of CCCR register*/
#define CAN_17_MCMCAN_CCCR_RESET_MASK                      (uint32)(0xFFFFFFFCU)

#define CAN_17_MCMCAN_RAM_ADDRESS_SHIFT_MASK                          (uint32)2U

/* Values used for FD mask and Extended Id Mask */
#define CAN_17_MCMCAN_EXTENDED_ID_SET                      (uint32)(0x80000000U)
#define CAN_17_MCMCAN_EXTENDED_ID_MASK                     (uint32)(0x1FFFFFFFU)
#define CAN_17_MCMCAN_STANDARD_ID_MASK                     (uint32)(0x000007FFU)

/******************************************************************************/
/*Values and masks to be used in specific configurations*/
/*If interrupt or mixed processing is enabled*/
#if ((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON) || \
     (CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON) ||     \
    (CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON))
/* Interrupt flag check count */
#define CAN_17_MCMCAN_FLAG_CHECK_COUNT                                 (uint8)3U
#endif

/*FD enabled*/
#if (CAN_17_MCMCAN_FD_ENABLE == STD_ON)

/*Macros to evaluate the range of the PDU length*/

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_PDULENGTH_CHKVAL24                              (uint8)24U
#define CAN_17_MCMCAN_PDULENGTH_CHKVAL11                              (uint8)11U
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_PDULENGTH_CHKVAL15                              (uint8)15U
#define CAN_17_MCMCAN_PDULENGTH_CHKVAL4                                (uint8)4U
#define CAN_17_MCMCAN_PDULENGTH_CHKVAL3                                (uint8)3U
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_PDULENGTH_CHKVAL2                                (uint8)2U
#define CAN_17_MCMCAN_PDULENGTH_CHKVAL8                                (uint8)8U
#define CAN_17_MCMCAN_PDULENGTH_CHKVAL6                                (uint8)6U

/*Macro to check for FD DLC value*/
#define CAN_17_MCMCAN_FDDLC_VAL                                       (uint8)16U

/*Macro to check the FD PDU ID*/
#define CAN_17_MCMCAN_ID_FD_ENABLE_SET                     (uint32)(0x40000000U)

/* Value used for set the FD status for upper-layer */
#define CAN_17_MCMCAN_SET_FD_MASK                          (uint32)(0x40000000U)

/* Value used for Max FD length operation */
#define CAN_17_MCMCAN_MAX_FD_LENGTH                                   (uint8)64U

#define CAN_17_MCMCAN_CCCR_FDOE_STATUS                       (uint32)((uint32) \
                             IFX_CAN_N_CCCR_FDOE_MSK << IFX_CAN_N_CCCR_FDOE_OFF)

#define CAN_17_MCMCAN_CCCR_BRSE_STATUS                       (uint32)((uint32) \
                             IFX_CAN_N_CCCR_BRSE_MSK << IFX_CAN_N_CCCR_BRSE_OFF)
#endif

/*Check if multiperiod support is ON*/
#if ((CAN_17_MCMCAN_RX_MULTI_PERIODS_SUPPORT == STD_ON) || \
     (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON))
/*Macro for total number of HOH*/
#define CAN_17_MCMCAN_NO_HOH_VAL                                     (uint8)255U
#endif

/*Check if ICOM is enabled*/
#if (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON)
/* Message Id Mask Value */
#define CAN_17_MCMCAN_MSG_MASK                                         (uint8)0U

/*Macro for data length value*/
#define CAN_17_MCMCAN_DATALENTH_VAL                                    (uint8)8U

/*Macro to check fiter address*/
#define CAN_17_MCMCAN_FILTER_ADDR_VAL                                  (uint8)8U

/*RX dedicated EFEC mask*/
#define CAN_17_MCMCAN_RXDED_EFEC_MASK                                  (uint8)7U

/*RX FIFO EFEC mask*/
#define CAN_17_MCMCAN_FIFO_EFEC_MASK                                   (uint8)2U
#endif

#if ((CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON))

/* Clear TEFN (Tx Event FIFO New Entry) flag in IR register */
#define CAN_17_MCMCAN_CLEAR_IE_TEFN_BIT                   (uint32) (0x00001000U)

#endif /* #if (CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING == STD_ON) */
#if (CAN_17_MCMCAN_BO_INTERRUPT_PROCESSING == STD_ON)

/* Clear BO (Bus_Off Status) flag in IR register */
#define CAN_17_MCMCAN_CLEAR_IE_BO_BIT                     (uint32) (0x02000000U)

#endif

#if ((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON) ||     \
    (CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON) ||          \
    (CAN_17_MCMCAN_RX_MULTI_PERIODS_SUPPORT == STD_ON))

/* Clear RF1W,RF1F flag in IR register */
#define CAN_17_MCMCAN_CLEAR_IR_RF1_WF_BITS                (uint32) (0x00000060U)

/* Clear RF0W,RF0F flag in IR register */
#define CAN_17_MCMCAN_CLEAR_IR_RF0_WF_BITS                (uint32) (0x00000006U)

#endif /* #if ((CAN_17_MCMCAN_RX_MULTI_PERIODS_SUPPORT == STD_ON) || \
     (CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||             \
      (CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON)) */

/* Message RAM element size with FD support */
#if (CAN_17_MCMCAN_MULTIPLEXED_TRANSMISSION == STD_ON)

#define CAN_17_MCMCAN_TXSLOT_VAL                                           0xFFU

#endif

/*Values and masks used for AUTOSAR 4.4.0 specifically*/
#if (MCAL_AR_VERSION == MCAL_AR_440)

/*TX error count mask*/
#define CAN_17_MCMCAN_TXERRORCOUNTMASK                                     0xFFU

/*RX error count mask*/
#define CAN_17_MCMCAN_RXERRORCOUNTMASK                                   0x7F00U

/*RX error count mask*/
#define CAN_17_MCMCAN_RXERRORPASSIVEMASK                                 0x8000U

/*RX shift mask to retrive RX error passive bit*/
#define CAN_17_MCMCAN_RXERRORPASSIVE_OFFSET                                  15U

/*RX shift mask to retrive RX error counter*/
#define CAN_17_MCMCAN_RXERRORCNT_OFFSET                                       8U
#endif

/******************************************************************************/
/* General values used by the CAN driver */

/*Macro used to set a particular bit in SFR operations*/
#define CAN_17_MCMCAN_BIT_RESET_VAL                                    (uint8)0U

/*Macro used to reset a particular bit in SFR operations*/
#define CAN_17_MCMCAN_BIT_SET_VAL                                      (uint8)1U

#if (((CAN_17_MCMCAN_RX_POLLING_PROCESSING == STD_ON) &&      \
      (CAN_17_MCMCAN_RX_MULTI_PERIODS_SUPPORT == STD_OFF)) || \
     (CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON) ||     \
     (CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON) ||         \
     ((CAN_17_MCMCAN_WU_POLLING_PROCESSING == STD_ON) &&      \
  (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON)))
/*Number of NDAT registers*/
#define CAN_17_MCMCAN_NDATREGNUM (uint8)2U
#endif /* (((CAN_17_MCMCAN_RX_POLLING_PROCESSING == STD_ON)&& \
  (CAN_17_MCMCAN_RX_MULTI_PERIODS_SUPPORT == STD_OFF))||      \
  (CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||         \
  (CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON)||             \
  ((CAN_17_MCMCAN_WU_POLLING_PROCESSING == STD_ON) &&         \
  (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON))) */

/*TX event FIFO address*/
#define CAN_17_MCMCAN_TXEVENTFIFO_ADDR_VAL                            (uint32)8U

/*Buffer Threshold value*/
#define CAN_17_MCMCAN_THRESHOLD_VAL                               (uint32)(100U)

/* RAM BYTE size */
#define CAN_17_MCMCAN_RAM_BYTES                                       (uint32)4U

/* Value for Address Check */
#define CAN_17_MCMCAN_ADDRESS_CHECK                       (uint32) (0x00000000U)

/* Values for clear IR register */
#define CAN_17_MCMCAN_CLEAR_ALL_INTERRUPTS                 (uint32)(0x3FCFFFFFU)

/* Values for Set Global register for reject RTR and Non Match Frames */
#define CAN_17_MCMCAN_GFC_REJT_RTR_NONMATCH                (uint32)(0x0000003FU)

/* Value for clear new data register */
#define CAN_17_MCMCAN_CLEAR_NEWDATA_REG                    (uint32)(0xFFFFFFFFU)

/* Value used for the CLK selection */
#define CAN_17_MCMCAN_MCR_CLKSEL_SET                       (uint32)(0x00000003U)

/* Value used for NDAT2 Register buffer Position access */
#define CAN_17_MCMCAN_BUFFER_POS                                      (uint8)32U

/* Value used for check bit is set or not */
#define CAN_17_MCMCAN_BIT_CLEAR_VAL                                    (uint8)0U

/* CLEAR IR Flags */
#define CAN_17_MCMCAN_RF0L_CLEAR                             (uint32)0x00000008U
#define CAN_17_MCMCAN_RF1L_CLEAR                             (uint32)0x00000080U

/* Clear event FULL and LOST condition in IR */
#define CAN_17_MCMCAN_TEFF_TEFL_CLEAR                        (uint32)0x0000C000U

/* Macro to get the core ID */
#define CAN_17_MCMCAN_GETCOREINDEX                 ((uint8)(Mcal_GetCpuIndex()))

/* SiZE of the variable to be read in SET bit atomic operations.
As the API expects a signed integer, hence no unsigned type is associated with
the value*/
#define CAN_17_MCMCAN_INIT_STATUS_SIZE                                         2

/* Disable CAN clock */
#define CAN_17_MCMCAN_CLK_DISABLE                                     (uint32)0U

/* CCR.INIT bit status check mask values */
#define CAN_17_MCMCAN_NODE_INIT_MODE                       (uint32)(0x00000001U)
#define CAN_17_MCMCAN_NODE_INIT_CCE_SET                     (uint32)(0x00000001)
#define CAN_17_MCMCAN_MODULE_DISABLE_STATUS                (uint32)(0x00000002U)
#define CAN_17_MCMCAN_MCR_RBUSY_STATUS                     (uint32)(0x10000000U)
#define CAN_17_MCMCAN_NODE_PSR_MODE                        (uint32)(0x00000018U)

/*Macro to calculate the GRINT offset*/
#define CAN_17_MCMCAN_INTLINE_OFFSET                                   (uint8)4U

/*Interrupt position values*/
/*Buss off*/
#define CAN_17_MCMCAN_BOFF_POS                                         (uint8)2U
/*Watermark*/
#define CAN_17_MCMCAN_WAT_POS                                          (uint8)3U
/*RX FIFO0*/
#define CAN_17_MCMCAN_RXF0_POS                                         (uint8)3U
/*RX FIFO1*/
#define CAN_17_MCMCAN_RXF1_POS                                         (uint8)3U

#define CAN_17_MCMCAN_RESET_VAL                                               0U


/*******************************************************************************
**                         User Mode Macros                                   **
*******************************************************************************/

/* [cover parentID={1A65EADD-AFD0-4845-B2D2-8257E086DD67}]
[/cover] */
#if (CAN_17_MCMCAN_INIT_DEINIT_API_MODE == CAN_17_MCMCAN_MCAL_SUPERVISOR)
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for
   User mode support in code. No side effects foreseen by violating this MISRA
   rule. */
#define CAN_17_MCMCAN_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(RegAdd,Data)   \
    Mcal_WritePeripEndInitProtReg(RegAdd,Data)

#else

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for
   User mode support in code. No side effects foreseen by violating this MISRA
   rule. */
#define CAN_17_MCMCAN_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(RegAdd,Data)   \
    MCAL_LIB_WRITEPERIPENDINITPROTREG(RegAdd,Data)

#endif

/******************************************************************************
**                      Private Type Definitions                             **
******************************************************************************/
/* [cover parentID={72E03DD2-2604-4aed-96A7-166B044E4FFE}]
[/cover] */
/* [cover parentID={BDE616FE-5D39-4b9d-9390-8351CC6C490C}]
[/cover] */
/*AUTOSAR 4.2.2 */
#if (MCAL_AR_VERSION == MCAL_AR_422)

/*Datatype to be used for controller state transition*/
typedef Can_StateTransitionType Can_17_McmCan_ControllerState;

/*Datatype to be used for controller state transition in Can IF layer*/
/* [cover parentID={54D31BBC-4A63-4b49-B60A-AC3636F4F81F}]
[/cover] */
#define CAN_17_MCMCAN_STARTED                              CANIF_CS_STARTED
#define CAN_17_MCMCAN_STOPPED                              CANIF_CS_STOPPED
#define CAN_17_MCMCAN_SLEEP                                CANIF_CS_SLEEP
#define CAN_17_MCMCAN_UNINIT                               CANIF_CS_UNINIT

/*Typedef to be used for Can_ReturnType*/
/* [cover parentID={3CC29527-F7AD-45d8-A28C-083F8E481191}]
[/cover] */
typedef enum
{
  CAN_17_MCMCAN_OK,
  CAN_17_MCMCAN_NOT_OK,
  CAN_17_MCMCAN_BUSY
} Can_17_McmCan_ReturnValueType;

/*AUTOSAR 4.4.0 */
#else
/*Datatype to be used for controller state transition*/
typedef Can_ControllerStateType Can_17_McmCan_ControllerState;

/*Datatype to be used for controller state transition in Can IF layer*/
/* [cover parentID={54D31BBC-4A63-4b49-B60A-AC3636F4F81F}]
[/cover] */
#define CAN_17_MCMCAN_STARTED                                     CAN_CS_STARTED
#define CAN_17_MCMCAN_STOPPED                                     CAN_CS_STOPPED
#define CAN_17_MCMCAN_SLEEP                                         CAN_CS_SLEEP
#define CAN_17_MCMCAN_UNINIT                                       CAN_CS_UNINIT

/*Typedef to be used for Std_ReturnType*/
/* [cover parentID={3CC29527-F7AD-45d8-A28C-083F8E481191}]
[/cover] */
typedef Std_ReturnType Can_17_McmCan_ReturnValueType;
#define CAN_17_MCMCAN_OK                                                (uint8)0
#define CAN_17_MCMCAN_NOT_OK                                            (uint8)1
#define CAN_17_MCMCAN_BUSY                                              (uint8)2

#endif

/* Data type used to hold the pending messages */
/* [cover parentID={718617BC-4A32-4c4d-8ED1-D13EE815ED57}]
[/cover] */

#if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON))
typedef struct
{
  /* Variable used to hold the current fill level of sw queue*/
  uint16 CanTxSwPendingQueueIndex;
  /* Variable used to hold the pending messages*/
  uint16 *CanTxSwPendingQueuePtr;

} Can_17_McmCan_TxSwQueueType;

#endif /* #if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON)) */

/* Data type used for core specific CAN driver global data storage */
/* [cover parentID={74FB2479-A60D-417a-B557-5B1530ED4D89}]
[/cover] */
typedef struct
{
  /* Pointer to the CAN transmit buffer Mask */
  uint32 *CanTxMaskPtr;

  /* Pointer to Backup variable used to restore during BO */
  uint32 *BackupCanTxMaskPtr;

   /* Can controller mode */
#if (MCAL_AR_VERSION == MCAL_AR_422)
  CanIf_ControllerModeType *CanControllerModePtr;
  #else
  Can_ControllerStateType *CanControllerModePtr;
  #endif

  /* This variable stores count value of disable Interrupt called for the
  controller in the core */
  uint8 *CanDisableIntrpCountPtr;

  /* Used to store swPduHandle passed by CanIf */
  PduIdType *CanSwObjectHandlePtr;

  #if (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON)

  /* This variable stores the wake on bus off status on ICOM configuration */
  boolean *CanIcomConfgBOStatusPtr;

  /* This variable stores the Pretended network support status */
  boolean *CanIcomEnableStatusPtr;

  /* If this variable is SET, Can_Write API will be blocked indicating that ICOM
  enable is in progress and filters are getting updated */
  boolean *CanIcomBlockWriteCallsPtr;

  /* This variable used to stores the current ICOM Configuration ID */
  uint8 *CanActiveIcomCfgIdPtr;

  /* ICOM Message counter counter value */
  uint16 *CanIcomMsgCntrValPtr;

  #endif
  #if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON))
  /* structure used to hold the pending messages*/
  Can_17_McmCan_TxSwQueueType *CanTxSwQueuePtr;
  #endif /* #if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON)) */
} Can_17_McmCan_CoreGlobalType;
/* [cover parentID={B5190528-1363-4e35-8769-DEC665200F41}]
[/cover] */

/*Datatype to check the timeout*/
typedef enum
{
  CAN_17_MCMCAN_EQUAL,
  CAN_17_MCMCAN_NOT_EQUAL,
  CAN_17_MCMCAN_NAND,
  CAN_17_MCMCAN_AND,
} Can_17_McmCan_TimeoutCheckType;

/******************************************************************************
**                      Private Function Declarations                        **
******************************************************************************/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_START_SEC_CODE_QM_GLOBAL
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
/*[cover parentID={A4F3B858-B167-4b5c-AB7F-390C5F5D2185}]
[/cover] */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"

#if (CAN_17_MCMCAN_MULTIPLEXED_TRANSMISSION == STD_ON)
static uint8 Can_17_McmCan_lCheckQueueMask(const uint8 ControllerId,
                        const Can_17_McmCan_CoreConfigType *const CoreConfigPtr,
                                          const uint32 *const QueueSlotMaskPtr);

#endif

/* Function to initialize CAN Module used global variables */
static void Can_17_McmCan_lInitGlobalVar(
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr,
    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr);

/* Function to initialize CAN Module clock/timing registers */
static Std_ReturnType Can_17_McmCan_lInitClkSetting(
    const Can_17_McmCan_ConfigType *const ConfigPtr,
    const uint8 KernelIndx);

/* Function to initialize the global CAN Module */
static Std_ReturnType Can_17_McmCan_lGlobalInit(
                   const Can_17_McmCan_ConfigType *const ConfigPtr);

/* Function to initialize the Core specific CAN Module */
static Std_ReturnType Can_17_McmCan_lCoreInit(
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr,
    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr);

/* Function to initialize CAN Module Node registers */
static Std_ReturnType Can_17_McmCan_lInitController(
    const uint8 ControllerId,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr,
    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr);

/* Function to initialize Tx Hw message objects */
static Std_ReturnType Can_17_McmCan_lInitTxMsgObj(
    const uint8 Controller,
    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr);

/* Function to cancel the pending Tx request */
static void Can_17_McmCan_lCancelPendingTx(const uint8 ControllerId,
    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr);

/* Internal function for Handling Tx write operation */
static Can_17_McmCan_ReturnValueType Can_17_McmCan_lWriteMsgObj(
    const Can_HwHandleType HthIndex,
    const Can_PduType *const PduInfoPtr,
    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr);

#if (CAN_17_MCMCAN_TRIG_TRANSMIT == STD_ON)
/* Function to handle trigger transmit handle */
static Can_17_McmCan_ReturnValueType Can_17_McmCan_lUpdatePduInfo(
    const Can_HwHandleType HthIndex,
    Can_PduType *const TempPduInfo, const Can_PduType *const PduInfoPtr,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr);
#endif /* #if (CAN_17_MCMCAN_TRIG_TRANSMIT == STD_ON) */

#if ((CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING == STD_ON) || \
     (CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) ||     \
     ((CAN_17_MCMCAN_TX_POLLING_PROCESSING == STD_ON) &&  \
 (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_OFF)))

/* Function for handling Tx confirmation operation */
static void Can_17_McmCan_lTxEventHandler(const uint8 HwControllerId,
    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,
    const Can_17_McmCan_ProcessingType ProcessingType,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr);

static void Can_17_McmCan_lTxEventProcessingHandler(const uint8 HwControllerId,
                       const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,
                       const Can_17_McmCan_CoreConfigType *const CoreConfigPtr);
#endif

#if (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON)

static Std_ReturnType Can_17_McmCan_lPeriodCheckSwHandle(
    const uint8 CtrlIndex,
    const uint16 SwObjIndx, const uint8 HthRefPeriods,
    const Can_17_McmCan_CoreConfigType *const ConfigPtr,
    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr);

static void Can_17_McmCan_lTxPeriodPollingHandler(const uint8 CtrlIndex,
            const uint8 HthRefPeriods,
            const Can_17_McmCan_CoreConfigType *const ConfigPtr,
            const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr);
#endif /* #if (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON) */

#if (CAN_17_MCMCAN_SET_BAUDRATE_API == STD_ON)
/* Function to set the nominal baudrate */
static Std_ReturnType Can_17_McmCan_lSetBaudrate(const uint8 Controller,
    const uint16 BaudrateIndx,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr);
#endif /* #if (CAN_17_MCMCAN_SET_BAUDRATE_API == STD_ON) */

#if (CAN_17_MCMCAN_FD_ENABLE == STD_ON)

/* Function to set the FD support baudrate */
static Std_ReturnType Can_17_McmCan_lFDSetBaudrate(const uint8 Controller,
                                                          const uint16 FdIndex,
                       const Can_17_McmCan_CoreConfigType *const CoreConfigPtr);

static uint8 Can_17_McmCan_lWriteFDFillTransmitBuffer(
                                            const Can_PduType *const PduInfoPtr,
                                              const Can_PduType *TempPduInfoPtr,
                                    const volatile Ifx_CAN_N *NodeRegAddressPtr,
                                  volatile Ifx_CAN_TXMSG *const TxMsgBufferPtr);

#endif /* #if (CAN_17_MCMCAN_FD_ENABLE == STD_ON) */

/* Function for state changes if wakeup is disabled */
static Std_ReturnType Can_17_McmCan_lTriggerStateTransition(
    const uint8 Controller,
    const Can_17_McmCan_ControllerState Transition,
    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr);

/*Function for state transition to STARTED*/
static Std_ReturnType Can_17_McmCan_lSetModeStart(const uint8 Controller,
    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr);

/*Function for state transition to STOPPED*/
static Std_ReturnType Can_17_McmCan_lSetModeStop(const uint8 Controller,
    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr);

/*Function for controller state machine transition*/
static Std_ReturnType Can_17_McmCan_lSetControllerMode(const uint8 Controller,
    const Can_17_McmCan_ControllerState Transition);

/* Function to initialize Rx Hw message objects */
static Std_ReturnType Can_17_McmCan_lInitRxMsgObj(const uint8 Controller,
  const Can_17_McmCan_CoreConfigType *const CoreConfigPtr);
/* Function to clear all received messages to avoid unexpected reception
 condition */
static void Can_17_McmCan_lClearReceivedMsg(const uint8 HwControllerId,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr);

/* Function to set the filter mask for standard messages */
static void Can_17_McmCan_lSIDFilterConfig(const uint8 ControllerId,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr);
/* Function to set the filter mask for Extended messages */
static void Can_17_McmCan_lXIDFilterConfig(const uint8 ControllerId,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr);

#if (((CAN_17_MCMCAN_RX_POLLING_PROCESSING == STD_ON) &&      \
      (CAN_17_MCMCAN_RX_MULTI_PERIODS_SUPPORT == STD_OFF)) || \
     (CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON) ||     \
     (CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON) ||         \
     ((CAN_17_MCMCAN_WU_POLLING_PROCESSING == STD_ON) &&      \
    (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON)))
/* Function for Handling data reception */
static void Can_17_McmCan_lReceiveHandler(const uint8 HwControllerId,
    const Can_17_McmCan_RxBufferType CheckBuffType,
    const Can_17_McmCan_ProcessingType ProcessingType,
    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr);

static void Can_17_McmCan_lRxDedicatedHandler(const uint8 HwControllerId,
                      const Can_17_McmCan_ProcessingType ProcessingType,
                      const Can_17_McmCan_CoreConfigType *const CoreConfigPtr,
                      const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr);

static void Can_17_McmCan_lRxFIFO0Handler(const uint8 HwControllerId,
                      const Can_17_McmCan_ProcessingType ProcessingType,
                      const Can_17_McmCan_CoreConfigType *const CoreConfigPtr,
                      const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr);

static void Can_17_McmCan_lRxFIFO1Handler(const uint8 HwControllerId,
                      const Can_17_McmCan_ProcessingType ProcessingType,
                      const Can_17_McmCan_CoreConfigType *const CoreConfigPtr,
                      const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr);
#endif /* (((CAN_17_MCMCAN_RX_POLLING_PROCESSING == STD_ON)&& \
    (CAN_17_MCMCAN_RX_MULTI_PERIODS_SUPPORT == STD_OFF))||    \
    (CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||       \
    (CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON)||           \
    ((CAN_17_MCMCAN_WU_POLLING_PROCESSING == STD_ON) &&       \
    (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON))) */

#if (CAN_17_MCMCAN_RX_MULTI_PERIODS_SUPPORT == STD_ON)
static void Can_17_McmCan_lCheckIfFifoMessageLost(const uint8 ControllerId,
                                const Can_17_McmCan_RxBufferType RxBufferType);

static void Can_17_McmCan_lRxDedicatedPeriodHandler(
  const Can_HwHandleType HrhCnt,
  const uint8 ControllerId,
  const Can_17_McmCan_CoreConfigType *ConfigPtr,
  const Can_17_McmCan_CoreGlobalType *CoreGlobalPtr);

static void Can_17_McmCan_lRxFIFOPeriodHandler(
  const Can_17_McmCan_RxBufferType RxFifo,
  const uint8 ControllerId,
  const Can_17_McmCan_CoreConfigType *ConfigPtr,
  const Can_17_McmCan_CoreGlobalType *CoreGlobalPtr);
#endif

/* Function for Handling data retrieve for the message buffer */
static void Can_17_McmCan_lRxExtractData(const uint8 HwControllerId,
    const uint8 RxBuffIndex,
    const Can_17_McmCan_RxBufferType RxBuffer,
    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr);

/* Handler for Bus-Off condition */
static void Can_17_McmCan_lBusOffHandler(const uint8 HwControllerId,
    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr);

#if (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON)

/* Function for Activate controller with Pretended mode */
static void Can_17_McmCan_lActivateIcom(const uint8 Controller,
    const IcomConfigIdType ConfigurationId,
    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr);

/* Function for De-activate controller with Pretended mode */
static void Can_17_McmCan_lDeactivateIcom(const uint8 Controller,
    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr);

/* Function to do ICOM message validation for greater or smaller operation */
static Std_ReturnType Can_17_McmCan_lIcomCheckGreaterSmaller(
    const uint8 ValData, const uint8 ConfigData,
    uint8 *const CheckValPtr,
    const Can_17_McmCan_IcomSignalOperType SignalOperType);

/* Function for Validate signal conditions */
static Std_ReturnType Can_17_McmCan_lIcomValidateMsgSignal(
    const uint16 MessageIndex,
    const PduInfoType *const PduInfoPtr,
    const Can_17_McmCan_ConfigType *const ConfigPtr);

/* Function for Validate receive message conditions */
static void Can_17_McmCan_lIcomValidateMsg(Can_HwType *const MailboxPtr,
    const PduInfoType *const PduInfoPtr,
    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr);

static void Can_17_McmCan_lIcomSIDFilterConfiguration(
    const uint8 Controller,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr);

static void Can_17_McmCan_lIcomXIDFilterConfiguration(
    const uint8 Controller,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr);

#endif /* #if (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON) */

/* Function for Hw failure time-out detection */
static Std_ReturnType Can_17_McmCan_lTimeOut(
    const volatile uint32 *const RegAddressPtr,
    const uint32 CheckVal, const Can_17_McmCan_TimeoutCheckType CheckStatus);

#if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON)
/* Function for validate the requested configuration */
static Std_ReturnType Can_17_McmCan_lInitDetCheck(
    const Can_17_McmCan_ConfigType *const ConfigPtr, const uint8 CoreIndex);

/* Function to validate the Initialization status of the specific core */
static Std_ReturnType Can_17_McmCan_lDetUninitConfig(
    const uint8 ServiceID,
    const uint8 CoreIndex);
/* Function for mode change request validation */
static Std_ReturnType Can_17_McmCan_lModeDetCheck(const uint8 Controller,
    const Can_17_McmCan_ControllerState Transition,
    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr);

/* Function for validate the requested controller id */
static Std_ReturnType Can_17_McmCan_lDetParamController(
    const uint8 CoreIndex,
    const uint8 Controller,
    const uint8 ServiceID);

/* Function for Write request validation */
static Std_ReturnType Can_17_McmCan_lWriteDetCheck(
    const Can_HwHandleType Hth,
    const Can_PduType *const PduInfoPtr);

/* Function to check validity of the Message ID passed for a write function */
static Std_ReturnType Can_17_McmCan_lWriteIdCheck(
    const Can_HwHandleType Hth,
    const Can_PduType *const PduInfoPtr,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr);

#endif /* #if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON) */

#if (CAN_17_MCMCAN_DEINIT_API == STD_ON)
static Std_ReturnType Can_17_McmCan_lCoreDeInit(
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr,
const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr);
#endif

#if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON)
static void Can_17_McmCan_lDetDataLength(void);
#endif

static Can_17_McmCan_ReturnValueType Can_17_McmCan_lWrite(
    const Can_HwHandleType Hth,
    const Can_PduType *const PduInfoPtr);

#define CAN_17_MCMCAN_STOP_SEC_CODE_QM_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/
#if (CAN_17_MCMCAN_CORE0_ACTIVATION == STD_ON)

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_START_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"
/* Can controller mode */
 #if (MCAL_AR_VERSION == MCAL_AR_422)

static CanIf_ControllerModeType
CanControllerModeCore0[CAN_17_MCMCAN_CORE0_NOOF_CONTROLLER];
#else
static Can_ControllerStateType
CanControllerModeCore0[CAN_17_MCMCAN_CORE0_NOOF_CONTROLLER];
#endif

/* This variable stores count value of disable Interrupt called for the
controller in the core */
static uint8 CanDisableIntrpCountCore0[CAN_17_MCMCAN_CORE0_NOOF_CONTROLLER];

/* Used to store swPduHandle passed by CanIf */
static PduIdType CanSwObjectHandleCore0[CAN_17_MCMCAN_CORE0_NOOF_CONTROLLER *
                                       CAN_17_MCMCAN_NOOF_TX_HW_BUFF_AVAILABLE];

/* Variable to store the Transmit buffer Mask */
static uint32 CanTxMaskCore0[CAN_17_MCMCAN_CORE0_NOOF_CONTROLLER];

/* Variable to store the back-up of transmit buffer,to be restored on Bus-Off */
static uint32 BackupCanTxMaskCore0[CAN_17_MCMCAN_CORE0_NOOF_CONTROLLER];

#if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON))

static uint16 CanTxSwPendingQueueCore0[CAN_17_MCMCAN_CORE0_NOOF_CONTROLLER *
  CAN_17_MCMCAN_NOOF_TX_HW_BUFF_AVAILABLE];
#endif

#if (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON)
/* This variable stores the wake on bus off status on ICOM configuration */
static boolean CanIcomConfgBOStatusCore0[CAN_17_MCMCAN_CORE0_NOOF_CONTROLLER];

/* This variable if SET will block the Can_Write API indicating that ICOM
  enable is in progress and filters are getting updated */
static boolean CanIcomBlockWriteCore0[CAN_17_MCMCAN_CORE0_NOOF_CONTROLLER];

/* This variable stores the Pretended network support status */
static boolean CanIcomEnableStatusCore0[CAN_17_MCMCAN_CORE0_NOOF_CONTROLLER];

/* This variable used to stores the current ICOM Configuration ID */
static uint8 CanActiveIcomCfgIdCore0[CAN_17_MCMCAN_CORE0_NOOF_CONTROLLER];

/* ICOM Message counter counter value */
static uint16 CanIcomMsgCntrValCore0[CAN_17_MCMCAN_NOOF_ICOM_MSGCONFIGURATIONS];
#endif

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_STOP_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"

/******************************************************************************/
/**************Global Initialized structure************************************/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_START_SEC_VAR_INIT_QM_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"

#if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON))

static Can_17_McmCan_TxSwQueueType CanTxSwQueueCore0 =
{
0U,
CanTxSwPendingQueueCore0
};

#endif /* #if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
(CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON)) */

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_STOP_SEC_VAR_INIT_QM_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"
/**************End of Global Initialized structure*****************************/

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_START_SEC_CONST_QM_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"
/* Structure holding core 0 specific CAN states */
static const Can_17_McmCan_CoreGlobalType Can_17_McmCan_Core0State =
{
  /* Pointer to the Variable to store the Transmit buffer Mask */
  CanTxMaskCore0,

  /* Pointer to the Variable to store the back-up of transmit buffer,
  to be restored on Bus-Off */
  BackupCanTxMaskCore0,

  /* Can controller mode */
  CanControllerModeCore0,

  /* This variable stores count value of disable Interrupt called for the
  controller in the core */
  CanDisableIntrpCountCore0,

  /* Used to store swPduHandle passed by CanIf */
  CanSwObjectHandleCore0,

  #if (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON)
  /* This variable stores the wake on bus off status on ICOM configuration */
  CanIcomConfgBOStatusCore0,

  /* This variable stores the Pretended network support status */
  CanIcomEnableStatusCore0,

  /* Block Can_Write during Icom Configuration */
  CanIcomBlockWriteCore0,

  /* This variable used to stores the current ICOM Configuration ID */
  CanActiveIcomCfgIdCore0,

  /* ICOM Message counter counter value */
  CanIcomMsgCntrValCore0,
  #endif

  #if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON))

  &CanTxSwQueueCore0

  #endif /* #if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON)) */
};

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_STOP_SEC_CONST_QM_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"
#endif /* #if (CAN_17_MCMCAN_CORE0_ACTIVATION == STD_ON) */

#if (MCAL_NO_OF_CORES > 1U)
#if (CAN_17_MCMCAN_CORE1_ACTIVATION == STD_ON)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_START_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"

 #if (MCAL_AR_VERSION == MCAL_AR_422)
static CanIf_ControllerModeType
CanControllerModeCore1[CAN_17_MCMCAN_CORE1_NOOF_CONTROLLER];

#else
static Can_ControllerStateType
CanControllerModeCore1[CAN_17_MCMCAN_CORE1_NOOF_CONTROLLER];
#endif

/* Variable to store the Transmit buffer Mask */
static uint32 CanTxMaskCore1[CAN_17_MCMCAN_CORE1_NOOF_CONTROLLER];

/* Variable to store the back-up of transmit buffer,
to be restored on Bus-Off */
static uint32 BackupCanTxMaskCore1[CAN_17_MCMCAN_CORE1_NOOF_CONTROLLER];

/* This variable stores count value of disable Interrupt called for the
controller in the core */
static uint8 CanDisableIntrpCountCore1[CAN_17_MCMCAN_CORE1_NOOF_CONTROLLER];

/* Used to store swPduHandle passed by CanIf */
static PduIdType CanSwObjectHandleCore1[CAN_17_MCMCAN_CORE1_NOOF_CONTROLLER *
     CAN_17_MCMCAN_NOOF_TX_HW_BUFF_AVAILABLE];

#if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON))
static uint16 CanTxSwPendingQueueCore1[CAN_17_MCMCAN_CORE1_NOOF_CONTROLLER *
  CAN_17_MCMCAN_NOOF_TX_HW_BUFF_AVAILABLE];
  #endif

#if (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON)
/* This variable stores the wake on bus off status on ICOM configuration */
static boolean CanIcomConfgBOStatusCore1[CAN_17_MCMCAN_CORE1_NOOF_CONTROLLER];

/* This variable stores the Pretended network support status */
static boolean CanIcomEnableStatusCore1[CAN_17_MCMCAN_CORE1_NOOF_CONTROLLER];

/* This variable if SET will block the Can_Write API indicating that ICOM
  enable is in progress and filters are getting updated */
static boolean CanIcomBlockWriteCore1[CAN_17_MCMCAN_CORE1_NOOF_CONTROLLER];

/* This variable used to stores the current ICOM Configuration ID */
static uint8 CanActiveIcomCfgIdCore1[CAN_17_MCMCAN_CORE1_NOOF_CONTROLLER];

/* ICOM Message counter counter value */
static uint16 CanIcomMsgCntrValCore1[CAN_17_MCMCAN_NOOF_ICOM_MSGCONFIGURATIONS];
#endif

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_STOP_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"

/******************************************************************************/
/**************Global Initialized structure************************************/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_START_SEC_VAR_INIT_QM_CORE1_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"

#if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON))

static Can_17_McmCan_TxSwQueueType CanTxSwQueueCore1 =
{
0U,
CanTxSwPendingQueueCore1
};

#endif /* #if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
(CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON)) */

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_STOP_SEC_VAR_INIT_QM_CORE1_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"
/**************End of Global Initialized structure*****************************/


/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_START_SEC_CONST_QM_CORE1_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"
/* Structure holding core 0 specific CAN states */
static const Can_17_McmCan_CoreGlobalType Can_17_McmCan_Core1State =
{
  /* Pointer to the Variable to store the Transmit buffer Mask */
  CanTxMaskCore1,

  /* Pointer to the Variable to store the back-up of transmit buffer,
  to be restored on Bus-Off */
  BackupCanTxMaskCore1,

  /* Can controller mode */
  CanControllerModeCore1,

  /* This variable stores count value of disable Interrupt called for the
  controller in the core */
  CanDisableIntrpCountCore1,

  /* Used to store swPduHandle passed by CanIf */
  CanSwObjectHandleCore1,

  #if (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON)
  /* This variable stores the wake on bus off status on ICOM configuration */
  CanIcomConfgBOStatusCore1,

  /* This variable stores the Pretended network support status */
  CanIcomEnableStatusCore1,

  /* Block Can_Write during Icom Configuration */
  CanIcomBlockWriteCore1,

  /* This variable used to stores the current ICOM Configuration ID */
  CanActiveIcomCfgIdCore1,

  /* ICOM Message counter counter value */
  CanIcomMsgCntrValCore1,
  #endif

  #if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON))

  &CanTxSwQueueCore1

  #endif /* #if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON)) */

};
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_STOP_SEC_CONST_QM_CORE1_UNSPECIFIED
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
/*[cover parentID={A4F3B858-B167-4b5c-AB7F-390C5F5D2185}]
[/cover] */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"
#endif /* #if (CAN_17_MCMCAN_CORE1_ACTIVATION == STD_ON) */
#endif /* #if (MCAL_NO_OF_CORES > 1U) */

#if (MCAL_NO_OF_CORES > 2U)
#if (CAN_17_MCMCAN_CORE2_ACTIVATION == STD_ON)

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_START_SEC_VAR_CLEARED_QM_CORE2_UNSPECIFIED
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
/*[cover parentID={A4F3B858-B167-4b5c-AB7F-390C5F5D2185}]
[/cover] */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"
#if (MCAL_AR_VERSION == MCAL_AR_422)
static CanIf_ControllerModeType
CanControllerModeCore2[CAN_17_MCMCAN_CORE2_NOOF_CONTROLLER];

#else
static Can_ControllerStateType
CanControllerModeCore2[CAN_17_MCMCAN_CORE2_NOOF_CONTROLLER];

#endif
/* Variable to store the Transmit buffer Mask */
static uint32 CanTxMaskCore2[CAN_17_MCMCAN_CORE2_NOOF_CONTROLLER];

/* Variable to store the back-up of transmit buffer,
to be restored on Bus-Off */
static uint32 BackupCanTxMaskCore2[CAN_17_MCMCAN_CORE2_NOOF_CONTROLLER];

/* This variable stores count value of disable Interrupt called for the
controller in the core */
static uint8 CanDisableIntrpCountCore2[CAN_17_MCMCAN_CORE2_NOOF_CONTROLLER];

/* Used to store swPduHandle passed by CanIf */
static PduIdType CanSwObjectHandleCore2[CAN_17_MCMCAN_CORE2_NOOF_CONTROLLER *
                                       CAN_17_MCMCAN_NOOF_TX_HW_BUFF_AVAILABLE];


#if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON))


static uint16 CanTxSwPendingQueueCore2[CAN_17_MCMCAN_CORE2_NOOF_CONTROLLER *
                                       CAN_17_MCMCAN_NOOF_TX_HW_BUFF_AVAILABLE];
#endif

#if (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON)
/* This variable stores the wake on bus off status on ICOM configuration */
static boolean CanIcomConfgBOStatusCore2[CAN_17_MCMCAN_CORE2_NOOF_CONTROLLER];

/* This variable stores the Pretended network support status */
static boolean CanIcomEnableStatusCore2[CAN_17_MCMCAN_CORE2_NOOF_CONTROLLER];

/* This variable if SET will block the Can_Write API indicating that ICOM
  enable is in progress and filters are getting updated */
static boolean CanIcomBlockWriteCore2[CAN_17_MCMCAN_CORE2_NOOF_CONTROLLER];

/* This variable used to stores the current ICOM Configuration ID */
static uint8 CanActiveIcomCfgIdCore2[CAN_17_MCMCAN_CORE2_NOOF_CONTROLLER];

/* ICOM Message counter counter value */
static uint16 CanIcomMsgCntrValCore2[CAN_17_MCMCAN_NOOF_ICOM_MSGCONFIGURATIONS];
#endif

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_STOP_SEC_VAR_CLEARED_QM_CORE2_UNSPECIFIED
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
/*[cover parentID={A4F3B858-B167-4b5c-AB7F-390C5F5D2185}]
[/cover] */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"

/******************************************************************************/
/**************Global Initialized structure************************************/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_START_SEC_VAR_INIT_QM_CORE2_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"

#if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON))
static Can_17_McmCan_TxSwQueueType CanTxSwQueueCore2 =
{
0U,
CanTxSwPendingQueueCore2
};

#endif /* #if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
(CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON)) */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_STOP_SEC_VAR_INIT_QM_CORE2_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"
/**************End of Global Initialized structure*****************************/

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_START_SEC_CONST_QM_CORE2_UNSPECIFIED
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
/*[cover parentID={A4F3B858-B167-4b5c-AB7F-390C5F5D2185}]
[/cover] */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"
/* Structure holding core 0 specific CAN states */
static const Can_17_McmCan_CoreGlobalType Can_17_McmCan_Core2State =
{
  /* Pointer to the Variable to store the Transmit buffer Mask */
  CanTxMaskCore2,

  /* Pointer to the Variable to store the back-up of transmit buffer,
  to be restored on Bus-Off */
  BackupCanTxMaskCore2,

  /* Can controller mode */
  CanControllerModeCore2,

  /* This variable stores count value of disable Interrupt called for the
  controller in the core */
  CanDisableIntrpCountCore2,

  /* Used to store swPduHandle passed by CanIf */
  CanSwObjectHandleCore2,

  #if (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON)
  /* This variable stores the wake on bus off status on ICOM configuration */
  CanIcomConfgBOStatusCore2,

  /* This variable stores the Pretended network support status */
  CanIcomEnableStatusCore2,

  /* Block Can_Write during Icom Configuration */
  CanIcomBlockWriteCore2,

  /* This variable used to stores the current ICOM Configuration ID */
  CanActiveIcomCfgIdCore2,

  /* ICOM Message counter counter value */
  CanIcomMsgCntrValCore2,
  #endif

  #if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON))

  &CanTxSwQueueCore2

  #endif /* #if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON)) */

};


/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_STOP_SEC_CONST_QM_CORE2_UNSPECIFIED
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
/*[cover parentID={A4F3B858-B167-4b5c-AB7F-390C5F5D2185}]
[/cover] */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"
#endif /* #if (CAN_17_MCMCAN_CORE2_ACTIVATION == STD_ON) */
#endif /* #if (MCAL_NO_OF_CORES > 2U) */

#if (MCAL_NO_OF_CORES > 3U)
#if (CAN_17_MCMCAN_CORE3_ACTIVATION == STD_ON)





/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_START_SEC_VAR_CLEARED_QM_CORE3_UNSPECIFIED
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
/*[cover parentID={A4F3B858-B167-4b5c-AB7F-390C5F5D2185}]
[/cover] */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"
#if (MCAL_AR_VERSION == MCAL_AR_422)
static CanIf_ControllerModeType
CanControllerModeCore3[CAN_17_MCMCAN_CORE3_NOOF_CONTROLLER];
#else
static Can_ControllerStateType
CanControllerModeCore3[CAN_17_MCMCAN_CORE3_NOOF_CONTROLLER];
#endif
/* Variable to store the Transmit buffer Mask */
static uint32 CanTxMaskCore3[CAN_17_MCMCAN_CORE3_NOOF_CONTROLLER];

/* Variable to store the back-up of transmit buffer,
to be restored on Bus-Off */
static uint32 BackupCanTxMaskCore3[CAN_17_MCMCAN_CORE3_NOOF_CONTROLLER];

/* This variable stores count value of disable Interrupt called for the
controller in the core */
static uint8 CanDisableIntrpCountCore3[CAN_17_MCMCAN_CORE3_NOOF_CONTROLLER];

/* Used to store swPduHandle passed by CanIf */
static PduIdType CanSwObjectHandleCore3[CAN_17_MCMCAN_CORE3_NOOF_CONTROLLER *
                                      CAN_17_MCMCAN_NOOF_TX_HW_BUFF_AVAILABLE];

#if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON))

static uint16 CanTxSwPendingQueueCore3[CAN_17_MCMCAN_CORE3_NOOF_CONTROLLER *
                                      CAN_17_MCMCAN_NOOF_TX_HW_BUFF_AVAILABLE];
#endif

#if (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON)
/* This variable stores the wake on bus off status on ICOM configuration */
static boolean CanIcomConfgBOStatusCore3[CAN_17_MCMCAN_CORE3_NOOF_CONTROLLER];

/* This variable stores the Pretended network support status */
static boolean CanIcomEnableStatusCore3[CAN_17_MCMCAN_CORE3_NOOF_CONTROLLER];

/* This variable if SET will block the Can_Write API indicating that ICOM
  enable is in progress and filters are getting updated */
static boolean CanIcomBlockWriteCore3[CAN_17_MCMCAN_CORE3_NOOF_CONTROLLER];

/* This variable used to stores the current ICOM Configuration ID */
static uint8 CanActiveIcomCfgIdCore3[CAN_17_MCMCAN_CORE3_NOOF_CONTROLLER];

/* ICOM Message counter counter value */
static uint16 CanIcomMsgCntrValCore3[CAN_17_MCMCAN_NOOF_ICOM_MSGCONFIGURATIONS];
#endif

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_STOP_SEC_VAR_CLEARED_QM_CORE3_UNSPECIFIED
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
/*[cover parentID={A4F3B858-B167-4b5c-AB7F-390C5F5D2185}]
[/cover] */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"
/******************************************************************************/
/**************Global Initialized structure************************************/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_START_SEC_VAR_INIT_QM_CORE3_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"

#if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON))
static Can_17_McmCan_TxSwQueueType CanTxSwQueueCore3 =
{
0U,
CanTxSwPendingQueueCore3
};

#endif /* #if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
(CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON)) */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_STOP_SEC_VAR_INIT_QM_CORE3_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"
/**************End of Global Initialized structure*****************************/


/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_START_SEC_CONST_QM_CORE3_UNSPECIFIED
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
/*[cover parentID={A4F3B858-B167-4b5c-AB7F-390C5F5D2185}]
[/cover] */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"
/* Structure holding core 0 specific CAN states */
static const Can_17_McmCan_CoreGlobalType Can_17_McmCan_Core3State =
{
  /* Pointer to the Variable to store the Transmit buffer Mask */
  CanTxMaskCore3,

  /* Pointer to the Variable to store the back-up of transmit buffer,
  to be restored on Bus-Off */
  BackupCanTxMaskCore3,

  /* Can controller mode */
  CanControllerModeCore3,

  /* This variable stores count value of disable Interrupt called for the
  controller in the core */
  CanDisableIntrpCountCore3,

  /* Used to store swPduHandle passed by CanIf */
  CanSwObjectHandleCore3,

  #if (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON)
  /* This variable stores the wake on bus off status on ICOM configuration */
  CanIcomConfgBOStatusCore3,

  /* This variable stores the Pretended network support status */
  CanIcomEnableStatusCore3,

    /* Block Can_Write during Icom Configuration */
  CanIcomBlockWriteCore3,

  /* This variable used to stores the current ICOM Configuration ID */
  CanActiveIcomCfgIdCore3,

  /* ICOM Message counter counter value */
  CanIcomMsgCntrValCore3,
  #endif

  #if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON))

  &CanTxSwQueueCore3

  #endif /* #if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON)) */

};



/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_STOP_SEC_CONST_QM_CORE3_UNSPECIFIED
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
/*[cover parentID={A4F3B858-B167-4b5c-AB7F-390C5F5D2185}]
[/cover] */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"
#endif /* #if (CAN_17_MCMCAN_CORE3_ACTIVATION == STD_ON) */
#endif /* #if (MCAL_NO_OF_CORES > 3U) */

#if (MCAL_NO_OF_CORES > 4U)
#if (CAN_17_MCMCAN_CORE4_ACTIVATION == STD_ON)



/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_START_SEC_VAR_CLEARED_QM_CORE4_UNSPECIFIED
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
/*[cover parentID={A4F3B858-B167-4b5c-AB7F-390C5F5D2185}]
[/cover] */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"

#if (MCAL_AR_VERSION == MCAL_AR_422)
static CanIf_ControllerModeType
CanControllerModeCore4[CAN_17_MCMCAN_CORE4_NOOF_CONTROLLER];
#else
static Can_ControllerStateType
CanControllerModeCore4[CAN_17_MCMCAN_CORE4_NOOF_CONTROLLER];
#endif
/* Variable to store the Transmit buffer Mask */
static uint32 CanTxMaskCore4[CAN_17_MCMCAN_CORE4_NOOF_CONTROLLER];

/* Variable to store the back-up of transmit buffer,
to be restored on Bus-Off */
static uint32 BackupCanTxMaskCore4[CAN_17_MCMCAN_CORE4_NOOF_CONTROLLER];

/* This variable stores count value of disable Interrupt called for the
controller in the core */
static uint8 CanDisableIntrpCountCore4[CAN_17_MCMCAN_CORE4_NOOF_CONTROLLER];

/* Used to store swPduHandle passed by CanIf */
static PduIdType CanSwObjectHandleCore4[CAN_17_MCMCAN_CORE4_NOOF_CONTROLLER *
                                       CAN_17_MCMCAN_NOOF_TX_HW_BUFF_AVAILABLE];


#if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON))
static uint16 CanTxSwPendingQueueCore4[CAN_17_MCMCAN_CORE4_NOOF_CONTROLLER *
                                       CAN_17_MCMCAN_NOOF_TX_HW_BUFF_AVAILABLE];
#endif
#if (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON)
/* This variable stores the wake on bus off status on ICOM configuration */
static boolean CanIcomConfgBOStatusCore4[CAN_17_MCMCAN_CORE4_NOOF_CONTROLLER];

/* This variable stores the Pretended network support status */
static boolean CanIcomEnableStatusCore4[CAN_17_MCMCAN_CORE4_NOOF_CONTROLLER];

/* This variable if SET will block the Can_Write API indicating that ICOM
  enable is in progress and filters are getting updated */
static boolean CanIcomBlockWriteCore4[CAN_17_MCMCAN_CORE4_NOOF_CONTROLLER];

/* This variable used to stores the current ICOM Configuration ID */
static uint8 CanActiveIcomCfgIdCore4[CAN_17_MCMCAN_CORE4_NOOF_CONTROLLER];

/* ICOM Message counter counter value */
static uint16 CanIcomMsgCntrValCore4[CAN_17_MCMCAN_NOOF_ICOM_MSGCONFIGURATIONS];
#endif

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_STOP_SEC_VAR_CLEARED_QM_CORE4_UNSPECIFIED
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
/*[cover parentID={A4F3B858-B167-4b5c-AB7F-390C5F5D2185}]
[/cover] */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"

/******************************************************************************/
/**************Global Initialized structure************************************/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_START_SEC_VAR_INIT_QM_CORE4_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"

#if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON))
static Can_17_McmCan_TxSwQueueType CanTxSwQueueCore4 =
{
0U,
CanTxSwPendingQueueCore4
};

#endif /* #if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
(CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON)) */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_STOP_SEC_VAR_INIT_QM_CORE4_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"
/**************End of Global Initialized structure*****************************/


/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_START_SEC_CONST_QM_CORE4_UNSPECIFIED
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
/*[cover parentID={A4F3B858-B167-4b5c-AB7F-390C5F5D2185}]
[/cover] */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"
/* Structure holding core 0 specific CAN states */
static const Can_17_McmCan_CoreGlobalType Can_17_McmCan_Core4State =
{
  /* Pointer to the Variable to store the Transmit buffer Mask */
  CanTxMaskCore4,

  /* Pointer to the Variable to store the back-up of transmit buffer,
  to be restored on Bus-Off */
  BackupCanTxMaskCore4,

  /* Can controller mode */
  CanControllerModeCore4,

  /* This variable stores count value of disable Interrupt called for the
  controller in the core */
  CanDisableIntrpCountCore4,

  /* Used to store swPduHandle passed by CanIf */
  CanSwObjectHandleCore4,

  #if (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON)
  /* This variable stores the wake on bus off status on ICOM configuration */
  CanIcomConfgBOStatusCore4,

  /* This variable stores the Pretended network support status */
  CanIcomEnableStatusCore4,

  /* Block Can_Write during Icom Configuration */
  CanIcomBlockWriteCore4,

  /* This variable used to stores the current ICOM Configuration ID */
  CanActiveIcomCfgIdCore4,

  /* ICOM Message counter counter value */
  CanIcomMsgCntrValCore4,
  #endif

  #if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON))

  &CanTxSwQueueCore4

  #endif /* #if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON)) */

};

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_STOP_SEC_CONST_QM_CORE4_UNSPECIFIED
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
/*[cover parentID={A4F3B858-B167-4b5c-AB7F-390C5F5D2185}]
[/cover] */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"
#endif /* #if (CAN_17_MCMCAN_CORE4_ACTIVATION == STD_ON) */
#endif /* #if (MCAL_NO_OF_CORE4 > 1U) */

#if (MCAL_NO_OF_CORES > 5U)
#if (CAN_17_MCMCAN_CORE5_ACTIVATION == STD_ON)





/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_START_SEC_VAR_CLEARED_QM_CORE5_UNSPECIFIED
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
/*[cover parentID={A4F3B858-B167-4b5c-AB7F-390C5F5D2185}]
[/cover] */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"
#if (MCAL_AR_VERSION == MCAL_AR_422)
static CanIf_ControllerModeType
CanControllerModeCore5[CAN_17_MCMCAN_CORE5_NOOF_CONTROLLER];

#else
static Can_ControllerStateType
CanControllerModeCore5[CAN_17_MCMCAN_CORE5_NOOF_CONTROLLER];

#endif
/* Variable to store the Transmit buffer Mask */
static uint32 CanTxMaskCore5[CAN_17_MCMCAN_CORE5_NOOF_CONTROLLER];

/* Variable to store the back-up of transmit buffer, to be restored on Bus-Off*/
static uint32 BackupCanTxMaskCore5[CAN_17_MCMCAN_CORE5_NOOF_CONTROLLER];

/* This variable stores count value of disable Interrupt called for the
controller in the core */
static uint8 CanDisableIntrpCountCore5[CAN_17_MCMCAN_CORE5_NOOF_CONTROLLER];

/* Used to store swPduHandle passed by CanIf */
static PduIdType CanSwObjectHandleCore5[CAN_17_MCMCAN_CORE5_NOOF_CONTROLLER *
                                       CAN_17_MCMCAN_NOOF_TX_HW_BUFF_AVAILABLE];


#if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON))

static uint16 CanTxSwPendingQueueCore5[CAN_17_MCMCAN_CORE5_NOOF_CONTROLLER *
                                       CAN_17_MCMCAN_NOOF_TX_HW_BUFF_AVAILABLE];
#endif

#if (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON)
/* This variable stores the wake on bus off status on ICOM configuration */
static boolean CanIcomConfgBOStatusCore5[CAN_17_MCMCAN_CORE5_NOOF_CONTROLLER];

/* This variable stores the Pretended network support status */
static boolean CanIcomEnableStatusCore5[CAN_17_MCMCAN_CORE5_NOOF_CONTROLLER];

/* This variable if SET will block the Can_Write API indicating that ICOM
  enable is in progress and filters are getting updated */
static boolean CanIcomBlockWriteCore5[CAN_17_MCMCAN_CORE5_NOOF_CONTROLLER];

/* This variable used to stores the current ICOM Configuration ID */
static uint8 CanActiveIcomCfgIdCore5[CAN_17_MCMCAN_CORE5_NOOF_CONTROLLER];

/* ICOM Message counter counter value */
static uint16 CanIcomMsgCntrValCore5[CAN_17_MCMCAN_NOOF_ICOM_MSGCONFIGURATIONS];

#endif

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_STOP_SEC_VAR_CLEARED_QM_CORE5_UNSPECIFIED
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
/*[cover parentID={A4F3B858-B167-4b5c-AB7F-390C5F5D2185}]
[/cover] */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"

/******************************************************************************/
/**************Global Initialized structure************************************/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_START_SEC_VAR_INIT_QM_CORE5_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"

#if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON))
static Can_17_McmCan_TxSwQueueType CanTxSwQueueCore5 =
{
0U,
CanTxSwPendingQueueCore5
};

#endif /* #if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
(CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON)) */

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_STOP_SEC_VAR_INIT_QM_CORE5_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"
/**************End of Global Initialized structure*****************************/

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_START_SEC_CONST_QM_CORE5_UNSPECIFIED
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
/*[cover parentID={A4F3B858-B167-4b5c-AB7F-390C5F5D2185}]
[/cover] */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"
/* Structure holding core 0 specific CAN states */
static const Can_17_McmCan_CoreGlobalType Can_17_McmCan_Core5State =
{
  /* Pointer to the Variable to store the Transmit buffer Mask */
  CanTxMaskCore5,

  /* Pointer to the Variable to store the back-up of transmit buffer,
  to be restored on Bus-Off */
  BackupCanTxMaskCore5,

  /* Can controller mode */
  CanControllerModeCore5,

  /* This variable stores count value of disable Interrupt called for the
  controller in the core */
  CanDisableIntrpCountCore5,

  /* Used to store swPduHandle passed by CanIf */
  CanSwObjectHandleCore5,

  #if (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON)
  /* This variable stores the wake on bus off status on ICOM configuration */
  CanIcomConfgBOStatusCore5,

  /* This variable stores the Pretended network support status */
  CanIcomEnableStatusCore5,

  /* Block Can_Write during Icom Configuration */
  CanIcomBlockWriteCore5,

  /* This variable used to stores the current ICOM Configuration ID */
  CanActiveIcomCfgIdCore5,

  /* ICOM Message counter counter value */
  CanIcomMsgCntrValCore5,
  #endif

  #if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON))

  &CanTxSwQueueCore5

  #endif /* #if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON)) */

};

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_STOP_SEC_CONST_QM_CORE5_UNSPECIFIED
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
/*[cover parentID={A4F3B858-B167-4b5c-AB7F-390C5F5D2185}]
[/cover] */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"
#endif /* #if (CAN_17_MCMCAN_CORE5_ACTIVATION == STD_ON) */
#endif /* #if (MCAL_NO_OF_CORES > 5U) */

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_START_SEC_CONST_QM_GLOBAL_UNSPECIFIED
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
/*[cover parentID={A4F3B858-B167-4b5c-AB7F-390C5F5D2185}]
[/cover] */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"

/* Variable to hold the pointers to variables holding core specific CAN
states */
static const Can_17_McmCan_CoreGlobalType *const
Can_17_McmCan_GblCoreState[MCAL_NO_OF_CORES] =
{
  #if (CAN_17_MCMCAN_CORE0_ACTIVATION == STD_ON)
  &Can_17_McmCan_Core0State
  #else
  NULL_PTR
  #endif
  #if (MCAL_NO_OF_CORES > 1U)
  #if (CAN_17_MCMCAN_CORE1_ACTIVATION == STD_ON)
  ,
  &Can_17_McmCan_Core1State
  #else
  ,
  NULL_PTR
  #endif
  #endif
  #if (MCAL_NO_OF_CORES > 2U)
  #if (CAN_17_MCMCAN_CORE2_ACTIVATION == STD_ON)
  ,
  &Can_17_McmCan_Core2State
  #else
  ,
  NULL_PTR
  #endif
  #endif
  #if (MCAL_NO_OF_CORES > 3U)
  #if (CAN_17_MCMCAN_CORE3_ACTIVATION == STD_ON)
  ,
  &Can_17_McmCan_Core3State
  #else
  ,
  NULL_PTR
  #endif
  #endif
  #if (MCAL_NO_OF_CORES > 4U)
  #if (CAN_17_MCMCAN_CORE4_ACTIVATION == STD_ON)
  ,
  &Can_17_McmCan_Core4State
  #else
  ,
  NULL_PTR
  #endif
  #endif
  #if (MCAL_NO_OF_CORES > 5U)
  #if (CAN_17_MCMCAN_CORE5_ACTIVATION == STD_ON)
  ,
  &Can_17_McmCan_Core5State
  #else
  ,
  NULL_PTR
  #endif
  #endif
};

#if (CAN_17_MCMCAN_FD_ENABLE == STD_ON)
/*Macros for the array values of the FD DLC array*/
#define CAN_17_MCMCAN_FDDLC_LEN_CODE_0                                        0U
#define CAN_17_MCMCAN_FDDLC_LEN_CODE_1                                        1U
#define CAN_17_MCMCAN_FDDLC_LEN_CODE_2                                        2U
#define CAN_17_MCMCAN_FDDLC_LEN_CODE_3                                        3U
#define CAN_17_MCMCAN_FDDLC_LEN_CODE_4                                        4U
#define CAN_17_MCMCAN_FDDLC_LEN_CODE_5                                        5U
#define CAN_17_MCMCAN_FDDLC_LEN_CODE_6                                        6U
#define CAN_17_MCMCAN_FDDLC_LEN_CODE_7                                        7U
#define CAN_17_MCMCAN_FDDLC_LEN_CODE_8                                        8U
#define CAN_17_MCMCAN_FDDLC_LEN_CODE_12                                      12U
#define CAN_17_MCMCAN_FDDLC_LEN_CODE_16                                      16U
#define CAN_17_MCMCAN_FDDLC_LEN_CODE_20                                      20U
#define CAN_17_MCMCAN_FDDLC_LEN_CODE_24                                      24U
#define CAN_17_MCMCAN_FDDLC_LEN_CODE_32                                      32U
#define CAN_17_MCMCAN_FDDLC_LEN_CODE_48                                      48U
#define CAN_17_MCMCAN_FDDLC_LEN_CODE_64                                      64U

static const uint8 Can_17_McmCan_GblFdDlcConvDB[CAN_17_MCMCAN_FDDLC_VAL] =
{
  CAN_17_MCMCAN_FDDLC_LEN_CODE_0,
  CAN_17_MCMCAN_FDDLC_LEN_CODE_1,
  CAN_17_MCMCAN_FDDLC_LEN_CODE_2,
  CAN_17_MCMCAN_FDDLC_LEN_CODE_3,
  CAN_17_MCMCAN_FDDLC_LEN_CODE_4,
  CAN_17_MCMCAN_FDDLC_LEN_CODE_5,
  CAN_17_MCMCAN_FDDLC_LEN_CODE_6,
  CAN_17_MCMCAN_FDDLC_LEN_CODE_7,
  CAN_17_MCMCAN_FDDLC_LEN_CODE_8,
  CAN_17_MCMCAN_FDDLC_LEN_CODE_12,
  CAN_17_MCMCAN_FDDLC_LEN_CODE_16,
  CAN_17_MCMCAN_FDDLC_LEN_CODE_20,
  CAN_17_MCMCAN_FDDLC_LEN_CODE_24,
  CAN_17_MCMCAN_FDDLC_LEN_CODE_32,
  CAN_17_MCMCAN_FDDLC_LEN_CODE_48,
  CAN_17_MCMCAN_FDDLC_LEN_CODE_64
};
#endif

/* MISRA2012_RULE_5_1_JUSTIFICATION:E External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_STOP_SEC_CONST_QM_GLOBAL_UNSPECIFIED
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
/*[cover parentID={A4F3B858-B167-4b5c-AB7F-390C5F5D2185}]
[/cover] */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_START_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
/*[cover parentID={A4F3B858-B167-4b5c-AB7F-390C5F5D2185}]
[/cover] */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"

/* Initialize status for all cores. */
/* MISRA2012_RULE_8_9_JUSTIFICATION: This 32 bit variable holds the status of
the CAN module accross the different cores hence cannot be placed in
block scope */
static uint32 Can_17_McmCan_InitStatus;
/* Pointer to store configuration set pointer */
static const Can_17_McmCan_ConfigType *Can_17_McmCan_kGblConfigPtr;

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_STOP_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
/*[cover parentID={A4F3B858-B167-4b5c-AB7F-390C5F5D2185}]
[/cover] */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define CAN_17_MCMCAN_START_SEC_CODE_QM_GLOBAL
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
/*[cover parentID={A4F3B858-B167-4b5c-AB7F-390C5F5D2185}]
[/cover] */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
    without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"

/*******************************************************************************
** Traceability   : [cover parentID={196A1432-EAB1-461a-BD6C-259784BF6397}]   **
**                  [cover parentID={70B9C2F0-4AE1-4940-B3BF-BDFA369B5330}]   **
**                                                                            **
**  Syntax           : void Can_17_McmCan_Init                                **
**                    (                                                       **
**                      const Can_17_McmCan_ConfigType *const Config          **
**                    )                                                       **
**                                                                            **
**  Description      : The function initializes all global variables and      **
**                     relevant registers of the MCMCAN(based on configuration)*
**                     assigned to that particular core with the values of    **
**                     structure referenced by the parameter ConfigPtr.       **
**                     Successful execution of this API will trigger a state  **
**                     transition of the CAN Driver state machine from        **
**                     CAN_UNINIT to CAN_READY state.                         **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : 0x00                                                   **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Non-Reentrant                                          **
**                                                                            **
**  Parameters(in)   : Config - Pointer to the CAN driver root configuration  **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
void Can_17_McmCan_Init(const Can_17_McmCan_ConfigType *const Config)
{
  /*Current executing core index*/
  uint8 CoreIndex;

  /*Variable to store the local core state type*/
  const Can_17_McmCan_CoreGlobalType *CoreGlobalPtr;

  /*Variable to store the local Config pointer type*/
  const Can_17_McmCan_CoreConfigType *CoreConfigPtr;


  /*Variable to store the return value of local functions*/
  Std_ReturnType ApiStatus = E_OK;


  /* Get core id which is executing currently */
  CoreIndex = CAN_17_MCMCAN_GETCOREINDEX;

  /*Check if DET is enabled*/
  /* [cover parentID={062510C8-FDBF-4251-9197-125FE758220C}]
  DET is enabled
  [/cover] */
  #if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON)

  /* Check if the driver is already initialized */
  /* [cover parentID={CF54DB20-E407-4ec6-863C-107A31F6E3FD}]
  Check if the driver is initialized
  [/cover] */
  ApiStatus = Can_17_McmCan_lInitDetCheck(Config, CoreIndex);

  /* [cover parentID={9438B1D7-5A49-4b5c-A516-070F22851D4E}]
  Is the DET check paased?
  [/cover] */
  if (E_OK == ApiStatus)
  #endif /* #if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON) */
  {


    /*Check if it is the master core currently executing*/
    /* [cover parentID={E9841F16-4DE5-48d3-8BA8-3DFEA3C6A1BC}]
    Is the executing core the master core?
    [/cover] */
    if (MCAL_MASTER_COREID == CoreIndex)
    {
      /* Core specific copy of the master configuration structure */
      Can_17_McmCan_kGblConfigPtr = Config;

      /* Call global initialization function */
      /* [cover parentID={365D29BD-D7A0-4171-A75D-98441782984B}]
      Call Global Initialization Function
      [/cover] */
      ApiStatus = Can_17_McmCan_lGlobalInit(Config);
    }

    /* [cover parentID={58FF9C64-0B92-4702-ACBD-74BB91604F41}]
    Check if master core allocation equals   STD_ON?
    [/cover] */
    #if (CAN_17_MCMCAN_MASTER_CORE_ALLOCATION == STD_OFF)
    else
    #else
    /*Return valure of global initialization to be validated*/
    /* [cover parentID={385BB402-BB7C-4728-B54E-62D6C1ABB764}]
    Is the global initialization done successfully?
    [/cover] */
    if(E_OK == ApiStatus)
    #endif
    {
      /* Extract the global core state variable */
      CoreGlobalPtr = Can_17_McmCan_GblCoreState[CoreIndex];

      /* Core specific configuration structure extracted */
      CoreConfigPtr = Config->CanCoreConfigPtr[CoreIndex];

      /* Call core specific Initialization function */
      /* [cover parentID={AA5CE85F-0158-4c85-80EB-B27C0E43E9D8}]
      Call core specific Initialization function
      [/cover] */
      ApiStatus = Can_17_McmCan_lCoreInit(CoreConfigPtr, CoreGlobalPtr);
    }
  }
  /* Check all the initial settings are done successfully */
  /* [cover parentID={42075D10-4075-4c99-BF15-2909396B7001}]
  If all the initial settings are done successfully
  [/cover] */
  if (E_OK == ApiStatus)
  {
    /* Set with Driver status as READY*/
    /* [cover parentID={01C0A3ED-D171-4cb6-BC94-7C206F04B658}]
    Set with Driver status as CAN_17_MCMCAN_READY
    [/cover] */
    Mcal_SetBitAtomic((sint32 *)(void *)&Can_17_McmCan_InitStatus,
           (sint32)(CoreIndex * (sint32)CAN_17_MCMCAN_INIT_STATUS_SIZE),
           CAN_17_MCMCAN_INIT_STATUS_SIZE, (uint32)(CAN_17_MCMCAN_DRV_READY));
  }
}

#if ((CAN_17_MCMCAN_SET_BAUDRATE_API == STD_ON) && \
(MCAL_AR_VERSION == MCAL_AR_422))
/******************************************************************************
**Traceability    : [cover parentID={D186055C-2A14-4cb0-807C-AD0F41D3B1C8}]  **
**                                                                           **
** Syntax           : Std_ReturnType Can_17_McmCan_CheckBaudrate             **
**                    (                                                      **
**                      const uint8 Controller,                              **
**                      const uint16 Baudrate                                **
**                    )                                                      **
**                                                                           **
** Description      : The function checks the baud rate of the CAN           **
**                    controller.                                            **
** [/cover]                                                                  **
**                                                                           **
** Service ID       : 0x0E                                                   **
**                                                                           **
** Sync/Async       : Synchronous                                            **
**                                                                           **
** Reentrancy       : Reentrant for different controller.                    **
**                    Non reentrant for same controller.                     **
**                                                                           **
** Parameters (in)  : Controller - Associated CAN Controller                 **
**                    Baudrate -  Baudrate to be checked                     **
**                                                                           **
** Parameters (out) : none                                                   **
**                                                                           **
** Return value     : E_OK: Service request accepted, checking of            **
**                    baud rate started.                                     **
**                    E_NOT_OK: Service request not accepted or DET occured  **
******************************************************************************/
Std_ReturnType Can_17_McmCan_CheckBaudrate(const uint8 Controller,
                                           const uint16 Baudrate)
{
  /* Variable to store the return value*/
  Std_ReturnType ApiStatus = E_NOT_OK;

  /* Offset for the end index of the baud rate configurations */
  uint16 EndBaudrateCfgIndx;

  /* start index of the baudrate configuration for this controller */
  uint16 StartBaudrateCfgIndx;

  /* Condition to break the while loop */
  uint8 LoopBreak;

  /* calling core index */
  uint8 CoreIndex;

  /* controller index counter */
  uint8 ContIndx;

  /* core specifc configuration */
  const Can_17_McmCan_CoreConfigType *ConfigPtr;

  /* Set with Value ZERO */
  LoopBreak = 0U;

  /* Get core id which is executing currently */
  CoreIndex = CAN_17_MCMCAN_GETCOREINDEX;

  /*Check if DET is enabled*/
  /* [cover parentID={FD38CAC0-3C12-45c0-A196-36A9B59A36C9}]
  Check if DET is enabled
  [/cover] */
  #if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON)

  /* Check if driver is initilaized */
  /* [cover parentID={C7E22275-4959-4b97-829D-5989A492D844}]
  Invoke the function to perform DET check and reporting if the driver is
  not initialized
  [/cover] */
  ApiStatus = Can_17_McmCan_lDetUninitConfig(CAN_17_MCMCAN_SID_CHECKBAUDRATE,
                                             CoreIndex);

  /* [cover parentID={7EA31E31-610D-4c99-AE2E-C13DE62B0DD4}]
  Is the driver initialized?
  [/cover] */
  if (E_OK == ApiStatus)
  {
    /* Check the requested controllerId is Valid and configured */
    /* [cover parentID={282ACAB9-14A6-4054-A4C4-6FD3A7576464}]
    Is the controller is valid ?
    [/cover] */
    ApiStatus = Can_17_McmCan_lDetParamController(CoreIndex, Controller,
                                            CAN_17_MCMCAN_SID_CHECKBAUDRATE);
  }

  /*Check if DET checks have passed*/
  /* [cover parentID={5149A284-26BF-41e5-8066-942958454C43}]
  Check if the error checks have passed
  [/cover] */
  if (E_OK == ApiStatus)
  #endif /* #if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Local copy of the core specific configuration */
    ConfigPtr = Can_17_McmCan_kGblConfigPtr->CanCoreConfigPtr[CoreIndex];

    /* Retrieve the kernel index offset for the core */
    ContIndx = Can_17_McmCan_kGblConfigPtr->
               CanLogicalControllerIndexPtr[Controller].CanLCoreSpecContIndex;

    /* Set Start index */
    StartBaudrateCfgIndx = ConfigPtr->
        CanControllerConfigPtr[ContIndx].CanBaudrateCfgIndx;

    /* Set with Total no of baudrate index */
    EndBaudrateCfgIndx = ConfigPtr->
        CanControllerConfigPtr[ContIndx].CanNoOfBaudrateCfg;
    /* [cover parentID={B0CF1D1A-E385-4b11-9E83-D64EFA82426D}]
    Check for all baud rate configurations
    [/cover] */
    while ((EndBaudrateCfgIndx > 0U) && (LoopBreak == 0U))
    {
      /* Check if requested baudrate is supported by the controller*/
      /* [cover parentID={A4577460-515B-49e4-9EB1-28097C3E0E8B}]
      Is the requested baudrate supported by the controller?
      [/cover] */
      if (Baudrate ==
          ConfigPtr->CanBaudrateConfigPtr[StartBaudrateCfgIndx].CanBaudrateCfg)
      {
        LoopBreak = 1U;
      }
      else
      {
        /* point to next baud-rate configuration */
        StartBaudrateCfgIndx++;
      }
      /* Decrement the configuration count */
      EndBaudrateCfgIndx--;
    }

    /* Check Loop break Status */
    /* [cover parentID={9865CADD-962A-4a23-B58B-1CA602FDD730}]
    Has the loop has been terminated due to invalid baud rate request?
    [/cover] */
    if (LoopBreak == 0U)
    {
      /* [cover parentID={54905E2E-ED5E-48d2-9F16-4182EB1F3C74}]
      DET is enabled
      [/cover] */
      #if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON)
      /* Report invalid baudrate to DET */
      /* [cover parentID={31F9D858-BDBD-46c5-9B70-1D4BD3A27217}]
      Report error CAN_17_MCMCAN_E_PARAM_BAUDRATE
      [/cover] */
      (void)Det_ReportError(CAN_17_MCMCAN_MODULE_ID, CAN_17_MCMCAN_INSTANCE_ID,
                            CAN_17_MCMCAN_SID_CHECKBAUDRATE,
                            CAN_17_MCMCAN_E_PARAM_BAUDRATE);
      #endif

      /* Set as not supported */
      ApiStatus = E_NOT_OK;
    }
    else
    {
      ApiStatus = E_OK;
    }
  }
  /* [cover parentID={2B1608EE-3E93-4b79-B8A9-A34CFD0CAF44}]
  Return the status of the service as E_NOT_OK
  [/cover] */
  return ApiStatus;
}

#endif /*End of #if ((CAN_17_MCMCAN_SET_BAUDRATE_API == STD_ON) && \
(MCAL_AR_VERSION == MCAL_AR_422))*/

#if (CAN_17_MCMCAN_SET_BAUDRATE_API == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={56D0417E-7E0D-4304-A6C8-90C6613023D9}]   **
**                                                                            **
**  Syntax           : Std_ReturnType Can_17_McmCan_SetBaudrate               **
**                    (                                                       **
**                     const uint8 Controller,                                **
**                     const uint16 BaudRateConfigID                          **
**                    )                                                       **
**                                                                            **
**  Description      : The function sets the baud rate configuration of the   **
**                     CAN controller during runtime when the CAN controller  **
**                     is in STOPPED state.                                   **
**                     The Can_17_McmCan_SetBaudrate() function is available  **
**                     only when CanSetBaudrateApi is enabled.                **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : 0x0F                                                   **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant for different controllers.                   **
**                     Non reentrant for the same controller.                 **
**                                                                            **
**  Parameters (in)  : Controller - CAN controller for which the, baud rate   **
**                    needs to be set                                         **
**                    BaudRateConfigID - References a baud rate configuration **
**                    by ID                                                   **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : E_OK: Service request accepted, setting of new baud    **
**                     rate started                                           **
**                     E_NOT_OK: Service request not accepted, or,            **
**                     development error reported.                            **
*******************************************************************************/
Std_ReturnType Can_17_McmCan_SetBaudrate(const uint8 Controller,
                                         const uint16 BaudRateConfigID)
{
  /* return value variable */
  Std_ReturnType ApiStatus = E_NOT_OK;

  /* calling core index */
  uint8 CoreIndex;

  /* controller index counter */
  uint8 ContIndx;

  /* core specifc configuration */
  const Can_17_McmCan_CoreConfigType *ConfigPtr;

  /* core specifc global variable structure */
  const Can_17_McmCan_CoreGlobalType *CoreGlobalPtr;

  /* Get core id which is executing currently */
  CoreIndex = CAN_17_MCMCAN_GETCOREINDEX;

  /*Check if DET is configured*/
  /* [cover parentID={F198BB9F-E919-417e-981B-AAC1306B8793}]
  Check if DET is enabled
  [/cover] */
  #if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON)

  /*Check if the driver is initialized*/
  /* [cover parentID={A38611DD-E2C1-4901-8712-9DE70BA7A92F}]
  Invoke the function to perform DET check and reporting if the driver
  is not initialized
  [/cover] */
  ApiStatus = Can_17_McmCan_lDetUninitConfig(CAN_17_MCMCAN_SID_SETBAUDRATE,
                                             CoreIndex);

  /*If DET check retruns no error*/
  /* [cover parentID={A9730BA3-104D-4a46-A916-1A5C7749C0D2}]
  Is the driver initialized?
  [/cover] */
  if (E_OK == ApiStatus)
  {
    /* Check the requested controllerId is Valid and configured */
    /* [cover parentID={CB0C342F-BD1C-41da-80EB-BAD62381F003}]
    Invoke the function to perform DET check and reporting if the controller
    passed is not valid
    [/cover] */
    ApiStatus = Can_17_McmCan_lDetParamController(CoreIndex, Controller,
                                                CAN_17_MCMCAN_SID_SETBAUDRATE);
  }

  /*If DET check retruns no error*/
  /* [cover parentID={D9EA81AD-42D5-42f1-A3EC-3683071A1DBB}]
  Is the controller ID valid?
  [/cover] */
  if (E_OK == ApiStatus)
  {
    /* Retrieve the controller index offset for the core */
    ContIndx = Can_17_McmCan_kGblConfigPtr->
               CanLogicalControllerIndexPtr[Controller].CanLCoreSpecContIndex;

    /* Check if baudrate config ID is supported/configured */
    /* [cover parentID={832137E8-E200-46db-94F9-DA2575D59A18}]
    Is the Baudrate config ID valid?
    [/cover] */
    if (BaudRateConfigID >= Can_17_McmCan_kGblConfigPtr->
        CanCoreConfigPtr[CoreIndex]->
        CanControllerConfigPtr[ContIndx].CanNoOfBaudrateCfg)
    {
      /* Report invalid baudrate to DET */
      /* [cover parentID={A62338AA-1D66-476f-974B-C7D1480CDC74}]
      Report DET error CAN_17_MCMCAN_E_PARAM_BAUDRATE
      [/cover] */
      (void)Det_ReportError(CAN_17_MCMCAN_MODULE_ID,
                           CAN_17_MCMCAN_INSTANCE_ID,
                           CAN_17_MCMCAN_SID_SETBAUDRATE,
                           CAN_17_MCMCAN_E_PARAM_BAUDRATE);

      /* Set return value with NOT_OK */
      ApiStatus = E_NOT_OK;
    }
  }
  if (E_OK == ApiStatus)
  #endif /* #if(CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Local copy of the core specific configuration */
    ConfigPtr = Can_17_McmCan_kGblConfigPtr->CanCoreConfigPtr[CoreIndex];

    /* Local copy of the core specific global states */
    CoreGlobalPtr = Can_17_McmCan_GblCoreState[CoreIndex];

    /* Retrieve the controller index offset for the core */
    ContIndx = Can_17_McmCan_kGblConfigPtr->
               CanLogicalControllerIndexPtr[Controller].CanLCoreSpecContIndex;

    /*Check Can Controller Mode*/
    /* [cover parentID={1A0D993A-7642-4e1f-B5F4-B13077DC2131}]
    Check Can Controller Mode
    [/cover] */
    if (CAN_17_MCMCAN_STOPPED == CoreGlobalPtr->CanControllerModePtr[ContIndx])
    {
      /* Set Baudrate of requested controller */
      /* [cover parentID={5315F5C7-9322-4d21-86F3-278A00D47848}]
      Set Baud rate of requested controller
      [/cover] */
      ApiStatus = Can_17_McmCan_lSetBaudrate(ContIndx, BaudRateConfigID,
                                             ConfigPtr);
    }
    else
    {
       /* Set return value with NOT_OK */
       /* [cover parentID={BAFDCD11-604E-4f70-90CD-02973F4FF4A0}]
       Set the return status as  E_NOT_OK
       [/cover] */
       ApiStatus = E_NOT_OK;
    }
  }

  /*Return the API status*/
  /* [cover parentID={FE22D591-87AA-403e-9FF4-BFD458721A12}]
  Return the status
  [/cover] */
  return ApiStatus;
}
#endif

/*******************************************************************************
** Traceability   : [cover parentID={10315407-9F74-45ef-AC03-36E1505C5B44}]   **
**                                                                            **
**  Syntax           : Can_ReturnType Can_17_McmCan_SetControllerMode         **
**                    (                                                       **
**                      const uint8 Controller,                               **
**                      const Can_StateTransitionType Transition              **
**                    )                                                       **
**                                                                            **
**  Description      : The function performs software triggered state         **
**                      transitions of the CAN controller State machine.      **
**                     The function is implemented synchronous as the change  **
**                     in the mode is done synchronously by the hardware.     **
**                     This is a deviation from AUTOSAR.                      **
**                      Also there is no HW support to wakeup the controller, **
**                     it is only logical sleep which is implemented in driver**
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : 0x03                                                   **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Non-Reentrant                                          **
**                                                                            **
**  Parameters (in)  :Controller - CAN controller for which the controller    **
**                    mode status shall be changed                            **
**                    Transition - Requested transition                       **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : CAN_OK: Service request accepted, state transition     **
**                     successful                                             **
**                     CAN_NOT_OK: Service request not accepted, or,          **
**                     development error reported.                            **
**                                                                            **
*******************************************************************************/

#if (MCAL_AR_VERSION == MCAL_AR_422)
Can_ReturnType Can_17_McmCan_SetControllerMode(const uint8 Controller,
                                               const Can_StateTransitionType
                                               Transition)
{
  /*Variable to store return value of the API*/
  Can_ReturnType ApiStatus;

  /*Variable to evaluate the return value from local functions*/
  Std_ReturnType ReturnValue;

  /*Variable to store state transition values*/
  Can_17_McmCan_ControllerState StateTransition = Transition;

  /*Invoke state transition request*/
  /* [cover parentID={298464FC-273C-4b4c-98CD-D6495306DCD8}]
  Invoke the function to set controller mode
  [/cover] */
  ReturnValue = Can_17_McmCan_lSetControllerMode(Controller, StateTransition);

  /*Check if state transition was successful*/
  /* [cover parentID={8640392A-734B-4eb9-99EA-DD652BD52979}]
  Check if state transition was successful?
  [/cover] */
  if (E_OK == ReturnValue)
  {
     ApiStatus = CAN_OK;
  }
  else
  {
     ApiStatus = CAN_NOT_OK;
  }
  return ApiStatus;
}
#else
/*******************************************************************************
** Traceability   : [cover parentID={21279E11-3BF3-4092-97DF-CA281356C98C}]   **
**                                                                            **
**  Syntax           : Std_ReturnType Can_17_McmCan_SetControllerMode         **
**                    (                                                       **
**                      const uint8 Controller,                               **
**                      const Can_ControllerStateType Transition              **
**                    )                                                       **
**                                                                            **
**  Description      : The function performs software triggered state         **
**                      transitions of the CAN controller State machine.      **
**                     The function is implemented synchronous as the change  **
**                     in the mode is done synchronously by the hardware.     **
**                     This is a deviation from AUTOSAR.                      **
**                      Also there is no HW support to wakeup the controller, **
**                     it is only logical sleep which is implemented in driver**
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : 0x03                                                   **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Non-Reentrant                                          **
**                                                                            **
**  Parameters (in)  :Controller - CAN controller for which the controller    **
**                    mode status shall be changed                            **
**                    Transition - Requested transition                       **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : E_OK: Service request accepted, state transition       **
**                     successful                                             **
**                     E_NOT_OK: Service request not accepted, or,            **
**                     development error reported.                            **
**                                                                            **
*******************************************************************************/

Std_ReturnType Can_17_McmCan_SetControllerMode(const uint8 Controller,
                                               const Can_ControllerStateType
                                               Transition)
{
    /*Variable to store return value of the API*/
    Std_ReturnType ApiStatus = E_NOT_OK;

    /*Variable to store state transition values*/
    Can_17_McmCan_ControllerState StateTransition = Transition;

    /*Invoke state transition request*/
    /* [cover parentID={5C4EB3F4-6B29-4f3b-8DC6-00A0036CA2BC}]
    Invoke the function to set the controller mode
    [/cover] */
    ApiStatus = Can_17_McmCan_lSetControllerMode(Controller, StateTransition);

    return ApiStatus;
}
#endif

/*******************************************************************************
** Traceability   : [cover parentID={88889393-8A52-4a81-98E6-A7FF930AC5F0}]   **
**                                                                            **
**  Syntax           : void Can_17_McmCan_DisableControllerInterrupts         **
**                    (                                                       **
**                      const uint8 Controller                                **
**                    )                                                       **
**                                                                            **
**  Description      : The function disables all interrupts for the given     **
**                     CAN controller                                         **
**                                                                            **
**  Service ID       : 0x04                                                   **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant                                              **
**                                                                            **
**  Parameters (in)  : Controller - CAN controller for which interrupts       **
**                     need to be disabled                                    **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
void Can_17_McmCan_DisableControllerInterrupts(const uint8 Controller)
{
  /* calling core index */
  uint8 CoreIndex;

  /* Core specific controller index */
  uint8 ControllerIndex;

  /* current IE value */
  uint32 IEvalueTemp;

  /* Configured interrupt mask */
  uint32 InterruptMask;

  /* core specifc configuration */
  const Can_17_McmCan_CoreConfigType *CoreConfigPtr;

  /* core specifc global variable structure */
  const Can_17_McmCan_CoreGlobalType *CoreGlobalPtr;

   /*Can controller node address pointer*/
  volatile Ifx_CAN_N *NodeRegAddressPtr;

  #if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON)

  /*Return value of the error checks*/
  Std_ReturnType ApiStatus = E_NOT_OK;
  #endif

  /* Get core id which is executing currently */
  CoreIndex = CAN_17_MCMCAN_GETCOREINDEX;

  /* [cover parentID={C8563E01-AACB-4ffe-B54C-110D5FD7D7FB}]
  Check if DET is enabled
  [/cover] */
  #if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON)
  /* Check if status is initilaized */
  /* [cover parentID={C8BADA98-6FC9-49de-B61C-9EEF1AC324B6}]
  Invoke the function to perform DET check and reporting if the driver is
  not initialized
  [/cover] */
  ApiStatus = Can_17_McmCan_lDetUninitConfig(
                                  CAN_17_MCMCAN_SID_DISABLECONTROLLERINTERRUPTS,
                                  CoreIndex);

  /*if status ok*/
  /* [cover parentID={A213EC1C-7237-4112-BB1C-11D56EF1C794}]
  Is the driver initialized?
  [/cover] */
  if (E_OK == ApiStatus)
  {

    /* Check if requested Controller is valid */
    /* [cover parentID={19E68920-CE83-4a93-B207-1C6CF6A7BEB5}]
    Invoke the function to perform DET check and reporting if the controller
    passed is not valid
    [/cover] */
    ApiStatus = Can_17_McmCan_lDetParamController(CoreIndex, Controller,
                                 CAN_17_MCMCAN_SID_DISABLECONTROLLERINTERRUPTS);
  }

  /*Controller validity return value*/
  /* [cover parentID={EDF457F7-0A35-4206-A16D-AB2EE6656214}]
  Is the controller is valid?
  [/cover] */
  if (E_OK == ApiStatus)
  #endif /* #if(CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Local copy of the core specific configuration */
    CoreConfigPtr = Can_17_McmCan_kGblConfigPtr->CanCoreConfigPtr[CoreIndex];

    /* Retrieve the controller index offset for the core */
    ControllerIndex = Can_17_McmCan_kGblConfigPtr->
               CanLogicalControllerIndexPtr[Controller].CanLCoreSpecContIndex;

    /* Read the exact Node Start address */
    NodeRegAddressPtr = CoreConfigPtr->
                        CanControllerConfigPtr[ControllerIndex].CanNodeAddressPtr;

    /* Local copy of the core specific global states */
    CoreGlobalPtr = Can_17_McmCan_GblCoreState[CoreIndex];

    /*Check Disable interrupt count is at reset value*/
    /* [cover parentID={10888F53-B131-40ae-A8C7-4B89A0F121AD}]
    Check the count of the disable interrupt calls if they are at the reset
    value
    [/cover] */
    if (0U == CoreGlobalPtr->CanDisableIntrpCountPtr[ControllerIndex])
    {

      /* read the current value of IE */
      IEvalueTemp = NodeRegAddressPtr->IE.U;

      /* read interrupt mask */
      InterruptMask = CoreConfigPtr->
          CanControllerConfigPtr[ControllerIndex].CanEnableInterruptMask;

      /* calculate disable mask to be used */
      IEvalueTemp = IEvalueTemp & (~InterruptMask);

      /* Disable controller interrupts */
      NodeRegAddressPtr->IE.U = IEvalueTemp;
    }

    /* Count the number of times Can_17_McmCan_DiableControllerInterrupts API
    is called */
    CoreGlobalPtr->CanDisableIntrpCountPtr[ControllerIndex]++;
  }
}

/*******************************************************************************
** Traceability   : [cover parentID={62DE3D9D-C847-4f77-B002-0EC887A129AB}]   **
**                                                                            **
**  Syntax           : void Can_17_McmCan_EnableControllerInterrupts          **
**                    (                                                       **
**                      const uint8 Controller                                **
**                    )                                                       **
**                                                                            **
**  Description      : The functions re-enables the allowed interrupts of     **
**                     the given CAN controller                               **
**                                                                            **
**  Service ID       : 0x05                                                   **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant                                              **
**                                                                            **
**  Parameters (in)  : Controller - CAN controller for which interrupts shall **
**                     be re-enabled                                          **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
void Can_17_McmCan_EnableControllerInterrupts(const uint8 Controller)
{
  /* Local variable to store the core index*/
  uint8 CoreIndex;

  /* Core specific controller index */
  uint8 ControllerIndex;

  /* core specifc configuration */
  const Can_17_McmCan_CoreConfigType *CoreConfigPtr;

  /*Can controller node address pointer*/
  volatile Ifx_CAN_N *NodeRegAddressPtr;

  /* core specifc global variable structure */
  const Can_17_McmCan_CoreGlobalType *CoreGlobalPtr;

  /* Get core id which is executing currently */
  CoreIndex = CAN_17_MCMCAN_GETCOREINDEX;

  /*Is DET enabled*/
  /* [cover parentID={ADCCC99D-104C-413e-A4A7-F83EAD748A14}]
  Check if DET is enabled
  [/cover] */
  #if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON)

  /*Variable to store the return value*/
  Std_ReturnType ApiStatus = E_NOT_OK;

  /*Check if the driver is initialized*/
  /* [cover parentID={BFAB4B15-FC23-4043-A1CC-3028D65120E4}]
  Invoke the function to perform DET check and reporting if the driver is
  not initialized
  [/cover] */
  ApiStatus = Can_17_McmCan_lDetUninitConfig(
                                   CAN_17_MCMCAN_SID_ENABLECONTROLLERINTERRUPTS,
                                   CoreIndex);

  /*Has the check passed*/
  /* [cover parentID={A69F5DC2-D3AF-4f9f-AD54-25854B5F177D}]
  Is the driver initialized?
  [/cover] */
  if (E_OK == ApiStatus)
  {
    /* Check if requested Controller is valid */
    /* [cover parentID={920BFF81-A655-4e2d-ADF6-0223524D241A}]
    Invoke the function to perform DET check and reporting if the controller
    passed is not valid
    [/cover] */
    ApiStatus = Can_17_McmCan_lDetParamController(CoreIndex, Controller,
                                  CAN_17_MCMCAN_SID_ENABLECONTROLLERINTERRUPTS);
  }
  /*Controller validity return value*/
  /* [cover parentID={CBA1EB3E-CF16-4216-BFDD-E98DED68884F}]
  Is the controller valid?
  [/cover] */
  if (E_OK == ApiStatus)
  #endif /* #if(CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON) */
  {

    /* Local copy of the core specific global states */
    CoreGlobalPtr = Can_17_McmCan_GblCoreState[CoreIndex];

    /* Local copy of the core specific configuration */
    CoreConfigPtr = Can_17_McmCan_kGblConfigPtr->CanCoreConfigPtr[CoreIndex];

    /* Retrieve the controller index offset for the core */
    ControllerIndex = Can_17_McmCan_kGblConfigPtr->
               CanLogicalControllerIndexPtr[Controller].CanLCoreSpecContIndex;

    /* Read the exact Node Start address */
    NodeRegAddressPtr = CoreConfigPtr->
                        CanControllerConfigPtr[ControllerIndex].CanNodeAddressPtr;


    /* Check Can_17_McmCan_DisableControllerInterrupts has been called before,If
     no then don't perform any action. */
    /* [cover parentID={0EAFB8A9-B109-404e-AA36-F2B90BA11BA3}]
    Check if the value of the disable interrupt counter is greater than
    reset value?
    [/cover] */
    if (CoreGlobalPtr->CanDisableIntrpCountPtr[ControllerIndex] > 0U)
    {
      /* Incremental interrupt disable/enable count */
      CoreGlobalPtr->CanDisableIntrpCountPtr[ControllerIndex]--;

      /* [cover parentID={D0735D9D-222C-4bb2-9518-4D4BDA150616}]
      Check if the value of the disable interrupt counter is equal to
      reset value?
      [/cover] */
      if (CoreGlobalPtr->CanDisableIntrpCountPtr[ControllerIndex] == 0U)
      {
        /* Enable Controller Interrupts */
        NodeRegAddressPtr->IE.U |= CoreConfigPtr->
        CanControllerConfigPtr[ControllerIndex].CanEnableInterruptMask;
      }

    }
  }
}

/*******************************************************************************
** Traceability   : [cover parentID={CFC67599-E6B0-4ecd-9618-5CF8729B0119}]   **
**                                                                            **
**  Syntax           : Can_ReturnType Can_17_McmCan_Write                     **
**                    (                                                       **
**                      const Can_HwHandleType Hth,                           **
**                      const Can_PduType *const PduInfo                      **
**                    )                                                       **
**                                                                            **
**  Description   :This function is used to transmit CAN/CAN FD frame based   **
**                 on the information passed to it. The CAN driver will only  **
**                 transmit messages with remote transmission request (RTR)   **
**                 bit at reset state (that is, no remote transmission request**
**                 will be accepted by the CAN driver).                       **
**                                                                            **
**  [/cover]                                                                  **
**  Service ID       : 0x06                                                   **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant(thread-safe)                                 **
**                                                                            **
** Parameters(in)   :Hth - Information which hardware transmit handle should  **
**                   be used for transmit. Implicitly this is also the        **
**                   information about the controller to use because the Hth  **
**                   numbers are unique inside a hardware unit.,              **
**                   PduInfo - Pointer to the SDU user memory, DLC and        **
**                   Identifier                                               **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : CAN_OK: Write command accepted, write is successful    **
**                     CAN_NOT_OK: Service request not successful, or,        **
**                     development error reported.                            **
**                     CAN_BUSY: No TX hardware buffer available or           **
**                     pre-emptive call of Can_Write that cannot be           **
**                     implemented re-entrant.                                **
**                                                                            **
*******************************************************************************/
#if (MCAL_AR_VERSION == MCAL_AR_422)
Can_ReturnType Can_17_McmCan_Write(const Can_HwHandleType Hth,
                                   const Can_PduType *const PduInfo)
{
  /*Return value of the function*/
  Can_17_McmCan_ReturnValueType ReturnValue = CAN_17_MCMCAN_NOT_OK;

  Can_ReturnType ApiStatus = CAN_NOT_OK;

  /*Return value after Can write is performed*/
  /* [cover parentID={A5D0A058-E87C-4248-902C-43B83EDACC1C}]
  Invoke the function to perform write
  [/cover] */
  ReturnValue = Can_17_McmCan_lWrite(Hth, PduInfo);

  /*Check if the return value is OK*/
  /* [cover parentID={C0BF4BF7-F9C0-4375-9AF6-51CB7A6E23A5}]
  Check if the return value is CAN_17_MCMCAN_OK
  [/cover] */
  if (CAN_17_MCMCAN_OK == ReturnValue)
  {
    ApiStatus = CAN_OK;
  }
  /* [cover parentID={65E5B418-1441-4af4-8CDE-34EBB0129E31}]
  Check if the return value is CAN_17_MCMCAN_NOT_OK
 [/cover] */
  else if (CAN_17_MCMCAN_NOT_OK == ReturnValue)
  {
    ApiStatus = CAN_NOT_OK;
  }
  /* [cover parentID={79A1F00C-9318-4fb7-AAEF-EB5C865E70CC}]
  Check if the return value is CAN_17_MCMCAN_BUSY
  [/cover] */
  else
  {
    ApiStatus = CAN_BUSY;
  }

  return ApiStatus;
}

#else

/*******************************************************************************
** Traceability   : [cover parentID={34B81560-627B-4a17-8448-C627E255D307}]   **
**                                                                            **
**  Syntax        : Std_ReturnType Can_17_McmCan_Write                        **
**                  (                                                         **
**                    const Can_HwHandleType Hth,                             **
**                    const Can_PduType *const PduInfo                        **
**                  )                                                         **
**                                                                            **
**  Description   :This function is used to transmit CAN/CAN FD frame based   **
**                 on the information passed to it. The CAN driver will only  **
**                 transmit messages with remote transmission request (RTR)   **
**                 bit at reset state (that is, no remote transmission request**
**                 will be accepted by the CAN driver).                       **
**                                                                            **
**  [/cover]                                                                  **
**  Service ID       : 0x06                                                   **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant(thread-safe)                                 **
**                                                                            **
** Parameters(in)   :Hth - Information which hardware transmit handle should  **
**                   be used for transmit. Implicitly this is also the        **
**                   information about the controller to use because the Hth  **
**                   numbers are unique inside a hardware unit.,              **
**                   PduInfo - Pointer to the SDU user memory, DLC and        **
**                   Identifier                                               **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : E_OK: Write command accepted, write is successful      **
**                     E_NOT_OK: Service request not successful, or,          **
**                     development error reported.                            **
**                     CAN_BUSY: No TX hardware buffer available or           **
**                     pre-emptive call of Can_Write that cannot be           **
**                     implemented re-entrant.                                **
**                                                                            **
*******************************************************************************/
Std_ReturnType Can_17_McmCan_Write(const Can_HwHandleType Hth,
                                   const Can_PduType *const PduInfo)
{
  /*Return value of type Can_17_McmCan_ReturnValueType*/
  Can_17_McmCan_ReturnValueType ReturnValue;

  /*API return value*/
  Std_ReturnType ApiStatus = E_NOT_OK;

  /*Return value after Can write is performed*/
  /* [cover parentID={B5AB7E3C-B24F-47ad-80E1-1002B15C4D08}]
  Invoke the function to perform write
  [/cover] */
  ReturnValue = Can_17_McmCan_lWrite(Hth, PduInfo);

  /*Check if the return value is OK*/
  /* [cover parentID={8F908949-988C-462e-B2A2-8F530A150B33}]
  Check if the return value is CAN_17_MCMCAN_OK
  [/cover] */
  if (CAN_17_MCMCAN_OK == ReturnValue)
  {
    ApiStatus = E_OK;
  }

  /* [cover parentID={8F2DC3E4-6BAE-48a2-8437-A8840BCDE130}]
  Check if the return value is CAN_17_MCMCAN_NOT_OK
  [/cover] */
  else if (CAN_17_MCMCAN_NOT_OK == ReturnValue)
  {
    ApiStatus = E_NOT_OK;
  }

  /* [cover parentID={238B404F-E301-4a69-B90D-86944AA29375}]
  Check if the return value is CAN_17_MCMCAN_BUSY
  [/cover] */
  else
  {
    ApiStatus = CAN_BUSY;
  }

  return ApiStatus;
}

#endif

#if (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={B6D12824-46DD-40e0-9479-46512A0EC7D1}]   **
**                                                                            **
**  Syntax           : Std_ReturnType Can_17_McmCan_SetIcomConfiguration      **
**                   (                                                        **
**                     const uint8 Controller,                                **
**                     const IcomConfigIdType ConfigurationId                 **
**                   )                                                        **
**                                                                            **
**  Description      : The API should change the Icom configuration of a CAN  **
**                     controller to the requested one. The function is       **
**                     available only when CanPublicIcomSupport is enabled.   **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : 0x21                                                   **
**                                                                            **
**  Sync/Async       : Asynchronous                                           **
**                                                                            **
**  Reentrancy       : Reentrant for different Controllers.                   **
**                     Non reentrant for the same controller.                 **
**                                                                            **
**  Parameters (in)  : Controller - CAN controller for which the status       **
**                     shall be changed.                                      **
**                    ConfigurationId - Requested configuration.              **
**                    An ID greater than 0 identifies a configuration         **
**                    in which pretended networking is activated for the      **
**                    Controller. An ID value of 0 deactivates the pretended  **
**                    networking identifier that is activated for the         **
**                    Controller.                                             **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : E_OK: : CAN driver succeeded in setting a configuration**
**                     with a valid Configuration id.                         **
**                     E_NOT_OK: CAN driver failed to set a configuration with**
**                     a valid Configuration id, or, development error occured**
*******************************************************************************/
Std_ReturnType Can_17_McmCan_SetIcomConfiguration(const uint8 Controller,
    const IcomConfigIdType ConfigurationId)
{
  /* Return value of API */
  Std_ReturnType ApiStatus = E_NOT_OK;

  #if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType DetStatus = E_NOT_OK;
  #endif

  /* Icom error variable */
  IcomSwitch_ErrorType IcomError = ICOM_SWITCH_E_FAILED;

  /* calling core index */
  uint8 CoreIndex;

  /* Core specific controller index */
  uint8 ContIndx;

  /* core specifc configuration */
  const Can_17_McmCan_CoreConfigType *CoreConfigPtr;

  /* core specifc global variable structure */
  const Can_17_McmCan_CoreGlobalType *CoreGlobalPtr;

  /* Get core id which is executing currently */
  CoreIndex = CAN_17_MCMCAN_GETCOREINDEX;

  /*If DET is enabled*/
  /* [cover parentID={C449A2F4-7C94-4b2e-8139-812F8302A685}]
  Check if DET is enabled
  [/cover] */
  #if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON)

  /* Check if status is initilaized */
  /* [cover parentID={D5544DF7-28D3-4bbd-B958-BF824907C63F}]
  Check if the driver is uninitialized
  [/cover] */
  DetStatus = Can_17_McmCan_lDetUninitConfig(
                  CAN_17_MCMCAN_SID_SETICOMCONFIGURATION, CoreIndex);
  /* [cover parentID={B60E1836-222F-4c7e-B9FE-DF2796F81972}]
  Is the driver initialized?
  [/cover] */
  if (E_OK == DetStatus)
  {
    /* Check the requested controllerId is Valid or not */
    /* [cover parentID={3860BC51-40B2-44cf-A5D9-195BF6C1A1A5}]
    Check if the controller Id is valid or not
    [/cover] */
    DetStatus = Can_17_McmCan_lDetParamController(CoreIndex, Controller,
                CAN_17_MCMCAN_SID_SETICOMCONFIGURATION);
  }
  /* Check if configuration ID is valid */
  /* [cover parentID={BAF66F05-4975-445c-AD7C-10C5B469BACF}]
  ICOM configuration ID passed is valid
  [/cover] */
  if ((ConfigurationId > CAN_17_MCMCAN_NOOF_ICOM_CONFIGURATIONS) &&
      (E_OK == DetStatus))
  {

    /* Report invalid  configuration ID to DET */
    /* [cover parentID={59065786-EA5E-4b5e-AD12-EC2B58EC2601}]
    Det error CAN_E_ICOM_CONFIG_INVALID
    [/cover] */
    (void)Det_ReportError(CAN_17_MCMCAN_MODULE_ID, CAN_17_MCMCAN_INSTANCE_ID,
                          CAN_17_MCMCAN_SID_SETICOMCONFIGURATION,
                          CAN_17_MCMCAN_E_ICOM_CONFIG_INVALID);
    /* [cover parentID={9716C92B-C90D-4b57-908C-F6B9555BF4FA}]
    Return E_NOT_OK
    [/cover] */
    DetStatus = E_NOT_OK;
  }
  if (E_OK == DetStatus)
  #endif /* #if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Local copy of the core specific configuration */
    CoreConfigPtr = Can_17_McmCan_kGblConfigPtr->CanCoreConfigPtr[CoreIndex];

    /* Local copy of the core specific global states */
    CoreGlobalPtr = Can_17_McmCan_GblCoreState[CoreIndex];

    /* Retrieve the kernel index offset for the core */
    ContIndx = Can_17_McmCan_kGblConfigPtr->
               CanLogicalControllerIndexPtr[Controller].CanLCoreSpecContIndex;

    /* [cover parentID={3353F6BF-53BF-458b-B197-19076CAE705B}]
    Controller mode is STARTED and ICOM config pointer is not a NULL_PTR
    [/cover] */
    if ((CAN_17_MCMCAN_STARTED == CoreGlobalPtr->
          CanControllerModePtr[ContIndx]) &&
          (NULL_PTR != Can_17_McmCan_kGblConfigPtr->CanIcomConfigPtr))
    {
      /* [cover parentID={42EBE452-1686-4593-A7DB-DAF5AA9D9C97}]
      Is the ICOM configuration ID passed greater than ZERO?
      [/cover] */
      if (0U < (uint8)ConfigurationId)
      {
        /* Block Can_Writes once the I-com API is accepted */
        CoreGlobalPtr->CanIcomBlockWriteCallsPtr[ContIndx] = TRUE;

        /* Activate ICOM settings*/
        /* [cover parentID={CFCE76D6-AEB0-455c-AC11-70B8E42CF4F2}]
        Activate the ICOM settings
        [/cover] */
        Can_17_McmCan_lActivateIcom(ContIndx, ConfigurationId, CoreGlobalPtr,
        CoreConfigPtr);

        /* Set IcomError as ICOM_SWITCH_E_OK */
        IcomError = ICOM_SWITCH_E_OK;

        /* Set ApiStatus as E_OK */
        ApiStatus = E_OK;
      }
      /* Check if ICOM is enabled*/
      /* [cover parentID={675AECD8-F1E6-40e7-8F0B-F4DD4736F9D8}]
      Is ICOM Activated?
      [/cover] */
      else if (TRUE == CoreGlobalPtr->CanIcomEnableStatusPtr[Controller])
      {
        /* De Activate ICOM settings*/
        /* [cover parentID={FC1E24F4-75FC-45d9-83B5-934309C2B206}]
        Deactivate the ICOM settings
        [/cover] */
        Can_17_McmCan_lDeactivateIcom(ContIndx, CoreGlobalPtr,
                                      CoreConfigPtr);

        /* Set IcomError as ICOM_SWITCH_E_OK */
        /* [cover parentID={32A6F62D-2135-4f7c-9FB5-A200EB3C139D}]
        Set ICOM status to ICOM_SWITCH_E_OK
        [/cover] */
        IcomError = ICOM_SWITCH_E_OK;

        /* Set ApiStatus as E_OK */
        ApiStatus = E_OK;
      }
      else
      {

        /* Set IcomError as ICOM_SWITCH_E_FAILED */
        IcomError = ICOM_SWITCH_E_FAILED;
      }
    }
    else
    {
      /* Set IcomError as ICOM_SWITCH_E_FAILED */
      /* [cover parentID={67D050FB-2C63-4d4b-8E20-178756F7167C}]
      Set ICOM status as ICOM_SWITCH_E_FAILED
      [/cover] */
      IcomError = ICOM_SWITCH_E_FAILED;
    }

    /* Notify the upper layer */
    /* [cover parentID={6AF5732D-8D8D-485a-9AAC-BB4BD677B985}]
    Notify the upper layer
    [/cover] */
    CanIf_CurrentIcomConfiguration(Controller, ConfigurationId, IcomError);
  }

  return ApiStatus;
}
#endif

#if (CAN_17_MCMCAN_DEINIT_API == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={1720B00B-1498-4297-8799-1D5E2027A61A}]   **
**                                                                            **
**  Syntax           : void Can_17_McmCan_DeInit                              **
**                    (                                                       **
**                     void                                                   **
**                    )                                                       **
**                                                                            **
**  Description      :The function de-initializes all global variables and    **
**                    relevant registers of the MCMCAN                        **
**                    (based on configuration) assigned to that particular    **
**                    core with the values of structure referenced by the     **
**                    parameter ConfigPtr. Successful execution of this API   **
**                    will trigger a state transition of the CAN Driver state **
**                    machine from CAN_READY to CAN_UNINIT state.             **
**                    The Can_17_McmCan_DeInit() function is available only   **
**                    when CanDeInitApi is enabled. in case of AUTOSAR 4.2.2, **
**                    the parameter can be enabled or disabled.               **
**                    In AUTOSAR 4.4.0 the parameter will always generate     **
**                    TRUE and will be disabled.                              **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : 0x10                                                   **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Non-Reentrant                                          **
**                                                                            **
**  Parameters (in)  : none                                                   **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
void Can_17_McmCan_DeInit(void)
{
  /* calling core index */
  uint8 CoreIndex;

  /* Return value of error checks */
  Std_ReturnType Status = E_NOT_OK;


  #if (CAN_17_MCMCAN_MULTICORE_ERROR_DETECT == STD_ON)
  /*Expected init status*/
  uint32 ExpInitStatus;
  #endif

  /*Ponter to CAN kernel configuration*/
  Ifx_CAN *MCMBaseAddressPtr;

  /* MISRA2012_RULE_19_2_JUSTIFICATION:Union is used to access the register
  contents directly without shift and OR operation. */
  /*CLC value*/
  Ifx_CAN_CLC DataAddress_CLC;

  /* Variable to scan across the configured kernel set  */
  uint8 KernelIndx;

  /*Pointer to CAN config structure*/
  const Can_17_McmCan_CoreGlobalType *CoreGlobalPtr;

  /*Pointer to CAN core state structure*/
  const Can_17_McmCan_CoreConfigType *CoreConfigPtr;

  /* Get core id which is executing currently */
  CoreIndex = CAN_17_MCMCAN_GETCOREINDEX;

  /* [cover parentID={3D624900-890B-4ed6-ACA8-836B7DFE335B}]
  DET is enabled
  [/cover] */
  #if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON)

  /* Check if CAN driver is initialized */
  /* [cover parentID={7ABFA6CF-0E88-4d8d-A9E9-CCF95AC2D148}]
  Invoke the function to check if the CAN driver is initialized
  [/cover] */
  Status = Can_17_McmCan_lDetUninitConfig(CAN_17_MCMCAN_SID_DEINIT, CoreIndex);

  /* [cover parentID={01137BB7-D712-4ebe-A18A-CADC5D077B13}]
  Multicore error detection is enabled
  [/cover] */
  #if (CAN_17_MCMCAN_MULTICORE_ERROR_DETECT == STD_ON)

  /* Calculation for expected Initialization variable status in master core */
  ExpInitStatus = 1U << ((uint32)MCAL_MASTER_COREID *
                  (uint32)CAN_17_MCMCAN_INIT_STATUS_SIZE);

  /* Master core deinit called only after slave core deinit */
  /* [cover parentID={4AA986F4-1A5F-4e3d-8453-223BBD493C10}]
  Is the master core deinit called before the slave core deinit?
  [/cover] */
  if (MCAL_MASTER_COREID == CoreIndex)
  {
    /* [cover parentID={90C3F49A-0148-4af1-B324-51D70A20FF66}]
    Is the driver initialized?
    [/cover] */
    if ((E_OK == Status) && (Can_17_McmCan_InitStatus != ExpInitStatus))
    {
      /* Slave core uninitialized error */
      /* [cover parentID={9D5E628C-2B95-45b1-9A6F-6CB7CD04563E}]
      Det error CAN_17_MCMCAN_E_SLAVE_CORE_INIT
      [/cover] */
      (void)Det_ReportError(CAN_17_MCMCAN_MODULE_ID, CAN_17_MCMCAN_INSTANCE_ID,
                     CAN_17_MCMCAN_SID_DEINIT, CAN_17_MCMCAN_E_SLAVE_CORE_INIT);

      Status = E_NOT_OK;
    }
  }
  #endif /* #if(CAN_17_MCMCAN_MULTICORE_ERROR_DETECT == STD_ON) */
  /* [cover parentID={6F23E73C-F88B-428f-AF33-C26A5F5FC526}]
  Is the status E_OK?
  [/cover] */
  if (E_OK == Status)
  #endif /* #if(CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Extract the global core state variable */
    CoreGlobalPtr = Can_17_McmCan_GblCoreState[CoreIndex];

    /* Local copy of the core specific configuration */
    CoreConfigPtr = Can_17_McmCan_kGblConfigPtr->CanCoreConfigPtr[CoreIndex];

    /* [cover parentID={9B3923C6-8921-44f1-AE95-77B424EFA1E4}]
    If Master Core is selected
    [/cover] */
    if (MCAL_MASTER_COREID == CoreIndex)
    {
      /* [cover parentID={ECE56D5E-F20B-47e9-9056-619DEC35FE71}]
      Is Master core allocation STD_ON?
      [/cover] */
      #if (CAN_17_MCMCAN_MASTER_CORE_ALLOCATION == STD_ON)
      /* [cover parentID={71BE4312-8876-4186-BEC6-F393A9FE2F9C}]
      Check if the controller associated with core are in STARTED state
      [/cover] */
      Status = Can_17_McmCan_lCoreDeInit(CoreConfigPtr, CoreGlobalPtr);

       /* [cover parentID={F7EC6A49-C61F-4611-9E54-1C5E4E25C564}]
      Is the status E_OK?
      [/cover] */
      if (E_OK == Status)
      #endif
      {
        /* Set the status of the driver state machine as UNINIT*/
        /* [cover parentID={813EB0F0-5F6A-4c98-AFB4-3AFA80A75353}]
        Set with Driver status as UNINIT
        [/cover] */
        Mcal_SetBitAtomic((sint32 *)(void *)&Can_17_McmCan_InitStatus,
                      (sint32)(CoreIndex * CAN_17_MCMCAN_INIT_STATUS_SIZE),
                      CAN_17_MCMCAN_INIT_STATUS_SIZE,
                      (uint32)(CAN_17_MCMCAN_DRV_UNINIT));

        /*DeInitialize all clocks and globals*/
        /* [cover parentID={91B0921A-4464-40e5-9283-5F04A4B9B308}]
        Configured kernel loop
        [/cover] */
        for (KernelIndx = 0U; KernelIndx < Can_17_McmCan_kGblConfigPtr->
                                               CanNoOfKernel; KernelIndx++)
        {
          /* Set with Kernel base address */
          MCMBaseAddressPtr = Can_17_McmCan_kGblConfigPtr->
                              CanMCMModuleConfigPtr[KernelIndx].CanBaseAddressPtr;

          /* Take a copy of the resgiter values */
          DataAddress_CLC.U = MCMBaseAddressPtr->CLC.U;

          /* Set DISR bit in CLC register to Disable the CAN module  */
          DataAddress_CLC.B.DISR = CAN_17_MCMCAN_BIT_SET_VAL;

          /*Reset the kernel*/
          /* [cover parentID={F9EBC60A-1176-42b3-BCBA-8FBF6667888D}]
          Reset the KRSTCLR register
          [/cover] */
          CAN_17_MCMCAN_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(
              &(MCMBaseAddressPtr->KRSTCLR.U), CAN_17_MCMCAN_BIT_SET_VAL);

          /*Reset the kernel specific KRST0*/
          /* [cover parentID={26139B1F-CBB2-4abb-B29F-8109B7D0CE3D}]
          Reset the Kernel registers0
          [/cover] */
          CAN_17_MCMCAN_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(
              &(MCMBaseAddressPtr->KRST0.U),
              CAN_17_MCMCAN_BIT_SET_VAL);

          /*Reset the kernel specific KRST1*/
          /* [cover parentID={2C4DC05A-1C14-4ca1-A2F1-30C5DC095E2C}]
          Reset the Kernel registers1
          [/cover] */
          CAN_17_MCMCAN_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(
              &(MCMBaseAddressPtr->KRST1.U),
              CAN_17_MCMCAN_BIT_SET_VAL);

          /*Reset the clock*/
          /* [cover parentID={E16E705C-8A0C-4f31-87B5-049A464BE0C9}]
          Set DISR bit in CLC register to Disable the CAN module
          [/cover] */
          CAN_17_MCMCAN_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(
              &(MCMBaseAddressPtr->CLC.U),
              DataAddress_CLC.U);
        }
        Can_17_McmCan_kGblConfigPtr = NULL_PTR;
      }
    }
    else
    {
      /* [cover parentID={05D1C26A-A8B2-4967-BB44-C1C491A3B43D}]
      Check if the controller associated with core are in STARTED state
      [/cover] */
      Status = Can_17_McmCan_lCoreDeInit(CoreConfigPtr, CoreGlobalPtr);
      /* [cover parentID={F86682AA-295A-46fb-8D67-90A3E8CA5DB5}]
      Is the status  E_OK?
      [/cover] */
      if (E_OK == Status)
      {

        /* Set the status of the driver state machine as UNINIT*/
        /* [cover parentID={C9A9F291-DD58-43d1-AAA0-6E2D1A47E9E4}]
        Set with Driver status as UNINIT
        [/cover] */
        Mcal_SetBitAtomic((sint32 *)(void *)&Can_17_McmCan_InitStatus,
                      (sint32)(CoreIndex * CAN_17_MCMCAN_INIT_STATUS_SIZE),
                      CAN_17_MCMCAN_INIT_STATUS_SIZE,
                      (uint32)(CAN_17_MCMCAN_DRV_UNINIT));
      }
    }
  }
}
#endif /* (CAN_17_MCMCAN_DEINIT_API == STD_ON) */
#if (MCAL_AR_VERSION == MCAL_AR_440)
/*******************************************************************************
** Traceability   : [cover parentID={5326C908-7827-401b-9E0C-F44C30D5D9E8}]   **
**                                                                            **
**  Syntax           : Std_ReturnType Can_GetControllerMode                   **
**                    ( const uint8 Controller,                               **
**                      Can_ControllerStateType *ControllerModePtr )          **
**                                                                            **
**  Description      : The function reports about the current controller      **
**                      status of the requested CAN controller.               **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : 0x12                                                   **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Non-Reentrant                                          **
**                                                                            **
**  Parameters (in)  : Controller: CAN controller for which the status shall  **
**                     be requested.                                          **
**                                                                            **
**  Parameters (out) : ControllerModePtr: Pointer to a memory location, where **
**                     the current mode of the CAN controller will be stored. **
**                                                                            **
**  Return value     :E_OK: Controller mode request has been accepted.        **
**                    E_NOT_OK: Controller mode request has not been accepted.**
**                                                                            **
*******************************************************************************/
Std_ReturnType Can_17_McmCan_GetControllerMode(const uint8 Controller,
                      Can_ControllerStateType *const ControllerModePtr)
{
  /* return value variable */
  Std_ReturnType ApiStatus = E_NOT_OK;

  /* calling core index */
  uint8 CoreIndex;

  /*Expected init status*/
  uint32 ExpInitStatus;

  /* Core specific controller index */
  uint8 ControllerIndex;

  /* core specifc global variable structure */
  const Can_17_McmCan_CoreGlobalType *CoreGlobalPtr;

  /* Get core id which is executing currently */
  CoreIndex = CAN_17_MCMCAN_GETCOREINDEX;

  /*Check if DET is enabled*/
  #if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON)
  /*Check if the driver is uninitialized*/
  /* [cover parentID={17EB6431-8113-4bc0-8FB8-BCD14F203B43}]
  Invoke the function to perform DET check and reporting if the driver is
  not initialized
  [/cover] */
  ApiStatus = Can_17_McmCan_lDetUninitConfig(
                  CAN_17_MCMCAN_SID_GETCONTROLLERMODE, CoreIndex);

  /* [cover parentID={9AE439D6-C7EA-4972-BA90-1CCDB05EAC84}]
  Is the driver is initialized?
  [/cover] */
  if (E_OK == ApiStatus)
  {
    /* Check the requested controllerId is Valid or not */
    /* [cover parentID={C3B24E4C-D2E7-4830-A1B0-25DBBFEDFA08}]
    Invoke the function to perform DET check and reporting if the controller
    passed is not valid
    [/cover] */
    ApiStatus = Can_17_McmCan_lDetParamController(CoreIndex, Controller,
                CAN_17_MCMCAN_SID_GETCONTROLLERMODE);

    /*Check if the controller mode pointer is not NULL*/
    /* [cover parentID={689CB2E4-E21E-4537-A5F5-9E5D14892048}]
    Is the controller is valid and the input pointer passed NULL?
    [/cover] */
    if ((E_OK == ApiStatus) && (NULL_PTR == ControllerModePtr))
    {
      /*Report DET*/
      /* [cover parentID={32BEC276-CDD2-4c55-A7BD-86CA2C9EFBAF}]
      Report DET CAN_17_MCMCAN_E_PARAM_POINTER
      [/cover] */
      (void)Det_ReportError(CAN_17_MCMCAN_MODULE_ID, CAN_17_MCMCAN_INSTANCE_ID,
      CAN_17_MCMCAN_SID_GETCONTROLLERMODE, CAN_17_MCMCAN_E_PARAM_POINTER);

      /* [cover parentID={551747A6-BA42-4f54-B848-88634A84660B}]
      Set the API status as E_NOT_OK
      [/cover] */
      ApiStatus = E_NOT_OK;
    }
  }
  /*Have all checks passed*/

  if (E_OK == ApiStatus)
  #endif
  {

    /* Check if CAN driver is un-initialized */
    ExpInitStatus = (Can_17_McmCan_InitStatus >> ((uint32)CoreIndex *
                    (uint32)CAN_17_MCMCAN_INIT_STATUS_SIZE)) & 1U;

    /* [cover parentID={D1CBCAB8-8605-49b2-A962-8166323D6F0D}]
    Is CAN Driver Uninitialized?
    [/cover] */
    if ((uint32)CAN_17_MCMCAN_DRV_UNINIT == ExpInitStatus)
    {
      /* Set state as Uninitialized*/
      *ControllerModePtr = CAN_CS_UNINIT;

      ApiStatus = E_OK;
    }
    else
    {
      /*Copy the core specific data into core state variable*/
      CoreGlobalPtr = Can_17_McmCan_GblCoreState[CoreIndex];

      /* Retrieve the controller index offset for the core */
      ControllerIndex = Can_17_McmCan_kGblConfigPtr->
                CanLogicalControllerIndexPtr[Controller].CanLCoreSpecContIndex;

      /*Copy it to the output variable*/
      *ControllerModePtr = (CoreGlobalPtr->CanControllerModePtr[ControllerIndex]);

      /* [cover parentID={995622F8-E52B-464f-96DC-5990B6792C96}]
      Set API status as E_OK
      [/cover] */
      ApiStatus = E_OK;
    }

  }

  return ApiStatus;
}

/*******************************************************************************
** Traceability   : [cover parentID={36BB0248-F261-45bc-A1AF-53660900CC3F}]   **
**                                                                            **
**  Syntax           : Std_ReturnType  Can_17_McmCan_GetControllerErrorState  **
**                     (const uint8 ControllerId,                             **
**                      Can_ErrorStateType  *const ErrorStatePtr)             **
**                                                                            **
**  Description      : The function obtains the error state of the CAN        **
**                     controller by reading the error state register.        **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : 0x11                                                   **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant for different controller.                    **
**                     Non Reentrant for the same controller                  **
**                                                                            **
**  Parameters (in)  : ControllerId - Abstracted CanIf ControllerId which     **
**                     is assigned to a CAN controller, which is requested for**
**                     ErrorState.                                            **
**                                                                            **
**  Parameters (out) : ErrorStatePtr: Pointer to a memory location, where the **
**                     error state of the CAN controller will be stored..     **
**                                                                            **
**  Return value     : Std_ReturnType: E_OK: Error state request              **
**                                     has been accepted.                     **
**                                     E_NOT_OK: Error state request          **
**                                               has not been accepted.       **
*******************************************************************************/
Std_ReturnType Can_17_McmCan_GetControllerErrorState(
    const uint8 ControllerId,
    Can_ErrorStateType *const ErrorStatePtr)

{
  /* return value variable */
  Std_ReturnType ApiStatus = E_NOT_OK;

  /* calling core index */
  uint8 CoreIndex;

  /* Core specific controller index */
  uint8 ControllerIndex;

  /* core specifc configuration */
  const Can_17_McmCan_CoreConfigType *CoreConfigPtr;

  /* Get core id which is executing currently */
  CoreIndex = CAN_17_MCMCAN_GETCOREINDEX;

  /*Can controller node address pointer*/
  const volatile Ifx_CAN_N *NodeRegAddressPtr;

  /*Check if DET is enabled*/
  #if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON)

  /*Check if the driver is uninitialized*/
  /* [cover parentID={9920DE00-CB8E-419a-BE2A-D9D3A62B8050}]
  Invoke the function to perform DET check and reporting if the driver
  is not initialized
  [/cover] */
  ApiStatus = Can_17_McmCan_lDetUninitConfig(
                          CAN_17_MCMCAN_SID_GETCONTROLLERERRORSTATE, CoreIndex);

  /* [cover parentID={B402D4D1-3BA9-476e-A7E4-303044871A03}]
  Is the driver is initialized?
  [/cover] */
  if (E_OK == ApiStatus)
  {
    /* Check the requested controllerId is Valid or not */
    /* [cover parentID={07035CA8-A359-45e1-BF46-FD6ABC5C4CB0}]
    Invoke the function to perform DET check and reporting if the controller
    passed is not valid
    [/cover] */
    ApiStatus = Can_17_McmCan_lDetParamController(CoreIndex, ControllerId,
                                    CAN_17_MCMCAN_SID_GETCONTROLLERERRORSTATE);

    /*Check if the pointer to the error state is NULL*/
    /* [cover parentID={01966EC9-5D9C-442a-AD46-1F0E694FCAF8}]
    Is the controller is valid and the input pointer passed NULL?
    [/cover] */
    if ((E_OK == ApiStatus) && (NULL_PTR == ErrorStatePtr))
    {
      /*Report DET*/
      /* [cover parentID={B03D6969-4217-4ec0-8814-87F753432045}]
      Report the DET CAN_17_MCMCAN_E_PARAM_POINTER
      [/cover] */
      (void)Det_ReportError(CAN_17_MCMCAN_MODULE_ID, CAN_17_MCMCAN_INSTANCE_ID,
      CAN_17_MCMCAN_SID_GETCONTROLLERERRORSTATE, CAN_17_MCMCAN_E_PARAM_POINTER);

      /* [cover parentID={5ADEE677-DC2A-44a6-97CC-EBEC3BB19015}]
      Set the API status as E_NOT_OK
      [/cover] */
      ApiStatus = E_NOT_OK;
    }
  }
  if (E_OK == ApiStatus)
  #endif
  {
    /*Copy the contents of the core specific config pointer*/
    CoreConfigPtr = Can_17_McmCan_kGblConfigPtr->CanCoreConfigPtr[CoreIndex];

    /* Retrieve the controller index offset for the core */
    ControllerIndex = Can_17_McmCan_kGblConfigPtr->
               CanLogicalControllerIndexPtr[ControllerId].CanLCoreSpecContIndex;

    /* Read the exact Node Start address */
    NodeRegAddressPtr = CoreConfigPtr->
                        CanControllerConfigPtr[ControllerIndex].CanNodeAddressPtr;


    /* Check the M_CAN is in BusOff state or not */
    /* Note: Bus off notification to application will be provided only once */
    /* [cover parentID={84F22D54-63A4-4750-A27C-ED47DCDD4E7C}]
    Is the bus off bit is SET?
    [/cover] */
    if (CAN_17_MCMCAN_BIT_SET_VAL == NodeRegAddressPtr->PSR.B.BO)
    {
       *ErrorStatePtr = CAN_ERRORSTATE_BUSOFF;
    }
    /* [cover parentID={82360D7C-A35F-4eed-8092-7C7D34136B32}]
    Is the error passive bit is SET?
    [/cover] */
    else if (CAN_17_MCMCAN_BIT_SET_VAL == NodeRegAddressPtr->PSR.B.EP)
    {

      *ErrorStatePtr = CAN_ERRORSTATE_PASSIVE;
    }
    else
    {
       *ErrorStatePtr = CAN_ERRORSTATE_ACTIVE;
    }

    /* [cover parentID={72775758-6556-47d9-A5B1-4FEA75315EF6}]
    Set the API status as E_OK
    [/cover] */
    ApiStatus = E_OK;
  }
  return ApiStatus;
}

/*******************************************************************************
** Traceability   : [cover parentID={480A0D2A-7168-4d41-B6D6-BA6B4DFA5032}]   **
**                                                                            **
**  Syntax        : Std_ReturnType  Can_17_McmCan_GetControllerTxErrorCounter **
**                  (const uint8 ControllerId,                                **
**                   uint8 * const TxErrorCounterPtr)                         **
**                                                                            **
**  Description      : The API returns the Tx error counter for a CAN         **
**                    controller. This value might not be available for all   **
**                    CAN controllers, in which case E_NOT_OK would be        **
**                    returned. The value of the counter might not be correct **
**                    at the moment the API returns it, because the Tx counter**
**                     is handled asynchronously in hardware. Applications    **
**                    should not trust this value for any assumption about    **
**                    the current bus state.                                  **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : 0x31                                                   **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant for different controller.                    **
**                     Non Reentrant for the same controller.                 **
**                                                                            **
**  Parameters (in)  : ControllerId - CAN controller, whose current Tx error  **
**                     counter shall be acquired.                             **
**                                                                            **
**  Parameters (out) : TxErrorCounterPtr: Pointer to a memory location,       **
**                     where the current Tx error counter of the CAN          **
**                     controller will be stored.                             **
**                                                                            **
**  Return value     : E_OK: Tx error counter available.                      **
**                     E_NOT_OK: Tx error counter not available.              **
*******************************************************************************/
Std_ReturnType Can_17_McmCan_GetControllerTxErrorCounter(
    const uint8 ControllerId, uint8 *const TxErrorCounterPtr)
{

  /* return value variable */
  Std_ReturnType ApiStatus = E_NOT_OK;

  /* calling core index */
  uint8 CoreIndex;

  /* Core specific controller index */
  uint8 ControllerIndex;

  /* core specifc configuration */
  const Can_17_McmCan_CoreConfigType *CoreConfigPtr;

  /*Can controller node address pointer*/
  const volatile Ifx_CAN_N *NodeRegAddressPtr;

  /* Get core id which is executing currently */
  CoreIndex = CAN_17_MCMCAN_GETCOREINDEX;

  /*Check if DET is enabled*/
  #if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={1657C3C7-8A4E-47d5-82CF-ABE39CB7A899}]
  Invoke the function to perform DET check and reporting if the driver is
  not initialized
  [/cover] */
  ApiStatus = Can_17_McmCan_lDetUninitConfig(
                  CAN_17_MCMCAN_SID_GETCONTROLLERTXERRORCOUNTER,CoreIndex);

  /*Check if the driver is initialized*/
  /* [cover parentID={E44761DE-1256-4e0c-AFD6-9DDF1585167B}]
  Is the driver is initialized?
  [/cover] */
  if (E_OK == ApiStatus)
  {

    /* Check the requested controllerId is Valid or not */
    /* [cover parentID={D61BC727-CDCF-4e63-AE51-02DA29C2DFD0}]
    Invoke the function to perform DET check and reporting if the controller
    passed is not valid
    [/cover] */
    ApiStatus = Can_17_McmCan_lDetParamController(CoreIndex, ControllerId,
                CAN_17_MCMCAN_SID_GETCONTROLLERTXERRORCOUNTER);

    /*Check if the RX error counter pointer is NULL*/
    /* [cover parentID={7550869C-5CB0-4e44-8845-987FF4340C79}]
    Is the controller is valid and the input pointer passed NULL?
    [/cover] */
    if ((E_OK == ApiStatus) && (NULL_PTR == TxErrorCounterPtr))
    {
      /*Report DET*/
      /* [cover parentID={E581D0F7-AD56-41ad-9ECC-8826210BEAA9}]
      Report DET CAN_17_MCMCAN_E_PARAM_POINTER
      [/cover] */
      (void)Det_ReportError(CAN_17_MCMCAN_MODULE_ID, CAN_17_MCMCAN_INSTANCE_ID,
                                 CAN_17_MCMCAN_SID_GETCONTROLLERTXERRORCOUNTER,
                                 CAN_17_MCMCAN_E_PARAM_POINTER);
      /* [cover parentID={7018D86A-CD15-400f-8D95-BFF6A0710D64}]
      Set the API status as E_NOT_OK
      [/cover] */
      ApiStatus = E_NOT_OK;
    }
  }
  /*Check if all checks have passed*/
  if (E_OK == ApiStatus)
  #endif
  {
    /*Copy the contents of the core specific config pointer*/
    CoreConfigPtr = Can_17_McmCan_kGblConfigPtr->CanCoreConfigPtr[CoreIndex];

        /* Retrieve the controller index offset for the core */
    ControllerIndex = Can_17_McmCan_kGblConfigPtr->
               CanLogicalControllerIndexPtr[ControllerId].CanLCoreSpecContIndex;

    /* Read the exact Node Start address */
    NodeRegAddressPtr = CoreConfigPtr->
                        CanControllerConfigPtr[ControllerIndex].CanNodeAddressPtr;

    /* [cover parentID={A884032B-B13D-455b-95F0-225E05F6F092}]
    Retrive the TX error count from ECR register
    [/cover] */
    *TxErrorCounterPtr = (uint8)(CAN_17_MCMCAN_TXERRORCOUNTMASK &
                                                      NodeRegAddressPtr->ECR.U);

    /* [cover parentID={AF36C302-C62B-4432-A27D-9D064FA563B2}]
    Set API status as E_OK
    [/cover] */
    ApiStatus = E_OK;
  }
  return ApiStatus;
}
/*******************************************************************************
** Traceability   : [cover parentID={537B5BC3-4E3C-4d93-B8F3-9D2E6F4B0BA0}]   **
**                                                                            **
**  Syntax        : Std_ReturnType  Can_17_McmCan_GetControllerRxErrorCounter **
**                  (const uint8 ControllerId,                                **
**                   uint8 *const RxErrorCounterPtr)                          **
**                                                                            **
**  Description      : The API returns the Rx error counter for a CAN         **
**                    controller. This value might not be available for all   **
**                    CAN controllers, in which case E_NOT_OK would be        **
**                    returned. The value of the counter might not be correct **
**                    at the moment the API returns it, because the Tx counter**
**                     is handled asynchronously in hardware. Applications    **
**                    should not trust this value for any assumption about    **
**                    the current bus state.                                  **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : 0x30                                                   **
**                                                                            **
**  Sync/Async       : Asynchronous                                           **
**                                                                            **
**  Reentrancy       : Reentrant for different controller.                    **
**                     Non Reentrant for the same controller.                 **
**                                                                            **
**  Parameters (in)  : ControllerId - CAN controller, whose current Rx error  **
**                     counter shall be acquired.                             **
**                                                                            **
**  Parameters (out) : RxErrorCounterPtr: Pointer to a memory location,       **
**                     where the current Rx error counter of the CAN          **
**                     controller will be stored.                             **
**                                                                            **
**  Return value     : E_OK: Rx error counter available.                      **
**                     E_NOT_OK: Rx error counter not available.              **
*******************************************************************************/
Std_ReturnType Can_17_McmCan_GetControllerRxErrorCounter(
      const uint8 ControllerId, uint8 *const RxErrorCounterPtr)
{
  /* return value variable */
  Std_ReturnType ApiStatus = E_NOT_OK;

  /* calling core index */
  uint8 CoreIndex;

  /* Core specific controller index */
  uint8 ControllerIndex;

  /* Rx error counter value */
  uint8 RxErrorCounter;

  /* core specifc configuration */
  const Can_17_McmCan_CoreConfigType *CoreConfigPtr;

  /*Can controller node address pointer*/
  const volatile Ifx_CAN_N *NodeRegAddressPtr;

  /* Get core id which is executing currently */
  CoreIndex = CAN_17_MCMCAN_GETCOREINDEX;

  /*Check if DET is enabled*/
  #if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={3AAEE5E5-3799-450d-A931-C70AB54235B7}]
  Invoke the function to perform DET check and reporting if the driver is
  not initialized
  [/cover] */
  ApiStatus = Can_17_McmCan_lDetUninitConfig(
                  CAN_17_MCMCAN_SID_GETCONTROLLERRXERRORCOUNTER, CoreIndex);
  /*Check if the driver is initialized*/
  /* [cover parentID={3896F9BB-608D-49b5-89FE-A4B4C5348649}]
  Is the driver is initialized?
  [/cover] */
  if (E_OK == ApiStatus)
  {
    /* Check the requested controllerId is Valid or not */
    /* [cover parentID={6F56DDE9-3370-4b8c-BE99-C299E69F4421}]
    Invoke the function to perform DET check and reporting if the controller
    passed is not valid
    [/cover] */
    ApiStatus = Can_17_McmCan_lDetParamController(CoreIndex, ControllerId,
                CAN_17_MCMCAN_SID_GETCONTROLLERRXERRORCOUNTER);

    /*Check if the RX error counter pointer is NULL*/
    /* [cover parentID={EB96813A-F801-41ab-83DE-EA9970470A49}]
    Is the controller is valid and the input pointer passed NULL?
    [/cover] */
    if ((E_OK == ApiStatus) && (NULL_PTR == RxErrorCounterPtr))
    {
      /*Report DET*/
      (void)Det_ReportError(CAN_17_MCMCAN_MODULE_ID, CAN_17_MCMCAN_INSTANCE_ID,
                              CAN_17_MCMCAN_SID_GETCONTROLLERRXERRORCOUNTER,
                              CAN_17_MCMCAN_E_PARAM_POINTER);

      /* [cover parentID={80999411-DEA9-4b33-84A6-28508BBA7183}]
      Set the API status as E_NOT_OK
      [/cover] */
      ApiStatus = E_NOT_OK;
    }
  }

  /*Check if the DET checks have passed*/
  if (E_OK == ApiStatus)
  #endif
  {
    /*Copy the contents of the core specific config pointer*/
    CoreConfigPtr = Can_17_McmCan_kGblConfigPtr->CanCoreConfigPtr[CoreIndex];

    /* Retrieve the controller index offset for the core */
    ControllerIndex = Can_17_McmCan_kGblConfigPtr->
               CanLogicalControllerIndexPtr[ControllerId].CanLCoreSpecContIndex;

    /* Read the exact Node Start address */
    NodeRegAddressPtr = CoreConfigPtr->
                        CanControllerConfigPtr[ControllerIndex].CanNodeAddressPtr;

    /* Retrieve rx error counter value */
    RxErrorCounter = (uint8)((CAN_17_MCMCAN_RXERRORCOUNTMASK &
                                  NodeRegAddressPtr->ECR.U) >>
                                    CAN_17_MCMCAN_RXERRORCNT_OFFSET);

    /* Add the passive bit and write counter value to the memory location */
    *RxErrorCounterPtr = RxErrorCounter +
                         (uint8)(( CAN_17_MCMCAN_RXERRORPASSIVEMASK &
                          NodeRegAddressPtr->ECR.U) >>
                          CAN_17_MCMCAN_RXERRORPASSIVE_OFFSET);

    /* [cover parentID={4FB3FD08-6FEF-4077-95A2-E92CDBC3D8D9}]
    Set API status as E_OK
    [/cover] */
    ApiStatus = E_OK;
  }
  return ApiStatus;
}
#endif

#if (CAN_17_MCMCAN_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={DFF7807D-69E0-42c4-AE95-F08E2299FC2D}]   **
**                                                                            **
** Syntax           : void Can_17_McmCan_GetVersionInfo                       **
**                    (                                                       **
**                      Std_VersionInfoType* const versioninfo                **
**                    )                                                       **
**                                                                            **
** Description      : - This function returns the version information of this **
**                      module.The version information include : Module ID,   **
**                      Vendor ID,Vendor specific version numbers             **
**                                                                            **
** Service ID       : 0x07                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (out) : versioninfo - Pointer to store the                      **
**                    version information of this module.                     **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
void Can_17_McmCan_GetVersionInfo(Std_VersionInfoType *const versioninfo)
{

  #if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={91C85D96-0FA9-4db2-99A7-1C27FD54723E}]
  DET is enabled
  [/cover] */
  /* [cover parentID={CD74AE77-3AD8-48db-9884-410074732021}]
  [/cover] */
  if ((versioninfo) == NULL_PTR)
  {
    /* [cover parentID={07B8D0A0-8243-4145-8BBA-F3CDC1763AA6}]
    Det error CAN_17_MCMCAN_E_PARAM_POINTER
    [/cover] */
    (void)Det_ReportError((uint16)CAN_17_MCMCAN_MODULE_ID,
                    CAN_17_MCMCAN_INSTANCE_ID,
                    CAN_17_MCMCAN_SID_GETVERSIONINFO,
                    CAN_17_MCMCAN_E_PARAM_POINTER);
  }
  else
  #endif /* #if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON )  */
  {

    ((Std_VersionInfoType *)(versioninfo))->moduleID = CAN_17_MCMCAN_MODULE_ID;

    ((Std_VersionInfoType *)(versioninfo))->vendorID = CAN_17_MCMCAN_VENDOR_ID;

    ((Std_VersionInfoType *)(versioninfo))->sw_major_version =
      (uint8)CAN_17_MCMCAN_SW_MAJOR_VERSION;

    ((Std_VersionInfoType *)(versioninfo))->sw_minor_version =
      (uint8)CAN_17_MCMCAN_SW_MINOR_VERSION;

    ((Std_VersionInfoType *)(versioninfo))->sw_patch_version =
      (uint8)CAN_17_MCMCAN_SW_PATCH_VERSION;
  }

  /* [cover parentID={CF6036C3-803C-466c-B52C-5F008AECD9F2}]
  End
  [/cover] */
}
#endif /* #if( (CAN_17_MCMCAN_VERSION_INFO_API == STD_ON) */

/*******************************************************************************
            Scheduled functions
*******************************************************************************/
#if (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_OFF)
/*******************************************************************************
** Traceability   : [cover parentID={B2620C39-C898-4a91-8D83-9B48F2A98804}]   **
**                  [cover parentID={0DFEBF6A-E273-4601-ABA3-0FD3C5635523}]   **
**                                                                            **
**  Syntax           : void Can_17_McmCan_MainFunction_Write                  **
**                    (                                                       **
**                      void                                                  **
**                    )                                                       **
**                                                                            **
** Description    :The function shall perform the polling of TX confirmation  **
**                 when CanTxProcessing is set to POLLING or MIXED. In case   **
**                 of MIXED processing only the hardware objects for which    **
**                 CanHardwareObjectUsesPolling is set to TRUE shall be polled**
**                 The function is implemented as an empty define in case no  **
**                 polling at all is used. In case the value of               **
**                 CanMainFunctionRWPeriod is 0 or 1,                         **
**                 Can_17_McmCan_MainFunctionWrite is used. In case it is     **
**                greater than 1, Can_17_McmCan_MainFunctionWrite_(x) is used.**
**                 The Tx slots are not freed until transmit notifications is **
**                 not provided to the upper layer.                           **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : 0x01                                                   **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Non-Reentrant                                          **
**                                                                            **
**  Parameters (in)  : none                                                   **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
void Can_17_McmCan_MainFunction_Write(void)
{

  /*Tx Polling Process is Enabled*/
  /* [cover parentID={F9B21214-AA72-4f21-8B95-878CA54AFC31}]
  Tx Polling or MIxed Process is Enabled and only one RW periods configured
  [/cover] */
  #if ((CAN_17_MCMCAN_TX_POLLING_PROCESSING == STD_ON) || \
      (CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON))
  /* calling core index */
  uint8 CoreIndex;

  /* Core specific controller index */
  uint8 CtrlIndex;

  uint32 ExpInitStatus;

  /* core specifc configuration */
  const Can_17_McmCan_CoreConfigType *ConfigPtr;

  /* core specifc global variable structure */
  const Can_17_McmCan_CoreGlobalType *CoreGlobalPtr;

  /* Get core id which is executing currently */
  CoreIndex = CAN_17_MCMCAN_GETCOREINDEX;

  /* Check if CAN driver is un-initialized */

  ExpInitStatus = (Can_17_McmCan_InitStatus >> ((uint32)CoreIndex *
                          (uint32)CAN_17_MCMCAN_INIT_STATUS_SIZE)) & 1U;

  /* [cover parentID={B9CB4235-6229-4d60-B124-6703ABC6C513}]
  Is the driver initialized?
  [/cover] */
  if ((uint32)CAN_17_MCMCAN_DRV_READY == ExpInitStatus)
  {

    /* Local copy of the core specific configuration */
    ConfigPtr = Can_17_McmCan_kGblConfigPtr->CanCoreConfigPtr[CoreIndex];

    /* Local copy of the core specific global states */
    CoreGlobalPtr = Can_17_McmCan_GblCoreState[CoreIndex];

    /* Call transmit handler function for each of the CAN controllers
    configured as POLLING or MIXED mode for transmission successful
    event handling */
    for (CtrlIndex = 0U; CtrlIndex < ConfigPtr->CanCoreContCnt; CtrlIndex++)
    {

      /*Requested controller transmit event handling is of polling or mixed type
      and the controller mode is STARTED*/
      /* [cover parentID={64AC5815-F17B-4ca1-B5FD-E89F51EF99DF}]
      Requested controller transmit event handling is of POLLING or MIXED type
      and the controller mode is STARTED
      [/cover] */
      if ((CAN_17_MCMCAN_INTERRUPT !=
           ConfigPtr->CanEventHandlingConfigPtr[CtrlIndex].CanTxProcessing) &&
          (CAN_17_MCMCAN_STARTED ==
                               CoreGlobalPtr->CanControllerModePtr[CtrlIndex]))
      {
        /*Check if the TX Hw object configuration pointer is not NULL*/
        /* [cover parentID={214D632C-55DF-4d73-9AC6-3350D140EEBB}]
        Is Transmission support ON?
        [/cover] */
        if (NULL_PTR != ConfigPtr->CanTxHwObjectConfigPtr)
        {
          /* Invoke internal function to process transmit confirmation */
          /* [cover parentID={CAD339A2-658C-4155-96B9-AAB45420B169}]
          Invoke Transmit Handler
          [/cover] */
          Can_17_McmCan_lTxEventHandler(CtrlIndex, CoreGlobalPtr,
                                             CAN_17_MCMCAN_POLLING, ConfigPtr);
        }
      }
    }
  }
  #endif /* #if((CAN_17_MCMCAN_TX_POLLING_PROCESSING == STD_ON) || \
      (CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON))*/
}
#endif /* #if (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_OFF) */

#if (CAN_17_MCMCAN_RX_MULTI_PERIODS_SUPPORT == STD_OFF)
/*******************************************************************************
** Traceability   : [cover parentID={4DF70F32-AF8B-4771-8288-7B236390D1C3}]   **
**                  [cover parentID={45061A30-5EB8-46cf-9681-9EAB76965D54}]   **
**                                                                            **
**  Syntax           : void Can_17_McmCan_MainFunction_Read                   **
**                    (                                                       **
**                      void                                                  **
**                    )                                                       **
**                                                                            **
** Description    :This main function performs the task of processing all the **
**                 HRH objects configured as polling and if respective        **
**                 messages are received will provide notification to upper   **
**                 layer. The function performs the polling of receive        **
**                 indication when CanRxProcessing is set to POLLING or MIXED.**
**                 In case of MIXED processing only the hardware objects      **
**                for which CanHardwareObjectUsesPolling is set to TRUE shall **
**                be polled. The function is implemented as an empty define   **
**                if none of the RX processing for any of the configured      **
**                controllers or hardware objects (in case of mixed mode)     **
**                is chosen as POLLING.In case the value of                   **
**                CanMainFunctionRWPeriod is 0 or 1,                          **
**                Can_17_McmCan_MainFunctionRead is used. In case it is       **
**                greater than 1, Can_17_McmCan_MainFunctionRead_(x) is used. **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : 0x08                                                   **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Non-Reentrant                                          **
**                                                                            **
**  Parameters (in)  : none                                                   **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
void Can_17_McmCan_MainFunction_Read(void)
{
  /*Rx Polling Process is Enabled*/
  /* [cover parentID={14C8B5DC-E3D1-4eec-9763-BCFBE7C300F5}]
  CAN_17_MCMCAN_RX_POLLING_PROCESSING and CAN_17_MCMCAN_RX_MIXED_PROCESSING
  is ON
  [/cover] */
  #if ((CAN_17_MCMCAN_RX_POLLING_PROCESSING == STD_ON) || \
      (CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))

  /* calling core index */
  uint8 CoreIndex;

  /* Core specific controller index */
  uint8 CtrlIndex;

  uint32 ExpInitStatus;

  /* core specifc configuration */
  const Can_17_McmCan_CoreConfigType *CoreConfigPtr;

  /* core specifc global variable structure */
  const Can_17_McmCan_CoreGlobalType *CoreGlobalPtr;

  /* Get core id which is executing currently */
  CoreIndex = CAN_17_MCMCAN_GETCOREINDEX;

  /* Check if CAN driver is un-initialized */
  ExpInitStatus = (Can_17_McmCan_InitStatus >> ((uint32)CoreIndex *
                      (uint32)CAN_17_MCMCAN_INIT_STATUS_SIZE)) & 1U;

  /* [cover parentID={59028030-EDEC-4e3f-A516-5BD3CB012AD0}]
  Is the driver initialized
  [/cover] */
  if ((uint32)CAN_17_MCMCAN_DRV_READY == ExpInitStatus)
  {
    /* Local copy of the core specific configuration */
    CoreConfigPtr = Can_17_McmCan_kGblConfigPtr->CanCoreConfigPtr[CoreIndex];

    /* Local copy of the core specific global states */
    CoreGlobalPtr = Can_17_McmCan_GblCoreState[CoreIndex];

    /* Call transmit handler function for each of the CAN controllers
     configured as POLLING or MIXED mode for transmission successful event
     handling */
    for (CtrlIndex = 0U; CtrlIndex < CoreConfigPtr->CanCoreContCnt; CtrlIndex++)
    {

      /*The controller mode is STARTED*/
      /* Check the controller mode is not Interrupt*/
      /* [cover parentID={D4F9DE02-7644-43b3-A022-B65E05081A04}]
      Check if  the mode is not INTERRUPT and the Controller mode is STARTED
      [/cover] */
      if ((CAN_17_MCMCAN_INTERRUPT !=
                            CoreConfigPtr->CanEventHandlingConfigPtr[CtrlIndex].
           CanRxProcessing) && (CAN_17_MCMCAN_STARTED == CoreGlobalPtr->
                                      CanControllerModePtr[CtrlIndex]))
      {
        /* Poll all 3, Rx Dedicated, Rx FIFO - 0, Rx FIFO - 1 */
        /* [cover parentID={B6EC69B6-2A59-4489-9B93-0EFEEE65D9C0}]
        Invoke Receive Handler
        [/cover] */
        Can_17_McmCan_lReceiveHandler(CtrlIndex, CAN_17_MCMCAN_RX_ALL,
                           CAN_17_MCMCAN_POLLING, CoreGlobalPtr, CoreConfigPtr);
      }
    }
  }
  #endif
}
#endif /* #if (CAN_17_MCMCAN_RX_MULTI_PERIODS_SUPPORT == STD_OFF) */

/*******************************************************************************
**                                                                            **
**  Traceability    : [cover parentID={6E7658DE-1E4B-4468-97D1-869C21AB0495}] **
**  Syntax           : void Can_17_McmCan_MainFunction_BusOff                 **
**                    (                                                       **
**                      void                                                  **
**                    )                                                       **
**                                                                            **
** Description    :The function performs the polling of bus-off events that   **
**                 are configured statically as 'to be polled'.               **
**                 Bus-off notification will be provided to upper layer only  **
**                 once when the hardware detects bus-off. If bus-off remains **
**                 after the first notification, no further notifications will**
**                 be provided to upper layer.                                **
**                 The function is implemented as an empty if the RX processing*
**                 for none of the configured controllers is chosen as POLLING**
**  [/cover]                                                                  **
**  Service ID       : 0x09                                                   **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Non-Reentrant                                          **
**                                                                            **
**  Parameters (in)  : none                                                   **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
void Can_17_McmCan_MainFunction_BusOff(void)
{

  /* [cover parentID={B735E851-C542-4855-8618-2162C8222243}]
  Bus Off Polling Process is Enabled
  [/cover] */
  #if (CAN_17_MCMCAN_BO_POLLING_PROCESSING == STD_ON)
  /* calling core index */
  uint8 CoreIndex;

  /* Core specific controller index */
  uint8 CtrlIndex;

  uint32 ExpInitStatus;

  /* core specifc configuration */
  const Can_17_McmCan_CoreConfigType *CoreConfigPtr;

  /* core specifc global variable structure */
  const Can_17_McmCan_CoreGlobalType *CoreGlobalPtr;

  /* Get core id which is executing currently */
  CoreIndex = CAN_17_MCMCAN_GETCOREINDEX;

  /* Check if CAN driver is un-initialized */
  ExpInitStatus = (Can_17_McmCan_InitStatus >> ((uint32)CoreIndex *
                      (uint32)CAN_17_MCMCAN_INIT_STATUS_SIZE)) & 1U;

  /* [cover parentID={7C472617-CF79-4a95-AEB7-8ECD7E351F63}]
  Is the driver initialized?
  [/cover] */
  if ((uint32)CAN_17_MCMCAN_DRV_READY == ExpInitStatus)
  {
    /* Local copy of the core specific configuration */
    CoreConfigPtr = Can_17_McmCan_kGblConfigPtr->CanCoreConfigPtr[CoreIndex];

    /* Local copy of the core specific global states */
    CoreGlobalPtr = Can_17_McmCan_GblCoreState[CoreIndex];

    /* Call bus-off handler function for each of the CAN controllers
    configured as POLLING mode for bus-off event handling */
    /* [cover parentID={293A7F96-4733-481f-B372-08CDA28E9CF8}]
    Can controller configuration set
    [/cover] */
    for (CtrlIndex = 0U; CtrlIndex < CoreConfigPtr->CanCoreContCnt; CtrlIndex++)
    {
      /* Check the BusOff processing mode as Polling */
      /* [cover parentID={9186D66E-F8BC-4552-8670-4CEC4AB50F09}]
      Requested controller bus off event handling is of polling type
      [/cover] */
      if (CAN_17_MCMCAN_POLLING == CoreConfigPtr->
                       CanEventHandlingConfigPtr[CtrlIndex].CanBusoffProcessing)
      {
        /* [cover parentID={166057C2-33FC-483b-A347-9317CD5DA638}]
        ICOM support is ON
        [/cover] */
        #if (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON)
        /* [cover parentID={68C61EB4-B24B-4bd1-A6FC-A82C293AECE8}]
        Is ICOM enable status not enabled or Bus off status not disabled?
        [/cover] */
        if ((TRUE != CoreGlobalPtr->CanIcomEnableStatusPtr[CtrlIndex]) ||
            (FALSE != CoreGlobalPtr->CanIcomConfgBOStatusPtr[CtrlIndex]))
        {
          /* Invoke Bus-Off Handler */
          /* [cover parentID={7B69687D-7429-4041-B07B-C734C946F7CB}]
          Invoke Bus Off Handler
          [/cover] */
          Can_17_McmCan_lBusOffHandler(CtrlIndex, CoreGlobalPtr, CoreConfigPtr);
        }
        #else

        /* Invoke Bus-Off Handler */
        /* [cover parentID={A26950E9-D247-4c48-A43B-4860963EA081}]
        Invoke Bus Off Handler
        [/cover] */
        Can_17_McmCan_lBusOffHandler(CtrlIndex, CoreGlobalPtr, CoreConfigPtr);
        #endif
     }
    }
  }
  #endif /* #if(CAN_17_MCMCAN_BO_POLLING_PROCESSING == STD_ON) */
}

/*******************************************************************************
** Traceability   : [cover parentID={185859A3-F84D-408d-88DB-0D4A648E8849}]   **
**                  [cover parentID={BF3EBBD1-0465-445d-851E-C085EBD8799C}]   **
**                                                                            **
**  Syntax           : void Can_17_McmCan_MainFunction_Wakeup                 **
**                    (                                                       **
**                      void                                                  **
**                    )                                                       **
**                                                                            **
** Description    :The function performs the polling of wake-up events that   **
**                 are configured statically as 'to be polled'.               **
**                 The function is implemented as an empty define in case     **
**                 no polling at all is used.                                 **
**                                                                            **
**  Service ID       : 0x0A                                                   **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Non-Reentrant                                          **
**                                                                            **
**  Parameters (in)  : none                                                   **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
void Can_17_McmCan_MainFunction_Wakeup(void)
{
  /*Wake Up Polling Process is Enabled*/
  /* [cover parentID={2466E081-CEB3-4c01-B071-1D65E3DF9782}]
  Wake Up Polling Process is Enabled and CAN public ICOM support is Enabled
  [/cover] */
  #if ((CAN_17_MCMCAN_WU_POLLING_PROCESSING == STD_ON) && \
  (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON))

  /* calling core index */
  uint8 CoreIndex;

  /* Core specific controller index */
  uint8 CtrlIndex;

  uint32 ExpInitStatus;

  /* core specifc configuration */
  const Can_17_McmCan_CoreConfigType *CoreConfigPtr;

  /* core specifc global variable structure */
  const Can_17_McmCan_CoreGlobalType *CoreGlobalPtr;

  /* Get core id which is executing currently */
  CoreIndex = CAN_17_MCMCAN_GETCOREINDEX;

  /* Check if CAN driver is un-initialized */
  ExpInitStatus = (Can_17_McmCan_InitStatus >> ((uint32)CoreIndex *
                      (uint32)CAN_17_MCMCAN_INIT_STATUS_SIZE)) & 1U;

  /* [cover parentID={D819E02B-E79C-4576-B9D5-79398475ADE6}]
  Is the driver initialized?
  [/cover] */
  if ((uint32)CAN_17_MCMCAN_DRV_READY == ExpInitStatus)
  {
    /* Local copy of the core specific configuration */
    CoreConfigPtr = Can_17_McmCan_kGblConfigPtr->CanCoreConfigPtr[CoreIndex];

    /* Local copy of the core specific global states */
    CoreGlobalPtr = Can_17_McmCan_GblCoreState[CoreIndex];

    /* Call wakeup handler function for each of the CAN controllers
    configured as POLLING mode for wakeup event handling */
    /* [cover parentID={438EBDFA-C83A-4cd2-897C-4DF8EC5CF670}]
    CAN controller configuration set
    [/cover] */
    for (CtrlIndex = 0U; CtrlIndex < CoreConfigPtr->CanCoreContCnt; CtrlIndex++)
    {
      /* Check if the controller is activated with Polling mode */
      /* [cover parentID={7A953952-FFF4-4ea7-8068-05D4964FF7B2}]
      Requested controller wake up event handling is of polling type
      [/cover] */
      if ((CAN_17_MCMCAN_POLLING == CoreConfigPtr->
               CanEventHandlingConfigPtr[CtrlIndex].CanWakeupProcessing) &&
          (TRUE == CoreGlobalPtr->CanIcomEnableStatusPtr[CtrlIndex]))
      {
        /* Invoke function for check the receive message wakeup events */
        /* [cover parentID={B084CCCF-36BA-448c-B2DE-AFEEEA8CE228}]
        Invoke Recive Handler
        [/cover] */
        Can_17_McmCan_lReceiveHandler(CtrlIndex, CAN_17_MCMCAN_RX_ALL,
                           CAN_17_MCMCAN_POLLING, CoreGlobalPtr, CoreConfigPtr);
      }
    }
  }
  #endif /* #if((CAN_17_MCMCAN_WU_POLLING_PROCESSING == STD_ON) && \
  (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON)) */
}

/*******************************************************************************
** Traceability   : [cover parentID={2A250146-E646-440d-868C-6AA4892FCD9E}]   **
**  Syntax           : void Can_17_McmCan_MainFunction_Mode                   **
**                    (                                                       **
**                      void                                                  **
**                    )                                                       **
**                                                                            **
**  Description      : The function is supposed to poll for the CAN controller**
**                     mode transitions.                                      **
**                     The CAN driver has a synchronous mode setting mechanism**
**                     and does not support the this function. It is          **
**                     implemented as an empty function.                      **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : 0x0C                                                   **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Non-Reentrant                                          **
**                                                                            **
**  Parameters (in)  : none                                                   **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
void Can_17_McmCan_MainFunction_Mode(void)
{
  /* The mode indication */
}

/********************************Local Functions*******************************/

/*******************************************************************************
** Traceability     : [cover parentID={BD8FE8B5-E2AB-4939-AE72-5CFE21FD53F2}] **
**                                                                            **
**  Syntax           :static Std_ReturnType Can_17_McmCan_lGlobalInit         **
**                    (                                                       **
**                      const Can_17_McmCan_ConfigType *const ConfigPtr       **
**                    )                                                       **
**                                                                            **
**  Description      : The function initializes the CAN kernel clocks.        **
**                     This is done by the master core.                       **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Non-Reentrant                                          **
**                                                                            **
**  Parameters(in)   : ConfigPtr - Pointer to the CAN driver root configuration*
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : E_OK: Global initialization of clocks successful       **
**                     E_NOT_OK: Global initialization of clocks failed       **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Can_17_McmCan_lGlobalInit(const Can_17_McmCan_ConfigType
                                                *const ConfigPtr)
{
  /*Variable to stote the return value of the local functions*/
  Std_ReturnType ReturnValue = E_NOT_OK;

  /*Variable to stote the CAN kernel index*/
  uint8 KerIndex;

  /* Set kernel index with zero */
  KerIndex = 0U;

  /* Initialize clock settings depends on the no of Kernels used */
  /* [cover parentID={A5E529AC-F4BE-4ffe-BB32-A90F4DF64109}]
  For all configured number of kernels or when clock setting for a kernel fails
  [/cover] */
  while (KerIndex < ConfigPtr->CanNoOfKernel)
  {
    /* Initialize the CAN clock settings*/
    /* [cover parentID={750CDB25-8A13-4692-BD6B-B409B5E35C25}]
    Invoke internal function for Clock Settings
    [/cover] */
    ReturnValue = Can_17_McmCan_lInitClkSetting(ConfigPtr, KerIndex);

    /*For all configured number of kernels or when clock setting for a
    kernel fails*/
    /* [cover parentID={23838530-F2E6-41dd-9B07-9FB86CFAF9EE}]
    Is the clock initialization successful?
    [/cover] */
    if (E_OK == ReturnValue)
    {
      /* Increment the kernel index */
      KerIndex++;
    }
    else
    {
       break;
    }
  }
  return ReturnValue;
}
/*******************************************************************************
** Traceability   : [cover parentID={5167E051-6336-4bd5-9944-1882E570BDC6}]   **
**                                                                            **
**                                                                            **
**  Syntax          : static Std_ReturnType Can_17_McmCan_lCoreInit           **
**                   (                                                        **
**                     const Can_17_McmCan_CoreConfigType *const CoreConfigPtr,*
**                     Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr      **
**                   )                                                        **
**                                                                            **
** Description    :The function triggers core specific initializations for    **
**                 controllers allocated to that core.                        **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Non-Reentrant                                          **
**                                                                            **
**  Parameters(in)   :CoreConfigPtr- Pointer to core specific CAN driver      **
**                    configuration                                           **
**                    CoreGlobalPtr - Pointer to core specific global         **
**                                    structure                               **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : E_OK: Controller specific initialization successful    **
**                     E_NOT_OK: Controller specific initialization failed    **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Can_17_McmCan_lCoreInit(const Can_17_McmCan_CoreConfigType
                                              *const CoreConfigPtr,
                                              const Can_17_McmCan_CoreGlobalType
                                              *const CoreGlobalPtr)
{
  /*Variable to stote the return value of the local functions*/
  Std_ReturnType ReturnValue = E_OK;

  /*Variable to stote the CAN controller index*/
  uint8 CtrlIndex;

  /* Initialize all the Global variables */
  Can_17_McmCan_lInitGlobalVar(CoreConfigPtr, CoreGlobalPtr);

  /* Set controller index with zero */
  CtrlIndex = 0U;

  /* Initialize the CAN controller */
  /* [cover parentID={7704C479-1A02-4b3b-8BF2-F0BB262023FC}]
  Initialize the CAN controller
  [/cover] */
  /* [cover parentID={F5B648CD-B829-4140-AFDA-9A809BA76E50}]
  For all controllers configured for this core
  [/cover] */
  while ((CtrlIndex < CoreConfigPtr->CanCoreContCnt) && (E_OK == ReturnValue))
  {

    /* Invoke internal function for the CAN Controller Initialization */
    /* [cover parentID={AE26591C-9FF7-4eb6-96FB-8435CD219D8D}]
    Invoke internal function for the CAN Controller Initialization
    [/cover] */
    ReturnValue = Can_17_McmCan_lInitController(CtrlIndex, CoreConfigPtr,
                                                CoreGlobalPtr);
    /* Increment with one */
    CtrlIndex++;
  }
  return ReturnValue;
}
/*******************************************************************************
** Traceability   : [cover parentID={C4964D9F-B613-4e31-BA02-D38ACFE184B8}]   **
**                                                                            **
**  Syntax           : static void Can_17_McmCan_lInitGlobalVar               **
**                    (const Can_17_McmCan_CoreConfigType *const CoreConfigPtr,*
**                     const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr)*
**                                                                            **
**  Description      : The function initializes global variables managing     **
**                     the interrupt counters, software object indices and    **
**                     priority object indices of CAN driver.                 **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Non-Reentrant                                          **
**                                                                            **
**  Parameters (in)  : CoreConfigPtr - Core specific config root structure    **
**                    CoreGlobalPtr - Pointer to core specific global         **
**                                    structure                               **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Parameters (in-out) : none                                                **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
static void Can_17_McmCan_lInitGlobalVar(const Can_17_McmCan_CoreConfigType
                                               *const CoreConfigPtr,
                                         const Can_17_McmCan_CoreGlobalType
                                               *const CoreGlobalPtr)
{
  /*Variable to store the CAN controller index*/
  uint8 CntrlIndx;

  /* Size of the transmit message buffer */
  uint16 TxHwIndex;

  /* SW Object index count*/
  uint16 SwObjIndx;

  /* Clear interrupt status and disable count */
  /* [cover parentID={B4A04CF1-43D7-4d6f-9158-B431892D833A}]
  Loop till the last configured Controller index
  [/cover] */
  for (CntrlIndx = 0U; CntrlIndx < CoreConfigPtr->CanCoreContCnt; CntrlIndx++)
  {
    /*Disable interrupt counter*/
    /* [cover parentID={3F53C84C-D232-4885-8B6E-35DCE4AC9A14}]
    Clear interrupt status and disable count
    [/cover] */
    CoreGlobalPtr->CanDisableIntrpCountPtr[CntrlIndx] = 0U;

    CoreGlobalPtr->CanControllerModePtr[CntrlIndx] = CAN_17_MCMCAN_UNINIT;

    /* Clear software PDU handle array */
    /* [cover parentID={5929D212-CE41-42a5-881B-7286B694446F}]
    Clear software PDU handle array
    [/cover] */
    for (TxHwIndex = 0U; TxHwIndex < CAN_17_MCMCAN_MAX_TX_BUFFER_INDEX;
          TxHwIndex++)
    {
      /* Calculate Sw Obj Handle index */
      /* [cover parentID={FE8C0678-2707-493d-BAC3-F0A6FD26D643}]
      Calculate Sw Obj Handle index
      [/cover] */
      SwObjIndx = (uint16)((CntrlIndx *
                      CAN_17_MCMCAN_NOOF_TX_HW_BUFF_AVAILABLE) + TxHwIndex);

      CoreGlobalPtr->CanSwObjectHandlePtr[SwObjIndx] = 0U;

      /* [cover parentID={8C993E14-9114-4ba6-A7C3-02E899CD6BDF}]
      TX MIXED PROCESSING or TX MULTIPERIOD is ON
      [/cover] */
      #if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
          (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON))

      /* initialise Pending queue with default value */
      CoreGlobalPtr->CanTxSwQueuePtr->CanTxSwPendingQueuePtr[SwObjIndx] =
                                               CAN_17_MCMCAN_MAX_SWOBJECT_INDEX;
      #endif /* #if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
            (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON)) */
    }
     /* [cover parentID={1D6AFA4D-B915-4e99-B3C2-838A4E715E58}]
     TX MIXED PROCESSING or TX MULTIPERIOD is ON
    [/cover] */
    #if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
          (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON))

    /* initialise the pending queue index */
    CoreGlobalPtr->CanTxSwQueuePtr->CanTxSwPendingQueueIndex = 0U;

    #endif /* #if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON)) */
  }
}
/*******************************************************************************
** Traceability   : [cover parentID={9EEB7EAB-D2C8-4cbf-BD18-5467E493D360}]   **
**                  [cover parentID={5178FA72-B5C6-4672-B206-324EA587C343}]   **
**                                                                            **
**  Syntax           : static Std_ReturnType                                  **
**                             Can_17_McmCan_lInitClkSetting                  **
**                    (                                                       **
**                      const Can_17_McmCan_ConfigType *const ConfigPtr,      **
**                      const uint8 KernelIndx                                **
**                    )                                                       **
**                                                                            **
**  Description      : The function initializes clock control register,       **
**                     RAM initialization, fractional divider register        **
**                     and module control register.                           **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Non-Reentrant                                          **
**                                                                            **
**  Parameters (in)  : ConfigPtr: - Pointer to CAN driver configuration       **
**                     KernelIndx: Logical core specific kernel indexing      **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : E_OK: Global initialization of clocks successful       **
**                     E_NOT_OK: Global initialization of clocks failed       **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Can_17_McmCan_lInitClkSetting(
    const Can_17_McmCan_ConfigType *const ConfigPtr, const uint8 KernelIndx)
{
  /*Base address pointer for the kernel*/
  volatile Ifx_CAN *MCMBaseAddressPtr;

  /*Variable to store kernel clock selection*/
  uint32 ClockSelConfigValue;

  /*Variable to store MCR SFR value*/
  volatile uint32 MCRValueTemp;

  /*Variable to store the active node count*/
  uint8 ActNodeCount;

  /*Variable to store the return value of the local functions*/
  Std_ReturnType ReturnValue = E_NOT_OK;

  /* Copy the MCMCAN module base address */
  MCMBaseAddressPtr =
      ConfigPtr->CanMCMModuleConfigPtr[KernelIndx].CanBaseAddressPtr;

  /* Disable CAN kernel clock via CLC */
  CAN_17_MCMCAN_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(
      &(MCMBaseAddressPtr->CLC), CAN_17_MCMCAN_CLK_DISABLE);

  /* Check disable bit is set or not */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: Typecasting to uint32 is
    required in order to maintain a common interface to check bits
    that are getting updated by hardware */
  ReturnValue = Can_17_McmCan_lTimeOut(                           \
      (const volatile uint32 *)(&(MCMBaseAddressPtr->CLC.U)),     \
      (uint32)CAN_17_MCMCAN_MODULE_DISABLE_STATUS,                \
                                      CAN_17_MCMCAN_NOT_EQUAL);

  /* Check Hw is set properly or not within the Time-out */
  /* [cover parentID={334271A9-DEBA-451e-82AE-ACCD7064B5BE}]
  Is Status Ok?
  [/cover] */
  if (E_OK == ReturnValue)
  {
    /*Read the MCR value*/
    MCRValueTemp = MCMBaseAddressPtr->MCR.U;

    /* Set CLK selection value with no CLK supply */
    ClockSelConfigValue = 0U;

    /* Read all the active node and set clock settings */
    /* [cover parentID={0A2A10DF-ECAE-419a-8D33-628D9B5B7FFF}]
    Loop till the last configured controller index for the CNA kernel
    [/cover] */
    for (ActNodeCount = 0U; ActNodeCount < CAN_17_MCMCAN_NOOF_NODES_PER_KERNEL;
         ActNodeCount++)
    {
      /* Set with CAN node Hw index for clock set */
      /* [cover parentID={B54DCAF8-A50A-4b7f-B186-E61620D07A25}]
      Check node is used
      [/cover] */
      if (TRUE == ConfigPtr->
              CanMCMModuleConfigPtr[KernelIndx].CanUsedHwCfgIndx[ActNodeCount])
      {
        /* Set configured module with clock selection as enable */
        ClockSelConfigValue |= ((Ifx_UReg_32Bit)CAN_17_MCMCAN_MCR_CLKSEL_SET <<
                               (ActNodeCount * CAN_17_MCMCAN_CLK_SHIFT_MASK));
      }
    }
    MCRValueTemp |= (CAN_17_MCMCAN_CLKSEL_WRITE_ENABLE_MASK |
                                                           ClockSelConfigValue);

    /* Set MCR.CI and MCR.CCCE to enable clock selection register write
    Set Clock selection for both Sync and Sync of selected Nodes in the
    SubSystem.
    */
    MCMBaseAddressPtr->MCR.U = (Ifx_UReg_32Bit)MCRValueTemp;

    MCRValueTemp &= ~(CAN_17_MCMCAN_CLKSEL_WRITE_ENABLE_MASK);

    /* Reset MCR.CI and MCR.CCCE to Clock Change disabled  */
    MCMBaseAddressPtr->MCR.U = MCRValueTemp;

    MCRValueTemp = MCMBaseAddressPtr->MCR.U;

    /* start RAM Initialization */
    MCMBaseAddressPtr->MCR.U |= CAN_17_MCMCAN_CLKSEL_WRITE_ENABLE_MASK;

    /* MISRA2012_RULE_11_3_JUSTIFICATION: Typecasting to uint32 is
    required in order to maintain a common interface to check bits
    that are getting updated by hardware */
    ReturnValue = Can_17_McmCan_lTimeOut((const volatile uint32 *)            \
                                (&(MCMBaseAddressPtr->MCR.U)),                \
                              (uint32)CAN_17_MCMCAN_CLKSEL_WRITE_ENABLE_MASK, \
                                       CAN_17_MCMCAN_EQUAL);

    /*Check if timeout has occured*/
    /* [cover parentID={6AF3C846-1225-4ae9-99A8-8CB04FB865CD}]
    Is Hw is set properly within the Time-out
    [/cover] */
    if (E_OK == ReturnValue)
    {
      /* Wait until CANn_MCR.RBUSY is 0b */
      /* MISRA2012_RULE_11_3_JUSTIFICATION: Typecasting to uint32 is
      required in order to maintain a common interface to check bits
      that are getting updated by hardware */
      ReturnValue = Can_17_McmCan_lTimeOut((const volatile uint32 *)          \
                                        (&(MCMBaseAddressPtr->MCR.U)),        \
                                      (uint32) CAN_17_MCMCAN_MCR_RBUSY_STATUS,\
                                     CAN_17_MCMCAN_NOT_EQUAL);

      /*No timeout occurs*/
      /* [cover parentID={DB6D17B2-06F1-44a8-B83A-5B0B87F2800A}]
      Is Status Ok?
      [/cover] */
      if (E_OK == ReturnValue)
      {
        /* Initialize the RAM */
        MCMBaseAddressPtr->MCR.B.RINIT = 0U;

        MCMBaseAddressPtr->MCR.B.RINIT = IFX_CAN_MCR_RINIT_MSK;

        /*Store the MCR value*/
        MCRValueTemp = MCMBaseAddressPtr->MCR.U;

        /* Wait until CANn_MCR.RBUSY is 0b */
        /* MISRA2012_RULE_11_3_JUSTIFICATION: Typecasting to uint32 is
        required in order to maintain a common interface to check bits
        that are getting updated by hardware */
        ReturnValue = Can_17_McmCan_lTimeOut((const volatile uint32 *)        \
                                        (&(MCMBaseAddressPtr->MCR.U)),        \
                                      (uint32) CAN_17_MCMCAN_MCR_RBUSY_STATUS,\
                                             CAN_17_MCMCAN_NOT_EQUAL);

        MCMBaseAddressPtr->MCR.U &= ~CAN_17_MCMCAN_CLKSEL_WRITE_ENABLE_MASK;
      }
    }
  }
  return ReturnValue;
}

/*******************************************************************************
** Traceability   : [cover parentID={7C4B0203-2A5D-4ae3-8DFD-C262F50F1971}]   **
**  Syntax          : static Std_ReturnType                                   **
**                    Can_17_McmCan_lInitController                           **
**                   (                                                        **
**                     const uint8 ControllerId,                              **
**                     const Can_17_McmCan_CoreConfigType *const CoreConfigPtr,*
**                     Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr      **
**                   )                                                        **
**                                                                            **
**  Description      : Initializes CAN Controller Registers and Enables CAN   **
**                    Controller Interrupts                                   **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Non-Reentrant                                          **
**                                                                            **
**  Parameters (in)  : ControllerId: Index of core specific Controller        **
**                     CoreConfigPtr - Pointer to CAN driver configuration    **
**                     CoreGlobalPtr - Pointer to global structure            **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Parameters (in-out) : none                                                **
**                                                                            **
**  Return value     : E_OK: Controller specific initialization successful    **
**                     E_NOT_OK: Controller specific initialization failed    **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Can_17_McmCan_lInitController(const uint8 ControllerId,
  const Can_17_McmCan_CoreConfigType *const CoreConfigPtr,
  const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr)
{
  /*Can controller node address pointer*/
  volatile Ifx_CAN_N *NodeRegAddressPtr;

  /*Baud rate configuration pointer*/
  const Can_17_McmCan_ControllerBaudrateConfigType *BaudratePtr;

  /*Local variable to store the node address register values*/
  const volatile uint32 *RegAddressPtr;

  /*Local variable to calculate interrupt line offset*/
  uint8 IntLineOffset;

  /*Baud rate default configuration*/
  uint16 BaudRateDefaultCfg;

  /*Return value of the function*/
  Std_ReturnType ReturnValue = E_NOT_OK;

  /* Variable to store return value for local functions */
  Std_ReturnType TxReturnValue = E_NOT_OK;
  Std_ReturnType RxReturnValue = E_NOT_OK;

  /*Calculate the base offset for interrupt*/
  IntLineOffset = CAN_17_MCMCAN_INTLINE_OFFSET *
                  CoreConfigPtr->
                      CanControllerConfigPtr[ControllerId].CanControllerHwId;

  /* Read the exact Node Start address */
  NodeRegAddressPtr = CoreConfigPtr->
                         CanControllerConfigPtr[ControllerId].CanNodeAddressPtr;

  /* Reset Interrupt Lines before assignment for different operations */
  NodeRegAddressPtr->GRINT1.U = (uint32)CAN_17_MCMCAN_BIT_RESET_VAL;
  NodeRegAddressPtr->GRINT2.U = (uint32)CAN_17_MCMCAN_BIT_RESET_VAL;

  /* Interrupt Line assignment for BUSOFF */
  NodeRegAddressPtr->GRINT1.B.BOFF = CAN_17_MCMCAN_BOFF_POS + IntLineOffset;

  /* Interrupt Line assignment for TxEventFIFO */
  NodeRegAddressPtr->GRINT1.B.TEFIFO = CAN_17_MCMCAN_BIT_SET_VAL +
                                                                  IntLineOffset;

  /* Interrupt Line assignment for RxFIFO buffer watermark level */
  NodeRegAddressPtr->GRINT1.B.WATI = CAN_17_MCMCAN_WAT_POS + IntLineOffset;

  /* Interrupt Line assignment for dedicated receive buffer */
  NodeRegAddressPtr->GRINT2.B.REINT = CAN_17_MCMCAN_BIT_RESET_VAL +
                                                                IntLineOffset;

  /* Interrupt Line assignment for Rx FIFO 0 buffer Full */
  NodeRegAddressPtr->GRINT2.B.RXF0F = CAN_17_MCMCAN_RXF0_POS + IntLineOffset;

  /* Interrupt Line assignment for Rx FIFO 1 buffer Full */
  NodeRegAddressPtr->GRINT2.B.RXF1F = CAN_17_MCMCAN_RXF1_POS + IntLineOffset;

  /* Check Controller in Software Initialization mode with Configuration
  Change Enable. */
  /* [cover parentID={7DC66300-8269-47a7-9F98-6A1790EEF225}]
  Controller in software initialization mode with config change enabled
  [/cover] */
  if (CAN_17_MCMCAN_BIT_CLEAR_VAL == NodeRegAddressPtr->CCCR.B.INIT)
  {
    /* Set with Initialization mode */
    NodeRegAddressPtr->CCCR.B.INIT = 1U;

    /* Set with Register Address */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: Typecasting to uint32 is
    required in order to maintain a common interface to check bits
    that are getting updated by hardware */
    RegAddressPtr = (const volatile uint32 *)(&(NodeRegAddressPtr->CCCR.U));

    /* Wait until the INIT bits become set */
    ReturnValue = Can_17_McmCan_lTimeOut(
                       (const volatile uint32 *)RegAddressPtr,
                       CAN_17_MCMCAN_NODE_INIT_CCE_SET,
                       CAN_17_MCMCAN_EQUAL);
  }
  else
  {
     ReturnValue = E_OK;
  }
  /* Check Hw is set properly or not within the Time-out */
  /* [cover parentID={95D450C7-4431-41d6-B854-FFFF7E96C5B6}]
  If Hw is set properly
  [/cover] */
  if (E_OK == ReturnValue)
  {
    /* Set Configuration Change Enable bit */
    NodeRegAddressPtr->CCCR.B.CCE = 1;

    /* Set with Register Address */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: Typecasting to uint32 is
    required in order to maintain a common interface to check bits
    that are getting updated by hardware */
    RegAddressPtr = (const volatile uint32 *)(&(NodeRegAddressPtr->CCCR.U));

    /* Wait until the Configuration Change Enable bits become set */
    /* [cover parentID={06E7E4FF-25A9-445b-97EE-C439BBC4FE1F}]
    Wait until the Configuration Change Enable bits become set
    [/cover] */
    ReturnValue = Can_17_McmCan_lTimeOut(
                      (const volatile uint32 *)RegAddressPtr,
                       CAN_17_MCMCAN_CCCR_CCE_SET_MASK,
                       CAN_17_MCMCAN_EQUAL);

    /*Check if timeout has occured*/
    /* [cover parentID={76016B53-1F74-438e-9A08-6AF916FC5C18}]
    Is Status Ok?
    [/cover] */
    if (E_OK == ReturnValue)
    {
      /* Reset RAM Watchdog Register */
      NodeRegAddressPtr->RWD.U = (uint32)CAN_17_MCMCAN_BIT_RESET_VAL;

      /* Reset Controller Configuration Register */
      NodeRegAddressPtr->CCCR.B.ASM = CAN_17_MCMCAN_BIT_RESET_VAL;
      NodeRegAddressPtr->CCCR.B.CSR = CAN_17_MCMCAN_BIT_RESET_VAL;
      NodeRegAddressPtr->CCCR.B.MON = CAN_17_MCMCAN_BIT_RESET_VAL;
      NodeRegAddressPtr->CCCR.B.DAR = CAN_17_MCMCAN_BIT_RESET_VAL;
      NodeRegAddressPtr->CCCR.B.TEST = CAN_17_MCMCAN_BIT_RESET_VAL;
      NodeRegAddressPtr->CCCR.B.FDOE = CAN_17_MCMCAN_BIT_RESET_VAL;
      NodeRegAddressPtr->CCCR.B.BRSE = CAN_17_MCMCAN_BIT_RESET_VAL;
      NodeRegAddressPtr->CCCR.B.PXHD = CAN_17_MCMCAN_BIT_RESET_VAL;
      NodeRegAddressPtr->CCCR.B.EFBI = CAN_17_MCMCAN_BIT_RESET_VAL;
      NodeRegAddressPtr->CCCR.B.TXP = CAN_17_MCMCAN_BIT_RESET_VAL;
      NodeRegAddressPtr->CCCR.B.NISO = CAN_17_MCMCAN_BIT_RESET_VAL;

      /* Set with Register Address */
      /* MISRA2012_RULE_11_3_JUSTIFICATION: Typecasting to uint32 is
      required in order to maintain a common interface to check bits
      that are getting updated by hardware */
      RegAddressPtr = (const volatile uint32 *)(&(NodeRegAddressPtr->CCCR.U));

      /* Wait until the CCCR register is reset */
      /* [cover parentID={23376274-C014-456e-8FC6-034BB36F5F47}]
      Wait until the CCCR register is reset
      [/cover] */
      ReturnValue = Can_17_McmCan_lTimeOut(
                                     (const volatile uint32 *)RegAddressPtr,
                                     CAN_17_MCMCAN_CCCR_RESET_MASK,
                                     CAN_17_MCMCAN_AND);

      /*Check if timeout has occured*/
      /* [cover parentID={834C8289-C881-4251-B7E1-428C2179D7D8}]
      Is Status Ok?
      [/cover] */
      if (E_OK == ReturnValue)
      {
        /* Set NPCR with the Rxinput/Loopback functionality */
        NodeRegAddressPtr->NPCR.U = CoreConfigPtr->
            CanControllerConfigPtr[ControllerId].CanNPCRValue;

        /* Read Baud rate configuration Index */
        BaudratePtr = CoreConfigPtr->CanBaudrateConfigPtr;

        /* Select default baud rate configuration of the controller */
        BaudRateDefaultCfg = CoreConfigPtr->
            CanControllerConfigPtr[ControllerId].CanDefaultBRCfgIndx;

        /* Set NBTP with Nominal baud-rate */
        NodeRegAddressPtr->NBTP.U =
            BaudratePtr[BaudRateDefaultCfg].CanControllerBaudrate;

        #if (CAN_17_MCMCAN_FD_ENABLE == STD_ON)
        /* CAN FD configuration */
        /* [cover parentID={56D0C81C-41E5-4c75-AEE1-176B5352FF46}]
        Is CAN FD configuration enabled?
        [/cover] */
        if (TRUE == BaudratePtr[BaudRateDefaultCfg].CanFdConfigEnabled)
        {
          /* Invoke internal function for set FD baud-rate */
          /* [cover parentID={7250DC4B-1EDB-4f7f-B93B-11A43289142F}]
          Invoke internal function to set FD baud-rate
          [/cover] */
          ReturnValue = Can_17_McmCan_lFDSetBaudrate(ControllerId,
                                 BaudratePtr[BaudRateDefaultCfg].CanFDIndex,
                                 CoreConfigPtr);
        }
        /* [cover parentID={E2D9AA37-4D28-46a6-9DA1-9203C2BAA72D}]
        Is Status Ok?
        [/cover] */
        if (E_OK == ReturnValue)
        #endif
        {
          /* Reset TX Buffer Transmission Interrupts */
          NodeRegAddressPtr->TX.BTIE.U = (uint32)CAN_17_MCMCAN_BIT_RESET_VAL;

          /* Clear All pending Interrupts */
          NodeRegAddressPtr->IR.U = CAN_17_MCMCAN_CLEAR_ALL_INTERRUPTS;

          /*Check if the configuation if for SID filter.
          In case it is for XID the pointer will be NULL*/
          /* [cover parentID={769C6736-DB97-4e11-B7D2-0BD181691F57}]
          Is SID Config pointer valid?
          [/cover] */
          if (NULL_PTR != CoreConfigPtr->CanSIDFilterConfigPtr)
          {
            /* Invoke function to Set standard ID filter setting */
            Can_17_McmCan_lSIDFilterConfig(ControllerId, CoreConfigPtr);
          }

          /*Check if the configuation if for SID filter.
          In case it is for XID the pointer will be NULL*/
          /* [cover parentID={1209C71F-83EF-46e2-9D8E-CAE8D2292585}]
          Check for XID filter config pointer validity
          [/cover] */
          if (NULL_PTR != CoreConfigPtr->CanXIDFilterConfigPtr)
          {
            /* Invoke function to Set Extended ID filter setting */
            Can_17_McmCan_lXIDFilterConfig(ControllerId, CoreConfigPtr);
          }

          /* Configure HW Recieve Message Objects*/
          /* [cover parentID={C9C3A33F-31B6-4a72-A4DA-991C89B1644D}]
          Receive Message RAM settings
          [/cover] */
          RxReturnValue = Can_17_McmCan_lInitRxMsgObj(ControllerId,
                                                      CoreConfigPtr);
          /* [cover parentID={F34F2A57-68EF-485c-A3BB-7CA922FD28F6}]
          Is Tx Hw object configuration NULL?
          [/cover] */
          if (NULL_PTR != CoreConfigPtr->CanTxHwObjectConfigPtr)
          {
            /* Configure HW Transmit Message Objects*/
            /* [cover parentID={C999A855-4697-4ca6-9993-31E1D6AB5A82}]
            Transmit MSG RAM Settings
            [/cover] */
            TxReturnValue = Can_17_McmCan_lInitTxMsgObj(ControllerId,
                                              CoreGlobalPtr, CoreConfigPtr);
          }
          else
          {
            TxReturnValue = E_OK;
          }
          /* Check whether Tx and Rx message objects are initialized
          successfully*/
          /* [cover parentID={C7A8C644-5DC0-419f-9A27-E1852BD5903C}]
          Check whether Tx and Rx message objects are initialized
          successfully
          [/cover] */
          if ((E_OK == RxReturnValue) && (E_OK == TxReturnValue))
          {
            /* Set Controller with STOP mode */
            /* [cover parentID={7A66CD62-B930-477a-BC98-B30C55192E29}]
            Set Controller mode to STOPPED
            [/cover] */
            CoreGlobalPtr->CanControllerModePtr[ControllerId] =
                                                        CAN_17_MCMCAN_STOPPED;

            #if (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON)

            /* Deactivate Pretended Networking after initialization */
            /* [cover parentID={068C379F-B8E3-41aa-817F-07F3658B0148}]
            Deactivate Pretended Networking after initialization
            [/cover] */
            CoreGlobalPtr->CanIcomEnableStatusPtr[ControllerId] = FALSE;
            CoreGlobalPtr->CanIcomBlockWriteCallsPtr[ControllerId] = FALSE;
            #endif
          }
          else
          {
            ReturnValue = E_NOT_OK;
          }
        }
      }
    }
  }
  return ReturnValue;
}
/*******************************************************************************
** Traceability   : [cover parentID={2ABF5A62-2C21-4dbd-A582-667E61C8FB73}]   **
**                                                                            **
**  Syntax           : static Std_ReturnType Can_17_McmCan_lInitTxMsgObj      **
**                    (                                                       **
**                     const uint8 Controller                                 **
**                     Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr      **
**                     const Can_17_McmCan_CoreConfigType *const CoreConfigPtr *
**                    )                                                       **
**                                                                            **
**  Description    : Initializes transmit message objects for the controller  **
**                   associated                                               **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Non-Reentrant                                          **
**                                                                            **
**  Parameters (in)  : CoreGlobalPtr: Index of core specific Controller       **
**                     CoreConfigPtr - Pointer to CAN driver configuration    **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Parameters (in-out) : CoreGlobalPtr - Pointer to global structure         **
**                                                                            **
**  Return value     : E_OK: Controller associated transmit message objects   **
**                           initialized successfully                         **
**                     E_NOT_OK: Controller associated transmit message       **
**                               initialization failed                        **                                                   **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Can_17_McmCan_lInitTxMsgObj(const uint8 Controller,
    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr)
{
  /*Can controller node address pointer*/
  volatile Ifx_CAN_N *NodeRegAddressPtr;

  /*TX Buffer start address*/
  uint32 TxBufferStartAddress;

  /*TX event start address*/
  uint32 TxEventStartAddress;

  /*TX slot index*/
  uint32 TxSlotIndex = 0U;

  /*Return value of the function*/
  Std_ReturnType TxMsgObjInitReturnValue = E_NOT_OK;

  /* MISRA2012_RULE_19_2_JUSTIFICATION:Union is used to access the register
  contents directly without shift and OR operation. */
  Ifx_CAN_N_TX_EFC TxTempEvntReg;

  /* MISRA2012_RULE_19_2_JUSTIFICATION:Union is used to access the register
  contents directly without shift and OR operation. */
  Ifx_CAN_N_TX_BC TxTempbuffReg;

  /* MISRA2012_RULE_19_2_JUSTIFICATION:Union is used to access the register
  contents directly without shift and OR operation. */
  Ifx_CAN_N_TX_ESC TxTempbuffSizeReg;

  /* Get Node Register address */
  NodeRegAddressPtr = CoreConfigPtr->
                           CanControllerConfigPtr[Controller].CanNodeAddressPtr;

  /* Set with MessageRAM Tx buffer section start address */
  TxBufferStartAddress = CoreConfigPtr->
                            CanControllerMsgRAMMapConfigPtr[Controller].
                            CanControllerMsgRAMMap[CAN_17_MCMCAN_TBSA];
  /* Set with value Zero */
  TxTempEvntReg.U = 0;

  /* Set with value Zero */
  TxTempbuffReg.U = 0;

  /* Set with value Zero */
  TxTempbuffSizeReg.U = 0;

  /* Check Tx Event buffer is allocated or not */
  /* [cover parentID={1691C839-6EFD-4be0-A0A0-37513FAA4220}]
  Is Tx Event buffer is allocated?
  [/cover] */
  if (CAN_17_MCMCAN_ADDRESS_CHECK != TxBufferStartAddress)
  {
    /* Set with MessageRAM Tx Event buffer section start address */
    TxEventStartAddress = CoreConfigPtr->
                             CanControllerMsgRAMMapConfigPtr[Controller].
                             CanControllerMsgRAMMap[CAN_17_MCMCAN_EFSA];

    /* Set TX Event FIFO Size */
    TxTempEvntReg.B.EFS = CoreConfigPtr->
                          CanControllerMsgRAMMapConfigPtr[Controller].
                          CanTxEvntFIFOSize;

    /* Set Tx Event FIFO Configuration register with Event FIFO Start Address*/
    TxTempEvntReg.B.EFSA = (uint16)((TxEventStartAddress &
                                   CAN_17_MCMCAN_RAM_ADDRESS_OFFSET_MASK) >>
                                   CAN_17_MCMCAN_RAM_ADDRESS_SHIFT_MASK);

    /* Set Offset for the TBSA */
    TxTempbuffReg.B.TBSA = (uint16)((TxBufferStartAddress &
                                   CAN_17_MCMCAN_RAM_ADDRESS_OFFSET_MASK) >>
                                   CAN_17_MCMCAN_RAM_ADDRESS_SHIFT_MASK);

    #if (CAN_17_MCMCAN_MULTIPLEXED_TRANSMISSION == STD_ON)
    /*  Check if Queue is Enabled */
    /* [cover parentID={F464C10C-74ED-4a8e-9EED-A7E335710EC6}]
    Is Tx Queue status is Enabled?
    [/cover] */
    if (TRUE == CoreConfigPtr->CanControllerMsgRAMMapConfigPtr[Controller].
                                                               CanTxQueueStatus)
    {
      /* Set for Tx Queue operation */
      TxTempbuffReg.B.TFQM = 1;
      /* Set Tx Queue size */
      TxTempbuffReg.B.TFQS = CoreConfigPtr->
                     CanControllerMsgRAMMapConfigPtr[Controller].CanTxQueueSize;

      /* Set No of used TX dedicated buffer */
      TxTempbuffReg.B.NDTB = CoreConfigPtr->
                  CanControllerMsgRAMMapConfigPtr[Controller].CanTxDedBuffCount;
    }
    else
    #endif
    {
      /* Set No of used TX dedicated buffer */
      TxTempbuffReg.B.NDTB = CoreConfigPtr->
        CanControllerMsgRAMMapConfigPtr[Controller].CanTxDedBuffCount;
    }

    /* Clear mask before usage */
    CoreGlobalPtr->CanTxMaskPtr[Controller] = 0;

    /* Arrive at the Tx slots available */
    /* [cover parentID={95CB2453-8B84-4810-A01F-63A10493ED47}]
    Update Transmit slot Mask
    [/cover] */
    for (TxSlotIndex = 0; TxSlotIndex < ((uint32)((uint32)TxTempbuffReg.B.NDTB +
                                                (uint32)TxTempbuffReg.B.TFQS));
                                                TxSlotIndex++)
    {
       CoreGlobalPtr->CanTxMaskPtr[Controller] |= ((uint32)1U << TxSlotIndex);
    }

    /* Copy to back-up buffer mask as well */
    CoreGlobalPtr->BackupCanTxMaskPtr[Controller] =
                                       CoreGlobalPtr->CanTxMaskPtr[Controller];
    /* [cover parentID={18D66B84-5E8D-4ee2-8F69-93CEE8074D73}]
    CAN FD is enabled
    [/cover] */
    #if (CAN_17_MCMCAN_FD_ENABLE == STD_ON)
    /* [cover parentID={6B1BCFFE-994D-4718-A3C0-410B2632829C}]
    Is FD Support enabled for the current controller?
    [/cover] */
    /* Load Tx Buffer Configuration register with configuration settings */
    if (TRUE ==
        CoreConfigPtr->CanControllerConfigPtr[Controller].CanFDSupport)
    {
      /* Set Tx Buffer Data Field Size for FD support */
      TxTempbuffSizeReg.B.TBDS = 7;
    }
    #endif

    /* Set Event FIFO configuration Register */
    NodeRegAddressPtr->TX.EFC.U = TxTempEvntReg.U;

    /* Set Tx message buffer configuration Register */
    NodeRegAddressPtr->TX.BC.U = TxTempbuffReg.U;

    /* Set Tx message buffer size configuration Register */
    NodeRegAddressPtr->TX.ESC.U = TxTempbuffSizeReg.U;
  }
  /* MISRA2012_RULE_13_5_JUSTIFICATION: And operator required to check the
  values of the SFRs.This warning is due to the volatile
  qualifier in the SFRs and no side-affect foreseen by violation.*/
  /* Check whether Tx FIFO and FIFO Queue Status Regsiter bits are reset */
  /* [cover parentID={38BD5059-5AFF-4c6b-B1D0-CB431B2696CC}]
  Check whether Tx FIFO and FIFO Queue Status Regsiter bits are reset
  [/cover] */
  if(((uint32)CAN_17_MCMCAN_BIT_RESET_VAL == NodeRegAddressPtr->TX.EFS.U) && \
     ((uint32)CAN_17_MCMCAN_BIT_RESET_VAL == NodeRegAddressPtr->TX.FQS.U))
  {
    TxMsgObjInitReturnValue = E_OK;
  }
  return TxMsgObjInitReturnValue;
}

/*******************************************************************************
** Traceability   : [cover parentID={E44FFE7B-9375-4fc3-80C1-1FBBEEF7C5F3}]   **
**  Syntax           : static void Can_17_McmCan_lInitRxMsgObj                **
**                    (                                                       **
**                     const uint8 Controller                                 **
**                     const Can_17_McmCan_CoreConfigType *const CoreConfigPtr**
**                    )                                                       **
**                                                                            **
** Description    :The function initializes receive message objects for the   **
**                 associated controller.                                     **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Non-Reentrant                                          **
**                                                                            **
**  Parameters (in)  : ControllerId: Index of core specific Controller        **
**                     CoreConfigPtr - Pointer to CAN driver configuration    **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Parameters (in-out) : none                                                **
**                                                                            **
**  Return value     : E_OK: Controller associated receive message objects    **
**                           initialized successfully                         **
**                     E_NOT_OK: Controller associated receive message        **
**                               initialization failed                        **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Can_17_McmCan_lInitRxMsgObj(const uint8 Controller,
  const Can_17_McmCan_CoreConfigType *const CoreConfigPtr)
{
  /*Can controller node address pointer*/
  volatile Ifx_CAN_N *NodeRegAddressPtr;

  /* MISRA2012_RULE_19_2_JUSTIFICATION:Union is used to access the register
  contents directly without shift and OR operation. */
  Ifx_CAN_N_RX_F0C RxTempFIFO0Config;

  /* MISRA2012_RULE_19_2_JUSTIFICATION:Union is used to access the register
  contents directly without shift and OR operation. */
  Ifx_CAN_N_RX_F1C RxTempFIFO1Config;

  /*Rx buffer configuration data*/
  uint32 RxBufferCfgData;

  /*Return value of the function*/
  Std_ReturnType RxMsgObjInitReturnValue = E_NOT_OK;

  /*Initialize FIFO configurations*/
  RxTempFIFO0Config.U = 0U;
  RxTempFIFO1Config.U = 0U;

  /* [cover parentID={0797ADBD-EF75-444b-9129-150A80EF83B9}]
  CAN FD is enabled
  [/cover] */
  #if (CAN_17_MCMCAN_FD_ENABLE == STD_ON)
    /* MISRA2012_RULE_19_2_JUSTIFICATION:Union is used to access the register
  contents directly without shift and OR operation. */
  Ifx_CAN_N_RX_ESC RxTempBuffSizeConfig;

  /*Initialize RX Buffer configurations*/
  RxTempBuffSizeConfig.U = 0U;
  #endif

  /* Get Node Register address */
  NodeRegAddressPtr =
      CoreConfigPtr->CanControllerConfigPtr[Controller].CanNodeAddressPtr;

  /* Reset New Data registers */
  NodeRegAddressPtr->NDAT1.U =
      NodeRegAddressPtr->NDAT1.U & CAN_17_MCMCAN_NDATA_RESET_MASK;
  NodeRegAddressPtr->NDAT2.U =
      NodeRegAddressPtr->NDAT2.U & CAN_17_MCMCAN_NDATA_RESET_MASK;

  /* Set Filter for reject non matching and RTR message */
  /* [cover parentID={FAED0B2A-27ED-4114-9D61-85227F5AC06F}]
  Set Filter for reject non matching and RTR message
  [/cover] */
  NodeRegAddressPtr->GFC.U = CAN_17_MCMCAN_GFC_REJT_RTR_NONMATCH;

  /* Copy Rx buffer start address */
  RxBufferCfgData = CoreConfigPtr->
                       CanControllerMsgRAMMapConfigPtr[Controller].
                       CanControllerMsgRAMMap[CAN_17_MCMCAN_RBSA];

  /* Reset Rx Buffer Configuration before setting offset for the RBSA */
  NodeRegAddressPtr->RX.BC.U = (uint32)CAN_17_MCMCAN_BIT_RESET_VAL;

  /*If Address is not NULL*/
  /* [cover parentID={24CF46B0-4388-48e8-A3DF-4EAB7C2649A8}]
  Is RX Buffer address NULL?
  [/cover] */
  if (CAN_17_MCMCAN_ADDRESS_CHECK != RxBufferCfgData)
  {
    /* Set Offset for the RBSA */
    NodeRegAddressPtr->RX.BC.B.RBSA = (uint16)((RxBufferCfgData &
                                      CAN_17_MCMCAN_RAM_ADDRESS_OFFSET_MASK) >>
                                      CAN_17_MCMCAN_MSGRAM_SHIFT_MASK);

    /*Is FD Support is enabled*/
    /* [cover parentID={6438DE3F-D6E4-461b-926B-6535CB1F7C04}]
    CAN FD is enabled
    [/cover] */
    #if (CAN_17_MCMCAN_FD_ENABLE == STD_ON)
    /* [cover parentID={773BB5A2-4B6D-4945-A657-FCB9DABE9754}]
    Is FD Support is enabled?
    [/cover] */
    if (TRUE == CoreConfigPtr->CanControllerConfigPtr[Controller].CanFDSupport)
    {
      /* Set RX Buffer Data Field Size for FD support */
      RxTempBuffSizeConfig.B.RBDS = IFX_CAN_N_RX_ESC_RBDS_MSK;
    }
    #endif
  }

  /* Read FIFO0 Start Address of requested controller */
  RxBufferCfgData = CoreConfigPtr->CanControllerMsgRAMMapConfigPtr[Controller].
                       CanControllerMsgRAMMap[CAN_17_MCMCAN_F0SA];
  /*If Address Exists*/
  /* [cover parentID={CD52627B-708D-4e86-B3A7-41BF341D28A2}]
  Is RX FIFO0 address NULL?
  [/cover] */
  if (CAN_17_MCMCAN_ADDRESS_CHECK != RxBufferCfgData)
  {
    /* Set Offset for the F0SA */
    RxTempFIFO0Config.B.F0SA = (uint16)((RxBufferCfgData &
                                 CAN_17_MCMCAN_RAM_ADDRESS_OFFSET_MASK) >>
                                 CAN_17_MCMCAN_MSGRAM_SHIFT_MASK);
    /* Set with the Rx FIFO0 Size*/
    RxTempFIFO0Config.B.F0S = CoreConfigPtr->
                     CanControllerMsgRAMMapConfigPtr[Controller].CanRxFIFO0Size;
    /* Set with the Rx FIFO0 Threshold (WatermarkLevel)*/
    RxTempFIFO0Config.B.F0WM = CoreConfigPtr->
                CanControllerMsgRAMMapConfigPtr[Controller].CanRxFIFO0Threshold;

    /*If FD support is enabled*/
    /* [cover parentID={326B0439-1519-4d2e-9659-AEAD5C2E7104}]
    CAN FD is enabled
    [/cover] */
    #if (CAN_17_MCMCAN_FD_ENABLE == STD_ON)
    /* [cover parentID={32E8045B-8F18-4e47-9AF5-11FA949AEEF5}]
    If FD Support is enabled
    [/cover] */
    if (TRUE == CoreConfigPtr->CanControllerConfigPtr[Controller].CanFDSupport)
    {
      /* Set RX Buffer Data Field Size for FD support */
      RxTempBuffSizeConfig.B.F0DS = IFX_CAN_N_RX_ESC_F0DS_MSK;
    }
    #endif
    /* Set the configuration */
    NodeRegAddressPtr->RX.F0C.U = RxTempFIFO0Config.U;
  }
  /* Read FIFO1 Start Address of requested controller */
  RxBufferCfgData = CoreConfigPtr->
                       CanControllerMsgRAMMapConfigPtr[Controller].
                       CanControllerMsgRAMMap[CAN_17_MCMCAN_F1SA];
  /*If Address Exists*/
  /* [cover parentID={E7206761-88E7-4868-A4F0-12DBC6BEC78C}]
  If Address Exists
  [/cover] */
  if (CAN_17_MCMCAN_ADDRESS_CHECK != RxBufferCfgData)
  {
    /* Set Offset for the RXFIFO1 */
    RxTempFIFO1Config.B.F1SA = (uint16)((RxBufferCfgData &
                                CAN_17_MCMCAN_RAM_ADDRESS_OFFSET_MASK) >>
                                CAN_17_MCMCAN_MSGRAM_SHIFT_MASK);
    /* Set with Rx FIFO 1 Size*/
    RxTempFIFO1Config.B.F1S = CoreConfigPtr->
                     CanControllerMsgRAMMapConfigPtr[Controller].CanRxFIFO1Size;
    /* Set with the Rx FIFO0 Threshold (WatermarkLevel)*/
    RxTempFIFO1Config.B.F1WM = CoreConfigPtr->
                CanControllerMsgRAMMapConfigPtr[Controller].CanRxFIFO1Threshold;

    #if (CAN_17_MCMCAN_FD_ENABLE == STD_ON)
    /*If FD Support is enabled*/
    /* [cover parentID={82BBE19F-721C-4568-A758-E4DA188A1824}]
    FD support Enabled
    [/cover] */
    if (TRUE == CoreConfigPtr->CanControllerConfigPtr[Controller].CanFDSupport)
    {
      /* Set RX Buffer Data Field Size for FD support */
      /* [cover parentID={8414C6CC-79E6-44e2-ABA8-F8E90F8DE57F}]
      Set RX Buffer Data Field Size for FD support
      [/cover] */
      RxTempBuffSizeConfig.B.F1DS = IFX_CAN_N_RX_ESC_F1DS_MSK;
    }
    #endif

    /* Set the configuration */
    NodeRegAddressPtr->RX.F1C.U = RxTempFIFO1Config.U;
  }

  #if (CAN_17_MCMCAN_FD_ENABLE == STD_ON)
  /* Reset Rx Buffer/FIFO element size configuration */
  NodeRegAddressPtr->RX.ESC.U = (uint32)CAN_17_MCMCAN_BIT_RESET_VAL;

  /* Set Rx Message RAM data Size */
  NodeRegAddressPtr->RX.ESC.U = RxTempBuffSizeConfig.U;
  #endif

  /* MISRA2012_RULE_13_5_JUSTIFICATION: And operator required to check the
  values of the SFRs.This warning is due to the volatile qualifier in the
  SFRs and no side-affect foreseen by violation.*/
  /* Check whether Rx FIFO and FIFO Queue Status Regsiter bits are reset */
  /* [cover parentID={7393AD59-1FEA-4520-B392-9837588DD2C0}]
  Check whether Rx FIFO and FIFO Queue Status Regsiter bits are reset
  [/cover] */
  if (((uint32)CAN_17_MCMCAN_BIT_RESET_VAL == NodeRegAddressPtr->RX.F0S.U) && \
      ((uint32)CAN_17_MCMCAN_BIT_RESET_VAL == NodeRegAddressPtr->RX.F1S.U))
  {
    RxMsgObjInitReturnValue = E_OK;
  }
  return RxMsgObjInitReturnValue;
}
#if (CAN_17_MCMCAN_DEINIT_API == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={61900072-6280-4d54-90C6-4411202FE204}]   **
**                                                                            **
**                                                                            **
**  Syntax          : static Std_ReturnType Can_17_McmCan_lCoreDeInit         **
**                   (                                                        **
**                     const Can_17_McmCan_CoreConfigType *const CoreConfigPtr *
**                     Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr      **
**                   )                                                        **
**                                                                            **
**  Description      : The function checks the Controller state assigned to   **
**                     the particular core                                    **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Non-Reentrant                                          **
**                                                                            **
**  Parameters(in)   :CoreConfigPtr- Pointer to core specific CAN driver      **
**                    configuration                                           **
**                    CoreGlobalPtr - Pointer to states of respective core    **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : E_OK: Controller in STOPPED or SLEEP state             **
**                     E_NOT_OK: Controller in STARTED state                  **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Can_17_McmCan_lCoreDeInit(
  const Can_17_McmCan_CoreConfigType *const CoreConfigPtr,
const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr)
{
  /*Variable to stote the return value of the local functions*/
  Std_ReturnType ReturnValue = E_OK;

  /*Variable to stote the CAN controller index*/
  uint8 CtrlIndex;

  CtrlIndex = 0U;

  /* Check for all CAN controllers*/
  /* [cover parentID={7AF0D0E9-5891-4a72-A3DA-DF87EC55B17A}]
  Check if the CAN controller mode is STARTED for all controllers
  [/cover] */
  while ((CtrlIndex < CoreConfigPtr->CanCoreContCnt) && (E_OK == ReturnValue))
  {
    /*The deinitialization is permitted only if the controller is in SLEEP or
    STOPPED state*/
    /* [cover parentID={77F7B55C-C0E8-4231-A1C7-2E06C5BFDB0C}]
    Is the controller mode STARTED?
    [/cover] */
    if (CAN_17_MCMCAN_STARTED == CoreGlobalPtr->CanControllerModePtr[CtrlIndex])
    {
      ReturnValue = E_NOT_OK;

      /* [cover parentID={B60FD1C0-CD29-4ba8-9DCB-5311E60A5AF7}]
      DET is enabled
      [/cover] */
      #if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      /* [cover parentID={0FEC7CF3-C172-4478-B27B-6AC93CFECFFE}]
       Report DET CAN_17_MCMCAN_E_TRANSITION
      [/cover] */
      (void)Det_ReportError(CAN_17_MCMCAN_MODULE_ID, CAN_17_MCMCAN_INSTANCE_ID,
                    CAN_17_MCMCAN_SID_DEINIT, CAN_17_MCMCAN_E_TRANSITION);
      #endif
    }
    else
    {
      ReturnValue = E_OK;
      /* Set current mode to UNINIT */
      CoreGlobalPtr->CanControllerModePtr[CtrlIndex] = CAN_17_MCMCAN_UNINIT;
    }
    /* Move to next controller */
    CtrlIndex++;
  }
  return ReturnValue;
}
#endif

#if (CAN_17_MCMCAN_SET_BAUDRATE_API == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={52E04677-D94C-44a9-B99A-215C596DA2E0}]   **
**                                                                            **
**  Syntax          : static void Can_17_McmCan_lSetBaudrate                  **
**                   (                                                        **
**                     const uint8 Controller,                                **
**                     const uint16 BaudrateIndx,                             **
**                     const Can_17_McmCan_CoreConfigType *const CoreConfigPtr**
**                   )                                                        **
**                                                                            **
** Description    :This function shall sets the CAN controller baud rate for  **
**                 nominal and check FD support is enabled within the         **
**                 configuration if enabled will call Can_lFDSetBaudrate()    **
**                 for set data bit timing                                    **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant for different controllers.                   **
**                     Non reentrant for the same controller.                 **
**                                                                            **
**  Parameters (in)  : ControllerId - CAN Controller Id                       **
**                     ControllerBaudrate - Register setting corresponding    **
**                                         to the baud-rate                   **
**                     CoreConfigPtr - Pointer to CAN driver configuration    **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : E_OK: The baud rate has been set as per the requested  **
**                     configuration ID
**                     E_NOT_OK: Timeout occured                              **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Can_17_McmCan_lSetBaudrate(const uint8 Controller,
                                              const uint16 BaudrateIndx,
                                              const Can_17_McmCan_CoreConfigType
                                              *const CoreConfigPtr)
{
  /*Local variable to store the start of the Baud reate config ID*/
  uint16 StartBaudrateCfgIndx;

  /*Local variable to store the end of the Baud reate config ID*/
  uint16 ActualBaudrateIndx;

  /*Pointer to the CAN node address*/
  volatile Ifx_CAN_N *NodeRegAddressPtr;

  /*Pointer to store baud rate configuration*/
  const Can_17_McmCan_ControllerBaudrateConfigType *BaudratePtr;

  /*Variable to store return value*/
  Std_ReturnType ReturnValue = E_NOT_OK;

  BaudratePtr = CoreConfigPtr->CanBaudrateConfigPtr;

  /* Get Node Register address */
  NodeRegAddressPtr = CoreConfigPtr->
                      CanControllerConfigPtr[Controller].CanNodeAddressPtr;

  /* Set with Start index of Baudrate configuration */
  StartBaudrateCfgIndx = CoreConfigPtr->
                         CanControllerConfigPtr[Controller].CanBaudrateCfgIndx;

  /* Set with exact Baudrate config index   */
  ActualBaudrateIndx = BaudrateIndx + StartBaudrateCfgIndx;

  /* Set NBTP with Nominal baud-rate */
  NodeRegAddressPtr->NBTP.U =
                          BaudratePtr[ActualBaudrateIndx].CanControllerBaudrate;

  /*If FD is enabled*/
  /* [cover parentID={FC860130-C9DA-430d-9630-1358E0FD206A}]
  Is CAN FD configuration is enabled?
  [/cover] */
  #if (CAN_17_MCMCAN_FD_ENABLE == STD_ON)
  /* Check if the FD configuration is */
  if (TRUE == BaudratePtr[ActualBaudrateIndx].CanFdConfigEnabled)
  {
    /* Invoke internal function for set FD baud-rate */
    ReturnValue = Can_17_McmCan_lFDSetBaudrate(Controller,
                BaudratePtr[ActualBaudrateIndx].CanFDIndex, CoreConfigPtr);
  }
  else
  {
    /* Disable FD Operation mode */
    NodeRegAddressPtr->CCCR.B.FDOE = CAN_17_MCMCAN_BIT_RESET_VAL;

    /* Wait until the INIT bits become set */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: Typecasting to uint32 is
    required in order to maintain a common interface to check bits
    that are getting updated by hardware */
    ReturnValue = Can_17_McmCan_lTimeOut((const volatile uint32 *)        \
                                          &NodeRegAddressPtr->CCCR.U,    \
                                          CAN_17_MCMCAN_CCCR_FDOE_STATUS,\
                                         CAN_17_MCMCAN_NOT_EQUAL);       \
  }
  #else

  ReturnValue = E_OK;

  #endif

  return ReturnValue;
}
#endif

#if (CAN_17_MCMCAN_FD_ENABLE == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={11202A75-6696-46fd-9135-52F35ACDDD6E}] **
**  Syntax         : static void Can_17_McmCan_lFDSetBaudrate                 **
**                 (                                                          **
**                    const uint8 Controller,                                 **
**                    const uint16 FdIndex,                                   **
**                    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr **
**                 )                                                          **
**                                                                            **
**  Description      : The function shall set the CAN controller FD baud rate.**
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant                                              **
**                                                                            **
**  Parameters (in)  : Controller - CAN Controller Id                         **
**                    FdIndex - Corresponding FD budrate array index          **
**                    CoreConfigPtr - Pointer to CAN driver configuration     **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Can_17_McmCan_lFDSetBaudrate(
    const uint8 Controller,
    const uint16 FdIndex,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr)
{
  /*Local variable to store the return value of the function*/
  Std_ReturnType ReturnValue = E_NOT_OK;

  volatile Ifx_CAN_N *NodeRegAddressPtr;

  /* Get Node Register address */
  NodeRegAddressPtr = CoreConfigPtr->
                      CanControllerConfigPtr[Controller].CanNodeAddressPtr;

  /* Set DBTP with FD configuration set */
  /* [cover parentID={78934EF7-E52F-4bb9-8ACA-836B12590D20}]
  Update DBTP register for the controller with FD baudrate value passed
  [/cover] */
  NodeRegAddressPtr->DBTP.U = CoreConfigPtr->
                           CanFDConfigParamPtr[FdIndex].CanControllerFDBaudrate;

  /*Update Transmitter Delay Compensation (TDCR) Register with the
  transmitter delay compensation value for the FD index passed*/
  /* [cover parentID={2544BBA5-38CE-4f6b-8639-9636525AD94E}]
  Update Transmitter Delay Compensation (TDCR) Register with the transmitter
  delay compensation value for the FD index passed
  [/cover] */
  NodeRegAddressPtr->TDCR.U = CoreConfigPtr->
                              CanFDConfigParamPtr[FdIndex].CanTrcvDelyComp;

  /* Set FD Operation mode as Enabled */
  /* [cover parentID={32EC2721-B304-407d-AFF7-447D2762F472}]
  FD Operation mode as enabled by setting FDOE
  [/cover] */
  NodeRegAddressPtr->CCCR.B.FDOE = IFX_CAN_N_CCCR_FDOE_MSK;

  /* Wait until the INIT bits become set */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: Typecasting to uint32 is
    required in order to maintain a common interface to check bits
    that are getting updated by hardware */
  ReturnValue = Can_17_McmCan_lTimeOut((const volatile uint32 *)        \
                                        &NodeRegAddressPtr->CCCR.U,     \
                                        CAN_17_MCMCAN_CCCR_FDOE_STATUS, \
                                       CAN_17_MCMCAN_EQUAL);

  /* [cover parentID={D02A3411-8ADB-4e7b-9210-F89C3F1F303F}]
  Is Status Ok?
  [/cover] */
  if (E_OK == ReturnValue)
  {
    /*Check if BRS is enabled */
    /* [cover parentID={35B6C3D4-FB01-4a5d-8A4E-389FF9CE03B4}]
    Is transmit BRS for the given CAN FD index is enabled
    [/cover] */
    if (TRUE == CoreConfigPtr->CanFDConfigParamPtr[FdIndex].CanTxBRSEnable)
    {
      /*Enable Bit rate switching for transmission by setting the BRSE bit
      of the CCCR register for the current controller passed*/
      /* [cover parentID={748FD593-B97F-48e6-93BE-94D5E6BD774E}]
      Enable Bit rate switching for transmission by setting the BRSE bit
      of the CCCR register for the current controller passed
      [/cover] */
      NodeRegAddressPtr->CCCR.B.BRSE = IFX_CAN_N_CCCR_BRSE_MSK;

      /* Wait until the INIT bits become set */
      /* MISRA2012_RULE_11_3_JUSTIFICATION: Typecasting to uint32 is
        required in order to maintain a common interface to check bits
        that are getting updated by hardware */
      ReturnValue = Can_17_McmCan_lTimeOut((const volatile uint32 *)         \
                                           &NodeRegAddressPtr->CCCR.U,      \
                                           CAN_17_MCMCAN_CCCR_BRSE_STATUS,  \
                                           CAN_17_MCMCAN_EQUAL);
    }
    else
    {
      /*Disable Bit rate switching for transmission by resetting the BRSE bit of
      the CCCR register for the current controller passed*/
      /* [cover parentID={C7BC8E2F-B84F-4d73-94A3-C67A4663276C}]
      Disable Bit rate switching for transmission by resetting the BRSE bit
      of the CCCR register for the current controller passed
      [/cover] */
      NodeRegAddressPtr->CCCR.B.BRSE = CAN_17_MCMCAN_BIT_RESET_VAL;

      /* Wait until the INIT bits become set */
      /* MISRA2012_RULE_11_3_JUSTIFICATION: Typecasting to uint32 is
      required in order to maintain a common interface to check bits
      that are getting updated by hardware */
      ReturnValue = Can_17_McmCan_lTimeOut((const volatile uint32 *)        \
                                           &NodeRegAddressPtr->CCCR.U,      \
                                           CAN_17_MCMCAN_CCCR_BRSE_STATUS,  \
                                           CAN_17_MCMCAN_NOT_EQUAL);        \
    }
  }
  return ReturnValue;
}
#endif

/*******************************************************************************
** Traceability   : [cover parentID={4F33647D-5A7C-4774-87CE-B218C63DFC52}]   **
**                                                                            **
**  Syntax         : static Std_ReturnType Can_17_McmCan_lSetControllerMode   **
**                  (const uint8 Controller,                                  **
**                   const Can_17_McmCan_ControllerState Transition)          **
**                                                                            **
**  Description      :The function controls the state machine transitions.    **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Non-Reentrant                                          **
**                                                                            **
**  Parameters (in)  : Controller - Associated CAN Controller Id              **
**                     Transition - Requested state transition                **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : E_OK: Service request accepted, state transition       **
**                     successful                                             **
**                     E_NOT_OK: Service request not accepted                 **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Can_17_McmCan_lSetControllerMode(
    const uint8 Controller,
    const Can_17_McmCan_ControllerState Transition)
{
  /*Local variable to store the return value of the function*/
  Std_ReturnType ReturnValue;

  /* calling core index */
  uint8 CoreIndex;

  /* Core specific controller index */
  uint8 ContIndx;

  /* core specifc configuration */
  const Can_17_McmCan_CoreConfigType *CoreConfigPtr;

  /* core specifc global variable structure */
  const Can_17_McmCan_CoreGlobalType *CoreGlobalPtr;

  /* Get core id which is executing currently */
  CoreIndex = CAN_17_MCMCAN_GETCOREINDEX;

  #if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON)
  /* Check if status is initilaized */
  ReturnValue = Can_17_McmCan_lDetUninitConfig(
                    CAN_17_MCMCAN_SID_SETCONTROLLERMODE,
                                           CoreIndex);
  /*check if the result is OK*/
  /* [cover parentID={D19066DE-59F4-490d-8E4C-98C447572E42}]
  Is the driver initialized?
  [/cover] */
  if (E_OK == ReturnValue)
  {

    /* Check the requested controllerId is Valid or not */
    ReturnValue = Can_17_McmCan_lDetParamController(
                                          CoreIndex,
                                          Controller,
                                          CAN_17_MCMCAN_SID_SETCONTROLLERMODE);
  }
  /*check if the result is OK*/
  /* [cover parentID={F5A9756A-8ADC-41e1-826D-A58FFE01D3D0}]
  Is the controller valid?
  [/cover] */
  if (E_OK == ReturnValue)
  {
    /* Check if requested state transition is valid */
    ReturnValue = Can_17_McmCan_lModeDetCheck(Can_17_McmCan_kGblConfigPtr->
               CanLogicalControllerIndexPtr[Controller].CanLCoreSpecContIndex,
               Transition,Can_17_McmCan_GblCoreState[CoreIndex]);
  }
  /*check if the result is OK*/
  /* [cover parentID={A0D434EB-75D2-4c22-B827-DC74A2CEBE37}]
  Is the mode valid?
  [/cover] */
  if (E_OK == ReturnValue)
  #endif /* #if(CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Local copy of the core specific configuration */
    CoreConfigPtr = Can_17_McmCan_kGblConfigPtr->CanCoreConfigPtr[CoreIndex];

    /* Local copy of the core specific global states */
    CoreGlobalPtr = Can_17_McmCan_GblCoreState[CoreIndex];

    /* Retrieve the controller index offset for the core */
    ContIndx = Can_17_McmCan_kGblConfigPtr->
               CanLogicalControllerIndexPtr[Controller].CanLCoreSpecContIndex;

    /* Perform state transition*/
    ReturnValue = Can_17_McmCan_lTriggerStateTransition(ContIndx, Transition,
                                                  CoreGlobalPtr, CoreConfigPtr);

    /* Check if the state transition request is successful */
    /* [cover parentID={C441C3E3-7F6E-4599-AF00-6F1C53135B59}]
    Is the state transition request sucessful?
    [/cover] */
    if (E_OK == ReturnValue)
    {
      /* Notify successful state transition to upper layer */
      /* [cover parentID={986F616F-A476-4b4f-B0FB-0F1A2F66EB14}]
      Notify the upper layer
      [/cover] */
      CanIf_ControllerModeIndication(Controller,
                                 CoreGlobalPtr->CanControllerModePtr[ContIndx]);
    }
  }
  /* return Api status */
  /* [cover parentID={C2FF6D23-0E1B-4cb2-8DB0-B93F21882352}]
  Retrun the status
  [/cover] */
  return ReturnValue;
}

/*******************************************************************************
** Traceability    : [cover parentID={B7A147D3-D308-4d22-9D34-F5E41D237DDA}]  **
**  Syntax       : static Std_ReturnType Can_17_McmCan_lTriggerStateTransition**
**                (                                                           **
**                  const uint8 Controller,                                   **
**                  const Can_17_McmCan_ControllerState Transition,           **
**                  const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,  **
**                  const Can_17_McmCan_CoreConfigype *const CoreConfigPtr    **
**                                                                            **
**  Description     : Performs software triggered state transitions of the    **
**                   CAN Controller State machine when wakeup support is      **
**                   Disabled                                                 **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID      : NA                                                      **
**                                                                            **
**  Sync/Async      : Synchronous                                             **
**                                                                            **
**  Reentrancy      : Non-Reentrant                                           **
**                                                                            **
**  Parameters (in) : Controller - Associated CAN Controller Configuration Id **
**                   Transition - Requested transition                        **
**                   CoreConfigPtr - Pointer to CAN driver configuration      **
**                                                                            **
**  Parameters(out): none                                                     **
**                                                                            **
**  Parameters (in-out) : CoreGlobalPtr - Pointer to global structure         **
**                                                                            **
**  Return value     : E_OK: Service request accepted, state transition       **
**                     successful                                             **
**                     E_NOT_OK: Service request not accepted                 **
*******************************************************************************/
static Std_ReturnType Can_17_McmCan_lTriggerStateTransition(
    const uint8 Controller,
    const Can_17_McmCan_ControllerState Transition,
    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr)
{

  /* return value for timeout check */
  Std_ReturnType ReturnValue = E_NOT_OK;

  /* Controller state machine transitions */
  switch (Transition)
  {
    /*STARTED*/
    /* [cover parentID={FC52AF5D-94C3-409c-AF08-DD9F7C089845}]
    AUTOSAR 4.2.2
    [/cover] */
    #if (MCAL_AR_VERSION == MCAL_AR_422)
    /* [cover parentID={17E8459B-E17B-4455-8238-8DF03F38DFD4}]
    Is the state request CAN_T_START?
    [/cover] */
    case CAN_T_START:
    #else
    /* [cover parentID={FB3C3BD9-6FD7-4e50-8A44-713AE87F1977}]
    AUTOSAR 4.4.0
    [/cover] */
    /* [cover parentID={3D66F9F0-6919-4a0b-AB32-D99219E910B0}]
    Is the state request CAN_CS_STARTED?
    [/cover] */
    case CAN_CS_STARTED:
    #endif
    {
      /*Trigger state transition to STARTED*/
      /* [cover parentID={EF522D39-D7B7-45ce-9E4C-6E3B13B2799A}]
      Invoke function to transition to STARTED
      [/cover] */
      ReturnValue = Can_17_McmCan_lSetModeStart(Controller, CoreGlobalPtr,
                                                CoreConfigPtr);
    }
    break;
    /*SLEEP*/
    /* [cover parentID={11058F37-0395-419d-891D-B17A5DFC0356}]
    AUTOSAR 4.2.2
    [/cover] */
    #if (MCAL_AR_VERSION == MCAL_AR_422)
    /* [cover parentID={3E44E492-6B04-400c-9EF6-AB411BA0196A}]
    Is the state request CAN_T_SLEEP?
    [/cover] */
    case CAN_T_SLEEP:
    /* [cover parentID={BE9DDDCA-D3CC-4a3c-970D-0252E952F997}]
    AUTOSAR 4.4.0
    [/cover] */
    #else
    /* [cover parentID={F069B08C-88D8-4732-822C-020D4591390D}]
    Is the state request CAN_CS_SLEEP?
    [/cover] */
    case CAN_CS_SLEEP:
    #endif
    {
      /* Set current mode to SLEEP */
      /* [cover parentID={59FC9AFF-E55F-43f9-9F7C-8CB80895877C}]
      Set the mode to SLEEP
      [/cover] */
      CoreGlobalPtr->CanControllerModePtr[Controller] = CAN_17_MCMCAN_SLEEP;
      ReturnValue = E_OK;
    }
    break;
    /*UNINIT*/
    /* [cover parentID={70BF72F2-90DF-4c05-A0D7-D03384FEB80E}]
    AUTOSAR 4.2.2
    [/cover] */
    #if (MCAL_AR_VERSION == MCAL_AR_422)
    /* [cover parentID={8DE7292E-BC51-4465-B19B-414F47AAF4E0}]
    Is the state request CAN_T_WAKEUP
    [/cover] */
    case CAN_T_WAKEUP:
    {

      /* [cover parentID={0592E166-6AD2-4004-8840-7DED26C83590}]
      Set current mode to STOPPED
      [/cover] */
      CoreGlobalPtr->CanControllerModePtr[Controller] = CAN_17_MCMCAN_STOPPED;
      ReturnValue = E_OK;
    }
    break;
    #endif
    /*STOPPED*/
    /*case CAN_T_STOP : in 4.2.2*/
    /*case CAN_CS_STOPPED: in AS 4.4.0*/
    default:
    {
      /*Trigger state transition to STOPPED*/
      /* [cover parentID={07FB951A-F779-4af0-8276-926EB0164AAA}]
      Default case: Invoke function to transition to STOPPED
      [/cover] */
      ReturnValue = Can_17_McmCan_lSetModeStop(Controller, CoreGlobalPtr,
                                                CoreConfigPtr);
    }
    break;
  }
  return ReturnValue;
}

/*******************************************************************************
** Traceability   : [cover parentID={4CD6F629-4DB7-4ea6-89D5-0DEEA0AC020F}]   **
**                                                                            **
**  Syntax          :static Std_ReturnType Can_17_McmCan_lSetModeStart        **
**                   (const uint8 Controller,                                 **
**                    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,**
**                    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr)**
**                                                                            **
**  Description      : The function changes the CAN controller state to       **
**                     STARTED from a valid controller state.                 **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Non-Reentrant                                          **
**                                                                            **
**  Parameters (in)  : Controller - Associated CAN Controller Configuration Id**
**                     CoreConfigPtr - Pointer to CAN driver configuration    **
**                     CoreGlobalPtr - Pointer to global structure            **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Parameters (in-out) : none                                                **
**                                                                            **
**  Return value     : E_OK: Service request accepted, state transition       **
**                     to STARTED successful                                  **
**                     E_NOT_OK: Service request not accepted                 **
*******************************************************************************/
static Std_ReturnType Can_17_McmCan_lSetModeStart(const uint8 Controller,
    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr)
{
  /* Pointer to CAN node register type */
  volatile Ifx_CAN_N *NodeRegAddressPtr;

  /* register address to be checked for timeout */
  const volatile uint32 *RegAddressPtr;

  /* return value for timeout check */
  Std_ReturnType ReturnValue;

  /* Get Node Register address */
  NodeRegAddressPtr =
      CoreConfigPtr->CanControllerConfigPtr[Controller].CanNodeAddressPtr;

  /* Clear receive message object to avoid older notification */
  Can_17_McmCan_lClearReceivedMsg(Controller, CoreConfigPtr);

  /* Set CAN controller with normal operation mode */
  /* [cover parentID={801EB399-9A83-44aa-9850-F093143FC98C}]
  Set CAN controller INIT bit with normal operation mode
  [/cover] */
  NodeRegAddressPtr->CCCR.B.INIT = CAN_17_MCMCAN_BIT_RESET_VAL;

  /* Set with Register Address */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: Typecasting to uint32 is
    required in order to maintain a common interface to check bits
    that are getting updated by hardware */
  RegAddressPtr = (const volatile uint32 *)(&(NodeRegAddressPtr->CCCR.U));

  /* Check the Hw status update */
  /* [cover parentID={5017BBBB-45DE-45d2-B8D6-22371A1991AC}]
  Invoke the function to check if the bit is set
  [/cover] */
  ReturnValue = Can_17_McmCan_lTimeOut((const volatile uint32 *)RegAddressPtr,
                                       (uint32)CAN_17_MCMCAN_NODE_INIT_MODE,
                                     CAN_17_MCMCAN_NOT_EQUAL);
  /*Check the Hw status update*/
  /* [cover parentID={96BD2DD2-88BC-4957-A8EF-2D29C2BE9FE3}]
  Has the timeout occurred?
  [/cover] */
  if (E_OK == ReturnValue)
  {
    /* Clear any registered interrupt */
    /* [cover parentID={3042EAFD-EDC7-4d31-A87B-8C65A96E6584}]
    Clear any registered interrupt by clearing IR register
    [/cover] */
    NodeRegAddressPtr->IR.U = NodeRegAddressPtr->IR.U;

    /* Set with Register Address */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: Typecasting to uint32 is
    required in order to maintain a common interface to check bits
    that are getting updated by hardware */
    RegAddressPtr = (const volatile uint32 *)(&(NodeRegAddressPtr->PSR.U));

    /* Check the Hw status update */
    /* [cover parentID={6EB81C96-2234-4298-82BD-E2E0FC61D98E}]
    Invoke function to check whether the bit is SET or not
    [/cover] */
    ReturnValue = Can_17_McmCan_lTimeOut((const volatile uint32 *)RegAddressPtr,
                                         (uint32)CAN_17_MCMCAN_NODE_PSR_MODE,
                                        CAN_17_MCMCAN_NAND);
    /*Check if timeout*/
    /* [cover parentID={6BEF49E0-C4D4-4b7d-803C-17CB52CB9888}]
    Has timeout occured?
    [/cover] */
    if (E_OK == ReturnValue)
    {
      /*Check for ICOM feature is enabled*/
      #if (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON)
      /*Check if ICOM is enabled*/
      /* [cover parentID={0B75D013-70DB-4bb8-ADF9-A06B134FB9DD}]
      Is ICOM enabled?
      [/cover] */
      if (0U != CoreGlobalPtr->CanActiveIcomCfgIdPtr[Controller])
      {
        /*Deactivate ICOM*/
        /* [cover parentID={169761E2-A0AC-49d2-94A4-844881770214}]
        Deactivate ICOM
        [/cover] */
        Can_17_McmCan_lDeactivateIcom(Controller, CoreGlobalPtr, CoreConfigPtr);
      }
      #endif /* #if (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON) */

      /* [cover parentID={41BAE71C-28BA-48fc-9116-5ECC37644720}]
      Are interrupts already enabled?
      [/cover] */
      if (0U == CoreGlobalPtr->CanDisableIntrpCountPtr[Controller])
      {
        NodeRegAddressPtr->IE.U = CoreConfigPtr->
                      CanControllerConfigPtr[Controller].CanEnableInterruptMask;
      }

      /* Clear the Pending Tx and rebuild Txmask */
      Can_17_McmCan_lCancelPendingTx(Controller,
                                   CoreGlobalPtr, CoreConfigPtr);

      /* Set current mode to STARTED */
      CoreGlobalPtr->CanControllerModePtr[Controller] = CAN_17_MCMCAN_STARTED;
    }
    else
    {
       /*Do nothing*/
    }
  }
  /* [cover parentID={BEC739F7-61A0-4cd8-A5E3-23AE54CCDF43}]
  Return the result
  [/cover] */
  return ReturnValue;
}

/*******************************************************************************
** Traceability   : [cover parentID={0491150C-6FB7-417d-A884-F9BC77093929}]   **
**  Syntax          :static Std_ReturnType Can_17_McmCan_lSetModeStop         **
**                   (const uint8 Controller,                                 **
**                    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,**
**                    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr)**
**                                                                            **
**  Description      :The function performs software triggered state          **
**                    transitions of the CAN Controller State machine         **
**                    to STOPPED                                              **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Non-Reentrant                                          **
**                                                                            **
**  Parameters (in)  : Controller - Associated CAN Controller Configuration Id**
**                     CoreConfigPtr - Pointer to CAN driver configuration    **
**                     CoreGlobalPtr - Pointer to global structure            **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Parameters (in-out) :                                                     **
**                                                                            **
**  Return value     : E_OK: Service request accepted, state transition       **
**                     to STOPPED successful                                  **
**                     E_NOT_OK: Service request not accepted                 **
*******************************************************************************/
 static Std_ReturnType Can_17_McmCan_lSetModeStop(const uint8 Controller,
    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr)
{

  /* Pointer to CAN node register type */
  volatile Ifx_CAN_N *NodeRegAddressPtr;

  /* register address to be checked for timeout */
  const volatile uint32 *RegAddressPtr;

  /* return value for timeout check */
  Std_ReturnType ReturnValue;

  /* Get Node Register address */
  NodeRegAddressPtr = CoreConfigPtr->
                          CanControllerConfigPtr[Controller].CanNodeAddressPtr;

  /* Request for cancel pending request */
  /* [cover parentID={27AFFF47-5D33-47c8-9DA7-0C86A5EF0668}]
  Cancel the pending transmit request
  [/cover] */
  Can_17_McmCan_lCancelPendingTx(Controller, CoreGlobalPtr, CoreConfigPtr);

  /* Set CAN controller with INIT mode */
  /* [cover parentID={DC1D3EFC-CE7F-46da-9A23-CC9EA0FB7248}]
  Set the CAN controller INIT mode
  [/cover] */
  NodeRegAddressPtr->CCCR.B.INIT = IFX_CAN_N_CCCR_INIT_MSK;

  /* Set with Register Address */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: Typecasting to uint32 is
    required in order to maintain a common interface to check bits
    that are getting updated by hardware */
  RegAddressPtr = (const volatile uint32 *)(&(NodeRegAddressPtr->CCCR.U));

  /* Wait for the INIT bit SET */
  /* [cover parentID={5D6F1D04-D89E-4430-97DB-A799787CADBE}]
  Invoke the function to check if the INIT bit is set
  [/cover] */
  ReturnValue = Can_17_McmCan_lTimeOut((const volatile uint32 *)RegAddressPtr,
                                        CAN_17_MCMCAN_CCCR_INIT_SET_MASK,
                                        CAN_17_MCMCAN_EQUAL);

  /* Hw state changes successfully then set SW flag */
  /* [cover parentID={1BB754DE-3357-4c91-B1F2-CEDE6FDE5E1C}]
  Has timeout occured?
  [/cover] */
  if (E_OK == ReturnValue)
  {
    /* Set Configuration Change Enable bit */
    NodeRegAddressPtr->CCCR.B.CCE = IFX_CAN_N_CCCR_CCE_MSK;

    /* Set with Register Address */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: Typecasting to uint32 is
    required in order to maintain a common interface to check bits
    that are getting updated by hardware */
    RegAddressPtr = (const volatile uint32 *)(&(NodeRegAddressPtr->CCCR.U));

    /* Wait for CCE bit to SET */
    /* [cover parentID={2C697330-FCFB-4ab3-BAE4-D5128D321B8D}]
    Invoke the function to check if the CCE bit is SET
    [/cover] */
    ReturnValue = Can_17_McmCan_lTimeOut((const volatile uint32 *)RegAddressPtr,
                                        CAN_17_MCMCAN_CCCR_CCE_SET_MASK,
                                        CAN_17_MCMCAN_EQUAL);

    /*ICOM is activated for the controller*/
    /* [cover parentID={6E7C9356-08B0-4908-A018-53B106CBE17E}]
    Has timeout occured?
    [/cover] */
    if (E_OK == ReturnValue)
    {
      #if (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON)
      /* [cover parentID={4EFDD549-849F-467b-90B8-E3F51E648CCA}]
      Is the activate ICOM configuration NULL?
      [/cover] */
      if (0U != CoreGlobalPtr->CanActiveIcomCfgIdPtr[Controller])
      {
        /*Deactivate ICOM*/
        /* [cover parentID={25F7BF3E-7BFE-4165-9F60-D2DC44C7497B}]
        Deactivate ICOM
        [/cover] */
        Can_17_McmCan_lDeactivateIcom(Controller, CoreGlobalPtr, CoreConfigPtr);
      }
      #endif /* #if (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON) */

      /* [cover parentID={A2173B32-7110-4323-9D31-0D8FF84D90EC}]
      Are the interrupts disabled?
      [/cover] */
      if (0U == CoreGlobalPtr->CanDisableIntrpCountPtr[Controller])
      {
        NodeRegAddressPtr->IE.U = CAN_17_MCMCAN_RESET_VAL;
      }

      /* [cover parentID={AD019B57-7F85-4dcc-A0E5-046E0C557650}]
      Set the controller mode to STOPPED
      [/cover] */
      CoreGlobalPtr->CanControllerModePtr[Controller] = CAN_17_MCMCAN_STOPPED;
    }
  }
  /* [cover parentID={E6D583F4-4D5D-49b0-A30A-856E25DF1D5C}]
  Return the value
  [/cover] */
  return ReturnValue;
}

#if (CAN_17_MCMCAN_TRIG_TRANSMIT == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={FC5DA7C1-F783-49e2-A1CC-FCAC1753A56F}]   **
**                                                                            **
**  Syntax        : static Can_17_McmCan_ReturnValueType                      **
**                                        Can_17_McmCan_lUpdatePduInfo        **
**                  (                                                         **
**                     const Can_HwHandleType HthIndex,                       **
**                     Can_PduType *TempPduInfoPtr,                           **
**                     const Can_PduType *const PduInfoPtr,                   **
**                     const Can_17_McmCan_CoreConfigType *const CoreConfigPtr**
**                   )                                                        **
**                                                                            **
**  Description    : Programs Message Object for transmission                 **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant for different controllers.                   **
**                     Non reentrant for the same controller.                 **
**                                                                            **
**  Parameters (in)  : HthIndex - HTH index in the configuration structure    **
**                    PduInfoPtr - Pointer to SDU user memory, DLC and        **
**                              Identifier                                    **
**                    CoreConfigPtr - Pointer to CAN driver configuration     **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Parameters (in-out) : CoreGlobalPtr - Pointer to global structure         **
**                                                                            **
**  Return value     : CAN_17_MCMCAN_OK - Write command has been accepted     **
**                   CAN_17_MCMCAN_NOT_OK - Development error occurred        **
**                                                                            **
*******************************************************************************/
static Can_17_McmCan_ReturnValueType Can_17_McmCan_lUpdatePduInfo(
    const Can_HwHandleType HthIndex,
    Can_PduType *const TempPduInfo, const Can_PduType *const PduInfoPtr,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr)
{
  /* PduInfoType structure variable */
  PduInfoType PduInfoTrigger;

  /*Temporary Pdu Info pointer*/
  PduInfoType *WritePduInfoPtr;

  /*Pointer to store TX Hw Object configuration*/
  const Can_17_McmCan_TxHwObjectConfigType *TxObjPtr;

  /*return value to store the trigger status*/
  Std_ReturnType TriggerStatus = E_NOT_OK;

  /*Variable to store the return value of the function*/
  Can_17_McmCan_ReturnValueType ReturnValue = CAN_17_MCMCAN_NOT_OK;

  /* Set with TX object configuration start index */
  TxObjPtr = CoreConfigPtr->CanTxHwObjectConfigPtr;

  /*MISRA2012_RULE_1_3_JUSTIFICATION:Address of auto variable is used
  only to read the values. The address is not used to perform any
  pointer arithmetic. hence no side effect has been seen.*/
  WritePduInfoPtr = &PduInfoTrigger;

  /* Check Trigger Transmit is Enabled */
  /* [cover parentID={04AC4257-F643-43e8-99D3-EBC156D07C6E}]
  Check trigger transmit is enabled for the Hth passed
  [/cover] */
  if (TRUE == TxObjPtr[HthIndex].CanTrigTxStatus)
  {

    /*Store Data pointer and Data length*/
    WritePduInfoPtr->SduDataPtr = PduInfoPtr->sdu;

    /*Store Data length*/
    WritePduInfoPtr->SduLength = (uint8)(PduInfoPtr->length);

    /* CanIf_TriggerTransmit() to acquire the PDUs data */
    /* [cover parentID={F0374D8B-60E3-4ab4-8FE3-7603DB0449AE}]
    Call CanIf_TriggerTransmit() to acquire the PDUs data
    [/cover] */
    TriggerStatus = CanIf_TriggerTransmit(PduInfoPtr->swPduHandle,
                                                    WritePduInfoPtr);

    /*Check Trigger Status*/
    /* [cover parentID={FD2C996D-7554-4999-B056-773E081E56BC}]
    check trigger status
    [/cover] */
    if (E_OK == TriggerStatus)
    {
      /*Store the updated Data pointer and Data length*/
      TempPduInfo->sdu = WritePduInfoPtr->SduDataPtr;

      /*Store the updated Data length*/
      TempPduInfo->length = (uint8)(WritePduInfoPtr->SduLength);

      ReturnValue = CAN_17_MCMCAN_OK;
    }
    else
    {
      #if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      /* [cover parentID={A27902BD-64B0-4990-8BA1-DD6CE6F07202}]
      Det error CAN_17_MCMCAN_E_PARAM_POINTER
      [/cover] */
      (void)Det_ReportError(CAN_17_MCMCAN_MODULE_ID, CAN_17_MCMCAN_INSTANCE_ID,
                      CAN_17_MCMCAN_SID_WRITE, CAN_17_MCMCAN_E_PARAM_POINTER);

      #endif
    }
  }
  else
  {
    /*Store the Data pointer*/
    TempPduInfo->sdu = PduInfoPtr->sdu;

    /*Store the updated Data length*/
    TempPduInfo->length = PduInfoPtr->length;

    ReturnValue = CAN_17_MCMCAN_OK;
  }
  return ReturnValue;
}
#endif /* #if (CAN_17_MCMCAN_TRIG_TRANSMIT == STD_ON) */

#if (CAN_17_MCMCAN_MULTIPLEXED_TRANSMISSION == STD_ON)
/*******************************************************************************
** Traceability   :  [cover parentID={D0A7E05E-23E0-4e41-98D8-FE87B3AB14CC}]  **
**                                                                            **
**  Syntax           : static uint8 Can_17_McmCan_lCheckQueueMask             **
**                    (const uint8 ControllerId,                              **
**                     const Can_17_McmCan_CoreConfigType *const CoreConfigPtr,*
**                     const uint32 *const QueueSlotMaskPtr)                  **
**                                                                            **
**                                                                            **
** Description    : The function checks and returns the slot available in     **
**                  transmit Queue each SET bit represents a free slot        **
**                  available for messages to be written, bit clear indicates **
**                  slot not available.                                       **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant                                              **
**                                                                            **
**  Parameters (in)  : ControllerId - Controller id for which Queue slot check**
**                     is made                                                **
**                     CoreConfigPtr - Can config pointer                     **
**                     QueueSlotMaskPtr - pointer to Queue mask updated       **
**                     for controller                                         **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : 0xFF - If no slot is found in Tx Queue                 **
**                   : 0 to Queue size - Next available free slot             **
**                                                                            **
*******************************************************************************/
static uint8 Can_17_McmCan_lCheckQueueMask(const uint8 ControllerId,
                        const Can_17_McmCan_CoreConfigType *const CoreConfigPtr,
                                           const uint32 *const QueueSlotMaskPtr)
{
  /*Variable to traverse through the slot indices*/
  uint32 TxIndex;

  /*TX slot value*/
  uint8 SlotValue = CAN_17_MCMCAN_TXSLOT_VAL;

  /*Mask to check if the TX slot is available*/
  uint32 SlotMask;

  /* MISRA2012_RULE_19_2_JUSTIFICATION:
  Copy of register content is taken to stack,
  used to access bits with-in the stack variable. */
  Ifx_CAN_N_TX_BC TxTempbuffReg;

  volatile const Ifx_CAN_N *NodeRegAddressPtr;

  NodeRegAddressPtr = CoreConfigPtr->
                         CanControllerConfigPtr[ControllerId].CanNodeAddressPtr;

  TxTempbuffReg.U = NodeRegAddressPtr->TX.BC.U;

  /* Check for slot in Queue */
  /* [cover parentID={538FB8CD-D833-43a9-A1A6-292667CF4B98}]
  Loop till the end of Queue
  [/cover] */
  for (TxIndex = (uint32)(TxTempbuffReg.B.NDTB);
       TxIndex < ((uint32)((uint32)TxTempbuffReg.B.NDTB +
       (uint32)TxTempbuffReg.B.TFQS));
       TxIndex++)
  {
    SlotMask = ((uint32)1U << TxIndex);

    /* Check if Tx Queue slot available*/
    /* [cover parentID={E1BE3A34-12AF-42a2-A0ED-FC72BDC0EE13}]
    Check for free slot among Tx Queue elements
    [/cover] */
    if ((*QueueSlotMaskPtr & SlotMask) == SlotMask)
    {
      SlotValue = (uint8)TxIndex;
      break;
    }
  }

  return SlotValue;
}
#endif

#if (CAN_17_MCMCAN_FD_ENABLE == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={4580DA3D-F859-4f87-BA15-567BBCEC96EA}]   **
**                                                                            **
**  Syntax          : static uint8 Can_17_McmCan_lWriteFDFillTransmitBuffer   **
**                   (                                                        **
**                     const Can_PduType *const PduInfoPtr,                   **
**                     const Can_PduType *TempPduInfoPtr,                     **
**                     const volatile Ifx_CAN_N *NodeRegAddressPtr,           **
**                     const uint32 TxWriteStartAddr)                         **
**                                                                            **
**  Description    : Programs Message Object for transmission if FD is enabled**
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant for different controllers.                   **
**                     Non reentrant for the same controller.                 **
**                                                                            **
**  Parameters (in)  : TempPduInfoPtr - Pointer to PDU info structure         **
**                     PduInfoPtr - Pointer to SDU user memory, DLC and       **
**                              Identifier                                    **
**                     NodeRegAddressPtr - Pointer to CAN controller address  **
**                     TxWriteStartAddr - Start address of TX write buffer    **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Parameters (in-out) : none                                                **
**                                                                            **
**  Return value     : uint8: DLC value                                       **
**                                                                            **
*******************************************************************************/

static uint8 Can_17_McmCan_lWriteFDFillTransmitBuffer(
                                           const Can_PduType *const PduInfoPtr,
                                             const Can_PduType *TempPduInfoPtr,
                              const volatile Ifx_CAN_N *const NodeRegAddressPtr,
                                   volatile Ifx_CAN_TXMSG *const TxMsgBufferPtr)
{

  /*Variable to store the DLC*/
  uint8 TempDLC;

  /* Check FD frame need to be transmit */
  /* [cover parentID={86874D89-EB8A-42bf-827F-15B3F819B27F}]
Check FD frame needs to be transmit
[/cover] */
  if (CAN_17_MCMCAN_ID_FD_ENABLE_SET == (PduInfoPtr->id &
                                         CAN_17_MCMCAN_ID_FD_ENABLE_SET))
  {
    /* Set Tx message with FD */
    TxMsgBufferPtr->T1.B.FDF = 1U;
  }
  else
  {
    /* Set Tx message with Normal */
    TxMsgBufferPtr->T1.B.FDF = 0U;
  }
    /* [cover parentID={5C503675-DA8C-48b4-8858-01C018B60B6D}]
If CAN FD frames transmitted with bit rate switching
[/cover] */
  if (CAN_17_MCMCAN_BIT_SET_VAL == NodeRegAddressPtr->CCCR.B.BRSE)
  {
    /* Enable BRS */
    TxMsgBufferPtr->T1.B.BRS = 1U;
  }
  else
  {
    /* Disable BRS */
    TxMsgBufferPtr->T1.B.BRS = 0U;
  }
  /* Check DLC length and calculate the Hw support value if DLC > 24 */
  /* [cover parentID={4C0B3EDE-30BC-484a-B545-7C63D7E6480F}]
Check DLC is greater than maximum FD number of bytes
[/cover] */
  if (TempPduInfoPtr->length > CAN_17_MCMCAN_PDULENGTH_CHKVAL24)
  {
    /* Set DLC length with Hw Supported value */
    TempDLC = (((TempPduInfoPtr->length + CAN_17_MCMCAN_PDULENGTH_CHKVAL15) >>
                CAN_17_MCMCAN_PDULENGTH_CHKVAL4) +
                CAN_17_MCMCAN_PDULENGTH_CHKVAL11);
  }
  /* Check DLC length and calculate the Hw support value if DLC > 8 */
  /* [cover parentID={06F71A1F-8ED9-4b46-A6A5-7FD63198F8BD}]
Check DLC is greater than normal message
[/cover] */

  else if (TempPduInfoPtr->length > CAN_17_MCMCAN_PDULENGTH_CHKVAL8)
  {
    /* Set DLC length with Hw Supported value */
    TempDLC = (((TempPduInfoPtr->length + CAN_17_MCMCAN_PDULENGTH_CHKVAL3) >>
                CAN_17_MCMCAN_PDULENGTH_CHKVAL2) +
                CAN_17_MCMCAN_PDULENGTH_CHKVAL6);
  }
  else
  {
        /* Set DLC with requested value */
      TempDLC = TempPduInfoPtr->length;
  }
  return TempDLC;
}

#endif

/*******************************************************************************
** Traceability   : [cover parentID={24A1ABDD-424C-4af5-8711-FB56D2461FCF}]   **
**                  [cover parentID={6E1CBB09-0089-421f-AFD2-C08A9E6EAEB6}]   **
**                                                                            **
**  Syntax           : static Can_ReturnType Can_17_McmCan_lWriteMsgObj       **
**                    (                                                       **
**                       const Can_HwHandleType HthIndex,                     **
**                       const Can_PduType *const PduInfoPtr,                 **
**                       Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,   **
**                       const Can_17_McmCan_CoreConfigType *const ConfigPtr  **
**                     )                                                      **
**                                                                            **
**  Description    : Programs Message Object for transmission                 **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant for different controllers.                   **
**                     Non reentrant for the same controller.                 **
**                                                                            **
**  Parameters (in)  : HthIndex - HTH index in the configuration structure    **
**                    PduInfoPtr - Pointer to SDU user memory, DLC and        **
**                              Identifier                                    **
**                     CoreConfigPtr - Pointer to CAN driver configuration    **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Parameters (in-out) : CoreGlobalPtr - Pointer to global structure         **
**                                                                            **
**  Return value     : CAN_17_MCMCAN_OK - Write command has been accepted     **
**                   CAN_17_MCMCAN_BUSY - No message object available or      **
**                              pre-emptive call of Can_17_McmCan_Write that  **
**                              can't be implemented re-entrant               **
*******************************************************************************/

static Can_17_McmCan_ReturnValueType Can_17_McmCan_lWriteMsgObj(
    const Can_HwHandleType HthIndex,
    const Can_PduType *const PduInfoPtr,
    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr)
{
  /*Can controller node address pointer*/
  volatile Ifx_CAN_N *NodeRegAddressPtr;

  /*TX message buffer pointer*/
  volatile Ifx_CAN_TXMSG *TxMsgBufferPtr;

  /*Pointer to TX HW object*/
  const Can_17_McmCan_TxHwObjectConfigType *TxObjPtr;

  /*Pointer to message RAM configuration*/
  const Can_17_McmCan_ControllerMsgRAMConfigType *MsgRamCfgPtr;

  /*Pointer to PDU info*/
  Can_PduType *TempPduInfo;

  /*Variable to store the intermediate PDU info values*/
  Can_PduType PduTemp;

  /*TX write start address*/
  uint32 TxWriteStartAddr;

  /*Buffer index*/
  uint32 BuffIndex;

  /*Buffer element index to traverse through the TX elements*/
  uint8 BuffElementIndex = 0U;

  /*Return value of the function*/
  Can_17_McmCan_ReturnValueType RetVal;

  /*DLC value of the TX message*/
  uint8 TxMsgDLC;

  /*Data byte position*/
  uint8 DataBytePos;

  /*CAN controller ID*/
  uint8 ControllerId;

  /*SW object index for buffer management*/
  uint16 SwObjIndx;

  #if (CAN_17_MCMCAN_MULTIPLEXED_TRANSMISSION == STD_ON)
  Can_17_McmCan_TxBufferType TxBuffType;
  #endif

  /* Set Message RAM configuration pointer with configuration address */
  MsgRamCfgPtr = CoreConfigPtr->CanControllerMsgRAMMapConfigPtr;

  /* Set with TX object configuration start index */
  TxObjPtr = CoreConfigPtr->CanTxHwObjectConfigPtr;

  /*Multiplexed transimssion is enabled*/
  /* [cover parentID={083BC331-9160-4caf-8113-27A6FC5E1098}]
  Multiplexed transimssion is enabled
  [/cover] */
  #if (CAN_17_MCMCAN_MULTIPLEXED_TRANSMISSION == STD_ON)

  /* Copy the buffer Type of requested HTH */
  TxBuffType = TxObjPtr[HthIndex].CanTxBufferType;

  #endif

  /* Set with the associated controller of requested HTH */
  ControllerId = Can_17_McmCan_kGblConfigPtr->
                 CanLogicalControllerIndexPtr[TxObjPtr[HthIndex].HwControllerId]
                 .CanLCoreSpecContIndex;

  /* Get Node Register address */
  NodeRegAddressPtr = CoreConfigPtr->
                      CanControllerConfigPtr[ControllerId].CanNodeAddressPtr;

  /* Set with Message RAM start address of Tx buffer */
  TxWriteStartAddr = MsgRamCfgPtr[ControllerId].
                     CanControllerMsgRAMMap[CAN_17_MCMCAN_TBSA];
  /* Set value with OK */
  RetVal = CAN_17_MCMCAN_OK;

  /* Copy the buffer Index for Mask */
  BuffIndex = (uint32)(CAN_17_MCMCAN_TX_BUFF_MASK <<
                      (TxObjPtr[HthIndex].CanTxBuffIndx));

  /* Enter Critical Section */
  /* [cover parentID={EC87F7B9-D77C-4a3f-9F3E-D94C2E054494}]
  Enter Critical Section call
  [/cover] */
  SchM_Enter_Can_17_McmCan_CanWrMO();

  /* [cover parentID={4B7CC083-04A5-46ab-AE13-7E997C720E65}]
  MULTIPLEXED TRANSMISSION is enabled
  [/cover] */
  #if (CAN_17_MCMCAN_MULTIPLEXED_TRANSMISSION == STD_OFF)
  /* check if buffer is free or not */
  /* [cover parentID={58143A88-35A7-4220-95E2-5634FFA8CA5D}]
  Check buffer is free
  [/cover] */
  if ((CoreGlobalPtr->CanTxMaskPtr[ControllerId] & BuffIndex) != BuffIndex)
  {
    /*Return value as BUSY*/
    /* [cover parentID={9A15F3CC-7C7F-45ba-BFF6-175F4FDC04C5}]
    Return CAN_17_MCMCAN_BUSY
    [/cover] */
    RetVal = CAN_17_MCMCAN_BUSY;

    BuffElementIndex = 0U;
  }
  else
  {
    /* Copy the exact buffer element offset */
    BuffElementIndex = TxObjPtr[HthIndex].CanTxBuffIndx;
  }
  #else
  /* Check Tx buffer Type for Start address calculation and buffer status */
  /* Dedicated buffer type */
  /* [cover parentID={173F25BC-AF6C-48b3-B55B-05EEAE85E097}]
  Check transmit buffer type is dedicated
  [/cover] */
  if (CAN_17_MCMCAN_TX_DED_BUFFER == TxBuffType)
  {
    /*Is the buffer free*/
    /* [cover parentID={D4AE8421-4CF4-4d62-9E9F-7A1DD412975E}]
    Check buffer is free
    [/cover] */
    if ((CoreGlobalPtr->CanTxMaskPtr[ControllerId] & BuffIndex) != BuffIndex)
    {
      /* [cover parentID={6CFB6E77-7FEB-49f7-AB24-C25B021E7CC5}]
      Return CAN_17_MCMCAN_BUSY
      [/cover] */
      RetVal = CAN_17_MCMCAN_BUSY;

      BuffElementIndex = 0U;
    }
    else
    {
      /* Copy the exact buffer element offset */
      BuffElementIndex = TxObjPtr[HthIndex].CanTxBuffIndx;
    }
  }
  else
  {
    /* Check TXQUEUE is Free or not */

     /* [cover parentID={D2536F08-9EC3-43be-B165-98C3D0AB16ED}]
     Check if transmit Queue is free
     [/cover] */
    if (CAN_17_MCMCAN_BIT_SET_VAL == NodeRegAddressPtr->TX.FQS.B.TFQF)
    {
      /*Return BUSY*/
            /*Set return value as Busy*/
      /* [cover parentID={01A8A051-9F22-4523-B752-240B11476297}]
      Return CAN_17_MCMCAN_BUSY
      [/cover] */
      RetVal = CAN_17_MCMCAN_BUSY;

      BuffElementIndex = 0U;
    }
    else
    {
      /* Check for next free slot in Tx Queue */
      BuffElementIndex = Can_17_McmCan_lCheckQueueMask(ControllerId,
                                                                 CoreConfigPtr,
                                    &CoreGlobalPtr->CanTxMaskPtr[ControllerId]);

      /*Check for available slot*/
      /* [cover parentID={B9C5F877-61F3-4595-8A1F-B9AC3BBF9347}]
      Check if no free slot is available
      [/cover] */
      if (BuffElementIndex == CAN_17_MCMCAN_TXSLOT_VAL)
      {
        RetVal = CAN_17_MCMCAN_BUSY;
      }
      else
      {
        /*Block Tx slot*/
        /* [cover parentID={1716BABC-B97B-415f-B1C2-DB0AEBA80690}]
        Copy the buffer Index for Mask
        [/cover] */
        BuffIndex = (uint32)(CAN_17_MCMCAN_TX_BUFF_MASK << BuffElementIndex);
      }
    }
  }
  #endif /* #if (CAN_17_MCMCAN_MULTIPLEXED_TRANSMISSION == STD_OFF) */

  /* [cover parentID={AD06B201-F7D9-4675-9F13-6D85FAFCA119}]
  Public ICOM is enabled
  [/cover] */
  #if (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON)
  /* [cover parentID={1D8F3616-5772-4d56-8ED1-88E3DD52331C}]
  Is the return status is CAN_17_MCMCAN_OK and controller is
  enabled for pretended networking?
  [/cover] */
  if ((RetVal == CAN_17_MCMCAN_OK) &&
      (TRUE == CoreGlobalPtr->CanIcomBlockWriteCallsPtr[ControllerId]))
  {
    /* [cover parentID={65F98883-86B6-4258-A828-57110E43C470}]
    Return CAN_17_MCMCAN_BUSY
   [/cover] */
    RetVal = CAN_17_MCMCAN_BUSY;
  }
  #endif

  /*MISRA2012_RULE_1_3_JUSTIFICATION:Address of auto variable is used
  only to read the values. The address is not used to perform any
  pointer arithmetic. hence no side effect has been seen.*/
  TempPduInfo = &PduTemp;
  #if (CAN_17_MCMCAN_TRIG_TRANSMIT == STD_ON)
  /*Check if trigger transmit is enabled*/
  /* [cover parentID={0081EEE0-5D89-414f-9D7B-0799A660541C}]
  Check if trigger transmit is enabled?
  [/cover] */
   /* [cover parentID={1BAFBAB1-8880-4308-B735-36B46C11103E}]
   Check if return status is CAN_17_MCMCAN_OK
   [/cover] */
  if (RetVal == CAN_17_MCMCAN_OK)
  {
    /* [cover parentID={2048703A-0E1A-4692-8533-D2CD73C8672E}]
    Call for trigger transmit status operations
    [/cover] */
    RetVal = Can_17_McmCan_lUpdatePduInfo(HthIndex, TempPduInfo,
                                           PduInfoPtr, CoreConfigPtr);
  }
  #else
    /*Store the Data pointer and Data length*/
    TempPduInfo->sdu = PduInfoPtr->sdu;
    TempPduInfo->length = PduInfoPtr->length;
  #endif /* #if (CAN_17_MCMCAN_TRIG_TRANSMIT == STD_ON) */
  if (CAN_17_MCMCAN_OK == RetVal)
  {
    /* Lock Tx Queue slot - Only if all checks are passed */
    CoreGlobalPtr->CanTxMaskPtr[ControllerId] &= ~((uint32)1U
                                                << BuffElementIndex);

    #if (CAN_17_MCMCAN_FD_ENABLE == STD_ON)
    /* [cover parentID={A66B9A3D-FE07-43dc-A9DD-DC2BF806916B}]
     Check FD is supported for this controller
    [/cover] */
    if (TRUE ==
        CoreConfigPtr->CanControllerConfigPtr[ControllerId].CanFDSupport)
    {

      /* Set buffer size with FD support */
      TxWriteStartAddr = (TxWriteStartAddr +
                                ((uint32)CAN_17_MCMCAN_MSG_RAM_ELEMENT_SIZE_FD *
                                              BuffElementIndex));
    }
    else
    #endif

    {
      /* Set buffer size with normal buffer */
      TxWriteStartAddr = TxWriteStartAddr +
                         (CAN_17_MCMCAN_MSG_RAM_ELEMENT_SIZE_NFD *
                                         (uint32)BuffElementIndex);
    }
    /* Set with Transmit message buffer0 pointer */
    /* MISRA2012_RULE_11_6_JUSTIFICATION: The pointer cast is used to
    cast the address to the Tx buffer elements structure type
    for accessing RAM area */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: Memory address is generated as a
    numerical value, it is accessed as a pointer to the RAM address.
    Hence an explicit typecast from numerical to pointer. */
    /* Set with Transmit message buffer0 pointer */
    TxMsgBufferPtr = (volatile Ifx_CAN_TXMSG *)TxWriteStartAddr;

    /* Reset the T0 Msg buffer being accessed */
    TxMsgBufferPtr->T0.U = 0U;

    /* Reset the RTR bit to avoid transmit messages triggered by
    remote transmission requests */
    TxMsgBufferPtr->T0.B.RTR = 0U;

    /* [cover parentID={55A345E3-2E98-4e91-89C7-E3037EDD0F70}]
    Check requested Id is extended
    [/cover] */
    if (CAN_17_MCMCAN_EXTENDED_ID_SET ==
        (PduInfoPtr->id & CAN_17_MCMCAN_EXTENDED_ID_SET))
    {
      /* Store extended Id and set XTD bit */
      TxMsgBufferPtr->T0.B.XTD = 1U;
      TxMsgBufferPtr->T0.B.ID =
                            ((PduInfoPtr->id) & CAN_17_MCMCAN_EXTENDED_ID_MASK);
    }
        /* [cover parentID={F5C8C104-A834-4ec7-AE45-811E40AC6921}]
    Set Id Type as Standard
    [/cover] */
    else
    {
      /* shift Standard Identifier to position 28..18 */
      TxMsgBufferPtr->T0.B.ID = (PduInfoPtr->id &
                                         CAN_17_MCMCAN_STANDARD_ID_MASK)
                                          << CAN_17_MCMCAN_SHIFT_MSGRAM_RT_MASK;

      /* Set Id Type as Standard */
      TxMsgBufferPtr->T0.B.XTD = 0U;
    }

    TxMsgBufferPtr->T1.U = (uint32)0U;

    #if (CAN_17_MCMCAN_FD_ENABLE == STD_ON)
    TxMsgDLC = Can_17_McmCan_lWriteFDFillTransmitBuffer(PduInfoPtr, TempPduInfo,
                                           NodeRegAddressPtr, TxMsgBufferPtr);
    #else
    /* Set DLC with requested value */
    TxMsgDLC = TempPduInfo->length;
    #endif

    /* Write DLC value to the T1 buffer */
    TxMsgBufferPtr->T1.B.DLC = TxMsgDLC;

    /* Write Event FIFO */
    TxMsgBufferPtr->T1.B.EFC = 1U;

    /* Calculate Sw Obj Handle index */
    SwObjIndx = (uint16)((ControllerId *
                   CAN_17_MCMCAN_NOOF_TX_HW_BUFF_AVAILABLE) + BuffElementIndex);

    /* Store sPduHandle Id for Tx confirmation process */
    CoreGlobalPtr->CanSwObjectHandlePtr[SwObjIndx] = PduInfoPtr->swPduHandle;

    /* Write Message Marker with SwHandle Index (HTH Indx - Controller StartHTH
    Index) Index for the Tx confirmation process */
    TxMsgBufferPtr->T1.B.MM = BuffElementIndex;

    /* Set data byte position with zero index */
    DataBytePos = 0U;

    #if (CAN_17_MCMCAN_FD_ENABLE == STD_ON)
    /* Convert DLC length to Number of Data Bytes supported by Hw */
    TxMsgDLC = Can_17_McmCan_GblFdDlcConvDB[TxMsgDLC];
    #endif

    /* Set loop for write with Number of Data Byte */
    while (TxMsgDLC > DataBytePos)
    {
      #if (CAN_17_MCMCAN_FD_ENABLE == STD_OFF)
      /* Store the data to the Tx Buffer */
      /* [cover parentID={2009DBAB-A5F6-4e87-BE49-6C1912F107ED}]
      Store extended Id and set XTD bit
      [/cover] */
      /* [cover parentID={E8DDD82E-BA0D-4872-84C4-0F67E7522B18}]
      Store sPduHandle Id for Tx Confirmation process
      [/cover] */
      TxMsgBufferPtr->DB[DataBytePos].U = TempPduInfo->sdu[DataBytePos];
      #else
      /* [cover parentID={54997C5D-274B-4e87-B39F-AE4FE0DACEF7}]
      Check byte position is with in the DLC
      [/cover] */
      if (DataBytePos < TempPduInfo->length)
      {
        /* Copy Message data to the Tx Buffer */
        /* [cover parentID={773E49C8-EEB4-4732-B164-BFEF1F4B02AB}]
        Store the data to the Tx Buffer
        [/cover] */
        TxMsgBufferPtr->DB[DataBytePos].U = TempPduInfo->sdu[DataBytePos];
      }
      else
      {
        /* Store with padding values to the Tx buffer */
        TxMsgBufferPtr->DB[DataBytePos].U = TxObjPtr[HthIndex].CanFdPaddValue;
      }
      #endif /* (CAN_17_MCMCAN_FD_ENABLE == STD_OFF) */

      /* Set for next data byte */
      DataBytePos++;
    }
    /* [cover parentID={83E2512D-CB7A-4a18-9AEA-2FC0DCD6A5C7}]
    Request for the Transmission
    [/cover] */
    NodeRegAddressPtr->TX.BAR.U = (Ifx_UReg_32Bit)BuffIndex;
  }

  /* Exit Critical Section */
  /* [cover parentID={85BA8CAE-3074-406e-B64D-361C3FAA9D22}]
  Exit Critical Section call
  [/cover] */
  SchM_Exit_Can_17_McmCan_CanWrMO();

  /* [cover parentID={5925E0A4-AEC9-4be4-9FEB-26D1EFF6EC91}]
  Return the status
  [/cover] */
  return RetVal;
}
/*******************************************************************************
** Traceability   : [cover parentID={56493419-1258-4521-BF29-67D088707B8D}]   **
**  Syntax           : static void Can_17_McmCan_lRxExtractData               **
**                    (                                                       **
**                      const uint8 RxBuffIndex,                              **
**                      const Can_17_McmCan_RxBufferType RxBuffer,            **
**                      Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,    **
**                      const Can_17_McmCan_CoreConfigType *const ConfigPtr   **
**                    )                                                       **
**                                                                            **
**  Description      : This function extracts data from the message object    **
**                    and notifies upper layer                                **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant                                              **
**                                                                            **
**  Parameters (in)  : RxBuffIndex - Bit Position within MSPND Register       **
**                     RxBuffer - receive buffer type used which can be       **
**                                       Dedicated RX/FIFO0/FIFO1             **
**                     ConfigPtr - Pointer to CAN driver configuration        **
**                     CoreGlobalPtr - Pointer to global structure            **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Parameters (in-out) : none                                                **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
static void Can_17_McmCan_lRxExtractData(const uint8 HwControllerId,
    const uint8 RxBuffIndex,
    const Can_17_McmCan_RxBufferType RxBuffer,
    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr)
{
  /*Pointer to message RAM configuration*/
  const Can_17_McmCan_ControllerMsgRAMConfigType *MsgRamCfgPtr;

  /*Pointer to RX Message RAM structure*/
  volatile const Ifx_CAN_RXMSG *RxMsgRAMPtr;

  /*Variable to store the message object info to be passed to upper layer*/
  Can_HwType RxMailBoxInfo;

  /*Variable to store the RX PDU info*/
  PduInfoType RxPduInfo;

  /*SID filter configuration */
  const Can_17_McmCan_SIDFilterConfigType *SIDFilterPtr;

  /*XID filter configuration */
  const Can_17_McmCan_XIDFilterConfigType *XIDFilterPtr;

  /*RX start address for Read*/
  uint32 RxReadStartAddr;

  /*RX read offset address*/
  uint32 RxReadOffsetAddr;

  /*Filter start index*/
  uint16 FiltrStartIndx;

  /*RX message Data*/
  uint8 RxMsgDLC;

  /*Filter index of RX message*/
  uint8 RxMsgFilterIndx;

  /*RX message count*/
  uint8 RxMsgCnt;

  /*RX message ID*/
  Can_IdType RxMsgId;

  /*Array to store the RX Message DATA. The size would differ based on FD
  or standard*/
  #if (CAN_17_MCMCAN_FD_ENABLE == STD_ON)
  uint8 RxMessageData[CAN_17_MCMCAN_NOOF_CONTROLLER]
                                        [CAN_17_MCMCAN_MAX_FD_LENGTH];

  #else
  uint8 RxMessageData[CAN_17_MCMCAN_NOOF_CONTROLLER]
                                         [CAN_17_MCMCAN_MAX_DATA_LENGTH];
  #endif

  /*Variable to evaluate the LPDU callout return*/
  #if (CAN_17_MCMCAN_LPDU_RX_CALLOUT == STD_ON)
  boolean RetVal;
  #endif

  /* Set Message RAM configuration pointer with configuration address */
  MsgRamCfgPtr = CoreConfigPtr->CanControllerMsgRAMMapConfigPtr;

  /* Check requested buffer type */

  /* [cover parentID={CC1A3A21-1E66-4fa4-9FCB-BD30E3B458C4}]
  Requested buffer type
  [/cover] */
  if (CAN_17_MCMCAN_RX_FIFO0 == RxBuffer)
  {
    /* Read Rx Message RAM start address of RXFIFO0 */
    RxReadStartAddr = MsgRamCfgPtr[HwControllerId].
                      CanControllerMsgRAMMap[CAN_17_MCMCAN_F0SA];
  }
  else if (CAN_17_MCMCAN_RX_FIFO1 == RxBuffer)
  {
    /* Read Rx Message RAM start address of RXFIFO1 */
    RxReadStartAddr =
        MsgRamCfgPtr[HwControllerId].CanControllerMsgRAMMap[CAN_17_MCMCAN_F1SA];
  }
  else
  {
    /* Read Rx Message RAM start address of dedicated buffer */
    RxReadStartAddr =
        MsgRamCfgPtr[HwControllerId].CanControllerMsgRAMMap[CAN_17_MCMCAN_RBSA];
  }

  /* Set OFFSET address with  buffer position */
  RxReadOffsetAddr = RxBuffIndex;

  /*Start Address value*/
  /* [cover parentID={33A22D31-6C26-4717-925E-939EE7EE3DCB}]
  Start Address value
  [/cover] */
  if (CAN_17_MCMCAN_ADDRESS_CHECK != RxReadStartAddr)
  {
    #if (CAN_17_MCMCAN_FD_ENABLE == STD_ON)
    /* Check if FD support is enabled for the controller*/
    if (TRUE ==
        CoreConfigPtr->CanControllerConfigPtr[HwControllerId].CanFDSupport)
    {
      /* Load the data receive message buffer address */
      RxReadStartAddr = RxReadStartAddr + (RxReadOffsetAddr *
                                 (uint32)CAN_17_MCMCAN_MSG_RAM_ELEMENT_SIZE_FD);
    }
    else
    #endif

    {

      /* Load the data receive message buffer address */
      RxReadStartAddr = RxReadStartAddr + (uint32)
                    (RxReadOffsetAddr * CAN_17_MCMCAN_MSG_RAM_ELEMENT_SIZE_NFD);
    }

    /* Load the data receive message buffer address */
    /* MISRA2012_RULE_11_6_JUSTIFICATION: The pointer cast is used to cast the
    address to the Rx buffer elements structure type for accessing RAM area*/
    /* MISRA2012_RULE_11_4_JUSTIFICATION: Memory address is generated as a
    numerical value, it is accessed as a pointer to the RAM address.
    Hence an explicit typecast from numerical to pointer. */
    RxMsgRAMPtr = (volatile Ifx_CAN_RXMSG *)RxReadStartAddr;

    /* Extract DLC information */
    RxMsgDLC = RxMsgRAMPtr->R1.B.DLC;

    /* Read Filter Index */
    RxMsgFilterIndx = RxMsgRAMPtr->R1.B.FIDX;

    /* Extract receive Msg.ID  and ID Type */
    /* [cover parentID={E48CA5D5-56B5-4124-87E7-E4FC09F758C9}]
    Message ID type configured
    [/cover] */
    if (CAN_17_MCMCAN_BIT_CLEAR_VAL == RxMsgRAMPtr->R0.B.XTD)
    {
      /* Read received message Id and Message type */
      RxMsgId = RxMsgRAMPtr->R0.B.ID >> CAN_17_MCMCAN_SHIFT_MSGRAM_RT_MASK;

      /* First index value of standard filter set */
      FiltrStartIndx = CoreConfigPtr->CanControllerConfigPtr[HwControllerId].
                       CanControllerMOMap[CAN_17_MCMCAN_RX_SID_STARTINDEX];

      /* Set SID filter list Address */
      SIDFilterPtr = CoreConfigPtr->CanSIDFilterConfigPtr;

      /* Read and store the HOH Id*/
      RxMailBoxInfo.Hoh = SIDFilterPtr[FiltrStartIndx + RxMsgFilterIndx].
                          CanSidHwObjId;
    }
    else
    {
      /* Set message ID type as Extended */
      /* [cover parentID={F220106E-922D-4368-9EBD-0C83BDB56ABB}]
      Set message ID type as extended and extract the message ID
      [/cover] */
      RxMsgId = CAN_17_MCMCAN_SET_XTD_BIT_MASK;

      /* Copy message ID  */
      RxMsgId |= (Can_IdType)RxMsgRAMPtr->R0.B.ID;

      /* First index value of Extended filter set */
      FiltrStartIndx = CoreConfigPtr->CanControllerConfigPtr[HwControllerId].
                       CanControllerMOMap[CAN_17_MCMCAN_RX_XID_STARTINDEX];

      /* Set XID filter list Address */
      XIDFilterPtr = CoreConfigPtr->CanXIDFilterConfigPtr;

      /* Read and store the HOH Id*/
      RxMailBoxInfo.Hoh =
          XIDFilterPtr[FiltrStartIndx + RxMsgFilterIndx].CanXidHwObjId;
    }

    /* Read FD status of received Message */
    #if (CAN_17_MCMCAN_FD_ENABLE == STD_ON)
    /* Read receive data information from R1 RAM element */
    /* [cover parentID={3CBFC192-2B42-491a-95FA-C9EBE7401C43}]
    Set FD bit of MsgId
    [/cover] */
    if (CAN_17_MCMCAN_BIT_SET_VAL == RxMsgRAMPtr->R1.B.FDF)
    {
      /* Set FD bit of MsgId */
      RxMsgId |= (Can_IdType)CAN_17_MCMCAN_SET_FD_MASK;
    }
    #endif /* #if (CAN_17_MCMCAN_FD_ENABLE == STD_ON) */

    /* Clear to read from Byte0 */
    RxMsgCnt = 0U;

    /* [cover parentID={0ABD541D-73FA-404a-9AD7-1AFE9DE0D81C}]
    CAN FD support is enabled for the controller
    [/cover] */
    #if (CAN_17_MCMCAN_FD_ENABLE == STD_ON)
    /* Convert DLC length to Number of Data Bytes supported by Hw */
    RxMsgDLC = Can_17_McmCan_GblFdDlcConvDB[RxMsgDLC];
    #endif /* #if (CAN_17_MCMCAN_FD_ENABLE == STD_ON) */

    /* Copy Message from RAM section to local data buffer */
    while (RxMsgCnt < RxMsgDLC)
    {
      /* copy data from byte0 to n the buffer */
      RxMessageData[HwControllerId][RxMsgCnt] = RxMsgRAMPtr->DB[RxMsgCnt].U;

      /* Increment to point next byte */
      RxMsgCnt++;
    }
    /* Call CanIf_RxIndication function with receive message information */
    RxMailBoxInfo.CanId = RxMsgId;

    RxMailBoxInfo.ControllerId = HwControllerId;

    RxPduInfo.SduLength = RxMsgDLC;

    /*MISRA2012_RULE_1_3_JUSTIFICATION:Address of auto variable is used
    only to read the values. The address is not used to perform any
    pointer arithmetic. hence no side effect has been seen.*/
    RxPduInfo.SduDataPtr = &RxMessageData[HwControllerId][0U];

    /*CAN public ICOM support is enabled*/
    /* [cover parentID={2BCD3D07-EC74-4f1b-AAD8-90099FBCD5FE}]
    CAN public ICOM support is enabled
    [/cover] */
    #if (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON)
    /* Check ICOM enabled */
    /* [cover parentID={F4D157C9-719B-425f-B679-E0410C730006}]
    Check ICOM is enabled for current controller
    [/cover] */
    if (TRUE == CoreGlobalPtr->CanIcomEnableStatusPtr[HwControllerId])
    {
      /* Call Message validate function */
      /*MISRA2012_RULE_1_3_JUSTIFICATION:Address of auto variable is used
      only to read the values. The address is not used to perform any
      pointer arithmetic. hence no side effect has been seen.*/
      Can_17_McmCan_lIcomValidateMsg(&RxMailBoxInfo, &RxPduInfo,
                                     CoreGlobalPtr, CoreConfigPtr);
    }
    else
    #else
    UNUSED_PARAMETER(CoreGlobalPtr);
    #endif /* #if(CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON) */

    {
      /*Is CAN LPdu callout function configured?*/
      #if (CAN_17_MCMCAN_LPDU_RX_CALLOUT == STD_ON)
      /* [cover parentID={9CD3A689-BDAE-4a51-A03E-6CA3504EF9BD}]
      Does LPdu callout function return TRUE?
      [/cover] */
      /* Call the LPDU callout function to check the return value */
      /* [cover parentID={3C5C0097-2631-4ff8-A314-C113C00DA37A}]
      [/cover] */
      RetVal = Can_17_McmCan_kGblConfigPtr->
                             CanLPduRxCalloutFuncPtr((RxMailBoxInfo.Hoh),
                                                          RxMsgId,
                                                          RxMsgDLC,
                                                          RxPduInfo.SduDataPtr);

      /* Notification function CanIf_RxIndication should be called only if the
      callout function returns true */
      /* [cover parentID={4A6EFA0F-F343-460b-B81F-8C7F73B53812}]
      FD status of recieve message register
      [/cover] */
      if (RetVal == TRUE)
      #endif /* #if (CAN_17_MCMCAN_LPDU_RX_CALLOUT == STD_ON) */
      {
        /* get logical Id to be passed to upper layer */
        RxMailBoxInfo.ControllerId = CoreConfigPtr->CanControllerIndexingPtr
                                     [HwControllerId];

        /*Notify to reception of message to CAN IF layer*/
        /*MISRA2012_RULE_1_3_JUSTIFICATION:Address of auto variable is used
        only to read the values. The address is not used to perform any
        pointer arithmetic. hence no side effect has been seen.*/
        /* [cover parentID={F495F68A-E87C-4161-BBF1-02187F5BF35D}]
        Notify to reception of message to CAN IF layer
        [/cover] */
        CanIf_RxIndication(&RxMailBoxInfo, &RxPduInfo);
      }
    }
  }
}
/*******************************************************************************
** Traceability   : [cover parentID={C3CEA0E7-2745-4d57-9B07-A608552CF60F}]   **
                                                                              **
**  Syntax           : static void Can_17_McmCan_lSIDFilterConfig             **
**                    (                                                       **
**                      const uint8 ControllerId,                             **
**                      const Can_17_McmCan_CoreConfigType *const CoreConfigPtr*
**                    )                                                       **
**                                                                            **
**  Description      : This function configure Standard filter register for   **
**                     filter usage and will writes the 11-bit message ID     **
**                     filter element into the Message RAM.                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Non-Reentrant                                          **
**                                                                            **
**  Parameters (in)  : ControllerId - Indexing of core specific CAN Controller**
**                     CoreConfigPtr - Pointer to CAN driver configuration    **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
static void Can_17_McmCan_lSIDFilterConfig(const uint8 ControllerId,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr)
{
  /*Can controller node address pointer*/
  volatile Ifx_CAN_N *NodeRegAddressPtr;

  /*SID filter data pointer*/
  volatile Ifx_CAN_STDMSG *SIDFilterDataPtr;

  /*SID data pointer*/
  const Can_17_McmCan_SIDFilterConfigType *SIDPtr;

  /*SID start address*/
  uint32 SIDFilterStartAddr;

  /*SID filter real address*/
  uint32 SIDFilterRealAddr;

  /*SID filter offset*/
  uint32 SIDFiltrOffset;

  /*SID filter index*/
  uint16 SIDFiltrIndx;

  /*SID filter start index*/
  uint16 SIDFiltrStartIndx;

  /*SID filter end index*/
  uint16 SIDFiltrEndIndx;

  /* Read the exact Node Start address */
  NodeRegAddressPtr = CoreConfigPtr->
                      CanControllerConfigPtr[ControllerId].CanNodeAddressPtr;

  /* Set SID filter list Address */
  SIDPtr = CoreConfigPtr->CanSIDFilterConfigPtr;

  /* Set with first SID filter Index */
  SIDFiltrStartIndx = CoreConfigPtr->CanControllerConfigPtr[ControllerId].
                      CanControllerMOMap[CAN_17_MCMCAN_RX_SID_STARTINDEX];

  /* Set with End SID filter Index */
  SIDFiltrEndIndx = SIDFiltrStartIndx +
                    CoreConfigPtr->CanControllerConfigPtr[ControllerId].
                    CanControllerMOMap[CAN_17_MCMCAN_TOTAL_SIDCFG];

  /* Read Standard Identifier filter Start address */
  SIDFilterStartAddr = CoreConfigPtr->
                       CanControllerMsgRAMMapConfigPtr[ControllerId].
                       CanControllerMsgRAMMap[CAN_17_MCMCAN_FLSSA];

  /* Load with Start address offset */
  NodeRegAddressPtr->SIDFC.B.FLSSA = ((uint16)((SIDFilterStartAddr &
                                     CAN_17_MCMCAN_RAM_ADDRESS_OFFSET_MASK) >>
                                     CAN_17_MCMCAN_MSGRAM_SHIFT_MASK));

  /* Set with Standard section RAM size */
  NodeRegAddressPtr->SIDFC.B.LSS = (uint8)SIDFiltrEndIndx - SIDFiltrStartIndx;

  /* Set Offset with First element */
  SIDFiltrOffset = 0U;

  /* Set with all standard filter configuration */
  /* [cover parentID={881B71FF-B6A6-4236-A65E-B6154C82CFFF}]
  Loop through all standard filter configurations
  [/cover] */
  for (SIDFiltrIndx = SIDFiltrStartIndx; SIDFiltrIndx < SIDFiltrEndIndx;
        SIDFiltrIndx++)
  {
    /* Set with SID element address */
    SIDFilterRealAddr = SIDFilterStartAddr + (CAN_17_MCMCAN_RAM_BYTES *
                        SIDFiltrOffset);

    /* MISRA2012_RULE_11_6_JUSTIFICATION: The pointer cast is used to
    cast the address to the Standard filter elements structure type
    for accessing RAM area */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: Memory address is generated as a
    numerical value, it is accessed as a pointer to the RAM address.
    Hence an explicit typecast from numerical to pointer. */
    SIDFilterDataPtr = (volatile Ifx_CAN_STDMSG *)SIDFilterRealAddr;

    /* Set Filter Data to the Filter element */
    SIDFilterDataPtr->S0.U = SIDPtr[SIDFiltrIndx].CanSIDFiltEleS0;

    /* Increment for access next element */
    SIDFiltrOffset++;
  }
}

/*******************************************************************************
** Traceability   : [cover parentID={FCE63161-A42C-41c4-9951-5F0A58190ED5}]   **
**                                                                            **
**  Syntax           : static void Can_17_McmCan_lXIDFilterConfig             **
**                    (                                                       **
**                      const uint8 ControllerId,                             **
**                      const Can_17_McmCan_CoreConfigType *const CoreConfigPtr*
**                    )                                                       **
**                                                                            **
** Description    :The function configures the extended filter register for   **
**                 filter usage and will writes the 29-bit message ID filter  **
**                 element into the Message RAM.                              **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Non-Reentrant                                          **
**                                                                            **
**  Parameters (in)  : ControllerId - Indexing of core specific CAN Controller**
**                     CoreConfigPtr - Pointer to CAN driver configuration    **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
static void Can_17_McmCan_lXIDFilterConfig(const uint8 ControllerId,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr)
{
  /*Can controller node address pointer*/
  volatile Ifx_CAN_N *NodeRegAddressPtr;

  /*XID filter data pointer*/
  volatile Ifx_CAN_EXTMSG *XIDFilterPtr;

  /*SID data pointer*/
  const Can_17_McmCan_XIDFilterConfigType *XIDPtr;

  /*XID start address*/
  uint32 XIDFilterStartAddr;

  /*XID filter real address*/
  uint32 XIDFilterRealAddr;

  /*XID filter data*/
  uint32 XIDFilterData;

  /*XID filter index*/
  uint16 XIDFiltrIndx;

  /*XID filter start index*/
  uint16 XIDFiltrStartIndx;

  /*XID filter end index*/
  uint16 XIDFiltrEndIndx;

  /*XID offset*/
  uint8 XIDOffsetIndx;

  /* Read the exact Node Start address */
  NodeRegAddressPtr =
          CoreConfigPtr->CanControllerConfigPtr[ControllerId].CanNodeAddressPtr;

  /* Set with start Index */
  XIDFiltrStartIndx =  CoreConfigPtr->CanControllerConfigPtr[ControllerId].
                      CanControllerMOMap[CAN_17_MCMCAN_RX_XID_STARTINDEX];

  /* Set with end Index */
  XIDFiltrEndIndx = XIDFiltrStartIndx +
                    CoreConfigPtr->CanControllerConfigPtr[ControllerId].
                    CanControllerMOMap[CAN_17_MCMCAN_TOTAL_XIDCFG];

  /* Set XID filter list Address */
  XIDPtr = CoreConfigPtr->CanXIDFilterConfigPtr;

  /* Read Extended Identifier filter Start address */
  XIDFilterStartAddr = CoreConfigPtr->
                       CanControllerMsgRAMMapConfigPtr[ControllerId].
                       CanControllerMsgRAMMap[CAN_17_MCMCAN_FLSEA];

  /* Load with Start address offset */
  NodeRegAddressPtr->XIDFC.B.FLESA = ((uint16)((XIDFilterStartAddr &
                                      CAN_17_MCMCAN_RAM_ADDRESS_OFFSET_MASK) >>
                                      CAN_17_MCMCAN_MSGRAM_SHIFT_MASK));

  /* Set with Extended section RAM size */
  NodeRegAddressPtr->XIDFC.B.LSE = (uint8)(XIDFiltrEndIndx - XIDFiltrStartIndx);

  /* Set with first Filter Index */
  XIDOffsetIndx = 0U;

  /* Set with all Extended filter configuration */
  /* [cover parentID={8D07FF6A-2898-4d17-9CAE-2C4DCD8B580F}]
  Set each of XID filter configuration
  [/cover] */
  for (XIDFiltrIndx = XIDFiltrStartIndx; XIDFiltrIndx < XIDFiltrEndIndx;
      XIDFiltrIndx++)
  {
    /* Set element offset address F0 */
    XIDFilterRealAddr = XIDFilterStartAddr + (XIDOffsetIndx *
                     CAN_17_MCMCAN_RAM_BYTES * CAN_17_MCMCAN_MSGRAM_SHIFT_MASK);

    /* Read Filter F0 configuration data */
    XIDFilterData = XIDPtr[XIDFiltrIndx].CanXIDFiltEleF0;

    /* MISRA2012_RULE_11_6_JUSTIFICATION: The pointer cast is used to
    cast the address to the extended filter elements structure type
    for accessing RAM area */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: Memory address is generated as a
    numerical value, it is accessed as a pointer to the RAM address.
    Hence an explicit typecast from numerical to pointer. */
    XIDFilterPtr = (volatile Ifx_CAN_EXTMSG *)XIDFilterRealAddr;

    /* Set Filter element F0 with configuration data */
    XIDFilterPtr->F0.U = XIDFilterData;

    /* Read Filter F1 configuration data */
    XIDFilterData = XIDPtr[XIDFiltrIndx].CanXIDFiltEleF1;

    /* Set Filter element F1 with configuration data */
    XIDFilterPtr->F1.U = XIDFilterData;

    /* Increment to next offset */
    XIDOffsetIndx++;
  }
}

/*******************************************************************************
** Traceability   : [cover parentID={7B84CDB7-2FA1-4d35-9D20-2AF5D95D5FDB}]   **
**                                                                            **
**  Syntax           : Can_17_McmCan_ReturnValueType Can_17_McmCan_lWrite     **
**                    (                                                       **
**                      const Can_HwHandleType Hth,                           **
**                      const Can_PduType *const PduInfoPtr                   **
**                    )                                                       **
**                                                                            **
**  Description      : Service to transmit CAN frame                          **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant                                              **
**                                                                            **
**  Parameters (in)  : Hth - Hardware Transmit Handle                         **
**                    PduInfoPtr - Pointer to SDU user memory, DLC and        **
**                                                            Identifier      **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : CAN_17_MCMCAN_OK: Write command accepted, write is
**                      successful                                            **
**                     CAN_17_MCMCAN_NOT_OK: Service request not successful,  **
**                     or development error reported.                         **
**                     CAN_17_MCMCAN_BUSY: No TX hardware buffer available or **
**                     pre-emptive call of Can_Write that cannot be           **
**                     implemented re-entrant.                                **
**                                                                            **
*******************************************************************************/
static Can_17_McmCan_ReturnValueType Can_17_McmCan_lWrite(
    const Can_HwHandleType Hth, const Can_PduType *const PduInfoPtr)
{
  /*HTH index*/
  Can_HwHandleType HthIndex;

  /* Return value */
  Can_17_McmCan_ReturnValueType ReturnValue = CAN_17_MCMCAN_NOT_OK;

  /* calling core index */
  uint8 CoreIndex;

  /* core specifc configuration */
  const Can_17_McmCan_CoreConfigType *CoreConfigPtr;

  /* core specifc global variable structure */
  const Can_17_McmCan_CoreGlobalType *CoreGlobalPtr;

  /* Get core id which is executing currently */
  CoreIndex = CAN_17_MCMCAN_GETCOREINDEX;

  /* [cover parentID={782F1606-4FAF-4688-965D-55A6C08C835C}]
  Write message into Tx buffer and request for transmission
  [/cover] */
  #if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON)

  /* Det check status */
  Std_ReturnType DetStatus;

  /*Check if DET has occured*/
  DetStatus = Can_17_McmCan_lWriteDetCheck(Hth, PduInfoPtr);

  /* [cover parentID={0AC79A75-B548-43fa-86B0-94FD3227CCF3}]
  Have the DET checks passed?
  [/cover] */
  if (E_OK == DetStatus)
  #endif /* #if(CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Local copy of the core specific configuration */
    CoreConfigPtr = Can_17_McmCan_kGblConfigPtr->CanCoreConfigPtr[CoreIndex];

    /* Local copy of the core specific global states */
    CoreGlobalPtr = Can_17_McmCan_GblCoreState[CoreIndex];

    /* Extract HTH index for accessing corresponding configuration */
    HthIndex = Can_17_McmCan_kGblConfigPtr->
               CanHthIndexPtr[Hth - (Can_17_McmCan_kGblConfigPtr->CanNoOfHrh)].
               CanHthCoreSpecIndex;

    /* Call function for write message into Tx buffer and request for
    Transmission */
    ReturnValue = Can_17_McmCan_lWriteMsgObj(HthIndex, PduInfoPtr,
                                             CoreGlobalPtr, CoreConfigPtr);
  }

  /* [cover parentID={83A544F0-08D8-4479-BE49-39229FF9EF23}]
  Return the value of the write operation result
  [/cover] */
  return ReturnValue;
}

/*******************************************************************************
         Receive ,Transmit ,Wakeup and Bus-Off  Handler
*******************************************************************************/
#if (((CAN_17_MCMCAN_RX_POLLING_PROCESSING == STD_ON) &&      \
     (CAN_17_MCMCAN_RX_MULTI_PERIODS_SUPPORT == STD_OFF)) ||  \
     (CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON) ||     \
     (CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON) ||         \
     ((CAN_17_MCMCAN_WU_POLLING_PROCESSING == STD_ON) &&      \
  (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON)))
/*******************************************************************************
** Traceability   : [cover parentID={DA288EF6-8632-4470-B2DB-98E7946FF40E}]   **
**                                                                            **
**  Syntax           : static void Can_17_McmCan_lReceiveHandler              **
**                    (                                                       **
**                      const uint8 HwControllerId,                           **
**                      const uint8 CheckBuffType,                            **
**                      Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,    **
**                      const Can_17_McmCan_CoreConfigType *const CoreConfigPtr*
**                    )                                                       **
**                                                                            **
**  Description      : - This function is the core part of the interrupt      **
**                      service routine for Receive Interrupt                 **
**                    - In case of successful reception event, this           **
**                      function calls the function                           **
**                     Can_17_McmCan_lRxExtractData to extract data from the  **
**                                message object and notify upper layer       **
**                    - This function is also called by the polling function  **
**                      Can_17_McmCan_MainFunction_Read for controllers       **
**                      configured with CanRxProcessing as POLLING or MIXED   **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant for different controllers.                   **
**                     Non reentrant for the same controller.                 **
**                                                                            **
**  Parameters (in)  :  HwControllerId - Associated CAN Controller            **
**                      CheckBuffType -  Data received buffer type            **
**                      ProcessingType -  Rx processing type                  **
**                      CoreConfigPtr - Pointer to CAN driver configuration   **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Parameters (in-out) : CoreGlobalPtr - Pointer to global structure         **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
static void Can_17_McmCan_lReceiveHandler(const uint8 HwControllerId,
    const Can_17_McmCan_RxBufferType CheckBuffType,
    const Can_17_McmCan_ProcessingType ProcessingType,
    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr)
{

  switch (CheckBuffType)
  {
    /* [cover parentID={2A8D12D0-8282-405f-B6F6-14ADF180E0ED}]
    Check if the buffer is RX DED
    [/cover] */
    case CAN_17_MCMCAN_RX_DED_BUFFER:
    {
      /*Invoke RX DED handler*/
      /* [cover parentID={E46502AD-E980-44df-A89A-A1A7C974686B}]
      Invoke RX dedicated handler
      [/cover] */
      Can_17_McmCan_lRxDedicatedHandler(HwControllerId, ProcessingType,
      CoreConfigPtr, CoreGlobalPtr);

      break;
    }
    /* [cover parentID={FEE28BE0-F1D0-4bc1-AA16-7FFF64BEF7EC}]
    Check if the buffer type is RX FIFO 0
    [/cover] */
    case CAN_17_MCMCAN_RX_FIFO0:
    {
      /*Invoke RX FIFO0 handler*/
      /* [cover parentID={A329D084-B1F5-43df-9334-18698F870782}]
      Invoke RX FIFO0 handler
      [/cover] */
      Can_17_McmCan_lRxFIFO0Handler(HwControllerId, ProcessingType,
                                                  CoreConfigPtr, CoreGlobalPtr);

      break;
    }
    /* [cover parentID={D25F4E22-53FC-49a6-9EB5-ABDB227EFD67}]
    Check if the buffer type RXFIFO1
    [/cover] */
    case CAN_17_MCMCAN_RX_FIFO1:
    {
      /*Invoke RX FIFO1 handler*/
      /* [cover parentID={99D42998-94F1-4b9c-BE4E-7C3D335A6CA9}]
      Invoke RXFIFO1 handler
      [/cover] */
      Can_17_McmCan_lRxFIFO1Handler(HwControllerId, ProcessingType,
                                                  CoreConfigPtr, CoreGlobalPtr);

      break;
    }
    /* [cover parentID={3A24AF71-3E04-4610-9216-782E1A18C0BA}]
    Check if the processing has to be done for all buffer types
    [/cover] */
    default:
    {
      /*Invoke RX DED handler*/
      /* [cover parentID={D4CE4E8E-16BB-4aee-BEA5-2A698DFE74C0}]
      Invoke RX dedicated handler
      [/cover] */
      Can_17_McmCan_lRxDedicatedHandler(HwControllerId, ProcessingType,
      CoreConfigPtr, CoreGlobalPtr);

      /*Invoke RX FIFO0 handler*/
      /* [cover parentID={59E49D06-8336-49ce-AFF9-B1696F05800B}]
      Invoke RX FIFO0 handler
      [/cover] */
      Can_17_McmCan_lRxFIFO0Handler(HwControllerId, ProcessingType,
                                        CoreConfigPtr, CoreGlobalPtr);

      /*Invoke RX FIFO1 handler*/
      /* [cover parentID={27B4BA44-39D3-48f7-BFFC-AD90241E7A84}]
      Invoke RX FIFO1 handler
      [/cover] */
      Can_17_McmCan_lRxFIFO1Handler(HwControllerId, ProcessingType,
                                        CoreConfigPtr, CoreGlobalPtr);
      break;
    }
  }
}

/*******************************************************************************
** Traceability   : [cover parentID={C7386540-E0F2-4b4c-A092-AB11D574E972}]   **
**                                                                            **
**  Syntax           : static void Can_17_McmCan_lRxFIFO0Handler              **
**                    (const uint8 HwControllerId,                            **
**                    const Can_17_McmCan_ProcessingType ProcessingType,      **
**                    const Can_17_McmCan_CoreConfigType *const ConfigPtr,    **
**                    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr)**
**                                                                            **
**  Description      : - This function shall process the reception of message **
**                        in RX FIFO0 objects                                 **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant                                              **
**                                                                            **
**  Parameters (in)  :  HwControllerId - Associated CAN Controller            **
**                      ProcessingType -  Rx processing type                  **
**                      ConfigPtr - Pointer to CAN driver configuration       **
**                      CoreGlobalPtr - Pointer to global structure           **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Parameters (in-out) :  none                                               **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/

static void Can_17_McmCan_lRxFIFO0Handler(const uint8 HwControllerId,
                      const Can_17_McmCan_ProcessingType ProcessingType,
                      const Can_17_McmCan_CoreConfigType *const CoreConfigPtr,
                      const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr)
{
  /*Can controller node address pointer*/
  volatile Ifx_CAN_N *NodeRegAddressPtr;

  /*RX FIFO processing type*/
  Can_17_McmCan_RxFIFOProcessingType RxFIFOProcessing;

  /*Variable to store RX buffer position*/
  uint8 RxHandleBuffPos;

  /*Flag to traverse through the RX FIFO types*/
  uint8 LoopExitCounter = 0;

  /*FIFO size*/
  uint8 FifoSize = CoreConfigPtr->
                 CanControllerMsgRAMMapConfigPtr[HwControllerId].CanRxFIFO0Size;

  /* Read the exact Node Start address */
  NodeRegAddressPtr = CoreConfigPtr->
                       CanControllerConfigPtr[HwControllerId].CanNodeAddressPtr;

  /*Read the processing type for RX FIFO*/
  RxFIFOProcessing = CoreConfigPtr->
              CanControllerConfigPtr[HwControllerId].CanRxFIFO0ProcessingConfig;

  /*Check the processing type for the RX FIFO0*/
  /* [cover parentID={6914BEB8-6A34-49fb-983C-A8009F047625}]
  Check if the processing type requested and the type read are the same?
  [/cover] */
  if ((uint8)RxFIFOProcessing == (uint8)ProcessingType)
  {

    /* Check Received CAN message is lost*/
    /* [cover parentID={251805DF-6482-42e8-9673-780589D4080F}]
    Check if the recieved CAN message is LOST?
    [/cover] */
    if (NodeRegAddressPtr->IR.B.RF0L != CAN_17_MCMCAN_BIT_CLEAR_VAL)
    {
      #if (CAN_17_MCMCAN_RUNTIME_ERROR_DETECT == STD_ON)
      /*Invoke the RUNTIME error handler to report CAN_E_DATALOST*/
      /* [cover parentID={04E14FBD-5FA0-426c-B842-A6EC4477F4D1}]
       Invoke function to report data lost error
       [/cover] */
       /* [cover parentID={D0691E36-6A44-4042-BEE5-D528EC3385C9}]
       Invoke function to report data lost error
       [/cover] */
      (void)Mcal_Wrapper_Det_ReportRuntimeError(CAN_17_MCMCAN_MODULE_ID,
            CAN_17_MCMCAN_INSTANCE_ID, CAN_17_MCMCAN_SID_RECEIVEHANDLER,
            CAN_17_MCMCAN_E_DATALOST);

      #endif
      NodeRegAddressPtr->IR.U = CAN_17_MCMCAN_RF0L_CLEAR;
    }

    /*Loop till all messages are read in Rx FIFO 0 or read max configured
    messages in FIFO*/
    /* [cover parentID={EDC0479C-D4A4-46e8-BC15-ADD79872C849}]
    Loop till all messages are read in Rx FIFO 0 or read max configured
    messages in FIFO0
    [/cover] */
    while ((NodeRegAddressPtr->RX.F0S.B.F0FL > 0U) &&
                                                   (LoopExitCounter < FifoSize))
    {
      LoopExitCounter++;
      /* a. Read all FIFO slots and acknowledge to free up slots
        b. Notify upper layer */
      /* Read Rx FIFO 0 Get Index */
      RxHandleBuffPos = NodeRegAddressPtr->RX.F0S.B.F0GI;

      /* Invoke data retrieve function */
      /* [cover parentID={F763BA89-1A78-4c20-B1B0-3E39D511A16B}]
      Invoke data retrieve function
      [/cover] */
      Can_17_McmCan_lRxExtractData(HwControllerId, RxHandleBuffPos,
                          CAN_17_MCMCAN_RX_FIFO0, CoreGlobalPtr, CoreConfigPtr);

      /* Set read Acknowledge of buffer */
      NodeRegAddressPtr->RX.F0A.U = RxHandleBuffPos;
    }
  }
}

/*******************************************************************************
** Traceability   : [cover parentID={7EF67B42-DC07-4b50-AF34-6AE739AA3AC3}]   **
**  Syntax           : static void Can_17_McmCan_lRxFIFO1Handler              **
**                    (const uint8 HwControllerId,                            **
**                    const Can_17_McmCan_ProcessingType ProcessingType,      **
**                    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr,**
**                    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr)**
**                                                                            **
**  Description      : - This function shall process the reception of message **
**                        in RX FIFO1 objects                                 **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant for different controllers.                   **
**                     Non reentrant for the same controller.                 **
**                                                                            **
**  Parameters (in)  :  HwControllerId - Associated CAN Controller            **
**                      ProcessingType -  Rx processing type                  **
**                      CoreConfigPtr - Pointer to CAN driver configuration   **
**                      CoreGlobalPtr - Pointer to global structure           **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Parameters (in-out) :                                                     **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/

static void Can_17_McmCan_lRxFIFO1Handler(const uint8 HwControllerId,
                      const Can_17_McmCan_ProcessingType ProcessingType,
                      const Can_17_McmCan_CoreConfigType *const CoreConfigPtr,
                      const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr)
{
  /*Can controller node address pointer*/
  volatile Ifx_CAN_N *NodeRegAddressPtr;

  /*RX FIFO processing type*/
  Can_17_McmCan_RxFIFOProcessingType RxFIFOProcessing;

  /*Variable to store RX buffer position*/
  uint8 RxHandleBuffPos;

  /*Flag to traverse through the RX FIFO types*/
  uint8 LoopExitFlag = 0;

  /*FIFO size*/
  uint8 FifoSize = CoreConfigPtr->
                 CanControllerMsgRAMMapConfigPtr[HwControllerId].CanRxFIFO1Size;

  /* Read the exact Node Start address */
  NodeRegAddressPtr = CoreConfigPtr->
                       CanControllerConfigPtr[HwControllerId].CanNodeAddressPtr;

  /*Read the processing type for RX FIFO1*/
  RxFIFOProcessing = CoreConfigPtr->
              CanControllerConfigPtr[HwControllerId].CanRxFIFO1ProcessingConfig;

  /*Check the processing type for the RX FIFO*/
  /* [cover parentID={72E04FBF-C90D-4e3d-862C-2330E1F31774}]
  Check if the processing type requested and the type read are the same?
  [/cover] */
  if ((uint8)RxFIFOProcessing == (uint8)ProcessingType)
  {

    /* Check Received CAN message is lost*/
    /* [cover parentID={41070E70-E13C-4a70-A125-2DFF26D7942F}]
    Check if the recieved CAN message is LOST?
    [/cover] */
    if (NodeRegAddressPtr->IR.B.RF1L != CAN_17_MCMCAN_BIT_CLEAR_VAL)
    {
      #if (CAN_17_MCMCAN_RUNTIME_ERROR_DETECT == STD_ON)
        /*Report RUNTIME error*/
        /* [cover parentID={7FF5D341-BB9F-4b61-9472-A9ADD400F33C}]
            #if (CAN_17_MCMCAN_RUNTIME_ERROR_DETECT == STD_ON)
        Invoke the RUNTIME handler to report CAN_E_DATALOST*/
        (void)Mcal_Wrapper_Det_ReportRuntimeError(CAN_17_MCMCAN_MODULE_ID, 
              CAN_17_MCMCAN_INSTANCE_ID, CAN_17_MCMCAN_SID_RECEIVEHANDLER,
              CAN_17_MCMCAN_E_DATALOST);
      #endif
      NodeRegAddressPtr->IR.U = CAN_17_MCMCAN_RF1L_CLEAR;
    }

    /*Loop till all messages are read in Rx FIFO 1 or read max configured
    messages in FIFO*/
    /* [cover parentID={B3373759-C0B1-46d1-BE89-347889C0721A}]
    Loop till all messages are read in Rx FIFO 1 or read max configured
    messages in FIFO1
    [/cover] */
    while ((NodeRegAddressPtr->RX.F1S.B.F1FL > 0U) && (LoopExitFlag < FifoSize))
    {
      LoopExitFlag++;
      /* a. Read all FIFO slots and acknowledge to free up slots
        b. Notify upper layer */
      /* Read Rx FIFO 0 Get Index */
      RxHandleBuffPos = NodeRegAddressPtr->RX.F1S.B.F1GI;

      /* Invoke data retrieve function */
      /* [cover parentID={7FF5D341-BB9F-4b61-9472-A9ADD400F33C}]
      Invoke data retrieve function
      [/cover] */
      Can_17_McmCan_lRxExtractData(HwControllerId, RxHandleBuffPos,
                          CAN_17_MCMCAN_RX_FIFO1, CoreGlobalPtr, CoreConfigPtr);

      /* Set read Acknowledge of buffer */
      NodeRegAddressPtr->RX.F1A.U = RxHandleBuffPos;
    }
  }
}

/*******************************************************************************
** Traceability   : [cover parentID={FF8CCCB4-401B-40bc-9F6F-4282C645F95F}]   **
**                                                                            **
**  Syntax           : static void Can_17_McmCan_lRxDedicatedHandler          **
**                    (                                                       **
**                     const uint8 HwControllerId,                            **
**                     const Can_17_McmCan_ProcessingType ProcessingType,     **
**                     const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,*
**                     const Can_17_McmCan_CoreConfigType *const CoreConfigPtr**
**                    )                                                       **
**                                                                            **
**  Description      : - This function shall process the reception of message **
**                        in dedicated receive objects                        **
**                                                                            **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant                                              **
**                                                                            **
**  Parameters (in)  : HwControllerId - Associated CAN Controller             **
**                     ProcessingType -  Rx processing type                   **
**                     CoreConfigPtr - Pointer to CAN driver configuration    **
**                     CoreGlobalPtr - Pointer to global structure            **
**  Parameters (in-out) :  none                                               **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
static void Can_17_McmCan_lRxDedicatedHandler(const uint8 HwControllerId,
                      const Can_17_McmCan_ProcessingType ProcessingType,
                      const Can_17_McmCan_CoreConfigType *const CoreConfigPtr,
                      const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr)
{
  /*Can controller node address pointer*/
  volatile Ifx_CAN_N *NodeRegAddressPtr;

  /*New data value from NDAT*/
  uint32 RxNDATValue;

  /*New Data Mask */
  uint32 RxNDATMask;

  /*New data value for NDAT1*/
  uint32 RxNDATValue1;

  /*New data value from NDAT2*/
  uint32 RxNDATValue2;

  /*NDAT1 mask*/
  uint32 RxNDAT1Mask = 0U;

  /*NDAT2 mask*/
  uint32 RxNDAT2Mask = 0U;

  /*RX dedicated mask*/
  uint32 RxDedMask;

  /*RX handle buffer position*/
  uint8 RxHandleBuffPos;

  /*Register set number*/
  uint8 RegSet;

  /* Read the exact Node Start address */
  NodeRegAddressPtr = CoreConfigPtr->
                      CanControllerConfigPtr[HwControllerId].CanNodeAddressPtr;

  /*Read the value of NDAT1 and NDAT2 registers*/
  RxNDATValue1 = NodeRegAddressPtr->NDAT1.U;

  RxNDATValue2 = NodeRegAddressPtr->NDAT2.U;

  /*Check the processing type and fill the masks*/
  /* [cover parentID={02BCB76D-D283-414e-B19B-7A3A60E8B74B}]
  Check if the processing type is POLLING
  [/cover] */
  if (ProcessingType == CAN_17_MCMCAN_POLLING)
  {
    RxNDAT1Mask = CoreConfigPtr->
                  CanControllerConfigPtr[HwControllerId].CanHrhNDAT1PollingMask;

    RxNDAT2Mask = CoreConfigPtr->
                  CanControllerConfigPtr[HwControllerId].CanHrhNDAT2PollingMask;
  }
  /* [cover parentID={5F7512C3-83A8-4a65-8FEA-434B8E4A94DE}]
  Check if the type is INTERRUPT
  [/cover] */
  else
  {
    RxNDAT1Mask = ~(CoreConfigPtr->
                 CanControllerConfigPtr[HwControllerId].CanHrhNDAT1PollingMask);

    RxNDAT2Mask = ~(CoreConfigPtr->
                 CanControllerConfigPtr[HwControllerId].CanHrhNDAT2PollingMask);
  }

  /* Set with first bit position*/
  RxHandleBuffPos = 0U;

  /* Read first NDAT1 buffer value */
  RxNDATValue = RxNDATValue1;

  RxNDATMask = RxNDAT1Mask;

  /*Loop to read the data registers*/
  for (RegSet = 0U; RegSet < CAN_17_MCMCAN_NDATREGNUM; RegSet++)
  {
    /* Set mask value */
    RxDedMask = 1U;

    /* Check any one of the Rx dedicated buffer is received with new
    data */
    while (0U != RxNDATValue)
    {
      RxNDATValue = (RxNDATValue & RxNDATMask);

      /* Check buffer with mask position is received data or not */
      /* [cover parentID={0FC18423-56F6-4489-9C34-08BF673A802D}]
      Check if the buffer mask position is recieve data or not
      [/cover] */
      if (0U != (RxNDATValue & RxDedMask))
      {
        /* Invoke Can_17_McmCan_lRxExtractData function for retrieve data from
        message */
        Can_17_McmCan_lRxExtractData(HwControllerId, RxHandleBuffPos,
                                      CAN_17_MCMCAN_RX_DED_BUFFER,
                                      CoreGlobalPtr, CoreConfigPtr);

        /* Clear the set bit position of NDAT Reg value */
        RxNDATValue = RxNDATValue & (~RxDedMask);

        /* Clear NDAT Register for receive new message */
        /* [cover parentID={1515CC39-ECF0-41b9-A8B7-00C21386E9D1}]
        Is the register NDAT1?
        [/cover] */
        if (RegSet == 0U)
        {
          NodeRegAddressPtr->NDAT1.U = RxDedMask;
        }
        /* [cover parentID={3D84D200-F673-426e-A5AC-072E4A9AE4BD}]
        Is the register NDAT2?
        [/cover] */
        else
        {
          NodeRegAddressPtr->NDAT2.U = RxDedMask;
        }
      }

      /* Set mask for check next buffer status */
      RxDedMask = RxDedMask << 1U;

      /* Increment bit position */
      RxHandleBuffPos++;
    }
    /* After completion of read NDAT1 load NDAT value with NDAT2 register
        value */
    RxNDATValue = RxNDATValue2;

    RxNDATMask = RxNDAT2Mask;

    /* Set Buffer position from value 32 for NDAT2 */
    RxHandleBuffPos = CAN_17_MCMCAN_BUFFER_POS;
  }
}
#endif /* #if(((CAN_17_MCMCAN_RX_POLLING_PROCESSING == STD_ON)&& \
  (CAN_17_MCMCAN_RX_MULTI_PERIODS_SUPPORT == STD_OFF))||         \
  (CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||            \
  (CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON)||                \
  ((CAN_17_MCMCAN_WU_POLLING_PROCESSING == STD_ON) &&            \
  (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON))) */

#if ((CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING == STD_ON) || \
     (CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) ||     \
     ((CAN_17_MCMCAN_TX_POLLING_PROCESSING == STD_ON) &&  \
(CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_OFF)))
/*******************************************************************************
** Traceability     : [cover parentID={BC51BE45-5022-41aa-B8D7-131F161BD213}] **
**  Syntax           : static void Can_17_McmCan_lTxEventHandler              **
**                    (                                                       **
**                      const uint8 HwControllerId,                           **
**                     const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,*
**                      const Can_17_McmCan_ProcessingType ProcessingType,    **
**                      const Can_17_McmCan_CoreConfigType *const CoreConfigPtr*
**                    )                                                       **
**                                                                            **
**  Description      : - This function shall read all the Tx event FIFO       **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant for different controllers.                   **
**                     Non reentrant for the same controller.                 **
**                                                                            **
**  Parameters (in)  : HwControllerId - Associated CAN Controller             **
**                     CoreConfigPtr - Pointer to CAN driver configuration    **
**                     ProcessingType -  Tx processing type                   **
**                     CoreGlobalPtr - Pointer to global structure            **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
static void Can_17_McmCan_lTxEventHandler(const uint8 HwControllerId,
    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,
    const Can_17_McmCan_ProcessingType ProcessingType,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr)
{
  /*Can controller node address pointer*/
  volatile Ifx_CAN_N *NodeRegAddressPtr;

  #if (CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON)
  /*TX event structure*/
  volatile const Ifx_CAN_TXEVENT *TxEvntReadData;

  /*Message RAM configuration structure*/
  const Can_17_McmCan_ControllerMsgRAMConfigType *MsgRamCfgPtr;

  /*TX event FIFO start address*/
  uint32 TxEvntFIFOstartAddr;

  /*TX event FIFO real address*/
  uint32 TxEvntFIFORealAddr;

  /*TX event FIFO get index*/
  uint32 TxEvntFIFOGetIndex;

  /*TX event handle index*/
  Can_HwHandleType TxHandleIndx;

  /*TX event fill level*/
  uint8 TxEvntFillLvlVal;

  /*Flag to traverse through the events*/
  uint8 LoopExitCounter;

  /*Flag to traverse through the events in pending queue*/
  uint8 LoopCounter;

  /*SW object index*/
  uint16 SwObjIndx;

  /*Expected low object index*/
  uint16 ExpSwObjIndxLow;

  /*Expected high object index*/
  uint16 ExpSwObjIndxHigh;

  /*Index to traverse through loop for pending queue*/
  sint16 PendingQueueLoopIndex;

  /*Current pending queue index*/
  uint16 PendingQueueIndex;

  /*Index to traverse through loop for pending queue*/
  uint16 LoopIndex;

  /*TX slot index*/
  uint32 TxSlotIndex;

  /*PDU handle to pass to upper layer*/
  PduIdType pduHandle;

  /*TX polling object filter*/
  uint32 TxPollingObjectFilter;

  /* Set pointer variable with Message RAM Configuration structure */
  MsgRamCfgPtr = CoreConfigPtr->CanControllerMsgRAMMapConfigPtr;

  #endif /* #if (CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) */

  /* Read the exact Node Start address */
  NodeRegAddressPtr =
        CoreConfigPtr->CanControllerConfigPtr[HwControllerId].CanNodeAddressPtr;

  /*Check if TX event is FULL*/
  /* [cover parentID={7F23492C-21EE-4c9b-A457-5502B0BDB7FE}]
  Is TX event FULL?
  [/cover] */
  if (CAN_17_MCMCAN_BIT_CLEAR_VAL != NodeRegAddressPtr->IR.B.TEFL)
  {
      #if (CAN_17_MCMCAN_RUNTIME_ERROR_DETECT == STD_ON)
      /*Raise a RUNTIME error if DATA is lost*/
     /* [cover parentID={DD29CA7D-839D-47b9-82AB-0F817BC75A26}]
     Invoke function to report data lost error
     [/cover] */
      (void)Mcal_Wrapper_Det_ReportRuntimeError(CAN_17_MCMCAN_MODULE_ID,
            CAN_17_MCMCAN_INSTANCE_ID, CAN_17_MCMCAN_SID_TRANSMITHANDLER,
            CAN_17_MCMCAN_E_DATALOST);
      #endif
      /* Clear TEFN and TEFL flags as well if SET */
      NodeRegAddressPtr->IR.U = CAN_17_MCMCAN_TEFF_TEFL_CLEAR;
  }
  /* [cover parentID={BAE23875-25AD-4a5b-ADE0-982C41745D99}]
  TX Mixed processing is ON
  [/cover] */
  #if (CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON)
  /* Set Tx Event FIFO Start Address */
  TxEvntFIFOstartAddr = MsgRamCfgPtr[HwControllerId].
                       CanControllerMsgRAMMap[CAN_17_MCMCAN_EFSA];

  /* Set safety loop exit flag with value zero */
  LoopExitCounter = 0U;

  /* Read Fill Level value */
  TxEvntFillLvlVal = NodeRegAddressPtr->TX.EFS.B.EFFL;

  /* If controller is configured in MIXED mode */
  /* [cover parentID={6EFEABE0-1EE9-4c2a-A790-88DDE77B25A4}]
  Is the controller configured in mixed mode?
  [/cover] */
  if(CAN_17_MCMCAN_MIXED == CoreConfigPtr->
                      CanEventHandlingConfigPtr[HwControllerId].CanTxProcessing)
  {
    /* If processing mode requested is INTERRUPT */
    /* [cover parentID={2941846B-0637-4838-8E4A-F2D277C4261C}]
    Is the processing mode requested INTERRUPT
    [/cover] */
    if (ProcessingType == CAN_17_MCMCAN_INTERRUPT)
    {
      /* Read the pollingobjectfilter */
      TxPollingObjectFilter = CoreConfigPtr->
               CanControllerConfigPtr[HwControllerId].CanTxPollingObjectMask;

      while ((0U != TxEvntFillLvlVal) &&
            (CAN_17_MCMCAN_NOOF_TX_HW_BUFF_AVAILABLE > LoopExitCounter))
      {

        /* Read TxEvent buffer index */
        TxEvntFIFOGetIndex = NodeRegAddressPtr->TX.EFS.B.EFGI;

        /* Set Real Event FIFO element address */
        TxEvntFIFORealAddr = TxEvntFIFOstartAddr + (TxEvntFIFOGetIndex *
                            (uint32)CAN_17_MCMCAN_TXEVENTFIFO_ADDR_VAL);

        /* Load EventFIFO element address */
        /* MISRA2012_RULE_11_6_JUSTIFICATION: The pointer cast is used to
        cast the address to the event elements structure type for
        accessing RAM area */
        /* MISRA2012_RULE_11_4_JUSTIFICATION: Memory address is generated as a
        numerical value, it is accessed as a pointer to the RAM address.
        Hence an explicit typecast from numerical to pointer. */
        TxEvntReadData = (volatile Ifx_CAN_TXEVENT *)TxEvntFIFORealAddr;

        /* Read Message Marker */
        TxHandleIndx = (Can_HwHandleType)TxEvntReadData->E1.B.MM;

        /* Calculate Sw Obj Handle index */
        SwObjIndx = (uint16)((HwControllerId *
                              CAN_17_MCMCAN_NOOF_TX_HW_BUFF_AVAILABLE) +
                              TxHandleIndx);

        /* Release Tx buffer before notification by copying the id */
        pduHandle = CoreGlobalPtr->CanSwObjectHandlePtr[SwObjIndx];

        TxSlotIndex = ((uint32)1U << TxHandleIndx);

        /* Check if the hw object is set for Polling */
        if (TxSlotIndex == (TxPollingObjectFilter & TxSlotIndex))
        {
          /* [cover parentID={859EA0AC-2801-4215-B0C6-AE8C074D8751}]
          Enter critical section
          [/cover] */
          SchM_Enter_Can_17_McmCan_CanWrMO();

          /* current pending queue index */
          PendingQueueIndex =
                       CoreGlobalPtr->CanTxSwQueuePtr->CanTxSwPendingQueueIndex;

          /* Add to the sw queue to be processed by POLLING method */
          CoreGlobalPtr->CanTxSwQueuePtr->
                          CanTxSwPendingQueuePtr[PendingQueueIndex] = SwObjIndx;

          /* increment the pending queue index */
          CoreGlobalPtr->CanTxSwQueuePtr->CanTxSwPendingQueueIndex++;

          /* [cover parentID={401F0491-C754-4a6b-B07C-CF87FC86AC84}]
          Exit critical section
          [/cover] */
          SchM_Exit_Can_17_McmCan_CanWrMO();

          /* Acknowledge shall set to free the Tx Event FIFO */
          NodeRegAddressPtr->TX.EFA.B.EFAI = (uint8)TxEvntFIFOGetIndex;
        }
        /* Object configured as Interrupt */
        else
        {

          /* Check if this element belong to configured Tx objects */
          /* [cover parentID={0B3760BF-BC1B-4422-B514-1CC6DCE6E141}]
          Check if this element belong to configured Tx objects?
          [/cover] */
          if((TxSlotIndex & CoreGlobalPtr->BackupCanTxMaskPtr[HwControllerId])
                                                             == TxSlotIndex)
          {
            /* Enter Critical Section */
            /* [cover parentID={40418F4D-2AB1-46d4-96D3-E8EA21231EA9}]
            Enter critical section
            [/cover] */
            SchM_Enter_Can_17_McmCan_CanWrMO();

            /* Release Transmit object */
            CoreGlobalPtr->CanTxMaskPtr[HwControllerId] |= TxSlotIndex;

            /* Exit Critical Section */
            /* [cover parentID={E1D3E8F1-394F-4efa-B896-E6771C50EFB5}]
            Exit critical section
            [/cover] */
            SchM_Exit_Can_17_McmCan_CanWrMO();
          }

          /* Acknowledge shall set to free the Tx Event FIFO */
          NodeRegAddressPtr->TX.EFA.B.EFAI = (uint8)TxEvntFIFOGetIndex;

          /*Call Transmission confirmation to upper-layer with L-PDU handle*/
          CanIf_TxConfirmation(pduHandle);
        }
        /* Increment exit loop condition for safety */
        LoopExitCounter++;

        /* Read Fill Level value */
        TxEvntFillLvlVal = NodeRegAddressPtr->TX.EFS.B.EFFL;
      }
    }
    /* ProcessingType is POLLING */
    else
    {
      /* current pending queue index */
      PendingQueueIndex = CoreGlobalPtr->
                          CanTxSwQueuePtr->CanTxSwPendingQueueIndex;

      PendingQueueLoopIndex = 0;

      /* Loop through the pending queue */
      /* [cover parentID={C51760C3-05B2-49a8-B91E-8440876D8807}]
      Set with Exact PduHandle Stored Index value
      [/cover] */
      for (LoopCounter = 0U; LoopCounter < PendingQueueIndex; LoopCounter++)
      {
        /* read the element in queue */
        SwObjIndx = CoreGlobalPtr->CanTxSwQueuePtr->
                    CanTxSwPendingQueuePtr[PendingQueueLoopIndex];

        /* low swobjindx for current controller */
        ExpSwObjIndxLow = (uint16)((HwControllerId *
                                    CAN_17_MCMCAN_NOOF_TX_HW_BUFF_AVAILABLE) +
                                    0U);

        /* high swobjindx for current controller */
        ExpSwObjIndxHigh = (uint16)((HwControllerId *
                                     CAN_17_MCMCAN_NOOF_TX_HW_BUFF_AVAILABLE) +
                                     CAN_17_MCMCAN_NOOF_TX_HW_BUFF_AVAILABLE);

        /* Check the element belong to the same controller */
        /* [cover parentID={B0302F79-81AF-4ff6-8145-AE45B9F6B536}]
        Check the element belong to the same controller?
        [/cover] */
        if ((SwObjIndx < ExpSwObjIndxHigh) && (SwObjIndx >= ExpSwObjIndxLow))
        {
          /* Read the PduHandle from sw queue */
          pduHandle = CoreGlobalPtr->CanSwObjectHandlePtr[SwObjIndx];

          /* Calculate TxSlotIndex */
          TxSlotIndex = SwObjIndx - (HwControllerId *
                                       CAN_17_MCMCAN_NOOF_TX_HW_BUFF_AVAILABLE);

          /* Check if this element belong to configured Tx objects */
          /* [cover parentID={4862732C-C161-4b23-9FD0-E67BDADAEC30}]
          Check if this element belong to configured Tx objects?
          [/cover] */
          if ((TxSlotIndex & CoreGlobalPtr->
                             BackupCanTxMaskPtr[HwControllerId]) == TxSlotIndex)
          {
            /* Enter Critical Section */
            SchM_Enter_Can_17_McmCan_CanWrMO();

            /* Clear sw queue for that entry */
            for (LoopIndex = (uint16)PendingQueueLoopIndex;
                              LoopIndex < PendingQueueIndex;
                              LoopIndex++)
            {
              CoreGlobalPtr->CanTxSwQueuePtr->
                  CanTxSwPendingQueuePtr[LoopIndex] =
              CoreGlobalPtr->CanTxSwQueuePtr->
                  CanTxSwPendingQueuePtr[LoopIndex + (uint16)1U];

              CoreGlobalPtr->CanTxSwQueuePtr->
                  CanTxSwPendingQueuePtr[LoopIndex + (uint16)1U] =
                                     CAN_17_MCMCAN_MAX_SWOBJECT_INDEX;
            }

            /* decrement the pending queue index */
            CoreGlobalPtr->CanTxSwQueuePtr->CanTxSwPendingQueueIndex--;

            /* Release Transmit object */
            CoreGlobalPtr->CanTxMaskPtr[HwControllerId] |= TxSlotIndex;

            /* Exit Critical Section */
            SchM_Exit_Can_17_McmCan_CanWrMO();
          }
          PendingQueueLoopIndex--;
          /* Set with Exact PduHandle Stored Index value */
          /* [cover parentID={B82A1B7E-03F0-4111-B4A3-704883E67EB5}]
          Call Transmission confirmation to upper-layer with L-PDU handle
          [/cover] */
          CanIf_TxConfirmation(pduHandle);
        }
      PendingQueueLoopIndex++;
      }
    }
  }
  /* Controller is not configured as MIXED mode Tx processing*/
  /* [cover parentID={CD1FC66A-0D93-4df8-AFB5-672C1BB80AC1}]
   Controller is not configured as MIXED mode Tx processing
   [/cover] */
  else
  #else
  UNUSED_PARAMETER(ProcessingType);
  #endif /* #if (CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) */
  {
    Can_17_McmCan_lTxEventProcessingHandler(HwControllerId, CoreGlobalPtr,
                                                                 CoreConfigPtr);
  }
}

/*******************************************************************************
** Traceability     : [cover parentID={C9569721-5947-442b-8001-187D06F8BDA3}] **
**                     static void Can_17_McmCan_lTxEventProcessingHandler    **
**                     (const uint8 HwControllerId,                           **
                       const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,*
                       const Can_17_McmCan_CoreConfigType                      *
                                             *const CoreConfigPtr)            **
**                                                                            **
**  Description      : - This function shall read all the Tx event FIFO for   **
**                      MIXED mode processing                                 **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant                                              **
**                                                                            **
**  Parameters (in)  : HwControllerId - Associated CAN Controller             **
**                     CoreGlobalPtr - Pointer to global structure            **
**                     CoreConfigPtr - Pointer to CAN driver configuration    **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
static void Can_17_McmCan_lTxEventProcessingHandler(const uint8 HwControllerId,
                       const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,
                       const Can_17_McmCan_CoreConfigType *const CoreConfigPtr)
{
   /*TX event FIFO start address*/
  uint32 TxEvntFIFOstartAddr;

  /*Message RAM configuration structure*/
  const Can_17_McmCan_ControllerMsgRAMConfigType *MsgRamCfgPtr;

  /*TX event FIFO real address*/
  uint32 TxEvntFIFORealAddr;

  /*TX event FIFO get index*/
  uint32 TxEvntFIFOGetIndex;

  /*TX event handle index*/
  Can_HwHandleType TxHandleIndx;

  /*TX event fill level*/
  uint8 TxEvntFillLvlVal;

  /*SW object index*/
  uint16 SwObjIndx;

  /*TX slot index*/
  uint32 TxSlotIndex;

  /*PDU handle to pass to upper layer*/
  PduIdType pduHandle;

    /*TX event structure*/
  volatile const Ifx_CAN_TXEVENT *TxEvntReadData;

    /*Can controller node address pointer*/
  volatile Ifx_CAN_N *NodeRegAddressPtr;

  /*Flag to traverse through the events*/
  uint8 LoopExitCounter = 0U;

  /* Read the exact Node Start address */
  NodeRegAddressPtr = CoreConfigPtr->
                      CanControllerConfigPtr[HwControllerId].CanNodeAddressPtr;

  /* Set pointer variable with Message RAM Configuration structure */
  MsgRamCfgPtr = CoreConfigPtr->CanControllerMsgRAMMapConfigPtr;

    /* Set Tx Event FIFO Start Address */
  TxEvntFIFOstartAddr = MsgRamCfgPtr[HwControllerId].
                       CanControllerMsgRAMMap[CAN_17_MCMCAN_EFSA];

  /* Read Fill Level value */
  TxEvntFillLvlVal = NodeRegAddressPtr->TX.EFS.B.EFFL;

  LoopExitCounter = 0U;

  /*Read Tx event FIFO register for read No of stored Events and
    check if it exceeds the range */
  while ((0U != TxEvntFillLvlVal) &&
          (CAN_17_MCMCAN_NOOF_TX_HW_BUFF_AVAILABLE > LoopExitCounter))
    {
      /* Read TxEvent buffer index */
      TxEvntFIFOGetIndex = NodeRegAddressPtr->TX.EFS.B.EFGI;

      /* Set Real Event FIFO element address */
      TxEvntFIFORealAddr = TxEvntFIFOstartAddr + (TxEvntFIFOGetIndex *
                           (uint32)CAN_17_MCMCAN_TXEVENTFIFO_ADDR_VAL);

      /* Load EventFIFO element address */
      /* MISRA2012_RULE_11_6_JUSTIFICATION: The pointer cast is used to
      cast the address to the event elements structure type for
      accessing RAM area */
      /* MISRA2012_RULE_11_4_JUSTIFICATION: Memory address is generated as a
      numerical value, it is accessed as a pointer to the RAM address.
      Hence an explicit typecast from numerical to pointer. */
    TxEvntReadData = (volatile Ifx_CAN_TXEVENT *)TxEvntFIFORealAddr;

      /* Read Message Marker */
    TxHandleIndx = (Can_HwHandleType)TxEvntReadData->E1.B.MM;

      /* Calculate Sw Obj Handle index */
      SwObjIndx = (uint16)((HwControllerId *
                          CAN_17_MCMCAN_NOOF_TX_HW_BUFF_AVAILABLE) +
                         TxHandleIndx);

      /* Release Tx buffer before notification by copying the id */
      pduHandle = CoreGlobalPtr->CanSwObjectHandlePtr[SwObjIndx];

      TxSlotIndex = ((uint32)1U << TxHandleIndx);

      /* Check if this element belong to configured Tx objects */
      /* [cover parentID={BDBF9902-E5FA-4adf-8C3A-DE77C6227361}]
      Check if this element belong to configured Tx objects
      [/cover] */
    if ((TxSlotIndex & CoreGlobalPtr->BackupCanTxMaskPtr[HwControllerId]) ==
                                                                    TxSlotIndex)
      {

        /* Enter Critical Section */
        /* [cover parentID={1E89BD02-5F05-4efd-B640-5711E15E7AEB}]
        Enter Critical Section
        [/cover] */
        SchM_Enter_Can_17_McmCan_CanWrMO();

        /* Release Transmit object */
        CoreGlobalPtr->CanTxMaskPtr[HwControllerId] |= TxSlotIndex;

        /* Exit Critical Section */
        /* [cover parentID={8032601C-6290-4a55-9C69-BA4A1E973C0A}]
        Exit critical section
        [/cover] */
        SchM_Exit_Can_17_McmCan_CanWrMO();
      }

      /* Acknowledge shall set to free the Tx Event FIFO */
    NodeRegAddressPtr->TX.EFA.B.EFAI = (uint8)TxEvntFIFOGetIndex;

      /*Call Transmission confirmation to upper-layer with L-PDU handle*/
      CanIf_TxConfirmation(pduHandle);

      /* Increment exit loop condition for safety */
      LoopExitCounter++;

      /* Read Fill Level value */
    TxEvntFillLvlVal = NodeRegAddressPtr->TX.EFS.B.EFFL;
    }
}

#endif /* #if((CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING == STD_ON)|| \
(CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) ||                  \
((CAN_17_MCMCAN_TX_POLLING_PROCESSING == STD_ON)&&                \
(CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_OFF))) */

/*******************************************************************************
** Traceability   : [cover parentID={C5F1A7D3-7724-40d7-96B8-040E817345EE}]   **
**                                                                            **
**  Syntax           : static void Can_17_McmCan_lBusOffHandler               **
**                    (                                                       **
**                      const uint8 HwControllerId,                           **
**                      Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,    **
**                      const Can_17_McmCan_CoreConfigType *const CoreConfigPtr*
**                    )                                                       **
**                                                                            **
** Description    :This function will check the Busoff status of requested    **
**                 controller, if detected as in Busoff mode then will        **
**                 initiate for the cancelation of the entire pending Tx      **
**                 request, and will be set the controller mode state in to   **
**                 STOP.                                                      **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant                                              **
**                                                                            **
**  Parameters (in)  : HwControllerId - 0 to N-1, where N is the number of    **
**                     CAN controllers in the considered device CAN controller**
**                     Id in hardware,                                        **
**                     CoreGlobalPtr - Core specific global variable holding  **
**                     controller states                                      **
**                     CoreConfigPtr - Core specific controller configuration **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Parameters (in-out) : none                                                **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
static void Can_17_McmCan_lBusOffHandler(const uint8 HwControllerId,
    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr)
{
  const volatile Ifx_CAN_N *NodeRegAddressPtr;
  Ifx_UReg_32Bit TempInitStatus;
  uint8 LogicalHwControllerId;

  /* Read the exact Node Start address */
  NodeRegAddressPtr = CoreConfigPtr->CanControllerConfigPtr[HwControllerId].
                      CanNodeAddressPtr;

  /* Read Controller mode status */
  TempInitStatus = NodeRegAddressPtr->CCCR.B.INIT;

  /* Check the M_CAN is in BusOff state or not */
  /* Note: Bus off notification to application will be provided only once   */
  /* [cover parentID={D5432A7A-C352-4415-9D98-2EF0777415BC}]
  Check if INIT bit in initialization state and Controller in Bus OFF state,and,
  controller is in STARTED state?
  [/cover] */
  if ((CAN_17_MCMCAN_BIT_SET_VAL == NodeRegAddressPtr->PSR.B.BO) &&
      (CAN_17_MCMCAN_BIT_SET_VAL == TempInitStatus) &&
      (CoreGlobalPtr->
      CanControllerModePtr[HwControllerId] == CAN_17_MCMCAN_STARTED))
  {

    /* invoke function to cancel all pending request */
    /* [cover parentID={E538497B-FAF6-4ab2-B3BE-D071E5CB386D}]
    Invoke function to cancel all pending request
    [/cover] */
    Can_17_McmCan_lCancelPendingTx(HwControllerId,
                                   CoreGlobalPtr, CoreConfigPtr);

    /* Set controller mode with STOP state */
    /* [cover parentID={F283AA67-B594-4280-A8F3-9625677BA78E}]
    Set Controller mode to STOPPED state
    [/cover] */
    CoreGlobalPtr->CanControllerModePtr[HwControllerId] = CAN_17_MCMCAN_STOPPED;


    LogicalHwControllerId =
                        CoreConfigPtr->CanControllerIndexingPtr[HwControllerId];

    /* Call Bus_Off notification function to notify upper layer */
    /* [cover parentID={838455CD-FCFA-45e0-B4C7-8FBEBACB92A0}]
    Call Bus_Off notification function to notify upper layer
    [/cover] */
    CanIf_ControllerBusOff(LogicalHwControllerId);
  }
}

#if (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={C5B59700-2570-42ed-8581-748B30C384D8}]   **
**                                                                            **
**  Syntax          :static void Can_17_McmCan_lTxPeriodPollingHandler(       **
**                  const uint8 CtrlIndex,                                    **
**                  const uint8 HthRefPeriods,                                **
**                  const Can_17_McmCan_CoreConfigType *const ConfigPtr,      **
**                  const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr)  **
**                                                                            **
**  Description      :  Function used to handle Tx event queue                **
**                      for multiple write period in POLLING mode             **
**                                                                            **
**                                                                            **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant                                              **
**                                                                            **
**  Parameters (in)  : CtrlIndex - Controller index to be processed           **
**                     HthRefPeriods - The write operation cyclic period      **
**                                  configuration index                       **
**                     ConfigPtr - Pointer to CAN driver configuration        **
**                     CoreGlobalPtr - Pointer to global structure            **
**                                                                            **
**  Parameters (in-out) : none                                                **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
static void Can_17_McmCan_lTxPeriodPollingHandler(const uint8 CtrlIndex,
            const uint8 HthRefPeriods,
            const Can_17_McmCan_CoreConfigType *const ConfigPtr,
            const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr)
{
  /*TX handle index*/
  uint8 TxHandleIndx;

  /*SW object index*/
  uint16 SwObjIndx;

  /*Retrun value to indicate if SW object found*/
  Std_ReturnType SwObjFound;

  /*TX event FIFO start address*/
  uint32 TxEvntFIFOstartAddr;

  /*Current pending queue index*/
  uint16 PendingQueueIndex;

  /*TX event FIFO real address*/
  uint32 TxEvntFIFORealAddr;

  /*TX event FIFO get index*/
  uint32 TxEvntFIFOGetIndex;

  /*TX event fill level value*/
  uint8 TxEvntFillLvlVal;

  /*Flag for loop exeit condition*/
  uint8 LoopExitFlag;

  /*TX event data read*/
  volatile const Ifx_CAN_TXEVENT *TxEvntReadData;

  /*Can controller node address pointer*/
  volatile Ifx_CAN_N *NodeRegAddressPtr;

  /*Pointer to message RAM configuration*/
  const Can_17_McmCan_ControllerMsgRAMConfigType *MsgRamCfgPtr;

  /* Set pointer variable with Message RAM Configuration structure */
  MsgRamCfgPtr = ConfigPtr->CanControllerMsgRAMMapConfigPtr;

  /* Check if the controller is configured as POLLING */
  /* [cover parentID={D31B1D5C-153F-45f7-80B5-CFBB888F97EF}]
  Check if POLLING?
  [/cover] */
  if (CAN_17_MCMCAN_POLLING ==
      ConfigPtr->CanEventHandlingConfigPtr[CtrlIndex].CanTxProcessing)
  {
    /* Read the exact Node Start address */
    NodeRegAddressPtr = ConfigPtr->
                            CanControllerConfigPtr[CtrlIndex].CanNodeAddressPtr;

    /* Set Tx Event FIFO Start Address */
    TxEvntFIFOstartAddr = MsgRamCfgPtr[CtrlIndex].
                          CanControllerMsgRAMMap[CAN_17_MCMCAN_EFSA];

    /*Check if TEFL is set*/
    /* [cover parentID={862539E4-5FEF-4b77-9AA8-7C2E6A14CCE6}]
    Check if TEFL is set
    [/cover] */
    if (CAN_17_MCMCAN_BIT_CLEAR_VAL != NodeRegAddressPtr->IR.B.TEFL)
    {
      #if (CAN_17_MCMCAN_RUNTIME_ERROR_DETECT == STD_ON)
      /*Raise a RUNTIME error if DATA is lost*/
      /* [cover parentID={BADCCE5A-30C1-42e7-923D-DDAB5FBDBA2E}]
      Raise a RUNTIME error if DATA is lost
      [/cover] */
      (void)Mcal_Wrapper_Det_ReportRuntimeError(CAN_17_MCMCAN_MODULE_ID, 
            CAN_17_MCMCAN_INSTANCE_ID, CAN_17_MCMCAN_SID_TRANSMITHANDLER,
            CAN_17_MCMCAN_E_DATALOST);
      #endif
      /* Clear TEFN and TEFL flags as well if SET */
      NodeRegAddressPtr->IR.U = CAN_17_MCMCAN_TEFF_TEFL_CLEAR;
    }

    /* Set safety loop exit flag with value zero */
    LoopExitFlag = 0U;

    /* Read Fill Level value */
    TxEvntFillLvlVal = NodeRegAddressPtr->TX.EFS.B.EFFL;

    /* [cover parentID={51FC334D-D7A8-4c9b-BC79-93FE5B20DA36}]
    Loop through all the available hardware buffers
    [/cover] */
    while ((0U != TxEvntFillLvlVal) &&
          (CAN_17_MCMCAN_NOOF_TX_HW_BUFF_AVAILABLE > LoopExitFlag))
    {
      /* Read TxEvent buffer index */
      TxEvntFIFOGetIndex = NodeRegAddressPtr->TX.EFS.B.EFGI;

      /* Set Real Event FIFO element address */
      TxEvntFIFORealAddr = TxEvntFIFOstartAddr +
                            (TxEvntFIFOGetIndex *
                            (uint32)CAN_17_MCMCAN_TXEVENTFIFO_ADDR_VAL);

      /* Load EventFIFO element address */
      /* MISRA2012_RULE_11_6_JUSTIFICATION: The pointer cast is used to
      cast the address to the event elements structure type for
      accessing RAM area */
      /* MISRA2012_RULE_11_4_JUSTIFICATION: Memory address is generated as a
      numerical value, it is accessed as a pointer to the RAM address.
      Hence an explicit typecast from numerical to pointer. */
      TxEvntReadData = (volatile Ifx_CAN_TXEVENT *)TxEvntFIFORealAddr;

      /* Read Message Marker */
      TxHandleIndx = (uint8)(TxEvntReadData->E1.B.MM);

      /* Calculate Sw Obj Handle index */
      SwObjIndx = (uint16)(CtrlIndex *
                            CAN_17_MCMCAN_NOOF_TX_HW_BUFF_AVAILABLE) +
                            TxHandleIndx;

      SwObjFound = Can_17_McmCan_lPeriodCheckSwHandle(CtrlIndex,
                    SwObjIndx, HthRefPeriods, ConfigPtr, CoreGlobalPtr);

      /*Check if Sw Obj Handle index is valid ?*/
      /* [cover parentID={095C0AA0-F583-42c7-828D-5358172E3919}]
      Check if Sw Obj Handle index is valid ?
      [/cover] */
      if (E_NOT_OK == SwObjFound)
      {
          /* [cover parentID={101FE09B-91DA-4171-AF2E-3F09A8CD4C8A}]
          Enter critical section
          [/cover] */
          SchM_Enter_Can_17_McmCan_CanWrMO();

          /* current pending queue index */
          PendingQueueIndex =
                       CoreGlobalPtr->CanTxSwQueuePtr->CanTxSwPendingQueueIndex;

          /* Add to the sw queue to be processed by POLLING method */
          CoreGlobalPtr->CanTxSwQueuePtr->
                          CanTxSwPendingQueuePtr[PendingQueueIndex] = SwObjIndx;

          /* increment the pending queue index */
          CoreGlobalPtr->CanTxSwQueuePtr->CanTxSwPendingQueueIndex++;

          /* [cover parentID={FCF338A9-3AEE-4357-BF67-33C89920291C}]
          Exit critical section
          [/cover] */
          SchM_Exit_Can_17_McmCan_CanWrMO();
      }

      /* Acknowledge shall set to free the Tx Event FIFO */
      NodeRegAddressPtr->TX.EFA.B.EFAI = (uint8)TxEvntFIFOGetIndex;

      /* Increment exit loop condition for safety */
      LoopExitFlag++;

      /* Read Fill Level value */
      TxEvntFillLvlVal = NodeRegAddressPtr->TX.EFS.B.EFFL;
    }
  }
}

/*******************************************************************************
** Traceability   : [cover parentID={8AF91135-3E29-4afe-911C-23E827A3053F}]   **
**  Syntax           :  void Can_17_McmCan_lTxPeriodHandler                   **
**                    (                                                       **
**                      const uint8 HthRefPeriods                             **
**                    )                                                       **
**                                                                            **
**  Description      :  Function used for handling Tx confirmation process    **
**                      with multiple write period                            **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Non Reentrant                                          **
**                                                                            **
**  Parameters (in)  : HthRefPeriods - The write operation cyclic period      **
**                    configuration index                                     **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
void Can_17_McmCan_lTxPeriodHandler(const uint8 HthRefPeriods)
{

  /* Variable holding the core index value */
  uint8 CoreIndex;

  /* Det check status */
  Std_ReturnType ApiStatus = E_NOT_OK;

  /*Retrun value to indicate if SW object found*/
  Std_ReturnType SwObjFound;

  /*Pointer to the core state structure*/
  const Can_17_McmCan_CoreGlobalType *CoreGlobalPtr;

  /*Poiner to CAN config structure*/
  const Can_17_McmCan_CoreConfigType *ConfigPtr;

  /*Controller index*/
  uint8 CtrlIndex;

  /*SW object index*/
  uint16 SwObjIndx;

  /*Index to traverse through loop for pending queue*/
  sint16 PendingQueueLoopIndex;

  /*Current pending queue index*/
  uint16 PendingQueueIndex;

  /*Flag to traverse through the events in pending queue*/
  uint8 LoopCounter;

  /*Index to traverse through loop for pending queue*/
  uint16 loopIndex;

  /* Get core id which is executing currently */
  CoreIndex = CAN_17_MCMCAN_GETCOREINDEX;

  /*Expected init status*/
  uint32 ExpInitStatus;

  /* Check if CAN driver is initialized */
  ExpInitStatus = (Can_17_McmCan_InitStatus >> ((uint32)CoreIndex *
                          (uint32)CAN_17_MCMCAN_INIT_STATUS_SIZE)) & 1U;

  /* [cover parentID={92FFCD78-CED4-49a5-9703-312D52363FD6}]
  Is the driver initialized?
  [/cover] */

  if ((uint32)CAN_17_MCMCAN_DRV_READY == ExpInitStatus)
  {
    /*Check if ref period is configured for current core and Status is OK*/
    /* [cover parentID={20BD2FAC-8864-420e-8B8A-186261C0E038}]
    Check if ref period is configured for current core and Status is OK?
    [/cover] */
    if ((CAN_17_MCMCAN_NO_HOH_VAL ==
                  Can_17_McmCan_kGblConfigPtr->CanCoreConfigPtr[CoreIndex]->
                  CanHthPeriodIndexPtr[HthRefPeriods]))
    {
      ApiStatus = E_NOT_OK;
    }
    else
    {
      ApiStatus = E_OK;
    }

    /* Is status E_OK? */

    if (E_OK == ApiStatus)
    {
      /* Local copy of the core specific global states */
      CoreGlobalPtr = Can_17_McmCan_GblCoreState[CoreIndex];

      /* Local copy of the core specific configuration */
      ConfigPtr = Can_17_McmCan_kGblConfigPtr->CanCoreConfigPtr[CoreIndex];

      /*Call transmit handler function for each of the CAN controllers*/
      for (CtrlIndex = 0U; CtrlIndex < ConfigPtr->CanCoreContCnt; CtrlIndex++)
      {

        /*Requested controller transmit event handling is of polling type
        and the controller mode is STARTED
        Check the Tx processing is configured as POLLING or MIXED*/
        /* [cover parentID={D5C52A11-422E-4504-A1A2-10893B61A054}]
        Check the Tx processing is configured as POLLING or MIXED and
        controller type
        is STARTED
        [/cover] */
        if ((CAN_17_MCMCAN_INTERRUPT != ConfigPtr->
            CanEventHandlingConfigPtr[CtrlIndex].CanTxProcessing) &&
            (CAN_17_MCMCAN_STARTED == CoreGlobalPtr->
                                            CanControllerModePtr[CtrlIndex]))
        {
          /* Current pending queue index */
          PendingQueueIndex = CoreGlobalPtr->CanTxSwQueuePtr->
                              CanTxSwPendingQueueIndex;

          PendingQueueLoopIndex = 0;

          /* Loop through the pending queue */
          /* [cover parentID={191730AE-8CB5-4819-A4DC-F6244885F909}]
          Loop through the pending queue
          [/cover] */
          for (LoopCounter = 0U;
                        LoopCounter < PendingQueueIndex; LoopCounter++)
          {
            /* read the element in queue */
            SwObjIndx = CoreGlobalPtr->CanTxSwQueuePtr->
                        CanTxSwPendingQueuePtr[PendingQueueLoopIndex];
            /* [cover parentID={83E0581E-939E-4050-9708-896C164A8BC1}]
            Call transmit handler function for each of the CAN controllers
            [/cover] */
            SwObjFound = Can_17_McmCan_lPeriodCheckSwHandle(CtrlIndex,
                      SwObjIndx, HthRefPeriods, ConfigPtr, CoreGlobalPtr);
            /* [cover parentID={FD9AF92F-CDD0-44ba-825E-984E8949287A}]
            Check If SwObj index is same as configured Index
            [/cover] */
            if (E_OK == SwObjFound)
            {
              /* Enter Critical Section */
              /* [cover parentID={DD687187-3429-4db8-AB99-00220CB84DEC}]
              Enter critical section
              [/cover] */
              SchM_Enter_Can_17_McmCan_CanWrMO();

              /* Clear sw queue for that entry */
              for (loopIndex = (uint16)PendingQueueLoopIndex;
                  loopIndex < PendingQueueIndex;
                  loopIndex++)
              {
                CoreGlobalPtr->CanTxSwQueuePtr->
                  CanTxSwPendingQueuePtr[loopIndex] =
                CoreGlobalPtr->CanTxSwQueuePtr->
                  CanTxSwPendingQueuePtr[loopIndex + (uint16)1U];

                CoreGlobalPtr->CanTxSwQueuePtr->
                  CanTxSwPendingQueuePtr[loopIndex + (uint16)1U] =
                CAN_17_MCMCAN_MAX_SWOBJECT_INDEX;
              }
              /* decrement the pending queue index */
              CoreGlobalPtr->CanTxSwQueuePtr->CanTxSwPendingQueueIndex--;

              /* [cover parentID={ABA091D2-5483-4c28-B33F-4458342095B2}]
              Exit critical section
              [/cover] */
              SchM_Exit_Can_17_McmCan_CanWrMO();

              PendingQueueLoopIndex--;
            }
            PendingQueueLoopIndex++;
          }

          /* [cover parentID={5F9332B5-8F15-4d26-A40A-13F75A51F018}]
          Invoke function for polling period handling
          [/cover] */
          Can_17_McmCan_lTxPeriodPollingHandler(CtrlIndex, HthRefPeriods,
                                                ConfigPtr, CoreGlobalPtr);
        }
      }
    }
  }
}

/*******************************************************************************
** Traceability   : [cover parentID={3A79409C-F659-4c8b-B069-5EB2BFA14FD7}]   **
**                                                                            **
**  Syntax           :  Std_ReturnType Can_17_McmCan_lPeriodCheckSwHandle     **
**                    (                                                       **
**                      const uint8 CtrlIndex,                                **
**                      const uint16 SwObjIndx,                               **
**                      const uint8 HthRefPeriods,                            **
**                      const Can_17_McmCan_CoreConfigType *const ConfigPtr,  **
**                     const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr**
**                    )                                                       **
**                                                                            **
**  Description      :  Function used for handling Tx confirmation according  **
**                      to the multiple write period called                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant                                              **
**                                                                            **
**  Parameters (in)  : HthRefPeriods - The write operation cyclic period      **
**                    configuration index                                     **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Can_17_McmCan_lPeriodCheckSwHandle(
    const uint8 CtrlIndex,
    const uint16 SwObjIndx, const uint8 HthRefPeriods,
    const Can_17_McmCan_CoreConfigType *const ConfigPtr,
    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr)
{
  /*Pointer to store HTH period info*/
  const Can_17_McmCan_PeriodHthMaskConfigType *HthPeriodInfo;

  /*Pointer to store HTH mask of the objects*/
  const Can_17_McmCan_HthMaskObjectConfigType *HthConfigInfo;

  /*Check if multiplexed transmission is enabled*/
  #if (CAN_17_MCMCAN_MULTIPLEXED_TRANSMISSION == STD_ON)

  /*Pointer to message RAM configuration*/
  const Can_17_McmCan_ControllerMsgRAMConfigType *MsgRamCfgPtr;

  /*Core specific TX queue size*/
  uint8 CoreTxQueueSize;

  /*HTH index*/
  Can_HwHandleType HthIndex;

  #endif

  /*Return value to check if SW object is found*/
  Std_ReturnType SwObjFound;

  /*HTH count*/
  Can_HwHandleType HthCnt;

  /*HTH start index*/
  Can_HwHandleType HthStartIndx;

  /*HTH end index*/
  Can_HwHandleType HthEndIndx;

  /*HTH reference period*/
  uint8 CoreHthRefPeriod;

  /*Can hardware controller ID*/
  uint8 HwControllerId;

  /*Core specific controller ID*/
  uint8 CoreControllerId;

  /*TX handle index*/
  Can_HwHandleType TxHandleIndx;

  /*HTH mask value*/
  uint8 HthMaskVal;

  /*SW object index calculation*/
  uint16 SwObjIndxCalc;

  /*Core specific HTH*/
  Can_HwHandleType CoreSpecHth;

  /*TX slot index*/
  uint32 TxSlotIndex;

  /*PDU handle*/
  PduIdType pduHandle;

  /*Variable to store TX buffer type*/
  Can_17_McmCan_TxBufferType BufferType;

  /* Set pointer with HTH period set information */
  HthPeriodInfo = ConfigPtr->CanPeriodHthMaskConfigPtr;

  /* Set pointer with HTH period handler information */
  HthConfigInfo = ConfigPtr->CanHthMaskObjectConfigPtr;

  /* Retrieve Core specific Hth period reference index */
  CoreHthRefPeriod = ConfigPtr->CanHthPeriodIndexPtr[HthRefPeriods];

  /* Read the cyclic corresponding handler first index */
  HthStartIndx = HthPeriodInfo[CoreHthRefPeriod].CanPerHthStartIndx;

  /* Read the cyclic corresponding handler first index */
  HthEndIndx = HthPeriodInfo[CoreHthRefPeriod].CanPerHthEndIndx;

  #if (CAN_17_MCMCAN_MULTIPLEXED_TRANSMISSION == STD_ON)

  /* Set pointer variable with Message RAM Configuration structure */
  MsgRamCfgPtr = ConfigPtr->CanControllerMsgRAMMapConfigPtr;
  #endif

  /* Reset object found flag */
  SwObjFound = E_NOT_OK;

  HthCnt = HthStartIndx;

  /*Read all the HTH  status corresponding with period*/
  /* [cover parentID={C784F5C2-29A8-4563-B083-DD0C6C59AB6D}]
  Read all the HTH  status corresponding with period
  [/cover] */
  while ((HthCnt < (HthStartIndx + HthEndIndx)) && (E_NOT_OK == SwObjFound))
  {
    /* Read Hw associated with HTH */
    HwControllerId = HthConfigInfo[HthCnt].HwControllerId;

    /* retrive core specific controller index */
    CoreControllerId = Can_17_McmCan_kGblConfigPtr->
                       CanLogicalControllerIndexPtr[HwControllerId].
                       CanLCoreSpecContIndex;


    /*Check If Controller Id is configured*/
    /* [cover parentID={B51CC71A-A81C-410c-A169-A9C89D1F99F2}]
    Check If Controller Id is configured ?
    [/cover] */
    if (CoreControllerId == CtrlIndex)
    {
      TxHandleIndx = HthConfigInfo[HthCnt].CanPerHthHwObjId -
                     Can_17_McmCan_kGblConfigPtr->CanNoOfHrh;

      /* Retrive core specific Hth of the hardware object */
      CoreSpecHth = Can_17_McmCan_kGblConfigPtr->
                    CanHthIndexPtr[TxHandleIndx].CanHthCoreSpecIndex;

      /* Read Mask value */
      HthMaskVal = ConfigPtr->CanTxHwObjectConfigPtr[CoreSpecHth].
                   CanTxBuffIndx;

      /* Retrive core specific Hth of the hardware object */
      BufferType = ConfigPtr->CanTxHwObjectConfigPtr[CoreSpecHth].
                   CanTxBufferType;


      /*Check if buffer is dedicated buffer*/
      /* [cover parentID={8F959ADA-A11D-4904-93C2-3EC18A61E061}]
      Check if buffer is dedicated buffer ?
      [/cover] */
      if (CAN_17_MCMCAN_TX_DED_BUFFER == BufferType)
      {
        /* Calculate Sw Obj Handle index */
        SwObjIndxCalc = (uint16)((CoreControllerId *
                                  CAN_17_MCMCAN_NOOF_TX_HW_BUFF_AVAILABLE) +
                                  HthMaskVal);

        /*Check if calculated SW obj handle is same as configuredSW obj handle*/
        /* [cover parentID={DFEEDF20-9DC4-4ecf-9565-DF85B91C3331}]
        Check if calculated SW obj handle is same as configuredSW obj handle
        [/cover] */
        if (SwObjIndx == SwObjIndxCalc)
        {
           /* Get Pdu Handle */
          pduHandle = CoreGlobalPtr->CanSwObjectHandlePtr[SwObjIndx];

          TxSlotIndex = ((uint32)1U << HthMaskVal);

           /* Check if slot is valid Tx slot */
           /* [cover parentID={DBE87262-8F3F-4c79-A87C-DBF97F775F04}]
          Check if slot is valid Tx slot
          [/cover] */
          if((TxSlotIndex & CoreGlobalPtr->BackupCanTxMaskPtr[CoreControllerId])
                                                                 == TxSlotIndex)
          {
            /* Enter Critical Section */
            /* [cover parentID={B3548DD9-8B5D-4510-B249-0395A4686BA3}]
            Enter Critical section
           [/cover] */
            SchM_Enter_Can_17_McmCan_CanWrMO();

            /* Release Tx Element */
            CoreGlobalPtr->CanTxMaskPtr[CoreControllerId] |= TxSlotIndex;

            /* Exit Critical Section */
            /* [cover parentID={639F9DAD-F435-487e-814C-C718F4E3B81B}]
            Exit Critical section
            [/cover] */
            SchM_Exit_Can_17_McmCan_CanWrMO();
          }

          /* Set with Exact PduHandle Stored Index value */
          /* Call Transmission confirmation to upper-layer with L-PDU handle */
          CanIf_TxConfirmation(pduHandle);

          /* handler configured for this period in the current core */
          SwObjFound = E_OK;
        }
      }
      #if (CAN_17_MCMCAN_MULTIPLEXED_TRANSMISSION == STD_ON)
      else
      {
        /*Read the core specific HTH from the configuration*/

        /* [cover parentID={4FB9A88A-0256-4351-86F3-45DAFE253A11}]
        Read all the HTH index
        [/cover] */
        CoreSpecHth = MsgRamCfgPtr[CoreControllerId].CanTxDedBuffCount;

        /*Read the TX queue size*/
        CoreTxQueueSize = MsgRamCfgPtr[CoreControllerId].CanTxQueueSize;

        /*Copy the HTH read to the HTH index*/
        HthIndex = CoreSpecHth;

        /*Scan through Hth buffers used*/

        while ((HthIndex < (CoreSpecHth + CoreTxQueueSize)) &&
              (E_NOT_OK == SwObjFound))
        {
          /* Calculate Sw Obj Handle index */
          SwObjIndxCalc = (uint16)((CoreControllerId *
                                    CAN_17_MCMCAN_NOOF_TX_HW_BUFF_AVAILABLE) +
                                    HthIndex);

          /*Check ifcalculated SW obj handle is same as configured SW obj
          handle*/
          /* [cover parentID={03A928B4-9D15-41ed-AE04-2CDB1043F16F}]
          Check ifcalculated SW obj handle is same as configured SW obj handle
          [/cover] */
          if (SwObjIndx == SwObjIndxCalc)
          {
            pduHandle = CoreGlobalPtr->CanSwObjectHandlePtr[SwObjIndx];

            TxSlotIndex = ((uint32)1U << HthIndex);

            /* Check if this element belong to Tx object */
            /* [cover parentID={CE35500A-3271-4820-8438-969C79F6690C}]
            Check if Queue index is mapped in back-up Queue (If mapped
            slot is part of Tx Queue)
            [/cover] */
            if((TxSlotIndex & CoreGlobalPtr->BackupCanTxMaskPtr[HwControllerId])
                                                                 == TxSlotIndex)
            {
              /* Enter Critical Section */
              /* [cover parentID={AC84AD36-1468-4653-910A-DC24604E1566}]
              Enter critical section for updating Queue mask
              [/cover] */
              SchM_Enter_Can_17_McmCan_CanWrMO();

              /* Release Tx object Element */
              CoreGlobalPtr->CanTxMaskPtr[HwControllerId] |= TxSlotIndex;

              /* Exit Critical Section */
              /* [cover parentID={E74A7318-C4F9-4b06-AC32-3B9A986C7091}]
              Exit critical section
              [/cover] */
              SchM_Exit_Can_17_McmCan_CanWrMO();
            }

            /* Set with Exact PduHandle Stored Index value */
            /* Call Transmission confirmation to upper-layer with L-PDU handle*/
            CanIf_TxConfirmation(pduHandle);

            /* handler configured for this period in the current core */
            SwObjFound = E_OK;
          }
          HthIndex++;
        }
      }
      #endif
    }
    HthCnt++;
  }
  return SwObjFound;
}
#endif /* #if (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON) */

#if (CAN_17_MCMCAN_RX_MULTI_PERIODS_SUPPORT == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={B707DAE3-81ED-45c7-A977-9CDA72CEF019}]   **
**  Syntax           : void Can_17_McmCan_lCheckIfFifoMessageLost             **
**                    (                                                       **
**                      const uint8 ControllerId,                             **
**                      const Can_17_McmCan_RxBufferType RxBuffer             **
**                    )                                                       **
**                                                                            **
**  Description      :  The functions checks if the Rx FIFO has lost any      **
**                      messages and raises errors                            **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Non-Reentrant                                          **
**                                                                            **
**  Parameters (in)  : ControllerId - Controller id to check Rx FIFO for      **
**                     RxBufferType - Indicates Fifo 0 or Fifo 1              **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
static void Can_17_McmCan_lCheckIfFifoMessageLost(const uint8 ControllerId,
                                  const Can_17_McmCan_RxBufferType RxBufferType)
{
  /*Can controller node address pointer*/
  volatile Ifx_CAN_N *NodeRegAddressPtr;

  /* calling core index */
  uint8 CoreIndex;

  /* core specifc configuration */
  const Can_17_McmCan_CoreConfigType *ConfigPtr;

  /* Get core id which is executing currently */
  CoreIndex = CAN_17_MCMCAN_GETCOREINDEX;

  /* Local copy of the core specific configuration */
  ConfigPtr = Can_17_McmCan_kGblConfigPtr->CanCoreConfigPtr[CoreIndex];

  /* Read the exact Node Start address */
  NodeRegAddressPtr = ConfigPtr->CanControllerConfigPtr[ControllerId].
                     CanNodeAddressPtr;

   /*For FIFO 0*/
   /* [cover parentID={02C75CDE-0894-43fc-81F1-DBA54E7C46E8}]
   Check if FIFO0?
   [/cover] */
  if (RxBufferType == CAN_17_MCMCAN_RX_FIFO0)
   {
    /* Check Received CAN message is lost or not */
    /* [cover parentID={BBE313D4-5537-4f9b-8683-99753C26283F}]
    Is the received CAN message is lost for FIFO0?
    [/cover] */
    if (NodeRegAddressPtr->IR.B.RF0L != CAN_17_MCMCAN_BIT_CLEAR_VAL)
    {
      #if (CAN_17_MCMCAN_RUNTIME_ERROR_DETECT == STD_ON)
      /*Trigger RUNTIME error*/
      /* [cover parentID={67C96A1C-8898-4e1f-BAE2-64408E0DE21E}]
      Call error handler to report runtime error
      [/cover] */
      /* [cover parentID={75D4CE5A-9F5C-4af6-A946-CD4D7FA4F10E}]
      Call error handler to report runtime error
     [/cover] */
      (void)Mcal_Wrapper_Det_ReportRuntimeError(CAN_17_MCMCAN_MODULE_ID,
            CAN_17_MCMCAN_INSTANCE_ID, CAN_17_MCMCAN_SID_RECEIVEHANDLER,
            CAN_17_MCMCAN_E_DATALOST);
      #endif
      /*Clear IR for RXFIFO0*/
      NodeRegAddressPtr->IR.U = CAN_17_MCMCAN_RF0L_CLEAR;
    }
   }

  /* For FIFO 1 */
  /* [cover parentID={A84D4442-37DA-479a-AC4B-2DA3A999EC1A}]
  Check if FIFO1?
  [/cover] */
  if (RxBufferType == CAN_17_MCMCAN_RX_FIFO1)
  {
    /* Check Received CAN message is lost or not */
    /* [cover parentID={F27F0069-159A-4820-9AD2-2A642DDA0FCA}]
    Is the received CAN message is lost for FIFO1?
    [/cover] */
    if (NodeRegAddressPtr->IR.B.RF1L != CAN_17_MCMCAN_BIT_CLEAR_VAL)
    {
      #if (CAN_17_MCMCAN_RUNTIME_ERROR_DETECT == STD_ON)
      /*Trigger RUNTIME error*/
      (void)Mcal_Wrapper_Det_ReportRuntimeError(CAN_17_MCMCAN_MODULE_ID,
            CAN_17_MCMCAN_INSTANCE_ID, CAN_17_MCMCAN_SID_RECEIVEHANDLER,
            CAN_17_MCMCAN_E_DATALOST);
      #endif
      /*Clear IR for RXFIFO0*/
      NodeRegAddressPtr->IR.U = CAN_17_MCMCAN_RF1L_CLEAR;
    }
  }
}

/*******************************************************************************
** Traceability   : [cover parentID={C4D59DCE-2FB9-45df-85DB-52DABEA0ED46}]   **
**  Syntax           :static void Can_17_McmCan_lRxDedicatedPeriodHandler(    **
**                          const Can_HwHandleType HrhCnt,                    **
**                          const uint8 ControllerId,                         **
**                          const Can_17_McmCan_CoreConfigType* ConfigPtr,    **
**                          const Can_17_McmCan_CoreGlobalType* CoreGlobalPtr)**
**                                                                            **
**  Description      :  Function used for handling Rx indication process with **
**                     multiple read period for Dedicated objects             **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Non-Reentrant                                          **
**                                                                            **
**  Parameters (in)  : HrhCnt - Total number of HRH                           **
**                     ControllerId -  CAN controller ID                      **
**                     CoreConfigPtr - Pointer to CAN driver configuration    **
**                     CoreGlobalPtr - Pointer to global structure            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
static void Can_17_McmCan_lRxDedicatedPeriodHandler(
                              const Can_HwHandleType HrhCnt,
                              const uint8 ControllerId,
    const Can_17_McmCan_CoreConfigType *ConfigPtr,
    const Can_17_McmCan_CoreGlobalType *CoreGlobalPtr)
{
  /*RX NDAT1 Value*/
  uint32 RxNDATValue0;

  /*RX NDAT2 Value*/
  uint32 RxNDATValue1;

  /*HRH mask value*/
  uint32 HrhMaskVal0;

  /*HRH mask value*/
  uint32 HrhMaskVal1;

  /*RX Dedicated mask*/
  uint32 RxDedMask;

  /*RX handle buffer position*/
  uint8 RxHandleBuffPos;

  /*Can controller node address pointer*/
  volatile Ifx_CAN_N *NodeRegAddressPtr;

  /*Pointer to HRH HW object object config type*/
  const Can_17_McmCan_HrhMaskObjectConfigType *HrhConfigInfo;

  /* Set pointer with Hrh period handler information */
  HrhConfigInfo = ConfigPtr->CanHrhMaskObjectConfigPtr;

  /* Read the exact Node Start address */
  NodeRegAddressPtr = ConfigPtr->CanControllerConfigPtr[ControllerId].
                      CanNodeAddressPtr;
  /* Read Mask value */
  HrhMaskVal0 = HrhConfigInfo[HrhCnt].CanPerRxbufferMaskvalue0;

  /* Read Mask value */
  HrhMaskVal1 = HrhConfigInfo[HrhCnt].CanPerRxbufferMaskvalue1;

  RxNDATValue0 = NodeRegAddressPtr->NDAT1.U;
  RxNDATValue1 = NodeRegAddressPtr->NDAT2.U;

  /*Check Buffer is NDAT1*/
  /* [cover parentID={9AF7E6F8-1AAC-4fb3-B1B0-B1B9CD1516C9}]
  Check Buffer is NDAT1
  [/cover] */
  /* [cover parentID={0CEF5CC2-D85A-4ffb-ACC5-35830091F7E8}]
  If NDAT1
  [/cover] */
  if ((HrhMaskVal0 != 0U) && (HrhMaskVal0 == (RxNDATValue0 & HrhMaskVal0)))
  {
    /* Set mask value */
    RxDedMask = 1U;

    /* Set with first bit position*/
    RxHandleBuffPos = 0U;

    /*Message is recieved at current rx buffer index*/

    /* [cover parentID={36C374AD-139A-4335-B5D6-58F3D51309E9}]
    Message is recieved at current rx buffer index
    [/cover] */
    while (HrhMaskVal0 != RxDedMask)
    {
      /* Increment bit position */
      RxHandleBuffPos++;

      /* Set mask for check next buffer status */
      RxDedMask = ((uint32)1U << RxHandleBuffPos);
    }
    /* Call receive data extract fucntion */
    /* [cover parentID={2967691D-3EC2-4038-B75B-78E16A93B075}]
    Call receive data extract fucntion
     [/cover] */
    Can_17_McmCan_lRxExtractData(ControllerId, RxHandleBuffPos,
                         CAN_17_MCMCAN_RX_DED_BUFFER, CoreGlobalPtr, ConfigPtr);
    /* Clear NDAT Register for receive new message */

    /* [cover parentID={C4F343B1-1A94-4378-9B73-BC4DD9EC63CF}]
    Set Mask
    [/cover] */
    NodeRegAddressPtr->NDAT1.U = HrhMaskVal0;
  }

  /*Check Buffer is NDAT2*/
  /* [cover parentID={C5E12580-5427-47b8-8C69-AC783512ED6D}]
  Check Buffer is NDAT2
  [/cover] */
  if ((HrhMaskVal1 != 0U) && (HrhMaskVal1 == (RxNDATValue1 & HrhMaskVal1)))
  {
    /* Set mask value */
    RxDedMask = 1U;

    /* Set with first bit position*/
    RxHandleBuffPos = 0U;

    /*Message is recieved at current rx buffer index*/
    /* [cover parentID={E9D26986-1144-4aa4-9EA7-222AAD0933DA}]
    If NDAT2
    [/cover] */
    while (HrhMaskVal1 != RxDedMask)
    {
      /* Increment bit position */
      /* [cover parentID={8DAADF17-7D80-472d-A565-33D449602749}]
      Increment bit position
      [/cover] */
      RxHandleBuffPos++;

      /* Set mask for check next buffer status */
      /* [cover parentID={56E851BD-F68F-48e1-8051-502160BCF1DB}]
      Set Mask
      [/cover] */
      RxDedMask = ((uint32)1U << RxHandleBuffPos);
    }

    /* Set for read data from NDAT1 buffer */
    RxHandleBuffPos = RxHandleBuffPos + CAN_17_MCMCAN_BUFFER_POS;

    /* Call receive data extract function */
    /* [cover parentID={815A6887-8E8B-4bc6-ABA2-4F23231A0631}]
    Call receive data extract fucntion
    [/cover] */
    Can_17_McmCan_lRxExtractData(ControllerId, RxHandleBuffPos,
                                CAN_17_MCMCAN_RX_DED_BUFFER, CoreGlobalPtr,
                                ConfigPtr);
    /* [cover parentID={06D915FF-05F9-440e-B38F-FD02D64B7E45}]
    Message is recieved at current rx buffer index
    [/cover] */
    NodeRegAddressPtr->NDAT2.U = HrhMaskVal1;
  }
}

/*******************************************************************************
** Traceability   : [cover parentID={E9A52584-F231-4d33-AC63-8EE58643ED53}]   **
**  Syntax           :static void Can_17_McmCan_lRxFIFOPeriodHandler(         **
**                          const Can_17_McmCan_RxBufferType RxFifo,          **
**                          const uint8 ControllerId,                         **
**                          const Can_17_McmCan_CoreConfigType* ConfigPtr,    **
**                          const Can_17_McmCan_CoreGlobalType* CoreGlobalPtr)**
**                                                                            **
**  Description      :The function used for handling Rx indication process    **
**                    with multiple read period for FIFO objects              **
**                                                                            **
**                                                                            **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Non-Reentrant                                          **
**                                                                            **
**  Parameters (in)  : RxFifo - RX buffer type                                **
**                     ControllerId -  CAN controller ID                      **
**                     CoreConfigPtr - Pointer to CAN driver configuration    **
**                     CoreGlobalPtr - Pointer to global structure            **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
static void Can_17_McmCan_lRxFIFOPeriodHandler(
  const Can_17_McmCan_RxBufferType RxFifo,
  const uint8 ControllerId,
  const Can_17_McmCan_CoreConfigType *ConfigPtr,
  const Can_17_McmCan_CoreGlobalType *CoreGlobalPtr)
{
  /*Flag for loop exit criteria*/
  uint8 LoopExitFlag = 0;

  /*RX handle buffer position*/
  uint8 RxHandleBuffPos;

  /*RX FIFO size*/
  uint8 FifoSize = 0;

  /*Can controller node address pointer*/
  volatile Ifx_CAN_N *NodeRegAddressPtr;

  /* Read the exact Node Start address */
  NodeRegAddressPtr = ConfigPtr->CanControllerConfigPtr[ControllerId].
                      CanNodeAddressPtr;
  /* [cover parentID={C1FC418B-1184-47a6-B6B9-179C27CBD2A0}]
  Check if it FIFO0
  [/cover] */
  if (CAN_17_MCMCAN_RX_FIFO0 == RxFifo)
  {
    FifoSize = ConfigPtr->CanControllerMsgRAMMapConfigPtr[ControllerId].
               CanRxFIFO0Size;

    /* Check and raise DET */
    /* [cover parentID={9DBFB56B-8AD5-47bb-84E5-CF5D94126CF5}]
    Check if message is LOST
    [/cover] */
    Can_17_McmCan_lCheckIfFifoMessageLost(ControllerId, CAN_17_MCMCAN_RX_FIFO0);

    /* Clear safety loop count, Clear WM,FULL flags, Read Fill value */
    NodeRegAddressPtr->IR.U = CAN_17_MCMCAN_CLEAR_IR_RF0_WF_BITS;

    /* Check if any of the message received by RXFIFO0 */
    /* [cover parentID={4697D94E-EC26-4971-864C-94F430F2EF41}]
    Check if any of the message received by RXFIFO0
    [/cover] */
    while ((NodeRegAddressPtr->RX.F0S.B.F0FL > 0U) && (LoopExitFlag < FifoSize))
    {
      LoopExitFlag++;
    /* a. Read all FIFO slots and acknowledge to free up slots
        b. Notify upper layer */
      /* Read Rx FIFO 0 Get Index */
      RxHandleBuffPos = NodeRegAddressPtr->RX.F0S.B.F0GI;

      /* Invoke data retrieve function */
      /* [cover parentID={5CD64370-B322-47b1-9667-0F4DF2DAB842}]
      Invoke data retrieve function
      [/cover] */
      Can_17_McmCan_lRxExtractData(ControllerId, RxHandleBuffPos,
                              CAN_17_MCMCAN_RX_FIFO0, CoreGlobalPtr, ConfigPtr);
      /* Set read Acknowledge of buffer */
      NodeRegAddressPtr->RX.F0A.B.F0AI = RxHandleBuffPos;
    }
  }
  /* [cover parentID={ECB68B61-7BD8-4713-8246-15E01A84D0D9}]
  Check if it FIFO1
  [/cover] */
  if (CAN_17_MCMCAN_RX_FIFO1 == RxFifo)
  {
    FifoSize = ConfigPtr->CanControllerMsgRAMMapConfigPtr[ControllerId].
                                                                CanRxFIFO1Size;
    LoopExitFlag = 0U;

    /* Check and raise DET */
    /* [cover parentID={6228044A-511A-40c2-9D2A-EBC272410F7A}]
    Check if message is LOST
    [/cover] */
    Can_17_McmCan_lCheckIfFifoMessageLost(ControllerId, CAN_17_MCMCAN_RX_FIFO1);

    /* Clear WM,FULL flags, Read Fill value */
    NodeRegAddressPtr->IR.U = CAN_17_MCMCAN_CLEAR_IR_RF1_WF_BITS;

    /* Check if any of the message received by RXFIFO1 */
    /* [cover parentID={93C98AA5-3B99-4a73-849D-34118F82BBAC}]
    Check if any of the message received by RXFIFO1
    [/cover] */
    while ((NodeRegAddressPtr->RX.F1S.B.F1FL > 0U) &&
                                                   (LoopExitFlag < FifoSize))
    {
      LoopExitFlag++;
      /* a. Read all FIFO slots and acknowledge to free up slots
        b. Notify upper layer */
      /* Read Rx FIFO 1 Get Index */
      RxHandleBuffPos = NodeRegAddressPtr->RX.F1S.B.F1GI;

      /* Invoke data retrieve function */
      /* [cover parentID={60997B77-CCE6-4699-9188-E65FCBA26316}]
      Invoke data retrieve function
      [/cover] */
      Can_17_McmCan_lRxExtractData(ControllerId, RxHandleBuffPos,
                              CAN_17_MCMCAN_RX_FIFO1, CoreGlobalPtr, ConfigPtr);
      /* Set read Acknowledge of buffer */
      NodeRegAddressPtr->RX.F1A.B.F1AI = RxHandleBuffPos;
    }
  }
}

/*******************************************************************************
** Traceability   : [cover parentID={855F23DF-F7AA-4b2d-BB46-206539D0F7B5}]   **
**                                                                            **
**  Syntax           : void Can_17_McmCan_lRxPeriodHandler                    **
**                    (                                                       **
**                      const uint8 HrhRefPeriods                             **
**                    )                                                       **
**                                                                            **
**  Description      :  Function used for handling Rx indication process with **
**                     multiple read period                                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Non-Reentrant                                          **
**                                                                            **
**  Parameters (in)  : HrhRefPeriods - The read operation cyclic period       **
**                    configuration index                                     **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
void Can_17_McmCan_lRxPeriodHandler(const uint8 HrhRefPeriods)
{
  /*Poinetr to HRH period info*/
  const Can_17_McmCan_PeriodHrhMaskConfigType *HrhPeriodInfo;

  /*Poinetr to HRH mask for HW objects*/
  const Can_17_McmCan_HrhMaskObjectConfigType *HrhConfigInfo;

  /*Core HRH reference period*/
  uint8 CoreHrhRefPeriod;

  /*HRH count*/
  Can_HwHandleType HrhCnt;

  /*HRH start index*/
  Can_HwHandleType HrhStartIndx;

  /*HRH end index*/
  Can_HwHandleType HrhEndIndx;

  /*Controller ID*/
  uint8 ControllerId;

  /*HE controller ID*/
  uint8 HwControllerId;

  /*Core index*/
  uint8 CoreIndex;

  /*Expected init status*/
  uint32 ExpInitStatus;

  /*Pointer to core state type */
  const Can_17_McmCan_CoreGlobalType *CoreGlobalPtr;

  /*Pointer to CAN configuration type*/
  const Can_17_McmCan_CoreConfigType *ConfigPtr;

  /*Type of RX processing for FIFOs*/
  Can_17_McmCan_RxFIFOProcessingType RxFIFOProcessing;

  /* Det check status */
  Std_ReturnType ApiStatus = E_NOT_OK;

  /* Get core id which is executing currently */
  CoreIndex = CAN_17_MCMCAN_GETCOREINDEX;

  /* Check if CAN driver is initialized */
  ExpInitStatus = (Can_17_McmCan_InitStatus >> ((uint32)CoreIndex *
                          (uint32)CAN_17_MCMCAN_INIT_STATUS_SIZE)) & 1U;

  /* [cover parentID={A4D84276-F7C2-48ae-A815-D2C9DBBE4004}]
  Is the driver initialized?
  [/cover] */
  if ((uint32)CAN_17_MCMCAN_DRV_READY == ExpInitStatus)
  {
    /* Check if ref period is configured for current core */
    /* [cover parentID={BD1836E8-2694-4150-B9FE-90BC6E72746A}]
    Is period configured for current core ?
    [/cover] */
    if ((CAN_17_MCMCAN_NO_HOH_VAL == Can_17_McmCan_kGblConfigPtr->
                                    CanCoreConfigPtr[CoreIndex]->
                                  CanHrhPeriodIndexPtr[HrhRefPeriods]))
    {
      ApiStatus = E_NOT_OK;
    }
    else
    {
      ApiStatus = E_OK;
    }

    if (E_OK == ApiStatus)
    {
      /* Local copy of the core specific configuration */
      ConfigPtr = Can_17_McmCan_kGblConfigPtr->CanCoreConfigPtr[CoreIndex];

      /* Local copy of the core specific global states */
      CoreGlobalPtr = Can_17_McmCan_GblCoreState[CoreIndex];

      /* Set pointer with Hrh period set information */
      HrhPeriodInfo = ConfigPtr->CanPeriodHrhMaskConfigPtr;

      /* Set pointer with Hrh period handler information */
      HrhConfigInfo = ConfigPtr->CanHrhMaskObjectConfigPtr;

      /* Retrieve Core specific Hrh period reference index */
      CoreHrhRefPeriod = ConfigPtr->CanHrhPeriodIndexPtr[HrhRefPeriods];

      /* Read the cyclic corresponding handler first index */
      HrhStartIndx = HrhPeriodInfo[CoreHrhRefPeriod].CanPerHrhStartIndx;

      /* Read the cyclic corresponding handler first index */
      HrhEndIndx = HrhStartIndx +
                              HrhPeriodInfo[CoreHrhRefPeriod].CanPerHrhEndIndx;

      /* Read all the Hrh  status corresponding with period */
      /* [cover parentID={39AB089C-F841-4ddc-8D11-8ED9AF549727}]
      Loop through the hrh objects
      [/cover] */
      for (HrhCnt = HrhStartIndx; HrhCnt < HrhEndIndx; HrhCnt++)
      {
        /* Read Hw associated with Hrh */
        HwControllerId = HrhConfigInfo[HrhCnt].HwControllerId;

        /* retrive core specific controller index */
        ControllerId = Can_17_McmCan_kGblConfigPtr->
                      CanLogicalControllerIndexPtr[HwControllerId].
                      CanLCoreSpecContIndex;

        /*If the controller is in STARTED mode?*/
        /* [cover parentID={E8CD6AF9-AB95-4752-9D17-003E31EB97B0}]
        Is the controller in STARTED mode?
        [/cover] */
        if (CAN_17_MCMCAN_STARTED == CoreGlobalPtr->
                                            CanControllerModePtr[ControllerId])
        {
          /* Check the buffer Type  */
          /* [cover parentID={5C1C012B-3DE4-40ec-B3EA-7116FC36ED2F}]
          Is it dedicated buffer?
          [/cover] */
          if (CAN_17_MCMCAN_RX_DED_BUFFER ==
                                    HrhConfigInfo[HrhCnt].CanPerHrhBufferType)
          {
            /* [cover parentID={A854942D-095E-4efc-94FA-2EF21D97FA8A}]
            Invoke the function for dedicated period handling
            [/cover] */
            Can_17_McmCan_lRxDedicatedPeriodHandler(HrhCnt, ControllerId,
                                                    ConfigPtr, CoreGlobalPtr);
          }

          /*Is it FIFO0 Buffer*/
          /* [cover parentID={0D0EE58C-45DF-489e-966F-C4C8EEDC1EB3}]
          Is it FIFO0 Buffer
          [/cover] */
          if (CAN_17_MCMCAN_RX_FIFO0 ==
                                    HrhConfigInfo[HrhCnt].CanPerHrhBufferType)
          {
            RxFIFOProcessing = ConfigPtr->
                CanControllerConfigPtr[ControllerId].CanRxFIFO0ProcessingConfig;

            /*Check if processing type is polling*/
            /* [cover parentID={7958D217-7CAC-41c7-87BE-2BF5DD137DCF}]
            Check if processing type is polling
            [/cover] */
            if (RxFIFOProcessing == CAN_17_MCMCAN_RX_FIFO_POLLING)
            {
              /* [cover parentID={725EEEA6-5A61-44ef-8EE1-478D63875F71}]
              Invoke function for FIFO period handler
              [/cover] */
              Can_17_McmCan_lRxFIFOPeriodHandler(CAN_17_MCMCAN_RX_FIFO0,
                                      ControllerId, ConfigPtr, CoreGlobalPtr);
            }
          }

          /*Is it FIFO1 buffer*/
          /* [cover parentID={103A55CC-7018-43eb-ACE2-3E8E8A294C1A}]
          Is it FIFO1 Buffer
          [/cover] */
          if (CAN_17_MCMCAN_RX_FIFO1 ==
                                      HrhConfigInfo[HrhCnt].CanPerHrhBufferType)
          {
            /*Check if processing type is polling*/
            RxFIFOProcessing = ConfigPtr->
                CanControllerConfigPtr[ControllerId].CanRxFIFO1ProcessingConfig;

            /* [cover parentID={323B8087-7A55-46ec-8F52-F504C460535D}]
            Check if processing type is polling
            [/cover] */
            if (RxFIFOProcessing == CAN_17_MCMCAN_RX_FIFO_POLLING)
            {
              /* [cover parentID={E2F380A3-493F-4e99-A689-DD29AE7C932B}]
              Inoke function for FIFO period handler
              [/cover] */
              Can_17_McmCan_lRxFIFOPeriodHandler(CAN_17_MCMCAN_RX_FIFO1,
                                  ControllerId, ConfigPtr, CoreGlobalPtr);
            }
          }
        }
      }
    }
  }
}
#endif /* #if (CAN_17_MCMCAN_RX_MULTI_PERIODS_SUPPORT == STD_ON) */

/*******************************************************************************
** Traceability   : [cover parentID={08B08865-A0FA-426d-BACC-9CBDE3F74BD1}]   **
**                                                                            **
**  Syntax           : static void Can_17_McmCan_lCancelPendingTx             **
**                    (                                                       **
**                      const uint8 ControllerId,                             **
**                      const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr*
**                      const Can_17_McmCan_CoreConfigType *const CoreConfigPtr*
**                    )                                                       **
**                                                                            **
** Description    :The function used to cancel all the pending Tx messages    **
**                 assigned with the specified controller.                    **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant                                              **
**                                                                            **
**  Parameters (in)  : ControllerId - Associated CAN Controller               **
**                     CoreGlobalPtr - Pointer to global structure            **
**                     ConfigPtr - Pointer to CAN driver configuration        **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
static void Can_17_McmCan_lCancelPendingTx(const uint8 ControllerId,
                      const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,
                      const Can_17_McmCan_CoreConfigType *const CoreConfigPtr)
{
  /*Can controller node address pointer*/
  volatile Ifx_CAN_N *NodeRegAddressPtr;

  /*TX pending status*/
  uint32 TxPendingStatus;

  /*TX hardware object index*/
  uint16 TxHwIndex;

  /*TX software object index*/
  uint16 SwObjIndx;

  /* Read the exact Node Start address */
  NodeRegAddressPtr = CoreConfigPtr->
                      CanControllerConfigPtr[ControllerId].CanNodeAddressPtr;

  /*Transmit hardware objects are configured for current core*/
  /* [cover parentID={96108FD4-DCDD-493c-804F-D21DE07FDA42}]
  Transmit hardware objects are configured for current core
  [/cover] */
  if (NULL_PTR != CoreConfigPtr->CanTxHwObjectConfigPtr)
  {
    for (TxHwIndex = 0U; TxHwIndex < CAN_17_MCMCAN_MAX_TX_BUFFER_INDEX;
                                                                   TxHwIndex++)
    {
      /* Calculate Sw Obj Handle index */
      SwObjIndx = (uint16)((ControllerId *
                            CAN_17_MCMCAN_NOOF_TX_HW_BUFF_AVAILABLE) +
                            TxHwIndex);

      CoreGlobalPtr->CanSwObjectHandlePtr[SwObjIndx] = 0U;
      /* [cover parentID={DDC22C72-AAE8-468c-AB65-FF858A945128}]
      Multiperiod is ON AND TX Processing is ON
      [/cover] */
      #if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
        (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON))

      /* reset the pending queue */
      CoreGlobalPtr->CanTxSwQueuePtr->CanTxSwPendingQueuePtr[SwObjIndx] =
                                               CAN_17_MCMCAN_MAX_SWOBJECT_INDEX;

      #endif /* #if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
          (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON)) */
    }
    /* [cover parentID={82001E39-4A61-42b2-AAF5-26133BF7BAEE}]
    TX MIXED PROCESSING or TX MULTI PERIOD is ON
    [/cover] */
    #if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
          (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON))

    /* reset the pending queue index */
    CoreGlobalPtr->CanTxSwQueuePtr->CanTxSwPendingQueueIndex = 0U;

    #endif /* #if ((CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON) || \
        (CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT == STD_ON)) */

    /* Check for pending request */
    /* [cover parentID={C926FB6D-5374-4b43-AA64-CFA53B46FAF2}]
    Pending Tx requests available
    [/cover] */
    if (0U != NodeRegAddressPtr->TX.BRP.U)
    {
      /* Read Pending Tx Request for buffer */
      TxPendingStatus = NodeRegAddressPtr->TX.BRP.U;

      /* Set the pending request with cancellation request */
      NodeRegAddressPtr->TX.BCR.U = TxPendingStatus;
    }

    /* Rebuild mask Queue element mask */
    CoreGlobalPtr->CanTxMaskPtr[ControllerId] =
                                CoreGlobalPtr->BackupCanTxMaskPtr[ControllerId];
  }
}

/*******************************************************************************
** Traceability   : [cover parentID={2928BBAC-9D1E-4219-BBED-D06CF1A2EACD}]   **
**                                                                            **
**  Syntax           : static void Can_17_McmCan_lClearReceivedMsg            **
**                    (                                                       **
**                      const uint8 HwControllerId,                           **
**                      const Can_17_McmCan_CoreConfigType *const CoreConfigPtr*
**                    )                                                       **
**                                                                            **
**  Description      :The function clears receive message objects to avoid    **
**                    any unintended notification                             **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant                                              **
**                                                                            **
**  Parameters (in)  : HwControllerId - Associated physical CAN Controller    **
**                     CoreConfigPtr - Pointer to CAN driver configuration    **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
static void Can_17_McmCan_lClearReceivedMsg(const uint8 HwControllerId,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr)
{
  /*Can controller node address pointer*/
  volatile Ifx_CAN_N *NodeRegAddressPtr;

  /*RX buffer position*/
  uint8 RxHandleBuffPos;

  /*Counter for loop*/
  uint8 LoopExitCounter = 0U;

  /*RX FIFO size*/
  uint8 FifoSize = 0U;

  /* Read the exact Node Start address */
  NodeRegAddressPtr = CoreConfigPtr->CanControllerConfigPtr[HwControllerId].
                      CanNodeAddressPtr;

  /* Dedicated Rx Message checks */
  /* [cover parentID={6507E831-08CA-4078-884E-FEF5E67DCC9F}]
  Is RX dedicated being used?
  [/cover] */
  if (CAN_17_MCMCAN_ADDRESS_CHECK != CoreConfigPtr->
                               CanControllerMsgRAMMapConfigPtr[HwControllerId].
                                     CanControllerMsgRAMMap[CAN_17_MCMCAN_RBSA])
  {
    /* Check if any of the message received by dedicated buffer NDAT1 */
    /* [cover parentID={CA82A735-67F5-4954-A151-88CEBBB0F624}]
    The message is received by dedicated buffer NDAT1
    [/cover] */
    if (0U != NodeRegAddressPtr->NDAT1.U)
    {
      /* Clear the Register */
      NodeRegAddressPtr->NDAT1.U = CAN_17_MCMCAN_CLEAR_NEWDATA_REG;
    }

    /* Check if any of the message received by dedicated buffer NDAT2 */
    /* [cover parentID={C1EBCA30-73E0-4cbb-80BE-D0B8E1F2928E}]
    The message is received by dedicated buffer NDAT2
    [/cover] */
    if (0U != NodeRegAddressPtr->NDAT2.U)
    {
      /* Clear the Register */
      NodeRegAddressPtr->NDAT2.U = CAN_17_MCMCAN_CLEAR_NEWDATA_REG;
    }
  }
  /* RxFIFO0 Message checks */
  /* [cover parentID={7DAB05D7-ACE9-4891-9BC9-103699A8D80F}]
  Message uses RX FIFO0
  [/cover] */
  if (CAN_17_MCMCAN_ADDRESS_CHECK != CoreConfigPtr->
                                CanControllerMsgRAMMapConfigPtr[HwControllerId].
                                CanControllerMsgRAMMap[CAN_17_MCMCAN_F0SA])
  {
    FifoSize = CoreConfigPtr->CanControllerMsgRAMMapConfigPtr[HwControllerId].
               CanRxFIFO0Size;

    /* Check if any of the message received by RXFIFO0 */
    /* [cover parentID={C8C29F16-63D3-4770-A7B5-D85FE656E164}]
    Message received by RXFIFO0
    [/cover] */
    while ((NodeRegAddressPtr->RX.F0S.B.F0FL > 0U) &&
                                                   (LoopExitCounter < FifoSize))
    {
      LoopExitCounter++;

      /* Read Rx FIFO 0 Get Index */
      RxHandleBuffPos = NodeRegAddressPtr->RX.F0S.B.F0GI;

      /* Set read Acknowledgement of buffer */
      NodeRegAddressPtr->RX.F0A.U = RxHandleBuffPos;
    }
  }
  /* RxFIFO1 Message checks */
  /* [cover parentID={ACD4DD5E-3FD6-476c-BD26-703E849459D2}]
  Message uses RX FIFO1
  [/cover] */
  if (0U != CoreConfigPtr->CanControllerMsgRAMMapConfigPtr[HwControllerId].
                                     CanControllerMsgRAMMap[CAN_17_MCMCAN_F1SA])
  {
    /*Read the FIFO size*/
    FifoSize = CoreConfigPtr->CanControllerMsgRAMMapConfigPtr[HwControllerId].
               CanRxFIFO1Size;

    LoopExitCounter = 0U;

    /* Check if any of the message received by RXFIFO1 */
    /* [cover parentID={A07022A0-5C78-4630-880B-1A2FFCBCF5AC}]
    Message received by RXFIFO1
    [/cover] */
    while ((NodeRegAddressPtr->RX.F1S.B.F1FL > 0U) &&
            (LoopExitCounter < FifoSize))
    {
      LoopExitCounter++;

      /* Read Rx FIFO 0 Get Index */
      RxHandleBuffPos = NodeRegAddressPtr->RX.F1S.B.F1GI;

      /* Set read Acknowledge of buffer */
      NodeRegAddressPtr->RX.F1A.U = RxHandleBuffPos;
    }
  }
}

/*******************************************************************************
** Traceability     : [cover parentID={F5913DAB-E168-432f-B5BC-C4429CEBC659}] **
**  Syntax           : static Std_ReturnType Can_17_McmCan_lTimeOut           **
**                    (                                                       **
**                      const volatile uint32* const RegAddressPtr,           **
**                      const uint32 CheckVal,                                **
**                      const boolean CheckStatus                             **
**                    )                                                       **
**                                                                            **
**  Description      : This service for a time-out detection in case the      **
**                    hardware does not react in the expected time            **
**                    (hardware error) to prevent endless loops.              **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Non-Reentrant                                          **
**                                                                            **
**  Parameters (in)  : RegAddressPtr- The address of register which value     **
**                    shall be check.                                         **
**                    CheckVal- The value which is used for comparing with    **
**                    Register value.                                         **
**                    CheckStatus- used for identify the comparison method    **
**                    Method.                                                 **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : E_OK: Hw written successfully                          **
**                     E_NOT_OK: Hw is not set with requested value           **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Can_17_McmCan_lTimeOut(
    const volatile uint32 *const RegAddressPtr,
    const uint32 CheckVal, const Can_17_McmCan_TimeoutCheckType CheckStatus)
{
  /*Timeout resolution to calculate the delay*/
  uint32 TimeOutResolution;

  /*Timeout count for delay span*/
  uint32 TimeOutCount;

  /*Initial timeout count for delay span*/
  uint32 TimeOutCountInitial;

  /*Total number of measured ticks*/
  uint32 MeasuredTicks;

  /*Variable to store Timeout status*/
  Std_ReturnType TimeOutStatus = E_NOT_OK;

  /* Read the delay calibration Time */
  TimeOutResolution = Mcal_DelayTickResolution();

  /* calculate actual delay span */
  TimeOutCount = (uint32)CAN_17_MCMCAN_TIMEOUT_DURATION / TimeOutResolution;
  /* Wait for Hardware Loop time-out to check  the setting status of
     status register */
  /* Set with initial value */
  TimeOutCountInitial = Mcal_DelayGetTick();
  do
  {
    /* Count the elapsed time */
    MeasuredTicks = Mcal_DelayGetTick() - TimeOutCountInitial;

    /*If the status for EQUAL check needs to be performed*/

    /* [cover parentID={DE447DBA-838D-4ca7-83BD-2EC917BD1887}]
    Is the status TRUE if the check is performed against EQUAL?
    [/cover] */
    if (CAN_17_MCMCAN_EQUAL == CheckStatus)
    {
      if (CheckVal == (((uint32)*RegAddressPtr & CheckVal)))
      {
        TimeOutStatus = E_OK;
      }
    }
    /*If the status for NOT EQUAL check needs to be performed*/
    /* [cover parentID={9186353F-7735-4403-8BF8-C4269FEC4CFD}]
    Is the status TRUE if the check is performed against NOT EQUAL?
    [/cover] */
    else if (CAN_17_MCMCAN_NOT_EQUAL == CheckStatus)
    {
      if (CheckVal != (((uint32)*RegAddressPtr & CheckVal)))
      {
        TimeOutStatus = E_OK;
      }
    }
    /*If the status for NAND check needs to be performed*/
    /* [cover parentID={3122C46A-F731-4976-8A77-CBD4C4B2CE91}]
    Is the status TRUE if the check is performed against NAND?
    [/cover] */
    else if (CAN_17_MCMCAN_NAND == CheckStatus)
    {
      /*CAN_17_MCMCAN_NAND == CheckStatus*/
      if (CAN_17_MCMCAN_BIT_RESET_VAL !=
            (((uint32)*RegAddressPtr) & (CheckVal)))
      {
        TimeOutStatus = E_OK;
      }
    }
    /*If the status for AND check needs to be performed*/
    /* [cover parentID={CF0234E8-4730-4b49-9644-7648914E6B37}]
    Is the status TRUE if the check is performed against AND?
    [/cover] */
    else
    {
      /*CAN_17_MCMCAN_AND == CheckStatus*/
      if (CAN_17_MCMCAN_BIT_RESET_VAL ==
            (((uint32)*RegAddressPtr) & (CheckVal)))
      {
        TimeOutStatus = E_OK;
      }
    }
  }
  /*Loop till timeout threshold is reached and status till remains E_NOT_OK*/
  while ((E_NOT_OK == TimeOutStatus) &&
           ((TimeOutCount * CAN_17_MCMCAN_THRESHOLD_VAL) >= MeasuredTicks));

  return TimeOutStatus;
}

#if (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={488C84CA-6384-46ea-9B45-C5A8B6FD3931}]   **
**                                                                            **
**  Syntax           : static void Can_17_McmCan_lActivateIcom                **
**                    (                                                       **
**                       const uint8 Controller ,                             **
**                       const IcomConfigIdType  ConfigurationId,             **
**                       Can_17_McmCan_CoreGlobalType  *const CoreGlobalPtr,  **
**                       const Can_17_McmCan_CoreConfigType *const ConfigPtr  **
**                    )                                                       **
**                                                                            **
** Description      :This internal function used for activated Pretended      **
**                   Networking support for the specified controller and this **
**                   function will reconfigure the can controller according   **
**                   with the Icom configuration parameter.                   **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant                                              **
**                                                                            **
**  Parameters (in)  : Controller - 0 to 255  Requested controller Id         **
**                     ConfigurationId - 1 to 255 Requested Icom              **
**                     configuration ID                                       **
**                     CoreGlobalPtr - Core specific global variable holding  **
**                     controller states                                      **
**                     CoreConfigPtr - Core specific controller configuration **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Parameters (in-out) : none                                                **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
static void Can_17_McmCan_lActivateIcom(const uint8 Controller,
                                         const IcomConfigIdType ConfigurationId,
                        const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,
                        const Can_17_McmCan_CoreConfigType *const CoreConfigPtr)
{
  /*Pointer to store the SID configuration*/
  const Can_17_McmCan_SIDFilterConfigType *SIDPtr;

  /*Pointer to store the data configuration of SID filters*/
  volatile Ifx_CAN_STDMSG *SIDFilterPtr;

  /*Variable to store filter start address*/
  uint32 FilterStartAddr;

  /*Variable to store actual filter address*/
  uint32 FilterRealAddr;

  /*Filter start index*/
  uint16 FiltrStartIndx;

  /*Filter end index*/
  uint16 FiltrEndIndx;

  /*Filter index to loop through the multiple configured filters*/
  uint16 FiltrIndx;

  /*Offset index*/
  uint8 OffsetIndx;

  /*Pointer to store the XID configuration*/
  const Can_17_McmCan_XIDFilterConfigType *XIDPtr;

  /*Pointer to store the data configuration of SID filters*/
  volatile Ifx_CAN_EXTMSG *XIDFilterPtr;

  /* Read the exact Node Start address */
  Ifx_CAN_N *NodeRegAddressPtr = CoreConfigPtr->
                                             CanControllerConfigPtr[Controller].
                                                              CanNodeAddressPtr;

  /* Check if Wakeup on bus off condition is configured*/
  /* [cover parentID={364ACACF-B21D-46a6-B2E1-525B11513D49}]
  Is Wakeup on bus off condition is configured
  [/cover] */
  if (FALSE == Can_17_McmCan_kGblConfigPtr->
               CanIcomConfigPtr[ConfigurationId - 1U].CanIcomWakeOnBusOff)
  {
    /* Check if Wakeup on bus off condition is configured*/
    /* [cover parentID={097D0152-B9A7-4708-B874-F5F51524750A}]
    Is Bus off interrupt of the current CAN node enabled
    [/cover] */
    if (CAN_17_MCMCAN_INTERRUPT == CoreConfigPtr->
                      CanEventHandlingConfigPtr[Controller].CanBusoffProcessing)
    {
      /* Disable Bus off interrupt of the current CAN node */
      NodeRegAddressPtr->IE.B.BOE = 0U;
    }
    /* Set the ICOM Wake on bus off status */
    CoreGlobalPtr->CanIcomConfgBOStatusPtr[Controller] = FALSE;
  }
  else
  {

    /*If Can event handling interrupt enabled ?*/
    /* [cover parentID={08AAC771-0EFE-4381-B519-F7CDE3A3A5ED}]
    Is Can event handling interrupt enabled ?
    [/cover] */
    if (CAN_17_MCMCAN_INTERRUPT ==
       CoreConfigPtr->CanEventHandlingConfigPtr[Controller].CanBusoffProcessing)
    {
      /* Enable Bus off interrupt of the current CAN node */
      NodeRegAddressPtr->IE.B.BOE = CAN_17_MCMCAN_BIT_SET_VAL;
    }
    /* Set the ICOM Wake on bus off status */
    CoreGlobalPtr->CanIcomConfgBOStatusPtr[Controller] = TRUE;
  }

  /*In a configuration if SID is configured, XID pointer would be NULL and
  vice versa. Both simultaneously can not be configured and neither would both
  be NULL. This is taken care at the configuration*/

  /*Check if SID filter is configured*/
  /* [cover parentID={DA2E1E7C-505A-4863-B084-B08A3887846E}]
  If SID Filter Config Pointer is not NULL
  [/cover] */
  if (NULL_PTR != CoreConfigPtr->CanSIDFilterConfigPtr)
  {
    /* Set offset with first element */
    OffsetIndx = 0U;

    /* Set SID filter list Address */
    SIDPtr = CoreConfigPtr->CanSIDFilterConfigPtr;

    /* Set with first SID filter Index */
    FiltrStartIndx = CoreConfigPtr->CanControllerConfigPtr[Controller].
                     CanControllerMOMap[CAN_17_MCMCAN_RX_SID_STARTINDEX];

    /* Set with End SID filter Index */
    FiltrEndIndx = FiltrStartIndx +
                              CoreConfigPtr->CanControllerConfigPtr[Controller].
                                CanControllerMOMap[CAN_17_MCMCAN_TOTAL_SIDCFG];

    /* Read Standard Identifier filter Start address */
    FilterStartAddr =
                     CoreConfigPtr->CanControllerMsgRAMMapConfigPtr[Controller].
                         CanControllerMsgRAMMap[CAN_17_MCMCAN_FLSSA];

    /* Set with all standard filter configuration */
    for (FiltrIndx = FiltrStartIndx; FiltrIndx < FiltrEndIndx; FiltrIndx++)
    {
      /* Set with SID Filter element address */
      FilterRealAddr = FilterStartAddr + (CAN_17_MCMCAN_RAM_BYTES *
                          (uint32)OffsetIndx);

      /* MISRA2012_RULE_11_6_JUSTIFICATION: The pointer cast is used to
      cast the address to the Standard filter elements structure type for
      accessing RAM area */
      /* MISRA2012_RULE_11_4_JUSTIFICATION: Memory address is generated as a
      numerical value, it is accessed as a pointer to the RAM address.
      Hence an explicit typecast from numerical to pointer. */
      /* Increment for access next filter element */
      SIDFilterPtr = (volatile Ifx_CAN_STDMSG *)FilterRealAddr;

      /*If Pretended Network OFF*/
      /* [cover parentID={0A4FDBB9-8D20-4320-B5C1-209682BE857A}]
      If Pretended Network OFF
      [/cover] */
      if (FALSE == SIDPtr[FiltrIndx].CanSidPNSupport)
      {
        /* Set to Reject Message with Filter element */
        SIDFilterPtr->S0.B.SFEC = 0U;
      }
      /* Increment for access next filter element */
      OffsetIndx++;
    }
  }

  /*Check if XID filter is configured*/
  /* [cover parentID={979410E7-2304-4e71-A0BD-BD924D7C9EA5}]
  If XID Filter Config Pointer is not NULL
  [/cover] */
  if (NULL_PTR != CoreConfigPtr->CanXIDFilterConfigPtr)
  {

    /* Set with XID filter list configuration address */
    XIDPtr = CoreConfigPtr->CanXIDFilterConfigPtr;

    /* Read Extended Identifier filter Start address */
    FilterStartAddr = CoreConfigPtr->
                      CanControllerMsgRAMMapConfigPtr[Controller].
                         CanControllerMsgRAMMap[CAN_17_MCMCAN_FLSEA];

    /* Set with start Index */
    FiltrStartIndx = CoreConfigPtr->CanControllerConfigPtr[Controller].
                        CanControllerMOMap[CAN_17_MCMCAN_RX_XID_STARTINDEX];

    /* Set with end Index */
    FiltrEndIndx = FiltrStartIndx +
                              CoreConfigPtr->CanControllerConfigPtr[Controller].
                                CanControllerMOMap[CAN_17_MCMCAN_TOTAL_XIDCFG];

    /* Set OFFSET with first element */
    OffsetIndx = 0U;

    /* Set with all Extended filter configuration */
    for (FiltrIndx = FiltrStartIndx; FiltrIndx < FiltrEndIndx; FiltrIndx++)
    {
      /* Set address with XID filter element Address */
      FilterRealAddr = FilterStartAddr +
                                      ((uint32)CAN_17_MCMCAN_FILTER_ADDR_VAL *
                                      (uint32)OffsetIndx);

      /* MISRA2012_RULE_11_6_JUSTIFICATION: The pointer cast is used to cast the
      address to the extended filter elements structure type for accessing
      RAM area */
      /* MISRA2012_RULE_11_4_JUSTIFICATION: Memory address is generated as a
      numerical value, it is accessed as a pointer to the RAM address.
      Hence an explicit typecast from numerical to pointer. */
      XIDFilterPtr = (volatile Ifx_CAN_EXTMSG *)FilterRealAddr;

      /*If Pretended Network OFF*/
      /* [cover parentID={AA578760-E59C-462a-9A65-81B9E3FFDB67}]
      If Pretended Network OFF
      [/cover] */
      if (FALSE == XIDPtr[FiltrIndx].CanXidPNSupport)
      {
        /* Set to Reject Message with Filter element */
        XIDFilterPtr->F0.B.EFEC = 0U;
      }
      /* Increment for access next filter element */
      OffsetIndx++;
    }
  }
  /* Store ICOM Configuration ID */
  CoreGlobalPtr->CanActiveIcomCfgIdPtr[Controller] = ConfigurationId;

  /*Set the pretended network status for the current CAN controller */
  CoreGlobalPtr->CanIcomEnableStatusPtr[Controller] = TRUE;
}

/*******************************************************************************
** Traceability   : [cover parentID={BE2FCC3E-23ED-4ab0-A6C3-8A5E7D285E7A}]   **
**                  [cover parentID={B3999980-346F-4b50-A961-D4F071098113}]   **
**  Syntax           : static void Can_17_McmCan_lDeactivateIcom              **
**                    (                                                       **
**                      const uint8 Controller,                               **
**                      Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,    **
**                      const Can_17_McmCan_CoreConfigType *const CoreConfigPtr*
**                    )                                                       **
**                                                                            **
** Description    :The function is used to deactivate Pretended Networking    **
**                 support of specified controller and make the controller    **
**                 for process the messages normally as configured in the     **
**                 normal configuration.                                      **
** Service ID       : NA                                                      **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant                                              **
**                                                                            **
**  Parameters (in)  : Controller - 0 to 255 Requested controller Id          **
**                     ConfigurationId - 1 to 255 Current Icom configuration  **
**                     used by the requested controller                       **
**                     CoreGlobalPtr - Global variable holding core specific  **
**                     controller states                                      **
**                     CoreConfigPtr - Core specific controller configuration **
**                     variable                                               **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Parameters (in-out) : none                                                **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
static void Can_17_McmCan_lDeactivateIcom(const uint8 Controller,
                        const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,
                        const Can_17_McmCan_CoreConfigType *const CoreConfigPtr)
{
  /* Pointer to CAN node register type */
  volatile Ifx_CAN_N *NodeRegAddressPtr;

  /* register address to be checked for timeout */
  const volatile uint32 *RegAddressPtr;

  /*First ICOM message index from configuration*/
  uint16 IcomMsgIndex;

  /*Variable to traverse through the ICOM message indices*/
  uint16 MsgIndex;

  /*Number of RX ICOM message indices*/
  uint16 IcomNoOfRxMsg;

  /*ICOM configuration ID*/
  uint8 IcomConfigId;

  /*Return value to check if timeout has occured*/
  Std_ReturnType ApiStatus;

  /* Get ICOM configuration ID*/
  IcomConfigId = CoreGlobalPtr->CanActiveIcomCfgIdPtr[Controller];

  /* Get the first receive configuration index */
  IcomMsgIndex = Can_17_McmCan_kGblConfigPtr->CanIcomConfigPtr
                 [IcomConfigId - 1U].CanIcomFirstMsgIndx;

  /* Get the total number of ICOM Receive messages configured*/
  IcomNoOfRxMsg = Can_17_McmCan_kGblConfigPtr->CanIcomConfigPtr
                  [IcomConfigId - 1U].CanIcomNoOfMsgIndx;

  /* Read the exact Node Start address */
  NodeRegAddressPtr =
            CoreConfigPtr->CanControllerConfigPtr[Controller].CanNodeAddressPtr;

  /* Set with Initialization mode */
  NodeRegAddressPtr->CCCR.B.INIT = CAN_17_MCMCAN_BIT_SET_VAL;

  /* Set with Register Address */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: Typecasting to uint32 is
    required in order to maintain a common interface to check bits
    that are getting updated by hardware */
  RegAddressPtr = (const volatile uint32 *)(&(NodeRegAddressPtr->CCCR.U));

  /* Wait until the INIT bits become set */
  ApiStatus = Can_17_McmCan_lTimeOut((const volatile uint32 *)RegAddressPtr,
              CAN_17_MCMCAN_NODE_INIT_CCE_SET, CAN_17_MCMCAN_EQUAL);

  /*Check if INIT bit is SET as expected*/
  /* [cover parentID={3126B8E2-B9AD-4d4d-B110-51FC582FFDA0}]
  Check if timeout occured
  [/cover] */
  if (E_OK == ApiStatus)
  {
    /* Enable configuration change */
    NodeRegAddressPtr->CCCR.B.CCE = CAN_17_MCMCAN_BIT_SET_VAL;

    /* Wait until the Configuration Change Enable bits become set */
    ApiStatus = Can_17_McmCan_lTimeOut((const volatile uint32 *)RegAddressPtr,
    CAN_17_MCMCAN_CCCR_CCE_SET_MASK, CAN_17_MCMCAN_EQUAL);
  }

  /*Check if CCE bit is SET as expected*/
  /* [cover parentID={3A5EFDD9-0795-4b4c-A3CD-DFE6BFF3F497}]
  Check if timeout occurs
  [/cover] */
  if (E_OK == ApiStatus)
  {

    /* Check if Wakeup on bus off condition is configured*/
    /* [cover parentID={CB0FE3D4-8D89-4b3c-9BD2-3A9FE061098A}]
    Check if Wakeup on bus off condition is configured and check interrupt
    [/cover] */
    if (FALSE == CoreGlobalPtr->CanIcomConfgBOStatusPtr[Controller])
    {
      if (CAN_17_MCMCAN_INTERRUPT == CoreConfigPtr->
                      CanEventHandlingConfigPtr[Controller].CanBusoffProcessing)
      {
        /* Re enable the Bus Off interrupt of the requested CAN node */
        NodeRegAddressPtr->IE.B.BOE = CAN_17_MCMCAN_BIT_SET_VAL;
      }
    }
    /*In a configuration if SID is configured, XID pointer would be NULL and
    vice versa. Both simultaneously can not be configured and neither would both
    be NULL. This is taken care at the configuration*/

    /*If SID Config Pointer is not Null*/
    /* [cover parentID={D719E03F-D4BE-4569-8473-A4DF0E8AE018}]
    If SID Config Pointer is NULL?
    [/cover] */
    if (NULL_PTR != CoreConfigPtr->CanSIDFilterConfigPtr)
    {
      /*Configure the ICOM with the SID fileter configuration*/
      Can_17_McmCan_lIcomSIDFilterConfiguration(Controller, CoreConfigPtr);
    }

    /* If XID Config Pointer is not Null*/
    /* [cover parentID={80B1B0F9-7EF8-46a6-A730-C2038990D035}]
    If XID Config Pointer NULL?
    [/cover] */
    if (NULL_PTR != CoreConfigPtr->CanXIDFilterConfigPtr)
    {
      /*Configure the ICOM with the XID fileter configuration*/
      Can_17_McmCan_lIcomXIDFilterConfiguration(Controller, CoreConfigPtr);
    }

    /*Set with normal operation mode,CCE will be cleared when INIT becomes '0'*/
    NodeRegAddressPtr->CCCR.B.INIT = CAN_17_MCMCAN_BIT_RESET_VAL;

    /* Check the Hw status update */
    ApiStatus = Can_17_McmCan_lTimeOut((const volatile uint32 *)RegAddressPtr,
                                       (uint32)CAN_17_MCMCAN_NODE_INIT_MODE,
                                      CAN_17_MCMCAN_NOT_EQUAL);

    /*Chek for timeout*/
    /* [cover parentID={55ABC673-3427-42f9-B732-C0674571A352}]
    Check if timeout occured
    [/cover] */
    if (E_OK == ApiStatus)
    {
      /* Enter critical section*/
      /* [cover parentID={7EBB138D-7A1D-4afc-81D9-CA6C9D7B0635}]
      Enter the critical section
      [/cover] */
      SchM_Enter_Can_17_McmCan_IcomMsgCntrVal();

      /* Set with First index value */
      MsgIndex = IcomMsgIndex;

      while (MsgIndex < (IcomMsgIndex + IcomNoOfRxMsg))
      {
        /* Clear Msg Counter values */
        CoreGlobalPtr->CanIcomMsgCntrValPtr[MsgIndex] = 0U;

        /* Increment message counter index */
        MsgIndex++;
      }

      /* Clear the ICOM Wake on bus off status */
      CoreGlobalPtr->CanIcomConfgBOStatusPtr[Controller] = FALSE;

      /* Set the pretended network status for the current CAN controller */
      CoreGlobalPtr->CanIcomEnableStatusPtr[Controller] = FALSE;

      /* Clear ICOM Configuration ID */
      CoreGlobalPtr->CanActiveIcomCfgIdPtr[Controller] = 0U;

      /* Allow Can_Writes - Icom de-activation completed */
      CoreGlobalPtr->CanIcomBlockWriteCallsPtr[Controller] = FALSE;

      /*Exit critical section*/

      /* [cover parentID={E2CCDE21-ACA6-449f-9123-96166B0C51C1}]
      Exit the critical section
      [/cover] */
      SchM_Exit_Can_17_McmCan_IcomMsgCntrVal();
    }
  }
}

/*******************************************************************************
** Traceability   : [cover parentID={BD44C305-83A3-4491-8FEF-0B908352B910}]   **
**  Syntax          : static void Can_17_McmCan_lIcomSIDFilterConfiguration   **
**                    (const uint8 Controller,                                **
**                     const Can_17_McmCan_CoreConfigType *const CoreConfigPtr)*
**                                                                            **
**  Description      : The function configures SID ICOM filter settings       **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant                                              **
**                                                                            **
**  Parameters (in)  : Controller - Associated CAN Controller                 **
**                    CoreConfigPtr - Pointer to CAN driver configuration     **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Parameters (in-out) : none                                                **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
static void Can_17_McmCan_lIcomSIDFilterConfiguration(const uint8 Controller,
                        const Can_17_McmCan_CoreConfigType *const CoreConfigPtr)
{
  /*Pointer to store the SID configuration*/
  const Can_17_McmCan_SIDFilterConfigType *SIDPtr;

  /*Pointer to store the data configuration of SID filters*/
  volatile Ifx_CAN_STDMSG *SIDFilterPtr;

  /*Variable to store filter start address*/
  uint32 SIDFilterStartAddr;

  /*Variable to store actual filter address*/
  uint32 SIDFilterRealAddr;

  /*Filter start index*/
  uint16 SIDFiltrStartIndx;

  /*Filter end index*/
  uint16 SIDFiltrEndIndx;

  /*Filter index to loop through the multiple configured filters*/
  uint16 SIDFiltrIndx;

  /*Offset index*/
  uint8 SIDOffsetIndx;

  /* Set SID filter list Address */
  SIDPtr = CoreConfigPtr->CanSIDFilterConfigPtr;

  /* Set with first SID filter Index */
  SIDFiltrStartIndx = CoreConfigPtr->CanControllerConfigPtr[Controller].
                      CanControllerMOMap[CAN_17_MCMCAN_RX_SID_STARTINDEX];

  /* Set with End SID filter Index */
  SIDFiltrEndIndx = SIDFiltrStartIndx +
                              CoreConfigPtr->CanControllerConfigPtr[Controller].
                           CanControllerMOMap[CAN_17_MCMCAN_WU_PROCESSING_MODE];

  /* Read Standard Identifier filter Start address */
  SIDFilterStartAddr = CoreConfigPtr->
                                    CanControllerMsgRAMMapConfigPtr[Controller].
                                    CanControllerMsgRAMMap[CAN_17_MCMCAN_FLSSA];

  /* Set Offset with First element*/
  SIDOffsetIndx = 0U;

  /* Set with all standard filter configuration */
  for(SIDFiltrIndx = SIDFiltrStartIndx; SIDFiltrIndx <
                                               SIDFiltrEndIndx; SIDFiltrIndx++)
  {
    /* Set with Address of  filter element */
    SIDFilterRealAddr = SIDFilterStartAddr + ((uint32)SIDOffsetIndx *
                        CAN_17_MCMCAN_RAM_BYTES);

    /* MISRA2012_RULE_11_6_JUSTIFICATION: The pointer cast is used to
    cast the address to the standard filter elements  structure type for
    accessing RAM area */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: Memory address is generated as a
    numerical value, it is accessed as a pointer to the RAM address.
    Hence an explicit typecast from numerical to pointer. */
    /* Set with First filter element */
    SIDFilterPtr = (volatile Ifx_CAN_STDMSG *)SIDFilterRealAddr;

    /*If Pretended Network OFF*/
    /* [cover parentID={E8E3BA1D-7E50-4885-B16F-62105C59D949}]
    If Pretended Network OFF
    [/cover] */
    if (FALSE == SIDPtr[SIDFiltrIndx].CanSidPNSupport)
    {
      /* [cover parentID={DBD9B803-A86D-40fa-BA97-85B3621A7415}]
      Check for FIFO
      [/cover] */
      /*Update the standard filter value as per RX buffer or FIFO being used*/
      /* [cover parentID={53FC16D0-A99E-428e-AB99-38DD12AD3EFD}]
      FIFO1
      [/cover] */
      if (CAN_17_MCMCAN_RX_FIFO1 == SIDPtr[SIDFiltrIndx].CanSidBufferType)
      {
        /* Set to store in RXFIO1 */
        SIDFilterPtr->S0.B.SFEC = CAN_17_MCMCAN_MSGRAM_SHIFT_MASK;
      }
      /* [cover parentID={ED3B2416-802B-46ba-AAFD-5C8D84EE9324}]
      FIFO0
      [/cover] */
      else if (CAN_17_MCMCAN_RX_FIFO0 ==
              SIDPtr[SIDFiltrIndx].CanSidBufferType)
      {
        /* Set to store in RXFIO0 */
        SIDFilterPtr->S0.B.SFEC = CAN_17_MCMCAN_BIT_SET_VAL;
      }
      /* [cover parentID={55ABC19D-1C9F-4778-AA21-EF217DA699CC}]
      For Others
      [/cover] */
      else
      {
        /* Set to store in RX Dedicated buffer */
        SIDFilterPtr->S0.B.SFEC = IFX_CAN_STDMSG_S0_SFEC_MSK;
      }
    }
    /* Increment to access next element */
    SIDOffsetIndx++;
  }
}

/*******************************************************************************
** Traceability   : [cover parentID={FA9E315E-05BE-4b5c-9043-9AE6F1B2D663}]   **
**  Syntax           : static void Can_17_McmCan_lIcomXIDFilterConfiguration  **
**                     (const uint8 Controller,                               **
**                      const Can_17_McmCan_CoreConfigType *const ConfigPtr)  **
**                                                                            **
**  Description      : The function configures XID ICOM filter settings       **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant                                              **
**                                                                            **
**  Parameters (in)  : Controller - Associated CAN Controller                 **
**                    CoreConfigPtr - Pointer to CAN driver configuration     **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Parameters (in-out) : none                                                **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/

static void Can_17_McmCan_lIcomXIDFilterConfiguration(const uint8 Controller,
                        const Can_17_McmCan_CoreConfigType *const CoreConfigPtr)
{
  /*Variable to store filter start address*/
  uint32 XIDFilterStartAddr;

  /*Variable to store actual filter address*/
  uint32 XIDFilterRealAddr;

  /*Filter start index*/
  uint16 XIDFiltrStartIndx;

  /*Filter end index*/
  uint16 XIDFiltrEndIndx;

  /*Filter index to loop through the multiple configured filters*/
  uint16 XIDFiltrIndx;

  /*Offset index*/
  uint8 XIDOffsetIndx;

  /*Pointer to store the XID configuration*/
  const Can_17_McmCan_XIDFilterConfigType *XIDPtr;

  /*Pointer to store the data configuration of SID filters*/
  volatile Ifx_CAN_EXTMSG *XIDFilterPtr;

  /* Set with XID filter list configuration address */
  XIDPtr = CoreConfigPtr->CanXIDFilterConfigPtr;

  /* Read Extended Identifier filter Start address */
  XIDFilterStartAddr =
                     CoreConfigPtr->CanControllerMsgRAMMapConfigPtr[Controller].
                                    CanControllerMsgRAMMap[CAN_17_MCMCAN_FLSEA];
  /* Set with start Index */
  XIDFiltrStartIndx = CoreConfigPtr->CanControllerConfigPtr[Controller].
                      CanControllerMOMap[CAN_17_MCMCAN_RX_XID_STARTINDEX];
  /* Set with end Index */
  XIDFiltrEndIndx = XIDFiltrStartIndx +
                              CoreConfigPtr->CanControllerConfigPtr[Controller].
                               CanControllerMOMap[CAN_17_MCMCAN_TOTAL_XIDCFG];

  /* Set Offset with first element */
  XIDOffsetIndx = 0U;

  /* Set with all Extended filter configuration */
  for (XIDFiltrIndx = XIDFiltrStartIndx; XIDFiltrIndx < XIDFiltrEndIndx;
                                                                 XIDFiltrIndx++)
  {
    /* Set with offset of XID filter element */
    XIDFilterRealAddr = XIDFilterStartAddr +
                        ((uint32)CAN_17_MCMCAN_FILTER_ADDR_VAL *
                        (uint32)XIDOffsetIndx);

    /* Set with First filter element */
    /* MISRA2012_RULE_11_6_JUSTIFICATION: The pointer cast is used to
    cast the address to the extended filter elements  structure type for
    accessing RAM area */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: Memory address is generated as a
    numerical value, it is accessed as a pointer to the RAM address.
    Hence an explicit typecast from numerical to pointer. */
    XIDFilterPtr = (volatile Ifx_CAN_EXTMSG *)XIDFilterRealAddr;

    /*If Pretended Network OFF*/
    /* [cover parentID={5DB99C4F-A201-4012-9B37-93D044954005}]
    If Pretended Network OFF
    [/cover] */
    if (FALSE == XIDPtr[XIDFiltrIndx].CanXidPNSupport)
    {
       /* [cover parentID={0A24EFBC-D889-4a87-A59A-4839B077C7EC}]
       FIFO1
      [/cover] */
      if (CAN_17_MCMCAN_RX_FIFO1 == XIDPtr[XIDFiltrIndx].CanXidBufferType)
      {
        /* Set to store in RXFIO1 */
        XIDFilterPtr->F0.B.EFEC = CAN_17_MCMCAN_FIFO_EFEC_MASK;
      }
      /* [cover parentID={3F015E97-6D67-4bbf-8EAB-02EDC948267A}]
      FIFO0
      [/cover] */
      else if (CAN_17_MCMCAN_RX_FIFO0 ==
              XIDPtr[XIDFiltrIndx].CanXidBufferType)
      {
        /* Set to store in RXFIO0 */
        XIDFilterPtr->F0.B.EFEC = CAN_17_MCMCAN_BIT_SET_VAL;
      }
      /* [cover parentID={9247EB9C-7691-41ad-80F2-F6390E8A822D}]
      For Others
      [/cover] */
      else
      {
        /* Set to store in RX Dedicated buffer */
        XIDFilterPtr->F0.B.EFEC = CAN_17_MCMCAN_RXDED_EFEC_MASK;
      }
    }
    /* increment to access next element */
    XIDOffsetIndx++;
  }
}

/*******************************************************************************
** Traceability   : [cover parentID={59278E5B-418E-4beb-B6C8-F2F6D8237C2D}]   **
**  Syntax          :static void Can_17_McmCan_lIcomValidateMsg               **
**                   (                                                        **
**                      Can_HwType *const Mailbox,                            **
**                      const PduInfoType *const PduInfoPtr,                  **
**                      Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,    **
**                      const Can_17_McmCan_CoreConfigType *const CoreConfigPtr*
**                   )                                                        **
**                                                                            **
** Description    :This internal function is used to validate whether the     **
**                 received signal is capable for the deactivation of ICOM    **
**                 or not. The function will check the received message and   **
**                 if the condition is matching with any of the configured    **
**                 CanIcomWakeupCauses then only  will inform to the upper    **
**                 layer with call back CanIf_RxIndication.()                 **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant                                              **
**                                                                            **
**  Parameters (in)  : Mailbox    : Included Received Message ID,HOH          **
**                                 and Controller Id                          **
**                    PduInfoPtr : Included SDU length and Data pointer       **
**                    CoreConfigPtr - Pointer to CAN driver configuration     **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Parameters (in-out) : CoreGlobalPtr - Pointer to global structure         **
**                                                                            **
**  Return value     :E_OK : The WakeUp condition is caused                   **
**                    E_NOT_OK : The WakeUp condition is not caused           **
**                                                                            **
*******************************************************************************/
static void Can_17_McmCan_lIcomValidateMsg(Can_HwType *const MailboxPtr,
                        const PduInfoType *const PduInfoPtr,
                        const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr,
                        const Can_17_McmCan_CoreConfigType *const CoreConfigPtr)
{
  /*ICOM RX Msg ID*/
  Can_IdType IcomRxMsgId;

  /*Variable to store the ICOM meassage ID which is to be validated against*/
  Can_IdType IcomCheckMsgId;

  /*Message index of the ICOM message ID*/
  uint16 IcomMsgIndex;

  /*Incoming Message index*/
  uint16 MsgIndex;

  /*Total number of ICOM recieve message configured*/
  uint16 IcomNoOfRxMsg;

  /*ICOM configuration iD*/
  uint8 IcomConfigId;

  /*CAN controller ID*/
  uint8 ControllerId;

  /*Can If RX indication status*/
  Std_ReturnType RxIndicationStatus = E_NOT_OK;
  Std_ReturnType ApiStatus;

  /* Set with Controller Configuration Id */
  ControllerId = MailboxPtr->ControllerId;

  /* Get ICOM configuration ID*/
  IcomConfigId = CoreGlobalPtr->CanActiveIcomCfgIdPtr[ControllerId];

  /* Get the first receive configuration index */
  IcomMsgIndex = Can_17_McmCan_kGblConfigPtr->CanIcomConfigPtr
                 [IcomConfigId - 1U].CanIcomFirstMsgIndx;

  /* Get the total number of ICOM Receive messages configured*/
  IcomNoOfRxMsg = Can_17_McmCan_kGblConfigPtr->CanIcomConfigPtr
                  [IcomConfigId - 1U].CanIcomNoOfMsgIndx;

  /* Set with First index value */
  MsgIndex = IcomMsgIndex;

  while (MsgIndex < (IcomMsgIndex + IcomNoOfRxMsg))
  {
    /* Set with Icom Rx message Id */
    IcomRxMsgId = MailboxPtr->CanId & ~(CAN_17_MCMCAN_SET_XTD_BIT_MASK);

    /* check if CanIcomMessageIdMask is configured */
    /* [cover parentID={7FCE3062-4F0E-42f9-8D63-BFBB915127D4}]
    Check CanIcomMessageIdMask is configured
    [/cover] */
    if (CAN_17_MCMCAN_MSG_MASK != Can_17_McmCan_kGblConfigPtr->
                                   CanIcomMsgConfigPtr[MsgIndex].CanIcomMaskRef)
    {
      /* Mask the received message ID with the ICOM Message Id mask */
      IcomRxMsgId &= (Can_17_McmCan_kGblConfigPtr->
                     CanIcomMsgConfigPtr[MsgIndex].CanIcomMaskRef);

      IcomCheckMsgId = (Can_17_McmCan_kGblConfigPtr->
                        CanIcomMsgConfigPtr[MsgIndex].CanIcomMsgId &
                         Can_17_McmCan_kGblConfigPtr->
                         CanIcomMsgConfigPtr[MsgIndex].CanIcomMaskRef);
    }
    else
    {
      IcomCheckMsgId = Can_17_McmCan_kGblConfigPtr->
                        CanIcomMsgConfigPtr[MsgIndex].CanIcomMsgId;
    }
    /* Compare Masked id with configured Id */
    /* [cover parentID={20A7B80B-4B45-4249-A1D9-005D2A4E3234}]
    Compare Masked id with configured Id
    [/cover] */
    if (IcomRxMsgId == IcomCheckMsgId)
    {
      /* Compare payload length(DLC)and if mismatch set as wake-up */
      /* [cover parentID={670F2400-E590-4930-BD2C-08C2B8FE8951}]
      Check payload length match
      [/cover] */
      if (PduInfoPtr->SduLength ==
          Can_17_McmCan_kGblConfigPtr->CanIcomMsgConfigPtr[MsgIndex].CanIcomDLC)
      {
        RxIndicationStatus = E_OK;
        ApiStatus = E_OK;
      }
      else
      {
        /* Set Status as Wakeup condition cause */
        /* [cover parentID={3193029F-59A3-4683-9006-5BCDB27C4AC6}]
        Check if WAKEUP conditio cause is TRUE?
        [/cover] */
        if (TRUE ==
            Can_17_McmCan_kGblConfigPtr->CanIcomMsgConfigPtr[MsgIndex].
            CanIcomLengthErr)
        {
          RxIndicationStatus = E_OK;
          ApiStatus = E_NOT_OK;
        }
        else
        {
          RxIndicationStatus = E_NOT_OK;
          ApiStatus = E_NOT_OK;
        }
      }
      /* [cover parentID={D088A1AF-E79D-488e-8523-1328EC6F754D}]
      signal comparison required
      [/cover] */
      if ((E_OK == ApiStatus) && (CAN_17_MCMCAN_BIT_RESET_VAL !=
                                  Can_17_McmCan_kGblConfigPtr->
                                  CanIcomMsgConfigPtr[MsgIndex].
                                  CanIcomNoOfSignalIndx))
      {
        /* Invoke function for Message signal validation */
        ApiStatus = Can_17_McmCan_lIcomValidateMsgSignal(
                             MsgIndex, PduInfoPtr, Can_17_McmCan_kGblConfigPtr);
        RxIndicationStatus = ApiStatus;
      }
      /* Check counter value is configured or not */
      /* [cover parentID={8F95B2D2-2799-4dfa-9D20-D8A6903FDC1E}]
      Message counter configured
      [/cover] */
      /* [cover parentID={45648DCE-4474-45bf-836F-76DAA4681C09}]
      Message signal match
      [/cover] */
      if ((E_OK == ApiStatus) && (0U != Can_17_McmCan_kGblConfigPtr->
                                 CanIcomMsgConfigPtr[MsgIndex].CanIcomCntrVal))
      {
        /*Enter critical sections*/
        /* [cover parentID={0A9EAA04-D385-4ef4-8108-238A62EEFD73}]
        Enter Critical Section
        [/cover] */
        SchM_Enter_Can_17_McmCan_IcomMsgCntrVal();

        /* Increment Message Counter Value */
        CoreGlobalPtr->CanIcomMsgCntrValPtr[MsgIndex]++;

        /* Check if the message with the ID is received n times on the
        communication channel. */
        /* [cover parentID={260D89D2-2DEF-4358-B480-ED98DD35D2A1}]
        Reception of messages for configured n times
        [/cover] */
        if (Can_17_McmCan_kGblConfigPtr->CanIcomMsgConfigPtr[MsgIndex].
            CanIcomCntrVal == CoreGlobalPtr->CanIcomMsgCntrValPtr[MsgIndex])
        {
          /* Set Status as Wakeup condition cause */
          RxIndicationStatus = E_OK;
          CoreGlobalPtr->CanIcomMsgCntrValPtr[MsgIndex] = 0U;
        }
        else
        {
          /* reset Wake up cause till counter value matches */
          RxIndicationStatus = E_NOT_OK;
        }

        /*Exit critical section*/
        /* [cover parentID={3F1C9B7C-A301-4948-A797-29EA14D9E24E}]
        Exit the critical section
        [/cover] */
        SchM_Exit_Can_17_McmCan_IcomMsgCntrVal();
      }

      /* Set Exit condition if Wakeup Cause is enabled */
      /* [cover parentID={EDAE206E-D3CF-40e8-9776-3DE465292239}]
      Is status E_OK?
      [/cover] */
      if (E_OK == RxIndicationStatus)
      {
        /* Update mail box info with logical controller ID value */
        MailboxPtr->ControllerId =
                          CoreConfigPtr->CanControllerIndexingPtr[ControllerId];

        /* Call CanIf_RxIndication received message matches the wakeup */
        /* [cover parentID={397CDE2A-64F0-4cec-B81E-42DF58B135BD}]
        Call CanIf_RxIndication received message matches the wakeup
        [/cover] */
        CanIf_RxIndication(MailboxPtr, PduInfoPtr);

        /* Set Exit Condition */
        MsgIndex = (IcomMsgIndex + IcomNoOfRxMsg);
      }
    }

    /* Increment to point next Message configuration*/
    MsgIndex++;
  }
}

/*******************************************************************************
** Traceability   : [cover parentID={A3BCA435-BA18-4435-B958-3572375DFFF9}]   **
**  Syntax           :  static Std_ReturnType                                 **
**                      Can_17_McmCan_lIcomCheckGreaterSmaller                **
**                     (                                                      **
**                       const uint8 ValData,const uint8 ConfigData,          **
**                       uint8 *const CheckValPtr,                            **
**                       const Can_17_McmCan_IcomSignalOperType SignalOperType)*
**                     )                                                      **
**                                                                            **
**  Description      : Validates the received message Signal values for       **
**                     the greater and lesser wakeup conditions.              **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant                                              **
**                                                                            **
**  Parameters (in)  : ValData - Signal index of the configuration message    **
**                                    to be compared with                     **
**                     ConfigData - Pointer to the information of received    **
**                                   LPDU                                     **
**                     CheckValPtr - Pointer to CAN driver configuration      **
**                     SignalOperType -
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : E_OK : Signal and mask payload data is correct         **
**                    E_NOT_OK : Signal and mask payload data is incorrect    **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Can_17_McmCan_lIcomCheckGreaterSmaller(
    const uint8 ValData, const uint8 ConfigData,
    uint8 *const CheckValPtr,
    const Can_17_McmCan_IcomSignalOperType SignalOperType)
{
  /* Function return value */
  Std_ReturnType RetVal = E_NOT_OK;

  /*Is SignalOperType is Greater*/
  /* [cover parentID={4268D730-023D-44b7-AED0-5636D62E3096}]
  Check the signal operation type
  [/cover] */
  if (CAN_17_MCMCAN_ICOM_OPER_GREATER == SignalOperType)
  {
    /* Verify the signal value and masked payload data */
    /*Data in is lesser than compare value*/

    /* [cover parentID={E3F306D6-0C45-4d77-BCB9-0E0293CAC375}]
    Data in is lesser than compare value
    [/cover] */
    if (ValData < ConfigData)
    {
      (*CheckValPtr)++;
    }

    /*Data in is greater than compare value*/
    /* [cover parentID={818C40E3-4242-4774-AC95-0A2C874EC77C}]
    Data in is greater than compare value
    [/cover] */
    else if ((ValData > ConfigData) &&
    (CAN_17_MCMCAN_BIT_RESET_VAL == (*CheckValPtr)))
    {
      RetVal = E_OK;
    }
    else
    {
      /* Do Nothing */
    }
  }

  /*Is SignalOperType is Smaller*/
  else
  {
    /* Verify the signal value and masked payload data */
    /* [cover parentID={8B9BFF52-0282-4bf5-B356-46D316416BB9}]
    Data in is greater than compare value
    [/cover] */
    if (ValData > ConfigData)
    {
      (*CheckValPtr)++;
    }

    /*Data in is lesser than compare value*/
    /* [cover parentID={77E7A7AC-DCE7-4dda-859B-088E6BFF919C}]
    Data in is lesser than compare value
    [/cover] */
    else if ((ValData < ConfigData) &&
    (CAN_17_MCMCAN_BIT_RESET_VAL == (*CheckValPtr)))
    {
      RetVal = E_OK;
    }
    else
    {
      /* Do Nothing */
    }
  }
  return RetVal;
}

/*******************************************************************************
** Traceability   : [cover parentID={728ADB13-2277-4569-BBED-C6598A5BA794}]   **
**  Syntax           :  static Std_ReturnType                                 **
**                      Can_17_McmCan_lIcomValidateMsgSignal                  **
**                     (                                                      **
**                        const uint16 MessageIndex,                          **
**                        const PduInfoType *const PduInfoPtr,                **
**                        const Can_17_McmCan_ConfigType *const ConfigPtr     **
**                     )                                                      **
**                                                                            **
** Description    :The function is used for validate whether the received     **
**                 signal is capable for the deactivation of ICOM or not.     **
**                 The function will check the If at least one Signal         **
**                 conditions defined in a CanIcomRxMessageSignalConfig       **
**                 evaluates to true then only will return with               **
**                 E_OK else E_NOT_OK                                         **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant                                              **
**                                                                            **
**  Parameters (in)  : MessageIndex : Signal Wakeup cause check corresponding **
**                                   Message configuration index              **
**                    PduInfoPtr   : Pointer to the information of received   **
**                                   LPDU                                     **
**                    ConfigPtr - Pointer to CAN driver configuration         **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     :E_OK : The WakeUp condition is caused                   **
**                    E_NOT_OK : The WakeUp condition is not caused           **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Can_17_McmCan_lIcomValidateMsgSignal(
                                                      const uint16 MessageIndex,
                                            const PduInfoType *const PduInfoPtr,
                                const Can_17_McmCan_ConfigType *const ConfigPtr)
{
  /*Variable to traverse through ICOM signal index*/
  uint32 SignalIndex;

  /*First ICOM signal index*/
  uint16 FirstSignalIndex;

  /*Second ICOM signal index*/
  uint16 EndSignalIndex;

  /*Number of message signals*/
  uint16 NoOfMsgSignal;

  /*Message counter fr number of bytes to checked*/
  uint8 MsgCtr;

  /*Data index value*/
  uint8 DataIndex;

  /*Data counter value*/
  uint8 DataCnt;

  /*Index to compare with the message counter*/
  uint8 CheckIndex;

  /*Temporary array to store the data and payload*/
  uint8 TempData[CAN_17_MCMCAN_DATALENTH_VAL];

  /*Return value of the function*/
  Std_ReturnType ReturnValue = E_NOT_OK;

  /* Initialize the temporary array */
  for (DataIndex = 0U; DataIndex < CAN_17_MCMCAN_DATALENTH_VAL; DataIndex++)
  {
    TempData[DataIndex] = 0U;
  }

  /* First signal index */
  FirstSignalIndex = ConfigPtr->
                     CanIcomMsgConfigPtr[MessageIndex].CanIcomFirstSignalIndx;

  /* No of signal configuration */
  NoOfMsgSignal = ConfigPtr->
                  CanIcomMsgConfigPtr[MessageIndex].CanIcomNoOfSignalIndx;

  /* Number of bytes to be checked */
  MsgCtr = ConfigPtr->CanIcomMsgConfigPtr[MessageIndex].CanIcomDLC;

  EndSignalIndex = FirstSignalIndex + NoOfMsgSignal;

  /* Message signal validation */
  for (SignalIndex = FirstSignalIndex; SignalIndex < EndSignalIndex;
                                                                 SignalIndex++)
  {
    /*Initialize check index */
    CheckIndex = 0U;

    /*MISRA2012_RULE_1_3_JUSTIFICATION:Address of auto variable is used
    only to read the values. The address is not used to perform any
    pointer arithmetic. hence no side effect has been seen.*/
    uint8 *CheckIndexPtr = &CheckIndex;

    DataCnt = MsgCtr;

    /*Reception of messages for configured n times*/
    while (0U != DataCnt)
    {
      DataIndex = DataCnt - 1U;
      DataCnt--;
      /* Mask the received payload and signal mask value */
      TempData[DataIndex] = (PduInfoPtr->SduDataPtr[DataIndex] &
                              (ConfigPtr->CanIcomRxSignalConfigPtr[SignalIndex].
                                CanIcomSignalMask[DataIndex]));
      /* Get the Signal operation */

      switch (ConfigPtr->
                  CanIcomRxSignalConfigPtr[SignalIndex].CanIcomSignalOper)
      {

        /*The ICOM signal operation is AND*/
        /* [cover parentID={3035480D-FFD2-4be8-93E9-3A9945ED2CF0}]
        The ICOM signal operation is AND
        [/cover] */
        case CAN_17_MCMCAN_ICOM_OPER_AND:
        {
          /* Verify the signal value and masked payload data */
          /* [cover parentID={FC150B53-99DD-48ce-BF32-0E3D01A27D6E}]
         Verify that the signal value and masked payload data when ANDed with
         the first signal data index give a NON ZERO value
          [/cover] */
          if (CAN_17_MCMCAN_BIT_RESET_VAL != (TempData[DataIndex] &
                            (ConfigPtr->CanIcomRxSignalConfigPtr[SignalIndex].
                                      CanIcomSignalValue[DataIndex])))
          {
            ReturnValue = E_OK;
          }
        }
        break;

        /* Verify the signal value and masked payload data */
        /* [cover parentID={A06F59E0-00A6-4813-8EA0-ADE12DBC856E}]
        The ICOM signal operation is EQUAL
        [/cover] */
        case CAN_17_MCMCAN_ICOM_OPER_EQUAL:
        {
          /* Verify the signal value and masked payload data */
          /* [cover parentID={F1FFF568-488F-4246-AA49-6A856E037E26}]
          Verify that the signal value and masked payload data is EQUAL to
          the ICOM signal value of the first signal index for the data Indexed
          [/cover] */
          if (TempData[DataIndex] ==
                           (ConfigPtr->CanIcomRxSignalConfigPtr[SignalIndex].
                                               CanIcomSignalValue[DataIndex]))
          {
            CheckIndex++;
          }

          /*Message counter configured*/
        if (CheckIndex == MsgCtr)
          {
            ReturnValue = E_OK;
          }
        }
        break;
        /*The ICOM signal operation is Greater*/
        /* [cover parentID={87F7972F-F16B-4831-AFF1-335EE9FB239A}]
        The ICOM signal operation is GREATER
        [/cover] */
        case CAN_17_MCMCAN_ICOM_OPER_GREATER:
        {
          /* [cover parentID={F83A3F5A-408E-46cb-960A-843D3AC6B10A}]
          Is Status ok ?
          [/cover] */
        if (E_NOT_OK == ReturnValue)
          {
          ReturnValue = Can_17_McmCan_lIcomCheckGreaterSmaller(
                        TempData[DataIndex],
                        (ConfigPtr->CanIcomRxSignalConfigPtr[SignalIndex].
                                               CanIcomSignalValue[DataIndex]),
                         CheckIndexPtr, CAN_17_MCMCAN_ICOM_OPER_GREATER);
          }
        }
        break;
        /*The ICOM signal operation is Smaller*/
        /* [cover parentID={40C6BAB3-243F-46e8-859F-0857FAA3D8DA}]
        The ICOM signal operation is SMALLER
        [/cover] */
        case CAN_17_MCMCAN_ICOM_OPER_SMALLER:
        {
          /* [cover parentID={A2265027-B208-4012-8497-AD99EF5B938C}]
          Is Status ok?
          [/cover] */
        if (E_NOT_OK == ReturnValue)
          {
            ReturnValue = Can_17_McmCan_lIcomCheckGreaterSmaller(
                        TempData[DataIndex], (ConfigPtr->
                                       CanIcomRxSignalConfigPtr[SignalIndex].
                                              CanIcomSignalValue[DataIndex]),
                        CheckIndexPtr, CAN_17_MCMCAN_ICOM_OPER_SMALLER);
          }
        }
        break;
        default:
        {
          /*Check if signal value and data when NORed gives valid value*/
          /* [cover parentID={A9027982-339E-47e4-B54D-05CD0CEF1382}]
          signal value and data when NORed if gives valid value
          [/cover] */
          if (CAN_17_MCMCAN_BIT_RESET_VAL != (TempData[DataIndex] ^
                             ConfigPtr->CanIcomRxSignalConfigPtr[SignalIndex].
                                              CanIcomSignalValue[DataIndex]))
          {
            ReturnValue = E_OK;
          }
        }
        break;
      }
    }
  }
  return ReturnValue;
}
#endif /* #if (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON) */
#if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON)
/*******************************Start of DET internal functions****************/
/*******************************************************************************
** Traceability   : [cover parentID={19795EB8-F799-445c-94A7-D709E980FBC6}]   **
**                                                                            **
**                                                                            **
** Syntax :        static Std_ReturnType Can_17_McmCan_lInitDetCheck          **
**                 ( const Can_17_McmCan_ConfigType *const ConfigPtr,         **
**                   const uint8 CoreIndex )                                  **
**                                                                            **
** Description :    The function checks master-slave core initialization      **
**                  sequence or if the CAN controllers are configured to the  **
**                  particular core                                           **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Non Reentrant                                           **
**                                                                            **
** Parameters (in):   ConfigPtr - CAN config pointer                          **
**                    CoreIndex  - Core which is calling this function        **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:      Std_ReturnType: status of DET.                          **
**  Return value     : E_OK: No error reported and DET is not triggered       **
**                     E_NOT_OK: Error reported and DET is triggered          **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Can_17_McmCan_lInitDetCheck(
    const Can_17_McmCan_ConfigType *const ConfigPtr,
    const uint8 CoreIndex)
{
  /*Return value of the function*/
  Std_ReturnType ReturnValue = E_OK;

  /*Variable to store current core initialization status*/
  uint32 ExpInitStatus;

  #if (CAN_17_MCMCAN_MULTICORE_ERROR_DETECT == STD_ON)

  /*Variable to store master core initialization status*/
  uint32 MasterCoreStatus;

  #endif


  /*Check if the Config pointer passed is NULL*/
  /* [cover parentID={AFC75F27-5860-4ac2-9C9D-4ECAF1B38F2D}]
  Check if the pointer is NULL
  [/cover] */
  if (NULL_PTR == ConfigPtr)
  {
    /*Report Error, Init has been called with wrong parameter
    NULL Config Pointer */
    /* [cover parentID={0B962D30-099E-4a4b-8E2C-BCD0F4DE2EDF}]
    Report Error CAN_17_MCMCAN_E_INIT_FAILED
    [/cover] */
    (void)Det_ReportError(CAN_17_MCMCAN_MODULE_ID, CAN_17_MCMCAN_INSTANCE_ID,
                    CAN_17_MCMCAN_SID_INIT, CAN_17_MCMCAN_E_INIT_FAILED);

    ReturnValue = E_NOT_OK;
  }

  /*Check if multicore error detect is ON*/
  #if (CAN_17_MCMCAN_MULTICORE_ERROR_DETECT == STD_ON)

  /* Check if current core is slave core */
  /* [cover parentID={2EF7682E-4DAE-4dc5-BF3A-F54F1DEDD108}]
  If current core is slave
  [/cover] */
  else if (MCAL_MASTER_COREID != CoreIndex)
  {
    /*Retrieve initialization status of master core*/
    MasterCoreStatus =
          (Can_17_McmCan_InitStatus >> ((uint32)MCAL_MASTER_COREID *
          (uint32)CAN_17_MCMCAN_INIT_STATUS_SIZE)) & 1U;
    /*Check if the core is already initialized*/
    /* [cover parentID={9FCB486F-7866-474e-9621-D78D124E5378}]
    Is master core is initialized
    [/cover] */
    if ((uint32)CAN_17_MCMCAN_DRV_READY != MasterCoreStatus)
    {
      /* Report error */
      /* [cover parentID={8176EBEA-757B-43d7-BC3E-1DFEC0BA802F}]
      Report Error CAN_17_MCMCAN_E_MASTER_CORE_UNINIT
      [/cover] */
      (void)Det_ReportError(CAN_17_MCMCAN_MODULE_ID, CAN_17_MCMCAN_INSTANCE_ID,
                            CAN_17_MCMCAN_SID_INIT,
                            CAN_17_MCMCAN_E_MASTER_CORE_UNINIT);

      ReturnValue = E_NOT_OK;
    }
    /* Check if config ptr is same as master core */
    /* [cover parentID={262A989B-2938-4e77-8CBB-09C4786036B7}]
    If config ptr is same as master core
    [/cover] */
    else if (Can_17_McmCan_kGblConfigPtr != ConfigPtr)
    {
      /* [cover parentID={FF84B51F-837D-4b45-801D-462D5D647425}]
      Det error CAN_17_MCMCAN_E_INIT_FAILED
      [/cover] */
      (void)Det_ReportError(CAN_17_MCMCAN_MODULE_ID, CAN_17_MCMCAN_INSTANCE_ID,
                           CAN_17_MCMCAN_SID_INIT, CAN_17_MCMCAN_E_INIT_FAILED);

      ReturnValue = E_NOT_OK;
    }
    /* Check if core is configured */
    /* [cover parentID={D6915A11-622A-4ac4-A117-7F00336FB2A1}]
    if core is configured
    [/cover] */
    else if (NULL_PTR == Can_17_McmCan_kGblConfigPtr->
                            CanCoreConfigPtr[CoreIndex])
    {
      /* Report Error */
      /* [cover parentID={57B0CDA5-A90D-47a1-954C-610EDE1A6889}]
      Report Error CAN_17_MCMCAN_E_NOT_CONFIGURED
      [/cover] */
      (void)Det_ReportError(CAN_17_MCMCAN_MODULE_ID, CAN_17_MCMCAN_INSTANCE_ID,
                            CAN_17_MCMCAN_SID_INIT,
                            CAN_17_MCMCAN_E_NOT_CONFIGURED);

      ReturnValue = E_NOT_OK;
    }
    else
    {
      /*Do nothing*/
    }
  }
  #endif /* #if (CAN_17_MCMCAN_MULTICORE_ERROR_DETECT == STD_ON) */
  else
  {
    /*Do nothing*/
  }
  /* [cover parentID={545ACBF1-A513-4b28-9044-E15771BB30DC}]
  Check if the core is already initialized
  [/cover] */
    /*Retrieve initialization status of current executing core*/
  ExpInitStatus = (Can_17_McmCan_InitStatus >> ((uint32)CoreIndex *
                  (uint32)CAN_17_MCMCAN_INIT_STATUS_SIZE)) & 1U;

  if ((uint32)CAN_17_MCMCAN_DRV_READY == ExpInitStatus)
  {

    /* Report Error */
    /* [cover parentID={730A153B-CF7D-456c-8CD2-032476BB5C1F}]
    Report Error CAN_17_MCMCAN_E_TRANSITION
    [/cover] */
    (void)Det_ReportError(CAN_17_MCMCAN_MODULE_ID, CAN_17_MCMCAN_INSTANCE_ID,
                    CAN_17_MCMCAN_SID_INIT, CAN_17_MCMCAN_E_TRANSITION);

    ReturnValue = E_NOT_OK;
  }
  else
  {
    /*Do nothing*/
  }
  return ReturnValue;
}

/*******************************************************************************
** Traceability   : [cover parentID={27564589-7252-4c12-B807-C6A1CA28D45B}]   **
**  Syntax           : static Std_ReturnType Can_17_McmCan_lDetUninitConfig   **
**                    (                                                       **
**                      const uint8 ServiceID,                                **
**                      const uint8 CoreIndex                                 **
**                    )                                                       **
**                                                                            **
**  Description      :The function checks the status of CAN driver            **
**                    initialization. If CAN driver is not initialized,       **
**                    reports to DET and  returns E_NOT_OK                    **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant                                              **
**                                                                            **
**  Parameters (in)  : ServiceId - Service Id of the calling API              **
**                     CoreIndex - Executing core ID                          **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : E_OK: CAN Driver is initialized                        **
**                  - E_NOT_OK: CAN Driver is not initialized                 **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Can_17_McmCan_lDetUninitConfig(
    const uint8 ServiceID, const uint8 CoreIndex)
{
  Std_ReturnType ReturnValue = E_NOT_OK;

  uint32 ExpInitStatus;

  /* Check if CAN driver is un-initialized */
  ExpInitStatus = (Can_17_McmCan_InitStatus >> ((uint32)CoreIndex *
                  (uint32)CAN_17_MCMCAN_INIT_STATUS_SIZE)) & 1U;

  /* [cover parentID={18C37795-B9DA-482d-83B4-0FB9AE5AE239}]
  Is CAN Driver Uninitialized?
  [/cover] */
  if ((uint32)CAN_17_MCMCAN_DRV_READY == ExpInitStatus)
  {
    /* Set as Drv state as Initialized*/
    ReturnValue = E_OK;
  }
  else
  {

    /* Report to DET */
    /* [cover parentID={68CAAF84-82ED-4b4e-BB5F-6D9938FA03CC}]
    Report Error CAN_17_MCMCAN_E_UNINIT
    [/cover] */
    (void)Det_ReportError(CAN_17_MCMCAN_MODULE_ID, CAN_17_MCMCAN_INSTANCE_ID,
                    ServiceID, CAN_17_MCMCAN_E_UNINIT);
    /* Set as Drv state as Initialized*/
    ReturnValue = E_NOT_OK;
  }
  return ReturnValue;
}

/*CYCLOMATIC_Can_17_McmCan_lModeDetCheck_JUSTIFICATION: This Function has a
cyclomatic Complexity of 16 because this function handles the DET checks of both
AUTOSAR versions of Mode transition checks. All checks are implemented as part
of this function and more redable to have it in single function. Also this
function is implemented using a switch case which makes it run only one of
the condition in each call.
*/
/*******************************************************************************
** Traceability   : [cover parentID={F3DCE1FB-C794-4cc3-9BA4-9E35206F6847}]   **
**                                                                            **
**  Syntax          : static Std_ReturnType Can_17_McmCan_lModeDetCheck       **
**                    (const uint8 Controller,                                **
**                     const Can_17_McmCan_ControllerState Transition,        **
**                     const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr)*
**                                                                            **
**  Description      : The function checks the validity of software triggered **
**                    CAN Controller state transition                         **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Non-Reentrant                                          **
**                                                                            **
**  Parameters (in)  :Controller - Associated CAN Controller Id               **
**                    Transition - Requested transition                       **
**                    CoreGlobalPtr - Pointer to global structure             **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : E_OK - Valid transition                                **
**                    E_NOT_OK - Invalid transition                           **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Can_17_McmCan_lModeDetCheck(const uint8 Controller,
    const Can_17_McmCan_ControllerState Transition,
    const Can_17_McmCan_CoreGlobalType *const CoreGlobalPtr)
{
  /*Return value of the function*/
  Std_ReturnType ReturnValue = E_NOT_OK;

  /*Check if the source and target transitions are valid as per the CAN
  controller state machine*/
  switch (Transition)
  {
    /*Check if current mode is  START. */
    #if (MCAL_AR_VERSION == MCAL_AR_422)
    /* [cover parentID={460052F2-FC60-41de-A2D3-1356A3BD22BE}]
    Transition value has requested state START
    [/cover] */
    case CAN_T_START:
    #else
    case CAN_CS_STARTED:
    #endif
    {
      /* Valid transition is to START -> STOPPED */
      /* [cover parentID={5923BF72-0BF1-4c64-804E-A5090E2B5A2A}]
      Current mode is STOPPED
      [/cover] */
      if (CAN_17_MCMCAN_STOPPED ==
                               CoreGlobalPtr->CanControllerModePtr[Controller])
      {
        ReturnValue = E_OK;
      }
    }
    break;

    /* Check if current mode is  SLEEP */
    #if (MCAL_AR_VERSION == MCAL_AR_422)
    /* [cover parentID={1D410320-C7C2-488f-809E-65EBD8FE9D21}]
    Transition value has requested state SLEEP
    [/cover] */
    case CAN_T_SLEEP:
    #else
    case CAN_CS_SLEEP:
    #endif
    {
      /* Valid transition is to SLEEP -> SLEEP, STOPPED -> SLEEP */
      /* [cover parentID={3343288B-3C63-4861-9A74-322D38B97B2E}]
      Current mode is STOPPED or SLEEP
      [/cover] */
    if ((CAN_17_MCMCAN_STOPPED ==
         CoreGlobalPtr->CanControllerModePtr[Controller]) ||
        (CAN_17_MCMCAN_SLEEP ==
                               CoreGlobalPtr->CanControllerModePtr[Controller]))
      {
        ReturnValue = E_OK;
      }
    }
    break;
    /* Check if current mode is  STOPPED */
    #if (MCAL_AR_VERSION == MCAL_AR_422)
    /* [cover parentID={96CB087E-4C25-4881-AAA7-17CAC4A30B90}]
    Transition value has requested state STOP
    [/cover] */
    case CAN_T_STOP:
    #else
    case CAN_CS_STOPPED:
    #endif /* (MCAL_AR_VERSION == MCAL_AR_422) */
    {
      /* Valid transition is to START -> STOPPED
      STOPPED -> STOPPED, SLEEP -> STOPPED */
      /*UNINIT -> STOPPED is through Can_Init only*/
      /* [cover parentID={F5240431-CB29-4040-8E13-15D29693722E}]
      Current mode is not UNINIT or SLEEP
      [/cover] */
    #if (MCAL_AR_VERSION == MCAL_AR_422)
    if (CAN_17_MCMCAN_SLEEP !=
                            CoreGlobalPtr->CanControllerModePtr[Controller])
    #endif
      {
        ReturnValue = E_OK;
      }
    }
    break;
    /* Check if current mode is  UNINIT */
    #if (MCAL_AR_VERSION == MCAL_AR_422)
    /* [cover parentID={D56EFC3C-497C-4541-9927-EBF8A0C9283B}]
    Transition value has requested state WAKEUP
    [/cover] */
    case CAN_T_WAKEUP:
    {
      /* In AUTOSAR 4.2.2, transition is allowed only if the controllers are in
      SLEEP/ STARTED state. The hardware does not support wakeup*/
      /* [cover parentID={5D0E3B19-8273-41ee-8647-4F2ED32F19EC}]
      Current mode is STOPPED or SLEEP
      [/cover] */
      if ((CAN_17_MCMCAN_SLEEP ==
         CoreGlobalPtr->CanControllerModePtr[Controller]) ||
        (CAN_17_MCMCAN_STOPPED ==
                              CoreGlobalPtr->CanControllerModePtr[Controller]))
      {
        ReturnValue = E_OK;
      }
    }
    break;
    /*Check if the current mode is UNINIT*/
    #else
    /* [cover parentID={C6F5955E-DA44-4959-AD92-8B00FE708643}]
    Transition value requested state is UNINIT
    [/cover] */
    case CAN_CS_UNINIT:
    {
      /*In AUTOSAR 4.4.0, transition to UNINIT from SLEEP/STOPPED is only
      Can_DeInit and Can_Init respectively*/
      ReturnValue = E_NOT_OK;
    }
    break;
    #endif
    default:
    {
      /* Invalid state is requested */
    }
    break;
  }
  if (E_NOT_OK == ReturnValue)
  {
    /* Report invalid transition request to DET */
    /* [cover parentID={2D27662F-B422-4d24-B1E5-A0BFFA7AAF18}]
    Det error CAN_17_MCMCAN_E_TRANSITION
    [/cover] */
    (void)Det_ReportError(CAN_17_MCMCAN_MODULE_ID, CAN_17_MCMCAN_INSTANCE_ID,
                    CAN_17_MCMCAN_SID_SETCONTROLLERMODE,
                    CAN_17_MCMCAN_E_TRANSITION);
  }
  return ReturnValue;
}

/*******************************************************************************
** Traceability   : [cover parentID={0AF2E988-8777-42b0-85BF-5C11C6C82B41}]   **
**                                                                            **
**  Syntax           :static Std_ReturnType Can_17_McmCan_lDetDataLength      **
**                    (void)                                                  **
**                                                                            **
**  Description      : The function reports data length errors as per the     **
**                     error IDs defined in the AUTOSAR versions              **
**                                                                            **
**  [/cover]                                                                  **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant                                              **
**                                                                            **
**  Parameters(in)   : none                                                   **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : none                                                   **
*******************************************************************************/

static void Can_17_McmCan_lDetDataLength(void)
{
  /*AUTOSAR 4.2.2 has the error ID as CAN_17_MCMCAN_E_PARAM_DLC*/
  /* [cover parentID={5EC85405-ECB7-4e61-9DB2-A544BDFE1585}]
  If AUTOSAR version is 4.2.2
  [/cover] */
  #if (MCAL_AR_VERSION == MCAL_AR_422)

  /* [cover parentID={F7B19A4E-8ED8-46b1-B62B-5EFDA9A921B1}]
  Report DET CAN_17_MCMCAN_E_PARAM_DLC
  [/cover] */
  (void)Det_ReportError(CAN_17_MCMCAN_MODULE_ID, CAN_17_MCMCAN_INSTANCE_ID,
                  CAN_17_MCMCAN_SID_WRITE, CAN_17_MCMCAN_E_PARAM_DLC);

  /*AUTOSAR 4.4.0 has the error ID as CAN_17_MCMCAN_E_PARAM_DATALENGTH*/
  /* [cover parentID={201EB7D6-19FF-4aeb-ABB0-F40CFA3060EE}]
  If AUTOSAR version is 4.4.0
  [/cover] */
  #else
  /* [cover parentID={87E75B28-B4A3-4f90-B1FE-9B0478F84D60}]
  Report DET CAN_17_MCMCAN_E_PARAM_DATALENGTH
  [/cover] */
  (void)Det_ReportError(CAN_17_MCMCAN_MODULE_ID, CAN_17_MCMCAN_INSTANCE_ID,
                  CAN_17_MCMCAN_SID_WRITE, CAN_17_MCMCAN_E_PARAM_DATALENGTH);
  #endif
}

/*CYCLOMATIC_Can_17_McmCan_lWriteDetCheck_JUSTIFICATION: This Function has a
  cyclomatic Complexity of 16 because this function handles the DET checks
  of Can_Write. All checks are implemented as part of this function and
  are more redable to have it in single function.
*/
/*******************************************************************************
** Traceability   : [cover parentID={18939D9E-445D-4178-A039-4CFA1B36C798}]   **
**                                                                            **
**  Syntax           : static Std_ReturnType Can_17_McmCan_lWriteDetCheck     **
**                    (                                                       **
**                       const Can_HwHandleType Hth,                          **
**                       const Can_PduType *const PduInfoPtr                  **
**                    )                                                       **
**                                                                            **
**  Description      : Handles DET checks for Can_17_McmCan_Write API         **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant                                              **
**                                                                            **
**  Parameters (in)  :Hth - Hardware Transmit Handle                          **
**                    PduInfoPtr - Pointer to SDU user memory, DLC and        **
**                                                                  Identifier**
**                    CoreConfigPtr - Pointer to CAN driver configuration     **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : E_OK - No Development Error                            **
**                    E_NOT_OK - Development Error detected and reported      **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Can_17_McmCan_lWriteDetCheck(const Can_HwHandleType Hth,
                                            const Can_PduType *const PduInfoPtr)
{
  /*Check if FD is enabled*/
  #if (CAN_17_MCMCAN_FD_ENABLE == STD_ON)

  /*Pointer to CAN controller address*/
  const volatile Ifx_CAN_N *NodeRegAddressPtr;

  /*CAN controller ID*/
  uint8 ControllerId;

  #endif

  /*Index of the currently executing core*/
  uint8 CoreIndex;

  /*Variable to store the local core Config pointer type*/
  const Can_17_McmCan_CoreConfigType *CoreConfigPtr;

  /*HTH index*/
  Can_HwHandleType HthIndex;

  #if (CAN_17_MCMCAN_MULTICORE_ERROR_DETECT == STD_ON) || \
        (CAN_17_MCMCAN_FD_ENABLE == STD_ON)
  /*Variable to store the logical controller ID*/
  uint8 LogicalControllerId;
  #endif /* (CAN_17_MCMCAN_MULTICORE_ERROR_DETECT == STD_ON) || \
        (CAN_17_MCMCAN_FD_ENABLE == STD_ON) */

  /*Return value of the function*/
  Std_ReturnType ReturnValue = E_NOT_OK;

  /*Get the currently executing core ID*/
  CoreIndex = CAN_17_MCMCAN_GETCOREINDEX;

  /*Check if the core is initialized*/
  ReturnValue = Can_17_McmCan_lDetUninitConfig(CAN_17_MCMCAN_SID_WRITE,
                                                              CoreIndex);


  /*Check if the core is initialized*/
  /* [cover parentID={4BBBFE04-F181-450f-84C0-4451E056FBF6}]
  Is the driver is initialized?
  [/cover] */
  if (E_OK == ReturnValue)
  {

  /*Check if multicore error detect is ON*/
  /* [cover parentID={34AB59AA-28A9-41b2-A700-E41F0FD00F14}]
  MULTICORE ERROR DETECT == STD_ON
  [/cover] */
  #if (CAN_17_MCMCAN_MULTICORE_ERROR_DETECT == STD_ON)

    /* Local copy of the core specific configuration */
    CoreConfigPtr = Can_17_McmCan_kGblConfigPtr->CanCoreConfigPtr[CoreIndex];

    /*Check if transmit objects are configured in this core*/
    /* [cover parentID={7FD20809-DAE1-43a0-A455-0A7DC1ACB803}]
    Are transmit objects configured in this core?
    [/cover] */

    if (NULL_PTR == CoreConfigPtr->CanTxHwObjectConfigPtr)
    {

      /* Report to DET */
      /* [cover parentID={1938CEB7-260A-405e-81EA-155BF2508492}]
      DetError CAN_17_MCMCAN_E_NOT_CONFIGURED
      [/cover] */
      (void)Det_ReportError(CAN_17_MCMCAN_MODULE_ID, CAN_17_MCMCAN_INSTANCE_ID,
                       CAN_17_MCMCAN_SID_WRITE, CAN_17_MCMCAN_E_NOT_CONFIGURED);

       ReturnValue = E_NOT_OK;
    }
    /*Check if HTH index is within the range*/
    /* [cover parentID={ABA556EB-B7FD-459c-811F-6C774F518AC9}]
    Sanity of the transmit hardware object by checking its range
    (include the Rx hardware object offset in the check)
    [/cover] */
    else if ((Hth >= Can_17_McmCan_kGblConfigPtr->CanTotalHwObj) ||
               (Hth < Can_17_McmCan_kGblConfigPtr->CanNoOfHrh))
    {
      /*Report to DET*/
      /* [cover parentID={154AD793-2358-4352-8745-21904858048B}]
      Det error CAN_17_MCMCAN_E_PARAM_HANDLE
      [/cover] */
      (void)Det_ReportError(CAN_17_MCMCAN_MODULE_ID, CAN_17_MCMCAN_INSTANCE_ID,
                    CAN_17_MCMCAN_SID_WRITE, CAN_17_MCMCAN_E_PARAM_HANDLE);

      ReturnValue = E_NOT_OK;
    }
    else
    {
      /* Extract HTH index for accessing corresponding configuration */
      HthIndex = Hth - (Can_17_McmCan_kGblConfigPtr->CanNoOfHrh);

      /* Set with the associated controller of requested HTH */
      LogicalControllerId = Can_17_McmCan_kGblConfigPtr->
                            CanHthIndexPtr[HthIndex].CanHthLogicContIndex;

       /*check validity of controller*/
       /* [cover parentID={343A75B8-FF81-4cd9-A22C-F8338EE9A041}]
       Validate controller ID
       [/cover] */
       ReturnValue = Can_17_McmCan_lDetParamController(CoreIndex,
                                  LogicalControllerId, CAN_17_MCMCAN_SID_WRITE);
    }
  /* [cover parentID={64794178-4784-49e9-A4EF-4470A47303DB}]
  MULTICORE ERROR DETECT == STD_OFF
  [/cover] */
  #else

    /*Check if HTH index is within the range*/
    /* [cover parentID={0A8527D7-2162-465e-864B-1E8F331B365E}]
    Check if the HTH is within the range?
    [/cover] */
    if ((Hth >= Can_17_McmCan_kGblConfigPtr->CanTotalHwObj) ||
               (Hth < Can_17_McmCan_kGblConfigPtr->CanNoOfHrh))
    {
      /*Report to DET*/
      /* [cover parentID={3778F7DC-BAF7-4832-B4D4-481B3F435468}]
      DET error CAN_17_MCMCAN_E_PARAM_HANDLE
      [/cover] */
      (void)Det_ReportError(CAN_17_MCMCAN_MODULE_ID, CAN_17_MCMCAN_INSTANCE_ID,
                    CAN_17_MCMCAN_SID_WRITE, CAN_17_MCMCAN_E_PARAM_HANDLE);

      ReturnValue = E_NOT_OK;
    }

  #endif
  }

  /*Check the sanity of the transmit hardware object by checking its range
  (include the Rx hardware object offset in the check)*/
  /* [cover parentID={088740AE-4624-4d0a-BE64-003CBE2994B4}]
  have checks passed
  [/cover] */
  if (E_OK == ReturnValue)
  {

    /*cehck if PDU info is NULL*/
    /* [cover parentID={52FE0CA3-2B3A-433a-A24F-1D2D6306DFF7}]
    Pdu info pointer is a NULL_PTR
    [/cover] */
    if (PduInfoPtr == NULL_PTR)
    {
      /*Report DET*/
      (void)Det_ReportError(CAN_17_MCMCAN_MODULE_ID, CAN_17_MCMCAN_INSTANCE_ID,
                      CAN_17_MCMCAN_SID_WRITE, CAN_17_MCMCAN_E_PARAM_POINTER);

      ReturnValue = E_NOT_OK;
    }

    /*Check if FD is enabled*/
    #if (CAN_17_MCMCAN_FD_ENABLE == STD_OFF)

    /*check if DLC is greater than 8*/
    /* [cover parentID={F0F8AFC3-C852-4962-AF7E-5B309EA6C6C9}]
    Pdu info for DLC is greater than the maximum data length for classical
    CAN message
    [/cover] */
    else if (PduInfoPtr->length > CAN_17_MCMCAN_MAX_DATA_LENGTH)
    {
      /* Report to DET */
      Can_17_McmCan_lDetDataLength();

      /* The DLC length is > 8 */
      ReturnValue = E_NOT_OK;
    }
    #else  /* #if (CAN_17_MCMCAN_FD_ENABLE == STD_OFF) */
    /*DLC not in range*/
    /* [cover parentID={4EC2EE6D-1E14-4acc-927D-50143C73A14E}]
    Pdu info for DLC is greater than the maximum data length for classical
    CAN message
    [/cover] */

    else if (PduInfoPtr->length > CAN_17_MCMCAN_MAX_FD_LENGTH)
    {
      /* Report to DET */
      Can_17_McmCan_lDetDataLength();

      /* The DLC length is > 64 */
      ReturnValue = E_NOT_OK;
    }
    #endif /* #if (CAN_17_MCMCAN_FD_ENABLE == STD_OFF) */
    else
    {
      /*Check if FD is enabled*/
      #if (CAN_17_MCMCAN_FD_ENABLE == STD_ON)

      /* Local copy of the core specific configuration */
      CoreConfigPtr = Can_17_McmCan_kGblConfigPtr->CanCoreConfigPtr[CoreIndex];

      /*PDU info out of range*/
      /* [cover parentID={BE15D587-DF6F-48e1-88DD-C08F9DB42241}]
      Pdu info for DLC is greater than Maximum FD data length value
      [/cover] */
      if (PduInfoPtr->length > CAN_17_MCMCAN_MAX_DATA_LENGTH)
      {
        /* Extract HTH index for accessing corresponding configuration */
        HthIndex = Hth - (Can_17_McmCan_kGblConfigPtr->CanNoOfHrh);

        /* Set with the associated controller of requested HTH */
        LogicalControllerId = Can_17_McmCan_kGblConfigPtr->
                              CanHthIndexPtr[HthIndex].
                              CanHthLogicContIndex;

        /* Set with the associated controller of requested HTH */
        ControllerId = Can_17_McmCan_kGblConfigPtr->
                       CanLogicalControllerIndexPtr[LogicalControllerId].
                       CanLCoreSpecContIndex;

        /* Controller Node Address */
        NodeRegAddressPtr = CoreConfigPtr->CanControllerConfigPtr[ControllerId].
                            CanNodeAddressPtr;

        /* Check the controller with FD mode */
        /* [cover parentID={F2A0A54C-6A0F-4ceb-9D7A-FC2DD5ABD5E8}]
        Is the FDOE bit of CCCR register for controller set in FD mode?
        [/cover] */

        if (CAN_17_MCMCAN_BIT_SET_VAL != NodeRegAddressPtr->CCCR.B.FDOE)
        {
          /* Report to DET */
          /* [cover parentID={2213868A-0BAE-4577-8321-1274A4806C31}]
          Report error as per the AUTOSAR version
          [/cover] */
          Can_17_McmCan_lDetDataLength();

          /* Set controller without FD mode while FD request */
          ReturnValue = E_NOT_OK;
        }
        else
        {
          /* Ckeck the message Id */
          /* [cover parentID={F2A0A54C-6A0F-4ceb-9D7A-FC2DD5ABD5E8}]
          Is the FDOE bit of CCCR register for controller set in FD mode?
          [/cover] */
          if (CAN_17_MCMCAN_ID_FD_ENABLE_SET != (PduInfoPtr->id &
                                              CAN_17_MCMCAN_ID_FD_ENABLE_SET))
          {
            /* Report to DET */
            /* [cover parentID={2736BD57-5B31-4d81-94CE-05D3CF0AB677}]
            Report error
            [/cover] */
            Can_17_McmCan_lDetDataLength();

            /* Set when controller in FD mode and DLC>8,but Id flag
            is not set properly */
            ReturnValue = E_NOT_OK;
          }
        }
      }
      #endif /* #if (CAN_17_MCMCAN_FD_ENABLE == STD_ON) */
    }
  }
  /*Check if status is OK*/
  if (E_OK == ReturnValue)
  {

    /* Local copy of the core specific configuration */
    CoreConfigPtr = Can_17_McmCan_kGblConfigPtr->CanCoreConfigPtr[CoreIndex];

    /* Extract HTH index for accessing corresponding core specific
    configuration */
    HthIndex = Can_17_McmCan_kGblConfigPtr->CanHthIndexPtr[Hth -
                 (Can_17_McmCan_kGblConfigPtr->CanNoOfHrh)].CanHthCoreSpecIndex;

    /* Check the validity of the CAN ID passed in the L-Pdu */
    /* [cover parentID={87850451-9C28-4a2f-8C35-BB19CA67FADF}]
    Check the validity of the CAN ID passed in the L-Pdu
    [/cover] */
    ReturnValue = Can_17_McmCan_lWriteIdCheck(HthIndex, PduInfoPtr,
                                               CoreConfigPtr);
  }
  return ReturnValue;
}

/*******************************************************************************
** Traceability   : [cover parentID={1E3A47B2-CF09-4091-AE09-0D558A65DFF6}]   **
**  Syntax           : static Std_ReturnType Can_17_McmCan_lWriteIdCheck      **
**                    (                                                       **
**                      const Can_HwHandleType Hth,                           **
**                      const Can_PduType *const PduInfoPtr,                  **
**                      const Can_17_McmCan_CoreConfigType *const CoreConfigPtr*
**                    )                                                       **
**                                                                            **
**  Description      : Handles DET checks related to Message ID passed for    **
**                     Can_17_McmCan_Write API                                **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant                                              **
**                                                                            **
**  Parameters (in)  : Hth - Hardware Transmit Handle specific to core        **
**                    PduInfoPtr - Pointer to SDU user memory, DLC and        **
**                                  Identifier                                **
**                    CoreConfigPtr - Pointer to CAN driver configuration     **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : E_OK - No Development Error                            **
**                    E_NOT_OK - Development Error detected and reported      **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Can_17_McmCan_lWriteIdCheck(
    const Can_HwHandleType Hth, const Can_PduType *const PduInfoPtr,
    const Can_17_McmCan_CoreConfigType *const CoreConfigPtr)
{
  /*Return value of the function*/
  Std_ReturnType ReturnValue = E_OK;

  #if (CAN_17_MCMCAN_TRIG_TRANSMIT == STD_ON)
  /*Variable to check the trigger status*/
  boolean TrigStatus;
  #endif /* #if (CAN_17_MCMCAN_TRIG_TRANSMIT == STD_ON) */

  /* Check requested Id Type is same as with HTH CanIdType */
  /* [cover parentID={8E54F20B-46B6-4e12-84DD-FEAE40115C26}]
  Check Hth CAN ID type is extended
  [/cover] */
  if (CAN_17_MCMCAN_ID_EXTENDED == CoreConfigPtr->CanTxHwObjectConfigPtr[Hth].
                                  CanTxHwObjIdType)
  {
    /* Check Id type is extended*/
    /* [cover parentID={3738E817-874C-4c93-88AC-EBEEC072E92D}]
    Check pdu info Id type is extended or not
    [/cover] */
    if (CAN_17_MCMCAN_SET_XTD_BIT_MASK != (PduInfoPtr->id &
                                          CAN_17_MCMCAN_SET_XTD_BIT_MASK))
    {
      /* Report to DET */
      /* [cover parentID={278FC26B-FBF3-4c0e-A8AB-0BF302F92B2A}]
      Det error CAN_17_MCMCAN_E_PARAM_MSGID
      [/cover] */
      (void)Det_ReportError(CAN_17_MCMCAN_MODULE_ID, CAN_17_MCMCAN_INSTANCE_ID,
                      CAN_17_MCMCAN_SID_WRITE, CAN_17_MCMCAN_E_PARAM_MSGID);

      ReturnValue = E_NOT_OK;
    }
    else
    {
      /* Do nothing */
      /* [cover parentID={D5F7008F-8509-4d81-8886-05C22D25468D}]
      Is status is E_OK?
      [/cover] */
      ReturnValue = E_OK;
    }
  }
  /* Check Id type is Standard or not */
  /* [cover parentID={5D1530A7-7FA2-4737-800C-640AAFEFB6CF}]
   Check Hth CAN ID type is standard type
  [/cover] */
  else if (CAN_17_MCMCAN_ID_STANDARD ==
      CoreConfigPtr->CanTxHwObjectConfigPtr[Hth].CanTxHwObjIdType)
  {
    /* Check Id type is extended or not */

    /* [cover parentID={E062AC43-44B7-4064-9F40-99327AC4CD3E}]
    Check pdu info Id type is standard or not
    [/cover] */
    if (CAN_17_MCMCAN_SET_XTD_BIT_MASK == (PduInfoPtr->id &
                                          CAN_17_MCMCAN_SET_XTD_BIT_MASK))
    {
      /*Report to DET*/
      (void)Det_ReportError(CAN_17_MCMCAN_MODULE_ID, CAN_17_MCMCAN_INSTANCE_ID,
                      CAN_17_MCMCAN_SID_WRITE, CAN_17_MCMCAN_E_PARAM_MSGID);

      ReturnValue = E_NOT_OK;
    }
    else
    {
      /* Do nothing */
      ReturnValue = E_OK;
    }
  }
  else
  {
    /* Do nothing */
  }


  if (E_OK == ReturnValue)
  {
    /*Check if trigger transmit is enabled*/
    /* [cover parentID={0035D8AC-101E-4048-B0CA-D0F6E11E5DFC}]
    Is trigger trasmit enabled?
    [/cover] */
    #if (CAN_17_MCMCAN_TRIG_TRANSMIT == STD_ON)
      /* Read requested HTH is with trigger transmit API is enabled  */
      TrigStatus = CoreConfigPtr->CanTxHwObjectConfigPtr[Hth].CanTrigTxStatus;

      /* Transmit trigger status is False or the sdu in the pdu info is a
      NULL_PTR, then check Trigger status */
      /* [cover parentID={9D09780A-1403-4d7c-8558-4B1EF0AC0B4E}]
      Check if transmit trigger status is False and
      the sdu in the pdu info is a NULL_PTR
      [/cover] */
      if ((FALSE == TrigStatus) && (NULL_PTR == PduInfoPtr->sdu))
      {
        /* Report to DET */
        /* [cover parentID={4415134C-B837-4414-941F-CD213C0F1FBC}]
        Report to DET CAN_17_MCMCAN_E_PARAM_POINTER
        [/cover] */
        (void)Det_ReportError(CAN_17_MCMCAN_MODULE_ID,
                              CAN_17_MCMCAN_INSTANCE_ID,
                              CAN_17_MCMCAN_SID_WRITE,
                              CAN_17_MCMCAN_E_PARAM_POINTER);

        /* Trigger transmit API is disabled for the requested HTH */
        ReturnValue = E_NOT_OK;
      }
    #else
      /* Check sdu info */

      /* [cover parentID={4770EDB2-C2EC-43f2-B8E2-A7E2BE29209F}]
      Sdu in the Pdu Info is a NULL_PTR
      [/cover] */
      if (NULL_PTR == PduInfoPtr->sdu)
      {
        /* Report to DET */
        /* [cover parentID={4415134C-B837-4414-941F-CD213C0F1FBC}]
        Report to DET CAN_17_MCMCAN_E_PARAM_POINTER
        [/cover] */
        (void)Det_ReportError(CAN_17_MCMCAN_MODULE_ID,
                              CAN_17_MCMCAN_INSTANCE_ID,
                               CAN_17_MCMCAN_SID_WRITE,
                               CAN_17_MCMCAN_E_PARAM_POINTER);

        /* Trigger transmit API is disabled for the requested HTH */
        ReturnValue = E_NOT_OK;
      }
      else
      {
        ReturnValue = E_OK;
      }
    #endif /* #if (CAN_17_MCMCAN_TRIG_TRANSMIT == STD_ON) */
  }
  return ReturnValue;
}

/*******************************************************************************
** Traceability     : [cover parentID={24945FE4-B6E6-451a-B8D2-6B09C759D8A8}] **
**  Syntax     : static Std_ReturnType Can_17_McmCan_lDetParamController      **
**                    (                                                       **
**                      const uint8 CoreIndex,                                **
**                      const uint8 Controller,                               **
**                      const uint8 ServiceID,                                **
**                    )                                                       **
**                                                                            **
**  Description      : The function checks whether CAN controller has a       **
**                     valid CAN controller Id and is activated. If not then, **
**                    reports DET.                                            **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant                                              **
**                                                                            **
**  Parameters (in)  : CoreIndex - Core which is calling this function        **
**                     Controller - Associated CAN Controller Id              **
**                     ServiceId - Service Id of the calling API              **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : E_OK: ControllerId is valid                            **
**                     E_NOT_OK: ControllerId is invalid                      **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Can_17_McmCan_lDetParamController(const uint8 CoreIndex,
                                                        const uint8 Controller,
                                                          const uint8 ServiceID)
{
  /*Return Value of the local function*/
  Std_ReturnType ReturnValue = E_NOT_OK;

  /* Check Controller Id is out of range */
  /* [cover parentID={378E7144-5309-46ea-852E-C7D6FF243F20}]
  Controller Id is greater than number of controllers configured
  [/cover] */
  if (Controller >= CAN_17_MCMCAN_NOOF_CONTROLLER)
  {
    /* Report to DET */
    /* [cover parentID={433A06CD-4D92-43c7-B000-7DE89BC6AD28}]
    Det error CAN_17_MCMCAN_E_PARAM_CONTROLLER
    [/cover] */
    (void)Det_ReportError(CAN_17_MCMCAN_MODULE_ID, CAN_17_MCMCAN_INSTANCE_ID,
                    ServiceID, CAN_17_MCMCAN_E_PARAM_CONTROLLER);
  }
  else
  {
    #if (CAN_17_MCMCAN_MULTICORE_ERROR_DETECT == STD_ON)
    /*Is Controller allocated to current core*/
    /* [cover parentID={F58BF72A-4FFD-4b58-B3B4-4CA2CBFC9D58}]
    Controller ID is allocated to current core
    [/cover] */
    if (CoreIndex == Can_17_McmCan_kGblConfigPtr->
                    CanLogicalControllerIndexPtr[Controller].CanLCoreAssigned)
    {
      ReturnValue = E_OK;
    }
    else
    {
      /* Report to DET */
      /* [cover parentID={7026EB9F-2D08-4ed2-994D-23A8227F5450}]
      Det error CAN_17_MCMCAN_E_NOT_CONFIGURED
      [/cover] */
      (void)Det_ReportError(CAN_17_MCMCAN_MODULE_ID, CAN_17_MCMCAN_INSTANCE_ID,
                      ServiceID, CAN_17_MCMCAN_E_NOT_CONFIGURED);
    }
    #else

    UNUSED_PARAMETER(CoreIndex);

    ReturnValue = E_OK;

    #endif /*   #if (CAN_17_MCMCAN_MULTICORE_ERROR_DETECT == STD_ON) */
  }

  return ReturnValue;
}

/*********************************End of DET internal functions****************/
#endif /* #if (CAN_17_MCMCAN_DEV_ERROR_DETECT == STD_ON) */

/*******************************************************************************
            Interrupt Handlers
*******************************************************************************/

#if ((CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON))
/*******************************************************************************
** Traceability   : [cover parentID={D47A49B6-985A-4c4f-86D5-C17125DAE268}]   **
**                                                                            **
**                                                                            **
** Syntax           : void Can_17_McmCan_IsrTransmitHandler                   **
**                    (                                                       **
**                      const uint8 HwKernelId                                **
**                      const uint8 NodeIdIndex                               **
**                    )                                                       **
**                                                                            **
** Description    :The function identifies the message object belonging to    **
**                 the given CAN controller for which the transmission request**
**                 was successful. It extracts the corresponding software PDU **
**                 handle and gives notification to upper layer.              **
**                 The Can_17_McmCan_IsrTransmitHandler() handler is available**
**                 only when CanTxProcessing is enabled                       **
**                 Due to Mixed mode support, if one of the HTH is configured **
**                 in INTERRUPT mode every successful transmission will       **
**                 trigger interrupt.                                         **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : HwKernelId - The CAN controller which is to be processed,*
**                    is associated with the passed Kernel                    **
**                    NodeIdIndex - The CAN node which is to be processed     **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
void Can_17_McmCan_IsrTransmitHandler(const uint8 HwKernelId,
                                      const uint8 NodeIdIndex)
{
  /*Can controller node address pointer*/
  volatile Ifx_CAN_N *NodeRegAddressPtr;

  /*Controller index*/
  uint8 CntrlIndx;

  /*Index of the core the function is invoked from*/
  uint8 CoreIndex;

  /*Pointer to the Can config structure*/
  const Can_17_McmCan_CoreConfigType *CoreConfigPtr;

  /*Pointer to the can core state type structure*/
  const Can_17_McmCan_CoreGlobalType *CoreGlobalPtr;

  /*Variabel to check the count of TX event FIFO entries*/
  uint8 CheckCount = 0U;

  /* Get core id which is executing currently */
  CoreIndex = CAN_17_MCMCAN_GETCOREINDEX;

  /* Local copy of the core specific configuration */
  CoreConfigPtr = Can_17_McmCan_kGblConfigPtr->CanCoreConfigPtr[CoreIndex];

  /* Local copy of the core specific global states */
  CoreGlobalPtr = Can_17_McmCan_GblCoreState[CoreIndex];

  /* Retrive core specific controller index */
  CntrlIndx = Can_17_McmCan_kGblConfigPtr->CanPhyControllerIndexPtr[
              (CAN_17_MCMCAN_NOOF_NODES_PER_KERNEL * HwKernelId) +
              NodeIdIndex].CanPCoreSpecContIndex;

  /* Check the controller mode is Interrupt or Mixed */
  if (CAN_17_MCMCAN_POLLING !=
      CoreConfigPtr->CanEventHandlingConfigPtr[CntrlIndx].CanTxProcessing)
  {
      /* Set with Node Register Start address */
    NodeRegAddressPtr = CoreConfigPtr->
                        CanControllerConfigPtr[CntrlIndx].CanNodeAddressPtr;

    /* Check if Tx Event FIFO New Entry is stored */
    /* [cover parentID={2C77992E-569E-461f-9A24-894A72EDCC38}]
    Loop for TEFN bit clear
    [/cover] */
    while ((CAN_17_MCMCAN_BIT_SET_VAL == NodeRegAddressPtr->IR.B.TEFN) &&
        (CheckCount < CAN_17_MCMCAN_FLAG_CHECK_COUNT))
    {
      NodeRegAddressPtr->IR.U = CAN_17_MCMCAN_CLEAR_IE_TEFN_BIT;

      CheckCount++;
    }
    /*If Config Pointer is not NULL*/
    /* [cover parentID={37BEC4E9-A8B9-46eb-959D-5A093D039C26}]
    Check if the TX hw object config poinetr is not NULL?
    [/cover] */
    if (NULL_PTR != CoreConfigPtr->CanTxHwObjectConfigPtr)
    {
      /* If New Event Entry is present then invoke Tx handler */
      /* [cover parentID={F6D5E63E-B4A0-4cff-9931-69495A1D6247}]
      Invoke Tx Handler
      [/cover] */
      Can_17_McmCan_lTxEventHandler(CntrlIndx, CoreGlobalPtr,
                                    CAN_17_MCMCAN_INTERRUPT, CoreConfigPtr);
    }
  }
}
#endif /* #if((CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON)) */

#if ((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON) || \
    (CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
/*******************************************************************************
** Traceability   : [cover parentID={B91B38C0-0F62-4a9a-BF22-9EC231B6521E}]   **
** Syntax           : void Can_17_McmCan_IsrReceiveHandler                    **
**                    (                                                       **
**                      const uint8 HwKernelId                                **
**                      const uint8 NodeIdIndex                               **
**                    )                                                       **
**                                                                            **
** Description    :The function should handle receive interrupts from         **
**                 dedicated receive buffers during CAN controller            **
**                 STARTED state.                                             **
**                 For dedicated reception the hardware filter code alone is  **
**                 considered, the receive mask available shall not be used   **
**                 during the filtering or processing of the message.         **
**                 In case of dedicated each hardware object can be configured**
**                 as INTERRUPT or POLLING. However as the interrupt lines are**
**                 shared, if one of the HRH is configured as INTERRUPT all   **
**                 dedicated objects on reception would trigger an interrupt. **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   :HwKernelId - The CAN controller which is to be processed,**
**                   is associated with the passed Kernel,                    **
**                   NodeIdIndex - The CAN node which is to be processed     **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
void Can_17_McmCan_IsrReceiveHandler(const uint8 HwKernelId,
                                     const uint8 NodeIdIndex)
{
  /*Can controller node address pointer*/
  volatile Ifx_CAN_N *NodeRegAddressPtr;

  /*Controller index*/
  uint8 CntrlIndx;

  /*Index of the core the function is invoked from*/
  uint8 CoreIndex;

  /*Pointer to the Can config structure*/
  const Can_17_McmCan_CoreConfigType *CoreConfigPtr;

  /*Pointer to the can core state type structure*/
  const Can_17_McmCan_CoreGlobalType *CoreGlobalPtr;

  /*Variabel to check the count of DRX*/
  uint8 CheckCount = 0U;

  /* Get core id which is executing currently */
  CoreIndex = CAN_17_MCMCAN_GETCOREINDEX;

  /* Local copy of the core specific configuration */
  CoreConfigPtr = Can_17_McmCan_kGblConfigPtr->CanCoreConfigPtr[CoreIndex];

  /* Local copy of the core specific global states */
  CoreGlobalPtr = Can_17_McmCan_GblCoreState[CoreIndex];

  /* Retrive core specific controller index */
  CntrlIndx = Can_17_McmCan_kGblConfigPtr->CanPhyControllerIndexPtr[
              (CAN_17_MCMCAN_NOOF_NODES_PER_KERNEL * HwKernelId) + NodeIdIndex].
              CanPCoreSpecContIndex;

  /* Set with Node Register Start address */
  NodeRegAddressPtr = CoreConfigPtr->CanControllerConfigPtr[CntrlIndx].
                      CanNodeAddressPtr;

  /* Check if any of the Message stored to Dedicated Rx Buffer */
  /* [cover parentID={4B1788E8-57B4-4d14-BB70-8CCEE77EB482}]
  Loop for DRX bit clear
  [/cover] */
  while ((IFX_CAN_N_IR_DRX_MSK == NodeRegAddressPtr->IR.B.DRX) &&
        (CheckCount < CAN_17_MCMCAN_FLAG_CHECK_COUNT))
  {
    NodeRegAddressPtr->IR.U = (uint32)((uint32)IFX_CAN_N_IR_DRX_MSK <<
                              IFX_CAN_N_IR_DRX_OFF);
    CheckCount++;
  }

  /* If current state is START Invoke receive handler function */
  /* [cover parentID={FD1329C9-2BBF-483a-A187-46467202ECD1}]
  Is Controller mode in STARTED
  [/cover] */
  if (CAN_17_MCMCAN_STARTED == CoreGlobalPtr->CanControllerModePtr[CntrlIndx])
  {
    /* Call receive handler with buffer type as dedicated */
    /* [cover parentID={6C716C92-D9AA-41c5-BD2B-38FC96CD61E9}]
    Invoke Rx Handler
    [/cover] */
    Can_17_McmCan_lReceiveHandler(CntrlIndx, CAN_17_MCMCAN_RX_DED_BUFFER,
                                  CAN_17_MCMCAN_INTERRUPT, CoreGlobalPtr,
                                  CoreConfigPtr);
  }
}
#endif /* #if((CAN_17_MCMCAN_RX_DED_INTERRUPT_PROCESSING == STD_ON) && \
    ((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON) ||              \
    (CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))) */

#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON) ||               \
    (CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
/*******************************************************************************
** Traceability   : [cover parentID={ADE7805B-51A9-4d63-8F4E-91F628C4625C}]   **
**                                                                            **
** Syntax           : void Can_17_McmCan_IsrRxFIFOHandler                     **
**                    (                                                       **
**                      const uint8 HwKernelId                                **
**                      const uint8 NodeIdIndex                               **
**                    )                                                       **
**                                                                            **
** Description    :The function shall handle receive interrupts from FIFO 0   **
**                 and FIFO 1 during CAN controller STARTED state.            **
**                 The ISR is triggered for FIFO0/ FIFO 1 on Watermark or     **
**                 on FIFO full event. Messages are read through FIFO and     **
**                 freed by acknowledging the slot to receive successive      **
**                 packet. Rx FIFO interrupt processes maximum of configured  **
**                 FIFO elements. In case the messages are received while the **
**                 Rx FIFO messages are in progress and if number of messages **
**                 received is greater than the configured threshold level;   **
**                 on exit of interrupt handler; watermark interrupt will     **
**                 not be triggered. Therefore all messages will be processed **
**                 only on FULL interrupt.                                    **
**                 If FIFO overflow is set, an error CAN_17_MCMCAN_E_DATALOST **
**                 is raised to indicate that few messages may be lost.       **
**                 RXFIFO 0 and 1 can be separately configured as INTERRUPT   **
**                 or POLLING in case mixed mode is used.                     **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   :HwKernelId - The CAN controller which is to be processed,**
**                   is associated with the passed Kernel,                    **
**                   NodeIdIndex - The CAN node which is to be processed      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
void Can_17_McmCan_IsrRxFIFOHandler(const uint8 HwKernelId,
                                     const uint8 NodeIdIndex)
{
  /*Can controller node address pointer*/
  volatile Ifx_CAN_N *NodeRegAddressPtr;

   /*RX FIFO processing type*/
  Can_17_McmCan_RxFIFOProcessingType RxFIFO0Processing;

  /*RX FIFO processing type*/
  Can_17_McmCan_RxFIFOProcessingType RxFIFO1Processing;

  /*Controller index*/
  uint8 CntrlIndx;

  /*Index of the core the function is invoked from*/
  uint8 CoreIndex;

  /*Pointer to the Can config structure*/
  const Can_17_McmCan_CoreConfigType *CoreConfigPtr;

  /*Pointer to the can core state type structure*/
  const Can_17_McmCan_CoreGlobalType *CoreGlobalPtr;

  /*Variabel to check the count of DRX*/
  uint8 CheckCount = 0U;

  /*RX Watermark*/
  Ifx_UReg_32Bit RxFxwm;

  /* Get core id which is executing currently */
  CoreIndex = CAN_17_MCMCAN_GETCOREINDEX;

  /* Local copy of the core specific configuration */
  CoreConfigPtr = Can_17_McmCan_kGblConfigPtr->CanCoreConfigPtr[CoreIndex];

  /* Local copy of the core specific global states */
  CoreGlobalPtr = Can_17_McmCan_GblCoreState[CoreIndex];

  /* Retrive core specific controller index */
  CntrlIndx = Can_17_McmCan_kGblConfigPtr->CanPhyControllerIndexPtr[
              (CAN_17_MCMCAN_NOOF_NODES_PER_KERNEL * HwKernelId) + NodeIdIndex].
              CanPCoreSpecContIndex;

  /* Set with Node Register Start address */
  NodeRegAddressPtr = CoreConfigPtr->CanControllerConfigPtr[CntrlIndx].
                      CanNodeAddressPtr;

    /*Read the processing type for RX FIFO*/
  RxFIFO0Processing = CoreConfigPtr->
              CanControllerConfigPtr[CntrlIndx].CanRxFIFO0ProcessingConfig;

  /*Read the RX FIFO0 Watermark*/
  RxFxwm = NodeRegAddressPtr->RX.F0C.B.F0WM;

  /*Loop till the RXFIFO 0 watermark bit is cleared*/
  /* [cover parentID={ED7EE307-164D-40e3-BF67-6917034A2CDB}]
  Loop till the RXFIFO 0 watermark bit is cleared
  [/cover] */
  while (((NodeRegAddressPtr->IR.U & CAN_17_MCMCAN_CLEAR_IR_RF0_WF_BITS) !=
                                CAN_17_MCMCAN_RESET_VAL) &&
                              (CheckCount < CAN_17_MCMCAN_FLAG_CHECK_COUNT))
  {
    /*Clear the RXXFIFO0 bit and increment the counter*/
    /* [cover parentID={4EEBC0C3-5ACC-45e2-84D7-5653FC0C3496}]
    Clear the RXXFIFO0 bit and increment the counter
    [/cover] */
    NodeRegAddressPtr->IR.U = CAN_17_MCMCAN_CLEAR_IR_RF0_WF_BITS;

    /* [cover parentID={6ACA260B-27BC-4805-9DC8-BF9F4F09531A}]
    Check if the RXFIFO 0 bit is set and retry count is less than 3
    [/cover] */
    CheckCount++;
  }

  /* Check if FIFO 0 level is greater than or equal to WM */
  /* [cover parentID={F09D073D-1AA6-4b42-83F0-7C91C64B08C8}]
  Check if FIFO 0 level is greater than or equal to WM
  [/cover] */
  if(RxFIFO0Processing != CAN_17_MCMCAN_RX_FIFO_NOT_CONFIGURED)
  {
    if((NodeRegAddressPtr->RX.F0S.B.F0FL)>= RxFxwm)
    {
      /* If current state is STARTED Invoke receive handler function */
      /* [cover parentID={AB57AAFD-A47C-4e6e-BD8C-1DBADF909240}]
      Is current state STARTED?
      [/cover] */
      if (CAN_17_MCMCAN_STARTED ==
                                 CoreGlobalPtr->CanControllerModePtr[CntrlIndx])
      {
        /* Call receive handler with buffer type as RXFIFO0 */
        /* [cover parentID={32835110-AFCD-4a05-801B-BFA6978ECE82}]
        Invoke Rx Handler
        [/cover] */
        Can_17_McmCan_lReceiveHandler(CntrlIndx, CAN_17_MCMCAN_RX_FIFO0,
                         CAN_17_MCMCAN_INTERRUPT, CoreGlobalPtr, CoreConfigPtr);
      }
   }
  }

  /*Read the processing type for RX FIFO1*/
  RxFIFO1Processing = CoreConfigPtr->
            CanControllerConfigPtr[CntrlIndx].CanRxFIFO1ProcessingConfig;

  /*Read the RX FIFO1 Watermark*/
  RxFxwm = NodeRegAddressPtr->RX.F1C.B.F1WM;

  /* Reset RXFIFO1 flags */
  CheckCount = 0U;

  /*Loop till RXFIFO1 watermark bit is clear*/
  /* [cover parentID={32FD0856-60DC-4a93-A4DF-4FA3574FADA7}]
  Loop till RXFIFO1 watermark bit is clear
  [/cover] */
  while (((NodeRegAddressPtr->IR.U & CAN_17_MCMCAN_CLEAR_IR_RF1_WF_BITS) !=
          CAN_17_MCMCAN_RESET_VAL) &&
          (CheckCount < CAN_17_MCMCAN_FLAG_CHECK_COUNT))
  {

    /*Check if the RF1 watermark bit is SET */
    /* [cover parentID={11071436-19A8-44a5-B699-0C92F440661F}]
    Clear RF1 watermark bit and increment retry counter
    [/cover] */
    NodeRegAddressPtr->IR.U = CAN_17_MCMCAN_CLEAR_IR_RF1_WF_BITS;

    /* [cover parentID={E1F85112-21F4-4e59-929B-41B347964203}]
    Check if the RF1 watermark bit is SET and the retry count is less than 3
    [/cover] */
    CheckCount++;
  }

  /* Check if FIFO 1 level is greater than or equal to WM */
  /* [cover parentID={CDC83D92-70B2-41ac-AF14-868EA78E3632}]
  Check if FIFO 1 level is greater than or equal to WM
  [/cover] */
  if (RxFIFO1Processing != CAN_17_MCMCAN_RX_FIFO_NOT_CONFIGURED)
  {
    if((NodeRegAddressPtr->RX.F1S.B.F1FL)>= RxFxwm)
    {
    /* If current state is STARTED Invoke receive handler function */
    /* [cover parentID={A31629D4-9B4B-43ee-83AF-529B0FD2BBBA}]
    Is current state is STARTED ?
    [/cover] */
    if (CAN_17_MCMCAN_STARTED == CoreGlobalPtr->CanControllerModePtr[CntrlIndx])
    {
      /* Call receive handler with buffer type as RXFIFO1 */
      /* [cover parentID={9D37E710-1493-4e31-8E04-952FC67DCCAF}]
      Invoke Rx Handler
      [/cover] */
      Can_17_McmCan_lReceiveHandler(CntrlIndx, CAN_17_MCMCAN_RX_FIFO1,
                         CAN_17_MCMCAN_INTERRUPT, CoreGlobalPtr, CoreConfigPtr);
    }
   }
  }
}
#endif /* #if((CAN_17_MCMCAN_RX_FIFO_INTERRUPT_PROCESSING == STD_ON) && \
    ((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON) ||               \
    (CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))) */

#if (CAN_17_MCMCAN_BO_INTERRUPT_PROCESSING == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={7F1E55A5-7758-442f-8BF8-2A8C1F035412}]   **
**                                                                            **
**  Syntax           : void Can_17_McmCan_IsrBusOffHandler                    **
**                    (                                                       **
**                      const uint8 HwKernelId                                **
**                      const uint8 NodeIdIndex                               **
**                    )                                                       **
**                                                                            **
**  Description      : The function checks the occurrence of bus-off events   **
**                     on the given CAN controller and gives corresponding    **
**                     notification to the upper layer. It resets the         **
**                    controller state to the STOPPED.                        **
**                     The Can_17_McmCan_IsrBusOffHandler() handler           **
**                     is available only when, CanBusoffProcessing is enabled **
**  [/cover]                                                                  **
**                                                                            **
**  Service ID       : NA                                                     **
**                                                                            **
**  Sync/Async       : Synchronous                                            **
**                                                                            **
**  Reentrancy       : Reentrant                                              **
**                                                                            **
**  Parameters (in)  : HwKernelId - The CAN controller which is to be         **
**                     processed, is associated with the  passed Kernel,      **
**                     NodeIdIndex - The CAN node which is to be processed    **
**                                                                            **
**  Parameters (out) : none                                                   **
**                                                                            **
**  Return value     : none                                                   **
**                                                                            **
*******************************************************************************/
void Can_17_McmCan_IsrBusOffHandler(const uint8 HwKernelId,
                                     const uint8 NodeIdIndex)
{
  /*Can controller node address pointer*/
  volatile Ifx_CAN_N *NodeRegAddressPtr;

  /*Controller index*/
  uint8 CntrlIndx;

  /*Index of the core the function is invoked from*/
  uint8 CoreIndex;

  /*Pointer to the Can config structure*/
  const Can_17_McmCan_CoreConfigType *CoreConfigPtr;

  /*Pointer to the can core state type structure*/
  const Can_17_McmCan_CoreGlobalType *CoreGlobalPtr;

  /* Get core id which is executing currently */
  CoreIndex = CAN_17_MCMCAN_GETCOREINDEX;

  /* Local copy of the core specific configuration */
  CoreConfigPtr = Can_17_McmCan_kGblConfigPtr->CanCoreConfigPtr[CoreIndex];

  /* Local copy of the core specific global states */
  CoreGlobalPtr = Can_17_McmCan_GblCoreState[CoreIndex];

  /* Retrive core specific controller index */
  CntrlIndx = Can_17_McmCan_kGblConfigPtr->CanPhyControllerIndexPtr[
              (CAN_17_MCMCAN_NOOF_NODES_PER_KERNEL * HwKernelId) + NodeIdIndex].
              CanPCoreSpecContIndex;

  /* Check the BusOff for the controller mode is Interrupt or not */
  /* [cover parentID={05DB45F8-9EB7-49b4-8ED2-0825484B87D7}]
  Controller index passed is configured for INTERRUPT Handling
  [/cover] */
  if (CAN_17_MCMCAN_INTERRUPT ==
      CoreConfigPtr->CanEventHandlingConfigPtr[CntrlIndx].CanBusoffProcessing)
  {
    /* Set with Node Register Start address */
    NodeRegAddressPtr = CoreConfigPtr->
                        CanControllerConfigPtr[CntrlIndx].CanNodeAddressPtr;

    /* Check if BusOff status is changed*/
    /* [cover parentID={C241ACB2-4CFC-46af-9617-E039387FE1B4}]
    The bus off status is changed, i.e., the BO bit in the IR register of
    the specific controller is set
    [/cover] */
    if (CAN_17_MCMCAN_BIT_SET_VAL == NodeRegAddressPtr->IR.B.BO)
    {

      /* [cover parentID={8CCAAD53-3C8E-459f-A3EE-1B5903D9C24E}]
      ICOM is ON
      [/cover] */
      #if (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON)
      /* [cover parentID={70AB158D-44C2-45ad-8370-5E417EA0AAA5}]
      Is ICOM enable status pointer is false OR BO status pointer is true?
      [/cover] */
      if ((TRUE != CoreGlobalPtr->CanIcomEnableStatusPtr[CntrlIndx]) ||
      (FALSE != CoreGlobalPtr->CanIcomConfgBOStatusPtr[CntrlIndx]))
      {
        /* If current state is STARTED
        Invoke BusOff handler function */
        /* [cover parentID={0761BB71-608E-4796-A935-52FD46D2CE67}]
        Invoke Bus Off Handler
        [/cover] */
        Can_17_McmCan_lBusOffHandler(CntrlIndx, CoreGlobalPtr, CoreConfigPtr);
      }
      #else /* #if(CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON) */

      /* If current state is STARTED Invoke BusOff handler function */
      /* [cover parentID={9DD152E3-42B5-491f-9B15-371F1658F1E1}]
      Invoke Bus Off Handler
      [/cover] */
      Can_17_McmCan_lBusOffHandler(CntrlIndx, CoreGlobalPtr, CoreConfigPtr);

      #endif /* #if(CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON) */

      /* Reset BO flag */
      /* [cover parentID={52AF64CA-597B-4b72-94A2-CA0B516E7B64}]
      Reset the Bus off flag
      [/cover] */
      NodeRegAddressPtr->IR.U = CAN_17_MCMCAN_CLEAR_IE_BO_BIT;
    }
  }
}
#endif /* #if(CAN_17_MCMCAN_BO_INTERRUPT_PROCESSING == STD_ON) */
#define CAN_17_MCMCAN_STOP_SEC_CODE_QM_GLOBAL
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
/*[cover parentID={A4F3B858-B167-4b5c-AB7F-390C5F5D2185}]
[/cover] */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"
