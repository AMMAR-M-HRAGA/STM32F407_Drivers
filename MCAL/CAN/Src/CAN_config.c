/*
*************** CAN_config.c ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/


#include "CAN_interface.h"


const Can_ConfigType  Can_ConfigInstance1 = 
{
	.controllerId       = CAN_INSTANCE_1,
	.opMode             = CAN_MODE_NORMAL,
	.autoBusOffRecovery = TRUE,
	.noAutoRetransmit   = FALSE,
	.txFifoPriority     = FALSE,
	.rxfifoLockMode     = FALSE,
	.slaveStartBank     = FALSE,
	.bitTiming          = 
	{
		.prescaler  = 6U,
		.timeSeg1   = 11U,
		.timeSeg2   = 2U,
		.sjw        = 1U
	}
	
};