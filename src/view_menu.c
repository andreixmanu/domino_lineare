//
// Created by andreixmanu on 25/10/23.
//

#include "../include/view_menu.h"
#include "../include/game.h"
#include "../include/print.h"
#include <stdio.h>
#include "../include/main.h"

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
            printf("Play\n");
            //initiate game
            init_game();
            break;
        case 2:
            printf("Rules\n");
            print_rules();
            break;
        case 3:
            printf("Exit\n");
            return;
        default:
            printf("Invalid option\n");
            view_menu();
            break;
    }
}