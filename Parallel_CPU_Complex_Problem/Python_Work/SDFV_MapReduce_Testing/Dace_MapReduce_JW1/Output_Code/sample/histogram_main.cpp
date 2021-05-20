#include <cstdlib>
#include "../include/histogram.h"

int main(int argc, char **argv) {
    histogramHandle_t handle;
    int H = 42;
    int W = 42;
    unsigned char * __restrict__ A = (unsigned char*) calloc((H * W), sizeof(unsigned char));
    unsigned int * __restrict__ hist = (unsigned int*) calloc(256, sizeof(unsigned int));


    handle = __dace_init_histogram(H, W);
    __program_histogram(handle, A, hist, H, W);
    __dace_exit_histogram(handle);

    free(A);
    free(hist);


    return 0;
}
