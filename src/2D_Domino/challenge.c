#include <stdio.h>
#include "include/2D_print.h"
#include "include/main.h"
#include "include/2D_gamemode.h"
#include <ctype.h>
#include "include/view_menu.h"
#include <stdlib.h>


#define CHALLENGE_1_MAX_SCORE 34
#define CHALLENGE_2_MAX_SCORE 49
#define CHALLENGE_3_MAX_SCORE 77
#define CHALLENGE_4_MAX_SCORE 38

#define LEFT_SIDE 1
#define RIGHT_SIDE 2

int rows_ = 1;

int challenge_1_complete = 0;
int challenge_2_complete = 0;
int challenge_3_complete = 0;

void
use_piece_2D_challenge(Piece **table, Piece *player, int piece, int side, int *player_size, int orientation, int row) {

    if (orientation == HORIZONTAL) {
        int picked_piece_index = pick_piece_index(player, *player_size, piece);

        if (picked_piece_index == -1) {
            printf("Invalid piece. It's an empty piece or pickedIndex is out of range.\n");
            return;
        }

        Piece selected_piece = player[picked_piece_index];

        //get the pieces indexes
        int first_valid_index = first_piece_2D(table[row], 20);
        int last_valid_index = last_piece_2d(table[row], 20);

        if (side == LEFT_SIDE && first_valid_index != -1) {

            Piece *table_piece = &table[row][first_valid_index];

            if (check_move_2D(table_piece, &selected_piece, LEFT_SIDE)) {
                table[row][first_valid_index - 1] = selected_piece;
                remove_piece_2D(player, player_size, picked_piece_index);
                return;
            }
        }

        if (side == RIGHT_SIDE && last_valid_index != -1) {

            Piece *table_piece = &table[row][last_valid_index];

            if (check_move_2D(table_piece, &selected_piece, RIGHT_SIDE)) {
                table[row][last_valid_index + 1] = selected_piece;
                remove_piece_2D(player, player_size, picked_piece_index);
                return;
            }
        }
        printf("Invalid move.\n");
    } else if (orientation == VERTICAL) {
        int picked_piece_index = pick_piece_index(player, *player_size, piece);

        if (picked_piece_index == -1) {
            printf("Invalid piece. It's an empty piece or pickedIndex is out of range.\n");
            return;
        }

        Piece selected_piece = player[picked_piece_index];

        //get the pieces indexes
        int first_valid_index = first_piece_2D(table[row], 20);
        int last_valid_index = last_piece_2d(table[row], 20);

        if (side == LEFT_SIDE && first_valid_index != -1) {

            Piece *table_piece = &table[row][first_valid_index];

            if (check_move_2D(table_piece, &selected_piece, LEFT_SIDE)) {
                table[row][first_valid_index - 1].left_side = -1;
                table[row][first_valid_index - 1].right_side = selected_piece.right_side;
                table[row + 1][first_valid_index - 1].left_side = selected_piece.left_side;
                table[row + 1][first_valid_index - 1].right_side = -1;
                remove_piece_2D(player, player_size, picked_piece_index);
                if (row == rows_ - 1) rows_++;
                return;
            }
        }

        if (side == RIGHT_SIDE && last_valid_index != -1) {

            Piece *table_piece = &table[row][last_valid_index];

            if (check_move_2D(table_piece, &selected_piece, RIGHT_SIDE)) {
                table[row][last_valid_index + 1].left_side = selected_piece.left_side;
                table[row][last_valid_index + 1].right_side = -1;
                table[row + 1][last_valid_index + 1].left_side = -1;
                table[row + 1][last_valid_index + 1].right_side = selected_piece.right_side;
                remove_piece_2D(player, player_size, picked_piece_index);
                if (row == rows_ - 1) rows_++;
                return;
            }
        }
        printf("Invalid move.\n");
    }
}

void end_challenge(int n_challenge){
    switch(n_challenge){
        case 1:
            challenge_1_complete = 1;
            break;
        case 2:
            challenge_2_complete = 1;
            break;
        case 3:
            challenge_3_complete = 1;
            break;
        default:
            printf("n_challenge not valid\n");
    }
    if(challenge_1_complete && challenge_2_complete && challenge_3_complete)
        printf("You unlocked the extra difficulty!\n\n");

    printf("Congratulations, you beat challenge %d!\n"
           "Do you want to play again?\n", n_challenge);
    char option_ = 'n';
    do { scanf(" %c", &option_); }
    while (option_ != 'y' && option_ != 'n');
    if (option_ == 'y' || option_ == 'Y') view_menu();
    else exit(0);
}

void challenge_1() {
    clear_screen();
    printf("In this challenge you need to reach exactly %d points", CHALLENGE_1_MAX_SCORE);

    int player_pieces = 3, score;
    int *pieces = &player_pieces;
    //build table
    Piece **table = create_matrix();
    table[0][10].left_side = 3;
    table[0][10].right_side = 4;
    table[0][11].left_side = 4;
    table[0][11].right_side = 1;
    table[0][9].left_side = 1;
    table[0][9].right_side = 3;
    printf("\nTable:\n");
    print_table_2D(table, rows_);

    //build player
    Piece *player = create_player_2D(player_pieces);
    player[0].left_side = 1;
    player[0].right_side = 1;
    player[1].left_side = 1;
    player[1].right_side = 5;
    player[2].left_side = 5;
    player[2].right_side = 5;

    while (!check_empty_player(player, *pieces)) {

        int row = 1;
        printf("Choose a piece to play:\n"
               "Press 0 to quit if you can't place any piece\n"
               "Press s to switch two pieces' values\n");
        print_player_2D(player, *pieces);
        char piece;
        scanf(" %c", &piece);

        if (piece == 's') {
            switch_values_2D(player, *pieces);
            print_table_2D(table, rows_);
            continue;
        } else if (piece - 48 > 3) {
            printf("Invalid piece. Please choose a piece between 1 and %d\n", *pieces);
            flush_input_buffer();
            continue;
        } else if (piece == '0') {
            printf("You surrendered.\n");
            printf("Do you want to retry?(y/n)\n");
            char option = 'n';
            scanf(" %c", &option);
            if (option == 'y' || option == 'Y') {
                rows_ = 1;
                challenge_1();
            } else exit(0);
        }

        printf("Do you want to place it vertically or horizontally?\n");
        printf("\t1. Horizontal\n"
               "\t2. Vertical\n");
        int orientation;
        do { scanf("%d", &orientation); }
        while (orientation != 1 && orientation != 2);

        printf("Choose a side to play:\n");
        printf("\t1. Left\n"
               "\t2. Right\n");
        int side;
        scanf("%d", &side);

        if (rows_ > 1) {
            printf("On  which row do you want to place it? (1 - %d)\n", rows_);
            scanf("%d", &row);
        }

        //cast piece to an integer
        if (isdigit(piece)) {
            int num_piece = piece - '0';
            use_piece_2D_challenge(table, player, num_piece - 1, side, pieces, orientation, row - 1);
            clear_screen();
            printf("Table:\n");
            //print_table_2D(table, rows);
            print_table_2D(table, rows_);
        }
        score = calculate_score_2D(table);
        if (score == CHALLENGE_1_MAX_SCORE) {
            end_challenge(1);
        }
    }
}

void challenge_2() {
    clear_screen();
    rows_ = 2;
    printf("In this challenge you need to reach exactly %d points.\n", CHALLENGE_2_MAX_SCORE);

    int player_pieces = 5, score;
    int *pieces = &player_pieces;
    //build table
    Piece **table = create_matrix();
    table[0][10].left_side = 5;
    table[0][10].right_side = 1;
    table[0][11].left_side = 1;
    table[0][11].right_side = 5;
    table[0][9].left_side = -1;
    table[0][9].right_side = 5;
    table[0][8].left_side = 3;
    table[0][8].right_side = 5;
    table[1][9].left_side = 3;
    table[1][9].right_side = -1;
    printf("\nTable:\n");
    print_table_2D(table, rows_);

    //build player
    Piece *player = create_player_2D(player_pieces);
    player[0].left_side = 2;
    player[0].right_side = 6;
    player[1].left_side = 3;
    player[1].right_side = 5;
    player[2].left_side = 1;
    player[2].right_side = 1;
    player[3].left_side = 2;
    player[3].right_side = 3;
    player[4].left_side = 2;
    player[4].right_side = 4;

    while (!check_empty_player(player, *pieces)) {

        int row = 1;
        printf("Choose a piece to play:\n"
               "Press 0 to quit if you can't place any piece\n"
               "Press s to switch two pieces' values\n");
        print_player_2D(player, *pieces);
        char piece;
        scanf(" %c", &piece);

        if (piece == 's') {
            switch_values_2D(player, *pieces);
            print_table_2D(table, rows_);
            continue;
        } else if (piece - 48 > *pieces) {
            printf("Invalid piece. Please choose a piece between 1 and %d\n", *pieces);
            flush_input_buffer();
            continue;
        } else if (piece == '0') {
            printf("You surrendered.\n");
            printf("Do you want to retry?(y/n)\n");
            char option = 'n';
            scanf(" %c", &option);
            if (option == 'y' || option == 'Y') {
                rows_ = 2;
                challenge_2();
            } else exit(0);
        }

        printf("Do you want to place it vertically or horizontally?\n");
        printf("\t1. Horizontal\n"
               "\t2. Vertical\n");
        int orientation;
        do { scanf("%d", &orientation); }
        while (orientation != 1 && orientation != 2);

        printf("Choose a side to play:\n");
        printf("\t1. Left\n"
               "\t2. Right\n");
        int side;
        scanf("%d", &side);

        if (rows_ > 1) {
            printf("On  which row do you want to place it? (1 - %d)\n", rows_);
            scanf("%d", &row);
        }

        //cast piece to an integer
        if (isdigit(piece)) {
            int num_piece = piece - '0';
            use_piece_2D_challenge(table, player, num_piece - 1, side, pieces, orientation, row - 1);
            clear_screen();
            printf("Table:\n");
            //print_table_2D(table, rows);
            print_table_2D(table, rows_);
        }
        score = calculate_score_2D(table);
        if (score == CHALLENGE_2_MAX_SCORE) {
            end_challenge(2);
        }
    }
}

void challenge_3() {
    clear_screen();
    rows_ = 2;
    printf("In this challenge you need to reach exactly %d points.\n", CHALLENGE_3_MAX_SCORE);

    int player_pieces = 7, score;
    int *pieces = &player_pieces;
    //build table
    Piece **table = create_matrix();
    table[0][10].left_side = 3;
    table[0][10].right_side = 3;
    table[0][11].left_side = 3;
    table[0][11].right_side = 4;
    table[0][12].left_side = 4;
    table[0][12].right_side = -1;
    table[0][9].left_side = 4;
    table[0][9].right_side = 3;
    table[0][8].left_side = -1;
    table[0][8].right_side = 4;
    table[1][8].left_side = 4;
    table[1][8].right_side = -1;
    table[1][9].left_side = 4;
    table[1][9].right_side = 3;
    table[1][11].left_side = 3;
    table[1][11].right_side = 4;
    table[1][12].left_side = -1;
    table[1][12].right_side = 4;
    printf("\nTable:\n");
    print_table_2D(table, rows_);

    //build player
    Piece *player = create_player_2D(player_pieces);
    player[0].left_side = 3;
    player[0].right_side = 4;
    player[1].left_side = 1;
    player[1].right_side = 5;
    player[2].left_side = 4;
    player[2].right_side = 5;
    player[3].left_side = 2;
    player[3].right_side = 4;
    player[4].left_side = 1;
    player[4].right_side = 4;
    player[5].left_side = 2;
    player[5].right_side = 4;
    player[6].left_side = 3;
    player[6].right_side = 3;

    while (!check_empty_player(player, *pieces)) {

        int row = 1;
        printf("Choose a piece to play:\n"
               "Press 0 to quit if you can't place any piece\n"
               "Press s to switch two pieces' values\n");
        print_player_2D(player, *pieces);
        char piece;
        scanf(" %c", &piece);

        if (piece == 's') {
            switch_values_2D(player, *pieces);
            print_table_2D(table, rows_);
            continue;
        } else if (piece - 48 > *pieces) {
            printf("Invalid piece. Please choose a piece between 1 and %d\n", *pieces);
            flush_input_buffer();
            continue;
        } else if (piece == '0') {
            printf("You surrendered.\n");
            printf("Do you want to retry?(y/n)\n");
            char option = 'n';
            scanf(" %c", &option);
            if (option == 'y' || option == 'Y') {
                rows_ = 2;
                challenge_3();
            } else exit(0);
        }

        printf("Do you want to place it vertically or horizontally?\n");
        printf("\t1. Horizontal\n"
               "\t2. Vertical\n");
        int orientation;
        do { scanf("%d", &orientation); }
        while (orientation != 1 && orientation != 2);

        printf("Choose a side to play:\n");
        printf("\t1. Left\n"
               "\t2. Right\n");
        int side;
        scanf("%d", &side);

        if (rows_ > 1) {
            printf("On  which row do you want to place it? (1 - %d)\n", rows_);
            scanf("%d", &row);
        }

        //cast piece to an integer
        if (isdigit(piece)) {
            int num_piece = piece - '0';
            use_piece_2D_challenge(table, player, num_piece - 1, side, pieces, orientation, row - 1);
            clear_screen();
            printf("Table:\n");
            print_table_2D(table, rows_);
        }
        score = calculate_score_2D(table);
        if (score == CHALLENGE_3_MAX_SCORE) {
            end_challenge(3);
        }
    }
}

void challenge_4() {
    clear_screen();
    printf("In this challenge you need to reach exactly %d points.\n"
           "NOTE: in this challenge you can only place pieces vertically\n", CHALLENGE_4_MAX_SCORE);

    int player_pieces = 7, score;
    int *pieces = &player_pieces;
    //build table
    Piece **table = create_matrix();
    table[0][10].left_side = 1;
    table[0][10].right_side = 1;
    printf("\nTable:\n");
    print_table_2D(table, rows_);

    //build player
    Piece *player = create_player_2D(player_pieces);
    player[0].left_side = 1;
    player[0].right_side = 6;
    player[1].left_side = 4;
    player[1].right_side = 5;
    player[2].left_side = 1;
    player[2].right_side = 6;
    player[3].left_side = 2;
    player[3].right_side = 6;
    player[4].left_side = 1;
    player[4].right_side = 3;
    player[5].left_side = 3;
    player[5].right_side = 6;
    player[6].left_side = 3;
    player[6].right_side = 6;

    while (!check_empty_player(player, *pieces)) {

        int row = 1;
        printf("Choose a piece to play:\n"
               "Press 0 to quit if you can't place any piece\n"
               "Press s to switch two pieces' values\n");
        print_player_2D(player, *pieces);
        char piece;
        scanf(" %c", &piece);

        if (piece == 's') {
            switch_values_2D(player, *pieces);
            print_table_2D(table, rows_);
            continue;
        } else if (piece - 48 > *pieces) {
            printf("Invalid piece. Please choose a piece between 1 and %d\n", *pieces);
            flush_input_buffer();
            continue;
        } else if (piece == '0') {
            printf("You surrendered.\n");
            printf("Do you want to retry?(y/n)\n");
            char option = 'n';
            scanf(" %c", &option);
            if (option == 'y' || option == 'Y') {
                rows_ = 2;
                challenge_4();
            } else exit(0);
        }

        printf("Choose a side to play:\n");
        printf("\t1. Left\n"
               "\t2. Right\n");
        int side;
        scanf("%d", &side);

        if (rows_ > 1) {
            printf("On  which row do you want to place it? (1 - %d)\n", rows_);
            scanf("%d", &row);
        }

        //cast piece to an integer
        if (isdigit(piece)) {
            int num_piece = piece - '0';
            use_piece_2D_challenge(table, player, num_piece - 1, side, pieces, VERTICAL, row - 1);
            clear_screen();
            printf("Table:\n");
            print_table_2D(table, rows_);
        }
        score = calculate_score_2D(table);
        if (score == CHALLENGE_4_MAX_SCORE) {
            printf("Congratulations, you beat challenge 4!\n"
                   "Do you want to play again?\n");
            char option_ = 'n';
            do { scanf(" %c", &option_); }
            while (option_ != 'y' && option_ != 'n');
            if (option_ == 'y' || option_ == 'Y') view_menu();
            else exit(0);
        }
    }
}

void challenge_main() {
    clear_screen();
    if(challenge_1_complete && challenge_2_complete && challenge_3_complete){
        printf("In this Puzzle mode you have a set of given cards and table, you have to reach the given\n"
               "objective with your cards. You can place the pieces either horizontally or vertically.\n"
               "Choose a challenge to face:\n"
               "\t1. Easy\n"
               "\t2. Medium\n"
               "\t3. Difficult\n"
               "\t4. Extra\n");
        int option = 0;
        scanf(" %d", &option);
        if (option < 1 || option > 4) {
            printf("Please select a valid option.\n");
            challenge_main();
        }
        clear_screen();
        switch (option) {
            case 1:
                challenge_1();
                break;
            case 2:
                challenge_2();
                break;
            case 3:
                challenge_3();
                break;
            case 4:
                challenge_4();
                break;
            default:
                challenge_main();
        }
    } else {
        printf("In this Puzzle mode you have a set of given cards and table, you have to reach the given\n"
               "objective with your cards. You can place the pieces either horizontally or vertically.\n"
               "Choose a challenge to face:\n"
               "\t1. Easy\n"
               "\t2. Medium\n"
               "\t3. Difficult\n");
        int option = 0;
        scanf(" %d", &option);
        if (option < 1 || option > 3) {
            printf("Please select a valid option.\n");
            challenge_main();
        }
        clear_screen();
        switch (option) {
            case 1:
                challenge_1();
                break;
            case 2:
                challenge_2();
                break;
            case 3:
                challenge_3();
                break;
            default:
                challenge_main();
        }
    }

}