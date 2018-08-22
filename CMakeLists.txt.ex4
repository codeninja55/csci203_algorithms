cmake_minimum_required(VERSION 3.10)
project(${PROJECT_SOURCE_DIR}/lab04/c_version C)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/lab04)
include_directories(${PROJECT_SOURCE_DIR}/lab04/c_version)

set(CMAKE_C_STANDARD 99)
set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/lab04/")

add_executable(ex4 helper.h lab04/c_version/ex4.c)