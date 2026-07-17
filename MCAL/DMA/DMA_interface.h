/*
*************** DMA_interface.h ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/

#include "std_types.h"
#include "DMA_reg.h"


typedef struct {
	u8 Channal;
	u8 Direction;
	u8 priority;
	u8 MSize;
	u8 PSize;
	u8 CircularMode;
	u8 MemInc;
	u8 PeriphInc;
	u8 DoubleBufferMode;
	u8 MemBurst;
	u8 periphBurst; 
	u8 CompleteINT;
	u8 HalfINT;
	u8 TransferErorrINT;
	u8 ErorrDirectINT;
}DMA_Config_t;


#define DMA1_STREAM0       (&(DMA1->Streams[0]))
#define DMA1_STREAM1       (&(DMA1->Streams[1]))
#define DMA1_STREAM2       (&(DMA1->Streams[2]))
#define DMA1_STREAM3       (&(DMA1->Streams[3]))
#define DMA1_STREAM4       (&(DMA1->Streams[4]))
#define DMA1_STREAM5       (&(DMA1->Streams[5]))
#define DMA1_STREAM6       (&(DMA1->Streams[6]))
#define DMA1_STREAM7       (&(DMA1->Streams[7]))



#define DMA2_STREAM0       (&(DMA2->Streams[0]))
#define DMA2_STREAM1       (&(DMA2->Streams[1]))
#define DMA2_STREAM2       (&(DMA2->Streams[2]))
#define DMA2_STREAM3       (&(DMA2->Streams[3]))
#define DMA2_STREAM4       (&(DMA2->Streams[4]))
#define DMA2_STREAM5       (&(DMA2->Streams[5]))
#define DMA2_STREAM6       (&(DMA2->Streams[6]))
#define DMA2_STREAM7       (&(DMA2->Streams[7]))

#define DMA_CHANNAL0 0
#define DMA_CHANNAL1 1
#define DMA_CHANNAL2 2
#define DMA_CHANNAL3 3
#define DMA_CHANNAL4 4
#define DMA_CHANNAL5 5
#define DMA_CHANNAL6 6
#define DMA_CHANNAL7 7


#define DMA_BURST_SINGLE  0
#define DMA_BURST_INCR4   1
#define DMA_BURST_INCR8   2
#define DMA_BURST_INCR16  3

#define DOUBLE_BFF_DISABLE 0
#define DOUBLE_BFF_ENALBE  1

#define PERIPHERAL_TO_MEMORY 0
#define MEMORY_TO_PERIPHERAL 1
#define MEMORY_TO_MEMORY     2



#define P_INCREMENT_DISABLE 0
#define P_INCREMENT_ENABLE  1

#define M_INCREMENT_DISABLE 0
#define M_INCREMENT_ENABLE  1

#define DMA_DBM_DISABLE 0
#define DMA_DBM_ENABLE  1

#define DMA_PRIORITY_LOW    0
#define DMA_PRIORITY_MED    1
#define DMA_PRIORITY_HIGH   2
#define DMA_PRIORITY_V_HIGH 3

#define DMA_M_SIZE_8  0
#define DMA_M_SIZE_16 1
#define DMA_M_SIZE_32 2

#define DMA_P_SIZE_8  0
#define DMA_P_SIZE_16 1 
#define DMA_P_SIZE_32 2


#define CIRCULAR_MODE_DISABLE 0
#define CIRCULAR_MODE_ENABLE  1



#define DMA_PREPH_FLAW_DISABLE 0
#define DMA_PREPH_FLAW_ENABLE  1

#define DMA_T_COMPLETE_INT_DISABLE 0
#define DMA_T_COMPLETE_INT_ENABLE  1

#define DMA_T_HALF_INT_DISABLE 0
#define DMA_T_HALF_INT_ENABLE  1

#define DMA_T_ERROR_INT_DISABLE 0
#define DMA_T_ERROR_INT_ENABLE  1


#define DMA_DIRECT_MODE_DISABLE 0
#define DMA_DIRECT_MODE_ENABLE  1

#define DMA_DISABLE 0
#define DMA_ENABLE  1






Std_ReturnType DMA_voidInitConfig();
Std_ReturnType DMA_voidInit(DMA_Stream_TypeDef*copy_pStream,const DMA_Config_t *DMA_Config);
void DMA_voidConfigTransfer(DMA_Stream_TypeDef*copy_pStream ,u32 copy_u32PeripheralAddr,u32 copy_u32MemoryAddr, u16 copy_u16Datalength);
Std_ReturnType DMA_voidCmd(DMA_Stream_TypeDef*copy_pStream,u8 copy_u8State);
void DMA_voidClearFlag(DMA_TypeDef* copy_pDma,u8 copy_u8StreamNumber,u8 copy_u8FlagBit);
void DMA_voidConfigDoubleBuffer(DMA_Stream_TypeDef*copy_pStream,u32 copy_u32Memory1Addr,u8 copy_u8StartBuffer);
void DMA_voidSetCallBackFunc(u8 copy_u8StreamNumber,u8 copy_u8StreamIndex, void (*pvNotificationFunc)(void));
void voidFuncISR_Handler(DMA_TypeDef*copy_dma,u8 copy_u8StreamNumber,u8 copy_u8dmaIndex);




