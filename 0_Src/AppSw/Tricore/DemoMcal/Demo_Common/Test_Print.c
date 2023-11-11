/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2019)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : Test_Print.c                                                **
**                                                                           **
**  VERSION    : 1.0.0                                                       **
**                                                                           **
**  DATE       : 2019-10-14                                                  **
**                                                                           **
**  VARIANT    : NA                                                          **
**                                                                           **
**  PLATFORM   : Infineon AURIX2G                                            **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION : This file provides display and print support.              **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/

/******************************************************************************
**                      Includes                                             **
******************************************************************************/
/* Inclusion of Platform_Types.h and Compiler.h */
#include "Std_Types.h"

/* Inclusion of Tasking sfr file */
#include "IfxAsclin_reg.h"

/* Include Mcallib.h to import the library functions */
#include "McalLib.h"

/* Include Test_Time header file - Test_Time.h */
#include "Test_Time.h"

/* Include Test_Print header file - Test_Print.h */
#include "Test_Print.h"
#include "IfxScu_reg.h"

/* Include stdio header file - stdio.h */
#if defined _GHS_C_TRICORE_
#pragma ghs nowarning 1729
#include <stdio.h>
#pragma ghs endnowarning 1729
#else
#include <stdio.h>
#endif

/******************************************************************************
**                      Imported Compiler Switch Checks                      **
******************************************************************************/

/******************************************************************************
**                      Private Macro Definitions                            **
******************************************************************************/
#define ASCLIN0_BASE          (0xF0000600U)
#define ASCLIN1_BASE          (0xF0000700U)

#define ASCLIN_FRAMECON_MODE_INIT (0U)
#define ASCLIN_FRAMECON_MODE_ASC  (1U)
#define ASCLIN_FRAMECON_MODE_SPI  (2U)
#define ASCLIN_FRAMECON_MODE_LIN  (3U)
#define ASCLIN_FRAMECON_MODE_SHIFT (16U)
#define ASCLIN_FRAMECON_STOP_SHIFT (9U)
#define ASCLIN_FRAMECON_STOP       (1U)

#define ASCLIN_DATCON_DATLEN       (7U) /* 8 bit */
#define ASCLIN_DATCON_DATLEN_SHIFT (0U)
#define ASCLIN_DATCON_DATLEN_MASK  (0xFFFFFFF0U)

#define ASCLIN_BITCON_PRESCALAR_SHIFT (0U)
#define ASCLIN_BITCON_OVERSAMPLING_SHIFT (16U)
#define ASCLIN_BITCON_SAMPLEPOINT_SHIFT (24U)
#define ASCLIN_BITCON_SM_SHIFT (31U)

#define ASCLIN_FREQ_10MHZ      0
#define ASCLIN_FREQ_20MHZ      1
#define ASCLIN_FREQ_80MHZ      2
#define ASCLIN_BDR_38P4K        0
#define ASCLIN_BDR_115P2K       1
#define ASCLIN_BDR_921P6K       2
#define ASCLIN_BDR_1MHZ         3
#define ASCLIN_BDR_1P5MHZ       4
#define ASCLIN_BDR_2MHZ         5
#ifndef ASCLIN_CLOCK
#define ASCLIN_CLOCK       ASCLIN_FREQ_20MHZ
#endif /* ASCLIN_CLOCK */
#ifndef ASCLIN_BAUDRATE
#define ASCLIN_BAUDRATE    ASCLIN_BDR_115P2K
#endif /* ASCLIN_BAUDRATE */
#if ASCLIN_CLOCK == ASCLIN_FREQ_20MHZ
#if ASCLIN_BAUDRATE == ASCLIN_BDR_2MHZ
#define ASCLIN_BITCON_PRESCALAR    (0U)  /* 1 - 4096 */
#define ASCLIN_BITCON_OVERSAMPLING (9U)  /* min of 3 */
#define ASCLIN_BITCON_SAMPLEPOINT  (5U)  /* min of 1 */
#define ASCLIN_BRG_DENOMINATOR     (2304U)
#elif ASCLIN_BAUDRATE == ASCLIN_BDR_1P5MHZ
#define ASCLIN_BITCON_PRESCALAR    (0U)  /* 1 - 4096 */
#define ASCLIN_BITCON_OVERSAMPLING (11U) /* min of 3 */
#define ASCLIN_BITCON_SAMPLEPOINT  (6U)  /* min of 1 */
#define ASCLIN_BRG_DENOMINATOR     (2560U)
#elif ASCLIN_BAUDRATE == ASCLIN_BDR_1MHZ
#define ASCLIN_BITCON_PRESCALAR    (0U)  /* 1 - 4096 */
#define ASCLIN_BITCON_OVERSAMPLING (15U) /* min of 3 */
#define ASCLIN_BITCON_SAMPLEPOINT  (8U)  /* min of 1 */
#define ASCLIN_BRG_DENOMINATOR     (2880U)
#elif ASCLIN_BAUDRATE == ASCLIN_BDR_921P6K
#define ASCLIN_BITCON_PRESCALAR    (0U)  /* 1 - 4096 */
#define ASCLIN_BITCON_OVERSAMPLING (15U) /* min of 3 */
#define ASCLIN_BITCON_SAMPLEPOINT  (8U)  /* min of 1 */
#define ASCLIN_BRG_DENOMINATOR     (3125U)
#elif ASCLIN_BAUDRATE == ASCLIN_BDR_115P2K
#define ASCLIN_BITCON_PRESCALAR (9U) /* 1 - 4096 */
#define ASCLIN_BITCON_OVERSAMPLING (15U) /* min of 3 */
#define ASCLIN_BITCON_SAMPLEPOINT (8U) /* min of 1 */
#define ASCLIN_BRG_DENOMINATOR     (2500U)
#elif ASCLIN_BAUDRATE == ASCLIN_BDR_38P4K
#define ASCLIN_BITCON_PRESCALAR    (29U)  /* 1 - 4096 */
#define ASCLIN_BITCON_OVERSAMPLING (15U) /* min of 3 */
#define ASCLIN_BITCON_SAMPLEPOINT  (8U)  /* min of 1 */
#define ASCLIN_BRG_DENOMINATOR     (2500U)
#else
#error "ASCLIN configuration not done for this ASCLIN_BAUDRATE setting, configure manually"
#endif /* ASCLIN_BAUDRATE == ASCLIN_BDR_2MHZ */
#elif ASCLIN_CLOCK == ASCLIN_FREQ_10MHZ
#if ASCLIN_BAUDRATE == ASCLIN_BDR_921P6K
#define ASCLIN_BITCON_PRESCALAR    (0U)  /* 1 - 4096 */
#define ASCLIN_BITCON_OVERSAMPLING (9U)  /* min of 3 */
#define ASCLIN_BITCON_SAMPLEPOINT  (5U)  /* min of 1 */
#define ASCLIN_BRG_DENOMINATOR     (2500U)
#elif ASCLIN_BAUDRATE == ASCLIN_BDR_115P2K
#define ASCLIN_BITCON_PRESCALAR    (4U)  /* 1 - 4096 */
#define ASCLIN_BITCON_OVERSAMPLING (15U) /* min of 3 */
#define ASCLIN_BITCON_SAMPLEPOINT  (8U)  /* min of 1 */
#define ASCLIN_BRG_DENOMINATOR     (2500U)
#elif ASCLIN_BAUDRATE == ASCLIN_BDR_38P4K
#define ASCLIN_BITCON_PRESCALAR    (14U)  /* 1 - 4096 */
#define ASCLIN_BITCON_OVERSAMPLING (15U) /* min of 3 */
#define ASCLIN_BITCON_SAMPLEPOINT  (8U)  /* min of 1 */
#define ASCLIN_BRG_DENOMINATOR     (2500U)
#else
#error "ASCLIN configuration not done for this ASCLIN_BAUDRATE setting, configure manually"
#endif /* ASCLIN_BAUDRATE == ASCLIN_BDR_921P6K */
#elif ASCLIN_CLOCK == ASCLIN_FREQ_80MHZ
#if ASCLIN_BAUDRATE == ASCLIN_BDR_115P2K
#define ASCLIN_BITCON_PRESCALAR    (4U) /* 1 - 4096 */
#define ASCLIN_BITCON_OVERSAMPLING (9U) /* min of 3 */
#define ASCLIN_BITCON_SAMPLEPOINT  (8U)  /* min of 1 */
#define ASCLIN_BRG_DENOMINATOR     (1000U)
#else
#error "Other baudrates for ASCLIN frequency 80MHz are not supported"
#endif/* ASCLIN_BAUDRATE == ASCLIN_BDR_921P6K */
#else
#error "ASCLIN configuration not done for this ASCLIN_CLOCK setting, configure manually"
#endif /* ASCLIN_BAUDRATE == ASCLIN_BDR_115P2K*/
#if ASCLIN_CLOCK == ASCLIN_FREQ_80MHZ
#define ASCLIN_BRG_NUMERATOR         (72U)
#else
#define ASCLIN_BRG_NUMERATOR         (2304U)
#endif
#define ASCLIN_BITCON_SM (0U)

#define ASCLIN_BRG_NUMERATOR_SHIFT (16U)
#define ASCLIN_BRG_DENOMINATOR_SHIFT (0U)


#define ASCLIN_CSR_CLKSEL_NOCLK     (0U)
#define ASCLIN_CSR_CLKSEL_CLC       (1U)
#define ASCLIN_CSR_CLKSEL_EVROSC    (2U)
#define ASCLIN_CSR_CLKSEL_FMAX      (8U)
#define ASCLIN_CSR_CLKSEL_SHIFT     (0U)
#define ASCLIN_CSR_CLKSEL       (4) /* EVR Osc used as Clock source*/

#define ASCLIN_TXFIFOCON_FILL_SHIFT (16U)
#define ASCLIN_TXFIFOCON_FILL_MASK  (0x1FU)
#define ASCLIN_TXFIFOCON_ENO_SHIFT (1U)
#define ASCLIN_TXFIFOCON_ENO_EN    (1U) /* tx fifo outlet enable */
#define ASCLIN_TXFIFOCON_INW_SHIFT (6U)
#define ASCLIN_TXFIFOCON_INW_VAL   (1U) /* tx fifo outlet width */

#define ASCLIN_RXFIFOCON_FILL_SHIFT (16U)
#define ASCLIN_RXFIFOCON_FILL_MASK  (0x1FU)
#define ASCLIN_RXFIFOCON_ENO_SHIFT (1U)
#define ASCLIN_RXFIFOCON_ENO_EN    (1U) /* rx fifo outlet enable */
#define ASCLIN_RXFIFOCON_INW_SHIFT (6U)
#define ASCLIN_RXFIFOCON_INW_VAL   (1U) /* rx fifo outlet width */

#define ASCLIN_FLAGSCLEAR_MASK (0xFFFFFFFFU)

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/


/****************************************************************************8**
**                      Private Function Declarations                         **
*******************************************************************************/


/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/


/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/


/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
static volatile Ifx_ASCLIN *psASCLIN;

#ifdef _TASKING_C_TRICORE_
#pragma section farbss="DEFAULT_RAM_8BIT"
#elif (defined _GNU_C_TRICORE_)
#pragma section ".data.DEFAULT_RAM_8BIT" aw 1
#endif

static char ubOutputBuf[120];

#ifdef _TASKING_C_TRICORE_
#pragma section farbss restore
#elif (defined _GNU_C_TRICORE_)
#pragma section
#endif
/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/


/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Local Function Declarations                           **
*******************************************************************************/
void put_char(char);
int get_char(void);
void Ifx_Console_print(const char *p_frm, ...);
void print_f(const char *p_frm, ...);
void getline(char *p_line, uint32 n_max);

LOCAL_INLINE void delay(void)
{
  volatile int i;
  for (i = 0; i < 100; i++) {};
}

/*******************************************************************************
** Syntax : void Test_InitPrint(void)                                         **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:                                                                **
**                                                                            **
** Reentrancy:                                                                **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : This function Initializes the Printing on Serial             **
**               Communication Port. Baud rate : 115,200 Hz                   **
*******************************************************************************/
void Test_InitPrint(void)
{
  volatile int i;

  psASCLIN = &MODULE_ASCLIN0;

  // Mcal_ResetCpuEndInitProtection();
  // psASCLIN->CLC.U =  0x00000000;
  // while(psASCLIN->CLC.U) ;
  // Mcal_SetCpuEndInitProtection();
  Mcal_WriteCpuEndInitProtReg((uint32*)&MODULE_ASCLIN0.CLC.U, (uint32)0x00000000);

  while(psASCLIN->CLC.U) {};

  psASCLIN->CSR.B.CLKSEL = ASCLIN_CSR_CLKSEL_NOCLK ;
  for (i = 0; i < 1000; i++)
  {;}
  /* select the operation mode (INIT)*/
  psASCLIN->FRAMECON.B.MODE  =  ASCLIN_FRAMECON_MODE_INIT  ;
  for (i = 0; i < 1000; i++)
  {;}
  /* activate the clock source */
  psASCLIN->CSR.B.CLKSEL       =  ASCLIN_CSR_CLKSEL ;

  /* provide delay of 2-fA clock cycles */
  for (i = 0; i < 1000; i++)
  {;}

  /* deactivate the clock source */
  psASCLIN->CSR.B.CLKSEL       = ASCLIN_CSR_CLKSEL_NOCLK ;
  for (i = 0; i < 1000; i++)
  {;}
  psASCLIN->FRAMECON.B.MODE =  ASCLIN_FRAMECON_MODE_ASC ;
  for (i = 0; i < 1000; i++)
  {;}
  /* activate the clock source */
  psASCLIN->CSR.B.CLKSEL       =  ASCLIN_CSR_CLKSEL ;

  /* provide delay of 2-fA clock cycles */
  for (i = 0; i < 100; i++)
  {;}

  /* deactivate the clock source */
  psASCLIN->CSR.B.CLKSEL =  ASCLIN_CSR_CLKSEL_NOCLK ;
  /* select 1 stop bit */
  psASCLIN->FRAMECON.B.MSB = 0U;
  psASCLIN->FRAMECON.B.LEAD = 0U;
  psASCLIN->FRAMECON.B.IDLE = 0;
  psASCLIN->FRAMECON.B.PEN  = 0U;

  psASCLIN->FRAMECON.U |= (1U << 9);

  psASCLIN->DATCON.B.DATLEN = ASCLIN_DATCON_DATLEN;

  /* rx fifo inlet enable, rx fifo outlet width */
  psASCLIN->RXFIFOCON.B.OUTW = ASCLIN_RXFIFOCON_INW_VAL ; /*1*/
  psASCLIN->RXFIFOCON.B.ENI = ASCLIN_RXFIFOCON_ENO_EN ; /*1*/
  psASCLIN->RXFIFOCON.B.FLUSH = 1 ;
  psASCLIN->RXFIFOCON.B.INTLEVEL = 0;
  psASCLIN->RXFIFOCON.B.BUF    = 0U;

  /* tx fifo inlet enable, tx fifo outlet width */
  psASCLIN->TXFIFOCON.B.INW = ASCLIN_TXFIFOCON_INW_VAL ;
  psASCLIN->TXFIFOCON.B.ENO = ASCLIN_TXFIFOCON_ENO_EN ;
  psASCLIN->TXFIFOCON.B.FLUSH = 1 ;
  psASCLIN->TXFIFOCON.B.INTLEVEL = 0;

  psASCLIN->BITCON.U =
    (ASCLIN_BITCON_OVERSAMPLING << ASCLIN_BITCON_OVERSAMPLING_SHIFT)
    | (ASCLIN_BITCON_PRESCALAR << ASCLIN_BITCON_PRESCALAR_SHIFT)
    | (ASCLIN_BITCON_SAMPLEPOINT << ASCLIN_BITCON_SAMPLEPOINT_SHIFT)
    | (ASCLIN_BITCON_SM << ASCLIN_BITCON_SM_SHIFT);

  psASCLIN->BRG.U = (ASCLIN_BRG_NUMERATOR << ASCLIN_BRG_NUMERATOR_SHIFT)
                    | (ASCLIN_BRG_DENOMINATOR << ASCLIN_BRG_DENOMINATOR_SHIFT);

  /* Select line A is used as Rx Input line*/
  psASCLIN->IOCR.B.ALTI =  0x0;

  /*  - P14.1 is used as ASCLIN0 receive input signal (ASCLIN0_RX)
     - the input pull-up device is assigned */

  /*  - P14.0 is used as ASCLIN0 transmit output signal (ASCLIN0_TX)
     - the push/pull function is activated (ALT2)
    - output driver characteristic: GRADE1 */


  /* activate the clock source */
  psASCLIN->CSR.B.CLKSEL =  ASCLIN_CSR_CLKSEL;
  for (i = 0; i < 100; i++)
  {;}

  psASCLIN->CSR.B.CLKSEL =  4;
  for (i = 0; i < 100; i++)
  {;}

  /* clear the interrupt event flags*/
  psASCLIN->FLAGSCLEAR.U =  ASCLIN_FLAGSCLEAR_MASK;

}

/*******************************************************************************
** Syntax : uint32 getlineWithPos(char *p_line, uint32 n_max, uint32 pos)     **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:                                                                **
**                                                                            **
** Reentrancy:                                                                **
**                                                                            **
** Parameters (in): p_line , n_max , pos                                      **
**                                                                            **
** Parameters (out): uint32: new char arrived is TAB or CR                    **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : This function used to Read input from communication Port     **
*******************************************************************************/
int getlineWithPos(char *p_line, uint32 n_max, uint32 *pos)
{
  uint32 w_cnt;
  uint32 ret_val;
  int w_key;

  w_cnt = *pos;
  p_line += *pos;
  ret_val = 0;


  do
  {
    w_key = get_ch();
    if (w_key == -1)
    {
      ret_val = 0;
    }
    else
    {
      if ((w_key == CR) || (w_key == LF))
      {
        *p_line = 0;
        ret_val = CR;
      }
      else
      {

        if (w_key == TAB)
        {
          *p_line = 0; /* set the value to 0 so that the first part of the string can be analyzed */
          ret_val = TAB;
        }
        else
        {
          if ((w_key == BACKSPACE) || (w_key == DEL))
          {
            /* backspace or delete */

            if (w_cnt != 0)

            {
              /* delete character */
              w_cnt--;
              p_line--;
              put_char(BACKSPACE);
              put_char(' ');
              put_char(BACKSPACE);
            }
          }
          else
          {
            if ((w_key != CNTLQ) && (w_key != CNTLS))
            {
              /* normal character*/
              {
                /* store/reflect character */
                *p_line = (char)w_key;
                put_char ((char)w_key);
                p_line++;
                w_cnt++;
                if (w_cnt == n_max)
                {
                  /* limit reached */
                  (void)beep();
                  /* delete all characters */
                  while (w_cnt != 0)
                  {
                    w_cnt--;
                    p_line--;
                    put_char(BACKSPACE);
                    put_char(' ');
                    put_char(BACKSPACE);

                  }
                }
              }
            }
          }
        }
      }
    }
  }
  while ((w_key != CR) && (w_key != LF) && (w_key != BACKSPACE) && \
         (w_key != DEL) && (w_key != TAB));
  *pos = w_cnt;
  return(ret_val);
}
/*******************************************************************************
** Syntax : int get_char(void)                                                **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:                                                                **
**                                                                            **
** Reentrancy:                                                                **
**                                                                            **
** Parameters (in):                                                           **
**                                                                            **
** Parameters (out): int                                                      **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : This function used to put the character to terminal          **
**               and waits till a char is entered.                            **
*******************************************************************************/
volatile uint32 rxdata1;
int get_char(void)
/*~-*/
{
  volatile uint32 rxdata;

  /*~L*/
  /* Wait till RX fifo is NOT empty */
  while ((psASCLIN->RXFIFOCON.B.FILL)  == 0)
    /*~-*/
  {
    /*~T*/
    delay();
    /*~-*/
  }
  /*~E*/
  /*~T*/
  /* get byte */
  rxdata = psASCLIN->RXDATA.U;

  psASCLIN->FLAGSCLEAR.U = ASCLIN_FLAGSCLEAR_MASK;
  rxdata1 = rxdata;
  return rxdata;
  /*~-*/
}
/*******************************************************************************
** Syntax : void put_char(char z)                                             **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:                                                                **
**                                                                            **
** Reentrancy:                                                                **
**                                                                            **
** Parameters (in):                                                           **
**                                                                            **
** Parameters (out): void                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : This function sends a character to Communication Port.       **
*******************************************************************************/
void put_char(char z)
/*~-*/
{
  /*~T*/
  /* send character */
  psASCLIN->FLAGSCLEAR.U = ASCLIN_FLAGSCLEAR_MASK;
  psASCLIN->TXDATA.U = (uint32)z;

  /*~I*/
  if (z == LF)
    /*~-*/
  {
    /*~L*/
    while ( (psASCLIN->TXFIFOCON.B.FILL) != 0)
      /*~-*/
    {
      /*~T*/
      delay();

      /*~-*/
    }
    /*~E*/
    /*~T*/
    /* send CR */
    psASCLIN->FLAGSCLEAR.U = ASCLIN_FLAGSCLEAR_MASK;
    psASCLIN->TXDATA.U = CR;
    /*~-*/
  }
  /*~E*/
  /*~L*/
  while ( (psASCLIN->TXFIFOCON.B.FILL ) != 0)
    /*~-*/
  {
    /*~T*/
    delay();
    /*~-*/
  }
  /*~E*/
  psASCLIN->FLAGSCLEAR.U = ASCLIN_FLAGSCLEAR_MASK;

  /*~-*/
}


/*******************************************************************************
** Syntax : void buf_to_screen(char *text_buf)                                **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:                                                                **
**                                                                            **
** Reentrancy:                                                                **
**                                                                            **
** Parameters (in):                                                           **
**                                                                            **
** Parameters (out): void                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : This function holds the Sting to be buffered to the          **
**               Communication Port.                                          **
*******************************************************************************/
void buf_to_screen(char *text_buf)
/*~-*/
{
  /*~L*/
  while (*text_buf != 0)
    /*~-*/
  {
    /*~T*/
    /* send character */
    put_char(*text_buf);
    text_buf++;

    /*~-*/
  }
  /*~E*/
  /*~-*/
}

/*******************************************************************************
** Syntax : void print_f(const char *p_frm, ...)                              **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:                                                                **
**                                                                            **
** Reentrancy:                                                                **
**                                                                            **
** Parameters (in):                                                           **
**                                                                            **
** Parameters (out): void                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : This function Prints a formatted string to the               **
**               Communication Port.                                          **
*******************************************************************************/

void Ifx_Console_print (const char *p_frm, ...)
{
}
void print_f(const char *p_frm, ...)
/*~-*/
{
  /*~T*/
  va_list p_arg;

  /*~T*/
  va_start(p_arg, p_frm);
  vsprintf(ubOutputBuf, p_frm, p_arg);
  va_end(p_arg);
  buf_to_screen(ubOutputBuf);

  /*~-*/
}

/*******************************************************************************
** Syntax : void getline(char *p_line, uint32 n_max)                          **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:                                                                **
**                                                                            **
** Reentrancy:                                                                **
**                                                                            **
** Parameters (in): p_line and n_max                                          **
**                                                                            **
** Parameters (out): void                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : This function used to Read input from communication Port     **
*******************************************************************************/
void getline(char *p_line, uint32 n_max)

/*~-*/
{
  /*~T*/
  uint32 w_cnt;
  int w_key;

  /*~T*/
  w_cnt = 0;

  /*~U*/
  /*~-2*/
  do
  {
    /*~T*/
    w_key = get_char();
    /*~I*/
    if ((w_key == CR) || (w_key == LF))

      /*~-*/
    {
      /*~T*/
      *p_line = 0;

      /*~-*/
    }
    /*~O*/
    /*~-2*/
    else
    {
      /*~I*/
      if ((w_key == BACKSPACE) || (w_key == DEL))

        /*~-*/
      {
        /*~T*/
        /* backspace or delete */

        /*~I*/
        if (w_cnt != 0)

          /*~-*/
        {
          /*~T*/
          /* delete character */
          w_cnt--;
          p_line--;
          put_char(BACKSPACE);
          put_char(' ');
          put_char(BACKSPACE);

          /*~-*/
        }
        /*~E*/
        /*~-*/
      }
      /*~O*/
      /*~-2*/
      else
      {
        /*~I*/
        if ((w_key != CNTLQ) && (w_key != CNTLS))

          /*~-*/
        {
          /*~F*/
          /* normal character*/

          /*~-*/
          {
            /*~T*/
            /* store/reflect character */
            *p_line = (char)w_key;
            put_char ((char)w_key);
            p_line++;
            w_cnt++;

            /*~I*/
            if (w_cnt == n_max)
              /*~-*/
            {
              /*~T*/
              /* limit reached */
              (void)beep();

              /*~T*/
              /* delete all characters */

              /*~L*/
              while (w_cnt != 0)
                /*~-*/
              {
                /*~T*/
                w_cnt--;
                p_line--;
                put_char(BACKSPACE);
                put_char(' ');
                put_char(BACKSPACE);

                /*~-*/
              }
              /*~E*/
              /*~-*/
            }
            /*~E*/
            /*~-*/
          }
          /*~E*/
          /*~-*/
        }
        /*~E*/
        /*~-*/
      }
      /*~E*/
      /*~-*/
    }
    /*~E*/
    /*~-*/
  }
  /*~O*/
  while ((w_key != CR) && (w_key != LF));
  /*~E*/
  /*~-*/
}

/*******************************************************************************
** Syntax : int get_ch(void)                                                  **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:                                                                **
**                                                                            **
** Reentrancy:                                                                **
**                                                                            **
** Parameters (in):  None                                                     **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value: int(ASCII value for the input character)                     **
**                                                                            **
** Description :This function reads a character from the Commucation port     **
**              and does not wait.                                            **
*******************************************************************************/
int get_ch(void)
{
  uint32 c;

  if (psASCLIN->RXFIFOCON.B.FILL  != 0)
  {
    c = (char)psASCLIN->RXDATA.U ;
    psASCLIN->FLAGSCLEAR.U = ASCLIN_FLAGSCLEAR_MASK;
    return c;
  }
  else
  {
    return (-1);
  }
}

/*******************************************************************************
** Syntax : void Continue(void)                                               **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:                                                                **
**                                                                            **
** Reentrancy:                                                                **
**                                                                            **
** Parameters (in):                                                           **
**                                                                            **
** Parameters (out): void                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : This function waits to get input from communication Port     **
*******************************************************************************/
void Continue(void)
{
  char szString[4];
  do
  {
    print_f("\n<ENTER>to continue: ");
    getline(szString, sizeof szString - 1);
    if (*szString != 0)
    {
      (void)beep();
    }
  }
  while (*szString != 0);
}


/*******************************************************************************
** Syntax : char ParMenu(char *pszText, PAR_t *pstPar, uint32 uwParNum)       **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:                                                                **
**                                                                            **
** Reentrancy:                                                                **
**                                                                            **
** Parameters (in):                                                           **
**                                                                            **
** Parameters (out): void                                                     **
**                                                                            **
** Return value: char                                                         **
**                                                                            **
** Description : This function used to check Parameter size and type.         **
*******************************************************************************/
char ParMenu(char *pszText, PAR_t *pstPar, uint32 uwParNum)
{
  char szString[81];
  PAR_t *pst;
  uint32 uwData;
  uint32 uwId;

  do
  {
    print_f("\nParameters for %s:\n", pszText);
    pst = pstPar;
    for (uwId = 0; uwId < uwParNum; uwId++)
    {
      print_f("<%d>%s: ", uwId, pst->szText);
      pst = pstPar + uwId;
      switch (pst->uwSize)
      {
        case 1:
        {
          print_f(pst->szOutputFormat, (uint32) * (uint8 *)pst->pvData);
          break;
        }
        case 2:
        {
          print_f(pst->szOutputFormat, (uint32) * (uint16 *)pst->pvData);
          break;
        }
        case 4:
        {
          print_f(pst->szOutputFormat, *(uint32 *)pst->pvData);
          break;
        }
        default:
        {
          print_f("\nINTERNAL ERROR - INVALID PARAMETER SIZE\n");
          return 'q';
        }
      }
      print_f("\n");
      pst++;
    }
    print_f("\n<Id Data> or <q>uit or <ENTER>continue: ");
    getline(szString, sizeof szString - 1);
    if ((*szString != 'q') && (*szString != 0))
    {
      if ((sscanf(szString, "%ld", &uwId)) && (uwId < uwParNum))
      {
        pst = pstPar + uwId;
        switch (pst->uwType)
        {
          case PAR_TYP_DEC:
          {
            if (sscanf(szString, "%ld %ld", &uwId, &uwData) == 2)
            {
              if (((sint32)uwData >= (sint32)pst->uwMin) &&
                  ((sint32)uwData <= (sint32)pst->uwMax))
              {
                switch (pst->uwSize)
                {
                  case 1:
                  {
                    *(sint8 *)pst->pvData = (sint8)uwData;
                    break;
                  }
                  case 2:
                  {
                    *(sint16 *)pst->pvData = (sint16)uwData;
                    break;
                  }
                  case 4:
                  {
                    *(sint32 *)pst->pvData = (sint32)uwData;
                    break;
                  }
                  default:
                  {
                    print_f("\nINTERNAL ERROR - INVALID PARAMETER \
                                              SIZE\n");
                    return 'q';
                  }
                }
              }
              else
              {
                (void)beep();
              }
            }
            else
            {
              (void)beep();

            }
            break;
          }
          case PAR_TYP_HEX:
          {
            if (sscanf(szString, "%ld %lx", &uwId, &uwData) == 2)
            {
              if ((uwData >= pst->uwMin) && (uwData <= pst->uwMax))
              {
                switch (pst->uwSize)
                {
                  case 1:
                  {
                    *(uint8 *)pst->pvData = (uint8)uwData;
                    break;
                  }
                  case 2:
                  {
                    *(uint16 *)pst->pvData = (uint16)uwData;
                    break;
                  }
                  case 4:
                  {
                    *(uint32 *)pst->pvData = (uint32)uwData;
                    break;
                  }

                  default:
                  {
                    print_f("\nINTERNAL ERROR - INVALID PARAMETER \
                                              SIZE\n");
                    return 'q';
                  }
                }
              }
              else
              {
                (void)beep();
              }
            }
            else
            {
              (void)beep();
            }
            break;
          }

          default:
          {
            (void)beep();
            print_f("\nINTERNAL ERROR - INVALID PARAMETER TYPE\n");
            return 'q';
          }

        }
      }
      else
      {
        (void)beep();
      }
    }
  }
  while ((*szString != 'q') && (*szString != 0));

  print_f("\n\n");

  return *szString;
}

/*******************************************************************************
** Syntax : void ClearBuffer(uint32* buf, uint32 size)                        **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:                                                                **
**                                                                            **
** Reentrancy:                                                                **
**                                                                            **
** Parameters (in):   buf and size                                            **
**                                                                            **
** Parameters (out): void                                                     **
**                                                                            **
** Return value: void                                                         **
**                                                                            **
** Description : This function used to clear the given buffer                 **
*******************************************************************************/
void ClearBuffer(uint32* buf, uint32 size)
{
  uint32 m;
  for(m = 0; m < size; m++)
  {
    buf[m] = 0;
  }
}

/*******************************************************************************
** Syntax : void SetBuffer(uint32* buf, uint32 size, uint32 seed)             **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:                                                                **
**                                                                            **
** Reentrancy:                                                                **
**                                                                            **
** Parameters (in):   buf,size and seed                                       **
**                                                                            **
** Parameters (out): void                                                     **
**                                                                            **
** Return value: void                                                         **
**                                                                            **
** Description : This function used to write the given value in to the buffer **
*******************************************************************************/
void SetBuffer(uint32* buf, uint32 size, uint32 seed)
{
  uint32 m;
  for(m = 0; m < size; m++)
  {
    buf[m] =  (uint32)( (size / 10 * (m + 3)) + (seed * (m + 1))) ;
  }
}

/*******************************************************************************
** Syntax : void print_flushfifo()                                            **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:                                                                **
**                                                                            **
** Reentrancy:                                                                **
**                                                                            **
** Parameters (in):   none                                                    **
**                                                                            **
** Parameters (out): void                                                     **
**                                                                            **
** Return value: void                                                         **
**                                                                            **
** Description : This function flushes TX and RX FIFO of ASCLIN               **
*******************************************************************************/
void print_flushfifo(void)
{
  psASCLIN->RXFIFOCON.B.FLUSH = 1 ;
  psASCLIN->TXFIFOCON.B.FLUSH = 1 ;
}

/*******************************************************************************
** Syntax : void StartResult(void)                                            **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:                                                                **
**                                                                            **
** Reentrancy:                                                                **
**                                                                            **
** Parameters (in):   none                                                    **
**                                                                            **
** Parameters (out): void                                                     **
**                                                                            **
** Return value: void                                                         **
**                                                                            **
** Description : This fnt indicates the Start of the DemoApp Result printing  **
*******************************************************************************/
void StartResult(void)
{
  print_f("\n\nRESULT_START\n");
}

/*******************************************************************************
** Syntax : void EndResult(void)                                            **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:                                                                **
**                                                                            **
** Reentrancy:                                                                **
**                                                                            **
** Parameters (in):   none                                                    **
**                                                                            **
** Parameters (out): void                                                     **
**                                                                            **
** Return value: void                                                         **
**                                                                            **
** Description : This fnt indicates the End of the DemoApp Result printing    **
*******************************************************************************/
void EndResult(void)
{
  print_f("\nRESULT_END\n\n");
}
