/* 
 * File:   MCAL_EXTERNAL_INTERRUPT.h
 * Author: ziad osama
 *
 * Created on October 18, 2024, 9:41 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H
/*____________________________________________________________________________*/
/*                         Section : Includes                                 */
/*____________________________________________________________________________*/
#include "MCAL_INTERRUPT_Config.h"
/*____________________________________________________________________________*/
/*                         Section : Macro Declarations                       */
/*____________________________________________________________________________*/
#if   (EXTERNAL_INTERRUPT_FEATURE_INTx == INTERRUPT_ENABLE) 
/*_____________________INT0_EXTERNAL_INTERRUPT________________________________*/

#define     INT0_INTERRUPT_ENABLE()                 (SET_BIT(INTCON,INT0IE))
#define     INT0_INTERRUPT_DISABLE()                (CLEAR_BIT(INTCON,INT0IE))
#define     INT0_INTERRUPT_FLAG_CLEAR()             (CLEAR_BIT(INTCON,INT0IF))
#define     INT0_INTERRUPT_TRIGGER_RISING_EDGE()    (SET_BIT(INTCON2,INTEDG0))
#define     INT0_INTERRUPT_TRIGGER_FALLING_EDGE()   (CLEAR_BIT(INTCON2,INTEDG0))
/*_____________________INT1_EXTERNAL_INTERRUPT________________________________*/

#define     INT1_INTERRUPT_ENABLE()                 (SET_BIT(INTCON3,INT1IE))
#define     INT1_INTERRUPT_DISABLE()                (CLEAR_BIT(INTCON3,INT1IE))
#define     INT1_INTERRUPT_FLAG_CLEAR()             (CLEAR_BIT(INTCON3,INT1IF))
#define     INT1_INTERRUPT_TRIGGER_RISING_EDGE()    (SET_BIT(INTCON2,INTEDG1))
#define     INT1_INTERRUPT_TRIGGER_FALLING_EDGE()   (CLEAR_BIT(INTCON2,INTEDG1))
/*_____________________INT2_EXTERNAL_INTERRUPT________________________________*/

#define     INT2_INTERRUPT_ENABLE()                 (SET_BIT(INTCON3,INT2IE))
#define     INT2_INTERRUPT_DISABLE()                (CLEAR_BIT(INTCON3,INT2IE))
#define     INT2_INTERRUPT_FLAG_CLEAR()             (CLEAR_BIT(INTCON3,INT2IF))
#define     INT2_INTERRUPT_TRIGGER_RISING_EDGE()    (SET_BIT(INTCON2,INTEDG2))
#define     INT2_INTERRUPT_TRIGGER_FALLING_EDGE()   (CLEAR_BIT(INTCON2,INTEDG2))

#if   (INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE)
/*_____________INT1_&_INT2_EXTERNAL_INTERRUPT_SET_PRIORITY____________________*/
#define     INT1_INTERRUPT_SET_HIGH_PRIORITY()      (SET_BIT(INTCON3,INT1IP))
#define     INT1_INTERRUPT_SET_LOW_PRIORITY()       (CLEAR_BIT(INTCON3,INT1IP))
#define     INT2_INTERRUPT_SET_HIGH_PRIORITY()      (SET_BIT(INTCON3,INT2IP))
#define     INT2_INTERRUPT_SET_LOW_PRIORITY()       (CLEAR_BIT(INTCON3,INT2IP))
#endif
#endif
/*____________________________________________________________________________*/
#if   (EXTERNAL_INTERRUPT_FEATURE_ON_CHANGE_KBIx == INTERRUPT_ENABLE)

#define     ON_CHANGE_KBI_INTERRUPT_ENABLE()        (SET_BIT(INTCON,RBIE))
#define     ON_CHANGE_KBI_INTERRUPT_DISABLE()       (CLEAR_BIT(INTCON,RBIE))
#define     ON_CHANGE_KBI_INTERRUPT_FLAG_CLEAR()    (CLEAR_BIT(INTCON,RBIF))


#if   (INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE)
/*_____________ON_CHANGE_KBI_EXTERNAL_INTERRUPT_SET_PRIORITY__________________*/
#define ON_CHANGE_KBI_INTERRUPT_SET_HIGH_PRIORITY() (SET_BIT(INTCON2,RBIP))
#define ON_CHANGE_KBI_INTERRUPT_SET_LOW_PRIORITY()  (CLEAR_BIT(INTCON2,RBIP))
#endif
#endif

/*____________________________________________________________________________*/
/*                         Section : Data Types Declarations                  */
/*____________________________________________________________________________*/
#if   (EXTERNAL_INTERRUPT_FEATURE_INTx == INTERRUPT_ENABLE) 
typedef enum 
{
    INTx_FALLING_EDGE = 0,
    INTx_RAISING_EDGE
}INTERRUPT_INTx_EDGE;
typedef enum 
{
    INT0_SOURCE = 0,
    INT1_SOURCE ,
    INT2_SOURCE 
}INTERRUPT_INTx_SOURCE;
typedef struct           /* INTx External Interrupt Structure     */
{
    void (* EXTTERNAL_INTERRUPT_HANDELER_TASK)(void);
    Pin_Config_t INTx_PIN ;
    INTERRUPT_INTx_EDGE EDGE ;
    INTERRUPT_INTx_SOURCE SOURCE ;
    INTERRUPT_PRIORITY  PRIORITY ;
}INTx_t;
#endif

#if   (EXTERNAL_INTERRUPT_FEATURE_ON_CHANGE_KBIx == INTERRUPT_ENABLE)
#define      KBI_4                                  4
#define      KBI_5                                  5
#define      KBI_6                                  6
#define      KBI_7                                  7
typedef struct          /* On Change External Interrupt Structure */
{
    Pin_Config_t KBIx_PIN ;  /*4-7 PINS*/
    INTERRUPT_PRIORITY  PRIORITY ;
    void (* EXTTERNAL_INTERRUPT_HANDELER_TASK_CHANGE_TO_HIGH)(void);
    void (* EXTTERNAL_INTERRUPT_HANDELER_TASK_CHANGE_TO_LOW)(void);
}KBIx_t;
#endif
/*____________________________________________________________________________*/
/*                         Section : APIs Declarations                        */
/*____________________________________________________________________________*/
#if   (EXTERNAL_INTERRUPT_FEATURE_INTx == INTERRUPT_ENABLE) 
std_ReturnType INTx_INTERRUPT_INITIALIZATION(const INTx_t * intx );
std_ReturnType INTx_INTERRUPT_DEINITIALIZATION(const INTx_t * intx );
#endif

#if   (EXTERNAL_INTERRUPT_FEATURE_ON_CHANGE_KBIx == INTERRUPT_ENABLE)
std_ReturnType KBIx_INTERRUPT_INITIALIZATION(const KBIx_t * kibx );
std_ReturnType KBIx_INTERRUPT_DEINITIALIZATION(const KBIx_t * kibx );
#endif

#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

