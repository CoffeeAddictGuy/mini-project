
struct quadEq {
  double x1;
  double x2;
};

struct polDef {
  int c;
  int px;
  int py;
};

struct quadEq* quadraticEquation(int *a, int *b, int *c);
void sumPol(int* f, int* f_s, int* s, int* s_s, int *res);
void subPol(int* f, int* f_s, int* s, int* s_s, int *res);
void mulPol(int* f, int* f_s, int* s, int* s_s, int *res);
void printPol(struct polDef* pd, int* s);
