cmake_minimum_required(VERSION 3.10)
project(Exercise08 CXX)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/ex08)
include_directories(${PROJECT_SOURCE_DIR}/ex08/cpp_version)

set(CMAKE_CXX_STANDARD 11)
set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/ex08/")

add_executable(ex8 helper.h helper.c ex08/cpp_version/ex08.cpp ex08/cpp_version/HashMap.cpp)