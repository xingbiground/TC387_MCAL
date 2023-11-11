/**
 * \file Ifx_Ssw_CompilersTasking.h
 * \brief Startup Software for Tasking compiler options
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
#ifndef IFX_SSW_COMPILERSTASKING_H_
#define IFX_SSW_COMPILERSTASKING_H_

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

/*Linker definitions which are specific to Tasking */
/* IFX_CFG_USE_COMPILER_DEFAULT_LINKER shall be defined in Ifx_Cfg.h
 * to use the default compiler linker varaibles and startup */
#ifndef IFX_CFG_USE_COMPILER_DEFAULT_LINKER

/*Start: Common definitions ********************************************** */
#define IFX_SSW_COMMON_LINKER_SYMBOLS()                                     \
    __asm("\t .extern _SMALL_DATA_, _LITERAL_DATA_, _A8_DATA_, _A9_DATA_"); \
    extern unsigned int __START0[];     /**< Pointer to the startup code */ \
    extern unsigned int __START1[];     /**< Pointer to the startup code */ \
    extern unsigned int __START2[];     /**< Pointer to the startup code */ \
    extern unsigned int __START3[];     /**< Pointer to the startup code */ \
    extern unsigned int __START4[];     /**< Pointer to the startup code */ \
    extern unsigned int __START5[];     /**< Pointer to the startup code */

/*End: Common definitions ************************************************ */

/*Start: Core 0 definitions ********************************************** */

/*C extern defintions */
#define IFX_SSW_CORE_LINKER_SYMBOLS(cpu)                                                                             \
    __asm("\t .extern __USTACK"#cpu);         /**< user stack end is required as asm to be used with setreg macro */ \
    extern unsigned int __ISTACK##cpu[];      /**< interrupt stack end */                                            \
    extern unsigned int __INTTAB_CPU##cpu[];  /**< interrupt vector table */                                         \
    extern unsigned int __TRAPTAB_CPU##cpu[]; /**< trap vector table */                                              \
    extern unsigned int __CSA##cpu[];         /**< context save area begin */                                        \
    extern unsigned int __CSA##cpu##_END[];   /**< context save area end   */

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

#define __SDATA1(cpu)      _SMALL_DATA_
#define __SDATA2(cpu)      _LITERAL_DATA_
#define __SDATA3(cpu)      _A8_DATA_
#define __SDATA4(cpu)      _A9_DATA_

#endif /*IFX_CFG_USE_COMPILER_DEFAULT_LINKER*/

#ifdef __cplusplus
#define IFX_SSW_INLINE   static inline
#else
#define IFX_SSW_INLINE   inline
#endif

#define IFX_SSW_NULL_PTR ((void *)0x0U)

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


#define Ifx_Ssw_CLZ(a)                     __clz(a)

#define Ifx_Ssw___setAddressReg(aReg, val) \
    {__asm(" movh.a\t "#aReg ",#@his("#val ")\n lea\t "#aReg ",["#aReg "]@los("#val ")"); }

#define Ifx_Ssw_setAddressReg(regNum, val) Ifx_Ssw___setAddressReg(regNum, val)

IFX_SSW_INLINE void Ifx_Ssw_moveToDataParam0(unsigned int var)
{
    __asm("mov d2, %0" ::"d" (var));
}


IFX_SSW_INLINE unsigned int Ifx_Ssw_getDataParam0(void)
{
    unsigned int var;
    __asm(" mov\t %0, d2" : "=d" (var));
    return var;
}


IFX_SSW_INLINE void Ifx_Ssw_jumpToFunction(void *fun)
{
    __asm("ji %0" ::"a" (fun));
}


IFX_SSW_INLINE void Ifx_Ssw_jumpToFunctionWithLink(void *fun)
{
    __asm("jli %0" ::"a" (fun));
}


IFX_SSW_INLINE void Ifx_Ssw_jumpBackToLink(void)
{
    __asm("ji a11");
}


IFX_SSW_INLINE void Ifx_Ssw_C_InitInline(void)
{
    extern void _c_init(void);
    _c_init();                  /* initialize data */
}


#endif /* IFX_SSW_COMPILERSTASKING_H_ */
