//
// Created by manua on 04/12/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "../include/2D_gamemode.h"
#include "../include/2D_print.h"
#include <ctype.h>

#define MOVE_ALLOWED 1
#define MOVE_NOT_ALLOWED 0
#define LEFT_SIDE 1
#define RIGHT_SIDE 2
#define HORIZONTAL 1
#define VERTICAL 2

Piece EMPTY_PIECE = {-1, -1};
int rows = 1;

int calculate_score_2D(Piece **table) {
    int score = 0;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (table[i][j].left_side == -1 && table[i][j].right_side == -1) {
                continue;
            }
            if (table[i][j].left_side == -1 && table[i][j].right_side != -1) {
                score += table[i][j].right_side;
                continue;
            }
            if (table[i][j].left_side != -1 && table[i][j].right_side == -1) {
                score += table[i][j].left_side;
                continue;
            }
            score += table[i][j].left_side + table[i][j].right_side;
        }
    }
    return score;
}

void assign_pieces_2D(Piece *player, int n) {
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

        player[i].left_side = possible_pieces[random_number][0];
        player[i].right_side = possible_pieces[random_number][1];
    }
}

int first_piece_2D(Piece *row, int cols) {
    for (int i = 0; i < cols; i++) {
        if (!(row[i].left_side == -1 && row[i].right_side == -1)) {
            return i;
        }
    }
    return -1;
}

int last_piece_2d(Piece *row, int cols) {
    for (int i = cols - 1; i >= 0; --i) {
        if (!(row[i].left_side == -1 && row[i].right_side == -1)) {
            return i;
        }
    }
    return -1;
}

Piece *create_player_2D(size_t n) {
    Piece *player = malloc(n * sizeof(Piece));
    if (player == NULL) {
        printf("DEBUG: Memory allocation failed.\n");
        exit(1);
    }
    return player;
}

int check_empty_player(Piece *player, int n) {
    for (int i = 0; i < n; i++) {
        if (player[i].left_side != -1 && player[i].right_side != -1) {
            return 0;
        }
    }
    return 1;
}

//TODO check for border test cases
//TODO implement double vertical piece check
int check_move_2D(Piece **table, Piece *piece, int side, int row) {
    if (side == RIGHT_SIDE) {
        int last_valid_index = last_piece_2d(table[row], 20);
        if (table[row][last_valid_index].right_side == -1 && table[row][last_valid_index].left_side != -1) {
            if (table[row][last_valid_index].left_side == piece->left_side) {
                return MOVE_ALLOWED;
            } else return MOVE_NOT_ALLOWED;
        }
        if (table[row][last_valid_index].right_side == piece->left_side) {
            return MOVE_ALLOWED;
        }
    }
    if (side == LEFT_SIDE) {
        int first_valid_index = first_piece_2D(table[row], 20);
        if (table[row][first_valid_index].right_side != -1 && table[row][first_valid_index].left_side == -1) {
            if (table[row][first_valid_index].right_side == piece->right_side) {
                return MOVE_ALLOWED;
            } else return MOVE_NOT_ALLOWED;
        }
        if (table[row][first_valid_index].left_side == piece->right_side) {
            return MOVE_ALLOWED;
        }
    }
    return MOVE_NOT_ALLOWED;
}

int pick_piece_index(Piece *player, int player_size, int pickedIndex) {
    int result_index = 0;
    for (int i = 0; i < player_size; i++) {
        if (player[i].left_side == -1 && player[i].right_side == -1) {
            continue;
        }
        if (result_index == pickedIndex) {
            return i;
        }
        result_index++;
    }
    return -1;
}

void use_piece_2D(Piece **table, Piece *player, int piece, int side, int *player_size, int orientation, int row) {

    if (orientation == HORIZONTAL) {
        int picked_piece_index = pick_piece_index(player, *player_size, piece);

        if (picked_piece_index == -1) {
            printf("Invalid piece. It's an empty piece or pickedIndex is out of range.\n");
            return;
        }

        Piece selected_piece = player[picked_piece_index];

        //populate first piece of the table
        if (table[0][10].left_side == -1 && table[0][10].right_side == -1) {
            table[0][10] = selected_piece;
            remove_piece_2D(player, player_size, picked_piece_index);
            return;
        }

        //get the pieces indexes
        int first_valid_index = first_piece_2D(table[0], 20);
        int last_valid_index = last_piece_2d(table[0], 20);

        if (side == LEFT_SIDE && first_valid_index != -1) {
            if (check_move_2D(table, &selected_piece, LEFT_SIDE, row)) {
                table[row][first_valid_index - 1] = selected_piece;
                remove_piece_2D(player, player_size, picked_piece_index);
                return;
            }
        }

        if (side == RIGHT_SIDE && last_valid_index != -1) {
            if (check_move_2D(table, &selected_piece, RIGHT_SIDE, row)) {
                table[row][last_valid_index + 1] = selected_piece;
                remove_piece_2D(player, player_size, picked_piece_index);
                return;
            }
        }
        printf("Invalid move.\n");
    }
    if (orientation == VERTICAL) {
        int picked_piece_index = pick_piece_index(player, *player_size, piece);

        if (picked_piece_index == -1) {
            printf("Invalid piece. It's an empty piece or pickedIndex is out of range.\n");
            return;
        }

        Piece selected_piece = player[picked_piece_index];

        //populate first piece of the table
        if (table[0][10].left_side == -1 && table[0][10].right_side == -1) {
            table[0][10].left_side = selected_piece.left_side;
            table[0][10].right_side = -1;
            table[1][10].left_side = -1;
            table[1][10].right_side = selected_piece.right_side;
            remove_piece_2D(player, player_size, picked_piece_index);
            return;
        }

        //get the pieces indexes
        int first_valid_index = first_piece_2D(table[0], 20);
        int last_valid_index = last_piece_2d(table[0], 20);

        if (side == LEFT_SIDE && first_valid_index != -1) {
            if (check_move_2D(table, &selected_piece, LEFT_SIDE, row)) {
                table[row][first_valid_index - 1].left_side = -1;
                table[row][first_valid_index - 1].right_side = selected_piece.right_side;
                table[row + 1][first_valid_index - 1].left_side = selected_piece.left_side;
                table[row + 1][first_valid_index - 1].right_side = -1;
                remove_piece_2D(player, player_size, picked_piece_index);
                if (row == rows - 1) rows++;
                return;
            }
        }
        if (side == RIGHT_SIDE && last_valid_index != -1) {
            if (check_move_2D(table, &selected_piece, RIGHT_SIDE, row)) {
                table[row][last_valid_index + 1].left_side = selected_piece.left_side;
                table[row][last_valid_index + 1].right_side = -1;
                table[row + 1][last_valid_index + 1].left_side = -1;
                table[row + 1][last_valid_index + 1].right_side = selected_piece.right_side;
                remove_piece_2D(player, player_size, picked_piece_index);
                if (row == rows - 1) rows++;
                return;
            }
        }
        printf("Invalid move.\n");
    }
}

void remove_piece_2D(Piece *player, int *size, int index) {
    if (index < 0 || index >= *size) return;
    for (int i = index; i < *size - 1; i++) player[i] = player[i + 1];
    (*size)--;
}

void switch_values_2D(Piece *player, int player_size) {
    printf("What piece do you want to switch?\n");
    int option;
    scanf("%d", &option);
    int index = pick_piece_index(player, player_size, option - 1);  // -1 if option is 1-based
    if (index == -1) {
        printf("Invalid option.\n");
        return;
    }
    int temp = player[index].left_side;
    player[index].left_side = player[index].right_side;
    player[index].right_side = temp;
}

void singleplayer_2D(Piece **table, int *pieces) {
    Piece *player = create_player_2D(*pieces);
    assign_pieces_2D(player, *pieces);

    //first piece
    printf("Player's pieces:\n");
    print_player_2D(player, *pieces);

    printf("Choose the first piece to play:\n");
    int piece;
    scanf("%d", &piece);

    use_piece_2D(table, player, piece - 1, 0, pieces, HORIZONTAL, rows - 1);

    printf("\t\t\t\t\t\t\t\t\t\t\t\t {Table}\n");
    print_table_2D(table, rows);

    //BEGIN GAME LOOP
    while (!check_empty_player(player, *pieces)) {

        int row = 1;

        printf("Player's pieces:\n");
        print_player_2D(player, *pieces);

        printf("Choose a piece to play:\n"
               "Press 0 to quit if you can't place any piece\n"
               "Press s to switch two pieces' values\n");
        char piece2;
        scanf(" %c", &piece2);

        if (piece2 == '0') {
            printf("Score is: %d\n", calculate_score_2D(table));
            exit(0);
        }

        if (piece2 == 's') {
            switch_values_2D(player, *pieces);
            continue;
        }

        printf("Do you want to place it vertically or horizontally?\n");
        printf("1. Horizontal\n"
               "2. Vertical\n");
        int orientation2;
        scanf("%d", &orientation2);

        printf("Choose a side to play:\n");
        printf("1. Left\n"
               "2. Right\n");
        int side;
        scanf("%d", &side);

        if (rows > 1) {
            printf("On  which row do you want to place it? (1 - %d)\n", rows);
            scanf("%d", &row);
        }

        //cast piece2 to an integer
        if (isdigit(piece2)) {
            int num_piece = piece2 - '0';
            use_piece_2D(table, player, num_piece - 1, side, pieces, orientation2, row - 1);
            printf("\t\t\t\t\t\t\t\t\t\t\t\t {Table}\n");
            print_table_2D(table, rows);
            continue;
        }
        printf("ERROR YOU SHOULD NOT BE HERE\n");
    }

    printf("Game over! Score is: %d", calculate_score_2D(table));

    exit(0);
}

Piece **create_matrix() {
    Piece **matrix = malloc(20 * sizeof(Piece *));
    if (matrix == NULL) {
        // Handle memory allocation failure
        exit(1);
    }
    for (size_t i = 0; i < 20; i++) {
        matrix[i] = malloc(20 * sizeof(Piece));
        if (matrix[i] == NULL) {
            exit(1);
        }
        for (size_t j = 0; j < 20; j++) {
            matrix[i][j] = EMPTY_PIECE; // initialize all locations to empty
        }
    }
    return matrix;
}

void not_linear_domino() {
    Piece **matrix = create_matrix();
    printf("Welcome to (not) Linear Domino!\n");
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
            singleplayer_2D(matrix, &pieces);
            break;
        case 2: // CPU mode
            printf("CPU mode\n");
            break;
        default:
            printf("Invalid game mode. Please choose 1 for singleplayer or 2 for CPU mode.\n");
            not_linear_domino();
    }
}