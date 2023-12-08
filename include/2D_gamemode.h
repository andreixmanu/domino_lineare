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

void singleplayer_2D();

void not_linear_domino();

#endif //DOMINO_LINEARE_2D_GAMEMODE_H
