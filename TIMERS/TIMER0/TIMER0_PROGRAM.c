/* 
 * File:  TIMER0_PROGRAM.C
 * Author: ziad osama
 *
 * Created on November 9, 2024, 6:52 PM
 */
/*_____________________________________________________________________________*/
/*                         Section : Includes                                  */
/*_____________________________________________________________________________*/
#include "TIMER0_INTERFACE.h"
/*_____________________________________________________________________________*/
/*                         Section : Global Pointer To Functions               */
/*_____________________________________________________________________________*/

#if  TIMER0_INTERRUPT_FEATURE == INTERRUPT_ENABLE
void (*TIMER0_INTERRUPT_HANDELAR_TASK)(void) = NULL;
#endif 
static uint16 Timer0PreLoadValue = 0 ;
/*_____________________________________________________________________________*/
/*                         Section : Helper Functions                          */
/*_____________________________________________________________________________*/
/**
 * 
 * @param timer0
 */
static void TIMER0_PRECALER_CONFIG(const TIMER0_t * timer0)
{
    if((timer0->PrescalerSelect) == PRESCALER_SELECT_ENABLE)
    {
        TIMER0_PRESCALER_ENABLE();
        T0CON &= 0xF8;
        T0CON |=(timer0->PrescalerValue);
    }
    else if ((timer0->PrescalerSelect) == PRESCALER_SELECT_DISABLE)
    {
        TIMER0_PRESCALER_DISABLE();
    }
    else
    {
        asm("NOP");
    }
}
/**
 * 
 * @param timer0
 */
static void TIMER0_SELSECT_MODE(const TIMER0_t * timer0)
{
    if((timer0->Timer0_Mode) == TIMER0_COUNTER_MODE)
    {
        TIMER0_COUNTER_MODE_ENABLE();
        if((timer0->Timer0_Counter_Mode_Edge) == EXTERNAL_CLOCK_SOURCE_FALLING_EDGE)
        {
            TIMER0_COUNTER_MODE_FALLING_Edge();
        }
        else if ((timer0->Timer0_Counter_Mode_Edge) == EXTERNAL_CLOCK_SOURCE_RAISING_EDGE)
        {
            TIMER0_COUNTER_MODE_RAISING_Edge();
        }
        else
        {
            asm("NOP");
        }
    }
    else if ((timer0->Timer0_Mode) == TIMER0_TIMER_MODE)
    {
        TIMER0_TIMER_MODE_ENABLE();
    }
    else
    {
        asm("NOP");
    }
}
/**
 * 
 * @param timer0
 */
static void TIMER0_SELSECT_REGISTER_SIZE(const TIMER0_t * timer0)
{
    if((timer0->Timer0_Register_Size) == TIMER0_8_BIT_REGISTER_SIZE)
    {
        TIMER0_CONFIGURE_8_BIT_RESLUTION();
    }
    else if ((timer0->Timer0_Register_Size) == TIMER0_16_BIT_REGISTER_SIZE)
    {
        TIMER0_CONFIGURE_16_BIT_RESLUTION();
    }
    else
    {
        asm("NOP");
    }
}
#if  TIMER0_INTERRUPT_FEATURE == INTERRUPT_ENABLE
#if  INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE
/**
 * 
 * @param timer0
 */
static void TIMER0_SELSECT_PRIORITY_INTERRUPT(const TIMER0_t * timer0)
{
    if((timer0->Timer0_Priority)== INTERRUPT_HIGH_PRIORITY)
    {
        GLOBAL_INTERRUPT_HIGH_PRORITY_ENABLE();
        TIMER0_SET_INTERRUPT_HIGH_PRIORITY();
    }
    else if ((timer0->Timer0_Priority)== INTERRUPT_LOW_PRIORITY)
    {
        GLOBAL_INTERRUPT_LOW_PRORITY_ENABLE();
        TIMER0_SET_INTERRUPT_LOW_PRIORITY();
    }
    else
    {
        asm("NOP");
    }
}
#endif
#endif

/*_____________________________________________________________________________*/
/*                         Section : APIs Definitions                          */
/*_____________________________________________________________________________*/
/**
 * 
 * @param timer0
 * @return 
 */
std_ReturnType TIMER0_INITIALIZE(const TIMER0_t * timer0)
{
    std_ReturnType RET = E_NOT_OK;
    /*Disable Timer0 Module*/
    TIMER0_DISABLE();
    /*Configure The Timer0 Pre-scaler */
    TIMER0_PRECALER_CONFIG(timer0);
    /*Configure the Timer0 Mode */
    TIMER0_SELSECT_MODE(timer0);
     /*Configure the Timer0 Register Size*/
    TIMER0_SELSECT_REGISTER_SIZE(timer0);
    /*Initialize The Counter Registers*/
    TMR0H = ((timer0->Timer0_Preload_Value)>> 8);
    TMR0L = (uint8)(timer0->Timer0_Preload_Value) ;
    /*Copy The Initialize The Counter Registers */
    Timer0PreLoadValue = (timer0->Timer0_Preload_Value);
    /* Configure the Timer0 Interrupt */
    #if  TIMER0_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    GLOBAL_INTERRUPT_ENABLE();
    PERIPHERAL_INTERRUPT_ENABLE();
    TIMER0_INTERRUPT_ENABLE();
    TIMER0_CLEAR_INTERRUPT_FLAG();
    TIMER0_INTERRUPT_HANDELAR_TASK = timer0->Timer0_Interrupt_Handelar;
    #if  INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE
    INTERRUPT_PRORITY_LEVELS_ENABLE();
    TIMER0_SELSECT_PRIORITY_INTERRUPT(timer0);
    #else
    #endif
    #endif
    /*Enable Timer0 Module*/
    TIMER0_ENABLE();
    return (RET);
}
/**
 * 
 * @param timer0
 * @return 
 */
std_ReturnType TIMER0_DEITIALIZE(const TIMER0_t * timer0)
{
    std_ReturnType RET = E_OK;
    if(timer0 == NULL)
    {
        RET = E_NOT_OK;
    }
    else
    {
        TIMER0_DISABLE();
        #if  TIMER0_INTERRUPT_FEATURE == INTERRUPT_ENABLE
        TIMER0_INTERRUPT_DISABLE();
        #endif 
    }
    return (RET);
}
/**
 * 
 * @param timer0
 * @param value
 * @return 
 */
std_ReturnType TIMER0_WRITE_VALUE_AT_COUNTER_REGISTER(const TIMER0_t * timer0,uint16 value)
{
    std_ReturnType RET = E_OK ;
    if(timer0 == NULL)
    {
        RET = E_NOT_OK;
    }
    else
    {
         TMR0H = ((value)>> 8) ;
         TMR0L = (uint8)(value) ;
    }
    return (RET);
}
/**
 * 
 * @param timer0
 * @param value
 * @return 
 */
std_ReturnType TIMER0_READ_VALUE_FROM_COUNTER_REGISTER(const TIMER0_t * timer0,uint16 * value)
{
    std_ReturnType RET = E_OK ;
    uint8 TEMP_TMR0L = 0 ,TEMP_TMR0H = 0;
    if((timer0 == NULL) || (value == NULL))
    {
        RET = E_NOT_OK;
    }
    else
    {
        TEMP_TMR0L = TMR0L;
        TEMP_TMR0H = TMR0H;
        *value = (uint16)((TEMP_TMR0H<<8) + TEMP_TMR0L);
    }
    return (RET);
}
/*_____________________________________________________________________________*/
/*                         Section : ISR Definitions                           */
/*_____________________________________________________________________________*/
#if  TIMER0_INTERRUPT_FEATURE == INTERRUPT_ENABLE
void TIMER0_ISR(void)
{
    TIMER0_CLEAR_INTERRUPT_FLAG();
    TMR0H = ((Timer0PreLoadValue)>> 8);
    TMR0L = (uint8)(Timer0PreLoadValue) ;
    if(TIMER0_INTERRUPT_HANDELAR_TASK)
    {
        TIMER0_INTERRUPT_HANDELAR_TASK();
    }
}
#endif