/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2020)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : WdgIf_Types.h                                              **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2020-10-01                                                 **
**                                                                            **
**  VARIANT      : NA                                                         **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : This file exports Wdg interface Type defnitions            **
**                                                                            **
**  SPECIFICATION(S) : AUTOSAR_SWS_WatchdogInterface,AUTOSAR                  **
**                     Release 4.2.2                                          **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/

/*---- Protection against multiple inclusion -------------------------------*/
#ifndef WDGIF_TYPES_H
#define WDGIF_TYPES_H

#include "Std_Types.h"

/*---- Version identification - --------------------------------------------*/

#define WDGIF_TYPES_MAJOR_VERSION      (4U)
#define WDGIF_TYPES_MINOR_VERSION      (2U)
#define WDGIF_TYPES_PATCH_VERSION      (2U)

/*---- Switch between external and forward declaration ---------------------*/

/*---- API Type definitions ------------------------------------------------*/

typedef enum
{
  WDGIF_OFF_MODE = 0U,
  WDGIF_SLOW_MODE = 1U,
  WDGIF_FAST_MODE = 2U
} WdgIf_ModeType; /*refer to SWS_WdgIf_00061*/

/*---- Include of configuration (public section) ---------------------------*/

/*--------------------------------------------------------------------------*/
#endif  /* End of WdgIf_Types.h */
