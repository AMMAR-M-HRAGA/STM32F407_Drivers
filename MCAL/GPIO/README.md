# 🛠️ STM32F407VG MCAL GPIO Driver

A bare-metal, highly modular Microcontroller Abstraction Layer (MCAL) driver for the **General Purpose Input/Output (GPIO)** peripheral on the **STM32F407VG** (Cortex-M4) microcontroller. This driver is built completely from scratch, emphasizing bare-metal optimization without using any external HAL libraries.

---

## 🚀 Features

* **Complete Port Mapping:** Full support for all STM32F407VG ports from `GPIOA` to `GPIOI`.
* **Flexible Pin Control:** Independent configuration for modes (Input, Output, Alternate Function, Analog).
* **Hardware Output Control:** Configurable output types (Push-Pull / Open-Drain) and output speeds (Low, Medium, Fast, High).
* **Internal Resistor Management:** Native handling of internal Pull-Up, Pull-Down, and Floating states.
* **Alternate Function Support:** Full integration of Alternate Function registers via `AFR[2]` array routing.

---

## 📁 File Structure

The driver follows a strict layered software architecture designed for maintainability:
```text
├── Inc/
│   ├── GPIO_interface.h  <-- Public APIs, Pin/Port configurations, and User structs.
│   ├── GPIO_config.h     <-- Pre-build static configurations (Default configurations).
│   ├── GPIO_private.h    <-- Internal private driver constants and helper macros.
│   └── GPIO_reg.h        <-- Base addresses and peripheral register definitions (Memory Map).
└── Src/
    └── GPIO_program.c    <-- Implementation of core GPIO configuration and control logic.
	
---	

🔧 Driver Configurations & APIs
typedef struct {
    u8 PinMode;       // e.g., GPIO_MODE_OUTPUT, GPIO_MODE_INPUT
    u8 PinNumber;     // e.g., GPIO_PIN_NO_0 to GPIO_PIN_NO_15
    u8 OutputType;    // e.g., GPIO_OP_TYPE_PP, GPIO_OP_TYPE_OD
    u8 SpeedType;     // e.g., GPIO_SPEED_FAST, GPIO_SPEED_LOW
    u8 PullType;      // e.g., GPIO_NO_PUPD, GPIO_PULL_UP, GPIO_PULL_DOWN
    u8 AFMode;        // e.g., AF0 to AF15 (Active when mode is Alternate Function)
} GPIO_PinConfig_t;


---

Main APIs Block

/* Clock Control */
void GPIO_ClockControl(GPIO_TypeDef *copy_pPORT, u8 copy_u8ClockState);

/* Initialization Functions */
void GPIO_InitConfig(void); // Static initialization via GPIO_config.h
void GPIO_Init(GPIO_PinConfig_t *copy_pPinConfig, GPIO_TypeDef *copy_pPORT);
void GPIO_DeInit(GPIO_TypeDef *copy_pPORT);

/* Read/Write APIs */
void GPIO_ToggleOutputPin(u8 copy_u8PinNumber, GPIO_TypeDef *copy_pPORT);
u8   GPIO_ReadFromInputPin(GPIO_TypeDef *copy_pPORT, u8 copy_u8PinNumber);
u16  GPIO_ReadFromInputPort(GPIO_TypeDef *copy_pPORT);
void GPIO_WriteToOutputPort(GPIO_TypeDef *copy_pPORT, u16 copy_u16Value);
void GPIO_WriteToOutputPin(GPIO_TypeDef *copy_pPORT, u8 copy_u8PinNumber, u8 copy_u8Value);

---

💻 Code Example (Blinking the On-Board Green LED)

#include "std_types.h"
#include "GPIO_interface.h"

int main(void)
{
    /* 1. Enable Clock for GPIOD */
    GPIO_ClockControl(GPIOD, GPIO_CLK_ENABLE);

    /* 2. Configure Pin D12 as Output */
    GPIO_PinConfig_t LedPin = {
        .PinNumber  = 12,                  // Pin 12
        .PinMode    = GPIO_MODE_OUT,       // Output mode
        .OutputType = GPIO_OP_TYPE_PP,     // Push-Pull
        .SpeedType  = GPIO_SPEED_FAST,     // Fast Speed
        .PullType   = GPIO_NO_PUPD         // No Pull-up / Pull-down
    };
    
    /* Apply configuration to Port D */
    GPIO_Init(&LedPin, GPIOD);

    while(1)
    {
        /* Toggle Green LED */
        GPIO_ToggleOutputPin(12, GPIOD);
        
        /* Delay loop */
        for(volatile u32 i = 0; i < 500000; i++);
    }
}