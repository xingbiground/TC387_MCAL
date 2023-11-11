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
**  FILENAME     : ComStack_Cfg.h                                             **
**                                                                            **
**  VERSION      : 3.0.0                                                      **
**                                                                            **
**  DATE         : 2020-05-05                                                 **
**                                                                            **
**  VARIANT      : NA                                                         **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY :                                                            **
**                                                                            **
**  DESCRIPTION  : Configuration header file for Com Stack                    **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : AUTOSAR_SWS_CommunicationStackTypes.pdf, AUTOSAR       **
**                     Release 4.2.2 and 4.4.0                                **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
#ifndef COMSTACK_CFG_H
#define COMSTACK_CFG_H

/*****************************************************************************
**                      Include Section                                     **
*****************************************************************************/

/*****************************************************************************
**                      Global Symbols                                      **
*****************************************************************************/

/*****************************************************************************
**                      Global Data Types (ECU dependent)                   **
*****************************************************************************/

typedef uint8        PduIdType;     /* Type of PDU ID.
                                    Allowed ranges: uint8 .. uint16 */

typedef uint16       PduLengthType; /* Type of PDU Length.
                                    Allowed ranges: uint8 .. uint32 */

#endif
