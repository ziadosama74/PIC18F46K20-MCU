/* 
 * File:   ADC_PROGRAM.C
 * Author: Ziad Osama
 *
 * Created on November 4, 2024, 8:59 PM
 */
/*_____________________________________________________________________________*/
/*                         Section : Includes                                  */
/*_____________________________________________________________________________*/
#include "ADC_INTERFACE.h"
/*_____________________________________________________________________________*/
/*                         Section : Global Pointer To Functions               */
/*_____________________________________________________________________________*/
#if  ADC_INTERRUPT_FEATURE == INTERRUPT_ENABLE
static void (*ADC_INTERRUPT_HANDELER)(void) = NULL ;
#endif
/*_____________________________________________________________________________*/
/*                         Section : Helper Functions                          */
/*_____________________________________________________________________________*/
/**
 * 
 * @param adc
 */
static void CONFIGURE_ANALOG_PIN_AS_INPUT(AnalogChannelSelect channel)
{
    switch(channel)
    {
        case ADC_CHANNEL_AN0 :SET_BIT(TRISA,RA0);break;
        case ADC_CHANNEL_AN1 :SET_BIT(TRISA,RA1);break;
        case ADC_CHANNEL_AN2 :SET_BIT(TRISA,RA2);break;
        case ADC_CHANNEL_AN3 :SET_BIT(TRISA,RA3);break;
        case ADC_CHANNEL_AN4 :SET_BIT(TRISA,RA5);break;
        case ADC_CHANNEL_AN5 :SET_BIT(TRISE,RE0);break;
        case ADC_CHANNEL_AN6 :SET_BIT(TRISE,RE1);break;
        case ADC_CHANNEL_AN7 :SET_BIT(TRISE,RE2);break;
        case ADC_CHANNEL_AN8 :SET_BIT(TRISB,RB2);break;
        case ADC_CHANNEL_AN9 :SET_BIT(TRISB,RB3);break;
        case ADC_CHANNEL_AN10:SET_BIT(TRISB,RB1);break;
        case ADC_CHANNEL_AN11:SET_BIT(TRISB,RB4);break;
        case ADC_CHANNEL_AN12:SET_BIT(TRISB,RB0);break;
    }
}
/**
 * 
 * @param adc
 */
static void CONFIGURE_ACQUISITION_TIME_ADC(const ADC_CONFIG_t * adc)
{
    ADCON2 &= 0xC7;
    ADCON2 |= ((adc->AcquisitionTime)<<3);
}
/**
 * 
 * @param adc
 */
static void CONFIGURE_THE_CHANNEL_ADC(AnalogChannelSelect channel)
{
    ADCON0 &= 0xC3;
    ADCON0 |= ((channel)<<2);
}
/**
 * 
 * @param adc
 */
static void CONFIGURE_CONVERSION_CLOCK_ADC(const ADC_CONFIG_t * adc)
{
    ADCON2 &= 0xF8;
    ADCON2 |= (adc->ConversionClock);
}
/**
 * 
 * @param adc
 */
static void CONFIGURE_THE_VREF_ADC(const ADC_CONFIG_t * adc)
{
    if((adc->Vref_STATUS) == Vref_EXTERNAL)
    {
        ADC_Vref_IS_EXTERNAL_AT_AN3_AND_AN2();
    }
    else if ((adc->Vref_STATUS) == Vref_INTERNAL)
    {
        ADC_Vref_IS_VDD_VSS();
    }
}
/**
 * 
 * @param adc
 */
static void CONFIGURE_THE_RESULT_FORMATE_ADC(const ADC_CONFIG_t * adc)
{
    if((adc->Result_Format) == ADC_RIGHT_FORMATE)
    {
        ADC_READ_RESULT_RIGHT_JUSTIFIED();
    }
    else if((adc->Result_Format) == ADC_LEFT_FORMATE)
    {
        ADC_READ_RESULT_LEFT_JUSTIFIED();
    }
}
/*_____________________________________________________________________________*/
/*                         Section : APIs Definitions                          */
/*_____________________________________________________________________________*/
/**
 * 
 * @param adc
 * @return 
 */
std_ReturnType ADC_INTITALIZE(const ADC_CONFIG_t * adc)
{
    std_ReturnType RET = E_OK ;
    if(NULL == adc)
    {
        RET = E_NOT_OK ;
    }
    else
    {
        /* ADC Disable*/
        ADC_CONVERT_MODULE_DISABLE();
        /* Select The Acquisition Time */
        CONFIGURE_ACQUISITION_TIME_ADC(adc);
        /* Select The Conversion Clock */
        CONFIGURE_CONVERSION_CLOCK_ADC(adc);
        /* Configure The Vref          */
        CONFIGURE_THE_VREF_ADC(adc);
        /* Select The Default Channel*/
        CONFIGURE_THE_CHANNEL_ADC(adc->ADC_Channel);
        /* Configure the pin is input  */
        CONFIGURE_ANALOG_PIN_AS_INPUT(adc->ADC_Channel);
        /* Configure The ADC Interrupt */
        #if  ADC_INTERRUPT_FEATURE == INTERRUPT_ENABLE
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERAL_INTERRUPT_ENABLE();
        ADC_MODULE_INTERRUPT_ENABLE();
        ADC_MODULE_CLEAR_FLAG();
        #if INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE
        INTERRUPT_PRORITY_LEVELS_ENABLE();
        if((adc->ADC_INERRUPT_PRIORITY) == INTERRUPT_LOW_PRIORITY)
        {
            ADC_MODULE_INTERRUPT_SET_LOW_PRIORITY(); 
        }
        else if((adc->ADC_INERRUPT_PRIORITY) == INTERRUPT_HIGH_PRIORITY)
        {
            ADC_MODULE_INTERRUPT_SET_HIGH_PRIORITY(); 
        }
        else
        {
            asm("NOP");
        }
        #endif
        ADC_INTERRUPT_HANDELER = (adc->ADC_INTERRUPT_HANDER);
        #endif
        /* Select The Result Format    */
        CONFIGURE_THE_RESULT_FORMATE_ADC(adc);
        /* ADC Enable  */
        ADC_CONVERT_MODULE_ENABLE();
    }
    return (RET);
}
/**
 * 
 * @param adc
 * @return 
 */
std_ReturnType ADC_DEINTITALIZE(const ADC_CONFIG_t * adc)
{
    std_ReturnType RET = E_OK ;
    if(NULL == adc)
    {
        RET = E_NOT_OK ;
    }
    else
    {
       /* ADC Disable*/
        ADC_CONVERT_MODULE_DISABLE();
        /* Configure The ADC Interrupt */
        #if  ADC_INTERRUPT_FEATURE == INTERRUPT_ENABLE
        ADC_MODULE_INTERRUPT_DISABLE();
        #endif
    }
    return (RET);
}
/**
 * 
 * @param adc
 * @param channel
 * @return 
 */
std_ReturnType ADC_SELECT_CHANNEL(const ADC_CONFIG_t * adc,AnalogChannelSelect channel)
{
    std_ReturnType RET = E_OK ;
    if(NULL == adc)
    {
        RET = E_NOT_OK ;
    }
    else
    {
        CONFIGURE_THE_CHANNEL_ADC(channel);
        CONFIGURE_ANALOG_PIN_AS_INPUT(adc);
        
    }
    return (RET);
}
/**
 * 
 * @param adc
 * @param Result
 * @return 
 */
/**
 * 
 * @param adc
 * @param Result
 * @return 
 */
std_ReturnType ADC_GET_RESULT(const ADC_CONFIG_t * adc,adc_result * Result)
{
    std_ReturnType RET = E_OK ;
    if((NULL == adc) || (NULL == Result))
    {
        RET = E_NOT_OK ;
    }
    else
    {
        if((adc->Result_Format == ADC_RIGHT_FORMATE))
        {
            *Result = (adc_result)((ADRESH<<8)+ADRESL);
        }
        else if (adc->Result_Format == ADC_LEFT_FORMATE)
        {
           *Result = (adc_result)(((ADRESH<<8)+ADRESL)<<6);
        }
        else
        {
           *Result = (adc_result)((ADRESH<<8)+ADRESL);
        }
    }
    return (RET);
}
/**
 * 
 * @param adc
 * @param Result
 * @param channel
 * @return 
 */
std_ReturnType ADC_GET_RESULT_FORM_CHANNEL(const ADC_CONFIG_t * adc,adc_result * Result,AnalogChannelSelect channel)
{
    std_ReturnType RET = E_OK ;
    if((NULL == adc) || (NULL == Result))
    {
        RET = E_NOT_OK ;
    }
    else
    {
        /*Select The Channel ADC       */
        CONFIGURE_THE_CHANNEL_ADC(channel);
        /* Configure the pin is input  */
        CONFIGURE_ANALOG_PIN_AS_INPUT(channel);
        /* Start Conversion            */
        ADC_START_ADC_CONVERSION();
        /*Wait Done Conversion         */
        while(ADC_GET_ADC_CONVERSION_STATUS())
        {
            asm("NOP");
        }
        /*Read The Result              */
         RET = ADC_GET_RESULT(adc,Result);
    }
    return (RET);
}
/**
 * 
 * @param adc
 * @param Result
 * @param channel
 * @return 
 */
std_ReturnType ADC_START_CONVERSION_INTERRUPT(const ADC_CONFIG_t * adc,AnalogChannelSelect channel)
{
    std_ReturnType RET = E_OK ;
    if(NULL == adc)
    {
        RET = E_NOT_OK ;
    }
    else
    {
        /*Select The Channel ADC       */
        CONFIGURE_THE_CHANNEL_ADC(channel);
        /* Configure the pin is input  */
        CONFIGURE_ANALOG_PIN_AS_INPUT(channel);
        /* Start Conversion            */
        ADC_START_ADC_CONVERSION();
    }
    return (RET);
}
/*_____________________________________________________________________________*/
/*                         Section : ISR Definitions                           */
/*_____________________________________________________________________________*/
#if  ADC_INTERRUPT_FEATURE == INTERRUPT_ENABLE
void ADC_ISR(void)
{
    ADC_MODULE_CLEAR_FLAG();
    if(ADC_INTERRUPT_HANDELER)
    {
        ADC_INTERRUPT_HANDELER();
    }
}
#endif