cmake_minimum_required(VERSION 3.10)
project(${PROJECT_SOURCE_DIR}/assignment02/c_version CXX)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/assignment02)
include_directories(${PROJECT_SOURCE_DIR}/assignment02/c_version)

#target_link_libraries()

set(CMAKE_CXX_STANDARD 11)
set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/assignment02/")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
set(SOURCE_FILES assignment02/cpp_version/ass2.cpp assignment02/cpp_version/EventQueue.cpp assignment02/cpp_version/EventQueue.h assignment02/cpp_version/Servers.cpp assignment02/cpp_version/Servers.h assignment02/cpp_version/ServerQueue.cpp assignment02/cpp_version/ServerQueue.h)

add_executable(ass2 ${SOURCE_FILES})
