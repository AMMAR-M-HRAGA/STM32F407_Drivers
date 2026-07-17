/*
*************** EXTI_interface.h ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/

#ifndef _EXTI_INTERFACE_H
#define _EXTI_INTERFACE_H

#include "std_types.h"
#include "bit_math.h"


typedef struct {
	
    u8 EXTI_u8Line ; // EXTI_LINE0||EXTI_LINE1...
	u8 EXTI_u8PORT ; // pAX || PBX ...
    u8 EXTI_u8Edge ; // Rising || falling || both
	u8 EXTI_u8mode; // Interrupt Enable or disable
	void (*EXTI_CallbackFunc)(void); // pointer to function.
}EXTI_Config_t;


void EXTI_voidInitConfig();
void EXTI_voidInit(EXTI_Config_t *EXTI_Config);
void EXTI_voidCallbackFunc(u8 copy_u8Line,void (*EXTI_pCallback)(void));
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10IRQHandler(void);







#endif
