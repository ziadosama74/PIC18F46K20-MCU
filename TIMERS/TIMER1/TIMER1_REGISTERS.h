/* 
 * File:   TIMER1_REGISTERS.h
 * Author: ziad osama
 *
 * Created on November 11, 2024, 8:56 PM
 */

#ifndef TIMER1_REGISTERS_H
#define	TIMER1_REGISTERS_H
/*_____________________________________________________________________________*/
/*                         Section : Includes                                  */
/*_____________________________________________________________________________*/
#include "../../MCAL_STD_TYPES.h"
/*_____________________________________________________________________________*/
/*                         Section : Macro Definitions                         */
/*_____________________________________________________________________________*/
#define            T1CON                    HWREG8(0xFCD)
#define                 TMR1ON                    0
#define                 TMR1CS                    1
#define                 T1SYNC                    2
#define                 T1OSCEN                   3
#define                 T1CKPS0                   4
#define                 T1CKPS1                   5
#define                 T1RUN                     6
#define                 RD16                      7
/*_____________________________________________________________________________*/
#define            TMR1H                    HWREG8(0xFCF)
/*_____________________________________________________________________________*/
#define            TMR1L                    HWREG8(0xFCE)
/*_____________________________________________________________________________*/

#endif	/* TIMER1_REGISTERS_H */

