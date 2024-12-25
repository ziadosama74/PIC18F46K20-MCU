/* 
 * File:   MCAL_STD_TYPES.h
 * Author: ziad osama
 *
 * Created on September 15, 2024, 7:13 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H
/* Section : Includes__________________________*/

#include "STD_Libraries.h"
#include "Compiler.h"
#define _XTAL_FREQ                8000000
/* Section : Data Types Declaration ___________*/

typedef unsigned char          uint8;
typedef unsigned short        uint16;
typedef unsigned int          uint32;
typedef signed char            sint8;
typedef signed short          sint16;
typedef signed int            sint32;

typedef uint8         std_ReturnType;                                           // this standard Type will be given to the functions to return the status of the functions .

/* Section : Macro Declaration ________________*/
#define BIT_MASK   (uint8)           1   
#define STD_HIGH                   0x01  
#define STD_LOW                    0x00     

#define STD_ON                     0x01  
#define STD_OFF                    0x00  

#define STD_ACTIVE                 0x01  
#define STD_IDEL                   0x00  

#define E_OK       (std_ReturnType)0x01                                         // Here I make an Explaced Casting to this value to (std_ReturnType) 
#define E_NOT_OK   (std_ReturnType)0x00                                         // Here I make an Explaced Casting to this value to (std_ReturnType)

#define CONFIG_ENABLE              0x01  
#define CONFIG_DISABLE             0x00 
#define     TRUE                     1
#define     FALSE                    0
/* Section : Macro Declaration Functions ______*/

#define HWREG8(_X)                 (*((volatile uint8 *)(_X)))                  // _X is Presented to The Address of The Register
#define SET_BIT(REG,BIT_POSN)      REG|=(BIT_MASK<<BIT_POSN)
#define CLEAR_BIT(REG,BIT_POSN)    REG&=~(BIT_MASK<<BIT_POSN)
#define TOGGLE_BIT(REG,BIT_POSN)   REG^=(BIT_MASK<<BIT_POSN)
#define READ_BIT(REG,BIT_POSN)     ((REG>>BIT_POSN)&BIT_MASK)
/* Section : Functions Declaration_____________*/


#endif	/* MCAL_STD_TYPES_H */

