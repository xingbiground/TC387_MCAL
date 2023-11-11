/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2021)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Test_Print.h                                                  **
**                                                                            **
**  VERSION   : 1.0.0                                                         **
**                                                                            **
**  DATE      : 2021-11-08                                                    **
**                                                                            **
**  VARIANT   : NA                                                            **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  :  This file exports the functionality of Test_Print.c       **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER [yes/no]: yes                                      **
**                                                                            **
*******************************************************************************/

#ifndef LLD_PRINT_H
#define LLD_PRINT_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#if defined _GHS_C_TRICORE_
#pragma ghs nowarning 1729
#include <stdio.h>
#pragma ghs endnowarning 1729
#else
#include <stdio.h>
#endif

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
#define BEL        0x07
#define TAB        0x09
#define XON        0x11
#define XOFF       0x13
#define CNTLQ      0x11
#define CNTLS      0x13
#define DEL        0x7F
#define BACKSPACE  0x08
#define CR         0x0D
#define LF         0x0A
#define ESC1       0x1B

#define beep()      putchar(0x07)
#define clreol()    printf("\033[K")
#define clrscr()    printf("\033[2J")
#define gotoxy(x,y) printf("\033[%d;%dH",y,x)
#define newline()   putchar(0x0A)
#define PAR_TYP_DEC 0
#define PAR_TYP_HEX 1

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
typedef struct
{
  uint32 uwType;
  uint32 uwSize;
  void *pvData;
  uint32 uwMin;
  uint32 uwMax;
  char  szText[81];
  char  szOutputFormat[6];
} PAR_t;

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
/*******************************************************************************
** Syntax : void Test_InitPrint(void)                                         **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:                                                                **
**                                                                            **
** Reentrancy:                                                                **
**                                                                            **
** Parameters (in):                                                           **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : This function Initializes the Printing on Serial             **
**               Communication Port.                                          **
*******************************************************************************/
extern void Test_InitPrint(void);


extern void StartResult(void);
extern void EndResult(void);

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
extern void put_char(char);

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
extern int get_char(void);

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
extern void print_f(const char *p_frm, ...);

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
extern void getline(char *p_line, uint32 n_max);

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
int getlineWithPos(char *p_line, uint32 n_max, uint32 *pos);

/*******************************************************************************
** Syntax : void erase_line(char *p_line,uint32 pos)                          **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:                                                                **
**                                                                            **
** Reentrancy:                                                                **
**                                                                            **
** Parameters (in): p_line , pos                                              **
**                                                                            **
** Parameters (out): void                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : This function used to erase the present received line        **
*******************************************************************************/
void erase_line(char *p_line, uint32 *pos);

/*******************************************************************************
** Syntax : void put_buffer(char *p_line, uint32 n_max,                       **
**                          const char *p_str,uint32 *pos)                    **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:                                                                **
**                                                                            **
** Reentrancy:                                                                **
**                                                                            **
** Parameters (in): p_line, n_max , p_str , pos                               **
**                                                                            **
** Parameters (out): void                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : This function fill buffer and send to terminal the string    **
*******************************************************************************/
void put_buffer(char *p_line, uint32 n_max, const char *p_str, uint32 *pos);

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
extern int get_ch(void);

/*******************************************************************************
** Syntax : void Print_Configuration(uint32 config)                           **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:                                                                **
**                                                                            **
** Reentrancy:                                                                **
**                                                                            **
** Parameters (in):   config                                                  **
**                                                                            **
** Parameters (out): void                                                     **
**                                                                            **
** Return value: void                                                         **
**                                                                            **
** Description : This function used  to print system clock frequency          **
*******************************************************************************/
extern void Print_Configuration(uint32 config);

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
extern void ClearBuffer(uint32* buf, uint32 size);

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
extern void SetBuffer(uint32* buf, uint32 size, uint32 seed);

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
extern  void Continue(void);

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
extern char ParMenu(char *pszText, PAR_t *pstPar, uint32 uwParNum);


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
extern void buf_to_screen(char *text_buf);

/*******************************************************************************
** Syntax : void print_FlushFifo()                                            **
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
extern void print_flushfifo(void);
#endif  /*  End of File print */
