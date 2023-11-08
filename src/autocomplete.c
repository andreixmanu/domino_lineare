//
// Created by manua on 30/10/2023.
//

#include "../include/main.h"
#include "../include/print.h"
#include <stdio.h>

void autocomplete(Player *bot, Player *enemy_bot, Domino_piece *table) {
    //TODO implementare AI
}

Domino_piece *cpu_move(Player *bot, Domino_piece *table) {

    printf("DEBUG: Print bots pieces\n");
    print_player(*bot);

    return table;
}