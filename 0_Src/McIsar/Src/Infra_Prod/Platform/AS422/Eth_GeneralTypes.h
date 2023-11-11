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
**  FILENAME     : Eth_GeneralTypes.h                                         **
**                                                                            **
**  VERSION      : 8.0.0                                                      **
**                                                                            **
**  DATE         : 2020-10-13                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Type Definition for ETH module                             **
**                                                                            **
**  SPECIFICATION(S) : AUTOSAR_SWS_EthernetDriver.pdf, AUTOSAR Release 4.2.2  **
**                                                                            **
**  MAY BE CHANGED BY USER : Yes                                              **
**                                                                            **
*******************************************************************************/
/* [cover parentID={02E963B3-0809-4549-A097-7621EFA30E8E}]
[/cover] */
#ifndef ETH_GENERALTYPES_H
#define ETH_GENERALTYPES_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Include Communication Stack Types */
#include "ComStack_Types.h"

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/* [cover parentID={E5F983BE-07BC-491a-88EC-2769CF667C1D}] */
typedef uint16 Eth_FrameType;
/* [/cover] */

/* [cover parentID={BD6101D5-1685-4c46-BB5D-40A2C68F6E12}] */
typedef uint8 Eth_DataType;
/* [/cover] */

/* [cover parentID={9B3DB455-B3B5-47c1-938F-DB195AED1CF8}] */
typedef enum
{
  ETH_MODE_DOWN   = 0x0U,
  ETH_MODE_ACTIVE = 0x1U
}Eth_ModeType;
/* [/cover] */

/* [cover parentID={BDAFE9DD-1BE4-4a80-8155-304968BD7C19}] */
typedef enum
{
  ETH_RECEIVED = 0x0U,
  ETH_NOT_RECEIVED,
  ETH_RECEIVED_MORE_DATA_AVAILABLE
} Eth_RxStatusType;
/* [/cover] */

/* [cover parentID={EBEF3D7C-B522-4bab-9C9C-49DD0A07DA4F}] */
typedef enum
{
  ETH_ADD_TO_FILTER = 0x0U,
  ETH_REMOVE_FROM_FILTER
} Eth_FilterActionType;
/* [/cover] */

/* [cover parentID={31610027-C922-48ba-A512-90E0F5996F6F}] */
typedef enum
{
  ETH_OK=0x0U,
  ETH_E_NOT_OK,
  ETH_E_NO_ACCESS
}Eth_ReturnType;
/*[/cover] */

/* [cover parentID={06942102-DFC0-443c-944A-4794B2962603}] */
typedef enum
{
  ETH_VALID = 0x0U,
  ETH_INVALID,
  ETH_UNCERTAIN
}Eth_TimeStampQualType;
/* [/cover] */

/* [cover parentID={F8A4A4C4-F873-4d21-A834-B1716374B502}] */
typedef struct
{
  uint32 nanoseconds;
  uint32 seconds;
  uint16 secondsHi;
}Eth_TimeStampType;
/* [/cover] */

/* [cover parentID={6FC1C2B8-4DC8-4acf-973D-81544DF0582F}] */
typedef struct
{
  Eth_TimeStampType diff;
  boolean sign;
}Eth_TimeIntDiffType;
/* [/cover] */

/* [cover parentID={E6EDFDCC-2FB2-495d-824D-A47DE34AAC19}] */
typedef struct
{
  Eth_TimeIntDiffType IngressTimeStampDelta ;
  Eth_TimeIntDiffType OriginTimeStampDelta ;
}Eth_RateRatioType;
/* [/cover] */

/* [cover parentID={137DCFF3-A8F0-4a14-99D6-A83E7975A0EA}] */
typedef uint32 Eth_BufIdxType;
/* [/cover] */

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/

/*******************************************************************************
**                            LOW Level Driver Definitions                    **
*******************************************************************************/

#endif /* ETH_GENERALTYPES_H */

