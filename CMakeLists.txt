cmake_minimum_required(VERSION 3.25)
project(domino_lineare C)

set(CMAKE_C_STANDARD 99)

include_directories(.)
include_directories(src)

add_executable(
                ${PROJECT_NAME}
                src/main.c
                src/view_menu.c
                src/print.c
                src/game.c
        include/main.h
)

# Locate the Ncurses library
# find_package(Curses REQUIRED)

# Link your program with the Ncurses library
# target_link_libraries(domino_lineare ${CURSES_LIBRARIES})
