cmake_minimum_required(VERSION 3.25)
project(domino_lineare C)

set(CMAKE_C_STANDARD 99)

include_directories(.)
include_directories(src)

add_executable(
                ${PROJECT_NAME}
                src/main.c
        src/Linear_Domino/view_menu.c
        src/Linear_Domino/print.c
        src/Linear_Domino/game.c
                include/main.h
                include/autocomplete.h
        src/Linear_Domino/autocomplete.c
        src/2D_Domino/2D_gamemode.c
        src/2D_Domino/2D_autocomplete.c
        src/2D_Domino/2D_print.c
        include/2D_print.h
        src/2D_Domino/challenge.c
        include/challenge.h
)

# Locate the Ncurses library
# find_package(Curses REQUIRED)

# Link your program with the Ncurses library
# target_link_libraries(domino_lineare ${CURSES_LIBRARIES})
