#include "../include/print.h"
#include "../include/view_menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  setvbuf(stdout, NULL, _IONBF,
          0); // disable stdout buffering for debug reasons
  srand(time(NULL));
  view_menu();
  return 0;
}
