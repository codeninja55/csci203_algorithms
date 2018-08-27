cmake_minimum_required(VERSION 3.10)
project(${PROJECT_SOURCE_DIR}/ex05/c_version C)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/ex05)
include_directories(${PROJECT_SOURCE_DIR}/ex05/c_version)

set(CMAKE_C_STANDARD 99)
set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/ex05/")

add_executable(ex5 helper.h helper.c ex05/c_version/ex5.c ex05/c_version/ex5.h)