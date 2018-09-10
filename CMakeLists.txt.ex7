cmake_minimum_required(VERSION 3.10)
project(${PROJECT_SOURCE_DIR}/ex06/c_version C)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/ex06)
include_directories(${PROJECT_SOURCE_DIR}/ex06/c_version)

set(CMAKE_C_STANDARD 99)
set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/ex06/")

add_executable(ex6 helper.h helper.c ex06/c_version/ex6.c ex06/c_version/ex6.h)