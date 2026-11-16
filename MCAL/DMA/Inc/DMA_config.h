/*
*************** DMA_config.h ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/


#ifndef DMA_CONFIG_H
#define DMA_CONFIG_H

#include "DMA_interface.h"
#include "DMA_reg.h"

/******* DMA2 STREAM0 ******/ 


#define CHANNAL                       STREAM0

#define MEMORY_SIZE                   DMA_M_SIZE_32

#define PREPH_SIZE 					  DMA_P_SIZE_32

#define MEMORY_INCERMENT 			  M_INCREMENT_ENABLE

#define PERIPHERAL_INCERMENT          P_INCREMENT_ENABLE

#define CIRCULAR_MODE                 CIRCULAR_MODE_DISABLE

#define DATA_DIRECTION                MEMORY_TO_MEMORY

#define DMA_PRIORITY_LEVEL            DMA_PRIORITY_HIGH

#define DMA_BOUBLE_BUFF_MODE          DOUBLE_BFF_DISABLE

#define DMA_MEMORY_BURST              DMA_BURST_SINGLE

#define DMA_PERIPH_BURST              DMA_BURST_SINGLE

#define TRANS_C_INT_SELECT 		      DMA_T_COMPLETE_INT_ENABLE

#define TRANS_H_INT_SELECT            DMA_T_HALF_INT_ENABLE

#define TRANS_E_INT_SELECT			  DMA_T_ERROR_INT_DISABLE

#define TRANS_DIRECT_E_INT_SELECT	  DMA_DIRECT_MODE_ENABLE

#define DMA_SELECT                    DMA_ENABLE


static DMA_Config_t DMA2_Stream0_Config = {
	.Channal = CHANNAL ,
	.Direction = DATA_DIRECTION,
	.priority = DMA_PRIORITY_LEVEL,
	.MSize = MEMORY_SIZE,
	.PSize = PREPH_SIZE,
	.CircularMode = CIRCULAR_MODE,
	.MemInc = MEMORY_INCERMENT,
	.PeriphInc = PERIPHERAL_INCERMENT,
	.DoubleBufferMode = DMA_BOUBLE_BUFF_MODE,
	.MemBurst = DMA_MEMORY_BURST,
	.periphBurst = DMA_PERIPH_BURST,
	.CompleteINT = TRANS_C_INT_SELECT,
	.HalfINT = TRANS_H_INT_SELECT,
	.TransferErorrINT = TRANS_E_INT_SELECT,
	.ErorrDirectINT = TRANS_DIRECT_E_INT_SELECT ,
};  








#endif







