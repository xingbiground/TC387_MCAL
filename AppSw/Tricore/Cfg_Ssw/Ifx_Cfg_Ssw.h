/**
 * \file Ifx_Cfg_Ssw.h
 * \brief Configuration header file for the Startup Software
 * \ingroup
 *
 * \copyright Copyright (c) 2018 Infineon Technologies AG. All rights reserved.
 *
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 */

#ifndef IFX_CFG_SSW_H_
#define IFX_CFG_SSW_H_

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/
#include "Ifx_Cfg.h"
#include "Ifx_Ssw.h"

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/
/** \brief Set this macro to 1, to configure the PMS EVR.
 */
#ifndef IFX_CFG_SSW_ENABLE_PMS_INIT
#define IFX_CFG_SSW_ENABLE_PMS_INIT       (0U)
#endif
/** \brief Set this macro to 1, to check the PMS EVR configuration.
 */
#ifndef IFX_CFG_SSW_ENABLE_PMS_INIT_CHECK
#define IFX_CFG_SSW_ENABLE_PMS_INIT_CHECK (0U)
#endif
/** \brief Set this macro to 1, to do LBIST checks.
 */
#ifndef IFX_CFG_SSW_ENABLE_LBIST
#define IFX_CFG_SSW_ENABLE_LBIST          (0U)
#endif
/** \brief Set this macro to 1, to do MONBIST checks.
 */
#ifndef IFX_CFG_SSW_ENABLE_MONBIST
#define IFX_CFG_SSW_ENABLE_MONBIST        (0U)
#endif
/** \brief Set this macro to 1, to do MMIC checks.
 */
#ifndef IFX_CFG_SSW_ENABLE_MMIC_CHECK
#define IFX_CFG_SSW_ENABLE_MMIC_CHECK     (0U)
#endif
/** \brief Set this macro to 1, to initialize the PLL.
 */
#ifndef IFX_CFG_SSW_ENABLE_PLL_INIT
#define IFX_CFG_SSW_ENABLE_PLL_INIT       (0U)
#endif
/** \brief Set this macro to 1, to do MBIST checks.
 */
#ifndef IFX_CFG_SSW_ENABLE_MBIST
#define IFX_CFG_SSW_ENABLE_MBIST          (0U)
#endif
/** \brief Set this macro to 1, to do SMU Alarm handling.
 */
#ifndef IFX_CFG_SSW_ENABLE_SMU
#define IFX_CFG_SSW_ENABLE_SMU            (0U)
#endif
/******************************************************************************/
/*------------------------  Function Implementations  ------------------------*/
/******************************************************************************/
#if IFX_CFG_SSW_ENABLE_PMS_INIT == 1U

extern void Ifx_Ssw_Pms_Init(void);
extern void Ifx_Ssw_Pms_InitCheck(void);

/** Callout hook API macro for PMS Initialization
 * This callout hook is referenced in Startup sequence. This need to be configured by application to
 * initialize the PMS EVR module. This hook is by default defined to empty call by startup implementation.
 * THIS CALLOUT HOOK SHALL NOT BE IMPLEMENTED AS FUNCTION CALL!
 * \param none
 * \return none
 */
#define IFX_CFG_SSW_CALLOUT_PMS_INIT()                     \
    {                                                      \
        Ifx_Ssw_jumpToFunctionWithLink(&Ifx_Ssw_Pms_Init); \
        IFX_CFG_SSW_CALLOUT_PMS_CHECK();                   \
    }

#if IFX_CFG_SSW_ENABLE_PMS_INIT_CHECK == 1U

/** Callout hook API macro for PMS Initialization check
 * This callout hook is referenced in Startup sequence. This need to be configured by application to
 * cross verify the PMS configuration with the required values. This hook is by default defined to empty
 * call by startup implementation.
 * THIS CALLOUT HOOK SHALL NOT BE IMPLEMENTED AS FUNCTION CALL!
 * \param none
 * \return none
 */
#define IFX_CFG_SSW_CALLOUT_PMS_CHECK()                         \
    {                                                           \
        Ifx_Ssw_jumpToFunctionWithLink(&Ifx_Ssw_Pms_InitCheck); \
    }
#else
#define IFX_CFG_SSW_CALLOUT_PMS_CHECK()
#endif /* End of IFX_CFG_SSW_ENABLE_PMS_INIT_CHECK */

#endif /* End of IFX_CFG_SSW_ENABLE_PMS_INIT */

/** Callout hook API macro for LBIST check
 * This callout hook is referenced in Startup sequence. This need to be configured by application to
 * do LBIST checks. This hook is by default defined to empty call by startup implementation.
 * THIS CALLOUT HOOK SHALL NOT BE IMPLEMENTED AS FUNCTION CALL!
 * \param none
 * \return none
 */
#if IFX_CFG_SSW_ENABLE_LBIST == 1U

extern void Ifx_Ssw_Lbist(void);

#define IFX_CFG_SSW_CALLOUT_LBIST()                     \
    {                                                   \
        Ifx_Ssw_jumpToFunctionWithLink(&Ifx_Ssw_Lbist); \
    }

#endif /* End of IFX_CFG_SSW_ENABLE_LBIST */

/** Callout hook API macro for MONBIST check
 * This callout hook is referenced in Startup sequence. This need to be configured by application to
 * do MONBIST checks. This hook is by default defined to empty call by startup implementation.
 * THIS CALLOUT HOOK SHALL NOT BE IMPLEMENTED AS FUNCTION CALL!
 * \param none
 * \return none
 */
#if IFX_CFG_SSW_ENABLE_MONBIST == 1U

extern void Ifx_Ssw_Monbist(void);

#define IFX_CFG_SSW_CALLOUT_MONBIST()                 \
{                                                     \
    Ifx_Ssw_jumpToFunctionWithLink(&Ifx_Ssw_Monbist); \
}
#endif /* End of IFX_CFG_SSW_ENABLE_MONBIST */

/** Callout hook API macro for PLL initialization
 * This callout hook is referenced in Startup sequence. This need to be configured by application to
 * initialize the PLL. This hook is by default defined to empty call by startup implementation.
 * \param none
 * \return none
 */
#if IFX_CFG_SSW_ENABLE_PLL_INIT == 1U

#define IFX_CFG_SSW_CALLOUT_PLL_INIT()                          \
    {                                                           \
    }

#endif /* End of IFX_CFG_SSW_ENABLE_PLL_INIT */

/** Callout hook API macro for MBIST check
 * This callout hook is referenced in Startup sequence. This need to be configured by application to
 * do MBIST checks. This hook is by default defined to empty call by startup implementation.
 * \param none
 * \return none
 */
#if IFX_CFG_SSW_ENABLE_MBIST == 1U

#define IFX_CFG_SSW_CALLOUT_MBIST() \
    {                               \
    }

#endif /* End of IFX_CFG_SSW_ENABLE_MBIST */

/** Callout hook API macro for MMIC check
 * This need to be configured by application to do MMIC checks.
 * This hook is by default defined to empty call by startup implementation.
 * \param none
 * \return none
 */
#if IFX_CFG_SSW_ENABLE_MMIC_CHECK == 1U
#define IFX_CFG_SSW_CALLOUT_MMIC_CHECK()
#endif /* End of IFX_CFG_SSW_ENABLE_MMIC_CHECK */

/** Callout hook API macro for SMU alarm handling
 * This need to be configured by application to do SMU alarm handling.
 * This hook is by default defined to empty call by startup implementation.
 * \param none
 * \return none
 */
#if IFX_CFG_SSW_ENABLE_SMU == 1U
#define IFX_CFG_SSW_CALLOUT_SMU()
#endif /* End of IFX_CFG_SSW_ENABLE_SMU */

#endif /* IFX_CFG_SSW_H_ */
