/* 
 * File:   USART_PROGRAM.c
 * Author: ziad osama
 *
 * Created on November 30, 2024, 3:14 PM
 */
/*_____________________________________________________________________________*/
/*                         Section : Includes                                  */
/*_____________________________________________________________________________*/
#include "USART_INTERFACE.h"
/*_____________________________________________________________________________*/
/*                         Section : Helper Functions                          */
/*_____________________________________________________________________________*/

#if  USART_TX_INTERRUPT_FEATURE == INTERRUPT_ENABLE
static void (*USART_TX_INTERRUPT_HANDLER_TASK)(void) = NULL;
#endif

#if  USART_RX_INTERRUPT_FEATURE == INTERRUPT_ENABLE
static void (*USART_RX_INTERRUPT_HANDLER_TASK)(void) = NULL;
static void (*USART_FRAM_ERROR_INTERRUPT_HANDLER_TASK)(void) = NULL;
static void (*USART_OVER_RUN_ERROR_INTERRUPT_HANDLER_TASK)(void) = NULL;
#endif


/*_____________________________________________________________________________*/
/*                         Section : Helper Functions                          */
/*_____________________________________________________________________________*/
/**
 * 
 * @param usart
 */
static void USART_BAUD_RATE_CALCULATION(const USART_t * usart)
{
    float Baud_Rate_Temp = 0 ;
    switch(usart->Baud_Rate_Mode_and_Form)
    {
        case BAUDRATE_ASYN_8BIT_LOW_SPEED :
            USART_ASYNC_MODE();
            USART_8BIT_BAUD_RATE_GENERATOR();
            USART_ASYNC_MODE_LOW_SPEED();
            Baud_Rate_Temp = ( ( _XTAL_FREQ / (float)(usart->Baud_Rate) )/ 64 ) - 1;
            break;
        case BAUDRATE_ASYN_8BIT_HIGH_SPEED :
            USART_ASYNC_MODE();
            USART_8BIT_BAUD_RATE_GENERATOR();
            USART_ASYNC_MODE_HIGH_SPEED();
            Baud_Rate_Temp = ( ( _XTAL_FREQ / (float)(usart->Baud_Rate) )/ 16 ) - 1;
            break;
        case BAUDRATE_ASYN_16BIT_LOW_SPEED :
            USART_ASYNC_MODE();
            USART_16BIT_BAUD_RATE_GENERATOR();
            USART_ASYNC_MODE_LOW_SPEED();
            Baud_Rate_Temp = ( ( _XTAL_FREQ / (float)(usart->Baud_Rate) )/ 16 ) - 1;
            break;
        case BAUDRATE_ASYN_16BIT_HIGH_SPEED : 
            USART_ASYNC_MODE();
            USART_16BIT_BAUD_RATE_GENERATOR();
            USART_ASYNC_MODE_HIGH_SPEED();
            Baud_Rate_Temp = ( ( _XTAL_FREQ / (float)(usart->Baud_Rate) )/ 4 ) - 1;
            break;
        case BAUDRATE_SYN_8BIT :
            USART_SYNC_MODE();
            USART_8BIT_BAUD_RATE_GENERATOR();
            Baud_Rate_Temp = ( ( _XTAL_FREQ / (float)(usart->Baud_Rate) )/ 4 ) - 1;
            break;
        case BAUDRATE_SYN_16BIT :
            USART_SYNC_MODE();
            USART_16BIT_BAUD_RATE_GENERATOR();
            Baud_Rate_Temp = ( ( _XTAL_FREQ / (float)(usart->Baud_Rate) )/ 4 ) - 1;
            break;
        default : asm("NOP");
    }
    SPBRG  = (uint8)((uint32)Baud_Rate_Temp);
    SPBRGH = (uint8)(((uint32)Baud_Rate_Temp)>>8) ;
}
/**
 * 
 * @param usart
 */
static void USART_ASYNC_TX_INIT(const USART_t * usart)
{
    /*TX Enable*/
    if((usart->TX_Cfg.USART_TX_ENABLE) == USART_ASYNCHRONOUS_TX_ENABLE)
    {
        USART_TX_ENABLE();
        /*TX Interrupt*/
        #if  USART_TX_INTERRUPT_FEATURE == INTERRUPT_ENABLE
        /*_____________________________________________________________________________*/
        if((usart->TX_Cfg.USART_TX_INTERRUPT_ENABLE) == USART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE)
        {
            GLOBAL_INTERRUPT_ENABLE();
            PERIPHERAL_INTERRUPT_ENABLE();
            USART_TX_INTERRUPT_ENABLE();
            #if INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE
            /*_____________________________________________________________________________*/
            INTERRUPT_PRORITY_LEVELS_ENABLE();
            if((usart->TX_Cfg.USART_TX_INTERRUPT_PRIORITY) == INTERRUPT_HIGH_PRIORITY)
            {
                USART_TX_SET_INTERRUPT_HIGH_PRIORITY();
            }
            else if ((usart->TX_Cfg.USART_TX_INTERRUPT_PRIORITY) == INTERRUPT_LOW_PRIORITY)
            {
                USART_TX_SET_INTERRUPT_LOW_PRIORITY();
            }
            else
            {
                asm("NOP");
            }
            /*_____________________________________________________________________________*/
            #endif
            USART_TX_INTERRUPT_HANDLER_TASK = (usart->USART_TX_DefaultInterruptHandler);
        }
        else if((usart->TX_Cfg.USART_TX_INTERRUPT_ENABLE) == USART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE)
        {
            USART_TX_INTERRUPT_DISABLE();
        }
        else
        {
            asm("NOP");
        }
        /*_____________________________________________________________________________*/
        #endif
        /*TX 9BIT Data*/
        if((usart->TX_Cfg.USART_TX_9BIT_DATA_ENABLE) == USART_ASYNCHRONOUS_9BIT_TX_ENABLE)
        {
            USART_TX_9BIT_TRANSMISSION_ENABLE();
        }
        else if ((usart->TX_Cfg.USART_TX_9BIT_DATA_ENABLE) == USART_ASYNCHRONOUS_9BIT_TX_DISABLE)
        {
            USART_TX_9BIT_TRANSMISSION_DISABLE();
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
 * @param usart
 */
static void USART_ASYNC_RX_INIT(const USART_t * usart)
{
    /*RX Enable*/
    if((usart->RX_Cfg.USART_RX_ENABLE) == USART_ASYNCHRONOUS_RX_ENABLE)
    {
        USART_RX_ASYNC_ENABLE();
        /*RX Interrupt*/
        #if  USART_RX_INTERRUPT_FEATURE == INTERRUPT_ENABLE
        /*_____________________________________________________________________________*/
        if((usart->RX_Cfg.USART_RX_INTERRUPT_ENABLE) == USART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE)
        {
            GLOBAL_INTERRUPT_ENABLE();
            PERIPHERAL_INTERRUPT_ENABLE();
            USART_RX_INTERRUPT_ENABLE();
            #if INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE
            /*_____________________________________________________________________________*/
            INTERRUPT_PRORITY_LEVELS_ENABLE();
            if((usart->RX_Cfg.USART_RX_INTERRUPT_PRIORITY) == INTERRUPT_HIGH_PRIORITY)
            {
                USART_RX_SET_INTERRUPT_HIGH_PRIORITY();
            }
            else if ((usart->RX_Cfg.USART_RX_INTERRUPT_PRIORITY) == INTERRUPT_LOW_PRIORITY)
            {
                USART_RX_SET_INTERRUPT_LOW_PRIORITY();
            }
            else
            {
                asm("NOP");
            }
            /*_____________________________________________________________________________*/
            #endif
            USART_RX_INTERRUPT_HANDLER_TASK = (usart->USART_RX_DefaultInterruptHandler);
            USART_FRAM_ERROR_INTERRUPT_HANDLER_TASK =(usart->USART_FramingError_DefaultInterruptHandler);
            USART_OVER_RUN_ERROR_INTERRUPT_HANDLER_TASK = (usart->USART_OverRunError_DefaultInterruptHandler);
        }
        else if((usart->RX_Cfg.USART_RX_INTERRUPT_ENABLE) == USART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE)
        {
            USART_RX_INTERRUPT_DISABLE();
        }
        else
        {
            asm("NOP");
        }
        /*_____________________________________________________________________________*/
        #endif
        /*RX 9BIT Data*/
        if((usart->RX_Cfg.USART_RX_9BIT_DATA_ENABLE) == USART_ASYNCHRONOUS_9BIT_RX_ENABLE)
        {
            USART_RX_9BIT_TRANSMISSION_ENABLE();
        }
        else if ((usart->RX_Cfg.USART_RX_9BIT_DATA_ENABLE) == USART_ASYNCHRONOUS_9BIT_RX_DISABLE)
        {
            USART_RX_9BIT_TRANSMISSION_DISABLE();
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
/*_____________________________________________________________________________*/
/*                         Section : APIs Definitions                          */
/*_____________________________________________________________________________*/
/**
 * 
 * @param usart
 * @return 
 */
std_ReturnType USART_ASYNC_INITIALIZE(const USART_t * usart)
{
    std_ReturnType RET = E_OK ;
    if(usart == NULL)
    {
        RET = E_NOT_OK;
    }
    else
    {
        /*Disable USART Module*/
        USART_MODULE_DISABLE();
        /* SPEN bit (RCSTA<7>) must be set (= 1) & TRISC<7> bit must be set (= 1)
         TRISC<6> bit must be set (= 1) Note: The EUSART control will automatically
        reconfigure the pin from input to output as needed.*/
        SET_BIT(TRISC,RC6);
        SET_BIT(TRISC,RC7);
        /*Baud Rate Calculation*/
        USART_BAUD_RATE_CALCULATION(usart);
        /*Set TX Configuration*/
        USART_ASYNC_TX_INIT(usart);
        /*Set RX Configuration*/
        USART_ASYNC_RX_INIT(usart);
        /*Enable USART Module*/
        USART_MODULE_ENABLE();
    }
    return (RET);
}
/**
 * 
 * @param usart
 * @return 
 */
std_ReturnType USART_ASYNC_DEINITIALIZE(const USART_t * usart)
{
    std_ReturnType RET = E_OK ;
    if(usart == NULL)
    {
        RET = E_NOT_OK;
    }
    else
    {
        /*Disable USART Module*/
        USART_MODULE_DISABLE();
    }
    return (RET);
}
/**
 * 
 * @param usart
 * @param DataByte
 * @return 
 */
std_ReturnType USART_ASYNC_READ_BYTE_BLOCKING(uint8 * DataByte)
{
    std_ReturnType RET = E_OK ;
    while(USART_RX_GET_INTERRUPT_FLAG_STATUS() == 0);
    *DataByte = (uint8)RCREG;
    return (RET);
}
/**
 * 
 * @param DataByte
 * @return 
 */
std_ReturnType USART_ASYNC_READ_BYTE_NON_BLOCKING(uint8 * DataByte)
{
    std_ReturnType RET = E_NOT_OK ;
    if(USART_RX_GET_INTERRUPT_FLAG_STATUS() == 1)
    {
        *DataByte = (uint8)RCREG;
        RET = E_OK ;
    }
    else
    {
        RET = E_NOT_OK;
    }
    return (RET);
}
/**
 * 
 * @param str
 * @return 
 */
std_ReturnType USART_ASYNC_READ_STRING_BLOCKING(uint8 * str,uint8 * Length_Str)
{
   std_ReturnType RET = E_NOT_OK;
   uint8 Read_Byte = 0 ;
   uint8 Local_Iterator = 0;
   while(Read_Byte != 0x0D)
   {
       RET = USART_ASYNC_READ_BYTE_BLOCKING(&Read_Byte);
       if(Read_Byte == 0x0D)
       {
            str[Local_Iterator] = '\0';
            str[Local_Iterator+1] = '\0';
       }
       else if(Read_Byte == 0x08)
       {
           str[Local_Iterator] = '\0';
           if((Local_Iterator == 1) && (str[Local_Iterator+1] == '\0'))
           {
               Local_Iterator = 0 ;
           }
           else
           {
               Local_Iterator-=2;
           }  
       }
       str[Local_Iterator] = Read_Byte;
       if(str[Local_Iterator] != '\0')
       {
           Local_Iterator++;

       }
   }
   *Length_Str = Local_Iterator;
   return (RET);
}
/**
 * 
 * @param usart
 * @param DataByte
 * @return 
 */
std_ReturnType USART_ASYNC_WRITE_BYTE_BLOCKING(uint8  DataByte)
{
    std_ReturnType RET = E_OK ;
    while(USART_TX_SHIFT_REG_STATUS() == USART_TX_SHIFT_REG_FULL);
    #if  USART_TX_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    USART_TX_INTERRUPT_ENABLE();
    #endif
    TXREG = (uint8)DataByte;
    return (RET);
}
/**
 * 
 */
void USART_ASYNC_RX_RESTART(void)
{
    USART_RX_ASYNC_DISABLE();
    USART_RX_ASYNC_ENABLE();
}
/**
 * 
 * @param str
 * @return 
 */
std_ReturnType USART_ASYNC_WRITE_STRING_BLOCKING(uint8 * str)
{
    std_ReturnType RET = E_OK;
    uint8 Local_Iterator = 0 ;
    if(str == NULL)
    {
        RET = E_NOT_OK;
    }
    else
    {
        while(str[Local_Iterator] != '\0')
        {
           RET = USART_ASYNC_WRITE_BYTE_BLOCKING(str[Local_Iterator]);
           Local_Iterator++;
        }
    }
    return (RET);
}
/*_____________________________________________________________________________*/
/*                         Section : ISR Functions                             */
/*_____________________________________________________________________________*/
/*____________________________________________________________________________*/
/*______________________USART_TX_INTERRUPT_FEATURE____________________________*/
/*____________________________________________________________________________*/
#if  USART_TX_INTERRUPT_FEATURE == INTERRUPT_ENABLE
void USART_TX_ISR(void)
{
    USART_TX_INTERRUPT_DISABLE();
    if(USART_TX_INTERRUPT_HANDLER_TASK)
    {
        USART_TX_INTERRUPT_HANDLER_TASK();
    }
}
#endif
/*____________________________________________________________________________*/
/*______________________USART_RX_INTERRUPT_FEATURE____________________________*/
/*____________________________________________________________________________*/
#if  USART_RX_INTERRUPT_FEATURE == INTERRUPT_ENABLE
void USART_RX_ISR(void)
{
    if(USART_RX_INTERRUPT_HANDLER_TASK)
    {
        USART_RX_INTERRUPT_HANDLER_TASK();
    }
    else{asm("NOP");}
    if(USART_FRAM_ERROR_INTERRUPT_HANDLER_TASK)
    {
        USART_FRAM_ERROR_INTERRUPT_HANDLER_TASK();
    }
    else{asm("NOP");}
    if(USART_OVER_RUN_ERROR_INTERRUPT_HANDLER_TASK)
    {
        USART_OVER_RUN_ERROR_INTERRUPT_HANDLER_TASK();
    }
    else{asm("NOP");}
}
#endif