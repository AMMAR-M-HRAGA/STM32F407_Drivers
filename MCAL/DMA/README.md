# ⚡ STM32F407VG MCAL DMA Driver

A highly optimized, bare-metal Microcontroller Abstraction Layer (MCAL) driver for the **Direct Memory Access (DMA)** controller on the **STM32F407VG** (Cortex-M4). This driver provides full control over data transfers between memory and peripherals without CPU intervention, fully supporting high-throughput applications.

---

## 🚀 Features

* **Dual-Controller Architecture:** 
  Full dynamic mapping and tracking support for both `DMA1` and `DMA2` instances.
* **Stream-Based Layout:** 
  Structured handle utilizing a multi-stream array (`Streams[8]`) to easily control all 8 available hardware channels per controller.
* **Advanced Transfer Modes:** 
  Native support for Memory-to-Memory, Memory-to-Peripheral, and Peripheral-to-Memory directions.
* **High-Performance Configurations:** 
  Configurable Data Burst transfers (Single, INCR4, INCR8, INCR16) and active **Double Buffer Mode** management.
* **Complete Interrupt System:** 
  Hardware hook-ups for Transfer Complete, Half Transfer, Transfer Error, and Direct Mode Error notifications.
* **Flexible Data Alignment:** 
  Independent configuration sizing for both peripheral and memory steps (8-bit, 16-bit, and 32-bit width alignments).

---

## 📁 File Structure

The driver organizes memory configurations and control logic inside a modular, decoupled layout:
```text
├── Inc/
│   ├── DMA_interface.h  <-- User-end config structures, channel/burst definitions, and public APIs.
│   ├── DMA_config.h     <-- Pre-build static transfer configurations (Stream, Channel, Size layout).
│   ├── DMA_private.h    <-- Internal driver masks and flag-clearing bit positions.
│   └── DMA_reg.h        <-- Memory mapping including status handlers and dual 8-stream pointer arrays.
└── Src/
    └── DMA_program.c    <-- Multi-stream initialization routines, transfer setup, and interrupt logic.
	

---

## 🔧 Driver Configurations & APIs

typedef struct {
    u8 Channal;            // DMA_CHANNAL0 to DMA_CHANNAL7
    u8 Direction;          // PERIPHERAL_TO_MEMORY, MEMORY_TO_PERIPHERAL, MEMORY_TO_MEMORY
    u8 priority;           // DMA_PRIORITY_LOW, MED, HIGH, V_HIGH
    u8 MSize;              // DMA_M_SIZE_8, DMA_M_SIZE_16, DMA_M_SIZE_32
    u8 PSize;              // DMA_P_SIZE_8, DMA_P_SIZE_16, DMA_P_SIZE_32
    u8 CircularMode;       // CIRCULAR_MODE_DISABLE / ENABLE
    u8 MemInc;             // M_INCREMENT_DISABLE / ENABLE
    u8 PeriphInc;          // P_INCREMENT_DISABLE / ENABLE
    u8 DoubleBufferMode;   // DOUBLE_BFF_DISABLE / ENABLE
    u8 MemBurst;           // DMA_BURST_SINGLE, INCR4, INCR8, INCR16
    u8 periphBurst;        // DMA_BURST_SINGLE, INCR4, INCR8, INCR16
    u8 CompleteINT;        // DMA_T_COMPLETE_INT_DISABLE / ENABLE
    u8 HalfINT;            // DMA_T_HALF_INT_DISABLE / ENABLE
    u8 TransferErorrINT;   // DMA_T_ERROR_INT_DISABLE / ENABLE
    u8 ErorrDirectINT;     // DMA_DIRECT_MODE_DISABLE / ENABLE
} DMA_Config_t;


---

### 📑 Main APIs Block

/* Initialization & Control */
Std_ReturnType DMA_voidInitConfig(void); 
Std_ReturnType DMA_voidInit(DMA_Stream_TypeDef *copy_pStream, const DMA_Config_t *DMA_Config);
void           DMA_voidCmd(DMA_Stream_TypeDef *copy_pStream, u8 copy_u8State);

/* Address Setup & Flag Management */
void voidConfigTransfer(DMA_Stream_TypeDef *copy_pStream, u32 copy_u32PeripheralAddr, u32 copy_u32Memory1Addr, u8 copy_u8DataLength);
void DMA_voidClearFlag(DMA_TypeDef *copy_pDma, u8 copy_u8StreamNumber, u8 copy_u8FlagBit);

/* Double Buffer & Async Callback Registration */
void DMA_voidConfigDoubleBuffer(DMA_Stream_TypeDef *copy_pStream, u32 copy_u32Memory1Addr, u8 copy_u8TargetBuffer);
void DMA_voidSetCallBackFunc(u8 copy_u8StreamNumber, u8 copy_u8StreamIndex, void (*pvNotificationFunc)(void));

/* ISR Handler */
void voidFuncISR_Handler(DMA_TypeDef *copy_dma, u8 copy_u8StreamNumber, u8 copy_u8dmaIndex);


---

## 💻 Code Example (Memory-to-Memory High-Speed Copy)

#include "std_types.h"
#include "DMA_interface.h"

#define BUFFER_SIZE   10

u32 SourceBuffer[BUFFER_SIZE]      = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
u32 DestinationBuffer[BUFFER_SIZE] = {0};

int main(void)
{
    /* 1. Enable Clock for DMA2 via RCC (Handled by your RCC Driver) */
    // RCC_voidEnablePeripheralClock(RCC_AHB1, RCC_AHB1_DMA2);

    /* 2. Initialize DMA according to static configurations in DMA_config.h */
    DMA_voidInitConfig();

    /* 3. Set the target Source, Destination addresses, and block length */
    voidConfigTransfer(DMA2_STREAM0, (u32)SourceBuffer, (u32)DestinationBuffer, BUFFER_SIZE);

    /* 4. Enable the Stream to start the lightning-fast hardware transfer */
    DMA_voidCmd(DMA2_STREAM0, DMA_ENABLE);

    while(1)
    {
        /* CPU is completely free while data is transferring in the background! */
    }
}


---

## 🧠 Key Learnings & Challenges
Stream Matrix Wrapping (DMA_reg.h): Successfully grouped the 8 identical stream channels into a clean nested structure array (Streams[8]), optimizing base pointer operations across both DMA1 and DMA2.

Byte-Offset Interrupt Clearing: Managed the distinct layout of Low and High Interrupt registers (LISR/HISR) safely by designing a unified dynamic index system inside the central ISR handler.