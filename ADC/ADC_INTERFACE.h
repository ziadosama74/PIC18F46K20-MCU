/* 
 * File:   ADC_INTERFACE.h
 * Author: ziad osama
 *
 * Created on November 4, 2024, 8:59 PM
 */

#ifndef ADC_INTERFACE_H
#define	ADC_INTERFACE_H
/*_____________________________________________________________________________*/
/*                         Section : Includes                                  */
/*_____________________________________________________________________________*/
#include "../../MCAL_Layer/GPIO/GPIO_Interface.h"
#include "../../MCAL_Layer/INTERRUPT/MCAL_INTERNAL_INTERRUPT.h"
#include "ADC_REGISTER.h"
#include "ADC_CONFIG.h"
/*_____________________________________________________________________________*/
/*                         Section : Macro Definitions                         */
/*_____________________________________________________________________________*/
#define     ADC_AN0_ANALOG_FUNCTIONALITY                            0x0E
#define     ADC_FROM_AN0__TO__AN1_ANALOG_FUNCTIONALITY              0x0D
#define     ADC_FROM_AN0__TO__AN2_ANALOG_FUNCTIONALITY              0x0C
#define     ADC_FROM_AN0__TO__AN3_ANALOG_FUNCTIONALITY              0x0B
#define     ADC_FROM_AN0__TO__AN4_ANALOG_FUNCTIONALITY              0x0A
#define     ADC_FROM_AN0__TO__AN5_ANALOG_FUNCTIONALITY              0x09
#define     ADC_FROM_AN0__TO__AN6_ANALOG_FUNCTIONALITY              0x08
#define     ADC_FROM_AN0__TO__AN7_ANALOG_FUNCTIONALITY              0x07
#define     ADC_FROM_AN0__TO__AN8_ANALOG_FUNCTIONALITY              0x06
#define     ADC_FROM_AN0__TO__AN9_ANALOG_FUNCTIONALITY              0x05
#define     ADC_FROM_AN0__TO__AN10_ANALOG_FUNCTIONALITY             0x04
#define     ADC_FROM_AN0__TO__AN11_ANALOG_FUNCTIONALITY             0x03
#define     ADC_FROM_AN0__TO__AN12_ANALOG_FUNCTIONALITY             0x02
#define     ADC_ALL_CHANNELS_ANALOG_FUNCTIONALITY                   0x01
#define     ADC_ALL_CHANNELS_DIGITAL_FUNCTIONALITY                  0x0F

#define    ADC_RIGHT_FORMATE                                         1
#define    ADC_LEFT_FORMATE                                          0

#define    Vref_INTERNAL                                             1
#define    Vref_EXTERNAL                                             0

#define    ADC_CONVERSION_COMPELETEED                                1
#define    ADC_CONVERSION__NOT_COMPELETEED                           0

#define        RA0                                                   0  
#define        RA1                                                   1  
#define        RA2                                                   2  
#define        RA3                                                   3 
#define        RA5                                                   5 

#define        RB0                                                   0
#define        RB1                                                   1 
#define        RB2                                                   2 
#define        RB3                                                   3
#define        RB4                                                   4 

#define        RE0                                                   0 
#define        RE1                                                   1 
#define        RE2                                                   2 
/*_____________________________________________________________________________*/
/*                         Section : Macro Functions                           */
/*_____________________________________________________________________________*/
#define     ADC_CONVERT_MODULE_ENABLE()             (SET_BIT(ADCON0,ADON))
#define     ADC_CONVERT_MODULE_DISABLE()            (CLEAR_BIT(ADCON0,ADON))
#define     ADC_GET_ADC_CONVERSION_STATUS()         (READ_BIT(ADCON0,GO_DONE))
#define     ADC_START_ADC_CONVERSION()              (SET_BIT(ADCON0,GO_DONE))
#define     ADC_Vref_IS_VDD_VSS()                  do                           \
                                                    {                           \
                                                      (CLEAR_BIT(ADCON1,VCFG0));\
                                                      (CLEAR_BIT(ADCON1,VCFG1));\
                                                    }                           \
                                                    while(FALSE)

#define     ADC_Vref_IS_EXTERNAL_AT_AN3_AND_AN2() do                            \
                                                    {                           \
                                                      (SET_BIT(ADCON1,VCFG0));  \
                                                      (SET_BIT(ADCON1,VCFG1));  \
                                                    }                           \
                                                    while(FALSE)
#define     ADC_READ_RESULT_RIGHT_JUSTIFIED()       (SET_BIT(ADCON2,ADFM))
#define     ADC_READ_RESULT_LEFT_JUSTIFIED()        (CLEAR_BIT(ADCON2,ADFM))
/*_____________________________________________________________________________*/
/*                         Section : Data Types Declaration                    */
/*_____________________________________________________________________________*/
typedef enum
{
    ADC_CHANNEL_AN0 = 0 ,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12,
}AnalogChannelSelect;

typedef enum
{
    FOSC_2 = 0 ,
    FOSC_8,
    FOSC_32,
    F_Clock_Derived_From_ADC_RC_Oscillator,
    FOSC_4,
    FOSC_16,
    FOSC_64,
}ADC_ConversionClockSelect;

typedef enum
{
    _0TAD = 0 ,
    _2TAD,
    _4TAD,
    _6TAD,
    _8TAD,
    _12TAD,
    _16TAD,
    _20TAD,
}ADC_AcquisitionTimeSelect;

typedef struct 
{
#if  ADC_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    void                    (*ADC_INTERRUPT_HANDER)(void);
    INTERRUPT_PRIORITY       ADC_INERRUPT_PRIORITY ;
#endif
    ADC_AcquisitionTimeSelect AcquisitionTime ;
    ADC_ConversionClockSelect ConversionClock ;
    AnalogChannelSelect       ADC_Channel ;
    uint8                     Vref_STATUS   : 1 ;
    uint8                     Result_Format : 1 ;
    uint8                     ADC_RESERVED  : 6 ;  /*to complete one byte*/  
}ADC_CONFIG_t;
/*_____________________________________________________________________________*/
/*                         Section : APIs Declaration                          */
/*_____________________________________________________________________________*/
std_ReturnType ADC_INTITALIZE(const ADC_CONFIG_t * adc);
std_ReturnType ADC_DEINTITALIZE(const ADC_CONFIG_t * adc);
std_ReturnType ADC_SELECT_CHANNEL(const ADC_CONFIG_t * adc,AnalogChannelSelect channel);
std_ReturnType ADC_GET_RESULT(const ADC_CONFIG_t * adc,adc_result * Result);
std_ReturnType ADC_GET_RESULT_FORM_CHANNEL(const ADC_CONFIG_t * adc,adc_result * Result,AnalogChannelSelect channel);

#if  ADC_INTERRUPT_FEATURE == INTERRUPT_ENABLE
std_ReturnType ADC_START_CONVERSION_INTERRUPT(const ADC_CONFIG_t * adc,AnalogChannelSelect channel);
#endif

#endif	/* ADC_INTERFACE_H */

