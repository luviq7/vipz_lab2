cmake_minimum_required(VERSION 3.10)
project(Vipz2)

set(CMAKE_BUILD_TYPE Debug) 
set(CMAKE_C_FLAGS "-Wall")


include_directories(src)

set(SOURCE_FILES src/main.c)

add_executable(program ${SOURCE_FILES})

