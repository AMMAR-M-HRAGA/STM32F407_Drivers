/*
*************** DMA_config.h ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/
#include "DMA_reg.h"


#define STREAM                        DMA2_STREAM0

#define CHANNAL                       DMA_CHANNAL0

#define MEMORY_SIZE                   DMA_M_SIZE_32

#define PREPH_SIZE 					  DMA_P_SIZE_16  

#define MEMORY_INCERMENT 			  M_INCREMENT_ENABLE

#define PERIPHERAL_INCERMENT          P_INCREMENT_DISABLE

#define CIRCULAR_MODE                 CIRCULAR_MODE_DISABLE

#define DATA_DIRECTION                MEMORY_TO_MEMORY

#define DMA_PRIORITY_LEVEL            DMA_PRIORITY_HIGH

#define DMA_BOUBLE_BUFF_MODE          DOUBLE_BFF_DISALBE

#define DMA_MEMORY_BURST              DMA_BURST_SINGLE

#define DMA_PERIPH_BURST              DMA_BURST_SINGLE


#define TRANS_C_INT_SELECT 		      DMA_T_COMPLETE_INT_ENABLE

#define TRANS_H_INT_SELECT            DMA_T_HALF_INT_ENABLE

#define TRANS_E_INT_SELECT			  DMA_T_ERROR_INT_DISABLE

#define TRANS_DIRECT_E_INT_SELECT	  DMA_DIRECT_MODE_ENABLE

#define DMA_SELECT                    DMA_DISABLE










