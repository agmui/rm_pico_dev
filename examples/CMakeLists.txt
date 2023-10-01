# # Generated Cmake Pico project file

# cmake_minimum_required(VERSION 3.13)

# set(CMAKE_C_STANDARD 11)
# set(CMAKE_CXX_STANDARD 17)

# # Initialise pico_sdk from installed location
# # (note this can come from environment, CMake cache etc)
# set(PICO_SDK_PATH "rm_pico_dev/pico-sdk")

# set(PICO_BOARD pico CACHE STRING "Board type")

# # Pull in Raspberry Pi Pico SDK (must be before project)
# include(./rm_pico_dev/lib/pico-sdk/pico_sdk_init.cmake)

# if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
#   message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
# endif()

# project(pico_app C CXX ASM)

# set(PICO_CXX_ENABLE_EXCEPTIONS 1)

# set(PICO_CXX_ENABLE_RTTI 1)

# # Initialise the Raspberry Pi Pico SDK
# pico_sdk_init()

# # Add executable. Default name is the project name, version 0.1

# add_executable(${PROJECT_NAME} main.cpp )

# pico_set_program_name(${PROJECT_NAME} "pico_app")
# pico_set_program_version(${PROJECT_NAME} "0.1")

# pico_enable_stdio_uart(${PROJECT_NAME} 1)
# pico_enable_stdio_usb(${PROJECT_NAME} 1)

# add_subdirectory(rm_pico_dev)

# # Add the standard library to the build
# target_link_libraries(${PROJECT_NAME}
#         pico_stdlib)

# # Add the standard include files to the build
# target_include_directories(${PROJECT_NAME} PRIVATE
#   ${CMAKE_CURRENT_LIST_DIR}
#   ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
# )

# # Add any user requested libraries
# # target_link_libraries(${PROJECT_NAME} 

# #         )

# pico_add_extra_outputs(${PROJECT_NAME})

add_subdirectory(cli)
add_subdirectory(hello_world)
add_subdirectory(motor)
# add_subdirectory(pico_2_pico_demo)
add_subdirectory(remote)
add_subdirectory(sd_card)