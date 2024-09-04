
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "initGame.h"
#include "playGame.h"


int main( int argc, char *argv[] ) {

  int mode;

  printf(
    "\n 0 - TEST | 1 - Random | 2 - Hunt | 3 - Hunt Parity | 4 - Main Algo\n\n"
    "Select a mode: ");

  if (!scanf(" %d", &mode)) {
    return 0;
  }

  // creates pointer for game structure
  Game *game = initGame(mode); 

  playGame(game);

  freeGame(game);

  return 0;
}

