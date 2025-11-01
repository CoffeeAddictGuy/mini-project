
struct quadEq {
  double x1;
  double x2;
};

struct polDef {
  int c;
  int x;
  int dx;
  int y;
  int dy;
};

struct quadEq* quadraticEquation(int *a, int *b, int *c);

void sumPol(struct polDef* pd, int* f_s, struct polDef* s, int* s_s, struct polDef *res, int *rsize);
void subPol(struct polDef *f, int *f_s, struct polDef *s, int *s_s, struct polDef *res, int *rsize);
void mulPol(struct polDef *f, int* f_s, struct polDef *s, int* s_s, struct polDef *res, int *rsize);
void divPol(struct polDef *f, int* f_s, struct polDef *s, int* s_s, struct polDef *res, int *rsize, struct polDef *rem, int *remsize);

void polSimplefire(struct polDef *pd, int* s);
void moveNullPol(struct polDef *pd, int* s, int z);
int getLastNotNullPol(struct polDef *pd, int n);
int getZeros(struct polDef *pd, int *n);
void polSort(struct polDef *pd, int* s);
int getHighestTerm(struct polDef *pd, int *s);

void printPol(struct polDef* pd, int* s);
void swapPol(struct polDef *a, struct polDef *b);
