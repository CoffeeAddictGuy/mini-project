#include "algebra.h"
#include <limits.h>
#include <math.h>

#include <stdio.h>
#include <stdlib.h>

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

void sumPol(struct polDef *f, int *f_s, struct polDef *s, int *s_s,
            struct polDef *res, int *rsize) {
  polSimplefire(f, f_s);
  f = realloc(f, sizeof(struct polDef) * *f_s);
  polSimplefire(s, s_s);
  s = realloc(s, sizeof(struct polDef) * *s_s);

  *rsize = *f_s + *s_s;

  int b = (*f_s > *s_s) ? *f_s : *s_s;
  int l = (*f_s > *s_s) ? *s_s : *f_s;

  for (int i = 0; i < b; i++) {
    for (int j = 0; j < l; j++) {
      if (f[i].x == s[j].x && f[i].y == s[j].y && f[i].dx == s[j].dx &&
          f[i].dy == s[j].dy) {
        res[i].c = f[i].c + s[j].c;
        res[i].x = f[i].x;
        res[i].y = f[i].y;
        res[i].dx = f[i].dx;
        res[i].dy = f[i].dy;
      }
    }
  }
  res = realloc(res, sizeof(struct polDef) * *rsize);
}

void subPol(struct polDef *f, int *f_s, struct polDef *s, int *s_s,
            struct polDef *res, int *rsize) {
  polSimplefire(f, f_s);
  f = realloc(f, sizeof(struct polDef) * *f_s);
  polSimplefire(s, s_s);
  s = realloc(s, sizeof(struct polDef) * *s_s);
  *rsize = *f_s + *s_s;

  int b = (*f_s > *s_s) ? *f_s : *s_s;
  int l = (*f_s > *s_s) ? *f_s : *s_s;
  for (int i = 0; i < b; i++) {
    for (int j = 0; j < l; j++) {
      if (f[i].x == s[j].x && f[i].y == s[j].y && f[i].dx == s[j].dx &&
          f[i].dy == s[j].dy) {
        res[i].c = f[i].c - s[j].c;
        res[i].x = f[i].x;
        res[i].y = f[i].y;
        res[i].dx = f[i].dx;
        res[i].dy = f[i].dy;
      }
    }
  }
  res = realloc(res, sizeof(struct polDef) * *rsize);
}

void mulPol(struct polDef *f, int *f_s, struct polDef *s, int *s_s,
            struct polDef *res, int *rsize) {}

void polSimplefire(struct polDef *pd, int *s) {
  int k = 0;
  for (int i = 0; i < *s; i++) {
    if (pd[i].x == 0 && pd[i].y == 0 && pd[i].c == 0)
      continue;
    for (int j = *s - 1; j > i; j--) {
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
  if (pd[z + 1].c == 0 && pd[z + 1].x == 0 && pd[z + 1].y == 0)
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
