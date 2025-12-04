cmake_minimum_required(VERSION 3.30)
project(c_example C)

set(CMAKE_C_STANDARD 17)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(c_example src/main.c
        modules/banner/banner.c
        include/InputBuffer/InputBuffer.h
        modules/buffer/buffer.c
        modules/prepare/prepareResult.c
        include/prepare/prepare.h
)
