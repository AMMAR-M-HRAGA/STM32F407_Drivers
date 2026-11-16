/*
*************** GPIO_config.h ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/

#ifndef GPIO_CONFIG_H
#define GPIO_CONFIG_H
#include "GPIO_interface.h"
#include "GPIO_private.h"

/****** CLOCK CONFIGURATION ******/

#define GPIOA_CLK_STATE DISABLE
#define GPIOB_CLK_STATE DISABLE
#define GPIOC_CLK_STATE DISABLE
#define GPIOD_CLK_STATE DISABLE
#define GPIOE_CLK_STATE DISABLE


/****** PIND12 CONFIGURATION ******/

// @breif  : Select GPIO
// Options : GPIOA , GPIOB , GPIOC , GPIOD , GPIOE

#define PIN1_PORT       GPIOD

// @breif  : Pin Number Of GPIOx
// Options : GPIO_PIN_NO_0 , GPIO_PIN_NO_1 ,...,GPIO_PIN_NO_7

#define PIN1_PIN_NUMBER GPIO_PIN_NO_12

// @breif  : The Mode of Pin1
// Options : GPIO_MODE_OUT , GPIO_MODE_INPUT , GPIO_MODE_AF , GPIO_MODE_ANALOG

#define PIN1_PIN_MODE   GPIO_MODE_OUT

// @breif  : The Speed of pin1 
// Options : GPIO_SPEED_LOW , GPIO_SPEED_MID , GPIO_SPEED_FAST , GPIO_SPEED_V_FAST

#define PIN1_SPEED      GPIO_SPEED_FAST

// @breif  : Select The Pull-Up Pull-Down
// Options : GPIO_NO_PUPD , GPIO_PIN_PU , GPIO_PIN_PD

#define PIN1_PUPD_STATE GPIO_NO_PUPD

// @breif  : The Type of OUTPUT State  
// Options : GPIO_OP_TYPE_PP , GPIO_OP_TYPE_OD

#define PIN1_PPOD_TYPE  GPIO_OP_TYPE_PP

// @breif  : The Mode Of AF 
// Options : AF0 , AF1 , ... ,AF15

#define PIN1_AF_MODE    AF0 

static GPIO_PinConfig_t PIN12_Config = {

    .GPIOx = PIN1_PORT,
    .PinNumber = PIN1_PIN_NUMBER,
    .PinMode = PIN1_PIN_MODE,
    .SpeedType = PIN1_SPEED,
    .PullType = PIN1_PUPD_STATE,
    .OutPutType = PIN1_PPOD_TYPE,
    .AFMode = PIN1_AF_MODE,

};




/****** PINA13 CONFIGURATION ******/


#define PIN2_PORT       GPIOD
#define PIN2_PIN_NUMBER GPIO_PIN_NO_13
#define PIN2_PIN_MODE   GPIO_MODE_OUT
#define PIN2_SPEED      GPIO_SPEED_FAST
#define PIN2_PUPD_STATE GPIO_NO_PUPD
#define PIN2_PPOD_TYPE  GPIO_OP_TYPE_PP
#define PIN2_AF_MODE    AF0


static GPIO_PinConfig_t PIN13_Config = {

    .GPIOx = PIN2_PORT,
    .PinNumber = PIN2_PIN_NUMBER,
    .PinMode = PIN2_PIN_MODE,
    .SpeedType = PIN2_SPEED,
    .PullType = PIN2_PUPD_STATE,
    .OutPutType = PIN2_PPOD_TYPE,
    .AFMode = PIN2_AF_MODE,

};



/****** PIND14 CONFIGURATION ******/

#define PIN3_PORT       GPIOD
#define PIN3_PIN_NUMBER GPIO_PIN_NO_14
#define PIN3_PIN_MODE   GPIO_MODE_OUT
#define PIN3_SPEED      GPIO_SPEED_FAST
#define PIN3_PUPD_STATE GPIO_NO_PUPD
#define PIN3_PPOD_TYPE  GPIO_OP_TYPE_PP
#define PIN3_AF_MODE    AF0

static GPIO_PinConfig_t PIN14_Config = {

    .GPIOx = PIN3_PORT,
    .PinNumber = PIN3_PIN_NUMBER,
    .PinMode = PIN3_PIN_MODE,
    .SpeedType = PIN3_SPEED,
    .PullType = PIN3_PUPD_STATE,
    .OutPutType = PIN3_PPOD_TYPE,
    .AFMode = PIN3_AF_MODE,

};



/****** PIND15 CONFIGURATION ******/

#define PIN4_PORT       GPIOD
#define PIN4_PIN_NUMBER GPIO_PIN_NO_15
#define PIN4_PIN_MODE   GPIO_MODE_OUT
#define PIN4_SPEED      GPIO_SPEED_FAST
#define PIN4_PUPD_STATE GPIO_NO_PUPD
#define PIN4_PPOD_TYPE  GPIO_OP_TYPE_PP
#define PIN4_AF_MODE    AF0

static GPIO_PinConfig_t PIN15_Config = {

    .GPIOx = PIN4_PORT,
    .PinNumber = PIN4_PIN_NUMBER,
    .PinMode = PIN4_PIN_MODE,
    .SpeedType = PIN4_SPEED,
    .PullType = PIN4_PUPD_STATE,
    .OutPutType = PIN4_PPOD_TYPE,
    .AFMode = PIN4_AF_MODE,

};


#endif
