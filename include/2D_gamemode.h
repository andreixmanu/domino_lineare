//
// Created by manua on 04/12/2023.
//

#ifndef DOMINO_LINEARE_2D_GAMEMODE_H
#define DOMINO_LINEARE_2D_GAMEMODE_H

typedef struct piece Piece;
struct piece {
    int left_side;
    int right_side;
};

void assign_pieces_2D(Piece* player, int n);

Piece* create_player_2D(size_t n);

int first_piece_2D(Piece* row, int cols);

int last_piece_2d(Piece* row, int cols);

void use_piece_2D(Piece** table, Piece* player, int piece, int side);

void singleplayer_2D(Piece** matrix, int pieces);

Piece** create_matrix();

void not_linear_domino();

#endif //DOMINO_LINEARE_2D_GAMEMODE_H