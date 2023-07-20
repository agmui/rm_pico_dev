# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/home/agmui/cs/pico/pico-sdk")

set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(rm_pico_dev C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(rm_pico_dev canbus.cpp )

pico_set_program_name(rm_pico_dev "canbus")
pico_set_program_version(rm_pico_dev "0.1")

pico_enable_stdio_uart(rm_pico_dev 0)
pico_enable_stdio_usb(rm_pico_dev 1)

# Add the standard library to the build
target_link_libraries(rm_pico_dev
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(rm_pico_dev PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)

add_library(can2040 can2040.c can2040.h)
target_link_libraries(can2040 pico_stdlib
        pico_base_headers
        hardware_dma
        cmsis_core
)
target_link_libraries(rm_pico_dev 
        can2040
        )

# Add any user requested libraries
target_link_libraries(rm_pico_dev 
        hardware_pio

        pico_base_headers
        hardware_dma
        cmsis_core
        )

pico_add_extra_outputs(rm_pico_dev)

