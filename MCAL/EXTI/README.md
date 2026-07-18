# ⚡ STM32F407VG MCAL EXTI Driver

A bare-metal Microcontroller Abstraction Layer (MCAL) driver for the **External Interrupt/Event Controller (EXTI)** and **System Configuration Controller (SYSCFG)** on the **STM32F407VG** (Cortex-M4). This driver allows managing hardware interrupts from external pins with customizable triggers and callback routing.

---

## 🚀 Features

* **SYSCFG Routing Integration:** 
  Built-in support for the `SYSCFG` memory map to seamlessly route any GPIO port (PA to PE) to its designated EXTI line.
* **Flexible Trigger Control:** 
  Configurable interrupt edge detection supporting Rising Edge, Falling Edge, or Both.
* **Callback Function Support:** 
  Integrated function pointer within the configuration structure to implement clean, asynchronous ISR handlers.
* **Comprehensive ISR Architecture:** 
  Complete implementation mapping for standard lines (`EXTI0`–`EXTI4`) and shared interrupt blocks (`EXTI9_5`, `EXTI15_10`).

---

## 📁 File Structure

The driver neatly encapsulates peripheral synchronization and system configuration registers:
```text
├── Inc/
│   ├── EXTI_interface.h  <-- Driver configuration struct, user APIs, and IRQ handlers.
│   ├── EXTI_config.h     <-- Pre-build static macro configurations for lines and edges.
│   ├── EXTI_private.h    <-- Internal driver configurations and private flags.
│   └── EXTI_reg.h        <-- Memory mapping for both EXTI and SYSCFG peripheral registers.
└── Src/
    └── EXTI_program.c    <-- Multi-channel routing logic and interrupt service implementations.
	
---

## 🔧 Driver Configurations & APIs

typedef struct {
    u8 EXTI_u8Line;                   // e.g., EXTI_LINE0, EXTI_LINE1
    u8 EXTI_u8PORT;                   // e.g., pAX, pBX (GPIO Port selection)
    u8 EXTI_u8Edge;                   // e.g., EXTI_RISING_EDGE, EXTI_FALLING_EDGE
    u8 EXTI_u8mode;                   // Interrupt Enable / Disable
    void (*EXTI_CallbackFunc)(void);  // Pointer to the function to execute on interrupt
} EXTI_Config_t;


---

### 📑 Main APIs Block

/* Initialization Routines */
void EXTI_voidInitConfig(void); 
void EXTI_voidInit(EXTI_Config_t *EXTI_Config);

/* Callback System Register */
void EXTI_voidCallbackFunc(u8 copy_u8Line, void (*EXTI_pCallback)(void));

/* ISR Hardware Handlers */
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);


---

## 💻 Code Example (Push Button Edge Trigger)

#include "std_types.h"
#include "EXTI_interface.h"

/* Simple callback function to link with the ISR */
void App_voidButtonCallback(void)
{
    // Write your logic here (e.g., Toggle an LED pin)
}

int main(void)
{
    /* 1. Set up the External Interrupt parameters */
    EXTI_Config_t UserButton = {
        .EXTI_u8Line       = 0,                        // Line 0 corresponds to Pin 0
        .EXTI_u8PORT       = 0,                        // Port A
        .EXTI_u8Edge       = EXTI_RISING_EDGE,         // Trigger on press
        .EXTI_u8mode       = EXTI_INT_ENABLE,          // Turn interrupt on
        .EXTI_CallbackFunc = App_voidButtonCallback    // Assign handler function
    };

    /* 2. Push configurations to the hardware registers */
    EXTI_voidInit(&UserButton);

    while(1)
    {
        // System sleeps or runs lower priority tasks safely
    }
}

🧠 Key Learnings & Challenges

SYSCFG Register Dependencies: Overcame the hardware constraint where EXTI lines cannot distinguish ports natively by linking the SYSCFG_EXTICR registers directly inside the initialization sequence.

Vector Table Shared Lines: Structured the callback functions efficiently to decouple shared lines like EXTI15_10 inside software loops, resolving which specific pin triggered the pending register (PR).