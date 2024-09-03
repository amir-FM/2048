#include "keys.h"

int keyInterpreter(char c) {
  int returnedValue;
  if (c == '\033')
    returnedValue = arrows();
  else
    returnedValue = wasd(c);
  return returnedValue;
}

int arrows() {
  getch();
  switch (getch()) {
    case 'A':  // arrow up
      return 2;
    case 'B':  // arrow down
      return 3;
    case 'C':  // arrow right
      return 1;
    case 'D':  // arrow left
      return 0;
  }
  return -1;
}

int wasd(char c) {
  switch (c) {
    case 'a':
      return 0;
    case 'd':
      return 1;
    case 'w':
      return 2;
    case 's':
      return 3;
  }
  return -1;
}
