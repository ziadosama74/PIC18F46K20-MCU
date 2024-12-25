/* 
 * File:   MCAL_INTERRUPT_MANAGER.C
 * Author: ziad osama
 *
 * Created on October 18, 2024, 9:42 PM
 */
/*____________________________________________________________________________*/
/*                         Section : Includes                                 */
/*____________________________________________________________________________*/

#include "MCAL_INTERRUPT_MANAGER.h"
#if EXTERNAL_INTERRUPT_FEATURE_ON_CHANGE_KBIx ==  INTERRUPT_ENABLE
volatile uint8 k4 = 0 ;
volatile uint8 k5 = 0 ;
volatile uint8 k6 = 0 ;
volatile uint8 k7 = 0 ;
#endif
/*____________________________________________________________________________*/
#if   (INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE)
/*______________________________________________________________________________*/
/*==============================================================================*/
/*==============================================================================*/
/*==================           InterruptManagerHigh           ==================*/
/*==============================================================================*/
/*==============================================================================*/

void __interrupt() InterruptManagerHigh(void)
{
    /*____________________________________________________________________________*/
   #if EXTERNAL_INTERRUPT_FEATURE_INTx == INTERRUPT_ENABLE
    /*____________________________________________________________________________*/
    /*_____________________EXTERNAL_INTERRUPT_FEATURE_INTx________________________*/
    /*____________________________________________________________________________*/
    if( ( (READ_BIT(INTCON,INT0IE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON,INT0IF)) == INTERRUPT_OCCURED) )
    {
        INT0_ISR();
    }
    else{/*NOTHING*/}
    if( ( (READ_BIT(INTCON3,INT1IE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON3,INT1IF)) == INTERRUPT_OCCURED) )
    {
        INT1_ISR();
    }
    else{/*NOTHING*/}
    if( ( (READ_BIT(INTCON3,INT2IE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON3,INT2IF)) == INTERRUPT_OCCURED) )
    {
        INT2_ISR();
    }
    else{/*NOTHING*/} 
    #endif
    /*____________________________________________________________________________*/
    #if EXTERNAL_INTERRUPT_FEATURE_ON_CHANGE_KBIx ==  INTERRUPT_ENABLE
    /*____________________________________________________________________________*/
    /*________________EXTERNAL_INTERRUPT_FEATURE_ON_CHANGE_KBIx___________________*/
    /*____________________________________________________________________________*/
    if( ( (READ_BIT(INTCON,RBIE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON,RBIF)) == INTERRUPT_OCCURED) && ((READ_BIT(PORTB,RB4)) == HIGH) && (k4 == 0))
    {
        k4 = 1 ;
        KBI_4_ISR(HIGH);
    }
    else{/*NOTHING*/}
    if( ( (READ_BIT(INTCON,RBIE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON,RBIF)) == INTERRUPT_OCCURED) && ((READ_BIT(PORTB,RB4)) == LOW ) && (k4 == 1))
    {
        k4 = 0 ;
        KBI_4_ISR(LOW);
    }
    else{/*NOTHING*/}
    /**==========================================================================================================*/
    if( ( (READ_BIT(INTCON,RBIE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON,RBIF)) == INTERRUPT_OCCURED) && ((READ_BIT(PORTB,RB5)) == HIGH) && (k5 == 0) )
    {
          k5 = 1 ;
        KBI_5_ISR(HIGH);
    }
    else{/*NOTHING*/}
    if( ( (READ_BIT(INTCON,RBIE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON,RBIF)) == INTERRUPT_OCCURED) && ((READ_BIT(PORTB,RB5)) == LOW ) && (k5 == 1) )
    {
        k5 = 0 ;
        KBI_5_ISR(LOW);
    }
    else{/*NOTHING*/}
    /**==========================================================================================================*/
    if( ( (READ_BIT(INTCON,RBIE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON,RBIF)) == INTERRUPT_OCCURED) && ((READ_BIT(PORTB,RB6)) == HIGH) && (k6 == 0) )
    {
        k6 = 1 ;
        KBI_6_ISR(HIGH);
    }
    else{/*NOTHING*/}
    if( ( (READ_BIT(INTCON,RBIE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON,RBIF)) == INTERRUPT_OCCURED) && ((READ_BIT(PORTB,RB6)) == LOW ) && (k6 == 1) )
    {
          k6 = 0 ;
        KBI_6_ISR(LOW);
    }
    else{/*NOTHING*/}
    /**==========================================================================================================*/
    if( ( (READ_BIT(INTCON,RBIE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON,RBIF)) == INTERRUPT_OCCURED) && ((READ_BIT(PORTB,RB7)) == HIGH) && (k7 == 0) )
    {
        k7 = 1 ;
        KBI_7_ISR(HIGH);
    }
    else{/*NOTHING*/}
    if( ( (READ_BIT(INTCON,RBIE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON,RBIF)) == INTERRUPT_OCCURED) && ((READ_BIT(PORTB,RB7)) == LOW ) && (k7 == 1) )
    {
        k7 = 0 ;
        KBI_7_ISR(LOW);
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*________________________ADC_INTERRUPT_FEATURE_______________________________*/
    /*____________________________________________________________________________*/
    #if  ADC_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    /*____________________________________________________________________________*/
    if(((READ_BIT(PIE1,ADIE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR1,ADIF)) == INTERRUPT_OCCURED))
    {
        ADC_ISR();
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*______________________TIMER0_INTERRUPT_FEATURE______________________________*/
    /*____________________________________________________________________________*/
    #if  TIMER0_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    if( ((READ_BIT(INTCON,TMR0IE)) == INTERRUPT_ENABLE) && ((READ_BIT(INTCON,TMR0IF)) == INTERRUPT_OCCURED) )
    {
        TIMER0_ISR();
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*______________________TIMER1_INTERRUPT_FEATURE______________________________*/
    /*____________________________________________________________________________*/
    #if  TIMER1_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    if( ((READ_BIT(PIE1,TMR1IE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR1,TMR1IF)) == INTERRUPT_OCCURED) )
    {
        TIMER1_ISR();
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*______________________TIMER2_INTERRUPT_FEATURE______________________________*/
    /*____________________________________________________________________________*/
    #if  TIMER2_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    if( ((READ_BIT(PIE1,TMR2IE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR1,TMR2IF)) == INTERRUPT_OCCURED) )
    {
        TIMER2_ISR();
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*______________________TIMER3_INTERRUPT_FEATURE______________________________*/
    /*____________________________________________________________________________*/
    #if  TIMER3_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    if( ((READ_BIT(PIE2,TMR3IE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR2,TMR3IF)) == INTERRUPT_OCCURED) )
    {
        TIMER3_ISR();
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*______________________CCP1_INTERRUPT_FEATURE________________________________*/
    /*____________________________________________________________________________*/
    #if  CCP1_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    if( ((READ_BIT(PIE1,CCP1IE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR1,CCP1IF)) == INTERRUPT_OCCURED) )
    {
        CCP1_ISR();
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*______________________CCP2_INTERRUPT_FEATURE________________________________*/
    /*____________________________________________________________________________*/
    #if  CCP2_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    if( ((READ_BIT(PIE2,CCP2IE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR2,CCP2IF)) == INTERRUPT_OCCURED) )
    {
        CCP2_ISR();
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*______________________USART_TX_INTERRUPT_FEATURE____________________________*/
    /*____________________________________________________________________________*/
    #if  USART_TX_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    if( ((READ_BIT(PIE1,TXIE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR1,TXIF)) == INTERRUPT_OCCURED) )
    {
        USART_TX_ISR();
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*______________________USART_RX_INTERRUPT_FEATURE____________________________*/
    /*____________________________________________________________________________*/
    #if  USART_RX_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    if( ((READ_BIT(PIE1,RCIE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR1,RCIF)) == INTERRUPT_OCCURED) )
    {
        USART_RX_ISR();
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*____________________________________________________________________________*/
    /*__________________________SPI_INTERRUPT_FEATURE_____________________________*/
    /*____________________________________________________________________________*/
    #if  SPI_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    if( ((READ_BIT(PIE1,SSPIE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR1,SSPIF)) == INTERRUPT_OCCURED) )
    {
        SPI_ISR();
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*____________________________________________________________________________*/
    /*__________________________I2C_INTERRUPT_FEATURE_____________________________*/
    /*____________________________________________________________________________*/
    #if  I2C_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    if( ((READ_BIT(PIE1,SSPIE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR1,SSPIF)) == INTERRUPT_OCCURED) )
    {
        I2C_ISR();
    }
    else{/*NOTHING*/}
    if( ((READ_BIT(PIE2,BCLIE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR2,BCLIF)) == INTERRUPT_OCCURED) )
    {
        I2C_DATA_COLLISION_ISR();
    }
    else{/*NOTHING*/}
    #endif
}

/*==============================================================================*/
/*==============================================================================*/
/*==================           InterruptManagerLow            ==================*/
/*==============================================================================*/
/*==============================================================================*/

void __interrupt(low_priority) InterruptManagerLow(void)
{
    /*____________________________________________________________________________*/
   #if EXTERNAL_INTERRUPT_FEATURE_INTx == INTERRUPT_ENABLE
    /*____________________________________________________________________________*/
    /*_____________________EXTERNAL_INTERRUPT_FEATURE_INTx________________________*/
    /*____________________________________________________________________________*/
    if( ( (READ_BIT(INTCON,INT0IE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON,INT0IF)) == INTERRUPT_OCCURED) )
    {
        INT0_ISR();
    }
    else{/*NOTHING*/}
    if( ( (READ_BIT(INTCON3,INT1IE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON3,INT1IF)) == INTERRUPT_OCCURED) )
    {
        INT1_ISR();
    }
    else{/*NOTHING*/}
    if( ( (READ_BIT(INTCON3,INT2IE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON3,INT2IF)) == INTERRUPT_OCCURED) )
    {
        INT2_ISR();
    }
    else{/*NOTHING*/} 
    #endif
    /*____________________________________________________________________________*/
    #if EXTERNAL_INTERRUPT_FEATURE_ON_CHANGE_KBIx ==  INTERRUPT_ENABLE
    /*____________________________________________________________________________*/
    /*________________EXTERNAL_INTERRUPT_FEATURE_ON_CHANGE_KBIx___________________*/
    /*____________________________________________________________________________*/
    if( ( (READ_BIT(INTCON,RBIE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON,RBIF)) == INTERRUPT_OCCURED) && ((READ_BIT(PORTB,RB4)) == HIGH) && (k4 == 0))
    {
        k4 = 1 ;
        KBI_4_ISR(HIGH);
    }
    else{/*NOTHING*/}
    if( ( (READ_BIT(INTCON,RBIE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON,RBIF)) == INTERRUPT_OCCURED) && ((READ_BIT(PORTB,RB4)) == LOW ) && (k4 == 1))
    {
        k4 = 0 ;
        KBI_4_ISR(LOW);
    }
    else{/*NOTHING*/}
    /**==========================================================================================================*/
    if( ( (READ_BIT(INTCON,RBIE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON,RBIF)) == INTERRUPT_OCCURED) && ((READ_BIT(PORTB,RB5)) == HIGH) && (k5 == 0) )
    {
          k5 = 1 ;
        KBI_5_ISR(HIGH);
    }
    else{/*NOTHING*/}
    if( ( (READ_BIT(INTCON,RBIE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON,RBIF)) == INTERRUPT_OCCURED) && ((READ_BIT(PORTB,RB5)) == LOW ) && (k5 == 1) )
    {
        k5 = 0 ;
        KBI_5_ISR(LOW);
    }
    else{/*NOTHING*/}
    /**==========================================================================================================*/
    if( ( (READ_BIT(INTCON,RBIE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON,RBIF)) == INTERRUPT_OCCURED) && ((READ_BIT(PORTB,RB6)) == HIGH) && (k6 == 0) )
    {
        k6 = 1 ;
        KBI_6_ISR(HIGH);
    }
    else{/*NOTHING*/}
    if( ( (READ_BIT(INTCON,RBIE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON,RBIF)) == INTERRUPT_OCCURED) && ((READ_BIT(PORTB,RB6)) == LOW ) && (k6 == 1) )
    {
          k6 = 0 ;
        KBI_6_ISR(LOW);
    }
    else{/*NOTHING*/}
    /**==========================================================================================================*/
    if( ( (READ_BIT(INTCON,RBIE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON,RBIF)) == INTERRUPT_OCCURED) && ((READ_BIT(PORTB,RB7)) == HIGH) && (k7 == 0) )
    {
        k7 = 1 ;
        KBI_7_ISR(HIGH);
    }
    else{/*NOTHING*/}
    if( ( (READ_BIT(INTCON,RBIE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON,RBIF)) == INTERRUPT_OCCURED) && ((READ_BIT(PORTB,RB7)) == LOW ) && (k7 == 1) )
    {
        k7 = 0 ;
        KBI_7_ISR(LOW);
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*________________________ADC_INTERRUPT_FEATURE_______________________________*/
    /*____________________________________________________________________________*/
    #if  ADC_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    /*____________________________________________________________________________*/
    if(((READ_BIT(PIE1,ADIE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR1,ADIF)) == INTERRUPT_OCCURED))
    {
        ADC_ISR();
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*______________________TIMER0_INTERRUPT_FEATURE______________________________*/
    /*____________________________________________________________________________*/
    #if  TIMER0_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    if( ((READ_BIT(INTCON,TMR0IE)) == INTERRUPT_ENABLE) && ((READ_BIT(INTCON,TMR0IF)) == INTERRUPT_OCCURED) )
    {
        TIMER0_ISR();
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*______________________TIMER1_INTERRUPT_FEATURE______________________________*/
    /*____________________________________________________________________________*/
    #if  TIMER1_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    if( ((READ_BIT(PIE1,TMR1IE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR1,TMR1IF)) == INTERRUPT_OCCURED) )
    {
        TIMER1_ISR();
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*______________________TIMER2_INTERRUPT_FEATURE______________________________*/
    /*____________________________________________________________________________*/
    #if  TIMER2_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    if( ((READ_BIT(PIE1,TMR2IE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR1,TMR2IF)) == INTERRUPT_OCCURED) )
    {
        TIMER2_ISR();
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*______________________TIMER3_INTERRUPT_FEATURE______________________________*/
    /*____________________________________________________________________________*/
    #if  TIMER3_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    if( ((READ_BIT(PIE2,TMR3IE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR2,TMR3IF)) == INTERRUPT_OCCURED) )
    {
        TIMER3_ISR();
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*______________________CCP1_INTERRUPT_FEATURE________________________________*/
    /*____________________________________________________________________________*/
    #if  CCP1_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    if( ((READ_BIT(PIE1,CCP1IE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR1,CCP1IF)) == INTERRUPT_OCCURED) )
    {
        CCP1_ISR();
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*______________________CCP2_INTERRUPT_FEATURE________________________________*/
    /*____________________________________________________________________________*/
    #if  CCP2_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    if( ((READ_BIT(PIE2,CCP2IE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR2,CCP2IF)) == INTERRUPT_OCCURED) )
    {
        CCP2_ISR();
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*______________________USART_TX_INTERRUPT_FEATURE____________________________*/
    /*____________________________________________________________________________*/
    #if  USART_TX_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    if( ((READ_BIT(PIE1,TXIE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR1,TXIF)) == INTERRUPT_OCCURED) )
    {
        USART_TX_ISR();
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*______________________USART_RX_INTERRUPT_FEATURE____________________________*/
    /*____________________________________________________________________________*/
    #if  USART_RX_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    if( ((READ_BIT(PIE1,RCIE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR1,RCIF)) == INTERRUPT_OCCURED) )
    {
        USART_RX_ISR();
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*____________________________________________________________________________*/
    /*__________________________SPI_INTERRUPT_FEATURE_____________________________*/
    /*____________________________________________________________________________*/
    #if  SPI_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    if( ((READ_BIT(PIE1,SSPIE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR1,SSPIF)) == INTERRUPT_OCCURED) )
    {
        SPI_ISR();
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*____________________________________________________________________________*/
    /*__________________________I2C_INTERRUPT_FEATURE_____________________________*/
    /*____________________________________________________________________________*/
    #if  I2C_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    if( ((READ_BIT(PIE1,SSPIE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR1,SSPIF)) == INTERRUPT_OCCURED) )
    {
        I2C_ISR();
    }
    else{/*NOTHING*/}
    if( ((READ_BIT(PIE2,BCLIE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR2,BCLIF)) == INTERRUPT_OCCURED) )
    {
        I2C_DATA_COLLISION_ISR();
    }
    else{/*NOTHING*/}
    #endif
}
#else

/*==============================================================================*/
/*==============================================================================*/
/*==================           InterruptManager               ==================*/
/*==============================================================================*/
/*==============================================================================*/

void __interrupt() InterruptManager(void)
{
    /*____________________________________________________________________________*/
   #if EXTERNAL_INTERRUPT_FEATURE_INTx == INTERRUPT_ENABLE
    /*____________________________________________________________________________*/
    /*_____________________EXTERNAL_INTERRUPT_FEATURE_INTx________________________*/
    /*____________________________________________________________________________*/
    if( ( (READ_BIT(INTCON,INT0IE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON,INT0IF)) == INTERRUPT_OCCURED) )
    {
        INT0_ISR();
    }
    else{/*NOTHING*/}
    if( ( (READ_BIT(INTCON3,INT1IE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON3,INT1IF)) == INTERRUPT_OCCURED) )
    {
        INT1_ISR();
    }
    else{/*NOTHING*/}
    if( ( (READ_BIT(INTCON3,INT2IE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON3,INT2IF)) == INTERRUPT_OCCURED) )
    {
        INT2_ISR();
    }
    else{/*NOTHING*/} 
    #endif
    /*____________________________________________________________________________*/
    #if EXTERNAL_INTERRUPT_FEATURE_ON_CHANGE_KBIx ==  INTERRUPT_ENABLE
    /*____________________________________________________________________________*/
    /*________________EXTERNAL_INTERRUPT_FEATURE_ON_CHANGE_KBIx___________________*/
    /*____________________________________________________________________________*/
    if( ( (READ_BIT(INTCON,RBIE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON,RBIF)) == INTERRUPT_OCCURED) && ((READ_BIT(PORTB,RB4)) == HIGH) && (k4 == 0))
    {
        k4 = 1 ;
        KBI_4_ISR(HIGH);
    }
    else{/*NOTHING*/}
    if( ( (READ_BIT(INTCON,RBIE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON,RBIF)) == INTERRUPT_OCCURED) && ((READ_BIT(PORTB,RB4)) == LOW ) && (k4 == 1))
    {
        k4 = 0 ;
        KBI_4_ISR(LOW);
    }
    else{/*NOTHING*/}
    /**==========================================================================================================*/
    if( ( (READ_BIT(INTCON,RBIE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON,RBIF)) == INTERRUPT_OCCURED) && ((READ_BIT(PORTB,RB5)) == HIGH) && (k5 == 0) )
    {
          k5 = 1 ;
        KBI_5_ISR(HIGH);
    }
    else{/*NOTHING*/}
    if( ( (READ_BIT(INTCON,RBIE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON,RBIF)) == INTERRUPT_OCCURED) && ((READ_BIT(PORTB,RB5)) == LOW ) && (k5 == 1) )
    {
        k5 = 0 ;
        KBI_5_ISR(LOW);
    }
    else{/*NOTHING*/}
    /**==========================================================================================================*/
    if( ( (READ_BIT(INTCON,RBIE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON,RBIF)) == INTERRUPT_OCCURED) && ((READ_BIT(PORTB,RB6)) == HIGH) && (k6 == 0) )
    {
        k6 = 1 ;
        KBI_6_ISR(HIGH);
    }
    else{/*NOTHING*/}
    if( ( (READ_BIT(INTCON,RBIE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON,RBIF)) == INTERRUPT_OCCURED) && ((READ_BIT(PORTB,RB6)) == LOW ) && (k6 == 1) )
    {
          k6 = 0 ;
        KBI_6_ISR(LOW);
    }
    else{/*NOTHING*/}
    /**==========================================================================================================*/
    if( ( (READ_BIT(INTCON,RBIE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON,RBIF)) == INTERRUPT_OCCURED) && ((READ_BIT(PORTB,RB7)) == HIGH) && (k7 == 0) )
    {
        k7 = 1 ;
        KBI_7_ISR(HIGH);
    }
    else{/*NOTHING*/}
    if( ( (READ_BIT(INTCON,RBIE)) == INTERRUPT_ENABLE )&& ( (READ_BIT(INTCON,RBIF)) == INTERRUPT_OCCURED) && ((READ_BIT(PORTB,RB7)) == LOW ) && (k7 == 1) )
    {
        k7 = 0 ;
        KBI_7_ISR(LOW);
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*________________________ADC_INTERRUPT_FEATURE_______________________________*/
    /*____________________________________________________________________________*/
    #if  ADC_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    /*____________________________________________________________________________*/
    if(((READ_BIT(PIE1,ADIE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR1,ADIF)) == INTERRUPT_OCCURED))
    {
        ADC_ISR();
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*______________________TIMER0_INTERRUPT_FEATURE______________________________*/
    /*____________________________________________________________________________*/
    #if  TIMER0_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    if( ((READ_BIT(INTCON,TMR0IE)) == INTERRUPT_ENABLE) && ((READ_BIT(INTCON,TMR0IF)) == INTERRUPT_OCCURED) )
    {
        TIMER0_ISR();
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*______________________TIMER1_INTERRUPT_FEATURE______________________________*/
    /*____________________________________________________________________________*/
    #if  TIMER1_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    if( ((READ_BIT(PIE1,TMR1IE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR1,TMR1IF)) == INTERRUPT_OCCURED) )
    {
        TIMER1_ISR();
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*______________________TIMER2_INTERRUPT_FEATURE______________________________*/
    /*____________________________________________________________________________*/
    #if  TIMER2_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    if( ((READ_BIT(PIE1,TMR2IE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR1,TMR2IF)) == INTERRUPT_OCCURED) )
    {
        TIMER2_ISR();
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*______________________TIMER3_INTERRUPT_FEATURE______________________________*/
    /*____________________________________________________________________________*/
    #if  TIMER3_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    if( ((READ_BIT(PIE2,TMR3IE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR2,TMR3IF)) == INTERRUPT_OCCURED) )
    {
        TIMER3_ISR();
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*______________________CCP1_INTERRUPT_FEATURE________________________________*/
    /*____________________________________________________________________________*/
    #if  CCP1_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    if( ((READ_BIT(PIE1,CCP1IE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR1,CCP1IF)) == INTERRUPT_OCCURED) )
    {
        CCP1_ISR();
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*______________________CCP2_INTERRUPT_FEATURE________________________________*/
    /*____________________________________________________________________________*/
    #if  CCP2_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    if( ((READ_BIT(PIE2,CCP2IE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR2,CCP2IF)) == INTERRUPT_OCCURED) )
    {
        CCP2_ISR();
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*______________________USART_TX_INTERRUPT_FEATURE____________________________*/
    /*____________________________________________________________________________*/
    #if  USART_TX_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    if( ((READ_BIT(PIE1,TXIE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR1,TXIF)) == INTERRUPT_OCCURED) )
    {
        USART_TX_ISR();
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*______________________USART_RX_INTERRUPT_FEATURE____________________________*/
    /*____________________________________________________________________________*/
    #if  USART_RX_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    if( ((READ_BIT(PIE1,RCIE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR1,RCIF)) == INTERRUPT_OCCURED) )
    {
        USART_RX_ISR();
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*____________________________________________________________________________*/
    /*__________________________SPI_INTERRUPT_FEATURE_____________________________*/
    /*____________________________________________________________________________*/
    #if  SPI_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    if( ((READ_BIT(PIE1,SSPIE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR1,SSPIF)) == INTERRUPT_OCCURED) )
    {
        SPI_ISR();
    }
    else{/*NOTHING*/}
    #endif
    /*____________________________________________________________________________*/
    /*____________________________________________________________________________*/
    /*__________________________I2C_INTERRUPT_FEATURE_____________________________*/
    /*____________________________________________________________________________*/
    #if  I2C_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    if( ((READ_BIT(PIE1,SSPIE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR1,SSPIF)) == INTERRUPT_OCCURED) )
    {
        I2C_ISR();
    }
    else{/*NOTHING*/}
    if( ((READ_BIT(PIE2,BCLIE)) == INTERRUPT_ENABLE) && ((READ_BIT(PIR2,BCLIF)) == INTERRUPT_OCCURED) )
    {
        I2C_DATA_COLLISION_ISR();
    }
    else{/*NOTHING*/}
    #endif
}
#endif