/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2019)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : Gpt_Demo.c                                                 **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2019-04-11                                                 **
**                                                                            **
**  VARIANT      : NA                                                         **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Demo application for GPT module                            **
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
#include "IfxScu_reg.h"
#include "IfxSrc_reg.h"
#include "Mcal_Compiler.h"
#include "Test_Print.h"
#include "Gpt.h"
#include "Mcu.h"
#include "Dio.h"
#include "Irq.h"
#include "Gpt_Demo.h"
#include "McalLib.h"

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
#define GPT_START_SEC_CODE_ASIL_B_GLOBAL
#include "Gpt_MemMap.h"

LOCAL_INLINE void Gpt_lStartDemo(void);

#define GPT_STOP_SEC_CODE_ASIL_B_GLOBAL
#include "Gpt_MemMap.h"

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
#define GPT_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
#include "Gpt_MemMap.h"

extern const Gpt_ConfigType Gpt_Config;

#define GPT_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
#include "Gpt_MemMap.h"

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/

volatile uint8 Gpt_ChannelNotif[2];
static uint8 Gpt_DemoCalled;
volatile uint8 Master_core_init_flag = 0;
volatile uint32 Gpt_Channel_0_Notif_count = 0;
volatile uint32 Gpt_Channel_1_Notif_count = 0;
volatile uint8 SlaveCore_InitFlag = 0;
volatile uint8 SlaveCore_DeInitFlag = 0;
/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define GPT_START_SEC_CODE_ASIL_B_GLOBAL
#include "Gpt_MemMap.h"

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : void Gpt_Demo(void)                                       **
**                                                                            **
** Description    : In this routine user options handling is done             **
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
void Gpt_Demo(void)
{
  volatile uint8 LoopVar = 0;
  char InputString[10];

  /* Initialiase interrupt request configurations */
  if( Gpt_DemoCalled == 0U )
  {
	#if (MCU_GTM_USED == STD_ON)
	IrqGtm_Init();
    SRC_GTMATOM00.B.SRE = 1;
	SRC_GTMTOM00.B.SRE = 1;
	#endif
    IrqGpt_Init();
	SRC_GPT120T6.U |= (unsigned_int)(1<<10);
	SRC_GPT120T3.U |= (unsigned_int)(1<<10);
	SRC_GPT120T4.U |= (unsigned_int)(1<<10);
    Gpt_DemoCalled = 1U;
  }

  /* Initialize GPT driver */
  Gpt_Init(&Gpt_Config);

  while (LoopVar == 0)
  {
    print_f("\n");
    print_f("\n < >: ............ GPT DRIVER DEMO MENU ............");
    print_f("\n <1>:  Start continuous timer : LED must start blinking");
    print_f("\n <2>:  Stop timer: LED must stop blinking");
    print_f("\n <.>: Go back to previous menu\n");
    print_f("\nEnter option Number: ");

    getline(InputString, sizeof InputString - 1);

    switch (*InputString)
    {
      case '1':
        Gpt_lStartDemo();
        StartResult();
        print_f("Result = Pass;");
        EndResult();
        break;

      case '2':
        /* Stop the timer, LED blinking stops, remains OFF/ON */
        Gpt_StopTimer(0);
        StartResult();
        print_f("Result = Pass;");
        EndResult();
        break;

      case '.':
        /* De-initialize GPT driver */
        Gpt_DeInit();
        Gpt_Channel_0_Notif_count = 0;				
        LoopVar = 1;
        StartResult();
        print_f("Result = Pass;");
        EndResult();
        break;

      default:
        print_f("\n\n  INVALID OPTION");
        StartResult();
        print_f("Result = Fail;");
        EndResult();
        break;
    }/* End of switch-case */
  }/* End of While loop */
}

#if ( MCAL_NO_OF_CORES > 1U )
void Gpt_Demo_Multi(void)
{
		if(MCAL_MASTER_COREID == Mcal_GetCpuIndex())
		{
		  /* Initialiase interrupt request configurations */
		if( Gpt_DemoCalled == 0U )
		{
		#if (MCU_GTM_USED == STD_ON)
		IrqGtm_Init();
		/* for Channel 1 in core 0 in conitnuous mode TC39x/38x/3EX/37x/36x/337 decvices */
		SRC_GTMTOM00.B.SRE = 1;
		/* for Channel 1 in core 1 in conitnuous mode TC39x/38x/3EX/37x/36x/337 decvices */
		SRC_GTMATOM00.B.SRE = 1;
		#endif
		IrqGpt_Init();
		/* Channel 0 in core 0  GPT12 T6 in conitnuous mode TC35x/TC337 ED ADAS devices */	
		SRC_GPT120T6.U |= (unsigned_int)(1<<10);
		/* Channel 1 in core 1  GPT12 T3,T4 in conitnuous mode TC35x/TC337 ED ADAS devices */
		SRC_GPT120T3.U |= (unsigned_int)(1<<10);
	    SRC_GPT120T4.U |= (unsigned_int)(1<<10);
		
		Gpt_DemoCalled = 1U;
		}
		Gpt_Init(&Gpt_Config); /* GPT initialization  */
		Master_core_init_flag = 0xff;
		print_f("\n CORE0,Core1 Executing,LEDs Blinking continuously for both cores \n");
		while(SlaveCore_InitFlag == 0){} /* To synch both cores to start timer channels */
		Gpt_EnableNotification(0);
		Gpt_StartTimer(0,65535U); /* Tom channel 16 bit max vaule */
		while(Gpt_Channel_0_Notif_count != 0x100) {}
		Gpt_StopTimer(0);
		print_f("\n CORE0 LEDS stop blinking after 128 times \n");
		while(SlaveCore_DeInitFlag == 0) {}
		/* Resetting */
		SlaveCore_DeInitFlag = 0;
		Master_core_init_flag = 0;		
		Gpt_DeInit();
        Gpt_Channel_0_Notif_count = 0;		
		print_f("\n CORE1 LEDS stop blinking after 192 times \n");		
	}
	else
	{
		/* wait for synch up,Core 1 is slave core  */
		while(Master_core_init_flag != 0xff) {}
		Gpt_Init(&Gpt_Config);
		SlaveCore_InitFlag = 1;	
		Gpt_EnableNotification(1);
		#if (MCU_GTM_USED == STD_ON)		
		Gpt_StartTimer(1,(16777215/16)); /* ATOM channel 24 bit max value divide by 16 */
		#else
		Gpt_StartTimer(1,65535); /* GPT12 timer channel  used in TC35x/TC33x ADAS devices */
		#endif
		while(Gpt_Channel_1_Notif_count != 0x180) {}
		Gpt_DisableNotification(1);
		Gpt_StopTimer(1);
		Gpt_DeInit();
		Gpt_Channel_1_Notif_count = 0;
		SlaveCore_DeInitFlag = 1; /* To Deinit master core */
	} 
}
#endif

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : void Gpt_Notification(void)                               **
**                                                                            **
** Description    : GPT channel notification functionality, turns ON/OFF LED  **
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
void IoHwAb_GptNotification0(void)
{
  /* start blinking the LED */
  if( Gpt_ChannelNotif[0] == 0)
  {
    Dio_WriteChannel(DioConf_DioChannel_DioChannel_LED, STD_LOW); /* DIO_CHANNEL_33_5*/
    Gpt_ChannelNotif[0] = 1;
  }
  else
  {
    Dio_WriteChannel(DioConf_DioChannel_DioChannel_LED, STD_HIGH);
    Gpt_ChannelNotif[0] = 0;
  }
  Gpt_Channel_0_Notif_count++;
}

void IoHwAb_GptNotification1(void)
{
  /* start blinking the LED */
  if( Gpt_ChannelNotif[1] == 0)
  {
    Dio_WriteChannel(DioConf_DioChannel_TRB_LED, STD_LOW); /* DIO_CHANNEL_20_11 */
    Gpt_ChannelNotif[1] = 1;
  }
  else
  {
    Dio_WriteChannel(DioConf_DioChannel_TRB_LED, STD_HIGH);
    Gpt_ChannelNotif[1] = 0;
  }
  Gpt_Channel_1_Notif_count++;
}



/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : void Gpt_lStartDemo(void)                                 **
**                                                                            **
** Description    : Enables GPT notification and starts timer with defined    **
**                  time out period                                           **
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
LOCAL_INLINE void Gpt_lStartDemo(void)
{
  /* Enable notification for Timer channel 0 */
  Gpt_EnableNotification(0);
  /* 16 bit max value in GPT12 timer */
  Gpt_StartTimer(0,65535U);  
}

#define GPT_STOP_SEC_CODE_ASIL_B_GLOBAL
#include "Gpt_MemMap.h"
