cmake_minimum_required(VERSION 2.8)
project(tetris)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON) #...without compiler extensions like gnu++11
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Threads)
if(Threads)
    message("Threads found!")
endif()

include_directories(figures)
include_directories(core)
include_directories(helpers)

add_subdirectory("${CMAKE_SOURCE_DIR}/../painter" "${CMAKE_BINARY_DIR}/painter")

include_directories(${CURSES_INCLUDE_DIR})

file(GLOB SOURCES figures/*.cpp core/*.cpp helpers/*.cpp)

add_executable(run_test test.cpp ${SOURCES})
add_executable(run run_rl.cpp ${SOURCES})
target_include_directories(run PUBLIC "${CMAKE_SOURCE_DIR}/../painter")
target_include_directories(run_test PUBLIC "${CMAKE_SOURCE_DIR}/../painter")
target_link_libraries(run Painter)
target_link_libraries(run_test Painter)
