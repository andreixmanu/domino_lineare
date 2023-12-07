//
// Created by andreixmanu on 28/10/23.
//

#include "../include/game.h"
#include "../include/print.h"
#include <stdlib.h>
#include <stdio.h>
#include "../include/autocomplete.h"
#include "../include/main.h"

#define LEFT_SIDE 0
#define RIGHT_SIDE 1
#define MOVE_ALLOWED 1
#define MOVE_NOT_ALLOWED 0


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
        score += (current_node->left_side.value + current_node->right_side.value);
        current_node = current_node->next;
    }
    return score;
}

Domino_piece *get_player_piece(Player *player, int n) {
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

Domino_piece *get_table_piece(Domino_piece *table, int n) {
    //traverse table and return n-th piece
    Domino_piece *current_node = table;
    for (int i = 1; i < n && current_node != NULL; i++)
        current_node = current_node->next;
    return current_node;
}

void append_vertical_piece(Domino_piece **table, Domino_piece *piece, int side) {
    Domino_piece *piece_clone = (Domino_piece *) malloc(sizeof(Domino_piece));

    piece_clone->orientation = VERTICAL;
    piece_clone->left_side.value = piece->left_side.value;
    piece_clone->left_side.other_box = &piece_clone->right_side;
    piece_clone->right_side.value = piece->right_side.value;
    piece_clone->right_side.other_box = &piece_clone->left_side;
    piece_clone->next = NULL;
    piece_clone->previous = NULL;

    if (side == LEFT_SIDE) piece_clone->downside = &piece_clone->left_side;
    if (side == RIGHT_SIDE) piece_clone->downside = &piece_clone->right_side;
    //TODO finish function
}

void prepend_vertical_piece(Domino_piece **table, Domino_piece *piece, int side) {
    Domino_piece *piece_clone = (Domino_piece *) malloc(sizeof(Domino_piece));

    piece_clone->orientation = VERTICAL;
    piece_clone->left_side.value = piece->left_side.value;
    piece_clone->left_side.other_box = &piece_clone->right_side;
    piece_clone->right_side.value = piece->right_side.value;
    piece_clone->right_side.other_box = &piece_clone->left_side;
    piece_clone->next = NULL;
    piece_clone->previous = NULL;

    if (side == LEFT_SIDE) piece_clone->downside = &piece_clone->left_side;
    if (side == RIGHT_SIDE) piece_clone->downside = &piece_clone->right_side;
    //TODO finish function
}

void append_piece(Domino_piece **table, Domino_piece *piece) {

    Domino_piece *piece_clone = (Domino_piece *) malloc(sizeof(Domino_piece));

    piece_clone->orientation = HORIZONTAL;
    piece_clone->left_side.value = piece->left_side.value;
    piece_clone->left_side.other_box = &piece_clone->right_side;
    piece_clone->right_side.value = piece->right_side.value;
    piece_clone->right_side.other_box = &piece_clone->left_side;
    piece_clone->next = NULL;
    piece_clone->previous = NULL;
    piece_clone->downside = NULL;

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

    piece_clone->orientation = HORIZONTAL;
    piece_clone->left_side.value = piece->left_side.value;
    piece_clone->left_side.other_box = &piece_clone->right_side;
    piece_clone->right_side.value = piece->right_side.value;
    piece_clone->right_side.other_box = &piece_clone->left_side;
    piece_clone->next = NULL;
    piece_clone->previous = NULL;
    piece_clone->downside = NULL;

    if (*table != NULL) {
        (*table)->previous = piece_clone;
    }
    *table = piece_clone;
    //printf("DEBUG: Prepended piece: %d|%d\n", piece_clone->left_side, piece_clone->right_side);
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

        new_node->left_side.value = possible_pieces[random_number][0];
        new_node->right_side.value = possible_pieces[random_number][1];
        new_node->next = NULL;
        new_node->previous = NULL;
        new_node->downside = NULL;

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

//checks if the side of the domino piece given as parameter corresponds to the side the player want to put the piece
//side must be equal to table->left_side or table->right_side
int check_move(Domino_piece *piece, Domino_piece *table, int side) {

    if (table == NULL) {
        printf("check_move: table is empty.\n");
        exit(EXIT_FAILURE);
    }

    // Controlla il lato destro del tavolo
    if (side == RIGHT_SIDE) {

        Domino_piece *last_table_node = get_last_table_piece(table);

        //printf("DEBUG: Table right piece %d|%d", last_table_node->left_side, last_table_node->right_side);
        //printf(" with player piece: %d|%d\n", current_node->left_side, current_node->right_side);
        //printf("DEBUG: Checking player number %d with table number %d\n", current_node->left_side, table->right_side);

        if (last_table_node->right_side.value == piece->left_side.value) {
            return MOVE_ALLOWED;
        } else if (last_table_node->right_side.value != piece->left_side.value) {
            return MOVE_NOT_ALLOWED;
        } else exit(EXIT_FAILURE);

    } else if (side == LEFT_SIDE) { //controlla il lato sinistro del tavolo

        //printf("DEBUG: Checking player piece: %d|%d", current_node->left_side, current_node->right_side);
        //printf(" with table piece %d|%d\n", table->left_side, table->right_side);
        //printf("DEBUG: Checking player number %d with table number %d\n", current_node->right_side, table->left_side);

        if (table->left_side.value == piece->right_side.value) {
            return MOVE_ALLOWED;
        } else if (table->left_side.value != piece->right_side.value) {
            return MOVE_NOT_ALLOWED;
        } else exit(33);

    }

    printf("Invalid side\n");
    return MOVE_NOT_ALLOWED;
}

void use_piece(Domino_piece *piece, Domino_piece **table, int side) {

    //printf("DEBUG: Piece being used: %d|%d\n", piece->left_side, piece->right_side);
    if (*table == NULL) {
        append_piece(table, piece);
    } else {
        // Check if the move is allowed
        if (check_move(piece, *table, side)) {
            if (side == RIGHT_SIDE) {
                append_piece(table, piece);
            } else if (side == LEFT_SIDE) {
                prepend_piece(table, piece);
            } else {
                printf("Side neither LEFT_SIDE nor RIGHT_SIDE\n");
                exit(EXIT_FAILURE);
            }
        } else {
            //printf("Move not allowed.\n");
            return;
        }
    }

    // Remove used piece from player
    if (piece->previous != NULL && piece->next != NULL) {
        piece->previous->next = piece->next;
        piece->next->previous = piece->previous;
    } else if (piece->previous != NULL) {
        piece->previous->next = NULL;
    } else if (piece->next != NULL) {
        piece->next->previous = NULL;
    }
}

void singleplayer(int pieces, Domino_piece *table) {
    Player player = create_player();
    assign_pieces(&player, pieces);

    while (player.first_piece != NULL) {

        printf("\nYour pieces:\n");
        print_player(&player);

        printf("Which piece do you want to place?\n");
        printf("Press 0 to quit if you can't place any piece\n");
        int piece;
        scanf("%d", &piece);
        if (piece == 0) {
            printf("Match ended, score is %d", calculate_score(table));
            exit(EXIT_SUCCESS);
        }
        Domino_piece *used_piece = get_player_piece(&player, piece);

        //append first piece
        if (table == NULL) {
            use_piece(used_piece, &table, RIGHT_SIDE);
            //now the table should NOT be NULL
            print_table(table); //table now is null
            continue;
        } else { //append / prepend next piece
            printf("Where do you want to place it? (Left :0, Right: 1)\n");
            int side;
            scanf("%d", &side);

            if (side == LEFT_SIDE) {
                //printf("DEBUG: Using piece on the left side...\n");
                use_piece(used_piece, &table, LEFT_SIDE);
            } else if (side == RIGHT_SIDE) {
                //printf("DEBUG: Using piece on the right side...\n");
                use_piece(used_piece, &table, RIGHT_SIDE);
            } else {
                printf("Invalid side. Please choose 0 for left or 1 for right.\n");
                continue;  // Add this line to continue the loop
            }
            //printf("DEBUG: After using piece...\n");
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
            autocomplete_stupid(&bot, table, pieces);
            break;
        }
        default:
            printf("Invalid game mode. Please choose 1 for singleplayer or 2 for CPU mode.\n");
            init_game();
    }
    free(table);
}