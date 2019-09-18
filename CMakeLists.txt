cmake_minimum_required(VERSION 3.6)
project(curses)

set(CMAKE_CXX_STANDARD 11)

find_package(Threads)
if(Threads)
    message("Threads found!")
endif()

set(CMAKE_CXX_FLAGS "-lncurses")
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(curses main.cpp)
add_executable(run run.cpp Figure.h LLFigure.cpp LRFigure.cpp Figure.cpp IFigure.cpp)
target_link_libraries(run ${CURSES_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(curses ${CURSES_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
