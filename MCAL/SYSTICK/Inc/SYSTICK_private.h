/*
*************** SYSTICK_private.h ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/

#ifndef SYSTICK_PRIVATE_H
#define SYSTICK_PRIVATE_H

#include "std_types.h"

#define SYSTICK_RVR_MASK            (0x00ffffff)


#define SYSTICK_CSR_ENABLE_MASK     (1U << 0)
#define SYSTICK_CSR_INT_MASK        (1U << 1)
#define SYSTICK_CSR_CLCKSOURCE_MASK (1U << 2)
#define SYSTICK_CSR_COUNTFLAG_MASK  (1U << 16)




typedef struct {
   volatile uint32 CSR;
   volatile uint32 RVR;
   volatile uint32 CVR;
   volatile uint32 CALIB;
}SysTick_Type;

#define SYSTICK_BASE   (0xE000E010)
#define STSTICK        ((SysTick_Type *)SYSTICK_BASE)



#endif