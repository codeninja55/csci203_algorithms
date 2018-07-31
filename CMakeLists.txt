cmake_minimum_required(VERSION 3.10)
project(lab02/c_version C)

include_directories(BEFORE ${PROJECT_SOURCE_DIR})
include_directories(AFTER ${PROJECT_SOURCE_DIR}/lab02/c_version)

set(CMAKE_C_STANDARD 99)

add_executable(ex2 lab02/c_version/ex2.c)