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
**  FILENAME     : Bfx_Local.c                                                **
**                                                                            **
**  VERSION      : 6.0.0                                                      **
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
**  TRACEABILITY :[cover parentID={ECC64048-9733-403e-B492-A04F7AD3A541}]     **
**                                                                            **
**  DESCRIPTION  : BFX library local source file                              **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of BFX library,                          **
**                     AUTOSAR Release 4.2.2 and 4.4.0                        **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#ifndef BFX_LOCAL_H
#define BFX_LOCAL_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*[cover parentID={DC0B4213-1D31-4256-BAD3-DC0CD7F025C4}]
File Structure
[/cover]*/

/*[cover parentID={43E56F75-50B4-4b3f-8C6C-13912D06E525}]*/
/*AUTOSAR data types are used instead of native C data types*/
#include "Std_Types.h"
/*[/cover] */

/* [cover parentID={2315CEFB-5155-410c-AA89-F72E519F9FBE}]
No configuration options. Hence no configuration file is included.
[/cover] */

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/
/*[cover parentID={CC8A1B89-5F19-4485-96B6-CE3DD698F100}]
The BFX library is implemented as ASIL B module.There is no ASIL decomposition
done for the BFX library.
[/cover]*/
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
/*[cover parentID={6D3BA711-CAAB-4a34-82CC-822B613FCB90}]
MemMap_h file to be developed by user
[/cover]*/
#include "Bfx_MemMap.h"

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
/*Macros to used as immediate data in assembly function*/
/*Typecasting is avoided as some compiler may not support typecasting for
 immediate value*/
/* Default width of the bit handling request - 1 bit */
#define BFX_DEFAULT_WIDTH               ((uint8)1)

/* Masks all bits except LSB to determine whether the value is even or odd */
#define BFX_MASK_ALL_EXCEPT_LSB         (0x00000001)

/* Holds maximum length of 64-bit data */
#define BFX_DOUBLE_WORD_LENGTH               (64)
/* Holds maximum length of 32-bit data */
#define BFX_WORD_LENGTH                      (32)
/* Minimum valid bit position */
#define BFX_MIN_POS                          (0)

/* Minimum valid bit position of the lower word */
#define BFX_MIN_POS_LOWER_WORD          ((uint8)0)
/* Minimum valid bit position of the higher word */
#define BFX_MIN_POS_HIGHER_WORD         ((uint8)32)

/* Holds maximum length of 8-bit data */
#define BFX_MAX_LENGTH_8BIT             ((uint8)8)
/* Holds maximum length of 16-bit data */
#define BFX_MAX_LENGTH_16BIT            ((uint8)16)
/* Holds maximum length of 32-bit data */
#define BFX_MAX_LENGTH_32BIT            ((uint8)32)
/* Holds maximum length of 64-bit data */
#define BFX_MAX_LENGTH_64BIT            ((uint8)64)

#ifdef _DIABDATA_C_TRICORE_
#if (_DIABDATA_C_TRICORE_ == 1U)
/* ASM Macro definition for inserting 8 bits */
/* This is implemented differently from other compilers as Windriver supports
   inline assembly as function like asm macro
*/
__asm volatile void BFX_INSERT8BITS_DCC(uint8 * const TargetPtr,
                                                  const uint8 SourceVal,
                                                  const uint8 Pos,
                                                  const uint8 Width)
{
%reg TargetPtr, SourceVal, Pos, Width;
!
  ld.bu %d11, [TargetPtr]0
  mov %d12, Pos
  mov %d13, Width
  insert %d11, %d11, SourceVal, %e12
  st.b [TargetPtr]0, %d11
}

/* ASM Macro definition for inserting 16 bits */
/* This is implemented differently from other compilers as Windriver supports
   inline assembly as function like asm macro
 */
__asm volatile void BFX_INSERT16BITS_DCC(uint16 * const TargetPtr,
                                                   const uint16 SourceVal,
                                                   const uint8 Pos,
                                                   const uint8 Width)
{
%reg TargetPtr, SourceVal, Pos, Width;
!
  ld.hu %d11, [TargetPtr]0
  mov %d12, Pos
  mov %d13, Width
  insert %d11, %d11, SourceVal, %e12
  st.h [TargetPtr]0, %d11
}

/* ASM Macro definition for inserting 32 bits */
/* This is implemented differently from other compilers as Windriver supports
   inline assembly as function like asm macro
 */
__asm volatile void BFX_INSERT32BITS_DCC(uint32 * const TargetPtr,
                                                   const uint32 SourceVal,
                                                   const uint8 Pos,
                                                   const uint8 Width)
{
%reg TargetPtr, SourceVal, Pos, Width;
!
  ld.w %d11, [TargetPtr]0
  mov %d12, Pos
  mov %d13, Width
  insert %d11, %d11, SourceVal, %e12
  st.w [TargetPtr]0, %d11
}

/* ASM Macro definition for extracting 32 bits */
/* This is implemented differently from other compilers as Windriver supports
   inline assembly as function like asm macro
 */

__asm volatile uint32 BFX_EXTRACTBITS_DCC(const uint32 SourceVal,
                                                    const uint8 Pos,
                                                    const uint8 Width)
{
%reg SourceVal, Pos, Width;
!"%d2"
  mov %d12, Pos
  mov %d13, Width
  extr.u %d2, SourceVal ,%e12
}


/* ASM Macro definition for odd parity check */
/* This is implemented differently from other compilers as Windriver supports
 * inline assembly as function like asm macro
 */
__asm volatile uint8 BFX_PARITY_DCC(const uint32 Value)
{
%reg Value;
!"%d2"
  popcnt.w %d14, Value
  and %d2, %d14, BFX_MASK_ALL_EXCEPT_LSB
}

/* ASM Macro definition for odd parity check */
/* This is implemented differently from other compilers as Windriver supports
 * inline assembly as function like asm macro
 */
__asm volatile uint8 BFX_PARITY64BITS_DCC(const uint64 Value)
{
%reg Value;
!"%d2"
  popcnt.w %d12, Value!L
  popcnt.w %d13, Value!H
  xor.t   %d2,%d12, BFX_MIN_POS, %d13, BFX_MIN_POS
}

/* ASM Macro definition for Extracting 64 bits when Pos != BFX_MIN_POS &
   Width > BFX_WORD_LENGTH */
/* This is implemented differently from other compilers as Windriver supports
   inline assembly as function like asm macro
*/
__asm volatile uint64 BFX_EXTRACT64BITS_DCC_PosNEQ0WidthGT32(
                                                    const uint64 SourceVal,
                                                    const uint8 Pos,
                                                    const uint8 Width)
{
  /*Pos != BFX_MIN_POS & Width > BFX_WORD_LENGTH*/

%reg SourceVal, Pos, Width;
!"%d2" "%d3"
  rsub %d11,Pos,BFX_WORD_LENGTH
  /*Extract the 32 bits starting from Pos to the lower word using
    dextr and the remaining bits to the higher word using extr*/
  dextr %d2,SourceVal!H,SourceVal!L,%d11
  /*Width=width-32=E[d][36:32]=d13[4:0]*/
  mov %d13,Width
  /*Pos=pos-32=E[d][4:0]=d12[4:0]*/
  mov %d12,Pos
  extr.u %d3,SourceVal!H,%e12
}

/* ASM Macro definition for Extracting 64 bits when Width < BFX_WORD_LENGTH &
   Pos >= BFX_WORD_LENGTH */
/* This is implemented differently from other compilers as Windriver supports
   inline assembly as function like asm macro
 */
__asm volatile uint64 BFX_EXTRACT64BITS_DCC_PosGTE32WidthLT32(
                                                    const uint64 SourceVal,
                                                    const uint8 Pos,
                                                    const uint8 Width)
{
  /*Width < BFX_WORD_LENGTH and Pos >= BFX_WORD_LENGTH*/

%reg SourceVal, Pos, Width;
!"%d2" "%d3"
  /*Since Width < 32 but Pos >= 32 extracted result is written
    only to the higher word. Hence the lower word is initialised
    with 0 to clear the random values it may have.*/
  mov %d3,BFX_MIN_POS
  /*pos=Pos-32=E[d][4:0]=d12[4:0]*/
  mov %d12,Pos
  /*width=Width=E[d][36:32]=d13[4:0]*/
  mov %d13,Width
  /*Extract partially into the higher word using extr*/
  extr.u %d2,SourceVal!H,%e12
 }

/* ASM Macro definition for Extracting 64 bits when Width == BFX_WORD_LENGTH,
    Pos != BFX_WORD_LENGTH or  BFX_MIN_POS*/
/* This is implemented differently from other compilers as Windriver supports
   inline assembly as function like asm macro
 */
__asm volatile uint64 BFX_EXTRACT64BITS_DCC_PosNEQ32Or0WidthEQ32(
                                                    const uint64 SourceVal,
                                                    const uint8 Pos)
{
  /*Width == BFX_WORD_LENGTH, Pos != BFX_WORD_LENGTH or  BFX_MIN_POS*/

%reg SourceVal, Pos;
!"%d2" "%d3"
  mov %d3,BFX_MIN_POS
  rsub %d12,Pos,BFX_WORD_LENGTH
  /*Extract the entire 32 bits using dextr.*/
  dextr %d2,SourceVal!H,SourceVal!L,%d12
}

/* ASM Macro definition for Extracting 64 bits when Pos = BFX_MIN_POS
   & Width > BFX_WORD_LENGTH*/
/* This is implemented differently from other compilers as Windriver supports
   inline assembly as function like asm macro
 */
__asm volatile uint64 BFX_EXTRACT64BITS_DCC_PosEQ0WidthGT32(
                                                    const uint64 SourceVal,
                                                    const uint8 Width)
{
  /*Pos = BFX_MIN_POS & Width > BFX_WORD_LENGTH*/

%reg SourceVal, Width;
!"%d2" "%d3"
  /*Extract the entire lower word using mov and the remaining
    bits using extr to the upper word.*/
  mov %d2,SourceVal!L
  mov %d12,BFX_MIN_POS
  /*For extr: width=Width-32=E[d][36:32]=d13[4:0]*/
  mov %d13,Width
  extr.u %d3,SourceVal!H,%e12
}

/* ASM Macro definition for Extracting 64 bits when Width = BFX_WORD_LENGTH
   & Pos = BFX_WORD_LENGTH or BFX_MIN_POS*/
/* This is implemented differently from other compilers as Windriver supports
   inline assembly as function like asm macro
 */
__asm volatile uint64 BFX_EXTRACT64BITS_DCC_PosEQ32Or0WidthEQ32(
                                                    const uint64 SourceVal,
                                                    const uint8 Pos)
{
  /*Width = BFX_WORD_LENGTH and Pos = BFX_WORD_LENGTH or BFX_MIN_POS*/

%reg SourceVal, Pos;
!"%d2" "%d3"
  /*Since Width = 32  extracted result is written
    only to the lower word. Hence the higher word is initialised
    with 0 to clear the random values it may have.*/
  mov %d3,BFX_MIN_POS
  /*Select the lower word if Pos is 0 or the higher word
    if Pos is 32 using sel and mov it to the lower word of the Result*/
  sel %d2,Pos,SourceVal!H,SourceVal!L
}

/* ASM Macro definition for Extracting 64 bits when Pos< BFX_WORD_LENGTH,
   Width< BFX_WORD_LENGTH & Pos+Width< BFX_WORD_LENGTH*/
/* This is implemented differently from other compilers as Windriver supports
   inline assembly as function like asm macro
 */
__asm volatile uint64 BFX_EXTRACT64BITS_DCC_PosLT32WidthLT32SumLT32(
                                                    const uint64 SourceVal,
                                                    const uint8 Pos,
                                                    const uint8 Width)
{
  /*Pos< BFX_WORD_LENGTH, Width< BFX_WORD_LENGTH & Pos+Width< BFX_WORD_LENGTH*/

%reg SourceVal, Pos, Width;
!"%d2" "%d3"
  /*Since Width < 32  extracted result is written
    only to the lower word. Hence the higher word is initialised
    with 0 to clear the random values it may have.*/
  mov %d3,BFX_MIN_POS
  /*For insert: pos=Pos and width=Width*/
  mov %d12,Pos
  mov %d13,Width
  /*Extract data partially from the lower word*/
  extr.u %d2,SourceVal!L,%e12
}

/* ASM Macro definition for Extracting 64 bits when Pos<BFX_WORD_LENGTH,
   Width<BFX_WORD_LENGTH & Pos+Width>= BFX_WORD_LENGTH)*/
/* This is implemented differently from other compilers as Windriver supports
   inline assembly as function like asm macro
 */
__asm volatile uint64 BFX_EXTRACT64BITS_DCC_PosLT32WidthLT32SumGTE32(
                                                    const uint64 SourceVal,
                                                    const uint8 Pos,
                                                    const uint8 Width)
{
  /*Pos<BFX_WORD_LENGTH, Width<BFX_WORD_LENGTH & Pos+Width>= BFX_WORD_LENGTH)*/

%reg SourceVal, Pos, Width;
!"%d2" "%d3"
  /*Since Width < 32  extracted result is written
    only to the lower word. Hence the higher word is initialised
    with 0 to clear the random values it may have.*/
  mov %d3,BFX_MIN_POS
  rsub %d13,Pos,BFX_WORD_LENGTH
  /*Extract 32 bits starting from Pos using dextr and
    then extract the Width bits from the dextracted word using extr*/
  dextr %d11,SourceVal!H,SourceVal!L,%d13
  /*For extr: pos=0=E[d][4:0]=d12[4:0]*/
  mov %d12,BFX_MIN_POS
  /*For extr: width=Width=E[d][36:32]=d13[4:0]*/
  mov %d13,Width
  /*Extract width bits from dextracted word*/
  extr.u %d2,%d11,%e12
}

/* ASM Macro definition for Insertion of  64 bits when Width>32
   & Pos+Width = 64)*/
/* This is implemented differently from other compilers as Windriver supports
   inline assembly as function like asm macro
 */
__asm volatile uint64 BFX_INSERT64BITS_DCC_WidthGT32SumEQ64(
                                                   uint64 * const TargetPtr,
                                                   const uint64 SourceVal,
                                                   const uint8 Pos,
                                                   const uint8 Width)
{
  /*Width > BFX_WORD_LENGTH and Pos + Width = BFX_DOUBLE_WORD_LENGTH*/

%reg TargetPtr, SourceVal, Pos, Width;
!
  /*Load the 64-bit data*/
  ld.d %e10,[TargetPtr]0
  /*Insert partially into the lower word using insert and then
    insert into the entire higher word using dextr as
    the remaining bits are to be copied from both the words
    of SourceVal*/
  /*For insert: pos=Pos=E[d][4:0]=d12[4:0]*/
  mov %d12,Pos
  /*For insert: width=32-Pos=Width-32=Width*/
  mov %d13,Width
  insert %d10,%d10,SourceVal!L,%e12
  /*For dextr: 32-pos=32-(32-pos)=pos*/
  dextr %d11,SourceVal!H,SourceVal!L,Pos
  /*Store the 64-bit data*/
  st.d [TargetPtr]0,%e10
}

/* ASM Macro definition for Insertion of 64 bits when Width = 32 & Pos = 32)*/
/* This is implemented differently from other compilers as Windriver supports
   inline assembly as function like asm macro
 */
__asm volatile uint64 BFX_INSERT64BITS_DCC_PosEQ32WidthEQ32(
                                                   uint64 * const TargetPtr,
                                                   const uint64 SourceVal)
{
  /*Width = BFX_WORD_LENGTH and Pos = BFX_WORD_LENGTH*/

%reg TargetPtr, SourceVal;
!
  /*Load the 64-bit data*/
  ld.d %e10,[TargetPtr]0
  /*Insert into the entire higher word using mov*/
  mov %d11,SourceVal!L
  /*Store the 64-bit data*/
  st.d [TargetPtr]0,%e10
}

/* ASM Macro definition for Insertion of 64 bits when Width>32, Pos+Width != 64
   & Pos = 0)*/
/* This is implemented differently from other compilers as Windriver supports
   inline assembly as function like asm macro
 */
__asm volatile uint64 BFX_INSERT64BITS_DCC_PosEQ0WidthGT32SumLT64(
                                                   uint64 * const TargetPtr,
                                                   const uint64 SourceVal,
                                                   const uint8 Width)
{
  /*Width > BFX_WORD_LENGTH, Pos + Width != BFX_DOUBLE_WORD_LENGTH and
    Pos = BFX_MIN_POS*/

%reg TargetPtr, SourceVal, Width;
!
  /*Load the 64-bit data*/
  ld.d %e10,[TargetPtr]0
  /*Insert into the entire lower word using mov and then
   insert partially into the higher word using insert*/
  mov %d10,SourceVal!L
  /*For insert: pos=0=E[d][4:0]=d12[4:0]*/
  mov %d12,BFX_MIN_POS
  /*For insert: width=Width-32=E[d][36:32]=%d13[4:0]*/
  mov %d13,Width
  insert %d11,%d11,SourceVal!H,%e12
  /*Store the 64-bit data*/
  st.d [TargetPtr]0,%e10
}

/* ASM Macro definition for Insertion of 64 bits when Pos > 0, Width > 32
   & Pos+Width < 64*/
/* This is implemented differently from other compilers as Windriver supports
   inline assembly as function like asm macro
 */
__asm volatile uint64 BFX_INSERT64BITS_DCC_PosGT0SumLT64(
                                                   uint64 * const TargetPtr,
                                                   const uint64 SourceVal,
                                                   const uint8 Pos,
                                                   const uint8 Width)
{
  /*Pos > BFX_MIN_POS and Width > BFX_WORD_LENGTH but
  Pos+Width < BFX_DOUBLE_WORD_LENGTH*/

%reg TargetPtr, SourceVal, Pos, Width;
!
  /*Load the 64-bit data*/
  ld.d %e10,[TargetPtr]0
  /*Insert partially into the lower word using insert and
    insert partially into the higher word using dextr and insert
    as the remaining bits to be copied are from both the words
    of SourceVal but less than 32 bits*/
  /*For dextr: 32-pos=32-(32-Pos)=Pos*/
  dextr %d14,SourceVal!H,SourceVal!L,Pos
  /*For insert: pos=0=E[d][4:0]=d12[4:0]*/
  mov %d12,BFX_WORD_LENGTH
  /*For insert: width=Width-(32-Pos)=(Pos+Width)-32=E[d][36:32]=d13[4:0]*/
  add %d13,Pos,Width
  insert %d11,%d11,%d14,%e12
  /*For insert: pos=Pos*/
  mov %d12,Pos
  /*For insert: width=32-Pos*/
  rsub %d13,Pos,BFX_WORD_LENGTH
  insert %d10,%d10,SourceVal!L,%e12
  /*Store the 64-bit data*/
  st.d [TargetPtr]0,%e10
}


/* ASM Macro definition for Insertion of 64 bits when Width < 32 but Pos >= 32*/
/* This is implemented differently from other compilers as Windriver supports
   inline assembly as function like asm macro
 */
__asm volatile uint64 BFX_INSERT64BITS_DCC_PosGTE32WidthLT32(
                                                   uint64 * const TargetPtr,
                                                   const uint64 SourceVal,
                                                   const uint8 Pos,
                                                   const uint8 Width)
{
  /* Width < BFX_WORD_LENGTH but Pos >= BFX_WORD_LENGTH */

%reg TargetPtr, SourceVal, Pos, Width;
!
  /*Load the 64-bit data*/
  ld.d %e10,[TargetPtr]0
  /*Insert partially into the higher word using insert*/
  /*For insert: pos=Pos-32=Pos=E[d][4:0]=d12[4:0] and width=Width*/
  mov %d12,Pos
  mov %d13,Width
  insert %d11,%d11,SourceVal!L,%e12
  /*Store the 64-bit data*/
  st.d [TargetPtr]0,%e10
}

/* ASM Macro definition for Insertion of 64 bits when Width = 32 &
   Pos+Width <= 32 (Pos = 0)*/
/* This is implemented differently from other compilers as Windriver supports
   inline assembly as function like asm macro
*/
__asm volatile uint64 BFX_INSERT64BITS_DCC_PosEQ0WidthEQ32(
                                                   uint64 * const TargetPtr,
                                                   const uint64 SourceVal)
{
  /*Width = BFX_WORD_LENGTH & Pos+Width <= BFX_WORD_LENGTH (Pos = BFX_MIN_POS)*/

%reg TargetPtr, SourceVal;
!
  /*Load the 64-bit data*/
  ld.d %e10,[TargetPtr]0
  /*Insert into the entire lower word using mov*/
  mov %d10,SourceVal!L
  /*Store the 64-bit data*/
  st.d [TargetPtr]0,%e10
}

/* ASM Macro definition for Insertion of 64 bits when Width<32 & Pos<32*/
/* This is implemented differently from other compilers as Windriver supports
   inline assembly as function like asm macro
 */
__asm volatile uint64 BFX_INSERT64BITS_DCC_PosLT32WidthLT32SumLT32(
                                                   uint64 * const TargetPtr,
                                                   const uint64 SourceVal,
                                                   const uint8 Pos,
                                                   const uint8 Width)
{
  /*Width<BFX_WORD_LENGTH & Pos<BFX_WORD_LENGTH*/

%reg TargetPtr, SourceVal, Pos, Width;
!
  /*Load the 64-bit data*/
  ld.d %e10,[TargetPtr]0
  /*Insert partially into the lower word using insert*/
  /*For insert: pos=Pos and width=Width*/
  mov %d12,Pos
  mov %d13,Width
  insert %d10,%d10,SourceVal!L,%e12
  /*Store the 64-bit data*/
  st.d [TargetPtr]0,%e10
}

#endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
#endif /* _DIABDATA_C_TRICORE_ */

/*******************************************************************************
**                         User Mode Macros                                   **
*******************************************************************************/

/*[cover parentID={C9E9BEC9-F29C-4330-920D-618869AE79FD}]
User Mode macros not required
[/cover]*/

/******************************************************************************/

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/


LOCAL_INLINE void Bfx_lInsert8Bits(uint8 * const TargetPtr,
                                   const uint8 SourceVal,
                                   const uint8 Pos,
                                   const uint8 Width);
LOCAL_INLINE void Bfx_lInsert16Bits(uint16 * const TargetPtr,
                                    const uint16 SourceVal,
                                    const uint8 Pos,
                                    const uint8 Width);
LOCAL_INLINE void Bfx_lInsert32Bits(uint32* const TargetPtr,
                                    const uint32 SourceVal,
                                    const uint8 Pos,
                                    const uint8 Width);
LOCAL_INLINE void Bfx_lInsert64Bits(uint64* const TargetPtr,
                                    const uint64 SourceVal,
                                    const uint8 Pos,
                                    const uint8 Width);
LOCAL_INLINE void Bfx_lInsWidthGT32SumEQ64(uint64* const TargetPtr,
                                    const uint64 SourceVal,
                                    const uint8 Pos,
                                    const uint8 Width);
LOCAL_INLINE void Bfx_lInsPosEQ32WidthEQ32(uint64* const TargetPtr,
                                    const uint64 SourceVal);
LOCAL_INLINE void Bfx_lInsPosEQ0WidthGT32SumLT64(uint64* const TargetPtr,
                                                 const uint64 SourceVal,
                                                 const uint8 Width);
LOCAL_INLINE void Bfx_lInsPosGT0LT32SumGT32LT64(uint64* const TargetPtr,
                                                 const uint64 SourceVal,
                                                 const uint8 Pos,
                                                 const uint8 Width);
LOCAL_INLINE void Bfx_lInsPosGTE32WidthLT32(uint64* const TargetPtr,
                                            const uint64 SourceVal,
                                            const uint8 Pos,
                                            const uint8 Width);
LOCAL_INLINE void Bfx_lInsPosEQ0WidthEQ32(uint64* const TargetPtr,
                                          const uint64 SourceVal);
LOCAL_INLINE void Bfx_lInsPosLT32WidthLT32SumLTE32(uint64* const TargetPtr,
                                                  const uint64 SourceVal,
                                                  const uint8 Pos,
                                                  const uint8 Width);
LOCAL_INLINE uint32 Bfx_lExtractBits(const uint32 Value,
                                     const uint8 Pos,
                                     const uint8 Width);
LOCAL_INLINE uint64 Bfx_lExtract64Bits(const uint64 Value,
                                     const uint8 Pos,
                                     const uint8 Width);
LOCAL_INLINE uint64 Bfx_lExtPosNEQ0WidthGT32(const uint64 Value,
                                             const uint8 Pos,
                                             const uint8 Width);
LOCAL_INLINE uint64 Bfx_lExtPosGTE32WidthLT32(const uint64 Value,
                                             const uint8 Pos,
                                             const uint8 Width);
LOCAL_INLINE uint64 Bfx_lExtPosNEQ32Or0WidthEQ32(const uint64 Value,
                                                 const uint8 Pos);
LOCAL_INLINE uint64 Bfx_lExtPosEQ0WidthGT32(const uint64 Value,
                                             const uint8 Width);
LOCAL_INLINE uint64 Bfx_lExtPosEQ32Or0WidthEQ32(const uint64 Value,
                                                const uint8 Pos);
LOCAL_INLINE uint64 Bfx_lExtPosLT32WidthLT32SumLT32(const uint64 Value,
                                                    const uint8 Pos,
                                                    const uint8 Width);
LOCAL_INLINE uint64 Bfx_lExtPosLT32WidthLT32SumGTE32(const uint64 Value,
                                                     const uint8 Pos,
                                                     const uint8 Width);
LOCAL_INLINE uint8 Bfx_lParity(const uint32 Value);
LOCAL_INLINE uint8 Bfx_lParity64Bits(const uint64 Value);


/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/
/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
/******************************************************************************/

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/

/*******************************************************************************
** Traceability      : [cover parentID={B07BF891-FFAF-4c8d-BFBE-CDE10E99D329},**
**                                     {44B965C9-ADC0-4ebd-BF53-2C409B6CC3F7}]**
**                                                                            **
**                                                                            **
** Syntax            : void Bfx_lInsert8Bits                                  **
**                     (                                                      **
**                       uint8 * const TargetPtr,                             **
**                       const uint8 SourceVal,                               **
**                       const uint8 Pos,                                     **
**                       const uint8 Width                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_lInsert8Bits function copies the bits from the **
**                     SourceVal parameter starting from 0 bit position for   **
**                     Width number of bits into the memory location pointed  **
**                     to by TargetPtr parameter at the bit positions starting**
**                     from Pos bit position for Width number of bits.        **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : None                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the function                    **
**                                                                            **
** Parameters (in)   : SourceVal - Source Data                                **
**                     Pos       - Start bit position (Valid range: 0 to 7 )  **
**                     Width     - Bit field length                           **
**                                (Valid range: 1 to (8-Pos))                 **
**                                                                            **
** Parameters(in-out): TargetPtr - Pointer to data which is to be modified    **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
LOCAL_INLINE void Bfx_lInsert8Bits(uint8 * const TargetPtr,
                                   const uint8 SourceVal,
                                   const uint8 Pos,
                                   const uint8 Width)
{
  #ifdef _TASKING_C_TRICORE_
  #if (_TASKING_C_TRICORE_ == 1U)
  __asm("ld.bu d11,[%0]""\n\t" \
        "mov d12,%2""\n\t" \
        "mov d13,%3""\n\t" \
        "insert d11,d11,%1,e12""\n\t" \
        "st.b [%0],d11" \
        : \
        : "a"(TargetPtr), "d" (SourceVal), "d" (Pos), "d" (Width) \
        : "d11", "d12", "d13");
  #endif /* #if (_TASKING_C_TRICORE_ == 1U) */
  #endif /* _TASKING_C_TRICORE_ */

  #ifdef _GNU_C_TRICORE_
  #if (_GNU_C_TRICORE_ == 1U)
  __asm__("ld.bu %%d11,[%0]""\n\t" \
          "mov %%d12,%2""\n\t" \
          "mov %%d13,%3""\n\t" \
          "insert %%d11,%%d11,%1,%%e12""\n\t" \
          "st.b [%0],%%d11" \
          : \
          : "a"(TargetPtr), "d" (SourceVal), "d" (Pos), "d" (Width) \
          : "d11", "d12", "d13", "memory");
  #endif /* #if (_GNU_C_TRICORE_ == 1U) */
  #endif /* _GNU_C_TRICORE_ */

  #ifdef _DIABDATA_C_TRICORE_
  #if (_DIABDATA_C_TRICORE_ == 1U)
  BFX_INSERT8BITS_DCC(TargetPtr, SourceVal, Pos, Width);
  #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
  #endif

  #ifdef _GHS_C_TRICORE_
  #if (_GHS_C_TRICORE_ == 1U)
  __asm ("ld.bu %%d11,[%0]""\n\t" \
         "mov %%d12,%2""\n\t" \
         "mov %%d13,%3""\n\t" \
         "insert %%d11,%%d11,%1,%%e12""\n\t" \
         "st.b [%0],%%d11" \
         : \
         : "a"(TargetPtr), "d" (SourceVal), "d" (Pos), "d" (Width) \
         : "d11", "d12", "d13");
  #endif /* #if (_GHS_C_TRICORE_ == 1U) */
  #endif /* _GHS_C_TRICORE_ */

  #if ((!defined(_TASKING_C_TRICORE_)) && (!defined(_GNU_C_TRICORE_)) &&\
       (!defined(_DIABDATA_C_TRICORE_)) && (!defined(_GHS_C_TRICORE_)))
  #error Unsupported compiler configured!
  #endif

  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
  /* MISRA2012_RULE_8_13_JUSTIFICATION: Parameter are updated via assembly
     instruction, hence cannot be passed as const.*/
}

/*******************************************************************************
** Traceability      : [cover parentID={D67AFC87-A469-4e5f-BC5E-6D01F9CF0443},**
**                                     {44B965C9-ADC0-4ebd-BF53-2C409B6CC3F7}]**
**                                                                            **
**                                                                            **
** Syntax            : void Bfx_lInsert16Bits                                 **
**                     (                                                      **
**                       uint16 * const TargetPtr,                            **
**                       const uint16 SourceVal,                              **
**                       const uint8 Pos,                                     **
**                       const uint8 Width                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_lInsert16Bits function copies the bits from the**
**                     SourceVal parameter starting from 0 bit position for   **
**                     Width number of bits into the memory location pointed  **
**                     to by TargetPtr parameter at the bit positions starting**
**                     from Pos bit position for Width number of bits.        **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : None                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the function                    **
**                                                                            **
** Parameters (in)   : SourceVal - Source Data                                **
**                     Pos       - Start bit position (Valid range: 0 to 15)  **
**                     Width     - Bit field length                           **
**                                 (Valid range: 1 to (16-Pos))               **
**                                                                            **
** Parameters(in-out): TargetPtr - Pointer to data which is to be modified    **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
LOCAL_INLINE void Bfx_lInsert16Bits(uint16 * const TargetPtr,
                                    const uint16 SourceVal,
                                    const uint8 Pos,
                                    const uint8 Width)
{
  #ifdef _TASKING_C_TRICORE_
  #if (_TASKING_C_TRICORE_ == 1U)
  __asm("ld.hu d11,[%0]""\n\t" \
        "mov d12,%2""\n\t" \
        "mov d13,%3""\n\t" \
        "insert d11,d11,%1,e12""\n\t" \
        "st.h [%0],d11" \
        : \
        : "a"(TargetPtr), "d" (SourceVal), "d" (Pos), "d" (Width) \
        : "d11", "d12", "d13");
  #endif /* #if (_TASKING_C_TRICORE_ == 1U) */
  #endif /* _TASKING_C_TRICORE_ */

  #ifdef _GNU_C_TRICORE_
  #if (_GNU_C_TRICORE_ == 1U)
  __asm__("ld.hu %%d11,[%0]""\n\t" \
          "mov %%d12,%2""\n\t" \
          "mov %%d13,%3""\n\t" \
          "insert %%d11,%%d11,%1,%%e12""\n\t" \
          "st.h [%0],%%d11" \
          : \
          : "a"(TargetPtr), "d" (SourceVal), "d" (Pos), "d" (Width) \
          : "d11", "d12", "d13", "memory");
  #endif /* #if (_GNU_C_TRICORE_ == 1U) */
  #endif /* _GNU_C_TRICORE_ */

  #ifdef _DIABDATA_C_TRICORE_
  #if (_DIABDATA_C_TRICORE_ == 1U)
  BFX_INSERT16BITS_DCC(TargetPtr, SourceVal, Pos, Width);
  #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
  #endif

  #ifdef _GHS_C_TRICORE_
  #if (_GHS_C_TRICORE_ == 1U)
  __asm ("ld.hu %%d11,[%0]""\n\t" \
         "mov %%d12,%2""\n\t" \
         "mov %%d13,%3""\n\t" \
         "insert %%d11,%%d11,%1,%%e12""\n\t" \
         "st.h [%0],%%d11" \
         : \
         : "a"(TargetPtr), "d" (SourceVal), "d" (Pos), "d" (Width) \
         : "d11", "d12", "d13");
  #endif /* #if (_GHS_C_TRICORE_ == 1U) */
  #endif /* _GHS_C_TRICORE_ */

  #if ((!defined(_TASKING_C_TRICORE_)) && (!defined(_GNU_C_TRICORE_)) &&\
       (!defined(_DIABDATA_C_TRICORE_)) && (!defined(_GHS_C_TRICORE_)))
  #error Unsupported compiler configured!
  #endif

  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
  /* MISRA2012_RULE_8_13_JUSTIFICATION: Parameter are updated via assembly
     instruction, hence cannot be passed as const.*/
}

/*******************************************************************************
** Traceability      : [cover parentID={C1D10318-09FD-4cb8-9950-AF15B6F13A37},**
**                                     {44B965C9-ADC0-4ebd-BF53-2C409B6CC3F7}]**
**                                                                            **
**                                                                            **
** Syntax            : void Bfx_lInsert32Bits                                 **
**                     (                                                      **
**                       uint32 * const TargetPtr,                            **
**                       const uint32 SourceVal,                              **
**                       const uint8 Pos,                                     **
**                       const uint8 Width                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_lInsert32Bits function copies the bits from the**
**                     SourceVal parameter starting from 0 bit position for   **
**                     Width number of bits into the memory location pointed  **
**                     to by TargetPtr parameter at the bit positions starting**
**                     from Pos bit position for Width number of bits.        **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : None                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the function                    **
**                                                                            **
** Parameters (in)   : SourceVal - Source Data                                **
**                     Pos       - Start bit position (Valid range: 0 to 31)  **
**                     Width     - Bit field length                           **
**                                 (Valid range: 1 to (32-Pos))               **
**                                                                            **
** Parameters(in-out): TargetPtr - Pointer to data which is to be modified    **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
LOCAL_INLINE void Bfx_lInsert32Bits(uint32* const TargetPtr,
                                    const uint32 SourceVal,
                                    const uint8 Pos,
                                    const uint8 Width)
{
  #ifdef _TASKING_C_TRICORE_
  #if (_TASKING_C_TRICORE_ == 1U)
  __asm("ld.w d11,[%0]""\n\t" \
        "mov d12,%2""\n\t" \
        "mov d13,%3""\n\t" \
        "insert d11,d11,%1,e12""\n\t" \
        "st.w [%0],d11" \
        : \
        : "a"(TargetPtr), "d" (SourceVal), "d" (Pos), "d" (Width) \
        : "d11", "d12", "d13", "memory");
  #endif /* #if (_TASKING_C_TRICORE_ == 1U) */
  #endif /* _TASKING_C_TRICORE_ */

  #ifdef _GNU_C_TRICORE_
  #if (_GNU_C_TRICORE_ == 1U)
  __asm__("ld.w %%d11,[%0]""\n\t" \
          "mov %%d12,%2""\n\t" \
          "mov %%d13,%3""\n\t" \
          "insert %%d11,%%d11,%1,%%e12""\n\t" \
          "st.w [%0],%%d11" \
          : \
          : "a"(TargetPtr), "d" (SourceVal), "d" (Pos), "d" (Width) \
          : "d11", "d12", "d13");
  #endif /* #if (_GNU_C_TRICORE_ == 1U) */
  #endif /* _GNU_C_TRICORE_ */

  #ifdef _DIABDATA_C_TRICORE_
  #if (_DIABDATA_C_TRICORE_ == 1U)
  BFX_INSERT32BITS_DCC(TargetPtr, SourceVal, Pos, Width);
  #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
  #endif

  #ifdef _GHS_C_TRICORE_
  #if (_GHS_C_TRICORE_ == 1U)
  __asm ("ld.w %%d11,[%0]""\n\t" \
         "mov %%d12,%2""\n\t" \
         "mov %%d13,%3""\n\t" \
         "insert %%d11,%%d11,%1,%%e12""\n\t" \
         "st.w [%0],%%d11" \
         : \
         : "a"(TargetPtr), "d" (SourceVal), "d" (Pos), "d" (Width) \
         : "d11", "d12", "d13");
  #endif /* #if (_GHS_C_TRICORE_ == 1U) */
  #endif /* _GHS_C_TRICORE_ */

  #if ((!defined(_TASKING_C_TRICORE_)) && (!defined(_GNU_C_TRICORE_)) &&\
       (!defined(_DIABDATA_C_TRICORE_)) && (!defined(_GHS_C_TRICORE_)))
  #error Unsupported compiler configured!
  #endif

  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
  /* MISRA2012_RULE_8_13_JUSTIFICATION: Parameter are updated via assembly
     instruction, hence cannot be passed as const.*/
}


/*******************************************************************************
** Traceability      : [cover parentID={145D5F6B-3581-4b99-9639-C0EC88AC7044}]**
**                                                                            **
** Syntax            : void Bfx_lInsert64Bits                                 **
**                     (                                                      **
**                       uint64 * const TargetPtr,                            **
**                       const uint64 SourceVal,                              **
**                       const uint8 Pos,                                     **
**                       const uint8 Width                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_lInsert64Bits function copies the bits from the**
**                     SourceVal parameter starting from 0 bit position for   **
**                     Width number of bits into the memory location pointed  **
**                     to by TargetPtr parameter at the bit positions starting**
**                     from Pos bit position for Width number of bits.        **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : None                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the function                    **
**                                                                            **
** Parameters (in)   : SourceVal - Source Data                                **
**                     Pos       - Start bit position (Valid range: 0 to 63)  **
**                     Width     - Bit field length                           **
**                                 (Valid range: 1 to (64-Pos) except 64)     **
**                                                                            **
** Parameters(in-out): TargetPtr - Pointer to data which is to be modified    **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
LOCAL_INLINE void Bfx_lInsert64Bits(uint64* const TargetPtr,
                                    const uint64 SourceVal,
                                    const uint8 Pos,
                                    const uint8 Width)
{
  /* [cover parentID={FEF78465-BD8C-49fc-8703-CA252122D57C}]
  Is Width greater than 32?
  [/cover] */
  if((Width > BFX_MAX_LENGTH_32BIT))
  {
    /* [cover parentID={B1D02DDA-0780-40be-9D98-991036FFD33B}]
    Insertion of the data when Width is greater than 32
    [/cover] */
    /* [cover parentID={1E03CB28-20EC-49f8-83C0-EEE162525BFC}]
    Is the sum of Position and Width 64?
    [/cover] */
    if((Pos+Width) == BFX_MAX_LENGTH_64BIT)
    {
      /* [cover parentID={DC0C139D-399C-4d37-9483-82468468A37E}]
      Insert data partially into the lower word starting from Pos
      bit position and the next 32 bits into the higher word.
      [/cover] */
      Bfx_lInsWidthGT32SumEQ64(TargetPtr,SourceVal,Pos,Width);
    }/*End of "if((Pos+Width) == BFX_MAX_LENGTH_64BIT)"*/
    else
    {
      /* [cover parentID={1C6A2A7F-D51C-4aa0-99E2-1DF701CE13D1}]
      Is Position 0?
      [/cover] */
      if(Pos == BFX_MIN_POS_LOWER_WORD)
      {
        /* [cover parentID={E6A2DA31-46BB-4fe7-8DB0-CC557EC08A3B}]
        Insert the 32 bits starting from position 0  into the lower
        word and the remaining data partially into the higher word.
        [/cover] */
        Bfx_lInsPosEQ0WidthGT32SumLT64(TargetPtr,SourceVal,Width);
      }/*End of "if(Pos == BFX_MIN_POS_LOWER_WORD)"*/
      else
      {
        /* [cover parentID={05CCCC3D-EFA6-448d-A62A-C38818240BFB}]
        Insert data partially into the lower word starting from Pos
        bit position and the remaining bits into the  higher word.
        [/cover] */
        Bfx_lInsPosGT0LT32SumGT32LT64(TargetPtr,SourceVal,Pos,Width);
      }/*End of  else block for "if(Pos == BFX_MIN_POS_LOWER_WORD)"*/
    }/*End of else block for "if((Pos+Width) == BFX_MAX_LENGTH_64BIT)"*/
  }/*End of "if((Width > BFX_MAX_LENGTH_32BIT))"*/
  /* [cover parentID={A2DF5623-33B1-49d1-A9F2-FAB1788DBCBB}]
  Is Width less than or equal to 32?
  [/cover] */
  else
  {
    /* [cover parentID={0EAE416A-A711-4a96-B76A-70C32510857E}]
    Insertion of the data when Width is less than or equal to 32
    [/cover] */
    /* [cover parentID={09369123-3388-4027-A99E-30BC784BEA71}]
    Is Position greater than or equal to 32?
    [/cover] */
    if(Pos >= BFX_MIN_POS_HIGHER_WORD)
    {
      /* [cover parentID={6ED206ED-EE9F-4f83-AE95-7DB2A78711FA}]
      Is Width 32?
      [/cover] */
      if(Width ==  BFX_MAX_LENGTH_32BIT)
      {
        /* [cover parentID={293BD585-C010-493e-80BC-08FFBD790207}]
        Insert the 32 bits into the entire higher word.
        [/cover] */
        Bfx_lInsPosEQ32WidthEQ32(TargetPtr,SourceVal);
      }/*End of "if(Width ==  BFX_MAX_LENGTH_32BIT)"*/
      else
      {
        /* [cover parentID={3F59EAD0-22E1-4a5d-A1F3-C2B748EAAACD}]
        Insert partially into the higher word starting from Pos bit position.
        [/cover] */
        Bfx_lInsPosGTE32WidthLT32(TargetPtr,SourceVal,Pos,Width);
      }/*End of else block for "if(Width ==  BFX_MAX_LENGTH_32BIT)"*/
    }/*End of "if(Pos >= BFX_MIN_POS_HIGHER_WORD)"*/
    else
    {
      /* [cover parentID={202A7578-F69A-4872-B191-CC9A53DD575F}]
      Is the sum of Position and Width greater than 32?
      [/cover] */
      if((Pos + Width) > BFX_MIN_POS_HIGHER_WORD)
      {
        /* [cover parentID={7E34CED7-0CB0-49df-91A3-3798B2B5026E}]
        Insert data partially into the lower word starting from Pos
        bit position and the remaining bits into the  higher word.
        [/cover] */
        Bfx_lInsPosGT0LT32SumGT32LT64(TargetPtr,SourceVal,Pos,Width);
      }/*End of "if((Pos + Width) > BFX_MIN_POS_HIGHER_WORD)"*/
      else
      {
        /* [cover parentID={DE85F20E-C182-47a1-AB85-0DE70AC178E5}]
        Is Width 32?
        [/cover] */
        if(Width == BFX_MAX_LENGTH_32BIT)
        {
          /* [cover parentID={B5DC4E76-16D6-4b72-808D-EAB45E5A8E16}]
          Insert the 32 bits into the entire lower word.
          [/cover] */
          Bfx_lInsPosEQ0WidthEQ32(TargetPtr,SourceVal);
        }/*End of "if(Width == BFX_MAX_LENGTH_32BIT)"*/
        else
        {
          /* [cover parentID={C1CF2E12-7058-4c5d-B496-C4CA286DCB7C}]
          Insert partially into the lower word starting from Pos bit position.
          [/cover] */
          Bfx_lInsPosLT32WidthLT32SumLTE32(TargetPtr,SourceVal,Pos,Width);
        }/*End of else block "if(Width == BFX_MAX_LENGTH_32BIT)"*/
      }/*End of else block for "if((Pos + Width) > BFX_MIN_POS_HIGHER_WORD)"*/
    }/*End of else block for "if(Pos >= BFX_MIN_POS_HIGHER_WORD)"*/
  }/*End of else block for "if((Width > BFX_MAX_LENGTH_32BIT))"*/
}


/*******************************************************************************
** Traceability      : [cover parentID={2DB607CC-CB48-40c1-A677-0AC93446A128}]**
**                                                                            **
**                                                                            **
** Syntax            : void Bfx_lInsWidthGT32SumEQ64                          **
**                     (                                                      **
**                       uint64 * const TargetPtr,                            **
**                       const uint64 SourceVal,                              **
**                       const uint8 Pos,                                     **
**                       const uint8 Width                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_lInsWidthGT32SumEQ64 function copies the bits  **
**                     from the SourceVal parameter starting from 0 bit       **
**                     position for Width number of bits into the memory      **
**                     location pointed to by TargetPtr parameter at the bit  **
**                     positions starting from bit position Pos less than 32  **
**                     for Width  greater than 32 number of bits and the sum  **
**                     of Pos and Width equal to 64. The function is          **
**                     implemented for 64-bit data.                           **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : None                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the function                    **
**                                                                            **
** Parameters (in)   : SourceVal - Source Data                                **
**                     Pos       - Start bit position (Valid range: 1 to 31)  **
**                     Width     - Bit field length (Valid range: (64-Pos))   **
**                                                                            **
** Parameters(in-out): TargetPtr - Pointer to data which is to be modified    **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
LOCAL_INLINE void Bfx_lInsWidthGT32SumEQ64(uint64* const TargetPtr,
                                    const uint64 SourceVal,
                                    const uint8 Pos,
                                    const uint8 Width)
{
  /*Width>BFX_WORD_LENGTH & (Pos+Width)=BFX_DOUBLE_WORD_LENGTH*/

  #ifdef _TASKING_C_TRICORE_
  #if (_TASKING_C_TRICORE_ == 1U)
  __asm("ld.d e10,[%0]""\n\t" \
    "mov d12,%2""\n\t" \
    "mov d13,%3""\n\t" \
    "insert d10,d10,%1.0,e12""\n\t" \
    "dextr d11,%1.1,%1.0,%2""\t""\n\t" \
    "st.d [%0],e10"\
    : \
    : "a"(TargetPtr), "e" (SourceVal), "d" (Pos), "d" (Width) \
    : "d10","d11", "d12", "d13");
  #endif /* #if (_TASKING_C_TRICORE_ == 1U) */
  #endif /* _TASKING_C_TRICORE_ */

  #ifdef _GNU_C_TRICORE_
  #if (_GNU_C_TRICORE_ == 1U)
  __asm__(/*Load the 64-bit data*/
    /*Pos+Width = 64*/
    /*Insert partially into the lower word using insert and then
      insert into the entire higher word using dextr as
      the remaining bits are to be copied from both the words
      of SourceVal*/
    /*For insert: pos=Pos and width=32-Pos=Width-32=Width*/
    /*For dextr: 32-pos=32-(32-pos)=pos*/
    /*Store the 64-bit data*/
    "ld.d %%e10,[%0]""\n\t" \
    "mov %%d12,%2""\n\t" \
    "mov %%d13,%3""\n\t" \
    "insert %%d10,%%d10,%L1,%%e12""\n\t" \
    "dextr %%d11,%H1,%L1,%2""\t""\n\t" \
    "st.d [%0],%%e10" \
    : \
    : "a"(TargetPtr), "d" (SourceVal), "d" (Pos), "d" (Width) \
    : "d10","d11", "d12", "d13", "memory");
  #endif/* #if (_GNU_C_TRICORE_ == 1U)*/
  #endif/* _GNU_C_TRICORE_*/

  #ifdef _DIABDATA_C_TRICORE_
  #if (_DIABDATA_C_TRICORE_ == 1U)
  BFX_INSERT64BITS_DCC_WidthGT32SumEQ64(TargetPtr, SourceVal, Pos, Width);
  #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
  #endif /* _DIABDATA_C_TRICORE_ */

  #ifdef _GHS_C_TRICORE_
  #if (_GHS_C_TRICORE_ == 1U)
  __asm(/*Load the 64-bit data*/
    /*Pos+Width = 64*/
    /*Insert partially into the lower word using insert and then
      insert into the entire higher word using dextr as
      the remaining bits are to be copied from both the words
      of SourceVal*/
    /*For insert: pos=Pos and width=32-Pos=Width-32=Width*/
    /*For dextr: 32-pos=32-(32-pos)=pos*/
    /*Store the 64-bit data*/
    "ld.d %%e10,[%0]""\n\t" \
    "mov %%d12,%2""\n\t" \
    "mov %%d13,%3""\n\t" \
    "insert %%d10,%%d10,%L1,%%e12""\n\t" \
    "dextr %%d11,%H1,%L1,%2""\t""\n\t" \
    "st.d [%0],%%e10" \
    : \
    : "a"(TargetPtr), "d" (SourceVal), "d" (Pos), "d" (Width) \
    : "d10","d11", "d12", "d13");
  #endif /* #if (_GHS_C_TRICORE_ == 1U) */
  #endif /* _GHS_C_TRICORE_ */

  #if ((!defined(_TASKING_C_TRICORE_)) && (!defined(_GNU_C_TRICORE_)) &&\
       (!defined(_DIABDATA_C_TRICORE_)) && (!defined(_GHS_C_TRICORE_)))
  #error Unsupported compiler configured!
  #endif
  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
  /* MISRA2012_RULE_8_13_JUSTIFICATION: Parameter are updated via assembly
     instruction, hence cannot be passed as const.*/
}

/*******************************************************************************
** Traceability      : [cover parentID={E1AC9BD3-A1DB-4990-BC17-E4AFCAD1E9B6}]**
**                                                                            **
**                                                                            **
**                                                                            **
** Syntax            : void Bfx_lInsPosEQ32WidthEQ32                          **
**                     (                                                      **
**                       uint64 * const TargetPtr,                            **
**                       const uint64 SourceVal                               **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_lInsPosEQ32WidthEQ32 function copies the bits  **
**                     from the SourceVal parameter starting from 0 bit       **
**                     position for Width number of bits into the memory      **
**                     location pointed to by TargetPtr parameter at the bit  **
**                     positions starting from 32 for Width of 32 number      **
**                     of bits. The function is implemented for 64 bit data.  **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : None                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the function                    **
**                                                                            **
** Parameters (in)   : SourceVal - Source Data                                **
**                                                                            **
** Parameters(in-out): TargetPtr - Pointer to data which is to be modified    **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
LOCAL_INLINE void Bfx_lInsPosEQ32WidthEQ32(uint64* const TargetPtr,
                                    const uint64 SourceVal)
{
  /*Width=BFX_WORD_LENGTH & Pos=BFX_WORD_LENGTH*/

  #ifdef _TASKING_C_TRICORE_
  #if (_TASKING_C_TRICORE_ == 1U)
  __asm("ld.d e10,[%0]""\n\t" \
    "mov d11,%1.0""\n\t" \
    "st.d [%0],e10"\
    : \
    : "a"(TargetPtr), "e" (SourceVal) \
    : "d10","d11");
  #endif /* #if (_TASKING_C_TRICORE_ == 1U) */
  #endif /* _TASKING_C_TRICORE_ */

  #ifdef _GNU_C_TRICORE_
  #if (_GNU_C_TRICORE_ == 1U)
  __asm__(/*Load the 64-bit data*/
    /*Insert into the entire higher word using mov*/
    /*Store the 64-bit data*/
    "ld.d %%e10,[%0]""\n\t" \
    "mov %%d11,%L1""\n\t" \
    "st.d [%0],%%e10" \
    : \
    : "a"(TargetPtr), "d" (SourceVal) \
    : "d10","d11", "memory");
  #endif/* #if (_GNU_C_TRICORE_ == 1U)*/
  #endif/* _GNU_C_TRICORE_*/

  #ifdef _DIABDATA_C_TRICORE_
  #if (_DIABDATA_C_TRICORE_ == 1U)
  BFX_INSERT64BITS_DCC_PosEQ32WidthEQ32(TargetPtr, SourceVal);
  #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
  #endif /* _DIABDATA_C_TRICORE_ */

  #ifdef _GHS_C_TRICORE_
  #if (_GHS_C_TRICORE_ == 1U)
  __asm(/*Load the 64-bit data*/
    /*Insert into the entire higher word using mov*/
    /*Store the 64-bit data*/
    "ld.d %%e10,[%0]""\n\t" \
    "mov %%d11,%L1""\n\t" \
    "st.d [%0],%%e10" \
    : \
    : "a"(TargetPtr), "d" (SourceVal) \
    : "d10","d11");
  #endif /* #if (_GHS_C_TRICORE_ == 1U) */
  #endif /* _GHS_C_TRICORE_ */

  #if ((!defined(_TASKING_C_TRICORE_)) && (!defined(_GNU_C_TRICORE_)) &&\
       (!defined(_DIABDATA_C_TRICORE_)) && (!defined(_GHS_C_TRICORE_)))
  #error Unsupported compiler configured!
  #endif

  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
  /* MISRA2012_RULE_8_13_JUSTIFICATION: Parameter are updated via assembly
     instruction, hence cannot be passed as const.*/
}

/*******************************************************************************
** Traceability      : [cover parentID={55929A47-8256-48c7-9DF9-565D18C28213}]**
**                                                                            **
**                                                                            **
**                                                                            **
** Syntax            : void Bfx_lInsPosEQ0WidthGT32SumLT64                    **
**                     (                                                      **
**                       uint64 * const TargetPtr,                            **
**                       const uint64 SourceVal,                              **
**                       const uint8 Width                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_lInsPosEQ0WidthGT32SumLT64 function copies     **
**                     the bits from the SourceVal parameter starting from 0  **
**                     bit position for Width number of bits into the memory  **
**                     location pointed to by TargetPtr parameter at the bit  **
**                     positions starting from bit position 0 for Width       **
**                     greater than 32 number of bits and the sum of Pos and  **
**                     Width less than 64. The function is implemented for    **
**                     64-bit data.                                           **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : None                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the function                    **
**                                                                            **
** Parameters (in)   : SourceVal - Source Data                                **
**                     Width     - Bit field length (Valid range: 33 to 63)   **
**                                                                            **
** Parameters(in-out): TargetPtr - Pointer to data which is to be modified    **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
LOCAL_INLINE void Bfx_lInsPosEQ0WidthGT32SumLT64(uint64* const TargetPtr,
                                                 const uint64 SourceVal,
                                                 const uint8 Width)
{
  /*Width>BFX_WORD_LENGTH, (Pos+Width)!=BFX_DOUBLE_WORD_LENGTH &
    Pos=BFX_MIN_POS*/

  #ifdef _TASKING_C_TRICORE_
  #if (_TASKING_C_TRICORE_ == 1U)
  __asm("ld.d e10,[%0]""\n\t" \
    "mov d10,%1.0""\n\t" \
    "mov d12,%2""\n\t" \
    "mov d13,%3""\n\t" \
    "insert d11,d11,%1.1,e12""\n\t" \
    "st.d [%0],e10"\
    : \
    : "a"(TargetPtr), "e" (SourceVal), "i" (BFX_MIN_POS), "d" (Width) \
    : "d10","d11", "d12", "d13");
  #endif /* #if (_TASKING_C_TRICORE_ == 1U) */
  #endif /* _TASKING_C_TRICORE_ */

  #ifdef _GNU_C_TRICORE_
  #if (_GNU_C_TRICORE_ == 1U)
  __asm__(/*Load the 64-bit data*/
    /*Insert into the entire lower word using mov and then
      insert partially into the higher word using insert*/
    /*For insert: pos=0=E[d][4:0]=d12[4:0]*/
    /*For insert: width=Width-32=E[d][36:32]=d13[4:0]*/
    /*Store the 64-bit data*/
    "ld.d %%e10,[%0]""\n\t" \
    "mov %%d10,%L1""\n\t" \
    "mov %%d12,%2""\n\t" \
    "mov %%d13,%3""\n\t" \
    "insert %%d11,%%d11,%H1,%%e12""\n\t" \
    "st.d [%0],%%e10" \
    : \
    : "a"(TargetPtr), "d" (SourceVal), "i" (BFX_MIN_POS), "d" (Width) \
    : "d10","d11", "d12", "d13", "memory");
  #endif/* #if (_GNU_C_TRICORE_ == 1U)*/
  #endif/* _GNU_C_TRICORE_*/

  #ifdef _DIABDATA_C_TRICORE_
  #if (_DIABDATA_C_TRICORE_ == 1U)
  BFX_INSERT64BITS_DCC_PosEQ0WidthGT32SumLT64(TargetPtr, SourceVal, Width);
  #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
  #endif /* _DIABDATA_C_TRICORE_ */

  #ifdef _GHS_C_TRICORE_
  #if (_GHS_C_TRICORE_ == 1U)
  __asm(/*Load the 64-bit data*/
    /*Insert into the entire lower word using mov and then
      insert partially into the higher word using insert*/
    /*For insert: pos=0=E[d][4:0]=d12[4:0]*/
    /*For insert: width=Width-32=E[d][36:32]=d13[4:0]*/
    /*Store the 64-bit data*/
    "ld.d %%e10,[%0]""\n\t" \
    "mov %%d10,%L1""\n\t" \
    "mov %%d12,%2""\n\t" \
    "mov %%d13,%3""\n\t" \
    "insert %%d11,%%d11,%H1,%%e12""\n\t"
    "st.d [%0],%%e10" \
    : \
    : "a"(TargetPtr), "d" (SourceVal), "i" (BFX_MIN_POS), "d" (Width) \
    : "d10","d11", "d12", "d13");
  #endif /* #if (_GHS_C_TRICORE_ == 1U) */
  #endif /* _GHS_C_TRICORE_ */

  #if ((!defined(_TASKING_C_TRICORE_)) && (!defined(_GNU_C_TRICORE_)) &&\
       (!defined(_DIABDATA_C_TRICORE_)) && (!defined(_GHS_C_TRICORE_)))
  #error Unsupported compiler configured!
  #endif

  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
  /* MISRA2012_RULE_8_13_JUSTIFICATION: Parameter are updated via assembly
     instruction, hence cannot be passed as const.*/
}

/*******************************************************************************
** Traceability      : [cover parentID={0D6F8C0D-7DB1-4e39-9FBA-F3C825C5EBFE}]**
**                                                                            **
**                                                                            **
**                                                                            **
** Syntax            : void Bfx_lInsPosGT0LT32SumGT32LT64                     **
**                     (                                                      **
**                       uint64 * const TargetPtr,                            **
**                       const uint64 SourceVal,                              **
**                       const uint8 Pos,                                     **
**                       const uint8 Width                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_lInsPosGT0LT32SumGT32LT64 function copies      **
**                     the bits from the SourceVal parameter starting from    **
**                     0 bit position for Width number of bits into the       **
**                     memory location pointed to by TargetPtr parameter      **
**                     at the bit positions starting from Pos bit position    **
**                     whose value is greater than 0 and less than 32 and     **
**                     the sum of Pos and Width greater than 32 and  less     **
**                     than 64. The function is implemented for 64-bit data.  **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : None                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the function                    **
**                                                                            **
** Parameters (in)   : SourceVal - Source Data                                **
**                     Pos       - Start bit position (Valid range: 1 to 31)  **
**                     Width     - Bit field length                           **
**                                 (Valid range: (33-pos) to (63-pos))        **
**                                                                            **
** Parameters(in-out): TargetPtr - Pointer to data which is to be modified    **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
LOCAL_INLINE void Bfx_lInsPosGT0LT32SumGT32LT64(uint64* const TargetPtr,
                                                 const uint64 SourceVal,
                                                 const uint8 Pos,
                                                 const uint8 Width)
{
  /*Pos>BFX_MIN_POS, Width>BFX_WORD_LENGTH &
    Pos+Width < BFX_DOUBLE_WORD_LENGTH*/

  #ifdef _TASKING_C_TRICORE_
  #if (_TASKING_C_TRICORE_ == 1U)
  __asm("ld.d e10,[%0]""\n\t" \
    "dextr d14,%1.1,%1.0,%2""\t""\n\t" \
    "mov d12,%4""\n\t" \
    "add d13,%2,%3""\n\t" \
    "insert d11,d11,d14,e12""\n\t" \
    "mov d12,%2""\n\t" \
    "rsub d13,%2,%4""\n\t" \
    "insert d10,d10,%1.0,e12""\n\t" \
    "st.d [%0],e10" \
    : \
    : "a"(TargetPtr), "e" (SourceVal), "d" (Pos), "d" (Width), \
      "i"(BFX_MIN_POS) \
    : "d10","d11", "d12", "d13", "d14");
  #endif /* #if (_TASKING_C_TRICORE_ == 1U) */
  #endif /* _TASKING_C_TRICORE_ */

  #ifdef _GNU_C_TRICORE_
  #if (_GNU_C_TRICORE_ == 1U)
  __asm__(/*Load the 64-bit data*/
    /*Insert partially into the lower word using insert and
      insert partially into the higher word using dextr and insert
      as the remaining bits to be copied are from both the words
      of SourceVal but less than 64 bits*/
    /*For dextr: 32-pos=32-(32-Pos)=Pos*/
    /*For 1st insert: pos=0=E[d][4:0]=d12[4:0]*/
    /*For 1st insert: width=Width-(32-Pos)=(Pos+Width)-32=E[d][36:32]=d13[4:0]*/
    /*For 2nd insert: pos=Pos=E[d][4:0]=d12[4:0]*/
    /*For 2nd insert: width=32-Pos=E[d][36:32]=d13[4:0]*/
    /*Store the 64-bit data*/
    "ld.d %%e10,[%0]""\n\t" \
    "dextr %%d14,%H1,%L1,%2""\t""\n\t" \
    "mov %%d12,%4""\n\t" \
    "add %%d13,%2,%3""\n\t" \
    "insert %%d11,%%d11,%%d14,%%e12""\n\t" \
    "mov %%d12,%2""\n\t" \
    "rsub %%d13,%2,%4""\n\t" \
    "insert %%d10,%%d10,%L1,%%e12""\n\t" \
    "st.d [%0],%%e10" \
    : \
    : "a"(TargetPtr), "d" (SourceVal), "d" (Pos), "d" (Width), \
      "i"(BFX_WORD_LENGTH)\
    : "d10","d11", "d12", "d13", "d14", "memory");
  #endif/* #if (_GNU_C_TRICORE_ == 1U)*/
  #endif/* _GNU_C_TRICORE_*/

  #ifdef _DIABDATA_C_TRICORE_
  #if (_DIABDATA_C_TRICORE_ == 1U)
  BFX_INSERT64BITS_DCC_PosGT0SumLT64(TargetPtr, SourceVal, Pos, Width);
  #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
  #endif /* _DIABDATA_C_TRICORE_ */

  #ifdef _GHS_C_TRICORE_
  #if (_GHS_C_TRICORE_ == 1U)
  __asm(/*Load the 64-bit data*/
    /*Insert partially into the lower word using insert and
      insert partially into the higher word using dextr and insert
      as the remaining bits to be copied are from both the words
      of SourceVal but less than 64 bits*/
    /*For dextr: 32-pos=32-(32-Pos)=Pos*/
    /*For 1st insert: pos=0=E[d][4:0]=d12[4:0]*/
    /*For 1st insert: width=Width-(32-Pos)=(Pos+Width)-32=E[d][36:32]=d13[4:0]*/
    /*For 2nd insert: pos=Pos=E[d][4:0]=d12[4:0]*/
    /*For 2nd insert: width=32-Pos=E[d][36:32]=d13[4:0]*/
    /*Store the 64-bit data*/
    "ld.d %%e10,[%0]""\n\t" \
    "dextr %%d14,%H1,%L1,%2""\t""\n\t" \
    "mov %%d12,%4""\n\t" \
    "add d13,%2,%3""\n\t" \
    "insert %%d11,%%d11,%%d14,%%e12""\n\t" \
    "mov %%d12,%2""\n\t" \
    "rsub %%d13,%2,%4""\n\t" \
    "insert %%d10,%%d10,%L1,%%e12""\n\t" \
    "st.d [%0],%%e10" \
    : \
    : "a"(TargetPtr), "d" (SourceVal), "d" (Pos), "d" (Width), \
      "i"(BFX_WORD_LENGTH) \
    : "d10","d11", "d12", "d13", "d14");
  #endif /* #if (_GHS_C_TRICORE_ == 1U) */
  #endif /* _GHS_C_TRICORE_ */

  #if ((!defined(_TASKING_C_TRICORE_)) && (!defined(_GNU_C_TRICORE_)) &&\
       (!defined(_DIABDATA_C_TRICORE_)) && (!defined(_GHS_C_TRICORE_)))
  #error Unsupported compiler configured!
  #endif

  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
  /* MISRA2012_RULE_8_13_JUSTIFICATION: Parameter are updated via assembly
     instruction, hence cannot be passed as const.*/
}

/*******************************************************************************
** Traceability      : [cover parentID={A32BBC4A-3092-4870-AA3C-3C7D4C4F1D45}]**
**                                                                            **
**                                                                            **
**                                                                            **
** Syntax            : void Bfx_lInsPosGTE32WidthLT32                         **
**                     (                                                      **
**                       uint64 * const TargetPtr,                            **
**                       const uint64 SourceVal,                              **
**                       const uint8 Pos,                                     **
**                       const uint8 Width                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_lInsPosGTE32WidthLT32 function copies          **
**                     the bits from the SourceVal parameter starting from    **
**                     0 bit position for Width number of bits into the       **
**                     memory location pointed to by TargetPtr parameter at   **
**                     the bit position Pos whose value is greater than or    **
**                     equal to 32 for Width less than 32 number of bits.     **
**                     The function is implemented for 64-bit data.           **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : None                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the function                    **
**                                                                            **
** Parameters (in)   : SourceVal - Source Data                                **
**                     Pos       - Start bit position (Valid range: 32 to 63 )**
**                     Width     - Bit field length                           **
**                                 (Valid range: 1 to (64-Pos), excluding 32) **
**                                                                            **
** Parameters(in-out): TargetPtr - Pointer to data which is to be modified    **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
LOCAL_INLINE void Bfx_lInsPosGTE32WidthLT32(uint64* const TargetPtr,
                                            const uint64 SourceVal,
                                            const uint8 Pos,
                                            const uint8 Width)
{
  /* Width<BFX_WORD_LENGTH & Pos>=BFX_WORD_LENGTH */
  #ifdef _TASKING_C_TRICORE_
  #if (_TASKING_C_TRICORE_ == 1U)
  __asm("ld.d e10,[%0]""\n\t" \
    "mov d12,%2""\n\t" \
    "mov d13,%3""\n\t" \
    "insert d11,d11,%1.0,e12""\n\t" \
    "st.d [%0],e10" \
    : \
    : "a"(TargetPtr), "e" (SourceVal), "d" (Pos), "d" (Width) \
    : "d10","d11", "d12", "d13");
  #endif /* #if (_TASKING_C_TRICORE_ == 1U) */
  #endif /* _TASKING_C_TRICORE_ */

  #ifdef _GNU_C_TRICORE_
  #if (_GNU_C_TRICORE_ == 1U)
  __asm__(/*Load the 64-bit data*/
    /*Insert partially into the higher word using insert*/
    /*For insert: pos=Pos-32=Pos=E[d][4:0]=d12[4:0]*/
    /*For insert: width=Width=E[d][36:32]=d13[4:0]*/
    /*Store the 64-bit data*/
    "ld.d %%e10,[%0]""\n\t" \
    "mov %%d12,%2""\n\t" \
    "mov %%d13,%3""\n\t" \
    "insert %%d11,%%d11,%L1,%%e12""\n\t" \
    "st.d [%0],%%e10" \
    : \
    : "a"(TargetPtr), "d" (SourceVal), "d" (Pos), "d" (Width)\
    : "d10","d11", "d12", "d13", "memory");
  #endif/* #if (_GNU_C_TRICORE_ == 1U)*/
  #endif/* _GNU_C_TRICORE_*/

  #ifdef _DIABDATA_C_TRICORE_
  #if (_DIABDATA_C_TRICORE_ == 1U)
  BFX_INSERT64BITS_DCC_PosGTE32WidthLT32(TargetPtr, SourceVal, Pos, Width);
  #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
  #endif /* _DIABDATA_C_TRICORE_ */

  #ifdef _GHS_C_TRICORE_
  #if (_GHS_C_TRICORE_ == 1U)
  __asm(/*Load the 64-bit data*/
    /*Insert partially into the higher word using insert*/
    /*For insert: pos=Pos-32=Pos=E[d][4:0]=d12[4:0]*/
    /*For insert: width=Width=E[d][36:32]=d13[4:0]*/
    /*Store the 64-bit data*/
    "ld.d %%e10,[%0]""\n\t" \
    "mov %%d12,%2""\n\t" \
    "mov %%d13,%3""\n\t" \
    "insert %%d11,%%d11,%L1,%%e12""\n\t" \
    "st.d [%0],%%e10" \
    : \
    : "a"(TargetPtr), "d" (SourceVal), "d" (Pos), "d" (Width) \
    : "d10","d11", "d12", "d13");
  #endif /* #if (_GHS_C_TRICORE_ == 1U) */
  #endif /* _GHS_C_TRICORE_ */

  #if ((!defined(_TASKING_C_TRICORE_)) && (!defined(_GNU_C_TRICORE_)) &&\
       (!defined(_DIABDATA_C_TRICORE_)) && (!defined(_GHS_C_TRICORE_)))
  #error Unsupported compiler configured!
  #endif

  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
  /* MISRA2012_RULE_8_13_JUSTIFICATION: Parameter are updated via assembly
     instruction, hence cannot be passed as const.*/
}

/*******************************************************************************
** Traceability      : [cover parentID={686F81DA-E37D-43ba-B8F3-C1CB58A5E1A0}]**
**                                                                            **
**                                                                            **
**                                                                            **
** Syntax            : void Bfx_lInsPosEQ0WidthEQ32                           **
**                     (                                                      **
**                       uint64 * const TargetPtr,                            **
**                       const uint64 SourceVal                               **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_lInsPosEQ0WidthEQ32 function copies the bits   **
**                     from the SourceVal parameter starting from 0 bit       **
**                     position for Width number of bits into the memory      **
**                     location pointed to by TargetPtr parameter at the bit  **
**                     positions starting from 0 bit position for 32 number   **
**                     of bits. The function is implemented for 64-bit data.  **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : None                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the function                    **
**                                                                            **
** Parameters (in)   : SourceVal - Source Data                                **
**                                                                            **
** Parameters(in-out): TargetPtr - Pointer to data which is to be modified    **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
LOCAL_INLINE void Bfx_lInsPosEQ0WidthEQ32(uint64* const TargetPtr,
                                          const uint64 SourceVal)
{
  /*Width=BFX_WORD_LENGTH & (Pos+Width)<=BFX_WORD_LENGTH (Pos = BFX_MIN_POS)*/

  #ifdef _TASKING_C_TRICORE_
  #if (_TASKING_C_TRICORE_ == 1U)
  __asm("ld.d e10,[%0]""\n\t" \
    "mov d10,%1.0""\n\t" \
    "st.d [%0],e10" \
    : \
    : "a"(TargetPtr), "e" (SourceVal) \
    : "d10","d11");
  #endif /* #if (_TASKING_C_TRICORE_ == 1U) */
  #endif /* _TASKING_C_TRICORE_ */

  #ifdef _GNU_C_TRICORE_
  #if (_GNU_C_TRICORE_ == 1U)
  __asm__(/*Load the 64-bit data*/
    /*Insert into the entire lower word using mov*/
    /*Store the 64-bit data*/
    "ld.d %%e10,[%0]""\n\t" \
    "mov %%d10,%L1""\n\t"
    "st.d [%0],%%e10" \
    : \
    : "a"(TargetPtr), "d" (SourceVal) \
    : "d10","d11", "memory");
  #endif/* #if (_GNU_C_TRICORE_ == 1U)*/
  #endif/* _GNU_C_TRICORE_*/

  #ifdef _DIABDATA_C_TRICORE_
  #if (_DIABDATA_C_TRICORE_ == 1U)
  BFX_INSERT64BITS_DCC_PosEQ0WidthEQ32(TargetPtr, SourceVal);
  #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
  #endif /* _DIABDATA_C_TRICORE_ */

  #ifdef _GHS_C_TRICORE_
  #if (_GHS_C_TRICORE_ == 1U)
  __asm(/*Load the 64-bit data*/
    /*Insert into the entire lower word using mov*/
    /*Store the 64-bit data*/
    "ld.d %%e10,[%0]""\n\t" \
    "mov %%d10,%L1""\n\t"
    "st.d [%0],%%e10" \
    : \
    : "a"(TargetPtr), "d" (SourceVal) \
    : "d10","d11" );
  #endif /* #if (_GHS_C_TRICORE_ == 1U) */
  #endif /* _GHS_C_TRICORE_ */

  #if ((!defined(_TASKING_C_TRICORE_)) && (!defined(_GNU_C_TRICORE_)) &&\
       (!defined(_DIABDATA_C_TRICORE_)) && (!defined(_GHS_C_TRICORE_)))
  #error Unsupported compiler configured!
  #endif

  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
  /* MISRA2012_RULE_8_13_JUSTIFICATION: Parameter are updated via assembly
     instruction, hence cannot be passed as const.*/
}

/*******************************************************************************
** Traceability      : [cover parentID={42F0D41E-FD49-4bb9-8F31-9303290FA7BF}]**
**                                                                            **
**                                                                            **
**                                                                            **
** Syntax            : void Bfx_lInsPosLT32WidthLT32SumLTE32                  **
**                     (                                                      **
**                       uint64 * const TargetPtr,                            **
**                       const uint64 SourceVal,                              **
**                       const uint8 Pos,                                     **
**                       const uint8 Width                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_lInsPosLT32WidthLT32SumLTE32 function copies   **
**                     the bits from the SourceVal parameter starting from 0  **
**                     bit position for Width number of bits into the memory  **
**                     location pointed to by TargetPtr parameter at the bit  **
**                     positions starting from Pos bit position whose value   **
**                     is less than 32 for Width less than 32 number of bits  **
**                     and the sum of Pos and Width less than or equal to 32. **
**                     The function is implemented for 64-bit data.           **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : None                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the function                    **
**                                                                            **
** Parameters (in)   : SourceVal - Source Data                                **
**                     Pos       - Start bit position (Valid range: 0 to 31 ) **
**                     Width     - Bit field length                           **
**                                 (Valid range: 1 to (32-Pos), excluding 32  **
**                                                                            **
** Parameters(in-out): TargetPtr - Pointer to data which is to be modified    **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
LOCAL_INLINE void Bfx_lInsPosLT32WidthLT32SumLTE32(uint64* const TargetPtr,
                                                  const uint64 SourceVal,
                                                  const uint8 Pos,
                                                  const uint8 Width)
{
  /*Width<BFX_WORD_LENGTH, Pos<BFX_WORD_LENGTH & (Pos+Width)<BFX_WORD_LENGTH*/

  #ifdef _TASKING_C_TRICORE_
  #if (_TASKING_C_TRICORE_ == 1U)
  __asm("ld.d e10,[%0]""\n\t" \
    "mov d12,%2""\n\t" \
    "mov d13,%3""\n\t" \
    "insert d10,d10,%1.0,e12""\n\t" \
    "st.d [%0],e10" \
    : \
    : "a"(TargetPtr), "e" (SourceVal), "d" (Pos), "d" (Width) \
    : "d10","d11", "d12", "d13");
  #endif /* #if (_TASKING_C_TRICORE_ == 1U) */
  #endif /* _TASKING_C_TRICORE_ */

  #ifdef _GNU_C_TRICORE_
  #if (_GNU_C_TRICORE_ == 1U)
  __asm__ (/*Load the 64-bit data*/
    /*Insert partially into the lower word using insert*/
    /*For insert: pos=Pos and width=Width*/
    /*Store the 64-bit data*/
    "ld.d %%e10,[%0]""\n\t" \
    "mov %%d12,%2""\n\t" \
    "mov %%d13,%3""\n\t" \
    "insert %%d10,%%d10,%L1,%%e12""\n" \
    "st.d [%0],%%e10" \
    : \
    : "a"(TargetPtr), "d" (SourceVal), "d" (Pos), "d" (Width)\
    : "d10","d11", "d12", "d13", "memory");
  #endif/* #if (_GNU_C_TRICORE_ == 1U)*/
  #endif/* _GNU_C_TRICORE_*/

  #ifdef _DIABDATA_C_TRICORE_
  #if (_DIABDATA_C_TRICORE_ == 1U)
  BFX_INSERT64BITS_DCC_PosLT32WidthLT32SumLT32(TargetPtr, SourceVal,
                                                         Pos, Width);
  #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
  #endif /* _DIABDATA_C_TRICORE_ */

  #ifdef _GHS_C_TRICORE_
  #if (_GHS_C_TRICORE_ == 1U)
  __asm(/*Load the 64-bit data*/
    /*Insert partially into the lower word using insert*/
    /*For insert: pos=Pos and width=Width*/
    /*Store the 64-bit data*/
    "ld.d %%e10,[%0]""\n\t" \
    "mov %%d12,%2""\n\t" \
    "mov %%d13,%3""\n\t" \
    "insert %%d10,%%d10,%L1,%%e12""\n" \
    "st.d [%0],%%e10" \
    : \
    : "a"(TargetPtr), "d" (SourceVal), "d" (Pos), "d" (Width) \
    : "d10","d11", "d12", "d13");
  #endif /* #if (_GHS_C_TRICORE_ == 1U) */
  #endif /* _GHS_C_TRICORE_ */

  #if ((!defined(_TASKING_C_TRICORE_)) && (!defined(_GNU_C_TRICORE_)) &&\
       (!defined(_DIABDATA_C_TRICORE_)) && (!defined(_GHS_C_TRICORE_)))
  #error Unsupported compiler configured!
  #endif

  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
  /* MISRA2012_RULE_8_13_JUSTIFICATION: Parameter are updated via assembly
     instruction, hence cannot be passed as const.*/
}

/*******************************************************************************
** Traceability      : [cover parentID={24F7AF0E-13C0-4849-A903-7190520A26E8},**
**                                     {44B965C9-ADC0-4ebd-BF53-2C409B6CC3F7}]**
**                                                                            **
**                                                                            **
** Syntax            : uint32 Bfx_lExtractBits                                **
**                     (                                                      **
**                       const uint32 Value,                                  **
**                       const uint8 Pos,                                     **
**                       const uint8 Width                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_lExtractBits function returns the bits from the**
**                     Value parameter starting from Pos bit position for     **
**                     Width number of bits.                                  **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : None                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Value - Input data                                     **
**                     Pos   - Start bit position (Valid range: 0 to 31)      **
**                     Width - Bit field length                               **
**                             (Valid range: 1 to (32-Pos), excluding 32)     **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : uint32 - Extracted data                                **
*******************************************************************************/
LOCAL_INLINE uint32 Bfx_lExtractBits(const uint32 Value,
                                     const uint8 Pos,
                                     const uint8 Width)
{
  uint32 ResultVal = 0x0U;

  #ifdef _TASKING_C_TRICORE_
  #if (_TASKING_C_TRICORE_ == 1U)
  __asm("mov d12,%2""\n\t" \
        "mov d13,%3""\n\t" \
        "extr.u %0,%1,e12" \
        : "=d" (ResultVal) \
        : "d" (Value), "d" (Pos), "d" (Width) \
        : "d12", "d13" );
  #endif /* #if (_TASKING_C_TRICORE_ == 1U) */
  #endif /* _TASKING_C_TRICORE_ */

  #ifdef _GNU_C_TRICORE_
  #if (_GNU_C_TRICORE_ == 1U)
  __asm__ volatile ("mov %%d12,%2""\n\t" \
                    "mov %%d13,%3""\n\t" \
                    "extr.u %0,%1,%%e12" \
                    : "=d" (ResultVal) \
                    : "d" (Value), "d" (Pos), "d" (Width) \
                    : "d12", "d13");
  #endif /* #if (_GNU_C_TRICORE_ == 1U) */
  #endif /* _GNU_C_TRICORE_ */

  #ifdef _DIABDATA_C_TRICORE_
  #if (_DIABDATA_C_TRICORE_ == 1U)
  ResultVal = BFX_EXTRACTBITS_DCC(Value, Pos, Width);

  #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
  #endif

  #ifdef _GHS_C_TRICORE_
  #if (_GHS_C_TRICORE_ == 1U)
  __asm volatile ("mov %%d12,%2""\n\t" \
                  "mov %%d13,%3""\n\t" \
                  "extr.u %0,%1,%%e12" \
                  : "=d" (ResultVal) \
                  : "d" (Value), "d" (Pos), "d" (Width) \
                  : "d12", "d13");
  #endif /* #if (_GHS_C_TRICORE_ == 1U) */
  #endif /* _GHS_C_TRICORE_ */

  #if ((!defined(_TASKING_C_TRICORE_)) && (!defined(_GNU_C_TRICORE_)) &&\
       (!defined(_DIABDATA_C_TRICORE_)) && (!defined(_GHS_C_TRICORE_)))
  #error Unsupported compiler configured!
  #endif

  return ResultVal;

  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
}



/*******************************************************************************
** Traceability      : [cover parentID={8FF9A64A-27B2-4399-922B-28E2BADCFCB9}]**
**                                                                            **
** Syntax            : uint64 Bfx_lExtract64Bits                              **
**                     (                                                      **
**                       const uint64 Value,                                  **
**                       const uint8 Pos,                                     **
**                       const uint8 Width                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_lExtract64Bits function returns the bits from  **
**                     the Value parameter starting from Pos bit position for **
**                     Width number of bits. The function is implemented      **
**                     for 64-bit data.                                       **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : None                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Value - Input data                                     **
**                     Pos   - Start bit position (Valid range: 0 to 63)      **
**                     Width - Bit field length                               **
**                             (Valid range: 1 to (64-Pos), excluding 64)     **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : uint64 - Extracted data                                **
*******************************************************************************/
LOCAL_INLINE uint64 Bfx_lExtract64Bits(const uint64 Value,
                                     const uint8 Pos,
                                     const uint8 Width)
{
  uint64 ResultVal=0U;
  /* [cover parentID={71D55E15-ED68-495a-9FD0-3CD1E562D2B9}]
  Is Width greater than or equal to 32?
  [/cover] */
  if((Width >= BFX_MAX_LENGTH_32BIT))
  {
    /* [cover parentID={E0658679-F4B4-4948-9037-E957770C9F25}]
    Extraction of data when Width is greater than or equal to 32
    [/cover] */
    /* [cover parentID={9B41AD31-56F6-482f-BFA4-DC75BDE43F9F}]
    Is Width equal to 32?
    [/cover] */
    if(Width == BFX_MAX_LENGTH_32BIT)
    {
      /* [cover parentID={67728590-D61C-43bd-A376-205FBAC46631}]
      Is Position either 32 or 0 ?
      [/cover] */
      if((Pos == BFX_MIN_POS_HIGHER_WORD)||(Pos == BFX_MIN_POS_LOWER_WORD))
      {
        /* [cover parentID={F5729171-A6C6-4e6e-89E8-FBD3430E4888}]
        Extract the entire upper or lower word based on value of Pos.
        [/cover] */
        ResultVal = Bfx_lExtPosEQ32Or0WidthEQ32(Value,Pos);
      }/*End of "if((Pos == BFX_MIN_POS_HIGHER_WORD)||
         (Pos == BFX_MIN_POS_LOWER_WORD))"*/
      else
      {
        /* [cover parentID={F9EC777E-6B49-44a8-BBFD-F958CBA5F62C}]
        Extract 32 bits partially from the lower and higher word,
        starting from Pos bit position.
        [/cover] */
        ResultVal = Bfx_lExtPosNEQ32Or0WidthEQ32(Value,Pos);
      }/*End of else block for "if(Pos != BFX_MIN_POS_HIGHER_WORD)||
         (Pos != BFX_MIN_POS_LOWER_WORD)"*/
    }/*End of "if(Width == BFX_MAX_LENGTH_32BIT)"*/
    else
    {
      /* [cover parentID={37A55627-9750-4985-96D7-83EDB6210DFF}]
      Is Position 0 ?
      [/cover] */
      if(Pos == BFX_MIN_POS_LOWER_WORD)
      {
        /* [cover parentID={FD83F3D4-95ED-4cba-9280-4D38EA3CB9C4}]
        Extract the entire lower word and then the remaining data
        bits from the higher word.
        [/cover] */
        ResultVal = Bfx_lExtPosEQ0WidthGT32(Value,Width);
      }/*End of "if(Pos == BFX_MIN_POS_LOWER_WORD)"*/
      else
      {
        /* [cover parentID={D1E54032-1AC4-435c-BAC5-EF0C8655CDA5}]
        Extract 32 bits partially from the lower and higher word
        starting from Pos bit position and then extract the
        remaining bits from the higher word.
        [/cover] */
        ResultVal = Bfx_lExtPosNEQ0WidthGT32(Value,Pos,Width);
      }/*End of else block for "if(Pos == BFX_MIN_POS_LOWER_WORD)"*/
    }/*End of else block for "if(Width == BFX_MAX_LENGTH_32BIT)"*/
  }/*End of "if((Width >= BFX_MAX_LENGTH_32BIT))"*/
  /* [cover parentID={AAA91FDF-3756-4b2e-A078-280FCD840646}]
  Is Width less than 32?
  [/cover] */
  else
  {
    /* [cover parentID={03AA1F50-D864-43ac-802B-42A5328CD20C}]
    Extraction of data when Width is less than 32
    [/cover] */
    /* [cover parentID={FA0735A6-F97F-43e5-8C06-21E77B8F84DE}]
    Is Position greater than or equal to 32?
    [/cover] */
    if(Pos >= BFX_MIN_POS_HIGHER_WORD)
    {
      /* [cover parentID={A9C0F51B-BEBA-415b-9238-DF1B7E01E73E}]
      Extact data partially from the higher word
      [/cover] */
      ResultVal = Bfx_lExtPosGTE32WidthLT32(Value,Pos,Width);
    }/*End of "if(Pos >= BFX_MIN_POS_HIGHER_WORD)"*/
    else
    {
      /* [cover parentID={AC87E7FE-9F26-4381-82E8-04C241A51F58}]
      Is the sum of Position and Width greater than or equal to 32?
      [/cover] */
      if((Pos + Width) < BFX_MIN_POS_HIGHER_WORD)
      {
        /* [cover parentID={963F2DB1-9ACC-4930-B85D-337AD24BE02E}]
        Extract data partially from the lower word
        [/cover] */
        ResultVal = Bfx_lExtPosLT32WidthLT32SumLT32(Value,Pos,Width);
      }/*End of "if((Pos + Width) < BFX_MIN_POS_HIGHER_WORD)"*/
      else
      {
        /* [cover parentID={07AF6A76-9C4A-4813-AECE-E2EF63BC2DCB}]
        Extract data partially from the lower and higher word
        starting from Pos bit position.
        [/cover] */
        ResultVal = Bfx_lExtPosLT32WidthLT32SumGTE32(Value,Pos,Width);
      }/*End of else block for "if((Pos + Width) < BFX_MIN_POS_HIGHER_WORD)"*/
    }/*End of else block for "if(Pos >= BFX_MIN_POS_HIGHER_WORD)"*/
  }/*End of else block for "if((Width >= BFX_MAX_LENGTH_32BIT))"*/
  /* [cover parentID={820E693E-406A-477f-92BA-7E9077B85F40}]
  Return the extracted bits
  [/cover] */
  return ResultVal;

}


/*******************************************************************************
** Traceability      : [cover parentID={16923C4E-97B5-487a-82FB-3642842E474A}]**
**                                                                            **
**                                                                            **
** Syntax            : uint64 Bfx_lExtPosNEQ0WidthGT32                        **
**                     (                                                      **
**                       const uint64 Value,                                  **
**                       const uint8 Pos,                                     **
**                       const uint8 Width                                    **
**                     )                                                      **
**                                                                            **
** Description       :  The Bfx_lExtPosNEQ0WidthGT32 function returns the     **
**                      extracted bits from the Value parameter starting from **
**                      bit position Pos with values greater than 0 for Width **
**                      greater than 32 number of bits. The function is       **
**                      implemented for 64-bit data.                          **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : None                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Value - Input data                                     **
**                     Pos   - Start bit position (Valid range: 0 to 31)      **
**                     Width - Bit field length (Valid range: 33 to 63)       **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : uint64 - Extracted data                                **
*******************************************************************************/
LOCAL_INLINE uint64 Bfx_lExtPosNEQ0WidthGT32(const uint64 Value,
                                             const uint8 Pos,
                                             const uint8 Width)
{
  /*Pos!=BFX_MIN_POS & Width>BFX_WORD_LENGTH*/

  uint64 ResultVal=0U;

  #ifdef _TASKING_C_TRICORE_
  #if (_TASKING_C_TRICORE_ == 1U)
  __asm("rsub d11,%2,%4""\n\t"\
    "dextr %0.0,%1.1,%1.0,d11""\n\t"\
    "mov d13,%3""\n\t"\
    "mov d12,%2""\n\t"\
    "extr.u %0.1,%1.1,e12""\n\t"\
    : "=&e"(ResultVal)\
    : "e"(Value), "d"(Pos), "d"(Width), "i"(BFX_WORD_LENGTH)\
    : "d11","d12", "d13");
  #endif /* #if (_TASKING_C_TRICORE_ == 1U) */
  #endif /* _TASKING_C_TRICORE_ */

  #ifdef _GNU_C_TRICORE_
  #if (_GNU_C_TRICORE_ == 1U)
  __asm__ volatile(/*Extract the 32 bits starting from Pos to the lower word using
    dextr and the remaining bits to the higher word using extr*/
    /*Width=width-32=E[d][36:32]=d13[4:0]*/
    /*Pos=pos-32=E[d][4:0]=d12[4:0]*/
    "rsub %%d11,%2,%4""\n\t"\
    "dextr %L0,%H1,%L1,%%d11""\n\t"\
    "mov %%d13,%3""\n\t"\
    "mov %%d12,%2""\n\t"\
    "extr.u %H0,%H1,%%e12""\n\t"\
    : "+&d" (ResultVal)\
    : "d" (Value), "d" (Pos), "d" (Width), "i"(BFX_WORD_LENGTH)\
    : "d11","d12", "d13");
  #endif /* #if (_GNU_C_TRICORE_ == 1U) */
  #endif /* _GNU_C_TRICORE_ */

  #ifdef _DIABDATA_C_TRICORE_
  #if (_DIABDATA_C_TRICORE_ == 1U)
  ResultVal = BFX_EXTRACT64BITS_DCC_PosNEQ0WidthGT32(Value, Pos, Width);
  #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
  #endif /* _DIABDATA_C_TRICORE_ */

  #ifdef _GHS_C_TRICORE_
  #if (_GHS_C_TRICORE_ == 1U)
  __asm__ volatile(/*Extract the 32 bits starting from Pos to the lower word using
    dextr and the remaining bits to the higher word using extr*/
    /*Width=width-32=E[d][36:32]=d13[4:0]*/
    /*Pos=pos-32=E[d][4:0]=d12[4:0]*/
    "rsub %%d11,%2,%4""\n\t"\
    "dextr %L0,%H1,%L1,%%d11""\n\t"\
    "mov %%d13,%3""\n\t"\
    "mov %%d12,%2""\n\t"\
    "extr.u %H0,%H1,%%e12""\n\t"\
    : "+&d" (ResultVal)\
    : "d" (Value), "d" (Pos), "d" (Width), "i"(BFX_WORD_LENGTH)\
    : "d11","d12", "d13");
  #endif /* #if (_GHS_C_TRICORE_ == 1U) */
  #endif /* _GHS_C_TRICORE_ */

  #if ((!defined(_TASKING_C_TRICORE_)) && (!defined(_GNU_C_TRICORE_)) &&\
       (!defined(_DIABDATA_C_TRICORE_)) && (!defined(_GHS_C_TRICORE_)))
  #error Unsupported compiler configured!
  #endif

  return ResultVal;

  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/

}

/*******************************************************************************
** Traceability      : [cover parentID={C7465A80-0C0C-4b3d-9469-BE4BE19890F4}]**
**                                                                            **
**                                                                            **
** Syntax            : uint64 Bfx_lExtPosGTE32WidthLT32                       **
**                     (                                                      **
**                       const uint64 Value,                                  **
**                       const uint8 Pos,                                     **
**                       const uint8 Width                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_lExtPosGTE32WidthLT32 function returns the     **
**                     bits from the Value parameter starting from bit        **
**                     position Pos with a value greater than or equal to 32  **
**                     for a Width less than 32 number of bits.               **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : None                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Value - Input data                                     **
**                     Pos   - Start bit position (Valid range: 32 to 63)     **
**                     Width - Bit field length                               **
**                             (Valid range: 1 to (64-Pos), excluding 32)     **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : uint64 - Extracted data                                **
*******************************************************************************/
LOCAL_INLINE uint64 Bfx_lExtPosGTE32WidthLT32(const uint64 Value,
                                             const uint8 Pos,
                                             const uint8 Width)
{
  /*Width<BFX_WORD_LENGTH & Pos>=BFX_WORD_LENGTH */

  uint64 ResultVal=0U;

  #ifdef _TASKING_C_TRICORE_
  #if (_TASKING_C_TRICORE_ == 1U)
  __asm("mov %0.1,%4""\n\t"\
    "mov d12,%2""\n\t"\
    "mov d13,%3""\n\t"\
    "extr.u %0.0,%1.1,e12""\n\t"\
    : "=&e"(ResultVal)\
    : "e"(Value), "d"(Pos), "d"(Width), "i"(BFX_MIN_POS)\
    : "d12", "d13");
  #endif /* #if (_TASKING_C_TRICORE_ == 1U) */
  #endif /* _TASKING_C_TRICORE_ */

  #ifdef _GNU_C_TRICORE_
  #if (_GNU_C_TRICORE_ == 1U)
  __asm__ volatile(/*Extract data partially from the higher word using extr*/
    /*For extr: pos=Pos-32=E[d][4:0]=d12[4:0]*/
    /*For extr: width=Width=E[d][36:32]=d13[4:0]*/
    "mov %%d12,%2""\n\t"\
    "mov %%d13,%3""\n\t"\
    "extr.u %L0,%H1,%%e12""\n\t"\
    : "+&d" (ResultVal)\
    : "d" (Value), "d" (Pos), "d" (Width)\
    : "d12", "d13");
  #endif /* #if (_GNU_C_TRICORE_ == 1U) */
  #endif /* _GNU_C_TRICORE_ */

  #ifdef _DIABDATA_C_TRICORE_
  #if (_DIABDATA_C_TRICORE_ == 1U)
  ResultVal = BFX_EXTRACT64BITS_DCC_PosGTE32WidthLT32(Value, Pos, Width);
  #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
  #endif /* _DIABDATA_C_TRICORE_ */

  #ifdef _GHS_C_TRICORE_
  #if (_GHS_C_TRICORE_ == 1U)
  __asm__ volatile(/*Extract data partially from the higher word using extr*/
    /*For extr: pos=Pos-32=E[d][4:0]=d12[4:0]*/
    /*For extr: width=Width=E[d][36:32]=d13[4:0]*/
    "mov %%d12,%2""\n\t"\
    "mov %%d13,%3""\n\t"\
    "extr.u %L0,%H1,%%e12""\n\t"\
    : "+&d" (ResultVal)\
    : "d" (Value), "d" (Pos), "d" (Width) \
    : "d12", "d13");
  #endif /* #if (_GHS_C_TRICORE_ == 1U) */
  #endif /* _GHS_C_TRICORE_ */

  #if ((!defined(_TASKING_C_TRICORE_)) && (!defined(_GNU_C_TRICORE_)) &&\
       (!defined(_DIABDATA_C_TRICORE_)) && (!defined(_GHS_C_TRICORE_)))
  #error Unsupported compiler configured!
  #endif

  return ResultVal;

  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
}

/*******************************************************************************
** Traceability      : [cover parentID={FC9A09CF-9F4D-47b7-AB7F-EAF3209D928C}]**
**                                                                            **
**                                                                            **
** Syntax            : uint64 Bfx_lExtPosNEQ32Or0WidthEQ32                    **
**                     (                                                      **
**                       const uint64 Value,                                  **
**                       const uint8 Pos                                      **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_lExtPosNEQ32Or0WidthEQ32 function returns the  **
**                     extracted bits from the Value parameter starting from  **
**                     bit position Pos not equal to 32 or 0 i.e Pos greater  **
**                     than 0 and less than 32 for Width of 32 number of bits.**
**                     The function is implemented for 64 bit data.           **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : None                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Value - Input data                                     **
**                     Pos   - Start bit position (Valid range: 1 to 31)      **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : uint64 - Extracted data                                **
*******************************************************************************/
LOCAL_INLINE uint64 Bfx_lExtPosNEQ32Or0WidthEQ32(const uint64 Value,
                                                 const uint8 Pos)
{
  /*Width==BFX_WORD_LENGTH, Pos!=BFX_WORD_LENGTH or  BFX_MIN_POS*/

  uint64 ResultVal=0U;

  #ifdef _TASKING_C_TRICORE_
  #if (_TASKING_C_TRICORE_ == 1U)
  __asm("mov %0.1,%4""\n\t"\
    "rsub d12,%2,%3""\n\t"\
    "dextr %0.0,%1.1,%1.0,d12""\n\t"\
    : "=&e"(ResultVal)\
    : "e"(Value), "d"(Pos),"i"(BFX_WORD_LENGTH),"i"(BFX_MIN_POS)\
    : "d12");
  #endif /* #if (_TASKING_C_TRICORE_ == 1U) */
  #endif /* _TASKING_C_TRICORE_ */

  #ifdef _GNU_C_TRICORE_
  #if (_GNU_C_TRICORE_ == 1U)
  __asm__ volatile(/* Extract the entire 32 bits by using dextr.*/
    "rsub %%d12,%2,%3""\n\t"\
    "dextr %L0,%H1,%L1,%%d12""\n\t"\
    : "+&d" (ResultVal)\
    : "d" (Value), "d" (Pos), "i" (BFX_WORD_LENGTH)\
    : "d12");
  #endif /* #if (_GNU_C_TRICORE_ == 1U) */
  #endif /* _GNU_C_TRICORE_ */

  #ifdef _DIABDATA_C_TRICORE_
  #if (_DIABDATA_C_TRICORE_ == 1U)
  ResultVal = BFX_EXTRACT64BITS_DCC_PosNEQ32Or0WidthEQ32(Value, Pos);
  #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
  #endif /* _DIABDATA_C_TRICORE_ */

  #ifdef _GHS_C_TRICORE_
  #if (_GHS_C_TRICORE_ == 1U)
  __asm__ volatile(/* Extract the entire 32 bits by using dextr.*/
    "rsub %%d12,%2,%3""\n\t"\
    "dextr %L0,%H1,%L1,%%d12""\n\t"\
    : "+&d" (ResultVal)\
    : "d" (Value), "d" (Pos), "i"(BFX_WORD_LENGTH)\
    : "d12");
  #endif /* #if (_GHS_C_TRICORE_ == 1U) */
  #endif /* _GHS_C_TRICORE_ */

  #if ((!defined(_TASKING_C_TRICORE_)) && (!defined(_GNU_C_TRICORE_)) &&\
       (!defined(_DIABDATA_C_TRICORE_)) && (!defined(_GHS_C_TRICORE_)))
  #error Unsupported compiler configured!
  #endif

  return ResultVal;

  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
}

/*******************************************************************************
** Traceability      : [cover parentID={3D4F1882-2FBA-48e2-8CCE-E2936771BA35}]**
**                                                                            **
**                                                                            **
** Syntax            : uint64 Bfx_lExtPosEQ0WidthGT32                         **
**                     (                                                      **
**                       const uint64 Value,                                  **
**                       const uint8 Width                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_lExtPosEQ0WidthGT32 function returns the bits  **
**                     from the Value parameter starting from bit position 0  **
**                     for Width greater than 32 number of bits. The function **
**                     is implemented for 64 bit data.                        **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : None                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Value - Input data                                     **
**                     Width - Bit field length (Valid range: 33 to 63)       **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : uint64 - Extracted data                                **
*******************************************************************************/
LOCAL_INLINE uint64 Bfx_lExtPosEQ0WidthGT32(const uint64 Value,
                                             const uint8 Width)
{
  /*Pos=BFX_MIN_POS & Width>BFX_WORD_LENGTH*/

  uint64 ResultVal=0U;

  #ifdef _TASKING_C_TRICORE_
  #if (_TASKING_C_TRICORE_ == 1U)
  __asm("mov %0.0,%1.0""\n\t"\
    "mov d12,%3""\n\t"\
    "mov d13,%2""\n\t"\
    "extr.u %0.1,%1.1,e12""\n\t"\
    : "=&e"(ResultVal)\
    : "e"(Value), "d"(Width), "i" (BFX_MIN_POS)\
    : "d12", "d13");
  #endif /* #if (_TASKING_C_TRICORE_ == 1U) */
  #endif /* _TASKING_C_TRICORE_ */

  #ifdef _GNU_C_TRICORE_
  #if (_GNU_C_TRICORE_ == 1U)
  __asm__ volatile(/*Extract the entire lower word using mov and the remaining
    bits using extr to the upper word.*/
    /*For extr: pos=0=E[d][4:0]=d12[4:0]*/
    /*For extr: width=Width-32=E[d][36:32]=d13[4:0]*/
    "mov %L0,%L1""\n\t"\
    "mov %%d12,%3""\n\t"\
    "mov %%d13,%2""\n\t"\
    "extr.u %H0,%H1,%%e12""\n\t"\
    : "+&d" (ResultVal)\
    : "d" (Value), "d" (Width), "i" (BFX_MIN_POS)\
    : "d12", "d13");
  #endif /* #if (_GNU_C_TRICORE_ == 1U) */
  #endif /* _GNU_C_TRICORE_ */

  #ifdef _DIABDATA_C_TRICORE_
  #if (_DIABDATA_C_TRICORE_ == 1U)
  ResultVal = BFX_EXTRACT64BITS_DCC_PosEQ0WidthGT32(Value, Width);
  #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
  #endif /* _DIABDATA_C_TRICORE_ */

  #ifdef _GHS_C_TRICORE_
  #if (_GHS_C_TRICORE_ == 1U)
  __asm__ volatile(/*Extract the entire lower word using mov and the remaining
    bits using extr to the upper word.*/
    /*For extr: pos=0=E[d][4:0]=d12[4:0]*/
    /*For extr: width=Width-32=E[d][36:32]=d13[4:0]*/
    "mov %L0,%L1""\n\t"\
    "mov %%d12,%3""\n\t"\
    "mov %%d13,%2""\n\t"\
    "extr.u %H0,%H1,%%e12""\n\t"\
    : "+&d" (ResultVal)\
    : "d" (Value), "d" (Width), "i"(BFX_MIN_POS)\
    : "d12", "d13");
  #endif /* #if (_GHS_C_TRICORE_ == 1U) */
  #endif /* _GHS_C_TRICORE_ */

  #if ((!defined(_TASKING_C_TRICORE_)) && (!defined(_GNU_C_TRICORE_)) &&\
       (!defined(_DIABDATA_C_TRICORE_)) && (!defined(_GHS_C_TRICORE_)))
  #error Unsupported compiler configured!
  #endif

  return ResultVal;

  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
}

/*******************************************************************************
** Traceability      : [cover parentID={0AB76AF6-1C98-4ea3-8CDC-1F88AB51DD54}]**
**                                                                            **
**                                                                            **
** Syntax            : uint64 Bfx_lExtPosEQ32Or0WidthEQ32                     **
**                     (                                                      **
**                       const uint64 Value,                                  **
**                       const uint8 Pos                                      **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_lExtPosEQ32Or0WidthEQ32 function returns the   **
**                     entire higher or lower word from the Value parameter   **
**                     for a Width of 32 bits based on the value of Pos. If   **
**                     the value of Pos is 32 then the function extracts the  **
**                     complete higher word or if the value of Pos is 0 then  **
**                     the function extracts the complete lower word.         **
**                     The function is implemented for 64 bit data.           **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : None                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Value - Input data                                     **
**                     Pos   - Start bit position (Valid range: 0 and 32)     **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : uint64 - Extracted data                                **
*******************************************************************************/
LOCAL_INLINE uint64 Bfx_lExtPosEQ32Or0WidthEQ32(const uint64 Value,
                                                const uint8 Pos)
{
  /*Width=BFX_WORD_LENGTH & Pos=BFX_WORD_LENGTH or BFX_MIN_POS*/

  uint64 ResultVal=0U;

  #ifdef _TASKING_C_TRICORE_
  #if (_TASKING_C_TRICORE_ == 1U)
  __asm("mov %0.1,%3""\n\t"\
    "sel %0.0,%2,%1.1,%1.0""\n\t"\
    : "=&e"(ResultVal)\
    : "e"(Value), "d"(Pos), "i"(BFX_MIN_POS));
  #endif /* #if (_TASKING_C_TRICORE_ == 1U) */
  #endif /* _TASKING_C_TRICORE_ */

  #ifdef _GNU_C_TRICORE_
  #if (_GNU_C_TRICORE_ == 1U)
  __asm__ volatile(/*Select the lower word if Pos is 0 or the higher word
    if Pos is 32 and then place it in lower word using sel*/
    "sel %L0,%2,%H1,%L1""\n\t"\
    : "+&d" (ResultVal)\
    : "d" (Value), "d" (Pos));
  #endif /* #if (_GNU_C_TRICORE_ == 1U) */
  #endif /* _GNU_C_TRICORE_ */

  #ifdef _DIABDATA_C_TRICORE_
  #if (_DIABDATA_C_TRICORE_ == 1U)
  ResultVal = BFX_EXTRACT64BITS_DCC_PosEQ32Or0WidthEQ32(Value, Pos);
  #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
  #endif /* _DIABDATA_C_TRICORE_ */

  #ifdef _GHS_C_TRICORE_
  #if (_GHS_C_TRICORE_ == 1U)
  __asm__ volatile(/*Select the lower word if Pos is 0 or the higher word
    if Pos is 32 and then place it in lower word using sel*/
    "sel %L0,%2,%H1,%L1""\n\t"\
    : "+&d" (ResultVal)\
    : "d" (Value), "d" (Pos));
  #endif /* #if (_GHS_C_TRICORE_ == 1U) */
  #endif /* _GHS_C_TRICORE_ */

  #if ((!defined(_TASKING_C_TRICORE_)) && (!defined(_GNU_C_TRICORE_)) &&\
       (!defined(_DIABDATA_C_TRICORE_)) && (!defined(_GHS_C_TRICORE_)))
  #error Unsupported compiler configured!
  #endif

  return ResultVal;

  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
}

/*******************************************************************************
** Traceability      : [cover parentID={B63AD29B-4FED-4a28-B8A8-D0E6B04D0B4E}]**
**                                                                            **
**                                                                            **
** Syntax            : uint64 Bfx_lExtPosLT32WidthLT32SumLT32                 **
**                     (                                                      **
**                       const uint64 Value,                                  **
**                       const uint8 Pos,                                     **
**                       const uint8 Width                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_lExtPosLT32WidthLT32SumLT32 function returns   **
**                     the bits from the Value parameter starting from bit    **
**                     position Pos with values less than 32 for Width less   **
**                     than 32 number of bits and the sum of Pos and Width    **
**                     less than 32. The function is implemented for          **
**                     64 bit data.                                           **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : None                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Value - Input data                                     **
**                     Pos   - Start bit position (Valid range: 0 to 30)      **
**                     Width - Bit field length                               **
**                             (Valid range: 1 to (31-Pos)                    **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : uint64 - Extracted data                                **
*******************************************************************************/
LOCAL_INLINE uint64 Bfx_lExtPosLT32WidthLT32SumLT32(const uint64 Value,
                                                    const uint8 Pos,
                                                    const uint8 Width)
{
  /*Pos<BFX_WORD_LENGTH, Width<BFX_WORD_LENGTH & (Pos+Width)<BFX_WORD_LENGTH*/

  uint64 ResultVal=0U;

  #ifdef _TASKING_C_TRICORE_
  #if (_TASKING_C_TRICORE_ == 1U)
  __asm("mov %0.1,%4""\n\t"\
    "mov d12,%2""\n\t"\
    "mov d13,%3""\n\t"\
    "extr.u %0.0,%1.0,e12""\n\t"\
    : "=&e"(ResultVal)\
    : "e"(Value), "d"(Pos), "d"(Width), "i" (BFX_MIN_POS)\
    : "d12", "d13");
  #endif /* #if (_TASKING_C_TRICORE_ == 1U) */
  #endif /* _TASKING_C_TRICORE_ */

  #ifdef _GNU_C_TRICORE_
  #if (_GNU_C_TRICORE_ == 1U)
  __asm__ volatile(/*Extract data partially from the lower word*/
    /*For extr:pos=Pos and width=Width*/
    "mov %%d12,%2""\n\t"\
    "mov %%d13,%3""\n\t"\
    "extr.u %L0,%L1,%%e12""\n\t"\
    : "+&d" (ResultVal)\
    : "d" (Value), "d" (Pos), "d" (Width)\
    : "d12", "d13");
  #endif /* #if (_GNU_C_TRICORE_ == 1U) */
  #endif /* _GNU_C_TRICORE_ */

  #ifdef _DIABDATA_C_TRICORE_
  #if (_DIABDATA_C_TRICORE_ == 1U)
  ResultVal = BFX_EXTRACT64BITS_DCC_PosLT32WidthLT32SumLT32(Value, Pos, Width);
  #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
  #endif /* _DIABDATA_C_TRICORE_ */

  #ifdef _GHS_C_TRICORE_
  #if (_GHS_C_TRICORE_ == 1U)
  __asm__ volatile(/*Extract data partially from the lower word*/
    /*For extr:pos=Pos and width=Width*/
    "mov %%d12,%2""\n\t"\
    "mov %%d13,%3""\n\t"\
    "extr.u %L0,%L1,%%e12""\n\t"\
    : "+&d" (ResultVal)\
    : "d" (Value), "d" (Pos), "d" (Width)\
    : "d12", "d13");
  #endif /* #if (_GHS_C_TRICORE_ == 1U) */
  #endif /* _GHS_C_TRICORE_ */

  #if ((!defined(_TASKING_C_TRICORE_)) && (!defined(_GNU_C_TRICORE_)) &&\
       (!defined(_DIABDATA_C_TRICORE_)) && (!defined(_GHS_C_TRICORE_)))
  #error Unsupported compiler configured!
  #endif

  return ResultVal;

  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
}

/*******************************************************************************
** Traceability      : [cover parentID={5C64D5D1-DE2C-46da-B4AF-0A166104314B}]**
**                                                                            **
**                                                                            **
** Syntax            : uint64 Bfx_lExtPosLT32WidthLT32SumGTE32                **
**                     (                                                      **
**                       const uint64 Value,                                  **
**                       const uint8 Pos,                                     **
**                       const uint8 Width                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_lExtPosLT32WidthLT32SumGTE32 function returns  **
**                     the extracted bits from the Value parameter starting   **
**                     from bit position Pos with values less than 32 for     **
**                     Width less than 32 number of bits and the sum of Pos   **
**                     and Width greater than or equal to 32. The function is **
**                     implemented for 64-bit data.                           **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : None                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Value - Input data                                     **
**                     Pos   - Start bit position (Valid range: 1 to 31)      **
**                     Width - Bit field length                               **
**                             (Valid range: (32-Pos) to 31)                  **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : uint64 - Extracted data                                **
*******************************************************************************/
LOCAL_INLINE uint64 Bfx_lExtPosLT32WidthLT32SumGTE32(const uint64 Value,
                                                     const uint8 Pos,
                                                     const uint8 Width)
{
  /*Pos<BFX_WORD_LENGTH, Width<BFX_WORD_LENGTH & (Pos+Width)>=BFX_WORD_LENGTH)*/

  uint64 ResultVal=0U;

  #ifdef _TASKING_C_TRICORE_
  #if (_TASKING_C_TRICORE_ == 1U)
  __asm("mov %0.1,%5""\n\t"\
    "mov d12,%4""\n\t"\
    "rsub d13,%2,%4""\n\t"\
    "dextr d11,%1.1,%1.0,d13""\n\t"\
    "mov d13,%3""\n\t"\
    "extr.u %0.0,d11,e12""\n\t"\
    : "=&e"(ResultVal)\
    : "e"(Value), "d"(Pos), "d"(Width),"i"(BFX_WORD_LENGTH),"i" (BFX_MIN_POS)\
    : "d11","d12", "d13");
  #endif /* #if (_TASKING_C_TRICORE_ == 1U) */
  #endif /* _TASKING_C_TRICORE_ */

  #ifdef _GNU_C_TRICORE_
  #if (_GNU_C_TRICORE_ == 1U)
  __asm__ volatile(/*Extract 32 bits starting from Pos using dextr
    and then extract the Width bits from the dextracted word*/
    /*For extr:pos=0=E[d][4:0]=d12[4:0] and width=Width=E[d][36:32]=d13[4:0]*/
    "mov %%d12,%4""\n\t"\
    "rsub %%d13,%2,%4""\n\t"\
    "dextr %%d11,%H1,%L1,%%d13""\n\t"\
    "mov %%d13,%3""\n\t"\
    "extr.u %L0,%%d11,%%e12""\n\t"\
    : "+&d" (ResultVal)\
    : "d" (Value), "d" (Pos), "d" (Width),"i"(BFX_WORD_LENGTH)\
    : "d11","d12", "d13");
  #endif /* #if (_GNU_C_TRICORE_ == 1U) */
  #endif /* _GNU_C_TRICORE_ */

  #ifdef _DIABDATA_C_TRICORE_
  #if (_DIABDATA_C_TRICORE_ == 1U)
  ResultVal = BFX_EXTRACT64BITS_DCC_PosLT32WidthLT32SumGTE32(Value, Pos, Width);
  #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
  #endif /* _DIABDATA_C_TRICORE_ */

  #ifdef _GHS_C_TRICORE_
  #if (_GHS_C_TRICORE_ == 1U)
  __asm__ volatile(/*Extract 32 bits starting from Pos using dextr
    and then extract the Width bits from the dextracted word*/
    /*For extr:pos=0=E[d][4:0]=d12[4:0] and width=Width=E[d][36:32]=d13[4:0]*/
    "mov %%d12,%4""\n\t"\
    "rsub %%d13,%2,%4""\n\t"\
    "dextr %%d11,%H1,%L1,%%d13""\n\t"\
    "mov %%d13,%3""\n\t"\
    "extr.u %L0,%%d11,%%e12""\n\t"\
    : "+&d" (ResultVal)\
    : "d" (Value), "d" (Pos), "d" (Width), "i"(BFX_WORD_LENGTH)\
    : "d11","d12", "d13");
  #endif /* #if (_GHS_C_TRICORE_ == 1U) */
  #endif /* _GHS_C_TRICORE_ */

  #if ((!defined(_TASKING_C_TRICORE_)) && (!defined(_GNU_C_TRICORE_)) &&\
       (!defined(_DIABDATA_C_TRICORE_)) && (!defined(_GHS_C_TRICORE_)))
  #error Unsupported compiler configured!
  #endif

  return ResultVal;

  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
}

/*******************************************************************************
** Traceability      : [cover parentID={EEABD022-A7D0-4b1b-9AFE-AB93984F7D0D},**
**                                     {44B965C9-ADC0-4ebd-BF53-2C409B6CC3F7}]**
**                                                                            **
**                                                                            **
** Syntax            : uint8 Bfx_lParity                                      **
**                     (                                                      **
**                       const uint32 Value                                   **
**                     )                                                      **
** Description       : The Bfx_lParity function returns the odd parity of     **
**                     the Value parameter.                                   **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : None                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Value - Input data for parity check                    **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : uint8 - Odd parity                                     **
*******************************************************************************/

LOCAL_INLINE uint8 Bfx_lParity(const uint32 Value)
{
  uint8 ResultVal = 0x0U;

  #ifdef _TASKING_C_TRICORE_
  #if (_TASKING_C_TRICORE_ == 1U)
  __asm("popcnt.w d14, %1""\n\t" \
        "and %0, d14, %2" \
        : "=d"(ResultVal) \
        : "d"(Value), "i"(BFX_MASK_ALL_EXCEPT_LSB) \
        : "d14");
  #endif /* #if (_TASKING_C_TRICORE_ == 1U) */
  #endif /* _TASKING_C_TRICORE_ */

  #ifdef _GNU_C_TRICORE_
  #if (_GNU_C_TRICORE_ == 1U)
  __asm__("popcnt.w %%d14, %1""\n\t" \
          "and %0, %%d14, %2" \
          : "=d"(ResultVal) \
          : "d"(Value), "i"(BFX_MASK_ALL_EXCEPT_LSB) \
          : "d14");
  #endif /* #if (_GNU_C_TRICORE_ == 1U) */
  #endif /* _GNU_C_TRICORE_ */

  #ifdef _DIABDATA_C_TRICORE_
  #if (_DIABDATA_C_TRICORE_ == 1U)
  ResultVal = BFX_PARITY_DCC(Value);
  #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
  #endif

  #ifdef _GHS_C_TRICORE_
  #if (_GHS_C_TRICORE_ == 1U)
  __asm ("popcnt.w %%d14, %1""\n\t" \
         "and %0, %%d14, %2" \
         : "=d"(ResultVal) \
         : "d"(Value), "i"(BFX_MASK_ALL_EXCEPT_LSB) \
         : "d14");
  #endif /* #if (_GHS_C_TRICORE_ == 1U) */
  #endif /* _GHS_C_TRICORE_ */

  #if ((!defined(_TASKING_C_TRICORE_)) && (!defined(_GNU_C_TRICORE_)) &&\
       (!defined(_DIABDATA_C_TRICORE_)) && (!defined(_GHS_C_TRICORE_)))
  #error Unsupported compiler configured!
  #endif

  return ResultVal;
  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
}


/*******************************************************************************
** Traceability      : [cover parentID={5CA5BD48-2554-4172-BF6E-89FF26CF326C},**
**                                     {44B965C9-ADC0-4ebd-BF53-2C409B6CC3F7}]**
**                                                                            **
**                                                                            **
** Syntax            : uint8 Bfx_lParity64Bits                                **
**                     (                                                      **
**                       const uint64 Value                                   **
**                     )                                                      **
** Description       : The Bfx_lParity64Bits function returns the odd         **
**                     parity of the Value parameter.                         **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : None                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Value - Input data for parity check                    **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : uint8 - Odd parity                                     **
*******************************************************************************/
LOCAL_INLINE uint8 Bfx_lParity64Bits(const uint64 Value)
{
  uint8 ResultVal = 0x0U;

  #ifdef _TASKING_C_TRICORE_
  #if (_TASKING_C_TRICORE_ == 1U)
  __asm("popcnt.w d12, %1.0""\n\t" \
        "popcnt.w d13, %1.1""\n\t" \
        "xor.t %0,d12, %2, d13, %2""\n\t" \
        : "=d"(ResultVal) \
        : "e"(Value),"i"(BFX_MIN_POS) \
        : "d12","d13");
  #endif /* #if (_TASKING_C_TRICORE_ == 1U) */
  #endif /* _TASKING_C_TRICORE_ */

  #ifdef _GNU_C_TRICORE_
  #if (_GNU_C_TRICORE_ == 1U)
  __asm__("popcnt.w %%d12, %L1""\n\t" \
          "popcnt.w %%d13, %H1""\n\t" \
          "xor.t %0, %%d12,%2, %%d13, %2""\n\t" \
          : "+&d"(ResultVal) \
          : "d"(Value),"i"(BFX_MIN_POS) \
          : "d12","d13");
  #endif /* #if (_GNU_C_TRICORE_ == 1U) */
  #endif /* _GNU_C_TRICORE_ */

  #ifdef _DIABDATA_C_TRICORE_
  #if (_DIABDATA_C_TRICORE_ == 1U)
  ResultVal = BFX_PARITY64BITS_DCC(Value);
  #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
  #endif

  #ifdef _GHS_C_TRICORE_
  #if (_GHS_C_TRICORE_ == 1U)
  __asm__("popcnt.w %%d12, %L1""\n\t" \
          "popcnt.w %%d13, %H1""\n\t" \
          "xor.t %0,%%d12, %2, %%d13, %2""\n\t" \
          : "=d"(ResultVal) \
          : "d"(Value),"i"(BFX_MIN_POS) \
          : "d12","d13");
  #endif /* #if (_GHS_C_TRICORE_ == 1U) */
  #endif /* _GHS_C_TRICORE_ */

  #if ((!defined(_TASKING_C_TRICORE_)) && (!defined(_GNU_C_TRICORE_)) &&\
       (!defined(_DIABDATA_C_TRICORE_)) && (!defined(_GHS_C_TRICORE_)))
  #error Unsupported compiler configured!
  #endif


  return ResultVal;
  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
}


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

#endif /* BFX_LOCAL_H */
