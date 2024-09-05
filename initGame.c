
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>


#include "game.h"
#include "initGame.h"
#include "playGame.h"

#define TESTING 0


int placeShip( int ship, char rotation, int x, int y,  Board* board ) {

  // reject if negative coordinates
  if ( x < 0 || y < 0 ) {
    return 0;
  }


  int shipLength = board->fleet[ship]->size;
  char ID = board->fleet[ship]->id;



  // reject if area aleady in use
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
      board->grid[x+k][y] = ID;
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
      board->grid[x][y+k] = ID;
    }
  }

  board->fleet[ship]->x = x;
  board->fleet[ship]->y = y;
  board->fleet[ship]->rotation = rotation;


  return 1;
}

Ship* createShip(char ID, int size) {

  Ship* new_ship = (Ship*)malloc(sizeof(Ship));

  new_ship->id = ID;
  new_ship->size = size;
  new_ship->afloat = true;
  

  return new_ship;

}

Board* createBoard(int boardSize) {

  Board* board = (Board*)malloc(sizeof(Board));

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

  board->fleetSize = 5;

  board->fleet = malloc(sizeof(Ship*) * board->fleetSize);

  board->fleet[0] = createShip('A', 5); // Aircraft Carrier
  board->fleet[1] = createShip('B', 4); // Battleship
  board->fleet[2] = createShip('S', 3); // Submarine
  board->fleet[3] = createShip('C', 3); // Cruiser
  board->fleet[4] = createShip('D', 2); // Destroyer


  return board;
}

// Board* maskBoard(Board* board) {

//   Board *maskedBoard = (Board *)malloc(sizeof(Board));

//   maskedBoard->grid = malloc(sizeof(char* ) * board->boardSize);
//   for (int i = 0; i < board->boardSize; i++) {
//     maskedBoard->grid[i] = malloc(sizeof(char ) * board->boardSize);
//   }

//   for (int i = 0; i < board->boardSize; i++) {
//     for (int j = 0; j < board->boardSize; j++) {
//       if (board->grid[i][j] == '*') {
//         maskedBoard->grid[i][j] = '*';
//       }
//       else if (board->grid[i][j] == 'x') {
//         maskedBoard->grid[i][j] = 'x';
//       }
//       else {
//         maskedBoard->grid[i][j] = '.';
//       }
//     }
//   }

//   maskedBoard->boardSize = board->boardSize;

//   maskedBoard->Aircraft_Carrier = board->Aircraft_Carrier;
//   maskedBoard->Battleship = board->Battleship;
//   maskedBoard->Submarine = board->Submarine;
//   maskedBoard->Cruiser = board->Cruiser;
//   maskedBoard->Destroyer = board->Destroyer;

//   return maskedBoard;
// }

void initShipsChoose( Board* board) {

  for (int ship = 0; ship < board->fleetSize; ship++) {
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

      if (!placeShip( ship, rotation, x, y, board )) {
        printf("ERROR! Incorrect coordinates\n");
        continue;
      }

      break;
    }
  }



}

void initShipsRandom(Board* board) {

  static char rotations[2] = { 'v' , 'h' };

  srand((unsigned int)clock()); // only use clock when testing
  // srand(time(0));

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
    initShipsRandom(game->userBoard);
    // initShipsChoose(game->userBoard);
    initShipsRandom(game->aiBoard);
  }

  game->mode = mode;
  game->maxTurns = 10*10;

  
  
  return game;
}

void freeBoard( Board *board ) {

  for (int i = 0; i < board->boardSize; i++) {
    free(board->grid[i]);
  }
  free(board->grid);

  free(board);
}

// edit to accept board freeing
void freeGame( Game *game ) {

  freeBoard(game->userBoard);
  freeBoard(game->aiBoard);

  free(game);
}



