
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

  case TESTING_RANDOM:
    return randomShooting(board);

  case RANDOM_SHOOTING:
    return randomShooting(board);
  
  case HUNT:
    return hunt(board);
  
  case HUNT_PARITY:
    return huntParity(board);
  
  case PROB_DENSITY:
    return probabilityDensity(board);
  
  default:
    return randomShooting(board);
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

      if (board->grid[x][y] == '*' || board->grid[x][y] == 'x') {
        continue;
      }
      else if (board->grid[x][y] == '.') {
        board->grid[x][y] = 'x';
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

  static int move[2];

  for (int x = 0; x < board->boardSize; x++) {
    for (int y = 0; y < board->boardSize; y++) {

        if (board->grid[x][y] == '*') {
          // Above HIT
          if (0 <= x-1 && board->grid[x-1][y] == '.') {
            move[0] = x-1; move[1] = y;
            return move;
          }
          // Below HIT
          if (x+1 < board->boardSize && board->grid[x+1][y] == '.') {
            move[0] = x+1; move[1] = y;
            return move;
          }
          // Right of HIT
          if (y+1 < board->boardSize && board->grid[x][y+1] == '.') {
            move[0] = x; move[1] = y+1;
            return move;
          }
          // Left of HIT
          if (0 <= y-1 && board->grid[x][y-1] == '.') {
            move[0] = x; move[1] = y-1;
            return move;
          }
        }

    }
  }


  return randomShooting(board);
}

int* huntParity(Board* board) {

  return randomShooting(board);
}

int* probabilityDensity(Board* board) {
  
  return randomShooting(board);
}