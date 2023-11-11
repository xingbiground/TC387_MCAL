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
**  FILENAME     : Ocu_Local.h                                                **
**                                                                            **
**  VERSION      : 12.0.0                                                     **
**                                                                            **
**  DATE         : 2021-09-06                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Ocu Driver Local header definition file                    **
**                                                                            **
**  SPECIFICATION(S) :Specification of OCU Driver,AUTOSAR Release 4.2.2&4.4.0 **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}][/cover] */
/* [cover parentID={9888E3DF-2D83-4bd0-8169-11439BDA4F3B}] */
/*  [/cover] */
#ifndef OCU_LOCAL_H
#define OCU_LOCAL_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                             **
*******************************************************************************/
/* Channel status variable bit positions */
/* Position 0 - To indicate channel RUNNING or STOPPED */
#define OCU_CHNL_STATUS_POS                    (0x0U)
/* OCU_CHNL_STATUS_POS bit length */
#define OCU_CHNL_STATUS_BIT_LENGTH             0x2

/*Position 1,2 - Channel pin action */
#define OCU_CHNL_PIN_ACTION_POS                (0x2U)
/* OCU_CHNL_PIN_ACTION_POS bit length */
#define OCU_CHNL_PIN_ACTION_BIT_LENGTH         0x2

/* Position 3 - Notification Enable/Disable */
#define OCU_CHNL_NOTIF_PRESENCE_POS            (0x4U)
/* OCU_CHNL_NOTIF_PRESENCE_POS bit length */
#define OCU_CHNL_NOTIF_BIT_LENGTH              0x1

/* Position 4 - Indicate re-program of ATOM ISR */
#define OCU_CHNL_ATOM_RE_PROG_ISR_POS          (0x5U)
/* OCU_CHNL_NOTIF_PRESENCE_POS bit length */
#define OCU_CHNL_ATOM_RE_PROG_ISR_BIT_LENGTH   0x1


/* To denote channel has started */
#define OCU_CHANNEL_RUNNING                    (0x1U)
#define OCU_CHANNEL_START_IN_PROGRESS          (0x2U)
/* To denote channel has stopped */
#define OCU_CHANNEL_STOPPED                    (0x0U)

/* To indicate an error */
#define OCU_ERROR_FOUND                        (0x1U)
#define OCU_ERROR_NOT_FOUND                    (0x0U)

/* Mask for Core ID in channel map */
#define OCU_CHNL_MAP_CORE_ID_MASK              (0xF00UL)
#define OCU_CHNL_MAP_CORE_ID_OFFSET            (0x8U)
/* Mask for core specific channel index in channel map */
#define OCU_CHNL_MAP_CHNL_INDEX_MASK           ((uint8)0xFFUL)
#define OCU_CHNL_MAP_INVALID_CHNL_INDEX        (0xFFUL)

/* Status to indicate that OCU is initialized */
#define OCU_DEINITPENDING                      ((uint32)0x2)
/* Status to indicate that OCU is initialized */
#define OCU_INITIALIZED                        ((uint32)0x1)
/* Status to indicate that OCU is de-initailized */
#define OCU_DEINITIALIZED                      ((uint32)0x0)
/* Status to indicate that OCU is de-initailized */
#define OCU_INIT_STATUS_SIZE                    0x2

/* Clear all pending interrupts */
#define OCU_CLR_PENDING_NOTIFICATION_FLAGS     (0x00000003UL)


/* To enable the notification */
#define OCU_ENABLE_NOTIFICATION                (0x1U)
/* To disable the notification */
#define OCU_DISABLE_NOTIFICATION               (0x0U)

#define OCU_BIT_SET                            (0x1U)
#define OCU_BIT_RESET                          (0x0U)

#define OCU_GTM_ATOM_SL_BIT_POS                (0xBU)
#define OCU_GTM_ATOM_SL_LENGTH                 0x1
#define OCU_GTM_CLKSELECT_BIT_POS              (0xCU)
#define OCU_GTM_ATOM_MODE_SOMC                 (0x1U)
#define OCU_GTM_ATOM_MODE_SOMP                 (0x2U)
#define OCU_GTM_ATOM_ACB_NO_ACTION             (0x1C0U)
#define OCU_GTM_ATOM_TBU_TS2                   (0x4U)
#define OCU_GTM_TBU_MASK                       (0x8U)
#define OCU_ATOM_SOMC_ACB_4_3_2_LEN            0x3
#define OCU_ATOM_SOMC_ACB_4_3_2_MASK           (0x7U)
#define OCU_ATOM_SOMC_ACB_CANCEL_COMPARISIONS  (0x7U)
#define OCU_ATOM_SOMC_ACB_4_3_2_POS            (0x6U)
#define OCU_ATOM_SOMC_ACB_1_0_LEN              0x2
#define OCU_ATOM_SOMC_ACB_1_0_MASK             (0x3U)
#define OCU_ATOM_SOMC_ACB_1_0_POS              (0x4U)
#define OCU_ATOM_SOMC_ENABLE_FREEZE            (0x80000000U) 
#define OCU_ATOM_SOMC_DISABLE_FREEZE           (0x7FFFFFFFU)

#define OCU_LOWER_WORD_MASK                    (0xFFFFU)
#define OCU_LOWER_BYTE_MASK                    (0xFFU)
#define OCU_TOUT_ALT_SEL_BIT_POS               (0x10U)


#define OCU_TBU_LOW_RES                        (0x0U)

#define LOW_RES_BIT_SHIFT                      (0x3U)

#define GTM_TOM_TGC_FUPD_CTRL_FUPD_CTRL_LEN     (0x2U)
#define GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT_LEN   (0x2U)
#define GTM_TOM_TGC_ENDIS_CTRL_ENDIS_CTRL_LEN   (0x2U)
#define GTM_TOM_TGC_OUTEN_STAT_OUTEN_STAT_LEN   (0x2U)
#define GTM_TOM_TGC_OUTEN_CTRL_OUTEN_CTRL_LEN   (0x2U)
#define GTM_TGC_CHANNEL_MASK                    (0x7U)

#define GTM_TOM_CH_ENABLE_READ                  (0x3U)
#define GTM_TOM_CH_OUT_DISABLE_READ             (0x0U)

#define TOUTSEL_LEN                             (0x3U)
#define MCAL_SELx_TOUTSEL                       (0x8U)
#define GTM_TOUTSEL_SELx_LEN                    (0x4U)

#define GTM_ATOM_AGC_FUPD_CTRL_FUPD_CTRL_LEN    (0x2U)
#define GTM_ATOM_AGC_OUTEN_STAT_OUTEN_STAT_LEN  (0x2U)
#define GTM_ATOM_AGC_OUTEN_CTRL_OUTEN_CTRL_LEN  (0x2U)
#define GTM_ATOM_AGC_ENDIS_STAT_ENDIS_CTRL_LEN  (0x2U)
#define GTM_ATOM_AGC_ENDIS_CTRL_ENDIS_CTRL_LEN  (0x2U)

#define GTM_ATOM_CH_OUT_ENABLE_READ              (0x3U)
#define GTM_ATOM_CH_ENABLE_READ                  (0x3U)
#define GTM_ATOM_CH_OUT_DISABLE_READ             (0x0U)

#define GTM_TOM_CH_UPDATE_ENABLE                 (0x01U)
#define GTM_ATOM_CH_UPDATE_ENABLE                (0x01U)

#define GTM_TOM_CH_UPDATE_ENABLE_READ            (0x03U)
#define  GTM_ATOM_CH_UPDATE_ENABLE_READ          (0x03U)

#define GTM_ATOM_AGC_GLB_CTRL_UPEN_CTRL0_OFF     (0x10U)

#define ACB_SET_HIGH                             (0x02U)

#define ACB_SET_LOW                              (0x01U)

#define ATOM_MASK_LSB_24BITS                     (0xFFFFFFU)

#define TOM_MASK_LSB_16BITS                      (0xFFFFU)

#define ENABLE_INTERRUPTS                        (1U)

#define DISABLE_INTERRUPTS                       (0U)

#ifndef TRUE
#define TRUE                                     (1U)
#endif
#ifndef FALSE
#define FALSE                                    (0U)
#endif

#define GTM_CLR_PENDING_IRQ                      (3U)

#define CNT_BORDER_VAL_BT_PAST_FUTURE            (0x800000U)

#define IRQ_PULSE_NOTIFY_MODE                    ((uint32)0x2U)

#define ATOM_CCU0_IRQ_EN                         (0x1U)

#define ATOM_CCU1_IRQ_EN                         (0x2U)

#define ATOM_COMPARE_CCU0                        (0x2U)

#define ATOM_COMPARE_CCU1                        (0x3U)

#define CCU0_INT_NOTIFY_SET                      (0x1U)

#define CCU1_INT_NOTIFY_SET                      (0x2U)

/******************************************************************************
**                      Private Type Definitions                             **
******************************************************************************/
#if(OCU_MAX_CHANNELS != 0U)
/* [cover parentID={F8600121-A4B2-46e6-BD16-F75330FADFFE}]
[/cover] */
typedef struct
{
  /* Compare value for the channel */
  Ocu_ValueType CompareValue;
  /* channel status */
  uint32 Status;
} Ocu_ChannelVarType;
#endif

/******************************************************************************
**                               STUBS                                       **
******************************************************************************/
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro defined for easy
 * readability in code. No side effects foreseen by violating this MISRA rule.
 */
#define OCU_GETCOREID() ((uint8)(Mcal_GetCpuIndex()))



#endif /* OCU_LOCAL_H */
