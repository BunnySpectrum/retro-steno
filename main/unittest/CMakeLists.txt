cmake_minimum_required(VERSION 3.13)

project(rs_unittest C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)


include_directories(../../external/Unity/src)
include_directories(../../lib)
include_directories(tests)
include_directories(utils)
add_executable(${PROJECT_NAME}
    main.c
    ../../external/Unity/src/unity.c
    ../../lib/utils/rs_string.c
    ../../lib/utils/rs_stdio.c
    ../../lib/bsp/exp.c
    ../../lib/bsp/keyboard.c
    ../../lib/app/model_point.c
    utils/log_check.c
    drv_i2c_test.c
    drv_gpio_test.c
    tests/test_gpio.c
    tests/test_ioexp.c
    tests/test_modelpoint.c
    tests/test_mp_keyboard.c
    tests/test_keyboard.c
    tests/test_string.c
)