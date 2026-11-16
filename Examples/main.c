#include "GPIO_config.h"
#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "SYSTICK_interface.h"

#define CPU_FEQ 42000000UL
void Led()
{
    GPIO_ToggleoutputPin(GPIOD,12U);
}


int main(void)
{
            

    GPIO_ClockControl(GPIOD,ENABLE);
    GPIO_Init(&PIN12_Config);
    SysTick_AsynchDelayMs(2000,CPU_FEQ,&Led);
    while(1)
    {
       
    }



    return 0;
}

