#ifndef FILEHANDLER_H_
#define FILEHANDLER_H_

#include <stdio.h>
#include <string.h>
#include <ncurses.h>

#define SVFILE "savefile"
#define LBFILE "leaderboard"
#define TMPFILE "xtemporaryxFilexForxLeaderboardx123x"

typedef struct {
  char name[4];
  int pcts;
} Scor;

int saveGame(int **);
int loadGame(int **);
int touchSave();
Scor getScore(char, char []);
int pushScore(Scor, char []);
int deleteScoreByName(Scor);
int permuteScore(int, int);
long int getFilesize(char []);
int addScoreByNum(Scor);

#endif // FILEHANDLER_H_
