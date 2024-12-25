/* 
 * File:   TIMER1_PROGRAM.c
 * Author: ziad osama
 *
 * Created on November 11, 2024, 8:57 PM
 */
/*_____________________________________________________________________________*/
/*                         Section : Includes                                  */
/*_____________________________________________________________________________*/
#include "TIMER1_INTERFACE.h"
/*_____________________________________________________________________________*/
/*                         Section : Global Pointer To Functions               */
/*_____________________________________________________________________________*/

#if  TIMER1_INTERRUPT_FEATURE == INTERRUPT_ENABLE
void (*TIMER1_INTERRUPT_HANDELAR_TASK)(void) = NULL;
#endif 
/*_____________________________________________________________________________*/
/*                         Section : Global Variables                          */
/*_____________________________________________________________________________*/
static uint16 Timer1PreLoadValue = 0 ;
/*_____________________________________________________________________________*/
/*                         Section : Helper Functions                          */
/*_____________________________________________________________________________*/
/**
 * 
 * @param timer1
 */
static void TIMER1_SELECT_PRESCALER_VALUE(const TIMER1_t * timer1)
{
    T1CON &= 0xCF;
    T1CON |= ((timer1->PrescalerValue)<<4);
}
/**
 * 
 * @param timer1
 */
static void TIMER1_SELECT_MODE(const TIMER1_t * timer1)
{
    if((timer1->Timer1_Mode) == TIMER1_SET_TIMER_MODE)
    {
        TIMER1_TIMER_MODE();
    }
    else if((timer1->Timer1_Mode) == TIMER1_SET_COUNTER_MODE)
    {
        TIMER1_COUNTER_MODE();
        if((timer1->Timer1_Countr_Mode_ASYNC_or_SYNC)== TIMER1_USE_COUNTER_MODE_ASYNCHRONIZE_T1_OSC)
        {
            TIMER1_COUNTER_MODE_ASYNCHRONIZE_T1_OSC();
        }
        else if((timer1->Timer1_Countr_Mode_ASYNC_or_SYNC)== TIMER1_USE_COUNTER_MODE_SYNCHRONIZE_T1_OSC)
        {
            TIMER1_COUNTER_MODE_SYNCHRONIZE_T1_OSC();
        }
        else
        {
            asm("NOP");
        }
    } 
    else
    {
        asm("NOP");
    }
}
/**
 * 
 * @param timer1
 */
#if  TIMER1_INTERRUPT_FEATURE == INTERRUPT_ENABLE
#if INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE
static void TIMER1_SELECT_INTERRUPT_PRORITY(const TIMER1_t * timer1)
{
    if((timer1->Timer1_Priority) == INTERRUPT_LOW_PRIORITY)
    {
        TIMER1_SET_INTERRUPT_LOW_PRIORITY();
    }
    else if ((timer1->Timer1_Priority) == INTERRUPT_HIGH_PRIORITY)
    {
        TIMER1_SET_INTERRUPT_HIGH_PRIORITY();
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
 * @param timer1
 * @return 
 */
std_ReturnType TIMER1_INITALIZE(const TIMER1_t * timer1)
{
    std_ReturnType RET = E_OK;
    if(timer1 == NULL)
    {
        RET = E_NOT_OK;
    }
    else
    {
        /*Disable Timer1 Module*/
        TIMER1_DISABLE();
        /*Select The Pre-Scaler*/
        TIMER1_SELECT_PRESCALER_VALUE(timer1);
        /*Select Timer1 Mode*/
        TIMER1_SELECT_MODE(timer1);
        /*Initialize The Counter Registers*/
        TMR1H = ((timer1->Timer1_Preload_Value)>> 8);
        TMR1L = (uint8)(timer1->Timer1_Preload_Value) ;
        /*Copy The Initialize The Counter Registers */
        Timer1PreLoadValue = (timer1->Timer1_Preload_Value);
/*_____________________________________________________________________________*/
        #if  TIMER1_INTERRUPT_FEATURE == INTERRUPT_ENABLE
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERAL_INTERRUPT_ENABLE();
        TIMER1_INTERRUPT_ENABLE();
        TIMER1_CLEAR_INTERRUPT_FLAG();
        TIMER1_INTERRUPT_HANDELAR_TASK = timer1->Timer1_Interrupt_Handelar;
/*_____________________________________________________________________________*/
        #if INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE
        INTERRUPT_PRORITY_LEVELS_ENABLE();
        TIMER1_SELECT_INTERRUPT_PRORITY(timer1);
        #endif
/*_____________________________________________________________________________*/
        #endif
    }
/*_____________________________________________________________________________*/
    /*Enable Timer1 Module*/
    TIMER1_ENABLE();
    return (RET);
}
/**
 * 
 * @param timer1
 * @return 
 */
std_ReturnType TIMER1_DEITIALIZE(const TIMER1_t * timer1)
{
    std_ReturnType RET = E_OK;
    if(timer1 == NULL)
    {
        RET = E_NOT_OK;
    }
    else
    {
        TIMER1_DISABLE();
        #if  TIMER1_INTERRUPT_FEATURE == INTERRUPT_ENABLE
        TIMER1_INTERRUPT_DISABLE();
        #endif
    }
    return (RET);
}
/**
 * 
 * @param timer1
 * @param value
 * @return 
 */
std_ReturnType TIMER1_WRITE_VALUE_AT_COUNTER_REGISTER(const TIMER1_t * timer1,uint16 value)
{
    std_ReturnType RET = E_OK;
    if(timer1 == NULL)
    {
        RET = E_NOT_OK;
    }
    else
    {
        TMR1H = ((value)>> 8) ;
        TMR1L = (uint8)(value) ;
    }
    return (RET);
}
/**
 * 
 * @param timer1
 * @param value
 * @return 
 */
std_ReturnType TIMER1_READ_VALUE_FROM_COUNTER_REGISTER(const TIMER1_t * timer1,uint16 * value)
{
    std_ReturnType RET = E_OK ;
    uint8 TEMP_TMR1L = 0 ,TEMP_TMR1H = 0;
    if((timer1== NULL) || (value == NULL))
    {
        RET = E_NOT_OK;
    }
    else
    {
        TEMP_TMR1L = TMR1L;
        TEMP_TMR1H = TMR1H;
        *value = (uint16)((TMR1H<<8) + TEMP_TMR1L);
    }
    return (RET);
}
/*_____________________________________________________________________________*/
/*                         Section : ISR Definitions                           */
/*_____________________________________________________________________________*/

#if  TIMER1_INTERRUPT_FEATURE == INTERRUPT_ENABLE
void TIMER1_ISR(void)
{
    TIMER1_CLEAR_INTERRUPT_FLAG();
    TMR1H = ((Timer1PreLoadValue)>> 8);
    TMR1L = (uint8)(Timer1PreLoadValue) ;
    if(TIMER1_INTERRUPT_HANDELAR_TASK)
    {
        TIMER1_INTERRUPT_HANDELAR_TASK();
    }
}
#endif