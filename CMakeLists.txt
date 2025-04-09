cmake_minimum_required(VERSION 3.10)
project(Vipz2 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-Wall")

include_directories(src)

set(SOURCE_FILES src/main.cpp src/func.cpp)

add_executable(program ${SOURCE_FILES})