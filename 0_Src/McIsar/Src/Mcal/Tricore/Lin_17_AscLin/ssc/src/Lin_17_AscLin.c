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
**  FILENAME     : Lin_17_AscLin.c                                            **
**                                                                            **
**  VERSION      : 29.0.0                                                     **
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
**  DESCRIPTION  : Lin Driver source file                                     **
**                                                                            **
**  SPECIFICATION(S) : Specification of Lin Driver, AUTOSAR Release 4.2.2     **
**                                                                and 4.4.0   **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/*[cover parentID={A6441ED2-CF72-40f9-B26D-BD0C8B9BBA95}] Naming Convention of
  API [/cover]*/

/*[cover parentID={8302A971-6646-47d4-A47F-7928F4305FE5}][/cover]*/
/* Inclusion of ASCLIN Register structure header file */

/*[cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}] single source and
   multiple plugins [/cover]*/

/*[cover parentID={F8C4D3E6-63EA-4c56-BA03-7DB3B44D5C20}] Lin_17_AscLin_Irq.c
File to be developed by user [/cover] */

#include "IfxAsclin_reg.h"

/* Inclusion of SRC Register structure header file */
#include "IfxSrc_reg.h"

/* Own header file, this includes own configuration file also */
#include "Lin_17_AscLin.h"

#if (MCAL_AR_VERSION == MCAL_AR_422)
#include "LinIf_Cbk.h"
#else
#include "LinIf.h"
#endif

#include "IfxAsclin_bf.h"

#if(LIN_17_ASCLIN_INIT_API_MODE != LIN_17_ASCLIN_MCAL_SUPERVISOR_MODE)
#include "McalLib_OsStub.h"
#endif

/* Inclusion from Diagnostic Error Manager File */
#if(LIN_17_ASCLIN_HW_ERROR_DEM_REPORT == LIN_17_ASCLIN_DEM_REPORT_ENABLED)
#include "Mcal_Wrapper.h"
#endif

/* Conditional Inclusion of Developement Error Tracer File */
#if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif /* (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON) */


/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/

/* Version checks */

#ifndef LIN_17_ASCLIN_SW_MAJOR_VERSION
#error "LIN_17_ASCLIN_SW_MAJOR_VERSION is not defined. "
#endif

#ifndef LIN_17_ASCLIN_SW_MINOR_VERSION
#error "LIN_17_ASCLIN_SW_MINOR_VERSION is not defined. "
#endif

#ifndef LIN_17_ASCLIN_SW_PATCH_VERSION
#error "LIN_17_ASCLIN_SW_PATCH_VERSION is not defined."
#endif

/* Check for Correct inclusion of headers */
#if ( LIN_17_ASCLIN_SW_MAJOR_VERSION != 20U )
#error "LIN_17_ASCLIN_SW_MAJOR_VERSION does not match. "
#endif
#if ( LIN_17_ASCLIN_SW_MINOR_VERSION != 25U )
#error "LIN_17_ASCLIN_SW_MINOR_VERSION does not match. "
#endif

#if ( LIN_17_ASCLIN_SW_PATCH_VERSION != 0U )
#error "LIN_17_ASCLIN_SW_PATCH_VERSION does not match."
#endif

#ifndef LIN_17_ASCLIN_AR_RELEASE_MAJOR_VERSION
#error "LIN_17_ASCLIN_AR_RELEASE_MAJOR_VERSION is not defined."
#endif


/*[cover parentID={0769BB51-2DA6-4bd2-A73E-9FDBFAB30329}] Modules version
consistency check [/cover]*/
#if ( LIN_17_ASCLIN_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION)
#error "LIN_17_ASCLIN_AR_RELEASE_MAJOR_VERSION does not match."
#endif

#ifndef LIN_17_ASCLIN_AR_RELEASE_MINOR_VERSION
#error "LIN_17_ASCLIN_AR_RELEASE_MINOR_VERSION is not defined."
#endif

#if ( LIN_17_ASCLIN_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION)
#error "LIN_17_ASCLIN_AR_RELEASE_MINOR_VERSION does not match."
#endif

#ifndef LIN_17_ASCLIN_AR_RELEASE_REVISION_VERSION
#error "LIN_17_ASCLIN_AR_RELEASE_REVISION_VERSION is not defined."
#endif


#if(LIN_17_ASCLIN_AR_RELEASE_REVISION_VERSION != MCAL_AR_RELEASE_REVISION_VERSION)
#error "LIN_17_ASCLIN_AR_RELEASE_REVISION_VERSION does not match."
#endif

#if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)

#ifndef DET_AR_RELEASE_MAJOR_VERSION
#error "DET_AR_RELEASE_MAJOR_VERSION is not defined."
#endif

/* [cover parentID={F090B58A-D80C-4b1a-8EA2-3880C205B571}]
    [/cover] */
#if (DET_AR_RELEASE_MAJOR_VERSION != LIN_17_ASCLIN_AR_RELEASE_MAJOR_VERSION)
#error "DET_AR_RELEASE_MAJOR_VERSION does not match."
#endif

#endif
/* End for LIN_17_ASCLIN_DEV_ERROR_DETECT */


/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

#define LIN_17_ASCLIN_FRAMECON_INIT_MODE (0x0U)/* ASCLIN INIT mode */
#define LIN_17_ASCLIN_FRAMECONREG_LIN_MODE (0x3U) /* ASCLIN LIN mode */
#define LIN_17_ASCLIN_FRAMECONREG_PEN_VAL (0x0U) /* Disable Parity */
#define LIN_17_ASCLIN_FRAMECONREG_CEN_VAL (0x1U) /* Collision detection enable*/
#define LIN_17_ASCLIN_FRAMECONREG_STOP_VAL (0x1U) /* 1 stop bit */
#define LIN_17_ASCLIN_FRAMECONREG_LEAD_VAL (0x2U) /* 1 bit Lead value */

#define LIN_17_ASCLIN_BITCONREG_OS_VAL (0xFU) /* Oversampling value = 15X */
#define LIN_17_ASCLIN_BITCONREG_SM_VAL (0x1U) /* Sample Mode = 3 bit */
#define LIN_17_ASCLIN_BITCON_SP_VAL (0x9U) /* Sample point = 9 */

#if (LIN_17_ASCLIN_MASTER_CH_PRESENT == STD_ON)
#define LIN_17_ASCLIN_CLASSIC_CHECKSUM (0x0U) /* Classic Checksum */
#endif

#define LIN_17_ASCLIN_IOCRREG_DEPTH_VAL (0x0U)/*digital Glitch Filter Disabled*/

#define LIN_17_ASCLIN_LINCONREG_CSEN_VAL (0x1U) /* Hw Checksum Enable  */
#define LIN_17_ASCLIN_LINCON_MASTER_ENABLE (0x1U) /* Enable LIN as Master */

#if (MCAL_AR_VERSION == MCAL_AR_440)
/* Slave Supported */

#define LIN_17_ASCLIN_LINCON_SLAVE_ENABLE (0x0U) /* Enable LIN as Slave */
#define LIN_17_ASCLIN_FRAMECON_IDLE_SLAVE_VAL (0x0U) /*Lead value for SLAVE */
/* The detection of the break pulse defined as low pulse with a minimum duration
   of 11 bit times and 1 additional bit time for the delimiter */
#define LIN_17_ASCLIN_LINBTIMER_SLAVE_BREAK_VAL (0xCU) /* Break = 12 bit/s */

#endif /* Slave Supported */

/* The detection of the break pulse defined as low pulse with a minimum duration
   of 13 bit times and 1 additional bit time for the delimiter */
#define LIN_17_ASCLIN_LINBTIMER_MASTER_BREAK_VAL (0xEU) /* Break = 14 bit/s */

#define LIN_17_ASCLIN_LINHTIMER_HEADER_VAL (48U) /* Header Timeout = 48 bits */

#define LIN_17_ASCLIN_CSRREG_CLKSEL_NOCLK (0x0U) /* No Clock  */

#if (LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT == STD_ON)
/* Falling edge detect */
#define LIN_17_ASCLIN_FLAGSREG_FED  ((uint32)0x1 << IFX_ASCLIN_FLAGS_FED_OFF)
#endif

/* AscLin Status Flags */

/* Transmit header Completed */
#if (LIN_17_ASCLIN_MASTER_CH_PRESENT == STD_ON)
#define LIN_17_ASCLIN_FLAGSREG_TH ((uint32)0x1 << IFX_ASCLIN_FLAGS_TH_OFF)
#endif

/* Transmit Response Completed */
#define LIN_17_ASCLIN_FLAGSREG_TR ((uint32)0x1 << IFX_ASCLIN_FLAGS_TR_OFF)
/* Receive Response completed  */
#define LIN_17_ASCLIN_FLAGSREG_RR ((uint32)0x1 << IFX_ASCLIN_FLAGS_RR_OFF)

#if ((MCAL_AR_VERSION == MCAL_AR_440) &&                                      \
     (LIN_17_ASCLIN_SLAVE_CH_PRESENT == STD_ON))
     /* Receive header completed  */
#define LIN_17_ASCLIN_FLAGSREG_RH ((uint32)0x1 << IFX_ASCLIN_FLAGS_RH_OFF)
/* Mask to clear all flags except RH */
#define LIN_17_ASCLIN_NOT_RH_FLAGSCLEAR (0xDFFFE06BU)
/* Macro for Break detect bit */
#define LIN_17_ASCLIN_BREAK_DETECTED  (1U)
/* Macro for no Break detect */
#define LIN_17_ASCLIN_BREAK_NOT_DETECTED  (0U)
#endif

#if (LIN_17_ASCLIN_MASTER_CH_PRESENT == STD_ON)
/* Mask for PID to remove Parity bits */
#define LIN_17_ASCLIN_PID_MASK_WO_PARITY  (63U)
#endif

/* Mask to Clear All register Flags */
#define LIN_17_ASCLIN_FLAGSCLEAR_VAL (0xDFFFE06FU)
/* Mask to clear MS_TX,MS_RX and MS_HO flags */
#define LIN_17_ASCLIN_FLAGSCLEAR_MASK (0x1F54000BU)

#if (LIN_17_ASCLIN_MASTER_CH_PRESENT == STD_ON)
/* RXFIFO fill value when only ID is recieved */
#define LIN_17_ASCLIN_RXFIFOVAL_IDONLY    (1U)

/*Response timeout = ((10 * (Datalength + 1) * 1.4)
                   = ((Datalength +1) * (14))*/
#define LIN_17_ASCLIN_TOLERANCE_VALUE   (14UL)
#endif

#if (LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT == STD_ON)
#define LIN_17_CLEAR_EVENT_BIT            (1U)
#endif
#define LIN_17_ASCLIN_ENABLE_FLAG         (1U)
#define LIN_17_ASCLIN_DISABLE_FLAG        (0U)

#if (LIN_17_ASCLIN_MASTER_CH_PRESENT == STD_ON)
#define LIN_17_ASCLIN_SLEEPCMD_DL         (8U)
#define LIN_17_ASCLIN_SLEEPCMD_PID        (60U)
#define LIN_17_ASCLIN_SLEEPCMD_DATA0      (0U)
#define LIN_17_ASCLIN_SLEEPCMD_DATA1TO7   (255U)
#define LIN_17_ASCLIN_SLEEPCMD_DATLEN     (8U)
#endif

#define LIN_17_ASCLIN_TXFIFOCON_INW       (0x40U)
#define LIN_17_ASCLIN_RXFIFOCON_OUTW      (0x40U)

/* Wake up low pulse in duration of 250 micro seconds to 5ms can be generated
  by the module. Reason for selecting 0x1F0 is to get 5 consecutive dominant bit
  along with stop bit and falls in the wake up pulse duration  */
#define LIN_17_ASCLIN_WAKEUP_VALUE               (0x1F0U)

/* LIN Buffer Size */
#define LIN_17_ASCLIN_RESP_BUF_SIZE               (9U)

/* Sleep Request Macros */
#define LIN_17_ASCLIN_SLEEP_NOT_REQ               (0U)
#define LIN_17_ASCLIN_SLEEP_REQ                   (1U)

/* TR: Transmit Response End Flag
 * HT: Header Timeout Flag
 * TFO: Transmit FIFO Overflow Flag
 * CE: Collision Detection Error Flag
 * RT: Response Timeout Flag
 * FE: Framing Error Flag
 * LP: LIN Parity Error Flag
 * RR: Receive Response End Flag
 * RFO: Receive FIFO Overflow Flag
 * RFU: Receive FIFO Underflow Flag
 * LC: LIN Checksum Error Flag
 * TH: Transmit Header End Flag
 * RT: Response Timeout Flag
 * TC: Transmission Completed Flag*/

#if ((MCAL_AR_VERSION == MCAL_AR_440) && (LIN_17_ASCLIN_SLAVE_CH_PRESENT == STD_ON))
/* Receive Header */
/* RHE | HTE | CEE | FEE | LAE | LPE */
#define LIN_17_ASCLIN_SLAVE_RECEIVER_HEADER_INTERRUPTS     (0x02CC0004)

/* Receive response */
/* RRE | RFOE | RFUC | LCE | FEE | RTE | BDE */
#define LIN_17_ASCLIN_SLAVE_RECEIVE_RESPONSE_INTERRUPTS    (0x0D340008)

/* Transmit response */
/* TRE | TFOE | CEE | BDE */ /* FLAGSET - TRRQS - SET */
#define LIN_17_ASCLIN_SLAVE_TRANSMIT_RESPONSE_INTERRUPTS   (0x42200002)

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
/* Receive Header */
/* HTE | CEE | FEE | | LPE | LAE (Not enabled - since Autbaud is not enabled) */
#define LIN_17_ASCLIN_SLAVE_RECEIVER_HEADER_ERRORS  (0x024C0000)
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
/* Receive response */
/* RFOE | RFUC | LCE | FEE | RTE | BDE */
#define LIN_17_ASCLIN_SLAVE_RECEIVE_RESPONSE_ERRORS (0x0F340000)
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
/* Transmit response */
/* TFOE | CEE | BDE */
#define LIN_17_ASCLIN_SLAVE_TRANSMIT_RESPONSE_ERRORS (0x42200000)

#define LIN_17_ASCLIN_FE_FLAG_BIT ((uint32)0x1 << IFX_ASCLIN_FLAGS_FE_OFF)
#define LIN_17_ASCLIN_LC_FLAG_BIT ((uint32)0x1 << IFX_ASCLIN_FLAGS_LC_OFF)

/*Maximum Response timeout value for max datalength 8 */
/* Calculate the Response timeout value as per LIN2.1
   Response timeout = ((10 * (Datalength + 1) * 1.4))
                    = ((Datalength +1) * (14))
                    = ((8+1) * (14))
                    = 126
*/
#define LIN_17_ASCLIN_MAX_RESPONSE_TIMEOUT   (126U)
#endif

#if (LIN_17_ASCLIN_MASTER_CH_PRESENT == STD_ON)
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
/* TH | HT | CE | BD */
#define LIN_17_ASCLIN_MASTER_TRANSMIT_HEADER    (0x02480001U)

/* TFO | CE | BD */
#define LIN_17_ASCLIN_MASTER_TRANSMIT_RESPONSE  (0x42200002U)
/* RFU | RFO | LC | BD | RT | HT */
#define LIN_17_ASCLIN_MASTER_RECEIVE_RESPONSE   (0x0D340008U)
#endif

#if (LIN_17_ASCLIN_MASTER_CH_PRESENT == STD_ON)
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
/* CE |LP| HT */
#define LIN_17_ASCLIN_MASTER_TRANSMIT_HEADER_ERROR    (0x02480000U)
/* CE */
#define LIN_17_ASCLIN_MASTER_RESPONSE_TRANSMIT_ERROR  (0x02000000U)
#endif


#if (LIN_17_ASCLIN_MASTER_CH_PRESENT == STD_ON)
/* Only TRE interrupt enabled */
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
#define LIN_17_ASCLIN_MASTER_TX_HEADER_AND_RESPONSE   (LIN_17_ASCLIN_MASTER_TRANSMIT_HEADER_ERROR |                                 \
LIN_17_ASCLIN_MASTER_TRANSMIT_RESPONSE)
#endif

#if (LIN_17_ASCLIN_MASTER_CH_PRESENT == STD_ON)
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
#define LIN_17_ASCLIN_MASTER_TRANSMIT_HEADER_SLAVE_RESPONSE (LIN_17_ASCLIN_MASTER_TRANSMIT_HEADER_ERROR |                                  \
LIN_17_ASCLIN_MASTER_RECEIVE_RESPONSE)

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
/*FE | RT | CE | LC | BD | RFO | RFU */
#define LIN_17_ASCLIN_MASTER_RECEIVE_RESPONSE_ERROR   (0x0F340000U)
#define LIN_17_ASCLIN_RT_BIT ((uint32)0x1 << IFX_ASCLIN_FLAGS_RT_OFF)
#define LIN_17_ASCLIN_CE_BIT ((uint32)0x1 << IFX_ASCLIN_FLAGS_CE_OFF)
#endif

#define LIN_17_ASCLIN_CLEAR_ALL_EVENTS (0xDFFFE06FU)

/* Map and use internal MACRO's, type names are different for 4.2.2 and 4.4.0
versions of AUTOSAR */
#if (MCAL_AR_VERSION == MCAL_AR_440)
/* Internal MACRO for Master node */
#if (LIN_17_ASCLIN_MASTER_CH_PRESENT == STD_ON)
#define LIN_17_ASCLIN_MSR_MASTER_RESPONSE_I   LIN_FRAMERESPONSE_TX
#define LIN_17_ASCLIN_MSR_SLAVE_RESPONSE_I    LIN_FRAMERESPONSE_RX
#endif
#if (LIN_17_ASCLIN_SLAVE_CH_PRESENT == STD_ON)
/* Internal MACRO for Slave node */
#define LIN_17_ASCLIN_SLV_MASTER_RESPONSE_I   LIN_FRAMERESPONSE_RX
#define LIN_17_ASCLIN_SLV_SLAVE_RESPONSE_I    LIN_FRAMERESPONSE_TX
#endif
#else
#define LIN_17_ASCLIN_MSR_MASTER_RESPONSE_I   LIN_MASTER_RESPONSE
#define LIN_17_ASCLIN_MSR_SLAVE_RESPONSE_I    LIN_SLAVE_RESPONSE
#endif

/*******************************************************************************
**                   Function like macro definitions                          **
*******************************************************************************/

/*******************************************************************************
**                         User Mode Macros                                   **
*******************************************************************************/
/* [cover parentID={1A65EADD-AFD0-4845-B2D2-8257E086DD67}]
    [/cover] */
/* [cover parentID={9A645A5C-2204-4b30-9B01-842C8E69CB7D}]
    [/cover] */
#if(LIN_17_ASCLIN_INIT_API_MODE == LIN_17_ASCLIN_MCAL_SUPERVISOR_MODE)
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for User
   mode support in code. No side effects foreseen by violating this MISRA
   rule. */
#define LIN_17_ASCLIN_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(RegAdd,Data)   \
    Mcal_WritePeripEndInitProtReg(RegAdd,Data)
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for
   User mode support in code. No side effects foreseen by violating this MISRA
   rule. */
#define LIN_17_ASCLIN_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(RegAdd,Data)   \
    MCAL_LIB_WRITEPERIPENDINITPROTREG(RegAdd,Data)
#endif

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*This Type is used to internal state of LIN driver.*/
/* [cover parentID={181C36B0-2030-4b33-9351-815EF2FB202A}]
    [/cover] */
typedef enum
{
  LIN_17_ASCLIN_MASTER_CH_UNINIT_STATE_I = 0U,
  LIN_17_ASCLIN_MASTER_CH_INIT_STATE_I,
  LIN_17_ASCLIN_MASTER_SEND_HDR_RESP_STATE_I,
  LIN_17_ASCLIN_MASTER_RESP_RECEIVE_WAIT_STATE_I,
  LIN_17_ASCLIN_MASTER_IGNORE_RESPONSE_STATE_I,
  LIN_17_ASCLIN_MASTER_TX_COMPLETE_STATE_I,
  LIN_17_ASCLIN_MASTER_RX_COMPLETE_STATE_I,
  LIN_17_ASCLIN_SLEEP_STATE_I,               /* State common for master and slave */
  LIN_17_ASCLIN_MASTER_SLEEP_PENDING_STATE_I,
  LIN_17_ASCLIN_MASTER_TX_HDR_ERROR_STATE_I,
  LIN_17_ASCLIN_MASTER_TX_ERROR_STATE_I,
  LIN_17_ASCLIN_MASTER_RX_ERROR_STATE_I,    /*a. Framing Error, CRC error, collision and Short
                                                 response */
  LIN_17_ASCLIN_MASTER_RX_NO_RESP_STATE_I,  /*a. When No response is received after header
                                                  transmission
                                              b. On response timeout - Returns LIN_RX_NO_RESPONSE */
  /* Slave node states */
  LIN_17_ASCLIN_SLAVE_HDR_WAIT_STATE_I,
  LIN_17_ASCLIN_SLAVE_TX_RESP_COMPLETE_WAIT_STATE_I,
  LIN_17_ASCLIN_SLAVE_RX_RESP_WAIT_STATE_I,
} Lin_17_AscLin_InternalStatusType;

/* This type is used store the core status */
/* [cover parentID={E9F52E51-AE2C-4074-832F-7AEB346BC13A}]
    [/cover] */
typedef enum
{
  LIN_17_ASCLIN_CORE_UNINITIALIZED = 0U,
  LIN_17_ASCLIN_CORE_INITIALIZED,
} Lin_17_AscLin_CoreInitStatusType;

/*
Lin_17_AscLin_ChannelInfoType: This structure is used for storing internal LIN
                     channel status and other information.
*/
/* [cover parentID={BF2D633E-B1C1-40b7-8F4F-0A0247A0830F}]
    [/cover] */
typedef struct
{
  Lin_17_AscLin_InternalStatusType   State;           /* Current internal state of LIN driver */
  uint8 ResponseBuffer[LIN_17_ASCLIN_RESP_BUF_SIZE];  /* buffer to store the data */
  uint8   Sleep;                                      /* Sleep requested/not requested */
} Lin_17_AscLin_ChannelInfoType;

/*
Lin_17_AscLin_CoreStatesType: This structure is used for storing channel related
                      information and Pdu information.
*/
/* [cover parentID={AD97595E-CE15-4e71-AAE7-22A05E59F81B}]
    [/cover] */

typedef struct
{
  Lin_17_AscLin_ChannelInfoType *ChannelStatus;      /* Internal channel status and other information */
  Lin_PduType *Lin_Pdu;                              /* The Pdu information of each channel */
  Lin_17_AscLin_CoreInitStatusType *CoreInitStatus;  /* Core status */
} Lin_17_AscLin_CoreStatesType;

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/


/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
    [/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}] memmap
    [/cover] */
/* [cover parentID={B7F970AB-64ED-40b5-9BE7-A64D9494F4AB}] memmap
    [/cover] */
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
#define LIN_17_ASCLIN_START_SEC_CONST_QM_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safeguard.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"

static Ifx_ASCLIN *const Lin_17_AscLin_kAscLinKernelRegAddr                  \
[LIN_17_ASCLIN_MAX_HW_UNIT] =                                                \
{ \
  /* This macro expands into a list of pointers, pointing to the register
   address in respective order of position depending on the device variant */
  LIN_17_ASCLIN_REGADDR
};

/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
    [/cover] */
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
#define LIN_17_ASCLIN_STOP_SEC_CONST_QM_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with Autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safeguard.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
    [/cover] */
#if (LIN_17_ASCLIN_MAX_CHANNELS_CORE0 > 0U)

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
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
    [/cover] */
#define LIN_17_ASCLIN_START_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safeguard.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"
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
/*
  This variable holds the status of the driver and includes: checksum,
  sleep status, data length, Pid response type, previous byte transmitted.
*/
static Lin_17_AscLin_ChannelInfoType \
ChannelStatus_Core0[LIN_17_ASCLIN_MAX_CHANNELS_CORE0];

/* The Pdu information of the channel */
static Lin_PduType Lin_Pdu_Core0[LIN_17_ASCLIN_MAX_CHANNELS_CORE0];

/* The init status of the core */
static Lin_17_AscLin_CoreInitStatusType CoreInitStatus_Core0;

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
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
    [/cover] */
#define LIN_17_ASCLIN_STOP_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safeguard.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define LIN_17_ASCLIN_START_SEC_CONST_QM_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"
/* Structure holding core 0 specific LIN states */
static const Lin_17_AscLin_CoreStatesType Lin_17_AscLin_kCore0State =
{
  /* Pointer to the variable to store the channel status */
  &ChannelStatus_Core0[0],

  /* Pointer to the Pdu info of the channel */
  &Lin_Pdu_Core0[0],

  /* Variable to store the core0 state */
  &CoreInitStatus_Core0
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define LIN_17_ASCLIN_STOP_SEC_CONST_QM_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"
#endif /* #if (LIN_17_ASCLIN_MAX_CHANNELS_CORE0 > 0U)*/

#if (MCAL_NO_OF_CORES > 1U)
#if (LIN_17_ASCLIN_MAX_CHANNELS_CORE1 > 0U)
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
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
    [/cover] */
#define LIN_17_ASCLIN_START_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safegaurd.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"
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
/*
  This variable holds the status of the driver and includes: checksum,
  sleep status, data length, Pid response type, previous byte transmitted.
*/
static Lin_17_AscLin_ChannelInfoType ChannelStatus_Core1                      \
[LIN_17_ASCLIN_MAX_CHANNELS_CORE1];

/* The Pdu information of the channel */
static Lin_PduType Lin_Pdu_Core1[LIN_17_ASCLIN_MAX_CHANNELS_CORE1];

/* The init status of the core */
static Lin_17_AscLin_CoreInitStatusType CoreInitStatus_Core1;

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
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
    [/cover] */
#define LIN_17_ASCLIN_STOP_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safeguard.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define LIN_17_ASCLIN_START_SEC_CONST_QM_CORE1_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"
/* Structure holding core 1 specific LIN states */
static const Lin_17_AscLin_CoreStatesType Lin_17_AscLin_kCore1State =
{
  /* Pointer to the variable to store the channel status */
  &ChannelStatus_Core1[0],
  /* Pointer to the Pdu info of the channel */
  &Lin_Pdu_Core1[0],
  /* Variable to store the core1 state */
  &CoreInitStatus_Core1
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define LIN_17_ASCLIN_STOP_SEC_CONST_QM_CORE1_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"
#endif /*(LIN_17_ASCLIN_MAX_CHANNELS_CORE1 > 0U) */
#endif /* #if (MCAL_NO_OF_CORES > 1U) */

#if (MCAL_NO_OF_CORES > 2U)
#if (LIN_17_ASCLIN_MAX_CHANNELS_CORE2 > 0U)
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
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
    [/cover] */
#define LIN_17_ASCLIN_START_SEC_VAR_CLEARED_QM_CORE2_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safeguard.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"
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
/*
  This variable holds the status of the driver and includes: checksum,
  sleep status, data length, Pid response type, previous byte transmitted.
*/
static Lin_17_AscLin_ChannelInfoType ChannelStatus_Core2                      \
[LIN_17_ASCLIN_MAX_CHANNELS_CORE2];

/* The Pdu information of the channel */
static Lin_PduType Lin_Pdu_Core2[LIN_17_ASCLIN_MAX_CHANNELS_CORE2];

/* The init status of the core */
static Lin_17_AscLin_CoreInitStatusType CoreInitStatus_Core2;

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
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
    [/cover] */
#define LIN_17_ASCLIN_STOP_SEC_VAR_CLEARED_QM_CORE2_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safeguard.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define LIN_17_ASCLIN_START_SEC_CONST_QM_CORE2_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"
/* Structure holding core 2 specific LIN states */
static const Lin_17_AscLin_CoreStatesType Lin_17_AscLin_kCore2State =
{
  /* Pointer to the variable to store the channel status */
  &ChannelStatus_Core2[0],
  /* Pointer to the Pdu info of the channel */
  &Lin_Pdu_Core2[0],
  /* Variable to store the core2 state */
  &CoreInitStatus_Core2
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define LIN_17_ASCLIN_STOP_SEC_CONST_QM_CORE2_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"
#endif /* (LIN_17_ASCLIN_MAX_CHANNELS_CORE2 > 0U) */
#endif /* (MCAL_NO_OF_CORES > 2U)  */

#if (MCAL_NO_OF_CORES > 3U)
#if (LIN_17_ASCLIN_MAX_CHANNELS_CORE3 > 0U)
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
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
    [/cover] */
#define LIN_17_ASCLIN_START_SEC_VAR_CLEARED_QM_CORE3_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safeguard.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"
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
/*
  This variable holds the status of the driver and includes: checksum,
  sleep status, data length, Pid response type, previous byte transmitted.
*/
static Lin_17_AscLin_ChannelInfoType ChannelStatus_Core3                      \
[LIN_17_ASCLIN_MAX_CHANNELS_CORE3];

/* The Pdu information of the channel */
static Lin_PduType Lin_Pdu_Core3[LIN_17_ASCLIN_MAX_CHANNELS_CORE3];

/* The init status of the core */
static Lin_17_AscLin_CoreInitStatusType CoreInitStatus_Core3;

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
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
    [/cover] */
#define LIN_17_ASCLIN_STOP_SEC_VAR_CLEARED_QM_CORE3_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safeguard.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define LIN_17_ASCLIN_START_SEC_CONST_QM_CORE3_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"

/* Structure holding core 3 specific LIN states */
static const Lin_17_AscLin_CoreStatesType Lin_17_AscLin_kCore3State =
{
  /* Pointer to the variable to store the channel status */
  &ChannelStatus_Core3[0],
  /* Pointer to the Pdu info of the channel */
  &Lin_Pdu_Core3[0],
  /* Variable to store the core3 state */
  &CoreInitStatus_Core3
};

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define LIN_17_ASCLIN_STOP_SEC_CONST_QM_CORE3_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"
#endif   /* (LIN_17_ASCLIN_MAX_CHANNELS_CORE3 > 0U) */
#endif   /*  (MCAL_NO_OF_CORES > 3U) */

#if (MCAL_NO_OF_CORES > 4U)
#if (LIN_17_ASCLIN_MAX_CHANNELS_CORE4 > 0U)
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
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
    [/cover] */
#define LIN_17_ASCLIN_START_SEC_VAR_CLEARED_QM_CORE4_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safeguard.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"
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
/*
  This variable holds the status of the driver and includes: checksum,
  sleep status, data length, Pid response type, previous byte transmitted.
*/
static Lin_17_AscLin_ChannelInfoType ChannelStatus_Core4                      \
[LIN_17_ASCLIN_MAX_CHANNELS_CORE4];

/* The Pdu information of the channel */
static Lin_PduType Lin_Pdu_Core4[LIN_17_ASCLIN_MAX_CHANNELS_CORE4];

/* The init status of the core */
static Lin_17_AscLin_CoreInitStatusType CoreInitStatus_Core4;

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
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
    [/cover] */
#define LIN_17_ASCLIN_STOP_SEC_VAR_CLEARED_QM_CORE4_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safeguard.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define LIN_17_ASCLIN_START_SEC_CONST_QM_CORE4_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"
/* Structure holding core 4 specific LIN states */
static const Lin_17_AscLin_CoreStatesType Lin_17_AscLin_kCore4State =
{
  /* Pointer to the variable to store the channel status */
  &ChannelStatus_Core4[0],
  /* Pointer to the Pdu info of the channel */
  &Lin_Pdu_Core4[0],
  /* Variable to store the core4 state */
  &CoreInitStatus_Core4
};

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define LIN_17_ASCLIN_STOP_SEC_CONST_QM_CORE4_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"
#endif   /* (LIN_17_ASCLIN_MAX_CHANNELS_CORE4 > 0U) */
#endif   /* #if (MCAL_NO_OF_CORES > 4U) */

#if (MCAL_NO_OF_CORES > 5U)
#if (LIN_17_ASCLIN_MAX_CHANNELS_CORE5 > 0U)
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
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
    [/cover] */
#define LIN_17_ASCLIN_START_SEC_VAR_CLEARED_QM_CORE5_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safeguard.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"
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
/*
  This variable holds the status of the driver and includes: checksum,
  sleep status, data length, Pid response type, previous byte transmitted.
*/
static Lin_17_AscLin_ChannelInfoType ChannelStatus_Core5                      \
[LIN_17_ASCLIN_MAX_CHANNELS_CORE5];

/* The Pdu information of the channel */
static Lin_PduType Lin_Pdu_Core5[LIN_17_ASCLIN_MAX_CHANNELS_CORE5];

/* The init status of the core */
static Lin_17_AscLin_CoreInitStatusType CoreInitStatus_Core5;

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
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
    [/cover] */
#define LIN_17_ASCLIN_STOP_SEC_VAR_CLEARED_QM_CORE5_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safeguard.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define LIN_17_ASCLIN_START_SEC_CONST_QM_CORE5_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"
/* Structure holding core 5 specific LIN states */
static const Lin_17_AscLin_CoreStatesType Lin_17_AscLin_kCore5State =
{
  /* Pointer to the variable to store the channel status */
  &ChannelStatus_Core5[0],
  /* Pointer to the Pdu info of the channel */
  &Lin_Pdu_Core5[0],
  /* Variable to store the core5 state */
  &CoreInitStatus_Core5
};

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define LIN_17_ASCLIN_STOP_SEC_CONST_QM_CORE5_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"
#endif   /* (LIN_17_ASCLIN_MAX_CHANNELS_CORE5 > 0U) */
#endif   /* #if (MCAL_NO_OF_CORES > 5U) */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define LIN_17_ASCLIN_START_SEC_CONST_QM_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safeguard. It complies to Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"
/* Variable to hold the pointers to variables holding core specific LIN
states */
static const Lin_17_AscLin_CoreStatesType *const Lin_17_AscLin_kCoreStatus    \
[MCAL_NO_OF_CORES] =
{
  #if (LIN_17_ASCLIN_MAX_CHANNELS_CORE0 > 0U)
  &Lin_17_AscLin_kCore0State
  #else
  NULL_PTR
  #endif

  #if (MCAL_NO_OF_CORES > 1U)
  #if (LIN_17_ASCLIN_MAX_CHANNELS_CORE1 > 0U)
  , &Lin_17_AscLin_kCore1State
  #else
  , NULL_PTR
  #endif
  #endif

  #if (MCAL_NO_OF_CORES > 2U)
  #if (LIN_17_ASCLIN_MAX_CHANNELS_CORE2 > 0U)
  , &Lin_17_AscLin_kCore2State
  #else
  , NULL_PTR
  #endif
  #endif

  #if (MCAL_NO_OF_CORES > 3U)
  #if (LIN_17_ASCLIN_MAX_CHANNELS_CORE3 > 0U)
  , &Lin_17_AscLin_kCore3State
  #else
  , NULL_PTR
  #endif
  #endif
  #if (MCAL_NO_OF_CORES > 4U)
  #if (LIN_17_ASCLIN_MAX_CHANNELS_CORE4 > 0U)
  , &Lin_17_AscLin_kCore4State
  #else
  , NULL_PTR
  #endif
  #endif
  #if (MCAL_NO_OF_CORES > 5U)
  #if (LIN_17_ASCLIN_MAX_CHANNELS_CORE5 > 0U)
  , &Lin_17_AscLin_kCore5State
  #else
  , NULL_PTR
  #endif
  #endif
};
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
    [/cover] */
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
#define LIN_17_ASCLIN_STOP_SEC_CONST_QM_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safeguard.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"

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
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
    [/cover] */
#define LIN_17_ASCLIN_START_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safeguard.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"

/*
Variable Holds the Configuration Pointer given in Lin_17_AscLin_Init and
Lin_ChannelInit
*/
static const Lin_17_AscLin_ConfigType *Lin_17_AscLin_kConfigPtr;

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
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
    [/cover] */
#define LIN_17_ASCLIN_STOP_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safeguard.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
    [/cover] */
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
    Callout Memory section not used in LIN driver
[/cover]*/
/*[cover parentID={9ABB6AE4-2142-4ac8-B499-48AE1C3A908C}]
Code Memory section executable by all cores
[/cover]*/
#define LIN_17_ASCLIN_START_SEC_CODE_QM_GLOBAL
/*mapping of code and data to specific memory sections via memory mapping file*/
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
   Lin_17_AscLin_Memmap.h header is included without safeguard.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"
#if ((MCAL_AR_VERSION == MCAL_AR_440)&&(LIN_17_ASCLIN_SLAVE_CH_PRESENT == STD_ON))
static void Lin_17_Asclin_lPrepareSlaveForHeaderRx
(
  Ifx_ASCLIN *const HwModulePtr,
  Lin_17_AscLin_ChannelInfoType *const ChannelStatePtr,
  const uint8 BreakBitValue
);
#endif /* (MCAL_AR_VERSION == MCAL_AR_440)*/
#if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)

/* function returns the DET check status for channel */
static Std_ReturnType Lin_17_AscLin_lGetDetStatus
(
  const uint8 Channel,
  const uint8 ApiId
);
/* function returns the Error status value in init API */
static Std_ReturnType Lin_17_AscLin_lInitDetCheck
(
  const Lin_17_AscLin_ConfigType *const Config,
  const uint8 CoreId
);

#endif /* (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)*/

#if ((MCAL_AR_VERSION == MCAL_AR_440) && (LIN_17_ASCLIN_SLAVE_CH_PRESENT == STD_ON))
static void Lin_17_AscLin_lReportSlaveError
(
  const uint32 HwErrorFlags,
  const uint8 Channel
);
#endif

/* function sends wakeup pulse with the time duration given by wakeup val */
static void Lin_17_AscLin_lHwSendWakeupPulse(const uint8 HwUnit);

/* function resets the kernel*/
static Std_ReturnType Lin_17_AscLin_lHwInitKernelReg(const uint8 HwUnit);

/* function initializes the ASCLIN Hw module */
static Std_ReturnType Lin_17_AscLin_lHwInit
(
  const Lin_17_AscLin_ConfigType *const Config,
  const uint8 HwUnit
);

/* function checks the status of change in Hardware bit */
static Std_ReturnType Lin_17_AscLin_lHwBitChangeCheck
(
  const Ifx_ASCLIN *HwModulePtr,
  const uint8 BitVal
);

#if (LIN_17_ASCLIN_MASTER_CH_PRESENT == STD_ON)
/* function to re-initialize the MODE of ASCLIN Hw module */
static Std_ReturnType Lin_17_AscLin_lModeReInit
(
  const Lin_17_AscLin_ChannelInfoType *const ChannelStatePtr,
  const uint8 HwUnit
);

/* function configures the ASCLIN hardware for Frame transmission */
static void Lin_17_AscLin_lHwStartTransmission
(
  const uint8 HwUnit,
  const uint8 Channel,
  const Lin_PduType *PduStatePtr
);

static Lin_StatusType Lin_17_AscLin_lRetState
(
  const Lin_17_AscLin_InternalStatusType  CurrentState,
  Lin_17_AscLin_ChannelInfoType *const ChannelStatePtr,
  const uint8 FifoValue
);

static Lin_17_AscLin_InternalStatusType Lin_17_AscLin_lGetIntErrorStatus_Master
(
  const uint32 HwErrorFlags,
  const uint8 Channel
);

static void Lin_17_AscLin_lHandleRx_Master
(
  const uint8 CoreId, const uint8 HwUnit, const uint8 Channel
);

static void Lin_17_AscLin_lHandleTx_Master
(
  const uint8 CoreId, const uint8 HwUnit, const uint8 Channel
);
#endif

#if ((MCAL_AR_VERSION == MCAL_AR_440)&& (LIN_17_ASCLIN_SLAVE_CH_PRESENT == STD_ON))
static void Lin_17_AscLin_lHandleRx_Slave
(
  const uint8 CoreId, const uint8 HwUnit, const uint8 Channel
);

static void Lin_17_AscLin_lHandleTx_Slave
(
  const uint8 CoreId, const uint8 HwUnit, const uint8 Channel
);
#endif

static void Lin_17_AscLin_lHandleErr
(
  const uint8  HwUnit
);

#if (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_OFF)
static void Lin_17_AscLin_lPolling
(
  const uint8  HwUnit,
  Lin_17_AscLin_ChannelInfoType *const ChannelStatePtr,
  const Ifx_ASCLIN *HwModulePtr
);
#endif

#if(LIN_17_ASCLIN_HW_ERROR_DEM_REPORT == LIN_17_ASCLIN_DEM_REPORT_ENABLED)
/* Function to report the Production Error */
static void Lin_17_AscLin_lReportDemError
(
  const Dem_EventIdType EventId,
  const Dem_EventStatusType EventStatus
);
#endif /*(LIN_17_ASCLIN_HW_ERROR_DEM_REPORT == LIN_17_ASCLIN_DEM_REPORT_ENABLED)*/

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/

/*******************************************************************************
** Traceability :[cover parentID={001A7921-AA81-443e-B348-8A15E16AACE6}]      **
**                         [/cover]                                           **
** Syntax : void Lin_17_AscLin_Init                                           **
**                         ( const Lin_17_AscLin_ConfigType *const Config )   **
**                                                                            **
** Service ID:  0x00                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  Config - Pointer to LIN driver configuration set        **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This API initializes the LIN channels and clear              **
**               global variables to their reset state. The SFRs of the       **
**               configured kernels are first reset to default values and     **
**              then initialized as per the configuration. The Initialization **
**              function shall initialize all the Lin channels with the values**
**              of the structure referenced by the parameter Config.          **
** Note :      This API is applicable to both Master and Slave nodes          **
*******************************************************************************/
void Lin_17_AscLin_Init(const Lin_17_AscLin_ConfigType *const Config)
{
  uint8 Kernel;
  uint8 CoreId;
  uint8 LinChannel;
  Ifx_ASCLIN *HwModuleAddrPtr;
  const Lin_17_AscLin_ChannelType *ChanCfgPtr;
  Lin_17_AscLin_ChannelInfoType *ChannelStatePtr;
  Lin_PduType *PduStatePtr;

  Std_ReturnType ReturnStatus = E_NOT_OK;
  /* Get core id which is executing currently */
  CoreId = (uint8)Mcal_GetCpuIndex();

  /* [cover parentID={6F017557-502E-47dd-A718-9C006789C05D}]
    [/cover] */
  #if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={257022D9-9A4A-4c7e-A778-D2D510359BC2}]
    [/cover] */
  ReturnStatus = Lin_17_AscLin_lInitDetCheck(Config, CoreId);
  /* [cover parentID={EC9A3949-9156-489a-814B-2FBE505AC83C}]
  [/cover] */
  if (ReturnStatus == E_OK)

  #else

  ReturnStatus = E_OK;

  #endif
  {
    /* [cover parentID={1BA6DB00-3DF6-4cb6-8780-474C8B7FDB6B}]
        [/cover] */
    /* Enable the ASCLIN hardware unit/s for all the Lin channels */
    /* [cover parentID={37FD59F2-577F-4120-87CD-2542CB410358}]
        [/cover] */
    for (LinChannel = 0U; ((LinChannel <                     \
                            Config->CoreConfigPtr[CoreId]->MaxCoreChannels) && \
                           (ReturnStatus == E_OK)); LinChannel++)
    {

      /* [cover parentID={9CEA4605-62BC-4270-B083-49BDB85C203D}]
          [/cover] */
      ChanCfgPtr = &(Config->CoreConfigPtr[CoreId]->                           \
                     ChannelConfigPtr[LinChannel]);
      ChannelStatePtr = &(Lin_17_AscLin_kCoreStatus[CoreId]->                  \
                          ChannelStatus[LinChannel]);
      PduStatePtr = &(Lin_17_AscLin_kCoreStatus[CoreId]->                      \
                      Lin_Pdu[LinChannel]);

      /* Extract the hwmodule */
      Kernel = ChanCfgPtr->HwModule;
      HwModuleAddrPtr = Lin_17_AscLin_kAscLinKernelRegAddr[Kernel];

      LIN_17_ASCLIN_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG
      (
        &HwModuleAddrPtr->CLC.U, (uint32)LIN_17_ASCLIN_CLC
      );
      if(HwModuleAddrPtr->CLC.B.DISS == LIN_17_ASCLIN_DISABLE_FLAG)
      {
        /* Reset Kernel  */
        /* [cover parentID={30C0A911-7A5D-4f79-B871-58C7F8AF9813}]
        [/cover] */
        ReturnStatus = Lin_17_AscLin_lHwInitKernelReg(Kernel);

        if (ReturnStatus == E_OK)
        {
          /* Initialize the Lin Hardware. */
          /* [cover parentID={09504911-2C34-4d6e-80C4-47D58D7FA9C3}]
          [/cover] */
          ReturnStatus = Lin_17_AscLin_lHwInit(Config, Kernel);
          if(ReturnStatus == E_OK)
          {
            /* [cover parentID={E9945956-F203-4ac0-9070-6BA687D26269}]
            [/cover] */
            /* [cover parentID={D1D5A830-D9E3-4e36-B49E-D845B5E1AC7E}]
            [/cover] */
            PduStatePtr->SduPtr =  ChannelStatePtr->ResponseBuffer;

            /* Enable wakeup since the sleep is the initial state for AS4.4.0 */
            /* If Wake-up is not enabled, need to call wakeup /
            wakeupinternal API to receive LIN frames */
            #if (MCAL_AR_VERSION == MCAL_AR_440)
            ChannelStatePtr->Sleep = (uint8)LIN_17_ASCLIN_SLEEP_REQ;

            /* Init the channel State variable */
            ChannelStatePtr->State = LIN_17_ASCLIN_SLEEP_STATE_I;
            /* [cover parentID={C0DC70A2-D878-4190-8A84-F6C682C09E82}]
            [/cover] */
            #if (LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT == STD_ON)
            if (LIN_17_ASCLIN_CHANNEL_WAKEUP_ENABLED == (ChanCfgPtr->Wakeup))
            {
              /* Enable the FED flag and intr */
              HwModuleAddrPtr->FLAGSCLEAR.B.FEDC = LIN_17_CLEAR_EVENT_BIT;
              HwModuleAddrPtr->FLAGSENABLE.B.FEDE = LIN_17_ASCLIN_ENABLE_FLAG;
            }
            #endif
            #else
            /* Init the channel State variable */
            ChannelStatePtr->State = LIN_17_ASCLIN_MASTER_CH_INIT_STATE_I;
            #endif
          }
        }
      }
      else
      {
        ReturnStatus = E_NOT_OK;
      }
    }
    /* [cover parentID={E1404D5A-6489-4c8f-B566-CB79126EC0C2}]
            [/cover] */
    if(ReturnStatus == E_OK)
    {
      /* Store Config for use by APIs*/
      Lin_17_AscLin_kConfigPtr = Config;
      /* [cover parentID={E2B44D7F-F060-4f44-862B-37CBF63E4FFE}]
            [/cover] */
      #if(LIN_17_ASCLIN_HW_ERROR_DEM_REPORT == LIN_17_ASCLIN_DEM_REPORT_ENABLED)
      Lin_17_AscLin_lReportDemError(LIN_17_ASCLIN_E_TIMEOUT, DEM_EVENT_STATUS_PASSED );
      #endif

      /* Update if all channels are initialized successfully */
      *Lin_17_AscLin_kCoreStatus[CoreId]->CoreInitStatus = LIN_17_ASCLIN_CORE_INITIALIZED;
    }
    else
    {
      #if(LIN_17_ASCLIN_HW_ERROR_DEM_REPORT == LIN_17_ASCLIN_DEM_REPORT_ENABLED)
        /* [cover parentID={F8C82D03-DA4C-432c-A04F-E15E0893DE7C}]
            [/cover] */
        Lin_17_AscLin_lReportDemError(LIN_17_ASCLIN_E_TIMEOUT, DEM_EVENT_STATUS_FAILED );
      #endif

      /* If one of the channels fail to initialize, core is not successful in Initialization */
      *Lin_17_AscLin_kCoreStatus[CoreId]->CoreInitStatus = LIN_17_ASCLIN_CORE_UNINITIALIZED;
    }
  }
  /* [cover parentID={91C2A319-DD67-4311-AA01-10998C554B7B}]
     [/cover] */
  return;
}

/*******************************************************************************
** Traceability :[cover parentID={5CA76F2E-2A38-4214-B7B9-1B9D511C32ED}]      **
**                        [/cover]                                            **
**                                                                            **
** Syntax : Std_ReturnType Lin_17_AscLin_CheckWakeup(const uint8 Channel)     **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x0A                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in): Channel - LIN channel to be addressed .                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK - send command has been accepted.                   **
**                   E_NOT_OK - send command has not been accepted,           **
**                              development or production error occurred.     **
** Description : Service to identify the Lin channel after a wake up is       **
** caused by LIN bus transceiver                                              **
** Note :      This API is applicable to both Master and Slave nodes          **
*******************************************************************************/
Std_ReturnType Lin_17_AscLin_CheckWakeup(const uint8 Channel)
{
  /* [cover parentID={BFDDB452-CD5E-4af0-ABCC-54E17031F897}]
     [/cover] */
  Std_ReturnType ReturnStatus = E_NOT_OK;
  #if (LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT == STD_ON)
  uint8 HwUnit;
  uint8 CoreId;
  uint8 ChannelId;
  const Ifx_ASCLIN *HwModuleAddrPtr;
  const Lin_17_AscLin_ChannelType *ChanCfgPtr;
  uint32 EcumStatus;
  uint32 WakeupEvent;
  #endif

  /* [cover parentID={00E1CCD0-9284-4a0d-8A10-BD6A7C9760BC}]
    [/cover] */
  #if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={57F66744-06F6-423a-A3F2-637545ECF6E8}]
    [/cover] */
  ReturnStatus = Lin_17_AscLin_lGetDetStatus
                 (
                   Channel, LIN_17_ASCLIN_SID_CHECKWAKEUP
                 );
  /* [cover parentID={4FF9DC02-8E00-488f-9DBF-B3D7A9CE6624}]
      [/cover] */
  if (ReturnStatus == E_OK)
  #endif  /* (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* [cover parentID={79186992-6E66-4a03-AFFA-CFD07ACABC61}]
       [/cover] */
    #if (LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT == STD_ON)
    /* Get core id which is executing currently */
    CoreId = (uint8)Mcal_GetCpuIndex();
    /*Extracting the physical channel ID*/
    ChannelId = Lin_17_AscLin_kConfigPtr->ChannelToCorePtr[Channel];
    ChanCfgPtr = &(Lin_17_AscLin_kConfigPtr->CoreConfigPtr[CoreId]->          \
                   ChannelConfigPtr[ChannelId]);
    /* Extract the hwmodule */
    HwUnit = ChanCfgPtr->HwModule;
    HwModuleAddrPtr = Lin_17_AscLin_kAscLinKernelRegAddr[HwUnit];

    /* If RxD line = 0, provide notification */
    if (HwModuleAddrPtr->IOCR.B.RXM == STD_LOW)
    {
      if (LIN_17_ASCLIN_CHANNEL_WAKEUP_ENABLED == (ChanCfgPtr->Wakeup))
      {
        EcumStatus = ChanCfgPtr->WakeupSourceId;

        /* Set the wakeup event in ECUM regardless of
          LinChannelWakeupSupport*/
        WakeupEvent = (uint32)LIN_17_ASCLIN_ENABLE_FLAG << EcumStatus;
        /* [cover parentID={397EEB66-6F86-4a46-B5E5-F5C596C6164C}]
           [/cover] */
        EcuM_SetWakeupEvent(WakeupEvent);

        /* Successful wakeup detection reported */
        /* [cover parentID={46F61585-74B5-4bf5-A12A-361E30796477}]
          [/cover] */
        LinIf_WakeupConfirmation(WakeupEvent);
        ReturnStatus = E_OK;
      }
    }/*(Lin_lHwGetRxDStatus(HwUnit) == STD_LOW)*/
    else
    {
      ReturnStatus = E_NOT_OK;
    }
    #else
    UNUSED_PARAMETER(Channel);
    ReturnStatus = E_NOT_OK;
    #endif
  }
  /* [cover parentID={6A567E77-816D-40ac-B8C5-DFBE1EEDA82E}]
     [/cover] */
  return ReturnStatus;
}
/* Compilation switch to allow call from master channel */
/* [cover parentID={B193939B-1551-4b4e-940D-5C341510200F}]
    [/cover] */
/* [cover parentID={7076D4F2-6F14-4511-95AD-DE9BF4EC07FC}]
     [/cover] */
#if (LIN_17_ASCLIN_MASTER_CH_PRESENT == STD_ON)
/*******************************************************************************
** Traceability :[cover parentID={D17A666A-6BBA-4c01-AFEA-2D32CEEB9E02}]      **
**                        [/cover]                                            **
** Syntax : Std_ReturnType Lin_17_AscLin_SendFrame                            **
**           (                                                                **
**             const uint8 Channel,                                           **
**             const Lin_PduType *const PduInfoPtr                            **
**           )                                                                **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x04                                                          **
**                                                                            **
** Sync/Async:  Asynchonous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in): Channel - LIN channel to be addressed .                   **
**                  PduInfoPtr - Pointer to PDU containing the PID, Checksum  **
**                  model, Response type, Dl and SDU data pointer             **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK - send command has been accepted.                   **
**                   E_NOT_OK - send command has not been accepted,           **
**                              development or production error occurred.     **
**                                                                            **
** Description : Service to send a Lin Frame (header and Response).           **
** Note :      This API is applicable to Master nodes only                    **
*******************************************************************************/
Std_ReturnType Lin_17_AscLin_SendFrame
(
  const uint8 Channel,
  const Lin_PduType *const PduInfoPtr
)
{
  uint8 Index;
  uint8 HwUnit;
  uint8 CoreId;
  uint8 ChannelId = 0;
  const uint8 *DataPtr;
  Ifx_ASCLIN *HwModulePtr;
  const Lin_17_AscLin_ChannelType *ChanCfgPtr;
  Lin_17_AscLin_ChannelInfoType *ChannelStatePtr;
  Lin_PduType *PduStatePtr;

  Std_ReturnType   RetVal = E_NOT_OK;
  /* [cover parentID={67F02934-4B13-4aa4-A781-E788AFADD578}]
    [/cover] */
  /* Get core id which is executing currently */
  CoreId = (uint8)Mcal_GetCpuIndex();

  /* [cover parentID={6DF86AA6-F42C-4ec0-AFA7-7DCF26707F91}]
    [/cover] */
  #if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)
  /* if the channel, UnInit parameters is invalid */
  /* [cover parentID={1075DF33-2FE3-4a1f-AD90-49CC6FA32731}]
    [/cover] */
  RetVal = Lin_17_AscLin_lGetDetStatus(Channel, LIN_17_ASCLIN_SID_SENDFRAME);
  if(E_OK == RetVal)
  {
    /*Extracting the physical channel ID*/
    ChannelId = Lin_17_AscLin_kConfigPtr->ChannelToCorePtr[Channel];
    /* if the node type of the channel is Slave */
    ChanCfgPtr = &(Lin_17_AscLin_kConfigPtr->CoreConfigPtr[CoreId]->          \
                   ChannelConfigPtr[ChannelId]);
    /* Extract the type of node */
    /* [cover parentID={48AE3A0A-1318-463b-890F-D1563CF3FB8A}]
      [/cover] */
    if(LIN_17_ASCLIN_MASTER_NODE != ChanCfgPtr->Node)
    {
      /* Report to  DET */
      /* [cover parentID={259B4F24-B3AF-41bd-AD59-E45AE502E2CC}]
         [/cover] */
      (void)Det_ReportError(
        LIN_17_ASCLIN_MODULE_ID,
        LIN_17_ASCLIN_INSTANCE_ID,
        LIN_17_ASCLIN_SID_SENDFRAME,
        LIN_17_ASCLIN_E_INVALID_CHANNEL
      );
      RetVal = E_NOT_OK;
    }
  }
  /* Check pointer validity */
  /* [cover parentID={AB597A35-D80C-48cb-9726-EE6B952C3C28}]
    [/cover] */
  if ((E_OK == RetVal) && (PduInfoPtr == NULL_PTR))
  {
    /* Report to  DET */
    /* [cover parentID={5C040CCD-F57E-4353-89DA-7A33908EFCAB}]
        [/cover] */
    (void)Det_ReportError(
      LIN_17_ASCLIN_MODULE_ID,
      LIN_17_ASCLIN_INSTANCE_ID,
      LIN_17_ASCLIN_SID_SENDFRAME,
      LIN_17_ASCLIN_E_PARAM_POINTER
    );

    RetVal = E_NOT_OK;
  }
  /* Check pointer validity */
  /* [cover parentID={AD814BD1-E396-4fb4-A88A-1AA49F220EB9}]
    [/cover] */
  if ((RetVal == E_OK) && (PduInfoPtr->SduPtr == NULL_PTR))
  {
    /* Report to  DET */
    /* [cover parentID={8851D3AB-0233-46c9-B571-062BED64D3AA}]
        [/cover] */
    (void)Det_ReportError(
      LIN_17_ASCLIN_MODULE_ID,
      LIN_17_ASCLIN_INSTANCE_ID,
      LIN_17_ASCLIN_SID_SENDFRAME,
      LIN_17_ASCLIN_E_PARAM_POINTER
    );
    RetVal = E_NOT_OK;
  }

  /* Check for the channel state machine in Sleep state */
  /* [cover parentID={6520F4C2-5EFA-4577-944C-083C3618C1BA}]
      [/cover] */
  /* [cover parentID={42D04DDA-B329-4bc7-9BD7-E78AEF772CF4}]
      [/cover] */
  if (RetVal == E_OK)
  {
    /*Extracting the physical channel ID*/
    ChannelId = Lin_17_AscLin_kConfigPtr->ChannelToCorePtr[Channel];
    ChannelStatePtr = &(Lin_17_AscLin_kCoreStatus[CoreId]->                     \
                        ChannelStatus[ChannelId]);
    if((ChannelStatePtr->State == LIN_17_ASCLIN_SLEEP_STATE_I) ||               \
        (ChannelStatePtr->State == LIN_17_ASCLIN_MASTER_SLEEP_PENDING_STATE_I))
    {
      /* Report to  DET */
      /* [cover parentID={A75AB9EE-0350-4da6-923C-2C94DB522447}]
         [/cover] */
      (void)Det_ReportError(
        LIN_17_ASCLIN_MODULE_ID,
        LIN_17_ASCLIN_INSTANCE_ID,
        LIN_17_ASCLIN_SID_SENDFRAME,
        LIN_17_ASCLIN_E_STATE_TRANSITION
      );

      RetVal = E_NOT_OK;
    }
  }

  if (RetVal == E_OK)
  #else
  /*Extracting the physical channel ID*/
  ChannelId = Lin_17_AscLin_kConfigPtr->ChannelToCorePtr[Channel];

  #endif  /* (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON) */
  {

    ChanCfgPtr = &(Lin_17_AscLin_kConfigPtr->CoreConfigPtr[CoreId]->           \
                   ChannelConfigPtr[ChannelId]);
    PduStatePtr = &(Lin_17_AscLin_kCoreStatus[CoreId]->                        \
                    Lin_Pdu[ChannelId]);
    ChannelStatePtr = &(Lin_17_AscLin_kCoreStatus[CoreId]->                    \
                        ChannelStatus[ChannelId]);

    /* Extract the Hw module */
    HwUnit = ChanCfgPtr->HwModule;

    HwModulePtr = Lin_17_AscLin_kAscLinKernelRegAddr[HwUnit];
    /* [cover parentID={536C9264-CCAD-4657-8B70-B1368CFD68E9}]
       [/cover] */
    /* Disable the Tx outlet b'fore the data entry */
    HwModulePtr->TXFIFOCON.B.ENO = LIN_17_ASCLIN_DISABLE_FLAG;
    /* Disable the RX inlet */
    HwModulePtr->RXFIFOCON.B.ENI = LIN_17_ASCLIN_DISABLE_FLAG;
    /* Receive Buffer Mode = RXFIFO */
    HwModulePtr->RXFIFOCON.B.BUF = LIN_17_ASCLIN_DISABLE_FLAG;
    /* Flush the Rx fifo */
    HwModulePtr->RXFIFOCON.B.FLUSH = LIN_17_ASCLIN_ENABLE_FLAG;

    /* Flush the Tx fifo */
    HwModulePtr->TXFIFOCON.B.FLUSH = LIN_17_ASCLIN_ENABLE_FLAG;

    /* Clear all the Flags. */
    HwModulePtr->FLAGSCLEAR.U = LIN_17_ASCLIN_FLAGSCLEAR_VAL;

    /* Check if there is no response or any Tx or Rx error is reported,
    * re-initialize the mode */
    RetVal = Lin_17_AscLin_lModeReInit(ChannelStatePtr, HwUnit);

    /* [cover parentID={7E92A8E9-2033-4505-AEFC-6759CD73BE58}]
     [/cover] */
    if (RetVal == E_OK)
    {
        /* [cover parentID={DF65621C-531E-42a2-91A3-672B39BF235C}]
             [/cover] */
        /* Copy PDU parmaeters in Lin_Channel_Info */
        PduStatePtr->Dl = PduInfoPtr->Dl;

        if(PduInfoPtr->Cs == LIN_ENHANCED_CS)
        {
          PduStatePtr->Cs = LIN_CLASSIC_CS;  /* The arrangement of checksum mode
                                               in DATCON.CSM is opposite of the
                                               enum definition */
        }
        else
        {
          PduStatePtr->Cs = LIN_ENHANCED_CS;
        }

        PduStatePtr->Pid = PduInfoPtr->Pid;
        PduStatePtr->Drc = PduInfoPtr->Drc;

        /* [cover parentID={3E7D9C9E-F2DC-44cf-8CB5-1D14D2CA2311}]
        [/cover] */
        /* Write Data bytes to local buffer in case of Master to Slave */
        if (PduStatePtr->Drc == LIN_17_ASCLIN_MSR_MASTER_RESPONSE_I)
        {
          Index = 0U;
          DataPtr = PduInfoPtr->SduPtr;
          do
          {
            /* [cover parentID={97E637A4-C513-4f50-82C8-C8D09577ECFE}]
              [/cover] */
            ChannelStatePtr->ResponseBuffer[Index] = *DataPtr;
            DataPtr++;
            Index++;
          } while (Index < PduStatePtr->Dl);
        }

        /* Start the Frame Transmission */
        Lin_17_AscLin_lHwStartTransmission(HwUnit, ChannelId, PduStatePtr);
        /* [cover parentID={5B283465-26F1-4006-A69A-01550A957BD5}]
        [/cover] */
        RetVal = E_OK;
    }
  }
  return RetVal;
}

/*******************************************************************************
** Traceability :[cover parentID={3172570B-BEE6-4305-92F9-9C6DA91D70EA}]      **
**                           [/cover]                                         **
** Syntax : Std_ReturnType Lin_17_AscLin_GoToSleep( const uint8 Channel )     **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x06                                                          **
**                                                                            **
** Sync/Async:  Asynchonous                                                   **
**                                                                            **
** Reentrancy:  Non Reentrant                                                 **
**                                                                            **
** Parameters (in) : Channel - LIN channel to be addressed                    **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: Sleep command has been accepted                    **
**                   E_NOT_OK: Sleep command has not been accepted,           **
**                   development or production error occurred                 **
**                                                                            **
** Description :    The service instructs the driver to transmit a            **
**               go-to-sleep-command on the addressed LIN channel             **
** Note :      This API is applicable to Master nodes only                    **
*******************************************************************************/
Std_ReturnType Lin_17_AscLin_GoToSleep(const uint8 Channel)
{
  uint8 Index;
  uint8 HwUnit;
  uint8 CoreId;
  uint8 ChannelId;
  Ifx_ASCLIN *HwModulePtr;
  Std_ReturnType  RetVal = E_NOT_OK;
  Lin_17_AscLin_ChannelInfoType *ChannelStatePtr;
  const Lin_17_AscLin_ChannelType *ChanCfgPtr;
  Lin_PduType *PduStatePtr;
  const Lin_17_AscLin_CoreConfigType *LinCorePtr;

  /* Get core id which is executing currently */
  CoreId = (uint8)Mcal_GetCpuIndex();
  /* [cover parentID={C94B8C44-E89D-45b9-AB98-7253C44EAFAC}]
       [/cover] */
  #if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)
  /* if the channel, UnInit parameters is invalid */
  /* [cover parentID={2D44F4D5-F7DA-4379-94A9-96744017041A}]
       [/cover] */
  RetVal = Lin_17_AscLin_lGetDetStatus(Channel, LIN_17_ASCLIN_SID_GOTOSLEEP);

  if (RetVal == E_OK)
  {
    /*Extracting the physical channel ID*/
    ChannelId = Lin_17_AscLin_kConfigPtr->ChannelToCorePtr[Channel];
    /* if the node type of the channel is Slave */
    ChanCfgPtr = &(Lin_17_AscLin_kConfigPtr->CoreConfigPtr[CoreId]->           \
                   ChannelConfigPtr[ChannelId]);
    /* [cover parentID={53576D11-1B62-4ee7-9977-6982E1413D15}]
       [/cover] */
    if(LIN_17_ASCLIN_MASTER_NODE != ChanCfgPtr->Node)
    {
      /* Report to  DET */
      /* [cover parentID={05362E18-DCB6-4d74-BF17-733D3CC8C61C}]
       [/cover] */
      (void)Det_ReportError(
        LIN_17_ASCLIN_MODULE_ID,
        LIN_17_ASCLIN_INSTANCE_ID,
        LIN_17_ASCLIN_SID_GOTOSLEEP,
        LIN_17_ASCLIN_E_INVALID_CHANNEL
      );
      RetVal = E_NOT_OK;
    }
    ChannelStatePtr = &(Lin_17_AscLin_kCoreStatus[CoreId]->                    \
                        ChannelStatus[ChannelId]);
    /* [cover parentID={4138A629-7FA1-492d-ACE1-DFD3761505A8}]
       [/cover] */
    if ((RetVal == E_OK) && (ChannelStatePtr->State == LIN_17_ASCLIN_SLEEP_STATE_I))
    {
      (void)Det_ReportError(
        LIN_17_ASCLIN_MODULE_ID,
        LIN_17_ASCLIN_INSTANCE_ID,
        LIN_17_ASCLIN_SID_GOTOSLEEP,
        LIN_17_ASCLIN_E_STATE_TRANSITION
      );
      RetVal = E_NOT_OK;
    }
  }
  if (RetVal == E_OK)
  #else
  /* [cover parentID={D6BF6D41-B133-4be8-9106-7DA5660D61FC}]
     [/cover] */


  #endif  /* (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON) */
  {
    LinCorePtr = Lin_17_AscLin_kConfigPtr->CoreConfigPtr[CoreId];
    /*Extracting the physical channel ID*/
    ChannelId = Lin_17_AscLin_kConfigPtr->ChannelToCorePtr[Channel];
    ChanCfgPtr = &(LinCorePtr->ChannelConfigPtr[ChannelId]);
    PduStatePtr = &(Lin_17_AscLin_kCoreStatus[CoreId]->                           \
                    Lin_Pdu[ChannelId]);
    /* Extract HwUnit */
    HwUnit = ChanCfgPtr->HwModule;

    HwModulePtr = (Lin_17_AscLin_kAscLinKernelRegAddr[HwUnit]);
    /* [cover parentID={C5C33D36-1E6C-4a07-9A96-409BF9BA4D91}]
       [/cover] */
    /* Disable the Tx outlet b'fore the data entry */
    HwModulePtr->TXFIFOCON.B.ENO = LIN_17_ASCLIN_DISABLE_FLAG;
    /* Disable the RX inlet */
    HwModulePtr->RXFIFOCON.B.ENI = LIN_17_ASCLIN_DISABLE_FLAG;
    /* Receive Buffer Mode = RXFIFO */
    HwModulePtr->RXFIFOCON.B.BUF = LIN_17_ASCLIN_DISABLE_FLAG;
    /* Flush the Rx fifo */
    HwModulePtr->RXFIFOCON.B.FLUSH = LIN_17_ASCLIN_ENABLE_FLAG;

    /* Flush the Tx fifo */
    HwModulePtr->TXFIFOCON.B.FLUSH = LIN_17_ASCLIN_ENABLE_FLAG;

    /* Clear all the Flags. */
    HwModulePtr->FLAGSCLEAR.U = LIN_17_ASCLIN_FLAGSCLEAR_VAL;

    /* Update Lin_Channel_Info with Sleep command */
    PduStatePtr->Dl = LIN_17_ASCLIN_SLEEPCMD_DL;
    /* MISRA2012_RULE_10_3_JUSTIFICATION: Assignment to narrower type
      enum is performed however assigned value is within range of
      Lin_FrameCsModelType */
    /* MISRA2012_RULE_10_5_JUSTIFICATION: Unsigned to enum typecast is
    performed to assign a unsigned value to Lin_FrameCsModelType and
    assigned value is within range of Lin_FrameCsModelType*/
    PduStatePtr->Cs = (Lin_FrameCsModelType)LIN_17_ASCLIN_CLASSIC_CHECKSUM;
    PduStatePtr->Pid = LIN_17_ASCLIN_SLEEPCMD_PID;
    PduStatePtr->Drc = LIN_17_ASCLIN_MSR_MASTER_RESPONSE_I;
    ChannelStatePtr = &(Lin_17_AscLin_kCoreStatus[CoreId]->                     \
                        ChannelStatus[ChannelId]);

    /* Sleep data */
    /* [cover parentID={CF442622-0972-4730-8131-760BAC9021B8}]
      Change state to sleep pending[/cover] */
    /* [cover parentID={3E7D9C9E-F2DC-44cf-8CB5-1D14D2CA2311}]
      Change state to sleep pending[/cover] */
    ChannelStatePtr->ResponseBuffer[0U] =   \
                                            LIN_17_ASCLIN_SLEEPCMD_DATA0;

    for(Index = 1U;                                                            \
        Index < LIN_17_ASCLIN_SLEEPCMD_DATLEN; Index++)
    {
      ChannelStatePtr->ResponseBuffer[Index] =                                 \
          LIN_17_ASCLIN_SLEEPCMD_DATA1TO7;
    }

    /* Update the state variables. */
    /* [cover parentID={0D306C59-2A49-4477-AEDF-49EAD5998DC6}]*/


    ChannelStatePtr->Sleep = (uint8)LIN_17_ASCLIN_SLEEP_REQ;

    /* Start the Sleep Frame Transmission.
    Since sleep frame transmission is internal to Driver,
    Configure to send both header and response at one shot.
    */
    Lin_17_AscLin_lHwStartTransmission(HwUnit, ChannelId, PduStatePtr);

    /* Change state to sleep pending[/cover] */
    /* [cover parentID={639B5194-5EFC-470e-8B95-7C6C0ECEDEB4}]
          [/cover] */
    ChannelStatePtr->State = LIN_17_ASCLIN_MASTER_SLEEP_PENDING_STATE_I;

    RetVal = E_OK;
  }
  return RetVal;
}
#endif
/*******************************************************************************
** Traceability :[cover parentID={7B6A6C05-68D3-45d0-A527-ADEB39AC2E85}]      **
**                        [/cover]                                            **
**                                                                            **
** Syntax :Std_ReturnType Lin_17_AscLin_GoToSleepInternal(const uint8 Channel)**
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x09                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Reentrant                                                 **
**                                                                            **
** Parameters (in) : Channel - LIN channel to be addressed .                  **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: Command has been accepted.                         **
**                   E_NOT_OK: Command has not been accepted, development     **
**                   or production error occurred                             **
**                                                                            **
** Description : Sets the channel state to LIN_CH_SLEEP                       **
** Note :      This API is applicable to both Master and Slave nodes          **
*******************************************************************************/
Std_ReturnType Lin_17_AscLin_GoToSleepInternal(const uint8 Channel)
{
  uint8 CoreId;
  uint8 HwUnit;
  uint8 ChannelId;
  Ifx_ASCLIN *HwModulePtr;
  Std_ReturnType  RetVal = E_NOT_OK;
  const Lin_17_AscLin_ChannelType *ChanCfgPtr;
  Lin_17_AscLin_ChannelInfoType *ChannelStatePtr;

  /* [cover parentID={5154DAA8-3580-4d5a-A639-EA8585BFE9D8}]
    [/cover] */
  #if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)

  /* if the channel, UnInit parameters is invalid */
  /* [cover parentID={2B7B6F9E-F2D6-4546-B4BE-9E9CE20901AC}]
    [/cover] */
  RetVal = Lin_17_AscLin_lGetDetStatus                                         \
           (                                                                   \
               Channel, LIN_17_ASCLIN_SID_GOTOSLEEPINTERNAL                    \
           );
  /* [cover parentID={D3D7BA5B-B25B-43f7-BC79-BDFB627F44EB}]
    [/cover] */
  if (RetVal == E_OK)
  #endif  /* (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get core id which is executing currently */
    CoreId = (uint8)Mcal_GetCpuIndex();
    /*Extracting the physical channel ID*/
    ChannelId = Lin_17_AscLin_kConfigPtr->ChannelToCorePtr[Channel];
    ChanCfgPtr = &(Lin_17_AscLin_kConfigPtr->CoreConfigPtr[CoreId]->           \
                   ChannelConfigPtr[ChannelId]);
    HwUnit = ChanCfgPtr->HwModule;
    HwModulePtr = Lin_17_AscLin_kAscLinKernelRegAddr[HwUnit];
    ChannelStatePtr = &(Lin_17_AscLin_kCoreStatus[CoreId]->                    \
                        ChannelStatus[ChannelId]);
    /* Disable the Tx outlet b'fore the data entry */
    HwModulePtr->TXFIFOCON.B.ENO = LIN_17_ASCLIN_DISABLE_FLAG;
    /* Disable the RX inlet */
    HwModulePtr->RXFIFOCON.B.ENI = LIN_17_ASCLIN_DISABLE_FLAG;
    /* Receive Buffer Mode = RXFIFO */
    HwModulePtr->RXFIFOCON.B.BUF = LIN_17_ASCLIN_DISABLE_FLAG;
    /* Flush the Rx fifo */
    HwModulePtr->RXFIFOCON.B.FLUSH = LIN_17_ASCLIN_ENABLE_FLAG;

    /* Flush the Tx fifo */
    HwModulePtr->TXFIFOCON.B.FLUSH = LIN_17_ASCLIN_ENABLE_FLAG;
    /* Disable FLAGSEN */
    HwModulePtr->FLAGSCLEAR.U = (uint32)
                                LIN_17_ASCLIN_FLAGSCLEAR_MASK ;

    HwModulePtr->FLAGSENABLE.U = (uint32)LIN_17_ASCLIN_DISABLE_FLAG;

    /* Change LIN Rx state to LIN_WAKEUP_WAIT */
    /* [cover parentID={50849575-C2FE-4e97-9999-FFEB44EB95BB}]
        [/cover] */
    /* [cover parentID={639B5194-5EFC-470e-8B95-7C6C0ECEDEB4}]
            [/cover] */
    ChannelStatePtr->State = LIN_17_ASCLIN_SLEEP_STATE_I;

    /* [cover parentID={0665FFA1-4EC2-4146-8F75-57EBED42760A}]
      [/cover] */
    #if (LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT == STD_ON)
    if (LIN_17_ASCLIN_CHANNEL_WAKEUP_ENABLED == (ChanCfgPtr->Wakeup))
    {

      HwModulePtr->FLAGSCLEAR.B.FEDC = LIN_17_CLEAR_EVENT_BIT;

      /* Enable the FED flag and intr */
      HwModulePtr->FLAGSENABLE.B.FEDE = LIN_17_ASCLIN_ENABLE_FLAG;
    }
    #endif

    ChannelStatePtr->Sleep = (uint8)LIN_17_ASCLIN_SLEEP_REQ;
    RetVal = E_OK;
  }
  /* [cover parentID={9223449D-38C7-4ada-A8E7-AAA338F87269}]
   [/cover] */
  return RetVal;
}

/*******************************************************************************
** Traceability :[cover parentID={E8ABDF1F-19B8-4250-A694-D5E8BB4643C0}]      **
**                        [/cover]                                            **
** Syntax : Std_ReturnType Lin_17_AscLin_Wakeup(const uint8 Channel )         **
** [/cover]                                                                   **
**                                                                            **
** Service ID:      7                                                         **
**                                                                            **
** Sync/Async:      Asynchronous                                              **
**                                                                            **
** Reentrancy:      non reentrant                                             **
**                                                                            **
** Parameters (in): Channel    : LIN channel to be addressed                  **
**                                                                            **
** Parameters (out):none                                                      **
**                                                                            **
** Return value:    E_OK     :Wake-up request has been accepted               **
**                  E_NOT_OK :Wake-up request has not been accepted,          **
**                            development or production error occurred        **
**                                                                            **
** Description :    The service function Lin_WakeUp generates a wakeup pulse  **
**                  on the addressed LIN channel                              **
**                                                                            **
**     Note :       The LIN channel shall be in the LIN_CH_SLEEP state when   **
**                  this service will be called.                              **
** Note :      This API is applicable to both Master and Slave nodes          **
*******************************************************************************/
Std_ReturnType Lin_17_AscLin_Wakeup(const uint8 Channel)
{
  uint8 CoreId;
  uint8 ChannelId = 0;
  Std_ReturnType  RetVal = E_NOT_OK;
  Lin_17_AscLin_ChannelInfoType *ChannelStatePtr = NULL_PTR;
  uint8 HwUnit;
  const Lin_17_AscLin_CoreConfigType *LinCorePtr;
  const Lin_17_AscLin_ChannelType *ChanCfgPtr;
  #if (((MCAL_AR_VERSION == MCAL_AR_440) &&                              \
  (LIN_17_ASCLIN_SLAVE_CH_PRESENT == STD_ON)) ||                          \
  (LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT == STD_ON))
  Ifx_ASCLIN *HwModulePtr;
  #endif
  /* Get core id which is executing currently */
  CoreId = (uint8)Mcal_GetCpuIndex();

  /* [cover parentID={6CC40F51-407D-4a62-BA35-CEE06AB02B2B}]
      [/cover] */
  #if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)
  /* if the channel, UnInit parameters is invalid */
  /* [cover parentID={98092161-60EF-447d-AF61-9490AEC86B93}]
      [/cover] */
  RetVal = Lin_17_AscLin_lGetDetStatus(Channel, LIN_17_ASCLIN_SID_WAKEUP);

  /* Check for the channel state machine in Sleep state */
  /* [cover parentID={6BF1BF46-F85D-4235-AE2F-8DB1893AD5C8}]
      [/cover] */
  if (RetVal == E_OK)
{
  /*Extracting the physical channel ID*/
  ChannelId = Lin_17_AscLin_kConfigPtr->ChannelToCorePtr[Channel];
    ChannelStatePtr = &(Lin_17_AscLin_kCoreStatus[CoreId]->                       \
                        ChannelStatus[ChannelId]);
    if (ChannelStatePtr->State != LIN_17_ASCLIN_SLEEP_STATE_I)
    {
      /* Report to  DET */
      /* [cover parentID={9F17B5BC-6BBF-46c1-B59B-4FFEC37BB7D8}]
        [/cover] */
      (void)Det_ReportError(
        LIN_17_ASCLIN_MODULE_ID,
        LIN_17_ASCLIN_INSTANCE_ID,
        LIN_17_ASCLIN_SID_WAKEUP,
        LIN_17_ASCLIN_E_STATE_TRANSITION
      );
      RetVal = E_NOT_OK;
    }
  }
  /* [cover parentID={5E7F6761-480F-4c05-8A0E-AA726068F311}]
     [/cover] */
  if (RetVal == E_OK)
  #else
  /*Extracting the physical channel ID*/
  ChannelId = Lin_17_AscLin_kConfigPtr->ChannelToCorePtr[Channel];
  ChannelStatePtr = &(Lin_17_AscLin_kCoreStatus[CoreId]->                       \
                      ChannelStatus[ChannelId]);
  if (ChannelStatePtr->State == LIN_17_ASCLIN_SLEEP_STATE_I)
  #endif
{
  LinCorePtr = Lin_17_AscLin_kConfigPtr->CoreConfigPtr[CoreId];
    ChanCfgPtr = &(LinCorePtr->ChannelConfigPtr[ChannelId]);
    /* Extract Hw Module */
    HwUnit = ChanCfgPtr->HwModule;
    #if (((MCAL_AR_VERSION == MCAL_AR_440)&&                                \
    (LIN_17_ASCLIN_SLAVE_CH_PRESENT == STD_ON)) ||                          \
    (LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT == STD_ON))
    HwModulePtr = Lin_17_AscLin_kAscLinKernelRegAddr[HwUnit];
    #endif

    #if ((MCAL_AR_VERSION == MCAL_AR_440)&& (LIN_17_ASCLIN_SLAVE_CH_PRESENT == STD_ON))
    /* Check if the node type is Slave */
    /* [cover parentID={F243CCB5-5379-4755-8C4D-2B525957860A}]
     [/cover] */
    if (LIN_17_ASCLIN_SLAVE_NODE == ChanCfgPtr-> Node)
  {
    /* Change State to header wait, Header receive + Error,
       Clear all interrupts, Flush FIFO */
    Lin_17_Asclin_lPrepareSlaveForHeaderRx(HwModulePtr, ChannelStatePtr,
                                           LIN_17_ASCLIN_BREAK_NOT_DETECTED);
    }
    else
    #endif
    {
      /* Change LIN state to LIN_17_ASCLIN_MASTER_CH_INIT_STATE_I */
      /* [cover parentID={639B5194-5EFC-470e-8B95-7C6C0ECEDEB4}]
            [/cover] */
      /* [cover parentID={D1D5A830-D9E3-4e36-B49E-D845B5E1AC7E}]
      [/cover] */

      ChannelStatePtr->State = LIN_17_ASCLIN_MASTER_CH_INIT_STATE_I;
    }

    ChannelStatePtr->Sleep = (uint8)LIN_17_ASCLIN_SLEEP_NOT_REQ;

    /* [cover parentID={56FE67D5-78CF-4454-8882-974C429CA6DB}]
      [/cover] */
    #if (LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT == STD_ON)
    if (LIN_17_ASCLIN_CHANNEL_WAKEUP_ENABLED == (ChanCfgPtr->Wakeup))
  {
    /* If this bit was SET an interrupt would have trigerred */
    /* Disable Falling edge intr */
    HwModulePtr->FLAGSENABLE.B.FEDE = LIN_17_ASCLIN_DISABLE_FLAG;
  }
    #endif
  /* [cover parentID={72656131-1591-4f08-8212-7B4A53A8238A}]
    [/cover] */
  RetVal = E_OK;

  /* [cover parentID={21E59C47-7D7B-4b70-9664-536266661B70}]
      [/cover] */
  Lin_17_AscLin_lHwSendWakeupPulse(HwUnit);
}
return RetVal;
}
/*******************************************************************************
** Traceability :[cover parentID={508EA393-BC0C-4a41-B45B-F1DA3E2CE186}]      **
**                           [/cover]                                         **
**                                                                            **
** Syntax : Std_ReturnType Lin_17_AscLin_WakeupInternal(const uint8 Channel ) **
** [/cover]                                                                   **
**                                                                            **
** Service ID:      0xB                                                       **
**                                                                            **
** Sync/Async:      Synchronous                                               **
**                                                                            **
** Reentrancy:      non reentrant                                             **
**                                                                            **
** Parameters (in): Channel    : LIN channel to be addressed                  **
**                                                                            **
** Parameters (out):none                                                      **
**                                                                            **
** Return value:    E_OK     :Wake-up request has been accepted               **
**                  E_NOT_OK :Wake-up request has not been accepted,          **
**                            development or production error occurred        **
**                                                                            **
** Description      : This service Sets the channel state to                  **
**                    LIN_CH_OPERATIONAL without generating a wake up pulse.  **
**                                                                            **
**    Note1 :       The LIN channel shall be in the LIN_CH_SLEEP state when   **
**                  this service will be called.                              **
** Note2 :     This API is applicable to both Master and Slave nodes          **
*******************************************************************************/
Std_ReturnType Lin_17_AscLin_WakeupInternal(const uint8 Channel)
{
  uint8 CoreId;
  uint8 ChannelId = 0;
  Std_ReturnType  RetVal = E_NOT_OK;
  Lin_17_AscLin_ChannelInfoType *ChannelStatePtr = NULL_PTR;
  #if (((MCAL_AR_VERSION == MCAL_AR_440) &&                                         \
  (LIN_17_ASCLIN_SLAVE_CH_PRESENT == STD_ON)) ||                                    \
  (LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT == STD_ON))
  const Lin_17_AscLin_CoreConfigType *LinCorePtr;
  const Lin_17_AscLin_ChannelType *ChanCfgPtr;
  uint8 HwUnit;
  Ifx_ASCLIN *HwModulePtr;
  #endif
  CoreId = (uint8)Mcal_GetCpuIndex();

  /* [cover parentID={F8E7A629-0FB8-4720-BB68-2F826450A548}]
      [/cover] */
  #if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)
  /* if the channel, UnInit parameters is invalid */
  /* [cover parentID={A29B579E-3A6B-40f0-BAC7-4E565FF05443}]
      [/cover] */
  RetVal = Lin_17_AscLin_lGetDetStatus
           (
             Channel, LIN_17_ASCLIN_SID_WAKEUPINTERNAL
           );

  /* Check for the channel state machine in Sleep state */
  /* [cover parentID={772504A5-6089-408d-8C12-1A741C937021}]
     [/cover] */
  if (RetVal == E_OK)
{
  /*Extracting the physical channel ID*/
  ChannelId = Lin_17_AscLin_kConfigPtr->ChannelToCorePtr[Channel];
    ChannelStatePtr = &(Lin_17_AscLin_kCoreStatus[CoreId]->                     \
                        ChannelStatus[ChannelId]);
    if(ChannelStatePtr->State != LIN_17_ASCLIN_SLEEP_STATE_I)
    {
      /* Report to  DET */
      /* [cover parentID={E4BC9FC5-C30A-4771-9D5F-17F89591E6C8}]
       [/cover] */
      (void)Det_ReportError(
        LIN_17_ASCLIN_MODULE_ID,
        LIN_17_ASCLIN_INSTANCE_ID,
        LIN_17_ASCLIN_SID_WAKEUPINTERNAL,
        LIN_17_ASCLIN_E_STATE_TRANSITION
      );
      RetVal = E_NOT_OK;
    }
  }
  /* [cover parentID={994823DF-74CC-4699-9DAF-F72C3B6B33B5}]
      [/cover] */
  if (RetVal == E_OK)
  #else

  /*Extracting the physical channel ID*/
  ChannelId = Lin_17_AscLin_kConfigPtr->ChannelToCorePtr[Channel];
  ChannelStatePtr = &(Lin_17_AscLin_kCoreStatus[CoreId]->                      \
                      ChannelStatus[ChannelId]);
  if (ChannelStatePtr->State == LIN_17_ASCLIN_SLEEP_STATE_I)
  #endif  /* (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON) */
{
  /* Change LIN state to LIN_17_ASCLIN_MASTER_CH_INIT_STATE_I */
  /* [cover parentID={0C877D48-6AD3-4707-AD2C-E5B0E10D4A57}]
      Change LIN state to operational [/cover] */
  /* [cover parentID={639B5194-5EFC-470e-8B95-7C6C0ECEDEB4}]
          [/cover] */
  #if (((MCAL_AR_VERSION == MCAL_AR_440)&&                                     \
  (LIN_17_ASCLIN_SLAVE_CH_PRESENT == STD_ON)) ||                               \
    (LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT == STD_ON))
    LinCorePtr = Lin_17_AscLin_kConfigPtr->CoreConfigPtr[CoreId];
    ChanCfgPtr = &(LinCorePtr->ChannelConfigPtr[ChannelId]);
    /* Extract Hw Module */
    HwUnit = ChanCfgPtr->HwModule;
    HwModulePtr = Lin_17_AscLin_kAscLinKernelRegAddr[HwUnit];
  #endif
    #if ((MCAL_AR_VERSION == MCAL_AR_440)&&(LIN_17_ASCLIN_SLAVE_CH_PRESENT == STD_ON))
    /* Check if the node type is Slave */
    /* [cover parentID={CA6FF9B8-FBE2-4aa1-BA1F-7CBF4276DB2D}]
     [/cover] */
    if (LIN_17_ASCLIN_SLAVE_NODE == ChanCfgPtr-> Node)
  {
    /* Change State to header wait, Header receive + errors,
    Clear all interrupts */
    Lin_17_Asclin_lPrepareSlaveForHeaderRx(HwModulePtr, ChannelStatePtr,
                                           LIN_17_ASCLIN_BREAK_NOT_DETECTED);
    }
    else
    #endif
    {
      ChannelStatePtr->State = LIN_17_ASCLIN_MASTER_CH_INIT_STATE_I;
    }

    ChannelStatePtr->Sleep = (uint8)LIN_17_ASCLIN_SLEEP_NOT_REQ;

    /* [cover parentID={115A3E84-25E3-4e05-95C8-E3200BF41E2D}]
     [/cover] */
    #if (LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT == STD_ON)
    if (LIN_17_ASCLIN_CHANNEL_WAKEUP_ENABLED == (ChanCfgPtr->Wakeup))
  {

    /* Disable Falling edge intr */
    HwModulePtr->FLAGSENABLE.B.FEDE = LIN_17_ASCLIN_DISABLE_FLAG;
  }
    #endif
  /* [cover parentID={D192D225-68FD-4680-AE60-86184488A5E7}]
   [/cover] */
  RetVal = E_OK;
}
return RetVal;
}
/* [cover parentID={EC29731C-ED85-47d2-88FE-A7577DA7B184}]
     [/cover] */
/* [cover parentID={869FC0CA-FB87-4a0c-813F-32E3E89A7CC5}]
      [/cover] */
#if (LIN_17_ASCLIN_MASTER_CH_PRESENT == STD_ON)
/*******************************************************************************
** Traceability :[cover parentID={022145B5-9509-49ed-B308-8A082B02D270}]      **
**                           [/cover]                                         **
** Syntax : Lin_StatusType Lin_17_AscLin_GetStatus                            **
                           (const uint8 Channel, uint8 **const LinSduPtr)     **
** [/cover]                                                                   **
**                                                                            **
** Service ID:      0x08                                                      **
**                                                                            **
** Sync/Async:      Synchronous                                               **
**                                                                            **
** Reentrancy:      non reentrant                                             **
**                                                                            **
** Parameters (in): Channel    : LIN channel to be addressed                  **
**                                                                            **
** Parameters (out):LinSduPtr : Reference to a shadow buffer or memory mapped **
**                               LIN Hardware receive buffer where the current**
**                               SDU is stored                                **
**                                                                            **
** Return value:    LIN_NOT_OK  : Development or Production error occurred    **
**                  LIN_TX_OK   : Successful transmission                     **
**                  LIN_TX_BUSY : Ongoing Transmission (Header or Response)   **
**                  LIN_TX_HEADER_ERROR :                                     **
**                      Erroneous header transmission such as:                **
**                         - Mismatch between sent and read back data         **
**                         - Identifier parity error or                       **
**                         - Physical bus error                               **
**                  LIN_TX_ERROR: Erroneous transmission                      **
**                         - Mismatch between sent and read back data         **
**                         - Physical bus error                               **
**                  LIN_RX_OK   : Reception of correct response               **
**                  LIN_RX_BUSY : Ongoing reception: at least one response    **
**                                byte has been received, but the checksum    **
**                                byte has not been received                  **
**                  LIN_RX_ERROR: Erroneous reception                         **
**                                - Framing error                             **
**                                - Data error                                **
**                                - Checksum error or Short response          **
**                  LIN_RX_NO_RESPONSE : No reception                         **
**                  LIN_CH_OPERATIONAL : Normal operation; the related LIN    **
**                                    channel is ready to transmit next header**
**                                    No data from previous frame available   **
**                                   (e.g. after initialization)              **
**                  LIN_CH_SLEEP : Sleep mode operation; in this mode wake-up **
**                                 detection from slave nodes is enabled      **
**                                                                            **
** Description :    Indicates the current transmission, reception or          **
**                  operation status of the LIN driver                        **
**                                                                            **
**                  If a SDU has been successfully received, the SDU          **
**                  will be stored in a shadow buffer or memory mapped LIN    **
**                  Hardware receive buffer referenced by Lin_SduPtr.         **
**                  The buffer will only be valid and must be read until the  **
**                  next Lin_17_AscLin_SendFrame function call.               **
**                  The LIN driver shall provide a function to                **
**                  interrogate the status of the current frame transmission  **
**                  request ((Lin_17_AscLin_GetStatus)                        **
**                  The LIN driver shall provide a service for                **
**                  checking the current state of each LIN channel under its  **
**                  control (( Lin_17_AscLin_GetStatus)                       **
**                  LIN operation states for a LIN channel or frame,          **
**                  as returned by the API service Lin_17_AscLin_GetStatus()  **
** Note :      This API is applicable to Master nodes only                    **
*******************************************************************************/
Lin_StatusType Lin_17_AscLin_GetStatus
(
  const uint8 Channel,
  uint8 ** const LinSduPtr
)
{
  Lin_StatusType  Status = LIN_OPERATIONAL;
  Lin_17_AscLin_InternalStatusType CurrentState;
  uint8 CoreId;
  uint8 ChannelId = 0;
  uint8 FifoValue;
  Lin_17_AscLin_ChannelInfoType *ChannelStatePtr = NULL_PTR;

  const Lin_17_AscLin_ChannelType *ChanCfgPtr;
  const Lin_17_AscLin_CoreConfigType *LinCorePtr;
  uint8 HwUnit;
  const Ifx_ASCLIN *HwModulePtr;
  #if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType   DetStatus;
  #endif

  /* Get core id which is executing currently */
  CoreId = (uint8)Mcal_GetCpuIndex();
  /* Check for the channel state machine in Sleep state */
  /* [cover parentID={BAB7E1C2-FF99-40f3-A409-88DA62FCA1A9}]
      [/cover] */
  #if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)
  /* if the channel, UnInit parameters is invalid */
  /* [cover parentID={4D966324-7633-401c-8063-AB278B7EE84F}]
      [/cover] */
  DetStatus = Lin_17_AscLin_lGetDetStatus(Channel,                             \
                                          LIN_17_ASCLIN_SID_GETSTATUS);
  if(E_OK == DetStatus)
  {
    /*Extracting the physical channel ID*/
    ChannelId = Lin_17_AscLin_kConfigPtr->ChannelToCorePtr[Channel];
    /* if the node type of the channel is Slave */
    ChanCfgPtr = &(Lin_17_AscLin_kConfigPtr->CoreConfigPtr[CoreId]->             \
                   ChannelConfigPtr[ChannelId]);
    /* [cover parentID={1FEB6101-551D-4769-B005-7C29FCEA4AEE}]
        [/cover] */
    if(LIN_17_ASCLIN_MASTER_NODE != ChanCfgPtr->Node)
    {
      /* Report to  DET */
      /* [cover parentID={FD2115AF-AE20-4133-8C65-5AF342EF66DE}]
         [/cover] */
      (void)Det_ReportError(
        LIN_17_ASCLIN_MODULE_ID,
        LIN_17_ASCLIN_INSTANCE_ID,
        LIN_17_ASCLIN_SID_GETSTATUS,
        LIN_17_ASCLIN_E_INVALID_CHANNEL
      );
      DetStatus = E_NOT_OK;
    }
  }
  /* Check for the channel state machine in Sleep state */
  /* [cover parentID={872EE24C-1E2B-4be9-AEB1-686180DA4B42}]
      [/cover] */
  if (E_OK == DetStatus)
  {

    if (LinSduPtr == NULL_PTR)
    {
      /* Report to  DET */
      /* [cover parentID={630FF490-78A7-40b4-BD20-9D354A13A1BF}]
        [/cover] */
      (void)Det_ReportError(
        LIN_17_ASCLIN_MODULE_ID,
        LIN_17_ASCLIN_INSTANCE_ID,
        LIN_17_ASCLIN_SID_GETSTATUS,
        LIN_17_ASCLIN_E_PARAM_POINTER
      );
      Status = LIN_NOT_OK;
    }
  }
  else
  {
    Status = LIN_NOT_OK;
  }
  /* [cover parentID={B737ADF0-531D-405a-B478-0FC43C4B8D1F}]
     [/cover] */
  /* [cover parentID={41E8F65B-B5D8-46a9-8FE5-7D8495062BF0}]
     [/cover] */
  if (Status != LIN_NOT_OK)
  #endif  /* (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON) */
  {
    /*Extracting the physical channel ID*/
    ChannelId = Lin_17_AscLin_kConfigPtr->ChannelToCorePtr[Channel];
    ChannelStatePtr = &(Lin_17_AscLin_kCoreStatus[CoreId]->                    \
                        ChannelStatus[ChannelId]);
    LinCorePtr = Lin_17_AscLin_kConfigPtr->CoreConfigPtr[CoreId];
    ChanCfgPtr = &(LinCorePtr->ChannelConfigPtr[ChannelId]);
    /* Extract HwUnit */
    HwUnit = ChanCfgPtr->HwModule;

    HwModulePtr = Lin_17_AscLin_kAscLinKernelRegAddr[HwUnit];
    /* If global interrupts are disabled */
    /* [cover parentID={D75E246D-0169-491e-8F2C-13D748B17109}]
       [/cover] */
    /* [cover parentID={B773D1E5-8B30-49ea-AFFD-AF9C1B138B8F}]
       [/cover] */
    #if (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_OFF)
    Lin_17_AscLin_lPolling(HwUnit, ChannelStatePtr, HwModulePtr);
    #endif

    CurrentState = ChannelStatePtr->State;
    FifoValue = HwModulePtr->RXFIFOCON.B.FILL;
    Status = Lin_17_AscLin_lRetState(CurrentState, ChannelStatePtr, FifoValue);
    /* [cover parentID={E5F47BAE-30C8-4960-90A0-2258B37D3ED2}]
       [/cover] */
    if (Status == LIN_RX_OK)
    {
      /* [cover parentID={DBDFDED2-7DF0-4624-AD39-DDC1E0D4466B}]
         [/cover] */
      /* Successful reception */
      /* Assign the receive buffer pointer */
      *LinSduPtr = ChannelStatePtr->ResponseBuffer;
    }
  }
  /* [cover parentID={4144ED6C-404A-48df-A98E-02544BB71B93}]
    [/cover] */
  return Status;
}
#endif
#if (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_OFF)
/*******************************************************************************
** Traceability :[cover parentID={0E4055EC-B159-4894-AE44-E60B419BD53B}]      **
**                        [/cover]                                            **
** Syntax :          static void Lin_17_AscLin_lPolling(const uint8  HwUnit   **
**                    Lin_17_AscLin_ChannelInfoType *const ChannelStatePtr,   **
**                    const Ifx_ASCLIN* HwModulePtr)                          **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       non reentrant                                            **
**                                                                            **
** Parameters (in):  HwUnit : Represents Hw Module number                     **
**                :  ChannelStatePtr : Pointer to the channel state           **
**                :  HwModulePtr : Pointer to the Hw-Unit                     **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :     This function will be called when the interrupts are off **
** Note :      This function is applicable to Master nodes only               **
*******************************************************************************/
static void Lin_17_AscLin_lPolling(const uint8  HwUnit,
                                   Lin_17_AscLin_ChannelInfoType *const ChannelStatePtr,
                                   const Ifx_ASCLIN* HwModulePtr)
{
  const Lin_PduType *PduStatePtr;
  Lin_17_AscLin_InternalStatusType CheckErr;
  uint32 HwFlags;
  uint8 CoreId;
  uint8 Channel;
  uint8 ChannelId;

  /* Extract the Channel */
  Channel =                                                                   \
      Lin_17_AscLin_kConfigPtr->Lin_17_AscLin_ChannelIdLookupPtr[HwUnit];
  HwFlags = HwModulePtr->FLAGS.U;

  /* [cover parentID={237B6FDA-46FB-4a04-9195-2BECBADD7920}]
     [/cover] */
  /* Get core id which is executing currently */
  CoreId = (uint8)Mcal_GetCpuIndex();

  /*Extracting the physical channel ID*/
  ChannelId = Lin_17_AscLin_kConfigPtr->ChannelToCorePtr[Channel];

  PduStatePtr = &(Lin_17_AscLin_kCoreStatus[CoreId]->Lin_Pdu[ChannelId]);

  CheckErr = Lin_17_AscLin_lGetIntErrorStatus_Master(HwFlags, Channel);

  if (CheckErr !=  LIN_17_ASCLIN_MASTER_CH_INIT_STATE_I)
  {
    Lin_17_AscLin_lHandleErr(HwUnit);
    ChannelStatePtr->State = CheckErr;
  }

  else if ( LIN_17_ASCLIN_MSR_MASTER_RESPONSE_I == PduStatePtr->Drc)
  {
    if (((HwFlags & ((uint32)LIN_17_ASCLIN_FLAGSREG_TR)) !=                    \
         LIN_17_ASCLIN_DISABLE_FLAG))
    {
      Lin_17_AscLin_lHandleTx_Master(CoreId, HwUnit, Channel);
    }
  }

  else if (LIN_17_ASCLIN_MSR_SLAVE_RESPONSE_I == PduStatePtr->Drc)
  {
    if(((HwFlags & ((uint32)LIN_17_ASCLIN_FLAGSREG_RR)) !=                     \
        LIN_17_ASCLIN_DISABLE_FLAG))
    {
      Lin_17_AscLin_lHandleRx_Master(CoreId, HwUnit, Channel);
    }
  }
  else
  {
    if(((HwFlags & ((uint32)LIN_17_ASCLIN_FLAGSREG_TH)) !=
        LIN_17_ASCLIN_DISABLE_FLAG))
    {
      Lin_17_AscLin_lHandleTx_Master(CoreId, HwUnit, Channel);
    }
  }
}
#endif

#if(LIN_17_ASCLIN_HW_ERROR_DEM_REPORT == LIN_17_ASCLIN_DEM_REPORT_ENABLED)
/*******************************************************************************
** Traceability :[cover parentID={C556947E-7134-46e8-B36A-8A02415A4AA7}]      **
**                        [/cover]                                            **
** Syntax :          static void Lin_17_AscLin_lReportDemError                **
**                                 (const Dem_EventIdType EventId,            **
**                                  const Dem_EventStatusType EventStatus)    **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  Dem_EventIdType - DEM Event ID                           **
**                   Dem_EventStatusType - DEM Status ID                      **
**                                                                            **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description     : Function reports production error based on the AS version             **
** Note :      This function is applicable to both Master and Slave nodes     **
*******************************************************************************/

static void Lin_17_AscLin_lReportDemError
(
  const Dem_EventIdType EventId,
  const Dem_EventStatusType EventStatus
)
{
  #if (MCAL_AR_VERSION == MCAL_AR_440)
  /* Report Production Error status for AS 440 */
  /* [cover parentID={4CF06BA6-C062-4803-BDCA-78CBE960F6EB}]
     [/cover] */
  (void)Mcal_Wrapper_Dem_SetEventStatus(EventId, EventStatus);
  #else
  /* Report Production Error status for AS 422 */
  /* [cover parentID={69C87B7A-7F25-4272-A938-C9C770669078}]
     [/cover] */
  Mcal_Wrapper_Dem_ReportErrorStatus(EventId, EventStatus);
  #endif
}
#endif
/*******************************************************************************
** Traceability :[cover parentID={1A15D430-7304-401d-B708-757D9D15340B}]      **
**                        [/cover]                                            **
** Syntax :          static Std_ReturnType Lin_17_AscLin_lHwBitChangeCheck    **
**                         (const Ifx_ASCLIN *HwModulePtr,const uint8 BitVal) **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Non-Reentrant                                            **
**                                                                            **
** Parameters (in): HwModulePtr: Pointer to the SFR                           **
**                : BitVal : Bit to be set/reset                              **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:    E_OK     :Bit has set/reset within the time duration      **
**                  E_NOT_OK :Bit failed to set/reset within the time duration**
**                                                                            **
** Description : Function monitors the bit set/reset for given timeout and    **
                 returns E_OK or E_NOT_OK                                     **
** Note :      This function is applicable to both Master and Slave nodes     **
*******************************************************************************/

static Std_ReturnType Lin_17_AscLin_lHwBitChangeCheck
(
  const Ifx_ASCLIN *HwModulePtr,
  const uint8 BitVal
)
{
  uint32 TimeOutCount ;
  uint32 MeasuredTicks;
  uint32 TimeOutResolution;
  uint32 InitialCount;
  uint8 ConBitChk;
  Std_ReturnType ReturnStatus = E_NOT_OK;

  TimeOutResolution = Mcal_DelayTickResolution();
  TimeOutCount = ((uint32)LIN_17_ASCLIN_TIMEOUT_COUNT / TimeOutResolution);

  InitialCount = Mcal_DelayGetTick();
  /* provide delay of TW >= 4 * (1/fA) + 2 * (1/fCLC) clock cycles */
  /*Wait TW or poll for CSR.CON = 1*/
  do
  {
    MeasuredTicks = Mcal_DelayGetTick() -  InitialCount;
    ConBitChk = HwModulePtr->CSR.B.CON;
  } while ((ConBitChk != BitVal) && (TimeOutCount         \
                                     > MeasuredTicks));

  /* If bit is Set/Reset successfully */
  /* [cover parentID={A26E8BE4-2C4F-45bc-AD34-F7A9F834ACA6}]
         [/cover] */
  if( ConBitChk == BitVal)
  {
    ReturnStatus = E_OK;
  }
  return ReturnStatus;
}

#if (LIN_17_ASCLIN_MASTER_CH_PRESENT == STD_ON)
/*******************************************************************************
** Traceability :[cover parentID={CCCEF2B7-70FC-4501-8026-0DF89BE717D7}]      **
**                        [/cover]                                            **
** Syntax :          static Lin_StatusType Lin_17_AscLin_lRetState            **
**                   (const Lin_17_AscLin_InternalStatusType    CurrentState, **
**                      Lin_17_AscLin_ChannelInfoType *const ChannelStatePtr, **
**                      const uint8 FifoValue)                                **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       non reentrant                                            **
**                                                                            **
** Parameters (in):  CurrentState : Represents internal channel status        **
**                                                                            **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:    LIN_NOT_OK  : Development or Production error occurred    **
**                  LIN_TX_OK   : Successful transmission                     **
**                  LIN_TX_BUSY : Ongoing Transmission (Header or Response)   **
**                  LIN_TX_HEADER_ERROR :                                     **
**                      Erroneous header transmission such as:                **
**                         - Mismatch between sent and read back data         **
**                         - Identifier parity error or                       **
**                         - Physical bus error                               **
**                  LIN_TX_ERROR: Erroneous transmission                      **
**                         - Mismatch between sent and read back data         **
**                         - Physical bus error                               **
**                  LIN_RX_OK   : Reception of correct response               **
**                  LIN_RX_BUSY : Ongoing reception: at least one response    **
**                                byte has been received, but the checksum    **
**                                byte has not been received                  **
**                  LIN_RX_ERROR: Erroneous reception                         **
**                                - Framing error                             **
**                                - Data error                                **
**                                - Checksum error or Short response          **
**                  LIN_RX_NO_RESPONSE : No reception                         **
**                  LIN_CH_OPERATIONAL : Normal operation; the related LIN    **
**                                    channel is ready to transmit next header**
**                                    No data from previous frame available   **
**                                   (e.g. after initialization)              **
**                  LIN_SLEEP : Sleep mode operation; in this mode wake-up    **
**                                 detection from slave nodes is enabled      **
**                  LIN_TX_HEADER_TIMEOUT_ERROR : Header timeout occured      **
**                  LIN_RX_RESPONSE_TIMEOUT_ERROR : Response timeout occured  **
**                                                                            **
** Description :    Indicates the current transmission, reception or          **
**                  operation status of the LIN driver                        **
**                                                                            **
** Note :      This function is applicable to Master nodes only               **
*******************************************************************************/
static Lin_StatusType Lin_17_AscLin_lRetState
(
  const Lin_17_AscLin_InternalStatusType    CurrentState,
  Lin_17_AscLin_ChannelInfoType *const ChannelStatePtr,
  const uint8 FifoValue
)
{
  Lin_StatusType  ChanStatus = LIN_OPERATIONAL;

  switch(CurrentState)
  {

    case LIN_17_ASCLIN_MASTER_TX_COMPLETE_STATE_I:
    {
      /* Successful transmission */
      /* [cover parentID={4185425B-FBED-494f-9069-8F4684BA28F6}]
         [/cover] */
      ChanStatus = LIN_TX_OK;
      break;
    }

    case LIN_17_ASCLIN_SLEEP_STATE_I:
    {
      /* Lin is in Sleep */
      /* [cover parentID={630BEAA7-839E-4939-97FD-2B0B212F1EA6}]
         [/cover] */
      ChanStatus = LIN_CH_SLEEP;
      break;
    }
    /* [cover parentID={95F706B8-8DF0-4939-ABAF-3D4C0F0EC344}]
       [/cover] */
    case LIN_17_ASCLIN_MASTER_SLEEP_PENDING_STATE_I:
    {
      /* Lin is in Sleep */
      /* [cover parentID={639B5194-5EFC-470e-8B95-7C6C0ECEDEB4}]
          [/cover] */

      ChanStatus = LIN_CH_SLEEP;
      ChannelStatePtr->State = LIN_17_ASCLIN_SLEEP_STATE_I;
      break;
    }

    case LIN_17_ASCLIN_MASTER_RX_COMPLETE_STATE_I:
    {
      /* [cover parentID={F0DCDC16-30C4-4007-B8E9-4ABC0933B4B1}]
       [/cover] */

      /* Successful reception */
      ChanStatus = LIN_RX_OK;
      break;
    }

    case LIN_17_ASCLIN_MASTER_TX_HDR_ERROR_STATE_I:
    {
      /* erroneous header transmission */
      /* [cover parentID={4278636F-88F5-4b83-B5EC-6A23F31164CA}]
       [/cover] */
      ChanStatus = LIN_TX_HEADER_ERROR;
      break;
    }

    case LIN_17_ASCLIN_MASTER_TX_ERROR_STATE_I:
    {
      /* Erroneous transmission */
      /* [cover parentID={7B4B8D39-785C-4f95-AB67-493F58009FDB}]
       [/cover] */
      ChanStatus = LIN_TX_ERROR;
      break;
    }

    case LIN_17_ASCLIN_MASTER_RX_ERROR_STATE_I:
    {
      /* Erroneous reception */
      /* [cover parentID={01E7CDC8-74E1-4fa6-BF49-BC1716E05E42}]
       [/cover] */
      ChanStatus = LIN_RX_ERROR;
      break;
    }

    case LIN_17_ASCLIN_MASTER_RX_NO_RESP_STATE_I:
    {
      /* No response received */
      ChanStatus = LIN_RX_NO_RESPONSE;
      break;
    }
    case LIN_17_ASCLIN_MASTER_SEND_HDR_RESP_STATE_I:
    {
      /* [cover parentID={952DE7E2-71C1-40f1-8B13-481328AD7003}]
       [/cover] */
      ChanStatus = LIN_TX_BUSY;
      break;
    }
    case LIN_17_ASCLIN_MASTER_RESP_RECEIVE_WAIT_STATE_I:
    {
      /* ID + atleast 1 response data byte received */

      if (LIN_17_ASCLIN_RXFIFOVAL_IDONLY < FifoValue)
      {
        /* When response type is Slave Response and only
           1 response byte is received */
        /* ID + atleast 1 response data byte received */
        /* [cover parentID={30045D09-49CF-4d94-9CCD-97BBE46358B5}]
           [/cover] */
        ChanStatus = LIN_RX_BUSY;
      }
      /* When reponse type is
            Slave Response and no reponse byte received OR
         When response type is
           Slave to Slave */


      else if (LIN_17_ASCLIN_RXFIFOVAL_IDONLY == FifoValue )
      {
        /* Only ID received. No response data byte received */
        /* [cover parentID={CBE09E6B-D20E-4f56-ABBF-9166B4B53CF5}]
           [/cover] */
        ChanStatus = LIN_RX_NO_RESPONSE;
      }
      else
      { /* Empty Else */
      }
      break;
    }

    default:
    {
      /* Default case is Normal operation */
      /* [cover parentID={C4547DED-454C-41a1-A386-5EE342FD2951}]
         [/cover] */
      ChanStatus = LIN_OPERATIONAL;
      break;
    }
  }
  return ChanStatus;
}
#endif
#if (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON)
/*******************************************************************************
** Traceability :[cover parentID={2CB4EE2F-66E6-4169-9A87-C3E729D3BBB7}]      **
**                        [/cover]                                            **
** Syntax :          void Lin_17_AscLin_IsrReceive(const uint8  HwUnit)       **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  HwUnit : Represents Hw Module number                     **
**                                                                            **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :     This ISR will be called whenever the Slave response data **
**                   is completely received or Header is completely recieved  **
**                                          by the ASCLIN w/o any errors      **
** Note :      This API is applicable to both Master and Slave nodes          **
*******************************************************************************/
void Lin_17_AscLin_IsrReceive(const uint8  HwUnit)
{
  uint32 StatusFlags;
  const Ifx_ASCLIN *HwModulePtr;
  uint8 Channel;
  uint8 CoreId;
  uint8 ChannelId;
  const Lin_17_AscLin_ChannelType *ChanCfgPtr;
  /* Get core id which is executing currently */
  CoreId = (uint8)Mcal_GetCpuIndex();

  HwModulePtr = Lin_17_AscLin_kAscLinKernelRegAddr[HwUnit];

  /* Extract the Channel */
  Channel =                                                                    \
      Lin_17_AscLin_kConfigPtr->Lin_17_AscLin_ChannelIdLookupPtr[HwUnit];

  StatusFlags = HwModulePtr->FLAGS.U;
  /*Extracting the physical channel ID*/
  ChannelId = Lin_17_AscLin_kConfigPtr->ChannelToCorePtr[Channel];
  ChanCfgPtr = &(Lin_17_AscLin_kConfigPtr->CoreConfigPtr[CoreId]->             \
                 ChannelConfigPtr[ChannelId]);

  /*[cover parentID={06FCE003-905F-4af7-9273-1926F4E52C3E}][/cover]*/
  /*[cover parentID={AB1D241E-CCCC-4bc5-B21C-0E21BCCA91BF}][/cover]*/
  #if ((MCAL_AR_VERSION == MCAL_AR_440) && (LIN_17_ASCLIN_SLAVE_CH_PRESENT == STD_ON))
  if (ChanCfgPtr->Node == LIN_17_ASCLIN_SLAVE_NODE)
  {
    /*[cover parentID={19BCC778-CF72-4f97-851B-AB6BB3021220}][/cover]*/
    if((StatusFlags & (((uint32)LIN_17_ASCLIN_FLAGSREG_RH) |
                       (uint32)LIN_17_ASCLIN_FLAGSREG_RR)) !=                  \
        LIN_17_ASCLIN_DISABLE_FLAG)
    {
      Lin_17_AscLin_lHandleRx_Slave(CoreId, HwUnit, Channel);
    }
  }
  #endif
  #if (LIN_17_ASCLIN_MASTER_CH_PRESENT == STD_ON)
  if (ChanCfgPtr->Node == LIN_17_ASCLIN_MASTER_NODE)
  {
    /*[cover parentID={7D2BF45E-3CBF-4385-9BAD-AF9E84CEA21D}][/cover]*/
    if((StatusFlags & ((uint32)LIN_17_ASCLIN_FLAGSREG_RR)) !=                  \
        LIN_17_ASCLIN_DISABLE_FLAG)
    {
      Lin_17_AscLin_lHandleRx_Master(CoreId, HwUnit, Channel);
    }
  }
  #endif
}
#endif
#if (LIN_17_ASCLIN_MASTER_CH_PRESENT == STD_ON)
/*******************************************************************************
** Traceability :[cover parentID={A2D519FC-40B7-4ce7-9F54-1060A2530D5B}]      **
**                        [/cover]                                            **
** Syntax :  static void Lin_17_AscLin_lHandleRx_Master(const uint8  HwUnit)  **
**                             const uint8  HwUnit, const uint8 Channel)      **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in): CoreId : Represents the Core Id                           **
**                  HwUnit : Represents Hw Module number                      **
**                  Channel: LIN channel to be addressed                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :     This local function will be called whenever the Slave    **
                     response data is completely received by the ASCLIN w/o   **
                     any errors                                               **
** Note :      This function is applicable to Master nodes only               **
*******************************************************************************/
static void Lin_17_AscLin_lHandleRx_Master(const uint8 CoreId,
    const uint8  HwUnit,
    const uint8 Channel)
{
  uint8 *RespPtr;
  uint8 Count;
  uint8 ChannelId;
  Ifx_ASCLIN *HwModulePtr;
  Lin_17_AscLin_ChannelInfoType *ChannelStatePtr;
  const Lin_PduType *PduStatePtr;

  /*Extracting the physical channel ID*/
  ChannelId = Lin_17_AscLin_kConfigPtr->ChannelToCorePtr[Channel];
  ChannelStatePtr = &(Lin_17_AscLin_kCoreStatus[CoreId]->                      \
                      ChannelStatus[ChannelId]);
  PduStatePtr = &(Lin_17_AscLin_kCoreStatus[CoreId]->Lin_Pdu[ChannelId]);

  /* copy the Response buffer pointer to local variable */
  RespPtr = ChannelStatePtr->ResponseBuffer;
  Count = PduStatePtr->Dl;
  HwModulePtr = Lin_17_AscLin_kAscLinKernelRegAddr[HwUnit];

  /*[cover parentID={C972A71B-3B64-4dff-A4C7-07F63C93E7A6}][/cover]*/
  *RespPtr = (uint8)HwModulePtr->RXDATA.U;

  /* Copy the RX FIFO data to the given buffer */
  while(Count != 0U)
  {
    *RespPtr = (uint8)HwModulePtr->RXDATA.U;
    RespPtr++;
    Count--;
  }

  /* [cover parentID={D2FF3221-EAF7-4308-A633-31E5897ABE77}]
      [/cover] */
  /* Flush the RX, TX FIFOs */
  HwModulePtr->TXFIFOCON.B.FLUSH = LIN_17_ASCLIN_ENABLE_FLAG;
  HwModulePtr->RXFIFOCON.B.FLUSH = LIN_17_ASCLIN_ENABLE_FLAG;

  /* Clear and disable all intr in FlagsEnable register */
  HwModulePtr->FLAGSCLEAR.U = (uint32)
                              LIN_17_ASCLIN_FLAGSCLEAR_MASK;

  HwModulePtr->FLAGSENABLE.U = (uint32)LIN_17_ASCLIN_DISABLE_FLAG;

  /* Update the state */
  ChannelStatePtr->State = LIN_17_ASCLIN_MASTER_RX_COMPLETE_STATE_I;
}
#endif
#if ((MCAL_AR_VERSION == MCAL_AR_440)&& (LIN_17_ASCLIN_SLAVE_CH_PRESENT == STD_ON))
/*******************************************************************************
** Traceability :[cover parentID={26639343-1744-46cf-9827-99C88A67C2D8}]      **
**                        [/cover]                                            **
** Syntax :          static void Lin_17_AscLin_lHandleRx_Slave(               **
**                      const uint8 CoreId, const uint8  HwUnit,              **
**                                         const uint8 Channel)               **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in): CoreId : Represents the Core Id                           **
**                  HwUnit : Represents Hw Module number                      **
**                  Channel: LIN channel to be addressed                      **
**                                                                            **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :     This local function will be called whenever the Master   **
                     response data is completely received by the ASCLIN w/o   **
                     any errors                                               **
** Note :      This function is applicable to Slave nodes only                **
*******************************************************************************/
static void Lin_17_AscLin_lHandleRx_Slave(const uint8 CoreId,
    const uint8  HwUnit,
    const uint8 Channel)
{
  uint8 *RespPtr;
  uint8 Count;
  uint8 Index;
  uint8 ChannelId;
  const uint8 *DataPtr;
  uint32 StatusFlags;
  uint32 RetVal = E_NOT_OK;
  Ifx_ASCLIN *HwModulePtr;
  Lin_17_AscLin_ChannelInfoType *ChannelStatePtr;
  Lin_PduType *PduPtr;

  /*Extracting the physical channel ID*/
  ChannelId = Lin_17_AscLin_kConfigPtr->ChannelToCorePtr[Channel];
  ChannelStatePtr = &(Lin_17_AscLin_kCoreStatus[CoreId]->                      \
                      ChannelStatus[ChannelId]);
  PduPtr = &(Lin_17_AscLin_kCoreStatus[CoreId]->Lin_Pdu[ChannelId]);
  HwModulePtr = Lin_17_AscLin_kAscLinKernelRegAddr[HwUnit];
  StatusFlags = HwModulePtr->FLAGS.U;

  if (ChannelStatePtr->State == LIN_17_ASCLIN_SLAVE_HDR_WAIT_STATE_I)
  {
    /* Check if the header is received successfully */
    /* [cover parentID={E39E0F17-78C1-4c21-B293-4A4F88B2B3EC}]
      [/cover] */
    /* [cover parentID={B3CE0FEF-59DB-4489-81FA-0E48A21BAFC6}]
      [/cover] */
    if((StatusFlags & ((uint32)LIN_17_ASCLIN_FLAGSREG_RH)) !=                  \
        LIN_17_ASCLIN_DISABLE_FLAG)
    {
      /* Provide the ID received to LinIf layer */
      /* [cover parentID={C839FD85-9575-460c-BEB6-D6FCE3F86BC5}]
      [/cover] */
      PduPtr->Pid = (uint8)HwModulePtr->RXDATA.U;

      RetVal = LinIf_HeaderIndication(Channel, PduPtr);
      /* Check if the callback function returned E_OK */
      /* [cover parentID={DCD457CA-3C10-48f2-B907-10E6D246FEA6}]
      [/cover] */
      if (RetVal == E_OK)
      {
        /* Configure the data length, checksum , response timeout */
        HwModulePtr->DATCON.B.DATLEN = PduPtr->Dl - 1U ;

        /* Copy PDU parmaeters */
        if(PduPtr->Cs == LIN_ENHANCED_CS)
        {
          HwModulePtr->DATCON.B.CSM = (Lin_FrameCsModelType)LIN_CLASSIC_CS;
          /* The arrangement of checksum mode
              in DATCON.CSM is opposite of the
              enum definition */
        }
        else
        {
          HwModulePtr->DATCON.B.CSM = (Lin_FrameCsModelType)LIN_ENHANCED_CS;
        }
        /* Identify the frameresponse type. If response type is MasterResponse*/
        /* [cover parentID={E5A1342B-6C0F-424b-B4B0-94471362E69A}]
           [/cover] */
        if (PduPtr->Drc == LIN_17_ASCLIN_SLV_MASTER_RESPONSE_I)
        {
          ChannelStatePtr->State = LIN_17_ASCLIN_SLAVE_RX_RESP_WAIT_STATE_I;
          /* Calculate the Response timeout value as per LIN2.1
          Response timeout = ((10 * (Datalength + 1) * 1.4))
                  = ((Datalength +1) * (14))
          */
          HwModulePtr->DATCON.B.RESPONSE = LIN_17_ASCLIN_MAX_RESPONSE_TIMEOUT;

          /* Inlet to be enabled */
          HwModulePtr->RXFIFOCON.B.ENI = LIN_17_ASCLIN_ENABLE_FLAG;
          HwModulePtr->DATCON.B.HO = LIN_17_ASCLIN_DISABLE_FLAG;

          /* On response receive, same interrupt will be retriggered */
          HwModulePtr->FLAGSENABLE.U = LIN_17_ASCLIN_SLAVE_RECEIVE_RESPONSE_INTERRUPTS;
        }
        /*If response type is SlaveResponse*/
        /* [cover parentID={323D8FB7-15DA-4a7c-B65D-E51A7FC595EF}]
           [/cover] */
        else if(PduPtr->Drc == LIN_17_ASCLIN_SLV_SLAVE_RESPONSE_I)
        {
          /* Write Data bytes to Tx fifo in case of Slave response */
          /* [cover parentID={3EBB4AC7-45AF-4487-A78B-49F150CCC7B9}]
             [/cover] */
          Index = 0U;
          DataPtr = PduPtr->SduPtr;
          do
          {
            HwModulePtr->TXDATA.U = *DataPtr;
            DataPtr++;
            Index++;
          } while (Index < PduPtr->Dl);

          ChannelStatePtr->State = LIN_17_ASCLIN_SLAVE_TX_RESP_COMPLETE_WAIT_STATE_I;
          HwModulePtr->DATCON.B.HO = LIN_17_ASCLIN_DISABLE_FLAG;

          /* Clear all events except RH*/
          HwModulePtr->FLAGSCLEAR.U = LIN_17_ASCLIN_NOT_RH_FLAGSCLEAR;
          HwModulePtr->FLAGSENABLE.U = LIN_17_ASCLIN_SLAVE_TRANSMIT_RESPONSE_INTERRUPTS;

          /* TRRQS is SET to start the transmission of response */
          HwModulePtr->FLAGSSET.B.TRRQS = LIN_17_ASCLIN_ENABLE_FLAG;

          /* Enable outlet */
          HwModulePtr->TXFIFOCON.B.ENO = LIN_17_ASCLIN_ENABLE_FLAG;
        }
        /*If response type is IgnoreResponse*/
        /* [cover parentID={905C5CA1-09A8-4b3b-A648-6E6225D2B112}]
           [/cover] */
        else
        {
          /* Change State to header wait, Header receive + errors, Clear all interrupts + FIFO Flush */
          /* [cover parentID={CAC0F2C3-CB5A-4c2f-85D6-F03EFA85D984}]
           [/cover] */
          Lin_17_Asclin_lPrepareSlaveForHeaderRx(HwModulePtr, ChannelStatePtr,
                                                 LIN_17_ASCLIN_BREAK_NOT_DETECTED);
        }
      }
      else
      {
        /* Change State to header wait, Header receive + errors, Clear all interrupts + FIFO Flush.*/
        /* [cover parentID={4C7C39F0-3FC6-4e24-8633-02DE34929244}]
           [/cover] */
        Lin_17_Asclin_lPrepareSlaveForHeaderRx(HwModulePtr, ChannelStatePtr,
                                               LIN_17_ASCLIN_BREAK_NOT_DETECTED);
      }
      /* [cover parentID={06BACA4A-0F64-48a5-B1B8-5A9BA48CDF75}]
           [/cover] */
      HwModulePtr->FLAGSCLEAR.U = (uint32)
                                  LIN_17_ASCLIN_FLAGSREG_RH;
    }
  }
  else
  {
    if((StatusFlags & ((uint32)LIN_17_ASCLIN_FLAGSREG_RR)) !=                  \
        LIN_17_ASCLIN_DISABLE_FLAG)
    {
      /* copy the Response buffer pointer to local variable */
      RespPtr = ChannelStatePtr->ResponseBuffer;
      Count = PduPtr->Dl;

      /* Copy the RX FIFO data to the given buffer */
      while(Count != 0U)
      {
        *RespPtr = (uint8)HwModulePtr->RXDATA.U;
        RespPtr++;
        Count--;
      }
      RespPtr = ChannelStatePtr->ResponseBuffer;
      /*Invoke the callback function with parameter set to reception data*/
      /* [cover parentID={C0D5FEB1-146B-4fca-8EA8-8FF768F929B4}]
         [/cover] */
      LinIf_RxIndication (Channel, RespPtr);

      /* Change State to header wait, Header receive + errors,
      Clear all interrupts */

      Lin_17_Asclin_lPrepareSlaveForHeaderRx(HwModulePtr, ChannelStatePtr,
                                             LIN_17_ASCLIN_BREAK_NOT_DETECTED);

      /* Clear receive response flag */
      /* [cover parentID={096737E4-7C34-4fa5-88A8-8095E1BCB2DA}]
         [/cover] */
      HwModulePtr->FLAGSCLEAR.U = (uint32)
                                  LIN_17_ASCLIN_FLAGSREG_RR;
    }
  }
}
#endif
#if (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON)
/*******************************************************************************
** Traceability :[cover parentID={2842502A-E2A6-4d6d-8F06-82AAE3D96731}]      **
**                           [/cover]                                         **
** Syntax :          void Lin_17_AscLin_IsrTransmit( uint8  HwUnit)           **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  HwUnit : Represents Hw Module number                     **
**                                                                            **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :     This ISR will be called whenever the response data       **
**                   is successfully transmitted by the ASCLIN w/o any errors **
** Note :      This API is applicable to both Master and Slave nodes          **
*******************************************************************************/
void Lin_17_AscLin_IsrTransmit(const uint8  HwUnit)
{
  uint32 StatusFlags;
  const Ifx_ASCLIN *HwModulePtr;
  uint8 CoreId;
  uint8 Channel;
  uint8 ChannelId;
  const Lin_17_AscLin_ChannelType *ChanCfgPtr;
  /* Get core id which is executing currently */
  CoreId = (uint8)Mcal_GetCpuIndex();

  HwModulePtr = Lin_17_AscLin_kAscLinKernelRegAddr[HwUnit];

  StatusFlags = HwModulePtr->FLAGS.U;
  /* Extract the Channel */
  Channel =                                                                    \
      Lin_17_AscLin_kConfigPtr->Lin_17_AscLin_ChannelIdLookupPtr[HwUnit];
  /*Extracting the physical channel ID*/
  ChannelId = Lin_17_AscLin_kConfigPtr->ChannelToCorePtr[Channel];
  ChanCfgPtr = &(Lin_17_AscLin_kConfigPtr->CoreConfigPtr[CoreId]->             \
                 ChannelConfigPtr[ChannelId]);

  /* [cover parentID={193A941A-FA09-4c36-AA09-826BC8CE1C8F}]
      [/cover] */
  /* [cover parentID={0242755F-CCBB-4fe5-AD24-54D9FC57A86F}]
      [/cover] */
  #if ((MCAL_AR_VERSION == MCAL_AR_440) && (LIN_17_ASCLIN_SLAVE_CH_PRESENT == STD_ON))
  /* [cover parentID={ADF49AC0-8D7B-4da6-B971-77D59C985204}]
     [/cover] */
  if (ChanCfgPtr->Node == LIN_17_ASCLIN_SLAVE_NODE)
  {
    if((StatusFlags & ((uint32)LIN_17_ASCLIN_FLAGSREG_TR)) !=                  \
        LIN_17_ASCLIN_DISABLE_FLAG)
    {
      Lin_17_AscLin_lHandleTx_Slave(CoreId, HwUnit, Channel);
    }
  }
  #endif
  #if (LIN_17_ASCLIN_MASTER_CH_PRESENT == STD_ON)
  /* [cover parentID={CC2BAFE1-A7C2-4535-9E63-B9D9B52BBB9C}]
     [/cover] */
  if (ChanCfgPtr->Node == LIN_17_ASCLIN_MASTER_NODE)
  {
    if((StatusFlags & (((uint32)LIN_17_ASCLIN_FLAGSREG_TH) |
                       (uint32)LIN_17_ASCLIN_FLAGSREG_TR)) !=                  \
        LIN_17_ASCLIN_DISABLE_FLAG)
    {
      Lin_17_AscLin_lHandleTx_Master(CoreId, HwUnit, Channel);
    }
  }
  #endif
}
#endif
#if ((MCAL_AR_VERSION == MCAL_AR_440)&& (LIN_17_ASCLIN_SLAVE_CH_PRESENT == STD_ON))
/*******************************************************************************
** Traceability :[cover parentID={5E143E80-3FDA-48cd-8F0B-6B54D8155265}]      **
**                           [/cover]                                         **
** Syntax :          static void Lin_17_AscLin_lHandleTx_Slave(               **
**                          const uint8 CoreId,                               **
**                          const uint8  HwUnit,const uint8 Channel)          **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in): CoreId : Represents the Core Id                           **
**                  Channel: LIN channel to be addressed                      **
**                                                                            **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :     This ISR will be called whenever the response data       **
**                   is successfully transmitted by the ASCLIN w/o any errors **
** Note :      This function is applicable to Slave nodes only                **
*******************************************************************************/
static void Lin_17_AscLin_lHandleTx_Slave
(
  const uint8 CoreId, const uint8 HwUnit, const uint8 Channel
)
{
  uint8 ChannelId;
  Lin_17_AscLin_ChannelInfoType *ChannelStatePtr;
  Ifx_ASCLIN *HwModulePtr;

  HwModulePtr = Lin_17_AscLin_kAscLinKernelRegAddr[HwUnit];
  /*Extracting the physical channel ID*/
  ChannelId = Lin_17_AscLin_kConfigPtr->ChannelToCorePtr[Channel];
  ChannelStatePtr = &(Lin_17_AscLin_kCoreStatus[CoreId]->                      \
                      ChannelStatus[ChannelId]);

    /* Enable the Response transmission in case of Master to Slave  */
    /* [cover parentID={DDE9DF14-DB6D-4c84-8DDD-8012E916A668}]
      [/cover] */
    LinIf_TxConfirmation(Channel);

    /* Change State to header wait, Enable Break, Header receive, Clear all
    interrupts, Enable Inlet */
    /* [cover parentID={3004B005-3899-4f2a-8CB7-2BE3303B9C80}]
      [/cover] */
    Lin_17_Asclin_lPrepareSlaveForHeaderRx(HwModulePtr, ChannelStatePtr,
                                           LIN_17_ASCLIN_BREAK_NOT_DETECTED);

}
#endif
#if (LIN_17_ASCLIN_MASTER_CH_PRESENT == STD_ON)
/*******************************************************************************
** Traceability :[cover parentID={3E5700B0-6D15-46ea-8D42-3C2177F78CE5}]      **
**                           [/cover]                                         **
** Syntax :          static void Lin_17_AscLin_lHandleTx_Master(              **
**                const uint8 CoreId, const uint8 HwUnit, const uint8 Channel)**
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in): CoreId : Represents the Core Id                           **
**                  HwUnit : Represents Hw Module number                      **
**                  Channel: LIN channel to be addressed                      **
**                                                                            **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :     This ISR will be called whenever the response data       **
**                   is successfully transmitted by the ASCLIN w/o any errors **
** Note :      This function is applicable to Master nodes only               **
*******************************************************************************/
static void Lin_17_AscLin_lHandleTx_Master
(
  const uint8 CoreId, const uint8 HwUnit, const uint8 Channel
)
{
  #if (LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT == STD_ON)
  const Lin_17_AscLin_ChannelType *ChanCfgPtr;
  #endif
  Ifx_ASCLIN *HwModulePtr;
  uint8 ChannelId;
  Lin_17_AscLin_ChannelInfoType *ChannelStatePtr;
  HwModulePtr = Lin_17_AscLin_kAscLinKernelRegAddr[HwUnit];
  /*Extracting the physical channel ID*/
  /* [cover parentID={25E1E2B9-93E8-43ee-BB4D-4D735275EAD8}]
        [/cover] */
  ChannelId = Lin_17_AscLin_kConfigPtr->ChannelToCorePtr[Channel];
  ChannelStatePtr = &(Lin_17_AscLin_kCoreStatus[CoreId]->                      \
                      ChannelStatus[ChannelId]);

  /* Flush the RX, TX FIFOs */
  HwModulePtr->TXFIFOCON.B.FLUSH = LIN_17_ASCLIN_ENABLE_FLAG;
  HwModulePtr->RXFIFOCON.B.FLUSH = LIN_17_ASCLIN_ENABLE_FLAG;

  /* [cover parentID={7AC758FD-75DF-4cfb-B952-2685ED8B8CCC}]
        [/cover] */
  if (ChannelStatePtr->Sleep !=                                                \
      (uint8)LIN_17_ASCLIN_SLEEP_REQ)
  {
    /* If the Sleep is Not requested,
    then update the state to Transmit completed */

    /* [cover parentID={1E9CC33A-2372-4192-A962-F37B5E0AD56D}]
        [/cover] */
    ChannelStatePtr->State =                                                   \
        LIN_17_ASCLIN_MASTER_TX_COMPLETE_STATE_I;
  }
  else
  {
    /* Disable the Tx Outlet */
    HwModulePtr->TXFIFOCON.B.ENO = LIN_17_ASCLIN_DISABLE_FLAG;

    /* [cover parentID={01BA7042-867F-4811-B6A2-0729C4583CED}]
        [/cover] */
    #if (LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT == STD_ON)
    ChanCfgPtr = &(Lin_17_AscLin_kConfigPtr->CoreConfigPtr[CoreId]->           \
                   ChannelConfigPtr[ChannelId]);
    if (LIN_17_ASCLIN_CHANNEL_WAKEUP_ENABLED == (ChanCfgPtr->Wakeup))
    {
      HwModulePtr->FLAGSCLEAR.B.FEDC = LIN_17_CLEAR_EVENT_BIT;

      /* Enable the FED flag and intr */
      HwModulePtr->FLAGSENABLE.B.FEDE = LIN_17_ASCLIN_ENABLE_FLAG;
    }
    #endif
  }
  /* Clear and disable all intr in FlagsEnable register */
  HwModulePtr->FLAGSCLEAR.U = (uint32)
                              LIN_17_ASCLIN_FLAGSCLEAR_MASK ;
  HwModulePtr->FLAGSENABLE.U = (uint32)LIN_17_ASCLIN_DISABLE_FLAG;
}
#endif
#if ((MCAL_AR_VERSION == MCAL_AR_440)&& (LIN_17_ASCLIN_SLAVE_CH_PRESENT == STD_ON))
/*******************************************************************************
** Traceability :[cover parentID={CFC9BB48-E790-401f-860B-C189BE396C26}]      **
**                           [/cover]                                         **
** Syntax :          static void                                              **
**                  Lin_17_Asclin_lPrepareSlaveForHeaderRx                    **
**             (Ifx_ASCLIN *const HwModulePtr, Lin_17_AscLin_ChannelInfoType  **
**             *const ChannelStatePtr, const uint8 BreakBitValue)             **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  HwModulePtr : Represents address Hw Module number        **
**                   ChannelStatePtr: Represents the address of the channel   **
**                   state                                                    **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :     This local function will be called whenever slave channel**
**                   is to be prepared for next header reception              **
** Note :      This function is applicable to Slave nodes only                **
*******************************************************************************/
static void Lin_17_Asclin_lPrepareSlaveForHeaderRx
(
  Ifx_ASCLIN *const HwModulePtr, Lin_17_AscLin_ChannelInfoType *const ChannelStatePtr,
  const uint8 BreakBitValue
)
{
  /* FLUSH FIFO, disable Inlet / outlet, prepare for next reception */
  /* [cover parentID={27523CFB-537C-4159-98AB-FBFFB93D263A}]
      [/cover] */
  HwModulePtr->RXFIFOCON.B.ENI = LIN_17_ASCLIN_DISABLE_FLAG;
  HwModulePtr->TXFIFOCON.B.ENO = LIN_17_ASCLIN_DISABLE_FLAG;
  HwModulePtr->TXFIFOCON.B.FLUSH = LIN_17_ASCLIN_ENABLE_FLAG;
  HwModulePtr->RXFIFOCON.B.FLUSH = LIN_17_ASCLIN_ENABLE_FLAG;

  /* [cover parentID={78EA7533-10A9-43a5-9B4B-FA4948B99487}]
      [/cover] */
  if(BreakBitValue != LIN_17_ASCLIN_BREAK_DETECTED)
  {
    /* Deliberately not enabling inlet, as BREAK is trigerred ENI is HW enabled.
     Any Error bring back the state to Header-Wait state*/
    ChannelStatePtr->State = LIN_17_ASCLIN_SLAVE_HDR_WAIT_STATE_I;

    /* Clear all event flags */
    HwModulePtr->FLAGSCLEAR.U = LIN_17_ASCLIN_FLAGSCLEAR_VAL;
    HwModulePtr->FLAGSENABLE.U = LIN_17_ASCLIN_SLAVE_RECEIVER_HEADER_INTERRUPTS;
  }
}
#endif
#if (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON)
/*******************************************************************************
** Traceability :[cover parentID={75CFD809-326C-4952-A2FF-5526AB7CA43B}]      **
**                  [/cover]                                                  **
** Syntax :          void Lin_17_AscLin_IsrError( uint8  HwUnit)              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  HwUnit : Represents Hw Module number                     **
**                                                                            **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :     This ISR will be called whenever there is an data        **
**                   transmission or reception error                          **
**                   or a wakeup interrupt in ASCLIN                          **
** Note :      This API is applicable to both Master and Slave nodes          **
*******************************************************************************/
void Lin_17_AscLin_IsrError(const uint8 HwUnit)
{
  const Lin_17_AscLin_ChannelType *ChanCfgPtr;
  uint8 CoreId;
  uint8 Channel;
  uint8 ChannelId;
  uint32 HwFlags;
  Ifx_ASCLIN *HwModulePtr;
  HwModulePtr = Lin_17_AscLin_kAscLinKernelRegAddr[HwUnit];
  Lin_17_AscLin_ChannelInfoType *ChannelStatePtr;

  /* Extract the Channel */
  Channel =                                                                    \
      Lin_17_AscLin_kConfigPtr->Lin_17_AscLin_ChannelIdLookupPtr[HwUnit];
  HwFlags = HwModulePtr->FLAGS.U;

  /* Get core id which is executing currently */
  CoreId = (uint8)Mcal_GetCpuIndex();
  /*Extracting the physical channel ID*/
  ChannelId = Lin_17_AscLin_kConfigPtr->ChannelToCorePtr[Channel];
  ChannelStatePtr = &(Lin_17_AscLin_kCoreStatus[CoreId]->                      \
                      ChannelStatus[ChannelId]);
  ChanCfgPtr = &(Lin_17_AscLin_kConfigPtr->CoreConfigPtr[CoreId]->             \
                 ChannelConfigPtr[ChannelId]);
  /* if Channel has NOT requested Sleep */
  /* [cover parentID={797B6752-1D88-47b5-B5D0-8729D14A6EA0}]
      [/cover] */
  /* [cover parentID={43DD1352-7E95-47ce-B2A9-0C7F04132716}]
      [/cover] */
  if (ChannelStatePtr->Sleep == (uint8)LIN_17_ASCLIN_SLEEP_NOT_REQ)
  {
    #if ((MCAL_AR_VERSION == MCAL_AR_440)&&(LIN_17_ASCLIN_SLAVE_CH_PRESENT == STD_ON))
    if(ChanCfgPtr->Node == LIN_17_ASCLIN_SLAVE_NODE)
    {
      Lin_17_AscLin_lReportSlaveError(HwFlags, Channel);

      /* Change State to header wait, Flush FIFO, Header receive + errors,
      Clear all interrupts */
      Lin_17_Asclin_lPrepareSlaveForHeaderRx(HwModulePtr, ChannelStatePtr,
                                             LIN_17_ASCLIN_BREAK_NOT_DETECTED);
    }
    #endif
    #if (LIN_17_ASCLIN_MASTER_CH_PRESENT == STD_ON)
    if (ChanCfgPtr->Node == LIN_17_ASCLIN_MASTER_NODE)
    {
      /* [cover parentID={9591230D-A273-4891-BC4D-414DD0427872}]
      [/cover] */
      ChannelStatePtr->State =                                                 \
          Lin_17_AscLin_lGetIntErrorStatus_Master(HwFlags, Channel);
    }
    #endif
  }
  else
  {
    #if (LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT == STD_ON)
    if (((HwFlags & (uint32)LIN_17_ASCLIN_FLAGSREG_FED ) !=                    \
       LIN_17_ASCLIN_DISABLE_FLAG))
    {
        /* [cover parentID={639B5194-5EFC-470e-8B95-7C6C0ECEDEB4}]
           [/cover] */
        /* clear Falling edge intr */
        HwModulePtr->FLAGSCLEAR.B.FEDC = LIN_17_CLEAR_EVENT_BIT;

        /* Wakeup intr (no error) */
        /* [cover parentID={CF5A7105-24E3-44f6-B57D-1927A3DA9E2C}]
           [/cover] */
        if (LIN_17_ASCLIN_CHANNEL_WAKEUP_ENABLED == (ChanCfgPtr->Wakeup))
        {
          /* [cover parentID={4E13C3D9-D6A6-4e42-9466-FE3A9A09F874}]
             [/cover] */
          EcuM_CheckWakeup(                                                    \
             (uint32)LIN_17_ASCLIN_ENABLE_FLAG << (ChanCfgPtr->WakeupSourceId));

          #if ((MCAL_AR_VERSION == MCAL_AR_440)&&                              \
               (LIN_17_ASCLIN_SLAVE_CH_PRESENT == STD_ON))
          if(ChanCfgPtr->Node == LIN_17_ASCLIN_SLAVE_NODE)
          {
            /* Change State to header wait, Flush FIFO, Header receive + errors,
            Clear all interrupts */
            /* [cover parentID={FD5B6D79-8E80-46bf-8833-C8CE11E760FD}]
               [/cover] */
            Lin_17_Asclin_lPrepareSlaveForHeaderRx(HwModulePtr, ChannelStatePtr,
                                                  LIN_17_ASCLIN_BREAK_DETECTED);
          }
          else
          #endif
          {
            /* Disable Falling edge intr  for master*/
            HwModulePtr->FLAGSENABLE.B.FEDE = LIN_17_ASCLIN_DISABLE_FLAG;
          }
        }
    }
    else
    #endif
    {
        /* Clear all intr flags register */
        HwModulePtr->FLAGSCLEAR.U = (uint32) LIN_17_ASCLIN_FLAGSCLEAR_VAL;
    }
  }

  /* [cover parentID={5518F4F6-AF46-4b75-AC21-0215A43BA123}]
  [/cover] */
  if(ChanCfgPtr->Node == LIN_17_ASCLIN_MASTER_NODE)
  {
    Lin_17_AscLin_lHandleErr(HwUnit);
  }
}
#endif
/*******************************************************************************
** Traceability :[cover parentID={1F2EE594-92D5-41f6-8D58-C7F3A3A69817}]      **
**                        [/cover]                                            **
** Syntax :          static void Lin_17_AscLin_lHandleErr( uint8  HwUnit)     **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  HwUnit : Represents Hw Module number                     **
**                                                                            **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :     This ISR will be called whenever there is an data        **
**                   transmission or reception error                          **
**                   or a wakeup interrupt in ASCLIN                          **
** Note :      This function is applicable to Slave nodes only                **
*******************************************************************************/
static void Lin_17_AscLin_lHandleErr
(
  const uint8 HwUnit
)
{
  Ifx_ASCLIN *HwModulePtr;
  HwModulePtr = Lin_17_AscLin_kAscLinKernelRegAddr[HwUnit];

  /* Flush the RX, TX FIFOs */
  /* [cover parentID={FFCC72F3-D47F-41a3-8D63-A9854F84C426}]
      [/cover] */
  HwModulePtr->TXFIFOCON.B.FLUSH = LIN_17_ASCLIN_ENABLE_FLAG;
  HwModulePtr->RXFIFOCON.B.FLUSH = LIN_17_ASCLIN_ENABLE_FLAG;

  /* Clear any bit that is SET - 0xDFFFE06F irrespective of Master / Slave
     Clear and disable all intr in FlagsEnable register */

  HwModulePtr->FLAGSCLEAR.U = (uint32)
                              LIN_17_ASCLIN_CLEAR_ALL_EVENTS ;

  /* Only for MASTER need to clear all interrupts since these
     will be reconfigured in SendFrame API */

  HwModulePtr->FLAGSENABLE.U = (uint32)LIN_17_ASCLIN_DISABLE_FLAG;
}
/*******************************************************************************
** Traceability :[cover parentID={11D8FCC9-EA25-4cc7-A512-F27C802D74F9}]      **
**                        [/cover]                                            **
** Syntax : static Std_ReturnType Lin_17_AscLin_lGetDetStatus                 **
**         (                                                                  **
**           const uint8 Channel,                                             **
**           const uint8 ApiId                                                **
**                                                                            **
**         )                                                                  **
**                                                                            **
** Service ID:  None                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Re-entrant (for different channel Ids)                        **
**                                                                            **
** Parameters (in) :   Channel - ChannelId                                    **
**                     ApiId - API ID                                         **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns DET status, E_OK or E_NOT_OK                     **
**                                                                            **
** Description : This Function returns the status of DET check                **
** Note :      This function is applicable to both Master and Slave nodes     **
*******************************************************************************/
#if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)
static Std_ReturnType Lin_17_AscLin_lGetDetStatus
(
  const uint8 Channel,
  const uint8 ApiId
)
{
  Std_ReturnType ReturnStatus;
  uint8 CoreId;
  Lin_17_AscLin_CoreInitStatusType CoreState;
  #if (LIN_17_ASCLIN_MULTICORE_ERROR_DETECT == STD_ON)
  const Lin_17_AscLin_CoreStatesType *LocalCoreStatusPtr;
  const Lin_17_AscLin_ChannelType *ChannelCfgPtr;
  const Lin_17_AscLin_CoreConfigType *CorePtr;
  uint8 ChannelId;
  #endif /*(LIN_17_ASCLIN_MULTICORE_ERROR_DETECT == STD_ON)*/

  /* Get core id which is executing currently */
  CoreId = (uint8)Mcal_GetCpuIndex();
  /* [cover parentID={4E31C23B-01D3-46b8-8AB3-6E4F4DB3DE98}]
    [/cover] */
  ReturnStatus = E_NOT_OK;

  /* Check channel out of range*/
  /* [cover parentID={7F22A0B8-40DA-4fb1-9B71-E262A9B52F9E}]
      [/cover] */
  /* [cover parentID={EDB9A363-3AA1-43a1-9D0D-68F573ADFE64}]
      [/cover] */
  if ( Channel >= (uint8)LIN_17_ASCLIN_MAXIMUM_CHANNEL_CONFIGURED )
  {
    /* Report to  DET */
    /* [cover parentID={E1D7398F-8AEA-4e2c-AD82-BCDE054F120A}]
        [/cover] */
    (void)Det_ReportError(
      LIN_17_ASCLIN_MODULE_ID,
      LIN_17_ASCLIN_INSTANCE_ID,
      ApiId,
      LIN_17_ASCLIN_E_INVALID_CHANNEL
    );
  }
  else
  {
    ReturnStatus = E_OK;
  }

  if (ReturnStatus == E_OK)
  {
    #if (LIN_17_ASCLIN_MULTICORE_ERROR_DETECT == STD_ON)
    LocalCoreStatusPtr = Lin_17_AscLin_kCoreStatus[CoreId];
    /* [cover parentID={6494BBBF-93DF-4e44-922C-041994FF6C5E}]
        [/cover] */
    if(LocalCoreStatusPtr == NULL_PTR)
    {
      /* Report DET */

      (void)Det_ReportError(
        LIN_17_ASCLIN_MODULE_ID,
        LIN_17_ASCLIN_INSTANCE_ID,
        ApiId,
        LIN_17_ASCLIN_E_CORE_CHANNEL_MISMATCH
      );/* End of report to DET */
      ReturnStatus = E_NOT_OK;
    }
    else
    #endif /*(LIN_17_ASCLIN_MULTICORE_ERROR_DETECT == STD_ON)*/
    {
      CoreState = *Lin_17_AscLin_kCoreStatus[CoreId]->CoreInitStatus;
      /* Check for LIN module initialization */
      /* [cover parentID={16D15282-4E18-4f1c-85A4-497CB13CEC1C}]
        [/cover] */
      /* [cover parentID={EAC6896A-D756-46f1-9BC8-00919A2518E0}]
        [/cover] */
      if (CoreState != LIN_17_ASCLIN_CORE_INITIALIZED)
      {
        /* Report to  DET */
        /* [cover parentID={4EDF95B0-21BE-4693-8886-D401DA59D2E4}]
           [/cover] */
        (void)Det_ReportError(
          LIN_17_ASCLIN_MODULE_ID,
          LIN_17_ASCLIN_INSTANCE_ID,
          ApiId,
          LIN_17_ASCLIN_E_UNINIT
        );

        ReturnStatus = E_NOT_OK;
      }
    }
  }
  if (ReturnStatus == E_OK)
  {
    #if (LIN_17_ASCLIN_MULTICORE_ERROR_DETECT == STD_ON)
    /*Extracting the physical channel ID*/
    CorePtr = Lin_17_AscLin_kConfigPtr->CoreConfigPtr[CoreId];
    ChannelId = Lin_17_AscLin_kConfigPtr->ChannelToCorePtr[Channel];
    /* Report to  DET */
    /* [cover parentID={81C9A06B-C9CF-437e-8A56-3C3C7AC8E1CF}]
          [/cover] */
    if(ChannelId < CorePtr->MaxCoreChannels)
    {
      ChannelCfgPtr = &(CorePtr->ChannelConfigPtr[ChannelId]);
      /* Check if the logical channel id is not matching */
      /* [cover parentID={72E83C0B-D915-40fa-A0B5-C322BC934633}]
      [/cover] */
      if(ChannelCfgPtr->LogicalId != Channel)
      {
        /* Report to  DET */
        (void)Det_ReportError(
          LIN_17_ASCLIN_MODULE_ID,
          LIN_17_ASCLIN_INSTANCE_ID,
          ApiId,
          LIN_17_ASCLIN_E_CORE_CHANNEL_MISMATCH
        );
        ReturnStatus = E_NOT_OK;
      }
    }
    else
    {
      (void)Det_ReportError(
        LIN_17_ASCLIN_MODULE_ID,
        LIN_17_ASCLIN_INSTANCE_ID,
        ApiId,
        LIN_17_ASCLIN_E_CORE_CHANNEL_MISMATCH
      );
      ReturnStatus = E_NOT_OK;
    }

    #endif /*(LIN_17_ASCLIN_MULTICORE_ERROR_DETECT == STD_ON)*/
  }
  return ReturnStatus;
}
#endif /*(LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)*/

/*******************************************************************************
** Traceability :[cover parentID={BA1097B5-C2AC-4744-97AC-68CDAF23E632}]      **
**                           [/cover]                                         **
** Traceability :                                                             **
** Syntax           : static void Lin_17_AscLin_lHwInit                       **
**                      (                                                     **
**                        const Lin_17_AscLin_ConfigType *const Config        **
**                        const uint8 HwUnit                                  **
**                      )                                                     **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non reentrant                                           **
**                                                                            **
** Parameters (in)  : Config - Pointer to the config root                     **
**                    HwUnit   : ASCLIN Hardware module no                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : This function initializes the ASCLIN Hw module          **
** Note :      This function is applicable to both Master and Slave nodes     **
*******************************************************************************/

static Std_ReturnType Lin_17_AscLin_lHwInit
(
  const Lin_17_AscLin_ConfigType *const Config,
  const uint8 HwUnit
)
{
  Ifx_ASCLIN *HwModulePtr;
  uint8 HeaderTimeOutVal;
  Std_ReturnType ClkStatus = E_NOT_OK;
  uint8 RxAlternatePinSelect;
  Lin_17_AscLin_ChannelTimingConfigType TimingCfg;

  uint8 CoreId;
  uint8 ChannelId;
  uint8 Channel;
  const Lin_17_AscLin_CoreConfigType *LinCorePtr;
  const Lin_17_AscLin_ChannelType *ChanCfgPtr;

  HwModulePtr = Lin_17_AscLin_kAscLinKernelRegAddr[HwUnit];

  /* Extract the Channel */
  Channel =                                                                    \
      Config->Lin_17_AscLin_ChannelIdLookupPtr[HwUnit];
  CoreId = (uint8)Mcal_GetCpuIndex();
  ChannelId = Config->ChannelToCorePtr[Channel];
  LinCorePtr = Config->CoreConfigPtr[CoreId];
  ChanCfgPtr = &(LinCorePtr->ChannelConfigPtr[ChannelId]);

  TimingCfg = ChanCfgPtr->TimingConfig;
  RxAlternatePinSelect = ChanCfgPtr->RxAlternatePinSelect;

  /* Disable the Clock source. */
  HwModulePtr->CSR.B.CLKSEL = LIN_17_ASCLIN_CSRREG_CLKSEL_NOCLK;

  /* Check status of disabling of clock source */
  ClkStatus = (Std_ReturnType)Lin_17_AscLin_lHwBitChangeCheck(
                HwModulePtr, LIN_17_ASCLIN_DISABLE_FLAG);

  if(ClkStatus == E_OK)
  {
    /* Change to INIT mode */
    /* [cover parentID={3831B2B5-BC7E-461f-9B3A-85054ED31C32} ]
        [/cover] */
    HwModulePtr->FRAMECON.B.MODE = LIN_17_ASCLIN_FRAMECON_INIT_MODE;

    /* Connect the Clock source */
    HwModulePtr->CSR.B.CLKSEL = LIN_17_ASCLIN_CSRREG_CLKSEL;

    /* Check status of Enabling of clock source */
    /* [cover parentID={C279E61E-A54E-4b60-BFE0-91D4225CDE44} ]
        [/cover] */
    ClkStatus = (Std_ReturnType)Lin_17_AscLin_lHwBitChangeCheck(
                  HwModulePtr, LIN_17_ASCLIN_ENABLE_FLAG);

  }

  if(ClkStatus == E_OK)
  {
    /* Disable the Clock source. */
    HwModulePtr->CSR.B.CLKSEL = LIN_17_ASCLIN_CSRREG_CLKSEL_NOCLK;

    /* Check status of disabling of clock source */
    /* [cover parentID={5D6A3E62-B379-4dd0-962C-D7D24B44BD79} ]
        [/cover] */
    ClkStatus = (Std_ReturnType)Lin_17_AscLin_lHwBitChangeCheck                \
                (HwModulePtr, LIN_17_ASCLIN_DISABLE_FLAG);
  }

  if(ClkStatus == E_OK)
  {
    /* Change to LIN mode */
    /* [cover parentID={528C5F6D-B261-436f-8D34-34BB2840A1DC} ]
        [/cover] */
    HwModulePtr->FRAMECON.B.MODE = LIN_17_ASCLIN_FRAMECONREG_LIN_MODE;

    /* Master / Slave mode - Applicable for 4.4.0 Mode only */
    #if (MCAL_AR_VERSION == MCAL_AR_440)
    if(ChanCfgPtr->Node == LIN_17_ASCLIN_SLAVE_NODE)
    {
      /* Lin mode is Slave Mode */
      /* [cover parentID={6D5D363D-940E-4b1d-B5D3-86E204C92F7D} ]
        [/cover] */
      HwModulePtr->LIN.CON.B.MS = LIN_17_ASCLIN_LINCON_SLAVE_ENABLE;

      /* LIN Break Timer */
      HwModulePtr->LIN.BTIMER.U = LIN_17_ASCLIN_LINBTIMER_SLAVE_BREAK_VAL;
      /* LEAD val i.e delay b/w end of break and start of Sync character */
      HwModulePtr->FRAMECON.B.IDLE = LIN_17_ASCLIN_FRAMECON_IDLE_SLAVE_VAL;
    }
    else
    #endif
    {
      /* Lin mode is Master Mode */
      HwModulePtr->LIN.CON.B.MS = LIN_17_ASCLIN_LINCON_MASTER_ENABLE;

      /* LIN Break Timer */
      HwModulePtr->LIN.BTIMER.U = LIN_17_ASCLIN_LINBTIMER_MASTER_BREAK_VAL;

      /* IDLE value i.e Interbyte space or response space */
      HwModulePtr->FRAMECON.B.IDLE = TimingCfg.InterByteResponseSpace;
    }

    /* LEAD val i.e delay b/w end of break and start of Sync character */
    HwModulePtr->FRAMECON.B.LEAD = LIN_17_ASCLIN_FRAMECONREG_LEAD_VAL;

    /* [cover parentID={F1058C0B-9867-4981-9F09-9C59A6A3827C}]
        [/cover] */
    /* Configure the Baudrate parameters */
    HwModulePtr->BRG.U = (((uint32)TimingCfg.HwBrgDenominator) |
                          ((uint32)TimingCfg.HwBrgNumerator << 16));
    HwModulePtr->BITCON.B.PRESCALER = TimingCfg.HwBitconPrescalar;
    HwModulePtr->BITCON.B.OVERSAMPLING = LIN_17_ASCLIN_BITCONREG_OS_VAL;

    /* Digital Glitch Filter = OFF */
    HwModulePtr->IOCR.B.DEPTH = LIN_17_ASCLIN_IOCRREG_DEPTH_VAL;

    /* Configure the Sample mode, Sample point, Parity, Collision detection */
    HwModulePtr->BITCON.B.SM = LIN_17_ASCLIN_BITCONREG_SM_VAL;
    HwModulePtr->BITCON.B.SAMPLEPOINT = LIN_17_ASCLIN_BITCON_SP_VAL;
    HwModulePtr->FRAMECON.B.PEN = LIN_17_ASCLIN_FRAMECONREG_PEN_VAL;
    HwModulePtr->FRAMECON.B.CEN = LIN_17_ASCLIN_FRAMECONREG_CEN_VAL;

    /* STOP bit = 1 */
    HwModulePtr->FRAMECON.B.STOP = LIN_17_ASCLIN_FRAMECONREG_STOP_VAL;


    /* Hw checksum enable, Checksum  injection to Rx FIFO disable */
    HwModulePtr->LIN.CON.B.CSEN = LIN_17_ASCLIN_LINCONREG_CSEN_VAL;

    /* Header Timeout = 48 bit times + Interbyte Space + Lead value */
    HeaderTimeOutVal =                                                         \
        ((uint8)LIN_17_ASCLIN_LINHTIMER_HEADER_VAL +                           \
         (TimingCfg.InterByteResponseSpace) +                            \
         (uint8)LIN_17_ASCLIN_FRAMECONREG_LEAD_VAL);

    HwModulePtr->LIN.HTIMER.B.HEADER = HeaderTimeOutVal;

    /* Configure the RX inlet, TX outlet width/s to 1 byte */
    /* [cover parentID={CF4574A7-B1B9-4dd2-9E14-B165D1120EF6}]
        [/cover] */
    HwModulePtr->TXFIFOCON.U = ((uint32)LIN_17_ASCLIN_TXFIFOCON_INW);
    HwModulePtr->RXFIFOCON.U = ((uint32)LIN_17_ASCLIN_RXFIFOCON_OUTW);

    HwModulePtr->IOCR.B.ALTI =  RxAlternatePinSelect;

    /* Connect the Clock source */
    HwModulePtr->CSR.B.CLKSEL = LIN_17_ASCLIN_CSRREG_CLKSEL;

    /* Check status of disabling of clock source */
    /* [cover parentID={5EC3C319-7016-4779-B606-9494EEC2DA8E}]
        [/cover] */
    ClkStatus = (Std_ReturnType)Lin_17_AscLin_lHwBitChangeCheck(
                  HwModulePtr, LIN_17_ASCLIN_ENABLE_FLAG);
  }

  return ClkStatus;
}

#if (LIN_17_ASCLIN_MASTER_CH_PRESENT == STD_ON)
/*******************************************************************************
** Traceability :[cover parentID={7E1A0CE6-F0B4-4422-AA04-23F7505E85B9}]      **                                     **
**                           [/cover]                                         **
** Traceability :                                                             **
** Syntax           : static void Lin_17_AscLin_lModeReInit                   **
**                      (                                                     **
**                          const Lin_17_AscLin_ChannelInfoType               **
**                                     *const ChannelStatePtr,                **
**                         const uint8 HwUnit                                 **
**                      )                                                     **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non reentrant                                           **
**                                                                            **
** Parameters (in)  : ChannelStatePtr :Pointer to the structure with internal **
**                                 LIN channel status and other information.  **
**                     HwUnit          : ASCLIN Hardware module no            **
**                                                                            **
**                                                                            **                                                                           **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Returns status of the re-initialization of              **
**                    operating mode of the ASCLIN hardware module.           **
**                    E_OK returned when MODE re-initialization is successful.**
**                    or if there is response and no Tx or Rx error is        **
**                    reported.                                               **
**                    E_NOT_OK returned when MODE re-initialization failed.   **                                                    **
**                                                                            **
** Description      : This function checks if there is no response or any Tx  **
**                    or Rx error is reported, the it re-initializes the      **
**                    operating mode of the module by switching first to the  **
**                    INIT mode and then to the LIN mode.                     **
** Note :           This function is applicable to only Master nodes          **
*******************************************************************************/
static Std_ReturnType Lin_17_AscLin_lModeReInit
(
  const Lin_17_AscLin_ChannelInfoType *const ChannelStatePtr,
  const uint8 HwUnit
)
{
  Ifx_ASCLIN *HwModulePtr;
  Std_ReturnType ClkStatus = E_NOT_OK;

  HwModulePtr = Lin_17_AscLin_kAscLinKernelRegAddr[HwUnit];

    /* If there is no response or any Tx or Rx error is reported */
    /* [cover parentID={AB829BA6-B774-4d31-A1D0-76AEFF6D7512} ]
    [/cover] */
    if((ChannelStatePtr->State == LIN_17_ASCLIN_MASTER_RX_NO_RESP_STATE_I) ||
       (ChannelStatePtr->State == LIN_17_ASCLIN_MASTER_RESP_RECEIVE_WAIT_STATE_I) ||
       (ChannelStatePtr->State == LIN_17_ASCLIN_MASTER_TX_ERROR_STATE_I) ||
       (ChannelStatePtr->State == LIN_17_ASCLIN_MASTER_RX_ERROR_STATE_I))
    {
      /* Disable the Clock source. */
      HwModulePtr->CSR.B.CLKSEL = LIN_17_ASCLIN_CSRREG_CLKSEL_NOCLK;

      /* Check status of disabling of clock source */
      ClkStatus = (Std_ReturnType)Lin_17_AscLin_lHwBitChangeCheck(
                    HwModulePtr, LIN_17_ASCLIN_DISABLE_FLAG);

     /* [cover parentID={9E153DB1-1A72-4119-A49B-16459299A200} ]
     [/cover] */
      if(ClkStatus == E_OK)
      {
        /* Change to INIT mode */

        HwModulePtr->FRAMECON.B.MODE = LIN_17_ASCLIN_FRAMECON_INIT_MODE;

        /* Connect the Clock source */
        HwModulePtr->CSR.B.CLKSEL = LIN_17_ASCLIN_CSRREG_CLKSEL;

        /* Check status of Enabling of clock source */
        ClkStatus = (Std_ReturnType)Lin_17_AscLin_lHwBitChangeCheck(
                      HwModulePtr, LIN_17_ASCLIN_ENABLE_FLAG);
      }

      /* [cover parentID={4FCF78A0-958B-4905-9CFE-0CF98BA97E61} ]
      [/cover] */
      if(ClkStatus == E_OK)
      {
        /* Disable the Clock source. */
        HwModulePtr->CSR.B.CLKSEL = LIN_17_ASCLIN_CSRREG_CLKSEL_NOCLK;

        /* Check status of disabling of clock source */
        ClkStatus = (Std_ReturnType)Lin_17_AscLin_lHwBitChangeCheck                \
                    (HwModulePtr, LIN_17_ASCLIN_DISABLE_FLAG);
      }

      /* [cover parentID={4F33C095-DCBD-4658-95D9-B8CA1F0CFC5E} ]
      [/cover] */
      if(ClkStatus == E_OK)
      {
        /* Change to LIN mode */
        HwModulePtr->FRAMECON.B.MODE = LIN_17_ASCLIN_FRAMECONREG_LIN_MODE;

        /* Connect the Clock source */
        HwModulePtr->CSR.B.CLKSEL = LIN_17_ASCLIN_CSRREG_CLKSEL;

        /* Check status of disabling of clock source */
        ClkStatus = (Std_ReturnType)Lin_17_AscLin_lHwBitChangeCheck(
                      HwModulePtr, LIN_17_ASCLIN_ENABLE_FLAG);
      }
    }
    else
    {
      ClkStatus = E_OK;
    }
  return ClkStatus;
}
#endif

#if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)
/*******************************************************************************
** Traceability :[cover parentID={7CD6E79A-EAF5-4e41-A5E7-5228D90D3C37}]      **
**                        [/cover]                                            **
** Syntax : static  Std_ReturnType Lin_17_AscLin_lInitDetCheck                **
**         (                                                                  **
**              const Lin_17_AscLin_ConfigType *Config,                       **
**              const uint8 CoreId                                            **
**         )                                                                  **
**                                                                            **
** Service ID:  None                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  non - reentrant                                               **
**                                                                            **
** Parameters (in) :  Config - Pointer to the config root.                    **
**                    CoreId - Core Number                                    **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns DET status, E_OK or E_NOT_OK                     **
**                                                                            **
** Description : This function checks all the DETs for Lin_17_AscLin_Init API.**
** Note :      This function is applicable to both Master and Slave nodes     **
*******************************************************************************/
static  Std_ReturnType Lin_17_AscLin_lInitDetCheck
(
  const Lin_17_AscLin_ConfigType *const Config,
  const uint8 CoreId
)
{
  Std_ReturnType ErrorStatus;
  #if (LIN_17_ASCLIN_MULTICORE_ERROR_DETECT == STD_ON)
  const Lin_17_AscLin_CoreConfigType *LinCorePtr;
  #endif
  Lin_17_AscLin_CoreInitStatusType CoreState;
  ErrorStatus = E_NOT_OK;
  /* Configuration pointer is null */
  /* [cover parentID={A390CE15-A292-4f72-A5E8-BD878E77E24D}]
    [/cover] */
  if (NULL_PTR == Config)
  {
    /* Report to  DET invalid input pointer */
    /* [cover parentID={69D78BF4-425F-4742-82C0-D2CF8D7EBA7B}]
      [/cover] */
    (void)Det_ReportError(
      LIN_17_ASCLIN_MODULE_ID,
      LIN_17_ASCLIN_INSTANCE_ID,
      LIN_17_ASCLIN_SID_INIT,
      LIN_17_ASCLIN_E_INVALID_POINTER
    );
  }

  #if (LIN_17_ASCLIN_MULTICORE_ERROR_DETECT == STD_ON)
  else if(NULL_PTR != Lin_17_AscLin_kConfigPtr)
  {
    /* [cover parentID={15763C38-51B7-49ec-9713-E3586B198380}]
       [/cover] */
    if(Lin_17_AscLin_kConfigPtr != Config)
    {
      /* Check if the config ptr is same across cores */
      /* [cover parentID={484CA8A8-31ED-4b01-A3D0-F2165F4625DD}]
       [/cover] */
      (void)Det_ReportError(
        LIN_17_ASCLIN_MODULE_ID,
        LIN_17_ASCLIN_INSTANCE_ID,
        LIN_17_ASCLIN_SID_INIT,
        LIN_17_ASCLIN_E_INVALID_POINTER
      );
    }
    else
    {
      ErrorStatus = E_OK;
    }
  }
  #endif

  else
  {
    ErrorStatus = E_OK;
  }

  if (ErrorStatus == E_OK)
  {
    #if (LIN_17_ASCLIN_MULTICORE_ERROR_DETECT == STD_ON)
    LinCorePtr = Config->CoreConfigPtr[CoreId];
    /* [cover parentID={A60DE256-ABA8-4893-A9D1-8A8CC22B1004}]
          If core address is not configured
          [/cover] */
    if(LinCorePtr == NULL_PTR)
    {
      (void)Det_ReportError(
        LIN_17_ASCLIN_MODULE_ID,
        LIN_17_ASCLIN_INSTANCE_ID,
        LIN_17_ASCLIN_SID_INIT,
        LIN_17_ASCLIN_E_CORE_NOT_CONFIGURED);/* End of report to DET */
      ErrorStatus = E_NOT_OK;
    }
    else
    #endif
    {
      /* Check for LIN module initialization */
      /* [cover parentID={C515FBC1-8135-4ef1-BDC6-E6896FB59CAC}]
        [/cover] */
      /* [cover parentID={EBFDA74D-9805-43ca-9BE9-8A50158DC544}]
        [/cover] */
      CoreState = *Lin_17_AscLin_kCoreStatus[CoreId]->CoreInitStatus;
      if (CoreState == LIN_17_ASCLIN_CORE_INITIALIZED)
      {
        /* Report to  DET module is already initialized*/
        /* [cover parentID={186A3BD5-58C3-4408-9A36-706468258B72}]
          [/cover]*/
        (void)Det_ReportError(
          LIN_17_ASCLIN_MODULE_ID,
          LIN_17_ASCLIN_INSTANCE_ID,
          LIN_17_ASCLIN_SID_INIT,
          LIN_17_ASCLIN_E_STATE_TRANSITION
        );

        ErrorStatus = E_NOT_OK;
      }
    }
  }
  return ErrorStatus;
}
#endif /*(LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)*/

/*******************************************************************************
** Traceability :[cover parentID={BFDAB12B-DC50-4853-8648-B1F3E36F7642}]      **
**                        [/cover]                                            **
** Syntax           : static void Lin_17_AscLin_lHwInitKernelReg              **
**                      (const uint8 HwUnit)                                  **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters (in)  : HwUnit   : ASCLIN Hardware module no                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : This function resets the Kernel                         **
** Note :      This function is applicable to both Master and Slave nodes     **
*******************************************************************************/
static Std_ReturnType Lin_17_AscLin_lHwInitKernelReg(const uint8 HwUnit)
{
  Std_ReturnType ReturnStatus = E_NOT_OK;
  uint32 WaitCount;
  Ifx_ASCLIN *HwModuleAddrPtr;
  uint32 InitialCount;
  uint32 TimeOutResolution;
  uint8 RstBitChk;
  uint32 MeasuredTicks;
  TimeOutResolution = Mcal_DelayTickResolution();
  WaitCount = ((uint32)LIN_17_ASCLIN_TIMEOUT_COUNT / TimeOutResolution);

  HwModuleAddrPtr = Lin_17_AscLin_kAscLinKernelRegAddr[HwUnit];

  /* [cover parentID={A194A83B-B657-42cf-99E2-B93652ACAB9E}]
    [/cover] */

  LIN_17_ASCLIN_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(                       \
      &HwModuleAddrPtr->KRST0.U, LIN_17_ASCLIN_ENABLE_FLAG);

  LIN_17_ASCLIN_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(                       \
      &HwModuleAddrPtr->KRST1.U, LIN_17_ASCLIN_ENABLE_FLAG);

  InitialCount = Mcal_DelayGetTick();
  do
  {
    MeasuredTicks =  Mcal_DelayGetTick() - InitialCount;
    RstBitChk = HwModuleAddrPtr->KRST0.B.RSTSTAT;
  } while((RstBitChk == LIN_17_ASCLIN_DISABLE_FLAG) &&                         \
          (WaitCount > MeasuredTicks));
  /* [cover parentID={157F3A23-AA5E-4e4a-933E-210623A6899F}]
    [/cover] */
  /* Check if Reset is successful */
  if (RstBitChk == LIN_17_ASCLIN_ENABLE_FLAG)
  {
    ReturnStatus = E_OK;

  }

  LIN_17_ASCLIN_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(                       \
      &HwModuleAddrPtr->KRSTCLR.U, LIN_17_ASCLIN_ENABLE_FLAG);

  return ReturnStatus;

}

#if (LIN_17_ASCLIN_MASTER_CH_PRESENT == STD_ON)
/*******************************************************************************
** Traceability :[cover parentID={55D558BF-1DDC-46ae-A340-41F9A18B272C}]      **
**                        [/cover]                                            **
** Syntax           : static void Lin_17_AscLin_lHwStartTransmission          **
**                      (const uint8 HwUnit,                                  **
**                       const uint8 Channel,const Lin_PduType *PduStatePtr)  **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters (in)  : HwUnit   : ASCLIN Hardware module no                    **
**                  : Channel : LIN Channel number                            **
**                  : PduStatePtr : Pointer to the Pdu Structure              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : This function configures the ASCLIN hardware for        **
**                    Frame transmission.                                     **
** Note :      This function is applicable to Master nodes only               **
*******************************************************************************/
static void Lin_17_AscLin_lHwStartTransmission
(
  const uint8 HwUnit,
  const uint8 Channel, const Lin_PduType *PduStatePtr
)
{
  uint8 CoreId;
  uint8 count;
  uint8 counter;
  uint8 ResponseTimeOutVal;
  Ifx_ASCLIN *HwModulePtr;
  uint32 LocalPid;
  Lin_17_AscLin_ChannelInfoType *ChannelStatePtr;
  /* Get core id which is executing currently */
  CoreId = (uint8)Mcal_GetCpuIndex();
  Lin_FrameResponseType LocalDrc;
  HwModulePtr = Lin_17_AscLin_kAscLinKernelRegAddr[HwUnit];
  ChannelStatePtr = &(Lin_17_AscLin_kCoreStatus[CoreId]->                      \
                      ChannelStatus[Channel]);
  /* Calculate the Response timeout value as per LIN2.1
     Response timeout = ((10 * (Datalength + 1) * 1.4))
                      = ((Datalength +1) * (14))
  */
  ResponseTimeOutVal = (uint8)((PduStatePtr->Dl + 1UL)                         \
                               * (LIN_17_ASCLIN_TOLERANCE_VALUE));

  /* Configure the data length, checksum , response timeout */
  HwModulePtr->DATCON.B.DATLEN = PduStatePtr->Dl - 1U ;
  /*[cover parentID={A72F1A67-E51D-4c28-972A-B5BC4B355289}]
      [/cover]*/
  HwModulePtr->DATCON.B.CSM = (uint8)PduStatePtr->Cs;
  HwModulePtr->DATCON.B.RESPONSE = (uint8)ResponseTimeOutVal;
  /* Response mode = Reponsetype */
  HwModulePtr->DATCON.B.RM = LIN_17_ASCLIN_ENABLE_FLAG;

  /*[cover parentID={2F471638-7EA8-4008-87A4-D7613885567E}]
      [/cover]*/
  /* Enable the appropriate interrupt Flags  */
  LocalDrc = PduStatePtr->Drc;

  /* Write ID to Tx Fifo.
    the Parity is masked out since the Hw generates the parity automatically */
  LocalPid = PduStatePtr->Pid ;
  LocalPid &= (Lin_FramePidType)LIN_17_ASCLIN_PID_MASK_WO_PARITY;
  HwModulePtr->TXDATA.U =  LocalPid;

  if (LIN_17_ASCLIN_MSR_MASTER_RESPONSE_I == LocalDrc)
  {
    /* [cover parentID={D291ED3D-C0F4-4eed-9BB1-848097D24AD2}]
        [/cover] */
    HwModulePtr->FLAGSENABLE.U = LIN_17_ASCLIN_MASTER_TX_HEADER_AND_RESPONSE;
    HwModulePtr->DATCON.B.HO = LIN_17_ASCLIN_DISABLE_FLAG;
    count = PduStatePtr->Dl;
    /* Write Data bytes to Tx fifo in case of Master to Slave */
    for (counter = (uint8)0U; counter < count; counter++)
    {

      HwModulePtr->TXDATA.U = ChannelStatePtr->ResponseBuffer[counter];
    }
  }
  else if (LIN_17_ASCLIN_MSR_SLAVE_RESPONSE_I == LocalDrc)
  {
    /* [cover parentID={FA3663B3-2A4B-4476-8BFC-63C29E0744BF}]
        [/cover] */
    HwModulePtr->FLAGSENABLE.U = LIN_17_ASCLIN_MASTER_TRANSMIT_HEADER_SLAVE_RESPONSE;
    HwModulePtr->RXFIFOCON.B.ENI = LIN_17_ASCLIN_ENABLE_FLAG;
    HwModulePtr->DATCON.B.HO = LIN_17_ASCLIN_DISABLE_FLAG;
    ChannelStatePtr->State = LIN_17_ASCLIN_MASTER_RESP_RECEIVE_WAIT_STATE_I;
  }
  else
  {
    ChannelStatePtr->State = LIN_17_ASCLIN_MASTER_IGNORE_RESPONSE_STATE_I;
    /* [cover parentID={E9B3584A-1AB6-4851-99AC-4CCC813862A9}]
        [/cover] */
    HwModulePtr->FLAGSENABLE.U = LIN_17_ASCLIN_MASTER_TRANSMIT_HEADER;
    HwModulePtr->DATCON.B.HO = LIN_17_ASCLIN_ENABLE_FLAG;

    /* ENI to be disabled if no response to be received */
    HwModulePtr->RXFIFOCON.B.ENI = LIN_17_ASCLIN_DISABLE_FLAG;
  }

  /* Enable the Header Transmission */
  /* [cover parentID={AC8BA49E-F628-487e-B04B-4F58F058F0E7}]
    [/cover] */
  HwModulePtr->FLAGSSET.B.THRQS = LIN_17_ASCLIN_ENABLE_FLAG ;

  /* Enable the Response transmission in case of Master to Slave  */
  /* [cover parentID={035C2F93-BFDE-4d9f-9D94-043E36286E57}]
  [/cover] */
  if (LIN_17_ASCLIN_MSR_MASTER_RESPONSE_I == LocalDrc)
  {
    HwModulePtr->FLAGSSET.B.TRRQS = LIN_17_ASCLIN_ENABLE_FLAG ;
    ChannelStatePtr->State = LIN_17_ASCLIN_MASTER_SEND_HDR_RESP_STATE_I;
  }

  /* Enable the Tx Outlet */
  /* [cover parentID={16F058DD-B1BA-47a2-8C4F-A810561E2BD2}]
    [/cover] */
  HwModulePtr->TXFIFOCON.B.ENO = LIN_17_ASCLIN_ENABLE_FLAG;
}

/*******************************************************************************
** Traceability :[cover parentID={BC9028A6-D3CF-48b1-93A6-25359079C9A0}]      **
**                           [/cover]                                         **
** Syntax           : static Lin_17_AscLin_InternalStatusType                 **
**                     Lin_17_AscLin_lGetIntErrorStatus_Master                **
**                     (const uint32 HwErrorFlags,const uint8 Channel)        **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : HwErrorFlags   : Hw error FLAGS as given by ASCLIN      **
**                  : Channel   : Logical Id of the channel                   **
** Parameters (out) : Lin_17_AscLin_InternalStatusType: Internal Status       **
**                                                                 information**
**                                                                            **
** Return value     : Internal status of the channel                          **
**                                                                            **
** Description      : This function returns the internal status information   **
**                   based on the asclin hw error flags register.             **
** Note :      This function is applicable to Master nodes only               **
*******************************************************************************/
static Lin_17_AscLin_InternalStatusType Lin_17_AscLin_lGetIntErrorStatus_Master
(
  const uint32 HwErrorFlags, const uint8 Channel
)
{
  Lin_17_AscLin_InternalStatusType Status = LIN_17_ASCLIN_MASTER_CH_INIT_STATE_I;
  uint8 HwUnit;
  uint8 CoreId;
  uint8 FifoValue;
  uint8 ChannelId = 0;
  const Ifx_ASCLIN *HwModulePtr;
  const Lin_17_AscLin_ChannelType *ChanCfgPtr;
  const Lin_17_AscLin_ChannelInfoType *ChannelStatePtr;

  /* Get core id which is executing currently */
  CoreId = (uint8)Mcal_GetCpuIndex();
  ChannelStatePtr = &(Lin_17_AscLin_kCoreStatus[CoreId]->                      \
                      ChannelStatus[Channel]);
  /*Extracting the physical channel ID*/
  ChannelId = Lin_17_AscLin_kConfigPtr->ChannelToCorePtr[Channel];
  ChanCfgPtr = &(Lin_17_AscLin_kConfigPtr->                                    \
                 CoreConfigPtr[CoreId]->ChannelConfigPtr[ChannelId]);
  /* Extract HwUnit */
  HwUnit = ChanCfgPtr->HwModule;
  HwModulePtr = Lin_17_AscLin_kAscLinKernelRegAddr[HwUnit];
  /* Read the RXFIFO FILL value from hw */
  FifoValue = HwModulePtr->RXFIFOCON.B.FILL;

  /* [cover parentID={E657398B-817D-450a-95C2-F9F87ED6A398}]
          [/cover] */
  if(ChannelStatePtr->State == LIN_17_ASCLIN_MASTER_RESP_RECEIVE_WAIT_STATE_I)
    /* Transmit Header, wait for slave response */
  {
    /*LIN_17_ASCLIN_MASTER_RECEIVE_RESPONSE_ERROR = FE | RT | CE | LC | BD | RFO | RFU */
    if((HwErrorFlags & (uint32)LIN_17_ASCLIN_MASTER_RECEIVE_RESPONSE_ERROR) != LIN_17_ASCLIN_DISABLE_FLAG)
    {
      /* Check for collision detection error flag */
      /* [cover parentID={B5C9019F-3614-4a11-B88C-DCC1A7453699}]
      [/cover] */
      if(((HwErrorFlags & ((uint32)LIN_17_ASCLIN_FLAGSREG_TH)) ==                            \
          LIN_17_ASCLIN_DISABLE_FLAG) && ((HwErrorFlags & (uint32)LIN_17_ASCLIN_CE_BIT) !=   \
                                          LIN_17_ASCLIN_DISABLE_FLAG))
      {
        Status = LIN_17_ASCLIN_MASTER_TX_HDR_ERROR_STATE_I;
      }
      /* Response timeout occurred but no response bytes received */
      /* [cover parentID={509A8EBF-89DB-46c5-BA8D-869C4E7F4C12}]
      [/cover] */
      else if(((HwErrorFlags & (uint32)LIN_17_ASCLIN_RT_BIT) !=                      \
          LIN_17_ASCLIN_DISABLE_FLAG) && (FifoValue == 1U))
      {
        Status = LIN_17_ASCLIN_MASTER_RX_NO_RESP_STATE_I;
      }
      else
      {
        /* Error in the response */
        /* [cover parentID={337D8EC9-A5DE-4666-BE0A-6561C3C9C54E}]
           [/cover] */
        Status = LIN_17_ASCLIN_MASTER_RX_ERROR_STATE_I;
      }
    }
  }
    /* [cover parentID={687CE175-1CAF-4828-8E00-E2F5DE0E3C0E}]
           [/cover] */
  else if(ChannelStatePtr->State == LIN_17_ASCLIN_MASTER_IGNORE_RESPONSE_STATE_I)
    /* Only header transmit */
  {
    /* LIN_17_ASCLIN_MASTER_TRANSMIT_HEADER_ERROR = CE |LP| HT */
    if((HwErrorFlags & (uint32)LIN_17_ASCLIN_MASTER_TRANSMIT_HEADER_ERROR) != LIN_17_ASCLIN_DISABLE_FLAG)
    {
      /* [cover parentID={D419CF2F-67E3-4461-B063-628539862733}]
             [/cover] */
      Status = LIN_17_ASCLIN_MASTER_TX_HDR_ERROR_STATE_I;
    }
  }
  /* [cover parentID={5A62BDFA-560C-49f7-B00F-E08948C12D11}]
           [/cover] */
  else if(ChannelStatePtr->State == LIN_17_ASCLIN_MASTER_SEND_HDR_RESP_STATE_I)
    /* Transmit Header, Response from Master */
    /* [cover parentID={B21CE53A-CBDB-46fb-BF73-111FD7C23028}]
      [/cover] */
  {
    if(((HwErrorFlags & ((uint32)LIN_17_ASCLIN_FLAGSREG_TH)) ==                \
        LIN_17_ASCLIN_DISABLE_FLAG) && ((HwErrorFlags & (uint32)LIN_17_ASCLIN_MASTER_TRANSMIT_HEADER_ERROR) !=
                                        LIN_17_ASCLIN_DISABLE_FLAG))
    {
      Status = LIN_17_ASCLIN_MASTER_TX_HDR_ERROR_STATE_I;
    }
    else if(((HwErrorFlags & ((uint32)LIN_17_ASCLIN_FLAGSREG_TH)) !=           \
             LIN_17_ASCLIN_DISABLE_FLAG) && ((HwErrorFlags & (uint32)LIN_17_ASCLIN_MASTER_RESPONSE_TRANSMIT_ERROR) !=
                 LIN_17_ASCLIN_DISABLE_FLAG))
    {
      /* [cover parentID={B73CBBD5-9BCC-4826-99D5-E849A90BEEDF}]
        [/cover] */
      Status = LIN_17_ASCLIN_MASTER_TX_ERROR_STATE_I;
    }
    else
    {
      /* Status will be returned as LIN_17_ASCLIN_MASTER_CH_INIT_STATE_I */
    }
  }
  else
  {
    /* Status will be returned as LIN_17_ASCLIN_MASTER_CH_INIT_STATE_I */
  }
  return Status;
}
#endif
#if ((MCAL_AR_VERSION == MCAL_AR_440)&& (LIN_17_ASCLIN_SLAVE_CH_PRESENT == STD_ON))
/*******************************************************************************
** Traceability :[cover parentID={A96902C7-4870-4f7a-9820-33C9D1AC5CF5}]      **
**                           [/cover]                                         **
** Syntax           : static void Lin_17_AscLin_lReportSlaveError             **
**                    (const uint32 HwErrorFlags,const uint8 Channel)         **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : HwErrorFlags   : Hw error FLAGS as given by ASCLIN      **
**                  : Channel   : Logical Id of the channel                   **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : This function returns the internal status information   **
**                   based on the asclin hw error flags register.             **
** Note :      This function is applicable to Slave nodes only                **
*******************************************************************************/
static void Lin_17_AscLin_lReportSlaveError
(
  const uint32 HwErrorFlags, const uint8 Channel
)
{
  uint8 HwUnit;
  uint8 CoreId;
  uint8 FifoValue;
  uint8 ChannelId = 0;
  const Ifx_ASCLIN *HwModulePtr;
  const Lin_17_AscLin_ChannelType *ChanCfgPtr;
  const Lin_17_AscLin_ChannelInfoType *ChannelStatePtr;

  /* Get core id which is executing currently */
  CoreId = (uint8)Mcal_GetCpuIndex();
  /*Extracting the physical channel ID*/
  ChannelId = Lin_17_AscLin_kConfigPtr->ChannelToCorePtr[Channel];
  ChannelStatePtr = &(Lin_17_AscLin_kCoreStatus[CoreId]->                      \
                      ChannelStatus[ChannelId]);

  ChanCfgPtr = &(Lin_17_AscLin_kConfigPtr->                                    \
                 CoreConfigPtr[CoreId]->ChannelConfigPtr[ChannelId]);
  /* Extract HwUnit */
  HwUnit = ChanCfgPtr->HwModule;
  HwModulePtr = Lin_17_AscLin_kAscLinKernelRegAddr[HwUnit];
  /* Read the RXFIFO FILL value from hw */
  FifoValue = HwModulePtr->RXFIFOCON.B.FILL;

  if((ChannelStatePtr->State == LIN_17_ASCLIN_SLAVE_HDR_WAIT_STATE_I) &&   \
  ((HwErrorFlags & (uint32)LIN_17_ASCLIN_SLAVE_RECEIVER_HEADER_ERRORS) !=   \
                                                LIN_17_ASCLIN_DISABLE_FLAG))
  {
      /* [cover parentID={6D7A6DBD-BCEB-4bdb-9209-62F692C486D2}]
      [/cover] */
      LinIf_LinErrorIndication(Channel, LIN_ERR_HEADER);
  }
  else if((ChannelStatePtr->State == LIN_17_ASCLIN_SLAVE_RX_RESP_WAIT_STATE_I) \
      && ((HwErrorFlags & (uint32) LIN_17_ASCLIN_SLAVE_RECEIVE_RESPONSE_ERRORS)\
                                                != LIN_17_ASCLIN_DISABLE_FLAG))
  {
    /* [cover parentID={2A910488-3081-4f97-8C2E-714FF649F8AB}]
           [/cover] */
      if((HwErrorFlags & LIN_17_ASCLIN_FE_FLAG_BIT) !=                         \
          LIN_17_ASCLIN_DISABLE_FLAG)
      {
         /* [cover parentID={56EB0609-94FE-4ea1-8642-9C7C2E93CF4A}]
         [/cover] */
         LinIf_LinErrorIndication(Channel, LIN_ERR_RESP_STOPBIT);
      }
      else if((HwErrorFlags & LIN_17_ASCLIN_LC_FLAG_BIT) !=                    \
              LIN_17_ASCLIN_DISABLE_FLAG)
      {
        /* [cover parentID={C1EFBBF1-B510-4100-88A7-6518612A314D}]
           [/cover] */
        LinIf_LinErrorIndication(Channel, LIN_ERR_RESP_CHKSUM);
      }
      else
      {
        /* [cover parentID={53A6A84E-4936-4d11-8852-85562B393D42}]
           [/cover] */
        if(FifoValue == 0U)
        {
          /* [cover parentID={41E6B2F1-5CDB-44a6-A13C-25636E804CFA}]
           [/cover] */
          LinIf_LinErrorIndication(Channel, LIN_ERR_NO_RESP);
        }
        else
        {
          /* [cover parentID={4CD14FE7-AC57-4f24-83C7-6524CD8B4153}]
           [/cover] */
          LinIf_LinErrorIndication(Channel, LIN_ERR_INC_RESP);
        }
      }
  }
  else
  {
    if((HwErrorFlags & (uint32)                                                \
        LIN_17_ASCLIN_SLAVE_TRANSMIT_RESPONSE_ERRORS) !=                       \
        LIN_17_ASCLIN_DISABLE_FLAG)
    {
      /* [cover parentID={5C6678D5-4FA0-4873-ADA7-84DD13A068BE}]
      [/cover] */
      LinIf_LinErrorIndication(Channel, LIN_ERR_RESP_DATABIT);
    }
  }
}
#endif
/*******************************************************************************
** Traceability :[cover parentID={B0B79DAA-543F-46b0-B614-AD8FEB018804}]      **
**                        [/cover]                                            **
** Syntax           : static void Lin_17_AscLin_lHwSendWakeupPulse            **
**                    (                                                       **
                        const uint8 HwUnit                                    **
                      )                                                       **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : HwUnit   : ASCLIN Hardware module no                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : This function sends the wakeup pulse with the           **
**                    time duration given by wakeup val                       **
** Note :      This function is applicable to both Master and Slave nodes     **
*******************************************************************************/
static void Lin_17_AscLin_lHwSendWakeupPulse(const uint8 HwUnit)
{
  Ifx_ASCLIN *HwModulePtr;
  HwModulePtr = Lin_17_AscLin_kAscLinKernelRegAddr[HwUnit];

  /* update the Wakeup pulse time duration in TX data  */
  /* [cover parentID={BAADBD24-5761-45b2-A5EA-059850AD3D03}]
      [/cover] */
  HwModulePtr->TXDATA.U = LIN_17_ASCLIN_WAKEUP_VALUE;

  /* Enable Tx Fifo outlet */
  HwModulePtr->TXFIFOCON.B.ENO = LIN_17_ASCLIN_ENABLE_FLAG;

  /* Set the Transmit wakeup pulse request bit */
  /* [cover parentID={3A996364-9681-4f0d-9E12-3FC8E80EB69F}]
      [/cover] */
  HwModulePtr->FLAGSSET.B.TWRQS = LIN_17_ASCLIN_ENABLE_FLAG;
}

#if(LIN_17_ASCLIN_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Traceability :[cover parentID={A14F0239-0C17-4d5a-B301-BA104A995C98}]      **
**                  [/cover]                                                  **
** Syntax           : void  Lin_17_AscLin_GetVersionInfo                      **
**                    (                                                       **
**                      Std_VersionInfoType *const VersionInfo                **
**                    )                                                       **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x01                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : none                                                    **
**                                                                            **
** Parameters (out) : versioninfo - Pointer to where to store the             **
**                    version information of this module.                     **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : This function:                                          **
**   - This function returns the version information of the module            **
** Note :      This API is applicable to both Master and Slave nodes          **
*******************************************************************************/
/* [cover parentID={0D572F1F-4815-4464-808C-FB9B006910CB}]
      [/cover] */
void  Lin_17_AscLin_GetVersionInfo(Std_VersionInfoType *const versioninfo)
{

  /* [cover parentID={27EC1E8E-92F2-472b-8C7D-A886EDFF43F1}]
      [/cover] */
  #if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={DD0A7898-E567-41b5-BB0B-8E1B89658C39}]
      [/cover] */
  /* [cover parentID={EA08717D-94D1-48d2-B346-386F24C5E1DD}]
      [/cover] */
  if((versioninfo) == (NULL_PTR))
  {
    /* [cover parentID={FC42A679-4D41-4c70-9D91-9BBADDBC161C}]
        [/cover] */
    (void)Det_ReportError(
      LIN_17_ASCLIN_MODULE_ID,
      LIN_17_ASCLIN_INSTANCE_ID,
      LIN_17_ASCLIN_SID_VERSIONINFO,
      LIN_17_ASCLIN_E_PARAM_POINTER
    );
  }
  else
  #endif
  {
    /* [cover parentID={CE29FE32-AB25-4b86-973E-B69964451527}]
         [/cover] */
    /* LIN vendor ID */
    ((Std_VersionInfoType*)(versioninfo))->moduleID = LIN_17_ASCLIN_MODULE_ID;
    /* LIN vendor ID */
    ((Std_VersionInfoType*)(versioninfo))->vendorID = LIN_17_ASCLIN_VENDOR_ID;
    /* Major version of LIN */
    ((Std_VersionInfoType*)(versioninfo))->sw_major_version =
      (uint8)LIN_17_ASCLIN_SW_MAJOR_VERSION;
    /* Minor version of LIN */
    ((Std_VersionInfoType*)(versioninfo))->sw_minor_version =
      (uint8)LIN_17_ASCLIN_SW_MINOR_VERSION;
    /* Patch version of LIN */
    ((Std_VersionInfoType*)(versioninfo))->sw_patch_version =
      (uint8)LIN_17_ASCLIN_SW_PATCH_VERSION;
  }
}
#endif

/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
    [/cover] */
/*[cover parentID={9ABB6AE4-2142-4ac8-B499-48AE1C3A908C}]
Code Memory section executable by all cores
[/cover]*/
#define LIN_17_ASCLIN_STOP_SEC_CODE_QM_GLOBAL
/*mapping of code and data to specific memory sections via memory mapping file*/
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safegaurd.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"
