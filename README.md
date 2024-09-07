# Battleships

An implementation of the game Battleships with an AI opponent. The user can play against a chosen algorithm from 4, each having a higher win rate than the last.

The game is set up using the basic 10x10 board with 5 ships, these amass a total ship space of 17 squares.
- Aircraft Carrier (5 squares, A)
- Battleship (4 squares, B)
- Submarine (3 squares, S)
- Cruiser (3 squares, C)
- Destroyer (2 squares, D)  

These general board settings can be altered within initGame's createBoard function, which allows the board to be resized and ships to be added and deleted. The program's functionality adapts to these board changes accordingly.  

The 4 algorithms which have been adapted are:  
- [Random Play](https://github.com/ellisstonehouse/Battleships/edit/main/README.md#random-play)
- [Hunt + Target](https://github.com/ellisstonehouse/Battleships/edit/main/README.md#hunt--target)
- [Hunt + Target (with Parity decisions)](https://github.com/ellisstonehouse/Battleships/edit/main/README.md#hunt--target-with-parity-decisions)
- [Probability Distributions](https://github.com/ellisstonehouse/Battleships/edit/main/README.md#probability-distributions)

## Random Play
The opponent will target random squares throughout the entire game.
## Hunt + Target 
The AI will act in two possible modes, hunt mode and target mode. Hunt mode works the same as random play and it will continue to be in this mode until a hit has occurred. Once a ship's square has been hit it will switch to target mode where 

## Hunt + Target (with Parity decisions)

## Probability Distributions  

The algorithms used are [clarified here](http://www.datagenetics.com/blog/december32011/) and further mentioned in this [Vsauce2 video here](https://www.youtube.com/watch?v=LbALFZoRrw8).


