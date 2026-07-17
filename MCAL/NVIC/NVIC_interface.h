/*
*************** NVIC_interface.h ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/
 
#include "std_types.h"
#include "bit_math.h"


#define ENABLE  1
#define DISABLE 0


void NVIC_IRQInterruptConfig(u8 copy_u8ENorDI,u8 copy_u8IRQNumber);
void NVIC_IRQPriorityConfig(u8 copy_IRQNumber,u8 copy_IRQpriority);


 
 
 
 
 
