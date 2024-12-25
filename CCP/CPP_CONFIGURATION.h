/* 
 * File:   CPP_CONFIGURATION.h
 * Author: ziad osama
 *
 * Created on November 21, 2024, 10:32 PM
 */

#ifndef CPP_CONFIGURATION_H
#define	CPP_CONFIGURATION_H
/*_____________________________________________________________________________*/
/*                         Section : Macro Definitions                         */
/*_____________________________________________________________________________*/
#define        CCP1_CAPTURE_MODE_SELECTED                  0
#define        CCP1_COMPARE_MODE_SELECTED                  1
#define        CCP1_PWM_MODE_SELECTED                      2
#define        CCP2_CAPTURE_MODE_SELECTED                  3
#define        CCP2_COMPARE_MODE_SELECTED                  4
#define        CCP2_PWM_MODE_SELECTED                      5
/*_____________________________________________________________________________*/
#define        CCP1_MODE_SELSECTED              (CCP1_PWM_MODE_SELECTED)
/*_____________________________________________________________________________*/
/*_____________________________________________________________________________*/
#define        CCP2_MODE_SELSECTED              (CCP2_PWM_MODE_SELECTED)
/*_____________________________________________________________________________*/
/*_____________________________________________________________________________*/
/*                         Section : Data Types Declaration                    */
/*_____________________________________________________________________________*/
#if (CCP1_MODE_SELSECTED == CCP1_CAPTURE_MODE_SELECTED ||  CCP2_MODE_SELSECTED == CCP2_CAPTURE_MODE_SELECTED || CCP1_MODE_SELSECTED == CCP1_COMPARE_MODE_SELECTED ||  CCP2_MODE_SELSECTED == CCP2_COMPARE_MODE_SELECTED)
typedef enum 
{
    Timer1_is_the_capture_compare_clock_source_for_CCPx_modules = 0,
    Timer3_is_the_capture_compare_clock_source_for_CCP2_and_Timer1_is_the_capture_compare_clock_source_for_CCP1 ,
    Timer3_is_the_capture_compare_clock_source_for_the_CCPx_modules ,        
}CCPx_Select_Timer_at_Capture_and_Compare_Mode;
#endif
/*_____________________________________________________________________________*/
typedef enum 
{
    
    Capture_Compare_PWM_disabled_resets_CCPx_module = 0,
    Reserved1,
    Compare_mode_toggle_output_on_match_CCPxIF_bit_is_set,
    Reserved2,
    Capture_mode_every_falling_edge,
    Capture_mode_every_rising_edge,
    Capture_mode_every_4th_rising_edge,
    Capture_mode_every_16th_rising_edge,
    Compare_mode_initialize_CCPx_pin_low,
    Compare_mode_initialize_CCPx_pin_high,
    Compare_mode_generate_software_interrupt_on_compare_match,
    Compare_mode_trigger_special_event, /*reset timer; CCPx match starts A/D conversion (CCPxIF bit is set)*/
    PWM_mode
            
}CCPx_Module_Sepecial_Mode_Select;
/*_____________________________________________________________________________*/
#endif	/* CPP_CONFIGURATION_H */

