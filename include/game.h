//
// Created by andreixmanu on 28/10/23.
//


#ifndef DOMINO_LINEARE_GAME_H
#define DOMINO_LINEARE_GAME_H


#include "main.h"

Domino_piece *create_table();

Domino_piece *get_player_piece(Player *player, int n);

Domino_piece *get_table_piece(Domino_piece *table, int n);

void append_piece(Domino_piece **table, Domino_piece* piece);

void prepend_piece(Domino_piece **table, Domino_piece* piece);

void assign_pieces(Player *player, int n);

//void human_vs_cpu(Player *player1, Player *player2, Domino_piece *table, int nPieces);

Player create_player();

int check_move(Domino_piece* piece, Domino_piece *table, int side);

void use_piece(Domino_piece* piece, Domino_piece *table, int side);

void singleplayer(int pieces, Domino_piece* table);

void init_game();

#endif //DOMINO_LINEARE_GAME_H
