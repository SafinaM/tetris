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
add_subdirectory("${CMAKE_SOURCE_DIR}/../rlutil" "${CMAKE_BINARY_DIR}/rlutil")

set(CMAKE_CXX_FLAGS "-lncurses")
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

file(GLOB SOURCES figures/*.cpp core/*.cpp)
message(${SOURCES})
add_executable(run run.cpp ${SOURCES})
add_executable(test test.cpp ${SOURCES})

# TODO here replace ncurses to rlutil.h - header only lib
target_link_libraries(run ${CURSES_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
