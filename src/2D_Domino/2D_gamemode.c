//
// Created by manua on 04/12/2023.
//

#include "include/main.h"
#include <stdio.h>
#include <stdlib.h>
#include "../include/2D_gamemode.h"

void singleplayer_2D() {

}

Piece** create_matrix(){
    Piece** matrix = malloc(20 * sizeof(Piece*));
    if (matrix == NULL) {
        // Handle memory allocation failure
        exit(1);
    }

    for (size_t i = 0; i < 20; i++) {
        matrix[i] = malloc(20 * sizeof(Piece));
        if (matrix[i] == NULL) {
            exit(1);
        }
    }
    return matrix;
}

void not_linear_domino() {
    Piece** matrix = create_matrix();
    printf("Welcome to (not) Linear Domino!\n");
    printf("How many pieces do you want to play with?:\n");
    int pieces;
    scanf("%d", &pieces);

    printf("Choose the game mode:\n");
    printf("1. Singleplayer\n");
    printf("2. CPU mode\n");

    int gameMode;
    scanf("%d", &gameMode);
    switch (gameMode) {
        case 1: // Singleplayer
            printf("Singleplayer\n");
            break;
        case 2: // CPU mode
            printf("CPU mode\n");
            break;
        default:
            printf("Invalid game mode. Please choose 1 for singleplayer or 2 for CPU mode.\n");
            not_linear_domino();
    }
}