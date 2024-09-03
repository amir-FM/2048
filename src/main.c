#include "main.h"

int main() {
  int mode = 0;

  initscr();
  noecho();
  initColors();
  curs_set(0);
  while (mode != 3) {
    mode = menu();
    clear();
    switch (mode) {
      case 0:
        game(1);
        break;
      case 1:
        game(0);
        break;
      case 2:
        leaderboard();
        break;
      default:
        break;
    }
    clear();
  }
  endwin();
  return 0;
}
