/*
*************** CAN_interface.h ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/

#ifndef CAN_INTERFACE_H
#define CAN_INTERFACE_H


#include "std_types.h"
#include "CAN_config.h"

#define CAN_INSTANCE_1                    (0U)
#define CAN_INSTANCE_2                    (1U)


#define CAN_MODE_NORMAL                   (0U)
#define CAN_MODE_LOOPBACK                 (1U)
#define CAN_MODE_SILENT                   (2U)
#define CAN_MODE_SILENT_LOOPBACK          (3U)

/* Interrupt Enable Flags */
#define CAN_IT_TX_MAILBOX_EMPTY           (1UL << 0U)  /* TMEIE */
#define CAN_IT_RX_FIFO0_MSG_PENDING       (1UL << 1U)  /* FMPIE0 */
#define CAN_IT_RX_FIFO0_FULL              (1UL << 2U)  /* FFIE0 */
#define CAN_IT_RX_FIFO0_OVERRUN           (1UL << 3U)  /* FOVIE0 */
#define CAN_IT_RX_FIFO1_MSG_PENDING       (1UL << 4U)  /* FMPIE1 */

#define CAN_RX_FIFO0                      (0U)
#define CAN_RX_FIFO1                      (1U)

typedef uint32  Can_IdType;
 
typedef enum {
	
	CAN_ID_STANDARD = 0U,
	CAN_ID_EXTENDED = 1U
}Can_IdFormatType;

typedef enum {
	
	CAN_FRAME_DATA   = 0U,
	CAN_FRAME_REMOTE = 1U
}Can_FrameType;

typedef enum {
	
	CAN_FILTER_MODE_IDMASK = 0U,
	CAN_FILTER_MODE_IDLIST
}Can_FilterModeType;

typedef enum {
	
	CAN_STATE_UNTINT = 0U,
	CAN_STATE_STOPPED,
	CAN_STATE_STARTED,
	CAN_STATE_SLEEP,
	CAN_STATE_BUS_OFF
}Can_ControllerStateType;

typedef enum {
	
	CAN_T_START = 0U,
	CAN_T_STOP,
	CAN_T_SLEEP,
	CAN_T_WAKEUP
}Can_StateTarnsitionType;

typedef enum {
	
	CAN_FILTER_SCALE_16BIT = 0U,
	CAN_FILTER_SCALE_32BIT
}Can_FilterScaleType;

typedef struct {
	
	Can_IdType        id;
	Can_IdFormatType  idFormat;
	Can_FrameType     frameType;
	uint8                length;
	uint8                sdu[8];
}Can_PduType;



typedef struct {
	
	uint16 prescaler ;
	uint8  timeSeg1; 
	uint8  timeSeg2;
	uint8  sjw;
}Can_BitTimingConfigType;


typedef struct {
	
	uint32      filterId;
	uint32      filterMask;
	uint8       filterBank;
	uint8       fifoAssignment;
	uint8       filterMode;
	uint8       filterScale;
	uint8       filterBankId;
	boolean  enable;
}Can_FilterConfigType;


typedef struct {
	
	uint8                      controllerId;
	uint8                      opMode;
	uint8                      autoBusOffRecovery;
	uint8                      noAutoRetransmit;
	uint8                      txFifoPriority;
	uint8                      rxfifoLockMode;
	uint8                      slaveStartBank;
	Can_BitTimingConfigType    bitTiming;
}Can_ConfigType;





typedef void (*Can_CallbackFnType)(void);


extern const Can_ConfigType  Can_ConfigInstance1;

void Can_Init(const Can_ConfigType *  ConfigPtr);
Std_ReturnType Can_SetConntrollerMode(uint8 Controller, Can_StateTarnsitionType Transition);
Std_ReturnType Can_Write(uint8 controller , const Can_PduType * PduInfo);
Std_ReturnType Can_Read(uint8 Controller ,uint8 FifoNumber,  Can_PduType * pduInfo );
Std_ReturnType Can_FilterInit(const Can_FilterConfigType * FilterConfig);
Std_ReturnType Can_EnableInterrupts(uint8 Controller, uint32 InterruptMask);
Std_ReturnType Can_RegisterCallback(uint8 Controller, uint32 InterruptSource,Can_CallbackFnType CallbackFn);
 


#endif