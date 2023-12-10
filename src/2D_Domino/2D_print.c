//
// Created by andreixmanu on 08/12/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/2D_gamemode.h"

void print_player_2D(Piece* player, int n) {
    for (int i = 0; i < n; i++) {
        if(player[i].left_side == -1 && player[i].right_side == -1) continue;
        printf("\t%d: [%d|%d]\n", i+1, player[i].left_side, player[i].right_side);
    }
    printf("\n");
}

void print_table_2D(Piece** table, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        printf("\t");
        for (int j = 0; j < cols; j++) {
            if(table[i][j].left_side == -1 && table[i][j].right_side == -1) {
                printf("     ");
                continue;
            }
            printf("[%d|%d]", table[i][j].left_side, table[i][j].right_side);
        }
        printf("\n");
    }
    printf("\n");
}