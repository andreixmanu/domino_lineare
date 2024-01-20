//
// Created by andreixmanu on 25/10/23.
//

#include "include/view_menu.h"
#include "include/game.h"
#include "include/print.h"
#include <stdio.h>
#include "include/2D_gamemode.h"
#include <stdlib.h>
#include "include/challenge.h"

void flush_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void view_menu() {
    int option;
    clear_screen();
    while (1) {  // Infinite loop until a valid option is selected
        printf("Welcome to Domino Lineare!\n");
        printf("\t1. Play\n");
        printf("\t2. Rules\n");
        printf("\t3. Exit\n");
        printf("\nChoose an option:");
        do{ scanf(" %d", &option); }
        while(option < 1 || option > 4);

        clear_screen();
        switch (option) {
            case 1:
                printf("Select gamemode:\n"
                       "\t1. Linear Domino\n"
                       "\t2. 2D Domino\n"
                       "\t3. Puzzle\n");

                int gamemode;
                scanf("%d", &gamemode);
                if (gamemode == 1) {
                    init_game();
                    return;  // Break out of the loop after a valid option
                } else if(gamemode == 2){
                    not_linear_domino();
                    return;  // Break out of the loop after a valid option
                } else if(gamemode == 3){
                    challenge_main();
                    break;
                } else{
                    printf("Please insert a valid number (1-3)\n");
                    view_menu();
                }
            case 2:
                print_rules();
                return;  // Break out of the loop after a valid option
            case 3:
                exit(EXIT_SUCCESS);
            case 4:{
                int challenge = 1;
                scanf("%d", &challenge);
                end_challenge(challenge);
                break;
            }
            default:
                printf("Invalid option\n\n");
                flush_input_buffer();
                break;
        }
    }
}
