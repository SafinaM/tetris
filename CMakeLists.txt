cmake_minimum_required(VERSION 3.14)
project(curses)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-lncurses")
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(curses main.cpp)
add_executable(run run.cpp Figure.cpp)
target_link_libraries(run ${CURSES_LIBRARIES})
target_link_libraries(curses ${CURSES_LIBRARIES})
