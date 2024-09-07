# Battleships

An implementation of the game Battleships with an AI opponent. The user can play against a chosen algorithm from 4, each having a higher win rate than the last. The algorithms used are [clarified here](http://www.datagenetics.com/blog/december32011/) and further mentioned in this [Vsauce2 video here](https://www.youtube.com/watch?v=LbALFZoRrw8).

The game is set up using the basic 10x10 board with 5 ships, these amass a total ship space of 17 squares.
- Aircraft Carrier (5 squares, A)
- Battleship (4 squares, B)
- Submarine (3 squares, S)
- Cruiser (3 squares, C)
- Destroyer (2 squares, D)  

These general board settings can be altered within initGame's createBoard function, which allows the board to be resized and ships to be added and deleted. The program's functionality adapts to these board changes accordingly.  

Make the program using
```
make
```
Run as
```
./Battleships
```

To run in TESTING mode run with an argument of 0. In this mode both boards are visible during play and user board allocation is skipped
```
./Battleships 0
```

The 4 algorithms which have been adapted are:  
- [Random Play](https://github.com/ellisstonehouse/Battleships/edit/main/README.md#random-play)
- [Hunt + Target](https://github.com/ellisstonehouse/Battleships/edit/main/README.md#hunt--target)
- [Hunt + Target (with Parity decisions)](https://github.com/ellisstonehouse/Battleships/edit/main/README.md#hunt--target-with-parity-decisions)
- [Probability Distributions](https://github.com/ellisstonehouse/Battleships/edit/main/README.md#probability-distributions)

## Random Play
The opponent will target random squares throughout the entire game.

## Hunt + Target 
The AI will act in two possible modes, hunt mode and target mode. Hunt mode works the same as random play and it will continue to be in this mode until a hit has occurred. Once a ship's square has been hit it will switch to target mode where each next guess will surround this hit in an attempt to sink the rest of the ship. At this stage, the algorithm is unable to detect when a ship has sunk so it will continue to iterate around a hit even if so.

## Hunt + Target (with Parity decisions)
A slight modification to the previous algorithm. Since the shortest length ship is a length of 2, if imagining the board as a chequerboard where for every white square all of its directly adjacent squares are black and vice versa, every ship will cross both a white and a black square at least. This fact means that the hunt algorithm only has to hunt within one of these colours and every ship will still be hit. Once a ship has been hit, target mode occurs as normal. 

## Probability Distributions  
This ultimate algorithm works by creating a probability density grid of all possible locations where all unsunk ships in the fleet may be based on the current state of the board. The move choice for the AI will be the square on the board which is most likely to contain a ship. The algorithm also works in a target mode, where if a hit has occurred and the ship stays unsunk, it will consider all possible outstanding ship sizes which involve this hit square and choose the most probable. In all cases, a hit square, a previously missed square and a sunk square will all return 0 in the probability density grid as it will be impossible for the opponent to choose this square again. This algorithm is also able to detect when a ship is sunk, unlike the others, so it will not continue to try sink an already sunk ship. A function call for a heat map of this probability graph exists in the code if desired. 
