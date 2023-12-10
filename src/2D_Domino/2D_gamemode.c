//
// Created by manua on 04/12/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "../include/2D_gamemode.h"
#include "../include/2D_print.h"

#define MOVE_ALLOWED 1
#define MOVE_NOT_ALLOWED 0
#define LEFT_SIDE 0
#define RIGHT_SIDE 1

Piece EMPTY_PIECE = {-1, -1};

void assign_pieces_2D(Piece* player, int n){
    const int possible_pieces[21][2] = {
            {1, 1},
            {1, 2},
            {1, 3},
            {1, 4},
            {1, 5},
            {1, 6},
            {2, 2},
            {2, 3},
            {2, 4},
            {2, 5},
            {2, 6},
            {3, 3},
            {3, 4},
            {3, 5},
            {3, 6},
            {4, 4},
            {4, 5},
            {4, 6},
            {5, 5},
            {5, 6},
            {6, 6}
    };

    for (int i = 0; i < n; i++) {
        int random_number = rand() % 21;

        player[i].left_side = possible_pieces[random_number][0];
        player[i].right_side = possible_pieces[random_number][1];
    }
}

int first_piece_2D(Piece* row, int cols) {
    for (int i = 0; i < cols; i++) {
        if(!(row[i].left_side == -1 && row[i].right_side == -1)) {
            return i;
        }
    }
    return -1;
}

int last_piece_2d(Piece* row, int cols) {
    for (int i = cols - 1; i >= 0; --i) {
        if(!(row[i].left_side == -1 && row[i].right_side == -1)) {
            return i;
        }
    }
    return -1;
}

Piece* create_player_2D(size_t n){
    Piece* player = malloc(n * sizeof(Piece));
    if (player == NULL) {
        printf("DEBUG: Memory allocation failed.\n");
        exit(1);
    }
    return player;
}

//TODO check for border test cases
int check_move_2D(Piece** table, Piece* piece, int side) {
    if(side == RIGHT_SIDE){
        int last_valid_index = last_piece_2d(table[0], 20);
        if(table[0][last_valid_index].right_side == piece->left_side){
            return MOVE_ALLOWED;
        }
    }
    if(side == LEFT_SIDE){
        int first_valid_index = first_piece_2D(table[0], 20);
        if(table[0][first_valid_index].left_side == piece->right_side){
            return MOVE_ALLOWED;
        }
    }
    return MOVE_NOT_ALLOWED;
}

void use_piece_2D(Piece** table, Piece* player, int piece, int side) {
    // Subtract 1 from piece for 0-based numbering.
    //piece--;

    if (table[0][10].left_side == -1 && table[0][10].right_side == -1) {
        table[0][10] = player[piece];
        player[piece] = EMPTY_PIECE;
        return;
    }

    int first_valid_index = first_piece_2D(table[0], 20);
    int last_valid_index = last_piece_2d(table[0], 20);

    if(side == LEFT_SIDE && first_valid_index != -1) {
        if(check_move_2D(table, &player[piece], LEFT_SIDE)){
            table[0][first_valid_index - 1] = player[piece];
            player[piece] = EMPTY_PIECE;
        }
    }

    if(side == RIGHT_SIDE && last_valid_index != -1) {
        if(check_move_2D(table, &player[piece], RIGHT_SIDE)){
            table[0][last_valid_index + 1] = player[piece];
            player[piece] = EMPTY_PIECE;
        }
    }
}

void singleplayer_2D(Piece** table, int pieces) {
    Piece* player = create_player_2D(pieces);
    assign_pieces_2D(player, pieces);
    printf("Player's pieces:\n");
    print_player_2D(player, pieces);

    while(player[0].left_side != -1 && player[0].right_side != -1){

        printf("Choose a piece to play:\n");
        int piece;
        scanf("%d", &piece);

        // Substract 1 from piece for 0-based numbering
        use_piece_2D(table, player, piece - 1, 0);
        printf("Table:\n");
        print_table_2D(table, 1, 20);
    }

    exit(0);
}

Piece** create_matrix() {
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
        for (size_t j = 0; j < 20; j++) {
            matrix[i][j] = EMPTY_PIECE; // initialize all locations to empty
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
            singleplayer_2D(matrix, pieces);
            break;
        case 2: // CPU mode
            printf("CPU mode\n");
            break;
        default:
            printf("Invalid game mode. Please choose 1 for singleplayer or 2 for CPU mode.\n");
            not_linear_domino();
    }
}