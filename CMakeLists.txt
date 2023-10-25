cmake_minimum_required(VERSION 3.25)
project(domino_lineare C)

set(CMAKE_C_STANDARD 99)

add_executable(domino_lineare src/main.c)

# Locate the Ncurses library
find_package(Curses REQUIRED)

# Link your program with the Ncurses library
target_link_libraries(domino_lineare ${CURSES_LIBRARIES})
