/* 
 * File:   TIMER2_INTERFACE.h
 * Author: ziad osama
 *
 * Created on November 12, 2024, 7:34 PM
 */

#ifndef TIMER2_INTERFACE_H
#define	TIMER2_INTERFACE_H
/*_____________________________________________________________________________*/
/*                         Section : Includes                                  */
/*_____________________________________________________________________________*/
#include "TIMER2_REGISTERS.h"
#include "../../INTERRUPT/MCAL_INTERNAL_INTERRUPT.h"
/*_____________________________________________________________________________*/
/*                         Section : Macro Definitions                         */
/*_____________________________________________________________________________*/
/*_____________________________________________________________________________*/
/*                         Section : Macro Functions                           */
/*_____________________________________________________________________________*/
#define   TIMER2_ENABLE()                              (SET_BIT(T2CON,TMR2ON))
#define   TIMER2_DISABLE()                             (CLEAR_BIT(T2CON,TMR2ON))
/*_____________________________________________________________________________*/
/*_____________________________________________________________________________*/
/*                         Section : Data Type Declaration                     */
/*_____________________________________________________________________________*/
typedef enum 
{
    Prescaler_is_1,
    Prescaler_is_4, 
    Prescaler_is_16, 
            
}Timer2_Prescaler_Value;

typedef enum 
{
    _1_1_Postscale,
    _1_2_Postscale, 
    _1_3_Postscale,
    _1_4_Postscale,
    _1_5_Postscale,
    _1_6_Postscale,
    _1_7_Postscale,
    _1_8_Postscale,
    _1_9_Postscale,
    _1_10_Postscale,
    _1_11_Postscale,
    _1_12_Postscale,
    _1_13_Postscale,
    _1_14_Postscale,
    _1_15_Postscale,
    _1_16_Postscale,
            
}Timer2_Postscale_Value;

typedef struct 
{
#if TIMER2_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    void (*Timer2_Interrupt_Handelar)(void);
    INTERRUPT_PRIORITY Timer2_Priority ;
#endif
   uint8 Timer2_Preload_Value;
   Timer2_Postscale_Value PostscaleValue ;
   Timer2_Prescaler_Value PrescalerValue ;
}TIMER2_t;
/*_____________________________________________________________________________*/
/*                         Section : APIs Declaration                          */
/*_____________________________________________________________________________*/
std_ReturnType TIMER2_INITALIZE(const TIMER2_t * timer2);
std_ReturnType TIMER2_DEITIALIZE(const TIMER2_t * timer2);
std_ReturnType TIMER2_WRITE_VALUE_AT_COUNTER_REGISTER(const TIMER2_t * timer2,uint8 value);
std_ReturnType TIMER2_READ_VALUE_FROM_COUNTER_REGISTER(const TIMER2_t * timer2,uint8 * value);

#endif	/* TIMER2_INTERFACE_H */

