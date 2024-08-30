
#include <stdio.h>

#include "game.h"
#include "playGame.h"

#define USER 0
#define AI 1

void playGame( Game *game ) {

  printBoard2(game->userBoard, game->aiBoard);

  // for (int round=1; round<=game->maxTurns; round++) {

  //   printf("Round %d:\n", round);

  //   printf("Player %c: Enter your move as row column values:\n", symbols[player]);

      // int move[2] = userMove();

      // int moveRejected = makeMove(game, USER, move);
      // while(moveRejected) {
      //   printf("Move rejected. Please try again\n");
      //   moveRejected = makeMove(game, USER, move);
      // }

      // turnResult(game->userBoard);

  //   if (winGame(game->board1, symbols[player], 10)) {
  //     printf("Player %c has won\n",symbols[player]);
  //     break;
  //   }

  // }
 
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
  
  static int move[2] = {0, 0};

  return move;
}


int confirmMove( Game *game, int player, int* move ) {
  return 0;
}

int turnResult( Board* board ) {

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

