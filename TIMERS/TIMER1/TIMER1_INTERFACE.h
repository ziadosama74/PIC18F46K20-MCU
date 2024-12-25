/* 
 * File:   TIMER1_INTERFACE.h
 * Author: ziad osama
 *
 * Created on November 11, 2024, 8:57 PM
 */

#ifndef TIMER1_INTERFACE_H
#define	TIMER1_INTERFACE_H
/*_____________________________________________________________________________*/
/*                         Section : Includes                                  */
/*_____________________________________________________________________________*/
#include "TIMER1_REGISTERS.h"
#include "../../INTERRUPT/MCAL_INTERNAL_INTERRUPT.h"
/*_____________________________________________________________________________*/
/*                         Section : Macro Definitions                         */
/*_____________________________________________________________________________*/
#define    TIMER1_SET_TIMER_MODE                               1
#define    TIMER1_SET_COUNTER_MODE                             0
/*_____________________________________________________________________________*/
#define    TIMER1_USE_COUNTER_MODE_ASYNCHRONIZE_T1_OSC         1
#define    TIMER1_USE_COUNTER_MODE_SYNCHRONIZE_T1_OSC          0
/*_____________________________________________________________________________*/
#define    TIMER1_USE_TIMER1_OSC_32_KHz_CRYSTALS               1
#define    TIMER1_DO_NOT_USE_TIMER1_OSC_32_KHz_CRYSTALS        0
/*_____________________________________________________________________________*/
#define    TIMER1_R_W_REGISTER_16_BIT                          1
#define    TIMER1_R_W_REGISTER_8_BIT                           0
/*_____________________________________________________________________________*/
/*_____________________________________________________________________________*/
/*                         Section : Macro Functions                           */
/*_____________________________________________________________________________*/
#define    TIMER1_ENABLE()                             (SET_BIT(T1CON,TMR1ON))
#define    TIMER1_DISABLE()                            (CLEAR_BIT(T1CON,TMR1ON))
/*_____________________________________________________________________________*/
#define    TIMER1_TIMER_MODE()                         (CLEAR_BIT(T1CON,TMR1CS))
#define    TIMER1_COUNTER_MODE()                       (SET_BIT(T1CON,TMR1CS))
/*_____________________________________________________________________________*/
#define    TIMER1_COUNTER_MODE_ASYNCHRONIZE_T1_OSC()   (SET_BIT(T1CON,T1SYNC))
#define    TIMER1_COUNTER_MODE_SYNCHRONIZE_T1_OSC()    (CLEAR_BIT(T1CON,T1SYNC))
/*_____________________________________________________________________________*/
#define    TIMER1_ENABLE_TIMER1_OSC_32_KHz_CRYSTALS()  (SET_BIT(T1CON,T1OSCEN))
#define    TIMER1_DISABLE_TIMER1_OSC_32_KHz_CRYSTALS() (CLEAR_BIT(T1CON,T1OSCEN))
/*_____________________________________________________________________________*/
#define    TIMER1_16_BIT_R_W_OPERATION()               (SET_BIT(T1CON,RD16))
#define    TIMER1_8_BIT_R_W_OPERATION()                (CLEAR_BIT(T1CON,RD16))
/*_____________________________________________________________________________*/
#define    TIMER1_READ_SYSTEM_CLOCK_SOURCE()           (READ_BIT(T1CON,T1RUN))
/*_____________________________________________________________________________*/
/*_____________________________________________________________________________*/
/*                         Section : Data Types Declaration                    */
/*_____________________________________________________________________________*/
typedef enum
{
    
    _1_1_Prescale_Value = 0,
    _1_2_Prescale_Value,
    _1_4_Prescale_Value,
    _1_8_Prescale_Value
            
}Timer1_Prescaler_Value;

typedef struct 
{
#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    void (*Timer1_Interrupt_Handelar)(void)   ;
    INTERRUPT_PRIORITY Timer1_Priority        ;
#endif
   Timer1_Prescaler_Value PrescalerValue      ;
   uint16 Timer1_Preload_Value                ;
   uint8 Timer1_Mode                      : 1 ;
   uint8 Timer1_Countr_Mode_ASYNC_or_SYNC : 1 ;
   uint8 Timer1_OSC_32_KHz_Crystals_Mode  : 1 ;
   uint8 Timer1_Register_R_W_Mode         : 1 ;
}TIMER1_t;
/*_____________________________________________________________________________*/
/*                         Section : APIs Declaration                          */
/*_____________________________________________________________________________*/
std_ReturnType TIMER1_INITALIZE(const TIMER1_t * timer1);
std_ReturnType TIMER1_DEITIALIZE(const TIMER1_t * timer1);
std_ReturnType TIMER1_WRITE_VALUE_AT_COUNTER_REGISTER(const TIMER1_t * timer1,uint16 value);
std_ReturnType TIMER1_READ_VALUE_FROM_COUNTER_REGISTER(const TIMER1_t * timer1,uint16 * value);

#endif	/* TIMER1_INTERFACE_H */ 

