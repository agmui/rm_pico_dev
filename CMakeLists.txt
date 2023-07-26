#used this guide: https://decovar.dev/blog/2021/03/08/cmake-cpp-library/
# git: https://github.com/retifrav/cmake-library-example/blob/master/internal-project/libraries/SomeLibrary/CMakeLists.txt

cmake_minimum_required(VERSION 3.13)

project("rm_pico_dev"
    VERSION 0.9.1
    DESCRIPTION "Some library"
)

set(CMAKE_C_STANDARD 11)
# set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
    PRIVATE
        src/drivers.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # where external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)


target_link_libraries(${PROJECT_NAME}
    pico_stdlib
)



# without it public headers won't get installed
set(public_headers
    include/drivers.hpp
)

