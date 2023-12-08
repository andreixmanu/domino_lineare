//
// Created by andreixmanu on 28/10/23.
//

#include "include/main.h"
#include <stdio.h>
#include "include/view_menu.h"
#include "include/game.h"
#include <stdlib.h>


void print_table(Domino_piece* table) {
    if (table == NULL) {
        printf("Table is empty\n");
        return;
    }
    int i = 0;
    Domino_piece *current_node = table;
    while (current_node != NULL) {
        printf("[%d|%d] ", current_node->left_side, current_node->right_side);
        current_node = current_node->next;
        i++;
    }
    printf("\n");
    //printf("DEBUG: Table contains %d pieces\n", i);
}

void print_player(Player* player) {
    if (player == NULL) {
        printf("DEBUG: Player is null\n");
        return;
    }
    if (player->first_piece == NULL) {
        printf("Player has no pieces, assigning now.\n");
        assign_pieces(player, 7);
        print_player(player);
    }
    int i = 1;
    Domino_piece *current_node = player->first_piece;
    while (current_node != NULL) {
        printf("%d: [%d|%d]\n",i, current_node->left_side, current_node->right_side);
        current_node = current_node->next;
        i++;
    }
    printf("\n");
}

void print_rules(){

    printf("\tYou can chose to play or to let the CPU play with its own pieces.\n"
           "\tYou have a chosen number of pieces, and each piece has two sides.\n"
           "\tPlace a piece on the table, and the next pieces to be placed must \n"
           "\thave the side adjacent to the piece on the table equal.\n"
           "\tYou can place pieces only to the right or left of the table.\n"
           "\tIf you can't place any piece you call the end of the game, and the\n"
           "\tscore get calculated.\n"
           "\tThe score is calculated by adding the two sides of each piece on the\n"
           "\ttable.\n"
           "\tThe same rules apply to the CPU.\n");

    view_menu();
}