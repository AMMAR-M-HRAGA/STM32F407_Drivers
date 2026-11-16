/*
*************** NVIC_program.c ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/

#include "NVIC_reg.h"
#include "NVIC_interface.h"
#include "std_types.h"


Std_ReturnType NVIC_IRQInterruptConfig(u8 copy_u8State,u8 copy_u8IRQNumber)
{
	
	
	Std_ReturnType Local_u8ErrorState = E_OK;
	
	if(copy_u8IRQNumber >= NVIC_MAX_IRQ_NUMBER)
	{
		Local_u8ErrorState = E_NOT_OK;
	}
	else
	{
		u8 local_u8RegisterIndex = copy_u8IRQNumber/NVIC_BITS_PER_REG;
		u8 local_u8BitPosition = copy_u8IRQNumber %NVIC_BITS_PER_REG;
		
		if (copy_u8State == ENABLE)
		{
			NVIC->ISER[local_u8RegisterIndex] |= (1UL <<local_u8BitPosition);
			
		}
		else if (copy_u8State == DISABLE)
		{
			NVIC->ICER[local_u8RegisterIndex] |= (1UL<<local_u8BitPosition);
		}
		else
		{
			// do nothing.
		}	
		
	}
    
	return Local_u8ErrorState;

}


Std_ReturnType NVIC_IRQPriorityConfig(u8 copy_IRQNumber,u8 copy_IRQpriority)
{
	Std_ReturnType Local_u8ErrorState = E_OK;
	
	if(copy_IRQNumber >= NVIC_MAX_IRQ_NUMBER)
	{
		Local_u8ErrorState = E_NOT_OK;
	}
	else 
	{
	    NVIC->IPR[copy_IRQNumber]  = 0x00U;
		NVIC->IPR[copy_IRQNumber] |= (copy_IRQpriority << NVIC_PRIORITY_BITS_SHIFT);
			
	}

	return Local_u8ErrorState;

}

