/*
*************** NVIC_interface.h ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/
 
#include "std_types.h"
#include "bit_math.h"


#define ENABLE  1
#define DISABLE 0

#define NVIC_MAX_IRQ_NUMBER      240U
#define NVIC_BITS_PER_REG        32U
#define NVIC_PRIORITY_BITS_SHIFT 4U

Std_ReturnType NVIC_IRQInterruptConfig(u8 copy_u8State,u8 copy_u8IRQNumber);
Std_ReturnType NVIC_IRQPriorityConfig(u8 copy_IRQNumber,u8 copy_IRQpriority);


 
 
 
 
 
