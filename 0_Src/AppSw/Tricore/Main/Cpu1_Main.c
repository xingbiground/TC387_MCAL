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
**  FILENAME     : Cpu1_Main.c                                                **
**                                                                            **
**  VERSION      : 0.0.2                                                      **
**                                                                            **
**  DATE         : 2016-08-17                                                 **
**                                                                            **
**  VARIANT      : NA                                                         **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Example Cpu1 Main startup file                             **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/

#include "Mcal_Compiler.h"
#include "Ifx_Ssw_Infra.h"
#include "IFX_Os.h"
#ifdef AURIX2G_MCAL_DEMOAPP
#include "DemoApp.h"
#include "McalLib.h"
#endif

#if ( MCAL_NO_OF_CORES > 1U )
#ifdef AURIX2G_MCAL_DEMOAPP
#ifdef _TASKING_C_TRICORE_
#pragma section farbss "ClearedData.LmuNC.32bit"
#pragma align 4
#elif defined _GNU_C_TRICORE_
#pragma section "ClearedData.LmuNC.32bit" aw 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section bss = ".ClearedData.LmuNC.32bit"
#elif defined _DIABDATA_C_TRICORE_
#pragma section DATA "InitData.LmuNC.32bit" "ClearedData.LmuNC.32bit" far-absolute RW
#endif
extern volatile uint32 MulticoreDemoEnable;
extern volatile uint32 Test_Demo_Sync;
extern volatile uint32 Demo_sync_all_cores;
extern volatile char szString[80];
#ifdef _TASKING_C_TRICORE_
#pragma align restore
#pragma section farbss restore
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma section
#endif
#endif
#endif

void core1_main (void)
{
  volatile unsigned short LoopFlag = 1U;
  unsigned short cpuWdtPassword;
  #if ((defined IFX_CFG_SSW_ENABLE_TRICORE0) && (IFX_CFG_SSW_ENABLE_TRICORE0 == 0))
  unsigned short safetyWdtPassword;
  #endif
  ENABLE();
  /*
   * !!WATCHDOG1 IS DISABLED HERE!!
   * Enable the watchdog in the demo if it is required and also service the watchdog periodically
   * */

  #if ((defined IFX_CFG_SSW_ENABLE_TRICORE0) && (IFX_CFG_SSW_ENABLE_TRICORE0 == 0))
  safetyWdtPassword = Ifx_Ssw_getSafetyWatchdogPassword();
  Ifx_Ssw_disableSafetyWatchdog(safetyWdtPassword);
  #endif

  cpuWdtPassword = Ifx_Ssw_getCpuWatchdogPassword(&MODULE_SCU.WDTCPU[1]);
  Ifx_Ssw_disableCpuWatchdog(&MODULE_SCU.WDTCPU[1], cpuWdtPassword);

  while (LoopFlag == 1U)
  {
	  #ifdef AURIX2G_MCAL_DEMOAPP 
	  #if ( MCAL_NO_OF_CORES > 1U )
      if(MulticoreDemoEnable==MULTICORE_DEMO_ENABLE_VALUE)
      {
          /* sync between cores has to be performed */
        Mcal_GetSpinlock(&Test_Demo_Sync, DEMO_CPU_SPINLOCK_TIMEOUT);
	    Demo_sync_all_cores = (Demo_sync_all_cores | 0x2U) ;
	    Mcal_ReleaseSpinlock(&Test_Demo_Sync);
	    while (Demo_sync_all_cores != 0x3U)
	    {}
        DemoApp_CallMenuFct((char*)szString);
	    Demo_sync_all_cores = 0;        
      }
	  #endif
	  #endif

  }

}
