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
**  FILENAME     : Fee_Demo.c                                                 **
**                                                                            **
**  VERSION      : 0.0.3                                                      **
**                                                                            **
**  DATE         : 2021-03-30                                                 **
**                                                                            **
**  VARIANT      : NA                                                         **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Demo application for FEE module                            **
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
#include "Fee.h"
#include "Fee_Cbk.h"
#include "SchM_Fee.h"
#include "SchM_Fls_17_Dmu.h"
#include "Fee_Demo.h"
#include "Test_Print.h"
#include "Mcal_Compiler.h"
#include "DemoApp.h"

/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

#define FEE_BLK_1       (1U)
#define FEE_BLK1_SIZE   (20U)

#define FEE_BLK_2       (2U)
#define FEE_BLK2_SIZE   (12U)

#define FEE_BLK_3       (3U)
#define FEE_BLK3_SIZE   (4096U-36U)

#define FEE_BUF_SIZE    (FEE_BLK3_SIZE)

#define Time_s(num)     (num*60*1000000)

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
#define FEE_START_SEC_CODE_ASIL_B_LOCAL
#include "Fee_MemMap.h"

LOCAL_INLINE void Fee_lFillWriteBuf_Seed(   uint16 BlkSize,
    uint8 seed,
    boolean print
                                        );

LOCAL_INLINE void Fee_lFillWriteBuf_Const(  uint16 BlkSize,
    uint8 val,
    boolean print
                                         );

LOCAL_INLINE Std_ReturnType Fee_lDemoRead(  uint16 BlockNumber,
    uint16 Length
                                         );

LOCAL_INLINE Std_ReturnType Fee_lDemoWrite(uint16 BlockNumber);

LOCAL_INLINE Std_ReturnType Fee_lDemoEraseQS(uint16 BlockNumber);

LOCAL_INLINE Std_ReturnType Fee_lComp(uint16 BlkSize);

LOCAL_INLINE Std_ReturnType Fee_lDemoSetup(void);

#define FEE_STOP_SEC_CODE_ASIL_B_LOCAL
#include "Fee_MemMap.h"

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

#define FEE_START_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
#include "Fee_MemMap.h"

extern const Fee_ConfigType Fee_Config;

#define FEE_STOP_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
#include "Fee_MemMap.h"

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
#define FEE_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
#include "Fee_MemMap.h"

static uint8 WriteDataBuffer[FEE_BUF_SIZE];
static uint8 ReadDataBuffer[FEE_BUF_SIZE];
static uint32 Fee_DemoCalled;
static boolean Fee_DemoCheckStatus;
static uint8 u8gTestFee_FeeInitFlag;
#define FEE_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
#include "Fee_MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define FEE_START_SEC_CODE_ASIL_B_LOCAL
#include "Fee_MemMap.h"

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : void Fee_Demo(void)                                       **
**                                                                            **
** Description    : Write/Read of blocks with desired data                    **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : none                                                      **
**                                                                            **
** Parameters(out): none                                                      **
**                                                                            **
** Return value   : none                                                      **
**                                                                            **
*******************************************************************************/
/* 1. Write Blk1 with 12341234 data
   2. Write Blk2 with AAAAAAAA data
   3. Write Blk1 with ABCDABCD data
   4. Write Blk2 with 99999999 data
   5. Check if Blk1 has ABCDABCD data
   6. Check if Blk2 has 99999999 data
   7. Write QS Blk3 with 56785678 data
   8. Check if QS Blk3 has 56785678 data
   9. Erase QS Blk3
*/
void Fee_Demo(void)
{
  Std_ReturnType resultflag;
  const Fls_17_Dmu_ConfigType * ConfigPtr = &Fls_17_Dmu_Config;

  Fee_DemoCheckStatus = FALSE;
  resultflag = E_OK;

  print_f("\n---------------  Start of FEE driver demo ---------------\n");

  /* Initialize FLS driver if not already done */
  if( DemoApp_FlsInitDone == 0U )
  {
    Fls_17_Dmu_Init(ConfigPtr);
    DemoApp_FlsInitDone = 1U;
  }

  if(Fee_DemoCalled == 0U)
  {
    /* Clear the DFlash to start the FEE Demo */
    resultflag = Fee_lDemoSetup();
    Fee_DemoCalled = 1U;
  }

  if(resultflag == E_OK)
  {
    print_f("\n1.Write Blk1 with data :  \n");

    /* Fill the buffer with 0xA,0xB,0xC,0xD,0xA,0xB... */
    /* 1. Write Blk1 with 12341234 data */
    Fee_lFillWriteBuf_Seed(FEE_BLK1_SIZE, 1, TRUE);
    resultflag = Fee_lDemoWrite(FEE_BLK_1);
    if( resultflag == E_OK)
    {
      print_f("\n2.Write Blk2 with data : \n");
      /* 2. Write Blk2 with AAAAAAAA data */
      Fee_lFillWriteBuf_Const(FEE_BLK2_SIZE, 0xA, TRUE);
      resultflag = Fee_lDemoWrite(FEE_BLK_2);
      if(resultflag == E_OK)
      {
        print_f("\n3.Write Blk1 with data : \n");
        /* 3. Write Blk1 with ABCDABCD data */
        Fee_lFillWriteBuf_Seed(FEE_BLK1_SIZE, 0xA, TRUE);
        resultflag = Fee_lDemoWrite(FEE_BLK_1);
        if(resultflag == E_OK)
        {
          print_f("\n4.Write Blk2 with data : \n");
          /* 4. Write Blk2 with 99999999 data */
          Fee_lFillWriteBuf_Const(FEE_BLK2_SIZE, 0x9, TRUE);
          resultflag = Fee_lDemoWrite(FEE_BLK_2);
          if(resultflag == E_OK)
          {
            print_f("\n5.Reading Blk1 data : \n");
            /* 5. Check if Blk1 has ABCDABCD data */
            Fee_lFillWriteBuf_Seed(FEE_BLK1_SIZE, 0xA, FALSE);
            resultflag = Fee_lDemoRead(FEE_BLK_1, FEE_BLK1_SIZE);
            if(resultflag == E_OK)
            {
              resultflag = Fee_lComp(FEE_BLK1_SIZE);
              if(resultflag == E_OK)
              {
                print_f("\n6.Reading Blk2 data : \n");
                /* 6. Check if Blk2 has 99999999 data */
                Fee_lFillWriteBuf_Const(FEE_BLK2_SIZE, 0x9, FALSE);
                resultflag = Fee_lDemoRead(FEE_BLK_2, FEE_BLK2_SIZE);
                if(resultflag == E_OK)
                {
                  resultflag = Fee_lComp(FEE_BLK2_SIZE);
                  if(resultflag == E_OK)
                  {
                    print_f("\n7.Write Blk3 with data : \n");
                    /* 7. Write QS Blk3 with 56785678 data */
                    Fee_lFillWriteBuf_Seed(FEE_BLK3_SIZE, 0x5, TRUE);
                    resultflag = Fee_lDemoWrite(FEE_BLK_3);
                    if(resultflag == E_OK)
                    {
                      print_f("\n8.Reading Blk3 data : \n");
                      /* 8. Check if QS Blk3 has 56785678 data */
                      Fee_lFillWriteBuf_Seed(FEE_BLK3_SIZE, 0x5, FALSE);
                      resultflag = Fee_lDemoRead(FEE_BLK_3, FEE_BLK3_SIZE);
                      if(resultflag == E_OK)
                      {
                        resultflag = Fee_lComp(FEE_BLK3_SIZE);
                        if(resultflag == E_OK)
                        {
                          print_f("\n9.Erasing Blk3 : \n");
                          /* 8. Erase QS Blk3 */
                          resultflag = Fee_lDemoEraseQS(FEE_BLK_3);
                          if(resultflag == E_OK)
                          {

                            StartResult();
                            print_f("Result = Pass;");
                            EndResult();

                          }/*end of step9 */
                        }/*end of compare */
                      }/*end of step8 */
                    }/*end of step7 */
                  }/*end of compare */
                }/*end of step6 */
              }/*end of compare */
            }/*end of step5 */
          }/*end of step4 */
        }/*end of step3 */
      }/*end of step2 */
    }/*end of step1 */
  }/*end of Setup */

  if( resultflag != E_OK)
  {
    StartResult();
    print_f("Result = Fail;");
    EndResult();
  }

  print_f("\n---------------  End of FEE driver demo ---------------\n");

}
#define FEE_STOP_SEC_CODE_ASIL_B_LOCAL
#include "Fee_MemMap.h"
/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : void NvM_JobEndNotification (void)                        **
**                                                                            **
** Description    : This function marks the completion of the requested  NVM  **
**                  operation                                                 **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : none                                                      **
**                                                                            **
** Parameters(out): none                                                      **
**                                                                            **
** Return value   : none                                                      **
**                                                                            **
*******************************************************************************/
void NvM_JobEndNotification (void)
{
  Fee_DemoCheckStatus = TRUE;
}

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : void NvM_JobErrorNotification (void)                      **
**                                                                            **
** Description    : This function marks the completion of the requested NVM   **
**                  operation(failure)                                        **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : none                                                      **
**                                                                            **
** Parameters(out): none                                                      **
**                                                                            **
** Return value   : none                                                      **
**                                                                            **
*******************************************************************************/
void NvM_JobErrorNotification (void)
{
  Fee_DemoCheckStatus = TRUE;
}

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : void NvM_IllegalStateNotification (void)                  **
**                                                                            **
** Description    : This function indicates that the FEE has reached an       **
**                  illegal state                                             **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : none                                                      **
**                                                                            **
** Parameters(out): none                                                      **
**                                                                            **
** Return value   : none                                                      **
**                                                                            **
*******************************************************************************/
void NvM_IllegalStateNotification (void)
{
  Fee_DemoCheckStatus = TRUE;
  print_f("\nIllegal state notification function called: ");
  print_f("FEE reached illegal state");
}

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : void QS_JobEndNotification (void)                         **
**                                                                            **
** Description    : This function marks the completion of the requested  QS   **
**                  operation                                                 **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : none                                                      **
**                                                                            **
** Parameters(out): none                                                      **
**                                                                            **
** Return value   : none                                                      **
**                                                                            **
*******************************************************************************/
void QS_JobEndNotification (void)
{
  Fee_DemoCheckStatus = TRUE;
}

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : void QS_JobErrorNotification (void)                       **
**                                                                            **
** Description    : This function marks the completion of the requested  QS   **
**                  operation(failure)                                        **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : none                                                      **
**                                                                            **
** Parameters(out): none                                                      **
**                                                                            **
** Return value   : none                                                      **
**                                                                            **
*******************************************************************************/
void QS_JobErrorNotification (void)
{
  Fee_DemoCheckStatus = TRUE;
}

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
#define FEE_START_SEC_CODE_ASIL_B_LOCAL
#include "Fee_MemMap.h"

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : LOCAL_INLINE void Fee_lFillWriteBuf_Seed                  **
**                    (                                                       **
**                        uint16 BlkSize, uint8 seed, boolean print           **
**                    )                                                       **
**                                                                            **
** Description    : This function fills the buffer with data starting with    **
**                    value 'seed' and then keeps incrementing the same       **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : BlkSize : Size of the block                               **
**                  Seed    : Starting value to be written                    **
**                  print   : Enable/Disable printing of data being written   **
**                                                                            **
** Parameters(out): none                                                      **
**                                                                            **
** Return value   : none                                                      **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Fee_lFillWriteBuf_Seed(uint16 BlkSize, uint8 seed, boolean print)
{
  uint16 i = 0;

  do
  {
    if(i < BlkSize)
    {
      WriteDataBuffer[i] = (i % 4) + seed;
      if( TRUE == print )
      {
        print_f(" %x ", WriteDataBuffer[i]);
        /* Avoid printing more than 20 data elements on screen */
        if ( i > 20)
        {
          print_f(" .... ");
          print = FALSE;
        }
      }
    }
    else
    {
      WriteDataBuffer[i] = 0;
    }
    i++;
  } while(i < FEE_BUF_SIZE);

}

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : LOCAL_INLINE void Fee_lFillWriteBuf_Const                 **
**                    (                                                       **
**                        uint16 BlkSize, uint8 val, boolean print            **
**                    )                                                       **
**                                                                            **
** Description    : This function fills the buffer with data 'val'            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : BlkSize : Size of the block                               **
**                  val     : value to be written                             **
**                  print   : Enable/Disable printing of data being written   **
**                                                                            **
** Parameters(out): none                                                      **
**                                                                            **
** Return value   : none                                                      **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Fee_lFillWriteBuf_Const(uint16 BlkSize,
    uint8 val,
    boolean print)
{
  uint16 i = 0;

  do
  {
    if(i < BlkSize)
    {
      WriteDataBuffer[i] = val;
      if(print)
      {
        print_f(" %x ", WriteDataBuffer[i]);
      }
    }
    else
    {
      WriteDataBuffer[i] = 0;
    }
    i++;
  } while(i < FEE_BUF_SIZE);

}

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : LOCAL_INLINE Std_ReturnType Fee_lDemoRead                 **
**                    (                                                       **
**                        uint16 BlockNumber, uint16 Length                   **
**                    )                                                       **
**                                                                            **
** Description    : This reads the required number of bytes                   **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : BlockNumber : Number of the block                         **
**                  Length      : Number of bytes to be read                  **
**                                                                            **
** Parameters(out): none                                                      **
**                                                                            **
** Return value   : Return status of the Read operation                       **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fee_lDemoRead( uint16 BlockNumber,
    uint16 Length)
{
  uint16 i;
  uint16 StopPrint = 0;
  Std_ReturnType resultflag;

  resultflag = Fee_Read(BlockNumber, 0, ReadDataBuffer, Length);
  if(resultflag == E_OK)
  {
    while(Fee_DemoCheckStatus != TRUE)
    {
      /* Wait till Fee_DemoCheckStatus is set in one of the notification
         functions */
      Fee_MainFunction();
      Fls_17_Dmu_MainFunction();
    }

    if( (Fee_GetStatus() != MEMIF_IDLE) ||
        (Fee_GetJobResult() != MEMIF_JOB_OK) ||
        (Fee_17_GetQuasiStaticJobResult() != MEMIF_JOB_OK)
      )
    {
      resultflag = E_NOT_OK;
    }

    for(i = 0; ((i < Length) && (StopPrint != 1)); i++)
    {
      print_f(" %x ", ReadDataBuffer[i]);
      /* Avoid printing more than 20 data elements on screen */
      if ( i > 20 )
      {
        print_f(" ... ");
        StopPrint = 1;
      }
    }

    Fee_DemoCheckStatus = FALSE;
  }
  return(resultflag);
}

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : LOCAL_INLINE Std_ReturnType Fee_lDemoWrite                **
**                    (                                                       **
**                        uint16 BlockNumber                                  **
**                    )                                                       **
**                                                                            **
** Description    : This writes the specified block                           **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : BlockNumber : Number of the block                         **
**                                                                            **
** Parameters(out): none                                                      **
**                                                                            **
** Return value   : Return status of the Write operation                      **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fee_lDemoWrite( uint16 BlockNumber)
{
  Std_ReturnType resultflag;

  resultflag = Fee_Write(BlockNumber, WriteDataBuffer);
  if(resultflag == E_OK)
  {
    while(Fee_DemoCheckStatus != TRUE)
    {
      /* Wait till Fee_DemoCheckStatus is set in one of the notification
         functions */
      Fee_MainFunction();
      Fls_17_Dmu_MainFunction();
    }

    if( (Fee_17_GetQuasiStaticJobResult() != MEMIF_JOB_OK) ||
        (Fee_GetJobResult() != MEMIF_JOB_OK)
      )
    {
      resultflag = E_NOT_OK;
    }

    Fee_DemoCheckStatus = FALSE;
  }
  return(resultflag);

}

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : LOCAL_INLINE Std_ReturnType Fee_lDemoEraseQS              **
**                    (                                                       **
**                        uint16 BlockNumber                                  **
**                    )                                                       **
**                                                                            **
** Description    : This erases the specified QS block                        **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : BlockNumber : Number of the block                         **
**                                                                            **
** Parameters(out): none                                                      **
**                                                                            **
** Return value   : Return status of the Erase operation                      **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fee_lDemoEraseQS( uint16 BlockNumber )
{
  Std_ReturnType resultflag;
  Fee_QuasiStaticBlockInfoType BlockInfo;

  resultflag = Fee_17_EraseQuasiStaticData(BlockNumber, 1);
  if(resultflag == E_OK)
  {
    while(Fee_DemoCheckStatus != TRUE)
    {
      /* Wait till Fee_DemoCheckStatus is set in one of the notification
         functions */
      Fee_MainFunction();
      Fls_17_Dmu_MainFunction();
    }

    if( (Fee_GetStatus() != MEMIF_IDLE) ||
        (Fee_17_GetQuasiStaticJobResult() != MEMIF_JOB_OK)
      )
    {
      resultflag = E_NOT_OK;
    }
    else
    {
      resultflag = Fee_17_GetQuasiStaticBlockInfo(BlockNumber, &BlockInfo);
      if( (E_OK == resultflag ) &&
          (FEE_QS_ERASE_COMPLETE == BlockInfo.State)
        )
      {
        print_f("QS block erased successfully");
      }
      else
      {
        resultflag = E_NOT_OK;
      }
    }

    Fee_DemoCheckStatus = FALSE;
  }
  return(resultflag);
}

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : LOCAL_INLINE Std_ReturnType Fee_lComp                     **
**                    (                                                       **
**                        uint16 BlkSize                                      **
**                    )                                                       **
**                                                                            **
** Description    : This function compares the read data with expected data   **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : BlkSize : Number of the bytes to be compared              **
**                                                                            **
** Parameters(out): none                                                      **
**                                                                            **
** Return value   : Return status of the Compare operation                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fee_lComp(uint16 BlkSize)
{
  uint16 i;
  Std_ReturnType retval;

  retval = E_OK;

  for(i = 0; i < BlkSize; i++)
  {
    if(WriteDataBuffer[i] != ReadDataBuffer[i])

    {
      retval = E_NOT_OK;
    }
  }
  return(retval);
}

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : LOCAL_INLINE Std_ReturnType Fee_lDemoSetup(void)          **
**                                                                            **
** Description    : This function erases the DFLASH allowing for the start    **
**                  of the demo                                               **
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
** Return value   : Return status of the erasing of DFLASH                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fee_lDemoSetup(void)
{
  Std_ReturnType resultflag;

  /* Clear the entire DFlash */
  resultflag = Fls_17_Dmu_Erase(0, FLS_17_DMU_TOTAL_SIZE);
  if(resultflag == E_OK)
  {
    while(Fls_17_Dmu_GetStatus() != MEMIF_IDLE)
    {
      /* Wait till Flash is erased */
      Fls_17_Dmu_MainFunction();
    }

    Fee_DemoCheckStatus = FALSE;
  }

  Fee_Init(&Fee_Config);
  u8gTestFee_FeeInitFlag = 1;
  while(Fee_GetStatus() != MEMIF_IDLE)
  {
    Fee_MainFunction();
    Fls_17_Dmu_MainFunction();
  }

  return(resultflag);
}

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : void Test_FeeJobEndNotification(void)                     **
**                                                                            **
** Description    : Job End notification function invoked by FLS to FEE       **
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
** Return value   : Void                                                      **
**                                                                            **
*******************************************************************************/
void Test_FeeJobEndNotification(void)
{
  if(1 == u8gTestFee_FeeInitFlag)
  {
    Fee_JobEndNotification();
  }
}

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : void Test_FeeJobErrorNotification(void)                   **
**                                                                            **
** Description    : Job Error notification function invoked by FLS to FEE     **
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
** Return value   : void                                                      **
**                                                                            **
*******************************************************************************/
void Test_FeeJobErrorNotification(void)
{
  if(1 == u8gTestFee_FeeInitFlag)
  {
    Fee_JobErrorNotification();
  }
}

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : void Test_FeeJobEraseErrorNotification(void)              **
**                                                                            **
** Description    : Erase job Error Erase notification function invoked by FLS**
**                  to FEE                                                    **
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
** Return value   : void                                                      **
**                                                                            **
*******************************************************************************/
void Test_FeeJobEraseErrorNotification(void)
{
  if(1 == u8gTestFee_FeeInitFlag)
  {
    Fee_17_JobEraseErrorNotification();
  }
}


/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : void Test_Fee_17_IllegalStateNotification(void)           **
**                                                                            **
** Description    : Illegal State notification function is invoked by FLS to  **
**                  FEE                                                       **
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
** Return value   : void                                                      **
**                                                                            **
*******************************************************************************/
void Test_Fee_17_IllegalStateNotification(void)
{
  if (1 != u8gTestFee_FeeInitFlag)
  {
    NvM_IllegalStateNotification();
  }
  else
  {
    Fee_17_IllegalStateNotification();
  }
}

#define FEE_STOP_SEC_CODE_ASIL_B_LOCAL
#include "Fee_MemMap.h"
