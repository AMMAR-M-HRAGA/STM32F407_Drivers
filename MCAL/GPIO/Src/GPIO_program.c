/*
*************** GPIO_program.c.c ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/

#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"
#include "GPIO_reg.h"
#include "std_types.h"
#include "bit_math.h"


static inline void GPIO_ModifyReg(volatile u32* reg, u8 pos, u8 width ,u32 value )
{
	*reg &= ~(((1UL << width) -1UL) << pos);
	*reg |= (value << pos);
}


Std_ReturnType GPIO_ClockControl(GPIO_TypeDef *copy_pPORT,u8 copy_u8ClockState)
{
	Std_ReturnType Local_u8ErrorState = E_OK;
    if((copy_pPORT != NULL)&&(copy_pPORT <= GPIOE)&&(copy_pPORT >= GPIOA))  
	{
		u8 Local_u8BitPosition = ((u32)copy_pPORT - (u32)GPIOA)/GPIO_ADDR_OFFEST;
		
		if(copy_u8ClockState == GPIO_CLK_ENABLE)
		{
			SET_BIT(RCC_AHB1ENR,Local_u8BitPosition);
		}
		else if (copy_u8ClockState == GPIO_CLK_DISABLE)
		{
			CLR_BIT(RCC_AHB1ENR,Local_u8BitPosition);
		}
		else 
		{
			//do nothing.
		}
	}
	else
	{
		Local_u8ErrorState = E_NOT_OK;
	}
    	
    return Local_u8ErrorState;
}


Std_ReturnType GPIO_Init(GPIO_PinConfig_t *GPIO_PinConfig)
{

	Std_ReturnType Local_u8ErrorState = E_OK;


	if (GPIO_PinConfig == NULL)
	{
		Local_u8ErrorState = E_NULL_POINTER;
	}
	else
	{
		GPIO_ModifyReg(&GPIO_PinConfig->GPIOx->MODER , GPIO_PinConfig->PinNumber*GPIO_MODER_PIN_WIDTH,
			          GPIO_MODER_PIN_WIDTH , GPIO_PinConfig->PinMode);

		GPIO_ModifyReg(&GPIO_PinConfig->GPIOx->PUPDR , GPIO_PinConfig->PinNumber*GPIO_PUPDR_PIN_WIDTH,
			          GPIO_PUPDR_PIN_WIDTH , GPIO_PinConfig->PullType);

		GPIO_ModifyReg(&GPIO_PinConfig->GPIOx->OSPEEDR , GPIO_PinConfig->PinNumber*GPIO_ODPEEDR_PIN_WIDTH,
					  GPIO_ODPEEDR_PIN_WIDTH , GPIO_PinConfig->SpeedType);
		
		GPIO_ModifyReg(&GPIO_PinConfig->GPIOx->OTYPER , GPIO_PinConfig->PinNumber*GPIO_OTYPER_PIN_WIDTH,
					  GPIO_OTYPER_PIN_WIDTH ,GPIO_PinConfig->OutPutType );

		if(GPIO_PinConfig->PinMode == GPIO_MODE_AF)
		{
			u8 index = GPIO_PinConfig->PinNumber / GPIO_AFR_PINS_PER_REG;
			u8 shift = GPIO_PinConfig->PinNumber % GPIO_AFR_PINS_PER_REG;

			GPIO_ModifyReg(&GPIO_PinConfig->GPIOx->AFR[index] , shift*GPIO_AFR_PIN_WIDTH , GPIO_AFR_PIN_WIDTH,
						GPIO_PinConfig->AFMode);
			

		}
		else
		{
			//do nothing.
		}

	}

	return Local_u8ErrorState;

}

Std_ReturnType GPIO_ToggleoutputPin(GPIO_TypeDef *copy_pPORT , u8 copy_u8PinNumber)
{
	Std_ReturnType Local_u8ErrorState = E_OK;
	if((copy_pPORT == NULL) || (copy_pPORT < GPIOA) || (copy_pPORT > GPIOE))
	{
		Local_u8ErrorState = E_NOT_OK;
	}
	else
	{
		copy_pPORT->ODR ^= (1UL<< copy_u8PinNumber);
	}

	return Local_u8ErrorState;
}


Std_ReturnType GPIO_DeInit(GPIO_TypeDef *copy_pPORT)
{
	Std_ReturnType Local_u8ErrorState = E_OK;
	if((copy_pPORT == NULL) || (copy_pPORT < GPIOA) || (copy_pPORT > GPIOE))
	{
		Local_u8ErrorState = E_NOT_OK;
	}
	else
	{
		copy_pPORT->MODER   = 0x00000000U;
		copy_pPORT->OTYPER  = 0x00000000U;
		copy_pPORT->OSPEEDR = 0x00000000U;
		copy_pPORT->PUPDR   = 0x00000000U;
		copy_pPORT->ODR     = 0x00000000U;
		copy_pPORT->BSRR    = 0x00000000U;
		copy_pPORT->AFR[0]  = 0x00000000U;
		copy_pPORT->AFR[1]  = 0x00000000U;
	} 

	return Local_u8ErrorState;

}


Std_ReturnType GPIO_ReadFromInputPin(GPIO_TypeDef *copy_pPORT,u8 copy_u8PinNumber , u8 * copy_pData)
{
	Std_ReturnType Local_u8ErrorState = E_OK;
	
	if((copy_pPORT == NULL)||(copy_pPORT < GPIOA) || (copy_pPORT > GPIOE))
	{
		Local_u8ErrorState = E_NOT_OK;
	}
	else
	{
		u8 value = (u8)((copy_pPORT->IDR >> copy_u8PinNumber) & 1);
		*copy_pData = value;
	}
	return Local_u8ErrorState;
}

Std_ReturnType GPIO_ReadFromInputPort(GPIO_TypeDef *copy_pPORT , u32 * copy_pData)
{
	Std_ReturnType Local_u8ErrorState = E_OK;
	
	if((copy_pPORT == NULL) || (copy_pPORT < GPIOA) || (copy_pPORT > GPIOE))
	{
		Local_u8ErrorState = E_NOT_OK;
	}
	else
	{
		*copy_pData  =  (u16)copy_pPORT->IDR;
	}

	return Local_u8ErrorState;
}



Std_ReturnType GPIO_WriteToOutputPort(GPIO_TypeDef *copy_pPORT,u16 Value)
{
	Std_ReturnType Local_u8ErrorState = E_OK;
	
	if((copy_pPORT == NULL)||(copy_pPORT < GPIOA) || (copy_pPORT > GPIOE))
	{
		Local_u8ErrorState = E_NOT_OK;
	}
	else
	{
		copy_pPORT->ODR  = Value;
	}
	return Local_u8ErrorState;

}


Std_ReturnType GPIO_WriteToOutputPin(GPIO_TypeDef *copy_pPORT,u8 PinNumber,u8 copy_u8Value)
{
	Std_ReturnType Local_u8ErrorState = E_OK;
	
	if((copy_pPORT != NULL)&&(copy_pPORT >= GPIOA)&& (copy_pPORT <= GPIOE)&&(PinNumber <= GPIO_MAX_PIN_NUMBER))
	{
		if(copy_u8Value == GPIO_PIN_HIGH)
		{
			SET_BIT(copy_pPORT->BSRR,PinNumber);
		}
		else if (copy_u8Value == GPIO_PIN_LOW)
		{
			SET_BIT(copy_pPORT->BSRR,(PinNumber + GPIO_BSRR_RESET_OFFEST));
		}
		else
		{
			//do nothing.
		}
		
	}
	else
	{
		Local_u8ErrorState = E_NOT_OK;
	}

	return Local_u8ErrorState;

}





























