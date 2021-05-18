#include <stdlib.h>
#include "cflow.h"

int main(int argc, char** argv) {
  int T = 42;
  float * __restrict__ A = (float*) calloc(2, sizeof(float));
  float * __restrict__ B = (float*) calloc(2, sizeof(float));

  __dace_init_cflow(A, B, T);
  __program_cflow(A, B, T);
  __dace_exit_cflow(A, B, T);

  free(A);
  free(B);
  return 0;
}
