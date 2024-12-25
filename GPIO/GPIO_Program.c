/* 
 * File:   GPIO_Program
 * Author: ziad osama
 *
 * Created on September 15, 2024, 6:57 PM
 */

/* Section : Includes ________________________________________________________*/
#include "GPIO_Interface.h"
/* Section : Functions Definitions____________________________________"APIs"__*/
/**
 * @Function GPIO_PIN_DIRECTION_INTIALIZE 
 * @param    PIN_TARGET_CONFIG
 * @return   RET STATES OF THE FUNCTION
 */
#if PORT_PIN_CONFIGRATION == CONFIG_ENABLE
std_ReturnType GPIO_PIN_DIRECTION_INTIALIZE(const Pin_Config_t * PIN_TARGET_CONFIG)
{
    std_ReturnType RET = E_OK ;
    if((NULL == PIN_TARGET_CONFIG) || (PIN_TARGET_CONFIG->PIN > PORT_PIN_MAX_NUMBER - 1) || (PIN_TARGET_CONFIG->PORT > PORT_MAX_NUMBER - 1))
    {
        RET = E_NOT_OK ;
    }
    else
    {
        switch(PIN_TARGET_CONFIG->Direction)
        {
            case OUTPUT :
                CLEAR_BIT(*(TRIS_REGISTERS[PIN_TARGET_CONFIG->PORT]),PIN_TARGET_CONFIG->PIN) ;
                break ;
            case INPUT  : 
                SET_BIT(*(TRIS_REGISTERS[PIN_TARGET_CONFIG->PORT]),PIN_TARGET_CONFIG->PIN) ;
                break ;
            default     :
                RET = E_NOT_OK ;
        }
    }
    return (RET);
}
#endif
/**
 * 
 * @param PIN_TARGET_CONFIG
 * @param DIRECTION_STATUS OF THE PIN
 * @return RET STATES OF THE FUNCTION
 */
#if PORT_PIN_CONFIGRATION == CONFIG_ENABLE
std_ReturnType GPIO_PIN_GET_DIRECTION_STATUS( const Pin_Config_t * PIN_TARGET_CONFIG , Direction_t * DIRECTION_STATUS)
{
    std_ReturnType RET = E_OK ;
    if((NULL == PIN_TARGET_CONFIG) || (PIN_TARGET_CONFIG->PIN > PORT_PIN_MAX_NUMBER - 1) || (NULL == DIRECTION_STATUS) || (PIN_TARGET_CONFIG->PORT > PORT_MAX_NUMBER - 1))
    {
        RET = E_NOT_OK ;
    }
    {
        *DIRECTION_STATUS = READ_BIT(*(TRIS_REGISTERS[PIN_TARGET_CONFIG->PORT]),PIN_TARGET_CONFIG->PIN);
    }
    return (RET);
}
#endif

/**
 * @Function GPIO_PIN_WRITE_LOGIC
 * @param    PIN_TARGET_CONFIG
 * @param    LOGIC_PIN
 * @return   RET STATES OF THE FUNCTION
 */
#if PORT_PIN_CONFIGRATION == CONFIG_ENABLE
std_ReturnType GPIO_PIN_WRITE_LOGIC( const Pin_Config_t * PIN_TARGET_CONFIG, Logic_t LOGIC_PIN)
{
    std_ReturnType RET = E_OK ;
    if((NULL == PIN_TARGET_CONFIG) || (PIN_TARGET_CONFIG->PIN > PORT_PIN_MAX_NUMBER - 1) || (PIN_TARGET_CONFIG->PORT > PORT_MAX_NUMBER - 1))
    {
        RET = E_NOT_OK ;
    }
    else
    {
        switch(LOGIC_PIN)
        {
            case LOW  :
                CLEAR_BIT(*(LAT_REGISTERS[PIN_TARGET_CONFIG->PORT]),PIN_TARGET_CONFIG->PIN);
                break;
            case HIGH :
                SET_BIT(*(LAT_REGISTERS[PIN_TARGET_CONFIG->PORT]),PIN_TARGET_CONFIG->PIN);
                break;
            default   :
                RET = E_NOT_OK;
        }
    }
    return (RET);
}
#endif
/**
 * Function GPIO_PIN_READ_LOGIC
 * @param PIN_TARGET_CONFIG
 * @param LOGIC_PIN
 * @return RET STATES OF THE FUNCTION
 */
#if PORT_PIN_CONFIGRATION == CONFIG_ENABLE
std_ReturnType GPIO_PIN_READ_LOGIC(const Pin_Config_t * PIN_TARGET_CONFIG,Logic_t * LOGIC_PIN)
{
    std_ReturnType RET = E_OK ;
    if((NULL == PIN_TARGET_CONFIG) || (NULL == LOGIC_PIN) || (PIN_TARGET_CONFIG->PIN > PORT_PIN_MAX_NUMBER - 1) || (PIN_TARGET_CONFIG->PORT > PORT_MAX_NUMBER - 1))
    {
        RET = E_NOT_OK ;
    }
    else
    {
        *LOGIC_PIN = READ_BIT(*(PORT_REGISTERS[PIN_TARGET_CONFIG->PORT]),PIN_TARGET_CONFIG->PIN);
    }
    return (RET);
}
#endif
/**
 * Function GPIO_PIN_TOGGLE_LOGIC
 * @param PIN_TARGET_CONFIG
 * @return RET STATES OF THE FUNCTION
 */
#if PORT_PIN_CONFIGRATION == CONFIG_ENABLE
std_ReturnType GPIO_PIN_TOGGLE_LOGIC(const Pin_Config_t * PIN_TARGET_CONFIG)
{
    std_ReturnType RET = E_OK ;
    if((NULL == PIN_TARGET_CONFIG)  || (PIN_TARGET_CONFIG->PIN > PORT_PIN_MAX_NUMBER - 1) || (PIN_TARGET_CONFIG->PORT > PORT_MAX_NUMBER - 1))
    {
        RET = E_NOT_OK ;
    }
    else
    {
        TOGGLE_BIT(*(LAT_REGISTERS[PIN_TARGET_CONFIG->PORT]),PIN_TARGET_CONFIG->PIN);
    }
    return (RET);
}
#endif
/**
 * Function GPIO_PORT_DIRECTION_INTIALIZE
 * @param PORT_TARGET
 * @param DIRECTION
 * @return RET STATES OF THE FUNCTION
 */
#if PORT_CONFIGRATION == CONFIG_ENABLE
std_ReturnType GPIO_PORT_DIRECTION_INTIALIZE( PORT_Index_t PORT_TARGET, uint8 DIRECTION)
{
    std_ReturnType RET = E_OK ;
    if(PORT_TARGET > PORT_MAX_NUMBER - 1)
    {
        RET = E_NOT_OK ;
    }
    else
    {
        *(TRIS_REGISTERS[PORT_TARGET]) = DIRECTION ;
    }
    return (RET);
}
#endif
/**
 * Function GPIO_PORT_GET_DIRECTION_STATUS
 * @param PORT_TARGET
 * @param DIRECTION_STATUS
 * @return RET STATES OF THE FUNCTION
 */
#if PORT_CONFIGRATION == CONFIG_ENABLE
std_ReturnType GPIO_PORT_GET_DIRECTION_STATUS(PORT_Index_t PORT_TARGET , uint8 * DIRECTION_STATUS)
{
    std_ReturnType RET = E_OK ;
    if((PORT_TARGET > PORT_MAX_NUMBER - 1) || (NULL == DIRECTION_STATUS))
    {
        RET = E_NOT_OK ;
    }
    else
    {
        *DIRECTION_STATUS = *(TRIS_REGISTERS[PORT_TARGET]);
    }
    return (RET);
}
#endif
/**
 * Function GPIO_PORT_WRITE_LOGIC
 * @param PORT_TARGET
 * @param LOGIC_PORT
 * @return RET STATES OF THE FUNCTION
 */
#if PORT_CONFIGRATION == CONFIG_ENABLE
std_ReturnType GPIO_PORT_WRITE_LOGIC( PORT_Index_t PORT_TARGET,uint8 LOGIC_PORT)
{
    std_ReturnType RET = E_OK ;
    if(PORT_TARGET > PORT_MAX_NUMBER - 1)
    {
        RET = E_NOT_OK ;
    }
    else
    {
        *(LAT_REGISTERS[PORT_TARGET]) = LOGIC_PORT ;
    }
    return (RET);
}
#endif
/**
 * Function GPIO_PORT_READ_LOGIC
 * @param PORT_TARGET
 * @param LOGIC_PORT
 * @return RET STATES OF THE FUNCTION
 */
#if PORT_CONFIGRATION == CONFIG_ENABLE
std_ReturnType GPIO_PORT_READ_LOGIC(PORT_Index_t PORT_TARGET, uint8 * LOGIC_PORT)
{
    std_ReturnType RET = E_OK ;
     if((PORT_TARGET > PORT_MAX_NUMBER - 1) || (NULL == LOGIC_PORT))
    {
        RET = E_NOT_OK ;
    }
    else
    {
        *LOGIC_PORT = *(LAT_REGISTERS[PORT_TARGET]);
    }
    return (RET);
}
#endif
/**
 * Function GPIO_PORT_TOGGLE_LOGIC
 * @param PORT_TARGET
 * @return RET STATES OF THE FUNCTION
 */
#if PORT_CONFIGRATION == CONFIG_ENABLE
std_ReturnType GPIO_PORT_TOGGLE_LOGIC(PORT_Index_t PORT_TARGET)
{
    std_ReturnType RET = E_OK ;
    if(PORT_TARGET > PORT_MAX_NUMBER - 1)
    {
        RET = E_NOT_OK ;
    }
    else
    {
        *(LAT_REGISTERS[PORT_TARGET]) = *(LAT_REGISTERS[PORT_TARGET]) ^ 0xFF ;
    }
    return (RET);
}
#endif