# 🛡️ STM32F407VG MCAL NVIC Driver

A bare-metal, low-level Microcontroller Abstraction Layer (MCAL) driver for the **Nested Vectored Interrupt Controller (NVIC)** peripheral on the **STM32F407VG** (ARM Cortex-M4) processor. This driver provides full control over peripheral interrupts, execution prioritization, and nested interrupt management completely from scratch.

---

## 🚀 Features

* **Core Interrupt Control:** Enable or disable non-core peripheral interrupts dynamically at runtime.
* **Precise Offset Mapping:** Perfect hardware register padding (`Reserved` slots) to match the ARM Cortex-M4 memory layout exactly.
* **Flexible Priority Management:** Full access to the Interrupt Priority Registers (`IPR`) using optimized 8-bit byte array mapping for up to 240 external interrupts.
* **Low-Overhead Execution:** Highly optimized dynamic register configuration avoiding manual absolute address calculations.

---

## 📁 File Structure

The driver separates core memory mapping from user logic to maintain a clean layered architecture:
```text
├── Inc/
│   ├── NVIC_interface.h  <-- Public configuration macros, ENABLE/DISABLE state definitions, and APIs.
│   ├── NVIC_config.h     <-- Configuration files for static configurations.
│   ├── NVIC_private.h    <-- Driver internal helper macros.
│   └── NVIC_reg.h        <-- Core NVIC peripheral layout and structured register definitions.
└── Src/
    └── NVIC_program.c    <-- Implementation of interrupt switching and priority configuration logic.
	
---

🔧 Driver Configurations & APIs

/* Enable or Disable a specific IRQ Number */
void NVIC_IRQInterruptConfig(u8 copy_u8ENorDI, u8 copy_u8IRQNumber);

/* Configure the Priority level for a specific IRQ Number */
void NVIC_IRQPriorityConfig(u8 copy_u8IRQNumber, u8 copy_u8IRQPriority);

---

💻 Code Example (Configuring EXTI0 Interrupt)

#include "std_types.h"
#include "NVIC_interface.h"

/* Define EXTI0 IRQ Number for STM32F407 */
#define EXTI0_IRQ_NUMBER    6

int main(void)
{
    /* 1. Set Priority for EXTI0 (e.g., Priority Level 3) */
    NVIC_IRQPriorityConfig(EXTI0_IRQ_NUMBER, 3);

    /* 2. Enable EXTI0 Interrupt line in the NVIC */
    NVIC_IRQInterruptConfig(ENABLE, EXTI0_IRQ_NUMBER);

    while(1)
    {
        // System handles incoming hardware interrupts automatically
    }
}


---

🧠 Key Learnings & Challenges

ARM Layout Emulation (NVIC_reg.h): Successfully aligned the structure to match the core register memory gaps (like the 24-word gap between ISER and ICER) using precise Reserved arrays to guarantee safe pointer arithmetic.

Byte-Addressable Priorities: Mapped the IPR registers as a u8 array rather than u32 to allow direct, atomic byte-access to individual interrupt priority configurations without the need for complex bitwise masking loops.

