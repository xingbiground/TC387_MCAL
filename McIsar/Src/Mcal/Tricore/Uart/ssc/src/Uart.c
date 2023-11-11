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
**  FILENAME     : Uart.c                                                     **
**                                                                            **
**  VERSION      : 34.0.0                                                     **
**                                                                            **
**  DATE         : 2023-05-24                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Uart driver source file.                                   **
**                                                                            **
**  SPECIFICATION(S):Specification of Uart driver, AUTOSAR Release4.2.2&4.4.0 **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={667124EB-C6C2-4ddd-B061-16464CBD86D6}]
[/cover] */
/* [cover parentID={2EAF6692-0C6B-47c3-9241-0E6FA442E362}]
[/cover] */
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Inclusion of SFR file */
#include "IfxAsclin_reg.h"
#include "IfxAsclin_bf.h"
/* Inclusion of mcal specific header files */
#include "McalLib.h"
/* UART driver header file */
#include "Uart.h"
/* Conditional inclusion for operating system header */
#if(UART_INIT_DEINIT_API_MODE != UART_SUPERVISOR_MODE)
#include "McalLib_OsStub.h"
#endif
/* Conditional inclusion of developement error tracer file */
#if (UART_DEV_ERROR_DETECT == STD_ON) 
#include "Det.h"
#endif

/* Include Mcal_Wrapper header file if runtime error is enabled */
#if (UART_RUNTIME_ERROR_DETECT == STD_ON)
#include"Mcal_Wrapper.h"
#endif
/* Conditional inclusion of safety error header */
/* [cover parentID= {16225CBD-29E1-4c54-91DA-FD91D2B6691B}]
Safety properties
[/cover] */
#if(UART_SAFETY_ENABLE == STD_ON)
#include "Mcal_SafetyError.h"
#endif

/* Scheduled functions header file */
#include "SchM_Uart.h"

/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/

/* [cover parentID={556980E1-0A03-42d9-906D-3CCABEADDC0C}]
[/cover] */
/* Version checks */
#ifndef UART_SW_MAJOR_VERSION
#error "UART_SW_MAJOR_VERSION is not defined. "
#endif
/* [cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}]
     [/cover] */
#ifndef UART_SW_MINOR_VERSION
#error "UART_SW_MINOR_VERSION is not defined. "
#endif

#ifndef UART_SW_PATCH_VERSION
#error "UART_SW_PATCH_VERSION is not defined."
#endif

#if (UART_SW_MAJOR_VERSION != 20U)
#error "UART_SW_MAJOR_VERSION does not match. "
#endif

#if (UART_SW_MINOR_VERSION != 25U)
#error "UART_SW_MINOR_VERSION does not match. "
#endif

#if (UART_SW_PATCH_VERSION != 0U)
#error "UART_SW_PATCH_VERSION does not match."
#endif
/* [cover parentID={FE57CB4E-B40A-4f42-B80F-09F3D2A2D55F}] */
/*  [/cover] */
/* Version check for DET module */
#if (UART_DEV_ERROR_DETECT == STD_ON)

#ifndef DET_AR_RELEASE_MAJOR_VERSION
#error "DET_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

/* [cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}]
     [/cover] */
#if ( DET_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION )
#error "DET_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

#endif

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/
/* [cover parentID={F01CBF38-51EF-4745-9313-7073F7E593E8}] */
/*  [/cover] */
/* UART channel transmit state. */
typedef enum
{
  /* UART channel in idle state (No transmit in progress) */
  UART_TX_IDLE,
  /* UART channel transmit preparation in progress. */
  UART_TX_PREP_IN_PROGRESS,
  /* UART channel transmit in progress. */
  UART_TX_IN_PROGRESS,
  /* UART channel TXFIFO copy in progress. */
  UART_TX_FIFO_COPY_IN_PROGRESS,
  /* UART channel transmit abort in progress.*/
  UART_TX_ABORT_IN_PROGRESS
} Uart_TxStateType;

/* [cover parentID={58619D4B-998E-49e0-9AA2-B609BE252FDA}] */
/*  [/cover] */
/* UART channel receive state. */
typedef enum
{
  /* UART Channel in idle state (No receive operation in progress) */
  UART_RX_IDLE,
  /* UART channel receive preparation in progress. */
  UART_RX_PREP_IN_PROGRESS,
  /* UART channel receive in progress. */
  UART_RX_IN_PROGRESS,
  /* UART channel RXFIFO copy in progress. */
  UART_RX_FIFO_COPY_IN_PROGRESS,
  /* UART channel receive abort in progress. */
  UART_RX_ABORT_IN_PROGRESS,
  /* UART channel stopstreaming in progress. */
  UART_RX_STOP_STREAMING_IN_PROGRESS
} Uart_RxStateType;

/* [cover parentID={D919E757-F884-4fba-A272-6119F74207CC}] */
/*  [/cover] */
/* Structure contains all required runtime information for transmit and receive
   operation.
*/
typedef struct
{
  /* Receive buffer pointer */
  Uart_MemType *RxBuffPtr;
  /* Transmit buffer pointer */
  Uart_MemType *TxBuffPtr;
  /* Channel Transmit state */
  Uart_TxStateType ChanTxState;
  /* Channel receive state */
  Uart_RxStateType ChanRxState;
  /* Number of bytes pending to transmit */
  Uart_SizeType TxDataLeft;
  /* Number of bytes pending to receive */
  Uart_SizeType RxDataLeft;
  #if(UART_RECEIVE_STREAMING_MODE_API == STD_ON)
  /* Application buffer size */
  Uart_SizeType RxBufSize;
  /* Channel receive mode */
  uint8 ChanRxMode;
  #endif
  /* Number of bytes transmited */
  Uart_SizeType TotalDataTxd;
  /* Number of bytes received */
  Uart_SizeType TotalDataRxd;
  /* Interrupt level set for RXFIFO  */
  uint8 RxIntLevel;
  /* Receive notification triggered */
  uint8 RxNotfn;
} Uart_ChannelInfoType;

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
#if ((UART_DEV_ERROR_DETECT == STD_ON) || (UART_SAFETY_ENABLE == STD_ON))
/* Uart Driver not initialized */
#define UART_UNINITIALISED                0x0U
/* Uart Driver is initialized */
#define UART_INITIALISED                  0x01U
#endif
/* UART FIFO Buffer Size */
#define UART_BUFFER_SIZE                  (16U)
/* Mask for DISS bit mask */
#define UART_CLC_DISS_MASK                0x00000002U
/* Mask for receive parity error */
#define UART_FLAGS_PE_MASK                0x00010000U
/* Mask for receive frame error */
#define UART_FLAGS_FE_MASK                0x00040000U
/* DISS bit position */
#define UART_CLC_DISS_BITPOS              1U
/* Mask to check receive error */
#define UART_FLAGS_READ_ERROR             0x04050000U
/* No Clock  */
#define UART_CSRREG_CLKSEL_NOCLK          (0U)
/* ASCLIN INIT mode */
#define UART_FRAMECONREG_INIT_MODE        (0U)
#define UART_FRAMECONREG_ASCLIN_MODE      (1U)

/* Digital glitch filter disabled */
#define UART_IOCRREG_DEPTH_VAL            (0U)

#define UART_BITCONREG_SM_VAL             (1U)
#if((UART_TX_MODE != UART_POLLING_MODE)||(UART_RX_MODE != UART_POLLING_MODE))
/* Invalid channel identifier */
#define UART_INVALID_CHANNEL              (0xFFU)
#endif

/* Inlet and outlet width for FIFO depending on the data length congfigured */
#define UART_TXFIFOCONREG_INW_2BYTE       (2U)
#define UART_RXFIFOCONREG_OUTW_2BYTE      (2U)
#define UART_STEPSIZE_2BYTE               (2U)
#define UART_TXFIFOCONREG_INW_1BYTE       (1U)
#define UART_RXFIFOCONREG_OUTW_1BYTE      (1U)
#define UART_STEPSIZE_1BYTE               (1U)

/* FIFO operating interrupt mode */
#if((UART_TX_MODE != UART_POLLING_MODE)||(UART_RX_MODE != UART_POLLING_MODE))
#define UART_COMBINED_MOVE_MODE           (0U)
#endif

/* Define to set and clear bit */
#define UART_SET_BIT                      (1U)
#define UART_CLEAR_BIT                    (0U)

/* Define for 9 bit frame length configured */
#define UART_NINEBIT_DATLEN               (9U)
/* Macro to check overflow of STM timer */
#define UART_STM_TICK_OVERFLOW            0xFFFFFFFFU

/* RXFIFO buffer interrupt level is set to store 16 bytes */
#define UART_RX_FIFO_INT_LEVEL_MAX        (15U)

#if(UART_INIT_CHECK_API == STD_ON)
#define UART_FULLREG_MASK                 (0xFFFFFFFFU)
/* Mask to check erase function */
#define UART_IOCR_CFG_MASK                (0x3FFFFFFFU)
/* ASCLIN UART mode */
#define UART_FRAMECONREG_ASC_MODE         (0x00010000U)

#define UART_TXFIFOCONREG_FIFO_MODE         (0U)
#define UART_RXFIFOCONREG_FIFO_MODE         (0U)

/* Bit position of baud rate numrator */
#define UART_BRG_NUMERATOR_BITPOS           16U
/* Bit position of oversampling */
#define UART_BITCON_OVERSAMPLING_BITPOS     16U
/* Bit position of CTS enable  */
#define UART_IOCR_CTSEN_BITPOS              29U
/* Bit position of CTS polarity */
#define UART_IOCR_RCPOL_BITPOS              25U
#define UART_BITCON_SM_BITPOS               31U
/* Bit position of sample point */
#define UART_BITCON_SAMPLEPOINT_BITPOS      24U
/* Bit position of parity enable */
#define UART_FRAMECON_PEN_BITPOS            30U
/* Bit position of parity config */
#define UART_FRAMECON_ODD_BITPOS            31U
/* Bit position of channel idle */
#define UART_FRAMECON_IDLE_BITPOS           6U
/* Bit position of stop bits configuration */
#define UART_FRAMECON_STOP_BITPOS           9U
/* Bit position of TXFIFO input word config */
#define UART_TXFIFOCON_INW_BITPOS           6U
/* Bit position of RXFIFO output word config */
#define UART_RXFIFOCON_OUTW_BITPOS          6U
#endif
/* Shift by 8 bit position */
#define UART_SHIFT_EIGHT_BIT                8U
/* Shift by 1 bit position */
#define UART_SHIFT_ONE_BIT                  1U
/* Register type to check status bit */
#define UART_REG_TYPE_CSR                   0U
#define UART_REG_TYPE_KRST0                 1U
/* Receive notification status */
#define UART_RX_NOTFN_TRIGGERED             1U
#define UART_RX_NOTFN_NOT_TRIGGERED         0U
/* Set Mask for RXFIFO level, RXFIFO overflow, Parity error
and Farame error bit fields */
#define UART_PEE_FEE_RFLE_RFOE_MASK  (((uint32)IFX_ASCLIN_FLAGSENABLE_PEE_MSK  \
    << IFX_ASCLIN_FLAGSENABLE_PEE_OFF)  | ((uint32)IFX_ASCLIN_FLAGSENABLE_FEE_MSK  \
    << IFX_ASCLIN_FLAGSENABLE_FEE_OFF)  | ((uint32)IFX_ASCLIN_FLAGSENABLE_RFLE_MSK \
    << IFX_ASCLIN_FLAGSENABLE_RFLE_OFF) | ((uint32)IFX_ASCLIN_FLAGSENABLE_RFOE_MSK\
    << IFX_ASCLIN_FLAGSENABLE_RFOE_OFF))

#if (UART_RECEIVE_STREAMING_MODE_API == STD_ON)
/* Receive operating modes */
#define UART_RX_IN_READ_MODE                 1U
#define UART_RX_IN_STREAMING_MODE            2U

/* RXFIFO interrupt levels */
#define UART_RX_FIFO_INT_LEVEL_MIN          (0U)
#define UART_RX_FIFO_INT_LEVEL_ONE          (1U)
#define UART_RECEIVED_DATA_SIZE_ZERO        (0U)
#endif
/*******************************************************************************
**                         User Mode Macros                                   **
*******************************************************************************/
#if(UART_INIT_DEINIT_API_MODE == UART_SUPERVISOR_MODE)
/* Library APIs  */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 *'UART_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG'
 *defined for User mode support in code.
 *No side effects foreseen by violating this MISRA rule. */
#define UART_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(RegAdd,Data)   \
    Mcal_WritePeripEndInitProtReg(RegAdd,Data)
#else
/* Library APIs  */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 *'UART_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG'
 *defined for User mode support in code.
 *No side effects foreseen by violating this MISRA rule. */
#define UART_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(RegAdd,Data)   \
    MCAL_LIB_WRITEPERIPENDINITPROTREG(RegAdd,Data)
#endif

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                     Private Function Declaration                           **
*******************************************************************************/
/*Memory Map of the UART Code*/
#define UART_START_SEC_CODE_ASIL_B_LOCAL
/* [cover parentID={84FCEDA9-01F7-4f48-AC8B-47FFAF8417E4}] */
/*  [/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Uart_MemMap.h"

LOCAL_INLINE uint8 Uart_lHwInitClcReg(const uint8 HwUnit, const uint32 Value);
LOCAL_INLINE void Uart_lTrasmitComplete(
                         Ifx_ASCLIN *const HwModulePtr,
                         Uart_ChannelInfoType *const ChannelInfoPtr,
                         const Uart_ChannelConfigType *const ChannelConfigPtr);


#if (UART_RX_MODE != UART_POLLING_MODE)
LOCAL_INLINE void Uart_lDisableReadInterrupts(Ifx_ASCLIN *const HwModulePtr);
LOCAL_INLINE void Uart_lEnableReadInterrupts(Ifx_ASCLIN *const HwModulePtr);
#endif
#if (UART_TX_MODE != UART_POLLING_MODE)
LOCAL_INLINE void Uart_lEnableWriteInterrupts(Ifx_ASCLIN *const HwModulePtr);
#endif
LOCAL_INLINE void Uart_lClearReadInterrupts(Ifx_ASCLIN *const HwModulePtr);

#if(UART_INIT_CHECK_API == STD_ON)
LOCAL_INLINE Std_ReturnType Uart_lCheckChannelInfo(const uint8 Channel);
#endif

#if ((UART_DEV_ERROR_DETECT == STD_ON) || (UART_SAFETY_ENABLE == STD_ON))
static Uart_ReturnType Uart_lCheckSize(const uint8 Channel,
                                       const Uart_SizeType Size,
                                       const uint8 ApiId);
static void Uart_lReportError(const uint8 ApiId, const uint8 ErrorId);
static Uart_ReturnType Uart_lCheckDetError(const uint8 Channel,
                                           const Uart_SizeType Size,
                                           const uint8 ApiId,
                                           const Uart_MemType *const MemPtr);
static Uart_ReturnType Uart_lChannelCheck(const Uart_ChannelIdType Channel,
                                          const uint8 ApiId);
#endif
static void Uart_lReceiveError(
                          const Uart_ChannelConfigType *const ChannelConfigPtr,
                          Ifx_ASCLIN *const HwModulePtr,
                          Uart_ChannelInfoType *const ChannelInfoPtr);
static void Uart_lRead(Ifx_ASCLIN *const HwModulePtr,
                          Uart_ChannelInfoType *const ChannelInfoPtr,
                          const Uart_ChannelConfigType *const ChannelConfigPtr,
                          const uint8 ReceiveFillLevel);
static void Uart_lHwInit(const uint8 HwUnit,
                          const Uart_ChannelConfigType *const ChannelConfigPtr);
static void Uart_lWrite(Ifx_ASCLIN *const HwModulePtr,
                          Uart_ChannelInfoType *const ChannelInfoPtr,
                          const Uart_ChannelConfigType *const ChannelConfigPtr);
static void Uart_lHwInitKernelReg(Ifx_ASCLIN *const HwModulePtr);
static void Uart_lStatusTimeout(const uint32 WaitTicks,
                                const Ifx_ASCLIN *const HwModulePtr,
                                const uint8 RegisterType,
                                const uint8 ExpStatValue);
#if (UART_RECEIVE_STREAMING_MODE_API == STD_ON)
static void Uart_lReceiveStreamingData(Ifx_ASCLIN *const HwModulePtr,
                         Uart_ChannelInfoType *const ChannelInfoPtr,
                         const Uart_ChannelConfigType *const ChannelConfigPtr);
#endif
#define UART_STOP_SEC_CODE_ASIL_B_LOCAL
/* [cover parentID={84FCEDA9-01F7-4f48-AC8B-47FFAF8417E4}] */
/*  [/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Uart_MemMap.h"

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
#define UART_START_SEC_CONST_ASIL_B_LOCAL_32
/* [cover parentID={84FCEDA9-01F7-4f48-AC8B-47FFAF8417E4}] */
/*  [/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Uart_MemMap.h"

/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
 * Variable Section
 * [/cover]*/
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
 * Const Section
 * [/cover]*/
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
 * Const Section
 * [/cover]*/
static Ifx_ASCLIN *const Uart_HwModuleAddr[UART_MAX_HW_UNIT] = \
                                                        {UART_ASCLIN_REG_ADDR};
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
#define UART_STOP_SEC_CONST_ASIL_B_LOCAL_32
/* [cover parentID={84FCEDA9-01F7-4f48-AC8B-47FFAF8417E4}] */
/*  [/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Uart_MemMap.h"

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
#define UART_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_8
/* [cover parentID={84FCEDA9-01F7-4f48-AC8B-47FFAF8417E4}] */
/*  [/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Uart_MemMap.h"

#if ((UART_DEV_ERROR_DETECT == STD_ON) || (UART_SAFETY_ENABLE == STD_ON))


/* Uart driver status */
static uint8 Uart_InitStatus;
#endif

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
#define UART_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_8
/* [cover parentID={84FCEDA9-01F7-4f48-AC8B-47FFAF8417E4}] */
/*  [/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Uart_MemMap.h"


/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
#define UART_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
/* [cover parentID={84FCEDA9-01F7-4f48-AC8B-47FFAF8417E4}] */
/*  [/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Uart_MemMap.h"
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
 * Variable Section
 * [/cover]*/
static const Uart_ConfigType *Uart_ConfigPtr;

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
#define UART_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
/* [cover parentID={84FCEDA9-01F7-4f48-AC8B-47FFAF8417E4}] */
/*  [/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Uart_MemMap.h"


/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
#define UART_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_UNSPECIFIED
/* [cover parentID={84FCEDA9-01F7-4f48-AC8B-47FFAF8417E4}] */
/*  [/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Uart_MemMap.h header is included without safegaurd.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Uart_MemMap.h header included
as per Autosar guidelines. */
#include "Uart_MemMap.h"
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
 * Variable Section
 * [/cover]*/



/*
  Variable hold runtime information of all configured Uart channel
*/
static Uart_ChannelInfoType Uart_ChannelInfo[UART_NUM_OF_CHANNEL_CONFIGURED];
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
#define UART_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_UNSPECIFIED
/* [cover parentID={84FCEDA9-01F7-4f48-AC8B-47FFAF8417E4}] */
/*  [/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Uart_MemMap.h header is included without safegaurd.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Uart_MemMap.h header included
as per Autosar guidelines. */
#include "Uart_MemMap.h"


/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define UART_START_SEC_CODE_ASIL_B_LOCAL
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
 * Code Section
 * [/cover]*/
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
 * Code Section
 * [/cover]*/
/* [cover parentID={84FCEDA9-01F7-4f48-AC8B-47FFAF8417E4}] */
/*  [/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Uart_MemMap.h"

#if(UART_RX_MODE != UART_INTERRUPT_MODE)
/*******************************************************************************
** Traceability     : [cover parentID={456967D9-1FBD-4f77-A4DD-9504ACA2C981}] **
** Syntax : void Uart_MainFunction_Read(void)                                 **
**                                                                            **
** Service ID      : 224                                                      **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant.                                           **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
** Description     : Schedule function to handle receives operation in        **
**                                                            polling mode.   **
**                                                                            **
*******************************************************************************/
void Uart_MainFunction_Read(void)
{
  Ifx_ASCLIN *HwModulePtr;
  const Uart_ChannelConfigType *ChannelConfigPtr;
  Uart_ChannelInfoType *ChannelInfoPtr;
  uint8 ChannelNo;
  uint8 MaxChannel;
  uint8 RecFillLevel;

  /* [cover parentID={C4700399-EA88-4ab5-8207-0E644DEECC15}]
  [/cover] */
  #if ((UART_DEV_ERROR_DETECT == STD_ON) || (UART_SAFETY_ENABLE == STD_ON))
  /* [cover parentID={3F85D301-6E6E-4005-BBBF-750BFF5A0478}]
  [/cover] */
  /* Check uart driver is initialized  */
  if (Uart_InitStatus != UART_UNINITIALISED)
  #endif
  {
    MaxChannel = Uart_ConfigPtr->NoOfChannels;
    /* [cover parentID={B329C547-A528-4806-A7DD-34DC94401639}]
    [/cover] */
    /* [cover parentID={E5AC9002-587B-4adb-AA8A-D2B3FE6F45A2}]
    [/cover] */
    for(ChannelNo = 0U; ChannelNo < MaxChannel; ChannelNo++)
    {
      /* [cover parentID={C7EA5654-89C6-432a-B610-1E4769F25117}]
      [/cover] */
      ChannelConfigPtr = &(Uart_ConfigPtr->ChannelConfigPtr[ChannelNo]);
      ChannelInfoPtr = &Uart_ChannelInfo[ChannelNo];
      /* [cover parentID={805F8B64-6349-4ad9-B100-829DF0D4499B}]
        [/cover] */
      /* [cover parentID={4867DC0E-A15A-41df-9B43-F1E6832438A1}]
      [/cover] */
      /* Check read configure in polling mode and receive in progress */
      if((ChannelConfigPtr->RxMode == UART_POLLING_MODE) && \
          (ChannelInfoPtr->ChanRxState == UART_RX_IN_PROGRESS))
      {
        /* [cover parentID={478B9940-1E11-4491-9392-0DA847F27096}]
        [/cover] */
        HwModulePtr = Uart_HwModuleAddr[ChannelConfigPtr->HwModule];

        ChannelInfoPtr->ChanRxState = UART_RX_FIFO_COPY_IN_PROGRESS;
        /* [cover parentID={D0D7B9CC-6AF3-41ef-9B17-3EDFF9E5CE25}]
        [/cover] */
        /* Check receive error flag set */
        if((HwModulePtr->FLAGS.U & UART_FLAGS_READ_ERROR) != 0U)
        {
          /* [cover parentID={933BB46F-C0FB-432a-83DC-86589D86B31D}]
          [/cover] */
          Uart_lReceiveError(ChannelConfigPtr, HwModulePtr, ChannelInfoPtr);
        }
        else
        {
          /* [cover parentID={8F57F81E-4D27-4bde-845B-D70D307ED1E4}]
          [/cover] */
          /* Extract received data filled level */
          RecFillLevel = HwModulePtr->RXFIFOCON.B.FILL;

          /* [cover parentID={D9F69DD0-D2E3-4e4e-9A3B-79DF6170DD57}]
          [/cover] */
          /* Check receive refill interrupt set */
          if(RecFillLevel > 0U)
          {
            /* [cover parentID={EA15C5F0-1253-4425-901E-82AB43CA33DB}]
            [/cover] */
            #if(UART_RECEIVE_STREAMING_MODE_API == STD_ON)
            /* [cover parentID={33611D71-437C-4392-95AB-FD17B7C0DF11}]
            [/cover] */
            /* Check channel read operation in streaming mode */
            if(ChannelInfoPtr->ChanRxMode == UART_RX_IN_STREAMING_MODE)
            {
            /* [cover parentID={AB7A73EB-AA91-41da-B3BC-6EBA70A110C4}]
            [/cover] */
            /* Handle received data in streaming mode*/
            Uart_lReceiveStreamingData(HwModulePtr, ChannelInfoPtr, ChannelConfigPtr);
            }
            else
            #endif
            {
            /* [cover parentID={990828D2-2BB2-4e71-BB34-E149852A8249}]
            [/cover] */
            /* Handle received data in normal read mode*/
            Uart_lRead(HwModulePtr, ChannelInfoPtr, ChannelConfigPtr, \
                       RecFillLevel);
            }
          }

          /* [cover parentID={5B58E5F9-9227-4de2-9C55-77301895C56D}]
          [/cover] */
          if(ChannelInfoPtr->ChanRxState == UART_RX_FIFO_COPY_IN_PROGRESS)
          {
            ChannelInfoPtr->ChanRxState = UART_RX_IN_PROGRESS;
          }
        }
      }
    }
  }
}
#endif

#if(UART_TX_MODE != UART_INTERRUPT_MODE)
/*******************************************************************************
** Traceability     : [cover parentID={5A0157F4-1D27-4361-A8F7-B90D1F20459B}] **
** Syntax : void Uart_MainFunction_Write(void)                                **
**                                                                            **
** Service ID      : 225                                                      **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant.                                           **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
** Description     : Schedule function to handle transmits operation in       **
**                                                             polling mode.  **
**                                                                            **
*******************************************************************************/
void Uart_MainFunction_Write(void)
{
  Ifx_ASCLIN *HwModulePtr;
  const Uart_ChannelConfigType *ChannelConfigPtr;
  Uart_ChannelInfoType *ChannelInfoPtr;
  uint8 CfgCount;
  uint8 MaxChannel;
  uint8 TxComplete;
  /* [cover parentID={2AF35BFD-01DF-4c12-8AB4-92C145D390DE}]
  [/cover] */
  #if ((UART_DEV_ERROR_DETECT == STD_ON) || (UART_SAFETY_ENABLE == STD_ON))
  /* [cover parentID={B54349C7-A51B-4312-B9BA-DB19E41EB078}]
  [/cover] */
  /* Check uart driver is initialized  */
  if (Uart_InitStatus != UART_UNINITIALISED)
  #endif
  {
    MaxChannel = Uart_ConfigPtr->NoOfChannels;
    /* [cover parentID={A3DC8E7A-8DA8-4713-B38D-BB0A1EF59553}]
    [/cover] */
    for(CfgCount = 0U; CfgCount < MaxChannel; CfgCount++)
    {
      /* [cover parentID={F9CB853B-440B-485d-A1F3-69C854CA6FD4}]
      [/cover] */
      ChannelConfigPtr = &(Uart_ConfigPtr->ChannelConfigPtr[CfgCount]);
      ChannelInfoPtr = &Uart_ChannelInfo[CfgCount];
      /* [cover parentID={E3F33A98-9F81-4940-BF7A-DC1B56218F15}]
      [/cover] */
      /* Check channel configure in polling mode and write operation on going */
      if((ChannelConfigPtr->TxMode == UART_POLLING_MODE) && \
          (ChannelInfoPtr->ChanTxState == UART_TX_IN_PROGRESS))
      {
        /* [cover parentID={5F48D152-FC6C-4685-963F-8E8977F94EF2}]
        [/cover] */
        /* Extract hardware SFR base address */
        HwModulePtr = Uart_HwModuleAddr[ChannelConfigPtr->HwModule];
        /* Set tx in copy state */
        ChannelInfoPtr->ChanTxState = UART_TX_FIFO_COPY_IN_PROGRESS;
        /* [cover parentID={31919728-DA86-4bfc-A41F-8727EF985B65}]
        [/cover] */
        /* Check last frame transmit in progress */
        if(ChannelInfoPtr->TxDataLeft == 0U)
        {
          TxComplete = HwModulePtr->FLAGS.B.TC;

          /* [cover parentID={5CD5A0F0-EF14-4f9a-AE8A-1370C2C3C751}]
          [/cover] */
          if(TxComplete != 0U)
          {
            /* handle transmit complete*/
            Uart_lTrasmitComplete(HwModulePtr, ChannelInfoPtr, \
                                  ChannelConfigPtr);
          }
        }/* [cover parentID={D04A3A5E-30B7-4469-8BF2-998892F5A673}][/cover] */
        else if(HwModulePtr->FLAGS.B.TFL == UART_SET_BIT)
        {
          /* [cover parentID={15AEF285-93B9-4946-9F0C-4F463FF63F6D}]
          [/cover] */
          /* Prepare TXFIFO for next transmition */
          Uart_lWrite(HwModulePtr, ChannelInfoPtr, ChannelConfigPtr);
        }
        else
        {
          /* Do nothing */
        }

        /* [cover parentID={80393C1E-8FEF-4a9e-B5C4-D696A0D3F958}]
        [/cover] */
        if(ChannelInfoPtr->ChanTxState == UART_TX_FIFO_COPY_IN_PROGRESS)
        {
          ChannelInfoPtr->ChanTxState = UART_TX_IN_PROGRESS;
        }
      }
    }
  }
}
#endif

#if(UART_INIT_CHECK_API == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={60A8D6EA-4861-4c51-8850-6E313881F7AB}] **
** Syntax           : Std_ReturnType Uart_InitCheck(const Uart_ConfigType     **
                      *const ConfigPtr )                                      **
** Service ID      : 216                                                      **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non reentrant                                            **
**                                                                            **
** Parameters (in) : ConfigPtr - Pointer to Uart driver configuration set     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_NOT_OK: DET is reported                                **
**                   E_OK: DET is not reported                                **
**                                                                            **
** Description     : Uart Module Initialization check function.Initialization **
**                   check function which verify variables and register's of  **
**                   Uart module and log error(in case missmatch).            **
*******************************************************************************/
Std_ReturnType Uart_InitCheck(const Uart_ConfigType *const ConfigPtr)
{
  const Uart_ChannelConfigType *ChannelConfigPtr;
  const Ifx_ASCLIN *HwModulePtr;
  uint32 CompareFlag = UART_FULLREG_MASK;
  uint32 SfrVal;
  uint32 CfgVal;
  Std_ReturnType RetVal = E_OK;
  uint8 Channel;
  uint8 MaxChannel;

  #if ((UART_DEV_ERROR_DETECT == STD_ON) || (UART_SAFETY_ENABLE == STD_ON))
  /* [cover parentID={C6DAA6BF-6BF6-4dfb-A5C3-F3753AB68DD0}]
  [/cover] */
  if(ConfigPtr == NULL_PTR)
  {
    /* [cover parentID={103812C9-24BA-4dfe-B00B-C8A092DF25BA}]
    [/cover] */
    Uart_lReportError(UART_SID_INITCHECK, UART_E_PARAM_POINTER);

    RetVal = E_NOT_OK;
  }
  /* [cover parentID={153DB37D-74EB-40a1-BF42-8AA76D88EEF3}]
  [/cover] */
  /* Check uart driver is initialized  */
  else if(Uart_InitStatus == UART_UNINITIALISED)
  {
    /* [cover parentID={C61E0BAA-E6F0-4311-A3B4-77C4D6FD5B63}]
    [/cover] */
    Uart_lReportError(UART_SID_INITCHECK, UART_E_UNINIT);

    RetVal = E_NOT_OK;
  }
  else
  #endif
  {
    MaxChannel = ConfigPtr->NoOfChannels;
    /* [cover parentID={8305568D-9E4D-4278-9D25-682FA7E899DD}]
    [/cover] */
    /* Enable the ASCLIN hardware units for all configured channels */
    for(Channel = 0U; ((Channel < MaxChannel) && (RetVal == E_OK)); Channel++)
    {
      ChannelConfigPtr = &(ConfigPtr->ChannelConfigPtr[Channel]);

      /* Extract HW Module */
      HwModulePtr =  Uart_HwModuleAddr[ChannelConfigPtr->HwModule];
      /* Check all module variables */
      RetVal = Uart_lCheckChannelInfo(Channel);

      /* [cover parentID={4F033FA5-D1CC-4688-A2DB-0ABEE62DBAC9}]
      [/cover] */
      /* Check is error set */
      if(RetVal != E_NOT_OK)
      {
        /* Check CLC */
        SfrVal = HwModulePtr->CLC.U;
        CfgVal = UART_SLEEP_MODE_SUPPORT;
        CompareFlag &= ~(SfrVal ^ CfgVal);

        /* Check FRAMECON  */
        CfgVal = UART_FRAMECONREG_ASC_MODE;

        CfgVal |= ((uint32)ChannelConfigPtr->ParityEnable << \
                   UART_FRAMECON_PEN_BITPOS);

        CfgVal |= ((uint32)ChannelConfigPtr->Parity << \
                   UART_FRAMECON_ODD_BITPOS);

        CfgVal |= ((uint32)1U << UART_FRAMECON_IDLE_BITPOS);

        CfgVal |= ((uint32)ChannelConfigPtr->StopBits << \
                   UART_FRAMECON_STOP_BITPOS);

        SfrVal = HwModulePtr->FRAMECON.U;
        CompareFlag &= ~(SfrVal ^ CfgVal);

        /* Check BRG */
        SfrVal = HwModulePtr->BRG.U;
        CfgVal = ((uint32)ChannelConfigPtr->ChanBaudRateNumerator << \
                  UART_BRG_NUMERATOR_BITPOS) | ChannelConfigPtr->\
                 ChanBaudRateDenominator;

        CompareFlag &= ~(SfrVal ^ CfgVal);

        /* Check IOCR */
        CfgVal = ((uint32)ChannelConfigPtr->CtsEnable << \
                  UART_IOCR_CTSEN_BITPOS);
        CfgVal |= ((uint32)ChannelConfigPtr->CtsPolarity << \
                   UART_IOCR_RCPOL_BITPOS);
        CfgVal |= ChannelConfigPtr->RxPin;
        SfrVal = HwModulePtr->IOCR.U & UART_IOCR_CFG_MASK;
        CompareFlag &= ~(SfrVal ^ CfgVal);

        /* Check TXFIFOCON  */
        CfgVal = UART_TXFIFOCONREG_FIFO_MODE;
        if(ChannelConfigPtr->DataLength < UART_NINEBIT_DATLEN)
        {
          CfgVal |= ((uint32)UART_TXFIFOCONREG_INW_1BYTE << \
                    UART_TXFIFOCON_INW_BITPOS);
        }
        else
        {
          CfgVal |= ((uint32)UART_TXFIFOCONREG_INW_2BYTE << \
                    UART_TXFIFOCON_INW_BITPOS);
        }

        SfrVal = HwModulePtr->TXFIFOCON.U;
        CompareFlag &= ~(SfrVal ^ CfgVal);

        /* Check RXFIFOCON  */
        CfgVal = UART_RXFIFOCONREG_FIFO_MODE;
        if(ChannelConfigPtr->DataLength < UART_NINEBIT_DATLEN)
        {
          CfgVal |= ((uint32)UART_RXFIFOCONREG_OUTW_1BYTE << \
                    UART_RXFIFOCON_OUTW_BITPOS);
        }
        else
        {
          CfgVal |= ((uint32)UART_RXFIFOCONREG_OUTW_2BYTE << \
                    UART_RXFIFOCON_OUTW_BITPOS);
        }

        SfrVal = HwModulePtr->RXFIFOCON.U;
        CompareFlag &= ~(SfrVal ^ CfgVal);

        /* Check DATACON */
        CfgVal = ((uint32)ChannelConfigPtr->DataLength - 1U);
        SfrVal = HwModulePtr->DATCON.U;
        CompareFlag &= ~(SfrVal ^ CfgVal);

        /* Check BITCON */
        CfgVal = ((uint32)ChannelConfigPtr->ChanOversampling << \
                  UART_BITCON_OVERSAMPLING_BITPOS);
        CfgVal |= ChannelConfigPtr->ChanBaudRatePrescalar;
        CfgVal |= ((uint32)UART_BITCONREG_SM_VAL << UART_BITCON_SM_BITPOS);

        CfgVal |= (uint32)((((uint32)(ChannelConfigPtr->ChanOversampling) \
                             >> 1U) + 1U) << UART_BITCON_SAMPLEPOINT_BITPOS);
        SfrVal = HwModulePtr->BITCON.U;
        CompareFlag &= ~(SfrVal ^ CfgVal);

        /* [cover parentID={EEF5CF88-EC8F-42e0-8BF4-63F769016B1F}]
        [/cover] */
        if(CompareFlag != UART_FULLREG_MASK)
        {
          RetVal = E_NOT_OK;
        }
      }
    }
  }

  return RetVal;
}
#endif

/*******************************************************************************
** Traceability     : [cover parentID={362C5E5F-C093-4473-800F-9FEC2CA1A688}] **
** Syntax : void Uart_Init(const Uart_ConfigType *const ConfigPtr )           **
**                                                                            **
** Service ID      : 215                                                      **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non reentrant                                            **
**                                                                            **
** Parameters (in) : ConfigPtr - Pointer to Uart driver configuration set     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : Uart driver Initialization function. Function initialize **
**                   all Uart configured channels.                            **
*******************************************************************************/
void Uart_Init(const Uart_ConfigType *const ConfigPtr)
{
  Uart_ChannelInfoType *ChannelInfoPtr;
  const Uart_ChannelConfigType *ChannelConfigPtr;
  uint8 ModuleNo;
  uint8 ChannelCounter;
  uint8 MaxChannel;
  uint8 ClkDisableChk;
  uint8 ClkFailureCounter;

  /* [cover parentID={BBF41573-09AD-4ce7-9EB4-92CD7426485A}]
  [/cover] */
  #if ((UART_DEV_ERROR_DETECT == STD_ON) || (UART_SAFETY_ENABLE == STD_ON))
  Std_ReturnType DevErrorStatus;
  DevErrorStatus  = E_OK;

  /* [cover parentID={A71729D1-5386-4b75-B52D-F2251E0DD855}]
  [/cover] */
  /* Check for NULL pointer passed */
  if(ConfigPtr == NULL_PTR)
  {
    /* [cover parentID={F589EDA5-C0F6-43e3-AD15-6C0BF075B3C7}]
    [/cover] */
    Uart_lReportError(UART_SID_INIT, UART_E_INIT_FAILED);
    DevErrorStatus  = E_NOT_OK;
  }
  /* [cover parentID={91F19D1F-B4B7-4e3b-B8B3-DBC569BB2F34}]
  [/cover] */
  /* Check Uart driver is initialized */
  else if(Uart_InitStatus == UART_INITIALISED)
  {
    /* [cover parentID={A0E3EFFD-C7ED-4578-B682-DA112AE5BFD0}]
    [/cover] */
    Uart_lReportError(UART_SID_INIT, UART_E_ALREADY_INITIALIZED);
    DevErrorStatus  = E_NOT_OK;
  }
  else
  {
    /* Do Nothing */
  }

  /* Check DET is set */
  if(DevErrorStatus  == E_OK)
  #endif
  {
    /* [cover parentID={A1DD42DE-B5C8-4a32-B2F1-15A7C76981A3}]
    [/cover] */
    MaxChannel = ConfigPtr->NoOfChannels;
    ClkFailureCounter = 0U;

    /* [cover parentID={A964CBBE-3D89-4e34-A9B2-56095510E20B}]
    [/cover] */
    /* [cover parentID={59971F7B-5AAA-4588-A212-25BDBF07E194}]
    [/cover] */
    /* Initialize all configured channel */
    for(ChannelCounter = 0U; ChannelCounter < MaxChannel; ChannelCounter++)
    {
      ChannelConfigPtr = &(ConfigPtr->ChannelConfigPtr[ChannelCounter]);
      ChannelInfoPtr = &Uart_ChannelInfo[ChannelCounter];
      /* Extract hardware unit number  */
      ModuleNo = ChannelConfigPtr->HwModule;

      /* [cover parentID={44156295-B949-4e64-BC73-BB48D8A7C952}]
      [/cover] */
      /* Configure module clock */
      ClkDisableChk = Uart_lHwInitClcReg(ModuleNo, UART_SLEEP_MODE_SUPPORT);
      /* [cover parentID={99F5D357-1924-41d0-9991-AC835D360A91}]
      [/cover] */
      if(0U == ClkDisableChk)
      {
        /* [cover parentID={126230AF-545A-4d7d-8F14-F6F839CBEDC1}]
        [/cover] */
        /* Reset ASCLIN kernel */
        Uart_lHwInitKernelReg(Uart_HwModuleAddr[ModuleNo]);

        /* [cover parentID={C0F5F312-1772-4235-B203-414AD7248F3D}]
        [/cover] */
        /* Initialize the ASCLIN hardware */
        Uart_lHwInit(ModuleNo, ChannelConfigPtr);

        /* Set Uart channel state to init */
        ChannelInfoPtr->ChanTxState = UART_TX_IDLE;
        ChannelInfoPtr->ChanRxState = UART_RX_IDLE;
      }
      else
      {
        /* [cover parentID={22C5E799-ED21-47e8-A2B4-E84E7F046646}]
        [/cover] */
        ClkFailureCounter++;
      }
    }

    /* [cover parentID={9BBC9AB8-31C4-4c58-80E4-DEAC1E6B3F97}]
    [/cover] */
    if(0U == ClkFailureCounter)
    {
      /* [cover parentID={C9DDD480-BC44-44e3-94BC-6A5E70287856}]
      [/cover] */
      /* Set uart configuration pointer */
      Uart_ConfigPtr = ConfigPtr;

      #if ((UART_DEV_ERROR_DETECT == STD_ON) || (UART_SAFETY_ENABLE == STD_ON))
      /* [cover parentID={6ED02763-3107-4d48-A7F2-D32B68497424}]
      [/cover] */
      /* Set driver state to init  */
      Uart_InitStatus = UART_INITIALISED;
      #endif
    }
    #if ((UART_DEV_ERROR_DETECT == STD_ON) || (UART_SAFETY_ENABLE == STD_ON))
    else
    {
      /* [cover parentID={A2FC8F1B-7E16-4cfe-B231-3C2EB718BF45}]
      [/cover] */
      /* Set driver state to un-initialized */
      Uart_InitStatus = UART_UNINITIALISED;
    }
    #endif
  }
}
#if (UART_DEINIT_API == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={A002E536-B667-4666-AD2A-973442C1AA98}] **
** Syntax          : void Uart_DeInit(void)                                   **
** Service ID      : 222                                                      **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : Uart driver deInitialization function.                   **
*******************************************************************************/
void Uart_DeInit(void)
{
  Ifx_ASCLIN *HwModulePtr;
  const Uart_ChannelConfigType *ChannelConfigPtr;
  Uart_ChannelInfoType *ChannelInfoPtr;
  uint32 TimerCorrectnWaitTicks;
  uint32 DelayTickResolution;
  uint8 ModuleNo;
  uint8 MaxChannel;
  uint8 Channel;

  /* [cover parentID={E1F92579-76C5-43c0-BC2E-89DD485420E7}]
  [/cover] */
  /* Get STM timer current resolution and calculate maximum number of ticks
     to wait before expected hardware behaviour is occurd- That timer
     correcttion */
  DelayTickResolution = Mcal_DelayTickResolution();
  TimerCorrectnWaitTicks  = (UART_MAXTIMEOUT_COUNT / DelayTickResolution);

  /* Do not allow ticks to wait to be zero, if STM timer resolution is lower*/
  if(TimerCorrectnWaitTicks == 0U)
  {
    TimerCorrectnWaitTicks++;
  }

  /* [cover parentID={539037A4-6F41-4cd4-8015-5D80294F5F6C}]
  [/cover] */
  #if ((UART_DEV_ERROR_DETECT == STD_ON) || (UART_SAFETY_ENABLE == STD_ON))
  /* [cover parentID=  {B791269A-2A45-40f9-9D8A-2435868F7169}]
  [/cover] */
  /* Check uart driver is initialized  */
  if(Uart_InitStatus == UART_UNINITIALISED)
  {
    /* [cover parentID={7DF24A9F-90C4-4fbe-ADCC-B88012043B34}]
    [/cover] */
    Uart_lReportError(UART_SID_DEINIT, UART_E_UNINIT);
  }
  else
  #endif
  {

    #if ((UART_DEV_ERROR_DETECT == STD_ON) || (UART_SAFETY_ENABLE == STD_ON))
    /* [cover parentID={B79A8CFE-B5B1-458a-A7F1-CF4B38A844E7}]
    [/cover] */
    /* Set Uart driver un-initialization state */
    Uart_InitStatus = UART_UNINITIALISED;
    #endif
    /* [cover parentID={4C909D2C-A7A4-4da1-B9A9-31730B6EA5CB}]
        Extract total number of channel's configured.
    [/cover] */
    MaxChannel = Uart_ConfigPtr->NoOfChannels;
    /* [cover parentID={AFD95056-F0B1-4aa3-9C37-58E839B75B19}]
    [/cover] */
    /* [cover parentID={F7CDB46B-E256-4ea4-AFA2-9F12214E8698}]
    [/cover] */
    /* [cover parentID={4B573AF2-B172-4c12-ABAA-DFF56BD2031D}]
    [/cover] */
    for(Channel = 0U; Channel < MaxChannel; Channel++)
    {
      /* [cover parentID={EE9313B1-B5C1-45cc-9085-8D18FECA0FFF}]
      [/cover] */
      ChannelConfigPtr = &(Uart_ConfigPtr->ChannelConfigPtr[Channel]);
      ChannelInfoPtr = &Uart_ChannelInfo[Channel];
      /* Extract hardware module number */
      ModuleNo = ChannelConfigPtr->HwModule;
      /* [cover parentID={ED0F1F61-92F9-4331-873C-2EF853ECB1D1}]
      [/cover] */
      HwModulePtr = Uart_HwModuleAddr[ModuleNo];
      /* [cover parentID={21C0704F-CC1D-4e38-8826-C3503EA42CA7}]
      [/cover] */
      /* Disable module clock */
      HwModulePtr->CSR.B.CLKSEL = UART_CSRREG_CLKSEL_NOCLK;
      Uart_lStatusTimeout(TimerCorrectnWaitTicks, HwModulePtr, \
                          UART_REG_TYPE_CSR, 0U);
      /* [cover parentID={80F2B724-EFA6-4866-B7A7-F207800300CD}]
      [/cover] */
      /* Change ASCLIN hardware to init mode */
      HwModulePtr->FRAMECON.B.MODE = UART_FRAMECONREG_INIT_MODE;
      /* [cover parentID={C05440CC-D155-4b8c-B980-6507900051BD}]
      [/cover] */
      /* Enable clock source */
      HwModulePtr->CSR.B.CLKSEL = UART_CSRREG_CLKSEL_CLC;
      Uart_lStatusTimeout(TimerCorrectnWaitTicks, HwModulePtr, \
                          UART_REG_TYPE_CSR, 1U);
      /* [cover parentID={0D08FC33-5C57-433b-968F-C97749752121}]
      [/cover] */
      /* Reset channel information */
      ChannelInfoPtr->ChanTxState = UART_TX_IDLE;
      ChannelInfoPtr->ChanRxState = UART_RX_IDLE;
      ChannelInfoPtr->TxDataLeft = 0U;
      ChannelInfoPtr->RxDataLeft = 0U;
      ChannelInfoPtr->TotalDataTxd = 0U;
      ChannelInfoPtr->TotalDataRxd = 0U;
      ChannelInfoPtr->TxBuffPtr = NULL_PTR;
      ChannelInfoPtr->RxBuffPtr = NULL_PTR;
      ChannelInfoPtr->RxIntLevel = 0U;

      /* [cover parentID={AC49A1D5-EE66-4ee2-B155-F64C4DA7E822}]
      [/cover] */
      /* Clear the read and write interrupts*/
      Uart_lClearReadInterrupts(HwModulePtr);
      /* [cover parentID={77C55436-A03A-464d-BD0C-7D28AEFB980C}]
      [/cover] */
      HwModulePtr->FLAGSCLEAR.B.TFLC = UART_SET_BIT;
      /* [cover parentID={29068AF7-4781-4684-A955-8E87A7DA4A28}]
      [/cover] */
      #if (UART_RX_MODE != UART_POLLING_MODE)
        /* [cover parentID={7EFCFF6B-1C79-47b1-A529-649502546FFA}]
        [/cover] */
        #if (UART_RX_MODE == UART_MIXED_MODE)
      /* [cover parentID={0F1099F3-0F21-4a28-9736-546F523DBECD}]
      [/cover] */
      /* Check channel RX configured in polling mode */
        if(ChannelConfigPtr->RxMode != UART_POLLING_MODE)
      #endif
      {
        /* [cover parentID={9A01A3F1-D2B4-4929-B37D-E598E911A52B}]
        [/cover] */
        /* Disable receive interrupts and RXFIFO interrupt mode */
        Uart_lDisableReadInterrupts(HwModulePtr);


        /* [cover parentID={D548D5E8-5948-4127-91B1-58413750017F}]
        [/cover] */
        HwModulePtr->RXFIFOCON.B.FM = UART_CLEAR_BIT;

      }
      #endif
      /* [cover parentID={C8BB867D-9CAB-4b8d-9B82-BAE8228B728E}]
      [/cover] */
      #if (UART_TX_MODE != UART_POLLING_MODE)
        /* [cover parentID={24149B90-B798-4324-932F-75A2DF708B74}]
        [/cover] */
        #if (UART_TX_MODE == UART_MIXED_MODE)
      /* [cover parentID={D5AC9ED5-E119-4ac9-95EF-CB80CF24B885}]
      [/cover] */
      /* Check channel TX configured in polling mode */
        if(ChannelConfigPtr->TxMode != UART_POLLING_MODE)
      #endif
      {
        /* [cover parentID={BF3798BD-2973-46ff-A279-3B33B6EFAE24}]
        [/cover] */
        /* Clear TXFIFO level interrupt and interrupt mode */
        HwModulePtr->FLAGSENABLE.B.TFLE = UART_CLEAR_BIT;

        /* [cover parentID={F749ED47-0A46-44d7-8BC0-F4C8BA598AE6}]
        [/cover] */
        HwModulePtr->TXFIFOCON.B.FM = UART_CLEAR_BIT;
      }
      #endif
      /* [cover parentID={B74C51A4-F281-4a35-B004-2560751F8CFF}]
      [/cover] */
      /* Reset ASCLIN kernel */
      Uart_lHwInitKernelReg(HwModulePtr);
      /* [cover parentID={58FB90BF-A051-43e3-BE2A-F7A3C3473AF0}]
      [/cover] */
      /* Disable module */
      UART_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(&HwModulePtr->CLC.U, \
          UART_SET_BIT);
    }
  }
}
#endif
/*******************************************************************************
** Traceability     : [cover parentID={E8F69A6A-1D68-4aa8-BA08-95B578C5F058}] **
** Syntax : Uart_ReturnType Uart_Read                                         **
**  (                                                                         **
**    const Uart_ChannelIdType channel,Uart_MemType *const MemPtr,            **
**                                                   const Uart_SizeType Size **
**  )                                                                         **
**                                                                            **
** Service ID      : 217                                                      **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant(Not for same channel)                          **
**                                                                            **
** Parameters (in) : Channel - Uart channel to be addressed.                  **
**                   MemPtr - Memory location where data needs to be stored   **
**                   Size -Number of data bytes to be received.If channel     **
**                         frame length configured with greater than 8 bit    **
**                         then number of bytes should be multiple of 2.      **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : UART_E_OK - Read operation was initiated successfully    **
**                   UART_E_NOT_OK - Read operation couldn't be initiated     **
**                   due to development errors                                **
**                   UART_E_BUSY - Uart channel is busy with other            **
**                   read operation                                           **
**                                                                            **
** Description     : Api to configure the given UART Channel for reception    **
**                   of the specified number of data bytes and the memory     **
**                   location to be used to store the received data           **
*******************************************************************************/
Uart_ReturnType Uart_Read(const Uart_ChannelIdType Channel,
                          Uart_MemType *const MemPtr,
                          const Uart_SizeType Size)
{
  Ifx_ASCLIN* HwModulePtr;
  Uart_ChannelInfoType* ChannelInfoPtr;
  Uart_ReturnType RetValue;
  uint8 IntLevel;

  /* [cover parentID={7460D8FB-49A0-4d0a-976B-2C0736B3A4A8}]
  [/cover] */
  #if ((UART_DEV_ERROR_DETECT == STD_ON) || (UART_SAFETY_ENABLE == STD_ON))
  /* [cover parentID={54097BC0-63A6-44c9-A188-F619750CB3F8}]
  [/cover] */
  RetValue = Uart_lCheckDetError(Channel, Size, UART_SID_READ, MemPtr);

  /* [cover parentID={7F0C55A3-34B3-4014-A795-5DBF2E11D3AC}]
  [/cover] */
  if(RetValue == UART_E_OK)
  #else
  RetValue = UART_E_OK;
  ChannelInfoPtr = &Uart_ChannelInfo[Channel];
  /* [cover parentID={A5D92A0D-2FDB-4a3e-BCBC-091F46B9168E}]
  [/cover] */
  /* Check read operation is ongoing for same channel */
  if(ChannelInfoPtr->ChanRxState != UART_RX_IDLE)
  {
    /* [cover parentID={3F1E0151-F369-4f44-B865-F5F9203940FB}]
    [/cover] */
    RetValue = UART_E_BUSY;
  }
  else
  #endif
  {
    #if ((UART_DEV_ERROR_DETECT == STD_ON) || (UART_SAFETY_ENABLE == STD_ON))
    ChannelInfoPtr = &Uart_ChannelInfo[Channel];
    #endif
    /* [cover parentID={584EC5F2-B82A-40e8-9CD9-8BC6B57D0D7A}]
    [/cover] */
    /* Update Uart_ChannelInfo for Read Operation */
    ChannelInfoPtr->ChanRxState = UART_RX_PREP_IN_PROGRESS;
    ChannelInfoPtr->RxBuffPtr = MemPtr;
    ChannelInfoPtr->RxDataLeft = Size;
    ChannelInfoPtr->TotalDataRxd = 0U;
    ChannelInfoPtr->RxNotfn = UART_RX_NOTFN_NOT_TRIGGERED;
    #if (UART_RECEIVE_STREAMING_MODE_API == STD_ON)
    ChannelInfoPtr->ChanRxMode = UART_RX_IN_READ_MODE;
    #endif
    /* [cover parentID={A775039E-7EAD-46f3-9CF3-6E98BC868B95}]
    [/cover] */
    /* Extract SFRs address for target ASCLIN Unit */
    HwModulePtr = Uart_HwModuleAddr[Uart_ConfigPtr->\
                                    ChannelConfigPtr[Channel].HwModule];
    /* Flush the RXFIFO */
    HwModulePtr->RXFIFOCON.B.FLUSH = UART_SET_BIT;

    /* Clear read interrupt */
    Uart_lClearReadInterrupts(HwModulePtr);
    /* [cover parentID={552D2AEB-D105-4089-B47D-BCC4F64B5199}]
    [/cover] */
    if(Size < UART_BUFFER_SIZE)
    {
      /* [cover parentID={57F2CC23-0868-4fcf-BBB8-425957FEC9E4}]
      [/cover] */
      /* Set RXFIFO interrupt level as per numebr of bytes to be receive */
      IntLevel = ((uint8)Size - (uint8)1U);
    }
    else
    {
      /* [cover parentID={FBDD09A0-F7EF-4c64-93E8-0E30E0AEACD5}]
      [/cover] */
      /* Set maximum receive level */
      IntLevel = UART_RX_FIFO_INT_LEVEL_MAX;
    }

    /* [cover parentID={17CA9E4F-302D-4d66-B3C3-2FD6EE211C45}]
    [/cover] */
    /* Copy transmit fill level to check spurius interrupt */
    HwModulePtr->RXFIFOCON.B.INTLEVEL = IntLevel;
    ChannelInfoPtr->RxIntLevel = IntLevel + 1U;
    /* [cover parentID={4DB647BF-1F8C-4733-8FC4-D0497AB63E78}]
    [/cover] */
    #if (UART_RX_MODE != UART_POLLING_MODE)
      /* [cover parentID={D840C322-4458-4f71-AEC8-FB7FB2DA7122}]
      [/cover] */
      #if (UART_RX_MODE == UART_MIXED_MODE)
    /* [cover parentID={BBF9AF60-A570-417e-8AF2-2CD0BFE873E4}]
    [/cover] */
    /* Check read operation for current channel configured in interrupt mode */
      if(Uart_ConfigPtr->ChannelConfigPtr[Channel].RxMode != UART_POLLING_MODE)
    #endif
    {
      /* [cover parentID={9FE13698-9996-4084-89AD-86C5A331389B}]
      [/cover] */
      /* Enable RXFIFO level and error interrupt */
      Uart_lEnableReadInterrupts(HwModulePtr);
    }
    #endif

    /* [cover parentID={7AE6C1BA-C878-4b32-877A-5E410BCD84D7}]
    [/cover] */
    /* Enable RXFIFO */
    HwModulePtr->RXFIFOCON.B.ENI = UART_SET_BIT;
    ChannelInfoPtr->ChanRxState = UART_RX_IN_PROGRESS;
  }

  return RetValue;
}
#if (UART_RECEIVE_STREAMING_MODE_API == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={713CDDB0-E6F7-41f4-BA83-D0D4E135E3C2}] **
** Syntax : Uart_ReturnType Uart_StartStreaming                               **
**  (                                                                         **
**    const Uart_ChannelIdType channel,Uart_MemType *const MemPtr,            **
**                                                const Uart_SizeType BufSize **
**  )                                                                         **
**                                                                            **
** Service ID      : 229                                                      **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant(Not for same channel)                          **
**                                                                            **
** Parameters (in) : Channel - UART channel id for the streaming mode         **
**                             operation.                                     **
**                   MemPtr - Application buffer address.The UART driver uses **
**                            this buffer to copy the received UART data from **
**                            the hardware FIFO memory to this application    **
**                            buffer and invokes streaming notification       **
**                            function.                                       **
**                  BufSize - The length of the application buffer in bytes   **
**                            which is passed in the parameter MemPtr. Since  **
**                            the hardware FIFO size is 16 bytes, at a time   **
**                            UART hardware can store up to 16 bytes. So      **
**                            recommended BufSize is 16 bytes anything above  **
**                            will not be utilized by the UART driver         **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : UART_E_OK - Streaming operation was initiated            **
**                   successfully                                             **
**                   UART_E_NOT_OK - Streaming operation couldn't be initiated**
**                   due to development errors                                **
**                   UART_E_BUSY - Uart channel is busy with other            **
**                   Streaming or read operation                              **
**                                                                            **
** Description     : Api to configure the receiving operation in streaming    **
**                   mode for specified UART channel in polling or            **
**                   interrupt mode                                           **
**                                                                            **
*******************************************************************************/
Uart_ReturnType Uart_StartStreaming(const Uart_ChannelIdType Channel,
                          Uart_MemType *const MemPtr,
                          const Uart_SizeType BufSize)
{
  Ifx_ASCLIN* HwModulePtr;
  Uart_ChannelInfoType* ChannelInfoPtr;
  const Uart_ChannelConfigType *ChannelConfigPtr;
  Uart_ReturnType RetValue = UART_E_OK;
  uint8 IntLevel;

  /* [cover parentID={E1CA14EC-AE8E-48a0-8E6F-C0F39A888A16}]
  [/cover] */
  /* DET or SAFETY is ON */
  #if ((UART_DEV_ERROR_DETECT == STD_ON) || (UART_SAFETY_ENABLE == STD_ON))
    /* [cover parentID={28F502D9-EF30-49a4-B71F-0D8A02264377}]
    [/cover] */
    /* Validate input parameters */
    RetValue = Uart_lCheckDetError(Channel, BufSize,\
                                            UART_SID_START_STREAMING, MemPtr);
    /* [cover parentID={445765AE-8657-47e6-A8D1-D7C2999CD5B0}]
    [/cover] */
  if(RetValue == UART_E_OK)
  #else
    /* [cover parentID={7ED0EA81-F4F5-4501-8210-59B0A9CD5B20}]
    [/cover] */
    ChannelInfoPtr = &Uart_ChannelInfo[Channel];

    /* [cover parentID={EB69E4E3-B897-4f70-BA52-814D32D607CA}]
    [/cover] */
    /* Check read operation is ongoing for same channel */
    if(ChannelInfoPtr->ChanRxState != UART_RX_IDLE)
      {
        /* [cover parentID={1F62665C-4D51-402f-8DCE-4A8B3888E97E}]
        [/cover] */
        /* Update return value with busy */
        RetValue = UART_E_BUSY;
      }
    else
  #endif
  {
    #if ((UART_DEV_ERROR_DETECT == STD_ON) || (UART_SAFETY_ENABLE == STD_ON))
    ChannelInfoPtr = &Uart_ChannelInfo[Channel];
    #endif
    /* [cover parentID={777E6E03-49E6-4f8e-9095-F659B6D3F34A}]
    [/cover] */
    /* Extract SFRs address for target ASCLIN Unit */
    ChannelConfigPtr = &(Uart_ConfigPtr->ChannelConfigPtr[Channel]);
    HwModulePtr = Uart_HwModuleAddr[ChannelConfigPtr->HwModule];

    /* [cover parentID={44B4FE03-00D3-4378-8003-69CC7DAB9CE8}]
    [/cover] */
    /* Update Uart_ChannelInfo for Streaming Operation */
    ChannelInfoPtr->ChanRxState = UART_RX_PREP_IN_PROGRESS;
    ChannelInfoPtr->RxBuffPtr = MemPtr;
    ChannelInfoPtr->RxBufSize = BufSize;
    ChannelInfoPtr->RxNotfn = UART_RX_NOTFN_NOT_TRIGGERED;
    ChannelInfoPtr->ChanRxMode = UART_RX_IN_STREAMING_MODE;

    /* Flush the RXFIFO */
    HwModulePtr->RXFIFOCON.B.FLUSH = UART_SET_BIT;

    /* [cover parentID={8062B707-4BDA-460e-ABC1-88A2A460F4D1}]
    [/cover] */
    /* Clear read interrupt */
    Uart_lClearReadInterrupts(HwModulePtr);


    /* [cover parentID={1A2BD08A-DF79-4f56-A5DE-8F55CA655C76}]
    [/cover] */
    /* Is DataLength more than 8 bits */
    if(ChannelConfigPtr->DataLength >= UART_NINEBIT_DATLEN)
      {
        /* [cover parentID={82088F06-E5A8-40c3-B153-F75DFCBF8E5D}]
        [/cover] */
        /* Set receive Interrupt level to 2Bytes */
        IntLevel = UART_RX_FIFO_INT_LEVEL_ONE;
      }
    else
      {
        /* [cover parentID={065AFD54-FFDD-4c73-89BE-B47554C1882E}]
        [/cover] */
        /* Set receive Interrupt level to 1Byte */
        IntLevel = UART_RX_FIFO_INT_LEVEL_MIN;
      }
    /* Copy Receive fill level to check spurius interrupt */
    HwModulePtr->RXFIFOCON.B.INTLEVEL = IntLevel;
    ChannelInfoPtr->RxIntLevel = IntLevel + 1U;

    /* [cover parentID={1A4431DF-B3A5-4b1b-B655-49E30D30F850}]
    [/cover] */
    #if (UART_RX_MODE != UART_POLLING_MODE)
      /* [cover parentID={40893C6E-0B79-469a-9CC8-EACE9F95B416}]
      [/cover] */
      #if (UART_RX_MODE == UART_MIXED_MODE)
    /* [cover parentID={BD35AFAB-2CB6-4822-A53A-1A92F77D697E}]
    [/cover] */
    /* Check read operation for current channel configured in interrupt mode */
      if(ChannelConfigPtr->RxMode != UART_POLLING_MODE)
    #endif
    {
      /* [cover parentID={709A0F8F-29B0-4277-8EEF-0027AE6AE9FA}]
      [/cover] */
      /* Enable RXFIFO level and error interrupt */
      Uart_lEnableReadInterrupts(HwModulePtr);
    }
    #endif
    /* [cover parentID={68D18281-6A5E-4142-9BF6-B05AA53D3672}]
    [/cover] */
    /* Enable RXFIFO */
    HwModulePtr->RXFIFOCON.B.ENI = UART_SET_BIT;
    ChannelInfoPtr->ChanRxState = UART_RX_IN_PROGRESS;

  }

  return RetValue;
}
#endif

#if (UART_RECEIVE_STREAMING_MODE_API == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={24571EE4-2E3C-46e3-9CD6-1735B930AD7B}] **
** Syntax:Uart_ReturnType Uart_StopStreaming(const Uart_ChannelIdType Channel)**
**                                                                            **
** Service ID      : 230                                                      **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant  (Not for the same channel)                    **
**                                                                            **
** Parameters (in) : Channel - Uart channel id which is configured for the    **
**                                         in straming mode                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : UART_E_OK - Streaming operation of the channel is        **
**                                                  stopped successfully      **
**                   UART_E_NOT_OK -Streaming operation of the channel        **
**                                  couldn't stopped due to development       **
**                                  errors or channel receive state is not in **
**                                  progress                                  **
** Description     : API to stop streaming operation on given channel.        **
**                                                                            **
*******************************************************************************/
Uart_ReturnType Uart_StopStreaming(const Uart_ChannelIdType Channel)
{
  Ifx_ASCLIN *HwModulePtr;
  const Uart_ChannelConfigType *ChannelConfigPtr;
  Uart_ChannelInfoType *ChannelInfoPtr;
  Uart_ReturnType RetValue = UART_E_OK;


    ChannelInfoPtr = &Uart_ChannelInfo[Channel];
  /* [cover parentID={AA22F99E-0EA5-4313-93E8-8D94614C5A57}]
  [/cover] */
  /* DET or SAFETY is ON */
  #if((UART_DEV_ERROR_DETECT == STD_ON) || (UART_SAFETY_ENABLE == STD_ON))
  /* [cover parentID={C88FD45B-0186-4bcf-9E60-BA404D3F67A2}]
  [/cover] */
  /* Is Uart driver initialized */
  if(Uart_InitStatus == UART_UNINITIALISED)
  {
    /* [cover parentID={7C70FA80-E826-4661-B5F2-3E0C653DD91B}]
    [/cover] */
    /* Uart is not uninitialized report DET */
    Uart_lReportError(UART_SID_STOP_STREAMING, UART_E_UNINIT);
    RetValue = UART_E_NOT_OK;
  }
  else
  {
    /* [cover parentID={4D1C4549-49D3-4c55-970F-5903D10601DE}]
    [/cover] */
    /* ChannelId is invalid report DET */
    RetValue = Uart_lChannelCheck(Channel, UART_SID_STOP_STREAMING);

    /* [cover parentID={129F32E8-58A7-4e7e-A5F5-C84824A4B7F5}]
    [/cover] */
    /*Is channel ID valid and in streaming mode*/
    if((RetValue == UART_E_OK) &&
    (ChannelInfoPtr->ChanRxMode != UART_RX_IN_STREAMING_MODE))
    {
        /* [cover parentID={CB2BCF14-E925-42f0-9E64-DE67FEEA6B90}]
        [/cover] */
        /*Report Uart driver is not in sreaming mode error*/
       Uart_lReportError(UART_SID_STOP_STREAMING, UART_E_INVALID_CHANNEL);
       RetValue = UART_E_NOT_OK;
    }
  }

  /* [cover parentID={3556B661-5A8B-447f-A623-0791BFA4518B}]
  [/cover] */
  if(RetValue == UART_E_OK)
  #endif
  {

    /* [cover parentID={5EFEAFE5-6D07-40a9-9A54-F5A1E3EDB20A}]
    [/cover] */
    /* Check receive in progress */
    if(ChannelInfoPtr->ChanRxState == UART_RX_IN_PROGRESS)
    {
        /* [cover parentID={B45FC54B-5663-4107-86B1-EA6757EA51DE}]
        [/cover] */
        /* Set receive state with stop streaming in progress */
      ChannelInfoPtr->ChanRxState = UART_RX_STOP_STREAMING_IN_PROGRESS;
      ChannelConfigPtr = &(Uart_ConfigPtr->ChannelConfigPtr[Channel]);
      HwModulePtr = Uart_HwModuleAddr[ChannelConfigPtr->HwModule];

      /* Disable and flush RXFIFO */
      HwModulePtr->RXFIFOCON.B.ENI = UART_CLEAR_BIT;
      HwModulePtr->RXFIFOCON.B.FLUSH = UART_SET_BIT;

      /* [cover parentID={B689C14D-0DD6-4204-B9F6-A2ACF33048AB}]
      [/cover] */
      /* Clear and disable Rx overflow and level interrupts */
      Uart_lClearReadInterrupts(HwModulePtr);

      /* [cover parentID={2DC9F736-7926-42d8-A327-02C0CA1506C9}]
      [/cover] */
      #if (UART_RX_MODE != UART_POLLING_MODE)
      /* [cover parentID={9D8FBC35-A17D-4894-A0C9-65B85448BEAB}]
      [/cover] */
        #if (UART_RX_MODE == UART_MIXED_MODE)
      /* [cover parentID={7BBABC18-7D8E-43bf-BEFD-AD24FA7A2984}]
      [/cover] */
      /* Check if read operation in interrupt mode */
        if(ChannelConfigPtr->RxMode != UART_POLLING_MODE)
      #endif
      {
        Uart_lDisableReadInterrupts(HwModulePtr);
      }
      #endif

      /* [cover parentID={F4B00BFC-B153-42b0-B3D0-D0A643BA0578}]
      [/cover] */
      /* Reset channel info structure */
      ChannelInfoPtr->RxBuffPtr = NULL_PTR;
      /* Reset channel state */
      ChannelInfoPtr->ChanRxState = UART_RX_IDLE;
    }
    else
    {
        RetValue = UART_E_NOT_OK;
    }
  }

  return RetValue;
}
#endif

/*******************************************************************************
** Traceability     : [cover parentID={8BED9241-561A-48c1-B43E-9D7304BC92F9}] **
** Syntax : Uart_ReturnType Uart_Write                                        **
**  (                                                                         **
**    const Uart_ChannelIdType channel,Uart_MemType *const MemPtr,            **
**    const Uart_SizeType Size                                                **
**  )                                                                         **
**                                                                            **
** Service ID      : 218                                                      **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant(Not for the same channel)                      **
**                                                                            **
** Parameters (in) : Channel -Uart channel to be addressed                    **
**                   MemPtr -Pointer to buffer from where data to be transmit **
**                   Size -Number of data bytes to be transmitted.If channel  **
**                         frame length configured with greater than 8 bit    **
**                         then number of bytes should be multiple of 2.      **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : UART_E_OK - Write operation initialized successfully     **
**                   UART_E_NOT_OK -Write operation couldn't performed due to **
**                                 development error.                         **
**                   UART_E_BUSY - Uart channel is busy in other transmit     **
**                                 operation                                  **
**                                                                            **
** Description     : Function to transmit data from user memory location      **
**                   (App Buffer)on to the given channel                      **
**                                                                            **
*******************************************************************************/
Uart_ReturnType Uart_Write(const Uart_ChannelIdType Channel,
                           Uart_MemType *const MemPtr,
                           const Uart_SizeType Size)
{
  const Uart_ChannelConfigType *ChannelConfigPtr;
  Ifx_ASCLIN *HwModulePtr;
  Uart_ChannelInfoType *ChannelInfoPtr;
  Uart_ReturnType RetValue;

  /* [cover parentID={C8B64780-1D25-4f20-9179-5365735C8230}]
  [/cover] */
  #if ((UART_DEV_ERROR_DETECT == STD_ON) || (UART_SAFETY_ENABLE == STD_ON))
  /* [cover parentID={AFAFDD8E-FDA0-4766-9A31-92BBC7A1E838}]
     Validate input parameter and update return value.
  [/cover] */
  RetValue = Uart_lCheckDetError(Channel, Size, UART_SID_WRITE, MemPtr);

  if(RetValue == UART_E_OK)
  #else
  /* [cover parentID={408AB9A6-A7F7-414d-9550-1DF4563A1A90}]
  [/cover] */
  /* [cover parentID={5C67C3DD-9F60-400c-AAFC-78740651B58A}]
  [/cover] */
  RetValue = UART_E_OK;
  ChannelInfoPtr = &Uart_ChannelInfo[Channel];
  /* [cover parentID={4407B922-09FB-4a3f-A697-06024FB5FF1A}]
  [/cover] */
  /* No other Uart write operation is in progress */
  if(ChannelInfoPtr->ChanTxState != UART_TX_IDLE)
  {
    /* [cover parentID={7F607969-07AB-4712-B138-AC90EB4CA176}]
    Set return variable with busy.
    [/cover] */
    RetValue = UART_E_BUSY;
  }
  else
  #endif
  {
    #if ((UART_DEV_ERROR_DETECT == STD_ON) || (UART_SAFETY_ENABLE == STD_ON))
    ChannelInfoPtr = &Uart_ChannelInfo[Channel];
    #endif
    /* [cover parentID={556E244D-2CE1-4c17-BC65-629524F62C94}]
    [/cover] */
    /* Update channel state */
    ChannelInfoPtr->ChanTxState = UART_TX_PREP_IN_PROGRESS;

    ChannelConfigPtr = &(Uart_ConfigPtr->ChannelConfigPtr[Channel]);
    /* Extract ASCLIN module SFR base address */
    HwModulePtr = Uart_HwModuleAddr[ChannelConfigPtr->HwModule];

    /* [cover parentID={25CCC9D8-9F3D-4c66-9C8B-F7232701FC03}]
    [/cover] */
    /* Update channel info to initiate data transmision */
    ChannelInfoPtr->TxBuffPtr = MemPtr;
    ChannelInfoPtr->TxDataLeft = Size;
    ChannelInfoPtr->TotalDataTxd = 0U;
    /* Flush TXFIFO */
    HwModulePtr->TXFIFOCON.B.FLUSH = UART_SET_BIT;

    /* [cover parentID={E5D5A953-4E20-4412-AB1E-7BEF2207C136}]
    [/cover] */
    /* Copy application buffer data to TXFIFO */
    Uart_lWrite(HwModulePtr, ChannelInfoPtr, ChannelConfigPtr);
    ChannelInfoPtr->ChanTxState = UART_TX_IN_PROGRESS;
  }

  return RetValue;
}
#if (UART_ABORT_READ_API == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={F0165BE1-EF5D-40d0-A7BB-CB61C01C15BC}] **
** Syntax : Uart_SizeType Uart_AbortRead(const Uart_ChannelIdType Channel)    **
**                                                                            **
** Service ID      : 220                                                      **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant  (Not for the same channel)                    **
**                                                                            **
** Parameters (in) : Channel - Uart channel to be addressed                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : UartRetSize - Number of bytes successfully received and  **
**                                 stored to the application memory location  **
**                                 before the read operation was aborted.     **
** Description     : API to abort read operation on given channel.            **
**                                                                            **
*******************************************************************************/
Uart_SizeType Uart_AbortRead(const Uart_ChannelIdType Channel)
{
  Ifx_ASCLIN *HwModulePtr;
  const Uart_ChannelConfigType *ChannelConfigPtr;
  Uart_ChannelInfoType *ChannelInfoPtr;
  Uart_SizeType UartRetSize;

  ChannelInfoPtr = &Uart_ChannelInfo[Channel];
  #if((UART_DEV_ERROR_DETECT == STD_ON) || (UART_SAFETY_ENABLE == STD_ON))
  Uart_ReturnType RetValue;
  #endif
  /* [cover parentID={7B82F49D-DC4C-4207-812E-B3957C6062B2}]
  [/cover] */
  /* Set return size to zero */
  UartRetSize = 0U;

  /* [cover parentID={FF0CFB7D-EECD-4cd8-AF17-706674EC5BC5}]
  [/cover] */
  #if((UART_DEV_ERROR_DETECT == STD_ON) || (UART_SAFETY_ENABLE == STD_ON))

  /* [cover parentID={9A5F0CAF-25DD-4b1d-8EFC-992090736371}]
  [/cover] */
  if(Uart_InitStatus == UART_UNINITIALISED)
  {
    /* [cover parentID={E1C462B3-34E6-4ec9-A6BA-43B5EFBC40A9}]
    [/cover] */
    /* Uart is not uninitialized report DET */
    Uart_lReportError(UART_SID_ABORT_READ, UART_E_UNINIT);
    RetValue = UART_E_NOT_OK;
  }
  else
  {
    /* [cover parentID={5EDE0315-EDD0-4fa5-A365-4D556F563B5A}]
    [/cover] */
    /* ChannelId is invalid report DET */
    RetValue = Uart_lChannelCheck(Channel, UART_SID_ABORT_READ);
    #if(UART_RECEIVE_STREAMING_MODE_API == STD_ON)
    /* [cover parentID={D000553D-7D83-4d31-A0DF-05FE18A3D415}]
    [/cover] */
    /*Is channel ID valid and in streaming mode*/
    if((RetValue == UART_E_OK) &&
    (ChannelInfoPtr->ChanRxMode != UART_RX_IN_READ_MODE))
    {
        /* [cover parentID={22E09971-BB7C-4799-BF79-A6B5B7925568}]
        [/cover] */
        /* Report Uart driver is not in normal read mode */
       Uart_lReportError(UART_SID_ABORT_READ, UART_E_INVALID_CHANNEL);
       RetValue = UART_E_NOT_OK;
    }
    #endif
  }

  /* [cover parentID={F30E1A6F-6E9A-4430-9212-ADD437C19246}]
  [/cover] */
  if(RetValue == UART_E_OK)
  #endif
  {
    /* [cover parentID={36FF27BF-91C6-4dbc-AB94-E42306A53B13}]
    [/cover] */
    if(ChannelInfoPtr->ChanRxState == UART_RX_IN_PROGRESS)
    {
      ChannelInfoPtr->ChanRxState = UART_RX_ABORT_IN_PROGRESS;
      ChannelConfigPtr = &(Uart_ConfigPtr->ChannelConfigPtr[Channel]);
      HwModulePtr = Uart_HwModuleAddr[ChannelConfigPtr->HwModule];
      /* [cover parentID={00BC0361-D302-48bb-8D66-D56F97633E18}]
      [/cover] */
      /* Disable and flush RXFIFO */
      HwModulePtr->RXFIFOCON.B.ENI = UART_CLEAR_BIT;
      HwModulePtr->RXFIFOCON.B.FLUSH = UART_SET_BIT;

      /* [cover parentID={896781A8-A7D1-457c-932D-EEC22C54DB01}]
      [/cover] */
      /* Clear and disable Rx overflow and level interrupts */
      Uart_lClearReadInterrupts(HwModulePtr);

      /* [cover parentID={70922CBC-C774-49a1-807B-FC44125BC1A7}]
      [/cover] */
      #if (UART_RX_MODE != UART_POLLING_MODE)
      /* [cover parentID={2BE2DFF7-1919-4cea-B323-DF3941845E9B}]
      [/cover] */
        #if (UART_RX_MODE == UART_MIXED_MODE)
      /* [cover parentID={0E47C788-D20A-44e9-B72B-A5181D8C2846}]
      [/cover] */
      /* Check if read operation in interrupt mode */
        if(ChannelConfigPtr->RxMode != UART_POLLING_MODE)
      #endif
      {
        /* [cover parentID={076D2D56-3D6A-4938-9FD0-D9ACDB039638}]
        [/cover] */
        Uart_lDisableReadInterrupts(HwModulePtr);
      }
      #endif

      /* [cover parentID={28200BAB-193D-4237-B7E2-9AA7CAFFCB78}]
      [/cover] */
      /* Return total data rxd before read operation was aborted */
      UartRetSize = ChannelInfoPtr->TotalDataRxd;
      /* [cover parentID={715DC8F6-D95B-4254-82FA-3886900B773E}]
      [/cover] */
      /* Reset channel info structure */
      ChannelInfoPtr->RxBuffPtr = NULL_PTR;
      /* Reset data Rxd counter */
      ChannelInfoPtr->TotalDataRxd = 0U;
      /* Reset channel state */
      ChannelInfoPtr->ChanRxState = UART_RX_IDLE;
      /* [cover parentID={E5378DB5-9FA5-4eb6-AD0C-CA27A0A2A0AA}]
      [/cover] */
      /* [cover parentID={1BCA0626-7BAC-43fe-8901-C50A3ABF94EB}]
      [/cover] */
      if(ChannelConfigPtr->UartNotif.UartAbortReceiveNotifPtr != NULL_PTR)
      {
        /* [cover parentID={5EC50B49-CAA7-48ca-BB5A-4471AA6E9A44}]
        [/cover] */
        /* Call abort receive notification function */
        ChannelConfigPtr->UartNotif.UartAbortReceiveNotifPtr(UART_E_NO_ERR);
      }
    }
  }

  return UartRetSize;
}
#endif

#if (UART_ABORT_WRITE_API == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={9299FAD8-EB63-453e-821C-EF1152ABF363}] **
** Syntax : Uart_SizeType Uart_AbortWrite( Uart_ChannelIdType Channel )       **
**                                                                            **
** Service ID      : 219                                                      **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant(Not for the same channel)                      **
**                                                                            **
** Parameters (in) : Channel - Uart channel to be addressed                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : UartRetSize - Number of bytes that have been             **
**                                 successfully transmitted before the write  **
**                                 operation was aborted.                     **
**                                                                            **
** Description     : API to abort data transmission on given channel.         **
                                                                              **
**                                                                            **
*******************************************************************************/
Uart_SizeType Uart_AbortWrite(const Uart_ChannelIdType Channel)
{
  Ifx_ASCLIN *HwModulePtr;
  const Uart_ChannelConfigType *ChannelConfigPtr;
  Uart_ChannelInfoType *ChannelInfoPtr;
  Uart_SizeType UartRetSize;
  uint16 TxdCount;
  #if((UART_DEV_ERROR_DETECT == STD_ON) || (UART_SAFETY_ENABLE == STD_ON))
  Uart_ReturnType RetValue;
  #endif

  /* [cover parentID={BDE6576C-4F1E-4e61-A61B-3947D34188F7}]
  [/cover] */
  /* Set return size to zero */
  UartRetSize = 0U;

  /* [cover parentID={CADEA39B-332E-4fbf-A955-3A742D78A958}]
  [/cover] */
  #if((UART_DEV_ERROR_DETECT == STD_ON) || (UART_SAFETY_ENABLE == STD_ON))
  /* [cover parentID={4D96F2F8-387B-41b5-AC30-D9E952781AF2}]
  [/cover] */
  if(Uart_InitStatus == UART_UNINITIALISED)
  {
    /* [cover parentID={C0C327EB-0E28-40d3-83B3-25CBA9D52F9F}]
    [/cover] */
    /* Report to  DET */
    Uart_lReportError(UART_SID_ABORT_WRITE, UART_E_UNINIT);
    RetValue = UART_E_NOT_OK;
  }
  else
  {
    /* [cover parentID={17622B0E-68CE-4d97-B995-98A562F8E831}]
    [/cover] */
    /* Check channel identifier */
    RetValue = Uart_lChannelCheck(Channel, UART_SID_ABORT_WRITE);
  }
  /* [cover parentID={64DF62FC-74FC-4b77-89E0-8E4758C4B9E1}]
  [/cover] */
  if(RetValue == UART_E_OK)
  #endif
  {
    ChannelInfoPtr = &Uart_ChannelInfo[Channel];
    /* [cover parentID={F1C45DD3-4668-4263-B94C-D5A73CB9E3EE}]
    [/cover] */
    if(ChannelInfoPtr->ChanTxState == UART_TX_IN_PROGRESS)
    {
      ChannelInfoPtr->ChanTxState = UART_TX_ABORT_IN_PROGRESS;
      ChannelConfigPtr = &(Uart_ConfigPtr->ChannelConfigPtr[Channel]);
      HwModulePtr = Uart_HwModuleAddr[ChannelConfigPtr->HwModule];

      /* [cover parentID={E14AFD10-BCA7-4ff5-8F4B-B87ED87BA24A}]
      [/cover] */
      /* Disable TXFIFO */
      HwModulePtr->TXFIFOCON.B.ENO = UART_CLEAR_BIT;

      /* Calculate the count of data Txd before write operation aborted */
      TxdCount = (uint16)HwModulePtr->TXFIFOCON.B.FILL;
      UartRetSize = (ChannelInfoPtr->TotalDataTxd - TxdCount);

      /* Flush TXFIFO */
      HwModulePtr->TXFIFOCON.B.FLUSH = UART_SET_BIT;
      /* Clear TXFIFO TXFIFO level interrupts */
      HwModulePtr->FLAGSCLEAR.B.TFLC = UART_SET_BIT;

      /* [cover parentID={FDF96931-A983-486f-81CF-4F26198D4CF6}]
      [/cover] */
      #if (UART_TX_MODE != UART_POLLING_MODE)
        /* [cover parentID={B6C2BD08-E2DC-49b4-9AE1-CE01890F275C}]
        [/cover] */
        #if (UART_TX_MODE == UART_MIXED_MODE)
      /* [cover parentID={AA9A4C3E-B66B-4a7d-B74A-F3E5315F5687}]
      [/cover] */
      /* Check if write operation in interrupt mode */
        if(ChannelConfigPtr->TxMode != UART_POLLING_MODE)
      #endif
      {
        /* [cover parentID={2D517F37-A4A9-4b20-8FD4-AAF54DCE15FC}]
        [/cover] */
        HwModulePtr->FLAGSENABLE.B.TFLE = UART_CLEAR_BIT;
      }
      #endif
      /* [cover parentID={51904506-15A1-41a7-A3ED-297CB28609E7}]
      [/cover] */
      /* Reset channel transmit information structure */
      ChannelInfoPtr->TxBuffPtr = NULL_PTR;
      ChannelInfoPtr->TotalDataTxd = 0U;
      ChannelInfoPtr->ChanTxState = UART_TX_IDLE;
      /* [cover parentID={95932254-1CC6-4460-8793-BC22F4471EA7}]
      [/cover] */
      /* [cover parentID={58AB1E41-45CC-46e4-80CD-E2181072FFF1}]
      [/cover] */
      if(ChannelConfigPtr->UartNotif.UartAbortTransmitNotifPtr != NULL_PTR)
      {
        /* [cover parentID={44138558-19E7-48ac-8A2B-9AFE25650FDC}]
        [/cover] */
        /* Call transmit abort notification function */
        ChannelConfigPtr->UartNotif.UartAbortTransmitNotifPtr(UART_E_NO_ERR);
      }
    }
  }

  return UartRetSize;
}
#endif

/*******************************************************************************
** Traceability     : [cover parentID={A01941DF-99E5-4c5f-8C1D-3B9918445D46}] **
** Syntax: Uart_StatusType Uart_GetStatus(const Uart_ChannelIdType Channel)   **
**                                                                            **
** Service ID      : 221                                                      **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant(Not for the same channel)                      **
**                                                                            **
** Parameters (in) : Channel - Uart channel to be addressed                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :                                                          **
**                   UART_BUSY_TRANSMIT : UART channel busy in transmit       **
**                                                              operation.    **
**                   UART_BUSY_RECEIVE : UART channel busy in receive         **
**                                                                 operation. **
**                   UART_BUSY_TRANSMIT_RECEIVE : UART channel busy in        **
**                                           receive and transmit operation.  **
**                   UART_IDLE : Idle state (no transmits or receive          **
**                               operation in progress).                      **
**                                                                            **
** Description     : API to read an UART channels status.                     **
**                                                                            **
*******************************************************************************/
Uart_StatusType Uart_GetStatus(const Uart_ChannelIdType Channel)
{
  /* [cover parentID={846EB689-8558-41b7-A390-289C89347E6F}]
  [/cover] */
  Uart_StatusType UartChanState;
  const Uart_ChannelInfoType *ChannelInfoPtr;
  Uart_TxStateType ChanTxState;
  Uart_RxStateType ChanRxState;

  /* [cover parentID={92479A7A-869B-4d59-82D6-07B198E98ADA}]
  [/cover] */
  #if((UART_DEV_ERROR_DETECT == STD_ON) || (UART_SAFETY_ENABLE == STD_ON))
  Uart_ReturnType ErrorFlag = UART_E_OK;

  /* [cover parentID={78A91410-5320-48be-B008-E6CFB31C1970}]
  [/cover] */
  /* Check for driver initialization */
  if (Uart_InitStatus == UART_UNINITIALISED)
  {
    /* [cover parentID={CC054C8A-FA63-465f-A018-14A6C4F5BBDD}]
    [/cover] */
    Uart_lReportError(UART_SID_GETSTATUS, UART_E_UNINIT);

    ErrorFlag = UART_E_NOT_OK;
  }
  else
  {
    /* [cover parentID={0C1BC7D9-6123-4c61-8F45-0FE80B830B30}]
    [/cover] */
    /* Check channel identifier */
    ErrorFlag = Uart_lChannelCheck(Channel, UART_SID_GETSTATUS);
  }
  /* Channel state set to idle */
  UartChanState = UART_IDLE;
  /* [cover parentID={D1BD3C7B-E3E4-4996-AE18-8747BC34F0BB}]
  [/cover] */
  if(ErrorFlag == UART_E_OK)
  #endif
  {
    ChannelInfoPtr = &Uart_ChannelInfo[Channel];

    ChanTxState = ChannelInfoPtr->ChanTxState;
    ChanRxState = ChannelInfoPtr->ChanRxState;
    /* [cover parentID={B81D3E43-9F1E-429e-9945-44FB25B5532E}]
    [/cover] */
    /* Return state as BUSY if channel is busy in read or write operation */
    if((ChanTxState != UART_TX_IDLE) && (ChanRxState != UART_RX_IDLE))
    {
      /* [cover parentID={6FAB290D-9EEB-47c5-8B01-3981BBDED395}]
      [/cover] */
      UartChanState = UART_BUSY_TRANSMIT_RECEIVE;
    }
    /* [cover parentID={064F1E42-7DA6-42af-89A2-4C82AC5FF451}]
    [/cover] */
    else if(ChanTxState != UART_TX_IDLE)
    {
      /* [cover parentID={AB7C44DD-1706-4ae1-95F2-3519B4C52D49}]
      [/cover] */
      UartChanState = UART_BUSY_TRANSMIT;
    }
    /* [cover parentID={C4B339C3-B021-41e0-B6E1-BBD423922E93}]
    [/cover] */
    else if(ChanRxState != UART_RX_IDLE)
    {
      /* [cover parentID={DC4B473C-D7B1-4ee0-9602-18A14981BD84}]
      [/cover] */
      UartChanState = UART_BUSY_RECEIVE;
    }
    else
    {
      /* [cover parentID={F5E28BB0-F688-45cb-9864-17EC11807CD0}]
      [/cover] */
      UartChanState = UART_IDLE;
    }
  }

  return UartChanState;
}

#if(UART_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={AAFF463D-E938-46cf-AD91-D7D38B819AC5}] **
**                                                                            **
** Syntax           : void Uart_GetVersionInfo                                **
**                    (                                                       **
**                      Std_VersionInfoType *const VersionInfoPtr             **
**                    )                                                       **
**                                                                            **
** Description      : This API returns the version information of this module **
**                    Note: API is available only when UartVersionInfoApi     **
**                    is configured as true.                                  **
**                                                                            **
** Service ID       : 223                                                     **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : VersionInfoPtr -  Pointer to store the version          **
**                    information of this module                              **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
void Uart_GetVersionInfo(Std_VersionInfoType *const VersionInfoPtr)
{

  /* [cover parentID={645A0E57-36E2-429f-AAE0-92BDA397972C}]
  [/cover] */
  /* [cover parentID={C795D9CF-0731-4fde-A4C1-B675D0DEED5D}]
  [/cover] */
  #if((UART_DEV_ERROR_DETECT == STD_ON) || (UART_SAFETY_ENABLE == STD_ON))
  /* [cover parentID={7811F5AF-419F-4c10-838E-42A772091987}]
  [/cover] */
  if (VersionInfoPtr == NULL_PTR)
  {
    /* [cover parentID={481D5C75-B2F6-49fe-8D43-DCC2CA7BB044}]
    [/cover] */
    /* Report to DET */
    Uart_lReportError(UART_SID_VERINFO, UART_E_PARAM_POINTER);
  }
  else
  #endif
  {
    /* [cover parentID={2CC5836B-0F0F-413f-9FB9-8D009A856E02}]
    [/cover] */
    /* Update version information */
    VersionInfoPtr->moduleID = (uint16)UART_MODULE_ID;
    VersionInfoPtr->vendorID = (uint16)UART_VENDOR_ID;
    VersionInfoPtr->sw_major_version = (uint8)UART_SW_MAJOR_VERSION;
    VersionInfoPtr->sw_minor_version = (uint8)UART_SW_MINOR_VERSION;
    VersionInfoPtr->sw_patch_version = (uint8)UART_SW_PATCH_VERSION;
  }
}
#endif

#if(UART_RX_MODE != UART_POLLING_MODE)
/*******************************************************************************
** Traceability     : [cover parentID={D9A75586-E7FE-4a50-84EB-227EC3EA8421}] **
** Syntax          : void Uart_IsrReceive(const uint8 HwUnit)                 **
**                                                                            **
** Service ID      : 227                                                      **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant(Not for the same HW Unit)                      **
**                                                                            **
** Parameters (in) : HwUnit : ASCLIN channel number.                          **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
** Description     : IRQ handler for RXFIFO level interrupts.                 **
*******************************************************************************/
void Uart_IsrReceive(const uint8 HwUnit)
{
  const Uart_ChannelConfigType *ChannelConfigPtr;
  Ifx_ASCLIN *HwModulePtr;
  Uart_ChannelInfoType *ChannelInfoPtr;
  Uart_ChannelIdType Channel;
  uint8 FlagEnable;
  uint8 ReceiveStatus;
  uint8 FillLevel;

  /* [cover parentID={D1802D50-071C-4c02-A27D-663DB967D727}]
  [/cover] */
  if(HwUnit < UART_MAX_HW_UNIT)
  {
    /* Extract SFR base address */
    HwModulePtr = Uart_HwModuleAddr[HwUnit];
    /* Extract the Channel */
    Channel = Uart_ConfigPtr->Uart_ChannelIdLookupPtr[HwUnit];

    /* [cover parentID={12D2BA2A-6E72-4c41-A54C-DA72053AB408}]
    [/cover] */
    if(Channel != UART_INVALID_CHANNEL)
    {
      ChannelConfigPtr = &(Uart_ConfigPtr->ChannelConfigPtr[Channel]);
      ChannelInfoPtr = &Uart_ChannelInfo[Channel];
      FillLevel = HwModulePtr->RXFIFOCON.B.FILL;
      ReceiveStatus = HwModulePtr->FLAGS.B.RFL;
      FlagEnable = HwModulePtr->FLAGSENABLE.B.RFLE;

      /* Clear RXFIFO level interrupt */
      HwModulePtr->FLAGSCLEAR.B.RFLC = UART_SET_BIT;
      /* [cover parentID={8681911E-E6B4-4e4f-93C4-3E000708677F}]
      [/cover] */
      /* Check receive notification already triggered and rx abort
         is in progress */
      if((ChannelInfoPtr->RxNotfn != UART_RX_NOTFN_TRIGGERED) && \
         (ChannelInfoPtr->ChanRxState != UART_RX_ABORT_IN_PROGRESS) &&
         (ChannelInfoPtr->ChanRxState != UART_RX_STOP_STREAMING_IN_PROGRESS))
      {
        /* [cover parentID={9A2ACC17-F70A-4fe9-92A3-32D1F90FBABD}]
        [/cover] */
        /* Check channel read operation is initiate */
        if((ChannelInfoPtr->ChanRxState == UART_RX_IN_PROGRESS) && \
            (FillLevel >= ChannelInfoPtr->RxIntLevel) && \
            (FlagEnable == UART_SET_BIT) && (ReceiveStatus == UART_SET_BIT))
        {
            /* [cover parentID={DFFA73B7-979B-4960-958F-294C004EC4B0}]
            [/cover] */
            #if(UART_RECEIVE_STREAMING_MODE_API == STD_ON)
            /* [cover parentID={957ED603-0F7C-498a-8F73-833EDE3D2D9D}]
            [/cover] */
            /* Check channel read operation in streaming mode */
            if(ChannelInfoPtr->ChanRxMode == UART_RX_IN_STREAMING_MODE)
            {
            /* [cover parentID={1A756836-FCD1-4cd0-8BD3-7827D485CA0E}]
            [/cover] */
            /* Handle received data in streaming mode*/
            Uart_lReceiveStreamingData(HwModulePtr, ChannelInfoPtr, ChannelConfigPtr);
            }
            else
            #endif
            {
            /* Handle received data in normal read mode*/
            /* [cover parentID={3456BB52-71EF-403e-98FB-31A1697E4306}]
            [/cover] */
             Uart_lRead(HwModulePtr, ChannelInfoPtr, ChannelConfigPtr, 0U);
            }
        }
        #if (UART_SAFETY_ENABLE == STD_ON)
        else
        {
          /* [cover parentID={3BB34A21-5ED6-4db8-9498-8AC989D9852D}]
          [/cover] */
          /* Report spurious interrupt safety error */
          Mcal_ReportSafetyError(UART_MODULE_ID, UART_INSTANCE_ID, \
                               UART_SID_ISR_RECEIVE, UART_E_SPURIOUS_INTERRUPT);
        }
        #endif
      }
      else
      {
        #if (UART_ABORT_READ_API == STD_ON)||(UART_RECEIVE_STREAMING_MODE_API == STD_ON)
        /* Check rx notification already triggered */
        if(ChannelInfoPtr->RxNotfn != UART_RX_NOTFN_NOT_TRIGGERED)
        #endif
        {
          ChannelInfoPtr->RxNotfn = UART_RX_NOTFN_NOT_TRIGGERED;
        }
      }
    }
    #if (UART_SAFETY_ENABLE == STD_ON)
    else
    {
      /* [cover parentID={D56E4A78-DFBA-46ce-ABCC-05600356DB5E}]
      [/cover] */
      Mcal_ReportSafetyError(UART_MODULE_ID, UART_INSTANCE_ID, \
                             UART_SID_ISR_RECEIVE, UART_E_INVALID_HW_UNIT);
    }
    #endif
  }
  #if (UART_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={F00264BD-69F4-4ca1-B075-323832936BD1}]
    [/cover] */
    Mcal_ReportSafetyError(UART_MODULE_ID, UART_INSTANCE_ID, \
                           UART_SID_ISR_RECEIVE, UART_E_INVALID_HW_UNIT);
  }
  #endif
}
#endif

#if(UART_TX_MODE != UART_POLLING_MODE)
/*******************************************************************************
** Traceability     : [cover parentID={9F7D514C-9706-4faf-8A23-43D7ECECDB75}] **
** Syntax          : void Uart_IsrTransmit(const uint8 HwUnit)                **
**                                                                            **
** Service ID      : 228                                                      **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant(Not for the same HW Unit)                      **
**                                                                            **
** Parameters (in) : HwUnit : ASCLIN channel number.                          **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
** Description     : IRQ handler for TXFIFO level interrupts.                 **
**                                                                            **
*******************************************************************************/
void Uart_IsrTransmit(const uint8 HwUnit)
{
  Ifx_ASCLIN *HwModulePtr;
  const Uart_ChannelConfigType *ChannelConfigPtr;
  Uart_ChannelInfoType *ChannelInfoPtr;
  Uart_ChannelIdType Channel;
  uint8 FillLevel;
  uint8 TransmitStatus;
  uint8 FlagEnable;

  /* [cover parentID={E8A72943-353A-4c29-A901-6C3E0351E55A}]
  [/cover] */
  if(HwUnit < UART_MAX_HW_UNIT)
  {
    /* Extract ASCLIN SFR base aaddress */
    HwModulePtr = Uart_HwModuleAddr[HwUnit];
    Channel = Uart_ConfigPtr->Uart_ChannelIdLookupPtr[HwUnit];

    /* [cover parentID={60C730FA-59A5-4c1c-9F40-9904675BA7D8}]
    [/cover] */
    if(Channel != UART_INVALID_CHANNEL)
    {
      ChannelInfoPtr = &Uart_ChannelInfo[Channel];
      FillLevel = HwModulePtr->TXFIFOCON.B.FILL;
      TransmitStatus = HwModulePtr->FLAGS.B.TFL;
      FlagEnable = HwModulePtr->FLAGSENABLE.B.TFLE;
      /* Clear level interrupt */
      HwModulePtr->FLAGSCLEAR.B.TFLC = UART_SET_BIT;
      #if (UART_ABORT_WRITE_API == STD_ON)
      /* [cover parentID={E534B2B4-7FBC-4259-9972-C3C569F19A8E}]
      [/cover] */
      /* Check tx abort is in progress */
      if(ChannelInfoPtr->ChanTxState != UART_TX_ABORT_IN_PROGRESS)
      #endif
      {
        /* [cover parentID={2BD10EE7-A0E9-4a2f-BAE5-F70F55008A1C}]
        [/cover] */
        /* Check spurious interrupt */
        if((FillLevel == 0U) && \
           (ChannelInfoPtr->ChanTxState == UART_TX_IN_PROGRESS) && \
           (TransmitStatus == UART_SET_BIT) && (FlagEnable == UART_SET_BIT))
        {
          ChannelConfigPtr = &(Uart_ConfigPtr->ChannelConfigPtr[Channel]);
          /* [cover parentID={73DC4782-2B43-4e58-B978-82453FD014F9}]
          [/cover] */
          /* Prepare TXFIFO for next transmition */
          Uart_lWrite(HwModulePtr, ChannelInfoPtr, ChannelConfigPtr);
        }
        /* [cover parentID={7FA296C1-82C0-4a20-8125-C939AA3309D7}]
        [/cover] */
        #if (UART_SAFETY_ENABLE == STD_ON)
        else
        {
          /* [cover parentID={EFBE87D7-A4EB-4efe-AE10-8C0EA6303302}]
          [/cover] */
          /* Report spurious interrupt safety error */
          Mcal_ReportSafetyError(UART_MODULE_ID, UART_INSTANCE_ID, \
                                 UART_SID_ISR_TRANSMIT, \
                                 UART_E_SPURIOUS_INTERRUPT);
        }
        #endif
      }
    }
    /* [cover parentID={F83B7ACD-B7B1-4d18-8196-319B307D9D5A}]
    [/cover] */
    #if (UART_SAFETY_ENABLE == STD_ON)
    else
    {
      Mcal_ReportSafetyError(UART_MODULE_ID, UART_INSTANCE_ID, \
                             UART_SID_ISR_TRANSMIT, UART_E_INVALID_HW_UNIT);
    }
    #endif
  }
  /* [cover parentID={3998C435-C8E4-40f1-95C5-45B8DA7CBEC6}]
  [/cover] */
  #if (UART_SAFETY_ENABLE == STD_ON)
  else
  {
    Mcal_ReportSafetyError(UART_MODULE_ID, UART_INSTANCE_ID, \
                           UART_SID_ISR_TRANSMIT, UART_E_INVALID_HW_UNIT);
  }
  #endif
}
#endif

#if((UART_TX_MODE != UART_POLLING_MODE)||(UART_RX_MODE != UART_POLLING_MODE))
/*CYCLOMATIC_Uart_IsrError_JUSTIFICATION:
Uart_IsrError has to verify receive states and transmit complete status flags
and also has to check for error scenarios. For better design readability, the function is not divided further.*/
/*******************************************************************************
** Traceability     : [cover parentID={2B420FC6-404E-4b40-AE40-D0C30BBC3EEC}] **
** Syntax           : void Uart_IsrError( const uint8  HwUnit)                **
**                                                                            **
** Service ID      : 226                                                      **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant  (Not for the same HW Unit)                    **
**                                                                            **
** Parameters (in) : HwUnit : ASCLIN channel number.                          **
**                                                                            **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
** Description     : IRQ handler for error occurred during reception and      **
**                   handle transmit complete interrupt.                      **
*******************************************************************************/
void Uart_IsrError(const uint8 HwUnit)
{
  const Uart_ChannelConfigType *ChannelConfigPtr;
  Ifx_ASCLIN *HwModulePtr;
  Uart_ChannelInfoType *ChannelInfoPtr;
  uint32 RxErrStatus;
  uint32 RxErrFlag;
  uint32 RxErrFlagEnable;
  Uart_RxStateType ChanRxState;
  uint8 TxComplete;
  uint8 TcEnable;
  uint8 Channel;

  #if (UART_SAFETY_ENABLE == STD_ON)
  uint8 ValidInterrupt = 0U;
  #endif
  /* [cover parentID={BBFBF983-4FDA-4c6d-A651-D924446B51D9}]
  [/cover] */
  if(HwUnit < UART_MAX_HW_UNIT)
  {
    /* Extract SFR base address and logical channel id */
    HwModulePtr = Uart_HwModuleAddr[HwUnit];
    Channel = Uart_ConfigPtr->Uart_ChannelIdLookupPtr[HwUnit];

    /* [cover parentID={A58B582D-5103-4932-AC57-D5316F7ABF98}]
    [/cover] */
    /* Check HwUnit is configured */
    if(Channel != UART_INVALID_CHANNEL)
    {
      /* [cover parentID={8A1AFB8F-6828-4543-973A-62F8D0923492}]
      [/cover] */
      ChannelConfigPtr = &(Uart_ConfigPtr->ChannelConfigPtr[Channel]);
      ChannelInfoPtr = &Uart_ChannelInfo[Channel];
      ChanRxState = ChannelInfoPtr->ChanRxState;
      RxErrStatus = HwModulePtr->FLAGS.U & UART_FLAGS_READ_ERROR;
      RxErrFlagEnable = HwModulePtr->FLAGSENABLE.U & UART_FLAGS_READ_ERROR;
      TcEnable = HwModulePtr->FLAGSENABLE.B.TCE;
      TxComplete =  HwModulePtr->FLAGS.B.TC;
      RxErrFlag = RxErrStatus & RxErrFlagEnable;
      TcEnable = TxComplete & TcEnable;

      /* [cover parentID={008EC0B0-6A7C-4b83-B330-886A3FE2DAE5}]
      [/cover] */
      if(((ChanRxState == UART_RX_IN_PROGRESS) && (RxErrFlag != 0U)) || \
         (ChannelInfoPtr->RxNotfn == UART_RX_NOTFN_TRIGGERED))
      {
        #if (UART_SAFETY_ENABLE == STD_ON)
        /* Set valid interrupt flag */
        ValidInterrupt = 1U;
        #endif
        /* [cover parentID={1EE28953-B8D1-410a-90D9-2869C9DA8B24}]
        [/cover] */
        if(ChannelInfoPtr->RxNotfn == UART_RX_NOTFN_NOT_TRIGGERED)
        {
          /* [cover parentID={032857C0-135E-4864-80D5-066D8FD6E4E6}]
          [/cover] */
          Uart_lReceiveError(ChannelConfigPtr, HwModulePtr, ChannelInfoPtr);
        }
        else
        {
          ChannelInfoPtr->RxNotfn = UART_RX_NOTFN_NOT_TRIGGERED;
        }
      }

      /* [cover parentID= {5517FD28-DA85-472c-8D33-72DBBD160939}]
      [/cover] */
      /* Check rx error status */
      if(RxErrStatus != 0U)
      {
        Uart_lClearReadInterrupts(HwModulePtr);
      }

      /* [cover parentID={9997A1F1-B6FF-4d62-8A3D-C542AFA05524}]
      [/cover] */
      /* Check TC is enabled and status flag is set */
      if(TcEnable == 1U)
      {
        #if (UART_SAFETY_ENABLE == STD_ON)
        /* Set valid interrupt flag */
        ValidInterrupt = 1U;
        #endif
        /* [cover parentID={525EA33C-AD42-4ce1-A9A9-DF13DEC08603}]
        [/cover] */
        /* Tx complete */
        Uart_lTrasmitComplete(HwModulePtr, ChannelInfoPtr, ChannelConfigPtr);
      }

      #if (UART_SAFETY_ENABLE == STD_ON)
      #if((UART_ABORT_READ_API == STD_ON) || (UART_ABORT_WRITE_API == STD_ON) || (UART_RECEIVE_STREAMING_MODE_API == STD_ON))

      #if(UART_ABORT_WRITE_API == STD_OFF)
      if(ChanRxState == UART_RX_ABORT_IN_PROGRESS)
      #elif(UART_ABORT_READ_API == STD_OFF)
      if(ChannelInfoPtr->ChanTxState == UART_TX_ABORT_IN_PROGRESS)
      #else
      if((ChannelInfoPtr->ChanTxState == UART_TX_ABORT_IN_PROGRESS) || \
         (ChanRxState == UART_RX_ABORT_IN_PROGRESS))
      #endif
      {
        ValidInterrupt = 1U;
      }
      #endif
      /* [cover parentID={59E7DC37-AA67-40ac-97F0-19EE68B05B01}]
      [/cover] */
      if(ValidInterrupt != 1U)
      {
        /* [cover parentID={9BFFDC2D-163C-4af6-8802-23F832DDB609}]
        [/cover] */
        Mcal_ReportSafetyError(UART_MODULE_ID, UART_INSTANCE_ID, \
                               UART_SID_ISR_ERROR, UART_E_SPURIOUS_INTERRUPT);
      }
      #endif
    }
    /* [cover parentID={55EECB3B-E83C-4620-9C48-C67BAA2EDA1D}]
    [/cover] */
    #if (UART_SAFETY_ENABLE == STD_ON)
    else
    {
      /* [cover parentID={0AF2CCC0-BA1B-4456-A12E-883D055715DA}]
      [/cover] */
      Mcal_ReportSafetyError(UART_MODULE_ID, UART_INSTANCE_ID, \
                             UART_SID_ISR_ERROR, UART_E_INVALID_HW_UNIT);
    }
    #endif
  }
  /* [cover parentID={0CEA974E-360F-4511-8B34-6DA2D9FA3FFB}]
  [/cover] */
  #if (UART_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={4DBDDF99-B054-4da7-B204-A9EC6D34E7F1}]
    [/cover] */
    Mcal_ReportSafetyError(UART_MODULE_ID, UART_INSTANCE_ID, \
                           UART_SID_ISR_ERROR, UART_E_INVALID_HW_UNIT);
  }
  #endif
}
#endif

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
/*******************************************************************************
** Traceability     : [cover parentID={67695152-7FD3-45c1-AE57-FDF026F83D6F}] **
** Syntax           : LOCAL_INLINE uint8 Uart_lHwInitClcReg(const uint8 HwUnit**
**                                                       ,const uint32 Value) **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : NA                                                      **
**                                                                            **
** Parameters (in)  : HwUnit   : ASCLIN Hardware module number                **
**                  : Value    : Value to configure CLC Reg                   **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : 0-Module Clk Enabled                                    **
**                    1-Module Clk Disabled)                                  **
**                                                                            **
** Description      : This function sets the clc register with given value    **
*******************************************************************************/
LOCAL_INLINE uint8 Uart_lHwInitClcReg(const uint8 HwUnit, const uint32 Value)
{
  uint8 ModClkStatus;
  /* [cover parentID={6C01CD27-68A6-4dc0-B9CA-78EA18E712DC}]
  [/cover] */
  /* Update clock register with end init protection */
  UART_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(&Uart_HwModuleAddr[HwUnit]->\
      CLC.U, Value);
  /* [cover parentID={BA9C54D0-B172-40a7-9A82-09A722BDEF88}]
  [/cover] */
  /* Read back clock register */
  ModClkStatus = (uint8)(((Uart_HwModuleAddr[HwUnit]->CLC.U) & \
                          UART_CLC_DISS_MASK) >> UART_CLC_DISS_BITPOS);

  return ModClkStatus;
}

/*******************************************************************************
** Traceability     : [cover parentID={275E2228-8434-4093-B73E-BB5C06F5C997}] **
** Syntax           : static void Uart_lRead                                  **
**  (                                                                         **
**    Ifx_ASCLIN * const HwModulePtr,Uart_ChannelInfoType  *const             **
        ChannelInfoPtr, const Uart_ChannelConfigType *const ChannelConfigPtr, **
        const uint8 ReceiveFillLevel                                          **
**  )                                                                         **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant(Not for same channel)                         **
**                                                                            **
** Parameters (in)  : ChannelConfigPtr - Uart channel to be addressed         **
**                    ReceiveFillLevel - RXFIFO filled level                  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Parameters (inout) : HwModulePtr - ASCLIN SFR address                      **
**                      ChannelInfoPtr - Channel information address          **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Function to copy the data from the RX FIFO buffer to    **
**                    the user specified memory location(App Buffer)          **
*******************************************************************************/
static void Uart_lRead(Ifx_ASCLIN *const HwModulePtr,
                         Uart_ChannelInfoType *const ChannelInfoPtr,
                         const Uart_ChannelConfigType *const ChannelConfigPtr,
                         const uint8 ReceiveFillLevel)
{
  Uart_MemType *BuffPtr;
  uint16 TempReadWord;
  uint16 NumBytesRead;
  uint8 UartFrameLen;
  uint8 ReadCount;
  uint8 RxfifoLevel;

  BuffPtr =  ChannelInfoPtr->RxBuffPtr;
  /* [cover parentID={A59D9101-6770-4321-9BFE-408F4EA6BF3A}]
  [/cover] */
  #if(UART_RX_MODE != UART_INTERRUPT_MODE)
  /* [cover parentID={986F5E3B-512A-4986-A58F-8460B935B529}]
  [/cover] */
  /* Check receive level non zero */
  if(ReceiveFillLevel > 0U)
  {
    /* [cover parentID={8BE6DB37-35AC-4c5c-BEEC-69DFBFBD9F26}]
    [/cover] */
    if(ReceiveFillLevel > ChannelInfoPtr->RxIntLevel)
    {
      /* [cover parentID={B035434A-FDB2-4515-87C0-953C75059278}]
      [/cover] */
      NumBytesRead = ChannelInfoPtr->RxIntLevel;
    }
    else
    {
      /* [cover parentID={968B63CD-2037-48ab-83A7-D336C34CBE58}]
      [/cover] */
      NumBytesRead = ReceiveFillLevel;
    }
  }
  else
  #else
  UNUSED_PARAMETER(ReceiveFillLevel);
  #endif
  {
    /* [cover parentID={D72443F5-AF4C-4c39-8DDC-BBFB31BDB0D8}]
    [/cover] */
    /* Extract number of bytes to be read */
    NumBytesRead = ChannelInfoPtr->RxIntLevel;
  }


  /* [cover parentID={983A2430-3B46-4794-B49C-E97FAE8A8C09}]
  [/cover] */
  /* Extract Uart frame length */
  UartFrameLen = ChannelConfigPtr->DataLength;
  /* [cover parentID={A5FE16F4-F59C-4617-80E6-D3E573F2ACF3}]
  [/cover] */
  ReadCount = 0U;
  /* [cover parentID={CA1F6B0F-F23C-4f38-88CF-04AFCDEC13F3}]
  [/cover] */
  /* [cover parentID={56BA6962-5A3F-4a95-B144-E464C97EB5EA}]
  [/cover] */
  /* Copy all receive bytes in application buffer */
  while(ReadCount < NumBytesRead)
  {
    /* [cover parentID={2B2BC711-9653-45ba-BCF6-F82F44FFB2E3}]
    [/cover] */
    /* [cover parentID={67F098DB-7E17-487e-AE03-3080BD657CB7}]
    [/cover] */
    /* Check frame size is 9 bit */
    if(UartFrameLen >= UART_NINEBIT_DATLEN)
    {
      /* [cover parentID={B2FC982E-216D-4aaa-B6E1-A15B16740E17}]
      [/cover] */
      /* Prepare 16 bits data and update application buffer */
      TempReadWord = (uint16)(HwModulePtr->RXDATA.U);
      BuffPtr[ReadCount] = (Uart_MemType)(TempReadWord);
      BuffPtr[ReadCount + 1U] = (Uart_MemType)(TempReadWord >> \
                                UART_SHIFT_EIGHT_BIT);
      /* Update local pointer and read count */
      ReadCount = ReadCount + UART_STEPSIZE_2BYTE;
    }
    else
    {
      /* [cover parentID={ECB547EB-ECF0-4293-B5D0-F46196B52CB3}]
      [/cover] */
      /* Update application buffer  */
      BuffPtr[ReadCount] = (Uart_MemType)(HwModulePtr->RXDATA.U);
      /* Update read count  */
      ReadCount = ReadCount + UART_STEPSIZE_1BYTE;
    }
  }
  /* [cover parentID={874E9225-DEBB-4636-9D8E-DFF018113111}]
  [/cover] */
  /* Update Uart channel info with total data received */
  ChannelInfoPtr->RxDataLeft -= NumBytesRead;
  ChannelInfoPtr->TotalDataRxd += NumBytesRead;

  /* Update read memory pointer */
  ChannelInfoPtr->RxBuffPtr = &BuffPtr[NumBytesRead];

  /* [cover parentID={672DE060-F07E-49cf-B6EC-7158FB9728F1}]
  [/cover] */
  /* Check read pending data fit in RXFIFO */
  if(ChannelInfoPtr->RxDataLeft > 0U)
  {
    /* [cover parentID={798B2B68-A307-483d-8426-E0D67F19849B}]
    [/cover] */
    if(ChannelInfoPtr->RxDataLeft < UART_BUFFER_SIZE)
    {
      /* [cover parentID={4E5B9683-4063-4a37-8A7F-D6B9317CEF62}]
      [/cover] */
      /* Set RXFIFO interrupt level according to the amount of data remainig */
      RxfifoLevel = ((uint8)ChannelInfoPtr->RxDataLeft - ((uint8)1U));
    }
    else
    {
      /* [cover parentID={258ABEDE-DA05-4976-929D-BD2627F27F3D}]
      [/cover] */
      /* Set interrupt level to RXFIFO buffer size */
      RxfifoLevel = UART_RX_FIFO_INT_LEVEL_MAX;
    }

    HwModulePtr->RXFIFOCON.B.INTLEVEL = RxfifoLevel;
    ChannelInfoPtr->RxIntLevel = RxfifoLevel + 1U;
  }
  else
  {
    /* [cover parentID={67724C3C-C8B1-4702-969A-151ED69307BB}]
    [/cover] */
    /* Flush RXFIFO */
    HwModulePtr->RXFIFOCON.B.FLUSH = UART_SET_BIT;

    /* [cover parentID={61097702-80D2-4138-B596-BA700A294D1A}]
    [/cover] */
    /* Clear RXFIFO overflow and level interrupts */
    Uart_lClearReadInterrupts(HwModulePtr);
    /* [cover parentID={7D227A9D-A5ED-4cf1-BC9D-461981055FBE}]
    [/cover] */
    /* Disable RXFIFO */
    HwModulePtr->RXFIFOCON.B.ENI = UART_CLEAR_BIT;
     /* [cover parentID={9504A03C-78E9-458a-9E72-D8481BDB5136}]
      [/cover] */
    #if (UART_RX_MODE != UART_POLLING_MODE)
      /* [cover parentID={1EC4BD58-00A7-4416-A106-86E5E70FA7B5}]
      [/cover] */
      #if (UART_RX_MODE == UART_MIXED_MODE)
    /* [cover parentID={B7F79AC9-B351-4062-8339-B732ADC8B5BF}]
    [/cover] */
    /* Check if read operation in interrupt mode */
      if(ChannelConfigPtr->RxMode != UART_POLLING_MODE)
    #endif
    {
      /* [cover parentID={79A194DA-75BE-4474-B1D9-A2A1454EDED1}]
      [/cover] */
      Uart_lDisableReadInterrupts(HwModulePtr);
    }
    #endif

    ChannelInfoPtr->RxBuffPtr = NULL_PTR;
    /* [cover parentID={CCCA6ED0-A60C-489b-9774-F693607BC968}]
    [/cover] */
    ChannelInfoPtr->TotalDataRxd = 0U;
    ChannelInfoPtr->RxIntLevel = 0U;
    ChannelInfoPtr->RxNotfn = UART_RX_NOTFN_TRIGGERED;
    ChannelInfoPtr->ChanRxState = UART_RX_IDLE;
    /* [cover parentID={CBE961A1-D62B-4011-A801-6FDBBB90D918}]
    [/cover] */
    /* [cover parentID={6459BCEF-C684-4cb1-A6E8-F531224ED19D}]
    [/cover] */
    /* Check receive notification configured */
    if(ChannelConfigPtr->UartNotif.UartReceiveNotifPtr != NULL_PTR)
    {
      /* [cover parentID={5B177583-CD17-4fc6-AF55-2E1B2FCA01A4}]
      [/cover] */
      /* Call the read notification function */
      ChannelConfigPtr->UartNotif.UartReceiveNotifPtr(UART_E_NO_ERR);
    }
  }
}

#if(UART_RECEIVE_STREAMING_MODE_API == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={9FFEC06A-0EBC-47e5-A282-ACEC274E8F53}] **
** Syntax           : static void Uart_lReceiveStreamingData                  **
**  (                                                                         **
**    Ifx_ASCLIN * const HwModulePtr,Uart_ChannelInfoType  *const             **
**      ChannelInfoPtr, const Uart_ChannelConfigType *const ChannelConfigPtr) **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant(Not for same channel)                         **
**                                                                            **
** Parameters (in)  : ChannelConfigPtr - Uart channel to be addressed         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Parameters (inout) : HwModulePtr - ASCLIN SFR address                      **
**                      ChannelInfoPtr - Channel information address          **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Function to copy received UART data from the hardware   **
**                    FIFO memory to the application buffer in in streaming   **
**                    mode.After copying the data, this function invokes the  **
**                    streaming notification function.                        **
*******************************************************************************/
static void Uart_lReceiveStreamingData(Ifx_ASCLIN *const HwModulePtr,
                         Uart_ChannelInfoType *const ChannelInfoPtr,
                         const Uart_ChannelConfigType *const ChannelConfigPtr)
{
  Uart_MemType *BuffPtr;
  uint16 TempReadWord;
  uint16 NumBytesRead;
  uint8 UartFrameLen;
  uint8 ReadCount;

  /* [cover parentID={C153106A-7F7C-4b46-80FF-50316579342B}]
  [/cover] */
  /* Set buffer pointer with application buffer pointer */
  BuffPtr =  ChannelInfoPtr->RxBuffPtr;

  /* [cover parentID={F6C641EA-89C5-47c2-90BE-0AB04C0821BB}]
  [/cover] */
  /* Extract number of bytes to be read */
  NumBytesRead = HwModulePtr->RXFIFOCON.B.FILL;

    /* [cover parentID={3F182B3C-78BE-4e43-8706-741A7DA6DE54}]
    [/cover] */
    /*check buffer size is more than the received data size */
    if(ChannelInfoPtr->RxBufSize >= NumBytesRead)
    {
      /* Extract Uart frame length */
      UartFrameLen = ChannelConfigPtr->DataLength;

      /* [cover parentID={6F05ED73-AAD1-47cc-97AF-168854A1A293}]
      [/cover] */
      /* Sart Read count from 0 */
      ReadCount = 0U;

      /* [cover parentID={73AC279E-0CE2-4ac0-9022-BBA8D8B5A0E1}]
      [/cover] */
      /* Copy all receive bytes in application buffer */
      while(ReadCount < NumBytesRead)
      {
        /* [cover parentID={4AFD2EDA-8C30-45f2-8E63-F2A5E8C2683D}]
        [/cover] */
        /* [cover parentID={400B8389-18A3-4200-997A-CCD88136548C}]
        [/cover] */
        /* Check frame size is 9 bit */
        if(UartFrameLen >= UART_NINEBIT_DATLEN)
        {
          /* [cover parentID={10E32977-9B78-4612-AC59-9D7EE69A8684}]
          [/cover] */
          /* Prepare 16 bits data and update application buffer */
          TempReadWord = (uint16)(HwModulePtr->RXDATA.U);
          BuffPtr[ReadCount] = (Uart_MemType)(TempReadWord);
          BuffPtr[ReadCount + 1U] = (Uart_MemType)(TempReadWord >> \
                                    UART_SHIFT_EIGHT_BIT);
          /* Update local pointer and read count */
          ReadCount = ReadCount + UART_STEPSIZE_2BYTE;
        }
        else
        {
          /* [cover parentID={F11DF8A3-ACE5-46ae-95C4-FEA9736CE017}]
          [/cover] */
          /* Update application buffer  */
          BuffPtr[ReadCount] = (Uart_MemType)(HwModulePtr->RXDATA.U);
          /* Update read count  */
          ReadCount = ReadCount + UART_STEPSIZE_1BYTE;
        }
      }
      /* [cover parentID={174E429E-6232-4d5e-852D-BACC92E5B5B6}]
      [/cover] */
      /* Flush the RXFIFO  */
      HwModulePtr->RXFIFOCON.B.FLUSH = UART_SET_BIT;

     /* [cover parentID={0FA41AD8-D442-4810-8B71-E032707F980B}]
     [/cover] */
     /* Check receive notification pointer is valid */
     if(ChannelConfigPtr->UartNotif.UartStreamingNotifPtr != NULL_PTR)
        {
            /* [cover parentID={AECC2F47-5F8A-4105-B3BC-0EC30BA4C34F}]
            [/cover] */
            /* Call the streaming notification function */
            ChannelConfigPtr->UartNotif.UartStreamingNotifPtr(UART_E_NO_ERR,\
                                                                NumBytesRead);
        }
    }
    else
    {
        /* [cover parentID={4ACDEA03-BF30-4377-95EE-83D4A6072D33}]
        [/cover] */
        /* Check Runtime error is enabled */
        #if (UART_RUNTIME_ERROR_DETECT == STD_ON)

        /* [cover parentID={1DC396F2-F2D7-4d66-B8C6-2A6B128BD4D0}]
        [/cover] */
        /* Check channel is configured in polling mode */
        if(ChannelConfigPtr->RxMode != UART_POLLING_MODE)
        {
        /* [cover parentID={6BBD9C3F-381E-4390-9490-7D7B4352B876}]
        [/cover] */
        /* Report runtime error with SID ISR error */
        (void)Mcal_Wrapper_Det_ReportRuntimeError((uint16)UART_MODULE_ID,
              UART_INSTANCE_ID, UART_SID_ISR_RECEIVE,
              (uint8)UART_E_INSUFFICIENT_BUFSIZE);
        }
        else
        {
        /* [cover parentID={619CAD25-5495-4742-B3E0-DE5F254CA644}]
        [/cover] */
        /* Report runtime error with SID Main Read */
        (void)Mcal_Wrapper_Det_ReportRuntimeError((uint16)UART_MODULE_ID,
              UART_INSTANCE_ID, UART_SID_MAIN_READ,
              (uint8)UART_E_INSUFFICIENT_BUFSIZE);
        }
        #endif

          /* [cover parentID={54F5874C-8D4D-4279-8B02-EFAD5EDF34D2}]
          [/cover] */
          /* Disable and flush RXFIFO */
          HwModulePtr->RXFIFOCON.B.ENI = UART_CLEAR_BIT;
          HwModulePtr->RXFIFOCON.B.FLUSH = UART_SET_BIT;

          /* [cover parentID={BF9C5D27-41CE-41b6-8F15-70013C36488D}]
          [/cover] */
          /* Clear and disable Rx overflow and level interrupts */
          Uart_lClearReadInterrupts(HwModulePtr);

          /* [cover parentID={DD8CD868-DE07-4905-B19D-BE50D63444A0}]
          [/cover] */
          #if (UART_RX_MODE != UART_POLLING_MODE)
          /* [cover parentID={DC18124C-D93A-4df7-BA4E-7D1EA5C3CAF2}]
          [/cover] */
            #if (UART_RX_MODE == UART_MIXED_MODE)
          /* [cover parentID={958C8206-EA40-40dd-9AC9-C60C4D0BC027}]
          [/cover] */
          /* Check if read operation in interrupt mode */
            if(ChannelConfigPtr->RxMode != UART_POLLING_MODE)
          #endif
          {
            /* [cover parentID={815AC398-55E7-43c5-9EC1-DA988E4CAA0D}]
            [/cover] */
            /* Disable Rx overflow and level interrupts */
            Uart_lDisableReadInterrupts(HwModulePtr);
          }
          #endif


          /* [cover parentID={B7A5D6E0-6CA5-4323-B940-4C8D55D32D1B}]
          [/cover] */
          /* Reset channel info structure */
          ChannelInfoPtr->RxBuffPtr = NULL_PTR;
          ChannelInfoPtr->ChanRxState = UART_RX_IDLE;

            /* [cover parentID={AD3825BD-009E-4e68-B468-01F68F8B3428}]
            [/cover] */
            /* Check streaming notification function pointer not
            equal to NULL    */
            if(ChannelConfigPtr->UartNotif.UartStreamingNotifPtr != NULL_PTR)
            {
            /* [cover parentID={2176AE4E-415B-4078-9422-843936C805C7}]
            [/cover] */
            /*Call streaming notification function */
            ChannelConfigPtr->UartNotif.UartStreamingNotifPtr(UART_E_INSUFFICIENT_BUFSIZE,UART_RECEIVED_DATA_SIZE_ZERO);
            }
      }

}
#endif

#if (UART_RX_MODE != UART_POLLING_MODE)
/*******************************************************************************
** Traceability     : [cover parentID={DF8BBEA1-D8F9-4586-A3A8-B4DEB37B6251}] **
** Syntax        : LOCAL_INLINE void Uart_lEnableReadInterrupts (Ifx_ASCLIN*  **
**                                                        const HwModulePtr)  **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
**                                                                            **
** Parameters (out): HwModulePtr - ASCLIN SFR address                         **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : Function to enable read and read error interrupt         **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Uart_lEnableReadInterrupts(Ifx_ASCLIN *const HwModulePtr)
{
  /* [cover parentID={91EE71DB-78AE-492d-8863-A8562A8B0266}]
  [/cover] */
  /* Enable RXFIFO level, RXFIFO overflow, Parity and Farame error
     interrupt */
    HwModulePtr->FLAGSENABLE.U |= UART_PEE_FEE_RFLE_RFOE_MASK;
}
#endif

/*******************************************************************************
** Traceability     : [cover parentID={75682D01-E6C0-4610-AA06-A016C12AE95F}] **
** Syntax : LOCAL_INLINE void Uart_lTrasmitComplete                           **
**                   ( Ifx_ASCLIN *const HwModulePtr,                         **
**                     Uart_ChannelInfoType *const ChannelInfoPtr,            **
**                     const Uart_ChannelConfigType *const ChannelConfigPtr   **
**                   )                                                        **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : ChannelConfigPtr - Channel configuration pointer         **
**                                                                            **
** Parameters (out): HwModulePtr - ASCLIN SFR address                         **
**                   ChannelInfoPtr - Pointer to channel information          **
** Return value    : None                                                     **
**                                                                            **
** Description     : Function to handle transmit complete and call            **
**                   notification function.                                   **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Uart_lTrasmitComplete(Ifx_ASCLIN *const HwModulePtr,
                           Uart_ChannelInfoType *const ChannelInfoPtr,
                           const Uart_ChannelConfigType *const ChannelConfigPtr)
{
  /* [cover parentID={A1B90D05-47E5-4c46-8724-53E8AB8DA654}]
  [/cover] */
  /* [cover parentID={ED3F7704-5A67-43e1-95DC-915F3BC47308}]
  [/cover] */
  #if (UART_TX_MODE != UART_POLLING_MODE)
    /* [cover parentID={8D3EDA15-9327-4fa4-8D55-F36AAD7DF3B2}]
    [/cover] */
    #if (UART_TX_MODE == UART_MIXED_MODE)
  /* [cover parentID={103725A9-6587-4be8-A66A-DF5B6DAE3045}]
  [/cover] */
  /* Check if write operation in interrupt mode */
    if(ChannelConfigPtr->TxMode != UART_POLLING_MODE)
  #endif
  {
    /* [cover parentID={8CF9B643-6688-4f18-A98A-38DECC376F36}]
    [/cover] */
    /* Disable the tx complete  */
    HwModulePtr->FLAGSENABLE.B.TCE = UART_CLEAR_BIT;
  }
  #endif
  /* [cover parentID={8D2F1FE4-B08A-4f0e-8916-AA68A7878F70}]
  [/cover] */
  /* Clear write interrupts */
  HwModulePtr->FLAGSCLEAR.B.TFLC = UART_SET_BIT;
  HwModulePtr->FLAGSCLEAR.B.TCC = UART_SET_BIT;
  /* Disable TXFIFO and clear transmit complete and TXFIFO level */
  HwModulePtr->TXFIFOCON.B.ENO = UART_CLEAR_BIT;
  /* Flush TXFIFO */
  HwModulePtr->TXFIFOCON.B.FLUSH = UART_SET_BIT;

  /* Reset channel information */
  ChannelInfoPtr->TxBuffPtr = NULL_PTR;
  ChannelInfoPtr->TotalDataTxd = 0U;
  ChannelInfoPtr->TxDataLeft = 0U;
  /* Reset chgannel state */
  ChannelInfoPtr->ChanTxState = UART_TX_IDLE;
  /* [cover parentID={80DA3291-D8DD-49be-88C5-E8CFC9BB9157}]
  [/cover] */
  /* [cover parentID={70B6F9A5-E16C-40de-8CD4-9621202AF56B}]
  [/cover] */
  /* Check transmit notification configured */
  if(ChannelConfigPtr->UartNotif.UartTransmitNotifPtr != NULL_PTR)
  {
    /* [cover parentID={01E417EF-E08B-4a4a-8444-20507A5C90F4}]
    [/cover] */
    /* Call configured transmit notification function */
    ChannelConfigPtr->UartNotif.UartTransmitNotifPtr(UART_E_NO_ERR);
  }
}

/*******************************************************************************
** Traceability     : [cover parentID={EBF95C37-3036-46ac-BEF6-8BB484067D24}] **
** Syntax          : static void Uart_lReceiveError                           **
**                   (                                                        **
**                      const Uart_ChannelConfigType *const ChannelConfigPtr, **
**                      Ifx_ASCLIN *const HwModulePtr,                        **
**                      Uart_ChannelInfoType *const ChannelInfoPtr            **
**                   )                                                        **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant  (Not for the same HW Unit)                    **
**                                                                            **
** Parameters (in) : ChannelConfigPtr: Channel configuration address          **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Parameters (inout): HwModulePtr: ASCLIN SFR address                        **
**                     ChannelInfoPtr : Pointer to Uart Channel Information   **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
** Description     : This function is called when receive error occur Uart    **
**                                                                channel     **
*******************************************************************************/
static void Uart_lReceiveError(
                         const Uart_ChannelConfigType *const ChannelConfigPtr,
                         Ifx_ASCLIN *const HwModulePtr,
                         Uart_ChannelInfoType *const ChannelInfoPtr)
{
  Uart_ErrorIdType RuntimeErrorId;
  uint32 Flag;
  uint8 RecFillLevel;

  /* [cover parentID={70808A98-64CF-4e47-AB03-4CB547C62256}]
  [/cover] */
  Flag = HwModulePtr->FLAGS.U;

  /* [cover parentID={00CF2087-AFC0-4e9c-8B90-0BF4E07ACC42}]
  [/cover] */
  /* Check parity error */
  if ((Flag & UART_FLAGS_PE_MASK) != 0U)
  {
    /* [cover parentID={E0D8F853-9CF2-4d01-93B9-356790F22FEF}]
    [/cover] */
    RuntimeErrorId = UART_E_PARITY_ERR;
  }
  /* [cover parentID={A60CF471-DE7E-4104-A82E-6FCDB94A471E}]
  [/cover] */
  /* Check frame error */
  else if((Flag & UART_FLAGS_FE_MASK) != 0U)
  {
    /* [cover parentID={350F2AA4-E702-4531-8135-63601BF9D834}]
    [/cover] */
    RuntimeErrorId = UART_E_FRAME_ERR;
  }
  /* [cover parentID={34FCA751-EFB7-4a61-9C73-332F2F7BBB18}]
  [/cover] */
  else
  {
    /* [cover parentID={C88B4DC4-6033-43aa-A301-66CFD11B02B0}]
    [/cover] */
    RuntimeErrorId = UART_E_RXFIFO_OVERFLOW;
  }

  /* Clear read interrupt */
  Uart_lClearReadInterrupts(HwModulePtr);
  /* [cover parentID={67AF5CD0-2FBE-4529-A45A-2E179FFC12CA}]
  [/cover] */
  #if(UART_RECEIVE_STREAMING_MODE_API == STD_ON)
  if((RuntimeErrorId == UART_E_RXFIFO_OVERFLOW) && \
    (ChannelInfoPtr->RxDataLeft <= UART_BUFFER_SIZE) &&
    (ChannelInfoPtr->ChanRxMode == UART_RX_IN_READ_MODE))
  #else
  if((RuntimeErrorId == UART_E_RXFIFO_OVERFLOW) && \
    (ChannelInfoPtr->RxDataLeft <= UART_BUFFER_SIZE))
  #endif
  {
    /* [cover parentID={9512703C-DAB4-43b4-B13C-E237379CFCC8}]
    [/cover] */
    RecFillLevel = HwModulePtr->RXFIFOCON.B.FILL;
    Uart_lRead(HwModulePtr, ChannelInfoPtr, ChannelConfigPtr, RecFillLevel);
  }
  else
  {
    /* Disable RXFIFO */
    HwModulePtr->RXFIFOCON.B.ENI = UART_CLEAR_BIT;
    /* [cover parentID={ACE3E6EC-6598-460f-8EF5-4974F827BE8C}]
    [/cover] */
    ChannelInfoPtr->TotalDataRxd = 0U;

    #if (UART_RUNTIME_ERROR_DETECT == STD_ON)
    /* [cover parentID={5C974F7C-16C2-44bf-8350-6A2635027C83}]
    [/cover] */
    /* Report runtime error */
    if(ChannelConfigPtr->RxMode != UART_POLLING_MODE)
    {
      (void)Mcal_Wrapper_Det_ReportRuntimeError((uint16)UART_MODULE_ID,
            UART_INSTANCE_ID,UART_SID_ISR_ERROR,(uint8)RuntimeErrorId);
    }
    else
    {
      (void)Mcal_Wrapper_Det_ReportRuntimeError((uint16)UART_MODULE_ID,
            UART_INSTANCE_ID, UART_SID_MAIN_READ,(uint8)RuntimeErrorId);
    }
    #endif

    ChannelInfoPtr->RxNotfn = UART_RX_NOTFN_TRIGGERED;
    /* Reset channel rx state */
    ChannelInfoPtr->ChanRxState = UART_RX_IDLE;

    #if(UART_RECEIVE_STREAMING_MODE_API == STD_ON)
    /* Check channel read operation in streaming mode */
    /* [cover parentID={1CE96BB7-2735-4829-8CC6-F0DB67F5C165}]
        [/cover] */
    if(ChannelInfoPtr->ChanRxMode == UART_RX_IN_STREAMING_MODE)
    {
        /* [cover parentID={24CF1C07-09FC-4064-8F22-54D537AEC26D}]
        [/cover] */
        /* Check receive notification pointer is valid */
        if(ChannelConfigPtr->UartNotif.UartStreamingNotifPtr != NULL_PTR)
        {
        /* [cover parentID={25227751-C359-43c4-9E0F-23C2DD087360}]
        [/cover] */
        /* Call the streaming notification function */
        ChannelConfigPtr->UartNotif.UartStreamingNotifPtr(RuntimeErrorId,\
                                                                UART_RECEIVED_DATA_SIZE_ZERO);
        }
    }
    else
    #endif
    {
        /* [cover parentID={3FA7B157-4BD2-4f14-9AA5-266D39BAAE71}]
        [/cover] */
        if(ChannelConfigPtr->UartNotif.UartReceiveNotifPtr != NULL_PTR)
        {
        /* [cover parentID={BF027EB9-43C9-4b7a-908F-E2CFFE12AABD}]
        [/cover] */
        /*Call receive notification function */
        ChannelConfigPtr->UartNotif.UartReceiveNotifPtr(RuntimeErrorId);
        }
    }
  }
}

#if(UART_INIT_CHECK_API == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={367E1272-8885-406b-AF34-D5D4383CD5AC}] **
** Syntax           : LOCAL_INLINE Std_ReturnType Uart_lCheckChannelInfo      **
**                    (                                                       **
**                       const uint8 Channel                                  **
**                    )                                                       **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Channel - Uart channel identifier                       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK: Channel information is set to init value.         **
**                    E_NOT_OK: Channel informatin differs from init value    **
**                                                                            **
** Description      : Check channel information                               **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Uart_lCheckChannelInfo(const uint8 Channel)
{
  const Uart_ChannelInfoType *ChannelInfoPtr;
  Std_ReturnType ErrorFlag;

  /* [cover parentID={0103085B-2794-4bbe-B2DF-A7B950066D61}]
  [/cover] */
  ErrorFlag = E_OK;
  ChannelInfoPtr = &Uart_ChannelInfo[Channel];

  /* [cover parentID={F4AD5286-B497-45a7-A6F9-C0CA80E18B37}]
  [/cover] */
  /* Check Uart driver TxState */
  if(ChannelInfoPtr->ChanTxState != UART_TX_IDLE)
  {
    /* [cover parentID={761B79D5-4318-4920-A36C-466EDD0663AB}]
    [/cover] */
    ErrorFlag = E_NOT_OK;
  }
  /* [cover parentID={F4AD5286-B497-45a7-A6F9-C0CA80E18B37}]
  [/cover] */
  /* Check Uart driver RxState */
  else if(ChannelInfoPtr->ChanRxState != UART_RX_IDLE)
  {
    /* [cover parentID={761B79D5-4318-4920-A36C-466EDD0663AB}]
    [/cover] */
    ErrorFlag = E_NOT_OK;
  }
  else
  {
    /* Do nothing */
  }

  return ErrorFlag;
}
#endif


/*******************************************************************************
** Traceability     : [cover parentID={0E2EF27E-87E6-44b6-A8D1-0B0F53693E42}] **
** Syntax           : static void Uart_lHwInitKernelReg                       **
**                      (Ifx_ASCLIN *const HwModulePtr)                       **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : NA                                                      **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (inout) : HwModulePtr: ASCLIN SFR address                       **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : This function resets the Kernel                         **
*******************************************************************************/
static void Uart_lHwInitKernelReg(Ifx_ASCLIN *const HwModulePtr)
{
  uint32 RegUpdate;
  uint32 TimerStatusWaitTicks;
  uint32 DelayTickResolution;

  /* Get STM timer current resolution and calculate maximum number of ticks
     to wait before expected hardware behaviour is occurd- That timer
     correcttion */

  /* [cover parentID={A29E9A04-F971-4938-8DC8-984382154670}]
  [/cover] */
  DelayTickResolution = Mcal_DelayTickResolution();
  /* [cover parentID={7D42675D-7BE4-4c46-81AF-7F7A77BC5ACA}]
  [/cover] */
  TimerStatusWaitTicks  = (UART_MAXTIMEOUT_COUNT / DelayTickResolution);
  /* Do not allow ticks to wait to be zero, if STM timer resolution is lower*/
  if(TimerStatusWaitTicks == 0U)
  {
    TimerStatusWaitTicks++;
  }

  /* [cover parentID={53F37258-33BA-4a24-95FF-60EC7CB51910}]
  [/cover] */
  RegUpdate = HwModulePtr->KRST0.U | UART_SET_BIT;
  /* Update kernel register with end init protection */
  UART_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(&HwModulePtr->KRST0.U, \
      RegUpdate);

  /* [cover parentID={E0D40F8C-5439-4b03-BF96-BA0F595CC45E}]
  [/cover] */
  RegUpdate = HwModulePtr->KRST1.U | UART_SET_BIT;
  /* Update kernel register with end init protection */
  UART_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(&HwModulePtr->KRST1.U, \
      RegUpdate);
  /* [cover parentID={A5AECAA1-573E-4f77-BD20-C5BABD90DB32}]
  [/cover] */
  Uart_lStatusTimeout(TimerStatusWaitTicks, HwModulePtr, UART_REG_TYPE_KRST0, \
                      1U);
  /* [cover parentID={FD383EED-A252-41c2-8766-75EB220372D0}]
  [/cover] */
  RegUpdate = HwModulePtr->KRSTCLR.U | UART_SET_BIT;

  /* Clear kernel reset register status with end init protection */
  UART_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(&HwModulePtr->KRSTCLR.U, \
      RegUpdate);
}

/*******************************************************************************
** Traceability     : [cover parentID={DF7C10DC-6389-4e5d-8C63-09A266323872}] **
** Syntax           : static void Uart_lHwInit(const uint8 HwUnit,            **
**                            Uart_ChannelConfigType *const ChannelConfigPtr) **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : NA                                                      **
**                                                                            **
** Parameters (in)  : HwUnit - ASCLIN Hardware module number                  **
**                    ChannelConfigPtr - Channel configuration address        **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : This function initializes the ASCLIN Hw module          **
*******************************************************************************/
static void Uart_lHwInit(const uint8 HwUnit,
                           const Uart_ChannelConfigType *const ChannelConfigPtr)
{
  Ifx_ASCLIN *HwModulePtr;
  uint32 TimerStatusWaitTicks;
  uint32 DelayTickResolution;

  /* [cover parentID={0C5CFB02-17FE-413e-A9F1-960F716044BE}]
  [/cover] */
  /* Extract ASCLIN SFR base address */
  HwModulePtr = Uart_HwModuleAddr[HwUnit];

  /* Get STM timer current resolution and calculate maximum number of ticks
  to wait before expected hardware behaviour is occured That timer correcttion
  */
  DelayTickResolution = Mcal_DelayTickResolution();
  TimerStatusWaitTicks  = (UART_MAXTIMEOUT_COUNT / DelayTickResolution);
  /* Do not allow ticks to wait to be zero, if STM timer resolution is lower*/
  if(TimerStatusWaitTicks == 0U)
  {
    TimerStatusWaitTicks++;
  }

  /* [cover parentID={BBA16715-4ACF-48b4-97AE-D552CEC1DDA7}]
  [/cover] */
  /* Disable module clock */
  HwModulePtr->CSR.B.CLKSEL = UART_CSRREG_CLKSEL_NOCLK;
  Uart_lStatusTimeout(TimerStatusWaitTicks, HwModulePtr, UART_REG_TYPE_CSR, 0U);
  /* [cover parentID={CC3188E3-5D67-4ab5-9ACE-7B0D39E71894}]
  [/cover] */
  /* Change ASCLIN hardware to init mode */
  HwModulePtr->FRAMECON.B.MODE = UART_FRAMECONREG_INIT_MODE;

  /* [cover parentID={D6E11FE5-C198-4303-8402-C67F41DB53EC}]
  [/cover] */
  /* Set module in ASC mode */
  HwModulePtr->FRAMECON.B.MODE = UART_FRAMECONREG_ASCLIN_MODE;

  /* [cover parentID={07F278FC-7CC5-4f39-9CB3-9162B9184DC5}]
  [/cover] */
  /* Configure baudrate parameters */
  HwModulePtr->BRG.B.NUMERATOR = ChannelConfigPtr->ChanBaudRateNumerator;
  HwModulePtr->BRG.B.DENOMINATOR = ChannelConfigPtr->ChanBaudRateDenominator;
  HwModulePtr->BITCON.B.PRESCALER = ChannelConfigPtr->ChanBaudRatePrescalar;
  HwModulePtr->BITCON.B.OVERSAMPLING = ChannelConfigPtr->ChanOversampling;

  /* Set digital glitch  */
  HwModulePtr->IOCR.B.DEPTH = UART_IOCRREG_DEPTH_VAL;
  /* Configure CTS */
  HwModulePtr->IOCR.B.CTS = ChannelConfigPtr->CTSPin;
  HwModulePtr->IOCR.B.CTSEN = ChannelConfigPtr->CtsEnable;
  HwModulePtr->IOCR.B.RCPOL = ChannelConfigPtr->CtsPolarity;

  /* Configure Sample mode(3 Bit), Sample point, Parity, Collision detection */
  HwModulePtr->BITCON.B.SM = UART_BITCONREG_SM_VAL;
  HwModulePtr->BITCON.B.SAMPLEPOINT = (((ChannelConfigPtr->ChanOversampling) \
                                        >> UART_SHIFT_ONE_BIT) + 1U);
  HwModulePtr->FRAMECON.B.PEN = ChannelConfigPtr->ParityEnable;
  HwModulePtr->FRAMECON.B.ODD = ChannelConfigPtr->Parity;
  HwModulePtr->FRAMECON.B.IDLE = UART_SET_BIT;
  HwModulePtr->FRAMECON.B.STOP = ChannelConfigPtr->StopBits;

  /* Configure TX and RX FIFO */
  if(ChannelConfigPtr->DataLength < UART_NINEBIT_DATLEN)
  {
    HwModulePtr->TXFIFOCON.B.INW = UART_TXFIFOCONREG_INW_1BYTE;
    HwModulePtr->RXFIFOCON.B.OUTW = UART_RXFIFOCONREG_OUTW_1BYTE;
  }
  else
  {
    HwModulePtr->TXFIFOCON.B.INW = UART_TXFIFOCONREG_INW_2BYTE;
    HwModulePtr->RXFIFOCON.B.OUTW = UART_RXFIFOCONREG_OUTW_2BYTE;
  }

  /* Set frame length */
  HwModulePtr->DATCON.B.DATLEN = (ChannelConfigPtr->DataLength - 1U);
  /* Disable loop back mode */
  HwModulePtr->IOCR.B.LB = UART_CLEAR_BIT;
  /* Select receive line */
  HwModulePtr->IOCR.B.ALTI = ChannelConfigPtr->RxPin;

  /* [cover parentID={882A0ABB-B2C0-4858-A8E7-114578D3078C}]
  [/cover] */
  #if (UART_RX_MODE != UART_POLLING_MODE)
  /* [cover parentID={86048A7F-0315-4187-AA96-281FFB1C7A60}]
  [/cover] */
    #if (UART_RX_MODE == UART_MIXED_MODE)
    /* [cover parentID={4E990346-845E-4d92-9DA1-AAE130E52C17}]
    [/cover] */
    /* Check channel RX configured in polling mode */
    if(ChannelConfigPtr->RxMode != UART_POLLING_MODE)
    #endif
      {
        /* [cover parentID={1DE53D6E-21E0-4d68-9566-763E8E84C27D}]
        [/cover] */
        /* Set RXFIFO interrupt mode to combined move mode */
        HwModulePtr->RXFIFOCON.B.FM = UART_COMBINED_MOVE_MODE;
      }
  #endif
      /* [cover parentID={8B5E505A-328A-4789-B5B5-5BEE75D26559}]
      [/cover] */
  #if (UART_TX_MODE != UART_POLLING_MODE)
        /* [cover parentID={A044B012-4825-426b-820D-9B4AC20A45FB}]
        [/cover] */
        #if (UART_TX_MODE == UART_MIXED_MODE)
        /* [cover parentID={E9A00803-E25B-4a91-9415-D034E0013612}]
        [/cover] */
        /* Check channel TX configured in polling mode */
        if(ChannelConfigPtr->TxMode != UART_POLLING_MODE)
        #endif
      {
        /* [cover parentID={16764FF0-34F4-4d8d-9571-008EA1430E51}]
        [/cover] */
        /* Set TXFIFO interrupt mode to combined move mode */
        HwModulePtr->TXFIFOCON.B.FM = UART_COMBINED_MOVE_MODE;
      }
  #endif
  /* [cover parentID={43B19A4C-BBC3-4cf1-87F9-0EDB839278F1}]
  [/cover] */
  /* Enable clock source */
  HwModulePtr->CSR.B.CLKSEL = UART_CSRREG_CLKSEL_CLC;
  Uart_lStatusTimeout(TimerStatusWaitTicks, HwModulePtr, UART_REG_TYPE_CSR, 1U);
}
/*******************************************************************************
** Traceability     : [cover parentID={D59BD65F-70B6-4b5a-AD67-E2A896B85404}] **
** Syntax           : static void Uart_lStatusTimeout                        **
**                                 ( const uint32 WaitTicks,                  **
**                                   const Ifx_ASCLIN *const HwModulePtr,     **
**                                   const uint8 RegisterType,                **
**                                   const uint8 ExpStatValue                 **
**                                 )                                          **
**                                                                            **
** Description      : Function to check that status bit set before timeout    **
**                    happens.                                                **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : NA                                                      **
**                                                                            **
** Parameters (in)  : WaitTicks - Number of ticks to wait for timeout.        **
**                    HwModulePtr - ASCLIN SFR address                        **
**                    RegisterType - Status register type which to be target. **
**                    ExpStatValue - Expected status bit value.               **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Uart_lStatusTimeout(const uint32 WaitTicks,
                                const Ifx_ASCLIN *const HwModulePtr,
                                const uint8 RegisterType,
                                const uint8 ExpStatValue)
{
  uint32 BaseSTMTick;
  uint32 CurrSTMTick;
  uint32 RegVal;
  Std_ReturnType TimeExpired;

  /* [cover parentID={6A5F5BD8-CD64-4e73-96A8-E82D55159073}]
  [/cover] */
  /*Get current STM tick*/
  CurrSTMTick = Mcal_DelayGetTick();
  BaseSTMTick = CurrSTMTick;
  TimeExpired = E_OK;

  /* [cover parentID={6E973609-424A-4c12-A8F4-015A3834242D}]
    Loop for status update done.
  [/cover] */
  do
  {
    /* [cover parentID={76371218-F5C9-48e5-A445-2478CDD56012}]
    [/cover] */
    /* [cover parentID={AAD20E1B-4BB0-485b-878C-5C47CC1582DF}]
    [/cover] */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and
    integer type. Permitted for special function registers.*/
    if(RegisterType == UART_REG_TYPE_CSR)
    {
      /* [cover parentID={A2C2A6A5-21A6-4310-ABA8-CF9FC38D4F5D}]
      [/cover] */
      RegVal = (uint32)HwModulePtr->CSR.B.CON;
    }
    else
    {
      /* [cover parentID={1CFD98F3-822D-406c-BE51-404D8E774125}]
      [/cover] */
      RegVal = HwModulePtr->KRST0.B.RSTSTAT;
    }
    /* [cover parentID={AED264A4-270A-4047-AD27-9C235510C65C}]
    [/cover] */

    /* [cover parentID={A84DE59C-7029-465f-929A-39FED046CDE6}]
    [/cover] */
    /* Check wait time is reached at maxmum timeout configured */
    if((((uint32)((CurrSTMTick - BaseSTMTick) & UART_STM_TICK_OVERFLOW)) >= \
        WaitTicks) && (RegVal != (uint32)ExpStatValue))
    {
      /* [cover parentID={D4847441-A13C-430f-9648-91798A838D6E}]
      [/cover] */
      /* Timeout happend status bit is not set as expected */
      TimeExpired = E_NOT_OK;
    }
    /* [cover parentID={69F6903F-DBB9-4fbb-9BB8-5854C84CC22E}]
    [/cover] */
    /*Get current STM tick*/
    CurrSTMTick = Mcal_DelayGetTick();
    /* [cover parentID={39253746-B158-429f-872A-843663F45392}]
        Timeout not occured and status not updated with expected value.
    [/cover] */
  } while((RegVal != (uint32)ExpStatValue) && (TimeExpired == E_OK));

}

#if (UART_RX_MODE != UART_POLLING_MODE)
/*******************************************************************************
** Traceability     : [cover parentID={63FFEA45-0466-45fd-9AB8-82E59A13CC54}] **
** Syntax : LOCAL_INLINE void Uart_lDisableReadInterrupts (Ifx_ASCLIN         **
**                                                       *const HwModulePtr)  **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): HwModulePtr - ASCLIN SFR address                         **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : Function to disable Rx and Err interrupts                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Uart_lDisableReadInterrupts(Ifx_ASCLIN *const HwModulePtr)
{

  /* [cover parentID={2AF4CAE3-BC96-42d9-BDDD-9E6529DADC8E}]
  [/cover] */
  /* Disable Parity, Frame, RXFIFO overflow and RXFIFO level interrupt errror */
  HwModulePtr->FLAGSENABLE.U &= ~(UART_PEE_FEE_RFLE_RFOE_MASK);

}
#endif

/*******************************************************************************
** Traceability     : [cover parentID={84BCA044-D446-415e-9ADA-6841E25E2565}] **
** Syntax :LOCAL_INLINE void Uart_lClearReadInterrupts(Ifx_ASCLIN *const      **
**                                                             HwModulePtr)   **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
**                                                                            **
** Parameters (out): HwModulePtr - ASCLIN SFR address                         **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : Function to Clear RXFIFO level and Err interrupts        **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Uart_lClearReadInterrupts(Ifx_ASCLIN *const HwModulePtr)
{
  /* [cover parentID={65E044B3-4C48-4c66-8C1A-7EF9801C562B}]
  [/cover] */
  /* Clear Parity, Frame, RxFIFO overflow and RxFIFO level interrupts */
  HwModulePtr->FLAGSCLEAR.U |= (UART_PEE_FEE_RFLE_RFOE_MASK);

}

/*******************************************************************************
** Traceability     : [cover parentID={B89977F1-117E-4821-A4D0-6E8D2EC27FDC}] **
** Syntax : static void Uart_lWrite                                           **
**   (                                                                        **
**      Ifx_ASCLIN* const HwModulePtr,                                        **
**        Uart_ChannelInfoType *const ChannelInfoPtr,                         **
**        const Uart_ChannelConfigType *const ChannelConfigPtr)               **
**   )                                                                        **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for different channel                          **
**                                                                            **
** Parameters (in) : ChannelConfigPtr: Channel configuration address.         **
**                                                                            **
** Parameters (inout): HwModulePtr - ASCLIN SFR address                       **
**                     ChannelInfoPtr- Address of channel information         **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : Function to copy the transmit data from specified memory **
**                   location(App buffer) to TXFIFO                           **
*******************************************************************************/
static void Uart_lWrite(Ifx_ASCLIN *const HwModulePtr,
                           Uart_ChannelInfoType *const ChannelInfoPtr,
                           const Uart_ChannelConfigType *const ChannelConfigPtr)
{
  Uart_MemType *BuffPtr;
  uint16 TempUartWriteData;
  uint8 WriteCount;
  uint8 NumBytesWrite;
  uint8 FrameLength;
  #if (UART_TX_MODE != UART_POLLING_MODE)
  uint8 TxLastFrame;
  #endif
  uint8 StepSize;

  /* [cover parentID={07BF5D56-B1D2-4adb-9700-3E810AB4D166}]
  [/cover] */
  BuffPtr = ChannelInfoPtr->TxBuffPtr;
  FrameLength = ChannelConfigPtr->DataLength;
  #if (UART_TX_MODE != UART_POLLING_MODE)
  TxLastFrame = 0U;
  #endif
  /* [cover parentID={82AEFF58-3513-42a9-A0E2-118AA11365C6}]
  [/cover] */
  if(ChannelInfoPtr->TxDataLeft <= UART_BUFFER_SIZE)
  {
    /* [cover parentID={7DC4D6C7-B581-411d-8DF3-4FA66C7E81AE}]
    [/cover] */
    /* Update number of bytes update in FIFO with number of bytes left */
    NumBytesWrite = (uint8)ChannelInfoPtr->TxDataLeft;

    /* [cover parentID={357E8ACD-12E5-4588-A6D9-9E7403FF7ECC}]
    [/cover] */
    if(FrameLength >= UART_NINEBIT_DATLEN)
    {
      StepSize = UART_STEPSIZE_2BYTE;
    }
    else
    {
      StepSize = UART_STEPSIZE_1BYTE;
    }

    if(NumBytesWrite > StepSize)
    {
      NumBytesWrite -= StepSize;
    }
    /* [cover parentID={1F714919-0CAC-40a9-A9D8-EAD27D68E3E2}]
  [/cover] */
    #if (UART_TX_MODE != UART_POLLING_MODE)
    else
    {
      TxLastFrame = 1U;
    }
    #endif
  }
  else
  {
    /* [cover parentID={8F062649-4602-46dd-BBA7-8516C223B655}]
    [/cover] */
    /* Update number of bytes update in FIFO with fifo size */
    NumBytesWrite = UART_BUFFER_SIZE;
  }

  /* [cover parentID={6DAE0C17-008F-48da-95FE-2A538B923D42}]
    [/cover] */
  #if (UART_TX_MODE != UART_POLLING_MODE)
  /* [cover parentID={8072C2FA-693C-48d0-BDD1-92D8DA733646}]
  [/cover] */
    #if (UART_TX_MODE == UART_MIXED_MODE)
  /* [cover parentID={A40A7F31-165D-4f22-984C-77A491D3B775}]
  [/cover] */
  /* Check if write operation in interrupt mode */
    if(ChannelConfigPtr->TxMode != UART_POLLING_MODE)
    #endif
  {
    /* [cover parentID={06B86483-9371-47b1-9B87-4D802E781DC6}]
    [/cover] */
    HwModulePtr->FLAGSENABLE.B.TFLE = UART_CLEAR_BIT;
  }
  #endif
  /* [cover parentID={DB76F095-188E-477b-9355-7255A294C2A2}]
  [/cover] */
  /* Disable TXFIFO */
  HwModulePtr->TXFIFOCON.B.ENO = UART_CLEAR_BIT;
  /* Clear level interrupt */
  HwModulePtr->FLAGSCLEAR.B.TFLC = UART_SET_BIT;

  /* [cover parentID={39904BE6-5D0E-451e-9803-F2EB76049426}]
     Initiate write count with value 0, Extract frame length
  [/cover] */
  /* [cover parentID={A8D6D7A8-FFB6-4b04-B8B1-3324CAF2AD02}]
        Set write count with 0.
  [/cover] */
  /* Initiate write counter with zero */
  WriteCount = 0U;

  /* [cover parentID={D5CF5384-CFF6-4525-8F9F-A7994560169C}]
  [/cover] */
  while(WriteCount < NumBytesWrite)
  {
    /* [cover parentID={DB1C4A5A-0A58-441f-8764-8D562EB88815}]
    [/cover] */
    if(FrameLength < UART_NINEBIT_DATLEN)
    {
      /* [cover parentID={C7020C46-CDD5-4c84-A95C-3FBA87C632B4}]
      [/cover] */
      /* Update TXFIFO */
      HwModulePtr->TXDATA.U =  BuffPtr[WriteCount];
      WriteCount += UART_TXFIFOCONREG_INW_1BYTE;
    }
    else
    {
      /* [cover parentID={BF676F45-6596-455a-9243-81DCF98B9F58}]
      [/cover] */
      /* Prepare 16 bits data for transmision */
      TempUartWriteData = BuffPtr[WriteCount];
      TempUartWriteData |= (uint16)(((uint16)BuffPtr[WriteCount + 1U])\
                                    << UART_SHIFT_EIGHT_BIT);
      HwModulePtr->TXDATA.U =  TempUartWriteData;
      WriteCount += UART_TXFIFOCONREG_INW_2BYTE;
    }
  }

  /* [cover parentID={4BB76DE2-A713-4f6c-AA5B-E1D7E90289CC}]
  [/cover] */
  if(HwModulePtr->TXFIFOCON.B.FILL == NumBytesWrite)
  {
    /* [cover parentID={3CD3C4F3-4D90-44a3-9875-5B7B5224CF2C}]
    [/cover] */
    /* Update channel information */
    ChannelInfoPtr->TxDataLeft -= NumBytesWrite;
    ChannelInfoPtr->TxBuffPtr = &BuffPtr[NumBytesWrite];
    ChannelInfoPtr->TotalDataTxd += NumBytesWrite;
    /* Clear transmit complete */
    HwModulePtr->FLAGSCLEAR.B.TCC = UART_SET_BIT;
    /* [cover parentID={0EF396C5-8C72-4c68-B192-EDE5BDA0F9E6}]
    [/cover] */
    /* [cover parentID={A8CA0785-78D6-473a-93E5-D36DED6D316A}]
    [/cover] */
    #if (UART_TX_MODE != UART_POLLING_MODE)
      /* [cover parentID={0EF396C5-8C72-4c68-B192-EDE5BDA0F9E6}]
      [/cover] */
      #if (UART_TX_MODE == UART_MIXED_MODE)
      /* [cover parentID={94E119A3-CAC4-4470-9773-9A8001CA40AF}]
      [/cover] */
      /* Check if write operation in interrupt mode */
      if(ChannelConfigPtr->TxMode != UART_POLLING_MODE)
    #endif
    {
      /* [cover parentID={53DB3510-A5D8-4782-A5EC-5379B796BC82}]
      [/cover] */
      /* [cover parentID={3CB61CDF-8DB4-4b2e-9B40-DD975134A34B}]
      [/cover] */
      if(TxLastFrame == 0U)
      {
        /* Enable the TXFIFO level interrupt */
        Uart_lEnableWriteInterrupts(HwModulePtr);
      }
      else
      {
        /* Enable transmit complete interrupt */
        HwModulePtr->TXFIFOCON.B.INTLEVEL = 0U;
        HwModulePtr->FLAGSENABLE.B.TCE = UART_SET_BIT;
      }
    }
    #endif
    /* [cover parentID={5E82E520-9160-4ea2-8799-31E55F8420B1}]
    [/cover] */
    /* Enable TXFIFO */
    HwModulePtr->TXFIFOCON.B.ENO = UART_SET_BIT;
  }
  #if (UART_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={C3674095-1594-4684-B73B-45674942D352}]
    [/cover] */
    if(ChannelInfoPtr->TotalDataTxd != 0U)
    {
      /* [cover parentID={AF17757D-7892-4131-96B9-9F6E092DB3D7}]
      [/cover] */
      if(ChannelConfigPtr->TxMode != UART_POLLING_MODE)
      {
        Mcal_ReportSafetyError(UART_MODULE_ID, UART_INSTANCE_ID, \
                               UART_SID_ISR_TRANSMIT, UART_E_TXFIFO_FILL_ERR);
      }
      else
      {
        Mcal_ReportSafetyError(UART_MODULE_ID, UART_INSTANCE_ID, \
                             UART_SID_MAIN_WRITE, UART_E_TXFIFO_FILL_ERR);
      }
    }
    else
    {
      Mcal_ReportSafetyError(UART_MODULE_ID, UART_INSTANCE_ID, \
                             UART_SID_WRITE, UART_E_TXFIFO_FILL_ERR);
    }
  }
  #endif
}

#if (UART_TX_MODE != UART_POLLING_MODE)
/*******************************************************************************
** Traceability     : [cover parentID={23E00FBA-5293-44fd-A135-7BF14799B2E9}] **
** Syntax : LOCAL_INLINE void Uart_lEnableWriteInterrupts                     **
**                   ( Ifx_ASCLIN *const HwModulePtr)                         **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for different channel.                         **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): HwModulePtr - ASCLIN SFR address                         **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : Function to enable interrupts for write Operation        **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Uart_lEnableWriteInterrupts(Ifx_ASCLIN *const HwModulePtr)
{
  /* [cover parentID={87CADC4F-2F55-4d7d-B8F0-EB2EA0F7A1A9}]
  [/cover] */
  /* Set TXFIFO interrupt level and enable TXFIFO overflow and level flags */
  HwModulePtr->TXFIFOCON.B.INTLEVEL = 0U;
  /* [cover parentID={A7106EFF-D9F3-4cc3-822E-946D4ADAC511}]
  [/cover] */
  HwModulePtr->FLAGSENABLE.B.TFLE = UART_SET_BIT;
}
#endif

#if ((UART_DEV_ERROR_DETECT == STD_ON) || (UART_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={9E74D621-957D-48af-8073-0F1F1B66E540}] **
** Syntax : static Uart_ReturnType Uart_lCheckDetError                        **
**                       (                                                    **
**                         const uint8 Channel,                               **
**                         const Uart_SizeType Size,                          **
**                         const uint8 ApiId,                                 **
**                         const Uart_MemType *const MemPtr                   **
**                       )                                                    **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : Channel - Uart channel identifier                        **
**                   Size - Number bytes to be read/write                     **
**                   ApiId - Api identifier                                   **
**                   MemPtr: Memory address where read or write operation     **
**                           to be performed.                                 **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : UART_E_NOT_OK: DET is reported                           **
**                   UART_E_OK: DET is not reported                           **
** Description     : Function validate input parameter's of read and write    **
**                   api and report DET in case of invalid parameter value.   **
**                                                                            **
*******************************************************************************/
static Uart_ReturnType Uart_lCheckDetError(const uint8 Channel,
                                           const Uart_SizeType Size,
                                           const uint8 ApiId,
                                           const Uart_MemType *const MemPtr)
{
  Uart_ReturnType RetValue;
  /* [cover parentID={CB7C8AB0-F5C7-41df-858A-28FFD67DDDE8}]
  [/cover] */
  if (Uart_InitStatus == UART_UNINITIALISED)
  {
    /* [cover parentID={66889E1A-1BB4-4976-97EA-ED19668B7C1B}]
    [/cover] */
    /* Report driver not initialized DET */
    Uart_lReportError(ApiId, UART_E_UNINIT);
    RetValue = UART_E_NOT_OK;
  }
  /* [cover parentID={CAF9000F-B48A-45c7-B9C2-A5F02775CFF2}]
  [/cover] */
  else if(MemPtr == NULL_PTR)
  {
    /* [cover parentID={55C78364-2920-40f6-8F3A-92C810536C1D}]
    [/cover] */
    /* Report invalid pointer DET  */
    Uart_lReportError(ApiId, UART_E_PARAM_POINTER);

    RetValue = UART_E_NOT_OK;
  }
  else
  {
    /* Check channel is configured */
    RetValue = Uart_lChannelCheck(Channel, ApiId);

    /* [cover parentID={35434EEA-D6E8-4a95-81AC-994568EF3C46}]
    [/cover] */
    if(RetValue == UART_E_OK)
    {
      /* Check valid size */
      RetValue = Uart_lCheckSize(Channel, Size, ApiId);
      /* [cover parentID={A536DE24-AFCA-40cd-B781-190F2935470C}]
      [/cover] */
      if(RetValue == UART_E_OK)
      {
        /* Check SID */
        if(ApiId == UART_SID_WRITE)
        {
          /* [cover parentID={DB0ED46B-34F6-42b8-86A0-4204ED5DC638}]
          [/cover] */
          if(Uart_ChannelInfo[Channel].ChanTxState != UART_TX_IDLE)
          {
            RetValue = UART_E_BUSY;
          }
        }
        else
        {
          /* [cover parentID={DB0ED46B-34F6-42b8-86A0-4204ED5DC638}]
          [/cover] */
          if(Uart_ChannelInfo[Channel].ChanRxState != UART_RX_IDLE)
          {
            RetValue = UART_E_BUSY;
          }
        }

        /* Check driver is ready for transmit/receive */
        if(RetValue == UART_E_BUSY)
        {
          /* [cover parentID={14D73258-FF34-48eb-9B7E-F420479E84EC}]
          [/cover] */
          Uart_lReportError(ApiId, UART_E_STATE_BUSY);
        }
      }
    }
  }

  return RetValue;
}
#endif

#if ((UART_DEV_ERROR_DETECT == STD_ON) || (UART_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={FF86A3F1-3924-45fa-B542-8A271B79AB66}] **
** Syntax : static Uart_ReturnType Uart_lCheckSize                            **
**                                     (                                      **
**                                       const uint8 Channel,                 **
**                                       const Uart_SizeType Size,            **
**                                       const uint8 ApiId                    **
**                                     )                                      **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : Channel - Uart channel identifier                        **
**                   Size - Number bytes to be read/write                     **
**                   ApiId - Api from where this function is called.          **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : UART_E_NOT_OK: Size is not valid.                        **
**                   UART_E_OK: Size is valid.                                **
** Description     : Function to check size requested in read and write api.  **
**                                                                            **
*******************************************************************************/
static Uart_ReturnType Uart_lCheckSize(const uint8 Channel,
                                       const Uart_SizeType Size,
                                       const uint8 ApiId)
{

  Uart_ReturnType RetVal;
  /* [cover parentID={7879EC08-B2B4-41f7-B3EF-B5E2F3D36F12}]
  [/cover] */
  /* Set return value with initial state */
  RetVal = UART_E_OK;

  /* [cover parentID={6FE0619C-615D-44ba-98D6-366D2BF646E8}]
  [/cover] */
  if(Size == 0u)
  {
    /* [cover parentID={EB3FBB3D-AD2F-4866-93DE-AED4BE360A87}]
    [/cover] */
    RetVal = UART_E_NOT_OK;
  }
  /* [cover parentID={BCC4AE15-DB86-4fc2-979E-DA2D2CE60AD1}]
  [/cover] */
  /* [cover parentID={84E2D439-2572-469d-B9F3-8E10327393B8}]
  [/cover] */
  else if(Uart_ConfigPtr->ChannelConfigPtr[Channel].DataLength >= \
          UART_NINEBIT_DATLEN)
  {
    /* [cover parentID={0C43FAEA-0F58-45af-8537-4DBE2498C3AC}]
    [/cover] */
    /* Check requested size is multiple of 2 in case frame length
    greater than is 9 bit */
    if((Size & 1U) != 0U)
    {
      /* [cover parentID={53184D86-DD86-4590-B7AA-395BA2671867}]
      [/cover] */
      RetVal = UART_E_NOT_OK;
    }
  }
  else
  {
    /* Do nothing */
  }

  /* [cover parentID={278601F6-0ADF-4f6e-8731-70315369B404}]
  [/cover] */
  if(RetVal != UART_E_OK)
  {
    /* [cover parentID={590DF40B-3DDF-4c6e-A786-B190A4817B87}]
    [/cover] */
    /* Report DET in case of invalid size */
    Uart_lReportError(ApiId, UART_E_INVALID_SIZE);
  }

  return RetVal;
}
#endif

#if ((UART_DEV_ERROR_DETECT == STD_ON) || (UART_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={CBA3F21A-CEDD-4050-AF8B-F86E61EBE841}] **
** Syntax : static Uart_ReturnType Uart_lChannelCheck                         **
**  (                                                                         **
**    const Uart_ChannelIdType Channel, const uint8 ApiId                     **
**  )                                                                         **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : Channel - Uart channel to be addressed                   **
**                   ApiId - Service id of the Api which calls this function  **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : UART_OK: Channel is configured.                          **
**                   UART_NOT_OK: Channel is not configured                   **
**                                                                            **
** Description     : Function to validate channel identifier                  **
**                                                                            **
*******************************************************************************/
static Uart_ReturnType Uart_lChannelCheck(const Uart_ChannelIdType Channel,
                                          const uint8 ApiId)
{
  /* [cover parentID={513E0CFE-0486-4d3c-9B79-3B7E7BD92408}]
  [/cover] */
  Uart_ReturnType RetValue = UART_E_NOT_OK;
  /* [cover parentID={0F8216D2-1973-4a3f-BA4F-0A47049CBD6F}]
  [/cover] */

  /* [cover parentID={A5A5FFDF-54B7-4206-A5FB-40FAFD8263C0}]
  [/cover] */
  /* Check requested channel id is less than number of channel configured */
  if(Channel >= Uart_ConfigPtr->NoOfChannels)
  {
    /* [cover parentID={41323DE9-B2E7-4e57-A37C-F533613974DA}]
    [/cover] */
    Uart_lReportError(ApiId, UART_E_INVALID_CHANNEL);
  }
  else
  {
    /* [cover parentID={4877005F-7EDE-467e-9645-E451DFD58282}]
    [/cover] */
    RetValue = UART_E_OK;
  }

  return RetValue;
}
#endif

#if (UART_DEV_ERROR_DETECT == STD_ON) || (UART_SAFETY_ENABLE == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={DBC6728F-35A8-4683-B3D9-D4F80889BF99}] **
** Syntax : static void Uart_lReportError( const uint8 ApiId,                 **
**                                         const uint8 ErrorId)               **
**                                                                            **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  ApiId - Service ID of the API reporting an error         **
**                   ErrorId - ID of the error reported                       **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
** Description :    Function to report Safety Error and DET                   **
*                                                                             **
*******************************************************************************/
static void Uart_lReportError(const uint8 ApiId, const uint8 ErrorId)
{
  /* [cover parentID={72DF3930-6D1C-423e-A06B-D68D2E82DCB6}]
  [/cover] */
  #if (UART_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={DD35001C-BCB0-4f89-B1D5-BB67FE25EC4B}]
  [/cover] */
  (void)Det_ReportError(UART_MODULE_ID, UART_INSTANCE_ID, ApiId, ErrorId);
  #endif

  #if (UART_SAFETY_ENABLE == STD_ON)
  Mcal_ReportSafetyError(UART_MODULE_ID, UART_INSTANCE_ID, ApiId, ErrorId);
  #endif
}
#endif
/* [cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
Callout Memory section not used in UART driver
[/cover]*/
#define UART_STOP_SEC_CODE_ASIL_B_LOCAL
/* [cover parentID={84FCEDA9-01F7-4f48-AC8B-47FFAF8417E4}] */
/*  [/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Uart_MemMap.h"
/*******************************************************************************
**                               End of File                                  **
*******************************************************************************/
