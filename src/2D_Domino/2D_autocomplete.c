#include <stdio.h>
#include "../include/2D_gamemode.h"
#include "../include/2D_autocomplete.h"
#include "../include/2D_print.h"
#include <stdlib.h>
#include "../include/view_menu.h"

#define LEFT_SIDE 1
#define RIGHT_SIDE 2
#define HORIZONTAL 1
#define VERTICAL 2
#define MOVE_ALLOWED 1
#define MOVE_NOT_ALLOWED 0
#define PIECE_PLACED 1
#define PIECE_NOT_PLACED 0

int pick_piece_index_autocomplete(Piece *player, int player_size, int pickedIndex) {
    int result_index = 0;

    for (int i = 0; i < player_size; i++) {
        if (player[i].left_side == -1 && player[i].right_side == -1) {
            continue;
        }
        if (result_index == pickedIndex) {
            return i;
        }
        result_index++;
    }
    return -1;
}

void auto_switch_values_2D(Piece *player, int player_size, int n) {

    int index = pick_piece_index_autocomplete(player, player_size, n-1);  // -1 if option is 1-based
    if (index == -1) {
        printf("DEBUG: Auto switch values: index = -1\n");
        return;
    }
    int temp = player[index].left_side;
    player[index].left_side = player[index].right_side;
    player[index].right_side = temp;
}

int remove_piece_autocomplete(Piece *player, int *size, int index) {

    if (index >= *size) --index;
    else if (index < 0) return 0;

    for (int i = index; i < *size - 1; i++) player[i] = player[i + 1];
    (*size)--;

    return 1;
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
    } else if (side == RIGHT_SIDE && last_valid_index != -1) {

        Piece *table_piece = &table[0][last_valid_index];

        if (check_move_2D(table_piece, &piece, RIGHT_SIDE)) {
            table[0][last_valid_index + 1] = piece;
            return PIECE_PLACED;
        }
    }
    return PIECE_NOT_PLACED;
}


void ai_first_fit(Piece **table, Piece *player, int *player_size) {
    for (int i = 1; i <= *player_size; i++) {
        // Scelta casuale tra LEFT_SIDE e RIGHT_SIDE
        int side = (rand() % 2) + 1;
        int index = 0;
        // Cerca la prima posizione libera nella prima riga del tavolo
        if (side == LEFT_SIDE) index = first_piece_2D(table[0], 20);
        else if (side == RIGHT_SIDE) index = last_piece_2d(table[0], 20);

        if (index != -1) {
            if (use_piece_autocomplete(table, player[i + 1], side) == PIECE_PLACED) {
                //remove the piece from the player
                if (!remove_piece_autocomplete(player, player_size, i + 1)) {
                    printf("DEBUG: remove_piece_2D failed\n");
                    exit(1);
                }
                continue;
            }
        }
    }

    for (int i = 0; i < *player_size; i++) {

        auto_switch_values_2D(player, *player_size, i + 1);

        int left_index = first_piece_2D(table[0], 20);
        if (left_index != -1) {
            if (use_piece_autocomplete(table, player[i + 1], LEFT_SIDE) == PIECE_PLACED) {
                //remove the piece from the player
                if (!remove_piece_autocomplete(player, player_size, i + 1)) {
                    printf("DEBUG: remove_piece_2D failed\n");
                    exit(1);
                }
                i = 0;
                continue;
            }
        }

        int right_index = last_piece_2d(table[0], 20);
        if (right_index != -1) {
            if (use_piece_autocomplete(table, player[i + 1], RIGHT_SIDE) == PIECE_PLACED) {
                //remove the piece from the player
                if (!remove_piece_autocomplete(player, player_size, i + 1)) {
                    printf("DEBUG: remove_piece_2D failed\n");
                    exit(1);
                }
                i = 0;
                continue;
            }
        }
    }
}

void ultimate_try(Piece** table, Piece* player, int* pieces){

    int last_valid_index = last_piece_2d(table[0], 20);
    int first_valid_index = first_piece_2D(table[0], 20);

    for(int i = 0; i < *pieces; i++){
        if(player[i].left_side == table[0][last_valid_index].right_side){
            table[0][last_valid_index + 1] = player[i];
            remove_piece_autocomplete(player, pieces, i);
            continue;
        }
        if(player[i].right_side == table[0][first_valid_index].left_side){
            table[0][first_valid_index - 1] = player[i];
            remove_piece_autocomplete(player, pieces, i);
            continue;
        }
    }
}

void autocomplete_2D(Piece **table, int *pieces) {
    clear_screen();
    Piece *player = create_player_2D(*pieces);
    assign_pieces_2D(player, *pieces);
    printf("\nBots pieces:\n");
    print_player_2D(player, *pieces);


    int picked_piece_index = rand() % *pieces;
    Piece selected_piece = player[picked_piece_index];
    table[0][10] = selected_piece;
    remove_piece_autocomplete(player, pieces, picked_piece_index);

    int iterations = 0;
    while (iterations < *pieces) {
        ai_first_fit(table, player, pieces);
        iterations++;
    }

    if(!check_empty_player(player, *pieces)) ultimate_try(table, player, pieces);

    printf("Table:\n");
    print_table_2D(table, 1);

    print_end_game_2D(table, 1);
}