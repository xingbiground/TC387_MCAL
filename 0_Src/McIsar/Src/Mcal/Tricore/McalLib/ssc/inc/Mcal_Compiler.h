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
**  FILENAME     : Mcal_Compiler.h                                            **
**                                                                            **
**  VERSION      : 25.0.0                                                     **
**                                                                            **
**  DATE         : 2023-05-16                                                 **
**                                                                            **
**  VARIANT      : NA                                                         **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION : This header file exports Mcal compiler specific             **
                   functions and macros                                       **
**                                                                            **
**  SPECIFICATION(S) : Specification of Compiler Abstraction, AUTOSAR         **
**                     Release 4.2.2  and 4.4.0                               **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
** Traceability     : [cover parentID={8763BB07-0320-4376-B4AA-D8E4AD40C12C}]**
*******************************************************************************/
#ifndef MCAL_COMPILER_H
#define MCAL_COMPILER_H



#include "Std_Types.h"
#include "Compiler.h"

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#ifdef _GNU_C_TRICORE_
#if (_GNU_C_TRICORE_ == 1U)
#include "machine/intrinsics.h"
#endif
#endif

#ifdef _DIABDATA_C_TRICORE_
#if (_DIABDATA_C_TRICORE_ == 1U)
#include "diab/tcasm.h"
#endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
#endif

#ifdef _GHS_C_TRICORE_
#if (_GHS_C_TRICORE_ == 1U)
#include "intrinsics.h"
#endif /* #if (_GHS_C_TRICORE_ == 1U) */
#endif


/*******************************************************************************
**                      Configuration data                                    **
*******************************************************************************/
/* [cover parentID={3ADDF021-6F50-4792-A2EE-4C4DB2513503}][/cover] */
/* [cover parentID={2BE469DD-6154-4e2a-99C2-FE17F1965089}][/cover] */
typedef unsigned int unsigned_int;

/*
 Keyword for IFX_NO_INLINE
*/
#ifdef _TASKING_C_TRICORE_
#if (_TASKING_C_TRICORE_ == 1U)

#ifndef IFX_NO_INLINE
#define IFX_NO_INLINE __noinline

#endif
/* #ifndef IFX_NO_INLINE */
#endif
/*#ifdef(_TASKING_C_TRICORE_)*/
#endif

#ifdef _GNU_C_TRICORE_
#if (_GNU_C_TRICORE_ == 1U)
#ifndef IFX_NO_INLINE

#define IFX_NO_INLINE __attribute__ ((noinline))
#endif
/* #ifndef IFX_NO_INLINE */
#endif
/*#ifdef(_GNU_C_TRICORE_)*/
#endif

#ifdef _DIABDATA_C_TRICORE_
#if (_DIABDATA_C_TRICORE_ == 1U)
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define IFX_NO_INLINE __attribute__ ((noinline))
#endif
/*#if (_DIABDATA_C_TRICORE_ == 1U)*/
#endif

#ifdef _GHS_C_TRICORE_
#if (_GHS_C_TRICORE_ == 1U)
#ifndef IFX_NO_INLINE
#define IFX_NO_INLINE __noinline
#endif
/*#ifdef(_GHS_C_TRICORE_)*/
#endif
#endif

/* [cover parentID={62B6B189-142A-46b4-8C1C-477F1887CD23}]
 * Intrensic Functions
 * [/cover] */
#ifdef _TASKING_C_TRICORE_
#if (_TASKING_C_TRICORE_ == 1U)
/*
Tasking Intrinsic: Insert ISYNC Instruction
*/
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define ISYNC() (__isync())

/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define DSYNC() __asm("dsync" \
                       :::)

/* Tasking Intrinsic: Disable Global Interrupt Flag */
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define DISABLE() (__disable())
/* Tasking Intrinsic: Enable Global Interrupt Flag */
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define ENABLE() (__enable())

/*
Tasking Intrinsic: move contents of the addressed core SFR into a data register
*/
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define MFCR(Reg) (__mfcr((sint32)(Reg)))

/*
Tasking Intrinsic:  Move contents of a data register (Data)
to the addressed core SFR (Reg).
For Tasking compiler,ISYNC is part of __mtcr call, hence not added in the macro
definition
*/
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define MTCR(Reg, Data)   DSYNC();\
                          __mtcr((sint32)(Reg), (sint32)(Data))

/* Tasking Intrinsic: No operation */
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define NOP() (__nop())

/*
Tasking Intrinsic: CRC32 instruction
*/
/* CRC32 function calculates the CRC of four bytes in big-endian order for the
   given input.*/
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define CRC32(b, a) (__crc32bw((unsigned_int)(b),(unsigned_int)(a)))

/*
Tasking Intrinsic: CRC32B instruction
*/
/* CRC32B function calculates the CRC of 8 bits input data in which the least
   significant bit is processed first and most significant bit is processed
   last*/
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define CRC32B(b, a) (__crc32b((unsigned_int)(b),(unsigned_int)(a)))

/*
 * Tasking Intrinsic: CRCN instruction
 * CRCN function calculates the CRC of 1 to 8 bits of input data with width 1 to
 * 16 bit.
 * d : parameters of crc algorithm
 *
 * Bit31    15      12         10       9        8                2         Bit0
 *  ---------------------------------------------------------------------------
 * |        |        |         |        |        |                |    input   |
 * | poly-  | CRC    |    0    | inver  | bit    |        0       |    data    |
 * | nomial | width  |         | sion   | order  |                |    width   |
 * |        | (1-16) |         |        |        |                |    (1-8)   |
 *  ---------------------------------------------------------------------------
 * b : initial seed value or CRC of previous sequence of data
 * a : input data
 */
 /*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define CRCN(d, b, a) \
                (__crcn((unsigned_int)(b),(unsigned_int)(d), (unsigned_int)(a)))

#endif
#endif

#ifdef _GNU_C_TRICORE_
#if (_GNU_C_TRICORE_ == 1U)

/* CRC32 function calculates the CRC of four bytes in big-endian order for the
   given input.*/
#define CRC32(b, a) (__crc32bw((unsigned_int)(b),(unsigned_int)(a)))

/* CRC declaration to ensure this function is always inlined */
static INLINE unsigned __crc32bw( unsigned b, unsigned a ) \
__attribute__ ((always_inline));

/* Calculate the CRC of register D[a] and the inverse of register D[b] and
put the result in D[res].
The CRC polynomial used is the CRC-32 polynomial as defined in the IEEE 802.3
standard. The initial value of D[b] should be zero
*/
static INLINE unsigned __crc32bw( unsigned b, unsigned a ) {
  unsigned res;
  __asm__ volatile("crc32b.w %0, %1, %2" :"=d"(res) : "d"(b), "d"(a): "memory");
    return res;
}

/* CRC32B function calculates the CRC of 8 bits input data in which the least
   significant bit is processed first and most significant bit is processed
   last*/
/* MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
   intrinsic function*/
#define CRC32B(b, a) (__crc32b((unsigned_int)(b),(unsigned_int)(a)))

/* CRC declaration to ensure this function is always inlined */
static INLINE unsigned __crc32b( unsigned b, unsigned a ) \
__attribute__ ((always_inline));

/* Calculate the CRC of register D[a] and the intial seed value of register D[b]
and put the result in D[res].
The CRC polynomial used is the CRC-32 polynomial as defined in the IEEE 802.3
standard. The initial value of D[b] should be zero
*/
static INLINE unsigned __crc32b( unsigned b, unsigned a ) {
  unsigned res;
  __asm__ volatile("crc32.b %0, %1, %2" :"=d"(res) : "d"(b), "d"(a): "memory");
    return res;
}


/*
 * CRCN function calculates the CRC of 1 to 8 bits of input data with width 1 to
 * 16 bit.
 */
/* [cover parentID={559F1AC9-23F4-4bc7-A192-3F268CFF3B28}][/cover] */
/* MISRA2012_RULE_19_07_STATUS:Function like macro used to call the Tricore
   intrinsic function*/
#define CRCN(d, b, a) \
                (__crcn ((unsigned_int)(d),(unsigned_int)(b),(unsigned_int)(a)))

/* CRCN declaration to ensure this function is always inlined */
static INLINE unsigned __crcn( unsigned d, unsigned b , unsigned a) \
__attribute__ ((always_inline));

/*
 * d : parameters of crc algorithm
 *
 * Bit31    15      12         10       9        8                2         Bit0
 *  ---------------------------------------------------------------------------
 * |        |        |         |        |        |                |    input   |
 * | poly-  | CRC    |    0    | inver  | bit    |        0       |    data    |
 * | nomial | width  |         | sion   | order  |                |    width   |
 * |        | (1-16) |         |        |        |                |    (1-8)   |
 *  ---------------------------------------------------------------------------
 * b : initial seed value or CRC of previous sequence of data
 * a : input data
*/
static INLINE unsigned __crcn( unsigned d, unsigned b, unsigned a) {
  unsigned res;
  __asm__ volatile
             ("crcn %0,%1,%2,%3" :"=d"(res) : "d"(b), "d"(d), "d"(a): "memory");
    return res;
}

/*
Hitech Intrinsic: Insert ISYNC Instruction
*/
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define ISYNC() _isync()

/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define DSYNC() _dsync()

/* Intrinsic: Disable Global Interrupt Flag */
/*MISRA2012_RULE_19_07_STATUS:Function like macro used to call the Tricore
intrinsic function*/
#define DISABLE() _disable()

/* Intrinsic: Enable Global Interrupt Flag */
/*MISRA2012_RULE_19_07_STATUS:Function like macro used to call the Tricore
intrinsic function*/
#define ENABLE() _enable()

/* Intrinsic: : move contents of the addressed core SFR into a data register */
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define MFCR(Reg) (__mfcr((Reg)))
/*
Intrinsic:  Move contents of a data register (Data)
to the addressed core SFR (Reg)
*/
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define MTCR(Reg, Data)   DSYNC();\
                          __mtcr((Reg), (Data));\
                          ISYNC()

/*********************************************************************
 * MTCR
 **********************************************************************/

/* Intrinsic: No operation */
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define NOP() (_nop())
#endif
#endif

#ifdef _GHS_C_TRICORE_
#if (_GHS_C_TRICORE_ == 1U)
/*
Greenhills Intrinsic: Insert ISYNC Instruction
*/
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define ISYNC() __isync()

/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define DSYNC() __dsync()
/* Intrinsic: Disable Global Interrupt Flag */
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define DISABLE() __disable()
/* Intrinsic: Enable Global Interrupt Flag */
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define ENABLE() __enable()
#define NOP() __nop()

/* Intrinsic: : move contents of the addressed core SFR into a data register */
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define MFCR(Reg) (__mfcr(((sint32)Reg)))

/*
Greenhills Intrinsic:  Move contents of a data register (Data)
to the addressed core SFR (Reg).
*/
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define MTCR(Reg, Data)   DSYNC();\
                          __mtcr((Reg), (Data));\
                          ISYNC()
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
//#define NOP() __nop()

/*
Greenhills Intrinsic: CRC32 instruction
*/
/* CRC32 function calculates the CRC of four bytes in big-endian order for the
   given input.*/
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
  intrinsic function*/
#define CRC32(b, a) (__crc32bw((unsigned_int)(b),(unsigned_int)(a)))

/* CRC declaration to ensure this function is always inlined */
static INLINE unsigned __crc32bw( unsigned b, unsigned a ) \
__attribute__ ((always_inline));

/* Calculate the CRC of register D[a] and the inverse of register D[b] and
put the result in D[res].
The CRC polynomial used is the CRC-32 polynomial as defined in the IEEE 802.3
standard. The initial value of D[b] should be zero
*/
static INLINE unsigned __crc32bw( unsigned b, unsigned a ) {
  unsigned res;
  __asm__ volatile("crc32b.w %0, %1, %2" :"=d"(res) : "d"(b), "d"(a): "memory");
    return res;
}

/* CRC32B function calculates the CRC of 8 bits input data in which the least
   significant bit is processed first and most significant bit is processed
   last*/
/* MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
   intrinsic function*/
#define CRC32B(b, a) (__crc32b((unsigned_int)(b),(unsigned_int)(a)))

/* crcb declaration to ensure this function is always inlined */
static INLINE unsigned __crc32b( unsigned b, unsigned a ) \
__attribute__ ((always_inline));

/* Calculate the CRC of register D[a] and the intial seed value D[b] and
put the result in D[res].
The CRC polynomial used is the CRC-32 polynomial as defined in the IEEE 802.3
standard. The initial value of D[b] should be zero
*/
static INLINE unsigned __crc32b( unsigned b, unsigned a ) {
  unsigned res;
  __asm__ volatile("crc32.b %0, %1, %2" :"=d"(res) : "d"(b), "d"(a): "memory");
    return res;
}

/*
 * CRCN function calculates the CRC of 1 to 8 bits of input data with width 1 to
 * 16 bit.
 */
/* [cover parentID={559F1AC9-23F4-4bc7-A192-3F268CFF3B28}][/cover] */
/* MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
   intrinsic function*/
#define CRCN(d, b, a) \
                (__crcn((unsigned_int)(d),(unsigned_int)(b), (unsigned_int)(a)))

/* CRCN declaration to ensure this function is always inlined */
static INLINE unsigned __crcn( unsigned d, unsigned b , unsigned a) \
__attribute__ ((always_inline));

/*
 * d : parameters of crc algorithm
 *
 * Bit31    15      12         10       9        8                2         Bit0
 *  ---------------------------------------------------------------------------
 * |        |        |         |        |        |                |    input   |
 * | poly-  | CRC    |    0    | inver  | bit    |        0       |    data    |
 * | nomial | width  |         | sion   | order  |                |    width   |
 * |        | (1-16) |         |        |        |                |    (1-8)   |
 *  ---------------------------------------------------------------------------
 * b : initial seed value or CRC of previous sequence of data
 * a : input data
 */
static INLINE unsigned __crcn( unsigned d, unsigned b, unsigned a) {
  unsigned res;

  __asm__ volatile
            ("crcn %0,%1,%2,%3": "=d"(res) : "d"(b), "d"(d), "d"(a) : "memory");
    return res;
}

#endif /* #ifdef _GHS_C_TRICORE_ */
#endif

#ifdef _DIABDATA_C_TRICORE_
#if (_DIABDATA_C_TRICORE_ == 1U)
/*
 * Hitech Intrinsic: Insert ISYNC Instruction
 */
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define ISYNC() __isync()

/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define DSYNC() __dsync()
/* Intrinsic: Disable Global Interrupt Flag */
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define DISABLE() _disable()
/* Intrinsic: Enable Global Interrupt Flag */
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define ENABLE() _enable()
#define NOP() _nop()

#define __dsync _dsync
#define __isync _isync
#define __mtcr _mtcr
#define __mfcr _mfcr
#define __abs _abs

/* Intrinsic: move contents of the addressed core SFR into a data register */
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define MFCR(Reg) (__mfcr((Reg)))
/*
 * Intrinsic:  Move contents of a data register (Data)
 * to the addressed core SFR (Reg)
 */
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define MTCR(Reg, Data)   DSYNC();\
                          __mtcr((Reg), (Data));\
                          ISYNC()
/* CRC32 function calculates the CRC of four bytes in big-endian order for the
   given input.*/
/* [cover parentID={8D500009-8000-4755-9A00-A1F075900E89}][/cover] */
/*MISRA2012_RULE_19_07_STATUS:Function like macro used to call the Tricore
intrinsic function*/
#define CRC32(b, a) (__crc32bw((unsigned_int)(b),(unsigned_int)(a)))

/* CRC32B function calculates the CRC of 8 bits input data in which the least
   significant bit is processed first and most significant bit is processed
   last*/
/* [cover parentID={D5E171A5-F94B-4e80-A365-4028FF7B9B11} ][/cover] */
/* MISRA2012_RULE_19_07_STATUS:Function like macro used to call the Tricore
   intrinsic function*/
#define CRC32B(b, a) (__crc32b((unsigned_int)(b),(unsigned_int)(a)))

/*
 * CRCN function calculates the CRC of 1 to 8 bits of input data with width 1 to
 * 16 bit.
 */
/* [cover parentID={559F1AC9-23F4-4bc7-A192-3F268CFF3B28}][/cover] */
/* MISRA2012_RULE_19_07_STATUS:Function like macro used to call the Tricore
   intrinsic function*/
#define CRCN(d, b, a) \
                (__crcn((unsigned_int)(d),(unsigned_int)(b), (unsigned_int)(a)))

#endif /* #ifdef _DIABDATA_C_TRICORE_ */
#endif

#ifdef _GNU_C_TRICORE_
#if (_GNU_C_TRICORE_ == 1U)
#ifndef __indirect
#define __indirect
#endif
#endif
#endif

#ifdef _DIABDATA_C_TRICORE_
#if (_DIABDATA_C_TRICORE_ == 1U)
#ifndef __indirect
#define __indirect
#endif /* (_DIABDATA_C_TRICORE_ == 1U) */
#endif
#endif

/*******************************************************************************
** Macro Syntax : IMASKLDMST(Address, Value, Offset, Bits)                    **
**                                                                            **
** Parameters (in) :  Address: Address of the Variable to be Modified         **
**                    Value  : Value to be written                            **
**                    Offset : Bit Offset from LSB                            **
**                    Bits   : No of Bits Modified                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Description    : IMASKLDMST is used to write atomic instructions in        **
**                  code.The function writes the number of bits of an integer **
**                  value at a certain address location in memory with a      **
**                  bitoffset. The number of bits must be a constant value    **
**                  Note that the Address must be Word Aligned.A direct type  **
**                  cast to "int"is needed to avoid Misra Violation           **
*******************************************************************************/

/*
Use of Atomic Write Intrinsic from Tasking.
*/

/*
The default option provided here:
extended imaskldmst, that helps to execute
ldmst irrespective of variable allocation. NEAR / FAR
boundary.

If the user desires to use TASKING LDMST
the following is the convention.
Caveat: the variable should be placed in
NEAR section.
A direct type cast to "int"
is needed to avoid Misra Violation

#define IMASKLDMST(address,val,offset,bits)  \
  __imaskldmst((sint32*)(address),\
                                 (sint32)(val),     \
                                 (sint32)(offset),  \
                                 (sint32)(bits))

*/
#ifdef _TASKING_C_TRICORE_
#if (_TASKING_C_TRICORE_ == 1U)
/* [cover parentID={A1FBBD4D-8040-42e0-80F9-7577CAB1099B}][/cover] */
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
/*MISRA2012_RULE_20_10_JUSTIFICATION: The "#" operator is used only to indicate
  a constant used to set the number of bits required for IMASK instruction as
  per inline assembly language syntax for Tasking compiler.
  There is no impact due to order of evaluation associated with the "#" operator
  used inside the inline assembly language construct */
#define IMASKLDMST(address,val,offset,bits) \
 __asm("imask e2,%0,%1,#" #bits " \n ldmst [%2]0,e2" \
        : : "d" (val), "d" (offset), "a" (address) : "e2")

#endif
#endif

#ifdef _GNU_C_TRICORE_
#if (_GNU_C_TRICORE_ == 1U)
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define IMASKLDMST(address,val,offset,bits) \
                        __imaskldmst(address, val, offset, bits)

/*! \brief Atomic load-modify-store. */

#define __imaskldmst(address, value, bitoffset, bits) \
  {long long tmp;\
  __asm__("imask %A0,%1,%2,%3"\
          :"=d"((long long)tmp)\
          :"d"(value),"d"(bitoffset),"i"(bits): "memory");\
  __asm__("ldmst [%0]0,%A1"::"a"(address),"d"(tmp): "memory");}

#endif
#endif

#ifdef _GHS_C_TRICORE_
#if (_GHS_C_TRICORE_ == 1U)

/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define IMASKLDMST(address,val,offset,bits) \
        __imaskldmst((int *)address, (int) val, (int)offset, (int)bits)

#endif
#endif

#ifdef _DIABDATA_C_TRICORE_
#if (_DIABDATA_C_TRICORE_ == 1U)
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define  IMASKLDMST(address,val,offset,bits) \
{unsigned long long tmp;\
  tmp = _imaskew( val, offset, bits);\
  _ldmst((void *)address, 0,tmp);\
}

#endif /* #ifdef _DIABDATA_C_TRICORE_  */
#endif

/*
Example:
A variable TESTVAR should be set to value 10 from  bit number 3 to 6.
Case 1:

  uint32 TESTVAR;  assume the variable is located at 0xd0001000
  IMASKLDMST(&TESTVAR,10,3,4);

  This will produce assembly instructions like
    imask e0,#10,#3,#4
  ldmst TESTVAR,e0

Case 2:

  Now if the variable is placed at outside 16K boundary
  uint32 TESTVAR __at(0xd0004000);

  Using IMASKLDMST will result in compile time error.
  So the user should use EXT_IMASKLDMST. The resulting
  assembly will be

  mov16 d15,#10
  movh.a  a15,#@his(TESTVAR)
  mov16 d0,#3
  lea a15,[a15]@los(TESTVAR)
  imask e2,d15,d0,#4
  ldmst [a15]0,e2

*/


/*******************************************************************************
** Macro Syntax : EXTRACT(value,pos,width)                                    **
**                                                                            **
** Parameters (in) :                                                          **
**                    Value  : Value to be extracted                          **
**                    pos : Bit Offset from LSB                               **
**                    Width   : No of Bits to be read                         **
** Parameters (out):  None                                                    **
** return value    : integer (extracted value)                                **
** Description    : EXTRACT is used to read value from a required position    **
**                  for the desired number of bits.                           **
**                  Reads the values in a single instruction when compared    **
**                  mask and loading the same                                 **
*******************************************************************************/
#ifdef _TASKING_C_TRICORE_
#if (_TASKING_C_TRICORE_ == 1U)
/* [cover parentID={4B3B7E56-9E6E-4a79-B856-C93255C53C05}][/cover] */
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define EXTRACT(value,pos,width)            (__extru((sint32)(value), \
                                                    (sint32)(pos), \
                                                    (sint32)(width)))

#endif
#endif

#ifdef _GNU_C_TRICORE_
#if (_GNU_C_TRICORE_ == 1U)
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define EXTRACT(value,pos,width)            (_extru((unsigned)(value), \
                                                    (unsigned)(pos), \
                                                    (unsigned)(width)))

/* Same as __extr() but return bit-field as unsigned integer */
static INLINE unsigned _extru(unsigned a, unsigned p, unsigned w) {
  unsigned res;
  __asm__ volatile ("mov %%d14,%2  \n\
                     mov %%d15,%3  \n\
                     extr.u %0,%1,%%e14"
                    : "=d" (res) : "d" (a), "d" (p), "d" (w):"d14","d15");
  return res;
}

#endif
#endif

#ifdef _GHS_C_TRICORE_
#if (_GHS_C_TRICORE_ == 1U)
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define EXTRACT(value,pos,width)           (_extru((unsigned)(value), \
                                                    (unsigned)(pos), \
                                                 (unsigned)(width)))

/* Same as __extr() but return bit-field as unsigned integer */
static INLINE unsigned _extru(unsigned a, unsigned p, unsigned w) {
unsigned res;
__asm volatile ("mov %%d14,%2  \n\
mov %%d15,%3  \n\
extr.u %0,%1,%%e14"
: "=d" (res) : "d" (a), "d" (p), "d" (w):"d14","d15");
return res;
}

#endif
#endif

#ifdef _DIABDATA_C_TRICORE_
#if (_DIABDATA_C_TRICORE_ == 1U)
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define EXTRACT(value,pos,width)            (_extru((unsigned)(value), \
                                                    (unsigned)(pos), \
                                                    (unsigned)(width)))


#endif /* #ifdef _DIABDATA_C_TRICORE_  */
#endif

/*******************************************************************************
** Macro Syntax : Mcal_CountLeadingZeros(Variable)                            **
**                                                                            **
** Parameters (in) :  Variable: variable whose leading zero needs to          **
**                              counted.                                      **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Description     : Macro to Count Leading Zeros in a  variable. The tasking **
**                   intrinsic __clz is used for this purpose.                **
**                                                                            **
*******************************************************************************/
#ifdef _TASKING_C_TRICORE_
#if (_TASKING_C_TRICORE_ == 1U)
/* [cover parentID={4F68E6B7-D267-42de-B363-1C0B7C4B3CD6}][/cover] */
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define Mcal_CountLeadingZeros(Variable) ( __clz((sint32)(Variable)))
#endif
#endif

#ifdef _GNU_C_TRICORE_
#if (_GNU_C_TRICORE_ == 1U)
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define Mcal_CountLeadingZeros(Variable) ( __CLZ((sint32)(Variable)))
#endif
#endif

#ifdef _DIABDATA_C_TRICORE_
#if (_DIABDATA_C_TRICORE_ == 1U)
/* int data type has to be replaced by proper abstraction*/
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define Mcal_CountLeadingZeros(Variable) ( _clz((int)(Variable)))
#endif /* #ifdef _DIABDATA_C_TRICORE_*/
#endif

#ifdef _GHS_C_TRICORE_
#if (_GHS_C_TRICORE_ == 1U)
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define Mcal_CountLeadingZeros(Variable) ( __CLZ32((uint32) (Variable)))
#endif /* #ifdef _GHS_C_TRICORE_ */
#endif

/*******************************************************************************
** Macro Syntax : cmpswap_w(unsigned_int volatile *address,                   **
**                                unsigned_int value, unsigned_int condition) **
**                                                                            **
** Parameters (in) : address : ResourceStatusPtr address                      **
**                   value: This variable is updated with status of           **
**                           ResourceStatusPtr                                **
** Parameters (out):  None                                                    **
**                                                                            **
** Description     : This function is a implementation of a binary semaphore  **
**                   using compare and swap instruction                       **
*******************************************************************************/
#ifdef _GNU_C_TRICORE_
#if (_GNU_C_TRICORE_ == 1U)
static INLINE unsigned_int cmpswap_w (unsigned_int volatile *address,
           unsigned_int value, unsigned_int condition)
{
  __extension__ unsigned long long reg64
    = value | (unsigned long long) condition << 32;

  __asm__ __volatile__ ("cmpswap.w [%[addr]]0, %A[reg]"
                        : [reg] "+d" (reg64)
                        : [addr] "a" (address)
                        : "memory");
    return reg64;
}

#endif
#endif
/*******************************************************************************
** Macro Syntax : Mcal_CmpAndSwap(ResourceStatusPtr,Value,Compare)            **
**                                                                            **
** Parameters (in) : Value: This variable is updated with status of           **
**                           ResourceStatusPtr                                **
**                   ResourceStatusPtr: This variable is set                  **
**                   Compare: Value with which ResourceStatusPtr value        **
**                      is compared.                                          **
** Parameters (out):  None                                                    **
**                                                                            **
** Description     : This function is a implementation of a binary semaphore  **
**                   using compare and swap instruction                       **
*******************************************************************************/
#ifdef _TASKING_C_TRICORE_
#if (_TASKING_C_TRICORE_ == 1U)
/* [cover parentID={235C2855-4A3E-459a-AE51-E1333A3DA5BB}][/cover] */
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define  Mcal_CmpAndSwap(ResourceStatusPtr,Value,Compare) \
     __cmpswapw(((unsigned_int*)(void*)(ResourceStatusPtr)), \
     ((unsigned_int)(Value)), ((unsigned_int)(Compare)) )

#endif
#endif

#ifdef _GNU_C_TRICORE_
#if (_GNU_C_TRICORE_ == 1U)
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define  Mcal_CmpAndSwap(ResourceStatusPtr,Value,Compare)  \
        cmpswap_w(((unsigned_int*)(void*)ResourceStatusPtr), \
        ((unsigned_int)Value), ((unsigned_int)Compare) )

#endif
#endif

#ifdef _GHS_C_TRICORE_
#if (_GHS_C_TRICORE_ == 1U)
/* int data type has to be replaced by proper abstraction*/
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define  Mcal_CmpAndSwap(ResourceStatusPtr,Value,Compare) \
     __cmpswapw(((int *)(void *)(ResourceStatusPtr)), \
     ((int)(Value)), ((int)(Compare)) )

#endif
#endif

#ifdef _DIABDATA_C_TRICORE_
#if (_DIABDATA_C_TRICORE_ == 1U)
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
asm volatile unsigned_int inline Mcal_CmpAndSwap(
   volatile unsigned long *ResourceStatusPtr, unsigned long RetVal,\
                                                         unsigned long CmpVal)
{
%reg RetVal,ResourceStatusPtr,CmpVal;
!"%d2","%d3"
  mov %d2,RetVal
  mov %d3,CmpVal
  cmpswap.w [ResourceStatusPtr]0,%e2
  mov RetVal,%d2
}

/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
/* function to calcute the crc values based on passed parameters  */
asm volatile unsigned inline __crc32bw( unsigned  b, unsigned  a)
{
%reg b,a;
!"%d2","%d3"
  mov %d2,b
  mov %d3,a
  crc32b.w %d2,%d2,%d3
}

/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
/* function to calcute the crc values based on passed parameters  */
asm volatile unsigned inline __crc32b( unsigned  b, unsigned  a)
{
%reg b,a;
!"%d2","%d3"
  mov %d2,b
  mov %d3,a
  crc32.B %d2,%d2,%d3
}

/*
 * d : parameters of crc algorithm
 *
 * Bit31    15      12         10       9        8                2         Bit0
 *  ---------------------------------------------------------------------------
 * |        |        |         |        |        |                |    input   |
 * | poly-  | CRC    |    0    | inver  | bit    |        0       |    data    |
 * | nomial | width  |         | sion   | order  |                |    width   |
 * |        | (1-16) |         |        |        |                |    (1-8)   |
 *  ---------------------------------------------------------------------------
 * b : initial seed value or CRC of previous sequence of data
 * a : input data
 */
asm volatile unsigned inline __crcn(unsigned  d, unsigned b, unsigned  a)
{
%reg d,b,a;
!"%d3","%d2","%d4"
  mov %d2,b
  mov %d3,d
  mov %d4,a
  crcn %d2,%d2,%d3,%d4
}
#endif /* #ifdef _DIABDATA_C_TRICORE_ */
#endif

/*******************************************************************************
** Macro Syntax : swapmskw(unsigned_int *address,                             **
**                                unsigned_int value                          **
**                                ,unsigned_int mask)                         **
**                                                                            **
** Parameters (in) : address : ResourceStatusPtr address                      **
**                   value: This variable is updated with status of           **
**                           ResourceStatusPtr                                **
**                   Mask - Value to indicate which register bits need        **
**                          to be updated.                                    **
** Parameters (out):  None                                                    **
**                                                                            **
** Description     : This function is a implementation of a binary semaphore  **
**                   using swap instruction                                   **
*******************************************************************************/
#ifdef _GNU_C_TRICORE_
#if (_GNU_C_TRICORE_ == 1U)
static INLINE unsigned_int swapmskw (unsigned_int  *address,
                                           unsigned_int value,unsigned_int mask)
{
  __extension__ unsigned long long reg64
    = value | (unsigned long long) mask << 32;

    __asm__ __volatile__( "swapmsk.w [%[addr]] 0,%A[reg]"
        : [reg]"+d" (reg64)
        : [addr]"a" (address)
        : "memory");
     return ((unsigned_int)reg64 & mask);
}

#endif
#endif

/*******************************************************************************
** Macro Syntax : Mcal_Swap(ResourceStatusPtr,Value,Mask)                     **
**                                                                            **
** Parameters (in) : Value: This variable is updated with status of           **
**                           ResourceStatusPtr                                **
**                   ResourceStatusPtr: This variable is set                  **
**                   Mask - Value to indicate which register bits need        **
**                          to be updated.                                    **
** Parameters (out):  None                                                    **
**                                                                            **
** Description     : This function is a implementation of a binary semaphore  **
**                   using swap instruction                                   **
*******************************************************************************/
#ifdef _TASKING_C_TRICORE_
#if (_TASKING_C_TRICORE_ == 1U)
/* [cover parentID={70E53449-BE73-4f4f-86F1-6253623649EE}][/cover] */
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define  Mcal_Swap(ResourceStatusPtr,Value,Mask) \
    __swapmskw(((unsigned_int*)(ResourceStatusPtr)),((unsigned_int)Value),\
             ((unsigned_int)Mask));
#endif
#endif

#ifdef _GNU_C_TRICORE_
#if (_GNU_C_TRICORE_ == 1U)
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define  Mcal_Swap(ResourceStatusPtr,Value,Mask) \
    swapmskw (((unsigned_int*)ResourceStatusPtr),((unsigned_int)Value),\
             ((unsigned_int)Mask));
#endif
#endif

#ifdef _GHS_C_TRICORE_
#if (_GHS_C_TRICORE_ == 1U)
/* int data type has to be replaced by proper abstraction*/
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define  Mcal_Swap(ResourceStatusPtr,Value,Mask) \
    __swapmskw (((int*)ResourceStatusPtr),((int)Value),\
             ((int)Mask));
#endif
#endif

#ifdef _DIABDATA_C_TRICORE_
#if (_DIABDATA_C_TRICORE_ == 1U)
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function */
#define  Mcal_Swap(ResourceStatusPtr,Value,Mask) \
    swapmskw (((unsigned_int*)ResourceStatusPtr),((unsigned_int)Value),\
             ((unsigned_int)Mask));

asm volatile unsigned_int inline swapmskw(
   unsigned_int *ResourceStatusPtr, unsigned long Value, unsigned long mask)
{
%reg Value,ResourceStatusPtr,mask;
!"%d2","%d3"
  mov %d2,Value
  mov %d3,mask
  swapmsk.w [ResourceStatusPtr]0,%e2
  mov Value,%d2
}
#endif /* _DIABDATA_C_TRICORE_ */
#endif

/*******************************************************************************
** Macro Syntax : POPCNT(Value)                                               **
**                                                                            **
** Parameters (in) : Value: The uint32 value whose number of ones             **
**                          is to be counted.                                 **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** return value    : uint32 - Count of the number of bits set                 **
**                   (Valid range: 0 to 32)                                   **
**                                                                            **
** Description     : POPCNT counts the number of ones in Value parameter and  **
**                   returns the count as the result                          **
**                                                                            **
*******************************************************************************/
#ifdef _TASKING_C_TRICORE_
#if (_TASKING_C_TRICORE_ == 1U)
/* [cover parentID={31327271-31E6-4741-9C3B-5D062691520D}][/cover] */
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define POPCNT(Value)           (__popcntw((unsigned_int)Value))

#endif
#endif

#ifdef _GNU_C_TRICORE_
#if (_GNU_C_TRICORE_ == 1U)
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define POPCNT(Value)           (_popcnt((unsigned_int)(Value)))

/*POPCNT declaration to ensure this function is always inlined */
static INLINE unsigned _popcnt(unsigned Value) __attribute__ ((always_inline));
/*POPCNT counts the number of ones in Value parameter and
returns the count as the result*/
static INLINE unsigned _popcnt(unsigned Value)
{
  unsigned ResultVal;

  __asm__ volatile("popcnt.w %0, %1"
    :"=d"(ResultVal)
    : "d"(Value));

  return ResultVal;

}
#endif /* #if (_GNU_C_TRICORE_ == 1U) */
#endif /* _GNU_C_TRICORE_ */

#ifdef _GHS_C_TRICORE_
#if (_GHS_C_TRICORE_ == 1U)
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define POPCNT(Value)           (_popcnt((unsigned_int)(Value)))

/*POPCNT declaration to ensure this function is always inlined */
static INLINE unsigned _popcnt(unsigned Value) __attribute__ ((always_inline));
/*POPCNT counts the number of ones in Value parameter and
returns the count as the result*/
static INLINE unsigned _popcnt(unsigned Value)
{
  unsigned ResultVal;
  __asm__ volatile ("popcnt.w %0, %1"
    : "=d"(ResultVal)
    : "d"(Value));

  return ResultVal;

}
#endif /* #if (_GHS_C_TRICORE_ == 1U) */
#endif /* _GHS_C_TRICORE_ */

#ifdef _DIABDATA_C_TRICORE_
#if (_DIABDATA_C_TRICORE_ == 1U)
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro used to call the Tricore
intrinsic function*/
#define  POPCNT(Value)          (_popcnt_w((unsigned_int)(Value)))

#endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
#endif /* _DIABDATA_C_TRICORE_ */
#endif /* MCAL_COMPILER_H  */
