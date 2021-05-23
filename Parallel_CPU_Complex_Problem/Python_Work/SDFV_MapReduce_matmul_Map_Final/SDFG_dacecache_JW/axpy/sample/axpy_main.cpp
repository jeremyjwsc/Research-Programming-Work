#include <cstdlib>
#include "../include/axpy.h"

int main(int argc, char **argv) {
    axpyHandle_t handle;
    double A = 42;
    int N = 42;
    double * __restrict__ X = (double*) calloc(N, sizeof(double));
    double * __restrict__ Y = (double*) calloc(N, sizeof(double));


    handle = __dace_init_axpy(A, N);
    __program_axpy(handle, X, Y, A, N);
    __dace_exit_axpy(handle);

    free(X);
    free(Y);


    return 0;
}
