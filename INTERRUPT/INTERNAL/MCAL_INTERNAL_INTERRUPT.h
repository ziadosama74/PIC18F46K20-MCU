/* 
 * File:   MCAL_INTERNAL_INTERRUPT.h
 * Author: ziad osama
 *
 * Created on October 18, 2024, 9:41 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/*____________________________________________________________________________*/
/*                         Section : Includes                                 */
/*____________________________________________________________________________*/
#include "MCAL_INTERRUPT_Config.h"
#define   PERIPHERAL_INTERRUPT_ENABLE()                (SET_BIT(INTCON,PEIE))
#define   PERIPHERAL_INTERRUPT_DISABLE()               (CLEAR_BIT(INTCON,PEIE))
#define   GLOBAL_INTERRUPT_ENABLE()                    (SET_BIT(INTCON,GIE))
#define   GLOBAL_INTERRUPT_DISABLE()                   (CLEAR_BIT(INTCON,GIE))
/*____________________________________________________________________________*/
/*________________________ADC_INTERRUPT_FEATURE_______________________________*/
/*____________________________________________________________________________*/
#if  ADC_INTERRUPT_FEATURE == INTERRUPT_ENABLE
/* Function Like Macro To Enable ADC Module Interrupt */
#define   ADC_MODULE_INTERRUPT_ENABLE()                (SET_BIT(PIE1,ADIE))
/* Function Like Macro To Disable ADC Module Interrupt  */
#define   ADC_MODULE_INTERRUPT_DISABLE()               (CLEAR_BIT(PIE1,ADIE))
/* Function Like Macro To Clear The Interrupt Flag of ADC Module*/
#define   ADC_MODULE_CLEAR_FLAG()                      (CLEAR_BIT(PIR1,ADIF))
/*____________________________PRORITY_LEVELS__________________________________*/

#if INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE
 
/* Function Like Macro To Set ADC Module Interrupt Low Priority */
#define   ADC_MODULE_INTERRUPT_SET_LOW_PRIORITY()      (CLEAR_BIT(IPR1,ADIP))
/* Function Like Macro To Set ADC Module Interrupt High Priority */
#define   ADC_MODULE_INTERRUPT_SET_HIGH_PRIORITY()     (SET_BIT(IPR1,ADIP))

#endif
#endif
/*_____________________________________________________________________________*/

/*____________________________________________________________________________*/
/*______________________TIMER0_INTERRUPT_FEATURE______________________________*/
/*____________________________________________________________________________*/
#if  TIMER0_INTERRUPT_FEATURE == INTERRUPT_ENABLE

/* Function Like Macro To Enable TIMER0 Module Interrupt */
#define    TIMER0_INTERRUPT_ENABLE()                   (SET_BIT(INTCON,TMR0IE))
/* Function Like Macro To Disable TIMER0 Module Interrupt  */
#define    TIMER0_INTERRUPT_DISABLE()                   (CLEAR_BIT(INTCON,TMR0IE))
/* Function Like Macro To Clear The Interrupt Flag of TIMER0 Module*/
#define    TIMER0_CLEAR_INTERRUPT_FLAG()               (CLEAR_BIT(INTCON,TMR0IF))
/*____________________________PRORITY_LEVELS__________________________________*/
#if INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE
/* Function Like Macro To Set TIMER0 Module Interrupt Low Priority */
#define    TIMER0_SET_INTERRUPT_LOW_PRIORITY()         (CLEAR_BIT(INTCON2,TMR0IP))
/* Function Like Macro To Set TIMER0 Module Interrupt High Priority */
#define    TIMER0_SET_INTERRUPT_HIGH_PRIORITY()        (SET_BIT(INTCON2,TMR0IP))
#endif
#endif
/*_____________________________________________________________________________*/

/*____________________________________________________________________________*/
/*______________________TIMER1_INTERRUPT_FEATURE______________________________*/
/*____________________________________________________________________________*/
#if  TIMER1_INTERRUPT_FEATURE == INTERRUPT_ENABLE

/* Function Like Macro To Enable TIMER1 Module Interrupt */
#define    TIMER1_INTERRUPT_ENABLE()                   (SET_BIT(PIE1,TMR1IE))
/* Function Like Macro To Disable TIMER1 Module Interrupt  */
#define    TIMER1_INTERRUPT_DISABLE()                   (CLEAR_BIT(PIE1,TMR1IE))
/* Function Like Macro To Clear The Interrupt Flag of TIMER1 Module*/
#define    TIMER1_CLEAR_INTERRUPT_FLAG()               (CLEAR_BIT(PIR1,TMR1IF))
/*____________________________PRORITY_LEVELS__________________________________*/
#if INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE
/* Function Like Macro To Set TIMER1 Module Interrupt Low Priority */
#define    TIMER1_SET_INTERRUPT_LOW_PRIORITY()         (CLEAR_BIT(IPR1,TMR1IP))
/* Function Like Macro To Set TIMER1 Module Interrupt High Priority */
#define    TIMER1_SET_INTERRUPT_HIGH_PRIORITY()        (SET_BIT(IPR1,TMR1IP))
#endif
#endif
/*_____________________________________________________________________________*/

/*____________________________________________________________________________*/
/*______________________TIMER2_INTERRUPT_FEATURE______________________________*/
/*____________________________________________________________________________*/
#if  TIMER2_INTERRUPT_FEATURE == INTERRUPT_ENABLE

/* Function Like Macro To Enable TIMER2 Module Interrupt */
#define    TIMER2_INTERRUPT_ENABLE()                   (SET_BIT(PIE1,TMR2IE))
/* Function Like Macro To Disable TIMER2 Module Interrupt  */
#define    TIMER2_INTERRUPT_DISABLE()                   (CLEAR_BIT(PIE1,TMR2IE))
/* Function Like Macro To Clear The Interrupt Flag of TIMER2 Module*/
#define    TIMER2_CLEAR_INTERRUPT_FLAG()               (CLEAR_BIT(PIR1,TMR2IF))
/*____________________________PRORITY_LEVELS__________________________________*/
#if INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE
/* Function Like Macro To Set TIMER2 Module Interrupt Low Priority */
#define    TIMER2_SET_INTERRUPT_LOW_PRIORITY()         (CLEAR_BIT(IPR1,TMR2IP))
/* Function Like Macro To Set TIMER2 Module Interrupt High Priority */
#define    TIMER2_SET_INTERRUPT_HIGH_PRIORITY()        (SET_BIT(IPR1,TMR2IP))
#endif
#endif
/*____________________________________________________________________________*/
/*______________________TIMER3_INTERRUPT_FEATURE______________________________*/
/*____________________________________________________________________________*/
#if  TIMER3_INTERRUPT_FEATURE == INTERRUPT_ENABLE

/* Function Like Macro To Enable TIMER3 Module Interrupt */
#define    TIMER3_INTERRUPT_ENABLE()                    (SET_BIT(PIE2,TMR3IE))
/* Function Like Macro To Disable TIMER3 Module Interrupt  */
#define    TIMER3_INTERRUPT_DISABLE()                   (CLEAR_BIT(PIE2,TMR3IE))
/* Function Like Macro To Clear The Interrupt Flag of TIMER3 Module*/
#define    TIMER3_CLEAR_INTERRUPT_FLAG()                (CLEAR_BIT(PIR2,TMR3IF))
/*____________________________PRORITY_LEVELS__________________________________*/
#if INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE
/* Function Like Macro To Set TIMER3 Module Interrupt Low Priority */
#define    TIMER3_SET_INTERRUPT_LOW_PRIORITY()          (CLEAR_BIT(IPR2,TMR3IP))
/* Function Like Macro To Set TIMER3 Module Interrupt High Priority */
#define    TIMER3_SET_INTERRUPT_HIGH_PRIORITY()         (SET_BIT(IPR2,TMR3IP))
#endif
#endif
/*____________________________________________________________________________*/
/*______________________CCP1_INTERRUPT_FEATURE________________________________*/
/*____________________________________________________________________________*/
#if  CCP1_INTERRUPT_FEATURE == INTERRUPT_ENABLE

/* Function Like Macro To Enable CCP1 Module Interrupt */
#define    CCP1_INTERRUPT_ENABLE()                    (SET_BIT(PIE1,CCP1IE))
/* Function Like Macro To Disable CCP1 Module Interrupt  */
#define    CCP1_INTERRUPT_DISABLE()                   (CLEAR_BIT(PIE1,CCP1IE))
/* Function Like Macro To Clear The Interrupt Flag of CCP1 Module*/
#define    CCP1_CLEAR_INTERRUPT_FLAG()                (CLEAR_BIT(PIR1,CCP1IF))
/*____________________________PRORITY_LEVELS__________________________________*/
#if INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE
/* Function Like Macro To Set CCP1 Module Interrupt Low Priority */
#define    CCP1_SET_INTERRUPT_LOW_PRIORITY()          (CLEAR_BIT(IPR1,CCP1IP))
/* Function Like Macro To Set CCP1 Module Interrupt High Priority */
#define    CCP1_SET_INTERRUPT_HIGH_PRIORITY()         (SET_BIT(IPR1,CCP1IP))
#endif
#endif
/*____________________________________________________________________________*/
/*____________________________________________________________________________*/
/*______________________CCP2_INTERRUPT_FEATURE________________________________*/
/*____________________________________________________________________________*/
#if  CCP2_INTERRUPT_FEATURE == INTERRUPT_ENABLE

/* Function Like Macro To Enable CCP2 Module Interrupt */
#define    CCP2_INTERRUPT_ENABLE()                    (SET_BIT(PIE2,CCP2IE))
/* Function Like Macro To Disable CCP2 Module Interrupt  */
#define    CCP2_INTERRUPT_DISABLE()                   (CLEAR_BIT(PIE2,CCP2IE))
/* Function Like Macro To Clear The Interrupt Flag of CCP2 Module*/
#define    CCP2_CLEAR_INTERRUPT_FLAG()                (CLEAR_BIT(PIR2,CCP2IF))
/*____________________________PRORITY_LEVELS__________________________________*/
#if INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE
/* Function Like Macro To Set CCP2 Module Interrupt Low Priority */
#define    CCP2_SET_INTERRUPT_LOW_PRIORITY()          (CLEAR_BIT(IPR2,CCP2IP))
/* Function Like Macro To Set CCP2 Module Interrupt High Priority */
#define    CCP2_SET_INTERRUPT_HIGH_PRIORITY()         (SET_BIT(IPR2,CCP2IP))
#endif
#endif
/*____________________________________________________________________________*/
/*____________________________________________________________________________*/
/*______________________USART_TX_INTERRUPT_FEATURE____________________________*/
/*____________________________________________________________________________*/
#if  USART_TX_INTERRUPT_FEATURE == INTERRUPT_ENABLE

/* Function Like Macro To Enable USART TX Module Interrupt */
#define    USART_TX_INTERRUPT_ENABLE()                    (SET_BIT(PIE1,TXIE))
/* Function Like Macro To Disable USART TX Module Interrupt  */
#define    USART_TX_INTERRUPT_DISABLE()                   (CLEAR_BIT(PIE1,TXIE))
/* Function Like Macro To Get The Interrupt Flag Status of USART TX Module*/
#define    USART_TX_GET_INTERRUPT_FLAG_STATUS()           (READ_BIT(PIR1,TXIF))
/*____________________________PRORITY_LEVELS__________________________________*/
#if INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE
/* Function Like Macro To Set USART TX Module Interrupt Low Priority */
#define    USART_TX_SET_INTERRUPT_LOW_PRIORITY()          (CLEAR_BIT(IPR1,TXIP))
/* Function Like Macro To Set USART TX Module Interrupt High Priority */
#define    USART_TX_SET_INTERRUPT_HIGH_PRIORITY()         (SET_BIT(IPR1,TXIP))
#endif
#endif
/*____________________________________________________________________________*/
/*____________________________________________________________________________*/
/*______________________USART_RX_INTERRUPT_FEATURE____________________________*/
/*____________________________________________________________________________*/
#if  USART_RX_INTERRUPT_FEATURE == INTERRUPT_ENABLE

/* Function Like Macro To Enable USART RX Module Interrupt */
#define    USART_RX_INTERRUPT_ENABLE()                    (SET_BIT(PIE1,RCIE))
/* Function Like Macro To Disable USART RX Module Interrupt  */
#define    USART_RX_INTERRUPT_DISABLE()                   (CLEAR_BIT(PIE1,RCIE))
/* Function Like Macro To Get The Interrupt Flag Status of USART RX Module*/
#define    USART_RX_GET_INTERRUPT_FLAG_STATUS()           (READ_BIT(PIR1,RCIF))
/*____________________________PRORITY_LEVELS__________________________________*/
#if INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE
/* Function Like Macro To Set USART RX Module Interrupt Low Priority */
#define    USART_RX_SET_INTERRUPT_LOW_PRIORITY()          (CLEAR_BIT(IPR1,RCIP))
/* Function Like Macro To Set USART RX Module Interrupt High Priority */
#define    USART_RX_SET_INTERRUPT_HIGH_PRIORITY()         (SET_BIT(IPR1,RCIP))
#endif
#endif
/*____________________________________________________________________________*/
/*____________________________________________________________________________*/
/*__________________________SPI_INTERRUPT_FEATURE_____________________________*/
/*____________________________________________________________________________*/
#if  SPI_INTERRUPT_FEATURE == INTERRUPT_ENABLE
/* Function Like Macro To Enable SPI Module Interrupt */
#define    SPI_INTERRUPT_ENABLE()                    (SET_BIT(PIE1,SSPIE))
/* Function Like Macro To Disable SPI Module Interrupt  */
#define    SPI_INTERRUPT_DISABLE()                   (CLEAR_BIT(PIE1,SSPIE))
/* Function Like Macro To Clear The Interrupt Flag Status of SPI Module*/
#define    SPI_CLEAR_INTERRUPT_FLAG()                (CLEAR_BIT(PIR1,SSPIF))
/*____________________________PRORITY_LEVELS__________________________________*/
#if INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE
/* Function Like Macro To Set SPI Module Interrupt Low Priority */
#define    SPI_SET_INTERRUPT_LOW_PRIORITY()          (CLEAR_BIT(IPR1,SSPIP))
/* Function Like Macro To Set SPI Module Interrupt High Priority */
#define    SPI_SET_INTERRUPT_HIGH_PRIORITY()         (SET_BIT(IPR1,SSPIP))
#endif
#endif
/*____________________________________________________________________________*/
/*____________________________________________________________________________*/
/*__________________________I2C_INTERRUPT_FEATURE_____________________________*/
/*____________________________________________________________________________*/
#if  I2C_INTERRUPT_FEATURE == INTERRUPT_ENABLE
/* Function Like Macro To Enable I2C Module Interrupt */
#define    I2C_INTERRUPT_ENABLE()                     (SET_BIT(PIE1,SSPIE))
/* Function Like Macro To Disable I2C Module Interrupt  */
#define    I2C_INTERRUPT_DISABLE()                    (CLEAR_BIT(PIE1,SSPIE))
/* Function Like Macro To Clear The Interrupt Flag Status of I2C Module*/
#define    I2C_CLEAR_INTERRUPT_FLAG()                 (CLEAR_BIT(PIR1,SSPIF))
/*____________________________________________________________________________*/
/*                     I2C_INTERRUPT_DATA_COLLISION                           */
/*____________________________________________________________________________*/
#define    I2C_INTERRUPT_DATA_COLLISION_ENABLE()      (SET_BIT(PIE2,BCLIE))
#define    I2C_INTERRUPT_DATA_COLLISION_DISABLE()     (CLEAR_BIT(PIE2,BCLIE))
#define    I2C_DTAT_COLLISION_CLEAR_INTERRUPT_FLAG()  (CLEAR_BIT(PIR2,BCLIF))
/*____________________________PRORITY_LEVELS__________________________________*/
#if INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE
/* Function Like Macro To Set I2C Module Interrupt Low Priority */
#define    I2C_SET_INTERRUPT_LOW_PRIORITY()           (CLEAR_BIT(IPR1,SSPIP))
/* Function Like Macro To Set I2C Module Interrupt High Priority */
#define    I2C_SET_INTERRUPT_HIGH_PRIORITY()          (SET_BIT(IPR1,SSPIP))
/*____________________________________________________________________________*/
/*                     I2C_INTERRUPT_DATA_COLLISION                           */
/*____________________________________________________________________________*/
#define   I2C_SET_DATA_COLLISION_INTERRUPT_LOW_PRIORITY()  (CLEAR_BIT(IPR2,BCLIP))
#define   I2C_SET_DATA_COLLISION_INTERRUPT_HIGH_PRIORITY() (SET_BIT(IPR2,BCLIP))
#endif
#endif
/*____________________________________________________________________________*/
#endif	/* MCAL_INTERNAL_INTERRUPT_H */

