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

	GPIO_TypeDef * GPIOx;
	u8 PinMode;
	u8 PinNumber;
	u8 OutPutType;
	u8 SpeedType;
	u8 PullType;
	u8 AFMode;
}GPIO_PinConfig_t;



Std_ReturnType GPIO_ClockControl(GPIO_TypeDef *copy_pPORT,u8 copy_u8ClockState);
Std_ReturnType GPIO_Init(GPIO_PinConfig_t *GPIO_PinConfig);
Std_ReturnType GPIO_DeInit(GPIO_TypeDef *copy_pPORT);
Std_ReturnType GPIO_ToggleoutputPin(GPIO_TypeDef *copy_pPORT , u8 copy_u8PinNumber);
Std_ReturnType GPIO_ReadFromInputPin(GPIO_TypeDef *copy_pPORT,u8 copy_u8PinNumber , u8 * copy_pData);
Std_ReturnType GPIO_ReadFromInputPort(GPIO_TypeDef *copy_pPORT , u32 * copy_pData);
Std_ReturnType GPIO_WriteToOutputPort(GPIO_TypeDef *copy_pPORT,u16 Value);
Std_ReturnType GPIO_WriteToOutputPin(GPIO_TypeDef *copy_pPORT,u8 PinNumber,u8 copy_u8Value);








#endif /* INC_GPIO_H_ */
