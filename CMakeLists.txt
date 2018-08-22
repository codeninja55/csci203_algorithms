cmake_minimum_required(VERSION 3.10)
project(${PROJECT_SOURCE_DIR}/assignment01/c_version C)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/assignment01)
include_directories(${PROJECT_SOURCE_DIR}/assignment01/c_version)

#target_link_libraries()

set(CMAKE_C_STANDARD 99)
set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/assignment01/")
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS})
set(SOURCE_FILES assignment01/c_version/ass1.c)

add_executable(ass1 ${SOURCE_FILES})
