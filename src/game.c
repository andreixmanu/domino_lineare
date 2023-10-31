//
// Created by andreixmanu on 28/10/23.
//


#include "../include/game.h"
#include "../include/print.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

//create table of 21 spaces for domino pieces
//the table will be double linked list
void create_table(){
    //create first node
    Domino_piece *first_node = (Domino_piece*) malloc(sizeof(Domino_piece));
    first_node->left_side = -1;
    first_node->right_side = -1;
    first_node->next = NULL;
    first_node->previous = NULL;

    //create the rest of the nodes
    Domino_piece *current_node = first_node;
    for(int i = 0; i < 20; i++){
        Domino_piece *new_node = (Domino_piece*) malloc(sizeof(Domino_piece));
        new_node->left_side = -1;
        new_node->right_side = -1;
        new_node->next = NULL;
        new_node->previous = (struct Domino_piece *) current_node;
        current_node->next = (struct Domino_piece *) new_node;
        current_node = new_node;
    }
    printf("Table created successfully\n");
}

//assign n random pieces to the player
/*
 * Possible variations of the pieces:
 * [1|1] [1|2] [1|3] [1|4] [1|5] [1|6]
 * [2|2] [2|3] [2|4] [2|5] [2|6]
 * [3|3] [3|4] [3|5] [3|6]
 * [4|4] [4|5] [4|6] [5|5] [5|6] [6|6]
 */

//assign n random pieces to the player according to the variations above
void assign_pieces(Player* player, int n){
    //create array of possible pieces
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
        //print_player(player);
    }
}
Player create_player(){
    Player player;
    player.first_piece = NULL;
    player.last_piece = NULL;
    printf("Player has been created\n");
    return player;
}

void init_game() {
    create_table();
    printf("Do you want a bot to play? (y/n):\n");
    char answer;
    scanf(" %c", &answer);
    printf("How many pieces do you want to play with?:\n");
    int pieces;
    scanf("%d", &pieces);

    Player bot;
    Player player;

    if (answer == 'y') {
        //create bot
        bot = create_player(bot);
        assign_pieces(&bot, pieces);
        print_player(bot);
    } else if (answer == 'n') {
        //create player
        player = create_player(player);
        assign_pieces(&player, pieces);
        print_player(player);
        //TODO continue
    } else {
        printf("Invalid answer\n");
        init_game();
    }
}

