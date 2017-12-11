#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// It is not part of the C standard library
// #include <conio.h>
#include <ncurses.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

// #define WIDTH 10
// #define HEIGHT 10
// #define TOTAL_SIZE 100

// #define PLAYER 'P'
#define GOLD 'G'

// #define KEY_UP 119
// #define KEY_DOWN 115
// #define KEY_LEFT 97
// #define KEY_LEFT 100

#define MOVE_UP 1
#define MOVE_DOWN 2
#define MOVE_LEFT 3
#define MOVE_RIGHT 4

// we are not currently using this
#define NO_OF_CONSTUMES 4
char CONSTUMES[NO_OF_CONSTUMES] = {'\\', '|', '/', '|'};

char PLAYER = 'P';

int PLAYER_POS = 0;
int MOVES = 0;
int WON = 0;

int WIDTH = 10;
int HEIGHT = 10;

int FANCY_FLAG = 0;

// char env[100] =
// {
//     'x','x','x','x','x','x','x','x','x','x',
//     'x',' ',' ',' ',' ',' ',' ',' ',' ',' ',
//     'x','x',' ','x',' ','x',' ','x',' ','x',
//     'x','x',' ','x',' ','x',' ','x',' ','x',
//     'x',' ',' ',' ',' ',' ',' ',' ',' ',' ',
//     'x','x','x','x','x','x','x',' ',' ','x',
//     'x','x','x','x','x','x','x',' ',' ','x',
//     'x',' ','G',' ',' ',' ',' ',' ',' ',' ',
//     'x',' ','x','x','x','x','x','x','x','x',
//     'x',' ',' ',' ',' ',' ',' ',' ',' ',' ',
// };

char env[10000];

/* Build up our env from file */
void buildenv(char *path);

/* Total Size of array :( */
int TOTALSIZE() { return WIDTH * HEIGHT; }

/* Display our grid from global env array */
void render();

/* Fancy render version */
void renderFancy();

/* Python equivalent string*number */
void characterMultiply(char c, int multi);

/* A horizontal seperator */
void sep();

/* Return slot from character single dimensional array using x and y */
char vector(int x, int y, char grid[]);

/* set slot to given character */
void setvector(int x, int y, char c, char grid[]);

/* get single dimensional index by treating them as multi dimensional array */
int getvector(int x, int y);

/* If you have `i` and want its x position */
int vectorX(int i);

/* If you have `i` and want its y position */
int vectorY(int i);

/* check whether the slot is empty */
int isemptyslot(int x, int y, char grid[]);

/* get random slot from character grid */
char getrandomslot(char grid[]);

/* get random index based on len of single dimensional array */
int getrandomvector(int limit, int add);

/* get index of empty slot from character grid */
int getemptyslot(char grid[], int limit, int offset);

/* set player to some empty position */
void initplayer(char grid[]);

/* Congrats, How do you want to celebrate do here. */
void won();

/* move player if empty slot */
void moveplayer(int move, char grid[]);

/* let's play */
void play();

/*  Carve the maze starting at x, y. */
void CarveMaze(char *maze, int width, int height, int x, int y);

/* Generate maze in matrix maze with size width, height. */
void GenerateMaze(char *maze, int width, int height);

void genbuildenv(char *env);

void usageInstruction();

/**
 * Our well known main function
 * @author Abdul Moiz
 */
int main(int argc, char *argv[]) {
    printf("----------------------------------------\n");
    printf("Maze by Abdul Moiz (progrmoiz@github)\n");
    printf("----------------------------------------\n\n");

    if (argc < 2) {
        usageInstruction();
        exit(EXIT_FAILURE);
    }

    if (argc > 1 && strcmp(argv[1], "gen") == 0 && argc != 4 && argc != 5) {
        usageInstruction();
        exit(EXIT_FAILURE);
    }

    if (argc == 3 && strcmp(argv[2], "--freaky") == 0) FANCY_FLAG = 1;
    if (argc == 5 && strcmp(argv[4], "--freaky") == 0) FANCY_FLAG = 1;

    // from file
    if (argc <= 3) {
        // build our path from arguments
        char path[17];
        strcpy(path, "./levels/level");
        strcat(path, argv[1]);
        strcat(path, ".txt");

        // building our enviorment from .txt file path
        buildenv(path);
    }

    // generated once
    if (argc >= 4) {
       /* Get and validate the size. */
        WIDTH = atoi(argv[2]) * 2 + 3;
        HEIGHT = atoi(argv[3]) * 2 + 3;

        genbuildenv(env);
    }

    // random seed
    srand(time(NULL));

    // lets play
    play();

    return 0;
}

/**
 * Carve the maze starting at x, y.
 * @author: Joe Wingbermuehle 19990805
 */
void CarveMaze(char *maze, int width, int height, int x, int y) {

   int x1, y1;
   int x2, y2;
   int dx, dy;
   int dir, count;

   dir = rand() % 4;
   count = 0;
   while(count < 4) {
      dx = 0; dy = 0;
      switch(dir) {
      case 0:  dx = 1;  break;
      case 1:  dy = 1;  break;
      case 2:  dx = -1; break;
      default: dy = -1; break;
      }
      x1 = x + dx;
      y1 = y + dy;
      x2 = x1 + dx;
      y2 = y1 + dy;
      if(   x2 > 0 && x2 < width && y2 > 0 && y2 < height
         && maze[y1 * width + x1] == 1 && maze[y2 * width + x2] == 1) {
         maze[y1 * width + x1] = 0;
         maze[y2 * width + x2] = 0;
         x = x2; y = y2;
         dir = rand() % 4;
         count = 0;
      } else {
         dir = (dir + 1) % 4;
         count += 1;
      }
   }

}

/**
 * Generate maze in matrix maze with size width, height.
 * @author: Joe Wingbermuehle 19990805
 */
void GenerateMaze(char *maze, int width, int height) {

   int x, y;

   /* Initialize the maze. */
   for(x = 0; x < width * height; x++) {
      maze[x] = 1;
   }
   maze[1 * width + 1] = 0;

   /* Seed the random number generator. */
   srand(time(0));

   /* Carve the maze. */
   for(y = 1; y < height; y += 2) {
      for(x = 1; x < width; x += 2) {
         CarveMaze(maze, width, height, x, y);
      }
   }

   /* Set up the entry and exit. */
   maze[0 * width + 1] = 0;
   maze[(height - 1) * width + (width - 2)] = 0;

}

/**
 * Generate our env
 * @param env  a game env
 */
void genbuildenv(char *env) {
    char *maze;
    maze = (char*)malloc(TOTALSIZE() * sizeof(char));

    GenerateMaze(maze, WIDTH, HEIGHT);
    int i;
    for (i = 0; i < TOTALSIZE(); i+=1) {
        if (maze[i] == 1) {
            env[i] = '@';
        } else if (maze[i] == 0) {
            env[i] = ' ';
        }
    }

    // adding gold
    int r = getemptyslot(env, WIDTH, TOTALSIZE() - WIDTH);
    int x = vectorX(r);
    int y = vectorY(r);
    setvector(x, y, GOLD, env);
}

/**
 * Usage Instruction
 */
void usageInstruction() {
    printf("Usage: \n");
    printf("    ./progrmaze <level> [--freaky]\n");
    printf("    ./progrmaze gen <width> <height> [--freaky]\n");

    printf("\nExamples: \n");
    printf("    ./progrmaze a\n");
    printf("    ./progrmaze 0 --freaky\n");
    printf("    ./progrmaze gen 10 10\n");
    printf("    ./progrmaze gen 5 10 --freaky\n");

    printf("\nInstruction: \n");
    printf("- Use arrow key or wasd to move around.\n");
    printf("- Press to '#' on your keyboard to exit.\n");
}

/**
 * let's play
 */
void play() {
    WINDOW *w;
    int ch;

    /* Curses Initialisations */
    w = initscr();

    // assci blocks doesn't support colors
    if (env[0] != 'M') {
        start_color();
    }
    raw();
    keypad(stdscr, TRUE);
    noecho();
    timeout(3000);

    /* Initializing Player */
    initplayer(env);

    /* Clear screen first */
    clear();

    FANCY_FLAG ? renderFancy() : render();

    while((ch = getch()) != '#') {

        switch(ch)
        {
        case 'w':
        case KEY_UP:
            moveplayer(MOVE_UP, env);
            break;
        case 's':
        case KEY_DOWN:
            moveplayer(MOVE_DOWN, env);
            break;
        case 'a':
        case KEY_LEFT:
            moveplayer(MOVE_LEFT, env);
            break;
        case 'd':
        case KEY_RIGHT:
            moveplayer(MOVE_RIGHT, env);
            break;
        }
        /* Clear screen */
        clear();

        // print our board
        FANCY_FLAG ? renderFancy() : render();

        if (WON) {
            refresh();
            break;
        }

    }

    if (ch == '#') {
        sep();
        init_pair(4, COLOR_RED, COLOR_BLACK);
        attron(COLOR_PAIR(4));
        printw("Coming out...\n");
        attroff(COLOR_PAIR(4));
    }

    if (WON) {
        sep();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        attron(COLOR_PAIR(1));
        printw("Congratulations!. ");
        attroff(COLOR_PAIR(1));
        printw("You done this in %d moves.\n", MOVES);
    }

    // exiting
    if (WON || ch == '#') {
        sep();
        refresh();
        //sleep:
        sleep(1);
        WON ? exit(EXIT_SUCCESS) : exit(EXIT_FAILURE);
    }

    /* End Curses */
    getch();
    endwin();
}

/**
 * Build up our env from file
 * @param path relative to current file, path for a level file
 */
void buildenv(char *path) {
    FILE *fp;
    char buff[255];

    fp = fopen(path, "r");

    if ( fp == NULL ) {
        printf("Path not exist: %s\n", path);
        sleep(0.1);
        exit(EXIT_FAILURE);
        return;
    }

    // users inputed width and height
    int width, height;
    fscanf(fp, "%d%d", &height, &width);

    int line = 0;
    int w = 0;
    int h = 0;
    while (fgets(buff, 255, (FILE*)fp) != NULL) {
        // calculating the width
        w = -1;
        int i;
        for (i = 0; buff[i] != '\0'; i+=1) {
            env[i+line] = buff[i];
            w += 1;
        }
        // calculating the height
        h += 1;
        line += w;
    }

    if ((width != 0 && width != w) || (height != 0 && height != h-1)) {
        printf("Error: Mismatch width or height.\n");
        printf("Actual: Width=%d, Height=%d\n", w, h-1);
        printf("Expected: Width=%d, Height=%d\n", width, height);
        exit(EXIT_FAILURE);
    }

    // users inputed width and height else our calculated width and height
    if (width != 0 && height != 0) {
        WIDTH = width;
        HEIGHT = height;
    } else {
        WIDTH = w;
        HEIGHT = h;
    }

    fclose(fp);
}

/**
 * Display our grid from global env array
 * No code coverage.
 */
void render() {
    // system("clear");
    // clear();
    printw("\n");
    int i;
    for (i = 0; i < TOTALSIZE(); i++) {

        // M is special block
        if (env[i] == 'M') {
            addch((char)0x2588);
        } else if (env[i] == '|' || env[i] == '\\' || env[i] == '/' || env[i] == 'P') {
            init_pair(1, COLOR_BLUE, COLOR_BLACK);
            attron(COLOR_PAIR(1));
            printw("%c", env[i]);
            attroff(COLOR_PAIR(1));
        } else if (env[i] == 'G') {
            init_pair(2, COLOR_YELLOW, COLOR_BLACK);
            attron(COLOR_PAIR(2));
            printw("%c", env[i]);
            attroff(COLOR_PAIR(2));
        } else {
            printw("%c", env[i]);
        }

        if ((i+1) % WIDTH == 0) {
            printw("\n");
        }
    }
}

/**
 * A colorful render
 * A lot copy pasting
 */
void renderFancy() {
    printw("\n");
    int i;
    for (i = 0; i < TOTALSIZE(); i++) {

        // M is special block
        if (env[i] == 'M') {
            addch((char)0x2588);
        } else if (env[i] == '|' || env[i] == '\\' || env[i] == '/' || env[i] == 'P') {
            init_pair(1, COLOR_BLUE, COLOR_BLACK);
            attron(COLOR_PAIR(1));
            printw("%c", env[i]);
            attroff(COLOR_PAIR(1));
        } else if (env[i] == 'G') {
            init_pair(2, COLOR_YELLOW, COLOR_BLACK);
            attron(COLOR_PAIR(2));
            printw("%c", env[i]);
            attroff(COLOR_PAIR(2));
        } else {
            // here is a fun part
            attron(COLOR_PAIR(5));
            init_pair(5, rand() % 7 + 1, COLOR_BLACK);
            printw("%c", env[i]);
            attroff(COLOR_PAIR(5));
        }

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
    int i;
    for (i = 0; i < multi; i++) {
        printw("%c", c);
    }
}

/**
 * A horizontal seperator
 */
void sep() {
    characterMultiply('-', 60);
    printw("\n");
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
    int y = rand() % 10;
    int x = rand() % WIDTH;
    return vector(x, y, grid);
}

/**
 * get random index based on len of single dimensional array
 * @return random index
 */
int getrandomvector(int limit, int add) {
    if (limit == 0) {
        return rand() % TOTALSIZE() + add;
    } else {
        return rand() % limit + add;
    }
}

/**
 * get index of empty slot from character grid
 * @param  grid a single dimensional array
 * @return      `i` index of empty slot
 */
int getemptyslot(char grid[], int limit, int offset) {
    while (1) {
        // try to place in first two lines
        int r = getrandomvector(limit, offset);
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
    int index = getemptyslot(grid, WIDTH*2, 0);
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

int toggle = 1;

/**
 * move player if empty slot
 * @param move Possible Values: MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT
 * @param grid A single dimenstional array
 */
void moveplayer(int move, char grid[]) {
    toggle = !toggle;
    if (move == MOVE_UP || move == MOVE_DOWN) {
        PLAYER = '|';
    } else {
        PLAYER = toggle ? '\\' : '/';
    }
    // PLAYER = CONSTUMES[MOVES % NO_OF_CONSTUMES];
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
