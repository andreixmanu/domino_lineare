//
// Created by andreixmanu on 28/10/23.
//

#include "../include/game.h"
#include "../include/print.h"
#include <stdlib.h>
#include <stdio.h>
#include "../include/autocomplete.h"
#include <stdlib.h>

#define LEFT_SIDE 0
#define RIGHT_SIDE 1
#define MOVE_ALLOWED 1
#define MOVE_NOT_ALLOWED 0


Domino_piece *create_table() {
    return NULL;
}

Domino_piece *get_player_piece(Player *player, int n) {
    //traverse player to the n-th piece and return the piece
    Domino_piece *current_node = player->first_piece;
    for (int i = 1; i < n && current_node != NULL; i++)
        current_node = current_node->next;
    return current_node;
}

Domino_piece *get_table_piece(Domino_piece *table, int n) {
    //traverse table and return n-th piece
    Domino_piece *current_node = table;
    for (int i = 0; i < n && current_node != NULL; i++)
        current_node = current_node->next;
    return current_node;
}

void append_piece(Domino_piece **table, int left_side, int right_side) {
    Domino_piece *new_piece = (Domino_piece *) malloc(sizeof(Domino_piece));
    new_piece->left_side = left_side;
    new_piece->right_side = right_side;
    new_piece->next = NULL;
    new_piece->previous = NULL;

    if (*table == NULL) {
        *table = new_piece;
    } else {
        Domino_piece *current_node = *table;
        while (current_node->next != NULL) {
            current_node = current_node->next;
        }
        current_node->next = new_piece;
        new_piece->previous = current_node;
    }
}

void prepend_piece(Domino_piece **table, int left, int right) {
    Domino_piece *new_piece = (Domino_piece *) malloc(sizeof(Domino_piece));
    new_piece->left_side = left;
    new_piece->right_side = right;
    new_piece->next = *table;
    new_piece->previous = NULL;

    if (*table != NULL) {
        (*table)->previous = new_piece;
    }

    *table = new_piece;
}

void assign_pieces(Player *player, int n) {
    const int possible_pieces[21][2] = {
            {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6},
            {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6},
            {3, 3}, {3, 4}, {3, 5}, {3, 6},
            {4, 4}, {4, 5}, {4, 6},
            {5, 5}, {5, 6},
            {6, 6}
    };

    for (int i = 0; i < n; i++) {
        int random_number = rand() % 21;

        Domino_piece *new_node = (Domino_piece *)malloc(sizeof(Domino_piece));
        if (new_node == NULL) {
            fprintf(stderr, "Errore nell'allocazione di memoria per il pezzo.\n");
            exit(EXIT_FAILURE);
        }

        new_node->left_side = possible_pieces[random_number][0];
        new_node->right_side = possible_pieces[random_number][1];
        new_node->next = NULL;
        new_node->previous = NULL;

        if (player->first_piece == NULL) {
            player->first_piece = new_node;
            player->last_piece = new_node;
        } else {
            player->last_piece->next = new_node;
            new_node->previous = player->last_piece;
            player->last_piece = new_node;
        }
    }
}

Player create_player() {
    Player player;
    player.first_piece = NULL;
    player.last_piece = NULL;
    //printf("DEBUG: Player has been created\n");
    return player;
}

//checks if the side of the domino piece given as parameter corresponds to the side the player want to put the piece
//side must be equal to table->left_side or table->right_side
int check_move(Player *player, Domino_piece *table, int n, int side) {
    Domino_piece *current_node = player->first_piece;

    // Trova il pezzo del giocatore
    int i;
    for (i = 1; i < n && current_node != NULL; i++)
        current_node = current_node->next;

    // Gestisci il caso in cui l'elemento non viene trovato o n supera il numero di pezzi
    if (i < n || current_node == NULL) {
        printf("Element not found or n exceeds the number of pieces\n");
        return MOVE_NOT_ALLOWED;
    }

    // Controlla il lato destro del tavolo
    if (side == RIGHT_SIDE) {

        Domino_piece *last_table_node = get_last_table_piece(table);

        //printf("DEBUG: Table right piece %d|%d", last_table_node->left_side, last_table_node->right_side);
        //printf(" with player piece: %d|%d\n", current_node->left_side, current_node->right_side);
        //printf("DEBUG: Checking player number %d with table number %d\n", current_node->left_side, table->right_side);

        if (last_table_node->right_side == current_node->left_side){
            return MOVE_ALLOWED;
        }
        else if(last_table_node->right_side != current_node->left_side){
            return MOVE_NOT_ALLOWED;
        } else exit(1);

    }
    else if (side == LEFT_SIDE) { //controlla il lato sinistro del tavolo

        //printf("DEBUG: Checking player piece: %d|%d", current_node->left_side, current_node->right_side);
        //printf(" with table piece %d|%d\n", table->left_side, table->right_side);
        //printf("DEBUG: Checking player number %d with table number %d\n", current_node->right_side, table->left_side);

        if (table->left_side == current_node->right_side){
            return MOVE_ALLOWED;
        }
        else if(table->left_side != current_node->right_side){
            return MOVE_NOT_ALLOWED;
        } else exit(1);

    }

    printf("Invalid side\n");
    return MOVE_NOT_ALLOWED;
}


void use_piece(Player *player1, Domino_piece *table, int n, int side) {

    if (n <= 0){ //n is invalid
        printf("n = %d\n", n);
        return;
    }

    Domino_piece *current_node = player1->first_piece;

    int i;
    for (i = 1; i < n && current_node != NULL; i++)
        current_node = current_node->next;

    if (i < n || current_node == NULL) {
        printf("Element not found or n exceeds the number of pieces\n");
        return;
    }

    //printf("DEBUG: Inside use_piece, the piece being used is %d|%d\n", current_node->left_side, current_node->right_side);

    //printf("Before check_move\n");
    if (check_move(player1, table, n, side)) {
        printf("DEBUG1: Check move returned: %d\n", check_move(player1, table, n, side));
        if (side == RIGHT_SIDE) {
            append_piece((Domino_piece **) &table, current_node->left_side, current_node->right_side);
            printf("Piece placed on right side\n");
        } else if (side == LEFT_SIDE) {
            prepend_piece((Domino_piece **) &table, current_node->left_side, current_node->right_side);
            printf("Piece placed on left side\n");
        }
    } else {
        printf("DEBUG2: Check move returned: %d\n", check_move(player1, table, n, side));
        exit(1);
    }
    //printf("Piece placed\n");

    // Remove piece from player
    if (current_node->previous == NULL) {
        player1->first_piece = current_node->next;
        if (player1->first_piece != NULL) player1->first_piece->previous = NULL;
    } else if (current_node->next == NULL) {
        player1->last_piece = current_node->previous;
        if (player1->last_piece != NULL) player1->last_piece->next = NULL;
    } else {
        Domino_piece *previous_node = current_node->previous;
        Domino_piece *next_node = current_node->next;
        previous_node->next = next_node;
        next_node->previous = previous_node;
    }
    //printf("Piece removed\n");

    //printf("Inside use_piece:\n");
    //print_table(table);

    // Move free after finishing using current_node data
    free(current_node);
    //printf("Piece used!\n");
}

void human_vs_cpu(Player *player1, Player *player2, Domino_piece *table, int nPieces) {

    int side;
    if (table != NULL) {
        //table is not empty
        printf("Do you want to place it to the left or to the right side of the table? (0/1):\n");
        scanf("%d", &side);

        if (side != LEFT_SIDE && side != RIGHT_SIDE) {
            printf("Invalid side. Please choose 0 for left or 1 for right.\n");
            return human_vs_cpu(player1, player2, table, nPieces);
        }
        //check if move is allowed
        if (check_move(player1, table, nPieces, side)) {
            use_piece(player1, table, nPieces, side);
            //printf("DEBUG: Table should have one piece\n");
            print_table(table);
        }
    } else { //table is empty, append first piece
        //printf("DEBUG: table is null, appending first piece\n");
        Domino_piece *new_piece = get_player_piece(player1, nPieces);
        append_piece(&table, new_piece->left_side, new_piece->right_side);
        //printf("DEBUG: first piece appended\n");
        //printf("DEBUG: First piece placed!\n");
        //printf("DEBUG: Piece that has to be printed is %d|%d\n", new_piece->left_side, new_piece->right_side);
        print_table(table);
        printf("Now it's the bots turn.\n");
        cpu_move(player2, table);
    }
}

void init_game() {

    Domino_piece *table = create_table();

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
        autocomplete(&bot, &enemy_bot, table);

    }
    //Human vs CPU mode
    else if (answer == 'n') {

        player = create_player();
        assign_pieces(&player, pieces);
        //print_player(player);
        enemy_bot = create_player();
        assign_pieces(&enemy_bot, pieces);
        //printf("DEBUG: Table should be empty\n");
        //print_table(table);
        printf("\nChe il gioco abbia inizio!\n"
               "Scegli la prima carta che vuoi giocare:\n");
        print_player(player);
        int choice;
        scanf("%d", &choice);
        if (choice < 1 || choice > 7) {
            printf("Invalid choice. Please choose a valid piece.\n");
            return init_game();
        }
        human_vs_cpu(&player, &enemy_bot, table, choice);

    } else {
        printf("Invalid answer\n");
        init_game();
    }
}