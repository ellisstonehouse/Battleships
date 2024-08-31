
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#include "game.h"
#include "playGame.h"
#include "initGame.h"
#include "aiMoves.h"

#define TESTING_RANDOM 0
#define RANDOM_SHOOTING 1
#define HUNT 2
#define HUNT_PARITY 3
#define PROB_DENSITY 4


int* aiMove(Board* board, int mode) {

  switch (mode) {

  case RANDOM_SHOOTING:
    return randomShooting(board);
  
  case HUNT:
    return hunt(board);
  
  case HUNT_PARITY:
    return huntParity(board);
  
  case PROB_DENSITY:
    return probabilityDensity(board);
  
  default:
    break;
  }
}

int* randomShooting(Board* board) {
  static int move[2];
  int x, y;

  while(true) {

      srand((unsigned int)clock()); // only use clock when testing
      // srand(time(0));

      x = rand() % board->boardSize;
      y = rand() % board->boardSize;

      if (board->grid[x][y] == '*') {
        printf("ERROR! Incorrect coordinates\n");
        continue;
      }
      else {
        board->grid[x][y] = '*';
      }

      break;
    }

    move[0] = x;
    move[1] = y;

    return move;
}



int* hunt(Board* board) {
}

int* huntParity(Board* board) {
}

int* probabilityDensity(Board* board) {
}