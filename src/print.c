//
// Created by andreixmanu on 28/10/23.
//

#include "../include/main.h"
#include <stdio.h>
#include "../include/view_menu.h"
#include "../include/game.h"


void print_table(Domino_piece *table) {
    if (table == NULL) {
        printf("Table is empty\n");
        return;
    }
    int i = 0;
    Domino_piece *current_node = table;
    while (current_node != NULL) {
        printf("%d|%d ", current_node->left_side, current_node->right_side);
        current_node = current_node->next;
        i++;
    }
    printf("\n");
    printf("DEBUG: Table contains %d pieces\n", i);
}


void print_player(Player player) {
    //printf("printing player\n");
    if (player.first_piece == NULL) {
        printf("Player has no pieces, assigning now.\n");
        assign_pieces(&player, 7);
        print_player(player);
    }
    int i = 1;
    Domino_piece *current_node = player.first_piece;
    while (current_node != NULL) {
        printf("%d: %d|%d\n",i, current_node->left_side, current_node->right_side);
        current_node = current_node->next;
        i++;
    }
    printf("\n");
}

void print_rules(){
    printf("\tThe game is played by two players. Each player has 7 domino pieces.\n"
           "\tThe first player is chosen randomly. The first player puts a domino piece on the table.\n"
           "\tThe second player puts a domino piece on the table.\n"
           "\tThe player who puts the domino piece with the highest sum of the numbers on the domino piece wins the round.\n"
           "\tThe player who wins the round gets a point.\n"
           "\tThe player who has the most points at the end of the game wins.\n"
           "\tIf the sum of the numbers on the domino pieces is equal, the player who put the domino piece first wins the round.\n"
           "\tIf the sum of the numbers on the domino pieces is equal and the domino pieces are the same, the round is a draw.\n"
           "\tIf a player doesn't have a domino piece that can be put on the table, he draws a domino piece from the table.\n"
           "\tIf the table is empty, the player draws a domino piece from the table.\n"
           "\tIf the player doesn't have a domino piece that can be put on the table and the table is empty, the player passes.\n"
           "\tIf both players pass, the game ends.\n\n");
    view_menu();
}