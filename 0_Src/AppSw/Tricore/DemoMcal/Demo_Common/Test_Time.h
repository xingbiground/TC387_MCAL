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
**  FILENAME  : Test_Time.h                                                   **
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
**  DESCRIPTION  : This file exports functionality of                         **
**                 System Timer Module.                                       **
**  SPECIFICATION(S) :                                                        **
**                                                                            **
**  MAY BE CHANGED BY USER [Yes/No]: Yes                                      **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

#ifndef TEST_TIME_H
#define TEST_TIME_H

#include "DemoApp_Cfg.h"

extern uint32 uwSysFreq;
extern uint32 uwPerFreq;

#define STM_SETALARM_API

#define ALARM_SINGLE_SHOT_MODE                (1U)
#define ALARM_CONTINUOUS_MODE                 (0)

#define ALARM_SRC0                            (0)
#define ALARM_SRC1                            (1U)

extern uint32 Count_Timer[2];

extern void (*TestTime_ArrayFnp[2])(void);

extern uint8 TestTime_AlarmMode;

typedef enum
{
  NS = 0, /* Not Supported */
  MS = 1, /* Millisecond */
  US = 2 /* Micro Seconds */
} Test_TimeUnit;

/* STM Init Function */
extern void Test_InitTime(void);

/* STM Delay Function */
extern void Timer_DelayMs(uint32 ReqTimeMs );
extern void Timer_DelayTicks(uint32 ReqTimeTicks );

#if (IRQ_DEMO_EN == STD_ON)
void Test_IrqStm_Init(void);
#endif

#ifdef STM_SETALARM_API
/* STM Test Function */
extern uint16 Test_Time_SetAlarm(uint8 AlarmId, uint8 AlarmMode, uint32 ReqTimeMs, \
                                 void (*Test_Time_CallFnpp)(void));

/* STM Test Function */
extern uint16 Test_Time_SetAlarmUs(uint8 AlarmId, uint8 AlarmMode, uint32 ReqTimeUs, \
                                   void (*Test_Time_CallFnpp)(void));

/*STM Test Function*/
extern uint16 Test_Time_SetAlarmTicks(uint8 AlarmId, uint8 AlarmMode, uint32 ReqTimeTicks, \
                                      void (*Test_Time_CallFnpp)(void));

/* STM DeInit Function */
extern void Test_Time_DeInitAlarm(uint8 AlarmId);

uint32 Get_Fstm();
uint32 Get_Counter_Value(uint32 reqTime, Test_TimeUnit unitOfReqTime);
uint32 Get_Max_Supported_Time(Test_TimeUnit unitOfReqTime);


#endif

#endif /* End of File Test_Time.h */
