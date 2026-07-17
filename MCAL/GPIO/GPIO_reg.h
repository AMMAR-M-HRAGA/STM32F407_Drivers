/*
*************** GPIO_reg.h ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/


#ifndef GPIO_REG_H
#define GPIO_REG_H

#include "std_types.h"


#define GPIOA_BASE_ADDRESS  (0x40020000UL)
#define GPIOB_BASE_ADDRESS  (0x40020400UL)
#define GPIOC_BASE_ADDRESS  (0x40020800UL)
#define GPIOD_BASE_ADDRESS  (0x40020C00UL)
#define GPIOE_BASE_ADDRESS  (0x40021000UL)
#define GPIOF_BASE_ADDRESS  (0x40021400UL)
#define GPIOG_BASE_ADDRESS  (0x40021800UL)
#define GPIOH_BASE_ADDRESS  (0x40021C00UL)
#define GPIOI_BASE_ADDRESS  (0x40022000UL)

typedef struct{
	volatile u32 MODER;
	volatile u32 OTYPER;
	volatile u32 OSPEEDR;
	volatile u32 PUPDR;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u32 BSRR;
	volatile u32 LCKR;
	volatile u32 AFR[2];
}GPIO_TypeDef;


#define GPIOA   ((GPIO_TypeDef*)GPIOA_BASE_ADDRESS)
#define GPIOB   ((GPIO_TypeDef*)GPIOB_BASE_ADDRESS)
#define GPIOC   ((GPIO_TypeDef*)GPIOC_BASE_ADDRESS)
#define GPIOD   ((GPIO_TypeDef*)GPIOD_BASE_ADDRESS)
#define GPIOE   ((GPIO_TypeDef*)GPIOE_BASE_ADDRESS)
#define GPIOF   ((GPIO_TypeDef*)GPIOF_BASE_ADDRESS)
#define GPIOG   ((GPIO_TypeDef*)GPIOG_BASE_ADDRESS)
#define GPIOH   ((GPIO_TypeDef*)GPIOH_BASE_ADDRESS)
#define GPIOI   ((GPIO_TypeDef*)GPIOI_BASE_ADDRESS)

#define RCC_BASE_ADDRESS 0x40023800UL
#define RCC_AHB1ENR  (*((volatile u32*)(RCC_BASE_ADDRESS+0x30)))






















#endif
