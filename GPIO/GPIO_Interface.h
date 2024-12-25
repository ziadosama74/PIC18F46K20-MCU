/* 
 * File:   GPIO_Interface.h
 * Author: ziad osama
 *
 * Created on September 15, 2024, 7:09 PM
 */

#ifndef GPIO_INTERFACE_H
#define	GPIO_INTERFACE_H

/* Section : Includes__________________________*/

#include "pic18f4620.h"
#include "../MCAL_STD_TYPES.h"
#include "../../Device_Config.h"
/* Section : Macro Declaration ________________*/ 
#define PORT_PIN_MAX_NUMBER                8
#define PORT_MAX_NUMBER                    5
#define TRIS_REGISTERS_SIZE                5
#define LAT_REGISTERS_SIZE                 5
#define PORT_REGISTERS_SIZE                5
#define PORT_PIN_CONFIGRATION        CONFIG_ENABLE
#define PORT_CONFIGRATION            CONFIG_ENABLE

/* Section : Registers Driver GPIO       ______*/

#define    TRISA                      HWREG8(0xF92)
#define    TRISB                      HWREG8(0xF93)
#define    TRISC                      HWREG8(0xF94)
#define    TRISD                      HWREG8(0xF95)
#define    TRISE                      HWREG8(0xF96)

#define    LATA                       HWREG8(0xF89)
#define    LATB                       HWREG8(0xF8A)
#define    LATC                       HWREG8(0xF8B)
#define    LATD                       HWREG8(0xF8C)
#define    LATE                       HWREG8(0xF8D)

#define    PORTA                      HWREG8(0xF80)
#define    PORTB                      HWREG8(0xF81)
#define    PORTC                      HWREG8(0xF82)
#define    PORTD                      HWREG8(0xF83)
#define    PORTE                      HWREG8(0xF84)

volatile uint8 * TRIS_REGISTERS[TRIS_REGISTERS_SIZE] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
volatile uint8 * LAT_REGISTERS[LAT_REGISTERS_SIZE]   = {&LATA, &LATB, &LATC, &LATD, &LATE};
volatile uint8 * PORT_REGISTERS[PORT_REGISTERS_SIZE] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};
/* Section : Macro Declaration Functions ______*/

/* Section : Data Types Declaration ___________*/

typedef enum                                                                    // Logic Enumeration 
{
    LOW = 0,
    HIGH
}Logic_t ;

typedef enum                                                                    // Direction Enumeration 
{
    OUTPUT = 0,
    INPUT
}Direction_t ;

typedef enum                                                                    // Pins Enumeration 
{
    PIN0 = 0 ,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7
}Pin_Index_t;

typedef enum                                                                    // Ports Enumeration
{
    PORTA_INDEX,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX
}PORT_Index_t;

typedef struct                                                                  // Pin configuration Structure
{
    uint8 PORT      : 3 ;
    uint8 PIN       : 3 ;
    uint8 Direction : 1 ;
    uint8 LOGIC     : 1 ;
}Pin_Config_t;

/* Section : Functions Declaration____"APIs"__*/

/*_____1______________ GPIO_PIN_DIRECTION_INTIALIZE Function ________________*/
std_ReturnType GPIO_PIN_DIRECTION_INTIALIZE
(
    const Pin_Config_t * PIN_TARGET_CONFIG
);

/*_____2______________ GPIO_PIN_GET_DIRECTION_STATUS Function _______________*/

std_ReturnType GPIO_PIN_GET_DIRECTION_STATUS
(
    const Pin_Config_t * PIN_TARGET_CONFIG ,
    Direction_t * DIRECTION_STATUS
);

/*_____3______________ GPIO_PIN_WRITE_LOGIC Function ________________________*/

std_ReturnType GPIO_PIN_WRITE_LOGIC
(
    const Pin_Config_t * PIN_TARGET_CONFIG,
    Logic_t LOGIC_PIN
);

/*_____4______________ GPIO_PIN_READ_LOGIC Function __________________________*/

std_ReturnType GPIO_PIN_READ_LOGIC
(
    const Pin_Config_t * PIN_TARGET_CONFIG,
    Logic_t * LOGIC_PIN
);

/*_____5______________ GPIO_PIN_TOGGLE_LOGIC Function ________________________*/

std_ReturnType GPIO_PIN_TOGGLE_LOGIC
(
    const Pin_Config_t * PIN_TARGET_CONFIG
);

/*____6_______________ GPIO_PORT_DIRECTION_INTIALIZE Function ________________*/

std_ReturnType GPIO_PORT_DIRECTION_INTIALIZE
(
    PORT_Index_t PORT_TARGET,
    uint8 DIRECTION
);

/*____7_______________ GPIO_PORT_GET_DIRECTION_STATUS Function _______________*/
std_ReturnType GPIO_PORT_GET_DIRECTION_STATUS
(
    PORT_Index_t PORT_TARGET ,
    uint8 * DIRECTION_STATUS
);
/*____8______________ GPIO_PORT_WRITE_LOGIC Function _________________________*/

std_ReturnType GPIO_PORT_WRITE_LOGIC
(
    PORT_Index_t PORT_TARGET,
    uint8 LOGIC_PORT
);

/*____9_______________ GPIO_PORT_READ_LOGIC Function _________________________*/

std_ReturnType GPIO_PORT_READ_LOGIC
(
    PORT_Index_t PORT_TARGET,
    uint8 * LOGIC_PORT
);

/*___10________________ GPIO_PORT_TOGGLE_LOGIC Function ______________________*/

std_ReturnType GPIO_PORT_TOGGLE_LOGIC
(
    PORT_Index_t PORT_TARGET
);

#endif	/* GPIO_INTERFACE_H */

