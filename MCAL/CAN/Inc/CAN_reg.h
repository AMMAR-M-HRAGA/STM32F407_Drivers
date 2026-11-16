/*
*************** CAN_reg.h ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/

#ifndef CAN_REG_H
#define CAN_REG_H

#include "std_types.h"

#define CAN1_BASE_ADDRESS  (0x40006400UL)
#define CAN2_BASE_ADDRESS  (0x40006800UL)


// @brief transmit mailbox Register Structure 
// bxCAN contains 3 Transmit mailboxes (Tx Mailbox 0,1,2)

typedef struct {
	
	volatile u32 TIR;   /* CAN Tx mailbox identifier register */
	volatile u32 TDTR;  /* CAN mailbox data length control and time stamp register */
	volatile u32 TDLR;  /* CAN mailbox data low register */
	volatile u32 TDHR;  /* CAN mailbox data high register */
}CAN_TxMalibox_RegType;

// @brief Receive FIFO Maibox Register Structure
// bxCAN contains 2 Receive FIFOs (FIFO 0,1) each with mailboxes depth
 
typedef struct {
	
	volatile u32 RIR;  /* CAN receive FIFO mailbox identifier register */
	volatile u32 RDTR; /* CAN receive FIFO mailbox data length control and time stamp register */
	volatile u32 RDLR; /* CAN receive FIFO mailbox data low register */
	volatile u32 RDHR; /* CAN receive FIFO mailbox data high register */
}CAN_RxFifo_RegType;

typedef struct {
	volatile u32 FR1;
	volatile u32 FR2;
}CAN_FilterBank_RegType;
 

typedef struct {
	
	volatile u32 MCR;
	volatile u32 MSR;
	volatile u32 TSR;
	volatile u32 RF0R;
	volatile u32 RF1R;
	volatile u32 IER;
	volatile u32 ESR;
	volatile u32 BTR;
	
	volatile u32 RESERVED0[88U];
	
	CAN_TxMalibox_RegType TxMailbox[3U];
	
	CAN_RxFifo_RegType RxFifio[2U];
	
	volatile u32 RESERVED1[12U];
	
	volatile u32 FMR;
	volatile u32 FM1R;
	volatile u32 RESERVED2;
	volatile u32 FS1R;
	volatile u32 RESERVED3;
	volatile u32 FFA1R;
	volatile u32 RESERVED4;
	volatile u32 FA1R;
	
	
	volatile u32 RESERVED5[8U];
	
	CAN_FilterBank_RegType FilterBank[28];
	
}CAN_RegMap_t;


#define CAN1      ((CAN_RegMap_t *) CAN1_BASE_ADDRESS)
#define CAN2      ((CAN_RegMap_t *) CAN2_BASE_ADDRESS)


#endif /* CAN_REG_H */