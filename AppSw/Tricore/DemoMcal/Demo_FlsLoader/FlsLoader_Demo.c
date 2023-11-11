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
**  FILENAME     : FlsLoader_Demo.c                                           **
**                                                                            **
**  VERSION      : 2.0.0                                                      **
**                                                                            **
**  DATE         : 2021-11-26                                                 **
**                                                                            **
**  VARIANT      : NA                                                         **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Demo application for FlsLoader module                      **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Std_Types.h"
#include "FlsLoader.h"
#include "Test_Print.h"
#include "Test_Time.h"
#include "IfxCpu_reg.h"
#include "IfxCpu_bf.h"

#if  ( FLSLOADER_DEV_ERROR_DETECT == STD_ON )
#include "Det.h"
#endif

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
#define FLSLOADER_LOCKUNLOCK_DEMO 0 /* Disabled intentionally to avoid 
                                       unexpected chip lock situations */
#define UCB_PFLASH_ADDR FLSLOADER_UCB_PFLASH_ORGINAL_START
#define UCB_DFLASH_ADDR FLSLOADER_UCB_DFLASH_ORIGINAL_START
#define NUM_OF_SECT_1   (1U)
#define BUFFER_SIZE1    (512U) /* Number of bytes to be written */


/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Local Function Declarations                           **
*******************************************************************************/
static FlsLoader_ReturnType FlsLoader_lDFlashDemo(void);
static FlsLoader_ReturnType FlsLoader_lPFlashDemo(void);

#if (FLSLOADER_LOCK_UNLOCK_API == STD_ON)
static FlsLoader_ReturnType FlsLoader_lLockDemo(void);
static FlsLoader_ReturnType FlsLoader_lDFUnLockDemo(void);
static FlsLoader_ReturnType FlsLoader_lPFUnLockDemo(void);
#endif

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
static uint32 FlsLoader_Address = 0 ;

/* Data structure for user input solicitation */
static const PAR_t Flsloader_AddressStruct[] =
{
  {
    PAR_TYP_HEX,                    /* uwType */
    sizeof(FlsLoader_Address),      /* uwSize */
    &FlsLoader_Address,             /* pvData */
    0x0U,                           /* uwMin */
    0xFFFFFFFFU,                    /* uwMax */
    "AddressValue",                 /* szText */
    "%x"                            /* szOutputFormat */
  }
};

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
static char FlashLoader_Address[25] = "Address in Hex";

#if (FLSLOADER_LOCKUNLOCK_DEMO == 1)
/* Passwords fixed for testing */
static uint32 DfPassword[8] =
{
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

static uint32 PfPassword[8] =
{
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};
#endif /* #if (FLSLOADER_LOCKUNLOCK_DEMO == 1) */


static uint8 buffer[512] =
{
  0x11, 0x11, 0x11, 0x11, 0x22, 0x22, 0x22, 0x22,
  0x33, 0x33, 0x33, 0x33, 0x44, 0x44, 0x44, 0x44,
  0x55, 0x55, 0x55, 0x55, 0x66, 0x66, 0x66, 0x66,
  0x77, 0x77, 0x77, 0x77, 0x88, 0x88, 0x88, 0x88,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x11, 0x11, 0x11, 0x11, 0x22, 0x22, 0x22, 0x22,
  0x33, 0x33, 0x33, 0x33, 0x44, 0x44, 0x44, 0x44,
  0x55, 0x55, 0x55, 0x55, 0x66, 0x66, 0x66, 0x66,
  0x77, 0x77, 0x77, 0x77, 0x88, 0x88, 0x88, 0x88,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x11, 0x11, 0x11, 0x11, 0x22, 0x22, 0x22, 0x22,
  0x33, 0x33, 0x33, 0x33, 0x44, 0x44, 0x44, 0x44,
  0x55, 0x55, 0x55, 0x55, 0x66, 0x66, 0x66, 0x66,
  0x77, 0x77, 0x77, 0x77, 0x88, 0x88, 0x88, 0x88,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x11, 0x11, 0x11, 0x11, 0x22, 0x22, 0x22, 0x22,
  0x33, 0x33, 0x33, 0x33, 0x44, 0x44, 0x44, 0x44,
  0x55, 0x55, 0x55, 0x55, 0x66, 0x66, 0x66, 0x66,
  0x77, 0x77, 0x77, 0x77, 0x88, 0x88, 0x88, 0x88,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08
};

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : void FlsLoader_Demo(void)                                 **
**                                                                            **
** Description    : FlsLoader driver demo main function                       **
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
void FlsLoader_Demo(void)
{
  uint8 TempUSage = 0;
  char szString[80];
  uint32 *SourcePtr;
  uint32 *SourcePtr1;
  uint32 *TargetPtr;
  uint32 Data;
  uint32 LoopCount;
  uint32 DataValidateFlg;
  FlsLoader_ReturnType retval;

  #if (FLSLOADER_LOCKUNLOCK_DEMO == 1)
  FlsLoader_ReturnType retval2, retval11;
  #endif

  print_f("\n---------------  Start of FLSLOADER driver demo ---------------\n");

  /* FlsLoader Initialization execution */
  print_f("\nFlsLoader_Init started..\n");
  retval = FlsLoader_Init(NULL_PTR);
  /* STALL flag is enabled, as not all code is running from RAM during erase */
  Data = (CPU0_FLASHCON1.U | IFX_CPU_FLASHCON1_STALL_MSK);
  Mcal_WriteCpuEndInitProtReg(&CPU0_FLASHCON1.U, Data);

  if(retval == FLSLOADER_E_OK)
  {
    print_f("\n FlsLoader_Init Execution Passed \n");
  }
  else if (retval == FLSLOADER_E_NOT_OK)
  {
    print_f("\n FlsLoader_Init Execution Failed \n");
  }
  else if(retval == FLSLOADER_E_ROMVERSION)
  {
    print_f("\n FlsLoader_Init Execution Failed, DFLASH protected under OTP\n");
  }

  while (TempUSage != 1)
  {
    print_f("\n 1. DFlash Programming ");
    print_f("\n 2. DFlash Read ");
    print_f("\n 3. PFlash Programming ");
    print_f("\n 4. PFlash Read ");

    #if (FLSLOADER_LOCKUNLOCK_DEMO == 1)
    print_f("\n 5. LOCK       ");
    print_f("\n 6. UNLOCK DFlash    ");
    print_f("\n 7. UNLOCK PFlash    ");
    #endif
    print_f("\n X. Go back to main menu    ");
    print_f("\n Option: ");
    getline(szString, sizeof szString - 1);

    switch (*szString)
    {
      case '1':
        retval = FlsLoader_lDFlashDemo();
        if (retval == FLSLOADER_E_OK)
        {
          StartResult();
          print_f("Result = Pass;");
          EndResult();
        }
        else
        {
          StartResult();
          print_f("Result = Fail;");
          EndResult();
        }
        break;
      case '3':
        retval = FlsLoader_lPFlashDemo();
        if (retval == FLSLOADER_E_OK)
        {
          StartResult();
          print_f("Result = Pass;");
          EndResult();
        }
        else
        {
          StartResult();
          print_f("Result = Fail;");
          EndResult();
        }
        break;
      case '2':
      {
        print_f("\n Reading first 8 bytes from programmed DFlash Address\n");
        SourcePtr = (uint32*)FlsLoader_Address;
        Data = *(SourcePtr);
        print_f("\n Value at Address 0x%X 0x%X ", SourcePtr++, Data);
        Data = *(SourcePtr);
        print_f("\n Value at Address 0x%X 0x%X ", SourcePtr++, Data);
        Data = *(SourcePtr);
        print_f("\n Value at Address 0x%X 0x%X ", SourcePtr++, Data);
        Data = *(SourcePtr);
        print_f("\n Value at Address 0x%X 0x%X ", SourcePtr++, Data);
        Data = *(SourcePtr);
        print_f("\n Value at Address 0x%X 0x%X ", SourcePtr++, Data);
        Data = *(SourcePtr);
        print_f("\n Value at Address 0x%X 0x%X ", SourcePtr++, Data);
        Data = *(SourcePtr);
        print_f("\n Value at Address 0x%X 0x%X ", SourcePtr++, Data);
        Data = *(SourcePtr);
        print_f("\n Value at Address 0x%X 0x%X\n", SourcePtr, Data);

        TargetPtr = (uint32*)FlsLoader_Address;
        SourcePtr1 = (uint32 *)(&buffer);
        DataValidateFlg = 0UL;
        for(LoopCount = 0; LoopCount < (BUFFER_SIZE1 / 4); LoopCount++)
        {
          if(*(uint32 *)TargetPtr != *(uint32 *)SourcePtr1)
          {
            /* Data validation Failed */
            DataValidateFlg = 1UL;
            break;
          }
          ++TargetPtr;
          ++SourcePtr1;
        }

        if(DataValidateFlg == 0UL)
        {
          print_f("Data Present in Buffer and DFlash Address are same\n");
          StartResult();
          print_f("Result = Pass;");
          EndResult();
        }
        else
        {
          print_f("Data Present in Buffer and DFlash Address are not same\n");
          StartResult();
          print_f("Result = Fail;");
          EndResult();
        }
      }
      break;
      case '4':
      {
        print_f("\n Reading first 8 bytes from programmed PFlash Address\n");
        SourcePtr = (uint32*)FlsLoader_Address;
        Data = *(SourcePtr);
        print_f("\n Value at Address 0x%X 0x%X ", SourcePtr++, Data);
        Data = *(SourcePtr);
        print_f("\n Value at Address 0x%X 0x%X ", SourcePtr++, Data);
        Data = *(SourcePtr);
        print_f("\n Value at Address 0x%X 0x%X ", SourcePtr++, Data);
        Data = *(SourcePtr);
        print_f("\n Value at Address 0x%X 0x%X ", SourcePtr++, Data);
        Data = *(SourcePtr);
        print_f("\n Value at Address 0x%X 0x%X ", SourcePtr++, Data);
        Data = *(SourcePtr);
        print_f("\n Value at Address 0x%X 0x%X ", SourcePtr++, Data);
        Data = *(SourcePtr);
        print_f("\n Value at Address 0x%X 0x%X ", SourcePtr++, Data);
        Data = *(SourcePtr);
        print_f("\n Value at Address 0x%X 0x%X\n", SourcePtr, Data);

        TargetPtr = (uint32*)FlsLoader_Address;
        SourcePtr1 = (uint32 *)(&buffer);
        DataValidateFlg = 0UL;
        for(LoopCount = 0; LoopCount < (BUFFER_SIZE1 / 4); LoopCount++)
        {
          if(*(uint32 *)TargetPtr != *(uint32 *)SourcePtr1)
          {
            /* Data validation Failed */
            DataValidateFlg = 1UL;
            break;
          }
          ++TargetPtr;
          ++SourcePtr1;
        }

        if(DataValidateFlg == 0UL)
        {
          print_f("Data Present in Buffer and PFlash Address are same\n");
          StartResult();
          print_f("Result = Pass;");
          EndResult();
        }
        else
        {
          print_f("Data Present in Buffer and PFlash Address are not same\n");
          StartResult();
          print_f("Result = Fail;");
          EndResult();
        }
      }
      break;
      #if (FLSLOADER_LOCKUNLOCK_DEMO == 1)
      case '5':
        #if (FLSLOADER_LOCK_UNLOCK_API == STD_ON)
        retval2 = FlsLoader_lLockDemo();
        if (retval2 == FLSLOADER_E_OK)
        {
          StartResult();
          print_f("Result = Pass;");
          EndResult();
        }
        else
        {
          StartResult();
          print_f("Result = Fail;");
          EndResult();
        }
        #endif
        break;
      case '6':
        #if (FLSLOADER_LOCK_UNLOCK_API == STD_ON)
        FlsLoader_Address = 0xAF000000U;
        print_f("\n Erasing the DFlash where UCB write Protection is Enabled \n");
        print_f("\n API should return FLSLOADER_E_LOCKED \n");
        retval = FlsLoader_Erase(FlsLoader_Address, NUM_OF_SECT_1);
        if (retval == FLSLOADER_E_LOCKED)
        {
          print_f("\n FlsLoader_Erase returned FLSLOADER_E_LOCKED. expected output.\n");
          retval11 = FLSLOADER_E_OK;
          retval11 |= FlsLoader_lDFUnLockDemo();
        }
        else
        {
          print_f("\n FlsLoader is not locked properly, unlock cannot be executed .\n");
          retval11 = FLSLOADER_E_NOT_OK;
        }
        if (retval11 == FLSLOADER_E_OK)
        {
          StartResult();
          print_f("Result = Pass;");
          EndResult();
        }
        else
        {
          StartResult();
          print_f("Result = Fail;");
          EndResult();
        }
        #endif
        break;
      case '7':
        #if (FLSLOADER_LOCK_UNLOCK_API == STD_ON)
        FlsLoader_Address = 0xA0EFC000;
        print_f("\n Erasing the PFlash where UCB write Protection is Enabled \n");
        print_f("\n API should return FLSLOADER_E_LOCKED \n");
        retval11 =  FlsLoader_Erase((uint32)FlsLoader_Address, NUM_OF_SECT_1);
        if (retval11 == FLSLOADER_E_LOCKED)
        {
          print_f("\n FlsLoader_Erase returned FLSLOADER_E_LOCKED. expected output.\n");
          retval11 = FLSLOADER_E_OK;
          retval11 |= FlsLoader_lPFUnLockDemo();
        }
        else
        {
          print_f("\n PFlash1 is not locked properly, unlock cannot be executed .\n");
          retval11 = FLSLOADER_E_NOT_OK;
        }
        if (retval11 == FLSLOADER_E_OK)
        {
          retval =  FlsLoader_Erase((uint32)FlsLoader_Address, NUM_OF_SECT_1);
          if (retval == FLSLOADER_E_OK)
          {
            StartResult();
            print_f("Result = Pass;");
            EndResult();
          }
          else
          {
            StartResult();
            print_f("Result = Fail;");
            EndResult();
          }
        }
        else
        {
          StartResult();
          print_f("Result = Fail;");
          EndResult();
        }
        if (retval11 == FLSLOADER_E_OK)
        {
          StartResult();
          print_f("Result = Pass;");
          EndResult();
        }
        else
        {
          StartResult();
          print_f("Result = Fail;");
          EndResult();
        }
        #endif
        break;
        #endif
      case 'x':
      case 'X':
        TempUSage = 1;
        retval =  FlsLoader_DeInit();
        print_f("\n FlsLoader de-init returned %d\n", retval);
        break;
    }
  }
}/* End of FlsLoader_Demo */

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : static FlsLoader_ReturnType FlsLoader_lDFlashDemo(void)   **
**                                                                            **
** Description    : Dflash erase & program demo                               **
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
** Return value   : Return status of the Dflash erase & program demo          **
**                                                                            **
*******************************************************************************/
static FlsLoader_ReturnType FlsLoader_lDFlashDemo(void)
{
  FlsLoader_ReturnType retval;
  retval = FLSLOADER_E_NOT_OK;
  if (ParMenu(&FlashLoader_Address[0],
              (PAR_t *)Flsloader_AddressStruct,
              sizeof Flsloader_AddressStruct / sizeof Flsloader_AddressStruct[0]) != 'q')
  {
    print_f("\n Address in Hex , Value = 0x%x \n", FlsLoader_Address);
    print_f("\n Erase operation start..  \n");
    retval =  FlsLoader_Erase((uint32)FlsLoader_Address, NUM_OF_SECT_1);
    if(retval == FLSLOADER_E_OK)
    {
      print_f("\n DFlash_Erase Execution Passed \n");
      print_f("\n Programming at the specified address \n");
      retval = FlsLoader_Write((uint32)FlsLoader_Address, BUFFER_SIZE1, &buffer[0]);
      if(retval == FLSLOADER_E_OK)
      {
        print_f("\n DFlash_Write Execution Passed \n");
      }
      else if(retval == FLSLOADER_E_LOCKED)
      {
        print_f("\n DFlash_Write Execution stopped,Flash Protection is ON \n");
      }
      else if (retval == FLSLOADER_E_BUSY)
      {
        print_f("\n DFlash_Write  STOPPED, Flash is Busy \n");
      }
      else
      {
        print_f("\n DFlash_Write Failed \n");
      }
    }
    else if(retval == FLSLOADER_E_LOCKED)
    {
      print_f("\n DFlash_Erase Execution stopped,Flash Protection is ON \n");
    }
    else if (retval == FLSLOADER_E_BUSY)
    {
      print_f("\n DFlash_Erase  STOPPED, Flash is Busy \n");
    }
    else
    {
      print_f("\n DFlash_Erase Failed \n");
    }
  }
  return retval;
}
/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : static FlsLoader_ReturnType FlsLoader_lPFlashDemo(void)   **
**                                                                            **
** Description    : Pflash erase & program demo                               **
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
** Return value   : Return status of the Pflash erase & program demo          **
**                                                                            **
*******************************************************************************/
static FlsLoader_ReturnType FlsLoader_lPFlashDemo(void)
{
  FlsLoader_ReturnType retval;
  retval = FLSLOADER_E_NOT_OK;
  if (ParMenu(&FlashLoader_Address[0],
              (PAR_t *)Flsloader_AddressStruct,
              sizeof Flsloader_AddressStruct / sizeof Flsloader_AddressStruct[0]) != 'q')
  {
    print_f("\n Address in Hex , Value = 0x%x \n", FlsLoader_Address);
    print_f("\n Erase operation start..  \n");
    retval = FlsLoader_Erase((uint32)FlsLoader_Address, NUM_OF_SECT_1);
    if(retval == FLSLOADER_E_OK)
    {
      print_f("\n PFlash_Erase Execution Passed \n");
      print_f("\n Programming at the specified address \n");
      retval = FlsLoader_Write((uint32)FlsLoader_Address, BUFFER_SIZE1, &buffer[0]);
      if(retval == FLSLOADER_E_OK)
      {
        print_f("\n PFlash_Write Execution Passed \n");
      }
      else if(retval == FLSLOADER_E_LOCKED)
      {
        print_f("\n PFlash_Write Execution stopped,Flash Protection is ON \n");
      }
      else if (retval == FLSLOADER_E_BUSY)
      {
        print_f("\n PFlash_Write  STOPPED, Flash is Busy \n");
      }
      else
      {
        print_f("\n PFlash_Write Failed \n");
      }
    }
    else if(retval == FLSLOADER_E_LOCKED)
    {
      print_f("\n PFlash_Erase Execution stopped,Flash Protection is ON \n");
    }
    else if (retval == FLSLOADER_E_BUSY)
    {
      print_f("\n PFlash_Erase  STOPPED, Flash is Busy \n");
    }
    else
    {
      print_f("\n PFlash_Erase Failed \n");
    }
  }
  return retval;
}

#if (FLSLOADER_LOCK_UNLOCK_API == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : static FlsLoader_ReturnType FlsLoader_lLockDemo(void)     **
**                                                                            **
** Description    : Flash lock demo                                           **
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
** Return value   : Return status of the Flash lock demo                      **
**                                                                            **
*******************************************************************************/
static FlsLoader_ReturnType FlsLoader_lLockDemo(void)
{
  FlsLoader_ReturnType retval;

  print_f("\n FlsLoader_Lock Demo start..  \n");
  retval = FlsLoader_Lock();

  if(retval == FLSLOADER_E_OK)
  {
    print_f("\n FlsLoader_Lock Execution Passed \n");
  }
  else if(retval == FLSLOADER_E_LOCKED)
  {
    print_f("\n FlsLoader_Lock Execution stopped,Flash Protection is ON \n");
  }
  else if (retval == FLSLOADER_E_BUSY)
  {
    print_f("\n FlsLoader_Lock  STOPPED, Flash is Busy \n");
  }
  else
  {
    print_f("\n FlsLoader_Lock Failed \n");
  }
  return retval;
}
#endif

#if (FLSLOADER_LOCK_UNLOCK_API == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : static FlsLoader_ReturnType FlsLoader_lDFUnLockDemo(void) **
**                                                                            **
** Description    : DFlash unlock demo                                        **
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
** Return value   : Return status of the DFlash unlock demo                   **
**                                                                            **
*******************************************************************************/
static FlsLoader_ReturnType FlsLoader_lDFUnLockDemo(void)
{
  FlsLoader_ReturnType retval;
  uint32 DfStartAddress1;
  uint32 SectorSize1;
  SectorSize1 = 1;
  DfStartAddress1 = FlsLoader_Address;
  print_f("\n FlsLoader_UnLock Demo start..  \n");
  retval = FlsLoader_UnLock(UCB_DFLASH_ADDR, &DfPassword[0]);
  if(retval == FLSLOADER_E_OK)
  {
    print_f("\n FlsLoader_UnLock Execution Passed \n");
  }
  else if (retval == FLSLOADER_E_BUSY)
  {
    print_f("\n FlsLoader_UnLock  STOPPED, Flash is Busy \n");
  }
  else
  {
    print_f("\n FlsLoader_UnLock Failed \n");
  }
  if(retval == FLSLOADER_E_OK)
  {
    print_f("\n Erasing the Flash where UCB write Protection is disabled \n");
    print_f("\n API should return FLSLOADER_E_OK \n");
    retval = FlsLoader_Erase(DfStartAddress1, SectorSize1);
    if (retval == FLSLOADER_E_OK)
    {
      print_f("\n FlsLoader_Erase returned FLSLOADER_E_OK. expected output.\n");
    }
    else if (retval == FLSLOADER_E_LOCKED)
    {
      print_f("\n FlsLoader_Erase returned FLSLOADER_E_LOCKED. Incorrect output.\n");
    }
    else
    {
      print_f("\n FlsLoader_Erase execution Failed \n");
    }
  }
  return retval;
}

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : static FlsLoader_ReturnType FlsLoader_lPFUnLockDemo(void) **
**                                                                            **
** Description    : PFlash unlock demo                                        **
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
** Return value   : Return status of the PFlash unlock demo                   **
**                                                                            **
*******************************************************************************/
static FlsLoader_ReturnType FlsLoader_lPFUnLockDemo(void)
{
  FlsLoader_ReturnType retval;
  uint32 PfStartAddress1;
  uint32 SectorSize1;
  PfStartAddress1 = FlsLoader_Address;
  SectorSize1 = 1;
  print_f("\n FlsLoader_UnLock Demo start..  \n");
  retval = FlsLoader_UnLock(UCB_PFLASH_ADDR, &PfPassword[0]);
  if(retval == FLSLOADER_E_OK)
  {
    print_f("\n FlsLoader_UnLock Execution Passed \n");
  }
  else if (retval == FLSLOADER_E_BUSY)
  {
    print_f("\n FlsLoader_UnLock  STOPPED, Flash is Busy \n");
  }
  else
  {
    print_f("\n FlsLoader_UnLock Failed \n");
  }
  if(retval == FLSLOADER_E_OK)
  {
    print_f("\n Erasing the Flash where UCB write Protection is disabled\n");
    print_f("\n API should return FLSLOADER_E_OK \n");
    retval = FlsLoader_Erase(PfStartAddress1, SectorSize1);
    if (retval == FLSLOADER_E_OK)
    {
      print_f("\n FlsLoader_Erase returned FLSLOADER_E_OK. expected output\n");
    }
    else if (retval == FLSLOADER_E_LOCKED)
    {
      print_f("\n FlsLoader_Erase returned FLSLOADER_E_LOCKED. Incorrect output\n");
    }
    else
    {
      print_f("\n FlsLoader_Erase execution Failed \n");
    }
  }
  return  retval;
}
#endif /* #if (FLSLOADER_LOCK_UNLOCK_API == STD_ON) */
