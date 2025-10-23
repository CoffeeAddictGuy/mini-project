#include "algebra.h"
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

void printPol(struct polDef *pd, int *s) {
  for (int i = 0; i < *s; i++) {
    if (pd[i].c == 0)
      continue;
    if (i != 0 && pd[i].c > 0)
      printf("+");
    printf("%d", pd[i].c);
    if (pd[i].px == 1)
      printf("%c", 'x');
    if (pd[i].py == 1)
      printf("%c", 'y');
  }
  printf("\n");
}
