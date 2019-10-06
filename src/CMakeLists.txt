cmake_minimum_required(VERSION 2.8)
project(curses)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON) #...without compiler extensions like gnu++11
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Threads)
if(Threads)
    message("Threads found!")
endif()

include_directories("${CMAKE_SOURCE_DIR}/../rlutil")
include_directories(figures)
include_directories(core)
include_directories(helpers)
include_directories(painter)
add_subdirectory("${CMAKE_SOURCE_DIR}/../rlutil" "${CMAKE_BINARY_DIR}/rlutil")

include_directories(${CURSES_INCLUDE_DIR})

file(GLOB SOURCES figures/*.cpp core/*.cpp painter/*.cpp helpers/*.cpp)
message(${SOURCES})
add_executable(test test.cpp ${SOURCES})
add_executable(rlutil_run run_rl.cpp ${SOURCES})