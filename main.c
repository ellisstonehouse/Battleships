
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "initGame.h"
#include "playGame.h"


int main( int argc, char *argv[] ) {

  int algo, mode;

  if (argc == 2 && argv[2] == 0) {
    mode = 0;
    printf("\nTESTING MODE:");
  }
  else {
    mode = 1;
  }

  printf(
    "\n  1 - Random | 2 - Hunt | 3 - Hunt Parity | 4 - Main Algo\n\n"
    "Select a mode: ");

  if (scanf(" %d", &algo) != 1 || algo < 0 || 4 < algo) {
    printf("ERROR! Invalid mode.\n");
    clearInputBuffer();
    return 1;
  }

  srand(time(NULL)); // initialise random seed

  Game *game = initGame(algo, mode); 

  playGame(game);

  freeGame(game);

  return 0;
}

