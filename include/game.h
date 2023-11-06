//
// Created by andreixmanu on 28/10/23.
//


#ifndef DOMINO_LINEARE_GAME_H
#define DOMINO_LINEARE_GAME_H


#include "main.h"

Domino_piece* create_table();
Domino_piece* append_piece(Domino_piece * table, int left, int right);
void assign_pieces(Player* player, int n);
void human_vs_cpu(Player* player1, Player* player2, Domino_piece** table);
void init_game();

#endif //DOMINO_LINEARE_GAME_H
