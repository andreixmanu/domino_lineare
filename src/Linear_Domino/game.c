//
// Created by andreixmanu on 28/10/23.
//

#include "include/game.h"
#include "include/print.h"
#include <stdlib.h>
#include <stdio.h>
#include "include/autocomplete.h"
#include "include/main.h"
#include "../include/view_menu.h"

#define LEFT_SIDE 1
#define RIGHT_SIDE 2
#define MOVE_ALLOWED 1
#define MOVE_NOT_ALLOWED 0

int max_pieces;

Domino_piece *create_table() {
    return NULL;
}

int calculate_score(Domino_piece *table) {
    int score = 0;
    if (table == NULL) {
        printf("DEBUG: inside calculate_score table is NULL\n");
        exit(EXIT_FAILURE);
    }
    Domino_piece *current_node = table;
    while (current_node != NULL) {
        score += (current_node->left_side + current_node->right_side);
        current_node = current_node->next;
    }
    return score;
}

Domino_piece *get_player_piece(Player *player, int n, int max) {

    if(n > max){
        printf("DEBUG: n is greater than max_pieces\n");
        return NULL;
    }

    // Check if player and first_piece are not null
    if (player == NULL || player->first_piece == NULL) {
        printf("DEBUG: Player is null or has no pieces\n");
        return NULL;
    }

    // Traverse player to the n-th piece and return the piece
    Domino_piece *current_node = player->first_piece;
    for (int i = 1; i < n && current_node != NULL; i++) {
        current_node = current_node->next;
    }
    return current_node;
}

void append_piece(Domino_piece **table, Domino_piece *piece) {

    Domino_piece *piece_clone = (Domino_piece *) malloc(sizeof(Domino_piece));

    piece_clone->left_side = piece->left_side;
    piece_clone->right_side = piece->right_side;
    piece_clone->next = NULL;
    piece_clone->previous = NULL;

    if (*table == NULL) {
        *table = piece_clone;
    } else {
        Domino_piece *current_node = *table;
        while (current_node->next != NULL) {
            current_node = current_node->next;
        }
        current_node->next = piece_clone;
        piece_clone->previous = current_node;
    }
}

void prepend_piece(Domino_piece **table, Domino_piece *piece) {
    Domino_piece *piece_clone = (Domino_piece *) malloc(sizeof(Domino_piece));

    piece_clone->left_side = piece->left_side;
    piece_clone->right_side = piece->right_side;
    piece_clone->next = *table;
    piece_clone->previous = NULL;

    if (*table != NULL) {
        (*table)->previous = piece_clone;
    }
    *table = piece_clone;
}

void assign_pieces(Player *player, int n) {
    const int possible_pieces[21][2] = {
            {1, 1},
            {1, 2},
            {1, 3},
            {1, 4},
            {1, 5},
            {1, 6},
            {2, 2},
            {2, 3},
            {2, 4},
            {2, 5},
            {2, 6},
            {3, 3},
            {3, 4},
            {3, 5},
            {3, 6},
            {4, 4},
            {4, 5},
            {4, 6},
            {5, 5},
            {5, 6},
            {6, 6}
    };

    for (int i = 0; i < n; i++) {
        int random_number = rand() % 21;

        Domino_piece *new_node = (Domino_piece *) malloc(sizeof(Domino_piece));
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
    return player;
}

int check_move(Domino_piece *piece, Domino_piece *table, int side) {

    if (table == NULL) {
        printf("check_move: table is empty.\n");
        exit(EXIT_FAILURE);
    }

    // Controlla il lato destro del tavolo
    if (side == RIGHT_SIDE) {

        Domino_piece *last_table_node = get_last_table_piece(table);

        if (last_table_node->right_side == piece->left_side) {
            return MOVE_ALLOWED;
        } else if (last_table_node->right_side != piece->left_side) {
            return MOVE_NOT_ALLOWED;
        } else exit(EXIT_FAILURE);

    } else if (side == LEFT_SIDE) { //controlla il lato sinistro del tavolo

        if (table->left_side == piece->right_side) {
            return MOVE_ALLOWED;
        } else if (table->left_side != piece->right_side) {
            return MOVE_NOT_ALLOWED;
        }

    }

    printf("Invalid side\n");
    return MOVE_NOT_ALLOWED;
}

void use_piece(Domino_piece *piece, Domino_piece **table, int side, Player *player) {

    if (*table == NULL) {
        append_piece(table, piece);
    } else {
        // Check if the move is allowed
        if (check_move(piece, *table, side)) {
            if (side == RIGHT_SIDE) {
                append_piece(table, piece);
            } else {
                prepend_piece(table, piece);
            }
        } else {
            // printf("Move not allowed.\n");
            return;
        }
    }

    // Remove used piece from player
    if (piece->previous != NULL) {
        piece->previous->next = piece->next;
    } else {
        // The used piece is the first piece in the player's list
        // Update the head of the player's list
        player->first_piece = piece->next;
    }

    if (piece->next != NULL) {
        piece->next->previous = piece->previous;
    }

    // Free the memory of the used piece
    free(piece);
}

void switch_values(Player *player, int n){
    Domino_piece* temp = get_player_piece(player, n, max_pieces);

    if(temp == NULL) {
        printf("Error: switched piece index is NULL\n");
        return;
    }

    int temp_value = temp->left_side;
    temp->left_side = temp->right_side;
    temp->right_side = temp_value;
}

void singleplayer(int pieces, Domino_piece *table) {
    Player player = create_player();
    assign_pieces(&player, pieces);

    // place first piece
    printf("Select the first piece to place:\n");
    print_player(&player);
    int first_piece;
    scanf(" %d", &first_piece);

    if (scanf("%d", &pieces) != 1) {
        printf("Invalid input. Please enter a number.\n");
        flush_input_buffer();
        singleplayer(pieces, table);
    }

    Domino_piece *selected_piece = get_player_piece(&player, first_piece, pieces);
    if(selected_piece == NULL) {
        printf("Selected piece is null\n");
        printf("\n");
        flush_input_buffer();
        singleplayer(pieces, table);
    }
    use_piece(selected_piece, &table, RIGHT_SIDE, &player);
    print_table(table);

    while (player.first_piece != NULL) {

        printf("\nYour pieces:\n");
        print_player(&player);

        printf("Which piece do you want to place?\n");
        printf("Press 0 to quit if you can't place any piece\n");
        printf("Press 's' to switch values\n");

        char choice;
        scanf(" %c", &choice);

        if (choice == '0') {
            print_end_game(&table);
            exit(EXIT_SUCCESS);
        } else if (choice == 's') {
            // Switch values of the selected piece
            printf("Enter the piece number to switch values: ");
            int piece_to_switch;
            scanf("%d", &piece_to_switch);
            switch_values(&player, piece_to_switch);
            continue; // Skip the rest of the loop and go to the next iteration
        }

        int piece;
        sscanf(&choice, "%d", &piece);

        Domino_piece *used_piece = get_player_piece(&player, piece, max_pieces);

        // append first piece
        if (table == NULL) {
            use_piece(used_piece, &table, RIGHT_SIDE, &player);
            // now the table should NOT be NULL
            print_table(table); // table now is null
            continue;
        } else { // append / prepend next piece
            printf("Where do you want to place it? (Left :1, Right: 2)\n");
            int side;
            scanf("%d", &side);

            if (side == LEFT_SIDE) {
                use_piece(used_piece, &table, LEFT_SIDE, &player);
            } else if (side == RIGHT_SIDE) {
                use_piece(used_piece, &table, RIGHT_SIDE, &player);
            } else {
                printf("Invalid side. Please choose 1 for left or 2 for right.\n");
                continue;
            }
        }
        print_table(table);
    }
    print_end_game(&table);
}


void init_game() {

    Domino_piece *table = create_table();

    printf("How many pieces do you want to play with?:\n");


    if (scanf("%d", &max_pieces) != 1) {
        printf("Invalid input. Please enter a number.\n");
        flush_input_buffer();
        init_game();
    }

    printf("Choose the game mode:\n");
    printf("\t1. Singleplayer\n");
    printf("\t2. CPU mode\n");

    int gameMode;
    scanf("%d", &gameMode);

    switch (gameMode) {
        case 1:
            singleplayer(max_pieces, table);
            break;
        case 2: {
            Player bot = create_player();
            assign_pieces(&bot, max_pieces);
            autocomplete_stupid(&bot, table, max_pieces);
            break;
        }
        default:
            printf("Invalid game mode. Please choose 1 for singleplayer or 2 for CPU mode.\n");
            flush_input_buffer();
            init_game();
    }
    free(table);
}