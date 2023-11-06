//
// Created by andreixmanu on 28/10/23.
//

#include "../include/game.h"
#include "../include/print.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/autocomplete.h"

#define LEFT_SIDE 0
#define RIGHT_SIDE 1

Domino_piece* create_table(){
    return NULL;
}

Domino_piece* append_piece(Domino_piece *table, int left, int right) {
    Domino_piece *new_piece = (Domino_piece*)malloc(sizeof(Domino_piece));
    new_piece->left_side = left;
    new_piece->right_side = right;
    new_piece->next = NULL;
    new_piece->previous = NULL;

    if (table == NULL) {
        // If the table is empty, return the new piece as the table
        return new_piece;
    } else {
        // Find the last piece in the table
        Domino_piece *current = table;
        while (current->next != NULL) {
            current = (Domino_piece *) current->next;
        }
        // Append the new piece to the end
        current->next = (struct Domino_piece *) new_piece;
        new_piece->previous = (struct Domino_piece *) current;
        return table;
    }
}

//TODO [BUG FIX] sometimes piece assigned is [0|0]
void assign_pieces(Player* player, int n){

    //array of possible pieces
    int possible_pieces[28][2] = {
            {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1 ,6},
            {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6},
            {3, 3}, {3, 4}, {3, 5}, {3, 6},
            {4, 4}, {4, 5}, {4, 6},
            {5, 5}, {5, 6},
            {6, 6}
    };

    //assign n random pieces to the player
    srand(time(NULL));
    for(int i = 0; i < n; i++){
        //generate random number between 0 and 27
        int random_number = rand() % 28;

        //create new node
        Domino_piece *new_node = (Domino_piece*) malloc(sizeof(Domino_piece));
        new_node->left_side = possible_pieces[random_number][0];
        new_node->right_side = possible_pieces[random_number][1];
        new_node->next = NULL;
        new_node->previous = NULL;

        //add node to the player
        if(player->first_piece == NULL){
            player->first_piece = new_node;
            player->last_piece = new_node;
        } else{
            player->last_piece->next = (struct Domino_piece *) new_node;
            new_node->previous = (struct Domino_piece *) player->last_piece;
            player->last_piece = new_node;
        }
    }
}

Player create_player(){
    Player player;
    player.first_piece = NULL;
    player.last_piece = NULL;
    //printf("Player has been created\n");
    return player;
}

int check_move(Player* player, Domino_piece* table, int side){
    //check if player has a piece that can be put on the table
    Domino_piece *current_node = player->first_piece;
    while(current_node != NULL){
        if(current_node->left_side == table->left_side || current_node->left_side == table->right_side ||
           current_node->right_side == table->left_side || current_node->right_side == table->right_side){
            return 1;
        }
        current_node = (Domino_piece *) current_node->next;
    }
    return 0;
}

void use_piece(Player* player1, Domino_piece* table, int n, int side) {

    // Invalid input
    if (n <= 0) return;

    Domino_piece *current_node = player1->first_piece;

    // Traverse the player's hand to find the n-th piece
    int i;
    for (i = 1; i < n && current_node != NULL; i++) {
        current_node = (Domino_piece *) current_node->next;
    }

    // Element not found or n exceeds the number of pieces, handle the error
    if (i < n || current_node == NULL){
        printf("Element not found or n exceeds the number of pieces\n");
        return;
    }

    // Remove piece from player
    if (current_node->previous == NULL) {
        player1->first_piece = (Domino_piece *) current_node->next;
        if (player1->first_piece != NULL) player1->first_piece->previous = NULL;
    } else if (current_node->next == NULL) {
        player1->last_piece = (Domino_piece *) current_node->previous;
        if (player1->last_piece != NULL) player1->last_piece->next = NULL;
    } else {
        Domino_piece *previous_node = (Domino_piece *) current_node->previous;
        Domino_piece *next_node = (Domino_piece *) current_node->next;
        previous_node->next = (struct Domino_piece *) next_node;
        next_node->previous = (struct Domino_piece *) previous_node;
    }
    free(current_node);
}


void human_vs_cpu(Player* player1, Player* player2, Domino_piece** table) {
    printf("\nChe il gioco abbia inizio!\n"
           "Scegli la prima carta che vuoi giocare:\n");
    print_player(*player1);

    int choice, side;
    scanf("%d", &choice);

    if (choice < 1 || choice > 7) {
        printf("Invalid choice. Please choose a valid piece.\n");
        return human_vs_cpu(player1, player2, table);
    }

    printf("La vuoi giocare a sinistra o a destra del tavolo? (0/1):\n");
    scanf("%d", &side);

    if (side != LEFT_SIDE && side != RIGHT_SIDE) {
        printf("Invalid side. Please choose 0 for left or 1 for right.\n");
        return human_vs_cpu(player1, player2, table);
    }
}

void init_game() {

    Domino_piece* table = create_table();

    printf("How many pieces do you want to play with?:\n");
    int pieces;
    scanf("%d", &pieces);

    printf("Do you want a bot to play? (y/n):\n");
    char answer;
    scanf(" %c", &answer);

    Player bot;
    Player player;
    Player enemy_bot;

    //CPU vs CPU mode
    if (answer == 'y') {

        bot = create_player();
        assign_pieces(&bot, pieces);
        print_player(bot);
        //create enemy bot, assign pieces and print enemy bot
        enemy_bot = create_player();
        autocomplete(&bot, &enemy_bot, (Domino_piece *) &table);

    }
    //Human vs CPU mode
    else if (answer == 'n') {

        player = create_player();
        assign_pieces(&player, pieces);
        //print_player(player);
        enemy_bot = create_player();
        printf("DEBUG: Table should be empty\n");
        print_table(table);

        human_vs_cpu(&player, &enemy_bot, (Domino_piece **) table);

    } else {
        printf("Invalid answer\n");
        init_game();
    }
}