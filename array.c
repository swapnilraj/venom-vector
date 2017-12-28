#include <stdio.h>
#include <stdlib.h>

union u_Cell {
  int i_val;
  float f_val;
  double d_val;
  char* s_val;
};

typedef enum {INTEGER, FLOAT, DOUBLE, STRING} type;

struct t_Cell {
  union u_Cell val;
  type t;
};

typedef struct t_Cell Cell;
const int SIZE_CELL = sizeof(Cell);

Cell* allocateArray(int);
void setValue(Cell*, int index, int val, type);
type getValue(Cell*, int);

int main(int argc, char** argv) {
  Cell* array = allocateArray(10);
  setValue(array, 1, 10, INTEGER);
  printf("%d\n", getValue(array, 1));
  return 0;
}

Cell* allocateArray(int s) {
  return malloc(s * sizeof(s * SIZE_CELL));
}

void setValue(Cell* a, int index, int val, type t) {
  *(a + index) = (Cell) {val, t};
}

type getValue(Cell* a, int index) {
  return ((a+index)->val.i_val);
}
