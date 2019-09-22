cmake_minimum_required(VERSION 2.8)
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
add_executable(run run.cpp figures/LLFigure.cpp figures/LRFigure.cpp figures/Figure.cpp figures/IFigure.cpp Movement.cpp Board.cpp)
add_executable(test test.cpp figures/LLFigure.cpp figures/LRFigure.cpp figures/Figure.cpp figures/IFigure.cpp Movement.cpp Board.cpp)

target_link_libraries(run ${CURSES_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(test ${CURSES_LIBRARIES})
target_link_libraries(curses ${CURSES_LIBRARIES})
