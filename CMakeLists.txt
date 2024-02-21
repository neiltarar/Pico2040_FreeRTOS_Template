cmake_minimum_required(VERSION 3.15)

if(UNIX)
    message("You're running CMake in Linux")
endif()

# Set project data
set(PROJECT_NAME "RP2040_FREERTOS_PROJECT")
set(BUILD_NUMBER "1")

# Set app name(s) and version(s)
set(APP_1_NAME "APP")
set(APP_1_VERSION_NUMBER "1.0.0")
set(APP_1_SRC_DIRECTORY "${CMAKE_SOURCE_DIR}/App")

# Set env variable 'PICO_SDK_PATH' to the local Pico SDK
# Comment out the set() if you have a global copy of the
# SDK set and $PICO_SDK_PATH defined in your $PATH
set(ENV{PICO_SDK_PATH} "${CMAKE_SOURCE_DIR}/lib/pico-sdk")

# Set flags and directory variables
set(FREERTOS_CFG_DIRECTORY "${CMAKE_SOURCE_DIR}/Config")
set(FREERTOS_SRC_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/FreeRTOS-Kernel")

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

# Add FreeRTOS as a library
add_library(FreeRTOS STATIC
    ${FREERTOS_SRC_DIRECTORY}/event_groups.c
    ${FREERTOS_SRC_DIRECTORY}/list.c
    ${FREERTOS_SRC_DIRECTORY}/queue.c
    ${FREERTOS_SRC_DIRECTORY}/stream_buffer.c
    ${FREERTOS_SRC_DIRECTORY}/tasks.c
    ${FREERTOS_SRC_DIRECTORY}/timers.c
    ${FREERTOS_SRC_DIRECTORY}/portable/MemMang/heap_3.c
    ${FREERTOS_SRC_DIRECTORY}/portable/GCC/ARM_CM0/port.c
)

# Build FreeRTOS
target_include_directories(FreeRTOS PUBLIC
    ${FREERTOS_CFG_DIRECTORY}/
    ${FREERTOS_SRC_DIRECTORY}/include
    ${FREERTOS_SRC_DIRECTORY}/portable/GCC/ARM_CM0
)

project(${PROJECT_NAME} 
    LANGUAGES C CXX ASM
    DESCRIPTION "FreeRTOS-based RP2040 applications"
    )

# Set the version of the languages that we want to use
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise the Pico SDK - creates a pico-sdk subdirectory in our projecct for the libraries
pico_sdk_init()

# Include the apps' source code
add_subdirectory(${APP_1_SRC_DIRECTORY})