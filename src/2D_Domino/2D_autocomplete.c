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

int rows_ = 1;

typedef struct best_move {
    int piece;
    int side;
    int orientation;
} Best_move;

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
        if(side == RIGHT_SIDE) index = last_piece_2d(table[0], 20);

        if (index != -1) {
            use_piece_2D(table, player, i, side, player_size, HORIZONTAL, 0);
        }
    }
}

void autocomplete_2D(Piece** table, int* pieces) {
    Piece* player = create_player_2D(*pieces);
    assign_pieces_2D(player, *pieces);
    int player_size = *pieces;
    print_player_2D(player, *pieces);

    for (int i = 0; i < *pieces; i++) {
        //Best_move move = find_best_move(player, player_size, table);
        ai_first_fit(table, player, pieces);
    }

    printf("\n\n\n\n\n\n\n\n\n\n");
    print_table_2D_DEBUG(table);
    printf("Score is: %d\n", calculate_score_2D(table));
}
