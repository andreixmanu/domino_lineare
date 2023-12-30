//
// Created by andreixmanu on 28/10/23.
//

#include "include/main.h"
#include <stdio.h>
#include "include/view_menu.h"
#include "include/game.h"
#include <stdlib.h>


void print_table(Domino_piece *table) {
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
}

void print_player(Player *player) {
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
        printf("\t%d: [%d|%d]\n", i, current_node->left_side, current_node->right_side);
        current_node = current_node->next;
        i++;
    }
    printf("\n");
}

void print_rules() {

    printf("\tYou can chose to play or to let the CPU play with its own pieces.\n"
           "\tYou have a chosen number of pieces, and each piece has two sides.\n"
           "\tPlace a piece on the table, and the next pieces to be placed must \n"
           "\thave the side adjacent to the piece on the table equal.\n"
           "\tYou can place pieces only to the right or left of the table.\n"
           "\tIf you can't place any piece you call the end of the game, and the\n"
           "\tscore get calculated.\n"
           "\tThe score is calculated by adding the two sides of each piece on the\n"
           "\ttable.\n"
           "\tThe same rules apply to the CPU.\n"
           "\tYou can also place pieces in vertical, if you choose to play the non-linear mode.\n"
           "\tSame rules apply to the vertical placing of the pieces.\n");

    view_menu();
}

void print_end_game(Domino_piece **table) {
    printf("\n"
           "  ________                           ________                          ._.\n"
           " /  _____/ _____     _____    ____   \\_____  \\  ___  __  ____  _______ | |\n"
           "/   \\  ___ \\__  \\   /     \\ _/ __ \\   /   |   \\ \\  \\/ /_/ __ \\ \\_  __ \\| |\n"
           "\\    \\_\\  \\ / __ \\_|  Y Y  \\\\  ___/  /    |    \\ \\   / \\  ___/  |  | \\/ \\|\n"
           " \\______  /(____  /|__|_|  / \\___  > \\_______  /  \\_/   \\___  > |__|    __\n"
           "        \\/      \\/       \\/      \\/          \\/             \\/          \\/\n");

    printf("\n"
           "______ _             _   _____                    \n"
           "|  ___(_)           | | /  ___|                   \n"
           "| |_   _ _ __   __ _| | \\ `--.  ___ ___  _ __ ___ \n"
           "|  _| | | '_ \\ / _` | |  `--. \\/ __/ _ \\| '__/ _ \\\n"
           "| |   | | | | | (_| | | /\\__/ / (_| (_) | | |  __/\n"
           "\\_|   |_|_| |_|\\__,_|_| \\____/ \\___\\___/|_|  \\___|\n"
           "                                                  \n"
           "                                                  \n");

    printf("%d\n", calculate_score(*table));

    printf("Do you want to play again? (y/n)\n");
    char answer;
    scanf(" %c", &answer);

    if (answer == 'y') main();
    else exit(0);
}