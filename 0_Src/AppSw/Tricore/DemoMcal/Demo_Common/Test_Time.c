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
**  FILENAME  : Test_Time.c                                                   **
**                                                                            **
**  VERSION      : 0.0.1                                                      **
**                                                                            **
**  DATE         : 2016-08-22                                                 **
**                                                                            **
**  VARIANT      : NA                                                         **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : This file contains functionality of                        **
**                 System Timer Module.                                       **
**  SPECIFICATION(S) :                                                        **
**                                                                            **
**  MAY BE CHANGED BY USER [Yes/No]: Yes                                      **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Inclusion of Platform_Types.h and Compiler.h */
#include "Std_Types.h"

/* Inclusion of Tasking sfr file */
#include "IfxScu_reg.h"
#include "IfxStm_reg.h"
#include "IfxSrc_reg.h"

/* Include Mcal_Irq.h to import the library functions */
// #include "Irq.h"
#include "Mcu_Cfg.h"

/* Include Test_Time.h  */
#include "Test_Time.h"

/* Include Test_Print.h to use print_f  */
#include "Test_Print.h"
#include "McalLib.h"
#if (IRQ_DEMO_EN == STD_ON)
#include "Irq.h"
#endif
/*******************************************************************************
**                      Imported Compiler Switch Checks                       **
*******************************************************************************/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
#define MAX_STM_VALUE 0xFFFFFFFF
/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/

#ifdef STM_SETALARM_API
/* API for the Alarm in Msec*/
uint16 Test_Time_SetAlarm(uint8 AlarmId, uint8 AlarmMode, uint32 ReqTimeMs, \
                          void (*Test_Time_CallFnpp)(void));

/* API for the Alarm in Usec*/
uint16 Test_Time_SetAlarmUs(uint8 AlarmId, uint8 AlarmMode, uint32 ReqTimeUs, \
                            void (*Test_Time_CallFnpp)(void));

/* API to DeInit the Alarm */
void Test_DeInitAlarm(void);


/* Arry of 2 Function Pointer for alarm ID 0, Alarm ID 1 */
void (*TestTime_ArrayFnp[2])(void);

#endif

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/


/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/


/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/


/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
#ifdef STM_SETALARM_API
/* Load Value for the Counter Compare register */
uint32 Count_Timer[2];

/*Variable to hold the Mode of alarm ID 0 and 1 at 0  and 1st bit respectively*/
uint8 TestTime_AlarmMode;
#endif

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/


/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/

/* System Frequency Params */
uint32 uwSysFreq;
uint32 uwPerFreq;

/*******************************************************************************
** Syntax           : uint32 Get_Fstm()                                       **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : uint32 - Fstm                                           **
**                                                                            **
** Description      : This function calculates Fstm runtime                   **
**                                                                            **
*******************************************************************************/

uint32 Get_Fstm()
{
  uint32 Fsrc = 0;
  uint32 Fstm = 10;

  uint8 CLKSEL = SCU_CCUCON0.B.CLKSEL;

  if(CLKSEL == 1)
  {
    Fsrc = ((MCU_MAIN_OSC_FREQ * 1000000) * (SCU_SYSPLLCON0.B.NDIV + 1)) / ((SCU_SYSPLLCON0.B.PDIV + 1) * (SCU_SYSPLLCON1.B.K2DIV + 1));
  }
  else
  {
    Fsrc = (MCU_BACKUP_FREQ * 1000000);
  }

  Fstm = Fsrc / (SCU_CCUCON0.B.STMDIV);

  return Fstm;
}

/*******************************************************************************
** Syntax           : void Test_InitTime(void)                                **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : This function Initializes System Timer Module           **
*******************************************************************************/

void Test_InitTime(void)
{
  // Mcal_ResetCpuEndInitProtection();
  // STM0_CLC.U = 0x00000108;
  // Mcal_SetCpuEndInitProtection();

  Mcal_WriteCpuEndInitProtReg((uint32*)&STM0_CLC.U, (uint32)0x00000108);

  uwSysFreq =  Get_Fstm();
  uwPerFreq =  (uwSysFreq / 2);

  STM0_CMP0.U     =  0x00000000U; /* load compare register 0 */
  STM0_CMP1.U     =  0x00000000U; /* load compare register 1 */
  STM0_CMCON.U    =  0x001F001FU; /* load compare match control register */
  STM0_ICR.U      =  0x00000051U; /* load interrupt control register */
}

#ifdef STM_SETALARM_API
/*******************************************************************************
** Syntax        : uint16 Test_Time_SetAlarmTicks(uint8 AlarmId,              **
**     uint8 AlarmMode, uint32 ReqTime, void (*Test_Time_CallFnpp)(void))     **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : reentrant                                               **
**                                                                            **
** Parameters(in)   : AlarmId (0,1) only 2 alarms are possible                **
**                    AlarmMode(0 for Continuous, 1 for SingleShot)           **
**                    ReqTimeMs(time in milli secs)                           **
**                    void (*Test_Time_CallFnpp)(void)) Function pointer      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : This function schedules a function based on the input   **
**                    parameters.The Required Time will be in Ticks           **
*******************************************************************************/


/* API for Scheduling a Task */
uint16 Test_Time_SetAlarmTicks(uint8 AlarmId, uint8 AlarmMode, uint32 ReqTimeTicks, \
                               void (*Test_Time_CallFnpp)(void))
{
  /* Update the Load Valule required in the Array based on the delay */
  Count_Timer[(AlarmId & 0x3U)] = ReqTimeTicks;

  /* Set alarm mode as one shot (1) or contnuous (0) */
  TestTime_AlarmMode = AlarmMode << AlarmId ;

  /*Check for the alarm ID and load corresponding compare register and enble SRN*/
  if( AlarmId == 0 )
  {

    /* store the local function pointer in the global array of function pointer */
    TestTime_ArrayFnp[0] = Test_Time_CallFnpp;
    /* Load the compare register */
    STM0_CMP0.U  =  (Count_Timer[AlarmId] + STM0_TIM0.U) & (0xffffffff);


    SRC_STM0SR0.B.CLRR = 1;
    SRC_STM0SR0.B.SRE = 1; /*  Enable intr */
  }
  else
  {

    /* store the local function pointer in the global array of function pointer   */
    TestTime_ArrayFnp[1] = Test_Time_CallFnpp;

    /* Load the compare register */
    STM0_CMP1.U  =  ( (Count_Timer[AlarmId]) + STM0_TIM0.U) & (0xffffffff);

    SRC_STM0SR1.B.CLRR = 1;
    SRC_STM0SR1.B.SRE = 1; /*  Enable intr */

  }
  return (uint16)E_OK;
}


/*******************************************************************************
** Syntax        : uint16 Test_Time_SetAlarm(uint8 AlarmId, uint8 AlarmMode,  **
**                 uint32 ReqTimeMs, void (*Test_Time_CallFnpp)(void))        **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : reentrant                                               **
**                                                                            **
** Parameters(in)   : AlarmId (0,1) only 2 alarms are possible                **
**                    AlarmMode(0 for Continuous, 1 for SingleShot)           **
**                    ReqTimeMs(time in milli secs)                           **
**                    void (*Test_Time_CallFnpp)(void)) Function pointer      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : This function schedules a function based on the input   **
**                    parameters.The Required time will be in millisec        **
*******************************************************************************/


/* API for Scheduling a Task */
uint16 Test_Time_SetAlarm(uint8 AlarmId, uint8 AlarmMode, uint32 ReqTimeMs, \
                          void (*Test_Time_CallFnpp)(void))
{

  if(ReqTimeMs > Get_Max_Supported_Time(MS))
  {
    /* Above Max value requested */
    return (uint16)E_NOT_OK;
  }
  else
  {
    /* Update the Load Valule required in the Array based on the delay */
    Count_Timer[(AlarmId & 0x3U)] = Get_Counter_Value(ReqTimeMs, MS);
  }


  /* Set alarm mode as one shot (1) or contnuous (0) */
  TestTime_AlarmMode = AlarmMode << AlarmId ;

  /*Check for the alarm ID and load corresponding compare register and enble SRN*/
  if( AlarmId == 0 )
  {

    /* store the local function pointer in the global array of function pointer */
    TestTime_ArrayFnp[0] = Test_Time_CallFnpp;
    /* Load the compare register */
    STM0_CMP0.U  =  (Count_Timer[AlarmId] + STM0_TIM0.U) & (0xffffffff);


    SRC_STM0SR0.B.CLRR = 1;
    SRC_STM0SR0.B.SRE = 1; /*  Enable intr */
  }
  else
  {

    /* store the local function pointer in the global array of function pointer   */
    TestTime_ArrayFnp[1] = Test_Time_CallFnpp;

    /* Load the compare register */
    STM0_CMP1.U  =  ( (Count_Timer[AlarmId]) + STM0_TIM0.U) & (0xffffffff);

    SRC_STM0SR1.B.CLRR = 1;
    SRC_STM0SR1.B.SRE = 1; /*  Enable intr */

  }
  return (uint16)E_OK;
}

/*******************************************************************************
** Syntax           : void Test_DeInitAlarm(void)                             **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : This function De-Initializes System Timer Module        **
*******************************************************************************/

void Test_Time_DeInitAlarm( uint8 AlarmId )
{

  /* if Timer is for AlarmID 0 clear corresponding SRC i.e SRC0 */
  if( AlarmId == 0 )
  {
    SRC_STM0SR0.B.SRE = 0U;
  }

  /* if Timer is for AlarmID 1 clear corresponding SRC i.e SRC1 */
  if( AlarmId == 1 )
  {
    SRC_STM0SR1.B.SRE = 0U;
  }
}

/*******************************************************************************
** Syntax        : uint16 Test_Time_SetAlarmUs(uint8 AlarmId, uint8 AlarmMode,**
**                 uint32 ReqTimeUs, void (*Test_Time_CallFnpp)(void))        **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : reentrant                                               **
**                                                                            **
** Parameters(in)   : AlarmId (0,1) only 2 alarms are possible                **
**                    AlarmMode(0 for Continuous, 1 for SingleShot)           **
**                    ReqTimeUs(time in Micro secs)                           **
**                    void (*Test_Time_CallFnpp)(void)) Function pointer      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : This function schedules a function based on the input   **
**                    parameters                                              **
*******************************************************************************/


/* API for Scheduling a Task */
uint16 Test_Time_SetAlarmUs(uint8 AlarmId, uint8 AlarmMode, uint32 ReqTimeUs, \
                            void (*Test_Time_CallFnpp)(void))
{
  if(ReqTimeUs > Get_Max_Supported_Time(US))
  {
    /* Above Max value requested */
    return (uint16)E_NOT_OK;
  }
  else
  {
    /* Update the Load Valule required in the Array based on the delay */
    Count_Timer[(AlarmId & 0x3U)] = Get_Counter_Value(ReqTimeUs, US);
  }


  /* Set alarm mode as one shot (1) or contnuous (0) */
  TestTime_AlarmMode = AlarmMode << AlarmId ;

  /*Check for the alarm ID and load corresponding compare register and enble SRN*/
  if( AlarmId == 0 )
  {

    /* store the local function pointer in the global array of function pointer */
    TestTime_ArrayFnp[0] = Test_Time_CallFnpp;

    /* Load the compare register */
    STM0_CMP0.U  =  (Count_Timer[AlarmId] + STM0_TIM0.U) & (0xffffffff);


    SRC_STM0SR0.B.CLRR = 1;
    SRC_STM0SR0.B.SRE = 1; /*  Enable intr */
  }
  else
  {

    /* store the local function pointer in the global array of function pointer   */
    TestTime_ArrayFnp[1] = Test_Time_CallFnpp;

    /* Load the compare register */
    STM0_CMP1.U  =  ( (Count_Timer[AlarmId]) + STM0_TIM0.U) & (0xffffffff);

    SRC_STM0SR1.B.CLRR = 1;
    SRC_STM0SR1.B.SRE = 1; /*  Enable intr */

  }
  return (uint16)E_OK;
}

#endif /* #ifdef STM_SETALARM_API */

/*******************************************************************************
** Syntax           : void Timer_DelayMs(uint32 ReqTime)                      **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : This function introduces a delay of ReqTimeMs in        **
**                      milli seconds                                         **
*******************************************************************************/

void Timer_DelayMs(uint32 ReqTimeMs )
{
  volatile uint32 ReadStm;
  uint32 Delay_Count, Delay_Compare_Count;

  Delay_Count = Get_Counter_Value(ReqTimeMs, MS);

  ReadStm = STM0_TIM0.U;
  if((MAX_STM_VALUE - ReadStm) > Delay_Count )
  {
    Delay_Compare_Count = Delay_Count + STM0_TIM0.U;

  }
  else
  {
    Delay_Compare_Count = Delay_Count - (MAX_STM_VALUE - ReadStm);
    /*Waiting till the timer overflows */
    while( Delay_Compare_Count <= ReadStm)
    {
      ReadStm = STM0_TIM0.U;
    }

  }
  while( Delay_Compare_Count >= ReadStm)
  {
    ReadStm = STM0_TIM0.U;
  }


}

/*******************************************************************************
** Syntax           : void Timer_DelayTicks(uint32 ReqTimeTicks)              **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : This function introduces a delay of ReqTimeTicks in     **
**                    STM Timer Ticks                                         **
*******************************************************************************/

void Timer_DelayTicks(uint32 ReqTimeTicks )
{
  volatile uint32 ReadStm;
  uint32 Delay_Compare_Count ;

  Delay_Compare_Count = ReqTimeTicks + STM0_TIM0.U;

  ReadStm = STM0_TIM0.U;

  while( Delay_Compare_Count >= ReadStm)
  {
    ReadStm = STM0_TIM0.U;
  }
}
/*******************************************************************************
** Syntax           : uint32 Get_Counter_Value(uint32 reqTime,Test_TimeUnit   **
**                    unitOfReqTime)                                          **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : uint32 reqTime (Input time)                             **
**                    Test_TimeUnit unitOfReqTime (NS/MS/US)                  **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : uint32 - Fstm                                           **
**                                                                            **
** Description      : This function calculates Fstm runtime                   **
**                                                                            **
*******************************************************************************/
uint32 Get_Counter_Value(uint32 reqTime, Test_TimeUnit unitOfReqTime)
{
  uint32 Fstm = Get_Fstm();
  if(unitOfReqTime == MS)
  {
    return (uint32)((float)(((((float)Fstm / (1000.0))) * (reqTime)) + 0.5));
  }
  else if(unitOfReqTime == US)
  {
    return (uint32)((float)(((((float)Fstm / (1000000.0))) * (reqTime))));
  }
  else
  {
    return (uint32)0;
  }
}
/*******************************************************************************
** Syntax           : uint32 Get_Max_Supported_Time(Test_TimeUnit             **
**                    unitOfReqTime)                                          **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : Test_TimeUnit unitOfReqTime (NS/MS/US)                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : uint32 - Max Supported Time                             **
**                                                                            **
** Description      : This function calculates Fstm runtime                   **
**                                                                            **
*******************************************************************************/
uint32 Get_Max_Supported_Time(Test_TimeUnit unitOfReqTime)
{
  uint32 Fstm = Get_Fstm();
  if(unitOfReqTime == MS)
  {
    return (uint32)((float)4294967295.0 / ((float)Fstm / (1000.0)));
  }
  else if(unitOfReqTime == US)
  {
    return (uint32)((float)4294967295.0 / ((float)Fstm / (1000000.0)));
  }
  else
  {
    return (uint32)0;
  }
}

/*******************************************************************************
** Syntax :  void Test_IrqStm_Init(void)                                      **
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
#if (IRQ_DEMO_EN == STD_ON)
void Test_IrqStm_Init(void)
{
  #if (IRQ_STM0_EXIST == STD_ON)
  IRQ_SFR_MODIFY32 (SRC_STM0SR0.U,  IRQ_CLEAR_MASK, \
                    (IRQ_STM0_SR0_TOS | IRQ_STM0_SR0_PRIO));
  IRQ_SFR_MODIFY32 (SRC_STM0SR1.U,  IRQ_CLEAR_MASK, \
                    (IRQ_STM0_SR1_TOS | IRQ_STM0_SR1_PRIO));
  #endif

  #if (IRQ_STM1_EXIST == STD_ON)
  IRQ_SFR_MODIFY32 (SRC_STM1SR0.U,  IRQ_CLEAR_MASK, \
                    (IRQ_STM1_SR0_TOS | IRQ_STM1_SR0_PRIO));
  IRQ_SFR_MODIFY32 (SRC_STM1SR1.U,  IRQ_CLEAR_MASK, \
                    (IRQ_STM1_SR1_TOS | IRQ_STM1_SR1_PRIO));
  #endif

  #if (IRQ_STM2_EXIST == STD_ON)
  IRQ_SFR_MODIFY32 (SRC_STM2SR0.U,  IRQ_CLEAR_MASK, \
                    (IRQ_STM2_SR0_TOS | IRQ_STM2_SR0_PRIO));
  IRQ_SFR_MODIFY32 (SRC_STM2SR1.U,  IRQ_CLEAR_MASK, \
                    (IRQ_STM2_SR1_TOS | IRQ_STM2_SR1_PRIO));
  #endif

  #if (IRQ_STM3_EXIST == STD_ON)
  IRQ_SFR_MODIFY32 (SRC_STM3SR0.U,  IRQ_CLEAR_MASK, \
                    (IRQ_STM3_SR0_TOS | IRQ_STM3_SR0_PRIO));
  IRQ_SFR_MODIFY32 (SRC_STM3SR1.U,  IRQ_CLEAR_MASK, \
                    (IRQ_STM3_SR1_TOS | IRQ_STM3_SR1_PRIO));
  #endif

  #if (IRQ_STM4_EXIST == STD_ON)
  IRQ_SFR_MODIFY32 (SRC_STM4SR0.U,  IRQ_CLEAR_MASK, \
                    (IRQ_STM4_SR0_TOS | IRQ_STM4_SR0_PRIO));
  IRQ_SFR_MODIFY32 (SRC_STM4SR1.U,  IRQ_CLEAR_MASK, \
                    (IRQ_STM4_SR1_TOS | IRQ_STM4_SR1_PRIO));
  #endif

  #if (IRQ_STM5_EXIST == STD_ON)
  IRQ_SFR_MODIFY32 (SRC_STM5SR0.U,  IRQ_CLEAR_MASK, \
                    (IRQ_STM5_SR0_TOS | IRQ_STM5_SR0_PRIO));
  IRQ_SFR_MODIFY32 (SRC_STM5SR1.U,  IRQ_CLEAR_MASK, \
                    (IRQ_STM5_SR1_TOS | IRQ_STM5_SR1_PRIO));
  #endif

}
#endif
