#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// It is not part of the C standard library
// #include <conio.h>
#include <ncurses.h>

#define WIDTH 10
#define HEIGHT 10
#define TOTAL_SIZE WIDTH * HEIGHT

#define PLAYER 'P'
#define GOLD 'G'

// #define KEY_UP 119
// #define KEY_DOWN 115
// #define KEY_LEFT 97
// #define KEY_LEFT 100

#define MOVE_UP 1
#define MOVE_DOWN 2
#define MOVE_LEFT 3
#define MOVE_RIGHT 4

int PLAYER_POS = 0;
int MOVES = 0;
int WON = 0;

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
    printw("\n");
    for (int i = 0; i < TOTAL_SIZE; i++) {
        printw("%c", env[i]);
        if ((i+1) % WIDTH == 0) {
            printw("\n");
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

/**
 * set slot to given character
 * @param x    x-axis
 * @param y    y-axis
 * @param c    a character to replace with
 * @param grid a single dimensional character array
 */
void setvector(int x, int y, char c, char grid[]) {
    grid[x + WIDTH*y] = c;
}

/**
 * get single dimensional index by treating them as multi dimensional array
 * @param  x x-axis
 * @param  y y-axis
 * @return   get single dimensional index
 */
int getvector(int x, int y) {
    return x + WIDTH*y;
}

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
    int y = rand() % HEIGHT;
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
    PLAYER_POS = index;

    // can also do this
    // grid[index] = PLAYER;

    // but for consistancy
    int x = vectorX(index);
    int y = vectorY(index);
    setvector(x, y, PLAYER, grid);
}

/**
 * Congrats, How do you want to celebrate do here.
 */
void won() {
    clear();
    printw("Won");
}

/**
 * move player if empty slot
 * @param move Possible Values: MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT
 * @param grid A single dimenstional array
 */
void moveplayer(int move, char grid[]) {
    int playerx = vectorX(PLAYER_POS);
    int playery = vectorY(PLAYER_POS);
    switch (move) {
        case MOVE_UP:
            playery -= 1;
            break;
        case MOVE_DOWN:
            playery += 1;
            break;
        case MOVE_LEFT:
            playerx -= 1;
            break;
        case MOVE_RIGHT:
            playerx += 1;
            break;
    }
    int isgold = vector(playerx, playery, grid) == GOLD;

    if (isemptyslot(playerx, playery, grid) || isgold) {
        MOVES += 1;
        grid[PLAYER_POS] = ' ';
        PLAYER_POS = getvector(playerx, playery);
        setvector(playerx, playery, PLAYER, grid);
    }
    if(isgold) {
        WON = 1;
    }
}


int main() {
    srand(time(NULL));

    WINDOW *w;
    int ch;

    /* Curses Initialisations */
    w = initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    timeout(3000);

    /* Initializing Player */
    initplayer(env);

    /* Clear screen first */
    clear();

    printw("Welcome - Press # to Exit\n");

    while((ch = getch()) != '#') {

        switch(ch)
        {
        case KEY_UP:
            moveplayer(MOVE_UP, env);
            break;
        case KEY_DOWN:
            moveplayer(MOVE_DOWN, env);
            break;
        case KEY_LEFT:
            moveplayer(MOVE_LEFT, env);
            break;
        case KEY_RIGHT:
            moveplayer(MOVE_RIGHT, env);
            break;
        }
        /* Clear screen */
        clear();

        // print our board
        render();

        if (WON) {
            won();
            refresh();
            break;
        }
    }

    if (WON) {
        printw("You won in %d moves", MOVES);
    }

    /* End Curses */
    getch();
    endwin();

    return 0;
}
