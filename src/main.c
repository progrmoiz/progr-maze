#include <stdio.h>
#include <stdlib.h>
// It is not part of the C standard library
// #include <conio.h>
#include <time.h>
#include <stdlib.h>

#define WIDTH 10
#define TOTAL_SIZE 100

#define PLAYER 'P'
#define KEY_UP

char env[100] =
{
    'x','x','x','x','x','x','x','x','x','x',
    'x',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    'x','x',' ','x',' ','x',' ','x',' ','x',
    'x','x',' ','x',' ','x',' ','x',' ','x',
    'x',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    'x','x','x','x','x','x','x',' ',' ','x',
    'x','x','x','x','x','x','x',' ',' ','x',
    'x',' ','G',' ',' ',' ',' ',' ',' ',' ',
    'x',' ','x','x','x','x','x','x','x','x',
    'x',' ',' ',' ',' ',' ',' ',' ',' ',' ',
};

/**
 * Display our grid from global env array
 * No code coverage.
 */
void render() {
    // system("clear");
    // clear();
    printf("\n");
    for (int i = 0; i < 100; i++) {
        printf("%c", env[i]);
        if ((i+1) % 10 == 0) {
            printf("\n");
        }
    }
}

/**
 * Python equivalent string*number
 * @param c     character
 * @param multi multiplier
 */
void characterMultiply(char c, int multi) {
    for (int i = 0; i < multi; i++) {
        printf("%c", c);
    }
}

/**
 * A horizontal seperator
 */
void sep() {
    printf("\n");
    characterMultiply('-', 80);
    printf("\n");
}

/**
 * Return slot from character single dimensional array using x and y
 * @param  x    x-axis
 * @param  y    y-axis
 * @param  grid A single dimensional character array
 * @return      a character at that position
 */
char vector(int x, int y, char grid[]) {
    return grid[x + WIDTH*y];
}

void setvector(int x, int y, char c, char grid[]) {
    grid[x + WIDTH*y] = c;
}

// move vector

/**
 * If you have `i` and want its x position
 * @param  i index of item in array
 * @return   return x position based to `i`
 */
int vectorX(int i) {
    return i % WIDTH;
}

/**
 * If you have `i` and want its y position
 * @param  i index of item in array
 * @return   return y position based to `i`
 */
int vectorY(int i) {
    return i / WIDTH;
}

/**
 * check whether the slot is empty
 * @param  x    x-axis
 * @param  y    y-axis
 * @param  grid a single dimensional array
 * @return      1 or 0 or true or false
 */
int isemptyslot(int x, int y, char grid[]) {
    return vector(x, y, grid) == ' ';
}

/**
 * get random slot from character grid
 * may be not used...
 * @param  grid a single dimensional array
 * @return      random slot from grid
 */
char getrandomslot(char grid[]) {
    int y = rand() % 10;
    int x = rand() % WIDTH;
    return vector(x, y, grid);
}

/**
 * get random index based on len of single dimensional array
 * @return random index
 */
int getrandomvector() {
    return rand() % TOTAL_SIZE;
}

/**
 * get index of empty slot from character grid
 * @param  grid a single dimensional array
 * @return      `i` index of empty slot
 */
int getemptyslot(char grid[]) {
    while (1) {
        int r = getrandomvector();
        int x = vectorX(r);
        int y = vectorY(r);
        if (isemptyslot(x, y, grid)) {
            return r;
        }
    }
    return 0;
}

/**
 * set player to some empty position
 * @param grid [description]
 */
void initplayer(char grid[]) {
    int index = getemptyslot(grid);

    // can also do this
    // grid[index] = PLAYER;

    // but for consistancy
    int x = vectorX(index);
    int y = vectorY(index);
    setvector(x, y, PLAYER, grid);
}

int main() {
    printf("Progr Maze -- Moiz\n");
    return 0;
}
