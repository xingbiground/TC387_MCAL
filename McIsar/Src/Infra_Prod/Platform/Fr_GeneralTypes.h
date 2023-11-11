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
**  FILENAME     : Fr_GeneralTypes.h                                          **
**                                                                            **
**  VERSION      : 7.0.0                                                      **
**                                                                            **
**  DATE         : 2020-05-28                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Type Definition for FR module                              **
**                                                                            **
**  SPECIFICATION(S) : AUTOSAR_SWS_FlexRayDriver.pdf, AUTOSAR Release 4.2.2   **
**                                                                            **
**  MAY BE CHANGED BY USER : Yes                                              **
**                                                                            **
*******************************************************************************/
#ifndef FR_GENERAL_TYPES
#define FR_GENERAL_TYPES

/*****************************************************************************
 Include Section
******************************************************************************/

#include "Std_Types.h"      /* basic AUTOSAR type definitions */
#include "McalLib.h"

/*****************************************************************************
 Global Macros
******************************************************************************/
/*
 * This macro maps to value FR_SLOTMODE_KEYSLOT.
 */
/* [cover parentID={24E2DB02-4096-4cd4-9EB3-B9CD669D91E4}] */
#define FR_SLOTMODE_SINGLE (0U)
/* [/cover] */

/*****************************************************************************
 Global Data Types
******************************************************************************/

/*
 * This enumerator type represents the FlexRay controller POC states.
 */
/* [cover parentID={C934702B-340F-4176-8F09-9B32542B95AE}] */
typedef enum
{
    FR_POCSTATE_CONFIG = 0,     /* config state */
    FR_POCSTATE_DEFAULT_CONFIG, /* default config state */
    FR_POCSTATE_HALT,           /* halt state */
    FR_POCSTATE_NORMAL_ACTIVE,  /* normal active state */
    FR_POCSTATE_NORMAL_PASSIVE, /* normal passive state */
    FR_POCSTATE_READY,          /* ready state */
    FR_POCSTATE_STARTUP,        /* startup state */
    FR_POCSTATE_WAKEUP          /* wakeup state */
}Fr_POCStateType;
/* [/cover] */

/*
 * This enumerator type represents the FlexRay controller slotmodes.
 */
/* [cover parentID={35920BA5-85D8-44e8-9154-27ADC0507EDC}] */
typedef enum
{
    FR_SLOTMODE_KEYSLOT = 0,     /* single slot mode */
    FR_SLOTMODE_ALL_PENDING,    /* all peding slot mode */
    FR_SLOTMODE_ALL             /* all slot mode */
}Fr_SlotModeType;
/*  [/cover] */

/*
 * This enumerator type represents the FlexRay controller errormode.
 */
/* [cover parentID={ECFD2660-6A1D-41f2-AF7A-C895B540FEF1}] */
typedef enum
{
    FR_ERRORMODE_ACTIVE = 0,    /* acvtive errormode */
    FR_ERRORMODE_PASSIVE,       /* passive errormode */
    FR_ERRORMODE_COMM_HALT      /* communication halted errormode */
}Fr_ErrorModeType;
/*  [/cover] */

/*
 * This enumerator type represents the wakeup status type.
 */
/* [cover parentID={F342FB8D-5077-48f6-B850-D8A466F4D9C8}] */
typedef enum
{
    FR_WAKEUP_UNDEFINED = 0,    /* wakeup state "undefined" */
    FR_WAKEUP_RECEIVED_HEADER,  /* wakeup state "received header" */
    FR_WAKEUP_RECEIVED_WUP,     /* wakeup state "received wakeup pattern" */
    FR_WAKEUP_COLLISION_HEADER, /* wakeup state "collsision header" */
    FR_WAKEUP_COLLISION_WUP,    /* wakeup state "collision wakeup pattern" */
    FR_WAKEUP_COLLISION_UNKNOWN,/* wakeup state "collision unknown" */
    FR_WAKEUP_TRANSMITTED       /* wakeup state "transmitted" */
}Fr_WakeupStatusType;
/*  [/cover] */

/*
 * This enumerator type represents the startup status type.
 */
/* [cover parentID={9039A568-81B7-476a-914D-B99E11D53938}] */
typedef enum
{
    FR_STARTUP_UNDEFINED = 0,                   /* startup state "undefined" */
    FR_STARTUP_COLDSTART_LISTEN,                /* startup state "coldstart listen" */
    FR_STARTUP_INTEGRATION_COLDSTART_CHECK,     /* startup state "integration coldstart check" */
    FR_STARTUP_COLDSTART_JOIN,                  /* startup state "coldstart join" */
    FR_STARTUP_COLDSTART_COLLISION_RESOLUTION,  /* startup state "collision resolution" */
    FR_STARTUP_COLDSTART_CONSISTENCY_CHECK,     /* startup state "consistency check" */
    FR_STARTUP_INTEGRATION_LISTEN,              /* startup state "integration listen" */
    FR_STARTUP_INITIALIZE_SCHEDULE,             /* startup state "initialize schedule" */
    FR_STARTUP_INTEGRATION_CONSISTENCY_CHECK,   /* startup state "integration consistency check" */
    FR_STARTUP_COLDSTART_GAP,                   /* startup state "coldstart gap" */
    FR_STARTUP_EXTERNAL_STARTUP
}Fr_StartupStateType;
/*  [/cover] */

/*
 * This structure contains the POC-Status information.
 */
/* [cover parentID={02B3C83C-CA07-4e43-9BCF-FB33558CA5B2}] */
typedef struct
{
    Fr_POCStateType State;            /*  CC - POC state */
    boolean Freeze;                   /*  CC - Freeze bit */
    boolean CHIHaltRequest;           /*  CC - CHI Halt request bit */
    boolean CHIReadyRequest;          /*  CC - CHI Ready request bit */
    boolean ColdstartNoise;           /*  CC - Coldstart noise bit */
    Fr_SlotModeType SlotMode;         /*  CC - slot mode */
    Fr_ErrorModeType ErrorMode;       /*  CC - error mode */
    Fr_WakeupStatusType WakeupStatus; /*  CC - wakeup state */
    Fr_StartupStateType StartupState; /*  CC - startup state */
}Fr_POCStatusType;
/*  [/cover] */

/*
 * This enumerator type represents the LSdu tx status.
 */
/* [cover parentID={C4EB4D59-07D3-44fc-BEEE-C01AA18FB8A0}] */
typedef enum
{
    FR_TRANSMITTED = 0,    /* LSdu was transmitted */
    FR_TRANSMITTED_CONFLICT, /* Lsdu transmission conflict has occurred */
    FR_NOT_TRANSMITTED     /* LSdu was not transmitted */
}Fr_TxLPduStatusType;
/*  [/cover] */

/*
 * This enumerator type represents the LSdu rx status.
 */
/* [cover parentID={357D7062-913B-491e-B220-9A86FDB0815C}] */
typedef enum
{
    FR_RECEIVED = 0,                 /* LSdu was received */
    FR_NOT_RECEIVED,                 /* LSdu was not received */
    FR_RECEIVED_MORE_DATA_AVAILABLE  /* FIFO is not empty */
}Fr_RxLPduStatusType;
/*  [/cover] */

#if(MCAL_AR_VERSION == MCAL_AR_422)
/*
 * This enumerator type represents the FlexRay channels for autosar 422.
 */
/* [cover parentID={9F772708-42EC-4974-9017-34536DA70CF7}] */
typedef enum
{

    FR_CHANNEL_A = 0,     /* FlexRay channel A */
    FR_CHANNEL_B,         /* FlexRay channel B */
    FR_CHANNEL_AB         /* FlexRay channel A and B */
} Fr_ChannelType;
/*  [/cover] */
#else
/*
 * This enumerator type represents the FlexRay channels for autosar 440.
 */
/* [cover parentID={9F772708-42EC-4974-9017-34536DA70CF7}] */
typedef enum
{

    FR_CHANNEL_A = 1,     /* FlexRay channel A */
    FR_CHANNEL_B,         /* FlexRay channel B */
    FR_CHANNEL_AB         /* FlexRay channel A and B */
} Fr_ChannelType;
/*  [/cover] */
#endif

/*
 * This enumerator type represents the FlexRay transceiver driver modes.
 */
typedef enum
{
    FRTRCV_TRCVMODE_NORMAL = 0,  /* FrTrcv mode "Normal" */
    FRTRCV_TRCVMODE_STANDBY,     /* FrTrcv mode "Standby" */
    FRTRCV_TRCVMODE_SLEEP,       /* FrTrcv mode "Sleep" */
    FRTRCV_TRCVMODE_RECEIVEONLY  /* FrTrcv mode "Receive Only" */
} FrTrcv_TrcvModeType;

/*
 * This enumerator type represents the FlexRay transceiver wakeup-reasons.
 */
typedef enum
{
    FRTRCV_WU_NOT_SUPPORTED = 0,  /* FrTrcv wakeup not supported */
    FRTRCV_WU_BY_BUS,             /* FrTrcv wakeup by bus */
    FRTRCV_WU_INTERNALLY,         /* FrTrcv internally wakeup */
    FRTRCV_WU_RESET,              /* FrTrcv reset wakeup */
    FRTRCV_WU_POWER_ON            /* FrTrcv power on wakeup */
} FrTrcv_TrcvWUReasonType;

/*
 * This structure contains information about the assignment of a FlexRay frame to
 * a cycle, Channel ID and slot ID
 */
/* [cover parentID={B676A3DC-0B05-4735-81B2-FBF9CE0F03B7}] */
typedef struct
{
  uint8 Cycle;                /*Cycle in which the frame is transmitted/received*/
  uint16 SlotId;              /*Slot Id of the frame*/
  Fr_ChannelType ChannelId;   /*Channel of the frame*/
}Fr_SlotAssignmentType;
/*  [/cover] */

/* Macros for Configuration Parameter indices */
/* Symbolic names that can be passed into API function Fr_ReadCCConfig as
   parameter Fr_ConfigParamIdx*/
/* [cover parentID={3266C5FD-4CBA-42fb-84F2-5369236F84BE}] */
#define   FR_CIDX_GDCYCLE                           (0U)
#define   FR_CIDX_PMICROPERCYCLE                    (1U)
#define   FR_CIDX_PDLISTENTIMEOUT                   (2U)
#define   FR_CIDX_GMACROPERCYCLE                    (3U)
#define   FR_CIDX_GDMACROTICK                       (4U)
#define   FR_CIDX_GNUMBEROFMINISLOTS                (5U)
#define   FR_CIDX_GNUMBEROFSTATICSLOTS              (6U)
#define   FR_CIDX_GDNIT                             (7U)
#define   FR_CIDX_GDSTATICSLOT                      (8U)
#define   FR_CIDX_GDWAKEUPRXWINDOW                  (9U)
#define   FR_CIDX_PKEYSLOTID                        (10U)
#define   FR_CIDX_PLATESTTX                         (11U)
#define   FR_CIDX_POFFSETCORRECTIONOUT              (12U)
#define   FR_CIDX_POFFSETCORRECTIONSTART            (13U)
#define   FR_CIDX_PRATECORRECTIONOUT                (14U)
#define   FR_CIDX_PSECONDKEYSLOTID                  (15U)
#define   FR_CIDX_PDACCEPTEDSTARTUPRANGE            (16U)
#define   FR_CIDX_GCOLDSTARTATTEMPTS                (17U)
#define   FR_CIDX_GCYCLECOUNTMAX                    (18U)
#define   FR_CIDX_GLISTENNOISE                      (19U)
#define   FR_CIDX_GMAXWITHOUTCLOCKCORRECTFATAL      (20U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
#define   FR_CIDX_GMAXWITHOUTCLOCKCORRECTPASSIVE    (21U)
#define   FR_CIDX_GNETWORKMANAGEMENTVECTORLENGTH    (22U)
#define   FR_CIDX_GPAYLOADLENGTHSTATIC              (23U)
#define   FR_CIDX_GSYNCFRAMEIDCOUNTMAX              (24U)
#define   FR_CIDX_GDACTIONPOINTOFFSET               (25U)
#define   FR_CIDX_GDBIT                             (26U)
#define   FR_CIDX_GDCASRXLOWMAX                     (27U)
#define   FR_CIDX_GDDYNAMICSLOTIDLEPHASE            (28U)
#define   FR_CIDX_GDMINISLOTACTIONPOINTOFFSET       (29U)
#define   FR_CIDX_GDMINISLOT                        (30U)
#define   FR_CIDX_GDSAMPLECLOCKPERIOD               (31U)
#define   FR_CIDX_GDSYMBOLWINDOW                    (32U)
#define   FR_CIDX_GDSYMBOLWINDOWACTIONPOINTOFFSET   (33U)
#define   FR_CIDX_GDTSSTRANSMITTER                  (34U)
#define   FR_CIDX_GDWAKEUPRXIDLE                    (35U)
#define   FR_CIDX_GDWAKEUPRXLOW                     (36U)
#define   FR_CIDX_GDWAKEUPTXACTIVE                  (37U)
#define   FR_CIDX_GDWAKEUPTXIDLE                    (38U)
#define   FR_CIDX_PALLOWPASSIVETOACTIVE             (39U)
#define   FR_CIDX_PCHANNELS                         (40U)
#define   FR_CIDX_PCLUSTERDRIFTDAMPING              (41U)
#define   FR_CIDX_PDECODINGCORRECTION               (42U)
#define   FR_CIDX_PDELAYCOMPENSATIONA               (43U)
#define   FR_CIDX_PDELAYCOMPENSATIONB               (44U)
#define   FR_CIDX_PMACROINITIALOFFSETA              (45U)
#define   FR_CIDX_PMACROINITIALOFFSETB              (46U)
#define   FR_CIDX_PMICROINITIALOFFSETA              (47U)
#define   FR_CIDX_PMICROINITIALOFFSETB              (48U)
#define   FR_CIDX_PPAYLOADLENGTHDYNMAX              (49U)
#define   FR_CIDX_PSAMPLESPERMICROTICK              (50U)
#define   FR_CIDX_PWAKEUPCHANNEL                    (51U)
#define   FR_CIDX_PWAKEUPPATTERN                    (52U)
#define   FR_CIDX_PDMICROTICK                       (53U)
#define   FR_CIDX_GDIGNOREAFTERTX                   (54U)
#define   FR_CIDX_PALLOWHALTDUETOCLOCK              (55U)
#define   FR_CIDX_PEXTERNALSYNC                     (56U)
#define   FR_CIDX_PFALLBACKINTERNAL                 (57U)
#define   FR_CIDX_PKEYSLOTONLYENABLED               (58U)
#define   FR_CIDX_PKEYSLOTUSEDFORSTARTUP            (59U)
#define   FR_CIDX_PKEYSLOTUSEDFORSYNC               (60U)
#define   FR_CIDX_PNMVECTOREARLYUPDATE              (61U)
#define   FR_CIDX_PTWOKEYSLOTMODE                   (62U)
/*  [/cover] */

#endif /* FR_GENERAL_TYPES */

