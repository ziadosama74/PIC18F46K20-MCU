/* 
 * File:   IN_EEPROM_REGISTERS.h
 * Author: ziad osama
 *
 * Created on October 25, 2024, 4:40 PM
 */

#ifndef IN_EEPROM_REGISTERS_H
#define	IN_EEPROM_REGISTERS_H
/*_____________________________________________________________________________*/
/*                         Section : Macro Definitions                         */
/*_____________________________________________________________________________*/
/* EEPROM Control Register 1 (set the configurations from it) */
#define       EECON1             HWREG8(0xFA6)
#define                 RD              0
#define                 WR              1
#define                 WREN            2
#define                 WRERR           3
#define                 FREE            4
#define                 CFGS            6
#define                 EEPGD           7
/* EEPROM Control Register 2 (Is For The Sequence) */
#define       EECON2             HWREG8(0xFA7)
/*  EEPROM Data Register */
#define       EEDATA             HWREG8(0xFA8)
/*  EEPROM Address Registers */
#define       EEADR              HWREG8(0xFA9) /*8 BITS*/
#define       EEADRH             HWREG8(0xFAA) /*2 BITS*/

#endif	/* IN_EEPROM_REGISTERS_H */

