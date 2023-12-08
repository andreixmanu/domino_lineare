//
// Created by andreixmanu on 25/10/23.
//

#include "include/view_menu.h"
#include "include/game.h"
#include "include/print.h"
#include <stdio.h>
#include "include/2D_gamemode.h"
#include <stdlib.h>

void view_menu() {

    int option = 0;

    printf("Welcome to Domino Lineare!\n");
    printf("1. Play\n");
    printf("2. Rules\n");
    printf("3. Exit\n");
    printf("Choose an option: ");
    scanf("%d", &option);

    switch (option) {
        case 1:
            printf("Select gamemode:\n"
                   "Linear Domino\n"
                   "2D Domino\n");
            int gamemode;
            scanf("%d", &gamemode);
            (gamemode == 1) ? init_game() : not_linear_domino();
            break;
        case 2:
            //printf("Rules\n");
            print_rules();
            break;
        case 3:
            //printf("Exit\n");
            exit(EXIT_SUCCESS);
        default:
            printf("Invalid option\n");
            view_menu();
            break;
    }
}