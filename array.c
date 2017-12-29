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

int* unboxH(Cell*);
int unboxI(Cell*);
float unboxF(Cell*);
double unboxD(Cell*);
char* unboxS(Cell*);
char unboxC(Cell*);

int main(int argc, char** argv) {
  Cell* array = allocateArray(10);
  setValue(array, 1, (CellT){99}, INTEGER);
  setValue(array, 2, (CellT){.f_val = 55.5f}, FLOAT);
  Cell* a = getValue(array, 1);
  Cell* f = getValue(array, 2);
  printf("%d\n", unboxH(a)(a));
  printf("%f\n", unboxH(f)(f));
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

int unboxI(Cell* c) { return c->val.i_val; }
float unboxF(Cell* c) { return c->val.f_val; }
double unboxD(Cell* c) { return c->val.d_val; }
char* unboxS(Cell* c) { return c->val.s_val; }
char unboxC(Cell* c) { return c->val.c_val; }

int* unboxH(Cell* c) {
  if(c->t == INTEGER) return unboxI;
  else if(c->t == FLOAT) return unboxF;
  else if(c->t == DOUBLE) return unboxD;
  else if(c->t == CHAR) return unboxC;
  else return unboxS;
}
