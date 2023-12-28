//
// Created by manua on 22/12/2023.
//

#ifndef DOMINO_LINEARE_2D_AUTOCOMPLETE_H
#define DOMINO_LINEARE_2D_AUTOCOMPLETE_H

#include "../include/2D_gamemode.h"

void auto_switch_values_2D(Piece* player, int player_size, int n);

int remove_piece_autocomplete(Piece *player, int *size, int index);

int use_piece_autocomplete(Piece **table, Piece piece, int side);

void undo_move(Piece** table, int side, int orientation);

void ai_first_fit(Piece** table, Piece* player, int* player_size);

void autocomplete_2D(Piece** table, int* pieces);

#endif //DOMINO_LINEARE_2D_AUTOCOMPLETE_H
