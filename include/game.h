//
// Created by andreixmanu on 28/10/23.
//


#ifndef DOMINO_LINEARE_GAME_H
#define DOMINO_LINEARE_GAME_H


#include "main.h"

Domino_piece *create_table();

Domino_piece *get_player_piece(Player *player, int n);

void append_piece(Domino_piece **table, int left_side, int right_side);

Domino_piece *prepend_piece(Domino_piece *table, int left, int right);

void assign_pieces(Player *player, int n);

void human_vs_cpu(Player *player1, Player *player2, Domino_piece *table, int nPieces);

int check_move(Player *player, Domino_piece *table, int n, int side);

void use_piece(Player *player1, Domino_piece *table, int n, int side);

void init_game();

#endif //DOMINO_LINEARE_GAME_H
