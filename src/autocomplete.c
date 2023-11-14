//
// Created by manua on 30/10/2023.
//

#include "../include/main.h"
#include "../include/print.h"
#include <stdio.h>

void autocomplete(Player *bot, Player *enemy_bot, Domino_piece *table) {
    //TODO implementare AI
}

Domino_piece *get_first_table_piece(Domino_piece *table) {
    Domino_piece *current_node = (Domino_piece *) malloc(sizeof(Domino_piece));
    current_node->left_side = table->left_side;
    current_node->right_side = table->right_side;
    current_node->next = NULL;
    current_node->previous = NULL;
    return current_node;
}

Domino_piece *get_last_table_piece(Domino_piece *table) {
    Domino_piece *current_node = table;
    while (current_node->next != NULL) {
        current_node = current_node->next;
    }
    return current_node;
}


void cpu_move(Player *bot, Domino_piece *table) {
    printf("DEBUG: Print bots pieces\n");
    print_player(*bot);
    Domino_piece *first_table_piece = get_first_table_piece(table);
    Domino_piece *last_table_piece = get_last_table_piece(table);

    use_piece(bot, table, 1, 1);
    print_table(table);
}
