/*
*************** CAN_private.h ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/

#ifndef CAN_PRIVATE_H
#define CAN_PRIVATE_H

#include "std_types.h"
#include "CAN_reg.h"

#define CAN_HW_MAX_CONTROLLERS           (2U)
#define CAN_HW_MAX_FILTER_BANKS          (28U)
#define CAN_HW_TX_MAILBOX_COUNT          (3U)
#define CAN_HW_RX_FIFO_COUNT             (2U)

#define CAN_TIMEOUT_COUNTER               (10000UL)
 

#define CAN_MSR_INAK_MASK                (1UL << 0U)
#define CAN_MSR_SLAK_MASK                (1UL << 1U)


#define CAN_MCR_INRQ_MASK                (1UL << 0U)
#define CAN_MCR_SLEEP_MASK               (1UL << 1U)
#define CAN_MCR_TXFP_MASK                (1UL << 2U)
#define CAN_MCR_RFLM_MASK                (1UL << 3U)
#define CAN_MCR_NART_MASK                (1UL << 4U)
#define CAN_MCR_ABOM_MASK                (1UL << 6U)

#define CAN_BTR_BRP_MASK   (0x3FFUL)
#define CAN_BTR_TS1_MASK   (0xFUL)
#define CAN_BTR_TS2_MASK   (0x7UL)
#define CAN_BTR_SJW_MASK   (0x3UL)

#define CAN_TSR_TME0_MASK                (1UL << 26U)
#define CAN_TSR_TME1_MASK                (1UL << 27U)
#define CAN_TSR_TME2_MASK                (1UL << 28U)
#define CAN_TSR_CODE_SHIFT               (24U)

#define CAN_FMR_FINIT_MASK               (1UL << 0U)
#define CAN_RFR_FMP_MASK                 (0x03UL)
#define CAN_RFR_FULL_MASK                (1UL << 3U)
#define CAN_RFR_FOVR_MASK                (1UL << 4U)
#define CAN_RFR_RFOM_MASK                (1UL << 5U)

#define CAN_RFR_FMP_MASK                  (0x03UL)
#define CAN_RFOM_MASK                     (1UL << 5U)

#define CAN_RI1R_STID_SHIFT               (21U)
#define CAN_RI1R_EXID_SHIFT               (3U)
#define CAN_RI1R_IDE_SHIFT                (2U)
#define CAN_RI1R_RTR_SHIFT                (1U)


#define CAN_BTR_BRP_SHIFT                (0U)
#define CAN_BTR_TS1_SHIFT                (16U)
#define CAN_BTR_TS2_SHIFT                (20U)
#define CAN_BTR_SJW_SHIFT                (24U)
#define CAN_BTR_LBKM_SHIFT               (30U)
#define CAN_BTR_SILM_SHIFT               (31U)


#define CAN_STD_ID_SHIFT                 (21U)
#define CAN_EXT_ID_SHIFT                 (3U)

#define CAN_TI1R_STID_SHIFT              (21U)
#define CAN_TI1R_EXID_SHIFT              (3U)
#define CAN_TI1R_IDE_SHIFT               (2U)
#define CAN_TI1R_RTR_SHIFT               (1U)
#define CAN_TI1R_TXRQ_SHIFT              (0U)


#define CAN_RI1R_STID_SHIFT               (21U)
#define CAN_RI1R_EXID_SHIFT               (3U)
#define CAN_RI1R_IDE_SHIFT                (2U)
#define CAN_RI1R_RTR_SHIFT                (1U)




static inline CAN_RegMap_t * Can_GetControllerBase(uint8 ConterollerId)
{
	CAN_RegMap_t * pCanBase = NULL;
	if (ConterollerId == CAN_INSTANCE_1)
	{
		pCanBase = CAN1;
	}
	else if (ConterollerId == CAN_INSTANCE_2)
	{
		pCanBase = CAN2;
	}
	else
	{
		//
	}
 	return pCanBase;
}


#endif