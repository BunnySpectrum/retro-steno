cmake_minimum_required(VERSION 3.13)

project(rs_unittest C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)


include_directories(../../external/Unity/src)
include_directories(../../lib)
add_executable(${PROJECT_NAME}
    ../../external/Unity/src/unity.c
    test_ioexp.c
    ../../lib/bsp/exp.c
    drv_i2c_test.c
)