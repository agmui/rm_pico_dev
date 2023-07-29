#used this guide: https://decovar.dev/blog/2021/03/08/cmake-cpp-library/
# git: https://github.com/retifrav/cmake-library-example/blob/master/internal-project/libraries/SomeLibrary/CMakeLists.txt

cmake_minimum_required(VERSION 3.13)

project("rm_pico_dev"
    VERSION 0.9.1
    DESCRIPTION "Some library"
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)


# here you can see how instead of writing "rm_pico_dev"
# we can just use the PROJECT_NAME variable
add_library(${PROJECT_NAME} STATIC)


# Here go the library target and its sources
target_sources(${PROJECT_NAME}
    PRIVATE
        src/algorithms/crc.cpp
        src/algorithms/crc.hpp
        src/communications/big_constants.h
        src/communications/CanBus.cpp
        src/communications/CanBus.h
        src/communications/DJISerial.cpp
        src/communications/DJISerial.h
        src/communications/RefSerial.cpp
        src/communications/RefSerialData.h
        src/communications/Remote.cpp
        src/communications/Uart.cpp
        src/Debug/Debug.cpp
        src/Debug/File.h
        src/Debug/SDCard.cpp
        src/Debug/TextFile.cpp
        src/Debug/TextFile.h
        src/Debug/Yaml.cpp
        src/Debug/Yaml.h
        src/modm/deque_impl.hpp
        src/modm/deque.hpp
        src/drivers.cpp
        src/endianness_wrappers.hpp
        src/clock.h
        src/DjiMotor.cpp
        src/ImuInterface.h
        src/MotorHandler.cpp
        src/MPU6050.cpp
        src/timeout.hpp
)

# Include directories
target_include_directories(${PROJECT_NAME}
    PRIVATE
        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # where external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)


#==================== linking submodules ====================  
target_link_libraries(${PROJECT_NAME}
    pico_stdlib
)


# canbus
add_library(can2040 lib/can2040/src/can2040.c lib/can2040/src/can2040.h)
target_link_libraries(can2040 pico_stdlib
        pico_base_headers
        hardware_dma
        cmsis_core
)
target_include_directories(${PROJECT_NAME} PRIVATE lib/can2040/src/)

# SD card
add_subdirectory(lib/no-OS-FatFS-SD-SPI-RPi-Pico/FatFs_SPI build)
target_link_libraries(${PROJECT_NAME} FatFs_SPI)


# get every header file
file(GLOB_RECURSE HEADER
    "include/*.h"
)
# Seting public header
# without it public headers won't get installed
set(public_headers
    HEADER
)

