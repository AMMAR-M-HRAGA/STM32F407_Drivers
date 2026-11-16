/*
*************** MPU_program.c ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/

#include "std_types.h"
#include "bit_math.h"
#include "MPU_reg.h"
#include "MPU_interface.h"
#include "MPU_config.h"
#include "MPU_private.h"



Std_ReturnType MPU_voidConfigRegion(MPU_RegionConfig_t * MPU_RegionConfig )
{
	Std_ReturnType Local_u8ErrorState = E_OK;
	
	if((MPU_RegionConfig == NULL) || (MPU_RegionConfig->RegionNumber > REGION_MAX_NUMBER))
	{
		Local_u8ErrorState = E_NOT_OK;
	}
	else 
	{
		u32 Local_u32CtrlBackup = MPU->CTRL;
		MPU->CTRL = 0;
		MPU->RNR = MPU_RegionConfig->RegionNumber ;
		MPU->RBAR = MPU_RegionConfig->RegionAddress ;
		MPU->RASR = (MPU_RegionConfig->RegionSize <<MPU_RASR_SIZE_SHIFT )|
					(MPU_RegionConfig->RegionPermission << MPU_RASR_AP_SHIFT)|
					(MPU_RegionConfig->RegionXNSelect << MPU_RASR_XN_SHIFT)|
					(MPU_RegionConfig->RegionMemType << MPU_RASR_MEM_TYPE_SHIFT)|
					(MPU_RegionConfig->RegionState << MPU_RASR_ENABLE);			
		
		MPU->CTRL  =  Local_u32CtrlBackup;		
	}

	return Local_u8ErrorState;
}

void MPU_voidEnable(void)
{ 
	MPU->CTRL |= (1 << 0) | (1 << 2) ;

}

void MPU_voidDisable(void)
{
	MPU->CTRL = 0;
}

void MemManageFault_voidEnable(void)
{
	SET_BIT(SCB_SHCSR,16);
}


void MemManageFault_voidDisable(void)
{
	CLR_BIT(SCB_SHCSR,16);
}



