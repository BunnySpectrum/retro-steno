cmake_minimum_required(VERSION 3.13)


include(pico_sdk_import.cmake)
project(app_rp2040_metro C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

pico_sdk_init()



include_directories(../../lib)
include_directories(../../external/stm32-st7735)
add_executable(${PROJECT_NAME}
    main.c
    drv_i2c_rp2040.c
    drv_spi_rp2040.c
    drv_gpio_rp2040.c
    drv_stdio_rp2040.c
    drv_st7735.c
    drv_ssd1306_rp2040.c
    sys_time_rp2040.c
    critical_rp2040.c
    ../../lib/utils/rs_stdio.c
    ../../lib/utils/sys_time.c
    ../../lib/utils/rs_colors.c
    ../../lib/utils/rs_string.c
    ../../lib/bsp/bsp.c
    ../../lib/bsp/scheduler.c
    ../../lib/bsp/led.c
    ../../lib/bsp/exp.c
    ../../lib/bsp/display.c
    ../../lib/bsp/keyboard.c
    ../../lib/app/alert.c
    ../../lib/app/hbt.c
    ../../lib/app/cli.c
    ../../lib/app/cmd.c
    ../../lib/app/screen.c
    ../../lib/app/model_point.c
    ../../lib/app/gfx/gfx_core.c
    ../../lib/app/gfx/fonts/win31_courier_e_10.c
    ../../lib/bsp/devices/displays/disp_adafruit_tft_128x128px_26mm4x26mm5.c
    ../../external/stm32-st7735/st7735.c
    ../../external/stm32-st7735/st7735_reg.c
)

# pull in common dependencies
target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_i2c hardware_spi hardware_pwm)

# create map/bin/hex file etc.
pico_add_extra_outputs(${PROJECT_NAME})

# add url via pico_set_program_url
include(auto_set_url.cmake)
auto_set_url(${PROJECT_NAME})

# Indicate we want to use USB CDC serial for stdin/stdout
#From: PICO_SDK_PATH/src/rp2_common/pico_stdlib/CMakeLists.txt
#   This will set the PICO_TARGET_STDIO_USB property to 
pico_enable_stdio_usb(${PROJECT_NAME} ENABLED) 