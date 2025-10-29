#include <algebra.h>
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <stdio.h>
#include <stdlib.h>

void setup(void) { puts("Tests for algebra module"); }

Test(algebra, subPolEz) {
  int as = 6, bs = 3, rs = as + bs;
  struct polDef *a = malloc(sizeof(struct polDef) * as);
  a[0] = (struct polDef){5, 1, 1, 1, 1};
  a[1] = (struct polDef){10, 1, 1, 0, 0};
  a[2] = (struct polDef){1, 1, 1, 1, 1};
  a[3] = (struct polDef){2, 1, 1, 1, 1};
  a[4] = (struct polDef){1, 0, 0, 1, 1};
  a[5] = (struct polDef){3, 0, 0, 1, 1};

  struct polDef *b = malloc(sizeof(struct polDef) * bs);
  b[0] = (struct polDef){10, 1, 1, 1, 1};
  b[1] = (struct polDef){2, 1, 1, 0, 0};
  b[2] = (struct polDef){3, 0, 0, 1, 1};
  struct polDef *res = malloc(sizeof(struct polDef) * rs);

  subPol(a, &as, b, &bs, res, &rs);
  res = realloc(res, sizeof(struct polDef) * rs);
  cr_expect(res[0].c == -2);
  cr_expect(res[1].c == 8);
  cr_expect(res[2].c == 1);
}

Test(algebra, sumPolEz) {
  int as = 3, bs = 3, rs = as + bs;
  struct polDef *a = malloc(sizeof(struct polDef) * as);
  a[0] = (struct polDef){1, 1, 2, 0, 0};
  a[1] = (struct polDef){5, 1, 1, 0, 0};
  a[2] = (struct polDef){2, 0, 0, 0, 0};
  struct polDef *b = malloc(sizeof(struct polDef) * bs);
  b[0] = (struct polDef){10, 1, 2, 0, 0};
  b[1] = (struct polDef){2, 1, 1, 0, 0};
  b[2] = (struct polDef){3, 0, 0, 0, 0};

  struct polDef *res = malloc(sizeof(struct polDef) * rs);

  sumPol(a, &as, b, &bs, res, &rs);

  cr_expect(res[0].c == 11);
  cr_expect(res[1].c == 7);
  cr_expect(res[2].c == 5);
}
