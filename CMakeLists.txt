cmake_minimum_required(VERSION 3.10)
project(lab02/c_version C)

#include_directories( ${MY_SOURCE_DIR}/lab02/c_version )
set(CMAKE_C_STANDARD 99)

add_executable(lab02 lab02/c_version/main.c)