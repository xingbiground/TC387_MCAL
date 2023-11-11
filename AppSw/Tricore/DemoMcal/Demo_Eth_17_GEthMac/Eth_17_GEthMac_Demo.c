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
**  FILENAME   : Eth_17_GEthMacV2_Demo.c                                     **
**                                                                           **
**  VERSION    : 2.0.0                                                       **
**                                                                           **
**  DATE       : 2020-12-11                                                  **
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
**                - Demo application for ETH driver                          **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/

/******************************************************************************
**                      Includes                                             **
******************************************************************************/
#include "IfxGeth_reg.h"
#include "Eth_17_GEthMac_Demo.h"
#if(MCAL_AR_VERSION == MCAL_AR_440)
#include "Eth_17_GEthMacV2.h"
#include "EthIf.h"
#else
#include "Eth_17_GEthMac.h"
#include "EthIf_Cbk.h"
#endif
#include "Test_Print.h"
#include "Test_Time.h"

#if defined _GHS_C_TRICORE_
#pragma ghs nowarning 1729
#include "stdlib.h"
#pragma ghs endnowarning 1729
#else
#include "stdlib.h"
#endif
#include "Eth_GeneralTypes.h"

/******************************************************************************
**                      Imported Compiler Switch Check                       **
******************************************************************************/

/******************************************************************************
**                      Private Macro Definitions                            **
******************************************************************************/
#define ETH_ARP_PROTOCOL                        (0X0806U)
#define PHY_PHYCTL1_REG                         (0x13)
#define PHY_PHYCTL2_REG                         (0x14)
#define PHY_MIICTRL_REG                         (0x17)

/*PHY Status Reg Link status bit position*/
#define ETH_PHY_INIT_DURATION                   (200U)
#define PHY_READ_DELAY                          (500U)
#define DELAY_30SEC                             (30000U)
#define ETH_FRAME_TYPE_1                        (0xABCDU)
#define ETH_IPADDRESS_LENGTH                    (4U)
#define ETH_ARPFRAME_DEST_IPADD_OFFSET          (24U)

/*PHY Interface Mode Value*/
#define RTL8211F_PHY_STATUS                     0x1a
#define RTL8211F_PAGE_SELECT                    0x1f
#define RTL8211F_TX_DELAY                       0x100

/* PHY Identifier Registers */
#define RTL8211F_PHY_ID1          (0x001cU)      /* PHY_ID1 for RTL8211F */
#define RTL8211F_PHY_ID2          (0xc916U)      /* PHY_ID2 for RTL8211F */
#define MII_BMCR                  0x00  /* Basic mode control register */
#define MII_PHYSID1               0x02  /* PHYS ID 1                   */
#define MII_PHYSID2               0x03  /* PHYS ID 2                   */
#define BMCR_RESET                0x8000  /* Reset to default state      */

/* Basic mode control register. */
#define BMCR_SPEED1000            0x0040  /* MSB of Speed (1000)         */
#define BMCR_FULLDPLX             0x0100  /* Full duplex                 */
#define BMCR_SPEED100             0x2000  /* Select 100Mbps              */
#define BMCR_SPEED10              0x0000  /* Select 10Mbps               */

/* Basic mode status register. */
#define ETH_FRAMEHEADER_LENGTH       (14U)
#define ETH_FRAMECHKSUM_LENGTH       (4U)
#define ETH_SHIFT_8BIT               (8U)
#define ETH_SHIFT_16BIT              (16U)
#define ETH_SHIFT_24BIT              (24U)
#define PHY_RESET                    0x00 
#define PHY_RESET_OK                 0x00
#define PHY_RESET_NOT_OK             0x01
#define PHY_CR2_ADDRESS              0x19
#define PHY_PAGE                     0xa43
#define MIICR_PAGE                   0xd08
#define RTL8211F_PHY_STATUS_LINK     0x0004
#define PHY_ID_VAL_NOT_OK            0x01 
#define PHY_ID_VAL_OK                0x00 
#define BMCR_ANENABLE                0x1000
#define BMCR_ANRESTART               0x0200


/******************************************************************************
**                      Private Type Definitions                             **
******************************************************************************/

/******************************************************************************
**                      Private Function Declarations                        **
******************************************************************************/

/******************************************************************************
**                      Global Constant Definitions                          **
******************************************************************************/
#if(MCAL_AR_VERSION == MCAL_AR_440)
/******************************************************************************
**                      Global Variable Definitions                          **
******************************************************************************/
#define ETH_17_GETHMACV2_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
#include "Eth_17_GEthMacV2_MemMap.h"

extern const Eth_17_GEthMacV2_ConfigType Eth_17_GEthMacV2_Config;

#define ETH_17_GETHMACV2_STOP_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
#include "Eth_17_GEthMacV2_MemMap.h"

uint16 Temp_Ret_RegVal_1 = 0;
/******************************************************************************
**                      Private Constant Definitions                         **
******************************************************************************/

/******************************************************************************
**                      Private Variable Definitions                         **
******************************************************************************/
#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED
#include "Eth_17_GEthMacV2_MemMap.h"

static Eth_BufIdxType TmpBuffIdx;
Eth_RxStatusType RxStatus;
volatile Std_ReturnType EthDemoRetVal;
static volatile BufReq_ReturnType Global_TempUSage1;

#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED
#include "Eth_17_GEthMacV2_MemMap.h"

#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_CORE0_32
#include "Eth_17_GEthMacV2_MemMap.h"

uint32 Src_IPaddress = 0xa9fefeab;

#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_CORE0_32
#include "Eth_17_GEthMacV2_MemMap.h"

#define ETH_17_GETHMACV2_START_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED
#include "Eth_17_GEthMacV2_MemMap.h"

static uint8* TmpBuffPtr;
uint8 ArpReply;
uint8 PromiscuousCheck;
uint8 Ret_MacAddr[ETH_MAC_ADD_LEN];
static uint8 Temp_Macaddress[6];

#define ETH_17_GETHMACV2_STOP_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED
#include "Eth_17_GEthMacV2_MemMap.h"

#define ETH_17_GETHMACV2_START_SEC_VAR_INIT_QM_LOCAL_8
#include "Eth_17_GEthMacV2_MemMap.h"

static uint8 MacDestArpaddress[6] =
{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; /*Broadcast*/

uint8 ArpData[28] =
{
  0x00, 0x01, 0x08, 0x00, 0x06, 0x04, 0x00, 0x01, 0x00, 0x03, 0x19, 0x00, 0x00, 0x01,
  0xa9, 0xfe, 0xfe, 0xab, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa9, 0xfe, 0xab, 0xa8
};
static uint8 MacDestBrodaddress[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

#define ETH_17_GETHMACV2_STOP_SEC_VAR_INIT_QM_LOCAL_8
#include "Eth_17_GEthMacV2_MemMap.h"

#else
	
#define ETH_17_GETHMAC_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
#include "Eth_17_GEthMac_MemMap.h"

extern const Eth_17_GEthMac_ConfigType Eth_17_GEthMac_Config;

#define ETH_17_GETHMAC_STOP_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
#include "Eth_17_GEthMac_MemMap.h"

uint16 Temp_Ret_RegVal_1 = 0;
/******************************************************************************
**                      Private Constant Definitions                         **
******************************************************************************/

/******************************************************************************
**                      Private Variable Definitions                         **
******************************************************************************/
#define ETH_17_GETHMAC_START_SEC_VAR_CLEARED_QM_GLOBAL_32
#include "Eth_17_GEthMac_MemMap.h"

static Eth_BufIdxType TmpBuffIdx;
Eth_RxStatusType RxStatus;
volatile Std_ReturnType EthDemoRetVal;
static volatile BufReq_ReturnType Global_TempUSage1;

#define ETH_17_GETHMAC_STOP_SEC_VAR_CLEARED_QM_GLOBAL_32
#include "Eth_17_GEthMac_MemMap.h"

#define ETH_17_GETHMAC_START_SEC_VAR_INIT_QM_CORE0_UNSPECIFIED
#include "Eth_17_GEthMac_MemMap.h"

uint32 Src_IPaddress = 0xa9fefeab;

#define ETH_17_GETHMAC_STOP_SEC_VAR_INIT_QM_CORE0_UNSPECIFIED
#include "Eth_17_GEthMac_MemMap.h"

#define ETH_17_GETHMAC_START_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED
#include "Eth_17_GEthMac_MemMap.h"

static uint8* TmpBuffPtr;
uint8 ArpReply;
uint8 PromiscuousCheck;
uint8 Ret_MacAddr[ETH_MAC_ADD_LEN];
static uint8 Temp_Macaddress[6];

#define ETH_17_GETHMAC_STOP_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED
#include "Eth_17_GEthMac_MemMap.h"

#define ETH_17_GETHMAC_START_SEC_VAR_INIT_QM_CORE0_UNSPECIFIED
#include "Eth_17_GEthMac_MemMap.h"

static uint8 MacDestArpaddress[6] =
{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; /*Broadcast*/

uint8 ArpData[28] =
{
  0x00, 0x01, 0x08, 0x00, 0x06, 0x04, 0x00, 0x01, 0x00, 0x03, 0x19, 0x00, 0x00, 0x01,
  0xa9, 0xfe, 0xfe, 0xab, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa9, 0xfe, 0xab, 0xa8
};
static uint8 MacDestBrodaddress[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

#define ETH_17_GETHMAC_STOP_SEC_VAR_INIT_QM_CORE0_UNSPECIFIED
#include "Eth_17_GEthMac_MemMap.h"
#endif
/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
#if(MCAL_AR_VERSION == MCAL_AR_440)
#define ETH_17_GETHMACV2_START_SEC_CODE_QM_GLOBAL
#include "Eth_17_GEthMacV2_MemMap.h"
#else
#define ETH_17_GETHMAC_START_SEC_CODE_QM_GLOBAL
#include "Eth_17_GEthMac_MemMap.h"
#endif
/*******************************************************************************
**    Fill Tx Buffer           **
*******************************************************************************/

void TxBufferFill(uint8 *pTxBuff, uint16 DataLen, uint8 *Framedatax )
{
  uint8 i = 0;

  for(; i < DataLen ; i++)
  {
    *(pTxBuff + i) = Framedatax[i];
  }

  return;
}

/*******************************************************************************
**    Transmit Arp Frame           **
*******************************************************************************/
void TransmitArpFrame(void)
{
  boolean Txstatus1 = 0;
  uint16 Tmp_Txlenghth1 = 28;
  #if(MCAL_AR_VERSION == MCAL_AR_440)
  uint8 Test_Priority = 0;
  Global_TempUSage1 = Eth_17_GEthMacV2_ProvideTxBuffer(0,Test_Priority, &TmpBuffIdx, &TmpBuffPtr, &Tmp_Txlenghth1);
  #else
  Global_TempUSage1 = Eth_17_GEthMac_ProvideTxBuffer(0, &TmpBuffIdx, &TmpBuffPtr, &Tmp_Txlenghth1);
  #endif
  
  if (Global_TempUSage1 == BUFREQ_OK)
  {
    print_f("\n BUFREQ_OK ");
  }
  else if (Global_TempUSage1 == BUFREQ_E_NOT_OK)
  {
    print_f("\n BUFREQ_E_NOT_OK ");
  }
  else if (Global_TempUSage1 == BUFREQ_E_BUSY)
  {
    print_f("\n BUFREQ_E_BUSY ");
  }
  else if (Global_TempUSage1 == BUFREQ_E_OVFL)
  {
    print_f("\n BUFREQ_E_OVFL ");
  }

  TxBufferFill(TmpBuffPtr, Tmp_Txlenghth1, ArpData);
  
  #if(MCAL_AR_VERSION == MCAL_AR_440)
  EthDemoRetVal = Eth_17_GEthMacV2_Transmit(0, TmpBuffIdx, ETH_ARP_PROTOCOL, \
  Txstatus1, Tmp_Txlenghth1, &MacDestBrodaddress[0]);
  #else
  EthDemoRetVal = Eth_17_GEthMac_Transmit(0, TmpBuffIdx, ETH_ARP_PROTOCOL, \
  Txstatus1, Tmp_Txlenghth1, &MacDestBrodaddress[0]);
  #endif
  
  if(EthDemoRetVal == E_OK)
  {
    print_f("\n GEthMac Transmit SUCCESS");
  }
  else
  {
    print_f("\n GEthMac Transmit Failed");
  }
}

/*******************************************************************************
**    Initialise Eth Driver including PHY        **
*******************************************************************************/

void Test_GEthControllerInit (void)
{
  #if(MCAL_AR_VERSION == MCAL_AR_440)
  if(Eth_17_GEthMacV2_SetControllerMode(0, ETH_MODE_ACTIVE) == E_OK)
  #else
  if(Eth_17_GEthMac_SetControllerMode(0, ETH_MODE_ACTIVE) == E_OK)
  #endif
  {
    print_f("\n\n GEthMAC SetControllerMode Success ");
  }
  else 
  {
    print_f("\n\n GEthMac SetControllerMode Failed ");
  }
  
  print_f("\n\n ENTER GEthMac GetPhysAddr ");
  #if(MCAL_AR_VERSION == MCAL_AR_440)
  Eth_17_GEthMacV2_GetPhysAddr((uint8)0, &Temp_Macaddress[0]);
  #else
  Eth_17_GEthMac_GetPhysAddr((uint8)0, &Temp_Macaddress[0]);
  #endif

  print_f("\n\n GEthMac GetPhysAddr =%x:%x:%x:%x:%x:%x", Temp_Macaddress[0], \
   Temp_Macaddress[1], Temp_Macaddress[2], Temp_Macaddress[3], Temp_Macaddress[4], Temp_Macaddress[5]);
}
/*******************************************************************************
**    Ping Application                                            **
*******************************************************************************/
void Ping_App(void)
{
  uint8 i;
  char param[20];
  char szString1[20];
  char *pszString1;
  uint32 paramArray[6];
  volatile uint32 TimeoutCntr = 0;
  uint8 paramCount = 0, charCount = 0;
  #if(MCAL_AR_VERSION == MCAL_AR_440)
  uint8 Test_FifoIdx = 0;
  #endif

  print_f("\n\n Enter IP Address to Ping(Your PC IP) : ");
  getline(szString1, sizeof szString1 - 1);
  pszString1 = &szString1[0];

  do
  {
    /* Look for the '.' delimiter */
    if (*pszString1 != '.')
    {
      param[charCount++] = (char) * pszString1;
    }
    else
    {
      param[charCount] = 0;
      paramArray[paramCount] = (uint32)atoi(param);
      paramCount++;
      charCount = 0;
    }
    pszString1++;
  } while (*pszString1 != '\0');

  print_f("\n After Do while Loop ");
  param[charCount] = 0;
  paramArray[paramCount] = (uint32) atoi(param);

  for(i = 0; i < ETH_IPADDRESS_LENGTH; i++)
  {
    ArpData[ETH_ARPFRAME_DEST_IPADD_OFFSET + i] = (uint8)paramArray[i];
  }

  Src_IPaddress = (((paramArray[0] & 0xFF) << ETH_SHIFT_24BIT) |  \
  ((paramArray[1] & 0xFF) << ETH_SHIFT_16BIT) | ((paramArray[2] & 0xFF) << ETH_SHIFT_8BIT) \
   | (paramArray[3] & 0xFF));

  print_f("\n Enter TransmitArpFrame() ");
  TransmitArpFrame();
  print_f("\n Exit TransmitArpFrame() ");

  do
  {
	#if(MCAL_AR_VERSION == MCAL_AR_440)
    Eth_17_GEthMacV2_Receive(0, Test_FifoIdx, (Eth_RxStatusType* )&RxStatus);
    #else
	Eth_17_GEthMac_Receive(0, (Eth_RxStatusType* )&RxStatus);
	#endif
    Timer_DelayMs(1);
    TimeoutCntr++;
  } while(( ArpReply != 1) && (DELAY_30SEC != TimeoutCntr));

  if(ArpReply == 1)
  {
    print_f("\n ArpReply OK\n  ");
    ArpReply = 0;
    StartResult();
    print_f("Result = Pass;");
    EndResult();
  }
  else
  {
    print_f("\n Destination Host Unreachable\n  ");
    print_f("Reason 1: Ethernet Cross Wire is NOT connected between AURIX Tri-Board and Your PC\n ");
    print_f("Reason 2: IP Address Entered is Wrong\n ");
    StartResult();
    print_f("Result = Fail;");
    EndResult();
  }
}

/*******************************************************************************
**    Promiscuous mode Receive all Frames                                     **
*******************************************************************************/
void Receive_Poll (void)
{
  volatile uint32 TimeoutCntr = 0;
  #if(MCAL_AR_VERSION == MCAL_AR_440)
  uint8 Test_FifoIdx = 0;

  Eth_17_GEthMacV2_GetPhysAddr(0, Ret_MacAddr);

  /* Update filter for Open filter mode */
  Eth_17_GEthMacV2_UpdatePhysAddrFilter(0, (uint8*)&MacDestBrodaddress, ETH_ADD_TO_FILTER);

  do
  {
    Eth_17_GEthMacV2_Receive(0, Test_FifoIdx, (Eth_RxStatusType* )&RxStatus);
    Timer_DelayMs(1);
    TimeoutCntr++;
  }
  #else
  Eth_17_GEthMac_GetPhysAddr(0, Ret_MacAddr);

  /* Update filter for Open filter mode */
  Eth_17_GEthMac_UpdatePhysAddrFilter(0, (uint8*)&MacDestBrodaddress, ETH_ADD_TO_FILTER);

  do
  {
    Eth_17_GEthMac_Receive(0, (Eth_RxStatusType* )&RxStatus);
    Timer_DelayMs(1);
    TimeoutCntr++;
  }
  #endif
  while(DELAY_30SEC != TimeoutCntr);
  /* Wait for 30 secs to receive frames */

  if((Test_EthRxConfirmCount[0])&&(PromiscuousCheck))
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

/*******************************************************************************
**    Transmit ETH Frame of User Defined Length                               **
*******************************************************************************/
void Tx_EthFrame (void)
{
  volatile uint32 TimeoutCntr;
  char szString[80];
  uint16 TmpTxlength, i;
  uint8 *TmpEthTxBuffPtr;
  #if(MCAL_AR_VERSION == MCAL_AR_440)
  uint8 Test_Priority = 0;
  #endif
  Test_EthTxConfirmCount[0] = 0;

  print_f("\n\n Enter ETH Frame Payload Length(42...1500) : ");
  getline(szString, sizeof szString - 1);

  TmpTxlength = (uint16)atoi(szString);
  #if(MCAL_AR_VERSION == MCAL_AR_440)
  Global_TempUSage1 = Eth_17_GEthMacV2_ProvideTxBuffer(0, Test_Priority, &TmpBuffIdx, \
   &TmpEthTxBuffPtr, &TmpTxlength);
  #else
  Global_TempUSage1 = Eth_17_GEthMac_ProvideTxBuffer(0, &TmpBuffIdx, \
   &TmpEthTxBuffPtr, &TmpTxlength);
  #endif

  for (i = 0; i < TmpTxlength ; i++)
  {
    *TmpEthTxBuffPtr = i + 1;
    TmpEthTxBuffPtr += 1;
  }
  #if(MCAL_AR_VERSION == MCAL_AR_440)
  EthDemoRetVal = Eth_17_GEthMacV2_Transmit(0, TmpBuffIdx, ETH_FRAME_TYPE_1, \
   1, TmpTxlength, &MacDestArpaddress[0]);
  #else
  EthDemoRetVal = Eth_17_GEthMac_Transmit(0, TmpBuffIdx, ETH_FRAME_TYPE_1, \
   1, TmpTxlength, &MacDestArpaddress[0]);
  #endif

  TimeoutCntr = 0x7FFFFF;

   do
  {
	#if(MCAL_AR_VERSION == MCAL_AR_440)
    Eth_17_GEthMacV2_TxConfirmation(0);
    #else
	Eth_17_GEthMac_TxConfirmation(0);
    #endif
  }
  while((!Test_EthTxConfirmCount[0])&&(TimeoutCntr--));

  if(Test_EthTxConfirmCount[0])
  {
    print_f("\n Transmitted ETH Frame of FrameType 0xABCD");
    print_f("\n Payload Length %d bytes and Total Frame Length %d bytes\n", \
    TmpTxlength, (TmpTxlength + ETH_FRAMEHEADER_LENGTH + ETH_FRAMECHKSUM_LENGTH));
    Test_EthTxConfirmCount[0] = 0;

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

/*******************************************************************************
**    Read PHY Registers                          **
*******************************************************************************/
void Read_PhyReg (void)
{
  uint16 Ret_RegVal;
  uint8 EthTest_CtrlIdx = 0,ErrCnt = 0;
  #if(MCAL_AR_VERSION == MCAL_AR_440)
  Std_ReturnType Return_Type1 = E_NOT_OK;
  #else
  Eth_ReturnType Return_Type1 = ETH_E_NOT_OK;
  #endif
  
  #if(MCAL_AR_VERSION == MCAL_AR_440)
  #if(ETH_17_GETHMACV2_ENA_MII_API == STD_ON)
  Std_ReturnType  Return_Type2 = E_NOT_OK;

  Return_Type1 =  Eth_17_GEthMacV2_ReadMii(EthTest_CtrlIdx, 1, 0x01, &Ret_RegVal);

  if(Return_Type1 == E_OK)
  {  print_f("\nReg Value Read from Ethernet PHY RegIdx 1 (Basic Mode Status REG): 0x%x \n ", Ret_RegVal);}
  else
  {ErrCnt++;}

  Return_Type2 = Eth_17_GEthMacV2_WriteMii(EthTest_CtrlIdx, 1, RTL8211F_PAGE_SELECT, 0xa43);
  Return_Type1 =  Eth_17_GEthMacV2_ReadMii(EthTest_CtrlIdx, 1, 0x18, &Ret_RegVal);

  if((Return_Type1 == E_OK) && (Return_Type2 == E_OK) )
  { print_f("Reg Value Read from Ethernet PHY RegIdx 19 (PHY_PHYCTL1_REG): 0x%x \n ", Ret_RegVal);}
  else
  {ErrCnt++;}

  Return_Type1 =  Eth_17_GEthMacV2_ReadMii(EthTest_CtrlIdx, 1, 0x19, &Ret_RegVal);
  if(Return_Type1 == E_OK)
  { print_f("Reg Value Read from Ethernet PHY RegIdx 20 (PHY_PHYCTL2_REG): 0x%x \n ", Ret_RegVal);}
  else
  {ErrCnt++;}

  Return_Type2 = Eth_17_GEthMacV2_WriteMii(EthTest_CtrlIdx, 1, RTL8211F_PAGE_SELECT, 0x0);
  if (Return_Type2 != E_OK)
  { print_f("\n Error in writing PageSelect Register\n");
    ErrCnt++;}

  Return_Type2 = Eth_17_GEthMacV2_WriteMii(EthTest_CtrlIdx, 1, RTL8211F_PAGE_SELECT, 0xd08);
  Return_Type1 =  Eth_17_GEthMacV2_ReadMii(EthTest_CtrlIdx, 1, 0x15, &Ret_RegVal);

  if((Return_Type1 == E_OK) && (Return_Type2 == E_OK) )
  { print_f("Reg Value Read from Ethernet PHY RegIdx 23 (PHY_MIICTRL_REG): 0x%x \n ", Ret_RegVal);}
  else
  {ErrCnt++;}

  Return_Type2 = Eth_17_GEthMacV2_WriteMii(EthTest_CtrlIdx, 1, RTL8211F_PAGE_SELECT, 0x0);
  if (Return_Type2 != E_OK)
  { print_f("\n Error in writing PageSelect Register\n");
    ErrCnt++;}
  #endif
  #else /*AS422*/
  #if(ETH_17_GETHMAC_ENA_MII_API == STD_ON)
  Eth_ReturnType  Return_Type2 = ETH_E_NOT_OK;

  Return_Type1 =  Eth_17_GEthMac_ReadMii(EthTest_CtrlIdx, 1, 0x01, &Ret_RegVal);

  if(Return_Type1 == E_OK)
  {  print_f("\nReg Value Read from Ethernet PHY RegIdx 1 (Basic Mode Status REG): 0x%x \n ", Ret_RegVal);}
  else
  {ErrCnt++;}
  Return_Type2 = Eth_17_GEthMac_WriteMii(EthTest_CtrlIdx, 1, RTL8211F_PAGE_SELECT, 0xa43);
  Return_Type1 =  Eth_17_GEthMac_ReadMii(EthTest_CtrlIdx, 1, 0x18, &Ret_RegVal);

  if((Return_Type1 == E_OK) && (Return_Type2 == E_OK) )
  { print_f("Reg Value Read from Ethernet PHY RegIdx 19 (PHY_PHYCTL1_REG): 0x%x \n ", Ret_RegVal);}
  else
  {ErrCnt++;}

  Return_Type1 =  Eth_17_GEthMac_ReadMii(EthTest_CtrlIdx, 1, 0x19, &Ret_RegVal);
  if(Return_Type1 == E_OK)
  { print_f("Reg Value Read from Ethernet PHY RegIdx 20 (PHY_PHYCTL2_REG): 0x%x \n ", Ret_RegVal);}
  else
  {ErrCnt++;}

  Return_Type2 = Eth_17_GEthMac_WriteMii(EthTest_CtrlIdx, 1, RTL8211F_PAGE_SELECT, 0x0);
  if (Return_Type2 != E_OK)
  { print_f("\n Error in writing PageSelect Register\n");
    ErrCnt++;}

  Return_Type2 = Eth_17_GEthMac_WriteMii(EthTest_CtrlIdx, 1, RTL8211F_PAGE_SELECT, 0xd08);
  Return_Type1 =  Eth_17_GEthMac_ReadMii(EthTest_CtrlIdx, 1, 0x15, &Ret_RegVal);

  if((Return_Type1 == E_OK) && (Return_Type2 == E_OK) )
  { print_f("Reg Value Read from Ethernet PHY RegIdx 23 (PHY_MIICTRL_REG): 0x%x \n ", Ret_RegVal);}
  else
  {ErrCnt++;}

  Return_Type2 = Eth_17_GEthMac_WriteMii(EthTest_CtrlIdx, 1, RTL8211F_PAGE_SELECT, 0x0);
  if (Return_Type2 != E_OK)
  { print_f("\n Error in writing PageSelect Register\n");
    ErrCnt++;}
  #endif
  #endif
  if(!ErrCnt)
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

/******************************************************************************
* Function Name : RTL8211F_IsPhyIdValid()*
* Description   : Function to validate RTL8211F PHY ID                        *
*******************************************************************************/
sint32 RTL8211F_IsPhyIdValid(void)
{
  uint16 phy_id1=0;
  uint16 phy_id2=0;
  #if(MCAL_AR_VERSION == MCAL_AR_440)
  /* Read PHY device Identification ID1. */
  if(Eth_17_GEthMacV2_ReadMii(0, 1, MII_PHYSID1, &phy_id1)!= 0)
  {
      return ETH_PHY_STATUS_ERROR;
  }
   /* Read PHY Device Identification ID2. */
  if(Eth_17_GEthMacV2_ReadMii(0, 1, MII_PHYSID2, &phy_id2)!= 0)
  {
      return ETH_PHY_STATUS_ERROR;
  }
  #else
  /* Read PHY device Identification ID1. */
  if(Eth_17_GEthMac_ReadMii(0, 1, MII_PHYSID1, &phy_id1)!= 0)
  {
      return ETH_PHY_STATUS_ERROR;
  }
   /* Read PHY Device Identification ID2. */
  if(Eth_17_GEthMac_ReadMii(0, 1, MII_PHYSID2, &phy_id2)!= 0)
  {
      return ETH_PHY_STATUS_ERROR;
  }
   #endif
  /* Verify PHY Device ID1 & ID2. */
  if((phy_id1 == RTL8211F_PHY_ID1) && (phy_id2 == RTL8211F_PHY_ID2))
  {
      return PHY_ID_VAL_OK;
  }

  return PHY_ID_VAL_NOT_OK;
}

/******************************************************************************
* Function Name : RTL8211F_PhyReset()*
* Description   : Function to do RTL8211F PHY software reset                  *
*******************************************************************************/
sint32 RTL8211F_PhyReset(void)
{
  uint16 reg_bmcr;
  #if(MCAL_AR_VERSION == MCAL_AR_440)
  /* Reset PHY*/
  if(Eth_17_GEthMacV2_ReadMii(0, 1, MII_BMCR, &reg_bmcr)!= 0)
  #else
  if(Eth_17_GEthMac_ReadMii(0, 1, MII_BMCR, &reg_bmcr)!= 0)
  #endif
  {
     return ETH_PHY_STATUS_ERROR; 
  }
    
  reg_bmcr |= BMCR_RESET;
  #if(MCAL_AR_VERSION == MCAL_AR_440)
  if(Eth_17_GEthMacV2_WriteMii(0, 1, MII_BMCR, reg_bmcr)!= 0)
  #else
  if(Eth_17_GEthMac_WriteMii(0, 1, MII_BMCR, reg_bmcr)!= 0)
  #endif
  {
     return ETH_PHY_STATUS_ERROR;  
  }

  return ETH_PHY_STATUS_OK;
}

/******************************************************************************
* Function Name : RTL8211F_PhyResetCheck()*
* Description   : Function to check the status of RTL8211F PHY software reset *
*******************************************************************************/
sint32 RTL8211F_PhyResetCheck(void)
{
  uint16 reg_bmcr;
  #if(MCAL_AR_VERSION == MCAL_AR_440)
  /*Check PHY reset status*/
  if(Eth_17_GEthMacV2_ReadMii(0, 1, MII_BMCR, &reg_bmcr)!= 0)
  #else
  if(Eth_17_GEthMac_ReadMii(0, 1, MII_BMCR, &reg_bmcr)!= 0)
  #endif
  {
      return ETH_PHY_STATUS_ERROR; 
  }
  if((reg_bmcr & BMCR_RESET) == PHY_RESET)
  {
      return PHY_RESET_OK;
  }

  return PHY_RESET_NOT_OK;
}

/******************************************************************************
* Function Name : RTL8211F_PhyInit()*
* Description   : Function to do initialization of RTL8211F PHY*
*******************************************************************************/
sint32 RTL8211F_PhyInit(void)
{
  uint16 reg_value = 0;
  uint16 reg_bmcr = 0;
  uint32 retries = 0xffffffff;
  #if(MCAL_AR_VERSION == MCAL_AR_440)
  /* Validate PHY Device ID. */
  while ((RTL8211F_IsPhyIdValid() != PHY_ID_VAL_OK) && (--retries)){}
  
  if (retries == 0)
  {
    return ETH_PHY_STATUS_ERROR_ID;
  }
  
  /*Enable CLKOUT @125MHz */
  /*Select the PHY page for the register PHY_CR2_ADDRESS*/
  Eth_17_GEthMacV2_WriteMii(0, 1, RTL8211F_PAGE_SELECT, PHY_PAGE);
  Eth_17_GEthMacV2_ReadMii(0, 1, PHY_CR2_ADDRESS, &reg_value);
  reg_value |= 0x1;
  Eth_17_GEthMacV2_WriteMii(0, 1, PHY_CR2_ADDRESS, reg_value);
  
  /* restore to default page 0 */
  Eth_17_GEthMacV2_WriteMii(0, 1, RTL8211F_PAGE_SELECT, 0x0);
  
  /* A PHY reset should be issued after setting this bits in PHY_CR2_ADDRESS */
  RTL8211F_PhyReset();
  
  /*Veirfy the phy reset is ok or not*/
  while (RTL8211F_PhyResetCheck() != PHY_RESET_OK){}
  
  /*RTL8211F_TX_DELAY delay to be added*/
  Eth_17_GEthMacV2_WriteMii(0, 1, RTL8211F_PAGE_SELECT, MIICR_PAGE);
  Eth_17_GEthMacV2_ReadMii(0, 1, 0x11, &reg_value);
  reg_value |= RTL8211F_TX_DELAY;  
  Eth_17_GEthMacV2_WriteMii(0, 1, 0x11, reg_value);	
  
  /*restore to default page 0 */
  Eth_17_GEthMacV2_WriteMii(0, 1, RTL8211F_PAGE_SELECT, 0x0);
  
  /*Reading the value of Basic mode control register*/
  Eth_17_GEthMacV2_ReadMii(0, 1, MII_BMCR, &reg_bmcr);
 
  /*Configure Ethernet speed to 1Gbps*/
  print_f ("Configured 1000 Mbps \n");
  reg_value |= BMCR_SPEED1000;
  
  /*Configure Ethernet mode to Full Duplex*/
  print_f ("Configured Full Duplex \n");
  reg_value |= BMCR_FULLDPLX;
  
  /*Setting the value to Basic mode control register*/
  Eth_17_GEthMacV2_WriteMii(0, 1, MII_BMCR, reg_value);
  
  /*Enable Auto Negotiation*/
  reg_bmcr |= BMCR_ANENABLE;
  Eth_17_GEthMacV2_WriteMii(0, 1, MII_BMCR, reg_bmcr);

  /*Software reset is asserted, Restart AN or power mode transition*/
  reg_bmcr |= BMCR_ANRESTART;
  Eth_17_GEthMacV2_WriteMii(0, 1, MII_BMCR, reg_bmcr);
  #else
  /* Validate PHY Device ID. */
  while ((RTL8211F_IsPhyIdValid() != PHY_ID_VAL_OK) && (--retries)) {}
  
  if (retries == 0)
  {
    return ETH_PHY_STATUS_ERROR_ID;
  }
  
  /*Enable CLKOUT @125MHz */
  /*Select the PHY page for the register PHY_CR2_ADDRESS*/
  Eth_17_GEthMac_WriteMii(0, 1, RTL8211F_PAGE_SELECT, PHY_PAGE);
  Eth_17_GEthMac_ReadMii(0, 1, PHY_CR2_ADDRESS, &reg_value);
  reg_value |= 0x1;
  Eth_17_GEthMac_WriteMii(0, 1, PHY_CR2_ADDRESS, reg_value);
  
  /* restore to default page 0 */
  Eth_17_GEthMac_WriteMii(0, 1, RTL8211F_PAGE_SELECT, 0x0);
  
  /* A PHY reset should be issued after setting this bits in PHY_CR2_ADDRESS */
  RTL8211F_PhyReset();
  
  /*Veirfy the phy reset is ok or not*/
  while (RTL8211F_PhyResetCheck() != PHY_RESET_OK) {}
  
  /*RTL8211F_TX_DELAY delay to be added*/
  Eth_17_GEthMac_WriteMii(0, 1, RTL8211F_PAGE_SELECT, MIICR_PAGE);
  Eth_17_GEthMac_ReadMii(0, 1, 0x11, &reg_value);
  reg_value |= RTL8211F_TX_DELAY;  
  Eth_17_GEthMac_WriteMii(0, 1, 0x11, reg_value);
  
  /*restore to default page 0 */
  Eth_17_GEthMac_WriteMii(0, 1, RTL8211F_PAGE_SELECT, 0x0);
  
  /*Reading the value of Basic mode control register*/
  Eth_17_GEthMac_ReadMii(0, 1, MII_BMCR, &reg_bmcr);
 
  /*Configure Ethernet speed to 1Gbps*/
  print_f ("Configured 1000 Mbps \n");
  reg_value |= BMCR_SPEED1000;
  
  /*Configure Ethernet mode to Full Duplex*/
  print_f ("Configured Full Duplex \n");
  reg_value |= BMCR_FULLDPLX;
  
  /*Setting the value to Basic mode control register*/
  Eth_17_GEthMac_WriteMii(0, 1, MII_BMCR, reg_value);
  
  /*Enable Auto Negotiation*/
  reg_bmcr |= BMCR_ANENABLE;
  Eth_17_GEthMac_WriteMii(0, 1, MII_BMCR, reg_bmcr);

  /*Software reset is asserted, Restart AN or power mode transition*/
  reg_bmcr |= BMCR_ANRESTART;
  Eth_17_GEthMac_WriteMii(0, 1, MII_BMCR, reg_bmcr);
  #endif
  return ETH_PHY_STATUS_OK;
}

/******************************************************************************
* Function Name : RTL8211F_GetPhyLinkStatus()*
* Description   : Function to get the link status of the RTL8211F PHY*
*******************************************************************************/
sint32 RTL8211F_GetPhyLinkStatus(void)
{
  uint16 reg_value = 0;
   #if(MCAL_AR_VERSION == MCAL_AR_440)
   Eth_17_GEthMacV2_WriteMii(0, 1, RTL8211F_PAGE_SELECT, PHY_PAGE);
   Eth_17_GEthMacV2_ReadMii(0, 1, RTL8211F_PHY_STATUS, &reg_value);
  
   /* restore to default page 0 */
   Eth_17_GEthMacV2_WriteMii(0, 1, RTL8211F_PAGE_SELECT, 0);
   #else
   Eth_17_GEthMac_WriteMii(0, 1, RTL8211F_PAGE_SELECT, PHY_PAGE);
   Eth_17_GEthMac_ReadMii(0, 1, RTL8211F_PHY_STATUS, &reg_value);
  
   /* restore to default page 0 */
   Eth_17_GEthMac_WriteMii(0, 1, RTL8211F_PAGE_SELECT, 0);
   #endif
  return ((reg_value & RTL8211F_PHY_STATUS_LINK) ? ETH_PHY_LINK_STATUS_UP : ETH_PHY_LINK_STATUS_DOWN);
}

/******************************************************************************
* Function Name : Test_GEthPhyInit()                           *
* Description   : Test funtion to Initialize ETHERNET module*
*******************************************************************************/
void Test_GEthPhyInit(void)
{
  print_f("\n Calling EthMAC Init API;\n\n");
  #if(MCAL_AR_VERSION == MCAL_AR_440)
  Eth_17_GEthMacV2_Init(&Eth_17_GEthMacV2_Config);
  #else
  Eth_17_GEthMac_Init(&Eth_17_GEthMac_Config);
  #endif
  print_f("\n  EthMAC Init API; Done \n\n");
  
  while(RTL8211F_PhyInit()!=ETH_PHY_STATUS_OK) {}
  print_f("\n\n ETH Driver Initialised Successfully!! ");
  
  while(RTL8211F_GetPhyLinkStatus()!= ETH_PHY_LINK_STATUS_UP) {}
  print_f("\n\n Ethernet LINK UP ");

  /*Delay added since ETh_init takes time to stabilize */
  Timer_DelayMs(ETH_PHY_INIT_DURATION);
}

/*******************************************************************************
** Syntax : void Eth_17_Demo(void)                                            **
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
** Description : Ethernet Demo Application                                   **
*******************************************************************************/
#if(MCAL_AR_VERSION == MCAL_AR_440)
void EthV2_17_Demo(void)
#else
void Eth_17_Demo(void)
#endif
{
  char szString[10];
  volatile uint8 loopvar = 0;

  /* Initialise Eth Driver including Realtek 8211F PHY */
  Test_GEthPhyInit(); 
  
  /* Initializes the Mac controller */
  Test_GEthControllerInit(); 

  while (loopvar == 0)
  {
    print_f("\n\n\n");
    print_f("\n/*********************************************************/\n");
    print_f("\n           ETH DRIVER DEMO MENU                          ");
    print_f("\n                                                         ");
    print_f("\n  <1> :Promiscuous Mode: Receive All Frames ");
    print_f("\n  <2> :PING Application"     );
    print_f("\n  <3> :Transmit ETH Frame of User Defined Payload Length");
    print_f("\n  <4> :Read PHY Registers ");
    print_f("\n  <x> :Go back to Main Menu    \n");
    print_f("\n  ENTER YOUR OPTION   : ");

    getline(szString, sizeof szString - 1);

    switch (*szString)
    {
      case '1':
        Receive_Poll();
        break;

      case '2':
        Ping_App();
        print_f("\n  EXIT   Ping_App(); : ");
        break;

      case '3':
        Tx_EthFrame();
        break;

      case '4':
        Read_PhyReg();
        break;

      case 'x':
        loopvar = 1;
        break;

      default:
        print_f("\n\n  INVALID OPTION");
        break;
    }/* End of Case */
  }/* End of While loop */
}


#if(MCAL_AR_VERSION == MCAL_AR_440)
#define ETH_17_GETHMACV2_STOP_SEC_CODE_QM_GLOBAL
#include "Eth_17_GEthMacV2_MemMap.h"
#else
#define ETH_17_GETHMAC_STOP_SEC_CODE_QM_GLOBAL
#include "Eth_17_GEthMac_MemMap.h"
#endif
