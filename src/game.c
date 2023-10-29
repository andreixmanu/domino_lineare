//
// Created by andreixmanu on 28/10/23.
//


#include "../include/game.h"
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
        new_node->previous = current_node;
        current_node->next = new_node;
        current_node = new_node;
    }
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
void assign_pieces(Player player, int n){
    return;
}
void create_player(Player player){
    player.first_piece = NULL;
    player.last_piece = NULL;
}

void init_game(){
    create_table();
    //ask if the player wants a bot to play
    printf("Do you want a bot to play? (y/n): ");
    char answer;
    scanf("%c", &answer);
    if(answer == 'y'){
        //create bot
        Player bot;
        create_player(bot);
    } else if(answer == 'n'){
        //create player
        Player player;
        create_player(player);
    } else{
        printf("Invalid answer\n");
        init_game();
    }
}

