//
// Created by manua on 30/10/2023.
//

#ifndef DOMINO_LINEARE_AUTOCOMPLETE_H
#define DOMINO_LINEARE_AUTOCOMPLETE_H

#include "../include/main.h"

void autocomplete(Player *bot, Player *enemy_bot, Domino_piece *table);
Domino_piece *get_first_table_piece(Domino_piece *table);
Domino_piece *get_last_table_piece(Domino_piece *table);
void cpu_move(Player *bot, Domino_piece *table);

#endif //DOMINO_LINEARE_AUTOCOMPLETE_H
