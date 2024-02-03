cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(test_project C CXX ASM)
set(CMAKE_C_STANDARD 11)

set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()


add_executable(test
    ./src/main.c
)

# pull in common dependencies
target_link_libraries(test pico_stdlib hardware_i2c)

# create map/bin/hex file etc.
pico_add_extra_outputs(test)

# add url via pico_set_program_url
include(auto_set_url.cmake)
auto_set_url(test)

pico_enable_stdio_usb(test ENABLED)
