
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#include "game.h"
#include "playGame.h"
#include "initGame.h"
#include "aiMoves.h"


int* aiMove(Board* board, int mode) {

  switch (mode) {

    case RANDOM_SHOOTING:
      return randomShooting(board);
    
    case HUNT:
      return huntTarget(board);
    
    case HUNT_PARITY:
      return huntTarget_parity(board);
    
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

    x = rand() % board->boardSize;
    y = rand() % board->boardSize;

    if (board->grid[x][y] == '*' || board->grid[x][y] == 'x' || board->grid[x][y] == '#') {
      continue;
    }

    break;
  }

  move[0] = x; move[1] = y;

  return move;
}



int* huntTarget(Board* board) {

  static int move[2];

  for (int x = 0; x < board->boardSize; x++) {
    for (int y = 0; y < board->boardSize; y++) {

        if (board->grid[x][y] == '*') {
          // Above HIT
          if (0 <= x-1 && board->grid[x-1][y] != '*' && board->grid[x-1][y] != 'x' && board->grid[x-1][y] != '#') {
            move[0] = x-1; move[1] = y;
            return move;
          }
          // Below HIT
          if (x+1 < board->boardSize && board->grid[x+1][y] != '*' && board->grid[x+1][y] != 'x' && board->grid[x+1][y] != '#') {
            move[0] = x+1; move[1] = y;
            return move;
          }
          // Right of HIT
          if (y+1 < board->boardSize && board->grid[x][y+1] != '*' && board->grid[x][y+1] != 'x' && board->grid[x][y+1] != '#') {
            move[0] = x; move[1] = y+1;
            return move;
          }
          // Left of HIT
          if (0 <= y-1 && board->grid[x][y-1] != '*' && board->grid[x][y-1] != 'x' && board->grid[x][y-1] != '#') {
            move[0] = x; move[1] = y-1;
            return move;
          }
        }

    }
  }

  return randomShooting(board);
}

int* huntTarget_parity(Board* board) {

  static int move[2];

  for (int x = 0; x < board->boardSize; x++) {
    for (int y = 0; y < board->boardSize; y++) {

      if (board->grid[x][y] == '*') {
        // Above HIT
        if (0 <= x-1 && board->grid[x-1][y] != '*' && board->grid[x-1][y] != 'x' && board->grid[x-1][y] != '#') {
          move[0] = x-1; move[1] = y;
          return move;
        }
        // Below HIT
        if (x+1 < board->boardSize && board->grid[x+1][y] != '*' && board->grid[x+1][y] != 'x' && board->grid[x+1][y] != '#') {
          move[0] = x+1; move[1] = y;
          return move;
        }
        // Right of HIT
        if (y+1 < board->boardSize && board->grid[x][y+1] != '*' && board->grid[x][y+1] != 'x' && board->grid[x][y+1] != '#') {
          move[0] = x; move[1] = y+1;
          return move;
        }
        // Left of HIT
        if (0 <= y-1 && board->grid[x][y-1] != '*' && board->grid[x][y-1] != 'x' && board->grid[x][y-1] != '#') {
          move[0] = x; move[1] = y-1;
          return move;
        }
      }

    }
  }

  int* rMove = randomShooting(board);

  while (rMove[0]%2 == rMove[1]%2) {
    rMove = randomShooting(board);
  }

  return rMove;
}

int* probabilityDensity(Board* board) {

  bool target = false;

  // if part of unsunk ship is located, target it
  for (int x = 0; x < board->boardSize; x++) {
    for (int y = 0; y < board->boardSize; y++) {
      if (board->grid[x][y] == '*') {
        target = true;
        break;
      }
    }
  }

  if (target) {
    return pD_Target(board);
  }
  else {
    return pD_Hunt(board);
  }
}

int* pD_Hunt(Board* board) {

  static int move[2];

  // allocate grid dynamically
  int** densityGrid = malloc(sizeof(int* ) * board->boardSize);
  for (int i = 0; i < board->boardSize; i++) {
    densityGrid[i] = malloc(sizeof(int ) * board->boardSize);
  }

  // set grid to 0's
  for (int x = 0; x < board->boardSize; x++) {
    for (int y = 0; y < board->boardSize; y++) {
      densityGrid[x][y] = 0;
    }
  }
  


  for (int i=0; i<board->fleetSize; i++) {

    Ship* ship = board->fleet[i];

    // only search for ships still afloat
    if (!ship->afloat) {
      continue;
    }

    for (int x = 0; x < board->boardSize; x++) {
      for (int y = 0; y < board->boardSize; y++) {

        // if ship fits in x-axis, add to probability grid
        if (x+ship->size <= board->boardSize) {
          int x_possible = true;

          for (int k = 0; k < ship->size; k++) {
            if (board->grid[x+k][y] == 'x' || board->grid[x+k][y] == '#') {
              x_possible = false;
              break;
            }
          }
          if (x_possible) {
            for (int k = 0; k < ship->size; k++) {
              densityGrid[x+k][y]++;
            }
          }
        }

        // if ship fits in y-axis, add to probability grid
        if (y+ship->size <= board->boardSize) {
          int y_possible = true;

          for (int k = 0; k < ship->size; k++) {
            if (board->grid[x][y+k] == 'x' || board->grid[x][y+k] == '#') {
              y_possible = false;
              break;
            }
          }
          if (y_possible) {
            for (int k = 0; k < ship->size; k++) {
              densityGrid[x][y+k]++;
            }
          }
        }

      }
    }
  }

  // locates the square with the highest possibility, sets it as the ai's move
  int max = 0;
  for (int x = 0; x < board->boardSize; x++) {
    for (int y = 0; y < board->boardSize; y++) {
      if (max < densityGrid[x][y]) {
        max = densityGrid[x][y];
        move[0] = x; move[1] = y;
      }
    }
  }

  // printHeatMap(board, densityGrid);

  // free the densityGrid
  for (int i = 0; i < board->boardSize; i++) {
    free(densityGrid[i]);
  }
  free(densityGrid);

  return move;
}

int* pD_Target(Board* board) {

  static int move[2];

  // allocate grid dynamically
  int** densityGrid = malloc(sizeof(int* ) * board->boardSize);
  for (int i = 0; i < board->boardSize; i++) {
    densityGrid[i] = malloc(sizeof(int ) * board->boardSize);
  }

  // set grid to 0's
  for (int x = 0; x < board->boardSize; x++) {
    for (int y = 0; y < board->boardSize; y++) {
      densityGrid[x][y] = 0;
    }
  }

  for (int i=0; i<board->fleetSize; i++) {

    Ship* ship = board->fleet[i];

    // only search for ships still afloat
    if (!ship->afloat) {
      continue;
    }

    for (int x = 0; x < board->boardSize; x++) {
      for (int y = 0; y < board->boardSize; y++) {

        // if ship fits in x-axis and contains a '*', add to probability grid
        if (x+ship->size <= board->boardSize) {
          int x_possible = false;

          for (int k = 0; k < ship->size; k++) {
            if (board->grid[x+k][y] == '*') {
              x_possible = true;
            }
            else if (board->grid[x+k][y] == 'x' || board->grid[x+k][y] == '#') {
              x_possible = false;
              break;
            }
          }
          if (x_possible) {
            for (int k = 0; k < ship->size; k++) {
              if (board->grid[x+k][y] != '*') {
                densityGrid[x+k][y]++;
              }
            }
          }
        }

        // if ship fits in y-axis and contains a '*', add to probability grid
        if (y+ship->size <= board->boardSize) {
          int y_possible = false;

          for (int k = 0; k < ship->size; k++) {
            if (board->grid[x][y+k] == '*') {
              y_possible = true;
            }
            else if (board->grid[x][y+k] == 'x' || board->grid[x][y+k] == '#') {
              y_possible = false;
              break;
            }
          }
          if (y_possible) {
            for (int k = 0; k < ship->size; k++) {
              if (board->grid[x][y+k] != '*') {
                densityGrid[x][y+k]++;
              }
            }
          }
        }

      }
    }
  }

  // locates the square with the highest possibility, sets it as the ai's move
  int max = 0;
  for (int x = 0; x < board->boardSize; x++) {
    for (int y = 0; y < board->boardSize; y++) {
      if (max < densityGrid[x][y]) {
        max = densityGrid[x][y];
        move[0] = x; move[1] = y;
      }
    }
  }

  // printHeatMap(board, densityGrid);

  // free the densityGrid
  for (int i = 0; i < board->boardSize; i++) {
    free(densityGrid[i]);
  }
  free(densityGrid);

  return move;
}


void printHeatMap(Board* board, int** densityGrid) {

  for (int x = 0; x < board->boardSize; x++) {
    printf("\t");
    for (int y = 0; y < board->boardSize; y++) {
      printf("%*d ", 2, densityGrid[x][y]);
    }
    printf("\n");
  }
}