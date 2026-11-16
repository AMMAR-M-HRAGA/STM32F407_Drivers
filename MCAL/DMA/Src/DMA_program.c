/*
*************** DMA_program.c***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/

#include "std_types.h"
#include "bit_math.h"
#include "DMA_reg.h"
#include "DMA_interface.h"
#include "DMA_private.h"
#include "DMA_config.h"
static const u8 DMA_au8TCBitPos[4] =  {5,11,21,27};
static void (*DMA_pvCallBackFunc[16])(void);



Std_ReturnType DMA_voidInit(DMA_Stream_TypeDef*copy_pStream,const DMA_Config_t *DMA_Config)
{

    Std_ReturnType Local_u8ErrorState = E_OK;
	u32 Local_u32Timeout = 500000;
	
	if((copy_pStream == NULL) || (DMA_Config == NULL))
	{
		Local_u8ErrorState = E_NOT_OK;
	}
	else
	{
		CLR_BIT(copy_pStream->CR,DMA_CR_EN_BIT);
		
		while ((GET_BIT(copy_pStream->CR,DMA_CR_EN_BIT)==1)&&(Local_u32Timeout>0))
		{
			Local_u32Timeout--;
		}
		
		if(Local_u32Timeout == 0)
		{
			Local_u8ErrorState = E_TIMEOUT;
		}
		else 
		{
			
			copy_pStream->CR = 0;
			
			copy_pStream->CR |= (DMA_Config->Channal            <<DMA_CR_CHSEL_BIT_POS)|
								(DMA_Config->Direction   	     <<DMA_CR_DIR_BIT_POS)|
								(DMA_Config->priority    	     <<DMA_CR_PL_BIT_POS)|
								(DMA_Config->MSize       	     <<DMA_CR_MSIZE_BIT_POS)|
								(DMA_Config->PSize        	     <<DMA_CR_PSIZE_BIT_POS)|
								(DMA_Config->CircularMode 	     <<DMA_CR_CIRC_BIT_POS)|
								(DMA_Config->MemInc       	     <<DMA_CR_MINC_BIT_POS)|
								(DMA_Config->PeriphInc    	     <<DMA_CR_PINC_BIT_POS)|
								(DMA_Config->DoubleBufferMode    <<DMA_CR_DBM_BIT_POS)|
								(DMA_Config->periphBurst         <<DMA_CR_PBURST_BIT_POS)|
								(DMA_Config->MemBurst            <<DMA_CR_MBURST_BIT_POS)|
								(DMA_Config->CompleteINT         <<DMA_CR_TCIE_BIT)|
								(DMA_Config->HalfINT             <<DMA_CR_HTIE_BIT)|
								(DMA_Config->TransferErorrINT    <<DMA_CR_TETE_BIT)|
								(DMA_Config->ErorrDirectINT     <<DMA_CR_DMEIE_BIT);
		   copy_pStream->FCR |= (3U << 0);
		}
	}
	return Local_u8ErrorState;
}



Std_ReturnType DMA_voidConfigTransfer(DMA_Stream_TypeDef*copy_pStream ,u32 copy_u32PeripheralAddr,u32 copy_u32MemoryAddr, u16 copy_u16Datalength)
{
	Std_ReturnType Local_u8ErrorState = E_OK;
	if(copy_pStream == NULL)
	{
		Local_u8ErrorState = E_NOT_OK;
	}
	else
	{
		copy_pStream->PAR = copy_u32PeripheralAddr;
		copy_pStream->M0AR = copy_u32MemoryAddr;
		copy_pStream->NDTR = copy_u16Datalength;
	}

	return Local_u8ErrorState;
}

Std_ReturnType DMA_voidCmd(DMA_Stream_TypeDef*copy_pStream,u8 copy_u8State)
{
	
	Std_ReturnType Local_u8ErrorState = E_OK;
	if(copy_pStream == NULL)
	{
		Local_u8ErrorState = E_NOT_OK;
	}
	else 
	{
		if (copy_u8State == DMA_ENABLE)
		{
			SET_BIT(copy_pStream->CR,DMA_CR_EN_BIT);
			
		}
		else if (copy_u8State == DMA_DISABLE)
		{
			CLR_BIT(copy_pStream->CR,DMA_CR_EN_BIT);
		}
		else
		{
			// do nothing.
		}
	
	}

	return Local_u8ErrorState;
}


Std_ReturnType DMA_voidClearFlag(DMA_TypeDef* copy_pDMA,u8 copy_u8StreamNumber,u8 copy_u8FlagBit)
{
	Std_ReturnType Local_u8ErrorState = E_OK;
	if(copy_pDMA == NULL)
	{
		Local_u8ErrorState = E_NOT_OK;
	}
	else 
	{
		if (copy_u8StreamNumber <4)
		{
			copy_pDMA->LICFR = (1UL << copy_u8FlagBit);
		}
		else 
		{
			copy_pDMA->HICFR = (1UL << copy_u8FlagBit);
		}
	}
	
	return Local_u8ErrorState;

}




Std_ReturnType DMA_voidConfigDoubleBuffer(DMA_Stream_TypeDef*copy_pStream,u32 copy_u32Memory1Addr,u8 copy_u8StartBuffer)
{
	Std_ReturnType Local_u8ErrorState = E_OK;
	if(copy_pStream == NULL)
	{
		Local_u8ErrorState = E_NOT_OK;
	}
	else 
	{
		copy_pStream->M1AR  = copy_u32Memory1Addr;
		
		if(copy_u8StartBuffer == 0)
		{
			CLR_BIT(copy_pStream->CR,DMA_CR_CT_BIT);
			
		}
		else 
		{
			SET_BIT(copy_pStream->CR,DMA_CR_CT_BIT);
		}	
	}
	
	return Local_u8ErrorState;
}



Std_ReturnType DMA_voidSetCallBackFunc(u8 copy_u8StreamNumber,u8 copy_u8DMAIndex, void (*pvNotificationFunc)(void))
{
	Std_ReturnType Local_u8ErrorState = E_OK;
	
	if((pvNotificationFunc != NULL)|| (copy_u8StreamNumber > DMA_MAX_NUMBER) || (copy_u8DMAIndex >= DAM_MAX_INDEX))
	{
		Local_u8ErrorState =  E_NOT_OK;
	}
	else
	{
		
		u8 Local_u8StreamNumber = (copy_u8DMAIndex*DMA_MAX_NUMBER) + copy_u8StreamNumber;  
		DMA_pvCallBackFunc[Local_u8StreamNumber] = pvNotificationFunc;
	}
	
	return Local_u8ErrorState;
}


static void DMA_voidFuncISR_Handler(DMA_TypeDef*copy_dma,u8 copy_u8StreamNumber,u8 copy_u8dmaIndex)
{
	u8 Local_u8BitPos = DMA_au8TCBitPos[copy_u8StreamNumber%4];
	DMA_voidClearFlag(copy_dma,copy_u8StreamNumber,Local_u8BitPos );
	u8 Local_u8CallBackIndex = (copy_u8dmaIndex*DMA_MAX_NUMBER) + copy_u8StreamNumber;
	
	if(DMA_pvCallBackFunc[Local_u8CallBackIndex] != NULL)
	{
		DMA_pvCallBackFunc[Local_u8CallBackIndex]();
	}
	else 
	{
		//do nothing.
	}
}  


void DMA1_Stream0_IRQHandler(void) { DMA_voidFuncISR_Handler(DMA1,0,0); }
void DMA1_Stream1_IRQHandler(void) { DMA_voidFuncISR_Handler(DMA1,1,0); }
void DMA1_Stream2_IRQHandler(void) { DMA_voidFuncISR_Handler(DMA1,2,0); }
void DMA1_Stream3_IRQHandler(void) { DMA_voidFuncISR_Handler(DMA1,3,0); }
void DMA1_Stream4_IRQHandler(void) { DMA_voidFuncISR_Handler(DMA1,4,0); }
void DMA1_Stream5_IRQHandler(void) { DMA_voidFuncISR_Handler(DMA1,5,0); }
void DMA1_Stream6_IRQHandler(void) { DMA_voidFuncISR_Handler(DMA1,6,0); }
void DMA1_Stream7_IRQHandler(void) { DMA_voidFuncISR_Handler(DMA1,7,0); }

void DMA2_Stream0_IRQHandler(void) { DMA_voidFuncISR_Handler(DMA2,0,1); }
void DMA2_Stream1_IRQHandler(void) { DMA_voidFuncISR_Handler(DMA2,1,1); }
void DMA2_Stream2_IRQHandler(void) { DMA_voidFuncISR_Handler(DMA2,2,1); }
void DMA2_Stream3_IRQHandler(void) { DMA_voidFuncISR_Handler(DMA2,3,1); }
void DMA2_Stream4_IRQHandler(void) { DMA_voidFuncISR_Handler(DMA2,4,1); }
void DMA2_Stream5_IRQHandler(void) { DMA_voidFuncISR_Handler(DMA2,5,1); }
void DMA2_Stream6_IRQHandler(void) { DMA_voidFuncISR_Handler(DMA2,6,1); }
void DMA2_Stream7_IRQHandler(void) { DMA_voidFuncISR_Handler(DMA2,7,1); }




















