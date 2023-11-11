/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2021)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : Fls_17_Dmu_ac.c                                             **
**                                                                           **
**  VERSION    :  16.0.0                                                     **
**                                                                           **
**  DATE       :  2021-10-12                                                 **
**                                                                           **
**  VARIANT    : Variant PB                                                  **
**                                                                           **
**  PLATFORM   : Infineon AURIX2G                                            **
**                                                                           **
**  AUTHOR     : DL-AUTOSAR-Engineering                                      **
**                                                                           **
**  VENDOR     : Infineon Technologies                                       **
**                                                                           **
**  DESCRIPTION: This file contains command sequences of Flash driver        **
**                                                                           **
**  SPECIFICATION(S) : Specification of FLS Driver,                          **
**                           AUTOSAR Release 4.2.2 and 4.4.0                 **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: No                                      **
**                                                                           **
******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* [cover parentID={4D611C8D-52AA-42d4-92A1-B4280952EE29}][/cover] */

/* Inclusion of flash sfr file */
#include "IfxDmu_reg.h"

/* Inclusion of Flash header file */
#include "Fls_17_Dmu.h"

/* Include Flash Module access code File */
#include "Fls_17_Dmu_ac.h"

/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
/* size of data loaded into page buffer at a time - 8bytes */
#define FLS_LOAD_PAGE_SIZE   (8U)

/* number of words per FLS_LOAD_PAGE_SIZE */
#define FLS_17_TWO_WORDS     (2U)

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled. Hence this macro will be unused
in other pre-compile conditions. There is no side effect violating this rule.*/
#define FLS_WORD_SIZE_MASK        (3U)

/* Hardare Timeout for Command cycle*/
#define FLS_17_DMU_CMDCYCLE_TIMEOUT            (25U)

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
#define FLS_17_DMU_START_SEC_CODE_ASIL_B_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. Even though the memmap
   header is included multiple times, the contents of the file are protected
   from multiple definition / inclusion. */
#include "Fls_17_Dmu_MemMap.h"
static void Fls_lWriteCmdCycles(const uint32 StartAddress,
                        const uint32 PageAddress,
                        const Fls_17_Dmu_AddressType* const ProgramDataPtr,
                        const uint8 WriteMode);

static void Fls_lEraseCmdCycles(const uint32 EraseAddress);
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_STOP_SEC_CODE_ASIL_B_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. Even though the memmap
   header is included multiple times, the contents of the file are protected
   from multiple definition / inclusion. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline.*/
#include "Fls_17_Dmu_MemMap.h"

LOCAL_INLINE boolean Fls_lCmdCycleTimeout(const uint32 InnerCount);

LOCAL_INLINE void Fls_lCycle5554(const uint32 Address, const uint32 Data);

LOCAL_INLINE void Fls_lCycleAAA8(const uint32 Address, const uint32 Data);

LOCAL_INLINE void Fls_lCycleAA50(const uint32 Address, const uint32 Data);

LOCAL_INLINE void Fls_lCycleAA58(const uint32 Address, const uint32 Data);

LOCAL_INLINE void Fls_lEnterPageMode(const uint32 Address, const uint32 Data);

LOCAL_INLINE void Fls_lLoadPage(const uint32 Address,
                                     const Fls_17_Dmu_AddressType* DataPtr);

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. Even though the memmap
   header is included multiple times, the contents of the file are protected
   from multiple definition / inclusion. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Fls_17_Dmu_MemMap.h"
extern const Fls_17_Dmu_ConfigType *Fls_ConfigPtr;

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. Even though the memmap
   header is included multiple times, the contents of the file are protected
   from multiple definition / inclusion. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
 #include "Fls_17_Dmu_MemMap.h"
/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/*******************************************************************************
** Traceability      : [cover parentID={E28AA64E-CA28-4cb9-9619-03B489318E98}]**
** Syntax : static void Fls_lWriteCmdCycles( const uint32 StartAddress,       **
**                             const uint32 PageAddress,                      **
**                       const Fls_17_Dmu_AddressType* const ProgramDataPtr   **
**                             const uint8 WriteMode                          **
**                                )                                           **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : StartAddress,PageAddress, ProgramDataPtr and WriteMode   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : This routine contains flash write command cycles             **
*******************************************************************************/
#define FLS_17_DMU_START_SEC_CODE_ASIL_B_LOCAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. Even though the memmap
   header is included multiple times, the contents of the file are protected
   from multiple definition / inclusion. */
/* CYCLOMATIC_Fls_lWriteCmdCycles_JUSTIFICATION: This Function is the command
 sequence for WRITE operation and has to check for many error conditions(as
per HW manual) which is leading to many conditional blocks. Breaking it into
local function will break the continuity of the command sequence*/
#include "Fls_17_Dmu_MemMap.h"
static void Fls_lWriteCmdCycles(const uint32 StartAddress,
                         const uint32 PageAddress,
                         const Fls_17_Dmu_AddressType* const ProgramDataPtr,
                         const uint8 WriteMode
                       )
{
  uint32 InnerCount;
  const Fls_17_Dmu_AddressType* pdata;
  Fls_17_Dmu_StateType* StatePtr;
  uint8 FlsSqerProtErr;
  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
  StatePtr->FlsTimeoutErr = 0U;
  FlsSqerProtErr = 0U;
  pdata = ProgramDataPtr;
  uint32 TimeOutCount;
  uint32 TimeOutCountInitial;
  uint32 TimeOutResolution;
  uint32 MeasuredTicks;

  /* Enter the Page Mode */
  Fls_lEnterPageMode(StartAddress, VALUE_5D);

  InnerCount = 0U;
  /* [cover parentID={D2FE3714-4104-455a-BD3E-0A20EF1CC9AC}]
  Is the sequence or protection error not detected or timeout has
  not happened or the status of DFPAGE bit is still not set?
  [/cover] */
  /*MISRA2012_RULE_13_5_JUSTIFICATION: No side effects due to order
  of evaluation of SFR declared volatile */
  while((DMU_HF_STATUS.B.DFPAGE != 1U) && \
        (InnerCount < FLS_17_DMU_CMDCYCLE_TIMEOUT) && \
        ((DMU_HF_ERRSR.B.SQER != 1U) && (DMU_HF_ERRSR.B.PROER != 1U)))
  {
    InnerCount++;
  }

  /* [cover parentID={5B8F5CD2-7BAA-43a3-8A28-25461B108C96}]
    Is the sequence error or protextion error detected ?
    [/cover] */
  /*MISRA2012_RULE_13_5_JUSTIFICATION: No side effects due to order
    of evaluation of SFR declared volatile */
  if((DMU_HF_ERRSR.B.SQER != 0U) || (DMU_HF_ERRSR.B.PROER != 0U))
  {
  /* [cover parentID={894F63D9-ED8A-4cee-BAD9-B19C597B3E65}]
    Set the sequence/protection error flag.
    [/cover] */
    FlsSqerProtErr = (uint8)1;
  }
  /* Check for command cycle Timeout */
  /* [cover parentID={7CD255DA-3A52-419e-A92A-FD403D848CA8}]
  Check for command cycle timeout ?
  [/cover] */
  if ((boolean)TRUE == Fls_lCmdCycleTimeout(InnerCount))
  {
    StatePtr->FlsTimeoutErr = FLS_17_DMU_WRITE;
  }
  /* [cover parentID={D932A957-AF90-4155-AB1B-9E04D85AE292}]
  Is the Sequence/protection error flag set ?
  [/cover] */
  else if (FlsSqerProtErr == (uint8)0)
  /* Check DFPAGE bit was SET */
  {
  /* [cover parentID={7F4B02D0-2884-42fa-BA9C-B6D1E0AD0F84}]
    Is the write mode = BURST
    [/cover] */
    if(WriteMode == FLS_17_DMU_BURST_WRITE)
    {
      InnerCount = (FLS_17_DMU_BURST_PAGE_SIZE / FLS_LOAD_PAGE_SIZE);
    }
    else
    {
      InnerCount = (FLS_17_DMU_PAGE_SIZE / FLS_LOAD_PAGE_SIZE);
    }
    /* [cover parentID={00BE431B-1CF4-4435-939C-9D6621BA4339}]
    Is the load page counter zero?
    [/cover] */
    while(InnerCount != 0U)
    {
      /* Load the data */
      Fls_lLoadPage(StartAddress, pdata);

      /* Page assembly buffer pointer gets incremented automatically */
      /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
      array indexing used for buffer address calculation and for subsequent
      traversal.The access range is within the valid range.*/
      pdata += FLS_17_TWO_WORDS;
      InnerCount--;
    }

    /* cycle 1 */
    Fls_lCycleAA50(StartAddress, PageAddress);
    /* cycle 2 */
    Fls_lCycleAA58(StartAddress, VALUE_00);

    /* cycle 3 */
    Fls_lCycleAAA8(StartAddress, VALUE_A0);

    /* [cover parentID={DB32ACFE-30AF-4391-967E-CE0DBDD535CF}]
    Is the writemode = BURST ?
    [/cover] */
    /* cycle 4 */
    if(WriteMode == FLS_17_DMU_BURST_WRITE)
    {
      Fls_lCycleAAA8(StartAddress, VALUE_A6);
    }
    else
    {
      Fls_lCycleAAA8(StartAddress, VALUE_AA);
    }

    InnerCount = 0U;

    /* [cover parentID={D5043E9E-2393-4da0-864E-211F54209D1B}]
    Is the programming still going on and there is no sequence or
    protection error and there is no timeout?
    [/cover] */
    /*MISRA2012_RULE_13_5_JUSTIFICATION: No side effects due to order
    of evaluation of SFR declared volatile */
    while((DMU_HF_OPERATION.B.PROG != 1U) &&    \
          (InnerCount < FLS_17_DMU_CMDCYCLE_TIMEOUT) && \
          ((DMU_HF_ERRSR.B.SQER != 1U) && (DMU_HF_ERRSR.B.PROER != 1U)))
    {
        /* [cover parentID={DD61E8C8-FD4B-4300-A02A-99B9BC7A3035}]
        Increment the time out variable.
        [/cover] */
      InnerCount++;
    }

    /* [cover parentID={177FF266-018D-410c-9B98-A9A98A923A0A}]
    Has timeout happened ?
    [/cover] */
    if ((boolean)TRUE == Fls_lCmdCycleTimeout(InnerCount))
    {
      StatePtr->FlsTimeoutErr = FLS_17_DMU_WRITE;
    }
    /* [cover parentID={AB7F7F55-C2C8-435a-8E97-3F74E1ACEACB}]
    [/cover] */
    /*MISRA2012_RULE_13_5_JUSTIFICATION: No side effects due to order
    of evaluation of SFR declared volatile */
    else if((DMU_HF_ERRSR.B.SQER != 1U) && (DMU_HF_ERRSR.B.PROER != 1U))
    {
      /* [cover parentID={282544B2-97FE-42a1-90D4-156115A4456B}]
      [/cover] */
      /*Wait for 100ns*/
      TimeOutResolution = Mcal_DelayTickResolution();
      TimeOutCount = (uint32)FLS_17_DMU_HWBUSY_DELAY / TimeOutResolution;
      TimeOutCountInitial = Mcal_DelayGetTick();

      do
      {
        MeasuredTicks = Mcal_DelayGetTick() -  TimeOutCountInitial;

      } while (TimeOutCount > MeasuredTicks);
      /* Flsstart ticks*/
      #if (FLS_17_DMU_TIMEOUT_SUPERVISION == STD_ON)
      /*Capture initial time-stamp*/
      StatePtr->FlsCmdStartTicks = Mcal_DelayGetTick();
      #endif
    }
    else
    {
      /*Dummy else for MISRA*/
    }
  }

  else
  {
    /*dummy else*/
  }
}


/*******************************************************************************
** Traceability : [cover parentID={D05B71FA-3BD8-4082-A5D0-96C88DFE1B88}]     **
** Syntax : static void Fls_lEraseCmdCycles(const uint32 EraseAddress)        **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : StartAddress                                             **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : This routine contains flash Erase command cycles             **
*******************************************************************************/
static void Fls_lEraseCmdCycles(const uint32 EraseAddress)
{
  uint32 InnerCount;
  uint32 StartAddress;
  uint8 EraseNumSec;
  uint32 TimeOutCount;
  uint32 TimeOutCountInitial;
  uint32 TimeOutResolution;
  uint32 MeasuredTicks;
  Fls_17_Dmu_StateType* StatePtr;

  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
  StatePtr->FlsTimeoutErr = 0U;
  EraseNumSec  = StatePtr->FlsEraseNumSecPerCmd;
  StartAddress = FLS_17_DMU_BASE_ADDRESS;
  /* cycle 1 */
  Fls_lCycleAA50(StartAddress, EraseAddress);
  /* cycle 2 */
  Fls_lCycleAA58(StartAddress, EraseNumSec);
  /* cycle 3 */
  Fls_lCycleAAA8(StartAddress, VALUE_80);
  /* cycle 4 */
  Fls_lCycleAAA8(StartAddress, VALUE_50);

  InnerCount = 0U;
  /* [cover parentID={F8169FB3-7136-418f-91E5-8685240E10EB}]
  Is the erase operation ongoing and the timeout has not happened
  and no sequence/protection error ?
  [/cover] */
  /*MISRA2012_RULE_13_5_JUSTIFICATION: No side effects due to order
  of evaluation of SFR declared volatile */
  while((DMU_HF_OPERATION.B.ERASE != 1U) &&   \
        (InnerCount < FLS_17_DMU_CMDCYCLE_TIMEOUT) && \
        ((DMU_HF_ERRSR.B.SQER != 1U) && (DMU_HF_ERRSR.B.PROER != 1U)))
  {
    InnerCount++;
  }

  /* [cover parentID={F9EB7FAE-AF68-468e-8433-6550F41B6FF8}]
  Has the timeout happened ?
  [/cover] */
  /*return Error there is a Timeout has happened */
  if ((boolean)TRUE == Fls_lCmdCycleTimeout(InnerCount))
  {
    StatePtr->FlsTimeoutErr = FLS_17_DMU_ERASE;
  }
  /*No sequence or protection error delay*/
  /* [cover parentID={B7658696-2459-4064-B4FE-2C696E4CE0EE}]
  [/cover] */
  /*MISRA2012_RULE_13_5_JUSTIFICATION: No side effects due to order
  of evaluation of SFR declared volatile */
  else if((DMU_HF_ERRSR.B.SQER != 1U) && (DMU_HF_ERRSR.B.PROER != 1U))
  {
    /*Wait for 100ns*/
    TimeOutResolution = Mcal_DelayTickResolution();
    TimeOutCount = (uint32)FLS_17_DMU_HWBUSY_DELAY / TimeOutResolution;
    TimeOutCountInitial = Mcal_DelayGetTick();

    do
    {
      MeasuredTicks = Mcal_DelayGetTick() -  TimeOutCountInitial;

    } while (TimeOutCount > MeasuredTicks);
    #if (FLS_17_DMU_TIMEOUT_SUPERVISION == STD_ON)
    /*Capture initial time-stamp*/
    StatePtr->FlsCmdStartTicks = Mcal_DelayGetTick();
    #endif
  }
  else
  {
      /*Dummy else for MISRA*/
  }
}
/*******************************************************************************
** Traceability      : [cover parentID={3EDE5110-6FEA-4a76-AF6E-0D82B833FAD1}]**
** Syntax : void Fls_lCallEraseCommand(const uint32 PhysicalAddress)          **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : PhysicalAddress                                          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : This routine calls flash Erase command cycles                **
*******************************************************************************/
void Fls_lCallEraseCommand(const uint32 PhysicalAddress)
{
    /*[cover parentID={3EDE5110-6FEA-4a76-AF6E-0D82B833FAD1}][/cover]*/
  Fls_lEraseCmdCycles(PhysicalAddress);

}

/*******************************************************************************
** Traceability   : [cover parentID={979BD858-458C-48e1-850D-E5F3DB61140D}]   **
** Syntax : void Fls_lCallWriteCommand(const uint32 PhysicalAddress,          **
**                       const Fls_17_Dmu_StateType *const StatePtr,          **
**                       const uint8 WriteMode)                               **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : PhysicalAddress, StatePtr, WriteMode                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : This routine calls flash write command cycles                **
*******************************************************************************/
void Fls_lCallWriteCommand(const uint32 PhysicalAddress,
                          const Fls_17_Dmu_StateType *const StatePtr,
                          const uint8 WriteMode)
{
    Fls_lWriteCmdCycles(PhysicalAddress,
                StatePtr->FlsWriteAddress,
    /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast
      is required to interface with the Dflash as it supports burst operations
       as well.The access range would already be checked for validity
       is within the flash address range */
                (const Fls_17_Dmu_AddressType*)StatePtr->FlsWriteBufferPtr,
                WriteMode);
}

/*******************************************************************************
** Traceability     : [cover parentID={6F8BADF8-9CC5-4f39-B3CA-943359E4BB7A}] **
** Syntax : void Fls_lResetReadCmdCycle(void)                                 **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : This routine contains flash Reset command cycles             **
*******************************************************************************/
void Fls_lResetReadCmdCycle(void)
{
  Fls_lCycle5554(FLS_17_DMU_BASE_ADDRESS, VALUE_F0);
}

/*******************************************************************************
** Traceability     : [cover parentID={03F78078-A11D-4d0e-907E-85646DED0A77}] **
** Syntax : void Fls_ClearStatusCmdCycle(void)                                **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : This routine contains flash clear status command cycles      **
*******************************************************************************/
void Fls_lClearStatusCmdCycle(void)
{
  /*[cover parentID={03F78078-A11D-4d0e-907E-85646DED0A77}][/cover]*/
  Fls_lCycle5554(FLS_17_DMU_BASE_ADDRESS, VALUE_FA);

}
#if (FLS_17_DMU_USE_ERASESUSPEND == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={BC5F8267-E635-4f4b-93CD-BB9373DD3024}]   **
** Syntax : void Fls_ResumeEraseCmdCycle(const uint32 StartAddress)           **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : StartAddress                                             **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : This routine contains flash resume erase command cycles      **
*******************************************************************************/
void Fls_lResumeEraseCmdCycle(const uint32 EraseAddress)
{

  uint32 StartAddress;
  uint8 EraseNumSec;
  const Fls_17_Dmu_StateType* StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
  EraseNumSec  = StatePtr->FlsEraseNumSecPerCmd;
  StartAddress = FLS_17_DMU_BASE_ADDRESS;

  /* cycle 1 */
  Fls_lCycleAA50(StartAddress, EraseAddress);

  /* cycle 2 */
  Fls_lCycleAA58(StartAddress, EraseNumSec);
  /* cycle 3 */
  Fls_lCycleAAA8(StartAddress, VALUE_70);
  /* cycle 4 */
  Fls_lCycleAAA8(StartAddress, VALUE_CC);
}
#endif /* FLS_17_DMU_USE_ERASESUSPEND == STD_ON */

/*******************************************************************************
** Traceability     : [cover parentID={05A73B74-EB36-4d6b-ACD6-BE0365197CE9}] **
** Syntax : void Fls_lUserContentCountCmdCycle(const uint32 WordLineAddress)  **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : WordLineAddress                                          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : This routine contains user content count command cycles      **
*******************************************************************************/
void Fls_lUserContentCountCmdCycle(const uint32 WordLineAddress)
{
  uint32 TimeOutCount;
  uint32 TimeOutCountInitial;
  uint32 TimeOutResolution;
  uint32 MeasuredTicks;
  /*[cover parentID={05A73B74-EB36-4d6b-ACD6-BE0365197CE9}][/cover] */
  uint32 StartAddress;
  StartAddress = FLS_17_DMU_BASE_ADDRESS;
  /* cycle 1 */
  Fls_lCycleAA50(StartAddress, WordLineAddress);
  /* cycle 2 */
  Fls_lCycleAA58(StartAddress, VALUE_00);
  /* cycle 3 */
  Fls_lCycleAAA8(StartAddress, VALUE_60);
  /* cycle 4 */
  Fls_lCycleAAA8(StartAddress, VALUE_14);

  /*Wait for 100ns*/
  TimeOutResolution = Mcal_DelayTickResolution();
  TimeOutCount = (uint32)FLS_17_DMU_HWBUSY_DELAY / TimeOutResolution;
  TimeOutCountInitial = Mcal_DelayGetTick();

  do
  {
    MeasuredTicks = Mcal_DelayGetTick() -  TimeOutCountInitial;

  } while (TimeOutCount > MeasuredTicks);

}
/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/

/*******************************************************************************
** Traceability     : [cover parentID={5D6E9D51-CF9C-473e-A04B-49B186086D16}] **
**                                                                            **
** Syntax: LOCAL_INLINE boolean Fls_lCmdCycleTimeout(const uint32 InnerCount) **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : InnerCount - Delay count                                 **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : boolean                                                  **
**                                                                            **
** Description : This routine checks if command cycle timeout occured         **
*******************************************************************************/
LOCAL_INLINE boolean Fls_lCmdCycleTimeout(const uint32 InnerCount)
{
  boolean RetVal;
  /* [cover parentID={A342486B-4B87-4f56-93BE-9AA362DDF172}]
  Is the command cycle counter greater than the configured command cycle
  timeout value ?
  [/cover] */
  if (InnerCount >= (uint32)FLS_17_DMU_CMDCYCLE_TIMEOUT)
  {
    /* [cover parentID={B60708BF-6C6F-4051-86F4-AE2F03E8666B}]
    [/cover] */
    RetVal = (boolean)TRUE;
  }
  else
  {
    /* [cover parentID={0E9E3292-D9FF-4a60-ADA1-F6370F212D5C}]
    [/cover] */
    RetVal = (boolean)FALSE;
  }
  return (RetVal);
}

/*******************************************************************************
** Traceability   : [cover parentID={2544FA01-8FBB-44f8-AA6B-23192E0792BF}]   **
** Syntax: LOCAL_INLINE void Fls_lCycle5554(const uint32 Address,             **
**                                                     const uint32 Data)     **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : Address, Data                                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value : None                                                        **
**                                                                            **
** Description : cmd cycle formation                                          **
*******************************************************************************/
LOCAL_INLINE void Fls_lCycle5554(const uint32 Address, const uint32 Data)
{
  uint32 StartAddress;
  StartAddress = ((Address) & MASK_HIGHER4_NIBBLES) + CYCLE_5554;
  /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from uint32 to pointer is required
     to store the data into the FLASH address/target address. No memory
     alignment issues.*/
  /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from uint32 to pointer
     type is required to store data into the FLASH address passed. No memory
     alignment issues. */
  *((volatile uint32*)StartAddress) = Data;
  DSYNC();
  return;
}

/*******************************************************************************
** Traceability     : [cover parentID={4B0DFE26-2619-48df-A703-CF8F905D71CF}] **
** Syntax: LOCAL_INLINE void CycleAAA8(const uint32 Address,                  **
**                                          const uint32 Data)                **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : Address, Data                                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value : None                                                        **
**                                                                            **
** Description : cmd cycle formation                                          **
*******************************************************************************/
LOCAL_INLINE void Fls_lCycleAAA8(const uint32 Address, const uint32 Data)
{
  uint32 StartAddress;
  StartAddress = ((Address) & MASK_HIGHER4_NIBBLES) + CYCLE_AAA8;
  /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from uint32 to pointer is required
     to store the data into the FLASH address/target address. No memory
     alignment issues.*/
  /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from uint32 to pointer
     type is required to store data into the FLASH address passed. No memory
     alignment issues. */
  *((volatile uint32*)StartAddress) = Data;
  DSYNC();
  return;
}

/*******************************************************************************
** Traceability     : [cover parentID={5E552EA7-13F9-4118-AF05-1CD567C573A9}] **
** Syntax: LOCAL_INLINE void CycleAA50(const uint32 Address,                  **
**                                          const uint32 Data)                **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : Address, Data                                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value : None                                                        **
**                                                                            **
** Description : cmd cycle formation                                          **
*******************************************************************************/
LOCAL_INLINE void Fls_lCycleAA50(const uint32 Address, const uint32 Data)
{
  /*[cover parentID={5E552EA7-13F9-4118-AF05-1CD567C573A9}][/cover] */
  uint32 StartAddress;
  StartAddress = ((Address) & MASK_HIGHER4_NIBBLES) + CYCLE_AA50;
  /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from uint32 to pointer is required
     to store the data into the FLASH address/target address. No memory
     alignment issues.*/
  /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from uint32 to pointer
     type is required to store data into the FLASH address passed. No memory
     alignment issues. */
  *((volatile uint32*)StartAddress) = Data;
  DSYNC();
  return;
}

/*******************************************************************************
**Traceability: [cover parentID={29FAE174-CA94-40b6-BA64-B2054A79A258}]       **
**Syntax: LOCAL_INLINE void CycleAA58(const uint32 Address, const uint32 Data)**
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : Address, Data                                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value : None                                                        **
**                                                                            **
** Description : cmd cycle formation                                          **
*******************************************************************************/
LOCAL_INLINE void Fls_lCycleAA58(const uint32 Address, const uint32 Data)
{
  uint32 StartAddress;
  StartAddress = ((Address) & MASK_HIGHER4_NIBBLES) + CYCLE_AA58;
  /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from uint32 to pointer is required
     to store the data into the FLASH address/target address. No memory
     alignment issues.*/
  /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from uint32 to pointer
     type is required to store data into the FLASH address passed. No memory
     alignment issues. */
  *((volatile uint32*)StartAddress) = Data;
  DSYNC();
  return;
}


/*******************************************************************************
** Traceability     : [cover parentID={D945F34C-7B95-428b-B9DF-AB23B2DF29CD}] **
** Syntax: LOCAL_INLINE void Fls_lEnterPageMode(const uint32 address,         **
**                                              const uint32 Data)            **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : address , Data                                           **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value : None                                                        **
**                                                                            **
** Description : cmd cycle formation                                          **
*******************************************************************************/
LOCAL_INLINE void Fls_lEnterPageMode(const uint32 Address, const uint32 Data)
{
  uint32 StartAddress;

  StartAddress = ((Address) & MASK_HIGHER4_NIBBLES) + CYCLE_5554;
  /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from uint32 to pointer is required
     to store the data into the FLASH address/target address. No memory
     alignment issues.*/
  /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from uint32 to pointer
     type is required to store data into the FLASH address passed. No memory
     alignment issues. */
  *((volatile uint32*)StartAddress) = Data;
  DSYNC();

  return;
}

/*******************************************************************************
** Traceability   : [cover parentID={475D10EA-2B17-43ea-8CF5-F58EC1B1DBA9}]   **
** Syntax: LOCAL_INLINE void Fls_lLoadPage(const uint32 Address,              **
**                                    const Fls_17_Dmu_AddressType* DataPtr)  **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : address                                                  **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value : None                                                        **
**                                                                            **
** Description : cmd cycle formation                                          **
*******************************************************************************/
LOCAL_INLINE void Fls_lLoadPage(const uint32 Address,
                                const Fls_17_Dmu_AddressType* DataPtr)
{
  volatile Fls_17_Dmu_AddressType* StartAddress;
  uint64 PageData;
  uint8 * PageDataPtr;
  const uint8 * PageDataPtrCpy;

  /* [cover parentID={D246E7FB-1E54-4467-8193-EFECF1FE355A}]
  Is the DataPtr word aligned?
  [/cover] */
  /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from pointer to uint32
     is required to check the value of the address for data buffer alignment.
     No memory alignment issues.*/
  /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from pointer to uint32
     type is required to access the FLASH address/target address which
     is defined as uint32. No memory alignment issues.*/
  /* MISRA2012_RULE_10_4_JUSTIFICATION: cast from pointer to uint32
    is required to check the value of the address for data buffer alignment.
   The implicit conversion will only compare the value*/
  if (((uint32)DataPtr & FLS_WORD_SIZE_MASK) != 0)
  {
    /*MISRA2012_RULE_1_3_JUSTIFICATION: The address of this variable is used
    within the context of this function. Hence, no side effects and unexpected
    behavior. This is done to take care of the user buffer address alignment
    requirement. */
    PageDataPtr = (uint8*)&PageData;
    /*MISRA2012_RULE_11_8_JUSTIFICATION: This function does not update the
    contents of the pointer. The cast is performed to facilitate bytewise
    copy of data*/
    PageDataPtrCpy = (uint8*)DataPtr;
    PageDataPtr[0] = PageDataPtrCpy[0];
    PageDataPtr[1] = PageDataPtrCpy[1];
    PageDataPtr[2] = PageDataPtrCpy[2];
    PageDataPtr[3] = PageDataPtrCpy[3];
    PageDataPtr[4] = PageDataPtrCpy[4];
    PageDataPtr[5] = PageDataPtrCpy[5];
    PageDataPtr[6] = PageDataPtrCpy[6];
    PageDataPtr[7] = PageDataPtrCpy[7];
  }
  else
  {
    /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion from uint32 to uint64 pointer
     type is required to write 64 bit data in page assembly buffer. No side effects.*/
    /*MISRA2012_RULE_1_3_JUSTIFICATION: Conversion from uint32 to uint64 pointer
     type is required to write 64 bit data in page assembly buffer. No side effects.*/
    /*MISRA2012_RULE_11_8_JUSTIFICATION: Conversion from uint32 to uint64 pointer
     type is required to write 64 bit data in page assembly buffer. No side effects.*/
    PageData = *((uint64*)DataPtr);
  }

  StartAddress = (volatile Fls_17_Dmu_AddressType *)
  /* MISRA2012_RULE_11_6_JUSTIFICATION: Cast from uint32 to pointer is required
     to store the data into the FLASH address/target address. No memory
     alignment issues.*/
  /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion from uint32 to pointer
     type is required to access the FLASH address. No memory alignment
     issues. */
  /* MISRA2012_RULE_10_8_JUSTIFICATION: Conversion from uint32 to pointer
       type is required to access the FLASH address/target address which
       is defined as uint32. */
               (((Address) & MASK_HIGHER4_NIBBLES) + CYCLE_55F0);

  /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion from uint32 to uint64 pointer
     type is required to write 64 bit data in page assembly buffer. No side effects.*/
  /*MISRA2012_RULE_1_3_JUSTIFICATION: Conversion from uint32 to uint64 pointer
     type is required to write 64 bit data in page assembly buffer. No side effects.*/
  /*MISRA2012_RULE_11_8_JUSTIFICATION: Conversion from uint32 to uint64 pointer
     type is required to write 64 bit data in page assembly buffer. No side effects.*/
  *((uint64*)StartAddress) = PageData;
  DSYNC();
  return;
}




/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_STOP_SEC_CODE_ASIL_B_LOCAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. Even though the memmap
   header is included multiple times, the contents of the file are protected
   from multiple definition / inclusion. */
#include "Fls_17_Dmu_MemMap.h"

