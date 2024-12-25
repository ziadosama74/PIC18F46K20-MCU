/* 
 * File:   MSSP_REGISTERS.h
 * Author: ziad osama
 *
 * Created on December 9, 2024, 9:33 PM
 */
#ifndef MSSP_REGISTERS_H
#define	MSSP_REGISTERS_H
/*_____________________________________________________________________________*/
/*                         Section : Includes                                  */
/*_____________________________________________________________________________*/
#include "../MCAL_STD_TYPES.h"
/*_____________________________________________________________________________*/
/*                         Section : Macro Definitions                         */
/*_____________________________________________________________________________*/
#define         SSPSTAT                           HWREG8(0xFC7)
#define                 BF                             0
#define                 UA                             1
#define                 R_W                            2
#define                 S                              3
#define                 P                              4
#define                 D_A                            5
#define                 CKE                            6
#define                 SMP                            7
/*_____________________________________________________________________________*/
#define         SSPCON1                           HWREG8(0xFC6)
#define                 SSPM0                          0
#define                 SSPM1                          1
#define                 SSPM2                          2
#define                 SSPM3                          3
#define                 CKP                            4
#define                 SSPEN                          5
#define                 SSPOV                          6
#define                 WCOL                           7
/*_____________________________________________________________________________*/
#define         SSPCON2                           HWREG8(0xFC5)
#define                 SEN                            0
#define                 RSEN                           1
#define                 PEN                            2
#define                 RCEN                           3
#define                 ACKEN                          4
#define                 ACKDT                          5
#define                 ACKSTAT                        6
#define                 GCEN                           7
/*_____________________________________________________________________________*/
#define         SSPBUF                           HWREG8(0xFC9)
/*_____________________________________________________________________________*/
#define         SSPADD                           HWREG8(0xFC8)
/*_____________________________________________________________________________*/
#endif	/* MSSP_REGISTERS_H */

