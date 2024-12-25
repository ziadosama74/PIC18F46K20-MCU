/* 
 * File:   TIMER0_REGISTERS.h
 * Author: ziad osama
 *
 * Created on November 9, 2024, 6:52 PM
 */

#ifndef TIMER0_REGISTERS_H
#define	TIMER0_REGISTERS_H
/*_____________________________________________________________________________*/
/*                         Section : Includes                                  */
/*_____________________________________________________________________________*/
#include "../../MCAL_STD_TYPES.h"
/*_____________________________________________________________________________*/
/*                         Section : Macro Definitions                         */
/*_____________________________________________________________________________*/
#define           T0CON                        HWREG8(0xFD5)
#define                  T0PS0                      0
#define                  T0PS1                      1
#define                  T0PS2                      2
#define                  PSA                        3
#define                  T0SE                       4
#define                  T0CS                       5
#define                  T08BIT                     6
#define                  TMR0ON                     7
/*_____________________________________________________________________________*/
#define           TMR0H                        HWREG8(0xFD7)
/*_____________________________________________________________________________*/
#define           TMR0L                        HWREG8(0xFD6)
/*_____________________________________________________________________________*/
#endif	/* TIMER0_REGISTERS_H */

