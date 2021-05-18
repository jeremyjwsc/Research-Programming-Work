#include <stdlib.h>
#include "multmul_Gemm_Final.h"

int main(int argc, char** argv) {
  int F = 42;
  int G = 42;
  int H = 42;
  dace::complex128 * __restrict__ A = (dace::complex128*) calloc((F * G), sizeof(dace::complex128));
  dace::complex128 * __restrict__ B = (dace::complex128*) calloc((G * H), sizeof(dace::complex128));
  dace::complex128 * __restrict__ C = (dace::complex128*) calloc((F * H), sizeof(dace::complex128));

  __dace_init_multmul_Gemm_Final(A, B, C, F, G, H);
  __program_multmul_Gemm_Final(A, B, C, F, G, H);
  __dace_exit_multmul_Gemm_Final(A, B, C, F, G, H);

  free(A);
  free(B);
  free(C);
  return 0;
}
