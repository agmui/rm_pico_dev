project(pico_receive)
add_executable(${PROJECT_NAME} pico_receive.cpp)

# pull in common dependencies
target_link_libraries(${PROJECT_NAME}
        pico_stdlib
        hardware_pio
        )


pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 1)

# create u2f/map/bin/hex file etc.
pico_add_extra_outputs(${PROJECT_NAME})

# add url via pico_set_program_url(not needed)
#example_auto_set_url(${PROJECT_NAME}) some picotool stuff https://forums.raspberrypi.com/viewtopic.php?t=323013#p1933508