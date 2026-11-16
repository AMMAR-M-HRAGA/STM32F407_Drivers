/*
*************** SYSTICK_interface.h ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/

#ifndef SYSTICK_INTERFACE_H
#define SYSTICK_INTERFACE_H

#include "std_types.h"







void SysTick_Init(uint32 ticks);
void SysTick_SynchDelayMs(uint32 ms , uint32 cpu_freq_hz);
void SysTick_AsynchDelayMs(uint32 ms , uint32 cpu_freq_hz , void (*pCallbackFunc ) (void));



#endif