
# code details

EXE = ./Battleships
SRC = main.c initGame.c playGame.c aiMoves.c
OBJ = main.o initGame.o playGame.o aiMoves.o

# generic build details

CC     = gcc
CFLAGS = -std=c99 -Wall
CLIBS  = 
CLINK  = 

# compile to object code

%.o: %.c
	$(CC) -c $(CFLAGS) $(CLIBS) $< -o $@

# build executable: type 'make'

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(CLINK) -o $(EXE) 

# clean up and remove object code and executable: type 'make clean'

clean:
	rm -f $(OBJ) $(EXE)

# dependencies

#
main.o: main.c game.h initGame.h
initGame.o: initGame.c game.h initGame.h
#
