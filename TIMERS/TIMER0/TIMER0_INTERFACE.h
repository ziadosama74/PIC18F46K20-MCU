/* 
 * File:   TIMER0_INTERFACE.h
 * Author: ziad osama
 *
 * Created on November 9, 2024, 6:52 PM
 */

#ifndef TIMER0_INTERFACE_H
#define	TIMER0_INTERFACE_H
/*_____________________________________________________________________________*/
/*                         Section : Includes                                  */
/*_____________________________________________________________________________*/
#include "TIMER0_CONFIG.h"
#include "TIMER0_REGISTERS.h"
#include "../../INTERRUPT/MCAL_INTERNAL_INTERRUPT.h"
#include "../../GPIO/GPIO_Interface.h"
/*_____________________________________________________________________________*/
/*                         Section : Macro Definitions                         */
/*_____________________________________________________________________________*/
#define       TIMER0_TIMER_MODE                                   1
#define       TIMER0_COUNTER_MODE                                 0
#define       TIMER0_8_BIT_REGISTER_SIZE                          1
#define       TIMER0_16_BIT_REGISTER_SIZE                         0
#define       PRESCALER_SELECT_ENABLE                             1
#define       PRESCALER_SELECT_DISABLE                            0
#define       EXTERNAL_CLOCK_SOURCE_FALLING_EDGE                  1
#define       EXTERNAL_CLOCK_SOURCE_RAISING_EDGE                  0
/*_____________________________________________________________________________*/
/*                         Section : Macro Functions                           */
/*_____________________________________________________________________________*/
#define       TIMER0_ENABLE()                       (SET_BIT(T0CON,TMR0ON))
#define       TIMER0_DISABLE()                      (CLEAR_BIT(T0CON,TMR0ON))

#define       TIMER0_PRESCALER_ENABLE()             (CLEAR_BIT(T0CON,PSA))
#define       TIMER0_PRESCALER_DISABLE()            (SET_BIT(T0CON,PSA))

#define       TIMER0_CONFIGURE_8_BIT_RESLUTION()    (SET_BIT(T0CON,T08BIT))
#define       TIMER0_CONFIGURE_16_BIT_RESLUTION()   (CLEAR_BIT(T0CON,T08BIT))

#define       TIMER0_TIMER_MODE_ENABLE()            (CLEAR_BIT(T0CON,T0CS))
#define       TIMER0_COUNTER_MODE_ENABLE()          (SET_BIT(T0CON,T0CS))

#define       TIMER0_COUNTER_MODE_FALLING_Edge()    (SET_BIT(T0CON,T0SE))
#define       TIMER0_COUNTER_MODE_RAISING_Edge()    (CLEAR_BIT(T0CON,T0SE))
/*_____________________________________________________________________________*/
/*                         Section : Data Types Declaration                    */
/*_____________________________________________________________________________*/
typedef enum 
{
  _1_2_PrescaleValue,
  _1_4_PrescaleValue,
  _1_8_PrescaleValue,
  _1_16_PrescaleValue,
  _1_32_PrescaleValue,
  _1_64_PrescaleValue,
  _1_128_PrescaleValue,
  _1_256_PrescaleValue,
}Timer0_Prescaler_Select;

typedef struct 
{
    #if  TIMER0_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    void  (*Timer0_Interrupt_Handelar)(void);
    INTERRUPT_PRIORITY Timer0_Priority;
    #endif
    uint16 Timer0_Preload_Value ;
    Timer0_Prescaler_Select PrescalerValue ;
    uint8 PrescalerSelect          : 1 ;
    uint8 Timer0_Mode              : 1 ;
    uint8 Timer0_Register_Size     : 1 ;
    uint8 Timer0_Counter_Mode_Edge : 1 ;
    uint8 Timer0_Resreved_Bits     : 4 ;
}TIMER0_t;
/*_____________________________________________________________________________*/
/*                         Section : APIs Declaration                          */
/*_____________________________________________________________________________*/
std_ReturnType TIMER0_INITIALIZE(const TIMER0_t * timer0);
std_ReturnType TIMER0_DEITIALIZE(const TIMER0_t * timer0);
std_ReturnType TIMER0_WRITE_VALUE_AT_COUNTER_REGISTER(const TIMER0_t * timer0,uint16 value);
std_ReturnType TIMER0_READ_VALUE_FROM_COUNTER_REGISTER(const TIMER0_t * timer0,uint16 * value);
#endif	/* TIMER0_INTERFACE_H */

