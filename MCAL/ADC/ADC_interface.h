/*
*************** ADC_interface.h ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/

#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#include "std_types.h"
#include "ADC_reg.h"

typedef struct {
    uint8 Prescaler;
    uint8 DataAlignment;
    uint8 Resolution;
    uint8 ContinuousConvMode;
    uint8 EXTrigConvEdgeInRegular;
    uint8 ExTrigConvEdgeInInjected;
    uint8 NbrOfConversion;

}ADC_Config_t;


Std_ReturnType ADC_Init(ADC_TypeDef * pADC , ADC_Config_t * ADC_Config);


Std_ReturnType ADC_ChannalConfig(ADC_TypeDef * pADC , uint8 Channal , uint8 SQRNumber);




#endif