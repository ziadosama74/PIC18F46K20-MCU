/* 
 * File:   IN_EEPROM_INTERFACE.h
 * Author: ziad osama
 *
 * Created on October 25, 2024, 4:41 PM
 */

#ifndef IN_EEPROM_INTERFACE_H
#define	IN_EEPROM_INTERFACE_H
/*_____________________________________________________________________________*/
/*                         Section : Includes                                  */
/*_____________________________________________________________________________*/
#include "pic18f4620.h"
#include "../MCAL_STD_TYPES.h"
#include "../../MCAL_Layer/INTERRUPT/MCAL_INTERNAL_INTERRUPT.h"
#include "IN_EEPROM_REGISTERS.h"
/*_____________________________________________________________________________*/
/*                         Section : Macro Definitions                         */
/*_____________________________________________________________________________*/

/*_____________________________________________________________________________*/
/*                         Section : Data Types Declaration                    */
/*_____________________________________________________________________________*/

/*_____________________________________________________________________________*/
/*                         Section : APIs Declaration                          */
/*_____________________________________________________________________________*/
std_ReturnType INTERNAL_EEPROM_WRITE_DATA_BYTE(uint16 Address ,uint8 Data);
std_ReturnType INTERNAL_EEPROM_READ_DATA_BYTE(uint16 Address ,uint8 * Data);
#endif	/* IN_EEPROM_INTERFACE_H */

