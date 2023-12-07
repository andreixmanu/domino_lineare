#include <stdio.h>
#include <stdlib.h>
#include "../include/view_menu.h"
#include "../include/print.h"
#include "../include/game.h"
#include <stdbool.h>
#include "../include/main.h"
#include <time.h>

//either side has a number from 0 to 6

int main(){
    setbuf(stdout, NULL); //disable stdout buffering for debug reasons
    //create a 2d array of 10x10 with malloc
    Domino_piece **matrix = (Domino_piece **) malloc(10 * sizeof(Domino_piece *));
    srand(time(NULL));
    view_menu();
    return 0;
}
