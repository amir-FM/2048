#include "game.h"

int game(char isResumed) {
  int **mat;
  int swaps, scor = 0;
  randInit();
  mat = matInit();
  if (isResumed == 1)
    loadGame(mat);
  else {
    randCellGen(mat);
    randCellGen(mat);
  }
  timeout(TIMEOUT * 1000);
  int c, makeMove = 0;
  matShow(mat);
  panel(scor);
  move(0, 0);
  refresh();

  while ((c = getch()) != 'q') {
    swaps = 0;
    if (c == ERR) {
      // dupa MOVETIME secunde celulele se deplaseaza
      // in directia data de autoSolve(mat)
      makeMove++;
      if (makeMove == MOVETIME) {
        swaps = gameMove(mat, &scor, autoSolve(mat));
        makeMove = 0;
      }
    } else {
      makeMove = 0;
      // daca tasta nu corespunde unei directii
      // nu se face nicio miscare
      int dir = keyInterpreter(c);
      if (dir != -1) swaps = gameMove(mat, &scor, dir);
    }
    // daca celulele s-au miscat se adauga o noua casuta
    if (swaps != 0) randCellGen(mat);
    matShow(mat);
    panel(scor);

    if (isSol(mat) == 1) {
      timeout(-1);
      mvprintw(LINE + 4, ROW, "You won! You are a champion!");
      savePanel(scor);
      remove(SVFILE);
      return 0;
    }
    if (canMove(mat) == 0) {
      timeout(-1);
      mvprintw(LINE + 4, ROW, "You lost! Don't give up!");
      savePanel(scor);
      remove(SVFILE);
      return 0;
    }
    refresh();
  }
  saveGame(mat);
  matFree(mat);
  return 0;
}

void randInit() { srand(time(NULL)); }

int **matInit() {
  int **mat, i;
  mat = (int **)malloc(MATSIZE * sizeof(int *));
  for (i = 0; i < MATSIZE; i++) mat[i] = (int *)calloc(MATSIZE, sizeof(int));
  return mat;
}

// se genereaza o celula la intamplare cu un numar
// din intervalul [0, 15] corespunzatoare unei casete
// din matrice
void randCellGen(int **mat) {
  int caseta, nr;
  do {
    caseta = randNum(16);
  } while (mat[caseta / 4][caseta % 4] != 0);
  nr = randNum(2);
  mat[caseta / 4][caseta % 4] = nr ? 4 : 2;
}

// genereaza un numar la intamplare din intervalul [0, a-1]
int randNum(int a) {
  int r = rand();
  return r % a;
}

int moveEast(int **mat, int *scor) {
  int i, j, k, combo, swaps = 0;
  for (i = 0; i < MATSIZE; i++) {
    combo = 0;
    for (j = MATSIZE - 2; j >= 0; j--) {
      if (mat[i][j]) {
        k = j + 1;
        while (mat[i][k] == 0 && k < MATSIZE - combo - 1) k++;
        if (mat[i][k] == mat[i][j]) {
          mat[i][k] *= 2;
          mat[i][j] = 0;
          *scor += mat[i][k];
          combo++;
          swaps++;
        } else {
          if (mat[i][k] == 0) {
            mat[i][k] = mat[i][j];
            mat[i][j] = 0;
            swaps++;
          } else {
            mat[i][k - 1] = mat[i][j];
            if (k - 1 != j) {
              mat[i][j] = 0;
              swaps++;
            }
          }
        }
      }
    }
  }
  return swaps;
}

int moveWest(int **mat, int *scor) {
  int i, j, k, combo, swaps = 0;
  for (i = 0; i < MATSIZE; i++) {
    combo = 0;
    for (j = 1; j < MATSIZE; j++) {
      if (mat[i][j]) {
        k = j - 1;
        while (mat[i][k] == 0 && k > combo) k--;
        if (mat[i][k] == mat[i][j]) {
          mat[i][k] *= 2;
          mat[i][j] = 0;
          *scor += mat[i][k];
          combo++;
          swaps++;
        } else {
          if (mat[i][k] == 0) {
            mat[i][k] = mat[i][j];
            mat[i][j] = 0;
            swaps++;
          } else {
            mat[i][k + 1] = mat[i][j];
            if (k + 1 != j) {
              mat[i][j] = 0;
              swaps++;
            }
          }
        }
      }
    }
  }
  return swaps;
}

int moveNorth(int **mat, int *scor) {
  int i, j, k, combo, swaps = 0;
  for (j = 0; j < MATSIZE; j++) {
    combo = 0;
    for (i = 1; i < MATSIZE; i++) {
      if (mat[i][j]) {
        k = i - 1;
        while (mat[k][j] == 0 && k > combo) k--;
        if (mat[k][j] == mat[i][j]) {
          mat[k][j] *= 2;
          mat[i][j] = 0;
          *scor += mat[k][j];
          combo++;
          swaps++;
        } else {
          if (mat[k][j] == 0) {
            mat[k][j] = mat[i][j];
            mat[i][j] = 0;
            swaps++;
          } else {
            mat[k + 1][j] = mat[i][j];
            if (k + 1 != i) {
              mat[i][j] = 0;
              swaps++;
            }
          }
        }
      }
    }
  }
  return swaps;
}

int moveSouth(int **mat, int *scor) {
  int i, j, k, combo, swaps = 0;
  for (j = 0; j < MATSIZE; j++) {
    combo = 0;
    for (i = MATSIZE - 2; i >= 0; i--) {
      if (mat[i][j]) {
        k = i + 1;
        while (mat[k][j] == 0 && k < MATSIZE - combo - 1) k++;
        if (mat[k][j] == mat[i][j]) {
          mat[k][j] *= 2;
          mat[i][j] = 0;
          *scor += mat[k][j];
          combo++;
          swaps++;
        } else {
          if (mat[k][j] == 0) {
            mat[k][j] = mat[i][j];
            mat[i][j] = 0;
            swaps++;
          } else {
            mat[k - 1][j] = mat[i][j];
            if (k - 1 != i) {
              mat[i][j] = 0;
              swaps++;
            }
          }
        }
      }
    }
  }
  return swaps;
}

// afisare matrice
void matShow(int **mat) {
  int i, j, pair;
  for (i = 0; i < MATSIZE; i++) {
    for (j = 0; j < MATSIZE; j++) {
      pair = cellColor(mat[i][j]);
      if (mat[i][j])
        attron(COLOR_PAIR(pair));
      else
        attron(A_DIM | (COLOR_PAIR(pair)));
      mvprintw(CELL_HEIGHT * i, CELL_WIDTH * j, "%10c", ' ');
      mvprintw(CELL_HEIGHT * i + 1, CELL_WIDTH * j, "%10c", ' ');
      mvprintw(CELL_HEIGHT * i + 2, CELL_WIDTH * j, "   %4d   ", mat[i][j]);
      mvprintw(CELL_HEIGHT * i + 3, CELL_WIDTH * j, "%10c", ' ');
      mvprintw(CELL_HEIGHT * i + 4, CELL_WIDTH * j, "%10c", ' ');
      if (mat[i][j])
        attroff(COLOR_PAIR(pair));
      else
        attroff(A_DIM | (COLOR_PAIR(pair)));
    }
    printw("\n");
  }
}

// verifica daca mai exista mutari
int canMove(int **mat) {
  int temp = 0, **dup, ok = 0;
  dup = matInit();
  matDup(mat, dup);
  if (moveEast(dup, &temp) != 0) ok = 1;
  if (moveWest(dup, &temp) != 0) ok = 1;
  if (moveNorth(dup, &temp) != 0) ok = 1;
  if (moveSouth(dup, &temp) != 0) ok = 1;
  matFree(dup);
  return (ok ? 1 : 0);
}

void matDup(int **mat, int **dup) {
  int i, j;
  for (i = 0; i < MATSIZE; i++)
    for (j = 0; j < MATSIZE; j++) dup[i][j] = mat[i][j];
}

void matFree(int **mat) {
  int i;
  for (i = 0; i < MATSIZE; i++) free(mat[i]);
  free(mat);
}

int isSol(int **mat) {
  int i, j;
  for (i = 0; i < MATSIZE; i++)
    for (j = 0; j < MATSIZE; j++)
      if (mat[i][j] == 2048) return 1;
  return 0;
}

// alege minimul dintre numarul de celule care exista dupa
// fiecare mutare corespunzatoare directiilor
int autoSolve(int **mat) {
  int **dup, temp = 0, i, moved;
  int options[MATSIZE + 1], min = MATSIZE;
  dup = matInit();

  for (i = 0; i < MATSIZE; i++) {
    matDup(mat, dup);
    moved = gameMove(dup, &temp, i);
    if (moved > 0)
      options[i] = cellCount(dup);
    else
      options[i] = -1;
  }

  options[min] = 17;
  for (i = 0; i < MATSIZE; i++) {
    if (options[i] < options[min] && options[i] > 0) min = i;
  }
  return min;
}

int cellCount(int **mat) {
  int i, j, contor = 0;
  for (i = 0; i < MATSIZE; i++)
    for (j = 0; j < MATSIZE; j++)
      if (mat[i][j] != 0) contor++;
  return contor;
}

int gameMove(int **mat, int *scor, int dir) {
  int swaps;
  switch (dir) {
    case 0:
      swaps = moveWest(mat, scor);
      break;
    case 1:
      swaps = moveEast(mat, scor);
      break;
    case 2:
      swaps = moveNorth(mat, scor);
      break;
    case 3:
      swaps = moveSouth(mat, scor);
      break;
  }
  return swaps;
}
