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

void sumPol(int *f, int *f_s, int *s, int *s_s, int *res) {
  int n = (*f_s > *s_s) ? *f_s : *s_s;

  for (int i = 0; i < n; i++) {
    int a = (i < *f_s) ? f[i] : 0;
    int b = (i < *s_s) ? s[i] : 0;
    res[i] = a + b;
  }
}

void subPol(int *f, int *f_s, int *s, int *s_s, int *res) {
  int n = (*f_s > *s_s) ? *f_s : *s_s;

  for (int i = 0; i < n; i++) {
    int a = (i < *f_s) ? f[i] : 0;
    int b = (i < *s_s) ? s[i] : 0;
    res[i] = a - b;
  }
}

void mulPol(int *f, int *f_s, int *s, int *s_s, int *res) {}

struct polDef *sumPolNew(struct polDef *f, int *f_s, struct polDef *s,
                         int *s_s) {
  polSimplefire(f, f_s);
  polSimplefire(s, s_s);

  struct polDef *res = malloc(sizeof(struct polDef) * (*f_s + *s_s));
  int b = (*f_s > *s_s) ? *f_s : *s_s;
  int l = (*f_s > *s_s) ? *s_s : *f_s;

  for (int i = 0; i < b; i++) {
    for (int j = 0; j < l; j++) {
      if (f[i].px == s[i].px && f[i].py == s[i].py) {
        res[i].c = f[i].c + s[i].c;
        res[i].px = f[i].px;
        res[i].py = f[i].py;
      }
    }
  }
  return res;
}

void polSimplefire(struct polDef *pd, int *s) {
  int k = 0;
  for (int i = 0; i < *s; i++) {
    if (pd[i].px == 0 && pd[i].py == 0 && pd[i].c == 0)
      continue;
    for (int j = *s - 1; j > i; j--) {
      if (pd[i].px == pd[j].px && pd[i].py == pd[j].py) {
        k += 1;
        pd[i].c += pd[j].c;
        pd[j].c = 0;
        pd[j].px = 0;
        pd[j].py = 0;
        moveNullPol(pd, s, j, getLastNotNullPol(pd, *s));
      }
    }
  }
  *s -= k;
}

void moveNullPol(struct polDef *pd, int *s, int z, int l) {
  pd[z].c = pd[l].c;
  pd[z].px = pd[l].px;
  pd[z].py = pd[l].py;

  pd[l].c = 0;
  pd[l].px = 0;
  pd[l].py = 0;
}

int getLastNotNullPol(struct polDef *pd, int n) {
  if (pd[n].c != 0 || pd[n].px != 0 || pd[n].py != 0) {
    n -= 1;
    getLastNotNullPol(pd, n);
  }
  return n;
}

void printPol(struct polDef *pd, int *s) {
  for (int i = 0; i < *s; i++) {
    if (pd[i].c == 0)
      continue;
    if (i != 0 && pd[i].c > 0)
      printf("+");
    if (pd[i].c != 1)
      printf("%d", pd[i].c);
    if (pd[i].px == 1)
      printf("%c", 'x');
    if (pd[i].py == 1)
      printf("%c", 'y');
  }
  printf("\n");
}
