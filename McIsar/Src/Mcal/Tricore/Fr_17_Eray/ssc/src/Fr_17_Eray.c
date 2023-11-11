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
**  FILENAME     : Fr_17_Eray.c                                               **
**                                                                            **
**  VERSION      : 42.0.0                                                     **
**                                                                            **
**  DATE         : 2023-05-22                                                **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Fr Driver source file                                      **
**                                                                            **
**  SPECIFICATION(S) : Specification of FlexRay Driver, AUTOSAR Release 4.2.2 **
**                     and 4.4.0                                              **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/* [cover parentID={9463A7C5-DBC8-49cc-AC90-8901630A4C34}] */
/*  [/cover] */

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* FR Driver header file structure. */

/* FR module interface file */
#include "Fr_17_Eray.h"

/* Conditional Inclusion of Default Error Tracer File */
#if ((FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) ||\
      (FR_17_ERAY_RUNTIME_ERROR_DETECT == STD_ON))
#include "Det.h"
#endif /* ((FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) ||\
               (FR_17_ERAY_RUNTIME_ERROR_DETECT == STD_ON)) */

#include "SchM_Fr_17_Eray.h"

#if (FR_17_ERAY_INIT_API_MODE != FR_17_ERAY_MCAL_SUPERVISOR)
#include "McalLib_OsStub.h"
#endif

/* Register definition file for Aurix2G target */
#include "IfxEray_reg.h"
#include "IfxEray_bf.h"

/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/
/*
  The Fr module shall perform a consistency check between code
  files and header files based on pre-process-checking the version numbers
  of related code files and header files.
*/
/* [cover parentID={69D3CC09-DA4A-4483-A2AD-E4A8F186BEF4}]
Module version consistency check
[/cover] */
#ifndef FR_17_ERAY_AR_RELEASE_MAJOR_VERSION
  #error "FR_17_ERAY_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#ifndef FR_17_ERAY_AR_RELEASE_MINOR_VERSION
  #error "FR_17_ERAY_AR_RELEASE_MINOR_VERSION is not defined."
#endif

#ifndef FR_17_ERAY_AR_RELEASE_REVISION_VERSION
  #error "FR_17_ERAY_AR_RELEASE_REVISION_VERSION is not defined."
#endif

#ifndef FR_17_ERAY_SW_MAJOR_VERSION
  #error "FR_17_ERAY_SW_MAJOR_VERSION is not defined. "
#endif

#ifndef FR_17_ERAY_SW_MINOR_VERSION
  #error "FR_17_ERAY_SW_MINOR_VERSION is not defined. "
#endif

#ifndef FR_17_ERAY_SW_PATCH_VERSION
  #error "FR_17_ERAY_SW_PATCH_VERSION is not defined. "
#endif

#if (FR_17_ERAY_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION)
  #error "FR_17_ERAY_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

#if ( FR_17_ERAY_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION)
  #error "FR_17_ERAY_AR_RELEASE_MINOR_VERSION does not match."
#endif

#if ( FR_17_ERAY_AR_RELEASE_REVISION_VERSION != MCAL_AR_RELEASE_REVISION_VERSION)
  #error "FR_17_ERAY_AR_RELEASE_REVISION_VERSION does not match."
#endif

#if ( FR_17_ERAY_SW_MAJOR_VERSION != 20U )
  #error "FR_17_ERAY_SW_MAJOR_VERSION does not match. "
#endif

#if ( FR_17_ERAY_SW_MINOR_VERSION != 25U )
  #error "FR_17_ERAY_SW_MINOR_VERSION does not match. "
#endif

#if (FR_17_ERAY_SW_PATCH_VERSION != 0U)
  #error "FR_17_ERAY_SW_PATCH_VERSION does not match. "
#endif

/*
  VERSION CHECK FOR Development Error Module Inclusion
*/
/* [cover parentID={D0A81DAD-B68A-4ae7-8F19-0DAF1E63635A}]
Version check for Development Error Module
[/cover] */
#if ( FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)

#ifndef DET_AR_RELEASE_MAJOR_VERSION
  #error "DET_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#if ( DET_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION )
  #error "DET_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

#endif
/* End Of FR_17_ERAY_DEV_ERROR_DETECT */

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
/* FlexRay Communication Host Interface commands.
FR_17_ERAY_CHI_CMD_SEND_MTS(0x8U) is removed as it is not used for
implementation */
#define FR_17_ERAY_CHI_CMD_NOT_ACCEPTED          (uint8)(0x0U)
#define FR_17_ERAY_CHI_CMD_CONFIG                (uint8)(0x1U)
#define FR_17_ERAY_CHI_CMD_READY                 (uint8)(0x2U)
#define FR_17_ERAY_CHI_CMD_WAKEUP                (uint8)(0x3U)
#define FR_17_ERAY_CHI_CMD_RUN                   (uint8)(0x4U)
#define FR_17_ERAY_CHI_CMD_ALL_SLOTS             (uint8)(0x5U)
#define FR_17_ERAY_CHI_CMD_HALT                  (uint8)(0x6U)
#define FR_17_ERAY_CHI_CMD_FREEZE                (uint8)(0x7U)
#define FR_17_ERAY_CHI_CMD_ALLOW_COLDSTART       (uint8)(0x9U)
#define FR_17_ERAY_CHI_CMD_CLEAR_RAMS            (uint8)(0xCU)

/*----------------------------------------------------------------------------*/
/*  Protocol Operation Control Status  */
/* Actual state of operation of the CC Protocol Operation Control */
#define FR_17_ERAY_POCS_DEFAULT_CONFIG  ((uint8)0x00)
#define FR_17_ERAY_POCS_READY           ((uint8)0x01)
#define FR_17_ERAY_POCS_NORMAL_ACTIVE   ((uint8)0x02)
#define FR_17_ERAY_POCS_NORMAL_PASSIVE  ((uint8)0x03)
#define FR_17_ERAY_POCS_HALT            ((uint8)0x04)
#define FR_17_ERAY_POCS_CONFIG          ((uint8)0x0F)
/* Indicates the actual state of operation of the POC in the wakeup path */
#define FR_17_ERAY_POCS_STARTUP_SUCCESS ((uint8)0x2B)

/*----------------------------------------------------------------------------*/

/* Maximum  LSDU Length */
#define FR_17_ERAY_MAX_LSDU_LENGTH            ((uint32)64U)

/* Buffer reconfiguration related macros */
#if (FR_17_ERAY_RECONFIG_LPDU == STD_OFF)
#define FR_17_ERAY_BUFFER_RECONFIG_LOCKED     (2U)
#endif

#define FR_17_ERAY_BUFFER_RECONFIG_ALLOWED    (0U)

/* Write values used in unlock sequence */
#define FR_17_ERAY_UNLOCK_SEQ1                (0xCEU)
#define FR_17_ERAY_UNLOCK_SEQ2                (0x31U)

/* Interrupt lines */
#define FR_17_ERAY_ILE_ENABLE_BOTH_LINES      (3U)
#define FR_17_ERAY_SILS_TIMER_LINES           (0x200U)

/* Mask for valid WRHS2 bits */
#define FR_17_ERAY_WRHS2_MASK                 (0x007F07FFU)
/* Offset and Mask for getting the PLC from WRHS2 */
#define FR_17_ERAY_WRHS2_ALLOWDYN_OFFSET      (23U)
#define FR_17_ERAY_WRHS2_ALLOWDYN_MASK        (0x00000001U)

/* Mask for MTV bits in MTCCV register*/
#define FR_17_ERAY_MTCCV_MTV_MASK             (0x00003FFFU)

/* Mask for CCV bits in MTCCV register*/
#define FR_17_ERAY_MTCCV_CCV_MASK             (0x0000003FU)

/*
  Transfer only header section to MessageRAM
    ERAY_IBCM.B.LHSH  = 1;  (Bit 0)
    ERAY_IBCM.B.LDSH  = 0;  (Bit 1)
    ERAY_IBCM.B.STXRH = 0;  (Bit 2)

*/
#define FR_17_ERAY_TRANSFER_HEADER            (1U)

/*
  Transfer only data section to MessageRAM and set message buffer for tx
    ERAY_IBCM.B.LHSH  = 0;  (Bit 0)
    ERAY_IBCM.B.LDSH  = 1;  (Bit 1)
    ERAY_IBCM.B.STXRH = 1;  (Bit 2)
*/
#define FR_17_ERAY_TRANSFER_DATA              (6U)

#define FR_17_ERAY_LPDU_IDX_UNUSED            (0xFFFFU)

#define FR_17_ERAY_MSGBUFF_UNUSED             ((uint8)0xFFU)

/* Bit position of RMC bit field */
#define FR_17_ERAY_CLC_RMC_BIT_POS            (8U)

/* Number of bytes per 16-bit word */
#define FR_17_ERAY_BYTES_PER_HALFWORD         ((uint8)2U)

#if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
/* Index of last FlexRay communication cycle*/
#define FR_17_ERAY_MAX_CYCLE_INDEX            (63U)

/* Limit Macro for Fr_ListSize in Fr_17_Eray_GetSyncFrameList */
#define FR_17_ERAY_MAX_LIST_SIZE              ((uint8)15U)

/*Max Valid configuration parameter Index*/
#define FR_17_ERAY_CONFIG_PARAM_IDX_MAX       ((uint8)63U)

#endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */

#if ((FR_17_ERAY_RECONFIG_LPDU == STD_ON) &&\
           (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON))
/* Cycle Repetition Macros: 1, 2, 4, 8, 16, 32, 64*/
#define FR_17_ERAY_CYCLE_REPETION_1         ((uint8)1U)
#define FR_17_ERAY_CYCLE_REPETION_2         ((uint8)2U)
#define FR_17_ERAY_CYCLE_REPETION_4         ((uint8)4U)
#define FR_17_ERAY_CYCLE_REPETION_8         ((uint8)8U)
#define FR_17_ERAY_CYCLE_REPETION_16        ((uint8)16U)
#define FR_17_ERAY_CYCLE_REPETION_32        ((uint8)32U)
#define FR_17_ERAY_CYCLE_REPETION_64        ((uint8)64U)

/*Max Valid Header CRC in Fr_ReconfigLpdu API*/
#define FR_17_ERAY_HEADER_CRC_MAX           ((uint16)2047U)
#define FR_17_ERAY_SUCC1_CHANNEL_MASK       ((uint32)0x03U)
#endif

/* Initialization vector of header */
#define FR_17_ERAY_HEADER_VECTOR_INITVAL      (0x1AU)
/* Flexray header CRC polynomial */
#define FR_17_ERAY_HEADER_CRC_POLYNOMINAL     (0x385U)
/* Number of bits for Header CRC Calculation */
#define FR_17_ERAY_NUM_BITS_FOR_HEADERCRC     (0x14U)
/* Slot ID bit position */
#define FR_17_ERAY_HEADER_FID_BITPOS          (0x07U)
/* Macro for MSB Mask */
#define FR_17_ERAY_MASK_MSB                   (0x80000000U)
/* Macro for 12U  */
#define FR_17_ERAY_NUM_12                     (0x0CU)
/* Macro for 21U  */
#define FR_17_ERAY_NUM_21                     (0x15U)
/* PLC Bit position  in WRHS2  */
#define FR_17_ERAY_BIT_POS_PLC                (0x10U)

/* Timer related macros */
#define FR_17_ERAY_TIMER_CYCLECODE_SHIFT          (8U)
#define FR_17_ERAY_TIMER_MACROTICK_SHIFT          (16U)
#define FR_17_ERAY_TIMER_CYCLECODE_ONCE_IN_64     ((uint32)0x40U)
#define FR_17_ERAY_TIMER_MODE_MASK                ((uint32)2U)

#define FR_17_ERAY_SIR_TI0_MASK               ((uint32)1 << 8U)

#define FR_17_ERAY_SIER_TI0E_MASK             ((uint32)1 << 8U)

#define FR_17_ERAY_SIES_TI0E_MASK             ((uint32)1 << 8U)

/* Number of Start up Frames */
#define FR_17_ERAY_STARTUP_FRAMES             ((uint8)2U)

/* Channel Status related Macros*/
/* Channel A related macros */
#define FR_17_ERAY_A_STATUS_MASK            ((uint32)0x001FU)
#define FR_17_ERAY_A_SWNIT_VMTS_MASK        ((uint32)0x0040U)
#define FR_17_ERAY_A_SWNIT_STATUS_MASK      ((uint32)0x0003U)
#define FR_17_ERAY_A_NIT_STATUS_MASK        ((uint32)0x0300U)

/* Channel B related macros */
#define FR_17_ERAY_B_STATUS_MASK            ((uint32)0x1F00U)
#define FR_17_ERAY_B_SWNIT_VMTS_MASK        ((uint32)0x0080U)
#define FR_17_ERAY_B_SWNIT_STATUS_MASK      ((uint32)0x0018U)
#define FR_17_ERAY_B_NIT_STATUS_MASK        ((uint32)0x0C00U)

#define FR_17_ERAY_A_SWNIT_VMTS_SHIFT       ((uint32)6U)
#define FR_17_ERAY_A_NIT_STATUS_SHIFT       ((uint32)8U)

#define FR_17_ERAY_B_ACS_SHIFT              ((uint32)8U)
#define FR_17_ERAY_B_SWNIT_VMTS_SHIFT       ((uint32)7U)
#define FR_17_ERAY_B_SWNIT_STATUS_SHIFT     ((uint32)3U)
#define FR_17_ERAY_B_NIT_STATUS_SHIFT       ((uint32)10U)

#define FR_17_ERAY_SWNIT_VMTS_SHIFT         ((uint32)8U)
#define FR_17_ERAY_SWNIT_STATUS_SHIFT       ((uint32)9U)
#define FR_17_ERAY_NIT_STATUS_SHIFT         ((uint32)12U)

#if(FR_17_ERAY_RX_STRINGENT_CHECK == STD_ON)
#define FR_17_ERAY_MBS_CHANNELA_MASK        (0x55U)
#define FR_17_ERAY_MBS_CHANNELB_MASK        (0xAAU)
#else
#define FR_17_ERAY_MBS_CHA_VALIDMASK        (0x01U)
#define FR_17_ERAY_MBS_CHB_VALIDMASK        (0x02U)
#endif /* (FR_17_ERAY_RX_STRINGENT_CHECK == STD_ON) */

#define FR_17_ERAY_MBS_CHANNELA_VALID_BIT   ((uint32)0x01U)
#define FR_17_ERAY_MBS_CHA_ERRORMASK        (0x54U)

#define FR_17_ERAY_MBS_CHANNELB_VALID_BIT   ((uint32)0x02U)
#define FR_17_ERAY_MBS_CHB_ERRORMASK        (0xA8U)

#define FR_17_ERAY_WRHS1_CHANNEL_MASK       ((uint32)0x03U)

/* Message buffer configuration values */
#define FR_17_ERAY_NO_FIFO_MSG_BUFFERS        ((uint8)0x80U)

#if (FR_17_ERAY_FIFO_CONFIGURED == STD_ON)
/*Symbolic FIFO Mesg Buffer ID to differentiate from other message Buff Ids*/
#define FR_17_ERAY_FIFO_MESG_BUF_ID           ((uint8)0xFFU)
#endif

/*Macro to reset Aggregated Channel status*/
#define FR_17_ERAY_ACS_RESET                  ((uint32)0x00001F1FU)

/*Macro to reset wakeup received indication status information */
#define FR_17_ERAY_SIR_RESET                  ((uint32)0x01010000U)

#if (FR_17_ERAY_CTRL_TEST_COUNT != 0U)
#define FR_17_ERAY_CUST1_MASK                 ((uint32)0xFC00U)
#define FR_17_ERAY_SUCC1_CMD_MASK             ((uint32)0x0FU)
/*Macro to define if register values is same as configuration */
#define FR_17_ERAY_TEST_PASS                  ((uint32)1U)
#define FR_17_ERAY_TEST_FAIL                  ((uint32)0U)
#endif /* (FR_17_ERAY_CTRL_TEST_COUNT != 0U) */

/* Macro to Mask Message Buffer ID */
#define FR_17_ERAY_MSG_BUFF_ID_MASK           ((uint32)0x1FU)

/*Macro for shift count of 5 */
#define FR_17_ERAY_MSG_BUFF_ID_SHIFT          ((uint8)5U)

/*Macro to use for Divide by 4 */
#define FR_17_ERAY_DIV_BY_4                   ((uint8)4U)

#define FR_17_ERAY_MOD_4                      ((uint8)3U)
/* Used to clear the Error Service Request registers by writing 1 to the valid
 positions and 0 to the reserved positions */
#define FR_17_ERAY_CLEAR_EIR_EIER_FLAGS       ((uint32)0x07070FFFU)
/* Used to clear the Status Service Request registers by writing 1 to the valid
 positions and 0 to the reserved positions */
#define FR_17_ERAY_CLEAR_SIR_SIER_FLAGS       ((uint32)0x0303FFFFU)
/* Used to clear the Message Handler Status register by writing 1 to the valid
 positions and 0 to the reserved positions */
#define FR_17_ERAY_CLEAR_MHDS_FLAGS           ((uint32)0x0000007FU)

#define FR_17_ERAY_CTRL_NOT_CONFIGURED        ((uint8)0xFFU)
#define FR_17_ERAY_DEC_ZERO                   ((uint8)0U)
#define FR_17_ERAY_DEC_ONE                    ((uint8)1U)
#define FR_17_ERAY_DEC_TWO                    ((uint8)2U)

#define FR_17_ERAY_RATECORR_SIGN_BIT          ((uint16)0x0800U)
#define FR_17_ERAY_RATECORR_SIGN_EXT          ((uint16)0xF000U)
#define FR_17_ERAY_OFFSETCORR_SIGN_BIT        ((uint32)0x00040000U)
#define FR_17_ERAY_OFFSETCORR_SIGN_EXT        ((uint32)0xFFF80000U)

#if(FR_17_ERAY_EXTENDED_LPDU_REPORTING == STD_ON)
#define FR_17_ERAY_CHANNEL_A                        ((uint32)1U)
#define FR_17_ERAY_CHANNEL_B                        ((uint32)2U)
#endif

#define FR_17_ERAY_WAKEUP_CHNL_A              ((uint8)0U)
#define FR_17_ERAY_WAKEUP_CHNL_B              ((uint8)1U)

#define FR_17_ERAY_MAX_NUM_CONTROLLERS        ((uint8)2U)

/* [cover parentID={949F41AC-2F5F-4400-9813-B169B75F85AA}]
User Mode Execution
[/cover] */
/* [cover parentID={1A65EADD-AFD0-4845-B2D2-8257E086DD67}]
User Mode Execution
[/cover] */
#if (FR_17_ERAY_INIT_API_MODE == FR_17_ERAY_MCAL_SUPERVISOR)
/* Library APIs  */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro defined for User mode
support in code. No side effects foreseen by violating this MISRA rule. */
#define FR_17_ERAY_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(RegAdd,Data) \
                                     Mcal_WritePeripEndInitProtReg(RegAdd,Data)

#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro defined for User mode
support in code. No side effects foreseen by violating this MISRA rule. */
#define FR_17_ERAY_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(RegAdd,Data) \
                                 MCAL_LIB_WRITEPERIPENDINITPROTREG(RegAdd,Data)

#endif /* (FR_INIT_API_MODE == FR_17_ERAY_MCAL_SUPERVISOR) */

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/
/* [cover parentID={D8E79100-2E2E-499e-B66F-A7586DB8158A}]
CC POC state
[/cover] */
/* Type definition to get the CC POC state and startup state */
typedef struct
{
  const Fr_StartupStateType CCStartupState;
  const Fr_POCStateType CCPOCState;
} Fr_17_Eray_CCStateType;

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
/* Memory Map of the FR Code */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
Memory mapping
[/cover] */
/* [cover parentID={DF28B3B6-C88D-459e-8E7C-E5538C958549}]
Fr_17_Eray_MemMap.h
[/cover] */
#define FR_17_ERAY_START_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: The declaration of Fr_17_Eray_CCStateType
is not before the required #include files. This MISRA rule is shown for the
inclusion of MemMap file */
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
#include "Fr_17_Eray_MemMap.h"

#if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)

/*Function to check for invalid Timer id for absolute timer */
LOCAL_INLINE uint32 Fr_17_Eray_lDetCheckInvTimerIdx(
                        const uint8 TimerIdx, const uint8 ServiceId);

/*Function to check for the pointer is invalid */
LOCAL_INLINE uint32 Fr_17_Eray_lDetCheckInvPointer(
                      const void * const Ptr, const uint8 ServiceId);

/*Function to check for invalid control index */
LOCAL_INLINE uint32 Fr_17_Eray_lDetCheckInvCtrlIdx(const uint8 Fr_CtrlIdx,
                                                   const uint8 ServiceId);

/* Used by all APIs */
LOCAL_INLINE uint32 Fr_17_Eray_lDetCheckNoInit(const uint8 ServiceId);


/* FR_17_ERAY_E_INV_LPDU_IDX: TransmitTxLPdu, ReceiveRxLPdu, CheckTxLPduStatus*/
LOCAL_INLINE uint32 Fr_17_Eray_lDetCheckInvLPduIdx
                                (const uint8 Fr_CtrlIdx, const uint16 LPduIdx,
                                                         const uint8 ServiceId);

LOCAL_INLINE  Std_ReturnType Fr_17_Eray_lReceiveDetCheck(
                            const uint8 Fr_CtrlIdx,
                            const uint16 Fr_LPduIdx,
                            const uint8 * const Fr_LSduPtr,
                            const Fr_RxLPduStatusType * const Fr_LPduStatusPtr,
                            const uint8 * const Fr_LSduLengthPtr
                                );

LOCAL_INLINE Std_ReturnType Fr_17_Eray_lTransmitDetCheck(
                              const uint8 Fr_CtrlIdx, const uint16 Fr_LPduIdx,
                                               const uint8 * const Fr_LSduPtr);

LOCAL_INLINE Std_ReturnType Fr_17_Eray_lGetSyncFrameList(
                                    const uint8 Fr_CtrlIdx,
                                    const uint8 Fr_ListSize,
                                    const uint16* const Fr_ChannelAEvenListPtr,
                                    const uint16* const Fr_ChannelBEvenListPtr,
                                    const uint16* const Fr_ChannelAOddListPtr,
                                    const uint16* const Fr_ChannelBOddListPtr
                                );

LOCAL_INLINE Std_ReturnType Fr_17_Eray_lCancelTxLPduDetCheck(
                          const uint8 Fr_CtrlIdx, const uint16 Fr_LPduIdx);

LOCAL_INLINE Std_ReturnType Fr_17_Eray_lCheckTxLPduDetCheck(
                          const uint8 Fr_CtrlIdx,
                          const uint16 Fr_LPduIdx,
                          const Fr_TxLPduStatusType * const Fr_TxLPduStatusPtr
                                     );
LOCAL_INLINE uint32 Fr_17_Eray_lDetCheckSetAbsoluteTimer(
                                             const uint8 Fr_CtrlIdx,
                                             const uint8 Fr_AbsTimerIdx,
                                             const uint8 Fr_Cycle,
                                             const uint16 Fr_Offset,
                                             const uint8 ServiceId);
#endif /*#if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */

#if (FR_17_ERAY_TX_CONFLICT_DETECTION == STD_ON)
LOCAL_INLINE Std_ReturnType Fr_17_Eray_lConflictStatusCheck(
                              const uint8 Fr_CtrlIdx, const uint8 ChannelIdx);
#endif /* (FR_17_ERAY_TX_CONFLICT_DETECTION == STD_ON) */

static Std_ReturnType Fr_17_Eray_lSlotStatusErrorCheck
                        (const uint8 Fr_CtrlIdx, const uint8 ChannelIdx,
                                                 const uint16 Fr_LPduIdx);

LOCAL_INLINE uint32 Fr_17_Eray_lIsCCInSync(const uint8 Fr_CtrlIdx);

LOCAL_INLINE Fr_SlotModeType Fr_17_Eray_lGetSlotMode(const uint8 Fr_CtrlIdx);

/* Function to change POC state any state except READY */
LOCAL_INLINE uint32 Fr_17_Eray_lChangePOCState(const uint8 Fr_CtrlIdx,
                                               const uint8 ChiCmdId);

/* Function to wait for ERAY POC state change */
LOCAL_INLINE uint32 Fr_17_Eray_lWaitTillPOCChange(
                      const uint8 Fr_CtrlIdx, const uint8 PocState);

/* Function to change POC state to READY */
LOCAL_INLINE Std_ReturnType Fr_17_Eray_lChangePOCToReady
                                                (const uint8 Fr_CtrlIdx);

/* Transfer input buffer contents to message RAM buffer */
LOCAL_INLINE uint32 Fr_17_Eray_lInputBufBsyHost(const uint8 Fr_CtrlIdx);

/* Function to re calculate header CRC */
LOCAL_INLINE uint32 Fr_17_Eray_lHeaderCRC
(
  const uint32 FrameId,
  const uint8 PayloadLength
);

#if (FR_17_ERAY_FIFO_CONFIGURED == STD_ON)
/*Function for Receive FIFO*/
LOCAL_INLINE Std_ReturnType Fr_17_Eray_lReceiveRxFifo(
                                 const uint8 Fr_CtrlIdx,
                                 const uint16 Fr_LPduIdx,
                                 uint8* const Fr_LSduPtr,
                                 Fr_RxLPduStatusType* const Fr_LPduStatusPtr,
                                 uint8* const Fr_LSduLengthPtr);
#endif

#if(FR_17_ERAY_CTRL_TEST_COUNT != 0U)
/* Function to check the CC registers are configured with configuration data */
LOCAL_INLINE Std_ReturnType Fr_17_Eray_lVerifyCCConfig(const uint8 Fr_CtrlIdx,
                                               const uint8 LogIndex);

#endif  /* #if (FR_17_ERAY_CTRL_TEST_COUNT != 0U) */

/* Function to check the OBSYS bit is cleared after a Request transfer
   of Message Buffer */
LOCAL_INLINE Std_ReturnType Fr_17_Eray_lWaitTransferComplete(
                                   const uint8 Fr_CtrlIdx, const uint8 LogIdx);

/* Function to initialise the Message Buffer handling variables */
LOCAL_INLINE void Fr_17_Eray_lMessageBufferInit(const uint8 Fr_CtrlIdx,
                                                const uint8 LogIdx);

/* Function to clear the status/ error flags and chnange POC state */
LOCAL_INLINE Std_ReturnType Fr_17_Eray_lClrFlagChangeState
                                                    (const uint8 Fr_CtrlIdx);

/* Function to configure the message buffers during initialization */
LOCAL_INLINE Std_ReturnType Fr_17_Eray_lConfigMessageBuffer
                         (const uint8 Fr_CtrlIdx, const uint8 LogIndex);

/* Function to configure header section with updated LSduLength */
LOCAL_INLINE Std_ReturnType Fr_17_Eray_lUpdateDyLSduLength
                         (const uint8 Fr_CtrlIdx, const uint8 LogIndex,
                          const uint16 Fr_LPduIdx, const uint8 Fr_LSduLength);

/* Function to configure data section for transmission */
LOCAL_INLINE Std_ReturnType Fr_17_Eray_lUpdateTransmitData
                    (const uint8 Fr_CtrlIdx, const uint16 Fr_LPduIdx,
                     const uint8 * const Fr_LSduPtr, const uint8 Fr_LSduLength,
                     const uint8 PlcBytes);

/* Function to check the acceptance criteria for reception */
static Std_ReturnType Fr_17_Eray_lRxAcceptanceCheck(
                         const uint8 Fr_CtrlIdx, const uint8 ChannelIdx);

#if ((FR_17_ERAY_RECONFIG_LPDU == STD_ON) &&\
           (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON))
LOCAL_INLINE Std_ReturnType Fr_17_Eray_lRecfgDetChkLpduParam(
                     const uint8 Fr_CtrlIdx, const uint16 Fr_LPduIdx,
                                     const Fr_ChannelType Fr_ChnlIdx);

LOCAL_INLINE Std_ReturnType Fr_17_Eray_lRecfgDetChkCycleVal(
                   const uint8 Fr_CycleRepetition, const uint8 Fr_CycleOffset);

LOCAL_INLINE Std_ReturnType Fr_17_Eray_lRecfgDetChkHeaderPL(
                   const uint8 Fr_CtrlIdx, const uint16 Fr_LPduIdx,
                   const uint8 Fr_PayloadLength, const uint16 Fr_HeaderCRC);

#endif /* (FR_17_ERAY_RECONFIG_LPDU, FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */

static void Fr_17_Eray_lReceiveDataCopy(const uint8 Fr_CtrlIdx,
                                        uint8 * const Fr_LSduPtr,
                                        uint8 * const Fr_LSduLengthPtr);

static Std_ReturnType Fr_17_Eray_lRxTransferToOBF(const uint8 Fr_CtrlIdx,
                                                  const uint16 Fr_LPduIdx,
                                                  const uint8 MsgBufferIdx);

LOCAL_INLINE Std_ReturnType Fr_17_Eray_lTrnsfHdrToOBF(
                                              const uint8 Fr_CtrlIdx,
                                              const uint8 MsgBufferIdx);

#if(((MCAL_AR_VERSION == MCAL_AR_422) &&\
          (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON))\
             || (FR_17_ERAY_RUNTIME_ERROR_DETECT == STD_ON))
static void Fr_17_Eray_lReportRuntimeDetError(
                                  const uint8 ApiId, const uint8 ErrorId);

/* FR_17_ERAY_E_INV_POCSTATE */
LOCAL_INLINE Std_ReturnType Fr_17_Eray_lDetCheckInvPOCState(
                             const uint8 Fr_CtrlIdx, const uint8 ExpectedState,
                                                        const uint8 ServiceId);
#endif

static void Fr_17_Eray_lReportDemError(const Dem_EventIdType EventId,
                                       const Dem_EventStatusType EventStatus);

static Std_ReturnType Fr_17_Eray_lCheckTxLPduStatus(
                                const uint8 Fr_CtrlIdx,
                                const uint16 Fr_LPduIdx,
                                Fr_TxLPduStatusType * const Fr_TxLPduStatusPtr);

static Std_ReturnType Fr_17_Eray_lTransmitTxLPdu(const uint8 Fr_CtrlIdx,
                                          const uint16 Fr_LPduIdx,
                                          const uint8 * const Fr_LSduPtr,
                                          const uint8 Fr_LSduLength);

static Std_ReturnType Fr_17_Eray_lReceiveRxLPdu(
                                  const uint8 Fr_CtrlIdx,
                                  const uint16 Fr_LPduIdx,
                                  uint8 * const Fr_LSduPtr,
                                  Fr_RxLPduStatusType *const Fr_RxLPduStatusPtr,
                                  uint8 * const Fr_LSduLengthPtr);

#if(FR_17_ERAY_EXTENDED_LPDU_REPORTING == STD_ON)
static Std_ReturnType Fr_17_Eray_lExtendedLPduReporting(
                            const uint8 Fr_CtrlIdx,
                            const uint16 Fr_LPduIdx,
                            Fr_SlotAssignmentType * const Fr_SlotAssignmentPtr
                            );

static Fr_ChannelType Fr_17_Eray_lCheckChannelType(uint32 Fr_ChannelId);
#endif

static Std_ReturnType Fr_17_Eray_lReadHeader(
                            const uint8 Fr_CtrlIdx,
                            const uint16 Fr_LPduIdx
                            );

/* Memory Map of the FR Code */
#define FR_17_ERAY_STOP_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Fr_17_Eray_MemMap.h"

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
Memory mapping
[/cover] */
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
Memory mapping for constants
[/cover] */
#define FR_17_ERAY_START_SEC_CONST_QM_LOCAL_8
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Fr_17_Eray_MemMap.h"

/*MISRA2012_RULE_8_9_JUSTIFICATION: Variable not defined at block scope.
The variable needs to be placed in the global const section and section
definition is defined in the global scope */
/* Holds the mapping information of the corresponding CC POC state in the
 Fr_17_Eray_CCPOCStateValues array. Based on the value of the pocstate in the
CCSV register, the appropriate index is chosen so that the appropriate value
can be fetched */
static const uint8 Fr_17_Eray_CCPOCStToValueMapIdx[44] =
{
  0U, 1U, 2U, 3U, 4U, 4U, 4U, 4U, 4U, 4U, 4U, 4U, 4U, 4U, 4U, 5U, 6U, 6U, 6U,
  6U, 4U, 4U, 4U, 4U, 4U, 4U, 4U, 4U, 4U, 4U, 4U, 4U, 7U, 8U, 9U, 10U, 11U, 12U,
  13U, 14U, 15U, 16U, 7U, 7U
};

/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
Memory mapping for constants
[/cover] */
#define FR_17_ERAY_STOP_SEC_CONST_QM_LOCAL_8
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Fr_17_Eray_MemMap.h"

/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
Memory mapping
[/cover] */
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
Memory mapping for constants
[/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
#define FR_17_ERAY_START_SEC_CONST_QM_LOCAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Fr_17_Eray_MemMap.h"

/* Contains the startup state and POC state values corresponding to
 DEFAULT_CONFIG state */
static const Fr_17_Eray_CCStateType Fr_17_Eray_CCPOCStateDefault =
{
  FR_STARTUP_UNDEFINED,
  FR_POCSTATE_DEFAULT_CONFIG
};

/* Contains the startup state and POC state values corresponding to
 READY state */
static const Fr_17_Eray_CCStateType Fr_17_Eray_CCPOCStateReady =
{
  FR_STARTUP_UNDEFINED,
  FR_POCSTATE_READY
};

/* Contains the startup state and POC state values corresponding to
 NORMAL_ACTIVE state */
static const Fr_17_Eray_CCStateType Fr_17_Eray_CCPOCStateNrmlActv =
{
  FR_STARTUP_UNDEFINED,
  FR_POCSTATE_NORMAL_ACTIVE
};

/* Contains the startup state and POC state values corresponding to
 NORMAL_PASSIVE state */
static const Fr_17_Eray_CCStateType Fr_17_Eray_CCPOCStateNrmlPssv =
{
  FR_STARTUP_UNDEFINED,
  FR_POCSTATE_NORMAL_PASSIVE
};

/* Contains the startup state and POC state values corresponding to
 HALT state */
static const Fr_17_Eray_CCStateType Fr_17_Eray_CCPOCStateHalt =
{
  FR_STARTUP_UNDEFINED,
  FR_POCSTATE_HALT
};

/* Contains the startup state and POC state values corresponding to
 CONFIG state */
static const Fr_17_Eray_CCStateType Fr_17_Eray_CCPOCStateConfig =
{
  FR_STARTUP_UNDEFINED,
  FR_POCSTATE_CONFIG
};

/* Contains the startup state and POC state values corresponding to
 WAKEUP state */
static const Fr_17_Eray_CCStateType Fr_17_Eray_CCPOCStateWakeup =
{
  FR_STARTUP_UNDEFINED,
  FR_POCSTATE_WAKEUP
};

/* Contains the startup state and POC state values corresponding to
 STARTUP state */
static const Fr_17_Eray_CCStateType Fr_17_Eray_CCPOCStateStartup =
{
  FR_STARTUP_UNDEFINED,
  FR_POCSTATE_STARTUP
};

/* Contains the startup state and POC state values corresponding to
 COLDSTART_LISTEN state */
static const Fr_17_Eray_CCStateType Fr_17_Eray_CCPOCStateCSListen =
{
  FR_STARTUP_COLDSTART_LISTEN,
  FR_POCSTATE_STARTUP
};

/* Contains the startup state and POC state values corresponding to
 COLDSTART_COLLISION_RESOLUTION state */
static const Fr_17_Eray_CCStateType Fr_17_Eray_CCPOCStateCSResolutn =
{
  FR_STARTUP_COLDSTART_COLLISION_RESOLUTION,
  FR_POCSTATE_STARTUP
};

/* Contains the startup state and POC state values corresponding to
 COLDSTART_CONSISTENCY_CHECK state */
static const Fr_17_Eray_CCStateType Fr_17_Eray_CCPOCStateCSCheck =
{
  FR_STARTUP_COLDSTART_CONSISTENCY_CHECK,
  FR_POCSTATE_STARTUP
};

/* Contains the startup state and POC state values corresponding to
 COLDSTART_GAP state */
static const Fr_17_Eray_CCStateType Fr_17_Eray_CCPOCStateCSGap =
{
  FR_STARTUP_COLDSTART_GAP,
  FR_POCSTATE_STARTUP
};

/* Contains the startup state and POC state values corresponding to
 COLDSTART_JOIN state */
static const Fr_17_Eray_CCStateType Fr_17_Eray_CCPOCStateCSJoin =
{
  FR_STARTUP_COLDSTART_JOIN,
  FR_POCSTATE_STARTUP
};

/* Contains the startup state and POC state values corresponding to
 INTEGRATION_COLDSTART_CHECK state */
static const Fr_17_Eray_CCStateType Fr_17_Eray_CCPOCStateIntCSCheck =
{
  FR_STARTUP_INTEGRATION_COLDSTART_CHECK,
  FR_POCSTATE_STARTUP
};

/* Contains the startup state and POC state values corresponding to
 INTEGRATION_LISTEN state */
static const Fr_17_Eray_CCStateType Fr_17_Eray_CCPOCStateIntListen =
{
  FR_STARTUP_INTEGRATION_LISTEN,
  FR_POCSTATE_STARTUP
};

/* Contains the startup state and POC state values corresponding to
 INTEGRATION_CONSISTENCY_CHECK state */
static const Fr_17_Eray_CCStateType Fr_17_Eray_CCPOCStateIntCheck =
{
  FR_STARTUP_INTEGRATION_CONSISTENCY_CHECK,
  FR_POCSTATE_STARTUP
};

/* Contains the startup state and POC state values corresponding to
 INITIALIZE_SCHEDULE state */
static const Fr_17_Eray_CCStateType Fr_17_Eray_CCPOCStateInitSchedule =
{
  FR_STARTUP_INITIALIZE_SCHEDULE,
  FR_POCSTATE_STARTUP
};

/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
Memory mapping for constants
[/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
#define FR_17_ERAY_STOP_SEC_CONST_QM_LOCAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Fr_17_Eray_MemMap.h"

/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
Memory mapping
[/cover] */
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
Memory mapping for constants
[/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
#define FR_17_ERAY_START_SEC_CONST_QM_LOCAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Fr_17_Eray_MemMap.h"

/* ERAY base address Kernel wise */
#if (FR_17_ERAY_NUM_CONTROLLERS_IN_DEVICE == 1u)
  static Ifx_ERAY* const ERAY[] = { &MODULE_ERAY0 };
#endif

#if (FR_17_ERAY_NUM_CONTROLLERS_IN_DEVICE == 2u)
static Ifx_ERAY* const ERAY[] = { &MODULE_ERAY0, &MODULE_ERAY1 };
#endif

/*MISRA2012_RULE_8_9_JUSTIFICATION: Variable not defined at block scope.
The variable needs to be placed in the global const section and section
definition is defined in the global scope */
/* Contains the addresses of the values of the Startup and POC state
 for different states. */
static const Fr_17_Eray_CCStateType* const Fr_17_Eray_CCPOCStateValues[17] =
{
  &Fr_17_Eray_CCPOCStateDefault,
  &Fr_17_Eray_CCPOCStateReady,
  &Fr_17_Eray_CCPOCStateNrmlActv,
  &Fr_17_Eray_CCPOCStateNrmlPssv,
  &Fr_17_Eray_CCPOCStateHalt,
  &Fr_17_Eray_CCPOCStateConfig,
  &Fr_17_Eray_CCPOCStateWakeup,
  &Fr_17_Eray_CCPOCStateStartup,
  &Fr_17_Eray_CCPOCStateCSListen,
  &Fr_17_Eray_CCPOCStateCSResolutn,
  &Fr_17_Eray_CCPOCStateCSCheck,
  &Fr_17_Eray_CCPOCStateCSGap,
  &Fr_17_Eray_CCPOCStateCSJoin,
  &Fr_17_Eray_CCPOCStateIntCSCheck,
  &Fr_17_Eray_CCPOCStateIntListen,
  &Fr_17_Eray_CCPOCStateIntCheck,
  &Fr_17_Eray_CCPOCStateInitSchedule
};

/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
Memory mapping for constants
[/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
#define FR_17_ERAY_STOP_SEC_CONST_QM_LOCAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Fr_17_Eray_MemMap.h"

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/

/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
Memory mapping
[/cover] */
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
Memory mapping for variables
[/cover] */
#define FR_17_ERAY_START_SEC_VAR_CLEARED_QM_LOCAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Fr_17_Eray_MemMap.h"

/* To store the driver configuration pointer */
static const Fr_17_Eray_ConfigType *Fr_17_Eray_ConfigPtr;

#define FR_17_ERAY_STOP_SEC_VAR_CLEARED_QM_LOCAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Fr_17_Eray_MemMap.h"

/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
Memory mapping
[/cover] */
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
Memory mapping for variables
[/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
#define FR_17_ERAY_START_SEC_VAR_CLEARED_QM_LOCAL_16
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Fr_17_Eray_MemMap.h"
/* Message buffer index to LPDU index mapping */

#if (FR_17_ERAY_NUM_CONTROLLERS_IN_DEVICE == 2u)

  #if (FR_17_ERAY_CONTROLLER0_CONFIGURED == STD_ON)
  static uint16 Fr_17_Eray_MsgBuff2LPduIdx_0[FR_17_ERAY_MSG_BUFF_COUNT_MAX_0];
  #endif

  #if (FR_17_ERAY_CONTROLLER1_CONFIGURED == STD_ON)
  static uint16 Fr_17_Eray_MsgBuff2LPduIdx_1[FR_17_ERAY_MSG_BUFF_COUNT_MAX_1];
  #endif

#endif

#if (FR_17_ERAY_NUM_CONTROLLERS_IN_DEVICE == 1u)
  #if (FR_17_ERAY_CONTROLLER0_CONFIGURED == STD_ON)
  static uint16 Fr_17_Eray_MsgBuff2LPduIdx_0[FR_17_ERAY_MSG_BUFF_COUNT_MAX_0];
  #endif
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
#define FR_17_ERAY_STOP_SEC_VAR_CLEARED_QM_LOCAL_16
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Fr_17_Eray_MemMap.h"

/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
Memory mapping
[/cover] */
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
Memory mapping for constants
[/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
#define FR_17_ERAY_START_SEC_CONST_QM_LOCAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Fr_17_Eray_MemMap.h"
/* Message buffer index to LPDU index mapping */

static uint16 * const
  Fr_17_Eray_MsgBuff2LPduIdxPtr[FR_17_ERAY_MAX_NUM_CONTROLLERS] =

{
#if (FR_17_ERAY_CONTROLLER0_CONFIGURED == STD_ON)
 Fr_17_Eray_MsgBuff2LPduIdx_0,
#else
 NULL_PTR,
#endif
#if ((FR_17_ERAY_NUM_CONTROLLERS_IN_DEVICE > 1U) && \
     (FR_17_ERAY_CONTROLLER1_CONFIGURED == STD_ON))
 Fr_17_Eray_MsgBuff2LPduIdx_1
#else
 NULL_PTR
#endif
};

/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
Memory mapping for constants
[/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
#define FR_17_ERAY_STOP_SEC_CONST_QM_LOCAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Fr_17_Eray_MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
Memory mapping
[/cover] */
/* Memory Map of the FR Code */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
Memory mapping for code
[/cover] */
#define FR_17_ERAY_START_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Fr_17_Eray_MemMap.h"

/*******************************************************************************
** Traceability    : [cover parentID={8E9E3AD1-5F5C-4c17-9529-FAC5AA7701AE}]  **
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
** Parameters (in) : Fr_ConfigPtr - Address to an Fr dependant configuration  **
**                                  structure that contains all information   **
**                                  for operating the Fr subsequently.        **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
void Fr_17_Eray_Init(const Fr_17_Eray_ConfigType * const Fr_ConfigPtr)
{
  uint32 TimeOutCount;
  uint32 TimeOutCountInitial;
  uint32 TimeOutResolution;
  uint32 MeasuredTicks;
  uint8 ModuleClockDivider;
  uint8 CtrlIdx;
  uint8 LogIdx;
  volatile uint8 CRamChk;
  volatile uint8 PbsyChk;
  volatile uint8 DissChk;

  /* [cover parentID={35B419F9-9640-45dc-9D60-41E08B87AEA7}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={3816FAEB-AE39-40fd-9E74-00A7743DD93E}]
  Is the Config Pointer NULL ?
  [/cover] */
  /* FR_17_ERAY_E_INIT_FAILED is reported if input pointer is NULL and return */
  if (Fr_ConfigPtr == NULL_PTR)
  {
    /* [cover parentID={85BFE057-8967-4f8a-9102-B8670BD6134A}]
    Report DET
    [/cover] */
    (void)Det_ReportError(FR_17_ERAY_MODULE_ID, FR_17_ERAY_INSTANCE_ID,
                    FR_17_ERAY_SID_INIT, FR_17_ERAY_E_INIT_FAILED);
  }
  else
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */
  {
    /* [cover parentID={F18008DD-A5B6-4cf0-8342-6456884DC1E7}]
    Store the address of the Config Pointer
    [/cover] */
    /* Store the configuration data address in a global variable to
     enable subsequent API calls to access the configuration data. */
    Fr_17_Eray_ConfigPtr = Fr_ConfigPtr;

    /* [cover parentID={CA45A3D5-FDF1-4d5f-97DE-FAC82038BD66}]
    Additional actions performed in Fr_17_Eray_Init API
    [/cover] */

    /* [cover parentID={8405D0A0-6C50-4406-A750-9799F93638DC}]
    Is Controller Index < num of FR controllers in device ?
    [/cover] */
    for (CtrlIdx = FR_17_ERAY_DEC_ZERO;
         (CtrlIdx < (uint8)FR_17_ERAY_NUM_CONTROLLERS_IN_DEVICE); CtrlIdx++)
    {

      LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[CtrlIdx];

      /* [cover parentID={7187DCB5-971C-41c8-B16F-FF55BB0809D3}]
      Is the Controller Index configured to be used  ?
      [/cover] */
      if (FR_17_ERAY_CTRL_NOT_CONFIGURED !=  LogIdx)
      {

        ModuleClockDivider =
          Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].FrClockDivider;

        /* Clear the DISR bit and write the configured FrClockDivider
        value into the RMC bits */
        /* [cover parentID={03ABF2AE-A492-4384-8CE4-BA40AC1B6FD1}]
        Enable Module Clock of the corresponding controller Index
        [/cover] */
        FR_17_ERAY_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(
            &ERAY[CtrlIdx]->CLC.U,
            ((uint32)ModuleClockDivider << FR_17_ERAY_CLC_RMC_BIT_POS));

        DissChk = ERAY[CtrlIdx]->CLC.B.DISS;

        /* Check the Module Disable Status Bit and if the module is not enabled
        then report Production  error */
        /* [cover parentID={A3CA4CC2-893C-4bb6-AFD6-5AFFF0791ABB}]
        Is the module Clock enabled ?
        [/cover] */
        if (FR_17_ERAY_DEC_ZERO != DissChk )
        {
          /* [cover parentID={A8AE55EE-6C40-4557-A731-061BBA39C444}]
          Is a DEM event configured for controller test ?
          [/cover] */
          if(Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].FrDemCtrlTestResultId
              != (Dem_EventIdType)FR_17_ERAY_DEM_REPORT_DISABLED)
          {
            /* [cover parentID={3A69B72C-1F25-47cc-AFC7-D7A2583D61F7}]
            Report the Production error status as FAILED to Mcal_Wrapper
            [/cover] */
            Fr_17_Eray_lReportDemError(
                Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].FrDemCtrlTestResultId,
                DEM_EVENT_STATUS_FAILED);
          }

        }
        else
        {

          /* Wait till the SUCC1.PBSY bit is cleared to check the POC is ready
             to accept a command */
          TimeOutResolution = Mcal_DelayTickResolution();
          TimeOutCount =
              (uint32)FR_17_ERAY_POC_BUSY_TIMEOUT / TimeOutResolution;
          TimeOutCountInitial = Mcal_DelayGetTick();

          do
          {
            MeasuredTicks = Mcal_DelayGetTick() -  TimeOutCountInitial;
            PbsyChk = ERAY[CtrlIdx]->SUCC1.B.PBSY;
            /* [cover parentID={0B8D11FD-4038-44f8-A805-3B0EBD536762}]
            Is (POC in busy state) AND (timeout has not occurred) ?
            [/cover] */
          } while ((PbsyChk == (uint8)1U) && (TimeOutCount > MeasuredTicks));

          /* [cover parentID={97D8EA8D-4F57-4345-93AB-28DAD10AE7C9}]
          Did a timeout occur ?
          [/cover] */
          if (PbsyChk == (uint8)1U)
          {
            /* [cover parentID={F082684A-25AD-40dd-B777-6CDA221DA560}]
            Is a DEM event configured for controller test ?
            [/cover] */
            if(Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].FrDemCtrlTestResultId
                != (Dem_EventIdType)FR_17_ERAY_DEM_REPORT_DISABLED)
            {
              /* [cover parentID={77ADDD12-051A-421e-A0F8-CD373E11FD51}]
              Report the Production error status as FAILED to Mcal_Wrapper
              [/cover] */
              Fr_17_Eray_lReportDemError(
                Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].FrDemCtrlTestResultId,
                DEM_EVENT_STATUS_FAILED);
            }

          }
          else
          {
            /* CLEAR_RAMS */
            ERAY[CtrlIdx]->SUCC1.B.CMD = FR_17_ERAY_CHI_CMD_CLEAR_RAMS;

            /* Wait till execution of the CHI command CLEAR_RAMS is complete */
            TimeOutResolution = Mcal_DelayTickResolution();
            TimeOutCount =
              (uint32)FR_17_ERAY_CLEAR_RAMS_TIMEOUT / TimeOutResolution;
            TimeOutCountInitial = Mcal_DelayGetTick();

            do
            {
              MeasuredTicks = Mcal_DelayGetTick() -  TimeOutCountInitial;
              CRamChk = ERAY[CtrlIdx]->MHDS.B.CRAM;
              /* [cover parentID={A347436D-DC63-4883-B650-8B6F6A531A07}]
              Is (execution of CLEAR_RAMS command ongoing) AND
              (timeout has not occurred) ?
              [/cover] */
            } while ((CRamChk == (uint8)1U) && (TimeOutCount > MeasuredTicks));

            /* [cover parentID={E495EE4E-FD0A-4fe1-92D8-327FF2081574}]
            Did a timeout occur ?
            [/cover] */
            if (CRamChk == (uint8)1U)
            {
              /* [cover parentID={CF8B763F-2636-438d-B4C0-8C24E346B334}]
              Is a DEM event configured for controller test ?
              [/cover] */
              if(Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].FrDemCtrlTestResultId !=
                  (Dem_EventIdType)FR_17_ERAY_DEM_REPORT_DISABLED)
              {
                /* [cover parentID={918658C5-45A3-450e-8334-FEA976714FF0}]
                Report the Production error status as FAILED to Mcal_Wrapper
                [/cover] */
                Fr_17_Eray_lReportDemError(
                  Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].FrDemCtrlTestResultId,
                  DEM_EVENT_STATUS_FAILED);
              }

            }
            else
            {
              /* ----------------------------------------------------------- */
              /* Construct global array Fr_17_Eray_MsgBuff2LPduIdx[ ] */
              /* [cover parentID={318D23AB-C67A-469a-8FDE-64EF38509067}]
              Invoke the Message Buffer initialization routine
              [/cover] */
              Fr_17_Eray_lMessageBufferInit(CtrlIdx, LogIdx);

            }

          }

        }

      }

    }

  }

}

/*******************************************************************************
** Traceability    : [cover parentID={D99B7473-C544-48a7-B872-FED3A0B03E70}]  **
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
Std_ReturnType Fr_17_Eray_ControllerInit(const uint8 Fr_CtrlIdx)
{
  uint32 ErrorCount;
  Std_ReturnType RetValue;
  uint8 LastConfiguredBuffer;
  uint8 LogIdx;

  #if (FR_17_ERAY_FIFO_CONFIGURED == STD_ON)
  const Fr_17_Eray_RxFifoConfigType *FifoCfgPtr;
  uint8 FifoFFB;
  uint8 FifoDepth;
  #endif

  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */

  ErrorCount = (uint32)FR_17_ERAY_DEC_ZERO;

  #if (FR_17_ERAY_FIFO_CONFIGURED == STD_ON)
  FifoDepth = FR_17_ERAY_DEC_ZERO;
  #endif

  /* [cover parentID={6481021B-509F-4f71-A190-C32F0685663E}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  RetValue = E_OK;

  /* [cover parentID={F04AD0A6-3B45-480a-AD09-E13DF2B64E79}]
  Check for Fr Initialization
  [/cover] */
  /*  FR_17_ERAY_E_INIT_FAILED */
  DevError = Fr_17_Eray_lDetCheckNoInit(FR_17_ERAY_SID_CONTROLLERINIT);

  /* [cover parentID={D013B60D-2A03-40a4-A057-754F45FA8F4F}]
  No Error due to the previous check ?
  [/cover] */
  if(DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={0ACC6099-FA05-4b77-8D6D-BC9D66FB0D40}]
    Check for validity of controller Index
    [/cover] */
    /*  FR_17_ERAY_E_INV_CTRL_IDX */
    DevError = Fr_17_Eray_lDetCheckInvCtrlIdx(
                                   Fr_CtrlIdx, FR_17_ERAY_SID_CONTROLLERINIT);
  }

  /* [cover parentID={771E36F0-ED86-43fd-9B0F-E4E8D1205229}]
  Any DET Error occurred ?
  [/cover] */
  if(DevError != FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={9875948A-8932-4b25-9E0A-AAAE7511CE8B}]
    Mark the return value as Error Detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  if(RetValue == E_OK)
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Clear status and Error flags and change the POC state to CONFIG */
    RetValue = Fr_17_Eray_lClrFlagChangeState(Fr_CtrlIdx);
  }

  /* [cover parentID={ABAFEB96-D9C4-43d2-BC75-7F9478C275E8}]
  Did any Error occur during change in POC state ?
  [/cover] */
  if(RetValue == E_OK)
  {
    /*
      Enable both interrupt lines(INT0SRC & INT1SRC).
      Line 0 is used for absolute timer interrupts
    */

    ERAY[Fr_CtrlIdx]->ILE.U = FR_17_ERAY_ILE_ENABLE_BOTH_LINES;

    ERAY[Fr_CtrlIdx]->SILS.U = FR_17_ERAY_SILS_TIMER_LINES;
    /*-------------------  MRC Register configuration  ----------------------*/
    /*
      First Dynamic Buffer configuration.
      Its value is hard coded to 0, meaning no group of Message Buffers
      exclusively for the static segment configured.

      Its configuration doesn't have significance w.r.t AUTOSAR requirements.
      FDB is used to disable transmission of message Buffers for static
      segment with numbers >= FDB when MRC.SEC = 1 or 3.
      AUTOSAR requirements do not require MRC.SEC to be 1 or 3.
    */
    ERAY[Fr_CtrlIdx]->MRC.B.FDB = FR_17_ERAY_DEC_ZERO;

    LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];
    /*  Last Configured Buffer
      01H..7FH: Number of Message Buffers is LCB + 1
      80H..FFH: No Message Buffer configured
     */
    LastConfiguredBuffer =
     Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].MsgBuffCountMax - FR_17_ERAY_DEC_ONE;
    ERAY[Fr_CtrlIdx]->MRC.B.LCB = (uint8)LastConfiguredBuffer;

    /* [cover parentID={413A46E5-95E2-47b3-8554-C87C5BEDDF51}]
    Is FIFO Configured ?
    [/cover] */
    #if (FR_17_ERAY_FIFO_CONFIGURED == STD_ON)
    FifoCfgPtr = Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].RxFifoConfigPtr;

    /* [cover parentID={1877E67A-4158-44b6-B7FF-37B3E5B52479}]
    Is the FIFO Pointer NULL ?
    [/cover] */
    /* If the FIFO pointer is not Null, then get the depth of FIFO */
    if (FifoCfgPtr != NULL_PTR)
    {
      FifoDepth = FifoCfgPtr->FrFifoDepth;
    }

    /* [cover parentID={A194221D-74B3-4b18-94AC-DEB23F56A518}]
    Is FIFO Depth greater than zero ?
    [/cover] */
    if (FifoDepth > FR_17_ERAY_DEC_ZERO)
    {
      /*  First Buffer of FIFO
      00H..7EH: Message Buffers from FFB to LCB assigned to the FIFO
      7FH: All Message Buffers assigned to the FIFO
      */
      /* [cover parentID={0071FB9A-2A40-4075-944B-1553FE55E9C4}]
      Set the First FIFO Buffer field to a value ->
      (Total number of message buffers - the FIFO depth)
      [/cover] */
      FifoFFB = Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].MsgBuffCountMax -
                                                               FifoDepth;
      /*(Total number of message buffers - FrFifoDepth)*/
      ERAY[Fr_CtrlIdx]->MRC.B.FFB = FifoFFB;

      /* [cover parentID={E12B427F-0345-4b08-BD51-994A75C04681}]
      Set the FIFO Rejection Filter and Rejection Filter Mask as per
      the configured values
      [/cover] */
      /* Configure Fifo Rejection Filter Register based on configuration */
      ERAY[Fr_CtrlIdx]->FRF.U = FifoCfgPtr->FrFifoFrfCfg;

      /* Configure FRFM.MFID */
      ERAY[Fr_CtrlIdx]->FRFM.B.MFID = FifoCfgPtr->FrFifoFrfm;

      /* Configure the Critical level */
      ERAY[Fr_CtrlIdx]->FCL.B.CL = FifoDepth;

    }
    else
    #endif /* FR_17_ERAY_FIFO_CONFIGURED == STD_ON */
    {
      /*
        First Buffer of FIFO
        FIFO is not supported by the driver. No message buffers assigned to
        the FIFO, if FFB >= 128
      */
      /* [cover parentID={A0066037-F06A-48cc-82CF-92E2AE95B1DD}]
      Set the First FIFO Buffer field (in MRC) to a value 128
      (FIFO not configured)
      [/cover] */
      ERAY[Fr_CtrlIdx]->MRC.B.FFB = FR_17_ERAY_NO_FIFO_MSG_BUFFERS;
    }

    /* Secure Buffers configuration:Enable if FrIf uses LPDU based */
    /* [cover parentID={F3F7E42F-033C-4ec0-90E1-C070581C26C6}]
    Is Prepare LPdu / Reconfig LPdu Enabled ?
    [/cover] */
    #if (FR_17_ERAY_RECONFIG_LPDU == STD_ON)
    ERAY[Fr_CtrlIdx]->MRC.B.SEC = FR_17_ERAY_BUFFER_RECONFIG_ALLOWED;
    #else
    /* Enable if the driver internal reconfiguration is ON */
    /* [cover parentID={679657AD-F578-4e35-B6A5-835AEA957771}]
    Is Internal buffer Reconfig On ?
    [/cover] */
    if (Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].FrIsBuffReconfigOn == 1U)
    {
      ERAY[Fr_CtrlIdx]->MRC.B.SEC = FR_17_ERAY_BUFFER_RECONFIG_ALLOWED;
    }
    else
    {
      /* Lock the reconfiguration as it is not used by Fr or FrIf */
      ERAY[Fr_CtrlIdx]->MRC.B.SEC = FR_17_ERAY_BUFFER_RECONFIG_LOCKED;
    }
    #endif

    /*
    Note:
      MRC.SPLM = 0 (Reset value; It is left untouched).
      Only Message Buffer 0 locked against reconfiguration.
      As per AUTOSAR, at most one slot id is used for SYNC frame transmission
      (Multiplicity of PKeySlotId is 0..1)

      This bit is only evaluated if the node is configured as sync node
      (SUCC1.TXSY = 1) or for single slot mode operation
      (SUCC1.TSM = 1).

      Hence,
      - the msg buf 0 CAN be shared among LPDUs if PKeySlotUsedForSync = false
      - the msg buf 0 CANNOT be shared among LPDUs if PKeySlotUsedForSync = true
    */

    /* Configure the message buffers */
    RetValue = Fr_17_Eray_lConfigMessageBuffer(Fr_CtrlIdx, LogIdx);

    /* [cover parentID={0E44F9EA-E39F-4d7c-A581-8F3D293753EC}]
    Any Error detected in buffer configuration ?
    [/cover] */
    if(RetValue == E_OK)
    {
      /* [cover parentID={7BEB3977-A6F6-4281-8F04-C586AE8EFAEB}]
      Update the Communication Controller configuration registers as per
      the configured values
      [/cover] */
      /*--------------- Communication controller Configuration -------------*/

      ERAY[Fr_CtrlIdx]->SUCC1.U =
       ((Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].CCCfgPtr->Succ1CfgVal) |
        ((uint32)FR_17_ERAY_CHI_CMD_CONFIG));

      ERAY[Fr_CtrlIdx]->SUCC2.U =
      Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].CCCfgPtr->Succ2CfgVal;

      ERAY[Fr_CtrlIdx]->SUCC3.U =
      Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].CCCfgPtr->Succ3CfgVal;

      ERAY[Fr_CtrlIdx]->NEMC.U =
      Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].CCCfgPtr->NemcCfgVal;

      ERAY[Fr_CtrlIdx]->PRTC1.U =
      Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].CCCfgPtr->Prtc1CfgVal;

      ERAY[Fr_CtrlIdx]->PRTC2.U =
      Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].CCCfgPtr->Prtc2CfgVal;

      ERAY[Fr_CtrlIdx]->MHDC.U =
      Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].CCCfgPtr->MhdcCfgVal;

      ERAY[Fr_CtrlIdx]->GTUC01.U =
       Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].CCCfgPtr->Gtuc01CfgVal;

      ERAY[Fr_CtrlIdx]->GTUC02.U =
       Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].CCCfgPtr->Gtuc02CfgVal;

      ERAY[Fr_CtrlIdx]->GTUC03.U =
      Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].CCCfgPtr->Gtuc03CfgVal;

      ERAY[Fr_CtrlIdx]->GTUC04.U =
       Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].CCCfgPtr->Gtuc04CfgVal;

      ERAY[Fr_CtrlIdx]->GTUC05.U =
       Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].CCCfgPtr->Gtuc05CfgVal;

      ERAY[Fr_CtrlIdx]->GTUC06.U =
       Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].CCCfgPtr->Gtuc06CfgVal;

      ERAY[Fr_CtrlIdx]->GTUC07.U =
      Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].CCCfgPtr->Gtuc07CfgVal;

      ERAY[Fr_CtrlIdx]->GTUC08.U =
       Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].CCCfgPtr->Gtuc08CfgVal;

      ERAY[Fr_CtrlIdx]->GTUC09.U =
       Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].CCCfgPtr->Gtuc09CfgVal;

      ERAY[Fr_CtrlIdx]->GTUC10.U =
       Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].CCCfgPtr->Gtuc10CfgVal;

      ERAY[Fr_CtrlIdx]->GTUC11.U =
       Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].CCCfgPtr->Gtuc11CfgVal;

      ERAY[Fr_CtrlIdx]->CUST1.U =
       Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].CCCfgPtr->Cust1CfgVal;

      /*---------------------- CC Test ----------------------------*/
      #if (FR_17_ERAY_CTRL_TEST_COUNT != 0U)
      /* [cover parentID={F4712F22-C38D-4560-9E06-22302EF2C354}]
      Invoke the Routine which verifies that parameters were written
       properly into the FlexRay CC
      [/cover] */
      RetValue = Fr_17_Eray_lVerifyCCConfig(Fr_CtrlIdx, LogIdx);

      /* [cover parentID={B2A12929-F9F5-46e9-AB06-71ABEDD74C30}]
      Any Error detected during verification?
      [/cover] */
      if(RetValue == E_OK)
      #endif  /* (FR_17_ERAY_CTRL_TEST_COUNT != 0U) */
      {
        /* [cover parentID={9AADE2D9-A5D9-4f7b-ABDF-B36BB96DCB20}]
        Switch the CC to POC:Ready state
        [/cover] */
        /* Switch the CC to POC:Ready state */
        RetValue = Fr_17_Eray_lChangePOCToReady(Fr_CtrlIdx);

        /* [cover parentID={DA00F28C-4502-48a5-9CA5-CBE74F4D9AB4}]
        Did error occur during POC state change to READY state
        [/cover] */
        if(RetValue == E_OK)
        {
          ErrorCount += Fr_17_Eray_lWaitTillPOCChange
                                        (Fr_CtrlIdx, FR_17_ERAY_POCS_READY);


          /* [cover parentID={256870B2-C056-4f94-81B3-87ECAFDF4588}]
          Did timeout error occur ?
          [/cover] */
          if (ErrorCount != (uint32)FR_17_ERAY_DEC_ZERO)
          {
            /* [cover parentID={6C058469-C767-4124-8A54-6CDEEF1463C7}]
            Mark the return value as Error Detected
            [/cover] */
            /* Command not accepted or POC state change did not happen->Time
            out->Production error */
            RetValue = E_NOT_OK;
          }
          /* If there is No error - then return E_OK */
          /* [cover parentID={F44160A5-E693-4c4f-91C1-CCAA62BF84CA}]
          Mark the return value as Successfully finished
          [/cover] */
        }
      }
    }
  }
  return RetValue;
}

/*******************************************************************************
** Traceability    : [cover parentID={E702EE89-030A-4041-AF9E-4647FE54DD7C}]  **
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
Std_ReturnType Fr_17_Eray_StartCommunication(const uint8 Fr_CtrlIdx )
{
  uint32 ErrorCount;
  Std_ReturnType RetValue;

  /* [cover parentID={0115221C-FCF7-4b45-807C-B7209E931BD0}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;

  RetValue = E_OK;

  /* [cover parentID={D4E0D824-2AD9-4350-98C5-E1FF8325832F}]
  Check for Fr Initialization
  [/cover] */
  /*  FR_17_ERAY_E_INIT_FAILED */
  DevError = Fr_17_Eray_lDetCheckNoInit(FR_17_ERAY_SID_STARTCOMMUNICATION);

  /* [cover parentID={22B86C8A-A7B4-4799-8797-734D0F05637D}]
  No DET Error due to the previous check ?
  [/cover] */
  if(DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={04F7DEEF-2CDE-4e15-9FF2-04D52E2A9CA5}]
    Check for validity of controller Index
    [/cover] */
    /* FR_17_ERAY_E_INV_CTRL_IDX */
    DevError = Fr_17_Eray_lDetCheckInvCtrlIdx(Fr_CtrlIdx,
                                            FR_17_ERAY_SID_STARTCOMMUNICATION);
  }

  /* [cover parentID={58C14B12-5DC8-4e16-9EBE-0610DFDBD287}]
  Any DET Error detected from the previous checks ?
  [/cover] */
  /* Return if a development error detected */
  if (DevError != FR_17_ERAY_E_DET_NO_ERR)

  {
    /* [cover parentID={C76B43CD-F93C-47ac-A484-64F59D1CBED0}]
    Mark the return value as Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  /* Driver is not initialized/invalid controller index, avoid register
     access */

  /* [cover parentID={F74E2529-EE4B-4f34-8EF9-4EC1415B0354}]
  Any DET error occurred ?
  [/cover] */
  if(RetValue == E_OK)
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)*/
  {
    /* ( ASR version is 422 and DET is Enabled ) or Runtime error detect
       is enabled */
    #if(((MCAL_AR_VERSION == MCAL_AR_422) &&\
          (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON))\
             || (FR_17_ERAY_RUNTIME_ERROR_DETECT == STD_ON))
    /* [cover parentID={97E729F0-EED2-4c24-B3B1-06906B4CBF42}]
    Check whether POC State is Ready
    [/cover] */
    RetValue = Fr_17_Eray_lDetCheckInvPOCState(Fr_CtrlIdx,
                    FR_17_ERAY_POCS_READY, FR_17_ERAY_SID_STARTCOMMUNICATION);

    /* [cover parentID={0A2503A2-DC54-4283-AB9D-46E17450A25C}]
    Is there DET Error due to the previous check ?
    [/cover] */
    if(RetValue == E_OK)
    #endif /*(((MCAL_AR_VERSION == MCAL_AR_422) &&\
          (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON))\
             || (FR_17_ERAY_RUNTIME_ERROR_DETECT == STD_ON))*/
    {
      ErrorCount = (uint32)FR_17_ERAY_DEC_ZERO;

      /* [cover parentID={35A7DD24-C3EA-4e15-AD6F-67AF0EC0F5AB}]
      Issue the CC CHI command 'RUN'
      [/cover] */
      /*
      Invoke the CC CHI command RUN, which initiates the startup procedure
      within the FlexRay CC.
      */
      ErrorCount +=
        Fr_17_Eray_lChangePOCState(Fr_CtrlIdx, FR_17_ERAY_CHI_CMD_RUN);

      /* [cover parentID={9E695D62-762E-43c0-A255-88BCA29C60F3}]
      Did any Error occur during invocation of 'RUN' command ?
      [/cover] */
      if (ErrorCount == (uint32)FR_17_ERAY_DEC_ZERO)
      {
        /* [cover parentID={830A74D6-3125-4e27-A695-766C3E0FCEE1}]
        Mark the return value as successfully finished
        [/cover] */
        RetValue = E_OK;
      }
      else
      {
        /* [cover parentID={9C39AE5A-8692-409a-965C-B202DB1EAEDE}]
        Mark the return value as Error Detected
        [/cover] */
        /* Command not accepted --> Time out --> Production error */
        RetValue = E_NOT_OK;
      }
    }
  }
  return RetValue;
}

/*******************************************************************************
** Traceability    : [cover parentID={6AA539D9-2ED4-4dd0-BCD4-F032363A4615}]  **
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
Std_ReturnType Fr_17_Eray_AllowColdstart(const uint8 Fr_CtrlIdx )
{
  uint32 ErrorCount;
  Std_ReturnType RetValue;

  #if(((MCAL_AR_VERSION == MCAL_AR_422) &&\
          (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON))\
             || (FR_17_ERAY_RUNTIME_ERROR_DETECT == STD_ON))
  uint8 TmpReg8;
  #endif

  /* [cover parentID={01511DAF-865D-4c86-AE27-4571D8A08907}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;

  RetValue = E_OK;

  /* [cover parentID={C8A16BF6-696D-45e7-ABF8-5D274E7C9382}]
  Check for Fr Initialization
  [/cover] */
  /*  FR_17_ERAY_E_INIT_FAILED */
  DevError = Fr_17_Eray_lDetCheckNoInit(FR_17_ERAY_SID_ALLOWCOLDSTART);

  /* [cover parentID={B0CE483E-9C1C-4481-B2A0-E8BAC51B4144}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={6E77DD72-E29B-483b-991D-8595262ECF27}]
    Check for validity of controller Index
    [/cover] */
    /*  FR_17_ERAY_E_INV_CTRL_IDX */
    DevError = Fr_17_Eray_lDetCheckInvCtrlIdx(Fr_CtrlIdx,
                                                FR_17_ERAY_SID_ALLOWCOLDSTART);
  }

  /* Return if a development error detected */
  /* [cover parentID={7D0BFFE0-2145-45cf-A876-AE92AF2BD47E}]
  Any DET Error detected from the previous checks ?
  [/cover] */
  if (DevError != FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={8B367682-C3A3-40ef-BE1D-1DBF7BE4AF6F}]
    Mark the return value as Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  /* [cover parentID={27896B62-5CB3-4d26-A431-7CB6AC725537}]
  Any DET error occurred ?
  [/cover] */
  if(RetValue == E_OK)
  #endif
  {
  /* (ASR version is 422 and DET is Enabled ) or Runtime error detect
     is enabled */
  #if(((MCAL_AR_VERSION == MCAL_AR_422) &&\
          (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON))\
             || (FR_17_ERAY_RUNTIME_ERROR_DETECT == STD_ON))
    TmpReg8 = ERAY[Fr_CtrlIdx]->CCSV.B.POCS;
    /* [cover parentID={0D20D5B6-EAC6-44d1-94A8-CE04425D5163}]
    Is the POC state in either DEFAULT_CONFIG, CONFIG or HALT state ?
    [/cover] */
    /*  FR_17_ERAY_E_INV_POCSTATE */
    if (( TmpReg8 == FR_17_ERAY_POCS_DEFAULT_CONFIG) ||
        (TmpReg8 == FR_17_ERAY_POCS_CONFIG) ||
        (TmpReg8 == FR_17_ERAY_POCS_HALT)
       )
    {
      /* [cover parentID={E9704A13-37EE-4b95-888D-23A9CE06C1AA}]
      Report DET
      [/cover] */
      Fr_17_Eray_lReportRuntimeDetError(FR_17_ERAY_SID_ALLOWCOLDSTART,
                                                   FR_17_ERAY_E_INV_POCSTATE);
      RetValue = E_NOT_OK;
    }
    else
    #endif /* (((MCAL_AR_VERSION == MCAL_AR_422) &&\
            (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON))\
               || (FR_17_ERAY_RUNTIME_ERROR_DETECT == STD_ON)) */
    {
      /* [cover parentID={57CD20B6-E307-41cd-96F7-FCD52CF4001F}]
      Issue the CC CHI command "ALLOW_COLDSTART"
      [/cover] */
      ErrorCount = Fr_17_Eray_lChangePOCState(Fr_CtrlIdx,
                      FR_17_ERAY_CHI_CMD_ALLOW_COLDSTART);

      /* [cover parentID={04F81C6E-866B-4b56-8CC2-4CA9E5BDC3BC}]
      Did any Error occur during invocation of ALLOW_COLSTART command ?
      [/cover] */
      if (ErrorCount != (uint32)FR_17_ERAY_DEC_ZERO)
      {
        /* [cover parentID={AFA76200-DD67-4972-AE43-CF8EA9122968}]
        Mark the return value as Error Detected
        [/cover] */
        /* Command not accepted --> Time out --> Production error */
        RetValue = E_NOT_OK;
      }
      else
      {
        /* [cover parentID={EEFC8689-3479-4bb6-ACB9-7509C821F857}]
        Mark the return value as successfully finished
        [/cover] */
        RetValue = E_OK;
      }
    }
  }

  return RetValue;
}

/*******************************************************************************
** Traceability    : [cover parentID={077DBAEE-AA6B-4f37-8F6A-042A6A8330A0}]  **
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
Std_ReturnType Fr_17_Eray_AllSlots(const uint8 Fr_CtrlIdx )
{
  Std_ReturnType RetValue;
  uint32 ErrorCount;

  /* [cover parentID={2039D3A3-2311-47dd-9155-4A27EACFF3DB}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;

  RetValue = E_OK;

  /* [cover parentID={5C9EF1A5-EF15-4adb-BA6C-5886F81E27F1}]
  Check for Fr Initialization
  [/cover] */
  /* FR_17_ERAY_E_INIT_FAILED */
  DevError = Fr_17_Eray_lDetCheckNoInit(FR_17_ERAY_SID_ALLSLOTS);

  /* [cover parentID={93C348FF-A62B-4e2b-9FD2-32B61F4771DA}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={DF51FF4B-DA19-4ecc-A040-3F653526DF91}]
    Check for validity of controller Index
    [/cover] */
    /* FR_17_ERAY_E_INV_CTRL_IDX */
    DevError = Fr_17_Eray_lDetCheckInvCtrlIdx(Fr_CtrlIdx,
                                               FR_17_ERAY_SID_ALLSLOTS);
  }

  /* Return if a development error detected */
  /* [cover parentID={B6CE52B7-6317-478d-9972-091A695AB133}]
  Any DET Error detected from the previous checks ?
  [/cover] */
  if (DevError != FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={1186B37B-B9BF-4b00-8611-41078B389855}]
    Mark the return value as Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  /* [cover parentID={E9245B87-C622-4716-9E5F-69313A85BF1E}]
  Any DET error occurred ?
  [/cover] */
  if (RetValue == E_OK)
  #endif /*(FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)*/
  {
    /* (ASR version is 422 and DET is Enabled ) or Runtime error detect is enabled */
    #if(((MCAL_AR_VERSION == MCAL_AR_422) &&\
        (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON))\
           || (FR_17_ERAY_RUNTIME_ERROR_DETECT == STD_ON))
    /*
      FR_17_ERAY_E_INV_POCSTATE if controller is not synchronized to global time
    */
    /* [cover parentID={5CA38705-2295-49c7-9159-561B016E772A}]
    Get the CC synchronization status with global time
    [/cover] */
    /* [cover parentID={D5DD91C1-46CB-4131-ABF4-B32F18D7276F}]
    Is Fr CC Not in sync with global time ?
    [/cover] */
    if (Fr_17_Eray_lIsCCInSync(Fr_CtrlIdx) == (uint32)FR_17_ERAY_DEC_ZERO)
    {
      /* [cover parentID={D93E33C4-B2DC-4d05-9F8D-7271861E8CE1}]
      Report DET
      [/cover] */
      Fr_17_Eray_lReportRuntimeDetError(FR_17_ERAY_SID_ALLSLOTS,
                                                FR_17_ERAY_E_INV_POCSTATE);
      RetValue = E_NOT_OK;

    }
    else
    #endif /*(((MCAL_AR_VERSION == MCAL_AR_422) &&\
             (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON))\
               || (FR_17_ERAY_RUNTIME_ERROR_DETECT == STD_ON))*/
    {
      ErrorCount = (uint32)FR_17_ERAY_DEC_ZERO;

      /* [cover parentID={DA1C2B3F-1667-4340-843A-D4D6769C12DE}]
      Issue the CC CHI command "ALL_SLOTS"
      [/cover] */
      /* Issue CC CHI command "ALL_SLOTS" */
      ErrorCount += Fr_17_Eray_lChangePOCState(Fr_CtrlIdx,
                        FR_17_ERAY_CHI_CMD_ALL_SLOTS);

      /* [cover parentID={B99DA12D-51E6-4026-B0EC-C15B0154959B}]
      Did any Error occur during invocation of HALT command ?
      [/cover] */
      if (ErrorCount == (uint32)FR_17_ERAY_DEC_ZERO)
      {
        /* [cover parentID={FE81D42E-65C1-4df0-86AA-3DEF3B0BB99E}]
        Mark the return value as successfully finished
        [/cover] */
        RetValue = E_OK;
      }
      else
      {
        /* [cover parentID={9FE54E60-6AA2-4e9d-AF19-F521BFCEDFD8}]
        Mark the return value as Error Detected
        [/cover] */
        /* Command not accepted --> Time out --> Production error */
        RetValue = E_NOT_OK;
      }
    }
  }

  return RetValue;
}

/*******************************************************************************
** Traceability    : [cover parentID={5F86F0F7-CEC4-4dc8-986C-0F6CC7BFF190}]  **
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
Std_ReturnType Fr_17_Eray_HaltCommunication(const uint8 Fr_CtrlIdx )
{
  uint32 ErrorCount;
  Std_ReturnType RetValue;

  /* [cover parentID={C881BC93-7167-49ef-9B89-E71DFAE54D17}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;

  RetValue = E_OK;

  /* [cover parentID={7F910055-E023-4b2a-84D6-6E5D87890C9C}]
  Check for Fr Initialization
  [/cover] */
  /* FR_17_ERAY_E_INIT_FAILED */
  DevError = Fr_17_Eray_lDetCheckNoInit(FR_17_ERAY_SID_HALTCOMMUNICATION);

  /* [cover parentID={A40935B6-CC12-48ad-8036-913ABE82C7B0}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={7AB40C4F-154D-434e-AEA1-4BABC0474987}]
    Check for validity of controller Index
    [/cover] */
    /* FR_17_ERAY_E_INV_CTRL_IDX */
    DevError = Fr_17_Eray_lDetCheckInvCtrlIdx(Fr_CtrlIdx,
                                             FR_17_ERAY_SID_HALTCOMMUNICATION);
  }

  /* Return if a development error detected */
  /* [cover parentID={F946CA16-4275-4e26-B981-9E8BD5EF59BB}]
  Any DET Error detected from the previous checks ?
  [/cover] */
  if (DevError != FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={124B123F-C87F-4ed0-87FF-B6944DA95649}]
    Mark the return value as Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  /* [cover parentID={E7CF310D-A6E1-4ec0-BA74-1E59B68873B1}]
  Any DET error occurred ?
  [/cover] */
  if(RetValue == E_OK)
  #endif /*(FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)*/
  {
    /* [cover parentID={3F08650D-5E0F-4464-902C-4B1B0F876072}]
    Get the CC synchronization status with global time
    [/cover] */
    /* (ASR version is 422 and DET is Enabled ) or Runtime error detect is enabled */
    #if(((MCAL_AR_VERSION == MCAL_AR_422) &&\
            (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON))\
               || (FR_17_ERAY_RUNTIME_ERROR_DETECT == STD_ON))
    /* [cover parentID={2D0DD4B1-3C5F-4e6b-AD7C-06D17C3EC1F9}]
    Is FR CC is not in sync with Global time ?
    [/cover] */
    if (Fr_17_Eray_lIsCCInSync(Fr_CtrlIdx) == (uint32)FR_17_ERAY_DEC_ZERO)
    {
      /* [cover parentID={8C083FAE-C252-422a-88EC-3E57FA3924AA}]
      Report Runtime or DET error
      [/cover] */

      Fr_17_Eray_lReportRuntimeDetError(FR_17_ERAY_SID_HALTCOMMUNICATION,
                                                    FR_17_ERAY_E_INV_POCSTATE);

      RetValue = E_NOT_OK;
    }
    else
    #endif
    {
      ErrorCount = (uint32)FR_17_ERAY_DEC_ZERO;

      /* [cover parentID={75F6D0B1-0E44-4e4f-BBCF-350D4BF1A856}]
      Issue the CC CHI command 'HALT'
      [/cover] */
      /* Issue CC CHI command "HALT" */
      ErrorCount +=
          Fr_17_Eray_lChangePOCState(Fr_CtrlIdx,FR_17_ERAY_CHI_CMD_HALT);

      /* [cover parentID={E9CC1398-B370-42cc-9BE6-0EC3DCD3A7EC}]
      Did any Error occur during invocation of HALT command ?
      [/cover] */
      if (ErrorCount == (uint32)FR_17_ERAY_DEC_ZERO)
      {
        /* [cover parentID={27CDE78E-7396-497b-8EDE-384416EF6A44}]
        Mark the return value as successfully finished
        [/cover] */
        RetValue = E_OK;
      }
      else
      {
        /* [cover parentID={9A2BAEFE-2B94-4c3c-B629-36C1443DAC2E}]
        Mark the return value as Error Detected
        [/cover] */
        /* Command not accepted --> Time out --> Production error */
        RetValue = E_NOT_OK;
      }
    }
  }
  return RetValue;

}

/*******************************************************************************
** Traceability    : [cover parentID={8A38CCF5-A769-40e5-A9B5-27AF037E1A7D}]  **
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
Std_ReturnType Fr_17_Eray_AbortCommunication(const uint8 Fr_CtrlIdx )
{
  uint32 ErrorCount;
  Std_ReturnType RetValue;
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */

  /* [cover parentID={05481175-E2AC-4807-9BAA-14C41790BCAB}]
  Mark the return value as successfully finished
  [/cover] */
  RetValue = E_OK;

  /* [cover parentID={D2401891-A617-4dd1-8100-A80A59716986}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={19C47667-67E2-4e8e-A1FC-E8663C427F77}]
  Check for Fr Initialization
  [/cover] */
  /* FR_17_ERAY_E_INIT_FAILED */
  DevError = Fr_17_Eray_lDetCheckNoInit(FR_17_ERAY_SID_ABORTCOMMUNICATION);

  /* [cover parentID={E9CEED54-4C37-413e-AD95-DD635FBE73E4}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={82CB07E6-D11F-4c38-A86F-05C3ED3BA14C}]
    Check for validity of controller Index
    [/cover] */
    /* FR_17_ERAY_E_INV_CTRL_IDX */
    DevError = Fr_17_Eray_lDetCheckInvCtrlIdx(Fr_CtrlIdx,
                                           FR_17_ERAY_SID_ABORTCOMMUNICATION);
  }

  /* Return if a development error detected */
  /* [cover parentID={7CEA355E-3346-4c74-9E1A-53DF97EF8672}]
  Any DET Error detected from the previous checks ?
  [/cover] */
  if (DevError != FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={DDBFCE4E-0DF8-42f7-A69F-59D481F6CE4D}]
    Mark the return value as Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  /* [cover parentID={C409671A-58E2-4a9d-A452-F93232751143}]
  Any DET error occurred ?
  [/cover] */
  if(RetValue == E_OK)
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */
  {
    ErrorCount = (uint32)FR_17_ERAY_DEC_ZERO;

    /* [cover parentID={291B0454-2E36-4c7f-B838-2E90DC5FFFDA}]
    Issue the CC CHI command 'FREEZE'
    [/cover] */
    /* Issue CC CHI command "FREEZE" */
    ErrorCount +=
        Fr_17_Eray_lChangePOCState(Fr_CtrlIdx,FR_17_ERAY_CHI_CMD_FREEZE);

    /* [cover parentID={DAA8CFF0-1850-4599-94CC-B4B7CDA42F65}]
    Did any Error occur during invocation of FREEZE command ?
    [/cover] */
    if (ErrorCount == (uint32)FR_17_ERAY_DEC_ZERO)
    {
      /* [cover parentID={A66A3DEE-0563-4cb7-81D4-F963C6444638}]
      Wait till the POC state changes to 'HALT'
      [/cover] */
      ErrorCount +=
        Fr_17_Eray_lWaitTillPOCChange(Fr_CtrlIdx,FR_17_ERAY_POCS_HALT);
    }

    /* [cover parentID={23693975-B515-4509-82E0-EADDE5AF034A}]
    Did a timeout error occur while waiting for state change to HALT?
    [/cover] */
    if (ErrorCount != (uint32)FR_17_ERAY_DEC_ZERO)
    {
      /* [cover parentID={B8760C94-068E-460d-807E-F1DCA2FAEC5D}]
      Mark the return value as Error Detected
      [/cover] */
      /* Command not accepted or POC state change did not happen --> Time out ->
          Production error */
      RetValue = E_NOT_OK;
    }
  }

  return RetValue;
}

/*******************************************************************************
** Traceability    : [cover parentID={B1FFDD07-DDD9-4754-BB51-33088073B770}]  **
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
Std_ReturnType Fr_17_Eray_SendWUP(const uint8 Fr_CtrlIdx )
{
  Std_ReturnType RetValue;
  uint32 ErrorCount;

  /* [cover parentID={578F0547-B478-425b-84AF-817B0D331C84}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;

  RetValue = E_OK;

  /* [cover parentID={C30DB5C1-29BE-46f4-BD30-3238F0A746B2}]
  Check for Fr Initialization
  [/cover] */
  /* FR_17_ERAY_E_INIT_FAILED */
  DevError = Fr_17_Eray_lDetCheckNoInit(FR_17_ERAY_SID_SENDWUP);

  /* [cover parentID={F59102F4-F9D6-4f10-86B5-16AE3E4F0555}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={7F650D1F-439E-4817-92DD-EDA7FFE53187}]
    Check for validity of controller Index
    [/cover] */
    /* FR_17_ERAY_E_INV_CTRL_IDX */
    DevError = Fr_17_Eray_lDetCheckInvCtrlIdx(Fr_CtrlIdx,
                                                      FR_17_ERAY_SID_SENDWUP);
  }

  /* Return if a development error detected */
  /* [cover parentID={E087BD36-BDB7-47da-A937-56F1D791B96A}]
  Any DET Error detected from the previous checks ?
  [/cover] */
  if (DevError != FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={C5148255-B59A-431c-91A6-9E0FAE15BF5F}]
    Mark the return value as Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  /* [cover parentID={15B38962-A2C6-42e0-AA93-9C5AF138CA8D}]
  Any DET error occurred ?
  [/cover] */
  if(RetValue == E_OK)
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */
  {
    /* (ASR version is 422 and DET is Enabled ) or
        Runtime error detect is enabled */
    #if(((MCAL_AR_VERSION == MCAL_AR_422) &&\
          (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON))\
             || (FR_17_ERAY_RUNTIME_ERROR_DETECT == STD_ON))
    /* [cover parentID={34E6A817-7DF7-4fd4-A3BA-8C542F8E44DD}]
    Check whether POC state is Ready ?
    [/cover] */
    RetValue = Fr_17_Eray_lDetCheckInvPOCState(Fr_CtrlIdx,
                    FR_17_ERAY_POCS_READY, FR_17_ERAY_SID_SENDWUP);

    /* [cover parentID={26EDE87C-B933-45df-B800-FB7232501785}]
    Is there DET Error due to the previous check ?
    [/cover] */
    if(RetValue == E_OK)
    #endif /*(((MCAL_AR_VERSION == MCAL_AR_422) &&\
          (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON))\
             || (FR_17_ERAY_RUNTIME_ERROR_DETECT == STD_ON))*/
    {
      ErrorCount = (uint32)FR_17_ERAY_DEC_ZERO;

      /* [cover parentID={4FD58854-F79D-41a8-83CA-5BC495DDBB74}]
      Issue the CHI command 'WAKEUP'
      [/cover] */
      /* Issue CC CHI command "WAKEUP" */
      ErrorCount +=
        Fr_17_Eray_lChangePOCState(Fr_CtrlIdx,FR_17_ERAY_CHI_CMD_WAKEUP);

      /* [cover parentID={7575BC6E-CEC0-441c-BA69-EDF3977FD4CC}]
      Did any Error occur during invocation of 'WAKEUP' command ?
      [/cover] */
      if (ErrorCount == (uint32)FR_17_ERAY_DEC_ZERO)
      {
        /* [cover parentID={4E8C6FF5-BC6F-4fad-99F0-753C6A1CC19C}]
        Mark the return value as successfully finished
        [/cover] */
        RetValue = E_OK;
      }
      else
      {
        /* [cover parentID={3336BCFB-17A5-4c98-8D47-B3C409DF58B5}]
        Mark the return value as Error Detected
        [/cover] */
        /* Command not accepted --> Time out --> Production error */
        RetValue = E_NOT_OK;
      }
    }
  }
  return RetValue;
}

/*******************************************************************************
** Traceability    : [cover parentID={281E7EA1-F575-400b-8F02-5CC1B1F020E5}]  **
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
Std_ReturnType Fr_17_Eray_SetWakeupChannel(
                                           const uint8 Fr_CtrlIdx,
                                           const Fr_ChannelType Fr_ChnlIdx
                                           )
{
  uint32 ErrorCount;
  Std_ReturnType RetValue;

  /* [cover parentID={804FA327-ABA5-4baf-B705-FAA78DF6734C}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;

  /* [cover parentID={79A5D5B3-23FF-45b5-AB95-B270B78E4EE7}]
  Mark the return value as successfully finished
  [/cover] */
  RetValue = E_OK;

  /* [cover parentID={38DE0C6B-7DE5-46f5-B2C5-DEAE78C1647A}]
  Check for Fr Initialization
  [/cover] */
  /* FR_17_ERAY_E_INIT_FAILED */
  DevError = Fr_17_Eray_lDetCheckNoInit(FR_17_ERAY_SID_SETWAKEUPCHANNEL);

  /* [cover parentID={C58D1014-807F-4529-86D8-BD7E637AAF27}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={26C80198-63A6-493c-BBB3-29F4E7BE4F43}]
    Check for validity of controller Index
    [/cover] */
    /* FR_17_ERAY_E_INV_CTRL_IDX */
    DevError = Fr_17_Eray_lDetCheckInvCtrlIdx(Fr_CtrlIdx,
                                            FR_17_ERAY_SID_SETWAKEUPCHANNEL);
  }

  /* [cover parentID={6F71692E-D9C9-4177-A027-DD1160010300}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={FAF976D9-2E75-46f0-B19F-51A3D7535D5B}]
    Is the Channel Index Invalid ?
    [/cover] */
    /* FR_17_ERAY_E_INV_CHNL_IDX */
    if ((Fr_ChnlIdx != FR_CHANNEL_A) && (Fr_ChnlIdx != FR_CHANNEL_B))
    {
      /* [cover parentID={A30C2E4B-9B53-4513-9EAF-004B16536E7A}]
      Report DET
      [/cover] */
      (void)Det_ReportError(FR_17_ERAY_MODULE_ID, FR_17_ERAY_INSTANCE_ID,
                   FR_17_ERAY_SID_SETWAKEUPCHANNEL, FR_17_ERAY_E_INV_CHNL_IDX);
      DevError = FR_17_ERAY_E_INV_CHNL_IDX;
    }
  }

  /* Return if a development error detected */
  /* [cover parentID={733A48C4-AFF2-494d-B499-670326997273}]
  Any DET Error detected from the previous checks ?
  [/cover] */
  if (DevError != FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={2C122971-4DC2-44d3-83F8-B980AF92E511}]
    Mark the return value as Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  /* [cover parentID={01DB54CD-0FC2-4f8e-B471-CF80253F9FF7}]
  Any DET error occurred ?
  [/cover] */
  if(RetValue == E_OK)
  #endif /*(FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */
  {
    #if(((MCAL_AR_VERSION == MCAL_AR_422) &&\
          (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON))\
             || (FR_17_ERAY_RUNTIME_ERROR_DETECT == STD_ON))
    /* [cover parentID={F06E6DED-8ECC-4fe1-961B-B2E5CFF740DC}]
    Check whether POC State is Ready
    [/cover] */
    RetValue = Fr_17_Eray_lDetCheckInvPOCState(Fr_CtrlIdx,
                    FR_17_ERAY_POCS_READY, FR_17_ERAY_SID_SETWAKEUPCHANNEL);
    /* [cover parentID={B3EDCE72-F5A4-4788-B39B-63ACDBC9B1B7}]
    Is there DET Error due to the previous check ?
    [/cover] */
    if(RetValue == E_OK)
    #endif /*(((MCAL_AR_VERSION == MCAL_AR_422) &&\
          (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON))\
             || (FR_17_ERAY_RUNTIME_ERROR_DETECT == STD_ON))*/
    {
      ErrorCount = (uint32)FR_17_ERAY_DEC_ZERO;

      /* [cover parentID={1B0D34AC-7DF5-4384-B0BE-B4A6DEAF68FF}]
      Change the POC state to Config
      [/cover] */
      /* Change the CC's POCState to POC:config by invoking the CHI command
      'CONFIG'. */
      ErrorCount +=
        Fr_17_Eray_lChangePOCState(Fr_CtrlIdx,FR_17_ERAY_CHI_CMD_CONFIG);

      /* [cover parentID={5427ABB3-F865-4fbc-BCE4-720A744A6DE5}]
      Any Error occurred during change in POC State ?
      [/cover] */
      if (ErrorCount == (uint32)FR_17_ERAY_DEC_ZERO)
      {
        /* [cover parentID={CCF098AA-2C3B-4ebf-A922-BADB8FFD1A9C}]
        Configure the wakeup channel according to parameter Fr_ChnlIdx
        [/cover] */
        if (Fr_ChnlIdx == FR_CHANNEL_A)
        {
        /* Configure the wakeup channel according to parameter Fr_ChnlIdx. */
          ERAY[Fr_CtrlIdx]->SUCC1.B.WUCS = FR_17_ERAY_WAKEUP_CHNL_A;
        }
        else
        {
          ERAY[Fr_CtrlIdx]->SUCC1.B.WUCS = FR_17_ERAY_WAKEUP_CHNL_B;
        }

        /* [cover parentID={3008FBB9-4DF0-4151-995B-81D71AB32751}]
        Change the POC state to Ready
        [/cover] */
        /*Change the CC's POCState to POC:ready again by invoking the CHI command
        "CONFIG_COMPLETE" */
        RetValue = Fr_17_Eray_lChangePOCToReady(Fr_CtrlIdx);
      }
      else
      {
        /* [cover parentID={E72B1281-85B7-427e-AE13-E23E33FF86BC}]
        Mark the return value Error Detected
        [/cover] */
        /* POC state change did not happen --> Time out --> Production error */
        RetValue = E_NOT_OK;
      }
    }
  }
  return RetValue;
}

/*******************************************************************************
** Traceability    : [cover parentID={A9D99485-843A-4dd8-BB1A-92B1E0D2C1FB}]  **
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
Std_ReturnType Fr_17_Eray_GetPOCStatus(
                                       const uint8 Fr_CtrlIdx,
                                       Fr_POCStatusType * const Fr_POCStatusPtr
                                      )
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION:Union is used to access the register
  contents directly without shift and OR operation. */
  Ifx_ERAY_CCSV RegCCSV;
  Std_ReturnType RetValue;
  uint8 pocstate;
  uint8 ValueIdx;
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */

  /* [cover parentID={51913A0B-1568-4844-939B-F0464B6DC28C}]
  Mark the return value as successfully finished
  [/cover] */
  RetValue = E_OK;

  /* [cover parentID={8AED97B6-E4FA-4f38-B2CD-103AECD3D399}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={3B7F5A6B-3EDE-4492-852E-49BFD232DF3E}]
  Check for Fr Initialization
  [/cover] */
  /* FR_17_ERAY_E_INIT_FAILED */
  DevError = Fr_17_Eray_lDetCheckNoInit(FR_17_ERAY_SID_GETPOCSTATUS);

  /* [cover parentID={EA2E2D60-B490-4f48-820E-3F7DAB7EEEE3}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={3CF42749-D987-4d7a-B943-8B6F764AFF07}]
    Check for validity of controller Index
    [/cover] */
    /* FR_17_ERAY_E_INV_CTRL_IDX */
    DevError = Fr_17_Eray_lDetCheckInvCtrlIdx(Fr_CtrlIdx,
                                                FR_17_ERAY_SID_GETPOCSTATUS);
  }

  /* [cover parentID={D7EC988F-9223-4f8e-8A75-8B07E64957FC}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={022A02B5-8613-4140-87DE-B76D3D638934}]
    Check whether POC Status pointer is NULL
    [/cover] */
    /* FR_17_ERAY_E_PARAM_POINTER */
    DevError = Fr_17_Eray_lDetCheckInvPointer(Fr_POCStatusPtr,
                                                FR_17_ERAY_SID_GETPOCSTATUS);
  }

  /* Return if a development error detected */
  /* [cover parentID={6DDC1886-150A-400a-9DA5-239CFD18E93D}]
  Any DET Error detected from the previous checks ?
  [/cover] */
  if (DevError != FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={58042DCE-1862-44b3-85C3-6593719D6AEB}]
    Mark the return value as Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  /* [cover parentID={9189D210-8265-41c4-863B-F440D2504945}]
  Any DET error occurred ?
  [/cover] */
  if(RetValue == E_OK)
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */
  {
    /* [cover parentID={FE18D254-180E-4830-BBD8-2AAF3CB4A193}]
    Get the Slot status of the POC and update the Fr Status Pointer
    [/cover] */
    RegCCSV.U = ERAY[Fr_CtrlIdx]->CCSV.U;

    /* [cover parentID={040B6C4D-4B0C-4e18-B494-3BC539B80AA5}]
    Write the POC status pointer with the fields cold start noise indicator,
    Halt Request, Freeze Status Indicator, Wakeup status, Error Mode
    [/cover] */
    if (RegCCSV.B.CSNI == FR_17_ERAY_DEC_ONE)
    {
      Fr_POCStatusPtr->ColdstartNoise = (boolean)TRUE;
    }
    else
    {
      Fr_POCStatusPtr->ColdstartNoise = (boolean)FALSE;
    }

    if (RegCCSV.B.HRQ == FR_17_ERAY_DEC_ONE)
    {
      Fr_POCStatusPtr->CHIHaltRequest = (boolean)TRUE;
    }
    else
    {
      Fr_POCStatusPtr->CHIHaltRequest = (boolean)FALSE;
    }

    if (RegCCSV.B.FSI == FR_17_ERAY_DEC_ONE)
    {
      Fr_POCStatusPtr->Freeze = (boolean)TRUE;
    }
    else
    {
      Fr_POCStatusPtr->Freeze = (boolean)FALSE;
    }

    Fr_POCStatusPtr->SlotMode = Fr_17_Eray_lGetSlotMode(Fr_CtrlIdx);
    /* MISRA2012_RULE_10_5_JUSTIFICATION:The value read from the register
       value to be converted to the enum type.The API parameter type is
       an enum type */
    /* MISRA2012_RULE_10_3_JUSTIFICATION:The value read from the register
       value to be converted to the enum type.The API parameter type is
       an enum type */
    Fr_POCStatusPtr->WakeupStatus = (Fr_WakeupStatusType)RegCCSV.B.WSV;

    /* MISRA2012_RULE_10_5_JUSTIFICATION:The value read from the register
       value to be converted to the enum type.The API parameter type is
       an enum type */
    /* MISRA2012_RULE_10_3_JUSTIFICATION:The value read from the register
       value to be converted to the enum type.The API parameter type is
       an enum type */
    Fr_POCStatusPtr->ErrorMode = (Fr_ErrorModeType)ERAY[Fr_CtrlIdx]->CCEV.B.ERRM;

    /* [cover parentID={2FED0CA1-9139-4a7a-90F4-BC45529C6EC1}]
    Read the value of POC Status of the controller
    [/cover] */
    pocstate = RegCCSV.B.POCS;

    /* [cover parentID={A3911D53-0577-4b13-8A0F-D309E8738F64}]
    Is the POC status greater than final valid POC state(STARTUP_SUCCESS) ?
    [/cover] */
    if (pocstate <= FR_17_ERAY_POCS_STARTUP_SUCCESS)
    {
      /* [cover parentID={13901684-EDE4-4746-A9B9-EBF47F3027B3}]
      Update the Fr POC status pointer accordingly for the fields POC State
      and Startup State
      [/cover] */
      ValueIdx = Fr_17_Eray_CCPOCStToValueMapIdx[pocstate];
      Fr_POCStatusPtr->StartupState =
                    Fr_17_Eray_CCPOCStateValues[ValueIdx]->CCStartupState;
      Fr_POCStatusPtr->State =
                    Fr_17_Eray_CCPOCStateValues[ValueIdx]->CCPOCState;
    }
    else
    {
      /* [cover parentID={7A2F64BA-0379-43bd-A356-4FF2FD0E044D}]
      Update the Fr POC status pointer with the default values
      [/cover] */
      Fr_POCStatusPtr->StartupState = FR_STARTUP_UNDEFINED;
      Fr_POCStatusPtr->State = FR_POCSTATE_HALT;
    }

  }
  return RetValue;
}

#if(MCAL_AR_VERSION == MCAL_AR_440)
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
Std_ReturnType  Fr_17_Eray_TransmitTxLPdu
(
    const uint8 Fr_CtrlIdx,
    const uint16 Fr_LPduIdx,
    const uint8 * const Fr_LSduPtr,
    const uint8 Fr_LSduLength,
    Fr_SlotAssignmentType* const Fr_SlotAssignmentPtr
)
{
  Std_ReturnType RetValue;
  #if(FR_17_ERAY_EXTENDED_LPDU_REPORTING == STD_ON)
  const Fr_17_Eray_LPduConfigType *LPduCfgPtr;
  uint8 LogIdx;
  uint32 ChnlId;
  #endif

  /* [cover parentID={DD55BB98-C3D5-4897-BECC-C4C904A089DE}]
  Mark the return value as successfully finished
  [/cover] */
  /* [cover parentID={7EB36DC8-7BD1-46d3-9E98-03B7AB2D6AA2}]
  Mark the return value as Error occured
  [/cover] */
  RetValue = Fr_17_Eray_lTransmitTxLPdu(Fr_CtrlIdx, Fr_LPduIdx,
                                                  Fr_LSduPtr, Fr_LSduLength);
  /* [cover parentID={D622E201-6B91-48dd-9C93-B25EA971EDB2}]
  Extended LPdu reporting is Enabled ?
  [/cover] */
  #if(FR_17_ERAY_EXTENDED_LPDU_REPORTING == STD_ON)
  /* [cover parentID={8F7D3C94-B151-4532-9105-EAAAE1155F20}]
  Is Transmit TX Lpdu API executed successfully and Fr_SlotAssignmentPtr is
  not NULL
  [/cover] */
  if((RetValue == E_OK) && (Fr_SlotAssignmentPtr != NULL_PTR))
  {
    LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];

    LPduCfgPtr = Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].LPduConfigPtr;
    /* [cover parentID={B7023BF5-E2BC-40fb-BF10-7D3E832BAAA1}]
    Is LPdu is Reconfigurable ?
    [/cover] */
    if ((LPduCfgPtr[Fr_LPduIdx].LpduReconfigurable ==
                  (uint8)FR_17_ERAY_LPDU_RECONFIGURABLE))
    {
      /* [cover parentID={995E5350-A3C5-46ad-992B-B9D6C34D9D54}]
      Update current SlotID, ChannelID and Cycle count in Fr_SlotAssignmentPtr
      using RDHS1 register
      [/cover] */
      /*Update LPdu configured cycle count to Fr_SlotAssignmentPtr*/
      Fr_SlotAssignmentPtr->SlotId =  ERAY[Fr_CtrlIdx]->RDHS1.B.FID;

      /*Update LPdu configured Slot ID to Fr_SlotAssignmentPtr*/
      Fr_SlotAssignmentPtr->Cycle =  ERAY[Fr_CtrlIdx]->RDHS1.B.CYC;

      /*Update LPdu configured Channel ID to Fr_SlotAssignmentPtr*/
      ChnlId = ((ERAY[Fr_CtrlIdx]->RDHS1.U>>IFX_ERAY_WRHS1_CHA_OFF)
      & FR_17_ERAY_WRHS1_CHANNEL_MASK);

      Fr_SlotAssignmentPtr->ChannelId = Fr_17_Eray_lCheckChannelType(ChnlId);
    }
    else
    {
      /* [cover parentID={7FF99747-17C0-4854-923B-C5887C864827}]
      Update current SlotID, ChannelID and Cycle count in Fr_SlotAssignmentPtr
      using Fr_17_Eray_ConfigPtr
      [/cover] */
      /*Update LPdu configured cycle count to Fr_SlotAssignmentPtr*/
      Fr_SlotAssignmentPtr->Cycle = (uint8)((Fr_17_Eray_ConfigPtr->
      CfgPtr[LogIdx].LPduConfigPtr[Fr_LPduIdx].Wrhs1CfgVal >>
      IFX_ERAY_WRHS1_CYC_OFF) & IFX_ERAY_WRHS1_CYC_MSK);

      /*Update LPdu configured Slot ID to Fr_SlotAssignmentPtr*/
      Fr_SlotAssignmentPtr->SlotId = (uint16)((Fr_17_Eray_ConfigPtr->
      CfgPtr[LogIdx].LPduConfigPtr[Fr_LPduIdx].Wrhs1CfgVal)
      & IFX_ERAY_WRHS1_FID_MSK);

      /*Update LPdu configured Channel ID to Fr_SlotAssignmentPtr*/
      ChnlId = ((Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx]
      .LPduConfigPtr[Fr_LPduIdx].Wrhs1CfgVal >> IFX_ERAY_WRHS1_CHA_OFF)
      & FR_17_ERAY_WRHS1_CHANNEL_MASK);

      Fr_SlotAssignmentPtr->ChannelId = Fr_17_Eray_lCheckChannelType(ChnlId);
    }
  }
  #else
    UNUSED_PARAMETER(Fr_SlotAssignmentPtr);
  #endif
  return RetValue ;

}
#elif (MCAL_AR_VERSION == MCAL_AR_422)
/*******************************************************************************
** Traceability    : [cover parentID={A89C2719-0EA5-47bf-BAC6-48FD23A2C94F}]  **
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
Std_ReturnType Fr_17_Eray_TransmitTxLPdu(
                                           const uint8 Fr_CtrlIdx,
                                           const uint16 Fr_LPduIdx,
                                           const uint8 * const Fr_LSduPtr,
                                           const uint8 Fr_LSduLength
                                         )
{
  Std_ReturnType RetValue;

  RetValue = Fr_17_Eray_lTransmitTxLPdu(Fr_CtrlIdx, Fr_LPduIdx,
                                                  Fr_LSduPtr, Fr_LSduLength);

  return RetValue ;
}
#endif
/*******************************************************************************
** Traceability    : [cover parentID={E6595800-57BB-4dd3-93E4-3726F7B12389}]  **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_CancelTxLPdu(                  **
**                                    const uint8 Fr_CtrlIdx,                 **
**                                    const uint16 Fr_LPduIdx,                **
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
Std_ReturnType Fr_17_Eray_CancelTxLPdu(const uint8 Fr_CtrlIdx,
                                       const uint16 Fr_LPduIdx)
{
  uint32 NdatRegId;
  uint32 NdatRegMsgBuffIdPos;
  Std_ReturnType RetValue;
  uint32 ErrCount;
  uint32 MsgBuffIdx;
  uint8 LogIdx;

  /* [cover parentID={51F5AA90-6885-45d8-9F57-17751E759474}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_OFF)
  RetValue = E_OK;
  #else
  RetValue = Fr_17_Eray_lCancelTxLPduDetCheck(Fr_CtrlIdx, Fr_LPduIdx);

  /* [cover parentID={63B6AF58-CB53-4858-B1C9-2C23B2EC3760}]
  Any DET error occurred ?
  [/cover] */
  if(RetValue == E_OK)
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_OFF) */
  {
    LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];

    /* [cover parentID={D3628F64-4436-467f-8C2C-EDFEE806A28F}]
    Get the message buffer number allocated to the LPdu Index
    [/cover] */
    /* Figure out the message buffer corresponding to LPduIdx */
    MsgBuffIdx =
       Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].LPduIdx2MsgBuffIdxPtr[Fr_LPduIdx];

    /* Does current message buffer configuration correspond to LPduIdx? */
    /* [cover parentID={0D54D5F1-4A2A-4088-A676-B5DF04C1DD0A}]
    Does the message buffer configuration correspond to LPdu Index?
    [/cover] */
    if (Fr_17_Eray_MsgBuff2LPduIdxPtr[Fr_CtrlIdx][MsgBuffIdx] == Fr_LPduIdx)
    {
      /* Figure out the TXRQ register corresponding to MsgBuffIdx */
      NdatRegId = (uint32)MsgBuffIdx >> FR_17_ERAY_MSG_BUFF_ID_SHIFT;

      /* Figure out the bit, corresponding to MsgBuffIdx, in TXRQ register */
      /* Note: ANDing with 0x1F ==> MOD operation */
      NdatRegMsgBuffIdPos = (uint32)MsgBuffIdx & FR_17_ERAY_MSG_BUFF_ID_MASK;

      /* Check if transmission is pending */
      /* [cover parentID={ED230BB2-5A9E-43fb-A120-863025C319C1}]
      Is the message buffer pending for transmission ?
      [/cover] */
      if (((&ERAY[Fr_CtrlIdx]->TXRQ1)[NdatRegId].U &
          ((uint32)1 << NdatRegMsgBuffIdPos)) != (uint32)0U)
      {
        /* [cover parentID={B413519D-2501-42ae-971E-DD75890345F4}]
        Update the Write header Section 1, 2 and 3 so that the pending
        bits are cleared and Transmission request is terminated.
        [/cover] */
        /* Updated header so that pending bit clears and TX does not happen */
        ERAY[Fr_CtrlIdx]->WRHS1.U =
        (Fr_17_Eray_ConfigPtr->
        CfgPtr[LogIdx].LPduConfigPtr)[Fr_LPduIdx].Wrhs1CfgVal;

        ERAY[Fr_CtrlIdx]->WRHS2.U =
        (Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].LPduConfigPtr)[
                       Fr_LPduIdx].Wrhs2CfgVal & (uint32)FR_17_ERAY_WRHS2_MASK;

        ERAY[Fr_CtrlIdx]->WRHS3.U =
        Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].DataPointerOffsetPtr[MsgBuffIdx];

        /* [cover parentID={AC670DDC-0C37-4826-9DDC-4C3E3082FE4D}]
        Select header section for writing into message buffer and start the
        transfer from input buffer to message RAM
        [/cover] */
        /* Select header section for writing into message buffer */
        ERAY[Fr_CtrlIdx]->IBCM.U = FR_17_ERAY_TRANSFER_HEADER;

        /* Start the buffer transfer */
        ERAY[Fr_CtrlIdx]->IBCR.B.IBRH = (uint8)MsgBuffIdx;

        /*  Check if input buffer is busy with another transfer
           a. Wait until it becomes free or a time out happens
           b. If time out happens, report Production Error to Mcal_Wrapper */
        ErrCount = Fr_17_Eray_lInputBufBsyHost(Fr_CtrlIdx);

        /* [cover parentID={C2B06B15-2949-41de-B6A1-A2D22D777232}]
        Is the input buffer host in busy state within timeout period ?
        [/cover] */
        if(ErrCount == (uint32)0U)
        {
          /* [cover parentID={F076AB09-D95B-4586-9CBC-0CFE81A390E4}]
          Mark the return value as successfully finished
          [/cover] */
          RetValue = E_OK;
        }
      }
      else
      {
        /* No transmission is pending, No such cancellation took place.
        return E_NOT_OK */
        RetValue = E_NOT_OK;
      }
    }
    else
    {
      /* [cover parentID={97E7A57E-17C5-4b50-99E6-B0B07F5C9DE8}]
      Mark the return value as Error Detected
      [/cover] */
      /* Current message buffer configuration does not correspond to
         LPduIdx */
      RetValue = E_NOT_OK;
    }
  }

  return RetValue;

}

#if(MCAL_AR_VERSION == MCAL_AR_440)
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
Std_ReturnType  Fr_17_Eray_ReceiveRxLPdu
(
    const uint8 Fr_CtrlIdx,
    const uint16 Fr_LPduIdx,
    uint8 * const Fr_LSduPtr,
    Fr_RxLPduStatusType * const Fr_RxLPduStatusPtr,
    uint8 * const Fr_LSduLengthPtr,
    Fr_SlotAssignmentType * const Fr_SlotAssignmentPtr)
{
  Std_ReturnType RetValue;
  /* Receive data from the network */
  RetValue = Fr_17_Eray_lReceiveRxLPdu(Fr_CtrlIdx, Fr_LPduIdx, Fr_LSduPtr,
                                        Fr_RxLPduStatusPtr, Fr_LSduLengthPtr);
  /* [cover parentID={46075E5A-2DC5-42b0-B530-1CA3EBDD094D}]
  Extended LPdu reporting is Enabled
  [/cover] */
  #if(FR_17_ERAY_EXTENDED_LPDU_REPORTING == STD_ON)
  /* [cover parentID={8F253439-6A52-41e0-BBF1-15FE692FAC50}]
  Is Frame receive API executed successfully and is Fr_SlotAssignmentPtr
  is not NULL
  [/cover] */
  if((RetValue == E_OK) && (Fr_SlotAssignmentPtr != NULL_PTR))
  {
    /* [cover parentID={8C224342-523D-48d6-833F-80A43500ABE2}]
    Update current SlotID, ChannelID and Cycle count in Fr_SlotAssignmentPtr
    [/cover] */
    RetValue = Fr_17_Eray_lExtendedLPduReporting(Fr_CtrlIdx, Fr_LPduIdx,
                                                  Fr_SlotAssignmentPtr);
  }
  #else
    UNUSED_PARAMETER(Fr_SlotAssignmentPtr);
  #endif
  return RetValue ;
}
#elif (MCAL_AR_VERSION == MCAL_AR_422)
/*******************************************************************************
** Traceability    : [cover parentID={6445F7A5-9653-436e-A28C-DCDA58243A1F}]  **
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
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
Std_ReturnType Fr_17_Eray_ReceiveRxLPdu(
                                  const uint8 Fr_CtrlIdx,
                                  const uint16 Fr_LPduIdx,
                                  uint8 * const Fr_LSduPtr,
                                  Fr_RxLPduStatusType *const Fr_RxLPduStatusPtr,
                                  uint8 * const Fr_LSduLengthPtr
                                        )
{
  Std_ReturnType RetValue;
  /* Receive data from the network */
  RetValue = Fr_17_Eray_lReceiveRxLPdu(Fr_CtrlIdx, Fr_LPduIdx, Fr_LSduPtr,
                                        Fr_RxLPduStatusPtr, Fr_LSduLengthPtr);

  return RetValue ;
}
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
Std_ReturnType  Fr_17_Eray_CheckTxLPduStatus(
                            const uint8 Fr_CtrlIdx,
                            const uint16 Fr_LPduIdx,
                            Fr_TxLPduStatusType * const Fr_TxLPduStatusPtr,
                            Fr_SlotAssignmentType * const Fr_SlotAssignmentPtr
                            )
{
  Std_ReturnType RetValue;

  RetValue = Fr_17_Eray_lCheckTxLPduStatus(Fr_CtrlIdx, Fr_LPduIdx,
                                                   Fr_TxLPduStatusPtr);

  /* [cover parentID={26BF453B-AEE5-42dc-8BB1-43FB3F84EF11}]
  Extended LPdu reporting is enabled
  [/cover] */
  #if(FR_17_ERAY_EXTENDED_LPDU_REPORTING == STD_ON)
  /* [cover parentID={A4E5F07E-C914-4d10-877A-CD3AE38B0DA9}]
  Is check Transmit TX LPdu function executed succesfully
  [/cover] */
  if((RetValue == E_OK) && (Fr_SlotAssignmentPtr != NULL_PTR))
  {
    /* [cover parentID={01E27573-1393-48a8-A261-DDEABFE4D5D2}]
    Update current slotID, ChannelID and Cycle count in Fr_SlotAssignmentPtr
    [/cover] */
    RetValue = Fr_17_Eray_lExtendedLPduReporting(Fr_CtrlIdx, Fr_LPduIdx,
                                                  Fr_SlotAssignmentPtr);
  }
  #else
  UNUSED_PARAMETER(Fr_SlotAssignmentPtr);
  #endif

  return RetValue;
}
#elif (MCAL_AR_VERSION == MCAL_AR_422)
/*******************************************************************************
** Traceability    : [cover parentID={F2A68EBA-FBB4-471f-BB6D-083101E55DBA}]  **
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
** Parameters (out): Fr_TxLPduStatusPtr - This reference is used to store the **
**                                        transmit status of the LPdu         **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
Std_ReturnType Fr_17_Eray_CheckTxLPduStatus(
                                 const uint8 Fr_CtrlIdx,
                                 const uint16 Fr_LPduIdx,
                                 Fr_TxLPduStatusType * const Fr_TxLPduStatusPtr
                                     )
{
  Std_ReturnType RetValue;

  RetValue = Fr_17_Eray_lCheckTxLPduStatus(Fr_CtrlIdx, Fr_LPduIdx,
                                                   Fr_TxLPduStatusPtr);
  return RetValue;
}
#endif


#if(FR_17_ERAY_PREPARE_LPDU == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID={CB82A6F8-F66A-420e-AC33-9ACACF337648}]  **
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
Std_ReturnType Fr_17_Eray_PrepareLPdu(
                                     const uint8 Fr_CtrlIdx,
                                     const uint16 Fr_LPduIdx
                                     )
{
  uint32 MsgBuffIdx;
  Std_ReturnType RetValue;
  volatile uint8 IbsyhZero;
  uint32 ErrCount;
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */
  uint8 LogIdx;

  RetValue = E_OK;

  /* [cover parentID={6BEDAF12-5927-49be-9EBD-DF8F23568A98}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={801E4B67-FD7E-4803-B446-F91FEE0ACCE4}]
  Check for Fr Initialization
  [/cover] */
  /* FR_17_ERAY_E_INIT_FAILED */
  DevError = Fr_17_Eray_lDetCheckNoInit(FR_17_ERAY_SID_PREPARELPDU);

  /* [cover parentID={7DAF03B2-54F5-4f73-947B-A32D8618B721}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={A7E49F49-E0B2-4e9b-BE50-6D59897CF073}]
    Check for validity of controller Index
    [/cover] */
    /* FR_17_ERAY_E_INV_CTRL_IDX */
    DevError = Fr_17_Eray_lDetCheckInvCtrlIdx(Fr_CtrlIdx,
                                                 FR_17_ERAY_SID_PREPARELPDU);
  }

  /* [cover parentID={102D57C9-2961-487b-819A-ECBA56786D01}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={C906DA72-7E43-48a6-955C-B3C22FBBDC5F}]
    Check the validity of the LPdu index
    [/cover] */
    /* FR_17_ERAY_E_INV_LPDU_IDX: LPduIdx >= LPDU count  */
    DevError = Fr_17_Eray_lDetCheckInvLPduIdx(Fr_CtrlIdx,Fr_LPduIdx,
                                                  FR_17_ERAY_SID_PREPARELPDU);
  }

  /* Return if a development error detected */
  /* [cover parentID={C3B331DA-61AE-4ed3-9A47-408E59492189}]
  Any DET Error detected from the previous checks ?
  [/cover] */
  if (DevError != FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={64BF78CC-68C2-4a12-9C83-F3BC0EC38CDD}]
    Mark the return value as Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  /* [cover parentID={26FCBEEF-7CB9-457e-BFA5-A9404B376358}]
  Any DET error occurred ?
  [/cover] */
  if(RetValue == E_OK)
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */
  {
    LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];

    /* [cover parentID={4D4409D9-C256-4178-8588-4A79A8678B6F}]
    Get the message buffer number allocated to the LPdu Index
    [/cover] */
    /* Figure out the message buffer corresponding to LPduIdx */
    MsgBuffIdx = Fr_17_Eray_ConfigPtr->
                    CfgPtr[LogIdx].LPduIdx2MsgBuffIdxPtr[Fr_LPduIdx];

    /* Is the message buffer MsgBuffIdx already configured for LPduIdx?
       Only for Buffer reconfigurable LPDUs the if condition PASS */
    /* [cover parentID={4BA46466-5427-4ba7-8865-6559B8060E75}]
    Is the message buffer already configured for the LPdu index ?
    [/cover] */
    if ((MsgBuffIdx != (uint32)FR_17_ERAY_MSGBUFF_UNUSED) &&
        (Fr_17_Eray_MsgBuff2LPduIdxPtr[Fr_CtrlIdx][MsgBuffIdx] != Fr_LPduIdx))
    {
      /* Reconfigure MsgBuffIdx for Fr_LPduIdx */

      /* [cover parentID={87EAA694-B71A-4ef6-B483-818D8D41FC9D}]
      Is host side input buffer free?
      [/cover] */
      /* Is host side input buffer free? */
      IbsyhZero = ERAY[Fr_CtrlIdx]->IBCR.B.IBSYH;
      if (IbsyhZero == (uint8)0U)
      {
        /* [cover parentID={2DF708D6-A624-456e-ADEB-0F9FB375AFD8}]
        Update the message buffer to LPdu mapping data
        [/cover] */
        /* Update the message buffer to LPDU mapping */
        Fr_17_Eray_MsgBuff2LPduIdxPtr[Fr_CtrlIdx][MsgBuffIdx] =
                                                           (uint8)Fr_LPduIdx;

        /* [cover parentID={03CB5A6E-8A86-40dd-8B40-2EA1199C3E9B}]
        Update the Write header section 1, 2 and 3 with the configured
        information corresponding to LPdu index
        [/cover] */
        /* Write into header section values into input buffer */
        ERAY[Fr_CtrlIdx]->WRHS1.U =
        (Fr_17_Eray_ConfigPtr->
                      CfgPtr[LogIdx].LPduConfigPtr)[Fr_LPduIdx].Wrhs1CfgVal;

        ERAY[Fr_CtrlIdx]->WRHS2.U =
            (Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].LPduConfigPtr)[
                       Fr_LPduIdx].Wrhs2CfgVal & (uint32)FR_17_ERAY_WRHS2_MASK;

        ERAY[Fr_CtrlIdx]->WRHS3.U =
            Fr_17_Eray_ConfigPtr->
                       CfgPtr[LogIdx].DataPointerOffsetPtr[MsgBuffIdx];

        /* [cover parentID={0F1E9127-5111-4032-8B77-05077AB74DD5}]
        Select header section for writing into message buffer and start
        the transfer from input buffer to message RAM
        [/cover] */
        /* Select header section for writing into message buffer */
        ERAY[Fr_CtrlIdx]->IBCM.U = FR_17_ERAY_TRANSFER_HEADER;

        /* Start the buffer transfer */
        ERAY[Fr_CtrlIdx]->IBCR.B.IBRH = (uint8)MsgBuffIdx;

        /*  Check if input buffer is busy with another transfer
           a. Wait until it becomes free or a time out happens
           b. If time out happens, report Production Error to Mcal_Wrapper  */
        ErrCount = Fr_17_Eray_lInputBufBsyHost(Fr_CtrlIdx);

        /* [cover parentID={C27E9C36-66C9-4c89-B5C3-B3C9866206A5}]
        Is the input buffer host in busy state within timeout period ?
        [/cover] */
        if(ErrCount != (uint32)0U)
        {
          /* [cover parentID={E60253D1-1AE8-406a-AA52-4D8C9BACE4A3}]
          Mark the return value as successfully finished
          [/cover] */
          RetValue = E_NOT_OK;
        }
      }
      else
      {
        /* [cover parentID={F212E838-5378-4059-A5A6-3CC1EC3F01B4}]
        Mark the return value as Error Detected
        [/cover] */
        /* Host side input buffer is NOT free */
        RetValue = E_NOT_OK;
      }
    }
  }
  return RetValue;
}
#endif /* (FR_17_ERAY_PREPARE_LPDU == STD_ON) */

#if (FR_17_ERAY_RECONFIG_LPDU == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID={73C55078-37F0-4708-9CA6-BCCDE96A46B5}]  **
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
         (FrameId, Channel, CycleRepetition, CycleOffset, PayloadLength,      **
         HeaderCRC) at runtime.                                               **
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
Std_ReturnType Fr_17_Eray_ReconfigLPdu(
    const uint8 Fr_CtrlIdx,
    const uint16 Fr_LPduIdx,
    const uint16 Fr_FrameId,
    const Fr_ChannelType Fr_ChnlIdx,
    const uint8 Fr_CycleRepetition,
    const uint8 Fr_CycleOffset,
    const uint8 Fr_PayloadLength,
    const uint16 Fr_HeaderCRC
)
{
  uint32 ErrorCount;
  uint32 MsgBuffIdx;
  Std_ReturnType RetValue;
  const Fr_17_Eray_LPduConfigType *LPduCfgPtr;
  uint8 PayloadLength;
  /* MISRA2012_RULE_19_2_JUSTIFICATION:Union is used to access the register
    contents directly without shift and OR operation. */
  Ifx_ERAY_WRHS1 Wrhs1;
  /* MISRA2012_RULE_19_2_JUSTIFICATION:Union is used to access the register
  contents directly without shift and OR operation. */
  Ifx_ERAY_WRHS2 Wrhs2;
  uint8 LogIdx;
  volatile uint8 IbsyhZero;

  /* [cover parentID={7115FF52-0D9D-44d3-A3B6-9D0D39140D4E}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)

  /*[cover parentID={45601B61-9409-4a35-A8A5-47E7045CD873}]
  Check for DET errors
  [/cover] */
  /* [cover parentID={82C76265-ED78-45ff-A4AA-1B5DCEDF6463}]
  Perform DET check for Init and Ctrl,LPdu, channel indices
  [/cover] */
  RetValue = Fr_17_Eray_lRecfgDetChkLpduParam(Fr_CtrlIdx, Fr_LPduIdx,
                                                          Fr_ChnlIdx);

  /* [cover parentID={8009B6DF-57BC-44b2-A1CD-6FD9D2B6EE8A}]
  Any DET error detected ?
  [/cover] */
  if (RetValue == E_OK)
  {
    /* [cover parentID={B899DB07-EBBA-4b3d-8AB2-D2F186243207}]
    Perform DET check for cycle repetition and offset
    [/cover] */
    RetValue = Fr_17_Eray_lRecfgDetChkCycleVal(Fr_CycleRepetition,
                                                 Fr_CycleOffset);

    /* [cover parentID={72F4D614-7F4C-40ff-99BC-32E59DF131A2}]
    Any DET error detected ?
    [/cover] */
    if (RetValue == E_OK)
    {
      /* [cover parentID={A170BD8B-A298-4d7d-8A9A-EB2A57403737}]
      Perform DET check for payload length and header CRC
      [/cover] */
      RetValue = Fr_17_Eray_lRecfgDetChkHeaderPL(Fr_CtrlIdx, Fr_LPduIdx,
                                          Fr_PayloadLength, Fr_HeaderCRC);
    }
  }

  /* [cover parentID={0D1B1ADF-7B1B-425c-88DB-3906D8B85512}]
  Any DET Error occurred ?
  [/cover] */
  if(RetValue == E_OK)
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */
  {
    LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];

    /* [cover parentID={96DF063C-1BF4-4296-91EE-08C8F23CE702}]
    Get the message buffer index that corresponds to the LPdu Index
    [/cover] */
    /* Figure out the message buffer corresponding to LPduIdx */
    MsgBuffIdx = Fr_17_Eray_ConfigPtr->
                           CfgPtr[LogIdx].LPduIdx2MsgBuffIdxPtr[Fr_LPduIdx];

    /* Is the message buffer MsgBuffIdx already configured for LPduIdx? */

    LPduCfgPtr = Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].LPduConfigPtr;

    /* Check if Lpdu is dynamically reconfigurable */
    /* [cover parentID={570288CD-CF3B-438d-8AD8-7CF8B1046C1F}]
    Is the LPdu 'Reconfigurable' ?
    [/cover] */
    if (LPduCfgPtr[Fr_LPduIdx].LpduReconfigurable ==
                                      (uint8)FR_17_ERAY_LPDU_RECONFIGURABLE)
    {
      /* [cover parentID={303A8291-788B-4a38-A9CE-2D554AA4C185}]
      Is the input host buffer in Busy state ?
      [/cover] */
      /* Is host side input buffer free? */
      IbsyhZero = ERAY[Fr_CtrlIdx]->IBCR.B.IBSYH;
      if (IbsyhZero == (uint8)0U)
      {
        /*Write from config for values that are not available for
        reconfiguring*/

        Wrhs1.U = LPduCfgPtr[Fr_LPduIdx].Wrhs1CfgVal;
        /* Write into header section values into input buffer */
        Wrhs1.B.FID = Fr_FrameId;
        /* CycleCode = CycleRepetition | BaseCycle */
        Wrhs1.B.CYC = (Fr_CycleRepetition + Fr_CycleOffset);

        /* Configure Channel Index, additional 0x1 as per WRHS1 bits */
        if (Fr_ChnlIdx == FR_CHANNEL_A)
        {
          Wrhs1.B.CHA = FR_17_ERAY_DEC_ONE;
          Wrhs1.B.CHB = FR_17_ERAY_DEC_ZERO;
        }
        else if (Fr_ChnlIdx == FR_CHANNEL_B)
        {
          Wrhs1.B.CHA = FR_17_ERAY_DEC_ZERO;
          Wrhs1.B.CHB = FR_17_ERAY_DEC_ONE;
        }
        else
        {
          Wrhs1.B.CHA = FR_17_ERAY_DEC_ONE;
          Wrhs1.B.CHB = FR_17_ERAY_DEC_ONE;
        }

        /* [cover parentID={24EE69B4-9D97-481f-B4F9-FAD5DCA8E802}]
        Update the Write header section 1 with the parameters Frame Id,
        Cycle Repetition, Cycle Offset and Channel Index
        [/cover] */
        ERAY[Fr_CtrlIdx]->WRHS1.U = Wrhs1.U;

        /* If payload length is odd, Fr_PayloadLength must be rounded to next
           higher even number */
        /* [cover parentID={6DDC6663-1138-4a17-BF3C-EF0F07F59CF2}]
        Is the Payload Length parameter an Odd value ?
        [/cover] */
        if ((Fr_PayloadLength & FR_17_ERAY_DEC_ONE) == FR_17_ERAY_DEC_ONE)
        {
          /* [cover parentID={68EC9233-259E-40bc-BD26-DCA428E5B6B3}]
          Copy the payload length value and increment by 1
          [/cover] */
          PayloadLength = (Fr_PayloadLength + (uint8)1U);
        }
        else
        {
          PayloadLength = Fr_PayloadLength;
        }

        /* Configure payload length in terms of 2 byte word */
        Wrhs2.B.PLC = (PayloadLength >> 1U);

        /*Configure Header CRC*/
        Wrhs2.B.CRC = Fr_HeaderCRC;

        /* [cover parentID={9F1E9071-0663-435a-B1FE-2201E0D0DB13}]
        Update the Write header section 2 with the payload length value
        and the header CRC parameter
        [/cover] */
        ERAY[Fr_CtrlIdx]->WRHS2.U = Wrhs2.U;

        ERAY[Fr_CtrlIdx]->WRHS3.U =
        Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].DataPointerOffsetPtr[MsgBuffIdx];

        /* Select header section for writing into message buffer */
        ERAY[Fr_CtrlIdx]->IBCM.U = FR_17_ERAY_TRANSFER_HEADER;

        /* Start the buffer transfer */
        ERAY[Fr_CtrlIdx]->IBCR.B.IBRH = (uint8)MsgBuffIdx;

        /*  Check if input buffer is busy with another transfer
           a. Wait until it becomes free or a time out happens
           b. If time out happens, report Production Error to Mcal_Wrapper  */
        ErrorCount = Fr_17_Eray_lInputBufBsyHost(Fr_CtrlIdx);

        /* [cover parentID={F22B2E63-A847-4ac0-9218-7707C92A69E7}]
        Is the input host buffer in busy state within timeout period ?
        [/cover] */
        if (ErrorCount != (uint32)0U)
        {
          /* Command not accepted or POC state change did not happen -->
          Time out--> Production error */
          RetValue = E_NOT_OK;
        }
        else
        {
          /* [cover parentID={B8E2A646-EEFA-4f37-906F-0DD3C63380A7}]
          Mark the return value as successfully finished
          [/cover] */
          RetValue = E_OK;
        }

        /* Update the message buffer to LPDU mapping */
        Fr_17_Eray_MsgBuff2LPduIdxPtr[Fr_CtrlIdx][MsgBuffIdx] =
                                                         (uint8)Fr_LPduIdx;
      }
      else
      {
        /* Host side input buffer is NOT free */
        RetValue = E_NOT_OK;
      }
    }
    else
    {
      /* [cover parentID={32972B0A-8780-4547-9A3F-F19A75C6A5BC}]
      Mark the return value as Error Detected
      [/cover] */
      /* LPDU is not reconfigurable */
      RetValue = E_NOT_OK;
    }
  }

  return RetValue;

}
#endif /* (FR_17_ERAY_RECONFIG_LPDU == STD_ON) */

#if (FR_17_ERAY_DISABLE_LPDU == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID={5184712D-F85A-4502-94AE-3658AD227B5F}]  **
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
Std_ReturnType Fr_17_Eray_DisableLPdu(
                                 const uint8 Fr_CtrlIdx,
                                 const uint16 Fr_LPduIdx
                                     )
{
  uint32 MsgBuffIdx;
  const Fr_17_Eray_LPduConfigType *LPduCfgPtr;
  Std_ReturnType RetValue;
  uint32 ErrCount;
  uint8 LogIdx;
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */

  RetValue = E_OK;

  /* [cover parentID={15AE6200-0441-4087-ACFC-44678BA3D43A}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={FB2CA9B2-F5C2-4b0f-9187-3033A14E66BF}]
  Check for Fr Initialization
  [/cover] */
  /* FR_17_ERAY_E_INIT_FAILED */
  DevError = Fr_17_Eray_lDetCheckNoInit(FR_17_ERAY_SID_DISABLELPDU);

  /* [cover parentID={A6C47E4A-FD97-4cb2-BFE0-8BF15634CED2}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={DB468CF0-0BF5-4330-9A8A-B68DDB4B0AF0}]
    Check for validity of controller Index
    [/cover] */
    /* FR_17_ERAY_E_INV_CTRL_IDX */
    DevError = Fr_17_Eray_lDetCheckInvCtrlIdx(Fr_CtrlIdx,
                                                   FR_17_ERAY_SID_DISABLELPDU);
  }

  /* [cover parentID={393FBF7D-A720-4c32-9104-7E47F6125B11}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={AF9226D2-7A25-4560-AAC1-CA66473C11E8}]
    Check the validity of the LPdu index
    [/cover] */
    /* FR_17_ERAY_E_INV_LPDU_IDX: LPduIdx >= LPDU count  */
    DevError = Fr_17_Eray_lDetCheckInvLPduIdx(Fr_CtrlIdx,Fr_LPduIdx,
                                                  FR_17_ERAY_SID_DISABLELPDU);
  }

  /* [cover parentID={E86B20F7-505B-4fa1-B4D7-4289E47CB54F}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];

    /* [cover parentID={73509707-73C1-4d9f-BB78-FE30A8BA6AC3}]
    Is the LPdu Not Reconfigurable ?
    [/cover] */
    if (Fr_17_Eray_ConfigPtr->
      CfgPtr[LogIdx].LPduConfigPtr[Fr_LPduIdx].LpduReconfigurable !=
                                         (uint8)FR_17_ERAY_LPDU_RECONFIGURABLE)
    {
      /* [cover parentID={9BE73DA7-EA83-4050-96E6-7F7BEA899CAA}]
      Report DET
      [/cover] */
      (void)Det_ReportError(FR_17_ERAY_MODULE_ID, FR_17_ERAY_INSTANCE_ID,
                   FR_17_ERAY_SID_DISABLELPDU, FR_17_ERAY_E_INV_LPDU_IDX);
      DevError = FR_17_ERAY_E_INV_LPDU_IDX;
    }
  }

  /* [cover parentID={0ECE5CD7-45FF-42a0-8AE8-F848F8F3F6B9}]
  Any DET Error detected from the previous checks ?
  [/cover] */
  /* Return if a development error detected */
  if (DevError != FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={D3A50BD8-1664-4421-BC65-EA0EC71369F9}]
    Mark the return value as Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  /* [cover parentID={2E899AB4-A6BF-4152-9D11-51B147B8AF3C}]
  Any DET error occurred ?
  [/cover] */
  if(RetValue == E_OK)
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */
  {
    LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];

    /* [cover parentID={0F5ED88C-F565-4ba6-8A66-239260EEE560}]
    Get the message buffer number corresponding to the LPdu Index
    [/cover] */
    /* Figure out the message buffer corresponding to LPduIdx */
    MsgBuffIdx = Fr_17_Eray_ConfigPtr->
                           CfgPtr[LogIdx].LPduIdx2MsgBuffIdxPtr[Fr_LPduIdx];

    /* Check if Lpdu is dynamically reconfigurable */

    LPduCfgPtr = Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].LPduConfigPtr;

    /* [cover parentID={863B054A-9F3A-4d8a-A561-FF86FDB94593}]
    Is the LPdu configured as Reconfigurable ?
    [/cover] */
    if (LPduCfgPtr[Fr_LPduIdx].LpduReconfigurable ==
                                   (uint8)FR_17_ERAY_LPDU_RECONFIGURABLE)
    {
      /* Set Channel Filter Control A and Channel Filter Control B bits to
      zero,to stop transmission and receive buffer will ignore frames.*/
      /* [cover parentID={22630B0B-0248-42e2-96C1-9B911979EED1}]
      Within the Write header Section 1, set Channel Filter Control A and
      Channel Filter Control B bits to zero (This stops transmission and
      receive buffer will ignore frames)
      [/cover] */
      ERAY[Fr_CtrlIdx]->WRHS1.B.CHA = FR_17_ERAY_DEC_ZERO;
      ERAY[Fr_CtrlIdx]->WRHS1.B.CHB = FR_17_ERAY_DEC_ZERO;

      /* [cover parentID={305360B3-11AD-4304-B477-C89F856E4CF3}]
      Select header section for writing into message buffer and start
      the transfer from input buffer to message RAM
      [/cover] */
      /* Select header section for writing into message buffer */
      ERAY[Fr_CtrlIdx]->IBCM.U = FR_17_ERAY_TRANSFER_HEADER;

      /* Start the buffer transfer */
      ERAY[Fr_CtrlIdx]->IBCR.B.IBRH = (uint8)MsgBuffIdx;

      /*  Check if input buffer is busy with another transfer
         a. Wait until it becomes free or a time out happens
         b. If time out happens, report Production Error to Mcal_Wrapper */
      ErrCount = Fr_17_Eray_lInputBufBsyHost(Fr_CtrlIdx);

      /* [cover parentID={C794D377-9412-4914-9366-1EEC2C2649C9}]
      Is the input buffer host in busy state within timeout period ?
      [/cover] */
      if(ErrCount != (uint32)0U)
      {
        /* [cover parentID={1B8CB456-9A1B-4326-B7CD-E3AF21629358}]
        Mark the return value as successfully finished
        [/cover] */
        RetValue = E_NOT_OK;
      }
    }
    else
    {
      /* [cover parentID={916F9D83-F22B-48f0-BAE7-9FB2423E7925}]
      Mark the return value as Error Detected
      [/cover] */
      RetValue = E_NOT_OK;
    }
  }

  return RetValue;

}
#endif /* (FR_17_ERAY_DISABLE_LPDU == STD_ON) */

/*******************************************************************************
** Traceability    : [cover parentID={9CED9736-D893-427e-A06A-4FBE5273ED4F}]  **
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
Std_ReturnType Fr_17_Eray_GetGlobalTime(
                                         const uint8 Fr_CtrlIdx,
                                         uint8* const Fr_CyclePtr,
                                         uint16* const Fr_MacroTickPtr
                                       )
{
  Std_ReturnType RetValue;
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */
  uint32 RegMTCCV;

  /* [cover parentID={72608589-A998-445b-B416-1346625BDB99}]
  Mark the return value as successfully finished
  [/cover] */
  RetValue = E_OK;

  /* [cover parentID={98C1591A-DF06-4d99-9FA4-B34920212115}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  /* FR_17_ERAY_E_INIT_FAILED */
  /* [cover parentID={E0B84451-09A7-47a4-960E-619363B1B5FE}]
  Check for Fr Initialization
  [/cover] */
  DevError = Fr_17_Eray_lDetCheckNoInit(FR_17_ERAY_SID_GETGLOBALTIME);

  /* [cover parentID={632C4A8D-57A2-43a7-BE23-9A7AFB634893}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={AC02F873-F1C2-4eed-8666-44519762A0CB}]
    Check for validity of controller Index
    [/cover] */
    /* FR_17_ERAY_E_INV_CTRL_IDX */
    DevError = Fr_17_Eray_lDetCheckInvCtrlIdx(Fr_CtrlIdx,
                                                FR_17_ERAY_SID_GETGLOBALTIME);
  }

  /* [cover parentID={3BBC0B66-CCDF-47a7-AB46-E72A8739F1FE}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={ADABBDF7-BA6A-4709-BF7F-71919C09CFA1}]
    Check whether the Fr Cycle pointer is NULL
    [/cover] */
    /* FR_17_ERAY_E_PARAM_POINTER */
    DevError = Fr_17_Eray_lDetCheckInvPointer(Fr_CyclePtr,
                                                FR_17_ERAY_SID_GETGLOBALTIME);
  }

  /* [cover parentID={62534E52-DD38-45c0-A548-0B3F30846332}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={C7D0457C-83FB-4126-959F-E18BC910C4AF}]
    Check whether the Fr Macrotick pointer is NULL
    [/cover] */
    /* FR_17_ERAY_E_PARAM_POINTER */
    DevError = Fr_17_Eray_lDetCheckInvPointer(Fr_MacroTickPtr,
                                                FR_17_ERAY_SID_GETGLOBALTIME);
  }

  /* [cover parentID={F1FB3CFA-AD98-4b6f-B4CC-CC5A92269536}]
  Any DET Error detected from the previous checks ?
  [/cover] */
  /* Return if a development error detected */
  if (DevError != FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={65B97C7A-0808-41e3-B429-11116F6F20B3}]
    Mark the return value as Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  /* [cover parentID={F1134ACC-D6A0-48fc-8CCE-BD6B4139FA99}]
  Any DET error occurred ?
  [/cover] */
  if(RetValue == E_OK)
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */
  {
    /* [cover parentID={DA8FF1FC-D51C-4968-BB57-09A56C04EE23}]
    Is CC in synchronous with global time ?
    [/cover] */
    if (Fr_17_Eray_lIsCCInSync(Fr_CtrlIdx) == (uint32)1U)
    {
      /* [cover parentID={FA65C3C9-DA2E-4def-B3D8-02AE81A152F8}]
      Get the global FlexRay time value (Macrotick and cycle counter value)
      from the HW register and store it locally
      [/cover] */
      RegMTCCV = ERAY[Fr_CtrlIdx]->MTCCV.U;

      /* [cover parentID={8CD586C2-9CA1-40de-B58E-98489E184039}]
      Extract the Macrotick value from the locally stored global time
      and write it to the output parameter Fr_MacroTickPtr
      [/cover] */
      *Fr_MacroTickPtr = (uint16)(RegMTCCV & FR_17_ERAY_MTCCV_MTV_MASK);

      /* [cover parentID={C14EC6C2-F711-422e-8DF1-B2F875BCCE1D}]
      Extract the cycle counter value from the locally stored global time
      and write it to the output parameter Fr_CyclePtr
      [/cover] */
      *Fr_CyclePtr = (uint8)((RegMTCCV >> 16) & FR_17_ERAY_MTCCV_CCV_MASK);
    }
    else
    {
      /* [cover parentID={537C5BD6-E462-4b11-8192-13EDDDD839BD}]
      Mark the return value as Error Detected
      [/cover] */
      RetValue = E_NOT_OK;
    }
  }

  return RetValue;

}

#if (FR_17_ERAY_NMVECTOR_ENABLE == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID={F64E2607-F11F-4359-B620-AE053688BF93}]  **
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
Std_ReturnType Fr_17_Eray_GetNmVector(
                                       const uint8 Fr_CtrlIdx,
                                       uint8* const Fr_NmVectorPtr
                                     )
{
  Std_ReturnType RetValue;
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */
  uint8 ByteIndex;
  const uint8* NmvRegAddr;
  uint8 LogIdx;

  /* [cover parentID={A51401EB-662D-4df6-B84D-35B2572E95E5}]
  Mark the return value as successfully finished
  [/cover] */
  RetValue = E_OK;

  /* [cover parentID={7EA96706-F0E9-44b0-88D3-AF4DFD954660}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={524ED879-1967-4c48-AE79-ED37C7D78F78}]
  Check for Fr Initialization
  [/cover] */
  /* FR_17_ERAY_E_INIT_FAILED */
  DevError = Fr_17_Eray_lDetCheckNoInit(FR_17_ERAY_SID_GETNMVECTOR);

  /* [cover parentID={C1DCC271-F540-4dab-A0C9-B3A60D47D39F}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={BB0184B1-CAE1-4fa0-A4A2-F76FDC36FE83}]
    Check for validity of controller Index
    [/cover] */
    /* FR_17_ERAY_E_INV_CTRL_IDX */
    DevError = Fr_17_Eray_lDetCheckInvCtrlIdx(Fr_CtrlIdx,
                                                  FR_17_ERAY_SID_GETNMVECTOR);
  }

  /* [cover parentID={1F04B7CB-EE85-4b39-BBBB-39A37192BB26}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={8E9E6C23-A5EC-4c34-B782-9F11F5100F0D}]
    Check whether NM vector pointer is NULL
    [/cover] */
    /* FR_17_ERAY_E_PARAM_POINTER */
    DevError = Fr_17_Eray_lDetCheckInvPointer(Fr_NmVectorPtr,
                                                  FR_17_ERAY_SID_GETNMVECTOR);
  }

  /* Return if a development error detected */
  /* [cover parentID={01DB7BCF-F8BF-4ebb-ADB1-BED47A3FB3D8}]
  Any DET Error detected from the previous checks ?
  [/cover] */
  if (DevError != FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={828B7976-D869-496b-936C-A35E1DC17890}]
    Mark the return value as Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  /* [cover parentID={73F4DD8A-7ADE-4ef3-874E-BF1C68A52294}]
  Any DET error occurred ?
  [/cover] */
  if(RetValue == E_OK)
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */
  {
    /* [cover parentID={FA7B3AFA-01A0-4924-ACD2-315BC097869F}]
    Get the status of synchronization with global time
    [/cover] */
    /* [cover parentID={E36DA08E-EF51-4c0c-9FB1-9DF37E648F59}]
    Is CC in synchronous with global time ?
    [/cover] */
    if (Fr_17_Eray_lIsCCInSync(Fr_CtrlIdx) == (uint32)1U)
    {
      NmvRegAddr = (uint8 *)&ERAY[Fr_CtrlIdx]->NMV_1S[0];

      LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];
      /* Fill in the NM vector values into output parameter */
      /* Note: NEMC.NML = gNetworkManagementVectorLength */
      /* [cover parentID={E34CB035-28B5-4602-A9A2-C5A2FFD2C131}]
      Loop till Index is (configured NM vector Length - 1)
      [/cover] */
      for (ByteIndex = FR_17_ERAY_DEC_ZERO; ByteIndex <
           (uint8)Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].CCCfgPtr->NemcCfgVal;
           ByteIndex++)
      {
        /* [cover parentID={E9466960-479B-493e-8687-2919C16FB33F}]
        Write the accrued network management vector byte-wise to the
        output parameter Fr_NmVectorPtr
        [/cover] */
        Fr_NmVectorPtr[ByteIndex] = *NmvRegAddr;

        NmvRegAddr++;
      }
    }
    else
    {
      /* [cover parentID={86B94030-2BD6-46a6-99CB-BA3D37D8A4A2}]
      Mark the return value as Error Detected
      [/cover] */
      RetValue = E_NOT_OK;
    }
  }

  return RetValue;

}
#endif /* (FR_17_ERAY_NMVECTOR_ENABLE == STD_ON) */

/*******************************************************************************
** Traceability    : [cover parentID={08F1A2B5-A472-47e9-8B4D-DCEBCD2E2D70}]  **
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
Std_ReturnType Fr_17_Eray_GetNumOfStartupFrames(
    const uint8 Fr_CtrlIdx,
    uint8* const Fr_NumOfStartupFramesPtr
)
{
  Std_ReturnType RetValue;
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  #endif

  RetValue = E_OK;

  /* [cover parentID={889ABF36-3057-423d-AD52-3FF91E58D95D}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={AAC27064-FB79-47e7-872C-27AB0E76784B}]
  Check for Fr Initialization
  [/cover] */
  /* FR_17_ERAY_E_INIT_FAILED */
  DevError = Fr_17_Eray_lDetCheckNoInit(FR_17_ERAY_SID_GETNUMOFSTARTUPFRAMES);

  /* [cover parentID={605613A4-4E7B-4053-B456-006636DDBB90}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={88103480-2AD8-466d-A268-3F7421FCCF53}]
    Check for validity of controller Index
    [/cover] */
    /* FR_17_ERAY_E_INV_CTRL_IDX */
    DevError = Fr_17_Eray_lDetCheckInvCtrlIdx(Fr_CtrlIdx,
                                      FR_17_ERAY_SID_GETNUMOFSTARTUPFRAMES);
  }

  /* [cover parentID={DB59BAC3-A0E7-465f-95C9-4D7D5727EA2D}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={178469BE-AEAF-46dd-9C86-3DA716F3309B}]
    Check whether Fr_NumOfStartupFramesPtr is NULL
    [/cover] */
    /* FR_17_ERAY_E_PARAM_POINTER */
    DevError = Fr_17_Eray_lDetCheckInvPointer(
       Fr_NumOfStartupFramesPtr,FR_17_ERAY_SID_GETNUMOFSTARTUPFRAMES);
  }

  /* Return if a development error detected */
  /* [cover parentID={2C238058-9FA6-471a-AA5E-A82DC00A364D}]
  Any DET Error detected from the previous checks ?
  [/cover] */
  if (DevError != FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={FAAF9380-113A-414a-B114-75F4911DD850}]
    Mark the return value as Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  /* [cover parentID={550A8B76-1AAA-425e-BCC7-3E77F075F47F}]
  Any DET error occurred ?
  [/cover] */
  if(RetValue == E_OK)
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */
  {
    /* [cover parentID={21AE7414-E6C6-4325-B8EF-4DFDB7659B03}]
    Get the status of synchronization with global time
    [/cover] */
    /* [cover parentID={E0FA76BF-3F35-4e4d-A5C4-CA4DA2E6B4C7}]
    Is CC in synchronous with global time ?
    [/cover] */
    if (Fr_17_Eray_lIsCCInSync(Fr_CtrlIdx) == (uint32)1U)
    {

      /* [cover parentID={5AF949B3-E8CD-4b3e-A40F-5F60267881D5}]
      Successfully finished
      [/cover] */
      /* [cover parentID={AA0D9612-93DE-4559-8266-65A58871E4DF}]
      Write a value of 2  to the output parameter Fr_NumOfStartupFramesPtr
      [/cover] */
      *Fr_NumOfStartupFramesPtr = FR_17_ERAY_STARTUP_FRAMES;
    }
    else
    {
      /* [cover parentID={B40F2CE5-4D92-4bc9-BCEC-1AD3215860EE}]
      Mark the return value as Error Detected
      [/cover] */
      RetValue = E_NOT_OK;
    }
  }

  return RetValue;

}

/*******************************************************************************
** Traceability    : [cover parentID={3CF256A7-ECA0-45fa-A820-E2A03A6FD82D}]  **
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
Std_ReturnType Fr_17_Eray_GetChannelStatus(
    const uint8 Fr_CtrlIdx,
    uint16* const Fr_ChannelAStatusPtr,
    uint16* const Fr_ChannelBStatusPtr
)
{
  Std_ReturnType RetValue;
  uint32 AggrChaAStatusA;
  uint32 SymbWindValidMTSA;
  uint32  SymbWindErrStatusA;
  uint32  NITStatusDataA;
  uint32 AggrChaAStatusB;
  uint32 SymbWindValidMTSB;
  uint32  SymbWindErrStatusB;
  uint32  NITStatusDataB;
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  #endif

  /* [cover parentID={0882AE19-D02A-49ec-AC91-E97904871DBC}]
  Mark the return value as successfully finished
  [/cover] */
  RetValue = E_OK;

  /* [cover parentID={05036A76-9BBD-46b1-AB1A-3B0DF3531FFC}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={B3EA858F-DB88-46b9-9EED-8E054DD08F02}]
  Check for Fr Initialization
  [/cover] */
  /* FR_17_ERAY_E_INIT_FAILED */
  DevError = Fr_17_Eray_lDetCheckNoInit(FR_17_ERAY_SID_GETCHANNELSTATUS);

  /* [cover parentID={A94A5D1F-15C6-4d77-81D6-3B5138B7A2F3}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={90C23268-21A1-4ab3-81C8-E88E82827FEF}]
    Check for validity of controller Index
    [/cover] */
    /* FR_17_ERAY_E_INV_CTRL_IDX */
    DevError = Fr_17_Eray_lDetCheckInvCtrlIdx(Fr_CtrlIdx,
                                      FR_17_ERAY_SID_GETCHANNELSTATUS);
  }

  /* [cover parentID={9C8EDB95-4D21-45f8-B0B0-40133F51F276}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={317825BE-0FA7-4a49-877D-B0D53185BB45}]
    Check whether the Channel A Status pointer is NULL
    [/cover] */
    /* FR_17_ERAY_E_PARAM_POINTER */
    DevError = Fr_17_Eray_lDetCheckInvPointer(
       Fr_ChannelAStatusPtr,FR_17_ERAY_SID_GETCHANNELSTATUS);
  }

  /* [cover parentID={5FCD92AF-AEA0-4c5e-94B6-3BFB3EBC3FD6}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={4FC7E141-5AA3-4403-9D60-A8590CBC7BFF}]
    Check whether the Channel B Status pointer is NULL
    [/cover] */
    /* FR_17_ERAY_E_PARAM_POINTER */
    DevError = Fr_17_Eray_lDetCheckInvPointer(
       Fr_ChannelBStatusPtr,FR_17_ERAY_SID_GETCHANNELSTATUS);
  }

  /* [cover parentID={69CBA40B-4CD2-4a17-A331-EAC044EB681E}]
  Any DET Error detected from the previous checks ?
  [/cover] */
  /* Return if a development error detected */
  if (DevError != FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={5C91734B-B671-42c8-87A1-D7E19B1F9D8D}]
    Mark the return value as Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  /* [cover parentID={121EF511-3A08-476b-8D0E-2CD927FE7229}]
  Any DET error occurred ?
  [/cover] */
  if(RetValue == E_OK)
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */
  {
    /* [cover parentID={EC92D494-D93A-4604-9A2D-DC50C4AA36B4}]
    Is CC in synchronous with global time ?
    [/cover] */
    if (Fr_17_Eray_lIsCCInSync(Fr_CtrlIdx) == (uint32)1U)
    {
      /*Channel A aggregated channel status */
      AggrChaAStatusA = ERAY[Fr_CtrlIdx]->ACS.U & FR_17_ERAY_A_STATUS_MASK;
      /* Channel A symbol window MTS status data */
      SymbWindValidMTSA = ((ERAY[Fr_CtrlIdx]->SWNIT.U  &
                  FR_17_ERAY_A_SWNIT_VMTS_MASK) >>
                  FR_17_ERAY_A_SWNIT_VMTS_SHIFT);
      /* Channel A symbol window status data */
      SymbWindErrStatusA = (ERAY[Fr_CtrlIdx]->SWNIT.U &
                    FR_17_ERAY_A_SWNIT_STATUS_MASK);
      /* Channel A NIT status data */
      NITStatusDataA = ((ERAY[Fr_CtrlIdx]->SWNIT.U &
                FR_17_ERAY_A_NIT_STATUS_MASK)>>
                FR_17_ERAY_A_NIT_STATUS_SHIFT);

      /* [cover parentID={DBBA5BA1-B448-4ec0-9ED7-E599B9C7670E}]
      Write the aggregated channel status, NIT status, symbol window status of
      Channel A (appropriately bit-coded)  to the output parameter
      Fr_ChannelAStatusPtr
      [/cover] */
      /* write channel status data to output parameter Fr_ChannelAStatusPtr */
      *Fr_ChannelAStatusPtr = (uint16)((AggrChaAStatusA)|
      (SymbWindValidMTSA << FR_17_ERAY_SWNIT_VMTS_SHIFT)|
      (SymbWindErrStatusA << FR_17_ERAY_SWNIT_STATUS_SHIFT)|
      (NITStatusDataA << FR_17_ERAY_NIT_STATUS_SHIFT));

      /*Channel B aggregated channel status */
      AggrChaAStatusB = ((ERAY[Fr_CtrlIdx]->ACS.U &
                  FR_17_ERAY_B_STATUS_MASK) >>
                  FR_17_ERAY_B_ACS_SHIFT);
      /* Channel A symbol window MTS status data */
      SymbWindValidMTSB = ((ERAY[Fr_CtrlIdx]->SWNIT.U  &
                  FR_17_ERAY_B_SWNIT_VMTS_MASK) >>
                  FR_17_ERAY_B_SWNIT_VMTS_SHIFT);
      /* Channel A symbol window status data */
      SymbWindErrStatusB = ((ERAY[Fr_CtrlIdx]->SWNIT.U &
                  FR_17_ERAY_B_SWNIT_STATUS_MASK) >>
                  FR_17_ERAY_B_SWNIT_STATUS_SHIFT);
      /* Channel A NIT status data */
      NITStatusDataB = ((ERAY[Fr_CtrlIdx]->SWNIT.U &
                  FR_17_ERAY_B_NIT_STATUS_MASK) >>
                  FR_17_ERAY_B_NIT_STATUS_SHIFT);

      /* [cover parentID={B14FA90A-EE08-4b2d-B70F-F68171DFB351}]
      Write the aggregated channel status, NIT status, symbol window status of
      Channel B (appropriately bit-coded)  to the output parameter
      Fr_ChannelBStatusPtr
      [/cover] */
      /* write channel status data to output parameter Fr_ChannelAStatusPtr */
      *Fr_ChannelBStatusPtr = (uint16)((AggrChaAStatusB)|
      ( SymbWindValidMTSB << FR_17_ERAY_SWNIT_VMTS_SHIFT)|
      ((SymbWindErrStatusB) << FR_17_ERAY_SWNIT_STATUS_SHIFT)|
      ((NITStatusDataB) << FR_17_ERAY_NIT_STATUS_SHIFT));

      /* [cover parentID={23AFAADF-C82A-4ea4-A07D-5B80B15188A1}]
      Reset the aggregated channel status information
      [/cover] */
      /*Reset the aggregated channel status info within the FlexRay controller*/
      /* A flag is cleared by writing a 1 to the corresponding bit position.*/
      ERAY[Fr_CtrlIdx]->ACS.U = FR_17_ERAY_ACS_RESET;

    }
    else
    {
      /* [cover parentID={0E10944B-866D-4c40-A369-00CB56590C0E}]
      Mark the return value as Error Detected
      [/cover] */
      RetValue = E_NOT_OK;
    }

  }

  return RetValue;

}

/*******************************************************************************
** Traceability    : [cover parentID={16FAC518-7B66-4fcb-9083-902970FB1A2D}]  **
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
**                   Fr_OffsetCorrectionPtr - Address where the current offset**
**                             correction value shall be stored.              **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
Std_ReturnType Fr_17_Eray_GetClockCorrection(
    const uint8 Fr_CtrlIdx,
    sint16* const Fr_RateCorrectionPtr,
    sint32* const Fr_OffsetCorrectionPtr
)
{
  Std_ReturnType RetValue;
  uint16 RateCorrVal;
  uint32 OffsetCorrVal;
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  #endif

  /* [cover parentID={3DDB1076-5CBE-4f16-80E4-9322D8949D92}]
  Mark the return value as successfully finished
  [/cover] */
  RetValue = E_OK;

  /* [cover parentID={45FA538F-4497-49ce-8222-536E8CB0E897}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={5C66A711-FB6E-4edc-8B2D-B84B3A884479}]
  Check for Fr Initialization
  [/cover] */
  /* FR_17_ERAY_E_INIT_FAILED */
  DevError = Fr_17_Eray_lDetCheckNoInit(FR_17_ERAY_SID_GETCLOCKCORRECTION);

  /* [cover parentID={A3F884C6-B024-4fff-8635-F802F0EE3AB0}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={F05CF814-358D-42e6-811E-4B9879CBF4B6}]
    Check for validity of controller Index
    [/cover] */
    /* FR_17_ERAY_E_INV_CTRL_IDX */
    DevError = Fr_17_Eray_lDetCheckInvCtrlIdx(Fr_CtrlIdx,
                                      FR_17_ERAY_SID_GETCLOCKCORRECTION);
  }

  /* [cover parentID={952ADB2C-BAB4-43d6-822C-AB68169BF9F8}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={B9BEB965-D314-443b-A59C-279B4FB1F1D4}]
    Check whether the rate correction pointer is NULL
    [/cover] */
    /* FR_17_ERAY_E_PARAM_POINTER */
    DevError = Fr_17_Eray_lDetCheckInvPointer(
       Fr_RateCorrectionPtr,FR_17_ERAY_SID_GETCLOCKCORRECTION);
  }

  /* [cover parentID={B360762C-6FC2-4e0b-AE88-E00AD03274BC}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={0474228B-F55D-4632-8A78-C4DF21868B8A}]
    Check whether the offset correction pointer is NULL
    [/cover] */
    /* FR_17_ERAY_E_PARAM_POINTER */
    DevError = Fr_17_Eray_lDetCheckInvPointer(
       Fr_OffsetCorrectionPtr,FR_17_ERAY_SID_GETCLOCKCORRECTION);
  }

  /* Return if a development error detected */
  if (DevError != FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={7E98FC44-E5DF-4f69-A69C-5DD617DACB73}]
    Mark the return value as Error Detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  /* [cover parentID={0D81117B-DFBE-46a5-952D-73CCE914D9CA}]
  Any DET error occurred ?
  [/cover] */
  if(RetValue == E_OK)
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the rate correction value */
    RateCorrVal = ERAY[Fr_CtrlIdx]->RCV.B.RCV;

    /* [cover parentID={2A2FD11C-4112-4ad4-809D-33C68E02949C}]
    Check if the rate correction value is negative
    [/cover] */
    if ((RateCorrVal & FR_17_ERAY_RATECORR_SIGN_BIT) != 0U)
    {
      /* [cover parentID={1AA90E97-B94B-4bd6-A1AC-293F8CC19781}]
      Extend the sign bit for 16-bit signed representation
      [/cover] */
      RateCorrVal |= FR_17_ERAY_RATECORR_SIGN_EXT;
    }

    /* [cover parentID={8583C204-7D03-48f2-83DB-93E09E012C93}]
    Write the rate correction value to the output parameter
    Fr_RateCorrectionPtr
    [/cover] */
    *Fr_RateCorrectionPtr = (sint16)RateCorrVal;

    /* Get the offset correction value */
    OffsetCorrVal = ERAY[Fr_CtrlIdx]->OCV.B.OCV;

    /* [cover parentID={0B0F0F33-50A5-4301-ADA5-54628B6356BB}]
    Check if the offset correction value is negative
    [/cover] */
    if ((OffsetCorrVal & FR_17_ERAY_OFFSETCORR_SIGN_BIT) != 0U)
    {
      /* [cover parentID={B12AD543-DA3C-4f97-8B18-6DC415C020C6}]
      Extend the sign bit for 32-bit representation
      [/cover] */
      OffsetCorrVal |= FR_17_ERAY_OFFSETCORR_SIGN_EXT;
    }

    /* [cover parentID={514C9A2F-1A4D-43f3-9AF3-4E9600968B89}]
    Write the offset correction value to the output parameter
    Fr_OffsetCorrectionPtr
    [/cover] */
    *Fr_OffsetCorrectionPtr = (sint32)OffsetCorrVal;
  }

  return RetValue;

}

/*******************************************************************************
** Traceability    : [cover parentID={C33848F9-A84D-4cb3-85BB-23345490E781}]  **
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
Std_ReturnType Fr_17_Eray_GetSyncFrameList(
    const uint8 Fr_CtrlIdx,
    const uint8 Fr_ListSize,
    uint16* const Fr_ChannelAEvenListPtr,
    uint16* const Fr_ChannelBEvenListPtr,
    uint16* const Fr_ChannelAOddListPtr,
    uint16* const Fr_ChannelBOddListPtr
)
{
  Std_ReturnType RetValue;
  uint8 Index;

  /* [cover parentID={9A0F7B27-27C6-4abe-9DDA-20FE435F4679}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  RetValue = Fr_17_Eray_lGetSyncFrameList(Fr_CtrlIdx, Fr_ListSize,
                  Fr_ChannelAEvenListPtr, Fr_ChannelBEvenListPtr,
                  Fr_ChannelAOddListPtr, Fr_ChannelBOddListPtr);

  /* [cover parentID={B8C79ACA-18F7-4b56-A041-6D20B35C1E64}]
  Any DET error occurred ?
  [/cover] */
  if(RetValue == E_OK)
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */
  {
    /* [cover parentID={29865CF6-4566-4c97-84F2-52725916D0DC}]
    Initialize the Channel list array elements to Zero
    [/cover] */
    /* Initialize all 4 array values to 0 */
    for(Index = FR_17_ERAY_DEC_ZERO; Index < Fr_ListSize; Index++)
    {

      Fr_ChannelAEvenListPtr[Index] = FR_17_ERAY_DEC_ZERO;

      Fr_ChannelBEvenListPtr[Index] = FR_17_ERAY_DEC_ZERO;

      Fr_ChannelAOddListPtr[Index] = FR_17_ERAY_DEC_ZERO;

      Fr_ChannelBOddListPtr[Index] = FR_17_ERAY_DEC_ZERO;
    }

    /* [cover parentID={5A973007-ED46-4e37-AB10-3C4DF3F2921F}]
    Loop till Index is (Fr List Size -1)
    [/cover] */
    for(Index = FR_17_ERAY_DEC_ZERO; Index < Fr_ListSize; Index++)
    {
      /*  Frame Ids of the SYNC frames received in even Comm Cycle */
      /* [cover parentID={2C0A5DEC-58DD-4eb3-8A25-A555C3468E71}]
      Is SYNC Frame received in even cycle on channel A for the
      corresponding index ?
      [/cover] */
      if (ERAY[Fr_CtrlIdx]->ESID_1S[Index].B.RXEA == 1U)
      {
        /* [cover parentID={3DE07D11-B355-4e27-90FE-02EB58336658}]
        Write the received sync frame ID to address provided by
        Fr_ChannelAEvenListPtr with the appropriate indexing
        [/cover] */
        Fr_ChannelAEvenListPtr[Index] =
             (uint16) ERAY[Fr_CtrlIdx]->ESID_1S[Index].B.EID;
      }

      /* [cover parentID={9FE2F668-D656-4038-856D-CAFDB25C388E}]
      Is SYNC Frame received in even cycle on channel B for the
      corresponding index ?
      [/cover] */
      if ( ERAY[Fr_CtrlIdx]->ESID_1S[Index].B.RXEB == 1U)
      {
        /* [cover parentID={902C6FBE-E44A-4279-AA08-5AACDBE679F2}]
        Write the received sync frame ID to address provided by
        Fr_ChannelBEvenListPtr with the appropriate indexing
        [/cover] */
        Fr_ChannelBEvenListPtr[Index] =
             (uint16) ERAY[Fr_CtrlIdx]->ESID_1S[Index].B.EID;
      }

      /*  Frame ids of the SYNC frames received in Odd comm. cycle */
      /* [cover parentID={B2052EEE-801A-464c-8171-4E7BA429868B}]
      Is SYNC Frame received in odd cycle on channel A for the
      corresponding index ?
      [/cover] */
      if (ERAY[Fr_CtrlIdx]->OSID_1S[Index].B.RXOA == 1U)
      {
        /* [cover parentID={CD52FF19-57BA-4c39-B5FC-CF05D404AE0F}]
        Write the received sync frame ID to address provided by
        Fr_ChannelAOddListPtr with the appropriate indexing
        [/cover] */
        Fr_ChannelAOddListPtr[Index] =
                            (uint16) ERAY[Fr_CtrlIdx]->OSID_1S[Index].B.OID;
      }

      /* [cover parentID={39190500-C7FE-454d-ADF1-A05FC60DCF93}]
      Is SYNC Frame received in odd cycle on channel B for the
      corresponding index ?
      [/cover] */
      if ( ERAY[Fr_CtrlIdx]->OSID_1S[Index].B.RXOB == 1U)
      {
        /* [cover parentID={D51A28A6-7646-4681-8D9C-69DF37410BD6}]
        Write the received sync frame ID to address provided by
        Fr_ChannelBOddListPtr with the appropriate indexing
         [/cover] */
        Fr_ChannelBOddListPtr[Index] =
                             (uint16) ERAY[Fr_CtrlIdx]->OSID_1S[Index].B.OID;
      }
    }

    /* [cover parentID={D9BCF112-4FCA-4d8c-A3A9-284EA16ECA2D}]
    Mark the return value as successfully finished
    [/cover] */
    RetValue = E_OK;

  }

  return RetValue;
}

/*******************************************************************************
** Traceability    : [cover parentID={12E31638-E0AB-4fc5-8765-A6568AE0B3A2}]  **
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
Std_ReturnType Fr_17_Eray_GetWakeupRxStatus(
    const uint8 Fr_CtrlIdx,
    uint8* const Fr_WakeupRxStatusPtr
)
{
  Std_ReturnType RetValue;
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  #endif

  /* [cover parentID={1C2DA84F-9165-4bb9-9CCA-14F40477A36C}]
  Mark the return value as successfully finished
  [/cover] */
  RetValue = E_OK;

  /* [cover parentID={A7807BB7-8F1E-4009-AECD-32F5355451AF}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={6966BFA5-5BD7-4319-BC31-7AA2452B87E2}]
  Check for Fr Initialization
  [/cover] */
  /* FR_17_ERAY_E_INIT_FAILED */
  DevError = Fr_17_Eray_lDetCheckNoInit(FR_17_ERAY_SID_GETWAKEUPRXSTATUS);

  /* [cover parentID={678F0345-E47D-44c9-A1BB-D59664645708}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={4BBD9591-0309-4e3c-95BE-6E6A15EC7349}]
    Check for validity of controller Index
    [/cover] */
    /* FR_17_ERAY_E_INV_CTRL_IDX */
    DevError = Fr_17_Eray_lDetCheckInvCtrlIdx(Fr_CtrlIdx,
                                      FR_17_ERAY_SID_GETWAKEUPRXSTATUS);
  }

  /* [cover parentID={980B01EE-DABD-4171-A56C-BAD6C425584B}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={2A96FC7D-914C-4908-A30A-B683BAA876B7}]
    Check whether the Wakeup Rx status pointer is NULL
    [/cover] */
    /* FR_17_ERAY_E_PARAM_POINTER */
    DevError = Fr_17_Eray_lDetCheckInvPointer(
       Fr_WakeupRxStatusPtr,FR_17_ERAY_SID_GETWAKEUPRXSTATUS);
  }

  /* Return if a development error detected */
  /* [cover parentID={0FE64618-6F5E-4447-805F-70496897B59F}]
  Is any DET Error detected from the previous checks ?
  [/cover] */
  if (DevError != FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={7FA30B66-44B2-4931-BB3C-21B030FF8A8E}]
    Mark the return value as Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  /* [cover parentID={5FA0C6EF-93CC-4ce9-9F95-255ECFA91B8E}]
  Any DET error occurred ?
  [/cover] */
  if(RetValue == E_OK)
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */
  {
    /* [cover parentID={F94F2ABE-C304-4b1a-8EE3-50743C7E1E25}]
    Write the wakeup pattern received indication status on channel A and B
    to output parameter Fr_WakeupRxStatusPtr
    [/cover] */
    *Fr_WakeupRxStatusPtr = (uint8)ERAY[Fr_CtrlIdx]->SIR.B.WUPA;
    *Fr_WakeupRxStatusPtr |=
            (uint8)((uint32)ERAY[Fr_CtrlIdx]->SIR.B.WUPB << 1U);

    /* [cover parentID={B124384C-7D4E-4721-AACE-F254E4F32033}]
    Reset the wakeup received indication status information within
    the FlexRay controller.
    [/cover] */
    /* A flag is cleared by writing a 1 to the corresponding bit position.
      Writing a 0 has no effect on the flag*/
    ERAY[Fr_CtrlIdx]->SIR.U = FR_17_ERAY_SIR_RESET;
  }
  return RetValue;

}

/*******************************************************************************
** Traceability    : [cover parentID={00B42A7D-5EB3-4cbd-A479-FB39929496F0}]  **
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
Std_ReturnType Fr_17_Eray_SetAbsoluteTimer(
                                             const uint8 Fr_CtrlIdx,
                                             const uint8 Fr_AbsTimerIdx,
                                             const uint8 Fr_Cycle,
                                             const uint16 Fr_Offset
                                           )
{
  Std_ReturnType RetValue;

  #if(FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  #else
  UNUSED_PARAMETER(Fr_AbsTimerIdx);
  #endif

  /* [cover parentID={F3DCFBA3-E701-48f2-9355-219D00B3A2EE}]
  Mark the return value as successfully finished
  [/cover] */
  RetValue = E_OK;

  /* [cover parentID={E011A409-BDE9-4349-85D9-6CC74A5A2972}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  DevError = Fr_17_Eray_lDetCheckSetAbsoluteTimer(Fr_CtrlIdx,
                             Fr_AbsTimerIdx, Fr_Cycle, Fr_Offset,
                             FR_17_ERAY_SID_SETABSOLUTETIMER);

  /* Return if a development error detected */
  /* [cover parentID={0905CB15-57A8-49af-A90A-CC5489116AE4}]
  Is any DET Error detected from the previous checks ?
  [/cover] */
  if (DevError != FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={9CF9DBAA-02F2-4040-B1BE-39830C5F5DC8}]
    Mark the return value as Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  /* [cover parentID={8F0D45CD-0462-4cf5-98A4-ED4341AC775C}]
  Any DET error occurred ?
  [/cover] */
  if(RetValue == E_OK)
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */
  {
    /* (ASR version is 422 and DET is Enabled ) or Runtime error detect is enabled */
  #if(((MCAL_AR_VERSION == MCAL_AR_422) &&\
       (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON))\
         || (FR_17_ERAY_RUNTIME_ERROR_DETECT == STD_ON))
    /* [cover parentID={F9217DE9-410F-4094-8FAF-E370AC756566}]
    Get the CC synchronization status with global time
    [/cover] */
    /* [cover parentID={19FBE834-1C6A-4025-A989-E25E062EF103}]
    Is Fr CC Not in sync with global time ?
    [/cover] */
    if (Fr_17_Eray_lIsCCInSync(Fr_CtrlIdx) == (uint32)0U)
    {
      /* [cover parentID={6AAFB7CA-B425-4b33-919E-113E4362ABD7}]
      Report Runtime or DET erro
      [/cover] */
      /* FR_17_ERAY_E_INV_POCSTATE if controller is not synchronised to
        global time */
      Fr_17_Eray_lReportRuntimeDetError(FR_17_ERAY_SID_SETABSOLUTETIMER,
                                                   FR_17_ERAY_E_INV_POCSTATE);
      RetValue = E_NOT_OK;
    }
    else
    #endif /*(((MCAL_AR_VERSION == MCAL_AR_422) && \
            (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)) \
               || (FR_17_ERAY_RUNTIME_ERROR_DETECT == STD_ON))*/
    {
      /* [cover parentID={545FAC7D-CFBD-4cc4-AF8E-8850AA393027}]
      Is CC synchronized with global time?
      [/cover] */
      if (Fr_17_Eray_lIsCCInSync(Fr_CtrlIdx) == (uint32)1U)
      {
        /* [cover parentID={293897B5-D920-4110-8012-92A20FD16CCC}]
        Halt the absolute timer 0
        [/cover] */
        ERAY[Fr_CtrlIdx]->T0C.B.T0RC = FR_17_ERAY_DEC_ZERO;

        /* [cover parentID={291F7AAB-7BDA-4d18-A8AA-0051264D4397}]
        Configure the absolute timer according to the parameters Fr_Cycle
        and Fr_Offset and in continuous mode
        [/cover] */
        /* [cover parentID={032A4707-AB44-4403-92B3-7852B5EC3843}]
        Absolute Timer Mode - Continuous mode
        [/cover] */
        /* Set cycle value to elapse at cycle count Cycle, once every 64 cycles*/
        /* Set macrotick offset and Timer mode (Continuous) */
        ERAY[Fr_CtrlIdx]->T0C.U =
        (uint32)(((FR_17_ERAY_TIMER_CYCLECODE_ONCE_IN_64 | (uint32)Fr_Cycle)
                                          << FR_17_ERAY_TIMER_CYCLECODE_SHIFT) |
                       ((uint32)Fr_Offset << FR_17_ERAY_TIMER_MACROTICK_SHIFT) |
                        FR_17_ERAY_TIMER_MODE_MASK);

        /* [cover parentID={23B8E0A8-E3C6-422f-A8B7-1E74EA2DD4D6}]
        Start the absolute timer 0
        [/cover] */
        ERAY[Fr_CtrlIdx]->T0C.B.T0RC = FR_17_ERAY_DEC_ONE;
      }
      else
      {
        /* [cover parentID={D8E0080E-7F4E-4deb-A24D-26A4E444A487}]
        Mark the return value as Error detected
        [/cover] */
        RetValue = E_NOT_OK;
      }
    }
  }

  return RetValue;

}

/*******************************************************************************
** Traceability    : [cover parentID={01850E3B-AB92-44ec-B65B-6B098C44F8F7}]  **
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
**                   Fr_AbsTimerIdx - Index of absolute timer within the      **
**                                    context of the FlexRay CC.              **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
Std_ReturnType Fr_17_Eray_CancelAbsoluteTimer(
                                               const uint8 Fr_CtrlIdx,
                                               const uint8 Fr_AbsTimerIdx
                                             )
{
  Std_ReturnType RetValue;
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  #else
  UNUSED_PARAMETER(Fr_AbsTimerIdx);
  #endif

  /* [cover parentID={7DC565A4-5EE7-4a53-9C6E-3CBAF0C318FE}]
  Mark the return value as successfully finished.
  [/cover] */
  RetValue = E_OK;

  /* [cover parentID={42D0D252-B20D-42da-93AA-0050C3796E54}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={E986B7D9-F9DB-494a-BE93-2009DC37DA1B}]
  Check for Fr Initialization
  [/cover] */
  /* FR_17_ERAY_E_INIT_FAILED */
  DevError = Fr_17_Eray_lDetCheckNoInit(FR_17_ERAY_SID_CANCELABSOLUTETIMER);

  /* [cover parentID={4AE7A3E2-32D5-4290-89A0-EFA6DE3CED1E}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={7BB1C1AC-A1A6-4792-B771-73FD101BC76F}]
    Check for validity of controller Index
    [/cover] */
    /* FR_17_ERAY_E_INV_CTRL_IDX */
    DevError = Fr_17_Eray_lDetCheckInvCtrlIdx(Fr_CtrlIdx,
                                         FR_17_ERAY_SID_CANCELABSOLUTETIMER);
  }

  /* [cover parentID={FF1D4CD3-702B-4b8a-9743-6F1CF3D87638}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={13354EF2-86E3-4e57-87B3-C5D62321D668}]
    Check for validity of absolute timer index
    [/cover] */
    /* FR_17_ERAY_E_INV_TIMER_IDX */
    DevError = Fr_17_Eray_lDetCheckInvTimerIdx(Fr_AbsTimerIdx,
                                         FR_17_ERAY_SID_CANCELABSOLUTETIMER);
  }

  /* Return if a development error detected */
  /* [cover parentID={2377E35E-683E-4498-AF5F-06BF379869C8}]
  Is any DET Error detected from the previous checks ?
  [/cover] */
  if (DevError != FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={7C6464A2-707D-488a-BE8A-E2918D3597A0}]
    Mark the return value as Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  /* [cover parentID={FF2412C0-1E2C-4bdc-8255-7A817447D074}]
  Any DET error occurred ?
  [/cover] */
  if(RetValue == E_OK)
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */
  {
    /* [cover parentID={31A5A7F1-5619-4f76-8548-C5BAA36F8712}]
    Disable Timer service request 0
    [/cover] */
    ERAY[Fr_CtrlIdx]->SIER.U = FR_17_ERAY_SIER_TI0E_MASK;

    /* [cover parentID={BDDE27A1-EFCE-44e0-951F-0AF89027C812}]
    Halt the absolute timer
    [/cover] */
    ERAY[Fr_CtrlIdx]->T0C.B.T0RC = FR_17_ERAY_DEC_ZERO;
  }

  return RetValue;

}


/*******************************************************************************
** Traceability    : [cover parentID={B6CE4BD8-A7D6-4f44-8C85-451B69D5C71A},
                                     {A98A91D8-7793-4124-8D83-011AF84B780A}]  **
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
**                  Fr_AbsTimerIdx - Index of absolute timer within the       **
**                                    context of the FlexRay CC.              **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
Std_ReturnType Fr_17_Eray_EnableAbsoluteTimerIRQ(
                                                   const uint8 Fr_CtrlIdx,
                                                   const uint8 Fr_AbsTimerIdx
                                                 )
{
  Std_ReturnType RetValue;
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  #else
  UNUSED_PARAMETER(Fr_AbsTimerIdx);
  #endif

  /* [cover parentID={518FE3C7-E2E0-46c7-A1E8-DFA4D97F0427}]
  Mark the return value as successfully finished.
  [/cover] */
  RetValue = E_OK;

  /* [cover parentID={87E3E600-CA9F-4d20-A197-1FF330981836}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={0FDEAE54-0F27-494c-AD04-78D141B15449}]
  Check for Fr Initialization
  [/cover] */
  /* FR_17_ERAY_E_INIT_FAILED */
  DevError = Fr_17_Eray_lDetCheckNoInit(FR_17_ERAY_SID_ENABLEABSOLUTETIMERIRQ);

  /* [cover parentID={C7959518-568D-47c2-B08C-FCE9692FA977}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={8E9DEC2C-54A8-451a-AEEA-4292668E59F0}]
    Check for validity of controller Index
    [/cover] */
    /* FR_17_ERAY_E_INV_CTRL_IDX */
    DevError = Fr_17_Eray_lDetCheckInvCtrlIdx(Fr_CtrlIdx,
                                       FR_17_ERAY_SID_ENABLEABSOLUTETIMERIRQ);
  }

  /* [cover parentID={16527B9C-E346-4041-B19B-DB5F79BAEBB5}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={97793036-71E0-49d2-B08A-DDF3FF88E6CE}]
    Check for validity of absolute timer index
    [/cover] */
    /* FR_17_ERAY_E_INV_TIMER_IDX */
    DevError = Fr_17_Eray_lDetCheckInvTimerIdx(Fr_AbsTimerIdx,
                                       FR_17_ERAY_SID_ENABLEABSOLUTETIMERIRQ);
  }

  /* Return if a development error detected */
  /* [cover parentID={1BD960E0-307B-4efe-9ECF-97D65B2ADBE4}]
  Is any DET Error detected from the previous checks ?
  [/cover] */
  if (DevError != FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={A021DD4C-1B24-444d-84C2-BE384DD6904A}]
    Mark the return value as Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  /* [cover parentID={20588FE7-098A-4e10-A51D-CA3191E46A86}]
  Any DET error occurred ?
  [/cover] */
  if(RetValue == E_OK)
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Clear any pending Timer Service Request 0 flag */
    ERAY[Fr_CtrlIdx]->SIR.U = FR_17_ERAY_SIR_TI0_MASK;

    /* [cover parentID={ABD467C1-B376-4623-A58B-5C12752FA1BC}]
    Enable timer service request 0.
    [/cover] */
    ERAY[Fr_CtrlIdx]->SIES.U = FR_17_ERAY_SIES_TI0E_MASK;
  }

  return RetValue;

}

/*******************************************************************************
** Traceability    : [cover parentID={C043CE52-58C9-4a16-8774-CDA936ACBB79},
                                     {A98A91D8-7793-4124-8D83-011AF84B780A}]  **
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
Std_ReturnType Fr_17_Eray_AckAbsoluteTimerIRQ(
                                               const uint8 Fr_CtrlIdx,
                                               const uint8 Fr_AbsTimerIdx
                                             )
{
  Std_ReturnType RetValue;
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  #else
  UNUSED_PARAMETER(Fr_AbsTimerIdx);
  #endif
  /* [cover parentID={1D6E3DE5-CB99-492b-8E5A-B1E9D8C7C895}]
  Mark the return value as successfully finished.
  [/cover] */
  RetValue = E_OK;

  /* [cover parentID={346F39C2-AB28-4fe5-8039-214057C6B8E4}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={45982EE1-E47E-425f-80B0-6A42C3FDEC1F}]
  Check for Fr Initialization
  [/cover] */
  /* FR_17_ERAY_E_INIT_FAILED */
  DevError = Fr_17_Eray_lDetCheckNoInit(FR_17_ERAY_SID_ACKABSOLUTETIMERIRQ);

  /* [cover parentID={22526644-EC3C-458d-9207-1D78433B2490}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={8D6D2554-99B3-4763-BE19-902708601348}]
    Check for validity of controller Index
    [/cover] */
    /* FR_17_ERAY_E_INV_CTRL_IDX */
    DevError = Fr_17_Eray_lDetCheckInvCtrlIdx(Fr_CtrlIdx,
                                        FR_17_ERAY_SID_ACKABSOLUTETIMERIRQ);
  }

  /* [cover parentID={5A4D22D2-1019-4b92-9F13-28C2A13A271B}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={0AB15B96-8BED-4579-A6E1-27A1174BE9D6}]
    Check for validity of absolute timer index
    [/cover] */
    /* FR_17_ERAY_E_INV_TIMER_IDX */
    DevError = Fr_17_Eray_lDetCheckInvTimerIdx(Fr_AbsTimerIdx,
                                        FR_17_ERAY_SID_ACKABSOLUTETIMERIRQ);
  }

  /* Return if a development error detected */
  /* [cover parentID={E8E630A7-CDB0-4cf9-9C57-D6986CB71098}]
  Is any DET Error detected from the previous checks ?
  [/cover] */
  if (DevError != FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={0C2B7F1B-A3B1-41c3-B0BB-66E8D582E673}]
    Mark the return value as Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  /* [cover parentID={992E817E-1C60-4d03-BAD6-63782F7901A1}]
  Any DET error occurred ?
  [/cover] */
  if(RetValue == E_OK)
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */
  {
    /* [cover parentID={AE851852-F38D-429d-8543-747AA4004CB2}]
    Clear timer service request 0 flag.
    [/cover] */
    ERAY[Fr_CtrlIdx]->SIR.U = FR_17_ERAY_SIR_TI0_MASK;
  }

  return RetValue;

}

/*******************************************************************************
** Traceability    : [cover parentID={3102E8C2-CEE4-4d89-9D4E-73C93E85626F},
                                     {A98A91D8-7793-4124-8D83-011AF84B780A}]  **
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
Std_ReturnType Fr_17_Eray_DisableAbsoluteTimerIRQ(
                                                   const uint8 Fr_CtrlIdx,
                                                   const uint8 Fr_AbsTimerIdx
                                                 )
{
  Std_ReturnType RetValue;
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  #else
  UNUSED_PARAMETER(Fr_AbsTimerIdx);
  #endif

  /* [cover parentID={2D946D54-477E-4020-856F-329820F3FE08}]
  Mark the return value as successfully finished.
  [/cover] */
  RetValue = E_OK;

  /* [cover parentID={0C8F008B-662B-45e3-9F83-7D67F5108A2F}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={4675816E-1D89-40cd-BCC6-FF877B8BC150}]
  Check for Fr Initialization
  [/cover] */
  /* FR_17_ERAY_E_INIT_FAILED */
  DevError = Fr_17_Eray_lDetCheckNoInit(FR_17_ERAY_SID_DISABLEABSOLUTETIMERIRQ);

  /* [cover parentID={D9049DDE-3A0C-4f70-9743-E5F6C62A8C75}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={0DC9DCCC-EAB9-40d6-A594-3C6E76EA7323}]
    Check for validity of controller Index
    [/cover] */
    /* FR_17_ERAY_E_INV_CTRL_IDX */
    DevError = Fr_17_Eray_lDetCheckInvCtrlIdx(Fr_CtrlIdx,
                                     FR_17_ERAY_SID_DISABLEABSOLUTETIMERIRQ);
  }

  /* [cover parentID={85AC0584-EDAC-4e1c-A38C-3DCDCB047BC3}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={F7992EBE-796B-4ab1-BA3A-2CE40E923739}]
    Check for validity of absolute timer index
    [/cover] */
    /* FR_17_ERAY_E_INV_TIMER_IDX */
    DevError = Fr_17_Eray_lDetCheckInvTimerIdx(Fr_AbsTimerIdx,
                                     FR_17_ERAY_SID_DISABLEABSOLUTETIMERIRQ);
  }

  /* Return if a development error detected */
  /* [cover parentID={E4983E00-2CEA-4b58-9DB3-8C0474F14E32}]
  Is any DET Error detected from the previous checks ?
  [/cover] */
  if (DevError != FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={A4838B53-48A2-4055-B6DC-F17771BCC53A}]
    Mark the return value as Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  /* [cover parentID={0EC72DE0-2CF7-458a-9368-C7F28EAEFB24}]
  Any DET error occurred ?
  [/cover] */
  if(RetValue == E_OK)
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */
  {
    /* [cover parentID={38AA1CB2-7ED7-474b-BF79-57C815CBCAC3}]
    Disable the timer service request 0
    [/cover] */
    ERAY[Fr_CtrlIdx]->SIER.U = FR_17_ERAY_SIER_TI0E_MASK;
  }

  return RetValue;

}


/*******************************************************************************
** Traceability    : [cover parentID={EC2D77CB-D6F1-4bad-803E-82E21D3946DB},
                                     {A98A91D8-7793-4124-8D83-011AF84B780A}]  **
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
Std_ReturnType Fr_17_Eray_GetAbsoluteTimerIRQStatus(
                                                const uint8 Fr_CtrlIdx,
                                                const uint8 Fr_AbsTimerIdx,
                                                boolean* const Fr_IRQStatusPtr
                                                   )
{
  Std_ReturnType RetValue;
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  #else
  UNUSED_PARAMETER(Fr_AbsTimerIdx);
  #endif

  /* [cover parentID={9D609F89-6DEC-4c5f-83EA-474F91EA8A77}]
  Mark the return value as successfully finished.
  [/cover] */
  RetValue = E_OK;

  /* [cover parentID={2F3F5C3B-7B42-420b-ACEF-FC48360BC606}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={6F723F2F-56E0-450a-99E8-5959FEB663EF}]
  Check for Fr Initialization
  [/cover] */
  /* FR_17_ERAY_E_INIT_FAILED */
  DevError = Fr_17_Eray_lDetCheckNoInit(FR_17_ERAY_SID_GETABSTIMERIRQSTATUS);

  /* [cover parentID={F278399C-FD7F-4a41-B866-954708BA5E18}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={9B5E95E6-D0E8-4f96-A7B8-6C309F8308A9}]
    Check for validity of controller Index
    [/cover] */
    /* FR_17_ERAY_E_INV_CTRL_IDX */
    DevError = Fr_17_Eray_lDetCheckInvCtrlIdx(Fr_CtrlIdx,
                                   FR_17_ERAY_SID_GETABSTIMERIRQSTATUS);
  }

  /* [cover parentID={7F3927B5-3D1A-412c-844F-A3C589272540}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={CE8B0026-A6D7-41e2-A7B5-DD9276D154B1}]
    Check for validity of absolute timer index
    [/cover] */
    /* FR_17_ERAY_E_INV_TIMER_IDX */
    DevError = Fr_17_Eray_lDetCheckInvTimerIdx(Fr_AbsTimerIdx,
                                   FR_17_ERAY_SID_GETABSTIMERIRQSTATUS);
  }

  /* [cover parentID={C690FD51-3903-44ec-A38C-6941CE1B3CA9}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={7CB74969-D946-4592-9009-B56AC5A1FA81}]
    Check whether the IRQ status pointer is NULL
    [/cover] */
    /* FR_17_ERAY_E_PARAM_POINTER */
    DevError = Fr_17_Eray_lDetCheckInvPointer(Fr_IRQStatusPtr,
                                   FR_17_ERAY_SID_GETABSTIMERIRQSTATUS);
  }

  /* Return if a development error detected */
  /* [cover parentID={F46879C9-90B6-450c-8F65-0E488B4F71D3}]
  Is any DET Error detected from the previous checks ?
  [/cover] */
  if (DevError != FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={46814387-9F2B-4609-BC27-8A14B90FA854}]
    Mark the return value as Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  /* [cover parentID={9CDD4F68-1268-42b2-9355-01D8BA68D2AA}]
  Any DET error occurred ?
  [/cover] */
  if(RetValue == E_OK)
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */
  {
    /* [cover parentID={F9E9B8D2-D546-4345-BD5F-87C5FAFE56D2}]
    Is the timer service request 0 status not cleared/ not acknowledged?
    [/cover] */
    /* Check if timer service request 0 flag is not cleared (acknowledged) */
    if (ERAY[Fr_CtrlIdx]->SIR.B.TI0 != (uint8)0U)
    {
      /* [cover parentID={4B831A64-7AF5-4fe7-9E9B-12F59166CC8B}]
      Write TRUE  to output parameter Fr_IRQStatusPtr
      [/cover] */
      *Fr_IRQStatusPtr = (boolean)TRUE;
    }
    else
    {
      /* [cover parentID={58CB7223-4CD9-44f8-97D2-0CA5E5E3631F}]
      Write FALSE to output parameter Fr_IRQStatusPtr
      [/cover] */
      *Fr_IRQStatusPtr = (boolean)FALSE;
    }
  }

  return RetValue;

}

#if (FR_17_ERAY_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID={123F8E6D-2C40-4648-AB22-E0FC31699468}]  **
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
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): VersioninfoPtr - Pointer to where to store the           **
**                    version information of this module.                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
void Fr_17_Eray_GetVersionInfo(Std_VersionInfoType * const VersioninfoPtr)
{
  /* [cover parentID={7388A595-B46F-4823-B56C-3595DA4A3265}]
  Fr_17_Eray_GetVersionInfo
  [/cover] */
  /* [cover parentID={B2E7E62B-D7E3-494c-A93C-A028EB69E49A}]
  DET is Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={99B59C13-3B23-47f4-823F-8CC1A30EB64D}]
  Is the Version Info Pointer NULL ?
  [/cover] */
  /* FR_17_ERAY_E_PARAM_POINTER is reported if input pointer is NULL */
  if (VersioninfoPtr == NULL_PTR)
  {
    /* [cover parentID={4A2333DD-5914-47c2-8EF9-B2FB6AF87E21}]
    Report DET
    [/cover] */
    (void)Det_ReportError(FR_17_ERAY_MODULE_ID, FR_17_ERAY_INSTANCE_ID,
                    FR_17_ERAY_SID_GETVERSIONINFO, FR_17_ERAY_E_PARAM_POINTER);
  }
  else
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */
  {
    /* [cover parentID={202A161F-58AF-432a-8145-06F7B8AFCF3F}]
    Write the values of Module ID, Vendor ID, SW Major, Minor and
    Patch version to the Version Info Pointer
    [/cover] */
    /* FR Module ID */
    VersioninfoPtr->moduleID = FR_17_ERAY_MODULE_ID;
    /* FR vendor ID */
    VersioninfoPtr->vendorID = (uint16)FR_17_ERAY_VENDOR_ID;
    /* major version of FR */
    VersioninfoPtr->sw_major_version = (uint8)FR_17_ERAY_SW_MAJOR_VERSION;
    /* minor version of FR */
    VersioninfoPtr->sw_minor_version = (uint8)FR_17_ERAY_SW_MINOR_VERSION;
    /* patch version of FR */
    VersioninfoPtr->sw_patch_version = (uint8)FR_17_ERAY_SW_PATCH_VERSION;
  }
}
#endif /* (FR_17_ERAY_VERSION_INFO_API == STD_ON) */

/*******************************************************************************
** Traceability    : [cover parentID={F319D30E-D0F9-44bc-8440-FE1A42405CB3}]  **
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
Std_ReturnType Fr_17_Eray_ReadCCConfig(
                                        const uint8 Fr_CtrlIdx,
                                        const uint8 Fr_ConfigParamIdx,
                                        uint32* const Fr_ConfigParamValuePtr
                                      )
{
  Std_ReturnType RetValue;
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  #endif
  uint8 LogIdx;

  /* [cover parentID={97066293-AA6B-4e85-8072-4F97655E4E68}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  RetValue = E_OK;

  /* [cover parentID={5996514B-47E6-4646-95D3-7D9FC44F64FB}]
  Check for Fr Initialization
  [/cover] */
  /* FR_17_ERAY_E_INIT_FAILED */
  DevError = Fr_17_Eray_lDetCheckNoInit(FR_17_ERAY_SID_READCCCONFIG);

  /* [cover parentID={A011E3F9-B9D6-4c47-90C8-EDDEC50DDBBB}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={E15A7600-2BB7-4102-822D-DCF151C8819D}]
    Check for validity of controller Index
    [/cover] */
    /* FR_17_ERAY_E_INV_CTRL_IDX */
    DevError = Fr_17_Eray_lDetCheckInvCtrlIdx(Fr_CtrlIdx,
                                      FR_17_ERAY_SID_READCCCONFIG);
  }

  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={F37A3E7E-8D62-49c7-A075-50AE6E70908D}]
    Is there No DET Error due to the previous check AND
    Is the Config Parameter Index Invalid ?
    [/cover] */
    /* FR_17_ERAY_E_INV_CONFIG_IDX (0 - 62)*/
    if (Fr_ConfigParamIdx >= FR_17_ERAY_CONFIG_PARAM_IDX_MAX )
    {
      /* [cover parentID={C5841471-58DA-417d-B166-2919FCE1E287}]
      Report DET
      [/cover] */
      (void)Det_ReportError(FR_17_ERAY_MODULE_ID, FR_17_ERAY_INSTANCE_ID,
                     FR_17_ERAY_SID_READCCCONFIG, FR_17_ERAY_E_INV_CONFIG_IDX);
      DevError = FR_17_ERAY_E_INV_CONFIG_IDX;
    }
  }

  /* [cover parentID={77963C24-CC36-4a93-BE0B-27DDE38D9017}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={FC374537-8D88-4487-B157-0611F7E1B00E}]
    Check whether the Config Param value pointer is NULL
    [/cover] */
    /* FR_17_ERAY_E_PARAM_POINTER */
    DevError = Fr_17_Eray_lDetCheckInvPointer(
       Fr_ConfigParamValuePtr,FR_17_ERAY_SID_READCCCONFIG);
  }

  /* Return if a development error detected */
  /* [cover parentID={026D1BC4-ECF1-4c4b-8140-53AAFFE17E22}]
  Any DET Error detected from the previous checks ?
  [/cover] */
  if (DevError != FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={BD3B6839-04E7-411e-8628-1FE0D18E357A}]
    Mark the return value as Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  /* [cover parentID={73ACE545-57DE-463f-8B32-F8036DD1E51A}]
  Any DET error occurred ?
  [/cover] */
  if(RetValue == E_OK)
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */
  {
    LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];

    /* [cover parentID={B9F2FCBF-6840-40e8-8E60-29106A83085B}]
    Retrieve the value of the configuration parameter that corresponds to the
    Config Parameter Index and write it to the output parameter.
    [/cover] */
    *Fr_ConfigParamValuePtr =
      Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].ConfigParamPtr[Fr_ConfigParamIdx];

    /* [cover parentID={C3960EE2-02E8-493b-93F9-0D731F51D4AD}]
    Mark the return value as successfully finished
    [/cover] */
    RetValue = E_OK;
  }

  return RetValue;
}

/*******************************************************************************
**                      Local Function Definitions                          **
*******************************************************************************/

/*******************************************************************************
** Traceability    : [cover parentID={46C2FA79-776F-4575-9A0A-CBBED0672684}]  **
**                                                                            **
** Syntax          : uint32 Fr_17_Eray_lChangePOCState                        **
**                        (const uint8 Fr_CtrlIdx, const uint8 ChiCmdId)      **
**                                                                            **
** Description     : Function to change ERAY POC state.                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  None                                                    **
**                                                                            **
** Sync/Async      :  Asynchronous                                            **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                   ChiCmdId -  Command to be written to the SUCC1.CMD       **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  zero     : Function call finished successfully.         **
**                    non-zero : Function call aborted due to time out error  **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Fr_17_Eray_lChangePOCState(const uint8 Fr_CtrlIdx,
                                               const uint8 ChiCmdId)
{
  uint32 TimeOutCount;
  uint32 TimeOutCountInitial;
  uint32 TimeOutResolution;
  uint32 MeasuredTicks;
  uint32 ErrCount;
  volatile uint8 PbsyChk;
  volatile uint8 ChiCmdChk;
  uint8 LogIdx;
  ErrCount = FR_17_ERAY_DEC_ZERO;

  /* Load the timeout value */
  TimeOutResolution = Mcal_DelayTickResolution();
  TimeOutCount = (uint32)FR_17_ERAY_TIMEOUT_DURATION / TimeOutResolution;
  TimeOutCountInitial = Mcal_DelayGetTick();

  /* Wait till the SUCC1.PBSY bit is cleared or timeout detected */
  do
  {

    MeasuredTicks = Mcal_DelayGetTick() -  TimeOutCountInitial;
    PbsyChk = ERAY[Fr_CtrlIdx]->SUCC1.B.PBSY;
    /* [cover parentID={48E9C448-9BEA-47ef-87D3-46F147ED3130}]
    Is (POC in busy state) AND (timeout has not occurred) ?
    [/cover] */
  } while ((PbsyChk == (uint8)1U) && (TimeOutCount > MeasuredTicks));


  LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];

  /* [cover parentID={3D57ED9B-2764-4d54-BDE2-CC628C587FC2}]
  Did a timeout occur ?
  [/cover] */
  if (PbsyChk == (uint8)1U)
  {
    /* [cover parentID={75E5D4AF-0B89-43b4-BA7F-BBCF5FACA888}]
    Is a DEM event configured for controller test ?
    [/cover] */
    if(Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].FrDemCtrlTestResultId !=
       (Dem_EventIdType)FR_17_ERAY_DEM_REPORT_DISABLED)
    {
      /* [cover parentID={4BC60960-0570-4da7-8279-FE0CEE26FEF9}]
      Report the Production error status as FAILED to Mcal_Wrapper
      [/cover] */
      Fr_17_Eray_lReportDemError(Fr_17_Eray_ConfigPtr->
                              CfgPtr[LogIdx].FrDemCtrlTestResultId,
                            DEM_EVENT_STATUS_FAILED);
    }
    /* [cover parentID={DA5FA7CF-01E3-4b42-898B-2E85DBA75D25}]
    Error detected - Increment the error count
    [/cover] */
    ErrCount++;
  }
  else
  {
    /* [cover parentID={85FD8FC0-1F70-47e5-A4CD-C028F2B33263}]
    Write the input CHI command into the CHI command vector register field
    [/cover] */
    ERAY[Fr_CtrlIdx]->SUCC1.B.CMD = ChiCmdId;

    ChiCmdChk = ERAY[Fr_CtrlIdx]->SUCC1.B.CMD;

    /* [cover parentID={F5EC9616-28C0-4076-8133-F4007AD4BA21}]
    Is the CHI command accepted ?
    [/cover] */
    if (ChiCmdChk == FR_17_ERAY_CHI_CMD_NOT_ACCEPTED)
    {
      /* [cover parentID={DA5FA7CF-01E3-4b42-898B-2E85DBA75D25}]
      Error detected - Increment the error count
      [/cover] */
      ErrCount++;
    }

  }

  return ErrCount;
}

#if (FR_17_ERAY_TX_CONFLICT_DETECTION == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID={C229AA80-56C8-4451-B768-237FFCD1CFDF}]  **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_lConflictStatusCheck           **
**                             const uint8 Fr_CtrlIdx,                        **
**                             const uint8 ChannelIdx                         **
**                         )                                                  **
**                                                                            **
** Description     : Checks if conflict occurred during transmission.         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :                                                          **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                                                                            **
**                   ChannelIdx - Channel A, Channel B or Channel AB of       **
**                   controller                                               **
**                                                                            **
** Return value    :  E_OK: If no transmission conflict is observed.          **
**                    E_NOT_OK: Transmission conflict is detected             **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fr_17_Eray_lConflictStatusCheck(
                                                const uint8 Fr_CtrlIdx,
                                                const uint8 ChannelIdx)
{
  Std_ReturnType RetValue;
  boolean ChASts;
  boolean ChBSts;

  RetValue = E_OK;

    /*[cover parentID={32C38734-B0FF-478d-8A07-B8C0CD1929AF}]
      Check if Channel A ?
      [/cover] */
  if(ChannelIdx == (uint8)FR_CHANNEL_A)
  {
    /* [cover parentID={1DDE1F43-FFF7-4074-84D8-AA06CAAC6333}]
       Check if conflict occurred on Channel A ?
       [/cover] */
    if(ERAY[Fr_CtrlIdx]->MBS.B.TCIA == 1U)
    {
      RetValue = E_NOT_OK;
    }
  }
  /* [cover parentID={50F2ACAB-59AA-4b20-9CF2-DB8536F315F8}]
     Check if Channel B ?
     [/cover] */
  else if(ChannelIdx == (uint8)FR_CHANNEL_B)
  {
  /* [cover parentID={956E01CD-16C1-4dc9-82B8-45206F02F6C6}]
     Check if conflict occurred on Channel B ?
     [/cover] */
    if(ERAY[Fr_CtrlIdx]->MBS.B.TCIB == 1U)
    {
      RetValue = E_NOT_OK;
    }
  }
  /* Evaluate Channel-AB */
  else
  {
    ChASts = ERAY[Fr_CtrlIdx]->MBS.B.TCIA;
    ChBSts = ERAY[Fr_CtrlIdx]->MBS.B.TCIB;

     /* [cover parentID={AB2674B6-3B01-4ebe-A52B-956A7675ED9C}]
     Check if conflict occurred on Channel A or B ?
    [/cover] */
    if((ChASts == 1U) || (ChBSts == 1U))
    {
      RetValue = E_NOT_OK;
    }
  }

  return RetValue;
}
#endif /* (FR_17_ERAY_TX_CONFLICT_DETECTION == STD_ON) */

/*******************************************************************************
** Traceability    : [cover parentID={CEAF1518-7380-4038-87CF-5806FD484FB0}]  **
**                                                                            **
** Syntax          : uint32 Fr_17_Eray_lWaitTillPOCChange                     **
**                        (const uint8 Fr_CtrlIdx, const uint8 PocState)      **
**                                                                            **
** Description     : Function to wait for ERAY POC state change               **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant for the same device                        **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                   PocState -  POC state within the context of the          **
**                                FlexRay CC Fr_CtrlIdx                       **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : zero     : Function call finished successfully.          **
**                   non-zero : Function call aborted due to error (time out) **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Fr_17_Eray_lWaitTillPOCChange(
                        const uint8 Fr_CtrlIdx, const uint8 PocState)
{
  uint32 TimeOutCount;
  uint32 TimeOutCountInitial;
  uint32 TimeOutResolution;
  uint32 MeasuredTicks;
  uint32 ErrorCount;
  uint8 LogIdx;
  volatile uint8 Pocs;
  ErrorCount = (uint32)FR_17_ERAY_DEC_ZERO;
  TimeOutResolution = Mcal_DelayTickResolution();
  TimeOutCount = (uint32)FR_17_ERAY_TIMEOUT_DURATION / TimeOutResolution;
  TimeOutCountInitial = Mcal_DelayGetTick();

  do
  {

    MeasuredTicks = Mcal_DelayGetTick() -  TimeOutCountInitial;
    Pocs = ERAY[Fr_CtrlIdx]->CCSV.B.POCS;
    /* [cover parentID={A7D174E8-FA9D-48ec-A785-AF946D783B85}]
    Is (Controller POCS not same as POC state input parameter ) AND
    (timeout has not occurred) ?
    [/cover] */
  }  while ((Pocs != PocState) && (TimeOutCount > MeasuredTicks));


  LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];

  /* [cover parentID={7EE76BE1-0813-4360-B870-670B429B99F8}]
  Did a timeout occur ?
  [/cover] */
  if (Pocs != PocState)
  {
    /* [cover parentID={B2610DAD-CBB8-4e24-AB8C-131E18BB5F12}]
    Is a DEM event configured for controller test ?
    [/cover] */
    if(Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].FrDemCtrlTestResultId !=
       (Dem_EventIdType)FR_17_ERAY_DEM_REPORT_DISABLED)
    {
      /* [cover parentID={88892493-910F-4142-BA74-B2A6A1A36116}]
      Report the Production error status as FAILED to Mcal_Wrapper
      [/cover] */
      Fr_17_Eray_lReportDemError(Fr_17_Eray_ConfigPtr->
                                CfgPtr[LogIdx].FrDemCtrlTestResultId,
                            DEM_EVENT_STATUS_FAILED);
    }

    ErrorCount++;
  }

  return ErrorCount;
}

/*******************************************************************************
** Traceability    : [cover parentID={98F4E1C2-371C-489a-B31E-04015C42C0BE}]  **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_lChangePOCToReady              **
**                          (const uint8 Fr_CtrlIdx)                          **
**                                                                            **
** Description     : Switch the CC to POC:Ready state.                        **
**                   Hardware requires uninterrupted execution of lock        **
**                   sequence, hence the need to disable all interrupts.      **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant for the same device                        **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fr_17_Eray_lChangePOCToReady(const uint8 Fr_CtrlIdx)
{
  uint32 TimeOutCount;
  uint32 TimeOutCountInitial;
  uint32 TimeOutResolution;
  uint32 MeasuredTicks;
  Std_ReturnType RetValue;
  volatile uint8 PbsyChk;
  uint8 LogIdx;

  RetValue = E_OK;

  /* [cover parentID={7A2FAD9E-DE0C-4701-82CA-33BBD3F42EA6}]
  Critical section
  [/cover] */
  /* [cover parentID={1E8DFCB9-58A3-4883-8B69-BBD345C66F8D}]
  Enter SchM section
  [/cover] */
  SchM_Enter_Fr_17_Eray_ConfigLockKey();

  /* Lock sequence start */
  /* [cover parentID={5AB92664-106C-400f-8F81-8AA6F8931C8E}]
  Write 0xCE to configuration Lock Key field as part of Unlock sequence
  [/cover] */
  ERAY[Fr_CtrlIdx]->LCK.B.CLK = FR_17_ERAY_UNLOCK_SEQ1;

  /* [cover parentID={CD072167-4059-487b-B28A-9EAD99EB33DD}]
  Write 0x31 to configuration Lock Key field as part of Unlock sequence
  [/cover] */
  ERAY[Fr_CtrlIdx]->LCK.B.CLK = FR_17_ERAY_UNLOCK_SEQ2;

  /* Switch CC into 'POC:ready'*/
  /* [cover parentID={40350EBC-6505-48b5-9213-9145B8CEC981}]
  Write the CHI command 'READY' to the CHI command vector
  [/cover] */
  ERAY[Fr_CtrlIdx]->SUCC1.B.CMD = FR_17_ERAY_CHI_CMD_READY;
  /* Lock sequence end */

  /* [cover parentID={295631A7-50ED-4c52-911F-0057D37F59DA}]
  Exit SchM section
  [/cover] */
  /* Exit Critical Section */
  SchM_Exit_Fr_17_Eray_ConfigLockKey();

  /* wait till the SUCC1.PBSY bit is cleared  */
  TimeOutResolution = Mcal_DelayTickResolution();
  TimeOutCount = (uint32)FR_17_ERAY_TIMEOUT_DURATION / TimeOutResolution;
  TimeOutCountInitial = Mcal_DelayGetTick();

  do
  {
    MeasuredTicks = Mcal_DelayGetTick() -  TimeOutCountInitial;
    PbsyChk = ERAY[Fr_CtrlIdx]->SUCC1.B.PBSY;
    /* [cover parentID={F8DC2A2D-E8E8-45dd-B93B-906856FBB3C9}]
    Is (POC in busy state) AND (timeout has not occurred) ?
    [/cover] */
  } while ((PbsyChk == (uint8)1U) && (TimeOutCount > MeasuredTicks));


  LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];

  /* Report time out Production error to Mcal_Wrapper */
  /* [cover parentID={EE63B9DA-D383-4ebf-A9EF-D02B96CC91E1}]
  Did a timeout occur ?
  [/cover] */
  if (PbsyChk == (uint8)1U)
  {
    /* [cover parentID={3BCDF2BE-BAE4-40a1-AFC9-88C9B7CABFC9}]
    Is a DEM event configured for controller test ?
    [/cover] */
    if(Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].FrDemCtrlTestResultId !=
       (Dem_EventIdType)FR_17_ERAY_DEM_REPORT_DISABLED)
    {
      /* [cover parentID={2AC6A312-27CA-45e4-95F1-15F12A713440}]
      Report the Production error status as FAILED to Mcal_Wrapper
      [/cover] */
      Fr_17_Eray_lReportDemError(Fr_17_Eray_ConfigPtr->
                            CfgPtr[LogIdx].FrDemCtrlTestResultId,
                            DEM_EVENT_STATUS_FAILED);
    }
    /* [cover parentID={BE624284-0B4E-49ad-9A55-8C48865587DC}]
    Mark the return value as Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  return RetValue;
}

/*******************************************************************************
** Traceability    : [cover parentID={BC9B832C-5A4A-4c42-B482-6E014259E1B3}]  **
**                                                                            **
** Syntax          : uint32 Fr_17_Eray_lHeaderCRC                             **
**                        (const uint32 FrameId, const uint8 PayloadLength)   **
**                                                                            **
** Description     : Used to Re Calculate Header CRC for Dynamic frames       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : FrameId - Frame ID                                       **
**                   PayloadLength -  Payload length                          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : HeaderCRC                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Fr_17_Eray_lHeaderCRC(
  const uint32 FrameId,
  const uint8 PayloadLength
)
{
  uint32 vCrcReg;
  uint32 vCrcPoly;
  uint32 vNextBitCrcReg;
  uint32 vCrcNext;
  uint32 length;
  uint32 Header;
  uint32 vNextBitHeader;

  /* [cover parentID={96AC687B-1389-42a5-8B05-2DE4D3152398}]
  Combine the Frame ID and Payload Length to form the header section on which
  the CRC is to be computed
  [/cover] */
  Header = (FrameId << FR_17_ERAY_HEADER_FID_BITPOS) | PayloadLength;
  /* Initial value for Header CRC - 0x1A */
  vCrcReg = FR_17_ERAY_HEADER_VECTOR_INITVAL;
  /* Flexray header CRC polynomial - 0x385U */
  vCrcPoly = FR_17_ERAY_HEADER_CRC_POLYNOMINAL;
  /* Number of bits for Header CRC Calculation  - 0x14 */
  length = FR_17_ERAY_NUM_BITS_FOR_HEADERCRC;

  Header = Header << FR_17_ERAY_NUM_12;
  vCrcReg = vCrcReg << FR_17_ERAY_NUM_21;
  vCrcPoly = vCrcPoly << FR_17_ERAY_NUM_21;

  /* [cover parentID={CA8FD20D-EB5C-4758-8A43-5A16EE1734DF}]
  Loop till the CRC is computed for all the bits
  [/cover] */
  while(length != FR_17_ERAY_DEC_ZERO)
  {
    vNextBitHeader = Header & FR_17_ERAY_MASK_MSB;
    vNextBitCrcReg = vCrcReg & FR_17_ERAY_MASK_MSB;
    vCrcNext = vNextBitHeader ^ vNextBitCrcReg;

    Header = Header << 1U;
    vCrcReg = vCrcReg << 1U;

    /* [cover parentID={87D132FB-72B7-428b-A422-70A0ADCC2228}]
    Is the result of the XOR operation from the previous step non-zero ?
    [/cover] */
    if(vCrcNext != FR_17_ERAY_DEC_ZERO)
    {
      vCrcReg = vCrcReg ^ vCrcPoly;
    }

    length--;
  }

  vCrcReg = vCrcReg >> FR_17_ERAY_NUM_21;

  /* [cover parentID={7FDC39AD-7AD1-4a87-A8AC-ABC2C27C8A7D}]
  Return the computed CRC value
  [/cover] */
  return vCrcReg;

}

#if (FR_17_ERAY_FIFO_CONFIGURED == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID={D16D957B-D046-4523-AE31-1CE7C093199C}]  **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_lReceiveRxFifo                 **
                     (                                                        **
**                      const uint8 Fr_CtrlIdx, const uint16 Fr_LPduIdx,      **
**                      uint8* const Fr_LSduPtr,                              **
**                      Fr_RxLPduStatusType* const Fr_LPduStatusPtr,          **
**                      uint8* const Fr_LSduLengthPtr                         **
**                   )                                                        **
**                                                                            **
** Description     : Function to perform Receive Fifo functionality           **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  NA                                                      **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                   Fr_LPduIdx - This index is used to uniquely identify a   **
**                                  FlexRay frame.                            **
**                   Fr_LSduPtr - This reference points to a buffer where the **
**                                  LSdu to be received shall be stored       **
**                   Fr_LPduStatusPtr - This reference points to the memory   **
**                                      location where the status of the LPdu **
**                                      shall be stored                       **
**                   Fr_LSduLengthPtr - This reference points to the memory   **
**                           location where the length of the LSdu (in bytes) **
**                           shall be stored. This length represents the      **
**                           number of bytes copied to LSduPtr.               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fr_17_Eray_lReceiveRxFifo(
                                 const uint8 Fr_CtrlIdx,
                                 const uint16 Fr_LPduIdx,
                                 uint8* const Fr_LSduPtr,
                                 Fr_RxLPduStatusType* const Fr_LPduStatusPtr,
                                 uint8* const Fr_LSduLengthPtr)
{
  Std_ReturnType RetVal;
  uint8 LogIdx;
  uint8 ChannelIdx;

  LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];
  RetVal = E_OK;

  /* Check if FIFO is not empty */
  /* [cover parentID={ED9913C6-BFD7-476b-8BAB-E88869F417C6}]
  Is the receive FIFO non-empty ?
  [/cover] */
  if (ERAY[Fr_CtrlIdx]->FSR.B.RFNE == 1U)
  {
    /*Receive FIFO is not empty, hence Read the New data*/

    /* [cover parentID={EF37AEDB-52DA-4152-8E6E-11194C209233}]
    Request for the transfer from the First FIFO message buffer into
    Output shadow buffer
    [/cover] */
    RetVal = Fr_17_Eray_lRxTransferToOBF(Fr_CtrlIdx, Fr_LPduIdx,
                             (uint8)ERAY[Fr_CtrlIdx]->MRC.B.FFB);
    /* [cover parentID={F81258D1-6504-4f8c-8D4F-3ABAE0BE56C0}]
    In case of error, return E_NOT_OK
    [/cover] */

    /* [cover parentID={B0F2FBD2-84E2-4a27-9A01-B361359331F6}]
    Is the request transfer successfully done ?
    [/cover] */
    if (RetVal == E_OK)
    {
#if(MCAL_AR_VERSION == MCAL_AR_440)
      ChannelIdx = (uint8)((Fr_17_Eray_ConfigPtr->
             CfgPtr[LogIdx].LPduConfigPtr[Fr_LPduIdx].Wrhs1CfgVal >>
             IFX_ERAY_WRHS1_CHA_OFF) & FR_17_ERAY_WRHS1_CHANNEL_MASK);
#else
      /* [cover parentID={2EC9630C-98A3-43ca-83C6-05AC517F6521}]
      Subtract 1 to correct the channel as per Fr_ChannelType enum in
      AUTOSAR 4.2.2, to be used for further processing
      [/cover] */
      ChannelIdx = (uint8)(((Fr_17_Eray_ConfigPtr->
             CfgPtr[LogIdx].LPduConfigPtr[Fr_LPduIdx].Wrhs1CfgVal >>
             IFX_ERAY_WRHS1_CHA_OFF) & FR_17_ERAY_WRHS1_CHANNEL_MASK) -
                                                         (uint8)0x1);
#endif

      /* [cover parentID={993C1D3D-8243-498d-9545-4870FC64377F}]
      Perform the acceptance check for receive operation
      [/cover] */
      RetVal = Fr_17_Eray_lRxAcceptanceCheck(Fr_CtrlIdx, ChannelIdx);

      /* [cover parentID={CEF96D0A-5546-49f4-B00E-5BC7FDD072E6}]
      Any Error detected ?
      [/cover] */
      if (RetVal == E_OK)
      {
        Fr_17_Eray_lReceiveDataCopy(Fr_CtrlIdx, Fr_LSduPtr, Fr_LSduLengthPtr);

        /* Check if Receive FIFO Fill Level has reached FIFO Critical Level
         (which is configured as depth) */
        /* [cover parentID={20FB8E73-C53E-45b4-BAFE-EB252796F600}]
        Return the value as E_OK
        [/cover] */
        /* [cover parentID={A94B5997-B664-47bc-86F5-0A1CFFC528A1}]
        Is the Receive-FIFO fill level (new data not yet read by the host)
        non-zero?
        [/cover] */
        if (ERAY[Fr_CtrlIdx]->FSR.B.RFFL != 0U)
        {
          /* [cover parentID={74040A1B-44ED-43ec-A36A-1ECA5B4F5F61}]
          Write FR_RECEIVED_MORE_DATA_AVAILABLE to LPdu status pointer
          [/cover] */
          /* FIFO has not reached critical level, more data is available in
             FIFO to be read */
          *Fr_LPduStatusPtr = FR_RECEIVED_MORE_DATA_AVAILABLE;
        }
        else
        {
          /* FIFO has reached critical level, No data is available in
             FIFO to be read */
          /* Receive FIFO is empty, New data is not received by FIFO */
          /* [cover parentID={9AAE124B-80D4-433f-8D52-206D90318C80}]
          Write FR_RECEIVED to LPdu status pointer
          [/cover] */
          *Fr_LPduStatusPtr = FR_RECEIVED;
        }
      }
      else
      {
        *Fr_LPduStatusPtr = FR_NOT_RECEIVED;
        *Fr_LSduLengthPtr = FR_17_ERAY_DEC_ZERO;
      }
    }
  }
  else
  {
    /* Receive FIFO is empty, New data is not received by FIFO */
    /* [cover parentID={2031D80D-CED7-43e3-A8CB-882A854DC2A4}]
    Write FR_NOT_RECEIVED to the LPdu status pointer
    [/cover] */
    *Fr_LPduStatusPtr = FR_NOT_RECEIVED;
    *Fr_LSduLengthPtr = FR_17_ERAY_DEC_ZERO;
  }

  return RetVal;

}
#endif /* (FR_17_ERAY_FIFO_CONFIGURED == STD_ON) */

#if(FR_17_ERAY_CTRL_TEST_COUNT != 0U)
/*******************************************************************************
** Traceability    : [cover parentID={043014EF-6EBA-4aa5-B69F-6F7B0DCC4145}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE uint32 Fr_17_Eray_lVerifyCCConfig           **
                     (                                                        **
                       const uint8 Fr_CtrlIdx,                                **
                       const uint8 LogIndex                                   **
                     )                                                        **
**                                                                            **
** Description     : The CC test to check if node and cluster FlexRay         **
**                     parameters were written properly into the FlexRay      **
**                     Communication Controller                               **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  NA                                                      **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                   LogIndex - Logical index of the communication controller **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fr_17_Eray_lVerifyCCConfig
                         (const uint8 Fr_CtrlIdx, const uint8 LogIndex)
{
  uint32 CtrlTest;
  uint32 CtrlTestRes;
  const Fr_17_Eray_CCConfigType *CCConfigPtr;
  uint8 RegCount;
  Std_ReturnType RetValue;

  CCConfigPtr = Fr_17_Eray_ConfigPtr->CfgPtr[LogIndex].CCCfgPtr;
  /* Initialize the return variable */
  CtrlTestRes = FR_17_ERAY_TEST_FAIL;

  /* [cover parentID={058FA8FC-3298-4d53-8898-504BB4E33534}]
  Loop until (Index < Ctrl Test Count parameter) AND
  (Ctrl test result status is FAIL)
  [/cover] */
  for (RegCount=FR_17_ERAY_DEC_ZERO; ((RegCount < FR_17_ERAY_CTRL_TEST_COUNT)&&
                     (CtrlTestRes == FR_17_ERAY_TEST_FAIL)); RegCount++)
  {
    /* [cover parentID={BCC4BB2E-011E-4a8c-A86C-D0228C9C6BCF}]
    Read back each of the register values which are configured for CC test
    [/cover] */
    CtrlTest = ((ERAY[Fr_CtrlIdx]->SUCC1.U) & (~FR_17_ERAY_SUCC1_CMD_MASK)) ^
             (CCConfigPtr->Succ1CfgVal);
    CtrlTest |= ((ERAY[Fr_CtrlIdx]->SUCC2.U) ^ (CCConfigPtr->Succ2CfgVal));
    CtrlTest |= ((ERAY[Fr_CtrlIdx]->SUCC3.U) ^ (CCConfigPtr->Succ3CfgVal));
    CtrlTest |= ((ERAY[Fr_CtrlIdx]->NEMC.U) ^ (CCConfigPtr->NemcCfgVal));
    CtrlTest |= ((ERAY[Fr_CtrlIdx]->PRTC1.U) ^ (CCConfigPtr->Prtc1CfgVal));
    CtrlTest |= ((ERAY[Fr_CtrlIdx]->PRTC2.U) ^ (CCConfigPtr->Prtc2CfgVal));
    CtrlTest |= ((ERAY[Fr_CtrlIdx]->MHDC.U) ^ (CCConfigPtr->MhdcCfgVal));
    CtrlTest |= ((ERAY[Fr_CtrlIdx]->GTUC01.U) ^ (CCConfigPtr->Gtuc01CfgVal));
    CtrlTest |= ((ERAY[Fr_CtrlIdx]->GTUC02.U) ^ (CCConfigPtr->Gtuc02CfgVal));
    CtrlTest |= ((ERAY[Fr_CtrlIdx]->GTUC03.U) ^ (CCConfigPtr->Gtuc03CfgVal));
    CtrlTest |= ((ERAY[Fr_CtrlIdx]->GTUC04.U) ^ (CCConfigPtr->Gtuc04CfgVal));
    CtrlTest |= ((ERAY[Fr_CtrlIdx]->GTUC05.U) ^ (CCConfigPtr->Gtuc05CfgVal));
    CtrlTest |= ((ERAY[Fr_CtrlIdx]->GTUC06.U) ^ (CCConfigPtr->Gtuc06CfgVal));
    CtrlTest |= ((ERAY[Fr_CtrlIdx]->GTUC07.U) ^ (CCConfigPtr->Gtuc07CfgVal));
    CtrlTest |= ((ERAY[Fr_CtrlIdx]->GTUC08.U) ^ (CCConfigPtr->Gtuc08CfgVal));
    CtrlTest |= ((ERAY[Fr_CtrlIdx]->GTUC09.U) ^ (CCConfigPtr->Gtuc09CfgVal));
    CtrlTest |= ((ERAY[Fr_CtrlIdx]->GTUC10.U) ^ (CCConfigPtr->Gtuc10CfgVal));
    CtrlTest |= ((ERAY[Fr_CtrlIdx]->GTUC11.U) ^ (CCConfigPtr->Gtuc11CfgVal));
    CtrlTest |= ((ERAY[Fr_CtrlIdx]->CUST1.U & FR_17_ERAY_CUST1_MASK) ^
                                                 (CCConfigPtr->Cust1CfgVal));

    /* [cover parentID={229B9EB8-EC62-4aa7-B5A7-AD548369830E}]
    Does the register values match the configured values?
    [/cover] */
    if (CtrlTest == (uint32)0U)
    {
      /* [cover parentID={7547D04E-B702-4fe3-BA11-2C0EC7D83915}]
      Mark the Ctrl test status result as PASS
      [/cover] */
      CtrlTestRes = FR_17_ERAY_TEST_PASS;
    }
  }

  /* [cover parentID={7FD0CBB8-805F-41da-A09B-768A118BEB7A}]
  Did any Error occur during the verification of parameters?
  [/cover] */
  if (CtrlTestRes == FR_17_ERAY_TEST_PASS)
  {
    /* [cover parentID={E02D5B23-2CFF-48a6-A992-D1861B45274C}]
    Is a Production error configured for controller test?
    [/cover] */
    if(Fr_17_Eray_ConfigPtr->CfgPtr[LogIndex].FrDemCtrlTestResultId !=
       (Dem_EventIdType)FR_17_ERAY_DEM_REPORT_DISABLED)
    {
      /* [cover parentID={BB8E20B0-0146-4b3d-B1B4-DC15DF14AE8A}]
      Report the Production error status as PASSED to Mcal_Wrapper
      [/cover] */
      Fr_17_Eray_lReportDemError(
           Fr_17_Eray_ConfigPtr->CfgPtr[LogIndex].FrDemCtrlTestResultId,
                            DEM_EVENT_STATUS_PASSED);
    }

    RetValue = E_OK;
  }
  else
  {
    /* [cover parentID={5772D118-EC7C-469e-A12B-14115148BC4A}]
    Is a Production error configured for controller test?
    [/cover] */
    if(Fr_17_Eray_ConfigPtr->CfgPtr[LogIndex].FrDemCtrlTestResultId !=
        (Dem_EventIdType)FR_17_ERAY_DEM_REPORT_DISABLED)
    {
      /* [cover parentID={068E9F37-5CA5-4a7f-8708-E1EFE58AEFDE}]
      Report the Production error status as FAILED to Mcal_Wrapper
      [/cover] */
      Fr_17_Eray_lReportDemError(
          Fr_17_Eray_ConfigPtr->CfgPtr[LogIndex].FrDemCtrlTestResultId,
                            DEM_EVENT_STATUS_FAILED);
    }

    /* [cover parentID={CCB23D18-D06F-4688-AD7A-508A3701128D}]
    Mark the return value as Error Detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  return RetValue;
}
#endif  /* (FR_17_ERAY_CTRL_TEST_COUNT != 0U) */

/*******************************************************************************
** Traceability    : [cover parentID={E8A331F9-CF9E-4d9c-ABF4-170A5E6C03D6}]  **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_lWaitTransferComplete          **
                     (                                                        **
                       const uint8 Fr_CtrlIdx,                                **
                       const uint8 LogIdx                                     **
                     )                                                        **
**                                                                            **
** Description     : Function to check the OBSYS bit is cleared after a       **
**                   Request transfer of Message Buffer                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  NA                                                      **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                   LogIdx - Logical index of the communication controller   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to timeout error.        **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fr_17_Eray_lWaitTransferComplete
                             (const uint8 Fr_CtrlIdx, const uint8 LogIdx)
{
  Std_ReturnType RetValue;
  uint32 TimeOutCount;
  uint32 TimeOutCountInitial;
  uint32 TimeOutResolution;
  uint32 MeasuredTicks;
  volatile uint8 Obsys;

  RetValue =  E_OK;
  TimeOutResolution = Mcal_DelayTickResolution();
  TimeOutCount = (uint32)FR_17_ERAY_MBF_TO_OBF_TRNSF_TIMEOUT/ TimeOutResolution;
  TimeOutCountInitial = Mcal_DelayGetTick();

  do
  {
    MeasuredTicks = Mcal_DelayGetTick() - TimeOutCountInitial;
    Obsys = ERAY[Fr_CtrlIdx]->OBCR.B.OBSYS;
    /* [cover parentID={345F1AC6-8471-4096-9F0C-7637F6A9288E}]
    Is (Output shadow buffer in busy state) AND (timeout has not occurred) ?
    [/cover] */
  } while ((Obsys == (uint8)1U) && (TimeOutCount > MeasuredTicks));

  /* Report time out Production error to Mcal_Wrapper */
  /* [cover parentID={021B9806-5DA3-4dff-B53E-A29917F76B9A}]
  Did a timeout occur ?
  [/cover] */
  if (Obsys == (uint8)1U)
  {
    /* [cover parentID={188D877C-E28F-4959-93EA-E0EA3C3AB501}]
    Is a DEM event configured for controller test ?
    [/cover] */
    if(Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].FrDemCtrlTestResultId !=
       (Dem_EventIdType)FR_17_ERAY_DEM_REPORT_DISABLED)
    {
      /* [cover parentID={A9A577E4-B766-41fb-859D-87F0F723FEB6}]
      Report the Production error status as FAILED to Mcal_Wrapper
      [/cover] */
      Fr_17_Eray_lReportDemError(
      Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].FrDemCtrlTestResultId,
                            DEM_EVENT_STATUS_FAILED);
    }
    RetValue =  E_NOT_OK;

  }

  return RetValue;
}

/*******************************************************************************
** Traceability    : [cover parentID={3B2206DA-5EFF-474b-9CE4-9450250F8827}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE void Fr_17_Eray_lMessageBufferInit          **
                     (                                                        **
                       const uint8 Fr_CtrlIdx,                                **
                       const uint8 LogIdx                                     **
                     )                                                        **
**                                                                            **
** Description     : Function to initialize the Message Buffer handling       **
**                   variables                                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  NA                                                      **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                   LogIdx - Logical index of the communication controller   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Fr_17_Eray_lMessageBufferInit(const uint8 Fr_CtrlIdx,
                                                const uint8 LogIdx)
{
  uint16 LPduIdx;
  uint8 MsgBuffIdx;
  #if (FR_17_ERAY_FIFO_CONFIGURED == STD_ON)
  uint8 FirstFifoBuffIdx;
  #endif

  /* Initialize array Fr_17_Eray_MsgBuff2LPduIdx[ ] with unused LPDU index
     values */
  for(MsgBuffIdx = FR_17_ERAY_DEC_ZERO;
      MsgBuffIdx < Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].MsgBuffCountMax;
      MsgBuffIdx++)
  {
    Fr_17_Eray_MsgBuff2LPduIdxPtr[Fr_CtrlIdx][MsgBuffIdx] =
                                           FR_17_ERAY_LPDU_IDX_UNUSED;
  }

  /* [cover parentID={A8F23604-4D1F-4d77-8FF5-C31B69CEE5F9}]
  Is FIFO Configured ?
  [/cover] */
  #if (FR_17_ERAY_FIFO_CONFIGURED == STD_ON)
  /* [cover parentID={7AF5BD38-52A5-4929-8412-0CD7FED3DCCD}]
  Is the FIFO config pointer NULL ?
  [/cover] */
  if (Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].RxFifoConfigPtr != NULL_PTR)
  {
    /* [cover parentID={8CB5BA19-F45C-45c4-B25E-C6201198EDE1}]
    Determine index (FIFO index) of the First FIFO buffer ->
    max message buffer count - FIFO depth
    [/cover] */
    FirstFifoBuffIdx = Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].MsgBuffCountMax -
           Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].RxFifoConfigPtr->FrFifoDepth;
  }
  else
  {
    FirstFifoBuffIdx = Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].MsgBuffCountMax;
  }
  #endif
  /* Construct array Fr_17_Eray_MsgBuff2LPduIdx[ ] */

  /* [cover parentID={8DD61E78-97A2-42e5-82EC-DD2EAE26B32E}]
  Loop till the last LPdu count
  [/cover] */
  for (LPduIdx = FR_17_ERAY_DEC_ZERO; LPduIdx <
    Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].LPduCount; LPduIdx++)
  {
    /* Check if the LPDU belongs to FIFO, else proceed */
    /* [cover parentID={941AC63D-073A-47eb-B0CE-E0B94F28809D}]
    Is the LPdu part of FIFO ?
    [/cover] */
    if(Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].LPduIdx2MsgBuffIdxPtr[LPduIdx]
       != (uint8)FR_17_ERAY_MSGBUFF_UNUSED)
    {
      /* In the case of HW buffer reconfiguration check whether buffer index is
        already allocated to an LPDU, else proceed */
      /* [cover parentID={83D79581-6972-4f94-BA5E-BAA4D4AE4F9A}]
      Is the message buffer index not allocated to an LPdu ?
      [/cover] */
      if (Fr_17_Eray_MsgBuff2LPduIdxPtr
            [Fr_CtrlIdx][Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].
            LPduIdx2MsgBuffIdxPtr[LPduIdx]] == FR_17_ERAY_LPDU_IDX_UNUSED)
      {
        /* [cover parentID={6F7B50ED-9F39-4370-BF23-B405A44C224C}]
        Update message buffer to LPdu index mapping array with LPdu index
        [/cover] */
        Fr_17_Eray_MsgBuff2LPduIdxPtr[Fr_CtrlIdx][Fr_17_Eray_ConfigPtr->
           CfgPtr[LogIdx].LPduIdx2MsgBuffIdxPtr[LPduIdx]] = LPduIdx;
      }
    }

    /* [cover parentID={4939177D-1072-494d-89F4-032B214619E8}]
    FIFO Configured
    [/cover] */
    #if (FR_17_ERAY_FIFO_CONFIGURED == STD_ON)
    /* This is for the FIFO LPDUs */
    else
    {
      /* if the buffer index is valid */
      /* [cover parentID={0155E327-1010-447e-AD61-9DA2BDD88B2A}]
      Is the FIFO index valid ?
      [/cover] */
      if (FirstFifoBuffIdx < Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].\
                                                        MsgBuffCountMax)
      {
        /* [cover parentID={92C7D8B9-76BD-49d0-8D21-ACC7C5CEE589}]
        Update the FIFO index of message buffer to LPdu index mapping array
        with the LPdu index
        [/cover] */
        Fr_17_Eray_MsgBuff2LPduIdxPtr[Fr_CtrlIdx][FirstFifoBuffIdx] = LPduIdx;
        FirstFifoBuffIdx++;
      }
    }
    #endif
  } /* End For LPduIdx */

}

/*******************************************************************************
** Traceability    : [cover parentID={391AD299-E945-4fcb-9AF7-97856CC7B2F0}]  **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_lSlotStatusErrorCheck          **
**                      (const uint8 Fr_CtrlIdx, const uint8 ChannelIdx       **
**                                               const uint16 Fr_LPduIdx)     **
**                                                                            **
** Description     : Function to check for the presence of Slot Status Error. **
**                   This function is to be invoked only if DEM is configured.**
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant for the same device                        **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                   ChannelIdx - Index of FlexRay channel within the context **
**                                of the FlexRay CC Fr_CtrlIdx                **
**                   Fr_LPduIdx - Index to uniquely identify a FlexRay frame  **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: API call finished successfully.                    **
**                   E_NOT_OK: API call aborted due to timeout error.         **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Fr_17_Eray_lSlotStatusErrorCheck(
                      const uint8 Fr_CtrlIdx, const uint8 ChannelIdx,
                                              const uint16 Fr_LPduIdx)
{
  uint32 ErayMbsChA;
  uint32 ErayMbsChB;
  uint8 LogIdx;
  Std_ReturnType RetValue;

  RetValue = E_OK;

  ErayMbsChA = (uint32)(ERAY[Fr_CtrlIdx]->MBS.U & FR_17_ERAY_MBS_CHA_ERRORMASK);
  ErayMbsChB = (uint32)(ERAY[Fr_CtrlIdx]->MBS.U & FR_17_ERAY_MBS_CHB_ERRORMASK);

  /* [cover parentID={249F340A-56EA-4634-B35A-603A87AD007B}]
  Is (Slot error detected on Channel A) AND (requested channel index is A) ?
  [/cover] */
  if((ChannelIdx == (uint8)FR_CHANNEL_A) && (ErayMbsChA != (uint32)0U))
  {
    /* [cover parentID={E992C2FD-3D90-42be-A53D-7549431EFA8C}]
    Mark the return value as Slot Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }
  /* [cover parentID={C0D57E6D-E735-490f-B1D0-A6C765DA67C1}]
  Is (Slot error detected on Channel B) AND (requested channel index is B) ?
  [/cover] */
  else if((ChannelIdx == (uint8)FR_CHANNEL_B) && (ErayMbsChB != (uint32)0U))
  {
    /* [cover parentID={6E964086-A3B9-411e-B705-2DB8342CF5E9}]
    Mark the return value as Slot Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }
  /* [cover parentID={E874CF4F-06BB-48fd-AE67-3E0F07EF307E}]
  Is (Slot error detected on Channel A&B) AND (requested channel index is AB)?
  [/cover] */
  else if((ErayMbsChA != (uint32)0U) && (ErayMbsChB != (uint32)0U))
  {
    /* [cover parentID={53C29E35-3386-49f8-94E6-9115FBB22266}]
    Mark the return value as Slot Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }
  else
  {
    /* for misra warning */
  }

  LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];

  /* If single slot status error bit (vSS!SyntaxError, vSS!ContentError,
  vSS!Bviolation) is set, Raise Production Error -> DEM_EVENT_STATUS_FAILED */
  /* [cover parentID={371BC828-B2B0-4721-A72E-A4A3E6452645}]
  Any Slot Error detected ?
  [/cover] */
  if(RetValue == E_NOT_OK)
  {
    /* [cover parentID={F7D5FD2A-7324-4ecf-AD55-E2DD87F48C39}]
    Report the Production error status as FAILED to Mcal_Wrapper
    [/cover] */
    Fr_17_Eray_lReportDemError(Fr_17_Eray_ConfigPtr->
              CfgPtr[LogIdx].LPduConfigPtr[Fr_LPduIdx].FrDemFTSlotStatusErrId,
                          DEM_EVENT_STATUS_FAILED);
  }
  else
  {
    /* If single slot status error bit (vSS!SyntaxError, vSS!ContentError,
    vSS!Bviolation) is not set, Raise Production Error -> DEM_EVENT_STATUS_PASSED */
    /* [cover parentID={9F31C51B-BB9A-4f2c-978B-5ECD626C587C}]
    Report the Production error status as PASSED to Mcal_Wrapper
    [/cover] */
    Fr_17_Eray_lReportDemError(Fr_17_Eray_ConfigPtr->
              CfgPtr[LogIdx].LPduConfigPtr[Fr_LPduIdx].FrDemFTSlotStatusErrId,
                          DEM_EVENT_STATUS_PASSED);
  }

  return RetValue;

}

/*******************************************************************************
** Traceability    : [cover parentID={FAA17C4F-0F75-45dd-8A5F-2FEA24D77496}]  **
**                                                                            **
** Syntax          : uint32 Fr_17_Eray_lIsCCInSync (const uint8 Fr_CtrlIdx)   **
**                                                                            **
** Description     : Function to check whether the communication controller   **
**                   is synchronous to FlexRay global time.                   **
**                   Condition (!vPOC!Freeze) is not checked as CC can never  **
**                   be in (!vPOC!Freeze) when the POC state is NORMAL_ACTIVE **
**                   or NORMAL_PASSIVE.                                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant for the same device                        **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : 0 : CC is not synchronous to global time                 **
**                   1 : CC is synchronous to global time                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Fr_17_Eray_lIsCCInSync(const uint8 Fr_CtrlIdx)
{
  uint32 RetVal;
  uint8 ErayCcsv;

  /* [cover parentID={E1DA96B9-A9FD-4452-9402-19D39CD16333}]
  Get the actual state of operation of CC Protocol Operation Control (POC)
  [/cover] */
  ErayCcsv = ERAY[Fr_CtrlIdx]->CCSV.B.POCS;

  /* [cover parentID={7687F193-A298-4ef6-B452-A7212386B35C}]
  Is the POC state in NORMAL_ACTIVE or NORMAL_PASSIVE ?
  [/cover] */
  if ((ErayCcsv == FR_17_ERAY_POCS_NORMAL_ACTIVE) ||
      (ErayCcsv == FR_17_ERAY_POCS_NORMAL_PASSIVE))
  {
    /* [cover parentID={625C60F6-7282-4fb0-A902-D3B658D0B312}]
    Set the return value to '1'
    [/cover] */
    RetVal = FR_17_ERAY_DEC_ONE;
  }
  else
  {
    /* [cover parentID={568532A4-6A59-4bb2-BB5C-854596FED18F}]
    Set the return value to '0'
    [/cover] */
    RetVal = FR_17_ERAY_DEC_ZERO;
  }

  return RetVal;

}

/*******************************************************************************
** Traceability    : [cover parentID={4D36D208-B24C-4d02-912E-D5CD293C82D9}]  **
**                                                                            **
** Syntax          : Fr_SlotModeType Fr_17_Eray_lGetSlotMode                  **
                                          (const uint8 Fr_CtrlIdx)            **
**                                                                            **
** Description     : Function to provide the slotmode from CCSV register      **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant for the same device                        **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : 0 : Single slot mode                                     **
**                   1 : All pending slot mode                                **
**                   2 : All slot mode                                        **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Fr_SlotModeType Fr_17_Eray_lGetSlotMode(const uint8 Fr_CtrlIdx)
{
  Fr_SlotModeType SlotMode;
  uint8 RegVal;

  RegVal = ERAY[Fr_CtrlIdx]->CCSV.B.SLM;
  /* SLM value 0x01B is Reserved */

  /* [cover parentID={577D6EC5-C9C2-4f9c-AA60-73E283EA1838}]
  Is the Slot Mode of POC - SINGLE ?
  [/cover] */
  if (RegVal == FR_17_ERAY_DEC_ZERO)
  {
    /* [cover parentID={AC7AA159-DAB2-4288-883A-3A641E79BB83}]
    Mark the return value as FR_SLOTMODE_KEYSLOT
    [/cover] */
    SlotMode = FR_SLOTMODE_KEYSLOT;
  }
  /* [cover parentID={D1D31B00-1933-483d-A522-2CBFA5040218}]
  Is the Slot Mode of the POC - ALL_PENDING ?
  [/cover] */
  else if (RegVal == FR_17_ERAY_DEC_TWO)
  {
    /* [cover parentID={F36F46B8-CF39-42be-86B5-C476E956AAF1}]
    Mark the return value as  FR_SLOTMODE_ALL_PENDING
    [/cover] */
    SlotMode = FR_SLOTMODE_ALL_PENDING;
  }
  else
  {
    /* [cover parentID={C20D46C8-428F-43a6-A639-21E7782FF99B}]
    Mark the return value as FR_SLOTMODE_ALL
    [/cover] */
    SlotMode = FR_SLOTMODE_ALL;
  }

  return SlotMode;

}

/*******************************************************************************
** Traceability    : [cover parentID={45DECE29-3C9C-4eec-8C3B-A1F0D1A0AEEE}]  **
**                                                                            **
** Syntax          : uint32 Fr_17_Eray_lInputBufBsyHost                       **
                                          (const uint8 Fr_CtrlIdx)            **
**                                                                            **
** Description     : Check the busy status of Input buffer                    **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant for the same device                        **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : 0: Function call finished successfully                   **
**                   1: Function call aborted due to error (time out)         **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Fr_17_Eray_lInputBufBsyHost(const uint8 Fr_CtrlIdx)
{
  uint32 ErrorCount;
  uint32 TimeOutCount;
  uint32 TimeOutCountInitial;
  uint32 TimeOutResolution;
  uint32 MeasuredTicks;
  volatile uint8 IbsyhChk;
  uint8 LogIdx;

  ErrorCount = (uint32)FR_17_ERAY_DEC_ZERO;
  /* Wait till Header is moved to message buffer and input buffer is free */
  TimeOutResolution = Mcal_DelayTickResolution();
  TimeOutCount = (uint32)FR_17_ERAY_TIMEOUT_DURATION / TimeOutResolution;
  TimeOutCountInitial = Mcal_DelayGetTick();

  do
  {
    MeasuredTicks = Mcal_DelayGetTick() -  TimeOutCountInitial;
    IbsyhChk = ERAY[Fr_CtrlIdx]->IBCR.B.IBSYH;
    /* [cover parentID={721C7D77-D20B-481b-B95B-54CEC302F221}]
    Is (Input host buffer in busy state) AND (timeout has not occurred) ?
    [/cover] */
  } while ((IbsyhChk == (uint8)1U) && (TimeOutCount > MeasuredTicks));

  LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];

  /*  Raise Production Error if Input buffer is not FREE within timeout period */
  /* [cover parentID={4388C491-1B6D-4ea4-9BCB-0933B5DA23C3}]
  Did a timeout occur ?
  [/cover] */
  if (IbsyhChk == (uint8)1U)
  {
    /* [cover parentID={D9776149-97F0-4d00-934A-F53C7CC64A96}]
    Is a DEM event configured for controller test ?
    [/cover] */
    if (Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].FrDemCtrlTestResultId !=
         (Dem_EventIdType)FR_17_ERAY_DEM_REPORT_DISABLED)
    {
      /* [cover parentID={2CA13095-3081-411f-B9C7-D5A90F8095EF}]
      Report the Production error status as FAILED to Mcal_Wrapper
      [/cover] */
      Fr_17_Eray_lReportDemError(Fr_17_Eray_ConfigPtr->
                                         CfgPtr[LogIdx].FrDemCtrlTestResultId,
                             DEM_EVENT_STATUS_FAILED);
    }
    ErrorCount++;

  }

  return ErrorCount;

}

#if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)

/*******************************************************************************
** Traceability    : [cover parentID={1BD67712-48A9-4318-8286-449C3035456B}]  **
**                                                                            **
** Syntax          : uint32 Fr_17_Eray_lDetCheckInvTimerIdx                   **
                             (const uint8 TimerIdx, const uint8 ServiceId)    **
**                                                                            **
** Description     : Function to check whether the timer index is valid       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : TimerIdx - Index of absolute timer of the particular     **
**                              FlexRay CC                                    **
**                   ServiceId - Service Index of FlexRay driver API          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : FR_17_ERAY_E_DET_NO_ERR(0) : Timer index is valid        **
**                   FR_17_ERAY_E_INV_TIMER_IDX : Timer index is not valid    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Fr_17_Eray_lDetCheckInvTimerIdx(
                                                      const uint8 TimerIdx,
                                                      const uint8 ServiceId
                                                   )
{
  uint32 DevError;

  DevError = FR_17_ERAY_E_DET_NO_ERR;

  /* [cover parentID={4562A9A1-D552-4ba3-B0AF-9E7A13C67BC1}]
  HW supports only one absolute timer
  [/cover] */
  /* Only timer (absolute or relative) exists */
  /* [cover parentID={604136BB-C6B1-4ab8-9ABB-A1FD0F37515F}]
  Is the Timer Index non-zero ?
  [/cover] */
  if (TimerIdx != (uint8)0U)
  {
    /* [cover parentID={E1FFAA8B-ECDA-454d-B318-BE77940F7F7B}]
    Report DET
    [/cover] */
    (void)Det_ReportError(FR_17_ERAY_MODULE_ID, FR_17_ERAY_INSTANCE_ID,
    ServiceId,FR_17_ERAY_E_INV_TIMER_IDX);
    DevError = FR_17_ERAY_E_INV_TIMER_IDX;
  }

  return DevError;
}

/*******************************************************************************
** Traceability    : [cover parentID={55BD6C33-7466-451d-A144-EECE8B26792E}]  **
**                                                                            **
** Syntax          : uint32 Fr_17_Eray_lDetCheckInvPointer                    **
                             (const void * const Ptr, const uint8 ServiceId)  **
**                                                                            **
** Description     : Function to check whether the pointer is valid           **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : Ptr - Pointer which needs to be validated                **
**                   ServiceId - Service Index of FlexRay driver API          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : FR_17_ERAY_E_DET_NO_ERR(0) : Pointer is valid            **
**                   FR_17_ERAY_E_PARAM_POINTER : Pointer is not valid        **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Fr_17_Eray_lDetCheckInvPointer(
                                                   const void * const Ptr,
                                                   const uint8 ServiceId)
{
  uint32 DevError;
  DevError = FR_17_ERAY_E_DET_NO_ERR;

  /* [cover parentID={082C6C12-CD50-43f7-BFB6-B471070D55B5}]
  Is the received Pointer a NULL pointer?
  [/cover] */
  if (Ptr == NULL_PTR)
  {
    /* [cover parentID={B4760278-4AB7-4949-9755-2061EB1076E7}]
    Report DET
    [/cover] */
    (void)Det_ReportError(FR_17_ERAY_MODULE_ID, FR_17_ERAY_INSTANCE_ID,
                  ServiceId, FR_17_ERAY_E_PARAM_POINTER);
    DevError = FR_17_ERAY_E_PARAM_POINTER;
  }

  return DevError;
}

/*******************************************************************************
** Traceability    : [cover parentID={3BF00FF5-CAC5-4812-B295-763D24077DA8}]  **
**                                                                            **
** Syntax          : uint32 Fr_17_Eray_lDetCheckInvCtrlIdx                    **
                                (const uint8 CtrlIdx, const uint8 ServiceId)  **
**                                                                            **
** Description     : Function to check whether the controller index is valid  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                             the FlexRay Driver                             **
**                   ServiceId - Service Index of FlexRay driver API          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : FR_17_ERAY_E_DET_NO_ERR(0): Controller index is valid    **
**                   FR_17_ERAY_E_INV_CTRL_IDX: Controller index is not valid **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Fr_17_Eray_lDetCheckInvCtrlIdx(
                                                    const uint8 Fr_CtrlIdx,
                                                    const uint8 ServiceId
                                                  )
{
  uint32 DevError;

  DevError = FR_17_ERAY_E_DET_NO_ERR;

  /* Only communication controller exists */
  /* [cover parentID={198A9B1C-57C6-492e-A703-EF6CA741149A}]
  Does controller index excced the number of CCs in device OR
  Is the controller Index not configured ?
  [/cover] */
  if ((Fr_CtrlIdx >= (uint8)FR_17_ERAY_NUM_CONTROLLERS_IN_DEVICE) ||
      (FR_17_ERAY_CTRL_NOT_CONFIGURED ==
                 Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx]))
  {
    /* [cover parentID={7FC4A46D-286C-43e5-8892-627C8BC38A35}]
    Report DET
    [/cover] */
    (void)Det_ReportError(FR_17_ERAY_MODULE_ID, FR_17_ERAY_INSTANCE_ID,
                           ServiceId, FR_17_ERAY_E_INV_CTRL_IDX);
    DevError = FR_17_ERAY_E_INV_CTRL_IDX;
  }

  return DevError;
}

/*******************************************************************************
** Traceability    : [cover parentID={B9B99D04-B94F-4b68-B75A-B88244F3344A}]  **
**                                                                            **
** Syntax          : uint32 Fr_17_Eray_lDetCheckNoInit                        **
**                                                   (const uint8 ServiceId)  **
**                                                                            **
** Description     : Function to check whether the module is initialized      **
**                    or not.                                                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : ServiceId - Service Index of FlexRay driver API          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : FR_17_ERAY_E_DET_NO_ERR(0) : Module is initialized       **
**                   FR_17_ERAY_E_INIT_FAILED: Module is not initialized      **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Fr_17_Eray_lDetCheckNoInit(const uint8 ServiceId)
{
  uint32 DevError;

  DevError = FR_17_ERAY_E_DET_NO_ERR;

  /* Fr_17_Eray_Init API was NOT called */
  /* [cover parentID={8B7EAB4E-2B7F-4673-8CF0-3CBEAC4ED3CF}]
  Is the Config Pointer a NULL pointer?
  [/cover] */
  if (Fr_17_Eray_ConfigPtr == NULL_PTR)
  {
    /* [cover parentID={F79EB218-0A60-4f09-AF64-820260DBA2A9}]
    Report DET
    [/cover] */
    (void)Det_ReportError(FR_17_ERAY_MODULE_ID, FR_17_ERAY_INSTANCE_ID,
                   ServiceId, FR_17_ERAY_E_INIT_FAILED);

    DevError = FR_17_ERAY_E_INIT_FAILED;
  }

  return DevError;
}

/*******************************************************************************
** Traceability    : [cover parentID={623EA6F3-4C6E-4eb5-AE5C-6C250DF345EF}]  **
**                                                                            **
** Syntax          : uint32 Fr_17_Eray_lDetCheckInvLPduIdx                    **
**                             (const uint8 Fr_CtrlIdx, const uint16 LPduIdx, **
**                                                 const uint8 ServiceId)     **
**                                                                            **
** Description     : Function to check whether the LPdu index is valid or not **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver                          **
**                   LPduIdx - Index of LPdu                                  **
**                   ServiceId - Service Index of FlexRay driver API          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : FR_17_ERAY_E_DET_NO_ERR(0) : LPdu  is valid              **
**                   FR_17_ERAY_E_INV_LPDU_IDX : LPdu  is not valid           **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Fr_17_Eray_lDetCheckInvLPduIdx(
                                                   const uint8 Fr_CtrlIdx,
                                                   const uint16 LPduIdx,
                                                   const uint8 ServiceId
                                                  )
{
  uint32 DevError;
  uint8 LogIdx;

  DevError = FR_17_ERAY_E_DET_NO_ERR;

  LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];

  /* [cover parentID={09F0DACD-DF1A-4333-BD28-E3968103C1A8}]
  Does the LPdu Index exceed the number of LPdus configured ?
  [/cover] */
  if (LPduIdx >= Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].LPduCount)
  {
    /* [cover parentID={E6697DFB-8B38-42a5-897C-6D42CBD62CD3}]
    Report DET
    [/cover] */
    (void)Det_ReportError(FR_17_ERAY_MODULE_ID, FR_17_ERAY_INSTANCE_ID,
                        ServiceId, FR_17_ERAY_E_INV_LPDU_IDX);

    DevError = FR_17_ERAY_E_INV_LPDU_IDX;
  }

  return DevError;
}

/*******************************************************************************
** Traceability    : [cover parentID={403E648D-BB72-4e67-9698-2C2D35D18ACD}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType Fr_17_Eray_lTransmitDetCheck **
**                                   (const uint8 Fr_CtrlIdx,                 **
**                                    const uint16 Fr_LPduIdx,                **
**                                    const uint8* const Fr_LSduPtr)          **
**                                                                            **
** Description     : Function to check the development error conditions for   **
**                     the API Fr_17_Eray_TransmitTxLPdu                      **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver                          **
**                   Fr_LPduIdx - This index is used to uniquely identify a   **
**                                  FlexRay frame.                            **
**                   Fr_LSduPtr - This reference points to a buffer where the **
**                                  assembled LSdu to be transmitted within   **
**                                  this LPdu is stored at.                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: API call finished successfully.                    **
**                   E_NOT_OK: API call aborted due to errors.                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fr_17_Eray_lTransmitDetCheck(
                                               const uint8 Fr_CtrlIdx,
                                               const uint16 Fr_LPduIdx,
                                               const uint8* const Fr_LSduPtr)
{
  uint32 DevError;
  Std_ReturnType RetVal;
  uint8 LogIdx;

  /* [cover parentID={801ECE09-B690-4cb9-A471-1217FADBD34C}]
  Check for Fr Initialization
  [/cover] */
  /* FR_17_ERAY_E_INIT_FAILED */
  DevError = Fr_17_Eray_lDetCheckNoInit(FR_17_ERAY_SID_TRANSMITTXLPDU);

  /* Driver not initialized(Fr_17_Eray_ConfigPtr->
                                  CfgPtr[LogIdx] not initialized), avoid trap*/
  /* [cover parentID={5B0E4130-E5EE-4f06-BE12-EF223EAFA667}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={6A4A2767-F13B-491f-A972-782F6AD2D918}]
    Check for validity of controller Index
    [/cover] */
    /* FR_17_ERAY_E_INV_CTRL_IDX */
    DevError = Fr_17_Eray_lDetCheckInvCtrlIdx(Fr_CtrlIdx,
                                                FR_17_ERAY_SID_TRANSMITTXLPDU);
  }

  /* [cover parentID={32D31A13-CA94-46c4-8BD6-8392DAB0D3A4}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={2B802949-142F-40bc-9FA3-ACB8FDD5F7E1}]
    Check the validity of the LPdu index
    [/cover] */
    /* FR_17_ERAY_E_INV_LPDU_IDX: Fr_LPduIdx >= LPDU count  */
    DevError = Fr_17_Eray_lDetCheckInvLPduIdx(Fr_CtrlIdx,Fr_LPduIdx,
                                               FR_17_ERAY_SID_TRANSMITTXLPDU);
  }

  /* [cover parentID={7A397E54-3DA9-4655-A0F3-7396A6BDBA34}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {

     LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];

    /* [cover parentID={82A49010-F06F-49d7-8346-17A49CB7A5AA}]
    Is the direction of LPdu configured as receive ?
    [/cover] */
    /* FR_17_ERAY_E_INV_LPDU_IDX if its a receive LPDU */
    if (((Fr_17_Eray_ConfigPtr->
                    CfgPtr[LogIdx].LPduConfigPtr[Fr_LPduIdx].Wrhs1CfgVal >>
          IFX_ERAY_WRHS1_CFG_OFF) & IFX_ERAY_WRHS1_CFG_MSK) == 0U)
    {
      /* [cover parentID={03B014DA-FEDA-4948-8F2A-99CD1A2B58E8}]
      Report DET
      [/cover] */
      (void)Det_ReportError(FR_17_ERAY_MODULE_ID, FR_17_ERAY_INSTANCE_ID,
                      FR_17_ERAY_SID_TRANSMITTXLPDU, FR_17_ERAY_E_INV_LPDU_IDX);

      DevError = FR_17_ERAY_E_INV_LPDU_IDX;
    }

  }

  /* [cover parentID={C39E46AD-9E87-4d73-B63B-F5F478451B8F}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={092FFEB8-5659-4cf4-B15E-1FD68ED52053}]
    Check whether the LSdu pointer is NULL
    [/cover] */
    /* FR_17_ERAY_E_PARAM_POINTER */
    DevError = Fr_17_Eray_lDetCheckInvPointer(Fr_LSduPtr,
                                               FR_17_ERAY_SID_TRANSMITTXLPDU);
  }

  /* [cover parentID={3F7E9DE6-FB81-42a9-A51B-1E04726EEA8B}]
  Any DET Error occurred ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    RetVal = E_OK;
  }
  else
  {
    /* [cover parentID={8A664A09-E672-44b5-85F8-D6353B70C299}]
    Mark the return value as Error Detected
    [/cover] */
    RetVal = E_NOT_OK;
  }

  return RetVal;

}

/*******************************************************************************
** Traceability    : [cover parentID={D97836B4-56D7-4158-A558-46B2968888D1}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType                              **
**                    Fr_17_Eray_lCancelTxLPduDetCheck                        **
**                                  (                                         **
**                                    const uint8 Fr_CtrlIdx,                 **
**                                    const uint16 Fr_LPduIdx                 **
**                                  )                                         **
**                                                                            **
** Description     : Checks for CancelTxLpdu API DET                          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  NA                                                      **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Reentrant                                               **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                 the FlexRay Driver.                        **
**                   Fr_LPduIdx - This index is used to uniquely identify a   **
                                   FlexRay frame.                             **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fr_17_Eray_lCancelTxLPduDetCheck(
                                                const uint8 Fr_CtrlIdx,
                                                const uint16 Fr_LPduIdx)
{
  uint32 DevError;
  Std_ReturnType RetVal;
  uint8 LogIdx;

  /* FR_17_ERAY_E_INIT_FAILED */
  /* [cover parentID={084C9627-4836-4e26-A85B-5FCB6ED30125}]
  Check for Fr Initialization
  [/cover] */
  DevError = Fr_17_Eray_lDetCheckNoInit(FR_17_ERAY_SID_CANCELTXLPDU);

  /* [cover parentID={28752832-9CED-432a-98E9-669B8A23BFC0}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={9291BDEF-315B-4cb1-91B4-238E4DAE7B05}]
    Check for validity of controller Index
    [/cover] */
    /* FR_17_ERAY_E_INV_CTRL_IDX */
    DevError = Fr_17_Eray_lDetCheckInvCtrlIdx(Fr_CtrlIdx,
                                                FR_17_ERAY_SID_CANCELTXLPDU);
  }

  /* [cover parentID={746EFC50-4095-4aad-BCDE-640BCDA50AB5}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={850CE976-85A8-4dbd-A509-AFCDF564F3D5}]
    Check the validity of the LPdu index
    [/cover] */
    /* FR_17_ERAY_E_INV_LPDU_IDX: Fr_LPduIdx >= LPDU count  */
    DevError = Fr_17_Eray_lDetCheckInvLPduIdx(Fr_CtrlIdx,Fr_LPduIdx,
                                               FR_17_ERAY_SID_CANCELTXLPDU);
  }

  /* [cover parentID={00B2E672-4074-44da-A4D6-4C4C3FE587E7}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];

    /* [cover parentID={9DF8A227-FA2F-497f-B79D-E99057B85067}]
    Is the direction of LPdu configured as receive ?
    [/cover] */
    /* FR_17_ERAY_E_INV_LPDU_IDX if its a receive LPDU */
    if (((Fr_17_Eray_ConfigPtr->
                    CfgPtr[LogIdx].LPduConfigPtr[Fr_LPduIdx].Wrhs1CfgVal >>
          IFX_ERAY_WRHS1_CFG_OFF) & IFX_ERAY_WRHS1_CFG_MSK) == 0U)
    {
      /* [cover parentID={32E12DCA-4C0B-496c-9D9C-A5458FDCA301}]
      Report DET
      [/cover] */
      (void)Det_ReportError(FR_17_ERAY_MODULE_ID, FR_17_ERAY_INSTANCE_ID,
                      FR_17_ERAY_SID_CANCELTXLPDU, FR_17_ERAY_E_INV_LPDU_IDX);

      DevError = FR_17_ERAY_E_INV_LPDU_IDX;
    }
  }

  /* [cover parentID={71730CDD-9FB5-48e7-9CEB-AB69E96DB15E}]
  Any DET Error detected from the previous checks ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    RetVal = E_OK;
  }
  else
  {
    /* [cover parentID={51A04956-D739-4fc9-B547-2C204B5A8B91}]
    Mark the return value as Error Detected
    [/cover] */
    RetVal = E_NOT_OK;
  }

  return RetVal;

}

/*******************************************************************************
** Traceability    : [cover parentID={D035812A-BCC4-4a21-94DC-9FB60B5BCCB2}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE  Std_ReturnType Fr_17_Eray_lReceiveDetCheck **
**                   (                                                        **
**                          const uint8 Fr_CtrlIdx,                           **
**                          const uint16 Fr_LPduIdx,                          **
**                          const uint8* const Fr_LSduPtr,                    **
**                          const Fr_RxLPduStatusType* const Fr_LPduStatusPtr,**
**                          const uint8* const Fr_LSduLengthPtr               **
**                   )                                                        **
**                                                                            **
** Description     : Function to check the development error conditions for   **
**                     the API Fr_17_Eray_ReceiveRxLPdu                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  NA                                                      **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Reentrant                                               **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                   Fr_LPduIdx - This index is used to uniquely identify a   **
**                                  FlexRay frame.                            **
**                   Fr_LSduPtr - This reference points to a buffer where the **
**                                  LSdu to be received shall be stored       **
**                   Fr_LPduStatusPtr - This reference points to the memory   **
**                                      location where the status of the LPdu **
**                                      shall be stored                       **
**                   Fr_LSduLengthPtr - This reference points to the memory   **
**                           location where the length of the LSdu (in bytes) **
**                           shall be stored. This length represents the      **
**                           number of bytes copied to LSduPtr.               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE  Std_ReturnType Fr_17_Eray_lReceiveDetCheck(
                             const uint8 Fr_CtrlIdx,
                             const uint16 Fr_LPduIdx,
                             const uint8* const Fr_LSduPtr,
                             const Fr_RxLPduStatusType* const Fr_LPduStatusPtr,
                             const uint8* const Fr_LSduLengthPtr
                                       )
{
  uint32 DevError;
  Std_ReturnType RetValue;
  uint8 LogIdx;

  /* [cover parentID={F882BEEB-779B-4b83-9F03-BB34D258DA12}]
  Check for Fr Initialization
  [/cover] */
  /* FR_17_ERAY_E_INIT_FAILED */
  DevError = Fr_17_Eray_lDetCheckNoInit(FR_17_ERAY_SID_RECEIVERXLPDU);

  /* [cover parentID={6BEB2D70-52E3-459e-B034-4E99E0D89F10}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={D0EDC053-F34C-40e3-BB10-0D13BB271DE1}]
    Check for validity of controller Index
    [/cover] */
    /* FR_17_ERAY_E_INV_CTRL_IDX */
    DevError = Fr_17_Eray_lDetCheckInvCtrlIdx(Fr_CtrlIdx,
                                                FR_17_ERAY_SID_RECEIVERXLPDU);
  }

  /* [cover parentID={3EC2B54F-F8AA-4261-AF9D-01FA284A8D1D}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={EEC12470-6CD4-4bd5-9656-3B23AE249633}]
    Check the validity of the LPdu index
    [/cover] */
    /* FR_17_ERAY_E_INV_LPDU_IDX */
    DevError = Fr_17_Eray_lDetCheckInvLPduIdx(Fr_CtrlIdx,Fr_LPduIdx,
                                                FR_17_ERAY_SID_RECEIVERXLPDU);
  }

  /*
    Invalid LPduIdx, avoid array out of bound access for
     Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].LPduConfigPtr[Fr_LPduIdx]
  */
  /* [cover parentID={769A2850-8706-4f4d-98C9-B8F3411A3D65}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {

    LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];

    /* [cover parentID={894E827A-2263-4e5e-8B07-A7C76D84D49C}]
    Is the direction of LPdu configured as transmit ?
    [/cover] */
    if (((Fr_17_Eray_ConfigPtr->
                   CfgPtr[LogIdx].LPduConfigPtr[Fr_LPduIdx].Wrhs1CfgVal >>
           IFX_ERAY_WRHS1_CFG_OFF) & IFX_ERAY_WRHS1_CFG_MSK) == 1U)
    {
      /* [cover parentID={64043729-D10E-43b2-A82F-8F257339C4F4}]
      Report DET
      [/cover] */
      (void)Det_ReportError(FR_17_ERAY_MODULE_ID, FR_17_ERAY_INSTANCE_ID,
                      FR_17_ERAY_SID_RECEIVERXLPDU, FR_17_ERAY_E_INV_LPDU_IDX);

      DevError = FR_17_ERAY_E_INV_LPDU_IDX;
    }

  }

  /* [cover parentID={7DEE16F1-E805-44c6-80DD-C9CCD1FBBAE1}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={0453374F-5A56-4fc2-9254-2B92F39EFAAF}]
    Check whether the LSdu pointer is NULL
    [/cover] */
    /* FR_17_ERAY_E_PARAM_POINTER */
    DevError = Fr_17_Eray_lDetCheckInvPointer(Fr_LSduPtr,
                                               FR_17_ERAY_SID_RECEIVERXLPDU);
  }

  /* [cover parentID={D7C950BB-E5F3-490c-AC41-6E1253CF0A2B}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={0B789D48-5665-4f79-9F34-5BE1E0F674C9}]
    Check whether the LPdu Status pointer is NULL
    [/cover] */
    /* FR_17_ERAY_E_PARAM_POINTER */
    DevError = Fr_17_Eray_lDetCheckInvPointer(
                  Fr_LPduStatusPtr, FR_17_ERAY_SID_RECEIVERXLPDU);
  }

  /* [cover parentID={94011396-C502-42d2-9C78-3F6E7591B7E6}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={031DD587-55FC-47e9-B310-2746FC8F38A2}]
    Check whether the LSdu Length pointer is NULL
    [/cover] */
    /* FR_17_ERAY_E_PARAM_POINTER */
    DevError = Fr_17_Eray_lDetCheckInvPointer(
                  Fr_LSduLengthPtr, FR_17_ERAY_SID_RECEIVERXLPDU);
  }

  /* Return if a development error detected */
  /* [cover parentID={C3A75C7D-2449-427f-ABA8-E0F11062DCAE}]
  Any DET Error detected from the previous checks ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    RetValue = E_OK;
  }
  else
  {
    /* [cover parentID={39077C30-7668-4142-B6DD-13593E31A7AC}]
    Mark the return value as Error Detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  return RetValue;
}

/*******************************************************************************
** Traceability    : [cover parentID={9AB66F46-DED1-46e0-89E7-1085694D400E}]  **
**                                                                            **
** Syntax          :LOCAL_INLINE Std_ReturnType Fr_17_Eray_lGetSyncFrameList  **
**                           (                                                **
**                                const uint8 Fr_CtrlIdx,                     **
**                                const uint8 Fr_ListSize,                    **
**                                const uint16* const Fr_ChannelAEvenListPtr, **
**                                const uint16* const Fr_ChannelBEvenListPtr, **
**                                const uint16* const Fr_ChannelAOddListPtr,  **
**                                const uint16* const Fr_ChannelBOddListPtr   **
**                           )                                                **
**                                                                            **
** Description     : Checks for Fr_17_Eray_GetSyncFrameList DET               **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  NA                                                      **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Reentrant                                               **
**                                                                            **
** Parameters (in) :                                                          **
**  Fr_CtrlIdx - Index of FlexRay CC within the context of the FlexRay Driver **
**  Fr_ListSize - Size of the arrays passed via parameters:                   **
**      Fr_ChannelAEvenListPtr, Fr_ChannelBEvenListPtr,                       **
**      Fr_ChannelAOddListPtr,  Fr_ChannelBOddListPtr.                        **
**      The service must ensure to not write more entries into those arrays   **
**      than granted by this parameter.                                       **
**  Fr_ChannelAEvenListPtr - Address the list of syncframes on channel        **
**      A within the even communication cycle is written to. The exact number **
**      of elements written to the list is limited by parameter Fr_ListSize.  **
**      Unused list elements are filled with the value '0' to indicate that   **
**      no more syncframe has been seen.                                      **
**  Fr_ChannelBEvenListPtr - Address the list of syncframes on channel B      **
**      within the even communication cycle is written to. The exact number   **
**      of elements written to the list is limited by parameter Fr_ListSize.  **
**      Unused list elements are filled with the value '0' to indicate that   **
**      no more syncframe has been seen.                                      **
**  Fr_ChannelAOddListPtr - Address the list of syncframes on channel A       **
**      within the odd communication cycle is written to. The exact number of **
**      elements written to the list is limited by parameter Fr_ListSize.     **
**      Unused list elements are filled with the value '0' to indicate that   **
**      no more syncframe has been seen.                                      **
**  Fr_ChannelBOddListPtr - Address the list of syncframes on channel B       **
**      within the odd communication cycle is written to. The exact number    **
**      of elements written to the list is limited by parameter Fr_ListSize.  **
**      Unused list elements are filled with the value '0' to indicate that   **
**      no more syncframe has been seen.                                      **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fr_17_Eray_lGetSyncFrameList(
                                    const uint8 Fr_CtrlIdx,
                                    const uint8 Fr_ListSize,
                                    const uint16* const Fr_ChannelAEvenListPtr,
                                    const uint16* const Fr_ChannelBEvenListPtr,
                                    const uint16* const Fr_ChannelAOddListPtr,
                                    const uint16* const Fr_ChannelBOddListPtr
                                                        )
{
  uint32 DevError;
  Std_ReturnType RetValue;

  /* [cover parentID={2746B9ED-E803-493c-BBCF-AB25578FFA36}]
  Check for Fr Initialization
  [/cover] */
  /* FR_17_ERAY_E_INIT_FAILED */
  DevError = Fr_17_Eray_lDetCheckNoInit(FR_17_ERAY_SID_GETSYNCFRAMELIST);

  /* [cover parentID={B317A114-5105-411c-B5EA-1ECA3FB23904}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={B5018ED1-84C0-4f28-AE37-5447F9F35E33}]
    Check the validity of controller Index
    [/cover] */
    /* FR_17_ERAY_E_INV_CTRL_IDX */
    DevError = Fr_17_Eray_lDetCheckInvCtrlIdx(Fr_CtrlIdx,
                                      FR_17_ERAY_SID_GETSYNCFRAMELIST);
  }

  /* [cover parentID={F5B9005E-018D-494e-8875-C85E4EC426B4}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={B1760E8A-D1B1-4fac-BFD1-03AC40370ABC}]
    Is the List size parameter an invalid value ( > 15) ?
    [/cover] */
    if (Fr_ListSize > FR_17_ERAY_MAX_LIST_SIZE)
    {
      /* [cover parentID={AF6A4157-ECB7-4f73-877F-AF3EFE3297B2}]
      Report DET
      [/cover] */
      (void)Det_ReportError(FR_17_ERAY_MODULE_ID, FR_17_ERAY_INSTANCE_ID,
       FR_17_ERAY_SID_GETSYNCFRAMELIST,FR_17_ERAY_E_INV_FRAMELIST_SIZE);

      DevError = FR_17_ERAY_SID_GETSYNCFRAMELIST;
    }
  }

  /* [cover parentID={E8128DD3-61A9-4c40-A1EF-03AC875E6042}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={47265140-897F-4d4c-B628-05CC2A2BC63B}]
    Is any of the Channel list pointers a NULL pointer ?
    [/cover] */
    /* FR_17_ERAY_E_PARAM_POINTER */
    if ((Fr_ChannelAEvenListPtr == NULL_PTR) ||
        (Fr_ChannelBEvenListPtr == NULL_PTR) ||
        (Fr_ChannelAOddListPtr == NULL_PTR) ||
        (Fr_ChannelBOddListPtr == NULL_PTR))
    {
      /* [cover parentID={753B8D81-48A4-456b-8B08-654D5881A6AB}]
      Report DET
      [/cover] */
      (void)Det_ReportError(FR_17_ERAY_MODULE_ID, FR_17_ERAY_INSTANCE_ID,
                      FR_17_ERAY_SID_GETSYNCFRAMELIST,
                      FR_17_ERAY_E_PARAM_POINTER);

      DevError = FR_17_ERAY_E_PARAM_POINTER;
    }
  }

  /* Return if a development error detected */
  /* [cover parentID={3B1DD628-DC3D-494a-B08C-82C99912E5F2}]
  Any DET Error detected from the previous checks ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    RetValue = E_OK;
  }
  else
  {
    /* [cover parentID={7F794EC3-CCF8-4503-996D-F12D22D56AF8}]
    Mark the return value as Error Detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  return RetValue;

}

/*******************************************************************************
** Traceability    : [cover parentID={C33CE6B4-B7B9-414c-A12D-668FAD1DB5D2}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE uint32 Fr_17_Eray_lDetCheckSetAbsoluteTimer(**
**                                             const uint8 Fr_CtrlIdx,        **
**                                             const uint8 Fr_AbsTimerIdx,    **
**                                             const uint8 Fr_Cycle,          **
**                                             const uint16 Fr_Offset,        **
**                                             const uint8 ServiceId)         **
**                                                                            **
**                                                                            **
**                                                                            **
** Service ID      :  NA                                                      **
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
**                  ServiceId - ID of API service in which error is detected  **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  FR_17_ERAY_E_DET_NO_ERR(0): No DET reported             **
**                   FR_17_ERAY_E_INIT_FAILED: Fr initialization failed       **
**                   FR_17_ERAY_E_INV_CTRL_IDX: Invalid Controller index      **
**                   FR_17_ERAY_E_INV_OFFSET: Fr Offset parameter Invalid     **
**                   FR_17_ERAY_E_INV_TIMER_IDX: Timer Index is Invalid       **
**                   FR_17_ERAY_E_INV_CYCLE : Fr Cycle parameter Invalid      **
**                                                                            **
** Description     :  Checks DET dring setting absolute timer.                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Fr_17_Eray_lDetCheckSetAbsoluteTimer(
                                             const uint8 Fr_CtrlIdx,
                                             const uint8 Fr_AbsTimerIdx,
                                             const uint8 Fr_Cycle,
                                             const uint16 Fr_Offset,
                                             const uint8 ServiceId)
{
  uint32 DevError;

  /* [cover parentID={A5B58967-B02F-4703-A926-1C9604D8F1CA}]
  Check for Fr Initialization
  [/cover] */
  /* FR_17_ERAY_E_INIT_FAILED */
  DevError = Fr_17_Eray_lDetCheckNoInit(ServiceId);

  /* [cover parentID={DB377464-75A1-42d8-8E65-48A6EFCBA116}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={15FF8359-49A7-47ea-A21E-A866582100D5}]
    Check for validity of controller index
    [/cover] */
    /* FR_17_ERAY_E_INV_CTRL_IDX */
    DevError = Fr_17_Eray_lDetCheckInvCtrlIdx(Fr_CtrlIdx,
                                             ServiceId);
  }

  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={0465165B-FA34-4e13-818E-A80DF4560DC0}]
    Is there No DET Error due to the previous check ? AND
    Is the Fr Offset parameter Invalid ?
    [/cover] */
    /* FR_17_ERAY_E_INV_OFFSET */
    /* Note: Valid Offset is 0 .. (gMacroPerCycle - 1) */
    if (Fr_Offset >= ERAY[Fr_CtrlIdx]->GTUC02.B.MPC)
    {
      /* [cover parentID={60130F1E-1D23-47ad-A5E5-F0079AC7C30E}]
      Report DET
      [/cover] */
      (void)Det_ReportError(FR_17_ERAY_MODULE_ID, FR_17_ERAY_INSTANCE_ID,
                    ServiceId, FR_17_ERAY_E_INV_OFFSET);
      DevError = FR_17_ERAY_E_INV_OFFSET;
    }
  }

  /* [cover parentID={100366E4-3FB1-4ce8-9E0B-4358810457E5}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={02ECE2E3-05CB-4532-B86F-596B9D708833}]
    Check the validity of timer index
    [/cover] */
    /* FR_17_ERAY_E_INV_TIMER_IDX */
    DevError = Fr_17_Eray_lDetCheckInvTimerIdx(Fr_AbsTimerIdx,
                                             ServiceId);
  }

  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={6D5D99E1-FD88-4b2a-8243-6BCC36443BE6}]
    Is there No DET Error due to the previous check ? AND
    Is Fr Cycle parameter invalid ?
    [/cover] */
    /* FR_17_ERAY_E_INV_CYCLE */
    if (Fr_Cycle > (uint8)FR_17_ERAY_MAX_CYCLE_INDEX )
    {
      /* [cover parentID={1FA156A2-2F6F-4a87-898B-824CC159263C}]
      Report DET
      [/cover] */
      (void)Det_ReportError(FR_17_ERAY_MODULE_ID, FR_17_ERAY_INSTANCE_ID,
                    ServiceId, FR_17_ERAY_E_INV_CYCLE);
      DevError = FR_17_ERAY_E_INV_CYCLE;
    }
  }

  return DevError;
}
#endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */

#if(((MCAL_AR_VERSION == MCAL_AR_422) &&\
          (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON))\
             || (FR_17_ERAY_RUNTIME_ERROR_DETECT == STD_ON))
/*******************************************************************************
** Traceability    : [cover parentID={5A82097D-631C-4ea0-BDE5-994FE87E7272}]  **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_lDetCheckInvPOCState           **
**                        (const uint8 Fr_CtrlIdx, const uint8 ExpectedState, **
**                                                 const uint8 ServiceId)     **
**                                                                            **
** Description     : Function to check whether the POC state is same as       **
**                    expected state or not. Used only by APIs that check     **
**                    against one expected state. It can't be used to check   **
**                    for multiple states for example : to check if CC is     **
**                    synchronized to FlexRay global time because it involves **
**                    checking if CC is in either NORMAL PASSIVE or ACTIVE    **
**                    state.                                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant for the same device                        **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver                          **
**                   ExpectedState - POC state to which the HW state is       **
**                                   evaluated                                **
**                   ServiceId - Service Index of FlexRay driver API          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fr_17_Eray_lDetCheckInvPOCState(
                                                     const uint8 Fr_CtrlIdx,
                                                     const uint8 ExpectedState,
                                                     const uint8 ServiceId
                                                   )
{
  Std_ReturnType RetValue;

  RetValue = E_OK;

  /* Fr_17_Eray_Init API was called */
  /* [cover parentID={D0B2B64B-06DE-41b8-9D1C-259C72D419B0}]
  Is the actual CC POC State not same as the expected state ?
  [/cover] */
  if (ERAY[Fr_CtrlIdx]->CCSV.B.POCS != (uint32)ExpectedState)
  {
    /* [cover parentID={2FA499EA-5257-4bb0-8DE1-47F58C7C2FA7}]
    Report DET
    [/cover] */
    Fr_17_Eray_lReportRuntimeDetError(ServiceId,
                                     FR_17_ERAY_E_INV_POCSTATE);

    RetValue = E_NOT_OK;
  }

  return RetValue;
}
#endif /*  #if(((MCAL_AR_VERSION == MCAL_AR_422) &&\
          (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON))\
             || (FR_17_ERAY_RUNTIME_ERROR_DETECT == STD_ON))*/
/*******************************************************************************
** Traceability    : [cover parentID={3560EDA8-E8DE-4e05-AE66-C3EBCF8DE7E1}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType                              **
                     Fr_17_Eray_lClrFlagChangeState (const uint8 Fr_CtrlIdx)  **
**                                                                            **
** Description     : Function to clear the Error flags, status flags and      **
**                     then change the POC state to CONFIG.                   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  NA                                                      **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fr_17_Eray_lClrFlagChangeState
                                                    (const uint8 Fr_CtrlIdx)
{
  uint32 ErrorCount;
  Std_ReturnType RetValue;

  ErrorCount = (uint32)FR_17_ERAY_DEC_ZERO;

  /* [cover parentID={9856BB25-7165-4f15-B001-DB245B002F39}]
  Clear all the Error flags, Status flags, Error service request flags,
   Status service request flags, Message handler status flags
  [/cover] */
  /* Clear all the Error flags */
  ERAY[Fr_CtrlIdx]->EIR.U   = FR_17_ERAY_CLEAR_EIR_EIER_FLAGS;
  /* Clear all the Status flags */
  ERAY[Fr_CtrlIdx]->SIR.U   = FR_17_ERAY_CLEAR_SIR_SIER_FLAGS;
  /* Clear the Error Service Request Register bits. */
  ERAY[Fr_CtrlIdx]->EIER.U  = FR_17_ERAY_CLEAR_EIR_EIER_FLAGS;
  /* Clear the Status Service Request Register bits.  */
  ERAY[Fr_CtrlIdx]->SIER.U  = FR_17_ERAY_CLEAR_SIR_SIER_FLAGS;
  /* Disable message handler Status.*/
  ERAY[Fr_CtrlIdx]->MHDS.U  = FR_17_ERAY_CLEAR_MHDS_FLAGS;

  /* Switch CC into 'POC:config' (from any other POCState). */
  /* [cover parentID={CE9B10F9-248F-48f5-AC3C-E944C6B3526B}]
  Is the POC status in 'CONFIG' state ?
  [/cover] */
  if (ERAY[Fr_CtrlIdx]->CCSV.B.POCS != (uint32)FR_17_ERAY_POCS_CONFIG)
  {
    /* Switch from any state to POC:HALT state, CHI Command is FREEZE */
    ErrorCount +=
        Fr_17_Eray_lChangePOCState(Fr_CtrlIdx,FR_17_ERAY_CHI_CMD_FREEZE);

    ErrorCount +=
      Fr_17_Eray_lWaitTillPOCChange(Fr_CtrlIdx,FR_17_ERAY_POCS_HALT);

    /* POC:HALT to POC:DEFAULT_CONFIG config, CHI Command is CONFIG */
    ErrorCount +=
        Fr_17_Eray_lChangePOCState(Fr_CtrlIdx,FR_17_ERAY_CHI_CMD_CONFIG);

    ErrorCount += Fr_17_Eray_lWaitTillPOCChange(Fr_CtrlIdx,
                                             FR_17_ERAY_POCS_DEFAULT_CONFIG);

    /* POC:DEFAULT_CONFIG to POC:CONFIG, CHI Command is CONFIG */
    /* [cover parentID={B409A632-DC46-49ea-B615-4C0781594179}]
    Provide the CHI command CONFIG to switch POC to CONFIG state
    [/cover] */
    ErrorCount +=
        Fr_17_Eray_lChangePOCState(Fr_CtrlIdx,FR_17_ERAY_CHI_CMD_CONFIG);

    /* [cover parentID={A7D5E1DA-388A-49c3-B235-CC24B57FC7CF}]
    Wait (until timeout) for the change in POC state to CONFIG
    [/cover] */
    ErrorCount +=
         Fr_17_Eray_lWaitTillPOCChange(Fr_CtrlIdx,FR_17_ERAY_POCS_CONFIG);

    /* [cover parentID={A7B4A0A5-0A98-4269-AEF9-BBF4134F0D92}]
    Did any Error/ timeout error occur during change in POC state ?
    [/cover] */
    if (ErrorCount != (uint32)FR_17_ERAY_DEC_ZERO)
    {
      /* [cover parentID={4BA3544E-A95C-4a78-AA41-76239B42B651}]
      Mark the return value as Error Detected
      [/cover] */
      /* Command not accepted or POC state change did not happen -->
         Time out-->Production error */
      RetValue = E_NOT_OK;
    }
    else
    {
      RetValue = E_OK;
    }
  }
  else
  {
    RetValue = E_OK;
  }

  return RetValue;
}

/*******************************************************************************
** Traceability    : [cover parentID={331EB409-3F2C-4d18-BD7C-CECE07EBAE19}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType                              **
                     Fr_17_Eray_lConfigMessageBuffer                          **
                     (                                                        **
                       const uint8 Fr_CtrlIdx,                                **
                       const uint8 LogIndex                                   **
                     )                                                        **
**                                                                            **
** Description     : Function to configure the message buffers during         **
**                     initialization.                                        **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  NA                                                      **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                   LogIndex - Logical index of the communication controller **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fr_17_Eray_lConfigMessageBuffer
                         (const uint8 Fr_CtrlIdx, const uint8 LogIndex)
{
  const Fr_17_Eray_LPduConfigType *LPduCfgPtr;
  uint32 ErrorCount;
  uint16 LpduId;
  uint8 MsgBuffIdx;
  Std_ReturnType RetValue;

  /* [cover parentID={6B4D6812-872C-4965-AFF3-5DA0BB6A550B}]
  FIFO configured
  [/cover] */
  #if (FR_17_ERAY_FIFO_CONFIGURED == STD_ON)
  const Fr_17_Eray_RxFifoConfigType *FifoCfgPtr;
  uint8 FifoBuffIdx;
  uint8 FifoDepth;
  uint8 FifoHSWriteCnt;

  FifoDepth = FR_17_ERAY_DEC_ZERO;
  FifoHSWriteCnt = FR_17_ERAY_DEC_ZERO;
  FifoBuffIdx = FR_17_ERAY_DEC_ZERO;

  FifoCfgPtr = Fr_17_Eray_ConfigPtr->CfgPtr[LogIndex].RxFifoConfigPtr;

  /* If the FIFO pointer is not Null, then get the depth of FIFO */
  /* [cover parentID={48397CF0-B774-4557-8ABD-8277369A931E}]
  Is the FIFO configured for this ctrl index ?
  [/cover] */
  if (FifoCfgPtr != NULL_PTR)
  {
    /* [cover parentID={D95364EA-BBA1-41b1-A7CB-4D9A60FF2610}]
    Get the configured value of the FIFO depth
    [/cover] */
    FifoDepth = FifoCfgPtr->FrFifoDepth;

    FifoBuffIdx = Fr_17_Eray_ConfigPtr->CfgPtr[LogIndex].MsgBuffCountMax -
                                                               FifoDepth;
  }
  #endif /* (FR_17_ERAY_FIFO_CONFIGURED == STD_ON) */

  RetValue = E_OK;
  ErrorCount = (uint32)FR_17_ERAY_DEC_ZERO;

  /* [cover parentID={7DDE3C26-01C1-4c49-8D7B-BFADDE87C85E}]
  Configure Message Buffers
  [/cover] */
  for(MsgBuffIdx = FR_17_ERAY_DEC_ZERO; MsgBuffIdx <
      (uint32)Fr_17_Eray_ConfigPtr->CfgPtr[LogIndex].MsgBuffCountMax;
       MsgBuffIdx++)
  {
    LpduId = Fr_17_Eray_MsgBuff2LPduIdxPtr[Fr_CtrlIdx][MsgBuffIdx];
    /*  Check if input buffer is busy with another transfer
        a. Wait until it becomes free or a time out happens
        b. If time out happens, report Production Error to Mcal_Wrapper */
    ErrorCount += Fr_17_Eray_lInputBufBsyHost(Fr_CtrlIdx);

    /* [cover parentID={51690072-0E68-4f09-ABFB-2CEB88AFF361}]
    Is the input host buffer in busy state within timeout period ?
    [/cover] */
    if (ErrorCount != (uint32)FR_17_ERAY_DEC_ZERO)
    {
      /* [cover parentID={FE5A37CD-0832-4ed3-A8CA-B1E66B82721C}]
      Mark the status as Error Detected and Break
      [/cover] */
      /* Command not accepted or POC state change did not happen -->
         Time out--> Production error */
      RetValue = E_NOT_OK;
      break;
    }
    else
    {
      /* [cover parentID={9E00B5A6-A1A0-4ace-B791-0444445A7059}]
      Mark the status as No Error Detected
      [/cover] */
      RetValue = E_OK;
    }

    /* Write header section values into input buffer */
    ERAY[Fr_CtrlIdx]->WRHS2.U =
        (Fr_17_Eray_ConfigPtr->CfgPtr[LogIndex].LPduConfigPtr)[
                     LpduId].Wrhs2CfgVal & (uint32)FR_17_ERAY_WRHS2_MASK;

    ERAY[Fr_CtrlIdx]->WRHS1.U =
    (Fr_17_Eray_ConfigPtr->CfgPtr[LogIndex].LPduConfigPtr)[LpduId].Wrhs1CfgVal;

    /* [cover parentID={FD0B0848-B5F1-466d-A4BD-3217DE2AEE69}]
    FIFO is Configured
    [/cover] */
    #if (FR_17_ERAY_FIFO_CONFIGURED == STD_ON)
    /* [cover parentID={C6CD76D1-41A4-4545-AB54-5D80E34FA9B4}]
    Is the LPdu index part of the FIFO ?
    [/cover] */
    if(Fr_17_Eray_ConfigPtr->CfgPtr[LogIndex].LPduIdx2MsgBuffIdxPtr[LpduId]==
                                             (uint8)FR_17_ERAY_MSGBUFF_UNUSED)
    {
      /* [cover parentID={AE0553A0-FBFC-43c3-80C7-3DA4D829666C}]
      Is (FIFO depth > 0) and (number of FIFO buffer headers written is less
      than the calculated FIFO depth)
      [/cover] */
      if ((FifoDepth > FR_17_ERAY_DEC_ZERO) && (FifoHSWriteCnt < FifoDepth))
      {
        /* [cover parentID={9BC7AAF8-CD42-4214-AA53-D606F972DA84}]
        Update write header sections 3 with the data pointer offset of
        First FIFO buffer [/cover] */
        ERAY[Fr_CtrlIdx]->WRHS3.U = Fr_17_Eray_ConfigPtr->
                      CfgPtr[LogIndex].DataPointerOffsetPtr[FifoBuffIdx];

        /* Increment number of FIFO buffer headers written and
        the index of the FIFO buffer */
        FifoHSWriteCnt += FR_17_ERAY_DEC_ONE;
        FifoBuffIdx += FR_17_ERAY_DEC_ONE;
      }
    }
    else
    #endif /* (FR_17_ERAY_FIFO_CONFIGURED == STD_ON) */
    {
      ERAY[Fr_CtrlIdx]->WRHS3.U =
       Fr_17_Eray_ConfigPtr->CfgPtr[LogIndex].DataPointerOffsetPtr[MsgBuffIdx];
    }

    /* Select header section for writing into message buffer */
    ERAY[Fr_CtrlIdx]->IBCM.U = FR_17_ERAY_TRANSFER_HEADER;

    /* Start the buffer transfer */
    ERAY[Fr_CtrlIdx]->IBCR.B.IBRH = MsgBuffIdx;

    /*  Check if input buffer is busy with another transfer
        a. Wait until it becomes free or a time out happens
        b. If time out happens, report Production Error to Mcal_Wrapper */
    ErrorCount += Fr_17_Eray_lInputBufBsyHost(Fr_CtrlIdx);
  }

  /*----- Disable all LPdus which are dynamically reconfigurable ---------*/
  /* [cover parentID={32F3E28F-252C-42b1-A8E6-B71929FA78FC}]
  Any Error detected in buffer configuration ?
  [/cover] */
  if(RetValue == E_OK)
  {
    /* Store the LPDU configuration */
    LPduCfgPtr = Fr_17_Eray_ConfigPtr->CfgPtr[LogIndex].LPduConfigPtr;

    /* Check if Lpdu is dynamically reconfigurable */
    /* [cover parentID={BA6328DC-A5E8-457a-8ACA-6877ABE116C4}]
    Disable dynamically reconfigurable LPdus
    [/cover] */
    for (LpduId = FR_17_ERAY_DEC_ZERO; LpduId <
                   Fr_17_Eray_ConfigPtr->CfgPtr[LogIndex].LPduCount; LpduId++)
    {
      /* [cover parentID={F0113FCA-7F10-47fc-9569-DF418080A088}]
      Is the LPdu Reconfigurable ?
      [/cover] */
      if (LPduCfgPtr[LpduId].LpduReconfigurable ==
                                     (uint8)FR_17_ERAY_LPDU_RECONFIGURABLE)
      {
        /* [cover parentID={177F8D0F-025D-4bb3-A763-B3B2624B14C4}]
        Determine the Mesage Buffer Index that corresponds to the LPdu index
        [/cover] */
        /* Figure out the message buffer corresponding to LPduIdx */
        MsgBuffIdx =
        Fr_17_Eray_ConfigPtr->CfgPtr[LogIndex].LPduIdx2MsgBuffIdxPtr[LpduId];

        /* [cover parentID={922DCEBE-CB65-4598-A132-1D8D5A82F344}]
        Update the write header section 1 - Channel Filter Control A and B
        bits to zero to stop transmission and receive buffer will ignore
        frames
        [/cover] */
        /* Set Channel Filter Control A and Channel Filter Control B bits to
           zero,to stop transmission and receive buffer will ignore frames */
        ERAY[Fr_CtrlIdx]->WRHS1.B.CHA = FR_17_ERAY_DEC_ZERO;
        ERAY[Fr_CtrlIdx]->WRHS1.B.CHB = FR_17_ERAY_DEC_ZERO;

        /* Select header section for writing into message buffer */
        ERAY[Fr_CtrlIdx]->IBCM.U = FR_17_ERAY_TRANSFER_HEADER;

        /* [cover parentID={B1AF3B71-8EC4-4d98-BB3E-28A07FFEDC51}]
        Initiate the transfer of header section from the input host buffer
        to the message RAM
        [/cover] */
        /* Start the buffer transfer */
        ERAY[Fr_CtrlIdx]->IBCR.B.IBRH = MsgBuffIdx;

        /* Check if input buffer is busy with another transfer
           a. Wait until it becomes free or a time out happens
           b. If time out happens, report Production Error to Mcal_Wrapper */
        ErrorCount += Fr_17_Eray_lInputBufBsyHost(Fr_CtrlIdx);
      }
    }

    /* [cover parentID={0774FCD2-6E6F-4c14-9F4F-F45C28546F8D}]
    Any timeout error detected during LPdu disabling ?
    [/cover] */
    if (ErrorCount != (uint32)FR_17_ERAY_DEC_ZERO)
    {
      /* [cover parentID={31A30A94-18A6-4a01-BA73-5D53244EDB1F}]
      Mark the return value as Error Detected
      [/cover] */
      /* Command not accepted or POC state change did not happen->Time out->
          Production error */
      RetValue = E_NOT_OK;
    }
  }

  return RetValue;
}

/*******************************************************************************
** Traceability    : [cover parentID={EA5A3274-0FDB-412d-91D2-0D427DFC6ADA}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType                              **
                     Fr_17_Eray_lUpdateDyLSduLength                           **
                     (                                                        **
                       const uint8 Fr_CtrlIdx,                                **
                       const uint8 LogIndex,                                  **
                       const uint16 Fr_LPduIdx,                               **
                       const uint8 Fr_LSduLength                              **
                     )                                                        **
**                                                                            **
** Description     : Function to update the dynamic LSdu length               **
**                    (in the header section) in case the parameter to allow  **
**                     dynamic LSdu length is enabled for the LPdu.           **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  NA                                                      **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                   LogIndex - Logical index of the communication controller **
**                   Fr_LPduIdx - This index is used to uniquely identify a   **
**                                FlexRay frame                               **
**                   Fr_LSduLength - Determines the length of the data        **
**                                   (in bytes) to be transmitted.            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fr_17_Eray_lUpdateDyLSduLength
                         (const uint8 Fr_CtrlIdx, const uint8 LogIndex,
                          const uint16 Fr_LPduIdx, const uint8 Fr_LSduLength)
{
  uint32 ConfiguredSlotId;
  uint32 HeaderCRC;
  uint32 HeaderPlc;
  uint32 ErrCount;
  uint8 LSduLengthIn16BitWords;
  uint8 MsgBuffIdx;
  Std_ReturnType RetValue;

  /* [cover parentID={754CD1DF-7E12-4a3e-88E3-E59D2359F86E}]
  Determine the Slot ID that corresponds to the Frame ID
  [/cover] */
  /* Get the SlotId of the LPdu */
  ConfiguredSlotId =
    (Fr_17_Eray_ConfigPtr->
     CfgPtr[LogIndex].LPduConfigPtr)[Fr_LPduIdx].Wrhs1CfgVal
                                       & IFX_ERAY_WRHS1_FID_MSK;

  /*Get LSduLength in 2 byte words,add 1 for length
  (for rounding)not multiple of 2 */
  LSduLengthIn16BitWords = (uint8)((Fr_LSduLength + 1U) >> 1U);

  /*  Re-Calculate header CRC for new LSduLength  */
  /* [cover parentID={FCB38A9F-2E82-4fdf-85A6-A90AC54449AB}]
  Calculate the header CRC
  [/cover] */
  HeaderCRC = Fr_17_Eray_lHeaderCRC(ConfiguredSlotId, LSduLengthIn16BitWords);

  /* Write header section values into input buffer */
  HeaderPlc = ((uint32)LSduLengthIn16BitWords << FR_17_ERAY_BIT_POS_PLC);

  MsgBuffIdx = Fr_17_Eray_ConfigPtr->
        CfgPtr[LogIndex].LPduIdx2MsgBuffIdxPtr[Fr_LPduIdx];

  /* [cover parentID={C60976C4-EEF4-41cf-97FE-ADA418FF07C2}]
  Update the write header sections 2 with the computed header CRC
  and payload length
  [/cover] */
  ERAY[Fr_CtrlIdx]->WRHS2.U = (uint32)(HeaderPlc|HeaderCRC);

  ERAY[Fr_CtrlIdx]->WRHS1.U =
  (Fr_17_Eray_ConfigPtr->CfgPtr[LogIndex].LPduConfigPtr)[
            Fr_17_Eray_MsgBuff2LPduIdxPtr[Fr_CtrlIdx][MsgBuffIdx]].Wrhs1CfgVal;

  ERAY[Fr_CtrlIdx]->WRHS3.U =
           Fr_17_Eray_ConfigPtr->
           CfgPtr[LogIndex].DataPointerOffsetPtr[MsgBuffIdx];

  /* Select header section for writing into message buffer */
  ERAY[Fr_CtrlIdx]->IBCM.U = FR_17_ERAY_TRANSFER_HEADER;

  /* Start the buffer transfer */
  ERAY[Fr_CtrlIdx]->IBCR.B.IBRH = MsgBuffIdx;

  /*  Check if input buffer is busy with another transfer
      a. Wait until it becomes free or a time out happens
      b. If time out happens, report Production Error to Mcal_Wrapper     */
  ErrCount = Fr_17_Eray_lInputBufBsyHost(Fr_CtrlIdx);

  /* [cover parentID={3007E1DB-ECE0-4ace-A650-DA98D2E030E5}]
  Is the input host buffer in busy state within timeout period ?
  [/cover] */
  if(ErrCount != 0U)
  {
    /* [cover parentID={23F20DF7-E34C-4484-B5DF-AC1676DF5A71}]
    Mark the return value as Error Detected
    [/cover] */
    RetValue = E_NOT_OK;
  }
  else
  {
    RetValue = E_OK;
  }

  return RetValue;
}

/*******************************************************************************
** Traceability    : [cover parentID={AB03F179-4655-47ff-A896-00C4A8E78394}]  **
**                                                                            **
** Syntax          : LOCAL_INLINE Std_ReturnType                              **
                     Fr_17_Eray_lUpdateTransmitData                           **
                     (                                                        **
                       const uint8 Fr_CtrlIdx,                                **
                       const uint16 Fr_LPduIdx,                               **
                       const uint8 * const Fr_LSduPtr,                        **
                       const uint8 Fr_LSduLength,                             **
                       const uint8 PlcBytes                                   **
                     )                                                        **
**                                                                            **
** Description     : Function to update the data section within the           **
**                    the message buffer for the requested LPdu transmission. **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  NA                                                      **
**                                                                            **
** Sync/Async      :  Asynchronous                                            **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                   Fr_LPduIdx - This index is used to uniquely identify a   **
**                                 FlexRay frame.                             **
**                   Fr_LSduPtr - This reference points to a buffer where the **
**                                 assembled LSdu to be transmitted within    **
**                                 this LPdu is stored at.                    **
**                   Fr_LSduLength - Determines the length of the data        **
**                                   (in bytes) to be transmitted.            **
**                   PlcBytes - Configured length of the data (in bytes)      **
**                                 to be transmitted                          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fr_17_Eray_lUpdateTransmitData
                    (const uint8 Fr_CtrlIdx, const uint16 Fr_LPduIdx,
                     const uint8 * const Fr_LSduPtr, const uint8 Fr_LSduLength,
                     const uint8 PlcBytes)
{
  uint32 TempLsduPtr[FR_17_ERAY_MAX_LSDU_LENGTH];
  uint32 ErrCount;
  uint8 ByteIndex;
  uint8 RegCount;
  uint8 RegIndex;
  uint8 CountDiv;
  uint8 LogIdx;
  uint8 MsgBuffIdx;
  uint8 AllowDynamicLSduLengthFlag;
  Std_ReturnType RetValue;

  LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];

  /* Figure out the message buffer corresponding to LPduIdx */
  MsgBuffIdx =
     Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].LPduIdx2MsgBuffIdxPtr[Fr_LPduIdx];

  /* Allow Dynamic LPdu Length reduction */
  /* [cover parentID={7BF9AE4C-5B9B-41d3-872F-0F266CD6024B}]
  Determine whether the LPdu is configured to support dynamic LSdu length
  [/cover] */
  AllowDynamicLSduLengthFlag = (uint8)((Fr_17_Eray_ConfigPtr->
         CfgPtr[LogIdx].LPduConfigPtr[Fr_LPduIdx].Wrhs2CfgVal>>
         FR_17_ERAY_WRHS2_ALLOWDYN_OFFSET) & FR_17_ERAY_WRHS2_ALLOWDYN_MASK);

  /* Set input buffer for data copy. Set input buffer for transmit */
  ERAY[Fr_CtrlIdx]->IBCM.U = FR_17_ERAY_TRANSFER_DATA;

  for (ByteIndex = FR_17_ERAY_DEC_ZERO;
              ByteIndex < FR_17_ERAY_MAX_LSDU_LENGTH; ByteIndex++)
  {
    TempLsduPtr[ByteIndex] = (uint32)FR_17_ERAY_DEC_ZERO;
  }

  /* [cover parentID={DBD872C9-D2D7-4915-97F2-74B1BB03D3F4}]
  Copy the LSdu data byte-wise from the LSdu pointer to a
  local buffer
  [/cover] */
  for (ByteIndex = FR_17_ERAY_DEC_ZERO;
        ByteIndex < Fr_LSduLength; ByteIndex++)
  {
    /* MISRA2012_RULE_18_4_JUSTIFICATION:The access to the 4 byte
    buffer TempLsduPtr should be 1 byte so pointer arithmetic is
    used.The array is defined in local scope with maximum LSDU
    length,so unintended corruption due to pointer access will
    not occur.*/
    *((uint8 *)TempLsduPtr + ByteIndex) =
                                   *(&Fr_LSduPtr[ByteIndex]);
  }

  /* [cover parentID={BEE25528-9693-4b77-B3D2-D42ACF8DF436}]
  Is (input LSdu Length less than the configured length) AND
  (Dynamic LSdu length not allowed) ?
  [/cover] */
  if ((Fr_LSduLength < PlcBytes) &&
      (AllowDynamicLSduLengthFlag != FR_17_ERAY_DEC_ONE))
  {
    /* [cover parentID={163B99A4-A28D-4333-AB4A-4EA5CFE3FEA1}]
    Convert the configured data length to be transmitted from bytes(PlcBytes)
    to words. Set the length to be a multiple of 4 (32-bit boundary).
    [/cover] */
    RegCount = (PlcBytes / FR_17_ERAY_DIV_BY_4);
    CountDiv = PlcBytes & FR_17_ERAY_MOD_4;
  }
  else
  {
    /* [cover parentID={AB330EA2-E430-4953-AEF2-E1DE6F16ACE4}]
    Convert the data length to be transmitted from bytes (Fr_LSduLength)
    to words. Set the length to be a multiple of 4 (32-bit boundary).
    [/cover] */
    RegCount = (Fr_LSduLength / FR_17_ERAY_DIV_BY_4);
    CountDiv = Fr_LSduLength & FR_17_ERAY_MOD_4;
  }

  /* Do 32-bit word transfer */
  if (CountDiv != (uint8)FR_17_ERAY_DEC_ZERO)
  {
    RegCount = RegCount + FR_17_ERAY_DEC_ONE;
  }

  /* [cover parentID={78EF9DCA-2DBF-4824-A8C4-B25B11A6D245}]
  Copy the data word-wise from the local LSdu buffer to the
  Write Data Section
  [/cover] */
  for (RegIndex = FR_17_ERAY_DEC_ZERO; RegIndex < RegCount; RegIndex++)
  {
    *(&ERAY[Fr_CtrlIdx]->WRDS_1S[RegIndex].U) =
                                         *(&TempLsduPtr[RegIndex]);
  }

  /* Set the input buffer to transfer the data section to message
    buffer */
  /* [cover parentID={B14D74B2-84F4-4eff-8758-DCF92F92B8EB}]
  Set the transmission request flag, Select the Data Section to be
  transferred from Input buffer to Message RAM
  [/cover] */
  ERAY[Fr_CtrlIdx]->IBCR.B.IBRH = MsgBuffIdx;

  /*  Check if input buffer is busy with another transfer
   a. Wait until it becomes free or a time out happens
   b. If time out happens, report Production Error to Mcal_Wrapper */
  ErrCount = Fr_17_Eray_lInputBufBsyHost(Fr_CtrlIdx);

  /* [cover parentID={713FCA9F-A685-4ad9-88E1-1637E8DDD189}]
  Is the input host buffer in busy state within timeout period ?
  [/cover] */
  if(ErrCount == (uint32)0U)
  {
    /* [cover parentID={44784F7F-7A31-47be-96E6-A4C1C0B7208D}]
    Mark the return value as successfully finished
    [/cover] */
    RetValue = E_OK;
  }
  else
  {
    /* [cover parentID={2D986F95-AC05-480d-9152-9400485FC788}]
    Mark the return value as Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  return RetValue;
}

/*******************************************************************************
** Traceability    : [cover parentID={B5DF6533-1FBF-4559-8D93-62ED2967449B}]  **
**                                                                            **
** Syntax          : static Std_ReturnType Fr_17_Eray_lRxAcceptanceCheck      **
**                      (const uint8 Fr_CtrlIdx, const uint8 ChannelIdx)      **
**                                                                            **
** Description     : Function to perform the acceptance check for the receive **
**                    operation                                               **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant for the same device                        **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                   ChannelIdx - Index of FlexRay channel within the context **
**                                of the FlexRay CC Fr_CtrlIdx                **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: API call finished successfully.                    **
**                   E_NOT_OK: API call aborted due to timeout error.         **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Fr_17_Eray_lRxAcceptanceCheck(
                       const uint8 Fr_CtrlIdx, const uint8 ChannelIdx)
{
  uint32 StatusMbsChA;
  uint32 StatusMbsChB;
  Std_ReturnType RetValue;

  #if (FR_17_ERAY_RX_STRINGENT_LENGTH_CHECK == STD_ON)
  uint8 PayloadLenReceived;
  uint8 PayloadLenConfigured;
  #endif /* (FR_17_ERAY_RX_STRINGENT_LENGTH_CHECK == STD_ON) */

  RetValue = E_OK;

  /* [cover parentID={777EB898-2BE4-48d2-A848-5E8445DE8292}]
  Receive Stringent Check Enabled
  [/cover] */
  /* [cover parentID={E29C16ED-4871-43b6-BD79-8C5CFFE341A3}]
  Receive Stringent Check Enabled
  [/cover] */
  #if(FR_17_ERAY_RX_STRINGENT_CHECK == STD_ON)

  /* Check if the SlotStatus does not show a valid frame (vSS!ValidFrame)
  and a single SlotStatus error bit set (vSS!SyntaxError,vSS!ContentError,
  vSS!Bviolation) and return E_NOT_OK */
  /* [cover parentID={20DFA4A8-9399-4f0d-8D3F-0FFFE62AAD4E}]
  Get the status of slot errors detected and valid frame received
  on Channel A from the Message Buffer Status
  [/cover] */
  StatusMbsChA = (uint32)(ERAY[Fr_CtrlIdx]->MBS.U &
                             FR_17_ERAY_MBS_CHANNELA_MASK);

  /* [cover parentID={CD935E50-E420-4fe7-A9BC-C235D0BF968F}]
  Get the status of slot errors detected and valid frame received
  on Channel B from the Message Buffer Status
  [/cover] */
  StatusMbsChB = (uint32)(ERAY[Fr_CtrlIdx]->MBS.U &
                             FR_17_ERAY_MBS_CHANNELB_MASK);

  /* [cover parentID={1D9C4E6C-0847-4c6e-B135-11F888854BD9}]
  Receive Stringent Check Disabled
  [/cover] */
  #else
  /* Check if the SlotStatus does not show a valid frame
     (vSS!ValidFrame) and return E_NOT_OK */
  /* [cover parentID={60D5337C-BF08-4a93-985F-7C852751A636}]
  Get the status of  valid frame received on Channel A from the
  Message Buffer Status
  [/cover] */
  StatusMbsChA = (uint32)(ERAY[Fr_CtrlIdx]->MBS.U &
                                FR_17_ERAY_MBS_CHA_VALIDMASK);

  /* [cover parentID={C0364511-5E54-446b-8B62-7C0F5D7A3032}]
  Get the status of  valid frame received on Channel B from the
  Message Buffer Status
  [/cover] */
  StatusMbsChB = (uint32)(ERAY[Fr_CtrlIdx]->MBS.U &
                                FR_17_ERAY_MBS_CHB_VALIDMASK);
  #endif /* (FR_17_ERAY_RX_STRINGENT_CHECK == STD_ON) */

  /* As VFRA is 0 if a valid frame is not received, toggle this bit to
     check for error */
  StatusMbsChA ^= FR_17_ERAY_MBS_CHANNELA_VALID_BIT;

  /* As VFRB is 0 if a valid frame is not received, toggle this bit to
     check for error */
  StatusMbsChB ^= FR_17_ERAY_MBS_CHANNELB_VALID_BIT;

  /* [cover parentID={2197832A-C00E-4804-9506-8FB3594BB76F}]
  Is (Error detected on Channel A) AND (requested channel index is A) ?
  [/cover] */
  if ((ChannelIdx == (uint8)FR_CHANNEL_A) && (StatusMbsChA != 0U))
  {
    /* [cover parentID={69ADD57D-503A-4091-B69A-11549E310370}]
    Mark the return value as Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }
  /* [cover parentID={A92A015D-9506-46f6-A70F-9CE93521BAE9}]
  Is (Error detected on Channel B) AND (requested channel index is B) ?
  [/cover] */
  else if ((ChannelIdx == (uint8)FR_CHANNEL_B) && (StatusMbsChB != 0U))
  {
    /* [cover parentID={ABC039FF-4C7D-4e6f-A696-9C0248E0FFBD}]
    Mark the return value as Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }
  /* [cover parentID={B09D7EE6-5CC6-486c-A044-5CBC2C38DDEF}]
  Is (Error detected on Channel A&B) AND (requested channel index is AB) ?
  [/cover] */
  else if ((StatusMbsChA != 0U) && (StatusMbsChB != 0U))
  {
    /* [cover parentID={DEB66CA6-29F5-42f4-B433-64D96EBB7E9F}]
    Mark the return value as Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }
  else
  {
    /* Do Nothing */
  }

  /* [cover parentID={191515FE-8871-4123-9405-78802AA48CE4}]
  Stringent Length Check is Enabled
  [/cover] */
  #if (FR_17_ERAY_RX_STRINGENT_LENGTH_CHECK == STD_ON)
  if (RetValue == E_OK)
  {
    /* Received length in bytes = Min(PLR, PLC) [FR239] * 2 */
    PayloadLenReceived = (uint8)ERAY[Fr_CtrlIdx]->RDHS2.B.PLR;

    /*Dynamic Slot*/
    PayloadLenConfigured = (uint8)ERAY[Fr_CtrlIdx]->RDHS2.B.PLC;

    /* [cover parentID={7B4BEB28-D573-466e-BF8A-B74989A1C884}]
    Is Payload length received same as configured length?
    [/cover] */
    /* Check if received payload length matches
    with configured payload length */
    if(PayloadLenReceived != PayloadLenConfigured)
    {
      /* received payload length does not match
      the configured payload length */
      /* [cover parentID={61DCC19A-A9EC-444c-8FA6-B62412202816}]
      Mark the return value as Error detected
      [/cover] */
      RetValue = E_NOT_OK;
    }
  }
  #endif /* (FR_17_ERAY_RX_STRINGENT_LENGTH_CHECK == STD_ON) */

  return RetValue;
}

#if ((FR_17_ERAY_RECONFIG_LPDU == STD_ON) &&\
           (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON))
/*******************************************************************************
** Traceability    : [cover parentID={FD6F6251-A8AF-4bd1-A3FE-EED6C57703C5}]  **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_lRecfgDetChkLpduParam(         **
**                                     const uint8 Fr_CtrlIdx,                **
**                                     const uint16 Fr_LPduIdx,               **
**                                     const uint16 Fr_FrameId,               **
**                                     const Fr_ChannelType Fr_ChnlIdx)       **
**                                                                            **
** Description     : Function to check the development error conditions for   **
**                     the API Fr_17_Eray_ReconfigLPdu                        **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  NA                                                      **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Reentrant                                               **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                   Fr_LPduIdx - This index is used to uniquely identify a   **
**                                FlexRay frame.                              **
**                   Fr_ChnlIdx - FlexRay Channel the FrIf_LPdu shall be      **
**                                configured to.                              **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE  Std_ReturnType Fr_17_Eray_lRecfgDetChkLpduParam(
                                              const uint8 Fr_CtrlIdx,
                                              const uint16 Fr_LPduIdx,
                                              const Fr_ChannelType Fr_ChnlIdx)
{
  uint32 DevError;
  const Fr_17_Eray_LPduConfigType *LPduCfgPtr;
  Std_ReturnType RetValue;
  Fr_ChannelType ChannelIdx;
  uint8 ChannelsConfig;
  uint8 LogIdx;

  /* [cover parentID={203FECE5-07BB-422d-91A8-41ADF65600EA}]
  Check for Fr Initialization
  [/cover] */
  /* FR_17_ERAY_E_INIT_FAILED */
  DevError = Fr_17_Eray_lDetCheckNoInit(FR_17_ERAY_SID_RECONFIGLPDU);

  /* [cover parentID={2CC15263-C05D-45f0-9330-8A3CBD2D059B}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={DB4CF7E2-4834-4574-8C9E-B4BDD44961EC}]
    Check for validity of controller Index
    [/cover] */
    /* FR_17_ERAY_E_INV_CTRL_IDX */
    DevError = Fr_17_Eray_lDetCheckInvCtrlIdx(Fr_CtrlIdx,
                                                 FR_17_ERAY_SID_RECONFIGLPDU);
  }

  /* [cover parentID={D47C1C8C-CB5C-42fd-BD67-B6D13795C147}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={FA37796F-0B1B-4b1f-98C8-AE2D1227E822}]
    Check the validity of the LPdu index
    [/cover] */
    /* FR_17_ERAY_E_INV_LPDU_IDX: LPduIdx >= LPDU count  */
    DevError = Fr_17_Eray_lDetCheckInvLPduIdx(Fr_CtrlIdx,Fr_LPduIdx,
                                                  FR_17_ERAY_SID_RECONFIGLPDU);
  }

  /* [cover parentID={43E9DA9C-7E4A-45ef-973F-F1B268624B2B}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];

    LPduCfgPtr = Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].LPduConfigPtr;

    /* [cover parentID={71072D4A-6769-491c-852C-21CDA448E5DD}]
    Is the LPdu Not Reconfigurable ?
    [/cover] */
    if (LPduCfgPtr[Fr_LPduIdx].LpduReconfigurable !=
                             (uint8)FR_17_ERAY_LPDU_RECONFIGURABLE)
    {
      /* [cover parentID={59892081-3C7B-4e15-B9C6-C578AA81657B}]
      Report DET
      [/cover] */
      (void)Det_ReportError(FR_17_ERAY_MODULE_ID, FR_17_ERAY_INSTANCE_ID,
                   FR_17_ERAY_SID_RECONFIGLPDU, FR_17_ERAY_E_INV_LPDU_IDX);
      DevError = FR_17_ERAY_E_INV_LPDU_IDX;
    }
  }

  /* [cover parentID={19FF4930-E836-4a7a-8DAC-3697190ED926}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={A3B88EC2-F375-40f9-9054-2AB2C27CBE84}]
    Is FR Channel index is in valid range ?
    [/cover] */
    if((Fr_ChnlIdx == FR_CHANNEL_A)||(Fr_ChnlIdx == FR_CHANNEL_B)||
                                          (Fr_ChnlIdx == FR_CHANNEL_AB))
    {
      LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];

      ChannelsConfig = (uint8)
          ((Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].CCCfgPtr->Succ1CfgVal >>
            IFX_ERAY_SUCC1_CCHA_OFF) & FR_17_ERAY_SUCC1_CHANNEL_MASK);

      if(ChannelsConfig == 0x1U)
      {
        ChannelIdx = FR_CHANNEL_A;
      }
      else if(ChannelsConfig == 0x2U)
      {
        ChannelIdx = FR_CHANNEL_B;
      }
      else
      {
        ChannelIdx = FR_CHANNEL_AB;
      }

      /* [cover parentID={2EED03A5-50EC-44e8-9FD4-15BFBA3E477F}]
      Is the Fr Channel Index parameter valid (compared with configured
      channel index)?
      [/cover] */
      if ((ChannelIdx != FR_CHANNEL_AB) && (Fr_ChnlIdx != ChannelIdx))
      {
        /* [cover parentID={8F8B72BB-1FCA-4066-990A-9C6D2AD7F1DC}]
        Report DET
        [/cover] */
        (void)Det_ReportError(FR_17_ERAY_MODULE_ID, FR_17_ERAY_INSTANCE_ID,
                     FR_17_ERAY_SID_RECONFIGLPDU, FR_17_ERAY_E_INV_CHNL_IDX);
        DevError = FR_17_ERAY_E_INV_CHNL_IDX;
      }
    }
    else
    {
      /* [cover parentID={DC2C05F8-0598-47c2-B2B9-BC03B620DFBF}]
      Report DET
      [/cover] */
      (void)Det_ReportError(FR_17_ERAY_MODULE_ID, FR_17_ERAY_INSTANCE_ID,
                   FR_17_ERAY_SID_RECONFIGLPDU, FR_17_ERAY_E_INV_CHNL_IDX);
      DevError = FR_17_ERAY_E_INV_CHNL_IDX;
    }
  }

  /* [cover parentID={7F82FF66-A943-4ff6-BD11-5A4505039C73}]
  Any DET error detected?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    RetValue = E_OK;
  }
  else
  {
    /* [cover parentID={B54C7DA6-40E1-4aac-AD51-85A5130EC18F}]
    Mark the return value as Error Detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  return RetValue;
}

/*******************************************************************************
** Traceability    : [cover parentID={E5BB282E-A00D-4bc8-9E08-0F5E5AAC5BDE}]  **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_lRecfgDetChkCycleVal(          **
**                                     const uint8 Fr_CtrlIdx,                **
**                                     const uint8 Fr_CycleRepetition)        **
**                                                                            **
** Description     : Function to check the development error conditions for   **
**                     the API Fr_17_Eray_ReconfigLPdu                        **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  NA                                                      **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Reentrant                                               **
**                                                                            **
** Parameters (in) : Fr_CycleRepetition -Cycle Repetition part of the cycle   **
**                          filter mechanism FrIf_LPdu shall be configured to **
**                   Fr_CycleOffset - Cycle Offset part of the cycle filter   **
**                                mechanism FrIf_LPdu shall be configured to. **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fr_17_Eray_lRecfgDetChkCycleVal(
                                              const uint8 Fr_CycleRepetition,
                                              const uint8 Fr_CycleOffset)
{
  uint32 DevError;
  Std_ReturnType RetValue;

  DevError = FR_17_ERAY_E_DET_NO_ERR;
  RetValue = E_OK;

  /* [cover parentID={8F40FFA5-92FF-4733-A2BB-099EB638983C}]
  Is the Cycle Repetition parameter Invalid ?
  [/cover] */
  /* Valid values for Fr_CycleRepetition: 1, 2, 4, 8, 16, 32, 64 */
  /* FR_17_ERAY_E_INV_CYCLE */
  if ((Fr_CycleRepetition != FR_17_ERAY_CYCLE_REPETION_1) &&
      (Fr_CycleRepetition != FR_17_ERAY_CYCLE_REPETION_2) &&
      (Fr_CycleRepetition != FR_17_ERAY_CYCLE_REPETION_4) &&
      (Fr_CycleRepetition != FR_17_ERAY_CYCLE_REPETION_8) &&
      (Fr_CycleRepetition != FR_17_ERAY_CYCLE_REPETION_16) &&
      (Fr_CycleRepetition != FR_17_ERAY_CYCLE_REPETION_32) &&
      (Fr_CycleRepetition != FR_17_ERAY_CYCLE_REPETION_64))
  {
    /* [cover parentID={7000FF0C-B71D-414c-8B29-2B0D25E85D3B}]
    Report DET
    [/cover] */
    (void)Det_ReportError(FR_17_ERAY_MODULE_ID, FR_17_ERAY_INSTANCE_ID,
                   FR_17_ERAY_SID_RECONFIGLPDU, FR_17_ERAY_E_INV_CYCLE);
    DevError = FR_17_ERAY_E_INV_CYCLE;
  }

  /* [cover parentID={82AA017B-F0A4-4e63-9ABF-8E996BD38DDE}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={FC933D3A-D358-49e1-90A3-36D8A56ED750}]
    Is the Cycle Offset parameter Invalid ?
    [/cover] */
    /* Valid values for Fr_BaseCycle : 0 to (Fr_CycleRepetition - 1) */
    /* FR_17_ERAY_E_INV_CYCLE */
    if (Fr_CycleOffset >= Fr_CycleRepetition)
    {
      /* [cover parentID={5B50F311-BD37-4b06-B642-8E42BA40CF76}]
      Report DET
      [/cover] */
      (void)Det_ReportError(FR_17_ERAY_MODULE_ID, FR_17_ERAY_INSTANCE_ID,
                     FR_17_ERAY_SID_RECONFIGLPDU, FR_17_ERAY_E_INV_CYCLE);
      DevError = FR_17_ERAY_E_INV_CYCLE;
    }
  }

  /* [cover parentID={024B6342-90C6-4e92-9DED-BCF7B918F814}]
  Any DET error detected?
  [/cover] */
  if (DevError != FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={5E378221-C9DD-4028-8939-D8D1DCD67701}]
    Mark the return value as Error Detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  return RetValue;
}

/*******************************************************************************
** Traceability    : [cover parentID={9CAC6FCC-3921-450e-A81B-1B2CD7F8AFB1}]  **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_lRecfgDetChkHeaderPL(          **
**                                     const uint8 Fr_CtrlIdx,                **
**                                     const uint16 Fr_LPduIdx,               **
**                                     const uint8 Fr_PayloadLength,          **
**                                     const uint16 Fr_HeaderCRC)             **
**                                                                            **
** Description     : Function to check the development error conditions for   **
**                     the API Fr_17_Eray_ReconfigLPdu                        **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  NA                                                      **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Reentrant                                               **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                   Fr_LPduIdx - This index is used to uniquely identify a   **
**                                FlexRay frame.                              **
**                   Fr_PayloadLength  - Payloadlength in units of bytes the  **
**                                FrIf_LPduIdx shall be configured to.        **
**                   Fr_HeaderCRC - Header CRC the FrIf_LPdu shall be         **
**                                  configured to.                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fr_17_Eray_lRecfgDetChkHeaderPL(
                                              const uint8 Fr_CtrlIdx,
                                              const uint16 Fr_LPduIdx,
                                              const uint8 Fr_PayloadLength,
                                              const uint16 Fr_HeaderCRC)
{
  uint32 DevError;
  const Fr_17_Eray_LPduConfigType *LPduCfgPtr;
  Std_ReturnType RetValue;
  uint8 ConfigPlcBytes;
  uint8 PlcBytes;
  uint8 LogIdx;

  DevError = FR_17_ERAY_E_DET_NO_ERR;
  RetValue = E_OK;

  LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];

  LPduCfgPtr = Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].LPduConfigPtr;
  /* Payload Length Configured in bytes */

  ConfigPlcBytes = (uint8)((LPduCfgPtr[Fr_LPduIdx].Wrhs2CfgVal >>
                IFX_ERAY_WRHS2_PLC_OFF) & IFX_ERAY_WRHS2_PLC_MSK);

  PlcBytes = (uint8)(ConfigPlcBytes * FR_17_ERAY_BYTES_PER_HALFWORD);

  /* [cover parentID={470F13AE-56C0-4254-BC0A-3098A67D339B}]
  Is the Fr payload length parameter greater than the configured length?
  [/cover] */
  /* FR_17_ERAY_E_INV_LENGTH */
  if (Fr_PayloadLength > PlcBytes)
  {
    /* [cover parentID={4133EEC2-C02E-4db3-B988-B2C653CE6E79}]
    Report DET
    [/cover] */
    (void)Det_ReportError(FR_17_ERAY_MODULE_ID, FR_17_ERAY_INSTANCE_ID,
                    FR_17_ERAY_SID_RECONFIGLPDU, FR_17_ERAY_E_INV_LENGTH);
    DevError = FR_17_ERAY_E_INV_LENGTH;
  }

  /* [cover parentID={B948D3EB-2469-4911-B568-75EFBC23BCB0}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={24C0A367-6DE7-4cc6-B77C-66060420D55A}]
    Is Fr Header CRC parameter greater than 2047 value ?
    [/cover] */
    /* Valid values for Fr_HeaderCRC : 0 to 2047 */
    /* FR_17_ERAY_E_INV_HEADERCRC */
    if (Fr_HeaderCRC > FR_17_ERAY_HEADER_CRC_MAX)
    {
      /* [cover parentID={5BCCFA00-279B-4a08-87C8-21702E77DF4E}]
      Report DET
      [/cover] */
      (void)Det_ReportError(FR_17_ERAY_MODULE_ID, FR_17_ERAY_INSTANCE_ID,
                     FR_17_ERAY_SID_RECONFIGLPDU, FR_17_ERAY_E_INV_HEADERCRC);
      DevError = FR_17_ERAY_E_INV_HEADERCRC;
    }
  }

  /* [cover parentID={C82B6F50-AC95-4bd4-9874-DFB99CE4AF90}]
  Any DET error detected?
  [/cover] */
  /* Return if a development error detected */
  if (DevError != FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={33D0A65A-93F2-4f3a-89A8-F29E8FBDD52F}]
    Mark the return value as Error detected
    [/cover] */
    RetValue = E_NOT_OK;
  }

  return RetValue;
}

#endif /* (FR_17_ERAY_RECONFIG_LPDU, FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */

/*******************************************************************************
** Traceability    : [cover parentID={0F93C06B-6C48-4d66-A250-1D420C42BD12}]  **
**                                                                            **
** Syntax          : static void Fr_17_Eray_lReceiveDataCopy(                 **
**                                     const uint8 Fr_CtrlIdx,                **
**                                     uint8 * const Fr_LSduPtr,              **
**                                     uint8 * const Fr_LSduLengthPtr)        **
**                                                                            **
** Description     : Function to copy the received data from output buffer    **
**                   to the buffer where the received LSdu is to be stored.   **
**                   This function needs to be invoked only after the transfer**
**                   of header and data section is done from message RAM to   **
**                   output buffer.                                           **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  NA                                                      **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                                                                            **
** Parameters (out): Fr_LSduPtr - This reference points to a buffer where the **
**                                  LSdu to be received shall be stored       **
**                   Fr_LSduLengthPtr - This reference points to the memory   **
**                           location where the length of the LSdu (in bytes) **
**                           shall be stored. This length represents the      **
**                           number of bytes copied to LSduPtr.               **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
static void Fr_17_Eray_lReceiveDataCopy(const uint8 Fr_CtrlIdx,
                                        uint8 * const Fr_LSduPtr,
                                        uint8 * const Fr_LSduLengthPtr)
{
  uint32 ByteIndex;
  uint32 TempLsduPtr[FR_17_ERAY_MAX_LSDU_LENGTH];
  uint8 PayloadLenReceived;
  uint8 PayloadLenConfigured;
  uint8 RegCount;
  uint8 RegIndex;

  for (RegIndex = FR_17_ERAY_DEC_ZERO;
       RegIndex < FR_17_ERAY_MAX_LSDU_LENGTH; RegIndex++)
  {
    TempLsduPtr[RegIndex] = (uint32)FR_17_ERAY_DEC_ZERO;
  }

  /* Received length in bytes = Min(PLR, PLC) * 2 */
  PayloadLenReceived = (uint8)ERAY[Fr_CtrlIdx]->RDHS2.B.PLR;

  PayloadLenConfigured = (uint8)ERAY[Fr_CtrlIdx]->RDHS2.B.PLC;

  /* [cover parentID={43502872-16E9-4797-97F2-56D62EB398FF}]
  Is Payload Length Received > Configured Length ?
  [/cover] */
  if (PayloadLenReceived > PayloadLenConfigured)
  {
    /* [cover parentID={FCAA519C-BFBA-4294-8288-24D6F599D3C8}]
    Write Configured payload length to LSdu Length pointer
    [/cover] */
    *Fr_LSduLengthPtr =
    (uint8)(PayloadLenConfigured * FR_17_ERAY_BYTES_PER_HALFWORD);
  }
  else
  {
    /* [cover parentID={1FC39F59-2C04-4633-9CE4-85DE2129E7F3}]
    Write Received payload length to LSdu Length pointer
    [/cover] */
    *Fr_LSduLengthPtr =
    (uint8)(PayloadLenReceived * FR_17_ERAY_BYTES_PER_HALFWORD);
  }

  /* Copy data from RDDSn registers to application buffer pointed
      by Fr_LSduPtr */

  RegCount = ((*Fr_LSduLengthPtr) / FR_17_ERAY_DIV_BY_4);

  if (((*Fr_LSduLengthPtr) & FR_17_ERAY_MOD_4) != (uint8)0U)
  {
    RegCount = RegCount + FR_17_ERAY_DEC_ONE;
  }

  for (RegIndex = FR_17_ERAY_DEC_ZERO; RegIndex < RegCount; RegIndex++)
  {
    TempLsduPtr[RegIndex] =
                 (uint32)(ERAY[Fr_CtrlIdx]->RDDS_1S[RegIndex].U);
  }

  /* [cover parentID={B7AA1D3E-F5C6-43d4-8B79-1662C315EE4A}]
  Copy the received data from the data section into LSdu pointer in
  the same order as it was received
  [/cover] */
  for (ByteIndex = FR_17_ERAY_DEC_ZERO;
        ByteIndex < (uint32)(*Fr_LSduLengthPtr); ByteIndex++)
  {
    /* MISRA2012_RULE_18_4_JUSTIFICATION:To perform the byte access
     to the buffer TempLsduPtr, pointer arithmetic is used.
     The array is defined in local scope with maximum LSdu length,
     so unintended corruption due to pointer access will not occur.*/
    Fr_LSduPtr[ByteIndex] = *((uint8*)TempLsduPtr + ByteIndex);
  }
}

/*******************************************************************************
** Traceability    : [cover parentID={2093216D-A604-4df0-9F36-D0390A7B80B7}]  **
**                                                                            **
** Syntax          : static Std_ReturnType Fr_17_Eray_lRxTransferToOBF(       **
**                                     const uint8 Fr_CtrlIdx,                **
**                                     const uint16 Fr_LPduIdx,               **
**                                     const uint8 MsgBufferIdx)              **
**                                                                            **
** Description     : This function performs the transfer of the header and    **
**                   data section from the message RAM to output buffer for   **
**                   indexed message buffer                                   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  NA                                                      **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                   Fr_LPduIdx - This index is used to uniquely identify a   **
**                                FlexRay frame.                              **
**                   MsgBufferIdx - Index of the message buffer within the CC **
**                                  that corresponds to Ldu index             **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: API call finished successfully.                    **
**                   E_NOT_OK: API call aborted due to errors.                **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Fr_17_Eray_lRxTransferToOBF(
                                              const uint8 Fr_CtrlIdx,
                                              const uint16 Fr_LPduIdx,
                                              const uint8 MsgBufferIdx)
{
  Std_ReturnType RetValue;
  uint8 ChannelIdx;
  uint8 LogIdx;

  LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];

  /* [cover parentID={94B9CA61-D74A-4d93-825D-193157547470}]
  Select header and data section to be transferred from Message RAM to
  Output buffer and Request the transfer for the message buffer index
  [/cover] */
  ERAY[Fr_CtrlIdx]->OBCM.B.RHSS = FR_17_ERAY_DEC_ONE;
  ERAY[Fr_CtrlIdx]->OBCM.B.RDSS = FR_17_ERAY_DEC_ONE;

  /*Request transfer of Message Buffer MsgBuffIdx to OBF Shadow
   buffer*/
  ERAY[Fr_CtrlIdx]->OBCR.B.OBRS = MsgBufferIdx;
  ERAY[Fr_CtrlIdx]->OBCR.B.VIEW = FR_17_ERAY_DEC_ZERO;
  ERAY[Fr_CtrlIdx]->OBCR.B.REQ = FR_17_ERAY_DEC_ONE;

  /* Wait until transfer is complete */
  RetValue = Fr_17_Eray_lWaitTransferComplete(Fr_CtrlIdx, LogIdx);

  /* [cover parentID={8F3CB8B8-F47D-457f-814F-90B0FBD155B4}]
  Is a Timeout Error detected ?
  [/cover] */
  if (RetValue == E_OK)
  {
    /* Clear the transfer request */
    ERAY[Fr_CtrlIdx]->OBCR.B.REQ = FR_17_ERAY_DEC_ZERO;

    /* [cover parentID={D563B049-FCC3-4404-80D4-C3FE51F31A8A}]
    Swap the host and shadow buffer to read the header/ data
    [/cover] */
    ERAY[Fr_CtrlIdx]->OBCR.B.VIEW = FR_17_ERAY_DEC_ONE;


#if(MCAL_AR_VERSION == MCAL_AR_440)
    ChannelIdx = (uint8)((Fr_17_Eray_ConfigPtr->
           CfgPtr[LogIdx].LPduConfigPtr[Fr_LPduIdx].Wrhs1CfgVal >>
           IFX_ERAY_WRHS1_CHA_OFF) & FR_17_ERAY_WRHS1_CHANNEL_MASK);
#else
    /* [cover parentID={B20634D6-2A85-4892-9A6C-5BFDCA24DB23}]
    Subtract 1 to correct the channel as per Fr_ChannelType enum in
    AUTOSAR 4.2.2, to be used for further processing
    [/cover] */
    ChannelIdx = (uint8)(((Fr_17_Eray_ConfigPtr->
           CfgPtr[LogIdx].LPduConfigPtr[Fr_LPduIdx].Wrhs1CfgVal >>
           IFX_ERAY_WRHS1_CHA_OFF) & FR_17_ERAY_WRHS1_CHANNEL_MASK) -
                                                          (uint8)0x1);
#endif

    /* [cover parentID={5ADB68B3-E929-44b1-9886-4D2DFA18DEC6}]
    Is Production Error reporting for Slot Error Configured ?
    [/cover] */
    if (Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].LPduConfigPtr[Fr_LPduIdx].
        FrDemFTSlotStatusErrId !=
                       (Dem_EventIdType)FR_17_ERAY_DEM_REPORT_DISABLED)
    {
      /* [cover parentID={C134C329-2D05-4a41-A151-424F42B6BC16}]
      Check for Slot Status Errors
      [/cover] */
      RetValue = Fr_17_Eray_lSlotStatusErrorCheck(Fr_CtrlIdx,
                                               ChannelIdx, Fr_LPduIdx);
    }
  }

  return RetValue;
}

/*******************************************************************************
** Traceability    : [cover parentID={A4729751-1166-45b4-AD51-7028361792DE}]  **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_lTrnsfHdrToOBF(                **
**                                     const uint8 Fr_CtrlIdx,                **
**                                     const uint8 MsgBufferIdx)              **
**                                                                            **
** Description     : This function performs the transfer of the header section**
**                   from the message RAM to output buffer for the indexed    **
**                   message buffer                                           **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  NA                                                      **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                   MsgBufferIdx - Index of the message buffer within the CC **
**                                  that corresponds to LPdu index            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: Header section transferred successfully.           **
**                   E_NOT_OK: Timeout error detected.                        **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fr_17_Eray_lTrnsfHdrToOBF(
                                              const uint8 Fr_CtrlIdx,
                                              const uint8 MsgBufferIdx)
{
  Std_ReturnType RetValue;
  uint8 LogIdx;

  LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];

  /* [cover parentID={E02170A9-3956-48ec-A33A-FCFBA0A89EE1}]
  Select only header section to be transferred from Message RAM to
  Output buffer and Request the transfer for the message buffer index
  [/cover] */
  ERAY[Fr_CtrlIdx]->OBCM.B.RHSS = FR_17_ERAY_DEC_ONE;

  /*Request transfer of Message Buffer MsgBufferIdx to OBF Shadow
   buffer*/
  ERAY[Fr_CtrlIdx]->OBCR.B.OBRS = MsgBufferIdx;
  ERAY[Fr_CtrlIdx]->OBCR.B.VIEW = FR_17_ERAY_DEC_ZERO;
  ERAY[Fr_CtrlIdx]->OBCR.B.REQ = FR_17_ERAY_DEC_ONE;

  /* Wait until transfer is complete */
  RetValue = Fr_17_Eray_lWaitTransferComplete(Fr_CtrlIdx, LogIdx);

  /* [cover parentID={7292B643-39E6-4b8d-85DE-E0C29A6587D9}]
  Is a Timeout Error detected ?
  [/cover] */
  if (RetValue == E_OK)
  {
    /* Clear the REQ bit before View bit is set. Otherwise data will be
       transferred to the shadow buffer */
    ERAY[Fr_CtrlIdx]->OBCR.B.REQ = FR_17_ERAY_DEC_ZERO;

    /* [cover parentID={0AAB871A-4805-4a45-9C0B-B40F7D1E844B}]
    Swap the host and shadow buffer to read the header/ data
    [/cover] */
    ERAY[Fr_CtrlIdx]->OBCR.B.VIEW = FR_17_ERAY_DEC_ONE;
  }

  return RetValue;
}

/*******************************************************************************
** Traceability    : [cover parentID={70AEC105-DB2B-4fd7-A058-5D0DAE395E4F}]  **
**                                                                            **
** Syntax          : static void Fr_17_Eray_lReportDemError                   **
                                      (const Dem_EventIdType EventId,         **
                                       const Dem_EventStatusType EventStatus) **
**                                                                            **
** Description     : Report Production error status                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  NA                                                      **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : EventId - DEM event identification number                **
**                                                                            **
**                   EventStatus - DEM event status to be set                 **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
static void Fr_17_Eray_lReportDemError(const Dem_EventIdType EventId,
                                       const Dem_EventStatusType EventStatus)
{
  /* Autosar version is AR440 */
  #if (MCAL_AR_VERSION == MCAL_AR_440)
  /* [cover parentID={1E93BFA5-9EC9-4210-9695-55D177CBC63E}]
  Report the Production Error status
  [/cover] */
    (void)Mcal_Wrapper_Dem_SetEventStatus(EventId, EventStatus);
  #else
  /* [cover parentID={3EE01967-667D-41c8-93D4-750F64CD61E5}]
  Report the Production Error status
  [/cover] */
    Mcal_Wrapper_Dem_ReportErrorStatus(EventId, EventStatus);
  #endif
}

#if(((MCAL_AR_VERSION == MCAL_AR_422) &&\
          (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON))\
             || (FR_17_ERAY_RUNTIME_ERROR_DETECT == STD_ON))
/*******************************************************************************
** Traceability    : [cover parentID={2E86BCDC-8417-49dc-9328-CD38B2CDECE4}]  **
**                                                                            **
** Syntax          : void Fr_17_Eray_lReportRuntimeDetError(const uint8       **
**                                       ApiId, const uint8 ErrorId)          **
**                                                                            **
** Description     : Report runtime or DET error                              **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  NA                                                      **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : ApiId - ID of API service in which error is detected     **
**                                                                            **
**                   ErrorId - ID of detected runtime or developement error   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
static void Fr_17_Eray_lReportRuntimeDetError(const uint8 ApiId,
                                                      const uint8 ErrorId)
{
  /* Runtime Error Detection is only available in Autosar version AR440 */
  #if (FR_17_ERAY_RUNTIME_ERROR_DETECT == STD_ON)
  /* [cover parentID={E961A150-701D-4241-863C-EC2CC8D3E99A}]
   Report the Runtime Error
  [/cover] */
  (void)Mcal_Wrapper_Det_ReportRuntimeError(FR_17_ERAY_MODULE_ID, FR_17_ERAY_INSTANCE_ID,
                                                             ApiId, ErrorId);
  /* Autosar version AR422 and DET enabled */
  #elif((MCAL_AR_VERSION == MCAL_AR_422) &&\
          (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON))
    /* [cover parentID={C0EC5ED4-F02D-4119-BE23-52A9291D1516}]
     Report the DET Error
    [/cover] */
    /* DET is ON */
    /* Report the DET Error */
    (void)Det_ReportError(FR_17_ERAY_MODULE_ID, FR_17_ERAY_INSTANCE_ID,
                                                             ApiId, ErrorId);
  #endif /*(FR_17_ERAY_RUNTIME_ERROR_DETECT == STD_ON)*/
}
#endif /*#if(((MCAL_AR_VERSION == MCAL_AR_422) &&\
          (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON))\
             || (FR_17_ERAY_RUNTIME_ERROR_DETECT == STD_ON))*/

/*******************************************************************************
** Traceability    : [cover parentID={B833CC1F-C5B0-4bfc-AD3A-D9107A46FF1B}]  **
**                                                                            **
** Syntax          : static Std_ReturnType Fr_17_Eray_lCheckTxLPduStatus(     **
**                             const uint8 Fr_CtrlIdx,                        **
**                             const uint16 Fr_LPduIdx,                       **
**                             Fr_TxLPduStatusType * const Fr_TxLPduStatusPtr **
**                         )                                                  **
**                                                                            **
** Description     : Checks the transmit status of the LSdu.                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  NA                                                      **
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
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Fr_17_Eray_lCheckTxLPduStatus(
                                 const uint8 Fr_CtrlIdx,
                                 const uint16 Fr_LPduIdx,
                                 Fr_TxLPduStatusType * const Fr_TxLPduStatusPtr)
{
  uint32 NdatRegId;
  uint32 NdatRegMsgBuffIdPos;
  Std_ReturnType RetValue;
  #if (FR_17_ERAY_TX_CONFLICT_DETECTION == STD_ON)
  Std_ReturnType RetConflictSts;
  #endif /* (FR_17_ERAY_TX_CONFLICT_DETECTION == STD_ON) */
  uint8 MsgBuffIdx;
  uint8 LogIdx;
  uint8 ChannelIdx;

  /* [cover parentID={462BEC60-2C4A-4e91-B16D-0148E23F9AB0}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  RetValue = Fr_17_Eray_lCheckTxLPduDetCheck(Fr_CtrlIdx, Fr_LPduIdx,
                                                  Fr_TxLPduStatusPtr);

  /* [cover parentID={3883C676-64E6-4456-841A-3641FE891794}]
  Any DET error occurred ?
  [/cover] */
  if(RetValue == E_OK)
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */
  {
    LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];

    /* [cover parentID={0FD23203-12C7-419e-9E80-44B38D50EC9B}]
    Get the message buffer number allocated to the LPdu Index
    [/cover] */
    /* Figure out the message buffer corresponding to LPduIdx */
    MsgBuffIdx = Fr_17_Eray_ConfigPtr->
                        CfgPtr[LogIdx].LPduIdx2MsgBuffIdxPtr[Fr_LPduIdx];

    /* [cover parentID={2CDE2688-478A-4fa9-A0A4-E653CFC98F23}]
    Does the message buffer configuration correspond to LPdu Index?
    [/cover] */
    /* Does current message buffer configuration correspond to LPduIdx? */
    if (Fr_17_Eray_MsgBuff2LPduIdxPtr[Fr_CtrlIdx][MsgBuffIdx] == Fr_LPduIdx)
    {
      /* Get the channel for which status has to be checked */
#if(MCAL_AR_VERSION == MCAL_AR_440)
      ChannelIdx = (uint8)((Fr_17_Eray_ConfigPtr->
             CfgPtr[LogIdx].LPduConfigPtr[Fr_LPduIdx].Wrhs1CfgVal >>
             IFX_ERAY_WRHS1_CHA_OFF) & FR_17_ERAY_WRHS1_CHANNEL_MASK);
#else
      /* [cover parentID={4DA691E0-8194-4f80-B023-5B84ED0A5943}]
      Subtract 1 to correct the channel as per Fr_ChannelType enum in
      AUTOSAR 4.2.2, to be used for further processing
      [/cover] */
      ChannelIdx = (uint8)(((Fr_17_Eray_ConfigPtr->
             CfgPtr[LogIdx].LPduConfigPtr[Fr_LPduIdx].Wrhs1CfgVal >>
             IFX_ERAY_WRHS1_CHA_OFF) & FR_17_ERAY_WRHS1_CHANNEL_MASK) -
                                                            (uint8)0x1);
#endif

      /* [cover parentID={A5F19037-96E4-4f15-830E-678FC9F347EB}]
      Tx Conflict Detection Enabled
      [/cover] */
      #if (FR_17_ERAY_TX_CONFLICT_DETECTION == STD_ON)
      RetValue = Fr_17_Eray_lTrnsfHdrToOBF(Fr_CtrlIdx, MsgBuffIdx);

      /* [cover parentID={D3DE0BFD-00E3-47a5-A8DD-562AA83BE717}]
      Any error detected ?
      [/cover] */
      if (RetValue == E_OK)
      #endif /* (FR_17_ERAY_TX_CONFLICT_DETECTION == STD_ON) */
      {
        /* [cover parentID={3B7787FE-87F6-476a-875C-545731D86B5B}]
        Is Production Error reporting for Slot Error Configured ?
        [/cover] */
        if(Fr_17_Eray_ConfigPtr->
            CfgPtr[LogIdx].LPduConfigPtr[Fr_LPduIdx].FrDemFTSlotStatusErrId !=
                       (Dem_EventIdType)FR_17_ERAY_DEM_REPORT_DISABLED)
        {
          /* [cover parentID={49E67E80-AAF2-4900-8FF6-C47CEFF631BA}]
          Tx Conflict Detection Disabled
          [/cover] */
          #if (FR_17_ERAY_TX_CONFLICT_DETECTION == STD_OFF)
          RetValue = Fr_17_Eray_lTrnsfHdrToOBF(Fr_CtrlIdx, MsgBuffIdx);

          /* [cover parentID={41D93D18-DE1C-4056-9980-7777E5EDD417}]
          Any error detected ?
          [/cover] */
          if (RetValue == E_OK)
          #endif /* (FR_17_ERAY_TX_CONFLICT_DETECTION == STD_OFF) */
          {
            /* [cover parentID={C375A6CD-A48F-4419-B53F-BBE767828120}]
            Check for Slot Status Errors
            [/cover] */
            RetValue = Fr_17_Eray_lSlotStatusErrorCheck(Fr_CtrlIdx, ChannelIdx,
                                                                   Fr_LPduIdx);
          }
        }
        #if (FR_17_ERAY_TX_CONFLICT_DETECTION == STD_OFF)
        else
        {
          /* Production Error reporting not configured, no error detected */
          RetValue = E_OK;
        }
        #endif /* (FR_17_ERAY_TX_CONFLICT_DETECTION == STD_OFF) */
      }

      /* [cover parentID={0C13C5F1-F9FD-4dbc-88EE-3EA5A692397D}]
      Any Error detected ?
      [/cover] */
      if (RetValue == E_OK)
      {
        /* [cover parentID={88B8E424-BA44-40fc-94C2-0CB38F347225}]
        Tx Conflict Detection Enabled
        [/cover] */
        #if (FR_17_ERAY_TX_CONFLICT_DETECTION == STD_ON)
        /* [cover parentID={585FD10C-1520-4281-9DBB-451E8261A587}]
        Check for Tx conflict occurrence
        [/cover] */
        RetConflictSts = Fr_17_Eray_lConflictStatusCheck(Fr_CtrlIdx,
                                                         ChannelIdx);

        /* [cover parentID={6D317D4C-FD6C-4f70-9376-E8A926EE4857}]
        Check if conflict occurred
        [/cover] */
        if (RetConflictSts == E_NOT_OK)
        {
          /* [cover parentID={FB0FD923-93FF-4884-AD7C-60C1F4FDBC70}]
          Write the status as 'FR_TRANSMITTED_CONFLICT' to the output parameter
          Fr_TxLPduStatusPtr
          [/cover] */
          *Fr_TxLPduStatusPtr = FR_TRANSMITTED_CONFLICT;
        }
        else
        #endif /* (FR_17_ERAY_TX_CONFLICT_DETECTION == STD_ON) */
        {
          /* [cover parentID={DFD22608-F5D3-405e-B1E4-2988B9904E0C}]
          Mark the return value as successfully finished
          [/cover] */
          /* Figure out the TXRQ register corresponding to MsgBuffIdx */
          NdatRegId = (uint32)MsgBuffIdx >> FR_17_ERAY_MSG_BUFF_ID_SHIFT;

          /* Figure out the bit, corresponding to MsgBuffIdx in TXRQ register */
          /* Note: ANDing with 0x1F ==> MOD operation */
          NdatRegMsgBuffIdPos = (uint32)MsgBuffIdx &
                                         FR_17_ERAY_MSG_BUFF_ID_MASK;

          /* [cover parentID={03DFBF7F-1410-463a-8D2B-F247C47C1D65}]
          Is the message buffer pending for transmission ?
          [/cover] */
          /* Check if transmission has completed. */
          if (((&ERAY[Fr_CtrlIdx]->TXRQ1)[NdatRegId].U &
              ((uint32)1 << NdatRegMsgBuffIdPos)) == (uint32)0U)
          {
            /* [cover parentID={3FBF35AC-C482-4545-BFC5-4A07A0E3C032}]
            Write the status as 'FR_TRANSMITTED' to the output parameter
            Fr_TxLPduStatusPtr
            [/cover] */
            *Fr_TxLPduStatusPtr = FR_TRANSMITTED;
          }
          else
          {
            /* [cover parentID={711BED17-63CF-4c6e-A1BE-909A285AB90C}]
            Write the status as 'FR_NOT_TRANSMITTED' to the output parameter
            Fr_TxLPduStatusPtr
            [/cover] */
            *Fr_TxLPduStatusPtr = FR_NOT_TRANSMITTED;
          }
        }
      }
    }
    else
    {
      /* Current message buffer configuration does not correspond to LPduIdx */
      /* [cover parentID={8B03B6FA-1579-4145-84F7-13793B73D920}]
      Mark the return value as Error Detected
      [/cover] */
      RetValue = E_NOT_OK;
    }
  }

  return RetValue;
}

/*******************************************************************************
** Traceability    : [cover parentID={CA124F75-8478-4513-A9E3-5C0703316779}]  **
**                                                                            **
** Syntax          : static Std_ReturnType Fr_17_Eray_lTransmitTxLPdu(        **
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
** Service ID      :  NA                                                      **
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
static Std_ReturnType Fr_17_Eray_lTransmitTxLPdu(const uint8 Fr_CtrlIdx,
                                          const uint16 Fr_LPduIdx,
                                          const uint8 * const Fr_LSduPtr,
                                          const uint8 Fr_LSduLength)
{
  Std_ReturnType RetValue;
  uint8 MsgBuffIdx;
  uint8  AllowDynamicLSduLengthFlag;
  uint8 PlcBytes;
  uint8 LogIdx;
  volatile uint8 IbsyhZero;
  const Fr_17_Eray_LPduConfigType *LPduCfgPtr;
  uint8 ConfigPlcBytes;

  /* [cover parentID={795E5A87-AD98-4d38-9F58-38E1B4453BE8}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_OFF)
  RetValue = E_OK;
  #else
  RetValue = Fr_17_Eray_lTransmitDetCheck(Fr_CtrlIdx, Fr_LPduIdx, Fr_LSduPtr);

  /* [cover parentID={5949081A-77A7-4ef0-ADE4-7F8124C9E5E6}]
  [/cover] */
  /* [cover parentID={2A581CB7-E1BB-47cd-B5FF-2DFC73634A67}]
  Any DET Error occurred ?
  [/cover] */
  if(RetValue == E_OK)
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_OFF) */
  {
    /* [cover parentID={B7AC9CBA-E45D-495d-8629-EEA3F9E63A40}]
    Get the logical index from map array
    [/cover] */
    LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];

    LPduCfgPtr = Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].LPduConfigPtr;

    ConfigPlcBytes = (uint8)((LPduCfgPtr[Fr_LPduIdx].Wrhs2CfgVal >>
                  IFX_ERAY_WRHS2_PLC_OFF) & IFX_ERAY_WRHS2_PLC_MSK);

    /* [cover parentID={4F9DD923-8AC4-45a1-9D88-D855524E8631}]
    Get the message buffer index that corresponds to the LPdu Index
    [/cover] */
    /* Figure out the message buffer corresponding to LPduIdx */
    MsgBuffIdx =
      Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].LPduIdx2MsgBuffIdxPtr[Fr_LPduIdx];

    /* Payload Length Configured in bytes */
    PlcBytes = (uint8)(ConfigPlcBytes * FR_17_ERAY_BYTES_PER_HALFWORD);

    /* DynamicLength Reduction Configuration  */
    AllowDynamicLSduLengthFlag = (uint8)((LPduCfgPtr[Fr_LPduIdx].Wrhs2CfgVal>>
                        FR_17_ERAY_WRHS2_ALLOWDYN_OFFSET) &
                        FR_17_ERAY_WRHS2_ALLOWDYN_MASK);

    /* [cover parentID={FB6F889B-6808-42ad-9D8C-7C4B81F65903}]
    Is the LPdu 'Reconfigurable' ? AND
    Is the allow dynamic LSduLength parameter disabled?
    [/cover] */
    if ((LPduCfgPtr[Fr_LPduIdx].LpduReconfigurable ==
                  (uint8)FR_17_ERAY_LPDU_RECONFIGURABLE) &&
                  (AllowDynamicLSduLengthFlag != FR_17_ERAY_DEC_ONE))
    {
      /*Read Header only */
      RetValue = Fr_17_Eray_lReadHeader(Fr_CtrlIdx, Fr_LPduIdx);

      /* [cover parentID={08D51CDF-EE6D-4278-AC05-2CACB7E4B2D2}]
      Is a Timeout Error Detected ?
      [/cover] */
      if (RetValue != E_OK)
      {
        PlcBytes = FR_17_ERAY_DEC_ZERO;
      }
      else
      {
        PlcBytes = (uint8)
         ((uint8)ERAY[Fr_CtrlIdx]->RDHS2.B.PLC * FR_17_ERAY_BYTES_PER_HALFWORD);
      }
    }

    #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
    /* [cover parentID={CA66C540-0173-4b9d-8E0A-12341CD2BC0C}]
    Is there No Error from the Previous Step AND Is the LSdu length greater
    than the configured payload length ?
    [/cover] */
    /* FR_17_ERAY_E_INV_LENGTH */
    if ((RetValue == E_OK) && (Fr_LSduLength > PlcBytes))
    {
      /* [cover parentID={11F45844-2BED-4a37-83ED-D906B6CC68D3}]
      Report DET
      [/cover] */
      (void)Det_ReportError(FR_17_ERAY_MODULE_ID, FR_17_ERAY_INSTANCE_ID,
                      FR_17_ERAY_SID_TRANSMITTXLPDU, FR_17_ERAY_E_INV_LENGTH);

      /* [cover parentID={5219C4AC-097A-4a01-899A-EC2D74E18A9B}]
      Mark the return value as Error Detected
      [/cover] */
      RetValue = E_NOT_OK;
    }
    #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */
    /* [cover parentID={E39A6AFB-F962-4ad1-B40C-9A5420114A29}]
    Is there Any Error from the previous step ?
    [/cover] */
    if(RetValue == E_OK)
    {
      /* [cover parentID={1DB762A9-B4E0-4713-819C-E7A51AEBC642}]
      Does present message buffer configuration correspond to LPdu Index?
      [/cover] */
      if (Fr_17_Eray_MsgBuff2LPduIdxPtr[Fr_CtrlIdx][MsgBuffIdx] == Fr_LPduIdx)
      {
        /* Is host side input buffer free? */
        IbsyhZero = ERAY[Fr_CtrlIdx]->IBCR.B.IBSYH;

        /* [cover parentID={75F2648E-3011-4f23-865C-C1D535A450FF}]
        Is the Input Host buffer free ?
        [/cover] */
        if (IbsyhZero == (uint8)0U)
        {
          /* [cover parentID={30D8111E-DE05-455f-BC92-83875DD3C55E}]
          Is the LPdu configured to support dynamic LSdu length ?
          [/cover] */
          if (AllowDynamicLSduLengthFlag == 1U)
          {
            /* [cover parentID={5DCD5945-35CF-4448-967C-511F01B01221}]
            Invoke routine to update header section with dynamic LSdu length
            [/cover] */
            RetValue = Fr_17_Eray_lUpdateDyLSduLength(Fr_CtrlIdx, LogIdx,
                                               Fr_LPduIdx, Fr_LSduLength);
          }

          /* [cover parentID={65ED6FEF-3AA0-4287-A6CD-F614FB818516}]
          Any Error Detected ?
          [/cover] */
          if (RetValue == E_OK)
          {
            /* [cover parentID={8D73DD3F-5544-4a5b-9A8E-E4A514141F03}]
            Invoke routine to update the data section and request
            for transmission [/cover] */
            RetValue = Fr_17_Eray_lUpdateTransmitData(Fr_CtrlIdx, Fr_LPduIdx,
                                     Fr_LSduPtr, Fr_LSduLength, PlcBytes);
          }
        }
        else
        {
          /* [cover parentID={97C3F0AF-CB0F-4211-B90E-B8EB31F4C204}]
          Mark the return value as Error Detected
          [/cover] */
          /* Host side input buffer is NOT free */
          RetValue = E_NOT_OK;
        }
      }
      else
      {
        /* [cover parentID={5219C4AC-097A-4a01-899A-EC2D74E18A9B}]
        Mark the return value as Error Detected
        [/cover] */
        /* Current message buffer configuration does not correspond to
           LPduIdx */
        RetValue = E_NOT_OK;
      }
    }
  }

  return RetValue;
}

/*******************************************************************************
** Traceability    : [cover parentID={AF55A412-BAD2-4d81-B6A3-2BBC663AD9DA}]  **
**                                                                            **
** Syntax          : static Std_ReturnType Fr_17_Eray_lReceiveRxLPdu(         **
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
** Service ID      :  NA                                                      **
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
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Fr_17_Eray_lReceiveRxLPdu(
                                  const uint8 Fr_CtrlIdx,
                                  const uint16 Fr_LPduIdx,
                                  uint8 * const Fr_LSduPtr,
                                  Fr_RxLPduStatusType *const Fr_RxLPduStatusPtr,
                                  uint8 * const Fr_LSduLengthPtr
                                  )
{
  uint32 NdatRegId;
  uint32 NdatRegMsgBuffIdPos;
  uint8 MsgBuffIdx;
  Std_ReturnType RetValue;
  uint8 ChannelIdx;
  uint8 LogIdx;
  #if (FR_17_ERAY_FIFO_CONFIGURED == STD_ON)
  uint8 FifoDepth;
  #endif

  #if (FR_17_ERAY_FIFO_CONFIGURED == STD_ON)
  FifoDepth = FR_17_ERAY_DEC_ZERO;
  #endif

  /* [cover parentID={78CE3C25-DB87-4c56-BF9A-FB5EC4C235FD}]
  DET Enabled
  [/cover] */
  #if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
  RetValue = Fr_17_Eray_lReceiveDetCheck(Fr_CtrlIdx, Fr_LPduIdx, Fr_LSduPtr,
                                         Fr_RxLPduStatusPtr, Fr_LSduLengthPtr);

  /* [cover parentID={22DAE576-07B3-4540-AB09-EA46F0A010E2}]
  Any DET Error detected
  [/cover] */
  if(RetValue == E_OK)
  #else
  RetValue = E_OK;
  #endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */
  {

    LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];

    /* Figure out the message buffer corresponding to LPduIdx */
    /* [cover parentID={E23C5B26-BB16-49a2-A0CB-ACC42F198588}]
    Determine the message buffer index that corresponds to the LPdu index
    [/cover] */
    MsgBuffIdx = Fr_17_Eray_ConfigPtr->
      CfgPtr[LogIdx].LPduIdx2MsgBuffIdxPtr[Fr_LPduIdx];

    /* [cover parentID={741A2828-3EF1-4007-ACE0-A0A02DC226AE}]
    FIFO is Configured
    [/cover] */
    #if (FR_17_ERAY_FIFO_CONFIGURED == STD_ON)
    /* [cover parentID={D202BA68-F283-4449-ACDE-C1EC073CDB14}]
    Is the Receive FIFO pointer NULL ?
    [/cover] */
    if (Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].RxFifoConfigPtr != NULL_PTR)
    {
      /* [cover parentID={03B0246F-E2BC-4230-88D9-75352965A522}]
      Get the FIFO depth value
      [/cover] */
      FifoDepth = Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].\
                                         RxFifoConfigPtr->FrFifoDepth;
    }

    /* [cover parentID={DBAB2FD3-D0C1-4b3b-8CD5-61EEA3A75FEE}]
    If (FIFO depth is non-zero) AND (message buffer index corresponds to FIFO)
    [/cover] */
    if((FifoDepth > FR_17_ERAY_DEC_ZERO)
          && (MsgBuffIdx == FR_17_ERAY_FIFO_MESG_BUF_ID))
    {
      /* [cover parentID={DAFE7153-99E3-4bf4-9D78-E4B215181D55}]
      Receive FIFO Operation
      [/cover] */
      /* MsgBuffIdx is stored as 0xFF for FIFO */
      /*If it is not a FIFO,then continue with normal Receive,
         else go to receive Fifo*/
      RetValue = Fr_17_Eray_lReceiveRxFifo(Fr_CtrlIdx, Fr_LPduIdx,
                     Fr_LSduPtr, Fr_RxLPduStatusPtr, Fr_LSduLengthPtr);
    }
    else
    #endif
    {
      /* [cover parentID={25D3FB3D-B083-4176-A26F-0B6D8C9F207C}]
      Does the present message buffer configuration correspond to LPdu index?
      [/cover] */
      /* Does current message buffer configuration correspond to LPduIdx? */
      if (Fr_17_Eray_MsgBuff2LPduIdxPtr[Fr_CtrlIdx][MsgBuffIdx] == Fr_LPduIdx)
      {
        /* Figure out the NDAT register corresponding to MsgBuffIdx */
        NdatRegId = (uint32)MsgBuffIdx >> FR_17_ERAY_MSG_BUFF_ID_SHIFT;

        /* Figure out the bit, corresponding to MsgBuffIdx, in NDAT register */
        /* Note: ANDing with 0x1F ==> MOD operation */
        NdatRegMsgBuffIdPos = (uint32)MsgBuffIdx & FR_17_ERAY_MSG_BUFF_ID_MASK;

        /* [cover parentID={8FDE35A7-17CE-4c0e-B5D3-3AC01756595D}]
        Is New data received for the Lpdu Index?
        [/cover] */
        /* Check if new data is received */
        if (((&ERAY[Fr_CtrlIdx]->NDAT1)[NdatRegId].U &
             ((uint32)1 << NdatRegMsgBuffIdPos)) != (uint32)0U)
        {
          RetValue = Fr_17_Eray_lRxTransferToOBF(Fr_CtrlIdx, Fr_LPduIdx,
                                                            MsgBuffIdx);

          /* [cover parentID={C167FF97-FDF7-4adb-88E4-B6EEC985CD63}]
          Any Error detected ?
          [/cover] */
          if (RetValue == E_OK)
          {

#if(MCAL_AR_VERSION == MCAL_AR_440)
            ChannelIdx = (uint8)((Fr_17_Eray_ConfigPtr->
               CfgPtr[LogIdx].LPduConfigPtr[Fr_LPduIdx].Wrhs1CfgVal >>
               IFX_ERAY_WRHS1_CHA_OFF) & FR_17_ERAY_WRHS1_CHANNEL_MASK);
#else
            /* [cover parentID={C79276EE-D430-4cc3-9DF7-86F0AA9B90D8}]
            Subtract 1 to correct the channel as per Fr_ChannelType enum in
            AUTOSAR 4.2.2, to be used for further processing
            [/cover] */
            ChannelIdx = (uint8)(((Fr_17_Eray_ConfigPtr->
              CfgPtr[LogIdx].LPduConfigPtr[Fr_LPduIdx].Wrhs1CfgVal >>
               IFX_ERAY_WRHS1_CHA_OFF) & FR_17_ERAY_WRHS1_CHANNEL_MASK) -
                                                             (uint8)0x1);
#endif

            /* [cover parentID={2DE82AEB-D477-4e5e-8FDD-2500111EB570}]
            perform acceptance check for receive operation
            [/cover] */
            RetValue = Fr_17_Eray_lRxAcceptanceCheck(Fr_CtrlIdx, ChannelIdx);

            /* [cover parentID={6B4D1EAC-2821-4ea5-97D2-410AC4CA5957}]
            Any Error detected ?
            [/cover] */
            if(RetValue == E_OK)
            {
              /* [cover parentID={90C73480-2E92-405a-9F00-37D5B3D383B2}]
              Copy the received data to the address Fr_LSduPtr and
              store the number of bytes to Fr_LSduLengthPtr
              [/cover] */
              Fr_17_Eray_lReceiveDataCopy(Fr_CtrlIdx, Fr_LSduPtr,
                                                Fr_LSduLengthPtr);

              /* [cover parentID={89E853BD-8693-4e51-A345-E98079404D45}]
              Write FR_RECEIVED to the LSdu Status pointer
              [/cover] */
              *Fr_RxLPduStatusPtr = FR_RECEIVED;
              /* [cover parentID={D47A621D-2765-48ee-9CA5-4A612427682B}]
              Return value is E_OK
              [/cover] */
            }
            else
            {
              /* [cover parentID={0F52C893-8536-427e-BB8A-B1F39727F37D}]
              Set the LSdu length pointer to zero and LPdu Status Pointer
              to FR_NOT_RECEIVED
              [/cover] */
              *Fr_LSduLengthPtr = FR_17_ERAY_DEC_ZERO;
              *Fr_RxLPduStatusPtr = FR_NOT_RECEIVED;
            }
          }
        }
        else
        {
          /* [cover parentID={FC865CD2-5275-4bb1-A3DF-239576F3CFFC}]
          Initialize the LSdu length pointer to zero and LPdu Status Pointer
          to FR_NOT_RECEIVED
          [/cover] */
          *Fr_LSduLengthPtr = FR_17_ERAY_DEC_ZERO;
          *Fr_RxLPduStatusPtr = FR_NOT_RECEIVED;
        }
      }
      else
      {
        /* [cover parentID={927D1E67-AD9A-48bb-9FE3-FCD02FB637DA}]
        Mark the return value as Error detected
        [/cover] */
        /* Current message buffer configuration does not correspond to
         LPduIdx */
        RetValue = E_NOT_OK;
      }
    }
  }
  return RetValue;
}

#if(FR_17_ERAY_EXTENDED_LPDU_REPORTING == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID={226DFD08-0C02-40ff-A11D-7377ACA68A2A}]  **
**                                                                            **
** Syntax          : static Std_ReturnType Fr_17_Eray_lExtendedLPduReporting( **
**                          const uint8 Fr_CtrlIdx,                           **
**                          const uint16 Fr_LPduIdx,                          **
**                          Fr_SlotAssignmentType * const Fr_SlotAssignmentPtr**
**                          )                                                 **
**                                                                            **
** Description     : Update Fr_SlotAssignmentPtr for extended LPdu reporting  **
**                   support                                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  NA                                                      **
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
**                  Fr_SlotAssignmentPtr - This reference points to the memory**
**                           location where current slotid, cycle count and   **
**                           channelID shall be stored.                       **
**                                                                            **
** Return value    :  E_OK: API call finished successfully.                   **
**                    E_NOT_OK: API call aborted due to errors.               **
*******************************************************************************/
static Std_ReturnType Fr_17_Eray_lExtendedLPduReporting(
                            const uint8 Fr_CtrlIdx,
                            const uint16 Fr_LPduIdx,
                            Fr_SlotAssignmentType * const Fr_SlotAssignmentPtr
                            )
{
  uint8 LogIdx;
  const Fr_17_Eray_LPduConfigType *LPduCfgPtr;
  Std_ReturnType RetValue;
  uint32 ChnlType;

  LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];

  LPduCfgPtr = Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].LPduConfigPtr;

  /* [cover parentID={75DDE63A-839F-409b-A89C-9164CE0ADF3D}]
  Is the LPdu 'Reconfigurable' ? AND
  [/cover] */
  /* [cover parentID={FB6F889B-6808-42ad-9D8C-7C4B81F65903}]
  Is the LPdu 'Reconfigurable' ? AND
  [/cover] */
  if ((LPduCfgPtr[Fr_LPduIdx].LpduReconfigurable ==
                  (uint8)FR_17_ERAY_LPDU_RECONFIGURABLE))
  {
    /* [cover parentID={CE813722-CB43-4218-B27A-D30B8DBCB336} ]
    Mark the return value as Error detected
    [/cover] */
    /* [cover parentID={9022D430-E0B2-4c5c-B745-5AFE71DED8C0} ]
    Mark the return value as succesfully finished
    [/cover] */
    RetValue = Fr_17_Eray_lReadHeader(Fr_CtrlIdx, Fr_LPduIdx);
    /* [cover parentID={0D585365-C2FD-41fb-8023-B3C525AFA7CD} ]
    Is read header updated successfully ?
    [/cover] */
    if(RetValue == E_OK)
    {
      /*Update LPdu configured cycle count to Fr_SlotAssignmentPtr*/
      Fr_SlotAssignmentPtr->SlotId =  ERAY[Fr_CtrlIdx]->RDHS1.B.FID;

      /*Update LPdu configured Slot ID to Fr_SlotAssignmentPtr*/
      Fr_SlotAssignmentPtr->Cycle =  ERAY[Fr_CtrlIdx]->RDHS1.B.CYC;

      ChnlType = ((ERAY[Fr_CtrlIdx]->RDHS1.U >> IFX_ERAY_WRHS1_CHA_OFF)
      & FR_17_ERAY_WRHS1_CHANNEL_MASK);

      Fr_SlotAssignmentPtr->ChannelId = Fr_17_Eray_lCheckChannelType(ChnlType);
    }
  }
  else
  {
    /*Update LPdu configured cycle count to Fr_SlotAssignmentPtr*/
    Fr_SlotAssignmentPtr->Cycle = (uint8)((Fr_17_Eray_ConfigPtr->
    CfgPtr[LogIdx].LPduConfigPtr[Fr_LPduIdx].Wrhs1CfgVal >>
    IFX_ERAY_WRHS1_CYC_OFF) & IFX_ERAY_WRHS1_CYC_MSK);

    /*Update LPdu configured Slot ID to Fr_SlotAssignmentPtr*/
    Fr_SlotAssignmentPtr->SlotId = (uint16)((Fr_17_Eray_ConfigPtr->
    CfgPtr[LogIdx].LPduConfigPtr[Fr_LPduIdx].Wrhs1CfgVal)
    & IFX_ERAY_WRHS1_FID_MSK);

    ChnlType = ((Fr_17_Eray_ConfigPtr->
    CfgPtr[LogIdx].LPduConfigPtr[Fr_LPduIdx].Wrhs1CfgVal>>
    IFX_ERAY_WRHS1_CHA_OFF) & FR_17_ERAY_WRHS1_CHANNEL_MASK);

    Fr_SlotAssignmentPtr->ChannelId = Fr_17_Eray_lCheckChannelType(ChnlType);

    RetValue = E_OK;
  }
  return RetValue;
}

/*******************************************************************************
** Traceability    : [cover parentID={0AF7F506-6C95-459e-B5E4-4EFDE58A59FB}]  **
**                                                                            **
** Syntax          : static Fr_ChannelType Fr_17_Eray_lCheckChannelType       **
**                   (uint32 Fr_ChannelId)                                    **
**                                                                            **
** Description     : To check configured FlexRay channel type                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  NA                                                      **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant for the same device                       **
**                                                                            **
** Parameters (in) : Fr_ChannelId - FR Channel ID configured                  **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  FR_CHANNEL_A: FR channel A selected                     **
**                    FR_CHANNEL_A: FR channel B selected                     **
**                    FR_CHANNEL_AB: FR channel A and B selected              **
*******************************************************************************/
static Fr_ChannelType Fr_17_Eray_lCheckChannelType(uint32 Fr_ChannelId)
{
  Fr_ChannelType Fr_ChnlType;
  /* [cover parentID={2A11D8A9-F57B-465c-926F-0B4F8867B6CF}]
  Is configured Channel ID is FR_17_ERAY_CHANNEL_A?
  [/cover] */
  if(Fr_ChannelId == FR_17_ERAY_CHANNEL_A)
  {
    Fr_ChnlType =  FR_CHANNEL_A;
  }
  /* [cover parentID={B4159FD8-705F-48dd-99CA-574157DBA93A}]
  Is configured Channel ID is FR_17_ERAY_CHANNEL_B?
  [/cover] */
  else if(Fr_ChannelId == FR_17_ERAY_CHANNEL_B)
  {
    Fr_ChnlType = FR_CHANNEL_B;
  }
  else
  {
    Fr_ChnlType = FR_CHANNEL_AB;
  }

  return Fr_ChnlType;
}
#endif /* (FR_17_ERAY_EXTENDED_LPDU_REPORTING == STD_ON) */
/*******************************************************************************
** Traceability    : [cover parentID={77FA4929-9AC6-47c5-B69D-108ED16C2834}]  **
**                                                                            **
** Syntax          : static Std_ReturnType                                    **
**                          Fr_17_Eray_lReadHeader(                           **
**                          const uint8 Fr_CtrlIdx,                           **
**                          const uint16 Fr_LPduIdx                           **
**                          )                                                 **
**                                                                            **
** Description     : Request for the transfer of only the header section      **
**                   from the indexed message buffer to the output shadow     **
**                   buffer                                                   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  NA                                                      **
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
*******************************************************************************/
static Std_ReturnType Fr_17_Eray_lReadHeader(const uint8 Fr_CtrlIdx,
                                             const uint16 Fr_LPduIdx)
{
  uint8 LogIdx;
  Std_ReturnType RetValue;
  uint8 MsgBuffIdx;

  LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];

  /* Get the message buffer index that corresponds to the LPdu Index */
  MsgBuffIdx =
  Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].LPduIdx2MsgBuffIdxPtr[Fr_LPduIdx];

  /*Read Header only */
  /* Request for the transfer of only the header section from the indexed
     message buffer to the output shadow buffer */
  ERAY[Fr_CtrlIdx]->OBCM.B.RHSS = FR_17_ERAY_DEC_ONE;

  /* Request transfer of Message Buffer MsgBuffIdx to OBF Shadow buffer */
  ERAY[Fr_CtrlIdx]->OBCR.B.OBRS = MsgBuffIdx;
  ERAY[Fr_CtrlIdx]->OBCR.B.VIEW = FR_17_ERAY_DEC_ZERO;
  ERAY[Fr_CtrlIdx]->OBCR.B.REQ = FR_17_ERAY_DEC_ONE;

  /* Wait until transfer is complete */
  RetValue = Fr_17_Eray_lWaitTransferComplete(Fr_CtrlIdx, LogIdx);

  /* [cover parentID={233E954D-E4FE-407a-9ACE-1934E0C4AC01}]
  [/cover] */
  /* [cover parentID={08D51CDF-EE6D-4278-AC05-2CACB7E4B2D2}]
  Is a Timeout Error Detected ?
  [/cover] */
  if (RetValue == E_OK)
  {
    /* Clear the transfer request */
    ERAY[Fr_CtrlIdx]->OBCR.B.REQ = FR_17_ERAY_DEC_ZERO;

    /* Swap the host and shadow buffer */
    ERAY[Fr_CtrlIdx]->OBCR.B.VIEW = FR_17_ERAY_DEC_ONE;
  }

  return RetValue;
}

#if (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID={280AD5DE-15EF-4d5d-8CC2-BF778BCEBB82}]  **
**                                                                            **
** Syntax          : Std_ReturnType Fr_17_Eray_lCheckTxLPduDetCheck(          **
**                       const uint8 Fr_CtrlIdx,                              **
**                       const uint16 Fr_LPduIdx,                             **
**                       const Fr_TxLPduStatusType * const Fr_TxLPduStatusPtr **
**                         )                                                  **
**                                                                            **
** Description     : Checks for development error conditions of               **
**                          Fr_17_Eray_CheckTxLPduStatus API                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  NA                                                      **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Reentrant                                               **
**                                                                            **
** Parameters (in) : Fr_CtrlIdx - Index of FlexRay CC within the context of   **
**                                the FlexRay Driver.                         **
**                   Fr_LPduIdx - This index is used to uniquely identify a   **
**                                  FlexRay frame.                            **
**                   Fr_TxLPduStatusPtr - This reference is used to store the **
**                                        transmit status of the LPdu         **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: No development error detected for input parameters **
**                   E_NOT_OK: Development error detected for one of the      **
**                              input parameters                              **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fr_17_Eray_lCheckTxLPduDetCheck(
                          const uint8 Fr_CtrlIdx,
                          const uint16 Fr_LPduIdx,
                          const Fr_TxLPduStatusType * const Fr_TxLPduStatusPtr
                                     )
{
  uint32 DevError;
  Std_ReturnType RetVal;
  uint8 LogIdx;

  /* [cover parentID={84C25C55-AE78-42b8-A18D-2AE0E197AA9F}]
  Check for Fr Initialization
  [/cover] */
  /* FR_17_ERAY_E_INIT_FAILED */
  DevError = Fr_17_Eray_lDetCheckNoInit(FR_17_ERAY_SID_CHECKTXLPDUSTATUS);

  /* [cover parentID={A0489795-4F45-4dda-B637-AD4023B9654B}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={9C071AC2-CABF-4b20-9E7D-A8E580B16941}]
    Check for validity of controller Index
    [/cover] */
    /* FR_17_ERAY_E_INV_CTRL_IDX */
    DevError = Fr_17_Eray_lDetCheckInvCtrlIdx(Fr_CtrlIdx,
                                            FR_17_ERAY_SID_CHECKTXLPDUSTATUS);
  }

  /* [cover parentID={01EB6486-94A1-4388-AC09-065AF677B469}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={38EB9699-E418-426b-AA9E-F659A8CD758A}]
    Check the validity of the LPdu index
    [/cover] */
    /* FR_17_ERAY_E_INV_LPDU_IDX */
    DevError = Fr_17_Eray_lDetCheckInvLPduIdx(Fr_CtrlIdx,Fr_LPduIdx,
                                            FR_17_ERAY_SID_CHECKTXLPDUSTATUS);
  }

  /*
    Invalid LPduIdx, avoid array out of bound access for
     Fr_17_Eray_ConfigPtr->CfgPtr[LogIdx].LPduConfigPtr[Fr_LPduIdx]
  */
  /* [cover parentID={3676EDC4-5C51-4da5-981F-AFC8C25814CF}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    LogIdx = Fr_17_Eray_ConfigPtr->Phy2LogIdxPtr[Fr_CtrlIdx];

    /* [cover parentID={2F6AAF95-8AE9-4868-824E-D32D2357F31B}]
    Is the direction of LPdu configured as receive ?
    [/cover] */
    /* FR_17_ERAY_E_INV_LPDU_IDX if its a receive message buffer */
    if (((Fr_17_Eray_ConfigPtr->
       CfgPtr[LogIdx].LPduConfigPtr[Fr_LPduIdx].Wrhs1CfgVal >>
       IFX_ERAY_WRHS1_CFG_OFF) & IFX_ERAY_WRHS1_CFG_MSK) == 0U)
    {
      /* [cover parentID={94B19427-CBA1-4441-8112-D6CD85460917}]
      Report DET
      [/cover] */
      (void)Det_ReportError(FR_17_ERAY_MODULE_ID, FR_17_ERAY_INSTANCE_ID,
                  FR_17_ERAY_SID_CHECKTXLPDUSTATUS, FR_17_ERAY_E_INV_LPDU_IDX);
      DevError = FR_17_ERAY_E_INV_LPDU_IDX;
    }
  }

  /* [cover parentID={7802AC88-BCD6-4027-BB35-9599710889FB}]
  No DET Error due to the previous check ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    /* [cover parentID={2E5450E2-E8C1-45df-8D30-9DC36D7A6D5B}]
    Check whether Tx LPdu status pointer is NULL
    [/cover] */
    /* FR_17_ERAY_E_PARAM_POINTER */
    DevError = Fr_17_Eray_lDetCheckInvPointer(
                 Fr_TxLPduStatusPtr, FR_17_ERAY_SID_CHECKTXLPDUSTATUS);
  }

  /* [cover parentID={7AE77C8F-5670-4850-8AD3-36FD572341EF}]
  Any DET Error detected from the previous checks ?
  [/cover] */
  if (DevError == FR_17_ERAY_E_DET_NO_ERR)
  {
    RetVal = E_OK;
  }
  else
  {
    /* [cover parentID={669F9F8E-0062-4910-AEA6-7E1E6922B250}]
    Mark the return value as Error detected
    [/cover] */
    RetVal = E_NOT_OK;
  }

  return RetVal;
}

#endif /* (FR_17_ERAY_DEV_ERROR_DETECT == STD_ON) */

/*----------------------------------------------------------------------------*/
/* Inapplicable requirements */
/* [cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
Memory mapping for callout code : No callout code present
[/cover] */

/*----------------------------------------------------------------------------*/

/* Memory Map of the FR Code */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
Memory mapping for code
[/cover] */
#define FR_17_ERAY_STOP_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Fr_17_Eray_MemMap.h"

/*******************************************************************************
**                               End of File                                  **
*******************************************************************************/
