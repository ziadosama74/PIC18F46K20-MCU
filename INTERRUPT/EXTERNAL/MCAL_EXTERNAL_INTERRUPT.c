
/* 
 * File:   MCAL_EXTERNAL_INTERRUPT.C
 * Author: ziad osama
 *
 * Created on October 18, 2024, 9:42 PM
 */
/*____________________________________________________________________________*/
/*                         Section : Includes                                 */
/*____________________________________________________________________________*/

#include "MCAL_EXTERNAL_INTERRUPT.h"
/*_____________________________________________________________________________*/
/*                         Section : Global Pointers                           */
/*_____________________________________________________________________________*/
#if   (EXTERNAL_INTERRUPT_FEATURE_INTx == INTERRUPT_ENABLE) 
static void(*INT0_INTERRUPT_ADDRESS_ISR_TASK)(void) = NULL;/*Pointer to Function*/
static void(*INT1_INTERRUPT_ADDRESS_ISR_TASK)(void) = NULL;
static void(*INT2_INTERRUPT_ADDRESS_ISR_TASK)(void) = NULL;
#endif
#if   (EXTERNAL_INTERRUPT_FEATURE_ON_CHANGE_KBIx == INTERRUPT_ENABLE)
static void(*KBI4_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_HIGH)(void) = NULL;
static void(*KBI4_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_LOW)(void) = NULL;

static void(*KBI5_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_HIGH)(void) = NULL;
static void(*KBI5_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_LOW)(void) = NULL;

static void(*KBI6_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_HIGH)(void) = NULL; 
static void(*KBI6_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_LOW)(void) = NULL;

static void(*KBI7_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_HIGH)(void) = NULL; 
static void(*KBI7_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_LOW)(void) = NULL;
#endif
/*____________________________________________________________________________*/
/*                         Section : Call Back Helper Functions Definitions   */
/*____________________________________________________________________________*/
/**
 * 
 * @param pointer_to_function
 * @return 
 */
#if   (EXTERNAL_INTERRUPT_FEATURE_INTx == INTERRUPT_ENABLE) 
static std_ReturnType INT0_INTERRUPT_SET_ISR_TASK(void(*pointer_to_function)(void)) /* COPY THE ADDRESS OF THE FUNCTION AT THE OBJECT AT THE Global Pointers TO FUNCTIONS */
{
    std_ReturnType RET = E_OK ;
    if(NULL == pointer_to_function)
    {
        RET = E_NOT_OK ;
    }
    else
    {
        INT0_INTERRUPT_ADDRESS_ISR_TASK = pointer_to_function ;
    }
    return (RET);
}
#endif
/**
 * 
 * @param pointer_to_function
 * @return 
 */
#if   (EXTERNAL_INTERRUPT_FEATURE_INTx == INTERRUPT_ENABLE) 
static std_ReturnType INT1_INTERRUPT_SET_ISR_TASK(void(*pointer_to_function)(void)) /* COPY THE ADDRESS OF THE FUNCTION AT THE OBJECT AT THE Global Pointers TO FUNCTIONS */
{
    std_ReturnType RET = E_OK ;
    if(NULL == pointer_to_function)
    {
        RET = E_NOT_OK ;
    }
    else
    {
        INT1_INTERRUPT_ADDRESS_ISR_TASK = pointer_to_function ;
    }
    return (RET);
}
#endif
/**
 * 
 * @param pointer_to_function
 * @return 
 */
#if   (EXTERNAL_INTERRUPT_FEATURE_INTx == INTERRUPT_ENABLE) 
static std_ReturnType INT2_INTERRUPT_SET_ISR_TASK(void(*pointer_to_function)(void)) /* COPY THE ADDRESS OF THE FUNCTION AT THE OBJECT AT THE Global Pointers TO FUNCTIONS */
{
    std_ReturnType RET = E_OK ;
    if(NULL == pointer_to_function)
    {
        RET = E_NOT_OK ;
    }
    else
    {
        INT2_INTERRUPT_ADDRESS_ISR_TASK = pointer_to_function ;
    }
    return (RET);
}
#endif
/**
 * 
 * @param intx
 * @return 
 */
#if   (EXTERNAL_INTERRUPT_FEATURE_INTx == INTERRUPT_ENABLE) 
static std_ReturnType INTx_INTERRUPT_SET_ISR_TASK(const INTx_t * intx)
{
    std_ReturnType RET = E_OK ;
    switch(intx->SOURCE)
    {
        case INT0_SOURCE :  INT0_INTERRUPT_SET_ISR_TASK(intx->EXTTERNAL_INTERRUPT_HANDELER_TASK);break; /*the Address of the function inside the Application */
        case INT1_SOURCE :  INT1_INTERRUPT_SET_ISR_TASK(intx->EXTTERNAL_INTERRUPT_HANDELER_TASK);break;
        case INT2_SOURCE :  INT2_INTERRUPT_SET_ISR_TASK(intx->EXTTERNAL_INTERRUPT_HANDELER_TASK);break;
        default : RET = E_NOT_OK ;
    }
    return (RET);
}
#endif
/*____________________________________________________________________________*/
/*                         Section : Helper Functions Definitions             */
/*____________________________________________________________________________*/
#if   (EXTERNAL_INTERRUPT_FEATURE_INTx == INTERRUPT_ENABLE) 
static std_ReturnType INTx_INTERRUPT_ENABLE(const INTx_t * intx)
{
    std_ReturnType RET = E_OK ;
    switch(intx->SOURCE)
    {
        case INT0_SOURCE :
            #if    (INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE)
            /*INT0 is always High Priority*/
            INTERRUPT_PRORITY_LEVELS_ENABLE();
            GLOBAL_INTERRUPT_HIGH_PRORITY_ENABLE();
            #else
            GLOBAL_INTERRUPT_ENABLE();
            PERIPHERAL_INTERRUPT_ENABLE();
            #endif
            INT0_INTERRUPT_ENABLE(); 
            break;
        case INT1_SOURCE :
            #if    (INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE)
            INTERRUPT_PRORITY_LEVELS_ENABLE();
            if((intx->PRIORITY) == INTERRUPT_LOW_PRIORITY)
            {
                GLOBAL_INTERRUPT_LOW_PRORITY_ENABLE();
            }
            else if((intx->PRIORITY) == INTERRUPT_HIGH_PRIORITY)
            {
                GLOBAL_INTERRUPT_HIGH_PRORITY_ENABLE();
            }
            else
            {
                RET = E_NOT_OK ;
            }
            #else
            GLOBAL_INTERRUPT_ENABLE();
            PERIPHERAL_INTERRUPT_ENABLE();
            #endif
            INT1_INTERRUPT_ENABLE();
            break;
        case INT2_SOURCE :
            #if    (INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE)
            INTERRUPT_PRORITY_LEVELS_ENABLE();
            if((intx->PRIORITY) == INTERRUPT_LOW_PRIORITY)
            {
                GLOBAL_INTERRUPT_LOW_PRORITY_ENABLE();
            }
            else if((intx->PRIORITY) == INTERRUPT_HIGH_PRIORITY)
            {
                GLOBAL_INTERRUPT_HIGH_PRORITY_ENABLE();
            }
            else
            {
                RET = E_NOT_OK ;
            }
            #else
            GLOBAL_INTERRUPT_ENABLE();
            PERIPHERAL_INTERRUPT_ENABLE();
            #endif
            INT2_INTERRUPT_ENABLE(); 
            break;
        default : RET = E_NOT_OK ; 
    }
    return (RET) ;
}
#endif
/**
 * 
 * @param intx
 * @return 
 */
#if   (EXTERNAL_INTERRUPT_FEATURE_INTx == INTERRUPT_ENABLE) 
static std_ReturnType INTx_INTERRUPT_DISABLE(const INTx_t * intx)
{
    std_ReturnType RET = E_OK ;
    switch(intx->SOURCE)
    {
        case INT0_SOURCE :INT0_INTERRUPT_DISABLE(); break;
        case INT1_SOURCE :INT1_INTERRUPT_DISABLE(); break;
        case INT2_SOURCE :INT2_INTERRUPT_DISABLE(); break;
        default : RET = E_NOT_OK ; 
    }
    return (RET) ;
}
#endif
#if   (EXTERNAL_INTERRUPT_FEATURE_INTx == INTERRUPT_ENABLE) 
#if   (INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE)
/**
 * 
 * @param intx
 * @return 
 */
static std_ReturnType INTx_INTERRUPT_SET_PRIORITY(const INTx_t * intx)
{
    std_ReturnType RET = E_OK ;
    switch(intx->SOURCE)
    {
        case INT1_SOURCE :
            if(INTERRUPT_LOW_PRIORITY == (intx->PRIORITY))
            {
                INT1_INTERRUPT_SET_LOW_PRIORITY();
            }
            else if (INTERRUPT_HIGH_PRIORITY == (intx->PRIORITY))
            {
                INT1_INTERRUPT_SET_HIGH_PRIORITY();
            }
            else
            {
                RET = E_NOT_OK ;
            }
            break;
        case INT2_SOURCE : 
            if(INTERRUPT_LOW_PRIORITY == (intx->PRIORITY))
            {
                INT2_INTERRUPT_SET_LOW_PRIORITY();
            }
            else if (INTERRUPT_HIGH_PRIORITY == (intx->PRIORITY))
            {
                INT2_INTERRUPT_SET_HIGH_PRIORITY();
            }
            else
            {
                RET = E_NOT_OK ;
            }
            break;
        default : RET = E_NOT_OK ; 
    }
    return (RET) ;
}
#endif
#endif
/**
 * 
 * @param intx
 * @return 
 */
#if   (EXTERNAL_INTERRUPT_FEATURE_INTx == INTERRUPT_ENABLE) 
static std_ReturnType INTx_INTERRUPT_SET_EDGE(const INTx_t * intx)
{
    std_ReturnType RET = E_OK ;
    switch(intx->SOURCE)
    {
        case INT0_SOURCE :
            if(INTx_FALLING_EDGE == intx->EDGE)
            {
                INT0_INTERRUPT_TRIGGER_FALLING_EDGE();
            }
            else if (INTx_RAISING_EDGE == intx->EDGE)
            {
                INT0_INTERRUPT_TRIGGER_RISING_EDGE();
            }
            else
            {
                RET = E_NOT_OK ;
            }
            break;
        case INT1_SOURCE :
            if(INTx_FALLING_EDGE == intx->EDGE)
            {
                INT1_INTERRUPT_TRIGGER_FALLING_EDGE();
            }
            else if (INTx_RAISING_EDGE == intx->EDGE)
            {
                INT1_INTERRUPT_TRIGGER_RISING_EDGE();
            }
            else
            {
                RET = E_NOT_OK ;
            }
            break;
        case INT2_SOURCE :
            if(INTx_FALLING_EDGE == intx->EDGE)
            {
                INT2_INTERRUPT_TRIGGER_FALLING_EDGE();
            }
            else if (INTx_RAISING_EDGE == intx->EDGE)
            {
                INT2_INTERRUPT_TRIGGER_RISING_EDGE();
            }
            else
            {
                RET = E_NOT_OK ;
            }
            break;
        default : RET = E_NOT_OK ; 
    }
    return (RET) ;
}
#endif
/**
 * 
 * @param intx
 * @return 
 */
#if   (EXTERNAL_INTERRUPT_FEATURE_INTx == INTERRUPT_ENABLE) 
static std_ReturnType INTx_INTERRUPT_SET_PIN(const INTx_t * intx)
{
    std_ReturnType RET = E_NOT_OK ;
    RET = GPIO_PIN_DIRECTION_INTIALIZE(&(intx->INTx_PIN));
    return (RET);
}
/**
 * 
 * @param kibx
 * @return 
 */
static std_ReturnType INTx_CLEAR_FLAG(const INTx_t * intx)
{
    std_ReturnType RET = E_OK ;
    switch(intx->SOURCE)
    {
        case INT0_SOURCE :INT0_INTERRUPT_FLAG_CLEAR(); break;
        case INT1_SOURCE :INT1_INTERRUPT_FLAG_CLEAR(); break;
        case INT2_SOURCE :INT2_INTERRUPT_FLAG_CLEAR(); break;
        default : RET = E_NOT_OK ; 
    }
    return (RET) ;
}
#endif
/*____________________________________________________________________________*/
/*                         Section : APIs Definitions                         */
/*____________________________________________________________________________*/
/**
 * 
 * @param intx
 * @return 
 */
#if   (EXTERNAL_INTERRUPT_FEATURE_INTx == INTERRUPT_ENABLE) 
std_ReturnType INTx_INTERRUPT_INITIALIZATION(const INTx_t * intx )
{
    std_ReturnType RET = E_OK ;
    if(NULL == intx)
    {
        RET = E_NOT_OK ;
    }
    else
    {
        /*Disable the External Interrupt*/
        RET = INTx_INTERRUPT_DISABLE(intx);
        /*Clear the Flag of External Interrupt*/
        RET = INTx_CLEAR_FLAG(intx);
        /*Configure the Edge of External Interrupt*/
        RET = INTx_INTERRUPT_SET_EDGE(intx);
        /*Configure the Priority of External Interrupt*/
        #if   (INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE)
        RET = INTx_INTERRUPT_SET_PRIORITY(intx);
        #endif
        /*Configure the I/O Pin of External Interrupt*/
        RET = INTx_INTERRUPT_SET_PIN(intx);
        /*Configure the Default Interrupt call back of External Interrupt*/
        RET = INTx_INTERRUPT_SET_ISR_TASK(intx);
        /*Disable the External Interrupt*/
        RET = INTx_INTERRUPT_ENABLE(intx);
    }
    return (RET);
}
/**
 * 
 * @param intx
 * @return 
 */
std_ReturnType INTx_INTERRUPT_DEINITIALIZATION(const INTx_t * intx )
{
    std_ReturnType RET = E_OK ;
    if(NULL == intx)
    {
        RET = E_NOT_OK ;
    }
    else
    {
        RET = INTx_INTERRUPT_DISABLE(intx);
    }
    return (RET);
}
#endif
/**
 * 
 * @param kibx
 * @return 
 */
#if   (EXTERNAL_INTERRUPT_FEATURE_ON_CHANGE_KBIx == INTERRUPT_ENABLE)
std_ReturnType KBIx_INTERRUPT_INITIALIZATION(const KBIx_t * kibx )
{
    std_ReturnType RET = E_OK ;
    if(NULL == kibx)
    {
        RET = E_NOT_OK ;
    }
    else
    {
        /*Disable the External Interrupt*/
        ON_CHANGE_KBI_INTERRUPT_DISABLE();
        /*Clear the Flag of External Interrupt*/
        ON_CHANGE_KBI_INTERRUPT_FLAG_CLEAR();
        /*Configure the Priority of External Interrupt*/
        #if    (INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE)
        INTERRUPT_PRORITY_LEVELS_ENABLE();
        if((kibx->PRIORITY) == INTERRUPT_LOW_PRIORITY)
        {
            GLOBAL_INTERRUPT_LOW_PRORITY_ENABLE();
        }
        else if((kibx->PRIORITY) == INTERRUPT_HIGH_PRIORITY)
        {
            GLOBAL_INTERRUPT_HIGH_PRORITY_ENABLE();
        }
        else
        {
            RET = E_NOT_OK ;
        }
        #else
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERAL_INTERRUPT_ENABLE();
        #endif
        /*initialize the Pin as Input*/
        RET = GPIO_PIN_DIRECTION_INTIALIZE(&(kibx->KBIx_PIN)); 
        /*Select The Pin Of On Change Interrupt to get the target ISR of pin*/
        switch(kibx->KBIx_PIN.PIN)
        {
            case KBI_4 :
                KBI4_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_HIGH = (kibx->EXTTERNAL_INTERRUPT_HANDELER_TASK_CHANGE_TO_HIGH);
                KBI4_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_LOW = (kibx->EXTTERNAL_INTERRUPT_HANDELER_TASK_CHANGE_TO_LOW);
                break;
            case KBI_5 :
                KBI5_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_HIGH = (kibx->EXTTERNAL_INTERRUPT_HANDELER_TASK_CHANGE_TO_HIGH);
                KBI5_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_LOW = (kibx->EXTTERNAL_INTERRUPT_HANDELER_TASK_CHANGE_TO_LOW);
                break;
            case KBI_6 : 
                KBI6_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_HIGH = (kibx->EXTTERNAL_INTERRUPT_HANDELER_TASK_CHANGE_TO_HIGH);
                KBI6_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_LOW = (kibx->EXTTERNAL_INTERRUPT_HANDELER_TASK_CHANGE_TO_LOW);
                break;
            case KBI_7 :
                KBI7_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_HIGH = (kibx->EXTTERNAL_INTERRUPT_HANDELER_TASK_CHANGE_TO_HIGH);
                KBI7_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_LOW = (kibx->EXTTERNAL_INTERRUPT_HANDELER_TASK_CHANGE_TO_LOW);
                break;
            default : RET = E_NOT_OK ;
        }
        /*Enable the External Interrupt*/
        ON_CHANGE_KBI_INTERRUPT_ENABLE();
    }
    return (RET);
}
/**
 * 
 * @param kibx
 * @return 
 */
std_ReturnType KBIx_INTERRUPT_DEINITIALIZATION(const KBIx_t * kibx )
{
    std_ReturnType RET = E_OK ;
    if(NULL == kibx)
    {
        RET = E_NOT_OK ;
    }
    else
    {
        ON_CHANGE_KBI_INTERRUPT_DISABLE();
    }
    return (RET);
}
#endif
/*____________________________________________________________________________*/
/*                         Section : ISR Functions Definitions                */
/*____________________________________________________________________________*/
#if   (EXTERNAL_INTERRUPT_FEATURE_INTx == INTERRUPT_ENABLE) 
void INT0_ISR(void)
{
    /*clear the flag by software */
    INT0_INTERRUPT_FLAG_CLEAR();
    /*code*/
    
    /*call back function if the interrupt occurred*/
    if(INT0_INTERRUPT_ADDRESS_ISR_TASK)
    {
        INT0_INTERRUPT_ADDRESS_ISR_TASK();
    }
}
void INT1_ISR(void)
{
    /*clear the flag by software */
    INT1_INTERRUPT_FLAG_CLEAR();
    /*code*/
    
    /*call back function if the interrupt occurred*/
    if(INT1_INTERRUPT_ADDRESS_ISR_TASK)
    {
        INT1_INTERRUPT_ADDRESS_ISR_TASK();
    }
}
void INT2_ISR(void)
{
    /*clear the flag by software */
    INT2_INTERRUPT_FLAG_CLEAR();
    /*code*/
    
    /*call back function if the interrupt occurred*/
    if(INT2_INTERRUPT_ADDRESS_ISR_TASK)
    {
        INT2_INTERRUPT_ADDRESS_ISR_TASK();
    }
}
#endif

#if   (EXTERNAL_INTERRUPT_FEATURE_ON_CHANGE_KBIx == INTERRUPT_ENABLE)
void KBI_4_ISR(uint8 CHANGE_TO_)
{
    /*clear the flag by software */
       ON_CHANGE_KBI_INTERRUPT_FLAG_CLEAR();
    /*code*/
       if(CHANGE_TO_ == HIGH)
       {
            /*call back function if the interrupt occurred*/
            if(KBI4_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_HIGH)
            {
                KBI4_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_HIGH();
            }
       }
       else if(CHANGE_TO_ == LOW)
       {
            /*call back function if the interrupt occurred*/
            if(KBI4_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_LOW)
            {
                KBI4_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_LOW();
            } 
       }

}
void KBI_5_ISR(uint8 CHANGE_TO_)
{
    /*clear the flag by software */
       ON_CHANGE_KBI_INTERRUPT_FLAG_CLEAR();
    /*code*/
       if(CHANGE_TO_ == HIGH)
       {
            /*call back function if the interrupt occurred*/
            if(KBI5_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_HIGH)
            {
                KBI5_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_HIGH();
            }
       }
       else if(CHANGE_TO_ == LOW)
       {
            /*call back function if the interrupt occurred*/
            if(KBI5_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_LOW)
            {
                KBI5_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_LOW();
            } 
       }
}
void KBI_6_ISR(uint8 CHANGE_TO_)
{
    /*clear the flag by software */
       ON_CHANGE_KBI_INTERRUPT_FLAG_CLEAR();
    /*code*/
       if(CHANGE_TO_ == HIGH)
       {
            /*call back function if the interrupt occurred*/
            if(KBI6_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_HIGH)
            {
                KBI6_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_HIGH();
            }
       }
       else if(CHANGE_TO_ == LOW)
       {
            /*call back function if the interrupt occurred*/
            if(KBI6_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_LOW)
            {
                KBI6_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_LOW();
            } 
       }
}
void KBI_7_ISR(uint8 CHANGE_TO_)
{
    /*clear the flag by software */
       ON_CHANGE_KBI_INTERRUPT_FLAG_CLEAR();
    /*code*/
       if(CHANGE_TO_ == HIGH)
       {
            /*call back function if the interrupt occurred*/
            if(KBI7_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_HIGH)
            {
                KBI7_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_HIGH();
            }
       }
       else if(CHANGE_TO_ == LOW)
       {
            /*call back function if the interrupt occurred*/
            if(KBI7_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_LOW)
            {
                KBI7_INTERRUPT_ADDRESS_ISR_TASK_CHANGE_TO_LOW();
            } 
       }
}
#endif