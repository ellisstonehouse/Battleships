# Battleships

An implementation of the game Battleships with an AI opponent. The user can play against a chosen algorithm from 4, each having a higher win rate than the last.

The game is set up using the basic 10x10 board with 5 ships, 
- Aircraft Carrier (5 squares, A)
- Battleship (4 squares, B)
- Submarine (3 squares, S)
- Cruiser (3 squares, C)
- Destroyer (2 squares, D)  
These amass a total ship space of 17 squares.

These general board settings can be altered within initGame's createBoard function, which allows the board to be resized and ships to be added and deleted. The programs functionality adapts to these board changed accordingly.  

The 4 algorithms which have been adapted are:  
- Random Play
- Hunt + Target
- Hunt + Target (with Parity decisions)
- Probability Distributions  

## Random Play

## Hunt + Target 

## Hunt + Target (with Parity decisions)

## Probability Distributions  

The algorithms used are [clarified here](http://www.datagenetics.com/blog/december32011/) and further mentioned in this [Vsauce2 video here](https://www.youtube.com/watch?v=LbALFZoRrw8).


