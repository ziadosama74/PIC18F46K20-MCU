/* 
 * File:   CCP1_PROGRAM.c
 * Author: ziad osama
 *
 * Created on November 21, 2024, 10:28 PM
 */
/*_____________________________________________________________________________*/
/*                         Section : Includes                                  */
/*_____________________________________________________________________________*/
#include "CCP1_INTERFACE.h"
/*_____________________________________________________________________________*/
/*                         Section : Global Pointers                           */
/*_____________________________________________________________________________*/
#if  CCP1_INTERRUPT_FEATURE == INTERRUPT_ENABLE
static void (*CCP1_INTERRUPT_HANDLER_TASK)(void) = NULL;
#endif
/*_____________________________________________________________________________*/
/*                         Section : Helper Functions                          */
/*_____________________________________________________________________________*/
#if (CCP1_MODE_SELSECTED == CCP1_CAPTURE_MODE_SELECTED || CCP1_MODE_SELSECTED == CCP1_COMPARE_MODE_SELECTED)
/**
 * 
 * @param ccp1
 * @return 
 */
static std_ReturnType CCP1_CONFIUGER_TIMER_SELECT(const CCP1_t * ccp1)
{
    std_ReturnType RET = E_OK;
    switch(ccp1->CCP1_Select_Timer)
    {
        case Timer1_is_the_capture_compare_clock_source_for_CCPx_modules :
            CLEAR_BIT(T3CON,T3CCP1);
            CLEAR_BIT(T3CON,T3CCP2);
            break;
        case Timer3_is_the_capture_compare_clock_source_for_CCP2_and_Timer1_is_the_capture_compare_clock_source_for_CCP1:
            SET_BIT(T3CON,T3CCP1);
            CLEAR_BIT(T3CON,T3CCP2);
            break;
        case Timer3_is_the_capture_compare_clock_source_for_the_CCPx_modules :
            SET_BIT(T3CON,T3CCP1);
            SET_BIT(T3CON,T3CCP2);
            break;
        default :
            RET = E_NOT_OK;
    }
}
#endif
/**
 * 
 * @param special_mode
 */
static void CCP1_SET_SPECIAL_MODE(CCPx_Module_Sepecial_Mode_Select special_mode)
{
    CCP1CON &= 0xF0;
    CCP1CON |= special_mode;
}
/**
 * 
 * @param ccp1
 * @return 
 */
static std_ReturnType CCP1_SELECT_MODE(const CCP1_t * ccp1)
{
    std_ReturnType RET = E_OK;
    if((ccp1->CCP1_Mode) == CCP1_CAPTURE_MODE)
    {
        #if CCP1_MODE_SELSECTED == CCP1_CAPTURE_MODE_SELECTED
        switch(ccp1->CCP1_Sepecial_Mode)
        {
            case Capture_Compare_PWM_disabled_resets_CCPx_module:
                CCP1_SET_SPECIAL_MODE(Capture_Compare_PWM_disabled_resets_CCPx_module);
                break;
            case Capture_mode_every_falling_edge:
                CCP1_SET_SPECIAL_MODE(Capture_mode_every_falling_edge);
                break;
            case Capture_mode_every_rising_edge:
                CCP1_SET_SPECIAL_MODE(Capture_mode_every_rising_edge);
                break;
            case Capture_mode_every_4th_rising_edge:
                CCP1_SET_SPECIAL_MODE(Capture_mode_every_4th_rising_edge);
                break;
            case Capture_mode_every_16th_rising_edge:
                CCP1_SET_SPECIAL_MODE(Capture_mode_every_16th_rising_edge);
                break;
            default: RET = E_NOT_OK ;
        }
        RET = CCP1_CONFIUGER_TIMER_SELECT(ccp1);
        #else
        RET = E_NOT_OK;
        #endif
    }
    else if ((ccp1->CCP1_Mode) == CCP1_COMPARE_MODE)
    {
        #if CCP1_MODE_SELSECTED == CCP1_COMPARE_MODE_SELECTED
        switch(ccp1->CCP1_Sepecial_Mode)
        {
            case Capture_Compare_PWM_disabled_resets_CCPx_module:
                CCP1_SET_SPECIAL_MODE(Capture_Compare_PWM_disabled_resets_CCPx_module);
                break;
            case Compare_mode_toggle_output_on_match_CCPxIF_bit_is_set:
                CCP1_SET_SPECIAL_MODE(Compare_mode_toggle_output_on_match_CCPxIF_bit_is_set);
                break;
            case Compare_mode_initialize_CCPx_pin_low:
                CCP1_SET_SPECIAL_MODE(Compare_mode_initialize_CCPx_pin_low);
                break;
            case Compare_mode_initialize_CCPx_pin_high:
                CCP1_SET_SPECIAL_MODE(Compare_mode_initialize_CCPx_pin_high);
                break;
            case Compare_mode_generate_software_interrupt_on_compare_match:
                CCP1_SET_SPECIAL_MODE(Compare_mode_generate_software_interrupt_on_compare_match);
                break;
            case Compare_mode_trigger_special_event:
                CCP1_SET_SPECIAL_MODE(Compare_mode_trigger_special_event);
                break;
            default: RET = E_NOT_OK  ;
        }
        RET = CCP1_CONFIUGER_TIMER_SELECT(ccp1);
        #else
        RET = E_NOT_OK;
        #endif
    }
    else if ((ccp1->CCP1_Mode) == CCP1_PWM_MODE)
    {
        #if CCP1_MODE_SELSECTED == CCP1_PWM_MODE_SELECTED
        switch(ccp1->CCP1_Sepecial_Mode)
        {
            case Capture_Compare_PWM_disabled_resets_CCPx_module :
                CCP1_SET_SPECIAL_MODE(Capture_Compare_PWM_disabled_resets_CCPx_module);
                break;
            case PWM_mode :
                CCP1_SET_SPECIAL_MODE(PWM_mode);
                break;
            default: RET = E_NOT_OK  ;
        }
        /* Determine The Total Period of Time (PWM)*/
        PR2 = (uint8)( ( (_XTAL_FREQ) /( (ccp1->PWM_Frequency) * 4.0 * (ccp1->PostscaleValue) * (ccp1->PrescalerValue) ) ) -1 );
        #else
        RET = E_NOT_OK;
        #endif
    }
   
    else
    {
        asm("NOP");
    }
    return (RET);
}
/*_____________________________________________________________________________*/
/*                         Section : APIs Definitions                          */
/*_____________________________________________________________________________*/
/**
 * 
 * @param ccp1
 * @return 
 */
std_ReturnType CCP1_INITIALIZE(const CCP1_t * ccp1)
{
    std_ReturnType RET = E_OK;
    if(ccp1 == NULL)
    {
        RET = E_NOT_OK;
    }
    else
    {
        /*Disable The CCP1 Module*/
        CCP1_SET_SPECIAL_MODE(Capture_Compare_PWM_disabled_resets_CCPx_module);
        /*Select The Mode Of CCP1*/
        RET = CCP1_SELECT_MODE(ccp1);
        /*Configure CCP1 Pin Direction According to The Mode*/
        RET = GPIO_PIN_DIRECTION_INTIALIZE(&(ccp1->CCP1_Pin));
        /*_____________________________________________________________________________*/
        /*CCP1 Interrupt Configurations*/
        /*_____________________________________________________________________________*/
        #if  CCP1_INTERRUPT_FEATURE == INTERRUPT_ENABLE
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERAL_INTERRUPT_ENABLE();
        CCP1_INTERRUPT_ENABLE();
        CCP1_CLEAR_INTERRUPT_FLAG();
        CCP1_INTERRUPT_HANDLER_TASK = (ccp1->CCP1_Interrupt_Handler);
        /*_____________________________________________________________________________*/
        #if INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE
        INTERRUPT_PRORITY_LEVELS_ENABLE();
        if((ccp1->CCP1_Interrupt_Priority) == INTERRUPT_HIGH_PRIORITY)
        {
            CCP1_SET_INTERRUPT_HIGH_PRIORITY();
        }
        else if ((ccp1->CCP1_Interrupt_Priority) == INTERRUPT_LOW_PRIORITY)
        {
            CCP1_SET_INTERRUPT_LOW_PRIORITY();
        }
        #endif
        /*_____________________________________________________________________________*/
        #endif
        /*_____________________________________________________________________________*/
    }
    return (RET);
}
/**
 * 
 * @param ccp1
 * @return 
 */
std_ReturnType CCP1_DEINITIALIZE(const CCP1_t * ccp1)
{
    std_ReturnType RET = E_OK;
    if(ccp1 == NULL)
    {
        RET = E_NOT_OK;
    }
    else
    {
        /*Disable The CCP1 Module*/
        CCP1_SET_SPECIAL_MODE(Capture_Compare_PWM_disabled_resets_CCPx_module);
        #if  CCP1_INTERRUPT_FEATURE == INTERRUPT_ENABLE
        CCP1_INTERRUPT_DISABLE();
        #endif
    }
    return (RET);
}
/*_____________________________________________________________________________*/
#if CCP1_MODE_SELSECTED == CCP1_CAPTURE_MODE_SELECTED
/**
 * 
 * @param Capture_Status
 * @return 
 */
std_ReturnType CCP1_CAPTURE_MODE_IS_DATA_DONE(uint8 * Capture_Status)
{
    std_ReturnType RET = E_OK;
    if(Capture_Status == NULL)
    {
        RET = E_NOT_OK;
    }
    else
    {
        if((READ_BIT(PIR1,CCP1IF)) == INTERRUPT_OCCURED)
        {
           *Capture_Status = CCP1_CAPTURE_MODE_READY;
           #if  CCP1_INTERRUPT_FEATURE == INTERRUPT_ENABLE
           CCP1_CLEAR_INTERRUPT_FLAG();
           #endif
        }
        else
        {
            *Capture_Status = CCP1_CAPTURE_MODE_NOT_READY;
        }
    }
    return (RET);
}
/**
 * 
 * @param Capture_Value
 * @return 
 */
std_ReturnType CCP1_CAPTURE_MODE_READ_VALUE(uint16 * Capture_Value)
{
    std_ReturnType RET = E_OK;
    CCP1_PERIOD_REG_t CAPTURE_TEMP_VALUE = {.ccpr1_low = 0 , .ccpr1_high = 0};
    if(Capture_Value == NULL)
    {
        RET = E_NOT_OK;
    }
    else
    {
        CAPTURE_TEMP_VALUE.ccpr1_low = CCPR1L;
        CAPTURE_TEMP_VALUE.ccpr1_high = CCPR1H;
        *Capture_Value = CAPTURE_TEMP_VALUE.ccpr1_16bit;
    }
    return (RET);
}
#endif
/*_____________________________________________________________________________*/
#if CCP1_MODE_SELSECTED == CCP1_COMPARE_MODE_SELECTED
/**
 * 
 * @param Compare_Status
 * @return 
 */
std_ReturnType CCP1_COMPARE_MODE_DATA_IS_DONE(uint8 * Compare_Status)
{
    std_ReturnType RET = E_OK;
    if(Compare_Status == NULL)
    {
        RET = E_NOT_OK;
    }
    else
    {
        if((READ_BIT(PIR1,CCP1IF)) == INTERRUPT_OCCURED)
        {
           *Compare_Status = CCP1_COMPARE_MODE_READY;
           CCP1_CLEAR_INTERRUPT_FLAG();
        }
        else
        {
            *Compare_Status = CCP1_COMPARE_MODE_NOT_READY;
        }
    }
    return (RET);
}
/**
 * 
 * @param Compare_Value
 * @return 
 */
std_ReturnType CCP1_COMPARE_MODE_WRITE_VALUE(uint16 Compare_Value)
{
    std_ReturnType RET = E_OK;
    CCP1_PERIOD_REG_t CAPTURE_TEMP_VALUE = {.ccpr1_low = 0 , .ccpr1_high = 0};
    CAPTURE_TEMP_VALUE.ccpr1_16bit = Compare_Value;
    CCPR1L = CAPTURE_TEMP_VALUE.ccpr1_low;
    CCPR1H = CAPTURE_TEMP_VALUE.ccpr1_high;
    return (RET);
}
#endif
/*_____________________________________________________________________________*/
#if CCP1_MODE_SELSECTED == CCP1_PWM_MODE_SELECTED
/**
 * 
 * @param duty_cycle
 * @return 
 */
std_ReturnType CCP1_PWM_MODE_SET_DUTY_CYCLE(uint8 duty_cycle)
{
    std_ReturnType RET = E_NOT_OK;
    uint16 DUTY_TEMB = 0 ;
    DUTY_TEMB = (uint16)(((PR2+1)*duty_cycle*4)/100.0);
    CCP1CON &= 0xCF;
    CCP1CON |= ((DUTY_TEMB & 0x03)<<4);
    CCPR1L = (uint8)(DUTY_TEMB>>2);
    return (RET);
}
/**
 * 
 * @return 
 */
std_ReturnType CCP1_PWM_MODE_START(void)
{
    std_ReturnType RET = E_NOT_OK;
    CCP1_SET_SPECIAL_MODE(PWM_mode);
    return (RET);
}
/**
 * 
 * @return 
 */
std_ReturnType CCP1_PWM_MODE_STOP(void)
{
    std_ReturnType RET = E_NOT_OK;
    CCP1_SET_SPECIAL_MODE(Capture_Compare_PWM_disabled_resets_CCPx_module);
    return (RET);
}
#endif
/*____________________________________________________________________________*/
/*___________________________CCP1_ISR_Function________________________________*/
/*____________________________________________________________________________*/
#if  CCP1_INTERRUPT_FEATURE == INTERRUPT_ENABLE
void CCP1_ISR(void)
{
    CCP1_CLEAR_INTERRUPT_FLAG();
    if(CCP1_INTERRUPT_HANDLER_TASK)
    {
        CCP1_INTERRUPT_HANDLER_TASK();
    }
}
#endif