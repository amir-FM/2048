#ifndef PANEL_H_
#define PANEL_H_

#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>
#include "fileHandler.h"

#define ROW 60
#define LINE 10

void panel(int);
void printTime();
void leaderboard();
void saveScore(int);
void savePanel(int);

#endif // PANEL_H_
