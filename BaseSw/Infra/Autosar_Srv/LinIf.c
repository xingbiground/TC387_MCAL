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
**  FILENAME   : LinIf.c                                                      **
**                                                                            **
**  VERSION    : 9.0.0                                                        **
**                                                                            **
**  DATE       : 2021-11-09                                                   **
**                                                                            **
**  VARIANT    : NA                                                           **
**                                                                            **
**  PLATFORM   : Infineon AURIX2G                                             **
**                                                                            **
**  AUTHOR      : DL-AUTOSAR-Engineering                                      **
**                                                                            **
**  VENDOR      : Infineon Technologies                                       **
**                                                                            **
**  DESCRIPTION : This file contains LIN Interface (LinIf) function           **
**                definitions                                                 **
**                Note : This file is for Evaluation Purpose Only             **
**                                                                            **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                      **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Inclusion of LinIf module header file  */
#include "LinIf.h"
#include "McalLib.h"

/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
#define TEST_LIN_MODULE_ID               (82U)
#define LINIF_TEST_ZERO_U                (0U)
#define LINIF_TEST_ONE_U                 (1U)
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
#ifdef  APP_SW
#if((APP_SW == TEST_APP)&&(BASE_TEST_MODULE_ID == TEST_LIN_MODULE_ID))
extern Std_ReturnType u8g_LinTest_CheckWakeupRes[];
#endif
#endif
/*******************************************************************************
**                      Global Function Declarations                         **
*******************************************************************************/
#ifdef  APP_SW
#if((APP_SW == TEST_APP)&&(BASE_TEST_MODULE_ID == TEST_LIN_MODULE_ID))
#if (MCAL_AR_VERSION == MCAL_AR_440)
extern void LinIfTest_WakeupConfirmation(EcuM_WakeupSourceType WakeupSource);

extern Std_ReturnType LinIfTest_HeaderIndication(NetworkHandleType Channel, Lin_PduType* PduPtr);

extern void LinIfTest_TxConfirmation(NetworkHandleType Channel);

extern void LinIfTest_LinErrorIndication(NetworkHandleType Channel, Lin_SlaveErrorType ErrorStatus);

extern void LinIfTest_RxIndication(NetworkHandleType Channel, uint8* Lin_SduPtr);
#endif
#endif
#endif
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
** Syntax : void LinIf_CheckWakeup( EcuM_WakeupSourceType WakeupSource)       **
**                                                                            **
** Service ID: none                                                           **
**                                                                            **
** Sync/Async:  none                                                          **
**                                                                            **
** Reentrancy:  none                                                          **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out):  none                                                    **
**                                                                            **
** Return value:  none                                                        **
**                                                                            **
** Description : This function is called by EcuM_CheckWakeup when the EcuM    **
**           has been notified about a wakeup event on a specific LIN channel.**
**                                                                            **
*******************************************************************************/
void LinIf_CheckWakeup( EcuM_WakeupSourceType WakeupSource)
{
  uint8 u8l_ChIdx = LINIF_TEST_ZERO_U;
  uint8 CoreId;
  #ifdef  APP_SW
  #if((APP_SW == TEST_APP)&&(BASE_TEST_MODULE_ID == TEST_LIN_MODULE_ID))
  uint8 LogChanId = LINIF_TEST_ZERO_U;
  #endif
  #endif

  #if (defined VARIATION_POINT_TEST) && (VARIATION_POINT_TEST == LINIF_TEST_ONE_U)
  static const Lin_17_AscLin_ConfigType* Lin_kConfigPtr = &Lin_17_AscLin_Config_Diesel;
  #else
  static const Lin_17_AscLin_ConfigType* Lin_kConfigPtr = &Lin_17_AscLin_Config;
  #endif

  volatile uint8 u8l_WakeupSrcChId = LINIF_TEST_ZERO_U;

  CoreId =(uint8)Mcal_GetCpuIndex();

  while((WakeupSource ^ (LINIF_TEST_ONE_U << u8l_WakeupSrcChId)) != LINIF_TEST_ZERO_U)
  {
    u8l_WakeupSrcChId++;
  }
  while((Lin_kConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[u8l_ChIdx].WakeupSourceId != u8l_WakeupSrcChId)&&
          (u8l_ChIdx != (Lin_kConfigPtr->CoreConfigPtr[CoreId]->MaxCoreChannels - LINIF_TEST_ONE_U)))
  {
      u8l_ChIdx++;
  }
  #ifdef  APP_SW
  #if((APP_SW == TEST_APP)&&(BASE_TEST_MODULE_ID == TEST_LIN_MODULE_ID))
  LogChanId = Lin_kConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[u8l_ChIdx].LogicalId;
  u8g_LinTest_CheckWakeupRes[CoreId] = Lin_17_AscLin_CheckWakeup(LogChanId);
  #endif
  #endif
}
#if (MCAL_AR_VERSION == MCAL_AR_440)
/*******************************************************************************
** Syntax : void LinIf_WakeupConfirmation( EcuM_WakeupSourceType WakeupSource)**
**                                                                            **
** Service ID: none                                                           **
**                                                                            **
** Sync/Async:  none                                                          **
**                                                                            **
** Reentrancy:  none                                                          **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out):  none                                                    **
**                                                                            **
** Return value:  none                                                        **
**                                                                            **
** Description : This function is called in LIN Driver or                     **
**               LIN Transceiver Driver.                                      **
**                                                                            **
*******************************************************************************/
void LinIf_WakeupConfirmation(EcuM_WakeupSourceType WakeupSource)
{
  #ifdef  APP_SW
  #if((APP_SW == TEST_APP)&&(BASE_TEST_MODULE_ID == TEST_LIN_MODULE_ID))
  LinIfTest_WakeupConfirmation(WakeupSource);
  #endif
  #endif
}
/*******************************************************************************
** Syntax : Std_ReturnType LinIf_HeaderIndication(NetworkHandleType Channel,  **
**                                               Lin_PduType* PduPtr)         **
** Service ID: none                                                           **
**                                                                            **
** Sync/Async:  none                                                          **
**                                                                            **
** Reentrancy:  none                                                          **
**                                                                            **
** Parameters (in): Channel                                                   **
**                                                                            **
** Parameters (inout):  PduPtr                                                **
**                                                                            **
** Return value:  none                                                        **
**                                                                            **
** Description : This function is called in LIN Driver or                     **
**               LIN Transceiver Driver.                                      **
**                                                                            **
*******************************************************************************/

Std_ReturnType LinIf_HeaderIndication(NetworkHandleType Channel, Lin_PduType*
PduPtr)
{
  Std_ReturnType u8l_LinTest_HeaderRetVal = E_NOT_OK;
  #ifdef  APP_SW
  #if((APP_SW == TEST_APP)&&(BASE_TEST_MODULE_ID == TEST_LIN_MODULE_ID))
  u8l_LinTest_HeaderRetVal = LinIfTest_HeaderIndication(Channel, PduPtr);
  #endif
  #endif
  return u8l_LinTest_HeaderRetVal;
}
/*******************************************************************************
** Syntax :  void LinIf_TxConfirmation( NetworkHandleType Channel)            **
** Service ID: none                                                           **
**                                                                            **
** Sync/Async:  none                                                          **
**                                                                            **
** Reentrancy:  none                                                          **
**                                                                            **
** Parameters (in): Channel                                                   **
**                                                                            **
** Parameters (inout):  none                                                  **
**                                                                            **
** Return value:  none                                                        **
**                                                                            **
** Description : This function is called in LIN Driver or                     **
**               LIN Transceiver Driver.                                      **
**                                                                            **
*******************************************************************************/
void LinIf_TxConfirmation( NetworkHandleType Channel )
{
  #ifdef  APP_SW
  #if((APP_SW == TEST_APP)&&(BASE_TEST_MODULE_ID == TEST_LIN_MODULE_ID))
   LinIfTest_TxConfirmation(Channel);
  #endif
  #endif
}
/*******************************************************************************
** Syntax:void LinIf_RxIndication(NetworkHandleType Channel,uint8* Lin_SduPtr)**
** Service ID: none                                                           **
**                                                                            **
** Sync/Async:  none                                                          **
**                                                                            **
** Reentrancy:  none                                                          **
**                                                                            **
** Parameters (in): Channel                                                   **
**                : Lin_SduPtr                                                **
** Parameters (out):  none                                                    **
**                                                                            **
** Return value:  none                                                        **
**                                                                            **
** Description : This function is called in LIN Driver or                     **
**               LIN Transceiver Driver.                                      **
**                                                                            **
*******************************************************************************/
void LinIf_RxIndication( NetworkHandleType Channel, uint8* Lin_SduPtr )
{
  #ifdef  APP_SW
  #if((APP_SW == TEST_APP)&&(BASE_TEST_MODULE_ID == TEST_LIN_MODULE_ID))
   LinIfTest_RxIndication(Channel, Lin_SduPtr);
  #endif
  #endif
}
/*******************************************************************************
** Syntax :void LinIf_LinErrorIndication( NetworkHandleType Channel           **
**                                       Lin_SlaveErrorType ErrorStatus )     **
** Service ID: none                                                           **
**                                                                            **
** Sync/Async:  none                                                          **
**                                                                            **
** Reentrancy:  none                                                          **
**                                                                            **
** Parameters (in): Channel                                                   **
**                : Lin_SduPtr                                                **
** Parameters (out):  none                                                    **
**                                                                            **
** Return value:  none                                                        **
**                                                                            **
** Description : This function is called in LIN Driver or                     **
**               LIN Transceiver Driver.                                      **
**                                                                            **
*******************************************************************************/
void LinIf_LinErrorIndication(NetworkHandleType Channel, Lin_SlaveErrorType
ErrorStatus)
{
  #ifdef  APP_SW
  #if((APP_SW == TEST_APP)&&(BASE_TEST_MODULE_ID == TEST_LIN_MODULE_ID))
  LinIfTest_LinErrorIndication(Channel, ErrorStatus);
  #endif
  #endif
}
#endif
/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
