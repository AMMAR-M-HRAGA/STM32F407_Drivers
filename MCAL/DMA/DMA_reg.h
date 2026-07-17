/*
*************** DMA_reg.h ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/

#ifndef DMA_REG_H
#define DMA_REG_H

#include "std_types.h"  

typedef struct {
	volatile u32 CR;
	volatile u32 NDTR;
	volatile u32 PAR;
	volatile u32 M0AR;
	volatile u32 M1AR;
	volatile u32 FCR;
}DMA_Stream_TypeDef;



typedef struct {
	
	volatile u32 LISR;
	volatile u32 HISR;
	volatile u32 LICFR;
	volatile u32 HICFR;
	DMA_Stream_TypeDef Streams[8];
}DMA_TypeDef;

#define DMA1_BASE_ADDRESS (0x40026000UL)
#define DMA2_BASE_ADDRESS (0x40026400UL)

#define DMA1     ((DMA_TypeDef*)DMA1_BASE_ADDRESS)
#define DMA2     ((DMA_TypeDef*)DMA2_BASE_ADDRESS)


#endif



















