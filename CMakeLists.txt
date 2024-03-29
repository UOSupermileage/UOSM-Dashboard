#THIS FILE IS AUTO GENERATED FROM THE TEMPLATE! DO NOT CHANGE!
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.27)

# specify cross-compilers and tools
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER  arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# project settings
project(UOSM-Dashboard C CXX ASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# Hardware floating point
add_compile_definitions(ARM_MATH_CM4;ARM_MATH_MATRIX_CHECK;ARM_MATH_ROUNDING)
add_compile_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
add_link_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)

add_compile_options(-mcpu=cortex-m7 -mthumb -mthumb-interwork)
add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)

# uncomment to mitigate c++17 absolute addresses warnings
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-register")

# Enable assembler files preprocessing
add_compile_options($<$<COMPILE_LANGUAGE:ASM>:-x$<SEMICOLON>assembler-with-cpp>)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(STATUS "Maximum optimization for speed")
    add_compile_options(-Ofast)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    message(STATUS "Maximum optimization for speed, debug info included")
    add_compile_options(-Ofast -g)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    message(STATUS "Maximum optimization for size")
    add_compile_options(-Os)
else ()
    message(STATUS "Minimal optimization, debug info included")
    add_compile_options(-Og -g)
endif ()

include_directories(
    Core/Inc Drivers/STM32F7xx_HAL_Driver/Inc Drivers/STM32F7xx_HAL_Driver/Inc/Legacy Drivers/CMSIS/Device/ST/STM32F7xx/Include Drivers/CMSIS/Include Middlewares/Third_Party/FreeRTOS/Source/include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1
    ${CMAKE_SOURCE_DIR}/Core/Tasks
    ${CMAKE_SOURCE_DIR}/Drivers
    ${CMAKE_SOURCE_DIR}/UOSM-Core/Drivers
    ${CMAKE_SOURCE_DIR}/UOSM-Core/Inc
    ${CMAKE_SOURCE_DIR}/UOSM-Core/Modules
    ${CMAKE_SOURCE_DIR}/UOSM-Core/Utils
    ${CMAKE_SOURCE_DIR}/Drivers/tft
    ${CMAKE_SOURCE_DIR}/Drivers/touchpad
    ${CMAKE_SOURCE_DIR}/Drivers/STM32F769I-Discovery
    ${CMAKE_SOURCE_DIR}/Core/UI
    ${CMAKE_SOURCE_DIR}/Core/UI/Utils
    ${CMAKE_SOURCE_DIR}/Core/UI/Data
    ${CMAKE_SOURCE_DIR}/Core/Modules
)

add_definitions(-DDEBUG -DUSE_HAL_DRIVER -DSTM32F769xx -DSTM -DUOSM_OBSERVABLES)

file(GLOB_RECURSE SOURCES "Core/*.*" "Middlewares/*.*" "Drivers/*.*")

file(GLOB TASK_SOURCES Core/Tasks/*.c)
file(GLOB UOSM_CORE_SOURCES
    UOSM-Core/Drivers/*.c
    UOSM-Core/Modules/*.c
    UOSM-Core/Utils/*.cpp
)

file(GLOB UI_SOURCES Core/UI/*.cpp Core/UI/Utils/*.cpp Core/UI/Data/*.cpp)

file(GLOB MODULE_SOURCES Core/Modules/*.c)

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/LinkerScript.ld)

add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
add_link_options(-mcpu=cortex-m7 -mthumb -mthumb-interwork)
add_link_options(-T ${LINKER_SCRIPT})

add_subdirectory(Drivers/lvgl)

add_executable(${PROJECT_NAME}.elf ${SOURCES} ${TASK_SOURCES} ${UOSM_CORE_SOURCES} ${UI_SOURCES} ${MODULE_SOURCES} ${LINKER_SCRIPT})

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")
