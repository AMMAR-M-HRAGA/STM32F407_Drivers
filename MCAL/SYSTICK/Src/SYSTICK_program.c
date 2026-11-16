#include "std_types.h"
#include "SYSTICK_interface.h"
#include "SYSTICK_private.h"



static uint32 volatile SysTickCounter = 0;
static void (*spCallBackFunc)(void)= NULL_PTR;
void SysTick_Init(uint32 ticks)
{


    STSTICK->CSR = 0UL;

    STSTICK->RVR = ((ticks-1U) & SYSTICK_RVR_MASK);

    STSTICK->CVR = 0UL;

    STSTICK->CSR  |= SYSTICK_CSR_CLCKSOURCE_MASK;
    STSTICK->CSR  |= SYSTICK_CSR_ENABLE_MASK;

} 

void SysTick_SynchDelayMs(uint32 ms , uint32 cpu_freq_hz)
{
    uint32 ticks_per_ms = cpu_freq_hz/1000U;

    for(uint32 i =0U; i<ms;i++)
    {
        STSTICK->RVR   = ((ticks_per_ms-1U) & SYSTICK_RVR_MASK);;
        STSTICK->CVR   = 0UL;
        STSTICK->CSR  |= SYSTICK_CSR_CLCKSOURCE_MASK;
        STSTICK->CSR  |= SYSTICK_CSR_ENABLE_MASK;

        while(!(STSTICK->CSR  & SYSTICK_CSR_COUNTFLAG_MASK));        
        STSTICK->CSR  = 0U;

    }

}


void SysTick_AsynchDelayMs(uint32 ms , uint32 cpu_freq_hz , void (*pCallbackFunc ) (void))
{
    uint32 ticks_per_ms = cpu_freq_hz/1000U;
    STSTICK->RVR   = ((ticks_per_ms-1U) & SYSTICK_RVR_MASK);;
    STSTICK->CVR   = 0UL;
    SysTickCounter = ms;
    if(pCallbackFunc != NULL )
    {
        spCallBackFunc = pCallbackFunc;
    }
    STSTICK->CSR   = SYSTICK_CSR_CLCKSOURCE_MASK | SYSTICK_CSR_ENABLE_MASK | SYSTICK_CSR_INT_MASK;
    
}

void SysTick_Handler(void)
{
    SysTickCounter--;

    if(SysTickCounter == 0U)
    {
        STSTICK->CSR &= ~SYSTICK_CSR_INT_MASK;
        STSTICK->CSR &= ~SYSTICK_CSR_ENABLE_MASK;
        if(spCallBackFunc != NULL_PTR)
        {
            spCallBackFunc();
        }
        else
        {
            //do nothing
        }
    }
    else
    {
        // do nothing
    }

}