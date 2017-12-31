#include <stdio.h>
#include <stdlib.h>

union u_Cell {
  int i_val;
  float f_val;
  double d_val;
  char* s_val;
  char c_val;
};
typedef union u_Cell CellT;

typedef enum {INTEGER, FLOAT, DOUBLE, STRING, CHAR} type;

struct t_Cell {
  union u_Cell val;
  type t;
};
typedef struct t_Cell Cell;

Cell* allocateArray(int);
void setValue(Cell*, int index, union u_Cell val, type);
Cell* getValue(Cell*, int);

void unboxI(Cell*, int*);
void unboxF(Cell*, float*);
void unboxD(Cell*, double*);
void unboxS(Cell*, char**);
void unboxC(Cell*, char*);
typeof(&unboxI) unboxH(Cell*);

int main(int argc, char** argv) {
  Cell* array = allocateArray(10);
  setValue(array, 1, (CellT){99}, INTEGER);
  setValue(array, 2, (CellT){.f_val = 55.5f}, FLOAT);
  Cell* a = getValue(array, 1);
  Cell* f = getValue(array, 2);
  int res;
  float fres;
  unboxH(a)(a, &res);
  unboxH(f)(f, &fres);
  printf("%d\n", res);
  printf("%f\n", fres);
  return 0;
}

Cell* allocateArray(int s) {
  return malloc(s * sizeof(Cell));
}

void setValue(Cell* a, int index, union u_Cell val, type t) {
  *(a + index) = (Cell) {val, t};
}

Cell* getValue(Cell* a, int index) {
  return a + index;
}

void unboxI(Cell* c, int* r) { *r = c->val.i_val; }
void unboxF(Cell* c, float* r) { *r = c->val.f_val; }
void unboxD(Cell* c, double* r) { *r = c->val.d_val; }
void unboxS(Cell* c, char** r) { *r = c->val.s_val; }
void unboxC(Cell* c, char* r) { *r = c->val.c_val; }

typeof(&unboxI) unboxH(Cell* c) {
  if(c->t == INTEGER) return unboxI;
  else if(c->t == FLOAT) return unboxF;
  else if(c->t == DOUBLE) return unboxD;
  else if(c->t == CHAR) return unboxC;
  else return unboxS;
}
