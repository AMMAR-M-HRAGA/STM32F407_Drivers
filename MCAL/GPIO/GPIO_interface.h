/*
*************** GPIO_interface.h ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/

#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_


#include "GPIO_reg.h"
#include "std_types.h"
#include "bit_math.h"

typedef struct {
	u8 PinMode;
	u8 PinNumber;
	u8 OutPutType;
	u8 Speedtype;
	u8 PullType;
	u8 AFMode;
}GPIO_PinConfig_t;



void GPIO_ClockControl(GPIO_TypeDef *copy_pPORT,u8 copy_u8ClockState);
void GPIO_InitConfig();
void GPIO_Init(GPIO_PinConfig_t *GPIO_PinConfig,GPIO_TypeDef *copy_pRORT);
void GPIO_DeInit(GPIO_TypeDef *copy_pPORT);
void GPIO_ToggleoutputPin(u8 PinNumber,GPIO_TypeDef *copy_pPORT);
u8 GPIO_ReadFromInputPin(GPIO_TypeDef *copy_pPORT,u8 copy_u8PinNumber);
u16 GPIO_ReadFromInputPort(GPIO_TypeDef *copy_pPORT);
void GPIO_WriteToOutputPort(GPIO_TypeDef *copy_pPORT,u16 Value);
void GPIO_WriteToOutputPin(GPIO_TypeDef *copy_pPORT,u8 PinNumber,u8 Value);








#endif /* INC_GPIO_H_ */
