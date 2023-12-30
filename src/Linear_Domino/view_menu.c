//
// Created by andreixmanu on 25/10/23.
//

#include "include/view_menu.h"
#include "include/game.h"
#include "include/print.h"
#include <stdio.h>
#include "include/2D_gamemode.h"
#include <stdlib.h>

void flush_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void view_menu() {
    int option;

    while (1) {  // Infinite loop until a valid option is selected
        printf("Welcome to Domino Lineare!\n");
        printf("\t1. Play\n");
        printf("\t2. Rules\n");
        printf("\t3. Exit\n");
        printf("Choose an option: \n");
        scanf(" %d", &option);

        switch (option) {
            case 1:
                printf("Select gamemode:\n"
                       "\t1. Linear Domino\n"
                       "\t2. 2D Domino\n");
                int gamemode;
                scanf("%d", &gamemode);
                if (gamemode == 1) {
                    init_game();
                    return;  // Break out of the loop after a valid option
                } else {
                    not_linear_domino();
                    return;  // Break out of the loop after a valid option
                }
            case 2:
                print_rules();
                return;  // Break out of the loop after a valid option
            case 3:
                exit(EXIT_SUCCESS);
            default:
                printf("Invalid option\n\n");
                flush_input_buffer();
                break;
        }
    }
}
