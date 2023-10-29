//
// Created by andreixmanu on 28/10/23.
//

#include "main.c"

void print_table(Table table) {
    Domino_piece *current_node = table.first_place;
    while (current_node != NULL) {
        printf("%d|%d ", current_node->left_side, current_node->right_side);
        current_node = current_node->next;
    }
    printf("\n");
}

void print_player(Player player) {
    Domino_piece *current_node = player.first_piece;
    while (current_node != NULL) {
        printf("%d|%d ", current_node->left_side, current_node->right_side);
        current_node = current_node->next;
    }
    printf("\n");
}

void print_rules(){
    printf("The game is played by two players. Each player has 7 domino pieces.\n"
           "The first player is chosen randomly. The first player puts a domino piece on the table.\n"
           "The second player puts a domino piece on the table.\n"
           "The player who puts the domino piece with the highest sum of the numbers on the domino piece wins the round.\n"
           "The player who wins the round gets a point.\n"
           "The player who has the most points at the end of the game wins.\n"
           "If the sum of the numbers on the domino pieces is equal, the player who put the domino piece first wins the round.\n"
           "If the sum of the numbers on the domino pieces is equal and the domino pieces are the same, the round is a draw.\n"
           "If a player doesn't have a domino piece that can be put on the table, he draws a domino piece from the table.\n"
           "If the table is empty, the player draws a domino piece from the table.\n"
           "If the player doesn't have a domino piece that can be put on the table and the table is empty, the player passes.\n"
           "If both players pass, the game ends.\n");
    view_menu();
}