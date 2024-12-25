/* 
 * File:   IN_EEPROM_PROGRAM.C
 * Author: ziad osama
 *
 * Created on October 25, 2024, 4:41 PM
 */
/*_____________________________________________________________________________*/
/*                         Section : Includes                                  */
/*_____________________________________________________________________________*/
#include "IN_EEPROM_INTERFACE.h"

/*_____________________________________________________________________________*/
/*                         Section : APIs Definitions                          */
/*_____________________________________________________________________________*/
std_ReturnType INTERNAL_EEPROM_WRITE_DATA_BYTE(uint16 Address ,uint8 Data)
{
    std_ReturnType RET = E_OK;
    /*Read The Interrupt Status Is Enable Or Disable & Disable it If is Enable*/
    uint8 Globle_Interrupt_Satus = READ_BIT(INTCON,GIE);
    /*Update The Address Registers */
    EEADRH = (uint8)((Address >> 8) & 0x03);
    EEADR = (uint8)(Address & 0xFF);
    /*Update The Data Register */
    EEDATA = (uint8)(Data);
    /* Data EEPROM Memory Select  Access data EEPROM memory */
    CLEAR_BIT(EECON1,EEPGD);
    /*Access Flash program or data EEPROM memory*/
    CLEAR_BIT(EECON1,CFGS);
    /* Allows write cycles to Flash program/Data EEPROM*/
    SET_BIT(EECON1,WREN);
    /* Disable The Global Interrupt */
    GLOBAL_INTERRUPT_DISABLE();
    /* write will not begin if this sequence is not exactly
       followed (write 55h to EECON2, write 0AAh to EECON2 */
    EECON2 = 0x55;
    EECON2 = 0xAA;
    /* Initiates a data EEPROM erase/write cycle or a program memory erase cycle or write cycle*/
    SET_BIT(EECON1,WR);
    /* Wait Till the writing Operation Is Completed */
    while((READ_BIT(EECON1,WR))) asm("NOP");
    /* Inhibits write cycles to Flash program/data EEPROM */
    CLEAR_BIT(EECON1,WREN);
    /*Return The Status Of The Interrupt */
    if(Globle_Interrupt_Satus == 1)
    {
        GLOBAL_INTERRUPT_ENABLE();
    }
    else
    { 
        asm("NOP");
    }
    return (RET);
}
std_ReturnType INTERNAL_EEPROM_READ_DATA_BYTE(uint16 Address ,uint8 * Data)
{
    std_ReturnType RET = E_OK ;
    if(Data == NULL)
    {
        RET = E_NOT_OK ;
    }
    else
    {
        /*Update The Address Registers */
        EEADRH = (uint8)((Address >> 8) & 0x03);
        EEADR = (uint8)(Address & 0xFF);
        /* Data EEPROM Memory Select  Access data EEPROM memory */
        CLEAR_BIT(EECON1,EEPGD);
        /*Access Flash program or data EEPROM memory*/
        CLEAR_BIT(EECON1,CFGS);
        /* set control bit RD to Start The Reading Operation */
        SET_BIT(EECON1,RD);
        /* According to the data sheet make 2 no operation
         * instructions if you use high frequency       */
        asm("NOP");
        asm("NOP");
        /* Read The Data */
        *Data = EEDATA ;
    }
    return (RET);
}