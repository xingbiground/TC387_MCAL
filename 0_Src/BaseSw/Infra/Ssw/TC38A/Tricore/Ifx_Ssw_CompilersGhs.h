/**
 * \file Ifx_Ssw_CompilersGhs.h
 * \brief Startup Software for GHS compiler options
 *
 * \version iLLD_1_0_1_11_0
 * \copyright Copyright (c) 2018 Infineon Technologies AG. All rights reserved.
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 */

#ifndef IFX_SSW_COMPILERSGHS_H_
#define IFX_SSW_COMPILERSGHS_H_

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "intrinsics.h"

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/
void __dsync(void);
void __isync(void);

/*Linker definitions which are specific to Gnuc */
/* IFX_CFG_USE_COMPILER_DEFAULT_LINKER shall be defined in Ifx_Cfg.h
 * to use the default compiler linker varaibles and startup */
#ifndef IFX_CFG_USE_COMPILER_DEFAULT_LINKER

/*Start: Common definitions ********************************************** */
#define IFX_SSW_COMMON_LINKER_SYMBOLS()                                                   \
    __asm__("\t .extern _SMALL_DATA_, _LITERAL_DATA_, _SMALL_DATA_A8_, _SMALL_DATA_A9_"); \
    extern unsigned int __START0[];                   /**< Pointer to the startup code */ \
    extern unsigned int __START1[];                   /**< Pointer to the startup code */ \
    extern unsigned int __START2[];                   /**< Pointer to the startup code */ \
    extern unsigned int __START3[];                   /**< Pointer to the startup code */ \
    extern unsigned int __START4[];                   /**< Pointer to the startup code */ \
    extern unsigned int __START5[]                   /**< Pointer to the startup code */

/*End: Common definitions ************************************************ */

/*Start: Core 0 definitions ********************************************** */

/*C extern defintions */
#define IFX_SSW_CORE_LINKER_SYMBOLS(cpu)                                        \
    extern unsigned int __USTACK##cpu[];      /**< user stack end */            \
    extern unsigned int __ISTACK##cpu[];      /**< interrupt stack end */       \
    extern unsigned int __INTTAB_CPU##cpu[];  /**< Interrupt vector table */    \
    extern unsigned int __TRAPTAB_CPU##cpu[]; /**< trap table */                \
    extern unsigned int __CSA##cpu[];         /**< context save area 1 begin */ \
    extern unsigned int __CSA##cpu##_END[]    /**< context save area 1 begin */

#define __USTACK(cpu)      __USTACK##cpu
#define __ISTACK(cpu)      __ISTACK##cpu
#define __INTTAB_CPU(cpu)  __INTTAB_CPU##cpu
#define __TRAPTAB_CPU(cpu) __TRAPTAB_CPU##cpu
#define __CSA(cpu)         __CSA##cpu
#define __CSA_END(cpu)     __CSA##cpu##_END
#define __START(cpu)       __START##cpu

/*Wrapper macros for the tool specific definitions */
#if defined(IFX_USE_SW_MANAGED_INT)
#define __INTTAB(cpu)      ((unsigned int)__INTTAB_CPU##cpu | (unsigned int)0x1FE0)
#else
#define __INTTAB(cpu)      __INTTAB_CPU##cpu
#endif /*defined(IFX_USE_SW_MANAGED_INT) */

#define __TRAPTAB(cpu)     __TRAPTAB_CPU##cpu

#define __SDATA1(cpu)      __A0_MEM
#define __SDATA2(cpu)      __A1_MEM
#define __SDATA3(cpu)      __A8_MEM
#define __SDATA4(cpu)      __A9_MEM

#endif /*#ifndef IFX_CFG_USE_COMPILER_DEFAULT_LINKER*/

#define IFX_SSW_INLINE   static inline __attribute__ ((always_inline))

#define IFX_SSW_NULL_PTR ((void *)0x0U)

/******************************************************************************/
/*--------------------------------   Typedefs  -------------------------------*/
/******************************************************************************/
typedef volatile union
{
    unsigned int       *ucPtr;
    unsigned int       *usPtr;
    unsigned int       *uiPtr;
    unsigned long long *ullPtr;
} Ifx_Ssw_CTablePtr;

/******************************************************************************/
/*----------------------------   GNU Intrinsics  -----------------------------*/
/******************************************************************************/

#define Ifx_Ssw_MTCR(reg, val) __mtcr(reg, val);

#define Ifx_Ssw_MFCR(reg)      __mfcr(reg);

IFX_SSW_INLINE void Ifx_Ssw_NOP(void)
{
    __nop();
}


IFX_SSW_INLINE void Ifx_Ssw_DSYNC(void)
{
    __dsync();
}


IFX_SSW_INLINE void Ifx_Ssw_ISYNC(void)
{
    __isync();
}


IFX_SSW_INLINE unsigned int Ifx_Ssw_MINU(unsigned int a, unsigned int b)
{
    return __minu(a, b);
}


#define Ifx_Ssw_CLZ(a)                     __CLZ32(a)

#define Ifx_Ssw___setAddressReg(aReg, val) \
    {__asm__ volatile ("movh.a\t "#aReg ", %hi("#val ")\n\tlea\t "#aReg ",["#aReg "]%lo("#val ")"); }

#define Ifx_Ssw_setAddressReg(regNum, val) Ifx_Ssw___setAddressReg(regNum, val)

IFX_SSW_INLINE void Ifx_Ssw_moveToDataParam0(unsigned int var)
{
    __asm__ volatile ("mov\t d2, %0" ::"d" (var));
}


IFX_SSW_INLINE unsigned int Ifx_Ssw_getDataParam0(void)
{
    unsigned int var;
    __asm__ volatile (" mov\t %0, d2" : "=d" (var));
    return var;
}


IFX_SSW_INLINE void Ifx_Ssw_jumpToFunction(void (*fun)(void))
{
    __asm__ volatile ("ji %0" ::"a" (fun));
}


IFX_SSW_INLINE void Ifx_Ssw_jumpToFunctionWithLink(void *fun)
{
    __asm__ volatile ("jli %0" ::"a" (fun));
}


IFX_SSW_INLINE void Ifx_Ssw_jumpBackToLink(void)
{
    __asm__ volatile ("ji a11");
}


typedef int          ptrdiff_t;
typedef unsigned int syze_t;
typedef signed int   signed_size_t;
#define size_t syze_t

extern void *memcpy(void *s1, const void *s2, syze_t n);
extern void *memset(void *s, int c, syze_t n);

/* rodata is absolute */
typedef const char rodata_ptr[];
#define PICBASE     0
#define PIDBASE     0
#define PIRBASE     0

#define CONST_FUNCP *const

IFX_SSW_INLINE void Ifx_Ssw_C_InitInline(void)
{
    /*----------------------------------------------------------------------*/
    /*									*/
    /*	Clear BSS							*/
    /*									*/
    /*----------------------------------------------------------------------*/
    {
#pragma ghs rodata
        extern rodata_ptr __ghsbinfo_clear;
#pragma ghs rodata
        extern rodata_ptr __ghseinfo_clear;
#pragma ghs rodata
        extern rodata_ptr __ghsbinfo_aclear;

        void            **b = (void **)((char *)__ghsbinfo_clear);
        void            **e = (void **)((char *)__ghseinfo_clear);
        void            **a = __ghsbinfo_aclear != 0 ?
                              ((void **)((char *)__ghsbinfo_aclear)) : e;

        /* Warning:  This code assumes
         * __ghsbinfo_clear <= __ghsbinfo_aclear <= __ghseinfo_clear
         * Which is currently enforced with elxr
         * OR
         * __ghsbinfo_aclear == 0 (i.e.: undefined)
         */

        int OFFSET = PIDBASE;

        while (b != e)
        {
            void     *t;        /* target pointer	*/
            ptrdiff_t v;        /* value to set		*/
            size_t    n;        /* set n bytes		*/

            while (b != a)
            {
                t = OFFSET + (char *)(*b++);
                v = *((ptrdiff_t *)b); b++;
                n = *((size_t *)b); b++;
                (void)memset(t, v, n);
            }

            OFFSET = 0;
            a      = e;
        }
    }

    /*----------------------------------------------------------------------*/
    /*									*/
    /*	Copy from ROM to RAM						*/
    /*									*/
    /*----------------------------------------------------------------------*/

    {
#pragma ghs rodata
        extern rodata_ptr __ghsbinfo_copy;
#pragma ghs rodata
        extern rodata_ptr __ghsbinfo_tcopy;
#pragma ghs rodata
        extern rodata_ptr __ghseinfo_copy;

        void            **b = (void **)((char *)__ghsbinfo_copy);
        void            **m = (void **)((char *)__ghsbinfo_tcopy);
        void            **e = (void **)((char *)__ghseinfo_copy);

        while (b != e)
        {
            void  *t;               /* target pointer	*/
            void  *s;               /* source pointer	*/
            size_t n;               /* copy n bytes		*/
            t = ((b < m) ? PIDBASE : PICBASE) + (char *)(*b); b++;
            s = PIRBASE + (char *)(*b++);
            n = *((size_t *)b); b++;
                   (void)memcpy(t, s, n);
        }
    }
}


#endif /* IFX_SSW_COMPILERSGHS_H_ */
