/* 
 * File:   CCP2_INTERFACE.h
 * Author: ziad osama
 *
 * Created on November 23, 2024, 1:25 AM
 */

#ifndef CCP2_INTERFACE_H
#define	CCP2_INTERFACE_H
/*_____________________________________________________________________________*/
/*                         Section : Includes                                  */
/*_____________________________________________________________________________*/
#include "../CCP_REGISTER.h"
#include "../CPP_CONFIGURATION.h"
#include "../../INTERRUPT/MCAL_INTERNAL_INTERRUPT.h"
#include "../../GPIO/GPIO_Interface.h"
#include "../../TIMERS/TIMER0/TIMER0_INTERFACE.h"
#include "../../TIMERS/TIMER1/TIMER1_INTERFACE.h"
#include "../../TIMERS/TIMER2/TIMER2_INTERFACE.h"
#include "../../TIMERS/TIMER3/TIMER3_INTERFACE.h"
/*_____________________________________________________________________________*/
/*                         Section : Macro Definitions                         */
/*_____________________________________________________________________________*/
#define          CCP2_CAPTURE_MODE_NOT_READY                       ((uint8)0)
#define          CCP2_CAPTURE_MODE_READY                           ((uint8)1)
/*_____________________________________________________________________________*/
#define          CCP2_COMPARE_MODE_NOT_READY                       ((uint8)0)
#define          CCP2_COMPARE_MODE_READY                           ((uint8)1)
/*_____________________________________________________________________________*/
#define          CCP2_Timer2_Prescaler_is_1                        ((uint8)1)
#define          CCP2_Timer2_Prescaler_is_4                        ((uint8)4)
#define          CCP2_Timer2_Prescaler_is_16                       ((uint8)16)
/*_____________________________________________________________________________*/
#define          CCP2_Timer2_1_1_Postscale                         ((uint8)1)
#define          CCP2_Timer2_1_2_Postscale                         ((uint8)2)
#define          CCP2_Timer2_1_3_Postscale                         ((uint8)3)
#define          CCP2_Timer2_1_4_Postscale                         ((uint8)4)
#define          CCP2_Timer2_1_5_Postscale                         ((uint8)5)
#define          CCP2_Timer2_1_6_Postscale                         ((uint8)6)
#define          CCP2_Timer2_1_7_Postscale                         ((uint8)7)
#define          CCP2_Timer2_1_8_Postscale                         ((uint8)8)
#define          CCP2_Timer2_1_9_Postscale                         ((uint8)9)
#define          CCP2_Timer2_1_10_Postscale                        ((uint8)10)
#define          CCP2_Timer2_1_11_Postscale                        ((uint8)11)
#define          CCP2_Timer2_1_12_Postscale                        ((uint8)12)
#define          CCP2_Timer2_1_13_Postscale                        ((uint8)13)
#define          CCP2_Timer2_1_14_Postscale                        ((uint8)14)
#define          CCP2_Timer2_1_15_Postscale                        ((uint8)15)
#define          CCP2_Timer2_1_16_Postscale                        ((uint8)16)
/*_____________________________________________________________________________*/
/*                         Section : Data Types Declaration                    */
/*_____________________________________________________________________________*/
typedef enum 
{
    CCP2_CAPTURE_MODE = 0,
    CCP2_COMPARE_MODE ,
    CCP2_PWM_MODE ,
            
}CCP2_Mode;
/*_____________________________________________________________________________*/
typedef union 
{
    struct
    {
        uint8 ccpr2_low;
        uint8 ccpr2_high;
    };
    struct
    {
        uint16 ccpr2_16bit;
    };
}CCP2_PERIOD_REG_t;

/*_____________________________________________________________________________*/
typedef struct 
{
    /*_________________________________________________________________________*/
    #if  CCP2_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    void (*CCP2_Interrupt_Handler)(void);
    INTERRUPT_PRIORITY CCP2_Interrupt_Priority;
    #endif
    /*_________________________________________________________________________*/
    CCP2_Mode CCP2_Mode;
    CCPx_Module_Sepecial_Mode_Select CCP2_Sepecial_Mode;
    /*_________________________________________________________________________*/
    #if CCP2_MODE_SELSECTED == CCP2_PWM_MODE_SELECTED
    uint32 PWM_Frequency;
    Timer2_Postscale_Value PostscaleValue ;
    Timer2_Prescaler_Value PrescalerValue ;
    #endif
    /*_________________________________________________________________________*/
    #if (CCP2_MODE_SELSECTED == CCP2_CAPTURE_MODE_SELECTED || CCP2_MODE_SELSECTED == CCP2_COMPARE_MODE_SELECTED)
    CCPx_Select_Timer_at_Capture_and_Compare_Mode CCP2_Select_Timer;
    #endif
    /*_________________________________________________________________________*/
    Pin_Config_t CCP2_Pin;
    
}CCP2_t;
/*_____________________________________________________________________________*/
/*                         Section : APIs Declaration                          */
/*_____________________________________________________________________________*/
std_ReturnType CCP2_INITIALIZE(const CCP2_t * ccp2);
std_ReturnType CCP2_DEINITIALIZE(const CCP2_t * ccp2);
/*_____________________________________________________________________________*/
#if CCP2_MODE_SELSECTED == CCP2_CAPTURE_MODE_SELECTED
std_ReturnType CCP2_CAPTURE_MODE_IS_DATA_DONE(uint8 * Capture_Status);
std_ReturnType CCP2_CAPTURE_MODE_READ_VALUE(uint16 * Capture_Value);
#endif
/*_____________________________________________________________________________*/
#if CCP2_MODE_SELSECTED == CCP2_COMPARE_MODE_SELECTED
std_ReturnType CCP2_COMPARE_MODE_DATA_IS_DONE(uint8 * Compare_Status);
std_ReturnType CCP2_COMPARE_MODE_WRITE_VALUE(uint16 Compare_Value);
#endif
/*_____________________________________________________________________________*/
#if CCP2_MODE_SELSECTED == CCP2_PWM_MODE_SELECTED
std_ReturnType CCP2_PWM_MODE_SET_DUTY_CYCLE(uint8 duty_cycle);
std_ReturnType CCP2_PWM_MODE_START(void);
std_ReturnType CCP2_PWM_MODE_STOP(void);
#endif
/*_____________________________________________________________________________*/
#endif	/* CCP2_INTERFACE_H */

