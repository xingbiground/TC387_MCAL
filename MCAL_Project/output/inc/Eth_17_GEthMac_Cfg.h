/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2023)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Eth_17_GEthMac_Cfg.h                                          **
**                                                                            **
**  VERSION   : 19.0.0                                                        **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:31      !!!IGNORE-LINE!!!               **
**                                                                            **
**  GENERATOR : Build b191017-0938          !!!IGNORE-LINE!!!               **
**                                                                            **
**  BSW MODULE DECRIPTION : NA                                                **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Eth configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Eth Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef ETH_17_GETHMAC_CFG_H
#define ETH_17_GETHMAC_CFG_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
#define ETH_17_GETHMAC_AR_RELEASE_MAJOR_VERSION      (4U)
#define ETH_17_GETHMAC_AR_RELEASE_MINOR_VERSION      (2U)
#define ETH_17_GETHMAC_AR_RELEASE_REVISION_VERSION   (2U)

#define ETH_17_GETHMAC_SW_MAJOR_VERSION              (20U)
#define ETH_17_GETHMAC_SW_MINOR_VERSION              (25U)
#define ETH_17_GETHMAC_SW_PATCH_VERSION              (0U)

/*
Configuration: ETH_17_GETHMAC_DEV_ERROR_DETECT
- if STD_ON, DET is Enabled
- if STD_OFF,DET is Disabled
This parameter shall activate or
deactivate the detection of all development errors.
*/
#define ETH_17_GETHMAC_DEV_ERROR_DETECT  (STD_ON)

/*
Configuration: ETH_17_GETHMAC_VERSION_INFO_API
- if STD_ON, Function Eth_17_GetVersionInfo is available
- if STD_OFF,Function Eth_17_GetVersionInfo is not available
*/
#define ETH_17_GETHMAC_VERSION_INFO_API  (STD_ON)

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#ifndef Eth_17_GEthMacConf_EthCtrlConfig_EthCtrlConfig_0
/* Macro to hold index of the configured controller */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define Eth_17_GEthMacConf_EthCtrlConfig_EthCtrlConfig_0 (0U)
#endif
/*
Configuration: ETH_17_GETHMAC_INDEX
- Ethernet Driver Instance ID, used in DET_Report(.,.) Interface.
*/
#define ETH_17_GETHMAC_INDEX (0U)
/*
Configuration: ETH_17_GETHMAC_ENA_MII_API
- if STD_ON, Functions Eth_17_WriteMii,Eth_17_ReadMii are available
- if STD_OFF,Functions Eth_17_WriteMii,Eth_17_ReadMii are not available
*/
#define ETH_17_GETHMAC_ENA_MII_API  (STD_ON)
/*
Configuration:  ETH_17_GETHMAC_DEM_ENABLED
ETH_17_GETHMAC_ENABLE_DEM_REPORT - Production error reporting enabled.
ETH_17_GETHMAC_DISABLE_DEM_REPORT - Production error reporting disabled
*/
#define ETH_17_GETHMAC_DEM_ENABLED  (ETH_17_GETHMAC_ENABLE_DEM_REPORT)
/* Maximum time in nanoseconds to wait for hardware timeout errors*/
#define ETH_17_GETHMAC_MAXTIMEOUT_COUNT  (4294967295U)

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* No of receive buffer for controller0 */
#define ETH_17_GETHMAC_CNTRL0_RXBUFFER_COUNT      (4U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* Size of the receive buffer for controller0 */
#define ETH_17_GETHMAC_CNTRL0_RXBUFFER_SIZE       (6112U)

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* No of transmit buffer for controller0 */
#define ETH_17_GETHMAC_CNTRL0_TXBUFFER_COUNT      (4U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* Size of the transmit buffer for controller0 */
#define ETH_17_GETHMAC_CNTRL0_TXBUFFER_SIZE       (6112U)

/* fSPB (SPB frequency) period in nanoseconds */
#define ETH_17_GETHMAC_FSPB_PERIOD_IN_NANOSEC   (10U)

/* fGETH frequency in Hz - basic frequency for the Gigabit Ethernet Kernel */
#define ETH_17_GETHMAC_FGETH_IN_HZ              (150000000U)

/* Wait time in nanoseconds after a kernel reset in RGMII mode */
#define ETH_17_GETHMAC_KRNLRST_RGMII_WAITCNT    (350U)

/* Wait time in nanoseconds after a kernel reset in MII/ RMII mode */
#define ETH_17_GETHMAC_KRNLRST_MII_WAITCNT      (700U)

/* Number of fSPB cycles to wait after a DMA software reset */
#define ETH_17_GETHMAC_DMA_RESET_WAITCYCLE      (4U)

/*
Configuration: ETH_17_GETHMAC_GETDROPCOUNT_API
- if STD_ON, Function Eth_17_GEthMac_GetDropCount is available
- if STD_OFF,Function Eth_17_GEthMac_GetDropCount is not available
*/
#define  ETH_17_GETHMAC_GETDROPCOUNT_API    (STD_ON)
/*
Configuration: ETH_17_GETHMAC_GETETHERSTATS_API
- if STD_ON, Function Eth_17_GEthMac_GetEtherStats is available
- if STD_OFF,Function Eth_17_GEthMac_GetEtherStats is not available
*/
#define  ETH_17_GETHMAC_GETETHERSTATS_API   (STD_ON)

/*
Configuration: ETH_17_GETHMAC_GLOBALTIMESUPPORT
- if STD_ON, TimeStamp feature is enabled.
- if STD_OFF,TimeStamp feature is disabled.
*/
#define  ETH_17_GETHMAC_GLOBALTIMESUPPORT   (STD_OFF)
/*
Configuration: ETH_17_GETHMAC_MULTICORE_ERROR_DETECT :
Adds/removes the Multi-core error detection and reporting
from the code
- if STD_ON, Multi-core error detection and reporting is enabled
- if STD_OFF, Multi-core error detection and reporting is disabled
*/
#define ETH_17_GETHMAC_MULTICORE_ERROR_DETECT           (STD_ON)

/*
Configuration: ETH_17_GETHMAC_ICMP_CHECKSUMOFFLOAD_ENABLE
- if STD_ON, Hardware offloading for ICMP checksums is enabled.
- if STD_OFF,Hardware offloading for ICMP checksums is disabled.
*/
#define ETH_17_GETHMAC_ICMP_CHECKSUMOFFLOAD_ENABLE  (STD_OFF)

/*
Configuration: ETH_17_GETHMAC_IPV4_CHECKSUMOFFLOAD_ENABLE
- if STD_ON, Hardware offloading for IPV4 checksums is enabled.
- if STD_OFF,Hardware offloading for IPV4 checksums is disabled.
*/
#define ETH_17_GETHMAC_IPV4_CHECKSUMOFFLOAD_ENABLE  (STD_OFF)

/*
Configuration: ETH_17_GETHMAC_TCP_CHECKSUMOFFLOAD_ENABLE
- if STD_ON, Hardware offloading for TCP checksums is enabled.
- if STD_OFF,Hardware offloading for TCP checksums is disabled.
*/
#define ETH_17_GETHMAC_TCP_CHECKSUMOFFLOAD_ENABLE   (STD_OFF)

/*
Configuration: ETH_17_GETHMAC_UDP_CHECKSUMOFFLOAD_ENABLE
- if STD_ON, Hardware offloading for UDP checksums is enabled.
- if STD_OFF,Hardware offloading for UDP checksums is disabled.
*/
#define ETH_17_GETHMAC_UDP_CHECKSUMOFFLOAD_ENABLE   (STD_OFF)

/*
Configuration: ETH_17_GETHMAC_UPDATE_PHY_ADDR_FILTER_API
- if STD_ON, Function Eth_17_GEthMac_UpdatePhysAddrFilter is available
- if STD_OFF,Function Eth_17_GEthMac_UpdatePhysAddrFilter is not available
*/
#define ETH_17_GETHMAC_UPDATE_PHY_ADDR_FILTER_API   (STD_ON)

/*
Configuration: ETH_17_GETHMAC_INIT_API_MODE
- if ETH_17_GETHMAC_MCAL_SUPERVISOR - Init API is executed in supervisor mode.
- if ETH_17_GETHMAC_MCAL_USER1 - Init API is executed in user1 mode.
*/
#define ETH_17_GETHMAC_INIT_API_MODE         (ETH_17_GETHMAC_MCAL_SUPERVISOR)

/*
Configuration: ETH_17_GETHMAC_RUNTIME_API_MODE
- if ETH_17_GETHMAC_MCAL_SUPERVISOR - Runtime APIs are executed in supervisor mode.
- if ETH_17_GETHMAC_MCAL_USER1 - Runtime APIs are executed in user1 mode.
*/
#define ETH_17_GETHMAC_RUNTIME_API_MODE      (ETH_17_GETHMAC_MCAL_SUPERVISOR)

/* Controller0 is configured to CORE0 */
#define ETH_17_GETHMAC_CNTRL0_CORE0  (STD_ON)

/* Controller0 is configured in this project */
#define ETH_17_GETHMAC_CNTRL0_CONFIGURED         (STD_ON)

/* Maximum Controllers allocated to CORE0
Value = 255- represents core is not available in current device */
#define ETH_17_GETHMAC_MAX_CNTRL_CORE0               (1U)

/* Maximum Controllers allocated to CORE1
Value = 255- represents core is not available in current device */
#define ETH_17_GETHMAC_MAX_CNTRL_CORE1               (0U)

/* Maximum Controllers allocated to CORE2
Value = 255- represents core is not available in current device */
#define ETH_17_GETHMAC_MAX_CNTRL_CORE2               (0U)

/* Maximum Controllers allocated to CORE3
Value = 255- represents core is not available in current device */
#define ETH_17_GETHMAC_MAX_CNTRL_CORE3               (0U)

/* Maximum Controllers allocated to CORE4
Value = 255- represents core is not available in current device */
#define ETH_17_GETHMAC_MAX_CNTRL_CORE4               (255U)

/* Maximum Controllers allocated to CORE5
Value = 255- represents core is not available in current device */
#define ETH_17_GETHMAC_MAX_CNTRL_CORE5               (255U)

/* Maximum available cores in this device */
#define ETH_17_GETHMAC_MAX_CORES                     (4U)

/* Maximum controllers available in this device */
#define ETH_17_GETHMAC_MAX_CONTROLLERS               (1U)
/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/
#endif  /* ETH_17_GETHMAC_CFG_H */

