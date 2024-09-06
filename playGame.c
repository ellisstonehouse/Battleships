
#include <stdio.h>
#include <stdbool.h>

#include "game.h"
#include "playGame.h"
#include "initGame.h"
#include "aiMoves.h"

#define USER 0
#define AI 1

void playGame( Game *game ) {

  int* move;
  int round = 1;

  Board* maskedAiBoard = maskBoard(game->aiBoard);
  Board* maskedUserBoard = maskBoard(game->userBoard);

  while(true) {

    if (game->mode == TEST) {
      printBoard2(game->userBoard, game->aiBoard);
    }
    else {
      printBoard2(game->userBoard, maskedAiBoard);
    }

    printf("Round %d:\n\n", round++);

    // ------------------------------------------
    printf("User:\n");

    move = userMove(maskedAiBoard);

    if (!acceptMove(game->aiBoard, maskedAiBoard, move)) {
      printf("Error occured\n");
      break;
    }

    if (fleetDefeated(game->aiBoard)) {
      printBoard2(game->userBoard, game->aiBoard);
      printf("User has won\n");
      break;
    }

    // ------------------------------------------
    printf("Opponent:\n");

    move = aiMove(game->userBoard, game->algo);

    if (!acceptMove(game->userBoard, maskedUserBoard, move)) {
      printf("Error occured\n");
      break;
    }

    if (fleetDefeated(game->userBoard)) {
      printBoard2(game->userBoard, game->aiBoard);
      printf("AI has won\n");
      break;
    }
  }

  freeBoard(maskedAiBoard);
  freeBoard(maskedUserBoard);
 
  return;
}

void printBoard( Board* board) {

  printf("\n");
  printf("    ");
  for (int i=0; i<board->boardSize; i++) {
    printf("  %d", i);
  }
  printf("\n\n");

  for (int i=0; i<board->boardSize; i++) {
    printf(" %d  ", i);
    for (int j=0; j<board->boardSize; j++) {
      printf("  %c", board->grid[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  return;
}

void printBoard2( Board* board1, Board* board2) {

  printf("\n");
  printf("    ");
  for (int i=0; i<board1->boardSize; i++) {
    printf(" %d", i);
  }
  printf("             ");
  for (int i=0; i<board2->boardSize; i++) {
    printf(" %d", i);
  }
  printf("\n\n");

  for (int i=0; i<board1->boardSize; i++) {
    printf(" %d  ", i);
    for (int j=0; j<board1->boardSize; j++) {
      printf(" %c", board1->grid[i][j]);
    }

    printf("          %d  ", i);
    for (int j=0; j<board2->boardSize; j++) {
      printf(" %c", board2->grid[i][j]);
    }

    printf("\n");
  }
  printf("\n");


  printf("    ");
  for (int i=0; i<board1->fleetSize; i++) {
    Ship* ship = board1->fleet[i];
     printf(" %c:%d", ship->id, ship->afloat);
  }
  printf("             ");
  for (int i=0; i<board2->fleetSize; i++) {
    Ship* ship = board1->fleet[i];
     printf(" %c:%d", ship->id, ship->afloat);
  }
  printf("\n\n");


  return;
}

int* userMove(Board* board) {

  static int move[2];
  int x, y;

  while(true) {

      printf("Enter your move as row column values:\n");

      if (scanf(" %d %d", &x, &y) != 2) {
        printf("ERROR! Incorrect coordinates\n");
        continue;
      }

      if ( x < 0 || board->boardSize <= x || y < 0 || board->boardSize <= y ) {
        printf("ERROR! Incorrect coordinates\n");
        continue;
      }

      if (board->grid[x][y] == '*' || board->grid[x][y] == 'x' || board->grid[x][y] == '#') {
        printf("ERROR! Incorrect coordinates\n");
        continue;
      }

      break;
    }

    move[0] = x;
    move[1] = y;

    return move;
}


int acceptMove( Board* board, Board* maskedBoard, int* move ) {

  int x = move[0];
  int y = move[1];


  if (board->grid[x][y] == '*' || board->grid[x][y] == 'x' || board->grid[x][y] == '#') {
    return 0;
  }
  else if (board->grid[x][y] == '.') {
    board->grid[x][y] = 'x';
    maskedBoard->grid[x][y] = 'x';
    return 1;
  }
  else {
    board->grid[x][y] = '*';
    maskedBoard->grid[x][y] = '*';
  }


  // check all afloat ships if they are instead newly sunk
  for (int i=0; i<board->fleetSize; i++) {

    Ship* ship = board->fleet[i];

    // skip check if already sunk
    if (!ship->afloat) {
      continue;
    }

    x = ship->x;
    y = ship->y;
    int count = 0;

    for (int k=0; k<ship->size; k++) {
      if (ship->rotation == 'v') {
        if (board->grid[x+k][y] != ship->id) {
          count++;
        }
      }
      else if (ship->rotation == 'h') {
        if (board->grid[x][y+k] != ship->id) {
          count++;
        }
      }
    }

    // if newly sunk, set ship to #
    if (ship->size == count) {
      for (int k=0; k<ship->size; k++) {
        if (ship->rotation == 'v') {
          board->grid[x+k][y] = '#';
          maskedBoard->grid[x+k][y] = '#';
        }
        else if (ship->rotation == 'h') {
          maskedBoard->grid[x][y+k] = '#';
        }
      }
      ship->afloat = false;

    }
  }

  return 1;
}

int fleetDefeated( Board* board ) {

  for (int ship=0; ship<board->fleetSize; ship++) {
    if (board->fleet[ship]->afloat) {
      return 0;
    }
  }

  return 1;
}

// Conceal ships function, which will take in the real board, conceal the ships and deduct whether the ships have sank or not.

