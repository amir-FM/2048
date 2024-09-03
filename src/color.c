#include "color.h"

// initializarea perechilor de culori
// init_pair(nr, fg, bg);
void initColors() {
  start_color();
  init_pair(0, 0, 7);
  init_pair(1, 7, 1);
  init_pair(2, 7, 2);
  init_pair(3, 7, 3);
  init_pair(4, 7, 4);
  init_pair(5, 7, 5);
  init_pair(6, 7, 6);
  init_pair(7, 7, 9);
  init_pair(8, 7, 10);
  init_pair(9, 7, 12);
  init_pair(10, 7, 13);
  init_pair(11, 7, 11);
  init_pair(12, 0, 247);
  init_pair(13, 1, 0);
  init_pair(13, 2, 0);
  init_pair(14, 3, 0);
  init_pair(15, 4, 0);
  init_pair(16, 5, 0);
  init_pair(17, 6, 0);
  init_pair(18, 9, 0);
  init_pair(19, 10, 0);
  init_pair(20, 11, 0);
  init_pair(21, 12, 0);
  init_pair(22, 13, 0);
}

int cellColor(int num) {
  switch (num) {
    default:
    case 0:
      return 12;
    case 2:
      return 1;
    case 4:
      return 2;
    case 8:
      return 3;
    case 16:
      return 4;
    case 32:
      return 5;
    case 64:
      return 6;
    case 128:
      return 7;
    case 256:
      return 8;
    case 512:
      return 9;
    case 1024:
      return 10;
    case 2048:
      return 11;
  }
}
