/*
*************** EXTI_reg.h ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/



#ifndef _EXTI_REG_H
#define _EXTI_REG_H

#include "std_types.h"
typedef struct
{
  volatile u32 IMR;    /*!< EXTI Interrupt mask register,            Address offset: 0x00 */
  volatile u32 EMR;    /*!< EXTI Event mask register,                Address offset: 0x04 */
  volatile u32 RTSR;   /*!< EXTI Rising trigger selection register,  Address offset: 0x08 */
  volatile u32 FTSR;   /*!< EXTI Falling trigger selection register, Address offset: 0x0C */
  volatile u32 SWIER;  /*!< EXTI Software interrupt event register,  Address offset: 0x10 */
  volatile u32 PR;     /*!< EXTI Pending register,                   Address offset: 0x14 */
} EXTI_TypeDef;

typedef struct
{
  volatile u32 MEMRMP;       /*!< SYSCFG memory remap register,                      Address offset: 0x00      */
  volatile u32 PMC;          /*!< SYSCFG peripheral mode configuration register,     Address offset: 0x04      */
  volatile u32 EXTICR[4];    /*!< SYSCFG external interrupt configuration registers, Address offset: 0x08-0x14 */
  u32          RESERVED[2];  /*!< Reserved, 0x18-0x1C                                                          */
  volatile u32 CMPCR;        /*!< SYSCFG Co  mpensation cell control register,         Address offset: 0x20      */
} SYSCFG_TypeDef;

#define EXTI_BASE_ADDRESS    (0x40013C00UL)
#define SYSCFG_BASE_ADDRESS  (0x40013800UL)

#define EXTI   ((EXTI_TypeDef*)EXTI_BASE_ADDRESS)
#define SYSCFG ((SYSCFG_TypeDef*)SYSCFG_BASE_ADDRESS)

#define RCC_BASE_ADDRESS  (0x40023800UL)
#define RCC_APB2ENR       *((volatile u32* )(RCC_BASE_ADDRESS+0x44))
#define RCC_APB2LPENR     *((volatile u32* )(RCC_BASE_ADDRESS+0x4C))




















#endif
