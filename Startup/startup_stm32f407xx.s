/*
 * Full Startup file for STM32F407xx Microcontrollers (GNU Toolchain)
 */
  .syntax unified
  .cpu cortex-m4
  .fpu softvfp
  .thumb

.global g_pfnVectors
.global Default_Handler

/* Symbols defined in Linker Script (.ld) */
.word _sidata
.word _sdata
.word _edata
.word _sbss
.word _ebss

.section .text.Reset_Handler
  .weak Reset_Handler
  .type Reset_Handler, %function
Reset_Handler:
  ldr   sp, =_estack      /* Initialize Stack Pointer */

/* Copy the data segment initializers from flash to SRAM */
  movs  r1, #0
  b     LoopCopyDataInit

CopyDataInit:
  ldr   r3, =_sidata
  ldr   r3, [r3, r1]
  str   r3, [r0, r1]
  adds  r1, r1, #4

LoopCopyDataInit:
  ldr   r0, =_sdata
  ldr   r3, =_edata
  adds  r2, r0, r1
  cmp   r2, r3
  bcc   CopyDataInit
  
/* Zero fill the bss segment */
  ldr   r2, =_sbss
  b     LoopFillZerobss

FillZerobss:
  movs  r3, #0
  str   r3, [r2], #4

LoopFillZerobss:
  ldr   r3, = _ebss
  cmp   r2, r3
  bcc   FillZerobss

/* Call the application's entry point */
  bl    main
  bx    lr
.size Reset_Handler, .-Reset_Handler

/**
 * @brief  Default interrupt handler
 */
  .section .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b     Infinite_Loop
  .size Default_Handler, .-Default_Handler

/*******************************************************************************
* Vector Table
*******************************************************************************/
  .section .isr_vector,"a",%progbits
  .type g_pfnVectors, %object
  .size g_pfnVectors, .-g_pfnVectors

g_pfnVectors:
  .word _estack
  .word Reset_Handler
  .word NMI_Handler
  .word HardFault_Handler
  .word MemManage_Handler
  .word BusFault_Handler
  .word UsageFault_Handler
  .word 0
  .word 0
  .word 0
  .word 0
  .word SVC_Handler
  .word DebugMon_Handler
  .word 0
  .word PendSV_Handler
  .word SysTick_Handler

  /* External Interrupts (STM32F407 Specific) */
  .word WWDG_IRQHandler
  .word PVD_IRQHandler
  .word TAMP_STAMP_IRQHandler
  .word RTC_WKUP_IRQHandler
  .word FLASH_IRQHandler
  .word RCC_IRQHandler
  .word EXTI0_IRQHandler
  .word EXTI1_IRQHandler
  .word EXTI2_IRQHandler
  .word EXTI3_IRQHandler
  .word EXTI4_IRQHandler
  .word DMA1_Stream0_IRQHandler
  .word DMA1_Stream1_IRQHandler
  .word DMA1_Stream2_IRQHandler
  .word DMA1_Stream3_IRQHandler
  .word DMA1_Stream4_IRQHandler
  .word DMA1_Stream5_IRQHandler
  .word DMA1_Stream6_IRQHandler
  .word ADC_IRQHandler
  .word CAN1_TX_IRQHandler
  .word CAN1_RX0_IRQHandler
  .word CAN1_RX1_IRQHandler
  .word CAN1_SCE_IRQHandler
  .word EXTI9_5_IRQHandler
  .word TIM1_BRK_TIM9_IRQHandler
  .word TIM1_UP_TIM10_IRQHandler
  .word TIM1_TRG_COM_TIM11_IRQHandler
  .word TIM1_CC_IRQHandler
  .word TIM2_IRQHandler
  .word TIM3_IRQHandler
  .word TIM4_IRQHandler
  .word I2C1_EV_IRQHandler
  .word I2C1_ER_IRQHandler
  .word I2C2_EV_IRQHandler
  .word I2C2_ER_IRQHandler
  .word SPI1_IRQHandler
  .word SPI2_IRQHandler
  .word USART1_IRQHandler
  .word USART2_IRQHandler
  .word USART3_IRQHandler
  .word EXTI15_10_IRQHandler
  .word RTC_Alarm_IRQHandler
  .word OTG_FS_WKUP_IRQHandler
  .word TIM8_BRK_TIM12_IRQHandler
  .word TIM8_UP_TIM13_IRQHandler
  .word TIM8_TRG_COM_TIM14_IRQHandler
  .word TIM8_CC_IRQHandler
  .word DMA1_Stream7_IRQHandler
  .word FSMC_IRQHandler
  .word SDIO_IRQHandler
  .word TIM5_IRQHandler
  .word SPI3_IRQHandler
  .word UART4_IRQHandler
  .word UART5_IRQHandler
  .word TIM6_DAC_IRQHandler
  .word TIM7_IRQHandler
  .word DMA2_Stream0_IRQHandler
  .word DMA2_Stream1_IRQHandler
  .word DMA2_Stream2_IRQHandler
  .word DMA2_Stream3_IRQHandler
  .word DMA2_Stream4_IRQHandler
  .word ETH_IRQHandler
  .word ETH_WKUP_IRQHandler
  .word CAN2_TX_IRQHandler
  .word CAN2_RX0_IRQHandler
  .word CAN2_RX1_IRQHandler
  .word CAN2_SCE_IRQHandler
  .word OTG_FS_IRQHandler
  .word DMA2_Stream5_IRQHandler
  .word DMA2_Stream6_IRQHandler
  .word DMA2_Stream7_IRQHandler
  .word USART6_IRQHandler
  .word I2C3_EV_IRQHandler
  .word I2C3_ER_IRQHandler
  .word OTG_HS_EP1_OUT_IRQHandler
  .word OTG_HS_EP1_IN_IRQHandler
  .word OTG_HS_WKUP_IRQHandler
  .word OTG_HS_IRQHandler
  .word DNE_IRQHandler
  .word CRYP_IRQHandler
  .word HASH_RNG_IRQHandler
  .word FPU_IRQHandler

/*******************************************************************************
* Provide weak aliases for System and External Handlers to Default_Handler.
*******************************************************************************/
  .macro SET_DEFAULT_HANDLER handler
  .weak \handler
  .thumb_set \handler, Default_Handler
  .endm

  SET_DEFAULT_HANDLER NMI_Handler
  SET_DEFAULT_HANDLER HardFault_Handler
  SET_DEFAULT_HANDLER MemManage_Handler
  SET_DEFAULT_HANDLER BusFault_Handler
  SET_DEFAULT_HANDLER UsageFault_Handler
  SET_DEFAULT_HANDLER SVC_Handler
  SET_DEFAULT_HANDLER DebugMon_Handler
  SET_DEFAULT_HANDLER PendSV_Handler
  SET_DEFAULT_HANDLER SysTick_Handler

  SET_DEFAULT_HANDLER WWDG_IRQHandler
  SET_DEFAULT_HANDLER PVD_IRQHandler
  SET_DEFAULT_HANDLER TAMP_STAMP_IRQHandler
  SET_DEFAULT_HANDLER RTC_WKUP_IRQHandler
  SET_DEFAULT_HANDLER FLASH_IRQHandler
  SET_DEFAULT_HANDLER RCC_IRQHandler
  SET_DEFAULT_HANDLER EXTI0_IRQHandler
  SET_DEFAULT_HANDLER EXTI1_IRQHandler
  SET_DEFAULT_HANDLER EXTI2_IRQHandler
  SET_DEFAULT_HANDLER EXTI3_IRQHandler
  SET_DEFAULT_HANDLER EXTI4_IRQHandler
  SET_DEFAULT_HANDLER DMA1_Stream0_IRQHandler
  SET_DEFAULT_HANDLER DMA1_Stream1_IRQHandler
  SET_DEFAULT_HANDLER DMA1_Stream2_IRQHandler
  SET_DEFAULT_HANDLER DMA1_Stream3_IRQHandler
  SET_DEFAULT_HANDLER DMA1_Stream4_IRQHandler
  SET_DEFAULT_HANDLER DMA1_Stream5_IRQHandler
  SET_DEFAULT_HANDLER DMA1_Stream6_IRQHandler
  SET_DEFAULT_HANDLER ADC_IRQHandler
  SET_DEFAULT_HANDLER CAN1_TX_IRQHandler
  SET_DEFAULT_HANDLER CAN1_RX0_IRQHandler
  SET_DEFAULT_HANDLER CAN1_RX1_IRQHandler
  SET_DEFAULT_HANDLER CAN1_SCE_IRQHandler
  SET_DEFAULT_HANDLER EXTI9_5_IRQHandler
  SET_DEFAULT_HANDLER TIM1_BRK_TIM9_IRQHandler
  SET_DEFAULT_HANDLER TIM1_UP_TIM10_IRQHandler
  SET_DEFAULT_HANDLER TIM1_TRG_COM_TIM11_IRQHandler
  SET_DEFAULT_HANDLER TIM1_CC_IRQHandler
  SET_DEFAULT_HANDLER TIM2_IRQHandler
  SET_DEFAULT_HANDLER TIM3_IRQHandler
  SET_DEFAULT_HANDLER TIM4_IRQHandler
  SET_DEFAULT_HANDLER I2C1_EV_IRQHandler
  SET_DEFAULT_HANDLER I2C1_ER_IRQHandler
  SET_DEFAULT_HANDLER I2C2_EV_IRQHandler
  SET_DEFAULT_HANDLER I2C2_ER_IRQHandler
  SET_DEFAULT_HANDLER SPI1_IRQHandler
  SET_DEFAULT_HANDLER SPI2_IRQHandler
  SET_DEFAULT_HANDLER USART1_IRQHandler
  SET_DEFAULT_HANDLER USART2_IRQHandler
  SET_DEFAULT_HANDLER USART3_IRQHandler
  SET_DEFAULT_HANDLER EXTI15_10_IRQHandler
  SET_DEFAULT_HANDLER RTC_Alarm_IRQHandler
  SET_DEFAULT_HANDLER OTG_FS_WKUP_IRQHandler
  SET_DEFAULT_HANDLER TIM8_BRK_TIM12_IRQHandler
  SET_DEFAULT_HANDLER TIM8_UP_TIM13_IRQHandler
  SET_DEFAULT_HANDLER TIM8_TRG_COM_TIM14_IRQHandler
  SET_DEFAULT_HANDLER TIM8_CC_IRQHandler
  SET_DEFAULT_HANDLER DMA1_Stream7_IRQHandler
  SET_DEFAULT_HANDLER FSMC_IRQHandler
  SET_DEFAULT_HANDLER SDIO_IRQHandler
  SET_DEFAULT_HANDLER TIM5_IRQHandler
  SET_DEFAULT_HANDLER SPI3_IRQHandler
  SET_DEFAULT_HANDLER UART4_IRQHandler
  SET_DEFAULT_HANDLER UART5_IRQHandler
  SET_DEFAULT_HANDLER TIM6_DAC_IRQHandler
  SET_DEFAULT_HANDLER TIM7_IRQHandler
  SET_DEFAULT_HANDLER DMA2_Stream0_IRQHandler
  SET_DEFAULT_HANDLER DMA2_Stream1_IRQHandler
  SET_DEFAULT_HANDLER DMA2_Stream2_IRQHandler
  SET_DEFAULT_HANDLER DMA2_Stream3_IRQHandler
  SET_DEFAULT_HANDLER DMA2_Stream4_IRQHandler
  SET_DEFAULT_HANDLER ETH_IRQHandler
  SET_DEFAULT_HANDLER ETH_WKUP_IRQHandler
  SET_DEFAULT_HANDLER CAN2_TX_IRQHandler
  SET_DEFAULT_HANDLER CAN2_RX0_IRQHandler
  SET_DEFAULT_HANDLER CAN2_RX1_IRQHandler
  SET_DEFAULT_HANDLER CAN2_SCE_IRQHandler
  SET_DEFAULT_HANDLER OTG_FS_IRQHandler
  SET_DEFAULT_HANDLER DMA2_Stream5_IRQHandler
  SET_DEFAULT_HANDLER DMA2_Stream6_IRQHandler
  SET_DEFAULT_HANDLER DMA2_Stream7_IRQHandler
  SET_DEFAULT_HANDLER USART6_IRQHandler
  SET_DEFAULT_HANDLER I2C3_EV_IRQHandler
  SET_DEFAULT_HANDLER I2C3_ER_IRQHandler
  SET_DEFAULT_HANDLER OTG_HS_EP1_OUT_IRQHandler
  SET_DEFAULT_HANDLER OTG_HS_EP1_IN_IRQHandler
  SET_DEFAULT_HANDLER OTG_HS_WKUP_IRQHandler
  SET_DEFAULT_HANDLER OTG_HS_IRQHandler
  SET_DEFAULT_HANDLER DNE_IRQHandler
  SET_DEFAULT_HANDLER CRYP_IRQHandler
  SET_DEFAULT_HANDLER HASH_RNG_IRQHandler
  SET_DEFAULT_HANDLER FPU_IRQHandler