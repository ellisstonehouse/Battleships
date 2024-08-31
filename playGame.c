
#include <stdio.h>
#include <stdbool.h>

#include "game.h"
#include "playGame.h"
#include "initGame.h"
#include "aiMoves.h"

#define USER 0
#define AI 1

void playGame( Game *game ) {

  printBoard2(game->userBoard, game->aiBoard);

  int* move;

  for (int round=1; round<=game->maxTurns; round++) {

    printf("Round %d:\n", round);

    // ----------
    Board* maskedAiBoard = maskBoard(game->aiBoard);

    printBoard2(game->userBoard, maskedAiBoard);

    move = userMove(maskedAiBoard); //takes in the masked board as arg

    freeBoard(maskedAiBoard);
    // ----------

    if (!acceptMove(game->aiBoard, move)) { // takes in the real board here
      printf("Error occured\n");
      break;
    }


    if (winGame(game->userBoard)) {
      printf("User has won\n");
      break;
    }

    Board* maskedUserBoard = maskBoard(game->userBoard);

    move = aiMove(maskedUserBoard, game->mode);

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

int* userMove(Board* board) {

  static int move[2];
  int x, y;

  while(true) {

      printf("Enter your move as row column values:\n");

      if (!scanf(" %d %d", &x, &y)) {
        printf("ERROR! Incorrect coordinates\n");
        continue;
      }

      if ( x < 0 || board->boardSize < x || y < 0 || board->boardSize < y ) {
        printf("ERROR! Incorrect coordinates\n");
        continue;
      }

      if (board->grid[x][y] == '*') {
        printf("ERROR! Incorrect coordinates\n");
        continue;
      }
      else {
        board->grid[x][y] = '*';
      }

      break;
    }

    move[0] = x;
    move[1] = y;

    return move;
}


int acceptMove( Board* board, int* move ) {

  int a=false, b=false, s=false, c=false, d=false;

  board->grid[move[0]][move[1]] = '*';

  for (int x=0; x<board->boardSize; x++) {
    for (int y=0; y<board->boardSize; y++) {
      switch (board->grid[x][y]) {
      case 'A': a = true; break;
      case 'B': b = true; break;
      case 'S': s = true; break;
      case 'C': c = true; break;
      case 'D': d = true; break;
      default: break;
      }
    }
  }

  if (board->Aircraft_Carrier != a) {
    // somehow got to target player name
    printf("Airship Carrier has been sunk\n");
    board->Aircraft_Carrier = false;
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

