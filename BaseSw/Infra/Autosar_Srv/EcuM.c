/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2020)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME     : Ecum.c                                                    **
**                                                                           **
**  VERSION      : 3.0.0                                                     **
**                                                                           **
**  DATE         : 2020-08-05                                                **
**                                                                           **
**  VARIANT      : Variant PB                                                **
**                                                                           **
**  PLATFORM     : Infineon AURIX2G                                          **
**                                                                           **
**  AUTHOR       : DL-AUTOSAR-Engineering                                    **
**                                                                           **
**  VENDOR       : Infineon Technologies                                     **
**                                                                           **
**  DESCRIPTION  : Contains a simple example of ECU State Manager Code       **
**                 This file is for Evaluation Purpose Only                  **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
#define TEST_CAN_MODULE_ID        (80U)  /* 0x50 */
#define TEST_CANTRCV_MODULE_ID    (70U)  /* 0x46 */
#define TEST_FR_MODULE_ID         (81U)  /* 0x51 */
#define TEST_LIN_MODULE_ID        (82U)  /* 0x52 */
#define TEST_GPT_MODULE_ID        (100U) /* 0x64 */

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Std_Types.h"
#include "Platform_Types.h"
#include "Mcal_Version.h"
#if (MCAL_AR_VERSION == MCAL_AR_422)
#include "EcuM_Cbk.h"
#else
#include "EcuM.h"
#endif
#include "IFX_Os.h"

#ifdef BASE_TEST_MODULE_ID
#if ((BASE_TEST_MODULE_ID == TEST_CAN_MODULE_ID)|| (BASE_TEST_MODULE_ID== TEST_CANTRCV_MODULE_ID))
#include "ComStack_Types.h"
#include "CanIf.h"
#endif
#if (BASE_TEST_MODULE_ID == TEST_LIN_MODULE_ID)
#include "ComStack_Types.h"
#include "LinIf.h"
#endif
#if(BASE_TEST_MODULE_ID == TEST_GPT_MODULE_ID)
#include "Gpt.h"
#endif
#endif /* #ifdef BASE_TEST_MODULE_ID */

/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
volatile uint32 EcuM_SetWakeupEventVariable;
volatile uint32 EcuM_CheckWakeupVariable;

#ifdef BASE_TEST_MODULE_ID
#if(BASE_TEST_MODULE_ID == TEST_GPT_MODULE_ID)
/* Array to hold info about wakeup events */
extern volatile uint8 Gpt_WakeupEvent[];

extern volatile uint8 EcuMSetWakeupEventCalled ;

/* Check if wakeup happened due to GPT */
extern volatile uint8 Gpt_WakeUpFlag;
/* Check if wakeup happened due to STM */
extern volatile uint8 Stm_WakeUpFlag;
#endif

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
#if ((BASE_TEST_MODULE_ID == TEST_CAN_MODULE_ID)|| (BASE_TEST_MODULE_ID== TEST_CANTRCV_MODULE_ID))
extern void EcumTest_SetWakeupEvent(EcuM_WakeupSourceType WakeupInfo);
#endif
#if (BASE_TEST_MODULE_ID == TEST_LIN_MODULE_ID)
extern void EcumLinTest_SetWakeupEvent(EcuM_WakeupSourceType WakeupInfo);
#endif
#endif /* #ifdef BASE_TEST_MODULE_ID */
/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Functon Definitions                            **
*******************************************************************************/

/*******************************************************************************
** Syntax           : void EcuM_Init(const EcuM_ConfigType *configptr)        **
**                                                                            **
** Service ID       : None/<Specified>                                        **
**                                                                            **
** Sync/Async       : Synchronous / Asynchronous                              **
**                                                                            **
** Reentrancy       : Non-reentrant / Reentrant                               **
**                                                                            **
** Parameters(in)   : None/<Specified>                                        **
**                                                                            **
** Parameters (out) : None/<Specified>                                        **
**                                                                            **
** Return value     : None/<Specified>                                        **
**                                                                            **
** Description      : <Suitable Description>                                  **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
** Syntax           : void EcuM_SetWakeupEvent(EcuM_WakeupSourceType events)  **
**                                                                            **
** Service ID       : None/<Specified>                                        **
**                                                                            **
** Sync/Async       : Synchronous / Asynchronous                              **
**                                                                            **
** Reentrancy       : Non-reentrant / Reentrant                               **
**                                                                            **
** Parameters(in)   : None/<Specified>                                        **
**                                                                            **
** Parameters (out) : None/<Specified>                                        **
**                                                                            **
** Return value     : None/<Specified>                                        **
**                                                                            **
** Description      : <Suitable Description>                                  **
**                                                                            **
*******************************************************************************/
void EcuM_SetWakeupEvent(EcuM_WakeupSourceType WakeupInfo)
{
  SuspendAllInterrupts();
  EcuM_SetWakeupEventVariable++;
  ResumeAllInterrupts();

  #ifdef BASE_TEST_MODULE_ID
  #if(BASE_TEST_MODULE_ID == TEST_GPT_MODULE_ID)
  /* Used by WakeUp only */
  uint32 WakeupInfoGpt = 0;
  uint32 Cnt = 1;

  EcuMSetWakeupEventCalled = 1 ;

  /* The following code is specific to GPT Testing */
  if(WakeupInfo == 0x80000000 )
  {
    Stm_WakeUpFlag = 1U;
  }
  else
  {
    /* Assumption: WakeupInfo = ChannelID ==> In configuration */
    Gpt_WakeUpFlag = 1U;
    while(Cnt != WakeupInfo)
    {
      Cnt *= 2;
      WakeupInfoGpt++;

    }
    Gpt_WakeupEvent[WakeupInfoGpt] = 1U;

  }

  #if(GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
  Gpt_SetMode(GPT_MODE_NORMAL);
  #endif

  #endif /* #if(BASE_TEST_MODULE_ID == TEST_GPT_MODULE_ID) */

  #if ((BASE_TEST_MODULE_ID == TEST_CAN_MODULE_ID)|| (BASE_TEST_MODULE_ID== TEST_CANTRCV_MODULE_ID))
  EcumTest_SetWakeupEvent(WakeupInfo);
  #endif

  #if (BASE_TEST_MODULE_ID == TEST_LIN_MODULE_ID)
  EcumLinTest_SetWakeupEvent(WakeupInfo);
  #endif

  #endif /* #ifdef BASE_TEST_MODULE_ID */
}

/*******************************************************************************
** Syntax           : void EcuM_ValidateWakeupEvent                           **
**                    (EcuM_WakeupSourceType events)                          **
**                                                                            **
** Service ID       : None/<Specified>                                        **
**                                                                            **
** Sync/Async       : Synchronous / Asynchronous                              **
**                                                                            **
** Reentrancy       : Non-reentrant / Reentrant                               **
**                                                                            **
** Parameters(in)   : None/<Specified>                                        **
**                                                                            **
** Parameters (out) : None/<Specified>                                        **
**                                                                            **
** Return value     : None/<Specified>                                        **
**                                                                            **
** Description      : <Suitable Description>                                  **
**                                                                            **
*******************************************************************************/
void EcuM_ValidateWakeupEvent(EcuM_WakeupSourceType events)
{

}

/*******************************************************************************
** Syntax           : void EcuM_CheckWakeup                                   **
**                    (EcuM_WakeupSourceType wakeupSource)                    **
**                                                                            **
** Service ID       : None/<Specified>                                        **
**                                                                            **
** Sync/Async       : Synchronous / Asynchronous                              **
**                                                                            **
** Reentrancy       : Non-reentrant / Reentrant                               **
**                                                                            **
** Parameters(in)   : wakeupSource                                            **
**                                                                            **
** Parameters (out) : None/<Specified>                                        **
**                                                                            **
** Return value     : None/<Specified>                                        **
**                                                                            **
** Description      : <Suitable Description>                                  **
**                                                                            **
*******************************************************************************/
void EcuM_CheckWakeup(EcuM_WakeupSourceType wakeupSource)
{
  EcuM_CheckWakeupVariable++;

  #ifdef BASE_TEST_MODULE_ID
  #if(BASE_TEST_MODULE_ID == TEST_GPT_MODULE_ID)
  #if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)	  
  Gpt_CheckWakeup(wakeupSource);
  #endif
  #endif

  #if ((BASE_TEST_MODULE_ID == TEST_CAN_MODULE_ID) ||(BASE_TEST_MODULE_ID == TEST_CANTRCV_MODULE_ID))
  CanIf_CheckWakeup(wakeupSource);
  #endif

  #if (BASE_TEST_MODULE_ID == TEST_LIN_MODULE_ID)
  LinIf_CheckWakeup(wakeupSource);
  #endif

  #endif /* #ifdef BASE_TEST_MODULE_ID */
}
