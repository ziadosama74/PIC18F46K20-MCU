/* 
 * File:   TIMER3_REGISTER.h
 * Author: ziad osama
 *
 * Created on November 15, 2024, 12:47 AM
 */

#ifndef TIMER3_REGISTER_H
#define	TIMER3_REGISTER_H
/*_____________________________________________________________________________*/
/*                         Section : Includes                                  */
/*_____________________________________________________________________________*/
#include "../../MCAL_STD_TYPES.h"
/*_____________________________________________________________________________*/
/*                         Section : Macro Definitions                         */
/*_____________________________________________________________________________*/
#define           T3CON                             HWREG8(0xFB1)
#define                 TMR3ON                           0
#define                 TMR3CS                           1
#define                 T3SYNC                           2
#define                 T3CCP1                           3
#define                 T3CKPS0                          4
#define                 T3CKPS1                          5
#define                 T3CCP2                           6
#define                 RD16                             7
/*_____________________________________________________________________________*/
#define          TMR3L                              HWREG8(0xFB2)
/*_____________________________________________________________________________*/
#define          TMR3H                              HWREG8(0xFB3)

#endif	/* TIMER3_REGISTER_H */

