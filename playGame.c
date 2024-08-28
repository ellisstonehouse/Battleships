
#include <stdio.h>

#include "game.h"
#include "playGame.h"

void playGame( Game *game ) {

  char symbols[2] = { '1', '2' };
  // player '1' plays first
  int player = 0;

  for (int round=1; round<=game->maxTurns; round++) {

    printf("Round %d:\n", round);

    printf("Player %c: Enter your move as row column values:\n", symbols[player]);

    // int moveRejected = makeMove(game, symbols[player]);
    // while(moveRejected) {
    //   printf("Move rejected. Please try again\n");
    //   moveRejected = makeMove(game, symbols[player]);
    // }

    if (winGame(game->board1, symbols[player], 10)) {
      printf("Player %c has won\n",symbols[player]);
      break;
    }
    else {
      player ^= 1; // toggle player
    }
  }
 
  return;
}

void printBoard( char** board, int boardSize) {

  printf("\n");
  printf("    ");
  for (int i=0; i<boardSize; i++) {
    printf("  %d", i);
  }
  printf("\n\n");

  for (int i=0; i<boardSize; i++) {
    printf(" %d  ", i);
    for (int j=0; j<boardSize; j++) {
      printf("  %c", board[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  return;
}

void printBoard2( char** board1, char** board2, int boardSize) {

  printf("\n");
  printf("    ");
  for (int i=0; i<boardSize; i++) {
    printf("  %d", i);
  }
  printf("\n\n");

  for (int i=0; i<boardSize; i++) {
    printf(" %d  ", i);
    for (int j=0; j<boardSize; j++) {
      printf("  %c", board1[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  return;
}

int makeMove( Game *game, char symbol ) {
  return 0;
}

int winGame( char** board, int boardSize, char symbol ) {

  for (int x=0; x<boardSize; x++) {
    for (int y=0; y<boardSize; y++) {
      if (board[x][y]=='A' || board[x][y]=='B' || board[x][y]=='C' || board[x][y]=='D') {
        return 0;
      }
    }
  }

  return 1;
}

