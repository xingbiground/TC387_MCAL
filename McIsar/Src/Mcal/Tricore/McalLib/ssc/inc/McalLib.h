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
** Traceability  : [cover parentID={FDA5B617-9482-449f-974E-909AC6993C94}]    **
**                                                                            **
**  FILENAME     : McalLib.h                                                  **
**                                                                            **
**  VERSION      : 17.0.0                                                     **
**                                                                            **
**  DATE         : 2021-02-22                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : MCAL Library header definition file                        **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef MCAL_LIB_H
#define MCAL_LIB_H
/* [cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}][/cover] */
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* [cover parentID={AE7302B7-A9ED-4ec6-B0D1-8F777770FBE2}][/cover] */
#include "McalLib_Cfg.h"
#include "Mcal_Compiler.h"
#include "Mcal_Version.h"

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/* [cover parentID={00FB21E9-30EC-4147-BE1F-1D0EA2FBBD1C}][/cover] */
#define MCALLIB_VENDOR_ID                          ((uint16)0x11U) /* 17U */
#define MCALLIB_MODULE_ID                          ((uint16)0xFFU) /* 255U */
/* MCALLIB MODULE INSTANCE ID */
#define MCALLIB_INSTANCE_ID                        ((uint8)0x0U)
/* Service is called with NULL_PTR */
#define MCALLIB_E_PARAM_POINTER                    ((uint8)0xC9U)
#define MCALLIB_E_TIMEOUT_FAILED                   ((uint8)0xCCU)
#define MCALLIB_E_CLKDISABLE                       ((uint8)0xD0U)
/* Service ID for Mcal_GetVersionInfo */
#define MCALLIB_SID_GETVERSIONINFO                 ((uint8)0x79U)
#define MCALLIB_SID_GETSPINLOCK                    ((uint8)0x8DU)
#define MCALLIB_SID_RELSPINLOCK                    ((uint8)0x8EU)
#define MCALLIB_SID_CPUENDINIT                     ((uint8)0x7EU)
#define MCALLIB_SID_SAFETYENDINIT                  ((uint8)0x7FU)
#define MCALLIB_SID_SETSAFETYENDINIT               ((uint8)0x80U)
#define MCALLIB_SID_SAFETYENDINIT_16               ((uint8)0x81U)
#define MCALLIB_SID_SAFETYENDINITMASK              ((uint8)0x8FU)
#define MCALLIB_SID_PERIPHERALENDINIT              ((uint8)0x7AU)
#define MCALLIB_SID_SETPERIPHERALENDINIT           ((uint8)0x7CU)
#define MCALLIB_SID_DELAYTICKRESOLUTION            ((uint8)0x86U)
#define MCAL_MAX_CORES                             (0x6U)
#define MCAL_CORE0_MEM_SEGMENT                     (0x7U)
#define MCAL_CORE1_MEM_SEGMENT                     (0x6U)
#define MCAL_CORE2_MEM_SEGMENT                     (0x5U)
#define MCAL_CORE3_MEM_SEGMENT                     (0x4U)
#define MCAL_CORE4_MEM_SEGMENT                     (0x3U)
#define MCAL_CORE5_MEM_SEGMENT                     (0x1U)
#define MCAL_MEM_SEGMENT2_MSB                      (0x2U)

#if(MCAL_NO_OF_CORES == 6U)
#define MCAL_COREID_MAX_VALUE                      (0x6U)
#else
#define MCAL_COREID_MAX_VALUE                      (MCAL_NO_OF_CORES - 1U)
#endif

#define MCAL_DSPR_GLOBAL_MASK                      (0xF0000000U)
#define MCAL_DSPR_GLOBAL_MASK_N                    (~MCAL_DSPR_GLOBAL_MASK)

#define MCAL_PSPR_GLOBAL_MASK                      (0xF0000000U)
#define MCAL_PSPR_GLOBAL_MASK_N                    (~MCAL_PSPR_GLOBAL_MASK)

#define MCAL_PSPR_LOCAL_MASK                      (0xF0100000U)
#define MCAL_PSPR_LOCAL_MASK_N                    (~MCAL_PSPR_LOCAL_MASK)

#define MCAL_LOCAL_DSPR_BASE_ADDR                  (0xD0000000U)
#define MCAL_LOCAL_PSPR_BASE_ADDR                  (0xC0000000U)

#define MCAL_DSPR0_END_ADDR                        (MCAL_DSPR0_GLOBAL_END_ADDR\
                                                    &  MCAL_DSPR_GLOBAL_MASK_N)
#define MCAL_PSPR0_BASE_ADDR                       (MCAL_PSPR0_GLOBAL_BASE_ADDR\
                                                    &  MCAL_PSPR_GLOBAL_MASK_N)
#define MCAL_PSPR0_END_ADDR                        (MCAL_PSPR0_GLOBAL_END_ADDR\
                                                    &  MCAL_PSPR_GLOBAL_MASK_N)
#define MCAL_LOCAL_PSPR0_BASE_ADDR                ((MCAL_PSPR0_GLOBAL_BASE_ADDR\
                           &  MCAL_PSPR_LOCAL_MASK) | MCAL_LOCAL_PSPR_BASE_ADDR)
#define MCAL_LOCAL_PSPR0_END_ADDR                 ((MCAL_PSPR0_GLOBAL_END_ADDR \
                         &  MCAL_PSPR_LOCAL_MASK_N) | MCAL_LOCAL_PSPR_BASE_ADDR)


#if ( MCAL_NO_OF_CORES > 1U )

#define MCAL_DSPR1_END_ADDR                        (MCAL_DSPR1_GLOBAL_END_ADDR \
                                                    &  MCAL_DSPR_GLOBAL_MASK_N)
#define MCAL_PSPR1_BASE_ADDR                       (MCAL_PSPR1_GLOBAL_BASE_ADDR\
                                                     &  MCAL_PSPR_GLOBAL_MASK_N)
#define MCAL_PSPR1_END_ADDR                        (MCAL_PSPR1_GLOBAL_END_ADDR \
                                                     &  MCAL_PSPR_GLOBAL_MASK_N)
#define MCAL_LOCAL_PSPR1_BASE_ADDR                ((MCAL_PSPR1_GLOBAL_BASE_ADDR\
                           &  MCAL_PSPR_LOCAL_MASK) | MCAL_LOCAL_PSPR_BASE_ADDR)
#define MCAL_LOCAL_PSPR1_END_ADDR                ((MCAL_PSPR1_GLOBAL_END_ADDR\
                          & MCAL_PSPR_LOCAL_MASK_N) | MCAL_LOCAL_PSPR_BASE_ADDR)
#endif

#if ( MCAL_NO_OF_CORES > 2U )

#define MCAL_DSPR2_END_ADDR                        (MCAL_DSPR2_GLOBAL_END_ADDR\
                                                    &  MCAL_DSPR_GLOBAL_MASK_N)
#define MCAL_PSPR2_BASE_ADDR                       (MCAL_PSPR2_GLOBAL_BASE_ADDR\
                                                     &  MCAL_PSPR_GLOBAL_MASK_N)
#define MCAL_PSPR2_END_ADDR                        (MCAL_PSPR2_GLOBAL_END_ADDR\
                                                     &  MCAL_PSPR_GLOBAL_MASK_N)
#define MCAL_LOCAL_PSPR2_BASE_ADDR                ((MCAL_PSPR2_GLOBAL_BASE_ADDR\
                           &  MCAL_PSPR_LOCAL_MASK) | MCAL_LOCAL_PSPR_BASE_ADDR)
#define MCAL_LOCAL_PSPR2_END_ADDR                  ((MCAL_PSPR2_GLOBAL_END_ADDR\
                         &  MCAL_PSPR_LOCAL_MASK_N) | MCAL_LOCAL_PSPR_BASE_ADDR)
#endif

#if ( MCAL_NO_OF_CORES > 3U )

#define MCAL_DSPR3_END_ADDR                        (MCAL_DSPR3_GLOBAL_END_ADDR \
                                                     &  MCAL_DSPR_GLOBAL_MASK_N)
#define MCAL_PSPR3_BASE_ADDR                       (MCAL_PSPR3_GLOBAL_BASE_ADDR\
                                                     &  MCAL_PSPR_GLOBAL_MASK_N)
#define MCAL_PSPR3_END_ADDR                        (MCAL_PSPR3_GLOBAL_END_ADDR \
                                                     &  MCAL_PSPR_GLOBAL_MASK_N)
#define MCAL_LOCAL_PSPR3_BASE_ADDR                ((MCAL_PSPR3_GLOBAL_BASE_ADDR\
                           &  MCAL_PSPR_LOCAL_MASK) | MCAL_LOCAL_PSPR_BASE_ADDR)
#define MCAL_LOCAL_PSPR3_END_ADDR                 ((MCAL_PSPR3_GLOBAL_END_ADDR \
                         &  MCAL_PSPR_LOCAL_MASK_N) | MCAL_LOCAL_PSPR_BASE_ADDR)

#endif

#if ( MCAL_NO_OF_CORES > 4U )

#define MCAL_DSPR4_END_ADDR                        (MCAL_DSPR4_GLOBAL_END_ADDR \
                                                    &  MCAL_DSPR_GLOBAL_MASK_N)
#define MCAL_PSPR4_BASE_ADDR                       (MCAL_PSPR4_GLOBAL_BASE_ADDR\
                                                     &  MCAL_PSPR_GLOBAL_MASK_N)
#define MCAL_PSPR4_END_ADDR                        (MCAL_PSPR4_GLOBAL_END_ADDR \
                                                     &  MCAL_PSPR_GLOBAL_MASK_N)
#define MCAL_LOCAL_PSPR4_BASE_ADDR                ((MCAL_PSPR4_GLOBAL_BASE_ADDR\
                           &  MCAL_PSPR_LOCAL_MASK) | MCAL_LOCAL_PSPR_BASE_ADDR)
#define MCAL_LOCAL_PSPR4_END_ADDR                 ((MCAL_PSPR4_GLOBAL_END_ADDR \
                         &  MCAL_PSPR_LOCAL_MASK_N) | MCAL_LOCAL_PSPR_BASE_ADDR)

#endif

#if ( MCAL_NO_OF_CORES > 5U )

#define MCAL_DSPR5_END_ADDR                        (MCAL_DSPR5_GLOBAL_END_ADDR \
                                                     &  MCAL_DSPR_GLOBAL_MASK_N)
#define MCAL_PSPR5_BASE_ADDR                       (MCAL_PSPR5_GLOBAL_BASE_ADDR\
                                                     &  MCAL_PSPR_GLOBAL_MASK_N)
#define MCAL_PSPR5_END_ADDR                        (MCAL_PSPR5_GLOBAL_END_ADDR \
                                                     &  MCAL_PSPR_GLOBAL_MASK_N)
#define MCAL_LOCAL_PSPR5_BASE_ADDR                ((MCAL_PSPR5_GLOBAL_BASE_ADDR\
                           &  MCAL_PSPR_LOCAL_MASK) | MCAL_LOCAL_PSPR_BASE_ADDR)
#define MCAL_LOCAL_PSPR5_END_ADDR                ((MCAL_PSPR5_GLOBAL_END_ADDR &\
                            MCAL_PSPR_LOCAL_MASK_N) | MCAL_LOCAL_PSPR_BASE_ADDR)
#endif

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'UNUSED_PARAMETER' to suppress compiler warnings for unused variables.
 * No side effects foreseen by violating this MISRA rule. */

#define UNUSED_PARAMETER(VariableName)             (void)(VariableName)

/*******************************************************************************
** Traceability     : [cover parentID={F7A28906-68FA-42a9-B64D-D16A1B2DC2A9}] **
**                                                                            **
** Syntax           : Mcal_SetBitAtomic(DataPtr,BitPos,BitLen,Data)           **
**                                                                            **
** Description      : This API like macro receives a pointer to a 32 bit word **
**                    and places Data in specified Bit Positions specified by **
**                    starting bit position BitPos and data length BitLen     **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : NA                                                      **
**                                                                            **
** Reentrancy       : NA                                                      **
**                                                                            **
** Parameters(in)   : BitPos - Starting bit position where Data needs         **
**                             to be placed                                   **
**                    BitLen - The length of the Data, starting the BitPos,   **
**                             which is replaced in *DataPtr                  **
**                    Data   - Value that is to be replaced in *DataPtr       **
**                                                                            **
** Parameters (out) : DataPtr - Address of the register/variable that is to be**
**                              modified                                      **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/

/* MISRA2012_RULE_4_9_JUSTIFICATION: 'Mcal_SetBitAtomic' implemented for atomic
 * bitwise write operation. Since this is compiler dependent, for ease of use,
 * it is implemented as function like macro.
 * No side effects foreseen by violating this MISRA rule. */

#define Mcal_SetBitAtomic(DataPtr,BitPos,BitLen,Data) \
      IMASKLDMST((DataPtr),(Data),(BitPos),(BitLen))

/*******************************************************************************
** Traceability     :  [cover parentID={2A5AA4BA-91C8-4ca4-86E4-D26FA49B51AD}]**
**                                                                            **
** Syntax           : Mcal_GetBitAtomic(DataValue,BitPos,BitLen)              **
**                                                                            **
** Description      : This API like macro receives a 32bit word, extracts data**
**                    starting bit positions BitPos of length BitLen and      **
**                    returns a 32 bit word.                                  **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : NA                                                      **
**                                                                            **
** Reentrancy       : NA                                                      **
**                                                                            **
** Parameters(in)   : BitPos - Starting bit position where Data needs         **
**                             to be placed                                   **
**                    BitLen - The length of the Data, starting the BitPos,   **
**                             which is extracted                             **
**                    DataValue - The variable/register from which data has to**
**                                be extracted                                **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Data that is extracted from DataVaue                    **
**                                                                            **
*******************************************************************************/
/* MISRA2012_RULE_4_9_JUSTIFICATION: 'Mcal_GetBitAtomic' implemented for
 * bitwise read operation. Since this is compiler dependent, for ease of use,
 * it is implemented as function like macro.
 * No side effects foreseen by violating this MISRA rule. */

#define Mcal_GetBitAtomic(DataValue,BitPos,BitLen) \
            (EXTRACT((DataValue),(BitPos),(BitLen)))

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
#define MCALLIB_START_SEC_CODE_ASIL_B_GLOBAL
#include "McalLib_MemMap.h"

/*******************************************************************************
** Traceability     : [cover parentID={8366FBD5-CC94-4b46-84C1-1587582733A4}] **
**           [/cover]                                                         **
** Syntax           : uint32 Mcal_GetCpuWdgPassword (void)                    **
**                                                                            **
** Description      : This interface is used by applications to retrieve the  **
**                    endinit password currently installed in the watchdog of **
**                    the CPU they are currently executing on.                **
**                                                                            **
** Service ID       : 0x01                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Currently installed password                            **
**                                                                            **
*******************************************************************************/
extern uint32 Mcal_GetCpuWdgPassword(void);

/*******************************************************************************
** Traceability     : [cover parentID={C5FA4346-076A-4fce-AC48-91FD7E7C4CBF}] **
**                                                                            **
** Syntax           : uint32 Mcal_SetCpuWdgPassword (const uint32 Password)   **
**                                                                            **
** Description      : This interface is used by applications to install a     **
**                    specified endinit password in the endinit registers of  **
**                    the watchdog of the CPU they are executing on.          **
**                    Previously stored data in the PW bitfield of            **
**                    WDTCPUxCON0 register is returned back to the caller     **
**                                                                            **
** Service ID       : 0x02                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant on same CPU, Reentrant on other CPUs      **
**                                                                            **
** Parameters(in)   : Password - New password to be installed into            **
**                    WDTCPUxCON0 register                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : return the previous installed password                  **
**                                                                            **
*******************************************************************************/
extern uint32 Mcal_SetCpuWdgPassword(const uint32 Password);

/*******************************************************************************
** Traceability     : [cover parentID={1619BFC3-44C7-4fe5-84B7-EA6DC8570B6A}] **
**                                                                            **
** Syntax           : void Mcal_WriteCpuEndInitProtReg                        **
**                   (volatile void* const RegAddress, const uint32 DataValue)**
**                                                                            **
** Description      : This interface is used by applications to resume        **
**                    protection of CPU endinit protected registers of the    **
**                    CPU they are executing on.                              **
**                                                                            **
** Service ID       : 0X03                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : RegAddress - CPU Endinit protected register address     **
**                    DataValue - Value to be written to the register located **
**                    at RegAddress.                                          **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Mcal_WriteCpuEndInitProtReg
(volatile void* const RegAddress, const uint32 DataValue);

/*******************************************************************************
** Traceability     : [cover parentID={5BE87D93-DC0C-4989-A16E-CE49AEE7BF0D}] **
**                                                                            **
** Syntax           : uint32 Mcal_GetSafetyEndInitPassword (void)             **
**                                                                            **
** Description      : This interface is used by applications to retrieve the  **
**                    Safety endinit password currently installed in the      **
**                    Global ENDINIT control register (SEICON0 register).     **
**                    The password corresponds to EPW bitfield in register    **
**                    SEICON0.                                                **
**                                                                            **
** Service ID       : 0x04                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Currently installed password                            **
**                                                                            **
*******************************************************************************/
extern uint32 Mcal_GetSafetyEndInitPassword(void);

/*******************************************************************************
** Traceability     : [cover parentID={1D74AAF8-8492-4b33-B8D8-B865ECB04396}] **
**                                                                            **
** Syntax           : uint32 Mcal_SetSafetyEndInitPassword                    **
**                                               (const uint32 Password)      **
**                                                                            **
** Description      : This interface is used by applications to install a     **
**                    password for Safety endinit protection. The interface   **
**                    internally prepares the password (shifting, inversion   **
**                    etc.), installs the password and returns the previously **
**                    installed password (from the EPW bitfield).             **
**                                                                            **
** Service ID       : 0x05                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : Password - New password to be installed into            **
**                    SEICON0 register                                        **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Returns the last installed password                     **
**                                                                            **
*******************************************************************************/
extern uint32 Mcal_SetSafetyEndInitPassword(const uint32 Password);

/*******************************************************************************
** Traceability     :[cover parentID={49C5FBA9-0673-47dd-8182-DE8AED479123}]  **
** [/cover]                                                                   **
** Syntax           : void Mcal_WriteSafetyEndInitProtReg                     **
                     (volatile void* const RegAddress, const uint32 DataValue)**
**                                                                            **
** Description      : This API is needed to write required values to safety   **
**                    end-init protected registers by unprotecting to write   **
**                    and protecting back to keep protection intact           **
**                                                                            **
**                                                                            **
** Service ID       : 0x06                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : RegAddress - Safety Endinit protected register address  **
**                    DataValue - Value to be written to the register located **
**                    at RegAddress                                           **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Mcal_WriteSafetyEndInitProtReg
( volatile void* const RegAddress, const uint32 DataValue);


/*******************************************************************************
** Traceability     : [cover parentID={C056F09A-B74A-4ac8-A7E8-9B8D40D8C8E2}] **
** [/cover]                                                                   **
** Syntax           : void Mcal_WriteSafetyEndInitProtRegMask                 **
**                      (volatile void* const RegAddress,                     **
**                      const uint32 DataValue,                               **
**                      uint32 Mask)                                          **
**                                                                            **
** Description      : This API is needed to write required values to safety   **
**                    end-init protected register bits by unprotecting to     **
                      write and protecting back to keep protection intact     **
**                                                                            **
**                                                                            **
**                                                                            **
** Service ID       : 0x16                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : RegAddress - Safety Endinit protected register address  **
**                    DataValue - Value to be written to the register located **
**                    at RegAddress                                           **
**                    Mask - Value to be written to mask the register value   **
**                    need to be changed.                                     **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Mcal_WriteSafetyEndInitProtRegMask
(volatile void* const RegAddress, const uint32 DataValue, uint32 Mask);

/*******************************************************************************
** Traceability     : [cover parentID={E0C11962-A636-4404-B096-E13741CF52ED}] **
** [/cover]                                                                   **
** Syntax           : uint32 Mcal_GetPeripheralEndInitPassword (void)         **
**                                                                            **
** Description      : This interface is used by applications to retrieve the  **
**                    peripheral endinit password currently installed in the  **
**                    Global ENDINIT control register (EICON0 register).      **
**                    The password corresponds to bits 15:2 in register EICON0**
**                                                                            **
** Service ID       : 0x07                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Currently installed password                            **
**                                                                            **
*******************************************************************************/
extern uint32 Mcal_GetPeripheralEndInitPassword(void);

/*******************************************************************************
** Traceability     :[cover parentID={1C3749D6-0FFF-4339-B267-3167F5938B13}]  **
**                                                                            **
** Syntax           : uint32 Mcal_SetPeripheralEndInitPassword                **
**                   (const uint32 Password)                                  **
**                                                                            **
** Description      : This interface is used by applications to install a     **
**                    password for peripheral endinit protection. The         **
**                    interface internally prepares the password (shifting,   **
**                    inversion etc.), installs the password and returns the  **
**                    previously installed password.                          **
**                                                                            **
** Service ID       : 0x08                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : Password - New password to be installed into            **
**                    EICON0 register                                         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Returns the last installed password                     **
**                                                                            **
*******************************************************************************/
extern uint32 Mcal_SetPeripheralEndInitPassword(const uint32 Password);

/*******************************************************************************
** Traceability     : [cover parentID={382E875A-A388-4f3f-842B-BBD7143DEE70}] **
**                                                                            **
** Syntax           : Mcal_WritePeripEndInitProtReg                           **
**                   (volatile void* const RegAddress, const uint32 DataValue)**
**                                                                            **
** Description      :This API is needed to write required values to peripheral**
**                   protected registers by unprotecting to write end-init    **
**                   and protecting back to keep protection intact.           **
**                                                                            **
** Service ID       : 0x09                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : RegAddress - Peripheral Endinit protected register      **
**                    address.                                                **
**                    DataValue - Value to be written to the register         **
**                    located at RegAddress.                                  **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Mcal_WritePeripEndInitProtReg
( volatile void* const RegAddress, const uint32 DataValue);

/*******************************************************************************
** Traceability     : [cover parentID={32C6BD4E-84D4-4d99-9939-40ACDFBADF92}] **
**                                                                            **
** Syntax           : uint32 Mcal_GetCpuPhysicalId(void)                      **
**                                                                            **
** Description      : This interface is used by applications in a multicore   **
**                    environment to determine the CPU they are executing on. **
**                    The API returns the contents of CORE_ID register, for   **
**                    the core on which it is invoked.                        **
**                                                                            **
** Service ID       : 0x0A                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Physical Core ID for the CPU on which this API is called**
**                                                                            **
*******************************************************************************/
extern uint32 Mcal_GetCpuPhysicalId(void);

/*******************************************************************************
** Traceability     : [cover parentID={19A3024B-65AF-4139-95D6-AF25CB4A476E}] **
**                                                                            **
** Syntax           : uint32 Mcal_GetGlobalDsprAddress                        **
**                    (                                                       **
**                     const uint32 CpuId,                                    **
**                     const uint32 LocalDsprAddress                          **
**                    )                                                       **
**                                                                            **
** Description      : This interface is used by applications in a multicore   **
**                    environment to determine the global address of a local  **
**                    DSPR address of a specified CPU. A value 0 is returned  **
**                    in case an invalid input argument is passed             **
**                    (incorrect CpuId, local DSPR address)                   **
**                                                                            **
**                                                                            **
** Service ID       : 0x0C                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : CpuId - Physical Core ID                                **
**                    LocalDsprAddress - Local DSPR address for which global  **
**                    DSPR address is returned                                **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : 0: Invalid input parameter passed                       **
**                    Else, value returned the Global DSPR address            **
**                    If passed parameter is valid global DSPR address        **
**                    corresponding to passed CPU id then return              **
**                    passed address as is.                                   **
*******************************************************************************/
extern uint32 Mcal_GetGlobalDsprAddress
(const uint32 CpuId, const uint32 LocalDsprAddress);

/*******************************************************************************
** Traceability     : [cover parentID={6A4C10C1-2C3C-468f-8F33-C02634550889}] **
**                                                                            **
** Syntax           : uint32 Mcal_GetLocalDsprAddress                         **
**                    (                                                       **
**                     const uint32 GlobalDsprAddress                         **
**                    )                                                       **
**                                                                            **
** Description      : This API is used by applications in a multicore         **
**                    environment to determine the local CPU address of a     **
**                    global DSPR address of the CPU, this interface is       **
**                    invoked on. A value 0 is returned in case an invalid    **
**                    input argument is passed(incorrect global DSPR address) **
**                                                                            **
** Service ID       : 0x0D                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : GlobalDsprAddress - Global DSPR address                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : 0: Invalid input parameter passed                       **
**                    Else, value returned the local DSPR address             **
**                    If passed parameter is valid local DSPR address         **
**                    corresponding to currently executing CPU then routine   **
**                    shall return passed address as is                       **
*******************************************************************************/
extern uint32 Mcal_GetLocalDsprAddress(const uint32 GlobalDsprAddress);

/*******************************************************************************
** Traceability     : [cover parentID={3FCAA99A-4260-4c7e-9224-EAE68F1461C6}] **
**                                                                            **
** Syntax           : uint32 Mcal_GetGlobalPsprAddress                        **
**                    (                                                       **
**                     const uint32 CpuId,                                    **
**                     const uint32 LocalPsprAddress                          **
**                    )                                                       **
**                                                                            **
** Description      : This interface is used by applications in a multicore   **
**                    environment to determine the global address of a local  **
**                    PSPR address of a specified CPU. A value 0 is returned  **
**                    in case an invalid input argument is passed             **
**                    (incorrect CpuId, local PSPR address)                   **
**                                                                            **
** Service ID       : 0x0E                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : CpuId - Physical Core ID                                **
**                    LocalPsprAddress - Local PSPR address for which global  **
**                    PSPR address is returned                                **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : 0: Invalid input parameter passed                       **
**                    Else, value returned the Global PSPR address            **
**                    If passed parameter is valid Global PSPR address        **
**                    corresponding to currently executing CPU then routine   **
**                    shall return passed address as is                       **
*******************************************************************************/
extern uint32 Mcal_GetGlobalPsprAddress
(const uint32 CpuId, const uint32 LocalPsprAddress);

/*******************************************************************************
** Traceability     : [cover parentID={CD35B780-C410-4f80-98F4-722831388424}] **
**                                                                            **
** Syntax           : uint32 Mcal_GetLocalPsprAddress                         **
**                    (                                                       **
**                     const  uint32 GlobalPsprAddress                        **
**                    )                                                       **
**                                                                            **
** Description      : This API is used by applications in a multicore         **
**                    environment to determine the local CPU address of a     **
**                    global PSPR address of the CPU, this interface is       **
**                    invoked on. A value 0 is returned in case an invalid    **
**                    input argument is passed(incorrect global PSPR address) **
**                                                                            **
** Service ID       : 0x0F                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : GlobalPsprAddress - Global PSPR address                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : 0: Invalid input parameter passed                       **
**                    Else, value returned the local PSPR address             **
**                    If passed parameter is valid local PSPR address         **
**                    corresponding to currently executing CPU then routine   **
**                    shall return passed address as is                       **
**                                                                            **
*******************************************************************************/
extern uint32 Mcal_GetLocalPsprAddress(const uint32 GlobalPsprAddress);

/*******************************************************************************
** Traceability     : [cover parentID={106361C3-AE5B-4684-9B55-96C57BF8AC41}] **
**                                                                            **
** Syntax           : uint32 Mcal_DelayTickResolution (void)                  **
**                                                                            **
** Description      : The interface is used by applications to retrieve in    **
**                    nanoseconds the resolution of the delay tick (STM timer)**
**                                                                            **
** Service ID       : 0x11                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Resolution of STM timer delay tick in nanoseconds       **
**                                                                            **
*******************************************************************************/
extern uint32 Mcal_DelayTickResolution(void);

/*******************************************************************************
** Traceability     : [cover parentID={06D30CED-D581-4f9d-88B2-BF39C78EA317}] **
**                                                                            **
** Syntax           : uint32 Mcal_DelayResetTickCalibration(void)             **
**                                                                            **
** Description      : The interface is used by applications to indicate to    **
**                    MCALLib that the clock tree has changed. The expectation**
**                    is that as a result of invocation of this service, any  **
**                    internally cached tick resolution data is discarded.    **
**                    This service is expected to query the clock tree and    **
**                    determine the resolution. The interface returns in      **
**                    nanoseconds the resolution of the delay tick (STM timer)**
**                                                                            **
** Service ID       : 0x10                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Resolution of delay tick in nanoseconds                 **
**                                                                            **
*******************************************************************************/
extern uint32 Mcal_DelayResetTickCalibration(void);

/*******************************************************************************
** Traceability     : [cover parentID={B90FF39B-C537-412f-8234-E9B0307B4D62}] **
** [/cover]                                                                   **
** Syntax           : uint32 Mcal_DelayGetTick (void)                         **
**                                                                            **
** Description      : This interface is used by applications to retrieve the  **
**                    latest tick count of the underlying STM timer. The      **
**                    latest tick count in STM0_TIM0 is returned by this      **
**                    interface. There are two uses of this interface.        **
**                    Applications can retrieve a base tick count, add the    **
**                    desired delay to the base tick count and arrive at a    **
**                    terminal tick count. Applications can also then         **
**                    periodically invoke this interface to determine if the  **
**                    underlying timer has counted up to the terminal tick    **
**                    count.                                                  **
**                                                                            **
** Service ID       : 0x12                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Latest lower 32 bit counter value of STM0 timer         **
**                                                                            **
**                                                                            **
*******************************************************************************/
extern uint32 Mcal_DelayGetTick(void);

/*******************************************************************************
** Traceability     :[cover parentID={1800AF01-292F-4937-B75B-A5A1CD450B30}]  **
**  [/cover]                                                                  **
** Syntax           : uint32 Mcal_GetCpuIndex (uint32 CpuId)                  **
**                                                                            **
** Description      : This interface is used by applications in a multicore   **
**                    environment to determine the CPU they are executing on. **
**                    The API returns the contents of CORE_ID register,       **
**                   variable, structure for the core on which it is invoked. **
**                                                                            **
** Service ID       : 0x0B                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Returns the Core Index corresponding to the input       **
**                    physical Core Id. In case the input Core Id is an       **
**                    invalid value, then the API returns 0xFFFFFFFF          **
**                                                                            **
*******************************************************************************/
extern uint32 Mcal_GetCpuIndex(void);

/*******************************************************************************
** Traceability     : [cover parentID={FDC04393-3918-4d1a-BD98-97EB51ACDAB3}, ** 
**                                    {5ADB9DA9-F509-4203-801F-50BDB32FD518}] **
** [/cover]                                                                   **
** Syntax           : void Mcal_GetSpinlock                                   **
**                  ( volatile uint32 * const LockAddress,\                   **
**                             const uint32 Timeout)                          **
**                                                                            **
** Description     : This API will check if spinlock is available in an non   **
**                   atomic fashion and if spinlock is free then it is        **
**                   acquired in an atomic fashion acquired else it will      **
**                   try again until the timer tick provided by user is not   **
**                   less than difference between current and base stm ticks. **
** Service ID       : 0x14                                                    **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : LockAddress - It is used to lock the shared variables.  **
**                    Timeout - It is total time provided in micro second by  **
**                              user using which spinlock should be acquired. **
**                              Timeout value should be in range of 1 us to   **
**                              1048575 us (timeout when passed as 1 indicate **
**                              as 1 us to this API).                         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None.                                                   **
*******************************************************************************/
extern void Mcal_GetSpinlock
(volatile uint32 * const LockAddress, const uint32 Timeout);

/*******************************************************************************
** Traceability     : [cover parentID={87DDCCC6-8C0A-4942-B49F-A3BABA4BFCA2}] **
** [/cover]                                                                   **
** Syntax           : void Mcal_ReleaseSpinlock                               **
**                               (volatile uint32 * const LockAddress)        **
**                                                                            **
** Description     : This API will release the Spinlock and value of lock     **
                     address will be 0x0U.                                    **
**                                                                            **
**                                                                            **
** Service ID      : 0x15                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters(in)   : Lock Address                                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
extern void Mcal_ReleaseSpinlock(volatile uint32 * const LockAddress);

/*******************************************************************************
** Traceability     : [cover parentID={79233180-2CAD-4a65-A94F-FEB42233EEC0}] **
** [/cover]                                                                   **
** Syntax           : void McalLib_GetVersionInfo                             **
**                                (Std_VersionInfoType* const versioninfo)    **
** Description      : Function "McalLib_GetVersionInfo" shall have means to   **
**                    provide the version information of the MCALLIB module.  **
**                                                                            **
** Service ID       : 0x0                                                     **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : versioninfo - Pointer to where to store the version     **
                      information of MCALLIB module.                          **
**                                                                            **
** Parameters (out) : MCALLIB version information                             **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void  McalLib_GetVersionInfo( Std_VersionInfoType* const versioninfo);

/*******************************************************************************
** Traceability     :[cover parentID=]                                        **
** [/cover]                                                                   **
** Syntax           : void Mcal_WriteSafetyEndInitProtReg16                   **
                     (volatile void* const RegAddress, const uint16 DataValue)**
**                                                                            **
** Description      : This API is needed to write required values to safety   **
**                    end-init protected registers by unprotecting to write   **
**                    and protecting back to keep protection intact           **
**                                                                            **
**                                                                            **
** Service ID       : 0x81                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : RegAddress - Safety Endinit protected register address  **
**                    DataValue - Value to be written to the register located **
**                    at RegAddress                                           **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Mcal_WriteSafetyEndInitProtReg16(volatile void* const RegAddress,
                                      const uint16 DataValue);

#define MCALLIB_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: 'McalLib_MemMap.h' is header file which
 * contains the memory sections for McalLib. It should not be guarded by
 * standard include. No side effects foreseen by violating this MISRA rule. */
#include "McalLib_MemMap.h"


#endif
