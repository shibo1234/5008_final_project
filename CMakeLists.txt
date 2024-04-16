cmake_minimum_required(VERSION 3.28)
project(final_project C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

set(CMAKE_C_STANDARD 11)

find_package(Curses REQUIRED)

add_executable(final_project
        src/snake.c
        src/snake_game.h
        src/snake_implement.c)

target_link_libraries(final_project PRIVATE ${CURSES_LIBRARIES})
target_include_directories(final_project PRIVATE ${CURSES_INCLUDE_DIRS})