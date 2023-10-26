#used this guide: https://decovar.dev/blog/2021/03/08/cmake-cpp-library/
# git: https://github.com/retifrav/cmake-library-example/blob/master/internal-project/libraries/SomeLibrary/CMakeLists.txt

cmake_minimum_required(VERSION 3.13)

project("rm_pico_dev"
    VERSION 0.9.1
    DESCRIPTION "Some library"
)



# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

#==================== building docs====================s
find_package(Doxygen)
if(Doxygen_FOUND)
    add_subdirectory(docs)
else()
    message(STATUS "Doxygen not found, not building docs")
endif()


# here you can see how instead of writing "rm_pico_dev"
# we can just use the PROJECT_NAME variable
add_library(${PROJECT_NAME} STATIC)


# Here go the library target and its sources
target_sources(${PROJECT_NAME}
    PRIVATE
        src/algorithms/crc.cpp
        src/algorithms/crc.hpp
        src/algorithms/extended_kalman.cpp
        src/algorithms/extended_kalman.hpp
        src/algorithms/math_user_utils.cpp
        src/algorithms/math_user_utils.hpp
        src/algorithms/smooth_pid.cpp
        src/algorithms/smooth_pid.hpp
        src/communications/can/can.cpp
        src/communications/can/can.hpp
        src/communications/can/CanBus.cpp
        src/communications/can/CanBus.h
        src/communications/big_constants.h
        src/communications/DJISerial.cpp
        src/communications/DJISerial.h
        src/communications/RefSerial.cpp
        src/communications/RefSerialData.h
        src/communications/Remote.cpp
        src/communications/Uart.cpp
        src/Debug/SDCard/File.cpp
        src/Debug/SDCard/File.h
        src/Debug/SDCard/hw_config.c
        src/Debug/SDCard/LogFile.h
        src/Debug/SDCard/SDCard.cpp
        src/Debug/SDCard/TextFile.cpp
        src/Debug/SDCard/TextFile.h
        src/Debug/SDCard/Yaml.cpp
        src/Debug/SDCard/Yaml.h
        # src/Debug/UI_tests/singleButton.cpp
        # src/Debug/UI_tests/terminalTest.cpp
        # src/Debug/UI_tests/widgetTest.cpp
        src/Debug/CLI.cpp
        src/Debug/CLI.h
        src/Debug/CliFunctions.cpp
        src/Debug/CliFunctions.h
        src/Debug/Debug.cpp
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

#=========================add tests============================ 
# FetchContent added in CMake 3.11, downloads during the configure step
# FetchContent_MakeAvailable was added in CMake 3.14; simpler usage
# include(FetchContent)

# Testing only available if this is the main app
# Note this needs to be done in the main CMakeLists
# since it calls enable_testing, which must be in the
# main CMakeLists.
# include(CTest)

# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well
# TODO:
# if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
#    add_subdirectory(tests)
# endif()

# if(TEST_BUILD)
  add_subdirectory(test)
# endif()


#==================== linking submodules ====================  
target_link_libraries(${PROJECT_NAME}
    pico_stdlib

    # hardware_pio
    # pico_base_headers
    # hardware_dma
    # cmsis_core
)

# Add the standard include files to the build
target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)

# canbus
add_library(can2040 lib/can2040/src/can2040.c lib/can2040/src/can2040.h)
target_link_libraries(can2040

        pico_stdlib
        pico_base_headers
        hardware_pio
        hardware_dma
        cmsis_core
)

target_link_libraries(${PROJECT_NAME} can2040)
target_include_directories(${PROJECT_NAME} PRIVATE lib/can2040/src/)

# add_library(icecream lib/icecream/icecream.hpp)
# set_target_properties(icecream PROPERTIES LINKER_LANGUAGE CXX)
# target_link_libraries(icecream
#     picos_stdlib
#     hardware_mutex
# )
target_include_directories(${PROJECT_NAME} PRIVATE lib/icecream/)

# arduino-compat retroterm
# add_subdirectory(lib/pico-arduino-compat/libs/retroterm)
# target_link_libraries(${PROJECT_NAME} 
#         pico_stdlib
#         pac-retroterm
# )
# target_include_directories(${PROJECT_NAME} INTERFACE lib/pico-arduino-compat/libs/retroterm)

# SD card
add_subdirectory(lib/no-OS-FatFS-SD-SPI-RPi-Pico/FatFs_SPI build)
target_link_libraries(${PROJECT_NAME} FatFs_SPI)
target_include_directories(${PROJECT_NAME} PRIVATE lib/no-OS-FatFS-SD-SPI-RPi-Pico/FatFs_SPI) #TODO: add include dir

#yaml-cpp
#============================== got from: https://github.com/jbeder/yaml-cpp/issues/566#issuecomment-591924960
# set(YAML_CPP_BUILD_TESTS OFF CACHE BOOL "disable yaml tests") # disables tests in yaml-cpp
# set(YAML_CPP_BUILD_TOOLS OFF CACHE BOOL "disable yaml tools")
# set(YAML_CPP_BUILD_CONTRIB OFF CACHE BOOL "disable yaml contrib")
# include(FetchContent)
# FetchContent_Declare(
# 		yaml-cpp
# 		GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
# 		GIT_SHALLOW	ON
# 		GIT_TAG yaml-cpp-0.7.0#6.3
# 	)
# FetchContent_GetProperties(yaml-cpp)
# if(NOT yaml-cpp_POPULATED)
# 	message(STATUS "Populating yaml-cpp...")
# 	FetchContent_Populate(yaml-cpp)
# 	# Add here options for yaml-cpp building
# 	set(YAML_CPP_BUILD_TESTS OFF) #do it again idk
#     set(YAML_CPP_BUILD_TOOLS OFF)
#     set(YAML_CPP_BUILD_CONTRIB OFF)
# 	add_subdirectory(${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR})
# 	message(STATUS "Done.")
# endif()

# include_directories(BEFORE SYSTEM ${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR}/include)
# target_link_libraries(${PROJECT_NAME} yaml-cpp)

#---

set(YAML_CPP_BUILD_TESTS OFF CACHE BOOL "disable yaml tests")
set(YAML_CPP_BUILD_TOOLS OFF CACHE BOOL "disable yaml tools")
set(YAML_CPP_BUILD_CONTRIB OFF CACHE BOOL "disable yaml contrib")
# add_subdirectory(lib/yaml-cpp)
# target_link_libraries(yaml-cpp pico_stdlib )
# target_link_libraries(${PROJECT_NAME} yaml-cpp)

#--

set(YAML_CPP_BUILD_TESTS OFF) #do it again idk
set(YAML_CPP_BUILD_TOOLS OFF)
set(YAML_CPP_BUILD_CONTRIB OFF)
include(FetchContent)
FetchContent_Declare(yaml-cpp URL https://github.com/jbeder/yaml-cpp/archive/refs/tags/yaml-cpp-0.7.0.tar.gz)
FetchContent_MakeAvailable(yaml-cpp)

target_link_libraries(${PROJECT_NAME} yaml-cpp)

#============================== 

#tiny-json
# add_library(tiny_json lib/tiny-json/tiny-json.c)
# target_include_directories(tiny_json lib/tiny-json)
# target_link_libraries(${PROJECT_NAME} tiny_json)

#json-maker
# add_library(json_maker STATIC lib/json-maker/src/json-maker.c)
# target_link_libraries(json_maker pico_stdlib)
# target_link_libraries(${PROJECT_NAME} json_maker)

#json
# FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
# FetchContent_MakeAvailable(json)

# target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)


#====================google test====================  
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)

# add_subdirectory(test)

#================================================== 

# get every header file
file(GLOB_RECURSE HEADER
    "include/*.h"
)
# Seting public header
# without it public headers won't get installed
set(public_headers
    HEADER
)

#==================== adding example====================s
add_subdirectory(examples)