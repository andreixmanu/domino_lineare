//
// Created by andreixmanu on 28/10/23.
//

#ifndef DOMINO_LINEARE_MAIN_H
#define DOMINO_LINEARE_MAIN_H

typedef struct {
    int left_side;
    int right_side;
    struct Domino_piece *next;
    struct Domino_piece *previous;
} Domino_piece;

typedef struct {
    Domino_piece *first_place;
    Domino_piece *last_place;
} Table;

typedef struct {
    Domino_piece *first_piece;
    Domino_piece *last_piece;
} Player;

int main()

#endif //DOMINO_LINEARE_MAIN_H
