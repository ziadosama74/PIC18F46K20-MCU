/* 
 * File:   USART_REGISTERS.h
 * Author: ziad osama
 *
 * Created on November 30, 2024, 3:14 PM
 */

#ifndef USART_REGISTERS_H
#define	USART_REGISTERS_H
/*_____________________________________________________________________________*/
/*                         Section : Includes                                  */
/*_____________________________________________________________________________*/
#include "../MCAL_STD_TYPES.h"
/*_____________________________________________________________________________*/
/*                         Section : Macro Definitions                         */
/*_____________________________________________________________________________*/
#define           TXSTA                                  HWREG8(0xFAC)
#define                 TX9D                                  0
#define                 TRMT                                  1
#define                 BRGH                                  2
#define                 SENDB                                 3
#define                 SYNC                                  4
#define                 TXEN                                  5
#define                 TX9                                   6
#define                 CSRC                                  7
/*_____________________________________________________________________________*/
#define           RCSTA                                  HWREG8(0xFAB)
#define                 RX9D                                  0
#define                 OERR                                  1
#define                 FERR                                  2
#define                 ADDEN                                 3
#define                 CREN                                  4
#define                 SREN                                  5
#define                 RX9                                   6
#define                 SPEN                                  7
/*_____________________________________________________________________________*/
#define           BAUDCON                                HWREG8(0xFB8)
#define                 ABDEN                                 0
#define                 WUE                                   1
#define                 BRG16                                 3
#define                 TXCKP                                 4
#define                 RXDTP                                 5
#define                 RCIDL                                 6
#define                 ABDOVF                                7
/*_____________________________________________________________________________*/
// USART Transmit Register
#define           TXREG                                  HWREG8(0xFAD)
/*_____________________________________________________________________________*/
// USART Receive Register
#define           RCREG                                  HWREG8(0xFAE)
/*_____________________________________________________________________________*/
// USART Baud Rate Generator Register High Byte
#define           SPBRGH                                 HWREG8(0xFB0)
/*_____________________________________________________________________________*/
// USART Baud Rate Generator Register Low Byte
#define           SPBRG                                  HWREG8(0xFAF)
/*_____________________________________________________________________________*/
#define           TRISC                                  HWREG8(0xF94)
#define                 RC6                                 6
#define                 RC7                                 7
#endif	/* USART_REGISTERS_H */

