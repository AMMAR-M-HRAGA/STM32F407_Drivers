/*
*************** NVIC_program.c ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/

#include "NVIC_reg.h"
#include "NVIC_interface.h"
#include "std_types.h"


void NVIC_IRQInterruptConfig(u8 copy_u8ENorDI,u8 copy_u8IRQNumber)
{

    u8 local_u8RegisterIndex = copy_u8IRQNumber/32;
	u8 local_u8BitPosition = copy_u8IRQNumber %32;
	
	if (copy_u8ENorDI == ENABLE)
	{
		NVIC->ISER[local_u8RegisterIndex] |= (1<<local_u8BitPosition);
		
	}
	else if (copy_u8ENorDI == DISABLE)
	{
		NVIC->ICER[local_u8RegisterIndex] |= (1<<local_u8BitPosition);
	}

    

}


void NVIC_IRQPriorityConfig(u8 copy_IRQNumber,u8 copy_IRQpriority)
{
	if(copy_IRQNumber < 240)
	{
		NVIC->IPR[copy_IRQNumber]  = 0x00;
		NVIC->IPR[copy_IRQNumber] |= (copy_IRQpriority << 4);
	}

}

