/* 
 * File:   INTERRUPT_GENERATE _CONFIGURATION.h
 * Author: ziad osama
 *
 * Created on October 19, 2024, 1:55 AM
 */

#ifndef INTERRUPT_GENERATE__CONFIGURATION_H
#define	INTERRUPT_GENERATE__CONFIGURATION_H
/*____________________________________________________________________________*/
/*                         Section : Includes                                 */
/*____________________________________________________________________________*/
#include "pic18f4620.h"
#include "../MCAL_STD_TYPES.h"
#include "../../MCAL_Layer/GPIO/GPIO_Interface.h"
/*____________________________________________________________________________*/
/*                         Section : Macro Declarations                       */
/*____________________________________________________________________________*/
#define INTERRUPT_ENABLE                    1
#define INTERRUPT_DISABLE                   0
#define INTERRUPT_OCCURED                   1
#define INTERRUPT_NOT_OCCURED               0
#define INTERRUPT_PRIORTY_ENABLE            1
#define INTERRUPT_PRIORTY_DISABLE           0
#define MAX_INTx_SOURCES                    3
/*____________________________________________________________________________*/
/*________________________INTERRUPT_PRORITY_LEVELS____________________________*/
/*____________________________________________________________________________*/
#define      INTERRUPT_PRORITY_LEVELS_STATUS               INTERRUPT_PRIORTY_DISABLE
/*____________________________________________________________________________*/
/*_____________________EXTERNAL_INTERRUPT_FEATURE_INTx________________________*/
/*____________________________________________________________________________*/
#define      EXTERNAL_INTERRUPT_FEATURE_INTx               INTERRUPT_DISABLE 
/*____________________________________________________________________________*/
/*________________EXTERNAL_INTERRUPT_FEATURE_ON_CHANGE_KBIx___________________*/
/*____________________________________________________________________________*/
#define      EXTERNAL_INTERRUPT_FEATURE_ON_CHANGE_KBIx     INTERRUPT_DISABLE 
/*____________________________________________________________________________*/
/*__________________________INTERNAL_INTERRUPT________________________________*/
/*____________________________________________________________________________*/
#define      INTERNAL_INTERRUPT_FEATURE                    INTERRUPT_DISABLE 
/*____________________________________________________________________________*/
/*________________________ADC_INTERRUPT_FEATURE_______________________________*/
/*____________________________________________________________________________*/
#define      ADC_INTERRUPT_FEATURE                         INTERRUPT_DISABLE 
/*____________________________________________________________________________*/
/*______________________TIMER0_INTERRUPT_FEATURE______________________________*/
/*____________________________________________________________________________*/
#define      TIMER0_INTERRUPT_FEATURE                      INTERRUPT_DISABLE
/*____________________________________________________________________________*/
/*______________________TIMER1_INTERRUPT_FEATURE______________________________*/
/*____________________________________________________________________________*/
#define      TIMER1_INTERRUPT_FEATURE                      INTERRUPT_DISABLE
/*____________________________________________________________________________*/
/*______________________TIMER2_INTERRUPT_FEATURE______________________________*/
/*____________________________________________________________________________*/
#define      TIMER2_INTERRUPT_FEATURE                      INTERRUPT_DISABLE
/*____________________________________________________________________________*/
/*______________________TIMER3_INTERRUPT_FEATURE______________________________*/
/*____________________________________________________________________________*/
#define      TIMER3_INTERRUPT_FEATURE                      INTERRUPT_DISABLE
/*____________________________________________________________________________*/
/*______________________CCP1_INTERRUPT_FEATURE________________________________*/
/*____________________________________________________________________________*/
#define      CCP1_INTERRUPT_FEATURE                        INTERRUPT_DISABLE
/*____________________________________________________________________________*/
/*______________________CCP2_INTERRUPT_FEATURE________________________________*/
/*____________________________________________________________________________*/
#define      CCP2_INTERRUPT_FEATURE                        INTERRUPT_DISABLE
/*____________________________________________________________________________*/
/*______________________USART_TX_INTERRUPT_FEATURE____________________________*/
/*____________________________________________________________________________*/
#define      USART_TX_INTERRUPT_FEATURE                    INTERRUPT_DISABLE
/*____________________________________________________________________________*/
/*______________________USART_RX_INTERRUPT_FEATURE____________________________*/
/*____________________________________________________________________________*/
#define     USART_RX_INTERRUPT_FEATURE                     INTERRUPT_DISABLE
/*____________________________________________________________________________*/
/*____________________________________________________________________________*/
/*______________________SPI_INTERRUPT_FEATURE_________________________________*/
#define    SPI_INTERRUPT_FEATURE                           INTERRUPT_DISABLE
/*____________________________________________________________________________*/
/*____________________________________________________________________________*/
/*______________________I2C_INTERRUPT_FEATURE_________________________________*/
#define    I2C_INTERRUPT_FEATURE                           INTERRUPT_ENABLE
/*____________________________________________________________________________*/
#endif	/* INTERRUPT_GENERATE__CONFIGURATION_H */

