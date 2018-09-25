cmake_minimum_required(VERSION 3.10)
project(Exercise07 C)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/ex07)
include_directories(${PROJECT_SOURCE_DIR}/ex07/c_version)

set(CMAKE_C_STANDARD 99)
set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/ex07/")

add_executable(ex7 helper.h helper.c ex07/c_version/ex7.c)