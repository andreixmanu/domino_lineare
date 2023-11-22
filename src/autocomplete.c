//
// Created by manua on 30/10/2023.
//

#include "../include/main.h"
#include "../include/print.h"
#include "../include/game.h"
#include "../include/autocomplete.h"
#include <stdio.h>
#include <stdlib.h>

#define LEFT_SIDE 0
#define RIGHT_SIDE 1


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


Id_piece decide_piece(Domino_piece* table, Player* bot) {
    Id_piece returning_piece = {0, LEFT_SIDE}; // Default values

    // Traverse the Table and get the score
    int score = 0, i = 0, j = 0;
    Domino_piece* current_node = table;
    while (current_node != NULL) {
        score += current_node->left_side + current_node->right_side;
        current_node = current_node->next;
    }
    int max_score = score;
    //printf("DEBUG: Score is %d\n", score);

    Domino_piece* check_left = bot->first_piece;
    while (check_left != NULL) {
        //printf("Entered first while\n");
        if (check_left->right_side == table->left_side) {
            //printf("DEBUG: Found a piece that fits on the left side\n");
            score = score - table->right_side + check_left->left_side + check_left->right_side;
            if (score > max_score) {
                max_score = score;
                returning_piece.npiece = i;
                returning_piece.side = LEFT_SIDE;
            }
            i++;
        }
        check_left = check_left->next;
    }

    Domino_piece* check_right = bot->last_piece;
    while (check_right != NULL) {
        //printf("Entered second while\n");
        if (check_right->left_side == get_last_table_piece(table)->right_side) {
            //printf("DEBUG: Found a piece that fits on the right side\n");
            score = score - get_last_table_piece(table)->left_side + check_right->left_side + check_right->right_side;
            if (score > max_score) {
                max_score = score;
                returning_piece.npiece = j;
                returning_piece.side = RIGHT_SIDE;
            }
            j++;
        }
        check_right = check_right->previous;
    }
    printf("DEBUG: Returning piece is %d on side %d\n", returning_piece.npiece, returning_piece.side);
    returning_piece.npiece++;
    return returning_piece;
}

void cpu_move(Player *bot, Domino_piece *table) {
    printf("Bot's pieces:\n");
    print_player(*bot);

    Id_piece piece = decide_piece(table, bot);
    printf("DEBUG: Bot has decided to use piece %d on side %d\n", piece.npiece, piece.side);

    use_piece(bot, table, piece.npiece, piece.side);

    printf("Printing new table\n");
    print_table(table);
}
