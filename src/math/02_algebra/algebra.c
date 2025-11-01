#include "algebra.h"
#include <limits.h>
#include <math.h>

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct quadEq *quadraticEquation(int *a, int *b, int *c) {
  struct quadEq *res = malloc(sizeof(struct quadEq));

  double a_d = (double)*a;
  double b_d = (double)*b;
  double c_d = (double)*c;

  double dis = sqrt(b_d * b_d - 4 * a_d * c_d);
  printf("Dis - %f\n", (-b_d + dis) / (2 * a_d));
  if (dis > 0) {
    res->x1 = (-b_d + dis) / (2 * a_d);
    res->x2 = (-b_d - dis) / (2 * a_d);
  } else if (dis == 0) {
    res->x1 = -(b_d / (2 * a_d));
    res->x2 = 0;
  } else {
    res->x1 = 0;
    res->x2 = 0;
  }
  return res;
}

void sumator(struct polDef *res, int *rsize) {
  for (int i = 0; i < *rsize - 1; i++) {
    for (int j = i + 1; j < *rsize; j++) {
      if (res[i].x == res[j].x && res[i].y == res[j].y &&
          res[i].dx == res[j].dx && res[i].dy == res[j].dy) {
        res[i] = (struct polDef){res[i].c + res[j].c, res[i].x, res[i].dx,
                                 res[i].y, res[i].dy};
        res[j] = (struct polDef){0, 0, 0, 0, 0};
      }
    }
  }
}

void sumPol(struct polDef *f, int *f_s, struct polDef *s, int *s_s,
            struct polDef *res, int *rsize) {
  const size_t sizeof_first = sizeof(*f) * *f_s;
  const size_t sizeof_second = sizeof(*s) * *s_s;
  memcpy(res, f, sizeof_first);
  memcpy(&res[*f_s], s, sizeof_second);
  sumator(res, rsize);
}

void subPol(struct polDef *f, int *f_s, struct polDef *s, int *s_s,
            struct polDef *res, int *rsize) {
  struct polDef *sT = malloc(sizeof(struct polDef) * *s_s);
  for (int i = 0; i < *s_s; i++) {
    sT[i] = (struct polDef){-s[i].c, s[i].x, s[i].dx, s[i].y, s[i].dy};
  }
  sumPol(f, f_s, sT, s_s, res, rsize);
  free(sT);
}

void mulPol(struct polDef *f, int *f_s, struct polDef *s, int *s_s,
            struct polDef *res, int *rsize) {
  int n = 0;

  for (int i = 0; i < *f_s; i++) {
    for (int j = 0; j < *s_s; j++) {
      res[n].c = f[i].c * s[j].c;
      res[n].dx = f[i].dx + s[j].dx;
      res[n].dy = f[i].dy + s[j].dy;
      res[n].x = (f[i].x == 1 || s[j].x == 1) ? 1 : f[i].x + s[j].x;
      res[n].y = (f[i].y == 1 || s[j].y == 1) ? 1 : f[i].y + s[j].y;
      n++;
    }
  }
}

void divPol(struct polDef *f, int *f_s, struct polDef *s, int *s_s,
            struct polDef *res, int *rsize, struct polDef *rem, int *remsize) {
  int hD = (f[getHighestTerm(f, f_s)].dx > f[getHighestTerm(f, f_s)].dy)
               ? getHighestTerm(f, f_s)
               : f[getHighestTerm(f, f_s)].dy;
  int hDi = (f[getHighestTerm(f, f_s)].dx > f[getHighestTerm(f, f_s)].dy)
                ? f[getHighestTerm(f, f_s)].dx
                : f[getHighestTerm(f, f_s)].dy;
  int hDivI = (s[getHighestTerm(s, s_s)].dx > s[getHighestTerm(s, s_s)].dy)
                  ? s[getHighestTerm(s, s_s)].dx
                  : s[getHighestTerm(s, s_s)].dy;
  if (hD < hDi || hD < hDi)
    return;

  int tmpSize = sizeof(struct polDef) * *f_s;
  struct polDef *tmp = malloc(tmpSize);
  tmp = memcpy(tmp, f, tmpSize);
  // printPol(tmp, f_s);
  struct polDef *ans = malloc(sizeof(struct polDef) * *f_s);
  int t = sizeof(struct polDef) * 1;
  struct polDef *temp = malloc(t);

  temp[0].c = (tmp[hD].c == 1) ? 1 : tmp[hD].c / s[hDi].c;
  temp[0].x = (tmp[hD].x == 1) ? 1 : 0;
  temp[0].y = (tmp[hD].y == 1) ? 1 : 0;
  temp[0].dx = (temp[0].x == 0) ? 0 : tmp[hD].dx - s[hDi].dx;
  temp[0].dy = (temp[0].y == 0) ? 0 : tmp[hD].dy - s[hDi].dy;
  printPol(temp, &t);
  mulPol(temp, &t, s, s_s, ans, f_s);
  printPol(ans, f_s);
  subPol(tmp, &tmpSize, ans, f_s, tmp, &tmpSize);
  printPol(tmp, &tmpSize);
}

void polSimplefire(struct polDef *pd, int *s) {
  int k = 0;
  for (int i = 0; i < *s; i++) {
    if (pd[i].x == 0 && pd[i].y == 0 && pd[i].c == 0)
      continue;
    for (int j = *s - 1; j > i; j--) {
      if (pd[j].x == 0 && pd[j].y == 0 && pd[j].c == 0)
        continue;
      if (pd[i].x == pd[j].x && pd[i].y == pd[j].y && pd[i].dx == pd[j].dx &&
          pd[i].dy == pd[j].dy) {
        pd[i].c += pd[j].c;
        pd[j].c = 0;
        pd[j].x = 0;
        pd[j].y = 0;
        pd[j].dx = 0;
        pd[j].dy = 0;
        moveNullPol(pd, s, j);
        k += 1;
      }
    }
  }
  *s -= k;
}

void moveNullPol(struct polDef *pd, int *s, int z) {
  if ((pd[z + 1].c == 0 && pd[z + 1].x == 0 && pd[z + 1].y == 0) ||
      (z == *s - 1))
    return;
  int l = getLastNotNullPol(pd, *s - 1);
  pd[z].c = pd[l].c;
  pd[z].x = pd[l].x;
  pd[z].y = pd[l].y;
  pd[z].dx = pd[l].dx;
  pd[z].dy = pd[l].dy;

  pd[l].c = 0;
  pd[l].x = 0;
  pd[l].y = 0;
  pd[l].dx = 0;
  pd[l].dy = 0;
}

int getLastNotNullPol(struct polDef *pd, int n) {
  if (pd[n].c != 0 || pd[n].x != 0 || pd[n].y != 0) {
    return n;
  }
  n -= 1;
  getLastNotNullPol(pd, n);
}

int getZeros(struct polDef *pd, int *n) {
  int k = 0;
  for (int i = 0; i < *n; i++) {
    if (pd[i].c == 0 && pd[i].x == 0 && pd[i].y == 0)
      k++;
  }
  return k;
}

void polSort(struct polDef *pd, int *s) {}

int getHighestTerm(struct polDef *pd, int *s) {
  int hT = 0;
  for (int i = 1; i < *s; i++) {
    if (pd[i].dx > pd[hT].dx)
      hT = i;
  }
  return hT;
}

void swapPolVar(struct polDef *a, struct polDef *b) {
  struct polDef *t = malloc(sizeof(struct polDef) * 1);
  *t = *a;
  *a = *b;
  *b = *t;
  free(t);
}

void printPol(struct polDef *pd, int *s) {
  for (int i = 0; i < *s; i++) {
    if (pd[i].c == 0)
      continue;
    if (i != 0 && pd[i].c > 0)
      printf("+");
    if (pd[i].c != 1)
      printf("%d", pd[i].c);
    if (pd[i].x == 1)
      printf("%c", 'x');
    if (pd[i].dx > 1)
      printf("^(%d)", pd[i].dx);
    if (pd[i].y == 1)
      printf("%c", 'y');
    if (pd[i].dy > 1)
      printf("^(%d)", pd[i].dy);
  }
  printf("\n");
}
