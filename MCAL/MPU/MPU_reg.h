/*
*************** MPU_reg.h ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/


#ifndef MPU_REG_H
#define MPU_REG_H




typedef struct {
	
	volatile u32 TYPE;
	volatile u32 CTRL;
	volatile u32 RNR;
	volatile u32 RBAR;
	volatile u32 RASR;
	
	volatile u32 RBAR_A1;
	volatile u32 RBSR_A1;
	volatile u32 RBAR_A2;
	volatile u32 RBSR_A2;
	volatile u32 RBAR_A3;
	volatile u32 RBSR_A3;
}MPU_TypeDef;


#define MPU    (( volatile MPU_TypeDef *)0xE000ED90)
#define SCB_SHCSR  (*((volatile u32 *)0xE000ED24))

#endif