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

struct t_vec {
  Cell* v;
  int size;
};
typedef struct t_vec Vector;

Cell* allocateArray(int);
void setValue(Cell*, int index, union u_Cell val, type);
Cell* getValue(Cell*, int);
Cell* resize(Cell*, int);
void initVector(Vector*);

typedef void (*unbox) (Cell*, void*);
void unboxI(Cell*, void*);
void unboxF(Cell*, void*);
void unboxD(Cell*, void*);
void unboxS(Cell*, void*);
void unboxC(Cell*, void*);
unbox unboxH(Cell*);

int main(int argc, char** argv) {
  Vector v = {.size = 10};
  initVector(&v);
  setValue(v.v, 1, (CellT){99}, INTEGER);
  setValue(v.v, 2, (CellT){.f_val = 55.5f}, FLOAT);
  Cell* a = getValue(v.v, 1);
  Cell* f = getValue(v.v, 2);
  int res;
  float fres;
  unboxH(a)(a, &res);
  unboxH(f)(f, &fres);
  printf("%d\n", res);
  printf("%f\n", fres);
  free(v.v);
}

void initVector(Vector* v) {
  if(v->size <= 0) {
    fprintf(stderr, "Size cannot be less than or equal to 0");
    exit(1);
  }
  v->v = allocateArray(v->size);
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

Cell* resize(Cell* a, int f) {
  return realloc(a, f * sizeof(Cell));
}

void unboxI(Cell* c, void* r) { *(int*)r = c->val.i_val; }
void unboxF(Cell* c, void* r) { *(float*)r = c->val.f_val; }
void unboxD(Cell* c, void* r) { *(double*)r = c->val.d_val; }
void unboxS(Cell* c, void* r) { *(char**)r = c->val.s_val; }
void unboxC(Cell* c, void* r) { *(char*)r = c->val.c_val; }

unbox unboxH(Cell* c) {
  if(c->t == INTEGER) return unboxI;
  else if(c->t == FLOAT) return unboxF;
  else if(c->t == DOUBLE) return unboxD;
  else if(c->t == CHAR) return unboxC;
  else return unboxS;
}
