/* 
 * File:   TIMER3_PROGRAM.c
 * Author: ziad osama
 *
 * Created on November 15, 2024, 12:48 AM
 */
/*_____________________________________________________________________________*/
/*                         Section : Includes                                  */
/*_____________________________________________________________________________*/
#include "TIMER3_INTERFACE.h"
/*_____________________________________________________________________________*/
/*                         Section : Global Pointer To Functions               */
/*_____________________________________________________________________________*/

#if  TIMER3_INTERRUPT_FEATURE == INTERRUPT_ENABLE
void (*TIMER3_INTERRUPT_HANDELAR_TASK)(void) = NULL;
#endif 
/*_____________________________________________________________________________*/
/*                         Section : Global Variables                          */
/*_____________________________________________________________________________*/
static uint16 Timer3PreLoadValue = 0 ;
/*_____________________________________________________________________________*/
/*                         Section : Helper Functions                          */
/*_____________________________________________________________________________*/
/**
 * 
 * @param timer3
 */
static void TIMER3_SELECT_MODE(const TIMER3_t * timer3)
{
    if((timer3->Timer3_Mode) == Timer3_Timer_Mode)
    {
        TIMER3_SET_TIMER_MODE();
    }
    else if((timer3->Timer3_Mode) == Timer3_Counter_Mode)
    {
        TIMER3_SET_COUNTER_MODE();
    }
}
/**
 * 
 * @param timer3
 */
static void TIMER3_SELECT_COUNTER_MODE_SYNCHRONIZATION(const TIMER3_t * timer3)
{
    if((timer3->Timer3_Synchronization_Counter_Mode) == Timer3_Synchronize)
    {
       TIMER3_COUNTER_MODE_SYNCHRONIZE();
    }
    else if((timer3->Timer3_Synchronization_Counter_Mode) == Timer3_Asynchronize)
    {
        TIMER3_COUNTER_MODE_ASYNCHRONIZE();
    }
}
/**
 * 
 * @param timer3
 */
 static void TIMER3_SELECT_PRESCALER_VALUE(const TIMER3_t * timer3)
 {
     T3CON &= 0xCF;
     T3CON |=((timer3->Timer3_Prescaler_Value)<<4);
 }
 /**
  * 
  * @param timer3
  */
  static void TIMER3_SELECT_REGISTER_SIZE(const TIMER3_t * timer3)
  {
      if((timer3->Timer3_Register_Size) == Timer3_16_Bit_Register)
      {
          TIMER3_SET_16_BIT_COUNTER_REGISTER();
      }
      else if ((timer3->Timer3_Register_Size) == Timer3_8_Bit_Register)
      {
          TIMER3_SET_8_BIT_COUNTER_REGISTER();
      }
  }
/*_____________________________________________________________________________*/
/*                         Section : APIs Definitions                          */
/*_____________________________________________________________________________*/
  /**
   * 
   * @param timer3
   * @return 
   */
std_ReturnType TIMER3_INITALIZE(const TIMER3_t * timer3)
{
    std_ReturnType RET = E_OK;
    if(timer3 == NULL)
    {
        RET = E_NOT_OK;
    }
    else
    {
        /*Timer3 Disable*/
        TIMER3_DISABLE();
        /*Timer3 Select Mode*/
        TIMER3_SELECT_MODE(timer3);
        /*Timer3 Select Synchronization For Counter Mode*/
        TIMER3_SELECT_COUNTER_MODE_SYNCHRONIZATION(timer3);
        /*Timer 3 Select Pre-Scaler Value */
        TIMER3_SELECT_PRESCALER_VALUE(timer3);
        /*Timer3 Select Register Size */
        TIMER3_SELECT_REGISTER_SIZE(timer3);
        /*Copy The Value at The Counter Register*/
        Timer3PreLoadValue = (timer3->Timer3_Preload_Value);
        /*Timer3 Initialize Pre-loaded Value by Registers */
        TMR3H =((timer3->Timer3_Preload_Value)<<8);
        TMR3L =(uint8)(timer3->Timer3_Preload_Value);
        #if  TIMER3_INTERRUPT_FEATURE == INTERRUPT_ENABLE
/*_____________________________________________________________________________*/
        TIMER3_INTERRUPT_HANDELAR_TASK = (timer3->Timer3_Interrupt_Handelar);
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERAL_INTERRUPT_ENABLE();
        TIMER3_INTERRUPT_ENABLE();
/*_____________________________________________________________________________*/
        #if  INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE
        INTERRUPT_PRORITY_LEVELS_ENABLE();
        if((timer3->Timer3_Priority) == INTERRUPT_HIGH_PRIORITY)
        {
             TIMER3_SET_INTERRUPT_HIGH_PRIORITY(); 
        }
        else if((timer3->Timer3_Priority) == INTERRUPT_LOW_PRIORITY)
        {
             TIMER3_SET_INTERRUPT_LOW_PRIORITY();
        }
        #endif
/*_____________________________________________________________________________*/
        #endif
/*_____________________________________________________________________________*/
        /*Timer3 Enable*/
        TIMER3_ENABLE();
    }
    return (RET);
}
/**
 * 
 * @param timer3
 * @return 
 */
std_ReturnType TIMER3_DEITIALIZE(const TIMER3_t * timer3)
{
    std_ReturnType RET = E_OK;
    if(timer3 == NULL)
    {
        RET = E_NOT_OK;
    }
    else
    {
        TIMER3_DISABLE();
        #if  TIMER3_INTERRUPT_FEATURE == INTERRUPT_ENABLE
        TIMER3_INTERRUPT_DISABLE();
        #endif
    }
    return (RET);
}
/**
 * 
 * @param timer3
 * @param value
 * @return 
 */
std_ReturnType TIMER3_READ_VALUE_FROM_COUNTER_REGISTER(const TIMER3_t * timer3,uint16 * value)
{
    std_ReturnType RET = E_OK;
    uint8 TEMP_TMR3H = 0 , TEMP_TMR3L = 0 ;
    if((timer3 == NULL) || (value == NULL))
    {
        RET = E_NOT_OK;
    }
    else
    {
        TEMP_TMR3H = TMR3H;
        TEMP_TMR3L = TMR3L;
        *value = (uint16)((TEMP_TMR3H<<8)+TEMP_TMR3L);
    }
    return (RET);
}
/**
 * 
 * @param timer3
 * @param value
 * @return 
 */
std_ReturnType TIMER3_WRITE_VALUE_AT_COUNTER_REGISTER(const TIMER3_t * timer3,uint16 value)
{
    std_ReturnType RET = E_OK;
    if(timer3 == NULL)
    {
        RET = E_NOT_OK;
    }
    else
    {
       TMR3H = ((value)>> 8) ;
       TMR3L = (uint8)(value) ;
    }
    return (RET);
}
/*_____________________________________________________________________________*/
/*                         Section : ISR Definitions                           */
/*_____________________________________________________________________________*/

#if  TIMER3_INTERRUPT_FEATURE == INTERRUPT_ENABLE
void TIMER3_ISR(void)
{
    TIMER3_CLEAR_INTERRUPT_FLAG();
    TMR3H =((Timer3PreLoadValue)<<8);
    TMR3L =(uint8)(Timer3PreLoadValue);
    if(TIMER3_INTERRUPT_HANDELAR_TASK)
    {
        TIMER3_INTERRUPT_HANDELAR_TASK();
    }
}
#endif