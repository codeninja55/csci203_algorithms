cmake_minimum_required(VERSION 3.10)
project(Assignment03 CXX)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/assignment03)
include_directories(${PROJECT_SOURCE_DIR}/assignment03/cpp_version)

set(CMAKE_CXX_STANDARD 98)
set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/assignment03/")

set(
    SOURCE_FILES
        assignment03/cpp_version/ass3.cpp
        assignment03/cpp_version/HashMap.h
        assignment03/cpp_version/MinHeap.h)

add_executable(ass3 ${SOURCE_FILES})