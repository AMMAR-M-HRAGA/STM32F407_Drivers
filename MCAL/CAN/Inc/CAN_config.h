/*
*************** CAN_config.h ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/


#ifndef CAN_CONFIG_H
#define CAN_CONFIG_H

#include "std_types.h"


#define CAN_DEV_ERROR_DETECT                (STD_ON)
#define CAN_DUAL_CAN_SUPPORT                (STD_ON)
#define CAN_TIMEOUT_PROCTECTION             (STD_ON)


#define CAN_TX_PROCESSING_POLLING            (0U)
#define CAN_RX_PROCESSING_INTERRUPT			 (1U)

#define CAN_PROCESSING_POLLING               (0U)
#define CAN_PROCESSING_INTERRUPT             (1U)

#define CAN_TX_PROCESSING                    CAN_PROCESSING_POLLING
#define CAN_RX_PROCESSING                    CAN_PROCESSING_INTERRUPT
#define CAN_BUSOFF_PROCESSING                CAN_PROCESSING_INTERRUPT























#endif