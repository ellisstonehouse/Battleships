#ifndef GAME_H
#define GAME_H

#include <stdbool.h>  // Include the boolean header

typedef struct _ship {
  char id;
  int size;
  bool afloat;         // Now you can use 'bool' here
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
  int mode;
  int maxTurns;
} Game;

#endif // GAME_H