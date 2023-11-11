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
** Traceability  : [cover parentID={71ADFE16-D2F4-40c1-8907-8CC7F3E02AF5}]    **
**                                                                            **
**  FILENAME         : Mcal_Version.h                                         **
**                                                                            **
**  VERSION          : 2.0.0                                                  **
**                                                                            **
**  DATE             : 2020-04-23                                             **
**                                                                            **
**  VARIANT          : NA                                                     **
**                                                                            **
**  PLATFORM         : Infineon AURIX2G                                       **
**                                                                            **
**  AUTHOR           : DL-AUTOSAR-Engineering                                 **
**                                                                            **
**  VENDOR           : Infineon Technologies                                  **
**                                                                            **
**  DESCRIPTION      : Autosar version specific macro definition file         **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : NO                                               **
**                                                                            **
*******************************************************************************/
#ifndef MCAL_VERSION_H
#define MCAL_VERSION_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Configuration data                                    **
*******************************************************************************/
/* Autosar version specific information */
#define MCAL_AR_422                                        (1U)
#define MCAL_AR_440                                        (0U)

/* [cover parentID={BDE616FE-5D39-4b9d-9390-8351CC6C490C}][/cover] */
#define MCAL_AR_VERSION                                    (MCAL_AR_422)

#define MCAL_AR_RELEASE_MAJOR_VERSION                      (4U)
#define MCAL_AR_RELEASE_MINOR_VERSION                      (2U)
#define MCAL_AR_RELEASE_REVISION_VERSION                   (2U)

#endif /* MCAL_VERSION_H  */

