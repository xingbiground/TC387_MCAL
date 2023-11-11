/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2016)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : Adc_Demo.c                                                  **
**                                                                           **
**  VERSION    : 0.0.1                                                       **
**                                                                           **
**  DATE       : 2016-08-24                                                  **
**                                                                           **
**  VARIANT    : NA                                                          **
**                                                                           **
**  PLATFORM   : Infineon AURIX2G                                            **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION : This file contains                                         **
**                - Demo application for ADC driver                          **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/
/******************************************************************************
**                      Includes                                             **
******************************************************************************/
#include "Std_Types.h"
#include "Adc.h"
#include "Adc_Demo.h"
#include "Test_Print.h"
#include "IfxSrc_reg.h"
#include "Irq.h"
/******************************************************************************
**                      Imported Compiler Switch Check                       **
******************************************************************************/
/******************************************************************************
**                      Private Macro Definitions                            **
******************************************************************************/
#ifndef AdcSWGroup
#define AdcSWGroup      AdcConf_AdcGroup_AdcSWGroup
#endif

#ifndef AdcHWGroup
#define AdcHWGroup      AdcConf_AdcGroup_AdcHWGroup
#endif

#define SRE_ENABLE (1<<10)
/******************************************************************************
**                      Private Type Definitions                             **
******************************************************************************/
/******************************************************************************
**                      Private Function Declarations                        **
******************************************************************************/
void DemoApp_Adc_Init(void);
/******************************************************************************
**                      Global Constant Definitions                          **
******************************************************************************/

/******************************************************************************
**                      Global Variable Definitions                          **
******************************************************************************/
/* Memory Mapping the global variables */

#define ADC_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
#include "Adc_MemMap.h"

/* Result buffer for Adc SW Group */
/* Streaming access result group: 5*2 */
Adc_ValueGroupType ADC_SW_GRP_RES[10];


/* Result buffer for Adc HW Group */
/* Streaming access result group: 5*2 */
Adc_ValueGroupType ADC_HW_GRP_RES[10];


#define ADC_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
#include "Adc_MemMap.h"

#define ADC_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
#include "Adc_MemMap.h"

extern const Adc_ConfigType Adc_Config;

#define  ADC_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
#include "Adc_MemMap.h"
/******************************************************************************
**                      Private Constant Definitions                         **
******************************************************************************/
/******************************************************************************
**                      Private Variable Definitions                         **
******************************************************************************/
static Adc_ValueGroupType *Demo_ResultPtr;
static Adc_StreamNumSampleType Demo_AdcNoSamp;

/******************************************************************************
**                      Global Function Definitions                          **
******************************************************************************/
/******************************************************************************
** Syntax : void Adc_SWGroupDemo(void)                                       **
**                                                                           **
** Service ID:   : NA                                                        **
**                                                                           **
** Sync/Async:   : Synchronous                                               **
**                                                                           **
** Reentrancy:   : Non Reentrant                                             **
**                                                                           **
** Parameters (in): none                                                     **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value    : none                                                    **
**                                                                           **
** Timing         : Fixed Cyclic/Variable Cyclic                             **
**                                                                           **
** Description : This routine will start the SW Group Configured as:         **
**               Conversion mode     : Continuous                            **
**               Result Access mode  : Streaming, Linear                     **
**               Streaming Length    : 5                                     **
**               Channels in a groups: AN1, AN0                              **
**               Result buffer       : ADC_SW_GRP_RES[5][2]                  **
**               Conversion is stopped automatically when once configured    **
**               number of samples are captured                              **
**               Read and print the latest conversion result using pointer   **
**               returned from API Adc_GetStreamLastPointer                  **
******************************************************************************/
void Adc_SWGroupDemo(void)
{
  Adc_StreamNumSampleType AdcSWGroupNoSamples;
  Std_ReturnType AdcBufferSetupStatus;

  /* Initialize ADC interrupt */
  IrqAdc_Init();

  /* Print user information */
  print_f("\nStart ADC0 SW group : AdcSWGroup       \n ");
  print_f("\nConversion mode     : Continuous       \n ");
  print_f("\nResult Access mode  : Streaming, Linear\n ");
  print_f("\nStreaming Length    : 5                \n ");
  print_f("\nChannels in a groups: AN1) - 12bit resolution   \n");
  print_f("                      AN0) - 12bit resolution \n ");
  /*Conversion is stopped automatically when once configured
    n number of samples are captured
    Function will Read and print the latest conversion result
    using pointer returned from API Adc_GetStreamLastPointer
  */
  print_f("\n\n ");

  /* Initialize ADC */
  DemoApp_Adc_Init();

  /* Buffer Marker value */
  ADC_SW_GRP_RES[0] = 0x00C8;

  /* Initialize the Result buffer for AdcSWGroup */
  AdcBufferSetupStatus = Adc_SetupResultBuffer(AdcSWGroup, ADC_SW_GRP_RES);

  if(AdcBufferSetupStatus == E_OK)
  {
    print_f("\nADC_SW_GRP_RES buffer is setup for AdcSWGroup");
    /* Initialize the no of conversted samples to 0 before starting the
       conversion
    */
    Demo_AdcNoSamp = 0;

    /* Initialize the no. of group samples (Streaming length)
       for AdcSWGroup as configured
    */
    AdcSWGroupNoSamples = (Adc_StreamNumSampleType)5;

    /* Start the AdcSWGroup group */
    Adc_StartGroupConversion(AdcSWGroup);


    while(Demo_AdcNoSamp != AdcSWGroupNoSamples)
    {
      /* Get the pointer to last conversion result of Adc Group */
      Demo_AdcNoSamp = Adc_GetStreamLastPointer(AdcSWGroup, &Demo_ResultPtr);
    }

    /* Print the latest converted result of the channels as pointed by
       Demo_ResultPtr
    */
    print_f("\n ADC Conversion Results (Raw Value): \n");
    print_f("AN0) : %4x\n", *(Demo_ResultPtr));
    print_f("AN1) : %4x\n", *(Demo_ResultPtr + AdcSWGroupNoSamples));
    StartResult();
    print_f("Result = Pass;");
    EndResult();

    /* Check if the Group has implictly stopped and status is IDLE
     before Stop request
    */
    if( (Adc_GetGroupStatus(AdcSWGroup)) != ADC_IDLE)
    {
      /* Stop the conversion which will reset the status and result buffer
         and notification is disabled
      */
      Adc_StopGroupConversion(AdcSWGroup);
    }
  }
  else
  {
    print_f("\nError in ADC_SW_GRP_RES buffer setup for AdcSWGroup");
    StartResult();
    print_f("Result = Fail;");
    EndResult();
  }
  Adc_DeInit();
  return;

} /* Adc_SWGroupDemo */


/******************************************************************************
**                      Global Function Definitions                          **
******************************************************************************/
/******************************************************************************
** Syntax : void Adc_HWGroupDemo(void)                                       **
**                                                                           **
** Service ID:   : NA                                                        **
**                                                                           **
** Sync/Async:   : Synchronous                                               **
**                                                                           **
** Reentrancy:   : Non Reentrant                                             **
**                                                                           **
** Parameters (in): none                                                     **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value    : none                                                    **
**                                                                           **
** Timing         : Fixed Cyclic/Variable Cyclic                             **
**                                                                           **
** Description : This routine will start the HW Group Configured as:         **
**               Conversion mode     : OneShot                               **
**               Result Access mode  : Streaming, Linear                     **
**               Streaming Length    : 5                                     **
**               Channels in a groups: AN1, AN0                              **
**               Result buffer       : ADC_HW_GRP_RES[5][2]                  **
**               Conversion is stopped automatically when once configured    **
**               number of samples are captured                              **
**               Read and print the latest conversion result using pointer   **
**               returned from API Adc_GetStreamLastPointer                  **
******************************************************************************/
void Adc_HWGroupDemo(void)
{
  Adc_StreamNumSampleType AdcHWGroupNoSamples;
  Std_ReturnType AdcBufferSetupStatus;

  /* Initialize ADC interrupt */
  IrqAdc_Init();

  /* Print user information */
  print_f("\nStart ADC0 HW group : AdcHWGroup       \n ");
  print_f("\nConversion mode     : OneShot       \n ");
  print_f("\nResult Access mode  : Streaming, Linear\n ");
  print_f("\nStreaming Length    : 5                \n ");
  print_f("\nChannels in a groups: AN1) - 12bit resolution   \n");
  print_f("                        AN0) - 12bit resolution \n ");
  /*Conversion is stopped automatically when once configured
    n number of samples are captured
    Function will Read and print the latest conversion result
    using pointer returned from API Adc_GetStreamLastPointer
  */
  print_f("\n\n ");

  /* Initialize ADC */
  DemoApp_Adc_Init();

  /* Buffer Marker value */
  ADC_HW_GRP_RES[0] = 0x00C8;

  /* Initialize the Result buffer for AdcHWGroup */
  AdcBufferSetupStatus = Adc_SetupResultBuffer(AdcHWGroup, ADC_HW_GRP_RES);

  if(AdcBufferSetupStatus == E_OK)
  {
    print_f("\nADC_HW_GRP_RES buffer is setup for AdcHWGroup");
    /* Initialize the no of conversted samples to 0 before starting the
       conversion
    */
    Demo_AdcNoSamp = 0;

    /* Initialize the no. of group samples (Streaming length)
       for AdcHWGroup as configured
    */
    AdcHWGroupNoSamples = (Adc_StreamNumSampleType)5;

    /* Start the AdcHWGroup group */
    Adc_EnableHardwareTrigger(AdcHWGroup);


    while(Demo_AdcNoSamp != AdcHWGroupNoSamples)
    {
      /* Get the pointer to last conversion result of Adc Group */
      Demo_AdcNoSamp = Adc_GetStreamLastPointer(AdcHWGroup, &Demo_ResultPtr);
    }

    /* Print the latest converted result of the channels as pointed by
       Demo_ResultPtr
    */
    print_f("\n ADC Conversion Results (Raw Value): \n");
    print_f("AN0) : %4x\n", *(Demo_ResultPtr));
    print_f("AN1) : %4x\n", *(Demo_ResultPtr + AdcHWGroupNoSamples));
    StartResult();
    print_f("Result = Pass;");
    EndResult();

    /* Check if the Group has implictly stopped and status is IDLE
     before Stop request
    */
    if( (Adc_GetGroupStatus(AdcHWGroup)) != ADC_IDLE)
    {
      /* Stop the conversion which will reset the status and result buffer
         and notification is disabled
      */
      Adc_DisableHardwareTrigger(AdcHWGroup);
    }
  }
  else
  {
    print_f("\nError in ADC_HW_GRP_RES buffer setup for AdcHWGroup");
    StartResult();
    print_f("Result = Fail;");
    EndResult();
  }
  Adc_DeInit();
  return;

} /* Adc_HWGroupDemo */
/*******************************************************************************
** Syntax : void DemoApp_Adc_Init(void)                                       **
**                                                                            **
** Service ID:   : NA                                                         **
**                                                                            **
** Sync/Async:   : Synchronous                                                **
**                                                                            **
** Reentrancy:   : Reentrant                                                  **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : Initialize ADC module                                        **
*******************************************************************************/
void DemoApp_Adc_Init(void)
{
  SRC_VADCG0SR0.U |= SRE_ENABLE;
  const Adc_ConfigType * ConfigPtr = NULL_PTR;
  ConfigPtr = &Adc_Config;
  Adc_Init(ConfigPtr);
  /* Wait till the StartUp calibration is over */
  while( (Adc_GetStartupCalStatus()) != E_OK)
  {}
}

/*******************************************************************************
** Syntax : void Adc_Demo(void)                                               **
**                                                                            **
** Service ID:   : NA                                                         **
**                                                                            **
** Sync/Async:   : Synchronous                                                **
**                                                                            **
** Reentrancy:   : Non Reentrant                                              **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
** Timing         : Fixed Cyclic/Variable Cyclic                              **
**                                                                            **
** Description : Adc Demo functions are called                                **
*******************************************************************************/
void Adc_Demo(void)
{
  char szString[4U];
  uint8 TempUSage = 0U;

  while (TempUSage != 1U)
  {
    print_f("\n\n\n");
    print_f("\n/******************************************************");
    print_f("*********************/\n");
    print_f("\n                 ADC DRIVER DEMOAPP MENU               \n");
    print_f("                   ENTER YOUR OPTION                     \n");
    print_f("              < 1 >  For ADC SW Group Demo               \n");
    print_f("              < 2 >  For ADC HW Group Demo               \n");
    print_f("              < x >  Back To Main Menu                   \n");
    print_f("\n/******************************************************");
    print_f("*********************/\n");
    print_f("Enter Your Option: ");

    getline(szString, sizeof szString - 1);

    switch (*szString)
    {
      case '1':
        Adc_SWGroupDemo();
        break;

      case '2' :
        Adc_HWGroupDemo();
        break;

      /* Go Back to Main Menu */
      case 'x':
      case 'X':
        TempUSage = 1U;
        break;

      default :
      {
        print_f("\n Invalid Option Choosen \n ");
        break;
      }
    }
  }
}/* Adc_Demo() */
