# 1. تحديد أقل إصدار مطلوب من CMake
cmake_minimum_required(VERSION 3.20)

# 2. إعلام CMake بأننا ندمج لبيئة Embedded (Bare-Metal) بدون نظام تشغيل
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# 3. تحديد أداة التجميع (Toolchain) المخصصة لمعالجات ARM
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_SIZE arm-none-eabi-size)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# 4. اسم المشروع واللغات المستخدمة (C و Assembly)
project(STM32F407_Drivers C ASM)

# 5. خيارات المترجم (Compiler Flags) الخاصة بـ ARM Cortex-M4
add_compile_options(
    -mcpu=cortex-m4
    -mthumb
    -mfloat-abi=hard
    -mfpu=fpv4-sp-d16
    -O0                 # إلغاء الـ Optimization لسهولة الـ Debugging
    -g3                 # إخراج جميع رموز الـ Debugging لـ GDB
    -w              # إظهار كل التحذيرات (Warnings)
)


# 1. مسارات ملفات الـ Headers
include_directories(
    LIB
    MCAL/GPIO/Inc
    MCAL/CAN/Inc
    MCAL/DMA/Inc
    MCAL/EXTI/Inc
    MCAL/MPU/Inc
    MCAL/NVIC/Inc
    MCAL/USART/Inc
    MCAL/SYSTICK/Inc
)

# 2. جمع كل ملفات السورس (.c و .s)
file(GLOB_RECURSE SOURCES 
    "MCAL/*.c"
    "LIB/*.c"
    "Examples/*.c"
    "Startup/*.s"
)


# 8. تحديد اسم الملف الناتج بصيغة ELF
add_executable(${PROJECT_NAME}.elf ${SOURCES})

# 9. تحديد مسار ملف الـ Linker Script
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F407VGTx_FLASH.ld)

# 10. خيارات الـ Linker لربط الذاكرة وتخفيف حجم الكود
# خيارات الـ Linker
target_link_options(${PROJECT_NAME}.elf PRIVATE
    -mcpu=cortex-m4
    -mthumb
    -mfloat-abi=hard
    -mfpu=fpv4-sp-d16
    -T${LINKER_SCRIPT}
    -Wl,-Map=${PROJECT_NAME}.map
    --specs=nano.specs
    --specs=nosys.specs
)
# 11. أوامر تنفذ بعد التجميع: طباعة الحجم واستخراج ملفات .hex و .bin
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_SIZE} ${PROJECT_NAME}.elf
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
)


add_custom_target(flash
    COMMAND openocd -f interface/stlink.cfg -c "adapter speed 1000" -f target/stm32f4x.cfg -c "reset_config srst_only srst_nogate connect_assert_srst" -c "program ${PROJECT_NAME}.elf verify reset exit"
    DEPENDS ${PROJECT_NAME}.elf
    COMMENT "Flashing ${PROJECT_NAME}.elf to STM32F407 target..."
)