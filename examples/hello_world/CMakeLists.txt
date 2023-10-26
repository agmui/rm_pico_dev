add_executable(hello_world hello_world_demo.cpp)

# pull in common dependencies
target_link_libraries(hello_world pico_stdlib)

pico_enable_stdio_uart(${PROJECT_NAME} 0)
pico_enable_stdio_usb(${PROJECT_NAME} 1)
# create u2f/map/bin/hex file etc.
pico_add_extra_outputs(hello_world)

# add url via pico_set_program_url(not needed)
#example_auto_set_url(hello_world) some picotool stuff https://forums.raspberrypi.com/viewtopic.php?t=323013#p1933508