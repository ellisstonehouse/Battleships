
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#include "game.h"
#include "initGame.h"
#include "playGame.h"


int placeShip( int shipLength, char rotation, int x, int y,  char** board, int boardSize ) {

  // reject if negative coordinates
  if ( x < 0 || y < 0 ) {
    return 0;
  }


  char ship;
  switch (shipLength) {
    case 5: ship = 'A'; break;
    case 4: ship = 'B'; break;
    case 3: ship = 'C'; break;
    case 2: ship = 'D'; break;
  }

  // reject if area alrady in use
  if ( rotation == 'v' ) {

    if ( x+shipLength-1 > 9 ) {
      return 0;
    }

    for (int k=0; k<shipLength; k++) {
      if (board[x+k][y] != '.'){
        return 0;
      }
    }
    for (int k=0; k<shipLength; k++) {
      board[x+k][y] = ship;
    }
  }
  else if ( rotation == 'h' ) {

    if ( y+shipLength-1 > 9 ) {
      return 0;
    }

    for (int k=0; k<shipLength; k++) {
      if (board[x][y+k] != '.'){
        return 0;
      }
    }
    for (int k=0; k<shipLength; k++) {
      board[x][y+k] = ship;
    }
  }

  return 1;
}

char** createBoard(int boardSize) {

  char** board = malloc(sizeof(char* ) * boardSize);
  for (int i = 0; i < 10; i++) {
    board[i] = malloc(sizeof(char ) * boardSize);
  }

  for (int i = 0; i < boardSize; i++) {
    for (int j = 0; j < boardSize; j++) {
        board[i][j] = '.';
    }
  }

  return board;
}

void initShipsChoose( char** board, int boardSize ) {

  for (int i = 5; i > 1; i--) {
    char rotation;
    int x, y;
  
    while(true) {

      printBoard(board, 10);

      printf("Rotation: Vertical(v) or Horizontal(h): ");
      if (!scanf(" %c", &rotation)) {
        printf("ERROR! Incorrect rotation\n");
        continue;
      }

      if (!(rotation== 'v' || rotation=='h')) {
        continue;
      }

      if (!scanf(" %d %d", &x, &y)) {
        printf("ERROR! Incorrect coordinates\n");
        continue;
      }

      if (!placeShip( i, rotation, x, y, board, boardSize )) {
        printf("ERROR! Incorrect coordinates\n");
        continue;
      }

      break;
    }
  }



}

void initShipsRandom(char** board, int boardSize) {

  char rotations[2] = { 'v' , 'h' };

  srand(time(0));

  for (int i = 5; i > 1; i--) {

    while(true) {

      int rotation = rand() % 2;
      int x = rand() % 10;
      int y = rand() % 10;

      if (!placeShip( i, rotations[rotation], x, y, board, boardSize )) {
        continue;
      }

      break;
    }
  }

  printBoard(board, 10);

}

Game *initGame( int mode ) {

  Game *game = (Game *)malloc(sizeof(Game));

  game->board1 = createBoard(10);
  game->board2 = createBoard(10);

  //initShipsChoose(game->board1, 10);
  initShipsRandom(game->board1, 10);

  game->maxTurns = 100;
  game->turns = 0;
  
  return game;
}

void freeGame( Game *game ) {

  for (int i = 0; i < 10; i++) {
    free(game->board1[i]);
    free(game->board2[i]);
  }
  free(game->board1);
  free(game->board2);

  free(game);
}



