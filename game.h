#include <stdbool.h>

#ifndef GAME_H
#define GAME_H

#define TEST 0
#define RANDOM_SHOOTING 1
#define HUNT 2
#define HUNT_PARITY 3
#define PROB_DENSITY 4

typedef struct _ship {
  char id;
  int size;
  bool afloat;
  int x;
  int y;
  char rotation;
} Ship;

typedef struct _board {
  char** grid;
  int boardSize;
  Ship** fleet;
  int fleetSize;
} Board;

typedef struct _game {
  Board* userBoard;    // Player1's Board
  Board* aiBoard;      // Player2's Board
  int algo;
  int mode;
} Game;

#endif // GAME_H