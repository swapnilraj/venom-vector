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
  CellT val;
  type t;
};
typedef struct t_Cell Cell;

struct t_vec {
  Cell* v;
  int size;
};
typedef struct t_vec Vector;

Cell* allocateArray(int);
void setValue(Vector*, int index, union u_Cell val, type);
void setValue(Vector*, int index, CellT val, type);
Cell* getValue(Vector*, int);
Cell* resize(Vector*, int);
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
  setValue(&v, 1, (CellT){99}, INTEGER);
  setValue(&v, 2, (CellT){.f_val = 55.5f}, FLOAT);
  Cell* a = getValue(&v, 1);
  Cell* f = getValue(&v, 2);
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

void setValue(Vector* v, int index,  CellT val, type t) {
  if(index < 0 || index >= v->size) {fprintf(stderr, "Out of bounds"); exit(1);}
  *(v->v + index) = (Cell) {val, t};
}

Cell* getValue(Vector* v, int index) {
  if(index < 0 || index >= v->size) {fprintf(stderr, "Out of bounds"); exit(1);}
  return v->v + index;
}

Cell* resize(Vector* v, int f) {
  return realloc(v->v, f * sizeof(Cell));
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
