/* 
 * File:   SPI_INTERFACE.h
 * Author: ziad osama
 *
 * Created on December 9, 2024, 9:34 PM
 */
/*_____________________________________________________________________________*/
/*                         Section : Includes                                  */
/*_____________________________________________________________________________*/
#include "SPI_INTERFACE.h"
/*_____________________________________________________________________________*/
/*                         Section : Global Pointer To Functions               */
/*_____________________________________________________________________________*/
#if  SPI_INTERRUPT_FEATURE == INTERRUPT_ENABLE
void (*SPI_INTERRUPT_HANDELAR_TASK)(void) = NULL;
#endif
/*_____________________________________________________________________________*/
/*                         Section : Helper Functions                          */
/*_____________________________________________________________________________*/
/**
 * 
 * @param spi
 */
static void SPI_SELECT_MASTER_OR_SLAVE_MODE(const SPI_t * spi)
{
    SSPCON1 &= 0x0F;
    SSPCON1 |= (spi->SPI_Mode);
}
/**
 * 
 * @param spi
 */
static void SPI_SELECT_TRANSMITTING_TRANSITION(const SPI_t * spi)
{
    switch((spi->SPI_Data_Transmitting_Transition))
    {
        case from_low_to_low:
            SPI_IDLE_STATE_LOW();
            SPI_TRANSMIT_FROM_IDLE_TO_ACTIVE_CLOCK();
            break;
        case from_high_to_low:
            SPI_IDLE_STATE_HIGH();
            SPI_TRANSMIT_FROM_IDLE_TO_ACTIVE_CLOCK();
            break;
        case from_low_to_high:
            SPI_IDLE_STATE_LOW();
            SPI_TRANSMIT_FROM_ACTIVE_TO_IDLE_CLOCK();
            break;
        case from_high_to_high:
            SPI_IDLE_STATE_HIGH();
            SPI_TRANSMIT_FROM_ACTIVE_TO_IDLE_CLOCK();
            break;
        default: asm("NOP");
    }
}
/**
 * 
 * @param spi
 */
static void SPI_SELECT_SAMPLE_MODE_RECEIVING(const SPI_t * spi)
{
    if( ((spi->SPI_Sample_Mode) == SPI_SAMPLE_SLAVE) || ((spi->SPI_Sample_Mode) == SPI_SAMPLE_MASTER_MID ) )
    {
        SPI_SAMPLE_SLAVE_MODE_AND_MID_DATA_OUTPUT();
    }
    else if((spi->SPI_Sample_Mode) == SPI_SAMPLE_MASTER_END )
    {
        SPI_SAMPLE_MASTER_MODE_END_DATA_OUTPUT();
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
 * @param spi
 * @return 
 */
std_ReturnType SPI_INITIALIZE(const SPI_t * spi)
{
    std_ReturnType RET = E_OK;
    if(spi == NULL)
    {
       RET = E_NOT_OK; 
    }
    else
    {
        /*Disable SPI Module*/
        SPI_DISABLE();
        /*Select SPI Mode and Pre-scaler*/
        SPI_SELECT_MASTER_OR_SLAVE_MODE(spi);
        /*Select The Transmitting Data Transition*/
        SPI_SELECT_TRANSMITTING_TRANSITION(spi);
        /*Select The Sampling Receiving Mode*/
        SPI_SELECT_SAMPLE_MODE_RECEIVING(spi);
        /*Initialize The SPI Pins */
        RET = GPIO_PIN_DIRECTION_INTIALIZE(&(spi->MISO));
        RET = GPIO_PIN_DIRECTION_INTIALIZE(&(spi->MOSI));
        RET = GPIO_PIN_DIRECTION_INTIALIZE(&(spi->SCK));
        RET = GPIO_PIN_DIRECTION_INTIALIZE(&(spi->SS));
        /* SPI Interrupt Feature */
        #if  SPI_INTERRUPT_FEATURE == INTERRUPT_ENABLE
        SPI_INTERRUPT_HANDELAR_TASK = (spi->SPI_Interrupt_Handler);
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERAL_INTERRUPT_ENABLE();
        SPI_INTERRUPT_ENABLE();
        /*_____________________________________________________________________________*/
        #if INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE
        /*_____________________________________________________________________________*/
        INTERRUPT_PRORITY_LEVELS_ENABLE();
        if((spi->SPI_Interrupt_Priority) == INTERRUPT_HIGH_PRIORITY)
        {
            SPI_SET_INTERRUPT_HIGH_PRIORITY();
        }
        else if((spi->SPI_Interrupt_Priority) == INTERRUPT_LOW_PRIORITY)
        {
            SPI_SET_INTERRUPT_LOW_PRIORITY();
        }
        else
        {
            asm("NOP");
        }
        /*_____________________________________________________________________________*/
        #endif
        /*_____________________________________________________________________________*/
        #endif
        /*Enable SPI Module*/
        SPI_ENABLE();
    }
    return (RET);
}
/**
 * 
 * @param spi
 * @return 
 */
std_ReturnType SPI_DEINITIALIZE(const SPI_t * spi)
{
    std_ReturnType RET = E_OK;
    if(spi == NULL)
    {
        RET = E_NOT_OK;
    }
    else
    {
        SPI_DISABLE();
        #if  SPI_INTERRUPT_FEATURE == INTERRUPT_ENABLE
        SPI_INTERRUPT_DISABLE();
        #endif
    }
    return (RET);
}
/**
 * 
 * @param spi
 * @param DataByte
 * @return 
 */
std_ReturnType SPI_MASTER_SEND_BYTE(const SPI_t * spi,const Pin_Config_t * SS_Slave,uint8 DataByte)
{
    std_ReturnType RET = E_OK;
    if((spi == NULL) || (SS_Slave == NULL))
    {
        RET = E_NOT_OK;
    }
    else
    {
       RET = GPIO_PIN_WRITE_LOGIC(SS_Slave,LOW);
       SSPBUF = (uint8)DataByte;
       while(!SPI_DATA_REGISTER_RECEIVE_MODE_STATUS());
    }
    return (RET);
}
/**
 * 
 * @param spi
 * @param DataByte
 * @return 
 */
std_ReturnType SPI_MASTER_RECEIVE_BYTE(const SPI_t * spi,const Pin_Config_t * SS_Slave,uint8 *DataByte)
{
    std_ReturnType RET = E_OK;
    if((spi == NULL) || (DataByte == NULL) || (SS_Slave == NULL))
    {
        RET = E_NOT_OK;
    }
    else
    {
        SSPBUF = 0x00;
        RET = GPIO_PIN_WRITE_LOGIC(SS_Slave,LOW);
        while(!SPI_DATA_REGISTER_RECEIVE_MODE_STATUS());
        *DataByte = SSPBUF;
    }
    return (RET);
}
/**
 * 
 * @param spi
 * @param DataByte
 * @return 
 */
std_ReturnType SPI_SLAVE_SEND_BYTE(const SPI_t * spi,uint8 DataByte)
{
    std_ReturnType RET = E_OK;
    if(spi == NULL)
    {
        RET = E_NOT_OK;
    }
    else
    {
        SSPBUF = (uint8)DataByte;
        while(!SPI_DATA_REGISTER_RECEIVE_MODE_STATUS());
    }
    return (RET);
}
/**
 * 
 * @param spi
 * @param DataByte
 * @return 
 */
std_ReturnType SPI_SLAVE_RECEIVE_BYTE(const SPI_t * spi,uint8 *DataByte)
{
    std_ReturnType RET = E_OK;
    if((spi == NULL) || (DataByte == NULL))
    {
        RET = E_NOT_OK;
    }
    else
    {
        while(!SPI_DATA_REGISTER_RECEIVE_MODE_STATUS());
        *DataByte = SSPBUF;
    }
    return (RET);
}
/*_____________________________________________________________________________*/
/*                         Section : ISR Definitions                           */
/*_____________________________________________________________________________*/
#if  SPI_INTERRUPT_FEATURE == INTERRUPT_ENABLE
void SPI_ISR(void)
{
    SPI_CLEAR_INTERRUPT_FLAG();
    if(SPI_INTERRUPT_HANDELAR_TASK)
    {
        SPI_INTERRUPT_HANDELAR_TASK();
    }
}
#endif