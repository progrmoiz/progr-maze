# progr-maze [![Build Status](https://travis-ci.com/progrmoiz/progr-maze.svg?token=HxxZgU9NXPX4YChEz1Wx&branch=master)](https://travis-ci.com/progrmoiz/progr-maze)
Introduction to CS (Project)

## Maze Generation
- http://www.delorie.com/game-room/mazes/genmaze.cgi?html+text+15+15
- http://joewing.net/projects/maze/

## Install and Running
Copy and paste it into your terminal
```
$ cd ~ && wget https://raw.githubusercontent.com/progrmoiz/progr-maze/master/start.sh && sh start.sh
```
It will save it to your home folder

## Usage
```
Usage: 
    ./progrmaze <level> [--freaky]
    ./progrmaze gen <width> <height> [--freaky]

Examples: 
    ./progrmaze a
    ./progrmaze 0 --freaky
    ./progrmoiz b # will run b ./levels/levelb.txt
    ./progrmaze gen 10 10
    ./progrmaze gen 5 10 --freaky

Instruction: 
- Use arrow key or wasd to move around.
- Press to '#' on your keyboard to exit.
```

## Change Levels
Giving first (level) arguments to `./progrmaze` script. Level folder must be in same folder where your program is. 

#### Example
```
$ ./progrmaze a
```

## How to play
- Use arrow keys or wasd keys to move your player
- Press '#' on your keyboard
- Reach to 'G' gold.
