/* 
 * File:   SPI_INTERFACE.h
 * Author: ziad osama
 *
 * Created on December 9, 2024, 9:34 PM
 */

#ifndef SPI_INTERFACE_H
#define	SPI_INTERFACE_H
/*_____________________________________________________________________________*/
/*                         Section : Includes                                  */
/*_____________________________________________________________________________*/
#include "../MSSP_REGISTERS.h"
#include "../../INTERRUPT/MCAL_INTERNAL_INTERRUPT.h"
#include "../../GPIO/GPIO_Interface.h"
/*_____________________________________________________________________________*/
/*                         Section : Macro Definitions                         */
/*_____________________________________________________________________________*/
#define   SPI_MASTER_MODE                                             1
#define   SPI_SLAVE_MODE                                              0

#define   SPI_DATA_REGISTER_RECEIVE_MODE_IS_FULL                      1
#define   SPI_DATA_REGISTER_RECEIVE_MODE_IS_EMPTY                     0


#define   SPI_SAMPLE_SLAVE                                            0
#define   SPI_SAMPLE_MASTER_MID                                       1
#define   SPI_SAMPLE_MASTER_END                                       2
/*_____________________________________________________________________________*/
/*                         Section : Macro Functions                           */
/*_____________________________________________________________________________*/
#define   SPI_DATA_REGISTER_RECEIVE_MODE_STATUS()       (READ_BIT(SSPSTAT,BF))
/*_____________________________________________________________________________*/
#define   SPI_TRANSMIT_FROM_ACTIVE_TO_IDLE_CLOCK()      (SET_BIT(SSPSTAT,CKE))
#define   SPI_TRANSMIT_FROM_IDLE_TO_ACTIVE_CLOCK()      (CLEAR_BIT(SSPSTAT,CKE))
/*_____________________________________________________________________________*/
#define   SPI_IDLE_STATE_HIGH()                         (SET_BIT(SSPCON1,CKP))
#define   SPI_IDLE_STATE_LOW()                          (CLEAR_BIT(SSPCON1,CKP))
/*_____________________________________________________________________________*/
#define   SPI_ENABLE()                                 (SET_BIT(SSPCON1,SSPEN))
#define   SPI_DISABLE()                                (CLEAR_BIT(SSPCON1,SSPEN))
/*_____________________________________________________________________________*/
#define   SPI_SAMPLE_SLAVE_MODE_AND_MID_DATA_OUTPUT()  (CLEAR_BIT(SSPSTAT,SMP))
#define   SPI_SAMPLE_MASTER_MODE_END_DATA_OUTPUT()     (SET_BIT(SSPSTAT,SMP))
/*_____________________________________________________________________________*/
#define   SPI_RECEIVE_SLAVE_MODE_READ_OVER_FLOW_BYTES() (READ_BIT(SSPCON1,SSPOV)) /*At The Slave Mode*/
#define   SPI_RECEIVE_SLAVE_MODE_CLEAR_OVER_FLOW_BYTES()(CLEAR_BIT(SSPCON1,SSPOV))
/*_____________________________________________________________________________*/
#define   SPI_READ_COLLISION_DATA_TRANSMITTING_FLAG()   (READ_BIT(SSPCON1,WCOL))
#define   SPI_CLEAR_COLLISION_DATA_TRANSMITTING_FLAG()  (CLEAR_BIT(SSPCON1,WCOL))
/*_____________________________________________________________________________*/
/*                         Section : Data Types Declaration                    */
/*_____________________________________________________________________________*/
typedef enum 
{
  SPI_Master_mode_clock_FOSC_4 = 0 ,
  SPI_Master_mode_clock_FOSC_16,
  SPI_Master_mode_clock_FOSC_64,
  SPI_Master_mode_clock_TMR2_DIV_2,
  SPI_Slave_mode_SCK_SS_ENABLED,
  SPI_Slave_mode_SCK_SS_DISABLED   /*SS can be used as I/O pin*/
}SPI_Mode_t;

typedef enum
{
    from_low_to_low,
    from_high_to_low,
    from_low_to_high,
    from_high_to_high,
}SPI_Bus_Mode_Data_Transmitting_t ;
typedef struct
{
    #if  SPI_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    void (*SPI_Interrupt_Handler)(void);
    INTERRUPT_PRIORITY SPI_Interrupt_Priority;
    #endif
    SPI_Mode_t SPI_Mode;//
    SPI_Bus_Mode_Data_Transmitting_t SPI_Data_Transmitting_Transition;//
    uint8 SPI_Sample_Mode :1;//
    Pin_Config_t MISO;
    Pin_Config_t MOSI;
    Pin_Config_t SCK;
    Pin_Config_t SS;
}SPI_t;
/*_____________________________________________________________________________*/
/*                         Section : APIs Declaration                          */
/*_____________________________________________________________________________*/
std_ReturnType SPI_INITIALIZE(const SPI_t * spi);
std_ReturnType SPI_DEINITIALIZE(const SPI_t * spi);

std_ReturnType SPI_MASTER_SEND_BYTE(const SPI_t * spi,const Pin_Config_t * SS_Slave,uint8 DataByte);
std_ReturnType SPI_MASTER_RECEIVE_BYTE(const SPI_t * spi,const Pin_Config_t * SS_Slave,uint8 *DataByte);

std_ReturnType SPI_SLAVE_SEND_BYTE(const SPI_t * spi,uint8 DataByte);
std_ReturnType SPI_SLAVE_RECEIVE_BYTE(const SPI_t * spi,uint8 *DataByte);
#endif	/* SPI_INTERFACE_H */

