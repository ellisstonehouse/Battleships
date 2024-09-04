
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

    printf("Round %d:\n\n", round);

    // -------------------------------------------
    printf("User:\n");

    Board* maskedAiBoard = maskBoard(game->aiBoard);

    move = userMove(maskedAiBoard); //takes in the masked board as arg

    if (!acceptMove(game->aiBoard, maskedAiBoard, move)) { // takes in the real board here
      printf("Error occured\n");
      break;
    }

    //printBoard2(game->userBoard, maskedAiBoard);

    freeBoard(maskedAiBoard);

    if (fleetDefeated(game->aiBoard)) {
      printBoard2(game->userBoard, maskedAiBoard);
      printf("User has won\n");
      break;
    }

    // -----------------------------------------
    printf("Opponent:\n");

    Board* maskedUserBoard = maskBoard(game->userBoard);

    move = aiMove(maskedUserBoard, game->mode);

    if (!acceptMove(game->userBoard, maskedUserBoard, move)) { // takes in the real board here
      printf("Error occured\n");
      break;
    }

    printBoard2(game->userBoard, game->aiBoard);

    freeBoard(maskedUserBoard);

    if (fleetDefeated(game->userBoard)) {
      printf("AI has won\n");
      break;
    }

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

  printf("     A:%d B:%d S:%d C:%d D:%d         ", board1->Aircraft_Carrier, board1->Battleship, board1->Submarine, board1->Cruiser, board1->Destroyer);
  printf("     A:%d B:%d S:%d C:%d D:%d\n\n", board2->Aircraft_Carrier, board2->Battleship, board2->Submarine, board2->Cruiser, board2->Destroyer);

  return;
}

int* userMove(Board* board) {

  static int move[2];
  int x, y;

  while(true) {

      printf("Enter your move as row column values:\n");

      int accept = scanf(" %d %d", &x, &y);

      if (!accept) {
        printf("ERROR! Incorrect coordinates\n");
        continue;
      }

      if ( x < 0 || board->boardSize < x || y < 0 || board->boardSize < y ) {
        printf("ERROR! Incorrect coordinates\n");
        continue;
      }

      if (board->grid[x][y] == '*' || board->grid[x][y] == 'x') {
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

  int a=false, b=false, s=false, c=false, d=false;

  // if it was a ship that it hit, do another symbol 'X' maybe ??
  if (board->grid[move[0]][move[1]] == '*' || board->grid[move[0]][move[1]] == 'x') {
    return 0;
  }
  else if (board->grid[move[0]][move[1]] == '.') {
    board->grid[move[0]][move[1]] = 'x';
    maskedBoard->grid[move[0]][move[1]] = 'x';
  }
  else {
    board->grid[move[0]][move[1]] = '*';
    maskedBoard->grid[move[0]][move[1]] = '*';
  }


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
    printf("Battleship has been sunk\n");
    board->Battleship = false;
  }
  if (board->Submarine != s) {
    printf("Submarine has been sunk\n");
    board->Submarine = false;
  }
  if (board->Cruiser != c) {
    printf("Cruiser has been sunk\n");
    board->Cruiser = false;
  }
  if (board->Destroyer != d) {
    printf("Destroyer has been sunk\n");
    board->Destroyer = false;
  }

  return 1;
}

int fleetDefeated( Board* board ) {

  if (board->Aircraft_Carrier || board->Battleship || board->Submarine || board->Cruiser || board->Destroyer) {
    return 0;
  }

  return 1;
}

// Conceal ships function, which will take in the real board, conceal the ships and deduct whether the ships have sank or not.

