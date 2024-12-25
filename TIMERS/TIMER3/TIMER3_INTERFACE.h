/* 
 * File:   TIMER3_INTERFACE.h
 * Author: ziad osama
 *
 * Created on November 15, 2024, 12:48 AM
 */

#ifndef TIMER3_INTERFACE_H
#define	TIMER3_INTERFACE_H
/*_____________________________________________________________________________*/
/*                         Section : Includes                                  */
/*_____________________________________________________________________________*/
#include "TIMER3_REGISTER.h"
#include "../../INTERRUPT/MCAL_INTERNAL_INTERRUPT.h"
/*_____________________________________________________________________________*/
/*                         Section : Macro Definitions                         */
/*_____________________________________________________________________________*/

/*_____________________________________________________________________________*/
/*                         Section : Macro Functions                           */
/*_____________________________________________________________________________*/
#define    TIMER3_ENABLE()                             (SET_BIT(T3CON,TMR3ON))
#define    TIMER3_DISABLE()                            (CLEAR_BIT(T3CON,TMR3ON))
/*_____________________________________________________________________________*/
// Internal clock (FOSC/4)
#define    TIMER3_SET_TIMER_MODE()                     (CLEAR_BIT(T3CON,TMR3CS))
//External clock input from Timer1 oscillator or T13CKI (on the rising edge after the first falling edge)
#define    TIMER3_SET_COUNTER_MODE()                   (SET_BIT(T3CON,TMR3CS))
/*_____________________________________________________________________________*/
#define   TIMER3_COUNTER_MODE_SYNCHRONIZE()            (CLEAR_BIT(T3CON,T3SYNC))
#define   TIMER3_COUNTER_MODE_ASYNCHRONIZE()           (SET_BIT(T3CON,T3SYNC))
/*_____________________________________________________________________________*/
#define   TIMER3_SET_16_BIT_COUNTER_REGISTER()         (SET_BIT(T3CON,RD16))
#define   TIMER3_SET_8_BIT_COUNTER_REGISTER()          (CLEAR_BIT(T3CON,RD16))
/*_____________________________________________________________________________*/
/*                         Section : Data Type Declaration                     */
/*_____________________________________________________________________________*/
typedef enum 
{
    _1_1_Prescaler_Value,
    _1_2_Prescaler_Value, 
    _1_4_Prescaler_Value,
    _1_8_Prescaler_Value
            
}Timer3_Prescaler_Value;
/*_____________________________________________________________________________*/
typedef enum 
{
    Timer3_Timer_Mode,
    Timer3_Counter_Mode, 
            
}Timer3_Mode;
/*_____________________________________________________________________________*/
typedef enum 
{
    Timer3_8_Bit_Register,
    Timer3_16_Bit_Register, 
            
}Timer3_Register_Size;
/*_____________________________________________________________________________*/
typedef enum 
{
    Timer3_Synchronize,
    Timer3_Asynchronize, 
            
}Timer3_Synchronization_Counter_Mode;
/*_____________________________________________________________________________*/
typedef struct 
{
    #if  TIMER3_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    void  (*Timer3_Interrupt_Handelar)(void);
    INTERRUPT_PRIORITY Timer3_Priority;
    #endif
    uint16 Timer3_Preload_Value ;
    Timer3_Prescaler_Value Timer3_Prescaler_Value ;
    Timer3_Mode Timer3_Mode ;
    Timer3_Register_Size Timer3_Register_Size ;
    Timer3_Synchronization_Counter_Mode Timer3_Synchronization_Counter_Mode;
}TIMER3_t;
/*_____________________________________________________________________________*/
/*                         Section : APIs Declaration                          */
/*_____________________________________________________________________________*/
std_ReturnType TIMER3_INITALIZE(const TIMER3_t * timer3);
std_ReturnType TIMER3_DEITIALIZE(const TIMER3_t * timer3);
std_ReturnType TIMER3_WRITE_VALUE_AT_COUNTER_REGISTER(const TIMER3_t * timer3,uint16 value);
std_ReturnType TIMER3_READ_VALUE_FROM_COUNTER_REGISTER(const TIMER3_t * timer3,uint16 * value);
#endif	/* TIMER3_INTERFACE_H */

