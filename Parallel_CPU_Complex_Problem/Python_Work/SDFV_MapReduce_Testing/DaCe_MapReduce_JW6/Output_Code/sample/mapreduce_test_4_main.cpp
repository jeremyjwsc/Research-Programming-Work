#include <cstdlib>
#include "../include/mapreduce_test_4.h"

int main(int argc, char **argv) {
    mapreduce_test_4Handle_t handle;
    int K = 42;
    int M = 42;
    int N = 42;
    double * __restrict__ A = (double*) calloc((M * N), sizeof(double));
    double * __restrict__ B = (double*) calloc((K * N), sizeof(double));
    double * __restrict__ C = (double*) calloc((K * M), sizeof(double));
    double * __restrict__ D = (double*) calloc(((K * M) * N), sizeof(double));


    handle = __dace_init_mapreduce_test_4(K, M, N);
    __program_mapreduce_test_4(handle, A, B, C, D, K, M, N);
    __dace_exit_mapreduce_test_4(handle);

    free(A);
    free(B);
    free(C);
    free(D);


    return 0;
}
