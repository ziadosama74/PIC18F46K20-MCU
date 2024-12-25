/* 
 * File:   I2C_INTERFACE.h
 * Author: ziad osama
 *
 * Created on December 20, 2024, 2:42 PM
 */

#ifndef I2C_INTERFACE_H
#define	I2C_INTERFACE_H
/*_____________________________________________________________________________*/
/*                         Section : Includes                                  */
/*_____________________________________________________________________________*/
#include "../MSSP_REGISTERS.h"
#include "../../INTERRUPT/MCAL_INTERNAL_INTERRUPT.h"
#include "../../GPIO/GPIO_Interface.h"
/*_____________________________________________________________________________*/
/*                         Section : Macro Definitions                         */
/*_____________________________________________________________________________*/
#define I2C_ENABLE_PARAMETER                                              1
#define I2C_DISABLE_PARAMETER                                             0 
/*_____________________________________________________________________________*/
/*I2C Mode*/
#define I2C_MASTER_MODE                                                   1
#define I2C_SLAVE_MODE                                                    0
/*In Slave mode : Indicates Last Byte Is Data or Address*/
#define I2C_LAST_BYTE_DATA                                                1
#define I2C_LAST_BYTE_ADREESS                                             0
/*Indicates Start Bit*/
#define I2C_START_BIT_DETECTED                                            1
#define I2C_START_BIT_NOT_DETECTED                                        0
/*Indicates Stop Bit*/
#define I2C_STOP_BIT_DETECTED                                             1
#define I2C_STOP_BIT_NOT_DETECTED                                         0
/*MSSP Mode Select*/
#define I2C_Slave_mode_10bit_address_with_S_and_P_bit_interrupts_enabled 0x0FU
#define I2C_Slave_mode_7bit_address_with_S_and_P_bit_interrupts_enabled  0x0EU
#define I2C_Firmware_Controlled_Master_mode_Slave_Idle                   0x0BU
#define I2C_Master_mode_clock_IS_FOSC_Div_4_x_SSPADD_puls_one            0x08U
#define I2C_Slave_mode_10bit_address                                     0x07U
#define I2C_Slave_mode_7bit_address                                      0x06U
/*Acknowledge Status bit (Master Transmit mode only)*/
#define I2C_ACK_RECEIVED_FROM_SLAVE                                       0
#define I2C_ACK_NOT_RECEIVED_FROM_SLAVE                                   1
/*Acknowledge Data bit (Master Receive mode only)*/
#define I2C_MASTER_SEND_ACK                                               0
#define I2C_MASTER_SEND_NACK                                              1
/*_____________________________________________________________________________*/
/*                         Section : Macro Functions                           */
/*_____________________________________________________________________________*/
/*MSSP I2C Module Enable/Disable*/
#define MSSP_I2C_MODULE_ENABLE()                       (SET_BIT(SSPCON1,SSPEN))
#define MSSP_I2C_MODULE_DISABLE()                      (CLEAR_BIT(SSPCON1,SSPEN))
/*Slew Rate Enable/Disable*/
#define I2C_STANDARD_SPEED_MODE_100KHz_SLEW_DISABLE()  (SET_BIT(SSPSTAT,SMP))
#define I2C_HIGH_SPEED_MODE_400KHz_SLEW_ENABLE()       (CLEAR_BIT(SSPSTAT,SMP))
/*SMBus Enable/Disable*/
#define I2C_SMBUS_ENABLE()                             (SET_BIT(SSPSTAT,CKE))
#define I2C_SMBUS_DISABLE()                            (CLEAR_BIT(SSPSTAT,CKE))
/*General Call Enable/Disable*/
#define I2C_GENERAL_CALL_ADDRESS_ENABLE()              (SET_BIT(SSPCON2,GCEN))
#define I2C_GENERAL_CALL_ADDRESS_DISABLE()             (CLEAR_BIT(SSPCON2,GCEN))
/*Master Receiver Mode Enable/Disable*/
#define I2C_MASTER_RECEIVER_ENABLE()                   (SET_BIT(SSPCON2,RCEN))
#define I2C_MASTER_RECEIVER_DISABLE()                  (CLEAR_BIT(SSPCON2,RCEN))
/*Master Send Start Condition*/
#define I2C_MASTER_SEND_S_CON()                        (SET_BIT(SSPCON2,SEN))
#define I2C_MASTER_READ_S_CON()                        (READ_BIT(SSPCON2,SEN))
/*Master Send Stop Condition*/
#define I2C_MASTER_SEND_P_CON()                        (SET_BIT(SSPCON2,PEN))
#define I2C_MASTER_READ_P_CON()                        (READ_BIT(SSPCON2,PEN))
/*Master Send Repeated Start Condition*/
#define I2C_MASTER_SEND_SR_CON()                       (SET_BIT(SSPCON2,RSEN))
#define I2C_MASTER_READ_SR_CON()                       (READ_BIT(SSPCON2,RSEN))
/*Master Clear MSSP Interrupt Flag from S & P Condition*/
#define I2C_MASTER_CLEAR_MSSP_INTERRUPT_FALG()         (CLEAR_BIT(PIR1,SSPIF))
#define I2C_MASTER_GET_MSSP_INTERRUPT_FALG()           (READ_BIT(PIR1,SSPIF))
/*Detect Start Condition & Stop Condition on I2C Bus */
#define I2C_DETECT_S_CON()                             (READ_BIT(SSPSTAT,S))
#define I2C_DETECT_P_CON()                             (READ_BIT(SSPSTAT,P))
/*Acknowledge Status bit (Master Transmit mode only)*/
#define I2C_GET_ACK_STATUS_FROM_SLAVE()                (READ_BIT(SSPCON2,ACKSTAT))
/*Data Register Status Buffer Register*/
#define I2C_GET_STATUS_DATA_BUFFER_REGISTER()          (READ_BIT(SSPSTAT,BF))
/*Acknowledge Data bit (Master Receive mode only)*/
#define I2C_MASTER_SEND_ACK_BIT()                      (CLEAR_BIT(SSPCON2,ACKDT))
#define I2C_MASTER_SEND_NACK_BIT()                     (SET_BIT(SSPCON2,ACKDT))
/*Acknowledge Sequence Enable bit (Master Receive mode only)*/
/*Initiates Acknowledge sequence on SDA and SCL pins and transmit ACKDT data bit.
  Automatically cleared by hardware*/
#define I2C_MASTER_INITE_ACK_SEQ()                     (SET_BIT(SSPCON2,ACKEN))
/*In Slave Transmit mode: WCOL: Write Collision Detect bit*/
#define I2C_SLAVE_CLEAR_COLLISION_DATA_DETECT()        (CLEAR_BIT(SSPCON1,WCOL))
/*Receive Overflow Indicator bit In Receive mode: 1 = A byte is received while 
the SSPBUF register is still holding the previous byte (must be cleared in software)*/
#define I2C_CLEAR_RECEIVE_OVERFLOW_FLAG()              (CLEAR_BIT(SSPCON1,SSPOV))
/* SCK Release Control bit In Slave mode: 1 = Releases clock*/
#define I2C_SLAVE_RELEASE_CLOCK()                      (SET_BIT(SSPCON1,CKP))
#define I2C_SLAVE_STRETCH_CLOCK()                      (CLEAR_BIT(SSPCON1,CKP))
/*_____________________________________________________________________________*/
/*                         Section : Data Types Declaration                    */
/*_____________________________________________________________________________*/
typedef struct 
{
    uint8 I2C_Mode_Cfg;                 /*MSSP Mode Select*/
    uint8 I2C_Slave_Address;            /*I2C Slave Address*/
    uint8 I2C_Mode:1;                   /*I2C : Master or Slave*/
    uint8 I2C_Slew_Rate:1;              /*Slew Rate Enable/Disable-SS-HS*/
    uint8 I2C_SMBus_Control:1;          /*SMBus Enable/Disable*/
    uint8 I2C_General_Call:1;           /*General Call Enable/Disable*/
    uint8 I2C_Master_Receiver_Mode:1;   /*Master Receiver Mode Enable/Disable*/
    uint8 I2C_Reaseved:3;
}I2C_Config;

typedef struct 
{
    uint32 I2C_Clock;  /*I2C Mater Clock Speed Frequency*/
    #if  I2C_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    void (*I2C_Report_Write_Collision)(void);    /*Write Collision Indicator*/
    INTERRUPT_PRIORITY I2C_Report_Write_Collision_Priority;
    void (*I2C_Default_Interrupt_Handler)(void); /*I2C Interrupt Handler */
    INTERRUPT_PRIORITY I2C_Default_Interrupt_Handler_Priority;
    void (*I2C_Report_Receive_Overflow)(void);   /*Receiver Overflow Indicator*/
    #endif
    I2C_Config I2C_Cfg;
}I2C_t;
/*_____________________________________________________________________________*/
/*                         Section : APIs Declaration                          */
/*_____________________________________________________________________________*/
std_ReturnType I2C_INITIALIZE(const I2C_t * i2c);
std_ReturnType I2C_DEINITIALIZE(const I2C_t * i2c);
std_ReturnType I2C_MASTER_SEND_STATRT(const I2C_t * i2c);
std_ReturnType I2C_MASTER_SEND_REPEATED_STATRT(const I2C_t * i2c);
std_ReturnType I2C_MASTER_SEND_STOP(const I2C_t * i2c);
std_ReturnType I2C_MASTER_WRITE_DATA(const I2C_t * i2c,uint8 Data,uint8 * ack);
std_ReturnType I2C_MASTER_READ_DATA(const I2C_t * i2c,uint8 ack,uint8 * Data);

#endif	/* I2C_INTERFACE_H */

