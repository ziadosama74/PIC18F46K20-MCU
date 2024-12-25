/* 
 * File:   TIMER2_REGISTERS.h
 * Author: ziad osama
 *
 * Created on November 12, 2024, 7:33 PM
 */

#ifndef TIMER2_REGISTERS_H
#define	TIMER2_REGISTERS_H
/*_____________________________________________________________________________*/
/*                         Section : Includes                                  */
/*_____________________________________________________________________________*/
#include "../../MCAL_STD_TYPES.h"
/*_____________________________________________________________________________*/
/*                         Section : Macro Definitions                         */
/*_____________________________________________________________________________*/
#define          T2CON                           HWREG8(0xFCA)
#define                  T2CKPS0                       0
#define                  T2CKPS1                       1
#define                  TMR2ON                        2
#define                  T2OUTPS0                      3
#define                  T2OUTPS1                      4
#define                  T2OUTPS2                      5
#define                  T2OUTPS3                      6
/*_____________________________________________________________________________*/
#define          TMR2                            HWREG8(0xFCC)
/*_____________________________________________________________________________*/
#define          PR2                             HWREG8(0xFCB)
/*_____________________________________________________________________________*/
#endif	/* TIMER2_REGISTERS_H */

