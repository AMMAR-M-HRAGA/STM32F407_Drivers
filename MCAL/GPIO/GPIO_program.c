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
 

void GPIO_ClockControl(GPIO_TypeDef *copy_pPORT,u8 copy_u8ClockState)
{
    if((copy_pPORT <= GPIOI)&&(copy_pPORT>=GPIOA))
	{
		u8 Local_u8BitPosition = ((u32)copy_pPORT - (u32)GPIOA)/0x400;
		
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
		//do nothing.
	}
    	

}

void GPIO_InitConfig()
{
	u32 temp = 0;
    GPIO_PORT->MODER  &= ~(0x3 << (GPIO_PIN_NUMBER *2));
	temp = (GPIO_PIN_MODE << (GPIO_PIN_NUMBER *2));
	GPIO_PORT->MODER |= temp;

	GPIO_PORT->PUPDR &= ~(0x3 << (GPIO_PIN_NUMBER *2));
	temp = (GPIO_PUPD_STATE << (GPIO_PIN_NUMBER *2));
	GPIO_PORT->PUPDR |= temp;

	GPIO_PORT->OTYPER &= ~(0x1 << (GPIO_PIN_NUMBER));
	temp = (GPIO_PPOD_TYPE << (GPIO_PIN_NUMBER));
	GPIO_PORT->OTYPER |= temp;

	if(GPIO_PIN_MODE == GPIO_MODE_AF)
	{
		u8 index = GPIO_PIN_NUMBER /8;
		u8 shift = GPIO_PIN_NUMBER %8;

		GPIO_PORT->AFR[index] &= ~(0xF << (shift*4));
		GPIO_PORT->AFR[index] |= (GPIO_AF_MODE << (shift*4));

	}
	else
	{
		//do nothing.
	}



}

void GPIO_Init(GPIO_PinConfig_t *GPIO_PinConfig,GPIO_TypeDef *copy_pPORT)
{
	u32 temp = 0;
	copy_pPORT->MODER  &= ~(0x3 << ((GPIO_PinConfig->PinNumber)*2));
	temp = (GPIO_PinConfig->PinMode << ((GPIO_PinConfig->PinNumber)*2));
	copy_pPORT->MODER |= temp;

	copy_pPORT->PUPDR &= ~(0x3 << ((GPIO_PinConfig->PinNumber)*2));
	temp = (GPIO_PinConfig->PullType << ((GPIO_PinConfig->PinNumber)*2));
	copy_pPORT->PUPDR |= temp;
	
	copy_pPORT->OSPEEDR &= ~(0x3 << ((GPIO_PinConfig->PinNumber)*2));
	temp = (GPIO_PinConfig->Speedtype << ((GPIO_PinConfig->PinNumber)*2));
	copy_pPORT->OSPEEDR |= temp;

	copy_pPORT->OTYPER &= ~(0x1 << (GPIO_PinConfig->PinNumber));
	temp = (GPIO_PinConfig->OutPutType << (GPIO_PinConfig->PinNumber));
	copy_pPORT->OTYPER |= temp;

	if(GPIO_PinConfig->PinMode == GPIO_MODE_AF)
	{
		u8 index = GPIO_PinConfig->PinNumber /8;
		u8 shift = GPIO_PinConfig->PinNumber %8;

		copy_pPORT->AFR[index] &= ~(0xF << (shift*4));
		copy_pPORT->AFR[index] |= (GPIO_PinConfig->AFMode << (shift*4));

	}
	else
	{
		//do nothing.
	}



}

void GPIO_ToggleoutputPin(u8 PinNumber,GPIO_TypeDef *copy_pPORT)
{
	copy_pPORT->ODR ^= (1<< PinNumber);
}


void GPIO_DeInit(GPIO_TypeDef *copy_pPORT)
{
	if((copy_pPORT >= GPIOA)&& (copy_pPORT <= GPIOI))
	{
		copy_pPORT->MODER   = 0x00000000;
		copy_pPORT->OTYPER  = 0x00000000;
		copy_pPORT->OSPEEDR = 0x00000000;
		copy_pPORT->PUPDR   = 0x00000000;
		copy_pPORT->ODR     = 0x00000000;
		copy_pPORT->BSRR    = 0x00000000;
		copy_pPORT->AFR[0]  = 0x00000000;
		copy_pPORT->AFR[1]  = 0x00000000;
	} 

}


u8 GPIO_ReadFromInputPin(GPIO_TypeDef *copy_pPORT,u8 copy_u8PinNumber)
{

	
	u8 value = (u8)((copy_pPORT->IDR >> copy_u8PinNumber) & 1);
	return value;
}

u16 GPIO_ReadFromInputPort(GPIO_TypeDef *copy_pPORT)
{

	return (u16)copy_pPORT->IDR;

}



void GPIO_WriteToOutputPort(GPIO_TypeDef *copy_pPORT,u16 Value)
{
	copy_pPORT->ODR  = Value;
}


void GPIO_WriteToOutputPin(GPIO_TypeDef *copy_pPORT,u8 PinNumber,u8 Value)
{
	if((copy_pPORT != NULL)&&(PinNumber <= 15))
	{
		if(Value == GPIO_PIN_HIGH)
		{
			SET_BIT(copy_pPORT->BSRR,PinNumber);
		}
		else if (Value == GPIO_PIN_LOW)
		{
			PinNumber+=16;
			SET_BIT(copy_pPORT->BSRR,PinNumber);
		}
		else
		{
			//do nothing.
		}
		
	}
	else
	{
		//do noting
	}

}

































