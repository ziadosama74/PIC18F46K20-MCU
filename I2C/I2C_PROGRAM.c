/* 
 * File:   I2C_PROGRAM.h
 * Author: ziad osama
 *
 * Created on December 20, 2024, 2:42 PM
 */
#include "I2C_INTERFACE.h"
/*_____________________________________________________________________________*/
/*                         Section : Global Pointer To Functions               */
/*_____________________________________________________________________________*/
#if  I2C_INTERRUPT_FEATURE == INTERRUPT_ENABLE
static void (*I2C_INTERRUPT_HANDELAR_TASK)(void) = NULL;
static void (*I2C_DATA_COLLISION_INTERRUPT_HANDELAR_TASK)(void) = NULL;
static void (*I2C_INTERRUPT_RECEIVE_OVERFLOW_HANDELAR_TASK)(void) = NULL;
#endif
/*_____________________________________________________________________________*/
/*                         Section : Helper Functions                          */
/*_____________________________________________________________________________*/
/**
 * 
 * @param i2c
 */
static void I2C_SELECT_MASTER_OR_SLAVE_MODE(const I2C_t * i2c)
{
    if((i2c->I2C_Cfg.I2C_Mode) == I2C_MASTER_MODE)
    {
        /*____________________________________________________________________*/
        /*      I2C Master Clock Mode By HW Equation at SSPADD Register       */
        /*____________________________________________________________________*/
        SSPCON1 &= 0xF0;
        SSPCON1 |= (i2c->I2C_Cfg.I2C_Mode_Cfg);
        SSPADD = (uint8)(((_XTAL_FREQ)/(4*(i2c->I2C_Clock)))-1);
        /*____________________________________________________________________*/
    }
    else if((i2c->I2C_Cfg.I2C_Mode) == I2C_SLAVE_MODE)
    {
        /*I2C Slave Mode General Call Configurations*/
        if((i2c->I2C_Cfg.I2C_General_Call) == I2C_ENABLE_PARAMETER)
        {
            I2C_GENERAL_CALL_ADDRESS_ENABLE();
        }
        else if((i2c->I2C_Cfg.I2C_General_Call) == I2C_DISABLE_PARAMETER)
        {
            I2C_GENERAL_CALL_ADDRESS_DISABLE();
        }
        else
        {
            asm("NOP");
        }
        /*I2C Slave Mode Clear The Write Collision Detect*/
        I2C_SLAVE_CLEAR_COLLISION_DATA_DETECT(); /*No collision*/
        /*I2C Slave Mode Clear The Receive Overflow Indicator*/
        I2C_CLEAR_RECEIVE_OVERFLOW_FLAG();       /*NO Overflow*/
        /*I2C Slave Mode Release The Clock*/
        I2C_SLAVE_RELEASE_CLOCK();
        /*I2C Slave Mode Assign The I2C Slave Address*/
        SSPADD = (i2c->I2C_Cfg.I2C_Slave_Address);
        /*I2C Slave Mode Configurations*/
        SSPCON1 &= 0xF0;
        SSPCON1 |= (i2c->I2C_Cfg.I2C_Mode_Cfg);
        /*____________________________________________________________________*/
    }
    else
    {
        asm("NOP");
    }
    /*____________________________________________________________________*/
    /*GPIO I2C Pins Configurations as Input at The Master and Slave as The*/
    /*                     Data Sheet Said                                */
    /*____________________________________________________________________*/
    SET_BIT(TRISC,3); /*I2C SCL Clock Line*/
    SET_BIT(TRISC,4); /*I2C SDA Data Line */
}
/**
 * 
 * @param i2c
 */
static void I2C_SLEW_RATE_ENABLE_OR_DISABLE(const I2C_t * i2c)
{
    if((i2c->I2C_Cfg.I2C_Slew_Rate) == I2C_ENABLE_PARAMETER)
    {
        I2C_HIGH_SPEED_MODE_400KHz_SLEW_ENABLE();
    }
    else if((i2c->I2C_Cfg.I2C_Slew_Rate) == I2C_DISABLE_PARAMETER)
    {
        I2C_STANDARD_SPEED_MODE_100KHz_SLEW_DISABLE();
    }
    else
    {
        asm("NOP");
    }
}
/**
 * 
 * @param i2c
 */
static void I2C_SMBUS_ENABLE_OR_DISABLE(const I2C_t * i2c)
{
    if((i2c->I2C_Cfg.I2C_SMBus_Control) == I2C_ENABLE_PARAMETER)
    {
        I2C_SMBUS_ENABLE();
    }
    else if((i2c->I2C_Cfg.I2C_SMBus_Control) == I2C_DISABLE_PARAMETER)
    {
        I2C_SMBUS_DISABLE();
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
 * @param i2c
 * @return 
 */
std_ReturnType I2C_INITIALIZE(const I2C_t * i2c)
{
    std_ReturnType RET = E_OK;
    if(i2c == NULL)
    {
        RET = E_NOT_OK;
    }
    else
    {
        /*MSSP I2C Module Disable*/
        MSSP_I2C_MODULE_DISABLE();
        /*I2C Select Mode Master or Slave Mode*/
        I2C_SELECT_MASTER_OR_SLAVE_MODE(i2c);
        /*I2C Slew Rate Enable or Disable*/
        I2C_SLEW_RATE_ENABLE_OR_DISABLE(i2c);
        /*I2C SMBus Enable or Disable*/
        I2C_SMBUS_ENABLE_OR_DISABLE(i2c);
        /*I2C Interrupt Feature*/
        #if  I2C_INTERRUPT_FEATURE == INTERRUPT_ENABLE
        I2C_INTERRUPT_HANDELAR_TASK = (i2c->I2C_Default_Interrupt_Handler);
        I2C_DATA_COLLISION_INTERRUPT_HANDELAR_TASK = (i2c->I2C_Report_Write_Collision);
        I2C_INTERRUPT_RECEIVE_OVERFLOW_HANDELAR_TASK = (i2c->I2C_Report_Receive_Overflow);
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERAL_INTERRUPT_ENABLE();
        I2C_INTERRUPT_ENABLE();
        I2C_INTERRUPT_DATA_COLLISION_ENABLE();
        I2C_CLEAR_INTERRUPT_FLAG();
        I2C_DTAT_COLLISION_CLEAR_INTERRUPT_FLAG();
        /*_____________________________________________________________________________*/
        #if INTERRUPT_PRORITY_LEVELS_STATUS == INTERRUPT_PRIORTY_ENABLE
        /*_____________________________________________________________________________*/
        INTERRUPT_PRORITY_LEVELS_ENABLE();
        if((i2c->I2C_Default_Interrupt_Handler_Priority) == INTERRUPT_HIGH_PRIORITY)
        {
            I2C_SET_INTERRUPT_HIGH_PRIORITY();
        }
        else if((i2c->I2C_Default_Interrupt_Handler_Priority) == INTERRUPT_LOW_PRIORITY)
        {
            I2C_SET_INTERRUPT_LOW_PRIORITY();
        }
        else
        {
            asm("NOP");
        }
        /*____________________________________________________________________________*/
        /*                     I2C_INTERRUPT_DATA_COLLISION                           */
        /*____________________________________________________________________________*/
        if((i2c->I2C_Report_Write_Collision_Priority) == INTERRUPT_HIGH_PRIORITY)
        {
            I2C_SET_DATA_COLLISION_INTERRUPT_HIGH_PRIORITY();
        }
        else if((i2c->I2C_Report_Write_Collision_Priority) == INTERRUPT_LOW_PRIORITY)
        {
            I2C_SET_DATA_COLLISION_INTERRUPT_LOW_PRIORITY();
        }
        else
        {
            asm("NOP");
        }
        /*_____________________________________________________________________________*/
        #endif
        /*_____________________________________________________________________________*/
        #endif
        /*MSSP I2C Module Enable*/
        MSSP_I2C_MODULE_ENABLE();
    }
    return (RET);
}
/**
 * 
 * @param i2c
 * @return 
 */
std_ReturnType I2C_DEINITIALIZE(const I2C_t * i2c)
{
    std_ReturnType RET = E_OK;
    if(i2c == NULL)
    {
        RET = E_NOT_OK;
    }
    else
    {
        MSSP_I2C_MODULE_DISABLE();
        #if  I2C_INTERRUPT_FEATURE == INTERRUPT_ENABLE
        I2C_INTERRUPT_DISABLE();
        I2C_INTERRUPT_DATA_COLLISION_DISABLE();
        #endif 
    }
    return (RET);
}
/**
 * 
 * @param i2c
 * @return 
 */
std_ReturnType I2C_MASTER_SEND_STATRT(const I2C_t * i2c)
{
    std_ReturnType RET = E_OK;
    if(i2c == NULL)
    {
        RET = E_NOT_OK;
    }
    else
    {
        /*Initialize Start Condition on SDA and SCL Pins*/
        I2C_MASTER_SEND_S_CON();
        /*Wait The Start Condition To Be Sent*/
        while(I2C_MASTER_READ_S_CON());
        /*Clear The MSSP Interrupt Flag : SSPIF : Because when you send S or P or SR this Flag Will Be Set and it must clear in SW*/
        I2C_MASTER_CLEAR_MSSP_INTERRUPT_FALG();
        /*Report Start Condition On The I2C Bus*/
        if(I2C_DETECT_S_CON())
        {
            RET = E_OK; 
        }
        else
        {
            RET = E_NOT_OK;
        }
    }
    return (RET);
}
/**
 * 
 * @param i2c
 * @return 
 */
std_ReturnType I2C_MASTER_SEND_REPEATED_STATRT(const I2C_t * i2c)
{
    std_ReturnType RET = E_OK;
    if(i2c == NULL)
    {
        RET = E_NOT_OK;
    }
    else
    {
        /*Initialize Repeated Start Condition on SDA and SCL Pins*/
        I2C_MASTER_SEND_SR_CON();
        /*Wait The Repeated Start Condition To Be Sent*/
        while(I2C_MASTER_READ_SR_CON());
        /*Clear The MSSP Interrupt Flag : SSPIF : Because when you send S or P or SR this Flag Will Be Set and it must clear in SW*/
        I2C_MASTER_CLEAR_MSSP_INTERRUPT_FALG();
    }
    return (RET);
}
/**
 * 
 * @param i2c
 * @return 
 */
std_ReturnType I2C_MASTER_SEND_STOP(const I2C_t * i2c)
{
    std_ReturnType RET = E_OK;
    if(i2c == NULL)
    {
        RET = E_NOT_OK;
    }
    else
    {
        /*Initialize Stop Condition on SDA and SCL Pins*/
        I2C_MASTER_SEND_P_CON();
        /*Wait The Stop Condition To Be Sent*/
        while(I2C_MASTER_READ_P_CON());
        /*Clear The MSSP Interrupt Flag : SSPIF : Because when you send S or P or SR this Flag Will Be Set and it must clear in SW*/
        I2C_MASTER_CLEAR_MSSP_INTERRUPT_FALG();
        /*Report Stop Condition On The I2C Bus*/
        if(I2C_DETECT_P_CON())
        {
            RET = E_OK; 
        }
        else
        {
            RET = E_NOT_OK;
        }     
    }
    return (RET);
}
/**
 * 
 * @param i2c
 * @param Data
 * @return 
 */
std_ReturnType I2C_MASTER_WRITE_DATA(const I2C_t * i2c,uint8 Data,uint8 * ack)
{
    std_ReturnType RET = E_OK;
    if((i2c == NULL) || (ack == NULL))
    {
        RET = E_NOT_OK;
    }
    else
    {
        /*Write Data To The Data Register*/
        SSPBUF = Data;
        /*Wait The Transmission Completed*/
        while(!I2C_MASTER_GET_MSSP_INTERRUPT_FALG());
        /*Clear The Flag Because it was set*/
        I2C_MASTER_CLEAR_MSSP_INTERRUPT_FALG();
        /*Report The ACK or NACK received from the slave*/
        if(I2C_GET_ACK_STATUS_FROM_SLAVE())
        {
            *ack = I2C_ACK_RECEIVED_FROM_SLAVE;
        }
        else
        {
            *ack = I2C_ACK_NOT_RECEIVED_FROM_SLAVE;
        }
    }
    return (RET);
}
/**
 * 
 * @param i2c
 * @param ack
 * @param Data
 * @return 
 */
std_ReturnType I2C_MASTER_READ_DATA(const I2C_t * i2c,uint8 ack,uint8 * Data)
{
    std_ReturnType RET = E_OK;
    if((i2c == NULL) || (Data == NULL))
    {
        RET = E_NOT_OK;
    }
    else
    {
        /*Enable Master to Receive*/
        I2C_MASTER_RECEIVER_ENABLE();
        /*Wait For a Completed Byte Received*/
        while(!I2C_GET_STATUS_DATA_BUFFER_REGISTER());
        /*Read The Data*/
        *Data = SSPBUF;
        /*Mater Send ACK or NACK*/
        if(ack == I2C_MASTER_SEND_ACK)
        {
            I2C_MASTER_SEND_ACK_BIT();
            I2C_MASTER_INITE_ACK_SEQ();
        }
        else if(ack == I2C_MASTER_SEND_NACK)
        {
            I2C_MASTER_SEND_NACK_BIT();
            I2C_MASTER_INITE_ACK_SEQ();
        }
        else
        {
           asm("NOP"); 
        }
    }
    return (RET);
}
/*_____________________________________________________________________________*/
/*__________________________ISR_Functions______________________________________*/
/*_____________________________________________________________________________*/
#if  I2C_INTERRUPT_FEATURE == INTERRUPT_ENABLE
void I2C_ISR(void)
{
    I2C_CLEAR_INTERRUPT_FLAG();
    if(I2C_INTERRUPT_HANDELAR_TASK)
    {
        I2C_INTERRUPT_HANDELAR_TASK();
    }
}
void I2C_DATA_COLLISION_ISR(void)
{
    I2C_DTAT_COLLISION_CLEAR_INTERRUPT_FLAG();
    if(I2C_DATA_COLLISION_INTERRUPT_HANDELAR_TASK)
    {
        I2C_DATA_COLLISION_INTERRUPT_HANDELAR_TASK();
    }
}
#endif