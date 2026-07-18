# 🛡️ STM32F407VG MCAL MPU Driver

A bare-metal Microcontroller Abstraction Layer (MCAL) driver for the **Memory Protection Unit (MPU)** embedded within the ARM Cortex-M4 core of the **STM32F407VG**. This driver provides robust memory isolation, task separation, and hardware-level fault detection, which are essential for automotive safety and cybersecurity applications.

---

## 🚀 Features

* **Hardware Hardware-Level Protection:** 
  Supports full management of up to 8 independent memory regions with configurable execution permissions.
* **Alias Register Mapping:** 
  Utilizes standard and system alternate registers (`RBAR_A1`–`RBAR_A3`) within the hardware structure for fast context switching.
* **Sub-Region & Size Control:** 
  Dynamic region size scaling ranging from 32 Bytes up to 4 Gigabytes, alongside background region policies.
* **Access Permission Management:** 
  Granular Access Permission (`AP`) mapping to enforce Privileged/User read-write structures or Read-Only restrictions.
* **Execute-Never (XN) Support:** 
  Built-in toggles for Instruction Fetch blocking (`XN_ENABLE`) to prevent unauthorized code execution inside RAM buffers.
* **Dedicated Fault Handling:** 
  Native control APIs to enable the System Control Block's Memory Management Fault Handler (`MemManageFault`).

---

## 📁 File Structure

The driver enforces a strict decoupling between low-level core configurations and configuration structures:
```text
├── Inc/
│   ├── MPU_interface.h  <-- Configuration structures, permission macros, and public MPU control APIs.
│   ├── MPU_config.h     <-- Static compile-time region layouts (Base addresses, sizes, and behaviors).
│   ├── MPU_private.h    <-- Internal core definitions and private mask adjustments.
│   └── MPU_reg.h        <-- Memory mapped core system protection structures and SCB fault registers.



---

## 🔧 Driver Configurations & APIs

typedef struct {
    u8  RegionState;       // MPU_REGION_ENABLE / MPU_REGION_DISABLE
    u8  RegionNumber;      // MPU_REGION0 to MPU_REGION7
    u8  RegionSize;        // MPU_SIZE_32B, MPU_SIZE_1KB, MPU_SIZE_1MB, etc.
    u8  RegionPermission;  // Privileged/User Access controls (e.g., MPU_AP_PRV_RW_USR_RW)
    u8  RegionXNSelect;    // MPU_XN_ENABLE (Execute-Never) / MPU_XN_DISABLE
    u32 RegionAddress;     // Hardware boundary base address alignment
    u8  RegionMemType;     // NORMAL_WB_NWA, DEVICE, STRONGLY_ORDERED
} MPU_RegionConfig_t;


---

### 📑 Main APIs Block

/* Global MPU Controller Actions */
void MPU_voidInit(void);
void MPU_voidEnable(void);
void MPU_voidDisable(void);

/* Runtime Configuration Control */
void MPU_voidConfigRegion(MPU_RegionConfig_t *MPU_RegionConfig);

/* System Fault Handler Hook-ups */
void MemManageFault_voidEnable(void);
void MemManageFault_voidDisable(void);


---

## 💻 Code Example (Enforcing Flash Read-Only & Executable RAM Protection)

#include "std_types.h"
#include "MPU_interface.h"

int main(void)
{
    /* 1. Initialize MPU using the static structures compiled from MPU_config.h */
    MPU_voidInit();

    /* 2. Enable the central Memory Management Fault to catch any illegal operations */
    MemManageFault_voidEnable();

    /* 3. Example: Creating a dynamic isolated runtime buffer */
    MPU_RegionConfig_t SecureBuffer = {
        .RegionState      = 1,                           // Enable region
        .RegionNumber     = MPU_REGION3,                 // Assign to target slot
        .RegionSize       = MPU_SIZE_64KB,               // Allocate size scale
        .RegionPermission = MPU_AP_PRV_RW_USR_NO,        // User tasks cannot access this memory
        .RegionXNSelect   = MPU_XN_ENABLE,               // Block execution from inside this buffer (No Exploits)
        .RegionAddress    = 0x10000000,                  // Base CCM-RAM start address
        .RegionMemType    = MPU_TYPE_NORMAL_WB_NWA       // Cache policy setting
    };

    /* Apply the updated layout to the system matrix */
    MPU_voidConfigRegion(&SecureBuffer);

    /* 4. Power up the protection unit hardware */
    MPU_voidEnable();

    while(1)
    {
        /* System runs safely. Any illegal memory access halts the CPU instantly into MemManage */
    }
}


---

## 🧠 Key Learnings & Challenges
Core Peripheral Alignment (MPU_reg.h): Mapped the system registers inside the Private Peripheral Bus (PPB) address space (0xE000ED90), ensuring explicit core cache bypassing by using volatile attributes correctly.

MemManage Fault Trapping: Linked the SCB_SHCSR register manipulation directly inside the initialization layer, providing deterministic system resets instead of dropping directly into a blind HardFault loop on illegal pointer operations.