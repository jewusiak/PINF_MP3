cmake_minimum_required(VERSION 3.20)
project(PINF_MP3 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(PINF_MP3 *.c *.h)
