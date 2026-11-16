/*
*************** ADC_reg.h ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/


#ifndef ADC_REG_H
#define ADC_REG_H

#include "std_types.h"



typedef struct {
    __I  uint32 SR;     // Status Register                 (Read Only change by hradware)
    __IO uint32 CR1;    // Control Register 1              (Read / Write)
    __IO uint32 CR2;    // Control Register 2              (Read / Write)
    __IO uint32 SMPR1;  // Sample Time Register 1          (Read / Write)
    __IO uint32 SMPR2;  // Sample Time Register 2          (Read / Write)
    __IO uint32 JOFR1;  // Injected Channel Data Offset 1  (Read / Write)
    __IO uint32 JOFR2;  // Injected Channel Data Offset 2  (Read / Write)
    __IO uint32 JOFR3;  // Injected Channel Data Offset 3  (Read / Write)
    __IO uint32 JOFR4;  // Injected Channel Data Offset 4  (Read / Write)
    __IO uint32 HTR;     // Watchdog Higher Threshold       (Read / Write)
    __IO uint32 LTR;     // Watchdog Lower Threshold        (Read / Write)
    __IO uint32 SQR1;    // Regular Sequence Register 1     (Read / Write)
    __IO uint32 SQR2;    // Regular Sequence Register 2     (Read / Write)
    __IO uint32 SQR3;    // Regular Sequence Register 3     (Read / Write)
    __IO uint32 JSQR;    // Injected Sequence Register      (Read / Write)
    __I  uint32 JDR1;    // Injected Data Register 1        (Read Only For Read The Data)
    __I  uint32 JDR2;    // Injected Data Register 2        (Read Only)
    __I  uint32 JDR3;    // Injected Data Register 3        (Read Only)
    __I  uint32 JDR4;    // Injected Data Register 4        (Read Only)
    __I  uint32 DR;     // Regular Data Register           (Read Only For Read The Data  )
} ADC_TypeDef;


typedef struct {
    __IO uint32 CSR;    // Common Status Register          (Offset: 0x300 relative to ADC1 base)
    __IO uint32 CCR;    // Common Control Register         (Offset: 0x304)
    __IO uint32 CDR;    // Common Regular Data Register    (Offset: 0x308)
} ADC_Common_TypeDef;



#define ADC1_BASE           0x40012000UL
#define ADC2_BASE           0x40013000UL
#define ADC3_BASE           0x40014000UL  
#define ADC_COMMON_BASE     (0x40012000UL + 0x300UL)
#define ADC1                ((ADC_TypeDef *) ADC1_BASE)
#define ADC2                ((ADC_TypeDef *) ADC2_BASE)
#define ADC3                ((ADC_TypeDef *) ADC3_BASE)
#define ADC_COMMON          ((ADC_Common_TypeDef *) ADC_COMMON_BASE)





#endif