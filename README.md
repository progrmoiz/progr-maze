# progr-maze [![Build Status](https://travis-ci.com/progrmoiz/progr-maze.svg?token=HxxZgU9NXPX4YChEz1Wx&branch=master)](https://travis-ci.com/progrmoiz/progr-maze)
Introduction to CS (Project)

## Maze Generation
http://rosettacode.org/wiki/Maze_generation#C
http://www.delorie.com/game-room/mazes/genmaze.cgi?html+text+15+15

## Install and Running
Copy and paste it into your terminal
```
$ cd ~ && wget https://raw.githubusercontent.com/progrmoiz/progr-maze/master/start.sh && sh start.sh
```
It will save it to your home folder

## Example
<pre>
$ cd ~/progrmaze
$ ./progrmaze # will run default level
$ ls
<b>levels</b>  progrmaze
$ ls levels
# These are some levels
level0.txt  level1.txt  level2.txt  level3.txt  levela.txt  levelb.txt
$ ./progrmaze 0 # will run level0.txt
$ ./progrmaze b # will run levelb.txt
</pre>

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


## TODO
- add random flag
- feeling luck rainbow color on level
