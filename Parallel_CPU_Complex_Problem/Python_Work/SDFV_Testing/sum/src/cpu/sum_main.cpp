#include <stdlib.h>
#include "sum.h"

int main(int argc, char** argv) {
  int N = 42;
  float * __restrict__ A = (float*) calloc(N, sizeof(float));
  float * __restrict__ out = (float*) calloc(1, sizeof(float));

  __dace_init_sum(A, out, N);
  __program_sum(A, out, N);
  __dace_exit_sum(A, out, N);

  free(A);
  free(out);
  return 0;
}
