#include "menu.h"

int menu(){
  char isSave = touchSave();

  char logo[] =
" 222222222222222         000000000            444444444       888888888\n\
2:::::::::::::::22     00:::::::::00         4::::::::4     88:::::::::88\n\
2::::::222222:::::2  00:::::::::::::00      4:::::::::4   88:::::::::::::88\n\
2222222     2:::::2 0:::::::000:::::::0    4::::44::::4  8::::::88888::::::8\n\
            2:::::2 0::::::0   0::::::0   4::::4 4::::4  8:::::8     8:::::8\n\
            2:::::2 0:::::0     0:::::0  4::::4  4::::4  8:::::8     8:::::8\n\
         2222::::2  0:::::0     0:::::0 4::::4   4::::4   8:::::88888:::::8\n\
    22222::::::22   0:::::0 000 0:::::04::::444444::::444  8:::::::::::::8\n\
  22::::::::222     0:::::0 000 0:::::04::::::::::::::::4 8:::::88888:::::8\n\
 2:::::22222        0:::::0     0:::::04444444444:::::4448:::::8     8:::::8\n\
2:::::2             0:::::0     0:::::0          4::::4  8:::::8     8:::::8\n\
2:::::2             0::::::0   0::::::0          4::::4  8:::::8     8:::::8\n\
2:::::2       2222220:::::::000:::::::0          4::::4  8::::::88888::::::8\n\
2::::::2222222:::::2 00:::::::::::::00         44::::::44 88:::::::::::::88\n\
2::::::::::::::::::2   00:::::::::00           4::::::::4   88:::::::::88\n\
22222222222222222222     000000000             4444444444     888888888";


  char options[][12] = {"Resume", "New Game", "Leaderboard", "Quit"};
  int i, cursor = 1, color;
  randInit();
  // se genereaza culori pentru titlu
  color = randNum(10) + 13;
  timeout(-1);
  while (1) {
    attron(COLOR_PAIR(color));
    printw("%s\n\n", logo);
    attroff(COLOR_PAIR(color));
    printw("______________\n");
    for (i = 0; i < OPTIONS; i++) {
      printw("|");
      if (i == 0 && isSave == 0) attron(A_DIM);
      if (i == cursor) attron(A_BLINK);
      printw("%-11s", options[i]);
      if (i == cursor) attroff(A_BLINK);
      if (i == 0 && isSave == 0) attroff(A_DIM);
      printw(" |\n");
    }
    char c = getch();
    if (c == '\n') return cursor;
    switch (keyInterpreter(c)) {
      case 3:
        if (cursor < OPTIONS - 1) cursor++;
        break;
      case 2:
        if (cursor > 1 - isSave) cursor--;
        break;
      default:
        break;
    }
    refresh();
    move(0, 0);
  }
}
