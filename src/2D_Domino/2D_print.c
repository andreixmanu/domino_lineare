//
// Created by andreixmanu on 08/12/23.
//
#include <stdio.h>
#include <stdlib.h>
#include "../include/2D_gamemode.h"
#include "../include/main.h"

void print_player_2D(Piece* player, int n) {
    int j = 1;
    for (int i = 0; i < n; i++) {
        // Skip the pieces that are empty
        if(player[i].left_side == -1 && player[i].right_side == -1){
            continue;
        }
        printf("\t%d: [%d|%d]\n", j, player[i].left_side, player[i].right_side);
        j++;
    }
    printf("\n");
}

void print_player_2D_DEBUG(Piece* player, int n) {
    for (int i = 0; i < n; i++)
        printf("\t%d: [%d|%d]\n", i+1, player[i].left_side, player[i].right_side);
    printf("\n");
}

void print_table_2D_DEBUG(Piece** table) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 20; j++) {
            if (table[i][j].left_side == -1 && table[i][j].right_side == -1) {
                printf("[   ]");
                continue;
            }
            if (table[i][j].left_side == -1) {
                // Print the non -1 side
                printf("[ %d ]", table[i][j].right_side);
                continue;
            } else if (table[i][j].right_side == -1) {
                // Print the non -1 side
                printf("[ %d ]", table[i][j].left_side);
                continue;
            } else {
                printf("[%d|%d]", table[i][j].left_side, table[i][j].right_side);
            }
        }
        printf("\n");
    }
}

void print_table_2D(Piece** table, int rows) {

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 20; j++) {
            if (table[i][j].left_side == -1 && table[i][j].right_side == -1) {
                printf("     ");
                continue;
            }
            if (table[i][j].left_side == -1) {
                // Print the non -1 side
                printf("[ %d ]", table[i][j].right_side);
                continue;
            } else if (table[i][j].right_side == -1) {
                // Print the non -1 side
                printf("[ %d ]", table[i][j].left_side);
                continue;
            } else {
                printf("[%d|%d]", table[i][j].left_side, table[i][j].right_side);
            }
        }
        printf("\n");
    }
}

void print_end_game_2D(Piece** table){
    printf("\n"
           "  ________                           ________                          ._.\n"
           " /  _____/ _____     _____    ____   \\_____  \\  ___  __  ____  _______ | |\n"
           "/   \\  ___ \\__  \\   /     \\ _/ __ \\   /   |   \\ \\  \\/ /_/ __ \\ \\_  __ \\| |\n"
           "\\    \\_\\  \\ / __ \\_|  Y Y  \\\\  ___/  /    |    \\ \\   / \\  ___/  |  | \\/ \\|\n"
           " \\______  /(____  /|__|_|  / \\___  > \\_______  /  \\_/   \\___  > |__|    __\n"
           "        \\/      \\/       \\/      \\/          \\/             \\/          \\/\n");

    printf("\n"
           "______ _             _   _____                    \n"
           "|  ___(_)           | | /  ___|                   \n"
           "| |_   _ _ __   __ _| | \\ `--.  ___ ___  _ __ ___ \n"
           "|  _| | | '_ \\ / _` | |  `--. \\/ __/ _ \\| '__/ _ \\\n"
           "| |   | | | | | (_| | | /\\__/ / (_| (_) | | |  __/\n"
           "\\_|   |_|_| |_|\\__,_|_| \\____/ \\___\\___/|_|  \\___|\n"
           "                                                  \n"
           "                                                  \n");

    printf("%d\n", calculate_score_2D(table));

    printf("Do you want to play again? (y/n)\n");
    char answer;
    scanf(" %c", &answer);

    if (answer == 'y') main();
    else exit(0);
}