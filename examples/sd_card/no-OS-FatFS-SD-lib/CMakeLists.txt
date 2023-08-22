project(no-OS-FatFS-SD-lib)
add_executable(${PROJECT_NAME} hw_config.c main.cpp)

# pull in common dependencies
target_link_libraries(${PROJECT_NAME}
        pico_stdlib
        rm_pico_dev
        )

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

# create u2f/map/bin/hex file etc.
pico_add_extra_outputs(${PROJECT_NAME})

# add url via pico_set_program_url(not needed)
#example_auto_set_url(${PROJECT_NAME}) some picotool stuff https://forums.raspberrypi.com/viewtopic.php?t=323013#p1933508