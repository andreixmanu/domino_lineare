//
// Created by andreixmanu on 28/10/23.
//

#include "../include/game.h"
#include "../include/print.h"
#include <stdlib.h>
#include <stdio.h>
#include "../include/autocomplete.h"

#define LEFT_SIDE 0
#define RIGHT_SIDE 1
#define MOVE_ALLOWED 1
#define MOVE_NOT_ALLOWED 0


Domino_piece *create_table() {
    return NULL;
}

Domino_piece *get_player_piece(Player *player, int n) {
    // Check if player and first_piece are not null
    if (player == NULL || player->first_piece == NULL) {
        printf("DEBUG: Player is null or has no pieces\n");
        return NULL;
    }

    // Traverse player to the n-th piece and return the piece
    Domino_piece *current_node = player->first_piece;
    for (int i = 1; i <= n && current_node != NULL; i++) {
        current_node = current_node->next;
    }

    return current_node;
}

Domino_piece *get_table_piece(Domino_piece *table, int n) {
    //traverse table and return n-th piece
    Domino_piece *current_node = table;
    for (int i = 1; i <= n && current_node != NULL; i++)
        current_node = current_node->next;
    return current_node;
}

void append_piece(Domino_piece **table, Domino_piece* piece) {

    if (*table == NULL) {
        *table = piece;
    } else {
        Domino_piece *current_node = *table;
        while (current_node->next != NULL) {
            current_node = current_node->next;
        }
        current_node->next = piece;
        piece->previous = current_node;
        piece->next = NULL;
    }
    printf("DEBUG: Appended piece: %d|%d\n", piece->left_side, piece->right_side);
}

void prepend_piece(Domino_piece **table, Domino_piece* piece) {
    //create clone of piece
    Domino_piece* piece_clone = (Domino_piece*) malloc(sizeof(piece));

    //initialize clone
    piece_clone->next = NULL;
    piece_clone->previous = NULL;
    piece_clone->left_side = piece->left_side;
    piece_clone->right_side = piece->right_side;

    if (*table != NULL) {
        piece_clone->next = *table;
        (*table)->previous = piece_clone;
    } else {
        piece_clone->next = NULL;
    }
    *table = piece_clone;
    printf("DEBUG: Prepended piece: %d|%d\n", piece->left_side, piece->right_side);
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
int check_move(Domino_piece* piece,  Domino_piece *table, int side) {

    if(table == NULL){
        printf("check_move: table is empty.\n");
        exit(EXIT_FAILURE);
    }

    // Controlla il lato destro del tavolo
    if (side == RIGHT_SIDE) {

        Domino_piece *last_table_node = get_last_table_piece(table);

        //printf("DEBUG: Table right piece %d|%d", last_table_node->left_side, last_table_node->right_side);
        //printf(" with player piece: %d|%d\n", current_node->left_side, current_node->right_side);
        //printf("DEBUG: Checking player number %d with table number %d\n", current_node->left_side, table->right_side);

        if (last_table_node->right_side == piece->left_side){
            return MOVE_ALLOWED;
        }
        else if(last_table_node->right_side != piece->left_side){
            return MOVE_NOT_ALLOWED;
        } else exit(EXIT_FAILURE);

    } else if (side == LEFT_SIDE) { //controlla il lato sinistro del tavolo

        //printf("DEBUG: Checking player piece: %d|%d", current_node->left_side, current_node->right_side);
        //printf(" with table piece %d|%d\n", table->left_side, table->right_side);
        //printf("DEBUG: Checking player number %d with table number %d\n", current_node->right_side, table->left_side);

        if (table->left_side == piece->right_side){
            return MOVE_ALLOWED;
        }
        else if(table->left_side != piece->right_side){
            return MOVE_NOT_ALLOWED;
        } else exit(33);

    }

    printf("Invalid side\n");
    return MOVE_NOT_ALLOWED;
}


void use_piece(Domino_piece * piece, Domino_piece *table, int side) {

    printf("DEBUG: Piece being used: %d|%d\n", piece->left_side, piece->right_side);
    if(table == NULL){
        printf("DEBUG: Table is empty, appending piece\n");
        append_piece(&table, piece);
    } else {
        // Check if the move is allowed
        if (check_move(piece, table, side)) {
            if (side == RIGHT_SIDE) {
                append_piece(&table, piece);
            } else if (side == LEFT_SIDE) {
                prepend_piece(&table, piece);
            } else {
                printf("Side neither LEFT_SIDE nor RIGHT_SIDE\n");
                exit(EXIT_FAILURE);
            }
        } else {
            printf("Move not allowed.\n");
            exit(EXIT_FAILURE);
        }
    }

    // Remove used piece from player
    if (piece->previous == NULL) {
        piece->next->previous = NULL;
    } else if (piece->next == NULL) {
        piece->previous->next = NULL;
    } else {
        piece->previous->next = piece->next;
        piece->next->previous = piece->previous;
    }
    free(piece);
}

/*void human_vs_cpu(Player *player1, Player *player2, Domino_piece *table, int nPieces) {

    int side;
    if (table != NULL) {
        //table is not empty
        printf("Your turn!\n");
        print_player(*player1);

        printf("Which piece do you want to place on the table?\n");
        printf("Press q to surrender if you don't have any pieces that can be placed on the table.\n");
        int choice;
        scanf("%d", &choice);
        //check if player wants to surrender
        if (choice == 'q') {
            printf("You surrendered. The bot wins!\n");
            exit(0);
        }
        printf("Do you want to place it to the left or to the right side of the table? (0/1):\n");
        scanf("%d", &side);

        if (side != LEFT_SIDE && side != RIGHT_SIDE) {
            printf("Invalid side. Please choose 0 for left or 1 for right.\n");
            return human_vs_cpu(player1, player2, table, nPieces);
        }
        //check if move is allowed
        if (check_move(player1, table, nPieces, side)) {
            use_piece(player1, table, nPieces, side);
            print_table(table);
        } else {
            printf("Invalid move. Please choose a valid piece.\n");
            return human_vs_cpu(player1, player2, table, nPieces);

        }
    } else { //table is empty, append first piece
        Domino_piece *new_piece = get_player_piece(player1, nPieces);
        append_piece(&table, new_piece->left_side, new_piece->right_side);
        print_table(table);
        printf("Now it's the bots turn.\n");
        cpu_move(player2, table);
        human_vs_cpu(player1, player2, table, nPieces);
    }
}*/

void singleplayer(int pieces, Domino_piece* table) {
    Player player = create_player();
    assign_pieces(&player, pieces);

    while (player.first_piece != NULL) {

        printf("\nYour pieces:\n");
        print_player(player);

        printf("Which piece do you want to place?\n");
        int piece;
        scanf("%d", &piece);
        Domino_piece* used_piece = get_player_piece(&player, piece);
        printf("DEBUG: Chosen piece: %d|%d\n", used_piece->left_side, used_piece->right_side);

        //append first piece
        if (table == NULL) {
            append_piece(&table, used_piece);
            print_table(table);
            continue;
        } else { //append / prepend next piece
            printf("Where do you want to place it? (Left :0, Right: 1)\n");
            int side;
            scanf("%d", &side);

            if (side == LEFT_SIDE) {
                printf("DEBUG: Using piece on the left side...\n");
                use_piece(used_piece, table, LEFT_SIDE);
            } else if (side == RIGHT_SIDE) {
                printf("DEBUG: Using piece on the right side...\n");
                use_piece(used_piece, table, RIGHT_SIDE);
            } else {
                printf("Invalid side. Please choose 0 for left or 1 for right.\n");
                continue;  // Add this line to continue the loop
            }
            printf("DEBUG: After using piece...\n");
        }
        print_table(table);
    }

    // Add the following line to break out of the loop when the player has no more pieces
    printf("You have no more pieces. The game is over.\n");
}

void init_game() {

    Domino_piece *table = create_table();

    printf("How many pieces do you want to play with?:\n");
    int pieces;
    scanf("%d", &pieces);

    printf("Choose the game mode:\n");
    printf("1. Singleplayer\n");
    //printf("2. Player vs CPU\n");
    printf("2. CPU mode\n");

    int gameMode;
    scanf("%d", &gameMode);

    switch (gameMode) {
        case 1: // Singleplayer
            singleplayer(pieces, table);
            break;
        case 2: { // CPU mode
            Player bot = create_player();
            assign_pieces(&bot, pieces);
            autocomplete(&bot, table);
            break;
        }
        default:
            printf("Invalid game mode. Please choose 1 for singleplayer or 2 for CPU mode.\n");
            init_game();
    }
}