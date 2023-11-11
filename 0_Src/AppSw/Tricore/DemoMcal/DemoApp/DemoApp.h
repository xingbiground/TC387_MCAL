/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2017)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : DemoApp.h                                                     **
**                                                                            **
**  VERSION    : 0.0.2                                                        **
**                                                                            **
**  DATE       : 2017-03-07                                                   **
**                                                                            **
**  VARIANT    : NA                                                           **
**                                                                            **
**  PLATFORM   : Infineon AURIX2G                                             **
**                                                                            **
**  AUTHOR      : DL-AUTOSAR-Engineering                                      **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION : This file exports                                           **
**                - DemoApp Framework for MCAL driver Demo Applications       **
**                                                                            **
**  SPECIFICATION(S) :  NA                                                    **
**                                                                            **
**  MAY BE CHANGED BY USER [Yes/No]: Yes                                      **
*******************************************************************************/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#ifndef  DEMOAPP_H
#define  DEMOAPP_H

/* Enable the inclusion of DemoApp for BFX library*/
#define BFX_DEMO_EN (STD_ON)
#define MULTICORE_DEMO_ENABLE_VALUE 0xABCDEF55U
#define DEMO_CPU_SPINLOCK_TIMEOUT   (0xFFFFFFU)
/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
extern uint8 DemoApp_FlsInitDone; /* Flag to check FLS init is already called */

typedef void (*demo_fct_type) (void);

/* Definition of menu type */
typedef  struct DemoApp_FctListType
{
  const char    *fct_name;
  demo_fct_type fct_p;
  const char    *fct_desc;
} DemoApp_FctListType;

typedef  struct DemoApp_MenuType
{
  uint32    size;
  DemoApp_FctListType const *list;
} DemoApp_MenuType;

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
extern void DemoApp(void);
extern void DemoApp_Init(void);
extern void DemoApp_CallMenuFct  (char *my_fct_name) __attribute__ ((noinline));
#endif /* DEMOAPP_H */

