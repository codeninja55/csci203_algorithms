cmake_minimum_required(VERSION 3.10)
project(Exercise07 CXX)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/ex07)
include_directories(${PROJECT_SOURCE_DIR}/ex07/cpp_version)

set(CMAKE_CXX_STANDARD 98)
set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/ex07/")

add_executable(ex7 helper.h helper.c ex07/cpp_version/queue.h ex07/cpp_version/ex7.cpp ex07/cpp_version/ex7.h)