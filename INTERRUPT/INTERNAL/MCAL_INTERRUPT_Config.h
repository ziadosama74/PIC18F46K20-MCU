/* 
 * File:   MCAL_INTERRUPT_Config.h
 * Author: ziad osama
 *
 * Created on October 18, 2024, 9:39 PM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/*____________________________________________________________________________*/
/*                         Section : Includes                                 */
/*____________________________________________________________________________*/
#include "INTERRUPT_GENERATE _CONFIGURATION.h"
/*____________________________________________________________________________*/
/*                         Section : Macro Declarations                       */
/*____________________________________________________________________________*/

/*____________________________________________________________________________*/
/*                         Section : Interrupt Registers                      */
/*____________________________________________________________________________*/
#define    INTCON                      HWREG8(0xFF2)
#define             RBIF              0
#define             INT0IF            1
#define             TMR0IF            2
#define             RBIE              3
#define             INT0IE            4
#define             TMR0IE            5
#define             GIEL              6
#define             PEIE              6
#define             GIEH              7
#define             GIE               7
/*____________________________________________________________________________*/

#define    INTCON2                     HWREG8(0xFF1)
#define             RBIP              0
#define             TMR0IP            2
#define             INTEDG2           4
#define             INTEDG1           5
#define             INTEDG0           6
#define             RBPU              7
/*____________________________________________________________________________*/

#define    INTCON3                     HWREG8(0xFF0)
#define             INT1IF            0
#define             INT2IF            1
#define             INT1IE            3
#define             INT2IE            4
#define             INT1IP            6
#define             INT2IP            7
/*____________________________________________________________________________*/

#define      PIR1                        HWREG8(0xF9E)
#define             TMR1IF            0
#define             TMR2IF            1
#define             CCP1IF            2
#define             SSPIF             3
#define             TXIF              4
#define             RCIF              5
#define             ADIF              6
#define             PSPIF             7
/*____________________________________________________________________________*/

#define      PIR2                        HWREG8(0xFA1)
#define             CCP2IF            0
#define             TMR3IF            1
#define             HLVDIF            2
#define             BCLIF             3
#define             EEIF              4
#define             C2IF              5
#define             C1IF              6
#define             OSCFIF            7
/*____________________________________________________________________________*/

#define      PIE1                        HWREG8(0xF9D)
#define             TMR1IE            0
#define             TMR2IE            1
#define             CCP1IE            2
#define             SSPIE             3
#define             TXIE              4
#define             RCIE              5
#define             ADIE              6
#define             PSPIE             7
/*____________________________________________________________________________*/

#define      PIE2                        HWREG8(0xFA0)
#define             CCP2IE            0
#define             TMR3IE            1
#define             HLVDIE            2
#define             BCLIE             3
#define             EEIE              4
#define             C2IE              5
#define             C1IE              6
#define             OSCFIE            7
/*____________________________________________________________________________*/

#define      IPR1                        HWREG8(0xF9F)
#define             TMR1IP            0
#define             TMR2IP            1
#define             CCP1IP            2
#define             SSPIP             3
#define             TXIP              4
#define             RCIP              5
#define             ADIP              6
#define             PSPIP             7
/*____________________________________________________________________________*/

#define      IPR2                        HWREG8(0xFA2)
#define             CCP2IP            0
#define             TMR3IP            1
#define             HLVDIP            2
#define             BCLIP             3
#define             EEIP              4
#define             C2IP              5
#define             C1IP              6
#define             OSCFIP            7
/*____________________________________________________________________________*/

#define      RCON                        HWREG8(0xFD0)
#define             BOR               0
#define             POR               1
#define             PD                2
#define             TO                3
#define             RI                4
#define             SBOREN            6
#define             IPEN              7
#define     PORTB                        HWREG8(0xF81)
#define             RB4              4
#define             RB5              5
#define             RB6              6
#define             RB7              7
/*____________________________________________________________________________*/
/*                         Section : Macro Functions                          */
/*____________________________________________________________________________*/

#if    (INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE)
/*                  at the case of active the priority levels                 */
#define   INTERRUPT_PRORITY_LEVELS_ENABLE()            (SET_BIT(RCON,IPEN))
#define   INTERRUPT_PRORITY_LEVELS_DISABLE()           (CLEAR_BIT(RCON,IPEN))
#define   GLOBAL_INTERRUPT_HIGH_PRORITY_ENABLE()       (SET_BIT(INTCON,GIEH))
#define   GLOBAL_INTERRUPT_HIGH_PRORITY_DISABLE()      (CLEAR_BIT(INTCON,GIEH))
#define   GLOBAL_INTERRUPT_LOW_PRORITY_ENABLE()        (SET_BIT(INTCON,GIEL))
#define   GLOBAL_INTERRUPT_LOW_PRORITY_DISABLE()       (CLEAR_BIT(INTCON,GIEL))

#else
/*                  at the case of deactivate the priority levels             */
#define   PERIPHERAL_INTERRUPT_ENABLE()                (SET_BIT(INTCON,PEIE))
#define   PERIPHERAL_INTERRUPT_DISABLE()               (CLEAR_BIT(INTCON,PEIE))
#define   GLOBAL_INTERRUPT_ENABLE()                    (SET_BIT(INTCON,GIE))
#define   GLOBAL_INTERRUPT_DISABLE()                   (CLEAR_BIT(INTCON,GIE))

#endif
/*____________________________________________________________________________*/
/*                         Section : Data Types Declarations                  */
/*____________________________________________________________________________*/
typedef enum 
{
    INTERRUPT_LOW_PRIORITY = 0,
    INTERRUPT_HIGH_PRIORITY
}INTERRUPT_PRIORITY;
#endif	/* MCAL_INTERRUPT_CONFIG_H */

