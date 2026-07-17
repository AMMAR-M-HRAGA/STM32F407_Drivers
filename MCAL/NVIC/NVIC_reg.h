/*
*************** NVIC_reg.h ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/
 
 
 
#ifndef NVIC_REG_H
#define NVIC_REG_H


#include "std_types.h"

#define NVIC_BASE_ADDRESS 0xE000E100UL

typedef struct {
	
	volatile u32 ISER[8];
	volatile u32 Reserved0[24];
	
	volatile u32 ICER[8];
	volatile u32 Reserved1[24];
	
	volatile u32 ISPR[8];
	volatile u32 Reserved2[24];
	
	volatile u32 ICPR[8];
	volatile u32 Reserved3[24];
	
	volatile u32 IABR[8];
	volatile u32 Reserved4[56];
	
	volatile u8 IPR[240];

	
}NVIC_TypeDef;


#define NVIC       ((NVIC_TypeDef*)NVIC_BASE_ADDRESS)



















#endif
