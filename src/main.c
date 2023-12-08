#include <stdio.h>
#include <stdlib.h>
#include "../include/view_menu.h"
#include "../include/print.h"
#include <time.h>

//either side has a number from 0 to 6

int main(){
    setbuf(stdout, NULL); //disable stdout buffering for debug reasons
    //create a 2d array of 10x10 with malloc
    srand(time(NULL));
    view_menu();
    return 0;
}
