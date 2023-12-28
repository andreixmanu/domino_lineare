#include <stdio.h>
#include "../include/2D_gamemode.h"
#include "../include/2D_autocomplete.h"
#include "../include/2D_print.h"
#include <stdlib.h>

#define LEFT_SIDE 1
#define RIGHT_SIDE 2
#define HORIZONTAL 1
#define VERTICAL 2
#define MOVE_ALLOWED 1
#define MOVE_NOT_ALLOWED 0
#define PIECE_PLACED 1
#define PIECE_NOT_PLACED 0

int rows_ = 1;

typedef struct best_move {
    int piece;
    int side;
    int orientation;
} Best_move;

void auto_switch_values_2D(Piece* player, int player_size, int n) {

    int index = pick_piece_index(player, player_size, n - 1);  // -1 if option is 1-based
    if (index == -1) {
        printf("DEBUG: Auto switch values: index = -1\n");
        return;
    }
    int temp = player[index].left_side;
    player[index].left_side = player[index].right_side;
    player[index].right_side = temp;
}
int remove_piece_autocomplete(Piece *player, int *size, int index) {
    if (index < 0 || index >= *size){
        return 0;
    }
    for (int i = index; i < *size - 1; i++) player[i] = player[i + 1];
    (*size)--;
    return 1;
}

void undo_move(Piece** table, int side, int orientation) {
    int first_valid_index = first_piece_2D(table[0], 20);
    int last_valid_index = last_piece_2d(table[0], 20);

    if (orientation == HORIZONTAL) {
        if (side == LEFT_SIDE && first_valid_index != -1) {
            table[0][first_valid_index].left_side = -1;
            table[0][first_valid_index].right_side = -1;
        }
        if (side == RIGHT_SIDE && last_valid_index != -1) {
            table[0][last_valid_index].left_side = -1;
            table[0][last_valid_index].right_side = -1;
        }
    }

    if (orientation == VERTICAL) {
        if (side == LEFT_SIDE && first_valid_index != -1) {
            table[0][first_valid_index].left_side = -1;
            table[0][first_valid_index].right_side = -1;
            table[1][first_valid_index].left_side = -1;
            table[1][first_valid_index].right_side = -1;
        }
        if (side == RIGHT_SIDE && last_valid_index != -1) {
            table[0][last_valid_index].left_side = -1;
            table[0][last_valid_index].right_side = -1;
            table[1][last_valid_index].left_side = -1;
            table[1][last_valid_index].right_side = -1;
        }
    }
}

int use_piece_autocomplete(Piece **table, Piece piece, int side) {

        //get the pieces indexes
        int first_valid_index = first_piece_2D(table[0], 20);
        int last_valid_index = last_piece_2d(table[0], 20);

        if (side == LEFT_SIDE && first_valid_index != -1) {

            Piece *table_piece = &table[0][first_valid_index];

            if (check_move_2D(table_piece, &piece, LEFT_SIDE)) {
                table[0][first_valid_index - 1] = piece;
                return PIECE_PLACED;
            }
        }

        if (side == RIGHT_SIDE && last_valid_index != -1) {

            Piece *table_piece = &table[0][last_valid_index];

            if (check_move_2D(table_piece, &piece, RIGHT_SIDE)) {
                table[0][last_valid_index + 1] = piece;
                return PIECE_PLACED;
            }
        }
        return PIECE_NOT_PLACED;
}

Best_move find_best_move(Piece* player, int player_size, Piece** table) {
    Best_move best_move = { -1, -1, -1 };
    int best_score = -1;

    for (int i = 1; i <= player_size; i++) {
        for (int side = LEFT_SIDE; side <= RIGHT_SIDE; side++) {
            for (int orientation = HORIZONTAL; orientation <= VERTICAL; orientation++) {
                use_piece_2D(table, player, i, side, &player_size, orientation, 0);

                int score = calculate_score_2D(table);

                undo_move(table, side, orientation);

                if (score > best_score) {
                    best_score = score;
                    best_move.piece = i;
                    best_move.side = side;
                    best_move.orientation = orientation;
                }
            }
        }
    }

    return best_move;
}

void ai_first_fit(Piece** table, Piece* player, int *player_size) {
    for (int i = 1; i <= *player_size; i++) {
        // Scelta casuale tra LEFT_SIDE e RIGHT_SIDE
        int side = (rand() % 2) + 1;
        int index = 0;
        // Cerca la prima posizione libera nella prima riga del tavolo
        if(side == LEFT_SIDE) index = first_piece_2D(table[0], 20);
        else if(side == RIGHT_SIDE) index = last_piece_2d(table[0], 20);

        if (index != -1) {
            if(use_piece_autocomplete(table, player[i+1], side) == PIECE_PLACED){
                //remove the piece from the player
                if(!remove_piece_autocomplete(player, player_size, i)){
                    printf("DEBUG: remove_piece_2D failed\n");
                    exit(1);
                }
                //printf("Placed piece %d on the table\n", i+1);
                continue;
            }
        }
    }

    for(int i = 0; i < *player_size; i++){

        //switch the first piece, and check if it fits either on the left or on the right side
        auto_switch_values_2D(player, *player_size, i+1);

        int left_index = first_piece_2D(table[0], 20);
        if(left_index != -1){
            if(use_piece_autocomplete(table, player[i+1], LEFT_SIDE) == PIECE_PLACED){
                //remove the piece from the player
                if(!remove_piece_autocomplete(player, player_size, i)){
                    printf("DEBUG: remove_piece_2D failed\n");
                    exit(1);
                }
                //printf("Placed piece %d on the table\n", i+1);
                continue;
            }
        }

        int right_index = last_piece_2d(table[0], 20);
        if(right_index != -1){
            if(use_piece_autocomplete(table, player[i+1], RIGHT_SIDE) == PIECE_PLACED){
                //remove the piece from the player
                if(!remove_piece_autocomplete(player, player_size, i)){
                    printf("DEBUG: remove_piece_2D failed\n");
                    exit(1);
                }
                //printf("Placed piece %d on the table\n", i+1);
                continue;
            }
        }
        //printf("Switched piece %d doesn't fit anywhere\n", i+1);
    }
}

void autocomplete_2D(Piece** table, int* pieces) {
    Piece* player = create_player_2D(*pieces);
    assign_pieces_2D(player, *pieces);
    int player_size = *pieces;
    print_player_2D(player, *pieces);

    //place first piece on the table and remove it from the player
    int picked_piece_index = rand()%*pieces;
    printf("DEBUG: Picked piece: %d\n", picked_piece_index+1);
    Piece selected_piece = player[picked_piece_index];
    table[0][10] = selected_piece;
    remove_piece_autocomplete(player, pieces, picked_piece_index);

    int iterations = 0;
    while (iterations < *pieces) {
        ai_first_fit(table, player, pieces);
        iterations++;
    }

    int iterations2 = 0;
    while (iterations2 < *pieces) {
        ai_first_fit(table, player, pieces);
        iterations2++;
    }

    int iterations3 = 0;
    while (iterations3 < *pieces) {
        ai_first_fit(table, player, pieces);
        iterations3++;
    }

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    print_table_2D(table, 1);
    print_player_2D(player, *pieces);
    printf("Score is: %d\n", calculate_score_2D(table));
}
