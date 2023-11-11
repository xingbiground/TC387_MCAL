/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2019)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : Irq.h                                                      **
**                                                                            **
**  VERSION      : 5.0.0                                                      **
**                                                                            **
**  DATE         : 2019-03-13                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Irq Driver header definition file                          **
**                                                                            **
**  SPECIFICATION(S) : na                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/

#ifndef  IRQ_H
#define  IRQ_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Inclusion of Platform_Types.h and Compiler.h SPI070: */
#include "Std_Types.h"

/* Include Irq Configuration */
#include "Irq_Cfg.h"
#include "Mcal_Compiler.h"


/*******************************************************************************
**                          Published parameters                              **
*******************************************************************************/
/* Irq Vendor ID */
#define IRQ_VENDOR_ID              ((uint16)17)
/* Irq Module ID */
#define IRQ_MODULE_ID              ((uint16)255)
/* Irq Instance ID */
#define IRQ_INSTANCE_ID            ((uint16)0)
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
#define IRQ_DMA_AVAILABLE          (0U)
#define IRQ_DMA_USED_MCALADC       (1U)
#define IRQ_DMA_USED_MCALSPI_TX    (2U)
#define IRQ_DMA_USED_MCALSPI_RX    (3U)
#define IRQ_CLEAR_MASK                0xFFFFFFFFU
#define SRC_STM0SR0_CLRR_CLEARMASK    0x7D3F1CFFU
#define SRC_STM0SR0_CLRR_SETMASK      0x02000000U
#define SRC_STM0SR0_SRE_CLEARMASK     0x7F3F18FFU
#define SRC_STM0SR1_CLRR_CLEARMASK    0x7D3F1CFFU
#define SRC_STM0SR1_CLRR_SETMASK      0x02000000U
#define SRC_STM0SR1_SRE_CLEARMASK     0x7F3F18FFU
#define STM0_CMP_CLEARMASK            0x00000000U



/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro declared to ensure
correct syntax of declaring const pointer to function as required by specific
compiler, No arithmetic operation is done in this macro.*/
#define IRQ_SFR_MODIFY32(reg, clearmask ,setmask) \
  { ((reg)) &= clearmask; ((reg)) = (setmask);}

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro declared to ensure
correct syntax of declaring const pointer to function as required by specific
compiler, No arithmetic operation is done in this macro.*/
#define Irq_InstallInterruptHandler(priority,irq_handler)


#ifndef ISR
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro declared to ensure
correct syntax of declaring const pointer to function as required by specific
compiler, No arithmetic operation is done in this macro.*/
#define ISR(x) void x(void)
#endif


#ifdef _TASKING_C_TRICORE_
#if (_TASKING_C_TRICORE_ == 1U)

#ifndef IFX_INTERRUPT
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro declared to ensure
correct syntax of declaring const pointer to function as required by specific
compiler, No arithmetic operation is done in this macro.*/
#define IFX_INTERRUPT(isr, vectabNum, prio) \
                    void __interrupt(prio) __vector_table(vectabNum) isr(void)
#endif

#endif
#endif /* (_TASKING_C_TRICORE_ == 1U) */

#ifdef _GNU_C_TRICORE_
#if (_GNU_C_TRICORE_ == 1U)
#ifndef IFX_INTERRUPT
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro declared to ensure
correct syntax of declaring const pointer to function as required by specific
compiler, No arithmetic operation is done in this macro.*/
#define IFX_INTERRUPT(isr, vectabNum, prio) \
                                   IFX_INTERRUPT_INTERNAL(isr, vectabNum, prio)
#endif


#ifndef IFX_INTERRUPT_INTERNAL
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro declared to ensure
correct syntax of declaring const pointer to function as required by specific
compiler, No arithmetic operation is done in this macro.*/
#define IFX_INTERRUPT_INTERNAL(isr, vectabNum, prio) \
__asm__ (".ifndef .intr.entry.include                        \n"\
    ".altmacro                                           \n"\
    ".macro .int_entry.2 intEntryLabel, name \
                                # define the section and inttab entry code \n"\
        " .pushsection .\\intEntryLabel,\"ax\",@progbits   \n"\
        " __\\intEntryLabel :                              \n"\
        "   svlcx                                        \n"\
        "   movh.a  %a14, hi:\\name                      \n"\
        "   lea     %a14, [%a14]lo:\\name                \n"\
        "   ji      %a14                                 \n"\
        " .popsection                                      \n"\
    ".endm                                               \n"\
    ".macro .int_entry.1 prio,vectabNum,u,name           \n"\
      ".int_entry.2 intvec_tc\\vectabNum\\u\\prio,(name) \
                                                  # build the unique name \n"\
    ".endm                                               \n"\
        "                                                    \n"\
    ".macro .intr.entry name,vectabNum,prio              \n"\
      ".int_entry.1 %(prio),%(vectabNum),_,name \
                               # evaluate the priority and the cpu number \n"\
    ".endm                                               \n"\
    ".intr.entry.include:                                \n"\
    ".endif                                              \n"\
        ".intr.entry "#isr","#vectabNum","#prio               );\
extern void __attribute__ ((interrupt_handler)) isr(); \
void isr (void)
#endif /* IFX_INTERRUPT */

#endif /* (_GNU_C_TRICORE_ == 1U) */
#endif /* End of #ifdef _GNU_C_TRICORE_ */



#ifdef _DIABDATA_C_TRICORE_

#if (_DIABDATA_C_TRICORE_ == 1U)

#ifndef IFX_INTERRUPT
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro declared to ensure
correct syntax of declaring const pointer to function as required by specific
compiler, No arithmetic operation is done in this macro.*/
#define IFX_INTERRUPT(isr, vectabNum, prio) \
                                  IFX_INTERRUPT_INTERNAL(isr, vectabNum, prio)
#endif

#ifndef IFX_INTERRUPT_INTERNAL
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro declared to ensure
correct syntax of declaring const pointer to function as required by specific
compiler, No arithmetic operation is done in this macro.*/
#define IFX_INTERRUPT_INTERNAL(isr, vectabNum, prio)                \
void __interrupt(prio) __vector_table(vectabNum) isr(void)
#endif /* IFX_INTERRUPT_INTERNAL */
#endif
#endif

#ifdef _GHS_C_TRICORE_
#if (_GHS_C_TRICORE_ == 1U)

#ifndef IFX_INTERRUPT
#define IFX_INTERRUPT(isr, vectabNum, prio) IFX_INTERRUPT_INTERNAL(isr, vectabNum, prio)
#endif

#define IFX_INTERRUPT_INTERNAL(isr, vectabNum, prio) \
__attribute__((section(".intvec_tc"#vectabNum"_"#prio))) void iVecEntry##vectabNum##_##prio(void) \
{ \
  __asm__("movh.a  a14, %hi("#isr") \n" \
      "lea     a14, [a14]%lo("#isr")\n" \
      "ji      a14"); \
} \
__interrupt void isr(void)
#endif /* (_GHS_C_TRICORE_ == 1U) */
#endif /* End of #ifdef _GHS_C_TRICORE_ */
/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/

#define IRQ_START_SEC_CODE_QM_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Irq_MemMap.h"


#if (IRQ_CCU6_EXIST == STD_ON)
/*******************************************************************************
** Syntax :  void IrqCcu6_Init(void)                                          **
**                                                                            **
** Service ID:  none                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  non reentrant                                                 **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : To set the interrupt priority for various                    **
**               service nodes according to priority configurartion.          **
**                                                                            **
*******************************************************************************/
extern void IrqCcu6_Init(void);
#endif/*End of IRQ_CCU6_EXIST*/

#if (IRQ_CAN_EXIST == STD_ON)
/*******************************************************************************
** Syntax :  void IrqCan_Init(void)                                           **
**                                                                            **
** Service ID:  none                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  non reentrant                                                 **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : To set the interrupt priority for various                    **
**               service nodes according to priority configurartion.          **
**                                                                            **
*******************************************************************************/
extern void IrqCan_Init(void);
#endif/*End of IRQ_CAN_EXIST*/

#if (IRQ_GPT12_EXIST == STD_ON)
/*******************************************************************************
** Syntax :  void IrqGpt_Init(void)                                           **
**                                                                            **
** Service ID:  none                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  non reentrant                                                 **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : To set the interrupt priority for various                    **
**               service nodes according to priority configurartion.          **
**                                                                            **
*******************************************************************************/
extern void IrqGpt_Init(void);
#endif/*End of IRQ_CCU6_EXIST*/


#if (IRQ_GTM_EXIST == STD_ON)
/*******************************************************************************
** Syntax :  void IrqGtm_Init(void)                                           **
**                                                                            **
** Service ID:  none                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  non reentrant                                                 **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : To set the interrupt priority for various                    **
**               service nodes according to priority configurartion.          **
**                                                                            **
*******************************************************************************/
extern void IrqGtm_Init(void);
#endif/*End of IRQ_GTM_EXIST*/

#if (IRQ_GPSRGROUP_EXIST == STD_ON)
/*******************************************************************************
** Syntax :  void IrqGpsrGroup_Init(void)                                     **
**                                                                            **
** Service ID:  none                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  non reentrant                                                 **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : To set the interrupt priority for various                    **
**               service nodes according to priority configurartion.          **
**                                                                            **
*******************************************************************************/
extern void IrqGpsrGroup_Init(void);
#endif/*End of IRQ_GPSRGROUP_EXIST*/

#if (IRQ_FLEXRAY_EXIST == STD_ON)
/*******************************************************************************
** Syntax :  void IrqFlexray_Init(void)                                       **
**                                                                            **
** Service ID:  none                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  non reentrant                                                 **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : To set the interrupt priority for ERay                       **
**               service nodes according to priority configurartion.          **
**                                                                            **
*******************************************************************************/
extern void IrqFlexray_Init(void);
#endif/*End of IRQ_FLEXRAY_EXIST*/

#if (IRQ_QSPI_EXIST == STD_ON)
/*******************************************************************************
** Syntax :  void IrqSpi_Init(void)                                           **
**                                                                            **
** Service ID:  none                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  non reentrant                                                 **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : To set the interrupt priority for various                    **
**               service nodes according to priority configurartion.          **
**                                                                            **
*******************************************************************************/
extern void IrqSpi_Init(void);
#endif/*End of IRQ_QSPI_EXIST*/

#if (IRQ_ASCLIN_EXIST == STD_ON)
/*******************************************************************************
** Syntax :  void IrqAsclin_Init(void)                                        **
**                                                                            **
** Service ID:  none                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  non reentrant                                                 **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : To set the interrupt priority for various                    **
**               service nodes according to priority configurartion.          **
**                                                                            **
*******************************************************************************/
extern void IrqAsclin_Init(void);
#endif/*End of IRQ_ASCLIN_EXIST*/

#if (IRQ_ADC_EXIST == STD_ON)
/*******************************************************************************
** Syntax :  void IrqAdc_Init(void)                                           **
**                                                                            **
** Service ID:  none                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  non reentrant                                                 **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : To set the interrupt priority for various                    **
**               service nodes according to priority configurartion.          **
**                                                                            **
*******************************************************************************/
extern void IrqAdc_Init(void);
#endif/*End of IRQ_ADC_EXIST*/

#if (IRQ_GETH_EXIST == STD_ON)
/*******************************************************************************
** Syntax :  void IrqEthernet_Init(void)                                      **
**                                                                            **
** Service ID:  none                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  non reentrant                                                 **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : To set the interrupt priority for Ethernet                   **
**               service nodes according to priority configurartion.          **
**                                                                            **
*******************************************************************************/
extern void IrqEthernet_Init(void);
#endif/*End of IRQ_GETH_EXIST*/

#if (IRQ_DMA_EXIST == STD_ON)
/*******************************************************************************
** Syntax :  void IrqDma_Init(void)                                           **
**                                                                            **
** Service ID:  none                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  non reentrant                                                 **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : To set the interrupt priority for DMA                        **
**               service nodes according to priority configurartion.          **
**                                                                            **
*******************************************************************************/
extern void IrqDma_Init(void);
#endif/*End of IRQ_DMA_EXIST*/

#if (IRQ_SCU_EXIST == STD_ON)
/*******************************************************************************
** Syntax :  void IrqScu_Init(void)                                           **
**                                                                            **
** Service ID:  none                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  non reentrant                                                 **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : To set the interrupt priority for                            **
**               service nodes according to priority configurartion.          **
**                                                                            **
*******************************************************************************/
extern void IrqScu_Init(void);
#endif/*End of IRQ_SCU_EXIST*/

#if (IRQ_DMU_EXIST == STD_ON)
/*******************************************************************************
** Syntax :  void IrqDmu_Init(void)                                           **
**                                                                            **
** Service ID:  none                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  non reentrant                                                 **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : To set the interrupt priority for                            **
**               service nodes according to priority configurartion.          **
**                                                                            **
*******************************************************************************/
extern void IrqDmu_Init(void);
#endif/*End of IRQ_DMU_EXIST*/

#if (IRQ_HSSL_EXIST == STD_ON)
/*******************************************************************************
** Syntax :  void IrqHssl_Init(void)                                          **
**                                                                            **
** Service ID:  none                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  non reentrant                                                 **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : To set the interrupt priority for                            **
**               service nodes according to priority configurartion.          **
**                                                                            **
*******************************************************************************/
extern void IrqHssl_Init(void);
#endif/*End of IRQ_HSSL_EXIST*/

#if (IRQ_SENT_EXIST == STD_ON)
/*******************************************************************************
** Syntax :  void IrqSent_Init(void)                                          **
**                                                                            **
** Service ID:  none                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  non reentrant                                                 **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : To set the interrupt priority for                            **
**               service nodes according to priority configurartion.          **
**                                                                            **
*******************************************************************************/
extern void IrqSent_Init(void);
#endif/*End of IRQ_SENT_EXIST*/

#if (IRQ_DSADC_EXIST == STD_ON)
/*******************************************************************************
** Syntax :  void IrqDsadc_Init(void)                                         **
**                                                                            **
** Service ID:  none                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  non reentrant                                                 **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : To set the interrupt priority for                            **
**               service nodes according to priority configurartion.          **
**                                                                            **
*******************************************************************************/
extern void IrqDsadc_Init(void);
#endif/*End of IRQ_DSADC_EXIST*/


/*******************************************************************************
** Syntax :  void Irq_ClearAllInterruptFlags(void)                            **
**                                                                            **
** Service ID:  none                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  non reentrant                                                 **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : To clear all SRR and corresponding SRE bits.This ensures     **
** Standby mode can be entered if no pending interrupts are available.        **
**                                                                            **
*******************************************************************************/
extern void Irq_ClearAllInterruptFlags(void);

#if (IRQ_STM_EXIST == STD_ON)
/*******************************************************************************
** Syntax :  void IrqStm_Init(void)                                           **
**                                                                            **
** Service ID:  none                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  non reentrant                                                 **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : To set the interrupt priority for STM                        **
**               service nodes according to priority configurartion.          **
**                                                                            **
*******************************************************************************/
extern void IrqStm_Init(void);
#endif/*End of IRQ_STM_EXIST*/


#if (IRQ_I2C_EXIST == STD_ON)
/*******************************************************************************
** Syntax :  void IrqI2c_Init(void)                                           **
**                                                                            **
** Service ID:  none                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  non reentrant                                                 **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : To set the interrupt priority for I2C                        **
**               service nodes according to priority configurartion.          **
**                                                                            **
*******************************************************************************/
extern void IrqI2c_Init(void);
#endif/*End of IRQ_I2C_EXIST*/

#define IRQ_STOP_SEC_CODE_QM_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Irq_MemMap.h"


/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/

#endif /* IRQ_H */
