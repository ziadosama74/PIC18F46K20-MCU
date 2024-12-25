/* 
 * File:   CCP_REGISTER.h
 * Author: ziad osama
 *
 * Created on November 21, 2024, 10:27 PM
 */

#ifndef CCP_REGISTER_H
#define	CCP_REGISTER_H
/*_____________________________________________________________________________*/
/*                         Section : Includes                                  */
/*_____________________________________________________________________________*/
#include "../MCAL_STD_TYPES.h"
/*_____________________________________________________________________________*/
/*                         Section : Macro Definitions                         */
/*_____________________________________________________________________________*/
#define            CCPR1H                                    HWREG8(0xFBF)
#define            CCPR1L                                    HWREG8(0xFBE)
/*_____________________________________________________________________________*/
#define            CCP1CON                                   HWREG8(0xFBD)
#define                     CCP1M0                                 0
#define                     CCP1M1                                 1
#define                     CCP1M2                                 2
#define                     CCP1M3                                 3
#define                     DC1B0                                  4
#define                     DC1B1                                  5
#define                     P1M0                                   6
#define                     P1M1                                   7
/*_____________________________________________________________________________*/
#define            CCPR2H                                    HWREG8(0xFBC)
#define            CCPR2L                                    HWREG8(0xFBB)
/*_____________________________________________________________________________*/
#define            CCP2CON                                   HWREG8(0xFBA)
#define                     CCP2M0                                 0
#define                     CCP2M1                                 1
#define                     CCP2M2                                 2
#define                     CCP2M3                                 3
#define                     DC2B0                                  4
#define                     DC2B1                                  5
#define                     unimplemented1                         6
#define                     unimplemented2                         7
/*_____________________________________________________________________________*/
#endif	/* CCP_REGISTER_H */

