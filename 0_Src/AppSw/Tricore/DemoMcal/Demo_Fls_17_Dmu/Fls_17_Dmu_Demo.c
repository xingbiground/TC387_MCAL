/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2016)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : Fls_17_Dmu_Demo.c                                          **
**                                                                            **
**  VERSION      : 0.0.2                                                      **
**                                                                            **
**  DATE         : 2016-12-14                                                 **
**                                                                            **
**  VARIANT      : NA                                                         **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Demo application for FLS module                            **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#if defined _GHS_C_TRICORE_
#pragma ghs nowarning 1729
#include "Std_Types.h"
#pragma ghs endnowarning 1729
#else
#include "Std_Types.h"
#endif
#include "Fls_17_Dmu.h"
#include "SchM_Fls_17_Dmu.h"
#include "Test_Print.h"
#include "Test_Time.h"
#include "DemoApp.h"

/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
#define FLS_DFLASH_BANK0_BASE (0U)

#define FLS_DFLASH_BANK1_BASE (FLS_NVMSECTOR_SIZE)

#define FLS_BUF_SIZE    (512U)

#define Time_s(num)     (num*1000U)

#define CALL_CYCLE      (100U * 1000U)
/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
#define FLS_17_DMU_START_SEC_CODE_ASIL_B_LOCAL
#include "Fls_17_Dmu_MemMap.h"

LOCAL_INLINE void Fls_lFillBuf(void);

LOCAL_INLINE Std_ReturnType Fls_lDemoCompare(void);

LOCAL_INLINE Std_ReturnType Fls_lDemoWrite(void);

LOCAL_INLINE Std_ReturnType Fls_lDemoRead(void);

LOCAL_INLINE Std_ReturnType Fls_lDemoSetup(void);

LOCAL_INLINE Std_ReturnType Fls_lDemoCancel(uint32 JobType);

LOCAL_INLINE void Fls_lCallMain(void);

#define FLS_17_DMU_STOP_SEC_CODE_ASIL_B_LOCAL
#include "Fls_17_Dmu_MemMap.h"

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

#define FLS_17_DMU_START_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
#include "Fls_17_Dmu_MemMap.h"

extern const Fls_17_Dmu_ConfigType Fls_17_Dmu_Config;

#define FLS_17_DMU_STOP_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
#include "Fls_17_Dmu_MemMap.h"

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/


static uint8 DataBuffer[FLS_BUF_SIZE];
static uint8 DataBufferRead[FLS_BUF_SIZE];


/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define FLS_17_DMU_START_SEC_CODE_ASIL_B_LOCAL
#include "Fls_17_Dmu_MemMap.h"

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : void Fls_17_Dmu_Demo(void)                                **
**                                                                            **
** Description    : Calls data flash driver APIs for demo                     **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : None                                                      **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
void Fls_17_Dmu_Demo(void)
{
  volatile uint32 delay = 0U;
  Std_ReturnType resultflag;
  const Fls_17_Dmu_ConfigType * ConfigPtr = &Fls_17_Dmu_Config;

  print_f("\n---------------  Start of FLS driver demo ---------------\n");

  /* Initialize FLS driver if not already done */
  if( DemoApp_FlsInitDone == 0U )
  {
    Fls_17_Dmu_Init(ConfigPtr);
    DemoApp_FlsInitDone = 1U;
  }

  /* Clear the DFlash to start the FLS Demo */
  /* FLS_STATE_VAR.FlsEraseTimeoutCycleCount = 0x100; for Debug support test */

  resultflag = Fls_lDemoSetup();
  if( resultflag == E_OK)
  {
    print_f("\n1.Write Blk1 with data :  \n");
    /* 1. Fill buffer with 12345... data */
    Fls_lFillBuf();
    resultflag = Fls_lDemoWrite();
    if( resultflag == E_OK)
    {
      print_f("\n2.Comparing the data : \n");
      /* 2. Compare the contents of DFlash with the buffer */
      resultflag = Fls_lDemoCompare();
      if(resultflag == E_OK)
      {
        print_f("The data in the flash is same as data in buffer");

        resultflag = Fls_lDemoRead();
        if(resultflag == E_OK)
        {
          print_f("\nDemoRead successful \n");
          resultflag = Fls_lDemoCancel(FLS_17_DMU_ERASE);
          if(resultflag == E_OK)
          {
            while(delay < 0xFFFFFFU)
            {
              delay++;
            }
            resultflag = Fls_lDemoCancel(FLS_17_DMU_WRITE);
            if(resultflag == E_OK)
            {
              delay = 0U;
              while(delay < 0xFFFFU)
              {
                delay++;
              }
              resultflag = Fls_lDemoCancel(FLS_17_DMU_READ);
              if(resultflag == E_OK)
              {
                resultflag = Fls_lDemoCancel(FLS_17_DMU_COMPARE);
              }
            }
          }
          if(resultflag == E_OK)
          {
            resultflag = Fls_17_Dmu_Read(0U, DataBufferRead, FLS_BUF_SIZE);
            if(resultflag == E_OK)
            {
              if(Fls_17_Dmu_GetStatus() == MEMIF_BUSY)
              {
                print_f("Calling CancelNonEraseJobs for Read ");
                Fls_17_Dmu_CancelNonEraseJobs();
              }
              if((Fls_17_Dmu_GetStatus() == MEMIF_IDLE) &&
                  (Fls_17_Dmu_GetJobResult() == MEMIF_JOB_CANCELED) )
              {
                resultflag = E_OK;
              }
              else
              {
                resultflag = E_NOT_OK;
              }
            }
          }
        }
        if(resultflag == E_OK)
        {
          StartResult();
          print_f("Result = Pass;");
          EndResult();
        }
      }/*end of step2 */
    }/*end of step1 */
  }/*end of Setup */

  if( resultflag != E_OK)
  {
    StartResult();
    print_f("Result = Fail;");
    EndResult();
  }

  print_f("\n---------------  End of FLS driver demo ---------------\n");
}

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : LOCAL_INLINE void Fls_lFillBuf(void)                      **
**                                                                            **
** Description    : Fills data buffer with integer data                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : None                                                      **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Fls_lFillBuf(void)
{
  uint16 i;

  i = 0;
  do
  {
    DataBuffer[i] = (uint8)i;
    print_f(" %x ", DataBuffer[i]);
    i++;
  } while(i < FLS_BUF_SIZE);

}

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : LOCAL_INLINE Std_ReturnType Fls_lDemoCompare(void)        **
**                                                                            **
** Description    : Compares data in flash with the data in known data buffer **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : None                                                      **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : Std_ReturnType - Compare command result status            **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fls_lDemoCompare(void)
{
  Std_ReturnType resultflag;
  volatile uint32 count = 0U;

  resultflag = Fls_17_Dmu_Compare(0U, DataBuffer, FLS_BUF_SIZE);
  if(resultflag == E_OK)
  {
    while((Fls_17_Dmu_GetStatus() != MEMIF_IDLE) && (count < Time_s(2U)))
    {
      /* Wait till Job completion */
      count++;
      Fls_lCallMain();
    }

    if( (Fls_17_Dmu_GetStatus() != MEMIF_IDLE) ||
        (Fls_17_Dmu_GetJobResult() != MEMIF_JOB_OK)
      )
    {
      resultflag = E_NOT_OK;
    }
  }
  return(resultflag);
}

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : LOCAL_INLINE Std_ReturnType Fls_lDemoRead(void)           **
**                                                                            **
** Description    : Reads data in flash & stores into known data buffer       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : None                                                      **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : Std_ReturnType - Read command result status               **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fls_lDemoRead(void)
{
  Std_ReturnType resultflag;
  volatile uint32 count = 0U;

  count = 0U;
  resultflag = Fls_17_Dmu_Read(0U, DataBufferRead, FLS_BUF_SIZE);
  if(resultflag == E_OK)
  {
    while((Fls_17_Dmu_GetStatus() != MEMIF_IDLE) && (count < Time_s(2U)))
    {
      /* Wait till Job is finished */
      count++;
      Fls_lCallMain();
    }

    if( (Fls_17_Dmu_GetStatus() != MEMIF_IDLE) ||
        (Fls_17_Dmu_GetJobResult() != MEMIF_JOB_OK)
      )
    {
      resultflag = E_NOT_OK;
    }
    else
    {
      uint32 i;
      i = 0;
      while((i < FLS_BUF_SIZE) && (resultflag != E_NOT_OK))
      {
        if(DataBuffer[i] != DataBufferRead[i])
        {
          resultflag = E_NOT_OK;
        }
        i++;
      }
    }
  }
  #if((defined FLS_IFX_FEE_USED) && (FLS_IFX_FEE_USED == STD_ON))
  if(resultflag == E_OK)
  {
    if(Fls_17_Dmu_ReadWordsSync(0U, (uint32 *)DataBufferRead,
                                (FLS_BUF_SIZE / 4)) == E_OK)
    {
      resultflag = Fls_17_Dmu_CompareWordsSync(0U, (uint32 *)DataBufferRead,
                   (FLS_BUF_SIZE / 4));
    }
    else
    {
      resultflag = E_NOT_OK;
    }
  }
  #endif
  return(resultflag);
}

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : LOCAL_INLINE Std_ReturnType Fls_lDemoCancel(              **
**                                                           uint32 JobType)  **
**                                                                            **
** Description    : Cancels the ongoing FLS operation                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : JobType - Job type currently running, that gets cancelled **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : Std_ReturnType - Cancel command result status             **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fls_lDemoCancel(uint32 JobType)
{
  Std_ReturnType resultflag;

  switch(JobType)
  {
    case FLS_17_DMU_WRITE:
    {
      resultflag = Fls_17_Dmu_Write(0U, DataBuffer, FLS_BUF_SIZE);

      if((resultflag == E_OK) && (Fls_17_Dmu_GetStatus() == MEMIF_BUSY))
      {
        print_f("\n Cancelling Write \n");
        Fls_17_Dmu_Cancel();
      }
      if((Fls_17_Dmu_GetStatus() == MEMIF_IDLE) &&
          (Fls_17_Dmu_GetJobResult() == MEMIF_JOB_CANCELED) )
      {
        resultflag = E_OK;
      }
      else
      {
        resultflag = E_NOT_OK;
      }
      break;
    }

    case FLS_17_DMU_ERASE:
    {
      resultflag = Fls_17_Dmu_Erase(FLS_DFLASH_BANK0_BASE, FLS_17_DMU_NVMSECTOR_SIZE);

      if((resultflag == E_OK) && (Fls_17_Dmu_GetStatus() == MEMIF_BUSY))
      {
        print_f("\n Cancelling Erase \n");
        Fls_17_Dmu_Cancel();
      }
      if((Fls_17_Dmu_GetStatus() == MEMIF_IDLE) &&
          (Fls_17_Dmu_GetJobResult() == MEMIF_JOB_CANCELED) )
      {
        resultflag = E_OK;
      }
      else
      {
        resultflag = E_NOT_OK;
      }
      break;
    }

    case FLS_17_DMU_READ:
    {
      resultflag = Fls_17_Dmu_Read(0U, DataBufferRead, FLS_BUF_SIZE);

      if((resultflag == E_OK) && (Fls_17_Dmu_GetStatus() == MEMIF_BUSY))
      {
        print_f("\n Cancelling Read \n");
        Fls_17_Dmu_Cancel();
      }
      if((Fls_17_Dmu_GetStatus() == MEMIF_IDLE) &&
          (Fls_17_Dmu_GetJobResult() == MEMIF_JOB_CANCELED) )
      {
        resultflag = E_OK;
      }
      else
      {
        resultflag = E_NOT_OK;
      }
      break;
    }

    case FLS_17_DMU_COMPARE:
    {
      resultflag = Fls_17_Dmu_Compare(0U, DataBufferRead, FLS_BUF_SIZE);

      if((resultflag == E_OK) && (Fls_17_Dmu_GetStatus() == MEMIF_BUSY))
      {
        print_f("\n Cancelling Compare \n");
        Fls_17_Dmu_Cancel();
      }
      if((Fls_17_Dmu_GetStatus() == MEMIF_IDLE) &&
          (Fls_17_Dmu_GetJobResult() == MEMIF_JOB_CANCELED) )
      {
        resultflag = E_OK;
      }
      else
      {
        resultflag = E_NOT_OK;
      }
      break;
    }
    default :
      resultflag = E_NOT_OK;
      break;

  }

  return(resultflag);
}

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : LOCAL_INLINE Std_ReturnType Fls_lDemoWrite(void)          **
**                                                                            **
** Description    : Writes data to flash from known data buffer               **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : None                                                      **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : Std_ReturnType - Write command result status              **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fls_lDemoWrite(void)
{
  Std_ReturnType resultflag1;

  #if((defined FLS_IFX_FEE_USED) && (FLS_IFX_FEE_USED == STD_ON))
  Std_ReturnType resultflag2;
  #endif
  uint32 WriteSize;
  uint32 WriteAddr;
  volatile uint32 count = 0U;

  WriteSize = FLS_BUF_SIZE * 5U;
  WriteAddr = 0U;
  do {
    resultflag1 = Fls_17_Dmu_Write(WriteAddr, DataBuffer, FLS_BUF_SIZE);

    if(resultflag1 == E_OK)
    {
      while((Fls_17_Dmu_GetStatus() != MEMIF_IDLE) && (count < Time_s(2U)))
      {
        /* Wait till Job is finished */
        count++;
        Fls_lCallMain();
      }

      if( (Fls_17_Dmu_GetStatus() != MEMIF_IDLE) ||
          (Fls_17_Dmu_GetJobResult() != MEMIF_JOB_OK)
        )
      {
        resultflag1 = E_NOT_OK;
      }
      else
      {
        resultflag1 = Fls_17_Dmu_Compare(WriteAddr, DataBuffer, FLS_BUF_SIZE);
        if(resultflag1 == E_OK)
        {
          count = 0U;
          while((Fls_17_Dmu_GetStatus() != MEMIF_IDLE) && (count < Time_s(1)))
          {
            /* Wait till Job is finished */
            count++;
            Fls_lCallMain();
          }
          if( (Fls_17_Dmu_GetStatus() != MEMIF_IDLE) ||
              (Fls_17_Dmu_GetJobResult() != MEMIF_JOB_OK)
            )
          {
            resultflag1 = E_NOT_OK;
            print_f("\n compare data failed at: 0x%x \n", WriteAddr);
          }
		  #if((defined FLS_IFX_FEE_USED) && (FLS_IFX_FEE_USED == STD_ON))
          resultflag2 = Fls_17_Dmu_CompareWordsSync(WriteAddr,
                        (const uint32*)DataBuffer, (FLS_BUF_SIZE / 4));
          if(resultflag2 == E_OK)
          {
            print_f("\nComparing with margin 0 successful\n");
          }
          else
          {
            print_f("\nComparing with margin 0 failed\n");
          }
          #endif
        }

        print_f("\nWritten and compared data at: 0x%x \n", WriteAddr);

        if(resultflag1 == E_OK)
        {
          WriteSize -= FLS_BUF_SIZE ;
          WriteAddr += FLS_BUF_SIZE ;
        }
      }
    }
  } while((WriteSize > 0U) && (resultflag1 == E_OK));

  return(resultflag1);
}

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : LOCAL_INLINE Std_ReturnType Fls_lDemoSetup(void)          **
**                                                                            **
** Description    : Erases flash sectors and verifies if it is successful     **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : None                                                      **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : Std_ReturnType - Erase verification result status         **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fls_lDemoSetup(void)
{
  Std_ReturnType resultflag1;
  #if((defined FLS_IFX_FEE_USED) && (FLS_IFX_FEE_USED == STD_ON))
  Std_ReturnType resultflag2;
  uint32 UnerasedWordlineAddressPtr;
  uint8 UnerasedWordlineCountPtr;
  #endif
  volatile uint32 count = 0U;

  /* Clear the entire DFlash */
  print_f("\nErasing Flash... Please wait... \n");
  resultflag1 = Fls_17_Dmu_Erase(FLS_DFLASH_BANK0_BASE, FLS_17_DMU_TOTAL_SIZE);

  if(resultflag1 == E_OK)
  {
    #if ((defined FLS_USE_ERASESUSPEND) && (FLS_USE_ERASESUSPEND == STD_ON))
    resultflag1 = Fls_17_Dmu_SuspendErase(0U);

    if(resultflag1 == E_OK)
    {
      print_f("\n Suspend Erase Passed");
    }
    else
    {
      print_f("\nSuspend Erase Failed");
    }

    while(count <= CALL_CYCLE)
    {
      count++;
    }

    resultflag1 = Fls_17_Dmu_ResumeErase(0U);
    if(resultflag1 == E_OK)
    {
      print_f("\n Resume Erase Passed");
    }
    else
    {
      print_f("\n Resume Erase Failed");
    }

    count = 0U;
    #endif
    while((Fls_17_Dmu_GetStatus() != MEMIF_IDLE) && (count < Time_s(2U)))
    {
      /* Wait till Erase completed */
      print_f("*");
      count++;
      Fls_lCallMain();
    }

    if( (Fls_17_Dmu_GetStatus() != MEMIF_IDLE) ||
        (Fls_17_Dmu_GetJobResult() != MEMIF_JOB_OK)
      )
    {
      resultflag1 = E_NOT_OK;
    }
  }
  #if ((defined FLS_IFX_FEE_USED) && (FLS_IFX_FEE_USED == STD_ON))
  resultflag2 = Fls_17_Dmu_VerifyErase((Fls_AddressType)FLS_DFLASH_BANK0_BASE, &UnerasedWordlineAddressPtr,
                                       &UnerasedWordlineCountPtr);
  if(resultflag2 == E_OK)
  {
    print_f("\nVerify Erase for Sector0: WLAddr: %x , WLCount : %x \n",
            UnerasedWordlineAddressPtr, UnerasedWordlineCountPtr);
  }
  else
  {
    print_f("\nVerify Erase for Sector0 Failed: WLAddr: %x , WLCount : %x \n",
            UnerasedWordlineAddressPtr, UnerasedWordlineCountPtr);
  }
  resultflag2 = Fls_17_Dmu_VerifyErase((Fls_AddressType)FLS_DFLASH_BANK1_BASE, &UnerasedWordlineAddressPtr,
                                       &UnerasedWordlineCountPtr);
  if(resultflag2 == E_OK)
  {
    print_f("\nVerify Erase for Sector1: WLAddr: %x , WLCount : %x \n",
            UnerasedWordlineAddressPtr, UnerasedWordlineCountPtr);
  }
  else
  {
    print_f("\nVerify Erase for Sector1 Failed : WLAddr: %x , WLCount : %x \n",
            UnerasedWordlineAddressPtr, UnerasedWordlineCountPtr);
  }
  #endif
  return(resultflag1);
}

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : LOCAL_INLINE void Fls_lCallMain(void)                     **
**                                                                            **
** Description    : Calls FLS main function after defined delay               **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : None                                                      **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Fls_lCallMain(void)
{
  volatile uint32 CallCycleTime;
  CallCycleTime = 0U;

  while(CallCycleTime <= CALL_CYCLE)
  {
    CallCycleTime++;
  }

  Fls_17_Dmu_MainFunction();
}

#define FLS_17_DMU_STOP_SEC_CODE_ASIL_B_LOCAL
#include "Fls_17_Dmu_MemMap.h"
