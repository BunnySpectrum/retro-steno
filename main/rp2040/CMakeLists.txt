cmake_minimum_required(VERSION 3.13)


include(pico_sdk_import.cmake)
project(app_rp2040_metro C CXX ASM)

set(CMAKE_C_STANDARD 11)

set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()



include_directories(../../lib)
add_executable(${PROJECT_NAME}
    main.c
    ../../lib/IOExpander/IOExpPCF8574AN/IOExpPCF8574AN.c
    ../../lib/I2C/
)

# pull in common dependencies
target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_i2c)

# create map/bin/hex file etc.
pico_add_extra_outputs(${PROJECT_NAME})

# add url via pico_set_program_url
include(auto_set_url.cmake)
auto_set_url(${PROJECT_NAME})

# Indicate we want to use USB CDC serial for stdin/stdout
#From: PICO_SDK_PATH/src/rp2_common/pico_stdlib/CMakeLists.txt
#   This will set the PICO_TARGET_STDIO_USB property to 
pico_enable_stdio_usb(${PROJECT_NAME} ENABLED) 