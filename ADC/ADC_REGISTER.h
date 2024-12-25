/* 
 * File:   ADC_REGISTER.h
 * Author: ziad osama
 *
 * Created on November 4, 2024, 8:58 PM
 */

#ifndef ADC_REGISTER_H
#define	ADC_REGISTER_H
/*_____________________________________________________________________________*/
/*                         Section : Includes                                  */
/*_____________________________________________________________________________*/
#include "../MCAL_STD_TYPES.h"
/*_____________________________________________________________________________*/
/*                         Section : Macro Definitions                         */
/*_____________________________________________________________________________*/
/*_____________________RESULT__ADC__REGISTERS__________________________________*/
#define       ADRESH            HWREG8(0xFC4)              
#define       ADRESL            HWREG8(0xFC3)
/*_____________________________________________________________________________*/
#define       ADCON0            HWREG8(0xFC2)
#define             ADON             0
#define             GO_DONE          1
#define             CHS0             2
#define             CHS1             3
#define             CHS2             4
#define             CHS3             5
/*_____________________________________________________________________________*/
#define       ADCON1            HWREG8(0xFC1)
#define             PCFG0            0
#define             PCFG1            1
#define             PCFG2            2
#define             PCFG3            3
#define             VCFG0            4
#define             VCFG1            5
/*_____________________________________________________________________________*/
#define       ADCON2            HWREG8(0xFC0)
#define             ADCS0            0
#define             ADCS1            1
#define             ADCS2            2
#define             ACQT0            3
#define             ACQT1            4
#define             ACQT2            5
#define             ADFM             7
/*_____________________________________________________________________________*/
#endif	/* ADC_REGISTER_H */

