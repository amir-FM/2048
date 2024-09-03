#ifndef GAME_H_
#define GAME_H_

#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "fileHandler.h"
#include "panel.h"
#include "color.h"
#include "keys.h"

#define MATSIZE 4
#define TIMEOUT 1
#define MOVETIME 30
#define CELL_HEIGHT 5
#define CELL_WIDTH 10

int game(char);
void randInit();
int **matInit();
void randCellGen(int **);
int randNum(int);
int moveEast(int **, int *);
int moveWest(int **, int *);
int moveNorth(int **, int *);
int moveSouth(int **, int *);
int gameMove(int **, int *, int);
int canMove(int **);
void matShow(int **);
void matDup(int **, int **);
void matFree(int **);
int isSol(int **);
int autoSolve(int **);
int cellCount(int **);
void initColors();

#endif // GAME_H_
