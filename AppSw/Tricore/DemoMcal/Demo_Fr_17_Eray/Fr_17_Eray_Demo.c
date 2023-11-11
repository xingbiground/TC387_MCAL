/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2013)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  $FILENAME   : Fr_17_Eray_Demo.c $                                         **
**                                                                            **
**  $CC VERSION : \main\30 $                                                  **
**                                                                            **
**  $DATE       : 2020-08-11 $                                                **
**                                                                            **
**  AUTHOR      : DL-AUTOSAR-Engineering                                      **
**                                                                            **
**  VENDOR      : Infineon Technologies                                       **
**                                                                            **
**  DESCRIPTION : This file contains function prototypes for demo             **
**                   application for FlexRay driver                           **
**                                                                            **
**  MAY BE CHANGED BY USER [yes/no]: yes                                      **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Std_Types.h"
#include "IfxEray_reg.h"
#include "IfxEray_bf.h"
#include "IfxSrc_reg.h"
#include "IfxScu_reg.h"
#include "IfxCpu_reg.h"
#include "Fr_17_Eray_Demo.h"
#include "Fr_17_Eray.h"
#include "Port.h"
#include "Test_Print.h"
#include "Test_Time.h"
#include "McalLib.h"

/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
/* Number of times different data is transmitted using an LPDU */
#define FR_17_ERAY_DATA_COUNT       (2U)

/* Data modification factor for next tranmission by an LPDU */
#define FR_17_ERAY_DATA_INCREMENT   (1U)

/* Initial data pattern used by first transmission by node 0 */
#define FR_17_ERAY_INITIAL_DATA     (0x10U)

#define FR_17_ERAY_POCS_NORMAL_ACTIVE   ((uint8)0x02)

#define FR_17_ERAY_POCS_NORMAL_PASSIVE  ((uint8)0x03)

#define FR_BEGIN_LPDU_RECONFIGURATION  ((uint8)18)
#define FR_BEGIN_LPDU_DISABLING_CANCELLATION  ((uint8)19)

#define FR_17_ERAY_LPDU7_INDX        ((uint8)0x07)

#define FR_NON_RECONFIG_LPDU_COUNT   ((uint8)0x04)

#define FR_TX_LPDU_HEADER_CRC_VAL    ((uint16)1750)

#define FR_RECONFIGURED_FRAME_ID     ((uint8)6)

#define FR_TX_CYCLE_REP_COUNT  ((uint8)4)
#define FR_TX_BASE_CYCLE       ((uint8)2)

#define FR_RX_CYCLE_REP_COUNT  ((uint8)8)
#define FR_RX_BASE_CYCLE       ((uint8)4)

#define FR_SAFETY_ENDINT_TIMEOUT ((uint32)150000U)

/* Macro to check if communication controller is synchronised to global time */
#define Fr_17_Eray_DemoIsCcInSync()    \
      ( (ERAY0_CCSV.B.POCS == FR_17_ERAY_POCS_NORMAL_ACTIVE) || \
        (ERAY0_CCSV.B.POCS == FR_17_ERAY_POCS_NORMAL_PASSIVE) )

#define CPU_PSW_USER_MODE_MASK (0xFFFFF3FFU)
#define SET_USER_MODE_MASK ((1U  <<  10U))

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
#define FR_17_ERAY_START_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
#include "Fr_17_Eray_MemMap.h"

extern const Fr_17_Eray_ConfigType Fr_17_Eray_Config;

#define FR_17_ERAY_STOP_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
#include "Fr_17_Eray_MemMap.h"
/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
#define FR_17_ERAY_START_SEC_VAR_CLEARED_QM_LOCAL_32
#include "Fr_17_Eray_MemMap.h"

/* Transmit buffer : Used by node 0 to transmit */
static uint8 FrDemo_TxDataBuffer[254] ;

/*
  Recieve buffer  : Used by node 0 to temporarily store data received
  from node 1
*/
static uint8 FrDemo_RxDataBuffer[254] ;

/*
  Storage for data multiple receptions. Needed for validation of received data
*/
static uint8 FrDemo_RxData[FR_17_ERAY_DATA_COUNT][254];
/*
  Storage for NM vector w.r.t multiple receptions. Needed for validation of
  received data
*/
static uint32 FrDemo_NmVectorPtr[FR_17_ERAY_DATA_COUNT];

#define FR_17_ERAY_STOP_SEC_VAR_CLEARED_QM_LOCAL_32
#include "Fr_17_Eray_MemMap.h"

void FrDemo_PrepareTxData(uint8 *SrcPtr, uint8 *DstPtr, uint8 DataLength);
void FrDemo_CopyReceivedData(uint8 *SrcPtr, uint8 *DstPtr, uint8 DataLength);
uint32 FrDemo_VerifyData(uint8 *DataPtr, uint8 DataLength,
                         uint16 RxDataIndex, uint8 InitialData);
void FrDemo_InitializeBuffer(uint8 *BufferPtr, uint8 DataLength, uint8 Data);
void FrDemo_PrintData(uint8 *BufferPtr, uint8 DataLength);
void FrDemo_PrintArray(uint16 *BufferPtr, uint8 DataLength);

#if(MCAL_AR_VERSION == MCAL_AR_440)
Fr_SlotAssignmentType Fr_Tx_SlotAssignment;
Fr_SlotAssignmentType Fr_Rx_SlotAssignment;
Fr_SlotAssignmentType Fr_Tx_Check_SlotAssignment;
#endif
/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
uint32 FrDemo_ClusterStartup(void);
uint32 FrDemo_TxRxTest(uint16 TxLPduIdx, uint8 TxLSduLength,
                       uint16 RxLPduIdx, uint8 InitialData );
uint32 FrDemo_ReconfigLpduTest(uint16 TxLPduIdx, uint8 TxLSduLength,
                               uint16 RxLPduIdx, uint8 InitialData);
uint32 FrDemo_TimerTest(void);
void IrqEray_Init(void);

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/

/*******************************************************************************
** Syntax : void Fr_17_Eray_Demo(void)                                               **
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
** Return value: none                                                         **
**                                                                            **
** Description : Performs the start-up procedure to estimate the estimate     **
**                 the transmission delays and programs them into the MLI     **
**                 local transmitter and MLI remote receiver                  **
**              Writes data to the MLI remote receiver                        **
**              Reads data from MLI remote receiver                           **
*******************************************************************************/
void Fr_17_Eray_Demo(void)
{
  /*  Std_VersionInfoType versionInfo ; */

  #ifdef FR_17_ERAY_PBCFG_0
  uint8 i ;
  uint8 LPduIndex ;
  uint8 LPduCountNode1 ;
  uint8 PlcBytes ;
  uint8 CycleNumber1, CycleNumber2 ;
  uint8 RetValue;
  uint8 FrDemo_ConfigParamIdx;
  uint8 FrDemo_NumOfStartupFrames;
  uint16 MacroTickPtr ;
  uint16 FrDemo_ChannelAStatus, FrDemo_ChannelBStatus;
  uint16 FrDemo_ChannelAEvenList[10], FrDemo_ChannelBEvenList[10];
  uint16 FrDemo_ChannelAOddList[10], FrDemo_ChannelBOddList[10];
  sint16 FrDemo_RateCorrection;
  sint32 FrDemo_OffsetCorrection;
  uint32 FrDemo_ConfigParamValue;
  uint32 ErrorCount = 0 ;
  #endif
  #ifdef IFX_MCAL_RUN_MODE_DEFINE
  /* IFX_MCAL_RUN_MODE_DEFINE = 0 indicates MCAL,
    runs in Supervisor mode*/
  #if(IFX_MCAL_RUN_MODE_DEFINE != 0U)
  /* Set the user-1 mode on*/
  uint32 Cpu_PSW;
  #endif
  #endif

  print_f("\n--------------- Start of FlexRay driver demo ---------------\n");

  /* #if (FR_17_ERAY_VERSION_INFO_API == ON)
    Fr_17_Eray_GetVersionInfo(&versionInfo);
    print_f("Vendor ID : %d\n", versionInfo.vendorID);
    print_f("Module ID : %d\n", versionInfo.moduleID);
    print_f("Instance ID : %d\n", versionInfo.instanceID);
    print_f("FR Driver version : ");
    print_f("%d.", versionInfo.sw_major_version);
    print_f("%d.", versionInfo.sw_minor_version);
    print_f("%d\n", versionInfo.sw_patch_version);
  #endif
  */

  /*  UNUSED_PARAMETER(ErrorCount)*/

  #ifdef FR_17_ERAY_PBCFG_0
  /* Initialize FlexRay driver for demo application (first part) */
  Fr_17_Eray_Init(&Fr_17_Eray_Config);

  /* Call this function if interrupt support is required */
  /* IrqEray_Init(); */
  #endif

  #ifdef DEMO_APP_NODE_1
  /* Initialize FlexRay driver for demo application (second part) */
  Fr_17_Eray_Init(&Fr_17_Eray_Config);
  #endif

  /*Clock Out*/
// Mcal_ResetSafetyEndInitProtection();
  // SCU_EXTCON.B.SEL0 = 2;
  // SCU_EXTCON.B.EN0 = 1;
  print_f("SCU_EXTCON=%d \n", SCU_EXTCON.U);
  Mcal_WriteSafetyEndInitProtReg((uint32*)0xF003603Cu, 0x00000009);
  print_f("SCU_EXTCON=%d \n", SCU_EXTCON.U);
  //SCU_EXTCON.U |= 0x00000009;
  //Ifx_SCU_EXTCON_Bits.SEL0=2;
// Mcal_SetSafetyEndInitProtection();

  #ifdef IFX_MCAL_RUN_MODE_DEFINE
  /* IFX_MCAL_RUN_MODE_DEFINE = 0 indicates MCAL,
     runs in Supervisor mode*/
  #if(IFX_MCAL_RUN_MODE_DEFINE != 0U)
  /* Set the user-1 mode on*/
  Cpu_PSW = (uint32)MFCR(CPU_PSW);
  Cpu_PSW = (Cpu_PSW & CPU_PSW_USER_MODE_MASK);
  Cpu_PSW = (Cpu_PSW | SET_USER_MODE_MASK);
  MTCR (CPU_PSW, Cpu_PSW); /* Set mode to user-1 mode. */
  #endif
  #endif
  /*----------------------------------------------------------------------------*/
  #ifdef FR_17_ERAY_PBCFG_0
  print_f("\nThis is FlexRay Communication Controller 0 \n\n");
  print_f("\nCurrently Communication Controller is in Key slot only Transmission Mode \n\n");

  /* Set FR_CIDX_PKEYSLOTONLYENABLED as Config Param Idx*/
  FrDemo_ConfigParamIdx = FR_CIDX_PKEYSLOTONLYENABLED;

  Fr_17_Eray_ReadCCConfig( 0, FrDemo_ConfigParamIdx, &FrDemo_ConfigParamValue );
  print_f("Configured Value of FrPKeySlotOnlyEnabled is %d \n", FrDemo_ConfigParamValue);

  ErrorCount += FrDemo_ClusterStartup();

  if(ErrorCount == 0)
  {
    RetValue = Fr_17_Eray_AllSlots(0);
    if(RetValue == E_OK)
    {
      print_f("\nSwitching from Key slot only mode to All Slots Transmission Mode \n\n");
    }
    else
    {
      print_f("\nFAILED to Switch to All Slots Transmission Mode \n");
      print_f("\nCC is NOT synchronized to global time\n\n");
    }
  }
  else
  {
    return;
  }

  Fr_17_Eray_GetGlobalTime(0, &CycleNumber1, &MacroTickPtr);

  CycleNumber2 = CycleNumber1 + 1 ;

  do
  {
    Fr_17_Eray_GetGlobalTime(0, &CycleNumber1, &MacroTickPtr);
  } while (CycleNumber1 != CycleNumber2) ;

  Fr_17_Eray_GetNumOfStartupFrames(0, &FrDemo_NumOfStartupFrames);
  print_f("No. of Startup Frames Received is %d \n", FrDemo_NumOfStartupFrames);

  Fr_17_Eray_GetSyncFrameList(0, 10, FrDemo_ChannelAEvenList, FrDemo_ChannelBEvenList, \
                              FrDemo_ChannelAOddList, FrDemo_ChannelBOddList );

  print_f("\nSync Frame Ids Received on Channel A Even Cycles = \n");
  FrDemo_PrintArray(FrDemo_ChannelAEvenList, 10);
  print_f("\nSync Frame Ids Received on Channel B Even Cycles = \n");
  FrDemo_PrintArray(FrDemo_ChannelBEvenList, 10);
  print_f("\nSync Frame Ids Received on Channel A Odd Cycles = \n");
  FrDemo_PrintArray(FrDemo_ChannelAOddList, 10);
  print_f("\nSync Frame Ids Received on Channel B Odd Cycles = \n");
  FrDemo_PrintArray(FrDemo_ChannelBOddList, 10);

  Fr_17_Eray_GetClockCorrection(0, &FrDemo_RateCorrection, &FrDemo_OffsetCorrection );
  print_f("\n\nRateCorrection Value for CC = %d \n", FrDemo_RateCorrection);
  print_f("OffsetCorrection Value for CC = %d \n", FrDemo_OffsetCorrection);

  print_f("\n-------------------------------------------------------------- \n") ;

  LPduCountNode1 = FR_NON_RECONFIG_LPDU_COUNT ;

  for (LPduIndex = 0;
       (LPduIndex < LPduCountNode1) && ((ErrorCount == 0)) ;
       LPduIndex = LPduIndex + 2)
  {
    //PlcBytes = Fr_17_Eray_Config.CfgPtr->LPduConfigPtr->WRHS2.B.PayloadLengthConfigured * 2 ;
    PlcBytes = ((Fr_17_Eray_Config.CfgPtr->LPduConfigPtr->Wrhs2CfgVal >> IFX_ERAY_WRHS2_PLC_OFF) & IFX_ERAY_WRHS2_PLC_MSK) * 2 ;

    print_f("***** Communication with LPDU %d and %d ***** \n", LPduIndex, (LPduIndex + 1)) ;

    /*
      Note: NMVector is assumed to be 2. Even if more than 2 bytes are used,
            only first 2 are used for NM vector verification
    */
    for (i = 1 ; ((i < 5) && (PlcBytes > 1) && (ErrorCount == 0)) ; i++ )
    {
      print_f("[ Length = %d ]\n", PlcBytes) ;
      ErrorCount += FrDemo_TxRxTest(LPduIndex, PlcBytes--, (LPduIndex + 1), (FR_17_ERAY_INITIAL_DATA + LPduIndex + i) );
    }
    print_f("\n-------------------------------------------------------------- \n") ;
  }

  print_f("***** Communication using Reconfigured LPDU 4 and 5 ***** \n") ;
  ErrorCount += FrDemo_ReconfigLpduTest(4, 2, 5, FR_17_ERAY_INITIAL_DATA);

  Fr_17_Eray_GetChannelStatus(0, &FrDemo_ChannelAStatus, &FrDemo_ChannelBStatus );
  print_f("\nLegend for Channel Status \n");
  print_f("--------------------------------- \n");
  print_f("1 - Valid Frame Received on the Channel\n");
  print_f("ANY OTHER VALUE - Slot Status Error Occurred\n");
  print_f("--------------------------------- \n");
  print_f("\nChannel A Status Value is %d \n", FrDemo_ChannelAStatus);
  print_f("Channel B Status Value is %d \n", FrDemo_ChannelBStatus);

  #endif
  /*----------------------------------------------------------------------------*/
  #ifdef DEMO_APP_NODE_1
  print_f("\nThis is FlexRay Communication Controller 1 \n");
  while(1)
  {
    uint8  LSduLength = 0;
    uint8  RxFrameCount = 0U;
    uint16 RxLPduIdx, j ;
    /*   uint32 ErrorCount = 0 ;*/
    uint32 ClusterStartupStatus = 1;

    Fr_TxLPduStatusType TxLPduStatus ;
    Fr_RxLPduStatusType RxLPduStatus ;

    Std_ReturnType RetValue ;

    /*   UNUSED_PARAMETER(ErrorCount)*/
    do
    {
      print_f("Trying FlexRay cluster startup...");
      ClusterStartupStatus = FrDemo_ClusterStartup();
    } while (ClusterStartupStatus == 1);

    /* Wait as long as other FlexRay node remains synchronised to this node */
    do
    {
      /* Make sure fresh data is received */
      FrDemo_InitializeBuffer(FrDemo_RxDataBuffer, 254, 0xDE);

      RxLPduIdx = 1 ;

      do
      {
        /* Prepare receive LPdu */
        Fr_17_Eray_PrepareLPdu(0, RxLPduIdx );

        /* Prepare transmit LPdu */
        Fr_17_Eray_PrepareLPdu(0, (RxLPduIdx - 1));

	      #if(MCAL_AR_VERSION == MCAL_AR_440)
          RetValue = Fr_17_Eray_ReceiveRxLPdu( 0, RxLPduIdx,
                                               (uint8*) &FrDemo_RxDataBuffer,
                                               &RxLPduStatus, &LSduLength, &Fr_Rx_SlotAssignment );
		  #else
		  RetValue = Fr_17_Eray_ReceiveRxLPdu( 0, RxLPduIdx,
                                               (uint8*) &FrDemo_RxDataBuffer,
                                               &RxLPduStatus, &LSduLength );  
		  #endif

        if(RetValue != E_OK)
        {
          print_f("The Fr_17_Eray_ReceiveRxLPdu returned E_NOT_OK. Halting the CC\n");
          Fr_17_Eray_AbortCommunication(0) ;
          break ;
        }

        if(RxLPduStatus == FR_RECEIVED)
        {

          print_f("\nData received: ");
          RxFrameCount++;
          FrDemo_PrintData(FrDemo_RxDataBuffer, LSduLength);

          FrDemo_PrepareTxData( FrDemo_RxDataBuffer, FrDemo_TxDataBuffer, LSduLength);

          print_f("\nData transmitted back: ");
          FrDemo_PrintData(FrDemo_TxDataBuffer, LSduLength);
          #if(MCAL_AR_VERSION == MCAL_AR_440)
          Fr_17_Eray_TransmitTxLPdu(0, (uint8)(RxLPduIdx - 1), (uint8*) &FrDemo_TxDataBuffer,
                                    LSduLength, &Fr_Tx_SlotAssignment) ;
		  #else
          Fr_17_Eray_TransmitTxLPdu(0, (uint8)(RxLPduIdx - 1), (uint8*) &FrDemo_TxDataBuffer,
                                    LSduLength) ;
		  #endif
          do
          {
			#if(MCAL_AR_VERSION == MCAL_AR_440)
            Fr_17_Eray_CheckTxLPduStatus(0, (uint8)(RxLPduIdx - 1), &TxLPduStatus, &Fr_Tx_Check_SlotAssignment);
		    #else
			Fr_17_Eray_CheckTxLPduStatus(0, (uint8)(RxLPduIdx - 1), &TxLPduStatus);
			#endif
          } while (TxLPduStatus != FR_TRANSMITTED);
        }

        RxLPduIdx += 2 ;

      } while (RxLPduIdx < (FR_NON_RECONFIG_LPDU_COUNT)) ;

      if(RxFrameCount == FR_BEGIN_LPDU_RECONFIGURATION)
      {
        RxLPduIdx = FR_17_ERAY_LPDU7_INDX ;

        /* Prepare receive LPdu */
        Fr_17_Eray_PrepareLPdu(0, RxLPduIdx );

        /* Prepare transmit LPdu */
        Fr_17_Eray_PrepareLPdu(0, (RxLPduIdx - 1));

        do
        {
	      #if(MCAL_AR_VERSION == MCAL_AR_440)
          RetValue = Fr_17_Eray_ReceiveRxLPdu( 0, RxLPduIdx,
                                               (uint8*) &FrDemo_RxDataBuffer,
                                               &RxLPduStatus, &LSduLength, &Fr_Rx_SlotAssignment );
		  #else
		  RetValue = Fr_17_Eray_ReceiveRxLPdu( 0, RxLPduIdx,
                                               (uint8*) &FrDemo_RxDataBuffer,
                                               &RxLPduStatus, &LSduLength );  
		  #endif

          if(RetValue != E_OK)
          {
            print_f("The Fr_17_Eray_ReceiveRxLPdu returned E_NOT_OK. Halting the CC\n");
            Fr_17_Eray_AbortCommunication(0) ;
            break ;
          }
        } while(RxLPduStatus != FR_RECEIVED);

        if(RxLPduStatus == FR_RECEIVED)
        {
          RxFrameCount++;
          print_f("\n Length of Data received is %d", LSduLength);
          print_f("\nData received: ");
          FrDemo_PrintData(FrDemo_RxDataBuffer, LSduLength);

          FrDemo_PrepareTxData( FrDemo_RxDataBuffer, FrDemo_TxDataBuffer, LSduLength);

          print_f("\n Length of Data Transmitted is %d", LSduLength);
          print_f("\nData transmitted back: ");
          FrDemo_PrintData(FrDemo_TxDataBuffer, LSduLength);
          #if(MCAL_AR_VERSION == MCAL_AR_440)
          Fr_17_Eray_TransmitTxLPdu(0, (uint8)(RxLPduIdx - 1), (uint8*) &FrDemo_TxDataBuffer,
                                    LSduLength, &Fr_Tx_SlotAssignment) ;
		  #else
          Fr_17_Eray_TransmitTxLPdu(0, (uint8)(RxLPduIdx - 1), (uint8*) &FrDemo_TxDataBuffer,
                                    LSduLength) ;
		  #endif
          do
          {
			#if(MCAL_AR_VERSION == MCAL_AR_440)
            Fr_17_Eray_CheckTxLPduStatus(0, (uint8)(RxLPduIdx - 1), &TxLPduStatus, &Fr_Tx_Check_SlotAssignment);
		    #else
			Fr_17_Eray_CheckTxLPduStatus(0, (uint8)(RxLPduIdx - 1), &TxLPduStatus);
			#endif
          } while (TxLPduStatus != FR_TRANSMITTED);
        }
      }

      if(RxFrameCount == FR_BEGIN_LPDU_DISABLING_CANCELLATION)
      {
        RxFrameCount++;
        do
        {
	      #if(MCAL_AR_VERSION == MCAL_AR_440)
          RetValue = Fr_17_Eray_ReceiveRxLPdu( 0, RxLPduIdx,
                                               (uint8*) &FrDemo_RxDataBuffer,
                                               &RxLPduStatus, &LSduLength, &Fr_Rx_SlotAssignment );
		  #else
		  RetValue = Fr_17_Eray_ReceiveRxLPdu( 0, RxLPduIdx,
                                               (uint8*) &FrDemo_RxDataBuffer,
                                               &RxLPduStatus, &LSduLength );  
		  #endif

          if(RetValue != E_OK)
          {
            print_f("The Fr_17_Eray_ReceiveRxLPdu returned E_NOT_OK. Halting the CC\n");
            Fr_17_Eray_AbortCommunication(0) ;
            break ;
          }
        } while(RxLPduStatus != FR_RECEIVED);

        if(RxLPduStatus == FR_RECEIVED)
        {
          print_f("\n Length of Data received is %d", LSduLength);
          print_f("\nData received: ");
          FrDemo_PrintData(FrDemo_RxDataBuffer, LSduLength);
        }

        j = 0;
        do
        {
	      #if(MCAL_AR_VERSION == MCAL_AR_440)
          RetValue = Fr_17_Eray_ReceiveRxLPdu( 0, RxLPduIdx,
                                               (uint8*) &FrDemo_RxDataBuffer,
                                               &RxLPduStatus, &LSduLength, &Fr_Rx_SlotAssignment );
		  #else
		  RetValue = Fr_17_Eray_ReceiveRxLPdu( 0, RxLPduIdx,
                                               (uint8*) &FrDemo_RxDataBuffer,
                                               &RxLPduStatus, &LSduLength );  
		  #endif
          j++;
          if(RetValue != E_OK)
          {
            print_f("The Fr_17_Eray_ReceiveRxLPdu returned E_NOT_OK. Halting the CC\n");
            Fr_17_Eray_AbortCommunication(0) ;
            break ;
          }
        } while((RxLPduStatus != FR_RECEIVED) && (j != 255));

        if(LSduLength == 0)
        {
          print_f("\n\nNO DATA Received.CANCELLATION of TxLpdu was Successfull\n");
        }

        print_f("\n Length of Data received is %d", LSduLength);
        print_f("\nData received: ");
        FrDemo_PrintData(FrDemo_RxDataBuffer, LSduLength);

        FrDemo_PrepareTxData( FrDemo_RxDataBuffer, FrDemo_TxDataBuffer, LSduLength);

        j = 0;
        do
        {
	      #if(MCAL_AR_VERSION == MCAL_AR_440)
          RetValue = Fr_17_Eray_ReceiveRxLPdu( 0, RxLPduIdx,
                                               (uint8*) &FrDemo_RxDataBuffer,
                                               &RxLPduStatus, &LSduLength, &Fr_Rx_SlotAssignment );
		  #else
		  RetValue = Fr_17_Eray_ReceiveRxLPdu( 0, RxLPduIdx,
                                               (uint8*) &FrDemo_RxDataBuffer,
                                               &RxLPduStatus, &LSduLength );  
		  #endif
          j++;
          if(RetValue != E_OK)
          {
            print_f("The Fr_17_Eray_ReceiveRxLPdu returned E_NOT_OK. Halting the CC\n");
            Fr_17_Eray_AbortCommunication(0) ;
            break ;
          }
        } while((RxLPduStatus != FR_RECEIVED) && (j != 255));

        if(LSduLength == 0)
        {
          print_f("\n\nNO DATA Received.DISABLING of TxLpdu was Successfull\n");
        }

        print_f("\n Length of Data received is %d", LSduLength);
        print_f("\nData received: ");
        FrDemo_PrintData(FrDemo_RxDataBuffer, LSduLength);

        FrDemo_PrepareTxData( FrDemo_RxDataBuffer, FrDemo_TxDataBuffer, LSduLength);

        LSduLength = 2;
        print_f("\n\n Length of Data Transmitted is %d", LSduLength);
        print_f("\nData transmitted back: ");
        FrDemo_PrintData(FrDemo_TxDataBuffer, LSduLength);
		
        #if(MCAL_AR_VERSION == MCAL_AR_440)
        Fr_17_Eray_TransmitTxLPdu(0, (uint8)(RxLPduIdx - 1), (uint8*) &FrDemo_TxDataBuffer,
                                  LSduLength, &Fr_Tx_SlotAssignment) ;
		#else
        Fr_17_Eray_TransmitTxLPdu(0, (uint8)(RxLPduIdx - 1), (uint8*) &FrDemo_TxDataBuffer,
                                  LSduLength) ;
		#endif

        do
        {
		   #if(MCAL_AR_VERSION == MCAL_AR_440)
           Fr_17_Eray_CheckTxLPduStatus(0, (uint8)(RxLPduIdx - 1), &TxLPduStatus, &Fr_Tx_Check_SlotAssignment);
		   #else
		   Fr_17_Eray_CheckTxLPduStatus(0, (uint8)(RxLPduIdx - 1), &TxLPduStatus);
		   #endif
        } while (TxLPduStatus != FR_TRANSMITTED);
      }
    } while(Fr_17_Eray_DemoIsCcInSync());
  }
  #endif
  /*----------------------------------------------------------------------------*/
  #ifdef FR_17_ERAY_PBCFG_0
  if(ErrorCount == 0)
  {
    Fr_POCStatusType Fr_17_Eray_POCStatus ;

    ErrorCount += FrDemo_TimerTest();

    Fr_17_Eray_AbortCommunication(0) ;

    Fr_17_Eray_GetPOCStatus(0, &Fr_17_Eray_POCStatus);

    if(Fr_17_Eray_POCStatus.State != FR_POCSTATE_HALT)
    {
      print_f("FlexRay CC did not abort the communication\n");
      ErrorCount++ ;
    }
  }
  if(ErrorCount)
  {
    print_f("FlexRay demo FAILED.\n");
    StartResult();
    print_f("\n Result = Fail");
    EndResult();    
  }
  else
  {
    print_f("FlexRay demo PASSED.\n");
    StartResult();
    print_f("\n Result = Pass");
    EndResult();
  }
  print_f("-------------------------------------------------------------- \n") ;
  #endif

}

uint32 FrDemo_ClusterStartup(void)
{
  volatile uint32 i ;
  Std_ReturnType ApiReturnValue ;

  Fr_POCStatusType POCStatusNew ;
  Fr_POCStatusType POCStatusOld ;

  #ifdef FR_17_ERAY_PBCFG_0
  uint8 FrTest_WakeupRxStatus = 0;
  #endif

  #ifdef DEMO_APP_NODE_1
  uint8 FrDemo_ConfigParamIdx;
  uint32 FrDemo_ConfigParamValue;
  #endif

  /* Initialize FlexRay CC */
  Fr_17_Eray_ControllerInit(0);

  #ifdef FR_17_ERAY_PBCFG_0
  do
  {
    Fr_17_Eray_GetWakeupRxStatus(0, &FrTest_WakeupRxStatus );

  } while(!FrTest_WakeupRxStatus);

  if(FrTest_WakeupRxStatus == 1)
  {
    print_f("\nWakeup Pattern Received on FR_CHANNEL_A \n");
  }
  else if(FrTest_WakeupRxStatus == 2)
  {
    print_f("\nWakeup Pattern Received on FR_CHANNEL_B \n");
  }

  Fr_17_Eray_GetPOCStatus(0, &POCStatusNew);

  while(POCStatusNew.State != FR_POCSTATE_READY)
  {
    Fr_17_Eray_GetPOCStatus(0, &POCStatusNew);
  }
  #endif

  #ifdef DEMO_APP_NODE_1
  /* Set FR_CIDX_PWAKEUPCHANNEL as Config Param Idx*/
  FrDemo_ConfigParamIdx = FR_CIDX_PWAKEUPCHANNEL;

  Fr_17_Eray_ReadCCConfig( 0, FrDemo_ConfigParamIdx, &FrDemo_ConfigParamValue );
  if(FrDemo_ConfigParamValue == 0)
  {
    print_f("\nDefault Configured FrPWakeupChannel is FR_CHANNEL_A \n");
  }
  else
  {
    print_f("\nDefault Configured FrPWakeupChannel is FR_CHANNEL_B \n");
  }

  Fr_17_Eray_SetWakeupChannel(0, FR_CHANNEL_A);
  print_f("\nSetting FR Wakeup Channel as FR_CHANNEL_B \n");
  i = 255 ;

  do
  {
    Fr_17_Eray_GetPOCStatus(0, &POCStatusNew);
    if(POCStatusNew.State != FR_POCSTATE_WAKEUP)
    {
      Fr_17_Eray_SendWUP(0);   /* Send wakeup signal */
    }
    i--;
  } while((POCStatusNew.State != FR_POCSTATE_WAKEUP) && i);

  print_f("\nSent Wakeup Pattern on FR_CHANNEL_B \n");

  Fr_17_Eray_GetPOCStatus(0, &POCStatusNew);

  while(POCStatusNew.State != FR_POCSTATE_READY)
  {
    Fr_17_Eray_GetPOCStatus(0, &POCStatusNew);
  }
  #endif

  i = 10 ;
  do
  {
    ApiReturnValue = Fr_17_Eray_AllowColdstart(0) ;
  } while ((ApiReturnValue == E_NOT_OK) && (i--));

  if(i == 0)
  {
    print_f("Fr_17_Eray_AllowColdstart API execution failed.\n");
  }

  /* Start FlexRay communication */
  i = 10 ;
  do
  {
    ApiReturnValue = Fr_17_Eray_StartCommunication(0) ;
  } while ((ApiReturnValue == E_NOT_OK) && (i--));
  if(i == 0)
  {
    print_f("Fr_17_Eray_StartCommunication API execution failed.\n");
    return 1 ; /* failure */
  }

  Fr_17_Eray_GetPOCStatus(0, &POCStatusOld);

  print_f("\nLegend for POC Startup State \n");
  print_f("--------------------------------- \n");
  print_f("0 - UNDEFINED\n");
  print_f("1 - COLDSTART_LISTEN\n");
  print_f("2 - INTEGRATION_COLDSTART_CHECK\n");
  print_f("3 - COLDSTART_JOIN\n");
  print_f("4 - COLLISION_RESOLUTION\n");
  print_f("5 - CONSISTENCY_CHECK\n");
  print_f("6 - INTEGRATION_LISTEN\n");
  print_f("7 - INITIALIZE_SCHEDULE\n");
  print_f("8 - INTEGRATION_CONSISTENCY_CHECK\n");
  print_f("9 - COLDSTART_GAP\n");
  print_f("\n");

  print_f("FlexRay cluster start up in progress.... \n\n");
  print_f("Startup state transitions = ");

  /* Wait till FlexRay CC synchronised to FlexRay global time */
  do
  {
    Fr_17_Eray_GetPOCStatus(0, &POCStatusNew);

    if (POCStatusNew.StartupState != POCStatusOld.StartupState)
    {
      print_f("%d, ", POCStatusNew.StartupState);
      POCStatusOld.StartupState = POCStatusNew.StartupState ;
    }
  } while( (!(Fr_17_Eray_DemoIsCcInSync())) &&
           (POCStatusNew.StartupState != FR_STARTUP_INTEGRATION_LISTEN) &&
           (POCStatusNew.State != FR_POCSTATE_HALT));

  if(Fr_17_Eray_DemoIsCcInSync())
  {
    print_f("\nFlexRay cluster startup successful. \n");
    return 0 ; /* Startup successful */
  }
  else
  {
    print_f("\n");
    if(POCStatusNew.State == FR_POCSTATE_HALT)
    {
      print_f("FlexRay CC moved to HALT state.\n");
      print_f("Try again. If it is persistent, check correctness of cluster parameters\n");
    }
    if(POCStatusNew.StartupState == FR_STARTUP_INTEGRATION_LISTEN)
    {
      print_f("FlexRay cluster startup attempt failed. \n");
      print_f("Hints: Check if\n");
      print_f("- Other FlexRay node is ready for synchronisation.\n");
      print_f("- FlexRay nodes are connected properly.\n");
      print_f("- Port pin configuration is done correctly.\n");
      print_f("\n");
      print_f("=================================================================");
      print_f("\n");
    }
    return 1 ; /* Startup failed */
  }
}

void FrDemo_InitializeBuffer(
  uint8 * BufferPtr,
  uint8 DataLength,
  uint8 Data
)
{
  uint32 i;

  for(i = 0; i < DataLength ; i++)
  {
    BufferPtr[i] = Data ;
  }
}

/* DataLength - in bytes as returned by API */
void FrDemo_CopyReceivedData(
  uint8 * SrcPtr,
  uint8 * DstPtr,
  uint8 DataLength
)
{
  uint32 i;

  for(i = 0; i < DataLength ; i++)
  {
    DstPtr[i] = SrcPtr[i] ;
  }
}

void FrDemo_PrepareTxData(
  uint8 * SrcPtr,
  uint8 * DstPtr,
  uint8 DataLength
)
{
  uint32 i;

  for(i = 0; i < DataLength ; i++)
  {
    DstPtr[i] = SrcPtr[i] + FR_17_ERAY_DATA_INCREMENT ;
  }
}

void FrDemo_PrintData(
  uint8 * BufferPtr,
  uint8 DataLength
)
{
  uint32 i;

  for(i = 0; i < DataLength ; i++)
  {
    print_f("%2x", BufferPtr[i]) ;
  }
}

void FrDemo_PrintArray(
  uint16 * BufferPtr,
  uint8 DataLength
)
{
  uint32 i;

  for(i = 0; i < DataLength ; i++)
  {
    print_f("%2x", BufferPtr[i]) ;
  }
}

uint32 FrDemo_VerifyData(
  uint8 * DataPtr,
  uint8 DataLength,
  uint16 RxDataIndex,
  uint8 InitialData
)
{
  uint32 i;
  uint32 ErrorCount = 0 ;

  for (i = 0; i < DataLength ; i++)
  {
    if( DataPtr[i] != (InitialData + (FR_17_ERAY_DATA_INCREMENT * (RxDataIndex + 1) * 2)) )
    {
      ErrorCount++ ;
    }
  }

  return ErrorCount ;
}

uint32 FrDemo_TxRxTest(
  uint16 TxLPduIdx,
  uint8 TxLSduLength,
  uint16 RxLPduIdx,
  uint8 InitialData
)
{
  uint32 ErrorCount = 0 ;
  uint16 j;

  Fr_TxLPduStatusType TxLPduStatus ;

  Fr_RxLPduStatusType RxLPduStatus ;
  uint8 RxLSduLength ;

  Std_ReturnType RetValue ;
  uint32 NmVectorPtr;

  uint8 CycleNumber1, CycleNumber2 ;
  uint16 MacroTickPtr ;

  /*----------------------------------------------------------------------------*/
  /*            Normal data transmission and reception                          */
  /*----------------------------------------------------------------------------*/
  print_f("Data transmission and reception in progress... \n");

  /* Initial data */
  FrDemo_InitializeBuffer(FrDemo_RxDataBuffer, TxLSduLength, InitialData);

  print_f("Initial data transferred: 0x%x\n", (InitialData + FR_17_ERAY_DATA_INCREMENT) );

  j = 0 ;

  do
  {
    /* Create new data to be transferred */
    FrDemo_PrepareTxData(FrDemo_RxDataBuffer, FrDemo_TxDataBuffer, TxLSduLength);

    Fr_17_Eray_PrepareLPdu(0, (uint8)TxLPduIdx);
    Fr_17_Eray_PrepareLPdu(0, RxLPduIdx );

    ERAY0_SIR.U = 0xC ;


    #if(MCAL_AR_VERSION == MCAL_AR_440)
    RetValue = Fr_17_Eray_TransmitTxLPdu(0, TxLPduIdx, (uint8*) &FrDemo_TxDataBuffer,
                                         TxLSduLength, &Fr_Tx_SlotAssignment) ;
	#else
    RetValue = Fr_17_Eray_TransmitTxLPdu(0, TxLPduIdx, (uint8*) &FrDemo_TxDataBuffer,
                                         TxLSduLength) ;
	#endif
    if(RetValue == E_NOT_OK)
    {
      print_f("Fr_17_Eray_TransmitTxLPdu returned E_NOT_OK\n");
      ErrorCount++ ;
      return ErrorCount ;
    }

    do
    {
	    #if(MCAL_AR_VERSION == MCAL_AR_440)
        RetValue = Fr_17_Eray_CheckTxLPduStatus(0, TxLPduIdx, &TxLPduStatus, &Fr_Tx_Check_SlotAssignment);
        #else
        RetValue = Fr_17_Eray_CheckTxLPduStatus(0, TxLPduIdx, &TxLPduStatus);
        #endif
      

      if(RetValue == E_NOT_OK)
      {
        print_f("Fr_17_Eray_CheckTxLPduStatus returned E_NOT_OK\n");
        ErrorCount++ ;
        return ErrorCount ;
      }
    } while (TxLPduStatus != FR_TRANSMITTED);

    /* Make sure fresh data is received */
    FrDemo_InitializeBuffer(FrDemo_RxDataBuffer, TxLSduLength, 0xDE);

    do
    {

	#if(MCAL_AR_VERSION == MCAL_AR_440)
    RetValue = Fr_17_Eray_ReceiveRxLPdu( 0, RxLPduIdx,
                                            (uint8*) &FrDemo_RxDataBuffer,
                                            &RxLPduStatus, &RxLSduLength, &Fr_Rx_SlotAssignment );
	#else
	RetValue = Fr_17_Eray_ReceiveRxLPdu( 0, RxLPduIdx,
                                            (uint8*) &FrDemo_RxDataBuffer,
                                            &RxLPduStatus, &RxLSduLength );  
	#endif

      if(RetValue == E_NOT_OK)
      {
        print_f("Fr_17_Eray_ReceiveRxLPdu returned E_NOT_OK\n");
        ErrorCount++ ;
        return ErrorCount ;
      }
    } while((RxLPduStatus != FR_RECEIVED) && (RxLPduStatus != FR_RECEIVED_MORE_DATA_AVAILABLE));

    Fr_17_Eray_GetGlobalTime(0, &CycleNumber1, &MacroTickPtr);
    CycleNumber2 = CycleNumber1 + 1 ;
    CycleNumber2 = CycleNumber2 % 64 ;

    do
    {
      Fr_17_Eray_GetGlobalTime(0, &CycleNumber1, &MacroTickPtr);
    } while (CycleNumber1 != CycleNumber2) ;

    NmVectorPtr = 0 ;
    Fr_17_Eray_GetNmVector(0, (uint8 *) &NmVectorPtr) ;

    FrDemo_CopyReceivedData(FrDemo_RxDataBuffer, FrDemo_RxData[j], RxLSduLength) ;

    FrDemo_NmVectorPtr [j] = NmVectorPtr ;

    j++ ;

  } while(FR_17_ERAY_DATA_COUNT - j);

  print_f("Received Data [NM Vector]:");
  for(j = 0; j < FR_17_ERAY_DATA_COUNT; j++)
  {
    /* validate data part only */
    if( FrDemo_VerifyData( FrDemo_RxData[j], TxLSduLength, j, InitialData))
    {
      ErrorCount++ ;
    }

    if((j % 3) == 0)
    {
      print_f("\n");
    }

    FrDemo_PrintData(FrDemo_RxData[j], TxLSduLength) ;
    print_f(" [%x], ", FrDemo_NmVectorPtr[j]);
  }

  print_f("\n");

  return ErrorCount ;
}

uint32 FrDemo_ReconfigLpduTest(
  uint16 TxLPduIdx,
  uint8 TxLSduLength,
  uint16 RxLPduIdx,
  uint8 InitialData
)
{
  uint8 RxLSduLength ;
  Std_ReturnType RetValue ;
  uint32 ErrorCount = 0, j ;

  Fr_TxLPduStatusType TxLPduStatus ;
  Fr_RxLPduStatusType RxLPduStatus ;

  /*----------------------------------------------------------------------------*/
  /*            Reconfigured Lpdus Data transmission and reception                          */
  /*----------------------------------------------------------------------------*/
  print_f("Data transmission and reception in progress... \n");

  /* Initial data */
  FrDemo_InitializeBuffer(FrDemo_RxDataBuffer, TxLSduLength, InitialData);

  /* Create new data to be transferred */
  FrDemo_PrepareTxData(FrDemo_RxDataBuffer, FrDemo_TxDataBuffer, TxLSduLength);

  /* Reconfigure the Tx LPdu for Transmission */
  Fr_17_Eray_ReconfigLPdu( 0, TxLPduIdx, FR_RECONFIGURED_FRAME_ID, FR_CHANNEL_A, FR_TX_CYCLE_REP_COUNT, FR_TX_BASE_CYCLE, TxLSduLength, FR_TX_LPDU_HEADER_CRC_VAL );
  /* Reconfigure the Rx LPdu for Reception */
  Fr_17_Eray_ReconfigLPdu( 0, RxLPduIdx, FR_RECONFIGURED_FRAME_ID, FR_CHANNEL_A, FR_RX_CYCLE_REP_COUNT, FR_RX_BASE_CYCLE, TxLSduLength, 0 );


  #if(MCAL_AR_VERSION == MCAL_AR_440)
  RetValue = Fr_17_Eray_TransmitTxLPdu(0, TxLPduIdx, (uint8*) &FrDemo_TxDataBuffer,
                                       TxLSduLength, &Fr_Tx_SlotAssignment) ;
  #else
  RetValue = Fr_17_Eray_TransmitTxLPdu(0, TxLPduIdx, (uint8*) &FrDemo_TxDataBuffer,
                                       TxLSduLength) ;
  #endif
  if(RetValue == E_NOT_OK)
  {
    print_f("Fr_17_Eray_TransmitTxLPdu returned E_NOT_OK\n");
    ErrorCount++ ;
    return ErrorCount ;
  }

  do
  {
	    #if(MCAL_AR_VERSION == MCAL_AR_440)
        RetValue = Fr_17_Eray_CheckTxLPduStatus(0, TxLPduIdx, &TxLPduStatus, &Fr_Tx_Check_SlotAssignment);
        #else
        RetValue = Fr_17_Eray_CheckTxLPduStatus(0, TxLPduIdx, &TxLPduStatus);
        #endif

    if(RetValue == E_NOT_OK)
    {
      print_f("Fr_17_Eray_CheckTxLPduStatus returned E_NOT_OK\n");
      ErrorCount++ ;
      return ErrorCount ;
    }
  } while (TxLPduStatus != FR_TRANSMITTED);

  print_f("\nReconfigured Lpdu Transmitted Data Length is %d", TxLSduLength);
  print_f("\nReconfigured Lpdu Transmitted Data []:");
  FrDemo_PrintData(FrDemo_TxDataBuffer, TxLSduLength) ;

  /* Make sure fresh data is received */
  FrDemo_InitializeBuffer(FrDemo_RxDataBuffer, TxLSduLength, 0xDE);

	#if(MCAL_AR_VERSION == MCAL_AR_440)
    RetValue = Fr_17_Eray_ReceiveRxLPdu( 0, RxLPduIdx,
                                            (uint8*) &FrDemo_RxDataBuffer,
                                            &RxLPduStatus, &RxLSduLength, &Fr_Rx_SlotAssignment );
	#else
	RetValue = Fr_17_Eray_ReceiveRxLPdu( 0, RxLPduIdx,
                                            (uint8*) &FrDemo_RxDataBuffer,
                                            &RxLPduStatus, &RxLSduLength );  
	#endif

  if(RetValue == E_NOT_OK)
  {
    print_f("Fr_17_Eray_ReceiveRxLPdu returned E_NOT_OK\n");
    ErrorCount++ ;
    return ErrorCount ;
  }

  print_f("\n\nReconfigured Lpdu Received Data Length is %d", RxLSduLength);
  print_f("\nReconfigured Lpdu Received Data []:");
  FrDemo_PrintData(FrDemo_RxDataBuffer, RxLSduLength) ;

  if((RxLPduStatus == FR_RECEIVED) && (TxLPduStatus == FR_TRANSMITTED))
  {
    print_f("\n\nSuccessfull Transmission and Reception of Data using Reconfigured Lpdus");
    print_f("\n-------------------------------------------------------------- \n") ;
  }


  #if(MCAL_AR_VERSION == MCAL_AR_440)
  RetValue = Fr_17_Eray_TransmitTxLPdu(0, TxLPduIdx, (uint8*) &FrDemo_TxDataBuffer,
                                       TxLSduLength, &Fr_Tx_SlotAssignment) ;
  #else
  RetValue = Fr_17_Eray_TransmitTxLPdu(0, TxLPduIdx, (uint8*) &FrDemo_TxDataBuffer,
                                       TxLSduLength) ;
  #endif
									   

  if(RetValue == E_NOT_OK)
  {
    print_f("Fr_17_Eray_TransmitTxLPdu returned E_NOT_OK\n");
    ErrorCount++ ;
    return ErrorCount ;
  }

  do
  {
	    #if(MCAL_AR_VERSION == MCAL_AR_440)
        RetValue = Fr_17_Eray_CheckTxLPduStatus(0, TxLPduIdx, &TxLPduStatus, &Fr_Tx_Check_SlotAssignment);
        #else
        RetValue = Fr_17_Eray_CheckTxLPduStatus(0, TxLPduIdx, &TxLPduStatus);
        #endif

    if(RetValue == E_NOT_OK)
    {
      print_f("Fr_17_Eray_CheckTxLPduStatus returned E_NOT_OK\n");
      ErrorCount++ ;
      return ErrorCount ;
    }
  } while (TxLPduStatus != FR_TRANSMITTED);

  print_f("\n\nReconfigured Lpdu Transmitted Data Length is %d", TxLSduLength);
  print_f("\nReconfigured Lpdu Transmitted Data []:");
  FrDemo_PrintData(FrDemo_TxDataBuffer, TxLSduLength) ;
  print_f("\n\nSuccessfull Re-Transmission of Data using Reconfigured Lpdus");
  print_f("\n-------------------------------------------------------------- \n") ;


  #if(MCAL_AR_VERSION == MCAL_AR_440)
  RetValue = Fr_17_Eray_TransmitTxLPdu(0, TxLPduIdx, (uint8*) &FrDemo_TxDataBuffer,
                                       TxLSduLength, &Fr_Tx_SlotAssignment) ;
  #else
  RetValue = Fr_17_Eray_TransmitTxLPdu(0, TxLPduIdx, (uint8*) &FrDemo_TxDataBuffer,
                                       TxLSduLength) ;
  #endif
  if(RetValue == E_NOT_OK)
  {
    print_f("Fr_17_Eray_TransmitTxLPdu returned E_NOT_OK\n");
    ErrorCount++ ;
    return ErrorCount ;
  }

	    #if(MCAL_AR_VERSION == MCAL_AR_440)
        Fr_17_Eray_CheckTxLPduStatus(0, TxLPduIdx, &TxLPduStatus, &Fr_Tx_Check_SlotAssignment);
        #else
        Fr_17_Eray_CheckTxLPduStatus(0, TxLPduIdx, &TxLPduStatus);
        #endif

  if(TxLPduStatus == FR_NOT_TRANSMITTED)
  {
    /* Cancel Tx LPdu Transmission */
    RetValue = Fr_17_Eray_CancelTxLPdu(0, TxLPduIdx);
    if(RetValue == E_NOT_OK)
    {
      print_f("\nFr_17_Eray_CancelTxLPdu returned E_NOT_OK\n");
      ErrorCount++ ;
      return ErrorCount ;
    }
    else
    {
      print_f("\nTx Lpdu Transmission Cancelled Sucessfully\n");
      print_f("\n-------------------------------------------------------------- \n") ;
    }
  }

  /* Disable the Tx LPdu for Transmission */
  Fr_17_Eray_DisableLPdu( 0, TxLPduIdx );


  #if(MCAL_AR_VERSION == MCAL_AR_440)
  RetValue = Fr_17_Eray_TransmitTxLPdu(0, TxLPduIdx, (uint8*) &FrDemo_TxDataBuffer,
                                       TxLSduLength, &Fr_Tx_SlotAssignment) ;
  #else
  RetValue = Fr_17_Eray_TransmitTxLPdu(0, TxLPduIdx, (uint8*) &FrDemo_TxDataBuffer,
                                       TxLSduLength) ;
  #endif
  if(RetValue == E_NOT_OK)
  {
    print_f("Fr_17_Eray_TransmitTxLPdu returned E_NOT_OK\n");
    ErrorCount++ ;
    return ErrorCount ;
  }

	    #if(MCAL_AR_VERSION == MCAL_AR_440)
        Fr_17_Eray_CheckTxLPduStatus(0, TxLPduIdx, &TxLPduStatus, &Fr_Tx_Check_SlotAssignment);
        #else
        Fr_17_Eray_CheckTxLPduStatus(0, TxLPduIdx, &TxLPduStatus);
        #endif

  if(TxLPduStatus == FR_NOT_TRANSMITTED)
  {
    print_f("\nTx Lpdu Transmission Disabled Sucessfully \n");
    print_f("\n-------------------------------------------------------------- \n") ;
  }

  /* Disable the Rx LPdu for Reception */
  Fr_17_Eray_DisableLPdu( 0, RxLPduIdx );

  /* Make sure fresh data is received */
  FrDemo_InitializeBuffer(FrDemo_RxDataBuffer, TxLSduLength, 0xDE);

  j = 0;
  do
  {
	#if(MCAL_AR_VERSION == MCAL_AR_440)
    RetValue = Fr_17_Eray_ReceiveRxLPdu( 0, RxLPduIdx,
                                            (uint8*) &FrDemo_RxDataBuffer,
                                            &RxLPduStatus, &RxLSduLength, &Fr_Rx_SlotAssignment );
	#else
	RetValue = Fr_17_Eray_ReceiveRxLPdu( 0, RxLPduIdx,
                                            (uint8*) &FrDemo_RxDataBuffer,
                                            &RxLPduStatus, &RxLSduLength );  
	#endif
    j++;
    if(RetValue == E_NOT_OK)
    {
      print_f("Fr_17_Eray_ReceiveRxLPdu returned E_NOT_OK\n");
      ErrorCount++ ;
      return ErrorCount ;
    }
  } while((RxLPduStatus != FR_RECEIVED) && (j != 255));

  if((RxLPduStatus == FR_NOT_RECEIVED) && (!RxLSduLength))
  {
    print_f("\nRx Lpdu Reception Disabled Sucessfully\n");
    print_f("\n-------------------------------------------------------------- \n") ;
  }

  print_f("\n");
  return ErrorCount ;
}

uint32 FrDemo_TimerTest(void)
{
  uint8 Fr_17_Eray_Cycle ;
  uint16 Fr_17_Eray_MacroTick ;
  uint32 ErrorCount = 0 ;
  volatile uint32 j;

  boolean Fr_IRQStatusPtr = FALSE ;

  /*----------------------------------------------------------------------------*/
  /*
    Test for
          - Fr_17_Eray_SetAbsoluteTimer
          - Fr_17_Eray_EnableAbsoluteTimerIRQ
          - Fr_17_Eray_GetAbsoluteTimerIRQStatus
          - Fr_17_Eray_AckAbsoluteTimerIRQ
  */
  /*----------------------------------------------------------------------------*/
  print_f("\n");
  print_f("\n-------------------------------------------------------------- \n") ;
  print_f("Testing APIs Fr_17_Eray_SetAbsoluteTimer, Fr_17_Eray_EnableAbsoluteTimerIRQ, \n");
  print_f("Fr_17_Eray_GetAbsoluteTimerIRQStatus, Fr_17_Eray_AckAbsoluteTimerIRQ...");

  /* Program absolute timer: Cycle = 5, macrotick = 2 */
  Fr_17_Eray_SetAbsoluteTimer(0, 0, 5, 2);

  Fr_17_Eray_EnableAbsoluteTimerIRQ(0, 0) ;

  /* Look for two absolute timer events ==> 2*64 communication cycles */
  j = 2;

  do
  {
    Fr_IRQStatusPtr = FALSE ;

    do
    {
      Fr_17_Eray_GetAbsoluteTimerIRQStatus(0, 0, &Fr_IRQStatusPtr) ;
    } while(Fr_IRQStatusPtr != TRUE);

    Fr_IRQStatusPtr = FALSE ;

    /* Acknowledge Absolute timer interrupt */
    Fr_17_Eray_AckAbsoluteTimerIRQ(0, 0);

  } while (j--) ;

  print_f(" DONE.\n\n");

  /*----------------------------------------------------------------------------*/
  /*  Test for Fr_17_Eray_DisableAbsoluteTimerIRQ  */
  /*----------------------------------------------------------------------------*/

  /* ------------  Only absolute timer IRQ disabled ---------------- */
  print_f("Testing API Fr_17_Eray_DisableAbsoluteTimerIRQ...");

  /* Disable absolute timer request only */
  Fr_17_Eray_DisableAbsoluteTimerIRQ(0, 0) ;

  /* Clear both timer interrupts */
  Fr_17_Eray_AckAbsoluteTimerIRQ(0, 0);

  do
  {
    Fr_17_Eray_GetGlobalTime(0, &Fr_17_Eray_Cycle, &Fr_17_Eray_MacroTick) ;
  } while(Fr_17_Eray_Cycle != 0);

  do
  {
    Fr_17_Eray_GetGlobalTime(0, &Fr_17_Eray_Cycle, &Fr_17_Eray_MacroTick) ;
  } while(Fr_17_Eray_Cycle != 63);

  /* Fr_IRQStatusPtr = FALSE ;
  Fr_17_Eray_GetAbsoluteTimerIRQStatus(0, 0, &Fr_IRQStatusPtr) ; */

  /* Absolute timer event is NOT expected */
  /* if(Fr_IRQStatusPtr == TRUE)
  {
    ErrorCount++ ;
    print_f("Error: Unexpected absolute timer event (1).\n");
  } */

  print_f(" DONE.\n\n");

  /* ------------  Both timers IRQ disabled ------------------- */

  print_f("Testing API Fr_17_Eray_DisableAbsoluteTimerIRQ ...");

  do
  {
    Fr_17_Eray_GetGlobalTime(0, &Fr_17_Eray_Cycle, &Fr_17_Eray_MacroTick) ;
  } while(Fr_17_Eray_Cycle != 0);

  do
  {
    Fr_17_Eray_GetGlobalTime(0, &Fr_17_Eray_Cycle, &Fr_17_Eray_MacroTick) ;
  } while(Fr_17_Eray_Cycle != 63);

  /*Fr_IRQStatusPtr = FALSE ;
  Fr_17_Eray_GetAbsoluteTimerIRQStatus(0, 0, &Fr_IRQStatusPtr) ;*/

  /* Absolute timer event is NOT expected */
  /* if(Fr_IRQStatusPtr == TRUE)
   {
     ErrorCount++ ;
     print_f("Error: Unexpected absolute timer event (2).\n");
   }*/

  print_f(" DONE.\n");

  /*----------------------------------------------------------------------------*/
  /* Test for Fr_17_Eray_CancelAbsoluteTimer */
  /*----------------------------------------------------------------------------*/

  print_f("Testing API Fr_17_Eray_CancelAbsoluteTimer ...");

  Fr_17_Eray_EnableAbsoluteTimerIRQ(0, 0) ;

  do
  {
    Fr_17_Eray_GetGlobalTime(0, &Fr_17_Eray_Cycle, &Fr_17_Eray_MacroTick) ;
  } while(Fr_17_Eray_Cycle != 0);

  do
  {
    Fr_17_Eray_GetGlobalTime(0, &Fr_17_Eray_Cycle, &Fr_17_Eray_MacroTick) ;
  } while(Fr_17_Eray_Cycle != 10);

  Fr_IRQStatusPtr = FALSE ;
  Fr_17_Eray_GetAbsoluteTimerIRQStatus(0, 0, &Fr_IRQStatusPtr) ;

  /* Absolute timer event is expected */
  if(Fr_IRQStatusPtr == FALSE)
  {
    ErrorCount++ ;
    print_f("Error: Expected absolute timer event didn't occur (2).\n");
  }

  /* Stop the timers */
  Fr_17_Eray_CancelAbsoluteTimer(0, 0);

  /* Clear the timer events */
  Fr_17_Eray_AckAbsoluteTimerIRQ(0, 0);

  /* ---- Wait for 64 communication cycles ----*/
  do
  {
    Fr_17_Eray_GetGlobalTime(0, &Fr_17_Eray_Cycle, &Fr_17_Eray_MacroTick) ;
  } while(Fr_17_Eray_Cycle != 0);

  do
  {
    Fr_17_Eray_GetGlobalTime(0, &Fr_17_Eray_Cycle, &Fr_17_Eray_MacroTick) ;
  } while(Fr_17_Eray_Cycle != 63);

  /* -----------------------------------------*/

  Fr_IRQStatusPtr = FALSE ;
  Fr_17_Eray_GetAbsoluteTimerIRQStatus(0, 0, &Fr_IRQStatusPtr) ;

  /* Absolute timer event is NOT expected */
  if(Fr_IRQStatusPtr == TRUE)
  {
    ErrorCount++ ;
    print_f("Error: Unexpected absolute timer event (3).\n");
  }

  print_f(" DONE.\n\n");
  print_f("-------------------------------------------------------------- \n") ;

  /*----------------------------------------------------------------------------*/
  return ErrorCount ;
}

#ifdef FR_17_ERAY_PBCFG_0

/*******************************************************************************
** Syntax : void IrqEray_Init(void)                                           **
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
** Return value: none                                                         **
**                                                                            **
** Description : Function to initialize interrupt service register INT0SRC to **
**               SRE = 1 , SRPN = 100;                                        **
**               Purpose of this function is to validate interrupt            **
**               functionality, so should be used in such scenarios.          **
**               Note: Should be called after Fr_17_Eray_Init function        **
**                                                                            **
*******************************************************************************/
void IrqEray_Init(void)
{
  SRC_ERAY_ERAY0_INT0.B.SRE = 1;
  SRC_ERAY_ERAY0_INT0.B.SRPN = 100U;
}

/*******************************************************************************
** Syntax :       void INTERRUPT (100) ERAY_ISR_SRN0(void)                    **
**                                                                            **
** Service ID:   : NA                                                         **
**                                                                            **
** Sync/Async:   : Asynchronous                                               **
**                                                                            **
** Reentrancy:   : Non Reentrant                                              **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : ISR for Ablsoute timer interrupt. Reads Global time and      **
**               prints cycle number along with macrotick.                    **
**               Purpose of this function is to validate interrupt            **
**               functionality, so will be valid when IrqEray_Init is called. **
**                                                                            **
*******************************************************************************/
void ERAY_ISR_SRN0(void)
{
  uint8 CycleNumber;
  uint16 MacroTickPtr ;

  Fr_17_Eray_GetGlobalTime(0, &CycleNumber, &MacroTickPtr);
  print_f("CycleNumber : %d   MacroTick : %d\n", CycleNumber, MacroTickPtr );

  SRC_ERAY_ERAY0_TINT0.B.CLRR = 1; /* Clear the request bit */
}

#endif /* #ifdef(FR_17_ERAY_PBCFG_0) */
