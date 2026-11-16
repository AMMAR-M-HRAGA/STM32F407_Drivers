/*
*************** ADC_program.c ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/

#include "std_types.h"
#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_reg.h"


static Std_ReturnType Git_ADC(ADC_TypeDef * pADC ,ADC_TypeDef ** pBackADC )
{
    if(pADC == NULL_PTR)
    {
        return E_NOT_OK;
    }
    if(pADC == ADC1) 
    {
        pBackADC = ADC1;
    }
    else if (pADC == ADC2)
    {
        pBackADC = ADC2;
    }
    else if (pADC == ADC3)
    {
        pBackADC = ADC3;
    }
    else
    {
        return E_NOT_OK;
    }

    return E_OK;
}

Std_ReturnType ADC_Init(ADC_TypeDef * pADC , ADC_Config_t * ADC_Config)
{
    ADC_TypeDef * ADC = NULL_PTR;
    if((Git_ADC(pADC,&ADC) != E_OK)  || (ADC_Config == NULL_PTR))
    {
        return E_NOT_OK;
    }

    ADC_COMMON->CCR |=((ADC_Config->Prescaler & CCR_PRESCALER_MASK) << CCR_PRESCALER_SHIFT);

    ADC->CR2 = ((ADC_Config->DataAlignment & CR2_ALIGNMENT_MASK) << CR2_ALIGNMENT_SHIFT)|
               ((ADC_Config->ContinuousConvMode & CR2_CONTINUOUS_MASK) << CR2_CONTINUOUS_SHIFT)|
               ((ADC_Config->EXTrigConvEdgeInRegular & CR2_TRIGGER_REGULAR_MASK) << CR2_TRIGGER_REGULAR_SHIFT)|
               ((ADC_Config->ExTrigConvEdgeInInjected & CR2_TRIGGER_INJECTED_MASK) << CR2_TRIGGER_INJECTED_SHIFT);


    ADC->CR1 |= ((ADC_Config->Resolution & CR1_RESOLUTION_MASK) << CR1_RESOLUTION_SHIFT);

    ADC->SQR1 |= ((ADC_Config->NbrOfConversion & SQR1_NUMBER_OF_CONV_MASK) << SQR1_NUMBER_OF_CONV_SHIFT);


    
}


Std_ReturnType ADC_ChannalConfig(ADC_TypeDef * pADC , uint8 Channal , uint8 SQRNumber)
{
    ADC_TypeDef * ADC = NULL_PTR;
    if((Git_ADC(pADC,&ADC) != E_OK))
    {
        return E_NOT_OK;
    }

    if((Channal < 0U) || (Channal > 15U) || (SQRNumber < 1U) || (SQRNumber > 16U) )
    {
        return E_NOT_OK;
    }

    uint8 adjustedSeq = SQRNumber -1;
    uint8 regNumber = adjustedSeq/6U;
    uint8 SQRIndex  = adjustedSeq%6U;

    if(regNumber == 0U)
    {
        ADC->SQR3 |= (Channal << (SQRIndex*5));
    }
    else if(regNumber == 1U)
    {
        ADC->SQR2 |= (Channal << (SQRIndex*5));
    }
    else if(regNumber == 2U)
    {
        ADC->SQR1 |= (Channal << (SQRIndex*5));
    }
    else
    {
        return E_NOT_OK;  
    }

    return E_OK;
}

Std_ReturnType ADC_SynchStartConversion(ADC_TypeDef * pADC , uint16 * pData)
{
    uint32 timeout = ADC_TIMEOUT;
    ADC_TypeDef * ADC = NULL_PTR;
    if((Git_ADC(pADC,&ADC) != E_OK) || (pData == NULL_PTR))
    {
        return E_NOT_OK;
    }

    ADC->CR2 |= CR2_START_CONV_MASK;                  

    while (((ADC->SR & SR_END_OF_ONV_MASK) == 0U) && (timeout > 0U))
    {
        timeout--;
    }
    if((timeout == 0U)  && ((ADC->SR & SR_END_OF_ONV_MASK) == 0U))
    {
        return E_NOT_OK;
    }

    *pData = ADC->DR & (0x0000FFFFUL);


}