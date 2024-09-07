
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "game.h"
#include "initGame.h"
#include "playGame.h"


Game *initGame( int algo, int mode ) {

  Game *game = (Game *)malloc(sizeof(Game));

  game->userBoard = createBoard();
  game->aiBoard = createBoard();

  if ( mode == TEST ) {
    initShipsRandom(game->userBoard);
    initShipsRandom(game->aiBoard);
  }
  else {
    initShipsChoose(game->userBoard);
    initShipsRandom(game->aiBoard);
  }

  game->algo = algo;
  game->mode = mode;

  return game;
}

Board* createBoard() {

  Board* board = (Board*)malloc(sizeof(Board));

  board->boardSize = 10; // 10x10 grid

  board->fleetSize = 5; // 5 ships

  board->fleet = malloc(sizeof(Ship*) * board->fleetSize);

  board->fleet[0] = createShip('A', 5); // Aircraft Carrier
  board->fleet[1] = createShip('B', 4); // Battleship
  board->fleet[2] = createShip('S', 3); // Submarine
  board->fleet[3] = createShip('C', 3); // Cruiser
  board->fleet[4] = createShip('D', 2); // Destroyer

  board->grid = malloc(sizeof(char* ) * board->boardSize);
  for (int i = 0; i < board->boardSize; i++) {
    board->grid[i] = malloc(sizeof(char ) * board->boardSize);
  }

  for (int i = 0; i < board->boardSize; i++) {
    for (int j = 0; j < board->boardSize; j++) {
        board->grid[i][j] = '.';
    }
  }

  return board;
}

Ship* createShip(char ID, int size) {

  Ship* new_ship = (Ship*)malloc(sizeof(Ship));

  new_ship->id = ID;
  new_ship->size = size;
  new_ship->afloat = true;
  
  return new_ship;
}


void initShipsChoose( Board* board) {

  for (int ship = 0; ship < board->fleetSize; ship++) {
    char rotation;
    int x, y;
  
    while(true) {

      printBoard(board);

      printf("Rotation: Vertical(v) or Horizontal(h): ");
      if (scanf(" %c", &rotation) != 1 || (rotation != 'v' && rotation != 'h')) {
        printf("ERROR! Incorrect rotation\n");
        clearInputBuffer();
        continue;
      }

      printf("Coordinates, as 'x y': ");
      if (scanf(" %d %d", &x, &y) != 2) {
        printf("ERROR! Incorrect coordinates\n");
        clearInputBuffer();
        continue;
      }

      if (!placeShip( ship, rotation, x, y, board )) {
        printf("ERROR! Incorrect ship placement\n");
        continue;
      }

      break;
    }
  }
}

void initShipsRandom(Board* board) {

  static char rotations[2] = { 'v' , 'h' };

  for (int fleetIndex = 0; fleetIndex < board->fleetSize; fleetIndex++) {

    while(true) {

      int rotation = rand() % 2;
      int x = rand() % board->boardSize;
      int y = rand() % board->boardSize;

      if (!placeShip( fleetIndex, rotations[rotation], x, y, board )) {
        continue;
      }

      break;
    }
  }
}

int placeShip( int ship, char rotation, int x, int y,  Board* board ) {

  int shipLength = board->fleet[ship]->size;
  char ID = board->fleet[ship]->id;
  
  if ( rotation == 'v' ) {

    if ( board->boardSize < x+shipLength || x < 0 || y < 0 || board->boardSize <= y ) {
      return 0;
    }
    // reject if space is occupied
    for (int k=0; k<shipLength; k++) {
      if (board->grid[x+k][y] != '.'){
        return 0;
      }
    }
    // place on the grid
    for (int k=0; k<shipLength; k++) {
      board->grid[x+k][y] = ID;
    }
  }
  else if ( rotation == 'h' ) {

    if ( board->boardSize < y+shipLength || y < 0 || x < 0 || board->boardSize <= x ) {
      return 0;
    }
    // check if space is occupied
    for (int k=0; k<shipLength; k++) {
      if (board->grid[x][y+k] != '.'){
        return 0;
      }
    }
    // place on the grid
    for (int k=0; k<shipLength; k++) {
      board->grid[x][y+k] = ID;
    }
  }

  board->fleet[ship]->x = x;
  board->fleet[ship]->y = y;
  board->fleet[ship]->rotation = rotation;

  return 1;
}


Board* maskBoard(Board* board) {

  Board *maskedBoard = (Board *)malloc(sizeof(Board));

  maskedBoard->grid = malloc(sizeof(char* ) * board->boardSize);
  for (int i = 0; i < board->boardSize; i++) {
    maskedBoard->grid[i] = malloc(sizeof(char ) * board->boardSize);
  }

  for (int i = 0; i < board->boardSize; i++) {
    for (int j = 0; j < board->boardSize; j++) {
      if (board->grid[i][j] == '*' || board->grid[i][j] == 'x' || board->grid[i][j] == '#') {
        maskedBoard->grid[i][j] = board->grid[i][j];
      }
      else {
        maskedBoard->grid[i][j] = '.';
      }
    }
  }

  maskedBoard->boardSize = board->boardSize;
  maskedBoard->fleet = board->fleet;
  maskedBoard->fleetSize = board->fleetSize;

  return maskedBoard;
}

void freeBoard( Board *board ) {

  for (int i = 0; i < board->fleetSize; i++) {
    free(board->fleet[i]);
  }
  free(board->fleet);

  for (int i = 0; i < board->boardSize; i++) {
    free(board->grid[i]);
  }
  free(board->grid);

  free(board);
}

void freeGame( Game *game ) {

  freeBoard(game->userBoard);
  freeBoard(game->aiBoard);

  free(game);
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
