//
// Created by andreixmanu on 28/10/23.
//

#ifndef DOMINO_LINEARE_MAIN_H
#define DOMINO_LINEARE_MAIN_H

#define HORIZONTAL 0
#define VERTICAL 1


typedef struct dominio_piece Domino_piece;
struct dominio_piece {
    int left_side;
    int right_side;
    Domino_piece *next;
    Domino_piece *previous;
};

typedef struct player Player;
struct player {
    Domino_piece *first_piece;
    Domino_piece *last_piece;
};

int main();

#endif //DOMINO_LINEARE_MAIN_H
