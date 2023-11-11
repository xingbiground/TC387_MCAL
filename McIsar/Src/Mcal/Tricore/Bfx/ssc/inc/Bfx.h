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
**  FILENAME     : Bfx.h                                                      **
**                                                                            **
**  VERSION      : 10.0.0                                                     **
**                                                                            **
**  DATE         : 2021-02-23                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID={AD206E98-A5A4-4617-AB6E-A1AA45B02DBE}]    **
**                                                                            **
**  DESCRIPTION  : BFX library header definition file                         **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of BFX library,                          **
**                     AUTOSAR Release 4.2.2  and 4.4.0                       **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#ifndef BFX_H
#define BFX_H


/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*[cover parentID={DC0B4213-1D31-4256-BAD3-DC0CD7F025C4}]
File Structure
[/cover]*/

/*[cover parentID={43E56F75-50B4-4b3f-8C6C-13912D06E525}]*/
/*AUTOSAR data types are used instead of native C data types*/
#include "Bfx_Local.h"
/*[/cover] */

/* [cover parentID={2315CEFB-5155-410c-AA89-F72E519F9FBE}]
No configuration options. Hence no configuration file is included.
[/cover] */

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/* [cover parentID={0CC029AF-BE1F-439f-BA30-B61F1DF79884}]
Published information
[/cover] */

/* [cover parentID={54218CEC-C551-425b-B6CA-866ECF627E37}] */
/* Vendor ID and Module ID */
/* BFX Vendor ID - Vendor ID of the dedicated implementation of BFX
module according to the AUTOSAR vendor list */
#define BFX_VENDOR_ID                   (17U)

/*BFX Module ID - Module ID of BFX module from Module List */
#define BFX_MODULE_ID                   (205U)
/* [/cover] */

/* [cover parentID={C4D0F741-16CE-494c-B9FB-95C39C94BA13}] */
/* AUTOSAR version */
/* The BFX library is developed as per the AUTOSAR v4.2.2 and v4.4.0.*/
/* [/cover] */

/*[cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}] Autosar variant management */

/* BFX SW Major Version - Major version number of the vendor specific
implementation of BFX module */
#define BFX_SW_MAJOR_VERSION            (20U)
/* BFX SW Minor Version - Minor version number of the vendor specific
implementation of BFX module */
#define BFX_SW_MINOR_VERSION            (0U)
/* BFX SW Patch Version - Patch level version number of the vendor specific
implementation of BFX module */
#define BFX_SW_PATCH_VERSION            (1U)


/* Holds the all '1' status */
#define BFX_DEFAULT_STATUS_1_EIGHT_BITS      ((uint8)0xFFU)
#define BFX_DEFAULT_STATUS_1_SIXTEEN_BITS    ((uint16)0xFFFFU)
#define BFX_DEFAULT_STATUS_1_THIRTYTWO_BITS  ((uint32)0xFFFFFFFFU)
#define BFX_DEFAULT_STATUS_1_SIXTYFOUR_BITS  ((uint64)0xFFFFFFFFFFFFFFFFU)

/* Holds the all '0' status */
#define BFX_DEFAULT_STATUS_0_EIGHT_BITS      ((uint8)0x00)
#define BFX_DEFAULT_STATUS_0_SIXTEEN_BITS    ((uint16)0x0000)
#define BFX_DEFAULT_STATUS_0_THIRTYTWO_BITS  ((uint32)0x00000000)
#define BFX_DEFAULT_STATUS_0_SIXTYFOUR_BITS  ((uint64)0x0000000000000000)


/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*[cover parentID={826C08F0-0107-42bf-9DCC-FABBFE7F9A19}]
Code Memory section executable by all cores
[/cover]*/
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
Memory mapping support
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
Code Memory section naming as per AS
[/cover]*/
#define BFX_START_SEC_CODE_ASIL_B_GLOBAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*[cover parentID={6D3BA711-CAAB-4a34-82CC-822B613FCB90}]
MemMap_h file to be developed by user
[/cover]*/
#include "Bfx_MemMap.h"
/*******************************************************************************
**                    Global INLINE Function Definitions                      **
*******************************************************************************/

/*
Global INLINE functions are not defined under any Memory section here.
They will lie in Code Memory section of User Application wherever called.
Code Memory section naming shall be as per AS.
*/


/*******************************************************************************
** Traceability      : [cover parentID={370DF4C4-2D74-4d77-9359-3AB8F40DD41A},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_SetBit_u8u8                                   **
**                     (                                                      **
**                       uint8 * const Data,                                  **
**                       const uint8 BitPn                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_SetBit_u8u8 function sets the logical status   **
**                     of the bit at BitPn bit position of the Data parameter **
**                     to 1.                                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x01                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitPn - Bit position (Valid range: 0 to 7)             **
**                                                                            **
** Parameters(in-out): Data  - Pointer to data which is to be modified        **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_SetBit_u8u8(uint8* const Data, const uint8 BitPn)
{
  /* [cover parentID={18069F15-3A0A-480f-A3B8-EA7774F28322}]
  Set bit at specified position
  [/cover] */
  Bfx_lInsert8Bits(Data, BFX_DEFAULT_STATUS_1_EIGHT_BITS, BitPn, \
                   BFX_DEFAULT_WIDTH);
}


/*******************************************************************************
** Traceability      : [cover parentID={DB38E919-375E-4d9d-A7E4-F73B323DD421},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_SetBit_u16u8                                  **
**                     (                                                      **
**                       uint16* const Data,                                  **
**                       const uint8 BitPn                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_SetBit_u16u8 function sets the logical status  **
**                     of the bit at BitPn bit position of the Data parameter **
**                     to 1.                                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x02                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitPn - Bit position (Valid range: 0 to 15)            **
**                                                                            **
** Parameters(in-out): Data  - Pointer to data which is to be modified        **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_SetBit_u16u8(uint16* const Data, const uint8 BitPn)
{
  /* [cover parentID={B54F8846-CE7D-4faf-B051-E6587D418872}]
  Set bit at specified position
  [/cover] */
  Bfx_lInsert16Bits(Data, BFX_DEFAULT_STATUS_1_SIXTEEN_BITS, BitPn, \
                    BFX_DEFAULT_WIDTH);
}

/*******************************************************************************
** Traceability      : [cover parentID={8D467B3D-18D9-4264-ACC4-CCF2BD1128B5},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_SetBit_u32u8                                  **
**                     (                                                      **
**                       uint32* const Data,                                  **
**                       const uint8 BitPn                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_SetBit_u32u8 function sets the logical status  **
**                     of the bit at BitPn bit position of the Data parameter **
**                     to 1.                                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x03                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitPn - Bit position (Valid range: 0 to 31)            **
**                                                                            **
** Parameters(in-out): Data  - Pointer to data which is to be modified        **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_SetBit_u32u8(uint32* const Data, const uint8 BitPn)
{
  /* [cover parentID={626FF1A4-52E3-4751-94D2-26F442EBDECA}]
  Set bit at specified position
  [/cover] */
  Bfx_lInsert32Bits(Data, BFX_DEFAULT_STATUS_1_THIRTYTWO_BITS, BitPn, \
                    BFX_DEFAULT_WIDTH);
}

/*******************************************************************************
** Traceability      : [cover parentID={584D1788-89DB-436e-9E3C-3A2BD2AE3A28},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_SetBit_u64u8                                  **
**                     (                                                      **
**                       uint64* const Data,                                  **
**                       const uint8 BitPn                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_SetBit_u64u8 function sets the logical status  **
**                     of the bit at BitPn bit position of the Data parameter **
**                     to 1.                                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x04                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitPn - Bit position (Valid range: 0 to 63)            **
**                                                                            **
** Parameters(in-out): Data  - Pointer to data which is to be modified        **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_SetBit_u64u8(uint64* const Data, const uint8 BitPn)
{
/* [cover parentID={12C125E7-5E35-4709-9150-C808BF903886}]
Set bit at specified position
[/cover] */
  Bfx_lInsert64Bits(Data, BFX_DEFAULT_STATUS_1_SIXTYFOUR_BITS, BitPn, \
                    BFX_DEFAULT_WIDTH);
}

/*******************************************************************************
** Traceability      : [cover parentID={EBADC8C7-DC4F-4204-B934-5A5E40D6D6CC},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ClrBit_u8u8                                   **
**                     (                                                      **
**                       uint8* const Data,                                   **
**                       const uint8 BitPn                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ClrBit_u8u8 function clears the logical status **
**                     of the bit at BitPn bit position of the Data parameter **
**                     to 0.                                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x06                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitPn - Bit position (Valid range: 0 to 7)             **
**                                                                            **
** Parameters(in-out): Data  - Pointer to data which is to be modified        **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ClrBit_u8u8(uint8* const Data, const uint8 BitPn)
{
  /* [cover parentID={4CD7E2E2-8845-4626-9B96-3BF100BAB684}]
  Clear bit at specified position
  [/cover] */
  Bfx_lInsert8Bits(Data, BFX_DEFAULT_STATUS_0_EIGHT_BITS, BitPn, \
                   BFX_DEFAULT_WIDTH);
}

/*******************************************************************************
** Traceability      : [cover parentID={DBD5C4F1-86CF-4d79-AB4A-70C83D46EBFC},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ClrBit_u16u8                                  **
**                     (                                                      **
**                       uint16* const Data,                                  **
**                       const uint8 BitPn                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ClrBit_u16u8 function clears the logical status**
**                     of the bit at BitPn bit position of the Data parameter **
**                     to 0.                                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x07                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitPn - Bit position (Valid range: 0 to 15)            **
**                                                                            **
** Parameters(in-out): Data  - Pointer to data which is to be modified        **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ClrBit_u16u8(uint16* const Data, const uint8 BitPn)
{
  /* [cover parentID={6C16625C-31DD-4163-B0FB-4FD8C120C37E}]
  Clear bit at specified position
  [/cover] */
  Bfx_lInsert16Bits(Data, BFX_DEFAULT_STATUS_0_SIXTEEN_BITS, BitPn, \
                    BFX_DEFAULT_WIDTH);
}

/*******************************************************************************
** Traceability      : [cover parentID={62A763AC-9D14-4c80-ABF0-B704131AAB58},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ClrBit_u32u8                                  **
**                     (                                                      **
**                       uint32* const Data,                                  **
**                       const uint8 BitPn                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ClrBit_u32u8 function clears the logical status**
**                     of the bit at BitPn bit position of the Data parameter **
**                     to 0.                                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x08                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitPn - Bit position (Valid range: 0 to 31)            **
**                                                                            **
** Parameters(in-out): Data  - Pointer to data which is to be modified        **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ClrBit_u32u8(uint32* const Data, const uint8 BitPn)
{
  /* [cover parentID={5F83395B-D398-4f2b-9F44-5EC5FD6D42C4}]
  Clear bit at specified position
  [/cover] */
  Bfx_lInsert32Bits(Data, BFX_DEFAULT_STATUS_0_THIRTYTWO_BITS, BitPn, \
                    BFX_DEFAULT_WIDTH);
}

/*******************************************************************************
** Traceability      : [cover parentID={B7DCE3C8-77DB-4302-9F85-BDC0648E35AC},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ClrBit_u64u8                                  **
**                     (                                                      **
**                       uint64* const Data,                                  **
**                       const uint8 BitPn                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ClrBit_u32u8 function clears the logical status**
**                     of the bit at BitPn bit position of the Data parameter **
**                     to 0.                                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x09                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitPn - Bit position (Valid range: 0 to 63)            **
**                                                                            **
** Parameters(in-out): Data  - Pointer to data which is to be modified        **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ClrBit_u64u8(uint64* const Data, const uint8 BitPn)
{
/* [cover parentID={824A15B7-D11B-4a72-BA8E-38BDC8F0EC9C}]
Clear bit at specified position
[/cover] */
  Bfx_lInsert64Bits(Data, BFX_DEFAULT_STATUS_0_SIXTYFOUR_BITS,\
                   BitPn,BFX_DEFAULT_WIDTH);
}

/*******************************************************************************
** Traceability      : [cover parentID={71315A63-0AF7-4eda-805A-490B11311EC1},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : boolean Bfx_GetBit_u8u8_u8                             **
**                     (                                                      **
**                       const uint8 Data,                                    **
**                       const uint8 BitPn                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_GetBit_u8u8_u8 function returns TRUE when the  **
**                     logical status of the bit at BitPn bit position of the **
**                     Data input parameter is 1, otherwise the function      **
**                     returns FALSE.                                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x0A                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Data  - Input data                                     **
**                     BitPn - Bit position (Valid range: 0 to 7)             **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : boolean - Bit status                                   **
**                               TRUE  :Extracted bit is 1                    **
**                               FALSE :Extracted bit is 0                    **
*******************************************************************************/
static INLINE boolean Bfx_GetBit_u8u8_u8(const uint8 Data, const uint8 BitPn)
{
  boolean ResultValue;

  /* [cover parentID={5CA198FA-AFA9-4a19-B430-1AAE37B749ED}]
  Extract bit from specified position
  [/cover] */
  /* [cover parentID={6195BF51-0FE4-44a7-ACC2-DFF532F3D80A}]
  Is the extracted bit non zero?
  [/cover] */
  if (Bfx_lExtractBits((uint32)Data, BitPn, BFX_DEFAULT_WIDTH) != (uint32)0U)
  {
    /* [cover parentID={A27EAB3F-4A72-47f7-8BDC-ABBE454F6602}]
    Return result as TRUE
    [/cover] */
    ResultValue = (boolean)TRUE;
  }
  else
  {
    /* [cover parentID={A9B5261F-8CFB-4dd8-B86A-812C467C4FEF}]
    Return result as FALSE
    [/cover] */
    ResultValue = (boolean)FALSE;
  }

  return ResultValue;
}
/*******************************************************************************
** Traceability      : [cover parentID={4956B919-A293-408c-ADF9-616E751F9445},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : boolean Bfx_GetBit_u16u8_u8                            **
**                     (                                                      **
**                       const uint16 Data,                                   **
**                       const uint8 BitPn                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_GetBit_u16u8_u8 function returns TRUE when the **
**                     logical status of the bit at BitPn bit position of the **
**                     Data input parameter is 1, otherwise the function      **
**                     returns FALSE.                                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x0B                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Data  - Input data                                     **
**                     BitPn - Bit position (Valid range: 0 to 15)            **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : boolean - Bit status                                   **
**                               TRUE  :Extracted bit is 1                    **
**                               FALSE :Extracted bit is 0                    **
*******************************************************************************/
static INLINE boolean Bfx_GetBit_u16u8_u8(const uint16 Data, const uint8 BitPn)
{
  boolean ResultValue;

  /* [cover parentID={1ACB5F5E-8286-447b-98B6-D6D054B0D74E}]
  Extract bit from specified position
  [/cover] */
  /* [cover parentID={4C4332B7-767A-4a55-9C75-EABD6613E4B0}]
  Is the extracted bit non zero?
  [/cover] */
  if (Bfx_lExtractBits((uint32)Data, BitPn, BFX_DEFAULT_WIDTH) != (uint32)0U)
  {
    /* [cover parentID={729341D0-2C6A-4193-A56B-1C8FAE055B24}]
    Return result as TRUE
    [/cover] */
    ResultValue = (boolean)TRUE;
  }
  else
  {
    /* [cover parentID={645088C6-C793-4dfb-A482-401D54035194}]
    Return result as FALSE
    [/cover] */
    ResultValue = (boolean)FALSE;
  }

  return ResultValue;
}

/*******************************************************************************
** Traceability      : [cover parentID={50CFB84B-B110-4ea3-BABB-A562C79F2466},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : boolean Bfx_GetBit_u32u8_u8                            **
**                     (                                                      **
**                       const uint32 Data,                                   **
**                       const uint8 BitPn                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_GetBit_u32u8_u8 function returns TRUE when the **
**                     logical status of the bit at BitPn bit position of the **
**                     Data input parameter is 1, otherwise the function      **
**                     returns FALSE.                                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x0C                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Data  - Input data                                     **
**                     BitPn - Bit position (Valid range: 0 to 31)            **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : boolean - Bit status                                   **
**                               TRUE  :Extracted bit is 1                    **
**                               FALSE :Extracted bit is 0                    **
*******************************************************************************/
static INLINE boolean Bfx_GetBit_u32u8_u8(const uint32 Data, const uint8 BitPn)
{
  boolean ResultValue;

  /* [cover parentID={E401CCF3-055A-497e-9AE8-B574C2AF62CA}]
  Extract bit from specified position
  [/cover] */
  /* [cover parentID={884D5F95-47A1-4a95-9AFE-55F500634635}]
  Is the extracted bit non zero?
  [/cover] */
  if (Bfx_lExtractBits(Data, BitPn, BFX_DEFAULT_WIDTH) != (uint32)0U)
  {
    /* [cover parentID={F5FA5213-AA56-45c1-8924-9095E696310C}]
    Return result as TRUE
    [/cover] */
    ResultValue = (boolean)TRUE;
  }
  else
  {
    /* [cover parentID={C1D686ED-35B1-437c-AA0C-B57B2DCBA0AC}]
    Return result as FALSE
    [/cover] */
    ResultValue = (boolean)FALSE;
  }

  return ResultValue;
}

/*******************************************************************************
** Traceability      : [cover parentID={D0587F4C-25A6-4383-A444-57FA4A692AAC},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : boolean Bfx_GetBit_u64u8_u8                            **
**                     (                                                      **
**                       const uint64 Data,                                   **
**                       const uint8 BitPn                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_GetBit_u64u8_u8 function returns TRUE when the **
**                     logical status of the bit at BitPn bit position of the **
**                     Data input parameter is 1, otherwise the function      **
**                     returns FALSE.                                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x0D                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Data  - Input data                                     **
**                     BitPn - Bit position (Valid range: 0 to 63)            **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : boolean - Bit status                                   **
**                               TRUE  :Extracted bit is 1                    **
**                               FALSE :Extracted bit is 0                    **
*******************************************************************************/
static INLINE boolean Bfx_GetBit_u64u8_u8(const uint64 Data, const uint8 BitPn)
{
  boolean ResultValue;

  /* [cover parentID={086F6741-BAA7-445a-97D4-CD04D5321513}]
  Extract bit from specified position
  [/cover] */
  /* [cover parentID={94E2EF9E-2C51-41f8-95F4-5901CB6D69B1}]
  Is the extracted bit non zero?
  [/cover] */
  if (Bfx_lExtract64Bits(Data, BitPn, BFX_DEFAULT_WIDTH) != (uint64)0U)
  {
    /* [cover parentID={7E73230F-3827-40a0-A494-A5824E5DD903}]
    Return result as TRUE
    [/cover] */
    ResultValue = (boolean)TRUE;
  }
  else
  {
    /* [cover parentID={D0B1D917-394B-424d-A380-8F86F699F15A}]
    Return result as FALSE
    [/cover] */
    ResultValue = (boolean)FALSE;
  }

  return ResultValue;
}

/*******************************************************************************
** Traceability      : [cover parentID={1B4F8CED-2663-4d2b-A5E7-1BE433FB06C7},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_SetBits_u8u8u8u8                              **
**                     (                                                      **
**                       uint8* const Data,                                   **
**                       const uint8 BitStartPn,                              **
**                       const uint8 BitLn,                                   **
**                       const uint8 Status                                   **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_SetBits_u8u8u8u8 function clears the logical   **
**                     status of the bits of the Data parameter starting from **
**                     BitStartPn bit position for BitLn number of bits to 0  **
**                     when the value of Status parameter is zero.            **
**                     Otherwise for non zero value of Status parameter, the  **
**                     function sets the logical status of the bits of the    **
**                     Data parameter starting from BitStartPn bit position   **
**                     for BitLn number of bits to 1.                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x20                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitStartPn - Start bit position (Valid range: 0 to 7)  **
**                     BitLn      - Bit field length                          **
**                                  (Valid range: 1 to (8 - BitStartPn))      **
**                     Status     - Status value to be set                    **
**                                                                            **
** Parameters(in-out): Data       - Pointer to data which is to be modified   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_SetBits_u8u8u8u8(uint8* const Data,
                          const uint8 BitStartPn,
                          const uint8 BitLn,
                          const uint8 Status)
{
  /* [cover parentID={E1D65739-F41E-47e0-8DCB-47F0C65BA653}]
  Initialize all the bits of the value to be inserted to 0
  [/cover] */

  uint8 SourceData = BFX_DEFAULT_STATUS_0_EIGHT_BITS;

  /* [cover parentID={C2C64356-4343-450a-A8F7-78FB07AEC3FD}]
  Is the status parameter passed to the API non zero?
  [/cover] */
  if (Status != 0U)
  {
    /* [cover parentID={E02F0FA7-6B27-4b68-9527-0C860B821095}]
    Update all the bits of the value to be inserted to 1
    [/cover] */
    SourceData = BFX_DEFAULT_STATUS_1_EIGHT_BITS;
  }

  /* [cover parentID={F4292F90-E346-432d-AAA1-D5DE7968EBC6}]
  Insert the specified number of bits of the value to be inserted into Data
  parameter starting from the specified position
  [/cover] */
  Bfx_lInsert8Bits(Data, SourceData, BitStartPn, BitLn);
}

/*******************************************************************************
** Traceability      : [cover parentID={EA541C21-B2D4-4c22-9033-5C6AB54CBF0A},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_SetBits_u16u8u8u8                             **
**                     (                                                      **
**                       uint16* const Data,                                  **
**                       const uint8 BitStartPn,                              **
**                       const uint8 BitLn,                                   **
**                       const uint8 Status                                   **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_SetBits_u16u8u8u8 function clears the logical  **
**                     status of the bits of the Data parameter starting from **
**                     BitStartPn bit position for BitLn number of bits to 0  **
**                     when the value of Status parameter is zero.            **
**                     Otherwise for non zero value of Status parameter, the  **
**                     function sets the logical status of the bits of the    **
**                     Data parameter starting from BitStartPn bit position   **
**                     for BitLn number of bits to 1.                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x21                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitStartPn - Start bit position (Valid range: 0 to 15) **
**                     BitLn      - Bit field length                          **
**                                  (Valid range: 1 to (16 - BitStartPn))     **
**                     Status     - Status value to be set                    **
**                                                                            **
** Parameters(in-out): Data       - Pointer to data which is to be modified   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_SetBits_u16u8u8u8(uint16* const Data,
                           const uint8 BitStartPn,
                           const uint8 BitLn,
                           const uint8 Status)
{
  /* [cover parentID={DBE57D26-E43D-475f-8A35-D63E9DBBBB30}]
  Initialize all the bits of the value to be inserted to 0
  [/cover] */
  uint16 SourceData = BFX_DEFAULT_STATUS_0_SIXTEEN_BITS;

  /* [cover parentID={BC973D4F-F38E-43ad-8EC3-5CA0F5EDED55}]
  Is the status parameter passed to the API non zero?
  [/cover] */
  if (Status != 0U)
  {
    /* [cover parentID={BA01C5E7-C80B-4c8d-8B73-979D789828F9}]
    Update all the bits of the value to be inserted to 1
    [/cover] */
    SourceData = BFX_DEFAULT_STATUS_1_SIXTEEN_BITS;
  }

  /* [cover parentID={EDBBE0F8-ADF6-40e8-9902-02777E7F2D05}]
  Insert the specified number of bits of the value to be inserted into Data
  parameter starting from the specified position
  [/cover] */
  Bfx_lInsert16Bits(Data, SourceData, BitStartPn, BitLn);
}

/*******************************************************************************
** Traceability      : [cover parentID={E8BF75C7-F05D-4f53-81B8-0C3AE2F33B46},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_SetBits_u32u8u8u8                             **
**                     (                                                      **
**                       uint32* const Data,                                  **
**                       const uint8 BitStartPn,                              **
**                       const uint8 BitLn,                                   **
**                       const uint8 Status                                   **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_SetBits_u32u8u8u8 function clears the logical  **
**                     status of the bits of the Data parameter starting from **
**                     BitStartPn bit position for BitLn number of bits to 0  **
**                     when the value of Status parameter is zero.            **
**                     Otherwise for non zero value of Status parameter, the  **
**                     function sets the logical status of the bits of the    **
**                     Data parameter starting from BitStartPn bit position   **
**                     for BitLn number of bits to 1.                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x22                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitStartPn - Start bit position (Valid range: 0 to 31) **
**                     BitLn      - Bit field length                          **
**                                  (Valid range: 1 to (32 - BitStartPn))     **
**                     Status     - Status value to be set                    **
**                                                                            **
** Parameters(in-out): Data       - Pointer to data which is to be modified   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_SetBits_u32u8u8u8(uint32* const Data,
                           const uint8 BitStartPn,
                           const uint8 BitLn,
                           const uint8 Status)
{
  /* [cover parentID={6D2D9D7E-432C-408e-9DC6-A33C60F7C74B}]
  Initialize all the bits of the value to be inserted to 0
  [/cover] */
  uint32 SourceData = BFX_DEFAULT_STATUS_0_THIRTYTWO_BITS;

  /* [cover parentID={1912FD23-C603-4d7b-8E73-0D6DFC3AC4D1}]
  Is the status parameter passed to the API non zero?
  [/cover] */
  if (Status != 0U)
  {
    /* [cover parentID={11E85383-518C-4bf5-A0ED-0C0C34369884}]
    Update all the bits of the value to be inserted to 1
    [/cover] */
    SourceData = BFX_DEFAULT_STATUS_1_THIRTYTWO_BITS;
  }

  /* [cover parentID={A555CF28-4802-4499-915B-5AD9F9EB098F}]
  Is number of bits to be modified 32?
  [/cover] */
  if (BitLn == BFX_MAX_LENGTH_32BIT)
  {
    /* [cover parentID={A4017B60-0DC7-4c03-BDE0-C612E38A9BD3}]
    Insert all the bits of the value to be inserted into Data parameter
    [/cover] */
    *Data = SourceData;
  }
  else
  {
    /* [cover parentID={EFD3F402-CD97-4191-A214-8A5523E74AE6}]
    Insert the specified number of bits of the value to be inserted into Data
    parameter starting from the specified position
    [/cover] */
    Bfx_lInsert32Bits(Data, SourceData, BitStartPn, BitLn);
  }
}


/*******************************************************************************
** Traceability      : [cover parentID={98B97C6C-492C-49c4-A422-C5F4AE52BE9D},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_SetBits_u64u8u8u8                             **
**                     (                                                      **
**                       uint64* const Data,                                  **
**                       const uint8 BitStartPn,                              **
**                       const uint8 BitLn,                                   **
**                       const uint8 Status                                   **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_SetBits_u64u8u8u8 function clears the logical  **
**                     status of the bits of the Data parameter starting from **
**                     BitStartPn bit position for BitLn number of bits to 0  **
**                     when the value of Status parameter is zero.            **
**                     Otherwise for non zero value of Status parameter, the  **
**                     function sets the logical status of the bits of the    **
**                     Data parameter starting from BitStartPn bit position   **
**                     for BitLn number of bits to 1.                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x23                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitStartPn - Start bit position (Valid range: 0 to 63) **
**                     BitLn      - Bit field length                          **
**                                  (Valid range: 1 to (64 - BitStartPn))     **
**                     Status     - Status value to be set                    **
**                                                                            **
** Parameters(in-out): Data       - Pointer to data which is to be modified   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_SetBits_u64u8u8u8(uint64* const Data,
                           const uint8 BitStartPn,
                           const uint8 BitLn,
                           const uint8 Status)
{
  /* [cover parentID={D8EDC5DD-9C59-41d9-A3AA-CF776C892B71}]
  Initialize all the bits of the value to be inserted to 0
  [/cover] */
  uint64 SourceData = BFX_DEFAULT_STATUS_0_SIXTYFOUR_BITS;

  /* [cover parentID={D23D65BE-97A0-4f1a-BCEC-AE84FF56735C}]
  Is the status parameter passed to the API non zero?
  [/cover] */
  if (Status != 0U)
  {
    /* [cover parentID={BB1794F9-8143-4cf2-B8FB-61F91FDE2F33}]
    Update all the bits of the value to be inserted to 1
    [/cover] */
    SourceData = BFX_DEFAULT_STATUS_1_SIXTYFOUR_BITS;
  }

  /* [cover parentID={0A984E7A-1BD7-4229-857B-D018A0418463}]
  Is number of bits to be modified 64?
  [/cover] */
  if (BitLn == BFX_MAX_LENGTH_64BIT)
  {
    /* [cover parentID={C21377AB-4F29-4248-97C9-655D0D23B72D}]
    Insert all the bits of the value to be inserted into Data parameter
    [/cover] */
    *Data = SourceData;
  }
  else
  {
    /* [cover parentID={C6B60DC9-3533-47b9-B14B-B31B4BF0DEFB}]
    Insert the specified number of bits of the value to be inserted into
    Data parameter starting from the specified position
    [/cover] */
    Bfx_lInsert64Bits(Data, SourceData, BitStartPn, BitLn);
  }
}

/*******************************************************************************
** Traceability      : [cover parentID={8B100A1A-4510-47a0-A747-A13F236D2938},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : uint8 Bfx_GetBits_u8u8u8_u8                            **
**                     (                                                      **
**                       const uint8 Data,                                    **
**                       const uint8 BitStartPn,                              **
**                       const uint8 BitLn                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_GetBits_u8u8u8_u8 function returns the bits    **
**                     of the Data input parameter starting from BitStartPn   **
**                     bit position for BitLn number of bits.                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x26                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Data        - Input data                               **
**                     BitStartPn  - Start bit position (Valid range: 0 to 7) **
**                     BitLn       - Bit field length                         **
**                                   (Valid range: 1 to (8 - BitStartPn))     **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : uint8      - Bits extracted from the input parameter   **
**                                                                            **
*******************************************************************************/
static INLINE uint8 Bfx_GetBits_u8u8u8_u8(const uint8 Data,
                            const uint8 BitStartPn,
                            const uint8 BitLn)
{
  uint8 ResultValue;
  /* [cover parentID={D3C31030-989A-4761-ACFA-592CB5E424F6}]
  Extract specified number of bits starting from specified position
  [/cover] */
  ResultValue = (uint8)Bfx_lExtractBits((uint32)Data, BitStartPn, BitLn);

  /* [cover parentID={B23D85FE-7645-467d-A708-58F7195A8050}]
  Return the extracted bits
  [/cover] */
  return ResultValue;
}

/*******************************************************************************
** Traceability      : [cover parentID={EFDF924E-BB78-4322-8E9B-9F00854ECAF6},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : uint16 Bfx_GetBits_u16u8u8_u16                         **
**                     (                                                      **
**                       const uint16 Data,                                   **
**                       const uint8 BitStartPn,                              **
**                       const uint8 BitLn                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_GetBits_u16u8u8_u16 function returns the bits  **
**                     of the Data input parameter starting from BitStartPn   **
**                     bit position for BitLn number of bits.                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x27                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Data        - Input data                               **
**                     BitStartPn  - Start bit position (Valid range: 0 to 15)**
**                     BitLn       - Bit field length                         **
**                                   (Valid range: 1 to (16 - BitStartPn))    **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : uint16      - Bits extracted from the input parameter  **
**                                                                            **
*******************************************************************************/
static INLINE uint16 Bfx_GetBits_u16u8u8_u16(const uint16 Data,
                               const uint8 BitStartPn,
                               const uint8 BitLn)
{
  uint16 ResultValue;

  /* [cover parentID={89014975-82DB-4ff9-9937-EDFF514863D1}]
  Extract specified number of bits starting from specified position
  [/cover] */
  ResultValue = (uint16)Bfx_lExtractBits((uint32)Data, BitStartPn, BitLn);

  /* [cover parentID={6783C927-AEFF-40db-A1A8-34A4CB491485}]
  Return the extracted bits
  [/cover] */
  return ResultValue;
}

/*******************************************************************************
** Traceability      : [cover parentID={7EE2F159-557F-4f9a-B5E5-380D9CB97CB0},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : uint32 Bfx_GetBits_u32u8u8_u32                         **
**                     (                                                      **
**                       const uint32 Data,                                   **
**                       const uint8 BitStartPn,                              **
**                       const uint8 BitLn                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_GetBits_u32u8u8_u32 function returns the bits  **
**                     of the Data input parameter starting from BitStartPn   **
**                     bit position for BitLn number of bits.                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x28                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Data        - Input data                               **
**                     BitStartPn  - Start bit position (Valid range: 0 to 31)**
**                     BitLn       - Bit field length                         **
**                                   (Valid range: 1 to (32 - BitStartPn))    **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : uint32      - Bits extracted from the input parameter  **
**                                                                            **
*******************************************************************************/
static INLINE uint32 Bfx_GetBits_u32u8u8_u32(const uint32 Data,
                               const uint8 BitStartPn,
                               const uint8 BitLn)
{
  uint32 ResultValue;

  /* [cover parentID={5F0ACB68-1DAF-45fd-B8A3-3F948AE67CBA}]
  Is number of bits to be extracted 32?
  [/cover] */
  if (BitLn == BFX_MAX_LENGTH_32BIT)
  {
    /* [cover parentID={8E472D22-DD73-4fb6-A47A-A6392C22A120}]
    Extract all the bits
    [/cover] */
    ResultValue = Data;
  }
  else
  {
    /* [cover parentID={03144818-3D82-43c9-A651-539022A3C908}]
    Extract specified number of bits starting from specified position
    [/cover] */
    ResultValue = Bfx_lExtractBits(Data, BitStartPn, BitLn);
  }

  /* [cover parentID={29852CDD-50FD-45ab-86BF-EA018FC69225}]
  Return the extracted bits
  [/cover] */
  return ResultValue;
}

/*******************************************************************************
** Traceability      : [cover parentID={920BFD19-B33E-4313-A058-8BC195E11432},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : uint32 Bfx_GetBits_u64u8u8_u64                         **
**                     (                                                      **
**                       const uint64 Data,                                   **
**                       const uint8 BitStartPn,                              **
**                       const uint8 BitLn                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_GetBits_u64u8u8_u64 function returns the bits  **
**                     of the Data input parameter starting from BitStartPn   **
**                     bit position for BitLn number of bits.                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x29                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Data        - Input data                               **
**                     BitStartPn  - Start bit position (Valid range: 0 to 63)**
**                     BitLn       - Bit field length                         **
**                                   (Valid range: 1 to (64 - BitStartPn))    **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : uint64      - Bits extracted from the input parameter  **
**                                                                            **
*******************************************************************************/

static INLINE uint64 Bfx_GetBits_u64u8u8_u64(const uint64 Data,
                               const uint8 BitStartPn,
                               const uint8 BitLn)
{
  uint64 ResultValue;
  /* [cover parentID={BF82D3C6-EC5D-45af-A986-90AEE81D4794}]
  Is number of bits to be extracted 64?
  [/cover] */
  if (BitLn == BFX_MAX_LENGTH_64BIT)
  {
    /* [cover parentID={8EAC957D-2B9F-400f-BCCD-7873EF7A645D}]
    Extract all the bits
    [/cover] */
    ResultValue = Data;
  }
  else
  {
    /* [cover parentID={147733AD-3AFC-4d04-92D5-73766080F03B}]
    Extract specified number of bits starting from specified position
    [/cover] */
    ResultValue = Bfx_lExtract64Bits(Data, BitStartPn, BitLn);
  }

  /* [cover parentID={2DB17720-CD92-4464-A81F-6DC593B7D602}]
  Return the extracted bits
  [/cover] */
  return ResultValue;
}


/*******************************************************************************
** Traceability      : [cover parentID={C231B55F-2892-4eab-85FD-0011AA3422A2},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : boolean Bfx_TstBitMask_u8u8_u8                         **
**                     (                                                      **
**                       const uint8 Data,                                    **
**                       const uint8 Mask                                     **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_TstBitMask_u8u8_u8 function returns TRUE when  **
**                     the logical status of all the bits defined in the Mask **
**                     parameter are also set at the same bit position in the **
**                     Data input parameter, otherwise the function returns   **
**                     FALSE.                                                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x36                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Data    - Input data                                   **
**                     Mask    - Mask value                                   **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : boolean - Test result                                  **
**                               TRUE  :All bits defined in mask are set in   **
**                                      input parameter                       **
**                               FALSE :At least one bit defined in mask is   **
**                                      not set in input parameter            **
*******************************************************************************/
static INLINE boolean Bfx_TstBitMask_u8u8_u8(const uint8 Data, const uint8 Mask)
{
  boolean ResultValue;

  /* [cover parentID={BA2B06BB-50AB-4b57-9D74-97F1AEECE684}]
  Is the value obtained by masking of data with specified mask same as the
  specified mask?
  [/cover] */
  if ((Data & Mask) == Mask)
  {
    /* [cover parentID={75FE7451-21C0-463c-8612-258143621E73}]
    Return result as TRUE
    [/cover] */
    ResultValue = (boolean)TRUE;
  }
  else
  {
    /* [cover parentID={2AB21B45-FB0C-4335-ADF9-02623FDA91C9}]
    Return result as FALSE
    [/cover] */
    ResultValue = (boolean)FALSE;
  }

  return ResultValue;
}

/*******************************************************************************
** Traceability      : [cover parentID={18881389-A2E8-41ad-A8F9-E2E1FD34F57E},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : boolean Bfx_TstBitMask_u16u16_u8                       **
**                     (                                                      **
**                       const uint16 Data,                                   **
**                       const uint16 Mask                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_TstBitMask_u16u16_u8 function returns TRUE when**
**                     the logical status of all the bits defined in the Mask **
**                     parameter are also set at the same bit position in the **
**                     Data input parameter, otherwise the function returns   **
**                     FALSE.                                                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x37                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Data    - Input data                                   **
**                     Mask    - Mask value                                   **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : boolean - Test result                                  **
**                               TRUE  :All bits defined in mask are set in   **
**                                      input parameter                       **
**                               FALSE :At least one bit defined in mask is   **
**                                      not set in input parameter            **
*******************************************************************************/
static INLINE boolean Bfx_TstBitMask_u16u16_u8(const uint16 Data,
                                               const uint16 Mask)
{

  boolean ResultValue;

  /* [cover parentID={E6912A5A-377D-4601-B6D9-34BCF6C3E3E3}]
  Is the value obtained by masking of data with specified mask same as the
  specified mask?
  [/cover] */
  if ((Data & Mask) == Mask)
  {
    /* [cover parentID={6EBDBAEB-8288-4282-AAC1-7C02B88D15D9}]
    Return result as TRUE
    [/cover] */
    ResultValue = (boolean)TRUE;
  }
  else
  {
    /* [cover parentID={C6848A4D-6A92-4c26-8348-E059018A066E}]
    Return result as FALSE
    [/cover] */
    ResultValue = (boolean)FALSE;
  }

  return ResultValue;
}

/*******************************************************************************
** Traceability      : [cover parentID={047E0F26-5FC6-4da6-AA57-675C5AD55363},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : boolean Bfx_TstBitMask_u32u32_u8                       **
**                     (                                                      **
**                       const uint32 Data,                                   **
**                       const uint32 Mask                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_TstBitMask_u32u32_u8 function returns TRUE when**
**                     the logical status of all the bits defined in the Mask **
**                     parameter are also set at the same bit position in the **
**                     Data input parameter, otherwise the function returns   **
**                     FALSE.                                                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x38                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Data    - Input data                                   **
**                     Mask    - Mask value                                   **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : boolean - Test result                                  **
**                               TRUE  :All bits defined in mask are set in   **
**                                      input parameter                       **
**                               FALSE :At least one bit defined in mask is   **
**                                      not set in input parameter            **
*******************************************************************************/
static INLINE boolean Bfx_TstBitMask_u32u32_u8(const uint32 Data,
                                               const uint32 Mask)
{
  boolean ResultValue;

  /* [cover parentID={7928FD72-5B90-4a68-863F-8338723A9976}]
  Is the value obtained by masking of data with specified mask same as the
  specified mask?
  [/cover] */
  if ((Data & Mask) == Mask)
  {
    /* [cover parentID={B73C97F5-BBD4-453c-BBA9-BFBE9B6001CD}]
    Return result as TRUE
    [/cover] */
    ResultValue = (boolean)TRUE;
  }
  else
  {
    /* [cover parentID={4333A9BA-4285-4dae-8621-68A32052CF99}]
    Return result as FALSE
    [/cover] */
    ResultValue = (boolean)FALSE;
  }

  return ResultValue;
}

/*******************************************************************************
** Traceability      : [cover parentID={6836EAFF-FAC0-4bf9-B7F5-714C294B6C93},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : boolean Bfx_TstBitMask_u64u64_u8                       **
**                     (                                                      **
**                       const uint64 Data,                                   **
**                       const uint64 Mask                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_TstBitMask_u64u64_u8 function returns TRUE when**
**                     the logical status of all the bits defined in the Mask **
**                     parameter are also set at the same bit position in the **
**                     Data input parameter, otherwise the function returns   **
**                     FALSE.                                                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x39                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Data    - Input data                                   **
**                     Mask    - Mask value                                   **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : boolean - Test result                                  **
**                               TRUE  :All bits defined in mask are set in   **
**                                      input parameter                       **
**                               FALSE :At least one bit defined in mask is   **
**                                      not set in input parameter            **
*******************************************************************************/
static INLINE boolean Bfx_TstBitMask_u64u64_u8(const uint64 Data,
                                               const uint64 Mask)
{
  boolean ResultValue;

  /* [cover parentID={DF163E57-1F60-4b94-A3A3-548C43C9992C}]
  Is the value obtained by masking of data with specified mask same
  as the specified mask?
  [/cover] */
  if ((Data & Mask) == Mask)
  {
    /* [cover parentID={B462936D-0151-4695-B205-BD321859F885}]
    Return result as TRUE
    [/cover] */
    ResultValue = (boolean)TRUE;
  }
  else
  {
    /* [cover parentID={134A1443-3713-4ea5-B8BA-39A67B06AD53}]
    Return result as FALSE
    [/cover] */
    ResultValue = (boolean)FALSE;
  }

  return ResultValue;
}

/*******************************************************************************
** Traceability      : [cover parentID={E099C4F2-5F42-4571-832F-4EAF2F665EBB},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : boolean Bfx_TstBitLnMask_u8u8_u8                       **
**                     (                                                      **
**                       const uint8 Data,                                    **
**                       const uint8 Mask                                     **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_TstBitLnMask_u8u8_u8 function returns TRUE when**
**                     the logical status of at least one bit defined in the  **
**                     Mask parameter is also set at the same bit position in **
**                     the Data input parameter, otherwise the function       **
**                     returns FALSE.                                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x3A                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Mask    - Mask value                                   **
**                     Data    - Input data                                   **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : boolean - Test result                                  **
**                               TRUE  :At least one bit defined in mask is   **
**                                      set in input parameter                **
**                               FALSE :No bit defined in mask is set in input**
**                                      parameter                             **
*******************************************************************************/
static INLINE boolean Bfx_TstBitLnMask_u8u8_u8(const uint8 Data,
                                               const uint8 Mask)
{
  boolean ResultValue;

  /* [cover parentID={C8FC3BA4-C391-42f4-B05F-2A0237A316FA}]
  Is the value obtained by masking of data with specified mask non zero?
  [/cover] */
  if ((uint8)(Data & Mask) != 0U)
  {
    /* [cover parentID={DFB5E091-1BBD-42d4-884E-C7A3E4A1FCB2}]
    Return result as TRUE
    [/cover] */
    ResultValue = (boolean)TRUE;
  }
  else
  {
    /* [cover parentID={0722B7F1-7B9E-490f-82AE-E9107C9D9BEB}]
    Return result as FALSE
    [/cover] */
    ResultValue = (boolean)FALSE;
  }

  return ResultValue;
}

/*******************************************************************************
** Traceability      : [cover parentID={1D0D1F15-2C3B-409a-B155-B6587E7AE23A},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : boolean Bfx_TstBitLnMask_u16u16_u8                     **
**                     (                                                      **
**                       const uint16 Data,                                   **
**                       const uint16 Mask                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_TstBitLnMask_u16u16_u8 function returns TRUE   **
**                     when the logical status of at least one bit defined in **
**                     the Mask parameter is also set at the same bit position**
**                     in the Data input parameter, otherwise the function    **
**                     returns FALSE.                                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x3B                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Mask    - Mask value                                   **
**                     Data    - Input data                                   **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : boolean - Test result                                  **
**                               TRUE  :At least one bit defined in mask is   **
**                                      set in input parameter                **
**                               FALSE :No bit defined in mask is set in input**
**                                      parameter                             **
*******************************************************************************/
static INLINE boolean Bfx_TstBitLnMask_u16u16_u8(const uint16 Data,
                                                 const uint16 Mask)
{
  boolean ResultValue;

  /* [cover parentID={8793782E-37DD-4dc8-BA4C-360909EC25EB}]
  Is the value obtained by masking of data with specified mask non zero?
  [/cover] */
  if (((uint16)(Data & Mask)) != 0U)
  {
    /* [cover parentID={9B95AE81-62AD-4f9c-9662-7AA7C3CCCDC9}]
    Return result as TRUE
    [/cover] */
    ResultValue = (boolean)TRUE;
  }
  else
  {
    /* [cover parentID={9FEA854F-6765-4590-AA15-1F9AA64EBFE2}]
    Return result as FALSE
    [/cover] */
    ResultValue = (boolean)FALSE;
  }

  return ResultValue;
}

/*******************************************************************************
** Traceability      : [cover parentID={455E950E-6409-47f0-ACA1-517EFFA6ECD9},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : boolean Bfx_TstBitLnMask_u32u32_u8                     **
**                     (                                                      **
**                       const uint32 Data,                                   **
**                       const uint32 Mask                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_TstBitLnMask_u32u32_u8 function returns TRUE   **
**                     when the logical status of at least one bit defined in **
**                     the Mask parameter is also set at the same bit position**
**                     in the Data input parameter, otherwise the function    **
**                     returns FALSE.                                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x3C                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Mask    - Mask value                                   **
**                     Data    - Input data                                   **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : boolean - Test result                                  **
**                               TRUE  :At least one bit defined in mask is   **
**                                      set in input parameter                **
**                               FALSE :No bit defined in mask is set in input**
**                                      parameter                             **
*******************************************************************************/
static INLINE boolean Bfx_TstBitLnMask_u32u32_u8(const uint32 Data,
                                                 const uint32 Mask)
{
  boolean ResultValue;

  /* [cover parentID={B87AF996-9C39-426d-A502-536A2E507443}]
  Is the value obtained by masking of data with specified mask non zero?
  [/cover] */
  if((Data & Mask) != 0U)
  {
    /* [cover parentID={3742E0D6-AEDC-4238-A757-A73294C5C4BF}]
    Return result as TRUE
    [/cover] */
    ResultValue = (boolean)TRUE;
  }
  else
  {
    /* [cover parentID={709DD6A3-EFF3-4ac9-B7EA-3993E565C8C9}]
    Return result as FALSE
    [/cover] */
    ResultValue = (boolean)FALSE;
  }

  return ResultValue;
}

/*******************************************************************************
** Traceability      : [cover parentID={2AA907E2-892F-4ad9-B184-7A027C4D3EEA},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : boolean Bfx_TstBitLnMask_u64u64_u8                     **
**                     (                                                      **
**                       const uint64 Data,                                   **
**                       const uint64 Mask                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_TstBitLnMask_u64u64_u8 function returns TRUE   **
**                     when the logical status of at least one bit defined in **
**                     the Mask parameter is also set at the same bit position**
**                     in the Data input parameter, otherwise the function    **
**                     returns FALSE.                                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x3D                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Mask    - Mask value                                   **
**                     Data    - Input data                                   **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : boolean - Test result                                  **
**                               TRUE  :At least one bit defined in mask is   **
**                                      set in input parameter                **
**                               FALSE :No bit defined in mask is set in input**
**                                      parameter                             **
*******************************************************************************/
static INLINE boolean Bfx_TstBitLnMask_u64u64_u8(const uint64 Data,
                                                 const uint64 Mask)
{
  boolean ResultValue;

  /* [cover parentID={E9EAD9D9-8B1D-41d5-B6B3-37B1372EB44C}]
  Is the value obtained by masking of data with specified mask non zero?
  [/cover] */
  if((Data & Mask) != 0U)
  {
    /* [cover parentID={5FEF3124-24D2-4624-826D-9027D6137326}]
    Return result as TRUE
    [/cover] */
    ResultValue = (boolean)TRUE;
  }
  else
  {
    /* [cover parentID={52E8870F-14E7-4a81-A859-450A0963B14F}]
    Return result as FALSE
    [/cover] */
    ResultValue = (boolean)FALSE;
  }

  return ResultValue;
}

/*******************************************************************************
** Traceability      : [cover parentID={7CAFBB18-DCD8-4979-847B-C77AF5C6D779},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : boolean Bfx_TstParityEven_u8_u8                        **
**                     (                                                      **
**                       const uint8 Data                                     **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_TstParityEven_u8_u8 function returns TRUE when **
**                     the logical status of even number of bits in the Data  **
**                     input parameter is set to 1, otherwise the function    **
**                     returns FALSE.                                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x40                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Data    - Input data                                   **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : boolean - Test result                                  **
**                               TRUE  :Parity of input parameter is even     **
**                               FALSE :Parity of input parameter is odd      **
*******************************************************************************/
static INLINE boolean Bfx_TstParityEven_u8_u8(const uint8 Data)
{
  boolean ResultValue;

  /* [cover parentID={FFA292AE-B84D-4877-93A5-073C38DCF3B6}]
  Compute the odd parity for Data
  [/cover] */
  /* [cover parentID={9940BDBE-D9B4-4c08-96F2-07F4AD30EDD3}]
  Is the computed odd parity zero?
  [/cover] */
  if (Bfx_lParity((uint32)Data) == 0U)
  {
    /* [cover parentID={DD015841-4DCE-41af-9540-F13BDE99DD33}]
    Return result as TRUE
    [/cover] */
    ResultValue = (boolean)TRUE;
  }
  else
  {
    /* [cover parentID={C977E1FD-C53F-4581-A263-1D9CCD422BB1}]
    Return result as FALSE
    [/cover] */
    ResultValue = (boolean)FALSE;
  }

  return ResultValue;
}

/*******************************************************************************
** Traceability      : [cover parentID={ACCFECED-0AB4-4f6e-87AA-75CF0CFDD289},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : boolean Bfx_TstParityEven_u16_u8                       **
**                     (                                                      **
**                       const uint16 Data                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_TstParityEven_u16_u8 function returns TRUE when**
**                     the logical status of even number of bits in the Data  **
**                     input parameter is set to 1, otherwise the function    **
**                     returns FALSE.                                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x41                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Data    - Input data                                   **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : boolean - Test result                                  **
**                               TRUE  :Parity of input parameter is even     **
**                               FALSE :Parity of input parameter is odd      **
*******************************************************************************/
static INLINE boolean Bfx_TstParityEven_u16_u8(const uint16 Data)
{
  boolean ResultValue;

  /* [cover parentID={0198EA53-C7FA-4907-947E-7AA7D3099A95}]
  Compute the odd parity for Data
  [/cover] */
  /* [cover parentID={66F9708F-AD3C-4a5f-AFDB-8573DD506908}]
  Is the computed odd parity zero?
  [/cover] */
  if (Bfx_lParity((uint32)Data) == 0U)
  {
    /* [cover parentID={DE997520-7AC1-4445-92CE-F467556E63B5}]
    Return result as TRUE
    [/cover] */
    ResultValue = (boolean)TRUE;
  }
  else
  {
    /* [cover parentID={DBE8E9C7-27D0-4a4c-AA94-523236B94016}]
    Return result as FALSE
    [/cover] */
    ResultValue = (boolean)FALSE;
  }

  return ResultValue;
}

/*******************************************************************************
** Traceability      : [cover parentID={5D85A155-22CA-446f-81D8-9A10FDAE0E7F},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : boolean Bfx_TstParityEven_u32_u8                       **
**                     (                                                      **
**                       const uint32 Data                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_TstParityEven_u32_u8 function returns TRUE when**
**                     the logical status of even number of bits in the Data  **
**                     input parameter is set to 1, otherwise the function    **
**                     returns FALSE.                                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x42                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Data    - Input data                                   **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : boolean - Test result                                  **
**                               TRUE  :Parity of input parameter is even     **
**                               FALSE :Parity of input parameter is odd      **
*******************************************************************************/

static INLINE boolean Bfx_TstParityEven_u32_u8(const uint32 Data)
{
  boolean ResultValue;

  /* [cover parentID={459736C3-3E5A-4a2f-B277-B017CE380BBF}]
  Compute the odd parity for Data
  [/cover] */
  /* [cover parentID={DAADB693-D551-4eb3-A0E8-1B0182932A11}]
  Is the computed odd parity zero?
  [/cover] */
  if (Bfx_lParity(Data) == 0U)
  {
    /* [cover parentID={F7DC956A-8A22-4b58-ACC4-45E191AEEA5C}]
    Return result as TRUE
    [/cover] */
    ResultValue = (boolean)TRUE;
  }
  else
  {
    /* [cover parentID={CFA10C19-EED6-4869-B564-7D361CE332AC}]
    Return result as FALSE
    [/cover] */
    ResultValue = (boolean)FALSE;
  }

  return ResultValue;
}


/*******************************************************************************
** Traceability      : [cover parentID={5BB7253F-AAA2-4665-9750-5FE027A400CA},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : boolean Bfx_TstParityEven_u64_u8                       **
**                     (                                                      **
**                       const uint64 Data                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_TstParityEven_u64_u8 function returns TRUE when**
**                     the logical status of even number of bits in the Data  **
**                     input parameter is set to 1, otherwise the function    **
**                     returns FALSE.                                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x43                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Data    - Input data                                   **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : boolean - Test result                                  **
**                               TRUE  :Parity of input parameter is even     **
**                               FALSE :Parity of input parameter is odd      **
*******************************************************************************/
static INLINE boolean Bfx_TstParityEven_u64_u8(const uint64 Data)
{
  boolean ResultValue;

  /* [cover parentID={0C7FD844-661E-43b8-B808-F42DBDD3F855}]
  Compute the odd parity for Data
  [/cover] */
  /* [cover parentID={974305B5-DDBD-4b4a-9103-E19BCFBB6A75}]
  Is the computed odd parity zero?
  [/cover] */

  if (Bfx_lParity64Bits(Data) == 0U)
  {
    /* [cover parentID={A4EFAA92-CC18-4406-85CC-C7E98D8B197D}]
    Return result as TRUE
    [/cover] */
    ResultValue = (boolean)TRUE;
  }
  else
  {
    /* [cover parentID={5F313FB4-B854-4c46-91BB-03EE90DE171F}]
    Return result as FALSE
    [/cover] */
    ResultValue = (boolean)FALSE;
  }

  return ResultValue;
}

/*******************************************************************************
** Traceability      : [cover parentID={794A96C2-AF39-4566-83B3-B82884C5648C},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_CopyBit_u8u8u8u8                              **
**                     (                                                      **
**                       uint8* const DestinationData,                        **
**                       const uint8 DestinationPosition,                     **
**                       const uint8 SourceData,                              **
**                       const uint8 SourcePosition                           **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_CopyBit_u8u8u8u8 function copies a bit at      **
**                     SourcePosition bit position of the SourceData parameter**
**                     to DestinationPosition bit position of the             **
**                     DestinationData parameter.                             **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x66                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : DestinationPosition  - Destination bit position        **
**                                            (Valid range: 0 to 7)           **
**                     SourceData           - Source data                     **
**                     SourcePosition       - Source bit position             **
**                                            (Valid range: 0 to 7)           **
**                                                                            **
** Parameters(in-out): DestinationData      - Pointer to destination data     **
**                                            which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_CopyBit_u8u8u8u8(uint8* const DestinationData,
                          const uint8 DestinationPosition,
                          const uint8 SourceData,
                          const uint8 SourcePosition)
{
  /* [cover parentID={9E96AC6C-182A-4d6b-9C5B-48F7FC68B27F}]
  Extract the bit at the specified position of SourceData
  [/cover] */
  uint32 Status = Bfx_lExtractBits((uint32)SourceData, SourcePosition, \
                                   BFX_DEFAULT_WIDTH);
  /* [cover parentID={4B8502B7-E3B5-4942-871A-A97CC5CE6775}]
  Insert the extracted bit at specified position of DestinationData
  [/cover] */
  Bfx_lInsert8Bits(DestinationData, (uint8)Status, \
                   DestinationPosition, BFX_DEFAULT_WIDTH);
}

/*******************************************************************************
** Traceability      : [cover parentID={9BD3929F-8DE0-4dbc-9F86-DC1195384BC5},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_CopyBit_u16u8u16u8                            **
**                     (                                                      **
**                       uint16* const DestinationData,                       **
**                       const uint8 DestinationPosition,                     **
**                       const uint16 SourceData,                             **
**                       const uint8 SourcePosition                           **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_CopyBit_u16u8u16u8 function copies a bit at    **
**                     SourcePosition bit position of the SourceData parameter**
**                     to DestinationPosition bit position of the             **
**                     DestinationData parameter.                             **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x67                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : DestinationPosition  - Destination bit position        **
**                                            (Valid range: 0 to 15)          **
**                     SourceData           - Source data                     **
**                     SourcePosition       - Source bit position             **
**                                            (Valid range: 0 to 15)          **
**                                                                            **
** Parameters(in-out): DestinationData      - Pointer to destination data     **
**                                            which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_CopyBit_u16u8u16u8(uint16* const DestinationData,
                            const uint8 DestinationPosition,
                            const uint16 SourceData,
                            const uint8 SourcePosition)
{
  /* [cover parentID={982AE1DD-E1E7-4ff2-ABE9-77CBCE08F140}]
  Extract the bit at the specified position of SourceData
  [/cover] */
  uint32 Status = Bfx_lExtractBits((uint32)SourceData, SourcePosition, \
                                   BFX_DEFAULT_WIDTH);
  /* [cover parentID={9CADCBC1-2F61-445f-9E3F-5C5ED4E7F254}]
  Insert the extracted bit at specified position of DestinationData
  [/cover] */
  Bfx_lInsert16Bits(DestinationData, (uint16)Status, \
                    DestinationPosition, BFX_DEFAULT_WIDTH);
}

/*******************************************************************************
** Traceability      : [cover parentID={4E376FA1-D316-47ee-8378-B1491803E4F1},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_CopyBit_u32u8u32u8                            **
**                     (                                                      **
**                       uint32* const DestinationData,                       **
**                       const uint8 DestinationPosition,                     **
**                       const uint32 SourceData,                             **
**                       const uint8 SourcePosition                           **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_CopyBit_u32u8u32u8 function copies a bit at    **
**                     SourcePosition bit position of the SourceData parameter**
**                     to DestinationPosition bit position of the             **
**                     DestinationData parameter.                             **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x68                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : DestinationPosition  - Destination bit position        **
**                                            (Valid range: 0 to 31)          **
**                     SourceData           - Source data                     **
**                     SourcePosition       - Source bit position             **
**                                            (Valid range: 0 to 31)          **
**                                                                            **
** Parameters(in-out): DestinationData      - Pointer to destination data     **
**                                            which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_CopyBit_u32u8u32u8(uint32* const DestinationData,
                            const uint8 DestinationPosition,
                            const uint32 SourceData,
                            const uint8 SourcePosition)
{
  /* [cover parentID={5E985BB2-05FD-4993-9225-85E365DC837E}]
  Extract the bit at the specified position of SourceData
  [/cover] */
  uint32 Status = Bfx_lExtractBits(SourceData, SourcePosition, \
                                   BFX_DEFAULT_WIDTH);
  /* [cover parentID={C32E4F2F-A6FE-4424-8F11-1A952DD8F577}]
  Insert the extracted bit at specified position of DestinationData
  [/cover] */
  Bfx_lInsert32Bits(DestinationData, Status, \
                    DestinationPosition, BFX_DEFAULT_WIDTH);
}


/*******************************************************************************
** Traceability      : [cover parentID={BDD82BD3-0D76-482b-94A6-AFA9E4F1D2E7},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_CopyBit_u64u8u64u8                            **
**                     (                                                      **
**                       uint64* const DestinationData,                       **
**                       const uint8 DestinationPosition,                     **
**                       const uint64 SourceData,                             **
**                       const uint8 SourcePosition                           **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_CopyBit_u64u8u64u8 function copies a bit at    **
**                     SourcePosition bit position of the SourceData parameter**
**                     to DestinationPosition bit position of the             **
**                     DestinationData parameter.                             **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x69                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : DestinationPosition  - Destination bit position        **
**                                            (Valid range: 0 to 63)          **
**                     SourceData           - Source data                     **
**                     SourcePosition       - Source bit position             **
**                                            (Valid range: 0 to 63)          **
**                                                                            **
** Parameters(in-out): DestinationData      - Pointer to destination data     **
**                                            which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_CopyBit_u64u8u64u8(uint64* const DestinationData,
                            const uint8 DestinationPosition,
                            const uint64 SourceData,
                            const uint8 SourcePosition)
{
  /* [cover parentID={251C273A-7288-4b02-897B-DF1A333E45EE}]
  Extract the bit at the specified position of SourceData
  [/cover] */
  uint64 Status = Bfx_lExtract64Bits(SourceData, SourcePosition, \
                                   BFX_DEFAULT_WIDTH);
  /* [cover parentID={D80E47B8-462A-4bda-8E9E-DE3AA90B7E3F}]
  Insert the extracted bit at specified position of DestinationData
  [/cover] */
  Bfx_lInsert64Bits(DestinationData, Status, \
                    DestinationPosition, BFX_DEFAULT_WIDTH);
}

/*******************************************************************************
** Traceability      : [cover parentID={FEF4C275-13FB-4180-AF6F-B7A556C304CC},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_PutBits_u8u8u8u8                              **
**                     (                                                      **
**                       uint8* const Data,                                   **
**                       const uint8 BitStartPn,                              **
**                       const uint8 BitLn,                                   **
**                       const uint8 Pattern                                  **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_PutBits_u8u8u8u8 function copies the bit       **
**                     pattern from the Pattern parameter starting from 0 bit **
**                     position for BitLn number of bits into the Data        **
**                     parameter at the bit positions starting from BitStartPn**
**                     bit position for BitLn number of bits.                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x70                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitStartPn - Start bit position (Valid range: 0 to 7)  **
**                     BitLn      - Bit field length                          **
**                                  (Valid range: 1 to (8 - BitStartPn))      **
**                     Pattern    - Bit pattern to be set                     **
**                                                                            **
** Parameters(in-out): Data       - Pointer to destination data which is to be**
**                                  modified                                  **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_PutBits_u8u8u8u8(uint8* const Data,
                          const uint8 BitStartPn,
                          const uint8 BitLn,
                          const uint8 Pattern)
{
  /* [cover parentID={4D312315-EC08-4f98-9DE9-FB0A29DE063E}]
  Insert the the specified number of bits from the Pattern into the Data
  starting from specified position
  [/cover] */
  Bfx_lInsert8Bits(Data, Pattern, BitStartPn, BitLn);
}

/*******************************************************************************
** Traceability      : [cover parentID={F323A140-7F49-4026-97D2-7E13215CF3DE},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_PutBits_u16u8u8u16                            **
**                     (                                                      **
**                       uint16* const Data,                                  **
**                       const uint8 BitStartPn,                              **
**                       const uint8 BitLn,                                   **
**                       const uint16 Pattern                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_PutBits_u16u8u8u16 function copies the bit     **
**                     pattern from the Pattern parameter starting from 0 bit **
**                     position for BitLn number of bits into the Data        **
**                     parameter at the bit positions starting from BitStartPn**
**                     bit position for BitLn number of bits.                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x71                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitStartPn - Start bit position (Valid range: 0 to 15) **
**                     BitLn      - Bit field length                          **
**                                  (Valid range: 1 to (16 - BitStartPn))     **
**                     Pattern    - Bit pattern to be set                     **
**                                                                            **
** Parameters(in-out): Data       - Pointer to destination data which is to be**
**                                  modified                                  **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_PutBits_u16u8u8u16(uint16* const Data,
                            const uint8 BitStartPn,
                            const uint8 BitLn,
                            const uint16 Pattern)
{
  /* [cover parentID={68993B6E-C74F-4704-A8F3-7C61DB45464A}]
  Insert the the specified number of bits from the Pattern into the Data
  starting from specified position
  [/cover] */
  Bfx_lInsert16Bits(Data, Pattern, BitStartPn, BitLn);
}

/*******************************************************************************
** Traceability      : [cover parentID={062A0EF3-0804-43a8-944C-5437894297DA},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_PutBits_u32u8u8u32                            **
**                     (                                                      **
**                       uint32* const Data,                                  **
**                       const uint8 BitStartPn,                              **
**                       const uint8 BitLn,                                   **
**                       const uint32 Pattern                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_PutBits_u32u8u8u32 function copies the bit     **
**                     pattern from the Pattern parameter starting from 0 bit **
**                     position for BitLn number of bits into the Data        **
**                     parameter at the bit positions starting from BitStartPn**
**                     bit position for BitLn number of bits.                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x72                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitStartPn - Start bit position (Valid range: 0 to 31) **
**                     BitLn      - Bit field length                          **
**                                  (Valid range: 1 to (32 - BitStartPn))     **
**                     Pattern    - Bit pattern to be set                     **
**                                                                            **
** Parameters(in-out): Data       - Pointer to destination data which is to be**
**                                  modified                                  **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_PutBits_u32u8u8u32(uint32* const Data,
                            const uint8 BitStartPn,
                            const uint8 BitLn,
                            const uint32 Pattern)
{
  /* [cover parentID={E30DFEE8-1F52-4713-A3DF-1E3F2DF35976}]
  Is number of bits to be modified 32?
  [/cover] */
  if(BitLn == BFX_MAX_LENGTH_32BIT)
  {
    /* [cover parentID={34B5CC33-2CA2-4703-81B8-236A68DACE92}]
    Insert all the bits of Pattern into Data
    [/cover] */
    *Data = Pattern;
  }
  else
  {
    /* [cover parentID={BF805070-A2BF-40bf-8B46-BB7098EE64D8}]
    Insert the the specified number of bits from Pattern into Data starting from
    specified position
    [/cover] */
    Bfx_lInsert32Bits(Data, Pattern, BitStartPn, BitLn);
  }
}

/*******************************************************************************
** Traceability      : [cover parentID={EA270D29-E719-444f-BD31-79AD2497ED45},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_PutBits_u64u8u8u64                            **
**                     (                                                      **
**                       uint64* const Data,                                  **
**                       const uint8 BitStartPn,                              **
**                       const uint8 BitLn,                                   **
**                       const uint64 Pattern                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_PutBits_u64u8u8u64 function copies the bit     **
**                     pattern from the Pattern parameter starting from 0 bit **
**                     position for BitLn number of bits into the Data        **
**                     parameter at the bit positions starting from BitStartPn**
**                     bit position for BitLn number of bits.                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x73                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitStartPn - Start bit position (Valid range: 0 to 63) **
**                     BitLn      - Bit field length                          **
**                                  (Valid range: 1 to (64 - BitStartPn))     **
**                     Pattern    - Bit pattern to be set                     **
**                                                                            **
** Parameters(in-out): Data       - Pointer to destination data which is to be**
**                                  modified                                  **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_PutBits_u64u8u8u64(uint64* const Data,
                            const uint8 BitStartPn,
                            const uint8 BitLn,
                            const uint64 Pattern)
{
  /* [cover parentID={3C4F7148-1660-4922-9D20-6EDD76844768}]
  Is number of bits to be modified 64?
  [/cover] */
  if(BitLn == BFX_MAX_LENGTH_64BIT)
  {
    /* [cover parentID={69C14556-737E-43eb-BFCA-4A4322282934}]
    Insert all the bits of Pattern into Data
    [/cover] */
    *Data = Pattern;
  }
  else
  {
    /* [cover parentID={E387B17A-7B18-46e3-8681-D2CE65440F28}]
    Insert the the specified number of bits from Pattern into Data
    starting from specified position
    [/cover] */
    Bfx_lInsert64Bits(Data, Pattern, BitStartPn, BitLn);
  }
}

/*******************************************************************************
** Traceability      : [cover parentID={AEACC909-ED92-4e45-97A7-13BB2DAD64BD},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_PutBit_u8u8u8                                 **
**                     (                                                      **
**                       uint8* const Data,                                   **
**                       const uint8 BitPn,                                   **
**                       const boolean Status                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_PutBit_u8u8u8 function updates the logical     **
**                     status of the bit at BitPn bit position of the Data    **
**                     parameter to 1 when the value of Status parameter is   **
**                     TRUE, otherwise the function updates the logical status**
**                     of the bit at BitPn bit position of the Data parameter **
**                     to 0.                                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x85                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitPn  - Bit position (Valid range: 0 to 7)            **
**                     Status - Status value (Valid values: TRUE or FALSE)    **
**                                                                            **
** Parameters(in-out): Data   - Pointer to data which is to be modified       **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_PutBit_u8u8u8(uint8* const Data,
                       const uint8 BitPn,
                       const boolean Status)
{
  /* [cover parentID={37F27069-B388-46e6-A736-4CFE653624C2}]
  Is the status parameter passed to the API TRUE?
  [/cover] */
  if(Status == (boolean)TRUE)
  {
    /* [cover parentID={8A49161A-E95A-4756-AC49-BA373035C2E0}]
    Set the bit at the specified position
    [/cover] */
    Bfx_lInsert8Bits(Data, BFX_DEFAULT_STATUS_1_EIGHT_BITS, \
                     BitPn, BFX_DEFAULT_WIDTH);
  }
  else
  {
    /* [cover parentID={24D4E1B2-3033-4baf-9AAE-203F880FD945}]
    Clear the bit at the specified position
    [/cover] */
    Bfx_lInsert8Bits(Data, BFX_DEFAULT_STATUS_0_EIGHT_BITS, \
                     BitPn, BFX_DEFAULT_WIDTH);
  }
}

/*******************************************************************************
** Traceability      : [cover parentID={E7F683A0-091D-431e-8C5D-2B829E0890D1},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_PutBit_u16u8u8                                **
**                     (                                                      **
**                       uint16* const Data,                                  **
**                       const uint8 BitPn,                                   **
**                       const boolean Status                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_PutBit_u16u8u8 function updates the logical    **
**                     status of the bit at BitPn bit position of the Data    **
**                     parameter to 1 when the value of Status parameter is   **
**                     TRUE, otherwise the function updates the logical status**
**                     of the bit at BitPn bit position of the Data parameter **
**                     to 0.                                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x86                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitPn  - Bit position (Valid range: 0 to 15)           **
**                     Status - Status value (Valid values: TRUE or FALSE)    **
**                                                                            **
** Parameters(in-out): Data   - Pointer to data which is to be modified       **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_PutBit_u16u8u8(uint16* const Data,
                        const uint8 BitPn,
                        const boolean Status)
{
  /* [cover parentID={2007F92E-4970-4a16-92F6-0E36D1B0CEAE}]
  Is the status parameter passed to the API TRUE?
  [/cover] */
  if(Status == (boolean)TRUE)
  {
    /* [cover parentID={12AA32D7-3F01-4489-8C9B-1E0BC9721A30}]
    Set the bit at the specified position
    [/cover] */
    Bfx_lInsert16Bits(Data, BFX_DEFAULT_STATUS_1_SIXTEEN_BITS, \
                      BitPn, BFX_DEFAULT_WIDTH);
  }
  else
  {
    /* [cover parentID={D7C87E0F-8844-447f-90DC-0C8F68715BBF}]
    Clear the bit at the specified position
    [/cover] */
    Bfx_lInsert16Bits(Data, BFX_DEFAULT_STATUS_0_SIXTEEN_BITS, \
                      BitPn, BFX_DEFAULT_WIDTH);
  }
}

/*******************************************************************************
** Traceability      : [cover parentID={2CF113E0-38FF-4489-BBE2-F01FABF4DD87},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_PutBit_u32u8u8                                **
**                     (                                                      **
**                       uint32* const Data,                                  **
**                       const uint8 BitPn,                                   **
**                       const boolean Status                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_PutBit_u32u8u8 function updates the logical    **
**                     status of the bit at BitPn bit position of the Data    **
**                     parameter to 1 when the value of Status parameter is   **
**                     TRUE, otherwise the function updates the logical status**
**                     of the bit at BitPn bit position of the Data parameter **
**                     to 0.                                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x87                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitPn  - Bit position (Valid range: 0 to 31)           **
**                     Status - Status value (Valid values: TRUE or FALSE)    **
**                                                                            **
** Parameters(in-out): Data   - Pointer to data which is to be modified       **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_PutBit_u32u8u8(uint32* const Data,
                        const uint8 BitPn,
                        const boolean Status)
{
  /* [cover parentID={FEF813FC-1C87-45e7-BE46-6278CE1EB176}]
  Is the status parameter passed to the API TRUE?
  [/cover] */
  if(Status == (boolean)TRUE)
  {
    /* [cover parentID={2946F86B-7564-4e9f-9FEF-0A2664130E29}]
    Set the bit at the specified position
    [/cover] */
    Bfx_lInsert32Bits(Data, BFX_DEFAULT_STATUS_1_THIRTYTWO_BITS, \
                      BitPn, BFX_DEFAULT_WIDTH);
  }
  else
  {
    /* [cover parentID={EB0C38DF-8FBA-43a3-AAD6-F806DC6FEC91}]
    Clear the bit at the specified position
    [/cover] */
    Bfx_lInsert32Bits(Data, BFX_DEFAULT_STATUS_0_THIRTYTWO_BITS, \
                      BitPn, BFX_DEFAULT_WIDTH);
  }
}

/*******************************************************************************
** Traceability      : [cover parentID={D0CF1579-8385-492b-B42F-659541B3F2F9},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_PutBit_u64u8u8                                **
**                     (                                                      **
**                       uint64* const Data,                                  **
**                       const uint8 BitPn,                                   **
**                       const boolean Status                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_PutBit_u64u8u8 function updates the logical    **
**                     status of the bit at BitPn bit position of the Data    **
**                     parameter to 1 when the value of Status parameter is   **
**                     TRUE, otherwise the function updates the logical status**
**                     of the bit at BitPn bit position of the Data parameter **
**                     to 0.                                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x88                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitPn  - Bit position (Valid range: 0 to 63)           **
**                     Status - Status value (Valid values: TRUE or FALSE)    **
**                                                                            **
** Parameters(in-out): Data   - Pointer to data which is to be modified       **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_PutBit_u64u8u8(uint64* const Data,
                        const uint8 BitPn,
                        const boolean Status)
{
  /* [cover parentID={7CF63AD5-DAC0-45b4-8AF0-3D5B5C3305DC}]
  Is the status parameter passed to the API TRUE?
  [/cover] */
  if(Status == (boolean)TRUE)
  {
    /* [cover parentID={D5E4369D-84DF-439d-97B2-1671DF0EB727}]
    Set the bit at the specified position
    [/cover] */
    Bfx_lInsert64Bits(Data, BFX_DEFAULT_STATUS_1_SIXTYFOUR_BITS, \
                      BitPn, BFX_DEFAULT_WIDTH);
  }
  else
  {
    /* [cover parentID={21A12E2B-40F7-4960-8E0A-C0494DFD145F}]
    Clear the bit at the specified position
    [/cover] */
    Bfx_lInsert64Bits(Data, BFX_DEFAULT_STATUS_0_SIXTYFOUR_BITS, \
                      BitPn, BFX_DEFAULT_WIDTH);
  }
}

/*******************************************************************************
** Traceability      : [cover parentID={6F9AA5AC-460A-4e75-8BA7-3058D802AF96},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_SetBitMask_u8u8                               **
**                     (                                                      **
**                       uint8* const Data,                                   **
**                       const uint8 Mask                                     **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_SetBitMask_u32u32 function sets the logical    **
**                     status of the bits of the Data parameter to 1, for all **
**                     the bit positions for which the logical status of bit  **
**                     in the Mask parameter is set to 1. The remaining bits  **
**                     of the Data parameter will retain their original       **
**                     values.                                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x2a                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : Mask - Mask value                                      **
**                                                                            **
** Parameters(in-out): Data - Pointer to data which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_SetBitMask_u8u8(uint8* const Data, const uint8 Mask)
{
  /*Data is equal to Bitwise OR of Data and Mask.*/
  *Data |= Mask;
}

/*******************************************************************************
** Traceability      : [cover parentID={0913DED7-D25F-45b8-BBF8-21C22DB8B56C},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_SetBitMask_u16u16                             **
**                     (                                                      **
**                       uint16* const Data,                                  **
**                       const uint16 Mask                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_SetBitMask_u16u16 function sets the logical    **
**                     status of the bits of the Data parameter to 1, for all **
**                     the bit positions for which the logical status of bit  **
**                     in the Mask parameter is set to 1. The remaining bits  **
**                     of the Data parameter will retain their original       **
**                     values.                                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x2b                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : Mask - Mask value                                      **
**                                                                            **
** Parameters(in-out): Data - Pointer to data which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_SetBitMask_u16u16(uint16* const Data, const uint16 Mask)
{
  /*Data is equal to Bitwise OR of Data and Mask.*/
  *Data |= Mask;
}

/*******************************************************************************
** Traceability      : [cover parentID={DF86A86A-A0FA-47f6-BF61-7755388E748E},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_SetBitMask_u32u32                             **
**                     (                                                      **
**                       uint32* const Data,                                  **
**                       const uint32 Mask                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_SetBitMask_u32u32 function sets the logical    **
**                     status of the bits of the Data parameter to 1, for all **
**                     the bit positions for which the logical status of bit  **
**                     in the Mask parameter is set to 1. The remaining bits  **
**                     of the Data parameter will retain their original       **
**                     values.                                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x2c                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : Mask - Mask value                                      **
**                                                                            **
** Parameters(in-out): Data - Pointer to data which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_SetBitMask_u32u32(uint32* const Data, const uint32 Mask)
{
  /*Data is equal to Bitwise OR of Data and Mask.*/
  *Data |= Mask;
}


/*******************************************************************************
** Traceability      : [cover parentID={E868A6D7-0CD7-497f-A245-2193AE8BF078},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_SetBitMask_u64u64                             **
**                     (                                                      **
**                       uint64* const Data,                                  **
**                       const uint64 Mask                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_SetBitMask_u64u64 function sets the logical    **
**                     status of the bits of the Data parameter to 1, for all **
**                     the bit positions for which the logical status of bit  **
**                     in the Mask parameter is set to 1. The remaining bits  **
**                     of the Data parameter will retain their original       **
**                     values.                                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x2D                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : Mask - Mask value                                      **
**                                                                            **
** Parameters(in-out): Data - Pointer to data which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_SetBitMask_u64u64(uint64* const Data, const uint64 Mask)
{
  /*Data is equal to Bitwise OR of Data and Mask.*/
  *Data |= Mask;
}

/*******************************************************************************
** Traceability      : [cover parentID={AA757405-3C76-45fb-BED8-518D5C3940EE},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ClrBitMask_u8u8                               **
**                     (                                                      **
**                       uint8* const Data,                                   **
**                       const uint8 Mask                                     **
**                      )                                                     **
**                                                                            **
** Description       : The Bfx_ClrBitMask_u8u8 function clears the logical    **
**                     status of the bits of the Data parameter to 0, for all **
**                     the bit positions for which the logical status of bit  **
**                     in the Mask parameter is set to 1. The remaining bits  **
**                     of Data parameter will retain their original values.   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
**                                                                            **
** Service ID        : 0x30                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : Mask - Mask value                                      **
**                                                                            **
** Parameters(in-out): Data - Pointer to data which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ClrBitMask_u8u8(uint8* const Data, const uint8 Mask)
{
  /*Data is equal to Bitwise AND of Data and Bitwise complement of Mask.*/
  *Data &= (~Mask);
}

/*******************************************************************************
** Traceability      : [cover parentID={8987E8DE-825A-48cb-9C8E-CE06410A59DE},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ClrBitMask_u16u16                             **
**                     (                                                      **
**                       uint16* const Data,                                  **
**                       const uint16 Mask                                    **
**                      )                                                     **
**                                                                            **
** Description       : The Bfx_ClrBitMask_u16u16 function clears the logical  **
**                     status of the bits of the Data parameter to 0, for all **
**                     the bit positions for which the logical status of bit  **
**                     in the Mask parameter is set to 1. The remaining bits  **
**                     of Data parameter will retain their original values.   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
**                                                                            **
** Service ID        : 0x31                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : Mask - Mask value                                      **
**                                                                            **
** Parameters(in-out): Data - Pointer to data which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ClrBitMask_u16u16(uint16* const Data, const uint16 Mask)
{
  /*Data is equal to Bitwise AND of Data and Bitwise complement of Mask.*/
  *Data &= (~Mask);
}

/*******************************************************************************
** Traceability      : [cover parentID={F9881519-1A97-46b4-A7F4-5295AA870DBA},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ClrBitMask_u32u32                             **
**                     (                                                      **
**                       uint32* const Data,                                  **
**                       const uint32 Mask                                    **
**                      )                                                     **
**                                                                            **
** Description       : The Bfx_ClrBitMask_u32u32 function clears the logical  **
**                     status of the bits of the Data parameter to 0, for all **
**                     the bit positions for which the logical status of bit  **
**                     in the Mask parameter is set to 1. The remaining bits  **
**                     of Data parameter will retain their original values.   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
**                                                                            **
** Service ID        : 0x32                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : Mask - Mask value                                      **
**                                                                            **
** Parameters(in-out): Data - Pointer to data which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ClrBitMask_u32u32(uint32* const Data, const uint32 Mask)
{
  /*Data is equal to Bitwise AND of Data and Bitwise complement of Mask.*/
  *Data &= (~Mask);
}

/*******************************************************************************
** Traceability      : [cover parentID={43361192-4327-420f-9A75-566FDEDF0134},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ClrBitMask_u64u64                             **
**                     (                                                      **
**                       uint64* const Data,                                  **
**                       const uint64 Mask                                    **
**                      )                                                     **
**                                                                            **
** Description       : The Bfx_ClrBitMask_u64u64 function clears the logical  **
**                     status of the bits of the Data parameter to 0, for all **
**                     the bit positions for which the logical status of bit  **
**                     in the Mask parameter is set to 1. The remaining bits  **
**                     of Data parameter will retain their original values.   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
**                                                                            **
** Service ID        : 0x33                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : Mask - Mask value                                      **
**                                                                            **
** Parameters(in-out): Data - Pointer to data which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ClrBitMask_u64u64(uint64* const Data, const uint64 Mask)
{
  /*Data is equal to Bitwise AND of Data and Bitwise complement of Mask.*/
  *Data &= (~Mask);
}

/*******************************************************************************
** Traceability      : [cover parentID={8937B7D6-5D53-4dc7-B065-BC8A41F234BF},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ToggleBits_u8                                 **
**                     (                                                      **
**                       uint8* const Data                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ToggleBits_u8 function toggles all the bits of **
**                     the Data parameter (1's complement of the Data         **
**                     parameter).                                            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x46                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : None                                                   **
**                                                                            **
** Parameters(in-out): Data - Pointer to data which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ToggleBits_u8(uint8* const Data)
{
  /*Data is equal to Bitwise NOT of Data.*/
  *Data = ~(*Data);
}

/*******************************************************************************
** Traceability      : [cover parentID={7D126D21-984E-480a-A672-B986D557452E},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ToggleBits_u16                                **
**                     (                                                      **
**                       uint16* const Data                                   **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ToggleBits_u16 function toggles all the bits of**
**                     the Data parameter (1's complement of the Data         **
**                     parameter).                                            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x47                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : None                                                   **
**                                                                            **
** Parameters(in-out): Data - Pointer to data which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ToggleBits_u16(uint16* const Data)
{
  /*Data is equal to Bitwise NOT of Data.*/
  *Data = ~(*Data);
}

/*******************************************************************************
** Traceability      : [cover parentID={A5F82090-2212-477e-A93B-451BA183251D},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ToggleBits_u32                                **
**                     (                                                      **
**                       uint32* const Data                                   **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ToggleBits_u32 function toggles all the bits of**
**                     the Data parameter (1's complement of the Data         **
**                     parameter).                                            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x48                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : None                                                   **
**                                                                            **
** Parameters(in-out): Data - Pointer to data which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ToggleBits_u32(uint32* const Data)
{
  /*Data is equal to Bitwise NOT of Data.*/
  *Data = ~(*Data);
}

/*******************************************************************************
** Traceability      : [cover parentID={FD6752CE-E8A3-49da-8DD9-AC81FB629874},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ToggleBits_u64                                **
**                     (                                                      **
**                       uint64* const Data                                   **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ToggleBits_u64 function toggles all the bits of**
**                     the Data parameter (1's complement of the Data         **
**                     parameter).                                            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x49                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : None                                                   **
**                                                                            **
** Parameters(in-out): Data - Pointer to data which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ToggleBits_u64(uint64* const Data)
{
  /*Data is equal to Bitwise NOT of Data.*/
  *Data = ~(*Data);
}

/*******************************************************************************
** Traceability      : [cover parentID={208AD1FB-083F-4fb6-B94F-E80C966B9313},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ToggleBitMask_u8u8                            **
**                     (                                                      **
**                       uint32* const Data,                                  **
**                       const uint32 Mask                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ToggleBitMask_u32u32 function toggles the      **
**                     logical status of the bits of the Data parameter, for  **
**                     all the bit positions for which the logical status of  **
**                     bit in the Mask parameter is set to 1. The remaining   **
**                     bits of the Data parameter will retain their original  **
**                     values.                                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x4a                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : Mask - Mask value                                      **
**                                                                            **
** Parameters(in-out): Data - Pointer to data which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ToggleBitMask_u8u8(uint8* const Data,
                                          const uint8 Mask)
{
  /*Data is equal to Bitwise XOR of Data and Mask.*/
  /*XOR with 0 gives unchanged value*/
  /*XOR with 1 gives complement of the value*/
  *Data = (*Data) ^ (Mask);
}

/*******************************************************************************
** Traceability      : [cover parentID={195DE81E-E6F7-43d3-9BED-8DBD0B872B63},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ToggleBitMask_u16u16                          **
**                     (                                                      **
**                       uint16* const Data,                                  **
**                       const uint16 Mask                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ToggleBitMask_u16u16 function toggles the      **
**                     logical status of the bits of the Data parameter, for  **
**                     all the bit positions for which the logical status of  **
**                     bit in the Mask parameter is set to 1. The remaining   **
**                     bits of the Data parameter will retain their original  **
**                     values.                                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x4b                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : Mask - Mask value                                      **
**                                                                            **
** Parameters(in-out): Data - Pointer to data which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ToggleBitMask_u16u16(uint16* const Data,
                                            const uint16 Mask)
{
  /*Data is equal to Bitwise XOR of Data and Mask.*/
  /*XOR with 0 gives unchanged value*/
  /*XOR with 1 gives complement of the value*/
  *Data = (*Data) ^ (Mask);
}


/*******************************************************************************
** Traceability      : [cover parentID={9A70B949-4D89-4d91-819E-CD517EEBC2B2},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ToggleBitMask_u32u32                          **
**                     (                                                      **
**                       uint32* const Data,                                  **
**                       uint32 Mask                                          **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ToggleBitMask_u32u32 function toggles the      **
**                     logical status of the bits of the Data parameter, for  **
**                     all the bit positions for which the logical status of  **
**                     bit in the Mask parameter is set to 1. The remaining   **
**                     bits of the Data parameter will retain their original  **
**                     values.                                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x4c                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : Mask - Mask value                                      **
**                                                                            **
** Parameters(in-out): Data - Pointer to data which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ToggleBitMask_u32u32(uint32* const Data,
                                            const uint32 Mask)
{
  /*Data is equal to Bitwise XOR of Data and Mask.*/
  /*XOR with 0 gives unchanged value*/
  /*XOR with 1 gives complement of the value*/
  *Data = (*Data) ^ (Mask);
}

/*******************************************************************************
** Traceability      : [cover parentID={538F933A-84C9-46df-8A31-81603CE68FD9},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ToggleBitMask_u64u64                          **
**                     (                                                      **
**                       uint64* const Data,                                  **
**                       uint64 Mask                                          **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ToggleBitMask_u64u64 function toggles the      **
**                     logical status of the bits of the Data parameter, for  **
**                     all the bit positions for which the logical status of  **
**                     bit in the Mask parameter is set to 1. The remaining   **
**                     bits of the Data parameter will retain their original  **
**                     values.                                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x4d                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : Mask - Mask value                                      **
**                                                                            **
** Parameters(in-out): Data - Pointer to data which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ToggleBitMask_u64u64(uint64* const Data,
                                            const uint64 Mask)
{
  /*Data is equal to Bitwise XOR of Data and Mask.*/
  /*XOR with 0 gives unchanged value*/
  /*XOR with 1 gives complement of the value*/
  *Data = (*Data) ^ (Mask);
}


/*******************************************************************************
** Traceability      : [cover parentID={308A7584-7C58-44eb-9A81-C79B18C02DF0},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ShiftBitRt_u8u8                               **
**                     (                                                      **
**                       uint8* const Data,                                   **
**                       const uint8 ShiftCnt                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ShiftBitRt_u8u8 function shifts the bits of   **
**                     the Data parameter to the right by ShiftCnt count. The **
**                     most significant bit (left-most bit) is replaced by a 0**
**                     bit and the least significant bit (right-most bit) is  **
**                     discarded for every single bit shift cycle.            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x50                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : ShiftCnt - Shift right count (Valid range: 0 to 7)     **
**                                                                            **
** Parameters(in-out): Data     - Pointer to data which is to be modified     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ShiftBitRt_u8u8(uint8* const Data,
                                       const uint8 ShiftCnt)
{
  /*Data Right Shifted by ShiftCnt number of times*/
  *Data = (uint8)(*Data >> ShiftCnt);
}

/*******************************************************************************
** Traceability      : [cover parentID={901BD331-E511-4f38-B1C6-AA9BC22F1DC2},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ShiftBitRt_u16u8                              **
**                     (                                                      **
**                       uint16* const Data,                                  **
**                       const uint8 ShiftCnt                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ShiftBitRt_u16u8 function shifts the bits of   **
**                     the Data parameter to the right by ShiftCnt count. The **
**                     most significant bit (left-most bit) is replaced by a 0**
**                     bit and the least significant bit (right-most bit) is  **
**                     discarded for every single bit shift cycle.            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x51                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : ShiftCnt - Shift right count (Valid range: 0 to 15)    **
**                                                                            **
** Parameters(in-out): Data     - Pointer to data which is to be modified     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ShiftBitRt_u16u8(uint16* const Data,
                                        const uint8 ShiftCnt)
{
  /*Data Right Shifted by ShiftCnt number of times*/
  *Data = (uint16)(*Data >> ShiftCnt);
}

/*******************************************************************************
** Traceability      : [cover parentID={368FDF87-541F-4604-BD29-2539D2D19F6B},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ShiftBitRt_u32u8                              **
**                     (                                                      **
**                       uint32* const Data,                                  **
**                       const uint8 ShiftCnt                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ShiftBitRt_u32u8 function shifts the bits of   **
**                     the Data parameter to the right by ShiftCnt count. The **
**                     most significant bit (left-most bit) is replaced by a 0**
**                     bit and the least significant bit (right-most bit) is  **
**                     discarded for every single bit shift cycle.            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x52                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : ShiftCnt - Shift right count (Valid range: 0 to 31)    **
**                                                                            **
** Parameters(in-out): Data     - Pointer to data which is to be modified     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ShiftBitRt_u32u8(uint32* const Data,
                                        const uint8 ShiftCnt)
{
  /*Data Right Shifted by ShiftCnt number of times*/
  *Data = (uint32)(*Data >> ShiftCnt);
}

/*******************************************************************************
** Traceability      : [cover parentID={AFBAB13A-FCDE-4c31-B938-5EBD45D4CD92},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ShiftBitRt_u64u8                              **
**                     (                                                      **
**                       uint64* const Data,                                  **
**                       const uint8 ShiftCnt                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ShiftBitRt_u64u8 function shifts the bits of   **
**                     the Data parameter to the right by ShiftCnt count. The **
**                     most significant bit (left-most bit) is replaced by a 0**
**                     bit and the least significant bit (right-most bit) is  **
**                     discarded for every single bit shift cycle.            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x53                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : ShiftCnt - Shift right count (Valid range: 0 to 63)    **
**                                                                            **
** Parameters(in-out): Data     - Pointer to data which is to be modified     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ShiftBitRt_u64u8(uint64* const Data,
                                        const uint8 ShiftCnt)
{
  /*Data Right Shifted by ShiftCnt number of times*/
  *Data = (uint64)(*Data >> ShiftCnt);
}


/*******************************************************************************
** Traceability      : [cover parentID={0B7C8575-F856-420f-AFF6-B12B16FDDE87},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ShiftBitLt_u8u8                               **
**                     (                                                      **
**                       uint8* const Data,                                   **
**                       const uint8 ShiftCnt                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ShiftBitLt_u8u8 function shifts the bits of    **
**                     the Data parameter to the left by ShiftCnt count. The  **
**                     least significant bit (right-most bit) is replaced by a**
**                     0 bit and the most significant bit (left-most bit) is  **
**                     discarded for every single bit shift cycle.            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x56                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : ShiftCnt - Shift left count (Valid range: 0 to 7)      **
**                                                                            **
** Parameters(in-out): Data     - Pointer to data which is to be modified     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ShiftBitLt_u8u8(uint8* const Data,
                                       const uint8 ShiftCnt)
{
  /*Data Left Shifted by ShiftCnt number of times*/
  *Data = (uint8)(((uint32)(*Data)) << ShiftCnt);
}

/*******************************************************************************
** Traceability      : [cover parentID={736588AF-9605-4f3f-ABF0-B42841715F34},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ShiftBitLt_u16u8                              **
**                     (                                                      **
**                       uint16* const Data,                                  **
**                       const uint8 ShiftCnt                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ShiftBitLt_u16u8 function shifts the bits of   **
**                     the Data parameter to the left by ShiftCnt count. The  **
**                     least significant bit (right-most bit) is replaced by a**
**                     0 bit and the most significant bit (left-most bit) is  **
**                     discarded for every single bit shift cycle.            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x57                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : ShiftCnt - Shift left count (Valid range: 0 to 15)     **
**                                                                            **
** Parameters(in-out): Data     - Pointer to data which is to be modified     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ShiftBitLt_u16u8(uint16* const Data,
                                        const uint8 ShiftCnt)
{
  /*Data Left Shifted by ShiftCnt number of times*/
  *Data = (uint16)(((uint32) * Data) << ShiftCnt);
}


/*******************************************************************************
** Traceability      : [cover parentID={B6EAE094-DFFC-4671-8C5D-8B984A16D19A},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ShiftBitLt_u32u8                              **
**                     (                                                      **
**                       uint32* const Data,                                  **
**                       const uint8 ShiftCnt                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ShiftBitLt_u32u8 function shifts the bits of   **
**                     the Data parameter to the left by ShiftCnt count. The  **
**                     least significant bit (right-most bit) is replaced by a**
**                     0 bit and the most significant bit (left-most bit) is  **
**                     discarded for every single bit shift cycle.            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x58                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : ShiftCnt - Shift left count (Valid range: 0 to 31)     **
**                                                                            **
** Parameters(in-out): Data     - Pointer to data which is to be modified     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ShiftBitLt_u32u8(uint32* const Data,
                                        const uint8 ShiftCnt)
{
  /*Data Left Shifted by ShiftCnt number of times*/
  *Data = *Data << ShiftCnt;
}

/*******************************************************************************
** Traceability      : [cover parentID={6F99D19B-EAD6-4153-B3E4-87AE8238C4F9},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ShiftBitLt_u64u8                              **
**                     (                                                      **
**                       uint64* const Data,                                  **
**                       const uint8 ShiftCnt                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ShiftBitLt_u64u8 function shifts the bits of   **
**                     the Data parameter to the left by ShiftCnt count. The  **
**                     least significant bit (right-most bit) is replaced by a**
**                     0 bit and the most significant bit (left-most bit) is  **
**                     discarded for every single bit shift cycle.            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x59                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : ShiftCnt - Shift left count (Valid range: 0 to 63)     **
**                                                                            **
** Parameters(in-out): Data     - Pointer to data which is to be modified     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ShiftBitLt_u64u8(uint64* const Data,
                                        const uint8 ShiftCnt)
{
  /*Data Left Shifted by ShiftCnt number of times*/
  *Data = *Data << ShiftCnt;
}


/*******************************************************************************
** Traceability      : [cover parentID={387FE8EC-FBAE-49cc-B50F-7546ADFB4453},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_RotBitRt_u8u8                                 **
**                     (                                                      **
**                       uint8* const Data,                                   **
**                       const uint8 ShiftCnt                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_RotBitRt_u8u8 function rotates the bits of the **
**                     Data parameter to the right by ShiftCnt count. The     **
**                     least significant bit (right-most bit) is rotated to   **
**                     the most significant bit (left-most bit) location for  **
**                     every single bit shift cycle.                          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x5a                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : ShiftCnt - Shift count (Valid range: 0 to 7)           **
**                                                                            **
** Parameters(in-out): Data     - Pointer to data which is to be modified     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_RotBitRt_u8u8(uint8* const Data, const uint8 ShiftCnt)
{
  /*  Data is equal to addition of
      1)  Data Right Shifted by ShiftCnt number of times and
      2)  Data Left Shifted by ((Max Length or (Max Position +1))-ShiftCnt)
        number of times.
  */
  *Data = (uint8)(*Data >> ShiftCnt) +
          (uint8)((((uint32)(*Data)) <<
          ((uint8)(BFX_MAX_LENGTH_8BIT - ShiftCnt))));
}

/*******************************************************************************
** Traceability      : [cover parentID={C4C0C241-9623-4783-8A76-29186EF9430A},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_RotBitRt_u16u8                                **
**                     (                                                      **
**                       uint16* const Data,                                  **
**                       const uint8 ShiftCnt                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_RotBitRt_u16u8 function rotates the bits of the**
**                     Data parameter to the right by ShiftCnt count. The     **
**                     least significant bit (right-most bit) is rotated to   **
**                     the most significant bit (left-most bit) location for  **
**                     every single bit shift cycle.                          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x5b                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : ShiftCnt - Shift count (Valid range: 0 to 15)          **
**                                                                            **
** Parameters(in-out): Data     - Pointer to data which is to be modified     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_RotBitRt_u16u8(uint16* const Data, const uint8 ShiftCnt)
{
  /*  Data is equal to addition of
      1)  Data Right Shifted by ShiftCnt number of times and
      2)  Data Left Shifted by ((Max Length or (Max Position +1))-ShiftCnt)
        number of times.
  */
  *Data = (uint16)(*Data >> ShiftCnt) +
          (uint16)(((uint32) * Data) <<
          (uint8)(BFX_MAX_LENGTH_16BIT - ShiftCnt));
}

/*******************************************************************************
** Traceability      : [cover parentID={59403A4F-D8BE-4be8-A2B2-FDAE1EF0067E},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_RotBitRt_u32u8                                **
**                     (                                                      **
**                       uint32* const Data,                                  **
**                       const uint8 ShiftCnt                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_RotBitRt_u32u8 function rotates the bits of the**
**                     Data parameter to the right by ShiftCnt count. The     **
**                     least significant bit (right-most bit) is rotated to   **
**                     the most significant bit (left-most bit) location for  **
**                     every single bit shift cycle.                          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x5c                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : ShiftCnt - Shift count (Valid range: 0 to 31)          **
**                                                                            **
** Parameters(in-out): Data     - Pointer to data which is to be modified     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_RotBitRt_u32u8(uint32* const Data, const uint8 ShiftCnt)
{
  /*  Data is equal to addition of
      1)  Data Right Shifted by ShiftCnt number of times and
      2)  Data Left Shifted by ((Max Length or (Max Position +1))-ShiftCnt)
        number of times.
  */
  *Data = (*Data >> ShiftCnt) +
          (*Data << (uint8)(BFX_MAX_LENGTH_32BIT - ShiftCnt));
}

/*******************************************************************************
** Traceability      : [cover parentID={94873AEB-8BD4-49dd-8A9E-CD6C569581E4},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_RotBitRt_u64u8                                **
**                     (                                                      **
**                       uint64* const Data,                                  **
**                       const uint8 ShiftCnt                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_RotBitRt_u64u8 function rotates the bits of the**
**                     Data parameter to the right by ShiftCnt count. The     **
**                     least significant bit (right-most bit) is rotated to   **
**                     the most significant bit (left-most bit) location for  **
**                     every single bit shift cycle.                          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x5d                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : ShiftCnt - Shift count (Valid range: 0 to 63)          **
**                                                                            **
** Parameters(in-out): Data     - Pointer to data which is to be modified     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_RotBitRt_u64u8(uint64* const Data, const uint8 ShiftCnt)
{
  /*  Data is equal to addition of
      1)  Data Right Shifted by ShiftCnt number of times and
      2)  Data Left Shifted by ((Max Length or (Max Position +1))-ShiftCnt)
          number of times.
  */
  *Data = (*Data >> ShiftCnt) +
          (*Data << (uint8)(BFX_MAX_LENGTH_64BIT - ShiftCnt));
}

/*******************************************************************************
** Traceability      : [cover parentID={7453858F-E5CD-4335-B315-EDB428DBDF6E},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_RotBitLt_u8u8                                 **
**                     (                                                      **
**                       uint8* const Data,                                   **
**                       const uint8 ShiftCnt                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_RotBitLt_u8u8 function rotates the bits of the **
**                     Data parameter to the left by ShiftCnt count. The      **
**                     most significant bit (left-most bit) is rotated to     **
**                     the least significant bit (right-most bit) location for**
**                     every single bit shift cycle.                          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x60                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : ShiftCnt - Shift count (Valid range: 0 to 7)           **
**                                                                            **
** Parameters(in-out): Data     - Pointer to data which is to be modified     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_RotBitLt_u8u8(uint8* const Data, const uint8 ShiftCnt)
{
  /* Data is equal to addition of
     1)  Data Left Shifted by ShiftCnt number of times and
     2)  Data Right Shifted by (Max Length or (MaxPos+1))-ShiftCnt number of
         times.
  */
  *Data = (uint8)(((uint32) * Data) << ShiftCnt) +
          (uint8)(*Data >> (uint8)(BFX_MAX_LENGTH_8BIT - ShiftCnt));
}

/*******************************************************************************
** Traceability      : [cover parentID={E41BE5C3-5963-4b98-8C6D-6922239B0480},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_RotBitLt_u16u8                                **
**                     (                                                      **
**                       uint16* const Data,                                  **
**                       const uint8 ShiftCnt                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_RotBitLt_u16u8 function rotates the bits of the**
**                     Data parameter to the left by ShiftCnt count. The      **
**                     most significant bit (left-most bit) is rotated to     **
**                     the least significant bit (right-most bit) location for**
**                     every single bit shift cycle.                          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x61                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : ShiftCnt - Shift count (Valid range: 0 to 15)          **
**                                                                            **
** Parameters(in-out): Data     - Pointer to data which is to be modified     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_RotBitLt_u16u8(uint16* const Data, const uint8 ShiftCnt)
{
  /*  Data is equal to addition of
      1)  Data Left Shifted by ShiftCnt number of times and
      2)  Data Right Shifted by (Max Length or (MaxPos+1))-ShiftCnt number of
          times.
  */
  *Data = (uint16)(((uint32) * Data) << ShiftCnt) +
          (uint16)(*Data >> (uint8)(BFX_MAX_LENGTH_16BIT - ShiftCnt));
}

/*******************************************************************************
** Traceability      : [cover parentID={3FB7D5F3-2908-40f4-BB63-414010081D5B},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_RotBitLt_u32u8                                **
**                     (                                                      **
**                       uint32* const Data,                                  **
**                       const uint8 ShiftCnt                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_RotBitLt_u32u8 function rotates the bits of the**
**                     Data parameter to the left by ShiftCnt count. The      **
**                     most significant bit (left-most bit) is rotated to     **
**                     the least significant bit (right-most bit) location for**
**                     every single bit shift cycle.                          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x62                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : ShiftCnt - Shift count (Valid range: 0 to 31)          **
**                                                                            **
** Parameters(in-out): Data     - Pointer to data which is to be modified     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_RotBitLt_u32u8(uint32* const Data, const uint8 ShiftCnt)
{
  /*  Data is equal to addition of
      1)  Data Left Shifted by ShiftCnt number of times and
      2)  Data Right Shifted by (Max Length or (MaxPos+1))-ShiftCnt number of
        times.
  */
  *Data = (*Data << ShiftCnt) +
          (*Data >> (BFX_MAX_LENGTH_32BIT - ShiftCnt));
}

/*******************************************************************************
** Traceability      : [cover parentID={5F332609-8934-44a0-84AC-8B3E26E64A50},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_RotBitLt_u64u8                                **
**                     (                                                      **
**                       uint64* const Data,                                  **
**                       const uint8 ShiftCnt                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_RotBitLt_u64u8 function rotates the bits of the**
**                     Data parameter to the left by ShiftCnt count. The      **
**                     most significant bit (left-most bit) is rotated to     **
**                     the least significant bit (right-most bit) location for**
**                     every single bit shift cycle.                          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x63                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : ShiftCnt - Shift count (Valid range: 0 to 63)          **
**                                                                            **
** Parameters(in-out): Data     - Pointer to data which is to be modified     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_RotBitLt_u64u8(uint64* const Data, const uint8 ShiftCnt)
{
  /*  Data is equal to addition of
      1)  Data Left Shifted by ShiftCnt number of times and
      2)  Data Right Shifted by (Max Length or (MaxPos+1))-ShiftCnt number of
        times.
  */
  *Data = (*Data << ShiftCnt) +
          (*Data >> (BFX_MAX_LENGTH_64BIT - ShiftCnt));
}

/*******************************************************************************
** Traceability      : [cover parentID={C89A45E8-BE7B-446e-82E3-9E48109C33B8},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_PutBitsMask_u8u8u8                            **
**                     (                                                      **
**                       uint8* const Data,                                   **
**                       const uint8 Pattern,                                 **
**                       const uint8 Mask                                     **
**                      )                                                     **
**                                                                            **
** Description       : The Bfx_PutBitsMask_u8u8u8 function copies the bit     **
**                     pattern from the Pattern parameter into the Data       **
**                     parameter, for all the bit positions for which the     **
**                     logical status of bit in the Mask parameter is set to 1**
**                     The remaining bits of the Data parameter retain their  **
**                     original values.                                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
**                                                                            **
**                                                                            **
** Service ID        : 0x80                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : Pattern - Bit pattern to be set                        **
**                     Mask    - Mask value                                   **
**                                                                            **
** Parameters(in-out): Data    - Pointer to destination data which is to be   **
**                               modified                                     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_PutBitsMask_u8u8u8(uint8* const Data,
                                          const uint8 Pattern,
                                          const uint8 Mask)
{
  /*  Data is equal to Bitwise OR of
      1)  Bitwise AND of Data and complement of Mask and
      2)  Bitwise AND of Pattern and Mask.
  */
  *Data = (*Data & (uint8)(~Mask)) | (uint8)(Pattern & Mask);
}

/*******************************************************************************
** Traceability      : [cover parentID={C64BA5A6-2D83-4e88-BC3B-C438AF44C598},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_PutBitsMask_u16u16u16                         **
**                     (                                                      **
**                       uint16* const Data,                                  **
**                       const uint16 Pattern,                                **
**                       const uint16 Mask                                    **
**                      )                                                     **
**                                                                            **
** Description       : The Bfx_PutBitsMask_u16u16u16 function copies the bit  **
**                     pattern from the Pattern parameter into the Data       **
**                     parameter, for all the bit positions for which the     **
**                     logical status of bit in the Mask parameter is set to 1**
**                     The remaining bits of the Data parameter retain their  **
**                     original values.                                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
**                                                                            **
**                                                                            **
** Service ID        : 0x81                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : Pattern - Bit pattern to be set                        **
**                     Mask    - Mask value                                   **
**                                                                            **
** Parameters(in-out): Data    - Pointer to destination data which is to be   **
**                               modified                                     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_PutBitsMask_u16u16u16(uint16* const Data,
                                             const uint16 Pattern,
                                             const uint16 Mask)
{
  /*  Data is equal to Bitwise OR of
      1)  Bitwise AND of Data and complement of Mask and
      2)  Bitwise AND of Pattern and Mask.
  */
  *Data = (*Data & (uint16)(~Mask)) | (uint16)(Pattern & Mask);
}

/*******************************************************************************
** Traceability      : [cover parentID={FAE92A6F-8944-4af4-B092-1D45BDFC4ED9},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_PutBitsMask_u32u32u32                         **
**                     (                                                      **
**                       uint32* const Data,                                  **
**                       const uint32 Pattern,                                **
**                       const uint32 Mask                                    **
**                      )                                                     **
**                                                                            **
** Description       : The Bfx_PutBitsMask_u32u32u32 function copies the bit  **
**                     pattern from the Pattern parameter into the Data       **
**                     parameter, for all the bit positions for which the     **
**                     logical status of bit in the Mask parameter is set to 1**
**                     The remaining bits of the Data parameter retain their  **
**                     original values.                                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
**                                                                            **
**                                                                            **
** Service ID        : 0x82                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : Pattern - Bit pattern to be set                        **
**                     Mask    - Mask value                                   **
**                                                                            **
** Parameters(in-out): Data    - Pointer to destination data which is to be   **
**                               modified                                     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_PutBitsMask_u32u32u32(uint32* const Data,
                                             const uint32 Pattern,
                                             const uint32 Mask)
{
  /* Data is equal to Bitwise OR of
     1)  Bitwise AND of Data and complement of Mask and
     2)  Bitwise AND of Pattern and Mask.
  */
  *Data = (*Data & (~Mask)) | (Pattern & Mask);
}


/*******************************************************************************
** Traceability      : [cover parentID={139899A0-3482-44e3-B0AA-9DBE48937846},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_PutBitsMask_u64u64u64                         **
**                     (                                                      **
**                       uint64* const Data,                                  **
**                       const uint64 Pattern,                                **
**                       const uint64 Mask                                    **
**                      )                                                     **
**                                                                            **
** Description       : The Bfx_PutBitsMask_u64u64u64 function copies the bit  **
**                     pattern from the Pattern parameter into the Data       **
**                     parameter, for all the bit positions for which the     **
**                     logical status of bit in the Mask parameter is set to 1**
**                     The remaining bits of the Data parameter retain their  **
**                     original values.                                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
**                                                                            **
**                                                                            **
** Service ID        : 0x83                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : Pattern - Bit pattern to be set                        **
**                     Mask    - Mask value                                   **
**                                                                            **
** Parameters(in-out): Data    - Pointer to destination data which is to be   **
**                               modified                                     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_PutBitsMask_u64u64u64(uint64* const Data,
                                             const uint64 Pattern,
                                             const uint64 Mask)
{
  /* Data is equal to Bitwise OR of
     1)  Bitwise AND of Data and complement of Mask and
     2)  Bitwise AND of Pattern and Mask.
  */
  *Data = (*Data & (~Mask)) | (Pattern & Mask);
}
/*******************************************************************************
**                       Global Function Declarations                         **
*******************************************************************************/

/*******************************************************************************
** Traceability      : [cover parentID  ]                                     **
**                                                                            **
** Syntax            : void Bfx_GetVersionInfo                                **
**                     (                                                      **
**                       Std_VersionInfoType* const Versioninfo               **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_GetVersionInfo returns the version information **
**                     of BFX library.                                        **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0xff                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : None                                                   **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : Versioninfo - Pointer to where to store the version    **
**                     information of this module                             **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
extern void Bfx_GetVersionInfo(Std_VersionInfoType * const Versioninfo);

/*******************************************************************************
**                            LOW Level Driver Definitions                    **
*******************************************************************************/

/*******************************************************************************
**                            LOW Level Driver Definitions                    **
*******************************************************************************/

/*[cover parentID={826C08F0-0107-42bf-9DCC-FABBFE7F9A19}]
Code Memory section executable by all cores
[/cover]*/
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
Memory mapping support
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
Code Memory section naming as per AS
[/cover]*/
#define BFX_STOP_SEC_CODE_ASIL_B_GLOBAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*[cover parentID={6D3BA711-CAAB-4a34-82CC-822B613FCB90}]
MemMap_h file to be developed by user
[/cover]*/
#include "Bfx_MemMap.h"

#endif /* BFX_H */

