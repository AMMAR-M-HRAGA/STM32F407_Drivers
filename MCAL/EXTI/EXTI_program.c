/*
*************** EXTI_program.c ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/

#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_reg.h"
#include "EXTI_config.h"
#include "std_types.h"
#include "bit_math.h"



static void (*GP_IRQ_Callback[16])(void) = {NULL};



void EXTI_voidInitConfig()
{
	
	SET_BIT(RCC_APB2ENR,SYSCFGEN);// Enable SYSCFG.
	
	SET_BIT(RCC_APB2LPENR,SYSCFGLPEN); // Enable SYSCFG at sleep mode.
	
	u8 regNumber =  EXTI_LINE /4; 
	
	u8 EXTINumber = EXTI_LINE %4; 
	
	SYSCFG->EXTICR[regNumber] &= ~(0xFUL << (EXTINumber*4));
	 
	SYSCFG->EXTICR[regNumber] |= EXTI_PORT<< (EXTINumber*4);
	
	
	
	
		
	#if EXTI_EDGE == EXTI_RISING_EDGE
		
		CLR_BIT(EXTI->FTSR,EXTI_LINE);
		SET_BIT(EXTI->RTSR,EXTI_LINE);
	
	#elif EXTI_EDGE == EXTI_FALLING_EDGE
	
	    CLR_BIT(EXTI->RTSR,EXTI_LINE);
		SET_BIT(EXTI->FTSR,EXTI_LINE);
	
	#elif EXTI_EDGE == EXTI_BOTH_EDGE
	
		SET_BIT(EXTI->RTSR,EXTI_LINE);
		SET_BIT(EXTI->FTSR,EXTI_LINE);
	
	#else 
	    #error "wrong EDGE Enable."
	#endif
		
	
	
	#if EXTI_MODE == EXTI_INT_ENABLE
	
		SET_BIT(EXTI->IMR,EXTI_LINE);
	
	#elif EXTI_MODE == EXTI_INT_DISABLE
	
		CLR_BIT(EXTI->IMR,EXTI_LINE);
	
	#else 
	    #error "wrong MODE Enable."
	#endif	

}

void EXTI_voidCallbackFunc(u8 copy_u8Line,void (*EXTI_pCallback)(void))
{
	if ((EXTI_pCallback!= NULL)&&(copy_u8Line < 16))
	{
		GP_IRQ_Callback[copy_u8Line] = EXTI_pCallback;
	}
}


void EXTI_voidInit(EXTI_Config_t *EXTI_Config)
{
	
	
	if((EXTI_Config!=NULL)&&(EXTI_Config->EXTI_u8Line < 16))
	{
		SET_BIT(RCC_APB2ENR,SYSCFGEN);// Enable SYSCFG.
		
		SET_BIT(RCC_APB2LPENR,SYSCFGLPEN); // Enable SYSCFG at sleep mode.
		
		u8 regNumber = (EXTI_Config->EXTI_u8Line )/4;
		
		u8 EXTINumber = (EXTI_Config->EXTI_u8Line) %4;
		
		
		SYSCFG->EXTICR[regNumber] &= ~(0xFUL << (EXTINumber *4));
		
		SYSCFG->EXTICR[regNumber] |= EXTI_Config->EXTI_u8PORT << (EXTINumber *4);
		
		
		if(EXTI_Config->EXTI_u8Edge == EXTI_RISING_EDGE)
		{
			CLR_BIT(EXTI->FTSR,EXTI_Config->EXTI_u8Line);
			SET_BIT(EXTI->RTSR,EXTI_Config->EXTI_u8Line);
		}
		else if (EXTI_Config->EXTI_u8Edge == EXTI_FALLING_EDGE)
		{
			CLR_BIT(EXTI->RTSR,EXTI_Config->EXTI_u8Line);
			SET_BIT(EXTI->FTSR,EXTI_Config->EXTI_u8Line);
		}
		else if (EXTI_Config->EXTI_u8Edge == EXTI_BOTH_EDGE)
		{
			SET_BIT(EXTI->RTSR,EXTI_Config->EXTI_u8Line);
			SET_BIT(EXTI->FTSR,EXTI_Config->EXTI_u8Line);
		}
		else 
		{
			//do nothing.
		}
		
		if (EXTI_Config->EXTI_u8mode == EXTI_INT_ENABLE)
		{
			SET_BIT(EXTI->IMR,EXTI_Config->EXTI_u8Line);
		}
		else if (EXTI_Config->EXTI_u8mode == EXTI_INT_DISABLE)
		{
			CLR_BIT(EXTI->IMR,EXTI_Config->EXTI_u8Line);
		}
		else 
		{
			//do nothing.
		}
	}
	else
	{
		//do nothing.
	}
	

	if (EXTI_Config->EXTI_CallbackFunc != NULL)
	{
		GP_IRQ_Callback[EXTI_Config->EXTI_u8Line] = EXTI_Config->EXTI_CallbackFunc;
	}
	else
	{
		//do nothing.
	}
}


void EXTI0_IRQHandler(void)
{
	if(GET_BIT(EXTI->PR,0)==1)
	{
		EXTI->PR = (1UL << 0);
		if(GP_IRQ_Callback[0]!=NULL)GP_IRQ_Callback[0]();
	}
}
 
void EXTI1_IRQHandler(void)
{
	if(GET_BIT(EXTI->PR,1)==1)
	{
		EXTI->PR = (1UL << 1);
		if(GP_IRQ_Callback[1]!=NULL)GP_IRQ_Callback[1]();
	}
}

void EXTI2_IRQHandler(void)
{
	if(GET_BIT(EXTI->PR,2)==1)
	{
		EXTI->PR = (1UL << 2);
		if(GP_IRQ_Callback[2]!=NULL)GP_IRQ_Callback[2]();
	}
}

void EXTI3_IRQHandler(void)
{
	if(GET_BIT(EXTI->PR,3)==1)
	{
		EXTI->PR = (1UL << 3);
		if(GP_IRQ_Callback[3]!=NULL)GP_IRQ_Callback[3]();
	}
}

void EXTI4_IRQHandler(void)
{
	if(GET_BIT(EXTI->PR,4)==1)
	{
		EXTI->PR = (1UL << 4);
		if(GP_IRQ_Callback[4]!=NULL)GP_IRQ_Callback[4]();
	}
}



void EXTI9_5_IRQHandler(void)
{
	u32 Local_u32PendingReg = EXTI->PR;
	for (u8 i = 5; i<=9;i++)
	{
		if(((Local_u32PendingReg>>i)&1)==1)
		{
			EXTI->PR = (1UL<<i);
			if(GP_IRQ_Callback[i] != NULL )GP_IRQ_Callback[i]();
		}
	}

}


void EXTI15_10_IRQHandler(void)
{
	u32 Local_u32PendingReg = EXTI->PR;
	for (u8 i = 10; i<=15;i++)
	{
		if(((Local_u32PendingReg>>i)&1)==1)
		{
			EXTI->PR = (1UL<<i);
			if(GP_IRQ_Callback[i]!=NULL)GP_IRQ_Callback[i]();
		}
	}

}
