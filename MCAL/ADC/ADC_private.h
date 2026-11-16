/*
*************** ADC_private.h ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/

#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

#define ADC_TIMEOUT                  (70000UL)

#define SR_END_OF_ONV_MASK           (1UL << 1U)

#define CCR_PRESCALER_MASK           (0x30UL) 
#define CCR_PRESCALER_SHIFT          (16U) 

#define CR2_ALIGNMENT_MASK           (1UL << 11U)
#define CR2_ALIGNMENT_SHIFT          (11U)

#define CR2_CONTINUOUS_MASK          (1UL << 1U)
#define CR2_CONTINUOUS_SHIFT         (1U)

#define CR2_TRIGGER_REGULAR_MASK     (0xFUL << 28U)
#define CR2_TRIGGER_REGULAR_SHIFT    (28U)

#define CR2_TRIGGER_INJECTED_MASK    (0xFUL << 20U)
#define CR2_TRIGGER_INJECTED_SHIFT   (20U)

#define CR2_START_CONV_MASK          (1UL << 30U)

#define CR1_RESOLUTION_MASK          (3UL << 24U)
#define CR1_RESOLUTION_SHIFT         (24U)

#define SQR1_NUMBER_OF_CONV_MASK     (7UL << 20U)
#define SQR1_NUMBER_OF_CONV_SHIFT    (20U)












#endif