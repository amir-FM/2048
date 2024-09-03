#include "fileHandler.h"

int saveGame(int **mat) {
  int i;
  FILE *fp;
  fp = fopen(SVFILE, "wb");
  if (fp == NULL) return 1;
  for (i = 0; i < 4; i++) fwrite(mat[i], sizeof(int), 4, fp);
  fclose(fp);
  return 0;
}

int loadGame(int **mat) {
  int i;
  FILE *fp;
  fp = fopen(SVFILE, "rb");
  if (fp == NULL) return 1;
  for (i = 0; i < 4; i++) fread(mat[i], sizeof(int), 4, fp);
  fclose(fp);
  return 0;
}

// verifica daca exista fisierul SVFILE
int touchSave() {
  FILE *fp;
  fp = fopen(SVFILE, "rb");
  if (fp != NULL)
    return 1;
  else
    return 0;
}

Scor getScore(char reset, char target[]) {
  static int cursor;
  FILE *fp;
  Scor s;
  if (reset == 1) cursor = 0;

  fp = fopen(target, "rb");
  fseek(fp, cursor * sizeof(Scor), SEEK_SET);
  fread(&s, sizeof(Scor), 1, fp);
  cursor++;
  return s;
}

// adauga un Scor la finalul fisierului target
int pushScore(Scor s, char target[]) {
  FILE *fp;
  fp = fopen(target, "ab");
  if (fp == NULL) return 1;
  fwrite(&s, sizeof(Scor), 1, fp);
  fclose(fp);
  return 0;
}

// sterge toate instantele scorului t din
// fisierul LBFILE
int deleteScoreByName(Scor s) {
  Scor t;
  int dim, i;

  remove(TMPFILE);
  dim = (int)(getFilesize(LBFILE) / sizeof(Scor));

  for (i = 0; i < dim; i++) {
    if (i == 0)
      t = getScore(1, LBFILE);
    else
      t = getScore(0, LBFILE);

    if (strcmp(t.name, s.name) != 0) {
      pushScore(t, TMPFILE);
    }
  }

  rename(TMPFILE, LBFILE);

  return 0;
}

// returneaza dimensiunea fisierului
long int getFilesize(char target[]) {
  long int size;

  FILE *fp = fopen(target, "rb");
  if (fp == NULL) return 0;

  fseek(fp, 0, SEEK_END);
  size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  return size;
}

// verifica daca mai exista un scor cu acelasi nume
// apoi adauga la fisierul LBFILE scorul a.i. ele sa
// fie ordonate descrescator
int addScoreByNum(Scor s) {
  int dim = (int)(getFilesize(LBFILE) / sizeof(Scor));
  int i, merged = 0;
  Scor t;

  // daca fisierul nu exista/este gol se adauga
  // automat scorul
  if (dim == 0) {
    pushScore(s, LBFILE);
    return 1;
  }

  remove(TMPFILE);

  deleteScoreByName(s);
  dim = (int)(getFilesize(LBFILE) / sizeof(Scor));

  for (i = 0; i < dim; i++) {
    if (i == 0)
      t = getScore(1, LBFILE);
    else
      t = getScore(0, LBFILE);
    if (t.pcts <= s.pcts && merged == 0) {
      pushScore(s, TMPFILE);
      merged = 1;
    }
    pushScore(t, TMPFILE);
  }

  if (merged == 0) pushScore(s, TMPFILE);

  rename(TMPFILE, LBFILE);
  return 0;
}
