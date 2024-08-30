
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>


#include "game.h"
#include "initGame.h"
#include "playGame.h"

#define TESTING 0


int placeShip( char ship, char rotation, int x, int y,  Board* board ) {

  // reject if negative coordinates
  if ( x < 0 || y < 0 ) {
    return 0;
  }

  int shipLength;
  switch (ship) {
    case 'A': shipLength = 5; break;
    case 'B': shipLength = 4; break;
    case 'S': shipLength = 3; break;
    case 'C': shipLength = 3; break;
    case 'D': shipLength = 2; break;
  }

  // reject if area alrady in use
  if ( rotation == 'v' ) {

    if ( x+shipLength > board->boardSize ) {
      return 0;
    }

    for (int k=0; k<shipLength; k++) {
      if (board->grid[x+k][y] != '.'){
        return 0;
      }
    }
    for (int k=0; k<shipLength; k++) {
      board->grid[x+k][y] = ship;
    }
  }
  else if ( rotation == 'h' ) {

    if ( y+shipLength-1 > board->boardSize ) {
      return 0;
    }

    for (int k=0; k<shipLength; k++) {
      if (board->grid[x][y+k] != '.'){
        return 0;
      }
    }
    for (int k=0; k<shipLength; k++) {
      board->grid[x][y+k] = ship;
    }
  }

  return 1;
}

Board *createBoard(int boardSize) {

  Board *board = (Board *)malloc(sizeof(Board));

  board->grid = malloc(sizeof(char* ) * boardSize);
  for (int i = 0; i < boardSize; i++) {
    board->grid[i] = malloc(sizeof(char ) * boardSize);
  }

  for (int i = 0; i < boardSize; i++) {
    for (int j = 0; j < boardSize; j++) {
        board->grid[i][j] = '.';
    }
  }
  board->boardSize = boardSize;

  board->Aircraft_Carrier = true;
  board->Battleship = true;
  board->Submarine = true;
  board->Aircraft_Carrier = true;
  board->Cruiser = true;

  return board;
}

void initShipsChoose( Board* board) {

  static char ship[5] = {'A', 'B', 'S', 'C', 'D'};

  for (int i = 0; i < 5; i++) {
    char rotation;
    int x, y;
  
    while(true) {

      printBoard(board);

      printf("Rotation: Vertical(v) or Horizontal(h): ");
      if (!scanf(" %c", &rotation)) {
        printf("ERROR! Incorrect rotation\n");
        continue;
      }

      printf("Coordinates, as 'x y': ");
      if (!(rotation == 'v' || rotation == 'h')) {
        continue;
      }

      if (!scanf(" %d %d", &x, &y)) {
        printf("ERROR! Incorrect coordinates\n");
        continue;
      }

      if (!placeShip( ship[i], rotation, x, y, board )) {
        printf("ERROR! Incorrect coordinates\n");
        continue;
      }

      break;
    }
  }



}

void initShipsRandom(Board* board) {

  static char rotations[2] = { 'v' , 'h' };
  static char ship[5] = {'A', 'B', 'S', 'C', 'D'};

  srand((unsigned int)clock()); // only use clock when testing
  // srand(time(0));

  for (int i = 0; i < 5; i++) {

    while(true) {

      int rotation = rand() % 2;
      int x = rand() % board->boardSize;
      int y = rand() % board->boardSize;

      if (!placeShip( ship[i], rotations[rotation], x, y, board )) {
        continue;
      }

      break;
    }
  }

  // printBoard(board);

}

Game *initGame( int mode ) {

  Game *game = (Game *)malloc(sizeof(Game));

  game->userBoard = createBoard(10);
  game->aiBoard = createBoard(10);

  if ( mode == TESTING) {
    initShipsRandom(game->userBoard);
    initShipsRandom(game->aiBoard);
  }
  else {
    initShipsChoose(game->userBoard);
    initShipsRandom(game->aiBoard);
  }

  game->mode = mode;
  game->maxTurns = 10*10;
  
  return game;
}

void freeGame( Game *game ) {

  for (int i = 0; i < game->userBoard->boardSize; i++) {
    free(game->userBoard->grid[i]);
  }
  free(game->userBoard->grid);

  for (int i = 0; i < game->aiBoard->boardSize; i++) {
    free(game->aiBoard->grid[i]);
  }
  free(game->aiBoard->grid);

  free(game->userBoard);
  free(game->aiBoard);

  free(game);
}



