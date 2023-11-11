/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2019)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME    : Icu_17_TimerIp_Demo.c                                      **
**                                                                           **
**  VERSION     : 1.0.0                                                      **
**                                                                           **
**  DATE        : 2019-04-11                                                 **
**                                                                           **
**  VARIANT     : NA                                                         **
**                                                                           **
**  PLATFORM    : Infineon AURIX2G                                           **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION : This file contains                                         **
**                - Demo application for ICU module                          **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: yes                                     **
**                                                                           **
******************************************************************************/

/******************************************************************************
**                      Includes                                             **
******************************************************************************/
#include "Std_Types.h"
#include "Icu_17_TimerIp.h"
#include "Icu_17_TimerIp_Demo.h"
#include "Test_Print.h"
#include "Irq.h"
#include "IfxSrc_reg.h"
#include "Test_Time.h"

/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/
/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
#define ICU_17_TIMERIP_START_SEC_CODE_ASIL_B_GLOBAL
#include "Icu_17_TimerIp_MemMap.h"

extern void Timer_DelayTicks(uint32 ReqTimeTicks );

#define ICU_17_TIMERIP_STOP_SEC_CODE_ASIL_B_GLOBAL
#include "Icu_17_TimerIp_MemMap.h"
/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
#define ICU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
#include "Icu_17_TimerIp_MemMap.h"
extern const Icu_17_TimerIp_ConfigType Icu_17_TimerIp_Config;
#define ICU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
#include "Icu_17_TimerIp_MemMap.h"

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
/* Icu Duty Cycle Variable */

#define ICU_17_TIMERIP_START_SEC_VAR_CLEARED_ASIL_B_CORE0_32
#include "Icu_17_TimerIp_MemMap.h"

Icu_17_TimerIp_DutyCycleType DutyCycle_Values1;

#define ICU_17_TIMERIP_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_32
#include "Icu_17_TimerIp_MemMap.h"

#define ICU_17_TIMERIP_START_SEC_VAR_CLEARED_ASIL_B_CORE0_32
#include "Icu_17_TimerIp_MemMap.h"

uint32 IcuKeep;

#define ICU_17_TIMERIP_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_32
#include "Icu_17_TimerIp_MemMap.h"

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/
/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define ICU_17_TIMERIP_START_SEC_CODE_ASIL_B_GLOBAL
#include "Icu_17_TimerIp_MemMap.h"
/*******************************************************************************
** Syntax : void Icu_17_TimerIp_Demo_Init(void)                               **
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
** Description : Initialise Icu module to for demo app                        **
*******************************************************************************/
void Icu_17_TimerIp_Demo_Init(void)
{
  /* enable interrupt system */
  IrqCcu6_Init();
  IrqScu_Init();
  SRC_CCU61SR0.U |= (unsigned_int)(1 << 10);
  #if ((defined MCU_GTM_USED) && (MCU_GTM_USED == STD_ON))   
  IrqGtm_Init();
  #endif

  /* initialize ICU configuration */
  Icu_17_TimerIp_Init(&Icu_17_TimerIp_Config);
}

/*******************************************************************************
** Syntax : void Icu_17_TimerIp_Demo(void)                                    **
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
** Description :Read out the PWM Duty Cycle and Period.The PWM must be        **
** generated using the PWM Demo befor using this ICU Demo.                    **
**                                                                            **
*******************************************************************************/
void Icu_17_TimerIp_Demo(void)
{
  uint32 DutyCycle;  

  /* check with variable IcuKeep to avoid calling multiple times */
  if (IcuKeep == 0U)
  {
    /* initialize ICU and ... */
    Icu_17_TimerIp_Demo_Init();
    /* ... start signal measurement */
    Icu_17_TimerIp_StartSignalMeasurement(IcuConf_IcuChannel_SignalMeas);

    /* these functions not be called again */
    IcuKeep++;
  }
  
  /*Delay to allow at least one complete cycle of input signal to be captured */
  Timer_DelayMs(5);


  /* invoke API to read the captured duty cycle values */
  Icu_17_TimerIp_GetDutyCycleValues(  IcuConf_IcuChannel_SignalMeas,
                                      &DutyCycle_Values1);

  /* calculate duty cycle */
  DutyCycle = (uint32)(   (DutyCycle_Values1.ActiveTime * 200U) \
                          + (DutyCycle_Values1.PeriodTime)        \
                      ) / (uint32)(2U * DutyCycle_Values1.PeriodTime);

  /* avoid priting negative values */
  if(DutyCycle == (uint32)(-1))
  {
    DutyCycle = 0U;
  }

  /* print caculated values */
  print_f("\n");
  print_f("High Time = %x\tPeriod = %x\tDuty Cycle = %d \n",
          DutyCycle_Values1.ActiveTime,
          DutyCycle_Values1.PeriodTime,
          DutyCycle);

  /* print note in case 0 was output */
  if(0U == DutyCycle)
  {
    print_f("duty cycle ZERO is output when capture is ongoing and not finished \n");

    StartResult();
    print_f("Result = Fail;");
    EndResult();
  }
  else
  {
    StartResult();
    print_f("Result = Pass;");
    EndResult();
  }

} /* Icu_17_TimerIp_Demo */
#define ICU_17_TIMERIP_STOP_SEC_CODE_ASIL_B_GLOBAL
#include "Icu_17_TimerIp_MemMap.h"
