/*
*************** CAN_program.c ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/

#include "CAN_interface.h"
#include "CAN_private.h"
#include "std_types.h"
#include "CAN_reg.h"

static Can_CallbackFnType Can_s_rxFifo0Callback[CAN_HW_MAX_CONTROLLERS] = {NULL_PTR, NULL_PTR};

static Std_ReturnType Can_s_WaitFlag(volatile uint32 * pReg, uint32 mask, boolean expectedSet)
{
    #if (CAN_TIMEOUT_PROCTECTION == STD_ON)
        uint32 timeout = CAN_TIMEOUT_COUNTER;
    #endif

    while ((((*pReg & mask) != 0U)) != expectedSet)
    {
    #if (CAN_TIMEOUT_PROCTECTION == STD_ON)
        if (timeout == 0U)
        {
            return E_NOT_OK;
        }
        timeout--;
    #endif
    }
    return E_OK;
}

static Can_ControllerStateType Can_s_controllerState[CAN_HW_MAX_CONTROLLERS] =
{
	CAN_STATE_UNTINT,
	CAN_STATE_UNTINT
};


void Can_Init(const Can_ConfigType *  ConfigPtr)
{
	CAN_RegMap_t * pCanBase = NULL;
	uint32 regTemp = 0U;
	
	#if ( CAN_DEV_ERROR_DETECT == STD_ON )
		if((ConfigPtr == NULL) || (ConfigPtr->controllerId >= CAN_HW_MAX_CONTROLLERS ))
		{
			return;
		}
	#endif
	
	pCanBase = Can_GetControllerBase(ConfigPtr->controllerId);
	
	if(pCanBase == NULL)
	{
		return;
	}

	pCanBase->MCR &= ~CAN_MCR_SLEEP_MASK;
	if(Can_s_WaitFlag(&pCanBase->MSR , CAN_MSR_SLAK_MASK,FALSE) != E_OK)
	{
		return;
	}

	pCanBase->MCR |= CAN_MCR_INRQ_MASK;
	if(Can_s_WaitFlag(&pCanBase->MSR , CAN_MSR_INAK_MASK,TRUE) != E_OK)
	{
		return;
	}


	regTemp = pCanBase->MCR;
	
	if(ConfigPtr->autoBusOffRecovery == TRUE)
	{
		regTemp |= CAN_MCR_ABOM_MASK;
	}
	else
	{
		regTemp &= ~CAN_MCR_ABOM_MASK;
	}

	if(ConfigPtr->noAutoRetransmit == TRUE)
	{
		regTemp |= CAN_MCR_NART_MASK;
	}
	else
	{
		regTemp &= ~CAN_MCR_NART_MASK;
	}
	
	if(ConfigPtr->txFifoPriority == TRUE)
	{
		regTemp |= CAN_MCR_TXFP_MASK;
	}
	else
	{
		regTemp &= ~CAN_MCR_TXFP_MASK;
	}
	
	if(ConfigPtr->rxfifoLockMode == TRUE)
	{
		regTemp |= CAN_MCR_RFLM_MASK;
	}
	else
	{
		regTemp &= ~CAN_MCR_RFLM_MASK;
	}
	
	pCanBase->MCR = regTemp;
	
	regTemp = 0U;
	
	regTemp |= (((uint32)(ConfigPtr->bitTiming.prescaler -1U) & CAN_BTR_BRP_MASK) << CAN_BTR_BRP_SHIFT );
	
	regTemp |= (((uint32)(ConfigPtr->bitTiming.timeSeg1 -1U) & CAN_BTR_TS1_MASK) << CAN_BTR_TS1_SHIFT);
	
	regTemp |= (((uint32)(ConfigPtr->bitTiming.timeSeg2 -1U) & CAN_BTR_TS2_MASK) << CAN_BTR_TS2_SHIFT);
	
	regTemp |= (((uint32)(ConfigPtr->bitTiming.sjw -1U) & CAN_BTR_SJW_MASK) << CAN_BTR_SJW_SHIFT);
	
	switch (ConfigPtr->opMode)
	{
		case CAN_MODE_NORMAL:
			break;
		
		case CAN_MODE_LOOPBACK:
			regTemp |= (1UL <<CAN_BTR_LBKM_SHIFT);
			break;
		
		case CAN_MODE_SILENT:
			regTemp |= (1UL << CAN_BTR_SILM_SHIFT);
		    break;
			
		case CAN_MODE_SILENT_LOOPBACK:
			regTemp |= (1UL <<CAN_BTR_LBKM_SHIFT);
			regTemp |= (1UL << CAN_BTR_SILM_SHIFT);
			break;
			
		default:
			break;
	}
	
	pCanBase->BTR = regTemp;
	


	Can_s_controllerState[ConfigPtr->controllerId] = CAN_STATE_STOPPED;
	
}







Std_ReturnType Can_SetConntrollerMode(uint8 Controller, Can_StateTarnsitionType Transition)
{
	
	Std_ReturnType retVal = E_NOT_OK;
	CAN_RegMap_t * pCanBase = NULL_PTR; 
	uint32 timeoutCounter = 0U;
	
	#if (CAN_DEV_ERROR_DETECT == STD_ON)
		if (Controller >= CAN_HW_MAX_CONTROLLERS)
		{
			return E_NOT_OK;
		}
		
		if (Can_s_controllerState[Controller] == CAN_STATE_UNTINT)
		{
			return E_NOT_OK;
		}
	#endif
	
	pCanBase = Can_GetControllerBase(Controller);
	
	if (pCanBase != NULL_PTR)
	{
		switch (Transition)
		{
			case CAN_T_START:
			
				if ((Can_s_controllerState[Controller] == CAN_STATE_STOPPED)||
					(Can_s_controllerState[Controller] == CAN_STATE_BUS_OFF))
			    {
						pCanBase->MCR &= ~(CAN_MCR_INRQ_MASK | CAN_MCR_SLEEP_MASK);
						
						#if (CAN_TIMEOUT_PROCTECTION == STD_ON)
							timeoutCounter == CAN_TIMEOUT_COUNTER;
							while(((pCanBase->MSR & CAN_MSR_INAK_MASK) != 0U) && (timeoutCounter > 0U))
							{
								timeoutCounter--;
							}
							
							if(timeoutCounter > 0U)
							{
								Can_s_controllerState[Controller] = CAN_STATE_STARTED;
								retVal = E_OK;
							}
							else
							{
								retVal = E_NOT_OK;
							}
							
						#else
							while((pCanBase->MSR & CAN_MSR_INAK_MASK) != 0U)
							{
								Can_s_controllerState[Controller] = CAN_STATE_STARTED;
								retVal = E_OK;
							}
							
						#endif
						
				}
				
				break;
				
			case CAN_T_STOP:
			
				if(Can_s_controllerState[Controller] == CAN_STATE_STARTED)
				{
					pCanBase->MCR |= CAN_MCR_INRQ_MASK;
					
					#if (CAN_TIMEOUT_PROCTECTION == STD_ON)
						timeoutCounter = CAN_TIMEOUT_COUNTER;
						while(((pCanBase->MSR & CAN_MSR_INAK_MASK) == 0U) && (timeoutCounter > 0U))
						{
							timeoutCounter--;
						}
						if(timeoutCounter > 0U)
						{
							Can_s_controllerState[Controller] = CAN_STATE_STOPPED;
							retVal = E_OK;
						}
						else
						{
							retVal = E_NOT_OK;
						}
					
					#else
							while((pCanBase->MSR & CAN_MSR_INAK_MASK) != 0U)
							{
								Can_s_controllerState[Controller] = CAN_STATE_STOPPED;
								retVal = E_OK;
							}	
					#endif
					
				}
				
				break;
				
			case CAN_T_SLEEP:
				if(Can_s_controllerState[Controller] == CAN_STATE_STOPPED)
				{
					pCanBase->MCR |= CAN_MCR_SLEEP_MASK;
					
					#if(CAN_TIMEOUT_PROCTECTION == STD_ON)
						timeoutCounter = CAN_TIMEOUT_COUNTER;
						while(((pCanBase->MSR & CAN_MSR_SLAK_MASK) == 0U) && (timeoutCounter > 0U))
						{
							timeoutCounter--;
						}
						if(timeoutCounter > 0U)
						{
							Can_s_controllerState[Controller] = CAN_STATE_STOPPED;
							retVal = E_OK;
						}
						else
						{
							retVal = E_NOT_OK;
						}
					#else
						while((pCanBase->MSR & CAN_MSR_SLAK_MASK) == 0U);
					    retVal = E_OK;
					#endif
				}
				
				break;
				
			case CAN_T_WAKEUP:
				pCanBase->MCR &= ~CAN_MCR_SLEEP_MASK;
				
				#if(CAN_TIMEOUT_PROCTECTION == STD_ON)
					timeoutCounter = CAN_TIMEOUT_COUNTER;
					while(((pCanBase->MSR & CAN_MSR_SLAK_MASK) != 0U) && (timeoutCounter > 0U))
					{
						timeoutCounter--;	
					}
					
					if(timeoutCounter > 0U)
					{
						Can_s_controllerState[Controller] = CAN_STATE_STOPPED;
						retVal = E_OK;
					}
				#else
					while((pCanBase->MSR & CAN_MSR_SLAK_MASK) == 0U);
					Can_s_controllerState[Controller] = CAN_STATE_STOPPED;
					retVal = E_OK;
				#endif
				
			default:
				retVal = E_NOT_OK;
				break; 
						
		}
	}
	
	return retVal; 
}




Std_ReturnType Can_Write(uint8 Controller , const Can_PduType * pduInfo)
{
	Std_ReturnType retVal   = E_NOT_OK;
	CAN_RegMap_t * pCanBase = NULL_PTR;
	uint8 mailboxIndex = 0xFFU;
	uint8 regTemp = 0U;
	uint8 i;
	
	
	#if (CAN_DEV_ERROR_DETECT == STD_ON )
		if(Controller >= CAN_HW_MAX_CONTROLLERS)
		{
			return E_NOT_OK;
		}
		
		if((pduInfo == NULL_PTR) || (pduInfo->sdu == NULL_PTR))
		{
			return E_NOT_OK;
		}
		
		if(Can_s_controllerState[Controller] != CAN_STATE_STARTED)
		{
			return E_NOT_OK;
		}
		
	#endif
	
	pCanBase = Can_GetControllerBase(Controller);
	
	if (pCanBase != NULL_PTR)
	{
		if((pCanBase->TSR & CAN_TSR_TME0_MASK ) != 0U)
		{
			mailboxIndex = 0U;
		}
		else if ((pCanBase->TSR & CAN_TSR_TME1_MASK) != 0U )
		{
			mailboxIndex = 1U;
		}
			else if ((pCanBase->TSR & CAN_TSR_TME2_MASK) != 0U )
		{
			mailboxIndex = 2U;
		}
		else
		{
			return E_NOT_OK;
		}
		
		regTemp = 0U;
		
		if(pduInfo->idFormat == CAN_ID_STANDARD)
		{
			regTemp |= ((pduInfo->id & 0x07FFUL) << CAN_TI1R_STID_SHIFT );
		}
		else
		{
			regTemp |= ((pduInfo->id & 0x1FFFFFFFUL) << CAN_TI1R_EXID_SHIFT);
			regTemp |= (1UL << CAN_TI1R_IDE_SHIFT);
		}
		
		if (pduInfo->frameType == CAN_FRAME_REMOTE)
		{
			regTemp |= (1UL << CAN_TI1R_RTR_SHIFT);
		}
		
		pCanBase->TxMailbox[mailboxIndex].TIR = regTemp;
		
		pCanBase->TxMailbox[mailboxIndex].TDTR = ((uint32)pduInfo->length & 0x0FUL);
		
		if (pduInfo->frameType == CAN_FRAME_DATA)
		{
			regTemp = 0U;
			for (i = 0U; (i < 4U) && (i < pduInfo->length) ; i++)
			{
				regTemp |= (((uint32) pduInfo->sdu[i]) << (i*8U));
			}
			
			pCanBase->TxMailbox[mailboxIndex].TDLR = regTemp;
			
			regTemp =0U;
			for (i = 4U; (i < 8U) && (i < pduInfo->length) ; i++)
			{
				regTemp |= (((uint32)pduInfo->sdu[i]) << ((i - 4U) * 8U));
			}
			
			pCanBase->TxMailbox[mailboxIndex].TDHR =  regTemp;
			
		}
		
		pCanBase->TxMailbox[mailboxIndex].TIR |= (1UL << CAN_TI1R_TXRQ_SHIFT);
		
		retVal = E_OK;
	
	}
	
	return retVal;
		
}

Std_ReturnType Can_FilterInit(const Can_FilterConfigType * FilterConfig)
{
    CAN_RegMap_t * pCanBase = CAN1;
    uint32 bankBitMask = 0U;
    
    #if (CAN_DEV_ERROR_DETECT == STD_ON)
        if ((FilterConfig == NULL_PTR) || (FilterConfig->filterBankId >= CAN_HW_MAX_FILTER_BANKS))
        {
            return E_NOT_OK;
        }
    #endif
    
    bankBitMask = (1UL << FilterConfig->filterBankId);
    
    pCanBase->FMR |= CAN_FMR_FINIT_MASK;
    
    pCanBase->FA1R &= ~bankBitMask;
    
    if (FilterConfig->filterScale == CAN_FILTER_SCALE_32BIT)
    {
        pCanBase->FS1R |= bankBitMask;
        pCanBase->FilterBank[FilterConfig->filterBankId].FR1 = (FilterConfig->filterId << 3U);
        pCanBase->FilterBank[FilterConfig->filterBankId].FR2 = (FilterConfig->filterMask << 3U);
    }
    else
    {
        pCanBase->FS1R &= ~bankBitMask;
    }
    
    if (FilterConfig->filterMode == CAN_FILTER_MODE_IDLIST)
    {
        pCanBase->FM1R |= bankBitMask;
    }
    else
    {
        pCanBase->FM1R &= ~bankBitMask;
    }
    
    if (FilterConfig->fifoAssignment == 1U)
    {
        pCanBase->FFA1R |= bankBitMask;
    }
    else
    {
        pCanBase->FFA1R &= ~bankBitMask;
    }
    
    if (FilterConfig->enable == TRUE)
    {
        pCanBase->FA1R |= bankBitMask;
    }
    
    pCanBase->FMR &= ~CAN_FMR_FINIT_MASK;
    
    return E_OK;
}

Std_ReturnType Can_Read(uint8 Controller,uint8 FifoNumber , Can_PduType * pduInfo )
{

	Std_ReturnType retVal = E_NOT_OK;
	CAN_RegMap_t * pCanBase = NULL_PTR;
	uint32 regTemp = 0U;
	uint8 i = 0u;


	#if (CAN_DEV_ERROR_DETECT == STD_ON)
		if((Controller >= CAN_HW_MAX_CONTROLLERS) || (pduInfo == NULL))
		{
			return E_NOT_OK;
		}
		if(FifoNumber > CAN_RX_FIFO1)
		{
			return E_NOT_OK;
		}
		if(Can_s_controllerState[Controller] != CAN_STATE_STARTED)
		{
			return E_NOT_OK;
		}

	#endif

	pCanBase = Can_GetControllerBase(Controller);
	if (pCanBase != NULL_PTR)
	{
		volatile uint32 * pRFR = (FifoNumber == CAN_RX_FIFO0) ? &(pCanBase->RF0R): &(pCanBase->RF1R);
		if ((*pRFR & CAN_RFR_FMP_MASK) != 0U)
			{
				regTemp = pCanBase->RxFifio[FifoNumber].RIR;

				if ((regTemp & (1UL << CAN_RI1R_IDE_SHIFT)) == 0U)
				{
					pduInfo->idFormat = CAN_ID_STANDARD;
					pduInfo->id = (regTemp >> CAN_RI1R_STID_SHIFT) & 0x07FFUL;
				}
				else
				{
					pduInfo->idFormat = CAN_ID_EXTENDED;
					pduInfo->id = (regTemp >> CAN_RI1R_EXID_SHIFT) & 0x1FFFFFFFUL;
				}

				if ((regTemp & (1UL << CAN_RI1R_RTR_SHIFT)) == 0U)
				{
					pduInfo->frameType = CAN_FRAME_DATA;
				}
				else
				{
					pduInfo->frameType = CAN_FRAME_REMOTE;
				}

				pduInfo->length = (uint8)(pCanBase->RxFifio[FifoNumber].RDTR & 0x0FUL);

				if (pduInfo->frameType == CAN_FRAME_DATA)
				{
					regTemp = pCanBase->RxFifio[FifoNumber].RDLR;
					for (i = 0U; (i < 4U) && (i < pduInfo->length); i++)
					{
						pduInfo->sdu[i] = (uint8)(regTemp >> (i * 8U));
					}

					regTemp = pCanBase->RxFifio[FifoNumber].RDHR;
					for (i = 4U; (i < 8U) && (i < pduInfo->length); i++)
					{
						pduInfo->sdu[i] = (uint8)(regTemp >> ((i - 4U) * 8U));
					}
				}

				*pRFR |= CAN_RFOM_MASK;

				retVal = E_OK;
			}
    }

    return retVal;
}	


Std_ReturnType Can_EnableInterrupts(uint8 Controller, uint32 InterruptMask)
{
    CAN_RegMap_t * pCanBase = Can_GetControllerBase(Controller);
    
    if (pCanBase != NULL_PTR)
    {
        pCanBase->IER |= InterruptMask;
        return E_OK;
    }
    return E_NOT_OK;
}



Std_ReturnType Can_RegisterCallback(uint8 Controller, uint32 InterruptSource, Can_CallbackFnType CallbackFn)
{
    if ((Controller < CAN_HW_MAX_CONTROLLERS) && (CallbackFn != NULL_PTR))
    {
        if (InterruptSource == CAN_IT_RX_FIFO0_MSG_PENDING)
        {
            Can_s_rxFifo0Callback[Controller] = CallbackFn;
            return E_OK;
        }
    }
    return E_NOT_OK;
}


void CAN1_RX0_IRQHandler(void)
{
    if ((CAN1->RF0R & CAN_RFR_FMP_MASK) != 0U)
    {
        if (Can_s_rxFifo0Callback[CAN_INSTANCE_1] != NULL_PTR)
        {
            Can_s_rxFifo0Callback[CAN_INSTANCE_1]();
        }
    }
}








