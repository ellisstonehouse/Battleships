
typedef struct _board {
  char** grid;
  int boardSize;
  int Aircraft_Carrier;
  int Battleship;
  int Submarine;
  int Cruiser;
  int Destroyer;
} Board;

typedef struct _game {
  Board* userBoard;    // Player1's Board
  Board* aiBoard;    // Player2's Board
  int maxTurns;
} Game;