#include "panel.h"

void panel(int scor) {
  printTime();
  mvprintw(LINE + 2, ROW, "Score: %d", scor);
  mvprintw(LINE + 3, ROW, "< ^ v > / w a s d and q");
}

void printTime() {
  time_t aux;
  struct tm *t;
  aux = time(NULL);
  t = localtime(&aux);
  mvprintw(LINE, ROW, "%02d.%02d.%d\n", t->tm_mday, t->tm_mon + 1,
           t->tm_year + 1900);
  mvprintw(LINE + 1, ROW, "%02d:%02d:%02d\n", t->tm_hour, t->tm_min, t->tm_sec);
}

void leaderboard() {

  char logo[] =
"  _                    _           _                         _\n\
 | |                  | |         | |                       | |\n\
 | |     ___  __ _  __| | ___ _ __| |__   ___   __ _ _ __ __| |\n\
 | |    / _ \\/ _` |/ _` |/ _ \\ '__| '_ \\ / _ \\ / _` | '__/ _` |\n\
 | |___|  __/ (_| | (_| |  __/ |  | |_) | (_) | (_| | | | (_| |\n\
 |______\\___|\\__,_|\\__,_|\\___|_|  |_.__/ \\___/ \\__,_|_|  \\__,_|";


  Scor s = {"MAX", 52};
  int dim, i;

  dim = (int)(getFilesize(LBFILE) / sizeof(Scor));

  move(0, 0);
  printw("%s\n\n", logo);
  printw("_______________\n");
  for (i = 0; i < dim; i++) {
    if (i == 0)
      s = getScore(1, LBFILE);
    else
      s = getScore(0, LBFILE);
    printw("%s %d\n", s.name, s.pcts);
  }
  printw("\nPress any key to return to the menu...");
  getch();
}

// functia care construieste variabila
// de tip Scor si o trimite pentru scriere
void saveScore(int scor) {
  char aux[3];
  Scor s;
  echo();
  scanw("%3s", aux);
  strcpy(s.name, aux);
  s.pcts = scor;
  noecho();
  addScoreByNum(s);
}

// panoul de salvare a scorului din joc
void savePanel(int scor) {
  char c;

  mvprintw(LINE + 5, ROW, "Save score? (y/n)");
  do {
    c = getch();
  } while (c != 'y' && c != 'n');
  printw("%c", c);
  if (c == 'y') {
    mvprintw(LINE + 6, ROW, "Name (3 chars): ");
    saveScore(scor);
  }
}
