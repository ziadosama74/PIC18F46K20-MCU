/* 
 * File:   USART_INTERFACE.h
 * Author: ziad osama
 *
 * Created on November 30, 2024, 3:14 PM
 */

#ifndef USART_INTERFACE_H
#define	USART_INTERFACE_H
/*_____________________________________________________________________________*/
/*                         Section : Includes                                  */
/*_____________________________________________________________________________*/
#include "USART_REGISTERS.h"
#include "USART_CONFIUG.h"
#include "../../MCAL_Layer/INTERRUPT/MCAL_INTERNAL_INTERRUPT.h"
/*_____________________________________________________________________________*/
/*                         Section : Macro Definitions                         */
/*_____________________________________________________________________________*/
/*______________________________________________________SYNCHRONIZATION________*/
#define    USART_SYNCHRONOUS_MODE                             1
#define    USART_ASYNCHRONOUS_MODE                            0
/*_____________________________________LOW_&_HIGH_SPEED_SYNCHRONIZATION________*/
#define    USART_ASYNCHRONOUS_HIGH_SPEED                      1
#define    USART_ASYNCHRONOUS_LOW_SPEED                       0
/*_______________________________________________BAUDRATE_REGISTER_SIZE________*/
#define    USART_16BIT_BAUDRATE_GEN                           1
#define    USART_8BIT_BAUDRATE_GEN                            0
/*__________________________________________________________TX FEATURES________*/
#define    USART_ASYNCHRONOUS_TX_ENABLE                       1
#define    USART_ASYNCHRONOUS_TX_DISABLE                      0

#define    USART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE             1
#define    USART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE            0

#define    USART_ASYNCHRONOUS_9BIT_TX_ENABLE                  1
#define    USART_ASYNCHRONOUS_9BIT_TX_DISABLE                 0
/*__________________________________________________________RX FEATURES________*/
#define    USART_ASYNCHRONOUS_RX_ENABLE                       1
#define    USART_ASYNCHRONOUS_RX_DISABLE                      0

#define    USART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE             1
#define    USART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE            0

#define    USART_ASYNCHRONOUS_9BIT_RX_ENABLE                  1
#define    USART_ASYNCHRONOUS_9BIT_RX_DISABLE                 0
/*_________________________________________________________FRAMING_ERROR_______*/
#define    USART_FRAMING_ERROR_DETECTED                       1
#define    USART_FRAMING_ERROR_CLEARED                        0
/*_________________________________________________________OVER_RUN_ERROR______*/
#define    USART_OVER_RUN_ERROR_DETECTED                      1
#define    USART_OVER_RUN_ERROR_CLEARED                       0
/*_________________________________________________________TX_SHIFT_REG_STATUS_*/
#define    USART_TX_SHIFT_REG_EMPTY                           1
#define    USART_TX_SHIFT_REG_FULL                            0
/*_____________________________________________________________________________*/
/*                         Section : Macro Functions                           */
/*_____________________________________________________________________________*/
#define  USART_16BIT_BAUD_RATE_GENERATOR()            (SET_BIT(BAUDCON,BRG16))
#define  USART_8BIT_BAUD_RATE_GENERATOR()             (CLEAR_BIT(BAUDCON,BRG16))
/*_____________________________________________________________________________*/
#define  USART_ASYNC_MODE()                           (CLEAR_BIT(TXSTA,SYNC))
#define  USART_SYNC_MODE()                            (SET_BIT(TXSTA,SYNC))
/*_____________________________________________________________________________*/
#define  USART_ASYNC_MODE_LOW_SPEED()                 (CLEAR_BIT(TXSTA,BRGH))
#define  USART_ASYNC_MODE_HIGH_SPEED()                (SET_BIT(TXSTA,BRGH))
/*_____________________________________________________________________________*/
#define  USART_MODULE_ENABLE()                        (SET_BIT(RCSTA,SPEN))
#define  USART_MODULE_DISABLE()                       (CLEAR_BIT(RCSTA,SPEN))
/*_____________________________________________________________________________*/
#define  USART_TX_ENABLE()                            (SET_BIT(TXSTA,TXEN))
#define  USART_TX_DISABLE()                           (CLEAR_BIT(TXSTA,TXEN))
/*_____________________________________________________________________________*/
#define  USART_TX_9BIT_TRANSMISSION_ENABLE()          (SET_BIT(TXSTA,TX9))
#define  USART_TX_9BIT_TRANSMISSION_DISABLE()         (CLEAR_BIT(TXSTA,TX9))
/*_____________________________________________________________________________*/
#define  USART_TX_SHIFT_REG_STATUS()                  (READ_BIT(TXSTA,TRMT))
/*_____________________________________________________________________________*/
#define  USART_RX_ASYNC_ENABLE()                      (SET_BIT(RCSTA,CREN))
#define  USART_RX_ASYNC_DISABLE()                     (CLEAR_BIT(RCSTA,CREN))
/*_____________________________________________________________________________*/
#define  USART_RX_9BIT_TRANSMISSION_ENABLE()          (SET_BIT(RCSTA,RX9))
#define  USART_RX_9BIT_TRANSMISSION_DISABLE()         (CLEAR_BIT(RCSTA,RX9))
/*_____________________________________________________________________________*/
#define    USART_RX_GET_INTERRUPT_FLAG_STATUS()           (READ_BIT(PIR1,RCIF))
/*_____________________________________________________________________________*/
/*                         Section : Data Types Declaration                    */
/*_____________________________________________________________________________*/
typedef enum
{
    BAUDRATE_ASYN_8BIT_LOW_SPEED,   // FOSC/[64 (n + 1)]
    BAUDRATE_ASYN_8BIT_HIGH_SPEED,  // FOSC/[16 (n + 1)]
    BAUDRATE_ASYN_16BIT_LOW_SPEED,  // FOSC/[16 (n + 1)]
    BAUDRATE_ASYN_16BIT_HIGH_SPEED, // FOSC/[4 (n + 1)]
    BAUDRATE_SYN_8BIT,              // FOSC/[4 (n + 1)]
    BAUDRATE_SYN_16BIT              // FOSC/[4 (n + 1)]  where n = value of SPBRGH:SPBRG register pair
}BaudRateGenFormate;

typedef union 
{
    struct
    {
        uint8 USART_FRAM_ERROE : 1;
        uint8 USART_OVER_RUN_ERROR : 1;
    };
    uint8 USART_ERRORS_FOE;   // where : FOE is Framing and Over run Errors 
}USART_ERROR_STATUS_t;

typedef struct 
{
    uint8 USART_TX_ENABLE : 1;
    uint8 USART_TX_INTERRUPT_ENABLE : 1;
    uint8 USART_TX_9BIT_DATA_ENABLE : 1;
    INTERRUPT_PRIORITY USART_TX_INTERRUPT_PRIORITY;
}USART_TX_CFG_t;

typedef struct 
{
    uint8 USART_RX_ENABLE : 1;
    uint8 USART_RX_INTERRUPT_ENABLE : 1;
    uint8 USART_RX_9BIT_DATA_ENABLE : 1;
    INTERRUPT_PRIORITY USART_RX_INTERRUPT_PRIORITY;
    
}USART_RX_CFG_t;

typedef struct 
{
    uint32 Baud_Rate;
    BaudRateGenFormate Baud_Rate_Mode_and_Form;
    USART_TX_CFG_t TX_Cfg;
    USART_RX_CFG_t RX_Cfg;
    USART_ERROR_STATUS_t Error_Status;
    void(*USART_TX_DefaultInterruptHandler)(void);
    void(*USART_RX_DefaultInterruptHandler)(void);
    void(*USART_FramingError_DefaultInterruptHandler)(void);
    void(*USART_OverRunError_DefaultInterruptHandler)(void);
}USART_t;
/*_____________________________________________________________________________*/
/*                         Section : APIs Declaration                          */
/*_____________________________________________________________________________*/
std_ReturnType USART_ASYNC_INITIALIZE(const USART_t * usart);
std_ReturnType USART_ASYNC_DEINITIALIZE(const USART_t * usart);

void USART_ASYNC_RX_RESTART(void);            /*Is used at the over run error */

std_ReturnType USART_ASYNC_READ_BYTE_BLOCKING(uint8 * DataByte);
std_ReturnType USART_ASYNC_READ_BYTE_NON_BLOCKING(uint8 * DataByte);
std_ReturnType USART_ASYNC_READ_STRING_BLOCKING(uint8 * str,uint8 * Length_Str);

std_ReturnType USART_ASYNC_WRITE_BYTE_BLOCKING(uint8  DataByte);
std_ReturnType USART_ASYNC_WRITE_STRING_BLOCKING(uint8 * str);
#endif	/* USART_INTERFACE_H */

