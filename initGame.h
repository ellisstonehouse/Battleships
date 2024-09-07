
Game *initGame( int algo, int mode );

Board* createBoard();

Ship* createShip(char ID, int size);

Board *maskBoard(Board* board);

void initShipsChoose( Board* board);

void initShipsRandom(Board* board);

int placeShip( int ship, char rotation, int x, int y,  Board* board );

void freeBoard(Board *board);

void freeGame(Game *game);

void clearInputBuffer();
