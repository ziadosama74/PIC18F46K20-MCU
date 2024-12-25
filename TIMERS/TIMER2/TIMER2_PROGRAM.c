/* 
 * File:   TIMER2_PROGRAM.c
 * Author: ziad osama
 *
 * Created on November 12, 2024, 7:34 PM
 */
/*_____________________________________________________________________________*/
/*                         Section : Includes                                  */
/*_____________________________________________________________________________*/
#include "TIMER2_INTERFACE.h"
/*_____________________________________________________________________________*/
/*                         Section : Global Pointer To Functions               */
/*_____________________________________________________________________________*/

#if  TIMER2_INTERRUPT_FEATURE == INTERRUPT_ENABLE
void (*TIMER2_INTERRUPT_HANDELAR_TASK)(void) = NULL;
#endif 
/*_____________________________________________________________________________*/
/*                         Section : Global Variables                          */
/*_____________________________________________________________________________*/
static uint16 Timer2PreLoadValue = 0 ;
/*_____________________________________________________________________________*/
/*                         Section : Helper Functions                          */
/*_____________________________________________________________________________*/
/**
 * 
 * @param timer2
 */
static void TIMER2_SELECT_PRESCALER(const TIMER2_t * timer2)
{
    T2CON &= 0xFC;
    T2CON |=(timer2->PrescalerValue);
}
/**
 * 
 * @param timer2
 */
static void TIMER2_SELECT_POSTSCALER(const TIMER2_t * timer2)
{
    T2CON &= 0x87;
    T2CON |= ((timer2->PostscaleValue)<<3);
}
/*_____________________________________________________________________________*/
/*                         Section : APIs Definitions                          */
/*_____________________________________________________________________________*/
/**
 * 
 * @param timer2
 * @return 
 */
std_ReturnType TIMER2_INITALIZE(const TIMER2_t * timer2)
{
    std_ReturnType RET = E_OK;
    if(timer2 == NULL)
    {
        RET = E_NOT_OK;
    }
    else
    {
        /*Disable Timer2 Module*/
        TIMER2_DISABLE();
        /*Select The Pre-Scaler Value*/
        TIMER2_SELECT_PRESCALER(timer2);
        /*Select The Post-Scaler Value*/
        TIMER2_SELECT_POSTSCALER(timer2);
        /*Copy The Value at The Counter Register*/
        Timer2PreLoadValue = (timer2->Timer2_Preload_Value);
        TMR2 = (timer2->Timer2_Preload_Value);
        /*Initialize Timer2 Interrupt Handler Task */
        #if  TIMER2_INTERRUPT_FEATURE == INTERRUPT_ENABLE
        TIMER2_INTERRUPT_HANDELAR_TASK = (timer2->Timer2_Interrupt_Handelar);
        #endif
        /*_____________________________________________________________________________*/
        #if  TIMER2_INTERRUPT_FEATURE == INTERRUPT_ENABLE
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERAL_INTERRUPT_ENABLE();
        TIMER2_INTERRUPT_ENABLE();
        /*_____________________________________________________________________________*/
        #if INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE
        INTERRUPT_PRORITY_LEVELS_ENABLE();
        if((timer2->Timer2_Priority) == INTERRUPT_HIGH_PRIORITY)
        {
            TIMER2_SET_INTERRUPT_HIGH_PRIORITY();
        }
        else if ((timer2->Timer2_Priority) == INTERRUPT_LOW_PRIORITY)
        {
            TIMER2_SET_INTERRUPT_LOW_PRIORITY();
        }
        else
        {
            asm("NOP");
        }
        #endif
        /*_____________________________________________________________________________*/
        #endif
        /*_____________________________________________________________________________*/
        /*Enable Timer2 Module*/
        TIMER2_ENABLE();
    }
    return (RET);
}
/**
 * 
 * @param timer2
 * @return 
 */
std_ReturnType TIMER2_DEITIALIZE(const TIMER2_t * timer2)
{
    std_ReturnType RET = E_OK;
    if(timer2 == NULL)
    {
        RET = E_NOT_OK;
    }
    else
    {
        TIMER2_DISABLE();
        #if  TIMER2_INTERRUPT_FEATURE == INTERRUPT_ENABLE
        TIMER2_INTERRUPT_DISABLE();
        #endif
    }
    return (RET);
}
/**
 * 
 * @param timer2
 * @param value
 * @return 
 */
std_ReturnType TIMER2_WRITE_VALUE_AT_COUNTER_REGISTER(const TIMER2_t * timer2,uint8 value)
{
    std_ReturnType RET = E_OK;
    if(timer2 == NULL)
    {
        RET = E_NOT_OK;
    }
    else
    {
        TMR2 = value;
    }
    return (RET);
}
/**
 * 
 * @param timer2
 * @param value
 * @return 
 */
std_ReturnType TIMER2_READ_VALUE_FROM_COUNTER_REGISTER(const TIMER2_t * timer2,uint8 * value)
{
    std_ReturnType RET = E_OK;
    if((timer2 == NULL) || (value == NULL))
    {
        RET = E_NOT_OK;
    }
    else
    {
        *value = TMR2;
    }
    return (RET);
}
/*_____________________________________________________________________________*/
/*                         Section : ISR Definitions                           */
/*_____________________________________________________________________________*/

#if  TIMER2_INTERRUPT_FEATURE == INTERRUPT_ENABLE
void TIMER2_ISR(void)
{
    TIMER2_CLEAR_INTERRUPT_FLAG();
    TMR2 = Timer2PreLoadValue;
    if(TIMER2_INTERRUPT_HANDELAR_TASK)
    {
        TIMER2_INTERRUPT_HANDELAR_TASK();
    }
}
#endif