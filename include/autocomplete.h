//
// Created by manua on 30/10/2023.
//

#ifndef DOMINO_LINEARE_AUTOCOMPLETE_H
#define DOMINO_LINEARE_AUTOCOMPLETE_H

#include "../include/main.h"

typedef struct{
    int npiece;
    int side;
} Id_piece;

void autocomplete(Player *bot, Domino_piece *table);
Domino_piece *get_first_table_piece(Domino_piece *table);
Domino_piece *get_last_table_piece(Domino_piece *table);
Id_piece decide_piece(Domino_piece* table, Player* bot);
void cpu_move(Player *bot, Domino_piece *table);

#endif //DOMINO_LINEARE_AUTOCOMPLETE_H
