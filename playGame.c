
#include <stdio.h>

#include "game.h"
#include "playGame.h"

#define USER 0
#define AI 1

void playGame( Game *game ) {

  printBoard2(game->userBoard, game->aiBoard);

  for (int round=1; round<=2; round++) {

    printf("Round %d:\n", round);

    printf("Player User: Enter your move as row column values:\n");

    int moveRejected = makeMove(game->aiBoard, userMove());
    while(moveRejected) {
      printf("Move rejected. Please try again\n");
      moveRejected = makeMove(game->aiBoard, userMove());
    }

    // turnResult(game->userBoard);

    // if (winGame(game->userBoard)) {
    //   printf("User has won\n");
    //   break;
    // }

    printBoard2(game->userBoard, game->aiBoard);

  }
 
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

  return;
}

int* userMove() {

  static int move[2];

  if (!scanf(" %d %d", &move[0], &move[1])) {
    move[0] = 0;
    move[1] = 0;
  }

  return move;
}


int makeMove( Board* board, int* move ) {

  int x = move[0];
  int y = move[1];

  if (board->grid[x][y] == '*') {
    return 1;
  }
  else {
    board->grid[x][y] = '*';
  }

  return 0;
}

int turnResult( Board* board ) {

  int a=1,b=1,s=1,c=1,d=1;

  for (int x=0; x<board->boardSize; x++) {
    for (int y=0; y<board->boardSize; y++) {
      switch (board->grid[x][y]) {
      case 'A': a = 0; break;
      case 'B': b = 0; break;
      case 'S': s = 0; break;
      case 'C': c = 0; break;
      case 'D': d = 0; break;
      default: break;
      }
    }
  }

  if (board->Aircraft_Carrier != a) {
    // somehow got to target player name
  }
  if (board->Battleship != b) {
  }
  if (board->Submarine != s) {
  }
  if (board->Cruiser != c) {
  }
  if (board->Destroyer != d) {
  }

  return 1;
}

int winGame( Board* board ) {

  for (int x=0; x<board->boardSize; x++) {
    for (int y=0; y<board->boardSize; y++) {
      if (board->grid[x][y]=='A' || board->grid[x][y]=='B' || board->grid[x][y]=='S' || board->grid[x][y]=='C' || board->grid[x][y]=='D') {
        return 0;
      }
    }
  }

  return 1;
}

// Conceal ships function, which will take in the real board, conceal the ships and deduct whether the ships have sank or not.

